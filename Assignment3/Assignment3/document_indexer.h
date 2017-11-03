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
	
public:

	/*! Default construct creates an indexer with static index file */
	document_indexer();

	
private:
	
    virtual void initialize() override;
    
};

