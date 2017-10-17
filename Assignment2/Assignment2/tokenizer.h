#pragma once
#include <vector>
#include <string>

class tokenizer
{
	/*! prints the the use of the tokenizer class */
	friend std::ostream& operator<<(std::ostream& os, const tokenizer & tk);
public:

	/*! Default constructor */
	tokenizer();

	/*! Destructor */
	~tokenizer();

	/*! returns a vector containing all the words (sanitized) from a given file */
	static std::vector<std::string> tokenize(const std::string & filename);

	/*! removes punctuation and makes all the characters lower case */
	static std::string sanitize(std::string &);

	/*! returns a vector containing all the words (sanitized) from a given string */
	static std::vector<std::string> tokenize_string(std::string & text);
};

