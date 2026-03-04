#include "directory_tree.hpp"
#include "../misc/get_root_name.hpp"

#include <filesystem>

using namespace directory_tree;
using namespace std::filesystem;

void DirectoryTree::modifyIndentationStep(bool positiveStep) {
	indentationVolume = positiveStep ? indentationVolume + '\t' :
		indentationVolume.substr(0, indentationVolume.find_last_of("\t"));
}

void DirectoryTree::getFamilyOfChildren(string& textualRep, FolderRep* parent) {
	textualRep += indentationVolume + parent->getName() + '\n';
	modifyIndentationStep(true);
	for (const auto& entryChild : parent->getChildren())
		textualRep += indentationVolume + entryChild->getName() + '\n';
	modifyIndentationStep(false);
}

FolderRep* DirectoryTree::getFolderAtRoot(string root) {
	vector<FileRep*> rootChildren;

	for (const auto& entry : directory_iterator(root)) {
		if (entry.is_regular_file())
			rootChildren.push_back(new FileRep(entry.path().filename().string()));
		else
			rootChildren.push_back(getFolderAtRoot(entry.path().string()));
	}

	return new FolderRep(getRootName(root), rootChildren);
}

string DirectoryTree::startAt(string root) {
	FolderRep* rootFolder = getFolderAtRoot(root);
	string textualRep = "";

	for (const auto& entry : rootFolder->getChildren()) {
		if (entry != nullptr) {
			if (dynamic_cast<FolderRep*>(entry) != nullptr)
				getFamilyOfChildren(textualRep, static_cast<FolderRep*>(entry));
			else
				textualRep += indentationVolume + entry->getName() + '\n';
		}
	}

	return textualRep;
}