//
//  index_exception.hpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef index_exception_hpp
#define index_exception_hpp
#include <string>
#include <iostream>
#include <exception>

class index_exception : public std::exception{
    
    friend std::ostream & operator<<(std::ostream & os, const index_exception & right);
public:
    
    /*! constructs an index_exception with a message describing the exception */
    explicit index_exception(const std::string & message);
    
    /*! returns the message */
    virtual const char * what() const throw() override;
private:
    std::string msg;
};

#endif /* index_exception_hpp */
