"""
 Script to create a DecayTreeTuple for Bs2JpsiKstar analysis.
  Input: run on the stripping locations: please check the exact location from one stripping to another!
         currently tested on DST. Should be tested on microDST
  Output: many information useful for analyse:
   - event related variables are stored in EventTuple
   - candidates related information are stored in Trees:
     kinematic, trigger, tagging, tracking, ...
     Names are the ones provided by the DecayTreeTuple framework or via LoKi Hybrid tuple.

  Options:
   1- job = 'Grid' to pass on grid mode, where there is a special recepie so the job pass with no problems,
      job = ''     to pass interactivly with real data dsts
      job = 'MC'   to pass on MC dsts: check the correct B inputLocation!
   2- Outputlevel = 1 , 2 , 3, 4 ,5 or 6 verbosity level (1 to show all messages from all tools , 6 shows just FATAL errors )
      to be set to 6 on grid, avoid unnecessary waste of time/space.
   3- Trigger(TisTos or not) tool is configuered to take a specific lines, those lines change with tcks,
      this list should be an input variable       
"""
# __author__ = "Basem Khanji, Emilie Maurice, Olivier Leroy (khanji@cppm.in2p3.fr)"
# Restripping section included by C. Vazquez Sierra. Some modifications were made, too.

import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from Configurables import GaudiSequencer
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *
from Configurables import CheckPV
from Configurables import (DecayTreeTuple,TupleToolDecay,TupleToolVtxIsoln ,
                           LoKi__Hybrid__TupleTool,TupleToolTrigger,TupleToolTagging,
                           TupleToolP2VV,TupleToolTISTOS,BTagging,
                           PrintDecayTree,PrintDecayTreeTool, TupleToolTrackPosition, TupleToolRecoStats )


job = 'Grid '
outputlevel = 6

##############################################################################################
##### RESTRIPPING (including StrippingBetaSBs2JpsiKstarWideLine):
##############################################################################################

## 2012 MC, magnetDown, BsJpsiKst.
## Stripping20r0p1 is an incremental restripping of Stripping20 for 2012 data.

## This script has been modified for MC DSTs which have been produced for Stripping20
## (NoPrescaling, Flagged), simulating the BsJpsiKst decay for 2012 conditions. This
## part runs the StrippingBetaSBs2JpsiKstarWideLine (Stripping20r0p1) over the MC DSTs.
## Next part, creates the ntuple using this line and the decay descriptor of BsJpsiKst.

MessageSvc().Format = "% F%30W%S%7W%R%T %0W%M" ## Only for Stripping20r0p1, I guess.

TupleSeq = GaudiSequencer('TupleSeq')
### Conditions (part 1/2):
DaVinci().DDDBtag   = "Sim08-20130503-1"
DaVinci().CondDBtag = "Sim08-20130503-1-vc-md100" ## Magnet down (md).
####################

from StrippingConf.Configuration import StrippingConf, StrippingStream
from StrippingSettings.Utils import strippingConfiguration
from StrippingArchive.Utils import buildStreams, cloneLinesFromStream
from StrippingArchive import strippingArchive

stripping='stripping20r0p1' ## Stripping version.
config  = strippingConfiguration(stripping)
archive = strippingArchive(stripping)
streams = buildStreams(stripping = config, archive = archive)

myStream = StrippingStream("myStream")
myLines = ["StrippingBetaSBs2JpsiKstarWideLine"]
for stream in streams:
  for line in stream.lines:
    if line.name() in myLines:  
      myStream.appendLines([ line ])

from Configurables import ProcStatusCheck
filterBadEvents=ProcStatusCheck()

sc = StrippingConf( Streams = [ myStream ],
                    MaxCandidates = 2000,
                    AcceptBadEvents = False,
                    BadEventSelection = filterBadEvents)

DaVinci().appendToMainSequence( [ sc.sequence() ] )

##############################################################################################
##### SELECTIONS:
##############################################################################################
#Bddecaydcr        = "[B0 -> (^J/psi(1S) -> ^mu+ ^mu-) (^K*(892)0 -> ^K+ ^pi-)]cc" # Change to this if you want to use the DetachedLine.
Bddecaydcr        = "[B_s0 -> (^J/psi(1S) => ^mu+ ^mu-) (^K*(892)~0 => ^K- ^pi+)]cc"
#BdPartVtxlocation = "AllStreams/Phys/BetaSBd2JpsiKstarDetachedLine/Particles" # Change to this if you want to use the DetachedLine.
BdPartVtxlocation = "Phys/BetaSBs2JpsiKstarWideLine/Particles"
##############################################################################################
BdTuple = DecayTreeTuple("BdTuple")
BdTuple.ToolList +=  [
    "TupleToolTrigger"
    , "TupleToolGeometry"
    , "TupleToolKinematic"
    , "TupleToolPropertime"
    , "TupleToolPrimaries"
    , "TupleToolEventInfo"
    , "TupleToolTrackInfo"
    , "TupleToolTagging"
    , "TupleToolRecoStats"
    , "TupleToolTrackPosition"
    , "TupleToolMCTruth"
    ]
BdTuple.Inputs = [BdPartVtxlocation]
BdTuple.Decay    = Bddecaydcr
BdTuple.ReFitPVs = True

TupleToolTrackPosition = TupleToolTrackPosition('TupleToolTrackPosition')
TupleToolTrackPosition.Z = 7500.
BdTuple.addTool(TupleToolTrackPosition)

TupleToolRecoStats = TupleToolRecoStats('TupleToolRecoStats')
TupleToolRecoStats.Verbose = True
BdTuple.addTool(TupleToolRecoStats)

LoKiVariables = LoKi__Hybrid__TupleTool('LoKiVariables')
LoKiVariables.Variables = {
	"LOKI_ENERGY"     : "E",
	"LOKI_ETA"        : "ETA",
	"LOKI_PHI"        : "PHI",
	 }

BdTuple.addTool(LoKiVariables , name = 'LoKiVariables' )
BdTuple.ToolList   += [ 'LoKi::Hybrid::TupleTool/LoKiVariables']
BdTuple.OutputLevel = 6

from Configurables import TupleToolGeometry, TupleToolTrackInfo
TupleToolGeometry = TupleToolGeometry('TupleToolGeometry')
TupleToolGeometry.RefitPVs = True
TupleToolGeometry.Verbose = True
BdTuple.addTool(TupleToolGeometry)

TupleToolTrackInfo = TupleToolTrackInfo('TupleToolTrackInfo')
TupleToolTrackInfo.Verbose = True
BdTuple.addTool(TupleToolTrackInfo)

TupleToolTagging = TupleToolTagging('TupleToolTagging')
TupleToolTagging.Verbose = True
BdTuple.addTool(TupleToolTagging)
TupleSeq.Members += [ BdTuple ]

#######################################################
##### TRIGGER:
#######################################################
TupleToolTrigger = TupleToolTrigger('TupleToolTrigger')
TupleToolTrigger.Verbose = True
TupleToolTrigger.TriggerList  =[
	 "L0PhysicsDecision"
	,"L0MuonDecision"
	,"L0DiMuonDecision"
	,"L0MuonHighDecision"
	,"L0HadronDecision"
	,"L0ElectronDecision"
	,"L0PhotonDecision"
	,"Hlt1DiMuonHighMassDecision"
	,"Hlt1DiMuonLowMassDecision"
	,"Hlt1SingleMuonNoIPDecision"
	,"Hlt1SingleMuonHighPTDecision"
	,"Hlt1TrackAllL0Decision"
	,"Hlt1TrackMuonDecision"
	,"Hlt1TrackPhotonDecision"
	,"Hlt1MBNoBiasDecision"
	,"Hlt1MBMicroBiasVeloDecision"
	,"Hlt1MBMicroBiasTStationDecision"
	,"Hlt1L0AnyDecision"
	,"Hlt1DiProtonDecision"
	,"Hlt1DiProtonLowMultDecision"
	,"Hlt2SingleElectronTFLowPtDecision"
	,"Hlt2SingleElectronTFHighPtDecision"
	,"Hlt2DiElectronHighMassDecision"
	,"Hlt2DiElectronBDecision"
	,"Hlt2B2HHLTUnbiasedDecision"
	,"Hlt2Topo2BodySimpleDecision"
	,"Hlt2Topo3BodySimpleDecision"
	,"Hlt2Topo4BodySimpleDecision"
	,"Hlt2Topo2BodyBBDTDecision"
	,"Hlt2Topo3BodyBBDTDecision"
	,"Hlt2Topo4BodyBBDTDecision"
	,"Hlt2TopoMu2BodyBBDTDecision"
	,"Hlt2TopoMu3BodyBBDTDecision"
	,"Hlt2TopoMu4BodyBBDTDecision"
	,"Hlt2TopoE2BodyBBDTDecision"
	,"Hlt2TopoE3BodyBBDTDecision"
	,"Hlt2TopoE4BodyBBDTDecision"
	,"Hlt2IncPhiDecision"
	,"Hlt2IncPhiSidebandsDecision"
	,"Hlt2MuonFromHLT1Decision"
	,"Hlt2SingleMuonDecision"
	,"Hlt2SingleMuonHighPTDecision"
	,"Hlt2SingleMuonLowPTDecision"
	,"Hlt2DiMuonDecision"
	,"Hlt2DiMuonLowMassDecision"
	,"Hlt2DiMuonJPsiDecision"
	,"Hlt2DiMuonJPsiHighPTDecision"
	,"Hlt2DiMuonPsi2SDecision"
	,"Hlt2DiMuonBDecision"
	,"Hlt2DiMuonZDecision"
	,"Hlt2DiMuonDY1Decision"
	,"Hlt2DiMuonDY2Decision"
	,"Hlt2DiMuonDY3Decision"
	,"Hlt2DiMuonDY4Decision"
	,"Hlt2DiMuonDetachedDecision"
	,"Hlt2DiMuonDetachedHeavyDecision"
	,"Hlt2DiMuonDetachedJPsiDecision"
	,"Hlt2DiMuonNoPVDecision"
	,"Hlt2TriMuonDetachedDecision"
	,"Hlt2TriMuonTauDecision"
	,"Hlt2DiMuonDetachedJPsiDecision"
	,"Hlt2DiMuonDetachedDecision"
	]
TupleToolTrigger.OutputLevel = 6
BdTuple.addTool(TupleToolTrigger)

TupleToolTISTOS = TupleToolTISTOS('TupleToolTISTOS')
TupleToolTISTOS.Verbose = True

TupleToolTISTOS.TriggerList=[
	"Hlt1DiMuonHighMassDecision"
	,"Hlt1DiMuonLowMassDecision"
	,"Hlt1SingleMuonNoIPDecision"
	,"Hlt1SingleMuonHighPTDecision"
	,"Hlt1TrackAllL0Decision"
	,"Hlt1TrackMuonDecision"
	,"Hlt2TopoMu2BodyBBDTDecision"
	,"Hlt2TopoMu3BodyBBDTDecision"
	,"Hlt2TopoMu4BodyBBDTDecision"
	,"Hlt2MuonFromHLT1Decision"
	,"Hlt2SingleMuonDecision"
	,"Hlt2SingleMuonHighPTDecision"
	,"Hlt2SingleMuonLowPTDecision"
	,"Hlt2DiMuonDecision"
	,"Hlt2DiMuonLowMassDecision"
	,"Hlt2DiMuonJPsiDecision"
	,"Hlt2DiMuonJPsiHighPTDecision"
	,"Hlt2DiMuonPsi2SDecision"
	,"Hlt2DiMuonBDecision"
	,"Hlt2DiMuonDetachedJPsiDecision"
	,"Hlt2DiMuonDetachedDecision"

		        ]

LoKi_SpecificToB=LoKi__Hybrid__TupleTool("LoKi_SpecificToB")
LoKi_SpecificToB.Variables =  {
    "LOKI_FDCHI2"          : "BPVVDCHI2",
    "LOKI_FDS"             : "BPVDLS",
    "LOKI_DIRA"            : "BPVDIRA",
    ###### DecayTreeFitVariables:
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )",
    "LOKI_DTF_CHI2NDOF"    : "DTF_CHI2NDOF( True )",
    "LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )",
    "LOKI_MASS_JpsiConstr" : "DTF_FUN ( M , False , 'J/psi(1S)' )" ,
    "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )",
        }

LoKi_SpecificToJpsi = LoKi__Hybrid__TupleTool("LoKi_SpecificToJpsi")
LoKi_SpecificToJpsi.Variables =  {
    "LOKI_DOCA_1_2"        : "DOCA(1,2)",
}

###########################################################
##################### BdTuple #############################
###########################################################
# Change to this if you want to use the DetachedLine:
#BdTuple.Branches={
#    "B0" :  "[B0]cc : [B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]cc",
#    "J_psi_1S" :  "[B0 -> (^J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]cc"
#    }
# Change to this if you want to use the WideLine:
BdTuple.Branches={
    "B0" :  "[B_s0]cc : [B_s0 -> (J/psi(1S) => mu+ mu-) (K*(892)~0 => K- pi+)]cc",
    "J_psi_1S" :  "[B_s0 -> (^J/psi(1S) => mu+ mu-) (K*(892)~0 => K- pi+)]cc",
    "Kplus" :  "[B_s0 -> (J/psi(1S) => mu+ mu-) (K*(892)~0 => ^K- pi+)]cc",
    "piminus" :  "[B_s0 -> (J/psi(1S) => mu+ mu-) (K*(892)~0 => K- ^pi+)]cc",
    "Kst_892_0" :  "[B_s0 -> (J/psi(1S) => mu+ mu-) (^K*(892)~0 => K- pi+)]cc"
            }
# Common for both lines:
BdTuple.addTool(TupleToolDecay, name="B0")
BdTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BdTuple.B0.addTool(LoKi_SpecificToB)
TupleToolP2VV_Bd = TupleToolP2VV('TupleToolP2VV_Bd')
TupleToolP2VV_Bd.Calculator = 'Bd2KstarMuMuAngleCalculator'
TupleToolP2VV_Bd.OutputLevel = 6
BdTuple.B0.addTool(TupleToolP2VV_Bd)
BdTuple.B0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_Bd"]

BdTuple.B0.addTool(TupleToolTISTOS)
from Configurables import TriggerTisTos
BdTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BdTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BdTuple.B0.ToolList+=["TupleToolTISTOS"]
BdTuple.B0.ToolList+=["TupleToolMCBackgroundInfo"]

BdTuple.addTool(TupleToolDecay, name="J_psi_1S")
BdTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BdTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

###########################################################
TupleSeq.ModeOR          = True
TupleSeq.ShortCircuit    = False
locations = []
for tupleAlg in TupleSeq.Members:
    locations.extend(tupleAlg.Inputs)

from Configurables import LoKi__VoidFilter as VoidFilter
locationFilter = VoidFilter("LocationFilter")
locationFilter.Code = '(' + ' | '.join(("(CONTAINS('%s') > 0)" % l for l in locations)) + ')'

from Configurables import EventTuple , TupleToolTrigger
evtTuple                = EventTuple()
evtTuple.ToolList      += [ "TupleToolEventInfo", "TupleToolTrigger"]

seqB2JpsiX               = GaudiSequencer('seqB2JpsiX')
seqB2JpsiX.Members       = [locationFilter, evtTuple, TupleSeq]

from FileStager.Configuration import configureFileStager
configureFileStager()

### Conditions (part 2/2):
DaVinci().EvtMax        =  -1
DaVinci().SkipEvents    =  0
DaVinci().Lumi = True
DaVinci().DataType     = '2012'
DaVinci().Simulation = True
####################
DaVinci().TupleFile       = "DTT.root"  # Final ntuple.
DaVinci().UserAlgorithms  = [seqB2JpsiX]
####################
