import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from Configurables import (GaudiSequencer,
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
                           PrintDecayTree,PrintDecayTreeTool, TupleToolTrackPosition, TupleToolRecoStats )
from GaudiConfUtils.ConfigurableGenerators import FilterDesktop, CombineParticles
from PhysSelPython.Wrappers import Selection, DataOnDemand, SelectionSequence


##############################################################################################
##### SELECTIONS
##############################################################################################
seqB2JpsiX = GaudiSequencer('seqB2JpsiX')
JpsiList = DataOnDemand(Location = "/Event/Dimuon/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles")
KaonList = DataOnDemand(Location = "/Event/Dimuon/Phys/StdAllLooseKaons/Particles")

Phi2KK = CombineParticles( DecayDescriptors = ["phi(1020) -> K+ K-"],
                            DaughtersCuts = {},
                            CombinationCut = "in_range(1008,AM,1050)",
                            MotherCut = "in_range(1008,M,1050) & (VFASPF(VCHI2PDOF) < 25)",
                            ReFitPVs = True)
Phi2KKSel = Selection( "Phi2KKSel", Algorithm = Phi2KK, RequiredSelections = [ KaonList ] )
SeqPhi2KK = SelectionSequence("SeqPhi2KK", TopSelection = Phi2KKSel)

Bs2JpsiPhi = CombineParticles( DecayDescriptors = ["B_s0 -> J/psi(1S) phi(1020)"],
                            DaughtersCuts = {},
                            CombinationCut = "in_range(5200,AM,5550)",
                            MotherCut = "in_range(5200,M,5550) & (VFASPF(VCHI2PDOF) < 25)",
                            ReFitPVs = True)
Bs2JpsiPhiSel = Selection( "Bs2JpsiPhiSel", Algorithm = Bs2JpsiPhi, RequiredSelections = [ JpsiList, Phi2KKSel ] )
SeqBs2JpsiPhi = SelectionSequence("SeqBs2JpsiPhi", TopSelection = Bs2JpsiPhiSel )
Bsdecaydcr        = "B_s0 -> (^J/psi(1S) => ^mu+ ^mu-) (^phi(1020) => ^K+ ^K-)"

## Create another Bs tuple with the striping as well
BsPartVtxlocationStripping = "/Event/Dimuon/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
BsdecaydcrStripping        = "B_s0 -> (^J/psi(1S) => ^mu+ ^mu-) (^phi(1020) => ^K+ ^K-)"



##############################################################################################
# TUPLE sequence
##############################################################################################
TupleSeq = GaudiSequencer('TupleSeq')
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

BsTuple.Inputs = [SeqBs2JpsiPhi.outputLocation()] #
BsTuple.Decay  = Bsdecaydcr
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

TupleToolTagging = TupleToolTagging('TupleToolTagging')
TupleToolTagging.Verbose = True
BsTuple.addTool(TupleToolTagging)
TupleSeq.Members += [ BsTuple ]

TupleToolTrigger = TupleToolTrigger('TupleToolTrigger')
TupleToolTrigger.Verbose = True
TupleToolTrigger.TriggerList = [
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
########################################
BsTupleStrip        = BsTuple.clone("BsTupleStrip")
BsTupleStrip.Inputs = [BsPartVtxlocationStripping]

BsTupleStrip.Decay  = BsdecaydcrStripping
BsTupleStrip.addTool(TupleToolGeometry)
BsTupleStrip.addTool(TupleToolTrackInfo)

TupleSeq.Members    += [BsTupleStrip]
########################################




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
    "LOKI_CosPolAngle_Dau1": "LV01",
    "LOKI_CosPolAngle_Dau2": "LV02",
    ###### DecayTreeFitVariables
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )",
    "LOKI_DTF_CHI2NDOF"    : "DTF_CHI2NDOF( True )",
    "LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )",
    "LOKI_MASS_JpsiConstr" : "DTF_FUN ( M , False , 'J/psi(1S)' )" ,
    "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )",
    #"LOKI_DTF_TAU"         : "DTF_FUN ( BPVLTIME('PropertimeFitter/properTime:PUBLIC') , True)"
       }

##################### BsTuple #############################
BsTuple.Branches={
    "B_s0" :  "B_s0 : B_s0 -> (J/psi(1S) => mu+ mu-) (phi(1020) -> K+ K-)",
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



##################### BsTupleStrip #############################
BsTupleStrip.Branches={
    "B_s0" :  "B_s0 : B_s0 -> (J/psi(1S) => mu+ mu-) (phi(1020) -> K+ K-)",
            }
BsTupleStrip.addTool(TupleToolDecay, name="B_s0")
BsTupleStrip.B_s0.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BsTupleStrip.B_s0.addTool(LoKi_SpecificToB)
TupleToolP2VV_BsStrip = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_BsStrip.Calculator = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_BsStrip.OutputLevel = 6
BsTupleStrip.B_s0.addTool(TupleToolP2VV_BsStrip)
BsTupleStrip.B_s0.ToolList +=  ["TupleToolP2VV/TupleToolP2VV_Bs"]

BsTupleStrip.B_s0.addTool(TupleToolTISTOS)
from Configurables import TriggerTisTos
BsTupleStrip.B_s0.TupleToolTISTOS.addTool( TriggerTisTos, "TriggerTisTos" )
BsTupleStrip.B_s0.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.

BsTupleStrip.B_s0.ToolList+=["TupleToolTISTOS"]
#######################################################################################



#######################################################################################
TupleSeq.ModeOR          = True
TupleSeq.ShortCircuit    = False

seqB2JpsiX.Members      += [ TupleSeq]
seqB2JpsiX.ModeOR        =   True
seqB2JpsiX.ShortCircuit  =   False

from Configurables import EventTuple , TupleToolTrigger
evtTuple                = EventTuple()
evtTuple.ToolList      += [ "TupleToolEventInfo", "TupleToolTrigger"]
DaVinci().EvtMax        =  -1
DaVinci().SkipEvents    =  -1
DaVinci().DataType      = '2011'
# Data
DaVinci().DDDBtag       = "head-20110914"  # dddb-20120831 
DaVinci().CondDBtag     = "head-20111111"  # cond-20120831  
DaVinci().Lumi		= True
DaVinci().TupleFile     = "DTT.root"  # Ntuple
DaVinci().UserAlgorithms += [SeqBs2JpsiPhi.sequence(),
                            evtTuple, seqB2JpsiX ]






#import glob
#files = glob.glob('/panasas/gcowan/MC/13144002/*dst')
#inputs = []
#for f in files:
#    inputs.append(f.rsplit('\n')[0])


## Run one event and look for the tags

## from GaudiConf import IOHelper
## IOHelper().inputFiles(['DSTs/00016768_00000001_1.dimuon.dst'])
## from GaudiPython import *
## gaudi = AppMgr()
## gaudi.run(1)
## tes = gaudi.evtSvc()
## tes.dump()
## print tes['/Event/Rec/Header']




#Colission11MagDown and Up
#--  DDDB : head-20110914 
#--  CONDDB : head-20111111 

#Colission12MagDown and Up
#--  DDDB : dddb-20120831 
#--  CONDDB : cond-20120831 

