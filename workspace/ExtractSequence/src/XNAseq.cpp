/*
 * XNAseq.cpp
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */


#include "XNAseq.h"

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

void XNAseq::cleanSeq() {
	std::transform(seq.begin(), seq.end(), seq.begin(),
			(int(*)(int))std::toupper);string::iterator endp = remove_if(seq.begin(),seq.end(), not_nucleotide);
    seq.erase(endp, seq.end());
}

int XNAseq::length() {
	return seq.size();
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



XNAseq XNAseq::compliment() {
	XNAseq tmpSeq;
	tmpSeq.id = id;
	tmpSeq.description = description;
	tmpSeq.seq = seq;
	int RNA = seq.find_last_of("U");
	if (RNA == -1) {
		transform(tmpSeq.seq.begin(), tmpSeq.seq.end(), tmpSeq.seq.begin(),
				compliment_DNA);
	} else {
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

