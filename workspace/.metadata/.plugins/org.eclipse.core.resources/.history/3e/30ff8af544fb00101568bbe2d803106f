/*
 * HexDiff.h
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#ifndef HEXDIFF_H_
#define HEXDIFF_H_

#include <list>
#include <cmath>
#include "DNA.h"
using namespace std;

class HexValue {
private:
	DNAseq hex;
	double value;
public:
	HexValue(DNAseq hex, double value);
	DNAseq getHex() const;
	double getValue() const;
	void setHex(DNAseq hex);
	void setValue(double ratio);
};

class Frame {
public:
	DNAseq seq;
	vector<HexValue> hexScore;
	int label;
	Frame(DNAseq seq, vector<HexValue> hexScore,int label);
	double totalScore();
};

class HexDiff {
public:
	HexDiff(DNA posSet, DNA negSet, int lengthHd, int windowSize,
			double threshold);
	virtual ~HexDiff();
	DNA posSet; // Positive Set
	DNA negSet; // Negative Set
	list<HexValue> Hd;
	list<HexValue> HdPos;
	list<HexValue> HdNeg;
	double threshold;
	int lengthHd;
	int windowSize;
	list<Frame> scoreList;
	void performFrequency();
	void chooseHexamers();
	vector<Frame> computeScore();
	void printHd();
	void printFrameSet(vector<Frame>);
};

extern bool compareRatio(HexValue first, HexValue second);
extern DNAseq nextLeaf(DNAseq a, int L);
extern int hammingDistance(string s, string t);
extern double computeOccurencies(DNAseq setSeq, DNAseq seq);
#endif /* HEXDIFF_H_ */
