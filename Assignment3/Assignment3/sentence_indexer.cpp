#include "sentence_indexer.h"
#include <algorithm>
#include <fstream>

using namespace std;

const string sentence_indexer::INDEX_DOCS = "index_docs.txt";

sentence_indexer::sentence_indexer()
	: indexer()
{
	ifstream fin(sentence_indexer::INDEX_DOCS.c_str());
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

vector<query_result> sentence_indexer::query(string search, int n)
{
	vector<query_result> results;

	for (int i = 0; i < documents.size(); i++) {
		double score = this->score(search, i);
		if (score != 0) {
			results.push_back(query_result(documents[i], score));
		}
	}
	sort(results.begin(), results.end(), gtScoreGrouped);
	vector<query_result> top_results;
	int totalWords = 0;
	for (query_result qr : results) {
		totalWords += qr.found_document->size();
		if (totalWords > n) {
			break;
		}
		top_results.push_back(qr);
	}
	return top_results;
}

bool gtScoreGrouped(const query_result & left, const query_result & right)
{
	const sentence * ls = dynamic_cast<const sentence*>(left.found_document);
	const sentence * rs = dynamic_cast<const sentence*>(right.found_document);
	if (ls->name() != rs->name()) {
		return ls->name() < rs->name();
	}
	else {
		return ls->get_pos() < rs->get_pos();
	}
}

void operator>>(sentence & s, sentence_indexer & idx)
{
	idx.documents.push_back(s);
}
