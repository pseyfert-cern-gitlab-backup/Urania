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
   1- job = 'Grid' to pass on grid mode, where there is a special recepie so the job pass with no problems,
      job = ''     to pass interactivly with real data dsts
      job = 'MC'   to pass on MC dsts: check the correct B inputLocation!
   2- Outputlevel = 1 , 2 , 3, 4 ,5 or 6 verbosity level (1 to show all messages from all tools , 6 shows just FATAL errors )
      to be set to 6 on grid, avoid unnecessary waste of time/space.
   3- Trigger(TisTos or not) tool is configuered to take a specific lines, those lines change with tcks,
      this list should be an input variable       
"""
# __author__ = "Basem Khanji, Emilie Maurice, Olivier Leroy (khanji@cppm.in2p3.fr)"


import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from Configurables import (GaudiSequencer,
                           FilterDesktop,
                           CombineParticles,
                           OfflineVertexFitter,
			   FitDecayTrees
                           )
from Configurables import DaVinci

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import CheckPV
from Configurables import (DecayTreeTuple,TupleToolDecay,TupleToolVtxIsoln ,
                           LoKi__Hybrid__TupleTool,TupleToolTrigger,TupleToolTagging,
                           TupleToolP2VV,TupleToolTISTOS,BTagging,
#                           PrintDecayTree,PrintDecayTreeTool )
                           PrintDecayTree,PrintDecayTreeTool, TupleToolTrackPosition, TupleToolRecoStats )

"""
Stripping Bq->JpsiX
"""

job = 'Grid' 
outputlevel = 6

'''
 | BuBdBsSelection/Phys/Bd2JpsiKs/Particles                                              |      570 |     0.9+-0.0    | 0.3     |    0 | 2      |
 | BuBdBsSelection/Phys/Bd2JpsiKsPrescaled/Particles                                     |     2501 |     1.0+-0.0    | 0.2     |    0 | 2      |
 | BuBdBsSelection/Phys/Bd2JpsiKstar/Particles                                           |     8418 |     1.3+-0.0    | 0.9     |    0 | 11     |
 | BuBdBsSelection/Phys/Bd2JpsiKstarPrescaled/Particles                                  |     9146 |     1.8+-0.0    | 1.3     |    0 | 19     |
 | BuBdBsSelection/Phys/Bs2JpsiPhi/Particles                                             |     3043 |     1.1+-0.0    | 0.6     |    0 | 6      |
 | BuBdBsSelection/Phys/Bs2JpsiPhiPrescaled/Particles                                    |    12365 |     1.3+-0.0    | 0.7     |    0 | 12     |
 | BuBdBsSelection/Phys/Bu2JpsiK/Particles                                               |     8561 |     1.1+-0.0    | 0.5     |    0 | 6      |
 | BuBdBsSelection/Phys/Bu2JpsiKPrescaled/Particles                                      |    15350 |     1.4+-0.0    | 0.8     |    0 | 9      |
 | BuBdBsSelection/Phys/Lb2JpsiL/Particles  
'''
##############################################################################################
##### SELECTIONS
##############################################################################################
seqB2JpsiX       = GaudiSequencer('seqB2JpsiX')
##############################################################################################
Bsdecaydcr        = "B_s0 -> (^J/psi(1S) => ^mu+ ^mu-) (^phi(1020) => ^K+ ^K-)"
# ol BsPartVtxlocation = "BuBdBsSelection/Phys/Bs2JpsiPhi/Particles"
BsPartVtxlocation = "/Event/Dimuon/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
# ol BsPartVtxlocationPrescaled = "/Event/Dimuon/Phys/Bs2JpsiPhiPrescaled/Particles"
BsPartVtxlocationPrescaled = "/Event/Dimuon/Phys/BetaSBs2JpsiPhiPrescaledLine/Particles"

Bddecaydcr        = "[B0 -> (^J/psi(1S) => ^mu+ ^mu-) (^K*(892)0 => ^K+ ^pi-)]cc"
#ol BdPartVtxlocation = "/Event/Dimuon/Phys/Bd2JpsiKstar/Particles"
#ol BdPartVtxlocationPrescaled = "/Event/Dimuon/Phys/Bd2JpsiKstarPrescaled/Particles"
BdPartVtxlocation = "/Event/Dimuon/Phys/BetaSBd2JpsiKstarDetachedLine/Particles"
BdPartVtxlocationPrescaled = "/Event/Dimuon/Phys/BetaSBd2JpsiKstarPrescaledLine/Particles"

Budecaydcr        = "[B+ -> (^J/psi(1S) => ^mu+ ^mu-) ^K+]cc"
#BuPartVtxlocation = "/Event/Dimuon/Phys/Bu2JpsiK/Particles"
#BuPartVtxlocationPrescaled = "/Event/Dimuon/Phys/Bu2JpsiKPrescaled/Particles"
BuPartVtxlocation = "/Event/Dimuon/Phys/BetaSBu2JpsiKDetachedLine/Particles"
BuPartVtxlocationPrescaled = "/Event/Dimuon/Phys/BetaSBu2JpsiKPrescaledLine/Particles"

BdKshortdecaydcr  = "B0 -> (^J/psi(1S)=> ^mu+ ^mu-) (^KS0 => ^pi+ ^pi-)"
BdKshortPartVtxlocation = "/Event/Dimuon/Phys/Bd2JpsiKs/Particles"
BdKshortPartVtxlocationPrescaled = "/Event/Dimuon/Phys/Bd2JpsiKsPrescaled/Particles"

Lbdecaydcr  = "[Lambda_b0 -> (^Lambda0 => ^p+ ^pi-) (^J/psi(1S) => ^mu+ ^mu-) ]cc"
LbPartVtxlocation = "/Event/Dimuon/Phys/Lb2JpsiL/Particles"
##############################################################################################


"""
# ==========================================================
# Flavour tagging.
# BTaggingAnalysis ntuple creation

from Configurables import BTaggingAnalysis, TriggerTisTos, TaggingUtilsChecker

taganaBu = BTaggingAnalysis("TagAnaBu")
taganaBu.Inputs = [ BuPartVtxlocation,"Phys/TaggingElectrons","Phys/TaggingMuons","Phys/TaggingPions"]
taganaBu.TagOutputLocation =  BuPartVtxlocation + "/FlavourTags"
taganaBu.ChoosePVCriterium = "bestPV"  # to be = to FT
taganaBu.PVReFit = True
taganaBu.BHypoCriterium = "MinChi2"
#taganaBu.ChoosePVCriterium = "PVbyIP"  # tuples
#tagana.BHypoCriterium = "MaximumPt"  #needed by CheatedSel
taganaBu.RequireTisTos = True
#tagana.SaveHlt1Lines = False  #require tistos
taganaBu.EnableMC = False

taganaBu.OutputLevel = 5
taganaBu.addTool( PhysDesktop )
taganaBu.PhysDesktop.OutputLevel = 5
taganaBu.addTool( TriggerTisTos )
taganaBu.TriggerTisTos.OutputLevel = 5
taganaBu.addTool( TaggingUtilsChecker )
taganaBu.TaggingUtilsChecker.OutputLevel = 5

# === Bs
taganaBs = taganaBu.clone("TagAnaBs")
taganaBs.Inputs = [ BsPartVtxlocation,"Phys/TaggingElectrons","Phys/TaggingMuons","Phys/TaggingPions"]
taganaBs.TagOutputLocation =  BsPartVtxlocation + "/FlavourTags"

# === Bd
taganaBd = taganaBu.clone("TagAnaBd")
taganaBd.Inputs = [ BdPartVtxlocation,"Phys/TaggingElectrons", "Phys/TaggingMuons","Phys/TaggingPions"]
taganaBd.TagOutputLocation =  BdPartVtxlocation + "/FlavourTags"


""" 



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
    ]
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
BsTuple.OutputLevel = 6

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
TupleToolTrigger.OutputLevel = 6
BsTuple.addTool(TupleToolTrigger)

# Now clone for the other lines
BuTuple = BsTuple.clone("BuTuple")
BuTuple.Inputs = [BuPartVtxlocation]

BuTuple.Decay          =  Budecaydcr
BuTuple.addTool(TupleToolGeometry)
BuTuple.addTool(TupleToolTrackInfo)

TupleSeq.Members      += [ BuTuple]



BdTuple = BsTuple.clone("BdTuple")
BdTuple.Inputs = [BdPartVtxlocation]
BdTuple.Decay          = Bddecaydcr
TupleSeq.Members      += [ BdTuple]

BdTuple.addTool(TupleToolGeometry)
BdTuple.addTool(TupleToolTrackInfo)

Bd2JpsiKSTuple = BsTuple.clone("Bd2JpsiKSTuple")
Bd2JpsiKSTuple.Inputs = [BdKshortPartVtxlocation]
Bd2JpsiKSTuple.Decay          = BdKshortdecaydcr
TupleSeq.Members      += [ Bd2JpsiKSTuple]

Bd2JpsiKSTuple.addTool(TupleToolGeometry)
Bd2JpsiKSTuple.addTool(TupleToolTrackInfo)

BsPrescaledTuple = BsTuple.clone("BsPrescaledTuple")
BsPrescaledTuple.Inputs = [BsPartVtxlocationPrescaled]
TupleSeq.Members      += [ BsPrescaledTuple]

BsPrescaledTuple.Decay          =  Bsdecaydcr
BsPrescaledTuple.addTool(TupleToolGeometry)
BsPrescaledTuple.addTool(TupleToolTrackInfo)

BuPrescaledTuple = BsTuple.clone("BuPrescaledTuple")
BuPrescaledTuple.Inputs = [BuPartVtxlocationPrescaled]

BuPrescaledTuple.Decay          =  Budecaydcr
BuPrescaledTuple.addTool(TupleToolGeometry)
BuPrescaledTuple.addTool(TupleToolTrackInfo)

TupleSeq.Members      += [ BuPrescaledTuple]



BdPrescaledTuple = BsTuple.clone("BdPrescaledTuple")
BdPrescaledTuple.Inputs = [BdPartVtxlocationPrescaled]
BdPrescaledTuple.Decay          = Bddecaydcr
TupleSeq.Members      += [ BdPrescaledTuple]

BdPrescaledTuple.addTool(TupleToolGeometry)
BdPrescaledTuple.addTool(TupleToolTrackInfo)

Bd2JpsiKSPrescaledTuple = BsTuple.clone("Bd2JpsiKSPrescaledTuple")
Bd2JpsiKSPrescaledTuple.Inputs = [BdKshortPartVtxlocationPrescaled]
Bd2JpsiKSPrescaledTuple.Decay          = BdKshortdecaydcr
TupleSeq.Members      += [ Bd2JpsiKSPrescaledTuple]

Bd2JpsiKSPrescaledTuple.addTool(TupleToolGeometry)
Bd2JpsiKSPrescaledTuple.addTool(TupleToolTrackInfo)

LbTuple = BsTuple.clone("LbTuple")
LbTuple.Inputs = [LbPartVtxlocation]
LbTuple.Decay          = Lbdecaydcr
TupleSeq.Members      += [ LbTuple]

LbTuple.addTool(TupleToolGeometry)
LbTuple.addTool(TupleToolTrackInfo)

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
BsTuple.Branches={
    "B_s0" :  "B_s0 : B_s0 -> (J/psi(1S) => mu+ mu-) (phi(1020) -> K+ K-)",
    "J_psi_1S" :  "B_s0 -> (^J/psi(1S) => mu+ mu-) (phi(1020) -> K+ K-)"
            }
BsTuple.addTool(TupleToolDecay, name="B_s0")
BsTuple.B_s0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTuple.B_s0.addTool(LoKi_SpecificToB)
TupleToolP2VV_Bs = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_Bs.Calculator = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_Bs.OutputLevel = 6
BsTuple.B_s0.addTool(TupleToolP2VV_Bs)
BsTuple.B_s0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_Bs"]

BsTuple.B_s0.addTool(TupleToolTISTOS)
from Configurables import TriggerTisTos
BsTuple.B_s0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BsTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.

BsTuple.B_s0.ToolList+=["TupleToolTISTOS"]

BsTuple.addTool(TupleToolDecay, name="J_psi_1S")
BsTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BsTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

# Prescaled line
BsPrescaledTuple.Branches={
    "B_s0" :  "B_s0 : B_s0 -> (J/psi(1S) => mu+ mu-) (phi(1020) -> K+ K-)",
    "J_psi_1S" :  "B_s0 -> (^J/psi(1S) => mu+ mu-) (phi(1020) -> K+ K-)"
            }
BsPrescaledTuple.addTool(TupleToolDecay, name="B_s0")
BsPrescaledTuple.B_s0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsPrescaledTuple.B_s0.addTool(LoKi_SpecificToB)
TupleToolP2VV_BsPrescaled = TupleToolP2VV('TupleToolP2VV_BsPrescaled')
TupleToolP2VV_BsPrescaled.Calculator = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_BsPrescaled.OutputLevel = 6
BsPrescaledTuple.B_s0.addTool(TupleToolP2VV_BsPrescaled)
BsPrescaledTuple.B_s0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_BsPrescaled"]

BsPrescaledTuple.B_s0.addTool(TupleToolTISTOS)
from Configurables import TriggerTisTos
BsPrescaledTuple.B_s0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BsPrescaledTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.

BsPrescaledTuple.B_s0.ToolList+=["TupleToolTISTOS"]

BsPrescaledTuple.addTool(TupleToolDecay, name="J_psi_1S")
BsPrescaledTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BsPrescaledTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

###########################################################

###########################################################
##################### BuTuple #############################
BuTuple.Branches={
    "Bplus" : "[B+]cc : [B+ -> (J/psi(1S) => mu+ mu-) K+]cc",
    "J_psi_1S" : "[B+ -> (^J/psi(1S) => mu+ mu-) K+]cc"
            }
BuTuple.addTool(TupleToolDecay, name="Bplus")
BuTuple.Bplus.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BuTuple.Bplus.addTool(LoKi_SpecificToB)

BuTuple.addTool(TupleToolGeometry)

BuTuple.Bplus.addTool(TupleToolTISTOS)
BuTuple.Bplus.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BuTuple.Bplus.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BuTuple.Bplus.ToolList+=["TupleToolTISTOS"]

BuTuple.addTool(TupleToolDecay, name="J_psi_1S")
BuTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BuTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

BuPrescaledTuple.Branches={
    "Bplus" : "[B+]cc : [B+ -> (J/psi(1S) => mu+ mu-) K+]cc",
    "J_psi_1S" : "[B+ -> (^J/psi(1S) => mu+ mu-) K+]cc"
            }
BuPrescaledTuple.addTool(TupleToolDecay, name="Bplus")
BuPrescaledTuple.Bplus.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BuPrescaledTuple.Bplus.addTool(LoKi_SpecificToB)

BuPrescaledTuple.addTool(TupleToolGeometry)

BuPrescaledTuple.Bplus.addTool(TupleToolTISTOS)
BuPrescaledTuple.Bplus.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BuPrescaledTuple.Bplus.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BuPrescaledTuple.Bplus.ToolList+=["TupleToolTISTOS"]

BuPrescaledTuple.addTool(TupleToolDecay, name="J_psi_1S")
BuPrescaledTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BuPrescaledTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

###########################################################

###########################################################
##################### BdTuple #############################
BdTuple.Branches={
    "B0" :  "[B0]cc : [B0 -> (J/psi(1S) => mu+ mu-) (K*(892)0 => K+ pi-)]cc",
    "J_psi_1S" :  "[B0 -> (^J/psi(1S) => mu+ mu-) (K*(892)0 => K+ pi-)]cc"
            }
BdTuple.addTool(TupleToolDecay, name="B0")
BdTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BdTuple.B0.addTool(LoKi_SpecificToB)
TupleToolP2VV_Bd = TupleToolP2VV('TupleToolP2VV_Bd')
TupleToolP2VV_Bd.Calculator = 'Bd2KstarMuMuAngleCalculator'
TupleToolP2VV_Bd.OutputLevel = 6
BdTuple.B0.addTool(TupleToolP2VV_Bd)
BdTuple.B0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_Bd"]

BdTuple.B0.addTool(TupleToolTISTOS)
BdTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BdTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BdTuple.B0.ToolList+=["TupleToolTISTOS"]

BdTuple.addTool(TupleToolDecay, name="J_psi_1S")
BdTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BdTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

# Prescaled
BdPrescaledTuple.Branches={
    "B0" :  "[B0]cc : [B0 -> (J/psi(1S) => mu+ mu-) (K*(892)0 => K+ pi-)]cc",
    "J_psi_1S" :  "[B0 -> (^J/psi(1S) => mu+ mu-) (K*(892)0 => K+ pi-)]cc"
            }
BdPrescaledTuple.addTool(TupleToolDecay, name="B0")
BdPrescaledTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BdPrescaledTuple.B0.addTool(LoKi_SpecificToB)
TupleToolP2VV_BdPrescaled = TupleToolP2VV('TupleToolP2VV_BdPrescaled')
TupleToolP2VV_BdPrescaled.Calculator = 'Bd2KstarMuMuAngleCalculator'
TupleToolP2VV_BdPrescaled.OutputLevel = 6
BdPrescaledTuple.B0.addTool(TupleToolP2VV_Bd)
BdPrescaledTuple.B0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_BdPrescaled"]

BdPrescaledTuple.B0.addTool(TupleToolTISTOS)
BdPrescaledTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BdPrescaledTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BdPrescaledTuple.B0.ToolList+=["TupleToolTISTOS"]

BdPrescaledTuple.addTool(TupleToolDecay, name="J_psi_1S")
BdPrescaledTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
BdPrescaledTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

############################################################
##################### Bd2JpsiKSTuple #############################
Bd2JpsiKSTuple.Branches={
    "B0" :  "[B0]cc : B0 -> (J/psi(1S) => mu+ mu-) (KS0 => pi+ pi-)",
    "J_psi_1S" :  "B0 -> (^J/psi(1S) => mu+ mu-) (KS0 => pi+ pi-)"
            }
Bd2JpsiKSTuple.addTool(TupleToolDecay, name="B0")
Bd2JpsiKSTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
Bd2JpsiKSTuple.B0.addTool(LoKi_SpecificToB)

Bd2JpsiKSTuple.B0.addTool(TupleToolTISTOS)
Bd2JpsiKSTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
Bd2JpsiKSTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
Bd2JpsiKSTuple.B0.ToolList+=["TupleToolTISTOS"]

Bd2JpsiKSTuple.addTool(TupleToolDecay, name="J_psi_1S")
Bd2JpsiKSTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
Bd2JpsiKSTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

Bd2JpsiKSPrescaledTuple.Branches={
    "B0" :  "[B0]cc : B0 -> (J/psi(1S) => mu+ mu-) (KS0 => pi+ pi-)",
    "J_psi_1S" :  "B0 -> (^J/psi(1S) => mu+ mu-) (KS0 => pi+ pi-)"
            }
Bd2JpsiKSPrescaledTuple.addTool(TupleToolDecay, name="B0")
Bd2JpsiKSPrescaledTuple.B0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
Bd2JpsiKSPrescaledTuple.B0.addTool(LoKi_SpecificToB)

Bd2JpsiKSPrescaledTuple.B0.addTool(TupleToolTISTOS)
Bd2JpsiKSPrescaledTuple.B0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
Bd2JpsiKSPrescaledTuple.B0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
Bd2JpsiKSPrescaledTuple.B0.ToolList+=["TupleToolTISTOS"]

Bd2JpsiKSPrescaledTuple.addTool(TupleToolDecay, name="J_psi_1S")
Bd2JpsiKSPrescaledTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
Bd2JpsiKSPrescaledTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

#############################################################
##################### LbTuple #############################
LbTuple.Branches={
    "Lambda_b0" :  "[Lambda_b0]cc : [Lambda_b0 -> (Lambda0 => p+ pi-) (J/psi(1S) => mu+ mu-) ]cc",
    "J_psi_1S" :  "[Lambda_b0 -> (Lambda0 => p+ pi-) (^J/psi(1S) => mu+ mu-) ]cc"
            }
LbTuple.addTool(TupleToolDecay, name="Lambda_b0")
LbTuple.Lambda_b0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
LbTuple.Lambda_b0.addTool(LoKi_SpecificToB)

LbTuple.Lambda_b0.addTool(TupleToolTISTOS)
LbTuple.Lambda_b0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
LbTuple.Lambda_b0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
LbTuple.Lambda_b0.ToolList+=["TupleToolTISTOS"]

LbTuple.addTool(TupleToolDecay, name="J_psi_1S")
LbTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToJpsi"]
LbTuple.J_psi_1S.addTool(LoKi_SpecificToJpsi)

###########################################################
TupleSeq.ModeOR          = True
TupleSeq.ShortCircuit    = False

###########################################################
seqB2JpsiX.Members      += [ TupleSeq]
seqB2JpsiX.ModeOR        =   True
seqB2JpsiX.ShortCircuit  =   False

from Configurables import EventTuple , TupleToolTrigger
evtTuple                = EventTuple()
evtTuple.ToolList      += [ "TupleToolEventInfo", "TupleToolTrigger"]
DaVinci().EvtMax        =  -1
#DaVinci().EvtMax        =  10000
DaVinci().SkipEvents    =  -1


# Data
#importOptions("$APPCONFIGOPTS/UseOracle.py")
# New condidtion Data base look at the bookeeping to check :
# Strip 12
#from Configurables import CondDB
#CondDB().UseLatestTags = ["2011"]
# 2011 real data:
#DaVinci().DDDBtag         = "head-20110914"
#DaVinci().CondDBtag       = "head-20110914"

# 2012 real data, strip20, reco14:
DaVinci().DataType     = '2012'
DaVinci().DDDBtag      = "dddb-20120831"
DaVinci().CondDBtag    =  "cond-20120831" 


#if job=='Grid':
#	from Configurables import CondDB
#	CondDB(UseOracle = True)
#	importOptions("$APPCONFIGOPTS/DisableLFC.py")
DaVinci().Lumi=True

# from a dimuon stripped file
#condDBTags :	[(DDDB, head-20110914), (LHCBCOND, head-20110914), (DQFLAGS, tt-20110126), (ONLINE, HEAD), (ONLINE, HEAD), (ONLINE, HEAD), (ONLINE, HEAD)]


"""
# MC
#DaVinci().Simulation = True
#DaVinci().DDDBtag   = "head-20100407"
#DaVinci().CondDBtag = "sim-20100429-vc-md100"
DaVinci().Lumi = True

# run HLT2 on Data
#DaVinci().Hlt             = True
#DaVinci().Hlt2Requires    = 'L0+Hlt1'
#DaVinci().HltThresholdSettings = 'Physics_320Vis_300L0_10Hlt1_Hlt2_Feb10'
"""


DaVinci().TupleFile       = "DTT.root"  # Ntuple
DaVinci().UserAlgorithms += [evtTuple, seqB2JpsiX ]
#DaVinci().UserAlgorithms += [ evtTuple , seqB2JpsiX, taganaBu, taganaBd, taganaBs ]  ??? I don't know if this is the best method.

