#pragma once
#include "index_item.h"
#include "document.h"
class sentence : public index_item
{
public:

	/*! prints the name of the document it belongs to and the size of the sentence in words */
	friend std::ostream& operator<<(std::ostream& os, const sentence & doc);

	/*! Default constructor */
	sentence();

	/*! Constructs a sentence using a document, its starting position and its ending position */
	sentence(const document & doc, long pos, long endPos);

	/*! returns the the number of words in the document */
	virtual long size() const override;

	/*! gets the starting position of the sentence */
	long get_pos() const;

private:
	long pos;
	long num_words;

	//may have to be removed
	//const document & doc;
};

