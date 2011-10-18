/*
 * main.cpp
 *
 *  Created on: 10/08/2011
 *      Author: josue
 */

#include "DNA.h"
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
	DNA d1, d2, d3, d4;
	vector<DNAseq>::iterator it, it2;
	string str, str2, ant;
	srand(time(NULL));
	int r = 0;

	d1.readFasta("../arquivos/entrada.fasta");
	d2.readFasta("../arquivos/genes.fasta");
	cout << "Total sequence " << d1.chain.size() << endl;
	cout << "Total MGs input " << d2.chain.size() << endl;

	/**
	 * Separa os genes MGs dos não MGs
	 */
	for (it = d1.chain.begin(); it != d1.chain.end(); ++it) {
		str = it->id.substr(0, 9);
		for (it2 = d2.chain.begin(); it2 != d2.chain.end(); ++it2) {
			str2 = it2->id.substr(0, 9);
			if (str == str2 && str != ant) {
				ant = str2;
				d3.addSeq(DNAseq(it->id,it->description="",it->seq));
			}
		}
	}

	/**
	 * Gera as sequencias non-DFSs com o DRE inserido no meio
	 */
	d1.readFasta("../arquivos/30_seqs_43000_43000_bp.fasta");
	for (it2 = d2.chain.begin(); it2 != d2.chain.end(); ++it2) {
		str2 = it2->id.substr(0, 9);
		for (it = d1.chain.begin(); it != d1.chain.end(); ++it) {
			str = it->id.substr(0, 9);
			if (str != str2 && str != ant) {
				ant = str;
				if (d4.chain.size() < 500 && it->seq.length() >= 1000) {
					r = rand() % 700 + 1;
					str = it->seq.substr(r, 100);
					str = str + "GCCGAC" + it->seq.substr(r + 7, 99);
					str2 = it->id.substr(0, 9);
					DNAseq seq = DNAseq(str2, "", str);
					d4.addSeq(seq);
				} else if (d4.chain.size() < 1000 && it->seq.length() >= 1000) {
					r = rand() % 700 + 1;
					str = it->seq.substr(r, 100);
					str = str + "ACCGAC" + it->seq.substr(r + 7, 99);
					str2 = it->id.substr(0, 9);
					DNAseq seq = DNAseq(str2, "", str);
					d4.addSeq(seq);
				}
			}
		}
	}
	cout << "non-DFS set size " << d4.chain.size() << endl;
	cout << "non-DFS size " << d4.chain[0].seq.length() + 1 << endl;
	d4.writeFasta("../arquivos/ramdomSet.fasta");
	d1.chain.clear();
	size_t found;
	int posAnt = 0, posPos = 0;

	/**
	 *  Gera reverse complemento
	 */
	DNAseq tmp;
	d4.chain.clear();
	int tam = d3.chain.size();
	for (int i = 0; i < tam; ++i) {
		tmp = d3.chain[i].reverse_compliment();
		tmp.description  =tmp.description+ "| reverse";
		d3.addSeq(tmp);
	}

	/**
	 * Procura dentro dos MGs os fragmentos que contem o DRE
	 */
	for (it = d3.chain.begin(); it != d3.chain.end(); ++it) {
		found = it->seq.find("GCCGAC");
		while (found != string::npos) {
			posAnt = (int) found - 100;
			if (posAnt >= 0) {
				str = it->seq.substr(posAnt, 205);
				str2 = it->id.substr(0, 9);
				DNAseq seq = DNAseq(str2, it->description+ "| DRE: GCCGAC;", str);
				d1.addSeq(seq);
			}

			found = it->seq.find("GCCGAC", found + 6);
		}

		found = it->seq.find("ACCGAC");
		while (found != string::npos) {
			posAnt = (int) found - 100;
			if (posAnt >= 0) {
				str = it->seq.substr(posAnt, 205);
				str2 = it->id.substr(0, 9);
				DNAseq seq = DNAseq(str2, it->description + "| DRE: ACCGAC;", str);
				d1.addSeq(seq);
			}

			found = it->seq.find("ACCGAC", found + 6);
		}

	}

	cout << "DFS set size " << d1.chain.size() << endl;
	cout << "DFS size " << d1.chain[0].seq.length() + 1 << endl;
	d1.writeFasta("../arquivos/resultado.fasta");

	for (it = d1.chain.begin(); it != d1.chain.end(); it++) {
		it->id =  "\""+it->id;
		it->description =  it->description+"\"";
		it->seq = "\""+it->seq+"\"";

	}
	d1.writeFasta("../arquivos/resultado.csv");
	return 0;
}
