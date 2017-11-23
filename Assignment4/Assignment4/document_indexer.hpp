//
//  document_indexer.hpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef document_indexer_hpp
#define document_indexer_hpp
#include "indexer.hpp"

class document_indexer : public indexer{

    friend std::ostream & operator<<(std::ostream & os, const document_indexer & right);
    
public:
    
    /*! Default constructor */
    document_indexer();
    
    /*! outputs the data from the index_files (each word with its occurence and weight from each document) in an adjencency matrix */
    void output() const;
    
    /*! given a query, returns the N best query_results score using the query */
    virtual std::vector<query_result> query(const std::string & q, int n = 10) override;
    
private:
    
    virtual void generateIndexItems() override;
    virtual std::string getIndexFile() const override;
    void printLegend() const;
    void printTotals() const;
    void printFullLine() const;
    void generateTotals() const;
    
    //const variables
    const int DictionaryLength = 10;
    const std::string INDEX_FILE = "index.txt";
};

#endif /* document_indexer_hpp */
