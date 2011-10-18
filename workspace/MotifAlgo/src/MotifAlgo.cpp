/*
 * MotifAlgo.cpp
 *
 *  Created on: 01/08/2011
 *      Author: josue
 */

#include "MotifAlgo.h"
/**
 * KmerFreq
 */
kmerFreq::kmerFreq() {
}

kmerFreq::kmerFreq(DNAseq olig, double occurrences = 0.0, double freq = 0.0) {
	this->olig = olig;
	this->occurrences = occurrences;
	this->freq = freq;
}

kmerFreq::~kmerFreq() {
}

double kmerFreq::getFreq() const {
	return freq;
}

double kmerFreq::getOccurrences() const {
	return occurrences;
}

DNAseq kmerFreq::getOlig() const {
	return olig;
}

void kmerFreq::setFreq(double freq) {
	this->freq = freq;
}

void kmerFreq::setOccurrences(double occurrences) {
	this->occurrences = occurrences;
}

void kmerFreq::setOlig(DNAseq olig) {
	this->olig = olig;
}

/**
 * prefix
 */

Prefix::Prefix() {

}
Prefix::Prefix(string prefix, double suffix_A, double suffix_C, double suffix_G,
		double suffix_T, double total) {
	this->prefix = prefix;
	this->suffix_A = suffix_A;
	this->suffix_C = suffix_C;
	this->suffix_G = suffix_G;
	this->suffix_T = suffix_T;
	this->total = total;
}
Prefix::~Prefix() {

}

string Prefix::getPrefix() const {
	return prefix;
}

double Prefix::getSuffixA() const {
	return suffix_A;
}

double Prefix::getSuffixC() const {
	return suffix_C;
}

double Prefix::getSuffixG() const {
	return suffix_G;
}

double Prefix::getSuffixT() const {
	return suffix_T;
}

double Prefix::getPrefixTotal() const {
	return total;
}

void Prefix::setPrefix(string prefix) {
	this->prefix = prefix;
}

void Prefix::setSuffixA(double suffix_A) {
	this->suffix_A = suffix_A;
}

void Prefix::setSuffixC(double suffix_C) {
	this->suffix_C = suffix_C;
}

void Prefix::setSuffixG(double suffix_G) {
	this->suffix_G = suffix_G;
}

void Prefix::setSuffixT(double suffix_T) {
	this->suffix_T = suffix_T;
}

void Prefix::setPrefixTotal(double total) {
	this->total = total;
}

/**
 * MotifAlgo
 */

MotifAlgo::MotifAlgo() {
	// TODO Auto-generated constructor stub

}

MotifAlgo::~MotifAlgo() {
	// TODO Auto-generated destructor stub
}

map<string, kmerFreq> MotifAlgo::computeTotalFrequency(DNA setSeq, int kmer,
		double setSeqSize) {
	map<string, kmerFreq> frequencies;
	ifstream file;
	string line;
	double occ;
	DNAseq olig;
	ostringstream stm;
	stm << kmer;
	setSeq.writeFasta("tmp.fasta");
	string str = "./meryl -B -m " + stm.str() + " -s tmp.fasta -o tmpSet";
	system(str.c_str());
	system("./meryl -Dt -s tmpSet > tmpSetOut");
	file.open("tmpSetOut", ios::in);
	while (file.good()) {
		getline(file, line);
		if (line.empty()) {
			continue;
		}
		line.erase(0, 1);
		occ = atof(line.c_str());
		getline(file, line);
		olig.seq = line;
		frequencies[line] = kmerFreq(olig, occ, (occ / setSeqSize));
	}
	return frequencies;
}

map<string, Prefix> MotifAlgo::buildTransitionTable(map<string, kmerFreq> frequencies) {
	map<string, Prefix> transMatrix;
	map<string, kmerFreq>::iterator it = frequencies.begin();
	int prefixLength = it->first.length() - 1;
	int cont = pow(4.0, prefixLength);
	DNAseq s;
	string seq = "";
	double total = 0;
	double A = 0, C = 0, G = 0, T = 0;
	for (int k = 0; k < prefixLength; ++k) {
		s.seq = s.seq + 'A';
	}

	for (int i = 0; i < cont; ++i) {

		seq = s.seq;
		seq = seq + "A";
		A = frequencies[seq].getFreq();

		seq = s.seq;
		seq = seq + "C";
		C = frequencies[seq].getFreq();

		seq = s.seq;
		seq = seq + "G";
		G = frequencies[seq].getFreq();

		seq = s.seq;
		seq = seq + "T";
		T = frequencies[seq].getFreq();

		total = A + C + G + T;
		A = A / total;
		C = C / total;
		G = G / total;
		T = T / total;

		transMatrix[s.seq] = Prefix(s.seq, A, C, G, T, total);

		s = nextLeaf(s, prefixLength);
	}
	return transMatrix;
}

long double MotifAlgo::scoreSeqMarkov(DNAseq seq, int order, map<string, Prefix> transMatrix) {
	string s = seq.seq;
	string prefix = s.substr(0, order);

	long double prod = 0.0;
	prod = transMatrix[prefix].getPrefixTotal();
	for (int i = order; i < seq.length(); ++i) {
		prefix = s.substr(i - order, order);
		if (s[i] == 'A') {
			prod = prod * transMatrix[prefix].getSuffixA();
		} else if (s[i] == 'C') {
			prod = prod * transMatrix[prefix].getSuffixC();
		} else if (s[i] == 'G') {
			prod = prod * transMatrix[prefix].getSuffixG();
		} else if (s[i] == 'T') {
			prod = prod * transMatrix[prefix].getSuffixT();
		}

	}
	return prod;

}