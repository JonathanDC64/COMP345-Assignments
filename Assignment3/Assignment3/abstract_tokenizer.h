#pragma once
#include "document.h"
#include <string>
#include <vector>
template<typename T>
class abstract_tokenizer
{
public:
	virtual std::vector<T> tokenize(const document & doc) = 0;
    
    /*! returns a vector containing all the words (sanitized) from a given string */
    static std::vector<std::string> tokenize_string(std::string & text);
    
    /*! removes punctuation and makes all the characters lower case */
    static std::string sanitize(std::string &);
};
