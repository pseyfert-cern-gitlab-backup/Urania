from ROOT import *
from PDF_2013_Asym import *
from Urania import *
from Cuts2013 import *
AccessPackage("Bs2MuMu")
import ipa_params
import Lb_params
from constrain_funcs import *
weightMC = RooRealVar("wMC","wMC", -10000, 10000)
massB11 = SignalMass("signal11")
ibin = "tightW"
gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")


massB11.ipa_lambda.setVal(ipa_params.Bin[ibin]["l"])
massB11.ipa_lambda.setConstant(1)#ipa_params.Bin[ibin]["l"])
massB11.a1_cb.setVal(ipa_params.Bin[ibin]["a"])
massB11.a1_cb.setConstant(1)
massB11.a2_cb.setVal(ipa_params.Bin[ibin]["a2"])
massB11.a2_cb.setConstant(1)
massB11.ncb1.setVal(ipa_params.Bin[ibin]["n"])
massB11.ncb1.setConstant(1)
massB11.ncb2.setVal(ipa_params.Bin[ibin]["n2"])
massB11.ncb2.setConstant(1)

massB12 = SignalMass("signal12")
massB12.ipa_lambda.setVal(ipa_params.Bin[ibin]["l"])
massB12.ipa_lambda.setConstant(1)#ipa_params.Bin[ibin]["l"])
massB12.a1_cb.setVal(ipa_params.Bin[ibin]["a"])
massB12.a1_cb.setConstant(1)
massB12.a2_cb.setVal(ipa_params.Bin[ibin]["a2"])
massB12.a2_cb.setConstant(1)
massB12.ncb1.setVal(ipa_params.Bin[ibin]["n"])
massB12.ncb1.setConstant(1)
massB12.ncb2.setVal(ipa_params.Bin[ibin]["n2"])
massB12.ncb2.setConstant(1)

#OUTPUT = "YIELDS"
OUTPUT = "RATIO"

f11 = TFile("~/NTuplesFast/Tuple_BsJPsiKst2011.root")
t11b = f11.Get("DecayTree")
f12 = TFile("~/NTuplesFast/Tuple_BsJPsiKst2012.root")
t12b = f12.Get("DecayTree")

f2 = TFile("/tmp/eraseme.root", "recreate")
t11 = t11b.CopyTree(cuts_loose_2011 + "&& abs(Kst_892_0_MM-896) < 40.")
t12 = t12b.CopyTree(cuts_loose_2012 + "&& abs(Kst_892_0_MM-896) < 40.")

dataset11 = RooDataSet("2011","2011",t11,RooArgSet(Mass, weightMC),"100000000000000 > 0", "wMC")
dataset12 = RooDataSet("2012","2012",t12,RooArgSet(Mass, weightMC),"100000000000000 > 0", "wMC")

Nmax = t11.GetEntries() + t12.GetEntries()
bkgmodel11 = FullBackground("Bkg11")
bkgmodel12 = FullBackground("Bkg12")


class LambdaDecay:
	def __init__(self, name = "Lambda"):
		self.name = name
		self.theta = RooRealVar(name + "theta",name + "theta",-200, -1000,-1)
		self.alpha = RooRealVar(name + "alpha",name + "alpha",1, 0.1, 10)
		self.offset = RooRealVar(name + "mean",name + "mean", 5600, 5450, 8000)
		self.mean = self.offset
		self.beta = RooRealVar(name + "beta", name + "beta", 2,-7,7)
		self.mass_model = RooAmorosoPdf(name + "mass_model", name+ "mass_model" ,Mass, self.offset, self.theta, self.alpha, self.beta)
	def set(self, var, value):
		getattr(self, var).setVal(value)
		getattr(self, var).setConstant(kTRUE)

LbpKmodel = LambdaDecay("Lb2JpsipK")
Lbppimodel = LambdaDecay("Lb2Jpsippi")

for key in Lb_params.LbpK[ibin].keys():
	LbpKmodel.set(key,Lb_params.LbpK[ibin][key])
	Lbppimodel.set(key,Lb_params.Lbppi[ibin][key])

nd = RooRealVar("nBd","nBd", 0.5*(Nmax),Nmax)
if OUTPUT == "YIELDS" : ns = RooRealVar("nBs","nBs", 0.,0.5*(Nmax))
else:
    RBs = RooRealVar("RBs","RBs",0,0.1)
    ns = RooFormulaVar("nBs", "nBs", "nBd*RBs", RooArgList(RBs,nd))
nbkg11 = RooRealVar("n_bkg11","n_bkg11", 0.,0.5*Nmax)
nbkg12 = RooRealVar("n_bkg12","n_bkg12", 0.,0.5*Nmax)
fd11 = RooRealVar("fd11","fd11", 0.3,0.1,0.5)
fs11 = RooRealVar("fs11","fs11", 0.3,0.1,0.5)
fb11 = RooRealVar("fb11","fb11", 0.3,0.1,0.5)
nd11 = RooFormulaVar("nd11","nd11", "fd11*nBd", RooArgList(fd11,nd))
nd12 = RooFormulaVar("nd12","nd12", "(1-fd11)*nBd", RooArgList(fd11,nd))
ns11 = RooFormulaVar("ns11","ns11", "fs11*nBs", RooArgList(fs11,ns))
ns12 = RooFormulaVar("ns12","ns12", "(1-fs11)*nBs", RooArgList(fs11,ns))


##nLbK11 = RooRealVar("nLbK11","nLbK11", 0.,0.5*(Nmax)*LAMBDA)
##nLbpi11 = RooRealVar("nLbpi11","nLbpi11", 0.,0.5*(Nmax)*LAMBDA)
##nLbK11.setConstant(not LAMBDA)
##nLbpi11.setConstant(not LAMBDA)
##nLbK12 = RooRealVar("nLbK12","nLbK12", 0.,0.5*(Nmax)*LAMBDA)
##nLbpi12 = RooRealVar("nLbpi12","nLbpi12", 0.,0.5*(Nmax)*LAMBDA)
##nLbK12.setConstant(not LAMBDA)
##nLbpi12.setConstant(not LAMBDA)
delta_m.setMin(70)
delta_m.setMax(100)
delta_m.setConstant(kFALSE)
###### Gaussian-constrain the \Lambdas
nLbK12, mk12, sk12, cons_nLbK12 = createConst(19.7, 17.7, "LbK12", signed = 1)
nLbK11, mk11, sk11, cons_nLbK11 = createConst(5.0, 2.9, "LbK11", signed = 1)
nLbp11, mp11, sp11, cons_nLbp11 = createConst(16.2, 4.9, "Lbp11", signed = 1)
nLbp12, mp12, sp12, cons_nLbp12 = createConst(33.2, 8.4, "Lbp12", signed = 1)
cat = RooCategory("year", "year")
cat.defineType("2011")
cat.defineType("2012")

model11 = RooAddPdf("model11","model11" ,RooArgList(massB11.sigBs,massB11.sigBd,bkgmodel11.massbkg, LbpKmodel.mass_model, Lbppimodel.mass_model),RooArgList(ns11,nd11,nbkg11, nLbK11, nLbp11))
model12 = RooAddPdf("model12","model12" ,RooArgList(massB12.sigBs,massB12.sigBd,bkgmodel12.massbkg, LbpKmodel.mass_model, Lbppimodel.mass_model),RooArgList(ns12,nd12,nbkg12, nLbK12, nLbp12))

model = RooSimultaneous("model","model", cat)
model.addPdf(model11, "2011")
model.addPdf(model12, "2012")
data = RooDataSet("data","data", RooArgSet( Mass,weightMC), RooFit.Index(cat), RooFit. Import("2011", dataset11), RooFit.Import("2012", dataset12),RooFit.WeightVar(weightMC.GetName()))

#summaryConstraints = RooArgSet(cons_nLbK12,cons_nLbK11,  cons_nLbp12, cons_nLbp11)  
nLbK12.setVal(nLbK12.getMin())
nLbK12.setConstant(kTRUE)
nLbK11.setVal(nLbK11.getMin())
nLbK11.setConstant(kTRUE)
nLbp12.setVal(nLbp12.getMin())
nLbp12.setConstant(kTRUE)
nLbp11.setVal(nLbp11.getMin())
nLbp11.setConstant(kTRUE)

res = model.fitTo(data, RooFit.Minos(kFALSE), RooFit.SumW2Error(kTRUE), RooFit.Offset(kTRUE))#,RooFit.ExternalConstraints(summaryConstraints))

#11  nBd          2.08464e+05   4.62520e+02   1.50849e-02   1.10297e+00
#12  nBs          1.82433e+03   5.12401e+01   2.87038e-03  -2.69653e+01
## 5  RBs          8.74938e-03   2.46379e-04  


#Feb 23
 #13  nBd          2.08467e+05   4.62524e+02   1.49618e-02   1.10306e+00
 #  5  RBs          8.75152e-03   2.46548e-04   6.75327e-03  -2.17144e+00


## pm40  1  RBs          8.35410e-03   2.50458e-04   6.89633e-05  -2.15723e+00
