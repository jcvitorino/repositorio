//============================================================================
// Name        : ExtractSequence.cpp
// Author      : josue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "XNA.h"

using namespace std;
void extractSeq(XNA seq,int start, int end);
int main() {
	XNA seq;
	seq.readFasta("file.fasta");
	int start = 15242;
	int end = 20460;
	extractSeq(seq, start, end);
	return 0;
}

void extractSeq(XNA seq, int start, int end){
	int n = end - start;
	string result = seq.chain[0].seq.substr(start - 1,n);
	XNA s;
	XNAseq xseq;
	xseq.seq = result;
	cout << "Gene  " <<seq.chain[0].seq.length() << endl;
	cout << "CRM   " << xseq.length() << endl;
	s.addSeq(xseq);
	s.writeFasta("CRM.fasta");
	/*
tll	15242	17701	tll_K2
tll	17701	20460	tll_P2
tll	19085	20460	tll_P3	 */


	int n1_1 = 16035 - n;
	int n1_2 = 16656 - n;


	int n2_1 = 17462 - ((16656 - 16035) + n);
	int n2_2 = 19015 - ((16656 - 16035) + n);

//	int n3_1 = 27994 - ((27394 - 25794) + (25494 - 24094) + n);
//	int n3_2 = 32794 - ((27394 - 25794) + (25494 - 24094) + n);

	//int n4_1 = 26693 - ((25258 - 24657) + (19132 - 18470) + (16769 - 16259) + n);
	//int n4_2 = 28199 - ((25258 - 24657) + (19132 - 18470) + (16769 - 16259) + n);

//	seq.chain[0].seq.erase(8603 - 2 , (9514 - 8603));
//	seq.chain[0].seq.erase(14320 - 2 , (14883 - 14320));
//	seq.chain[0].seq.erase(9078 - 2 , (10551 - 9078));
	//seq.chain[0].seq.erase(27400 - 2 , (28199 - 27400));
	seq.chain[0].seq.erase(start - 2 , n);
//	seq.chain[0].seq.erase(n1_1 - 2 , (n1_2 - n1_1) );
//	seq.chain[0].seq.erase(n2_1 - 2 , (n2_2 - n2_1) );
//	seq.chain[0].seq.erase(n3_1 - 2 , (n3_2 - n3_1) );
	//seq.chain[0].seq.erase(n4_1 - 2 , (n4_2 - n4_1) );
	cout << "noCRM  " <<seq.chain[0].seq.length() << endl;
	seq.writeFasta("noCRM.fasta");

}
