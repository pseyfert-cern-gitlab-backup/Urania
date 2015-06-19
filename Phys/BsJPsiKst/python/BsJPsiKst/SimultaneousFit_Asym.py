from ROOT import *
from math import *
import os
#if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
#gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/AngJpsiKst_Swave.cxx++")
#gSystem.Load("AngJPsiKst_cxx")
from PDF_2012_Asym import *

print "Class for fitting polarization: AngularPDF"

samplename = "sample"
cat =  RooCategory(samplename, samplename)
cat.defineType("2011"), cat.defineType("2012"), cat.defineType("2011n"), cat.defineType("2012n")
s_a = 5.

ACC_FREE = 1
FIX_Bd = ACC_FREE
SAME_ACC = 1
Mass.setRange("Bs_range",5366.3-25,5366.3+25)
Mass.setRange("Bd_range",5279.5-25,5279.5+25)

cuts = "muplus_MINIPCHI2 > 25 && muminus_MINIPCHI2 > 25 && Kplus_MINIPCHI2 > 4 && piminus_MINIPCHI2 > 4  && Kplus_PT > 500 && piminus_PT>500 && piminus_PIDK<-6 && Kplus_PIDK > 6 && J_psi_1S_FDCHI2_TOPPV > 169 &&  J_psi_1S_LOKI_DOCA_1_2<0.3"
cuts += "&&  J_psi_1S_ENDVERTEX_CHI2 < 9 && B0_IPCHI2_OWNPV < 25"
cuts += "&& abs(Mjpsik-5279)>60"
cuts += "&& abs(Kst_892_0_MM-896)<70"


 ## Acceptance
        
if __name__=="__main__":

    f11 = TFile("~/vol5/OL_2011_GL.root")
    #f11 = TFile("/user/diegoms/cmtuser/NTuples/OL_2011_GL.root")
    t2_11 = f11.Get("T")
    f12 = TFile("~/vol5/OL_2012_GL.root")
    #f12 = TFile("/user/diegoms/cmtuser/NTuples/OL_2012_GL.root")
    t2_12 = f12.Get("T")
    #f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
 

    fx=TFile("/tmp/SimulFit_nada.root","recreate")
    t12p=t2_12.CopyTree(cuts+"&& GLsb>0.2 && Kplus_ID > 0")
    t12n=t2_12.CopyTree(cuts+"&& GLsb>0.2 && Kplus_ID < 0")
    t11p=t2_11.CopyTree(cuts+"&& GLsb>0.2 && Kplus_ID > 0")
    t11n=t2_11.CopyTree(cuts+"&& GLsb>0.2 && Kplus_ID < 0")
    
    #BREAK
    
    
    AngBd_2011p,  AngBd_2011n = InitSignalPdfs("Bd","2011")
    AngBd_2011p.OwnPhys(equalAsym = 1)
    AngBd_2011p.OwnAcc()
    AngBd_2011p.modParam("fL",0.5488,0.1,kTRUE)
    AngBd_2011p.modParam("fpa",0.2392,0.1,kTRUE)
    AngBd_2011p.modParam("As2",0.047,0.01,kTRUE)
    AngBd_2011p.modParam("dpa",-2.98,0.1,kTRUE)
    AngBd_2011p.modParam("dpe",3.07,0.1,kTRUE)
    AngBd_2011p.modParam("ds",2.20,0.1,kTRUE)
    AngBd_2011p.modParam("c1_psi",-0.592,0.1)
    
    AngBd_2011n.CopyFreeParams(AngBd_2011p)
    AngBd_2011n.OwnAcc()
    AngBd_2011n.modParam("c1_psi",-0.592,0.1)
    
    AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011")
    AngBs_2011p.OwnPhys()
    AngBs_2011p.modParam("dpa",-pi,pi*.5)
    AngBs_2011n.CopyFreeParams(AngBs_2011p)

    
    AngBd_2012p,  AngBd_2012n = InitSignalPdfs("Bd","2012")
    AngBd_2012p.CopyPhys(AngBd_2011p)
    AngBd_2012p.OwnAcc()
    AngBd_2012n.CopyPhys(AngBd_2011n)
    AngBd_2012n.OwnAcc()

    AngBs_2012p,  AngBs_2012n = InitSignalPdfs("Bs","2012")
    AngBs_2012p.CopyPhys(AngBs_2011p)
    AngBs_2012n.CopyPhys(AngBs_2011n)

    
    if SAME_ACC:
        AngBs_2011p.CopyAcc(AngBd_2011p)
        AngBs_2012p.CopyAcc(AngBd_2012p)
        AngBs_2011n.CopyAcc(AngBd_2011n)
        AngBs_2012n.CopyAcc(AngBd_2012n)

    AngBd_2012p.modParam("c1_psi",-0.592,0.1)
    AngBd_2012p.modParam("c2_psi",-0.613,0.1)
    AngBd_2011p.make(), AngBs_2011p.make(), AngBd_2012p.make(), AngBs_2012p.make()
    AngBd_2012n.modParam("c1_psi",-0.592,0.1)
    AngBd_2012n.modParam("c2_psi",-0.613,0.1)
    AngBd_2011n.make(), AngBs_2011n.make(), AngBd_2012n.make(), AngBs_2012n.make()

    mass2011 = SignalMass("2011")
    mass2012 = SignalMass("2012")

    SigBs_2011p = RooProdPdf("Bs pdf 2011p", "Bs pdf 2011p",RooArgList(AngBs_2011p.model,mass2011.sigBs))
    SigBd_2011p = RooProdPdf("Bd pdf 2011p", "Bd pdf 2011p",RooArgList(AngBd_2011p.model,mass2011.sigBd))
    SigBs_2012p = RooProdPdf("Bs pdf 2012p", "Bs pdf 2012p",RooArgList(AngBs_2012p.model,mass2012.sigBs))
    SigBd_2012p = RooProdPdf("Bd pdf 2012p", "Bd pdf 2012p",RooArgList(AngBd_2012p.model,mass2012.sigBd))
    
    SigBs_2011n = RooProdPdf("Bs pdf 2011n", "Bs pdf 2011n",RooArgList(AngBs_2011n.model,mass2011.sigBs))
    SigBd_2011n = RooProdPdf("Bd pdf 2011n", "Bd pdf 2011n",RooArgList(AngBd_2011n.model,mass2011.sigBd))
    SigBs_2012n = RooProdPdf("Bs pdf 2012n", "Bs pdf 2012n",RooArgList(AngBs_2012n.model,mass2012.sigBs))
    SigBd_2012n = RooProdPdf("Bd pdf 2012n", "Bd pdf 2012n",RooArgList(AngBd_2012n.model,mass2012.sigBd))
    
    
    #BREAK
    nd_2011 = RooRealVar("nBd_2011_phys","nBd_2011_phys", 0.5*(t11p.GetEntries() + t11n.GetEntries()),t11p.GetEntries() + t11n.GetEntries())
    ns_2011 = RooFormulaVar("nBs_2011_phys","nBs_2011_phys", "fBs*nBd_2011_phys",RooArgList(fBs,nd_2011))
    
    nd_2011p_phys = RooFormulaVar("nBd_2011p_phys", "nBd_2011p_phys", "nBd_2011_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2011,AngBd_2011p.psACP))
    nd_2011n_phys = RooFormulaVar("nBd_2011n_phys", "nBd_2011n_phys", "nBd_2011_phys - nBd_2011p_phys",RooArgList(nd_2011,nd_2011p_phys))

    ns_2011p_phys = RooFormulaVar("nBs_2011p_phys", "nBs_2011p_phys", "nBs_2011_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2011,AngBs_2011p.psACP))
    ns_2011n_phys = RooFormulaVar("nBs_2011n_phys", "nBs_2011n_phys", "nBs_2011_phys - nBs_2011p_phys",RooArgList(ns_2011,ns_2011p_phys))

    ns_2011p = RooFormulaVar("nBs_2011p","nBs_2011p", "nBs_2011p_phys*(1 + A_D + A_prod_s)",RooArgList(ns_2011p_phys, A_D, Aprod_s))
    ns_2011n = RooFormulaVar("nBs_2011n","nBs_2011n", "nBs_2011n_phys*(1 - A_D - A_prod_s)",RooArgList(ns_2011n_phys, A_D, Aprod_s))

    nd_2011p = RooFormulaVar("nBd_2011p","nBd_2011p", "nBd_2011p_phys*(1 + A_D + A_prod_d)",RooArgList(nd_2011p_phys, A_D, Aprod_d))
    nd_2011n = RooFormulaVar("nBd_2011n","nBd_2011n", "nBd_2011n_phys*(1 - A_D - A_prod_d)",RooArgList(nd_2011n_phys, A_D, Aprod_d))
    
    nbkg_2011p = RooRealVar("n nbkg 11p","n bkg 11p", 0.,0.1*t11p.GetEntries())
    nbkg_2011n = RooRealVar("n nbkg 11n","n bkg 11n", 0.,0.1*t11n.GetEntries())

    nd_2012 = RooRealVar("nBd_2012_phys","nBd_2012_phys", 0.5*(t12p.GetEntries() + t12n.GetEntries()),t12p.GetEntries() + t12n.GetEntries())
    ns_2012 = RooFormulaVar("nBs_2012_phys","nBs_2012_phys", "fBs*nBd_2012_phys",RooArgList(fBs,nd_2012))

    ### Physic assymetries from 2011 ....
    nd_2012p_phys = RooFormulaVar("nBd_2012p_phys", "nBd_2012p_phys", "nBd_2012_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2012,AngBd_2011p.psACP))
    nd_2012n_phys = RooFormulaVar("nBd_2012n_phys", "nBd_2012n_phys", "nBd_2012_phys - nBd_2012p_phys",RooArgList(nd_2012,nd_2012p_phys))

    ns_2012p_phys = RooFormulaVar("nBs_2012p_phys", "nBs_2012p_phys", "nBs_2012_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2012,AngBs_2011p.psACP))
    ns_2012n_phys = RooFormulaVar("nBs_2012n_phys", "nBs_2012n_phys", "nBs_2012_phys - nBs_2012p_phys",RooArgList(ns_2012,ns_2012p_phys))

    ns_2012p = RooFormulaVar("nBs_2012p","nBs_2012p", "nBs_2012p_phys*(1 + A_D + A_prod_s)",RooArgList(ns_2012p_phys, A_D, Aprod_s))
    ns_2012n = RooFormulaVar("nBs_2012n","nBs_2012n", "nBs_2012n_phys*(1 - A_D - A_prod_s)",RooArgList(ns_2012n_phys, A_D, Aprod_s))

    nd_2012p = RooFormulaVar("nBd_2012p","nBd_2012p", "nBd_2012p_phys*(1 + A_D + A_prod_d)",RooArgList(nd_2012p_phys, A_D, Aprod_d))
    nd_2012n = RooFormulaVar("nBd_2012n","nBd_2012n", "nBd_2012n_phys*(1 - A_D - A_prod_d)",RooArgList(nd_2012n_phys, A_D, Aprod_d))
    
    
    nbkg_2012p = RooRealVar("n nbkg 12p","n bkg 12p", 0.,0.1*t12p.GetEntries())
    nbkg_2012n = RooRealVar("n nbkg 12n","n bkg 12n", 0.,0.1*t12n.GetEntries())

## Here
    bkgmodel_2011 = FullBackground("Bkg_2011")
    bkgmodel_2011.thetaFromAcc(AngBd_2011p)
    bkgmodel_2012 = FullBackground("Bkg_2012")
    bkgmodel_2012.thetaFromAcc(AngBd_2012p)
    bkgmodel_2011.make(), bkgmodel_2012.make()
    
    model11p = RooAddPdf("model11p","model11p",RooArgList(SigBs_2011p,SigBd_2011p,bkgmodel_2011.model),RooArgList(ns_2011p,nd_2011p,nbkg_2011p))
    model12p = RooAddPdf("model12p","model12p",RooArgList(SigBs_2012p,SigBd_2012p,bkgmodel_2012.model),RooArgList(ns_2012p,nd_2012p,nbkg_2012p))
    dataset11p = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi, Mass))
    dataset12p = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi, Mass))

    model11n = RooAddPdf("model11n","model11n",RooArgList(SigBs_2011n,SigBd_2011n,bkgmodel_2011.model),RooArgList(ns_2011n,nd_2011n,nbkg_2011n))
    model12n = RooAddPdf("model12n","model12n",RooArgList(SigBs_2012n,SigBd_2012n,bkgmodel_2012.model),RooArgList(ns_2012n,nd_2012n,nbkg_2012n))
    dataset11n = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi, Mass))
    dataset12n = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi, Mass))

    allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi, Mass), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2012p",dataset12p), RooFit.Import("2011n",dataset11n),RooFit.Import("2012n",dataset12n) )
    
    #just_mass_model.fitTo(dataset,RooFit.Minos(1),RooFit.Save())
    #BREAK
    

    Mass.setRange("ref",Mass.getMin(),Mass.getMax())
    CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
    CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
    Phi.setRange("ref",Phi.getMin(),Phi.getMax())
    model11p.fixCoefRange("ref")
    model12p.fixCoefRange("ref")
    model11n.fixCoefRange("ref")
    model12n.fixCoefRange("ref")
    
    #fitres12 = model12.fitTo(dataset12,RooFit.Minos(0),RooFit.Save(), RooFit.Offset(kTRUE))

    fiter = RooSimultaneous("fitter", "fitter", cat)
    fiter.addPdf(model11p,"2011p")
    fiter.addPdf(model12p,"2012p")
    fiter.addPdf(model11n,"2011n")
    fiter.addPdf(model12n,"2012n")

def fit11(minos=0, offset = 0):
    if offset: fitres11 = model11.fitTo(dataset11,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(4),RooFit.Offset(offset))
    else: fitres11 = model11.fitTo(dataset11,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(4))#,RooFit.Offset(offset))
    return fitres11

def fit12(minos=0, offset = 0):
    if offset: fitres12 = model12.fitTo(dataset12,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(4),RooFit.Offset(offset))
    else: fitres12 = model12.fitTo(dataset12,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(4))
    return fitres12

def fixAcc():
    AngBd_2011p.modParam("c1_psi", -5.20101e-01 ,0.1, kTRUE)
    AngBd_2011p.modParam("c2_psi", -7.33299e-01 ,0.1, kTRUE)
    AngBd_2011p.modParam("c3_psi", -2.90606e-01  ,0.1, kTRUE)
    AngBd_2011p.modParam("c4_psi", 2.69475e-01   ,0.1, kTRUE)
    
    AngBd_2011p.modParam("c1_phi",  7.28029e-02 ,0.1, kTRUE)
    AngBd_2011p.modParam("c2_phi",  2.04947e+00 ,0.1, kTRUE)
    AngBd_2011p.modParam("c3_phi",  5.44128e-01 ,0.1, kTRUE)

    AngBd_2011p.modParam("c2_theta",  -1.82470e-01,0.1, kTRUE)

    AngBd_2012p.modParam("c1_psi", -4.98121e-01 ,0.1, kTRUE)
    AngBd_2012p.modParam("c2_psi", -6.66902e-01 ,0.1, kTRUE)
    AngBd_2012p.modParam("c3_psi", -3.78649e-01  ,0.1, kTRUE)
    AngBd_2012p.modParam("c4_psi", 2.24531e-01   ,0.1, kTRUE)
    
    AngBd_2012p.modParam("c1_phi",  8.75128e-02 ,0.1, kTRUE)
    AngBd_2012p.modParam("c2_phi",  1.95453e+00  ,0.1, kTRUE)
    AngBd_2012p.modParam("c3_phi",  4.82842e-01 ,0.1, kTRUE)
    AngBd_2012p.modParam("c2_theta",   -1.68274e-01,0.1, kTRUE)
    
    AngBd_2011n.modParam("c1_psi", -5.20101e-01 ,0.1, kTRUE)
    AngBd_2011n.modParam("c2_psi", -7.33299e-01 ,0.1, kTRUE)
    AngBd_2011n.modParam("c3_psi", -2.90606e-01  ,0.1, kTRUE)
    AngBd_2011n.modParam("c4_psi", 2.69475e-01   ,0.1, kTRUE)
    
    AngBd_2011n.modParam("c1_phi",  7.28029e-02 ,0.1, kTRUE)
    AngBd_2011n.modParam("c2_phi",  2.04947e+00 ,0.1, kTRUE)
    AngBd_2011n.modParam("c3_phi",  5.44128e-01 ,0.1, kTRUE)

    AngBd_2011n.modParam("c2_theta",  -1.82470e-01,0.1, kTRUE)

    AngBd_2012n.modParam("c1_psi", -4.98121e-01 ,0.1, kTRUE)
    AngBd_2012n.modParam("c2_psi", -6.66902e-01 ,0.1, kTRUE)
    AngBd_2012n.modParam("c3_psi", -3.78649e-01  ,0.1, kTRUE)
    AngBd_2012n.modParam("c4_psi", 2.24531e-01   ,0.1, kTRUE)
    
    AngBd_2012n.modParam("c1_phi",  8.75128e-02 ,0.1, kTRUE)
    AngBd_2012n.modParam("c2_phi",  1.95453e+00  ,0.1, kTRUE)
    AngBd_2012n.modParam("c3_phi",  4.82842e-01 ,0.1, kTRUE)
    AngBd_2012n.modParam("c2_theta",   -1.68274e-01,0.1, kTRUE)
    
def fitAll(minos=0, offset = 0, noCP = 0):
    fixAcc()
    if noCP:
        AngBd_2011p.ACPL.setVal(0)
        AngBs_2011p.ACPL.setVal(0)
        AngBd_2011p.ACPL.setConstant(1)
        AngBs_2011p.ACPL.setConstant(1)
        A_D.setMin(-0.3)
        A_D.setMax(0.3)
        A_D.setConstant(0)
    
    if offset: fitres = fiter.fitTo(allData,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8),RooFit.Offset(kTRUE))
    else: fitres = fiter.fitTo(allData,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8))
    return fitres
    
        
def plotAngle(name,rangename,nbins):
    
    name = str(name)
    if "11p" in name:
        model = model11p
        dataset = dataset11p
    if "11n" in name:
        model = model11n
        dataset = dataset11n
    if "12p" in name:
        model = model12p
        dataset = dataset12p
    if "12n" in name:
        model = model12n
        dataset = dataset12n
    
        
    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
#     model.paramOn(cpsif)
    cpsif.Draw()

    cv3.cd(2)
    cthf = CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cthf.Draw()

    cv3.cd(3)
    cphif = Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cphif.Draw()

    return cv3, cphif,cthf, cpsif

    
def plot_mass(name, nbins = 100):
    
    name = str(name)
    cv3 = TCanvas()
    
    if "11p" in name:
        model = model11p
        dataset = dataset11p
    if "11n" in name:
        model = model11n
        dataset = dataset11n
    if "12p" in name:
        model = model12p
        dataset = dataset12p
    if "12n" in name:
        model = model12n
        dataset = dataset12n
   
        
    cphif = Mass.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    model.plotOn(cphif)
    model.plotOn(cphif,RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cphif,RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cphif,RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    #model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cphif.Draw()

    return cv3, cphif#,cthf, cpsif

## ratioBs = RooFormulaVar("rBs","rBs", "nBs/nBd", RooArgList(ns,nd))
## print "NBs/NBd = ", ratioBs.getVal(), "+/-", ratioBs.getPropagatedError(fitres)
## print "Apa2 Bd = ", AngBd.Apa2.getVal(), "+/-", AngBd.Apa2.getPropagatedError(fitres)
## print "Ape2 Bd = ", AngBd.Ape2.getVal(), "+/-", AngBd.Ape2.getPropagatedError(fitres)
## print "As2 Bd = ", AngBd.As2.getVal(), "+/-", AngBd.As2.getPropagatedError(fitres)
## print "Apa2 Bs = ", AngBs.Apa2.getVal(), "+/-", AngBs.Apa2.getPropagatedError(fitres)
## print "Ape2 Bs = ", AngBs.Ape2.getVal(), "+/-", AngBs.Ape2.getPropagatedError(fitres)
## print "As2 Bs = ", AngBs.As2.getVal(), "+/-", AngBs.As2.getPropagatedError(fitres)

## ### Renormalized to 1

## rA02d = RooFormulaVar("rA02d","rA02d","A02Bd/(A02Bd+Apa2Bd+Ape2Bd)",RooArgList(AngBd.A02,AngBd.Apa2,AngBd.Ape2))
## rApa2d = RooFormulaVar("rApa2d","rApa2d","Apa2Bd/(A02Bd+Apa2Bd+Ape2Bd)",RooArgList(AngBd.A02,AngBd.Apa2,AngBd.Ape2))
## rApe2d = RooFormulaVar("rApe2d","rApe2d","Ape2Bd/(A02Bd+Apa2Bd+Ape2Bd)",RooArgList(AngBd.A02,AngBd.Apa2,AngBd.Ape2))
## rA02s = RooFormulaVar("rA02s","rA02s","A02Bs/(A02Bs+Apa2Bs+Ape2Bs)",RooArgList(AngBs.A02,AngBs.Apa2,AngBs.Ape2))
## rApa2s = RooFormulaVar("rApa2s","rApa2s","Apa2Bs/(A02Bs+Apa2Bs+Ape2Bs)",RooArgList(AngBs.A02,AngBs.Apa2,AngBs.Ape2))
## rApe2s = RooFormulaVar("rApe2s","rApe2s","Ape2Bs/(A02Bs+Apa2Bs+Ape2Bs)",RooArgList(AngBs.A02,AngBs.Apa2,AngBs.Ape2))
## print "RENORMALZED"
## print "r Apa2 Bd = ", rApa2d.getVal(), "+/-", rApa2d.getPropagatedError(fitres)
## print "r Ape2 Bd = ", rApe2d.getVal(), "+/-", rApe2d.getPropagatedError(fitres)
## print "r A02 Bd = ", rA02d.getVal(), "+/-", rA02d.getPropagatedError(fitres)
## print "r Apa2 Bs = ", rApa2s.getVal(), "+/-", rApa2s.getPropagatedError(fitres)
## print "r Ape2 Bs = ", rApe2s.getVal(), "+/-", rApe2s.getPropagatedError(fitres)
## print "r A02 Bs = ", rA02s.getVal(), "+/-", rA02s.getPropagatedError(fitres)



## cv1, psif1, thf1, phif1 = replot("Bd_range",50)
## cv2, psif2, thf2, phif2 = replot("Bs_range",10)
## cv3, mf = plot_mass(100)

## cv1.SaveAs("Bd_fit_FL_MC11MC11_pol.root")
## cv2.SaveAs("Bs_fit_FL_MC11MC11_pol.root")
## cv3.SaveAs("Mass_fit_FL_MC11MC11_pol.root")
## ## fmcd = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJpsiKstTotMC11_v2.root")
## ## tmcd2 = fmcd.Get("T/T")


## ## tmcd = tmcd2.CopyTree(cuts+"&& GL11sb.>0.2 && abs(B0_MM-5279)<25")
## def plot_jmass(nbins):
##     cv3 = TCanvas()    
##     cphif = Mass.frame()
##     RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
##     just_mass_model.plotOn(cphif)
##     ## model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
## ##     model.plotOn(cphif,RooFit.Components("Bs pdf"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
## ##     model.plotOn(cphif,RooFit.Components("Bd pdf"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
## ##     #model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
##     cphif.Draw()

##     return cv3, cphif#,cthf, cpsif






### 2012

 ##  NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
##    1  As2Bs        1.04617e-02   8.94282e-03   1.74647e-03  -1.37615e+01
##    2  c1_phiBd2012   8.75128e-02   6.55108e-03   4.22613e-01   4.86258e-01
##    3  c1_phiBkg_2012   6.59267e-02   6.37163e-02   3.15944e-04   6.59746e-02
##    4  c1_psiBd2012  -4.98121e-01   1.39279e-01   2.32634e-03   1.21910e+00
##    5  c2_phiBd2012   1.95453e+00   4.12700e-02   5.00000e-01  -6.14050e-01
##    6  c2_phiBkg_2012   1.43560e-02   1.63941e-02   3.07372e-03  -1.12972e+00
##    7  c2_psiBd2012  -6.66902e-01   1.20411e-01   5.00000e-01  -5.69269e-01
##    8  c2_thetaBd2012  -1.68274e-01   1.16891e-02   3.89757e-03   2.70656e-01
##    9  c3_phiBd2012   4.82842e-01   6.40953e-02   4.44267e-01   6.90397e-01
##   10  c3_phiBkg_2012  -1.92045e-02   9.92086e-03   4.95244e-04  -1.93246e-01
##   11  c3_psiBd2012  -3.78649e-01   2.86916e-02   1.17852e-02  -2.49301e-02
##   12  c4_psiBd2012   2.24531e-01   9.56314e-02   9.00116e-04   1.44245e-01
##   13  delta_s2012   7.69184e+00   3.57118e-01   2.35347e-04  -4.40374e-02
##   14  dpaBs       -3.14416e+00   6.04074e-01   5.00000e-01  -1.63423e-03
##   15  dsBs         1.80793e-02   1.85053e+00   5.00000e-01  -1.41893e+00
##   16  f small res2012   7.68788e-01   1.57721e-02   5.74900e-04   5.67560e-01
##   17  fBs          8.34464e-03   4.72419e-04   1.02989e-03  -1.01907e+00
##   18  fLBs         5.82232e-01   3.95537e-02   2.53881e-03   7.73729e-01
##   19  fpaBs        1.20620e-01   3.84086e-02   4.19345e-03  -6.92454e-01
##   20  kBkg_2012   -2.54186e-03   4.29126e-04   9.93237e-05   1.46992e+00
##   21  mean12012    5.28132e+03   3.50469e-02   4.17192e-05  -5.89882e-01
##   22  n nbkg 12    1.10380e+03   5.52664e+01   2.65998e-04  -6.61840e-01
##   23  nBd_2012     5.57073e+04   2.38262e+02   4.29626e-04   1.09832e+00
##   24  sigma12012   6.67359e+00   7.31154e-02   2.38882e-04  -7.25095e-01
##                                ERR DEF= 0.5
