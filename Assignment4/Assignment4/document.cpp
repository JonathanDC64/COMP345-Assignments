//
//  document.cpp
//  project
//
//  Created by justin baron on 2017-11-10.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "document.hpp"
#include <fstream>
#include <iostream>


unsigned int document::size() const{
    return this->content().size();
}

document::document(std::string file_name)
:index_item::index_item()
{
    this->setName(file_name);
    std::string line;
    std::ifstream ifs(file_name.c_str());
    while(std::getline(ifs, line)){
        this->setContent(this->content() + line + "\n");
    }
}

std::ostream & operator<<(std::ostream & os, const document & doc)
{
    os << "Name: " << doc.name() << " Size: " << doc.size();
    return os;
}

document::document()
:index_item::index_item()
{
    
}
