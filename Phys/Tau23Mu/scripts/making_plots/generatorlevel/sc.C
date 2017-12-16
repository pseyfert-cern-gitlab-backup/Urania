#include "dalitz.h"
#include "TFile.h"
#include "TTree.h"

int main(int argc, char** argv) {
  if (argc<2) return 2;
  TFile* ff = new TFile(argv[1],"read");
  TTree* tree = (TTree*)ff->Get("dalitz");
  if (NULL==tree) return 1;

  dalitz klasse(tree);
  klasse.Loop();
  return 0;
}
