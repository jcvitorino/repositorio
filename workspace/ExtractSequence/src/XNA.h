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
#include "XNAseq.h"
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
