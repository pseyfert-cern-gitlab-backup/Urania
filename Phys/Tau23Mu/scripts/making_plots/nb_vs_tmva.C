#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <vector>
#include <iostream>
#include <TRandom3.h>
#include <TGraphErrors.h>
#include <TH1F.h>
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
//TString sig_f = "/auto/data/pseyfert/Tau_MC/use.root";
//TString bkg_f = "/auto/data/pseyfert/Tau23Mu_Stripping20/v9_2nd/use.1.root";

TString sig_f = "/tmp/splot.root";
//TString bkg_f = "/afs/cern.ch/work/p/pseyfert/public/triggeremulation/allbkg.root";

std::vector<TString> classifiers;
void mcroc() {
  //classifiers.push_back("GeoMVA");
  classifiers.push_back("GeoMVA");
//  classifiers.push_back("NeuroBayes_0x141cf018");
  //classifiers.push_back("NeuroBayes_0x141cf818");
  //classifiers.push_back("NeuroBayes_0x149cf018");
  //classifiers.push_back("NeuroBayes_0x149cf818");
  classifiers.push_back("flat_TMVA_0x149cf018");
  classifiers.push_back("flat_TMVA_0x141cf818");
  classifiers.push_back("flat_TMVA_0x149cf818");
  //classifiers.push_back("flat_TMVA_v1_0x149cf818");
  //classifiers.push_back("flat_TMVA_0x149cf018");
  //classifiers.push_back("MLPCJ_v3_0x149cf818");
  //classifiers.push_back("MLPCJ_v2_0x149cf818");
  //classifiers.push_back("MLPCJ_v1_0x141cf018");

  float scanpoint = 0.5;
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
  std::vector<float> CB_bkgeff;

  TChain* testtree = new TChain("rds_data");
  //TChain* testtree = new TChain("Tau23Mu");
  testtree->Add(sig_f.Data());
  //testtree->Add(bkg_f.Data());


  TH1F* buffer = new TH1F("buffer","buffer",100,-1.1,1.1);
  TString sigstring = "truetau==15&&cleaningcut&&L0Dec&&Hlt1Dec&&cleaningcut&&mass_p0p1>250&&abs(mass_p0p2-1020.4)>20&&abs(mass_p1p2-1020.4)>20";
  //TFile* bufferfile = new TFile("/tmp/buffer.root","recreate");
  //bufferfile->cd();
  //TTree* signal = testtree->CopyTree(sigstring.Data());
  TString bkgstring = "truetau!=15&&cleaningcut&&L0Dec&&Hlt1Dec&&cleaningcut&&mass_p0p1>250&&abs(mass_p0p2-1020.4)>20&&abs(mass_p1p2-1020.4)>20&&abs(mass-1777)>20";
  //TTree* background = testtree->CopyTree(bkgstring.Data());
  std::cout << " done copying " << std::endl;
  testtree->Draw(classifiers[0]+">>buffer","yield_bkg_sw");
  //background->Draw(classifiers[0]+">>buffer","1");
  float allbkg = buffer->GetSum();
  testtree->Draw(classifiers[0]+">>buffer","yield_dst_sw");
  //signal->Draw(classifiers[0]+">>buffer","1");
  float allsig = buffer->GetSum();
  std::cout << allbkg << "\t" << allsig << std::endl;

  TRandom3 rand;

  while (scanpoint < 1.001) {
    if (scanpoint < 0.99) {
      scanpoint += 0.0075;
    } else {
      scanpoint += 0.00025;
    }

    unsigned ustart = 1u;
    //if ((fabs(scanpoint-0.05) <0.003 )|| (fabs(scanpoint-0.35) <0.003 )|| (fabs(scanpoint-0.65) <0.003 )|| (fabs(scanpoint-0.74) <0.003)) {
      //std::cout << "scanpoint = " << scanpoint << "   signature " << (fabs(scanpoint-0.05) <0.003 )<< (fabs(scanpoint-0.35) <0.003 )<< (fabs(scanpoint-0.65) <0.003 )<< (fabs(scanpoint-0.74) <0.003) << std::endl; 
      ustart = 0u;
    //}

    for (unsigned u = ustart ; u < classifiers.size() ; ++u) {
      testtree->Draw(classifiers[u]+">>buffer",Form("yield_dst_sw*(%s>%f)",classifiers[u].Data(),scanpoint));
      float A_thissig = buffer->GetSum();
      testtree->Draw(classifiers[u]+">>buffer",Form("yield_bkg_sw*(%s>%f)",classifiers[u].Data(),scanpoint));
      float A_thisbkg = buffer->GetSum();
      sigeffs[u].push_back(((float)A_thissig)/((float)allsig));
      bkgeffs[u].push_back(1.-((float)A_thisbkg)/((float)allbkg));
      esigeffs[u].push_back(sqrt((A_thissig+1)*(allsig-A_thissig+1)/(allsig+2)/(allsig+2)/(allsig+3)));
      ebkgeffs[u].push_back(sqrt((A_thisbkg+1)*(allbkg-A_thisbkg+1)/(allbkg+2)/(allbkg+2)/(allbkg+3)));
      if (rand.Rndm()<0.01) {
        std::cout << " sigeff = " << sigeffs[u].back() << " +/- " << esigeffs[u].back() << std::endl;
        std::cout << " bkgeff = " << bkgeffs[u].back() << " +/- " << ebkgeffs[u].back() << std::endl;
      }
    }



  }


  std::vector<TGraph*> graphs;
  std::vector<EColor> cols;
  cols.push_back(kRed);
  cols.push_back(kBlue);
  cols.push_back(kBlack);
  cols.push_back(kGreen);
  for (unsigned u = 0 ; u < classifiers.size() ; ++u) {
    graphs.push_back(new TGraphErrors(sigeffs[u].size(), &sigeffs[u][0], &bkgeffs[u][0], &esigeffs[u][0], &ebkgeffs[u][0]));
    graphs.back()->SetFillColor(0);
    graphs.back()->SetLineColor(cols[u]);
    graphs.back()->SetMarkerColor(cols[u]);
    //if (u==0u) {
     // graphs.back()->SetMarkerStyle(5);
    //} else {
      graphs.back()->SetMarkerStyle(0);
    //}
    graphs.back()->SetTitle(classifiers[u]);
  }

  TCanvas* c = new TCanvas();
  graphs[1]->Draw("eac");
  for (unsigned u = 0u ; u < classifiers.size() ; ++u) {
    if (u==1) continue;
    graphs[u]->Draw("e same");
  }
  c->BuildLegend()->SetFillColor(0);

  TFile* res = new TFile("/tmp/results.root","recreate");
  res->WriteTObject(c);
  for (unsigned u = 0 ; u < classifiers.size() ; ++u) {
    res->WriteTObject(graphs[u]);
  }

}

int nb_vs_tmva() {
  mcroc();
  return 0;
}
