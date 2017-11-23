#pragma once
#include "document.h"
#include "index_item.h"
#include <string>
#include <vector>
template<typename T>
class abstract_tokenizer
{
	/*! prints information about how the class should be used */
	friend std::ostream & operator<<(std::ostream & os, const abstract_tokenizer & right);

public:
	/*! splits a document into index_items and returns them as a vector */
	virtual std::vector<T> tokenize(const document & doc) = 0;

};


namespace tokenizer_tools {
	/*! returns a vector containing all the words (sanitized) from a given string */
	std::vector<std::string> tokenize_string(std::string & text);

	/*! removes punctuation and makes all the characters lower case */
	std::string sanitize(std::string &);
}