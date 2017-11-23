//
//  indexer.hpp
//  assignment3
//
//  Created by justin baron on 2017-11-03.
//  Copyright © 2017 justin baron. All rights reserved.
//

#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include "stopword.h"
#include "document.h"
#include "query_result.h"
#include "word_tokenizer.h"
#include "sentence_tokenizer.h"
#include "term_info.h"

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::multimap;

typedef map<string, map<int, term_info>> dmap;

class indexer
{
    
	friend void operator>>(index_item & d, indexer & idx);

	/*! Returns true if the left query_result has a bigger score than the right */
    friend bool gtScore(const query_result & left, const query_result & right);
    
    /*! Sends the number of terms in the dictionary and the number of documents to an output stream*/
    friend std::ostream& operator<<(std::ostream& os, const indexer & idx);
    
public:
    
	/*! Default constructor */
    indexer();
    
    /*! Gives the number of documents processed by the index */
    unsigned int size() const;
    
    /*! Removes all stopword terms from the dictionary*/
    void remove_stop_words();
    
    /*! searches the dictionary and documents for certain keywords*/
    virtual vector<query_result> query(string search, int n = 10) = 0;
    
    /*! Retrieves an indexed document at the specified index*/
    index_item * operator[](int index);
    
protected:
    
    vector<index_item*> documents;
	dmap dictionary;
	map<string, int> occurence_map;
	vector<double> denoms;
    
    const string STOPWORD_FILENAME = "stopwords.txt";
    const string INDEX_FILENAME = "index.txt";

	int N; //Document count
	void generateDictionary();

	void compute(); // used to be called num occurences

	double score(string & query, int document_index);

private:
    
    const stopword stopwords;

    string::size_type biggest_word_length = 0;

    double normalize(int term_fequency, int document_frequency);

    double cosine_similarity(const vector<double> & q, int document_index);

};