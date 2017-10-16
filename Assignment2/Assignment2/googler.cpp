#include "indexer.h"
#include <iostream>


int main() {
	indexer idx;

	cout << "Please enter a search query : ";
	string query;
	getline(cin, query);

	vector<query_result> result = idx.query(query);
	
	for (query_result qr : result) {
		cout << qr.found_document.name() << "  score: " << qr.score << endl;
	}

	system("pause");
	return 0;
}