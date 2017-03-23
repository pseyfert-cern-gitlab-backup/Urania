#  An example of using Extended Dalitz plot phase space class. 
#  (Dalitz plot with the mass of the mother particle in a range)
#  Generate points across the 3D phase space and use kernel 
#  estimation to estimate efficiency shape. 

import os, sys
os.environ["ROOT_INCLUDE_PATH"] = os.pathsep + "../inc/"

from ROOT import gSystem, gStyle, RooRealVar

gSystem.Load("../lib/libMeerkat.so")

from ROOT import ExtendedDalitzPhaseSpace, BinnedKernelDensity, FactorisedDensity, FormulaDensity
from ROOT import TFile, TNtuple, TCanvas, TH1F, TH2F, TText

# Define masses of initial ("d") and final state particles ("a,b,c") for the Dalitz phase space. 
md1 = 1.     # D0
md2 = 2.     # D0
ma = 0.497   # K
mb = 0.139   # Pi
mc = 0.139   # Pi

# Define Dalitz phase space for D0->KsPiPi decay
# The phase space is defined in x=m^2(ab), y=m^2(ac) variables
phsp = ExtendedDalitzPhaseSpace("PhspDalitz", md1, md2, ma, mb, mc)

# Create a true PDF over this phase space, a function in x, y and z
truepdf = FormulaDensity("TruePDF", phsp, "sqrt(1.-0.1*(y-1.3)^4)*(1.+2.*exp(-z))")

outfile = TFile.Open("DalitzPdf.root", "RECREATE")
ntuple = TNtuple("ntuple", "2D NTuple", "m:x:y")

# Generate 50000 toys according to the "true" PDF
truepdf.generate(ntuple, 100000)

# Create kernel PDF from the generated sample
kde = BinnedKernelDensity("KernelPDF", 
                          phsp,    # Phase space
                          ntuple,  # Input ntuple
                          "m","x","y", # Variables to use
                          30,100,100,  # Numbers of bins
                          0.2,0.4, 0.4,# Kernel widths
                          0,       # Approximation PDF (0 for flat approximation)
                          200000    # Sample size for MC convolution (0 for binned convolution)
                         )

# Write binned PDF into a file
kde.writeToFile("ExtendedDalitzPdf_bins.root")

# That's it. Now fill some histograms and show the results. 

true1_hist = TH2F("true1", "True PDF", 100, phsp.lowerLimit(1), phsp.upperLimit(1), 
                                       100, phsp.lowerLimit(2), phsp.upperLimit(2))
kernel1_hist = TH2F("kernel1", "Kernel PDF", 100, phsp.lowerLimit(1), phsp.upperLimit(1), 
                                             100, phsp.lowerLimit(2), phsp.upperLimit(2))

true2_hist = TH2F("true2", "True PDF", 100, phsp.lowerLimit(1), phsp.upperLimit(1), 
                                       100, phsp.lowerLimit(2), phsp.upperLimit(2))
kernel2_hist = TH2F("kernel2", "Kernel PDF", 100, phsp.lowerLimit(1), phsp.upperLimit(1), 
                                             100, phsp.lowerLimit(2), phsp.upperLimit(2))

true_kpi = TH1F("true_kpi", "M^{2}(K_{S}#pi) slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) )
kernel_kpi = TH1F("kernel_kpi", "M^{2}(K_{S}#pi) slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) )
true_pipi = TH1F("true_pipi", "M^{2}(#pi#pi) slice", 100, phsp.lowerLimit(2), phsp.upperLimit(2) )
kernel_pipi = TH1F("kernel_pipi", "M^{2}(#pi#pi) slice", 100, phsp.lowerLimit(2), phsp.upperLimit(2) )

# Coordinates in the phase space where we will create the 1D slices.
from ROOT import std, Double
v = std.vector(Double)(3)
v[0] = 1.9;
v[1] = 1.0;
v[2] = 0.3;

# Fill histogram with the result of kernel density estimation
truepdf.slice(v, 1, 2, true1_hist)
true1_hist.Write()
kde.slice(v, 1, 2, kernel1_hist)
kernel1_hist.Write()

# Fill 1D slice in x projection, at the point y=v[1]
truepdf.slice(v, 1, true_kpi) 
true_kpi.Write() 
kde.slice(v, 1, kernel_kpi)
kernel_kpi.Write()

# Fill 1D slice in y projection, at the point x=v[0]
truepdf.slice(v, 2, true_pipi)
true_pipi.Write()
kde.slice(v, 2, kernel_pipi)
kernel_pipi.Write()

v[0] = 1.3;
v[1] = 1.0;
v[2] = 0.3;

# Fill histogram with the result of kernel density estimation
truepdf.slice(v, 1, 2, true2_hist)
true2_hist.Write()
kde.slice(v, 1, 2, kernel2_hist)
kernel2_hist.Write()

# Plot 2D and 1D histograms

gStyle.SetOptStat(0)

canvas = TCanvas("canvas", "ExtendedDalitzPdf", 600, 900)
canvas.Divide(2,3)

canvas.cd(1)
true1_hist.Draw("zcol")
true1_hist.GetXaxis().SetTitle("M^{2}(K_{S}#pi), GeV")
true1_hist.GetYaxis().SetTitle("M^{2}(#pi#pi), GeV")

canvas.cd(2)
kernel1_hist.Scale( true1_hist.GetSumOfWeights() / kernel1_hist.GetSumOfWeights() )
kernel1_hist.Draw("zcol")
kernel1_hist.GetXaxis().SetTitle("M^{2}(K_{S}#pi), GeV")
kernel1_hist.GetYaxis().SetTitle("M^{2}(#pi#pi), GeV")

canvas.cd(3)
true2_hist.Draw("zcol")
true2_hist.GetXaxis().SetTitle("M^{2}(K_{S}#pi), GeV")
true2_hist.GetYaxis().SetTitle("M^{2}(#pi#pi), GeV")

canvas.cd(4)
kernel2_hist.Scale( true2_hist.GetSumOfWeights() / kernel2_hist.GetSumOfWeights() )
kernel2_hist.Draw("zcol")
kernel2_hist.GetXaxis().SetTitle("M^{2}(K_{S}#pi), GeV")
kernel2_hist.GetYaxis().SetTitle("M^{2}(#pi#pi), GeV")

canvas.cd(5)
kernel_kpi.Scale( true_kpi.GetSumOfWeights() / kernel_kpi.GetSumOfWeights() )
true_kpi.Draw()
kernel_kpi.SetLineColor(2)
kernel_kpi.Draw("same")

canvas.cd(6)
kernel_pipi.Scale( true_pipi.GetSumOfWeights() / kernel_pipi.GetSumOfWeights() )
true_pipi.Draw()
kernel_pipi.SetLineColor(2)
kernel_pipi.Draw("same")

canvas.Print("ExtendedDalitzPdf.png")
canvas.Update()

#outfile.Close()
