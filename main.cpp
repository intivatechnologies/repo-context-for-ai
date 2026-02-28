#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <filesystem>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc > 1) {
		string root = argv[1], rootName = root.substr(root.find_last_of("\\") + 1, root.size() - 1);
		vector<string> subNames;

		for (const auto& entry : filesystem::directory_iterator(argv[1])) {
			string eps = entry.path().string(), name = eps.substr(root.size() + 1, eps.size() - 1);
			subNames.push_back(name);
		}

		cout << rootName << ": {" << endl;
		for (const auto& subName : subNames) {
			cout << "\t" << subName << "," << endl;
		}
		cout << "}" << endl;

		return 0;
	}

	cout << "An input directory could not be found." << endl;
	return -1;
}