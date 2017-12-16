#include "flat.h"
#include <iostream>
#include "TFile.h"
#include "TTree.h"

int main(int argc, char** argv) {
  if (argc<2) return 2;

  {
    TChain* tree = new TChain("MCSel_Tau23Mu");
    for (unsigned k = 1 ; k < argc ; ++k)
      tree->Add(argv[k]);
    //TFile* ff = new TFile(argv[1],"read");
    //TTree* tree = (TTree*)ff->Get("MCSel_Tau23Mu");
    flat klasse((TTree*)tree);
    std::cout << " ===== mcsel, no selection ====" << std::endl;
    klasse.Loop(true,false); // truemom, aftersel
    std::cout << " ===== mcsel, after selection ====" << std::endl;
    klasse.Loop(true,true); // truemom, aftersel
  }
  {
    TChain* tree = new TChain("Tau23Mu");
    for (unsigned k = 1 ; k < argc ; ++k)
      tree->Add(argv[k]);
    flat klasse((TTree*)tree);
    std::cout << " ===== strip, no selection ====" << std::endl;
    klasse.Loop(true,false); // truemom, aftersel
    std::cout << " ===== strip, after selection ====" << std::endl;
    klasse.Loop(true,true); // truemom, aftersel
  }
  return 0;
}
