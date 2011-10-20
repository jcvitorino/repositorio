/*
 * XNA.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#include "DNA.h"

DNA::DNA() {
}



/*
 /////////////////////////////////////////////////////////////////////////
 //ATM, the FASTA definition line must follow the conventions of the FASTA
 //Defline Format;
 GenBank                           gi|gi-number|gb|accession|locus
 EMBL Data Library                 gi|gi-number|emb|accession|locus
 DDBJ, DNA Database of Japan       gi|gi-number|dbj|accession|locus
 NBRF PIR                          pir||entry
 Protein Research Foundation       prf||name
 SWISS-PROT                        sp|accession|name
 Brookhaven Protein Data Bank (1)  pdb|entry|chain
 Brookhaven Protein Data Bank (2)  entry:chain|PDBID|CHAIN|SEQUENCE
 Patents                           pat|country|number
 GenInfo Backbone Id               bbs|number
 General database identifier       gnl|database|identifier
 NCBI Reference Sequence           ref|accession|locus
 Local Sequence identifier         lcl|identifier
 ///////////////////////////////////////////////////////////////////////////
 */
void DNA::readFasta(char *file) // read Fasta format sequences
		{
	try {
		ifstream Fin(file);
		if (!Fin)
			throw strcat("Cannot open input Fasta file ", file);
		bool fastaFormat = false;
		string buf;
		int newLine;
		DNAseq tmpSeq;
		for (;;) {
			// read a new line in every cycle
			getline(Fin, buf);
			/* The new line is marked with an integer, which corresponds
			 to one of the following cases:

			 1. New sequence line, which starts with "> ".
			 2. Sequence line, which starts with any charactor except for ">"
			 3. End of file, detected by function eof().
			 */
			if (buf[0] == '>')
				newLine = 1;
			else if (Fin.eof())
				newLine = 3;
			else
				newLine = 2;
			if (newLine == 1) { // this is a start of a new chain.
				if (!fastaFormat) {
					// if it is the first chain, just build a new chain object
					tmpSeq.clear();
					fastaFormat = true;
				} else {
					// otherwise, need to store the old chain first, then build a new chain
					tmpSeq.cleanSeq();
					addSeq(tmpSeq);
					tmpSeq.clear();
				}
				// this is set to accept FASTA Defline header information
				// in an intelligent way...
				int bar = buf.find_last_of("|");
				if (bar != -1) {
					int barpos = 1;
					string zedo(" ");
					if (zedo[0] == (buf.substr(bar + 1, buf.size() - 1)[0])) {
						barpos++;
					}
					tmpSeq.set_description(
							buf.substr(bar + barpos, buf.size() - 1));
					tmpSeq.set_id(buf.substr(1, bar));
				}
				// if fasta does not follow Defline, it's probably just
				// a simple descriptor...
				else {
					tmpSeq.set_description(buf.substr(1, buf.size() - 1));
					tmpSeq.set_id(buf.substr(1, buf.size() - 1));
				}
			}
			if (newLine == 2 && fastaFormat) { // sequence line
				tmpSeq.seq.append(buf);
			}
			if (newLine == 3) { // end of file
				if (!fastaFormat)
					throw strcat(file, " is not in Fasta format.");
				else {
					// otherwise, need to store the old chain first, then to
					// build a new chain

					tmpSeq.cleanSeq();
					addSeq(tmpSeq);
					break;
				}
			}
		}
	} catch (char* pMsg) {
		cerr << endl << "Exception:" << pMsg << endl;
	}
}


void DNA::writeFasta(char* file) {

	try {
		ofstream Fout(file);
		if (!Fout)
			throw strcat("Cannot open output Fasta file ", file);

		int i, j;
		for (i = 0; i < chain.size(); i++) {
			if (chain[i].id != chain[i].description) {
				Fout << ">" << chain[i].id << " " << chain[i].description
						<< endl;
			} else {
				Fout << ">" << chain[i].description << endl;
			}
			for (j = 0; j < chain[i].seq.size(); j++) {
				Fout << chain[i].seq[j];
				if ((j + 1) % 60 == 0)
					Fout << endl;
			}
			Fout << endl;
		}
	}

	catch (char* pMsg) {
		cerr << endl << "Exception:" << pMsg << endl;
	}
}


void DNA::addSeq(DNAseq ds) {
	chain.push_back(ds);
}



