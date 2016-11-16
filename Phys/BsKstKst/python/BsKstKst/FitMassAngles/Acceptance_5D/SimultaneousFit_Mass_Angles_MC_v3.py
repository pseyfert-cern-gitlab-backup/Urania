from ROOT import *
from math import *
from PDF_builder_self_acc_v2 import *


gStyle.SetPadBottomMargin(0.2)
gStyle.SetPadLeftMargin(0.2)
gStyle.SetTitleYOffset(1.06)
CHI2 = 1
markerSize = 1.4

### IMPORT DATA
########################################################################################################################
file_data = TFile("/scratch08/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r1_GL_2012.root")
tree2 = file_data.Get("T")

signalcuts = "GLKsb.>0.14"
signalcuts += "& ((P11_richPID_p-P11_richPID_k)<15) & ((P21_richPID_p-P21_richPID_k)<15) "
# signalcuts += "& (abs(B_mass-5366.3)<30)"
signalcuts += "& (P21_richPID_k>4) & (P11_richPID_k>4) &(P22_richPID_k<-2) & (P12_richPID_k<-2) "
signalcuts += "& ! ( (abs(M_prpiKpi-5620)<50 && P11_richPID_p-P11_richPID_k>0 ) || (abs(M_Kpiprpi-5620)<50 && P21_richPID_p-P21_richPID_k>0 )) "
# signalcuts += "& abs(P1_mass-896)<100 & abs(P2_mass-896)<100"
signalcuts += "& L0Decision & Hlt1Decision & Hlt2Decision"

    
fout = TFile("trash.root","recreate")
t = tree2.CopyTree(signalcuts)


CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")
Phi.setMin(0)
Phi.setMax(2*pi)


dataset_Bs = RooDataSet("data_Bs","data_Bs",t,RooArgSet(CTh1,CTh2,Phi,m1,m2))


### ANGULAR MODEL
########################################################################################################################

import os
path = os.environ["BSKSTKSTROOT"] + "/options/Acceptance_5D/"
filename = path+"acceptance_coef_5D.root"
treename = "acc5D"
bname = "coeffs"
facc = TFile(filename)
tacc = facc.Get(treename)



Apa_Bs = 0.5
Ape_Bs = 0.33
A0_Bs  = 0.8
dpa_Bs = 3.14
dpe_Bs = 3.14

a02_Bs = A0_Bs*A0_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
apa2_Bs = Apa_Bs*Apa_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
ape2_Bs = Ape_Bs*Ape_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)

Ang_Bs = AngularPDF("Bs",tacc,bname)
Ang_Bs.OwnPhys()
Ang_Bs.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bs.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bs.modParam("Bs2",0.,0.,kTRUE)
Ang_Bs.modParam("MBs",5366.3,0.,kTRUE)
Ang_Bs.modParam("Asp2",0.,0.,kTRUE)
Ang_Bs.modParam("Asm2",0.,0.,kTRUE)
Ang_Bs.modParam("dsm",0.,0.,kTRUE)
Ang_Bs.modParam("Ass2",0.,0.,kTRUE)
Ang_Bs.modParam("dss",0.,0,kTRUE)
# Ang_Bs.modParam("dss",0.,pi,kFALSE)
Ang_Bs.modParam("dpe",0.,0.,kTRUE)
Ang_Bs.modParam("dsp",0.,pi,kFALSE)
# Ang_Bs.modParam("dsp",0.,0.,kTRUE)
Ang_Bs.modParam("dpe",dpe_Bs,0.,kTRUE)
Ang_Bs.modParam("dpa",dpa_Bs,0.,kTRUE)
Ang_Bs.modParam("fL",a02_Bs,0.,kTRUE)
Ang_Bs.modParam("fpax",apa2_Bs/(1-a02_Bs),0.,kTRUE)


Ang_Bs.modParam("normP",1./8.82332476508e+13,0,kTRUE)#1./433923.65279,0,kTRUE)
Ang_Bs.modParam("normS",1./1.60399738894e+14,0,kTRUE)#1./771976.068198,0,kTRUE)
Ang_Bs.modParam("normSS",1./2.91590686297e+14,0,kTRUE)#1./1373391.4871,0,kTRUE)
# Ang_Bs.modParam("fL",0.7,0.,kTRUE)

Ang_Bs.make()

fiter = Ang_Bs.sigmodel


### FIT
########################################################################################################################
m1.setRange("ref",m1.getMin(),m1.getMax())
m2.setRange("ref",m2.getMin(),m2.getMax())
CTh1.setRange("ref",CTh1.getMin(),CTh1.getMax())
CTh2.setRange("ref",CTh2.getMin(),CTh2.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())

# allData = RooDataSet("all Data","all Data", RooArgSet(CTh1,CTh2,Phi,m1,m2), RooFit.Index(cat), RooFit.Import("Bs",dataset_Bs),RooFit.Import("Bd",dataset_Bd))

# fitres = fiter.fitTo(allData,RooFit.Minos(0),RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1))

#fitres_Bd = Ang_Bd.sigmodel.fitTo(dataset_Bd,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1),RooFit.Minos(0))
#fitres_Bs = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(), RooFit.NumCPU(4))#,RooFit.SumW2Error(1),RooFit.Minos(1))RooFit.NumCPU(3)

#BREAK

### PLOT
########################################################################################################################

####### CALCULATE NORMALIZATION ########
nbins = 11
nparams=2


func_int_Bs = Ang_Bs.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1,m2)).getVal()
norm_cth_Bs = dataset_Bs.sumEntries()*2/nbins/func_int_Bs
norm_phi_Bs = dataset_Bs.sumEntries()*2*pi/nbins/func_int_Bs
norm_mass_Bs = dataset_Bs.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_Bs

#func_int_Bd = Ang_Bd.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1,m2)).getVal()
#norm_cth_Bd = dataset_Bd.sumEntries()*2/nbins/func_int_Bd
#norm_phi_Bd = dataset_Bd.sumEntries()*2*pi/nbins/func_int_Bd
#norm_mass_Bd = dataset_Bd.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_Bd



dataset = dataset_Bs
rangename = "FULL"
name = "Bs"

cv3 = TCanvas()
cv3.SetFillColor(0)
cv3.Divide(3,2)

cv3.cd(1)
cpsif = CTh1.frame()

Ang_Bs.norm.setVal(norm_cth_Bs)
Ang_Bs_PW_c1 = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
Ang_Bs_SW_c1 = Ang_Bs.Swave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
Ang_Bs_SW_int_c1 = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh2,Phi,m1,m2))

RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs_PW_c1.plotOn(cpsif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_SW_c1.plotOn(cpsif,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bs_SW_int_c1.plotOn(cpsif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))

tc1_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc1_Bs.SetTextSize(0.06)
# Ang_Bs.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cpsif.Draw()
if CHI2: tc1_Bs.Draw()

BREAK


cv3.cd(2)
cthf = CTh2.frame()

Ang_Bs.norm.setVal(norm_cth_Bs)
Ang_Bs_PW_c2 = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
Ang_Bs_SW_c2 = Ang_Bs.Swave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
Ang_Bs_SW_int_c2 = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh1,Phi,m1,m2))

RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs_PW_c2.plotOn(cthf,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_SW_c2.plotOn(cthf,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bs_SW_int_c2.plotOn(cthf,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.NumCPU(3))

tc2_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_Bs.SetTextSize(0.06)
# Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthf.Draw()
if CHI2: tc2_Bs.Draw()

BREAK

cv3.cd(3)
cphif = Phi.frame()

Ang_Bs.norm.setVal(norm_phi_Bs)
Ang_Bs_PW_ph = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
Ang_Bs_SW_ph = Ang_Bs.Swave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
Ang_Bs_SW_int_ph = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))

RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs_PW_ph.plotOn(cphif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_SW_ph.plotOn(cphif,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bs_SW_int_ph.plotOn(cphif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename))

tph_Bs = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tph_Bs.SetTextSize(0.06)
# Ang_Bs.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cphif.Draw()
if CHI2: tph_Bs.Draw()


cv3.cd(5)
cm1f = m1.frame()

Ang_Bs.norm.setVal(norm_mass_Bs)
Ang_Bs_PW_m1 = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
Ang_Bs_SW_m1 = Ang_Bs.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
Ang_Bs_SW_int_m1 = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))


RooAbsData.plotOn(dataset,cm1f,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs_PW_m1.plotOn(cm1f,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_SW_m1.plotOn(cm1f,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bs_SW_int_m1.plotOn(cm1f,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs.sigmodel.plotOn(cm1f,RooFit.ProjectionRange(rangename))

tm1_Bs = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1f.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm1_Bs.SetTextSize(0.06)
# Ang_Bs.sigmodel.plotOn(cm1f,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm1f.Draw()
if CHI2: tm1_Bs.Draw()

cv3.cd(6)
cm2f = m2.frame()

Ang_Bs.norm.setVal(norm_mass_Bs)
Ang_Bs_PW_m2 = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
Ang_Bs_SW_m2 = Ang_Bs.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
Ang_Bs_SW_int_m2 = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))

RooAbsData.plotOn(dataset,cm2f,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bs_PW_m2.plotOn(cm2f,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_SW_m2.plotOn(cm2f,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bs_SW_int_m2.plotOn(cm2f,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs.sigmodel.plotOn(cm2f,RooFit.ProjectionRange(rangename))

tm2_Bs = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2f.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm2_Bs.SetTextSize(0.06)
# Ang_Bs.sigmodel.plotOn(cm2f,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm2f.Draw()
if CHI2: tm2_Bs.Draw()




dataset = dataset_Bd
name = "Bd"




cv4 = TCanvas()
cv4.SetFillColor(0)
cv4.Divide(3,2)

cv4.cd(1)
cpsif_Bd = CTh1.frame()

Ang_Bd.norm.setVal(norm_cth_Bd)
Ang_Bd_PW_c1 = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
Ang_Bd_SW_c1 = Ang_Bd.Swave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
Ang_Bd_SW_int_c1 = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh2,Phi,m1,m2))

RooAbsData.plotOn(dataset,cpsif_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd_PW_c1.plotOn(cpsif_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd_SW_c1.plotOn(cpsif_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bd_SW_int_c1.plotOn(cpsif_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd.sigmodel.plotOn(cpsif_Bd,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))

tc1_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc1_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cpsif_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cpsif_Bd.Draw()
if CHI2: tc1_Bd.Draw()



cv4.cd(2)
cthf_Bd = CTh2.frame()

Ang_Bd.norm.setVal(norm_cth_Bd)
Ang_Bd_PW_c2 = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
Ang_Bd_SW_c2 = Ang_Bd.Swave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
Ang_Bd_SW_int_c2 = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh1,Phi,m1,m2))

RooAbsData.plotOn(dataset,cthf_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd_PW_c2.plotOn(cthf_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd_SW_c2.plotOn(cthf_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bd_SW_int_c2.plotOn(cthf_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd.sigmodel.plotOn(cthf_Bd,RooFit.ProjectionRange(rangename))

tc2_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cthf_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthf_Bd.Draw()
if CHI2: tc2_Bd.Draw()



cv4.cd(3)
cphif_Bd = Phi.frame()

Ang_Bd.norm.setVal(norm_phi_Bd)
Ang_Bd_PW_ph = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
Ang_Bd_SW_ph = Ang_Bd.Swave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
Ang_Bd_SW_int_ph = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))

RooAbsData.plotOn(dataset,cphif_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd_PW_ph.plotOn(cphif_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd_SW_ph.plotOn(cphif_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bd_SW_int_ph.plotOn(cphif_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd.sigmodel.plotOn(cphif_Bd,RooFit.ProjectionRange(rangename))

tph_Bd = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tph_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cphif_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cphif_Bd.Draw()
if CHI2: tph_Bd.Draw()


cv4.cd(5)
cm1f_Bd = m1.frame()

Ang_Bd.norm.setVal(norm_mass_Bd)
Ang_Bd_PW_m1 = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
Ang_Bd_SW_m1 = Ang_Bd.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
Ang_Bd_SW_int_m1 = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))


RooAbsData.plotOn(dataset,cm1f_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd_PW_m1.plotOn(cm1f_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd_SW_m1.plotOn(cm1f_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bd_SW_int_m1.plotOn(cm1f_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd.sigmodel.plotOn(cm1f_Bd,RooFit.ProjectionRange(rangename))

tm1_Bd = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1f_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm1_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cm1f_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm1f_Bd.Draw()
if CHI2: tm1_Bd.Draw()

cv4.cd(6)
cm2f_Bd = m2.frame()

Ang_Bd.norm.setVal(norm_mass_Bd)
Ang_Bd_PW_m2 = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
Ang_Bd_SW_m2 = Ang_Bd.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
Ang_Bd_SW_int_m2 = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))

RooAbsData.plotOn(dataset,cm2f_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd_PW_m2.plotOn(cm2f_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd_SW_m2.plotOn(cm2f_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
Ang_Bd_SW_int_m2.plotOn(cm2f_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bd.sigmodel.plotOn(cm2f_Bd,RooFit.ProjectionRange(rangename))

tm2_Bd = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2f_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm2_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cm2f_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm2f_Bd.Draw()
if CHI2: tm2_Bd.Draw()


# cv4 = TCanvas()
# cv4.SetFillColor(0)
# cv4.Divide(3,2)


# cv4.cd(1)
# cpsifd = CTh1.frame()
# RooAbsData.plotOn(dataset,cpsifd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bd.sigmodel.plotOn(cpsifd,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))
# tc1_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsifd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tc1_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cpsifd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cpsifd.Draw()
# if CHI2: tc1_Bd.Draw()

# cv4.cd(2)
# cthfd = CTh2.frame()
# RooAbsData.plotOn(dataset,cthfd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bd.sigmodel.plotOn(cthfd,RooFit.ProjectionRange(rangename))
# tc2_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthfd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tc2_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cthfd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cthfd.Draw()
# if CHI2: tc2_Bd.Draw()

# cv4.cd(3)
# cphifd = Phi.frame()
# RooAbsData.plotOn(dataset,cphifd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bd.sigmodel.plotOn(cphifd,RooFit.ProjectionRange(rangename))
# tph_Bd = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphifd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tph_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cphifd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cphifd.Draw()
# if CHI2: tph_Bd.Draw()


# cv4.cd(5)
# cm1fb = m1.frame()
# RooAbsData.plotOn(dataset,cm1fb,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bd.sigmodel.plotOn(cm1fb,RooFit.ProjectionRange(rangename))
# tm1_Bd = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1fb.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tm1_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cm1fb,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cm1fb.Draw()
# if CHI2: tm1_Bd.Draw()

# cv4.cd(6)
# cm2fb = m2.frame()
# RooAbsData.plotOn(dataset,cm2fb,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bd.sigmodel.plotOn(cm2fb,RooFit.ProjectionRange(rangename))
# tm2_Bd = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2fb.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tm2_Bd.SetTextSize(0.06)
# Ang_Bd.sigmodel.plotOn(cm2fb,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cm2fb.Draw()
# if CHI2: tm2_Bd.Draw()

print
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print "Bd fL: ",Ang_Bd.fL.getVal(), " + ", Ang_Bd.fL.getErrorHi()," ",Ang_Bd.fL.getErrorLo()
print "Bd fpax: ",Ang_Bd.fpax.getVal(), " + ", Ang_Bd.fpax.getErrorHi()," ",Ang_Bd.fpax.getErrorLo()
print "Bd Asp2: ",Ang_Bd.Asp2.getVal(), " + ", Ang_Bd.Asp2.getErrorHi()," ",Ang_Bd.Asp2.getErrorLo()
print "Bd Asm2: ",Ang_Bd.Asm2.getVal(), " + ", Ang_Bd.Asm2.getErrorHi()," ",Ang_Bd.Asm2.getErrorLo()
print "Bd dpa: ",Ang_Bd.dpa.getVal(), " + ", Ang_Bd.dpa.getErrorHi()," ",Ang_Bd.dpa.getErrorLo()
print "Bd dsp: ",Ang_Bd.dsp.getVal(), " + ", Ang_Bd.dsp.getErrorHi()," ",Ang_Bd.dsp.getErrorLo()
print "Bd dsm: ",Ang_Bd.dsm.getVal(), " + ", Ang_Bd.dsm.getErrorHi()," ",Ang_Bd.dsm.getErrorLo()
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print "Bs fL: ",Ang_Bs.fL.getVal(), " + ", Ang_Bs.fL.getErrorHi()," ",Ang_Bs.fL.getErrorLo()
print "Bs fpax: ",Ang_Bs.fpax.getVal(), " + ", Ang_Bs.fpax.getErrorHi()," ",Ang_Bs.fpax.getErrorLo()
print "Bs Asp2: ",Ang_Bs.Asp2.getVal(), " + ", Ang_Bs.Asp2.getErrorHi()," ",Ang_Bs.Asp2.getErrorLo()
print "Bs Asm2: ",Ang_Bs.Asm2.getVal(), " + ", Ang_Bs.Asm2.getErrorHi()," ",Ang_Bs.Asm2.getErrorLo()
print "Bs dpa: ",Ang_Bs.dpa.getVal(), " + ", Ang_Bs.dpa.getErrorHi()," ",Ang_Bs.dpa.getErrorLo()
print "Bs dsp: ",Ang_Bs.dsp.getVal(), " + ", Ang_Bs.dsp.getErrorHi()," ",Ang_Bs.dsp.getErrorLo()
print "Bs dsm: ",Ang_Bs.dsm.getVal(), " + ", Ang_Bs.dsm.getErrorHi()," ",Ang_Bs.dsm.getErrorLo()
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print 
