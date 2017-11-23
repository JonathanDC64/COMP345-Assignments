//
//  query_result.cpp
//  project
//
//  Created by justin baron on 2017-11-10.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "query_result.hpp"
#include <fstream>

bool bScore(const query_result & left, const query_result & right){
    return left.getScore() > right.getScore();
}

double query_result::getScore() const{
    return score;
}

query_result::query_result(index_item &item, double score) {
    this->item = &item;
    this->score = score;
}

const index_item *query_result::getItem() const { 
    return this->item;
}

std::ostream & operator<<(std::ostream & os, const query_result & right){
  
    return os;
}


