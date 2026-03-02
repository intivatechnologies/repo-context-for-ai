#pragma once

#include <string>
#include <vector>
#include <map>

#include "../misc/get_root_name.hpp"

using namespace std;

enum PlaceOperation {
	TABULATE,
	DETABULATE,
	CONTINUE
};

/* A line placed */
class PlacedLine {
	static const vector<string> ignoreDirectoryNames;

	const string line;
	const PlaceOperation placeOperation;

public:
	static vector<PlacedLine> getPlacedLines(string root);

	const string& getLine() const { return line; };
	const PlaceOperation& getPlaceOperation() const { return placeOperation; };
	explicit PlacedLine(string line, PlaceOperation placeOperation = PlaceOperation::CONTINUE)
		: line(line), placeOperation(placeOperation) {
	}
};