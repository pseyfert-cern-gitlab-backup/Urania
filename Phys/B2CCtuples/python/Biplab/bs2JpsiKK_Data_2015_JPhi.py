from Gaudi.Configuration import *
from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import addBranches

from Configurables import CombineParticles, TrackScaleState
from Configurables import TupleToolTrigger, BackgroundCategory
from Configurables import LoKi__Hybrid__TupleTool, TupleToolP2VV, TupleToolTISTOS, TupleToolMCTruth
from Configurables import TupleToolTrackPosition
from Configurables import TupleToolTagging

from Configurables import DaVinci, TupleToolDecay, TupleToolRecoStats, TupleToolDira
from Configurables import TupleToolDecayTreeFitter
from Configurables import FilterDesktop
from Configurables import SubstitutePID # only for J/psi(1S)
from Configurables import TupleToolGeometry, TupleToolTrackInfo

from PhysSelPython.Wrappers import Selection, SelectionSequence, DataOnDemand

from Configurables import GaudiSequencer, PrintMCTree

##################################################################
# Initialize some settings independent of LHCb tools
inputType      = "DST"
isMC           = False
year           = "2015"
evtmax         = -1
magpos         = "MD"  # don't need this for Data
##################################################################


if isMC:
        loc      = "/Event/AllStreams/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
else:
        loc      = "/Event/Dimuon/Phys/BetaSBs2JpsiPhiDetachedLine/Particles"
###################################################################
 
bs_filter = FilterDesktop("bs_filter", Code = "(in_range(5150,mBs,5550)) & (dtf_prob > 10E-8)")
bs_filter.Preambulo = [
                          "dtf_prob = DTF_PROB(True, 'J/psi(1S)')",
                          "mBs      = DTF_FUN(M, True, 'J/psi(1S)')"
                      ]

sel_B_init = DataOnDemand(Location = loc)
sel_B = Selection("sel_B", Algorithm = bs_filter, RequiredSelections = [sel_B_init])
sel_B.ReFitPVs = True

seq_B = SelectionSequence("SeqB2ccbarKK",TopSelection =sel_B)

#######################################################################

l0_lines =   [ 'L0MuonDecision'
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
             , 'Hlt2DiMuonDetachedJPsiDecision']

trigs = l0_lines + hlt1_lines + hlt2_lines

#########################################################################

l0_lines_liming   = ['L0PhysicsDecision', 'L0PhotonDecision', 'L0ElectronDecision', 'L0MuonHighDecision', 'L0HadronDecision']

hlt1_lines_liming = ['Hlt1MBNoBiasDecision', 'Hlt1SingleMuonNoIPDecision', 'Hlt1DiProtonDecision', 'Hlt1MBMicroBiasVeloDecision', 'Hlt1MBMicroBiasTStationDecision', 'Hlt1TrackPhotonDecision', 'Hlt1DiProtonLowMultDecision']

hlt2_lines_liming = ['Hlt2DiMuonDecision',  'Hlt2DiMuonJPsiDecision', 'Hlt2MuonFromHLT1Decision', 'Hlt2TopoMu4BodyBBDTDecision', 'Hlt2Topo3BodySimpleDecision', 'Hlt2SingleElectronTFLowPtDecision', 'Hlt2Topo4BodySimpleDecision', 'Hlt2DiMuonNoPVDecision', 'Hlt2IncPhiSidebandsDecision', 'Hlt2DiMuonZDecision','Hlt2Topo4BodyBBDTDecision', 'Hlt2TopoMu2BodyBBDTDecision', 'Hlt2DiMuonBDecision', 'Hlt2DiElectronBDecision', 'Hlt2DiMuonJPsiHighPTDecision', 'Hlt2DiMuonLowMassDecision', 'Hlt2SingleElectronTFHighPtDecision', 'Hlt2B2HHLTUnbiasedDecision', 'Hlt2DiElectronHighMassDecision', 'Hlt2Topo3BodyBBDTDecision', 'Hlt2IncPhiDecision', 'Hlt2DiMuonDY2Decision', 'Hlt2DiMuonDecision', 'Hlt2Topo2BodySimpleDecision', 'Hlt2TopoE4BodyBBDTDecision', 'Hlt2DiMuonDY4Decision', 'Hlt2TriMuonTauDecision', 'Hlt2TriMuonDetachedDecision', 'Hlt2TopoE2BodyBBDTDecision', 'Hlt2DiMuonDY3Decision', 'Hlt2TopoE3BodyBBDTDecision', 'Hlt2DiMuonJPsiDecision', 'Hlt2DiMuonDY1Decision', 'Hlt2DiMuonPsi2SDecision', 'Hlt2Topo2BodyBBDTDecision','Hlt2TopoMu3BodyBBDTDecision']

trigs_liming     = l0_lines_liming + hlt1_lines_liming + hlt2_lines_liming

###################################################
# Use the CondDB to get the right database tags for data
from Configurables import CondDB
if not isMC: CondDB(LatestGlobalTagByDataType = year )
###################################################


dv = DaVinci(
     InputType     = inputType,
     DataType      =  year  ,
     EvtMax        =  evtmax  , # -1 for all files
     TupleFile     = 'DTT.root',
     PrintFreq     = 10000,
     Simulation    = isMC,
     Lumi = False if isMC else True
)


###################################

dddb_tag = { 'isMC': {'2011': {"MD" : "dddb-20130929", "MU" : "dddb-20130929"},
                      '2012': {"MD" : "dddb-20130929-1", "MU" : "dddb-20130929-1"} }
           }

cond_tag = { 'isMC': {'2011': {"MD" : "sim-20130522-vc-md100", "MU" : "sim-20130522-vc-mu100"},
                      '2012': {"MD" : "sim-20130522-1-vc-md100", "MU" : "sim-20130522-1-vc-mu100"} }
           }


if isMC:
   dv.DDDBtag   = dddb_tag['isMC'][year][magpos]
   dv.CondDBtag = cond_tag['isMC'][year][magpos]


####################################


from DecayTreeTuple.Configuration import *
BTuple =  DecayTreeTuple("BTuple")#,OutputLevel = DEBUG)
BTuple.Decay = "(B_s0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(phi(1020) -> ^K+ ^K-))"
BTuple.ReFitPVs = True
BTuple.addBranches({
                    "bMom"     :  "B_s0 -> (J/psi(1S) -> mu+ mu-)  (phi(1020) -> K+ K-)",
                    "Mup"      :  "B_s0 -> (J/psi(1S) -> ^mu+ mu-) (phi(1020) -> K+ K-)",
                    "Mum"      :  "B_s0 -> (J/psi(1S) -> mu+ ^mu-) (phi(1020) -> K+ K-)",
                    "Kp"       :  "B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> ^K+ K-)",
                    "Km"       :  "B_s0 -> (J/psi(1S) -> mu+ mu-) (phi(1020) -> K+ ^K-)"
                   })


BTuple.Inputs = [sel_B.outputLocation() ] 
BTuple.ToolList += [
    		     "TupleToolGeometry"
                    ,"TupleToolTrackInfo"
                    ,"TupleToolTrigger"
                    ,"TupleToolPid"
                    ,"TupleToolKinematic"
                    ,"TupleToolPropertime"
                    ,"TupleToolPrimaries"
                    ,"TupleToolEventInfo"
                    ,"TupleToolTagging"
                    ,"TupleToolRecoStats"
                    ,"TupleToolTrackIsolation"
                    ,"TupleToolTrackPosition"
#                    ,"TupleToolDira"
                     ,"TupleToolVtxIsoln"
#                    ,"TupleToolANNPID" Run2 default tuning is in ProbNN already
                    ]

if isMC: BTuple.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"]

BTuple.addTool(TupleToolTrackPosition,name = 'TupleToolTrackPosition')
BTuple.TupleToolTrackPosition.Z = 7500

BTuple.addTool(TupleToolRecoStats,name = 'TupleToolRecoStats')
BTuple.TupleToolRecoStats.Verbose = True

LoKiVariables = LoKi__Hybrid__TupleTool('LoKiVariables')
LoKiVariables.Variables = {
        "ETA"        : "ETA"
         }
BTuple.addTool(LoKiVariables , name = 'LoKiVariables' )
BTuple.ToolList   += [ 'LoKi::Hybrid::TupleTool/LoKiVariables']

# From JpsiPhi tupling 
LoKi_SpecificToB           = LoKi__Hybrid__TupleTool('LoKi_SpecificToB')
LoKi_SpecificToB.Variables =  { 
         "JpsiPhiMass"          : "WM('J/psi(1S)','phi(1020)')",
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
         "LOKI_DTF_VCHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True )"}
BTuple.addTool(TupleToolDecay, name = "bMom")
BTuple.bMom.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_SpecificToB"]
BTuple.bMom.addTool(LoKi_SpecificToB)

TupleToolP2VV_Bs = TupleToolP2VV('TupleToolP2VV_Bs')
TupleToolP2VV_Bs.Calculator  = 'Bs2JpsiPhiAngleCalculator'
TupleToolP2VV_Bs.OutputLevel = 6
BTuple.bMom.addTool(TupleToolP2VV_Bs)
BTuple.bMom.ToolList       += ["TupleToolP2VV/TupleToolP2VV_Bs"]

#TupleToolTagging
BTuple.addTool(TupleToolTagging, name = "TupleToolTagging")
BTuple.TupleToolTagging.Verbose = True

# TupleToolGeometry/TrackInfo
BTuple.addTool(TupleToolGeometry,name = 'TupleToolGeometry')
BTuple.TupleToolGeometry.Verbose = True
BTuple.TupleToolGeometry.RefitPVs = True
BTuple.addTool(TupleToolTrackInfo,name = 'TupleToolTrackInfo')
BTuple.TupleToolTrackInfo.Verbose = True

# Trigger
BTuple.addTool(TupleToolTrigger,name = 'TupleToolTrigger')
BTuple.TupleToolTrigger.Verbose = True
BTuple.TupleToolTrigger.TriggerList = trigs

# TupleToolTISTOS
BTuple.bMom.addTool(TupleToolTISTOS,name = 'TupleToolTISTOS')
BTuple.bMom.TupleToolTISTOS.Verbose = True
BTuple.bMom.TupleToolTISTOS.TriggerList = trigs
BTuple.bMom.ToolList+=["TupleToolTISTOS"]

########################################################################
#
# Signal
#
########################################################################

BTuple.bMom.ToolList +=  ["TupleToolDecayTreeFitter/SigBJpsi"]
sigDTF_Jpsi = TupleToolDecayTreeFitter( "SigBJpsi" ,
                                   Verbose=True ,
                                   daughtersToConstrain = [ "J/psi(1S)" ],
                                   constrainToOriginVertex=True,
                                   UpdateDaughters=True
                                  )
BTuple.bMom.addTool(sigDTF_Jpsi)

BTuple.bMom.ToolList +=  ["TupleToolDecayTreeFitter/SigB_MCJpsi"]
sig_MC_DTF_Jpsi = TupleToolDecayTreeFitter( "SigB_MCJpsi" ,
                                   Verbose=True ,
                                   daughtersToConstrain = [ "J/psi(1S)" , "B_s0"] ,
                                   constrainToOriginVertex=True,
                                   UpdateDaughters=True
                                  )
BTuple.bMom.addTool(sig_MC_DTF_Jpsi)


########################################################################
#
# Backgrounds
#
########################################################################

#
# B -> Kp piMuMu
#

BTuple.bMom.ToolList +=  ["TupleToolDecayTreeFitter/SubB2KpPiJpsi"]
subDTFB2KpPiJpsi = TupleToolDecayTreeFitter( "SubB2KpPiJpsi" ,
                                   Verbose=True ,
                                   Substitutions={
                                           'Beauty -> Meson (phi(1020) -> ^K+ X-)': 'pi+'
                                   },
                                   daughtersToConstrain = [ "J/psi(1S)" ],
                                   constrainToOriginVertex=True
                                  )
BTuple.bMom.addTool(subDTFB2KpPiJpsi)

#
# B -> Km piMuMu
#

BTuple.bMom.ToolList +=  ["TupleToolDecayTreeFitter/SubB2KmPiJpsi"]
subDTFB2KmPiJpsi = TupleToolDecayTreeFitter( "SubB2KmPiJpsi" ,
                                   Verbose=True ,
                                   Substitutions={
                                           'Beauty -> Meson (phi(1020) -> X+ ^K-)': 'pi-'
                                   },
                                   daughtersToConstrain = [ "J/psi(1S)" ],
                                   constrainToOriginVertex=True
                                  )
BTuple.bMom.addTool(subDTFB2KmPiJpsi)

#
# Lb -> pKMuMuKp
#

BTuple.bMom.ToolList +=  ["TupleToolDecayTreeFitter/SubpKMuMuKpJpsi"]
subDTFpKMuMuKpJpsi = TupleToolDecayTreeFitter( "SubpKMuMuKpJpsi" ,
                                   Verbose=True ,
                                   Substitutions={
                                           'Beauty -> Meson (phi(1020) -> ^K+ X-)': 'p+'
                                   },
                                   daughtersToConstrain = [ "J/psi(1S)" ],
                                   constrainToOriginVertex=True
                                  )
BTuple.bMom.addTool(subDTFpKMuMuKpJpsi)

#
# Lb -> pKMuMuKm
#

BTuple.bMom.ToolList +=  ["TupleToolDecayTreeFitter/SubpKMuMuKmJpsi"]
subDTFpKMuMuKmJpsi = TupleToolDecayTreeFitter( "SubpKMuMuKmJpsi" ,
                                   Verbose=True ,
                                   Substitutions={
                                           'Beauty -> Meson (phi(1020) -> X+ ^K-)': 'p~-'
                                   },
                                   daughtersToConstrain = [ "J/psi(1S)" ],
                                   constrainToOriginVertex=True
                                  )
BTuple.bMom.addTool(subDTFpKMuMuKmJpsi)



# Matt Needham(?)'s momentum scale calibration for data
from Configurables import TrackScaleState
if not isMC: 
   scaler            = TrackScaleState('scaler')
   dv.UserAlgorithms =  [ scaler ]

# smear proto particles and their associated tracks for MC

from Configurables import TrackSmearState
if isMC: 
   smear = TrackSmearState("TrackSmearState")
   dv.UserAlgorithms =  [ smear ]

# scaler/smear must be executed before the analysis algorithms
seqB2ccbarKK         = GaudiSequencer('seqB2ccbarKK')
seqB2ccbarKK.Members = [seq_B.sequence(), BTuple]

dv.UserAlgorithms += [ seqB2ccbarKK ]

