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
  
  int status = -999;
  int covQual = -999;
  double edm = -999;
  double globalCorr_accY = -999;
  double globalCorr_accZ = -999;
  double globalCorr_accVelo = -999;
  
  double param_Val = -999;
  double param_Err = -999;
  double param_Pull = -999;
  
  chain->SetBranchAddress("Minuit_status", &status);
  chain->SetBranchAddress("Minuit_covQual", &covQual);
  chain->SetBranchAddress("Minuit_edm", &edm);
  chain->SetBranchAddress("Minuit_globalCorr_accY", &globalCorr_accY);
  chain->SetBranchAddress("Minuit_globalCorr_accZ", &globalCorr_accZ);
  chain->SetBranchAddress("Minuit_globalCorr_accVelo", &globalCorr_accVelo);
  
  chain->SetBranchAddress(param+"_Val", &param_Val);
  chain->SetBranchAddress(param+"_Err", &param_Err);
  chain->SetBranchAddress(param+"_Pull", &param_Pull);
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////
  
  RooRealVar *Val = new RooRealVar("Val","Value",0.);
  RooRealVar *Err = new RooRealVar("Err","Uncertainty",0.);
  RooRealVar *Pull = new RooRealVar("Pull","Pull",0.);
  
  RooArgSet *Obs = new RooArgSet(*Val,*Err,*Pull);
  RooDataSet *data = new RooDataSet("data","Unbinned dataset",*Obs);
  
  // ***** Fill DataSet ***** //
  //////////////////////////////
  
  int not_converged = 0;
  int not_conv_10 = 0;
  int not_conv_100 = 0;
  int not_conv_1000 = 0;
  int not_posdef_edm = 0;
  int not_posdef = 0;
  int too_corr = 0;
  
  for(Long64_t i=0; i<nEntries_All; i++){
    chain->GetEntry(i);
    
    if(status==0 && covQual==3){
      Val->setVal(param_Val);
      Err->setVal(param_Err);
      Pull->setVal(param_Pull);
      data->add(*Obs);
      nEntries_Good++;
    }
    if(edm>0.0001 && covQual==3) not_converged++;
    if(edm>0.001 && covQual==3) not_conv_10++;
    if(edm>0.01 && covQual==3) not_conv_100++;
    if(edm>0.1 && covQual==3) not_conv_1000++;
    if(covQual==2 && edm<0.001) not_posdef_edm++;
    if(covQual==2) not_posdef++;
    if(globalCorr_accY>0.99) too_corr++;
    //if(covQual==2 && globalCorr_accY<=0.99) std::cout << globalCorr_accY << std::endl;
  }
  

  TString track = (tracktype==3 ? "_LL" : "_DD");
  double Results_Val[] = {-999,-999,-999,-999};
  FitPlotParam(Val,data,param+"_Val"+track+".pdf",Results_Val,lumi);
  
  double Results_Err[] = {-999,-999,-999,-999};
  FitPlotParam(Err,data,param+"_Err"+track+".pdf",Results_Err,lumi);
  
  double Results_Pull[] = {-999,-999,-999,-999};
  FitPlotParam(Pull,data,param+"_Pull"+track+".pdf",Results_Pull,lumi);
  double sigMean = Results_Pull[0]/Results_Pull[1];
  double sigWidth = (Results_Pull[2]-1)/Results_Pull[3];

  // ***** Results ***** //
  /////////////////////////
  
  std::cout << "*** STATUS ***" << std::endl;
  std::cout << "Good Fits: " << nEntries_Good << std::endl;
  std::cout << "Not Converged: " << not_converged << " " << not_conv_10 << " " << not_conv_100 << " " << not_conv_1000 << std::endl;
  std::cout << "Forced PosDef: " << not_posdef << " " << not_posdef_edm << std::endl;
  std::cout << "Parameters too Correlated: " << too_corr << std::endl;
  std::cout << std::endl;
  std::cout << "*** RESULTS ***" << std::endl; 
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
  if(convSave.find("Pull")!=string::npos) fitresult = (RooFitResult *)gauss->fitTo(*Data,Range("PullRange"),Save());
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
  double min = Results[0]-3*Results[2];
  double max = Results[0]+3*Results[2];
  int nbins = 50;
  TString xtitle = "Parameter";
  TString ytitle = "Events";
  
  if(convSave.find("Minuit_tau_Bs")!=string::npos){
    if(convSave.find("Val")!=string::npos && lumi=="1"){
      nbins = 60;
      min = 1.;
      max = 2.2;
      xtitle = "#tau_{B_{s}}^{eff} (ps)";
      ytitle = "Events/(0.02 ps)";
    }
    else if(convSave.find("Val")!=string::npos && lumi=="3"){
      nbins = 60;
      min = 1.3;
      max = 1.9;
      xtitle = "#tau_{B_{s}}^{eff} (ps)";
      ytitle = "Events/(0.01 ps)";
    }
    else if(convSave.find("Err_LL")!=string::npos && lumi=="1"){
      nbins = 70;
      min = 0.11;
      max = 0.25;
      xtitle = "#sigma(#tau_{B_{s}}^{eff}) (ps)";
      ytitle = "Events/(0.002 ps)";
    }
    else if(convSave.find("Err_LL")!=string::npos && lumi=="3"){
      nbins = 70;
      min = 0.06;
      max = 0.13;
      xtitle = "#sigma(#tau_{B_{s}}^{eff}) (ps)";
      ytitle = "Events/(0.001 ps)";
    }
    else if(convSave.find("Err_DD")!=string::npos && lumi=="1"){
      nbins = 50;
      min = 0.09;
      max = 0.19;
      xtitle = "#sigma(#tau_{B_{s}}^{eff}) (ps)";
      ytitle = "Events/(0.002 ps)";
    }
    else if(convSave.find("Err_DD")!=string::npos && lumi=="3"){
      nbins = 80;
      min = 0.06;
      max = 0.10;
      xtitle = "#sigma(#tau_{B_{s}}^{eff}) (ps)";
      ytitle = "Events/(0.0005 ps)";
    }
    else if(convSave.find("Pull")!=string::npos){
      nbins = 70;
      min = -3.5;
      max = 3.5;
      xtitle = "Pull #tau_{B_{s}}^{eff}";
      ytitle = "Events/(0.1)";
    }
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
  size_t isLL=convSave.find("LL");
  size_t isDD=convSave.find("DD");
  
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
  
  // *** LHCb Tag ***
	TPaveText *lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");
  //if(logy==1) lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");
  //else if(logy==0) lhcbTag = new TPaveText(0.65,0.35,0.89,0.54,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(convSave.find("1fb")!=string::npos) lhcbTag->AddText("#splitline{Toy Simulation}{#splitline{#scale[0.7]{LHCb 2011}}{#scale[0.7]{"+track+"}}}");
  else lhcbTag->AddText("#splitline{Toy Simulation}{#splitline{#scale[0.7]{LHCb 2011+2012}}{#scale[0.7]{"+track+"}}}");
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
