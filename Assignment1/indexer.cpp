#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string DICTIONARY_FILE = "dictionary.txt";
const string FILENAME_FILE = "index.txt";

void readDictionaryFile(vector<string> &dictionary) {
	ifstream fin(DICTIONARY_FILE.c_str());
	string stopWord;

	while (fin >> stopWord) {
		dictionary.push_back(stopWord);
	}

	fin.close();
}

void readFilenames(vector<string> &filenames) {
	ifstream fin(FILENAME_FILE.c_str());
	string filename;

	while (fin >> filename) {
		filenames.push_back(filename);
	}

	fin.close();
}

void numOccurences(const string &stopWord, const string &filename) {
	ifstream fin(filename.c_str());
	string line;

	while (fin >> line) {
		int start = 0;
		int end = 0;
		for (int i = 0; i < line.size(); ++i) {
			cout << line.at(i) << endl;
			if (line.at(i) == ' ') {
				end = i - 1;
				string word = line.substr(start, end);
				start = i + 1;
				cout << word << endl;
			}
		}
	}

	fin.close();
}

int main() {
	vector<string> dictionary;
	readDictionaryFile(dictionary);

	vector<string> filenames;
	readFilenames(filenames);

	numOccurences("the", "Doc1.txt");

	system("pause");
	return 0;
}