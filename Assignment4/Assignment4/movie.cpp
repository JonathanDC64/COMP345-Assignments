//
//  movie.cpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "movie.hpp"

std::ostream & operator<<(std::ostream & os, const movie & right){
    os << "\n\nTitle: " << right.movie_name << std::endl
    << "Release date: " << right.release_date << std::endl
    << "ID: " << right.id << std::endl
    << std::endl
    << right.content()
    << "\n\n\n";
    return os;
}

movie::movie(std::string id, std::string name, std::string release_date, std::string content)
:id(id),movie_name(name),release_date(release_date)
{
    this->setContent(content);
}

unsigned int movie::size() const { 
    return this->content().size();
}

std::string movie::name() const {
    return this->movie_name;
}


