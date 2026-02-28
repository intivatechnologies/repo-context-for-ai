#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <filesystem>

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

int main(int argc, char* argv[]) {
	if (argc > 1) {
		PlaceOperation nextOperation = PlaceOperation::TABULATE;
		string root = argv[1], rootName = root.substr(root.find_last_of("\\") + 1, root.size() - 1);
		vector<PlacedLine> lines({ PlacedLine(rootName + ": {")});

		//examines each name in the directory
		for (const auto& entry : filesystem::directory_iterator(argv[1])) {
			string eps = entry.path().string(), name = eps.substr(root.size() + 1, eps.size() - 1);
			if(entry.is_regular_file())
				lines.push_back(PlacedLine(name, nextOperation));
			else {
				/* CHANGE THIS */
				lines.push_back(PlacedLine(name + ": {", nextOperation));
				lines.push_back(PlacedLine("}"));
			}

			if (nextOperation != PlaceOperation::CONTINUE)
				nextOperation = PlaceOperation::CONTINUE;
		}
		lines.push_back(PlacedLine("}", PlaceOperation::DETABULATE));

		string indentation = "";
		int tabsSoFar = 0;

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

		return 0;
	}

	cout << "An input directory could not be found." << endl;
	return -1;
}