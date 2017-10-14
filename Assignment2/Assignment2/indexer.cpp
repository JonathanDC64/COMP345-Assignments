#include "indexer.h"
#include <fstream>
#include <iomanip>

indexer::indexer()
	: stopwords(STOPWORD_FILENAME.c_str())
{
	std::ifstream fin(this->INDEX_FILENAME.c_str());
	std::string filename;

	while (fin >> filename) {
		document d(filename);
		d >> *this;
	}
	this->generateDictionary();
}


indexer::~indexer()
{
}

unsigned int indexer::size() const
{
	return this->documents.size();
}

void indexer::output_occurences() const
{
	this->output(false);
}

void indexer::output_occurences_filtered() const
{
	this->output(true);
}

void indexer::printLegend() const
{
	printFullLine();
	cout << "| " << left << setw(biggestWordLength) << "Dictionary" << " |";
	for (int i = 0; i<documents.size(); i++) {
		cout << " " + documents[i].name() + " |";
	} cout << endl;
	printFullLine();
}

void indexer::printFullLine() const
{
	for (int i = 0; i<biggestWordLength + 4; i++) {
		cout << "-";
	}
	for (int i = 0; i<documents.size(); i++) {
		cout << "-";
		for (int j = 0; j<documents[i].name().size(); j++) {
			cout << "-";
		}
		cout << "--";
	} cout << endl;
}

void indexer::output(bool filtered) const
{
	map<string, string> dictionary_copy(this->dictionary);

	if (filtered) {
		this->removeStopWords(dictionary_copy);
	}

	printLegend();

	vector<vector<int>> occurences;
	for (document doc : documents) {
		occurences.push_back(numOccurences(doc.name()));
	}

	vector<int> totals(documents.size(), 0);
	int row = 0;
	for (pair<string, string> dict : dictionary_copy) {
		cout << "| " << left << setw(biggestWordLength) << dict.second << " |";
		for (int i = 0; i < occurences.size(); ++i) {
			cout << setw(documents[i].name().size() + 1) << right << occurences[i][row] << " |";
			totals[i] += occurences[i][row];
		}
		cout << endl;
		row++;
	}

	printFullLine();
	cout << "| " << left << setw(biggestWordLength) << "Totals" << " |";
	for (int i = 0; i < totals.size(); ++i) {
		cout << setw(documents[i].name().size() + 1) << right << totals[i] << " |";
	}
	cout << endl;
	printFullLine();
	cout << endl;
}

void indexer::generateDictionary()
{
	tokenizer t;
	for (document doc : this->documents) {
		std::vector<std::string> tokens = t.tokenize(doc.name());
		for (std::string token : tokens) {
			this->dictionary.insert(pair<string, string>(token, token));
		}
	}

	for (pair<string, string> d : dictionary) {
		string token = d.first;
		if (token.length() > biggestWordLength) {
			biggestWordLength = token.length();
		}
	}
}

void indexer::removeStopWords(map<string, string>& dictionary) const
{
	map<string, string>::iterator it;
	for (pair<string, string> d : dictionary) {
		
		string word = d.second;

		if (stopwords(word)) {
			it = dictionary.find(word);

			if (it != dictionary.end()) {
				dictionary.erase(it);
			}
		}
	}
}

vector<int> indexer::numOccurences(const string & filename) const
{
	//initialize an occurences list with the same size as the dictionary and make all their values 0
	vector<int> occurences(dictionary.size(), 0);

	ifstream fin(filename.c_str());
	string word;

	while (fin >> word) {
		map<string, string>::const_iterator it = this->dictionary.find(word);
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


void operator>>(document & d, indexer & idx)
{
	idx.documents.push_back(d);
}
