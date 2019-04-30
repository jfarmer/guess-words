#ifndef _LEXICON_H
#define _LEXICON_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

class Lexicon {

	double singletonProb;
	map<char,int> characterCount;
	map<string, double> wordProb;
	long long characterTotal;
	unsigned int maxLen;
	
	public:
		Lexicon(string);
		bool inLexicon(string);
		double getProb(string);
};
#endif
