/***************************************************************************
                         B10.CPP XNA USAGE EXAMPLE
                             -------------------
       A simple example of how to use B10.CPP to read and write a 
       fasta file and XML file using the XNA class.
       
       Compile example: g++ exampleXNAuse.cpp -o test.exe
*******************************************************************************/

#include <string>
#include "XNA.h"

/*
int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage:  fasta-input-file fasta-output-file XML-input-file"
                  << std::endl;
        return EXIT_FAILURE;
    }

    char* finFSA=argv[1];
    char* fout=argv[2];
    char* finXML=argv[3];
    XNA s1;
    s1.readFasta(finFSA);
    s1.readXML(finXML);
    // to find the number of sequence in class:
    int numberOfSequences=s1.chain.size();
    cout << numberOfSequences << endl;

    for (int i=0; i<numberOfSequences; i++) {
      string mainSEQ=s1.chain[i].seq;
      string mainid=s1.chain[i].id;
      string maindesc=s1.chain[i].description;
      int lenSeq=s1.chain[i].length();
      cout << mainid << endl << maindesc << endl << lenSeq << endl << endl;
      
    }
    string mS=s1.chain[0].seq;
    string mI=s1.chain[0].id;
    XNAseq rC=s1.chain[0].reverse_compliment();
    cout << mI << endl << mS[1] << endl;
    s1.writeFasta(fout);
    return EXIT_SUCCESS;


};
*/
