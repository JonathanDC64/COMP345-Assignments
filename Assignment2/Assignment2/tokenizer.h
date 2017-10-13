#pragma once
#include <vector>
#include <string>

using namespace std;

class tokenizer
{
public:
	tokenizer();
	~tokenizer();
	vector<string> tokenize(string &);
	static string sanitize(string &);
};

