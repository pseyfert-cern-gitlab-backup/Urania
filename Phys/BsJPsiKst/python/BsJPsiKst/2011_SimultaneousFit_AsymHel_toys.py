from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Asym_ToysAng import *
from parameters_toys import angular_params as angParams
from parameters_toys import parametric_angular_acceptance as acc_params

from parameters import KpiBins4 as KpiBins, myCsp23 as myCsp, myCsd23 as myCsd, myCpd23 as myCpd, translateWeightsSPD as translateWeights

from parameters_toys import d_ACPs

gRandom = TRandom3()
seed = 0 # see http://root.cern.ch/root/html/TRandom3.html#TRandom3:SetSeed
gRandom.SetSeed(seed)
randomID = gRandom.Uniform(-100,100)

Pi = 3.141592653589793
TwoPi = 2.*Pi

debug = True





# To fit an specific bin, run the script with two input arguments corresponding to the lower and upper limits of the mass bin.
tupleSource   = str(sys.argv[1]) # string to tag the source of ntuples: 'Toys' or 'Data' 
iexp          = str(sys.argv[2]) # int to tag the nbr of the experiment
_USE_GRID_    = str(sys.argv[3]) # bool to tag if we are on the grid or not (files location)
InPutTag      = str(sys.argv[4]) # string to tag the name of the InPutFile
OutPutTag     = str(sys.argv[5]) # string to tag the name of the OutPutFile
sWeights      = str(sys.argv[6]) # str to flag if we want to copy sWeighted files
trueDist      = str(sys.argv[7]) # str to flag if we want to fit true angular distributions
nonZeroACPs   = str(sys.argv[8]) # str to flag if we generate the ACPs with non zero values
doSyst        = str(sys.argv[9]) # str to flag if we perform systematics evaluation
doAccSyst     = str(sys.argv[10])# str to flag if we perform systematics evaluation for Angular acceptance
OneSigma      = str(sys.argv[11]) #string to tag if we move the norm. Weights by plus or minus one sigma: "P" or "M"

_USE_GRID_=int(_USE_GRID_)
sWeights  =int(sWeights)
trueDist=int(trueDist)
nonZeroACPs=int(nonZeroACPs)
doSyst=int(doSyst)
doAccSyst=int(doAccSyst)







ACPset        = "set_noCP"
_MINOS_       = 1
if nonZeroACPs:
    ACPset    = str(sys.argv[10]) # string to tag the set of ACPs
    _MINOS_   = 0

nCPUs = 1
if not _USE_GRID_:
    nCPUs = 8

print "Class for fitting polarization: AngularPDF"
timeZero = time.time()

ACC_FREE = 0
FIX_Bd = ACC_FREE
SAME_ACC = 1
YEAR = 1211# choose 2011, 2012 or 1211->2011+2012 data  
WEIGHT_CAT = "Bs" # type of weights: Bs, Bd or none for the cFit
ACC_TYPE = 2 # 1 for factorized acceptance, 2 for Normalization Weights
flatAcc = 0
fix_param= kFALSE

if (WEIGHT_CAT=="Bd"): 
    nominal_fit =  {'ACPLBd': 0.034908797834336536, 'nBd_2011_phys_861_896': 26522.74418435338, 'fpaBd': 0.253720491776814, 'fLBd': 0.5115733619250857, 'dpeBd': 3.033578103494267, 'dsBd_861_896': 2.764321114454498, 'nBd_2011_phys_826_861': 7196.898721386629, 'nBd_2012_phys_861_896': 56369.740142529794, 'dsBd_826_861': 3.781102712656586, 'As2Bd_861_896': 0.01730633350765509, 'dsBd_931_966': 2.017447751361098, 'nBd_2012_phys_826_861': 15253.521299814052, 'As2Bd_826_861': 0.06158808372214847, 'ACPSBd': 0.14891920924207547, 'As2Bd_931_966': 0.31395744147081, 'nBd_2012_phys_931_966': 15871.935391560288, 'nBd_2011_phys_896_931': 23805.299937234235, 'dpaBd': -2.8779215977671413, 'dsBd_896_931': 2.129496094606144, 'nBd_2012_phys_896_931': 50431.323976171116, 'nBd_2011_phys_931_966': 7515.662526222207, 'As2Bd_896_931': 0.0513136987868249}

elif (WEIGHT_CAT=="Bs"): 
    nominal_fit ={'nBs_2011_phys_931_966': 46.97187439718392, 'nBs_2012_phys_896_931': 326.78581898274035, 'dsBs_896_931': -2.083255407477461, 'nBs_2011_phys_896_931': 156.31062071698844, 'dpeBs': -0.08058734396429568, 'nBs_2011_phys_861_896': 142.67184248400332, 'ACPpaBs': -0.4447110716513627, 'dsBs_861_896': -0.4950160624423221, 'fpaBs': 0.18116889892116878, 'As2Bs_826_861': 0.5256840561267434, 'As2Bs_931_966': 0.6978287427751428, 'ACPLBs': 0.17530775376940522, 'nBs_2012_phys_826_861': 54.4574314931169, 'fLBs': 0.48363060967986604, 'dpaBs': -2.5851910748964, 'nBs_2012_phys_931_966': 121.14451728550068, 'As2Bs_861_896': 0.10320851509262918, 'dsBs_931_966': -2.318614456032184, 'ACPpeBs': 0.07528314367115763, 'ACPSBs': -0.2694179650057612, 'dsBs_826_861': 0.2961264552812759, 'As2Bs_896_931': 0.06361982182340231, 'nBs_2012_phys_861_896': 288.87377220088587, 'nBs_2011_phys_826_861': 29.842201396132992}


tagSweights = ""
if sWeights:
	tagSweights = "_AddedsWeights"
tagTrueAngles = ""
if trueDist:
    tagTrueAngles = "sig%s==1 && "%WEIGHT_CAT

if tupleSource == "Toys" and not sWeights and not trueDist:
    print "ERROR:: trying to fit sWeighted distributions from a file without sWeights!!!"
    exit(1)

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
    myweight = cor_sWeights_nBd

if WEIGHT_CAT == "Bs":
    myweight = cor_sWeights_nBs
          
## Why do we need this ?
Mass.setRange("ref",Mass.getMin(),Mass.getMax())
CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
Phi.setRange("ref",Phi.getMin(),Phi.getMax())
###
Mass.setRange("Bs_range",5366.77-25,5366.77+25) 
Mass.setRange("Bd_range",5279.5-25,5279.5+25)

myfiles = {}
mytrees0 = {}
mytrees = {}
samplename = "sample"
masterCat =  RooCategory(samplename, samplename)
binCat = RooCategory("binCat","binCat")
for i in range(len(KpiBins)-1): binCat.defineType(str(KpiBins[i]) + "_" + str(KpiBins[i+1]))
             


# 2011 pos
AngBd_2011p, AngBd_2011n = InitSignalPdfs("Bd","2011",acc_type = ACC_TYPE)
AngBd_2011p.OwnPhys(equalAsym = 1)
if flatAcc:
    AngBd_2011p.FlatAcc()
else:
    AngBd_2011p.OwnAcc()

#Bd paper values 
fL_Bd  = angParams["Bd"][0]["fL"]
fpa_Bd = angParams["Bd"][0]["fpa"]
dpa_Bd = angParams["Bd"][0]["dpa"]
dpe_Bd = angParams["Bd"][0]["dpe"]
ds_Bd  = angParams["Bd"][0]["ds"]
As2_Bd = angParams["Bd"][0]["As2"]

AngBd_2011p.modParamAsym("fL",  fL_Bd,   fL_Bd,         1-fL_Bd,       False) 
AngBd_2011p.modParamAsym("fpa", fpa_Bd,  fpa_Bd,        1-fpa_Bd,      False)
AngBd_2011p.modParamAsym("dpa", dpa_Bd,  TwoPi-dpa_Bd,  TwoPi+dpa_Bd,  False)
AngBd_2011p.modParamAsym("dpe", dpe_Bd,  TwoPi-dpe_Bd,  TwoPi+dpe_Bd,  False)

AngBd_2011p.modParamAsym("ds",  ds_Bd,   TwoPi-ds_Bd,   TwoPi+ds_Bd,  False)
AngBd_2011p.modParamAsym("As2", As2_Bd,  As2_Bd,        1-As2_Bd,     False)#2012
AngBd_2011p.modParam("CSP",1.,.1,True)

if tupleSource == "Toys":
    AngBd_2011p.ACPL.setVal(angParams["Bd"][0]["ACPL"])
    AngBd_2011p.ACPL.setConstant(True)

if not flatAcc and ACC_TYPE==1:
    AngBd_2011p.modParam("c1_psi",  acc_params["Bd"]["2011"]["c1_psi"],0.1, True)
    AngBd_2011p.modParam("c2_psi",  acc_params["Bd"]["2011"]["c2_psi"],0.1, True)
    AngBd_2011p.modParam("c3_psi",  acc_params["Bd"]["2011"]["c3_psi"],0.1, True)
    AngBd_2011p.modParam("c4_psi",  acc_params["Bd"]["2011"]["c4_psi"],0.1, True)
    AngBd_2011p.modParam("c2_theta",acc_params["Bd"]["2011"]["c2_theta"],0.1, True)

# 2011 neg
AngBd_2011n.CopyFreeParams(AngBd_2011p)
#AngBd_2011n.CopyAcc(AngBd_2011p)
AngBd_2011n.OwnAcc()

# -----------------------------------------------------------------------
# 2012 pos
AngBd_2012p,  AngBd_2012n = InitSignalPdfs("Bd","2012",acc_type = ACC_TYPE)
AngBd_2012p.CopyPhys(AngBd_2011p)
AngBd_2012p.CopyAcc(AngBd_2011p)
#AngBd_2012p.OwnAcc()

# 2012 neg
AngBd_2012n.CopyPhys(AngBd_2011n)
AngBd_2012n.CopyAcc(AngBd_2011n)
#AngBd_2012n.OwnAcc()

# -----------------------------------------------------------------------
# Bs  
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------
# 2011 pos
AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011",acc_type = ACC_TYPE)
AngBs_2011p.OwnPhys(equalAsym = 0)

fL_Bs  = angParams["Bs"][0]["fL"]
fpa_Bs = angParams["Bs"][0]["fpa"]
dpa_Bs = angParams["Bs"][0]["dpa"]
dpe_Bs = angParams["Bs"][0]["dpe"]
ds_Bs  = angParams["Bs"][0]["ds"]
As2_Bs = angParams["Bs"][0]["As2"]

# Fix the angular parameters (by hand here)
AngBs_2011p.modParamAsym("fL",  fL_Bs,   fL_Bs,         1-fL_Bs,      False) 
AngBs_2011p.modParamAsym("fpa", fpa_Bs,  fpa_Bs,        1-fpa_Bs,     False)
AngBs_2011p.modParamAsym("dpa", dpa_Bs,  TwoPi-dpa_Bs,  TwoPi+dpa_Bs, False)
AngBs_2011p.modParamAsym("dpe", dpe_Bs,  TwoPi-dpe_Bs,  TwoPi+dpe_Bs, False)
AngBs_2011p.modParamAsym("ds",  ds_Bs,   TwoPi-ds_Bs,   TwoPi+ds_Bs,  False)
AngBs_2011p.modParamAsym("As2", As2_Bs,  As2_Bs,        1-As2_Bs,     False)#2012

AngBs_2011p.modParam("CSP",1.,.1,True)

ACPL_Bs  = angParams["Bs"][0]["ACPL"]
ACPpa_Bs = angParams["Bs"][0]["ACPpa"]
ACPpe_Bs = angParams["Bs"][0]["ACPpe"]
ACPS_Bs  = angParams["Bs"][0]["ACPS"]

if nonZeroACPs:
    ACPL_Bs  = d_ACPs[ACPset]["ACPL"]
    ACPpa_Bs = d_ACPs[ACPset]["ACPpa"]
    ACPpe_Bs = d_ACPs[ACPset]["ACPpe"]
    ACPS_Bs  = d_ACPs[ACPset]["ACPS"]

    print "Going to fit pseudo-experiment with ACPs values set to random set number %s :"%(ACPset[len(ACPset)-1:])
    for key in d_ACPs[ACPset].keys():
        print "%s = %s"%(key, d_ACPs[ACPset][key])
else:
    print "Going to fit pseudo-experiment with all ACPs set to zero (taken from parameters_toys.py) !!!"

if tupleSource == "Toys":
    AngBs_2011p.ACPL.setVal(ACPL_Bs)
    AngBs_2011p.ACPpa.setVal(ACPpa_Bs)
    AngBs_2011p.ACPpe.setVal(ACPpe_Bs)
    AngBs_2011p.ACPS.setVal(ACPS_Bs)

# 2011 neg
AngBs_2011n.CopyFreeParams(AngBs_2011p)

# -----------------------------------------------------------------------
# 2012 
AngBs_2012p,  AngBs_2012n = InitSignalPdfs("Bs","2012",acc_type = ACC_TYPE)
AngBs_2012p.CopyPhys(AngBs_2011p)
AngBs_2012n.CopyPhys(AngBs_2011n)

# -----------------------------------------------------------------------
# COPY ACCEPTANCE PARAMETERS
if SAME_ACC:
    AngBs_2011p.CopyAcc(AngBd_2011p)
    AngBs_2012p.CopyAcc(AngBd_2012p)
    AngBs_2011n.CopyAcc(AngBd_2011n)
    AngBs_2012n.CopyAcc(AngBd_2012n)

# --------------------------------------
AngBs_2012n.CopyFreeParams(AngBs_2011p)
AngBs_2012p.CopyFreeParams(AngBs_2011p)

# MAKE THE PDFs
AngBd_2011n.make() 
AngBs_2011n.make()
AngBd_2011p.make()
AngBs_2011p.make()

AngBd_2012n.make()
AngBs_2012n.make()
AngBd_2012p.make()
AngBs_2012p.make()

print "2011p:"
print "ACPL = ",AngBs_2011p.ACPL.getVal()
print "ACPpa = ",AngBs_2011p.ACPpa.getVal()
print "ACPpe = ",AngBs_2011p.ACPpe.getVal()
print "ACPS = ",AngBs_2011p.ACPS.getVal()
print "2011n:"
print "ACPL = ",AngBs_2011n.ACPL.getVal()
print "ACPpa = ",AngBs_2011n.ACPpa.getVal()
print "ACPpe = ",AngBs_2011n.ACPpe.getVal()
print "ACPS = ",AngBs_2011n.ACPS.getVal()
print "2012n:"
print "ACPL = ",AngBs_2012n.ACPL.getVal()
print "ACPpa = ",AngBs_2012n.ACPpa.getVal()
print "ACPpe = ",AngBs_2012n.ACPpe.getVal()
print "ACPS = ",AngBs_2012n.ACPS.getVal()
print "2012p:"
print "ACPL = ",AngBs_2012p.ACPL.getVal()
print "ACPpa = ",AngBs_2012p.ACPpa.getVal()
print "ACPpe = ",AngBs_2012p.ACPpe.getVal()
print "ACPS = ",AngBs_2012p.ACPS.getVal()


###########################################################################
###########################################################################

SampleSizes = {}
mydatasets = {}
mergeddatasets = {}
masterCatImports = []

if trueDist:
    myweight.setVal(1.)
    myweight.setConstant(1.)

for s in ["11p","11n","12p","12n"]:
     masterCat.defineType(s)
     SampleSizes[s] = 0
     myImports = []
     for i in range(len(KpiBins)-1):
          binname = str(KpiBins[i]) + "_" + str(KpiBins[i+1])
          name  = s + "_" + binname
          
          inputFile_name = ""
          if tupleSource == "Toys":
              inputFile_name="genData_%s_Exp%s%s.root"%(InPutTag,iexp,tagSweights)
          else:
              if not doSyst:
#                 
                  inputFile_name="%s.root"%(InPutTag)
              else:
#                  
                  inputFile_name="%s.root"%(InPutTag)

          if _USE_GRID_:
              myfiles[name] = TFile.Open(inputFile_name)
          else: 
              if tupleSource == "Toys":
                  if tagSweights:
                      myfiles[name] = TFile.Open("/zfs_lhcb/Bs2JpsiKst/%s/splitTuples/%s/%s"%(tupleSource,InPutTag,inputFile_name))
                  else:
                      myfiles[name] = TFile.Open("/zfs_lhcb/Bs2JpsiKst/%s/Tuples/%s/%s"%(tupleSource,InPutTag,inputFile_name))
              else:
                  if not doSyst:
                      myfiles[name] = TFile.Open("/zfs_lhcb/Bs2JpsiKst/%s/splitTuples/%s"%(tupleSource,inputFile_name))
                  else:
                      myfiles[name] = TFile.Open("/zfs_lhcb/Bs2JpsiKst/%s/splitTuples/%s"%(tupleSource,inputFile_name))

          treeName    = "genTree"
          selCut      = "%s KpiBin==%s && Year==20%s"%(tagTrueAngles,str(i),s[:2])
          kChargeName = "Kcharge"
          if tupleSource == "Data":
              treeName    = "DecayTree"
              selCut      = "Kst_892_0_MM >= %s && Kst_892_0_MM < %s && Year==20%s"%(KpiBins[i],KpiBins[i+1],s[:2])
              kChargeName = "Kplus_ID"


          mytrees0[name] = myfiles[name].Get(treeName)
          fx=TFile("SimulFit_nada_%s.root"%randomID,"recreate")


          if(s[2:]=='p'):
              selCut+= " && %s>0"%kChargeName
          else: 
              selCut+= " && %s<0"%kChargeName
          mytrees[name]  = mytrees0[name].CopyTree(selCut)
              

          nEntries = mytrees[name].GetEntries()
          if tupleSource == "Toys": 
              nEntries = mytrees[name].GetEntries("sig%s==1"%WEIGHT_CAT)

          print "tree ", name, "size: ",nEntries
          SampleSizes[s] +=  nEntries
          
          mydatasets[name] = RooDataSet("data" + name,"data" + name, mytrees[name],RooArgSet(CPsi,CTheta,Phi,myweight))
          myImports.append(RooFit.Import(binname, mydatasets[name]))

          myfiles[name].Close()
          fx.Close()
          os.system("rm SimulFit_nada_%s.root"%randomID)

     mergeddatasets[s] = RooDataSet(s,s,RooArgSet(CPsi,CTheta,Phi,myweight),RooFit.Index(binCat),*myImports)
     masterCatImports.append(RooFit.Import(s, mergeddatasets[s]))

allData = RooDataSet("all Data","all Data", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports)
allDatap = RooDataSet("all Data p","all Data p", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *[masterCatImports[0],masterCatImports[2]])
allDatan = RooDataSet("all Data n","all Data n", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *[masterCatImports[1],masterCatImports[3]])
dataset11 = RooDataSet("dataset11","dataset11", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports[:2])
dataset12 = RooDataSet("dataset12","dataset12", RooArgSet(CPsi,CTheta,Phi,myweight,binCat),RooFit.Index(masterCat),RooFit.Cut(""),RooFit.CutRange(""),RooFit.WeightVar(myweight.GetName()), *masterCatImports[2:])



#######################################ext.
## Normaliations to Make extended PDF
    
nd_2011 = RooRealVar("nBd_2011_phys","nBd_2011_phys", 0.01*(SampleSizes["11p"] + SampleSizes["11n"]),2*(SampleSizes["11p"] + SampleSizes["11n"]))
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
   

def fixCP():
    ACPS_Bs=ACPL_Bs=ACPpa_Bs=ACPpe_Bs=0.
    AngBs_2011p.ACPS.setVal(ACPS_Bs)
    AngBs_2011p.ACPS.setConstant(True)
    AngBs_2011p.ACPL.setVal(ACPL_Bs)
    AngBs_2011p.ACPL.setConstant(True)
    AngBs_2011p.ACPpa.setVal(ACPpa_Bs)
    AngBs_2011p.ACPpa.setConstant(True)
    AngBs_2011p.ACPpe.setVal(ACPpe_Bs)
    AngBs_2011p.ACPpe.setConstant(True)
    AD_s.setVal(0)
    AD_s.setConstant(kTRUE)
    Aprod_s.setVal(0)
    Aprod_s.setConstant(kTRUE)
    #     A_D.setMin(-0.3)
    #     A_D.setMax(0.3)
    #     A_D.setVal(-0.01185)
    #     A_D.setConstant(kTRUE)
    if (DWAVE != 0):
        AngBs_2011p.ACP2L.setVal(0)
        AngBs_2011p.ACP2L.setConstant(1)
        AngBs_2011p.ACP2pa.setVal(0)
        AngBs_2011p.ACP2pa.setConstant(1)
        AngBs_2011p.ACP2pe.setVal(0)
        AngBs_2011p.ACP2pe.setConstant(1)



    
def runFit(minos=0, offset = 0, numCPU = 1, dataset = "all"):
     #fixCP()
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
          if (ACC_TYPE== 2):
              mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys" + model11p.GetNormWeightString(),"binCat"))
              mbc.addPdf("11n",model11n_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys" + model11n.GetNormWeightString(),"binCat"))
          else: 
              mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys","binCat"))
              mbc.addPdf("11n",model11n_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys","binCat"))

     if dataset in ["12", "all"]:
          wimport(model12p_ext,RooFit.RecycleConflictNodes())
          wimport(model12n_ext,RooFit.RecycleConflictNodes())
          
          if (ACC_TYPE== 2):
              mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys" + model12p.GetNormWeightString(),"binCat")) 
              mbc.addPdf("12n",model12n_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys" + model12n.GetNormWeightString(),"binCat"))
          else:
              mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys","binCat")) 
              mbc.addPdf("12n",model12n_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys","binCat"))

     if dataset in ["allp"]:
          wimport(model11p_ext,RooFit.RecycleConflictNodes())
          wimport(model12p_ext,RooFit.RecycleConflictNodes())

          if (ACC_TYPE== 2):
              mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys" + model11p.GetNormWeightString(),"binCat"))
              mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys" + model12p.GetNormWeightString(),"binCat"))
          else: 
              mbc.addPdf("11p",model11p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2011_phys","binCat"))
              mbc.addPdf("12p",model12p_ext.GetName(),RooFit.SplitParam(split_string + "n"+WEIGHT_CAT+"_2012_phys","binCat"))

     wimport(RooArgSet(masterCat, binCat))
    
     w.Print()

     Master = SimPdfTool.build("Master",mbc) 

     Master.Print()
     Master.indexCat().Print()
     Master.indexCat().Print("v")
    
     w.Print()
         
     argList = Master.getParameters(allData)
     argList.Print()
     if (WEIGHT_CAT=="Bs"):
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_826_861",3.05065e+01)
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_861_896",1.42640e+02)
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_896_931",1.57590e+02)
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_931_966",4.47586e+01)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_826_861",5.62591e+01)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_861_896",2.88887e+02)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_896_931",3.29490e+02)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_931_966",1.22927e+02)
     elif (WEIGHT_CAT=="Bd"):
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_826_861",7.19690e+03)
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_861_896",2.65227e+04)
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_896_931",2.38053e+04)
         argList.setRealValue("n"+WEIGHT_CAT+"_2011_phys_931_966",7.51566e+03)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_826_861",1.52535e+04)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_861_896",5.63697e+04)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_896_931",5.04313e+04)
         argList.setRealValue("n"+WEIGHT_CAT+"_2012_phys_931_966",1.58719e+04)

     for i in range(len(KpiBins)-1): 
          argList.setRealValue("CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),angParams[WEIGHT_CAT][i]["CSP"])
          argList.setRealValue("As2"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),angParams[WEIGHT_CAT][i]['As2'])
          argList.setRealValue("ds"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),angParams[WEIGHT_CAT][i]['ds'])
          if DWAVE:
              argList.setRealValue("CSD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myCsd[i]) 
              argList.setRealValue("CPD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]),myCpd[i])
          if (ACC_TYPE== 2):
              
              
        
              for thing in model11p.Tristan_weights: 
                  argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2011p_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])

              for thing in model11n.Tristan_weights: 
                  argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2011n_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])

              for thing in model12p.Tristan_weights: argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2012p_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])
              for thing in model12n.Tristan_weights: argList.setRealValue(thing.GetName()+"_"+ str(KpiBins[i]) +  "_" + str(KpiBins[i+1]), NormWeights["2012n_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])][translateWeights(thing.GetName())])          
              
              if doAccSyst:
              
                  
                  states= ['0S', '0pa', 'paS', 'pape', '0pe', 'SS', 'papa', 'pepe', '00', 'peS']
                  for year in ["2011_","2012_"]:
                              for charge in ["pos_","neg_"]:
                                  for i in range(len(KpiBins)-1):

                                      name= "w_"+states[int(iexp)]+"Bd"+year+charge+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])
                                      ref =year[:4]+charge[:1]+  "_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])
                                      weight= WeightsBd[ref][states[int(iexp)]]
                                      sigma= WeightsBdErr[ref][states[int(iexp)]]
                                      if (OneSigma=="P"):
                                       weightANDsig= weight+sigma
                                      elif (OneSigma=="M"):
                                       weightANDsig= weight-sigma
                                                                              
                                      argList.setRealValue(name,weightANDsig)
                  normWsyst={}
                  for state in states:
                      for charge in ["pos_","neg_"]:
                          for i in range(len(KpiBins)-1):
                          
                              name= "w_"+state+"Bd2011_"+charge+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])
                              w= argList.getRealValue(name)
                              normWsyst.update({name:w})
                  

     # Csp factors
     for i in range(len(KpiBins)-1):  print "CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList.getRealValue("CSP"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])) 
     if DWAVE :
          for i in range(len(KpiBins)-1):  print "CSD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList.getRealValue("CSD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])) 
          for i in range(len(KpiBins)-1):  print "CPD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])+":",argList.getRealValue("CPD"+WEIGHT_CAT+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1]))      
              

              
     argSet = Master.getParameters(allData)
     argSet.Print()
     iter = argSet.iterator()
     for iarg in range(0, argSet.getSize()):
         arg = iter.Next()
         parVal = argSet.getRealValue(arg.GetName())
         print "Parameter :",arg.GetName()," with initial value :",parVal
                   
#                         
                         
     if dataset == "11": fitres_bins = Master.fitTo(dataset11,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "12": fitres_bins = Master.fitTo(dataset12,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "all": fitres_bins = Master.fitTo(allData,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     elif dataset == "allp": fitres_bins = Master.fitTo(allDatap,RooFit.Minos(minos), RooFit.Save(), RooFit.NumCPU(numCPU),RooFit.SumW2Error(kTRUE))
     

####################################################
     res_file = TFile.Open('fit_result_%s.root'%(OutPutTag),'recreate')   
     fitres_bins.Write()
     res_file.Close()
     
     # Store the fit results
     OutPutFileName = ""
     OutPutFileName_Loc = ""

     if _USE_GRID_:
         if tupleSource == "Toys":
             OutPutFileName = "%sAngFitResults_%s_%s_%s_Exp%s.root"%(OutPutFileName_Loc,tupleSource,InPutTag,OutPutTag,iexp)
         else:
             if not doSyst:
                 OutPutFileName = "%sAngFitResults_%s_%s_%s_nominal.root"%(OutPutFileName_Loc,tupleSource,InPutTag,OutPutTag)
             else:
                 OutPutFileName = "%sAngFitResults_%s_%s_%s_systSet%s.root"%(OutPutFileName_Loc,tupleSource,InPutTag,OutPutTag,iexp)

     else:
         if tupleSource == "Toys":
             OutPutFileName_Loc = "/zfs_lhcb/Bs2JpsiKst/%s/fitResults/%s_%s/"%(tupleSource,InPutTag,OutPutTag)
             os.system("mkdir %s"%OutPutFileName_Loc)
             OutPutFileName = "%sAngFitResults_%s_%s_%s_Exp%s.root"%(OutPutFileName_Loc,tupleSource,InPutTag,OutPutTag,iexp)
         else:
             if not doSyst:
                 OutPutFileName_Loc = ""#"/zfs_lhcb/Bs2JpsiKst/%s/fitResults/Angles/"%(tupleSource)
                 os.system("mkdir %s"%OutPutFileName_Loc)
                 OutPutFileName = "%sAngFitResults_%s_%s_%s_nominal.root"%(OutPutFileName_Loc,tupleSource,InPutTag,OutPutTag)
             else:
                 OutPutFileName_Loc = "/zfs_lhcb/Bs2JpsiKst/%s/fitResults/forSyst/Angles/"%(tupleSource)
                 os.system("mkdir %s"%OutPutFileName_Loc)
                 OutPutFileName = "%sAngFitResults_%s_%s_%s_systSet%s.root"%(OutPutFileName_Loc,tupleSource,InPutTag,OutPutTag,iexp)


         
     outf = TFile(OutPutFileName,"RECREATE")
     outt = TTree("rfr","Weighted Angular sFit Toymc Tree")

     # ----------------------------------------------------------------------------------------------------------------------
     # Declare the structure to create the TTree
     gROOT.ProcessLine( "struct MyStructF{ Float_t afloat; };" )
     gROOT.ProcessLine( "struct MyStructI{ Int_t anInt; };" )

     # ----------------------------------------------------------------------------------------------------------------------
     # Defnitions of the numbers of stored values per fitted parameter
     nv = 6 # 6 values for each parameter: initial value, fitted value, fitted error, fitted error high, fitted error low, pull
     strl = [ "_genVal", "_fitVal", "_err", "_errHi", "_errLo", "_pull" ] 
     
     # ----------------------------------------------------------------------------------------------------------------------
     # Decalaration of the list containing the values in the branchs ("emptied" and filled for each pseudo-experiment) 
     nexp = 1
     parlist = []

     # First make the tree structure with the names of the branches, as well as the type of the data stored in the leaves (int, float, double, etc)
     print""
     print"Creation of the angular fit tree structure..."
     parlist.append( MyStructI() )
     outt.Branch("iExp", AddressOf(parlist[0],'anInt'), "iExp/I" )

     parlist.append( MyStructI() )
     outt.Branch("fitStatus", AddressOf(parlist[1],'anInt'), "fitStatus/I" )
     
     my_array={}
     my_array2={}
     my_array3={}
     my_array4={}

     diffWithNominal={}

     for par in range( 0, fitres_bins.floatParsFinal().getSize() ):
         param = fitres_bins.floatParsFinal().at(par)
         my_array.update({param.GetName():fitres_bins.floatParsFinal().at(par).getVal()})
         my_array2.update({param.GetName():fitres_bins.floatParsFinal().at(par).getError()})
         my_array3.update({param.GetName():fitres_bins.floatParsFinal().at(par).getErrorHi()})
         my_array4.update({param.GetName():fitres_bins.floatParsFinal().at(par).getErrorLo()})
         
         
         for ii in range(0,nv):
             parlist.append( MyStructF() )
             outt.Branch( param.GetName()+strl[ii], AddressOf(parlist[nv*par + ii + 2],'afloat'), param.GetName()+strl[ii]+"/F" )

     # Loop again to get the correlations between the fitted parameters 
     for par_i in range( 0, fitres_bins.floatParsFinal().getSize() ):
         param_i = fitres_bins.floatParsFinal().at(par_i)
         for par_j in range( 0, fitres_bins.floatParsFinal().getSize() ):
             param_j = fitres_bins.floatParsFinal().at(par_j)
             parlist.append( MyStructF() )
             outt.Branch( "Corr_"+param_i.GetName()+"_"+param_j.GetName(), AddressOf(parlist[nv*fitres_bins.floatParsFinal().getSize() + fitres_bins.floatParsFinal().getSize()*par_i + par_j + 2],'afloat'), "Corr_"+param_i.GetName()+"_"+param_j.GetName()+"/F" )

     branches = outt.GetListOfBranches()

     # Now fill the tree...
     print""
     print"Filling the tree now..."
     for iter in range(0,nexp): #loop on the pseudo-experiments

         # Fill the information on the number of the considered pseudo-experiment
         parlist[0].anInt = iter+1

         fitStatus = 0
         for par in range( 0, fitres_bins.floatParsFinal().getSize() ): #loop on the parameters
             val_ini = fitres_bins.floatParsInit().at(par).getVal() 
             val_fit = fitres_bins.floatParsFinal().at(par).getVal() 
             err     = fitres_bins.floatParsFinal().at(par).getError()   # Gaussian error given by HESSE
             errHi   = fitres_bins.floatParsFinal().at(par).getErrorHi() # Asymm error high given by MINOS
             errLo   = fitres_bins.floatParsFinal().at(par).getErrorLo() # Asymm error low given by MINOS

             if debug: print ""
             if debug: print "At param:", fitres_bins.floatParsInit().at(par).GetName()
             if debug: print "   val_ini = %s"%(val_ini)
             if debug: print "   val_fit = %s"%(val_fit)
             if debug: print "   err     = %s"%(err)
             if debug: print "   errHi   = %s"%(errHi)
             if debug: print "   errLo   = %s"%(errLo)

                  
         
             


             if "_phys" not in fitres_bins.floatParsInit().at(par).GetName() and abs(val_fit - val_ini) > 20*err:
                 fitStatus = 1
                 print "Setting fitStatus to 1 (failed) since abs(val_fit - val_ini) > 20*err"
             else:
                 fitStatus = 3
                 print "Setting fitStatus to 3 (success) since abs(val_fit - val_ini) < 20*err"

             # if (par>7 and par<14):
             if "ds" in fitres_bins.floatParsInit().at(par).GetName() or "dp" in fitres_bins.floatParsInit().at(par).GetName():
                 val_fit_Temp = val_fit
                 Iteration_Path = 2*pi
                 print "Initial val_fit_val = ", val_fit_Temp

                 if( val_fit < -pi or  val_fit> pi):
                     while(val_fit_Temp < -pi or val_fit_Temp> pi):
                         if(val_fit_Temp < -pi):
                            val_fit_Temp += Iteration_Path
                         if(val_fit_Temp > pi):
                            val_fit_Temp -= Iteration_Path

                         val_fit = val_fit_Temp
                 else:
                     print "val_fit is ", val_fit
                 print "final val_fit ",  val_fit


             pull = -99999.            
             if not err==0.:
                 delta = (val_fit - val_ini)
                 if fitres_bins.floatParsFinal().at(par).hasAsymError():
                     # Asymmetric error given by MINOS
                     if delta < 0.0: pull = delta/errHi
                     else:           pull = -delta/errLo
                 else: pull = delta/err
                 # Gaussian error given by HESSE
             else:
                 pull = 0.

             if debug: print "   pull    = %s"%(pull)

             parlist[nv*par + 0 + 2].afloat = val_ini
             parlist[nv*par + 1 + 2].afloat = val_fit
             parlist[nv*par + 2 + 2].afloat = err
             parlist[nv*par + 3 + 2].afloat = errHi
             parlist[nv*par + 4 + 2].afloat = errLo
             parlist[nv*par + 5 + 2].afloat = pull        


         # Fill the information on the fit status
         print"fitStatus = ",fitStatus
         parlist[1].anInt = int(fitStatus)

         # Fill the correlation branches
         for par_i in range( 0, fitres_bins.floatParsFinal().getSize() ):
             param_i = fitres_bins.floatParsFinal().at(par_i)
             for par_j in range( 0, fitres_bins.floatParsFinal().getSize() ):
                 param_j = fitres_bins.floatParsFinal().at(par_j)
                 parlist[nv*fitres_bins.floatParsFinal().getSize() + fitres_bins.floatParsFinal().getSize()*par_i + par_j + 2].afloat = float(fitres_bins.correlation(param_i,param_j))        

         # Fill the TTree and go to the next pseudo-experiment
         outt.Fill()

     outf.Write()
     outf.Close()
     
     if doAccSyst: 
         sys.stdout = open('fitRes'+WEIGHT_CAT+'%s_%s_sets.py'%(OutPutTag,OneSigma), 'a+')
     else: 
         sys.stdout = open('fitRes'+WEIGHT_CAT+'%s_sets.py'%(OutPutTag), 'a+')
              
     if doAccSyst: 
         print "normWsyst_Exp%s = "%(iexp),normWsyst
     print ""
     print "fitRes_Exp%s = "%(iexp),my_array
     print ""
     print "fitRes_Exp%s_Error = "%(iexp),my_array2
     print ""
     print "fitRes_Exp%s_ErrorHigh = "%(iexp),my_array3
     print ""
     print "fitRes_Exp%s_ErrorLow = "%(iexp),my_array4
     print ""
     normWsyst={}
     states= ['0S', '0pa', 'paS', 'pape', '0pe', 'SS', 'papa', 'pepe', '00', 'peS']
     for state in states:
         for charge in ["pos_","neg_"]:
             for i in range(len(KpiBins)-1):
                  
                 name= "w_"+state+"Bd2011_"+charge+"_" + str(KpiBins[i]) +  "_" + str(KpiBins[i+1])
                 w= argList.getRealValue(name)
                 normWsyst.update({name:w})
     print "normWsyst_Exp%s = "%(iexp),normWsyst
     if doSyst: 
         for par in range( 0, fitres_bins.floatParsFinal().getSize() ): #loop on the parameters
             param = fitres_bins.floatParsFinal().at(par)
             diffWithNominal.update({param.GetName():nominal_fit[param.GetName()]-my_array[param.GetName()]})
         print "diffWithNominal_Exp%s= "%(iexp),diffWithNominal
     print "###########################################"
     for par in range( 0, fitres_bins.floatParsFinal().getSize() ): #loop on the parameters
         param = fitres_bins.floatParsFinal().at(par)
         diffWithNominal.update({param.GetName():nominal_fit[param.GetName()]-my_array[param.GetName()]})
       #  print "$",param.GetName(),"$ && ",nominal_fit[param.GetName()]-my_array[param.GetName()],"\\\ "
    
     return fitres_bins, Master, w, mbc, argList



if YEAR == 1112 or YEAR == 1211: my_res = runFit(numCPU = nCPUs, minos = _MINOS_)
if YEAR == 2011: my_res = runFit(numCPU = nCPUs, dataset = "11", minos = _MINOS_)
if YEAR == 2012: my_res = runFit(numCPU = nCPUs, dataset = "12", minos = _MINOS_)

