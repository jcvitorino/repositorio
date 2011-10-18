/*
 * function.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#include "function.h"

bool not_nucleotide(char ch) {
	string str = "ACGTU";
	// added U accept RNA;
	// uppercase the seq in all inlines
	string ts(1, ch);
	if (str.find(ts) == string::npos)
		return true;
	else
		return false;
}


char compliment_DNA(char ch) {
	string str = "ACGT";
	string ts(1, ch);
	if (ch == 'A')
		return 'T';
	else if (ch == 'T')
		return 'A';
	else if (ch == 'C')
		return 'G';
	else
		return 'C';
}

char compliment_RNA(char ch) {
	string str = "ACGT";
	string ts(1, ch);
	if (ch == 'A')
		return 'T';
	else if (ch == 'T')
		return 'A';
	else if (ch == 'C')
		return 'G';
	else
		return 'C';
}

char replace_nucleotide(char ch) {
// basically converts T to U for RNA
	if (ch == 'T')
		return 'U';
	else
		return ch;
}

/*
class hsp {
	int query_start, query_end;
	int sbjct_start, sbjct_end;
};
*/


bool space(char c) {
	return isspace(c);
}

// false if argument is whitespace, true otherwise
bool not_space(char c) {
	return !isspace(c);
}

// The following split function is adapted
// from Andrew Koenig and Barbara Moo,
// "Accelerated C++"; true if argument is delim"|",
// false otherwise
vector<string> split(const string& str) {
	typedef string::const_iterator iter;
	vector<string> ret;
	iter i = str.begin();
	while (i != str.end()) {
		// ignore leading blanks
		i = find_if(i, str.end(), not_space); // not_space
		// find end of next word
		iter j = find_if(i, str.end(), space); // space
		// copy the characters in [i,j)
		if (i != str.end())
			ret.push_back(string(i, j));
		i = j;
	}
	return ret;
}

// one way to convert a string to an int using streams...
bool StringToInt(const string &s, int &i) {
	istringstream myStream(s);
	if (myStream >> i)
		return true;
	else
		return false;
}





