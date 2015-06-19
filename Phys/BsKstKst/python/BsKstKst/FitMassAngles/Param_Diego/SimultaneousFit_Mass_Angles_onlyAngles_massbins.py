from ROOT import *
from math import *
# from BsKstKstPDF import *
from PDF_builder_self_onlyangles import *


gStyle.SetPadBottomMargin(0.2)
gStyle.SetPadLeftMargin(0.2)
gStyle.SetTitleYOffset(1.06)
CHI2 = 1
markerSize = 1.4

### IMPORT DATA
########################################################################################################################

# file_data = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2Kst0Kst0_Real2011_2012_wide_DecayTree_v1_GL2012.root")
# tree2 = file_data.Get("T")

# cuts = "GLK2012sb.>0.14 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10. && abs(Kst_M-895.94)<50.  && Kstb_M<1700"

fout = TFile("trash.root","recreate")
# t3 = tree2.CopyTree(cuts)

file_data = TFile("Cutted_Data.root")
t3 = file_data.Get("T")

CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")

CTh1.setMax(0.7)
CTh2.setMax(0.7)

### MASSFIT & sPLOT
########################################################################################################################


# Mass_bins = [744.,800.,850.,905.,940.,1045.,1150,1250,1350,1450,1550,1650]
# Mass_bins = [744.,850.,905.,940.,1045.,1150,1250,1350,1450,1550,1650]
Mass_bins = [744.,850.,870.,880,890.,900.,910.,920,940,970,1040,1300,1700]
swave = []
swave_err = []

pwave = []
pwave_err = []

dwave = []
dwave_err = []

plot_results = []

masses = []
masses_err = []


# BREAK

for i in range(len(Mass_bins)-1):


    t = t3.CopyTree("Kstb_M>"+str(Mass_bins[i])+" && "+"Kstb_M<"+str(Mass_bins[i+1]))


    masses.append(0.5*(Mass_bins[i]+Mass_bins[i+1]))
    masses_err.append(0.5*(Mass_bins[i+1]-Mass_bins[i]))
    
    from fit_8 import *

    dataset_all_b = RooDataSet("dataALLb","dataALLb",t,RooArgSet(CTh1,CTh2,Phi,Bmass))

    resalt = model.fitTo(dataset_all_b,RooFit.Minos(0),RooFit.Save(1),RooFit.Extended(1))

    c=TCanvas()
    c.SetFillColor(0)
    gStyle.SetOptTitle(0)
    m=c.cd(1)
    frame = Bmass.frame()
    RooAbsData.plotOn(dataset_all_b,frame,RooFit.Binning(60))
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


#     # d0_c.setConstant(1)
#     kkkst_mean.setConstant(1)
#     mean_d.setConstant(1)
#     c_bkg.setConstant(1)
#     sigma.setConstant(1)

#     # n_lambda.setConstant(1)
#     # n_lambda2.setConstant(1)
#     # n_kst1430g.setConstant(1)
#     # n_d0.setConstant(1)
#     # n_d02.setConstant(1)
#     # n_rhokst.setConstant(1)


#     sdata = RooStats.SPlot("sData","An SPlot",dataset_all ,model, RooArgList(n_s,n_d,n_bkg,n_lambda,n_lambda2,n_kkkst,n_d0,n_d02,n_rhokst) )
    
#     dataset_Bs = RooDataSet("data_Bs","data_Bs",dataset_all,dataset_all.get(),"1","n_s_sw")
#     dataset_Bd = RooDataSet("data_Bd","data_Bd",dataset_all,dataset_all.get(),"1","n_d_sw")


    Bmassb = RooRealVar("B_s0_M","B_s0_M_b",mean_s.getVal()-30,mean_s.getVal()+30)

    dataset_all = RooDataSet("dataALL","dataALL",t,RooArgSet(CTh1,CTh2,Phi,Bmass))

    c1_th = RooRealVar("c1_th","c1_th",-3.42376e-01)
    c2_th = RooRealVar("c2_th","c2_th",-8.09980e-01)
    c3_th = RooRealVar("c3_th","c3_th",-3.65408e-01)
    c4_th = RooRealVar("c4_th","c4_th",1.74248e-01)
    y = RooRealVar("y","y",5.19370e-04)
    c5_th = RooFormulaVar("c5_th","y-1-c1_th-c2_th-c3_th-c4_th",RooArgList(c1_th,c2_th,c3_th,c4_th,y))

    acceptance_c1 = RooFormulaVar("acceptance_c1","1+c1_th*CosTheta1+c2_th*CosTheta1*CosTheta1+c3_th*CosTheta1*CosTheta1*CosTheta1+c4_th*CosTheta1*CosTheta1*CosTheta1*CosTheta1+c5_th*CosTheta1*CosTheta1*CosTheta1*CosTheta1*CosTheta1",RooArgList(c1_th,c2_th,c3_th,c4_th,c5_th,CTh1))
    acceptance_c2 = RooFormulaVar("acceptance_c2","1+c1_th*CosTheta2+c2_th*CosTheta2*CosTheta2+c3_th*CosTheta2*CosTheta2*CosTheta2+c4_th*CosTheta2*CosTheta2*CosTheta2*CosTheta2+c5_th*CosTheta2*CosTheta2*CosTheta2*CosTheta2*CosTheta2",RooArgList(c1_th,c2_th,c3_th,c4_th,c5_th,CTh2))

    acc_corr = RooFormulaVar("acc_corr","1./(acceptance_c1*acceptance_c2)",RooArgList(acceptance_c1,acceptance_c2))

#     n_s_sw = RooRealVar("n_s_sw","n_s_sw",-500,+500)
    
#     weight = RooFormulaVar("weight","n_s_sw*acc_corr",RooArgList(n_s_sw,acc_corr))
    
    dataset_all.addColumn(acc_corr)
#     dataset_all.addColumn(weight)

#     dataset_Bs = RooDataSet("data_Bs","data_Bs",dataset_all,dataset_all.get(),"1","weight")
#     dataset_Bd = RooDataSet("data_Bd","data_Bd",dataset_all,dataset_all.get(),"1","n_d_sw")

    dataset_Bs = RooDataSet("data_Bs","data_Bs",dataset_all,dataset_all.get(),"1","acc_corr")
    dataset_Bd = RooDataSet("data_Bd","data_Bd",dataset_all,dataset_all.get(),"1","acc_corr")
    

    Ang_Bs = AngularPDF("Bs")
    Ang_Bs.OwnPhys()
    Ang_Bs.make()

    Ang_Bd = AngularPDF("Bd")
    Ang_Bd.OwnPhys()
    Ang_Bd.make()
    

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
    
#     fitres_Bd = Ang_Bd.sigmodel.fitTo(dataset_Bd,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1),RooFit.Minos(1))
    fitres_Bs = Ang_Bs.sigmodel.fitTo(dataset_Bs,RooFit.Save(),RooFit.NumCPU(4),RooFit.SumW2Error(1),RooFit.Minos(0))

    nentries = t.GetEntries()

    swave_ = nentries*Ang_Bs.As2.getVal()
    swave_err_ = nentries*Ang_Bs.As2.getError()

    dwave_ = nentries*(Ang_Bs.Ad02.getVal()+Ang_Bs.Adpa2.getVal()+Ang_Bs.Adpe2.getVal())
    dwave_err_ = nentries*sqrt(Ang_Bs.Ad02.getError()+Ang_Bs.Adpa2.getError()+Ang_Bs.Adpe2.getError())

    Ap2 = RooFormulaVar("Ap2","1-"+Ang_Bs.As2.GetName()+"-"+Ang_Bs.Ad02.GetName()+"-"+Ang_Bs.Adpa2.GetName()+"-"+Ang_Bs.Adpe2.GetName(),RooArgList(Ang_Bs.As2,Ang_Bs.Ad02,Ang_Bs.Adpa2,Ang_Bs.Adpe2))

    pwave_ = nentries*Ap2.getVal()
    pwave_err_ = nentries*Ap2.getPropagatedError(fitres_Bs)

    pwave.append(pwave_)
    pwave_err.append(pwave_err_)
    swave.append(swave_)
    swave_err.append(swave_err_)
    dwave.append(dwave_)
    dwave_err.append(dwave_err_)




#     swave_ = (Ang_Bs.Asp2.getVal()+Ang_Bs.Asm2.getVal())
#     swave_err_ = sqrt(Ang_Bs.Asp2.getError()+Ang_Bs.Asm2.getError())

#     Ap2 = RooFormulaVar("Ap2","1-"+Ang_Bs.Asp2.GetName()+"-"+Ang_Bs.Asm2.GetName(),RooArgList(Ang_Bs.Asp2,Ang_Bs.Asm2))

#     pwave_ = Ap2.getVal()
#     pwave_err_ = Ap2.getPropagatedError(fitres_Bs)

#     n_pw = n_s.getVal()*pwave_
#     n_pw_err = sqrt((n_s.getVal()*pwave_err_)**2 + (pwave_*n_s.getError())**2)


#     pwave.append(n_pw)
#     pwave_err.append(n_pw_err)
#     swave.append(swave_)
#     swave_err.append(swave_err_)
    

    ### PLOT
    ########################################################################################################################

    ####### CALCULATE NORMALIZATION ########
    nbins = 11
    nparams=2

#     func_int_Bs = Ang_Bs.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi)).getVal()
#     norm_cth_Bs = dataset_Bs.sumEntries()*2/nbins/func_int_Bs
#     norm_phi_Bs = dataset_Bs.sumEntries()*2*pi/nbins/func_int_Bs
#     norm_mass_Bs = dataset_Bs.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_Bs
    
#     func_int_Bd = Ang_Bd.sigmodel.createIntegral(RooArgSet(CTh1,CTh2,Phi)).getVal()
#     norm_cth_Bd = dataset_Bd.sumEntries()*2/nbins/func_int_Bd
#     norm_phi_Bd = dataset_Bd.sumEntries()*2*pi/nbins/func_int_Bd
#     norm_mass_Bd = dataset_Bd.sumEntries()*(m1.getMax()-m1.getMin())/nbins/func_int_Bd
    
    
    dataset = dataset_Bs
    rangename = "FULL"
    name = "Bs"
    
    cv3 = TCanvas("cv3_"+str(i),"cv3_"+str(i),400,900)
    cv3.SetFillColor(0)
    cv3.Divide(1,3)
    
    cv3.cd(1)
    cpsif = CTh1.frame()
    
#     Ang_Bs.norm.setVal(norm_cth_Bs)
#     Ang_Bs_PW_c1 = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh2,Phi))
#     Ang_Bs_SW_c1 = Ang_Bs.Swave.createIntegral(RooArgSet(CTh2,Phi))
#     Ang_Bs_SW_int_c1 = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh2,Phi))
    
    RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
#     Ang_Bs_PW_c1.plotOn(cpsif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     Ang_Bs_SW_c1.plotOn(cpsif,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
#     Ang_Bs_SW_int_c1.plotOn(cpsif,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
    Ang_Bs.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))
    
    tc1_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
    tc1_Bs.SetTextSize(0.06)
    # Ang_Bs.sigmodel.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
    cpsif.Draw()
    if CHI2: tc1_Bs.Draw()


    
    cv3.cd(2)
    cthf = CTh2.frame()
    
#     Ang_Bs.norm.setVal(norm_cth_Bs)
#     Ang_Bs_PW_c2 = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh1,Phi))
#     Ang_Bs_SW_c2 = Ang_Bs.Swave.createIntegral(RooArgSet(CTh1,Phi))
#     Ang_Bs_SW_int_c2 = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh1,Phi))
    
    RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
#     Ang_Bs_PW_c2.plotOn(cthf,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     Ang_Bs_SW_c2.plotOn(cthf,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
#     Ang_Bs_SW_int_c2.plotOn(cthf,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
    Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename))

    tc2_Bs = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
    tc2_Bs.SetTextSize(0.06)
    # Ang_Bs.sigmodel.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
    cthf.Draw()
    if CHI2: tc2_Bs.Draw()



    cv3.cd(3)
    cphif = Phi.frame()
    
#     Ang_Bs.norm.setVal(norm_phi_Bs)
#     Ang_Bs_PW_ph = Ang_Bs.Pwave.createIntegral(RooArgSet(CTh1,CTh2))
#     Ang_Bs_SW_ph = Ang_Bs.Swave.createIntegral(RooArgSet(CTh1,CTh2))
#     Ang_Bs_SW_int_ph = Ang_Bs.Swave_int.createIntegral(RooArgSet(CTh1,CTh2))

    RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
#     Ang_Bs_PW_ph.plotOn(cphif,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     Ang_Bs_SW_ph.plotOn(cphif,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
#     Ang_Bs_SW_int_ph.plotOn(cphif,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
    Ang_Bs.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename))

    tph_Bs = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
    tph_Bs.SetTextSize(0.06)
    # Ang_Bs.sigmodel.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
    cphif.Draw()
    if CHI2: tph_Bs.Draw()






#     dataset = dataset_Bd
#     name = "Bd"




#     cv4 = TCanvas("cv4","cv4",400,900)
#     cv4.SetFillColor(0)
#     cv4.Divide(1,3)

#     cv4.cd(1)
#     cpsif_Bd = CTh1.frame()
    
#     Ang_Bd.norm.setVal(norm_cth_Bd)
#     Ang_Bd_PW_c1 = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh2,Phi))
#     Ang_Bd_SW_c1 = Ang_Bd.Swave.createIntegral(RooArgSet(CTh2,Phi))
#     Ang_Bd_SW_int_c1 = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh2,Phi))

#     RooAbsData.plotOn(dataset,cpsif_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.Name("Data"),RooFit.DataError(RooAbsData.SumW2))
#     Ang_Bd_PW_c1.plotOn(cpsif_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     Ang_Bd_SW_c1.plotOn(cpsif_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
#     Ang_Bd_SW_int_c1.plotOn(cpsif_Bd,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
#     Ang_Bd.sigmodel.plotOn(cpsif_Bd,RooFit.ProjectionRange(rangename),RooFit.Name("FullSigmodel"))

#     tc1_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cpsif_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
#     tc1_Bd.SetTextSize(0.06)
#     # Ang_Bd.sigmodel.plotOn(cpsif_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     cpsif_Bd.Draw()
#     if CHI2: tc1_Bd.Draw()
    


#     cv4.cd(2)
#     cthf_Bd = CTh2.frame()
    
#     Ang_Bd.norm.setVal(norm_cth_Bd)
#     Ang_Bd_PW_c2 = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh1,Phi))
#     Ang_Bd_SW_c2 = Ang_Bd.Swave.createIntegral(RooArgSet(CTh1,Phi))
#     Ang_Bd_SW_int_c2 = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh1,Phi))

#     RooAbsData.plotOn(dataset,cthf_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
#     Ang_Bd_PW_c2.plotOn(cthf_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     Ang_Bd_SW_c2.plotOn(cthf_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
#     Ang_Bd_SW_int_c2.plotOn(cthf_Bd,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
#     Ang_Bd.sigmodel.plotOn(cthf_Bd,RooFit.ProjectionRange(rangename))

#     tc2_Bd = TLatex(0.265618,50,"#chi^{2}/NODF = %.3f"%(cthf_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
#     tc2_Bd.SetTextSize(0.06)
#     # Ang_Bd.sigmodel.plotOn(cthf_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     cthf_Bd.Draw()
#     if CHI2: tc2_Bd.Draw()



#     cv4.cd(3)
#     cphif_Bd = Phi.frame()

#     Ang_Bd.norm.setVal(norm_phi_Bd)
#     Ang_Bd_PW_ph = Ang_Bd.Pwave.createIntegral(RooArgSet(CTh1,CTh2))
#     Ang_Bd_SW_ph = Ang_Bd.Swave.createIntegral(RooArgSet(CTh1,CTh2))
#     Ang_Bd_SW_int_ph = Ang_Bd.Swave_int.createIntegral(RooArgSet(CTh1,CTh2))

#     RooAbsData.plotOn(dataset,cphif_Bd,RooFit.CutRange(rangename),RooFit.Binning(nbins),RooFit.DataError(RooAbsData.SumW2))
#     Ang_Bd_PW_ph.plotOn(cphif_Bd,RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     Ang_Bd_SW_ph.plotOn(cphif_Bd,RooFit.LineColor(kGreen),RooFit.LineStyle(kDashed))
#     Ang_Bd_SW_int_ph.plotOn(cphif_Bd,RooFit.LineColor(kCyan),RooFit.LineStyle(kDashed))
#     Ang_Bd.sigmodel.plotOn(cphif_Bd,RooFit.ProjectionRange(rangename))

#     tph_Bd = TLatex(3,60,"#chi^{2}/NODF = %.3f"%(cphif_Bd.chiSquare(nparams)*(nbins-nparams))+"/%i"%(nbins-nparams))
#     tph_Bd.SetTextSize(0.06)
#     # Ang_Bd.sigmodel.plotOn(cphif_Bd,RooFit.ProjectionRange(rangename),RooFit.Components("sigmodel_"+name),RooFit.LineColor(kRed),RooFit.LineStyle(kDashed))
#     cphif_Bd.Draw()
#     if CHI2: tph_Bd.Draw()




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
    
#     print
#     print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
#     print "Bd fL: ",Ang_Bd.fL.getVal(), " + ", Ang_Bd.fL.getErrorHi()," ",Ang_Bd.fL.getErrorLo()
#     print "Bd fpa: ",Ang_Bd.fpa.getVal(), " + ", Ang_Bd.fpa.getErrorHi()," ",Ang_Bd.fpa.getErrorLo()
#     print "Bd Asp2: ",Ang_Bd.Asp2.getVal(), " + ", Ang_Bd.Asp2.getErrorHi()," ",Ang_Bd.Asp2.getErrorLo()
#     print "Bd Asm2: ",Ang_Bd.Asm2.getVal(), " + ", Ang_Bd.Asm2.getErrorHi()," ",Ang_Bd.Asm2.getErrorLo()
#     print "Bd dpa: ",Ang_Bd.dpa.getVal(), " + ", Ang_Bd.dpa.getErrorHi()," ",Ang_Bd.dpa.getErrorLo()
#     print "Bd dsp: ",Ang_Bd.dsp.getVal(), " + ", Ang_Bd.dsp.getErrorHi()," ",Ang_Bd.dsp.getErrorLo()
#     print "Bd dsm: ",Ang_Bd.dsm.getVal(), " + ", Ang_Bd.dsm.getErrorHi()," ",Ang_Bd.dsm.getErrorLo()
#     print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
#     print
#     print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
#     print "Bs fL: ",Ang_Bs.fL.getVal(), " + ", Ang_Bs.fL.getErrorHi()," ",Ang_Bs.fL.getErrorLo()
#     print "Bs fpa: ",Ang_Bs.fpa.getVal(), " + ", Ang_Bs.fpa.getErrorHi()," ",Ang_Bs.fpa.getErrorLo()
#     print "Bs Asp2: ",Ang_Bs.Asp2.getVal(), " + ", Ang_Bs.Asp2.getErrorHi()," ",Ang_Bs.Asp2.getErrorLo()
#     print "Bs Asm2: ",Ang_Bs.Asm2.getVal(), " + ", Ang_Bs.Asm2.getErrorHi()," ",Ang_Bs.Asm2.getErrorLo()
#     print "Bs dpa: ",Ang_Bs.dpa.getVal(), " + ", Ang_Bs.dpa.getErrorHi()," ",Ang_Bs.dpa.getErrorLo()
#     print "Bs dsp: ",Ang_Bs.dsp.getVal(), " + ", Ang_Bs.dsp.getErrorHi()," ",Ang_Bs.dsp.getErrorLo()
#     print "Bs dsm: ",Ang_Bs.dsm.getVal(), " + ", Ang_Bs.dsm.getErrorHi()," ",Ang_Bs.dsm.getErrorLo()
#     print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
#     print 

    plot_results.append({"mass_bin":i, "mass_plot":c, "angular_plot":cv3})
#     plot_results.append({"mass_bin":i, "angular_plot":cv3})


    
from graph_tools import *
pwgraph = assymGraph(masses,pwave,masses_err,pwave_err,title="pwave_fraction")
swgraph = assymGraph(masses,swave,masses_err,swave_err,title="swave_fraction")
dwgraph = assymGraph(masses,dwave,masses_err,dwave_err,title="dwave_fraction")
cv5=TCanvas()
pwgraph.SetLineColor(kRed)
pwgraph.SetMarkerColor(kRed)
pwgraph.Draw("AP")
swgraph.Draw("P")
dwgraph.SetLineColor(kBlue)
dwgraph.SetMarkerColor(kBlue)
dwgraph.Draw("P")
