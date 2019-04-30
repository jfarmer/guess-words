#include "Lexicon.h"

extern bool quiet;

Lexicon::Lexicon (string file) {
	unsigned int i;
	string line;
	ifstream lexicon, lexicon1;
	characterTotal = 0;
	maxLen = 0;
	
	if (!quiet) cout << "Loading lexicon from \"" + file + "\"...";
	fflush(NULL);
	lexicon.open(file.c_str());
	
	if (!lexicon) {
		cout << "error!" << endl;
		exit(1);
	}
	if (!quiet) cout << "done" << endl;
	if (!quiet) cout << "Computing character statistics...";
	fflush(NULL);
	
	while(getline(lexicon, line)) {
		for(i = 0; i < line.size(); i++) {
			if ( !isspace(line[i])) {
				characterCount[line[i]]++;
				characterTotal++;		
			}
		}
	}
	if (!quiet) cout << "done" << endl;
	
	singletonProb = log2((double)characterTotal);
	
	if (!quiet) cout << "\tWord count:\t" << characterTotal << endl;
	if (!quiet) cout << "\tSingleton plog:\t" << singletonProb << " bits" << endl;
	
	lexicon.close();
	lexicon1.open(file.c_str());

	if (!quiet) cout << "Computing word statistics...";
	fflush(NULL);	
	
	
	while(lexicon1 >> line) {
		bool wordExists = (wordProb[line] != 0.0);
		if (!wordExists && line.size() > maxLen)
			maxLen = line.size();
		for(i = 0; i < line.size(); i++) {
			if (characterCount[line[i]] != 0 && !wordExists) {
				wordProb[line] += -log2(((double)characterCount[line[i]]) / (double)characterTotal);
			}
		}
	}
	
	if (!quiet) cout << "done" << endl;
	fflush(NULL);
	if (!quiet) cout << "\tLexicon size:\t" << wordProb.size() << endl;
	if (!quiet) cout << "\tMax. length:\t" << maxLen << endl;
	
	lexicon1.close();
}
/*
Lexicon::Lexicon (void) {
	wordProb["he"] = 4.0;
	wordProb["her"] = 4.0;
	wordProb["the"] = 3.0;
	wordProb["here"] = 5.0;
	wordProb["there"] = 5.0;
	wordProb["rent"] = 7.0;
	wordProb["is"] = 4.0;
	wordProb["tis"] = 8.0;
	wordProb["due"] = 7.0;
	wordProb["ere"] = 8.0;
	
	singletonProb = 3.0;
}
*/
bool Lexicon::inLexicon(string s) {
	if (s.size() > maxLen)
		return false;

	if (s.size() == 1 || wordProb[s] != 0.0)
		return true;
	
	return false;
}
double Lexicon::getProb(string s) {
	if (wordProb[s] == 0.0)
		return singletonProb;
	return wordProb[s];
}
