#! /usr/bin/env python
from ROOT import *
from SomeUtils.UnbinnedCLs import LimitCalculator
import sys
from histocreator import mass,mean,sigma,k,bk,ns,nb,signal,model
import time

NumCPU = RooFit.NumCPU
LineColor = RooFit.LineColor
Name = RooFit.Name
Binning = RooFit.Binning
Import = RooFit.Import

start = time.time()

Nsig = 23
job = 322
if sys.argv[1:]: Nsig = float(sys.argv[1])
if sys.argv[2:]: job = float(sys.argv[2])
RooRandom.randomGenerator().SetSeed(int(job*1000 + Nsig))

TOYS = 1000## if good, try with 10000 toys 

f = TFile("my_histos_and_models2.root")
##model = f.Get("model")
datahist = RooDataHist("datahist","datahist",RooArgList(mass),Import(datapdf__mass))

### Sistematicos (aqui llamados constraints)
## Ponemos uno en el yield esperado de bkg:
nb_constrain = RooGaussian("nb_g", "nb_g", nb, RooFit.RooConst(nb.getVal()), RooFit.RooConst(0.75*nb.getVal()))
sigma_constrain = RooGaussian("sigma_c","sigma_c", sigma, RooFit.RooConst(sigma.getVal()), RooFit.RooConst(2))
mean_constrain = RooGaussian("m_c","m_c", mean, RooFit.RooConst(mean.getVal()), RooFit.RooConst(1))
k_constrain = RooGaussian("k_c","k_c", k, RooFit.RooConst(k.getVal()), RooFit.RooConst(0.3e-04))

### End systematicos

mass.setBins(10)
#nb.setConstant(kTRUE)
CL = LimitCalculator(ns,nb, RooArgSet(mass), model, 30, binned = True)
#CL.SetConstraints(RooArgSet(nb_constrain,k_constrain,mean_constrain, sigma_constrain))
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
cPickle.dump(dc, file("outputnosys2_" + str(int(job)) +"_" + str(Nsig),"w"))
##end = time.time()
##print(end - start)
## from ROOT.RooFit import ExternalConstraints, NumCPU,LineColor, Name, Binning
## nll = model.createNLL(datahist,ExternalConstraints(RooArgSet(nb_constrain, mean_constrain, sigma_constrain, k_constrain)),NumCPU(12))    
## myminuit = RooMinuit(nll)
## myminuit.minos(RooArgSet(ns))
## gROOT.SetBatch()
## pl = nll.createProfile(RooArgSet(ns))

## ##f = TFile("prueba.root","recreate")
## myframe = ns.frame()
## ##data.plotOn(myframe)
## ##model.plotOn(myframe)
## ##nll.plotOn(myframe)
## pl.plotOn(myframe,LineColor(kRed),Name("gr"))
## gr = myframe.getCurve("gr")

## mygraph = TGraph()
## mygraph2 = TGraph()
## mygraph.SetName("loglikelihood")
## mygraph2.SetName("likelihood")
## xval = Double(0)
## yval = Double(0)
## x = []
## y = []
## n = 0
## p = gr.GetPoint(n,xval,yval)
## x.append(xval)
## y.append(yval)

## def my_getpoint(n):
##     xval = Double(0)
##     yval = Double(0)
##     p = gr.GetPoint(n,xval,yval)
##     return xval,yval

## while(n<106):
##     n += 1
##     x.append(my_getpoint(n)[0])
##     y.append(my_getpoint(n)[1])
##     print x
##     print y
##     mygraph.SetPoint(n,x[n-1],y[n-1])
##     ##mygraph2.SetPoint(n,xval,exp(-yval))

## xl = x[3:16]
## yll = y[3:16]
## yl = map(lambda l: exp(-l),yll)
## sumyl = sum(yl)
## ylnorm = map(lambda l: l*(1./sumyl),yl)


## for i in range(len(xl)):
##     ##mygraph.SetPoint(n,x[i],y[i])
##     mygraph2.SetPoint(i,xl[i],ylnorm[i])

## f = TFile("mierda.root","recreate")
## mygraph.Write()
## mygraph2.Write()
## f.Close()


