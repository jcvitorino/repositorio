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
#include <cmath>
#include "XNA.h"

using namespace std;

int totalDistance(XNAseq prefix, XNA seq, int sizeP);
int hammingDistance(string s, string t);
struct ret bypass(XNAseq a, int i);
struct ret nextVertex(XNAseq a, int i, int L);
XNAseq medianString(XNA seq, int L, int mis);
XNAseq nextLeaf(XNAseq a, int L);
void allLeaves(int L);
vector<struct Fe_b_> computeFrequency(XNA seq, double n, int len);
struct Fe_b_ _computeFrequency(XNA setSeq, XNAseq seq);
XNA processSet(XNA seq);
double fatorial(double n);
double probOccBGreater(double Eocc, double T, double n);
double probOccBEq(double Eocc, double T, double n);
double sigValue(double Poccb, int w);
struct ret {
	XNAseq s;
	int i;
};

struct Fe_b_ {
	XNAseq olig;
	double freq;
	double T;
	double Eocccb;
	double Poccb_eq;
	double Poccb_great;
	double sig;

};

int main() {

	//char* finFSA = "cr25s.fsa";
	//char* finFSA = "example.fasta";
	char* finFSA = "oligo.fasta";
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
	prefix.set_seq("TTT");
//	int sizeP = 4;
	//int res = totalDistance(prefix,s1,sizeP);
	//cout <<"Resp " <<res <<endl;
//    struct ret r = bypass(prefix,2);
	//   cout << r.s.seq << ' ' << r.i << endl;

	/*
	 struct ret r;
	 r.s = prefix;
	 r.i = 0;
	 int k = 1;
	 while (r.i != -1){
	 r = nextVertex(r.s,r.i,4);
	 cout  << r.s.seq << ' ' << r.i << ' ' << k << endl;
	 k++;
	 }
	 */

	/*
	 // teste NextLeaf
	 int k = 1;
	 while(k < 256){
	 prefix = nextLeaf(prefix,4);
	 cout  << prefix.seq << ' ' << k << endl;
	 k++;
	 }
	 */
	// teste allLeaves
	/*
	 for (int j = 1; j < 10; ++j) {
	 allLeaves(j);
	 }
	 */

	// teste _computeFrequency
	/*
	 struct Fe_b_ Feb;
	 Feb = _computeFrequency(s1,prefix);
	 cout << Feb.olig.seq << ' ' <<  Feb.freq << endl;
	 */

	// teste computeFrequency
	vector<struct Fe_b_> Feb;
	vector<struct Fe_b_>::iterator it;
	s1 = processSet(s1);
	Feb = computeFrequency(s1, 3000, 6);
//	cout << Feb.size() << endl;
//	for (it = Feb.begin(); it < Feb.end(); ++it) {
//		cout << it->olig.seq << ' ' << it->T << ' ' << it->freq << ' '
//				<< it->Eocccb << ' ' << it->Poccb_eq << ' ' << it->Poccb_great
//				<< ' ' << it->sig << endl;
//	}

	// teste double sigValue(double Poccb, int w)
	//cout  << sigValue( 44, 6) << endl;
	// teste processSet(s1);
	/*
	 s1 = processSet(s1);
	 int numberOfSequences=s1.chain.size();
	 cout << numberOfSequences << endl;

	 for (int i=0; i<numberOfSequences; i++) {
	 string mainSEQ=s1.chain[i].seq;
	 string mainid=s1.chain[i].id;
	 string maindesc=s1.chain[i].description;
	 int lenSeq=s1.chain[i].length();
	 cout << mainid << endl << maindesc << endl << lenSeq << mainSEQ <<endl << endl;

	 }
	 */
	// teste double probOccBEq(double Eocc, double T, double n)
	/*
	 double Eocc = 12;
	 double T = 15;
	 double n = 15;
	 double res = probOccBEq(Eocc, T, n);
	 cout << res << endl;
	 */

	// teste double probOccBGreater(double Eocc, double T, double n)
	/*
	 double res = probOccBGreater(12,15,10);
	 cout << res << endl;
	 */

//	prefix = medianString(s1, 8, 4);
//	cout << prefix.seq << endl;
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

XNAseq nextLeaf(XNAseq a, int L) {
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
	XNAseq s;
	for (int k = 0; k < L; ++k) {
		s.seq = s.seq + 'A';
	}
	int i = 0;
	int cont = pow(4, L);
	while (i < cont) {
		cout << s.seq << ' ' << i << endl;
		s = nextLeaf(s, L);
		i++;
	}
}

vector<struct Fe_b_> computeFrequency(XNA seq, double n, int len) {
	vector<struct Fe_b_> Feb;
	struct Fe_b_ Fq;
	int S = seq.chain.size();
	int L = seq.chain[0].length();
	cout << L <<endl;
	//	for (int j = 1; j < 10; ++j) {
		XNAseq s;
		for (int k = 0; k < len; ++k) {
			s.seq = s.seq + 'A';
		}
		int i = 0;
		int cont = pow(4, len);
		while (i < cont) {
			Fq = _computeFrequency(seq, s);
			if (Fq.freq != 0) {
				Fq.T = 2 * S * (L - Fq.olig.seq.length() + 1);
				Fq.Eocccb = Fq.freq * Fq.T;
				Fq.Poccb_eq = probOccBEq(Fq.Eocccb, Fq.T, n);
				Fq.Poccb_great = probOccBGreater(Fq.Eocccb, Fq.T, n);
				Fq.sig = sigValue(Fq.Poccb_great, Fq.olig.seq.length());
				cout << Fq.olig.seq << ' ' << Fq.T << ' ' << Fq.freq << ' '
								<< Fq.Eocccb << ' ' << Fq.Poccb_eq << ' ' << Fq.Poccb_great
								<< ' ' << Fq.sig << endl;
				Feb.push_back(Fq);
			}
			s = nextLeaf(s, len);
			i++;
		}
//	}
	return Feb;
}

double probOccBEq(double Eocc, double T, double n) {
	double TFactorial = fatorial(T);
	double T_minus_n = fatorial((T - n));
	double fatorial_n = fatorial(n);

	double p_Eocc = pow(Eocc, n);
	double p2_Eocc = pow((1 - Eocc), (T - n));

	double partialResul = TFactorial / (T_minus_n * fatorial_n);
	double resul = partialResul * p_Eocc * p2_Eocc;
	return resul;
}

double probOccBGreater(double Eocc, double T, double n) {
	double sum = 0;
	for (int j = n; j <= T; ++j) {
		sum = sum + probOccBEq(Eocc, T, j);
	}
	return (sum);
}

double sigValue(double Poccb, int w) {
	double D = pow(4, w) - ((pow(4, w) - pow(4, (w / 2)))/2);
	double sig = -log10(Poccb * D);
	return sig;
}

double fatorial(double x) {
	if (x == 0 || x == 1)
		return 1;
	else
		return (x * fatorial(x - 1));
}

struct Fe_b_ _computeFrequency(XNA setSeq, XNAseq seq) {
	int dist = 0;
	double freq = 0;
	struct Fe_b_ Feb;
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
	Feb.olig = seq;
	Feb.freq = freq; //(freq/(setSeq.chain.size() * numberOfSequences));
	return Feb;
}

XNA processSet(XNA seq) {
	int numberOfSequences = seq.chain.size();
	int length = 0;
	int lengthAux = 0;
	length = seq.chain[0].length();

	for (int i = 1; i < numberOfSequences; i++) {
		lengthAux = seq.chain[i].length();
		if (lengthAux < length) {
			length = lengthAux;
		}
	}

	for (int j = 0; j < numberOfSequences; j++) {
		seq.chain[j].seq.erase(seq.chain[j].seq.begin() + length,
				seq.chain[j].seq.end());
	}
	return seq;
}
