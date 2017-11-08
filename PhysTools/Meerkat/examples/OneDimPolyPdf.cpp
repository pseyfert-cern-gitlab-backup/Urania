#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"

#include "OneDimPhaseSpace.hh"
#include "UniformDensity.hh"
#include "PolynomialDensity.hh"

/* 
  Example of 1D polynomial fit. 
  
  Generate a uniform distribution in (-1,1) range 
  and fit it with polynomial of power 8. 
*/ 

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // Define 1D phase space for a variable in range (-1, 1)
  OneDimPhaseSpace phsp("Phsp1D", -1., 1.);

  // Create a uniform PDF over this phase space
  UniformDensity uniform("UniformPDF", &phsp); 

  TFile outfile("OneDimPolyPdf.root", "RECREATE");
  TNtuple ntuple("ntuple", "1D NTuple", "x"); 

  // Generate 10000 toys according to the uniform PDF
  uniform.generate(&ntuple, 100000); 

  PolynomialDensity poly("PolyPDF", &phsp, 8, &ntuple, "x"); 

  TH1F uniform_hist("unform", "PDF", 200, -1.5, 1.5); 
  TH1F poly_hist("poly", "Polynomial PDF", 200, -1.5, 1.5); 

  uniform.project(&uniform_hist); 
  poly.project(&poly_hist); 

  uniform_hist.Write();
  poly_hist.Write();

  outfile.Close(); 

  gStyle->SetOptStat(0);
  
  TCanvas canvas("canvas", "OneDimPolyPdf", 400, 400); 
  uniform_hist.Draw(); 
  poly_hist.Scale( uniform_hist.GetSumOfWeights() / poly_hist.GetSumOfWeights() ); 
  poly_hist.SetLineColor(2); 
  poly_hist.Draw("same"); 

  canvas.Print("OneDimPolyPdf.png"); 

  theApp.Run();

  return 0; 
}
