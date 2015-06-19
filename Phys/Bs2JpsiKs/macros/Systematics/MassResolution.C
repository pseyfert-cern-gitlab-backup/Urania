///////////////////////////////////////////////////////////////////
// ***** Study the Effect of Difference in Mass Resolution ***** //
///////////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Fit the Bs mass distribution
// - Study the effect of differences in the mass resolution with the Bd component


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, Int_t logy=0);


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void Resolution(TString which, Int_t tracktype = 0){

// ***** Initialize ***** //
////////////////////////////

  // *** Settings ***
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;
  
  // *** Plot Settings ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;
  Int_t nBins = (Bmass_max-Bmass_min)/5;

// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

// This is done to easily handle the selection cuts and allows semi-automatic looping over these cuts

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
 
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-SigBs.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-SigBs.root/Slim_B2JpsiKs_Tuple");
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***

  // Observable
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // Observables for Common Selection Cuts
  Float_t B_FullFit_ctau[10];
  // Trigger
  Bool_t PsiHlt1TrackMuonDecision_TOS = -999;
  Bool_t PsiHlt1DiMuonHighMassDecision_TOS = -999; 
  Bool_t PsiHlt1TrackAllL0Decision_TOS = -999;
  Bool_t PsiHlt2DiMuonDetachedJPsiDecision_TOS = -999; 
  Bool_t PsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
  Bool_t PsiHlt2DiMuonJPsiDecision_TOS = -999;
  Bool_t PsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;  
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
  // True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
  Int_t B_BKGCAT = -999;
  
  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Observables for Common Selection Cuts
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  // Trigger
  chain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
  chain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
  chain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);  
  chain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
  chain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
  chain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
  chain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);  
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass);
  RooDataSet *data = new RooDataSet("data","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;
  
  bool TruthMatch = false;
  bool Trigger = false;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    // Truth Match
    if(TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && B_BKGCAT==20) TruthMatch = true;
    else TruthMatch = false;
    
    // Trigger
    Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
              (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
               PsiHlt2TopoMu2BodyBBDTDecision_TOS);
    
    if(TruthMatch && Trigger && (piminus_TRACK_Type==tracktype || tracktype==0)){
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        if(B_FullFit_M[pv]>Bmass_min && B_FullFit_M[pv]<Bmass_max){
          if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){
        
            Bmass->setVal(B_FullFit_M[pv]);
            data->add(*Obs);
          }
        }
      }
    }
  }

  // Free Memory
  delete chain;


// ***** Part II: Mass Fit ***** //
///////////////////////////////////  

  std::cout << std::endl;
  std::cout << "== Part II: Mass Fit ==" << std::endl;
  std::cout << "=======================" << std::endl;
  
  // ***** Mass Model ***** //
  ////////////////////////////

  // *** Define Parameters ***
  Double_t apar_I_Val = (tracktype==3 ? 1.3124 : (tracktype==5 ? 2.3394 : 2.3045));
  Double_t apar_II_Val = (tracktype==3 ? -1.4314 : (tracktype==5 ? -2.2482 : -2.2074));
  Double_t fracB_Val = (tracktype==3 ? 0.47458 : (tracktype==5 ? 0.64630 : 0.65254));
  Double_t npar_I_Val = (tracktype==3 ? 4.0188 : (tracktype==5 ? 1.7084 : 1.7497));
  Double_t npar_II_Val = (tracktype==3 ? 124.48 : (tracktype==5 ? 6.6748 : 7.4342));
  Double_t sigmaB_I_Val = (tracktype==3 ? 5.1423 : (tracktype==5 ? 6.2735 : 5.9641));
  Double_t sigmaB_II_Val = (tracktype==3 ? 6.8683 : (tracktype==5 ? 10.884 : 10.525));
  
  if(NNcut_LL>0.5){
    apar_I_Val = (tracktype==3 ? 1.2128 : (tracktype==5 ? 2.4783 : 2.3869));
    apar_II_Val = (tracktype==3 ? -1.5172 : (tracktype==5 ? -2.5354 : -2.4101));
    fracB_Val = (tracktype==3 ? 0.41314 : (tracktype==5 ? 0.67070 : 0.67072));
    npar_I_Val = (tracktype==3 ? 5.1266 : (tracktype==5 ? 1.8101 : 1.9366));
    npar_II_Val = (tracktype==3 ? 145.50 : (tracktype==5 ? 7.4710 : 8.8797));
    sigmaB_I_Val = (tracktype==3 ? 4.9750 : (tracktype==5 ? 6.1474 : 5.8081));
    sigmaB_II_Val = (tracktype==3 ? 6.5592 : (tracktype==5 ? 10.326 : 9.9057));
  }

  // Signal
  RooRealVar *meanBs = new RooRealVar("meanBs","Position of Bs mass peak",5366.,Bmass_min,Bmass_max);
  RooRealVar *sigmaB_I = new RooRealVar("sigmaB_I","Width of Bd mass peak",sigmaB_I_Val,1.0,25.0);
  RooRealVar *sigmaB_II = new RooRealVar("sigmaB_II","Width of Bd mass peak",sigmaB_II_Val,1.0,25.0);
  RooRealVar *fracB = new RooRealVar("fracB","Fraction of model I",fracB_Val,0.,1.);
  RooRealVar *apar_I = new RooRealVar("apar_I","A parameter of Crystal Ball I",apar_I_Val,0.,5.);
  RooRealVar *apar_II = new RooRealVar("apar_II","A parameter of Crystal Ball II",apar_II_Val,-5.,0.);
  RooRealVar *npar_I = new RooRealVar("npar_I","N parameter of Crystal Ball I",npar_I_Val,0.,25.);
  RooRealVar *npar_II = new RooRealVar("npar_II","N parameter of Crystal Ball II",npar_II_Val,0.,250.);

  // *** PDF ***
  // Bs Signal
  RooCBShape *CBall_Bs_I = new RooCBShape("CBall_Bs_I","Crystal Ball model",*Bmass,*meanBs,*sigmaB_I,*apar_I,*npar_I);
  RooCBShape *CBall_Bs_II = new RooCBShape("CBall_Bs_II","Reflected Crystal Ball model",*Bmass,*meanBs,*sigmaB_II,*apar_II,*npar_II);
  RooAddPdf *double_CBall_Bs = new RooAddPdf("double_CBall_Bs","Double Crystal Ball",RooArgList(*CBall_Bs_I,*CBall_Bs_II),*fracB);


  // *** Fit ***
  apar_I->setConstant();
  apar_II->setConstant();
  npar_I->setConstant();
  npar_II->setConstant();
  fracB->setConstant();
  if(which=="PullOnly"){
    sigmaB_I->setConstant();
    sigmaB_II->setConstant();
  }
  RooFitResult *fitresult = (RooFitResult *)double_CBall_Bs->fitTo(*data,Save(),NumCPU(2));
 

// ***** Part III: Plot ***** //
////////////////////////////////

  std::cout << std::endl;
  std::cout << "== Part III: Plot ==" << std::endl;
  std::cout << "====================" << std::endl;

  // *** Frame ***
  RooPlot* BmassFrame = Bmass->frame(Bins(nBins));

  // Titles
  BmassFrame->SetYTitle("Events/(5 MeV/c^{2})");
  BmassFrame->SetXTitle("m_{J/#psi K_{S}^{0}} #scale[0.8]{(MeV/c^{2})}");

  // Cosmetics
  BmassFrame->SetTitleOffset(0.9,"x");
  BmassFrame->SetTitleOffset(1.2,"y");
  BmassFrame->SetTitleSize(0.07,"x");
  BmassFrame->SetTitleSize(0.07,"y");
  BmassFrame->SetTitleFont(132,"y");
  BmassFrame->SetTitleFont(132,"x");
  BmassFrame->SetLabelOffset(0.015,"y");
  BmassFrame->SetLabelSize(0.05,"y");
  BmassFrame->SetLabelSize(0.05,"x");
  BmassFrame->SetLabelFont(132,"x");
  BmassFrame->SetLabelFont(132,"y");

  // The order is important for the pull plot
  data ->plotOn(BmassFrame,MarkerStyle(8),MarkerSize(0.8)); 
  double_CBall_Bs->plotOn(BmassFrame,Range(Bmass_min,Bmass_max),LineColor(4),LineWidth(2));
  
  BmassFrame->SetMinimum(0.9);
  BmassFrame->SetMaximum(50000);
  
  // Pull
  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
  TString saveString("MassResolution_SigBs"+which);
  if(tracktype==3) saveString.Append("_LL");
  else if(tracktype==5) saveString.Append("_DD");
  if(NNcut_LL>-1) saveString.Append(buffer);
  else saveString.Append("_LooseCuts");
  saveString.Append(".pdf");
  
  PullPlot(saveString,BmassFrame,1);

    
  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;  
  std::cout << "========================" << std::endl;
  std::cout << "== Results: NN"+which+" - "+(tracktype==3 ? "Long" : (tracktype==5 ? "Down" : "All"))+" ==" << std::endl;
  std::cout << "========================" << std::endl;
  fitresult->Print();
  
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, Int_t logy){
  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
	doek->cd(1);
	Float_t ratio = 0.30; // Percentage of the plot for Pull distributions
	
	// *** Pull Plot ***
  RooPlot* pullframe = (RooPlot *)frame->emptyClone("pullframe");
	
	// Titles
  pullframe->SetYTitle("Pull");
  pullframe->SetXTitle(frame->GetXaxis()->GetTitle());

  // Cosmetics
  pullframe->SetTitleOffset(0.9,"x");
  pullframe->SetTitleSize(0.07,"x");
  pullframe->SetTitleFont(132,"x");
  pullframe->SetLabelSize(0.05,"x");
  pullframe->SetLabelFont(132,"x");
  pullframe->SetTitleSize(0,"y");// No title here	
	pullframe->SetLabelSize(0.03,"y");// and no labels
  pullframe->SetLabelFont(132,"y");	
	
	// Fill - And specify plot option: Bar-chart
	pullframe->addObject((TObject*)frame->pullHist(),"B");
	// Extract the histogram in orde to apply plot options
	TGraph* pullgraph = (TGraph*) pullframe->getObject(0);
	//pullgraph->SetLineWidth(2);
	pullgraph->SetFillColor(4);
	pullgraph->SetFillStyle(1001);
	
	// General Settings
  pullframe->SetMinimum(-5);
	pullframe->SetMaximum(5);
	pullframe->GetYaxis()->SetNdivisions(503,kTRUE);
	
	// *** Place the first frame ***
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
	xPad->SetLeftMargin(0.2);
	xPad->SetBottomMargin(ratio);	
	// Draw Pad	
	xPad->Draw();
	xPad->cd();
	xPad->SetLogy(logy);
	// Suppress X-axis decoration
	frame->SetLabelSize(0,"x");
	frame->SetTitleSize(0,"x");
  frame->SetLabelOffset(0.015,"y");
	// Fill Pad	
	frame->Draw("");
	
	
  // *** LHCb Tag *** 
  string convSave (savestring);
  size_t isBd=convSave.find("SigBd");
  size_t isBs=convSave.find("SigBs");
  size_t isLL=convSave.find("LL");
  size_t isDD=convSave.find("DD");
  
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
  
	TPaveText *lhcbTag = 0;
  double offset = 0.;
  if(isBd==string::npos && isBs==string::npos) offset = 0.04;
	if(logy==1){lhcbTag = new TPaveText(0.23,0.70,0.47+offset,0.89,"NDC");}
	//if(logy==1){lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");}
	if(logy==0){lhcbTag = new TPaveText(0.65,0.35,0.89,0.47,"NDC");}

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(isBd!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else if(isBs!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else lhcbTag->AddText("#splitline{LHCb 2011}{#splitline{#scale[0.7]{Reco 12 - Stripping 17b}}{#scale[0.7]{"+track+"}}}");
  lhcbTag -> Draw("");
		
	
	// *** Place the second frame ***
	// go back to the Bottom layer
	doek->cd();
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* pullPad = new TPad("pullPad", "Pad for Pull Plot", 0., 0., 1., 1);
	pullPad->SetLeftMargin(0.2);
	pullPad->SetBottomMargin(0.15);	
	pullPad->SetTopMargin(1-ratio+0.01);
	// Make the pad transparent
	pullPad->SetFillColor(0);
	pullPad->SetFillStyle(0);
	// Draw Pad	
	pullPad->Draw();
	pullPad->cd();
	// Fill Pad - Draw Y axis on the right side such that it doesn't overlap
	pullframe->Draw("");

	// *** Save ***
	doek->SaveAs(savestring);
	
	// *** Clean Up ***
	delete lhcbTag;
	delete xPad;
	delete pullPad;
	delete pullframe;
	delete doek;
	return;
}
