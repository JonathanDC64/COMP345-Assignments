#include "stopword.h"
#include <fstream>


stopword::stopword(){}
stopword::~stopword() {}

stopword::stopword(const std::string & file_name){
	std::ifstream fin(file_name.c_str());
	std::string stopword;
	while (fin >> stopword) {
		this->stopwords[stopword] = stopword;
	}

	fin.close();
}

bool stopword::exists(const std::string & word) const
{
	return this->stopwords.find(word) != this->stopwords.end();
}

bool stopword::operator()(const std::string & word) const
{
	return this->exists(word);
}
