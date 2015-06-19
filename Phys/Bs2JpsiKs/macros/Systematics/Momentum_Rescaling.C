////////////////////////////////////
// ***** Rescale B Momentum ***** //
////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Rescale the B momentum and study its effect on the decay time


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void Momentum(Double_t scale = 1, Double_t NNCut = -1.5){

// ***** Initialize ***** //
////////////////////////////

  // *** Neural Net ***
  Double_t NNcut_LL = (NNCut==1 ? 0.60 : NNCut);
  Double_t NNcut_DD = (NNCut==1 ? 0.75 : NNCut);
  
  // *** PDG ***
  Double_t mpiplus = 139.57018;
  Double_t mmuplus = 105.6583715;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////

  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-SigBd.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-SigBd.root/Slim_B2JpsiKs_Tuple");
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
        
  // Observable
  Double_t B_TRUEORIGINVERTEX_X = -999;
  Double_t B_TRUEORIGINVERTEX_Y = -999;
  Double_t B_TRUEORIGINVERTEX_Z = -999;
  Double_t B_TRUEENDVERTEX_X = -999;
  Double_t B_TRUEENDVERTEX_Y = -999;
  Double_t B_TRUEENDVERTEX_Z = -999;
  Double_t piplus_TRUEP_X = -999;
  Double_t piplus_TRUEP_Y = -999;
  Double_t piplus_TRUEP_Z = -999;
  Double_t piminus_TRUEP_X = -999;
  Double_t piminus_TRUEP_Y = -999;
  Double_t piminus_TRUEP_Z = -999;
  Double_t muplus_TRUEP_X = -999;
  Double_t muplus_TRUEP_Y = -999;
  Double_t muplus_TRUEP_Z = -999;
  Double_t muminus_TRUEP_X = -999;
  Double_t muminus_TRUEP_Y = -999;
  Double_t muminus_TRUEP_Z = -999;
  // PV Matching
  Float_t B_FullFit_PV_X[10];
  Float_t B_FullFit_PV_Y[10];
  Float_t B_FullFit_PV_Z[10];
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
  Int_t piminus_TRACK_Type = -999;
  // True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
  Int_t B_BKGCAT = -999;
  Double_t B_TRUETAU = -999;

  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
    B_FullFit_PV_X[i] = -999;
    B_FullFit_PV_Y[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    netOutput[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  chain->SetBranchAddress("B_TRUEENDVERTEX_X", &B_TRUEENDVERTEX_X);
  chain->SetBranchAddress("B_TRUEENDVERTEX_Y", &B_TRUEENDVERTEX_Y);
  chain->SetBranchAddress("B_TRUEENDVERTEX_Z", &B_TRUEENDVERTEX_Z);
  chain->SetBranchAddress("piplus_TRUEP_X", &piplus_TRUEP_X);
  chain->SetBranchAddress("piplus_TRUEP_Y", &piplus_TRUEP_Y);
  chain->SetBranchAddress("piplus_TRUEP_Z", &piplus_TRUEP_Z);
  chain->SetBranchAddress("piminus_TRUEP_X", &piminus_TRUEP_X);
  chain->SetBranchAddress("piminus_TRUEP_Y", &piminus_TRUEP_Y);
  chain->SetBranchAddress("piminus_TRUEP_Z", &piminus_TRUEP_Z);
  chain->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X);
  chain->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y);
  chain->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z);
  chain->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X);
  chain->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y);
  chain->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z);
  // PV Matching
  chain->SetBranchAddress("B_FullFit_PV_X", &B_FullFit_PV_X);
  chain->SetBranchAddress("B_FullFit_PV_Y", &B_FullFit_PV_Y);
  chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
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
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // True ID of Decay
  chain->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain->SetBranchAddress("B_TRUETAU", &B_TRUETAU);
  
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Diff = new RooRealVar("Diff","true - scaled lifetime",-1.,1.,"ps");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Diff);
  RooDataSet *data = new RooDataSet("data","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////
  
  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  
  bool TruthMatch = false;
  bool Trigger = false;
  
  Double_t flight = -999;
  Double_t momX = -999;
  Double_t momY = -999;
  Double_t momZ = -999;
  Double_t momTot = -999;
  Double_t momPiplus = -999;
  Double_t momPiminus = -999;
  Double_t momMuplus = -999;
  Double_t momMuminus = -999;
  Double_t Bmass = -999;
  Double_t Blife = -999;

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;
 
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    TruthMatch = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10));
    
    Trigger = ((PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
         (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||PsiHlt2TopoMu2BodyBBDTDecision_TOS));

    if(TruthMatch){ // Select only True Signal
        
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }

      // Loop 2: Fill
      if(NNCut<-1. || (Trigger && ((piminus_TRACK_Type==3 && netOutput[truePV]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[truePV]>NNcut_DD)))){
      
        flight = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X - B_TRUEENDVERTEX_X,2) + pow(B_TRUEORIGINVERTEX_Y - B_TRUEENDVERTEX_Y,2) + pow(B_TRUEORIGINVERTEX_Z - B_TRUEENDVERTEX_Z,2));
        momX = scale*(piplus_TRUEP_X + piminus_TRUEP_X + muplus_TRUEP_X + muminus_TRUEP_X);
        momY = scale*(piplus_TRUEP_Y + piminus_TRUEP_Y + muplus_TRUEP_Y + muminus_TRUEP_Y);
        momZ = scale*(piplus_TRUEP_Z + piminus_TRUEP_Z + muplus_TRUEP_Z + muminus_TRUEP_Z);
        momTot = TMath::Sqrt(pow(momX,2) + pow(momY,2) + pow(momZ,2));
        momPiplus = TMath::Sqrt(pow(scale*piplus_TRUEP_X,2) + pow(scale*piplus_TRUEP_Y,2) + pow(scale*piplus_TRUEP_Z,2));
        momPiminus = TMath::Sqrt(pow(scale*piminus_TRUEP_X,2) + pow(scale*piminus_TRUEP_Y,2) + pow(scale*piminus_TRUEP_Z,2));
        momMuplus = TMath::Sqrt(pow(scale*muplus_TRUEP_X,2) + pow(scale*muplus_TRUEP_Y,2) + pow(scale*muplus_TRUEP_Z,2));
        momMuminus = TMath::Sqrt(pow(scale*muminus_TRUEP_X,2) + pow(scale*muminus_TRUEP_Y,2) + pow(scale*muminus_TRUEP_Z,2));
        Bmass = TMath::Sqrt(pow(TMath::Sqrt(pow(mpiplus,2)+pow(momPiplus,2)) + TMath::Sqrt(pow(mpiplus,2)+pow(momPiminus,2)) + TMath::Sqrt(pow(mmuplus,2)+pow(momMuplus,2)) + TMath::Sqrt(pow(mmuplus,2)+pow(momMuminus,2)),2) - pow(momTot,2));
        Blife = (Bmass*flight/momTot)*pow(10.,12)/(299792458*pow(10.,3));
        Diff->setVal(100*(B_TRUETAU*1000 - Blife)/(B_TRUETAU*1000));

        if(Diff->getVal()>-1 && Diff->getVal()<1) data->add(*Obs);
      }
    }
    // Reset
    DOCA_min = 999;
  }

  // Free Memory
  delete chain;
  
  
  Double_t mean = data->mean(*Diff);
  Double_t sigma = data->sigma(*Diff);

// ***** Part II: Plot ***** //
///////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part II: Plot ==" << std::endl;
  std::cout << "===================" << std::endl;

  // *** Save String ***
  char buffer[3];
  TString savestring("Momentum_Rescale");
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  if(NNCut>-1){
    std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
    savestring.Append(buffer);
  }
  else savestring.Append("_Loose");
  Int_t scaleInt = scale*10000;
  std::sprintf(buffer,"_%d",scaleInt);
  savestring.Append(buffer);
  savestring.Append(".pdf");

	
  // *** Signal ***
  RooPlot* Frame = Diff->frame(Range(-0.01,0.05),Bins(60));

  // Titles
  Frame->SetYTitle("# Events/(0.001)");
  Frame->SetXTitle("(t_{true}-t_{scaled})/t_{true} (%)");

  // Cosmetics
  Frame->SetTitleOffset(1.2,"y");
  Frame->SetTitleSize(0.07,"x");
  Frame->SetTitleSize(0.07,"y");
  Frame->SetTitleFont(132,"y");
  Frame->SetTitleFont(132,"x");
  Frame->SetLabelSize(0.05,"y");
  Frame->SetLabelSize(0.05,"x");
  Frame->SetLabelFont(132,"x");
  Frame->SetLabelFont(132,"y");

  data->plotOn(Frame,MarkerStyle(8),MarkerSize(0.8));

  Frame->SetMinimum(0.);
  Frame->SetMaximum(150000);
  
  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","doek",900,800);
  doek->SetLeftMargin(0.2);
  doek->SetBottomMargin(0.15);
  doek->cd(1);
  //gPad->SetLogy(1);
  Frame->Draw("");
  
  // *** LHCb Tag ***   
	TPaveText *lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("#splitline{LHCb MC11a}{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}");
  lhcbTag -> Draw("");
  
  doek->SaveAs(savestring);
  
  std::cout << std::endl;
  std::cout << "(Delta t)/t for scale factor = " << scale << std::endl;
  std::cout << "  mean = " << mean << std::endl;
  std::cout << "  sigma = " << sigma << std::endl;
  
}
