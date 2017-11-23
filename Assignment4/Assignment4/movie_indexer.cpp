//
//  movie_indexer.cpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "movie_indexer.hpp"
#include "movie.hpp"
#include "word_tokenizer.hpp"
#include "index_exception.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>


std::ostream & operator<<(std::ostream & os, const movie_indexer & right){
    os << "This class is used to index movies\n";
    return os;
}

movie_indexer::movie_indexer()
:indexer::indexer()
{
    generateIndexItems();
    generateDictionary();
}

void movie_indexer::generateIndexItems() {
    std::ifstream ifs(this->MOVIE_METADATA.c_str());
    std::map<std::string,std::string>::iterator it;
    std::string id;
    std::string name;
    std::string date;
    std::string code;
    std::string word;
    std::string garbage;

    while(std::getline(ifs, id, '\t')){
        if(!(id < "999999999" || id > "00000")){
            continue;
        }
        std::getline(ifs, code, '\t');
        std::getline(ifs,name,'\t');
        std::getline(ifs,date,'\t');
        std::getline(ifs, garbage);
        name = word_tokenizer::sanitize(name);
        
        movie * mv = new movie(id,name,date,"");
        this->plot.insert(std::make_pair(id, mv));
        *mv >> *this;
    }
    ifs.close();
    this->denom_double = std::vector<double>(this->size(),0.0);
}



std::vector<query_result> movie_indexer::query(const std::string & qu, int n) {
    std::string query = "";
    for(index_item * ii: index_items){
        if(ii->name() == qu){
            query = qu;
        }
    }
    if(query == ""){
        throw index_exception("The movie was not found");
    }
    std::vector<std::string> query_tokens = word_tokenizer::tokenizeString(query);
    std::vector<double> q;
    std::vector<double> d;
    std::vector<query_result> results;
    dmap::iterator it;
    for (int doc_index = 0; doc_index < this->size(); ++doc_index) {
        if(this->index_items[doc_index]->content() == ""){
            continue;
        }
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
    return std::vector<query_result>(results.cbegin(),results.cbegin()+n);
}

std::string movie_indexer::getIndexFile() const { 
    return this->INDEX_FILE;
}


bool movie_indexer::isDate(const std::string &date) const { 
    std::string s = date.substr(0,1);
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void movie_indexer::generateDictionary() {
    std::ifstream ifs(FILE_PLOT.c_str());
    std::string word;
    std::string line;
    std::string id;
    
    int doc_count = 0;
    dmap::iterator it;
    std::map<int,data_item>::iterator it2;
    while(std::getline(ifs, line)){
        std::string content = "";
        std::stringstream ss(line);
        ss >> id;
        while(ss >> word){
            content += word + " ";
            word = word_tokenizer::sanitize(word);
            if(stop_words(word)){
                continue;
            }
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
        std::map<std::string, movie*>::iterator it3;
        it3 = this->plot.find(id);
        if (it3 != this->plot.end()){
            it3->second->setContent(content);
        }
        else{
            
        }
        word = word_tokenizer::sanitize(word);

        doc_count++;
    }
    
    ifs.close();
    normalize();
}






