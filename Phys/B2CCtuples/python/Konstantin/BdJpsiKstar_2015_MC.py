# Copyright Konstantin Gizdov 2017
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

location  = '/Event/AllStreams/Phys/BetaSBd2JpsiKstarDetachedLine/Particles'
from PhysSelPython.Wrappers import AutomaticData
b2jpsikstar_selection = AutomaticData( location )

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
    , [ b2jpsikstar_selection ]
    ## Properties:
    , Decay    = "[B0 ->  ^(J/psi(1S) ->  ^mu+  ^mu-)  ^(K*(892)0 ->  ^K+  ^pi-)]CC"
    , ToolList = tl
    , Branches = {
            "B"       : "[B0 ->  (J/psi(1S) ->  mu+  mu-)  (K*(892)0 ->  K+  pi-)]CC",
            "Jpsi"    : "[B0 -> ^(J/psi(1S) ->  mu+  mu-)  (K*(892)0 ->  K+  pi-)]CC",
            "muplus"  : "[B0 ->  (J/psi(1S) -> ^mu+  mu-)  (K*(892)0 ->  K+  pi-)]CC",
            "muminus" : "[B0 ->  (J/psi(1S) ->  mu+ ^mu-)  (K*(892)0 ->  K+  pi-)]CC",
            "X"       : "[B0 ->  (J/psi(1S) ->  mu+  mu-) ^(K*(892)0 ->  K+  pi-)]CC",
            "hplus"   : "[B0 ->  (J/psi(1S) ->  mu+  mu-)  (K*(892)0 -> ^K+  pi-)]CC",
            "hminus"  : "[B0 ->  (J/psi(1S) ->  mu+  mu-)  (K*(892)0 ->  K+ ^pi-)]CC"
        }
    )
tuple_b2jpsikstar = rd_selection.algorithm()
tuples = [ tuple_b2jpsikstar ]

for particle in ["B", "Jpsi", "muplus", "muminus", "X", "hplus", "hminus"]:
    tuple_b2jpsikstar.addTool(TupleToolDecay, name = particle)

tuple_b2jpsikstar.ReFitPVs = True

tuple_b2jpsikstar.ToolList += tl

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
tuple_b2jpsikstar.addTool(TupleToolTrackInfo)
tuple_b2jpsikstar.addTool(TupleToolTagging)
tuple_b2jpsikstar.addTool(TupleToolTrackPosition)
tuple_b2jpsikstar.addTool(TupleToolRecoStats)
tuple_b2jpsikstar.addTool(TupleToolGeometry)
tuple_b2jpsikstar.addTool(TupleToolTrigger)

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

tuple_b2jpsikstar.Jpsi.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_Jpsi"]
tuple_b2jpsikstar.Jpsi.addTool(LoKi_Jpsi)

tuple_b2jpsikstar.Jpsi.ToolList += [ "TupleToolTISTOS" ]
tuple_b2jpsikstar.Jpsi.addTool(TupleToolTISTOS, name = "TupleToolTISTOS" )
tuple_b2jpsikstar.Jpsi.TupleToolTISTOS.Verbose = True
tuple_b2jpsikstar.Jpsi.TupleToolTISTOS.TriggerList = mtl

# Change TOSFracMu for Jpsi
from Configurables import TriggerTisTos
tuple_b2jpsikstar.Jpsi.TupleToolTISTOS.addTool(TriggerTisTos())
tuple_b2jpsikstar.Jpsi.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
tuple_b2jpsikstar.Jpsi.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
tuple_b2jpsikstar.Jpsi.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.

tuple_b2jpsikstar.addTool(TupleToolDecay, name = 'B')
LoKi_B = LoKi__Hybrid__TupleTool("LoKi_B")
LoKi_B.Variables = {
        "JpsiKstarMass"        : "WM('J/psi(1S)','K*(892)0')",
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

tuple_b2jpsikstar.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_B"]
tuple_b2jpsikstar.B.addTool(LoKi_B)

LoKi_muon = LoKi__Hybrid__TupleTool("LoKi_muon")
LoKi_muon.Variables = {
        "LOKI_ETA": "ETA",
        "LOKI_Y"  : "Y",
        }
tuple_b2jpsikstar.muplus.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_muon"]
tuple_b2jpsikstar.muminus.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_muon"]
tuple_b2jpsikstar.muplus.addTool(LoKi_muon)
tuple_b2jpsikstar.muminus.addTool(LoKi_muon)

# refit with mass constraint
from Configurables import TupleToolDecayTreeFitter

tuple_b2jpsikstar.B.ToolList += ["TupleToolDecayTreeFitter/ConstJpsi"]
tuple_b2jpsikstar.B.addTool(TupleToolDecayTreeFitter("ConstJpsi"))
tuple_b2jpsikstar.B.ConstJpsi.Verbose = True
tuple_b2jpsikstar.B.ConstJpsi.UpdateDaughters = True
tuple_b2jpsikstar.B.ConstJpsi.constrainToOriginVertex = True
tuple_b2jpsikstar.B.ConstJpsi.daughtersToConstrain = ["J/psi(1S)"]

tuple_b2jpsikstar.B.ToolList += ["TupleToolDecayTreeFitter/ConstJpsiNoPV"]
tuple_b2jpsikstar.B.addTool(TupleToolDecayTreeFitter("ConstJpsiNoPV"))
tuple_b2jpsikstar.B.ConstJpsiNoPV.Verbose = True
tuple_b2jpsikstar.B.ConstJpsiNoPV.UpdateDaughters = True
tuple_b2jpsikstar.B.ConstJpsiNoPV.constrainToOriginVertex = False
tuple_b2jpsikstar.B.ConstJpsiNoPV.daughtersToConstrain = ["J/psi(1S)"]

tuple_b2jpsikstar.B.ToolList += ["TupleToolDecayTreeFitter/ConstBJpsi"]
tuple_b2jpsikstar.B.addTool(TupleToolDecayTreeFitter("ConstBJpsi"))
tuple_b2jpsikstar.B.ConstBJpsi.Verbose = True
tuple_b2jpsikstar.B.ConstBJpsi.UpdateDaughters = True
tuple_b2jpsikstar.B.ConstBJpsi.constrainToOriginVertex = True
tuple_b2jpsikstar.B.ConstBJpsi.daughtersToConstrain = ["B0", "J/psi(1S)"]

tuple_b2jpsikstar.B.ToolList += ["TupleToolDecayTreeFitter/ConstBJpsiNoPV"]
tuple_b2jpsikstar.B.addTool(TupleToolDecayTreeFitter("ConstBJpsiNoPV"))
tuple_b2jpsikstar.B.ConstBJpsiNoPV.Verbose = True
tuple_b2jpsikstar.B.ConstBJpsiNoPV.UpdateDaughters = True
tuple_b2jpsikstar.B.ConstBJpsiNoPV.constrainToOriginVertex = False
tuple_b2jpsikstar.B.ConstBJpsiNoPV.daughtersToConstrain = ["B0", "J/psi(1S)"]

### Backgrounds
# B -> KplusPiMuMu
tuple_b2jpsikstar.B.ToolList +=  ["TupleToolDecayTreeFitter/Jpsipipi"]
Jpsipipi = TupleToolDecayTreeFitter("Jpsipipi",
                                    Verbose=True,
                                    Substitutions = {
                                      'Beauty -> Meson (K*(892)0  -> ^K+ X-)': 'pi+'
                                     ,'Beauty -> Meson (K*(892)~0 -> ^K- X+)': 'pi-'
                                    },
                                    daughtersToConstrain = [ "J/psi(1S)" ],
                                    constrainToOriginVertex = True
                                    )
tuple_b2jpsikstar.B.addTool(Jpsipipi)

# B -> KminusPiMuMu
tuple_b2jpsikstar.B.ToolList +=  ["TupleToolDecayTreeFitter/JpsiKK"]
JpsiKK = TupleToolDecayTreeFitter("JpsiKK",
                                  Verbose=True,
                                  Substitutions = {
                                    'Beauty -> Meson (K*(892)0  -> X+ ^pi-)': 'K-'
                                   ,'Beauty -> Meson (K*(892)~0 -> X- ^pi+)': 'K+'
                                  },
                                  daughtersToConstrain = [ "J/psi(1S)" ],
                                  constrainToOriginVertex = True
                                  )
tuple_b2jpsikstar.B.addTool(JpsiKK)

# Lb -> pKMuMu (Kplus)
tuple_b2jpsikstar.B.ToolList +=  ["TupleToolDecayTreeFitter/Jpsippi"]
Jpsippi = TupleToolDecayTreeFitter("Jpsippi" ,
                                   Verbose=True ,
                                   Substitutions = {
                                     'Beauty -> Meson (K*(892)0  -> ^K+ X-)': 'p+'
                                    ,'Beauty -> Meson (K*(892)~0 -> ^K- X+)': 'p~-'
                                   },
                                   daughtersToConstrain = [ "J/psi(1S)" ],
                                   constrainToOriginVertex = True
                                   )
tuple_b2jpsikstar.B.addTool(Jpsippi)

# Lb -> pKMuMu (Piminus)
tuple_b2jpsikstar.B.ToolList +=  ["TupleToolDecayTreeFitter/JpsipK"]
JpsipK = TupleToolDecayTreeFitter("JpsipK",
                                  Verbose = True,
                                  Substitutions = {
                                    'Beauty -> Meson (K*(892)0  -> X+ ^pi-)': 'p~-'
                                   ,'Beauty -> Meson (K*(892)~0 -> X- ^pi+)': 'p+'
                                  },
                                  daughtersToConstrain = [ "J/psi(1S)" ],
                                  constrainToOriginVertex = True
                                  )
tuple_b2jpsikstar.B.addTool(JpsipK)

tuple_b2jpsikstar.B.ToolList+=[ "TupleToolTISTOS" ]
tuple_b2jpsikstar.B.addTool(TupleToolTISTOS, name = "TupleToolTISTOS" )
tuple_b2jpsikstar.B.TupleToolTISTOS.Verbose = True
tuple_b2jpsikstar.B.TupleToolTISTOS.TriggerList = mtl

# change TOSFracMu for Bc (?)
from Configurables import TriggerTisTos
tuple_b2jpsikstar.B.TupleToolTISTOS.addTool(TriggerTisTos())
tuple_b2jpsikstar.B.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
tuple_b2jpsikstar.B.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
tuple_b2jpsikstar.B.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.

# specific tagging tuple tool
tuple_b2jpsikstar.B.ToolList+=[ "TupleToolTagging" ]
tuple_b2jpsikstar.B.addTool(TupleToolTagging, name = "TupleToolTagging" )
tuple_b2jpsikstar.B.TupleToolTagging.Verbose = True
tuple_b2jpsikstar.B.TupleToolTagging.StoreTaggersInfo = True

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

tuple_b2jpsikstar.ToolList+=["LoKi::Hybrid::EvtTupleTool/LoKi_EvtTuple"]
tuple_b2jpsikstar.addTool(LoKi_EvtTuple)

TupleToolP2VV_BdDetached             = TupleToolP2VV('TupleToolP2VV_Bd')
TupleToolP2VV_BdDetached.Calculator  = 'Bd2KstarMuMuAngleCalculator'
TupleToolP2VV_BdDetached.OutputLevel = 6
tuple_b2jpsikstar.B.addTool(TupleToolP2VV_BdDetached)
tuple_b2jpsikstar.B.ToolList        += ["TupleToolP2VV/TupleToolP2VV_Bd"]

MCTruth = TupleToolMCTruth()
MCTruth.ToolList = [
    "MCTupleToolKinematic",
    "MCTupleToolHierarchy",
    "MCTupleToolPID"
]

tuple_B2jpsiphi.addTool(MCTruth)

## Force update of CondDB to use proper momentum scaling
from Configurables import CondDB
CondDB(LatestGlobalTagByDataType = '2015')

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
DaVinci().DataType       = "2015"
DaVinci().EvtMax         = -1                                   # Number of events
DaVinci().InputType      = 'DST'
DaVinci().PrintFreq      = 1000
DaVinci().SkipEvents     = 0                                    # Events to skip
DaVinci().HistogramFile  = "DVHistos.root"                      # Histogram file
DaVinci().TupleFile      = "BdJpsiKstar.root"                   # Ntuple
DaVinci().Simulation     = True
DaVinci().Lumi           = False
