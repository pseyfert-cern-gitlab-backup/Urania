from ROOT import *
from math import *
import os
from Urania import *
gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")

Mass = RooRealVar("B0_MM","B0_MM",5150, 5650.)

mean  = RooRealVar("mean", "mean",  5500.00, 5450, 5550.)
theta = RooRealVar("theta","theta",-245.84, -1000,-1)
alpha = RooRealVar("alpha","alpha", 0.22, 0.1, 10)
beta  = RooRealVar("beta", "beta",  6.624,-7,7)

LbK_pdf = RooAmorosoPdf("mass_model", "mass_model", Mass, mean, theta, alpha, beta)
LbK_dataset = LbK_pdf.generate(RooArgSet(Mass),int(750))

fr = Mass.frame()
LbK_dataset.plotOn(fr)
LbK_pdf.plotOn(fr)
fr.Draw()
fr.SaveAs("mass_plot_testAmoroso.root")
