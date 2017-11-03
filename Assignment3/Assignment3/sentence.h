#pragma once
#include "index_item.h"
#include "document.h"
class sentence : public index_item
{
public:
	sentence();

	sentence(const document & doc, long pos, long endPos);

	/*! returns the the number of character in the document */
	virtual long size() const override;

	long get_pos() const;
private:
	long pos;
	long num_words;

	//may have to be removed
	//const document & doc;
};

