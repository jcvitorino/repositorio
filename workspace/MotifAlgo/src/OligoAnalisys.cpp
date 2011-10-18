/*
 * OligoAnalisys.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#include "OligoAnalisys.h"

OligoAnalisys::OligoAnalisys() {
	// TODO Auto-generated constructor stub

}

OligoAnalisys::~OligoAnalisys() {
	// TODO Auto-generated destructor stub
}

list<CalculatedOligo> OligoAnalisys::performAnalysis(DNA seq, DNA learningSeq,
		double n, int oligoLength) {

	list<CalculatedOligo> calOlig;
	map<string, kmerFreq> freq;
	map<string, kmerFreq>::iterator it;
	map<string, Prefix> matrix;
	CalculatedOligo olig;
	int S = seq.chain.size();
	int learningSeqSize = 0;
	int T = 0;
	int L = 0;
	int seqTotalsize = 0;

	for (int i = 0; i < learningSeq.chain.size(); ++i) {
		learningSeqSize = learningSeqSize + learningSeq.chain[i].length();
	}

	for (int i = 0; i < S; ++i) {
		L = L + (seq.chain[i].length() - oligoLength + 1);
	}
	T = 2 * L;

	for (int m = 0; m < S; ++m) {
		seq.addSeq(seq.chain[m].reverse_compliment());
	}

	for (int k = 0; k < (2 * S); ++k) {
		seqTotalsize = seqTotalsize + seq.chain[k].length();
	}

	cout << " L " << L << endl;
	cout << " T " << T << endl;
	cout << " learningSeqSize " << learningSeqSize << endl;
	cout << " seqTotalsize " << seqTotalsize << endl;

	freq = computeTotalFrequency(learningSeq, 3, learningSeqSize);
	matrix = buildTransitionTable(freq);
	freq = computeTotalFrequency(seq, 6, seqTotalsize);

	for (it = freq.begin(); it != freq.end(); ++it) {
		olig.setOlig(it->second.getOlig());
		olig.setFreq(it->second.getFreq());
		olig.setOccurrences(it->second.getOccurrences());
		olig.setExpFreq(scoreSeqMarkov(it->second.getOlig(), 2, matrix));
		olig.setExpOcc(olig.getExpFreq() * T);
		olig.setOccP(
				binomialPValue(T, olig.getExpFreq(),
						it->second.getOccurrences()));
		olig.setOccE(
				probOccBGreater(olig.getExpFreq(), T,
						it->second.getOccurrences()));
		olig.setOccSig(sigValue(olig.getOccE(), oligoLength));
		calOlig.push_back(olig);
		/*
		 cout << "Seq " << olig.getOlig().seq
		 << " freq " << olig.getFreq()
		 << "  exp_freq " << olig.getExpFreq() << " occ "
		 << olig.getOccurrences() << " exp_occ " << olig.getExpOcc()
		 << " Binomial " << olig.getOccP() << " Occ_E " << olig.getOccE()
		 << " sig " << olig.getOccSig() << endl;
		 */
	}
	calOlig.sort(compareOccSig);
	return calOlig;
}

list<CalculatedOligo> OligoAnalisys::selectOlig(list<CalculatedOligo> l) {
	list<CalculatedOligo> ret;
	list<CalculatedOligo>::iterator it;
	for (it = l.begin(); it != l.end(); ++it) {
		if (it->getOccSig() > 0) {
			ret.push_back(*(it));
		}
	}
	return ret;
}

void OligoAnalisys::printCalculatedOligo(list<CalculatedOligo> l) {
	list<CalculatedOligo>::iterator it;
	for (it = l.begin(); it != l.end(); ++it) {
		cout << "Seq " << it->getOlig().seq << " freq " << it->getFreq()
				<< "  exp_freq " << it->getExpFreq() << " occ "
				<< it->getOccurrences() << " exp_occ " << it->getExpOcc()
				<< " occ_P " << it->getOccP() << " Occ_E " << it->getOccE()
				<< " sig " << it->getOccSig() << endl;
	}
}
double OligoAnalisys::binomialPValue(double T, double Eocc, double n) {
	vector<double> calc(n + 1);
	for (int i = 0; i < n + 1; ++i) {
		if (i == 0) {
			calc[i] = pow(1 - Eocc, T);
		} else {
			calc[i] = calc[i - 1] * ((T - (i - 1)) * Eocc)
					/ (((i - 1) + 1) * (1 - Eocc));
		}
	}
	return calc.back();
}

double OligoAnalisys::probOccBGreater(double Eocc, double T, double n) {
	double sum = 0;
	for (int j = 0; j <= n - 1; ++j) {
		sum = sum + binomialPValue(T, Eocc, j);
	}
	return (1 - sum);
}

double OligoAnalisys::sigValue(double Poccb, int w) {
	double D = pow(4.0, w) - ((pow(4.0, w) - pow(4.0, (w / 2)))/2);
	double sig = -log10(Poccb * D);
	return sig;
}

/**
 * CalculatedOligo
 */

CalculatedOligo::CalculatedOligo() {

}

CalculatedOligo::~CalculatedOligo() {

}

double CalculatedOligo::getExpFreq() const {
	return exp_freq;
}

double CalculatedOligo::getExpOcc() const {
	return exp_occ;
}

double CalculatedOligo::getOccE() const {
	return occ_E;
}

double CalculatedOligo::getOccP() const {
	return occ_P;
}

double CalculatedOligo::getOccSig() const {
	return occ_sig;
}

void CalculatedOligo::setExpFreq(double exp_freq) {
	this->exp_freq = exp_freq;
}

void CalculatedOligo::setExpOcc(double exp_occ) {
	this->exp_occ = exp_occ;
}

void CalculatedOligo::setOccE(double occ_E) {
	this->occ_E = occ_E;
}

void CalculatedOligo::setOccP(double occ_P) {
	this->occ_P = occ_P;
}

void CalculatedOligo::setOccSig(double occ_sig) {
	this->occ_sig = occ_sig;
}

bool compareOccSig(CalculatedOligo first, CalculatedOligo second) {
	if (first.getOccSig() > second.getOccSig()) {
		return true;
	} else {
		return false;
	}

}