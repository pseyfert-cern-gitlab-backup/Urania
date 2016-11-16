from ROOT import *
from math import *
# from BsKstKstPDF import *
from PDF_builder_self import *


gStyle.SetPadBottomMargin(0.2)
gStyle.SetPadLeftMargin(0.2)
gStyle.SetTitleYOffset(1.06)
CHI2 = 1
markerSize = 1.4

### IMPORT DATA
########################################################################################################################

file_data = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/histos_abraham_phi_str17.root")
tree2 = file_data.Get("data")

# cuts = "GLKsb.>0.14 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10."

cuts = "GLKsb.>0.225 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>2. && Kminus_PIDK>2. && Piplus_PIDp<10. && Piminus_PIDp<10."
   
fout = TFile("trash.root","recreate")
t = tree2.CopyTree(cuts)


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

dataset_Bs = RooDataSet("data_Bs","data_Bs",dataset_all,dataset_all.get(),"1","n_s_sw")
dataset_Bd = RooDataSet("data_Bd","data_Bd",dataset_all,dataset_all.get(),"1","n_d_sw")



### ANGULAR MODEL
########################################################################################################################

########### Bs ###########
Ang_Bs = AngularPDF("Bs")
Ang_Bs.OwnPhys()
Ang_Bs.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bs.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bs.modParam("Bs2",0.,0.,kTRUE)
Ang_Bs.modParam("MBs",5366.3,0.,kTRUE)
Ang_Bs.modParam("Asm2",0.,0.,kTRUE)
Ang_Bs.modParam("dsm",0.,0.,kTRUE)
Ang_Bs.modParam("Ass2",0.,0.,kTRUE)
Ang_Bs.modParam("dss",0.,0.,kTRUE)
Ang_Bs.modParam("dpe",0.,0.,kTRUE)


Ang_Bs.modParam("c1_th",-0.407291/1.19601,0.,kTRUE)
Ang_Bs.modParam("c2_th",-0.522295/1.19601,0.,kTRUE)
Ang_Bs.modParam("c3_th",-0.193329/1.19601,0.,kTRUE)
Ang_Bs.modParam("c4_th",-0.111589/1.19601,0.,kTRUE)
y_val = 1+Ang_Bs.c1_th.getVal()+Ang_Bs.c2_th.getVal()+Ang_Bs.c3_th.getVal()+Ang_Bs.c4_th.getVal()
Ang_Bs.modParam("y",y_val,0.,kTRUE)
Ang_Bs.modParam("c1_ph",0.,0.,kTRUE)
Ang_Bs.modParam("c2_ph",1.5,0.,kTRUE)
Ang_Bs.modParam("c3_ph",0.,0.,kTRUE)

Ang_Bs.modParam("normP",1./433923.65279,0,kTRUE)
Ang_Bs.modParam("normS",1./771976.068198,0,kTRUE)
Ang_Bs.modParam("normSS",1./1373391.4871,0,kTRUE)



########### Bd ###########
Ang_Bd = AngularPDF("Bd")
# Ang_Bd.CopySwave(Ang_Bs)
Ang_Bd.OwnPhys()
Ang_Bd.CopyAcceptance(Ang_Bs)
Ang_Bd.CopyNorm(Ang_Bs)
Ang_Bd.modParam("m_kst",8.95279e+02 , 1, kTRUE)
Ang_Bd.modParam("g_kst",5.01156e+01 , 1, kTRUE)
Ang_Bd.modParam("Bs2",0.,0.,kTRUE)
Ang_Bd.modParam("MBs",5279.5,0.,kTRUE)
Ang_Bd.modParam("DGs",0.,0.,kTRUE)
Ang_Bd.modParam("Asm2",0.,0.,kTRUE)
Ang_Bd.modParam("dsm",0.,0.,kTRUE)
Ang_Bd.modParam("Ass2",0.,0.,kTRUE)
Ang_Bd.modParam("dss",0.,0.,kTRUE)
Ang_Bd.modParam("dpe",0.,0.,kTRUE)

Ang_Bs.make(), Ang_Bd.make()



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

fitres_Bd = Ang_Bd.sigmodel.fitTo(dataset_Bd,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1))
fitres_Bs = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1))

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


