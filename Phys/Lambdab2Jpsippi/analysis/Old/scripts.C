// ####################################################################################################
// Analysis code for Lambdab->(J/psi) p pi
// Authors: Alexandru Babeanu
// ####################################################################################################

// ####################################################################################################
// compile & load with 
//
// .L scripts.C++
//  AnalysisPlots() // calls LoadTrees()
//
// before calling other functions below, besides AnalysisPlots(), which does it automatically
// check whether PlotPath is properly defined 
//
// AnalysisPlots() contains all relevant function calls -- 
// including LoadTrees() -- for producing the important plots for this analysis, according to 20.08.2012
//

// used C++ classes
#include <iostream>
#include <sstream>
#include <string>

// used root classes
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TImage.h"
#include "TLegend.h"
#include "TF1.h"
#include "Math/Functor.h"
#include "TGraph.h"
#include "TString.h"

using namespace std;
using namespace RooFit;

TString goodName(TString name){
 // cout << "goodName : Name input " << name << endl ;
  name.ReplaceAll(" ","_");
  name.ReplaceAll("(","_");
  name.ReplaceAll(")","_");
  name.ReplaceAll("/","_");
  name.ReplaceAll(">","_g_");
  name.ReplaceAll("<","_l_");
  name.ReplaceAll("*","_times_");
  name.ReplaceAll(".","_");
  name.ReplaceAll("[","_");
  name.ReplaceAll("]","_");
  name.ReplaceAll("?","_");
  name.ReplaceAll("{","_");
  name.ReplaceAll("}","_");
  name.ReplaceAll("||","_or_");
  name.ReplaceAll("&&","_and_");
  name.ReplaceAll("&","_");
  name.ReplaceAll("|","_");
  name.ReplaceAll(":","_vs_");
//  cout << "Name output " << name << endl ;
  return name;
}
// global pointers to relevant trees, loaded via LoadTrees() together with associated expertises

TTree* treeS; // signal (S)
TTree* treeB; // total background (B)
TTree* treeD; // data (D)

TTree* treeB1; // first reflection background: MC11a-PsiKpi-523 (B1)
TTree* treeB2; // second reflection background: MC11a-Bd2JpsiKstar-627 (B2)
TTree* treeB3; // third reflection background: MC11a-PsipK-516 (normalization channel) (B2)



// TH1D* hInteresting; !! a global pointer to some interesting histogram, for later use ;)

// relative path to folder where all png files of crated plots are saved
TString PlotPath("../analysis/AnalysisPlots/"); 							
// absolute path to (castor) folder where all root trees are
TString TreePath("~/work/Baryons/Lambdab/"); 			
// absolute path to (local) folder where all expert-generated friends are
TString FriendPath("~/codes/Lambdab2Jpsippi/root/");	


// template function for saving plots as .png files
void pad2png()
{
  // Create a canvas and save as png.
  //Author: Valeriy Onuchin
  
  TCanvas *c = new TCanvas;
  TH1F *h = new TH1F("gaus", "gaus", 100, -5, 5);
  h->FillRandom("gaus", 10000);
  h->Draw();
   
  c->SetLogy();
   
  gSystem->ProcessEvents();
   
  TImage *img = TImage::Create();
   
  //img->FromPad(c, 10, 10, 300, 200);
  img->FromPad(c);
   
  img->WriteImage("canvas.png");
   
  delete h;
  delete c;
  delete img;
}

// loading signal MC, background MC, data and reflection MC files and combining them with their associated expertieses
// run prior to other things below !
void LoadTrees()
{
  // loading signal MC:
  TFile* fileS = TFile::Open((TreePath+"Lambdab2Jpsippi-MC11a-Psippi-521.root"));		
  treeS = (TTree*) fileS->Get("Lambdab2Jpsippi_TupleMC/DecayTree");
  
  TFile* fileSE = TFile::Open((FriendPath+"Lambdab2Jpsippi-MC11a-Psippi-521-NN.root"));		
  TTree* treeSE = (TTree*) fileSE->Get("NetTree");
  
  treeS->AddFriend(treeSE, "ExpertiseInfo");
  
  // loading background MC:
  TFile* fileB = TFile::Open((TreePath+"Lambdab2Jpsippi-MC11a-IncPsi-501.root"));		
  treeB = (TTree*) fileB->Get("Lambdab2Jpsippi_TupleMC/DecayTree");
  
  TFile* fileBE = TFile::Open((FriendPath+"Lambdab2Jpsippi-MC11a-IncPsi-501-NN.root"));		
  TTree* treeBE = (TTree*) fileBE->Get("NetTree");
  
  treeB->AddFriend(treeBE, "ExpertiseInfo");
  
  // loading data:
  TFile* fileD = TFile::Open((TreePath+"Lambdab-R12S17b-435-436.root"));		
  treeD = (TTree*) fileD->Get("BetaSLambdab2JpsippiDetachedLine_Tuple/DecayTree");
  
  TFile* fileDE = TFile::Open((FriendPath+"Lambdab-R12S17b-435-436-NN.root"));		
  TTree* treeDE = (TTree*) fileDE->Get("NetTree");
  
  treeD->AddFriend(treeDE, "ExpertiseInfo");
  
  // loading reflection 1:
  TFile* fileB1 = TFile::Open((TreePath+"Lambdab2Jpsippi-MC11a-PsiKpi-523.root"));		
  treeB1 = (TTree*) fileB1->Get("Lambdab2Jpsippi_TupleMC/DecayTree");
  
  TFile* fileB1E = TFile::Open((FriendPath+"Lambdab2Jpsippi-MC11a-PsiKpi-523-NN.root"));		
  TTree* treeB1E = (TTree*) fileB1E->Get("NetTree");
  
  treeB1->AddFriend(treeB1E, "ExpertiseInfo");
  
  // loading reflection 2:
  TFile* fileB2 = TFile::Open((TreePath+"Lambdab2Jpsippi-MC11a-Bd2JpsiKstar-627.root"));		
  treeB2 = (TTree*) fileB2->Get("Lambdab2Jpsippi_TupleMC/DecayTree");
  
  TFile* fileB2E = TFile::Open((FriendPath+"Lambdab2Jpsippi-MC11a-Bd2JpsiKstar-627-NN.root"));		
  TTree* treeB2E = (TTree*) fileB2E->Get("NetTree");
  
  treeB2->AddFriend(treeB2E, "ExpertiseInfo");
  
  // loading reflection 3:
  TFile* fileB3 = TFile::Open((TreePath+"Lambdab2Jpsippi-MC11a-PsipK-516.root"));		
  treeB3 = (TTree*) fileB3->Get("Lambdab2Jpsippi_TupleMC/DecayTree");
  
  TFile* fileB3E = TFile::Open((FriendPath+"Lambdab2Jpsippi-MC11a-PsipK-516-NN.root"));		
  TTree* treeB3E = (TTree*) fileB3E->Get("NetTree");
  
  treeB3->AddFriend(treeB3E, "ExpertiseInfo");
  
}

// importing variable "name" from ((J/Psi) inclusive MC) (B) and 
// ((J/Psi) p pi MC) (S) and plotting original and logarithmic histograms
// background MC normalized to signal MC
// only use after LoadTrees()
void VarCompBS(TString name, int bins, double l1, double l2)
{
  int flag;
  TString nameAux(name);
  
  TString textS("Signal histogram;");
  TString textB("Background histogram;");
  
  TString last(";Entries");
  
  if(nameAux.Contains("pplus")) 
    {
      
      if(nameAux.Contains("sqrt"))
	{
	  nameAux = "p_pi_Invariant_Mass";
	} 
      
      textS += nameAux; 
      textS += " [MeV]";
      textB += nameAux; 
      textB += " [MeV]";
      
    }
  else
    {
      textS += nameAux;
      textB += nameAux;
    } 
  
  
  textS += last;
  textB += last;
  
  TH1D* hS;
  TH1D* hB;
	
  TLegend *leg = new TLegend(0.78,0.6,0.97,0.75);

  
  // normalization ratio for rescaling background to signal
  Double_t ratio = ((Double_t)(treeS->GetEntries())/treeB->GetEntries());
  
  const char* tS = textS;
  hS = new TH1D("hS",tS,bins,l1,l2);
  
  const char* tB = textB;
  hB = new TH1D("hB",tB,bins,l1,l2);
  
  TCanvas *cO = new TCanvas;
  
  treeS->Draw((name + " >> hS"));
  treeB->Draw((name + " >> hB"));
  
  leg->AddEntry(hS,"signal MC","l");
  leg->AddEntry(hB,"background MC","l");	
  
  gStyle->SetHistLineColor(kBlack); // black for background
  hB->UseCurrentStyle();      
  hB->Draw();
  hB->Scale(ratio);
  
  gStyle->SetHistLineColor(kRed); // red for signal
  hS->UseCurrentStyle();      
  hS->Draw("same");
  
  leg->Draw("same");
  
  TString s("");
  
  gSystem->ProcessEvents();
  
  TImage *imgO = TImage::Create();
  
  imgO->FromPad(cO);
  
  imgO->WriteImage((PlotPath+"Orig/VCBS_"+goodName(nameAux)+".png"));
  
  
  TCanvas *cL = new TCanvas;
  
  gStyle->SetHistLineColor(kBlack); // black for background
  hB->UseCurrentStyle();      
  hB->Draw();
  
  gStyle->SetHistLineColor(kRed); // red for signal
  hS->UseCurrentStyle();      
  hS->Draw("same");
  
  leg->Draw("same");
  
  cL->SetLogy();				
  
  gSystem->ProcessEvents();
  
  TImage *imgL = TImage::Create();
  
  imgL->FromPad(cL);
  
  imgL->WriteImage((PlotPath+"Log/VCBS_"+goodName(nameAux)+".png"));
  
  cout << "Input something!" << endl;

  cin >> flag;
  
  delete hS;
  delete hB;
  delete cO;
  delete cL;	
  delete imgO;
  delete imgL;
  
}

// creating combiend (Sig & Backgr) MC histogram plots (both Orig and Log) 
// of variable "name", with "cut", with "bins" bins, within limits "l1" and "l2"
// MC background normalized to MC signal
// use only after running LoadTrees()
void VarCutCompBS(TString name, TString cut, int bins, double l1, double l2)
{
  
  int flag;
  TString nameAux(name);
  
  TString textS("Signal-Background histogram at " + cut + ";");
  TString textB("Signal-Background histogram at " + cut + ";");
  
  TString last(";Entries");
  
  if(nameAux.Contains("pplus")) 
    {
      
      if(nameAux.Contains("sqrt"))
	{
	  nameAux = "p_pi_Invariant_Mass";
	} 
      
      textS += nameAux; 
      textS += " [MeV]";
      textB += nameAux; 
      textB += " [MeV]";
      
    }
  else
    {
      textS += nameAux;
      textB += nameAux;
    } 
  
  textS += last;
  textB += last;
  
  TH1D* hS;
  TH1D* hB;
  
  
  // normalization ratio for rescaling background to signal
  Double_t ratio = ((Double_t)(treeS->GetEntries())/treeB->GetEntries());
		
  
  
  const char* tS = textS;
  hS = new TH1D("hS",tS,bins,l1,l2);
  
  const char* tB = textB;
  hB = new TH1D("hB",tB,bins,l1,l2);
  
  
  TLegend *leg = new TLegend(0.78,0.6,0.97,0.75);
  
  leg->AddEntry(hS,"signal MC","l");
  leg->AddEntry(hB,"background MC","l");
  
  TCanvas *cO = new TCanvas;
  
  // cuts enter here	
  treeS->Draw((name + " >> hS"),cut); 
  treeB->Draw((name + " >> hB"),cut);
	
  gStyle->SetHistLineColor(2); // red for signal
  hS->UseCurrentStyle();      
  hS->Draw();
            
  gStyle->SetHistLineColor(1); // black for background
  hB->UseCurrentStyle();      
  hB->Draw("same");
  hB->Scale(ratio);
  
  leg->Draw("same");
  
  TString s("");
  
  gSystem->ProcessEvents();
  
  TImage *imgO = TImage::Create();

  imgO->FromPad(cO);
  
  imgO->WriteImage((PlotPath+"Orig/VCCBS_"+goodName(nameAux)+"_"+goodName(cut)+"_Orig.png"));
  
  
  
  TCanvas *cL = new TCanvas;
  
  gStyle->SetHistLineColor(2); // red for signal
  hS->UseCurrentStyle();      
  hS->Draw();
  
  gStyle->SetHistLineColor(1); // black for background
  hB->UseCurrentStyle();      
  hB->Draw("same");
  
  leg->Draw("same");
  
  cL->SetLogy();				
  
  gSystem->ProcessEvents();
  
  TImage *imgL = TImage::Create();
  
  imgL->FromPad(cL);
  
  imgL->WriteImage((PlotPath+"Log/VCCBS_"+goodName(nameAux)+"_"+goodName(cut)+"_Log.png"));
  
  cout << "Input something!" << endl;
  
  cin >> flag;
  
  delete hS;
  delete hB;
  delete cO;
  delete cL;	
  delete imgO;
  delete imgL;

}

// creating signal sig-efficiency profile plot -- use only after running LoadTrees()
// efficiency = (nr of candidates clasif as signal in bin) / (tot nr of candidates in bin)
// netOutput cut done within, name should only contain horizontal axis, "cut" is any other required cut !!!
// convenient for using after runing the NN expert on S, for testing purposes (against NN biases, overtraining etc)
void TestProfS(TString name, TString cut, int bins, double l1, double l2)
{
  
  int flag;
  TString nameAux(name);
  
  TString NOC1 = "(netOutput>0.0):"; // net output cuts
  TString NOC2 = "(netOutput>0.7):";
  
  TString textS("MC-Signal Profile;");
  
  TString last(";Signal Efficiency at:");
  
  if(nameAux.Contains("pplus")) 
    {
      
      if(nameAux.Contains("sqrt"))
	{
	  nameAux = "p_pi_Invariant_Mass";
	} 
      
      textS += nameAux; 
      textS += " [MeV]";
      
    }
  else
    {
      textS += nameAux;
    } 
  
  textS += last;
  
  TProfile* pS1; 
  TProfile* pS2;
		
  const char* tS = textS;
  pS1 = new TProfile("pS1",tS,bins,l1,l2,0.0,1.0);
  pS2 = new TProfile("pS2",tS,bins,l1,l2,0.0,1.0);
  
  TLegend *leg = new TLegend(0.78,0.51,0.97,0.66);
  
  leg->AddEntry(pS1,NOC1,"l");
  leg->AddEntry(pS2,NOC2,"l");
  
  TCanvas *cO = new TCanvas;
  
  
  // cuts enter here	
  treeS->Draw((NOC1 + name + " >> pS1"),cut);
  treeS->Draw((NOC2 + name + " >> pS2"),cut);
  
  gStyle->SetHistLineColor(kRed); // red for signal
  pS1->UseCurrentStyle();      
  pS1->Draw();	
	
  gStyle->SetHistLineColor(kViolet+2); // red for signal
  pS2->UseCurrentStyle();      
  pS2->Draw("same");	
  
  leg->Draw("same");
  
  TString s("");
  
  gSystem->ProcessEvents();
  
  TImage *imgO = TImage::Create();
  
  imgO->FromPad(cO);

  imgO->WriteImage((PlotPath+"Orig/TPS_"+goodName(nameAux)+"_"+goodName(cut)+".png"));
  
  
  cout << "Input something!" << endl;
  
  cin >> flag;
  
  delete pS1;
  delete pS2;
  delete cO;
  delete imgO;

}

// creating background sig-efficiency profile plot -- use only after running LoadTrees()
// efficiency = (nr of candidates acc as signal in bin) / (tot nr of candidates in bin)
// netOutput cut done within, name should only contain horizontal axis !!!
// convenient for using after running NN expert on B, for testing purposes (against NN biases, overtraining etc.)
void TestProfB(TString name, TString cut, int bins, double l1, double l2)
{

  int flag;
  TString nameAux(name);

  TString NOC1 = "(netOutput>0.0):"; // net output cuts
  TString NOC2 = "(netOutput>-0.7):";

  TString textB("MC-Background Profile;");
	
  TString last(";Signal Efficiency at:");
	
  if(nameAux.Contains("pplus")) 
    {
	
      if(nameAux.Contains("sqrt"))
	{
	  nameAux = "p_pi_Invariant_Mass";
	} 

      textB += nameAux; 
      textB += " [MeV]";
		
    }
  else
    {
      textB += nameAux;
    } 

  textB += last;
	
  TProfile* pB1; 
  TProfile* pB2;
		
  const char* tB = textB;
  pB1 = new TProfile("pB1",tB,bins,l1,l2,0.0,1.0);
  pB2 = new TProfile("pB2",tB,bins,l1,l2,0.0,1.0);

  TLegend *leg = new TLegend(0.10,0.75,0.29,0.90);
	
  leg->AddEntry(pB1,NOC1,"l");
  leg->AddEntry(pB2,NOC2,"l");
		
  TCanvas *cO = new TCanvas;
	
			
  // cuts enter here	
  treeB->Draw((NOC1 + name + " >> pB1"),cut);
  treeB->Draw((NOC2 + name + " >> pB2"),cut);
	
  gStyle->SetHistLineColor(kBlue); // black for background
  pB2->UseCurrentStyle();      
  pB2->Draw();	

  gStyle->SetHistLineColor(kBlack); // black for background
  pB1->UseCurrentStyle();      
  pB1->Draw("same");	
	
  leg->Draw("same");

  TString s("");

  gSystem->ProcessEvents();

  TImage *imgO = TImage::Create();

  imgO->FromPad(cO);

  imgO->WriteImage((PlotPath+"Orig/TPB_"+goodName(nameAux)+"_"+goodName(cut)+"_Orig.png"));
      
      
  cout << "Input something!" << endl;

  cin >> flag;

  delete pB1;
  delete pB2;
  delete cO;
  delete imgO;

}

// creating Data histogram plot of variable "name" at cut "cut"
// use only after running LoadTrees()
// convenient for using after running the NN Expert on D, for actual analysis purposes
void VarEvalD(TString name, TString cut, int bins, double l1, double l2)
{
  int flag;
  TString nameAux(name);

  TString textD("Data histogram at " + cut + ";");
	
  TString last(";Entries");
	
  if(nameAux.Contains("Mass")) {textD += nameAux; textD += " [MeV]";}
  else 
	
    if(nameAux.Contains("pplus") && nameAux.Contains("piminus")) 
      {
	
	nameAux = "p_pi_Invariant_Mass";

	textD += nameAux; 
	textD += " [MeV]";		
      }
    else 	if(nameAux.Contains("pplus") && nameAux.Contains("Psi")) 
      {
	nameAux = "p_psi_Invariant_Mass";

	textD += nameAux; 
	textD += " [MeV]";		
      }
    else	if(nameAux.Contains("Psi") && nameAux.Contains("piminus")) 
      {
	nameAux = "psi_pi_Invariant_Mass";

	textD += nameAux; 
	textD += " [MeV]";		
      }
    else if(nameAux.Contains("pplus") || nameAux.Contains("piminus") || nameAux.Contains("Psi"))
      {
	textD += nameAux;
	textD += " [MeV]";
      } 
    else
      {			
	textD += nameAux;
      }


  textD += last;
	
  TH1D* hD;		
	

  const char* tD = textD;
  hD = new TH1D("hD",tD,bins,l1,l2);

  TLegend *leg = new TLegend(0.78,0.6,0.97,0.75);
	
  leg->AddEntry(hD,"data","l"); 
		
  TCanvas *cO = new TCanvas;
		
  // cuts enter here	
  treeD->Draw((name + " >> hD"),cut); 
	
  gStyle->SetHistLineColor(kBlue); // blue for data
  hD->UseCurrentStyle();      
  hD->Draw();
	
  leg->Draw("same");
	

  TString s("");

  gSystem->ProcessEvents();

  TImage *imgO = TImage::Create();

  imgO->FromPad(cO);

  imgO->WriteImage((PlotPath+"Orig/VED_"+goodName(nameAux)+"_"+goodName(cut)+"_Orig.png"));
      

  TCanvas *cL = new TCanvas;

  gStyle->SetHistLineColor(kBlue); // blue for data
  hD->UseCurrentStyle();      
  hD->Draw();
            	
  leg->Draw("same");

  cL->SetLogy();				
      
  gSystem->ProcessEvents();

  TImage *imgL = TImage::Create();

  imgL->FromPad(cL);

  imgL->WriteImage((PlotPath+"Log/VED_"+goodName(nameAux)+"_"+goodName(cut)+"_Log.png"));
	      
  cout << "Input something!" << endl;

  cin >> flag;

  delete hD;
  delete cO;
  delete cL;	
  delete imgO;
  delete imgL;
}

// creating histogram  plots of variable "name", at NN output "cut", within limits "l1" and "l2"
// for all MC contributions (S, B, B1, B2, B3)
// use only after running LoadTrees()
// convenient to use after running the NN Expert on all reflection MC's
void HistAllMC(TString name, TString cut, int bins, double l1, double l2)
{
  int flag;
  TString nameAux(name);

  TH1D *hS,*hB,*hB1,*hB2,*hB3;		

  if(nameAux.Contains("sqrt"))
    {
      nameAux = "p_pi_Invariant_Mass";
    } 


  // ----- S -------------------------------------------------------------

  TString textS("MC Signal histogram at " + cut + ";");
	
  TString lastS(";Entries");
	
  if(nameAux.Contains("Mass")) {textS += nameAux; textS += " [MeV]";}
  else textS += nameAux;

  textS += lastS;

  const char* tS = textS;
					
  TCanvas *cS = new TCanvas;	

  hS = new TH1D("hS",tS,bins,l1,l2);	
					
  // cuts enter here	
  treeS->Draw((name + " >> hS"),cut); 

  gStyle->SetHistLineColor(kRed); // red for MC signal
  hS->UseCurrentStyle();      
  hS->Draw();
	
  gSystem->ProcessEvents();

  TImage *imgS = TImage::Create();

  imgS->FromPad(cS);

  imgS->WriteImage((PlotPath+"Orig/HAS_"+goodName(nameAux)+"_S_"+goodName(cut)+"_Orig.png"));

  cout << "Input something!" << endl;
  cin >> flag;



  // ------ B -------------------------------------------------------------

  TString textB("MC Background histogram at " + cut + ";");
	
  TString lastB(";Entries");
	
  if(nameAux.Contains("Mass")) {textB += nameAux; textB += " [MeV]";}
  else textB += nameAux;

  textB += lastB;

  const char* tB = textB;
      	      
  TCanvas *cB = new TCanvas;	

  hB = new TH1D("hB",tB,bins,l1,l2);	
					
  // cuts enter here	
  treeB->Draw((name + " >> hB"),cut); 

  gStyle->SetHistLineColor(kBlack); // black for MC background
  hB->UseCurrentStyle();      
  hB->Draw();
	
  gSystem->ProcessEvents();

  TImage *imgB = TImage::Create();

  imgB->FromPad(cB);

  imgB->WriteImage((PlotPath+"Orig/HAB_"+goodName(nameAux)+"_B_"+goodName(cut)+"_Orig.png"));

  cout << "Input something!" << endl;
  cin >> flag;

      
  // ----- B1 -------------------------------------------------------------

  TString textB1("MC Reflection 1 histogram at " + cut + ";");
	
  TString lastB1(";Entries");
	
  if(nameAux.Contains("Mass")) {textB1 += nameAux; textB1 += " [MeV]";}
  else textB1 += nameAux;

  textB1 += lastB1;

  const char* tB1 = textB1;
      	      
  TCanvas *cB1 = new TCanvas;	

  hB1 = new TH1D("hB1",tB1,bins,l1,l2);	
					
  // cuts enter here	
  treeB1->Draw((name + " >> hB1"),cut); 

  gStyle->SetHistLineColor(kYellow+3); // black for MC background
  hB1->UseCurrentStyle();      
  hB1->Draw();
	
  gSystem->ProcessEvents();

  TImage *imgB1 = TImage::Create();

  imgB1->FromPad(cB1);

  imgB1->WriteImage((PlotPath+"Orig/HAB1_"+goodName(nameAux)+"_B1_"+goodName(cut)+"_Orig.png"));

  cout << "Input something!" << endl;
  cin >> flag;
      
      
  // ------ B2 -------------------------------------------------------------      

  TString textB2("MC Reflection 2 histogram at " + cut + ";");
	
  TString lastB2(";Entries");
	
  if(nameAux.Contains("Mass")) {textB2 += nameAux; textB2 += " [MeV]";}
  else textB2 += nameAux;

  textB2 += lastB2;

  const char* tB2 = textB2;
      	      
  TCanvas *cB2 = new TCanvas;	

  hB2 = new TH1D("hB2",tB2,bins,l1,l2);	
					
  // cuts enter here	
  treeB2->Draw((name + " >> hB2"),cut); 

  gStyle->SetHistLineColor(kGreen+3); // black for MC background
  hB2->UseCurrentStyle();      
  hB2->Draw();
	
  gSystem->ProcessEvents();

  TImage *imgB2 = TImage::Create();

  imgB2->FromPad(cB2);

  imgB2->WriteImage((PlotPath+"Orig/HAB2_"+goodName(nameAux)+"_B2_"+goodName(cut)+"_Orig.png"));

  cout << "Input something!" << endl;
  cin >> flag;


  // ------ B3 -------------------------------------------------------------      

  TString textB3("MC Reflection 3 histogram at " + cut + ";");
	
  TString lastB3(";Entries");
	
  if(nameAux.Contains("Mass")) {textB3 += nameAux; textB3 += " [MeV]";}
  else textB3 += nameAux;

  textB3 += lastB3;

  const char* tB3 = textB3;
      	      
  TCanvas *cB3 = new TCanvas;	

  hB3 = new TH1D("hB3",tB3,bins,l1,l2);	
					
  // cuts enter here	
  treeB3->Draw((name + " >> hB3"),cut); 

  gStyle->SetHistLineColor(kCyan+3); // black for MC background
  hB3->UseCurrentStyle();      
  hB3->Draw();
	
  gSystem->ProcessEvents();

  TImage *imgB3 = TImage::Create();

  imgB3->FromPad(cB3);

  imgB3->WriteImage((PlotPath+"Orig/HAB3_"+goodName(nameAux)+"_B3_"+goodName(cut)+"_Orig.png"));

      
  cout << "Input something!" << endl;
  cin >> flag;


  delete hS;
  delete hB;
  delete hB1;
  delete hB2;
  delete hB3;
  delete cS;
  delete imgS;
  delete cB;
  delete imgB;
  delete cB1;
  delete imgB1;
  delete cB2;
  delete imgB2;
  delete cB3;
  delete imgB3;
}

// clean code in function below: !!! 

// computing the Punzi FoM from the Data invariant-mass histogram at a certain netOutput cut, 
// for lS1-lS2 as a signal region, lB1-lB2 as a background region
// lS1-lS2 should be included in lB1-lB2
// BNN extracted from the integral between lS1-lS2 of the polynomial function fitted to the region lS2-lB2 
// -- fitting currently done with 2'nd order polyn
// epsNN extracted from S ntuple as the ratio between number of candidates passing the NNcut 
// and total number of candidates between lB1-lB2 only use after running LoadTrees()
Double_t EvalPunzi(TString cut, int bins, Double_t lS1, Double_t lS2, Double_t lB1, Double_t lB2, Double_t alpha)
{

  int binS1, binS2;
	
  Double_t sqrtBNN; // average background
  Double_t epsNN; // efficiency of Neural Network
  Double_t nS; // nr of events in signal and background
	
  Double_t PFoM; // Punzi Figure of Merit

  TString name("FullFitMass");

  TString textD("Data histogram at " + cut + ";");
	
  TString last(";Entries");
	
  textD += name;

  textD += last;
	
  TH1D *hD,*hS,*hST;		

  const char* tD = textD;
  hD = new TH1D("hD",tD,bins,lB1,lB2);
  hS = new TH1D("hS",tD,bins,lB1,lB2);
  hST = new TH1D("hST",tD,bins,lB1,lB2);

  treeD->Draw((name + " >> hD"),cut); 
  treeS->Draw((name + " >> hS"),cut); 
  treeS->Draw((name + " >> hST")); 

  // enable for fit-visualization purposes:
  /*
    TCanvas *cD = new TCanvas;
    gStyle->SetHistLineColor(kBlue); // blue for data
    hD->UseCurrentStyle();      
    hD->Draw();
  */	

  // converting double invariant mass values into bin positions:

  binS1 = floor((lS1-lB1+1)/(lB2-lB1+1)*bins);
  binS2 = floor((lS2-lB1+1)/(lB2-lB1+1)*bins);
				
  nS = hST->Integral(binS1,binS2); // total number of candidates of MC S in signal region  
	
  epsNN = hS->Integral(binS1,binS2) / nS; // the integral counts the candidates of MC S passing the NN cut in signal region
	
  // change order of poly function to fit the background here:
  hD->Fit("pol2","I","",lS2,lB2);
	
  TF1 *lineFunc = hD->GetFunction("pol2");
	
  sqrtBNN = sqrt(lineFunc->Integral(lS1,lS2));
			
  delete hD;
  delete hS;
  delete hST;

  PFoM = (epsNN)/(alpha/2 + sqrtBNN);
	
  cout << epsNN << " " << sqrtBNN << " " << PFoM << endl;		
	
  return PFoM;

}

// creates Punzi FoM - netOutput graph plot, for 3 values of alpha, taken as input
// use only after running LoadTrees()
void PunziLoop(Double_t alpha, Double_t alpha1, Double_t alpha2)
{
  Int_t n = 39;

  Double_t start;
  Double_t nOC[n], nOC1[n], nOC2[n]; 		// netOutputCut vectors
  Double_t PFoM[n], PFoM1[n], PFoM2[n];	// Punzi FoM vectors
  TString cut;

  int flag;

  TCanvas *c1 = new TCanvas();
	
  TLegend* leg = new TLegend(0.18,0.6,0.37,0.75);
	
  start = 800.0;

  // first loop over netOutputCut
  for(Int_t i = 0; i < n; i++)
    {
      ostringstream cutOS(ostringstream::out);
      nOC[i]=(start+(Double_t)(i)*5)/1000.0;
      cutOS << nOC[i];
      cut = cutOS.str();
      cutOS.clear() ;

      PFoM[i] = EvalPunzi("netOutput>"+cut,300,5600,5640,5400,5800,alpha);		

      cout << nOC[i] << " " << PFoM[i] << endl;
    }

	
  TGraph *gr = new TGraph(n,nOC,PFoM);
  ostringstream alp(ostringstream::out);
  alp << alpha;
  leg->AddEntry(gr,TString("alpha="+alp.str()),"l"); 	

  start = 800.0;

  // second loop over netOutputCut
  for(Int_t i = 0; i < n; i++)
    {
      ostringstream cutOS(ostringstream::out);
      nOC1[i]=(start+(Double_t)(i)*5)/1000.0;
      cutOS << nOC1[i];
      cut = cutOS.str();
      cutOS.clear() ;

      PFoM1[i] = EvalPunzi("netOutput>"+cut,300,5600,5640,5400,5800,alpha1);		

      cout << nOC1[i] << " " << PFoM1[i] << endl;
    }
	
  TGraph *gr1 = new TGraph(n,nOC1,PFoM1);
  ostringstream alp1(ostringstream::out);
  alp1 << alpha1;
  leg->AddEntry(gr1,TString("alpha="+alp1.str()),"l"); 	

  start = 800.0;

  // third loop over netOutputCut
  for(Int_t i = 0; i < n; i++)
    {
      ostringstream cutOS(ostringstream::out);
      nOC2[i]=(start+(Double_t)(i)*5)/1000.0;
      cutOS << nOC2[i];
      cut = cutOS.str();
      cutOS.clear();

      PFoM2[i] = EvalPunzi("netOutput>"+cut,300,5600,5640,5400,5800,alpha2);		
		
      cout << nOC2[i] << " " << PFoM2[i] << endl;
    }
	
  TGraph *gr2 = new TGraph(n,nOC2,PFoM2);
  ostringstream alp2(ostringstream::out);
  alp2 << alpha2;
  leg->AddEntry(gr2,TString("alpha="+alp2.str()),"l");
		
  gStyle->SetHistLineColor(kBlue); // blue for data
  gr->UseCurrentStyle();
	
  gr->GetYaxis()->SetTitle("Punzi FoM");
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->GetXaxis()->SetTitle("netOutput");	
	      
  gr->Draw("AC*");

  gStyle->SetHistLineColor(kBlue+2); // blue for data
  gr1->UseCurrentStyle();      
	
  gr1->GetYaxis()->SetTitle("Punzi FoM");
  gr1->GetYaxis()->SetTitleOffset(1.4);
  gr1->GetXaxis()->SetTitle("netOutput");	
	
  gr1->Draw("same");
		 	
  gStyle->SetHistLineColor(kBlue+4); // blue for data
  gr2->UseCurrentStyle();      

  gr2->GetYaxis()->SetTitle("Punzi FoM");
  gr2->GetYaxis()->SetTitleOffset(1.4);
  gr2->GetXaxis()->SetTitle("netOutput");

  gr2->Draw("same");

  leg->Draw("same");
	

  gSystem->ProcessEvents();

  TImage *imgO = TImage::Create();

  imgO->FromPad(c1);

  imgO->WriteImage((PlotPath+"Orig/OptimPunziFoM.png"));
      
      
  cout << "Input something!" << endl;

  cin >> flag;
	
  delete gr;
  delete gr1;
  delete gr2;
  delete c1;
  delete imgO;

}

// creates 2 ppi-invariant mass plots, containing histograms at several netOutput cuts
// one contains data inside the Lambda_b peak, one data outside the Lambda_b peak
// only use after calling LoadTrees()
void Lambda0Check(int bins, double l1, double l2)
{
	
  int flag;

  TString netCut1("netOutput > 0.0");	
  TString netCut2("netOutput > 0.7");	
  TString netCut3("netOutput > 0.9");

		
  // p-pi invariant mass:	
  TString name("sqrt((pplus_PE+piminus_PE)**2-(pplus_PX+piminus_PX)**2-(pplus_PY+piminus_PY)**2-(pplus_PZ+piminus_PZ)**2)");


  // cutting for invariant mass region inside the peak
  TString massCutLbI(" && (FullFitMass>5600 && FullFitMass<5640)");

  // complete cuts inside
  TString cut1I("");
  TString cut2I("");
  TString cut3I("");
	
  cut1I += netCut1;
  cut2I += netCut2;
  cut3I += netCut3;
	
  cut1I += massCutLbI;
  cut2I += massCutLbI;
  cut3I += massCutLbI;

	
  // cutting for invariant mass region outside the peak
  TString massCutLbO(" && (FullFitMass<5600 || FullFitMass>5640)");

  // complete cuts outside
  TString cut1O("");
  TString cut2O("");
  TString cut3O("");
	
  cut1O += netCut1;
  cut2O += netCut2;
  cut3O += netCut3;
	
  cut1O += massCutLbO;
  cut2O += massCutLbO;
  cut3O += massCutLbO;


  TString textDI("Data histogram inside peak at: ;p_pi_Invariant_Mass [MeV] ;Entries");

  TString textDO("Data histogram outside peak at: ;p-pi_Invariant_Mass [MeV] ;Entries");

  TH1D *hD1I, *hD2I, *hD3I, *hD1O, *hD2O, *hD3O;		

  const char* tDI = textDI;
  hD1I = new TH1D("hD1I",tDI,bins,l1,l2);
  hD2I = new TH1D("hD2I",tDI,bins,l1,l2);
  hD3I = new TH1D("hD3I",tDI,bins,l1,l2);

  const char* tDO = textDO;
  hD1O = new TH1D("hD1O",tDO,bins,l1,l2);
  hD2O = new TH1D("hD2O",tDO,bins,l1,l2);
  hD3O = new TH1D("hD3O",tDO,bins,l1,l2);


  // canvas and image inside Lambda_b peak
  TCanvas *cI = new TCanvas;
		
  treeD->Draw((name + " >> hD1I"),cut1I); 
  treeD->Draw((name + " >> hD2I"),cut2I); 
  treeD->Draw((name + " >> hD3I"),cut3I); 
	
  gStyle->SetHistLineColor(kViolet); // blue for data
  hD1I->UseCurrentStyle();      
  hD1I->Draw();

  gStyle->SetHistLineColor(kGreen); // blue for data
  hD2I->UseCurrentStyle();      
  hD2I->Draw("same");

  gStyle->SetHistLineColor(kBlue); // blue for data
  hD3I->UseCurrentStyle();      
  hD3I->Draw("same");
	
  TLegend *legI = new TLegend(0.78,0.6,0.97,0.75);
	
  legI->AddEntry(hD1I,netCut1,"l"); 
  legI->AddEntry(hD2I,netCut2,"l"); 
  legI->AddEntry(hD3I,netCut3,"l"); 	
	
  legI->Draw("same");
	
  gSystem->ProcessEvents();

  TImage *imgI = TImage::Create();

  imgI->FromPad(cI);

  imgI->WriteImage((PlotPath+"Orig/LC_"+"ppiInsidePeak.png"));

  cout << "Input Something" << endl;
  cin >> flag;
	
	
  // canvas and image outside Lambda_b peak	
  TCanvas *cO = new TCanvas;

  cout << cut1O << endl;
  cout << cut2O << endl;
  cout << cut3O << endl;
		
  treeD->Draw((name + " >> hD1O"),cut1O); 
  treeD->Draw((name + " >> hD2O"),cut2O); 
  treeD->Draw((name + " >> hD3O"),cut3O); 
	
  gStyle->SetHistLineColor(kViolet); // blue for data
  hD1O->UseCurrentStyle();      
  hD1O->Draw();

  gStyle->SetHistLineColor(kGreen); // blue for data
  hD2O->UseCurrentStyle();      
  hD2O->Draw("same");

  gStyle->SetHistLineColor(kBlue); // blue for data
  hD3O->UseCurrentStyle();      
  hD3O->Draw("same");
	
  TLegend *legO = new TLegend(0.78,0.6,0.97,0.75);
	
  legO->AddEntry(hD1O,netCut1,"l"); 
  legO->AddEntry(hD2O,netCut2,"l"); 
  legO->AddEntry(hD3O,netCut3,"l"); 	
	
  legO->Draw("same");
	
  gSystem->ProcessEvents();

  TImage *imgO = TImage::Create();

  imgO->FromPad(cO);

  imgO->WriteImage((PlotPath+"Orig/LC_"+"ppiOutsidePeak.png"));

  cout << "Input Something" << endl;
  cin >> flag;

  delete cI;
  delete cO;
  delete imgI;
  delete imgO;

}

// plots all 3 Dalitz plots
// only use after calling LoadTrees()
void Dalitz()
{
  int flag;
		
  TString sPsiPi("(Psi_PE+piminus_PE)**2-(Psi_PX+piminus_PX)**2-(Psi_PY+piminus_PY)**2-(Psi_PZ+piminus_PZ)**2");
  TString sPPi("(piminus_PE+pplus_PE)**2-(piminus_PX+pplus_PX)**2-(piminus_PY+pplus_PY)**2-(piminus_PZ+pplus_PZ)**2");
  //	string sPsiP("(Psi_PE+pplus_PE)**2-(Psi_PX+pplus_PX)**2-(Psi_PY+pplus_PY)**2-(Psi_PZ+pplus_PZ)**2");

  // Dalitz plot psi-pi:p-pi
  TCanvas *c1 = new TCanvas;
  TH2D *h1 = new TH2D("h1","Dalitz plot;InvMass(p-pi)^2 [MeV^2];InvMass(psi-pi)^2 [MeV^2]",
                      300,1000*1000,2600*2600,300,3200*3200,5000*5000);

  treeD->Draw((sPsiPi+":"+sPPi+" >> h1"),"netOutput > 0.96 && FullFitMass > 5600.0 && FullFitMass < 5640.0"); 

  h1->Draw("scat");

  TImage *img1 = TImage::Create();

  img1->FromPad(c1);

  img1->WriteImage((PlotPath+"Orig/"+"Dalitz_PsiPi_PPi.png"));

  cout << "Input Something" << endl;
  cin >> flag;
	
  delete h1;
  delete c1;
  delete img1;
}

// creates all relevant analysis plots produced and used during July and August 2012 
// please be patient between the steps
void AnalysisPlots()
{
  LoadTrees();

  VarCompBS("pplus_PZ", 300, 0.0, 200000);
	
  TestProfS(TString("sqrt((pplus_PE+piminus_PE)**2-(pplus_PX+piminus_PX)**2-")+
            TString("(pplus_PY+piminus_PY)**2-(pplus_PZ+piminus_PZ)**2)"),"B_BKGCAT==0",50,800.0,3500.0);
  TestProfB("FullFitMass","B_BKGCAT!=30 && B_BKGCAT!=40 && B_BKGCAT!=60",50,4800.0,6200.0);

  VarEvalD("FullFitMass","netOutput>0.9",300,5400, 5800);
  VarEvalD("netOutput","",300,-1.5, 1.5);
		
  PunziLoop(6,10,20);

  VarEvalD("FullFitMass","netOutput>0.96",300,5400, 5800);
		
  Lambda0Check(300,1030,1200);
	
  HistAllMC("FullFitMass", "netOutput > 0.96", 300, 5200, 6000);
  HistAllMC("B_SubpK_M[0]", "netOutput > 0.96", 300, 5200, 6000);
  HistAllMC("B_SubKpi_M[0]", "netOutput > 0.96", 300, 5200, 6000);

  VarEvalD(TString("sqrt((pplus_PE+piminus_PE)**2-(pplus_PX+piminus_PX)**2-")+
           TString("(pplus_PY+piminus_PY)**2-(pplus_PZ+piminus_PZ)**2)"),"netOutput>0.96",300,1000.0, 2600.0);

  VarEvalD(TString("sqrt((pplus_PE+piminus_PE)**2-(pplus_PX+piminus_PX)**2-")+
           TString("(pplus_PY+piminus_PY)**2-(pplus_PZ+piminus_PZ)**2)"),
           "netOutput>0.96 && FullFitMass > 5600.0 && FullFitMass < 5640.0",300,1000.0, 2600.0);
  VarEvalD(TString("sqrt((Psi_PE+piminus_PE)**2-(Psi_PX+piminus_PX)**2-")+
           TString("(Psi_PY+piminus_PY)**2-(Psi_PZ+piminus_PZ)**2)"),
           "netOutput>0.96 && FullFitMass > 5600.0 && FullFitMass < 5640.0",300,3400.0, 4900.0);
  VarEvalD(TString("sqrt((pplus_PE+Psi_PE)**2-(pplus_PX+Psi_PX)**2-")+
           TString("(pplus_PY+Psi_PY)**2-(pplus_PZ+Psi_PZ)**2)"),
           "netOutput>0.96 && FullFitMass > 5600.0 && FullFitMass < 5640.0",300,4000.0, 5400.0);

  HistAllMC(TString("sqrt((pplus_PE+piminus_PE)**2-(pplus_PX+piminus_PX)**2-")+
            TString("(pplus_PY+piminus_PY)**2-(pplus_PZ+piminus_PZ)**2)"), "netOutput > 0.96", 300, 800.0, 3500.0);

  Dalitz();
}
