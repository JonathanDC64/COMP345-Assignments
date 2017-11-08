#include "sentence_indexer.h"
#include "query_result.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const string QUERY_FILE = "index_queries.txt";

int main() {
	cout << "Loading Documents..." << endl;
	sentence_indexer idx;
	idx.remove_stop_words();
	bool again = false;
	cout << showpoint;

	string filename;

	ifstream qfs(QUERY_FILE.c_str());

	//do {
	while (qfs >> filename) {
		//cout << "Please enter a search query : ";
		string query;
		string line;
		ifstream dfs(filename.c_str());

		while (getline(dfs, line)) {
			query += line + " ";
		}
		
		dfs.close();

		cout << endl;
		cout << "Processing Query... :" << endl;
		cout << query << endl;
		cout << endl;

		const int n = 500;
		vector<query_result> results = idx.query(query, n);

		cout << endl;
		cout << "Ranked search Results: " << endl;
		cout << endl;
		cout <<
			setw(15) << left << "Doc. Name" <<
			setw(13) << right << "Score" <<
			endl;

		int pos = 1;
		for (query_result result : results) {

			cout << to_string(pos) + ": ";
			cout << result;

			pos++;
		}

		cout << "Essay:" << endl;
		for (query_result result : results) {
			cout << result.found_document->content() << endl << endl;
		}

		cout << endl;
	}
	//} while (again);
	qfs.close();
	system("pause");
	return 0;
}