#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm> 
#include <map>

using namespace std;

//test
const string DICTIONARY_FILE = "dictionary.txt";
const string FILENAME_FILE = "index.txt";
const unsigned char DICTIONARY_WIDTH = 14;
const unsigned char LOWERCASE_OFFSET = 'a' - 'A';
string::size_type biggestWordLength = 0;

//Makes a word lower case and removes punctuation
string sanitize(string text) {
	for (char &c : text) {
		//make lowercase
		if (c >= 'A' && c <= 'Z') {
			c += LOWERCASE_OFFSET;
		}
	}

	//remove punctuation
	text.erase(std::remove_if(text.begin(), text.end(), ::ispunct), text.end());
	return text;
}

//Creates the dictionary from the stopwords filename
void readDictionaryFile(map<string, string> &dictionary) {
	ifstream fin(DICTIONARY_FILE.c_str());
	string stopWord;
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
			if (word.length() > biggestWordLength) {
				biggestWordLength = word.length();
			}
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
		map<string, string>::iterator it = dictionary.find(sanitize(word));
		//only add occurence if word is in the dictionary
		if (it != dictionary.end()) {
			//find the index of the word in the map
			int index = distance(dictionary.begin(), it);
			occurences[index]++;
		}
	}

	fin.close();
	return occurences;
}


const void printFullLine(const vector<string>& documents) {
	for (int i = 0; i<biggestWordLength + 4; i++) {
		cout << "-";
	}
	for (int i = 0; i<documents.size(); i++) {
		cout << "-";
		for (int j = 0; j<documents[i].size(); j++) {
			cout << "-";
		}
		cout << "--";
	} cout << endl;
}

void printLegend(const vector<string>& documents) {
	printFullLine(documents);
	cout << "| " << left << setw(biggestWordLength) << "Dictionary" << " |";
	for (int i = 0; i<documents.size(); i++) {
		cout << " " + documents[i] + " |";
	} cout << endl;
	printFullLine(documents);
}


void output(map<string, string> &dictionary, const vector<string> &documents) {
	
	printLegend(documents);
	
	vector<vector<int>> occurences;
	for (string filename : documents) {
		occurences.push_back(numOccurences(dictionary, filename));
	}

	vector<int> totals(documents.size(), 0);
	int row = 0;
	for (pair<string, string> dict : dictionary) {
		cout << "| " << left << setw(biggestWordLength) << dict.second << " |";
		for (int i = 0; i < occurences.size(); ++i) {
			cout << setw(documents[i].size() + 1) << right << occurences[i][row] << " |";
			totals[i] += occurences[i][row];
		}
		cout << endl;
		row++;
	}

	printFullLine(documents);
	cout << "| " << left << setw(biggestWordLength) << "Totals" << " |";
	for (int i = 0; i < totals.size(); ++i) {
		cout << setw(documents[i].size() + 1) << right << totals[i] << " |";
	}
	cout << endl;
	printFullLine(documents);
	cout << endl;
}

void removeStopWords(map<string, string>& dictionary) {
	string stopWord;
	map<string, string>::iterator it;

	ifstream ifs(DICTIONARY_FILE.c_str());
	while (ifs >> stopWord) {
		stopWord = sanitize(stopWord);
		it = dictionary.find(stopWord);

		if (it != dictionary.end()) {
			dictionary.erase(it);
		}
	}
}



int main() {
	map<string, string> dictionary;
	vector<string> documents;

	readDocumentNames(documents);
	generateDictionary(dictionary, documents);

	output(dictionary, documents);

	removeStopWords(dictionary);

	output(dictionary, documents);
	
	system("pause");
	return 0;
}
