from ROOT import *
from array import array as afC
from SomeUtils.alyabar import *
from fiducial import *
import histoTex as M
import KsmmMathCrap as K
import cPickle
import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from triggerclass import *
mK0 = 497.614
BDTNAME = "BDTDB"
MISID = 1
ptbins = afC('d', [150,650,1000,2500])
ybins = afC('d' , [2,2.5,3,3.5,4, 4.5])

#ptbins = afC('d', [0,150,650,1000,2500,4000])
#ybins = afC('d' , [0,2,2.5,3,3.5,4, 4.5,7])

def isPromptish(t): return abs(t.mc_myv_z) <100 and abs(t.mc_myv_x)<.05 and abs(t.mc_myv_y)<.05
isPrompt = isPromptish
epsTOS = cPickle.load(file("eps_TOS"))
epsTIS = cPickle.load(file("eps_TIS"))
if "TOS" in BDTNAME:
    eps = epsTOS
    fiducial = fiducialtos
else: eps = epsTIS

###########################
##                       ##
## Deita Min Bias NTuple ##
##                       ##
###########################

fmb = TFile("minbias.root")
tmb2 = fmb.Get("T")

#################
##             ##
##  MC NTuples ##
##             ##
#################

if MISID:
    fpipiMCT = TFile("KsPiPi_MC11_tisstudies_ntuples.root")
    fpipi = TFile("~/vol5/ks/kspipi_misid11.root")
else: 
    fpipiMCT = TFile("KsPiPi_MC11_ntuples.root")
    fpipi = TFile("~/vol5/ks/kspipimc11.root")
fmumuMCT = TFile("KsMuMu_MC11_ntuples.root")
fmumu = TFile("~/vol5/ks/ksmmmc11.root")

tpipiMCT = fpipiMCT.Get("Kspipi_mct")
tmumuMCT = fmumuMCT.Get("Ksmumu_mct")
#tpipiR = fpipiMCT.Get("Kspipi")
tmumu2 = fmumu.Get("T")
tpipi2 = fpipi.Get("T")

va = ["mv_Offline", "evt", "Bmass","Bips_r", "DOCA","lessIPSmu", "Blife_ps_r","Vchi2","SV1","SV2","SV3", "C_angle" , "Bpt", "mu1p1","mu1p2","mu1p3","mu2p1","mu2p2","mu2p3"]#, "PVchi2","longTracks"]
P = channelData("~/vol5/pipi_plots",labels = va)#,name2 = "Kspipi")
M = channelData("~/vol5/mm_plots",labels = va)#name2 = "Ksmumu")

def addOp(ch):
    ch.addVariable("mu1pVec",["mu1p1","mu1p2","mu1p3"], vector)
    ch.addVariable("mu2pVec",["mu2p1","mu2p2","mu2p3"], vector)
    ch.addVariable("op_angle",["mu1pVec","mu2pVec"], ACO)
    return 1

addOp(P)
addOp(M)
