#! /usr/bin/env python
from ROOT import *
from SomeUtils.UnbinnedCLs import LimitCalculator
import sys
Nsig = 10
job = 322
if sys.argv[1:]: Nsig = float(sys.argv[1])
if sys.argv[2:]: job = float(sys.argv[2])
RooRandom.randomGenerator().SetSeed(int(job*1000 + Nsig))

TOYS = 1000
mass = RooRealVar("mass","mass", 5309.6, 5429.6)

## Signal model : Just a gaussian
mean = RooRealVar("mean", "mean" ,5369.6, 5360, 5500)
sigma = RooRealVar("sigma", "sigma", 22, 18, 25)
signal = RooGaussian("signal", "signal", mass, mean, sigma)

## Bkg model: A exponential
k = RooRealVar("kappa","kappa", -1e-04,-1e-03, 1e-03)
bk = RooExponential("bk","bk", mass, k)

## Define the yields and the combined model
ns = RooRealVar("ns","ns", 10,0,300)
nb = RooRealVar("nb","nb", 30, 0,600)
model = RooAddPdf("model", "model", RooArgList(signal,bk),RooArgList(ns,nb))

### Sistematicos (aqui llamados constraints)

## Ponemos uno en el yield esperado de bkg:
nb_constrain = RooGaussian("nb_g", "nb_g", nb, RooFit.RooConst(nb.getVal()), RooFit.RooConst(0.25*nb.getVal()))
sigma_constrain = RooGaussian("sigma_c","sigma_c", sigma, RooFit.RooConst(sigma.getVal()), RooFit.RooConst(2))
mean_constrain = RooGaussian("m_c","m_c", mean, RooFit.RooConst(mean.getVal()), RooFit.RooConst(1))
k_constrain = RooGaussian("k_c","k_c", k, RooFit.RooConst(k.getVal()), RooFit.RooConst(0.3e-04))

### End systematicos

mass.setBins(10)
f = TFile("data_test.root")#, "recreate")
#data = model.generateBinned(RooArgSet(mass))

data = f.Get("modelData") #model.generateBinned(RooArgSet(mass))

#nb.setConstant(kTRUE)
CL = LimitCalculator(ns,nb, RooArgSet(mass), model, 30, binned = True)
CL.SetConstraints(RooArgSet(nb_constrain, mean_constrain, sigma_constrain, k_constrain))
    #print CL.ConfidenceLevels(data,10)

#BREAK

a = CL.ConfidenceLevelsClassic(data,Nsig, NToys = TOYS)
ndll1 = list(CL.nullDLLs)
tdll1 = list(CL.testDLLs)
b = CL.ConfidenceLevels(data,Nsig, NToys = TOYS)
ndll2 = list(CL.nullDLLs)
tdll2 = list(CL.testDLLs)
print a, b
dc = {}
dc["clas"] = a
dc["free"] = b
import cPickle
cPickle.dump(dc, file("output_" + str(int(job)) +"_" + str(Nsig),"w"))

## from bisect import *
## g1,g2 = TGraph(), TGraph()
## for i in range(4000):
##     xcut = -20 + .01*i
##     g1.SetPoint(i, float(bisect(tdll1,xcut))/len(tdll1), float(bisect(ndll1,xcut))/len(ndll1))
##     g2.SetPoint(i, float(bisect(tdll2,xcut))/len(tdll2), float(bisect(ndll2,xcut))/len(ndll2))
## g2.SetLineColor(kBlue)
## g1.Draw("AL")
## g2.Draw("L")

