from ROOT import *

gROOT.ProcessLine(".x ../../src/TimeDependent/TwoBodyMassModel.cxx++")

fin = TFile("/scratch27/julian.garcia/Bs2KpiKpi/fast_ntuples/MassPlaneMLAU.root")
tin = fin.Get("AnalysisTree")
fout = TFile("tmp.root","recreate")
tout = tin.CopyTree("")

m1 = RooRealVar("m1","M(K^{+}#pi^{-})",750.,1600.,"MeV/c^{2}")
m2 = RooRealVar("m2","M(K^{-}#pi^{+})",750.,1600.,"MeV/c^{2}")
weight = RooRealVar("weight","weight",-20.,20.)

#f_VV = RooRealVar("f_VV","f_VV",0,1)
#f_Swave = RooRealVar("f_Swave","f_Swave",0,1)
#f_SS = RooRealVar("f_SS","f_SS",0,1)
#D_SVVS = RooRealVar("D_SVVS","D_SVVS",-1,1)
#f_VTTV = RooRealVar("f_VTTV","f_VTTV",0,1)
#f_TT = RooRealVar("f_TT","f_TT",0,1)
#D_STTS = RooRealVar("D_STTS","D_STTS",-1,1)
#D_VTTV = RooRealVar("D_VTTV","D_VTTV",-1,1)
#f00 = RooFormulaVar("f00","f00","(1-f_VV)*f_Swave*f_SS",RooArgList(f_VV,f_Swave,f_SS))
#f01 = RooFormulaVar("f01","f01","(1-f_VV)*f_Swave*(1-f_SS)*0.5*(1+D_SVVS)",RooArgList(f_VV,f_Swave,f_SS,D_SVVS))
#f02 = RooFormulaVar("f02","f02","(1-f_VV)*(1-f_Swave)*(1-f_VTTV)*(1-f_TT)*0.5*(1+D_STTS)",RooArgList(f_VV,f_Swave,f_VTTV,f_TT,D_STTS))
#f10 = RooFormulaVar("f10","f10","(1-f_VV)*f_Swave*(1-f_SS)*0.5*(1-D_SVVS)",RooArgList(f_VV,f_Swave,f_SS,D_SVVS))
#f11 = RooFormulaVar("f11","f11","f_VV",RooArgList(f_VV))
#f12 = RooFormulaVar("f12","f12","(1-f_VV)*(1-f_Swave)*f_VTTV*0.5*(1+D_VTTV)",RooArgList(f_VV,f_Swave,f_VTTV,D_VTTV))
#f20 = RooFormulaVar("f20","f20","(1-f_VV)*(1-f_Swave)*(1-f_VTTV)*(1-f_TT)*0.5*(1-D_STTS)",RooArgList(f_VV,f_Swave,f_VTTV,f_TT,D_STTS))
#f21 = RooFormulaVar("f21","f21","(1-f_VV)*(1-f_Swave)*f_VTTV*0.5*(1-D_VTTV)",RooArgList(f_VV,f_Swave,f_VTTV,D_VTTV))
#f22 = RooFormulaVar("f22","f22","(1-f_VV)*(1-f_Swave)*(1-f_VTTV)*f_TT",RooArgList(f_VV,f_Swave,f_VTTV,f_TT))

"""logf00 = RooRealVar("logf00","logf00",2,18)
logf01 = RooRealVar("logf01","logf01",2,10)
logf02 = RooRealVar("logf02","logf02",-1,5)
logf10 = RooRealVar("logf10","logf10",2,10)
logf12 = RooRealVar("logf12","logf12",-5,0)
logf20 = RooRealVar("logf20","logf20",-1,5)
logf21 = RooRealVar("logf21","logf21",-5,0)
logf22 = RooRealVar("logf22","logf22",-5,0)
f00 = RooFormulaVar("f00","f00","exp(logf00)",RooArgList(logf00))
f01 = RooFormulaVar("f01","f01","exp(logf01)",RooArgList(logf01))
f02 = RooFormulaVar("f02","f02","exp(logf02)",RooArgList(logf02))
f10 = RooFormulaVar("f10","f10","exp(logf01)",RooArgList(logf01))
f11 = RooRealVar("f11","f11",1.)
f12 = RooFormulaVar("f12","f12","exp(logf12)",RooArgList(logf12))
f20 = RooFormulaVar("f20","f20","exp(logf02)",RooArgList(logf02))
f21 = RooFormulaVar("f21","f21","exp(logf12)",RooArgList(logf12))
f22 = RooFormulaVar("f22","f22","exp(logf22)",RooArgList(logf22))"""

f00 = RooRealVar("f00","f00",0,60)
f01 = RooRealVar("f01","f01",0,30)
f02 = RooRealVar("f02","f02",0,5)
f11 = RooRealVar("f11","f11",5)
f12 = RooRealVar("f12","f12",0,5)
f22 = RooRealVar("f22","f22",0,5)

alass = RooRealVar("alass","alass",35.2,0.1,100.)#0.003,0.0008,0.01)
blass = RooRealVar("blass","blass",1.027,0.1,200.)#0.003,0.0008,0.01)
Class = RooRealVar("Class","Class",-1.e-3,-1.,1.)
ms = RooRealVar("ms","ms",1330.)#,800.,1600.)
gs = RooRealVar("gs","gs",300.,150.,600.)
alass_gc = RooGaussian("alass_gc","alass_gc",alass,RooFit.RooConst(3.83e-3),RooFit.RooConst(1.1e-4))
blass_gc = RooGaussian("blass_gc","blass_gc",blass,RooFit.RooConst(2.86e-3),RooFit.RooConst(2.2e-4))
ms_gc = RooGaussian("ms_gc","ms_gc",ms,RooFit.RooConst(1456.7),RooFit.RooConst(3.9))
gs_gc = RooGaussian("gs_gc","gs_gc",gs,RooFit.RooConst(323.),RooFit.RooConst(11.))

c1 = RooRealVar("c1","c1",0,-10,10)
c2 = RooRealVar("c2","c2",0,-10,10)
c3 = RooRealVar("c3","c3",0,-10,10)
c4 = RooRealVar("c4","c4",0,-10,10)
c5 = RooRealVar("c5","c5",0,-10,10)
c6 = RooRealVar("c6","c6",0,-10,10)
c7 = RooRealVar("c7","c7",0,-10,10)
c8 = RooRealVar("c8","c8",0,-10,10)
c9 = RooRealVar("c9","c9",0,-10,10)

f00.setVal(0.00853231464149)
f01.setVal(0.241423330772)
f02.setVal(0.032490188411)
f12.setVal(2.48472136602)
f22.setVal(0.805319361029)
c1.setVal(-0.434327337925)
c2.setVal(-0.295564102912)
c3.setVal(-0.0427751032878)
c4.setVal(-0.0430223299716)

mv = RooRealVar("mv","mv",895.81,890.,900.)
gv = RooRealVar("gv","gv",47.4,45.,55.)
mt = RooRealVar("mt","mt",1432.4,1425.,1440.)
gt = RooRealVar("gt","gt",109.,95.,140.)
mv_gc = RooGaussian("mv_gc","mv_gc",mv,RooFit.RooConst(895.81),RooFit.RooConst(0.19))
gv_gc = RooGaussian("gv_gc","gv_gc",gv,RooFit.RooConst(47.4),RooFit.RooConst(0.6))
mt_gc = RooGaussian("mt_gc","mt_gc",mt,RooFit.RooConst(1432.4),RooFit.RooConst(1.3))
gt_gc = RooGaussian("gt_gc","gt_gc",gt,RooFit.RooConst(109.),RooFit.RooConst(5.))

data = RooDataSet("data","data",tout,RooArgSet(m1,m2,weight),"","weight")



#for c in [c1,c2,c3,c4,c5,c6,c7,c8,c9]: c.setConstant()
#for c in [c3,c4,c8,c9]: c.setConstant()
for c in [c5,c6,c7,c8,c9]: c.setConstant()
for mg in [mv,gv,mt,gt]: mg.setConstant()
#for fij in [f00,f01,f02,f12,f22]: fij.setConstant()

model_ = TwoBodyMassModel("model_","model_",f00,f01,f01,f02,f02,f11,f12,f12,f22,m1,m2,c1,c2,c3,c4,c5,c6,c7,c8,c9,ms,mv,gv,mt,gt)
#model = RooProdPdf("model","model",RooArgList(model_,mv_gc,gv_gc,mt_gc,gt_gc))

#for f in [f01,f02,f12,f11,f22]: f.setVal(0)
model_.fitTo(data,RooFit.NumCPU(30),RooFit.SumW2Error(kFALSE),RooFit.Minos(0),RooFit.Timer(kTRUE))

fr1 = m1.frame()
fr2 = m2.frame()
data.plotOn(fr1,RooFit.Binning(40))
data.plotOn(fr2,RooFit.Binning(40))
model_.plotOn(fr1)
model_.plotOn(fr2)

fr12 = RooPlot(m1,m2)
data.plotOn(fr12)
model_.plotOn(fr12)

for par in [f00,f01,f02,f12,f22,c1,c2,c3,c4,c5,c6,c7,c8,c9,mv,gv,mt,gt]: print par.GetName()+'.setVal('+str(par.getVal())+')'

c = TCanvas("c","c",1000,800)
fr1.Draw()

c.Print("MassPlanePlot.root")
c.Print("MassPlanePlot.pdf")
