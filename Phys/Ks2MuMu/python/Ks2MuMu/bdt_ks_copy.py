#! /usr/bin/env python
import sys, os
from Gaudi.Configuration import NTupleSvc
from Configurables import GaudiSequencer, DaVinci, L0Conf, SelDSTWriter, FilterDesktop

from BenderAlgo.BenderV0 import *
from BenderAlgo.BenderBuJPsiK import *
from BenderAlgo.BenderBdJPsiKst import *
from BenderAlgo.BenderBsJPsiPhi import *
from BenderAlgo.extrafunctions import *
from SomeUtils.TMVAoperators import *

#bdt_for_A = TMVAoperator("~/vol5/ks/weightsTOS_for_A/TMVAClassification_BDTD.class.C","BDTDTOSA", ["Bips_r", "DOCA","lessIPSmu", "Blife_ps_r","Vchi2","Bpt", "mv_Offline", "C_angle" ])#

#bdt_for_B = TMVAoperator("~/vol5/ks/weightsTOS_for_B/TMVAClassification_BDTD.class.C","BDTDTOSB", ["Bips_r", "DOCA","lessIPSmu", "Blife_ps_r","Vchi2","Bpt", "mv_Offline", "C_angle" ])
#bdt_for_A = TMVAoperator("~/vol5/ks/weightsA/TMVAClassification_BDTDA_TIS.class.C","BDTDA", ["Bips_r", "DOCA","lessIPSmu", "Blife_ps_r","Vchi2","SV1","SV2","SV3", "C_angle" ])
bdt_for_B = TMVAoperator("~/vol5/ks/weightsB/TMVAClassification_BDTDB_TIS.class.C","BDTDB", ["Bips_r", "DOCA","lessIPSmu", "Blife_ps_r","Vchi2","SV1","SV2","SV3", "C_angle" ])
#fA = Tfkspipi_ntuple_251111_1000pb_sampleA.root
from ROOT import *
import sys
sys.path.append(os.environ["HOME"] + "/cmtuser/Erasmus_v6r0/Phys/Bs2MuMu/python/Bs2MuMu/")
from RTuple import *
from fiducial import *
## f = TFile("KsPiPi_MC11_ntuples.root")
## #t.Draw("sqrt(mc_ks_px^2 + mc_ks_py^2)>>hppt")
## #str_match

## f2 = TFile("KsMuMu_MC11_ntuples.root")
## tmm = f2.Get("Ksmumu")
## t = f.Get("Kspipi")
## ## fpipiA = TFile("kspipi_
#ntuple_251111_1000pb_sampleA.root")
## tpA = fpipiA.Get("Ks2pipi")
## fpipiB = TFile("kspipi_ntuple_251111_1000pb_sampleB.root")
## tpB = fpipiB.Get("Ks2pipi")

## fmmA = TFile("ksmumu_ntuple_251111_1000pb_sampleA.root")
## tmA = fmmA.Get("Ks2mumu")
## fmmB = TFile("ksmumu_ntuple_251111_1000pb_sampleB.root")
## tmB = fmmB.Get("Ks2mumu")



## fmc1 = TFile("kspipimc11.root")
## tmc1 = fmc1.Get("T")#Kspipi")
## fmcmm = TFile("ksmumumc11.root")
## tmcmm = fmcmm.Get("T")#Ksmumu")
## fmc2 = TFile("kspipimc10.root")
## tmc2 = fmc2.Get("T")#Kspipi")

def addMVAs(tree,outputfile, bdt,  bdtname = "BDTwrong", doshit = 0):
    names = []
    labels = []
    #debug = int(debug)
    a = tree.GetListOfBranches()
    for branch in a:
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")
    
    #ls = ["life_ps/F","lessIPSmu/F","Bip/F","DOCA/F","life/F"]
    ls = []
        
 
    ls.append(bdtname + "/F")
    if doshit: ls.append("BDTDTOSB/F")
    #ls.append(glname + "/F")
    
    for l in ls:
        if l not in labels: labels.append(l)
    tup = RTuple(outputfile,labels)
    
    rangeN = range(tree.GetEntries())
    #rdr = {"DOCA":-1.,"lessIPSmu":-1.,"mu1iso":-1.,"mu2iso":-1., "Bip":-1., "life":-1.}
    for i in rangeN:
        if not i%10000: print i*100./tree.GetEntries(), "percent complete"
        
        tree.GetEntry(i)
        if doshit: tup.fillItem("BDTDTOSB", tree.BDTDDTOSB)
        for name in names:
            tup.fillItem(name,getattr(tree,name))
        rdr = {}
        #rdr["minpt"] = min(tree.mu1pt,tree.mu2pt)
       #rdr["isoSum"] = tree.mu1iso5 + tree.mu2iso5
        
        #for k in glkeys:
         #   if k == "minpt": continue
          #  if k == "isoSum": continue
           # rdr[k] = getattr(tree,k)
        
        tup.fillItem(bdtname,bdt(tree))
        #out = gl(rdr)
        #for ki in out.keys():
        #tup.fillItem(glname,out["sb"])
       
        tup.fill()
        
    tup.close()



#os.system("cp kspipi_misid11.root kspipi_misid11b.root")
#os.system("cp kspipimc11.root kspipimc11b.root")
#os.system("cp ksmmmc11.root kmmmc11b.root")

## f1 = TFile('kspipi_misid11b.root')
## t1 = f1.Get("T")
## f2 = TFile('kspipimc11b.root')
## t2 = f2.Get("T")
## f3 = TFile('kmmmc11b.root')
## t3 = f3.Get("T")
f1 = TFile("MM_B_unblind_2b.root")
t1 = f1.Get("T")
#f1 = TFile("~/vol5/ks/IdontKnowWhatIsThis_dcfc.root")#"KsPiPiMinBias_dcfc_MC10_trig11.root")#KsPiMuNu_MC11_ntuples.root')
f2 = TFile("PiPi_B_unblind_2b.root")
           
t2 = f2.Get("T")
addMVAs(t1,"~/vol5/ks/MM_B_unblind",bdt_for_B, "BDTDB", doshit=1)
addMVAs(t2,"~/vol5/ks/PiPi_B_unblind",bdt_for_B, "BDTDB")
#addMVAs(t3,"~/vol5/ks/ksmmmc11",bdt_for_B, "BDTDB")


