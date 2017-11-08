########################################################################
# Options for Bs->DsMuNu ntuples 
########################################################################

from DaVinci.Configuration import *
from Configurables import DaVinci
from Gaudi.Configuration import *
from Configurables import GaudiSequencer, DecayTreeTuple, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS, FilterDesktop, TupleToolMCTruth, MCTupleToolKinematic, MCTupleToolHierarchy, MCTupleToolPID, TupleToolDalitz
from Configurables import CombineParticles,  FilterDesktop
from Configurables import TupleToolSLTools, TupleToolEWTrackIsolation, TupleToolIsoGeneric
from Configurables import OfflineVertexFitter
from Configurables import LoKi__VoidFilter as VoidFilter
from Configurables import SubstitutePID, SubPIDMMFilter
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from StandardParticles import StdLoosePi02gg, StdLooseResolvedPi0, StdLooseMergedPi0, StdVeryLooseAllPhotons
import os
currentPath = os.getcwd()
PackagePath = '/'.join(s.strip('/') for s in currentPath.split('/')[:-1])
## PackagePath should end in Phys/BsDsMuNuForRDS

########################################################################
### Configure the following options 
########################################################################

#### Only needed if you run in local. These are used by TupleToolMuonIsolation AND also the algo to make BDTS cut if you are making it
#weightFile     = PackagePath+"/utils/TMVA_7Dec.weights.xml"
#flatteningFile = PackagePath+"/utils/HflatBDTS_7Dec.root"
#isoBDT1File    = PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_1_BDT.weights.xml"
#isoBDT2File    = PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_8_BDT.weights.xml"
#isoBDT3File    = PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_9_BDT.weights.xml"
#isoBDT4File    = PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_4_BDT.weights.xml"

rootfilename = "TupleRDS.root" ## output file name
Usegrid = False
myEvents = 100
photonControl = False
doStripping = False ## run the stripping over the events
doMatchedNtuples = False ## does the MC matching for all the decays
doMatchedDsst = False
doSoftSelection = False
doSoftSelection2 = False

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
#    weightFile     = "TMVA_7Dec.weights.xml"
#    flatteningFile =  "HflatBDTS_7Dec.root"
#    isoBDT1File    = "600_2500_4_30_0.75_1_1_BDT.weights.xml"
#    isoBDT2File    = "600_2500_4_30_0.75_1_8_BDT.weights.xml"
#    isoBDT3File    = "600_2500_4_30_0.75_1_9_BDT.weights.xml"
#    isoBDT4File    = "600_2500_4_30_0.75_1_4_BDT.weights.xml"

B2DMuNuInput =     "/Event/B2DMuNuXANDTAU/Phys/b2DsMuXB2DMuForTauMuLine/Particles"
B2DMuNuInputFake = "/Event/B2DMuNuXANDTAU/Phys/b2DsMuXFakeB2DMuForTauMuLine/Particles"

if doSoftSelection:
  B2DMuNuInput =     "/Event/Phys/b2DsMuXB2DMuForTauMuLine/Particles"
  B2DMuNuInputFake = "/Event/Phys/b2DsMuXFakeB2DMuForTauMuLine/Particles"

if photonControl:
  B2DMuNuInput =   "/Event/AllStreams/Phys/B02DPiD2HHHBeauty2CharmLine/Particles"
  B2DMuNuSSInput = "/Event/AllStreams/Phys/B02DPiWSD2HHHBeauty2CharmLine/Particles"

#B2DMuNuInput     = "/Event/Phys/b2DsMuXB2DMuForTauMuLine/Particles"
#B2DMuNuInputFake = "/Event/Semileptonic/Phys/B2DMuNuX_Ds_FakeMuon/Particles"

## Check the number of PVs
from Configurables import CheckPV
checkPV = CheckPV('CheckPVMin1')
checkPV.MinPVs = 1
mySequencer.Members += [checkPV]

if photonControl:
  ## Create a FilterDesktop to cut the output of the stripping from the BHADRONCOMPLETEEVENT
  dsFilter = FilterDesktop("DsFilter", Code = "(M < 5800) & (M > 4000)")# & INTREE( (ABSID=='D-') & (M>1840) ) & INTREE( (ABSID=='D-') & (M<2500) )")
  TightInput = AutomaticData(Location = B2DMuNuInput)
  TightSel = Selection(name = "TightSel", Algorithm = dsFilter, RequiredSelections = [TightInput])
  TightSeq = SelectionSequence("TightSeq", TopSelection = TightSel)
  mySequencer.Members += [TightSeq.sequence()]
  print TightSeq.outputLocation()

  dsSSFilter = FilterDesktop("DsSSFilter", Code = "(M < 5800) & (M > 4000)") # & INTREE( (ABSID=='D-') & (M>1840) ) & INTREE( (ABSID=='D-') & (M<2500) )")
  TightSSInput = AutomaticData(Location = B2DMuNuSSInput)
  TightSSSel = Selection(name = "TightSSSel", Algorithm = dsSSFilter, RequiredSelections = [TightSSInput])
  TightSSSeq = SelectionSequence("TightSSSeq", TopSelection = TightSSSel)
  mySequencer.Members += [TightSSSeq.sequence()]

from Configurables import PrintMCTree, PrintMCDecayTreeTool
mctree = PrintMCTree("PrintTrueBs")
mctree.addTool( PrintMCDecayTreeTool, name = "PrintMC" )
mctree.PrintMC.Information = "Name P Px Py Pz Pt"
mctree.ParticleNames = [  "B_s0", "B_s~0" ]
mctree.Depth = 2

# redo the stripping 
if doStripping:

    # Specify the name of your configuration
    from StrippingConf.Configuration import StrippingConf
    confname='B2DMuForTauMu' #FOR USERS
    from StrippingSelections import buildersConf
    confs = buildersConf()
    from StrippingSelections.Utils import lineBuilder, buildStreamsFromBuilder
    ## this is a trick as the MC was not generated with the Hlt2 trigger line as it did not exist back then
    confs[confname]['CONFIG']['Hlt2Line'] = ""
    confs[confname]['CONFIG']['Hlt2LineFake'] = ""
    streams = buildStreamsFromBuilder(confs,confname)

    from Configurables import  ProcStatusCheck
    filterBadEvents =  ProcStatusCheck()
    sc = StrippingConf( Streams = streams,
                        MaxCandidates = 2000,
                        AcceptBadEvents = False,
                        HDRLocation="Phys/MyReports",
                        BadEventSelection = filterBadEvents)

    for stream in streams:
        for line in stream.lines :
            print "Adding ", line.name(), " output location : ", line.outputLocation()

    from Configurables import StrippingReport
    sr = StrippingReport(Selections = sc.selections())
    sr.ReportFrequency = 10000

    mySequencer.Members += [ sc.sequence() ]
    mySequencer.Members += [ sr ]

print 'The locations to read (for the ntuple) are', B2DMuNuInput

## do a soft selection to eliminate all the cuts at the stripping level
if doSoftSelection2:
  lkpreambulo=["from LoKiPhysMC.decorators import *","from LoKiPhysMC.functions import mcMatch"]
  
  cpDst2KKpi = CombineParticles("cpDs")
  cpDst2KKpi.Preambulo=lkpreambulo
  cpDst2KKpi.DecayDescriptors = ["[D_s- -> K+ K- pi-]cc"]
  cpDst2KKpi.DaughtersCuts = {"pi+":"mcMatch('[D_s+ ==x> K+ K- ^pi+]CC')","K+":"mcMatch('[D_s+ ==x> ^K+ ^K- pi+]CC')"}
  cpDst2KKpi.MotherCut = "(ALL)"
  selcpDst2KKpi=Selection ("selcpDst2KKpi", Algorithm = cpDst2KKpi, RequiredSelections = [DataOnDemand("Phys/StdAllNoPIDsKaons/Particles"), DataOnDemand("Phys/StdAllNoPIDsPions/Particles")])
  selseqcpDst2KKpi=SelectionSequence("selseqcpDst2KKpi",TopSelection=selcpDst2KKpi)
  mySequencer.Members += [mctree]

  #cpDsst = CombineParticles("cpDsst")
  #cpDsst.Preambulo = lkpreambulo
  #cpDsst.DecayDescriptor = "[D*_s+ -> D_s+ gamma]cc"
  #cpDsst.DaughtersCuts = {"gamma":"mcMatch('[D*_s- ==x> D_s- ^gamma]CC')","D_s-":"mcMatch('[D*_s- ==x> ^D_s- gamma]CC')"} 
  #cpDsst.MotherCut = "(ALL)"
  #selcpDsst = Selection("selcpDsst", Algorithm = cpDsst, RequiredSelections = [DataOnDemand("Phys/StdVeryLooseAllPhotons/Particles"), selcpDst2KKpi])
  #selseqcpDsst = SelectionSequence("selseqcpDsst", TopSelection = selcpDsst)
  #mySequencer.Members += [selseqcpDsst.sequence()]
  #cpBs=CombineParticles("cpBs")
  #cpBs.Preambulo = lkpreambulo
  #cpBs.DecayDescriptors = ["[B_s~0 -> D_s- mu+]cc","[B_s~0 -> D_s+ mu-]cc"]
  #cpBs.DaughtersCuts = {"mu-":"ALL"} 
  #cpBs.CombinationCut = "(APT>0)"
  #cpBs.MotherCut = "(PT > 0)"

  cpBsDsst = CombineParticles("cpBsDsst")
  cpBsDsst.Preambulo = lkpreambulo
  cpBsDsst.DecayDescriptors = ["[B_s0 -> D_s- gamma mu+]cc","[B_s0 -> D_s+ gamma mu-]cc"]
  cpBsDsst.DaughtersCuts = {"mu-":"ALL","D_s+":"ALL","gamma":"ALL"}
  cpBsDsst.CombinationCut = "(APT>0)"
  cpBsDsst.MotherCut = "(PT > 0)"

  #selcpBs=Selection ( "selcpBs", Algorithm = cpBs, RequiredSelections = [selcpDst2KKpi, DataOnDemand("Phys/StdAllNoPIDsMuons/Particles")])
  #selseqcpBs=SelectionSequence("selseqcpBs",TopSelection=selcpBs)
  #B2DMuNuInput = selseqcpBs.outputLocation()
  #mySequencer.Members += [selseqcpBs.sequence()]

  selcpBsDsst=Selection ( "selcpBsDsst", Algorithm = cpBsDsst, RequiredSelections = [selcpDst2KKpi, DataOnDemand("Phys/StdVeryLooseAllPhotons/Particles"), DataOnDemand("Phys/StdAllNoPIDsMuons/Particles")])
  selseqcpBsDsst=SelectionSequence("selseqcpBsDsst",TopSelection=selcpBsDsst)
  B2DMuNuInput = selseqcpBsDsst.outputLocation()
  mySequencer.Members += [selseqcpBsDsst.sequence()]
#  from StandardParticles import StdAllLooseMuons, StdLoosePions, StdLooseKaons
#  kaons = Selection("KaonsForDs", Algorithm = FilterDesktop("kaonFilter", Code = "(MIPCHI2DV(PRIMARY)>2)"), RequiredSelections = [StdLooseKaons])
#  pions = Selection("PionsForDs", Algorithm = FilterDesktop("pionFilter", Code = "(MIPCHI2DV(PRIMARY)>2)"), RequiredSelections = [StdLoosePions])
#  muons = Selection("MuonsForDs", Algorithm = FilterDesktop("muonFilter", Code = "(MIPCHI2DV(PRIMARY)>0)"), RequiredSelections = [StdAllLooseMuons])
#  _daughCut = '(PT > 200)'  
#  _combCut = "(ADAMASS('D_s+') < 120*MeV)"
#  _DsMomCuts = "(ADMASS('D_s+') < 100*MeV) & (VFASPF(VCHI2/VDOF) < 100)"
#  _BsMomCuts = '(M > 2500) & (M < 6000)'
#  _makeDs = CombineParticles("DsMaker",
#                             DecayDescriptor = "[D_s+ -> K+ K- pi+]cc",
#                             #DaughtersCuts = {"K+" : _daughCut, "pi+" : _daughCut },
#                             CombinationCut = _combCut,
#                             MotherCut = _DsMomCuts
#                            )
#  myDs = Selection("myDs",
#                   Algorithm = _makeDs,
#                   RequiredSelections = [pions, kaons]
#                   )
#  _makeBs = CombineParticles("BsMaker",
#                             DecayDescriptor = "[B_s0 -> D_s+ mu-]cc",
#                             MotherCut = _BsMomCuts 
#                             )
#  BsSel = Selection("myBs", Algorithm = _makeBs, RequiredSelections = [myDs,muons])
#  BsSeq = SelectionSequence("BsDsMuNuDummySeq", TopSelection = BsSel)
#  
#  B2DMuNuInput = BsSeq.outputLocation()
#  mySequencer.Members += [BsSeq.sequence()]

print 'The locations to read (for the ntuple) are', B2DMuNuInput

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
                    , "TupleToolSLTools"
                    , "TupleToolTrackInfo"
                    , "TupleToolMCTruth"
                    , "TupleToolDalitz"
                    , "TupleToolIsoGeneric"
                    ]

from Configurables import TupleToolGeometry
myNTUPLE.addTool(TupleToolGeometry)
myNTUPLE.TupleToolGeometry.OutputLevel = INFO
myNTUPLE.TupleToolGeometry.Verbose = True
myNTUPLE.TupleToolGeometry.RefitPVs = True

#from Configurables import TupleToolMuonIsolation
#myNTUPLE.addTool(TupleToolMuonIsolation)
#myNTUPLE.TupleToolMuonIsolation.BDTSRootFile = flatteningFile
#myNTUPLE.TupleToolMuonIsolation.BDTSXMLFile  = weightFile  
#myNTUPLE.TupleToolMuonIsolation.isMC = True
#myNTUPLE.TupleToolMuonIsolation.isoBDT1_xmlFile = isoBDT1File
#myNTUPLE.TupleToolMuonIsolation.isoBDT2_xmlFile = isoBDT2File
#myNTUPLE.TupleToolMuonIsolation.isoBDT3_xmlFile = isoBDT3File
#myNTUPLE.TupleToolMuonIsolation.isoBDT4_xmlFile = isoBDT4File
#myNTUPLE.TupleToolMuonIsolation.OutputLevel = ERROR

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
# Fix TISTOS bug
from Configurables import TriggerTisTos
myNTUPLE.TupleToolTISTOS.addTool(TriggerTisTos())
myNTUPLE.TupleToolTISTOS.TriggerTisTos.TOSFracMuon = 0.
myNTUPLE.TupleToolTISTOS.TriggerTisTos.TOSFracEcal = 0.
myNTUPLE.TupleToolTISTOS.TriggerTisTos.TOSFracHcal = 0.

myNTUPLE.addTool(TupleToolSLTools)
myNTUPLE.TupleToolSLTools.Bmass = 5366.3
myNTUPLE.TupleToolSLTools.VertexCov = True
myNTUPLE.TupleToolSLTools.MomCov = True

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

if doMatchedDsst :
    _Preambulo = ["from LoKiPhysMC.decorators import *","from LoKiPhysMC.functions import mcMatch"]

    ## Dictionary of daughters for the CombineParticles.
    cheatDaug = {
          "K+"   : "(mcMatch('[D_s+ --> K- K+ pi+]CC'))"
          ,"pi+" : "(mcMatch('[D_s+ --> K- ^K+ pi+]CC'))"
          }

    cheatMother = "(mcMatch('[D_s+ --> K- K+ pi+]CC'))"

    MatchedDsPlus = CombineParticles(
       "MatchedDsComb"
       , Preambulo = _Preambulo
       , DecayDescriptor = "[D_s+ -> K- K+ pi+]cc"
       , Inputs = [ "Phys/StdAllNoPIDsPions/Particles", "Phys/StdAllNoPIDsKaons/Particles" ]
       , DaughtersCuts = cheatDaug
       , CombinationCut = "AALL"
       , MotherCut = cheatMother
    )

    cheatReDaug = {
          "gamma" : "(mcMatch('[D*_s+ --> D_s+ gamma]CC'))"
          }
    cheatReMother = "(mcMatch('[D*_s+ --> D_s+ gamma]CC'))"
    MatchedDsst = CombineParticles(
        "MatchedDsstComb"
        , Preambulo = _Preambulo
        , DecayDescriptor = "[D*_s+ -> D_s+ gamma]cc"
        , Inputs = ["Phys/MatchedDsComb", "Phys/StdVeryLooseAllPhotons"]
        , DaughtersCuts = cheatReDaug
        , CombinationCut = "AALL"
        , MotherCut = cheatReMother
    )

    # Now we make the Bs candidate with a second instance of CombineParticles.
    cheatBsMuMother = "(mcMatch('[B_s~0 --> D*_s+ mu- ... ]CC'))"
    cheatBsMuDaug   = { "mu-" : "(mcMatch('[B_s~0 --> D*_s+ ^mu- ... ]CC'))" }
    MatchedBsMu = CombineParticles(
        "MatchedBsDsstMuNuComb"
        , Preambulo = _Preambulo
        , DecayDescriptor = "[B_s~0 -> D*_s+ mu-]cc"
        , Inputs = [ "Phys/StdAllNoPIDsMuons/Particles", 'Phys/MatchedDsstComb' ]
        , DaughtersCuts = cheatBsMuDaug
        , CombinationCut = "AALL"
        , MotherCut = cheatBsMuMother
        )

    Seq = GaudiSequencer( 'SeqMatchedBsDsstMuNuComb' )
    Seq.Members = [ MatchedDsPlus, MatchedDsst, MatchedBsMu ]
    mySequencer.Members += [ Seq ]

if doMatchedNtuples :
    _Preambulo = ["from LoKiPhysMC.decorators import *","from LoKiPhysMC.functions import mcMatch"]

    ## Dictionary of daughters for the CombineParticles.
    cheatDaug = {
          "K+"   : "(mcMatch('[D_s+ ==> K- K+ pi+]CC'))"
          ,"pi+" : "(mcMatch('[D_s+ ==> K- ^K+ pi+]CC'))"
          }

    cheatMother = "(mcMatch('[D_s+ ==> K- K+ pi+]CC'))" 

    MatchedDsPlus = CombineParticles(
       "MatchedDsComb"
       , Preambulo = _Preambulo
       , DecayDescriptor = "[D_s+ -> K- K+ pi+]cc"
       , Inputs = [ "Phys/StdAllNoPIDsPions/Particles", "Phys/StdAllNoPIDsKaons/Particles" ]
       , DaughtersCuts = cheatDaug
       , CombinationCut = "AALL"
       , MotherCut = cheatMother
    )

    # Now we make the Bs candidate with a second instance of CombineParticles.
    cheatBsMuMother = "(mcMatch('[B_s~0 --> D_s+ mu- ... ]CC'))"
    cheatBsMuDaug   = { "mu-" : "(mcMatch('[B_s~0 --> D_s+ ^mu- ... ]CC'))" }
    MatchedBsMu = CombineParticles(
        "MatchedBsDMuNuComb"
        , Preambulo = _Preambulo
        , DecayDescriptor = "[B_s~0 -> D_s+ mu-]cc"
        , Inputs = [ "Phys/StdAllNoPIDsMuons/Particles", 'Phys/MatchedDsComb' ]
        , DaughtersCuts = cheatBsMuDaug
        , CombinationCut = "AALL"
        , MotherCut = cheatBsMuMother
        )

    Seq = GaudiSequencer( 'SeqMatchedBsDMuNuComb' )
    Seq.Members = [ MatchedDsPlus, MatchedBsMu ]
    mySequencer.Members += [ Seq ]
    
############################
###     Make    ntuples  ###
############################

from DecayTreeTuple.Configuration import *

## for signal line ##
B2DMuNuTuple = myNTUPLE.clone("B2DsMuNuTuple")
B2DMuNuTuple.Inputs = [B2DMuNuInput]
if doSoftSelection:
  B2DMuNuTuple.Decay = "[B_s0 -> ^(D*_s+ -> (D_s+ -> ^K- ^K+ ^pi+) gamma) ^mu-]CC"
  B2DMuNuTuple.Branches = {"Bs_0"  : "[B_s0 -> (D*_s+ -> (D_s+ -> K- K+ pi+) gamma) mu-]CC",
                           "Ds"    : "[B_s0 -> (D*_s+ -> ^(D_s+ -> K- K+ pi+) gamma) mu-]CC",
                           "Kpl"   : "[B_s0 -> (D*_s+ -> (D_s+ -> K- ^K+ pi+) gamma) mu-]CC",
                           "Kmi"   : "[B_s0 -> (D*_s+ -> (D_s+ -> ^K- K+ pi+) gamma) mu-]CC",
                           "pi"    : "[B_s0 -> (D*_s+ -> (D_s+ -> K- K+ ^pi+) gamma) mu-]CC",
                           "mu"    : "[B_s0 -> (D*_s+ -> (D_s+ -> K- K+ pi+) gamma) ^mu-]CC"}
if photonControl:
  B2DMuNuTuple.Inputs = [TightSeq.outputLocation()]
  B2DMuNuTuple.Decay = "[B0 -> ^(D- -> ^K- ^K+ ^pi-) ^pi+]CC"
  B2DMuNuTuple.Branches = {"B"       : "[B0 -> (D- -> K- K+ pi-) pi+ ]CC",
                           "Ds"      : "[B0 -> ^(D- -> K- K+ pi-) pi+ ]CC",
                           "Kpl"     : "[B0 -> (D- -> K- ^K+ pi-) pi+ ]CC",
                           "Kmi"     : "[B0 -> (D- -> ^K- K+ pi-) pi+ ]CC",
                           "pi"      : "[B0 -> (D- -> K- K+ ^pi-) pi+ ]CC",
                           "piFromB" : "[B0 -> (D- -> K- K+ pi-) ^pi+ ]CC"}

else:
  B2DMuNuTuple.Decay = "[B- -> ^(D_s+ -> ^K- ^K+ ^pi+) ^mu-]CC"
  B2DMuNuTuple.Branches = {"Bs_0"  : "[B- ->  (D_s+ -> K- K+ pi+)  mu-]CC",
                           "Ds"    : "[B- -> ^(D_s+ -> K- K+ pi+)  mu-]CC",
                           "Kpl"   : "[B- ->  (D_s+ -> K- ^K+ pi+)  mu-]CC",
                           "Kmi"   : "[B- ->  (D_s+ -> ^K- K+ pi+)  mu-]CC",
                           "pi"    : "[B- ->  (D_s+ -> K- K+ ^pi+)  mu-]CC",
                           "mu"    : "[B- ->  (D_s+ -> K- K+ pi+) ^mu-]CC"}


B2DMuNuTuple.addTool(TupleToolDecay("B"))
B2DMuNuTuple.B.InheritTools = True

B2DMuNuTuple.addTool(TupleToolDecay("Ds"))
B2DMuNuTuple.Ds.InheritTools = True
EWconeDs = B2DMuNuTuple.Ds.addTupleTool(TupleToolEWTrackIsolation)
EWconeDs.ConeStepSize = 0.2
EWconeDs.MinConeRadius = 0.4
EWconeDs.MaxConeRadius = 0.6
EWconeDs.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDs.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDs.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"
EWconeDs.isMC = True

#B2DMuNuTuple.addTool(TupleToolDecay("mu"))
#B2DMuNuTuple.mu.InheritTools = True
#EWconeMu = B2DMuNuTuple.mu.addTupleTool(TupleToolEWTrackIsolation)
#EWconeMu.ConeStepSize = .2
#EWconeMu.MinConeRadius = 0.4
#EWconeMu.MaxConeRadius = 0.6
#EWconeMu.ExtraParticlesLocation = "StdAllLoosePions"

## for same sign muon
B2DMuNuTupleSS = myNTUPLE.clone("B2DsMuNuSSTuple")
B2DMuNuTupleSS.Inputs = [B2DMuNuInput]
B2DMuNuTupleSS.Decay = "[B+ -> ^(D_s+ -> ^K- ^K+ ^pi+) ^mu+]CC"
B2DMuNuTupleSS.Branches = {"Bs_0"  : "[B+ ->  (D_s+ -> K- K+ pi+)  mu+]CC",
                           "Ds"    : "[B+ -> ^(D_s+ -> K- K+ pi+)  mu+]CC",
                           "Kpl"   : "[B+ ->  (D_s+ -> K- ^K+ pi+)  mu+]CC",
                           "Kmi"   : "[B+ ->  (D_s+ -> ^K- K+ pi+)  mu+]CC",
                           "pi"    : "[B+ ->  (D_s+ -> K- K+ ^pi+)  mu+]CC",
                           "mu"    : "[B+ ->  (D_s+ -> K- K+ pi+) ^mu+]CC"}

if photonControl:
  B2DMuNuTupleSS.Inputs = [TightSSSeq.outputLocation()]
  B2DMuNuTupleSS.Decay = "[B0 -> ^(D- -> ^K- ^K+ ^pi-) ^pi-]CC"
  B2DMuNuTupleSS.Branches = {"B"       : "[B0 -> (D- -> K- K+ pi-) pi- ]CC",
                             "Ds"      : "[B0 -> ^(D- -> K- K+ pi-) pi- ]CC",
                             "Kpl"     : "[B0 -> (D- -> K- ^K+ pi-) pi- ]CC",
                             "Kmi"     : "[B0 -> (D- -> ^K- K+ pi-) pi- ]CC",
                             "pi"      : "[B0 -> (D- -> K- K+ ^pi-) pi- ]CC",
                             "piFromB" : "[B0 -> (D- -> K- K+ pi-) ^pi- ]CC"}

B2DMuNuTupleSS.addTool(TupleToolDecay("B"))
B2DMuNuTupleSS.B.InheritTools = True

B2DMuNuTupleSS.addTool(TupleToolDecay("Ds"))
B2DMuNuTupleSS.Ds.InheritTools = True
EWconeDsSS = B2DMuNuTupleSS.Ds.addTupleTool(TupleToolEWTrackIsolation)
EWconeDsSS.ConeStepSize = 0.2
EWconeDsSS.MinConeRadius = 0.4
EWconeDsSS.MaxConeRadius = 0.6
EWconeDsSS.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDsSS.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDsSS.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"
EWconeDsSS.isMC = True

#B2DMuNuTupleSS.addTool(TupleToolDecay("mu"))
#B2DMuNuTupleSS.mu.InheritTools = True
#EWconeMuSS = B2DMuNuTupleSS.mu.addTupleTool(TupleToolEWTrackIsolation)
#EWconeMuSS.ConeStepSize = .2
#EWconeMuSS.MinConeRadius = 0.4
#EWconeMuSS.MaxConeRadius = 0.6
#EWconeMuSS.ExtraParticlesLocation = "StdAllLoosePions"

## For fake muon signal ##
B2DMuNuTupleFake = myNTUPLE.clone("B2DsMuNuTupleFake")
B2DMuNuTupleFake.Inputs = [B2DMuNuInputFake]
B2DMuNuTupleFake.Decay = "[B- -> ^(D_s+ -> ^K- ^K+ ^pi+) ^mu-]CC"
B2DMuNuTupleFake.Branches = {"Bs_0"  : "[B- ->  (D_s+ -> K- K+ pi+)  mu-]CC",
                             "Ds"    : "[B- -> ^(D_s+ -> K- K+ pi+)  mu-]CC",
                             "Kpl"   : "[B- ->  (D_s+ -> K- ^K+ pi+)  mu-]CC",
                             "Kmi"   : "[B- ->  (D_s+ -> ^K- K+ pi+)  mu-]CC",
                             "pi"    : "[B- ->  (D_s+ -> K- K+ ^pi+)  mu-]CC",
                             "mu"    : "[B- ->  (D_s+ -> K- K+ pi+) ^mu-]CC"}

B2DMuNuTupleFake.addTool(TupleToolDecay("B"))
B2DMuNuTupleFake.B.InheritTools = True

B2DMuNuTupleFake.addTool(TupleToolDecay("Ds"))
B2DMuNuTupleFake.Ds.InheritTools = True
EWconeDsFake = B2DMuNuTupleFake.Ds.addTupleTool(TupleToolEWTrackIsolation)
EWconeDsFake.ConeStepSize = 0.2
EWconeDsFake.MinConeRadius = 0.4
EWconeDsFake.MaxConeRadius = 0.6
EWconeDsFake.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDsFake.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDsFake.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"
EWconeDsFake.isMC = True

#B2DMuNuTupleFake.addTool(TupleToolDecay("mu"))
#B2DMuNuTupleFake.mu.InheritTools = True
#EWconeMuFake = B2DMuNuTupleFake.mu.addTupleTool(TupleToolEWTrackIsolation)
#EWconeMuFake.ConeStepSize = .2
#EWconeMuFake.MinConeRadius = 0.4
#EWconeMuFake.MaxConeRadius = 0.6
#EWconeMuFake.ExtraParticlesLocation = "StdAllLoosePions"

## For fake muon SameSign
B2DMuNuTupleFakeSS = myNTUPLE.clone("B2DsMuNuSSTupleFake")
B2DMuNuTupleFakeSS.Inputs = [B2DMuNuInputFake]
B2DMuNuTupleFakeSS.Decay = "[B+ -> ^(D_s+ -> ^K- ^K+ ^pi+) ^mu+]CC"
B2DMuNuTupleFakeSS.Branches = {"Bs_0"  : "[B+ ->  (D_s+ -> K- K+ pi+)  mu+]CC",
                               "Ds"    : "[B+ -> ^(D_s+ -> K- K+ pi+)  mu+]CC",
                               "Kpl"   : "[B+ ->  (D_s+ -> K- ^K+ pi+)  mu+]CC",
                               "Kmi"   : "[B+ ->  (D_s+ -> ^K- K+ pi+)  mu+]CC",
                               "pi"    : "[B+ ->  (D_s+ -> K- K+ ^pi+)  mu+]CC",
                               "mu"    : "[B+ ->  (D_s+ -> K- K+ pi+) ^mu+]CC"}

B2DMuNuTupleFakeSS.addTool(TupleToolDecay("B"))
B2DMuNuTupleFakeSS.B.InheritTools = True

B2DMuNuTupleFakeSS.addTool(TupleToolDecay("Ds"))
B2DMuNuTupleFakeSS.Ds.InheritTools = True
EWconeDsFakeSS = B2DMuNuTupleFakeSS.Ds.addTupleTool(TupleToolEWTrackIsolation)
EWconeDsFakeSS.ConeStepSize = 0.2
EWconeDsFakeSS.MinConeRadius = 0.4
EWconeDsFakeSS.MaxConeRadius = 0.6
EWconeDsFakeSS.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDsFakeSS.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDsFakeSS.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"
EWconeDsFakeSS.isMC = True

#B2DMuNuTupleFakeSS.addTool(TupleToolDecay("mu"))
#B2DMuNuTupleFakeSS.mu.InheritTools = True
#EWconeMuFakeSS = B2DMuNuTupleFakeSS.mu.addTupleTool(TupleToolEWTrackIsolation)
#EWconeMuFakeSS.ConeStepSize = .2
#EWconeMuFakeSS.MinConeRadius = 0.4
#EWconeMuFakeSS.MaxConeRadius = 0.6
#EWconeMuFakeSS.ExtraParticlesLocation = "StdAllLoosePions"

##################
### Do MCMatch ###
##################

if doMatchedDsst:
    MBsDsstMuNuTuple = myNTUPLE.clone("MB2DsstMuNuTuple")
    MBsDsstMuNuTuple.Inputs = [ "Phys/MatchedBsDsstMuNuComb" ]
    MBsDsstMuNuTuple.Decay = "[B_s0 -> ^(D*_s- -> (D_s- -> ^K- ^K+ ^pi-) gamma) ^mu+]CC"
    MBsDsstMuNuTuple.Branches = {"Bs_0"  : "[B_s0 -> (D*_s- -> (D_s- -> K- K+ pi-) gamma)  mu+]CC",
                              "Dsst"  : "[B_s0 -> ^(D*_s- -> (D_s- -> K- K+ pi-) gamma) mu+]CC",
                              "Ds"    : "[B_s0 -> (D*_s- -> ^(D_s- -> K- K+ pi-) gamma) mu+]CC",
                              "Kpl"   : "[B_s0 -> (D*_s- -> (D_s- -> K- ^K+ pi-) gamma) mu+]CC",
                              "Kmi"   : "[B_s0 -> (D*_s- -> (D_s- -> ^K- K+ pi-) gamma) mu+]CC",
                              "pi"    : "[B_s0 -> (D*_s- -> (D_s- -> K- K+ ^pi-) gamma) mu+]CC",
                              "mu"    : "[B_s0 -> (D*_s- -> (D_s- -> K- K+ pi-) gamma) ^mu+]CC",
                              "gamma" : "[B_s0 -> (D*_s- -> (D_s- -> K- K+ pi-) ^gamma) mu+]CC"
    }

    MBsDsstMuNuTuple.addTool(TupleToolDecay("B"))
    MBsDsstMuNuTuple.B.InheritTools = True
    mySequencer.Members += [MBsDsstMuNuTuple]

if doMatchedNtuples:
    MBsDMuNuTuple = myNTUPLE.clone("MB2DsMuNuTuple")
    MBsDMuNuTuple.Inputs = [ "Phys/MatchedBsDMuNuComb" ] 
    MBsDMuNuTuple.Decay = "[B_s0 => ^(D_s- => ^K- ^K+ ^pi-) ^mu+]CC" 
    MBsDMuNuTuple.Branches = {"Bs_0"  : "[B_s0 ->  (D_s- -> K- K+ pi-)  mu+]CC",
                              "Ds"    : "[B_s0 -> ^(D_s- -> K- K+ pi-)  mu+]CC",
                              "Kpl"   : "[B_s0 ->  (D_s- -> K- ^K+ pi-)  mu+]CC",
                              "Kmi"   : "[B_s0 ->  (D_s- -> ^K- K+ pi-)  mu+]CC",
                              "pi"    : "[B_s0 ->  (D_s- -> K- K+ ^pi-)  mu+]CC",
                              "mu"    : "[B_s0 ->  (D_s- -> K- K+ pi-) ^mu+]CC"}
    MBsDMuNuTuple.addTool(TupleToolDecay("B"))
    MBsDMuNuTuple.B.InheritTools = True
    mySequencer.Members += [MBsDMuNuTuple]
   
#######################
### DaVinci options ###
#######################
DaVinci().EvtMax = myEvents  
DaVinci().SkipEvents = 0
DaVinci().DataType = "2012"
DaVinci().Simulation = True
DaVinci().Lumi = False
DaVinci().PrintFreq = 1000
DaVinci().UserAlgorithms = [ mySequencer ]
#DaVinci().MoniSequence = [B2DMuNuTuple, B2DMuNuTupleSS, B2DMuNuTupleFake, B2DMuNuTupleFakeSS]
if doSoftSelection:
  DaVinci().MoniSequence = [B2DMuNuTuple]
if photonControl:
  DaVinci().MoniSequence = [B2DMuNuTuple, B2DMuNuTupleSS]
if doMatchedNtuples:
  DaVinci().MoniSequence = [ B2DMuNuTuple, B2DMuNuTupleSS, B2DMuNuTupleFake, B2DMuNuTupleFakeSS, MBsDMuNuTuple ]
if doMatchedDsst:
  DaVinci().MoniSequence = [ B2DMuNuTuple, B2DMuNuTupleSS, B2DMuNuTupleFake, B2DMuNuTupleFakeSS, MBsDsstMuNuTuple ]
#DaVinci().MoniSequence += [ mctree ]
#else:
DaVinci().MoniSequence = [B2DMuNuTuple]

DaVinci().TupleFile = rootfilename
#DaVinci().DDDBtag   = detectorDB 
#DaVinci().CondDBtag = conditionDB
#print 'DDDBtag was ', detectorDB, ' and condDBtag was ', conditionDB

DaVinci().InputType = "DST"

if not(Usegrid):
    from GaudiConf import IOHelper
    IOHelper().inputFiles([
    "root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000001_2.dst?svcClass=lhcbDst",
    "root://lhcb-sdpd15.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbdisk/lhcb/MC/2015/DST/00048906/0000/00048906_00000002_2.dst",
    "root://se.cat.cbpf.br:1094//dpm/cat.cbpf.br/home/lhcb/MC/2015/DST/00048906/0000/00048906_00000003_2.dst",
    "root://tcd4.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbtape/lhcb/MC/2015/DST/00048906/0000/00048906_00000004_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000005_2.dst",
    "root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/archive/lhcb/MC/2015/DST/00048906/0000/00048906_00000006_2.dst?svcClass=lhcbRawRdst",
    "root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000007_2.dst?svcClass=lhcbDst",
    "root://ccdcacli265.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048906/0000/00048906_00000008_2.dst",
    "root://storage01.lcg.cscs.ch:1094/pnfs/lcg.cscs.ch/lhcb/lhcb/MC/2015/DST/00048906/0000/00048906_00000009_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000010_2.dst",
    "root://ccdcacli264.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048906/0000/00048906_00000011_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000012_2.dst",
    "root://f01-080-123-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048906/0000/00048906_00000013_2.dst",
    "root://grid05.lal.in2p3.fr:1094//dpm/lal.in2p3.fr/home/lhcb/MC/2015/DST/00048906/0000/00048906_00000014_2.dst",
    "root://tbit00.nipne.ro:1094//dpm/nipne.ro/home/lhcb/MC/2015/DST/00048906/0000/00048906_00000015_2.dst",
    "root://storage01.lcg.cscs.ch:1094/pnfs/lcg.cscs.ch/lhcb/lhcb/MC/2015/DST/00048906/0000/00048906_00000016_2.dst",
    "root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000017_2.dst?svcClass=lhcbDst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000018_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000019_2.dst",
    "root://heplnx237.pp.rl.ac.uk:1094/pnfs/pp.rl.ac.uk/data/lhcb/lhcb/MC/2015/DST/00048906/0000/00048906_00000020_2.dst",
    "root://door03.pic.es:1094/pnfs/pic.es/data/lhcb/MC/2015/DST/00048906/0000/00048906_00000021_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000022_2.dst",
    "root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000023_2.dst?svcClass=lhcbDst",
    "root://storage01.lcg.cscs.ch:1094/pnfs/lcg.cscs.ch/lhcb/lhcb/MC/2015/DST/00048906/0000/00048906_00000024_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000025_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000027_2.dst",
    "root://f01-080-123-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048906/0000/00048906_00000028_2.dst",
    "root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000029_2.dst?svcClass=lhcbDst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000030_2.dst",
    "root://ccdcacli264.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048906/0000/00048906_00000031_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000032_2.dst",
    "root://marsedpm.in2p3.fr:1094//dpm/in2p3.fr/home/lhcb/MC/2015/DST/00048906/0000/00048906_00000033_2.dst",
    "root://f01-080-125-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048906/0000/00048906_00000034_2.dst",
    "root://storage01.lcg.cscs.ch:1094/pnfs/lcg.cscs.ch/lhcb/lhcb/MC/2015/DST/00048906/0000/00048906_00000035_2.dst",
    "root://heplnx230.pp.rl.ac.uk:1094/pnfs/pp.rl.ac.uk/data/lhcb/lhcb/MC/2015/DST/00048906/0000/00048906_00000036_2.dst",
    "root://lhcb-sdpd15.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbdisk/lhcb/MC/2015/DST/00048906/0000/00048906_00000037_2.dst",
    "root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048906/0000/00048906_00000039_2.dst",
    
    #"root://by32-4.grid.sara.nl:1094/pnfs/grid.sara.nl/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000001_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000002_2.dst",
    #"root://lhcb-sdpd14.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbdisk/lhcb/MC/2015/DST/00048896/0000/00048896_00000003_2.dst",
    #"root://ccdcacli264.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000004_2.dst",
    #"root://by32-4.grid.sara.nl:1094/pnfs/grid.sara.nl/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000005_2.dst",
    #"root://tbit00.nipne.ro:1094//dpm/nipne.ro/home/lhcb/MC/2015/DST/00048896/0000/00048896_00000006_2.dst",
    #"root://ccdcacli265.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000007_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000008_2.dst",
    #"root://clhcbstager.ads.rl.ac.uk//castor/ads.rl.ac.uk/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000009_2.dst?svcClass=lhcbDst",
    #"root://ccdcacli264.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000010_2.dst",
    #"root://se.cat.cbpf.br:1094//dpm/cat.cbpf.br/home/lhcb/MC/2015/DST/00048896/0000/00048896_00000012_2.dst",
    #"root://ccdcacli265.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000013_2.dst",
    #"root://ccdcacli265.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000014_2.dst",
    #"root://storage01.lcg.cscs.ch:1094/pnfs/lcg.cscs.ch/lhcb/lhcb/MC/2015/DST/00048896/0000/00048896_00000015_2.dst",
    #"root://f01-080-125-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048896/0000/00048896_00000016_2.dst",
    #"root://door06.pic.es:1094/pnfs/pic.es/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000017_2.dst",
    #"root://f01-080-125-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048896/0000/00048896_00000018_2.dst",
    #"root://f01-080-123-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048896/0000/00048896_00000019_2.dst",
    #"root://f01-080-125-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048896/0000/00048896_00000020_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000021_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000022_2.dst",
    #"root://heplnx235.pp.rl.ac.uk:1094/pnfs/pp.rl.ac.uk/data/lhcb/lhcb/MC/2015/DST/00048896/0000/00048896_00000023_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000024_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000025_2.dst",
    #"root://door04.pic.es:1094/pnfs/pic.es/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000026_2.dst",
    #"root://bohr3226.tier2.hep.manchester.ac.uk:1094//dpm/tier2.hep.manchester.ac.uk/home/lhcb/lhcb/MC/2015/DST/00048896/0000/00048896_00000027_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000028_2.dst",
    #"root://lhcb-sdpd14.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbdisk/lhcb/MC/2015/DST/00048896/0000/00048896_00000029_2.dst",
    #"root://tbit00.nipne.ro:1094//dpm/nipne.ro/home/lhcb/MC/2015/DST/00048896/0000/00048896_00000030_2.dst",
    #"root://lhcb-sdpd14.t1.grid.kiae.ru:1094/t1.grid.kiae.ru/data/lhcb/lhcbdisk/lhcb/MC/2015/DST/00048896/0000/00048896_00000031_2.dst",
    #"root://f01-080-123-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048896/0000/00048896_00000032_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000033_2.dst",
    #"root://f01-080-125-e.gridka.de:1094/pnfs/gridka.de/lhcb/MC/2015/DST/00048896/0000/00048896_00000034_2.dst",
    #"root://ccdcacli264.in2p3.fr:1094/pnfs/in2p3.fr/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000035_2.dst",
    #"root://door06.pic.es:1094/pnfs/pic.es/data/lhcb/MC/2015/DST/00048896/0000/00048896_00000036_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000038_2.dst",
    #"root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/MC/2015/DST/00048896/0000/00048896_00000039_2.dst"
    ]
    ,clear=True)
MessageSvc().Format = "% F%60W%S%7W%R%T %0W%M"
MessageSvc().OutputLevel = INFO
