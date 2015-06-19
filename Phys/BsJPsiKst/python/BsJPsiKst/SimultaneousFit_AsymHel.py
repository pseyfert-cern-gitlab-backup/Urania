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
NTUPLE_PATH = "~/w7folder/NTuples/Bs_Jpsi_Kst_2013/"
from parameters import KpiBins4 as KpiBins, myCsp4 as myCsp, translateWeights
#from parameters import KpiBins4 as KpiBins, myCsp23 as myCsp, myCsd23 as myCsd, myCpd23 as myCpd, translateWeightsSPD
print "Class for fitting polarization: AngularPDF"
timeZero = time.time()

ACC_FREE = 0
FIX_Bd = ACC_FREE
SAME_ACC = 1
YEAR = 2012# choose 2011, 2012 or 1211->2011+2012 data  
WEIGHT_CAT = "Bs" # type of weights: Bs, Bd or none for the cFit
ACC_TYPE = 2 # 1 for factorized acceptance, 2 for Normalization Weights
fix_param= kFALSE

print "\n IMPORTANT MESSAGE "
print "\n ####################################################################"
print "\n You choose: SFIT= ",SFIT,", YEAR= ",YEAR,", WEIGHT_CAT= ",WEIGHT_CAT
print "\n ####################################################################"


if WEIGHT_CAT == "Bd":
     myweight = cor_sWeights_Bd
     myAs2={0: 0.138,1: 0.027,2: 0.016,3: 0.082} ### Walaa's init values
     myds={0: 3.6,1: 3.3,2: 2.00,3: 1.39}
        
if WEIGHT_CAT == "Bs":
     myweight = cor_sWeights_Bs
     myAs2={0: 0.151,1: 0.054,2: 0.051,3: 0.171} ### Walaa's init values
     myds={0: 2.,1:-0.71 ,2: 1.56,3: 1.63}
          
## Why do we need this ?
Mass.setRange("ref",Mass.getMin(),Mass.getMax())
CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())
###
Mass.setRange("Bs_range",5366.77-25,5366.77+25) 
Mass.setRange("Bd_range",5279.5-25,5279.5+25)

myfiles = {}
mytrees = {}
samplename = "sample"
masterCat =  RooCategory(samplename, samplename)
binCat = RooCategory("binCat","binCat")
for i in range(len(KpiBins)-1): binCat.defineType(str(KpiBins[i]) + "_" + str(KpiBins[i+1]))
#NTUPLE_PATH = "~/NTuplesFast/Carlos_NS_sw/"
#NTUPLE_PATH = "/home/galaceos/cmtuser/URANIA/URANIA_HEAD/Phys/BsJPsiKst/ntuples/"
SampleSizes = {}
for s in ["11p","11n","12p","12n"]:
     masterCat.defineType(s)
     SampleSizes[s] = 0
     for i in range(len(KpiBins)-1):
          name  = s + "_" + str(KpiBins[i]) + "_" + str(KpiBins[i+1])
          mytrees[name], myfiles[name] = getTuple(NTUPLE_PATH + "/20" + name, thing = "DecayTree")
          SampleSizes[s] +=  mytrees[name].GetEntries()
          
AngBd_2011p,  AngBd_2011n = InitSignalPdfs("Bd","2011", acc_type = ACC_TYPE)
AngBd_2011p.OwnPhys(equalAsym = 1)
AngBd_2011p.modParam("CSP",1.,.1,kTRUE)

AngBd_2011p.OwnAcc()

### DMS: I do not understand why we need the following two lines: 
    
AngBd_2011p.modParam("fL",0.572,0.5,fix_param)
AngBd_2011p.modParam("fpa",0.227,0.4,fix_param)
AngBd_2011p.modParam("As2",0.05,0.05,kFALSE)#2012
AngBd_2011p.modParam("dpa",-2.9,1.,kFALSE)#2012
AngBd_2011p.modParam("dpe",2.9,1.,kFALSE)#2012
AngBd_2011p.As2.setMax(0.5)


if ACC_TYPE == 1: AngBd_2011p.modParam("c1_psi",-0.592,0.1)

AngBd_2011n.CopyFreeParams(AngBd_2011p)
AngBd_2011n.CopyAcc(AngBd_2011p) ## Assume same acceptance for "+" and "-"
    
# Angular PDF for Bs
AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011", acc_type = ACC_TYPE)

AngBs_2011p.OwnPhys()
AngBs_2011p.modParam("CSP",1.,.1,kTRUE)

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
AngBs_2011p.As2.setMin(0.005)

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
    
nd_2011 = RooRealVar("nBd_2011_phys","nBd_2011_phys", 0.01*(SampleSizes["11p"] + SampleSizes["11n"]),2*(SampleSizes["11p"] + SampleSizes["11n"]))
#ns_2011 = RooFormulaVar("nBs_2011_phys","nBs_2011_phys", "fBs*nBd_2011_phys",RooArgList(fBs,nd_2011))
ns_2011 = RooRealVar("nBs_2011_phys","nBs_2011_phys",10., SampleSizes["11p"] + SampleSizes["11n"])

nd_2011p_phys = RooFormulaVar("nBd_2011p_phys", "nBd_2011p_phys", "nBd_2011_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2011,AngBd_2011p.psACP))
nd_2011n_phys = RooFormulaVar("nBd_2011n_phys", "nBd_2011n_phys", "nBd_2011_phys - nBd_2011p_phys",RooArgList(nd_2011,nd_2011p_phys))

ns_2011p_phys = RooFormulaVar("nBs_2011p_phys", "nBs_2011p_phys", "nBs_2011_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2011,AngBs_2011p.psACP))
ns_2011n_phys = RooFormulaVar("nBs_2011n_phys", "nBs_2011n_phys", "nBs_2011_phys - nBs_2011p_phys",RooArgList(ns_2011,ns_2011p_phys))

ns_2011p = RooFormulaVar("nBs_2011p","nBs_2011p", "nBs_2011p_phys*(1 + A_D - A_prod_s)",RooArgList(ns_2011p_phys, A_D, Aprod_s)) #wk 
ns_2011n = RooFormulaVar("nBs_2011n","nBs_2011n", "nBs_2011n_phys*(1 - A_D + A_prod_s)",RooArgList(ns_2011n_phys, A_D, Aprod_s))  

nd_2011p = RooFormulaVar("nBd_2011p","nBd_2011p", "nBd_2011p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2011p_phys, A_D, Aprod_d))
nd_2011n = RooFormulaVar("nBd_2011n","nBd_2011n", "nBd_2011n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2011n_phys, A_D, Aprod_d))



nd_2012 = RooRealVar("nBd_2012_phys","nBd_2012_phys", 0.01*(SampleSizes["12p"] + SampleSizes["12n"]),2*(SampleSizes["12p"] + SampleSizes["12n"]))
ns_2012 = RooRealVar("nBs_2012_phys","nBs_2012_phys", 10.,SampleSizes["12p"] + SampleSizes["12n"])



nd_2012p_phys = RooFormulaVar("nBd_2012p_phys", "nBd_2012p_phys", "nBd_2012_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2012,AngBd_2011p.psACP))
nd_2012n_phys = RooFormulaVar("nBd_2012n_phys", "nBd_2012n_phys", "nBd_2012_phys - nBd_2012p_phys",RooArgList(nd_2012,nd_2012p_phys))

ns_2012p_phys = RooFormulaVar("nBs_2012p_phys", "nBs_2012p_phys", "nBs_2012_phys*0.5/" + AngBs_2011p.psACP.GetName(), RooArgList(ns_2012,AngBs_2011p.psACP))
ns_2012n_phys = RooFormulaVar("nBs_2012n_phys", "nBs_2012n_phys", "nBs_2012_phys - nBs_2012p_phys",RooArgList(ns_2012,ns_2012p_phys))

ns_2012p = RooFormulaVar("nBs_2012p","nBs_2012p", "nBs_2012p_phys*(1 + A_D - A_prod_s)",RooArgList(ns_2012p_phys, A_D, Aprod_s))
ns_2012n = RooFormulaVar("nBs_2012n","nBs_2012n", "nBs_2012n_phys*(1 - A_D + A_prod_s)",RooArgList(ns_2012n_phys, A_D, Aprod_s))

nd_2012p = RooFormulaVar("nBd_2012p","nBd_2012p", "nBd_2012p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2012p_phys, A_D, Aprod_d))
nd_2012n = RooFormulaVar("nBd_2012n","nBd_2012n", "nBd_2012n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2012n_phys, A_D, Aprod_d))


mydatasets = {}
mergeddatasets = {}
masterCatImports = []
     
for s in ["11p","11n","12p","12n"]:
     myImports = []
     for i in range(len(KpiBins)-1):
          binname = str(KpiBins[i]) + "_" + str(KpiBins[i+1])
          name  = s + "_" + binname
          mydatasets[name] = RooDataSet("data" + name,"data" + name, mytrees[name],RooArgSet(CPsi,CTheta,Phi,myweight))
          myImports.append(RooFit.Import(binname, mydatasets[name]))
     mergeddatasets[s] = RooDataSet(s,s,RooArgSet(CPsi,CTheta,Phi,myweight),RooFit.Index(binCat),*myImports)
     masterCatImports.append(RooFit.Import(s, mergeddatasets[s]))

allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports)
dataset11 = RooDataSet("dataset11","dataset11", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports[:2])
dataset12 = RooDataSet("dataset12","dataset12", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports[2:])


if WEIGHT_CAT=="Bs":

     model11p = AngBs_2011p
     model12p = AngBs_2012p
     
     model11p_ext = RooExtendPdf("model11p_ext","model11p_ext",AngBs_2011p.model,ns_2011p)
     model12p_ext = RooExtendPdf("model12p_ext","model12p_ext",AngBs_2012p.model,ns_2012p)
     
     model11n = AngBs_2011n
     model12n = AngBs_2012n
     
     model11n_ext = RooExtendPdf("model11n_ext","model11n_ext",AngBs_2011n.model,ns_2011n)
     model12n_ext = RooExtendPdf("model12n_ext","model12n_ext",AngBs_2012n.model,ns_2012n)
          
elif WEIGHT_CAT=="Bd":
     
     model11p = AngBd_2011p
     model12p = AngBd_2012p
          
     model11p_ext = RooExtendPdf("model11p_ext","model11p_ext",AngBd_2011p.model,nd_2011p)
     model12p_ext = RooExtendPdf("model12p_ext","model12p_ext",AngBd_2012p.model,nd_2012p)
          
     model11n = AngBd_2011n
     model12n = AngBd_2012n
          
     model11n_ext = RooExtendPdf("model11n_ext","model11n_ext",AngBd_2011n.model,nd_2011n)
     model12n_ext = RooExtendPdf("model12n_ext","model12n_ext",AngBd_2012n.model,nd_2012n)
        

allData.Print()    


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
   
    
def runFit(minos=0, offset = 0, noCP = 1, numCPU = 1, dataset = "all"):
     if noCP:
          #AngBs_2011p.ACPS_.setVal(0.)
          AngBs_2011p.ACPL_.setVal(0.)
          AngBs_2011p.ACPpa_.setVal(0)
          AngBs_2011p.ACPpe_.setVal(0)
          #AngBs_2011p.ACP2L_.setVal(0.)
          #AngBs_2011p.ACP2pa_.setVal(0)
          #AngBs_2011p.ACP2pe_.setVal(0)

     #AngBs_2011p.ACPS_.setConstant(noCP)    
     AngBs_2011p.ACPL_.setConstant(noCP)
     AngBs_2011p.ACPpa_.setConstant(noCP)
     AngBs_2011p.ACPpe_.setConstant(noCP)
     #AngBs_2011p.ACP2L_.setConstant(noCP)
     #AngBs_2011p.ACP2pa_.setConstant(noCP)
     #AngBs_2011p.ACP2pe_.setConstant(noCP)

     w = RooWorkspace("w")
     wimport = getattr(w,'import')
     SimPdfTool = RooSimWSTool(w)
     mbc= RooSimWSTool.MultiBuildConfig(samplename)
     split_string = "As2"+WEIGHT_CAT+",ds"+WEIGHT_CAT+",CSP"+WEIGHT_CAT
     
     if dataset in ["11","all"]:
          wimport(model11p_ext,RooFit.RecycleConflictNodes())
          wimport(model11n_ext,RooFit.RecycleConflictNodes())

          mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + ",n"+WEIGHT_CAT+"_2011_phys" + model11p.GetNormWeightString(),"binCat"))
          mbc.addPdf("11n",model11n_ext.GetName(),RooFit.SplitParam(split_string + ",n"+WEIGHT_CAT+"_2011_phys" + model11n.GetNormWeightString(),"binCat"))
  
     if dataset in ["12", "all"]:
          wimport(model12p_ext,RooFit.RecycleConflictNodes())
          wimport(model12n_ext,RooFit.RecycleConflictNodes())

          mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + ",n"+WEIGHT_CAT+"_2012_phys" + model12p.GetNormWeightString(),"binCat")) 
          mbc.addPdf("12n",model12n_ext.GetName(),RooFit.SplitParam(split_string + ",n"+WEIGHT_CAT+"_2012_phys" + model12n.GetNormWeightString(),"binCat")) 
    
     wimport(RooArgSet(masterCat, binCat))
    
     w.Print()

     Master = SimPdfTool.build("Master",mbc) 

     Master.Print()
     Master.indexCat().Print()
     Master.indexCat().Print("v")
    
     w.Print()
         
     argList = Master.getParameters(allData)
     argList.Print()
     for i in range(len(KpiBins)-1): 
          argList.setRealValue("CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myCsp[i])
          argList.setRealValue("As2"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myAs2[i])      
          argList.setRealValue("ds"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myds[i])
          for thing in model11p.Tristan_weights: argList.setRealValue(thing.GetName(), NormWeights["2011p_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          for thing in model11n.Tristan_weights: argList.setRealValue(thing.GetName(), NormWeights["2011n_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          for thing in model12p.Tristan_weights: argList.setRealValue(thing.GetName(), NormWeights["2012p_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          for thing in model12n.Tristan_weights: argList.setRealValue(thing.GetName(), NormWeights["2012n_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          
          
     
     argList2 = Master.getParameters(allData)

     # Csp factors
     for i in range(len(KpiBins)-1):  print "CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList2.getRealValue("CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])) 
     
     if dataset == "11": fitres_bins = Master.fitTo(dataset11,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "12": fitres_bins = Master.fitTo(dataset12,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "all": fitres_bins = Master.fitTo(allData,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     

     return fitres_bins, Master, w, mbc


#runFit(numCPU = 1, noCP = 0)

#if YEAR == 1112 or YEAR == 1211: my_res = runFit(noCP = 0, numCPU = 3)
#if YEAR == 2011: my_res = runFit(noCP = 0, numCPU = 3, dataset = "11")
#if YEAR == 2012: my_res = runFit(noCP = 0, numCPU = 3, dataset = "12")
if YEAR == 1112 or YEAR == 1211: my_res = runFit(noCP = 0, numCPU = 8)
if YEAR == 2011: my_res = runFit(noCP = 0, numCPU = 8, dataset = "11")
if YEAR == 2012: my_res = runFit(noCP = 0, numCPU = 3, dataset = "12")

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
                  


##### Result July dms:
##     EXT PARAMETER                                INTERNAL      INTERNAL  
##  NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
##   1  ACPLBd       1.16138e-01   3.16352e-03   1.46731e-04   2.34418e-01
##   2  As2Bd_826_861   1.34603e-01   4.77079e-03   4.76144e-04  -4.79784e-01
##   3  As2Bd_861_896   4.13329e-02   1.97069e-03   2.32529e-04  -9.87530e-01
##   4  As2Bd_896_931   3.79117e-02   2.93479e-03   4.58376e-04  -1.01287e+00
##   5  As2Bd_931_966   1.07901e-01   6.92620e-03   6.57179e-04  -2.53704e+00
##   6  dpaBd        2.95679e+00   1.19593e-02   3.68637e-05   4.89956e-01
##   7  dpeBd        2.22032e-01   9.50307e-03   2.41995e-05   3.53448e-02
##   8  dsBd_826_861   3.13531e+00   4.55310e-02   1.79807e-02   5.22445e-01
##   9  dsBd_861_896   3.60329e+00   3.55924e-02   1.09897e-04   6.10750e-01
##  10  dsBd_896_931   4.47388e+00   1.73581e-02   4.08483e-04   7.92400e-01
##  11  dsBd_931_966  -1.32317e+00   1.83027e-02   2.94452e-04  -2.12178e-01
##  12  fLBd         5.55628e-01   1.72114e-03   6.66861e-05  -3.27495e-02
##  13  fpaBd        2.12157e-01   1.99649e-03   5.09596e-04  -3.71164e-02
##  14  nBd_2011_phys_826_861   7.54311e+03   8.68040e+01   6.46375e-05  -7.41538e+00
##  15  nBd_2011_phys_861_896   2.79860e+04   1.67198e+02   6.74993e-05  -2.47083e+00
##  16  nBd_2011_phys_896_931   2.52792e+04   1.58908e+02   6.68229e-05  -2.42190e+00
##  17  nBd_2011_phys_931_966   8.04781e+03   8.96608e+01   6.45413e-05  -8.30880e+00
##  18  nBd_2012_phys_826_861   1.64538e+04   1.28202e+02   4.35837e-05  -7.41755e+00
##  19  nBd_2012_phys_861_896   6.15679e+04   2.47993e+02   4.55003e-05  -2.47068e+00
##  20  nBd_2012_phys_896_931   5.55375e+04   2.35535e+02   4.50401e-05  -2.42112e+00
##  21  nBd_2012_phys_931_966   1.77282e+04   1.33074e+02   4.35085e-05  -8.30906e+00
##                               ERR DEF= 0.5


############## SECOND MINIMUM

##  EXT PARAMETER                                INTERNAL      INTERNAL  
##  NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
##   1  ACPLBd       1.19956e-01   3.81305e-03   1.67873e-04   2.42275e-01
##   2  As2Bd_826_861   1.38758e-01   5.79483e-03   5.51984e-04  -4.61138e-01
##   3  As2Bd_861_896   4.07266e-02   2.36937e-03   2.65288e-04  -9.91949e-01
##   4  As2Bd_896_931   3.75888e-02   3.51051e-03   2.59138e-03  -1.01531e+00
##   5  As2Bd_931_966   1.19137e-01   8.46046e-03   7.40246e-04  -5.50900e-01
##   6  dpaBd       -2.95266e+00   1.45009e-02   1.17870e-03  -5.26888e-02
##   7  dpeBd        2.91731e+00   1.14661e-02   1.74174e-04   1.73092e-02
##   8  dsBd_826_861   3.13179e+00   5.40420e-02   2.06642e-02   5.21798e-01
##   9  dsBd_861_896   2.68016e+00   4.36634e-02   1.14581e-04   4.40687e-01
##  10  dsBd_896_931   1.81710e+00   2.11091e-02   6.86275e-05   2.93392e-01
##  11  dsBd_931_966   1.32097e+00   2.08220e-02   3.19600e-04   2.11819e-01
##  12  fLBd         5.58059e-01   2.07291e-03   7.61607e-05  -2.78856e-02
##  13  fpaBd        2.10602e-01   2.39927e-03   5.80476e-04  -4.10060e-02
##  14  nBd_2012_phys_826_861   1.64537e+04   1.28202e+02   4.12654e-05  -7.41755e+00
##  15  nBd_2012_phys_861_896   6.15689e+04   2.47996e+02   4.30787e-05  -2.47069e+00
##  16  nBd_2012_phys_896_931   5.55378e+04   2.35536e+02   4.26455e-05  -2.42112e+00
##  17  nBd_2012_phys_931_966   1.77283e+04   1.33075e+02   4.11945e-05  -8.30906e+00



##### Bs

##     EXT PARAMETER                                INTERNAL      INTERNAL  
##  NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
##   1  ACPLBs       1.60369e-01   5.22479e-02   4.31519e-04   3.26509e-01
##   2  ACPpaBs     -2.17957e-01   1.74627e-01   1.33111e-03  -1.30174e+01
##   3  ACPpeBs      3.19897e-02   9.65873e-02   6.48474e-04  -3.20562e+00
##   4  As2Bs_826_861   1.85271e-01   1.82462e-01   1.04216e-01  -2.56343e+00
##   5  As2Bs_861_896   4.00495e-02   4.53770e-02   5.79274e-04  -1.14771e+00
##   6  As2Bs_896_931   4.05765e-02   3.50959e-02   8.96504e-02  -1.14449e+00
##   7  As2Bs_931_966   2.57119e-01   9.97798e-02   1.04012e-01  -3.74425e-01
##   8  dpaBs       -2.78457e+00   1.80669e-01   1.07417e-04  -4.59140e-01
##   9  dpeBs       -7.05749e-02   1.15016e-01   6.04013e-05  -1.12326e-02
##  10  dsBs_826_861   6.89297e-01   6.59747e-01   1.74852e-02   1.09926e-01
##  11  dsBs_861_896  -8.17679e-01   5.97024e-01   1.85322e-02  -1.30508e-01
##  12  dsBs_896_931   4.71610e+00   2.00138e-01   2.00649e-04   8.48955e-01
##  13  dsBs_931_966   4.58459e+00   1.35646e-01   1.31297e-02   8.17824e-01
##  14  fLBs         5.45449e-01   2.49678e-02   4.96246e-04   5.64899e-01
##  15  fpaBs        1.47433e-01   2.67500e-02   8.21573e-04  -4.63304e-01
##  16  nBs_2012_phys_826_861   6.25003e+01   7.90715e+00   1.11220e-04  -4.66490e+02
##  17  nBs_2012_phys_861_896   3.43576e+02   1.85388e+01   2.28668e-05  -9.59101e+01
##  18  nBs_2012_phys_896_931   5.06756e+02   2.25147e+01   1.38834e-05  -5.82312e+01
##  19  nBs_2012_phys_931_966   2.04342e+02   1.42966e+01   3.48125e-05  -1.46014e+02
