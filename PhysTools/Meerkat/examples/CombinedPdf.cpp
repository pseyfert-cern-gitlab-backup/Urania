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
#include "CombinedPhaseSpace.hh"
#include "BinnedKernelDensity.hh"
#include "FactorisedDensity.hh"
#include "FormulaDensity.hh"

/* 
   This example demonstrated the use of combined phase spaces and factorised density. 
   Here we create a 2D phase space for two variables in range (-1,1), and estimate 
   the density which has a slight correlation between the two variables. 

   We compare three approaches to estimate the true PDF: 
     * Factorised PDF, which is simply a product of kernel PDFs in each variable
     * Kernel PDF with the flat approximation
     * Kernel PDF with factorised approximation. 
   The latter gives better results at the edges of the phase space. 
*/ 

int main(int argc, char** argv) {

  TApplication theApp("App", &argc, argv);

  // Define 1D phase spaces for each of the two variables
  OneDimPhaseSpace phsp_x("PhspX", -1., 1.);
  OneDimPhaseSpace phsp_y("PhspY", -1., 1.);

  // Define combined phase space for the two variables (AKA direct product)
  CombinedPhaseSpace phsp("PhspCombined", &phsp_x, &phsp_y); 

  TFile* outfile = new TFile("CombinedPdf.root", "RECREATE");
  TNtuple* ntuple = new TNtuple("ntuple", "2D NTuple", "x:y"); 

  FormulaDensity truepdf("TruePDF", &phsp, "1.-0.05*(x+y)^4-0.2*(x-y)^2");

  truepdf.generate(ntuple, 50000);

  // Create kernel PDF from the generated sample for projection to variable x
  BinnedKernelDensity kde_x("KernelPDF_X",
                          &phsp_x, // Phase space
                          ntuple, // Input ntuple
                          "x",     // Variables to use
                          200,     // Numbers of bins
                          0.2,     // Kernel width
                          0,       // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Create kernel PDF from the generated sample for projection to variable y
  BinnedKernelDensity kde_y("KernelPDF_Y",
                          &phsp_y, // Phase space
                          ntuple, // Input ntuple
                          "y",     // Variables to use
                          200,     // Numbers of bins
                          0.2,     // Kernel width
                          0,       // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Create factorised PDF which is the product of PDFs in x and y
  FactorisedDensity fact("FactPDF", &phsp, &kde_x, &kde_y);

  // Create kernel PDF from the generated sample, using flat approximation
  BinnedKernelDensity kde("KernelPDF",
                          &phsp,   // Phase space
                          ntuple, // Input ntuple
                          "x","y", // Variables to use
                          100,100, // Numbers of bins
                          0.4, 0.4,// Kernel widths
                          0,       // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         ); 

  // Create kernel PDF from the generated sample, using factorised PDF as approximation
  BinnedKernelDensity kde_factappr("KernelPDFWithFactApprox",
                          &phsp,   // Phase space
                          ntuple, // Input ntuple
                          "x","y", // Variables to use
                          100,100, // Numbers of bins
                          0.4, 0.4,// Kernel widths
                          &fact,   // Approximation PDF (0 for flat approximation)
                          100000   // Sample size for MC convolution (0 for binned convolution)
                         );

  // That's it. Now fill some histograms and show the results. 

  TH2F* true_hist = new TH2F("true", "True PDF", 100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                     100, phsp.lowerLimit(1), phsp.upperLimit(1)); 
  TH2F* fact_hist = new TH2F("fact", "Factorised PDF", 100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                           100, phsp.lowerLimit(1), phsp.upperLimit(1)); 
  TH2F* kernel_hist = new TH2F("kernel", "Kernel PDF with flat approximation", 
                                           100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                           100, phsp.lowerLimit(1), phsp.upperLimit(1)); 
  TH2F* kernel_factappr_hist = new TH2F("kernel_fa", "Kernel PDF with factorised approximation", 
                                           100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                           100, phsp.lowerLimit(1), phsp.upperLimit(1)); 

  std::vector<Double_t> v(2); 

  truepdf.slice(v, 0, 1, true_hist); 
  true_hist->Write();

  // Fill histogram with the result of kernel density estimation
  // In this particular case, since we are plotting a 2D slice of a 2D distribution, 
  // the value of "v" is ignored. 
  kde.slice(v, 0, 1, kernel_hist); 
  kernel_hist->Write();

  kde_factappr.slice(v, 0, 1, kernel_factappr_hist); 
  kernel_factappr_hist->Write();

  fact.slice(v, 0, 1, fact_hist); 
  fact_hist->Write();

  gStyle->SetOptStat(0);
  
  TCanvas canvas("canvas", "CombinedPdf", 500, 500); 
  canvas.Divide(2,2); 

  canvas.cd(1); 
  true_hist->SetMaximum(1.1); 
  true_hist->SetMinimum(0.0); 
  true_hist->Draw("zcol"); 
//  ntuple->Draw("y:x", "", "same"); 
  canvas.cd(2);
  fact_hist->Scale( true_hist->GetSumOfWeights() / fact_hist->GetSumOfWeights() ); 
  fact_hist->SetMaximum(1.1); 
  fact_hist->SetMinimum(0.0); 
  fact_hist->Draw("zcol"); 
  canvas.cd(3); 
  kernel_hist->Scale( true_hist->GetSumOfWeights() / kernel_hist->GetSumOfWeights() ); 
  kernel_hist->SetMaximum(1.1); 
  kernel_hist->SetMinimum(0.0); 
  kernel_hist->Draw("zcol"); 
  canvas.cd(4); 
  kernel_factappr_hist->Scale( true_hist->GetSumOfWeights() / kernel_factappr_hist->GetSumOfWeights() ); 
  kernel_factappr_hist->SetMaximum(1.1); 
  kernel_factappr_hist->SetMinimum(0.0); 
  kernel_factappr_hist->Draw("zcol");

  canvas.Print("CombinedPdf.png"); 

  theApp.Run();

  outfile->Close(); 

  return 0; 
}
