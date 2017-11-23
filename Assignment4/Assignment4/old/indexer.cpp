#include "indexer.h"
#include "abstract_tokenizer.h"
#include <sstream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

indexer::indexer()
	: stopwords(STOPWORD_FILENAME.c_str())
{

}

unsigned int indexer::size() const
{
	return documents.size();
}


void indexer::generateDictionary()
{
	int i = 0;
    for (index_item * doc : this->documents) {
        vector<string> tokens = tokenizer_tools::tokenize_string(doc->content());
        for (string token : tokens) {
			dmap::iterator it = dictionary.find(token);
			if (it != dictionary.end()) {
				map<int, term_info>::iterator t = it->second.find(i);
				if (t != it->second.end()) {
					it->second[i].occurence++;
				}
				else {
					it->second.insert(make_pair(i, term_info(1,0)));
				}
			}
			else {
				this->dictionary.insert(make_pair(token, map<int, term_info>()));
			}

        }
		i++;
    }

	i = 0;
	for (pair<string, map<int, term_info>> dict : dictionary) {
		occurence_map.insert(make_pair(dict.first, i));
		i++;
	}
}


void indexer::remove_stop_words()
{
	for (dmap::iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
        string word = it->first;
        if (stopwords(word)) {
            dictionary.erase(it++);
        }
    }

	occurence_map.clear();
	int i = 0;
	for (pair<string, map<int, term_info>> dict : dictionary) {
		occurence_map.insert(make_pair(dict.first, i));
		i++;
	}
    
    this->compute();
}

bool gtScore(const query_result & left, const query_result & right)
{
    return left.score > right.score;
}


void indexer::compute()
{
	denoms = vector<double>(documents.size(), 0.0);
	for (dmap::iterator dict = dictionary.begin(); dict != dictionary.end(); ++dict) {

		for (map<int, term_info>::iterator info = dict->second.begin(); info != dict->second.end(); ++info) {
			double weight = normalize(info->second.occurence, dict->second.size());
			info->second.weight = weight;
			denoms[info->first] += weight * weight;
		}
	}

	for (vector<double>::iterator it = denoms.begin(); it != denoms.end(); ++it) {
		*it = sqrt(*it);
	}
}


double indexer::normalize(int term_frequency, int document_frequency)
{
	return (term_frequency > 0) ? (1 + log10((double)term_frequency)) * log10((double)this->N / (double)document_frequency) : 0;
}


double indexer::score(string & query, int document_index)
{
	vector<string> query_tokens = tokenizer_tools::tokenize_string(query);
    vector<double> q(this->dictionary.size(), 0.0);
    
	for (string & token : query_tokens) {
        dmap::iterator it = this->dictionary.find(token);
        //only add occurence if word is in the dictionary
        if (it != dictionary.end()) {
            //find the index of the word in the map
            int index = occurence_map[token];
			double weight = it->second[document_index].weight;
			q[index] = weight;
        }
    }
    
    double cos_sim = this->cosine_similarity(q, document_index);
    
    return cos_sim >= 0 ? cos_sim : 0;
}


double indexer::cosine_similarity(const vector<double> & q, int document_index)
{
    double dot = 0.0, denom_a = 0.0, denom_b = denoms[document_index];
    for (unsigned int i = 0u; i < q.size(); ++i) {
        dot += q[i] * q[i];
        denom_a += q[i] * q[i];
    }
    return dot / (sqrt(denom_a) * denom_b);
}



void operator>>(index_item & d, indexer & idx)
{
    idx.documents.push_back(&d);
}


std::ostream & operator<<(std::ostream & os, const indexer & idx)
{
    os << "Dictionary terms : " << idx.dictionary.size() << " Num. Documents: " << idx.size();
    return os;
}


index_item * indexer::operator[](int index) {
    return this->documents[index];
}
