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

/*! The indexer is responsible for storing and maintaining your document index*/
class indexer
{
	friend bool gtScore(const query_result & left, const query_result & right);

	/*! Adds a document file to an indexer*/
	friend void operator>>(document & d, indexer & idx);

	/*! Sends the number of terms in the dictionary and the number of documents to an output stream*/
	friend std::ostream& operator<<(std::ostream& os, const indexer & idx);
public:

	/*! Default construct creates an indexer with static index file */
	indexer();

	/*! Gives the number of documents processed by the index */
	unsigned int size() const;

	/*! Displays all terms, their fequency, their weight and document frequency to standard output*/
	void output() const;

	/*! Removes all stopword terms from the dictionary*/
	void remove_stop_words();

	/*! searches the dictionary and documents for certain keywords*/
	vector<query_result> query(string search, int n = 10);

	/*! Retrieves an indexed document at the specified index*/
	document & operator[](int index);
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

