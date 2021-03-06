#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"

#include "OneDimPhaseSpace.hh"
#include "UniformDensity.hh"
#include "BinnedKernelDensity.hh"

/* 
  This is the simplest possible example of using Meerkat package. 

  Generate a uniform distribution in the range (-1,1)
  and apply a Meerkat procedure to estimate PDF from it. 

  The application creates the ROOT file with the generated ntuple, 
  true and estimated distributions. 
*/ 

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // Define 1D phase space for a variable in range (-1, 1)
  OneDimPhaseSpace phsp("Phsp1D", -1., 1.);

  // Create a uniform PDF over this phase space
  UniformDensity uniform("UniformPDF", &phsp); 

  TFile outfile("OneDimPdf.root", "RECREATE");
  TNtuple ntuple("ntuple", "1D NTuple", "x"); 

  // Generate 10000 toys according to the uniform PDF
  uniform.generate(&ntuple, 10000); 

  // Create kernel PDF from the generate sample
  BinnedKernelDensity kde("KernelPDF", 
                          &phsp, 
                          &ntuple, // Input ntuple
                          "x",     // Variable to use
                          1000,    // Number of bins
                          0.2,     // Kernel width
                          0,       // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Write binned PDF into a file
  kde.writeToFile("OneDimPdf_bins.root"); 
  
  TH1F uniform_hist("unform", "PDF", 200, -1.5, 1.5); 
  TH1F kernel_hist("kernel", "Kernel PDF", 200, -1.5, 1.5); 

  std::vector<Double_t> x(1); 

  uniform.slice(x, 0, &uniform_hist); 
  kde.slice(x, 0, &kernel_hist); 

  uniform_hist.Write();
  kernel_hist.Write();

  outfile.Close(); 

  gStyle->SetOptStat(0);
  
  TCanvas canvas("canvas", "OneDimPdf", 400, 400); 
  uniform_hist.Draw(); 
  kernel_hist.Scale( uniform_hist.GetSumOfWeights() / kernel_hist.GetSumOfWeights() ); 
  kernel_hist.SetLineColor(2); 
  kernel_hist.Draw("same"); 

  canvas.Print("OneDimPdf.png"); 

  theApp.Run();

  return 0; 
}
