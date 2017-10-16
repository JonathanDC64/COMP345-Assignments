#include "indexer.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <numeric>
#include <functional> 
#include <algorithm>


indexer::indexer()
	: stopwords(STOPWORD_FILENAME.c_str())
{
	std::ifstream fin(this->INDEX_FILENAME.c_str());
	std::string filename;

	while (fin >> filename) {
		document d(filename);
		d >> *this;
	}
	this->N = documents.size();
	this->generateDictionary();
	this->numOccurences();
}


indexer::~indexer()
{
}

unsigned int indexer::size() const
{
	return this->documents.size();
}

void indexer::print_legend() const
{
	printFullLine();
	cout << "| " << left << setw(biggestWordLength) << "Dictionary" << " |";
	for (int i = 0; i<documents.size(); i++) {
		cout << " " + documents[i].name() + " |";
		cout << " " + documents[i].name() + "(weight) |";
	} 
	cout << " df_t |";
	cout << endl;
	printFullLine();
}

const int dtf_size = 5;
const int wtd_size = 8;

void indexer::printFullLine() const
{
	for (int i = 0; i<biggestWordLength + 4; i++) {
		cout << "-";
	}
	for (int i = 0; i<documents.size(); i++) {
		cout << "-";
		for (int j = 0; j< ((documents[i].name().size() + 2) * 2) + wtd_size; j++) {
			cout << "-";
		}

		cout << "-";
	} 

	for (int i = 0; i < dtf_size; i++) {
		cout << "-";
	}
	cout << "--";
	cout << endl;
}

void indexer::output() const
{
	print_legend();
	cout << showpoint;
	vector<int> totals(documents.size(), 0);
	int row = 0;
	for (pair<string, string> dict : this->dictionary) {
		cout << "| " << left << setw(biggestWordLength) << dict.second << " |";
		for (int i = 0; i < documents.size(); ++i) {
			cout << setw(documents[i].name().size() + 1) << right << this->occurences[i][row] << " |";
			cout << setw(documents[i].name().size() + 1 + wtd_size) << right << setprecision(2) << this->weights[i][row] << " |";
			totals[i] += this->occurences[i][row];
		}
		cout << setw(dtf_size) << right  << this->document_frequency[row] << " |";
		cout << endl;
		row++;
	}

	printFullLine();
	cout << "| " << left << setw(biggestWordLength) << "Totals" << " |";
	for (int i = 0; i < totals.size(); ++i) {
		cout << setw(documents[i].name().size() + 1) << right << totals[i] << " |";
		cout << string(documents[i].name().size() + wtd_size + 1, ' ') << " |";
	}
	cout << string(dtf_size, ' ') << " |";
	cout << endl;
	printFullLine();
	cout << endl;
}

void indexer::generateDictionary()
{
	tokenizer t;
	for (document doc : this->documents) {
		std::vector<std::string> tokens = t.tokenize(doc.name());
		for (std::string token : tokens) {
			this->dictionary.insert(pair<string, string>(token, token));
		}
	}

	for (pair<string, string> d : this->dictionary) {
		string token = d.first;
		if (token.length() > biggestWordLength) {
			biggestWordLength = token.length();
		}
	}
}

void indexer::removeStopWords()
{
	vector<string> removal_list;
	for (pair<string, string> d : this->dictionary) {
		string word = d.first;

		if (stopwords(word)) {
			removal_list.push_back(word);//dictionary.erase(word);
		}
	}

	for (string word : removal_list) {
		this->dictionary.erase(word);
	}

	this->numOccurences();
}

vector<query_result> indexer::query(string search, int n)
{
	return vector<query_result>();
}

void indexer::numOccurences()
{
	this->occurences.clear();
	this->document_frequency = vector<int>(this->dictionary.size(), 0);
	this->weights.clear();
	
	for (document doc : documents) {
		vector<int> occurence(this->dictionary.size(), 0);
		vector<bool> frequents(this->dictionary.size(), false);

		string word;
		istringstream iss(doc.content());

		while (iss >> word) {
			word = tokenizer::sanitize(word);
			map<string, string>::iterator it = dictionary.find(word);
			//only add occurence if word is in the dictionary
			if (it != dictionary.end()) {
				//find the index of the word in the map
				int index = distance(this->dictionary.begin(), it);
				occurence[index]++;
				if (!frequents[index]) {
					frequents[index] = true;
					this->document_frequency[index]++;
				}
			}
		}
		this->occurences.push_back(occurence);
	}

	for (int i = 0; i < this->documents.size(); i++) {
		vector<double> weight(this->dictionary.size(), 0.0);
		//calculate weight
		for (int j = 0; j < this->dictionary.size(); j++) {
			weight[j] = indexer::normalize(this->occurences[i][j], this->document_frequency[j]);
		}

		this->weights.push_back(weight);
	}

}

double indexer::normalize(int term_frequency, int document_frequency)
{
	return (term_frequency > 0) ? ( 1 + log10((double)term_frequency)) * log10((double)this->N / (double)document_frequency) : 0;
}

double indexer::score(string & query, int document_index)
{
	vector<string> query_tokens = tokenizer::tokenize_string(query);
	vector<double> q(this->dictionary.size(), 0.0);
	vector<double> d = this->weights[document_index];

	for (string token : query_tokens) {
		map<string, string>::iterator it = this->dictionary.find(token);
		//only add occurence if word is in the dictionary
		if (it != dictionary.end()) {
			//find the index of the word in the map
			int index = distance(this->dictionary.begin(), it);
			q[index] = this->weights[document_index][index];
		}
	}
	
	//double numerator = inner_product(q.begin(), q.end(), d.begin(), 0.0);
	//double denominator = sqrt(for_each(q.begin(), q.end(), 0.0, std::square_acc ));

	double cos_sim = this->cosine_similarity(q, d);

	return cos_sim;
}

double indexer::cosine_similarity(const vector<double> & q, const vector<double> & d)
{
	double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
	for (unsigned int i = 0u; i < q.size(); ++i) {
		dot += q[i] * d[i];
		denom_a += q[i] * q[i];
		denom_b += d[i] * d[i];
	}
	return dot / (sqrt(denom_a) * sqrt(denom_b));
}


void operator>>(document & d, indexer & idx)
{
	idx.documents.push_back(d);
}

int main() {
	indexer idx;
	idx.output();
	idx.removeStopWords();
	idx.output();
	system("pause");
	return 0;
}