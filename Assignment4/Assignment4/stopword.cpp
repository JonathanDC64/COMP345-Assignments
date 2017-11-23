//
//  stopwords.cpp
//  project
//
//  Created by justin baron on 2017-11-16.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "stopword.hpp"
#include <fstream>

std::ostream & operator<<(std::ostream & os, const stopword & right){
    os << "The stopword class holds the set of stopwords";
    return os;
}

stopword::stopword(){
    std::ifstream ifs(stopword::STOP_WORDS.c_str());
    std::string word;
    while(ifs >> word){
        this->stopwords.insert(word);
    }
    ifs.close();
}

bool stopword::operator()(std::string word){
    return this->stopwords.find(word)!=this->stopwords.end();
}
