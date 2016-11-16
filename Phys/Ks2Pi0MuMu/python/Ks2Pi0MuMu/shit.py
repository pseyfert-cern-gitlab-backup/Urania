#! /usr/bin/env python
from ROOT import *
from SomeUtils.UnbinnedCLs import LimitCalculator
from SomeUtils.numericFunctionClass import *
import sys
from scipy.stats import poisson
from histocreator import mass,mean,sigma,k,bk,ns,nb,signal,model
from scipy.interpolate import interp1d

def normalize(x):
    """ Returns x/sum(x) (normalized vector)"""
    sumx = sum(x)
    y = []
    for xi in x:
        xi = xi*(1./sumx)
        y.append(xi)
    return y

NumCPU = RooFit.NumCPU
LineColor = RooFit.LineColor
Name = RooFit.Name
Binning = RooFit.Binning
Import = RooFit.Import

Nsig = 23
job = 322
if sys.argv[1:]: Nsig = float(sys.argv[1])
if sys.argv[2:]: job = float(sys.argv[2])
RooRandom.randomGenerator().SetSeed(int(job*1000 + Nsig))

TOYS = 100 ## if good, try with 10000 toys 

##mean.setConstant(kTRUE)
##sigma.setConstant(kTRUE)
##k.setConstant(kTRUE)

f = TFile("my_histos_and_models.root")
## ##model = f.Get("model")

datapdf = f.Get("datapdf__mass")
## sigpdf = f.Get("sigpdf__mass")
## bkgpdf = f.Get("bkgpdf__mass")
## slist = []
## blistn = []
## xlist = []
## for i in range(1,6):
##     xlist.append(datapdf.GetBinContent(i))
##     slist.append(sigpdf.GetBinContent(i))
##     blistn.append(bkgpdf.GetBinContent(i))

## mean.setConstant(kTRUE)
## sigma.setConstant(kTRUE)
## k.setConstant(kTRUE)

## blistn = normalize(blistn)
## blist = []
## for bi in blistn:
##     blist.append(30*bi)
datahist = RooDataHist("datahist","datahist",RooArgList(mass),Import(datapdf__mass))
## slist = normalize(slist)
### Sistematicos (aqui llamados constraints)
## Ponemos uno en el yield esperado de bkg:

##mean.setConstant(kTRUE)
##sigma.setConstant(kTRUE)
##k.setConstant(kTRUE)

nb_constrain = RooGaussian("nb_g", "nb_g", nb, RooFit.RooConst(nb.getVal()),RooFit.RooConst(0.000001))# RooFit.RooConst(0.25*nb.getVal()))
sigma_constrain = RooGaussian("sigma_c","sigma_c", sigma, RooFit.RooConst(sigma.getVal()), RooFit.RooConst(2))
mean_constrain = RooGaussian("m_c","m_c", mean, RooFit.RooConst(mean.getVal()), RooFit.RooConst(1))
k_constrain = RooGaussian("k_c","k_c", k, RooFit.RooConst(k.getVal()), RooFit.RooConst(0.3e-04))

### End systematicos
mass.setBins(5)

CL = LimitCalculator(ns,nb, RooArgSet(mass), model, 30, binned = True)
CL.SetConstraints(RooArgSet(nb_constrain))##nb_constrain,k_constrain,mean_constrain, sigma_constrain))
    #print CL.ConfidenceLevels(data,10)


#BREAK

a = CL.ConfidenceLevelsClassic(datahist,Nsig, NToys = TOYS)
ndll1 = list(CL.nullDLLs) 
tdll1 = list(CL.testDLLs)
b = CL.ConfidenceLevels(datahist,Nsig, NToys = TOYS)
ndll2 = list(CL.nullDLLs)
tdll2 = list(CL.testDLLs)
##print a, b
dc = {}
dc["clas"] = a
dc["free"] = b
import cPickle
cPickle.dump(dc, file("shit2_" + str(int(job)) +"_" + str(Nsig),"w"))
