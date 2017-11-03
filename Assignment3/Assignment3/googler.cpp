#include "document_indexer.h"
#include "query_result.h"
#include "sentence_indexer.h"
#include <iostream>
#include <iomanip>


using namespace std;

//int main() {
	/*sentence_indexer idx;
	idx.output();

	system("pause");
	return 0;*/
//}


int main() {
	document_indexer idx;
	bool again = false;
	cout << showpoint;
	do {
		cout << "Please enter a search query : ";
		string query;
		getline(cin, query);

		const int n = 10;
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

		cout << endl;
		cout << "Perform another search?: (y/n) : ";

		string answer;
		cin >> answer;
		again = answer == "y" ? true : false;

		//removes any '\n' left in the cin buffer
		cin.ignore();

		cout << endl;
	} while (again);

	system("pause");
	return 0;
}
 
