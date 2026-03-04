#pragma once
#ifndef FOLDER_REP_HPP
#define FOLDER_REP_HPP

#include <string>
#include <vector>

using namespace std;

class FileRep {
protected:
	const string name;

public:
	FileRep(const string name) : name(name) {}

	virtual ~FileRep() = default; // Make destructor virtual for polymorphism

	const string getName() const {
		return name;
	}
};

class FolderRep : public FileRep {
	const vector<FileRep*> children;

public:
	FolderRep(const string name, const vector<FileRep*> children) : FileRep(name), children(children) {}

	const vector<FileRep*> getChildren() const {
		return children;
	}
};

#endif