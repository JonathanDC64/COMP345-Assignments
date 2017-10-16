#pragma once
#include <vector>
#include <string>

class tokenizer
{
	friend std::ostream& operator<<(std::ostream& os, const tokenizer & tk);
public:
	tokenizer();
	~tokenizer();
	static std::vector<std::string> tokenize(const std::string & filename);
	static std::string sanitize(std::string &);
	static std::vector<std::string> tokenize_string(std::string & text);
};

