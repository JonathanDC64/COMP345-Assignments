#pragma once
#include <vector>
#include <string>

class tokenizer
{
public:
	tokenizer();
	~tokenizer();
	std::vector<std::string> tokenize(const std::string &);
	static std::string sanitize(std::string &);
};

