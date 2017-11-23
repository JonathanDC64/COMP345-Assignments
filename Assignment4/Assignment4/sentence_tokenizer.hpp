//
//  sentence_tokenizer.hpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef sentence_tokenizer_hpp
#define sentence_tokenizer_hpp
#include "abstract_tokenizer.hpp"
#include "sentence.hpp"

class sentence_tokenizer : public abstract_tokenizer<sentence>{
    
    friend std::ostream & operator<<(std::ostream & os, const sentence_tokenizer & right);
    
public:
    
    /*! splits the document into sentences */
    virtual std::vector<sentence> tokenize(const document & doc) const override;
    
    /*! removes unnecessary white spaces from the sentence */
    static sentence sanitize(sentence & sent);
private:
    
};

#endif /* sentence_tokenizer_hpp */
