

#ifndef NOARVORE_H_
#define NOARVORE_H_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class NoArvore{
	private:
			 vector<NoArvore *> filhos;

			 string label;
			 bool reduce;
			 bool visitado;
			 int posicao;
	public:
             NoArvore* pai;
			 NoArvore();
			 int getPosicao();
             void setVisitado();
             bool getVisitado();
             NoArvore(string);
             NoArvore(NoArvore * pai);
             NoArvore(string nome, NoArvore * pai);
             NoArvore(NoArvore * pai, int posicao);
             NoArvore(string nome, NoArvore * pai, int posicao);             
             virtual ~NoArvore(){};
             void inserirNo(NoArvore *);
             void setLabel(string);
             void setReduce(bool);
             void mostrarNo();
             void exibirFilhos(int,ofstream*);
             void reduzArvore();
             bool canReduce() const;
             int getQtdeFilhos() const;
             string getLabel() const;
             NoArvore* leaf(int pos);
             NoArvore* nextVertex();
             NoArvore* byPass();
};

#endif
