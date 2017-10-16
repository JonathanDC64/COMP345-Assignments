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
	void output() const;
	void removeStopWords();
private:
	int N; //Document count
	const string STOPWORD_FILENAME = "stopwords.txt";
	const string INDEX_FILENAME = "index.txt";
	const stopword stopwords;

	string::size_type biggestWordLength = 0;

	vector<document> documents;
	map<string, string> dictionary;
	vector<vector<int>> occurences;
	vector<int> document_frequency;
	vector<vector<double>> weights;


	void generateDictionary();

	void print_legend() const;
	void printFullLine() const;
	
	void numOccurences();

	double calc_weight(int term_fequency, int document_frequency);
};

