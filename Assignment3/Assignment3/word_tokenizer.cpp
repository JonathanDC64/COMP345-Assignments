#include "word_tokenizer.h"
#include "abstract_tokenizer.h"
#include <fstream>
#include <algorithm>
#include <sstream>


word_tokenizer::word_tokenizer()
{
}


word_tokenizer::~word_tokenizer()
{
}

std::vector<std::string> word_tokenizer::tokenize(const document & doc) {
    
    std::vector<std::string> tokens;
    std::string word;
    std::istringstream iss(doc.content());
    
    while (iss >> word) {
        word = tokenizer_tools::sanitize(word);
        tokens.push_back(word);
    }
    
    return tokens;
}


std::ostream & operator<<(std::ostream & os, const word_tokenizer & tk)
{
	os << "Splits contents of string or file into lowercase tokens";
	return os;
}
