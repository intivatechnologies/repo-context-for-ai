#include "directory_tree.hpp"
#include "../misc/get_root_name.hpp"

#include <filesystem>

using namespace directory_tree;

const char DirectoryTree::indentationUnits[3] = { ' ', ' ' };

void DirectoryTree::modifyIndentationStep(bool positiveStep) {
	if (positiveStep) {
		for (char indentationUnit : indentationUnits)
			indentationVolume += indentationUnit;
	}
	else for (char indentationUnit : indentationUnits)
		indentationVolume = indentationVolume.substr(0, indentationVolume.find_last_of(indentationUnit));
}

void DirectoryTree::getFamilyOfChildren(string& textualRep, FolderRep* parent) {
	modifyIndentationStep(true);

	vector<FolderRecord*> children = parent->getChildren();
	if(children.size() > 0)
		for (const auto& entryChild : children) {
			if (entryChild != nullptr) {
				textualRep += indentationVolume + entryChild->getName() + '\n';
				if (entryChild->recordClassifier == FolderRecord::RecordClassifier::FOLDER)
					getFamilyOfChildren(textualRep, static_cast<FolderRep*>(entryChild));
			}
		}
		
	modifyIndentationStep(false);
}

void DirectoryTree::getFamily(string& textualRep, FolderRep* parent) {
	textualRep += indentationVolume + parent->getName() + '\n';
	getFamilyOfChildren(textualRep, parent);
}

string DirectoryTree::startAt(FolderRep* rep) {
	string textualRep = "";
	getFamily(textualRep, rep);

	return textualRep;
}