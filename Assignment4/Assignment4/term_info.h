#pragma once
class term_info
{
public:
	term_info();
	term_info(int occurence, double weight);
	int occurence;
	double weight;
};