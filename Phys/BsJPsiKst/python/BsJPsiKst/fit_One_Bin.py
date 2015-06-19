from ROOT import *
from math import pi
gROOT.ProcessLine(".L $BSJPSIKSTROOT/src/TristanJpsiKpi_J1.cxx++")
#gROOT.ProcessLine(".L $BSJPSIKSTROOT/python/BsJPsiKst/TristanJpsiKpi_J1.cxx++")
f1=TFile("~/NTuplesFast/Carlos_NS_sw/2011p_826_861.root")
tree1=f1.Get("DecayTree")
f2=TFile("~/NTuplesFast/Carlos_NS_sw/2011n_826_861.root")
tree2=f2.Get("DecayTree")
#BREAK
from parameters import *
nws = WeightsBd["2011p_826_861"]
cspval = myCsp4[0] 
###################  CONSTRUCTING THE MODEL

As2 = RooRealVar("As2","As2",0.,.1)

fL = RooRealVar("fL","fL",0.3,0.7)
fpa = RooRealVar("fpa","fpa", 0.1,0.3)

CThetaL = RooRealVar("helcosthetaL","helcosthetaL", -1,1)
CThetaK = RooRealVar("helcosthetaK","helcosthetaL", -1,1)
Phi = RooRealVar("B0_Phi","B0_Phi", -pi,pi)

deltaPa = RooRealVar("deltaPa","deltaPa",-2.*pi,2*pi)
deltaPe = RooRealVar("deltaPe","deltaPe",1,  -2*pi,2*pi)
deltaS  = RooRealVar("deltaS" ,"deltaS" ,-2*pi,2*pi)

deltaPe_neg = RooFormulaVar("delta2Pe","delta2Pe","deltaPe + " +str(pi), RooArgList(deltaPe))
w00 = RooRealVar("w00","w00",nws['00'])
wpe2 = RooRealVar("wpe2","wpe2",nws["pe2"])
wpa2 = RooRealVar("wpa2","wpa2",nws["pa2"])
CSP = RooRealVar("CSP","CSP", cspval)
wS2 = RooRealVar("wS2","wS2",nws["SS"])
w0pa = RooRealVar("w0pa","w0pa",nws["0pa"])
w0pe = RooRealVar("w0pe","w0pe",nws["0pe"])
wSpe = RooRealVar("wSpe","wSpe",nws["Spe"])
wSpa = RooRealVar("wSpa","wSpa",nws["Spa"])
wS0 = RooRealVar("wS0","wS0",nws["S0"])
wpape = RooRealVar("wpape","wpape",nws["pape"])


model=TristanJpsiKpi_J1("model","model",  CThetaK,CThetaL,Phi,As2,fL,fpa,deltaPa,deltaPe,deltaS,CSP,wpe2,wS2,w0pe,wSpe,wpape,wpa2,wSpa,w0pa,wS0,w00)

model2=TristanJpsiKpi_J1("model2","model2",CThetaK,CThetaL,Phi,As2,fL,fpa,deltaPa,deltaPe_neg,deltaS,CSP,wpe2,wS2,w0pe,wSpe,wpape,wpa2,wSpa,w0pa,wS0,w00)


datan = RooDataSet("negative", "negative",tree2,RooArgSet(CThetaK,CThetaL,Phi))
datap = RooDataSet("positive", "positive",tree1,RooArgSet(CThetaK,CThetaL,Phi))


cat = RooCategory("cat","cat")
cat.defineType("P"), cat.defineType("N")
allData = RooDataSet("all Data","all Data", RooArgSet(CThetaK,CThetaL, Phi), RooFit.Index(cat), RooFit.Import("P",datap),RooFit.Import("N",datan))
fitter = RooSimultaneous("fitter", "fitter", cat)
fitter.addPdf(model,"P")
fitter.addPdf(model2,"N")

def fitAll(minos) : fitter.fitTo(allData,RooFit.Minos(minos), RooFit.NumCPU(3))
def fitP(minos): model.fitTo(datap,RooFit.Minos(minos), RooFit.NumCPU(3))
def fitB(minos): model2.fitTo(datan,RooFit.Minos(minos), RooFit.NumCPU(3))



def test(model,data):
    res = model.fitTo(data,RooFit.Minos(kTRUE))#, RooFit.Range("REDUCED"))
    Angframe = CThetaK.frame()
    data.plotOn(Angframe)
    model.plotOn(Angframe)
    Angframe.Draw()
    return res, Angframe

#w_1 = test(model)
#w_2 = test(model2)

################ DRAWING 
