#pragma once

#include <string>
#include <vector>
#include <map>

#include "../file_records/folder_rep.hpp"

using namespace std;

namespace directory_tree {
	class DirectoryTree {
		//privatize constructor to enforce singleton pattern
		DirectoryTree() = default;

		string indentationVolume = "";

		void modifyIndentationStep(bool positiveStep);
		void getFamilyOfChildren(string& textualRep, FolderRep* parent);
		FolderRep* getFolderAtRoot(string root);

	public:
		static DirectoryTree& getInstance() {
			static DirectoryTree instance; // Thread-safe in C++11+
			return instance;
		}

		// Delete copy/assignment to ensure single instance
		DirectoryTree(const DirectoryTree&) = delete;
		DirectoryTree& operator=(const DirectoryTree&) = delete;

		string startAt(string root);
	};
}
