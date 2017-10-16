#include "query_result.h"
#include <iomanip>

query_result::query_result(const document & found_document, const double score)
{
	this->found_document = found_document;
	this->score = score;
}

bool gtScore(const query_result & left, const query_result & right)
{
	return left.score > right.score;
}

std::ostream & operator<<(std::ostream & os, const query_result & qr)
{
	os << std::setw(15) << std::left <<
		qr.found_document.name() <<
		"|" <<
		std::setw(10) << std::right << std::setprecision(4) <<
		qr.score <<
		std::endl;
	return os;
}


query_result::~query_result()
{
}
