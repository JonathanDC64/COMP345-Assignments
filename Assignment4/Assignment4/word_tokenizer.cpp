//
//  word_tokenizer.cpp
//  project
//
//  Created by justin baron on 2017-11-10.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "word_tokenizer.hpp"
#include <sstream>
#include <algorithm>


std::ostream & operator<<(std::ostream & os, const word_tokenizer & right){
    os << "this class is used to tokenize documents into word tokens\n";
    return os;
}

std::vector<std::string> word_tokenizer::tokenize(const document & doc) const{
    std::vector<std::string> tokens;
    std::stringstream ss(doc.content());
    std::string word;
    while(ss >> word){
        word = sanitize(word);
        tokens.push_back(word);
    }
    return tokens;
}

std::string word_tokenizer::sanitize(std::string word){
    word.erase(std::remove_if(word.begin (), word.end (), ::ispunct), word.end());
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

std::vector<std::string> word_tokenizer::tokenizeString(const std::string s) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string word;
    while(ss >> word){
        word = sanitize(word);
        tokens.push_back(word);
    }
    return tokens;
}




