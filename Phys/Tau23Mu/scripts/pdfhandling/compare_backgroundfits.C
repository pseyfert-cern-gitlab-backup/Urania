#include "TH2D.h"
#include <iostream>
#include "TFile.h"

void comp(TH2* m, TH2* mp, TH2* b, TH2* bp) {

  std::cout << "bin&\tmarcin&\tbasem\\\\\\hline" << std::endl;
  for (int x = 1 ; x < m->GetNbinsX() ; ++x) {
    float xsumm_m = 0.f;
    float xsumm_b = 0.f;
    float xsumm_mp = 0.f;
    float xsumm_bp = 0.f;
    for (int y = 1 ; y < m->GetNbinsY() ; ++y) {
      int bin = m->GetBin(x,y);
      xsumm_m += m->GetBinContent(bin);
      xsumm_b += b->GetBinContent(bin);
      if (mp) {
        xsumm_mp += mp->GetBinContent(bin);
      }
      xsumm_bp += bp->GetBinContent(bin);
    }
    xsumm_mp -= xsumm_m;
    xsumm_bp -= xsumm_b;
    std::cout << x << "&\t" << xsumm_m << " \\pm " << xsumm_mp << "\t&\t" << xsumm_b << " \\pm " << xsumm_bp << "\\\\" << std::endl;
    float d = fabs(xsumm_m-xsumm_b)/sqrt(xsumm_bp*xsumm_bp+xsumm_mp*xsumm_mp);
    if (d>.5) std::cout << "ERROR" << std::endl;
  }
}

void compare() {
  TFile* mf = new TFile("../../params/3fb/2011_PDF_BCK/bck_eta_cut450.root","read");
  //TFile* mf = new TFile("../../params/3fb/2012_PDF_BCK/bck_eta_cut450_2012.root","read");
  TH2* mh = (TH2*)mf->Get("expected_exp");
  TH2* mp = (TH2*)mf->Get("expected_plus");

  TFile* bf = new TFile("../../params/3fb/background_2011_notrash.root","read");
  //TFile* bf = new TFile("../../params/3fb/background_2012_notrash.root","read");
  TH2* bh = (TH2*)bf->Get("expected");
  TH2* bp = (TH2*)bf->Get("expected_plus");
  comp(mh,mp,bh,bp);
}
