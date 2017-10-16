#pragma once
#include <vector>
#include <string>

class tokenizer
{
public:
	tokenizer();
	~tokenizer();
	static std::vector<std::string> tokenize(const std::string &);
	static std::string sanitize(std::string &);
	static std::vector<std::string> tokenize_string(std::string & text);
};

