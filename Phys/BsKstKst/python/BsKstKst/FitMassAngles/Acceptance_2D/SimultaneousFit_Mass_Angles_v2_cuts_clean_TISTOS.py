from ROOT import *
from math import *
# from BsKstKstPDF import *
from PDF_builder import *


gStyle.SetPadBottomMargin(0.2)
gStyle.SetPadLeftMargin(0.2)
gStyle.SetTitleYOffset(1.06)
CHI2 = 1
markerSize = 1.4

### IMPORT DATA
########################################################################################################################

import cPickle, os
cuts_file = open(os.environ["BSKSTKSTROOT"]+"/options/parameters_abril.dct")
parameters = cPickle.load(cuts_file)


file_data = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_Real2011_strip17_cuts_v9r1_GL2012.root")
tree2 = file_data.Get("T")

cuts = parameters["signalcuts"]

gl = "&& GLK2012sb.>0.14"
mass_cut = "&& abs(B_mass-5366.3)<30"
cuts_tos = "(L0Tos) && (Hlt1Tos) && (Hlt2Tos)"
cuts_notos = "!((L0Tos) && (Hlt1Tos) && (Hlt2Tos))"

t_tos = tree2.CopyTree(cuts+gl+mass_cut+"&&"+cuts_tos)
t_notos = tree2.CopyTree(cuts+gl+mass_cut+"&&"+cuts_notos)




CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")
m1.SetNameTitle("P1_mass","P1_mass")
m2.SetNameTitle("P2_mass","P2_mass")



import os
path = os.environ["BSKSTKSTROOT"] + "/options/Acceptance_5D/"
filename_tos = path+"acceptance_coef_2D_TOS_latest_one.root"
filename_notos = path+"acceptance_coef_2D_NOTOS_latest_one.root"
treename = "acc5D"
bname = "coeffs"
# fin = TFile(filename)
# tin = fin.Get(treename)

#BREAK

Ang_Bs_TOS = AngularPDF("TOS",filename_tos,bname)
Ang_Bs_TOS.OwnPhys()
# Ang_Bs_TOS.modParam("m_kst",8.95279e+02 , 1, kTRUE)
# Ang_Bs_TOS.modParam("g_kst",5.01156e+01 , 1, kTRUE)
# Ang_Bs_TOS.modParam("normP",1./9.53823067503e+13,0,kTRUE)
# Ang_Bs_TOS.modParam("normS",1./1.67643895893e+14,0,kTRUE)
# Ang_Bs_TOS.modParam("normSS",1./2.94649825509e+14,0,kTRUE)

Ang_Bs_TOS.modParam("m_kst",8.96178e+02 , 1, kTRUE)
Ang_Bs_TOS.modParam("g_kst",4.79932e+01 , 1, kTRUE)
Ang_Bs_TOS.modParam("normP",1./8.82332476508e+13,0,kTRUE)
Ang_Bs_TOS.modParam("normS",1./1.60399738894e+14,0,kTRUE)
Ang_Bs_TOS.modParam("normSS",1./2.91590686297e+14,0,kTRUE)

# Ang_Bs_TOS.modParam("m_kst",8.94478e+02,10.,kTRUE)
# Ang_Bs_TOS.modParam("g_kst",4.46093e+01,20.,kTRUE)
# Ang_Bs_TOS.modParam("normP",1./7.77674790047e+13,0.,kTRUE)
# Ang_Bs_TOS.modParam("normS",1./1.51374602998e+14,0., kTRUE)
# Ang_Bs_TOS.modParam("normSS",1./2.94649825509e+14,0., kTRUE)

Ang_Bs_TOS.modParam("Bs2",0.,0.,kTRUE)
Ang_Bs_TOS.modParam("MBs",5366.3,0.,kTRUE)
Ang_Bs_TOS.modParam("dpe",0.,pi,kFALSE)
Ang_Bs_TOS.modParam("dsp",0,0,kTRUE)
Ang_Bs_TOS.modParam("dpa",pi,pi,kFALSE)
Ang_Bs_TOS.modParam("dss",pi,pi,kFALSE)





Ang_Bs_NOTOS = AngularPDF("NOTOS",filename_notos,bname)
Ang_Bs_NOTOS.CopyPhys(Ang_Bs_TOS)
Ang_Bs_NOTOS.CopyNorm(Ang_Bs_TOS)

Ang_Bs_TOS.modParam("fbkg",parameters["f_bkg_tos"] ,0,kTRUE)
Ang_Bs_NOTOS.modParam("fbkg",parameters["f_bkg_notos"] ,0,kTRUE)
Ang_Bs_TOS.make(),Ang_Bs_NOTOS.make()


samplename = "sample"
cat =  RooCategory(samplename, samplename)
cat.defineType("TOS"), cat.defineType("NOTOS")

dataset_TOS = RooDataSet("dataTOS","dataTOS",t_tos,RooArgSet(CTh1,CTh2,Phi,m1,m2))
dataset_NOTOS = RooDataSet("dataNOTOS","dataNOTOS",t_notos,RooArgSet(CTh1,CTh2,Phi,m1,m2))

allData = RooDataSet("all Data","all Data", RooArgSet(CTh1,CTh2,Phi,m1,m2), RooFit.Index(cat), RooFit.Import("TOS",dataset_TOS),RooFit.Import("NOTOS",dataset_NOTOS))


m1.setRange("ref",m1.getMin(),m1.getMax())
m2.setRange("ref",m2.getMin(),m2.getMax())
CTh1.setRange("ref",CTh1.getMin(),CTh1.getMax())
CTh2.setRange("ref",CTh2.getMin(),CTh2.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())
# Ang_Bs_TOS.model.fixCoefRange("ref")
# Ang_Bs_NOTOS.model.fixCoefRange("ref")

fiter = RooSimultaneous("fitter", "fitter", cat)
fiter.addPdf(Ang_Bs_TOS.model,"TOS")
fiter.addPdf(Ang_Bs_NOTOS.model,"NOTOS")

# nll = RooNLLVar("nll","nll",fiter,allData)                                                                                                                                                                         
# m = RooMinuit(nll)                                                                                                                                                                                                 
# m.simplex()                                                                                                                                                                                                        

# BREAK                                                                                                                                                                                                              
fitres = fiter.fitTo(allData,RooFit.Save(),RooFit.NumCPU(4),RooFit.Minos(1))

foutres =  TFile("fit_result_enero.root","RECREATE")
fitres.Write("fitres")
foutres.Close()




BREAK
#Asm2_Bs=0.4878, Asp2_Bs=0.4963, Ass2_Bs=0.03187, dpa_Bs=-1.033, dsm_Bs=2.966, dsp_Bs=-0.9301, dss_Bs=1.86, fL_Bs=0.467, fpax_Bs=0.2966,
### PLOT
########################################################################################################################
Ang_Bs_TOS.Asm2.setVal(5.31455e-01)
Ang_Bs_TOS.Asp2x.setVal(2.39736e-01)
Ang_Bs_TOS.Ass2x.setVal(1.16018e-14)
Ang_Bs_TOS.dpa.setVal(5.21424e+00)
Ang_Bs_TOS.dsm.setVal(2.54980e+00)
Ang_Bs_TOS.dpe.setVal(1.12969e+00)
Ang_Bs_TOS.dsp.setVal(0.)
Ang_Bs_TOS.dss.setVal(0.)
Ang_Bs_TOS.fL.setVal(2.64951e-01)
Ang_Bs_TOS.fpax.setVal(2.65745e-01)



# # Ang_Bs.fpax.setVal(0.3452)
# # Ang_Bs.fL.setVal(0.3517) 


# Ang_Bs_TOS.Asm2.setVal(5.13912e-01)
# Ang_Bs_TOS.Asp2x.setVal(2.59030e-01)
# Ang_Bs_TOS.Ass2x.setVal(5.79422e-02)
# Ang_Bs_TOS.dpa.setVal(-1.14966e+00)
# Ang_Bs_TOS.dsm.setVal(2.38773e+00)
# Ang_Bs_TOS.dsp.setVal(-9.59555e-01)
# Ang_Bs_TOS.dss.setVal(2.09127e+00 )
# Ang_Bs_TOS.fL.setVal(1.09691e-01)
# Ang_Bs_TOS.fpax.setVal(2.99199e-01)

print "fL: ",Ang_Bs_TOS.fL.getVal()," +/- ",Ang_Bs_TOS.fL.getError()
print "fpa: ",Ang_Bs_TOS.fpa.getVal()#," +/- ",Ang_Bs_TOS.fpa.getError()
print "Asm2: ",Ang_Bs_TOS.Asm2.getVal()#," +/- ",Ang_Bs_TOS.Asm2.getError()
print "Asp2: ",Ang_Bs_TOS.Asp2.getVal()#," +/- ",Ang_Bs_TOS.Asp2.getError()
print "Ass2: ",Ang_Bs_TOS.Ass2.getVal()#," +/- ",Ang_Bs_TOS.Ass2.getError()




####### CALCULATE NORMALIZATION ########
nbins = 11
nparams=2

func_int_TOS = Ang_Bs_TOS.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1,m2)).getVal()
norm_cth_TOS = dataset_TOS.sumEntries()*2/nbins/func_int_TOS
norm_phi_TOS = dataset_TOS.sumEntries()*2*pi/nbins/func_int_TOS
norm_mass_TOS = dataset_TOS.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_TOS

func_int_NOTOS = Ang_Bs_NOTOS.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1,m2)).getVal()
norm_cth_NOTOS = dataset_NOTOS.sumEntries()*2/nbins/func_int_NOTOS
norm_phi_NOTOS = dataset_NOTOS.sumEntries()*2*pi/nbins/func_int_NOTOS
norm_mass_NOTOS = dataset_NOTOS.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_NOTOS


dataset = dataset_TOS
rangename = "FULL"
name = "TOS"

cv3 = TCanvas()
cv3.SetFillColor(0)
cv3.Divide(3,2)

cv3.cd(1)
cpsif = CTh1.frame()

Ang_Bs_TOS.norm.setVal(norm_cth_Bs)
Ang_Bs_TOS_PW_c1 = Ang_Bs_TOS.Pwave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
Ang_Bs_TOS_SW_c1 = Ang_Bs_TOS.Swave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
Ang_Bs_TOS_SW_int_c1 = Ang_Bs_TOS.Swave_int.createIntegral(RooArgSet(CTh2,Phi,m1,m2))

RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_TOS_PW_c1.plotOn(cpsif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_c1.plotOn(cpsif,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_int_c1.plotOn(cpsif,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
Ang_Bs_TOS.model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineStyle(kDashed),RooFit.LineColor(kBlue))
Ang_Bs_TOS.model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))

tc1_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc1_Bs.SetTextSize(0.06)
# Ang_Bs_TOS.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cpsif.Draw()
if CHI2: tc1_Bs.Draw()

BREAK

cv3.cd(2)
cthf = CTh2.frame()

#Ang_Bs_TOS.norm.setVal(norm_cth_Bs)
# Ang_Bs_TOS_PW_c2 = Ang_Bs_TOS.Pwave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
# Ang_Bs_TOS_SW_c2 = Ang_Bs_TOS.Swave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
# Ang_Bs_TOS_SW_int_c2 = Ang_Bs_TOS.Swave_int.createIntegral(RooArgSet(CTh1,Phi,m1,m2))

RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_TOS_PW_c2.plotOn(cthf,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_c2.plotOn(cthf,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_int_c2.plotOn(cthf,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
Ang_Bs_TOS.model.plotOn(cthf,RooFit.ProjectionRange(rangename))

tc2_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_Bs.SetTextSize(0.06)
# Ang_Bs_TOS.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthf.Draw()
if CHI2: tc2_Bs.Draw()



cv3.cd(3)
cphif = Phi.frame()

#Ang_Bs_TOS.norm.setVal(norm_phi_Bs)
# Ang_Bs_TOS_PW_ph = Ang_Bs_TOS.Pwave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
# Ang_Bs_TOS_SW_ph = Ang_Bs_TOS.Swave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
# Ang_Bs_TOS_SW_int_ph = Ang_Bs_TOS.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))

RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_TOS_PW_ph.plotOn(cphif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_ph.plotOn(cphif,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_int_ph.plotOn(cphif,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
Ang_Bs_TOS.model.plotOn(cphif,RooFit.ProjectionRange(rangename))

tph_Bs = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tph_Bs.SetTextSize(0.06)
# Ang_Bs_TOS.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cphif.Draw()
if CHI2: tph_Bs.Draw()


cv3.cd(5)
cm1f = m1.frame()

#Ang_Bs_TOS.norm.setVal(norm_mass_Bs)
# Ang_Bs_TOS_PW_m1 = Ang_Bs_TOS.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
# Ang_Bs_TOS_SW_m1 = Ang_Bs_TOS.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
# Ang_Bs_TOS_SW_int_m1 = Ang_Bs_TOS.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))


RooAbsData.plotOn(dataset,cm1f,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_TOS_PW_m1.plotOn(cm1f,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_m1.plotOn(cm1f,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_int_m1.plotOn(cm1f,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
Ang_Bs_TOS.model.plotOn(cm1f,RooFit.ProjectionRange(rangename))

tm1_Bs = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1f.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm1_Bs.SetTextSize(0.06)
# Ang_Bs_TOS.sigmodel.plotOn(cm1f,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm1f.Draw()
if CHI2: tm1_Bs.Draw()

cv3.cd(6)
cm2f = m2.frame()

#Ang_Bs_TOS.norm.setVal(norm_mass_Bs)
# Ang_Bs_TOS_PW_m2 = Ang_Bs_TOS.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
# Ang_Bs_TOS_SW_m2 = Ang_Bs_TOS.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
# Ang_Bs_TOS_SW_int_m2 = Ang_Bs_TOS.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))

RooAbsData.plotOn(dataset,cm2f,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_TOS_PW_m2.plotOn(cm2f,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_m2.plotOn(cm2f,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_TOS_SW_int_m2.plotOn(cm2f,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
Ang_Bs_TOS.model.plotOn(cm2f,RooFit.ProjectionRange(rangename))

tm2_Bs = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2f.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm2_Bs.SetTextSize(0.06)
# Ang_Bs_TOS.sigmodel.plotOn(cm2f,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm2f.Draw()
if CHI2: tm2_Bs.Draw()




dataset = dataset_NOTOS
name = "NOTOS"


cv4 = TCanvas()
cv4.SetFillColor(0)
cv4.Divide(3,2)

cv4.cd(1)
cpsif_NOTOS = CTh1.frame()

#Ang_Bs_NOTOS.norm.setVal(norm_cth_NOTOS)
# Ang_Bs_NOTOS_PW_c1 = Ang_Bs_NOTOS.Pwave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
# Ang_Bs_NOTOS_SW_c1 = Ang_Bs_NOTOS.Swave.createIntegral(RooArgSet(CTh2,Phi,m1,m2))
# Ang_Bs_NOTOS_SW_int_c1 = Ang_Bs_NOTOS.Swave_int.createIntegral(RooArgSet(CTh2,Phi,m1,m2))

RooAbsData.plotOn(dataset,cpsif_NOTOS,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_NOTOS_PW_c1.plotOn(cpsif_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_c1.plotOn(cpsif_NOTOS,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_int_c1.plotOn(cpsif_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_NOTOS.model.plotOn(cpsif_NOTOS,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))

tc1_NOTOS = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif_NOTOS.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc1_NOTOS.SetTextSize(0.06)
# Ang_Bs_NOTOS.sigmodel.plotOn(cpsif_NOTOS,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cpsif_NOTOS.Draw()
if CHI2: tc1_NOTOS.Draw()



cv4.cd(2)
cthf_NOTOS = CTh2.frame()

#Ang_Bs_NOTOS.norm.setVal(norm_cth_NOTOS)
# Ang_Bs_NOTOS_PW_c2 = Ang_Bs_NOTOS.Pwave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
# Ang_Bs_NOTOS_SW_c2 = Ang_Bs_NOTOS.Swave.createIntegral(RooArgSet(CTh1,Phi,m1,m2))
# Ang_Bs_NOTOS_SW_int_c2 = Ang_Bs_NOTOS.Swave_int.createIntegral(RooArgSet(CTh1,Phi,m1,m2))

RooAbsData.plotOn(dataset,cthf_NOTOS,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_NOTOS_PW_c2.plotOn(cthf_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_c2.plotOn(cthf_NOTOS,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_int_c2.plotOn(cthf_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_NOTOS.model.plotOn(cthf_NOTOS,RooFit.ProjectionRange(rangename))

tc2_NOTOS = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf_NOTOS.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_NOTOS.SetTextSize(0.06)
# Ang_Bs_NOTOS.sigmodel.plotOn(cthf_NOTOS,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthf_NOTOS.Draw()
if CHI2: tc2_NOTOS.Draw()



cv4.cd(3)
cphif_NOTOS = Phi.frame()

#Ang_Bs_NOTOS.norm.setVal(norm_phi_NOTOS)
# Ang_Bs_NOTOS_PW_ph = Ang_Bs_NOTOS.Pwave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
# Ang_Bs_NOTOS_SW_ph = Ang_Bs_NOTOS.Swave.createIntegral(RooArgSet(CTh1,CTh2,m1,m2))
# Ang_Bs_NOTOS_SW_int_ph = Ang_Bs_NOTOS.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,m1,m2)
                                                               

RooAbsData.plotOn(dataset,cphif_NOTOS,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_NOTOS_PW_ph.plotOn(cphif_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_ph.plotOn(cphif_NOTOS,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_int_ph.plotOn(cphif_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_NOTOS.model.plotOn(cphif_NOTOS,RooFit.ProjectionRange(rangename))

tph_NOTOS = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif_NOTOS.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tph_NOTOS.SetTextSize(0.06)
# Ang_Bs_NOTOS.sigmodel.plotOn(cphif_NOTOS,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cphif_NOTOS.Draw()
if CHI2: tph_NOTOS.Draw()


cv4.cd(5)
cm1f_NOTOS = m1.frame()

#Ang_Bs_NOTOS.norm.setVal(norm_mass_NOTOS)
# Ang_Bs_NOTOS_PW_m1 = Ang_Bs_NOTOS.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
# Ang_Bs_NOTOS_SW_m1 = Ang_Bs_NOTOS.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))
# Ang_Bs_NOTOS_SW_int_m1 = Ang_Bs_NOTOS.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m2))


RooAbsData.plotOn(dataset,cm1f_NOTOS,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_NOTOS_PW_m1.plotOn(cm1f_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_m1.plotOn(cm1f_NOTOS,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_int_m1.plotOn(cm1f_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_NOTOS.model.plotOn(cm1f_NOTOS,RooFit.ProjectionRange(rangename))

tm1_NOTOS = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1f_NOTOS.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm1_NOTOS.SetTextSize(0.06)
# Ang_Bs_NOTOS.sigmodel.plotOn(cm1f_NOTOS,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm1f_NOTOS.Draw()
if CHI2: tm1_NOTOS.Draw()

cv4.cd(6)
cm2f_NOTOS = m2.frame()

#Ang_Bs_NOTOS.norm.setVal(norm_mass_NOTOS)
# Ang_Bs_NOTOS_PW_m2 = Ang_Bs_NOTOS.Pwave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
# Ang_Bs_NOTOS_SW_m2 = Ang_Bs_NOTOS.Swave.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))
# Ang_Bs_NOTOS_SW_int_m2 = Ang_Bs_NOTOS.Swave_int.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1))

RooAbsData.plotOn(dataset,cm2f_NOTOS,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_Bs_NOTOS_PW_m2.plotOn(cm2f_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_m2.plotOn(cm2f_NOTOS,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
# Ang_Bs_NOTOS_SW_int_m2.plotOn(cm2f_NOTOS,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
Ang_Bs_NOTOS.model.plotOn(cm2f_NOTOS,RooFit.ProjectionRange(rangename))

tm2_NOTOS = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2f_NOTOS.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tm2_NOTOS.SetTextSize(0.06)
# Ang_Bs_NOTOS.sigmodel.plotOn(cm2f_NOTOS,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cm2f_NOTOS.Draw()
if CHI2: tm2_NOTOS.Draw()


BREAK

# cv4 = TCanvas()
# cv4.SetFillColor(0)
# cv4.Divide(3,2)


# cv4.cd(1)
# cpsifd = CTh1.frame()
# RooAbsData.plotOn(dataset,cpsifd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
# Ang_NOTOS.sigmodel.plotOn(cpsifd,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))
# tc1_NOTOS = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsifd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tc1_NOTOS.SetTextSize(0.06)
# Ang_NOTOS.sigmodel.plotOn(cpsifd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cpsifd.Draw()
# if CHI2: tc1_NOTOS.Draw()

# cv4.cd(2)
# cthfd = CTh2.frame()
# RooAbsData.plotOn(dataset,cthfd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_NOTOS.sigmodel.plotOn(cthfd,RooFit.ProjectionRange(rangename))
# tc2_NOTOS = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthfd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tc2_NOTOS.SetTextSize(0.06)
# Ang_NOTOS.sigmodel.plotOn(cthfd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cthfd.Draw()
# if CHI2: tc2_NOTOS.Draw()

# cv4.cd(3)
# cphifd = Phi.frame()
# RooAbsData.plotOn(dataset,cphifd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_NOTOS.sigmodel.plotOn(cphifd,RooFit.ProjectionRange(rangename))
# tph_NOTOS = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphifd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tph_NOTOS.SetTextSize(0.06)
# Ang_NOTOS.sigmodel.plotOn(cphifd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cphifd.Draw()
# if CHI2: tph_NOTOS.Draw()


# cv4.cd(5)
# cm1fb = m1.frame()
# RooAbsData.plotOn(dataset,cm1fb,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_NOTOS.sigmodel.plotOn(cm1fb,RooFit.ProjectionRange(rangename))
# tm1_NOTOS = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm1fb.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tm1_NOTOS.SetTextSize(0.06)
# Ang_NOTOS.sigmodel.plotOn(cm1fb,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cm1fb.Draw()
# if CHI2: tm1_NOTOS.Draw()

# cv4.cd(6)
# cm2fb = m2.frame()
# RooAbsData.plotOn(dataset,cm2fb,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
# Ang_NOTOS.sigmodel.plotOn(cm2fb,RooFit.ProjectionRange(rangename))
# tm2_NOTOS = TLatex(900,60,"#chi^{2}/NODF = %.3f"%(cm2fb.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
# tm2_NOTOS.SetTextSize(0.06)
# Ang_NOTOS.sigmodel.plotOn(cm2fb,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
# cm2fb.Draw()
# if CHI2: tm2_NOTOS.Draw()

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
