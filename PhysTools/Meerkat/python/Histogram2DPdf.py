#  An example of using histogram density class. 

import os, sys
os.environ["ROOT_INCLUDE_PATH"] = os.pathsep + os.environ["MEERKATROOT"]

from ROOT import gSystem, gStyle, RooRealVar

gSystem.Load("libMeerkatLib.so")

from ROOT import DalitzPhaseSpace, BinnedKernelDensity, FactorisedDensity, FormulaDensity, HistogramDensity
from ROOT import BinnedDensity, AdaptiveKernelDensity, PolynomialDensity
from ROOT import TFile, TNtuple, TCanvas, TH1F, TH2F, TText

# Define masses of initial ("d") and final state particles ("a,b,c") for the Dalitz phase space. 
md = 1.8646  # D0
ma = 0.497   # KS0
mb = 0.139   # Pi
mc = 0.139   # Pi

# Define Dalitz phase space for D0->KsPiPi decay
# The phase space is defined in x=m^2(ab), y=m^2(ac) variables
phsp = DalitzPhaseSpace("PhspDalitz", md, ma, mb, mc)

# Create a true PDF over this phase space, polynomial of power 4 in x and y
truepdf = FormulaDensity("TruePDF", phsp, "sqrt(1.-0.1*(x-1.3)^4)*(1.+2.*exp(-y))")

outfile = TFile.Open("DalitzPdf.root", "RECREATE")
ntuple = TNtuple("ntuple", "2D NTuple", "x:y")

# Generate 25000 toys according to the "true" PDF
truepdf.generate(ntuple, 25000)

hist = TH2F("hist","", 20, 0., phsp.upperLimit(0), 20, 0., phsp.upperLimit(1))
ntuple.Project("hist","y:x")

histpdf = HistogramDensity("histpdf", phsp, hist)

# That's it. Now fill some histograms and show the results. 

true_hist = TH2F("true", "True PDF", 100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                     100, phsp.lowerLimit(1), phsp.upperLimit(1))
hist_hist = TH2F("poly", "Polynomial PDF", 100, phsp.lowerLimit(0), phsp.upperLimit(0), 
                                     100, phsp.lowerLimit(1), phsp.upperLimit(1))

true_kpi = TH1F("true_kpi", "M^{2}(K_{S}#pi) slice", 100, phsp.lowerLimit(0), phsp.upperLimit(0) )
hist_kpi = TH1F("poly_kpi", "M^{2}(K_{S}#pi) slice", 100, phsp.lowerLimit(0), phsp.upperLimit(0) )
true_pipi = TH1F("true_pipi", "M^{2}(#pi#pi) slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) )
hist_pipi = TH1F("poly_pipi", "M^{2}(#pi#pi) slice", 100, phsp.lowerLimit(1), phsp.upperLimit(1) )

# Coordinates in the phase space where we will create the 1D slices.
from ROOT import std, Double
v = std.vector(Double)(2)
v[0] = 1.0;
v[1] = 0.3;

# Fill histogram with the result of kernel density estimation
truepdf.project(true_hist)
true_hist.Write()
histpdf.project(hist_hist)
hist_hist.Write()

# Fill 1D slice in x projection, at the point y=v[1]
truepdf.slice(v, 0, true_kpi) 
true_kpi.Write() 
histpdf.slice(v, 0, hist_kpi)
hist_kpi.Write()

# Fill 1D slice in y projection, at the point x=v[0]
truepdf.slice(v, 1, true_pipi)
true_pipi.Write()
histpdf.slice(v, 1, hist_pipi)
hist_pipi.Write()

# Plot 2D and 1D histograms

gStyle.SetOptStat(0)

canvas = TCanvas("canvas", "DalitzPdf", 600, 600)
canvas.Divide(2,2)

canvas.cd(1)
true_hist.Draw("zcol")
true_hist.GetXaxis().SetTitle("M^{2}(K_{S}#pi), GeV")
true_hist.GetYaxis().SetTitle("M^{2}(#pi#pi), GeV")

canvas.cd(2)
hist_hist.Scale( true_hist.GetSumOfWeights() / hist_hist.GetSumOfWeights() )
hist_hist.Draw("zcol")
hist_hist.GetXaxis().SetTitle("M^{2}(K_{S}#pi), GeV")
hist_hist.GetYaxis().SetTitle("M^{2}(#pi#pi), GeV")

canvas.cd(3)
hist_kpi.Scale( true_kpi.GetSumOfWeights() / hist_kpi.GetSumOfWeights() )
true_kpi.Draw()
hist_kpi.SetLineColor(2)
hist_kpi.Draw("hist same l")

canvas.cd(4)
hist_pipi.Scale( true_pipi.GetSumOfWeights() / hist_pipi.GetSumOfWeights() )
true_pipi.Draw()
hist_pipi.SetLineColor(2)
hist_pipi.Draw("hist same l")

canvas.Print("Histogram2DPdf.png")

#outfile.Close()
