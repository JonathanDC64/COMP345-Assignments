#include "abstract_tokenizer.h"
#include <sstream>


//Makes a word lower case and removes punctuation
template<typename T>
std::string abstract_tokenizer<T>::sanitize(std::string & text) {
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

template<typename T>
std::vector<std::string> abstract_tokenizer<T>::tokenize_string(std::string & text)
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
