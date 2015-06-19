/////////////////////////////////////////////////
// ********** Toy Monte Carlo Model ********** //
/////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Check for any biases in the fit method


//////////////////////////////////////////////////
// ********** Loading useful classes ********** //
//////////////////////////////////////////////////

#include "ToyModel.h"

ClassImp(ToyModel); 



////////////////////////////////////////////////////////////
// ********** Defining Constants and Variables ********** //
////////////////////////////////////////////////////////////

void ToyModel::DefiningConstantsAndVariables(int tracktype, double theLumi){
  
  std::cout << "*** Defining Constants and Variables ***" << std::endl;
  
  // ********** General ********** //
  ///////////////////////////////////  

  TrackType = tracktype;
  LumiGen = (theLumi==0 ? 1.018 : theLumi);

  // ********** Detector Observables ********** //
  ////////////////////////////////////////////////

  // *** B0 Mass ***
  Bmass = new RooRealVar("Bmass","Reconstructed B0 mass",5180.,5520.,"MeV/c^{2}");

  // *** Bs Lifetime ***
  Btime = new RooRealVar("Btime","Reconstructed Bs lifetime",0.2,15.,"ps");

 
  // ********** Used Constants: B0 Mass ********** //
  ///////////////////////////////////////////////////
  
  input_Bmass_Bd = 5279.58;
  Bmass_Bd = new RooRealVar("Bmass_Bd","Bd Mass",input_Bmass_Bd, input_Bmass_Bd-10., input_Bmass_Bd+10.,"MeV/c^{2}");
  Bmass_Diff = new RooRealVar("Bmass_Diff","Bs - Bd mass difference", 87.52);
  Bmass_Bs = new RooAddition("Bmass_Bs","Bmass_Bs", RooArgSet(*Bmass_Bd,*Bmass_Diff));

  // *** Signal ***
  input_sigma_I = (tracktype==3 ? 5.3112 : 7.3136);
  Bmass_sigma_I = new RooRealVar("Bmass_sigma_I","Width of the Crystal Ball",input_sigma_I,1.,10.,"MeV/c^{2}");
  input_sigma_II = (tracktype==3 ? 8.6452 : 13.767);
  Bmass_sigma_II = new RooRealVar("Bmass_sigma_II","Width of the Crystal Ball",input_sigma_II,1.,25.,"MeV/c^{2}");
  input_fraction = (tracktype==3 ? 0.49925 : 0.76959);
  Bmass_fraction = new RooRealVar("Bmass_fraction","Fraction of Crystal Ball I",input_fraction,0.,1.);
  
  Bmass_apar_I = new RooRealVar("Bmass_apar_I","A parameter of Crystal Ball",(tracktype==3 ? 1.21 : 2.478));
  Bmass_npar_I = new RooRealVar("Bmass_npar_I","N parameter of Crystal Ball",(tracktype==3 ? 5.28 : 1.81));
  Bmass_apar_II = new RooRealVar("Bmass_apar_II","A parameter of Crystal Ball",(tracktype==3 ? -1.517 : -2.54));
  Bmass_npar_II = new RooRealVar("Bmass_npar_II","N parameter of Crystal Ball",(tracktype==3 ? 145.501 : 7.5));

  // *** Background ***
  input_lambda = (tracktype==3 ? -0.0021401 : -0.0033263);
  Bmass_lambda = new RooRealVar("Bmass_lambda","Decay constant of the exponential",input_lambda,-0.1,0.1,"MeV/c^{2}");
  
  
  // ********** Used Constants: Time ********** //
  ////////////////////////////////////////////////

  // *** Lifetime ***
  tau_Bd = new RooRealVar("tau_Bd","Average lifetime for Bd",1.519,"ps");
  input_tau_Bs = 1.619;
  tau_Bs = new RooRealVar("tau_Bs","Average lifetime for Bs",input_tau_Bs,0.,3.,"ps");
  
  // *** Resolution ***
  resMean = new RooRealVar("resMean","Resolution - mean",0.,"ps");
  coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",(tracktype==3 ? 0.0339915 : 0.0397601),"ps");
  midSigma = new RooRealVar("midSigma","Resolution - Middle Width",(tracktype==3 ? 0.0648249 : 0.0720899),"ps");
  tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",(tracktype==3 ? 0.37931 : 0.210496),"ps");
  Corefrac = new RooRealVar("Corefrac","Fraction of Core",(tracktype==3 ? 0.625239 : 0.491009));
  Midfrac = new RooRealVar("Midfrac","Fraction of Middle",(tracktype==3 ? 0.362524 : 0.43744));
  
  // *** Acceptacne ***
  accX = new RooRealVar("accX","Acceptance - X",0.65);
  accX->setConstant();
  input_accY = (tracktype==3 ? 1.5195 : 2.0242);
  accY = new RooRealVar("accY","Acceptance - Y",input_accY,0.,5.,"ps");
  input_accZ = (tracktype==3 ? 2.3331 : 1.1122);
  accZ = new RooRealVar("accZ","Acceptance - Z",input_accZ,0.,5.,"ps");
  input_accVelo = (tracktype==3 ? -0.025264 : 0.030720);
  accVelo = new RooRealVar("accVelo","Acceptance - beta",input_accVelo,-0.5,0.5,"ps^{-1}");

  // *** Background ***
  input_tau_short = (tracktype==3 ? 0.39811 : -999);
  tau_short = new RooRealVar("tau_short","Average lifetime for short background component",input_tau_short,0.,1.5,"ps");
  input_tau_long = (tracktype==3 ? 1.7544 : 1.7785);
  tau_long = new RooRealVar("tau_long","Average lifetime for long background component",input_tau_long,0.5,5.,"ps");
  input_tau_fraction = (tracktype==3 ? 0.42136 : -999);
  tau_fraction = new RooRealVar("tau_fraction","Fraction of short background component",input_tau_fraction,0.,1.);
  bkgX = new RooRealVar("bkgX","Acceptance - X",1.);
  bkgX->setConstant();
  input_bkgY = (tracktype==3 ? -999 : 3.1074);
  bkgY = new RooRealVar("bkgY","Acceptance - Y",input_bkgY,0.,25.,"ps");
  input_bkgZ = (tracktype==3 ? -999 : 2.6334);
  bkgZ = new RooRealVar("bkgZ","Acceptance - Z",input_bkgZ,0.,5.,"ps");
  bkgVelo = new RooRealVar("bkgVelo","Acceptance - beta",0.,"ps^{-1}");
  bkgVelo->setConstant();
  

  // ********** Events ********** //
  //////////////////////////////////
   
  // *** Number of events in Current Sample ***
  lumi_sample = new RooRealVar("lumi_sample","Luminosity of current sample",1.018);
  nBd_sample = new RooRealVar("nBd_sample","Number of events in current sample",(tracktype==3 ? 9039.7 : 14390.3));
  nBs_sample = new RooRealVar("nBs_sample","Number of events in current sample",(tracktype==3 ? 116.7 : 155.1));
  nBkg_sample = new RooRealVar("nBkg_sample","Number of events in current sample",(tracktype==3 ? 276.6 : 492.6));
  
  // *** Scale to desired luminosity ***
  lumi_generated = new RooRealVar("lumi_generated","Generated Luminosity",LumiGen);
  // At 14 TeV we assume the b-bbar cross section to double. For simplicity I put this factor two in the luminosity
  if(LumiGen>1.018 && LumiGen<=3.060){lumi_generated->setVal(1.018+(8./7.)*(LumiGen-1.018));}// 1 fb at 7 TeV and X-1 fb at 8 TeV
  else if(LumiGen>3.060){lumi_generated->setVal(1.018+(8./7.)*(LumiGen-2.042)+2*(LumiGen-3.060));}// 3 fb at 7/8 TeV and X-3 fb at 14 TeV
  
  nBd_generated = new RooFormulaVar("nBd_generated","Number of events to generate","@0*@2/@1",RooArgSet(*nBd_sample,*lumi_sample,*lumi_generated));
  nBs_generated = new RooFormulaVar("nBs_generated","Number of events to generate","@0*@2/@1",RooArgSet(*nBs_sample,*lumi_sample,*lumi_generated));
  nBkg_generated = new RooFormulaVar("nBkg_generated","Number of events to generate","@0*@2/@1",RooArgSet(*nBkg_sample,*lumi_sample,*lumi_generated));
  
  std::cout << "Generating: " << nBd_generated->getVal() << " Bd + " << nBs_generated->getVal() << " Bs + " << nBkg_generated->getVal() << " Bkg = " << nBd_generated->getVal()+nBs_generated->getVal()+nBkg_generated->getVal() << " events." << std::endl;
  
  // Transform to RooRealVar for Fitting
  nBd_fit = new RooRealVar("nBd_fit","Number of events for fitting",nBd_generated->getVal(),0,2*nBd_generated->getVal());
  nBs_fit = new RooRealVar("nBs_fit","Number of events for fitting",nBs_generated->getVal(),0,2*nBs_generated->getVal());
  nBkg_fit = new RooRealVar("nBkg_fit","Number of events for fitting",nBkg_generated->getVal(),0,2*nBkg_generated->getVal());

};


/////////////////////////////////////////
// ********** Building PDFs ********** //
/////////////////////////////////////////

void ToyModel::BuildPdf(){

  // ********** Mass PDFs ********** //
  /////////////////////////////////////
  std::cout << "*** Building Mass PDF ***" << std::endl;

  // *** Crystal Ball ***
  CBall_Bd_I = new RooCBShape("CBall_Bd_I","CB Shape - Bd",*Bmass,*Bmass_Bd,*Bmass_sigma_I,*Bmass_apar_I,*Bmass_npar_I);  
  CBall_Bd_II = new RooCBShape("CBall_Bd_II","CB Shape - Bd",*Bmass,*Bmass_Bd,*Bmass_sigma_II,*Bmass_apar_II,*Bmass_npar_II);
  CBall_Bs_I = new RooCBShape("CBall_Bs_I","CB Shape - Bs",*Bmass,*Bmass_Bs,*Bmass_sigma_I,*Bmass_apar_I,*Bmass_npar_I);  
  CBall_Bs_II = new RooCBShape("CBall_Bs_II","CB Shape - Bs",*Bmass,*Bmass_Bs,*Bmass_sigma_II,*Bmass_apar_II,*Bmass_npar_II);

  // *** Exponential Background ***
  Bmass_Exp_bkg = new RooExponential("Bmass_Exp_bkg","Reconstructed B mass for background",*Bmass,*Bmass_lambda);

  // *** Composite PDFs ***
  Bmass_Sig_Bd = new RooAddPdf("Bmass_Sig_Bd","Reconstructed Bd mass",RooArgList(*CBall_Bd_I,*CBall_Bd_II),*Bmass_fraction);
  Bmass_Sig_Bs = new RooAddPdf("Bmass_Sig_Bs","Reconstructed Bs mass",RooArgList(*CBall_Bs_I,*CBall_Bs_II),*Bmass_fraction);


  // ********** Time PDFs ********** //
  /////////////////////////////////////
  std::cout << "*** Building Decay Time PDF ***" << std::endl;

  // *** Resolution ***
  core = new RooGaussModel("core","Core Gaussian",*Btime,*resMean,*coreSigma);
  mid = new RooGaussModel("mid","Middle Gaussian",*Btime,*resMean,*midSigma);
  tail = new RooGaussModel("tail","Tail Gaussian",*Btime,*resMean,*tailSigma);
  resModel = new RooAddModel("resModel","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));

  // *** Acceptance ***
  acceptance = new LHCbAcceptance("acceptance","Acceptance",*Btime,*accX,*accY,*accZ,*accVelo);
  bkgAcc = new LHCbAcceptance("bkgAcc","Acceptance for Bkg",*Btime,*bkgX,*bkgY,*bkgZ,*bkgVelo);
  
  // *** Signal ***
  decay_Bd = new RooDecay("decay_Bd","Fitted Decay",*Btime,*tau_Bd,*resModel,RooDecay::SingleSided);
  decay_acc_Bd = new RooEffProd("decay_acc_Bd","Decay with acceptance",*decay_Bd,*acceptance);
  decay_Bs = new RooDecay("decay_Bs","Fitted Decay",*Btime,*tau_Bs,*resModel,RooDecay::SingleSided);
  decay_acc_Bs = new RooEffProd("decay_acc_Bs","Decay with acceptance",*decay_Bs,*acceptance);
  
  // *** Background ***
  decay_short = new RooDecay("decay_short","Short Lifetimes",*Btime,*tau_short,*resModel,RooDecay::SingleSided);
  decay_long = new RooDecay("decay_long","Long Lifetimes",*Btime,*tau_long,*resModel,RooDecay::SingleSided);
  decay_acc_bkg = new RooEffProd("decay_acc_bkg","Decay with acceptance",*decay_long,*bkgAcc);
  if(TrackType==3){
    decay_background = new RooAddPdf("decay_background","Background Model",RooArgList(*decay_short,*decay_long),*tau_fraction);
  }
  else if(TrackType==5){
    decay_background = decay_acc_bkg;
  }


  // ********** Total PDFs ********** //
  //////////////////////////////////////
  std::cout << "*** Building Total Mass PDF ***" << std::endl;

  total_Bd = new RooProdPdf("total_Bd","Total PDF - Signal Bd",RooArgList(*Bmass_Sig_Bd,*decay_acc_Bd));
  total_Bs = new RooProdPdf("total_Bs","Total PDF - Signal Bs",RooArgList(*Bmass_Sig_Bs,*decay_acc_Bs));  
  total_Bkg = new RooProdPdf("total_Bkg","Total PDF - Background",RooArgList(*Bmass_Exp_bkg,*decay_background));  

  // *** Composite PDFs ***
  total_pdf = new RooAddPdf("total_pdf","Total PDF",RooArgList(*total_Bd,*total_Bs,*total_Bkg),RooArgList(*nBd_fit,*nBs_fit,*nBkg_fit),kFALSE);

};


///////////////////////////////////////////
// ********** Generating data ********** //
///////////////////////////////////////////

void ToyModel::GenerateData(int set_seed){

  // *** Identifying and starting Random Generator ***
  RooRandom::randomGenerator()->SetSeed(set_seed);
  std::cout << "*** Using Random Generator:  " << RooRandom::randomGenerator()->GetName() << " with starting seed = " << RooRandom::randomGenerator()->GetSeed() << " ***" << std::endl;

  // ********** Generating ********** //
  //////////////////////////////////////

  nEvents = (int) (nBd_generated->getVal() + nBs_generated->getVal() + nBkg_generated->getVal());
  ToyData = total_pdf->generate(RooArgSet(*Bmass,*Btime), nEvents);
  ToyData->Print();
};


///////////////////////////////////////////////////
// ***** Helper Function: Create Pull Plot ***** //
///////////////////////////////////////////////////

void ToyModel::PullPlot(TString savestring, RooPlot* frame, int logy){
  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
  doek->cd(1);
  float ratio = 0.30; // Percentage of the plot for Pull distributions
  
  // *** Pull Plot ***
  RooPlot* pullframe = (RooPlot *)frame->emptyClone("pullframe");
  
  // Titles
  pullframe->SetYTitle("Pull");
  pullframe->SetXTitle(frame->GetXaxis()->GetTitle());

  // Cosmetics
  pullframe->SetTitleSize(0.07,"x");
  pullframe->SetTitleFont(132,"x");
  pullframe->SetLabelSize(0.05,"x");
  pullframe->SetLabelFont(132,"x");
  pullframe->SetTitleSize(0,"y");// No title here  
  pullframe->SetLabelSize(0.,"y");// and no labels
  //pullframe->SetLabelFont(132,"y");  
  
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
  // Fill Pad  
  frame->Draw("");
  
  
  // *** LHCb Tag *** 
  TPaveText *lhcbTag = 0;
  //if(logy==1){lhcbTag = new TPaveText(0.22,0.75,0.46,0.89,"NDC");}
  if(logy==1){lhcbTag = new TPaveText(0.65,0.75,0.89,0.89,"NDC");}
  if(logy==0){lhcbTag = new TPaveText(0.65,0.35,0.89,0.47,"NDC");}

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(TrackType==3) lhcbTag->AddText("#splitline{Toy Simulation}{#scale[0.7]{Long K_{S}^{0}}}");
  else if(TrackType==5) lhcbTag->AddText("#splitline{Toy Simulation}{#scale[0.7]{Downstream K_{S}^{0}}}");

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


////////////////////////////////////
// ********** Plotting ********** //
////////////////////////////////////

void ToyModel::Plotting(TString tag){

  // ********** B0 Mass frame ********** //
  /////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Mass ***" << std::endl;

  // *** Mass Distribution ***
  RooPlot* massFrame = Bmass->frame(Bins(68));

  // Titles
  massFrame->SetYTitle("# Events/(5 MeV/c^{2})");
  massFrame->SetXTitle("m_{J/#psi K_{S}^{0}} (MeV/c^{2})");

  // Cosmetics
  massFrame->SetTitleOffset(0.8,"x");
  massFrame->SetTitleOffset(1.2,"y");
  massFrame->SetTitleSize(0.07,"x");
  massFrame->SetTitleSize(0.07,"y");
  massFrame->SetTitleFont(132,"y");
  massFrame->SetTitleFont(132,"x");
  massFrame->SetLabelSize(0.05,"y");
  massFrame->SetLabelSize(0.05,"x");
  massFrame->SetLabelFont(132,"x");
  massFrame->SetLabelFont(132,"y");

  ToyData->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  total_pdf->plotOn(massFrame,Components("Bmass_Sig_Bd"),LineWidth(2),LineColor(2));
  total_pdf->plotOn(massFrame,Components("Bmass_Sig_Bs"),LineWidth(2),LineColor(3));  
  total_pdf->plotOn(massFrame,Components("Bmass_Exp_bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(massFrame,LineWidth(2),LineColor(4));

  // General Settings
  massFrame->SetMinimum(0.9);
  massFrame->SetMaximum(5000);
  
  TString track = (TrackType==3 ? "LL" : "DD");
  
  PullPlot("ToyModel_Bmass_"+track+"_"+tag+".pdf",massFrame,1);


  // ********** Bs Lifetime frame ********** //
  /////////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Decay Time ***" << std::endl;

  // *** Datapoints and distribution ***
  RooPlot *tauFrame = Btime->frame(Bins(74)); 
  tauFrame->SetYTitle("# Events/(0.2 ps)");
  tauFrame->SetXTitle("B decay time (ps)");

  tauFrame->SetTitleOffset(1.3,"y");
  tauFrame->SetTitleSize(0.07,"x");
  tauFrame->SetTitleSize(0.07,"y");
  tauFrame->SetTitleFont(132,"y");
  tauFrame->SetTitleFont(132,"x");
  tauFrame->SetLabelSize(0.05,"x");
  tauFrame->SetLabelSize(0.05,"y");
  tauFrame->SetLabelFont(132,"x");
  tauFrame->SetLabelFont(132,"y");
  
  // *** Full Untagged Sample ***
  ToyData->plotOn(tauFrame,MarkerStyle(21),MarkerSize(0.8));
  total_pdf->plotOn(tauFrame,Components("total_Bd"),LineWidth(2),LineColor(2));
  total_pdf->plotOn(tauFrame,Components("total_Bs"),LineWidth(2),LineColor(3));
  total_pdf->plotOn(tauFrame,Components("total_Bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(tauFrame,LineWidth(2),LineColor(4));
  
  // General Settings
  tauFrame->SetMinimum(1);
  tauFrame->SetMaximum(5000);
  
  // Add Pull Distribution
  PullPlot("ToyModel_Btime_"+track+"_"+tag+".pdf",tauFrame,1);
  
  
  // ********** Bs Lifetime frame ********** //
  /////////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Decay Time in Bs mass window ***" << std::endl;

  // *** Datapoints and distribution ***
  RooPlot *tauBsFrame = Btime->frame(Bins(74)); 
  tauBsFrame->SetYTitle("# Events/(0.2 ps)");
  tauBsFrame->SetXTitle("B decay time (ps)");

  tauBsFrame->SetTitleOffset(1.3,"y");
  tauBsFrame->SetTitleSize(0.07,"x");
  tauBsFrame->SetTitleSize(0.07,"y");
  tauBsFrame->SetTitleFont(132,"y");
  tauBsFrame->SetTitleFont(132,"x");
  tauBsFrame->SetLabelSize(0.05,"x");
  tauBsFrame->SetLabelSize(0.05,"y");
  tauBsFrame->SetLabelFont(132,"x");
  tauBsFrame->SetLabelFont(132,"y");
  
  // *** Full Untagged Sample ***
  Bmass->setRange("BsOnly",5340,5390);
  ToyData->plotOn(tauBsFrame,CutRange("BsOnly"),MarkerStyle(21),MarkerSize(0.8));
  total_pdf->plotOn(tauBsFrame,ProjectionRange("BsOnly"),Components("total_Bd"),LineWidth(2),LineColor(2));
  total_pdf->plotOn(tauBsFrame,ProjectionRange("BsOnly"),Components("total_Bs"),LineWidth(2),LineColor(3));
  total_pdf->plotOn(tauBsFrame,ProjectionRange("BsOnly"),Components("total_Bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(tauBsFrame,ProjectionRange("BsOnly"),LineWidth(2),LineColor(4));
  
  // General Settings
  tauBsFrame->SetMinimum(1);
  tauBsFrame->SetMaximum(100);
  
  // Add Pull Distribution
  PullPlot("ToyModel_Btime_BsOnly_"+track+"_"+tag+".pdf",tauBsFrame,1);
  

  // ********** Bs Lifetime frame ********** //
  /////////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Decay Time in Mass Sidebands ***" << std::endl;

  // *** Datapoints and distribution ***
  RooPlot *tauBkgFrame = Btime->frame(Bins(74)); 
  tauBkgFrame->SetYTitle("# Events/(0.2 ps)");
  tauBkgFrame->SetXTitle("B decay time (ps)");

  tauBkgFrame->SetTitleOffset(1.3,"y");
  tauBkgFrame->SetTitleSize(0.07,"x");
  tauBkgFrame->SetTitleSize(0.07,"y");
  tauBkgFrame->SetTitleFont(132,"y");
  tauBkgFrame->SetTitleFont(132,"x");
  tauBkgFrame->SetLabelSize(0.05,"x");
  tauBkgFrame->SetLabelSize(0.05,"y");
  tauBkgFrame->SetLabelFont(132,"x");
  tauBkgFrame->SetLabelFont(132,"y");
  
  // *** Full Untagged Sample ***
  Bmass->setRange("MassSidebands",5400,5520);
  ToyData->plotOn(tauBkgFrame,CutRange("MassSidebands"),MarkerStyle(21),MarkerSize(0.8));
  total_pdf->plotOn(tauBkgFrame,ProjectionRange("MassSidebands"),Components("total_Bd"),LineWidth(2),LineColor(2));
  total_pdf->plotOn(tauBkgFrame,ProjectionRange("MassSidebands"),Components("total_Bs"),LineWidth(2),LineColor(3));
  total_pdf->plotOn(tauBkgFrame,ProjectionRange("MassSidebands"),Components("total_Bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(tauBkgFrame,ProjectionRange("MassSidebands"),LineWidth(2),LineColor(4));
  
  // General Settings
  tauBkgFrame->SetMinimum(1);
  tauBkgFrame->SetMaximum(100);
  
  // Add Pull Distribution
  PullPlot("ToyModel_Btime_MassSidebands_"+track+"_"+tag+".pdf",tauBkgFrame,1);

};


//////////////////////////////////////////////
// ********** Fitting parameters ********** //
//////////////////////////////////////////////

void ToyModel::FittingParameters(){

  // ********** Fit ********** //
  ///////////////////////////////
  
  std::cout << "*** Fitting parameters ***" << std::endl;
  RooFitResult *fitresult = total_pdf->fitTo(*ToyData,Save(),Strategy(2),Verbose());
  fitresult->Print();
  
  // ********** Extract results ********** //
  ///////////////////////////////////////////

  Minuit_status = fitresult->status();
  Minuit_covQual = fitresult->covQual();
  Minuit_edm = fitresult->edm();
  Minuit_globalCorr_accY = fitresult->globalCorr("accY");
  Minuit_globalCorr_accZ = fitresult->globalCorr("accZ");
  Minuit_globalCorr_accVelo = fitresult->globalCorr("accVelo");

  Minuit_nBd_Val = -999;
  Minuit_nBd_Err = -999;
  Minuit_nBd_Pull = -999;  
  Minuit_nBs_Val = -999;
  Minuit_nBs_Err = -999;
  Minuit_nBs_Pull = -999;  
  Minuit_nBkg_Val = -999;
  Minuit_nBkg_Err = -999;  
  Minuit_nBkg_Pull = -999;
  
  Minuit_Bmass_Bd_Val = -999;
  Minuit_Bmass_Bd_Err = -999;
  Minuit_Bmass_Bd_Pull = -999; 
  Minuit_sigma_I_Val = -999;
  Minuit_sigma_I_Err = -999;
  Minuit_sigma_I_Pull = -999; 
  Minuit_sigma_II_Val = -999;
  Minuit_sigma_II_Err = -999;
  Minuit_sigma_II_Pull = -999; 
  Minuit_fraction_Val = -999;
  Minuit_fraction_Err = -999;
  Minuit_fraction_Pull = -999; 
  Minuit_lambda_Val = -999;
  Minuit_lambda_Err = -999;
  Minuit_lambda_Pull = -999;
  
  Minuit_accY_Val = -999;
  Minuit_accY_Err = -999;
  Minuit_accY_Pull = -999; 
  Minuit_accZ_Val = -999;
  Minuit_accZ_Err = -999;
  Minuit_accZ_Pull = -999; 
  Minuit_accVelo_Val = -999;
  Minuit_accVelo_Err = -999;
  Minuit_accVelo_Pull = -999; 
  Minuit_tau_Bs_Val = -999;
  Minuit_tau_Bs_Err = -999;
  Minuit_tau_Bs_Pull = -999; 
  
  Minuit_bkgY_Val = -999;
  Minuit_bkgY_Err = -999;
  Minuit_bkgY_Pull = -999; 
  Minuit_bkgZ_Val = -999;
  Minuit_bkgZ_Err = -999;
  Minuit_bkgZ_Pull = -999; 
  Minuit_tau_short_Val = -999;
  Minuit_tau_short_Err = -999;
  Minuit_tau_short_Pull = -999; 
  Minuit_tau_long_Val = -999;
  Minuit_tau_long_Err = -999;
  Minuit_tau_long_Pull = -999; 
  Minuit_tau_fraction_Val = -999;
  Minuit_tau_fraction_Err = -999;
  Minuit_tau_fraction_Pull = -999; 
  
  const RooArgList& fitted_par = fitresult->floatParsFinal();
  
  temp_Par = (RooRealVar*)fitted_par.find("nBd_fit");
  if(temp_Par){
    Minuit_nBd_Val = temp_Par->getVal();
    Minuit_nBd_Err = temp_Par->getError();
    Minuit_nBd_Pull = (Minuit_nBd_Val-nBd_generated->getVal())/Minuit_nBd_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("nBs_fit");
  if(temp_Par){
    Minuit_nBs_Val = temp_Par->getVal();
    Minuit_nBs_Err = temp_Par->getError();
    Minuit_nBs_Pull = (Minuit_nBs_Val-nBs_generated->getVal())/Minuit_nBs_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("nBkg_fit");
  if(temp_Par){
    Minuit_nBkg_Val = temp_Par->getVal();
    Minuit_nBkg_Err = temp_Par->getError();
    Minuit_nBkg_Pull = (Minuit_nBkg_Val-nBkg_generated->getVal())/Minuit_nBkg_Err;
  delete temp_Par;
  }

  temp_Par = (RooRealVar*)fitted_par.find("Bmass_Bd");
  if(temp_Par){
    Minuit_Bmass_Bd_Val = temp_Par->getVal();
    Minuit_Bmass_Bd_Err = temp_Par->getError();
    Minuit_Bmass_Bd_Pull = (Minuit_Bmass_Bd_Val-input_Bmass_Bd)/Minuit_Bmass_Bd_Err;
  delete temp_Par;
  }

  temp_Par = (RooRealVar*)fitted_par.find("Bmass_sigma_I");
  if(temp_Par){
    Minuit_sigma_I_Val = temp_Par->getVal();
    Minuit_sigma_I_Err = temp_Par->getError();
    Minuit_sigma_I_Pull = (Minuit_sigma_I_Val-input_sigma_I)/Minuit_sigma_I_Err;
  delete temp_Par;
  }

  temp_Par = (RooRealVar*)fitted_par.find("Bmass_sigma_II");
  if(temp_Par){
    Minuit_sigma_II_Val = temp_Par->getVal();
    Minuit_sigma_II_Err = temp_Par->getError();
    Minuit_sigma_II_Pull = (Minuit_sigma_II_Val-input_sigma_II)/Minuit_sigma_II_Err;
  delete temp_Par;
  }

  temp_Par = (RooRealVar*)fitted_par.find("Bmass_fraction");
  if(temp_Par){
    Minuit_fraction_Val = temp_Par->getVal();
    Minuit_fraction_Err = temp_Par->getError();
    Minuit_fraction_Pull = (Minuit_fraction_Val-input_fraction)/Minuit_fraction_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("Bmass_lambda");
  if(temp_Par){
    Minuit_lambda_Val = temp_Par->getVal();
    Minuit_lambda_Err = temp_Par->getError();
    Minuit_lambda_Pull = (Minuit_lambda_Val-input_lambda)/Minuit_lambda_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("accY");
  if(temp_Par){
    Minuit_accY_Val = temp_Par->getVal();
    Minuit_accY_Err = temp_Par->getError();
    Minuit_accY_Pull = (Minuit_accY_Val-input_accY)/Minuit_accY_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("accZ");
  if(temp_Par){
    Minuit_accZ_Val = temp_Par->getVal();
    Minuit_accZ_Err = temp_Par->getError();
    Minuit_accZ_Pull = (Minuit_accZ_Val-input_accZ)/Minuit_accZ_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("accVelo");
  if(temp_Par){
    Minuit_accVelo_Val = temp_Par->getVal();
    Minuit_accVelo_Err = temp_Par->getError();
    Minuit_accVelo_Pull = (Minuit_accVelo_Val-input_accVelo)/Minuit_accVelo_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("tau_Bs");
  if(temp_Par){
    Minuit_tau_Bs_Val = temp_Par->getVal();
    Minuit_tau_Bs_Err = temp_Par->getError();
    Minuit_tau_Bs_Pull = (Minuit_tau_Bs_Val-input_tau_Bs)/Minuit_tau_Bs_Err;
  delete temp_Par;
  }

  temp_Par = (RooRealVar*)fitted_par.find("bkgY");
  if(temp_Par){
    Minuit_bkgY_Val = temp_Par->getVal();
    Minuit_bkgY_Err = temp_Par->getError();
    Minuit_bkgY_Pull = (Minuit_bkgY_Val-input_bkgY)/Minuit_bkgY_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("bkgZ");
  if(temp_Par){
    Minuit_bkgZ_Val = temp_Par->getVal();
    Minuit_bkgZ_Err = temp_Par->getError();
    Minuit_bkgZ_Pull = (Minuit_bkgZ_Val-input_bkgZ)/Minuit_bkgZ_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("tau_long");
  if(temp_Par){
    Minuit_tau_long_Val = temp_Par->getVal();
    Minuit_tau_long_Err = temp_Par->getError();
    Minuit_tau_long_Pull = (Minuit_tau_long_Val-input_tau_long)/Minuit_tau_long_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("tau_short");
  if(temp_Par){
    Minuit_tau_short_Val = temp_Par->getVal();
    Minuit_tau_short_Err = temp_Par->getError();
    Minuit_tau_short_Pull = (Minuit_tau_short_Val-input_tau_short)/Minuit_tau_short_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("tau_fraction");
  if(temp_Par){
    Minuit_tau_fraction_Val = temp_Par->getVal();
    Minuit_tau_fraction_Err = temp_Par->getError();
    Minuit_tau_fraction_Pull = (Minuit_tau_fraction_Val-input_tau_fraction)/Minuit_tau_fraction_Err;
  delete temp_Par;
  }

  
  
  // ********** Report ********** //
  //////////////////////////////////

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "///////////////////////////////////" << std::endl;
  std::cout << "// ********** Results ********** //" << std::endl;
  std::cout << "///////////////////////////////////" << std::endl;
  std::cout << "Status" << std::endl;
  std::cout << "======" << std::endl;  
  std::cout << "Minuit Status: " << Minuit_status << std::endl;
  std::cout << "Covariance Quality: " << Minuit_covQual << std::endl;
  std::cout << "EDM: " << Minuit_edm << std::endl;
  std::cout << "accY Global Cor: " << Minuit_globalCorr_accY << std::endl;
  std::cout << "accZ Global Cor: " << Minuit_globalCorr_accZ << std::endl;
  std::cout << "accVelo Global Cor: " << Minuit_globalCorr_accVelo << std::endl;
  std::cout << std::endl;
  std::cout << "Number of Events" << std::endl;
  std::cout << "================" << std::endl;  
  std::cout << "Number of Bd->JpsiKs  Events = " << Minuit_nBd_Val << " +/- " << Minuit_nBd_Err << " / Input: " << nBd_generated->getVal() << " / Pull: " << Minuit_nBd_Pull << std::endl;
  std::cout << "Number of Bs->JpsiKs  Events = " << Minuit_nBs_Val << " +/- " << Minuit_nBs_Err << " / Input: " << nBs_generated->getVal() << " / Pull: " << Minuit_nBs_Pull << std::endl;
  std::cout << "Number of Background Events = " << Minuit_nBkg_Val << " +/- " << Minuit_nBkg_Err << " / Input: " << nBkg_generated->getVal() << " / Pull: " << Minuit_nBkg_Pull << std::endl;
  std::cout << std::endl;
  std::cout << "Mass" << std::endl;
  std::cout << "====" << std::endl;  
  std::cout << "Bd mass = " << Minuit_Bmass_Bd_Val << " +/- " << Minuit_Bmass_Bd_Err << " / Input: 5279.58 / Pull: " << Minuit_Bmass_Bd_Pull << std::endl;
  std::cout << "Sigma I = " << Minuit_sigma_I_Val << " +/- " << Minuit_sigma_I_Err << " / Input: " << input_sigma_I << " / Pull: " << Minuit_sigma_I_Pull << std::endl;
  std::cout << "Sigma II = " << Minuit_sigma_II_Val << " +/- " << Minuit_sigma_II_Err << " / Input: " << input_sigma_II << " / Pull: " << Minuit_sigma_II_Pull << std::endl;
  std::cout << "Fraction = " << Minuit_fraction_Val << " +/- " << Minuit_fraction_Err << " / Input: " << input_fraction << " / Pull: " << Minuit_fraction_Pull << std::endl;
  std::cout << "Lambda = " << Minuit_lambda_Val << " +/- " << Minuit_lambda_Err << " / Input: " << input_lambda << " / Pull: " << Minuit_lambda_Pull << std::endl;
  std::cout << std::endl;
  std::cout << "Acceptance" << std::endl;
  std::cout << "==========" << std::endl;  
  std::cout << "Acc Y = " << Minuit_accY_Val << " +/- " << Minuit_accY_Err << " / Input: " << input_accY << " / Pull: " << Minuit_accY_Pull << std::endl;
  std::cout << "Acc Z = " << Minuit_accZ_Val << " +/- " << Minuit_accZ_Err << " / Input: " << input_accZ << " / Pull: " << Minuit_accZ_Pull << std::endl;
  std::cout << "Acc Velo = " << Minuit_accVelo_Val << " +/- " << Minuit_accVelo_Err << " / Input: " << input_accVelo << " / Pull: " << Minuit_accVelo_Pull << std::endl;
  std::cout << std::endl;
  std::cout << "Background" << std::endl;
  std::cout << "==========" << std::endl;  
  if(TrackType==5) std::cout << "Bkg Y = " << Minuit_bkgY_Val << " +/- " << Minuit_bkgY_Err << " / Input: " << input_bkgY << " / Pull: " << Minuit_bkgY_Pull << std::endl;
  if(TrackType==5) std::cout << "Bkg Z = " << Minuit_bkgZ_Val << " +/- " << Minuit_bkgZ_Err << " / Input: " << input_bkgZ << " / Pull: " << Minuit_bkgZ_Pull << std::endl;
  if(TrackType==3) std::cout << "Tau Short = " << Minuit_tau_short_Val << " +/- " << Minuit_tau_short_Err << " / Input: " << input_tau_short << " / Pull: " << Minuit_tau_short_Pull << std::endl;
  std::cout << "Tau Long = " << Minuit_tau_long_Val << " +/- " << Minuit_tau_long_Err << " / Input: " << input_tau_long << " / Pull: " << Minuit_tau_long_Pull << std::endl;
  if(TrackType==3) std::cout << "Tau Fraction = " << Minuit_tau_fraction_Val << " +/- " << Minuit_tau_fraction_Err << " / Input: " << input_tau_fraction << " / Pull: " << Minuit_tau_fraction_Pull << std::endl;
  std::cout << std::endl;
  std::cout << "Effective Lifetime" << std::endl;
  std::cout << "==================" << std::endl;  
  std::cout << "Tau Bs = " << Minuit_tau_Bs_Val << " +/- " << Minuit_tau_Bs_Err << " / Input: " << input_tau_Bs << " / Pull: " << Minuit_tau_Bs_Pull << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

};


//////////////////////////////////
// ********** Saving ********** //
//////////////////////////////////

void ToyModel::Saving(){
  std::cout << "*** Saving data ***" << std::endl;
  
  double input_nBd = nBd_generated->getVal();
  double input_nBs = nBs_generated->getVal();
  double input_nBkg = nBkg_generated->getVal();

  // ********** File ********** //
  ////////////////////////////////
  // *** Creating n-tuple to store the results ***
  TString track = (TrackType==3 ? "LL" : "DD");
  TString rootfile = "Toy_Model_Results_"+track+".root";

  std::cout << "*** Opening file: " << rootfile << " ***" << std::endl;
  TFile *save_data = new TFile(rootfile,"UPDATE");
  save_data->cd();
  
  // ********** NTuples ********** //
  ///////////////////////////////////
  
  outputTree = (TTree *) save_data->Get("Minuit_Results");
  if(!outputTree){
    outputTree = new TTree("Minuit_Results","Minuit Results");
    
    outputTree->Branch("LumiGen", &LumiGen,"b_LumiGen/D");
    outputTree->Branch("Minuit_status", &Minuit_status,"b_Minuit_status/I");
    outputTree->Branch("Minuit_covQual", &Minuit_covQual,"b_Minuit_covQual/I");
    outputTree->Branch("Minuit_edm", &Minuit_edm,"b_Minuit_edm/D");
    outputTree->Branch("Minuit_globalCorr_accY", &Minuit_globalCorr_accY,"b_Minuit_globalCorr_accY/D");
    outputTree->Branch("Minuit_globalCorr_accZ", &Minuit_globalCorr_accZ,"b_Minuit_globalCorr_accZ/D");
    outputTree->Branch("Minuit_globalCorr_accVelo", &Minuit_globalCorr_accVelo,"b_Minuit_globalCorr_accVelo/D");
    
    outputTree->Branch("input_nBd", &input_nBd,"b_input_nBd/D");
    outputTree->Branch("Minuit_nBd_Val", &Minuit_nBd_Val,"b_Minuit_nBd_Val/D");
    outputTree->Branch("Minuit_nBd_Err", &Minuit_nBd_Err,"b_Minuit_nBd_Err/D");
    outputTree->Branch("Minuit_nBd_Pull", &Minuit_nBd_Pull,"b_Minuit_nBd_Pull/D");
  
    outputTree->Branch("input_nBs", &input_nBs,"b_input_nBs/D");
    outputTree->Branch("Minuit_nBs_Val", &Minuit_nBs_Val,"b_Minuit_nBs_Val/D");
    outputTree->Branch("Minuit_nBs_Err", &Minuit_nBs_Err,"b_Minuit_nBs_Err/D");
    outputTree->Branch("Minuit_nBs_Pull", &Minuit_nBs_Pull,"b_Minuit_nBs_Pull/D");

    outputTree->Branch("input_nBkg", &input_nBkg,"b_input_nBkg/D");
    outputTree->Branch("Minuit_nBkg_Val", &Minuit_nBkg_Val,"b_Minuit_nBkg_Val/D");
    outputTree->Branch("Minuit_nBkg_Err", &Minuit_nBkg_Err,"b_Minuit_nBkg_Err/D");
    outputTree->Branch("Minuit_nBkg_Pull", &Minuit_nBkg_Pull,"b_Minuit_nBkg_Pull/D");
  
    outputTree->Branch("input_Bmass_Bd", &input_Bmass_Bd,"b_input_Bmass_Bd/D");
    outputTree->Branch("Minuit_Bmass_Bd_Val", &Minuit_Bmass_Bd_Val,"b_Minuit_Bmass_Bd_Val/D");
    outputTree->Branch("Minuit_Bmass_Bd_Err", &Minuit_Bmass_Bd_Err,"b_Minuit_Bmass_Bd_Err/D");
    outputTree->Branch("Minuit_Bmass_Bd_Pull", &Minuit_Bmass_Bd_Pull,"b_Minuit_Bmass_Bd_Pull/D");
  
    outputTree->Branch("input_sigma_I", &input_sigma_I,"b_input_sigma_I/D");
    outputTree->Branch("Minuit_sigma_I_Val", &Minuit_sigma_I_Val,"b_Minuit_sigma_I_Val/D");
    outputTree->Branch("Minuit_sigma_I_Err", &Minuit_sigma_I_Err,"b_Minuit_sigma_I_Err/D");
    outputTree->Branch("Minuit_sigma_I_Pull", &Minuit_sigma_I_Pull,"b_Minuit_sigma_I_Pull/D");
  
    outputTree->Branch("input_sigma_II", &input_sigma_II,"b_input_sigma_II/D");
    outputTree->Branch("Minuit_sigma_II_Val", &Minuit_sigma_II_Val,"b_Minuit_sigma_II_Val/D");
    outputTree->Branch("Minuit_sigma_II_Err", &Minuit_sigma_II_Err,"b_Minuit_sigma_II_Err/D");
    outputTree->Branch("Minuit_sigma_II_Pull", &Minuit_sigma_II_Pull,"b_Minuit_sigma_II_Pull/D");
  
    outputTree->Branch("input_fraction", &input_fraction,"b_input_fraction/D");
    outputTree->Branch("Minuit_fraction_Val", &Minuit_fraction_Val,"b_Minuit_fraction_Val/D");
    outputTree->Branch("Minuit_fraction_Err", &Minuit_fraction_Err,"b_Minuit_fraction_Err/D");
    outputTree->Branch("Minuit_fraction_Pull", &Minuit_fraction_Pull,"b_Minuit_fraction_Pull/D");
  
    outputTree->Branch("input_lambda", &input_lambda,"b_input_lambda/D");
    outputTree->Branch("Minuit_lambda_Val", &Minuit_lambda_Val,"b_Minuit_lambda_Val/D");
    outputTree->Branch("Minuit_lambda_Err", &Minuit_lambda_Err,"b_Minuit_lambda_Err/D");
    outputTree->Branch("Minuit_lambda_Pull", &Minuit_lambda_Pull,"b_Minuit_lambda_Pull/D");

    outputTree->Branch("input_accY", &input_accY,"b_input_accY/D");
    outputTree->Branch("Minuit_accY_Val", &Minuit_accY_Val,"b_Minuit_accY_Val/D");
    outputTree->Branch("Minuit_accY_Err", &Minuit_accY_Err,"b_Minuit_accY_Err/D");
    outputTree->Branch("Minuit_accY_Pull", &Minuit_accY_Pull,"b_Minuit_accY_Pull/D");

    outputTree->Branch("input_accZ", &input_accZ,"b_input_accZ/D");
    outputTree->Branch("Minuit_accZ_Val", &Minuit_accZ_Val,"b_Minuit_accZ_Val/D");
    outputTree->Branch("Minuit_accZ_Err", &Minuit_accZ_Err,"b_Minuit_accZ_Err/D");
    outputTree->Branch("Minuit_accZ_Pull", &Minuit_accZ_Pull,"b_Minuit_accZ_Pull/D");
  
    outputTree->Branch("input_accVelo", &input_accVelo,"b_input_accVelo/D");
    outputTree->Branch("Minuit_accVelo_Val", &Minuit_accVelo_Val,"b_Minuit_accVelo_Val/D");
    outputTree->Branch("Minuit_accVelo_Err", &Minuit_accVelo_Err,"b_Minuit_accVelo_Err/D");
    outputTree->Branch("Minuit_accVelo_Pull", &Minuit_accVelo_Pull,"b_Minuit_accVelo_Pull/D");
  
    outputTree->Branch("input_bkgY", &input_bkgY,"b_input_bkgY/D");
    outputTree->Branch("Minuit_bkgY_Val", &Minuit_bkgY_Val,"b_Minuit_bkgY_Val/D");
    outputTree->Branch("Minuit_bkgY_Err", &Minuit_bkgY_Err,"b_Minuit_bkgY_Err/D");
    outputTree->Branch("Minuit_bkgY_Pull", &Minuit_bkgY_Pull,"b_Minuit_bkgY_Pull/D");
  
    outputTree->Branch("input_bkgZ", &input_bkgZ,"b_input_bkgZ/D");
    outputTree->Branch("Minuit_bkgZ_Val", &Minuit_bkgZ_Val,"b_Minuit_bkgZ_Val/D");
    outputTree->Branch("Minuit_bkgZ_Err", &Minuit_bkgZ_Err,"b_Minuit_bkgZ_Err/D");
    outputTree->Branch("Minuit_bkgZ_Pull", &Minuit_bkgZ_Pull,"b_Minuit_bkgZ_Pull/D");
  
    outputTree->Branch("input_tau_short", &input_tau_short,"b_input_tau_short/D");
    outputTree->Branch("Minuit_tau_short_Val", &Minuit_tau_short_Val,"b_Minuit_tau_short_Val/D");
    outputTree->Branch("Minuit_tau_short_Err", &Minuit_tau_short_Err,"b_Minuit_tau_short_Err/D");
    outputTree->Branch("Minuit_tau_short_Pull", &Minuit_tau_short_Pull,"b_Minuit_tau_short_Pull/D");
  
    outputTree->Branch("input_tau_long", &input_tau_long,"b_input_tau_long/D");
    outputTree->Branch("Minuit_tau_long_Val", &Minuit_tau_long_Val,"b_Minuit_tau_long_Val/D");
    outputTree->Branch("Minuit_tau_long_Err", &Minuit_tau_long_Err,"b_Minuit_tau_long_Err/D");
    outputTree->Branch("Minuit_tau_long_Pull", &Minuit_tau_long_Pull,"b_Minuit_tau_long_Pull/D");
  
    outputTree->Branch("input_tau_fraction", &input_tau_fraction,"b_input_tau_fraction/D");
    outputTree->Branch("Minuit_tau_fraction_Val", &Minuit_tau_fraction_Val,"b_Minuit_tau_fraction_Val/D");
    outputTree->Branch("Minuit_tau_fraction_Err", &Minuit_tau_fraction_Err,"b_Minuit_tau_fraction_Err/D");
    outputTree->Branch("Minuit_tau_fraction_Pull", &Minuit_tau_fraction_Pull,"b_Minuit_tau_fraction_Pull/D");
  
    outputTree->Branch("input_tau_Bs", &input_tau_Bs,"b_input_tau_Bs/D");
    outputTree->Branch("Minuit_tau_Bs_Val", &Minuit_tau_Bs_Val,"b_Minuit_tau_Bs_Val/D");
    outputTree->Branch("Minuit_tau_Bs_Err", &Minuit_tau_Bs_Err,"b_Minuit_tau_Bs_Err/D");
    outputTree->Branch("Minuit_tau_Bs_Pull", &Minuit_tau_Bs_Pull,"b_Minuit_tau_Bs_Pull/D");
  }
  else{
    TBranch *b_LumiGen;
    outputTree->SetBranchAddress("LumiGen", &LumiGen,&b_LumiGen);
    TBranch *b_Minuit_status;
    outputTree->SetBranchAddress("Minuit_status", &Minuit_status,&b_Minuit_status);
    TBranch *b_Minuit_covQual;
    outputTree->SetBranchAddress("Minuit_covQual", &Minuit_covQual,&b_Minuit_covQual);
    TBranch *b_Minuit_edm;
    outputTree->SetBranchAddress("Minuit_edm", &Minuit_edm,&b_Minuit_edm);
    TBranch *b_Minuit_globalCorr_accY;
    outputTree->SetBranchAddress("Minuit_globalCorr_accY", &Minuit_globalCorr_accY,&b_Minuit_globalCorr_accY);
    TBranch *b_Minuit_globalCorr_accZ;
    outputTree->SetBranchAddress("Minuit_globalCorr_accZ", &Minuit_globalCorr_accZ,&b_Minuit_globalCorr_accZ);
    TBranch *b_Minuit_globalCorr_accVelo;
    outputTree->SetBranchAddress("Minuit_globalCorr_accVelo", &Minuit_globalCorr_accVelo,&b_Minuit_globalCorr_accVelo);
    
    TBranch *b_input_nBd;
    outputTree->SetBranchAddress("input_nBd", &input_nBd,&b_input_nBd);
    TBranch *b_Minuit_nBd_Val;
    outputTree->SetBranchAddress("Minuit_nBd_Val", &Minuit_nBd_Val,&b_Minuit_nBd_Val);
    TBranch *b_Minuit_nBd_Err;
    outputTree->SetBranchAddress("Minuit_nBd_Err", &Minuit_nBd_Err,&b_Minuit_nBd_Err);
    TBranch *b_Minuit_nBd_Pull;
    outputTree->SetBranchAddress("Minuit_nBd_Pull", &Minuit_nBd_Pull,&b_Minuit_nBd_Pull);
  
    TBranch *b_input_nBs;
    outputTree->SetBranchAddress("input_nBs", &input_nBs,&b_input_nBs);
    TBranch *b_Minuit_nBs_Val;
    outputTree->SetBranchAddress("Minuit_nBs_Val", &Minuit_nBs_Val,&b_Minuit_nBs_Val);
    TBranch *b_Minuit_nBs_Err;
    outputTree->SetBranchAddress("Minuit_nBs_Err", &Minuit_nBs_Err,&b_Minuit_nBs_Err);
    TBranch *b_Minuit_nBs_Pull;
    outputTree->SetBranchAddress("Minuit_nBs_Pull", &Minuit_nBs_Pull,&b_Minuit_nBs_Pull);

    TBranch *b_input_nBkg;
    outputTree->SetBranchAddress("input_nBkg", &input_nBkg,&b_input_nBkg);
    TBranch *b_Minuit_nBkg_Val;
    outputTree->SetBranchAddress("Minuit_nBkg_Val", &Minuit_nBkg_Val,&b_Minuit_nBkg_Val);
    TBranch *b_Minuit_nBkg_Err;
    outputTree->SetBranchAddress("Minuit_nBkg_Err", &Minuit_nBkg_Err,&b_Minuit_nBkg_Err);
    TBranch *b_Minuit_nBkg_Pull;
    outputTree->SetBranchAddress("Minuit_nBkg_Pull", &Minuit_nBkg_Pull,&b_Minuit_nBkg_Pull);
 
    TBranch *b_input_Bmass_Bd;
    outputTree->SetBranchAddress("input_Bmass_Bd", &input_Bmass_Bd,&b_input_Bmass_Bd);
    TBranch *b_Minuit_Bmass_Bd_Val;
    outputTree->SetBranchAddress("Minuit_Bmass_Bd_Val", &Minuit_Bmass_Bd_Val,&b_Minuit_Bmass_Bd_Val);
    TBranch *b_Minuit_Bmass_Bd_Err;
    outputTree->SetBranchAddress("Minuit_Bmass_Bd_Err", &Minuit_Bmass_Bd_Err,&b_Minuit_Bmass_Bd_Err);
    TBranch *b_Minuit_Bmass_Bd_Pull;
    outputTree->SetBranchAddress("Minuit_Bmass_Bd_Pull", &Minuit_Bmass_Bd_Pull,&b_Minuit_Bmass_Bd_Pull);

    TBranch *b_input_sigma_I;
    outputTree->SetBranchAddress("input_sigma_I", &input_sigma_I,&b_input_sigma_I);
    TBranch *b_Minuit_sigma_I_Val;
    outputTree->SetBranchAddress("Minuit_sigma_I_Val", &Minuit_sigma_I_Val,&b_Minuit_sigma_I_Val);
    TBranch *b_Minuit_sigma_I_Err;
    outputTree->SetBranchAddress("Minuit_sigma_I_Err", &Minuit_sigma_I_Err,&b_Minuit_sigma_I_Err);
    TBranch *b_Minuit_sigma_I_Pull;
    outputTree->SetBranchAddress("Minuit_sigma_I_Pull", &Minuit_sigma_I_Pull,&b_Minuit_sigma_I_Pull);
 
    TBranch *b_input_sigma_II;
    outputTree->SetBranchAddress("input_sigma_II", &input_sigma_II,&b_input_sigma_II);
    TBranch *b_Minuit_sigma_II_Val;
    outputTree->SetBranchAddress("Minuit_sigma_II_Val", &Minuit_sigma_II_Val,&b_Minuit_sigma_II_Val);
    TBranch *b_Minuit_sigma_II_Err;
    outputTree->SetBranchAddress("Minuit_sigma_II_Err", &Minuit_sigma_II_Err,&b_Minuit_sigma_II_Err);
    TBranch *b_Minuit_sigma_II_Pull;
    outputTree->SetBranchAddress("Minuit_sigma_II_Pull", &Minuit_sigma_II_Pull,&b_Minuit_sigma_II_Pull);

    TBranch *b_input_fraction;  
    outputTree->SetBranchAddress("input_fraction", &input_fraction,&b_input_fraction);
    TBranch *b_Minuit_fraction_Val;
    outputTree->SetBranchAddress("Minuit_fraction_Val", &Minuit_fraction_Val,&b_Minuit_fraction_Val);
    TBranch *b_Minuit_fraction_Err;
    outputTree->SetBranchAddress("Minuit_fraction_Err", &Minuit_fraction_Err,&b_Minuit_fraction_Err);
    TBranch *b_Minuit_fraction_Pull;
    outputTree->SetBranchAddress("Minuit_fraction_Pull", &Minuit_fraction_Pull,&b_Minuit_fraction_Pull);

    TBranch *b_input_lambda;  
    outputTree->SetBranchAddress("input_lambda", &input_lambda,&b_input_lambda);
    TBranch *b_Minuit_lambda_Val;
    outputTree->SetBranchAddress("Minuit_lambda_Val", &Minuit_lambda_Val,&b_Minuit_lambda_Val);
    TBranch *b_Minuit_lambda_Err;
    outputTree->SetBranchAddress("Minuit_lambda_Err", &Minuit_lambda_Err,&b_Minuit_lambda_Err);
    TBranch *b_Minuit_lambda_Pull;
    outputTree->SetBranchAddress("Minuit_lambda_Pull", &Minuit_lambda_Pull,&b_Minuit_lambda_Pull);

    TBranch *b_input_accY;
    outputTree->SetBranchAddress("input_accY", &input_accY,&b_input_accY);
    TBranch *b_Minuit_accY_Val;
    outputTree->SetBranchAddress("Minuit_accY_Val", &Minuit_accY_Val,&b_Minuit_accY_Val);
    TBranch *b_Minuit_accY_Err;
    outputTree->SetBranchAddress("Minuit_accY_Err", &Minuit_accY_Err,&b_Minuit_accY_Err);
    TBranch *b_Minuit_accY_Pull;
    outputTree->SetBranchAddress("Minuit_accY_Pull", &Minuit_accY_Pull,&b_Minuit_accY_Pull);

    TBranch *b_input_accZ;
    outputTree->SetBranchAddress("input_accZ", &input_accZ,&b_input_accZ);
    TBranch *b_Minuit_accZ_Val;
    outputTree->SetBranchAddress("Minuit_accZ_Val", &Minuit_accZ_Val,&b_Minuit_accZ_Val);
    TBranch *b_Minuit_accZ_Err;
    outputTree->SetBranchAddress("Minuit_accZ_Err", &Minuit_accZ_Err,&b_Minuit_accZ_Err);
    TBranch *b_Minuit_accZ_Pull;
    outputTree->SetBranchAddress("Minuit_accZ_Pull", &Minuit_accZ_Pull,&b_Minuit_accZ_Pull);

    TBranch *b_input_accVelo;  
    outputTree->SetBranchAddress("input_accVelo", &input_accVelo,&b_input_accVelo);
    TBranch *b_Minuit_accVelo_Val;
    outputTree->SetBranchAddress("Minuit_accVelo_Val", &Minuit_accVelo_Val,&b_Minuit_accVelo_Val);
    TBranch *b_Minuit_accVelo_Err;
    outputTree->SetBranchAddress("Minuit_accVelo_Err", &Minuit_accVelo_Err,&b_Minuit_accVelo_Err);
    TBranch *b_Minuit_accVelo_Pull;
    outputTree->SetBranchAddress("Minuit_accVelo_Pull", &Minuit_accVelo_Pull,&b_Minuit_accVelo_Pull);

    TBranch *b_input_bkgY;  
    outputTree->SetBranchAddress("input_bkgY", &input_bkgY,&b_input_bkgY);
    TBranch *b_Minuit_bkgY_Val;
    outputTree->SetBranchAddress("Minuit_bkgY_Val", &Minuit_bkgY_Val,&b_Minuit_bkgY_Val);
    TBranch *b_Minuit_bkgY_Err;
    outputTree->SetBranchAddress("Minuit_bkgY_Err", &Minuit_bkgY_Err,&b_Minuit_bkgY_Err);
    TBranch *b_Minuit_bkgY_Pull;
    outputTree->SetBranchAddress("Minuit_bkgY_Pull", &Minuit_bkgY_Pull,&b_Minuit_bkgY_Pull);

    TBranch *b_input_bkgZ;  
    outputTree->SetBranchAddress("input_bkgZ", &input_bkgZ,&b_input_bkgZ);
    TBranch *b_Minuit_bkgZ_Val;
    outputTree->SetBranchAddress("Minuit_bkgZ_Val", &Minuit_bkgZ_Val,&b_Minuit_bkgZ_Val);
    TBranch *b_Minuit_bkgZ_Err;
    outputTree->SetBranchAddress("Minuit_bkgZ_Err", &Minuit_bkgZ_Err,&b_Minuit_bkgZ_Err);
    TBranch *b_Minuit_bkgZ_Pull;
    outputTree->SetBranchAddress("Minuit_bkgZ_Pull", &Minuit_bkgZ_Pull,&b_Minuit_bkgZ_Pull);
 
    TBranch *b_input_tau_short;
    outputTree->SetBranchAddress("input_tau_short", &input_tau_short,&b_input_tau_short);
    TBranch *b_Minuit_tau_short_Val;
    outputTree->SetBranchAddress("Minuit_tau_short_Val", &Minuit_tau_short_Val,&b_Minuit_tau_short_Val);
    TBranch *b_Minuit_tau_short_Err;
    outputTree->SetBranchAddress("Minuit_tau_short_Err", &Minuit_tau_short_Err,&b_Minuit_tau_short_Err);
    TBranch *b_Minuit_tau_short_Pull;
    outputTree->SetBranchAddress("Minuit_tau_short_Pull", &Minuit_tau_short_Pull,&b_Minuit_tau_short_Pull);
 
    TBranch *b_input_tau_long;
    outputTree->SetBranchAddress("input_tau_long", &input_tau_long,&b_input_tau_long);
    TBranch *b_Minuit_tau_long_Val;
    outputTree->SetBranchAddress("Minuit_tau_long_Val", &Minuit_tau_long_Val,&b_Minuit_tau_long_Val);
    TBranch *b_Minuit_tau_long_Err;
    outputTree->SetBranchAddress("Minuit_tau_long_Err", &Minuit_tau_long_Err,&b_Minuit_tau_long_Err);
    TBranch *b_Minuit_tau_long_Pull;
    outputTree->SetBranchAddress("Minuit_tau_long_Pull", &Minuit_tau_long_Pull,&b_Minuit_tau_long_Pull);
 
    TBranch *b_input_tau_fraction;
    outputTree->SetBranchAddress("input_tau_fraction", &input_tau_fraction,&b_input_tau_fraction);
    TBranch *b_Minuit_tau_fraction_Val;
    outputTree->SetBranchAddress("Minuit_tau_fraction_Val", &Minuit_tau_fraction_Val,&b_Minuit_tau_fraction_Val);
    TBranch *b_Minuit_tau_fraction_Err;
    outputTree->SetBranchAddress("Minuit_tau_fraction_Err", &Minuit_tau_fraction_Err,&b_Minuit_tau_fraction_Err);
    TBranch *b_Minuit_tau_fraction_Pull;
    outputTree->SetBranchAddress("Minuit_tau_fraction_Pull", &Minuit_tau_fraction_Pull,&b_Minuit_tau_fraction_Pull);
  
    TBranch *b_input_tau_Bs;
    outputTree->SetBranchAddress("input_tau_Bs", &input_tau_Bs,&b_input_tau_Bs);
    TBranch *b_Minuit_tau_Bs_Val;
    outputTree->SetBranchAddress("Minuit_tau_Bs_Val", &Minuit_tau_Bs_Val,&b_Minuit_tau_Bs_Val);
    TBranch *b_Minuit_tau_Bs_Err;
    outputTree->SetBranchAddress("Minuit_tau_Bs_Err", &Minuit_tau_Bs_Err,&b_Minuit_tau_Bs_Err);
    TBranch *b_Minuit_tau_Bs_Pull;
    outputTree->SetBranchAddress("Minuit_tau_Bs_Pull", &Minuit_tau_Bs_Pull,&b_Minuit_tau_Bs_Pull);
  }


  // ********** Writing ********** //
  ///////////////////////////////////
  outputTree->Fill();
  outputTree->Write("", TObject::kOverwrite);
  std::cout << "*** Data saved ***" << std::endl;
  save_data->Close();

}
