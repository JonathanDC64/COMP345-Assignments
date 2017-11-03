#include "sentence_indexer.h"
//
//  sentence_indexer.cpp
//  assignment3
//
//  Created by justin baron on 2017-11-03.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "sentence_indexer.h"
#include <fstream>

using namespace std;

sentence_indexer::sentence_indexer()
	: indexer()
{
	ifstream fin(this->INDEX_FILENAME.c_str());
	string filename;
	vector<sentence> sentences;
	sentence_tokenizer st;

	while (fin >> filename) {
		document d(filename);
		sentences = st.tokenize(d);

		for (sentence s : sentences)
			s >> *this;
	}
	this->N = documents.size();
	this->generateDictionary();
	this->compute();
}

void operator>>(sentence & s, sentence_indexer & idx)
{
	idx.documents.push_back(s);
}
