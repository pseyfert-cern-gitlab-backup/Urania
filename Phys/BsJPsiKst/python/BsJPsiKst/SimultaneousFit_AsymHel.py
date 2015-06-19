
from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Asym import *

print "Class for fitting polarization: AngularPDF"

timeZero = time.time()


ACC_FREE = 0
FIX_Bd = ACC_FREE
SAME_ACC = 1

SFIT = 2 # 0: cFit, 1: compute only sweights with cFit, 2: full sFit
         # you should also change this condition in PDF_2013_Asym 
YEAR = 1211 # choose 2011, 2012 or 1211->2011+2012 data  
WEIGHT_CAT = "Bs" # type of weights: Bs, Bd or none for the cFit
# Tuples for classic fit (without any weight)
# version BDTG, KstarWide stripping Line, from Diego
print "\n IMPORTANT MESSAGE "
print "\n ####################################################################"
print "\n You choose: SFIT= ",SFIT,", YEAR= ",YEAR,", WEIGHT_CAT= ",WEIGHT_CAT
print "\n ####################################################################"

if SFIT==0:
    t11p,f11p = getTuple("/zfs_lhcb/users/kanso/realData/for_jpsiK/2011p", thing = "DecayTree")
    t11n,f11n = getTuple("/zfs_lhcb/users/kanso/realData/for_jpsiK/2011n", thing = "DecayTree")
    t12p,f12p = getTuple("/zfs_lhcb/users/kanso/realData/for_jpsiK/2012p", thing = "DecayTree")
    t12n,f12n = getTuple("/zfs_lhcb/users/kanso/realData/for_jpsiK/2012n", thing = "DecayTree")



elif SFIT==2:

    t2_11,f11 = getTuple("data2011_sWeights_"+WEIGHT_CAT, thing = "DecayTree")
    fx=TFile("SimulFit_nada.root","recreate")
    t11p=t2_11.CopyTree("Kplus_ID>0")
    t11n=t2_11.CopyTree("Kplus_ID<0")
    t2_12,f12 = getTuple("data2012_sWeights_"+WEIGHT_CAT, thing = "DecayTree")
    fx2=TFile("SimulFit_nada2.root","recreate")
    t12p=t2_12.CopyTree("Kplus_ID>0")
    t12n=t2_12.CopyTree("Kplus_ID<0")
else: 
    if (YEAR==2011):
        pathTuple = "/zfs_lhcb/users/kanso/2011diego20131115.root"
        print "sWeights extraction for Bs2JpsiKst data."
        os.system("cp "+pathTuple+" ./test_data2011_sWeights_"+WEIGHT_CAT+".root") 
        fx=TFile("junk2011p.root","recreate") 

        Mmax = 5450.
        cuts = "B0_MM>5150. && B0_MM<"+str(Mmax)
        f11 = TFile("./test_data2011_sWeights_"+WEIGHT_CAT+".root","update") 
        t2_11 = f11.Get("DecayTree")
        t11=t2_11.CopyTree(cuts)
    else:
        pathTuple = "/zfs_lhcb/users/kanso/2012diego20131115.root"
        print "sWeights extraction for Bs2JpsiKst data."

        os.system("cp "+pathTuple+" ./data2012_sWeights_"+WEIGHT_CAT+".root") 
        fx=TFile("junk2012p.root","recreate") 

        Mmax = 5450.
        cuts = "B0_MM>5150. && B0_MM<"+str(Mmax)
        f12 = TFile("./data2012_sWeights_"+WEIGHT_CAT+".root","update") 
        t2_12 = f12.Get("DecayTree")
        t12=t2_12.CopyTree(cuts)
    
    
    



if (SFIT==0 or SFIT ==2):
    samplename = "sample"
    cat =  RooCategory(samplename, samplename)
    if (YEAR==2011 or YEAR==1211):
        cat.defineType("2011p"), cat.defineType("2011n")
    if (YEAR==2012 or YEAR==1211):
        cat.defineType("2012p"), cat.defineType("2012n")
    else:
        print "check your ntuples1"

    s_a = 5.

    Mass.setRange("Bs_range",5366.77-25,5366.77+25) 
    Mass.setRange("Bd_range",5279.5-25,5279.5+25)

# Angular PDF for Bd: 
#  define 2011p and copy all param in 2011n
    AngBd_2011p,  AngBd_2011n = InitSignalPdfs("Bd","2011")
    AngBd_2011p.OwnPhys(equalAsym = 1)
    AngBd_2011p.OwnAcc()
    fix_param= kTRUE
    if (WEIGHT_CAT=="Bd"):
      fix_param=kFALSE
    else:
      fix_param= kTRUE

      
    if (WEIGHT_CAT== "Bs" or WEIGHT_CAT=="none"):
        AngBd_2011p.modParam("fL",0.5488,0.1,kTRUE)
        AngBd_2011p.modParam("fpa",0.2392,0.1,kTRUE)
        AngBd_2011p.modParam("As2",0.047,0.01,kTRUE)
        AngBd_2011p.modParam("dpa",-2.98,0.1,kTRUE)
        AngBd_2011p.modParam("dpe",3.07-pi,0.1,kTRUE)
        AngBd_2011p.modParam("ds",2.20,0.1,kTRUE)
        AngBd_2011p.modParam("c1_psi",-0.592,0.1)
    

    else:
        AngBd_2011p.modParam("fL",0.5488,0.5*pi,fix_param)
        AngBd_2011p.modParam("fpa",0.2392,0.5*pi,fix_param)
        AngBd_2011p.modParam("As2",0.047,0.01,kTRUE)
        AngBd_2011p.modParam("dpa",-2.98,0.5*pi,fix_param)
        AngBd_2011p.modParam("dpe",2.94,0.5*pi,fix_param)
        AngBd_2011p.modParam("ds",2.20,0.1,kTRUE)
        AngBd_2011p.modParam("c1_psi",-0.592,0.1)

    AngBd_2011n.CopyFreeParams(AngBd_2011p)
    AngBd_2011n.CopyAcc(AngBd_2011p)
    AngBd_2011n.modParam("c1_psi",-0.592,0.1)
    

# Angular PDF for Bs
#  define 2011n and copy all in 2011p
    AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011")

    AngBs_2011p.OwnPhys()
    AngBs_2011p.modParam("dpe",0,pi)
    AngBs_2011p.modParam("dpa",-pi,pi*.5)
    AngBs_2011n.CopyFreeParams(AngBs_2011p)
    
# Now copy 2011 into 2012, dor Bd, Bs, n and p    
    AngBd_2012p,  AngBd_2012n = InitSignalPdfs("Bd","2012")
    AngBd_2012p.CopyPhys(AngBd_2011p)
    AngBd_2012p.CopyAcc(AngBd_2011p)
    AngBd_2012n.CopyPhys(AngBd_2011n)
    AngBd_2012n.CopyAcc(AngBd_2011p)

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



if SFIT== 1:
    
    samplename = "sample"
    cat =  RooCategory(samplename, samplename)
    if (YEAR==2011):
        cat.defineType("2011")
        mass2011 = SignalMass("2011")
        nd_2011 = RooRealVar("nBd_2011","nBd_2011", 0.5*(t11.GetEntries()),t11.GetEntries())
        ns_2011 = RooRealVar("nBs_2011","nBs_2011", 0.,0.5*(t11.GetEntries()))
        nbkg_2011 = RooRealVar("n bkg 11","n bkg 11", 0.,t11.GetEntries())
        #HEREself.kbkg = RooRealVar("k"+name,"k"+name,-1e-03,-1e-02,0)
        # HERE self.massbkg = RooExponential("Mass" + name, "Mass" + name, Mass, self.kbkg)
        bkgmodel_2011 = FullBackground("Bkg_2011")
        bkgmodel_2011.make()

        model11 = RooAddPdf("model11","model11",RooArgList(mass2011.sigBs,mass2011.sigBd,bkgmodel_2011.model),RooArgList(ns_2011,nd_2011,nbkg_2011))
        dataset11 = RooDataSet("data11","data11",t11,RooArgSet(Mass))
    
    elif (YEAR==2012):
        cat.defineType("2012")
        mass2012 = SignalMass("2012")
        nd_2012 = RooRealVar("nBd_2012","nBd_2012", 0.5*(t12.GetEntries()),t12.GetEntries())
        ns_2012 = RooRealVar("nBs_2012","nBs_2012", 0.,0.5*(t12.GetEntries()))
        nbkg_2012 = RooRealVar("n bkg 12","n bkg 12", 0.,t12.GetEntries())

        bkgmodel_2012 = FullBackground("Bkg_2012")
        bkgmodel_2012.make()

        model12 = RooAddPdf("model12","model12",RooArgList(mass2012.sigBs,mass2012.sigBd,bkgmodel_2012.model),RooArgList(ns_2012,nd_2012,nbkg_2012))
        dataset12 = RooDataSet("data12","data12",t12,RooArgSet(Mass))
    
        print "t12 entries :   ",t12.GetEntries()
        print "t12 - dataset12 ", t12.GetEntries()-dataset12.sumEntries()
    else:
        "check your ntuples2"

if SFIT == 2:

 if WEIGHT_CAT=="Bs":
     model11p = AngBs_2011p.model
     model12p = AngBs_2012p.model
     dataset11p = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs))
     dataset12p = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs))
    

     model11n = AngBd_2011n.model
     model12n = AngBd_2012n.model
     dataset11n = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs))
     dataset12n = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs))
    

     if(YEAR==2011):
         allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,sWeights_Bs), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("sWeights_Bs"))
     elif(YEAR==2012):
         allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,sWeights_Bs), RooFit.Index(cat), RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("sWeights_Bs"))
     else:
         allData = RooDataSet("all Data"
,"all Data", RooArgSet(CPsi,CTheta,Phi,sWeights_Bs), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("sWeights_Bs")) 
    
         

 if WEIGHT_CAT=="Bd":
     
     model11p = AngBd_2011p.model
     model12p = AngBd_2012p.model
     
     dataset11p = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi,sWeights_Bd))
     dataset12p = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi,sWeights_Bd))

     model11n = AngBd_2011n.model
     model12n = AngBd_2012n.model
     dataset11n = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi,sWeights_Bd))
     dataset12n = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi,sWeights_Bd))

     if(YEAR==2011):
      allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,sWeights_Bd), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("sWeights_Bd"))
     elif(YEAR==2012):
         allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,sWeights_Bd), RooFit.Index(cat), RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("sWeights_Bd"))
     else:
        allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,sWeights_Bd), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("sWeights_Bd")) 

     

 print " ####################################### in SFIT=2   ", 
 print " "


 dataset11n.Print()
 dataset11p.Print()
 dataset12n.Print()
 dataset12p.Print()
 allData.Print()    
 Mass.setRange("ref",Mass.getMin(),Mass.getMax())


#################################################################################################
# cFit
#################################################################################################
if SFIT==0: 

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
    
    
 nd_2011 = RooRealVar("nBd_2011_phys","nBd_2011_phys", 0.5*(t11p.GetEntries() + t11n.GetEntries()),t11p.GetEntries() + t11n.GetEntries())
 ns_2011 = RooFormulaVar("nBs_2011_phys","nBs_2011_phys", "fBs*nBd_2011_phys",RooArgList(fBs,nd_2011))
    
 nd_2011p_phys = RooFormulaVar("nBd_2011p_phys", "nBd_2011p_phys", "nBd_2011_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2011,AngBd_2011p.psACP))
 nd_2011n_phys = RooFormulaVar("nBd_2011n_phys", "nBd_2011n_phys", "nBd_2011_phys - nBd_2011p_phys",RooArgList(nd_2011,nd_2011p_phys))
 
 ns_2011p_phys = RooFormulaVar("nBs_2011p_phys", "nBs_2011p_phys", "nBs_2011_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2011,AngBs_2011p.psACP))
 ns_2011n_phys = RooFormulaVar("nBs_2011n_phys", "nBs_2011n_phys", "nBs_2011_phys - nBs_2011p_phys",RooArgList(ns_2011,ns_2011p_phys))
 
 ns_2011p = RooFormulaVar("nBs_2011p","nBs_2011p", "nBs_2011p_phys*(1 + A_D - A_prod_s)",RooArgList(ns_2011p_phys, A_D, Aprod_s)) #wk 
 ns_2011n = RooFormulaVar("nBs_2011n","nBs_2011n", "nBs_2011n_phys*(1 - A_D + A_prod_s)",RooArgList(ns_2011n_phys, A_D, Aprod_s))  
 
 nd_2011p = RooFormulaVar("nBd_2011p","nBd_2011p", "nBd_2011p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2011p_phys, A_D, Aprod_d))
 nd_2011n = RooFormulaVar("nBd_2011n","nBd_2011n", "nBd_2011n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2011n_phys, A_D, Aprod_d))
 
 nbkg_2011p = RooRealVar("n nbkg 11p","n bkg 11p", 0.,t11p.GetEntries())
 nbkg_2011n = RooRealVar("n nbkg 11n","n bkg 11n", 0.,t11n.GetEntries())
 
 nd_2012 = RooRealVar("nBd_2012_phys","nBd_2012_phys", 0.5*(t12p.GetEntries() + t12n.GetEntries()),t12p.GetEntries() + t12n.GetEntries())
 ns_2012 = RooFormulaVar("nBs_2012_phys","nBs_2012_phys", "fBs*nBd_2012_phys",RooArgList(fBs,nd_2012))

 
 nd_2012p_phys = RooFormulaVar("nBd_2012p_phys", "nBd_2012p_phys", "nBd_2012_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2012,AngBd_2011p.psACP))
 nd_2012n_phys = RooFormulaVar("nBd_2012n_phys", "nBd_2012n_phys", "nBd_2012_phys - nBd_2012p_phys",RooArgList(nd_2012,nd_2012p_phys))

 ns_2012p_phys = RooFormulaVar("nBs_2012p_phys", "nBs_2012p_phys", "nBs_2012_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2012,AngBs_2011p.psACP))
 ns_2012n_phys = RooFormulaVar("nBs_2012n_phys", "nBs_2012n_phys", "nBs_2012_phys - nBs_2012p_phys",RooArgList(ns_2012,ns_2012p_phys))

 ns_2012p = RooFormulaVar("nBs_2012p","nBs_2012p", "nBs_2012p_phys*(1 + A_D - A_prod_s)",RooArgList(ns_2012p_phys, A_D, Aprod_s))
 ns_2012n = RooFormulaVar("nBs_2012n","nBs_2012n", "nBs_2012n_phys*(1 - A_D + A_prod_s)",RooArgList(ns_2012n_phys, A_D, Aprod_s))

 nd_2012p = RooFormulaVar("nBd_2012p","nBd_2012p", "nBd_2012p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2012p_phys, A_D, Aprod_d))
 nd_2012n = RooFormulaVar("nBd_2012n","nBd_2012n", "nBd_2012n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2012n_phys, A_D, Aprod_d))


 nbkg_2012p = RooRealVar("n nbkg 12p","n bkg 12p", 0.,t12p.GetEntries())
 nbkg_2012n = RooRealVar("n nbkg 12n","n bkg 12n", 0.,t12n.GetEntries())

 
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

 print " ####################################### in SFIT=0 (i.e. cFit)  ", 

 dataset11n.Print()
 dataset11p.Print()
 dataset12n.Print()
 dataset12p.Print()

 allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi, Mass), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2012p",dataset12p), RooFit.Import("2011n",dataset11n),RooFit.Import("2012n",dataset12n) )
 

 allData.Print()    
 Mass.setRange("ref",Mass.getMin(),Mass.getMax())

# ) end of if not SFIT

CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())

if not SFIT:
 model11p.fixCoefRange("ref")
 model12p.fixCoefRange("ref")
 model11n.fixCoefRange("ref")
 model12n.fixCoefRange("ref")
    

    
fiter = RooSimultaneous("fitter", "fitter", cat)

if (SFIT==0 or SFIT==2):
 if (YEAR == 2011 or YEAR==1211): 
  fiter.addPdf(model11p,"2011p")
  fiter.addPdf(model11n,"2011n")
 if (YEAR == 2012 or YEAR==1211):
  fiter.addPdf(model12p,"2012p")
  fiter.addPdf(model12n,"2012n")
 else: 
  print "check your ntuples3"
else:
 if (YEAR == 2011): 
    fiter.addPdf(model11,"2011")
 elif (YEAR == 2012): 
    fiter.addPdf(model12,"2012")
 else:
    print "check your ntuples4" 

def fixAcc():
    if (WEIGHT_CAT=="Bd" or WEIGHT_CAT=="none"):
        AngBd_2011p.modParam("c1_psi", -5.20101e-01 ,0.1, kTRUE)
        AngBd_2011p.modParam("c2_psi", -7.33299e-01 ,0.1, kTRUE)
        AngBd_2011p.modParam("c3_psi", -2.90606e-01  ,0.1, kTRUE)
        AngBd_2011p.modParam("c4_psi", 2.69475e-01   ,0.1, kTRUE) 
        AngBd_2011p.modParam("c2_theta", 2.76201e-01   ,0.1, kTRUE)
    elif WEIGHT_CAT=="Bs":  
        AngBs_2011p.modParam("c1_psi", -5.20101e-01 ,0.1, kTRUE)
        AngBs_2011p.modParam("c2_psi", -7.33299e-01 ,0.1, kTRUE)
        AngBs_2011p.modParam("c3_psi", -2.90606e-01  ,0.1, kTRUE)
        AngBs_2011p.modParam("c4_psi", 2.69475e-01   ,0.1, kTRUE) 
        AngBs_2011p.modParam("c2_theta", 2.76201e-01   ,0.1, kTRUE)
   
    
def fitAll(minos=0, offset = 0, noCP = 0):
    fixAcc()  # you can leave acc param free by not calling the function "fixAcc()".
    if noCP:fixCP() 
    AngBd_2011p.ACPL.setVal(-0.002) #check
    AngBd_2011p.ACPL.setConstant(1) #check
    AngBs_2011p.ds.setVal(1.1) #check
    AngBs_2011p.ds.setConstant(1) #check
    if offset: 
        fitres = fiter.fitTo(allData,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8),RooFit.Offset(kTRUE),RooFit.SumW2Error(kTRUE))
    else: 
        fitres = fiter.fitTo(allData,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE))
    return fitres
        

def computeWeights12():
        
    gROOT.ProcessLine("struct MyStruct{Float_t sWFloat;};")
    gROOT.ProcessLine("struct MyStruct2{Float_t cor_sWFloat;};")
    from ROOT import MyStruct
    from ROOT import MyStruct2
    
    
    sWValue = MyStruct()
    cor_sWValue = MyStruct2()
    sWeights_Bs_F = "sWeights_" +WEIGHT_CAT+"/F"
    sWBranch = t12.Branch("sWeights_"+WEIGHT_CAT, AddressOf(sWValue,'sWFloat'),"sWeights_"+WEIGHT_CAT+"/F") 
    cor_sWBranch = t12.Branch("cor_sWeights_"+WEIGHT_CAT, AddressOf(cor_sWValue,'cor_sWFloat'), "cor_sWeights_"+WEIGHT_CAT+"/F") 
#############
    minos = 0
    yield_cat=0
    if(WEIGHT_CAT=="Bs"):
     yield_cat=0
    else:
     yield_cat=1

    fitres = model12.fitTo(dataset12,RooFit.Minos(minos),RooFit.Save(),RooFit.NumCPU(8))

    yieldNames = ['nBs_2012','nBd_2012','n bkg 12']
    sData = RooStats.SPlot("sData","An SPlot",dataset12,model12,RooArgList(ns_2012,nd_2012,nbkg_2012))
        
## Extracting sWeights:
    sWList = []
    corrFactor=0.
    sumW=0.
    sumSqW=0.
        
    for nPar in range(len(yieldNames)):
        sWList.append([])
        print '\nExtracting sWeights...'
    for entry in range(int(t12.GetEntries())):
        for yName in range(len(yieldNames)):
            sWList[yName].append(sData.GetSWeight(entry,yieldNames[yName]))
               
## Filling the branch:
            
        sWValue.sWFloat = sWList[yield_cat][entry]
        sWBranch.Fill()

        sumW += sWList[yield_cat][entry]
        sumSqW+= (sWList[yield_cat][entry])**2
        
##################################
        
    corrFactor=sumW/sumSqW
    print "corrFactor=sumW/sumSqW= ",corrFactor 
    for entry in range(int(t12.GetEntries())):
        cor_sWValue.cor_sWFloat = corrFactor*sWList[yield_cat][entry]
        cor_sWBranch.Fill()
    print '\nElapsed time: ' + str(time.time()-timeZero) + ' s.'
    t12.Write("",TObject.kOverwrite)
    f12.Close()

    
    return 0


def computeWeights11():
        
    gROOT.ProcessLine("struct MyStruct{Float_t sWFloat;};")
    gROOT.ProcessLine("struct MyStruct2{Float_t cor_sWFloat;};")
    from ROOT import MyStruct
    from ROOT import MyStruct2
    
    
    sWValue = MyStruct()
    cor_sWValue = MyStruct2()
    sWeights_Bs_F = "sWeights_" +WEIGHT_CAT+"/F"
    sWBranch = t11.Branch("sWeights_"+WEIGHT_CAT, AddressOf(sWValue,'sWFloat'),"sWeights_"+WEIGHT_CAT+"/F") 
    cor_sWBranch = t11.Branch("cor_sWeights_"+WEIGHT_CAT, AddressOf(cor_sWValue,'cor_sWFloat'), "cor_sWeights_"+WEIGHT_CAT+"/F") 
#############
    minos = 0
    yield_cat=0
    if(WEIGHT_CAT=="Bs"):
     yield_cat=0
    else:
     yield_cat=1
    fitres = model11.fitTo(dataset11,RooFit.Minos(minos),RooFit.Save(),RooFit.NumCPU(8))

    yieldNames = ['nBs_2011','nBd_2011','n bkg 11']
    sData = RooStats.SPlot("sData","An SPlot",dataset11,model11,RooArgList(ns_2011,nd_2011,nbkg_2011))
        
## Extracting sWeights:
    sWList = []
    corrFactor=0.
    sumW=0.
    sumSqW=0.
        
    for nPar in range(len(yieldNames)):
        sWList.append([])
        print '\nExtracting sWeights...'
    for entry in range(int(t11.GetEntries())):
        for yName in range(len(yieldNames)):
            sWList[yName].append(sData.GetSWeight(entry,yieldNames[yName]))
               
## Filling the branch:
            
        sWValue.sWFloat = sWList[yield_cat][entry]
        sWBranch.Fill()

        sumW += sWList[yield_cat][entry]
        sumSqW+= (sWList[yield_cat][entry])**2
        
##################################
        
    corrFactor=sumW/sumSqW
    print "corrFactor=sumW/sumSqW= ",corrFactor 
    for entry in range(int(t11.GetEntries())):
        cor_sWValue.cor_sWFloat = corrFactor*sWList[yield_cat][entry]
        cor_sWBranch.Fill()
    print '\nElapsed time: ' + str(time.time()-timeZero) + ' s.'
    t11.Write("",TObject.kOverwrite)
    f11.Close()

    
    return 0


def fixCP():
    #AngBd_2011p.ACPL.setVal(0) #check
    AngBs_2011p.ACPL.setVal(0)
    #AngBd_2011p.ACPL.setConstant(1) #check
    AngBs_2011p.ACPL.setConstant(1)
    #AngBd_2011p.ACPpa.setVal(0)
    AngBs_2011p.ACPpa.setVal(0)
    #AngBd_2011p.ACPpa.setConstant(1)
    AngBs_2011p.ACPpa.setConstant(1)
    #AngBd_2011p.ACPpe.setVal(0)
    AngBs_2011p.ACPpe.setVal(0)
    #AngBd_2011p.ACPpe.setConstant(1)
    AngBs_2011p.ACPpe.setConstant(1)
    AngBs_2011p.ds.setVal(1.1) #check
    AngBs_2011p.ds.setConstant(1) #check
    A_D.setMin(-0.3)
    A_D.setMax(0.3)
    #A_D.setConstant(0)
    A_D.setVal(-0.01185)
    A_D.setConstant(kTRUE)
           
def plotAngle(name,rangename,nbins):
    
    name = str(name)
    if "11p" in name:
        model = model11p
        if (SFIT==0):
            dataset = dataset11p
        else:
            dataset = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs),"","sWeights_"+WEIGHT_CAT)
    if "11n" in name:
        model = model11n
        if (SFIT==0): 
            dataset = dataset11n
        else:
            dataset = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs),"","sWeights_"+WEIGHT_CAT)
    if "12p" in name:
        model = model12p
        if (SFIT==0):
            dataset = dataset12p
        else:
            dataset = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs),"","sWeights_"+WEIGHT_CAT)
    if "12n" in name:
        model = model12n
        if (SFIT==0):
            dataset = dataset12n
        else:
            dataset = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi,sWeights_Bs),"","sWeights_"+WEIGHT_CAT)
    
        
    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename))
    if (SFIT==0):
        model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
        model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
        model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    if (WEIGHT_CAT=="Bs"):
        model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    if (WEIGHT_CAT=="Bd"):
        model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.LineColor(kRed),RooFit.LineStyle(7))

    cpsif.SetTitle("")
    cpsif.SetXTitle("cos(\Psi)")
    cpsif.Draw()

    cv3.cd(2)
    cthf = CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename))
    if (SFIT==0):
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    if (WEIGHT_CAT=="Bs"):
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    if (WEIGHT_CAT=="Bd"):
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cthf.SetTitle("")
    cthf.SetXTitle("cos(\Theta)")
    cthf.Draw()

    cv3.cd(3)
    cphif = Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename))
    if (SFIT==0):
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    if (WEIGHT_CAT=="Bs"):
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    if (WEIGHT_CAT=="Bd"):
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cphif.SetTitle("")
    cphif.SetXTitle("cos(\phi)")
    cphif.Draw()

    return cv3, cphif,cthf, cpsif


def plot_mass(name, nbins = 100):
    
    name = str(name)
    cv3 = TCanvas()
    
    if (SFIT==1):
        if YEAR==2012:
            model = model12
            dataset = dataset12
        if YEAR==2011:
            model = model11
            dataset = dataset11
    if (SFIT==0 or SFIT==2):
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

    cphif.SetTitle("")
    cphif.SetXTitle("M_{J/\Psi K\pi} (MeV/c^{2})")
    cphif.Draw()

    return cv3, cphif#,cthf, cpsif


if SFIT==1:
    if (YEAR==2011):
     my_int = computeWeights11()
     os.system('rm junk2011p.root')
    else:
     my_int = computeWeights12()
     os.system('rm junk2012p.root')
        
elif (SFIT==2 or SFIT==0):
 fitres = fitAll(minos = 0, offset = 0)
 ff = TFile("FitResults.root","recreate")
 fitres.Write("FitResults")
 ff.Close()

else:
  print "fit function is not called" 

#-------------------------------------------------
if (YEAR==2011 or YEAR==1211):  
  
  if(SFIT==0 or SFIT==2):

   if (WEIGHT_CAT=="Bd" or WEIGHT_CAT=="none"):
       Bd_cv11p, Bd_psif11p, Bd_thf11p, Bd_phif11p = plotAngle("2011p","",70)
       Bd_cv11n, Bd_psif11n, Bd_thf11n, Bd_phif11n = plotAngle("2011n","",70)
       Bd_cv11p.SaveAs("Bd_cv11p_"+WEIGHT_CAT+".root")
       Bd_cv11n.SaveAs("Bd_cv11n_"+WEIGHT_CAT+".root")
       
   if(WEIGHT_CAT=="Bs" or WEIGHT_CAT=="none"):
       Bs_cv11p, Bs_psif11p, Bs_thf11p, Bs_phif11p = plotAngle("2011p","",30)
       Bs_cv11n, Bs_psif11n, Bs_thf11n, Bs_phif11n = plotAngle("2011n","",30)
       Bs_cv11p.SaveAs("Bs_cv11p_"+WEIGHT_CAT+".root")
       Bs_cv11n.SaveAs("Bs_cv11n_"+WEIGHT_CAT+".root")
       

  else:
      print "no angular fit"
  
  if(SFIT==0 ):
   a_cv11p, a_cphif11p = plot_mass("2011p")
   a_cv11n, a_cphif11n = plot_mass("2011n")
   a_cv11p.SaveAs("a_cv11p.root")
   a_cv11n.SaveAs("a_cv11n.root")
   
  
  elif(SFIT==1):
      
   a_cv11, a_cphif11 = plot_mass("2011")
   a_cv11.SaveAs("a_cv11_"+WEIGHT_CAT+".root")

else:
    print "2011 data not used "


#--------------------------------------------------------


#-------------------------------------------------


#-------------------------------------------------
if (YEAR==2012 or YEAR==1211):  
  
  if(SFIT==0 or SFIT==2):

   if(WEIGHT_CAT=="Bd" or WEIGHT_CAT=="none"):
       
       Bd_cv12p, Bd_psif12p, Bd_thf12p, Bd_phif12p = plotAngle("2012p","Bd_range",70)
       Bd_cv12n, Bd_psif12n, Bd_thf12n, Bd_phif12n = plotAngle("2012n","Bd_range",70)
       Bd_cv12p.SaveAs("Bd_cv12p_"+WEIGHT_CAT+".root")
       Bd_cv12n.SaveAs("Bd_cv12n_"+WEIGHT_CAT+".root")
   
  
   if(WEIGHT_CAT=="Bs" or WEIGHT_CAT=="none"):

       Bs_cv12p, Bs_psif12p, Bs_thf12p, Bs_phif12p = plotAngle("2012p","Bs_range",30)
       Bs_cv12n, Bs_psif12n, Bs_thf12n, Bs_phif12n = plotAngle("2012n","Bs_range",30)
       Bs_cv12p.SaveAs("Bs_cv12p_"+WEIGHT_CAT+".root")
       Bs_cv12n.SaveAs("Bs_cv12n_"+WEIGHT_CAT+".root")
       

  else:
      print "no angular fit"

  if(SFIT==0):
   a_cv12p, a_cphif12p = plot_mass("2012p")
   a_cv12n, a_cphif12n = plot_mass("2012n")
   a_cv12p.SaveAs("a_cv12p.root")
   a_cv12n.SaveAs("a_cv12n.root")
   
  
  elif(SFIT==1):
   
   a_cv12, a_cphif12 = plot_mass("2012")
   a_cv12.SaveAs("a_cv12"+WEIGHT_CAT+"sW.root")

else:
    print "2012 data not used "







