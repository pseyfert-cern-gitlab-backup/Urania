from ROOT import *
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *

gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")
## Usamos a distribucao Hiperbolica Geralicada como modelo
## de resolucao. Para isso colhemos a Ipatia, e eliminamos
f = TFile("Masshistos_nopi0.root")
#t = f.Get("PVChecker/10")
h = f.Get("BVC")#TH1F("DZ","DZ", 100, -0.8, 0.8)
mass = RooRealVar("mass","mass",400,600)
h2 = RooDataHist("massH", "massH", RooArgList(mass), h)

a2 = RooRealVar("a2","a2",100) ### Ponhendo os parametros da CB lonje, quedamonos so co core
a = RooRealVar("a","a" ,100) ### Ponhendo os parametros da CB lonje, quedamonos so co core
n = RooRealVar("n","n",1.)#,0.8,10)
n2 = RooRealVar("n2","n2",1)#.,0.8,60)

ipa_s = RooRealVar("ipa_s","ipa_s", 30,10,1000)
##ipa_m = RooRealVar("ipa_m","ipa_m",495,490,500)
ipa_m = RooRealVar("ipa_m","ipa_m",480,520)
##beta = RooRealVar("beta","beta",0, -1e-03,1e03)#
beta = RooRealVar("beta","beta",0,-2000,1e03)
zeta = RooRealVar("zeta","zeta",1e-03, 0, 5)
ipa_l = RooRealVar("l","l",-2,-6,6)
ipatia = RooIpatia2("Ipatia","Ipatia",mass,ipa_l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
ipatia.fitTo(h2)

fr = mass.frame()
h2.plotOn(fr)
ipatia.plotOn(fr)

fr.GetYaxis().SetTitle("Events /2 ( MeV/c^{2} )")
fr.GetXaxis().SetTitle("M(#pi^{0} #mu^{+} #mu^{-} ) [MeV/c^{2}]");

fr.Draw()
