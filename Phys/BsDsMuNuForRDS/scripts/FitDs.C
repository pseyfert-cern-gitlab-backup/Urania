#include "RooGaussian.h"
#include "RooExponential.h"
#include "TFile.h"
#include "RooRealVar.h"
#include "TH1F.h"
#include "RooDataHist.h"
#include "RooExtendPdf.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooGenericPdf.h"
#include "RooLandau.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"
#include "RooEffProd.h"
#include "RooCBShape.h"

void FitDs(){
 
  gSystem->Load("libRooFit");
  using namespace RooFit;
  using namespace RooStats;

  TTree *tree;
  TChain *chain = new TChain("B2DsMuNuTuple/DecayTree");
  chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/DataMagUp_S23r1_RDS_FromVubStripping.root");
  chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/s/sogilvy/RDs/DataMagDown_S23r1_RDS_FromVubStripping.root");
  tree = chain;

  double entries = tree->GetEntries();

  RooRealVar mass("Ds_MM","Ds_MM",1900,2048);
  RooRealVar muProb("mu_ProbNNmu","m_ProbNNmu", 0., 1.);
  RooRealVar isoBDT("Bs_0_D1_isobdt3_2nd", "Bs_0_D1_isobdt3_2nd", -5., 5.);
  RooRealVar mcorr("Bs_0_MCORR", "Bs_0_MCORR", 3000, 7000);
  RooRealVar DsPE("Ds_PE", "Ds_PE", 0.,1000000);
  RooRealVar DsPX("Ds_PX", "Ds_PX", -1000000.,1000000);
  RooRealVar DsPY("Ds_PY", "Ds_PY", -1000000.,1000000);
  RooRealVar DsPZ("Ds_PZ", "Ds_PZ", -1000000.,1000000);
  RooRealVar muPE("mu_PE", "mu_PE", 0.,1000000);
  RooRealVar muPX("mu_PX", "mu_PX", -1000000.,1000000);
  RooRealVar muPY("mu_PY", "mu_PY", -1000000.,1000000);
  RooRealVar muPZ("mu_PZ", "mu_PZ", -1000000.,1000000); 

  TCut cuts = "mu_ProbNNmu>0.3 && Bs_0_D1_isobdt3_2nd>0.09 && sqrt(pow((Ds_PE+mu_PE),2)-(pow(Ds_PX+mu_PX,2)+pow(Ds_PY+mu_PY,2)+pow(Ds_PZ+mu_PZ,2)))>3000 && Bs_0_MCORR<7000 && Bs_0_MCORR>3000";
  RooArgSet vars(mass,muProb,isoBDT,mcorr);
  vars.add(RooArgSet(DsPE,DsPX,DsPY,DsPZ));
  vars.add(RooArgSet(muPE,muPX,muPY,muPZ));
  
  RooDataSet *data = new RooDataSet("ds", "ds", vars, Import(*tree), Cut(cuts));

  mass.setRange("AllRange",1900,2048);
  mass.setRange("FitRange",1950,1990);
  
  RooRealVar mean = RooRealVar("Mean", "mean", 1968., 1966., 1970., "MeV/c^{2}");
  RooRealVar sigma = RooRealVar("Sigma", "sigma", 7, 3, 15, "MeV/c^{2}");
  RooRealVar alpha1 = RooRealVar("alpha1", "alpha1", 1.6, 0., 3.);
  RooRealVar n1 = RooRealVar("n1", "n1", 10., 3., 200.);
  RooRealVar alpha2 = RooRealVar("alpha2", "alpha2", -1.6, -3., 0.);
  RooRealVar n2 = RooRealVar("n2", "n2", 10., 3., 200.);
  RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);

  RooCBShape *sig1 = new RooCBShape("sig1", "signal CB", mass, mean, sigma, alpha1, n1);
  RooCBShape *sig2 = new RooCBShape("sig2", "signal CB", mass, mean, sigma, alpha2, n2);
  RooAddPdf *sig = new RooAddPdf("sig", "sig", RooArgList(*sig1,*sig2),frac);

  //RooGaussian *sig;
  //sig = new RooGaussian("sigG", "signal gaussian", mass, mean, sigma);

  RooRealVar c = RooRealVar("c", "c", -0.001, -1., 0.);
  RooExponential bkg("expo", "exponential", mass, c);

  std::cout << "Functions are defined" << std::endl;

  RooRealVar *nSig = new RooRealVar("N_{sig}", "number of signal", 0.8*entries, entries*0.0, 1.0*entries); 
  nSig->setError(sqrt(entries));
  RooRealVar *nBkg = new RooRealVar("N_{bkg}", "number of background", 0.2*entries, entries*0.0, 1.00*entries); 
  nBkg->setError(sqrt(entries));

  RooExtendPdf *sig_E = new RooExtendPdf("sig_E","Extended signal PDF",*sig,*nSig);
  RooExtendPdf *bkg_E = new RooExtendPdf("bkg_E","Extended background PDF",bkg,*nBkg);
  RooAddPdf *totalPDF = new RooAddPdf("total", "right sign pdf", RooArgList(*sig_E, *bkg_E));

  std::cout << "Total PDFs defined" << std::endl;
  
  RooPlot *plot = mass.frame(Title("Mass"));
  std::cout << "Plot created" << std::endl;
  data->plotOn(plot);
  std::cout << "data ploted" << std::endl;
  RooFitResult *res;
  std::cout << "Plot created" << std::endl; 

  res = totalPDF->fitTo(*data,RooFit::Extended(true),RooFit::Minos(true),RooFit::NumCPU(4),RooFit::Strategy(2),RooFit::Range("AllRange"),RooFit::Save(true),RooFit::Verbose(false),RooFit::Timer(kTRUE));
  std::cout << "Fit done" << std::endl;
  totalPDF->plotOn(plot,RooFit::LineColor(kBlue),RooFit::Range("AllRange"));
  totalPDF->plotOn(plot,RooFit::Components(*sig),RooFit::LineColor(kGreen),RooFit::Range("AllRange"));
  totalPDF->plotOn(plot,RooFit::Components(bkg),RooFit::LineColor(kRed),RooFit::Range("AllRange"));
  std::cout << "Plots done" << std::endl;

  TCanvas *canvas = new TCanvas("c","c",0,0,800,600);
  plot->Draw();
  canvas->SaveAs("FitToDsMass_Data.pdf");

}


