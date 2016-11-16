
from ROOT import *
from math import pi
gROOT.ProcessLine(".L NewTristanPhisFitB.cxx++")
gROOT.ProcessLine(".L NewTristanPhisFitBbar.cxx++")
from vasilis_weights import SCNoTrig as SC

f_MC = TFile("~diegoms/vol5/BsJpsiPhi/MC/Bs2JpsiPhi_MC2012_ntupleB_20130904_smeared_sel.root")
SC["tree"] = "DecayTree"
t_MC = f_MC.Get(SC["tree"])

TIME_ACC_WEIGHTS = ""#B_velo_eff_weight_no_trigger"
VELO_WEIGHTS = TIME_ACC_WEIGHTS

fx = TFile("~/eraseme.root","recreate")

t1 = t_MC.CopyTree("((mdau2-1020)<20)&&((mdau2-1020)>-20)&&trueid==531")### put the cut you want ... mdau2, or mdau1

time = RooRealVar("truetime","truetime", 0.4, 14)
cThetaK = RooRealVar("helcosthetaK","helcosthetaK", -1,1)
cThetaL = RooRealVar("helcosthetaL","helcosthetaL", -1,1)
phi  = RooRealVar("B_phi", "B_phi" , -pi,pi)

if VELO_WEIGHTS:
    velo = RooRealVar(TIME_ACC_WEIGHTS,TIME_ACC_WEIGHTS,-10,10)
    datasetB1 = RooDataSet("dataB1","dataB1",t1,RooArgSet(cThetaK,cThetaL,phi,time,velo))

else:
    datasetB1 = RooDataSet("dataB1","dataB1",t1,RooArgSet(cThetaK,cThetaL,phi,time))


phi0 = RooRealVar("phi0","phi0",-pi,pi)
phipa = RooFormulaVar("phipa","phipa","phi0",RooArgList(phi0))
phipe = RooFormulaVar("phipe","phipe","phi0 - " +str(pi),RooArgList(phi0))
#phipe = RooRealVar("phipe","phipe",-pi,pi)

A02 = RooRealVar("A02","A02",0.5213, 0.48, 0.58)  #0.48 , 0.55
Ape2 = RooRealVar("Ape2","Ape2", 0.23, 0.1,0.45)
d0 = RooRealVar("d0","d0", 0)
dpa = RooRealVar("dpa","dpa", 0,10)
dpe = RooRealVar("dpe","dpe", -10,10)
Gamma = RooRealVar("Gamma","Gamma",0.6,0.8)
DG = RooRealVar("DG","DG",0.01, 0.18)  # -0.2, 0.2
DMS = RooRealVar("DMS","DMS",17.8)#, 16, 19)
A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(A02))
Ape = RooFormulaVar("Ape","Ape","sqrt(Ape2)", RooArgList(Ape2))
Apa = RooFormulaVar("Apa","Apa","sqrt(1-A02-Ape2)",RooArgList(A02,Ape2))
FLAT_ACC  = 0
### Tristan Weights (Int (fij(Omega)* Epsilon(Omega)))
print "I am here."
#put weights here
if not FLAT_ACC:
##     w2pe = RooRealVar("w2pe","w2pe", SC["2pe"])
##     w0pe = RooRealVar("w0pe","w0pe", SC["0pe"])
##     w2pa = RooRealVar("w2pa","w2pa", SC["2pa"])
##     wpape = RooRealVar("wpape", "wpape", SC["pape"])
##     w0pa = RooRealVar("w0pa","w0pa", SC["0pa"])
##     w02 = RooRealVar("w02","w02",SC["02"])

    w2pe = RooRealVar("w2pe","w2pe",7.49306674434 )#19.7721242002)#Abs(A_pe)**2
    w0pe = RooRealVar("w0pe","w0pe", -0.210262999226 )# 0.0586204920098)
    w2pa = RooRealVar("w2pa","w2pa", 8.47749100138 )#20.5966721636 )
    wpape = RooRealVar("wpape", "wpape", -0.278820292866 )#  0.446851662638  )
    w0pa = RooRealVar("w0pa","w0pa", 1.74572911146 )# -1.82568282849 )
    w02 = RooRealVar("w02","w02", 7.10141633906 )# 13.3476648864 )
    #wSS = RooRealVar("wSS","wSS",......)#SC["02"])
else:
    w2pe = RooRealVar("w2pe","w2pe", 1.)
    w0pe = RooRealVar("w0pe","w0pe", 0.000)
    w2pa = RooRealVar("w2pa","w2pa",1.0)
    wpape = RooRealVar("wpape", "wpape", -0.000)
    w0pa = RooRealVar("w0pa", "w0pa", -0.000)
    w02 = RooRealVar("w02","w02",1)

def setFlat():
    w2pe.setMin(-1), w2pe.setMax(+2)
    w2pe.setVal(1)
    w2pa.setMin(-1)
    w2pa.setMax(+2)
    w2pa.setVal(1)
    wpape.setMin(-1)
    wpape.setMax(+2)
    wpape.setVal(0)
    w0pe.setMin(-1)
    w0pe.setMax(+2)
    w0pe.setVal(0)
    w0pa.setMin(-1)
    w0pa.setMax(+2)
    w0pe.setVal(0)
    w02.setMin(-1)
    w02.setMax(+2)
    w02.setVal(1)

fitterB1 = NewTristanPhisFitB("fitterB1","fitterB1",cThetaK,cThetaL,phi, time, Apa, Ape,A0,dpa,dpe,d0, phipa,phipe,phi0,Gamma,DG,DMS, w2pe,w0pe,w2pa,wpape,w0pa, w02)

cat = RooCategory("cat","cat")
cat.defineType("B_MC")

if VELO_WEIGHTS: allData = RooDataSet("all Data","all Data", RooArgSet(cThetaK,cThetaL, phi, time,velo), RooFit.Index(cat),RooFit.WeightVar(velo), RooFit.Import("B_MC",datasetB1))

else: allData = RooDataSet("all Data","all Data", RooArgSet(cThetaK,cThetaL, phi, time), RooFit.Index(cat), RooFit.Import("B_MC",datasetB1))

fitter = RooSimultaneous("fitter", "fitter", cat)
fitter.addPdf(fitterB1,"B_MC")

def fitAll(minos) : fitter.fitTo(allData,RooFit.Minos(minos), RooFit.NumCPU(8))
fitAll(0)
