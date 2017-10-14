#pragma once
#include "tokenizer.h"
#include "stopword.h"
#include "document.h"
#include <string>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

class indexer
{
	friend void operator>>(document & d, indexer & idx);
public:
	indexer();
	~indexer();
	unsigned int size() const;
	int normalize();
	void output_occurences() const;
	void output_occurences_filtered() const;
private:
	static const int N = 10; //Document count
	const string STOPWORD_FILENAME = "stopwords.txt";
	const string INDEX_FILENAME = "index.txt";
	const stopword stopwords;

	string::size_type biggestWordLength = 0;

	vector<document> documents;
	map<string, string> dictionary;

	void generateDictionary();

	void printLegend() const;
	void printFullLine() const;
	void output(bool filtered) const;

	void removeStopWords(map<string, string>& dictionary) const;
	static vector<int> numOccurences(const map<string, string>& dictionary, const string &filename);
};

