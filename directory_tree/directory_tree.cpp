#include "directory_tree.hpp"
#include "../misc/get_root_name.hpp"

#include <filesystem>

using namespace directory_tree;
using namespace std::filesystem;

FolderRep DirectoryTree::getDirectoryChildren(string root) {
	vector<FileRep> rootChildren;

	for (const auto& entry : directory_iterator(root)) {
		if (entry.is_regular_file())
			rootChildren.push_back(FileRep(entry.path().filename().string()));
		else {
			FolderRep entryFolder = getDirectoryChildren(entry.path().string());


		}
	}

	return FolderRep(getRootName(root), rootChildren);
}

string DirectoryTree::startAt(string root) {
	FolderRep rootFolder = getDirectoryChildren(root);
	


	return "";
}