//============================================================================
// Name        : DREBSearch.cpp
// Author      : josue
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "HexDiff.h"
#include <string>
using namespace std;

int main() {
	 // conjunto negativo
	char* finFSA2= "ramdomSet3.fasta";
	// conjunto positivo
	char* finFSA = "resultado2.fasta";
	// conjunto positivo
	//char* finFSA = "sampling_500.fasta";
	DNA s1, s2;
	s1.readFasta(finFSA);
	s2.readFasta(finFSA2);
	HexDiff hex(s1, s2, 140, 1200, 150);
	hex.performFrequency();
	hex.chooseHexamers();
	//hex.printHd();
	//cout << "===========================================================\n\n\n";
	hex.printFrameSet(hex.computeScore());
	return 0;
}
