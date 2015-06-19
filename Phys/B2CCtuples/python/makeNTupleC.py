from ROOT import *
from os import system as shell, environ
from Urania import *
AccessPackage("Bs2MuMu")
from merger import *
from smartpyROOT import *
from Urania import PDG
from sWeightsIpatia import *
from Bs2JpsiPhiParams.Selections import KKbins#, trig_biased, trig_unbiased
from Bs2JpsiPhiParams import peaking as Dianne
from scipy import random as rnd

## Hack triggers
trig_biased = '(hlt1_excl_biased_dec==1 && (hlt2_biased==1 || hlt2_unbiased==1))'
trig_unbiased = '(hlt1_unbiased_dec==1 && (hlt2_biased==1 || hlt2_unbiased==1))'
tempf = "/tmp/" + user + "/"
shell("mkdir " + tempf)
from os import system
system("rm nTupleC*")
gROOT.ProcessLine(\
    "struct runPeriod{\
     Int_t year;\
    };")

gROOT.ProcessLine(\
    "struct tagginghack{\
     Double_t tagomega_ss;\
     Double_t tagomega_os;\
     Int_t tagdecision_ss;\
     Int_t tagdecision_os;\
    };")

MC_ADD_YEAR = 1
#MC_HACK_TAG = 1
PHYS_RW = 0

def addYear(name1, name2,treename, year):
    f = TFile(name1)
    t = f.Get(treename)
    f2 = TFile(name2,"recreate")
    t2 = t.CopyTree("1")
    value = runPeriod()
    branch = t2.Branch("runPeriod",AddressOf(value,"year"), "runPeriod/I")
    for i in range(t.GetEntries()):
        value.year = year
        branch.Fill()
        #print i, t.GetEntries()
    #print t.GetEntries()
    t2.Write("",TObject.kOverwrite)
    f2.Close()
def hackTag(name1, name2,treename):
    f = TFile(name1)
    t = f.Get(treename)
    f2 = TFile(name2,"recreate")
    t2 = t.CopyTree("1")
    value = tagginghack()
    branch_omega_ss = t2.Branch("tagomega_ss_nn",AddressOf(value,"tagomega_ss"), "tagomega_ss_nn/D")
    branch_omega_os = t2.Branch("tagomega_os_cb",AddressOf(value,"tagomega_os"), "tagomega_os_cb/D")
    branch_dec_ss = t2.Branch("tagdecision_ss_nn",AddressOf(value,"tagdecision_ss"), "tagdecision_ss_nn/I")
    branch_dec_os = t2.Branch("tagdecision_os_cb",AddressOf(value,"tagdecision_os"), "tagdecision_os_cb/I")
  
    for i in range(t.GetEntries()):
        t.GetEntry(i)
        value.tagomega_ss = t.tagomega_ss
        value.tagomega_os = t.tagomega_os
        value.tagdecision_ss = t.tagdecision_ss
        value.tagdecision_os = t.tagdecision_os
        #if rnd.random()> 0.5: value.tagdecision_ss = -1 #t.tagdecision_ss
        #else: value.tagdecision_ss = 1
       
        branch_omega_ss.Fill(), branch_omega_os.Fill(), branch_dec_ss.Fill(), branch_dec_os.Fill()
    t2.Write("",TObject.kOverwrite)
    f2.Close()

#datatuple = "/afs/cern.ch/user/d/diegoms/vol5/BsJpsiPhi/Data//fitNTuple_2011_2012_Reco14_20131112.root" ### Update!!

datatuple = "/afs/cern.ch/user/j/jleerdam/public/Bs2JpsiPhi_2011_2012_s20_dv33r6p1_20131217_tupleB_selTrig.root"
#"/afs/cern.ch/user/o/ooleroy/data/Bs2JpsiPhi_2012_s20r0p1_dv33r6p1_20131211_NoTagCalib_tupleB.root"


## Redefine the MC tuples to be those containing mc matched events
Bdtuple11 = "Bd11_for_tupleC.root"
Lbtuple11 = "Lb11_for_tupleC.root"
Bdtuple12 = "Bd12_for_tupleC.root"
Lbtuple12 = "Lb12_for_tupleC.root"

## if MC_HACK_TAG:
##     Bdtuple11_new = tempf + "Bdtuple11_hackTag"
##     hackTag(Bdtuple11, Bdtuple11_new,"DecayTree")
##     Bdtuple11 = Bdtuple11_new
##     Bdtuple12_new = tempf + "Bdtuple12_hackTag"
##     hackTag(Bdtuple12, Bdtuple12_new,"DecayTree")
##     Bdtuple12 = Bdtuple12_new
##     Lbtuple11_new = tempf + "Lbtuple11_hackTag"
##     hackTag(Lbtuple11, Lbtuple11_new,"DecayTree")
##     Lbtuple11 = Lbtuple11_new
##     Lbtuple12_new = tempf + "Lbtuple12_hackTag"
##     hackTag(Lbtuple12, Lbtuple12_new,"DecayTree")
##     Lbtuple12 = Lbtuple12_new

if MC_ADD_YEAR:
    Bdtuple11_new = tempf + "Bdtuple11_runPeriod"
    addYear(Bdtuple11,Bdtuple11_new,"DecayTree",2011)
    Bdtuple11 = Bdtuple11_new
    Bdtuple12_new = tempf + "Bdtuple12_runPeriod"
    addYear(Bdtuple12,Bdtuple12_new,"DecayTree",2012)
    Bdtuple12 = Bdtuple12_new
    Lbtuple11_new = tempf + "Lbtuple11_runPeriod"
    addYear(Lbtuple11,Lbtuple11_new,"DecayTree",2011)
    Lbtuple11 = Lbtuple11_new
    Lbtuple12_new = tempf + "Lbtuple12_runPeriod"
    addYear(Lbtuple12,Lbtuple12_new,"DecayTree",2012)
    Lbtuple12 = Lbtuple12_new
    
mcfolder ="DecayTree"#/DecayTree"    
qf = TFile(Bdtuple11)
tqf = qf.Get(mcfolder)
wBd11 = -(Dianne.Bd11 +0.0*Dianne.Bd11Err)  *1./tqf.GetEntries() ## Can also be a formula!
qf = TFile(Lbtuple11)
tqf = qf.Get(mcfolder)
wLb11 = -(Dianne.Lb11 + 0.0*Dianne.Lb11Err) *1./tqf.GetEntries()  ## Can also be a formula!

qf = TFile(Bdtuple12)
tqf = qf.Get(mcfolder)
wBd12 = -(Dianne.Bd12 + 0.0*Dianne.Bd12Err) * 1./tqf.GetEntries() ## Can also be a formula!
qf = TFile(Lbtuple12)
tqf = qf.Get(mcfolder)
wLb12 = -(Dianne.Lb12 + 0.0*Dianne.Lb12Err) * 1./tqf.GetEntries()  ## Can also be a formula!

############################
# PHASE SPACE REWEIGHTING ##
############################

if PHYS_RW:
    wBd11 = str(wBd11) + "*wphys"
    wBd12 = str(wBd12) + "*wphys"
    wLb11 = str(wLb11) + "*wphys"
    wLb12 = str(wLb12) + "*wphys"

#BREAK


shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + Bdtuple11 + " " + mcfolder + " " + str(wBd11) +  " wMC " + tempf + "Bd11.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + Lbtuple11 + " " + mcfolder + " " + str(wLb11) +  " wMC " + tempf + "Lb11.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + Bdtuple12 + " " + mcfolder + " " + str(wBd12) +  " wMC " + tempf + "Bd12.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + Lbtuple12 + " " + mcfolder + " " + str(wLb12) +  " wMC " + tempf + "Lb12.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + datatuple  + " DecayTree " + str(1.0) +  " wMC " + tempf + "deita.root")


mergeSamples(["Bd11","Bd12","Lb11","Lb12","deita"],"nTuple_temp", tempf,["DecayTree/DecayTree"],"./")
#mergeSamples(["deita","deita"],"nTuple_temp", tempf,["DecayTree/DecayTree"],"./")
t,f = getTuple("nTuple_temp_merged",thing = "DecayTree")
#BREAK
fs = {}
ts = {}
aa = "&&"
params = CBparams_smeared_noMatch
samples = []
NKK = len(KKbins)
yvar = "runPeriod" ## change to runPeriod if needed
for i in range(NKK):
    name = "nTupleC_biased11" + str(i)
    samples.append(name)
    fs[i] = TFile(name + ".root","recreate")
    ts[i] = t.CopyTree(KKbins[i] + aa+ trig_biased + aa + "(" + yvar + "==2011)")
    op = doMassFit(ts[i],getattr(params,"BiasedBin" + str(i)),"wMC")
    b = sWeighter("ipatia",op)
    fs[i].Close()
    name = "nTupleC_unbiased11" + str(i)
    samples.append(name)
   
    fs[i + NKK] = TFile(name + ".root","recreate")
    ts[i + NKK] = t.CopyTree(KKbins[i] + aa+ trig_unbiased  + aa + "(" + yvar + "==2011)")
    op = doMassFit(ts[i + NKK],getattr(params,"UnbiasedBin" + str(i)),"wMC")
    b = sWeighter("ipatia",op)
    fs[i + NKK].Close()
    
    name = "nTupleC_biased12" + str(i)
    samples.append(name)
   
    fs[i + 2*NKK] = TFile(name + ".root","recreate")
    ts[i + 2*NKK] = t.CopyTree(KKbins[i] + aa+ trig_biased + aa + "(" + yvar + "==2012)")
    op = doMassFit(ts[i+2*NKK],getattr(params,"BiasedBin" + str(i)),"wMC")
    b = sWeighter("ipatia",op)
    fs[i + 2*NKK].Close()
    name = "nTupleC_unbiased12" + str(i)
    samples.append(name)
   
    fs[i + 3*NKK] = TFile(name + ".root","recreate")
    ts[i + 3*NKK] = t.CopyTree(KKbins[i] + aa+ trig_unbiased  + aa + "(" + yvar + "==2012)")
    op = doMassFit(ts[i + 3*NKK],getattr(params,"UnbiasedBin" + str(i)),"wMC")
    b = sWeighter("ipatia",op)
    fs[i + 3*NKK].Close()

mergeSamples(samples,"nTupleC", "./",["DecayTree"],"./")
