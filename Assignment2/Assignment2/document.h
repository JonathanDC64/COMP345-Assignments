#pragma once
#include <string>
#include <vector>

class document
{
public:
	document();
	~document();
	document(const std::string & file_name);
	std::string name() const;
	long size() const;
	std::string content() const;
private:
	std::string document_name;
	std::string document_content;
};

