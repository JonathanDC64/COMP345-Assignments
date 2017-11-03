#include "document_indexer.h"

using namespace std;

document_indexer::document_indexer()
: indexer::indexer()
{
    
}

void document_indexer::initialize()
{
    ifstream fin(this->INDEX_FILENAME.c_str());
    string filename;
    
    while (fin >> filename) {
        document d(filename);
        d >> *this;
    }
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
