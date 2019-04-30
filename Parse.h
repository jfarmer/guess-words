#ifndef _PARSE_H
#define _PARSE_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Parse {
		double cost;
		string phrase;
		vector <int> breaks;
	public:
		Parse(double, string, vector <int>);
		Parse(void);
		Parse operator + (Parse);
		bool operator < (Parse);
		
		string parse(void);
		string parse(const char);
};
#endif
