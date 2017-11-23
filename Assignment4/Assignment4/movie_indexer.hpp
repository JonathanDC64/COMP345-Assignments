//
//  movie_indexer.hpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef movie_indexer_hpp
#define movie_indexer_hpp
#include <map>
#include "movie.hpp"

#include "indexer.hpp"

class movie_indexer : public indexer{
  
    friend std::ostream & operator<<(std::ostream & os, const movie_indexer & right);
    
public:
    
    /*! Default constructor */
    movie_indexer();
    
    /*! given a movie name, returns the N best query_results's score using the summary of the movie name */
    virtual std::vector<query_result> query(const std::string & q, int n = 5) override;
private:
    std::map<std::string,movie*> plot;
    virtual void generateDictionary() override;
    virtual void generateIndexItems() override;
    virtual std::string getIndexFile() const override;
    
    bool isDate(const std::string & date) const;
    
    const std::string MOVIE_METADATA = "MovieSummaries/movie.metadata.tsv";
    const std::string FILE_PLOT = "MovieSummaries/plot_summaries.txt";
    const std::string INDEX_FILE = "index_movie.txt";
};

#endif /* movie_indexer_hpp */
