#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace directory_tree {
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
