//============================================================================
// Name        : median.cpp
// Author      : josue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "XNA.h"

using namespace std;

int totalDistance(XNAseq prefix, XNA seq, int sizeP);
int hammingDistance(string s, string t);
struct ret bypass(XNAseq a, int i);
struct ret nextVertex(XNAseq a, int i, int L);
XNAseq medianString(XNA seq, int L, int mis);

struct ret {
	XNAseq s;
	int i;
};

int main() {

	char* finFSA = "example.fasta";
	char* fout = "out.fsa";
	XNA s1;
	s1.readFasta(finFSA);


/*
	int numberOfSequences = s1.chain.size();
	cout << numberOfSequences << endl;

	for (int i = 0; i < numberOfSequences; i++) {
		string mainSEQ = s1.chain[i].seq;
		string mainid = s1.chain[i].id;
		string maindesc = s1.chain[i].description;
		int lenSeq = s1.chain[i].length();
		cout << mainid << endl << maindesc << endl << lenSeq << endl << mainSEQ << endl << endl;

	}
*/


	XNAseq prefix;
	prefix.set_seq("AAAA");
//	int sizeP = 4;
	//int res = totalDistance(prefix,s1,sizeP);
	//cout <<"Resp " <<res <<endl;
//    struct ret r = bypass(prefix,2);
	//   cout << r.s.seq << ' ' << r.i << endl;
	/*
	 struct ret r;
	 r.s = prefix;
	 r.i = 0;
	 for (int k = 0; k < 400; ++k) {
	 r = nextVertex(r.s,r.i,4);
	 cout << r.s.seq << ' ' << r.i << endl;
	 }
	 */
	prefix = medianString(s1, 8, 4);
	//cout << prefix.seq << endl;
	return 0;
}

int hammingDistance(string s, string t) {
	if (s.length() != t.length()) {
		cout << "s and t must have same length in hammingDistance()" << endl;
		exit(0);
	}
	int ct = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] != t[i])
			++ct;
	}
	return ct;
}

int totalDistance(XNAseq prefix, XNA seq, int sizeP) {
	vector<int> sum;
	int numberOfSequences = seq.chain.size();
	for (int i = 0; i < numberOfSequences; i++) {
		int dist1 = 20000;
		for (int j = 0; j < ((seq.chain[i].length() - sizeP) + 1); j++) {
			int dist2 = hammingDistance(prefix.seq,
					seq.chain[i].seq.substr(j, sizeP));
			if (dist1 > dist2) {
				dist1 = dist2;
			}
		}
		sum.push_back(dist1);
	}
	int result = 0;
	vector<int>::iterator it;
	for (it = sum.begin(); it < sum.end(); it++) {
		result = result + *it;
	}
	return result;
}

struct ret bypass(XNAseq a, int i) {
	int j = i;
	ret r;
	while (j != -1) {
		if (a.seq[j] != 'T') {
			if (a.seq[j] == 'A') {
				a.seq[j] = 'C';
				r.s = a;
				r.i = j;
				return r;
			}
			if (a.seq[j] == 'C') {
				a.seq[j] = 'G';
				r.s = a;
				r.i = j;
				return r;
			}
			if (a.seq[j] == 'G') {
				a.seq[j] = 'T';
				r.s = a;
				r.i = j;
				return r;
			}

		}
		j = j - 1;
	}
	r.s = a;
	r.i = -1;
	return r;
}

struct ret nextVertex(XNAseq a, int i, int L) {
	int j = L - 1;
	struct ret r;
	if (i < (L - 1)) {
		a.seq[i + 1] = 'A';
		r.s = a;
		r.i = (i + 1);
		return r;
	} else {
		while (j != -1) {
			if (a.seq[j] != 'T') {
				if (a.seq[j] == 'A') {
					a.seq[j] = 'C';
					r.s = a;
					r.i = j;
					return r;
				}
				if (a.seq[j] == 'C') {
					a.seq[j] = 'G';
					r.s = a;
					r.i = j;
					return r;
				}
				if (a.seq[j] == 'G') {
					a.seq[j] = 'T';
					r.s = a;
					r.i = j;
					return r;
				}

			}
			j = j - 1;
		}
		r.s = a;
		r.i = -1;
		return r;
	}
}

XNAseq medianString(XNA seq, int L, int mis) {
	XNAseq s;
	for (int k = 0; k < L; ++k) {
		s.seq = s.seq + 'A';
	}
	int i = 0;
	int bestDistance = 500;
	XNAseq bestWord, prefix;
	int optmisticDistance = 0;
	struct ret r;
	int totalDist = 0;
	while (i > -1) {
		if (i < (L - 1)) {
			prefix.seq = s.seq.substr(0, i + 1);
			//cout << i << endl;
			//cout << prefix.seq << endl;
			optmisticDistance = totalDistance(prefix, seq, prefix.seq.length());
			//cout << optmisticDistance << endl;
			if (optmisticDistance > bestDistance) {
				r = bypass(s, i);
				s = r.s;
				i = r.i;
			} else {
				r = nextVertex(s, i, L);
				s = r.s;
				i = r.i;
			}
		} else {
			totalDist = totalDistance(s, seq, s.seq.length());
			if (totalDist <= bestDistance) {
				bestDistance = totalDist;
				bestWord = s;
				if (bestDistance <= mis) {
					cout << bestWord.seq << endl;
				}
			}
			r = nextVertex(s, i, L);
			s = r.s;
			i = r.i;
		}
	}
	return bestWord;
}
