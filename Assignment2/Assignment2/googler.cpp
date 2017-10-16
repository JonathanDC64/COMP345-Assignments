#include "indexer.h"
#include <iostream>


int main() {
	indexer idx;


	cout << "Please enter a search query : ";
	string query;
	getline(cin, query);

	vector<query_result> result = idx.query(query);

	return 0;
}