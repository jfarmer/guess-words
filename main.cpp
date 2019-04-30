#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>


#include "Lexicon.h"
#include "Parse.h"

#define DEFAULT_DATA "data/kjv"
#define DEFAULT_STRING "therentisdue"

using namespace std;

string doParse(Lexicon *, string);


void usage(const char *);
bool quiet = false;

int main(int argc, char **argv) {
	int i;
	unsigned int j;
	string data = DEFAULT_DATA;
	string s = DEFAULT_STRING;
	Lexicon *lexicon;
	
	for (i = 1; i < argc; i++) {
		string arg = argv[i];
		for (j = 0; j < arg.size() - 1; j++ ) {
			if (arg[0] == '-') {
				switch (arg[1]) {
					case 'd':
						if (i+1 == argc) {
							cerr << "ERROR: No filename specified, but -d option supplied." << endl;
							usage(argv[0]);
							return 0;
						}
						data = argv[++i];
						break;
					case 's':
						if (i+1 == argc) {
							cerr << "ERROR: No string specified, but -s option supplied." << endl;
							usage(argv[0]);
							return 0;
						}
						s = argv[++i];
						break;
					case 'q':
						quiet = true;
						break;
					case 'h':
						usage(argv[0]);
						return 0;
						break;
					default:
						break;
				}
			}
		}
	}
	
	if (s.length() == 0) {
		usage(argv[0]);
		return 0;
	}
	
	lexicon = new Lexicon(data);
	
	if (s == "-")
		while(getline(cin, s))
			cout << doParse(lexicon, s) << endl;
	else
		cout << doParse(lexicon, s) << endl;
	return 0;
}


void usage(const char *app)
{
	cout << "USAGE" << endl;
	cout << "  " << app << " -s [<string>|-]" << endl;
	cout << "OPTIONS" << endl;
	cout << "  -d <file>         Use <file> as the training data.  Default is 'data/kjv'" << endl;
	cout << "  -h                Display this message." << endl;
	cout << "  -q                Turn off verbose messages." << endl;
	cout << "  -s [<string>|-]   Parse <string>.  If <string> is '-' then read data from stdin." << endl;
}

string doParse(Lexicon *lexicon, string s) {
	Parse BestParses[s.size()+1];
	Parse n,p;
	vector <int> a;
	string *u;
	unsigned int i, j;
	
	a.push_back(0);
	BestParses[0] = *(new Parse(0.0, "", a));
	if (!quiet) cout << "Parsing string \"" << s << "\"...";
	fflush(NULL);
	for (i = 1; i <= s.size(); i++) {
		for(j=0;j < i; j++) {
			u = new string(s.substr(j,i-j));
			if (lexicon->inLexicon(*u)) {
				Parse n (lexicon->getProb(*u), *u, a);
				
				p = BestParses[j]+n;
				
				if ( p < BestParses[i] )
					BestParses[i] = p;
			}
		}
	}
	if (!quiet) cout << "done" << endl;
	return BestParses[s.size()].parse();
}
