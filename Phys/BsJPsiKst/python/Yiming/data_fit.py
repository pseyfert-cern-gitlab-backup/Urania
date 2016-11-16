from ROOT import *
from math import pi
gROOT.ProcessLine(".L ~diegoms/public/for_Yiming/NewTristanPhisFitB.cxx++")
gROOT.ProcessLine(".L ~diegoms/public/for_Yiming/NewTristanPhisFitBbar.cxx++")
from vasilis_weights import SCNoTrig as SC

#f_MC = TFile("~diegoms/vol5/BsJpsiPhi/MC/Bs2JpsiPhi_MC2012_ntupleB_20130904_smeared_sel.root")
#f_data =TFile("~yicai/jpsikst/testcut4.root")
f_data =TFile("~yicai/jpsikst/my_newtime_tuple2.root")
SC["tree"] = "DecayTree/DecayTree"
#t_MC = f_MC.Get(SC["tree"])
t_data = f_data.Get(SC["tree"])
SWEIGHT_WEIGHTS = 1  #for the "if SWE...."

fx = TFile("~/eraseme.root","recreate")

#t1 = t_MC.CopyTree("((mdau2-1020)<20)&&((mdau2-1020)>-20)&&trueid==531")### put the cut you want ... mdau2, or mdau1
t1 = t_data.CopyTree("((phi_1020_MM-1020)<20)&&((phi_1020_MM-1020)>-20)")

#time_mm = RooRealVar("B0_LOKI_DTF_CTAU","B0_LOKI_DTF_CTAU", 0.0003, 0.014)
time = RooRealVar("time_in_ps", "time_in_ps", 0.3, 14)
cThetaK = RooRealVar("helcosthetaK","helcosthetaK", -1,1)
cThetaL = RooRealVar("helcosthetaL","helcosthetaL", -1,1)
phi  = RooRealVar("B_s0_Phi", "B_s0_Phi" , -pi,pi)

if SWEIGHT_WEIGHTS:
    sWeight = RooRealVar("myweight","myweight",-10,10)
  #  charcut = RooRealVar("charcut","charcut",0)
  #datasetB = RooDataSet("dataB","dataB",t1,RooArgSet(cThetaK,cThetaL,phi,time,sWeight),RooFit.WeightVar("myweight"))
    datasetB = RooDataSet("dataB","dataB",t1,RooArgSet(cThetaK,cThetaL,phi,time,sWeight), "(1>0)","myweight") 
#  datasetBbar = RooDataSet("dataBbar","dataBbar",t1,RooArgSet(cThetaK,cThetaL,phi,time,sWeight))

else:
    datasetB = RooDataSet("dataB","dataB",t1,RooArgSet(cThetaK,cThetaL,phi,time))
#    datasetBbar = RooDataSet("dataBbar","dataBbar",t1,RooArgSet(cThetaK,cThetaL,phi,time,sWeight))

phi0 = RooRealVar("phi0","phi0",-pi,pi)
phipa = RooFormulaVar("phipa","phipa","phi0",RooArgList(phi0))
phipe = RooFormulaVar("phipe","phipe","phi0 - " +str(pi),RooArgList(phi0))
#phipe = RooRealVar("phipe","phipe",-pi,pi)

A02 = RooRealVar("A02","A02",0.5213,0.45,0.53) ## 0.40, 0.58)  #0.48 , 0.55
Ape2 = RooRealVar("Ape2","Ape2", 0.23, 0.15,0.40)##0.1,0.50)  #0.1,0.45
d0 = RooRealVar("d0","d0", 0)
dpa = RooRealVar("dpa","dpa", 0,10)
dpe = RooRealVar("dpe","dpe", -10,10)
Gamma = RooRealVar("Gamma","Gamma",0.35,0.75)##0.8)    #0.6,0.8
DG = RooRealVar("DG","DG",0.01,0.20)## 0.35)             # -0.2, 0.2
DMS = RooRealVar("DMS","DMS",17.8, 16, 22)    ## 16,19
A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(A02))
Ape = RooFormulaVar("Ape","Ape","sqrt(Ape2)", RooArgList(Ape2))

AS2 =  RooRealVar("AS2","AS2", 0.0001 , 0.1 )  ## new change  0.001,0.8
Apa = RooFormulaVar("Apa","Apa","sqrt(1-A02-Ape2-AS2)",RooArgList(A02,Ape2, AS2))

AS = RooFormulaVar("AS","AS","sqrt(AS2)", RooArgList(AS2))
dS =  RooRealVar("dS","dS", -10,10)
phiS = RooRealVar("phiS","phiS",-pi,pi)

coef_1 = RooRealVar("coef_1","coef_1",0.5)

FLAT_ACC  = 0
### Tristan Weights (Int (fij(Omega)* Epsilon(Omega)))
print "I am here."
#put weights here
if not FLAT_ACC:
    w2pe = RooRealVar("w2pe","w2pe", SC["2pe"])
    w0pe = RooRealVar("w0pe","w0pe", SC["0pe"])
    w2pa = RooRealVar("w2pa","w2pa", SC["2pa"])
    wpape = RooRealVar("wpape", "wpape", SC["pape"])
    w0pa = RooRealVar("w0pa","w0pa", SC["0pa"])
    w02 = RooRealVar("w02","w02",SC["02"])
    wS2 =  RooRealVar("wS2","wS2", SC["S2"])
    wS0  =  RooRealVar("wS0","wS0", SC["S0"])
    wSpa  =  RooRealVar("wSpa","wSpa", SC["Spa"])
    wSpe  =  RooRealVar("wSpe","wSpe", SC["Spe"])
##     w2pe = RooRealVar("w2pe","w2pe",  19.7721242002)  #Abs(A_pe)**2
##     w0pe = RooRealVar("w0pe","w0pe",  0.0586204920098)
##     w2pa = RooRealVar("w2pa","w2pa", 20.5966721636 )
##     wpape = RooRealVar("wpape", "wpape",   0.446851662638  )
##     w0pa = RooRealVar("w0pa","w0pa",  -1.82568282849 )
##     w02 = RooRealVar("w02","w02",  13.3476648864 )
##     #wSS = RooRealVar("wSS","wSS",......)#SC["02"])
else:
    w2pe = RooRealVar("w2pe","w2pe", 1.)
    w0pe = RooRealVar("w0pe","w0pe", 0.000)
    w2pa = RooRealVar("w2pa","w2pa",1.0)
    wpape = RooRealVar("wpape", "wpape", -0.000)
    w0pa = RooRealVar("w0pa", "w0pa", -0.000)
    w02 = RooRealVar("w02","w02",1)
    wS2 =  RooRealVar("wS2","wS2", 1)
    wS0  =  RooRealVar("wS0","wS0", 0)
    wSpa  =  RooRealVar("wSpa","wSpa", 0)
    wSpe  =  RooRealVar("wSpe","wSpe", 0)
    
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
    wS2.setMin(-1)
    wS2.setMax(+2)
    wS2.setVal(1)
    wSpe.setMin(-1)
    wSpe.setMax(+2)
    wSpe.setVal(1)
    wS0.setMin(-1)
    wS0.setMax(+2)
    wS0.setVal(1)
    wSpa.setMin(-1)
    wSpa.setMax(+2)
    wSpa.setVal(1)
    
fitterB = NewTristanPhisFitB("fitterB","fitterB",cThetaK,cThetaL,phi, time, Apa, Ape,AS,A0,dpa,dpe,dS,d0,phipa,phipe,phiS,phi0,Gamma,DG,DMS, w2pe,  wS2, w0pe,  wSpe, wpape,w2pa,  wSpa, w0pa, wS0, w02)
fitterBbar = NewTristanPhisFitBbar("fitterBar","fitterBar",cThetaK,cThetaL,phi, time, Apa, Ape,AS,A0,dpa,dpe,dS,d0,phipa,phipe,phiS,phi0,Gamma,DG,DMS, w2pe,  wS2, w0pe,  wSpe, wpape,w2pa,  wSpa, w0pa, wS0, w02)

fit_data = RooAddPdf("fitdata","fitdata",fitterB,fitterBbar,coef_1)
#fit_data.fitTo(datasetB, RooFit.Offset(kTRUE),RooFit.NumCPU(8))
fit_data.fitTo(datasetB, RooFit.Offset(kTRUE),RooFit.Minos(kTRUE),RooFit.NumCPU(8))

#cat = RooCategory("cat","cat")
#cat.defineType("B_data"), cat.defineType("Bbar_data")

#if SWEIGHT_WEIGHTS: allData = RooDataSet("all Data","all Data", RooArgSet(cThetaK,cThetaL, phi, time,sWeight), RooFit.Index(cat),RooFit.WeightVar(sWeight), RooFit.Import("B_data",datasetB),RooFit.Import("Bbar_data",datasetBbar))

#else: allData = RooDataSet("all Data","all Data", RooArgSet(cThetaK,cThetaL, phi, time), RooFit.Index(cat), RooFit.Import("B_data",datasetB), RooFit.Import("Bbar_data",datasetBbar))


def plot():
    c = TCanvas()
    c.Divide(2,2)
    c.cd(1)
    fr = cThetaK.frame()
    datasetB.plotOn(fr)
    fr.Draw()
    c.cd(2)
    fr2 = cThetaL.frame()
    datasetB.plotOn(fr2)
    fr2.Draw()
    c.cd(3)
    fr3 = phi.frame()
    datasetB.plotOn(fr3)
    fr3.Draw()
    c.cd(4)
    fr4 = time.frame()
    datasetB.plotOn(fr4)
    fit_data.plotOn(fr4)
    fr4.Draw()
    return c, fr, fr2, fr3, fr4
