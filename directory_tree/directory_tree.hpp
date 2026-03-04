#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace directory_tree {
	class FileRep {
	protected:
		string name;

	public:
		FileRep(string name) : name(name) {}
	};

	class FolderRep : public FileRep {
		vector<FileRep> children;

	public:
		FolderRep(string name, vector<FileRep> children) : FileRep(name), children(children) {}
	};

	class DirectoryTree {
		static FolderRep getDirectoryChildren(string root);

	public:
		static string startAt(string root);
	};
}
