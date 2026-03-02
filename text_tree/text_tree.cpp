#include "text_tree.hpp"
#include "placed_line.hpp"
#include "../misc/get_root_name.hpp"

string TextTree::startAt(const char* root) {
	vector<PlacedLine> lines;
	{
		vector<PlacedLine> nestedLines = PlacedLine::getPlacedLines(root);
		if (nestedLines.size() > 0) {
			lines.push_back(PlacedLine(getRootName(root) + ": {"));
			for (const auto& nestedEntry : nestedLines)
				lines.push_back(nestedEntry);
			lines.push_back(PlacedLine("},", PlaceOperation::DETABULATE));
		}
		else
			lines.push_back(PlacedLine(getRootName(root) + ": {},"));
	}

	string text_tree = "", indentation = "";
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

		text_tree += indentation + pl.getLine() + "\n";
	}

	return text_tree;
}