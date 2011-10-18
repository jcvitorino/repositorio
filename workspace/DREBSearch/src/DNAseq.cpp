/*
 * XNAseq.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */


#include "DNAseq.h"

DNAseq::DNAseq() {
	seq = "";
	id = "";
	description = "";
}

DNAseq::DNAseq(string id, string description, string seq){
	this->seq = seq;
	this->id = id;
	this->description = description;
}

void DNAseq::set_id(string input_id) {
	id = input_id;
}

void DNAseq::set_description(string input_description) {
	description = input_description;
}

void DNAseq::set_seq(string input_seq) {
	seq = input_seq;
}

void DNAseq::clear() {
	seq = "";
	id = "";
	description = "";
}


void DNAseq::cleanSeq() {
	std::transform(seq.begin(), seq.end(), seq.begin(),
			(int(*)(int))std::toupper);string::iterator endp = remove_if(seq.begin(),seq.end(), not_nucleotide);
    seq.erase(endp, seq.end());
}

int DNAseq::length() {
	return seq.size();
}


DNAseq DNAseq::reverse_compliment() {
	DNAseq tmpSeq;
	tmpSeq.id = id;
	tmpSeq.description = description;
	tmpSeq.seq = seq;
	int RNA = seq.find_last_of("U");
	if (RNA == -1) {
		reverse_copy(seq.begin(), seq.end(), tmpSeq.seq.begin());
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_DNA);
	} else {
		reverse_copy(seq.begin(), seq.end(), tmpSeq.seq.begin());
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_RNA);
	}
	return tmpSeq;
}



DNAseq DNAseq::compliment() {
	DNAseq tmpSeq;
	tmpSeq.id = id;
	tmpSeq.description = description;
	tmpSeq.seq = seq;
	int RNA = seq.find_last_of("U");
	if (RNA == -1) {
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_DNA);
	} else {
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_RNA);
	}
	return tmpSeq;
}


DNAseq DNAseq::toRNA() {
	DNAseq tmpSeq;
	tmpSeq.id = id;
	tmpSeq.description = description;
	tmpSeq.seq = seq;
	transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
			replace_nucleotide);
	return tmpSeq;
}

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

