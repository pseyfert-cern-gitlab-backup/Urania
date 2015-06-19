/////////////////////////////////////////////////
// ********** Toy Monte Carlo Model ********** //
/////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the study of Bs->JpsiKs at LHCb
// - Feasibility study: Separate LL and DD fits for Bs + Bkg mass window [5340,5520] only


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
  Bmass = new RooRealVar("Bmass","Reconstructed B0 mass",5340.,5520.,"MeV/c^{2}");

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
  
  // *** Tagged Parameters *** //
  ///////////////////////////////
  
	// *** Penguin parameters ***
  a_penguin = new RooRealVar("a_penguin","Penguin contribution",0.22448);
  theta_penguin = new RooRealVar("theta_penguin","Penguin phase",180.213*acos(-1)/180);

  // *** CKM Constants ***
  gamma = new RooRealVar("gamma","CP angle",68*acos(-1)/180);// arXiv 1011.1096
  eta = new RooRealVar("eta","CP eigenvalue",-1);// J/psi Ks is CP odd
  phi_Bs   = new RooRealVar("phi_Bs","Bs - Bsbar mixing angle",-2.08*acos(-1)/180);// arXiv 1106.4041

  // *** Lifetime Constants ***
  //tau_Bs = new RooRealVar("tau_Bs","Average lifetime for Bs",1./0.6714,"ps");// LHCB-ANA-2012-067
  tau_Bs = new RooRealVar("tau_Bs","Average lifetime for Bs",1.503,"ps");// HFAG - Fall 2012
  //dG_Bs  = new RooRealVar("dG_Bs","Lifetime difference for Bs",0.100,"ps^-1"); // HFAG - PDG 2012 && LHCB-ANA-2012-067
  dG_Bs  = new RooRealVar("dG_Bs","Lifetime difference for Bs",0.091,"ps^-1"); // HFAG - Fall 2012
  dM_Bs  = new RooRealVar("dM_Bs","Mass difference between light and heavy weak-eigenstate for Bs",17.725,"ps^-1");// LHCB-CONF-2011-050
  
  // *** CP Observables *** 
  Robs_Bs_input = new RooFormulaVar("Robs_Bs_input","R observable for Bs", "1-2*@0*cos(@1)*cos(@2)+pow(@0,2)",RooArgList(*a_penguin,*theta_penguin,*gamma));
  Adir_Bs_input = new RooFormulaVar("Adir_Bs_input","Direct CP asymmetry for Bs", "(2*@0*sin(@1)*sin(@2))/(1-2*@0*cos(@1)*cos(@2)+pow(@0,2))",RooArgList(*a_penguin,*theta_penguin,*gamma));
  Amix_Bs_input = new RooFormulaVar("Amix_Bs_input","Mixing induced CP asymmetry for Bs", "@4*(sin(@3)-2*@0*cos(@1)*sin(@3+@2)+pow(@0,2)*sin(@3+2*@2))/(1-2*@0*cos(@1)*cos(@2)+pow(@0,2))",RooArgList(*a_penguin,*theta_penguin,*gamma,*phi_Bs,*eta));
  ADG_Bs_input  = new RooFormulaVar("ADG_Bs_input" ,"Delta Gamma CP asymmetry for Bs", "-1*@4*(cos(@3)-2*@0*cos(@1)*cos(@3+@2)+pow(@0,2)*cos(@3+2*@2))/(1-2*@0*cos(@1)*cos(@2)+pow(@0,2))",RooArgList(*a_penguin,*theta_penguin,*gamma,*phi_Bs,*eta));

  Adir_Bs = new RooRealVar("Adir_Bs","Direct CP asymmetry for Bs", Adir_Bs_input->getVal(),-3.,3.);
  Amix_Bs = new RooRealVar("Amix_Bs","Mixing induced CP asymmetry for Bs",Amix_Bs_input->getVal(),-3.,3.);
  ADG_Bs  = new RooRealVar("ADG_Bs" ,"Delta Gamma CP asymmetry for Bs", ADG_Bs_input->getVal(),-3.,3.);

  // *** Mistagging ***
  // |A(t)|_obs^2 = w|Abar(t)|_phys^2 + (1-w)|A(t)|_phys^2
  mistag = new RooRealVar("mistag","Mistag fraction of original B and Bbar",(0.367*(0.332-0.332*0.121) + 0.344*0.121)/(0.332 + 0.121 - 0.332*0.121));// LHCB-CONF-2012-026 && LHCB-CONF-2012-050
  tageff = new RooRealVar("tageff","Tagging efficiency",0.332 + 0.121 - 0.332*0.121);// LHCB-CONF-2012-026 && LHCB-CONF-2012-050
  tag = new RooCategory("tag","Flavour tag of the B meson");
  tag->defineType("B",1);
  tag->defineType("Bbar",-1);
  tag->defineType("untag",0);
  
  // *** Coefficients for the decay equations ***
  // Overall normalization is done automatically
  tagNorm = new RooFormulaVar("tagNorm","Normalisation using tagging eff","@0!=0 ? 0.5*@1 : 1-@1",RooArgList(*tag,*tageff));
  ACosh_Bs = new RooFormulaVar("ACosh_Bs","Parameter of the Cosh in decay equation for Bs","@0",RooArgList(*tagNorm));
  DSinh_Bs = new RooFormulaVar("DSinh_Bs","Parameter of the Sinh in decay equation for Bs","@0*@1",RooArgList(*tagNorm,*ADG_Bs));
  CCos_Bs = new RooFormulaVar("CCos_Bs","Parameter of the Cos in decay equation for Bs","@0*@3*@1*(1-2*@2)",RooArgList(*tagNorm,*Adir_Bs,*mistag,*tag));
  SSin_Bs = new RooFormulaVar("SSin_Bs","Parameter of the Sin in decay equation for Bs","@0*@3*@1*(1-2*@2)",RooArgList(*tagNorm,*Amix_Bs,*mistag,*tag));
  
  
  // *** Untagged Parameters *** //
  /////////////////////////////////
  
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
  nBs_sample = new RooRealVar("nBs_sample","Number of events in current sample",(tracktype==3 ? 116.7 : 155.1));
  nBkg_sample = new RooRealVar("nBkg_sample","Number of events in current sample",(tracktype==3 ? 121.5 : 192.4));
  
  // *** Scale to desired luminosity ***
  lumi_generated = new RooRealVar("lumi_generated","Generated Luminosity",LumiGen);
  // At 14 TeV we assume the b-bbar cross section to double. For simplicity I put this factor two in the luminosity
  if(LumiGen>1.018 && LumiGen<=3.060){lumi_generated->setVal(1.018+(8./7.)*(LumiGen-1.018));}// 1 fb at 7 TeV and X-1 fb at 8 TeV
  else if(LumiGen>3.060){lumi_generated->setVal(1.018+(8./7.)*(LumiGen-2.042)+2*(LumiGen-3.060));}// 3 fb at 7/8 TeV and X-3 fb at 14 TeV
  
  nBs_generated = new RooFormulaVar("nBs_generated","Number of events to generate","@0*@2/@1",RooArgSet(*nBs_sample,*lumi_sample,*lumi_generated));
  nBkg_generated = new RooFormulaVar("nBkg_generated","Number of events to generate","@0*@2/@1",RooArgSet(*nBkg_sample,*lumi_sample,*lumi_generated));
  
  std::cout << "Generating: " << nBs_generated->getVal() << " Bs + " << nBkg_generated->getVal() << " Bkg = " << nBs_generated->getVal()+nBkg_generated->getVal() << " events." << std::endl;
  
  // Transform to RooRealVar for Fitting
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
  CBall_Bs_I = new RooCBShape("CBall_Bs_I","CB Shape - Bs",*Bmass,*Bmass_Bs,*Bmass_sigma_I,*Bmass_apar_I,*Bmass_npar_I);  
  CBall_Bs_II = new RooCBShape("CBall_Bs_II","CB Shape - Bs",*Bmass,*Bmass_Bs,*Bmass_sigma_II,*Bmass_apar_II,*Bmass_npar_II);

  // *** Exponential Background ***
  Bmass_Exp_bkg = new RooExponential("Bmass_Exp_bkg","Reconstructed B mass for background",*Bmass,*Bmass_lambda);

  // *** Composite PDFs ***
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
  decay_Bs = new RooBDecay("decay_Bs","Fitted Decay",*Btime,*tau_Bs,*dG_Bs,*ACosh_Bs,*DSinh_Bs,*CCos_Bs,*SSin_Bs,*dM_Bs,*resModel,RooBDecay::SingleSided);
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

  total_Bs = new RooProdPdf("total_Bs","Total PDF - Signal Bs",RooArgList(*Bmass_Sig_Bs,*decay_acc_Bs));  
  total_Bkg = new RooProdPdf("total_Bkg","Total PDF - Background",RooArgList(*Bmass_Exp_bkg,*decay_background));  

  // *** Composite PDFs ***
  total_pdf = new RooAddPdf("total_pdf","Total PDF",RooArgList(*total_Bs,*total_Bkg),RooArgList(*nBs_fit,*nBkg_fit),false);

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

  nEvents = (int) (nBs_generated->getVal() + nBkg_generated->getVal());
  ToyData = total_pdf->generate(RooArgSet(*Bmass,*Btime,*tag), nEvents);
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
  pullframe->SetTitleOffset(0.9,"x");
  pullframe->SetTitleFont(132,"x");
  pullframe->SetLabelSize(0.04,"x");
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

void ToyModel::Plotting(TString label){

  // ********** B0 Mass frame ********** //
  /////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Mass ***" << std::endl;

  // *** Mass Distribution ***
  RooPlot* massFrame = Bmass->frame(Bins(60));

  // Titles
  massFrame->SetYTitle("# Events/(3 MeV/c^{2})");
  massFrame->SetXTitle("m_{J/#psi K_{S}^{0}} #scale[0.8]{(MeV/c^{2})}");

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
  total_pdf->plotOn(massFrame,Components("Bmass_Sig_Bs"),LineWidth(2),LineColor(3));  
  total_pdf->plotOn(massFrame,Components("Bmass_Exp_bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(massFrame,LineWidth(2),LineColor(4));

  // General Settings
  massFrame->SetMinimum(0.9);
  massFrame->SetMaximum(100);
  
  TString track = (TrackType==3 ? "LL" : "DD");
  
  PullPlot("ToyModel_Bmass_"+track+"_"+label+".pdf",massFrame,1);


  // ********** Bs Lifetime frame ********** //
  /////////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Untagged Decay Time ***" << std::endl;

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
  total_pdf->plotOn(tauFrame,Components("total_Bs"),LineWidth(2),LineColor(3));
  total_pdf->plotOn(tauFrame,Components("total_Bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(tauFrame,LineWidth(2),LineColor(4));
  
  // General Settings
  tauFrame->SetMinimum(1);
  tauFrame->SetMaximum(500);
  
  // Add Pull Distribution
  PullPlot("ToyModel_Btime_"+track+"_"+label+".pdf",tauFrame,1);
  
  
  // ********** Bs Lifetime frame ********** //
  /////////////////////////////////////////////

  std::cout << "*** Plotting PDF components: Tagged Decay Time ***" << std::endl;

  // *** Datapoints and distribution ***
  RooPlot *tagFrame = Btime->frame(Bins(74)); 
  tagFrame->SetYTitle("# Events/(0.2 ps)");
  tagFrame->SetXTitle("B decay time (ps)");

  tagFrame->SetTitleOffset(1.3,"y");
  tagFrame->SetTitleSize(0.07,"x");
  tagFrame->SetTitleSize(0.07,"y");
  tagFrame->SetTitleFont(132,"y");
  tagFrame->SetTitleFont(132,"x");
  tagFrame->SetLabelSize(0.05,"x");
  tagFrame->SetLabelSize(0.05,"y");
  tagFrame->SetLabelFont(132,"x");
  tagFrame->SetLabelFont(132,"y");
  
  // *** Full Untagged Sample ***
  ToyData->plotOn(tagFrame,Cut("tag==1"),MarkerStyle(21),MarkerSize(0.8));
  total_pdf->plotOn(tagFrame,Slice(*tag,"B"),Components("total_Bs"),LineWidth(2),LineColor(3));
  total_pdf->plotOn(tagFrame,Slice(*tag,"B"),Components("total_Bkg"),LineWidth(2),LineColor(1),LineStyle(kDashed));
  total_pdf->plotOn(tagFrame,Slice(*tag,"B"),LineWidth(2),LineColor(4));
  
  // General Settings
  tagFrame->SetMinimum(1);
  tagFrame->SetMaximum(100);
  
  // Add Pull Distribution
  PullPlot("ToyModel_Btime_Tagged_"+track+"_"+label+".pdf",tagFrame,1);

};


//////////////////////////////////////////////
// ********** Fitting parameters ********** //
//////////////////////////////////////////////

void ToyModel::FittingParameters(TString setup){
  
  std::cout << "*** Fitting parameters ***" << std::endl;
  
  // ********** Fit ********** //
  ///////////////////////////////
  
  // Systematics Fits
  if(TrackType==3){
    Bmass_sigma_I->setVal(setup=="sigmaI+" ? input_sigma_I+0.0830587 : (setup=="sigmaI-" ? input_sigma_I-0.0830587 : input_sigma_I));
    Bmass_sigma_II->setVal(setup=="sigmaII+" ? input_sigma_II+0.118424 : (setup=="sigmaII-" ? input_sigma_II-0.118424 : input_sigma_II));
    Bmass_fraction->setVal(setup=="fraction+" ? input_fraction+0.0195975 : (setup=="fraction-" ? input_fraction-0.0195975 : input_fraction));
    Bmass_lambda->setVal(setup=="lambda+" ? input_lambda+0.000383303 : (setup=="lambda-" ? input_lambda-0.000383303 : input_lambda));
    accY->setVal(setup=="accY+" ? input_accY+0.090213 : (setup=="accY-" ? input_accY-0.090213 : input_accY));
    accZ->setVal(setup=="accZ+" ? input_accZ+0.113975 : (setup=="accZ-" ? input_accZ-0.113975 : input_accZ));
    accVelo->setVal(setup=="accVelo+" ? input_accVelo+0.00563871 : (setup=="accVelo-" ? input_accVelo-0.00563871 : input_accVelo));
    tau_short->setVal(setup=="tau_short+" ? input_tau_short+0.06702 : (setup=="tau_short-" ? input_tau_short-0.06702 : input_tau_short));
    tau_long->setVal(setup=="tau_long+" ? input_tau_long+0.172539 : (setup=="tau_long-" ? input_tau_long-0.172539 : input_tau_long));
    tau_fraction->setVal(setup=="tau_fraction+" ? input_tau_fraction+0.0736814 : (setup=="tau_fraction-" ? input_tau_fraction-0.0736814 : input_tau_fraction));
  }
  else if(TrackType==5){
    Bmass_sigma_I->setVal(setup=="sigmaI+" ? input_sigma_I+0.084198 : (setup=="sigmaI-" ? input_sigma_I-0.084198 : input_sigma_I));
    Bmass_sigma_II->setVal(setup=="sigmaII+" ? input_sigma_II+0.347354 : (setup=="sigmaII-" ? input_sigma_II-0.347354 : input_sigma_II));
    Bmass_fraction->setVal(setup=="fraction+" ? input_fraction+0.0190301 : (setup=="fraction-" ? input_fraction-0.0190301 : input_fraction));
    Bmass_lambda->setVal(setup=="lambda+" ? input_lambda+0.000293372 : (setup=="lambda-" ? input_lambda-0.000293372 : input_lambda));
    accY->setVal(setup=="accY+" ? input_accY+0.0470528 : (setup=="accY-" ? input_accY-0.0470528 : input_accY));
    accZ->setVal(setup=="accZ+" ? input_accZ+0.0340995 : (setup=="accZ-" ? input_accZ-0.0340995 : input_accZ));
    accVelo->setVal(setup=="accVelo+" ? input_accVelo+0.00711173 : (setup=="accVelo-" ? input_accVelo-0.00711173 : input_accVelo));
    bkgY->setVal(setup=="bkgY+" ? input_bkgY+0.767295 : (setup=="bkgY-" ? input_bkgY-0.767295 : input_bkgY));
    bkgZ->setVal(setup=="bkgZ+" ? input_bkgZ+0.244815 : (setup=="bkgZ-" ? input_bkgZ-0.244815 : input_bkgZ));
    tau_long->setVal(setup=="tau_long+" ? input_tau_long+0.0724936 : (setup=="tau_long-" ? input_tau_long-0.0724936 : input_tau_long));
  }
  
  // Constants
  // We will need to fix them from a separate fit to the untagged sample
  Bmass_Bd->setConstant();
  Bmass_sigma_I->setConstant();
  Bmass_sigma_II->setConstant();
  Bmass_fraction->setConstant();
  accY->setConstant();
  accZ->setConstant();
  accVelo->setConstant();
  // and while we are at it
  Bmass_lambda->setConstant();
  bkgY->setConstant();
  bkgZ->setConstant();
  tau_short->setConstant();
  tau_long->setConstant();
  tau_fraction->setConstant();
  
  RooFitResult *fitresult = total_pdf->fitTo(*ToyData,Save(),Strategy(2),Verbose());
  fitresult->Print();
  
  // ********** Extract results ********** //
  ///////////////////////////////////////////

  Minuit_status = fitresult->status();
  Minuit_covQual = fitresult->covQual();
  Minuit_edm = fitresult->edm();

  Minuit_nBs_Val = -999;
  Minuit_nBs_Err = -999;
  Minuit_nBs_Pull = -999;  
  Minuit_nBkg_Val = -999;
  Minuit_nBkg_Err = -999;  
  Minuit_nBkg_Pull = -999;
  Minuit_ADG_Bs_Val = -999;
  Minuit_ADG_Bs_Err = -999;
  Minuit_ADG_Bs_Pull = -999; 
  Minuit_Adir_Bs_Val = -999;
  Minuit_Adir_Bs_Err = -999;
  Minuit_Adir_Bs_Pull = -999; 
  Minuit_Amix_Bs_Val = -999;
  Minuit_Amix_Bs_Err = -999;
  Minuit_Amix_Bs_Pull = -999; 
  
  const RooArgList& fitted_par = fitresult->floatParsFinal();

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
  temp_Par = (RooRealVar*)fitted_par.find("ADG_Bs");
  if(temp_Par){
    Minuit_ADG_Bs_Val = temp_Par->getVal();
    Minuit_ADG_Bs_Err = temp_Par->getError();
    Minuit_ADG_Bs_Pull = (Minuit_ADG_Bs_Val-ADG_Bs_input->getVal())/Minuit_ADG_Bs_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("Adir_Bs");
  if(temp_Par){
    Minuit_Adir_Bs_Val = temp_Par->getVal();
    Minuit_Adir_Bs_Err = temp_Par->getError();
    Minuit_Adir_Bs_Pull = (Minuit_Adir_Bs_Val-Adir_Bs_input->getVal())/Minuit_Adir_Bs_Err;
  delete temp_Par;
  }
  
  temp_Par = (RooRealVar*)fitted_par.find("Amix_Bs");
  if(temp_Par){
    Minuit_Amix_Bs_Val = temp_Par->getVal();
    Minuit_Amix_Bs_Err = temp_Par->getError();
    Minuit_Amix_Bs_Pull = (Minuit_Amix_Bs_Val-Amix_Bs_input->getVal())/Minuit_Amix_Bs_Err;
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
  std::cout << std::endl;
  std::cout << "Number of Events" << std::endl;
  std::cout << "================" << std::endl;  
  std::cout << "Number of Bs->JpsiKs  Events = " << Minuit_nBs_Val << " +/- " << Minuit_nBs_Err << " / Input: " << nBs_generated->getVal() << " / Pull: " << Minuit_nBs_Pull << std::endl;
  std::cout << "Number of Background Events = " << Minuit_nBkg_Val << " +/- " << Minuit_nBkg_Err << " / Input: " << nBkg_generated->getVal() << " / Pull: " << Minuit_nBkg_Pull << std::endl;
  std::cout << std::endl;
  std::cout << "CP Observables" << std::endl;
  std::cout << "==============" << std::endl;
  std::cout << "ADG = " << Minuit_ADG_Bs_Val << " +/- " << Minuit_ADG_Bs_Err << " / Input: " << ADG_Bs_input->getVal() << " / Pull: " << Minuit_ADG_Bs_Pull << std::endl;
  std::cout << "Adir = " << Minuit_Adir_Bs_Val << " +/- " << Minuit_Adir_Bs_Err << " / Input: " << Adir_Bs_input->getVal() << " / Pull: " << Minuit_Adir_Bs_Pull << std::endl;
  std::cout << "Amix = " << Minuit_Amix_Bs_Val << " +/- " << Minuit_Amix_Bs_Err << " / Input: " << Amix_Bs_input->getVal() << " / Pull: " << Minuit_Amix_Bs_Pull << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

};


//////////////////////////////////
// ********** Saving ********** //
//////////////////////////////////

void ToyModel::Saving(){
  std::cout << "*** Saving data ***" << std::endl;
  
  double input_nBs = nBs_generated->getVal();
  double input_nBkg = nBkg_generated->getVal();
  
  double input_ADG_Bs = ADG_Bs_input->getVal();
  double input_Adir_Bs = Adir_Bs_input->getVal();
  double input_Amix_Bs = Amix_Bs_input->getVal();
  

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
    
    outputTree->Branch("input_nBs", &input_nBs,"b_input_nBs/D");
    outputTree->Branch("Minuit_nBs_Val", &Minuit_nBs_Val,"b_Minuit_nBs_Val/D");
    outputTree->Branch("Minuit_nBs_Err", &Minuit_nBs_Err,"b_Minuit_nBs_Err/D");
    outputTree->Branch("Minuit_nBs_Pull", &Minuit_nBs_Pull,"b_Minuit_nBs_Pull/D");

    outputTree->Branch("input_nBkg", &input_nBkg,"b_input_nBkg/D");
    outputTree->Branch("Minuit_nBkg_Val", &Minuit_nBkg_Val,"b_Minuit_nBkg_Val/D");
    outputTree->Branch("Minuit_nBkg_Err", &Minuit_nBkg_Err,"b_Minuit_nBkg_Err/D");
    outputTree->Branch("Minuit_nBkg_Pull", &Minuit_nBkg_Pull,"b_Minuit_nBkg_Pull/D");

    outputTree->Branch("input_ADG_Bs", &input_ADG_Bs,"b_input_ADG_Bs/D");
    outputTree->Branch("Minuit_ADG_Bs_Val", &Minuit_ADG_Bs_Val,"b_Minuit_ADG_Bs_Val/D");
    outputTree->Branch("Minuit_ADG_Bs_Err", &Minuit_ADG_Bs_Err,"b_Minuit_ADG_Bs_Err/D");
    outputTree->Branch("Minuit_ADG_Bs_Pull", &Minuit_ADG_Bs_Pull,"b_Minuit_ADG_Bs_Pull/D");

    outputTree->Branch("input_Adir_Bs", &input_Adir_Bs,"b_input_Adir_Bs/D");
    outputTree->Branch("Minuit_Adir_Bs_Val", &Minuit_Adir_Bs_Val,"b_Minuit_Adir_Bs_Val/D");
    outputTree->Branch("Minuit_Adir_Bs_Err", &Minuit_Adir_Bs_Err,"b_Minuit_Adir_Bs_Err/D");
    outputTree->Branch("Minuit_Adir_Bs_Pull", &Minuit_Adir_Bs_Pull,"b_Minuit_Adir_Bs_Pull/D");

    outputTree->Branch("input_Amix_Bs", &input_Amix_Bs,"b_input_Amix_Bs/D");
    outputTree->Branch("Minuit_Amix_Bs_Val", &Minuit_Amix_Bs_Val,"b_Minuit_Amix_Bs_Val/D");
    outputTree->Branch("Minuit_Amix_Bs_Err", &Minuit_Amix_Bs_Err,"b_Minuit_Amix_Bs_Err/D");
    outputTree->Branch("Minuit_Amix_Bs_Pull", &Minuit_Amix_Bs_Pull,"b_Minuit_Amix_Bs_Pull/D");

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

    TBranch *b_input_ADG_Bs;
    outputTree->SetBranchAddress("input_ADG_Bs", &input_ADG_Bs,&b_input_ADG_Bs);
    TBranch *b_Minuit_ADG_Bs_Val;
    outputTree->SetBranchAddress("Minuit_ADG_Bs_Val", &Minuit_ADG_Bs_Val,&b_Minuit_ADG_Bs_Val);
    TBranch *b_Minuit_ADG_Bs_Err;
    outputTree->SetBranchAddress("Minuit_ADG_Bs_Err", &Minuit_ADG_Bs_Err,&b_Minuit_ADG_Bs_Err);
    TBranch *b_Minuit_ADG_Bs_Pull;
    outputTree->SetBranchAddress("Minuit_ADG_Bs_Pull", &Minuit_ADG_Bs_Pull,&b_Minuit_ADG_Bs_Pull);
    
    TBranch *b_input_Adir_Bs;
    outputTree->SetBranchAddress("input_Adir_Bs", &input_Adir_Bs,&b_input_Adir_Bs);
    TBranch *b_Minuit_Adir_Bs_Val;
    outputTree->SetBranchAddress("Minuit_Adir_Bs_Val", &Minuit_Adir_Bs_Val,&b_Minuit_Adir_Bs_Val);
    TBranch *b_Minuit_Adir_Bs_Err;
    outputTree->SetBranchAddress("Minuit_Adir_Bs_Err", &Minuit_Adir_Bs_Err,&b_Minuit_Adir_Bs_Err);
    TBranch *b_Minuit_Adir_Bs_Pull;
    outputTree->SetBranchAddress("Minuit_Adir_Bs_Pull", &Minuit_Adir_Bs_Pull,&b_Minuit_Adir_Bs_Pull);
    
    TBranch *b_input_Amix_Bs;
    outputTree->SetBranchAddress("input_Amix_Bs", &input_Amix_Bs,&b_input_Amix_Bs);
    TBranch *b_Minuit_Amix_Bs_Val;
    outputTree->SetBranchAddress("Minuit_Amix_Bs_Val", &Minuit_Amix_Bs_Val,&b_Minuit_Amix_Bs_Val);
    TBranch *b_Minuit_Amix_Bs_Err;
    outputTree->SetBranchAddress("Minuit_Amix_Bs_Err", &Minuit_Amix_Bs_Err,&b_Minuit_Amix_Bs_Err);
    TBranch *b_Minuit_Amix_Bs_Pull;
    outputTree->SetBranchAddress("Minuit_Amix_Bs_Pull", &Minuit_Amix_Bs_Pull,&b_Minuit_Amix_Bs_Pull);

  }


  // ********** Writing ********** //
  ///////////////////////////////////
  outputTree->Fill();
  outputTree->Write("", TObject::kOverwrite);
  std::cout << "*** Data saved ***" << std::endl;
  save_data->Close();

}
