#pragma once
#include <map>
#include <string>


class stopword
{
public:
	stopword();
	stopword(const std::string & file_name);
	~stopword();
	bool exists(const std::string & word);
	bool operator()(const std::string & word);
private:
	std::map<std::string, std::string> stopwords;
};

