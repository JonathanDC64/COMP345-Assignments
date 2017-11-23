//
//  indexer.cpp
//  project
//
//  Created by justin baron on 2017-11-09.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "indexer.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include "word_tokenizer.hpp"

indexer::indexer()
:maxWordLength(0),stop_words(stopword())
{
}


void indexer::generateDictionary() {
    std::string word;
    dmap::iterator it;
    std::map<int,data_item>::iterator it2;
    int doc_count = 0;
    for(index_item * ii : this->index_items){
        std::stringstream ss(ii->content());
        while(ss >> word){
            word = word_tokenizer::sanitize(word);
            if(word.length() > maxWordLength)
                maxWordLength = word.length();
            it = dictionary.find(word);
            if(it != dictionary.end()){
                it2 = it->second.find(doc_count);
                if(it2 != it->second.end()){
                    it->second[doc_count].occurence++;
                }
                else{
                    it->second.insert(std::make_pair(doc_count, data_item()));
                }
            }
            else{
                dictionary.insert(std::make_pair(word, std::map<int,data_item>()));
                dictionary.at(word).insert(std::make_pair(doc_count, data_item()));
            }
        }
        ++doc_count;
    }
    normalize();
}

void indexer::removeStopwords() {
    dmap::iterator it;
    std::vector<std::string> words_to_remove;
    for(auto word : dictionary){
        if(stop_words(word.first)){
            words_to_remove.push_back(word.first);
        }
    }
    for(std::string word : words_to_remove){
        this->dictionary.erase(word);
    }
}

int indexer::size() const {
    return static_cast<int>(this->index_items.size());
}

void indexer::normalize() {
    dmap::iterator it;
    std::map<int,data_item>::iterator it2;
    for (it = dictionary.begin(); it != this->dictionary.end(); ++it) {
        for(it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            double d = (1.0 + log10(it2->second.occurence)) * log10((double)this->size()/it->second.size());
            it2->second.weight = d;
            this->denom_double[it2->first] += std::pow(d, 2);
        }
    }
}

double indexer::cosine_similarity(const std::vector<double> & q, const std::vector<double> & d, const int doc_index)
{
    double dot = 0.0, denom_a = 0.0;
    for (unsigned int i = 0; i < q.size(); ++i) {
        dot += q[i] * d[i];
        denom_a += q[i] * q[i];
        //denom_b += d[i] * d[i];
    }
    double result = dot / (sqrt(denom_a) * sqrt(this->denom_double[doc_index]));
    return (result >= 0)? result : 0.0;
}

index_item *indexer::operator[](int index) {
    return index_items[index];
}


const index_item *indexer::operator[](int index) const {
    return index_items[index];
}

indexer::~indexer()
{ 

}


void operator>>(index_item & doc, indexer & idx){
    idx.index_items.push_back(&doc);
}

std::ostream & operator<<(std::ostream & os, const indexer & right){
    os << "dictionary size : " << right.dictionary.size() << "\nindex_items size : "
        << right.size() << std::endl;
    return os;
}














