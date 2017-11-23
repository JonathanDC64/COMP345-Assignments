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

class sentence_indexer : public indexer
{
	
	/*! prints information about the class */
	friend std::ostream & operator<<(std::ostream & os, const sentence_indexer & right);
	/*! sorts the query_results by their name, and then by their position in the document */
	friend bool gtScoreGrouped(const query_result & left, const query_result & right);
public:

	/*! Default constructor */
	sentence_indexer();
	/*! Gets the top query_result (score) until the sums of their words reached (N) and returns them as a vector */
	virtual vector<query_result> query(string search, int n = 500) override;

private:
	static const std::string INDEX_DOCS;
};


