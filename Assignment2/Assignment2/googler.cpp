#include "indexer.h"
#include <iostream>
#include <iomanip>


int main() {
	indexer idx;
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
			setw(15) << left << "Doc. Name:" <<
			setw(10) << right << "Score:" <<
			endl;

		int pos = 1;
		for (query_result result : results) {
			

			cout << 
				setw(15) << left << 
				(to_string(pos) + ": " + result.found_document.name()) << 
				"|" <<
				setw(10) << right << setprecision(4) <<
				result.score <<
				endl;

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



	return 0;
}