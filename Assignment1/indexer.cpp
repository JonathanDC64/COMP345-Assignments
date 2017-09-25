#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string DICTIONARY_FILE = "dictionary.txt";
const string FILENAME_FILE = "index.txt";
const unsigned char DICTIONARY_WIDTH = 14;
const unsigned char LOWERCASE_OFFSET = 'A' - 'a';

string toLowerCase(string text) {
	for (char &c : text) {
		if (c >= 'A' && c <= 'Z') {
			c += LOWERCASE_OFFSET;
		}
	}
	return text;
}

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

int numOccurences(const string &stopWord, const string &filename) {
	ifstream fin(filename.c_str());
	string word;
	int occurences = 0;


	while (fin >> word) {
		if (toLowerCase(word) == toLowerCase(stopWord)) {
			occurences++;
		}
	}

	fin.close();
	return occurences;
}

int main() {
	vector<string> dictionary;
	readDictionaryFile(dictionary);

	vector<string> filenames;
	readFilenames(filenames);

	cout << toLowerCase("ABCDEFGHIJKLMNOPQRSTUVWXYZ") << endl;

	cout << setw(DICTIONARY_WIDTH) << left << "Dictionary" ;
	for (string file : filenames) {
		cout << setw(file.size() + 4) << right << file;
	}
	cout << endl;

	for (string dict : dictionary) {
		cout << setw(DICTIONARY_WIDTH) << left << dict;
		for (string file : filenames) {
			cout << setw(file.size() + 4) << right << numOccurences(dict, file);
		}
		cout << endl;
	}

	system("pause");
	return 0;
}