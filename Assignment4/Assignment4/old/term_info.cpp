#include "term_info.h"



term_info::term_info()
	: occurence(1), weight(0)
{
}

term_info::term_info(int occurence, double weight)
	: occurence(occurence), weight(weight)
{
}
