#include "TROOT.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TStyle.h"

#include "DalitzPhaseSpace.hh"
#include "ExtendedDalitzPhaseSpace.hh"
#include "FormulaDensity.hh"
#include "BinnedDensity.hh"
#include "BinnedKernelDensity.hh"
#include "AdaptiveKernelDensity.hh"

/*
  My version of the file
  An example of using 3D Dalitz plot phase space class.

  Generate points across the Dalitz plot and use kernel
  estimation to estimate efficiency shape.

  Demonstrates the use of 2D projection and 1D slices.
*/

int main(int argc, char** argv) {

  // Define masses of initial ("d") and final state particles ("a,b,c") for the Dalitz phase space.
  Double_t mResMin = 1.0;   // Kpipimin
  Double_t mResMax = 2.0;   // Kpipimax
  Double_t ma = 0.497;   // K
  Double_t mb = 0.139;   // Pi
  Double_t mc = 0.139;   // Pi

  TApplication theApp("App", &argc, argv);

  // Define Dalitz phase space for K1_1270 -> KPiPi decay
  // The phase space is defined in x=m^2(ab), y=m^2(ac) variables
  ExtendedDalitzPhaseSpace phsp("PhspDalitz", mResMin, mResMax, ma, mb, mc);

  // Create a true PDF over this phase space,
  // a function in x, y and z
  FormulaDensity truepdf("TruePDF", &phsp, "sqrt(1.-0.1*(y-1.3)^4)*(1.+2.*exp(-z))");

  TFile outfile("DalitzPdf.root", "RECREATE");
  TNtuple ntuple("ntuple", "3D NTuple", "m:x:y");
  // Generate 50000 toys according to the "true" PDF
  truepdf.generate(&ntuple, 100000);


  // Create kernel PDF from the generated sample
  BinnedKernelDensity kde("KernelPDF",
                          &phsp,   // Phase space
                          &ntuple, // Input ntuple
                          "m","x","y", // Variables to use
                          30,100,100, // Numbers of bins
                          0.2, 0.4, 0.4,// Kernel widths
                          0,       // Approximation PDF (0 for flat approximation)
                          200000   // Sample size for MC convolution (0 for binned convolution)
                         );

  // Write binned PDF into a file
  kde.writeToFile("ExtendedDalitzPdf_bins.root");

  // That's it. Now fill some histograms and show the results.

  TH2F true1_hist("true1", "True PDF at m=1.9, x=1.0, y=0.3", 100, phsp.lowerLimit(1), phsp.upperLimit(1),
                                       100, phsp.lowerLimit(2), phsp.upperLimit(2));
  TH2F kernel1_hist("kernel1", "Kernel PDF at m=1.9, x=1.0, y=0.3", 100, phsp.lowerLimit(1), phsp.upperLimit(1),
                                             100, phsp.lowerLimit(2), phsp.upperLimit(2));
  TH2F true2_hist("true2", "True PDF at m=1.3, x=1.0, y=0.3", 100, phsp.lowerLimit(1), phsp.upperLimit(1),
                                       100, phsp.lowerLimit(2), phsp.upperLimit(2));
  TH2F kernel2_hist("kernel2", "Kernel PDF at m=1.3, x=1.0, y=0.3", 100, phsp.lowerLimit(1), phsp.upperLimit(1),
                                             100, phsp.lowerLimit(2), phsp.upperLimit(2));

  TH1F true_kpi("true_kpi", "M^{2}(K#pi) slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) );
  TH1F kernel_kpi("kernel_kpi", "M^{2}(K#pi) slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) );
  TH1F true_pipi("true_pipi", "M^{2}(#pi#pi) slice", 100, phsp.lowerLimit(2), phsp.upperLimit(2) );
  TH1F kernel_pipi("kernel_pipi", "M^{2}(#pi#pi) slice", 100, phsp.lowerLimit(2), phsp.upperLimit(2) );

  // Coordinates in the phase space where we will create the 1D slices.
  std::vector<Double_t> v(3);
  v[0] = 1.9;
  v[1] = 1.0;
  v[2] = 0.3;

  // Fill histogram with the result of kernel density estimation
  truepdf.slice(v, 1, 2, &true1_hist);
  true1_hist.Write();
  kde.slice(v, 1, 2, &kernel1_hist);
  kernel1_hist.Write();

  // Fill 1D slice in x projection, at the point y=v[1]
  truepdf.slice(v, 1, &true_kpi);
  true_kpi.Write();
  kde.slice(v, 1, &kernel_kpi);
  kernel_kpi.Write();

  // Fill 1D slice in y projection, at the point x=v[0]
  truepdf.slice(v, 2, &true_pipi);
  true_pipi.Write();
  kde.slice(v, 2, &kernel_pipi);
  kernel_pipi.Write();

  outfile.Close();

  // Slice a different mass for the mother resonance
  v[0] = 1.3;
  v[1] = 1.0;
  v[2] = 0.3;

  // Fill histogram with the result of kernel density estimation
  truepdf.slice(v, 1, 2, &true2_hist);
  true2_hist.Write();
  kde.slice(v, 1, 2, &kernel2_hist);
  kernel2_hist.Write();

  // Plot 2D and 1D histograms
  gStyle->SetOptStat(0);

  TCanvas canvas("canvas", "ExtendedDalitzPdf", 600, 900);
  canvas.Divide(2,3);

  canvas.cd(1);
  true1_hist.Draw("zcol");
  //ntuple.Draw("m:y:x", "");
  true1_hist.GetXaxis()->SetTitle("M^{2}(K#pi), GeV");
  true1_hist.GetYaxis()->SetTitle("M^{2}(#pi#pi), GeV");

  canvas.cd(2);
  kernel1_hist.Scale( true1_hist.GetSumOfWeights() / kernel1_hist.GetSumOfWeights() );
  kernel1_hist.Draw("zcol");
  kernel1_hist.GetXaxis()->SetTitle("M^{2}(K#pi), GeV");
  kernel1_hist.GetYaxis()->SetTitle("M^{2}(#pi#pi), GeV");

  canvas.cd(3);
  true2_hist.Draw("zcol");
  //ntuple.Draw("m:y:x", "");
  true2_hist.GetXaxis()->SetTitle("M^{2}(K#pi), GeV");
  true2_hist.GetYaxis()->SetTitle("M^{2}(#pi#pi), GeV");

  canvas.cd(4);
  kernel2_hist.Scale( true2_hist.GetSumOfWeights() / kernel2_hist.GetSumOfWeights() );
  kernel2_hist.Draw("zcol");
  kernel2_hist.GetXaxis()->SetTitle("M^{2}(K#pi), GeV");
  kernel2_hist.GetYaxis()->SetTitle("M^{2}(#pi#pi), GeV");

  canvas.cd(5);
  kernel_kpi.Scale( true_kpi.GetSumOfWeights() / kernel_kpi.GetSumOfWeights() );
  true_kpi.Draw();
  kernel_kpi.SetLineColor(2);
  kernel_kpi.Draw("same");

  canvas.cd(6);
  kernel_pipi.Scale( true_pipi.GetSumOfWeights() / kernel_pipi.GetSumOfWeights() );
  true_pipi.Draw();
  kernel_pipi.SetLineColor(2);
  kernel_pipi.Draw("same");

  canvas.Print("ExtendedDalitzPdf.png");
  theApp.Run();

  return 0;
}
