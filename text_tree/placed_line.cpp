#include "placed_line.hpp"

const vector<string> PlacedLine::ignoreDirectoryNames{ ".git", "build" };

vector<PlacedLine> PlacedLine::getPlacedLines(string root) {
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

			/*
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
			*/
		}
		else {
			auto ignoreNameCheck = find(ignoreDirectoryNames.begin(), ignoreDirectoryNames.end(), name);
			if (ignoreNameCheck != ignoreDirectoryNames.end())
				//ignores all folder contents with a single line
				lines.push_back(PlacedLine(name + ": { ... },", nextOperation));
			else {
				//function recalls itself to acquire inner/nested content
				vector<PlacedLine> nestedLines = getPlacedLines(root + "\\" + name);

				if (nestedLines.size() > 0) {
					lines.push_back(PlacedLine(name + ": {", nextOperation));
					for (const auto& nestedEntry : nestedLines)
						lines.push_back(nestedEntry);
					lines.push_back(PlacedLine("},", PlaceOperation::DETABULATE));
				}
				else
					lines.push_back(PlacedLine(name + ": {},", nextOperation));
			}
		}

		if (nextOperation != PlaceOperation::CONTINUE)
			nextOperation = PlaceOperation::CONTINUE;
	}

	return lines;
}