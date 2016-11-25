# C. Vazquez Sierra, Oct 2016

from GaudiKernel.SystemOfUnits import *
from Gaudi.Configuration import *
from Configurables import DaVinci, EventTuple, TupleToolRecoStats, TupleToolDecayTreeFitter, LoKi__Hybrid__EvtTupleTool, CheckPV
from Configurables import GaudiSequencer, OfflineVertexFitter, FitDecayTrees, CheckPV, TupleToolGeometry, TupleToolTrackInfo, TriggerTisTos
from Configurables import DecayTreeTuple, TupleToolDecay, TupleToolVtxIsoln, LoKi__Hybrid__TupleTool, TupleToolTrigger, TupleToolTagging
from Configurables import TupleToolP2VV, TupleToolTISTOS, BTagging, PrintDecayTree, PrintDecayTreeTool, TupleToolTrackPosition
from GaudiConfUtils.ConfigurableGenerators import FilterDesktop, CombineParticles
from PhysSelPython.Wrappers import Selection, DataOnDemand, SelectionSequence

dataType   = '2015'
isMC       = False
tupleName  = "DTT.root"

##### Trigger lines for TupleToolTrigger and TupleToolTISTOS

l0_lines   = [ 'L0PhysicsDecision'
             , 'L0MuonDecision'
             , 'L0DiMuonDecision'
             , 'L0MuonHighDecision'
             , 'L0HadronDecision'
             , 'L0ElectronDecision'
             , 'L0PhotonDecision'
             , 'L0MuonNoSPDDecision' ]

hlt1_lines = [ 'Hlt1DiMuonHighMassDecision' 
             , 'Hlt1DiMuonLowMassDecision' 
             , 'Hlt1SingleMuonNoIPDecision' 
             , 'Hlt1SingleMuonHighPTDecision' 
             , 'Hlt1SingleElectronNoIPDecision' 
             , "Hlt1TrackMuonMVADecision"
             , "Hlt1TwoTrackMVADecision"
             , 'Hlt1TrackAllL0TightDecision' 
             , 'Hlt1TrackMuonDecision' 
             , 'Hlt1TrackPhotonDecision' 
             , 'Hlt1TrackForwardPassThroughDecision' 
             , 'Hlt1TrackForwardPassThroughLooseDecision' 
             , 'Hlt1LumiDecision' 
             , 'Hlt1LumiMidBeamCrossingDecision' 
             , 'Hlt1MBNoBiasDecision' 
             , 'Hlt1CharmCalibrationNoBiasDecision' 
             , 'Hlt1MBMicroBiasVeloDecision' 
             , 'Hlt1MBMicroBiasTStationDecision' 
             , 'Hlt1L0AnyDecision' 
             , 'Hlt1L0AnyNoSPDDecision' 
             , 'Hlt1L0HighSumETJetDecision' 
             , 'Hlt1NoPVPassThroughDecision' 
             , 'Hlt1DiProtonDecision' 
             , 'Hlt1DiProtonLowMultDecision' 
             , 'Hlt1BeamGasNoBeamBeam1Decision' 
             , 'Hlt1BeamGasNoBeamBeam2Decision' 
             , 'Hlt1BeamGasBeam1Decision' 
             , 'Hlt1BeamGasBeam2Decision' 
             , 'Hlt1BeamGasCrossingEnhancedBeam1Decision' 
             , 'Hlt1BeamGasCrossingEnhancedBeam2Decision' 
             , 'Hlt1BeamGasCrossingForcedRecoDecision' 
             , 'Hlt1BeamGasCrossingForcedRecoFullZDecision' 
             , 'Hlt1BeamGasHighRhoVerticesDecision' 
             , 'Hlt1ODINTechnicalDecision' 
             , 'Hlt1Tell1ErrorDecision' 
             , 'Hlt1VeloClosingMicroBiasDecision' 
             , 'Hlt1VertexDisplVertexDecision' 
             , 'Hlt1BeamGasCrossingParasiticDecision' 
             , 'Hlt1ErrorEventDecision' 
             , 'Hlt1GlobalDecision'
             , 'Hlt1TrackMuonNoSPDDecision'
             , 'Hlt2SingleMuonNoSPDDecision'
             , 'Hlt1TrackMVADecision'
             , 'Hlt1TwoTrackMVADecision' ]

hlt2_lines = [ 'Hlt2SingleElectronTFLowPtDecision'
             , 'Hlt2SingleElectronTFHighPtDecision'
             , 'Hlt2DiElectronHighMassDecision'
             , 'Hlt2DiElectronBDecision'
             , 'Hlt2B2HHLTUnbiasedDecision'
             , 'Hlt2Topo2BodySimpleDecision'
             , 'Hlt2Topo3BodySimpleDecision'
             , 'Hlt2Topo4BodySimpleDecision'
             , 'Hlt2Topo2BodyBBDTDecision'
             , 'Hlt2Topo3BodyBBDTDecision'
             , 'Hlt2Topo4BodyBBDTDecision'
             , 'Hlt2TopoMu2BodyBBDTDecision'
             , 'Hlt2TopoMu3BodyBBDTDecision'
             , 'Hlt2TopoMu4BodyBBDTDecision'
             , 'Hlt2TopoE2BodyBBDTDecision'
             , 'Hlt2TopoE3BodyBBDTDecision'
             , 'Hlt2TopoE4BodyBBDTDecision'
             , 'Hlt2IncPhiDecision'
             , 'Hlt2IncPhiSidebandsDecision'
             , 'Hlt2MuonFromHLT1Decision'
             , 'Hlt2SingleMuonDecision'
             , 'Hlt2SingleMuonHighPTDecision'
             , 'Hlt2SingleMuonLowPTDecision'
             , 'Hlt2DiMuonDecision'
             , 'Hlt2DiMuonLowMassDecision'
             , 'Hlt2DiMuonJPsiDecision'
             , 'Hlt2DiMuonJPsiHighPTDecision'
             , 'Hlt2DiMuonPsi2SDecision'
             , 'Hlt2DiMuonBDecision'
             , 'Hlt2DiMuonZDecision'
             , 'Hlt2DiMuonDY1Decision'
             , 'Hlt2DiMuonDY2Decision'
             , 'Hlt2DiMuonDY3Decision'
             , 'Hlt2DiMuonDY4Decision'
             , 'Hlt2DiMuonDetachedDecision'
             , 'Hlt2DiMuonDetachedHeavyDecision'
             , 'Hlt2DiMuonDetachedJPsiDecision'
             , 'Hlt2DiMuonNoPVDecision'
             , 'Hlt2TriMuonDetachedDecision'
             , 'Hlt2TriMuonTauDecision'
             , 'Hlt2DiMuonDetachedPsi2SDecision'
             , 'Hlt2Topo2BodyDecision'
             , 'Hlt2Topo3BodyDecision'
             , 'Hlt2Topo4BodyDecision'
             , 'Hlt2TopoMu2BodyDecision'
             , 'Hlt2TopoMu3BodyDecision'
             , 'Hlt2TopoMu4BodyDecision' ]

trigger_list = l0_lines + hlt1_lines + hlt2_lines
tistos_list  = trigger_list

##### Selection 1: Bs->J/PsiPhi from detached muons and loose kaons

seqB2JpsiX    = GaudiSequencer('seqB2JpsiX')
Bsdecaydcr    = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"

#### phi(1020) -> K+ K-
KaonList  = DataOnDemand(Location = "/Event/Dimuon/Phys/StdAllLooseKaons/Particles")
Phi2KK    = CombineParticles(DecayDescriptors = ["phi(1020) -> K+ K-"],
                             DaughtersCuts = {},
                             CombinationCut = "in_range(1008,AM,1050)",
                             MotherCut = "in_range(1008,M,1050) & (VFASPF(VCHI2PDOF) < 25)",
                             ReFitPVs = True)
Phi2KKSel = Selection("Phi2KKSel", Algorithm = Phi2KK, RequiredSelections = [KaonList])
SeqPhi2KK = SelectionSequence("SeqPhi2KK", TopSelection = Phi2KKSel)

#### Bs -> J/Psi(1S) phi(1020)
Bs2JpsiPhi    = CombineParticles(DecayDescriptors = ["B_s0 -> J/psi(1S) phi(1020)"],
                              DaughtersCuts = {},
                              CombinationCut = "in_range(5200,AM,5550)",
                              MotherCut = "in_range(5200,M,5550) & (VFASPF(VCHI2PDOF) < 25)",
                              ReFitPVs = True)
JpsiList      = DataOnDemand(Location = "/Event/Dimuon/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles")
Bs2JpsiPhiSel = Selection("Bs2JpsiPhiSel", Algorithm = Bs2JpsiPhi, RequiredSelections = [JpsiList, Phi2KKSel])
SeqBs2JpsiPhi = SelectionSequence("SeqBs2JpsiPhi", TopSelection = Bs2JpsiPhiSel)

##### Selection 2: Bs->J/PsiPhi from the corresponding stripping line

BsPartVtxlocationStripping = "/Event/Dimuon/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
BsdecaydcrStripping        = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"

##### Tuple preparation 

TupleSeq          = GaudiSequencer('TupleSeq')

BsTuple           = DecayTreeTuple("BsTuple")
BsTuple.ToolList += [ "TupleToolTrigger"
                    , "TupleToolGeometry"
                    , "TupleToolKinematic"
                    , "TupleToolPropertime"
                    , "TupleToolPrimaries"
                    , "TupleToolEventInfo"
                    , "TupleToolTrackInfo"
                    , "TupleToolTagging"
                    , "TupleToolRecoStats"
                    , "TupleToolTrackPosition"
                    , "TupleToolPid"
                    , "TupleToolL0Data"
                    , "TupleToolL0Calo" ]

BsTuple.Inputs   = [SeqBs2JpsiPhi.outputLocation()]
BsTuple.Decay    = Bsdecaydcr
BsTuple.ReFitPVs = True

#### Adding tuple tools

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
TupleToolTrigger.TriggerList = trigger_list
TupleToolTrigger.OutputLevel = 6
BsTuple.addTool(TupleToolTrackInfo)
BsTuple.addTool(TupleToolTagging)
BsTuple.addTool(TupleToolTrackPosition)
BsTuple.addTool(TupleToolRecoStats)
BsTuple.addTool(TupleToolGeometry)
BsTuple.addTool(TupleToolTrigger)

TupleSeq.Members   += [BsTuple]

##### Cloning for stripping-line-based tuple

BsTupleStrip        = BsTuple.clone("BsTupleStrip")
BsTupleStrip.Inputs = [BsPartVtxlocationStripping]
BsTupleStrip.Decay  = BsdecaydcrStripping
BsTupleStrip.addTool(TupleToolTrackInfo)
#BsTupleStrip.addTool(TupleToolTagging)
#BsTupleStrip.addTool(TupleToolTrackPosition)
#BsTupleStrip.addTool(TupleToolRecoStats)
BsTupleStrip.addTool(TupleToolGeometry)
#BsTupleStrip.addTool(TupleToolTrigger)

TupleSeq.Members   += [BsTupleStrip]

#### Adding the tuple tools to the corresponding decays

BsTuple.Branches = { "B_s0"     : "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))"
                   , "J_psi_1S" :  "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"  }

### Global to all tracks

LoKiVariables = LoKi__Hybrid__TupleTool('LoKiVariables')
LoKiVariables.Variables = { "LOKI_ENERGY"     : "E"
                          , "LOKI_Y"          : "Y"
                          , "LOKI_ETA"        : "ETA"
                          , "LOKI_PHI"        : "PHI" }
BsTuple.addTool(LoKiVariables , name = 'LoKiVariables')
BsTuple.ToolList   += ['LoKi::Hybrid::TupleTool/LoKiVariables']
BsTuple.OutputLevel = 6

### Specific to Bs

LoKi_SpecificToB           = LoKi__Hybrid__TupleTool('LoKi_SpecificToB')
LoKi_SpecificToB.Variables =  { "LOKI_FDCHI2"          : "BPVVDCHI2"
                              , "LOKI_FDS"             : "BPVDLS"
                              , "LOKI_DIRA"            : "BPVDIRA"
                              , "LOKI_CosPolAngle_Dau1": "LV01"
                              , "LOKI_CosPolAngle_Dau2": "LV02"
                              , "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )"
                              , "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )"
                              , "LOKI_DTF_CHI2NDOF"    : "DTF_CHI2NDOF( True )"
                              , "LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )"
                              , "LOKI_MASS_JpsiConstr" : "DTF_FUN ( M , False , 'J/psi(1S)' )"
                              , "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )"
                              , "JpsiKMass"            : "WM('J/psi(1S)','phi(1020)')" }
BsTuple.addTool(TupleToolDecay, name = "B_s0")
BsTuple.B_s0.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTuple.B_s0.addTool(LoKi_SpecificToB)

TupleToolP2VV_Bs = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_Bs.Calculator  = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_Bs.OutputLevel = 6
BsTuple.B_s0.addTool(TupleToolP2VV_Bs)
BsTuple.B_s0.ToolList       += ["TupleToolP2VV/TupleToolP2VV_Bs"]

TupleToolTISTOS                                        = TupleToolTISTOS('TupleToolTISTOS')
TupleToolTISTOS.Verbose                                = True
TupleToolTISTOS.TriggerList                            = tistos_list
BsTuple.B_s0.addTool(TupleToolTISTOS)
BsTuple.B_s0.TupleToolTISTOS.addTool(TriggerTisTos, "TriggerTisTos")
BsTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BsTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
BsTuple.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.
BsTuple.B_s0.ToolList                                 += ["TupleToolTISTOS"]

BsTuple.B_s0.addTool(TupleToolTagging, name = "TupleToolTagging")
BsTuple.B_s0.TupleToolTagging.Verbose          = True
BsTuple.B_s0.TupleToolTagging.StoreTaggersInfo = True

### Specific to J/Psi

LoKi_Jpsi           = LoKi__Hybrid__TupleTool("LoKi_Jpsi")
LoKi_Jpsi.Variables = { "LV01"        : "LV01",
                        "LV02"        : "LV02",
                        "LOKI_FDCHI2" : "BPVVDCHI2",
                        "LOKI_FDS"    : "BPVDLS",
                        "LOKI_DIRA"   : "BPVDIRA" }
BsTuple.addTool(TupleToolDecay, name = "J_psi_1S")
BsTuple.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_Jpsi"]
BsTuple.J_psi_1S.addTool(LoKi_Jpsi)

BsTuple.J_psi_1S.addTool(TupleToolTISTOS)
BsTuple.J_psi_1S.TupleToolTISTOS.addTool(TriggerTisTos, "TriggerTisTos")
BsTuple.J_psi_1S.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BsTuple.J_psi_1S.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
BsTuple.J_psi_1S.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.
BsTuple.J_psi_1S.ToolList                                 += ["TupleToolTISTOS"]

### Re-fit with mass constraint

BsTuple.B_s0.ToolList += ["TupleToolDecayTreeFitter/MassFit"]
BsTuple.B_s0.ToolList += ["TupleToolDecayTreeFitter/PVFit"]

BsTuple.B_s0.addTool(TupleToolDecayTreeFitter("PVFit"))
BsTuple.B_s0.PVFit.Verbose                 = True
BsTuple.B_s0.PVFit.constrainToOriginVertex = True
BsTuple.B_s0.PVFit.daughtersToConstrain    = ["J/psi(1S)"]

BsTuple.B_s0.addTool(TupleToolDecayTreeFitter("MassFit"))
BsTuple.B_s0.MassFit.constrainToOriginVertex = False
BsTuple.B_s0.MassFit.Verbose                 = True
BsTuple.B_s0.MassFit.daughtersToConstrain    = ["J/psi(1S)"]

### Event tuple

LoKi_EvtTuple     = LoKi__Hybrid__EvtTupleTool("LoKi_EvtTuple")
LoKi_EvtTuple.VOID_Variables = { "LoKi_nPVs"                : "CONTAINS('Rec/Vertex/Primary')"
                               , "LoKi_nSpdMult"            : "CONTAINS('Raw/Spd/Digits')"
                               , "LoKi_nVeloClusters"       : "CONTAINS('Raw/Velo/Clusters')"
                               , "LoKi_nVeloLiteClusters"   : "CONTAINS('Raw/Velo/LiteClusters')"
                               , "LoKi_nITClusters"         : "CONTAINS('Raw/IT/Clusters')"
                               , "LoKi_nTTClusters"         : "CONTAINS('Raw/TT/Clusters')"
                               , "LoKi_nOThits"             : "CONTAINS('Raw/OT/Times')" }   
BsTuple.ToolList += ["LoKi::Hybrid::EvtTupleTool/LoKi_EvtTuple"]
BsTuple.addTool(LoKi_EvtTuple)

#### Repeating for stripping-line-based tuple

BsTupleStrip.Branches = { "B_s0"     : "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))"
                        , "J_psi_1S" :  "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"  }

### Global to all tracks

BsTupleStrip.addTool(LoKiVariables , name = 'LoKiVariables')
BsTupleStrip.ToolList   += ['LoKi::Hybrid::TupleTool/LoKiVariables']
BsTupleStrip.OutputLevel = 6

### Specific to Bs

BsTupleStrip.addTool(TupleToolDecay, name = "B_s0")
BsTupleStrip.B_s0.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTupleStrip.B_s0.addTool(LoKi_SpecificToB)

TupleToolP2VV_BsStrip             = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_BsStrip.Calculator  = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_BsStrip.OutputLevel = 6
BsTupleStrip.B_s0.addTool(TupleToolP2VV_BsStrip)
BsTupleStrip.B_s0.ToolList       += ["TupleToolP2VV/TupleToolP2VV_Bs"]

BsTupleStrip.B_s0.addTool(TupleToolTISTOS)
BsTupleStrip.B_s0.TupleToolTISTOS.addTool(TriggerTisTos, "TriggerTisTos")
BsTupleStrip.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BsTupleStrip.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
BsTupleStrip.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.
BsTupleStrip.B_s0.ToolList                                 += ["TupleToolTISTOS"]

BsTupleStrip.B_s0.addTool(TupleToolTagging, name = "TupleToolTagging")
BsTupleStrip.B_s0.TupleToolTagging.Verbose          = True
BsTupleStrip.B_s0.TupleToolTagging.StoreTaggersInfo = True

### Specific to J/Psi

BsTupleStrip.addTool(TupleToolDecay, name = "J_psi_1S")
BsTupleStrip.J_psi_1S.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_Jpsi"]
BsTupleStrip.J_psi_1S.addTool(LoKi_Jpsi)

BsTupleStrip.J_psi_1S.addTool(TupleToolTISTOS)
BsTupleStrip.J_psi_1S.TupleToolTISTOS.addTool(TriggerTisTos, "TriggerTisTos")
BsTupleStrip.J_psi_1S.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BsTupleStrip.J_psi_1S.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
BsTupleStrip.J_psi_1S.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.
BsTupleStrip.J_psi_1S.ToolList                                 += ["TupleToolTISTOS"]

### Re-fit with mass constraint

BsTupleStrip.B_s0.ToolList += ["TupleToolDecayTreeFitter/MassFit"]
BsTupleStrip.B_s0.ToolList += ["TupleToolDecayTreeFitter/PVFit"]

BsTupleStrip.B_s0.addTool(TupleToolDecayTreeFitter("PVFit"))
BsTupleStrip.B_s0.PVFit.Verbose                 = True
BsTupleStrip.B_s0.PVFit.constrainToOriginVertex = True
BsTupleStrip.B_s0.PVFit.daughtersToConstrain    = ["J/psi(1S)"]

BsTupleStrip.B_s0.addTool(TupleToolDecayTreeFitter("MassFit"))
BsTupleStrip.B_s0.MassFit.constrainToOriginVertex = False
BsTupleStrip.B_s0.MassFit.Verbose                 = True
BsTupleStrip.B_s0.MassFit.daughtersToConstrain    = ["J/psi(1S)"]

### Event tuple

BsTupleStrip.ToolList += ["LoKi::Hybrid::EvtTupleTool/LoKi_EvtTuple"]
BsTupleStrip.addTool(LoKi_EvtTuple)

##### Main body

#from GaudiConf import IOHelper
#IOHelper().inputFiles(['./00049575_00000024_1.dimuon.dst'], clear=True)

TupleSeq.ModeOR           = True
TupleSeq.ShortCircuit     = False

check_PV                  = CheckPV()
seqB2JpsiX.Members       += [TupleSeq]
seqB2JpsiX.ModeOR         = True
seqB2JpsiX.ShortCircuit   = False

evtTuple                  = EventTuple()
evtTuple.ToolList        += ["TupleToolEventInfo", "TupleToolTrigger"]

DaVinci().EvtMax          = -1
DaVinci().SkipEvents      = -1
DaVinci().DataType        = dataType

DaVinci().Lumi            = not(isMC)
DaVinci().Simulation      = isMC
DaVinci().TupleFile       = tupleName
DaVinci().UserAlgorithms += [check_PV, SeqBs2JpsiPhi.sequence(), evtTuple, seqB2JpsiX]

