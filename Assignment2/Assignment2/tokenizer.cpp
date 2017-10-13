#include "tokenizer.h"
#include <fstream>
#include <algorithm>



tokenizer::tokenizer()
{
}


tokenizer::~tokenizer()
{
}

std::vector<std::string> tokenizer::tokenize(const std::string & document) {

	std::vector<std::string> tokens;
	std::string word;
	std::ifstream fin(document.c_str());

	while (fin >> word) {
		word = sanitize(word);
		tokens.push_back(word);
	}
	fin.close();

	return tokens;
}

//Makes a word lower case and removes punctuation
std::string tokenizer::sanitize(std::string & text) {
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
