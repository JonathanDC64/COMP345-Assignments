//
//  sentence_indexer.hpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef sentence_indexer_hpp
#define sentence_indexer_hpp
#include "indexer.hpp"
#include "sentence.hpp"

class sentence_indexer : public indexer{
    
    friend std::ostream & operator<<(std::ostream & os, const sentence_indexer & right);
    
    friend bool gtScoreGrouped(const query_result & left, const query_result & right);
    
public:
    
    /*! Default constructor */
    sentence_indexer();
    
    /*! from a given  */
    virtual std::vector<query_result> query(const std::string & q, int n = 500) override;
    
    /*! holds the set of abbreviations */
    static std::set<std::string> abbreviations;
    
    /*! holds the set of queries */
    std::vector<std::string> queries;
    
private:
    const std::string ABBREVITATIONS_FILE = "abbreviations.txt";
    const std::string INDEX_FILE = "doc_index.txt";
    const std::string QUERY_FILES = "query_files.txt";
    
    //functions
    void generateAbbreviations();
    void generateQueries();
    virtual void generateIndexItems() override;
    virtual std::string getIndexFile() const override;
};

bool gtScoreGrouped(const query_result & left, const query_result & right);

#endif /* sentence_indexer_hpp */
