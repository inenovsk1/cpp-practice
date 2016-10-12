#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// hash map. key = number of characters; the value is a vector of all 
// the strings with this number of characters in them 
using Table = unordered_map<int, vector<string>>;

int main(int argc, char** argv) {
	if (argc < 2) {
		cerr << "Oops, looks like you forgot to specify a file to be read from.." << endl;
		return 1;
	}

	ifstream in(argv[1]);
	if (!in) {
		cerr << "Error openning " << argv[1] << endl;
		return 0;
	}

	string line; // line from the text file
	Table table;
	while (!in.eof()) {
		getline(in, line);
		istringstream input(line);
		string word;

		while (!input.eof()) {

			// clear the last word
			word.clear();

			// read next word on the line
			input >> word;

			// in case we have an empty line, don't add a word of size 0 to our table
			if (word.size() == 0) {
				continue;
			}

			// add the word to our list of other words with this size
			table[word.size()].push_back(word);
		}
	}

	in.close();

	// print the results in an ordered fashion
	// e.g. 1 letter words first, 2 letter words second, etc..
	vector<int> keys;
	for (auto it = table.begin(); it != table.end(); ++it) {
		keys.push_back((*it).first);
	}

	sort(keys.begin(), keys.end());

	for (int i = 0; i < keys.size(); ++i) {
		cout << keys.at(i) << " character words: " << table[keys.at(i)].size() << " words" << endl;
	}

	system("PAUSE");
}
