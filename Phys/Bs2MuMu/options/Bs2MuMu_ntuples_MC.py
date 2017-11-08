
########################################################################
# Options for Bs->mumu ntuples MC only 
########################################################################

from DaVinci.Configuration import *
from Gaudi.Configuration import *
from Configurables import GaudiSequencer, DecayTreeTuple, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS, FilterDesktop, TupleToolDecayTreeFitter,  LoKi__Hybrid__TupleTool
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence

#from STTools import STOfflineConf
#STOfflineConf.DefaultConf().configureTools()

########################################################################
### Configure the following options 
########################################################################

##### Only needed if you run in local. These are used by tupletoolMuonVariables AND also the algo to make BDTS cut if you are making it
path_to_iso_BDT_weights = "/afs/cern.ch/user/m/mmulder/work/UraniaDev_v7r0/Phys/Bs2MuMu/options/"    
weightFile     = path_to_iso_BDT_weights + "TMVA_7Dec.weights.xml"
flatteningFile=  "/eos/lhcb/wg/RD/BsMuMu/operators/weights/HflatBDTS_7Dec.root"
ZVisoWeightsFile = path_to_iso_BDT_weights + "ZVisoBDTG_BsMuMu.weights.xml"

#Outputfile name
rootfilename = "BsMuMu_ntuples.root" 

#Set as 11, 12, 15 or 16. Selects the datatype = 2012 or 2011 or 2015 or 2016.
Collision = 16

#Set as 20 for stripping 20 or 20r1, set as 21 for stripping 21 or 21r1, set as 24 for stripping 24, set as 26 for stripping 26. If running on stripping 21(r1) on microDST, Leptonic stream you need to use the mDSTs from the MDST.DST reprosessing and need to set MDST_DST_reprocessing = True
stripping = '26'
MDST_DST_reprocessing = False # This should be true if running on S21(r1) Leptonic stream, false for everything else

#Get all isolations from RelatedInfos - this MIST be true if running on stripping 24 or on microDST. In stripping 24 the RelatedInfo variables are present in the Dimuon and Letponic streams. They are in stripping 21 as well but they are wrong in the stripping 21 Dimuon stream
isolations_from_RelatedInfos = True

#This is to include variables needed for BDT isolation studies this must be false if running on microDST.
include_track_block = True

#This is to include the charmonium and bottomonium resonances lines. There are Dimuon and Leptonic lines - the leptonic lines have a huge number of events
include_resonaces = False

#Use the grid
Usegrid = True

#Other options
makeGP = False  # for Reco14 onwards
muID = False 
cutBDTS = False

doMatchedNtuples = True
doMCDecayTreeTuple= True

########################################################################
###  Configuration ends but CHECK to the DV configuration at the end
########################################################################

## configure Track<-->MC relation tables
import LoKiPhysMC.Track2MC_Configuration

mySequencer = GaudiSequencer("mySequencer")
from Configurables import EventCountHisto,  LoKi__Hybrid__EvtTupleTool,  LoKi__Hybrid__TupleTool

if Usegrid:
    weightFile     = "TMVA_7Dec.weights.xml"
    flatteningFile =  "HflatBDTS_7Dec.root"
    ZVisoWeightsFile= "ZVisoBDTG_BsMuMu.weights.xml"

B2HHInput  =      ""
B2MuMuInput =     ""
B2JpsiKInput =    ""
B2JpsiKstInput =  ""
B2JpsiPhiInput =  ""
B2SSInput =  ""
#Lifetime unbiased lines
LTUBB2KKInput =  ""
LTUBBs2MuMuInput =  ""
#Resonace lines
DiMuonHighMassInput =    ""
DiMuonPsi2MuMuTOSInput =    ""
DiMuonJpsi2MuMuTOSInput =    ""
DiMuonIncInput =  ""
#RelatedInfo locations
B2HHRelatedInfoInput =   ""
B2MuMuRelatedInfoInput =   ""
B2JpsiKRelatedInfoInput =   ""
B2JpsiKstRelatedInfoInput =  ""
B2JpsiPhiRelatedInfoInput =  ""
LTUBBs2MuMuRelatedInfoInput =    ""
LTUBB2KKRelatedInfoInput =    ""
B2SSRelatedInfoInput =    ""

prefix = "/Event/AllStreams/" #one container for all MC except low pt bbbar->MuMuX MC
#prefix = "/Event/Bs2MuMu.Strip/" ##for low pt bbbar->MuMuX MC 
if stripping == '20' :
    ## --- default Stripping location
    B2HHInput =      prefix +"Phys/Bs2MuMuLinesNoMuIDLine/Particles"
    B2MuMuInput =    prefix +"Phys/Bs2MuMuLinesWideMassLine/Particles"
    B2JpsiKInput =   prefix +"Phys/Bs2MuMuLinesBu2JPsiKLine/Particles"
    B2JpsiKstInput = prefix +"Phys/Bs2MuMuLinesBd2JPsiKstLine/Particles"
    B2JpsiPhiInput = prefix +"Phys/Bs2MuMuLinesBs2JPsiPhiLine/Particles"
    B2SSInput =      prefix +"Phys/Bs2MuMuLinesSSLine/Particles"
    
    if include_resonaces:
        #Charmonium
        DiMuonJpsi2MuMuTOSInput = prefix +"Phys/FullDSTDiMuonJpsi2MuMuTOSLine/Particles"
        DiMuonPsi2MuMuTOSInput = prefix +"Phys/FullDSTDiMuonPsi2MuMuTOSLine/Particles"
        #Bottomonium:
        DiMuonHighMassInput  = prefix +"Phys/FullDSTDiMuonDiMuonHighMassLine/Particles"

if  stripping == '21' :
    ##Stripping locations on Dimuon dsts
    B2HHInput =      prefix +"Phys/Bs2MuMusNoMuIDLine/Particles"
    B2MuMuInput =    prefix +"Phys/Bs2MuMusWideMassLine/Particles"
    
    ##Locations for related Infos
    B2HHRelatedInfoInput =      prefix +"Phys/Bs2MuMusNoMuIDLine/"
    B2MuMuRelatedInfoInput =    prefix +"Phys/Bs2MuMusWideMassLine/"

    if include_resonaces:
        #Charmonium
        DiMuonJpsi2MuMuTOSInput = prefix +"Phys/FullDSTDiMuonJpsi2MuMuTOSLine/Particles"
        DiMuonPsi2MuMuTOSInput = prefix +"Phys/FullDSTDiMuonPsi2MuMuTOSLine/Particles"
        #Bottomonium:
        DiMuonHighMassInput  = prefix +"Phys/FullDSTDiMuonDiMuonHighMassLine/Particles"

if stripping in ['24', '26']:
    ##Stripping locations on Dimuon dsts
    B2HHInput =      prefix +"Phys/Bs2MuMuLinesNoMuIDLine/Particles"
    B2MuMuInput =    prefix +"Phys/Bs2MuMuLinesWideMassLine/Particles"
    B2JpsiKInput =   prefix +"Phys/Bs2MuMuLinesBu2JPsiKLine/Particles"
    B2JpsiPhiInput = prefix +"Phys/Bs2MuMuLinesBs2JPsiPhiLine/Particles"

    ##Locations for related Infos
    B2HHRelatedInfoInput =      prefix +"Phys/Bs2MuMuLinesNoMuIDLine/"
    B2MuMuRelatedInfoInput =    prefix +"Phys/Bs2MuMuLinesWideMassLine/"
    B2JpsiKRelatedInfoInput =  prefix +"Phys/Bs2MuMusBu2JPsiKSelJpsi/"

    if include_resonaces:
        #Charmonium
        DiMuonJpsi2MuMuTOSInput = prefix +"Phys/FullDSTDiMuonJpsi2MuMuTOSLine/Particles"
        DiMuonPsi2MuMuTOSInput = prefix +"Phys/FullDSTDiMuonPsi2MuMuTOSLine/Particles"
        #Bottomonium:
        DiMuonHighMassInput  = prefix +"Phys/FullDSTDiMuonDiMuonHighMassLine/Particles"

############################
### Configure the ntuple ###
############################
myNTUPLE = DecayTreeTuple('myNTUPLE')

myNTUPLE.ToolList +=  [  "TupleToolGeometry"
                         , "TupleToolKinematic"
                         , "TupleToolEventInfo" 
                         , "TupleToolPid"
                         , "TupleToolPropertime"
                         , "TupleToolRecoStats"
                         , "TupleToolTrigger"
                         , "TupleToolTISTOS"
                         , "TupleToolTrackInfo"
                         , "TupleToolMuonPid"
                         # ,"LoKi::Hybrid::TupleTool/LoKiTool"
                         ,"LoKi::Hybrid::TupleTool/LoKi_All"
                         ,"LoKi::Hybrid::EvtTupleTool/LoKiEvent"
                         #, "TupleToolTrackKink"
                         ]

#############################################
### Configure the TupleToolMuonVariables  ###
#############################################

from Configurables import TupleToolMuonVariables
myNTUPLE.ToolList+=["TupleToolMuonVariables"] 
myNTUPLE.addTool(TupleToolMuonVariables)

#Weights files for 3fb analysis isolations
myNTUPLE.TupleToolMuonVariables.BDTSRootFile = flatteningFile
myNTUPLE.TupleToolMuonVariables.BDTSXMLFile  = weightFile

#If you are running on microDST set this to True to compute only variables which are not isolations in this tool. Default is false. 
myNTUPLE.TupleToolMuonVariables.is_microDST = False

#These are the paths to the weights files used in the BDT isolation computations
myNTUPLE.TupleToolMuonVariables.isoBDT_xmlFilePath =  path_to_iso_BDT_weights
if Usegrid:
    myNTUPLE.TupleToolMuonVariables.isoBDT_xmlFilePath =  "" 

myNTUPLE.TupleToolMuonVariables.isoBDT1_xmlFile = "600_2500_4_30_0.75_1_1_BDT.weights.xml"
myNTUPLE.TupleToolMuonVariables.isoBDT2_xmlFile = "600_2500_4_30_0.75_1_8_BDT.weights.xml"
myNTUPLE.TupleToolMuonVariables.isoBDT3_xmlFile = "600_2500_4_30_0.75_1_9_BDT.weights.xml"
myNTUPLE.TupleToolMuonVariables.isoBDT4_xmlFile = "600_2500_4_30_0.75_1_4_BDT.weights.xml"

#This is information that is used to study and develop isolation variables, if they are set to True the the ntuples produced are very large. They are not needed to compute BDT isolation variables already contained within this tool. Default is false for all.
myNTUPLE.TupleToolMuonVariables.dumpVeloTracks =  False
myNTUPLE.TupleToolMuonVariables.dumpUpstreamTracks =  False
myNTUPLE.TupleToolMuonVariables.dumpFullInfo  =   False
if include_track_block:
    myNTUPLE.TupleToolMuonVariables.dumpVeloTracks =  True
    myNTUPLE.TupleToolMuonVariables.dumpUpstreamTracks =  False
    myNTUPLE.TupleToolMuonVariables.dumpFullInfo  =   True
myNTUPLE.TupleToolMuonVariables.isMC = True

#########################################################
#Set up jet locations - these are in the RelatedInfos 
#########################################################
if not isolations_from_RelatedInfos:   
    from Configurables import DaVinci
    from CommonParticles.Utils import *
    from Configurables import TupleToolJetsForB
    
    #These locations must be used is you are running on low pt bbbar->MuMuX MC 
    #bsmm_locations = {"BsMuMu":"Bs2MuMu.Strip/Phys/Bs2MuMuLinesWideMassLine/Particles",
    #                  "B2HH":"Bs2MuMu.Strip/Phys/Bs2MuMuLinesNoMuIDLine/Particles",
    #                  "B2SS":"Bs2MuMu.Strip/Phys/Bs2MuMuLinesSSLine/Particles", }

    bsmm_locations = {"BsMuMu":"AllStreams/Phys/Bs2MuMuLinesWideMassLine/Particles",
                      "B2HH":"AllStreams/Phys/Bs2MuMuLinesNoMuIDLine/Particles",
                      "B2SS":"AllStreams/Phys/Bs2MuMuLinesSSLine/Particles", }
        
    # JET CONFIGURATION
    ## standard jetID                                                                        
    from JetAccessories.JetMaker_Config import JetMakerConf
    StdJetsNoJetIDNoBan = JetMakerConf("StdJetsNoJetID",
                                       R = 0.7 ,
                                       PtMin = 500.,
                                       JetIDCut = False).algorithms[0]
    
    jetlocation1 = updateDoD ( StdJetsNoJetIDNoBan ).keys()[0]
    
    # the muons banning and B adding is line dependent (need to provide the location of the muons/B!)
    def create_stdjets(line_location,stdjets_name_ban, stdjets_name_addb):
        
        # ban particles
        myconf1 = JetMakerConf(stdjets_name_ban,
                               R = 0.7 ,
                               PtMin = 500.,
                               listOfParticlesToBan = [line_location],
                               JetIDCut = False).algorithms[0]
        
        locations2 = updateDoD ( myconf1 ).keys()[0]
        
        # consider particles together
        myconf2 = JetMakerConf(stdjets_name_addb,
                               Inputs = ['Phys/PFParticles/Particles',line_location],
                               R = 0.7,
                               PtMin = 500.,
                               JetIDCut = False).algorithms[0]
        locations3 = updateDoD ( myconf2 ).keys()[0]
        return locations2,locations3
    
    jetlocations2,jetlocations3={},{}
# create the other two types of stdjets
    
    for name in bsmm_locations:
        locs = create_stdjets(bsmm_locations[name],"StdJetsNoID"+name+"Ban", "StdJetsNoID"+name+"Bcand")
        jetlocations2[name]=locs[0];jetlocations3[name]=locs[1]
        
    tupletooljets = {}
    for name in bsmm_locations:
        # configure tupletooljetsforb
        tupletooljets[name] = TupleToolJetsForB(name)
        tupletooljets[name].LocationJetsNoRemove = jetlocation1
        tupletooljets[name].LocationJetsNoMu = jetlocations2[name]
        tupletooljets[name].LocationJetsForceB = jetlocations3[name]
    
########################################################
##        ----------  Store Triggers         ---------##
########################################################

L0Triggers = ["L0MuonDecision", "L0DiMuonDecision", "L0HadronDecision", "L0ElectronDecision", "L0ElectronHiDecision", "L0PhotonDecision", "L0PhotonHiDecision" ]

Hlt1Triggers = [  "Hlt1SingleMuonNoIPDecision", "Hlt1SingleMuonHighPTDecision", "Hlt1SingleElectronNoIPDecision"
                  ,"Hlt1TrackAllL0Decision", "Hlt1TrackMuonDecision" ,"Hlt1TrackPhotonDecision" 
                  ,"Hlt1TrackAllL0.*Decision"
                  ,"Hlt1DiMuonLowMassDecision" ,"Hlt1DiMuonHighMassDecision", "Hlt1MB.*Decision"]

if Collision == 12 :
    Hlt1Triggers += ["Hlt1TrackAllL0TightDecision"]
if stripping == '24':
       Hlt1Triggers += [
    "Hlt1TrackMuonDecision",
    "Hlt1DiMuonHighMassDecision",
    "Hlt1DiMuonLowMassDecision",
    "Hlt1SingleMuonNoIPDecision",
    "Hlt1SingleMuonHighPTDecision",
    "Hlt1MultiMuonNoL0Decision",
    "Hlt1CalibMuonAlignJpsiDecision",
    "Hlt1DiMuonNoL0Decision",
    "Hlt1TrackMVADecision",
    "Hlt1TwoTrackMVADecision",
    "Hlt1B2GammaGammaDecision",
    "Hlt1B2HH_LTUNB_KKDecision",
    "Hlt1B2HH_LTUNB_KPiDecision",
    "Hlt1B2HH_LTUNB_PiPiDecision",
    "Hlt1B2PhiGamma_LTUNBDecision",
    "Hlt1B2PhiPhi_LTUNBDecision",
    "Hlt1CalibHighPTLowMultTrksDecision",
    "Hlt1CalibRICHMirrorRICH1Decision",
    "Hlt1CalibRICHMirrorRICH2Decision",
    "Hlt1CalibTrackingKKDecision",
    "Hlt1CalibTrackingKPiDecision",
    "Hlt1CalibTrackingKPiDetachedDecision",
    "Hlt1CalibTrackingPiPiDecision",
    "Hlt1DiProtonDecision",
    "Hlt1DiProtonLowMultDecision",
    "Hlt1IncPhiDecision",
    "Hlt1L0AnyDecision",
    "Hlt1L0AnyNoSPDDecision",
    "Hlt1LumiDecision",
    "Hlt1MBNoBiasDecision",
    "Hlt1MBNoBiasRateLimitedDecision",
    "Hlt1NoBiasNonBeamBeamDecision",
    "Hlt1NoPVPassThroughDecision",
    "Hlt1ODINTechnicalDecision",
    "Hlt1SingleElectronNoIPDecision",
    "Hlt1Tell1ErrorDecision",
    "Hlt1TrackMuonNoSPDDecision",
    "Hlt1VeloClosingMicroBiasDecision",
    "Hlt1BeamGasCrossingParasiticDecision",
    "Hlt1ErrorEventDecision",
    "Hlt1GlobalDecision",
    ]

if stripping == '26':
    Hlt1Triggers += ["Hlt1B2HH_LTUNB_KKDecision", "Hlt1B2HH_LTUNB_KPiDecision", "Hlt1B2HH_LTUNB_PiPiDecision", "Hlt1CalibMuonAlignJpsiDecision", "Hlt1DiMuonHighMassDecision", "Hlt1DiMuonLowMassDecision", "Hlt1DiMuonNoIPDecision", "Hlt1DiMuonNoL0Decision", "Hlt1DiProtonDecision", "Hlt1GlobalDecision", "Hlt1IncPhiDecision", "Hlt1L0AnyDecision", "Hlt1L0AnyNoSPDDecision", "Hlt1LowMultMuonDecision", "Hlt1MultiDiMuonNoIPDecision", "Hlt1MultiMuonNoL0Decision", "Hlt1SingleMuonHighPTDecision", "Hlt1SingleMuonNoIPDecision", "Hlt1TrackMVADecision", "Hlt1TrackMVALooseDecision", "Hlt1TrackMuonDecision", "Hlt1TrackMuonMVADecision", "Hlt1TwoTrackMVADecision", "Hlt1TwoTrackMVALooseDecision"] 
  
Hlt2Triggers = [
    ## muon lines
    "Hlt2SingleMuonDecision", "Hlt2SingleMuonLowPTDecision", "Hlt2SingleMuonHighPTDecision",
    "Hlt2DiMuonDecision",  "Hlt2DiMuonLowMassDecision",
    "Hlt2DiMuonJPsiDecision",  "Hlt2DiMuonJPsiHighPTDecision",  "Hlt2DiMuonPsi2SDecision",
    "Hlt2DiMuonDetachedDecision",  "Hlt2DiMuonDetachedJPsiDecision", "Hlt2DiMuonDetachedHeavyDecision", "Hlt2TriMuonTauDecision",
    ## hadron/Topo lines
    "Hlt2B2HHDecision",
    "Hlt2DiMuonBDecision",  "Hlt2DiMuonZDecision",
    "Hlt2TopoMu2BodyBBDTDecision", "Hlt2TopoMu3BodyBBDTDecision", "Hlt2TopoMu4BodyBBDTDecision",
    "Hlt2Topo2BodyBBDTDecision",   "Hlt2Topo3BodyBBDTDecision",   "Hlt2Topo4BodyBBDTDecision",
    "Hlt2Topo2BodySimpleDecision", "Hlt2Topo3BodySimpleDecision", "Hlt2Topo4BodySimpleDecision",
    ##others
    "Hlt2PassThroughDecision",
    "Hlt2TransparentDecision",
    "Hlt2IncPhiDecision",
    ## inclusive decisions
    "Hlt2DiMuonDY.*Decision","Hlt2TopoE.*Decision", "Hlt2Topo.*Decision",  "Hlt2Charm.*Decision", "Hlt2DiElectron.*Decision", "Hlt2.*GammaDecision"
    ]

if stripping == '24':
    Hlt2Triggers += [
        "Hlt2B2HHDecision",
        "Hlt2B2K0pi0iDecision",
        "Hlt2B2KKDecision",
        "Hlt2B2KPiDecision",
        "Hlt2B2Kpi0Decision",
        "Hlt2B2PiPiDecision",
        "Hlt2Bs2PhiPhiDecision",
        "Hlt2DebugEventDecision",
        "Hlt2DiMuonBDecision",
        "Hlt2DiMuonDetachedDecision",
        "Hlt2DiMuonDetachedHeavyDecision",
        "Hlt2DiMuonDetachedJPsiDecision",
        "Hlt2DiMuonDetachedPsi2SDecision",
        "Hlt2DiMuonJPsiDecision",
        "Hlt2DiMuonJPsiHighPTDecision",
        "Hlt2DiMuonPsi2SDecision",
        "Hlt2DiMuonPsi2SHighPTDecision",
        "Hlt2DiMuonSoftDecision",
        "Hlt2DiMuonZDecision",
        "Hlt2DiPhiDecision",
        "Hlt2DiProtonDecision",
        "Hlt2DiProtonLowMultDecision",
        "Hlt2EWDiElectronDYDecision",
        "Hlt2EWDiElectronHighMassDecision",
        "Hlt2EWDiMuonDY1Decision",
        "Hlt2EWDiMuonDY2Decision",
        "Hlt2EWDiMuonDY3Decision",
        "Hlt2EWDiMuonDY4Decision",
        "Hlt2EWDiMuonZDecision",
        "Hlt2EWSingleElectronHighPtDecision",
        "Hlt2EWSingleElectronLowPtDecision",
        "Hlt2EWSingleElectronVHighPtDecision",
        "Hlt2EWSingleMuonHighPtDecision",
        "Hlt2EWSingleMuonLowPtDecision",
        "Hlt2EWSingleMuonVHighPtDecision",
        "Hlt2EWSingleTauHighPt2ProngDecision",
        "Hlt2EWSingleTauHighPt3ProngDecision",
        "Hlt2ForwardDecision",
        "Hlt2IncPhiDecision",
        "Hlt2Lb2PKDecision",
        "Hlt2Lb2PPiDecision",
        "Hlt2LumiDecision",
        "Hlt2NoBiasNonBeamBeamDecision",
        "Hlt2PassThroughDecision",
        "Hlt2Phi2KsKsDecision",
        "Hlt2Phi2KsKsD0CtrlDecision",
        "Hlt2SingleMuonDecision",
        "Hlt2SingleMuonHighPTDecision",
        "Hlt2SingleMuonLowPTDecision",
        "Hlt2SingleMuonNoSPDDecision",
        "Hlt2SingleMuonRareDecision",
        "Hlt2SingleMuonVHighPTDecision",
        "Hlt2Topo2BodyDecision",
        "Hlt2Topo3BodyDecision",
        "Hlt2Topo4BodyDecision",
        "Hlt2TopoMu2BodyDecision",
        "Hlt2TopoMu3BodyDecision",
        "Hlt2TopoMu4BodyDecision",
        "Hlt2TrackEff_D0ToKpiKaonProbeDecision",
        "Hlt2TrackEff_D0ToKpiPionProbeDecision",
        "Hlt2TransparentDecision",
        "Hlt2TriMuonDetachedDecision",
        "Hlt2TriMuonTau23MuDecision",
        "Hlt2XcMuXForTauB2XcFakeMuDecision",
        "Hlt2XcMuXForTauB2XcMuDecision",
        "Hlt2ErrorEventDecision"
        ]

if stripping == '26':
    Hlt2Triggers += [
        "Hlt2B2HH_B2HHDecision",
        "Hlt2B2HH_B2KKDecision",
        "Hlt2B2HH_B2KPiDecision",
        "Hlt2B2HH_B2PiPiDecision",
        "Hlt2B2HH_Lb2PKDecision",
        "Hlt2B2HH_Lb2PPiDecision",
        "Hlt2DebugEventDecision",
        "Hlt2DiMuonDetachedDecision",
        "Hlt2DiMuonDetachedHeavyDecision",
        "Hlt2DiMuonDetachedJPsiDecision",
        "Hlt2DiMuonDetachedPsi2SDecision",
        "Hlt2DiMuonJPsiHighPTDecision",
        "Hlt2DiMuonPsi2SHighPTDecision",
        "Hlt2DiMuonSoftDecision",
        "Hlt2DiMuonZDecision",
        "Hlt2EWDiElectronDYDecision",
        "Hlt2EWDiElectronHighMassDecision",
        "Hlt2EWDiMuonDY1Decision",
        "Hlt2EWDiMuonDY2Decision",
        "Hlt2EWDiMuonDY3Decision",
        "Hlt2EWDiMuonDY4Decision",
        "Hlt2EWDiMuonZDecision",
        "Hlt2ErrorEventDecision",
        "Hlt2GlobalDecision",
        "Hlt2LowMultMuonDecision",
        "Hlt2LumiDecision",
        "Hlt2MBNoBiasDecision",
        "Hlt2PassThroughDecision",
        "Hlt2SingleMuonDecision",
        "Hlt2SingleMuonHighPTDecision",
        "Hlt2SingleMuonLowPTDecision",
        "Hlt2SingleMuonRareDecision",
        "Hlt2SingleMuonVHighPTDecision",
        "Hlt2Topo2BodyDecision",
        "Hlt2Topo3BodyDecision",
        "Hlt2Topo4BodyDecision",
        "Hlt2TopoE3BodyDecision",
        "Hlt2TopoE4BodyDecision",
        "Hlt2TopoEE2BodyDecision",
        "Hlt2TopoMu2BodyDecision",
        "Hlt2TopoMu3BodyDecision",
        "Hlt2TopoMu4BodyDecision",
        "Hlt2TopoMuE2BodyDecision",
        "Hlt2TopoMuE3BodyDecision",
        "Hlt2TopoMuE4BodyDecision",
        "Hlt2TopoMuMu2BodyDecision",
        "Hlt2TopoMuMu3BodyDecision",
        "Hlt2TopoMuMu4BodyDecision",
        "Hlt2TopoMuMuDDDecision",
        "Hlt2TransparentDecision",
        "Hlt2TriMuonDetachedDecision",
        "Hlt2TriMuonTau23MuDecision",
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
#myNTUPLE.TupleToolTISTOS.PIDList = [511, 521, 531] # to include trigger information for all particles

########################################################
##### ----------  Config for muon ID    ---------#######
########################################################

if muID:
    myNTUPLE.ToolList+= [ "TupleToolMuonIDCalib"]
    from Configurables import TupleToolMuonIDCalib
    myNTUPLE.addTool(TupleToolMuonIDCalib)
    myNTUPLE.TupleToolMuonIDCalib.XFOIParameter1 = [5.5, 4.0, 3.3, 2.8,
                         5.2, 3.6, 2.4, 2.4,
                         5.7, 4.4, 2.8, 2.3,
                         5.1, 3.1, 2.3, 2.1,
                         5.8, 3.4, 2.6, 2.8]
    myNTUPLE.TupleToolMuonIDCalib.XFOIParameter2 = [11., 3., 1., 1.,
                         31., 28., 21., 17.,
                         30., 31., 27., 22.,
                         28., 33., 35., 47.,
                         31., 39., 56., 151.]
    myNTUPLE.TupleToolMuonIDCalib.XFOIParameter3 = [0.2, 0.08, 0.03, 0.1,
                         0.06, 0.08, 0.10, 0.15,
                         0.04, 0.06, 0.09, 0.12,
                         0.08, 0.15, 0.23, 0.36,
                         0.07, 0.14, 0.24, 0.49]
    myNTUPLE.TupleToolMuonIDCalib.YFOIParameter1 = [2.8, 1.7, -153., 1.9,
                         3.3, 2.1, 1.7, 1.6,
                         3.6, 2.8, 1.9, 1.8,
                          4.4, 3.3, 2.2, 2.2,
                         4.8, 3.9, 2.6, 2.3]
    myNTUPLE.TupleToolMuonIDCalib.YFOIParameter2 = [3., 2., 156., 0.,
                         17., 15., 9., 5.,
                         26., 25., 16., 15.,
                         30., 49., 57., 92.,
                         32., 55., 96., 166.]
    myNTUPLE.TupleToolMuonIDCalib.YFOIParameter3 = [0.03, 0.02, 0.00, 0.09,
                         0.13, 0.19, 0.19, 0.24,
                         0.11, 0.19, 0.21, 0.32,
                         0.10, 0.22, 0.30, 0.52,
                         0.08, 0.20, 0.34, 0.52]

## ---------- For storing some event variables   ---------##
    
LoKiEventTuple = LoKi__Hybrid__EvtTupleTool("LoKiEvent")
LoKiEventTuple.Preambulo = [ 
    "from LoKiTracks.decorators import *",
    "from LoKiCore.functions import *"
    ]
LoKiEventTuple.VOID_Variables =  {
    "nTTCls"   :  " CONTAINS('Raw/TT/Clusters') " , ## number of Clusters in TT 
    "nVeloTraks_All"   :   " TrSOURCE('Rec/Track/Best' , TrVELO) >> TrSIZE " , ## number of Velo tracks
    "nLongTrks"   :   " TrSOURCE('Rec/Track/Best', TrLONG) >> TrSIZE " , ## number of Long tracks
    "nDownTrks"   :   " TrSOURCE('Rec/Track/Best', TrDOWNSTREAM) >> TrSIZE " , ## number of Down tracks
    "nTTrks"      :   " TrSOURCE('Rec/Track/Best', TrTTRACK) >> TrSIZE ",  ## number of T tracks
    }

myNTUPLE.addTool(LoKiEventTuple)

#######################################################
############## Do Matched ntuples  ################
#######################################################
from Configurables import NoPIDsParticleMaker,TrackSelector 
from Configurables import CombineParticles,  FilterDesktop
from Configurables import OfflineVertexFitter
from Configurables import LoKi__VoidFilter as VoidFilter
from Configurables import SubstitutePID, SubPIDMMFilter
if doMatchedNtuples :

    from Configurables import CheckPV
    ##SelCheckPV  = Selection ("MatchPV",
    ##                          Algorithm =  CheckPV('TwoPV', MinPVs=1),
    ##                          RequiredSelections = [] )
    ##seqCheckPV =  SelectionSequence('SeqPV', SelCheckPV )

    _Preambulo = ["from LoKiPhysMC.decorators import *","from LoKiPhysMC.functions import mcMatch"]
    _stdLooseMuons = DataOnDemand(Location = "Phys/StdLooseMuons/Particles")
    _stdAllNoPIDsPions = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")
    _stdAllNoPIDsMuons = DataOnDemand(Location = "Phys/StdAllNoPIDsMuons/Particles")
    _stdAllNoPIDsKaons = DataOnDemand(Location = "Phys/StdAllNoPIDsKaons/Particles")
    _kaons = DataOnDemand(Location='Phys/StdNoPIDsKaons/Particles')
    _stdLoosePions = DataOnDemand(Location = "Phys/StdLoosePions/Particles")
    _stdLooseKaons = DataOnDemand(Location = "Phys/StdLooseKaons/Particles")

    MatchedJpsiComb =  CombineParticles("MatchedJpsiComb") ## makes a particle out of the two muons
    MatchedJpsiComb.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
    MatchedJpsiComb.Preambulo = _Preambulo
    MatchedJpsiComb.addTool( OfflineVertexFitter )
    MatchedJpsiComb.ParticleCombiners.update( { "" : "OfflineVertexFitter"} )
    MatchedJpsiComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedJpsiComb.ReFitPVs = True
    MatchedJpsiComb.DaughtersCuts = { "mu+" : "mcMatch( '[mu+]cc' )"}
    MatchedJpsiComb.MotherCut     =  "mcMatch('J/psi(1S) => mu+ mu-')" ##give error "configure me!" if not set

    SelMJPsi  = Selection ("MatchJPsi",
                           Algorithm = MatchedJpsiComb,
                           RequiredSelections = [ _stdAllNoPIDsMuons ] )

    #B2JpsiK
    MatchedB2JpsiKComb = CombineParticles("MatchedB2JpsiKComb") 
    MatchedB2JpsiKComb.Preambulo = _Preambulo
    MatchedB2JpsiKComb.addTool( OfflineVertexFitter() )
    MatchedB2JpsiKComb.VertexFitters.update( { "" : "OfflineVertexFitter"} )
    MatchedB2JpsiKComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedB2JpsiKComb.ReFitPVs = True
    MatchedB2JpsiKComb.DecayDescriptor = "[B+ -> J/psi(1S) K+]cc"; 
    MatchedB2JpsiKComb.DaughtersCuts = { "K+" : "mcMatch( '[K+]cc' )"}
    MatchedB2JpsiKComb.MotherCut = "mcMatch( '[B+ => J/psi(1S) K+]CC' )" 
    ##see https://twiki.cern.ch/twiki/bin/view/LHCb/FAQ/LoKiNewDecayFinders for the syntax
    SelMB2JpsiK = Selection("MatchB2JpsiK", 
                            Algorithm = MatchedB2JpsiKComb,
                            RequiredSelections=[SelMJPsi,_stdAllNoPIDsKaons])
    ##put a filter in input, selecting only events from the BsMuMu stripping line
    ##bsFilter = VoidFilter("Bs2MuMuInputFilter", Code = "CONTAINS('%s') > 0" % B2MuMuInput)
    SeqMyMatchedBplus = SelectionSequence('SeqMyMatchedBplus', TopSelection  =  SelMB2JpsiK, EventPreSelector = [CheckPV('TwoPV', MinPVs=1)])####, EventPreSelector = [bsFilter])
    ##build the sequence
    SequenceMatchBplus = GaudiSequencer( "SequenceMatchBplus" )
    SequenceMatchBplus.Members += [ SeqMyMatchedBplus.sequence() ]
    DaVinci().UserAlgorithms += [ SequenceMatchBplus ]
    
    #Bs2MuMu
    MatchedBsMuMuComb =  CombineParticles("MatchedBsMuMuComb") ## makes a particle out of the two muons
    ## Note this the DecayDescriptor here is just the name given to the output candidates do NOT put cc!
    ## otherwise you get double candidates 
    MatchedBsMuMuComb.DecayDescriptor = "B_s0 -> mu+ mu-"
    MatchedBsMuMuComb.Preambulo = _Preambulo
    MatchedBsMuMuComb.addTool( OfflineVertexFitter )
    MatchedBsMuMuComb.ParticleCombiners.update( { "" : "OfflineVertexFitter"} )
    MatchedBsMuMuComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedBsMuMuComb.ReFitPVs = True
    MatchedBsMuMuComb.DaughtersCuts = { "mu+" : "mcMatch( '[mu+]cc' )"}
    MatchedBsMuMuComb.MotherCut     =  "mcMatch('[B_s0 => mu+ mu-]CC')" ##give error "configure me!" if not set

    SelMBs2MuMu = Selection("MatchBs2MuMu", 
                            Algorithm = MatchedBsMuMuComb,
                            RequiredSelections=[       _stdAllNoPIDsMuons   ])
    SeqMyMatchedBsMuMu = SelectionSequence('SeqMyMatchedBsMuMu', TopSelection  =  SelMBs2MuMu, EventPreSelector = [CheckPV('TwoPV', MinPVs=1)])
    SequenceMatchBsMuMu = GaudiSequencer( "SequenceMatchBsMuMu" )
    SequenceMatchBsMuMu.Members += [ SeqMyMatchedBsMuMu.sequence() ]
    DaVinci().UserAlgorithms += [ SequenceMatchBsMuMu ]

    #Bds2MuMu
    MatchedBdMuMuComb =  CombineParticles("MatchedBdMuMuComb") ## makes a particle out of the two muons
    ## Note this the DecayDescriptor here is just the name given to the output candidates do NOT put cc!
    ## otherwise you get double candidates 
    MatchedBdMuMuComb.DecayDescriptor = "B0 -> mu+ mu-"
    MatchedBdMuMuComb.Preambulo = _Preambulo
    MatchedBdMuMuComb.addTool( OfflineVertexFitter )
    MatchedBdMuMuComb.ParticleCombiners.update( { "" : "OfflineVertexFitter"} )
    MatchedBdMuMuComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedBdMuMuComb.ReFitPVs = True
    MatchedBdMuMuComb.DaughtersCuts = { "mu+" : "mcMatch( '[mu+]cc' )"}
    MatchedBdMuMuComb.MotherCut     =  "mcMatch('[B0 => mu+ mu-]CC')" ##give error "configure me!" if not set

    SelMBd2MuMu = Selection("MatchBd2MuMu", 
                            Algorithm = MatchedBdMuMuComb,
                            RequiredSelections=[       _stdAllNoPIDsMuons   ])
    SeqMyMatchedBdMuMu = SelectionSequence('SeqMyMatchedBdMuMu', TopSelection  =  SelMBd2MuMu,
                                           EventPreSelector = [CheckPV('TwoPV', MinPVs=1)])
    SequenceMatchBdMuMu = GaudiSequencer( "SequenceMatchBdMuMu" )
    SequenceMatchBdMuMu.Members += [ SeqMyMatchedBdMuMu.sequence() ]
    DaVinci().UserAlgorithms += [ SequenceMatchBdMuMu ]

    #B2KPi
    MatchedBdKPiComb =  CombineParticles("MatchedBdKPiComb",OutputLevel = INFO) ## makes a particle out of the two muons
    MatchedBdKPiComb.DecayDescriptor = "B_s0 -> mu+ mu-"
    MatchedBdKPiComb.Preambulo = _Preambulo
    MatchedBdKPiComb.addTool( OfflineVertexFitter )
    MatchedBdKPiComb.ParticleCombiners.update( { "" : "OfflineVertexFitter"} )
    MatchedBdKPiComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedBdKPiComb.ReFitPVs = True
    #    MatchedBdKPiComb.DaughtersCuts = {  "K+" : "mcMatch( '[K+]cc' )",
    #                                       "pi-": "mcMatch( '[pi-]cc')"}
    # FRA: here we might want to match only the "favoured sign" :  B0-> K+ pi-, and not the other, but it will not make any difference.
    MatchedBdKPiComb.MotherCut     =  "(mcMatch('[B0 => K+ pi-]CC'))|(mcMatch('[B0 => K- pi+]CC'))" ##give error "configure me!" if not set
    SelMBdKPi = Selection("MatchBdKPi", 
                          Algorithm = MatchedBdKPiComb,
                          RequiredSelections=[ _stdAllNoPIDsMuons ])
    SeqMyMatchedBdKPi = SelectionSequence('SeqMyMatchedBdKPi', TopSelection  =  SelMBdKPi, EventPreSelector = [CheckPV('TwoPV', MinPVs=1)])
    SequenceMatchBdKPi = GaudiSequencer( "SequenceMatchBdKPi" )
    SequenceMatchBdKPi.Members += [ SeqMyMatchedBdKPi.sequence() ]
    DaVinci().UserAlgorithms += [ SequenceMatchBdKPi ]

    #B2JpsiPhi
    MatchedphiComb =  CombineParticles("MatchedphiComb") ## makes a particle out of the two muons
    MatchedphiComb.DecayDescriptor = "phi(1020) -> K+ K-"
    MatchedphiComb.Preambulo = _Preambulo
    MatchedphiComb.addTool( OfflineVertexFitter )
    MatchedphiComb.ParticleCombiners.update( { "" : "OfflineVertexFitter"} )
    MatchedphiComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedphiComb.ReFitPVs = True
    MatchedphiComb.DaughtersCuts = { "K+" : "mcMatch( '[K+]cc' )"}
    MatchedphiComb.MotherCut     =  "mcMatch('phi(1020) => K+ K-')" ##give error "configure me!" if not set
    SelMphi  = Selection ("Matchphi",
                          Algorithm = MatchedphiComb,
                          RequiredSelections = [ _stdAllNoPIDsKaons ] )

    MatchedBs2JpsiphiComb = CombineParticles("MatchedBs2JpsiphiComb") 
    MatchedBs2JpsiphiComb.Preambulo = _Preambulo
    MatchedBs2JpsiphiComb.addTool( OfflineVertexFitter() )
    MatchedBs2JpsiphiComb.VertexFitters.update( { "" : "OfflineVertexFitter"} )
    MatchedBs2JpsiphiComb.OfflineVertexFitter.useResonanceVertex = False
    MatchedBs2JpsiphiComb.ReFitPVs = True
    MatchedBs2JpsiphiComb.DecayDescriptor = "B_s0 -> J/psi(1S)  phi(1020)"; 
    MatchedBs2JpsiphiComb.MotherCut = "mcMatch( '[B_s0 => J/psi(1S) phi(1020)]CC' )" 
    SelMBs2Jpsiphi = Selection("MatchBs2Jpsiphi", 
                               Algorithm = MatchedBs2JpsiphiComb,
                               RequiredSelections=[SelMJPsi, SelMphi])
    SeqMyMatchedBsJpsiphi = SelectionSequence('SeqMyMatchedBsJpsiphi', TopSelection  =  SelMBs2Jpsiphi, EventPreSelector = [CheckPV('TwoPV', MinPVs=1)])####, EventPreSelector = [bsFilter])
    SequenceMatchBsJpsiphi = GaudiSequencer( "SequenceMatchBsJpsiphi" )
    SequenceMatchBsJpsiphi.Members += [ SeqMyMatchedBsJpsiphi.sequence() ]
    DaVinci().UserAlgorithms += [ SequenceMatchBsJpsiphi ]

########################################################
#Add in used for MC variables
########################################################

LoKiTuple = LoKi__Hybrid__TupleTool("LoKi_All")
LoKiTuple.Variables = {"BPVDIRA"   : "BPVDIRA"
                     , "BPVVDCHI2" : "BPVVDCHI2"
                     , "BPVIPCHI2" : "BPVIPCHI2()"
                     , "BPVVDZ"    : "BPVVDZ"
                     , "VFASPF"    : "VFASPF(VCHI2/VDOF)"
                     , "DOCAMAX"   : "DOCAMAX"
                     , "MINIPCHI2" : "MIPCHI2DV(PRIMARY)"
                   }
myNTUPLE.addTool(LoKiTuple)  
#myNTUPLE.ToolList +=  ["LoKi::Hybrid::TupleTool/LoKi_All"]
    
from Configurables import  TupleToolMCTruth
MCTruth = TupleToolMCTruth()
MCTruth.ToolList = [
    "MCTupleToolKinematic" ,
    "MCTupleToolHierarchy"
    ]
myNTUPLE.addTool(MCTruth)
myNTUPLE.ToolList += [
    "TupleToolMCTruth"
   ,"TupleToolMCBackgroundInfo"
 #, "TupleToolGeneration"
   ,"MCTupleToolPrimaries"
    ]

#########################################################################
########  DecayTreeFitter extra kinematic variables needed   ###########
#########################################################################
#Bs2MuMuLine and B2HHLine and Bs2MuMu lifetime unbiased
LoKiVariablesMuMu = LoKi__Hybrid__TupleTool('LoKiVariablesMuMu')
LoKiVariablesMuMu.Variables = {
    "DTF_MM"  : "DTF_FUN(MM, False, strings(['mu+',  'mu-']))"
    ,"DTF_M"  : "DTF_FUN(M, False, strings(['mu+',  'mu-']))"
    ,"DTF_P"  : "DTF_FUN(P, False, strings(['mu+',  'mu-']))"
    ,"DTF_PT" : "DTF_FUN(PT, False, strings(['mu+',  'mu-']))"
    ,"DTF_PE" : "DTF_FUN(E, False, strings(['mu+',  'mu-']))"
    ,"DTF_PX" : "DTF_FUN(PX, False, strings(['mu+',  'mu-']))"
    ,"DTF_PY" : "DTF_FUN(PY, False, strings(['mu+',  'mu-']))"
    ,"DTF_PZ" : "DTF_FUN(PZ, False, strings(['mu+',  'mu-']))"
   }
#B2JpsiKLine
LoKiVariablesJpsiK = LoKi__Hybrid__TupleTool('LoKiVariablesJpsiK')
LoKiVariablesJpsiK.Variables = {
        "DTF_MM"  : "DTF_FUN(MM, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_M"  : "DTF_FUN(M, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_P"  : "DTF_FUN(P, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_PT" : "DTF_FUN(PT, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_PE" : "DTF_FUN(E, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_PX" : "DTF_FUN(PX, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_PY" : "DTF_FUN(PY, False, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_PZ" : "DTF_FUN(PZ, False, strings(['J/psi(1S)',  'K+']))"
        }
#B2JpsiKstLine
LoKiVariablesJpsiKst = LoKi__Hybrid__TupleTool('LoKiVariablesJpsiKst')
LoKiVariablesJpsiKst.Variables = { 
        "DTF_MM"  : "DTF_FUN(MM, False, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_M"  : "DTF_FUN(M,  False, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_P"  : "DTF_FUN(P, False , strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_PT" : "DTF_FUN(PT, False , strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_PE" : "DTF_FUN(E,  False, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_PX" : "DTF_FUN(PX, False , strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_PY" : "DTF_FUN(PY,  False, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_PZ" : "DTF_FUN(PZ, False , strings(['J/psi(1S)',  'K*(892)0']))"
        }   
#B2JpsiPhiLine
LoKiVariablesJpsiPhi = LoKi__Hybrid__TupleTool('LoKiVariablesJpsiPhi')
LoKiVariablesJpsiPhi.Variables = { 
        "DTF_MM"  : "DTF_FUN(MM, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_M"  : "DTF_FUN(M, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_P"  : "DTF_FUN(P, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_PT" : "DTF_FUN(PT, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_PE" : "DTF_FUN(E, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_PX" : "DTF_FUN(PX, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_PY" : "DTF_FUN(PY, False, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_PZ" : "DTF_FUN(PZ, False, strings(['J/psi(1S)', 'phi(1020)']))"
        }
#B2KK lifetime unbiased
LoKiVariablesKK = LoKi__Hybrid__TupleTool('LoKiVariablesKK')
LoKiVariablesKK.Variables = {
    "DTF_MM"  : "DTF_FUN(MM, False, strings(['K+',  'K-']))"
    ,"DTF_M"  : "DTF_FUN(M, False, strings(['K+',  'K-']))"
    ,"DTF_P"  : "DTF_FUN(P, False, strings(['K+',  'K-']))"
    ,"DTF_PT" : "DTF_FUN(PT, False, strings(['K+',  'K-']))"
    ,"DTF_PE" : "DTF_FUN(E, False, strings(['K+',  'K-']))"
    ,"DTF_PX" : "DTF_FUN(PX, False, strings(['K+',  'K-']))"
    ,"DTF_PY" : "DTF_FUN(PY, False, strings(['K+',  'K-']))"
    ,"DTF_PZ" : "DTF_FUN(PZ, False, strings(['K+',  'K-']))"
   }
#B2SS
LoKiVariablesSS = LoKi__Hybrid__TupleTool('LoKiVariablesSS')
LoKiVariablesSS.Variables = {
    "DTF_MM"  : "DTF_FUN(MM, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_M"  : "DTF_FUN(M, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_P"  : "DTF_FUN(P, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PT" : "DTF_FUN(PT, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PE" : "DTF_FUN(E, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PX" : "DTF_FUN(PX, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PY" : "DTF_FUN(PY, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PZ" : "DTF_FUN(PZ, False, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
   }



##########################################################################################
########  DecayTreeFitter extra kinematic variables needed With PV constraint  ###########
##########################################################################################
#Bs2MuMuLine and B2HHLine and Bs2MuMu lifetime unbiased
LoKiVariablesMuMuVFit = LoKi__Hybrid__TupleTool('LoKiVariablesMuMuVFit')
LoKiVariablesMuMuVFit.Variables = {
    "DTF_VFit_MM"  : "DTF_FUN(MM, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_M"  : "DTF_FUN(M, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_P"  : "DTF_FUN(P, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_PT" : "DTF_FUN(PT, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_PE" : "DTF_FUN(E, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_PX" : "DTF_FUN(PX, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_PY" : "DTF_FUN(PY, True, strings(['mu+',  'mu-']))"
    ,"DTF_VFit_PZ" : "DTF_FUN(PZ, True, strings(['mu+',  'mu-']))"
   }
#B2JpsiKLine
LoKiVariablesJpsiKVFit = LoKi__Hybrid__TupleTool('LoKiVariablesJpsiKVFit')
LoKiVariablesJpsiKVFit.Variables = {
        "DTF_VFit_MM"  : "DTF_FUN(MM, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_M"  : "DTF_FUN(M, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_P"  : "DTF_FUN(P, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_PT" : "DTF_FUN(PT, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_PE" : "DTF_FUN(E, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_PX" : "DTF_FUN(PX, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_PY" : "DTF_FUN(PY, True, strings(['J/psi(1S)',  'K+']))"
        ,"DTF_VFit_PZ" : "DTF_FUN(PZ, True, strings(['J/psi(1S)',  'K+']))"
        }
#B2JpsiKstLine 
LoKiVariablesJpsiKstVFit = LoKi__Hybrid__TupleTool('LoKiVariablesJpsiKstVFit')
LoKiVariablesJpsiKstVFit.Variables = { 
        "DTF_VFit_MM"  : "DTF_FUN(MM, True, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_M"  : "DTF_FUN(M,  True, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_P"  : "DTF_FUN(P, True , strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_PT" : "DTF_FUN(PT, True , strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_PE" : "DTF_FUN(E,  True, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_PX" : "DTF_FUN(PX, True , strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_PY" : "DTF_FUN(PY,  True, strings(['J/psi(1S)',  'K*(892)0']))"
        ,"DTF_VFit_PZ" : "DTF_FUN(PZ, True , strings(['J/psi(1S)',  'K*(892)0']))"
        }
#B2JpsiPhiLine
LoKiVariablesJpsiPhiVFit = LoKi__Hybrid__TupleTool('LoKiVariablesJpsiPhiVFit')
LoKiVariablesJpsiPhiVFit.Variables = { 
        "DTF_VFit_MM"  : "DTF_FUN(MM, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_M"  : "DTF_FUN(M, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_P"  : "DTF_FUN(P, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_PT" : "DTF_FUN(PT, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_PE" : "DTF_FUN(E, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_PX" : "DTF_FUN(PX, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_PY" : "DTF_FUN(PY, True, strings(['J/psi(1S)', 'phi(1020)']))"
        ,"DTF_VFit_PZ" : "DTF_FUN(PZ, True, strings(['J/psi(1S)', 'phi(1020)']))"
        }
#B2KK lifetime unbiased
LoKiVariablesKKVFit = LoKi__Hybrid__TupleTool('LoKiVariablesKKVFit')
LoKiVariablesKKVFit.Variables = {
    "DTF_MM"  : "DTF_FUN(MM, True, strings(['K+',  'K-']))"
    ,"DTF_M"  : "DTF_FUN(M, True, strings(['K+',  'K-']))"
    ,"DTF_P"  : "DTF_FUN(P, True, strings(['K+',  'K-']))"
    ,"DTF_PT" : "DTF_FUN(PT, True, strings(['K+',  'K-']))"
    ,"DTF_PE" : "DTF_FUN(E, True, strings(['K+',  'K-']))"
    ,"DTF_PX" : "DTF_FUN(PX, True, strings(['K+',  'K-']))"
    ,"DTF_PY" : "DTF_FUN(PY, True, strings(['K+',  'K-']))"
    ,"DTF_PZ" : "DTF_FUN(PZ, True, strings(['K+',  'K-']))"
   }
#B2SS
LoKiVariablesSSVFit = LoKi__Hybrid__TupleTool('LoKiVariablesSSVFit')
LoKiVariablesSSVFit.Variables = {
    "DTF_MM"  : "DTF_FUN(MM, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_M"  : "DTF_FUN(M, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_P"  : "DTF_FUN(P, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PT" : "DTF_FUN(PT, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PE" : "DTF_FUN(E, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PX" : "DTF_FUN(PX, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PY" : "DTF_FUN(PY, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
    ,"DTF_PZ" : "DTF_FUN(PZ, True, strings(['mu-',  'mu-'],['mu+',  'mu+'] ))"
   }

############################
###     Make    ntuples  ###
############################

#For HH
###############################################################
B2HHTuple = myNTUPLE.clone("B2HHTuple")
B2HHTuple.Inputs = [B2HHInput]
B2HHTuple.Decay = 'B_s0 -> ^mu+ ^mu-'

B2HHTuple.Branches = { "B" :  "B_s0 -> mu+ mu-"}

B2HHTuple.addTool(TupleToolDecay, name="B")

B2HHTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
B2HHTuple.B.addTool(LoKiVariablesMuMu)

B2HHTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMuVFit"]
B2HHTuple.B.addTool(LoKiVariablesMuMuVFit)

B2HHTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
B2HHTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
B2HHTuple.B.Fit.daughtersToConstrain = ["mu+", "mu-"]
B2HHTuple.B.Fit.UpdateDaughters = True 
B2HHTuple.B.Fit.constrainToOriginVertex = False
B2HHTuple.B.Fit.Verbose = True

#include vertex constraint
B2HHTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
B2HHTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
B2HHTuple.B.VFit.daughtersToConstrain = ["mu+", "mu-"]
B2HHTuple.B.VFit.UpdateDaughters = True 
B2HHTuple.B.VFit.constrainToOriginVertex = True
B2HHTuple.B.VFit.Verbose = True
        
if not isolations_from_RelatedInfos:
    from Configurables import TupleToolBsMuMuZViso
    B2HHTuple.B.ToolList+=["TupleToolBsMuMuZViso"]
    B2HHTuple.B.addTool(TupleToolBsMuMuZViso)
    B2HHTuple.B.TupleToolBsMuMuZViso.Weights_BDTG_ZViso = ZVisoWeightsFile
    
    B2HHTuple.B.ToolList += ["TupleToolJetsForB/B2HH"]
    B2HHTuple.B.addTool(tupletooljets["B2HH"])

#Including isolation variables for MDST
##########################################################
if isolations_from_RelatedInfos:
    LoKi_iso_HH =  LoKi__Hybrid__TupleTool( 'LoKi_iso_HH')
    
    LoKi_iso_HH.Variables = {
        #isolation variables used in 3fb analysis
        "BSMUMUCDFISO" : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+B2HHRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"    
        ,'iso_giampi' :"RELINFO('"+B2HHRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+B2HHRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2HHRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2HHRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"  
        ,'iso_giampi_2' :"RELINFO('"+B2HHRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+B2HHRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2HHRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2HHRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        #ZV isolation
        ,'ZVISO'   : "RELINFO('"+B2HHRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"
        
        #BDT Track isolations
        ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2HHRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        #jet varaibles
        ,'JETNOMU1PX' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PX', -0.)"
        ,'JETNOMU1PY' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PY', -0.)"
        ,'JETNOMU1PZ' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PZ', -0.)"
        ,'JETNOMU1PT' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PT', -0.)"
        ,'JETNOMU1JETWIDTH' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1JETWIDTH', -0.)"
        ,'JETNOMU1NNTAG' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1NNTAG', -0.)"
        ,'JETNOMU1MNF' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1MNF', -0.)"
        ,'JETNOMU2PX' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PX', -0.)"
        ,'JETNOMU2PY' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PY', -0.)"
        ,'JETNOMU2PZ' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PZ', -0.)"
        ,'JETNOMU2PT' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PT', -0.)"
        ,'JETMU1PX' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1PX', -0.)"
        ,'JETMU1PY' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1PY', -0.)"
        ,'JETMU1PZ' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1PZ', -0.)"
        ,'JETNOMU2JETWIDTH': "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2JETWIDTH' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2NNTAG' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2NNTAG', -0.)"
        ,'JETNOMU2MNF' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2MNF', -0.)"
        ,'JETNOMU3PX' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PX', -0.)"
        ,'JETNOMU3PY' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PY', -0.)"
        ,'JETNOMU3PZ' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PZ', -0.)"
        ,'JETNOMU3PT' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PT', -0.)"
        ,'JETNOMU3JETWIDTH' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3JETWIDTH', -0.)"
        ,'JETNOMU3NNTAG' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3NNTAG', -0.)"
        ,'JETNOMU3MNF' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3MNF', -0.)"
        ,'JETMU1PT' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1PT', -0.)"
        ,'JETMU1JETWIDTH' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1JETWIDTH', -0.)"
        ,'JETMU1NNTAG' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1NNTAG', -0.)"
        ,'JETMU1MNF' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU1MNF', -0.)"
        ,'JETMU2PX' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2PX', -0.)"
        ,'JETMU2PY' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2PY', -0.)"
        ,'JETMU2PZ' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2PZ', -0.)"
        ,'JETMU2PT' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2PT', -0.)"
        ,'JETMU2JETWIDTH' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2JETWIDTH', -0.)"
        ,'JETMU2NNTAG' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2NNTAG', -0.)"
        ,'JETMU2MNF' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETMU2MNF', -0.)"
        ,'JETBPX' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBPX', -0.)"
        ,'JETBPY' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBPY', -0.)"
        ,'JETBPZ' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBPZ', -0.)"
        ,'JETBPT' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBPT', -0.)"
        ,'JETBJETWIDTH' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBJETWIDTH', -0.)"
        ,'JETBNNTAG' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBNNTAG', -0.)"
        ,'JETBMNF' : "RELINFO('"+B2HHRelatedInfoInput+"RelatedInfoJets', 'JETBMNF', -0.)"
        
        }
    
    B2HHTuple.B.addTool(LoKi_iso_HH)
    B2HHTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_iso_HH"]

# For MuMu
##############################################################

B2MuMuTuple = myNTUPLE.clone("B2MuMuTuple")
B2MuMuTuple.Inputs = [B2MuMuInput]
B2MuMuTuple.Decay = 'B_s0 -> ^mu+ ^mu-'

B2MuMuTuple.Branches = { "B" :  "B_s0 -> mu+ mu-"}

B2MuMuTuple.addTool(TupleToolDecay, name="B")

B2MuMuTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
B2MuMuTuple.B.addTool(LoKiVariablesMuMu)

B2MuMuTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMuVFit"]
B2MuMuTuple.B.addTool(LoKiVariablesMuMuVFit)

B2MuMuTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
B2MuMuTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
B2MuMuTuple.B.Fit.daughtersToConstrain = ["mu+", "mu-"]
B2MuMuTuple.B.Fit.UpdateDaughters = True 
B2MuMuTuple.B.Fit.constrainToOriginVertex = False
B2MuMuTuple.B.Fit.Verbose = True

#include vertex fit
B2MuMuTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
B2MuMuTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
B2MuMuTuple.B.VFit.daughtersToConstrain = ["mu+", "mu-"]
B2MuMuTuple.B.VFit.UpdateDaughters = True 
B2MuMuTuple.B.VFit.constrainToOriginVertex  = True
B2MuMuTuple.B.VFit.Verbose = True

if not isolations_from_RelatedInfos:
    from Configurables import TupleToolBsMuMuZViso
    B2MuMuTuple.B.ToolList+=["TupleToolBsMuMuZViso"]
    B2MuMuTuple.B.addTool(TupleToolBsMuMuZViso)
    B2MuMuTuple.B.TupleToolBsMuMuZViso.Weights_BDTG_ZViso = ZVisoWeightsFile
    
    B2MuMuTuple.B.ToolList += ["TupleToolJetsForB/BsMuMu"]
    B2MuMuTuple.B.addTool(tupletooljets["BsMuMu"])

#Including isolation variables for MDST
##########################################################

if isolations_from_RelatedInfos: 
    LoKi_iso_MuMu =  LoKi__Hybrid__TupleTool( 'LoKi_iso_MuMu')
    LoKi_iso_MuMu.Variables = {

        #3fb isolation variables
        "BSMUMUCDFISO" : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+B2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
        
        ,'iso_giampi' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        ,'iso_giampi_2' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        #ZV isolatio
        ,'ZVISO'   : "RELINFO('"+B2MuMuRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"
        
        #BDT Track isolations
        ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        #jet variables
        ,'JETNOMU1PX' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PX', -0.)"
        ,'JETNOMU1PY' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PY', -0.)"
        ,'JETNOMU1PZ' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PZ', -0.)"
        ,'JETNOMU1PT' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PT', -0.)"
        ,'JETNOMU1JETWIDTH' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1JETWIDTH', -0.)"
        ,'JETNOMU1NNTAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1NNTAG', -0.)"
        ,'JETNOMU1MNF' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1MNF', -0.)"
        ,'JETNOMU2PX' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PX', -0.)"
        ,'JETNOMU2PY' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PY', -0.)"
        ,'JETNOMU2PZ' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PZ', -0.)"
        ,'JETNOMU2PT' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PT', -0.)"
        ,'JETMU1PX' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PX', -0.)"
        ,'JETMU1PY' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PY', -0.)"
        ,'JETMU1PZ' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PZ', -0.)"
        ,'JETNOMU2JETWIDTH': "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2JETWIDTH' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2NNTAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2NNTAG', -0.)"
        ,'JETNOMU2MNF' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2MNF', -0.)"
        ,'JETNOMU3PX' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PX', -0.)"
        ,'JETNOMU3PY' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PY', -0.)"
        ,'JETNOMU3PZ' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PZ', -0.)"
        ,'JETNOMU3PT' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PT', -0.)"
        ,'JETNOMU3JETWIDTH' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3JETWIDTH', -0.)"
        ,'JETNOMU3NNTAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3NNTAG', -0.)"
        ,'JETNOMU3MNF' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3MNF', -0.)"
        ,'JETMU1PT' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PT', -0.)"
        ,'JETMU1JETWIDTH' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1JETWIDTH', -0.)"
        ,'JETMU1NNTAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1NNTAG', -0.)"
        ,'JETMU1MNF' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1MNF', -0.)"
        ,'JETMU2PX' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PX', -0.)"
        ,'JETMU2PY' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PY', -0.)"
        ,'JETMU2PZ' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PZ', -0.)"
        ,'JETMU2PT' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PT', -0.)"
        ,'JETMU2JETWIDTH' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2JETWIDTH', -0.)"
        ,'JETMU2NNTAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2NNTAG', -0.)"
        ,'JETMU2MNF' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2MNF', -0.)"
        ,'JETBPX' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPX', -0.)"
        ,'JETBPY' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPY', -0.)"
        ,'JETBPZ' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPZ', -0.)"
        ,'JETBPT' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPT', -0.)"
        ,'JETBJETWIDTH' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBJETWIDTH', -0.)"
        ,'JETBNNTAG' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBNNTAG', -0.)"
        ,'JETBMNF' : "RELINFO('"+B2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBMNF', -0.)"

        }
    
    B2MuMuTuple.B.addTool(LoKi_iso_MuMu)
    B2MuMuTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_iso_MuMu"]

#For JpsiK
################################################################
    
B2JpsiKTuple = myNTUPLE.clone("B2JpsiKTuple")
B2JpsiKTuple.Inputs = [B2JpsiKInput]
B2JpsiKTuple.Decay = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^K+ ]CC"

B2JpsiKTuple.Branches = {
    "B" :  "^([B+ -> (J/psi(1S) -> mu+ mu-) K+ ]CC)"
    ,"J_psi_1S" :  "([B+ -> ^(J/psi(1S) -> mu+ mu-) K+ ]CC)"
    }

B2JpsiKTuple.addTool(TupleToolDecay, name="B")
B2JpsiKTuple.addTool(TupleToolDecay, name="J_psi_1S")
B2JpsiKTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesJpsiK"]
B2JpsiKTuple.B.addTool(LoKiVariablesJpsiK)

B2JpsiKTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesJpsiKVFit"]
B2JpsiKTuple.B.addTool(LoKiVariablesJpsiKVFit)

B2JpsiKTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
B2JpsiKTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
B2JpsiKTuple.B.Fit.daughtersToConstrain = ["J/psi(1S)", "K+"] 
B2JpsiKTuple.B.Fit.UpdateDaughters = True 
B2JpsiKTuple.B.Fit.constrainToOriginVertex = False
B2JpsiKTuple.B.Fit.Verbose = True

#include vertex fit
B2JpsiKTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
B2JpsiKTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
B2JpsiKTuple.B.VFit.daughtersToConstrain = ["J/psi(1S)", "K+"]
B2JpsiKTuple.B.VFit.UpdateDaughters = True 
B2JpsiKTuple.B.VFit.constrainToOriginVertex  = True
B2JpsiKTuple.B.VFit.Verbose = True

if not isolations_from_RelatedInfos:
    from Configurables import TupleToolBsMuMuZViso
    B2JpsiKTuple.J_psi_1S.ToolList+=["TupleToolBsMuMuZViso"]
    B2JpsiKTuple.J_psi_1S.addTool(TupleToolBsMuMuZViso)
    B2JpsiKTuple.J_psi_1S.TupleToolBsMuMuZViso.Weights_BDTG_ZViso = ZVisoWeightsFile
    
#Including isolation variables for MDST
##########################################################
if isolations_from_RelatedInfos:

    LoKi_iso_K =  LoKi__Hybrid__TupleTool( 'LoKi_iso_K')
    LoKi_iso_K.Variables = {

    #3fb isolation variables
        "BSMUMUCDFISO" : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+B2JpsiKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
        
        ,'iso_giampi' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        ,'iso_giampi_2' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        #ZV isolations
        ,'ZVISO'   : "RELINFO('"+B2JpsiKRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"

        #BDT track isolations
        ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2JpsiKRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        }

    B2JpsiKTuple.J_psi_1S.addTool(LoKi_iso_K)
    B2JpsiKTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_iso_K"]

################################################################
#For Jpsi Phi

B2JpsiPhiTuple = myNTUPLE.clone("B2JpsiPhiTuple")
B2JpsiPhiTuple.Inputs = [ B2JpsiPhiInput ]
B2JpsiPhiTuple.Decay ="[B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)]CC"
    
B2JpsiPhiTuple.Branches = {
    "B" :  "^([B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)]CC)"
    ,"J_psi_1S" :  "([B_s0 -> ^(J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ K-)]CC)"
    }

B2JpsiPhiTuple.addTool(TupleToolDecay, name="B")
B2JpsiPhiTuple.addTool(TupleToolDecay, name="J_psi_1S")

B2JpsiPhiTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesJpsiPhi"]
B2JpsiPhiTuple.B.addTool(LoKiVariablesJpsiPhi)

B2JpsiPhiTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesJpsiPhiVFit"]
B2JpsiPhiTuple.B.addTool(LoKiVariablesJpsiPhiVFit)

B2JpsiPhiTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
B2JpsiPhiTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
B2JpsiPhiTuple.B.Fit.daughtersToConstrain = ["J/psi(1S)", "phi(1020)"]
B2JpsiPhiTuple.B.Fit.UpdateDaughters = True 
B2JpsiPhiTuple.B.Fit.constrainToOriginVertex = False
B2JpsiPhiTuple.B.Fit.Verbose = True

#include vertex fit
B2JpsiPhiTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
B2JpsiPhiTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
B2JpsiPhiTuple.B.VFit.daughtersToConstrain = ["J/psi(1S)", "phi(1020)"]
B2JpsiPhiTuple.B.VFit.UpdateDaughters = True 
B2JpsiPhiTuple.B.VFit.constrainToOriginVertex  = True
B2JpsiPhiTuple.B.VFit.Verbose = True

if not isolations_from_RelatedInfos:  
    from Configurables import TupleToolBsMuMuZViso
    B2JpsiPhiTuple.J_psi_1S.ToolList+=["TupleToolBsMuMuZViso"]
    B2JpsiPhiTuple.J_psi_1S.addTool(TupleToolBsMuMuZViso)
    B2JpsiPhiTuple.J_psi_1S.TupleToolBsMuMuZViso.Weights_BDTG_ZViso = ZVisoWeightsFile

#Including isolation variables for MDST
##########################################################
if  isolations_from_RelatedInfos:
    
    LoKi_iso_Phi =  LoKi__Hybrid__TupleTool( 'LoKi_iso_Phi')
    LoKi_iso_Phi.Variables = {

        #3fb isolation variables
        "BSMUMUCDFISO" : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
        
        ,'iso_giampi' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        ,'iso_giampi_2' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"

        #ZV isolation
        ,'ZVISO'   : "RELINFO('"+B2JpsiPhiRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"

        #BDT track isolations
        ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        
        ,'1_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        
        ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        
        ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        
        ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2JpsiPhiRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        }

    B2JpsiPhiTuple.J_psi_1S.addTool(LoKi_iso_Phi)
    B2JpsiPhiTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_iso_Phi"]

############################################
#For  JpsiKst
############################################
    
B2JpsiKstTuple = myNTUPLE.clone("B2JpsiKstTuple")
B2JpsiKstTuple.Decay = "[B0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(K*(892)0 -> ^K+ ^pi-) ]CC"
B2JpsiKstTuple.Inputs = [B2JpsiKstInput]

B2JpsiKstTuple.Branches = {
    "B" :  "^([B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]CC)"
    ,"J_psi_1S" :  "([B0 -> ^(J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]CC)"
    }

B2JpsiKstTuple.addTool(TupleToolDecay, name="B") 
B2JpsiKstTuple.addTool(TupleToolDecay, name="J_psi_1S")

B2JpsiKstTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesJpsiKst"]
B2JpsiKstTuple.B.addTool(LoKiVariablesJpsiKst)

B2JpsiKstTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesJpsiKstVFit"]
B2JpsiKstTuple.B.addTool(LoKiVariablesJpsiKstVFit)

B2JpsiKstTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
B2JpsiKstTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
B2JpsiKstTuple.B.Fit.daughtersToConstrain =  ["J/psi(1S)", "K*(892)0"]
B2JpsiKstTuple.B.Fit.UpdateDaughters = True 
B2JpsiKstTuple.B.Fit.constrainToOriginVertex = False
B2JpsiKstTuple.B.Fit.Verbose = True

#include vertex fit
B2JpsiKstTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
B2JpsiKstTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
B2JpsiKstTuple.B.VFit.daughtersToConstrain =  ["J/psi(1S)", "K*(892)0"]
B2JpsiKstTuple.B.VFit.UpdateDaughters = True 
B2JpsiKstTuple.B.VFit.constrainToOriginVertex  = True
B2JpsiKstTuple.B.VFit.Verbose = True

if not isolations_from_RelatedInfos:
    from Configurables import TupleToolBsMuMuZViso
    B2JpsiKstTuple.J_psi_1S.ToolList+=["TupleToolBsMuMuZViso"]
    B2JpsiKstTuple.J_psi_1S.addTool(TupleToolBsMuMuZViso)
    B2JpsiKstTuple.J_psi_1S.TupleToolBsMuMuZViso.Weights_BDTG_ZViso = ZVisoWeightsFile

#Including isolation variables for MDST
##########################################################
if isolations_from_RelatedInfos:
    LoKi_iso_Kst =  LoKi__Hybrid__TupleTool( 'LoKi_iso_Kst')
    LoKi_iso_Kst.Variables = {
        
        #3fb isolation variables
        "BSMUMUCDFISO" : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+B2JpsiKstRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
        
        ,'iso_giampi' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        ,'iso_giampi_2' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
        #ZV isolation
        ,'ZVISO'   : "RELINFO('"+B2JpsiKstRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"

        #BDT Track isolations
        ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
    
        ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2JpsiKstRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
    
        }

    B2JpsiKstTuple.J_psi_1S.addTool(LoKi_iso_Kst)
    B2JpsiKstTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_iso_Kst"]

#For SameSign
###############################################################
B2SSTuple = myNTUPLE.clone("B2SSTuple")
B2SSTuple.Inputs = [B2SSInput]
B2SSTuple.Decay = "[B_s0 -> ^mu+ mu+]CC"

B2SSTuple.Branches = { "B" :  "[B_s0 -> mu+ mu+]CC"}
    
B2SSTuple.addTool(TupleToolDecay, name="B")

B2SSTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesSS"]
B2SSTuple.B.addTool(LoKiVariablesSS)

B2SSTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesSSVFit"]
B2SSTuple.B.addTool(LoKiVariablesSSVFit)

B2SSTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
B2SSTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
B2SSTuple.B.Fit.daughtersToConstrain = ["mu+", "mu+"]
B2SSTuple.B.Fit.UpdateDaughters = True 
B2SSTuple.B.Fit.constrainToOriginVertex = False
B2SSTuple.B.Fit.Verbose = True

#include vertex constraint
B2SSTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
B2SSTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
B2SSTuple.B.VFit.daughtersToConstrain = ["mu+", "mu+"]
B2SSTuple.B.VFit.UpdateDaughters = True 
B2SSTuple.B.VFit.constrainToOriginVertex = True
B2SSTuple.B.VFit.Verbose = True

if not isolations_from_RelatedInfos:
    from Configurables import TupleToolBsMuMuZViso
    B2SSTuple.B.ToolList+=["TupleToolBsMuMuZViso"]
    B2SSTuple.B.addTool(TupleToolBsMuMuZViso)
    B2SSTuple.B.TupleToolBsMuMuZViso.Weights_BDTG_ZViso = ZVisoWeightsFile
    
    B2SSTuple.B.ToolList += ["TupleToolJetsForB/B2SS"]
    B2SSTuple.B.addTool(tupletooljets["B2SS"])

#Including isolation variables for MDST
##########################################################
if isolations_from_RelatedInfos:
    LoKi_iso_SS =  LoKi__Hybrid__TupleTool( 'LoKi_iso_SS')
    
    LoKi_iso_SS.Variables = {
        #3fb isolation variables
        "BSMUMUCDFISO" : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+B2SSRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
        
        ,'iso_giampi' :"RELINFO('"+B2SSRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+B2SSRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2SSRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2SSRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        ,'iso_giampi_2' :"RELINFO('"+B2SSRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+B2SSRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+B2SSRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+B2SSRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
        #ZV isolations
        ,'ZVISO'   : "RELINFO('"+B2SSRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"
        
        #BDT Track isolations
        ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
        ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+B2SSRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
        
        #jet varaibles
        ,'JETNOMU1PX' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PX', -0.)"
        ,'JETNOMU1PY' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PY', -0.)"
        ,'JETNOMU1PZ' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PZ', -0.)"
        ,'JETNOMU1PT' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PT', -0.)"
        ,'JETNOMU1JETWIDTH' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1JETWIDTH', -0.)"
        ,'JETNOMU1NNTAG' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1NNTAG', -0.)"
        ,'JETNOMU1MNF' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1MNF', -0.)"
        ,'JETNOMU2PX' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PX', -0.)"
        ,'JETNOMU2PY' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PY', -0.)"
        ,'JETNOMU2PZ' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PZ', -0.)"
        ,'JETNOMU2PT' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PT', -0.)"
        ,'JETMU1PX' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1PX', -0.)"
        ,'JETMU1PY' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1PY', -0.)"
        ,'JETMU1PZ' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1PZ', -0.)"
        ,'JETNOMU2JETWIDTH': "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2JETWIDTH' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2NNTAG' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2NNTAG', -0.)"
        ,'JETNOMU2MNF' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2MNF', -0.)"
        ,'JETNOMU3PX' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PX', -0.)"
        ,'JETNOMU3PY' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PY', -0.)"
        ,'JETNOMU3PZ' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PZ', -0.)"
        ,'JETNOMU3PT' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PT', -0.)"
        ,'JETNOMU3JETWIDTH' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3JETWIDTH', -0.)"
        ,'JETNOMU3NNTAG' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3NNTAG', -0.)"
        ,'JETNOMU3MNF' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3MNF', -0.)"
        ,'JETMU1PT' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1PT', -0.)"
        ,'JETMU1JETWIDTH' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1JETWIDTH', -0.)"
        ,'JETMU1NNTAG' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1NNTAG', -0.)"
        ,'JETMU1MNF' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU1MNF', -0.)"
        ,'JETMU2PX' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2PX', -0.)"
        ,'JETMU2PY' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2PY', -0.)"
        ,'JETMU2PZ' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2PZ', -0.)"
        ,'JETMU2PT' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2PT', -0.)"
        ,'JETMU2JETWIDTH' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2JETWIDTH', -0.)"
        ,'JETMU2NNTAG' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2NNTAG', -0.)"
        ,'JETMU2MNF' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETMU2MNF', -0.)"
        ,'JETBPX' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBPX', -0.)"
        ,'JETBPY' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBPY', -0.)"
        ,'JETBPZ' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBPZ', -0.)"
        ,'JETBPT' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBPT', -0.)"
        ,'JETBJETWIDTH' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBJETWIDTH', -0.)"
        ,'JETBNNTAG' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBNNTAG', -0.)"
        ,'JETBMNF' : "RELINFO('"+B2SSRelatedInfoInput+"RelatedInfoJets', 'JETBMNF', -0.)"
        
        }
    
    B2SSTuple.B.addTool(LoKi_iso_SS)
    B2SSTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_iso_SS"]

#####################################################################################
#Include lifetime unbiased lines - no MC for these stripping lines
#####################################################################################

#Bs2MuMU lifetime unbiased line
#######################################################
Bs2MuMuLTUBTuple = myNTUPLE.clone("Bs2MuMuLTUBTuple")
Bs2MuMuLTUBTuple.Inputs = [ LTUBBs2MuMuInput ]
Bs2MuMuLTUBTuple.Decay = "B_s0 -> ^mu+ ^mu-"
Bs2MuMuLTUBTuple.Branches = { "B" :  "B_s0 -> mu+ mu-"}
Bs2MuMuLTUBTuple.addTool(TupleToolDecay, name="B")
#Bs2MuMuLTUBTuple.P2PVInputLocations = ["Phys/Bs2MuMusLTUBLine/Particle2VertexRelations"]
    
Bs2MuMuLTUBTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
Bs2MuMuLTUBTuple.B.addTool(LoKiVariablesMuMu)

Bs2MuMuLTUBTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMuVFit"]
Bs2MuMuLTUBTuple.B.addTool(LoKiVariablesMuMuVFit)

Bs2MuMuLTUBTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
Bs2MuMuLTUBTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
Bs2MuMuLTUBTuple.B.Fit.daughtersToConstrain = ["mu+", "mu-"]
Bs2MuMuLTUBTuple.B.Fit.UpdateDaughters = True 
Bs2MuMuLTUBTuple.B.Fit.constrainToOriginVertex = False
Bs2MuMuLTUBTuple.B.Fit.Verbose = True
    
#include vertex constraint
Bs2MuMuLTUBTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
Bs2MuMuLTUBTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
Bs2MuMuLTUBTuple.B.VFit.daughtersToConstrain = ["mu+", "mu-"]
Bs2MuMuLTUBTuple.B.VFit.UpdateDaughters = True 
Bs2MuMuLTUBTuple.B.VFit.constrainToOriginVertex = True
Bs2MuMuLTUBTuple.B.VFit.Verbose = True
    
if isolations_from_RelatedInfos:
    LoKi_Iso_MuMu =  LoKi__Hybrid__TupleTool('LoKi_Iso_MuMu')
    
    LoKi_Iso_MuMu.Variables = {
        
             "BSMUMUCDFISO" : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
            ,'BSMUMUOTHERBMAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
            ,'BSMUMUOTHERBANGLE' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
            ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
            ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
            ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
            ,'BSMUMUPARTID' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
            ,'BSMUMUTOPID' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
            
            ,'JETNOMU1PX' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PX', -0.)"
            ,'JETNOMU1PY' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PY', -0.)"
            ,'JETNOMU1PZ' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PZ', -0.)"
            ,'JETNOMU1PT' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PT', -0.)"
            ,'JETNOMU1JETWIDTH' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1JETWIDTH', -0.)"
            ,'JETNOMU1NNTAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1NNTAG', -0.)"
            ,'JETNOMU1MNF' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1MNF', -0.)"
            ,'JETNOMU2PX' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PX', -0.)"
            ,'JETNOMU2PY' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PY', -0.)"
            ,'JETNOMU2PZ' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PZ', -0.)"
            ,'JETNOMU2PT' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PT', -0.)"
            ,'JETMU1PX' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PX', -0.)"
            ,'JETMU1PY' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PY', -0.)"
            ,'JETMU1PZ' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PZ', -0.)"
            ,'JETNOMU2JETWIDTH': "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
            ,'JETNOMU2JETWIDTH' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
            ,'JETNOMU2NNTAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2NNTAG', -0.)"
            ,'JETNOMU2MNF' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2MNF', -0.)"
            ,'JETNOMU3PX' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PX', -0.)"
            ,'JETNOMU3PY' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PY', -0.)"
            ,'JETNOMU3PZ' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PZ', -0.)"
            ,'JETNOMU3PT' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PT', -0.)"
            ,'JETNOMU3JETWIDTH' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3JETWIDTH', -0.)"
            ,'JETNOMU3NNTAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3NNTAG', -0.)"
            ,'JETNOMU3MNF' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3MNF', -0.)"
            ,'JETMU1PT' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1PT', -0.)"
            ,'JETMU1JETWIDTH' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1JETWIDTH', -0.)"
            ,'JETMU1NNTAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1NNTAG', -0.)"
            ,'JETMU1MNF' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU1MNF', -0.)"
            ,'JETMU2PX' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PX', -0.)"
            ,'JETMU2PY' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PY', -0.)"
            ,'JETMU2PZ' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PZ', -0.)"
            ,'JETMU2PT' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2PT', -0.)"
            ,'JETMU2JETWIDTH' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2JETWIDTH', -0.)"
            ,'JETMU2NNTAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2NNTAG', -0.)"
            ,'JETMU2MNF' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETMU2MNF', -0.)"
            ,'JETBPX' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPX', -0.)"
            ,'JETBPY' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPY', -0.)"
            ,'JETBPZ' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPZ', -0.)"
            ,'JETBPT' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBPT', -0.)"
            ,'JETBJETWIDTH' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBJETWIDTH', -0.)"
            ,'JETBNNTAG' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBNNTAG', -0.)"
            ,'JETBMNF' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelatedInfoJets', 'JETBMNF', -0.)"
            
            ,'ZVISO'   : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"
            
            ,'iso_giampi' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
            ,'iso_new2' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
            ,'BSMUMUTRACKID' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
            ,'BSMUMUTRACKTOPID' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
            
            ,'iso_giampi_2' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
            ,'iso_new2_2' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
            ,'BSMUMUTRACKID' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
            ,'BSMUMUTRACKTOPID' :"RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
            
            ,'1_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
            ,'1_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
            ,'1_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
            ,'1_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
            ,'1_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
            ,'1_TRKISOBDTSECONDVALUE0' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
            ,'1_TRKISOBDTSECONDVALUE1' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
            ,'1_TRKISOBDTSECONDVALUE2' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
            ,'1_TRKISOBDTSECONDVALUE3' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
            ,'1_TRKISOBDTSECONDVALUE4' : "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
            ,'1_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
            ,'1_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
            ,'1_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
            ,'1_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
            ,'1_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon1TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
            
            ,'2_TRKISOBDTFIRSTVALUE0' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTFIRSTVALUE', -0.)"
            ,'2_TRKISOBDTFIRSTVALUE1' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTFIRSTVALUE', -0.)"
            ,'2_TRKISOBDTFIRSTVALUE2' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTFIRSTVALUE', -0.)"
            ,'2_TRKISOBDTFIRSTVALUE3' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTFIRSTVALUE', -0.)"
            ,'2_TRKISOBDTFIRSTVALUE4' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTFIRSTVALUE', -0.)"
            ,'2_TRKISOBDTSECONDVALUE0' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTSECONDVALUE', -0.)"
            ,'2_TRKISOBDTSECONDVALUE1' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTSECONDVALUE', -0.)"
            ,'2_TRKISOBDTSECONDVALUE2' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTSECONDVALUE', -0.)"
            ,'2_TRKISOBDTSECONDVALUE3' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTSECONDVALUE', -0.)"
            ,'2_TRKISOBDTSECONDVALUE4' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTSECONDVALUE', -0.)"
            ,'2_TRKISOBDTTHIRDVALUE0' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_0','TRKISOBDTTHIRDVALUE', -0.)"
            ,'2_TRKISOBDTTHIRDVALUE1' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_1','TRKISOBDTTHIRDVALUE', -0.)"
            ,'2_TRKISOBDTTHIRDVALUE2' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_2','TRKISOBDTTHIRDVALUE', -0.)"
            ,'2_TRKISOBDTTHIRDVALUE3' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_3','TRKISOBDTTHIRDVALUE', -0.)"
            ,'2_TRKISOBDTTHIRDVALUE4' :  "RELINFO('"+LTUBBs2MuMuRelatedInfoInput+"Muon2TrackIsoBDTInfo_4','TRKISOBDTTHIRDVALUE', -0.)"
            
            }
        
    Bs2MuMuLTUBTuple.B.addTool(LoKi_Iso_MuMu)
    Bs2MuMuLTUBTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_Iso_MuMu"]

#Bs2KK lifetime unbiased line
#######################################################
Bs2KKLTUBTuple = myNTUPLE.clone("Bs2KKLTUBTuple")
Bs2KKLTUBTuple.Inputs = [ LTUBB2KKInput ]
Bs2KKLTUBTuple.Decay = "B_s0 -> ^K+ ^K-"
Bs2KKLTUBTuple.Branches = { "B" :  "B_s0 -> K+ K-"}
Bs2KKLTUBTuple.addTool(TupleToolDecay, name="B")
    
Bs2KKLTUBTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesKK"]
Bs2KKLTUBTuple.B.addTool(LoKiVariablesKK)

Bs2KKLTUBTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesKKVFit"]
Bs2KKLTUBTuple.B.addTool(LoKiVariablesKKVFit)

Bs2KKLTUBTuple.B.ToolList+=["TupleToolDecayTreeFitter/Fit"]
Bs2KKLTUBTuple.B.addTool(TupleToolDecayTreeFitter("Fit"))
Bs2KKLTUBTuple.B.Fit.daughtersToConstrain = ["K+", "K-"]
Bs2KKLTUBTuple.B.Fit.UpdateDaughters = True 
Bs2KKLTUBTuple.B.Fit.constrainToOriginVertex = False
Bs2KKLTUBTuple.B.Fit.Verbose = True

#include vertex constraint
Bs2KKLTUBTuple.B.ToolList+=["TupleToolDecayTreeFitter/VFit"]
Bs2KKLTUBTuple.B.addTool(TupleToolDecayTreeFitter("VFit"))
Bs2KKLTUBTuple.B.VFit.daughtersToConstrain = ["K+", "K-"]
Bs2KKLTUBTuple.B.VFit.UpdateDaughters = True 
Bs2KKLTUBTuple.B.VFit.constrainToOriginVertex = True
Bs2KKLTUBTuple.B.VFit.Verbose = True

if isolations_from_RelatedInfos:

    LoKi_Iso_KK =  LoKi__Hybrid__TupleTool('LoKi_Iso_KK')
    
    LoKi_Iso_KK.Variables = {
        
        "BSMUMUCDFISO" : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUCDFISO', -0.)"
        ,'BSMUMUOTHERBMAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBMAG', -0.)"
        ,'BSMUMUOTHERBANGLE' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBANGLE', -0.)"
        ,'BSMUMUOTHERBBOOSTMAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTMAG', -0.)"
        ,'BSMUMUOTHERBBOOSTANGLE' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBBOOSTANGLE', -0.)"
        ,'BSMUMUOTHERBTRACKS' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUOTHERBTRACKS', -0.)"
        ,'BSMUMUPARTID' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUPARTID', -0.)"
        ,'BSMUMUTOPID' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"BSMUMUVARIABLES', 'BSMUMUTOPID', -0.)"
        
        ,'JETNOMU1PX' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PX', -0.)"
        ,'JETNOMU1PY' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PY', -0.)"
        ,'JETNOMU1PZ' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PZ', -0.)"
        ,'JETNOMU1PT' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1PT', -0.)"
        ,'JETNOMU1JETWIDTH' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1JETWIDTH', -0.)"
        ,'JETNOMU1NNTAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1NNTAG', -0.)"
        ,'JETNOMU1MNF' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU1MNF', -0.)"
        ,'JETNOMU2PX' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PX', -0.)"
        ,'JETNOMU2PY' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PY', -0.)"
        ,'JETNOMU2PZ' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PZ', -0.)"
        ,'JETNOMU2PT' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2PT', -0.)"
        ,'JETMU1PX' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1PX', -0.)"
        ,'JETMU1PY' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1PY', -0.)"
        ,'JETMU1PZ' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1PZ', -0.)"
        ,'JETNOMU2JETWIDTH': "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2JETWIDTH' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2JETWIDTH', -0.)"
        ,'JETNOMU2NNTAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2NNTAG', -0.)"
        ,'JETNOMU2MNF' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU2MNF', -0.)"
        ,'JETNOMU3PX' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PX', -0.)"
        ,'JETNOMU3PY' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PY', -0.)"
        ,'JETNOMU3PZ' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PZ', -0.)"
        ,'JETNOMU3PT' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3PT', -0.)"
        ,'JETNOMU3JETWIDTH' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3JETWIDTH', -0.)"
        ,'JETNOMU3NNTAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3NNTAG', -0.)"
        ,'JETNOMU3MNF' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETNOMU3MNF', -0.)"
        ,'JETMU1PT' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1PT', -0.)"
        ,'JETMU1JETWIDTH' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1JETWIDTH', -0.)"
        ,'JETMU1NNTAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1NNTAG', -0.)"
        ,'JETMU1MNF' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU1MNF', -0.)"
        ,'JETMU2PX' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2PX', -0.)"
        ,'JETMU2PY' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2PY', -0.)"
        ,'JETMU2PZ' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2PZ', -0.)"
        ,'JETMU2PT' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2PT', -0.)"
        ,'JETMU2JETWIDTH' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2JETWIDTH', -0.)"
        ,'JETMU2NNTAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2NNTAG', -0.)"
        ,'JETMU2MNF' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETMU2MNF', -0.)"
        ,'JETBPX' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBPX', -0.)"
        ,'JETBPY' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBPY', -0.)"
        ,'JETBPZ' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBPZ', -0.)"
        ,'JETBPT' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBPT', -0.)"
        ,'JETBJETWIDTH' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBJETWIDTH', -0.)"
        ,'JETBNNTAG' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBNNTAG', -0.)"
        ,'JETBMNF' : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelatedInfoJets', 'JETBMNF', -0.)"
        
        ,'ZVISO'   : "RELINFO('"+LTUBB2KKRelatedInfoInput+"RelInfoZVisoBDT', 'ZVISO', -0.)"
        
        ,'iso_giampi' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon1iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        ,'iso_giampi_2' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISO', -0.)"
        ,'iso_new2_2' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKPLUSISOTWO', -0.)"
        ,'BSMUMUTRACKID' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKID', -0.)"
        ,'BSMUMUTRACKTOPID' :"RELINFO('"+LTUBB2KKRelatedInfoInput+"Muon2iso' , 'BSMUMUTRACKTOPID', -0.)"
        
        }
    
    Bs2KKLTUBTuple.B.addTool(LoKi_Iso_KK)
    Bs2KKLTUBTuple.B.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_Iso_KK"]
    
#########################################################################################3
#Include ntuples for MC
if doMatchedNtuples:
    MB2JpsiKTuple = myNTUPLE.clone("MB2JpsiKTuple")
    MB2JpsiKTuple.Inputs = [ SelMB2JpsiK.outputLocation() ] 
    MB2JpsiKTuple.Decay = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^K+ ]CC"

    MBs2MuMuTuple = myNTUPLE.clone("MBs2MuMuTuple")
    MBs2MuMuTuple.Inputs = [ SelMBs2MuMu.outputLocation() ] 
    MBs2MuMuTuple.Decay =  "B_s0 -> ^mu+ ^mu-"

    MBd2MuMuTuple = myNTUPLE.clone("MBd2MuMuTuple")
    MBd2MuMuTuple.Inputs = [ SelMBd2MuMu.outputLocation() ] 
    MBd2MuMuTuple.Decay =  "B0 -> ^mu+ ^mu-"

    MBd2KPiTuple = myNTUPLE.clone("MBd2KPiTuple")
    MBd2KPiTuple.Inputs = [ SelMBdKPi.outputLocation() ] 
    MBd2KPiTuple.Decay =  "B_s0 -> ^mu+ ^mu-"

    MBs2JpsiPhiTuple = myNTUPLE.clone("MBs2JpsiPhiTuple")
    MBs2JpsiPhiTuple.Inputs = [ SelMBs2Jpsiphi.outputLocation() ] 
    MBs2JpsiPhiTuple.Decay ="[B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-)]CC"

if doMCDecayTreeTuple:
    
    from Configurables import  MCDecayTreeTuple, MCTupleToolPID, MCTupleToolKinematic, MCTupleToolHierarchy, MCTupleToolReconstructed
    mymctuple = MCDecayTreeTuple('mymctuple')
    mymctuple.ToolList += [ "MCTupleToolKinematic"
                            ,"MCTupleToolHierarchy"
                            ,"MCTupleToolPID"
                           , "MCTupleToolReconstructed"  ]
    mymctuple.addTool(MCTupleToolKinematic)
    mymctuple.MCTupleToolKinematic.Verbose=True
    mymctuple.addTool(MCTupleToolReconstructed)
    mymctuple.MCTupleToolReconstructed.Verbose=True

    MCB2KPiTuple = mymctuple.clone( 'MCB2KPiTuple' )
    MCB2KPiTuple.Decay =   '[B0 => ^K+ ^pi-]CC' 
   
    MCBs2MuMuTuple = mymctuple.clone( 'MCBs2MuMuTuple' )
    MCBs2MuMuTuple.Decay =    '[B_s0 => ^mu+ ^mu-]CC' 
  
    MCBd2MuMuTuple = mymctuple.clone( 'MCBd2MuMuTuple' )
    MCBd2MuMuTuple.Decay =    '[B0 => ^mu+ ^mu-]CC' 
 
    MCB2JpsiKTuple = mymctuple.clone( 'MCB2JpsiKTuple' )
    MCB2JpsiKTuple.Decay =    "[B+ => ^(J/psi(1S) => ^mu+ ^mu-) ^K+ ]CC"
  
    MCB2JpsiPhiTuple = mymctuple.clone( 'MCB2JpsiPhiTuple' )
    MCB2JpsiPhiTuple.Decay =   "[B_s0 => ^(J/psi(1S) => ^mu+ ^mu-) ^(phi(1020) => ^K+ ^K-)]CC" 
   
#############################
#Format the the Jpsi Lines
#############################
if include_resonaces:
    myNTUPLE_Jpsi = DecayTreeTuple('myNTUPLE_Jpsi')

    myNTUPLE_Jpsi.ToolList +=  [  "TupleToolGeometry"
                                  ,"TupleToolKinematic"
                                  , "TupleToolEventInfo" 
                                  , "TupleToolPid"                    
                                  , "TupleToolRecoStats"
                                  , "TupleToolTrigger"
                                  , "TupleToolTISTOS"
                                  , "TupleToolTrackInfo"
                                  , "TupleToolMuonPid"
                                  ,"LoKi::Hybrid::TupleTool/LoKiTool"
                                  ,"LoKi::Hybrid::TupleTool/LoKi_All"
                                  ]

    myNTUPLE.addTool(TupleToolTISTOS)
    myNTUPLE.TupleToolTISTOS.VerboseL0 = True
    myNTUPLE.TupleToolTISTOS.VerboseHlt1 = True
    myNTUPLE.TupleToolTISTOS.VerboseHlt2 = True
    myNTUPLE.TupleToolTISTOS.FillL0 = True
    myNTUPLE.TupleToolTISTOS.FillHlt1 = True
    myNTUPLE.TupleToolTISTOS.FillHlt2 = True
    myNTUPLE.TupleToolTISTOS.OutputLevel = INFO
    myNTUPLE.TupleToolTISTOS.TriggerList = triggerListF
    
    #DiMuonJpsi2MuMuTOS
    ############################################################################################################
    
    Jpsi2MuMuTOSTuple = myNTUPLE_Jpsi.clone("Jpsi2MuMuTOSTuple")
    Jpsi2MuMuTOSTuple.Inputs = [ DiMuonJpsi2MuMuTOSInput ]
    Jpsi2MuMuTOSTuple.Decay = "J/psi(1S) -> ^mu+ ^mu-"
    
    Jpsi2MuMuTOSTuple.Branches = {"J_psi_1S" : "J/psi(1S) -> mu+ mu-"}
    
    Jpsi2MuMuTOSTuple.addTool(TupleToolDecay, name="J_psi_1S")
    Jpsi2MuMuTOSTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
    Jpsi2MuMuTOSTuple.J_psi_1S.addTool(LoKiVariablesMuMu)
 
    Jpsi2MuMuTOSTuple.J_psi_1S.ToolList+=["TupleToolDecayTreeFitter/Fit"]
    Jpsi2MuMuTOSTuple.J_psi_1S.addTool(TupleToolDecayTreeFitter("Fit"))
    Jpsi2MuMuTOSTuple.J_psi_1S.Fit.daughtersToConstrain = ["mu+", "mu-"]
    Jpsi2MuMuTOSTuple.J_psi_1S.Fit.UpdateDaughters = True 
    Jpsi2MuMuTOSTuple.J_psi_1S.Fit.constrainToOriginVertex = False
    Jpsi2MuMuTOSTuple.J_psi_1S.Fit.Verbose = True

    #DiMuonPsi2MuMuTOSTuple
    ############################################################################################################
        
    Psi2MuMuTOSTuple = myNTUPLE_Jpsi.clone("Psi2MuMuTOSTuple")
    Psi2MuMuTOSTuple.Inputs = [ DiMuonPsi2MuMuTOSInput ]
    Psi2MuMuTOSTuple.Decay ="J/psi(1S) -> ^mu+ ^mu-"
    
    Psi2MuMuTOSTuple.Branches = {"J_psi_1S" : "J/psi(1S) -> mu+ mu-" }
    
    Psi2MuMuTOSTuple.addTool(TupleToolDecay, name="J_psi_1S")
    Psi2MuMuTOSTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
    Psi2MuMuTOSTuple.J_psi_1S.addTool(LoKiVariablesMuMu)
   
    Psi2MuMuTOSTuple.J_psi_1S.ToolList+=["TupleToolDecayTreeFitter/Fit"]
    Psi2MuMuTOSTuple.J_psi_1S.addTool(TupleToolDecayTreeFitter("Fit"))
    Psi2MuMuTOSTuple.J_psi_1S.Fit.daughtersToConstrain = ["mu+", "mu-"]
    Psi2MuMuTOSTuple.J_psi_1S.Fit.UpdateDaughters = True 
    Psi2MuMuTOSTuple.J_psi_1S.Fit.constrainToOriginVertex = False
    Psi2MuMuTOSTuple.J_psi_1S.Fit.Verbose = True
    
    #DiMuonHighMassInput 
    ############################################################################################################
    DiMuonHighMassTuple = myNTUPLE_Jpsi.clone("DiMuonHighMassTuple")
    DiMuonHighMassTuple.Inputs = [ DiMuonHighMassInput ]
    DiMuonHighMassTuple.Decay ="J/psi(1S) -> ^mu+ ^mu-"
    
    DiMuonHighMassTuple.Branches = {"J_psi_1S" : "J/psi(1S) -> mu+ mu-"}
    
    DiMuonHighMassTuple.addTool(TupleToolDecay, name="J_psi_1S")
    DiMuonHighMassTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
    DiMuonHighMassTuple.J_psi_1S.addTool(LoKiVariablesMuMu)
 
    DiMuonHighMassTuple.J_psi_1S.ToolList+=["TupleToolDecayTreeFitter/Fit"]
    DiMuonHighMassTuple.J_psi_1S.addTool(TupleToolDecayTreeFitter("Fit"))
    DiMuonHighMassTuple.J_psi_1S.Fit.daughtersToConstrain = ["mu+", "mu-"]
    DiMuonHighMassTuple.J_psi_1S.Fit.UpdateDaughters = True 
    DiMuonHighMassTuple.J_psi_1S.Fit.constrainToOriginVertex = False
    DiMuonHighMassTuple.J_psi_1S.Fit.Verbose = True
    
    #Leptonic line
    ############################################################################################################
    DiMuonIncTuple = myNTUPLE_Jpsi.clone("DiMuonIncTuple")
    DiMuonIncTuple.Inputs = [ DiMuonIncInput ]
    DiMuonIncTuple.Decay ="J/psi(1S) -> ^mu+ ^mu-"
    
    DiMuonIncTuple.Branches = {"J_psi_1S" : "J/psi(1S) -> mu+ mu-"}       
    
    DiMuonIncTuple.addTool(TupleToolDecay, name="J_psi_1S")
    DiMuonIncTuple.J_psi_1S.ToolList+=["LoKi::Hybrid::TupleTool/LoKiVariablesMuMu"]
    DiMuonIncTuple.J_psi_1S.addTool(LoKiVariablesMuMu)
    
    DiMuonIncTuple.J_psi_1S.ToolList+=["TupleToolDecayTreeFitter/Fit"]
    DiMuonIncTuple.J_psi_1S.addTool(TupleToolDecayTreeFitter("Fit"))
    DiMuonIncTuple.J_psi_1S.Fit.daughtersToConstrain = ["mu+", "mu-"]
    DiMuonIncTuple.J_psi_1S.Fit.UpdateDaughters = True 
    DiMuonIncTuple.J_psi_1S.Fit.constrainToOriginVertex = False
    DiMuonIncTuple.J_psi_1S.Fit.Verbose = True

############################
###         BDTS cut     ###
############################
if cutBDTS:
    from Configurables import BsMuMuBDTSelectionTool as BDTS
    bdts = BDTS('B2HHFilterSel.BsmmBDT') 
    bdts.OutputLevel = 3
    bdts.Cut = 0.03  # cut on BDTS
    bdts.WeightsFile   = weightFile
    bdts.FlatHistoFile = flatteningFile
    BDTSFilter = FilterDesktop('BDTSFilter', Code = 'ALL')
    BDTSFilter.Code = " (MM > 4000.*MeV) & FILTER('BsMuMuBDTSelectionTool/BsmmBDT') "  

    B2HHSel = AutomaticData(Location   = B2HHInput)
    B2HHFilterSel = Selection(name = 'B2HHFilterSel', Algorithm = BDTSFilter,   RequiredSelections = [B2HHSel] )
    B2HHSeq =SelectionSequence("B2HHSeq", TopSelection  = B2HHFilterSel )
    B2HHTuple.Inputs = [B2HHSeq.outputLocation()]
    print B2HHSeq.outputLocation()

    bdts2 = BDTS('B2MuMuFilterSel.BsmmBDT2')  ## xyzSel.BsmmBDT2 where xyzSel has to be the same name as the Selection object that is going to run it
    bdts2.OutputLevel = 3
    bdts2.Cut = -1 # 0.03
    bdts2.WeightsFile   = weightFile
    bdts2.FlatHistoFile = flatteningFile
    BDTSFilter2 = FilterDesktop('BDTSFilter2', Code = 'ALL')
    BDTSFilter2.Code = " (MM > 4000.*MeV) & FILTER('BsMuMuBDTSelectionTool/BsmmBDT2') "
    
    B2MuMuSel = AutomaticData(Location = B2MuMuInput)
    B2MuMuFilterSel = Selection(name = 'B2MuMuFilterSel', Algorithm = BDTSFilter2,   RequiredSelections = [B2MuMuSel] )
    B2MuMuSeq =SelectionSequence("B2MuMuSeq", TopSelection  = B2MuMuFilterSel )
    B2MuMuTuple.Inputs = [ B2MuMuSeq.outputLocation() ]
    print B2MuMuSeq.outputLocation()
        
    BDTSSequencer = GaudiSequencer("BDTSSequencer")
    BDTSSequencer.Members += [ B2HHSeq.sequence() , B2MuMuSeq.sequence(), B2JpsiKSeq.sequence() ]

    BDTSSequencer.ShortCircuit = False
    mySequencer.Members +=[ BDTSSequencer ]

############################
###   DV configuration ####
############################
if makeGP:
    from STTools import STOfflineConf
    STOfflineConf.DefaultConf().configureTools()
    from Configurables import TrackModifier, TrackAddNNGhostId

from Configurables import DaVinci
DaVinci().EvtMax = -1 
DaVinci().SkipEvents = 0

#Set collision type
if(Collision==16):
    DaVinci().DataType = "2016"
if(Collision==15):
    DaVinci().DataType = "2015"
if(Collision==12):
    DaVinci().DataType = "2012"
if(Collision==11):
    DaVinci().DataType = "2011"

DaVinci().Simulation   = True
DaVinci().Lumi   = False

DaVinci().UserAlgorithms += [mySequencer]

if makeGP:
    DaVinci().UserAlgorithms = +[ #mySequencer,
        TrackModifier("prepare_tracks_1",Location=B2HHInput ),
        TrackModifier("prepare_tracks_2",Location=B2MuMuInput), 
        TrackAddNNGhostId()
        ]
    if stripping in ['24','26']:
        DaVinci().UserAlgorithms = +[ #mySequencer,
            TrackModifier("prepare_tracks_3",Location=B2JpsiKInput),
            TrackAddNNGhostId()
            ]
    if stripping == '20':
        DaVinci().UserAlgorithms = +[ #mySequencer,
            TrackModifier("prepare_tracks_3",Location=B2JpsiKInput),
            TrackModifier("prepare_tracks_4",Location=B2JpsiKstInput),
            TrackModifier("prepare_tracks_5",Location=B2JpsiPhiInput), 
            TrackAddNNGhostId()
            ]

#Add ntuples to MoniSequence
DaVinci().MoniSequence += [ B2HHTuple, B2MuMuTuple, B2JpsiKTuple, B2JpsiPhiTuple]
#DaVinci().MoniSequence += [ B2HHTuple, B2MuMuTuple, B2JpsiKTuple, B2JpsiKstTuple, B2JpsiPhiTuple, Bs2MuMuLTUBTuple, Bs2KKLTUBTuple, B2SSTuple]
#DaVinci().MoniSequence += [ B2HHTuple, B2MuMuTuple]

if include_resonaces:
    DaVinci().MoniSequence += [DiMuonHighMassTuple, Jpsi2MuMuTOSTuple, Psi2MuMuTOSTuple]

#If it is MC
if doMatchedNtuples:
    DaVinci().MoniSequence += [ MBd2KPiTuple , MBs2MuMuTuple , MBd2MuMuTuple,   MB2JpsiKTuple,  MBs2JpsiPhiTuple]

if doMCDecayTreeTuple:
    DaVinci().MoniSequence += [ MCB2KPiTuple , MCBs2MuMuTuple , MCBd2MuMuTuple,  MCB2JpsiKTuple,  MCB2JpsiPhiTuple]
 
DaVinci().TupleFile = rootfilename
DaVinci().InputType = "DST"

if not Usegrid:
  from GaudiConf import IOHelper
  DaVinci().Input = [
#      "DATAFILE='PFN:/afs/cern.ch/user/r/rvazquez/work/public/00049671_00000259_1.dimuon.dst, TYP='POOL_ROOTTREE' OPT='READ'" ## 2015 data
#      "DATAFILE='PFN:/afs/cern.ch/user/r/rvazquez/work/public/00052191_00006089_1.dimuon.dst, TYP='POOL_ROOTTREE' OPT='READ'" ## 2016 data
  "DATAFILE='PFN:/afs/cern.ch/work/m/mmulder/UraniaDev_v7r0/Phys/Bs2MuMu/options/00059558_00000011_1.dimuon.dst', TYPE = 'POOL_ROOTTREE', OPT = 'READ'"
]
########################################################################
# HLT
#DaVinci().ReplaceL0BanksWithEmulated = True ## enable if you want to rerun L0
#DaVinci().Hlt2Requires = 'L0+Hlt1'          ## change if you want Hlt2 irrespective of Hlt1
#DaVinci().HltType = 'Hlt1'             ## pick one of 'Hlt1', 'Hlt2', or 'Hlt1+Hlt2'
########################################################################
MessageSvc().Format = "% F%60W%S%7W%R%T %0W%M"
MessageSvc().OutputLevel = INFO
#MessageSvc().OutputLevel = VERBOSE
########################################################################
