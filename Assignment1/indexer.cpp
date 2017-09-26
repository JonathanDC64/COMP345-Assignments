#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm> 
#include <map>

using namespace std;

const string DICTIONARY_FILE = "dictionary.txt";
const string FILENAME_FILE = "index.txt";
const unsigned char DICTIONARY_WIDTH = 14;
const unsigned char LOWERCASE_OFFSET = 'a' - 'A';

//Makes a word lower case and removes punctuation
string sanitize(string text) {
	for (char &c : text) {
		//make lowercase
		if (c >= 'A' && c <= 'Z') {
			c += LOWERCASE_OFFSET;
		}
	}

	//remove punctuation
	text.erase(std::remove_if(text.begin(), text.end(), ispunct), text.end());
	return text;
}

//Creates the dictionary from the stopwords filename
void readDictionaryFile(map<string, string> &dictionary) {
	ifstream fin(DICTIONARY_FILE.c_str());
	string stopWord;
	dictionary.clear();
	while (fin >> stopWord) {
		string word = sanitize(stopWord);
		dictionary.insert(pair<string, string>(word, word));
	}
	fin.close();
}

//Generates the dictionary based off of all the words in the documents
void generateDictionary(map<string, string> &dictionary, const vector<string> &documents) {
	for (string document : documents) {
		ifstream fin(document.c_str());
		string word;
		while (fin >> word) {
			string lowercaseWord = sanitize(word);
			dictionary.insert(pair<string, string>(lowercaseWord, lowercaseWord));
		}
		fin.close();
	}
}

void readDocumentNames(vector<string> &filenames) {
	ifstream fin(FILENAME_FILE.c_str());
	string filename;

	while (fin >> filename) {
		filenames.push_back(filename);
	}

	fin.close();
}

vector<int> numOccurences(map<string, string> &dictionary, const string &filename) {
	//initialize an occurences list with the same size as the dictionary and make all their values 0
	vector<int> occurences(dictionary.size(), 0);

	ifstream fin(filename.c_str());
	string word;

	while (fin >> word) {
		//find the index of the word in the map
		int index = distance(dictionary.begin(), dictionary.find(sanitize(word)));
		occurences[index]++;
	}

	fin.close();
	return occurences;
}

int main() {
	map<string, string> dictionary;
	vector<string> documents;

	readDocumentNames(documents);
	generateDictionary(dictionary, documents);

	cout << setw(DICTIONARY_WIDTH) << left << "Dictionary" ;
	for (string file : documents) {
		cout << setw(file.size() + 4) << right << file;
	}
	cout << endl;

	vector<vector<int>> occurences;
	for (string filename : documents) {
		occurences.push_back(numOccurences(dictionary, filename));
	}

	int row = 0;
	for (pair<string, string> dict : dictionary) {
		cout << setw(DICTIONARY_WIDTH) << left << dict.second;
		for (int i = 0; i < occurences.size(); ++i) {
			cout << setw(documents[i].size() + 4) << right << occurences[i][row];
		}
		cout << endl;
		row++;
	}

	system("pause");
	return 0;
}