#include "word_tokenizer.h"
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
		word = sanitize(word);
		tokens.push_back(word);
	}

	return tokens;
}

std::vector<std::string> word_tokenizer::tokenize_string(std::string & text)
{
	std::vector<std::string> tokens;
	std::string word;
	std::istringstream iss(text);

	while (iss >> word) {
		word = sanitize(word);
		tokens.push_back(word);
	}

	return tokens;
}

//Makes a word lower case and removes punctuation
std::string word_tokenizer::sanitize(std::string & text) {
    const unsigned char LOWERCASE_OFFSET = 'a' - 'A';
	for (char &c : text) {
		//make lowercase
		if (c >= 'A' && c <= 'Z') {
			c += LOWERCASE_OFFSET;
		}
	}

	//remove punctuation
	text.erase(std::remove_if(text.begin(), text.end(), ::ispunct), text.end());
	return text;
}

std::ostream & operator<<(std::ostream & os, const word_tokenizer & tk)
{
	os << "Splits contents of string or file into lowercase tokens";
	return os;
}
