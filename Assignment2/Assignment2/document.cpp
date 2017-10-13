#include "document.h"
#include <fstream>
#include <iostream>

document::document(){}

document::~document(){}

document::document(const std::string & file_name)
{
	this->document_name = file_name;

	std::string line;
	std::ifstream fin(file_name.c_str());
	
	while (std::getline(fin, line)) {
		this->document_content += (line + '\n');
	}

	fin.close();
}

std::string document::name() const
{
	return this->name;
}

long document::size() const
{
	return this->document_content.size();
}

std::string document::content() const
{
	return this->document_content;
}
