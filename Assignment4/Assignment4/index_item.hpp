//
//  index_item.hpp
//  project
//
//  Created by justin baron on 2017-11-11.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef index_item_hpp
#define index_item_hpp
#include <iostream>
#include <string>


class index_item{
    
    friend std::ostream & operator<<(std::ostream & os, const index_item & right);
    
public:
    
    /*! Default constructor */
    index_item();
    
    /*! returns the size of the index_item */
    virtual unsigned int size() const = 0;
    
    /*! returns the file_name */
    virtual std::string name() const;
    
    /*! returns the content of the index_item */
    std::string content() const;
    
    /*! sets the content of the index_item to the string argument */
    void setContent(const std::string & content);
    
protected:
    void setName(const std::string & name);
    
private:
    std::string file_name;
    std::string index_item_content;
};

#endif /* index_item_hpp */
