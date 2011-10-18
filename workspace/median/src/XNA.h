/***************************************************************************
 B10.CPP XNA API  -  alpha (0.3)
 -------------------
 begin                : 06-2006
 authors              : Honguy Zhang, Michael Janis
 email                : mjanis@chem.ucla.edu

 B10.CPP (BioCPP, BioC++) and associated libraries are distributed under the BSD license:
 Copyright (c) 2006, Hongyu Zhang, Michael Janis
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * Neither the names of B10.CPP, BioCPP, BioC++ nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <list>
#include <cstdlib>
#include <cctype>
#include <stdio.h>  // to get "printf" function
#include <stdlib.h> // to get "free" function
//#include "xmlParser.h"
using namespace std;

#ifdef WIN32
#include <tchar.h>
#endif

#ifdef _UNICODE
#ifdef __linux__
#include <wchar.h>
#define _T(c) L ## c
#endif
#ifndef LPCTSTR
#define LPCTSTR const wchar_t *
#endif /* LPCTSTR */
#ifndef LPTSTR
#define LPTSTR wchar_t *
#endif /* LPTSTR */
#ifndef TCHAR
#define TCHAR wchar_t
#endif /* TCHAR */
#else
#ifndef WIN32
#define _T(c) c
#endif
#ifndef LPCTSTR
#define LPCTSTR const char *
#endif /* LPCTSTR */
#ifndef LPTSTR
#define LPTSTR char *
#endif /* LPTSTR */
#ifndef TCHAR
#define TCHAR char
#endif /* TCHAR */
#endif
#ifndef FALSE
#define FALSE 0
#endif /* FALSE */
#ifndef TRUE
#define TRUE 1
#endif /* TRUE */

class XNA;
class XNAseq;

class XNAseq {
public:
	string id;
	string description;
	string seq;

	XNAseq(); // constructor
	void clear(); // clear the content of object
	void cleanSeq(); // clean the sequence, remove non "AGCT"(+"U" for RNA) charactors
	void set_id(string input_id);
	void set_description(string input_description);
	void set_seq(string input_seq);
	XNAseq reverse_compliment(); // return the reverse compliment
	XNAseq assemble(XNAseq c1, XNAseq c2, int minmatch);
	XNAseq toRNA();
	int length();
};

class XNA {
public:
	vector<XNAseq> chain; // this is left as generic vector
	// to allow for a multitude of weird identifiers and further
	// map creation from *ANY* element (feature, etc.) -
	// in B10.CPP, ALL data is metadata (including the sequence);
	// therefore this remains as a simple vector instead of a
	// map<string,XNAseq>...
	XNA(); // constructor
	void readFasta(char *file); // read Fasta format sequence
//	void readXML(char *file); // read GenBank XML format sequence
	void writeFasta(char *file); // write Fasta format sequence
	void addSeq(XNAseq ds); // add a new chain member
};

XNAseq::XNAseq() {
	seq = "";
	id = "";
	description = "";
}

void XNAseq::set_id(string input_id) {
	id = input_id;
}

void XNAseq::set_description(string input_description) {
	description = input_description;
}

void XNAseq::set_seq(string input_seq) {
	seq = input_seq;
}

void XNAseq::clear() {
	seq = "";
	id = "";
	description = "";
}

bool not_nucleotide(char ch) {
	string str = "ACGTU";
	// added U accept RNA;
	// uppercase the seq in all inlines
	string ts(1, ch);
	if (str.find(ts) == string::npos)
		return true;
	else
		return false;
}

void XNAseq::cleanSeq() {
	std::transform(seq.begin(), seq.end(), seq.begin(),
			(int(*)(int))std::toupper);string::iterator endp = remove_if(seq.begin(),seq.end(), not_nucleotide);
    seq.erase(endp, seq.end());
}

int XNAseq::length() {
	return seq.size();
}

char compliment_DNA(char ch) {
	string str = "ACGT";
	string ts(1, ch);
	if (ch == 'A')
		return 'T';
	else if (ch == 'T')
		return 'A';
	else if (ch == 'C')
		return 'G';
	else
		return 'C';
}

char compliment_RNA(char ch) {
	string str = "ACGT";
	string ts(1, ch);
	if (ch == 'A')
		return 'T';
	else if (ch == 'T')
		return 'A';
	else if (ch == 'C')
		return 'G';
	else
		return 'C';
}

char replace_nucleotide(char ch) {
// basically converts T to U for RNA
	if (ch == 'T')
		return 'U';
	else
		return ch;
}

XNAseq XNAseq::reverse_compliment() {
	XNAseq tmpSeq;
	tmpSeq.id = id;
	tmpSeq.description = description;
	tmpSeq.seq = seq;
	int RNA = seq.find_last_of("U");
	if (RNA == -1) {
		reverse_copy(seq.begin(), seq.end(), tmpSeq.seq.begin());
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_DNA);
	} else {
		reverse_copy(seq.begin(), seq.end(), tmpSeq.seq.begin());
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_RNA);
	}
	return tmpSeq;
}

XNAseq XNAseq::toRNA() {
	XNAseq tmpSeq;
	tmpSeq.id = id;
	tmpSeq.description = description;
	tmpSeq.seq = seq;
	transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
			replace_nucleotide);
	return tmpSeq;
}

class hsp {
	int query_start, query_end;
	int sbjct_start, sbjct_end;
};

XNA::XNA() {
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
void XNA::readFasta(char *file) // read Fasta format sequences
		{
	try {
		ifstream Fin(file);
		if (!Fin)
			throw strcat("Cannot open input Fasta file ", file);
		bool fastaFormat = false;
		string buf;
		int newLine;
		XNAseq tmpSeq;
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

/***********************************************************************
 XML for the components of a GenBank/EMBL/DDBJ sequence record.
 The International Nucleotide Sequence Database (INSD) collaboration
 Version 1.4, 19 September 2005

 ************************************************************************
 INSDSeq provides the elements of a sequence as presented in the
 GenBank/EMBL/DDBJ-style flatfile formats, with a small amount of
 additional structure.

 URLs for the DDBJ, EMBL, and GenBank Feature Table Document:
 http://www.ddbj.nig.ac.jp/FT/full_index.html
 http://www.ebi.ac.uk/embl/Documentation/FT_definitions/feature_table.html
 http://www.ncbi.nlm.nih.gov/projects/collab/FT/index.html

 URLs for DDBJ, EMBL, and GenBank Release Notes :
 ftp://ftp.ddbj.nig.ac.jp/database/ddbj/ddbjrel.txt
 http://www.ebi.ac.uk/embl/Documentation/Release_notes/current/relnotes.html
 ftp://ftp.ncbi.nih.gov/genbank/gbrel.txt


 All publicly accessible sequence records in INSDSeq format will
 include accession and accession.version. However, these elements
 are optional in optional in INSDSeq so that this format can also
 be used for non-public sequence data, prior to the assignment of
 accessions and version numbers. In such cases, records will have only
 "other-seqids".

 sequences will normally all have "sequence" filled in. But contig
 records will have a "join" statement in the "contig" slot, and no
 "sequence".

 Four (optional) elements are specific to records represented via the
 EMBL sequence database: INSDSeq_update-release,
 INSDSeq_create-release, INSDSeq_entry-version, and
 INSDSeq_database-reference.

 One (optional) element is specific to records originating at the
 GenBank
 and DDBJ sequence databases: INSDSeq_segment.
 *************************************************************************/
/*
void XNA::readXML(char *file) // read INSD XML format sequences
		{
	//  XMLNode xNode=xMainNode.getChildNode("Header");
	XNAseq tmpSeq;
	// this opens and parse the XML file:
	XMLNode xMainNode = XMLNode::openFileHelper(file, "INSDSet");
	// get the INSDSeq, inner of INSDSet; why is this like this?
	XMLNode MainNode = xMainNode.getChildNode("INSDSeq");
	string SeqNode = MainNode.getChildNode("INSDSeq_sequence").getText();
	string LocusNode = MainNode.getChildNode("INSDSeq_locus").getText();
	string DefNode = MainNode.getChildNode("INSDSeq_definition").getText();
	string AccNode =
			MainNode.getChildNode("INSDSeq_primary-accession").getText();
	tmpSeq.seq.append(SeqNode);
	tmpSeq.set_description(DefNode);
	tmpSeq.set_id(AccNode);
	tmpSeq.cleanSeq();
	addSeq(tmpSeq);

}
*/
void XNA::writeFasta(char* file) {

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

void XNA::addSeq(XNAseq ds) {
	chain.push_back(ds);
}

bool space(char c) {
	return isspace(c);
}

// false if argument is whitespace, true otherwise
bool not_space(char c) {
	return !isspace(c);
}

// The following split function is adapted
// from Andrew Koenig and Barbara Moo, 
// "Accelerated C++"; true if argument is delim"|", 
// false otherwise
vector<string> split(const string& str) {
	typedef string::const_iterator iter;
	vector<string> ret;
	iter i = str.begin();
	while (i != str.end()) {
		// ignore leading blanks
		i = find_if(i, str.end(), not_space); // not_space
		// find end of next word
		iter j = find_if(i, str.end(), space); // space
		// copy the characters in [i,j)
		if (i != str.end())
			ret.push_back(string(i, j));
		i = j;
	}
	return ret;
}

// one way to convert a string to an int using streams...
bool StringToInt(const string &s, int &i) {
	istringstream myStream(s);
	if (myStream >> i)
		return true;
	else
		return false;
}

