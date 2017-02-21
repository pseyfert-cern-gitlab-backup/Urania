# Copyright Konstantin Gizdov 2016
from os import environ
from GaudiKernel.SystemOfUnits import *
from Gaudi.Configuration import *
from Configurables import GaudiSequencer, CombineParticles, OfflineVertexFitter, TupleToolGeometry
from Configurables import DecayTreeTuple, EventTuple, TupleToolTrigger, TupleToolTISTOS, FilterDesktop
from Configurables import BackgroundCategory, TupleToolDecay, TupleToolVtxIsoln, TupleToolPid, EventCountHisto, TupleToolRecoStats
from Configurables import LoKi__Hybrid__TupleTool, TupleToolVeto, TupleToolTrackPosition, TupleToolTrackInfo
from Configurables import TupleToolTagging, TupleToolL0Data, TupleToolL0Calo, TupleToolP2VV, TupleToolMCTruth, TupleToolMCBackgroundInfo

l0_lines = [ 'L0MuonDecision'
           , 'L0DiMuonDecision'
           , 'L0GlobalDecision' ]

hlt1_lines = [ 'Hlt1TrackMVADecision'
             , 'Hlt1TwoTrackMVADecision'
             , 'Hlt1TrackMVALooseDecision'
             , 'Hlt1TwoTrackMVALooseDecision'
             , 'Hlt1TrackMuonDecision'
             , 'Hlt1TrackMuonMVADecision'
             , 'Hlt1DiMuonHighMassDecision'
             , 'Hlt1DiMuonLowMassDecision'
             , 'Hlt1SingleMuonHighPTDecision'
             , 'Hlt1DiMuonNoL0Decision'
             , 'Hlt1L0AnyDecision'
             , 'Hlt1GlobalDecision' ]

hlt2_lines = [ 'Hlt2Topo2BodyDecision'
             , 'Hlt2Topo3BodyDecision'
             , 'Hlt2Topo4BodyDecision'
             , 'Hlt2TopoMu2BodyDecision'
             , 'Hlt2TopoMu3BodyDecision'
             , 'Hlt2TopoMu4BodyDecision'
             , 'Hlt2TopoMuMu2BodyDecision'
             , 'Hlt2TopoMuMu3BodyDecision'
             , 'Hlt2TopoMuMu4BodyDecision'
             , 'Hlt2SingleMuonDecision'
             , 'Hlt2SingleMuonHighPTDecision'
             , 'Hlt2SingleMuonLowPTDecision'
             , 'Hlt2SingleMuonRareDecision'
             , 'Hlt2SingleMuonVHighPTDecision'
             , 'Hlt2DiMuonDecision'
             , 'Hlt2DiMuonJPsiDecision'
             , 'Hlt2DiMuonDetachedDecision'
             , 'Hlt2DiMuonDetachedHeavyDecision'
             , 'Hlt2DiMuonDetachedJPsiDecision'
             , 'Hlt2DiMuonDetachedPsi2SDecision' ]

mtl = l0_lines + hlt1_lines + hlt2_lines

location  = '/Event/AllStreams/Phys/BetaSBs2JpsiPhiDetachedLine/Particles'
from PhysSelPython.Wrappers import AutomaticData
b2jpsiphi_selection = AutomaticData( location )

tl = ["TupleToolTrigger"
     ,"TupleToolGeometry"
     ,"TupleToolKinematic"
     ,"TupleToolPropertime"
     ,"TupleToolPrimaries"
     ,"TupleToolEventInfo"
     ,"TupleToolTrackInfo"
     ,"TupleToolTagging"
     ,"TupleToolPid"
     ,"TupleToolANNPID"
     ,"TupleToolRecoStats"
     ,"TupleToolTrackPosition"
     ,"TupleToolL0Calo"
     ,"TupleToolL0Data"
     ,"TupleToolTISTOS"
     ,"TupleToolMCTruth"
     ,"TupleToolMCBackgroundInfo"
     ]

from GaudiConfUtils.ConfigurableGenerators import DecayTreeTuple as TUPLE
from PhysSelPython.Wrappers                import SimpleSelection
rd_selection = SimpleSelection (
    'Tuple'
    , TUPLE
    , [ b2jpsiphi_selection ]
    ## Properties:
    , Decay    = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"
    , ToolList = tl
    , Branches = {
            "B"       : "B_s0 ->  (J/psi(1S) ->  mu+  mu-)  (phi(1020) ->  K+  K-)",
            "Jpsi"    : "B_s0 -> ^(J/psi(1S) ->  mu+  mu-)  (phi(1020) ->  K+  K-)",
            "muplus"  : "B_s0 ->  (J/psi(1S) -> ^mu+  mu-)  (phi(1020) ->  K+  K-)",
            "muminus" : "B_s0 ->  (J/psi(1S) ->  mu+ ^mu-)  (phi(1020) ->  K+  K-)",
            "X"       : "B_s0 ->  (J/psi(1S) ->  mu+  mu-) ^(phi(1020) ->  K+  K-)",
            "hplus"   : "B_s0 ->  (J/psi(1S) ->  mu+  mu-)  (phi(1020) -> ^K+  K-)",
            "hminus"  : "B_s0 ->  (J/psi(1S) ->  mu+  mu-)  (phi(1020) ->  K+ ^K-)"
        }
    )

tuple_B2jpsiphi = rd_selection.algorithm()

tuples = [ tuple_B2jpsiphi ]

for particle in ["B", "Jpsi", "muplus", "muminus", "X", "hplus", "hminus"]:
    tuple_B2jpsiphi.addTool(TupleToolDecay, name = particle)

tuple_B2jpsiphi.ReFitPVs = True

tuple_B2jpsiphi.ToolList += tl

TupleToolTrackPosition       = TupleToolTrackPosition('TupleToolTrackPosition')
TupleToolTrackPosition.Z     = 7500.
TupleToolRecoStats           = TupleToolRecoStats('TupleToolRecoStats')
TupleToolRecoStats.Verbose   = True
TupleToolGeometry            = TupleToolGeometry('TupleToolGeometry')
TupleToolGeometry.RefitPVs   = True
TupleToolGeometry.Verbose    = True
TupleToolTrackInfo           = TupleToolTrackInfo('TupleToolTrackInfo')
TupleToolTrackInfo.Verbose   = True
TupleToolTagging             = TupleToolTagging('TupleToolTagging')
TupleToolTagging.Verbose     = True
TupleToolTrigger             = TupleToolTrigger('TupleToolTrigger')
TupleToolTrigger.Verbose     = True
TupleToolTrigger.TriggerList = tl
TupleToolTrigger.OutputLevel = 6
tuple_B2jpsiphi.addTool(TupleToolTrackInfo)
tuple_B2jpsiphi.addTool(TupleToolTagging)
tuple_B2jpsiphi.addTool(TupleToolTrackPosition)
tuple_B2jpsiphi.addTool(TupleToolRecoStats)
tuple_B2jpsiphi.addTool(TupleToolGeometry)
tuple_B2jpsiphi.addTool(TupleToolTrigger)

from Configurables import LoKi__Hybrid__TupleTool
LoKi_Jpsi = LoKi__Hybrid__TupleTool("LoKi_Jpsi")
LoKi_Jpsi.Variables = {
        "ETA"         : "ETA",
        "Y"           : "Y",
        "LV01"        : "LV01",
        "LV02"        : "LV02",
        "LOKI_FDCHI2" : "BPVVDCHI2",
        "LOKI_FDS"    : "BPVDLS",
        "LOKI_DIRA"   : "BPVDIRA"
        }

tuple_B2jpsiphi.Jpsi.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_Jpsi"]
tuple_B2jpsiphi.Jpsi.addTool(LoKi_Jpsi)

tuple_B2jpsiphi.Jpsi.ToolList += [ "TupleToolTISTOS" ]
tuple_B2jpsiphi.Jpsi.addTool(TupleToolTISTOS, name = "TupleToolTISTOS" )
tuple_B2jpsiphi.Jpsi.TupleToolTISTOS.Verbose = True
tuple_B2jpsiphi.Jpsi.TupleToolTISTOS.TriggerList = mtl

# Change TOSFracMu for Jpsi
from Configurables import TriggerTisTos
tuple_B2jpsiphi.Jpsi.TupleToolTISTOS.addTool(TriggerTisTos())
tuple_B2jpsiphi.Jpsi.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
tuple_B2jpsiphi.Jpsi.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
tuple_B2jpsiphi.Jpsi.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.

# RecoStats to filling SpdMult, etc
tuple_B2jpsiphi.addTool(TupleToolRecoStats, name = "TupleToolRecoStats")
tuple_B2jpsiphi.TupleToolRecoStats.Verbose = True

tuple_B2jpsiphi.addTool(TupleToolDecay, name = 'B')
LoKi_B = LoKi__Hybrid__TupleTool("LoKi_B")
LoKi_B.Variables = {
        "JpsiPhiMass"          : "WM('J/psi(1S)','phi(1020)')",
        "ETA"                  : "ETA",
        "Y"                    : "Y",
        "LV01"                 : "LV01",
        "LV02"                 : "LV02",
        "LOKI_FDCHI2"          : "BPVVDCHI2",
        "LOKI_FDS"             : "BPVDLS",
        "LOKI_DIRA"            : "BPVDIRA",
        "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
        "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )",
        "LOKI_DTF_CHI2NDOF"    : "DTF_CHI2NDOF( True )",
        "LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )",
        "LOKI_MASS_JpsiConstr" : "DTF_FUN ( M , True , 'J/psi(1S)' )" ,
        "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )"
        }

tuple_B2jpsiphi.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_B"]
tuple_B2jpsiphi.B.addTool(LoKi_B)

LoKi_muon = LoKi__Hybrid__TupleTool("LoKi_muon")
LoKi_muon.Variables = {
        "LOKI_ETA": "ETA",
        "LOKI_Y"  : "Y",
        }
tuple_B2jpsiphi.muplus.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_muon"]
tuple_B2jpsiphi.muminus.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_muon"]
tuple_B2jpsiphi.muplus.addTool(LoKi_muon)
tuple_B2jpsiphi.muminus.addTool(LoKi_muon)

# refit with mass constraint
from Configurables import TupleToolDecayTreeFitter

tuple_B2jpsiphi.B.ToolList += ["TupleToolDecayTreeFitter/ConstJpsi"]
tuple_B2jpsiphi.B.addTool(TupleToolDecayTreeFitter("ConstJpsi"))
tuple_B2jpsiphi.B.ConstJpsi.Verbose = True
tuple_B2jpsiphi.B.ConstJpsi.UpdateDaughters = True
tuple_B2jpsiphi.B.ConstJpsi.constrainToOriginVertex = True
tuple_B2jpsiphi.B.ConstJpsi.daughtersToConstrain = ["J/psi(1S)"]

tuple_B2jpsiphi.B.ToolList += ["TupleToolDecayTreeFitter/ConstJpsiNoPV"]
tuple_B2jpsiphi.B.addTool(TupleToolDecayTreeFitter("ConstJpsiNoPV"))
tuple_B2jpsiphi.B.ConstJpsiNoPV.Verbose = True
tuple_B2jpsiphi.B.ConstJpsiNoPV.UpdateDaughters = True
tuple_B2jpsiphi.B.ConstJpsiNoPV.constrainToOriginVertex = False
tuple_B2jpsiphi.B.ConstJpsiNoPV.daughtersToConstrain = ["J/psi(1S)"]

tuple_B2jpsiphi.B.ToolList += ["TupleToolDecayTreeFitter/ConstBJpsi"]
tuple_B2jpsiphi.B.addTool(TupleToolDecayTreeFitter("ConstBJpsi"))
tuple_B2jpsiphi.B.ConstBJpsi.Verbose = True
tuple_B2jpsiphi.B.ConstBJpsi.UpdateDaughters = True
tuple_B2jpsiphi.B.ConstBJpsi.constrainToOriginVertex = True
tuple_B2jpsiphi.B.ConstBJpsi.daughtersToConstrain = ["B_s0", "J/psi(1S)"]

tuple_B2jpsiphi.B.ToolList += ["TupleToolDecayTreeFitter/ConstBJpsiNoPV"]
tuple_B2jpsiphi.B.addTool(TupleToolDecayTreeFitter("ConstBJpsiNoPV"))
tuple_B2jpsiphi.B.ConstBJpsiNoPV.Verbose = True
tuple_B2jpsiphi.B.ConstBJpsiNoPV.UpdateDaughters = True
tuple_B2jpsiphi.B.ConstBJpsiNoPV.constrainToOriginVertex = False
tuple_B2jpsiphi.B.ConstBJpsiNoPV.daughtersToConstrain = ["B_s0", "J/psi(1S)"]

### Backgrounds
# B -> KplusPiMuMu
tuple_B2jpsiphi.B.ToolList +=  ["TupleToolDecayTreeFitter/B2KpPiJpsi"]
B2KpPiJpsi = TupleToolDecayTreeFitter("B2KpPiJpsi",
                                      Verbose=True,
                                      Substitutions = {
                                          'Beauty -> Meson (phi(1020) -> ^K+ X-)': 'pi+'
                                      },
                                      daughtersToConstrain = [ "J/psi(1S)" ],
                                      constrainToOriginVertex = True
                                      )
tuple_B2jpsiphi.B.addTool(B2KpPiJpsi)

# B -> KminusPiMuMu
tuple_B2jpsiphi.B.ToolList +=  ["TupleToolDecayTreeFitter/B2KmPiJpsi"]
B2KmPiJpsi = TupleToolDecayTreeFitter("B2KmPiJpsi",
                                      Verbose=True,
                                      Substitutions = {
                                          'Beauty -> Meson (phi(1020) -> X+ ^K-)': 'pi-'
                                      },
                                      daughtersToConstrain = [ "J/psi(1S)" ],
                                      constrainToOriginVertex = True
                                      )
tuple_B2jpsiphi.B.addTool(B2KmPiJpsi)

# Lb -> pKMuMu (Kplus)
tuple_B2jpsiphi.B.ToolList +=  ["TupleToolDecayTreeFitter/pKMuMuKplus"]
pKMuMuKplus = TupleToolDecayTreeFitter("pKMuMuKplus" ,
                                       Verbose=True ,
                                       Substitutions = {
                                           'Beauty -> Meson (phi(1020) -> ^K+ X-)': 'p+'
                                       },
                                       daughtersToConstrain = [ "J/psi(1S)" ],
                                       constrainToOriginVertex = True
                                       )
tuple_B2jpsiphi.B.addTool(pKMuMuKplus)

# Lb -> pKMuMu (Kminus)
tuple_B2jpsiphi.B.ToolList +=  ["TupleToolDecayTreeFitter/pKMuMuKminus"]
pKMuMuKminus = TupleToolDecayTreeFitter("pKMuMuKminus",
                                        Verbose = True,
                                        Substitutions = {
                                            'Beauty -> Meson (phi(1020) -> X+ ^K-)': 'p~-'
                                        },
                                        daughtersToConstrain = [ "J/psi(1S)" ],
                                        constrainToOriginVertex = True
                                        )
tuple_B2jpsiphi.B.addTool(pKMuMuKminus)

### TISTOS
tuple_B2jpsiphi.B.ToolList += [ "TupleToolTISTOS" ]
tuple_B2jpsiphi.B.addTool(TupleToolTISTOS, name = "TupleToolTISTOS" )
tuple_B2jpsiphi.B.TupleToolTISTOS.Verbose = True
tuple_B2jpsiphi.B.TupleToolTISTOS.TriggerList = mtl

# change TOSFracMu for Bc (?)
from Configurables import TriggerTisTos
tuple_B2jpsiphi.B.TupleToolTISTOS.addTool(TriggerTisTos())
tuple_B2jpsiphi.B.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
tuple_B2jpsiphi.B.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
tuple_B2jpsiphi.B.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.

# specific tagging tuple tool
tuple_B2jpsiphi.B.ToolList += [ "TupleToolTagging" ]
tuple_B2jpsiphi.B.addTool(TupleToolTagging, name = "TupleToolTagging" )
tuple_B2jpsiphi.B.TupleToolTagging.Verbose = True
tuple_B2jpsiphi.B.TupleToolTagging.StoreTaggersInfo = True

# event tuple
from Configurables import LoKi__Hybrid__EvtTupleTool
LoKi_EvtTuple=LoKi__Hybrid__EvtTupleTool("LoKi_EvtTuple")
LoKi_EvtTuple.VOID_Variables = {
    "LoKi_nPVs"              : "CONTAINS('Rec/Vertex/Primary')",
    "LoKi_nSpdMult"          : "CONTAINS('Raw/Spd/Digits')",
    "LoKi_nVeloClusters"     : "CONTAINS('Raw/Velo/Clusters')",
    "LoKi_nVeloLiteClusters" : "CONTAINS('Raw/Velo/LiteClusters')",
    "LoKi_nITClusters"       : "CONTAINS('Raw/IT/Clusters')",
    "LoKi_nTTClusters"       : "CONTAINS('Raw/TT/Clusters')",
    "LoKi_nOThits"           : "CONTAINS('Raw/OT/Times')"
    }

tuple_B2jpsiphi.ToolList += ["LoKi::Hybrid::EvtTupleTool/LoKi_EvtTuple"]
tuple_B2jpsiphi.addTool(LoKi_EvtTuple)


TupleToolP2VV_BsDetached             = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_BsDetached.Calculator  = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_BsDetached.OutputLevel = 6
tuple_B2jpsiphi.B.addTool(TupleToolP2VV_BsDetached)
tuple_B2jpsiphi.B.ToolList          += ["TupleToolP2VV/TupleToolP2VV_Bs"]

MCTruth = TupleToolMCTruth()
MCTruth.ToolList = [
    "MCTupleToolKinematic",
    "MCTupleToolHierarchy",
    "MCTupleToolPID"
]

tuple_B2jpsiphi.addTool(MCTruth)

## Force update of CondDB to use proper momentum scaling
from Configurables import CondDB
CondDB(LatestGlobalTagByDataType = '2016')

## primary vertex selection
from Configurables import CheckPV
checkpv = CheckPV()

from PhysSelPython.Wrappers import SelectionSequence
rd_SEQ = SelectionSequence('DATA', rd_selection)

from Configurables import TrackSmearState
smear = TrackSmearState('TrackSmearState')

# from GaudiConf import IOHelper
# # Use the local input data
# IOHelper().inputFiles([
#     './00058167_00000095_3.AllStreams.dst'
# ], clear=True)

########################################################################
from Configurables import DaVinci
DaVinci().UserAlgorithms = [checkpv, smear, rd_SEQ.sequence()]  # two trees, for reco and gene information
DaVinci().DataType       = "2016"
DaVinci().EvtMax         = -1                                   # Number of events
DaVinci().InputType      = 'DST'
DaVinci().PrintFreq      = 1000
DaVinci().SkipEvents     = 0                                    # Events to skip
DaVinci().HistogramFile  = "DVHistos.root"                      # Histogram file
DaVinci().TupleFile      = "BsJpsiPhi.root"                     # Ntuple
DaVinci().Simulation     = True
DaVinci().Lumi           = False
