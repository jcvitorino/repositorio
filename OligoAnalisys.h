/*
 * OligoAnalisys.h
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#ifndef OLIGOANALISYS_H_
#define OLIGOANALISYS_H_

#include "medianString.h"

using namespace std;

class CalculatedOligo: public kmerFreq {
private:
	double exp_freq;
	double exp_occ;
	double occ_P;
	double occ_E;
	double occ_sig;
	vector<string> positonOcc;
public:
	CalculatedOligo();
	virtual ~CalculatedOligo();
	double getExpFreq() const;
	double getExpOcc() const;
	double getOccE() const;
	double getOccP() const;
	double getOccSig() const;
	void setExpFreq(double exp_freq);
	void setExpOcc(double exp_occ);
	void setOccE(double occ_E);
	void setOccP(double occ_P);
	void setOccSig(double occ_sig);
	void addPositonOcc(string seqId,int start, int end);
	void clearPositionOcc();
	vector<string> getPositionOcc();
	void printPositionOcc();


};

class OligoAnalisys: public MotifAlgo {
public:
	OligoAnalisys();
	virtual ~OligoAnalisys();
	list<CalculatedOligo> performAnalysis(DNA seq, DNA learningSeq, double n,
			int len);
	double binomialPValue(double T, double Eocc, double n);
	double probOccBGreater(double Eocc, double T, double n);
	double sigValue(double Poccb, int w);
	list<CalculatedOligo> selectOlig(list<CalculatedOligo>);
	void printCalculatedOligoModel(list<CalculatedOligo>);
	list<CalculatedOligo> findInSeq(list<CalculatedOligo>,DNA seq,int len);
	void printFindOlig(list<CalculatedOligo>);
};

extern bool compareOccSig(CalculatedOligo first, CalculatedOligo second);
extern string intToString(int);
#endif /* OLIGOANALISYS_H_ */
