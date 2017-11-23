//
//  abstract_tokenizer.hpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef abstract_tokenizer_hpp
#define abstract_tokenizer_hpp
#include <string>
#include <vector>
#include "index_item.hpp"
#include "document.hpp"

template<typename T>
class abstract_tokenizer {
    
public:
    
    /*! splits a document into tokens */
    virtual std::vector<T> tokenize(const document & doc) const = 0;
private:
    
};

#endif /* abstract_tokenizer_hpp */
