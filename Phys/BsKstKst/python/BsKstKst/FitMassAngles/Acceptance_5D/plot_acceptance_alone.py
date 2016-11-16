from ROOT import *
from math import *
from PDF_builder_self_acc import *
from python_utils import *
import os

gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/Acceptance_5D/Acceptance.cxx++")

# Phi.setVal(0)
# Phi.setConstant(1)
# m1.setMin(896-120)
# m1.setMax(896+120)
# m2.setMin(896-120)
# m2.setMax(896+120)

Phi.setMin(0)
Phi.setMax(2*pi)

path = os.environ["BSKSTKSTROOT"] + "/options/Acceptance_5D/"

filename = path+"acceptance_coef_5D.root"#2D_m1c1.root"
treename = "acc5D"
bname = "coeffs"
fin = TFile(filename)
tin = fin.Get(treename)
acc = Acceptance("acceptance","acceptance",CTh1,CTh2,Phi,m1,m2,tin,bname)


nbins= 50
# acc_c1c2 = acc.createIntegral(RooArgSet(Phi,m1,m2))
# histo_acc_c1c2 = acc_c1c2.createHistogram("histo_acc_c1c2",CTh1,RooFit.Binning(nbins),RooFit.YVar(CTh2,RooFit.Binning(nbins)))
# histo_acc_c1c2.Draw("COLZ")


# acc_c1 = acc.createIntegral(RooArgSet(Phi,m1,m2,CTh1))
# c1f = CTh2.frame()
# acc_c1.plotOn(c1f)
# cv2 = TCanvas()
# c1f.Draw()

#acc.forceNumInt(1)

#BREAK
##Plots 2D
cv1 = TCanvas()
cv1.Divide(4,3)
cv1.cd(1)
acc_c1c2 = acc.createIntegral(RooArgSet(Phi,m1,m2))
histo_acc_c1c2 = acc_c1c2.createHistogram("histo_acc_c1c2",CTh1,RooFit.Binning(nbins),RooFit.YVar(CTh2,RooFit.Binning(nbins)))
histo_acc_c1c2.Draw("COLZ")
BREAK
cv1.cd(2)
acc_c1ph = acc.createIntegral(RooArgSet(CTh2,m1,m2))
histo_acc_c1ph = acc_c1ph.createHistogram("histo_acc_c1ph",CTh1,RooFit.Binning(nbins),RooFit.YVar(Phi,RooFit.Binning(nbins)))
histo_acc_c1ph.Draw("COLZ")
cv1.cd(3)
acc_c2ph = acc.createIntegral(RooArgSet(CTh1,m1,m2))
histo_acc_c2ph = acc_c2ph.createHistogram("histo_acc_c2ph",CTh2,RooFit.Binning(nbins),RooFit.YVar(Phi,RooFit.Binning(nbins)))
histo_acc_c2ph.Draw("COLZ")

cv1.cd(5)
acc_c1m1 = acc.createIntegral(RooArgSet(CTh2,Phi,m2))
histo_acc_c1m1 = acc_c1m1.createHistogram("histo_acc_c1m1",CTh1,RooFit.Binning(nbins),RooFit.YVar(m1,RooFit.Binning(nbins)))
histo_acc_c1m1.Draw("COLZ")
cv1.cd(6)
acc_c2m2 = acc.createIntegral(RooArgSet(CTh1,Phi,m1))
histo_acc_c2m2 = acc_c2m2.createHistogram("histo_acc_c2m2",CTh2,RooFit.Binning(nbins),RooFit.YVar(m2,RooFit.Binning(nbins)))
histo_acc_c2m2.Draw("COLZ")
cv1.cd(7)
acc_phm1 = acc.createIntegral(RooArgSet(CTh1,CTh2,m2))
histo_acc_phm1 = acc_phm1.createHistogram("histo_acc_phm1",Phi,RooFit.Binning(nbins),RooFit.YVar(m1,RooFit.Binning(nbins)))
histo_acc_phm1.Draw("COLZ")
cv1.cd(8)
acc_phm2 = acc.createIntegral(RooArgSet(CTh1,CTh2,m1))
histo_acc_phm2 = acc_phm2.createHistogram("histo_acc_phm2",Phi,RooFit.Binning(nbins),RooFit.YVar(m2,RooFit.Binning(nbins)))
histo_acc_phm2.Draw("COLZ")

cv1.cd(8)
acc_m1m2 = acc.createIntegral(RooArgSet(CTh1,CTh2,Phi))
histo_acc_m1m2 = acc_m1m2.createHistogram("histo_acc_m1m2",m1,RooFit.Binning(nbins),RooFit.YVar(m2,RooFit.Binning(nbins)))
histo_acc_m1m2.Draw("COLZ")

cv1.cd(10)
acc_c1m2 = acc.createIntegral(RooArgSet(CTh2,Phi,m1))
histo_acc_c1m2 = acc_c1m2.createHistogram("histo_acc_c1m2",CTh1,RooFit.Binning(nbins),RooFit.YVar(m2,RooFit.Binning(nbins)))
histo_acc_c1m2.Draw("COLZ")
cv1.cd(11)
acc_c2m1 = acc.createIntegral(RooArgSet(CTh1,Phi,m2))
histo_acc_c2m1 = acc_c2m1.createHistogram("histo_acc_c2m1",CTh2,RooFit.Binning(nbins),RooFit.YVar(m1,RooFit.Binning(nbins)))
histo_acc_c2m1.Draw("COLZ")



BREAK

faccmc = TFile("acceptances_from_MC.root")
hc1acc = faccmc.Get("hc1acc")
hc2acc = faccmc.Get("hc2acc")
hphacc = faccmc.Get("hphacc")
hm1acc = faccmc.Get("hm1acc")
hm2acc = faccmc.Get("hm2acc")


## Plots 1D
cv2 = TCanvas()
cv2.Divide(3,2)
cv2.cd(1)
acc_c1 = acc.createIntegral(RooArgSet(Phi,m1,m2,CTh2))
c1f = CTh1.frame()
acc_c1.plotOn(c1f)
c1f.Draw()
cv2.cd(2)
acc_c2 = acc.createIntegral(RooArgSet(Phi,m1,m2,CTh1))
c2f = CTh2.frame()
acc_c2.plotOn(c2f)
c2f.Draw()
cv2.cd(3)
acc_ph = acc.createIntegral(RooArgSet(m1,m2,CTh1,CTh2))
phf = Phi.frame()
acc_ph.plotOn(phf)
phf.Draw()
cv2.cd(4)
acc_m1 = acc.createIntegral(RooArgSet(Phi,m2,CTh1,CTh2))
m1f = m1.frame()
acc_m1.plotOn(m1f)
m1f.Draw()
cv2.cd(5)
acc_m2 = acc.createIntegral(RooArgSet(Phi,m1,CTh1,CTh2))
m2f = m2.frame()
acc_m2.plotOn(m2f)
m2f.Draw()


cv2num = TCanvas()
cv2num.Divide(3,2)
cv2num.cd(1)
acc_c1 = acc.createIntegral(RooArgSet(m1,m2,CTh2))
c1f = CTh1.frame()
acc_c1.plotOn(c1f)
c1f.Draw()
cv2num.cd(2)
acc_c2 = acc.createIntegral(RooArgSet(m1,m2,CTh1))
c2f = CTh2.frame()
acc_c2.plotOn(c2f)
c2f.Draw()
# cv2num.cd(3)
# acc_ph = acc.createIntegral(RooArgSet(m1,m2,CTh1,CTh2))
# phf = Phi.frame()
# acc_ph.plotOn(phf)
# phf.Draw()
cv2num.cd(4)
acc_m1 = acc.createIntegral(RooArgSet(m2,CTh1,CTh2))
m1f = m1.frame()
acc_m1.plotOn(m1f)
m1f.Draw()
cv2num.cd(5)
acc_m2 = acc.createIntegral(RooArgSet(m1,CTh1,CTh2))
m2f = m2.frame()
acc_m2.plotOn(m2f)
m2f.Draw()

# CTh1.SetNameTitle("CosTheta1","CosTheta1")
# CTh2.SetNameTitle("CosTheta2","CosTheta2")
# Phi.SetNameTitle("Phi_pi","Phi_pi")
# Phi.setMin(0)
# Phi.setMax(2*pi)
# m1.SetNameTitle("P1_mass","P1_mass")
# m2.SetNameTitle("P2_mass","P2_mass")



# f = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r2_GL_2012_pi.root")
# t2 = f.Get("T")
# fgen = TFile("/scratch08/NTuples_Bs2KstKst_strip17_Brais/public/Bs2Kst0Kst0_MC11.root")                                                                                                 
# t2 = fgen.Get("BsKst0Kst0")                                                                                                                                                             


# cuts = "B_IPS<5 "
# cuts += "&& P21_richPID_k>10 && P11_richPID_k>10 &&P22_richPID_k<0 && P12_richPID_k<0 "
# cuts += "&& SV_chi2<25"
# cuts += "&& P11_TrChi2DoF<5 && P12_TrChi2DoF<5 && P21_TrChi2Dof<5 && P22_TrChi2Dof<5 "
# cuts += "&& P1_pt>900 && P2_pt>900 "
# cuts += "&& P11_pt>500 && P12_pt>500 && P21_pt>500 && P22_pt>500 "
# cuts += "&& max(P1V_chi2,P2V_chi2)<9 "
# cuts += "&& B_dissig>15"
# cuts += "&& (P11_richPID_p-P11_richPID_k)<15 && (P21_richPID_p-P21_richPID_k)<15"
# cuts += "&& (abs(B_mass-5366.3)<30)"
# cuts += "&& ! ( (abs(M_prpiKpi-5620)<40 && P11_richPID_p-P11_richPID_k>0 ) || (abs(M_Kpiprpi-5620)<40 && P21_richPID_p-P21_richPID_k>0 ) ) "
# # signalcuts += "& abs(P1_mass-896)<100 & abs(P2_mass-896)<100"                                                                                                                           
# cuts += "&& !(P11_muonPID_isMuonLoose || P12_muonPID_isMuonLoose || P21_muonPID_isMuonLoose || P22_muonPID_isMuonLoose)"


# trigger = "L0Decision && Hlt1Decision && Hlt2Decision"

# cuts_tos = " & (L0Tos) & (Hlt1Tos) & (Hlt2Tos)"
# cuts_notos =  " & !((L0Tos) & (Hlt1Tos) & (Hlt2Tos))"# & P12_pt>1500 && P22_pt>1500"                                                                                                      

# #trigger = "B_Decision==1"                                                                                                                                                                

# gl = "&& GLKsb.>0.24 "#&& B_tos==1" ## GLKsb. is the GLK2012sb. in real data!!!                                                                                                           

# cuts += gl + " && "+ trigger + cuts_notos


# f2=TFile("nada.root","recreate")
# t=t2.CopyTree(cuts)

# data = RooDataSet("data","data",t,RooArgSet(CTh1,CTh2,Phi,m1,m2))


# Apa_Bs = 0.5
# Ape_Bs = 0.33
# A0_Bs  = 0.8
# dpa_Bs = 3.14
# dpe_Bs = 0.#3.14                                                                                                                                                                          

# a02_Bs = A0_Bs*A0_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
# apa2_Bs = Apa_Bs*Apa_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
# ape2_Bs = Ape_Bs*Ape_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)


# filename = path+"acceptance_coef_5D.root"
# treename = "acc5D"
# bname = "coeffs"
# fin = TFile(filename)
# tin = fin.Get(treename)


# PDF = AngularPDF("Bs",tin,bname)
# PDF.OwnPhys()
# PDF.modParam("m_kst",8.95279e+02 , 1, kTRUE)
# PDF.modParam("g_kst",5.01156e+01 , 1, kTRUE)
# PDF.modParam("Bs2",0.,0.,kTRUE)
# PDF.modParam("MBs",5366.3,0.,kTRUE)
# PDF.modParam("Asm2",0.,0.,kTRUE)
# PDF.modParam("dsm",0.,0.,kTRUE)
# PDF.modParam("Asp2",0.,0.,kTRUE)
# PDF.modParam("dsp",0.,0.,kTRUE)
# PDF.modParam("Ass2",0.,0.,kTRUE)
# PDF.modParam("dss",0.,0.,kTRUE)
# PDF.modParam("dpe",0.,0.,kTRUE)
# PDF.modParam("dpe",dpe_Bs,0.,kTRUE)
# PDF.modParam("dpa",dpa_Bs,0.,kTRUE)
# PDF.modParam("fL",a02_Bs,0.,kTRUE)
# PDF.modParam("fpax",apa2_Bs/(1-a02_Bs),0.,kTRUE)


# PDF.modParam("normP",1./8.82332476508e+13,0,kTRUE)#1./433923.65279,0,kTRUE)
# PDF.modParam("normS",1./1.60399738894e+14,0,kTRUE)#1./771976.068198,0,kTRUE)
# PDF.modParam("normSS",1./2.91590686297e+14,0,kTRUE)#1./1373391.4871,0,kTRUE)

# PDF.make()

# nbins=50

# cv = TCanvas()
# cv.Divide(3,2)
# cv.cd(1)
# c1f = CTh1.frame()
# data.plotOn(c1f,RooFit.Binning(nbins))
# PDF.sigmodel.plotOn(c1f)
# c1f.Draw()
# cv.cd(2)
# c2f = CTh2.frame()
# data.plotOn(c2f,RooFit.Binning(nbins))
# PDF.sigmodel.plotOn(c2f)
# c2f.Draw()
# cv.cd(3)
# phf = Phi.frame()
# data.plotOn(phf,RooFit.Binning(nbins))
# PDF.sigmodel.plotOn(phf)
# phf.Draw()
# cv.cd(4)
# m1f = m1.frame()
# data.plotOn(m1f,RooFit.Binning(nbins))
# PDF.sigmodel.plotOn(m1f)
# m1f.Draw()
# cv.cd(5)
# m2f = m2.frame()
# data.plotOn(m2f,RooFit.Binning(nbins))
# PDF.sigmodel.plotOn(m2f)
# m2f.Draw()



