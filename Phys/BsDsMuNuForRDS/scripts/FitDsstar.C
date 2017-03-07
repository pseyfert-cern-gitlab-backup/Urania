#include "RooChi2Var.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
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

void FitDsstar(int type, int neutral, int energy, int tauVeto){
 
  gSystem->Load("libRooFit");
  using namespace RooFit;
  using namespace RooStats;

  TString d, n, e, v;
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

  if(tauVeto == 0){
    v = "";
  }
  if(tauVeto == 1){
    v = "NoTauVeto";
  }

  //chain = new TFile("../src/histosNeutralReco_"+d+"_All_Veto.root");
  chain = new TFile("../tuples/histosNeutralReco_MC09_MuNu_All_Veto.root");
  //chain = new TFile("../tuples/histosNeutralReco_MC_All_Veto.root");

  //TH1F *h = (TH1F*) chain->Get("DsMuMass"+e+n+"04");
  //if(neutral == 2){
  TString histoName;
  histoName = "DsMuMass"+e+n+"04"+v;
  std::cout << histoName << std::endl;
  TH1F *h = (TH1F*) chain->Get(histoName);
  double entries = h->GetEntries();
  std::cout << "N entries = " << entries << std::endl;

  RooDataHist *data;
  RooRealVar mass("mass", "mass",1950,2600);
  mass.setRange("AllRange",1950,2600);
  if(neutral == 0){
    mass.setRange("AllRange",2040,2300);
  }
  if(neutral == 1){
    mass.setRange("AllRange",2201,2600);
  }
  if(neutral == 2){
    mass.setRange("AllRange",2350,3000);
  }
  data = new RooDataHist("data", "data", mass, h, 1.0);
  
  RooRealVar *mean, *mean3;
  if(neutral == 0){
    mean = new RooRealVar("Mean", "mean", 2112.1, 2109.1, 2115.1, "MeV/c^{2}");
  }
  if(neutral == 1){
    mean = new RooRealVar("Mean", "mean", 2317.7, 2310.7, 2324.7, "MeV/c^{2}");
  }
  if(neutral == 2){
    mean = new RooRealVar("Mean", "mean", 2460.5, 2460.5, 2460.5, "MeV/c^{2}");
  }
  //mean->setConstant();
  RooRealVar sigma = RooRealVar("Sigma", "sigma", 15., 3., 40., "MeV/c^{2}");
  RooRealVar alpha1 = RooRealVar("alpha1", "alpha1", 0.8, 0., 3.);
  RooRealVar n1 = RooRealVar("n1", "n1", 10., 0.2, 50.);
  RooRealVar alpha2 = RooRealVar("alpha2", "alpha2", -0.8, -3.0, 0.);
  RooRealVar n2 = RooRealVar("n2", "n2", 25., 0.2, 100.);
  RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);

  //RooRealVar sigma = RooRealVar("Sigma", "sigma", 10, 10, 10, "MeV/c^{2}");
  //RooRealVar alpha2 = RooRealVar("alpha2", "alpha2", -0.8, -0.8, -0.8);
  //RooRealVar n2 = RooRealVar("n2", "n2", 15., 15., 15.);
  //sigma.setConstant(true);
  //alpha2.setConstant(true);
  //n2.setConstant(true);  
  
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
  //RooCBShape *sig1 = new RooCBShape("sig1", "signal CB", mass, *mean, sigma, alpha1, n1);
  RooCBShape *sig = new RooCBShape("sig2", "signal CB", mass, *mean, sigma, alpha2, n2);
  //RooAddPdf *sig = new RooAddPdf("sig", "sig", RooArgList(*sig1,*sig2),frac);
  //RooGaussian *sig = new RooGaussian("sig", "sig", mass, *mean, sigma);

  RooRealVar c = RooRealVar("c", "c", -0.0001, -1., 0.);
  RooRealVar c2 = RooRealVar("c2", "c2", -0.01, -1., 0.);
  RooRealVar c3 = RooRealVar("c3", "c3", 0.01, -1000., 1000.);
  RooRealVar c4 = RooRealVar("c4", "c4", 0, -2000., 2000.);
  RooRealVar c5 = RooRealVar("c5", "c5", 0.01, -100., 100.);

  // double expo
  RooExponential *bkg = new RooExponential("expo", "exponential 1", mass, c);
  //RooExponential expo2("expo2", "exponential 2", mass, c2);
  //RooAddPdf *bkg = new RooAddPdf("expo", "exponential", RooArgList(expo1,expo2),frac);
  
  // single expo
  //RooPolynomial expo("expo","exponential",mass,RooArgList(c,c2));

  // DESPERATE TEMPATIVE -> GOMPERTZ FUNCTION
  //RooRealVar aGom = RooRealVar("aGom", "aGom", 10., 0., 50);
  //RooRealVar bGom = RooRealVar("bGom", "bGom", -30., -100., 0.);
  //RooRealVar cGom = RooRealVar("cGom", "cGom", -0.01, -1., 0.);  
  //RooGenericPdf bkg("gompertz","aGom*bGom*cGom*exp(bGom*exp(cGom*mass)+cGom*mass)", RooArgList(mass,aGom,bGom,cGom));

  /*
  mean3 = new RooRealVar("Mean3", "mean3", 2000.1, 1950.1, 2100.1, "MeV/c^{2}");
  RooRealVar sigma3 = RooRealVar("Sigma3", "sigma3", 10, 5, 60, "MeV/c^{2}");
  RooRealVar alpha3 = RooRealVar("alpha3", "alpha3", -0.5, -15.0, 0.0);
  RooRealVar n3 = RooRealVar("n3", "n3", 15., 10., 160.);
  RooCBShape bkg("expo", "bkg", mass, *mean3, sigma3, alpha3, n3);
  */

  RooRealVar *thMass;
  if(neutral == 0){
    thMass = new RooRealVar("thMass", "thMass", 2050, 1980, 2150, "MeV/c^{2}");
  }
  if(neutral == 1){
    thMass = new RooRealVar("thMass", "thMass", 2250, 2150, 2400, "MeV/c^{2}");
  }
  if(neutral == 2){
    thMass = new RooRealVar("thMass", "thMass", 2250, 2150, 2400, "MeV/c^{2}");
  }

  std::cout << "here" << std::endl;
  // Error function times exponential
  RooRealVar *thSigma = new RooRealVar("thSigma", "thSigma", 15, 10, 80, "MeV/c^{2}");
  RooFormulaVar *thres = new RooFormulaVar("thres","0.5*(TMath::Erf((mass-thMass)/thSigma)+1)",RooArgList(mass, *thMass, *thSigma));
  //RooEffProd *bkg = new RooEffProd("bkg", "background", *expo, *thres);
  //RooFormulaVar *eff = new RooFormulaVar("eff","exp(bGom*exp(cGom*(mass-thMass))+cGom*(mass))",RooArgList(mass,*thMass,bGom,cGom));
  //RooEffProd bkg("modelEff","model with efficiency",expo,*eff) ;
  //RooRealVar thMass2 = RooRealVar("thMass2", "thMass2", 600.0, 100., 5000.0);
  //RooGenericPdf bkg("modelEff", "exp(bGom*exp(cGom*(mass-thMass))+cGom*(mass-thMass2))", RooArgList(mass,*thMass,thMass2,bGom,cGom));

  //RooRealVar thresM = RooRealVar("thresM", "thresM", 2050, 2000, 2100, "MeV/c^{2}");
  //RooRealVar thresS = RooRealVar("thresS", "thresS", 20, 10, 60, "MeV/c^{2}");
  //RooFormulaVar thres("DsThres", "thresS*(TMath::Erf((thresM-mass)/thresS)+thresM)", RooArgList(thresM,thresS,mass)) ;
  //RooFormulaVar thres("DsThres", "0.5*(TMath::Erf((mass-1)/0.5)+1)", mass) ;

  //RooFormulaVar thresL("thresL", "(thresM-mass)/(thresS)", RooArgList(thresM,mass,thresS)) ;
  //RooFormulaVar thresL("thresL", "(1.0-mass)/(0.5)",mass) ;
  //RooAbsReal *thres = bindFunction("thres", TMath::Erfc, thresL);
  //RooEffProd *bkg = new RooEffProd("bkg", "background", expo, *thres);

  std::cout << "Functions are defined" << std::endl;

  RooRealVar *nSig = new RooRealVar("N_{sig}", "number of signal", 0.40*entries, entries*0.0, 1.0*entries); 
  nSig->setError(sqrt(entries));
  RooRealVar *nBkg = new RooRealVar("N_{bkg}", "number of background", 0.60*entries, entries*0.0, 1.00*entries); 
  nBkg->setError(sqrt(entries));

  RooExtendPdf *sig_E = new RooExtendPdf("sig_E","Extended signal PDF",*sig,*nSig);
  RooExtendPdf *bkg_E = new RooExtendPdf("bkg_E","Extended background PDF",*bkg,*nBkg);
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
  totalPDF->plotOn(plot,RooFit::Components(*bkg),RooFit::LineColor(kRed),RooFit::Range("AllRange"));
  std::cout << "Plots done" << std::endl;

  TCanvas *canvas = new TCanvas("c","c",0,0,800,600);
  plot->Draw();
  canvas->SaveAs("DsMu"+n+"Mass_"+d+"_"+e+"040"+v+".pdf");

  std::cout << "my chi2 is " << plot->chiSquare() << std::endl;
  //RooChi2Var chi2_lowstat("chi2_lowstat","chi2",totalPDF,*data) ;
  //std::cout << "my chi2 is " << chi2_lowstat.getVal() << std::endl ;

}


