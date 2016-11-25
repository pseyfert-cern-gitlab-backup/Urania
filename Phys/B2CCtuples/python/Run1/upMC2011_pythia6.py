"""
 Script to create a DecayTreeTuple for b2JpsiX analyses:
  Bs2JpsiPhi , Bu2JpsiKplus, Bd2JpsiKstar ,
  (one can easly add Bd2JpsiKshort or Lambda_b2JpsiLambda but one should provide the proper selection
   for those channels in the selection file). 
  Input: run on the stripping locations: please check the exact location from one stripping to another!
         currently tested on DST. Should be tested on microDST
  Output: many information useful for analyse:
   - event related variables are stored in EventTuple
   - candidates related information are stored in Trees:
     kinematic, trigger, tagging, tracking, ...
     Names are the ones provided by the DecayTreeTuple framework or via LoKi Hybrid tuple.

  Options:
   3- Trigger(TisTos or not) tool is configuered to take a specific lines, those lines change with tcks,
      this list should be an input variable       
"""
# __author__ = "Basem Khanji, Emilie Maurice, Olivier Leroy (khanji@cppm.in2p3.fr)"


import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from Configurables import GaudiSequencer
from Configurables import DaVinci

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import CheckPV
from Configurables import (TupleToolDecay,TupleToolVtxIsoln ,
                           LoKi__Hybrid__TupleTool,TupleToolTrigger,TupleToolTagging,
                           TupleToolP2VV,TupleToolTISTOS,BTagging,
#                           PrintDecayTree,PrintDecayTreeTool )
                           PrintDecayTree,PrintDecayTreeTool, TupleToolTrackPosition, TupleToolRecoStats )
from DecayTreeTuple.Configuration import *

##############################################################################################
##### SELECTIONS
##############################################################################################
##############################################################################################
Bsdecaydcr        = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"
BsPartVtxlocation = "AllStreams/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
#BsPartVtxlocationPrescaled = "AllStreams/Phys/BetaSBs2JpsiPhiPrescaledLine/Particles"

Bddecaydcr        = "[B0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(K*(892)0 -> ^K+ ^pi-)]CC"
BdPartVtxlocation = "AllStreams/Phys/BetaSBd2JpsiKstarDetachedLine/Particles"
#BdPartVtxlocationPrescaled = "AllStreams/Phys/BetaSBd2JpsiKstarPrescaledLine/Particles"

Budecaydcr        = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^K+]CC"
BuPartVtxlocation = "AllStreams/Phys/BetaSBu2JpsiKDetachedLine/Particles"
#BuPartVtxlocationPrescaled = "AllStreams/Phys/BetaSBu2JpsiKPrescaledLine/Particles"

#BdKshortdecaydcr  = "B0 -> ^(J/psi(1S)-> ^mu+ ^mu-) ^(KS0 -> ^pi+ ^pi-)"
#BdKshortPartVtxlocation = "AllStreams/Phys/BetaSBd2JpsiKsDetachedLine/Particles"
#BdKshortPartVtxlocationPrescaled = "AllStreams/Phys/BetaSBd2JpsiKsPrescaledLine/Particles"

#Lbdecaydcr  = "[Lambda_b0 -> ^(Lambda0 -> ^p+ ^pi-) ^(J/psi(1S) -> ^mu+ ^mu-) ]CC"
#LbPartVtxlocation = "AllStreams/Phys/BetaSLambdab2JpsiLambdaUnbiasedLine/Particles"
##############################################################################################




##############################################################################################
#TUPLE
TupleSeq = GaudiSequencer('TupleSeq')
################################################################################################
BsTuple = DecayTreeTuple("BsTuple")
BsTuple.ToolList +=  [
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
#BsTuple.InputLocations = [BsPartVtxlocation] #
BsTuple.Inputs = [BsPartVtxlocation] #
BsTuple.Decay    = Bsdecaydcr
BsTuple.ReFitPVs = True

TupleToolTrackPosition = TupleToolTrackPosition('TupleToolTrackPosition')
TupleToolTrackPosition.Z = 7500.
BsTuple.addTool(TupleToolTrackPosition)

TupleToolRecoStats = TupleToolRecoStats('TupleToolRecoStats')
TupleToolRecoStats.Verbose = True
BsTuple.addTool(TupleToolRecoStats)

LoKiVariables = LoKi__Hybrid__TupleTool('LoKiVariables')
LoKiVariables.Variables = {
	"LOKI_ENERGY"     : "E",
	"LOKI_ETA"        : "ETA",
	"LOKI_PHI"        : "PHI",
	 }

BsTuple.addTool(LoKiVariables , name = 'LoKiVariables' )
BsTuple.ToolList   += [ 'LoKi::Hybrid::TupleTool/LoKiVariables']

from Configurables import TupleToolGeometry, TupleToolTrackInfo
TupleToolGeometry = TupleToolGeometry('TupleToolGeometry')
TupleToolGeometry.RefitPVs = True
TupleToolGeometry.Verbose = True
BsTuple.addTool(TupleToolGeometry)

TupleToolTrackInfo = TupleToolTrackInfo('TupleToolTrackInfo')
TupleToolTrackInfo.Verbose = True
BsTuple.addTool(TupleToolTrackInfo)

# Add per Tagger infos ...:
TupleToolTagging = TupleToolTagging('TupleToolTagging')
TupleToolTagging.Verbose = True
BsTuple.addTool(TupleToolTagging)

# BsTuple.addTool(TupleToolTagging, name = 'Bs')
# ############# Tagging configuration for Reco 14 - MC12 ############
# BsTag = BsTtuple.Bs.addTupleTool( TupleToolTagging, name="BsAll")
# BsTag.TaggingToolName = "BTaggingTool/BsTaggingTool"
# BsTag.addTool(BTaggingTool,name="BsTaggingTool")
# BsTag.BsTaggingTool.ForceSignalID = '"Bs"'   # required if you want to force the combination of OS with SSK
# BsTag.Verbose = True
# from FlavourTagging.Tunings import TuneTool
# myTuneTool = TuneTool(BsTag,"Reco14_MC12","BsTaggingTool")  # sets the Reco14_MC12 tuning (default is Reco14_2012)

TupleSeq.Members += [ BsTuple ]
##### TRIGGER :
#######################################################
TupleToolTrigger = TupleToolTrigger('TupleToolTrigger')
TupleToolTrigger.Verbose = True
#TupleToolTrigger.UseAutomaticTriggerList = True
#TupleToolTrigger.CollateTriggerList    = True
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
BsTuple.addTool(TupleToolTrigger)

# Now clone for the other lines
BuTuple = BsTuple.clone("BuTuple")
#BuTuple.InputLocations = [BuPartVtxlocation]
BuTuple.Inputs = [BuPartVtxlocation]

BuTuple.Decay          =  Budecaydcr
BuTuple.addTool(TupleToolGeometry)
BuTuple.addTool(TupleToolTrackInfo)

TupleSeq.Members      += [ BuTuple]



BdTuple = BsTuple.clone("BdTuple")
#BdTuple.InputLocations = [BdPartVtxlocation]
BdTuple.Inputs = [BdPartVtxlocation]
BdTuple.Decay          = Bddecaydcr
TupleSeq.Members      += [ BdTuple]

BdTuple.addTool(TupleToolGeometry)
BdTuple.addTool(TupleToolTrackInfo)

#Bd2JpsiKSTuple = BsTuple.clone("Bd2JpsiKSTuple")
#Bd2JpsiKSTuple.InputLocations = [BdKshortPartVtxlocation]
#Bd2JpsiKSTuple.Decay          = BdKshortdecaydcr
#TupleSeq.Members      += [ Bd2JpsiKSTuple]

#Bd2JpsiKSTuple.addTool(TupleToolGeometry)
#Bd2JpsiKSTuple.addTool(TupleToolTrackInfo)

# BsPrescaledTuple = BsTuple.clone("BsPrescaledTuple")
# BsPrescaledTuple.Inputs = [BsPartVtxlocationPrescaled]
# TupleSeq.Members      += [ BsPrescaledTuple]

# BsPrescaledTuple.Decay          =  Bsdecaydcr
# BsPrescaledTuple.addTool(TupleToolGeometry)
# BsPrescaledTuple.addTool(TupleToolTrackInfo)

#olBuPrescaledTuple = BsTuple.clone("BuPrescaledTuple")
#olBuPrescaledTuple.Inputs = [BuPartVtxlocationPrescaled]

#olBuPrescaledTuple.Decay          =  Budecaydcr
#BuPrescaledTuple.addTool(TupleToolGeometry)
#olBuPrescaledTuple.addTool(TupleToolTrackInfo)

#olTupleSeq.Members      += [ BuPrescaledTuple]


#olBdPrescaledTuple = BsTuple.clone("BdPrescaledTuple")
#olBdPrescaledTuple.Inputs = [BdPartVtxlocationPrescaled]
#olBdPrescaledTuple.Decay          = Bddecaydcr
#olTupleSeq.Members      += [ BdPrescaledTuple]

#olBdPrescaledTuple.addTool(TupleToolGeometry)
#olBdPrescaledTuple.addTool(TupleToolTrackInfo)

#Bd2JpsiKSPrescaledTuple = BsTuple.clone("Bd2JpsiKSPrescaledTuple")
#Bd2JpsiKSPrescaledTuple.InputLocations = [BdKshortPartVtxlocationPrescaled]
#Bd2JpsiKSPrescaledTuple.Decay          = BdKshortdecaydcr
#TupleSeq.Members      += [ Bd2JpsiKSPrescaledTuple]

#Bd2JpsiKSPrescaledTuple.addTool(TupleToolGeometry)
#Bd2JpsiKSPrescaledTuple.addTool(TupleToolTrackInfo)

#LbTuple = BsTuple.clone("LbTuple")
#LbTuple.InputLocations = [LbPartVtxlocation]
#LbTuple.Decay          = Lbdecaydcr
#TupleSeq.Members      += [ LbTuple]

#LbTuple.addTool(TupleToolGeometry)
#LbTuple.addTool(TupleToolTrackInfo)

# fine tunning to add variables to Bplus particle
TupleToolTISTOS = TupleToolTISTOS('TupleToolTISTOS')
TupleToolTISTOS.Verbose = True

#TupleToolTISTOS.UseAutomaticTriggerList = True
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
    ###### DecayTreeFitVariables
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )",
    "LOKI_DTF_CHI2NDOF"    : "DTF_CHI2NDOF( True )",
    "LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )",
    "LOKI_MASS_JpsiConstr" : "DTF_FUN ( M , False , 'J/psi(1S)' )" ,
    "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )",
    #"LOKI_DTF_TAU"         : "DTF_FUN ( BPVLTIME('PropertimeFitter/properTime:PUBLIC') , True)"
        }

LoKi_SpecificToJpsi = LoKi__Hybrid__TupleTool("LoKi_SpecificToJpsi")
LoKi_SpecificToJpsi.Variables =  {
    "LOKI_DOCA_1_2"        : "DOCA(1,2)",
}

###########################################################
##################### BsTuple #############################
BsTuple.addBranches({
    "B_s0" :  "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))",
    "J_psi_1S" :  "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"
    })
BsTuple.addTool(TupleToolDecay, name="B_s0")
BsTuple.B_s0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTuple.B_s0.addTool(LoKi_SpecificToB)
TupleToolP2VV_Bs = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_Bs.Calculator = 'Bs2JpsiPhiAngleCalculator'
BsTuple.B_s0.addTool(TupleToolP2VV_Bs)
BsTuple.B_s0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_Bs"]

BsTuple.B_s0.addTool(TupleToolTISTOS)
from Configurables import TriggerTisTos
BsTuple.B_s0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BsTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.

BsTuple.B_s0.ToolList+=["TupleToolTISTOS"]
BsTuple.B_s0.ToolList+=["TupleToolMCBackgroundInfo"]

BsTuple.addTool(TupleToolDecay, name="J_psi_1S")
BsTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BsTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)


# Prescaled line
# BsPrescaledTuple.addBranches({
#     "B_s0" :  "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))",
#     "J_psi_1S" : "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"
#     })
# BsPrescaledTuple.addTool(TupleToolDecay, name="B_s0")
# BsPrescaledTuple.B_s0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
# BsPrescaledTuple.B_s0.addTool(LoKi_SpecificToB)
# TupleToolP2VV_BsPrescaled = TupleToolP2VV('TupleToolP2VV_Bs')
# TupleToolP2VV_BsPrescaled.Calculator = 'Bs2JpsiPhiAngleCalculator'
# BsPrescaledTuple.B_s0.addTool(TupleToolP2VV_BsPrescaled)
# BsPrescaledTuple.B_s0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_BsPrescaled"]

# BsPrescaledTuple.B_s0.addTool(TupleToolTISTOS)
# from Configurables import TriggerTisTos
# BsPrescaledTuple.B_s0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
# BsPrescaledTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.

# BsPrescaledTuple.B_s0.ToolList+=["TupleToolTISTOS"]
# BsPrescaledTuple.B_s0.ToolList+=["TupleToolMCBackgroundInfo"]

# BsPrescaledTuple.addTool(TupleToolDecay, name="J_psi_1S")
# BsPrescaledTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
# BsPrescaledTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)


###########################################################

###########################################################
##################### BuTuple #############################
BuTuple.addBranches({
    "Bplus" : "[^(B+ -> (J/psi(1S) -> mu+ mu-) K+)]CC",
    "J_psi_1S" : "[B+ -> ^(J/psi(1S) -> mu+ mu-) K+]CC"
    })
BuTuple.addTool(TupleToolDecay, name="Bplus")
BuTuple.Bplus.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BuTuple.Bplus.addTool(LoKi_SpecificToB)

BuTuple.addTool(TupleToolGeometry)

BuTuple.Bplus.addTool(TupleToolTISTOS)
BuTuple.Bplus.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BuTuple.Bplus.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BuTuple.Bplus.ToolList+=["TupleToolTISTOS"]
BuTuple.Bplus.ToolList+=["TupleToolMCBackgroundInfo"]

BuTuple.addTool(TupleToolDecay, name="J_psi_1S")
BuTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BuTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)


# BuPrescaledTuple.addBranches({
#     "Bplus" : "[^(B+ -> (J/psi(1S) -> mu+ mu-) K+)]CC",
#     "J_psi_1S" : "[B+ -> ^(J/psi(1S) -> mu+ mu-) K+]CC"
#     })
# BuPrescaledTuple.addTool(TupleToolDecay, name="Bplus")
# BuPrescaledTuple.Bplus.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
# BuPrescaledTuple.Bplus.addTool(LoKi_SpecificToB)

# BuPrescaledTuple.addTool(TupleToolGeometry)

# BuPrescaledTuple.Bplus.addTool(TupleToolTISTOS)
# BuPrescaledTuple.Bplus.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
# BuPrescaledTuple.Bplus.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
# BuPrescaledTuple.Bplus.ToolList+=["TupleToolTISTOS"]
# BuPrescaledTuple.Bplus.ToolList+=["TupleToolMCBackgroundInfo"]

# BuPrescaledTuple.addTool(TupleToolDecay, name="J_psi_1S")
# BuPrescaledTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
# BuPrescaledTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

###########################################################

###########################################################
##################### BdTuple #############################
# BdTuple.addBranches({
#     "B0" :  "[^(B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-))]CC",
#     "J_psi_1S" :  "[B0 -> ^(J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]CC"
#     })
# BdTuple.addTool(TupleToolDecay, name="B0")
# BdTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
# BdTuple.B0.addTool(LoKi_SpecificToB)
# TupleToolP2VV_Bd = TupleToolP2VV('TupleToolP2VV_Bd')
# TupleToolP2VV_Bd.Calculator = 'Bd2KstarMuMuAngleCalculator'
# BdTuple.B0.addTool(TupleToolP2VV_Bd)
# BdTuple.B0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_Bd"]

# BdTuple.B0.addTool(TupleToolTISTOS)
# BdTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
# BdTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
# BdTuple.B0.ToolList+=["TupleToolTISTOS"]
# BdTuple.B0.ToolList+=["TupleToolMCBackgroundInfo"]

# # Prescaled
# BdPrescaledTuple.addBranches({
#     "B0" :  "[^(B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-))]CC",
#     "J_psi_1S" :  "[B0 -> ^(J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]CC"
#     })
# BdPrescaledTuple.addTool(TupleToolDecay, name="B0")
# BdPrescaledTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
# BdPrescaledTuple.B0.addTool(LoKi_SpecificToB)
# TupleToolP2VV_BdPrescaled = TupleToolP2VV('TupleToolP2VV_BdPrescaled')
# TupleToolP2VV_BdPrescaled.Calculator = 'Bd2KstarMuMuAngleCalculator'
# BdPrescaledTuple.B0.addTool(TupleToolP2VV_Bd)
# BdPrescaledTuple.B0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_BdPrescaled"]

# BdPrescaledTuple.B0.addTool(TupleToolTISTOS)
# BdPrescaledTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
# BdPrescaledTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
# BdPrescaledTuple.B0.ToolList+=["TupleToolTISTOS"]
# BdPrescaledTuple.B0.ToolList+=["TupleToolMCBackgroundInfo"]

# BdTuple.addTool(TupleToolDecay, name="J_psi_1S")
# BdTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
# BdTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

############################################################
##################### Bd2JpsiKSTuple #############################
"""
Bd2JpsiKSTuple.addBranches({
    "B0" :  "^(B0 -> (J/psi(1S) -> mu+ mu-) (KS0 -> pi+ pi-))",
    "J_psi_1S" :  "B0 -> ^(J/psi(1S) -> mu+ mu-) (KS0 -> pi+ pi-)"
    })
Bd2JpsiKSTuple.addTool(TupleToolDecay, name="B0")
Bd2JpsiKSTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
Bd2JpsiKSTuple.B0.addTool(LoKi_SpecificToB)

Bd2JpsiKSTuple.B0.addTool(TupleToolTISTOS)
Bd2JpsiKSTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
Bd2JpsiKSTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
Bd2JpsiKSTuple.B0.ToolList+=["TupleToolTISTOS"]
Bd2JpsiKSTuple.B0.ToolList+=["TupleToolMCBackgroundInfo"]

Bd2JpsiKSPrescaledTuple.addBranches({
    "B0" :  "^(B0 -> (J/psi(1S) -> mu+ mu-) (KS0 -> pi+ pi-))",
    "J_psi_1S" :  "B0 -> ^(J/psi(1S) -> mu+ mu-) (KS0 -> pi+ pi-)"
    })
Bd2JpsiKSPrescaledTuple.addTool(TupleToolDecay, name="B0")
Bd2JpsiKSPrescaledTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
Bd2JpsiKSPrescaledTuple.B0.addTool(LoKi_SpecificToB)

Bd2JpsiKSPrescaledTuple.B0.addTool(TupleToolTISTOS)
Bd2JpsiKSPrescaledTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
Bd2JpsiKSPrescaledTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
Bd2JpsiKSPrescaledTuple.B0.ToolList+=["TupleToolTISTOS"]
Bd2JpsiKSPrescaledTuple.B0.ToolList+=["TupleToolMCBackgroundInfo"]

Bd2JpsiKSTuple.addTool(TupleToolDecay, name="J_psi_1S")
Bd2JpsiKSTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
Bd2JpsiKSTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

"""

"""
#############################################################
##################### LbTuple #############################
LbTuple.addBranches({
    "Lambda_b0" :  "[^(Lambda_b0 -> (Lambda0 -> p+ pi-) (J/psi(1S) -> mu+ mu-))]CC",
    "J_psi_1S" :  "[Lambda_b0 -> (Lambda0 -> p+ pi-) ^(J/psi(1S) -> mu+ mu-) ]CC"
    })
LbTuple.addTool(TupleToolDecay, name="Lambda_b0")
LbTuple.Lambda_b0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
LbTuple.Lambda_b0.addTool(LoKi_SpecificToB)

LbTuple.Lambda_b0.addTool(TupleToolTISTOS)
LbTuple.Lambda_b0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
LbTuple.Lambda_b0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
LbTuple.Lambda_b0.ToolList+=["TupleToolTISTOS"]
LbTuple.Lambda_b0.ToolList+=["TupleToolMCBackgroundInfo"]
###########################################################
"""

TupleSeq.ModeOR          = True
TupleSeq.ShortCircuit    = False

###########################################################
locations = []
for tupleAlg in TupleSeq.Members:
    locations.extend(tupleAlg.Inputs)

from Configurables import LoKi__VoidFilter as VoidFilter
locationFilter = VoidFilter("LocationFilter")
locationFilter.Code = '(' + ' | '.join(("(CONTAINS('%s') > 0)" % l for l in locations)) + ')'

from Configurables import TrackSmearState
# smear proto particles and their associated tracks
smear = TrackSmearState("TrackSmearState")

from Configurables import EventTuple , TupleToolTrigger
evtTuple                = EventTuple()
evtTuple.ToolList      += [ "TupleToolEventInfo", "TupleToolTrigger"]

seqB2JpsiX               = GaudiSequencer('seqB2JpsiX')
##seqB2JpsiX.Members       = [locationFilter, evtTuple, TupleSeq]
#ol PK, seqB2JpsiX.Members       = [locationFilter, evtTuple, smear, TupleSeq]
seqB2JpsiX.Members       = [locationFilter, CheckPV(), evtTuple, smear, TupleSeq]

from FileStager.Configuration import configureFileStager
configureFileStager()

DaVinci().DDDBtag   = "Sim08-20130503"
DaVinci().CondDBtag = "Sim08-20130503-vc-mu100"


## DaVinci().EvtMax        =  5000
DaVinci().EvtMax        =  -1
DaVinci().SkipEvents    =  0
DaVinci().Lumi=False
DaVinci().DataType     = '2011'
DaVinci().Simulation = True

DaVinci().TupleFile       = "DTT.root"  # Ntuple
DaVinci().UserAlgorithms  = [seqB2JpsiX]

