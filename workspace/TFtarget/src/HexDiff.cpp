/*
 * HexDiff.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#include "HexDiff.h"

HexDiff::HexDiff(DNA posSet, DNA negSet, int lengthHd, int windowSize,
		double threshold) {
	this->posSet = posSet;
	this->negSet = negSet;

	this->lengthHd = lengthHd;
	this->windowSize = windowSize;
	this->threshold = threshold;
}

HexDiff::~HexDiff() {
	// TODO Auto-generated destructor stub
}

void HexDiff::performFrequency() {
	double posFq = 0;
	double negFq = 0;
	int posSetLength = posSet.chain.size();
	int negSetLength = negSet.chain.size();
	int seqSizePos = 0;
	int seqSizeNeg = 0;
	ifstream file;
	string line;
	double freq;

	//Add the compliment on the positive sequence set
	for (int m = 0; m < posSetLength; ++m) {
		//posSet.addSeq(posSet.chain[m].compliment());
		posSet.addSeq(posSet.chain[m].reverse_compliment());
	}

	//Add the compliment on the negative sequence set
	for (int n = 0; n < negSetLength; ++n) {
		//negSet.addSeq(negSet.chain[n].compliment());
		negSet.addSeq(negSet.chain[n].reverse_compliment());
	}

	// Calcula o tamanho da do conjunto positivo
	for (int m = 0; m < (2 * posSetLength); ++m) {
		//posSet.addSeq(posSet.chain[m].compliment());
		seqSizePos = seqSizePos + posSet.chain[m].length();

	}
	// Calcula o tamanho da do conjunto negativo
	for (int m = 0; m < (2 * negSetLength); ++m) {
		//posSet.addSeq(posSet.chain[m].compliment());
		seqSizeNeg = seqSizeNeg + negSet.chain[m].length();

	}
	posSet.writeFasta("posSet.fasta");
	negSet.writeFasta("negSet.fasta");

	// compute positive frequency
	system("./meryl -B -m 6 -s posSet.fasta -o posSet");
	system("./meryl -Dt -s posSet > posSetOut");
	file.open("posSetOut", ios::in);
	while (file.good()) {
		getline(file, line);
		line.erase(0, 1);
		freq = atof(line.c_str());
		getline(file, line);
		DNAseq seq;
		seq.seq = line;
		HexValue hexR(seq, freq / seqSizePos);
		HdPos.push_back(hexR);
	}
	file.close();

	// compute negative frequency
	system("./meryl -B -m 6 -s negSet.fasta -o negSet");
	system("./meryl -Dt -s negSet > negSetOut");
	file.open("negSetOut", ios::in);
	while (file.good()) {
		getline(file, line);
		line.erase(0, 1);
		freq = atof(line.c_str());
		getline(file, line);
		DNAseq seq;
		seq.seq = line;
		HexValue hexR(seq, freq / seqSizeNeg);
		HdNeg.push_back(hexR);
	}
	file.close();

	DNAseq s;
	// First hexamer to compute
	s.seq = "AAAAAA";
	double ratio = 0;
	int i = 0;
	int cont = pow(4.0, 6);
	list<HexValue>::iterator it;
	while (i < cont) {
		for (it = HdPos.begin(); it != HdPos.end(); ++it) {
			if (it->getHex().seq == s.seq) {
				posFq = it->getValue();
				HdPos.erase(it);
				break;
			}
		}

		for (it = HdNeg.begin(); it != HdNeg.end(); ++it) {
			if (it->getHex().seq == s.seq) {
				negFq = it->getValue();
				HdNeg.erase(it);
				break;
			}
		}

		// find the ratio between positive and negative set
		if (posFq == 0) {
			ratio = 0;
		} else if (negFq == 0) {
			ratio = 0;
		} else {
			ratio = posFq / negFq;
		}

		HexValue hexR(s, ratio);
		Hd.push_back(hexR);
		s = nextLeaf(s, 6);
		i++;
		posFq = 0;
		negFq = 0;
	}

}

void HexDiff::chooseHexamers() {
	Hd.sort(compareRatio);
	list<HexValue>::iterator it1, it2;
	it1 = Hd.begin();
	it2 = Hd.end();
	advance(it1, lengthHd);
	Hd.erase(it1, it2);
}

vector<Frame> HexDiff::computeScore() {
	vector<Frame> frameSet;
	DNA tmpSet;
	DNAseq tmpSeq;
	vector<HexValue> hexValue;
	list<HexValue>::iterator it;
	vector<DNAseq>::iterator it2;
	double occ = 0.0;
	for (it2 = posSet.chain.begin(); it2 != posSet.chain.end(); it2++) {
		for (it = Hd.begin(); it != Hd.end(); ++it) {
			occ = computeOccurencies((*it2), it->getHex());
			hexValue.push_back(HexValue(it->getHex(),(occ * it->getValue())));
		}
		frameSet.push_back(Frame((*it2),hexValue,1));
		hexValue.clear();
	}

	for (it2 = negSet.chain.begin(); it2 != negSet.chain.end(); it2++) {
		for (it = Hd.begin(); it != Hd.end(); ++it) {
			occ = computeOccurencies((*it2), it->getHex());
			hexValue.push_back(HexValue(it->getHex(),(occ * it->getValue())));
		}
		frameSet.push_back(Frame(*(it2),hexValue,-1));
		hexValue.clear();
	}

	return frameSet;
}
void HexDiff::printFrameSet(vector<Frame> frameSet){
	vector<Frame>::iterator it;
	vector<HexValue>::iterator it2;
	string str = "";
	for(it = frameSet.begin(); it != frameSet.end(); it++){
		cout << it->label << ";";
		for(it2 = it->hexScore.begin(); it2 != it->hexScore.end(); it2++){
			cout << it2->getValue() << ";";
			if(it2 == it->hexScore.end() - 1){
				cout << it2->getValue();
			}
		}
		cout << endl;
	}

}
void HexDiff::printHd() {
	list<HexValue>::iterator it;
	for (it = Hd.begin(); it != Hd.end(); ++it) {
		cout << it->getHex().seq << ' ' << it->getValue() << endl;
	}
}
/********************
 * HexRatio Methods *
 ********************/
HexValue::HexValue(DNAseq hex, double ratio) {
	this->hex = hex;
	this->value = ratio;
}
DNAseq HexValue::getHex() const {
	return hex;
}

double HexValue::getValue() const {
	return value;
}

void HexValue::setHex(DNAseq hex) {
	this->hex = hex;
}

void HexValue::setValue(double ratio) {
	this->value = ratio;
}

/*****************
 * FrameScore Methods *
 *****************/
Frame::Frame(DNAseq seq, vector<HexValue> hexScore,int label) {
	this->seq = seq;
	this->hexScore = hexScore;
	this->label = label;
}

bool compareRatio(HexValue first, HexValue second) {
	if (first.getValue() > second.getValue()) {
		return true;
	} else {
		return false;
	}

}
/*

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
*/

double computeOccurencies(DNAseq setSeq, DNAseq seq) {
	double freq = 0;
	for (int j = 0; j < ((setSeq.length() - seq.length()) + 1); j++) {
		int dist = hammingDistance(seq.seq, setSeq.seq.substr(j, seq.length()));
		if (dist == 0) {
			freq++;
		}
	}
	return freq;

}
