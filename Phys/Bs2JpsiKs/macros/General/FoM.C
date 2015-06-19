/////////////////////////////////////////////
// ***** Bs2JpsiKs - Figure of Merit ***** //
/////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Make a fancy plot of the Figure of Merit curve

/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TPaveText.h"

using namespace RooFit;

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void FancyPlot(Int_t tracktype = 3){

  // ***** Initialize ***** //
  ////////////////////////////
  
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;

  // ***** Load Root File ***** //
  ////////////////////////////////

  TFile* m_file = TFile::Open("B2JpsiKs-BR-random-LHCb2011-Net2.root");// Double Net
  
  TString name = "";
  if(tracktype==3) name = " vs NNcut - odd && LL==3 && net>0.580"; // Best cut of Linear Optimisation
  else if(tracktype==5) name = " vs NNcut - odd && LL==5 && net>0.690"; // Best cut of Linear Optimisation
  TGraphErrors *grS = (TGraphErrors *)m_file->Get("Signal"+name);
  TGraphErrors *grB = (TGraphErrors *)m_file->Get("Background"+name);
  TGraphErrors *grSig = (TGraphErrors *)m_file->Get("Significance"+name);
  
  // ***** Edit ***** //
  //////////////////////  
  
  Int_t numSig = grSig->GetN();
  for(Int_t i=(numSig-1); i>0; i--){
    if(grSig->GetErrorY(i)>10 || grSig->GetErrorY(i)<0) grSig->RemovePoint(i);
  }
  
  // ***** Plot ***** //
  //////////////////////
  
  // *** Canvas ***
  TCanvas *doek_Sig = new TCanvas("doek_Sig","Efficiency",900,800);
  doek_Sig->SetLeftMargin(0.2);
  doek_Sig->SetBottomMargin(0.15);
  doek_Sig->cd(1);
  
	// Add titles
  grSig->GetXaxis()->SetTitle("Network Output Cut");
  grSig->GetYaxis()->SetTitle("Punzi Figure of Merit");

  // Plot range
  grSig->SetMaximum(13);
  grSig->SetMinimum(0);
  grSig->GetXaxis()->SetRangeUser(0.,1.);
  //grSig->GetXaxis()->SetNdivisions(-405);

  // Cosmetics
  grSig->GetXaxis()->SetTitleSize(0.07);
  grSig->GetXaxis()->SetTitleOffset(1);
  grSig->GetXaxis()->SetLabelSize(0.05);
  grSig->GetXaxis()->SetTitleFont(132);
  grSig->GetXaxis()->SetLabelFont(132);

  grSig->GetYaxis()->SetTitleSize(0.07);
  grSig->GetYaxis()->SetTitleOffset(1);
  grSig->GetYaxis()->SetLabelSize(0.05);
  grSig->GetYaxis()->SetTitleFont(132);
  grSig->GetYaxis()->SetLabelFont(132);

	grSig->SetMarkerStyle(23);
	grSig->SetMarkerSize(0.8);
  grSig->SetMarkerColor(4);
  grSig->SetLineColor(4);
  grSig->SetLineWidth(1);

  // Draw
  grSig->Draw("APL");
  
  
  Float_t black_pointx[2];
  black_pointx[0] = (tracktype==3 ? NNcut_LL : NNcut_DD);
  black_pointx[1] = black_pointx[0];
  Float_t black_pointy[4];
  black_pointy[0] = 0;
  black_pointy[1] = 2500.;
  TGraph *black_contour = new TGraph(2,black_pointx,black_pointy);
  black_contour->SetLineColor(1);
  black_contour->SetLineWidth(2);
  black_contour->Draw("");

  // *** Further Decoration *** //
  ////////////////////////////////
  
  // *** LHCb Tag ***
  TPaveText *lhcbTag = new TPaveText(0.25,0.72,0.54,0.89,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  TString track = "";
  if(tracktype==3) track = "Long K_{S}^{0}";
  else if(tracktype==5) track = "Downstream K_{S}^{0}";
  lhcbTag->AddText("#splitline{LHCb 2011}{#splitline{#scale[0.7]{Reco 12 - Stripping 17b}}{#scale[0.7]{"+track+"}}}");
  lhcbTag->Draw("");
  
  // *** Save ***
  TString savestring = "";
  if(tracktype==3) savestring = "_LL_Net2.pdf";
  else if(tracktype==5) savestring = "_DD_Net2.pdf";
  doek_Sig->SaveAs("Significance"+savestring);
  
  
  // ***** Plot ***** //
  //////////////////////
  
  // *** Canvas ***
  TCanvas *doek_SB = new TCanvas("doek_SB","Efficiency",900,800);
  doek_SB->SetLeftMargin(0.2);
  doek_SB->SetBottomMargin(0.15);
  doek_SB->cd(1);
  
	// Add titles
  grS->GetXaxis()->SetTitle("Network Output Cut");
  grS->GetYaxis()->SetTitle("Surviving Events");

  // Plot range
  grS->SetMaximum(tracktype==3 ? 600 : 2200);
  grS->SetMinimum(0);
  grS->GetXaxis()->SetRangeUser(0.,1.);

  // Cosmetics
  grS->GetXaxis()->SetTitleSize(0.07);
  grS->GetXaxis()->SetTitleOffset(1);
  grS->GetXaxis()->SetLabelSize(0.05);
  grS->GetXaxis()->SetTitleFont(132);
  grS->GetXaxis()->SetLabelFont(132);

  grS->GetYaxis()->SetTitleSize(0.07);
  grS->GetYaxis()->SetTitleOffset(1);
  grS->GetYaxis()->SetLabelSize(0.05);
  grS->GetYaxis()->SetTitleFont(132);
  grS->GetYaxis()->SetLabelFont(132);

	grS->SetMarkerStyle(23);
	grS->SetMarkerSize(0.8);
  grS->SetMarkerColor(4);
  grS->SetLineColor(4);
  grS->SetLineWidth(1);
  
	grB->SetMarkerStyle(21);
	grB->SetMarkerSize(0.8);
  grB->SetMarkerColor(2);
  grB->SetLineColor(2);
  grB->SetLineWidth(1);  

  // Draw
  grS->Draw("APL");
  grB->Draw("PL");
  black_contour->Draw("");
  lhcbTag->Draw("");
  
  // *** Legend *** //
  ////////////////////
  // Very nasty trick to get the dot in he legend in the correct color
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(1);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);

  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);

  TLegend *leg = new TLegend(0.25,0.65,0.42,0.73);
  leg->AddEntry(blue_contour,"Signal","lep");
  leg->AddEntry(red_contour,"Background","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");

  
  doek_SB->SaveAs("Surviving_Events"+savestring);
  
}

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void sWeights(TString net = "1", Int_t mytrack = 3){

  // ***** Initialize ***** //
  ////////////////////////////
  
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;
  Double_t plotMin = -0.05;
  Double_t plotMax = 0.40;

  // ***** Load NTuple ***** //
  /////////////////////////////
  
  TChain* chain = new TChain("chain");
  if(net=="1") chain->Add("B2JpsiKs-Weights-1-random-LHCb2011.root/WeightTree_Merged");
  else if(net=="2") chain->Add("B2JpsiKs-Weights-2-random-LHCb2011.root/WeightTree_Merged");
  
  Long64_t nEntries = chain->GetEntries();
  //nEntries = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries << std::endl;
  
  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
  Double_t mass[10];
  Double_t sweightB[10];
  Double_t sweightNonPeaking[10];
  Int_t tracktype = -999;
  Int_t PVs = -999;
  
  // *** Set Branch Addresses ***
  chain->SetBranchAddress("mass", &mass);
  chain->SetBranchAddress("sweightB", &sweightB);
  chain->SetBranchAddress("sweightNonPeaking", &sweightNonPeaking);
  chain->SetBranchAddress("tracktype", &tracktype);
  chain->SetBranchAddress("PVs", &PVs);
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////
  
  // *** Observable ***
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
  RooRealVar *weight = new RooRealVar("weight","weight",0.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass,*weight);
  RooDataSet *data_Sig = new RooDataSet("data_Sig","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Bkg = new RooDataSet("data_Bkg","Unbinned dataset",*Obs, WeightVar(*weight));
  
  // ***** Loop over Entries ***** //
  ///////////////////////////////////

  Double_t tot_Sig = 0;
  Double_t tot_Bkg = 0;

  std::cout << "=== Get Weights ===" << std::endl;
  for(Long64_t i=0; i<nEntries; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries << " (" << 100*i/nEntries << "%)" << std::endl;

    for(Int_t pv = 0; pv < PVs ; pv++){
      if(sweightB[pv]>=-1 && tracktype==mytrack) tot_Sig += sweightB[pv];
      if(sweightNonPeaking[pv]>=-1 && tracktype==mytrack) tot_Bkg += sweightNonPeaking[pv];
    }
  }  

  std::cout << "=== Get Data ===" << std::endl;
  for(Long64_t i=0; i<nEntries; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries << " (" << 100*i/nEntries << "%)" << std::endl;

    for(Int_t pv = 0; pv < PVs ; pv++){
      if(sweightB[pv]>=-1 && tracktype==mytrack){
        Bmass->setVal(mass[pv]);
        weight->setVal(sweightB[pv]/tot_Sig);
        data_Sig->add(*Obs, weight->getVal());
      }
      if(sweightNonPeaking[pv]>=-1 && tracktype==mytrack){
        Bmass->setVal(mass[pv]);
        weight->setVal(sweightNonPeaking[pv]/tot_Bkg);
        data_Bkg->add(*Obs, weight->getVal());
      }
    }
  }


  // ***** Plot ***** //
  //////////////////////
  
  // *** Frame ***
  RooPlot* BFrame = Bmass->frame(Bins(68));

  // Titles
  BFrame->SetYTitle("Events/(5 MeV/c^{2})");
  BFrame->SetXTitle("B mass (MeV/c^{2})");

  // Cosmetics
  BFrame->SetTitleOffset(1.2,"y");
  BFrame->SetTitleSize(0.07,"x");
  BFrame->SetTitleSize(0.07,"y");
  BFrame->SetTitleFont(132,"y");
  BFrame->SetTitleFont(132,"x");
  BFrame->SetLabelSize(0.05,"y");
  BFrame->SetLabelSize(0.05,"x");
  BFrame->SetLabelFont(132,"x");
  BFrame->SetLabelFont(132,"y");

  data_Sig->plotOn(BFrame,MarkerStyle(23),MarkerSize(0.8),MarkerColor(4));
  data_Bkg->plotOn(BFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2));
  
  BFrame->SetMinimum(plotMin);
  BFrame->SetMaximum(plotMax);
  
  // *** Canvas ***
  TCanvas* doek = new TCanvas("doek","Observable",900,800);
  doek->SetLeftMargin(0.2);
  doek->SetBottomMargin(0.15);
  doek->cd(1);
  BFrame->Draw();
  
  // *** Further Decoration *** //
  ////////////////////////////////
  
  // *** Exclusion Box ***
  TBox* box = new TBox(5340,plotMin,5390,plotMax-0.001);
  box->SetFillColor(18);
  box->Draw();
  BFrame->Draw("same");
    
  Float_t black_pointx[2];
  black_pointx[0] = 5340;
  black_pointx[1] = black_pointx[0];
  black_pointx[2] = 5390;
  black_pointx[3] = black_pointx[2];
  Float_t black_pointy[4];
  black_pointy[0] = plotMin;
  black_pointy[1] = plotMax+0.01;
  black_pointy[2] = black_pointy[1];
  black_pointy[3] = black_pointy[0];
  TGraph *black_contour = new TGraph(4,black_pointx,black_pointy);
  black_contour->SetLineColor(1);
  black_contour->SetLineWidth(2);
  black_contour->Draw("");
  
  // *** LHCb Tag ***
  TPaveText *lhcbTag = new TPaveText(0.65,0.72,0.89,0.89,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  TString track = "";
  if(mytrack==3) track = "Long K_{S}^{0}";
  else if(mytrack==5) track = "Downstream K_{S}^{0}";
  lhcbTag->AddText("#splitline{LHCb 2011}{#splitline{#scale[0.6]{Reco 12 - Stripping 17b}}{#scale[0.6]{"+track+"}}}");
  lhcbTag->Draw("");

  // *** Legend *** //
  ////////////////////
  // Very nasty trick to get the dot in he legend in the correct color
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(1);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);

  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);

  TLegend *leg = new TLegend(0.66,0.65,0.83,0.73);
  leg->AddEntry(blue_contour,"Signal","lep");
  leg->AddEntry(red_contour,"Background","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  
  TString savestring = "";
  if(mytrack==3) savestring = "_LL.pdf";
  else if(mytrack==5) savestring = "_DD.pdf";
  doek->SaveAs("sWeights_Net"+net+savestring);

}
