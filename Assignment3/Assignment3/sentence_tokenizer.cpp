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
		//need to pass full string and index
		endPos = find_punct(doc.content(), pos) + 1;
		tokens.push_back(sentence(doc, pos, endPos));
		pos = endPos;
	}

	return tokens;
}

std::string::size_type sentence_tokenizer::find_punct(const std::string & text, int start)
{
	for (std::string::size_type i = start; i < text.size(); i++) {
		if (text[i] == '.' || text[i] == '!' || text[i] == '?')
			return i;
	}
	return text.size();//std::string::npos;
}
