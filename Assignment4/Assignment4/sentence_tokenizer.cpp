//
//  sentence_tokenizer.cpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "sentence_tokenizer.hpp"
#include "sentence_indexer.hpp"
#include <sstream>


std::ostream & operator<<(std::ostream & os, const sentence_tokenizer & right){
    os << "this class is used to tokenize documents into sentences\n";
    return os;
}

std::vector<sentence> sentence_tokenizer::tokenize(const document &doc) const {
    std::vector<sentence> sentences;
    std::string content = doc.content();
    unsigned int pos = 0;
    for(int i = 0; i < content.size(); ++i){
        if(content[i] == '.'){
            std::string isAbbrev = "";
            int index = i - 1;
            while(index > pos && (content[index] != ' ' && content[index] != '.')){
                --index;
            }
            while(index != i - 1){
                ++index;
                isAbbrev += content[index];
            }
            std::set<std::string>::iterator it = sentence_indexer::abbreviations.find(isAbbrev);
            if(it != sentence_indexer::abbreviations.end()){
                // is abbrev
                continue;
            }
            std::string sent = content.substr(pos,i-pos + 1);
            if(sent[0] == '\'' && sent[1] == '\''){
                sent += "''";
            }
            sentence s(sent,doc.name(),pos);
            sentences.push_back(s);
            pos = i + 1;
        }
       
    }
    return sentences;
}

sentence sentence_tokenizer::sanitize(sentence &sent) { 
    std::stringstream ss(sent.content());
    std::string word;
    std::string newSent = "";
    while(ss >> word){
        newSent += word + " ";
    }
    return sentence(newSent,sent.name(),sent.getPos());
}

