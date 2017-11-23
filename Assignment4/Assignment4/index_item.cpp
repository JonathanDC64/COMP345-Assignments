//
//  index_item.cpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "index_item.hpp"

std::ostream & operator<<(std::ostream & os, const index_item & right){
    os << "file name: " << right.file_name << std::endl;
    os << "content: " << right.index_item_content << std::endl;
    return os;
}

std::string index_item::content() const{
    return this->index_item_content;
}


std::string index_item::name() const{
    return this->file_name;
}

void index_item::setContent(const std::string &content) {
    this->index_item_content = content;
}

void index_item::setName(const std::string &name) { 
    this->file_name = name;
}

index_item::index_item() { 
    this->file_name = "";
    this->index_item_content = "";
}



