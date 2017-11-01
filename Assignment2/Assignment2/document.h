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

	/*! returns the name of the document */
	virtual std::string name() const;

	/*! returns the the number of character in the document */
	virtual long size() const;

	/*! returns the content of the document (Text) */
	virtual std::string content() const;

private:
	std::string document_name; // name of document
	std::string document_content; // content of document
};

