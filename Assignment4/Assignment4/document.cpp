#include "document.h"
#include <fstream>
#include <iostream>

document::document(){}

document::~document(){}

document::document(const std::string & file_name)
	: index_item(file_name)
{	
}

long document::size() const
{
	return this->get_full_content().size();
}

std::ostream & operator<<(std::ostream & os, const document & doc)
{
	os << "Name: " << doc.name() << " Size: " << doc.size();
	return os;
}
