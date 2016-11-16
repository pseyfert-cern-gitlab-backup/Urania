from SomeUtils.TMVAoperators import *
import os
from ROOT import Double


yury = TMVAoperatorFlat(os.environ["BS2MUMUROOT"] + "/operators/Y9.C","BDTD",["LF_time", "lessIPSmu", "isoSum", "Bpt", "yet_another_CDF_iso", "minpt", "Cosnk", "DOCA", "Bip_r" ], os.environ["BS2MUMUROOT"] +"/operators/Y9_U")
#y6 = TMVAoperatorFlat(os.environ["BS2MUMUROOT"] +"/operators/Y6_2iso.C","BDTG",["Bip_r","DOCA","lessIPSmu","Blife_ps_r","Bpt","mu1iso5","mu2iso5", "Cosnk"], os.environ["BS2MUMUROOT"] +"/operators/Y6_2iso_U")
#gl = cPickle.load(file(os.environ["BS2MUMUROOT"] +"/operators/GL_2011_r"))

bdts = TMVAoperator(os.environ["BS2MUMUROOT"] + "/operators/TMVAClassification_BDTS_ROOT5_30.class.C","BDTS",["Bips_r", "DOCA", "JPsiChi2", "DIRA", "Bip_r", "minIPdaug"])


def addTMVAs(algo, CandidateInfo,Done):
    CandidateInfo["isoSum"] = CandidateInfo["mu1iso5"] + CandidateInfo["mu2iso5"]
    CandidateInfo["minpt"] =  min(CandidateInfo["mu1pt"],CandidateInfo["mu2pt"])
    CandidateInfo["BDTflat"] = yury(CandidateInfo)
    #CandidateInfo["BDTGsimp"] = y6(CandidateInfo)
    #out = gl(CandidateInfo)
    #f#or key in out.keys():
     #   CandidateInfo["GL11" + key] = out[key]
    
def addBDTS(algo, CandidateInfo,Done):
    CandidateInfo["minIPdaug"] = min(CandidateInfo["mu1mip"],CandidateInfo["mu2mip"])
    CandidateInfo["BDTS"] = bdts(CandidateInfo)
   


def addBDTS_cx(algo, CandidateInfo, Done):
     """get BDT from particle"""

     b = Done["Candidate"]
     res = Double(0)
     sc=algo.BDTSTool.getBDTVal(b,res)
     if sc.isFailure():
         CandidateInfo["BDTS_cx"] = 0.
         return 1
     CandidateInfo["BDTS_cx"] = float(res)
     return 1
