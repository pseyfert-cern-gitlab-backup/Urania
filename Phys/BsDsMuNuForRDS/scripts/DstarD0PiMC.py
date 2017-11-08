########################################################################
# Options for Bs->DsMuNu ntuples 
########################################################################

from DaVinci.Configuration import *
from Configurables import DaVinci
from Gaudi.Configuration import *
from Configurables import GaudiSequencer, DecayTreeTuple, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS, FilterDesktop, TupleToolMCTruth, MCTupleToolKinematic, MCTupleToolHierarchy, MCTupleToolPID, TupleToolDalitz #, TupleToolSLTools
from Configurables import CombineParticles, FilterDesktop
from GaudiConfUtils.ConfigurableGenerators import DaVinci__N3BodyDecays as Combine3Particles
from Configurables import OfflineVertexFitter
from Configurables import LoKi__VoidFilter as VoidFilter
from Configurables import SubstitutePID, SubPIDMMFilter
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from StandardParticles import StdLoosePi02gg, StdLooseResolvedPi0, StdLooseMergedPi0, StdVeryLooseAllPhotons
from StandardParticles import StdLooseAllPhotons, StdLoosePions, StdLooseKaons
import os
currentPath = os.getcwd()
PackagePath = '/'.join(s.strip('/') for s in currentPath.split('/')[:-1])
## PackagePath should end in Phys/BsDsMuNuForRDS

rootfilename = "TupleRDS_Merged.root" ## output file name
#Usegrid = True
Usegrid = False
myEvents = -1

############################
###   DV configuration ####
############################
#detectorDB = "dddb-20150724"
#conditionDB = "sim-20160606-vc-md100"

########################################################################
###  Configuration ends but CHECK to the DV configuration at the end
########################################################################

mySequencer = GaudiSequencer("mySequencer")
from Configurables import EventCountHisto,  LoKi__Hybrid__TupleTool

if Usegrid:
    myEvents = -1

## Check the number of PVs
from Configurables import CheckPV
checkPV = CheckPV('CheckPVMin1')
checkPV.MinPVs = 1
mySequencer.Members += [checkPV]

## do a selection for D*+->D0(Kpigamma)pi only one photon
lkpreambulo=["from LoKiPhysMC.decorators import *","from LoKiPhysMC.functions import mcMatch"]

cpPhiKK = Combine3Particles()
cpPhiKK.Preambulo = lkpreambulo
cpPhiKK.DecayDescriptors = ["[D0 -> K- pi+ gamma]cc"]
cpPhiKK.DaughtersCuts = {"K-" : "(TRGHP<0.4) & (MIPCHI2DV(PRIMARY) > 16) & (TRCHI2DOF<3) & (P>1500) & (PT>250) & (PIDK>-3)", 
                         "pi+" : "(TRGHP<0.4) & (MIPCHI2DV(PRIMARY) > 16) & (TRCHI2DOF<3) & (P>1500) & (PT>250) & (PIDK<3)"}
cpPhiKK.Combination12Cut = "(AM > 600)"
cpPhiKK.MotherCut = "(M < 2000) & (M > 600) & (PT>500) & (BPVVDCHI2>49)"
selcpPhi = Selection("selcpPhi", Algorithm = cpPhiKK, RequiredSelections = [StdLooseKaons, StdLoosePions, StdLooseAllPhotons])
selseqcpPhi = SelectionSequence("selseqcpPhi", TopSelection=selcpPhi)

cpDsPhiPi = CombineParticles("cpDs")
cpDsPhiPi.Preambulo = lkpreambulo
cpDsPhiPi.DecayDescriptors = ["[D*(2010)+ -> D0 pi+]cc"]
cpDsPhiPi.DaughtersCuts = {"pi+":"(TRGHP<0.4) & (TRCHI2DOF<3) & (PIDK<3) & (MIPCHI2DV(PRIMARY) < 25)"}
cpDsPhiPi.MotherCut = "(M < 2100) & (M > 700) & (VFASPF(VCHI2) < 9.0) & (M-MAXTREE('D0'==ABSID,M)>0) & (M-MAXTREE('D0'==ABSID,M)<350) & (PT>2000)"
selcpDs = Selection("selcpDs", Algorithm = cpDsPhiPi, RequiredSelections = [selcpPhi, DataOnDemand("Phys/StdLoosePions/Particles")])
selseqcpDs = SelectionSequence("selseqcpDs", TopSelection = selcpDs)

mySequencer.Members += [selseqcpDs.sequence()]

## do a selection for D*+->D0(Kpipi0)pi both photons
cpD0KPiPi0 = Combine3Particles()
cpD0KPiPi0.Preambulo = lkpreambulo
cpD0KPiPi0.DecayDescriptors = ["[D0 -> K- pi+ pi0]cc"]
cpD0KPiPi0.DaughtersCuts = {"K-" : "(TRGHP<0.4) & (MIPCHI2DV(PRIMARY) > 16) & (TRCHI2DOF<3) & (P>1500) & (PT>250) & (PIDK>-3)",
                         "pi+" : "(TRGHP<0.4) & (MIPCHI2DV(PRIMARY) > 16) & (TRCHI2DOF<3) & (P>1500) & (PT>250) & (PIDK<3)"}
cpD0KPiPi0.Combination12Cut = "(AM > 600)"
cpD0KPiPi0.MotherCut = "(M < 2000) & (M > 1700) & (PT>500) & (BPVVDCHI2>49)"
selcpD0 = Selection("selcpD0", Algorithm = cpD0KPiPi0, RequiredSelections = [DataOnDemand("Phys/StdLooseKaons/Particles"),DataOnDemand("Phys/StdLoosePions/Particles"), DataOnDemand("Phys/StdLooseMergedPi0/Particles")])
selseqcpD0 = SelectionSequence("selseqcpD0", TopSelection=selcpD0)

cpDstarD0Pi = CombineParticles("cpDstar")
cpDstarD0Pi.Preambulo = lkpreambulo
cpDstarD0Pi.DecayDescriptors = ["[D*(2010)+ -> D0 pi+]cc"]
cpDstarD0Pi.DaughtersCuts = {"pi+":"(TRGHP<0.4) & (TRCHI2DOF<3) & (PIDK<3) & (MIPCHI2DV(PRIMARY) < 25)"}
#cpDstarD0Pi.MotherCut = "(M < 2150) & (M > 1850) & (VFASPF(VCHI2) < 9.0) & (M-MAXTREE('D0'==ABSID,M)>0) & (M-MAXTREE('D0'==ABSID,M)<350) & (PT>2000)"
cpDstarD0Pi.MotherCut = "(M < 2150) & (M > 1850) & (VFASPF(VCHI2) < 9.0) & (PT>2000)"
selcpDstar = Selection("selcpDstar", Algorithm = cpDstarD0Pi, RequiredSelections = [selcpD0, DataOnDemand("Phys/StdLoosePions/Particles")])
selseqcpDstar = SelectionSequence("selseqcpDstar", TopSelection = selcpDstar)

mySequencer.Members += [selseqcpDstar.sequence()]



############################
### Configure the ntuple ###
############################

myNTUPLE = DecayTreeTuple('myNTUPLE')   
myNTUPLE.IgnoreP2PVFromInputLocations = True # ignore all stored Particle -> PV relations
myNTUPLE.ReFitPVs = True # re-fit the PVs
myNTUPLE.ToolList = [ "TupleToolGeometry"
                    , "TupleToolKinematic"
                    , "TupleToolEventInfo"
                    , "TupleToolPid"
                    , "TupleToolRecoStats"
                    , "TupleToolTrigger"
                    , "TupleToolVtxIsoln"
                    , "TupleToolTISTOS"
                    , "TupleToolTrackInfo"
                    , "TupleToolMCTruth"
                    , "TupleToolDalitz"
                   # , "TupleToolSLTools"
                   # , "TupleToolIsoGeneric"
                    ]

from Configurables import TupleToolGeometry
myNTUPLE.addTool(TupleToolGeometry)
myNTUPLE.TupleToolGeometry.OutputLevel = INFO
myNTUPLE.TupleToolGeometry.Verbose = True
myNTUPLE.TupleToolGeometry.RefitPVs = True

########################################################
## ----------  Store Triggers  ---------##
########################################################

L0Triggers = ["L0MuonDecision", "L0DiMuonDecision", "L0HadronDecision"]

Hlt1Triggers = [  "Hlt1SingleMuonNoIPDecision", "Hlt1SingleMuonHighPTDecision", "Hlt1TrackAllL0Decision", "Hlt1TrackMuonDecision"
                  ,"Hlt1TrackAllL0.*Decision"]

Hlt2Triggers = [
    "Hlt2XcMuXForTauB2XcMuDecision", "Hlt2XcMuXForTauB2XcFakeMuDecision", 
    "Hlt2TopoMu2BodyBBDTDecision", "Hlt2TopoMu3BodyBBDTDecision", "Hlt2TopoMu4BodyBBDTDecision",
    "Hlt2Topo2BodyBBDTDecision",   "Hlt2Topo3BodyBBDTDecision",   "Hlt2Topo4BodyBBDTDecision",
    "Hlt2Topo2BodySimpleDecision", "Hlt2Topo3BodySimpleDecision", "Hlt2Topo4BodySimpleDecision",
    ]

triggerListF = L0Triggers + Hlt1Triggers + Hlt2Triggers

myNTUPLE.addTool(TupleToolTISTOS)
myNTUPLE.TupleToolTISTOS.VerboseL0 = True
myNTUPLE.TupleToolTISTOS.VerboseHlt1 = True
myNTUPLE.TupleToolTISTOS.VerboseHlt2 = True
myNTUPLE.TupleToolTISTOS.FillL0 = True
myNTUPLE.TupleToolTISTOS.FillHlt1 = True
myNTUPLE.TupleToolTISTOS.FillHlt2 = True
myNTUPLE.TupleToolTISTOS.OutputLevel = INFO
myNTUPLE.TupleToolTISTOS.TriggerList = triggerListF
myNTUPLE.TupleToolTISTOS.PIDList = [511, 521, 531]

#from Configurables import TupleToolSLTools
#myNTUPLE.addTool(TupleToolSLTools)
#myNTUPLE.TupleToolSLTools.Bmass = 5366.3
#myNTUPLE.TupleToolSLTools.VertexCov = True
#myNTUPLE.TupleToolSLTools.MomCov = True

myNTUPLE.addTool(TupleToolMCTruth)
myNTUPLE.TupleToolMCTruth.OutputLevel = INFO
myNTUPLE.TupleToolMCTruth.addTool(MCTupleToolKinematic())
myNTUPLE.TupleToolMCTruth.addTool(MCTupleToolHierarchy())
myNTUPLE.TupleToolMCTruth.addTool(MCTupleToolPID())
myNTUPLE.TupleToolMCTruth.ToolList = [
    "MCTupleToolKinematic" , 
    "MCTupleToolHierarchy" , 
    "MCTupleToolPID" 
    ]
myNTUPLE.TupleToolMCTruth.MCTupleToolKinematic.StoreKineticInfo = True
myNTUPLE.TupleToolMCTruth.MCTupleToolKinematic.StoreVertexInfo = True
myNTUPLE.TupleToolMCTruth.MCTupleToolKinematic.StorePropertimeInfo = True
myNTUPLE.TupleToolMCTruth.MCTupleToolKinematic.OutputLevel = INFO

############################
###     Make    ntuples  ###
############################

from DecayTreeTuple.Configuration import *

## for signal one photon ##
B2DMuNuTuple = myNTUPLE.clone("DstarKPiG_Tuple")
B2DMuNuTuple.Inputs = [selseqcpDs.outputLocation()]
print selseqcpDs.outputLocation()
B2DMuNuTuple.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^pi+ ^gamma) ^pi+]CC"
B2DMuNuTuple.Branches = {"Dstar"   :  "[D*(2010)+ -> (D0 -> K- pi+ gamma) pi+]CC",
                         "D0"      :  "[D*(2010)+ -> ^(D0 -> K- pi+ gamma) pi+]CC",
                         "kpl"     :  "[D*(2010)+ -> (D0 -> ^K- pi+ gamma) pi+]CC",
                         "pim"     :  "[D*(2010)+ -> (D0 -> K- ^pi+ gamma) pi+]CC",
                         "ph"      :  "[D*(2010)+ -> (D0 -> K- pi+ ^gamma) pi+]CC",
                         "pis"     :  "[D*(2010)+ -> (D0 -> K- pi+ gamma) ^pi+]CC"}

B2DMuNuTuple.addTool(TupleToolDecay("Dstar"))
B2DMuNuTuple.Dstar.InheritTools = True

from Configurables import TupleToolEWTrackIsolation
B2DMuNuTuple.addTool(TupleToolDecay("Dstar"))
B2DMuNuTuple.Dstar.InheritTools = True
EWconeDs = B2DMuNuTuple.Dstar.addTupleTool(TupleToolEWTrackIsolation)
EWconeDs.ConeStepSize = 0.2
EWconeDs.MinConeRadius = 0.2
EWconeDs.MaxConeRadius = 1.0
EWconeDs.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDs.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDs.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"
EWconeDs.isMC = True

## for signal one pi0 ##
DstarPi0Tuple = myNTUPLE.clone("DstarKPiPi0_Tuple")
DstarPi0Tuple.Inputs = [selseqcpDstar.outputLocation()]
DstarPi0Tuple.Decay = "[D*(2010)+ -> ^(D0 -> ^K- ^pi+ ^(pi0 -> ^gamma ^gamma)) ^pi+]CC"
DstarPi0Tuple.Branches = {"Dstar"   :  "[D*(2010)+ -> (D0 -> K- pi+ (pi0 -> gamma gamma) ) pi+]CC",
                         "D0"      :  "[D*(2010)+ -> ^(D0 -> K- pi+ (pi0 -> gamma gamma) ) pi+]CC",
                         "kpl"     :  "[D*(2010)+ -> (D0 -> ^K- pi+ (pi0 -> gamma gamma) ) pi+]CC",
                         "pim"     :  "[D*(2010)+ -> (D0 -> K- ^pi+ (pi0 -> gamma gamma) ) pi+]CC",
                         "pi0"      :  "[D*(2010)+ -> (D0 -> K- pi+ ^(pi0 -> gamma gamma) ) pi+]CC",
                         "ph1"      :  "[D*(2010)+ -> (D0 -> K- pi+ (pi0 -> ^gamma gamma) ) pi+]CC",
                         "ph2"      :  "[D*(2010)+ -> (D0 -> K- pi+ (pi0 -> gamma ^gamma) ) pi+]CC", 
                         "pis"     :  "[D*(2010)+ -> (D0 -> K- pi+ ^(pi0 -> gamma gamma) ) ^pi+]CC"}

DstarPi0Tuple.addTool(TupleToolDecay("Dstar"))
DstarPi0Tuple.Dstar.InheritTools = True

#from Configurables import TupleToolEWTrackIsolation
#DstarPi0Tuple.addTool(TupleToolDecay("Dstar"))
#DstarPi0Tuple.Dstar.InheritTools = True
#EWconeDs = DstarPi0Tuple.Dstar.addTupleTool(TupleToolEWTrackIsolation)
#EWconeDs.ConeStepSize = 0.2
#EWconeDs.MinConeRadius = 0.2
#EWconeDs.MaxConeRadius = 1.0
#EWconeDs.ExtraParticlesLocation = "StdAllLoosePions"
#EWconeDs.ExtraPi0sLocation = "StdLoosePi02gg"
#EWconeDs.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"
#EWconeDs.isMC = True

#######################
### DaVinci options ###
#######################
DaVinci().EvtMax = myEvents  
DaVinci().SkipEvents = 0
DaVinci().DataType = "2016"
DaVinci().Simulation = True
DaVinci().Lumi = False
DaVinci().PrintFreq = 200
DaVinci().UserAlgorithms = [ mySequencer ]
DaVinci().MoniSequence = [B2DMuNuTuple, DstarPi0Tuple]
#DaVinci().MoniSequence = [DstarPi0Tuple]
#DaVinci().MoniSequence = [B2DMuNuTuple]

DaVinci().TupleFile = rootfilename
#DaVinci().DDDBtag   = detectorDB 
#DaVinci().CondDBtag = conditionDB
#print 'DDDBtag was ', detectorDB, ' and condDBtag was ', conditionDB

DaVinci().InputType = "DST"

if not(Usegrid):
    from GaudiConf import IOHelper
    IOHelper().inputFiles([
    #"root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000001_2.dst?svcClass=lhcbDst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2016/ALLSTREAMS.DST/00062510/0000/00062510_00000004_7.AllStreams.dst",
    "root://ccdcacli265.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2016/ALLSTREAMS.DST/00062510/0000/00062510_00000001_7.AllStreams.dst",
    "root://lhcb-sdpd9.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbdisk/lhcb/MC/2016/ALLSTREAMS.DST/00062510/0000/00062510_00000002_7.AllStreams.dst",
    "root://mouse16.grid.surfsara.nl:1094/pnfs/grid.sara.nl/data/lhcb/MC/2016/ALLSTREAMS.DST/00062510/0000/00062510_00000003_7.AllStreams.dst"
    ]
    ,clear=True)
MessageSvc().Format = "% F%60W%S%7W%R%T %0W%M"
MessageSvc().OutputLevel = INFO
