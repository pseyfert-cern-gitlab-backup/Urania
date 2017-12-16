'''
from ROOT import *
from os import *
import getSelEff as E
E.getBsmmEff()
'''

from ROOT import *
from os import *


mBs = 5366.3
mBu = 5279.17
mBd = 5279.5
mJPsi = 3096.916
mPhi = 1019.455
mTau = 1776.8 
mDs = 1968.47



def getTauEff_s17():
    
    #filename = "~/NTuples/tau23mu/v3_MC10_tau23mu_allNoPIDs_TCK0x00760037_mcTruth_mud_sm0_nEvt10000_flat.root"
    #filename = "~/NTuples/tau23mu/v3_MC10_tau23mu_allNoPIDs_TCK0x00760037_mcTruth_mud_sm1_nEvt10000_flat.root"
    filename = "~/NTuples/tau23mu/v3_MC10_tau23mu_allNoPIDs_TCK0x00760037_mcTruth_mud_sm1.5_nEvt10000_flat.root"


    fsm = TFile(filename)
    print ""
    print "sel eff, use file: ",filename  
    print ""
    fsm.ls()
    tsm= fsm.Get("Tau23Mu")
    

    nTot=1.*tsm.GetEntries()
    print "nTot: ",nTot
    cut="1"
   
    new="&&p0_isMuon&&p1_isMuon&&p2_isMuon"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&p0_track_Chi2Dof<4&&p1_track_Chi2Dof<4&&p2_track_Chi2Dof<4"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
    new="&&p0_IPSig>3&&p1_IPSig>3&&p2_IPSig>3"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&p0_pt>300&&p1_pt>300&&p2_pt>300"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
    new="&&VertexChi2<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&LifeTime*299792458e-3>100"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&IPSig<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
  
    new="&&BPVLTIME225"
    cut=cut#+new
    n=1.*tsm.GetEntries(cut)    
    print ""
    print new+" VARIABLE IS MISSING"#, " efficiency : ",n/nTot
    print

    new="&&fabs(1777-mass)<50"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
    e1=n/nTot
    new="&&fabs(1019.455-mass_p1p2)>20&&fabs(1019.455-mass_p0p2)>20&&mass_p1p2>250"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot  
    e2=n/nTot
  
    print ""
    print ""
    print "full cut strin used: ",cut

    return



def getDsPhiPiEff_s17():
    
    #filename = "~/NTuples/tau23mu/v3_MC10_DsPhiPi_allNoPIDs_TCK0x00760037_mcTruth_mud_sm0_nEvt10000_flat.root"
    #filename = "~/NTuples/tau23mu/v3_MC10_DsPhiPi_allNoPIDs_TCK0x00760037_mcTruth_mud_sm1_nEvt10000_flat.root"
    filename = "~/NTuples/tau23mu/v3_MC10_DsPhiPi_allNoPIDs_TCK0x00760037_mcTruth_mud_sm1.5_nEvt10000_flat.root"


    fsm = TFile(filename)
    print ""
    print "sel eff, use file: ",filename  
    print ""
    #tsm = fsm.Get("StrippingTau23MuTau23MuLine")
    #tsm = fsm.Get("flat_ntuple")
    fsm.ls()
    #tsm= fsm.Get("flatStrippingTau23MuDs2PhiPiLine")
    tsm= fsm.Get("Ds2PhiPi")
    

    nTot=1.*tsm.GetEntries()
    print "nTot: ",nTot
    cut="1"
   
    new="&&p1_isMuon&&p2_isMuon"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&p0_track_Chi2Dof<4&&p1_track_Chi2Dof<4&&p2_track_Chi2Dof<4"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
    new="&&p0_IPSig>3&&p1_IPSig>3&&p2_IPSig>3"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&p0_pt>300&&p1_pt>300&&p2_pt>300"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
    new="&&VertexChi2<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&LifeTime*299792458e-3>100"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&IPSig<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
  
    new="&&BPVLTIME225"
    cut=cut#+new
    n=1.*tsm.GetEntries(cut)    
    print ""
    print new+" VARIABLE IS MISSING"#, " efficiency : ",n/nTot
    print

    new="&&fabs(1968.47-mass)<50"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
    e1=n/nTot
    new="&&fabs(1019.455-mass_p1p2)<20"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot  
    e2=n/nTot
  
    print ""
    print ""
    print "full cut strin used: ",cut

    return

'''
def getDsPhiPiEff_s15s17():
    
    filename = "v2a_Ds2PhiPi_md_mctruth.root"
    fsm = TFile(filename)
    print ""
    print "sel eff, use file: ",filename  
    print ""
    tsm = fsm.Get("flat_ntuple")

    nTot=1.*tsm.GetEntries()
    print "nTot: ",nTot

    new="erstIsMuon&&firstIsMuon"#&&secondIsMuon"
    cut=new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&minMuPT>300"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&pt>2000"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&erstrealtrackchi2<4&&firstrealtrackchi2<4&&secondrealtrackchi2<4"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&firstIPSig>3.464&&secondIPSig>3.464&&thirdIPSig>3.464"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&VertexChi<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&ctau>100"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&IPSig<3"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
  
    
    new="&&fabs(1968.47-mass)<50"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    
   
    e1=n/nTot
    new="&&fabs(1019.455-mumu3)<20"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    

    e2=n/nTot
    
    
    print "phi cut eff: ",e2/e1


    return



def getTrgDec():

    filename = "~/tauNT/MCdsphiboth_tauANDcalib_D0_290_291_flat_v0.root"
#    filename = "v2a_tau23mu_md_mctruth.root"
    fsm = TFile(filename)
    print ""
    print "sel eff, use file: ",filename  
    print ""
    tsm = fsm.Get("flat_ntuple")

    nTot=1.*tsm.GetEntries()
    print "nTot: ",nTot
    
    cut="1"
    nsel=1.*tsm.GetEntries(cut)    
    new="&&L0Dec"
    cut=cut+new
    nl0=1.*tsm.GetEntries(cut)    
    
    
    print "L0 eff: ",nl0/nsel
    
    
    new="&&Hlt1Dec"
    cut=cut+new
    nhlt1=1.*tsm.GetEntries(cut) 
    print "Hlt1 eff: ",nhlt1/nl0

    new="&&Hlt2Dec"
    cut=cut+new
    nhlt2=1.*tsm.GetEntries(cut) 
    print "Hlt2 eff: ",nhlt2/nhlt1

    print "total trg eff",nhlt2/nsel


def getTauEff_s17():
    
    #filename = "v1_MC10_tau23mu_mcTruth_md_10k_flat.root"
    filename = "v2a_tau23mu_md_mctruth.root"
    fsm = TFile(filename)
    print ""
    print "sel eff, use file: ",filename  
    print ""
    tsm = fsm.Get("flat_ntuple")

    nTot=1.*tsm.GetEntries()
    print "nTot: ",nTot

    cut="erstIsMuon&&firstIsMuon&&secondIsMuon"
    n=1.*tsm.GetEntries(cut)    
    print cut, " efficiency : ",n/nTot

    cut="minMuPT>300"
    n=1.*tsm.GetEntries(cut)    
    print cut, " efficiency : ",n/nTot

    new="&&erstrealtrackchi2<4&&firstrealtrackchi2<4&&secondrealtrackchi2<4"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&firstIPSig>3&&secondIPSig>3&&thirdIPSig>3"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&VertexChi<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&ctau>100"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&IPSig<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&fabs(1776.8-mass)<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    e1=n/nTot

    mCut=20
    
    #new="&&fabs(1019.455-mumu1)>20&&fabs(1019.455-mumu3)>20"
    new="&&mumu2>250"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot
    

    e2=n/nTot
    print "phi cut eff: ",e2/e1

    return

def getTauEff_s15s17():
    
    #filename = "v1_MC10_tau23mu_mcTruth_md_10k_flat.root"
    filename = "v2a_tau23mu_md_mctruth.root"
    fsm = TFile(filename)
    print ""
    print "sel eff, use file: ",filename  
    print ""
    tsm = fsm.Get("flat_ntuple")

    nTot=1.*tsm.GetEntries()
    print "nTot: ",nTot

    cut="erstIsMuon&&firstIsMuon&&secondIsMuon"
    n=1.*tsm.GetEntries(cut)    
    print cut, " efficiency : ",n/nTot

    cut=cut+"&&minMuPT>300"
    n=1.*tsm.GetEntries(cut)    
    print cut, " efficiency : ",n/nTot

    new="&&maxMuPT>1000"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&erstrealtrackchi2<4&&firstrealtrackchi2<4&&secondrealtrackchi2<4"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&firstIPSig>3&&secondIPSig>3&&thirdIPSig>3"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&VertexChi<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&ctau>100"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&IPSig<15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&fabs(1776.8-mass)<25"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&fabs(1019.455-mumu1)>15&&fabs(1019.455-mumu3)>15"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    new="&&mumu2>250"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    
    print new, " efficiency : ",n/nTot

    esel=n/nTot
    new="&&L0Dec"
    cut=cut+new
    n=1.*tsm.GetEntries(cut)    

    el0=n/nTot
    print "L0 eff: ",el0/esel

    
    new="&&Hlt1Decision&&Hlt2Decision"
    cut=cut+new
    n=1.*tsm.GetEntries(cut) 
    ehlt1=n/nTot
    print "Hlt1 eff: ",ehlt1/el0

    return

'''
