from ROOT import *
from math import *
import os
import time
#---------------------------------------------------------------------------
timeZero = time.time()
#---------------------------------------------------------------------------
tuplePath = './MagUpAndDown4000GeVReco14s20r0p1dv33r4_2062pb_StrippingBetaSBs2JpsiKstarWideLine_2012_BDTG_Loose.root'
Mmax = 5650.
#---------------------------------------------------------------------------
print "Simple mass fit for BsJpsiKst data"
#---------------------------------------------------------------------------
## Rectangular cuts (loose):
rect_cuts = "muplus_MINIPCHI2 > 16. && muminus_MINIPCHI2 > 16. && Kplus_MINIPCHI2 > 2. && piminus_MINIPCHI2 > 2."
rect_cuts += " && B0_LOKI_DTF_CTAU > 0."
rect_cuts += " && Kplus_PT > 500. && piminus_PT > 500."
rect_cuts += " && abs(Kst_892_0_MM-896) < 70."
rect_cuts += " && abs(Mjpsik-5279) > 60."
cuts = rect_cuts + " && piminus_ProbNNk<0.01 && Kplus_ProbNNk>0.21"
cuts += " && Kplus_ProbNNk/Kplus_ProbNNp>0.99 && piminus_ProbNNpi/piminus_ProbNNp>21.9"
cuts += " && BDTG>0.12" # 2012
#cuts += " && BDTG>0.2" # 2011
#---------------------------------------------------------------------------
myTFile = TFile(tuplePath)
aTTree = myTFile.Get("DecayTree")
fx=TFile("junkFile.root","recreate")
cuts += " && B0_MM>5150. && B0_MM<"+str(Mmax)
myTTree=aTTree.CopyTree(cuts)
#---------------------------------------------------------------------------
Mass = RooRealVar("B0_MM","B0_MM",5150,Mmax)
a1_cb = RooRealVar("a1_cb","a1_cb",2.8)
a2_cb = RooRealVar("a2_cb","a2_cb",2.3)
a2r_cb = RooRealVar("a2r_cb","a2r_cb",-1.79)
ncb = RooRealVar("ncb","ncb",1)
ncb2 = RooRealVar("ncb2","ncb2",3.1)
delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
f05 = RooRealVar("f05","f05",0.5)
fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
#---------------------------------------------------------------------------
## Signal:
mean1 = RooRealVar("mean1","mean1",5279,5276,5300)
sigma1 = RooRealVar("sigma1","sigma1", 6.,10.)
delta_s = RooRealVar("delta_s","delta_s", 2., 1., 15.)
sigma2 = RooFormulaVar("sigma2","sigma2","sigma1 + delta_s",RooArgList(sigma1,delta_s))
mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(mean1,delta_m))
sigb11  = RooCBShape("SigmodelB11","SigmodelB11", Mass, mean1, sigma1, a1_cb, ncb)
sigb12l  = RooCBShape("SigmodelB12l","SigmodelB12l", Mass, mean1, sigma2, a2_cb, ncb)
sigb12r  = RooCBShape("SigmodelB12r","SigmodelB12r", Mass, mean1, sigma2, a2r_cb, ncb2)
sigb12  = RooAddPdf("SigmodelB12","SigmodelB12", sigb12l, sigb12r, f05)
sigb21  = RooCBShape("SigmodelB21","SigmodelB21", Mass, mean2, sigma1, a1_cb, ncb)
sigb22l  = RooCBShape("SigmodelB22l","SigmodelB22l", Mass, mean2, sigma2, a2_cb, ncb)
sigb22r  = RooCBShape("SigmodelB22r","SigmodelB22r", Mass, mean2, sigma2, a2r_cb, ncb2)
sigb22  = RooAddPdf("SigmodelB22","SigmodelB22", sigb22l, sigb22r, f05)
fsmres = RooRealVar("f small res","f small res",0.8, 0., 1.)
sigBd  = RooAddPdf("SigmodelB1","SigmodelB1", sigb11, sigb12, fsmres)
sigBs  = RooAddPdf("SigmodelB2","SigmodelB2", sigb21, sigb22, fsmres)
## Background:
kbkg = RooRealVar("kBkg","kBkg",-1e-03,-1,0)
bkgmodel = RooExponential("MassBkg", "MassBkg", Mass, kbkg)
#---------------------------------------------------------------------------
nd = RooRealVar("nBd","nBd", 0.5*(myTTree.GetEntries()),myTTree.GetEntries())
ns = RooRealVar("nBs","nBs", 0.,0.5*(myTTree.GetEntries()))
nbkg = RooRealVar("nBkg","nBkg", 0.,myTTree.GetEntries())
#---------------------------------------------------------------------------
model = RooAddPdf("model","model",RooArgList(sigBs,sigBd,bkgmodel),RooArgList(ns,nd,nbkg))
dataset = RooDataSet("data","data",myTTree,RooArgSet(Mass))
#---------------------------------------------------------------------------
minos = 1
fitres = model.fitTo(dataset,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8))
#---------------------------------------------------------------------------
os.system("rm junkFile.root")
#---------------------------------------------------------------------------
def plot_mass(nbins = 100):
  cv3 = TCanvas()
  themodel = model
  thedataset = dataset
  cphif = Mass.frame()
  RooAbsData.plotOn(thedataset,cphif,RooFit.Binning(nbins))
  themodel.plotOn(cphif)
  themodel.plotOn(cphif,RooFit.Components("MassBkg"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
  themodel.plotOn(cphif,RooFit.Components("SigmodelB2"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
  themodel.plotOn(cphif,RooFit.Components("SigmodelB1"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
  cphif.Draw()
  return cv3, cphif
ff = TFile("FitResults.root","recreate")
fitres.Write("FitResults")
ff.Close()
a_cv, a_cphif = plot_mass()
a_cv.SaveAs("mass_cv.root")
#---------------------------------------------------------------------------
print '\nElapsed time: ' + str(time.time()-timeZero) + ' s.'
#---------------------------------------------------------------------------
