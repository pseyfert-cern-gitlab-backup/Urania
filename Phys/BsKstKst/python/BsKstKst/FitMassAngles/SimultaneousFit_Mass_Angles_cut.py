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

# file_data = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/histos_abraham_phi_str17.root")
# tree2 = file_data.Get("data")

file_data = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2Kst0Kst0_Real2011_2012_wide_DecayTree_v1_GL2012.root")
tree2 = file_data.Get("T")

# cuts = "GLK2012sb.>0.14 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10."

cuts = "GLK2012sb.>0.14 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10."

# cuts = "GLKsb.>0.225 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>2. && Kminus_PIDK>2. && Piplus_PIDp<10. && Piminus_PIDp<10."
   
fout = TFile("trash.root","recreate")
t = tree2.CopyTree(cuts)

CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")
# m1.setMin(740)
# m1.setMax(1200)
# m2.setMin(740)
# m2.setMax(1200)

### MASSFIT & sPLOT
########################################################################################################################



from fit_8 import *


dataset_all = RooDataSet("dataALL","dataALL",t,RooArgSet(CTh1,CTh2,Phi,m1,m2,Bmass))

resalt = model.fitTo(dataset_all,RooFit.Minos(0),RooFit.Save(1),RooFit.Extended(1))

c=TCanvas()
c.SetFillColor(0)
gStyle.SetOptTitle(0)
m=c.cd(1)
frame = Bmass.frame()
RooAbsData.plotOn(dataset_all,frame,RooFit.Binning(60))
model.plotOn(frame,RooFit.Components("peak_df"),RooFit.FillStyle(1001),RooFit.FillColor(kCyan-8),RooFit.DrawOption("F"))
model.plotOn(frame,RooFit.Components("peak_sf"),RooFit.FillStyle(3001),RooFit.FillColor(kRed),RooFit.DrawOption("F"))
model.plotOn(frame,RooFit.Components("kkkstpdf"),RooFit.LineColor(kMagenta))
model.plotOn(frame,RooFit.Components("d0pdf"),RooFit.LineColor(kOrange+10))
model.plotOn(frame,RooFit.Components("d02pdf"),RooFit.LineColor(kCyan))
model.plotOn(frame,RooFit.Components("BkgMass"),RooFit.LineColor(12),RooFit.LineStyle(2))
model.plotOn(frame,RooFit.Components("rhokstpdf"),RooFit.LineColor(kViolet-3))
model.plotOn(frame,RooFit.Components("shoulder"),RooFit.LineStyle(9),RooFit.LineColor(kGreen))
plot=model.plotOn(frame)
frame.Draw()


# d0_c.setConstant(1)
kkkst_mean.setConstant(1)
mean_d.setConstant(1)
c_bkg.setConstant(1)
sigma.setConstant(1)

# n_lambda.setConstant(1)
# n_lambda2.setConstant(1)
# n_kst1430g.setConstant(1)
# n_d0.setConstant(1)
# n_d02.setConstant(1)
# n_rhokst.setConstant(1)


sdata = RooStats.SPlot("sData","An SPlot",dataset_all ,model, RooArgList(n_s,n_d,n_bkg,n_lambda,n_lambda2,n_kkkst,n_d0,n_d02,n_rhokst) )

tcut_Bs = t.CopyTree("abs(B_s0_M-"+str(mean_s.getVal())+")<30")
tcut_Bd = t.CopyTree("abs(B_s0_M-"+str(mean_d.getVal())+")<30")
dataset_Bs = RooDataSet("data_Bs","data_Bs",tcut_Bs,dataset_all.get())
dataset_Bd = RooDataSet("data_Bd","data_Bd",tcut_Bd,dataset_all.get())




### ANGULAR MODEL
########################################################################################################################

########### Bs ###########
#  **********
#  **   23 **HESSE        4000
#  **********
#  COVARIANCE MATRIX CALCULATED SUCCESSFULLY
#  FCN=571656 FROM HESSE     STATUS=OK             61 CALLS         993 TOTAL
#                      EDM=0.0152483    STRATEGY= 1      ERROR MATRIX ACCURATE 
#   EXT PARAMETER                                INTERNAL      INTERNAL  
#   NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
#    1  c1_ph_Bs     1.11472e-01   6.65765e-03   8.39960e-05  -8.89976e-01
#    2  c1_th_Bs    -3.42376e-01   1.79245e-02   5.69210e-05  -7.54263e-01
#    3  c2_ph_Bs     1.08315e+00   7.14544e-02   1.81897e-04  -3.27805e-01
#    4  c2_th_Bs    -8.09980e-01   2.38984e-02   1.24966e-05  -2.08153e-01
#    5  c3_ph_Bs     6.22806e+00   8.09221e-02   4.84711e-04   1.75841e+00
#    6  c3_th_Bs    -3.65408e-01   5.66281e-02   6.16153e-05  -3.74071e-01
#    7  c4_th_Bs     1.74248e-01   2.71377e-02   2.79275e-05  -1.01176e-01
#    8  y_Bs         5.19370e-04   6.03892e-04   1.53825e-04  -1.50633e+00
#                                ERR DEF= 0.5

Ang_Bs = AngularPDF("Bs")
Ang_Bs.OwnPhys()
Ang_Bs.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bs.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bs.modParam("Bs2",0.,0.,kTRUE)
Ang_Bs.modParam("MBs",5366.3,0.,kTRUE)
# Ang_Bs.modParam("Asp2",0.,0.,kTRUE)
# Ang_Bs.modParam("Asm2",0.,0.,kTRUE)
# Ang_Bs.modParam("dsm",0.,0.,kTRUE)
Ang_Bs.modParam("Ass2",0.,0.,kTRUE)
Ang_Bs.modParam("dss",0.,0.,kTRUE)
Ang_Bs.modParam("dpe",0.,0.,kTRUE)
Ang_Bs.modParam("dsp",0.,pi,kFALSE)
# Ang_Bs.modParam("dsp",0.,0.,kTRUE)


Ang_Bs.modParam("c1_th",-3.42376e-01,0.,kTRUE)
Ang_Bs.modParam("c2_th",-8.09980e-01,0.,kTRUE)
Ang_Bs.modParam("c3_th",-3.65408e-01,0.,kTRUE)
Ang_Bs.modParam("c4_th",1.74248e-01,0.,kTRUE)
Ang_Bs.modParam("y",5.19370e-04,0.,kTRUE)
Ang_Bs.modParam("c1_ph",1.11472e-01,0.,kTRUE)
Ang_Bs.modParam("c2_ph",1.08315e+00,0.,kTRUE)
Ang_Bs.modParam("c3_ph",6.22806e+00,0.,kTRUE)
# Ang_Bs.modParam("c1_ph",0.,0.,kTRUE)
# Ang_Bs.modParam("c2_ph",1.5,0.,kTRUE)
# Ang_Bs.modParam("c3_ph",0.,0.,kTRUE)

Ang_Bs.modParam("normP",433923.65279,0,kTRUE)
Ang_Bs.modParam("normS",771976.068198,0,kTRUE)
Ang_Bs.modParam("normSS",1373391.4871,0,kTRUE)
# Ang_Bs.modParam("fL",0.7,0.,kTRUE)


########### Bd ###########
#  **********
#  **   23 **HESSE        4000
#  **********
#  COVARIANCE MATRIX CALCULATED SUCCESSFULLY
#  FCN=375869 FROM HESSE     STATUS=OK             65 CALLS         721 TOTAL
#                      EDM=0.000358976    STRATEGY= 1      ERROR MATRIX ACCURATE 
#   EXT PARAMETER                                INTERNAL      INTERNAL  
#   NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
#    1  c1_ph_Bd     1.10311e-01   8.32613e-03   8.62914e-05  -8.93673e-01
#    2  c1_th_Bd    -3.81266e-01   2.17241e-02   5.60740e-05  -8.67217e-01
#    3  c2_ph_Bd     1.11360e+00   7.42673e-02   1.79250e-04  -3.05707e-01
#    4  c2_th_Bd    -8.36709e-01   2.76152e-02   1.16441e-05  -2.26402e-01
#    5  c3_ph_Bd     9.96182e-06   1.52700e-02   5.00000e-01   4.71491e+00
#    6  c3_th_Bd    -2.67494e-01   6.64872e-02   5.05937e-05  -2.70791e-01
#    7  c4_th_Bd     1.95106e-01   3.03307e-02   2.50003e-05  -7.32581e-02
#    8  y_Bd         2.81334e-08   2.79071e-04   7.98877e-04  -1.57032e+00
#                                  WARNING -   - ABOVE PARAMETER IS AT LIMIT.
#                                ERR DEF= 0.5


Ang_Bd = AngularPDF("Bd")
# Ang_Bd.CopySwave(Ang_Bs)
Ang_Bd.OwnPhys()
# Ang_Bd.CopyAcceptance(Ang_Bs)

Ang_Bd.modParam("c1_th",-3.81266e-01,0.,kTRUE)
Ang_Bd.modParam("c2_th",-8.36709e-01,0.,kTRUE)
Ang_Bd.modParam("c3_th",-2.67494e-01,0.,kTRUE)
Ang_Bd.modParam("c4_th",1.95106e-01,0.,kTRUE)
Ang_Bd.modParam("y",2.81334e-08,0.,kTRUE)
Ang_Bd.modParam("c1_ph",1.10311e-01,0.,kTRUE)
Ang_Bd.modParam("c2_ph",1.11360e+00,0.,kTRUE)
Ang_Bd.modParam("c3_ph",9.96182e-06,0.,kTRUE)


Ang_Bd.CopyNorm(Ang_Bs)
Ang_Bd.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bd.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bd.modParam("Bs2",0.,0.,kTRUE)
Ang_Bd.modParam("MBs",5279.5,0.,kTRUE)
Ang_Bd.modParam("DGs",0.,0.,kTRUE)
# Ang_Bd.modParam("Asp2",0.,0.,kTRUE)
# Ang_Bd.modParam("Asm2",0.,0.,kTRUE)
Ang_Bd.modParam("dsm",0,pi,kFALSE)
# Ang_Bd.modParam("dsp",0.,0.,kTRUE)
# Ang_Bd.modParam("dsp",pi,pi,kFALSE)
Ang_Bd.modParam("Ass2",0.,0.,kTRUE)
Ang_Bd.modParam("dss",0.,0.,kTRUE)
Ang_Bd.modParam("dpe",0.,0.,kTRUE)

# Ang_Bs.CopyAcceptance(Ang_Bd)
Ang_Bs.make(), Ang_Bd.make()

#BREAK


#BREAK
########### Full Model ###########
cat =  RooCategory("sample", "sample")
cat.defineType("Bd"), cat.defineType("Bs")

fiter = RooSimultaneous("fitter", "fitter", cat)
fiter.addPdf(Ang_Bs.sigmodel,"Bs")
fiter.addPdf(Ang_Bd.sigmodel,"Bd")


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
# fitres_Bs = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1),RooFit.Minos(0))
fitres_Bs = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(),RooFit.NumCPU(4),RooFit.Minos(1))

### PLOT
########################################################################################################################

####### CALCULATE NORMALIZATION ########
nbins = 11
nparams=2

func_int_Bs = Ang_Bs.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1,m2)).getVal()
norm_cth_Bs = dataset_Bs.sumEntries()*2/nbins/func_int_Bs
norm_phi_Bs = dataset_Bs.sumEntries()*2*pi/nbins/func_int_Bs
norm_mass_Bs = dataset_Bs.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_Bs

func_int_Bd = Ang_Bd.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi,m1,m2)).getVal()
norm_cth_Bd = dataset_Bd.sumEntries()*2/nbins/func_int_Bd
norm_phi_Bd = dataset_Bd.sumEntries()*2*pi/nbins/func_int_Bd
norm_mass_Bd = dataset_Bd.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_Bd


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
Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename))

tc2_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
tc2_Bs.SetTextSize(0.06)
# Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
cthf.Draw()
if CHI2: tc2_Bs.Draw()



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
print "Bd fpa: ",Ang_Bd.fpa.getVal(), " + ", Ang_Bd.fpa.getErrorHi()," ",Ang_Bd.fpa.getErrorLo()
print "Bd Asp2: ",Ang_Bd.Asp2.getVal(), " + ", Ang_Bd.Asp2.getErrorHi()," ",Ang_Bd.Asp2.getErrorLo()
print "Bd Asm2: ",Ang_Bd.Asm2.getVal(), " + ", Ang_Bd.Asm2.getErrorHi()," ",Ang_Bd.Asm2.getErrorLo()
print "Bd dpa: ",Ang_Bd.dpa.getVal(), " + ", Ang_Bd.dpa.getErrorHi()," ",Ang_Bd.dpa.getErrorLo()
print "Bd dsp: ",Ang_Bd.dsp.getVal(), " + ", Ang_Bd.dsp.getErrorHi()," ",Ang_Bd.dsp.getErrorLo()
print "Bd dsm: ",Ang_Bd.dsm.getVal(), " + ", Ang_Bd.dsm.getErrorHi()," ",Ang_Bd.dsm.getErrorLo()
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print "Bs fL: ",Ang_Bs.fL.getVal(), " + ", Ang_Bs.fL.getErrorHi()," ",Ang_Bs.fL.getErrorLo()
print "Bs fpa: ",Ang_Bs.fpa.getVal(), " + ", Ang_Bs.fpa.getErrorHi()," ",Ang_Bs.fpa.getErrorLo()
print "Bs Asp2: ",Ang_Bs.Asp2.getVal(), " + ", Ang_Bs.Asp2.getErrorHi()," ",Ang_Bs.Asp2.getErrorLo()
print "Bs Asm2: ",Ang_Bs.Asm2.getVal(), " + ", Ang_Bs.Asm2.getErrorHi()," ",Ang_Bs.Asm2.getErrorLo()
print "Bs dpa: ",Ang_Bs.dpa.getVal(), " + ", Ang_Bs.dpa.getErrorHi()," ",Ang_Bs.dpa.getErrorLo()
print "Bs dsp: ",Ang_Bs.dsp.getVal(), " + ", Ang_Bs.dsp.getErrorHi()," ",Ang_Bs.dsp.getErrorLo()
print "Bs dsm: ",Ang_Bs.dsm.getVal(), " + ", Ang_Bs.dsm.getErrorHi()," ",Ang_Bs.dsm.getErrorLo()
print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print 
