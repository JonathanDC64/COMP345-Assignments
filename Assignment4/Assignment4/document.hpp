//
//  document.hpp
//  project
//
//  Created by justin baron on 2017-11-10.
//  Copyright © 2017 justin baron. All rights reserved.
//

#ifndef document_hpp
#define document_hpp
#include "index_item.hpp"

class document : public index_item{
  
    /*! prints the name of the document with its size */
    friend std::ostream& operator<<(std::ostream& os, const document & doc);
    
public:
    
    /*! Default constructor */
    document();
    
    /*! constructs a document from a file name */
    document(std::string file_name);
    
    /*!  */
    virtual unsigned int size() const override;
private:
    
};

#endif /* document_hpp */
