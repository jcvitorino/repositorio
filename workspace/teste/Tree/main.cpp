#include "NoArvore.h"
#include "Arvore.h"
using namespace std;

int main(int argc, char **argv) {
	Arvore *tree;
	tree = new Arvore();
	tree->iniciarArvore("--");

	NoArvore *A = new NoArvore("A-", tree->raiz, 1);
	NoArvore *C = new NoArvore("C-", tree->raiz, 2);
	NoArvore *G = new NoArvore("G-", tree->raiz, 3);
	NoArvore *T = new NoArvore("T-", tree->raiz, 4);

	tree->inserirNo(tree->getRaiz(), A);
	tree->inserirNo(tree->getRaiz(), C);
	tree->inserirNo(tree->getRaiz(), G);
	tree->inserirNo(tree->getRaiz(), T);

	A->inserirNo(new NoArvore("AA", A, A->getQtdeFilhos() + 1));
	A->inserirNo(new NoArvore("AC", A, A->getQtdeFilhos() + 1));
	A->inserirNo(new NoArvore("AG", A, A->getQtdeFilhos() + 1));
	A->inserirNo(new NoArvore("AT", A, A->getQtdeFilhos() + 1));

	C->inserirNo(new NoArvore("CA", C, C->getQtdeFilhos() + 1));
	C->inserirNo(new NoArvore("CC", C, C->getQtdeFilhos() + 1));
	C->inserirNo(new NoArvore("CG", C, C->getQtdeFilhos() + 1));
	C->inserirNo(new NoArvore("CT", C, C->getQtdeFilhos() + 1));

	G->inserirNo(new NoArvore("GA", G, G->getQtdeFilhos() + 1));
	G->inserirNo(new NoArvore("GC", G, G->getQtdeFilhos() + 1));
	G->inserirNo(new NoArvore("GG", G, G->getQtdeFilhos() + 1));
	G->inserirNo(new NoArvore("GT", G, G->getQtdeFilhos() + 1));

	T->inserirNo(new NoArvore("TA", T, T->getQtdeFilhos() + 1));
	T->inserirNo(new NoArvore("TC", T, T->getQtdeFilhos() + 1));
	T->inserirNo(new NoArvore("TG", T, T->getQtdeFilhos() + 1));
	T->inserirNo(new NoArvore("TT", T, T->getQtdeFilhos() + 1));

	tree->mostrarArvore();
	NoArvore * teste;

	teste = tree->raiz->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";



	teste = teste->nextVertex();
	cout << teste->getLabel();
	cout << "\n";

	teste = A->byPass();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->byPass();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->byPass();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->byPass();
	cout << teste->getLabel();
	cout << "\n";

	teste = teste->byPass();
	cout << teste->getLabel();
	cout << "\n";

	//    cout << teste->getPosicao();
	//    tree->getRaiz()->exibirFilhos(0,new ofstream("arqs/R.txt",ios::trunc));
	//    cout << G->getLabel();
	//    cout << tree->raiz->getQtdeFilhos();
	cout << "\n";
	system("pause");
}
