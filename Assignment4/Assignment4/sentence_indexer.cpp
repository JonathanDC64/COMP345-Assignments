//
//  sentence_indexer.cpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "sentence_indexer.hpp"
#include "sentence_tokenizer.hpp"
#include "word_tokenizer.hpp"
#include <fstream>
#include <algorithm>


std::set<std::string> sentence_indexer::abbreviations;


std::ostream & operator<<(std::ostream & os, const sentence_indexer & right){
    os << "This class is used to index sentences from multiple documents\n";
    return os;
}

void sentence_indexer::generateIndexItems() {
    std::ifstream ifs(this->INDEX_FILE.c_str());
    std::string fileName;
    sentence_tokenizer st;
    while(ifs >> fileName){
        document d(fileName);
        std::vector<sentence> sentences = st.tokenize(d);
        for(sentence s : sentences){
            s = sentence_tokenizer::sanitize(s);
            sentence * sent = new sentence(s.content(),s.name(),s.getPos());
            *sent >> *this;
        }
    }
   this->denom_double = std::vector<double>(this->size(),0.0);
}

bool gtScoreGrouped(const query_result & left, const query_result & right)
{
    const sentence * ls = dynamic_cast<const sentence*>(left.item);
    const sentence * rs = dynamic_cast<const sentence*>(right.item);
    if (ls->name() != rs->name()) {
        return ls->name() < rs->name();
    }
    else {
        return ls->getPos() < rs->getPos();
    }
}

std::vector<query_result> sentence_indexer::query(const std::string &query, int n) {
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
    
    std::sort(results.begin(),results.end(),bScore);
    
    std::vector<query_result> top_results;
    int totalWords = 0;
    
    // Only get sentences up to (n) words
    for (query_result qr : results) {
        totalWords += qr.item->size();
        if (totalWords > n) {
            break;
        }
        top_results.push_back(qr);
    }
    
    //Group sentences by their index_items and sentence position
    sort(top_results.begin(), top_results.end(), gtScoreGrouped);
    
    return top_results;
}


sentence_indexer::sentence_indexer()
:indexer::indexer()
{
    generateAbbreviations();
    generateQueries();
    generateIndexItems();
    generateDictionary();
}

void sentence_indexer::generateAbbreviations() { 
    std::ifstream ifs(sentence_indexer::ABBREVITATIONS_FILE.c_str());
    std::string abbreviation;
    while(ifs >> abbreviation){
        this->abbreviations.insert(abbreviation);
    }
    ifs.close();
}

std::string sentence_indexer::getIndexFile() const { 
    return this->INDEX_FILE;
}

void sentence_indexer::generateQueries() { 
    std::ifstream ifs(this->QUERY_FILES.c_str());
    std::string file;
    while(ifs >> file){
        std::string query = "";
        std::ifstream ifs2(file.c_str());
        std::string line;
        while(getline(ifs2, line)){
            query += (line + "\n");
        }
        this->queries.push_back(query);
    }
    ifs.close();
}




