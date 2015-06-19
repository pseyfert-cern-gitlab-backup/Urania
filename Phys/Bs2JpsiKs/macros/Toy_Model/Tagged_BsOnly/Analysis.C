//////////////////////////////////////
// ********** Simulation ********** //
//////////////////////////////////////

// This is the RooFit Macro written by Kristof De Bruyn for "Implications of Penguin Topologies" Paper

///////////////////////////////////////////////////
// ********** Loading usefull classes ********** //
///////////////////////////////////////////////////

#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TMath.h"
#include "TPaveText.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, int logy);
void FitPlotParam(RooRealVar *Obs,RooDataSet *Data, TString saveString,double *Results,TString lumi);


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void toyFit(int tracktype,TString lumi, TString param){

  // ***** Load NTuples ***** //
  //////////////////////////////
  
  TChain* chain = new TChain("chain");
  if(tracktype==3) chain->Add("Toy_Model_Results_LL_"+lumi+"fb.root/Minuit_Results");
  else if(tracktype==5) chain->Add("Toy_Model_Results_DD_"+lumi+"fb.root/Minuit_Results");
  
  int nEntries_All = chain->GetEntries();
  int nEntries_Good = 0;
  
  if(nEntries_All==0) return;
  
  // ***** Define NTuple Observables ***** //
  ///////////////////////////////////////////
  
  int covQual = -999;
  
  double param_Val = -999;
  double param_Err = -999;
  double param_Pull = -999;
  
  double ADG_Err = -999;
  double Adir_Err = -999;
  double Amix_Err = -999;

  chain->SetBranchAddress("Minuit_covQual", &covQual);
  
  chain->SetBranchAddress("Minuit_"+param+"_Val", &param_Val);
  //chain->SetBranchAddress("Minuit_"+param+"_Err", &param_Err);
  chain->SetBranchAddress("Minuit_"+param+"_Pull", &param_Pull);
  
  chain->SetBranchAddress("Minuit_ADG_Bs_Err", &ADG_Err);
  chain->SetBranchAddress("Minuit_Adir_Bs_Err", &Adir_Err);
  chain->SetBranchAddress("Minuit_Amix_Bs_Err", &Amix_Err);
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////
  
  RooRealVar *Val = new RooRealVar("Val","Value",0.);
  RooRealVar *Err = new RooRealVar("Err","Uncertainty",0.);
  RooRealVar *Pull = new RooRealVar("Pull","Pull",0.);
  
  RooArgSet *Obs = new RooArgSet(*Val,*Err,*Pull);
  RooDataSet *data = new RooDataSet("data","Unbinned dataset",*Obs);
  
  // ***** Fill DataSet ***** //
  //////////////////////////////
  
  int bad_Err = 0;
  
  for(Long64_t i=0; i<nEntries_All; i++){
    chain->GetEntry(i);
    
    if(param=="ADG_Bs") param_Err = ADG_Err;
    else if(param=="Adir_Bs") param_Err = Adir_Err;
    else if(param=="Amix_Bs") param_Err = Amix_Err; 
    
    if(covQual==3 && ADG_Err>0.2 && Adir_Err>0.2 && Amix_Err>0.2){
      Val->setVal(param_Val);
      Err->setVal(param_Err);
      Pull->setVal(param_Pull);
      data->add(*Obs);
      nEntries_Good++;
    }
    else if(covQual==3) bad_Err++;
  }
  

  TString track = (tracktype==3 ? "_LL" : "_DD");
  double Results_Val[] = {-999,-999,-999,-999};
  FitPlotParam(Val,data,"SepBsOnly_"+param+"_Val"+track+".pdf",Results_Val,lumi);
  
  double Results_Err[] = {-999,-999,-999,-999};
  FitPlotParam(Err,data,"SepBsOnly_"+param+"_Err"+track+".pdf",Results_Err,lumi);
  
  double Results_Pull[] = {-999,-999,-999,-999};
  FitPlotParam(Pull,data,"SepBsOnly_"+param+"_Pull"+track+".pdf",Results_Pull,lumi);
  double sigMean = Results_Pull[0]/Results_Pull[1];
  double sigWidth = (Results_Pull[2]-1)/Results_Pull[3];

  // ***** Results ***** //
  /////////////////////////
  
  std::cout << std::endl;
  std::cout << "*** RESULTS ***" << std::endl; 
  std::cout << "Due to unrealistic error estimate: " << bad_Err << "/" << nEntries_All << std::endl;
  std::cout << param << " & Val & " << nEntries_Good << "/" << nEntries_All << " & ";
  std::cout << Results_Val[0] << " ! " << Results_Val[1] << " & ";
  std::cout << Results_Val[2] << " ! " << Results_Val[3] << std::endl;
  std::cout << param << " & Err & " << nEntries_Good << "/" << nEntries_All << " & ";
  std::cout << Results_Err[0] << " ! " << Results_Err[1] << " & ";
  std::cout << Results_Err[2] << " ! " << Results_Err[3] << std::endl;
  std::cout << param << " & Pull & " << nEntries_Good << "/" << nEntries_All << " & ";
  std::cout << Results_Pull[0] << " ! " << Results_Pull[1] << " & $" << sigMean << "sigma$ & ";
  std::cout << Results_Pull[2] << " ! " << Results_Pull[3] << " & $" << sigWidth << "sigma$" << std::endl;
  printf(param+" & %.3f ! %.3f & $%.1fsigma$ & %.3f ! %.3f & $%.1fsigma$ \n",Results_Pull[0],Results_Pull[1],sigMean,Results_Pull[2],Results_Pull[3],sigWidth);
  
}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitPlotParam(RooRealVar *Obs,RooDataSet *Data, TString saveString,double *Results,TString lumi){

  string convSave (saveString);

  // ***** Fit Model ***** //
  ///////////////////////////
  
  double estMean = Data->mean(*Obs);
  double estSigma = Data->sigma(*Obs);
  
  if(convSave.find("Pull")!=string::npos && fabs(estMean)>5){
    estMean = 0.;
    estSigma = 3.;
  }
  RooRealVar *mean = new RooRealVar("mean","Mean of Fit",estMean,estMean-3*estSigma,estMean+3*estSigma);
  RooRealVar *sigma = new RooRealVar("sigma","Sigma of Fit",estSigma,0.,3*estSigma);
  
  RooGaussian *gauss = new RooGaussian("gauss","Gaussian for Fit",*Obs,*mean,*sigma);
  
  RooFitResult *fitresult = 0;
  Obs->setRange("PullRange",-5.,5.);
  Obs->setRange("FitRange",estMean-5*estSigma,estMean+5*estSigma);
  Obs->setRange("ADGRange",0.5,1.5);
  if(convSave.find("Pull")!=string::npos) fitresult = (RooFitResult *)gauss->fitTo(*Data,Range("PullRange"),Save());
  else if(convSave.find("ADG_Bs_Err")!=string::npos) fitresult = (RooFitResult *)gauss->fitTo(*Data,Range("ADGRange"),Save());
  else fitresult = (RooFitResult *)gauss->fitTo(*Data,Range("FitRange"),Save());
  
  RooRealVar* temp = 0;
  temp = (RooRealVar*)fitresult->floatParsFinal().find("mean");
  if(temp){
    Results[0] = temp->getVal();
    Results[1] = temp->getError();
    delete temp;
  }
  temp = (RooRealVar*)fitresult->floatParsFinal().find("sigma");
  if(temp){
    Results[2] = temp->getVal();
    Results[3] = temp->getError();
    delete temp;
  }
  
  // ***** Plot ***** //
  //////////////////////
  
  // *** Settings ***
  double min = Results[0]-5*Results[2];
  double max = Results[0]+5*Results[2];
  int nbins = 50;
  TString xtitle = "Parameter";
  TString ytitle = "Events";
  
  if(convSave.find("Val")!=string::npos){
    nbins = 60;
    min = -3.;
    max = 3.;
    ytitle = "Events/(0.1)";
  }
  else if(convSave.find("Err_LL")!=string::npos){
    nbins = 60;
    min = 0.4;
    max = 1.0;
    ytitle = "Events/(0.01)";
  }
  else if(convSave.find("Err_DD")!=string::npos){
    nbins = 60;
    min = 0.5;
    max = 1.1;
    ytitle = "Events/(0.01)";
  }
  else if(convSave.find("Pull")!=string::npos){
    nbins = 70;
    min = -3.5;
    max = 3.5;
    ytitle = "Events/(0.1)";
  }
  if(convSave.find("ADG")!=string::npos){
    if(convSave.find("Pull")!=string::npos) xtitle = "Pull A_{#Delta#Gamma}";
    else if(convSave.find("Val")!=string::npos) xtitle = "A_{#Delta#Gamma}";
    else if(convSave.find("Err_LL")!=string::npos){
      nbins = 90;
      min = 0.5;
      max = 1.4;
      xtitle = "#sigma(A_{#Delta#Gamma})";
      ytitle = "Events/(0.01)";
    }
    else if(convSave.find("Err_DD")!=string::npos){
      nbins = 90;
      min = 0.4;
      max = 1.3;
      xtitle = "#sigma(A_{#Delta#Gamma})";
      ytitle = "Events/(0.01)";
    }
  }
  else if(convSave.find("Adir")!=string::npos){
    if(convSave.find("Pull")!=string::npos) xtitle = "Pull A_{dir}^{CP}";
    if(convSave.find("Val")!=string::npos) xtitle = "A_{dir}^{CP}";
    if(convSave.find("Err")!=string::npos) xtitle = "#sigma(A_{dir}^{CP})";
  }
  else if(convSave.find("Amix")!=string::npos){
    if(convSave.find("Pull")!=string::npos) xtitle = "Pull A_{mix}^{CP}";
    if(convSave.find("Val")!=string::npos) xtitle = "A_{mix}^{CP}";
    if(convSave.find("Err")!=string::npos) xtitle = "#sigma(A_{mix}^{CP})";
  }
  
  
  // *** Frame ***
  RooPlot* ObsFrame = Obs->frame(Range(min,max),Bins(nbins));

  // Titles
  ObsFrame->SetXTitle(xtitle);
  ObsFrame->SetYTitle(ytitle);

  // Cosmetics
  ObsFrame->SetTitleOffset(1.2,"y");
  ObsFrame->SetTitleSize(0.07,"x");
  ObsFrame->SetTitleSize(0.07,"y");
  ObsFrame->SetTitleFont(132,"y");
  ObsFrame->SetTitleFont(132,"x");
  ObsFrame->SetLabelSize(0.05,"y");
  ObsFrame->SetLabelSize(0.05,"x");
  ObsFrame->SetLabelFont(132,"x");
  ObsFrame->SetLabelFont(132,"y");

  Data->plotOn(ObsFrame,MarkerStyle(8),MarkerSize(0.8));
  gauss->plotOn(ObsFrame,LineWidth(2),LineColor(4));
  
  ObsFrame->SetMinimum(0);
  ObsFrame->SetMaximum(60);
  
  // *** Pull of Fit ***
  TString directory = "";
  if(convSave.find("LL")!=string::npos) directory = "Parameter_Fits_LL_"+lumi+"fb/";
  if(convSave.find("DD")!=string::npos) directory = "Parameter_Fits_DD_"+lumi+"fb/";
  PullPlot(directory+saveString,ObsFrame,0);
}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, int logy){
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
  pullframe->SetTitleOffset(0.8,"x");
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
	TPaveText *lhcbTag = 0;
  if(convSave.find("ADG_Bs_Val")!=string::npos) lhcbTag = new TPaveText(0.25,0.70,0.49,0.89,"NDC");
  else lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  
  TString track("");
  if(convSave.find("LL")!=string::npos) track = "Long K_{S}^{0}";
  else if(convSave.find("DD")!=string::npos) track = "Downstream K_{S}^{0}";
  lhcbTag->AddText("#splitline{Toy Simulation}{#splitline{#scale[0.7]{LHCb 2011+2012}}{#scale[0.7]{"+track+"}}}");
  lhcbTag->Draw();
  
  
  
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
