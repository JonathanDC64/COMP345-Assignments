//
//  document_indexer.cpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "document_indexer.hpp"
#include "word_tokenizer.hpp"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>


std::ostream & operator<<(std::ostream & os, const document_indexer & right){
    os << "This class is used to index documents\n";
    return os;
}

std::vector<query_result> document_indexer::query(const std::string &query, int n) {
    std::vector<std::string> query_tokens = word_tokenizer::tokenizeString(query);
    std::vector<double> q;
    std::vector<double> d;
    std::vector<query_result> results;
    dmap::iterator it;
    for (int doc_index = 0; doc_index < this->size(); ++doc_index) {
        for (std::string word : query_tokens){
            it = this->dictionary.find(word);
            if(it != this->dictionary.end()){
                q.push_back(it->second[doc_index].weight);
                d.push_back(it->second[doc_index].weight);
            }
        }
        double cos = cosine_similarity(q, d, doc_index);
        results.push_back(query_result(*(this->index_items[doc_index]),cos));
        q.clear();
        d.clear();
    }
    std::sort(results.begin(), results.end(), bScore);

    if(this->size() < n)
        n = this->size();

    return std::vector<query_result>(results.cbegin(),results.cbegin()+n);
}

void document_indexer::generateIndexItems() {
    std::ifstream ifs(this->INDEX_FILE.c_str());
    std::string fileName;
    while(ifs >> fileName){
        document * d = new document(fileName);
        *d >> *this;
    }
    ifs.close();
    this->denom_double = std::vector<double>(this->size(),0.0);
    this->totals = std::vector<int>(this->size(),0);
}



void document_indexer::printTotals() const{
    generateTotals();
    const int WEIGHT_TAG = 10;
    printFullLine();
    int gapN = DictionaryLength - static_cast<int>(maxWordLength);
    if(gapN < 0) gapN = 0;
    std::cout << "| " << std::left << std::setw(static_cast<int>(maxWordLength + gapN)) << "Totals" << " |";
    for(int i = 0; i < this->size(); ++i){
        std::cout << " " << std::right << std::setw(static_cast<int>(index_items[i]->name().size())) << this->totals[i] << " |";
        std::cout << std::setw(static_cast<int>(index_items[i]->name().size() + 3) + WEIGHT_TAG) << "|";
    }
    std::cout << std::setw(6) << "|";
    std::cout << std::endl;
    printFullLine();
}

void document_indexer::printLegend() const{
    printFullLine();
    std::cout << "| " << std::left << std::setw(static_cast<int>(maxWordLength)) << "Dictionary" << " |";
    for(int i = 0; i < this->size(); ++i){
        std::cout << " " << index_items[i]->name() << " |";
        std::cout << " " << (index_items[i]->name()+" (weights)") << " |";
    }
    std::cout << " dtf |";
    std::cout << std::endl;
    printFullLine();
}

void document_indexer::printFullLine() const{
    const int WEIGHT_TAG = 10;
    for (int i = 0; i < ((DictionaryLength > maxWordLength)? DictionaryLength + 4 : maxWordLength + 4); ++i) {std::cout << "-";}
    for (int i = 0; i < this->size(); ++i){
        for (int j = 0; j < 2*(index_items[i]->name().size() + 3) + WEIGHT_TAG; ++j){std::cout << "-";}
    }
    std::cout << "------" << std::endl;
}

void document_indexer::generateTotals() const{
    std::fill(totals.begin(), totals.end(), 0);
    for(auto word : this->dictionary){
        for(auto doc : word.second){
            this->totals[doc.first]++;
        }
    }
}

void document_indexer::output() const{
    printLegend();
    int row = 0;
    int gapN = DictionaryLength - static_cast<int>(maxWordLength);
    if(gapN < 0) gapN = 0;
    for(auto word : dictionary){
        std::cout << "| " << std::left << std::setw(static_cast<int>(maxWordLength) + gapN) << word.first << " |";
        for(int i = 0; i < this->size(); ++i){
            bool found = false;
            auto it = word.second.find(i);
            if(it != word.second.end())
                found = true;
            std::cout << " " << std::right << std::setw(static_cast<int>(index_items[i]->name().size())) << ((found)?it->second.occurence : 0) << " |";
            std::cout << " " << std::fixed << std::setprecision(2) << std::setw(static_cast<int>(index_items[i]->name().size())+ 10) << ((found)?it->second.weight : 0) << " |";
        }
        std::cout << " " << std::setw(3) << word.second.size() << " |";
        ++row;
        std::cout << std::endl;
    }
    printTotals();
}

document_indexer::document_indexer()
:indexer::indexer()
{
    generateIndexItems();
    generateDictionary();
}

std::string document_indexer::getIndexFile() const { 
    return this->INDEX_FILE;
}




