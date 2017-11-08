#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TText.h"

#include "OneDimPhaseSpace.hh"
#include "FormulaDensity.hh"
#include "BinnedDensity.hh"
#include "BinnedKernelDensity.hh"
#include "AdaptiveKernelDensity.hh"

/* 
  This is an example of using adaptive kernel class for estimation of 1D PDF 
  with a narrow peak. 
  
  It also uses FormulaDensity to describe the true PDF in a parametrised way. 
*/

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // Define 1D phase space for a variable in range (-1, 1)
  OneDimPhaseSpace phsp("Phsp1D", -1., 1.);

  // Create a "true" PDF over this phase space in a parametrised way
  FormulaDensity formula("FormulaPDF", &phsp, "(1. + 4.*exp(-x*x/2/0.1/0.1))*( abs(x)<1 )"); 

  TFile outfile("OneDimAdaptiveKernel.root", "RECREATE");
  TNtuple ntuple("ntuple", "1D NTuple", "x"); 

  // Generate toys according to the "true" PDF
  formula.generate(&ntuple, 10000); 
  
  // Create kernel PDF from the generate sample
  BinnedKernelDensity kde("KernelPDF", 
                          &phsp,   // Phase space
                          &ntuple, // Input ntuple
                          "x",     // Variable to use
                          1000,    // Number of bins
                          0.1,     // Kernel width
                          0,       // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Create binned PDF from the kernel PDF. 
  // In principle, kernel PDF is already binned, but the trick here is 
  // that BinnedDensity will be normalized to have the average PDF value equal to 1. 
  // This is needed for AdaptiveKernelDensity
  BinnedDensity kde_binned("BinnedPDF", &phsp, &kde, 1000); 

  // Create adaptive kernel PDF with the kernel width depending on the binned PDF 
  AdaptiveKernelDensity kde_adaptive("AdaptivePDF", 
                          &phsp,       // Phase space
                          &ntuple,     // Input ntuple
                          "x",         // Variable to use
                          1000,        // Number of bins
                          0.1,         // Initial kernel width
                          &kde_binned, // PDF for width scaling
                          0,           // Approximation PDF (0 for flat approximation)
                          100000       // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Write binned PDF into a file
  kde_adaptive.writeToFile("OneDimAdaptiveKernel_bins.root"); 
  
  TH1F true_hist("true_pdf", "PDF", 200, -1.1, 1.1); 
  TH1F kernel_hist("kernel_pdf", "Kernel PDF", 200, -1.1, 1.1); 
  TH1F adaptive_hist("adaptive_pdf", "Adaptive kernel PDF", 200, -1.1, 1.1); 

  TH1F kernel_diff("kernel_diff", "PDF bias", 200, -1.1, 1.1); 
  TH1F adaptive_diff("adaptive_diff", "PDF bias", 200, -1.1, 1.1); 

  std::vector<Double_t> x(1); 

  // Fill histogram with true PDF
  formula.slice(x, 0, &true_hist); 
  true_hist.Write();

  // Fill histogram with the result of kernel density estimation
  kde.slice(x, 0, &kernel_hist); 
  kernel_hist.Write();

  kde_adaptive.slice(x, 0, &adaptive_hist); 
  adaptive_hist.Write();

  gStyle->SetOptStat(0); 
  
  TCanvas canvas("canvas", "OneDimAdaptiveKernel", 400, 600); 
  canvas.Divide(1, 2);
  canvas.cd(1); 
  true_hist.SetLineColor(1); 
  true_hist.Draw(); 
  kernel_hist.Scale( true_hist.GetSumOfWeights() / kernel_hist.GetSumOfWeights() ); 
  kernel_hist.SetLineColor(2); 
  kernel_hist.Draw("same"); 
  adaptive_hist.Scale( true_hist.GetSumOfWeights() / adaptive_hist.GetSumOfWeights() ); 
  adaptive_hist.SetLineColor(4); 
  adaptive_hist.Draw("same"); 

  TText t;
  t.SetTextSize(0.04); 
  t.SetTextColor(1); 
  t.DrawText(0.2, 4.5, "True PDF"); 
  t.SetTextColor(2); 
  t.DrawText(0.2, 4.2, "Fixed kernel PDF"); 
  t.SetTextColor(4); 
  t.DrawText(0.2, 3.9, "Adaptive kernel PDF"); 

  kernel_diff.Add(&kernel_hist, &true_hist, 1., -1.);
  adaptive_diff.Add(&adaptive_hist, &true_hist, 1., -1.);
  canvas.cd(2); 
  kernel_diff.SetMinimum(-1.); 
  kernel_diff.SetMaximum( 1.); 
  kernel_diff.SetLineColor(2); 
  kernel_diff.Draw(); 
  adaptive_diff.SetLineColor(4); 
  adaptive_diff.Draw("same"); 

  t.SetTextColor(2); 
  t.DrawText(0.2, 0.8, "Fixed kernel PDF"); 
  t.SetTextColor(4); 
  t.DrawText(0.2, 0.6, "Adaptive kernel PDF"); 

  canvas.Print("OneDimAdaptiveKernel.png"); 

  theApp.Run();

  outfile.Close(); 
  
  return 0; 
}
