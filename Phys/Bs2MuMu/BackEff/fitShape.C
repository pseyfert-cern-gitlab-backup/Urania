#include <iostream>
#include <string>
#include <fstream>
#include "TROOT.h"
#include <vector>
#include "TRandom3.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TCut.h"
#include "zstyle.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TPRegexp.h"
#include "TPostScript.h"
#include "TGaxis.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TTreeFormula.h"

#include "Riostream.h"
#include "RooRealVar.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooExtendPdf.h"
#include "TGaxis.h"
#include "RooHist.h"
#include "RooExponential.h"
#include "cutsdefinition.h"
#include "DrawUtils.h"
#include "Measurement.h" 
#include "RooPhysBkg.h"
#include "RooExpAndGauss.h"
#include "RooExpAndGaussInv.h"
#include "RooFitResult.h"
#include "RooChi2Var.h"
#include "RooMinuit.h" 

using namespace std;
using namespace RooFit;
using namespace DrawUtils;

TLatex *   tex            = new TLatex(0.7,0.83,"LHCb");

Bool_t makePaperPlots     = kFALSE;

void setPaperPlotsStyle(RooPlot* f);

TString mass_name = "B_s0_M";
RooRealVar *mass = new RooRealVar(mass_name, "Mass ", 4000, 6000);

RooFitResult fitRooPhysBkg(RooAbsData *ds, TString name, int bin, int suggestion)
{


  RooRealVar *sh_mean =  new RooRealVar("mean","mean", 5200, 4600, 5600);

  RooRealVar *sh_sigma = new RooRealVar("sigma","sigma", 70, 35, 90); //bdpimunu

  RooRealVar *sh_c = new RooRealVar("sh_c", "sh_c", 0.01, 1e-7, 0.1);
  if(suggestion ==1){//bdpimunu
    //    sh_mean->setVal(5150);
    sh_mean->setRange(4300, 5800); //bdpimunu
    sh_sigma->setVal(55);
    sh_sigma->setRange(30, 100); //bdpimunu bin 4
    sh_c->setVal(1e-6);
  }
  if(suggestion ==2){
    sh_sigma->setVal(80); //bskmunu    
    sh_sigma->setRange(40,105); //bskmunu    
    //    sh_mean->setVal(5300);
    sh_c->setVal(1e-6);
    
    
  }
  if(suggestion ==3){//lbpmunu
    sh_sigma->setVal(70); 
    sh_sigma->setRange(40,80); 
    sh_mean->setVal(5300);
    
  }
  if(suggestion ==3){//lbpmunu
    sh_sigma->setVal(70); 
    sh_sigma->setRange(40,80); 
    sh_mean->setVal(5300);
    
  }

  Bool_t B2pimumu           = kFALSE;
  if(suggestion ==4){
    B2pimumu = kTRUE;

    sh_mean->setRange(4200,5500);
    sh_mean->setVal(5360);
    
    sh_sigma->setRange(0,100); 
    sh_sigma->setVal(50);
    
    sh_c->setRange( 0.000001, 0.5);
    sh_c->setVal( 0.001);
    

  }
  
  
    
  RooPhysBkg *phys = 
    new RooPhysBkg("shoulder", "shoulder pdf", *mass, *sh_mean, *sh_c, *sh_sigma);
  //RooGaussian *gau = new RooGaussian("gau","gau", *mass, *sh_mean, *sh_sigma);

  RooRealVar *e_mean = new RooRealVar("e_mean", "e_mean", 5107, 4500.,6000.);
  RooRealVar *e_sigma =  new RooRealVar("e_sigma", "e_sigma", 14., 10.,150.);
  RooRealVar * e_dtrans = new RooRealVar("e_dtrans", "e_dtrans", 2., 0.3, 100);
  RooFormulaVar * e_trans = new RooFormulaVar("e_trans", "e_trans", 
                                              "e_mean - e_dtrans", 
                                              RooArgList(*e_mean, *e_dtrans)) ;
  RooExpAndGauss * shoulder = 
    new RooExpAndGauss("shoulder", "shoulder pdf", *mass,*e_mean, *e_sigma, *e_trans);
  

  
  mass->setRange(4900, 6000);
  RooAbsPdf *model = phys;
  
  
  RooPlot *frame = mass->frame(Title("Mass"));
  
  ds->plotOn(frame,DataError(RooAbsData::SumW2));
  // Tweak for bu2pimumu
  RooFitResult *rf  = B2pimumu ? model->fitTo(*ds,Save(),
                                             RooFit::Minos(kTRUE),RooFit::Range(4900,5250)) :
    model->fitTo(*ds,Save(),RooFit::Hesse(true),
                SumW2Error(false), 
                RooFit::Strategy(2), 
                RooFit::Offset(true),
                Range(4900, 5600));
  
  //  RooFitResult * rf = gau->fitTo(ds,Save(),RooFit::Minos(kTRUE),RooFit::Hesse(true),SumW2Error(true));


  rf->Print();
  
  model->plotOn(frame);
  //gau->plotOn(frame);
  
  TCanvas *canvas =new TCanvas(name, name);

  if(makePaperPlots) setPaperPlotsStyle(frame);
  frame->Draw();
  
  tex->SetTextAlign(13);
  tex->SetTextFont(1);
  makePaperPlots ? tex->SetTextSize(0.045) : tex->SetTextSize(0.03);

  tex->SetLineWidth(2);
  
  if(makePaperPlots) tex->DrawLatex(0.5,0.9,TString::Format("LHCb Simulations  BDT-Bin %i", bin));
  TString drawString  = Form("Mean:    %4.4f  +-  %3.4f", sh_mean->getVal(), sh_mean->getError());
  tex->DrawLatex(0.5, 0.8, drawString);
  drawString          = Form("Sigma:   %4.4f  +-  %3.4f", sh_sigma->getVal(), sh_sigma->getError());
  tex->DrawLatex(0.5, 0.7, drawString);
  drawString          = Form("C:       %4.4f  +-  %3.4f", sh_c->getVal(), sh_c->getError());
  tex->DrawLatex(0.5, 0.6, drawString);



  TString saveName = makePaperPlots ? "plots/"+name+"_paper.pdf" : "plots/"+name+".pdf";
  canvas->SaveAs(saveName);

  return *rf;
  
}

void makeSummary(TString prefix)
{
  Info("makeSummary", "Starting to write the outputs, prefix =  %s", prefix.Data());
  RooFitResult *r[9];
  const int nbins =8;
  
  cout << " going to write on file " << endl;
  ofstream out("summary/"+prefix+"_RPB_params.txt");
  ofstream outPy("summary/"+prefix+"_RPB_params.py");
  for(int ii =1; ii<=nbins; ii++){
    TString name = prefix+"_RPB_bin";
    name += ii;
    TFile f("root/"+name+".root");
    r[ii-1] = (RooFitResult*)f.Get("fitresult_shoulder_ds");
    
    const RooArgList pr = r[ii-1]->floatParsFinal();
    RooRealVar *mean = (RooRealVar*)pr.at(0);
    out << mean->getValV() << " \t " << mean->getError() << " \t # Mean for bin " << ii << endl;
    outPy << "Mean" <<ii<< " = EVal("<< mean->getValV() << " , " << mean->getError() << ") \t # Mean for bin " << ii << endl;
    RooRealVar *shc = (RooRealVar*)pr.at(1);
    out << shc->getValV() << " \t " << shc->getError() <<  " \t # Shc for bin " << ii << endl;
    outPy << "Shc" <<ii<< " = EVal("<< shc->getValV() << " , " << shc->getError() << ") \t # Shc for bin " << ii << endl;
    RooRealVar *sigma = (RooRealVar*)pr.at(2);
    out << sigma->getValV() << " \t " << sigma->getError() <<  " \t # Sigma for bin " << ii << endl;
    outPy << "Sigma" <<ii<< " = EVal("<< sigma->getValV() << " , " << sigma->getError() << ") \t # Sigma for bin " << ii << endl;
  }
  int ii =78;
  TString name = prefix+"_RPB_bin";
  name += ii;
  TFile f("root/"+name+".root");
  r[8] = (RooFitResult*)f.Get("fitresult_shoulder_ds");
  const RooArgList pr = r[8]->floatParsFinal();
  RooRealVar *mean = (RooRealVar*)pr.at(0);
  out << mean->getValV() << " \t " << mean->getError() << " \t # Mean for bin " << ii << endl;
  outPy << "Mean" <<ii<< " = EVal("<< mean->getValV() << " , " << mean->getError() << ") \t # Mean for bin " << ii << endl;
  RooRealVar *shc = (RooRealVar*)pr.at(1);
  out << shc->getValV() << " \t " << shc->getError() <<  " \t # Shc for bin " << ii << endl;
  outPy << "Shc" <<ii<< " = EVal("<< shc->getValV() << " , " << shc->getError() << ") \t # Shc for bin " << ii << endl;
  RooRealVar *sigma = (RooRealVar*)pr.at(2);
  out << sigma->getValV() << " \t " << sigma->getError() <<  " \t # Sigma for bin " << ii << endl;
  outPy << "Sigma" <<ii<< " = EVal("<< sigma->getValV() << " , " << sigma->getError() << ") \t # Sigma for bin " << ii << endl;
  
}


void help(){
  cout << endl << " ------ fitshape ------- " << endl;
  cout << "   Fitter for mass shapes of partially reconstructed backgrounds for BsMuMu analysis  " << endl;
  cout << endl;
  cout << " -h             \t Shows this help " << endl;
  cout << " -f [fileName]  \t Analyse given input file " << endl;
  cout << " -s [number]    \t Get suggestion for fitting parameters (see below) " << endl;
  cout << " -b             \t Runs in batch   " << endl;
  cout << " -d             \t Debug mode on   " << endl;
  cout << endl;
  cout << " Suggestions    " << endl;
  cout << " 1             \t Bd-> pi mu nu   " << endl;
  cout << " 2             \t Bs-> K mu nu   " << endl;
  cout << " 3             \t Lb-> p mu nu   " << endl;
  cout << " 4             \t B-> pi mu mu   " << endl;
  cout << "............................................................" << endl;
  
}




//============================================================
// MAIN
//============================================================
int main(int argc, char **argv){

  zstyle();
  TH1::SetDefaultSumw2();
  cout << " Start " << endl;
  TString filename;
  int mybin=-1;
  int suggestion =0;
  
  for(Int_t i=1; i<argc; i++){
    TString opt(argv[i]);
    cout << " Parsing option: " << opt << endl;
    if(opt.Contains("-h")){
      help();
      return 0;
    }else if(opt == "-b"){
      Info("...","Running in batch" );
      //batchrunning =true;
      // Note: option will be parsed by TApplication later 
    }else if(opt.Contains("-d")){
      Info("...","DEBUG mode on" );
      //DEBUG =true;
    }else if(opt.Contains("-f")){
      i++;
      TString val(argv[i]);
      filename = val; 
    }else if(opt == "-bin"){
      i++;
      TString val(argv[i]);
      mybin = val.Atoi();
      cout << " going to run only on bin " << mybin << endl;
      
    }else if(opt == "-s") // Suggestion for fit parameters
    {
      i++;
      TString val(argv[i]);
      suggestion = val.Atoi();
      cout << " going to use suggestion " << suggestion << endl;
      
      
    }

    
  }
  
  if(filename==""){
    Error("Configuration","No file name given");
    return -1;
  }
  TApplication theApp("App", &argc, argv);


  // Stuff for writing on plots 
  tex->SetNDC();
  tex->SetTextAlign(12);
  tex->SetTextFont(132);
  tex->SetTextSize(0.08);
  tex->SetLineWidth(2);

  TFile f(filename);
  
  bool binned = !filename.Contains("_ds_");
  Info("", (binned)? "Doing a binned fit ": "Doing an unbinned fit");
  
  const int nbins = 8;
      
  TString prefix = filename;
  prefix.ReplaceAll("root/","");
  prefix.ReplaceAll(".root","");
  int minbin =1;
  int maxbin =nbins;
  if(mybin!=-1)
  {
    
    minbin =mybin;
    maxbin =mybin;
  }
  
  RooFitResult *r[9];
  if(binned)
  {    
    TH2D *MvsBdt = (TH2D*)f.Get("MassFit");  

    for(int ii =minbin; ii<=maxbin; ii++)
    {
      
      TH1D *h           = MvsBdt->ProjectionX(Form("proj_bin_%i",ii),ii,ii);
      TString name = prefix+"_RPB_bin";
      name += ii;
      RooDataHist *ds = new RooDataHist("ds","ds", *mass, Import(*h));
      r[ii-1] = new RooFitResult(fitRooPhysBkg(ds, name,ii, suggestion));
      r[ii-1]->SaveAs("root/"+name+".root");
    }
    int ii =78;
    TH1D *h           = MvsBdt->ProjectionX(Form("proj_bin_%i",ii),7,8);
    TString name = prefix+"_RPB_bin";
    name += ii;
    RooDataHist *ds = new RooDataHist("ds","ds", *mass, Import(*h));
    r[ii-1] = new RooFitResult(fitRooPhysBkg(ds, name,ii, suggestion));
    r[ii-1]->SaveAs("root/"+name+".root");

      
  }else
  {

    Double_t bins[nbins+1] = {0,0.25, 0.4, 0.5, 0.6, 0.7,  0.8, 0.9, 1.0   };
    
    RooDataSet * ds = (RooDataSet*)f.Get("ds");
    if(!ds)    {
      Error("", "No dataset found");
      return -1;
    }
    
    for(int ii=minbin; ii<=maxbin; ii++)
    {
      TString cut = Form("BDT > %f  &&  BDT <= %f", bins[ii-1], bins[ii]);
      RooDataSet *data = (RooDataSet*)ds->reduce(Cut(cut.Data()));
      TString name = prefix+"_RPB_bin";
      name += ii;
      r[ii-1] = new RooFitResult(fitRooPhysBkg(data, name,ii, suggestion));
      r[ii-1]->SaveAs("root/"+name+".root");
      
    }
    if(mybin == -1 || mybin == 78)
    {
      // hack to do also the 7+8
      TString cut = Form("BDT > %f  &&  BDT <= %f", bins[nbins-2], bins[nbins]);
      RooDataSet *data = (RooDataSet*)ds->reduce(Cut(cut.Data()));
      TString name = prefix+"_RPB_bin";
      name += "78";
      r[8] = new RooFitResult(fitRooPhysBkg(data, name,78, suggestion));
      r[8]->SaveAs("root/"+name+".root");
    }
  }
  
  makeSummary(prefix);
  
  
  

  cout << "... this is the end"<< endl;
  theApp.Run();
  return 0;

}
void setPaperPlotsStyle(RooPlot* f){
  f->getCurve()->SetLineWidth(3);
  f->getCurve()->SetLineColor(kRed);
  f->GetXaxis()->SetTitle("m( #mu^{+} #mu^{-} ) [MeV]");
  f->GetXaxis()->SetTitleSize(0.065);
  f->GetXaxis()->SetTitleOffset(1.05);
  f->GetXaxis()->SetLabelSize(0.065);
  f->GetXaxis()->SetNoExponent();
  f->GetYaxis()->SetTitle("# candidates / 50 MeV");
  f->GetYaxis()->SetTitleSize(0.065);
  f->GetYaxis()->SetTitleOffset(1.05);
  f->GetYaxis()->SetLabelSize(0.065);
};

