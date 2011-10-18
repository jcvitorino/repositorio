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
	if (argv[1][0] == '1') {
		char* finFSA2 = "noCRM_L.fasta"; // conjunto negativo
		//char* finFSA2 = "ramdomSet.fasta";
		//char* finFSA = "../src/hexx.fasta";
		char* finFSA3 = "seqt.fasta"; // conjunto teste
		//char* finFSA = "example.fasta";
		//char* finFSA2 = "oligo.fasta";
		char* finFSA = "dros.fasta"; // conjunto positivo
		//char* finFSA = "resultado.fasta"; // conjunto positivo
		//char* finFSA = "sampling_500.fasta";
		DNA s1, s2, s3;
		s1.readFasta(finFSA);
		s2.readFasta(finFSA2);
		s3.readFasta(finFSA3);
		HexDiff hex(s1, s2, s3, 156, 1200, 150);
		hex.performFrequency();
		//hex.loocv();
		hex.chooseHexamers();
		hex.printHd();
		cout << "\n\n\n\n" << "-----------------------------------" << endl;
		//hex.computeScore();
		//hex.printScore();
		/*
		 hex.chooseHexamers();
		 hex.printHd();
		 cout << "\n\n\n\n" << "-----------------------------------" << endl;
		 hex.computeScore();
		 hex.printScore();
		 */
	} else if (argv[1][0] == '2') {
		cout << "Oligo-Analisys" << endl;
		//char* finFSA4 = "cr25s.fasta";
		//char* finFSA4 = "oligo.fasta";
		char* finFSA4 = "in.fasta";
		//char* finFSA5 = "up_600.fasta";
		//char* finFSA5 = "up_olig.fasta";
		char* finFSA5 = "resultado.fasta";
		//char* finFSA4 = "30_seqs_43000_43000_bp.fasta";
		DNA s4;
		DNA s5;
		s4.readFasta(finFSA4);
		s5.readFasta(finFSA5);
		OligoAnalisys *olig = new OligoAnalisys();
		//s1 = processSet(s1);
		list<CalculatedOligo> l = olig->performAnalysis(s4,s5, 80, 6);
		l = olig->selectOlig(l);
		olig->printCalculatedOligo(l);

	} else if (argv[1][0] == '3') {
		MotifAlgo algo;
		//char* finFSA4 = "oligo.fasta";
		char* finFSA4 = "resultado.fasta";
		//char* finFSA4 = "30_seqs_43000_43000_bp.fasta";
		DNA s4;
		s4.readFasta(finFSA4);
		map<string, kmerFreq> freq = algo.computeTotalFrequency(s4, 3, 9485);
		/*

		 DNAseq s;

		 s.seq = "AA";
		 freq["AA"] = kmerFreq(s, 526149, (526149.0 / 4687999.0));
		 s.seq = "AC";
		 freq["AC"] = kmerFreq(s, 251377, (251377.0 / 4687999.0));
		 s.seq = "AG";
		 freq["AG"] = kmerFreq(s, 275056, (275056.0 / 4687999.0));
		 s.seq = "AT";
		 freq["AT"] = kmerFreq(s, 414453, (414453.0 / 4687999.0));

		 s.seq = "CA";
		 freq["CA"] = kmerFreq(s, 294423, (294423.0 / 4687999.0));
		 s.seq = "CC";
		 freq["CC"] = kmerFreq(s, 178324, (178324.0 / 4687999.0));
		 s.seq = "CG";
		 freq["CG"] = kmerFreq(s, 146052, (146052.0 / 4687999.0));
		 s.seq = "CT";
		 freq["CT"] = kmerFreq(s, 275859, (275859.0 / 4687999.0));

		 s.seq = "GA";
		 freq["GA"] = kmerFreq(s, 277343, (277343.0 / 4687999.0));
		 s.seq = "GC";
		 freq["GC"] = kmerFreq(s, 184367, (184367.0 / 4687999.0));
		 s.seq = "GG";
		 freq["GG"] = kmerFreq(s, 173404, (173404.0 / 4687999.0));
		 s.seq = "GT";
		 freq["GT"] = kmerFreq(s, 239569, (239569.0 / 4687999.0));

		 s.seq = "TA";
		 freq["TA"] = kmerFreq(s, 369980, (369980.0 / 4687999.0));
		 s.seq = "TC";
		 freq["TC"] = kmerFreq(s, 280475, (280475.0 / 4687999.0));
		 s.seq = "TG";
		 freq["TG"] = kmerFreq(s, 279932, (270932.0 / 4687999.0));
		 s.seq = "TT";
		 freq["TT"] = kmerFreq(s, 521236, (521236.0 / 4687999.0));

		 algo.frequencies = freq;
		 */

		map<string, kmerFreq>::iterator it1 = freq.begin();
		for (int i = 0; i < 16; ++i) {
			cout << " Olig " << it1->second.getOlig().seq << " Occ "
					<< it1->second.getOccurrences() << " Freq "
					<< it1->second.getFreq() << endl;
			it1++;
		}

		map<string, Prefix> matrix = algo.buildTransitionTable(freq);
		map<string, Prefix>::iterator it;
/*

		matrix["AA"] = Prefix("AA", 0.388, 0.161, 0.200, 0.251, 0.112);
		matrix["AC"] = Prefix("AC", 0.339, 0.198, 0.173, 0.290, 0.054);
		matrix["AG"] = Prefix("AG", 0.345, 0.204, 0.196, 0.255, 0.059);
		matrix["AT"] = Prefix("AT", 0.311, 0.184, 0.182, 0.323, 0.088);

		matrix["CA"] = Prefix("CA", 0.347, 0.178, 0.189, 0.286, 0.063);
		matrix["CC"] = Prefix("CC", 0.341, 0.190, 0.161, 0.309, 0.038);
		matrix["CG"] = Prefix("CG", 0.293, 0.221, 0.196, 0.290, 0.031);
		matrix["CT"] = Prefix("CT", 0.229, 0.195, 0.205, 0.371, 0.059);

		matrix["GA"] = Prefix("GA", 0.394, 0.155, 0.187, 0.264, 0.059);
		matrix["GC"] = Prefix("GC", 0.330, 0.205, 0.169, 0.297, 0.038);
		matrix["GG"] = Prefix("GG", 0.318, 0.217, 0.187, 0.277, 0.037);
		matrix["GT"] = Prefix("GT", 0.285, 0.175, 0.204, 0.336, 0.051);

		matrix["TA"] = Prefix("TA", 0.300, 0.193, 0.168, 0.339, 0.079);
		matrix["TC"] = Prefix("TC", 0.313, 0.203, 0.152, 0.332, 0.060);
		matrix["TG"] = Prefix("TG", 0.302, 0.209, 0.208, 0.282, 0.060);
		matrix["TT"] = Prefix("TT", 0.210, 0.208, 0.189, 0.392, 0.111);
*/

		for (it = matrix.begin(); it != matrix.end(); it++) {
			cout << it->first << " =>  Prefix  " << it->second.getPrefix()
					<< " A " << it->second.getSuffixA() << " C "
					<< it->second.getSuffixC() << " G "
					<< it->second.getSuffixG() << " T "
					<< it->second.getSuffixT() << " total "
					<< it->second.getPrefixTotal() << "\n";
		}

		DNAseq seq;
		//algo.transMatrix = matrix;
		seq.seq = "CCTACTATATGCCCAGAATT";
		cout << "Prob " << algo.scoreSeqMarkov(seq, 2,matrix) << endl;

	}
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