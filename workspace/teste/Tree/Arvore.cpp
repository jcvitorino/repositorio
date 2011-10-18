#include "Arvore.h"

Arvore::Arvore(){
        this->raiz = NULL;
}

void Arvore::iniciarArvore(string root){
     this->raiz = new NoArvore();
     this->raiz->setLabel(root);
}

void Arvore::mostrarArvore(){
     file = new ofstream("arqs/Arvore.txt",ios::trunc);
     (*file) << "    [+] " <<this->raiz->getLabel();
     this->raiz->exibirFilhos(0,file);
     file->close();
}

void Arvore::mostrarArvoreReduzida(){
     this->raiz->reduzArvore();
     this->mostrarArvore();
}

void Arvore::inserirNo(NoArvore *pai ,NoArvore *filho){
     pai->inserirNo(filho);
}

NoArvore * Arvore::getRaiz(){
     return this->raiz;
}
