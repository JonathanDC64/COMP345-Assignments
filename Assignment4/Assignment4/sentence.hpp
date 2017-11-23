//
//  sentence.hpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef sentence_hpp
#define sentence_hpp
#include "index_item.hpp"

class sentence : public index_item{
    
    friend std::ostream & operator<<(std::ostream & os, const sentence & right);
    
public:
    /*! Constructs a sentence with (the content of the sentence, the name of the
         document where the sentence is from, the starting position of the sentence in the document */
    sentence(const std::string & content, const std::string & name, unsigned int pos);
    
    /*! returns the number of words in the sentence */
    virtual unsigned int size() const override;
    
    /*! gets the starting position of the sentence in its document */
    unsigned int getPos() const;
private:
    unsigned int pos;
};

#endif /* sentence_hpp */
