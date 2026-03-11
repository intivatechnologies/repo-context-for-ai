#pragma once

#include "../file_records/filesystem_node.hpp"

using namespace file_records;

void traverseContentRootsByExtension(vector<string>& contentRoots, const FilesystemNode& node,
	const vector<string>& contentExtensions) {
	for (FilesystemNode child : node.children) {
		string childRoot = child.path.string();

		if (child.children.size() > 0)
			traverseContentRootsByExtension(contentRoots, child, contentExtensions);
		else for (const auto& contentExtension : contentExtensions)
			if (child.extension == contentExtension) {
				contentRoots.push_back(childRoot);
				break;
			}
	}
}