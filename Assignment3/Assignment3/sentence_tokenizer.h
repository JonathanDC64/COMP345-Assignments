#pragma once
#include "abstract_tokenizer.h"
#include "sentence.h"
class sentence_tokenizer : public abstract_tokenizer<sentence>
{
public:
	sentence_tokenizer();
	virtual std::vector<sentence> tokenize(const document & doc) override;

private:
	std::string::size_type find_punct(const std::string & text);
};

