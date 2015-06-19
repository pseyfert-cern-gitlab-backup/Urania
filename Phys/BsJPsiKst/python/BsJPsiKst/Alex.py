from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Alex import *
from OurSites import NTUPLE_PATH
from parameters import KpiBins4 as KpiBins, AlexCsp as myCsp
#1  ACPLBd      -1.54822e-02   6.94526e-01   1.02768e-01   4.69031e-01
print "Class for fitting polarization: AngularPDF"
#sys.path.append(".")
timeZero = time.time()

ACC_FREE = 0
FIX_Bd = ACC_FREE
SAME_ACC = 1
YEAR = 2011# choose 2011, 2012 or 1211->2011+2012 data  
WEIGHT_CAT = "Bd" # type of weights: Bs, Bd or none for the cFit
ACC_TYPE = 2
fix_param= kFALSE
FLIP = 0## Swaps the positive and negative kaon models
print "\n IMPORTANT MESSAGE "
print "\n ####################################################################"
print "\n You choose: SFIT= ",SFIT,", YEAR= ",YEAR,", WEIGHT_CAT= ",WEIGHT_CAT
print "\n ####################################################################"


#myweight = "Nsig_sw"
myAs2={0: 0.115,1: 0.049,2: 0.052,3: 0.105} ### Walaa's init values
myds={0: 3.09,1: 2.66,2: 1.94,3: 1.53}
          
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
NTUPLE_PATH = "~/NTuplesFast/"
SampleSizes = {}

kaon_cats = ["11p","11n"]#,"11n"]
for s in kaon_cats:
     masterCat.defineType(s)
     SampleSizes[s] = 0
     for i in range(len(KpiBins)-1):
          name  = s + "_" + str(KpiBins[i]) + "_" + str(KpiBins[i+1])
          mytrees[name], myfiles[name] = getTuple(NTUPLE_PATH + "/Alex20" + name, thing = "merged")
          SampleSizes[s] +=  mytrees[name].GetEntries()
          
AngBd_2011p,  AngBd_2011n = InitSignalPdfs("Bd","2011", acc_type = ACC_TYPE)
AngBd_2011p.OwnPhys(equalAsym = 1)
AngBd_2011p.modParam("CSP",1.,.1,kTRUE)
AngBd_2011p.modParam("As2",0.05,.1,kFALSE)
AngBd_2011p.modParam("ds",0.0,2*pi,kFALSE)
#AngBd_2011p.modParam("dpa",3, 1)

AngBd_2011p.modParam("fL",0.572,0.5,fix_param)
AngBd_2011p.modParam("fpa",0.227,0.4,fix_param)

AngBd_2011p.modParam("dpa",-2.94,2*pi)#, kTRUE)#,fix_param)
AngBd_2011p.modParam("dpe",2.94,2*pi)#,fix_param)

AngBd_2011p.OwnAcc()

if ACC_TYPE == 1: AngBd_2011p.modParam("c1_psi",-0.592,0.1)

AngBd_2011n.CopyFreeParams(AngBd_2011p)
AngBd_2011n.CopyAcc(AngBd_2011p) ## Assume same acceptance for "+" and "-"

AngBd_2011p.As2.setVal(0.05)
AngBd_2011p.As2.setMin(0.03)
AngBd_2011p.make()#, AngBs_2011p.make(), AngBd_2012p.make(), AngBs_2012p.make()
AngBd_2011n.make()#, AngBs_2011n.make(), AngBd_2012n.make(), AngBs_2012n.make()


#######################################ext.
## Normaliations to Make extended PDF

#BREAK
nd_2011 = RooRealVar("nBd_2011_phys","nBd_2011_phys", 800.,160000.)
#ns_2011 = RooFormulaVar("nBs_2011_phys","nBs_2011_phys", "fBs*nBd_2011_phys",RooArgList(fBs,nd_2011))

nd_2011p_phys = RooFormulaVar("nBd_2011p_phys", "nBd_2011p_phys", "nBd_2011_phys*0.5/" + AngBd_2011p.psACP.GetName(), RooArgList(nd_2011,AngBd_2011p.psACP))
nd_2011n_phys = RooFormulaVar("nBd_2011n_phys", "nBd_2011n_phys", "nBd_2011_phys - nBd_2011p_phys",RooArgList(nd_2011,nd_2011p_phys))


nd_2011p = RooFormulaVar("nBd_2011p","nBd_2011p", "nBd_2011p_phys*(1 - A_D + A_prod_d)",RooArgList(nd_2011p_phys, A_D, Aprod_d))
nd_2011n = RooFormulaVar("nBd_2011n","nBd_2011n", "nBd_2011n_phys*(1 + A_D - A_prod_d)",RooArgList(nd_2011n_phys, A_D, Aprod_d))


#################################################################################################
# cFit
#################################################################################################
if 1:
     mydatasets = {}
     mergeddatasets = {}
     masterCatImports = []
     fakeCatImports = []
     for s in kaon_cats:
          myImports = []
          for i in range(len(KpiBins)-1):
               binname = str(KpiBins[i]) + "_" + str(KpiBins[i+1])
               name  = s + "_" + binname
               mydatasets[name] = RooDataSet("data" + name,"data" + name, mytrees[name],RooArgSet(CPsi,CTheta,Phi,myweight))
               myImports.append(RooFit.Import(binname, mydatasets[name]))
          mergeddatasets[s] = RooDataSet(s,s,RooArgSet(CPsi,CTheta,Phi,myweight),RooFit.Index(binCat),*myImports)
          masterCatImports.append(RooFit.Import(s, mergeddatasets[s]))
     #flippedImports = [ RooFit.Import("11p",mergeddatasets["11n"]), RooFit.Import("11n",mergeddatasets["11p"])]
     if "11p" in kaon_cats:
          positiveImports = [ RooFit.Import("11p",mergeddatasets["11p"])]
          dataset11p = RooDataSet("dataset11p","dataset11p", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *positiveImports)

     if "11n" in kaon_cats:
          negativeImports = [ RooFit.Import("11n",mergeddatasets["11n"])]
          dataset11n = RooDataSet("dataset11p","dataset11p", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *negativeImports)
          
     dataset11 = RooDataSet("dataset11","dataset11", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports[:2])
      
     
          
     if FLIP == 0:
          model11p = AngBd_2011p.model
          model11n = AngBd_2011n.model
     else:
          model11p = AngBd_2011n.model
          model11n = AngBd_2011p.model  
         
     model11p_ext = RooExtendPdf("model11p_ext","model11p_ext",model11p,nd_2011p)
     model11n_ext = RooExtendPdf("model11n_ext","model11n_ext",model11n,nd_2011n)
dataset11.Print()    


##############################################ext


if not SFIT:
    model11p.fixCoefRange("ref")
   
    model11n.fixCoefRange("ref")
    
   
    
def runFit(minos=0, offset = 0, noCP = 1, numCPU = 1, dataset = dataset11):
     if noCP: AngBd_2011p.ACPL_.setVal(0.)
         
     AngBd_2011p.ACPL_.setConstant(noCP)
     
     w = RooWorkspace("w")
     wimport = getattr(w,'import')
     SimPdfTool = RooSimWSTool(w)
     mbc= RooSimWSTool.MultiBuildConfig(samplename) 

     if "11p" in kaon_cats:
          wimport(model11p_ext,RooFit.RecycleConflictNodes())
          mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam("As2"+WEIGHT_CAT+",ds"+WEIGHT_CAT+",CSP"+WEIGHT_CAT+",n"+WEIGHT_CAT+"_2011_phys","binCat"))

     if "11n" in kaon_cats:
          wimport(model11n_ext,RooFit.RecycleConflictNodes())
          mbc.addPdf("11n",model11n_ext.GetName(),RooFit.SplitParam("As2"+WEIGHT_CAT+",ds"+WEIGHT_CAT+",CSP"+WEIGHT_CAT+",n"+WEIGHT_CAT+"_2011_phys","binCat"))
      
     wimport(RooArgSet(masterCat, binCat))
    
     w.Print()

     Master = SimPdfTool.build("Master",mbc) 
     
     Master.Print()
     Master.indexCat().Print()
     Master.indexCat().Print("v")
    
     w.Print()
     if kaon_cats == ["11p","11n"]: thedata = dataset#,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))  
     elif kaon_cats == ["11p"]: thedata = dataset11p#,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))  
     elif kaon_cats == ["11n"]: thedata = dataset11n#,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))  
    
     argList = Master.getParameters(thedata)
     argList.Print()
     for i in range(len(KpiBins)-1): 
          argList.setRealValue("CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myCsp[i])      
          argList.setRealValue("As2"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myAs2[i])      
          argList.setRealValue("ds"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myds[i])     

     fitres_bins = Master.fitTo(thedata,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))  
     
     return fitres_bins, Master, w, mbc


#runFit(numCPU = 1, noCP = 0)
   
#if YEAR == 1112 or YEAR == 1211: my_res = runFit(noCP = 0, numCPU = 3)
#my_res = runFit(numCPU = 3)
#if YEAR == 2012: my_res = runFit(noCP = 0, numCPU = 3, dataset = "12")


