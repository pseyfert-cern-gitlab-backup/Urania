#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TStyle.h"

#include "OneDimPhaseSpace.hh"
#include "ParametricPhaseSpace.hh"
#include "FormulaDensity.hh"
#include "BinnedDensity.hh"
#include "BinnedKernelDensity.hh"
#include "AdaptiveKernelDensity.hh"

/* 
  An example of using 2D parametric phase space class. 
*/  

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // First create the 1D phase space for variable x
  OneDimPhaseSpace xphsp("PhspX", -1., 1.); 
  
  // Now create the parametric phase space for (x,y) where limits on variable y are functions of x
  ParametricPhaseSpace phsp("PhspParam", &xphsp, "-sqrt(1-x^2)", "sqrt(1-x^2)", -1., 1.);

  // Create a uniform PDF over this phase space
  // Sum of a polynomial shape and a Gaussian peak with correlation between x and y
  FormulaDensity truepdf("TruePDF", &phsp, "1.-0.8*x^2-0.8*y^2+exp(-(x-y)^2/2./(0.4)^2-(x+y)^2/2./(0.8)^2)"); 

  // Create an approximation PDF over this phase space
  // Just a polymonial shape. It will mostly be used to approximate the PDF 
  // at the edges of the phase space.
  FormulaDensity approxpdf("TruePDF", &phsp, "1.-0.8*x^2-0.8*y^2"); 

  TFile outfile("ParamPhsp.root", "RECREATE");
  TNtuple ntuple("ntuple", "2D NTuple", "x:y"); 

  // Generate 50000 toys according to the "true" PDF
  truepdf.generate(&ntuple, 50000); 

  // Create kernel PDF from the generated sample. Use polynomial shape as an approximation PDF 
  BinnedKernelDensity kde("KernelPDF", 
                          &phsp,     // Phase space
                          &ntuple,   // Input ntuple
                          "x","y",   // Variables to use
                          200,200,   // Numbers of bins
                          0.2, 0.2,  // Kernel widths
                          &approxpdf,// Approximation PDF (0 for flat approximation)
                          100000     // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Write binned PDF into a file
  kde.writeToFile("ParamPhsp_bins.root"); 
  
  // That's it. Now fill some histograms and show the results. 

  TH2F true_hist("true", "True PDF", 100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                     100, phsp.lowerLimit(1), phsp.upperLimit(1)); 
  TH2F kernel_hist("kernel", "Kernel PDF", 100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                           100, phsp.lowerLimit(1), phsp.upperLimit(1)); 

  TH1F true_kpi("true_kpi", "X slice", 100, phsp.lowerLimit(0), phsp.upperLimit(0) ); 
  TH1F kernel_kpi("kernel_kpi", "X slice", 100, phsp.lowerLimit(0), phsp.upperLimit(0) ); 
  TH1F true_pipi("true_pipi", "Y slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) ); 
  TH1F kernel_pipi("kernel_pipi", "Y slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) ); 

  // Coordinates in the phase space where we will create the 1D slices.
  std::vector<Double_t> v(2); 
  v[0] = 0.;
  v[1] = 0.;

  // Fill histogram with the result of kernel density estimation
  // In this particular case, since we are plotting a 2D slice of a 2D distribution, 
  // the value of "v" is ignored. 
  truepdf.slice(v, 0, 1, &true_hist); 
  true_hist.Write();
  kde.slice(v, 0, 1, &kernel_hist); 
  kernel_hist.Write();

  // Fill 1D slice in x projection, at the point y=v[1]
  truepdf.slice(v, 0, &true_kpi); 
  true_kpi.Write(); 
  kde.slice(v, 0, &kernel_kpi); 
  kernel_kpi.Write(); 

  // Fill 1D slice in y projection, at the point x=v[0]
  truepdf.slice(v, 1, &true_pipi); 
  true_pipi.Write(); 
  kde.slice(v, 1, &kernel_pipi); 
  kernel_pipi.Write(); 

  // Plot 2D and 1D histograms

  gStyle->SetOptStat(0);
  
  TCanvas canvas("canvas", "ParamPhsp", 500, 500); 
  canvas.Divide(2,2); 

  canvas.cd(1); 
  true_hist.Draw("zcol"); 
//  ntuple.Draw("y:x", "", "same"); 
  canvas.cd(2);
  kernel_hist.Scale( true_hist.GetSumOfWeights() / kernel_hist.GetSumOfWeights() ); 
  kernel_hist.Draw("zcol"); 
  canvas.cd(3); 
  kernel_kpi.Scale( true_kpi.GetSumOfWeights() / kernel_kpi.GetSumOfWeights() ); 
  true_kpi.Draw(); 
  kernel_kpi.SetLineColor(2); 
  kernel_kpi.Draw("same"); 
  canvas.cd(4); 
  kernel_pipi.Scale( true_pipi.GetSumOfWeights() / kernel_pipi.GetSumOfWeights() ); 
  true_pipi.Draw(); 
  kernel_pipi.SetLineColor(2); 
  kernel_pipi.Draw("same"); 

  canvas.Print("ParamPhsp.png"); 

  theApp.Run();

  outfile.Close(); 

  return 0; 
}
