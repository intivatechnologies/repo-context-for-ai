#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <algorithm>

using namespace std;

enum PlaceOperation {
	TABULATE,
	DETABULATE,
	CONTINUE
};

/* A line placed */
class PlacedLine {
	const string line;
	const PlaceOperation placeOperation;

public:
	const string& getLine() const { return line; };
	const PlaceOperation& getPlaceOperation() const { return placeOperation; };
	explicit PlacedLine(string line, PlaceOperation placeOperation = PlaceOperation::CONTINUE)
		: line(line), placeOperation(placeOperation) {}
};

string getRootName(filesystem::path path) {
	return path.string().substr(path.string().find_last_of("\\") + 1, path.string().size() - 1);
}

static const vector<string> ignoreNames({ ".git", "build" });

static vector<string> includeForFileContents;
static map<string, string> fileContents;

vector<PlacedLine> getPlacedLines(string root) {
	//whenever getPlacedLines() is called, it starts by tabulating its return content
	PlaceOperation nextOperation = PlaceOperation::TABULATE;
	string rootName = getRootName(root);
	vector<PlacedLine> lines;

	//examines each name in the directory
	for (const auto& entry : filesystem::directory_iterator(root)) {
		//extract the file/folder name
		string eps = entry.path().string(), name = eps.substr(root.size() + 1, eps.size() - 1);

		if (entry.is_regular_file()) {
			lines.push_back(PlacedLine(name + ",", nextOperation));
			//fileContents.insert({ root + '\\' + name, vector<string>()});

			//store file content if extension is favoured
			const int dotPosition = name.find_last_of('.');
			if (includeForFileContents.size() > 0 && dotPosition != -1) {
				const string extension = name.substr(dotPosition, name.size() - 1);
				auto includeForContentsCheck = find(includeForFileContents.begin(),
					includeForFileContents.end(), extension);

				if (includeForContentsCheck != includeForFileContents.end()) {
					ifstream file(root + '\\' + name);
					if (!file)
						throw std::runtime_error("Failed to open file");

					ostringstream buffer;
					buffer << file.rdbuf(); //read entire file

					fileContents.insert({ root + '\\' + name, buffer.str() });
				}
			}
		}
		else {
			auto ignoreNameCheck = find(ignoreNames.begin(), ignoreNames.end(), name);
			if (ignoreNameCheck != ignoreNames.end())
				//ignores all folder contents with a single line
				lines.push_back(PlacedLine(name + ": { ... },", nextOperation));
			else {
				lines.push_back(PlacedLine(name + ": {", nextOperation));

				//function recalls itself to acquire inner/nested content
				vector<PlacedLine> nestedLines = getPlacedLines(root + "\\" + name);
				for (const auto& nestedEntry : nestedLines)
					lines.push_back(nestedEntry);

				//if there is no inner/nested content, no tabulation/detabulation occurs
				lines.push_back(PlacedLine("}", nestedLines.size() > 0
					? PlaceOperation::DETABULATE : PlaceOperation::CONTINUE));
			}
		}

		if (nextOperation != PlaceOperation::CONTINUE)
			nextOperation = PlaceOperation::CONTINUE;
	}

	return lines;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		if (argc > 2) {
			for (int i = 2; i < argc; i++)
				includeForFileContents.push_back(argv[i]);
		}

		cout << "> PROJECT STRUCTURE:" << endl;

		vector<PlacedLine> lines({ PlacedLine(getRootName(argv[1]) + ": {") });

		for (const auto& nestedEntry : getPlacedLines(argv[1]))
			lines.push_back(nestedEntry);

		lines.push_back(PlacedLine("}", PlaceOperation::DETABULATE));

		string indentation = "";
		int tabsSoFar = 0;

		//loads indentation into the text (based on the PlacedLine objects)
		for (PlacedLine pl : lines) {
			switch (pl.getPlaceOperation()) {
			case PlaceOperation::TABULATE:
				indentation += "\t";
				++tabsSoFar;
				break;
			case PlaceOperation::DETABULATE:
				--tabsSoFar;
				indentation = "";
				for (int i = 0; i < tabsSoFar; i++)
					indentation += "\t";
				break;
			}

			cout << indentation << pl.getLine() << endl;
		}

		if (argc > 2) {
			cout << "> FILE CONTENTS" << endl;
			for (const auto& [key, value] : fileContents)
			{
				cout << ">> \"" << key << '\"' << endl;
				cout << value << endl << endl;
			}
		}

		return 0;
	}

	cout << "An input directory could not be found." << endl;
	return -1;
}