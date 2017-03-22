#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TRandom3.h"

#include "OneDimPhaseSpace.hh"
#include "BinnedKernelDensity.hh"

/* 
  This example demonstrates the use of weighted ntuple. 

  Generate a uniform distribution of variable x in the range (-1,1) 
  with the weight which is a function of x, 
  and apply a Meerkat procedure to estimate PDF from it. 

  The application creates the ROOT file with the generated ntuple, 
  true and estimated distributions. 
*/ 

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // Define 1D phase space for a variable in range (-1, 1)
  OneDimPhaseSpace phsp("Phsp1D", -1., 1.);

  TFile outfile("WeightedTuple.root", "RECREATE");
  TNtuple ntuple("ntuple", "1D NTuple with weight", "x:w"); 
  
  // Generate 10000 toys according to the uniform PDF
  // and weight
  TH1F uniform_hist("unform", "PDF", 200, -1.5, 1.5); 
  TRandom3 rnd;
  for (Int_t i=0; i<10000; i++) {
    Double_t x = rnd.Rndm()*2.-1.;
    Double_t w = x*x; 
    ntuple.Fill(x, w); 
    uniform_hist.Fill(x, w); 
  }
  ntuple.Write(); 

  // Create kernel PDF from the generated sample
  // If the number of variables passed to the constructor is larger by 1 than the phase 
  // space dimensionality, the last variables is considered as the weight
  BinnedKernelDensity kde("KernelPDF", 
                          &phsp, 
                          &ntuple, // Input ntuple
                          "x",     // Variable to use
                          "w",     // Weight variable
                          1000,    // Number of bins
                          0.1,     // Kernel width
                          0,       // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Write binned PDF into a file
  kde.writeToFile("WeightedTuple_bins.root"); 

  // That's it. Now fill some control histograms and plot them. 
  TH1F kernel_hist("kernel", "Kernel PDF", 200, -1.5, 1.5); 

  kde.project(&kernel_hist); 

  uniform_hist.Write();
  kernel_hist.Write();

  gStyle->SetOptStat(0);
  
  TCanvas canvas("canvas", "WeightedTuple", 400, 400); 
  uniform_hist.Draw(); 
  kernel_hist.Scale( uniform_hist.GetSumOfWeights() / kernel_hist.GetSumOfWeights() ); 
  kernel_hist.SetLineColor(2); 
  kernel_hist.Draw("same"); 

  canvas.Print("WeightedTuple.png"); 

  theApp.Run();

  outfile.Close(); 

  return 0; 
}
