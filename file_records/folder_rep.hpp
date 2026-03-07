#pragma once
#ifndef FOLDER_REP_HPP
#define FOLDER_REP_HPP

#include <string>
#include <vector>

using namespace std;

namespace file_records {
	class FolderRecord {
		const string name, root;

	public:
		enum RecordClassifier { FILE, FOLDER } recordClassifier;

		FolderRecord(const string name, const string root) : name(name), root(root) {}
		virtual ~FolderRecord() = default; // Make destructor virtual for polymorphism

		const string getName() const {
			return name;
		}

		const string getRoot() const {
			return root;
		}
	};

	class FileRep : public FolderRecord {
	protected:
		const string extension;

	public:
		FileRep(const string name, const string root, const string extension) 
			: FolderRecord(name, root), extension(extension) {
			recordClassifier = RecordClassifier::FILE;
		}

		const string getExtension() const {
			return extension;
		}
	};

	class FolderRep : public FolderRecord {
		static const vector<string> disincludeFolders;

		const vector<FolderRecord*> children;

	public:
		static FolderRep* installFolderAtRoot(string root);
		static void loadAllRootsByExtension(vector<string>& roots, FolderRep* parentFolder,
			const string ext);

		FolderRep(const string name, const string root, const vector<FolderRecord*> children)
			: FolderRecord(name, root), children(children) {
			recordClassifier = RecordClassifier::FOLDER;
		}

		const vector<FolderRecord*>& getChildren() const {
			return children;
		}
	};
}

#endif