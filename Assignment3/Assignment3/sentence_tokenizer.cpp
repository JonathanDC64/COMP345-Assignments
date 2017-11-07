#include "sentence_tokenizer.h"
#include "document.h"
#include <fstream>

sentence_tokenizer::sentence_tokenizer()
{
	std::string word;
	std::ifstream ifs(ABBREVIATION_FILE.c_str());
	while (ifs >> word)
	{
		std::pair<std::string, std::string> abb(word, word);
		abbreviations.insert(abb);
	}
	ifs.close();
}

std::vector<sentence> sentence_tokenizer::tokenize(const document & doc)
{
	std::vector<sentence> tokens;

	std::string::size_type pos = 0;
	std::string::size_type endPos = 0;
	std::string::size_type size = doc.content().size();
	std::string docContent = doc.content();

	while (pos <= size) {
		//need to pass full string and index
		while (docContent[pos] == ' ' || docContent[pos] == '\t' || docContent[pos] == '\n')
		{
			++pos;
		}
		endPos = find_punct(docContent, pos) + 1;
		tokens.push_back(sentence(doc, pos, endPos));
		pos = endPos;
	}

	return tokens;
}

std::string::size_type sentence_tokenizer::find_punct(std::string & text, int start)
{
	for (std::string::size_type i = start; i < text.size(); i++) {
		if (text[i] == '.')
		{
			int s = i - 1;
			
			while (s >= start && text[s] != ' ' && text[s] != '.')
			{
				--s;
			}
			++s;
			std::string wordBeforePeriod = text.substr(s, i - s);
			if(!isAbbreviation(wordBeforePeriod))
				return i;
		}
		else if (text[i] == '!' || text[i] == '?')
			return i;
	}
	return text.size();
}

bool sentence_tokenizer::isAbbreviation(std::string ab)
{
	return abbreviations.find(ab) != abbreviations.end();
}
