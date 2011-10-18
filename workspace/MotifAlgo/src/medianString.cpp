/*
 * medianString.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#include "medianString.h"


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

int totalDistance(DNAseq prefix, DNA seq, int sizeP) {
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

struct ret bypass(DNAseq a, int i) {
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

struct ret nextVertex(DNAseq a, int i, int L) {
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

DNAseq medianString(DNA seq, int L, int mis) {
	DNAseq s;
	for (int k = 0; k < L; ++k) {
		s.seq = s.seq + 'A';
	}
	int i = 0;
	int bestDistance = 500;
	DNAseq bestWord, prefix;
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

DNAseq nextLeaf(DNAseq a, int L) {
	int j = L - 1;
	while (j != -1) {
		if (a.seq[j] != 'T') {
			if (a.seq[j] == 'A') {
				a.seq[j] = 'C';
				return a;
			}
			if (a.seq[j] == 'C') {
				a.seq[j] = 'G';
				return a;
			}
			if (a.seq[j] == 'G') {
				a.seq[j] = 'T';
				return a;
			}

		}
		a.seq[j] = 'A';
		j = j - 1;
	}
	return a;
}

void allLeaves(int L) {
	DNAseq s;
	for (int k = 0; k < L; ++k) {
		s.seq = s.seq + 'A';
	}
	int i = 0;
	int cont = pow(4.0, L);
	while (i < cont) {
		cout << s.seq << ' ' << i << endl;
		s = nextLeaf(s, L);
		i++;
	}
}

struct Freq computeFrequency(DNA setSeq, DNAseq seq) {
	int dist = 0;
	double freq = 0;
	struct Freq Feq;
	int numberOfSequences = setSeq.chain.size();
	for (int i = 0; i < numberOfSequences; i++) {
		for (int j = 0; j < ((setSeq.chain[i].length() - seq.length()) + 1);
				j++) {
			int dist = hammingDistance(seq.seq,
					setSeq.chain[i].seq.substr(j, seq.length()));
			if (dist == 0) {
				freq++;
			}
		}
	}
	Feq.olig = seq;
	Feq.freq = freq; //(freq/(setSeq.chain.size() * numberOfSequences));
	return Feq;
}

