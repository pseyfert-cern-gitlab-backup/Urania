#include <iostream>
#include <fstream>
#include <vector>

#include "TCanvas.h"
#include "TTree.h"
#include "TApplication.h"
#include "TMath.h"
#include "TFile.h"
#include "zstyle.h"
#include "TString.h"
#include "TAxis.h"
// This lib contains the definition of the cuts 
#include "cutsdefinition.h" 
#include "Measurement.h" 
// RooFit
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPhysBkg.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooWorkspace.h"

using namespace std;

int main(int argc, char **argv){
  zstyle();
  TApplication theApp("App", &argc, argv);
  // Get the file where the MvsBDT workspace is in (all but masscut!!)
  TFile f("BuPiMuMu_wspc.root");
  RooWorkspace* w = (RooWorkspace*)f.Get("w");
  float masshigh = 6000.;
  float masslow  = 4200.;

  TLatex *   tex            = new TLatex(0.7,0.83,"LHCb");
  
  // Variable masscut
  TString masscut = Form("B_s0_M > %f && B_s0_M< %f", masslow, masshigh);

  RooRealVar* m                       = (RooRealVar*)w->var("B_s0_M");
  //RooRealVar* bdt                     = new RooRealVar("BDT12flat", "Bdt", 0, 1);
  

  RooDataSet* data_mass     = (RooDataSet*)w->data("MvsBdt");
  Double_t bdtbins[8+1] = {0, 0.25, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  RooDataSet* data[8];
  RooFitResult* r[8];
  for(int ii=0; ii<8;ii++){
    std::cout << "reducing datasets: bin " << ii+1 << endl;
    data[ii]   = (RooDataSet*)data_mass->reduce(RooFit::Cut(Form("BDT12flat>=%f && BDT12flat<%f && "+masscut,bdtbins[ii],bdtbins[ii+1])));
    std::cout << "entries in bin " << ii+1 << " : " << data[ii]->numEntries() << std::endl;
  }
  // fit function
  for(int iii=0; iii<8;iii++){
    std::cout << "BEGIN NEW BIN! -> " << iii+1 << std::endl;
    TString mass_name     = "B_s0_M";
    //RooRealVar *mass      = new RooRealVar(mass_name,"m(#mu^{+}#mu^{-}) MeV", 4000, 5600);
    RooRealVar *sh_mean   = new RooRealVar("mean","mean",5360, 4200, 5500);
    RooRealVar *sh_sigma  = new RooRealVar("sigma","sigma", 50, 0, 100);
    RooRealVar *sh_c      = new RooRealVar("sh_c", "sh_c", 0.001, 0.000001, 0.5);

    RooPhysBkg *phys      =  new RooPhysBkg("shoulder", 
                                            "shoulder pdf", 
                                            *m, *sh_mean, 
                                            *sh_c, *sh_sigma);

    RooPlot *frame = m->frame(RooFit::Title(" "),RooFit::Range(masslow,masshigh),RooFit::Bins(36));
    data[iii]->plotOn(frame);
    r[iii]  = phys->fitTo(*data[iii],RooFit::Save(),
                          RooFit::Minos(kTRUE),
                          //RooFit::Strategy(3), RooFit::Minos(kTRUE),
                          RooFit::Range(masslow,masshigh), RooFit::NumCPU(2));
    phys->plotOn(frame);
    TCanvas *canvas = new TCanvas(Form("bin %i",iii+1), Form("Mass Shape Test bin %i",iii+1), 800, 450);
    
    frame->getCurve()->SetLineWidth(3);
    frame->getCurve()->SetLineColor(kRed);
    frame->GetXaxis()->SetTitleSize(0.05);
    frame->GetXaxis()->SetTitleOffset(1.03);
    frame->GetXaxis()->SetLabelSize(0.05);
    frame->GetXaxis()->SetNoExponent();
    frame->GetYaxis()->SetTitleSize(0.05);
    frame->GetYaxis()->SetTitleOffset(1.03);
    frame->GetYaxis()->SetLabelSize(0.05);
    frame->Draw();
    // Stuff for writing on plots 
    tex->SetNDC();
    tex->SetTextAlign(12);
    tex->SetTextFont(132);
    tex->SetTextSize(0.06);
    tex->SetLineWidth(2);
    tex->DrawLatex(0.55,0.8,TString::Format("LHCb Simulations  BDT-Bin %i", iii+1));
    TString drawString  = Form("Mean:    %4.4f  +-  %3.4f", sh_mean->getVal(), sh_mean->getError());
    tex->DrawLatex(0.55, 0.7, drawString);
    drawString          = Form("Sigma:   %4.4f  +-  %3.4f", sh_sigma->getVal(), sh_sigma->getError());
    tex->DrawLatex(0.55, 0.6, drawString);
    drawString          = Form("C:       %4.4f  +-  %3.4f", sh_c->getVal(), sh_c->getError());
    tex->DrawLatex(0.55, 0.5, drawString);
    canvas->SaveAs(Form("__testMassShape_bin_%i.pdf",iii+1));
    delete sh_mean;
    delete sh_sigma; 
    delete sh_c;
  } 

  ofstream out("summary/Bu2Pimumu_RPB_params.txt");
  for(int ii =1; ii<=8; ii++){
    const RooArgList pr = r[ii-1]->floatParsFinal();
    RooRealVar *mean = (RooRealVar*)pr.at(0);
    out << mean->getValV() << " \t " << mean->getError() << " \t # Mean for bin " << ii << endl;
    RooRealVar *shc = (RooRealVar*)pr.at(1);
    out << shc->getValV() << " \t " << shc->getError() <<  " \t # Shc for bin " << ii << endl;
    RooRealVar *sigma = (RooRealVar*)pr.at(2);
    out << sigma->getValV() << " \t " << sigma->getError() <<  " \t # Sigma for bin " << ii << endl;
  }

  delete m;
  delete data_mass;
  theApp.Run();
  return 0;
}


/*
//Trigger
  RooRealVar B_s0L0MuonDecision_Dec("B_s0L0MuonDecision_Dec", "B_s0L0MuonDecision_Dec", 0, 1);
  RooRealVar B_s0L0DiMuonDecision_Dec("B_s0L0DiMuonDecision_Dec", "B_s0L0DiMuonDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt1DiMuonLowMassDecision_Dec("B_s0Hlt1DiMuonLowMassDecision_Dec", "B_s0Hlt1DiMuonLowMassDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt1DiMuonHighMassDecision_Dec("B_s0Hlt1DiMuonHighMassDecision_Dec", "B_s0Hlt1DiMuonHighMassDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt1TrackMuonDecision_Dec("B_s0Hlt1TrackMuonDecision_Dec", "B_s0Hlt1TrackMuonDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt1SingleMuonNoIPDecision_Dec("B_s0Hlt1SingleMuonNoIPDecision_Dec", "B_s0Hlt1SingleMuonNoIPDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt1SingleMuonHighPTDecision_Dec("B_s0Hlt1SingleMuonHighPTDecision_Dec", "B_s0Hlt1SingleMuonHighPTDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt1TrackAllL0Decision_Dec("B_s0Hlt1TrackAllL0Decision_Dec", "B_s0Hlt1TrackAllL0Decision_Dec", 0, 1);
  RooRealVar B_s0Hlt2DiMuonBDecision_Dec("B_s0Hlt2DiMuonBDecision_Dec", "B_s0Hlt2DiMuonBDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2DiMuonDecision_Dec("B_s0Hlt2DiMuonDecision_Dec", "B_s0Hlt2DiMuonDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2DiMuonDetachedDecision_Dec("B_s0Hlt2DiMuonDetachedDecision_Dec", "B_s0Hlt2DiMuonDetachedDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2DiMuonDetachedJPsiDecision_Dec("B_s0Hlt2DiMuonDetachedJPsiDecision_Dec", "B_s0Hlt2DiMuonDetachedJPsiDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2DiMuonDetachedHeavyDecision_Dec("B_s0Hlt2DiMuonDetachedHeavyDecision_Dec", "B_s0Hlt2DiMuonDetachedHeavyDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2SingleMuonDecision_Dec("B_s0Hlt2SingleMuonDecision_Dec", "B_s0Hlt2SingleMuonDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2SingleMuonHighPTDecision_Dec("B_s0Hlt2SingleMuonHighPTDecision_Dec", "B_s0Hlt2SingleMuonHighPTDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2TopoMu2BodyBBDTDecision_Dec("B_s0Hlt2TopoMu2BodyBBDTDecision_Dec", "B_s0Hlt2TopoMu2BodyBBDTDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2TopoMu3BodyBBDTDecision_Dec("B_s0Hlt2TopoMu3BodyBBDTDecision_Dec", "B_s0Hlt2TopoMu3BodyBBDTDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2TopoMu4BodyBBDTDecision_Dec("B_s0Hlt2TopoMu4BodyBBDTDecision_Dec", "B_s0Hlt2TopoMu4BodyBBDTDecision_Dec", 0, 1);
  RooRealVar B_s0Hlt2DiMuonJPsiDecision_Dec("B_s0Hlt2DiMuonJPsiDecision_Dec", "B_s0Hlt2DiMuonJPsiDecision_Dec", 0, 1);
  // Fiducial
  RooRealVar B_s0_PT("B_s0_PT", "B_s0_PT", 0, 1000000);
  RooRealVar B_s0_TAU("B_s0_TAU", "B_s0_TAU", 0, 1100000);
  RooRealVar muminus_P("muminus_P", "muminus_P", 0, 1000000);
  RooRealVar muplus_P("muplus_P", "muplus_P", 0, 1000000);
  RooRealVar muminus_PT("muminus_PT", "muminus_PT", 0, 1000000);
  RooRealVar muplus_PT("muplus_PT", "muplus_PT", 0, 1000000);
  RooRealVar muplus_PIDmu("muplus_PIDmu", "muplus_PIDmu", -100, 100);
  RooRealVar muplus_PIDK("muplus_PIDK", "muplus_PIDK", -100, 100);
  RooRealVar muminus_PIDmu("muminus_PIDmu", "muminus_PIDmu", -100, 100);
  RooRealVar muminus_PIDK("muminus_PIDK", "muminus_PIDK", -10, 100);
  RooRealVar B_s0_BDTS("B_s0_BDTS", "B_s0_BDTS", 0, 1);
  //ghost
  RooRealVar muplus_TRACK_GhostProb("muplus_TRACK_GhostProb", "muplus_TRACK_GhostProb", 0, 1);
  RooRealVar muminus_TRACK_GhostProb("muminus_TRACK_GhostProb", "muminus_TRACK_GhostProb", 0, 1);
  // MC MATCH
  RooRealVar muplus_TRUEID("muplus_TRUEID", "muplus_TRUEID", -1000000, 1000000);
  RooRealVar muminus_TRUEID("muminus_TRUEID", "muminus_TRUEID", -1000000, 1000000);
  RooRealVar muplus_MC_MOTHER_ID("muplus_MC_MOTHER_ID", "muplus_MC_MOTHER_ID", -1000000, 1000000);
  RooRealVar muminus_MC_MOTHER_ID("muminus_MC_MOTHER_ID", "muminus_MC_MOTHER_ID", -1000000, 1000000);
  RooRealVar muplus_MC_GD_MOTHER_ID("muplus_MC_GD_MOTHER_ID", "muplus_MC_GD_MOTHER_ID", -1000000, 1000000);
  RooRealVar muminus_MC_GD_MOTHER_ID("muminus_MC_GD_MOTHER_ID", "muminus_MC_GD_MOTHER_ID", -1000000, 1000000);

  RooArgSet set(*m,*bdt,B_s0L0MuonDecision_Dec,
  B_s0L0DiMuonDecision_Dec,
  B_s0Hlt1DiMuonLowMassDecision_Dec,
  B_s0Hlt1DiMuonHighMassDecision_Dec,
  B_s0Hlt1TrackMuonDecision_Dec);
  
  set.add(B_s0Hlt1SingleMuonNoIPDecision_Dec);
  set.add(B_s0Hlt1SingleMuonHighPTDecision_Dec);
  set.add(B_s0Hlt1TrackAllL0Decision_Dec);
  set.add(B_s0Hlt2DiMuonBDecision_Dec);
  set.add(B_s0Hlt2DiMuonDecision_Dec);
  set.add(B_s0Hlt2DiMuonDetachedDecision_Dec);
  set.add(B_s0Hlt2DiMuonDetachedJPsiDecision_Dec);
  set.add(B_s0Hlt2DiMuonDetachedHeavyDecision_Dec);
  set.add(B_s0Hlt2SingleMuonDecision_Dec);
  set.add(B_s0Hlt2SingleMuonHighPTDecision_Dec);
  set.add(B_s0Hlt2TopoMu2BodyBBDTDecision_Dec);
  set.add(B_s0Hlt2TopoMu3BodyBBDTDecision_Dec);
  set.add(B_s0Hlt2TopoMu4BodyBBDTDecision_Dec);
  set.add(B_s0Hlt2DiMuonJPsiDecision_Dec);
  set.add(B_s0_PT);
  set.add(B_s0_TAU);
  set.add(muminus_P);
  set.add(muplus_P);
  set.add(muminus_PT);
  set.add(muplus_PT);
  set.add(muplus_PIDmu);
  set.add(muplus_PIDK);
  set.add(muminus_PIDmu);
  set.add(muminus_PIDK);
  set.add(B_s0_BDTS);
  set.add(muplus_TRACK_GhostProb);
  set.add(muminus_TRACK_GhostProb);
  set.add(muplus_TRUEID);
  set.add(muminus_TRUEID);
  set.add(muplus_MC_MOTHER_ID);
  set.add(muminus_MC_MOTHER_ID);
  set.add(muplus_MC_GD_MOTHER_ID);
  set.add(muminus_MC_GD_MOTHER_ID);
  */