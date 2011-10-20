/*
 * medianString.h
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#ifndef MEDIANSTRING_H_
#define MEDIANSTRING_H_
#include "MotifAlgo.h"

using namespace std;

struct ret {
	DNAseq s;
	int i;
};

struct Freq{
	DNAseq olig;
	double freq;

};


int hammingDistance(string s, string t);
int totalDistance(DNAseq prefix, DNA seq, int sizeP);
struct ret bypass(DNAseq a, int i);
struct ret nextVertex(DNAseq a, int i, int L);
DNAseq medianString(DNA seq, int L, int mis);
DNAseq nextLeaf(DNAseq a, int L);
void allLeaves(int L);
struct Freq computeFrequency(DNA setSeq, DNAseq seq);

#endif /* MEDIANSTRING_H_ */
