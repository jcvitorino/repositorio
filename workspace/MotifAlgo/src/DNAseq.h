/*
 * XNAseq.h
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#ifndef DNASEQ_H_
#define DNASEQ_H_

#include <algorithm>
#include <string>
#include <string.h>
#include "function.h"

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


class DNAseq {
public:
	string id;
	string description;
	string seq;

	DNAseq(); // constructor
	void clear(); // clear the content of object
	void cleanSeq(); // clean the sequence, remove non "AGCT"(+"U" for RNA) charactors
	void set_id(string input_id);
	void set_description(string input_description);
	void set_seq(string input_seq);
	DNAseq reverse_compliment(); // return the reverse compliment
	DNAseq compliment();
	DNAseq assemble(DNAseq c1, DNAseq c2, int minmatch);
	DNAseq toRNA();
	int length();
};



#endif /* DNASEQ_H_ */
