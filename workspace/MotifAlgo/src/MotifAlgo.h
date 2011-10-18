/*
 * MotifAlgo.h
 *
 *  Created on: 01/08/2011
 *      Author: josue
 */

#ifndef MOTIFALGO_H_
#define MOTIFALGO_H_

#include  "DNA.h"
#include <map>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
#include <list>
#include <vector>
#include "medianString.h"
using namespace std;

class kmerFreq {
private:
	DNAseq olig;
	double occurrences;
	double freq;
public:
	kmerFreq();
	kmerFreq(DNAseq olig , double occurrences , double freq );
	virtual ~kmerFreq();
	double getFreq() const;
	double getOccurrences() const;
	DNAseq getOlig() const;
	void setFreq(double freq);
	void setOccurrences(double occurrences);
	void setOlig(DNAseq olig);
};

class Prefix {
private:
	string prefix;
	double total;
	double suffix_A;
	double suffix_C;
	double suffix_G;
	double suffix_T;
public:
	Prefix();
	Prefix(string prefix, double suffix_A, double suffix_C, double suffix_G,
			double suffix_T, double total);
	virtual ~Prefix();
	string getPrefix() const;
	double getSuffixA() const;
	double getSuffixC() const;
	double getSuffixG() const;
	double getSuffixT() const;
	double getPrefixTotal() const;
	void setPrefix(string prefix);
	void setSuffixA(double suffix_A);
	void setSuffixC(double suffix_C);
	void setSuffixG(double suffix_G);
	void setSuffixT(double suffix_T);
	void setPrefixTotal(double total);

};

class MotifAlgo {
public:
	MotifAlgo();
	virtual ~MotifAlgo();
	map<string, kmerFreq> computeTotalFrequency(DNA setSeq, int kmer,
			double setSeqSize);
	kmerFreq computeMotifFrequency(DNA setSeq, DNAseq seq);
	map<string, Prefix> buildTransitionTable(map<string, kmerFreq> frequencies);
	long double scoreSeqMarkov(DNAseq seq, int order,map<string, Prefix> transMatrix);

};

#endif /* MOTIFALGO_H_ */
