#pragma once
#include "abstract_tokenizer.h"
#include "sentence.h"
#include <map>
class sentence_tokenizer : public abstract_tokenizer<sentence>
{
public:
	
	/*! prints information about the class*/
	friend std::ostream & operator<<(std::ostream & os, const sentence_tokenizer & right);

	/*! Default constructor */
	sentence_tokenizer();

	/*! splits a document into sentences and returns them as a vector */
	virtual std::vector<sentence> tokenize(const document & doc) override;

private:

	const std::string ABBREVIATION_FILE = "abbreviations.txt";

	std::string::size_type find_punct(std::string & text, int start);
	std::map<std::string,std::string> abbreviations;
	bool isAbbreviation(std::string ab);
};

