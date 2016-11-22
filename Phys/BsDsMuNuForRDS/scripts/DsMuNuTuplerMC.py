########################################################################
# Options for Bs->DsMuNu ntuples 
########################################################################

from DaVinci.Configuration import *
from Configurables import DaVinci
from Gaudi.Configuration import *
from Configurables import GaudiSequencer, DecayTreeTuple, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS, FilterDesktop, TupleToolMCTruth, MCTupleToolKinematic, MCTupleToolHierarchy, MCTupleToolPID, TupleToolSLTools, TupleToolEWTrackIsolation, TupleToolDalitz, TupleToolIsoGeneric
from Configurables import CombineParticles,  FilterDesktop
from Configurables import OfflineVertexFitter
from Configurables import LoKi__VoidFilter as VoidFilter
from Configurables import SubstitutePID, SubPIDMMFilter
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from StandardParticles import StdLoosePi02gg, StdLooseResolvedPi0, StdLooseMergedPi0, StdVeryLooseAllPhotons

########################################################################
### Configure the following options 
########################################################################

#### Only needed if you run in local. These are used by TupleToolMuonIsolation AND also the algo to make BDTS cut if you are making it
weightFile     = "/afs/cern.ch/user/s/sogilvy/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/utils/TMVA_7Dec.weights.xml"
flatteningFile=  "/afs/cern.ch/user/s/sogilvy/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/utils/HflatBDTS_7Dec.root"
isoBDT1File    = "/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_1_BDT.weights.xml"
isoBDT2File    = "/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_8_BDT.weights.xml"
isoBDT3File    = "/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_9_BDT.weights.xml"
isoBDT4File    = "/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_4_BDT.weights.xml"

rootfilename = "TupleRDS.root" ## output file name
Usegrid = False
myEvents = -1

doStripping = True ## run the stripping over the events
doMatchedNtuples = True ## does the MC mathching for all the decays

############################
###   DV configuration ####
############################
detectorDB = "head-20120413"
conditionDB = "sim-20120727-vc-mu100"

########################################################################
###  Configuration ends but CHECK to the DV configuration at the end
########################################################################

mySequencer = GaudiSequencer("mySequencer")
from Configurables import EventCountHisto,  LoKi__Hybrid__TupleTool

if Usegrid:
    myEvents = -1
    weightFile     = "TMVA_7Dec.weights.xml"
    flatteningFile =  "HflatBDTS_7Dec.root"
    isoBDT1File    = "600_2500_4_30_0.75_1_1_BDT.weights.xml"
    isoBDT2File    = "600_2500_4_30_0.75_1_8_BDT.weights.xml"
    isoBDT3File    = "600_2500_4_30_0.75_1_9_BDT.weights.xml"
    isoBDT4File    = "600_2500_4_30_0.75_1_4_BDT.weights.xml"

B2DMuNuInput     = "/Event/Phys/b2DsMuXB2DMuForTauMuLine/Particles"
B2DMuNuInputFake = "/Event/Semileptonic/Phys/B2DMuNuX_Ds_FakeMuon/Particles"

## Check the number of PVs
from Configurables import CheckPV
checkPV = CheckPV('CheckPVMin1')
checkPV.MinPVs = 1
mySequencer.Members += [checkPV]

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
                    #, "TupleToolPropertime"
                    , "TupleToolRecoStats"
                    , "TupleToolTrigger"
                    , "TupleToolVtxIsoln"
                    , "TupleToolTISTOS"
                    , "TupleToolTrackInfo"
                    , "TupleToolMuonIsolation"
                    , "TupleToolMCTruth"
                    , "TupleToolSLTools"
                    , "TupleToolDalitz"
                    , "TupleToolIsoGeneric"
                    ]

from Configurables import TupleToolGeometry
myNTUPLE.addTool(TupleToolGeometry)
myNTUPLE.TupleToolGeometry.OutputLevel = INFO
myNTUPLE.TupleToolGeometry.Verbose = True
myNTUPLE.TupleToolGeometry.RefitPVs = True

from Configurables import TupleToolMuonIsolation
myNTUPLE.addTool(TupleToolMuonIsolation)
myNTUPLE.TupleToolMuonIsolation.BDTSRootFile = flatteningFile
myNTUPLE.TupleToolMuonIsolation.BDTSXMLFile  = weightFile  
myNTUPLE.TupleToolMuonIsolation.isMC = True
myNTUPLE.TupleToolMuonIsolation.isoBDT1_xmlFile = isoBDT1File
myNTUPLE.TupleToolMuonIsolation.isoBDT2_xmlFile = isoBDT2File
myNTUPLE.TupleToolMuonIsolation.isoBDT3_xmlFile = isoBDT3File
myNTUPLE.TupleToolMuonIsolation.isoBDT4_xmlFile = isoBDT4File
myNTUPLE.TupleToolMuonIsolation.OutputLevel = ERROR

########################################################
## ----------  Store Triggers  ---------##
########################################################

L0Triggers = ["L0MuonDecision", "L0DiMuonDecision", "L0HadronDecision"]
##            ['Muon',               'DiMuon',               '  Hadron',     'Electron',  'Photon','PhotonHi','ElectronHi']

Hlt1Triggers = [  "Hlt1SingleMuonNoIPDecision", "Hlt1SingleMuonHighPTDecision", "Hlt1TrackAllL0Decision", "Hlt1TrackMuonDecision"
                  ,"Hlt1TrackAllL0.*Decision"]

Hlt2Triggers = [
    ## muon lines
    "Hlt2XcMuXForTauB2XcMuDecision", "Hlt2XcMuXForTauB2XcFakeMuDecision" 
#    "Hlt2DiMuonDecision",  "Hlt2DiMuonLowMassDecision",
#    "Hlt2DiMuonJPsiDecision",  "Hlt2DiMuonJPsiHighPTDecision",  "Hlt2DiMuonPsi2SDecision",
#    "Hlt2DiMuonDetachedDecision",  "Hlt2DiMuonDetachedJPsiDecision", "Hlt2DiMuonDetachedHeavyDecision", "Hlt2TriMuonTauDecision",
    ## hadron/Topo lines
#    "Hlt2B2HHDecision",
#    "Hlt2DiMuonBDecision",  "Hlt2DiMuonZDecision",
    "Hlt2TopoMu2BodyBBDTDecision", "Hlt2TopoMu3BodyBBDTDecision", "Hlt2TopoMu4BodyBBDTDecision",
    "Hlt2Topo2BodyBBDTDecision",   "Hlt2Topo3BodyBBDTDecision",   "Hlt2Topo4BodyBBDTDecision",
    "Hlt2Topo2BodySimpleDecision", "Hlt2Topo3BodySimpleDecision", "Hlt2Topo4BodySimpleDecision",
    ##others
#    "Hlt2PassThroughDecision",
#    "Hlt2TransparentDecision",
#    "Hlt2IncPhiDecision",
    ## inclusive decisions
#    "Hlt2DiMuonDY.*Decision","Hlt2TopoE.*Decision", "Hlt2Topo.*Decision",  "Hlt2Charm.*Decision", "Hlt2DiElectron.*Decision", "Hlt2.*GammaDecision"
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

from Configurables import TupleToolSLTools
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
EWconeDs.ConeStepSize = .2
EWconeDs.MinConeRadius = 0.4
EWconeDs.MaxConeRadius = 0.6
EWconeDs.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDs.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDs.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"

B2DMuNuTuple.addTool(TupleToolDecay("mu"))
B2DMuNuTuple.mu.InheritTools = True
EWconeMu = B2DMuNuTuple.mu.addTupleTool(TupleToolEWTrackIsolation)
EWconeMu.ConeStepSize = .2
EWconeMu.MinConeRadius = 0.4
EWconeMu.MaxConeRadius = 0.6
EWconeMu.ExtraParticlesLocation = "StdAllLoosePions"

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

B2DMuNuTupleSS.addTool(TupleToolDecay("B"))
B2DMuNuTupleSS.B.InheritTools = True

B2DMuNuTupleSS.addTool(TupleToolDecay("Ds"))
B2DMuNuTupleSS.Ds.InheritTools = True
EWconeDsSS = B2DMuNuTupleSS.Ds.addTupleTool(TupleToolEWTrackIsolation)
EWconeDsSS.ConeStepSize = .2
EWconeDsSS.MinConeRadius = 0.4
EWconeDsSS.MaxConeRadius = 0.6
EWconeDsSS.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDsSS.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDsSS.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"

B2DMuNuTupleSS.addTool(TupleToolDecay("mu"))
B2DMuNuTupleSS.mu.InheritTools = True
EWconeMuSS = B2DMuNuTupleSS.mu.addTupleTool(TupleToolEWTrackIsolation)
EWconeMuSS.ConeStepSize = .2
EWconeMuSS.MinConeRadius = 0.4
EWconeMuSS.MaxConeRadius = 0.6
EWconeMuSS.ExtraParticlesLocation = "StdAllLoosePions"

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
EWconeDsFake.ConeStepSize = .2
EWconeDsFake.MinConeRadius = 0.4
EWconeDsFake.MaxConeRadius = 0.6
EWconeDsFake.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDsFake.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDsFake.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"

B2DMuNuTupleFake.addTool(TupleToolDecay("mu"))
B2DMuNuTupleFake.mu.InheritTools = True
EWconeMuFake = B2DMuNuTupleFake.mu.addTupleTool(TupleToolEWTrackIsolation)
EWconeMuFake.ConeStepSize = .2
EWconeMuFake.MinConeRadius = 0.4
EWconeMuFake.MaxConeRadius = 0.6
EWconeMuFake.ExtraParticlesLocation = "StdAllLoosePions"

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
EWconeDsFakeSS.ConeStepSize = .2
EWconeDsFakeSS.MinConeRadius = 0.4
EWconeDsFakeSS.MaxConeRadius = 0.6
EWconeDsFakeSS.ExtraParticlesLocation = "StdAllLoosePions"
EWconeDsFakeSS.ExtraPi0sLocation = "StdLoosePi02gg"
EWconeDsFakeSS.ExtraPhotonsLocation = "StdVeryLooseAllPhotons"

B2DMuNuTupleFakeSS.addTool(TupleToolDecay("mu"))
B2DMuNuTupleFakeSS.mu.InheritTools = True
EWconeMuFakeSS = B2DMuNuTupleFakeSS.mu.addTupleTool(TupleToolEWTrackIsolation)
EWconeMuFakeSS.ConeStepSize = .2
EWconeMuFakeSS.MinConeRadius = 0.4
EWconeMuFakeSS.MaxConeRadius = 0.6
EWconeMuFakeSS.ExtraParticlesLocation = "StdAllLoosePions"

##################
### Do MCMatch ###
##################

if doMatchedNtuples:
    MBsDMuNuTuple = myNTUPLE.clone("MB2DsMuNuTuple")
    MBsDMuNuTuple.Inputs = [ "Phys/MatchedBsDMuNuComb" ] 
    MBsDMuNuTuple.Decay = "[B_s0 -> ^(D_s- -> ^K- ^K+ ^pi-) ^mu+]CC" 
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
DaVinci().Simulation   = True
DaVinci().Lumi   = False
DaVinci().UserAlgorithms = [ mySequencer ]
DaVinci().MoniSequence += [B2DMuNuTuple, B2DMuNuTupleSS, B2DMuNuTupleFake, B2DMuNuTupleFakeSS]
if doMatchedNtuples:
    DaVinci().MoniSequence += [ MBsDMuNuTuple ]

DaVinci().TupleFile = rootfilename
DaVinci().DDDBtag   = detectorDB 
DaVinci().CondDBtag = conditionDB
print 'DDDBtag was ', detectorDB, ' and condDBtag was ', conditionDB

DaVinci().InputType = "DST"

if not(Usegrid):
    from GaudiConf import IOHelper
    DaVinci().Input = [
        #"DATAFILE='PFN:/afs/cern.ch/user/r/rvazquez/work/dsts/MC_RDS/00025691_00000002_1.allstreams.dst',TYP='POOL_ROOTTREE' OPT='READ'" ##sig
        "DATAFILE='PFN:/afs/cern.ch/user/r/rvazquez/work/public/00051263_00000005_2.dst',TYP='POOL_ROOTTREE' OPT='READ'"
        ] 
MessageSvc().Format = "% F%60W%S%7W%R%T %0W%M"
MessageSvc().OutputLevel = INFO