/*
 * HexDiff.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#include "HexDiff.h"

HexDiff::HexDiff(DNA posSet, DNA negSet, DNA testSet, int lengthHd,
		int windowSize, double threshold) {
	this->posSet = posSet;
	this->negSet = negSet;
	this->testSet = testSet;
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

	for (int m = 0; m < (2 * posSetLength); ++m) {
		//posSet.addSeq(posSet.chain[m].compliment());
		 seqSizePos = seqSizePos + posSet.chain[m].length();

	}

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
		HexRatio hexR(seq, freq/seqSizePos);
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
		HexRatio hexR(seq, freq/seqSizeNeg);
		HdNeg.push_back(hexR);
	}
	file.close();

	DNAseq s;
	// First hexamer to compute
	s.seq = "AAAAAA";
	double ratio = 0;
	int i = 0;
	int cont = pow(4.0, 6);
	list<HexRatio>::iterator it;
	while (i < cont) {
		for (it = HdPos.begin(); it != HdPos.end(); ++it) {
			if (it->getHex().seq == s.seq) {
				posFq = it->getRatio();
				HdPos.erase(it);
				break;
			}
		}

		for (it = HdNeg.begin(); it != HdNeg.end(); ++it) {
			if (it->getHex().seq == s.seq) {
				negFq = it->getRatio();
				HdNeg.erase(it);
				break;
			}
		}

		// find the ratio between positive and negative set
		if (posFq == 0 ) {
			ratio = 0;
		} else if(negFq == 0){
			ratio = 0;
		}
		else {
			ratio = posFq / negFq;
		}

		HexRatio hexR(s, ratio);
		Hd.push_back(hexR);
		s = nextLeaf(s, 6);
		i++;
		posFq = 0;
		negFq = 0;
	}

}

void HexDiff::loocv() {
	ifstream file;
	string line;
	double freq;
	file.open("hexdiff", ios::in);
	while (file.good()) {
		getline(file, line);
		DNAseq seq;
		seq.seq = line;
		getline(file, line);
		freq = atof(line.c_str());
		HexRatio hexR(seq, freq);
		Hd.push_back(hexR);
	}
	file.close();
}

void HexDiff::chooseHexamers() {
	Hd.sort(compareRatio);
	list<HexRatio>::iterator it1, it2;
	it1 = Hd.begin();
	it2 = Hd.end();
	advance(it1, lengthHd);
	Hd.erase(it1, it2);
}

void HexDiff::computeScore() {
	DNA tmpSet;
	DNAseq tmpSeq;
	list<HexRatio>::iterator it;
	Freq freq;
	double sum = 0;

	cout << "teste seq tam " << testSet.chain[0].length()<<endl;

	for (int i  = 0; i < ((testSet.chain[0].length() - windowSize) + 1); ++i) {
		tmpSeq.seq = testSet.chain[0].seq.substr(i, windowSize);
		tmpSet.addSeq(tmpSeq);
		// Compute the frequency for each Hd in the test Set
		for (it = Hd.begin(); it != Hd.end(); ++it) {
			freq = computeFrequency(tmpSet, it->getHex());
			sum = sum + (freq.freq * it->getRatio());
		}
		if (sum > threshold) {
			Score s(i, sum);
			scoreList.push_back(s);
		}
		tmpSeq.clear();
		tmpSet.chain.clear();
		sum = 0;
	}
}

/*
 void HexDiff::computeScore() {
 XNA tmpSet;
 XNAseq tmpSeq;
 list<HexRatio>::iterator it;
 double freq;
 ifstream file;
 string line;
 vector<HexRatio> HdTmp;
 vector<HexRatio>::iterator itHT;
 double sum = 0;
 for (int i = 0; i < ((testSet.chain[0].length() - windowSize) + 1); ++i) {
 tmpSeq.seq = testSet.chain[0].seq.substr(i, windowSize);
 tmpSet.addSeq(tmpSeq);
 tmpSet.writeFasta("tmp.fasta");

 // compute positive frequency
 system("./meryl -B -m 6 -s tmp.fasta -o tmp");
 system("./meryl -Dt -s tmp > tmpOut");
 file.open("tmpOut", ios::in);
 while (file.good()) {
 getline(file, line);
 line.erase(0, 1);
 freq = atof(line.c_str());
 getline(file, line);
 XNAseq seq;
 seq.seq = line;
 HexRatio hexR(seq, freq);
 HdTmp.push_back(hexR);
 }
 file.close();

 // Compute the frequency for each Hd in the test Set
 for (itHT = HdTmp.begin(); itHT != HdTmp.end(); ++itHT) {
 for (it = Hd.begin(); it != Hd.end(); ++it) {
 if ( it->getHex().seq == itHT->getHex().seq){
 sum = sum + (itHT->getRatio() * it->getRatio());
 }
 }
 }
 if (sum > threshold) {
 Score s(i, sum);
 scoreList.push_back(s);
 }
 tmpSeq.clear();
 tmpSet.chain.clear();
 sum = 0;
 HdTmp.clear();
 }
 }
 */

void HexDiff::printHd() {
	list<HexRatio>::iterator it;
	for (it = Hd.begin(); it != Hd.end(); ++it) {
		cout << it->getHex().seq << ' ' << it->getRatio() << endl;
	}
}

void HexDiff::printScore() {
	list<Score>::iterator it;
	for (it = scoreList.begin(); it != scoreList.end(); ++it) {
		cout << "position: " << it->getPosition() << "   score: "
				<< it->getScore() << endl;
	}
}
/********************
 * HexRatio Methods *
 ********************/
HexRatio::HexRatio(DNAseq hex, double ratio) {
	this->hex = hex;
	this->ratio = ratio;
}
DNAseq HexRatio::getHex() const {
	return hex;
}

double HexRatio::getRatio() const {
	return ratio;
}

void HexRatio::setHex(DNAseq hex) {
	this->hex = hex;
}

void HexRatio::setRatio(double ratio) {
	this->ratio = ratio;
}

/*****************
 * Score Methods *
 *****************/
Score::Score(int position, double score) {
	this->position = position;
	this->score = score;
}

int Score::getPosition() const {
	return position;
}

double Score::getScore() const {
	return score;
}

void Score::setPosition(int position) {
	this->position = position;
}

void Score::setScore(double score) {
	this->score = score;
}

bool compareRatio(HexRatio first, HexRatio second) {
	if (first.getRatio() > second.getRatio()) {
		return true;
	} else {
		return false;
	}

}