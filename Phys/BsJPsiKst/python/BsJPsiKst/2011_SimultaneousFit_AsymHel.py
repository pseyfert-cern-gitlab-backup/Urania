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

from parameters import KpiBins4 as KpiBins, myCsp4 as myCsp, myCsd23 as myCsd, myCpd23 as myCpd, translateWeightsSPD as translateWeights

# To fit an specific bin, run the script with two input arguments corresponding to the lower and upper limits of the mass bin.
if (len(sys.argv) == 3): KpiBins = [sys.argv[1],sys.argv[2]]

print "Class for fitting polarization: AngularPDF"
timeZero = time.time()

ACC_FREE = 0
FIX_Bd = ACC_FREE
SAME_ACC = 1
YEAR = 1211# choose 2011, 2012 or 1211->2011+2012 data  
WEIGHT_CAT = "Bs" # type of weights: Bs, Bd or none for the cFit
ACC_TYPE = 2 # 1 for factorized acceptance, 2 for Normalization Weights
fix_param= kFALSE
#NTUPLE_PATH = "/home/diegoms/NTuplesFast/WalaaJuly/"#/NTuples/Bs_Jpsi_Kst_2013/"

print "\n IMPORTANT MESSAGE "
print "\n ####################################################################"
print "\n You choose: SFIT= ",SFIT,", YEAR= ",YEAR,", WEIGHT_CAT= ",WEIGHT_CAT

if (not NO_CP): print "\n CP asymmetries INCLUDED in the model"
else: print "\n CP asymmetries NOT INCLUDED in the model"
if (not DWAVE): print " D-wave NOT INCLUDED in the model"
else:
    if (SET0DWAVE): print " D-wave INCLUDED in the model but SET TO 0"
    else: print " D-wave INCLUDED in the model"
print "\n Kpi invariant mass range: ["+str(KpiBins[0])+","+str(KpiBins[len(KpiBins)-1])+"], divided into "+str(len(KpiBins)-1)+" bins"

print "\n ####################################################################"

if WEIGHT_CAT == "Bd":
    myweight = cor_sWeights_Bd
    #myAs2={0: 0.138,1: 0.027,2: 0.016,3: 0.082} ### Walaa's init values
    #myds={0: 3.6,1: 3.3,2: 2.00,3: 1.39}

if WEIGHT_CAT == "Bs":
    myweight = cor_sWeights_Bs
    #myAs2={0: 0.151,1: 0.054,2: 0.051,3: 0.171} ### Walaa's init values
    #myds={0: 2.,1:-0.71 ,2: 1.56,3: 1.63}
          
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
##NTUPLE_PATH = "root://eoslhcb.cern.ch//eos/lhcb/user/j/jugarcia/ntuples"
#NTUPLE_PATH = "~/w7folder/NTuples/"
SampleSizes = {}
for s in ["11p","11n","12p","12n"]:
     masterCat.defineType(s)
     SampleSizes[s] = 0
     for i in range(len(KpiBins)-1):
          name  = s + "_" + str(KpiBins[i]) + "_" + str(KpiBins[i+1])
         ## if (DWAVE):
##		myfiles[name] = TFile.Open(NTUPLE_PATH + "/Kpi_20" + name + ".root")
##		mytrees[name] = myfiles[name].Get("DecayTree")
	  #else:
          myfiles[name] = TFile.Open(NTUPLE_PATH + "/20" + name + ".root")
          mytrees[name] = myfiles[name].Get("DecayTree")
          SampleSizes[s] +=  mytrees[name].GetEntries()
          
AngBd_2011p,  AngBd_2011n = InitSignalPdfs("Bd","2011", acc_type = ACC_TYPE)
AngBd_2011p.OwnPhys(equalAsym = 1)

AngBd_2011p.modParam("CSP",1.,.1,kTRUE)
if (DWAVE != 0):
    AngBd_2011p.modParam("CSD",1.,.1,kTRUE)
    AngBd_2011p.modParam("CPD",1.,.1,kTRUE)



AngBd_2011p.OwnAcc()

if ACC_TYPE == 1: AngBd_2011p.modParam("c1_psi",-0.592,0.1)

AngBd_2011n.CopyFreeParams(AngBd_2011p)
AngBd_2011n.CopyAcc(AngBd_2011p) ## Assume same acceptance for "+" and "-"
    
# Angular PDF for Bs
AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011", acc_type = ACC_TYPE)

AngBs_2011p.OwnPhys()

AngBs_2011p.modParam("CSP",1.,.1,kTRUE)
if (DWAVE != 0):
    AngBs_2011p.modParam("CSD",1.,.1,kTRUE)
    AngBs_2011p.modParam("CPD",1.,.1,kTRUE)

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

nd_2011p_phys = RooFormulaVar("nBd_2011p_phys", "nBd_2011p_phys", "nBd_2011_phys*0.5*(1.+" + AngBd_2011p.ACPN.GetName() + ")", RooArgList(nd_2011,AngBd_2011p.ACPN))
nd_2011n_phys = RooFormulaVar("nBd_2011n_phys", "nBd_2011n_phys", "nBd_2011_phys - nBd_2011p_phys",RooArgList(nd_2011,nd_2011p_phys))

ns_2011p_phys = RooFormulaVar("nBs_2011p_phys", "nBs_2011p_phys", "nBs_2011_phys*0.5*(1.+" + AngBs_2011p.ACPN.GetName() + ")", RooArgList(ns_2011,AngBs_2011p.ACPN))
ns_2011n_phys = RooFormulaVar("nBs_2011n_phys", "nBs_2011n_phys", "nBs_2011_phys - nBs_2011p_phys",RooArgList(ns_2011,ns_2011p_phys))

ns_2011p = RooFormulaVar("nBs_2011p","nBs_2011p", "nBs_2011p_phys*(1 + AD_s - Aprod_s)",RooArgList(ns_2011p_phys, AD_s, Aprod_s)) #wk 
ns_2011n = RooFormulaVar("nBs_2011n","nBs_2011n", "nBs_2011n_phys*(1 - AD_s + Aprod_s)",RooArgList(ns_2011n_phys, AD_s, Aprod_s))  

nd_2011p = RooFormulaVar("nBd_2011p","nBd_2011p", "nBd_2011p_phys*(1 - AD_d + Aprod_d)",RooArgList(nd_2011p_phys, AD_d, Aprod_d))
nd_2011n = RooFormulaVar("nBd_2011n","nBd_2011n", "nBd_2011n_phys*(1 + AD_d - Aprod_d)",RooArgList(nd_2011n_phys, AD_d, Aprod_d))

nd_2012 = RooRealVar("nBd_2012_phys","nBd_2012_phys", 0.01*(SampleSizes["12p"] + SampleSizes["12n"]),2*(SampleSizes["12p"] + SampleSizes["12n"]))
ns_2012 = RooRealVar("nBs_2012_phys","nBs_2012_phys", 10.,SampleSizes["12p"] + SampleSizes["12n"])


nd_2012p_phys = RooFormulaVar("nBd_2012p_phys", "nBd_2012p_phys", "nBd_2012_phys*0.5*(1.+" + AngBd_2011p.ACPN.GetName() + ")", RooArgList(nd_2012,AngBd_2011p.ACPN))
nd_2012n_phys = RooFormulaVar("nBd_2012n_phys", "nBd_2012n_phys", "nBd_2012_phys - nBd_2012p_phys",RooArgList(nd_2012,nd_2012p_phys))

ns_2012p_phys = RooFormulaVar("nBs_2012p_phys", "nBs_2012p_phys", "nBs_2012_phys*0.5*(1.+" + AngBs_2011p.ACPN.GetName() + ")", RooArgList(ns_2012,AngBs_2011p.ACPN))
ns_2012n_phys = RooFormulaVar("nBs_2012n_phys", "nBs_2012n_phys", "nBs_2012_phys - nBs_2012p_phys",RooArgList(ns_2012,ns_2012p_phys))

ns_2012p = RooFormulaVar("nBs_2012p","nBs_2012p", "nBs_2012p_phys*(1 + AD_s - Aprod_s)",RooArgList(ns_2012p_phys, AD_s, Aprod_s))
ns_2012n = RooFormulaVar("nBs_2012n","nBs_2012n", "nBs_2012n_phys*(1 - AD_s + Aprod_s)",RooArgList(ns_2012n_phys, AD_s, Aprod_s))

nd_2012p = RooFormulaVar("nBd_2012p","nBd_2012p", "nBd_2012p_phys*(1 - AD_d + Aprod_d)",RooArgList(nd_2012p_phys, AD_d, Aprod_d))
nd_2012n = RooFormulaVar("nBd_2012n","nBd_2012n", "nBd_2012n_phys*(1 + AD_d - Aprod_d)",RooArgList(nd_2012n_phys, AD_d, Aprod_d))





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
allDatap = RooDataSet("all Data p","all Data p", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *[masterCatImports[0],masterCatImports[2]])
allDatan = RooDataSet("all Data n","all Data n", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *[masterCatImports[1],masterCatImports[3]])
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
   
    
def runFit(minos=0, offset = 0, numCPU = 1, dataset = "all"):
     
     w = RooWorkspace("w")
     wimport = getattr(w,'import')
     SimPdfTool = RooSimWSTool(w)
     mbc= RooSimWSTool.MultiBuildConfig(samplename)
     if (DWAVE and not SET0DWAVE): split_string = "As2"+WEIGHT_CAT+",fD"+WEIGHT_CAT+",ds"+WEIGHT_CAT+",d20"+WEIGHT_CAT+",CSP"+WEIGHT_CAT+",CSD"+WEIGHT_CAT+",CPD"+WEIGHT_CAT+","
     else: split_string = "As2"+WEIGHT_CAT+",ds"+WEIGHT_CAT+",CSP"+WEIGHT_CAT+","

     if (len(sys.argv) == 3): split_string = ""

     if dataset in ["11","all"]:
          wimport(model11p_ext,RooFit.RecycleConflictNodes())
          wimport(model11n_ext,RooFit.RecycleConflictNodes())

          mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys" + model11p.GetNormWeightString(),"binCat"))
          mbc.addPdf("11n",model11n_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys" + model11n.GetNormWeightString(),"binCat"))
  
     if dataset in ["12", "all"]:
          wimport(model12p_ext,RooFit.RecycleConflictNodes())
          wimport(model12n_ext,RooFit.RecycleConflictNodes())

          mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys" + model12p.GetNormWeightString(),"binCat")) 
          mbc.addPdf("12n",model12n_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys" + model12n.GetNormWeightString(),"binCat"))

     if dataset in ["allp"]:
          wimport(model11p_ext,RooFit.RecycleConflictNodes())
          wimport(model12p_ext,RooFit.RecycleConflictNodes())

          mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys" + model11p.GetNormWeightString(),"binCat"))
          mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys" + model12p.GetNormWeightString(),"binCat"))
    
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
          if DWAVE:
              argList.setRealValue("CSD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myCsd[i])
              argList.setRealValue("CPD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myCpd[i])
	      
          for thing in model11p.Tristan_weights: argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2011p_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          for thing in model11n.Tristan_weights: argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2011n_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          for thing in model12p.Tristan_weights: argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2012p_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
          for thing in model12n.Tristan_weights: argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2012n_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])          
     
     argList2 = Master.getParameters(allData)

     # Csp factors
     for i in range(len(KpiBins)-1):  print "CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList2.getRealValue("CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])) 
     if DWAVE :
          for i in range(len(KpiBins)-1):  print "CSD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList2.getRealValue("CSD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])) 
          for i in range(len(KpiBins)-1):  print "CPD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList2.getRealValue("CPD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]))      

     if dataset == "11": fitres_bins = Master.fitTo(dataset11,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "12": fitres_bins = Master.fitTo(dataset12,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "all": fitres_bins = Master.fitTo(allData,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "allp": fitres_bins = Master.fitTo(allDatap,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))

     return fitres_bins, Master, w, mbc, argList

file_res = TFile("vasilis.root","recreate")
if YEAR == 1112 or YEAR == 1211: my_res = runFit(numCPU = 3, minos = 1)
if YEAR == 2011: my_res = runFit(numCPU = 3, dataset = "11")
if YEAR == 2012: my_res = runFit(numCPU = 3, dataset = "12")
my_res[0].Write()
file_res.Close()
def fixCP():
    AngBs_2011p.ACPS.setVal(0)
    AngBs_2011p.ACPS.setConstant(1)
    AngBs_2011p.ACPL.setVal(0)
    AngBs_2011p.ACPL.setConstant(1)
    AngBs_2011p.ACPpa.setVal(0)
    AngBs_2011p.ACPpa.setConstant(1)
    AngBs_2011p.ACPpe.setVal(0)
    AngBs_2011p.ACPpe.setConstant(1)
    A_D.setMin(-0.3)
    A_D.setMax(0.3)
    A_D.setVal(-0.01185)
    A_D.setConstant(kTRUE)
    if (DWAVE != 0):
        AngBs_2011p.ACP2L.setVal(0)
        AngBs_2011p.ACP2L.setConstant(1)
        AngBs_2011p.ACP2pa.setVal(0)
        AngBs_2011p.ACP2pa.setConstant(1)
        AngBs_2011p.ACP2pe.setVal(0)
        AngBs_2011p.ACP2pe.setConstant(1)


#### DMS Feb 26

## 1  As2Bs_826_861   4.13337e-01   1.11907e-01  -1.10117e-01   1.14118e-01
##   2  As2Bs_861_896   7.22970e-02   2.80707e-02  -2.44286e-02   3.19071e-02
##   3  As2Bs_896_931   7.85055e-02   4.97345e-02  -4.28054e-02   5.63743e-02
##   4  As2Bs_931_966   5.36167e-01   1.07132e-01  -1.09978e-01   1.04763e-01
##   5  dpaBs       -2.54330e+00   1.57035e-01  -1.58872e-01   1.55220e-01
##   6  dpeBs        8.65076e-02   1.15190e-01  -1.15602e-01   1.15283e-01
##   7  dsBs_826_861   6.85987e-01   1.54774e-01  -1.62426e-01   1.53034e-01
##   8  dsBs_861_896  -6.21106e-01   2.39711e-01  -2.14736e-01   2.67076e-01
##   9  dsBs_896_931  -1.62474e+00   1.49574e-01  -1.63507e-01   1.49361e-01
##  10  dsBs_931_966  -1.67025e+00   1.24627e-01  -1.27885e-01   1.22042e-01
##  11  fLBs         5.24089e-01   2.46887e-02  -2.49426e-02   2.44385e-02
##  12  fpaBs        1.61161e-01   2.57601e-02  -2.51567e-02   2.63403e-02
##  13  nBs_2011_phys_826_861   3.57865e+01   5.98219e+00  -5.65363e+00   6.31964e+00
##  14  nBs_2011_phys_861_896   1.53216e+02   1.23780e+01  -1.20457e+01   1.27149e+01
##  15  nBs_2011_phys_896_931   1.75104e+02   1.32326e+01  -1.29003e+01   1.35694e+01
##  16  nBs_2011_phys_931_966   4.82643e+01   6.94724e+00  -6.61782e+00   7.28447e+00
##  17  nBs_2012_phys_826_861   5.99216e+01   7.74095e+00  -7.41287e+00   8.07573e+00
##  18  nBs_2012_phys_861_896   2.98944e+02   1.72900e+01  -1.69568e+01   1.76265e+01
##  19  nBs_2012_phys_896_931   3.50407e+02   1.87191e+01  -1.83871e+01   1.90543e+01
##  20  nBs_2012_phys_931_966   1.41853e+02   1.19102e+01  -1.15783e+01   1.22468e+01
##                               ERR DEF= 0.5
