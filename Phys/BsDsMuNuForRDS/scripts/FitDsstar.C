#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooChebychev.h"
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

void FitDsstar(int type, int neutral, int energy){
 
  gSystem->Load("libRooFit");
  using namespace RooFit;
  using namespace RooStats;

  TString d, n, e;
  if(type == 0){
    d = "MC";
  }
  if(type == 1){
    d = "Data"; 
  }

  if(neutral == 0){
    n = "G";
  }
  if(neutral == 1){
    n = "Pi0";
  }
  if(neutral == 2){
    n = "Pi0G";
  }

  if(energy == 0){
    e = "First";
  }
  if(energy == 1){
    e = "Second";
  }

  chain = new TFile("../src/histosNeutralReco_"+d+"_All.root");

  TH1F *h = (TH1F*) chain->Get("DsMuMass"+e+n+"04");
  double entries = h->GetEntries();

  RooDataHist *data;
  RooRealVar mass("mass", "mass",1950,2600);
  mass.setRange("AllRange",1950,2600);
  data = new RooDataHist("data1", "data0", mass, h, 1.0);
  
  RooRealVar *mean;
  if(neutral == 0){
    mean = new RooRealVar("Mean", "mean", 2112.1, 2109.1, 2115.1, "MeV/c^{2}");
  }
  if(neutral == 1){
    mean = new RooRealVar("Mean", "mean", 2317.7, 2310.7, 2324.7, "MeV/c^{2}");
  }
  RooRealVar sigma = RooRealVar("Sigma", "sigma", 10, 5, 60, "MeV/c^{2}");
  RooRealVar alpha1 = RooRealVar("alpha1", "alpha1", 1.6, 0., 3.);
  RooRealVar n1 = RooRealVar("n1", "n1", 7., 1., 20.);
  RooRealVar alpha2 = RooRealVar("alpha2", "alpha2", -0.8, -15.0, 0.0);
  RooRealVar n2 = RooRealVar("n2", "n2", 15., 1., 60.);
  RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);
/* 
  RooRealVar mean = RooRealVar("Mean", "mean", 2316.5, 2316.5, 2316.5, "MeV/c^{2}");
  RooRealVar sigma = RooRealVar("Sigma", "sigma", 18.6, 18.6, 18.6, "MeV/c^{2}");
  RooRealVar alpha2 = RooRealVar("alpha2", "alpha2", -1.12, -1.12, -1.12);
  RooRealVar n2 = RooRealVar("n2", "n2", 3.07, 3.07, 3.07);
  mean.setConstant(true);
  sigma.setConstant(true);
  alpha2.setConstant(true);
  n2.setConstant(true);
*/
  //RooCBShape *sig1 = new RooCBShape("sig1", "signal CB", mass, mean, sigma, alpha1, n1);
  RooCBShape *sig = new RooCBShape("sig2", "signal CB", mass, *mean, sigma, alpha2, n2);
  //RooAddPdf *sig = new RooAddPdf("sig", "sig", RooArgList(*sig1,*sig2),frac);
  //RooGaussian *sig = new RooGaussian("sig", "sig", mass, mean, sigma);

  RooRealVar c = RooRealVar("c", "c", -0.01, -1., 0.);
  //RooRealVar c2 = RooRealVar("c2", "c2", -0.01, -10., 10.);
  //RooRealVar c3 = RooRealVar("c3", "c3", 0.1, -10., 10.);
  RooExponential expo("expo", "exponential", mass, c);
  //RooChebychev expo("expo","exponential",mass,RooArgList(c,c2,c3));

  RooRealVar *thMass;
  if(neutral == 0){
    thMass = new RooRealVar("thMass", "thMass", 2000, 1950, 2050, "MeV/c^{2}");
  }
  if(neutral == 1){
    thMass = new RooRealVar("thMass", "thMass", 2250, 2150, 2400, "MeV/c^{2}");
  }
  RooRealVar thSigma = RooRealVar("thSigma", "thSigma", 80, 10, 120, "MeV/c^{2}");
  RooFormulaVar eff("eff","0.5*(TMath::Erf((mass-thMass)/thSigma)+1)",RooArgList(mass,*thMass,thSigma)) ;
  RooEffProd bkg("modelEff","model with efficiency",expo,eff) ;

  //RooRealVar thresM = RooRealVar("thresM", "thresM", 2050, 2000, 2100, "MeV/c^{2}");
  //RooRealVar thresS = RooRealVar("thresS", "thresS", 20, 10, 60, "MeV/c^{2}");
  //RooFormulaVar thres("DsThres", "thresS*(TMath::Erf((thresM-mass)/thresS)+thresM)", RooArgList(thresM,thresS,mass)) ;
  //RooFormulaVar thres("DsThres", "0.5*(TMath::Erf((mass-1)/0.5)+1)", mass) ;

  //RooFormulaVar thresL("thresL", "(thresM-mass)/(thresS)", RooArgList(thresM,mass,thresS)) ;
  //RooFormulaVar thresL("thresL", "(1.0-mass)/(0.5)",mass) ;
  //RooAbsReal *thres = bindFunction("thres", TMath::Erfc, thresL);
  //RooEffProd *bkg = new RooEffProd("bkg", "background", expo, *thres);

  std::cout << "Functions are defined" << std::endl;

  RooRealVar *nSig = new RooRealVar("N_{sig}", "number of signal", 0.35*entries, entries*0.0, 1.0*entries); 
  nSig->setError(sqrt(entries));
  RooRealVar *nBkg = new RooRealVar("N_{bkg}", "number of background", 0.65*entries, entries*0.0, 1.00*entries); 
  nBkg->setError(sqrt(entries));

  RooExtendPdf *sig_E = new RooExtendPdf("sig_E","Extended signal PDF",*sig,*nSig);
  RooExtendPdf *bkg_E = new RooExtendPdf("bkg_E","Extended background PDF",bkg,*nBkg);
  RooAddPdf *totalPDF = new RooAddPdf("total", "right sign pdf", RooArgList(*sig_E,*bkg_E));
  //RooAddPdf *totalPDF = new RooAddPdf("total", "right sign pdf", RooArgList(*bkg_E));

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
  canvas->SaveAs("Ds"+n+"Mass_"+d+"_"+e+"040.pdf");

}


