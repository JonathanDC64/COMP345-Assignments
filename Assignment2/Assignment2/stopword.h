#pragma once
#include <map>
#include <string>


class stopword
{
public:
	stopword();
	stopword(const std::string & file_name);
	~stopword();
	bool exists(const std::string & word) const;
	bool operator()(const std::string & word) const;
private:
	std::map<std::string, std::string> stopwords;
};

