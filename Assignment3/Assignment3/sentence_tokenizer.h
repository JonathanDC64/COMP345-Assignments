#pragma once
#include "abstract_tokenizer.h"
#include "sentence.h"
#include <map>
class sentence_tokenizer : public abstract_tokenizer<sentence>
{
public:
	sentence_tokenizer();
	virtual std::vector<sentence> tokenize(const document & doc) override;

private:

	const std::string ABBREVIATION_FILE = "abbreviations.txt";

	std::string::size_type find_punct(std::string & text, int start);
	std::map<std::string,std::string> abbreviations;
	bool isAbbreviation(std::string ab);
};

