#include "Parse.h"

Parse::Parse(double c, string p, vector <int> v) {
	cost = c;
	phrase = p;
	breaks = v;
}

Parse::Parse(void) {
	cost = -1.0;
	phrase = "";
	
}

Parse Parse::operator +(Parse p) {
	Parse r;
	unsigned int i;
	
	r.cost = cost + p.cost;
	r.phrase = phrase + p.phrase;
	
	/* If "phrase" is empty we shouldn't be adding any breaks */
	if (phrase.size())
		r.breaks = breaks;
	
	for (i = 0; i < p.breaks.size(); i++)
		r.breaks.push_back(p.breaks[i] + phrase.size());
	
	return r;
}

bool Parse::operator < (Parse p) {
	return (p.cost < 0 || cost < p.cost);
}

string Parse::parse(void) {
	
	return parse('-');
}

string Parse::parse(const char c) {
	string parsedString;
	unsigned int i;
	int j = 0;
	
	for ( i = 0; i < phrase.size(); i++ ) {
		if ( i == breaks[j] ) {
			parsedString.push_back(c);
			j++;
		}
		parsedString.push_back(phrase[i]);
	}
	
	return parsedString;
}
