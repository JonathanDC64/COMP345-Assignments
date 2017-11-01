#include "index_item.h"
#include <fstream>


index_item::index_item()
{
}

index_item::index_item(const std::string & file_name)
{
	set_name(file_name);

	std::string line;
	std::ifstream fin(file_name.c_str());

	while (std::getline(fin, line)) {
		this->document_content += (line + '\n');
	}

	fin.close();
}

std::string index_item::name() const
{
	return this->document_name;
}


index_item::~index_item()
{
}

std::string index_item::content() const
{
	return this->document_content;
}

void index_item::set_content(const std::string & content)
{
	this->document_content = content;
}

const std::string & index_item::get_full_content() const
{
	return this->document_content;
}

void index_item::set_name(const std::string & name)
{
	this->document_name = name;
}

