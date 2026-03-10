#define K_INCLUDE_EXT "include-ext"
#define K_EXCLUDE_DIR "exclude-dir"
#define K_MODE "mode"
#define K_ROOT "root"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <filesystem>

#include "file_records/filesystem_node.hpp"
#include "traversals/traversals_content_roots.hpp"
#include "traversals/traversals_string_tree.hpp"
#include "misc/get_content_from_files.hpp"
#include "misc/get_root_name.hpp"

using namespace std;
using namespace file_records;

void throwErr(string reasonInp) {
	throw "Your input failed to specify " + reasonInp + ".";
}

struct Config {
	map<string, vector<string>> flags;

	enum ModeFlag {
		MF_NONE = 0,
		MF_STRUCTURE = 1 << 0,
		MF_CONTENT = 1 << 1
	} MODE_FLAG = ModeFlag::MF_NONE;
} Conf;

//populate static map flags 'flags' with all flags and tags
void parseFlags(const int FLAGS_INDEX, int argc, char* argv[]) {
	string currentFlag = "";
	for (int i = FLAGS_INDEX; i < argc; i++) {
		string token = argv[i];
		if (token == "\\")
			continue;

		//process for --flags
		if (token.rfind("--", 0) == 0)
		{
			currentFlag = token.substr(2);
			Conf.flags[currentFlag]; // ensure key exists
		}

		//process for tags
		else
			Conf.flags[currentFlag].push_back(token);
	}
}

//assign tags and refine where needed
void installFlags(const map<string, vector<string>>::iterator FLAG_INCLUDE_EXTENSIONS_ITER) {
	//ensure file extensions have a dot char at the beginning
	if (FLAG_INCLUDE_EXTENSIONS_ITER != Conf.flags.end())
		for (auto& tag : FLAG_INCLUDE_EXTENSIONS_ITER->second) {
			if (tag[0] != '.')
				tag.insert(tag.begin(), '.');
		}

	//extract one or modes into K_MODE
	auto modeIter = Conf.flags.find(K_MODE);
	if (modeIter != Conf.flags.end())
		for (auto& m : modeIter->second) {
			if (m == "structure")
				Conf.MODE_FLAG = (Config::ModeFlag)(Conf.MODE_FLAG | Conf.MF_STRUCTURE);

			if (m == "content")
				Conf.MODE_FLAG = (Config::ModeFlag)(Conf.MODE_FLAG | Conf.MF_CONTENT);
		}

	//print all flags and tags
	for (const auto& pair : Conf.flags) {
		cout << "--" << pair.first;
		for (const auto& tag : Conf.flags.at(pair.first))
			cout << ' ' << tag;
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	const int FLAGS_INDEX = 1;

	if (argc > FLAGS_INDEX) {
		parseFlags(FLAGS_INDEX, argc, argv);

		const auto FLAG_INCLUDE_EXTENSIONS_ITER = Conf.flags.find(K_INCLUDE_EXT);
		installFlags(FLAG_INCLUDE_EXTENSIONS_ITER);

		auto rootIter = Conf.flags.find(K_ROOT);
		if (rootIter != Conf.flags.end()) {
			//then we have a root path to work with
			filesystem::path rootPath(rootIter->second.at(0));
			filesystem::directory_entry rootEntry(rootPath);

			//build the tree
			FilesystemNode rootNode(&rootEntry);
			rootNode.buildOut(Conf.flags.at(K_EXCLUDE_DIR));

			if (Conf.MODE_FLAG & Conf.MF_STRUCTURE) {
				//list the tree
				string tree = rootNode.name+ '\n';
				traverseStringTree(tree, rootNode);
				cout << "> PROJECT STRUCTURE:" << endl << tree << endl;
			}

			if (FLAG_INCLUDE_EXTENSIONS_ITER != Conf.flags.end()
				&& FLAG_INCLUDE_EXTENSIONS_ITER->second.size() > 0) {
				cout << "> CONTENT EXTENSIONS:" << endl;
				for (auto& contentExtension : FLAG_INCLUDE_EXTENSIONS_ITER->second)
					cout << '-' << contentExtension << endl;

				if (Conf.MODE_FLAG & Conf.MF_CONTENT) {
					//list all roots with extensions that are dedicated to content extraction
					vector<string> contentRoots;
					traverseContentRootsByExtension(contentRoots, rootNode,
						FLAG_INCLUDE_EXTENSIONS_ITER->second);

					cout << endl << "> CONTENT ROOTS:" << endl;
					for (string contentRoot : contentRoots)
						cout << ">> " << contentRoot << endl;

					/*
					vector<string> contents = getContentFromFiles(contentRoots);

					cout << endl << "> CONTENTS:" << endl;
					for (int i = 0; i < contentRoots.size(); i++) {
						cout << ">> " << contentRoots[i] << endl;
						cout << contents[i] << endl << endl;
					}
					*/
				}
			}
			else
				throwErr("file extensions to dedicate for extraction");
		}
	}

	return 0;
}