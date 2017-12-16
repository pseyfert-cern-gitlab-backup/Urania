#include "generatorclass.h"
#include "TFile.h"
#include "TTree.h"

int main(int argc, char** argv) {
  if (argc<2) return 2;
  TFile* ff = new TFile(argv[1],"read");
  TTree* tree = (TTree*)ff->Get("GeneratorFullMonitor/1");
  if (NULL==tree) return 1;

  generatorclass klasse(tree);
  klasse.Loop();
  return 0;
}
