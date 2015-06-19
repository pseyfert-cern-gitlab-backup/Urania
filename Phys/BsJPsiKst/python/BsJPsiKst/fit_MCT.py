from ROOT import *
from math import pi
gROOT.ProcessLine(".L $BSJPSIKSTROOT/src/TristanJpsiKpi_J1.cxx++")
#gROOT.ProcessLine(".L $BSJPSIKSTROOT/python/BsJPsiKst/TristanJpsiKpi_J1.cxx++")
f=TFile("~/w7folder/NTuples/Bd_MCT_2014.root")
tree=f.Get("T")
f1=TFile("/tmp/trash.root","recreate")
tree2 = tree.CopyTree("k1ID<0 && (pi1ID!=0) && (mu1ID!=0) && (mu2ID)!=0")
tree1 = tree.CopyTree("k1ID>0 && (pi1ID!=0) && (mu1ID!=0) && (mu2ID)!=0")

###################  CONSTRUCTING THE MODEL

As2 = RooRealVar("As2","As2",0.,.1)

fL = RooRealVar("fL","fL",0.3,0.7)
fpa = RooRealVar("fpa","fpa", 0.1,0.3)

CThetaL = RooRealVar("helcosthetaL","helcosthetaL", -1,1)
CThetaK = RooRealVar("helcosthetaK","helcosthetaL", -1,1)
Phi = RooRealVar("helphi","helphi", -pi,pi)

deltaPa = RooRealVar("deltaPa","deltaPa",0,2*pi)
deltaPe = RooRealVar("deltaPe","deltaPe",0,2*pi)
deltaS  = RooRealVar("deltaS" ,"deltaS" ,0.)#9,0.,2*pi)

deltaPe_neg = RooFormulaVar("delta2Pe","delta2Pe","deltaPe + " +str(pi), RooArgList(deltaPe))
w00 = RooRealVar("w00","w00",1)
wpe2 = w00
wpa2 = w00
CSP = w00
wS2 = w00
w0pa = RooRealVar("w0pa","w0pa",0)
w0pe = w0pa
wSpe = w0pa
wSpa = w0pa
wS0 = w0pa
wpape = w0pa

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

def doContour():
    deltaPa.setConstant(kFALSE)
    deltaPe.setConstant(kFALSE)
    fitAll(0)
    h = TH2F("a","a", 110, -pi,pi, 110,-pi,pi)
    #nll = fitter.createNLL(allData)
    nll = model.createNLL(datap, RooFit.NumCPU(3))
    deltaPa.setMin(-pi)
    deltaPe.setMin(-pi)
    deltaPa.setConstant(kTRUE)
    deltaPe.setConstant(kTRUE)
    nllvals = []
    for i in range(100):
        x = -pi + 0.01*i*2*pi
        deltaPa.setVal(x)
        for j in range(100):
            y = -pi + 0.01*2*pi*j
            deltaPe.setVal(y)
            LLval = nll.getVal()
            nllvals.append(LLval)
            h.Fill(deltaPa.getVal(),deltaPe.getVal(),LLval)
    nllvals.sort()
    LL0 = nllvals[0]
    for i in range(h.GetNbinsX()):
        for j in range(h.GetNbinsY()):
            h.SetBinContent(i+1,j+1, max(h.GetBinContent(i+1,j+1)-LL0,0))
    return h, nllvals
