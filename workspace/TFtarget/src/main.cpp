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
#include "medianString.h"
#include "OligoAnalisys.h"
#include "HexDiff.h"
#include "MotifAlgo.h"

using namespace std;

DNA processSet(DNA seq);

int main(int argc, char *argv[]) {

		DNA posSeq;
		DNA learningSeq;
		DNA negSeq;
		int num = 106;
for (int i = 0; i < 12; ++i) {

	//posSeq.readFasta("../entrada/sampling_"+intToString(num)+".fasta");
	posSeq.readFasta("../entrada/resultado_"+intToString(num)+".fasta");
	learningSeq.readFasta("../entrada/sampling_"+intToString(num)+".fasta");
	negSeq.readFasta("../entrada/ramdomSet_"+intToString(num)+".fasta");

	OligoAnalisys *olig = new OligoAnalisys();
	list<CalculatedOligo> l = olig->performAnalysis(posSeq,learningSeq, 80, 6);
	l = olig->selectOlig(l);
	olig->writeFrameSetCSV("../saida/saidaMarkov_"+intToString(num)+".csv",olig->computeScore(l,posSeq,negSeq));
	num += 50;
	posSeq.chain.clear();
	negSeq.chain.clear();
	learningSeq.chain.clear();
}
cout << num - 50 << endl;
	return 0;
}


DNA processSet(DNA seq) {
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
