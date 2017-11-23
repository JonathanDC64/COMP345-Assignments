//
//  indexer.hpp
//  project
//
//  Created by justin baron on 2017-11-09.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef indexer_hpp
#define indexer_hpp
#include <set>
#include <map>
#include <map>
#include <vector>
#include <string>
#include "query_result.hpp"
#include "index_item.hpp"
#include "stopword.hpp"


struct data_item{
    int occurence = 1;
    double weight = 0.0;
};

typedef std::map<std::string,std::map<int,data_item>> dmap;

class indexer{
    
    friend std::ostream & operator<<(std::ostream & os, const indexer & right);
    friend void operator>>(index_item & doc, indexer & idx);
    
public:
    
    /*! Default constructor - initializes members */
    indexer();
    
    /*! Destructor */
    virtual ~indexer();
    
    /*! Removes all stopwords from the dictionary */
    void removeStopwords();
    
    /*! returns a const pointer to the index item at a given index */
    const index_item * operator[](int index) const;
    
    /*! returns a pointer to the index item at a given index */
    index_item * operator[](int index);
    
protected:
    //members
    dmap dictionary;
    std::vector<index_item *> index_items;
    std::vector<double> denom_double;
    mutable std::vector<int> totals;
    unsigned int maxWordLength;
    stopword stop_words;
    
    //functions
    int size() const;
    virtual void generateIndexItems() = 0;
    virtual std::string getIndexFile() const = 0;
    virtual std::vector<query_result> query(const std::string & q, int n = 10) = 0;
    virtual void generateDictionary();
    void normalize();
    double cosine_similarity(const std::vector<double> & q, const std::vector<double> & d,const int doc_index);
    
private:
    
};

#endif /* indexer_hpp */
