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

file_data_Bd = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bd2KstKst_MC11a_MagUpAndDown_GL2012.root")
tree_Bd2 = file_data_Bd.Get("T")

file_data_Bs = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r2_GL_2012.root")
tree_Bs2 = file_data_Bs.Get("T")


cuts_Bd = "GLK2012sb.>0.14 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10."

cuts_Bs = "GLK2012sb.>0.14 && (P11_richPID_p-P11_richPID_k)<0. && (P21_richPID_p-P21_richPID_k)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && P22_richPID_k<-5. && P12_richPID_k<-5. && P11_richPID_k>5. && P21_richPID_k>5. && P22_richPID_p<10. && P12_richPID_p<10."


# cuts_Bd = "GLK2012sb.>0.225 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>2. && Kminus_PIDK>2. && Piplus_PIDp<10. && Piminus_PIDp<10."

# cuts_Bs = "GLK2012sb.>0.225 && (P11_richPID_p-P11_richPID_k)<0. && (P21_richPID_p-P21_richPID_k)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && P22_richPID_k<-5. && P12_richPID_k<-5. && P11_richPID_k>2. && P21_richPID_k>2. && P22_richPID_p<10. && P12_richPID_p<10."


fout = TFile("trash.root","recreate")
t_Bd = tree_Bd2.CopyTree(cuts_Bd)
t_Bs = tree_Bs2.CopyTree(cuts_Bs)


### DATASETS
########################################################################################################################

CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")

dataset_Bd = RooDataSet("data_Bd","data_Bd",t_Bd,RooArgSet(CTh1,CTh2,Phi,m1,m2))
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
Ang_Bs.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bs.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bs.modParam("Bs2",0.,0.,kTRUE)
Ang_Bs.modParam("MBs",5366.3,0.,kTRUE)
Ang_Bs.modParam("Asm2",0.,0.,kTRUE)
Ang_Bs.modParam("dsm",0.,0.,kTRUE)
Ang_Bs.modParam("Asp2",0.,0.,kTRUE)
Ang_Bs.modParam("dsp",0.,0.,kTRUE)
Ang_Bs.modParam("Ass2",0.,0.,kTRUE)
Ang_Bs.modParam("dss",0.,0.,kTRUE)
Ang_Bs.modParam("dpe",0.,0.,kTRUE)
Ang_Bs.modParam("dpe",dpe_Bs,0.,kTRUE)
Ang_Bs.modParam("dpa",dpa_Bs,0.,kTRUE)
Ang_Bs.modParam("fL",a02_Bs,0.,kTRUE)
Ang_Bs.modParam("fpax",apa2_Bs/(1-a02_Bs),0.,kTRUE)


Ang_Bs.modParam("normP",1./8.82332476508e+13,0,kTRUE)#1./433923.65279,0,kTRUE)
Ang_Bs.modParam("normS",1./1.60399738894e+14,0,kTRUE)#1./771976.068198,0,kTRUE)
Ang_Bs.modParam("normSS",1./2.91590686297e+14,0,kTRUE)#1./1373391.4871,0,kTRUE)

########### Bd MC  ###########

H0_Bd = TComplex(0.9,0,1)
Hplus_Bd = TComplex(0.44,pi,1)
Hminus_Bd = TComplex(0.,pi,1)

CA0_Bd = H0_Bd
CApa_Bd = (Hplus_Bd+Hminus_Bd)/sqrt(2)
CApe_Bd = (Hplus_Bd-Hminus_Bd)/sqrt(2)


a02_Bd = CA0_Bd.Rho2()/(CA0_Bd.Rho2()+CApa_Bd.Rho2()+CApe_Bd.Rho2()) 
apa2_Bd = CApa_Bd.Rho2()/(CA0_Bd.Rho2()+CApa_Bd.Rho2()+CApe_Bd.Rho2()) 
ape2_Bd = CApe_Bd.Rho2()/(CA0_Bd.Rho2()+CApa_Bd.Rho2()+CApe_Bd.Rho2()) 
dpa_Bd = CApa_Bd.Theta()
dpe_Bd = CApe_Bd.Theta()

Ang_Bd = AngularPDF("Bd")
Ang_Bd.OwnPhys()
Ang_Bd.CopyNorm(Ang_Bs)
Ang_Bd.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bd.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bd.modParam("Bs2",0.,0.,kTRUE)
Ang_Bd.modParam("MBs",5279.5,0.,kTRUE)
Ang_Bd.modParam("DGs",0.,0.,kTRUE)
Ang_Bd.modParam("Asp2",0.,0.,kTRUE)
Ang_Bd.modParam("dsp",0.,0.,kTRUE)
Ang_Bd.modParam("Asm2",0.,0.,kTRUE)
Ang_Bd.modParam("dsm",0.,0.,kTRUE)
Ang_Bd.modParam("Ass2",0.,0.,kTRUE)
Ang_Bd.modParam("dss",0.,0.,kTRUE)
Ang_Bd.modParam("dpe",dpe_Bd,0.,kTRUE)
Ang_Bd.modParam("dpa",dpa_Bd,0.,kTRUE)
Ang_Bd.modParam("dpa",dpa_Bd,0.,kTRUE)
Ang_Bd.modParam("fL",a02_Bd,0.,kTRUE)
Ang_Bd.modParam("fpax",apa2_Bd/(1-a02_Bd),0.,kTRUE)



Ang_Bs.make(), Ang_Bd.make()


### FIT
########################################################################################################################
m1.setRange("ref",m1.getMin(),m1.getMax())
m2.setRange("ref",m2.getMin(),m2.getMax())
CTh1.setRange("ref",CTh1.getMin(),CTh1.getMax())
CTh2.setRange("ref",CTh2.getMin(),CTh2.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())


fitres = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1))
fitres = Ang_Bd.sigmodel.fitTo(dataset_Bd,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1))

### PLOT
########################################################################################################################


dataset = dataset_Bs
rangename = "FULL"
nbins = 11
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




dataset = dataset_Bd
name = "Bd"



cv4 = TCanvas()
cv4.SetFillColor(0)
cv4.Divide(3,2)


cv4.cd(1)
cpsifd = CTh1.frame()
RooAbsData.plotOn(dataset,cpsifd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd.sigmodel.plotOn(cpsifd,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))
tc1_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsifd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc1_Bd.SetTextSize(0.06)
Ang_Bd.sigmodel.plotOn(cpsifd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cpsifd.Draw()
if CHI2: tc1_Bd.Draw()

cv4.cd(2)
cthfd = CTh2.frame()
RooAbsData.plotOn(dataset,cthfd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd.sigmodel.plotOn(cthfd,RooFit.ProjectionRange(rangename))
tc2_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthfd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_Bd.SetTextSize(0.06)
Ang_Bd.sigmodel.plotOn(cthfd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthfd.Draw()
if CHI2: tc2_Bd.Draw()

cv4.cd(3)
cphifd = Phi.frame()
RooAbsData.plotOn(dataset,cphifd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd.sigmodel.plotOn(cphifd,RooFit.ProjectionRange(rangename))
tph_Bd = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphifd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tph_Bd.SetTextSize(0.06)
Ang_Bd.sigmodel.plotOn(cphifd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cphifd.Draw()
if CHI2: tph_Bd.Draw()


cv4.cd(5)
cm1fb = m1.frame()
RooAbsData.plotOn(dataset,cm1fb,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd.sigmodel.plotOn(cm1fb,RooFit.ProjectionRange(rangename))
tm1_Bd = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1fb.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm1_Bd.SetTextSize(0.06)
Ang_Bd.sigmodel.plotOn(cm1fb,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm1fb.Draw()
if CHI2: tm1_Bd.Draw()

cv4.cd(6)
cm2fb = m2.frame()
RooAbsData.plotOn(dataset,cm2fb,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
Ang_Bd.sigmodel.plotOn(cm2fb,RooFit.ProjectionRange(rangename))
tm2_Bd = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2fb.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm2_Bd.SetTextSize(0.06)
Ang_Bd.sigmodel.plotOn(cm2fb,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm2fb.Draw()
if CHI2: tm2_Bd.Draw()



### ANGULAR ACCEPTANCE Bs VS Bd
########################################################################################################################


acc_par_Bd = TF1("acc_param_Bd","[0]*(1+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x)",-1,1)
acc_par_Bd.FixParameter(0,1.)
acc_par_Bd.FixParameter(1,Ang_Bd.c1_th.getVal())
acc_par_Bd.FixParameter(2,Ang_Bd.c2_th.getVal())
acc_par_Bd.FixParameter(3,Ang_Bd.c3_th.getVal())
acc_par_Bd.FixParameter(4,Ang_Bd.c4_th.getVal())
acc_par_Bd.FixParameter(5,Ang_Bd.c5_th.getVal())

int_Bd = acc_par_Bd.Integral(-1.,1.)

acc_par_phi_Bd = TF1("acc_param_phi_Bd","[0]*(1+[1]*cos([2]*x+[3]))",-pi,pi)
acc_par_phi_Bd.FixParameter(0,1)
acc_par_phi_Bd.FixParameter(1,Ang_Bd.c1_ph.getVal())
acc_par_phi_Bd.FixParameter(2,Ang_Bd.c2_ph.getVal())
acc_par_phi_Bd.FixParameter(3,Ang_Bd.c3_ph.getVal())


acc_par_Bs = TF1("acc_param_Bs","[0]*(1+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x)",-1,1)
acc_par_Bs.FixParameter(0,1.)
acc_par_Bs.FixParameter(1,Ang_Bs.c1_th.getVal())
acc_par_Bs.FixParameter(2,Ang_Bs.c2_th.getVal())
acc_par_Bs.FixParameter(3,Ang_Bs.c3_th.getVal())
acc_par_Bs.FixParameter(4,Ang_Bs.c4_th.getVal())
acc_par_Bs.FixParameter(5,Ang_Bs.c5_th.getVal())
int_Bs = acc_par_Bs.Integral(-1.,1.)
acc_par_Bs

acc_par_phi_Bs = TF1("acc_param_phi_Bs","[0]*(1+[1]*cos([2]*x+[3]))",-pi,pi)
acc_par_phi_Bs.FixParameter(0,1)
acc_par_phi_Bs.FixParameter(1,Ang_Bs.c1_ph.getVal())
acc_par_phi_Bs.FixParameter(2,Ang_Bs.c2_ph.getVal())
acc_par_phi_Bs.FixParameter(3,Ang_Bs.c3_ph.getVal())


acc_par_phikst = TF1("acc_param_phikst","[0]*(1+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x)",-1,1)
acc_par_phikst.FixParameter(0,1.5297867901079965/1.6715476737931401)
acc_par_phikst.FixParameter(1,-0.407291/1.19601)
acc_par_phikst.FixParameter(2,-0.522295/1.19601)
acc_par_phikst.FixParameter(3,-0.193329/1.19601)
acc_par_phikst.FixParameter(4,-0.111589/1.19601)
acc_par_phikst.FixParameter(5,0)

acc_par_phi_phikst = TF1("acc_param_phi_phikst","[0]*(1+[1]*cos([2]*x+[3]))",-pi,pi)
acc_par_phi_phikst.FixParameter(0,1)
acc_par_phi_phikst.FixParameter(1,0)
acc_par_phi_phikst.FixParameter(2,1.5)
acc_par_phi_phikst.FixParameter(3,0)


cv5 = TCanvas()
cv5.Divide(2,1)
cv5.cd(1)
acc_par_Bd.SetLineColor(kRed)
acc_par_Bs.SetLineColor(kBlue)
acc_par_phikst.SetLineColor(kGreen)
acc_par_Bd.Draw()
acc_par_Bs.Draw("SAME")
acc_par_phikst.Draw("SAME")
cv5.cd(2)
acc_par_phi_Bd.SetLineColor(kRed)
acc_par_phi_Bs.SetLineColor(kBlue)
acc_par_phi_phikst.SetLineColor(kGreen)
acc_par_phi_Bd.Draw()
acc_par_phi_Bs.Draw("SAME")
acc_par_phi_phikst.Draw("SAME")
