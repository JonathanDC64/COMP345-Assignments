#pragma once
#include <map>
#include <string>


class stopword
{
	friend std::ostream& operator<<(std::ostream& os, const stopword & sw);
public:
	stopword();
	stopword(const std::string & file_name);
	~stopword();
	bool exists(const std::string & word) const;
	bool operator()(const std::string & word) const;
private:
	std::map<std::string, std::string> stopwords;
};

