//
//  stopwords.hpp
//  project
//
//  Created by justin baron on 2017-11-16.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef stopwords_hpp
#define stopwords_hpp
#include <string>
#include <set>


class stopword{
    
    friend std::ostream & operator<<(std::ostream & os, const stopword & right);
public:
    
    /*! default constructor - loads the stopwords */
    stopword();
    
    /*! returns true if the given word is a stopword, else returns false */
    bool operator()(std::string word);
private:
    std::set<std::string> stopwords;
    const std::string STOP_WORDS = "stopwords.txt";
};

#endif /* stopwords_hpp */
