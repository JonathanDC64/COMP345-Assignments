#pragma once
#include "document.h"
#include <string>
#include <vector>
template<typename T>
class abstract_tokenizer
{
public:
	virtual std::vector<T> tokenize(const document & doc) = 0;
};