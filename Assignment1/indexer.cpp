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

//Creates the dictionary from the stopwords file
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

int numOccurences(const string &stopWord, const string &filename) {
	ifstream fin(filename.c_str());
	string word;
	int occurences = 0;


	while (fin >> word) {
		if (sanitize(word) == stopWord) {
			occurences++;
		}
	}

	fin.close();
	return occurences;
}

int main() {
	map<string, string> dictionary;
	//readDictionaryFile(dictionary);
	//sort(dictionary.begin(), dictionary.end());

	vector<string> documents;
	readDocumentNames(documents);

	generateDictionary(dictionary, documents);

	cout << setw(DICTIONARY_WIDTH) << left << "Dictionary" ;
	for (string file : documents) {
		cout << setw(file.size() + 4) << right << file;
	}
	cout << endl;

	for (pair<string, string> dict : dictionary) {
		cout << setw(DICTIONARY_WIDTH) << left << dict.second;
		for (string file : documents) {
			cout << setw(file.size() + 4) << right << numOccurences(dict.second, file);
		}
		cout << endl;
	}

	system("pause");
	return 0;
}