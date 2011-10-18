#ifndef ARVORE_H_
#define ARVORE_H_

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "NoArvore.h"

using namespace std;

class Arvore{
		private:
			   
			   ofstream *file;

        public:
               NoArvore *raiz;
               Arvore();
               virtual ~Arvore(){}
               void iniciarArvore(string);
               void mostrarArvore();
               void mostrarArvoreReduzida();
               void inserirNo(NoArvore *,NoArvore *);
               void inserirNaRaiz(NoArvore *);
               NoArvore * getRaiz();
};

#endif
