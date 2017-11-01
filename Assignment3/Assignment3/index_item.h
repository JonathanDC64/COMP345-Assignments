#pragma once
#include <string>
class index_item
{
public:
	index_item();

	index_item(const std::string & file_name);
	
	/*! returns the name of the document */
	std::string name() const;

	/*! returns the the number of character in the document */
	virtual long size() const = 0;

	/*! returns the content of the document (Text) */
	std::string content() const;

protected:
	void set_content(const std::string &content);
	const std::string & get_full_content() const;
	void set_name(const std::string &name);

private:
	std::string document_name; // name of document
	std::string document_content; // content of document
};

