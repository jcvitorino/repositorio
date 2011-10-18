#include "NoArvore.h"

NoArvore::NoArvore() {
	this->label = "";
	this->reduce = false;
	this->pai = NULL;
	this->posicao = 0;
}

NoArvore::NoArvore(string nome) {
	this->label = nome;
	this->reduce = true;
	this->pai = NULL;
	this->posicao = 0;
}

NoArvore::NoArvore(NoArvore* pai) {
	this->label = "";
	this->reduce = false;
	this->pai = pai;
	this->posicao = 0;
}

NoArvore::NoArvore(string nome, NoArvore* pai) {
	this->label = nome;
	this->reduce = true;
	this->pai = pai;
	this->posicao = 0;
}

NoArvore::NoArvore(NoArvore* pai, int posicao) {
	this->label = "";
	this->reduce = false;
	this->pai = pai;
	this->posicao = posicao;
	this->visitado = false;
}

NoArvore::NoArvore(string nome, NoArvore* pai, int posicao) {
	this->label = nome;
	this->reduce = true;
	this->pai = pai;
	this->posicao = posicao;
	this->visitado = false;
}

void NoArvore::inserirNo(NoArvore *no) {
	this->filhos.push_back(no);
}

void NoArvore::setLabel(string nome) {
	this->label = nome;
}

string NoArvore::getLabel() const {
	return this->label;
}

void NoArvore::setReduce(bool n) {
	this->reduce = n;
}

bool NoArvore::canReduce() const {
	return this->reduce;
}

int NoArvore::getQtdeFilhos() const {
	return this->filhos.size();
}

void NoArvore::reduzArvore() {
	vector<NoArvore *>::iterator it;
	for (it = this->filhos.begin(); it != this->filhos.end(); it++) {
		(*it)->reduzArvore();
		if ((*it)->getQtdeFilhos() == 1 && (*it)->canReduce())
			(*it) = (*it)->filhos.front();
	}
}

void NoArvore::exibirFilhos(int level, ofstream *file) {
	vector<NoArvore *>::iterator it;
	vector<NoArvore *>::iterator j;
	for (it = this->filhos.begin(); it != this->filhos.end(); it++) {
		(*file) << endl;
		for (int i = 0; i <= level; i++)
			(*file) << "      " << (char) 166;
		if ((*it)->getQtdeFilhos() > 0)
			(*file) << "---[+]";
		else
			(*file) << "--->";
		(*file) << (*it)->getLabel();
		if ((*it)->getQtdeFilhos() == 0)
			continue;
		for (j = (*it)->filhos.begin(); j != (*it)->filhos.end(); j++) {
			(*file) << endl;
			for (int i = 0; i <= level; i++)
				(*file) << "      " << (char) 166;
			if ((*j)->getQtdeFilhos() > 0)
				(*file) << "      " << (char) 166 << "---[+]";
			else
				(*file) << "      " << (char) 166 << "--->";
			(*file) << (*j)->getLabel();
			if ((*j)->getQtdeFilhos() > 0)
				(*j)->exibirFilhos(level + 2, file);// exibir filhos
			if ((*j)->getQtdeFilhos() == 0)
				continue;
			(*file) << endl;
			for (int i = 0; i <= level + 1; i++)
				(*file) << "      " << (char) 166;
		}
		(*file) << endl;
		for (int i = 0; i <= level; i++)
			(*file) << "      " << (char) 166;
	}
}

NoArvore* NoArvore::leaf(int pos) {
	return this->filhos[pos];

}

void NoArvore::setVisitado() {
	visitado = true;
}

bool NoArvore::getVisitado() {
	return visitado;
}

int NoArvore::getPosicao() {
	return this->posicao;
}

NoArvore* NoArvore::nextVertex() {
	// se nao ha mais nos para processar retorna um no NULL
	if (this->getLabel() == "NULL") {
		return (new NoArvore("NULL"));
	}
	vector<NoArvore *>::iterator it;
	this->setVisitado();
	//verifica se ha algum filho no nodo
	if (this->getQtdeFilhos() == 0) {
		if (this->pai->getQtdeFilhos() == this->getPosicao()) { // verifica se e o utlimo filho do no se for chama o avo
			return (this->pai->pai->nextVertex());
		}
		//cout << this->pai->filhos[this->getPosicao() ]->getLabel()<<endl;
		return (this->pai->filhos[this->getPosicao()]);
	}

	for (it = this->filhos.begin(); it != this->filhos.end(); it++) {
		if ((*it)->getVisitado() == true) {
			continue;
		} else {
			return (*it);
		}
	}
	// se nao ha mais nos para processar retorna um no NULL
	return (new NoArvore("NULL"));
}

NoArvore* NoArvore::byPass(){
	vector<NoArvore *>::iterator it;
	// se nao ha mais nos para processar retorna um no NULL
	if (this->getLabel() == "NULL") {
		return (new NoArvore("NULL"));
	}

		if (this->pai->getQtdeFilhos() == this->getPosicao()) { // verifica se e o utlimo filho do no se for chama o avo
			return (new NoArvore("NULL"));
		}
		//cout << this->pai->filhos[this->getPosicao() ]->getLabel()<<endl;
		return (this->pai->filhos[this->getPosicao()]);
}
