from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Asym import *
from OurSites import NTUPLE_PATH
print "Class for fitting polarization: AngularPDF"

timeZero = time.time()


ACC_FREE = 0
FIX_Bd = ACC_FREE
SAME_ACC = 1
#SFIT== 0
YEAR = 1211 # choose 2011, 2012 or 1211->2011+2012 data  
WEIGHT_CAT = "Bd" # type of weights: Bs, Bd or none for the cFit
ACC_TYPE = 2
# Tuples for classic fit (without any weight)
# version BDTG, KstarWide stripping Line, from Diego
print "\n IMPORTANT MESSAGE "
print "\n ####################################################################"
print "\n You choose: SFIT= ",SFIT,", YEAR= ",YEAR,", WEIGHT_CAT= ",WEIGHT_CAT
print "\n ####################################################################"

## Why do we need this ?
Mass.setRange("ref",Mass.getMin(),Mass.getMax())
CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())
###
Mass.setRange("Bs_range",5366.77-25,5366.77+25) 
Mass.setRange("Bd_range",5279.5-25,5279.5+25)

t11p,f11p = getTuple(NTUPLE_PATH + "/2011p", thing = "DecayTree")
t11n,f11n = getTuple(NTUPLE_PATH + "/2011n", thing = "DecayTree")
t12p,f12p = getTuple(NTUPLE_PATH + "/2012p", thing = "DecayTree")
t12n,f12n = getTuple(NTUPLE_PATH + "/2012n", thing = "DecayTree")
#BREAK
samplename = "sample"
cat =  RooCategory(samplename, samplename)
cat.defineType("2011p"), cat.defineType("2011n"), cat.defineType("2012p"), cat.defineType("2012n")

AngBd_2011p,  AngBd_2011n = InitSignalPdfs("Bd","2011", acc_type = ACC_TYPE)
AngBd_2011p.OwnPhys(equalAsym = 1)
AngBd_2011p.OwnAcc()
fix_param= kTRUE
if (WEIGHT_CAT=="Bs" or WEIGHT_CAT=="none"):
    fix_param=kTRUE
    AngBd_2011p.modParam("dpe",3.07-pi,0.75*pi,fix_param)
else:
    fix_param= kFALSE
    AngBd_2011p.modParam("dpe",2.94,0.75*pi,fix_param)
        
AngBd_2011p.modParam("fL",0.5488,0.5*pi,fix_param)
AngBd_2011p.modParam("fpa",0.2392,0.5*pi,fix_param)
####AngBd_2011p.modParam("As2",0.047,0.01,kTRUE)
AngBd_2011p.modParam("dpa",-2.98,0.5*pi,fix_param)
AngBd_2011p.modParam("ds",2.20,0.1,kTRUE)
if ACC_TYPE == 1: AngBd_2011p.modParam("c1_psi",-0.592,0.1)

AngBd_2011n.CopyFreeParams(AngBd_2011p)
AngBd_2011n.CopyAcc(AngBd_2011p) ## Assume same acceptance for "+" and "-"
#AngBd_2011n.modParam("c1_psi",-0.592,0.1)
    
# Angular PDF for Bs
AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011", acc_type = ACC_TYPE)

AngBs_2011p.OwnPhys()
AngBs_2011p.modParam("dpe",0,pi)
AngBs_2011p.modParam("dpa",-pi,pi*.5)
AngBs_2011n.CopyFreeParams(AngBs_2011p)

# Now copy 2011 into 2012, dor Bd, Bs, n and p    
AngBd_2012p,  AngBd_2012n = InitSignalPdfs("Bd","2012", acc_type = ACC_TYPE)
AngBd_2012p.CopyPhys(AngBd_2011p)
AngBd_2012p.CopyAcc(AngBd_2011p)
AngBd_2012n.CopyPhys(AngBd_2011n)
AngBd_2012n.CopyAcc(AngBd_2011p)

AngBs_2012p,  AngBs_2012n = InitSignalPdfs("Bs","2012", acc_type = ACC_TYPE)
AngBs_2012p.CopyPhys(AngBs_2011p)
AngBs_2012n.CopyPhys(AngBs_2011n)

if SAME_ACC:
    AngBs_2011p.CopyAcc(AngBd_2011p)
    AngBs_2012p.CopyAcc(AngBd_2012p)
    AngBs_2011n.CopyAcc(AngBd_2011n)
    AngBs_2012n.CopyAcc(AngBd_2012n)
if ACC_TYPE == 1:    
    AngBd_2012p.modParam("c1_psi",-0.592,0.1)
    AngBd_2012p.modParam("c2_psi",-0.613,0.1)
    AngBd_2012n.modParam("c1_psi",-0.592,0.1)
    AngBd_2012n.modParam("c2_psi",-0.613,0.1)
    
AngBd_2011p.make(), AngBs_2011p.make(), AngBd_2012p.make(), AngBs_2012p.make()
AngBd_2011n.make(), AngBs_2011n.make(), AngBd_2012n.make(), AngBs_2012n.make()


#######################################ext.
## Normaliations to Make extended PDF
    
nd_2011 = RooRealVar("nBd_2011_phys","nBd_2011_phys", 0.2*(t11p.GetEntries() + t11n.GetEntries()),2*(t11p.GetEntries() + t11n.GetEntries()))
ns_2011 = RooFormulaVar("nBs_2011_phys","nBs_2011_phys", "fBs*nBd_2011_phys",RooArgList(fBs,nd_2011))

nd_2011p_phys = RooFormulaVar("nBd_2011p_phys", "nBd_2011p_phys", "nBd_2011_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2011,AngBd_2011p.psACP))
nd_2011n_phys = RooFormulaVar("nBd_2011n_phys", "nBd_2011n_phys", "nBd_2011_phys - nBd_2011p_phys",RooArgList(nd_2011,nd_2011p_phys))

ns_2011p_phys = RooFormulaVar("nBs_2011p_phys", "nBs_2011p_phys", "nBs_2011_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2011,AngBs_2011p.psACP))
ns_2011n_phys = RooFormulaVar("nBs_2011n_phys", "nBs_2011n_phys", "nBs_2011_phys - nBs_2011p_phys",RooArgList(ns_2011,ns_2011p_phys))

ns_2011p = RooFormulaVar("nBs_2011p","nBs_2011p", "nBs_2011p_phys*(1 + A_D - A_prod_s)",RooArgList(ns_2011p_phys, A_D, Aprod_s)) #wk 
ns_2011n = RooFormulaVar("nBs_2011n","nBs_2011n", "nBs_2011n_phys*(1 - A_D + A_prod_s)",RooArgList(ns_2011n_phys, A_D, Aprod_s))  

nd_2011p = RooFormulaVar("nBd_2011p","nBd_2011p", "nBd_2011p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2011p_phys, A_D, Aprod_d))
nd_2011n = RooFormulaVar("nBd_2011n","nBd_2011n", "nBd_2011n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2011n_phys, A_D, Aprod_d))

nd_2012 = RooRealVar("nBd_2012_phys","nBd_2012_phys", 0.2*(t12p.GetEntries() + t12n.GetEntries()),2*(t12p.GetEntries() + t12n.GetEntries()))
ns_2012 = RooFormulaVar("nBs_2012_phys","nBs_2012_phys", "fBs*nBd_2012_phys",RooArgList(fBs,nd_2012))

nd_2012p_phys = RooFormulaVar("nBd_2012p_phys", "nBd_2012p_phys", "nBd_2012_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2012,AngBd_2011p.psACP))
nd_2012n_phys = RooFormulaVar("nBd_2012n_phys", "nBd_2012n_phys", "nBd_2012_phys - nBd_2012p_phys",RooArgList(nd_2012,nd_2012p_phys))

ns_2012p_phys = RooFormulaVar("nBs_2012p_phys", "nBs_2012p_phys", "nBs_2012_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2012,AngBs_2011p.psACP))
ns_2012n_phys = RooFormulaVar("nBs_2012n_phys", "nBs_2012n_phys", "nBs_2012_phys - nBs_2012p_phys",RooArgList(ns_2012,ns_2012p_phys))

ns_2012p = RooFormulaVar("nBs_2012p","nBs_2012p", "nBs_2012p_phys*(1 + A_D - A_prod_s)",RooArgList(ns_2012p_phys, A_D, Aprod_s))
ns_2012n = RooFormulaVar("nBs_2012n","nBs_2012n", "nBs_2012n_phys*(1 - A_D + A_prod_s)",RooArgList(ns_2012n_phys, A_D, Aprod_s))

nd_2012p = RooFormulaVar("nBd_2012p","nBd_2012p", "nBd_2012p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2012p_phys, A_D, Aprod_d))
nd_2012n = RooFormulaVar("nBd_2012n","nBd_2012n", "nBd_2012n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2012n_phys, A_D, Aprod_d))

#################################################################################################
# cFit
#################################################################################################
if SFIT==0:  ### Include mass pdf
    nbkg_2011p = RooRealVar("n nbkg 11p","n bkg 11p", 0.,t11p.GetEntries())
    nbkg_2011n = RooRealVar("n nbkg 11n","n bkg 11n", 0.,t11n.GetEntries())
     
    nbkg_2012p = RooRealVar("n nbkg 12p","n bkg 12p", 0.,t12p.GetEntries())
    nbkg_2012n = RooRealVar("n nbkg 12n","n bkg 12n", 0.,t12n.GetEntries())

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
   
 
    bkgmodel_2011 = FullBackground("Bkg_2011")
    bkgmodel_2012 = FullBackground("Bkg_2012")
    if ACC_TYPE !=2:
        bkgmodel_2011.thetaFromAcc(AngBd_2011p)
        bkgmodel_2012.thetaFromAcc(AngBd_2012p)
    else:
        bkgmodel_2011.OwnTheta()
        bkgmodel_2012.OwnTheta()
        
    bkgmodel_2011.make(), bkgmodel_2012.make()
    
    model11p = RooAddPdf("model11p","model11p",RooArgList(SigBs_2011p,SigBd_2011p,bkgmodel_2011.model),RooArgList(ns_2011p,nd_2011p,nbkg_2011p))
    model12p = RooAddPdf("model12p","model12p",RooArgList(SigBs_2012p,SigBd_2012p,bkgmodel_2012.model),RooArgList(ns_2012p,nd_2012p,nbkg_2012p))
     
    model11n = RooAddPdf("model11n","model11n",RooArgList(SigBs_2011n,SigBd_2011n,bkgmodel_2011.model),RooArgList(ns_2011n,nd_2011n,nbkg_2011n))
    model12n = RooAddPdf("model12n","model12n",RooArgList(SigBs_2012n,SigBd_2012n,bkgmodel_2012.model),RooArgList(ns_2012n,nd_2012n,nbkg_2012n))

    ## Datasets (do we really need to define them here?
    
    dataset11p = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi, Mass))
    dataset12p = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi, Mass))
    dataset11n = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi, Mass))
    dataset12n = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi, Mass))

    print " ####################################### in SFIT=0 (i.e. cFit)  ", 
    allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi, Mass), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2012p",dataset12p), RooFit.Import("2011n",dataset11n),RooFit.Import("2012n",dataset12n) )    
        
    
# ) end of if CFIT
#############################################""ext.
elif SFIT == 2:

    if WEIGHT_CAT=="Bs":
        model11p = AngBs_2011p.model
        model12p = AngBs_2012p.model
     
        model11p_ext = RooExtendPdf("model11p_ext","model11p_ext",AngBs_2011p.model,ns_2011p)
        model12p_ext = RooExtendPdf("model12p_ext","model12p_ext",AngBs_2012p.model,ns_2012p)
     
        dataset11p = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs))
        dataset12p = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs))
    
        model11n = AngBs_2011n.model
        model12n = AngBs_2012n.model
     
        model11n_ext = RooExtendPdf("model11n_ext","model11n_ext",AngBs_2011n.model,ns_2011n)
        model12n_ext = RooExtendPdf("model12n_ext","model12n_ext",AngBs_2012n.model,ns_2012n)
     
        dataset11n = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs))
        dataset12n = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs))
    

        if(YEAR==2011):
            allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("cor_sWeights_Bs"))
        elif(YEAR==2012):
            allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs), RooFit.Index(cat), RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("cor_sWeights_Bs"))
        else:
            allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("cor_sWeights_Bs")) 
    
    elif WEIGHT_CAT=="Bd":
     
        model11p = AngBd_2011p.model
        model12p = AngBd_2012p.model
     
        model11p_ext = RooExtendPdf("model11p_ext","model11p_ext",AngBd_2011p.model,nd_2011p)
        model12p_ext = RooExtendPdf("model12p_ext","model12p_ext",AngBd_2012p.model,nd_2012p)

       
        model11n = AngBd_2011n.model
        model12n = AngBd_2012n.model
     
        model11n_ext = RooExtendPdf("model11n_ext","model11n_ext",AngBd_2011n.model,nd_2011n)
        model12n_ext = RooExtendPdf("model12n_ext","model12n_ext",AngBd_2012n.model,nd_2012n)
        
        dataset11p = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd))
        dataset12p = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd))
        dataset11n = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd))
        dataset12n = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd))
     

        if(YEAR==2011):
            allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("cor_sWeights_Bd"))
        elif(YEAR==2012):
            allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd), RooFit.Index(cat), RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("cor_sWeights_Bd"))
        else:
            allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bd), RooFit.Index(cat), RooFit.Import("2011p",dataset11p),RooFit.Import("2011n",dataset11n),RooFit.Import("2012p",dataset12p),RooFit.Import("2012n",dataset12n),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar("cor_sWeights_Bd")) 

     

    print " ####################################### in SFIT=2   ", 
    print " "
        
        
dataset11n.Print()
dataset11p.Print()
dataset12n.Print()
dataset12p.Print()
allData.Print()    


##############################################ext


if not SFIT:
    model11p.fixCoefRange("ref")
    model12p.fixCoefRange("ref")
    model11n.fixCoefRange("ref")
    model12n.fixCoefRange("ref")
    
fiter = RooSimultaneous("fitter", "fitter", cat)

if (SFIT==2):
    if (YEAR == 2011 or YEAR==1211): 
        fiter.addPdf(model11p_ext,"2011p")
        fiter.addPdf(model11n_ext,"2011n")
    if (YEAR == 2012 or YEAR==1211):
            fiter.addPdf(model12p_ext,"2012p")
            fiter.addPdf(model12n_ext,"2012n")
    else: 
        print "check your ntuples3"
        
if (SFIT==0):
    if (YEAR == 2011 or YEAR==1211): 
        fiter.addPdf(model11p,"2011p")
        fiter.addPdf(model11n,"2011n")
    if (YEAR == 2012 or YEAR==1211):
        fiter.addPdf(model12p,"2012p")
        fiter.addPdf(model12n,"2012n")
    else: 
        print "check your ntuples3"

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
    if ACC_TYPE == 1: fixAcc()  # you can leave acc param free by not calling the function "fixAcc()".
    if noCP:fixCP() 
    # AngBd_2011p.ACPL.setVal(-0.002) #check
    # AngBd_2011p.ACPL.setConstant(1) #check
    # AngBs_2011p.ds.setVal(1.1) #check
    # AngBs_2011p.ds.setConstant(1) #
    
    if offset: 
        fitres = fiter.fitTo(allData,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8),RooFit.Offset(kTRUE),RooFit.SumW2Error(kTRUE))
    else: 
        fitres = fiter.fitTo(allData,RooFit.Minos(minos),RooFit.Save(), RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE))
    return fitres
        


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
            dataset = RooDataSet("data11p","data11p",t11p,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs),"","cor_sWeights_"+WEIGHT_CAT)
    if "11n" in name:
        model = model11n
        if (SFIT==0): 
            dataset = dataset11n
        else:
            dataset = RooDataSet("data11n","data11n",t11n,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs),"","cor_sWeights_"+WEIGHT_CAT)
    if "12p" in name:
        model = model12p
        if (SFIT==0):
            dataset = dataset12p
        else:
            dataset = RooDataSet("data12p","data12p",t12p,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs),"","cor_sWeights_"+WEIGHT_CAT)
    if "12n" in name:
        model = model12n
        if (SFIT==0):
            dataset = dataset12n
        else:
            dataset = RooDataSet("data12n","data12n",t12n,RooArgSet(CPsi,CTheta,Phi,cor_sWeights_Bs),"","cor_sWeights_"+WEIGHT_CAT)
    
        
    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename))
    if (WEIGHT_CAT=="none"):
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
    if (WEIGHT_CAT=="none"):
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    elif (WEIGHT_CAT=="Bs"):
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    elif (WEIGHT_CAT=="Bd"):
        model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cthf.SetTitle("")
    cthf.SetXTitle("cos(\Theta)")
    cthf.Draw()

    cv3.cd(3)
    cphif = Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename))
    if (WEIGHT_CAT=="none"):
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("modelBkg_" + name[:-1]),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf " + name),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf " + name),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    elif (WEIGHT_CAT=="Bs"):
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    elif (WEIGHT_CAT=="Bd"):
        model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cphif.SetTitle("")
    cphif.SetXTitle("cos(\phi)")
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

    cphif.SetTitle("")
    cphif.SetXTitle("M_{J/\Psi K\pi} (MeV/c^{2})")
    cphif.Draw()

    return cv3, cphif#,cthf, cpsif


fitres = fitAll(minos = 1, offset = 1)
ff = TFile("FitResults.root","recreate")
fitres.Write("FitResults")
ff.Close()


#-------------------------------------------------
if (YEAR==2011 or YEAR==1211):  
    if (WEIGHT_CAT=="Bd" or WEIGHT_CAT=="none"):
        Bd_cv11p, Bd_psif11p, Bd_thf11p, Bd_phif11p = plotAngle("2011p","Bd_range",70)
        Bd_cv11n, Bd_psif11n, Bd_thf11n, Bd_phif11n = plotAngle("2011n","Bd_range",70)
        Bd_cv11p.SaveAs("Bd_cv11p_"+WEIGHT_CAT+".root")
        Bd_cv11n.SaveAs("Bd_cv11n_"+WEIGHT_CAT+".root")
       
    if(WEIGHT_CAT=="Bs" or WEIGHT_CAT=="none"):
        Bs_cv11p, Bs_psif11p, Bs_thf11p, Bs_phif11p = plotAngle("2011p","Bs_range",30)
        Bs_cv11n, Bs_psif11n, Bs_thf11n, Bs_phif11n = plotAngle("2011n","Bs_range",30)
        Bs_cv11p.SaveAs("Bs_cv11p_"+WEIGHT_CAT+".root")
        Bs_cv11n.SaveAs("Bs_cv11n_"+WEIGHT_CAT+".root")
        

    else:
        print "no angular fit"
  
    if(SFIT==0 ):
        a_cv11p, a_cphif11p = plot_mass("2011p")
        a_cv11n, a_cphif11n = plot_mass("2011n")
        a_cv11p.SaveAs("a_cv11p.root")
        a_cv11n.SaveAs("a_cv11n.root")
else:
    print "2011 data not used "
   
#--------------------------------------------------------


#-------------------------------------------------


#-------------------------------------------------
if (YEAR==2012 or YEAR==1211):  

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
else:
    print "2012 data not used "







