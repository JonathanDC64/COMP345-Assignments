//
//  movie.hpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef movie_hpp
#define movie_hpp
#include "index_item.hpp"

class movie : public index_item{
    
    friend std::ostream & operator<<(std::ostream & os, const movie & right);
    
public:

    /*! constructs a movie with (movie id, movie name, movie release date, movie summary */
    movie(std::string id, std::string name, std::string release_date, std::string content);
    
    /*! Returns the number of characters in the movie summary */
    unsigned int size() const override;
    
    /*! returns the name of the movie */
    virtual std::string name() const override;
private:
    
    std::string id;
    std::string movie_name;
    std::string release_date;

};

#endif /* movie_hpp */

