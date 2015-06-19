from ROOT import *
from math import *
# from BsKstKstPDF import *
from PDF_builder_self_v2 import *


gStyle.SetPadBottomMargin(0.2)
gStyle.SetPadLeftMargin(0.2)
gStyle.SetTitleYOffset(1.06)
CHI2 = 1
markerSize = 1.4

### IMPORT DATA
########################################################################################################################

file_data_Bs = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_generated_MC11_angles.root")
t_Bs = file_data_Bs.Get("T")



### DATASETS
########################################################################################################################

CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")
# Phi.SetNameTitle("Phi_pi","Phi_pi")
# Phi.setMin(0.)
# Phi.setMax(2*pi)

dataset_Bs = RooDataSet("data_Bs","data_Bs",t_Bs,RooArgSet(CTh1,CTh2,Phi,m1,m2))


### ANGULAR MODEL
########################################################################################################################

########### Bs MC ###########

Apa_Bs = 0.5
Ape_Bs = 0.33
A0_Bs  = 0.8
dpa_Bs = 3.14
dpe_Bs = 0.#3.14

a02_Bs = A0_Bs*A0_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
apa2_Bs = Apa_Bs*Apa_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
ape2_Bs = Ape_Bs*Ape_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)


Ang_Bs = AngularPDF("Bs")
Ang_Bs.OwnPhys()
# Ang_Bs.modParam("m_kst",8.95279e+02 , 1, kTRUE)
# Ang_Bs.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bs.modParam("Bs2",0.,0.,kTRUE)
Ang_Bs.modParam("MBs",5366.3,0.,kTRUE)


Ang_Bs.modParam("c1_th",0.,0.,kTRUE)
Ang_Bs.modParam("c2_th",0.,0.,kTRUE)
Ang_Bs.modParam("c3_th",0.,0.,kTRUE)
Ang_Bs.modParam("c4_th",0.,0.,kTRUE)
Ang_Bs.modParam("y",1.,0.,kTRUE)
Ang_Bs.modParam("c1_ph",0.,0.,kTRUE)
Ang_Bs.modParam("c2_ph",1.5,0.,kTRUE)
Ang_Bs.modParam("c3_ph",0.,0.,kTRUE)


Ang_Bs.modParam("Asm2",0.,0.,kTRUE)
Ang_Bs.modParam("dsm",0.,0.,kTRUE)
Ang_Bs.modParam("Asp2",0.,0.,kTRUE)
Ang_Bs.modParam("dsp",0.,0.,kTRUE)
Ang_Bs.modParam("Ass2",0.,0.,kTRUE)
Ang_Bs.modParam("dss",0.,0.,kTRUE)
Ang_Bs.modParam("dpe",0.,0.,kTRUE)
# Ang_Bs.modParam("dpe",dpe_Bs,0.,kTRUE)
# Ang_Bs.modParam("dpa",dpa_Bs,0.,kTRUE)
# Ang_Bs.modParam("fL",a02_Bs,0.,kTRUE)
# Ang_Bs.modParam("fpa",apa2_Bs,0.,kTRUE)


Ang_Bs.modParam("normP",1./433923.65279,0,kTRUE)
Ang_Bs.modParam("normS",1./771976.068198,0,kTRUE)
Ang_Bs.modParam("normSS",1./1373391.4871,0,kTRUE)





Ang_Bs.make()


### FIT
########################################################################################################################
# m1.setRange("ref",m1.getMin(),m1.getMax())
# m2.setRange("ref",m2.getMin(),m2.getMax())
# CTh1.setRange("ref",CTh1.getMin(),CTh1.getMax())
# CTh2.setRange("ref",CTh2.getMin(),CTh2.getMax())
# Phi.setRange("ref",Phi.getMin(),Phi.getMax())


fitres = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1))

### PLOT
########################################################################################################################

dataset = dataset_Bs
rangename = "FULL"
nbins = 100
nparams=2
name = "Bs"

cv3 = TCanvas()
cv3.SetFillColor(0)
cv3.Divide(3,2)


cv3.cd(1)
cpsif = CTh1.frame()
RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))
tc1_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc1_Bs.SetTextSize(0.06)
Ang_Bs.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cpsif.Draw()
if CHI2: tc1_Bs.Draw()

cv3.cd(2)
cthf = CTh2.frame()
RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename))
tc2_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_Bs.SetTextSize(0.06)
Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthf.Draw()
if CHI2: tc2_Bs.Draw()

cv3.cd(3)
cphif = Phi.frame()
RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename))
tph_Bs = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tph_Bs.SetTextSize(0.06)
Ang_Bs.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cphif.Draw()
if CHI2: tph_Bs.Draw()


cv3.cd(5)
cm1f = m1.frame()
RooAbsData.plotOn(dataset,cm1f,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs.sigmodel.plotOn(cm1f,RooFit.ProjectionRange(rangename))
tm1_Bs = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1f.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm1_Bs.SetTextSize(0.06)
Ang_Bs.sigmodel.plotOn(cm1f,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm1f.Draw()
if CHI2: tm1_Bs.Draw()

cv3.cd(6)
cm2f = m2.frame()
RooAbsData.plotOn(dataset,cm2f,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs.sigmodel.plotOn(cm2f,RooFit.ProjectionRange(rangename))
tm2_Bs = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2f.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm2_Bs.SetTextSize(0.06)
Ang_Bs.sigmodel.plotOn(cm2f,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm2f.Draw()
if CHI2: tm2_Bs.Draw()


