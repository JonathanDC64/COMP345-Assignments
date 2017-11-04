//
//  sentence_indexer.hpp
//  assignment3
//
//  Created by justin baron on 2017-11-03.
//  Copyright © 2017 justin baron. All rights reserved.
//

#pragma once
#include "indexer.h"
#include "sentence.h"
#include "sentence_tokenizer.h"

class sentence_indexer : public indexer<sentence, sentence_tokenizer>
{
	friend bool gtScoreGrouped(const query_result & left, const query_result & right);
	/*! Adds a document file to an indexer*/
	friend void operator>>(sentence & s, sentence_indexer & idx);
public:
	sentence_indexer();
	virtual vector<query_result> query(string search, int n = 500) override;
	static const std::string INDEX_DOCS;
};


