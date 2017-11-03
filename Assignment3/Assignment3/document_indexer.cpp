#include "document_indexer.h"

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


/*
int main() {
	document_indexer idx;
	idx.output();
	idx.removeStopWords();
	idx.output();
	system("pause");
	return 0;
}*/

void operator>>(document & d, document_indexer &idx)
{
	idx.documents.push_back(d);
}
