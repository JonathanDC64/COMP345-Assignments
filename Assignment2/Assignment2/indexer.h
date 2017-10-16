#pragma once
#include "tokenizer.h"
#include "stopword.h"
#include "document.h"
#include "query_result.h"
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
	void output() const;
	void remove_stop_words();
	vector<query_result> query(string search, int n = 10);
	document operator[](int index);
private:
	int N; //Document count
	const string STOPWORD_FILENAME = "stopwords.txt";
	const string INDEX_FILENAME = "index.txt";
	const stopword stopwords;

	string::size_type biggest_word_length = 0;

	vector<document> documents;
	map<string, string> dictionary;
	vector<vector<int>> occurences;
	vector<int> document_frequency;
	vector<vector<double>> weights;


	void generateDictionary();

	void print_legend() const;
	void print_full_line() const;
	

	void compute(); // used to be called num occurences

	double normalize(int term_fequency, int document_frequency);
	double score(string & query, int document_index);

	double cosine_similarity(const vector<double> & q, const vector<double> & d);
};

