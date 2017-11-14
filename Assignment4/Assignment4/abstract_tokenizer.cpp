#include "abstract_tokenizer.h"
#include <sstream>
#include <algorithm>


//Makes a word lower case and removes punctuation
std::string tokenizer_tools::sanitize(std::string & text) {
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    
    //remove punctuation
    text.erase(std::remove_if(text.begin(), text.end(), ::ispunct), text.end());
    return text;
}

std::vector<std::string> tokenizer_tools::tokenize_string(std::string & text)
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
template<typename T>
std::ostream & operator<<(std::ostream & os, const abstract_tokenizer<T> & right)
{
	os << "The abstract tokenizer splits documents into index_items";
	return os;
}
