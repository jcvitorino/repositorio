/*
 * HexDiff.h
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#ifndef HEXDIFF_H_
#define HEXDIFF_H_

#include "medianString.h"

class HexRatio {
private:
	DNAseq hex;
	double ratio;
public:
	HexRatio(DNAseq hex, double ratio);
	DNAseq getHex() const;
	double getRatio() const;
	void setHex(DNAseq hex);
	void setRatio(double ratio);
};

class Score {
private:
	int position;
	double score;
public:
	Score(int position,double score);
	int getPosition() const;
	double getScore() const;
	void setPosition(int position);
	void setScore(double score);
};

class HexDiff {
public:
	HexDiff(DNA posSet, DNA negSet, DNA testSet, int lengthHd, int windowSize, double threshold);
	virtual ~HexDiff();
	DNA posSet; // Positive Set
	DNA negSet; // Negative Set
	DNA testSet;
	list<HexRatio> Hd;
	list<HexRatio> HdPos;
	list<HexRatio> HdNeg;
	double threshold;
	int lengthHd;
	int windowSize;
	list<Score> scoreList;
	void performFrequency();
	void chooseHexamers();
	void computeScore();
	void printHd();
	void printScore();
	void loocv();
};

extern bool compareRatio(HexRatio first, HexRatio second);
#endif /* HEXDIFF_H_ */
