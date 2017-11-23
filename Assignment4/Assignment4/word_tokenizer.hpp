//
//  word_tokenizer.hpp
//  project
//
//  Created by justin baron on 2017-11-10.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef word_tokenizer_hpp
#define word_tokenizer_hpp
#include "document.hpp"
#include "abstract_tokenizer.hpp"

class word_tokenizer : public abstract_tokenizer<std::string>{
    
    friend std::ostream & operator<<(std::ostream & os, const word_tokenizer & right);
    
public:
    
    /*! splits the document's content into words */
    std::vector<std::string> tokenize(const document & doc) const override;
    
    /*! splits the string into words */
    static std::vector<std::string> tokenizeString(const std::string s);
    
    /*! makes the word lowercase and removes punctuation */
    static std::string sanitize(std::string word);
private:
    
};

#endif /* word_tokenizer_hpp */
