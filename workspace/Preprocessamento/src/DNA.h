
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
#include "DNAseq.h"
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

class DNA {
public:
	vector<DNAseq> chain;
	DNA(); // constructor
	void readFasta(string file); // read Fasta format sequence
	void writeFasta(string file); // write Fasta format sequence
	void appendToFastaFile(string file);
	void addSeq(DNAseq ds); // add a new chain member
};
