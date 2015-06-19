from ROOT import *
from Urania import *
AccessPackage("BsJPsiKst")
from parameters import KpiBins23 as Kpibins
from Cuts2013 import cuts12noKpi_nopPID as cuts12
BIN = 3
f2 = TFile("~/NTuplesFast/for_Yorgos/LbJpsipK.root")
t2 = f2.Get("DecayTree")
f = TFile("/tmp/eraseme.root","recreate")
t= t2.CopyTree(cuts12)

Mmax = Kpibins[BIN+1]
Mmin = Kpibins[BIN] 
#Mmax = 1e06
#Mmin = 0
hm = TH1F("B0_MM","B0_MM",20,5150,5500)
for entry in t:
    if not entry.MC_TRUEID : continue
    if entry.Kst_892_0_MM  < Mmin: continue
    if entry.Kst_892_0_MM  > Mmax : continue
    
    hm.Fill(entry.B0_MM)

gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")
x = RooRealVar("B0_MM", "B0_MM", hm.GetBinLowEdge(1),hm.GetBinLowEdge(hm.GetNbinsX()+1))

theta = RooRealVar("theta","theta",-200, -1000,-1)#1000) ## kind of sigma
alpha = RooRealVar("alpha","alpha",1, 0.1, 10)
offset = RooRealVar("mean","mean", 5600, 5450, 8000)
beta = RooRealVar("beta", "beta", 2,-7,7)
## var = "B_s0_MMERR"
h2m = RooDataHist(x.GetName(),x.GetName(),RooArgList(x), hm)
model = RooAmorosoPdf("testing", "testing" ,x, offset, theta, alpha, beta)
fr = x.frame()
model.fitTo(h2m, RooFit.Offset(kTRUE))
h2m.plotOn(fr)
model.plotOn(fr)
fr.Draw()
things = [theta,beta,alpha,offset]
out = {}
for thing in things:
    out[thing.GetName()] = thing.getVal()
print out
