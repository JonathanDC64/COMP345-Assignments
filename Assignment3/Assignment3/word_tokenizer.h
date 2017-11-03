#pragma once
#include "abstract_tokenizer.h"
#include <vector>
#include <string>


class word_tokenizer : public abstract_tokenizer<std::string>
{
	/*! prints the the use of the tokenizer class */
	friend std::ostream& operator<<(std::ostream& os, const word_tokenizer & tk);
public:

	/*! Default constructor */
	word_tokenizer();

	/*! Destructor */
	~word_tokenizer();

	/*! returns a vector containing all the words (sanitized) from a given file */
	virtual std::vector<std::string> tokenize(const document & filename) override;

};

