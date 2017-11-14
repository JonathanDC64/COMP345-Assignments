#include "document_indexer.h"
#include <algorithm>
using namespace std;


document_indexer::document_indexer()
	: indexer<document,word_tokenizer>()
{
	ifstream fin(this->INDEX_FILENAME.c_str());
	string filename;

	while (fin >> filename) {
		document d(filename);
		d >> *this;
	}
	this->N = documents.size();
	this->generateDictionary();
	this->compute();
}

vector<query_result> document_indexer::query(string search, int n)
{
	vector<query_result> results;

	for (int i = 0; i < documents.size(); i++) {
		double score = this->score(search, i);
		results.push_back(query_result(documents[i], score));
	}
	sort(results.begin(), results.end(), gtScore);

	if (results.size() < n) {
		n = results.size();
	}

	vector<query_result> top_results(results.begin(), results.begin() + n);
	return top_results;
}

/*
int main() {
	document_indexer idx;
	idx.output();
	idx.removeStopWords();
	idx.output();
	system("pause");
	return 0;
}*/

std::ostream & operator<<(std::ostream & os, const document_indexer & right)
{
	os << "The document_indexer indexes multiple documents";
	return os;
}

void operator>>(document & d, document_indexer &idx)
{
	idx.documents.push_back(d);
}
