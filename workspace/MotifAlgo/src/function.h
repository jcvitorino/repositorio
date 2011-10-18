/*
 * function.h
 *
 *  Created on: 19/07/2011
 *      Author: josue
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <algorithm>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

extern bool not_nucleotide(char ch);
extern char compliment_DNA(char ch);
extern char compliment_RNA(char ch);
extern char replace_nucleotide(char ch);
extern bool space(char c);
extern bool not_space(char c);
extern bool StringToInt(const string &s, int &i);


#endif /* FUNCTION_H_ */
