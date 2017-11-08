#include "indexer.h"
#include "abstract_tokenizer.h"
#include <sstream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename T, typename E>
indexer<T, E>::indexer<T, E>()
	: stopwords(STOPWORD_FILENAME.c_str())
{
}

//template<typename T, typename E>
//indexer<T, E>::~indexer()
//{
//	for (vector<int> * oc : occurences) {
//		delete oc;
//	}
//	this->occurences.clear();
//}

template<typename T, typename E>
unsigned int indexer<T, E>::size() const
{
	return 0;
}

template <typename T, typename E>
void indexer<T,E>::print_legend() const
{
    print_full_line();
    cout << "| " << std::left << setw(biggest_word_length) << "Dictionary" << " |";
    for (int i = 0; i<documents.size(); i++) {
        cout << " " + documents[i].name() + " |";
        cout << " " + documents[i].name() + "(weight) |";
    }
    cout << " df_t |";
    cout << endl;
    print_full_line();
}

const int dtf_size = 5;
const int wtd_size = 8;

template <typename T, typename E>
void indexer<T,E>::print_full_line() const
{
    for (int i = 0; i<biggest_word_length + 4; i++) {
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

template <typename T, typename E>
void indexer<T,E>::output() const
{
    print_legend();
    cout << std::showpoint;
    vector<int> totals(documents.size(), 0);
    int row = 0;
    for (pair<string, string> dict : this->dictionary) {
        cout << "| " << left << setw(biggest_word_length) << dict.second << " |";
        for (int i = 0; i < documents.size(); ++i) {
            cout << setw(documents[i].name().size() + 1) << right << this->occurences[i][row] << " |";
            cout << setw(documents[i].name().size() + 1 + wtd_size) << right << setprecision(2) << this->weights[i][row] << " |";
            totals[i] += this->occurences[i][row];
        }
        cout << setw(dtf_size) << right  << this->document_frequency[row] << " |";
        cout << endl;
        row++;
    }
    
    print_full_line();
    cout << "| " << left << setw(biggest_word_length) << "Totals" << " |";
    for (int i = 0; i < totals.size(); ++i) {
        cout << setw(documents[i].name().size() + 1) << right << totals[i] << " |";
        cout << string(documents[i].name().size() + wtd_size + 1, ' ') << " |";
    }
    cout << string(dtf_size, ' ') << " |";
    cout << endl;
    print_full_line();
    cout << endl;
}

template <typename T, typename E>
void indexer<T,E>::generateDictionary()
{
    //E t;
    for (T doc : this->documents) {
        vector<string> tokens = tokenizer_tools::tokenize_string(doc.content());
        for (string token : tokens) {
            this->dictionary.insert(pair<string, string>(token, token));
        }
    }


	int i = 0;
    for (pair<string, string> d : this->dictionary) {
		string token = d.first;
		if (token.length() > biggest_word_length) {
			biggest_word_length = token.length();
		}
		occurence_map.insert(pair<string, int>(token, i));
		++i;
    }
}

template <typename T, typename E>
void indexer<T,E>::remove_stop_words()
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

	occurence_map.clear();
	int i = 0;
	for (pair<string, string> d : this->dictionary) {
		string token = d.first;
		if (token.length() > biggest_word_length) {
			biggest_word_length = token.length();
		}
		occurence_map.insert(pair<string, int>(token, i));
		++i;
	}
    
    this->compute();
}

bool gtScore(const query_result & left, const query_result & right)
{
    return left.score > right.score;
}

template <typename T, typename E>
void indexer<T,E>::compute()
{
	/*for (vector<int> * oc : occurences) {
		delete oc;
	}*/
    this->occurences.clear();
    this->document_frequency = vector<int>(this->dictionary.size(), 0);
    this->weights.clear();
    
    for (T doc : documents) {
        vector<int>  occurence(this->dictionary.size(), 0);
        vector<bool> frequents(this->dictionary.size(), false);
        
        string word;
        istringstream iss(doc.content());
        
        while (iss >> word) {
            word = tokenizer_tools::sanitize(word);
            map<string, string>::iterator it = dictionary.find(word);
            //only add occurence if word is in the dictionary
			if (it != dictionary.end()) {
				int index = this->occurence_map[word];
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
			weight[j] = normalize(this->occurences[i][j], this->document_frequency[j]);
        }
        
        this->weights.push_back(weight);
    }
	int i = 8;
}

template <typename T, typename E>
double indexer<T,E>::normalize(int term_frequency, int document_frequency)
{
	return (term_frequency > 0) ? (1 + log10((double)term_frequency)) * log10((double)this->N / (double)document_frequency) : 0;
}

template <typename T, typename E>
double indexer<T,E>::score(string & query, int document_index)
{
	vector<string> query_tokens = tokenizer_tools::tokenize_string(query);
    vector<double> q(this->dictionary.size(), 0.0);
    vector<double> * d = &(this->weights[document_index]);
    
	for (string & token : query_tokens) {
        map<string, string>::iterator it = this->dictionary.find(token);
        //only add occurence if word is in the dictionary
        if (it != dictionary.end()) {
            //find the index of the word in the map
            int index = occurence_map[token];
            q[index] = this->weights[document_index][index];
        }
    }
    
    //double numerator = inner_product(q.begin(), q.end(), d.begin(), 0.0);
    //double denominator = sqrt(for_each(q.begin(), q.end(), 0.0, std::square_acc ));
    
    double cos_sim = this->cosine_similarity(q, *d);
    
    return cos_sim >= 0 ? cos_sim : 0;
}

template <typename T, typename E>
double indexer<T,E>::cosine_similarity(const vector<double> & q, const vector<double> & d)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
    for (unsigned int i = 0u; i < q.size(); ++i) {
        dot += q[i] * d[i];
        denom_a += q[i] * q[i];
        denom_b += d[i] * d[i];
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b));
}

template <typename T, typename E>
void operator>>(T & d, indexer<T, E> & idx)
{
    idx.documents.push_back(d);
}

template <typename T, typename E>
std::ostream & operator<<(std::ostream & os, const indexer<T,E> & idx)
{
    os << "Dictionary terms : " << idx.dictionary.size() << " Num. Documents: " << idx.size();
    return os;
}

template <typename T, typename E>
index_item * indexer<T,E>::operator[](int index) {
    return static_cast<index_item*>(&(this->documents[index]));
}
