#include "filesystem_node.hpp"

using namespace file_records;

void FilesystemNode::buildOut(vector<string> excludeDirs) {
	for (filesystem::directory_entry entry : filesystem::directory_iterator(path)) {
		FilesystemNode entryNode(&entry);

		if (entry.is_directory()) {
			bool isADisincludedFolderNest = false;

			for (const auto& disincludeFolderNest : excludeDirs)
				if (entryNode.name == disincludeFolderNest) {
					isADisincludedFolderNest = true;
					break;
				}

			if (!isADisincludedFolderNest)
				entryNode.buildOut(excludeDirs);
		}

		children.push_back(entryNode);
	}
}