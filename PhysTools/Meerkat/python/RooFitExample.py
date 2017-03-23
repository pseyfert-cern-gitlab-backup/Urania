#
#  This is the example of using Meerkat package with RooFit
#

# The order of imports is a bit convoluted
# First you need to import usual RooFit stuff
import os, sys
os.environ["ROOT_INCLUDE_PATH"] = os.pathsep + "../inc/"

from ROOT import gSystem, gStyle
from ROOT import RooRealVar, RooGaussian, RooChebychev, RooAddPdf, RooArgList, RooArgSet, RooFit

# then load Meerkat library
gSystem.Load("../lib/libMeerkat.so")

# and then Meerkat-specific stuff, including RooMeerkatPdf
from ROOT import OneDimPhaseSpace, UniformDensity, BinnedKernelDensity, FormulaDensity
from ROOT import RooMeerkatPdf
from ROOT import TFile, TNtuple, TCanvas, TH1F

###########################################################
########## First create signal model with Meerkat #########
###########################################################

# Define 1D phase space for a variable in range (-1, 1)
phsp = OneDimPhaseSpace("Phsp1D", -1., 1.)

# Create Gaussian PDF over the phase space
gaussian = FormulaDensity("FormulaPDF", phsp, "exp(-x*x/2/0.1/0.1)*( abs(x)<1 )")

outfile = TFile("OneDimPdf.root", "RECREATE")
ntuple = TNtuple("ntuple", "1D NTuple", "x")

# Generate 10000 toys according to the uniform PDF
gaussian.generate(ntuple, 10000)

# Create kernel PDF from the generate gaussian sample
kde = BinnedKernelDensity("KernelPDF", 
                          phsp, 
                          ntuple, # Input ntuple
                          "x",    # Variable to use
                          1000,   # Number of bins
                          0.03,   # Kernel width
                          0,      # Approximation PDF (0 for flat approximation)
                          100000  # Sample size for MC convolution (0 for binned convolution)
                         )

# Write binned PDF into a file
kde.writeToFile("OneDimPdfBins.root")

##########################################
########## Now start with RooFit #########
##########################################

x = RooRealVar("x","x",-1,1)

# Use RooGaussian in the generation
mean = RooRealVar("mean","mean of gaussian",0,-1,1)
sigma = RooRealVar("sigma","sigma of gaussian",0.1,-1,1)
sig = RooGaussian("gauss","gaussian PDF",x,mean,sigma) ; 

# Background
a0 = RooRealVar("a0","a0",0.5,0.,1.)
a1 = RooRealVar("a1","a1",-0.2,0.,1.)
bkg = RooChebychev("bkg","Background",x,RooArgList(a0,a1))

bkgfrac = RooRealVar("bkgfrac","fraction of background",0.5,0.,1.)
model = RooAddPdf("model","g+a",RooArgList(bkg,sig), RooArgList(bkgfrac) )

data = model.generate(RooArgSet(x), 10000)

# Use RooMeerkatPdf in the fit
meerkat_sig = RooMeerkatPdf("meerkat_sig", "Meerkat PDF", RooArgList(x), kde)
model2 = RooAddPdf("model2","m+a",RooArgList(bkg,meerkat_sig),RooArgList(bkgfrac) )

model2.fitTo(data)

xframe = x.frame(RooFit.Title(""))

data.plotOn(xframe)
model2.plotOn(xframe)
model2.plotOn(xframe,RooFit.Components("bkg"), RooFit.LineColor(2))
model2.plotOn(xframe,RooFit.Components("meerkat_sig"), RooFit.LineColor(6))

c = TCanvas("c", "c", 600, 600)
xframe.GetYaxis().SetTitleOffset(1.4)
xframe.Draw()
