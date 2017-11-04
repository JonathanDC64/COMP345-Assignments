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
#include "indexer.h"
#include "stopword.h"
#include "document.h"
#include "query_result.h"
#include "word_tokenizer.h"
#include "sentence_tokenizer.h"

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;


template <typename T, typename E>
class indexer
{
    
    friend bool gtScore(const query_result & left, const query_result & right);
    
    /*! Sends the number of terms in the dictionary and the number of documents to an output stream*/
    friend std::ostream& operator<<(std::ostream& os, const indexer & idx);
    
public:
    
    indexer<T,E>();
    
    /*! Gives the number of documents processed by the index */
    unsigned int size() const;
    
    /*! Displays all terms, their fequency, their weight and document frequency to standard output*/
    void output() const;
    
    /*! Removes all stopword terms from the dictionary*/
    void remove_stop_words();
    
    /*! searches the dictionary and documents for certain keywords*/
    virtual vector<query_result> query(string search, int n = 10) = 0;
    
    /*! Retrieves an indexed document at the specified index*/
    T & operator[](int index);
    
protected:
    
    vector<T> documents;
    map<string, string> dictionary;
    vector<vector<int>> occurences;
    vector<int> document_frequency;
    vector<vector<double>> weights;
    
    const string STOPWORD_FILENAME = "stopwords.txt";
    const string INDEX_FILENAME = "index.txt";

	int N; //Document count
	void generateDictionary();

	void compute(); // used to be called num occurences

	double score(string & query, int document_index);

private:

    
    const stopword stopwords;

    std::string::size_type biggest_word_length = 0;

    void print_legend() const;
    void print_full_line() const;

    double normalize(int term_fequency, int document_frequency);

    double cosine_similarity(const vector<double> & q, const vector<double> & d);
};

template class indexer<document, word_tokenizer>;
template class indexer<sentence, sentence_tokenizer>;