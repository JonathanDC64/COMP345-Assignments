#pragma once
#include <map>
#include <string>


class stopword
{
	/*! prints the number of stop words */
	friend std::ostream& operator<<(std::ostream& os, const stopword & sw);
public:

	/*! Default constructor */
	stopword();

	/*! Constructs a stopword object using the name of a file */
	stopword(const std::string & file_name);

	/*! Destructor */
	~stopword();

	/*! Returns true if the given word is a stopword, else false */
	bool exists(const std::string & word) const;

	/*! allows exists() method to be called like the following: stopwords(word) */
	bool operator()(const std::string & word) const;
private:
	std::map<std::string, std::string> stopwords; // map containing all the stopwords
};

