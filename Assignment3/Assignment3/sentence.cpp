#include "sentence.h"
#include <string>
#include <sstream>


sentence::sentence()
	: /*doc(std::string("")),*/ index_item()
{
}

sentence::sentence(const document & doc, long pos, long endPos)
	: /*doc(doc), */index_item()
{
	this->set_name(doc.name());
	this->pos = pos;

	this->set_content(doc.content().substr(this->pos, endPos - this->pos));

	std::istringstream ist(this->content());
	std::string word;
	while (ist >> word) {
		this->num_words++;
	}
}

long sentence::size() const
{
	return this->num_words;
}