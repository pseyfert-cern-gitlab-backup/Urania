#include "./MVAntuple.h"

int main() {
  TChain* sig = new TChain("Tau23Mu");
  sig->Add("./largesig.root");
  TChain* bkg = new TChain("Tau23Mu");
  bkg->Add("./largebkg.root");
  MVAntuple tup(bkg);
  tup.Loop();
  return 0;
}
