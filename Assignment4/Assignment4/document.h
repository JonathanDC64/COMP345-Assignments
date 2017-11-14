#pragma once
#include "index_item.h"
#include <string>
#include <vector>

class document : public index_item
{
	/*! prints the name of the document with its size */
	friend std::ostream& operator<<(std::ostream& os, const document & doc);
public:

	/*! Default constructor */
	document();

	/*! Destructor */
	~document();

	/*! Constructor that creates a document using the name of a given file */
	document(const std::string & file_name);

	/*! returns the the number of character in the document */
	virtual long size() const override;
};

