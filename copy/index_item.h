#pragma once
#include <string>
class index_item
{
public:
	index_item();
	~index_item();
	/*! returns the name of the document */
	virtual std::string name() const = 0;

	/*! returns the the number of character in the document */
	virtual long size() const = 0;

	/*! returns the content of the document (Text) */
	virtual std::string content() const = 0;
};

