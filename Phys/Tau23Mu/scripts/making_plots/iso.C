#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <vector>
#include <iostream>
#include <TRandom3.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

/**
 * @file mcroc.C
 * @brief make two quick ROC curves from MC w/o calibration
 * @author Paul Seyfert
 * @date 2012-10-18
 */


//TString sig_f = "/afs/cern.ch/work/p/pseyfert/public/signal_test.root"
//TString bkg_f = "/afs/cern.ch/work/p/pseyfert/public/data_middle.root"
//
//TString sig_f = "/tmp/splot.root";
//TString bkg_f = "/afs/cern.ch/work/p/pseyfert/public/triggeremulation/allbkg.root";

std::vector<TString> classifiers;
std::vector<TString> titles;
void mcroc() {
  //classifiers.push_back("GeoMVA");
  //classifiers.push_back("GeoMVA");
  //classifiers.push_back("NeuroBayes_0x141cf018");
  //classifiers.push_back("NeuroBayes_0x141cf818");
  //classifiers.push_back("NeuroBayes_0x149cf018");
  //classifiers.push_back("NeuroBayes_v1_0x141cf018");
  //classifiers.push_back("NeuroBayes_v1_0x149cf018");
  //classifiers.push_back("NeuroBayes_v1_0x141cf818");
  //
  //classifiers.push_back("flat_TMVA_v1_0x141cf818");
  /////////////////////////classifiers.push_back("flat_TMVA_v1_0x149cf818");
  classifiers.push_back("flat_TMVA_v3_0x149cf818");
  titles.push_back("all isolations");
  classifiers.push_back("flat_TMVA_v3_0x149cf018");
  titles.push_back("Giampi's isolation");
  classifiers.push_back("flat_TMVA_v3_0x141cf818");
  titles.push_back("Laura's isolation");
  classifiers.push_back("flat_TMVA_v3_0x141cf018");
  titles.push_back("no isolation");


  //classifiers.push_back("NeuroBayes_0x149cf818");
  //classifiers.push_back("NeuroBayes_v2_0x149cf818");
  //classifiers.push_back("NeuroBayes_v3_0x149cf818");
  //classifiers.push_back("flat_TMVA_v1_0x141cf818");
  //classifiers.push_back("flat_TMVA_v3_0x141cf818");
  //classifiers.push_back("MLPCJ_v1_0x149cf818");
  //classifiers.push_back("MLPCJ_v3_0x149cf818");
  //classifiers.push_back("MLPCJ_v2_0x149cf818");
  //classifiers.push_back("MLPBFGS_v1_0x149cf818");
  //classifiers.push_back("MLP_v1_0x149cf818");
  //classifiers.push_back("MLP_v3_0x149cf818");
  //classifiers.push_back("MLP_v1_0x141cf818");
  //classifiers.push_back("MLP_v3_0x141cf818");

  float scanpoint = 0.4;
  std::vector<std::vector<float> > sigeffs;
  std::vector<std::vector<float> > bkgeffs;
  std::vector<std::vector<float> > esigeffs;
  std::vector<std::vector<float> > ebkgeffs;
  for (unsigned u = 0 ; u < classifiers.size() ; ++u) {
    sigeffs.push_back(std::vector<float>());
    bkgeffs.push_back(std::vector<float>());
    esigeffs.push_back(std::vector<float>());
    ebkgeffs.push_back(std::vector<float>());
  }


  TFile* bufferfileS = new TFile("/auto/data/pseyfert/Tau_MC/buffer.root","read");
  TFile* bufferfileB = new TFile("/auto/data/pseyfert/Tau23Mu_Stripping20/v9_2nd/buffer.root","read");
  TTree* signal;
  TTree* background;
  bufferfileS->GetObject("Tau23Mu",signal);
  bufferfileB->GetObject("Tau23Mu",background);
  TH1F* buffer = new TH1F("buffer","buffer",100,-1.1,1.1);
//(min(p0_ANNmuon,min(p1_ANNmuon,p2_ANNmuon))>-0.1)&&
  TString cutstring = "(min(p0_ANNmuon,min(p1_ANNmuon,p2_ANNmuon))>-0.1)&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";
  background->Draw(classifiers[0]+">>buffer",cutstring.Data());
  float allbkg = buffer->GetSum();
  signal->Draw(classifiers[0]+">>buffer",cutstring.Data());
  float allsig = buffer->GetSum();

  TRandom3 rand;

  while (scanpoint < 1.001) {
    if (scanpoint < 0.99) {
      scanpoint += 0.005;
    } else {
      scanpoint += 0.00020;
    }

    unsigned ustart = 1u;
    //if ((fabs(scanpoint-0.05) <0.003 )|| (fabs(scanpoint-0.35) <0.003 )|| (fabs(scanpoint-0.65) <0.003 )|| (fabs(scanpoint-0.74) <0.003)) {
      //std::cout << "scanpoint = " << scanpoint << "   signature " << (fabs(scanpoint-0.05) <0.003 )<< (fabs(scanpoint-0.35) <0.003 )<< (fabs(scanpoint-0.65) <0.003 )<< (fabs(scanpoint-0.74) <0.003) << std::endl; 
      ustart = 0u;
    //}

    for (unsigned u = ustart ; u < classifiers.size() ; ++u) {
      signal->Draw(classifiers[u]+">>buffer",Form("(%s)*(%s>%f)",cutstring.Data(),classifiers[u].Data(),scanpoint));
      float A_thissig = buffer->GetSum();
      background->Draw(classifiers[u]+">>buffer",Form("(%s)*(%s>%f)",cutstring.Data(),classifiers[u].Data(),scanpoint));
      float A_thisbkg = buffer->GetSum();
      sigeffs[u].push_back(((float)A_thissig)/((float)allsig));
      bkgeffs[u].push_back(1.-((float)A_thisbkg)/((float)allbkg));
      esigeffs[u].push_back(sqrt((A_thissig+1)*(allsig-A_thissig+1)/(allsig+2)/(allsig+2)/(allsig+3)));
      ebkgeffs[u].push_back(sqrt((A_thisbkg+1)*(allbkg-A_thisbkg+1)/(allbkg+2)/(allbkg+2)/(allbkg+3)));
      if (rand.Rndm()<0.01) {
        std::cout << " sigeff = " << ((float)A_thissig) << " / " << ((float)allsig) << " = " << sigeffs[u].back() << " +/- " << esigeffs[u].back() << std::endl;
        std::cout << " bkgeff = " << ((float)A_thisbkg) << " / " << ((float)allbkg) << " = " << bkgeffs[u].back() << " +/- " << ebkgeffs[u].back() << std::endl;
      }
    }



  }


  std::vector<TGraph*> graphs;
  std::vector<EColor> cols;
  cols.push_back(kRed);
  cols.push_back(kBlue);
  cols.push_back(kBlack);
  cols.push_back(kGreen);
  cols.push_back(kCyan);
  cols.push_back(kMagenta);
  cols.push_back(kYellow);
  for (unsigned u = 0 ; u < classifiers.size() ; ++u) {
    graphs.push_back(new TGraphErrors(sigeffs[u].size(), &sigeffs[u][0], &bkgeffs[u][0], &esigeffs[u][0], &ebkgeffs[u][0]));
    graphs.back()->SetFillColor(0);
    if (u!=0u) {
      graphs.back()->SetLineColor(cols[u]);
      graphs.back()->SetMarkerColor(cols[u]);
      graphs.back()->SetMarkerStyle(0);
    } else {
      graphs.back()->SetMarkerStyle(5);
      graphs.back()->SetMarkerColor(cols[u]);
      graphs.back()->SetLineColor(cols[u]);
    }
    graphs.back()->SetTitle(titles[u]);
  }

  TCanvas* c = new TCanvas();
  unsigned firstplot = 0u;
  //graphs[firstplot]->Draw("al");
  bool drew = false;
  for (unsigned u = 0u ; u < classifiers.size() ; ++u) {
    //if (firstplot==u) continue;
    if (drew) {
      graphs[u]->Draw("l same");
    } else {
      drew = true;
      graphs[u]->Draw("al");
    }
  }
  //graphs[firstplot]->Draw("5 same");
  c->BuildLegend()->SetFillColor(0);

  TFile* res = new TFile("/tmp/results.root","recreate");
  res->WriteTObject(c);
  for (unsigned u = 0 ; u < classifiers.size() ; ++u) {
    res->WriteTObject(graphs[u]);
  }
  bufferfileS->Close();
  bufferfileB->Close();
  delete bufferfileS;
  delete bufferfileB;

}

int nb_vs_tmva() {
  mcroc();
  return 0;
}
