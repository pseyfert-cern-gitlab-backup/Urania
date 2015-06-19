#! /usr/bin/env python
import sys, os
from Gaudi.Configuration import NTupleSvc
from Configurables import GaudiSequencer, DaVinci, L0Conf, SelDSTWriter, FilterDesktop

bsmumuCounterKeys = ["MuMuCouplesAnalyzed","EVT", "weird"]

################################### Some General Options. Remember to check it

INTERACTIVE = 0

MC_INFO = 1
ONLY_MC = 1
DST = 0
TUP = 1
TRIGGER = 0
REDOTRIGGER = 0
DebugAlgos = 0
SMEARIP=1

N = 100000

Njobmax = 1.e10  ### info only, not real limit. Used to set an offset in the evt no. label


SIMULATION =  True
#VERSION = "sim07reco06"   ## Only makes sense if SIMULATION is 1
VERSION = "sim03reco03"


DataType = "2010"  ##### To pass to DV
print DataType, SIMULATION*"MONTE CARLO"

#########################
### ALGORITHMS TO ADD ###
#########################

__BHH = 1
__BsMuMu = 0
__BuJPsiK = 0
__BdJPsiKstar = 0
__Bs2JPsiPhi= 0


###########################
### FOR BATCH MODE ONLY ###
###########################
string = ""
args = sys.argv
for arg in args[1:]:
    if arg in ["-b","-b-"]: continue
    string += "_" + arg

N0 = string.replace("_","")
N0 = int(max(N0,"0"))
    
####################################
### Names for OUTPUT NTuple, Dst ###
####################################

#ntName="v2.2_Bu2JPsiX_smearTr_debugAlgs_1.5Smear"
ntName="_tmp"
TUPLE_FILE = os.environ["HOME"] + "/NTuples/bkpi0x002a002a_smeared" + SIMULATION*("MC" + VERSION) + string+".root"

#TUPLE_FILE = os.environ["HOME"] + "/NTuples/"+ntName+ "MC" + string+".root"
HISTO_FILE = os.environ["HOME"] + "/NTuples/"+ntName+ "MC" + "_H_"+ string+".root"


if TUP:
    
#    NTupleSvc( Output = [ 'T DATAFILE=\'castor:'+os.environ["CASTOR_HOME"]+"/muons/mb" + SIMULATION*"MC"+ string +'.root\' TYP=\'ROOT\' OPT=\'NEW\'' ]) ## To save the NTuple in Castor (a la Elias)
    NTupleSvc( Output =["T DATAFILE='"+ TUPLE_FILE + "' TYP='ROOT' OPT='NEW'"] )


#################
### DATACARDS ###
#################

#datacards = "$BSMUMUPYROOT/data/data2010/MagDown/Stripping07_DIMUONDST_July21" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/data2010/MagUp/Stripping07_DIMUONDST_July30" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/MC/BsMuMu3dot5TeV" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/MC/Bd3dot5" + string + ".py"

#datacards = "$BSMUMUPYROOT/data/MC/MCBuJPsiX_Sim03Reco03_hopefully" + string + ".py"
#datacards = "/afs/cern.ch/user/d/diegoms/cmtuser/data/MC2010/minbias_DiMuon_DST" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/data2010/data_600pb" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/MC/MCBKpi_2010_428935_2010-Sim03Reco03-withTruth_11102003__DST" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/data2010/data_other087" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/data2010/MagUp//MagUp_stp10_Oct18" + string + ".py"
#datacards = "$BSMUMUPYROOT/data/data2010/stripped_stp09" + string + ".py"

#datacards = "$BSMUMUPYROOT/data/MC/MCBsmumu_2010_428935_2010-Sim07Reco06-withTruth_13112001__DST.py"

#datacards = "$BSMUMUPYROOT/data/MC/mc_2010_sim3rec3_down_bjpsiX.opts"


#datacards = "$BSMUMUPYROOT/data/MC/bskpi_sim7reco6_0x002b002a.opts"
#datacards = "$BSMUMUPYROOT/data/MC/MC2010_Bs2JPsiPhi_sim03reco03_00007386_300k.py"
#datacards = "$BSMUMUPYROOT/data/data2010/MagUp_stp10_Oct21_F0_albrecht68_subs" + string + ".py"

#datacards = "$BSMUMUPYROOT/data/MC/MCBuJPsiX_2010_428935_2010-Sim03Reco03-withTruth_11442001__DST.py"

#datacards = "$BSMUMUPYROOT/data/MC/MCBuJPsiX_Sim03Reco03_hopefully.py"
#datacards = "$BSMUMUPYROOT/data/MC/Bu3dot5.py"

#datacards = "$BSMUMUPYROOT/data/MC/McStripped/mc_2010_sim3rec3_bjpsiX_down_nu1_stripped_0x002b002a_pfn.opts"

datacards = "$BSMUMUPYROOT/data/MC/stp_MC/0x002a002a/mc_2010_sim3rec3_bkpi_nu1_stripped_0x002a002a_pfn.opts"

from BsMuMuPy.algorithms.BenderB2QQ_dbg_sm import *
#from BsMuMuPy.algorithms.BenderBuJPsiK_dbg_sm import *
#from BsMuMuPy.algorithms.BenderBdJPsiKst_dbg_sm import *
#from BsMuMuPy.algorithms.BenderBsJPsiPhi_dbg import *
from BsMuMuPy.algorithms.extrafunctions import *

from ROOT import *

import GaudiPython
import Gaudi
from Gaudi.Configuration import *

#these tags are on the data
#tags = {"sim01reco01":['head-20100119','sim-20100222-vc-md100'],"sim03reco03":['head-20100407','sim-20100429-vc-mu100'],"sim07reco06":['head-20100624','sim-20100715-vc-md100']}

#using new reco, we need to use these tags
tags = {"sim01reco01":['head-20100624','sim-20100831-vc-md100'],"sim03reco03":['head-20100624','sim-20100831-vc-md100'],"sim07reco06":['head-20101003','sim-20100831-vc-md100']}

#JA
#tags = {"mc09":['MC09-20090602','MC09-20100921-vc-md100'],"sim01reco01":['head-20100624','sim-20100831-vc-md100'],"sim03reco03":['head-20100624','sim-20100831-vc-md100'],"sim07reco06":['head-20101003','sim-20100831-vc-md100']}
def configure():
    
    ################### IMPORTING OPTIONS

    DaVinci().EvtMax = 0    
    DaVinci().DataType = DataType 
    DaVinci().Simulation = SIMULATION
    DaVinci().L0 = bool(TRIGGER)

    DaVinci().UserAlgorithms = []
    DaVinci().Hlt = bool(TRIGGER)
    DaVinci().HistogramFile = HISTO_FILE
    DaVinci().Lumi = False
    #DaVinci().InputType = "MDST"

    if REDOTRIGGER:
        from Configurables import L0Conf, HltConf
        #first, redo L0 and HLT
        DaVinci().L0 = True
        #DaVinci().Hlt = True
        DaVinci().ReplaceL0BanksWithEmulated=True
        #HltConf().ThresholdSettings = 'Physics_HighNu_80Vis_30L0_5Hlt1_CoreHlt2_Jun10'
        #HltConf().ThresholdSettings = 'Physics_HighNu_3000Vis_200L0_20Hlt1_CoreHlt2_Sep10'
        #check that this is consistent with the setting above
        L0Conf().TCK = '0x002a'
 	HltConf().ForceSingleL0Configuration = False

        #comment these in if you want candidate info at each stage
        #from Configurables import HltSelReportsMaker
        #HltSelReportsMaker().DebugEventPeriod=1
        #HltSelReportsMaker().MaxCandidatesNonDecision=500

        #JA 31/08/2010
        #this part is neededto prepare L0 info for the
        #"new" L0TisTosTool --> will be obsolete soon

        #from Configurables import L0Conf, HltConf
        #DaVinci().L0 = True
        #L0Conf().TCK = '0x0025'
        from Configurables import L0Conf
        L0Conf().IgnoreL0MuonCondDB = True
        from L0DU.L0Algs import emulateL0Muon
        l0muon = emulateL0Muon()
        l0muon.IgnoreCondDB = True
        l0muon.FoiXSize =[6,5,0,4,8]
        l0muon.FoiYSize =[0,0,0,1,1]
        l0muon.OutputLevel=2
    if TRIGGER:
        
        L0SelRepSeq = GaudiSequencer("L0SelRepSeq")
        L0SelRepSeq.MeasureTime = True
        from Configurables import L0SelReportsMaker, L0DecReportsMaker
        L0SelRepSeq.Members += [ L0DecReportsMaker(), L0SelReportsMaker() ]
        DaVinci().UserAlgorithms += [ L0SelRepSeq ]
    
    if SIMULATION:
        DaVinci().DDDBtag = tags[VERSION][0]
        DaVinci().CondDBtag = tags[VERSION][1]
        
    else: ## MagUp
         #from Configurables import CondDB
         #CondDB(UseOracle = True)
         DaVinci().DDDBtag = 'head-20101003'
         DaVinci().CondDBtag = 'head-20101003'

    
    importOptions("$STDOPTS/PreloadUnits.opts")

    if SMEARIP:
         #importOptions("$BSMUMUPYROOT/python/BsMuMuPy/pyUtils/MakeMyParticles.py")
                          
         import BsMuMuPy.pyDaVinci.MakeMyParticles as M
         M.makeMyProtoP("Best")
         #M.makeMyKaons("MyLooseKaons", "Best", "kaon")
         #M.makeMyMuons("MyLooseMuons", "Best", "muon")
         #M.makeMyParticles("MyLoosePions", "Best", "pion")
         #M.makeNoPIDParticles("MyNoPIDPions", "Best", "pion")
         #         M.makeNoPIDParticles("MyNoPIDMuons", "Best", "muon")
         #         M.makeNoPIDParticles("MyNoPIDKaons", "Best", "kaon")
         M.makeNoPIDMuons("MyNoPIDsMuons", "Best")
         M.makeNoPIDKaons("MyNoPIDsPions", "Best")
         #M.makeMyKaons("MyNoPIDsKaons", "Best", "kaon")
         #M.makeMyMuons("MyNoPIDsMuons", "Best", "muon")
 
         from Configurables import TrackSmeared
         TrackSmeared("BestTrackSmeared").xpar1_mc = 5.5
         TrackSmeared("BestTrackSmeared").xpar2_mc = 23.5
         TrackSmeared("BestTrackSmeared").xpar1_data = 7.9
         TrackSmeared("BestTrackSmeared").xpar2_data = 31.0
         TrackSmeared("BestTrackSmeared").ypar1_mc = 5.5
         TrackSmeared("BestTrackSmeared").ypar2_mc = 23.3
         TrackSmeared("BestTrackSmeared").ypar1_data = 8.1
         TrackSmeared("BestTrackSmeared").ypar2_data = 30.0
         TrackSmeared("BestTrackSmeared").smear = True
         TrackSmeared("BestTrackSmeared").Scale=1.

    
    
           
    if DST:
        from PhysSelPython.Wrappers import Selection, DataOnDemand, SelectionSequence
        bmm = FilterDesktop('bmm')
        bmm.Code = "ALL"

        MyBmm=DataOnDemand('/Event/Phys/PreselBs2MuMu')
        SelMyBmm=Selection('SelMyBmm',Algorithm=bmm, RequiredSelections = [MyBmm])
        SeqBmm = SelectionSequence('SeqBmm', TopSelection = SelMyBmm)

        dstWriter = SelDSTWriter("BmmDSTWriter",
                                 SelectionSequences = [SeqBmm],
                                 SaveCandidates = True,
                                 CopyMCTruth = SIMULATION,
                                 WriteFSR = True,
                                 OutputFileSuffix = "Test"
                                 )

        DaVinci().UserAlgorithms += [dstWriter.sequence()]



    importOptions(datacards)  ### Be sure you DO NOT import any other options file after this one. You can overwrite eventselector input.
    ################## END IMPORTING OPTIONS
    DaVinci().applyConf()   
    gaudi = appMgr()
        
    algos = []
    
    if __BsMuMu:
        alg = B2QQ('Bs2MuMu')
        alg.LookIn = "Phys/PreselBs2MuMu"
        alg.decayname = "Bs-->mumu"
        alg.COUNTER = {}
        alg.COUNTER["Bender(evts) " + alg.decayname] = 0
        alg.mcs = [531, 13,-13]
        alg.Sel_Above_GL = 0
        alg.extraFunctions = [trackHits, subdetectorDLLs, geoVarOld, more_muon_things]#, addGL]
        if SIMULATION*MC_INFO: alg.extraFunctions += [BQQMCtruth, mc_geometry]
        for key in bsmumuCounterKeys:
            alg.COUNTER[key] = 0
        algos.append(alg)
        gaudi.addAlgorithm(alg)
        #alg.InputLocations = ['/Event/Phys/StdNoPIDsMuons' ]  
        alg.InputLocations = ['/Event/Phys/MyNoPIDsMuons' ]

    if __BuJPsiK:
        bu = BuJPsiK("Bu2JPsiK")
        bu.COUNTER= {"EVT":0,"No Online Tracks":0, "No Linked Tracks":0, "Sel":0}
        bu.LookIn = "Phys/PreselBu2JPsiKCommon"
        bu.extraFunctions = [more_muon_things]
        algos.append(bu)
        gaudi.addAlgorithm(bu)
        bu.decayname = "B+ --> J/Psi K+"
        #bu.InputLocations = ['/Event/Phys/StdNoPIDsMuons', '/Event/Phys/StdNoPIDsKaons']
        bu.InputLocations = ['/Event/Phys/MyNoPIDsMuons', '/Event/Phys/MyNoPIDsKaons']
                                          
    if __BdJPsiKstar:
        bd = BdJPsiKstar("Bd2JPsiKstar")
        bd.COUNTER= {"EVT":0,"No Online Tracks":0, "No Linked Tracks":0, "Sel":0}
        bd.LookIn = "Phys/PreselBd2JPsiKstCommon"
        bd.extraFunctions = [more_muon_things,mc_geometry]
        algos.append(bd)
        gaudi.addAlgorithm(bd)
        bd.decayname = "B+ --> J/Psi K*"
        #bd.InputLocations = ['/Event/Phys/StdNoPIDsMuons', '/Event/Phys/StdNoPIDsKaons', '/Event/Phys/StdNoPIDsPions']
        bd.InputLocations = ['/Event/Phys/MyNoPIDsMuons', '/Event/Phys/MyNoPIDsKaons', '/Event/Phys/MyNoPIDsPions']


    if __Bs2JPsiPhi:
        bs = BsJPsiPhi("Bs2JPsiPhi")
        bs.COUNTER= {"EVT":0,"No Online Tracks":0, "No Linked Tracks":0, "Sel":0}
        bs.LookIn = "Phys/PreselBs2JPsiPhiCommon"
        bs.extraFunctions = [more_muon_things]
        algos.append(bs)
        gaudi.addAlgorithm(bs)
        bs.decayname = "Bs --> J/Psi Phi"
        bs.InputLocations = ['/Event/Phys/StdNoPIDsMuons', '/Event/Phys/StdNoPIDsKaons']
  

    if __BHH:
        bhh = B2QQ("B2hh")
        bhh.decayname = "B --> h+ h-"
        algos.append(bhh)
        bhh.COUNTER = {}
        bhh.COUNTER["Bender(evts) " + bhh.decayname] = 0
        bhh.LookIn = "Phys/PreselB2HH"
        bhh.Sel_Above_GL = 0
        bhh.mcs = [511,321,211]#,-321,-211]
        bhh.extraFunctions = [trackHits, subdetectorDLLs, geoVarOld, more_muon_things, addSomeGLs, globalEvtVars, massHypo]
        if SIMULATION: bhh.extraFunctions += [BQQMCtruth, mc_geometry]
       
        for key in bsmumuCounterKeys:
            bhh.COUNTER[key] = 0
        gaudi.addAlgorithm(bhh)
        #bhh.InputLocations = ['/Event/Phys/StdLooseMuons']  ## Muons needed for strudies of JPsi Veto.
        bhh.InputLocations = ['/Event/Phys/MyNoPIDsKaons' ,'/Event/Phys/MyLooseMuons','/Even/Phys/MyNoPIDsPions']
   
    

    gaudi.initialize()
    from BsMuMuPy.pyDaVinci import PIDcalTools
 
    ########################
    ##COMMON ATRIBUTES ####
    ######################
   
    for algo in algos:
        algo.MC_INFO = SIMULATION*MC_INFO
        algo.ONLY_MC = SIMULATION*ONLY_MC
        algo.TRIGGER = TRIGGER
        algo.PIDcalTools = PIDcalTools
        algo.NTupleLUN = "T"
        algo.addedKeys = []
        #algo.runinfo = runinfo
        algo.DST = DST
        algo.TUP = TUP
        algo.COUNTER['negSq'] = 0
        algo.COUNTER["weird"] = 0
        algo.DEBUG = DebugAlgos ### Do not define global DEBUG
       
        algo.evt_of = Njobmax*N0
        if TRIGGER:
            algo.tistostool = algo.tool( cpp.ITriggerTisTos , 'TriggerTisTos')
            algo.tisTosToolL0= algo.tool(cpp.ITriggerTisTos , 'L0TriggerTisTos')
            algo.extraFunctions.append(triggerBlock)
            
            algo.l0List = ['Muon', 'DiMuon','Hadron']
            algo.hlt1List = ['Hlt1SingleMuonIPCL0',
                             'Hlt1SingleMuonNoIPL0',
                             'Hlt1DiMuonIPC2L0',
                             'Hlt1DiMuonIPCL0Di',
                             'Hlt1DiMuonIPCL0Seg',
                             'Hlt1DiMuonNoIP2L0',
                             'Hlt1DiMuonNoIPL0Di',
                             'Hlt1DiMuonNoIPL0Seg',
                             'Hlt1MuTrack',
                             'Hlt1SingleHadron',
                             'Hlt1DiHadron',
                             'Hlt1SingleMuon4BsMuMu',
                             'Hlt1DiMuon4BsMuMu',
                             'Hlt1TrackAllL0',
                             'Hlt1TrackMuon',
                             'Hlt1TrackPhoton'
                             ]
 
            algo.hlt2List = ['Hlt2DiMuonUnbiasedBmm',
                             'Hlt2DiMuonUnbiasedJPsi',
                             'Hlt2MuTrack',
                             'Hlt2BiasedDiMuonIP',
                             'Hlt2BiasedDiMuonMass',
                             'Hlt2BiasedDiMuonRefined',
                             'Hlt2BiasedDiMuonSimple',
                             'Hlt2DiMuonSameSign',
                             'Hlt2UnbiasedDiMuon',
                             'Hlt2SingleMuon',
                             'Hlt2B2HH',
                             'Hlt2SingleHighPTMuon',
                             'Hlt2TopoOSTF2Body',
                             'Hlt2TopoOSTF3Body',
                             'Hlt2TopoOSTF4Body'
                             ]
            
            
configure()

gaudi = appMgr()

if INTERACTIVE: N =1
    
gaudi.run(N)


if not INTERACTIVE:
    gaudi.stop()
    #if DST: gaudi.service( 'PoolRootKeyEvtCnvSvc').finalize() # This line prevents from loosing your output dst if something doesn't know how to finalize...
    gaudi.finalize()
