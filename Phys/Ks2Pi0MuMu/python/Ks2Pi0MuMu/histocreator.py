#! /usr/bin/env python
from ROOT import *
from Urania import *
NumCPU = RooFit.NumCPU
LineColor = RooFit.LineColor
Name = RooFit.Name
Binning = RooFit.Binning
Import = RooFit.Import
##from ROOT.RooFit import ExternalConstraints, NumCPU,LineColor, Name, Binning

mass = RooRealVar("mass","mass", 5309.6, 5429.6)

## Signal model : Just a gaussian
mean = RooRealVar("mean", "mean" ,5369.6, 5360, 5500)
sigma = RooRealVar("sigma", "sigma", 22, 18, 25)
mean.setConstant(kTRUE)
sigma.setConstant(kTRUE)
signal = RooGaussian("signal", "signal", mass, mean, sigma)

## Bkg model: A exponential
k = RooRealVar("kappa","kappa", -1.0e-04,-1e-03, 1e-03)
k.setConstant(kTRUE)
bk = RooExponential("bk","bk", mass, k)

## Define the yields and the combined model
ns = RooRealVar("ns","ns", 10,0,300)
nb = RooRealVar("nb","nb",30.0 , 0,600)

model = RooAddPdf("model", "model", RooArgList(signal,bk),RooArgList(ns,nb))
nullmodel = RooAddPdf("model","model",RooArgList(bk),RooArgList(nb))

mass.setBins(10)
data = model.generateBinned(RooArgSet(mass),20)


## Create Histo from signal and background models
sigpdf_model = RooAddPdf("sigpdf_model","sigpdf_model",RooArgList(signal),RooArgList(ns))
sigpdf = sigpdf_model.createHistogram("sigpdf",mass,Binning(10))
bkgpdf_model = RooAddPdf("bkgpdf_model","bkgpdf_model",RooArgList(bk),RooArgList(nb))
bkgpdf = bkgpdf_model.createHistogram("bkgpdf",mass,Binning(10))
datapdf = data.createHistogram("datapdf",mass,Binning(10))
f = TFile("histos_and_models.root","recreate")
sigpdf.Write()
bkgpdf.Write()
datapdf.Write()
sigpdf_model.Write()
bkgpdf_model.Write()
data.Write()
model.Write()
f.Close()


#myfr = mass.frame()
#model.plotOn(myfr)
#myfr.GetYaxis().SetTitle("")
#myfr.GetXaxis().SetTitle("Mass ( MeV/c^{2} )")
#myfr.SetTitle("")
#myfr.Draw()
