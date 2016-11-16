from ROOT import *
from Urania import *
AccesPackage("Bs2MuMu")
AccesPackage("Urania")
import sys
sys.path.append("..")
#import dev_amoroso
from smartpyROOT import *
#from Bs2JpsiPhiParams import Selections
mvar = "B_s0_MM"
f2 = TFile("~/NTuplesFast/Bsmm/MC2012_BsMuMu_down_1M_Strip_match.root")
t2 = f2.Get("B2MuMuTuple/DecayTree")
t2 = f2.Get("MBs2MuMuTuple/DecayTree")
#BREAK
f = TFile("/tmp/dms","recreate")
aa = "&&"

t = t2# signal1.CopyTree(cuts)
 #BREAKtailtable()
#BREAK

mass = RooRealVar(mvar,mvar,4769.6, 5969.6)
#mass = RooRealVar(mvar,mvar,5350, 5400)


gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")
#gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooJohanCruijff.cxx++")


# IPATIA
a2 = RooRealVar("a2","a2",1,10)
a = RooRealVar("a","a",0.5,10)
n = RooRealVar("n","n",1,0.,40)
n2 = RooRealVar("n2","n2",1,.01,40)

ipa_s = RooRealVar("ipa_s","ipa_s", 8, 30)
ipa_m = RooRealVar("ipa_m","ipa_m",5363,5380)
beta = RooRealVar("beta","beta",0)#-0.1,0.1)
zeta = RooRealVar("zeta","zeta",.1,0,10)

l = RooRealVar("l","l",-2,-6,6)

ipatia = RooIpatia2("bullshit","bullshit",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)



hm = TH1F("a"+mass.GetName(),"a"+mass.GetName(),200, mass.getMin(),mass.getMax())
hm2 = TH1F("a2"+mass.GetName(),"a2"+mass.GetName(),200, mass.getMin(),mass.getMax())
for i in range(t.GetEntries()):
    t.GetEntry(i)
    mval = getattr(t,mvar)
    hm.Fill(mval )

h2m = RooDataHist(mass.GetName(),mass.GetName(),RooArgList(mass), hm)

#cruijff.fitTo(h2m,RooFit.Minos(1), RooFit.Offset(kTRUE))
#yuehong.fitTo(h2m,RooFit.Minos(1), RooFit.Offset(kTRUE))
#ipatia.fitTo(h2m,RooFit.Minos(1), RooFit.Offset(kTRUE))

fr = mass.frame()
h2m.plotOn(fr, RooFit.Binning(100))

indx = RooRealVar("indx", "indx", -0.1,0)
bkg = RooExponential("bkg","bkg", mass,indx)
fs = RooRealVar("fsig","fsig", 0 , 1)
#model = RooAddPdf("model","model",ipatia,bkg,fs)
ipatia.fitTo(h2m,RooFit.Minos(1), RooFit.Offset(kTRUE))
#cruijff.plotOn(fr, RooFit.LineColor(kGreen),RooFit.LineStyle(7))
#yuehong.plotOn(fr, RooFit.LineColor(kRed))#,RooFit.LineStyle(7))
ipatia.plotOn(fr)
fr.Draw()
print (a.getVal(),a2.getVal(),n.getVal(),n2.getVal(),l.getVal(), zeta.getVal())

#BREAK

#fr.Draw()
#l.setVal(-1.35)
#l.setConstant(kTRUE)
n2.setConstant(kTRUE)
a2.setVal(300)
a2.setConstant(kTRUE)
sigma0= RooRealVar("sigma0","sigma0",12,6,15)
mean0= RooRealVar("mean0","mean0",0)
res0 = RooGaussian("reso0","reso0",mass,mean0,sigma0)
ipa2 = RooFFTConvPdf("ipa2","ipa2",mass, ipatia,res0)
ipa_s.setMin(1)
zeta.setVal(0)
zeta.setConstant(kTRUE)
l.setVal(-2.35)
#l.setConstant(kTRUE)
beta.setMin(-1)
beta.setMax(1)
beta.setVal(0)
#beta.setConstant(kFALSE)
ipa2.fitTo(h2m,RooFit.Minos(1), RooFit.Offset(kTRUE))
ipa2.plotOn(fr,RooFit.LineColor(TColor.GetColor("#ff99cc")))
fr.Draw()


