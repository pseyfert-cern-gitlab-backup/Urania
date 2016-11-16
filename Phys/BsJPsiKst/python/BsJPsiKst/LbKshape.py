from ROOT import *
from Urania import *
AccessPackage("BsJPsiKst")
from parameters import KpiBins23 as Kpibins
from Cuts2013 import cuts12noKpi_nopPID as cuts12
BIN = 3
f2 = TFile("~/NTuplesFast/MC/peaking/2012/Lb_JpsipK_sel.root")
t2 = f2.Get("DecayTree")
f1 = TFile("~/NTuplesFast/MC/peaking/2011/Lb_JpsipK_sel.root")
t1= f1.Get("DecayTree")
WEIGHT = 1

Mmax = Kpibins[BIN+1]
Mmin = Kpibins[BIN] 
#Mmax = 896+70
#Mmin = 896-70
hm = TH1F("B0_MM","B0_MM",20,5150,5500)
if WEIGHT:
    SUMW = 0
    SUMW2 = 0
    for entry in t1:
        SUMW += entry.weights
        SUMW2 += entry.weights**2
    SUMWb = 0
    SUMW2b = 0
    for entry in t2:
        SUMWb += entry.weights
        SUMW2b += entry.weights**2

for entry in t1:
    #if not entry.MC_TRUEID : continue
    if entry.Kst_892_0_MM  < Mmin: continue
    if entry.Kst_892_0_MM  > Mmax : continue
    
    if WEIGHT: hm.Fill(entry.B0_MM, entry.weights*SUMW/SUMW2)
    else: hm.Fill(entry.B0_MM)
for entry in t2:
    #if not entry.MC_TRUEID : continue
    if entry.Kst_892_0_MM  < Mmin: continue
    if entry.Kst_892_0_MM  > Mmax : continue
    
    if WEIGHT: hm.Fill(entry.B0_MM, entry.weights*SUMWb/SUMW2b)
    else: hm.Fill(entry.B0_MM)


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
