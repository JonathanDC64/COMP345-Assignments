#include "sentence_tokenizer.h"
#include "document.h"
#include<fstream>


sentence_tokenizer::sentence_tokenizer()
{
}

std::vector<sentence> sentence_tokenizer::tokenize(const document & doc)
{
	std::vector<sentence> tokens;

	std::string::size_type pos = 0;
	std::string::size_type endPos = 0;
	std::string::size_type size = doc.content().size();

	while (pos <= size) {
		endPos = find_punct(doc.content().substr(pos)) + 1;
		tokens.push_back(sentence(doc, pos, endPos));
		pos = endPos;
	}

	return tokens;
}

std::string::size_type sentence_tokenizer::find_punct(const std::string & text)
{
	for (std::string::size_type i = 0; i < text.size(); i++) {
		if (text[i] == '.' || text[i] == '!' || text[i] == '?')
			return i;
	}
	return std::string::npos;
}
