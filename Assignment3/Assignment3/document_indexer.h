#pragma once
#include "indexer.h"
#include "stopword.h"
#include "document.h"
#include "query_result.h"
#include "word_tokenizer.h"
#include <string>
#include <fstream>
#include <map>
#include <iostream>


using namespace std;

/*! The indexer is responsible for storing and maintaining your document index*/
class document_indexer : public indexer<document, word_tokenizer>
{
	/*! prints information about the class */
	friend std::ostream & operator<<(std::ostream & os, const document_indexer & right);

	/*! Adds a document file to an indexer*/
	friend void operator>>(document & d, document_indexer & idx);
public:

	/*! Default construct creates an indexer with static index file */
	document_indexer();

	/*! returns a vector of top (n) query_results for the given query (search) */
	virtual vector<query_result> query(string search, int n = 10) override;
};

