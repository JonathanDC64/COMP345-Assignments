#pragma once
#include "document.h"

class query_result
{
	friend std::ostream& operator<<(std::ostream& os, const query_result & qr);
public:
	query_result(const document & found_document, const double score);
	~query_result();

	document found_document;
	double score;
	
};