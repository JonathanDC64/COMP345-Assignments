//
//  sentence.cpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "sentence.hpp"
#include <sstream>

std::ostream & operator<<(std::ostream & os, const sentence & right){
    os << "document name: " << right.name() << "sentence content: " << right.content() << std::endl;
    return os;
}

unsigned int sentence::getPos() const { 
    return this->pos;
}


unsigned int sentence::size() const { 
    std::stringstream ss(this->content());
    std::string word;
    unsigned int count = 0;
    while(ss >> word) ++count;
    return count;
}

sentence::sentence(const std::string &content, const std::string & name, unsigned int pos)
:index_item::index_item()
{
    this->setName(name);
    this->setContent(content);
}

