#pragma once
#include "document.h"

class query_result
{
	/*! prints the name of the document with its score */
	friend std::ostream& operator<<(std::ostream& os, const query_result & qr);
public:

	/*! constructs a query_result using a document and its score */
	query_result(const document & found_document, const double score);

	/*! Destructor */
	~query_result();

	document found_document; // document
	double score; // score of the document
	
};