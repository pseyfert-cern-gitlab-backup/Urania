#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"

#include "OneDimPhaseSpace.hh"
#include "CombinedPhaseSpace.hh"
#include "UniformDensity.hh"
#include "FormulaDensity.hh"
#include "PolynomialDensity.hh"
#include "ParametricPhaseSpace.hh"

/* 
  This is the example of using 2D polynomial fit class. 

  Generate a distribution in the circular phase space x**2+y**2<1
  and use PolynomialDensity class to fit it. 
*/ 

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // First create the 1D phase space for variable x
  OneDimPhaseSpace xphsp("PhspX", -1., 1.); 
  
  // Now create the parametric phase space for (x,y) where limits on variable y are functions of x
  ParametricPhaseSpace phsp("PhspParam", &xphsp, "-sqrt(1-x^2)", "sqrt(1-x^2)", -1., 1.);

  TFile outfile("TwoDimPolyPdf.root", "RECREATE");
  TNtuple ntuple("ntuple", "2D NTuple", "x:y"); 

  // True PDF
  FormulaDensity true_pdf("TruePDF", &phsp, "1.+0.1*x-0.4*x^2-0.8*y^2"); 

  // Generate 10000 toys according to the true PDF
  true_pdf.generate(&ntuple, 50000); 

  PolynomialDensity poly("PolyPDF", &phsp, 4, &ntuple, "x", "y", 100000); 

  TH2F poly_hist("poly", "Polynomial PDF", 200, -1.1, 1.1, 200, -1.1, 1.1); 

  poly.project(&poly_hist); 

  poly_hist.Write();

  outfile.Close(); 

  gStyle->SetOptStat(0);
  
  TCanvas canvas("canvas", "TwoDimPolyPdf", 400, 400); 
  poly_hist.Draw("zcol"); 

  canvas.Print("TwoDimPolyPdf.png"); 

  theApp.Run();

  return 0; 
}
