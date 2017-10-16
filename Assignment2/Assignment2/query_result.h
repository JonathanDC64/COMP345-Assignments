#pragma once
#include "document.h"

class query_result
{
public:
	query_result(const document & found_document, const double score);
	~query_result();

	document found_document;
	double score;
};