//
//  query_result.hpp
//  project
//
//  Created by justin baron on 2017-11-10.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef query_result_hpp
#define query_result_hpp
#include "document.hpp"
#include "index_item.hpp"

class query_result{
    friend bool bScore(const query_result & left, const query_result & right);
    friend std::ostream & operator<<(std::ostream & ofs, const query_result & right);
public:
    
    /*! constructs a query_result with (an index_item, a score) */
    query_result(index_item & item, double score);
    
    /*! returns the query_result's score */
    double getScore() const;
    
    /*! gets the index_item */
    const index_item * getItem() const;
    
    /*!  */
    index_item * item;
private:
    double score;
};

bool bScore(const query_result & left, const query_result & right);

#endif /* query_result_hpp */
