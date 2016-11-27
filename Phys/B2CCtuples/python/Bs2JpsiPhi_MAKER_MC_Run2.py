# C. Vazquez Sierra, Oct 2016

from GaudiKernel.SystemOfUnits import *
from Gaudi.Configuration import *
from Configurables import DaVinci
from Configurables import GaudiSequencer, OfflineVertexFitter, FitDecayTrees, CheckPV, TupleToolGeometry, TupleToolTrackInfo, TriggerTisTos
from Configurables import DecayTreeTuple, TupleToolDecay, TupleToolVtxIsoln, LoKi__Hybrid__TupleTool, TupleToolTrigger, TupleToolTagging, EventTuple
from Configurables import TupleToolP2VV, TupleToolTISTOS, BTagging, PrintDecayTree, PrintDecayTreeTool, TupleToolTrackPosition, TupleToolRecoStats
from GaudiConfUtils.ConfigurableGenerators import FilterDesktop, CombineParticles
from PhysSelPython.Wrappers import Selection, DataOnDemand, SelectionSequence

dataType   = '2015'
isMC       = True
tupleName  = 'DTT.root'

##### Trigger lines for TupleToolTrigger and TupleToolTISTOS

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

trigger_list = l0_lines + hlt1_lines + hlt2_lines
tistos_list  = trigger_list

##### Selection 1: Bs->J/PsiPhi from detached muons and loose kaons

seqB2JpsiX    = GaudiSequencer('seqB2JpsiX')
Bsdecaydcr    = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"

#### phi(1020) -> K+ K-
KaonList  = DataOnDemand(Location = "Phys/StdAllLooseKaons/Particles")
Phi2KK    = CombineParticles(DecayDescriptors = ["phi(1020) -> K+ K-"],
                             DaughtersCuts = {},
                             #CombinationCut = "in_range(1008,AM,1050)",
                             #MotherCut = "in_range(1008,M,1050) & (VFASPF(VCHI2PDOF) < 25)",
                             #CombinationCut = "ALL",
                             MotherCut = "(VFASPF(VCHI2PDOF) < 25)",
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

##### Selection 2: Bs->J/PsiPhi from the corresponding detached stripping line

BsPartVtxlocationDetached = "/Event/AllStreams/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
BsdecaydcrDetached        = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"

##### Selection 3: Bs->J/PsiPhi from the corresponding prescaled stripping line

BsPartVtxlocationPrescaled = "/Event/AllStreams/Phys/BetaSBs2JpsiPhiPrescaledLine/Particles"
BsdecaydcrPrescaled        = "B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)"

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
                    , "TupleToolPid"
                    , "TupleToolANNPID"
                    , "TupleToolRecoStats"
                    , "TupleToolTrackPosition" ]
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

BsTupleDetached        = BsTuple.clone("BsTupleDetached")
BsTupleDetached.Inputs = [BsPartVtxlocationDetached]
BsTupleDetached.Decay  = BsdecaydcrDetached
BsTupleDetached.addTool(TupleToolGeometry)
BsTupleDetached.addTool(TupleToolTrackInfo)
TupleSeq.Members   += [BsTupleDetached]

BsTuplePrescaled        = BsTuple.clone("BsTuplePrescaled")
BsTuplePrescaled.Inputs = [BsPartVtxlocationPrescaled]
BsTuplePrescaled.Decay  = BsdecaydcrPrescaled
BsTuplePrescaled.addTool(TupleToolGeometry)
BsTuplePrescaled.addTool(TupleToolTrackInfo)
TupleSeq.Members   += [BsTuplePrescaled]

#### Adding the tuple tools to the corresponding decays

BsTuple.Branches = { "B_s0"     : "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))"
                   , "J_psi_1S" :  "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"  }

LoKiVariables = LoKi__Hybrid__TupleTool('LoKiVariables')
LoKiVariables.Variables = { "LOKI_ENERGY"     : "E"
                          , "LOKI_ETA"        : "ETA"
                          , "LOKI_PHI"        : "PHI" }
BsTuple.addTool(LoKiVariables , name = 'LoKiVariables')
BsTuple.ToolList   += ['LoKi::Hybrid::TupleTool/LoKiVariables']
BsTuple.OutputLevel = 6

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
                              , "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )" }
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
BsTuple.B_s0.ToolList                                 += ["TupleToolTISTOS"]

#### Repeating for stripping-line-based tuple

BsTuplePrescaled.Branches = { "B_s0"     : "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))"
                            , "J_psi_1S" :  "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"  }

BsTuplePrescaled.addTool(TupleToolDecay, name = "B_s0")
BsTuplePrescaled.B_s0.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTuplePrescaled.B_s0.addTool(LoKi_SpecificToB)

TupleToolP2VV_BsPrescaled             = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_BsPrescaled.Calculator  = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_BsPrescaled.OutputLevel = 6
BsTuplePrescaled.B_s0.addTool(TupleToolP2VV_BsPrescaled)
BsTuplePrescaled.B_s0.ToolList       += ["TupleToolP2VV/TupleToolP2VV_Bs"]

BsTuplePrescaled.B_s0.addTool(TupleToolTISTOS)
BsTuplePrescaled.B_s0.TupleToolTISTOS.addTool(TriggerTisTos, "TriggerTisTos")
BsTuplePrescaled.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BsTuplePrescaled.B_s0.ToolList                                 += ["TupleToolTISTOS"]

BsTupleDetached.Branches = { "B_s0"     : "^(B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-))"
                           , "J_psi_1S" :  "B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)"  }

BsTupleDetached.addTool(TupleToolDecay, name = "B_s0")
BsTupleDetached.B_s0.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTupleDetached.B_s0.addTool(LoKi_SpecificToB)

TupleToolP2VV_BsDetached             = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_BsDetached.Calculator  = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_BsDetached.OutputLevel = 6
BsTupleDetached.B_s0.addTool(TupleToolP2VV_BsDetached)
BsTupleDetached.B_s0.ToolList       += ["TupleToolP2VV/TupleToolP2VV_Bs"]

BsTupleDetached.B_s0.addTool(TupleToolTISTOS)
BsTupleDetached.B_s0.TupleToolTISTOS.addTool(TriggerTisTos, "TriggerTisTos")
BsTupleDetached.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
BsTupleDetached.B_s0.ToolList                                 += ["TupleToolTISTOS"]

##### Main body

#from GaudiConf import IOHelper
#IOHelper().inputFiles(['./00049575_00000024_1.dimuon.dst'], clear=True)

from Configurables import TrackSmearState
smear = TrackSmearState('TrackSmearState')

TupleSeq.ModeOR           = True
TupleSeq.ShortCircuit     = False

seqB2JpsiX.Members       += [TupleSeq]
seqB2JpsiX.ModeOR         = True
seqB2JpsiX.ShortCircuit   = False

evtTuple                  = EventTuple()
evtTuple.ToolList        += ["TupleToolEventInfo", "TupleToolTrigger"]
DaVinci().EvtMax          = -1
DaVinci().SkipEvents      = -1
DaVinci().DataType        = dataType

DaVinci().Lumi		  = not(isMC)
DaVinci().Simulation      = isMC
DaVinci().TupleFile       = tupleName
DaVinci().CondDBtag       = "sim-20160907-1-vc-md100" # Update.
DaVinci().DDDBtag         = "dddb-20150928" # Update.
DaVinci().UserAlgorithms += [smear, SeqBs2JpsiPhi.sequence(), evtTuple, seqB2JpsiX]

