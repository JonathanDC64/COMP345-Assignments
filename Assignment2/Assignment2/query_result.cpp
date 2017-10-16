#include "query_result.h"

query_result::query_result(const document & found_document, const double score)
{
	this->found_document = found_document;
	this->score = score;
}

bool gtScore(const query_result & left, const query_result & right)
{
	return left.score > right.score;
}


query_result::~query_result()
{
}
