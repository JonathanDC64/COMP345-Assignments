//
//  index_exception.cpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "index_exception.hpp"


std::ostream & operator<<(std::ostream & os, const index_exception & right){
    os << right.what() << std::endl;
    return os;
}

index_exception::index_exception(const std::string &message)
:msg(message)
{
    
}

const char *index_exception::what() const throw() { 
    return this->msg.c_str();
}

