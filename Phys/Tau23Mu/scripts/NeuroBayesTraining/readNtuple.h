//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 18 18:23:09 2013 by ROOT version 5.34/07
// from TChain Tau23Mu/
//////////////////////////////////////////////////////////

#ifndef readNtuple_h
#define readNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class readNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RUNNING_EVENT_NUMBER;
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           TCK;
   Int_t           cleaningcut;
   Float_t         NumberPV;
   Int_t           Ncandidates;
   Int_t           NbestTracks;
   Float_t         L0Dec;
   Float_t         Hlt1Dec;
   Float_t         Hlt2Dec;
   Float_t         Hlt2Dec_unprescaled;
   Float_t         Hlt2DecOld;
   Float_t         L0Hlt1DecMu;
   Float_t         Hlt2DecMu;
   Float_t         Hlt2DecSingleMu;
   Float_t         Hlt2DecDhhh;
   Int_t           TriggerTISL0Muon;
   Int_t           TriggerTPSL0Muon;
   Int_t           TriggerTISHlt1TrackMuon;
   Int_t           TriggerTPSHlt1TrackMuon;
   Int_t           TriggerTISHlt2DiMuonDetached;
   Int_t           TriggerTPSHlt2DiMuonDetached;
   Int_t           TriggerTISHlt2TriMuonTau;
   Int_t           TriggerTPSHlt2TriMuonTau;
   Int_t           TriggerTISHlt2CharmSemilepD2HMuMu;
   Int_t           TriggerTPSHlt2CharmSemilepD2HMuMu;
   Int_t           TriggerTOSL0B1gas;
   Int_t           TriggerTOSL0B2gas;
   Int_t           TriggerTOSL0Calo;
   Int_t           TriggerTOSL0DiMuon;
   Int_t           TriggerTOSL0DiMuonlowMult;
   Int_t           TriggerTOSL0Electron;
   Int_t           TriggerTOSL0GlobalPi0;
   Int_t           TriggerTOSL0HCAL;
   Int_t           TriggerTOSL0Hadron;
   Int_t           TriggerTOSL0LocalPi0;
   Int_t           TriggerTOSL0MuonMinbias;
   Int_t           TriggerTOSL0Muon;
   Int_t           TriggerTOSL0MuonLowMult;
   Int_t           TriggerTOSL0PU;
   Int_t           TriggerTOSL0PU20;
   Int_t           TriggerTOSL0Photon;
   Int_t           TriggerTOSL0SPD;
   Int_t           TriggerTOSL0SPD40;
   Int_t           TriggerTOSHlt1DiMuonHighMassDecision;
   Int_t           TriggerTOSHlt1DiMuonLowMassDecision;
   Int_t           TriggerTOSHlt1SingleMuonNoIPDecision;
   Int_t           TriggerTOSHlt1SingleMuonHighPTDecision;
   Int_t           TriggerTOSHlt1TrackAllL0Decision;
   Int_t           TriggerTOSHlt1TrackMuonDecision;
   Int_t           TriggerTOSHlt1TrackPhotonDecision;
   Int_t           TriggerTOSHlt1LumiDecision;
   Int_t           TriggerTOSHlt1LumiMidBeamCrossingDecision;
   Int_t           TriggerTOSHlt1MBNoBiasDecision;
   Int_t           TriggerTOSHlt1L0AnyDecision;
   Int_t           TriggerTOSHlt1L0AnyRateLimitedDecision;
   Int_t           TriggerTOSHlt1L0AnyNoSPDDecision;
   Int_t           TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision;
   Int_t           TriggerTOSHlt1NoPVPassThroughDecision;
   Int_t           TriggerTOSHlt1DiProtonLowMultDecision;
   Int_t           TriggerTOSHlt1BeamGasNoBeamBeam1Decision;
   Int_t           TriggerTOSHlt1BeamGasNoBeamBeam2Decision;
   Int_t           TriggerTOSHlt1BeamGasBeam1Decision;
   Int_t           TriggerTOSHlt1BeamGasBeam2Decision;
   Int_t           TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision;
   Int_t           TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision;
   Int_t           TriggerTOSHlt1BeamGasCrossingForcedRecoDecision;
   Int_t           TriggerTOSHlt1ODINTechnicalDecision;
   Int_t           TriggerTOSHlt1Tell1ErrorDecision;
   Int_t           TriggerTOSHlt1BeamGasCrossingParasiticDecision;
   Int_t           TriggerTOSHlt1ErrorEventDecision;
   Int_t           TriggerTOSHlt1Global;
   Int_t           TriggerTOSHlt1MBMicroBiasVeloDecision;
   Int_t           TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision;
   Int_t           TriggerTOSHlt1MBMicroBiasTStationDecision;
   Int_t           TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision;
   Int_t           TriggerTOSHlt1DiProtonDecision;
   Int_t           TriggerTOSHlt1VeloClosingMicroBiasDecision;
   Int_t           TriggerTOSHlt1SingleElectronNoIPDecision;
   Int_t           TriggerTOSHlt1TrackForwardPassThroughDecision;
   Int_t           TriggerTOSHlt1TrackForwardPassThroughLooseDecision;
   Int_t           TriggerTOSHlt1CharmCalibrationNoBiasDecision;
   Int_t           TriggerTOSHlt1L0HighSumETJetDecision;
   Int_t           TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision;
   Int_t           TriggerTOSHlt1BeamGasHighRhoVerticesDecision;
   Int_t           TriggerTOSHlt1VertexDisplVertexDecision;
   Int_t           TriggerTOSHlt1TrackAllL0TightDecision;
   Int_t           TriggerTOSHlt2SingleElectronTFLowPtDecision;
   Int_t           TriggerTOSHlt2SingleElectronTFHighPtDecision;
   Int_t           TriggerTOSHlt2DiElectronHighMassDecision;
   Int_t           TriggerTOSHlt2DiElectronBDecision;
   Int_t           TriggerTOSHlt2Topo2BodySimpleDecision;
   Int_t           TriggerTOSHlt2Topo3BodySimpleDecision;
   Int_t           TriggerTOSHlt2Topo4BodySimpleDecision;
   Int_t           TriggerTOSHlt2Topo2BodyBBDTDecision;
   Int_t           TriggerTOSHlt2Topo3BodyBBDTDecision;
   Int_t           TriggerTOSHlt2Topo4BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoMu2BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoMu3BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoMu4BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoE2BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoE3BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoE4BodyBBDTDecision;
   Int_t           TriggerTOSHlt2IncPhiDecision;
   Int_t           TriggerTOSHlt2IncPhiSidebandsDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHKsLLDecision;
   Int_t           TriggerTOSHlt2Dst2PiD02PiPiDecision;
   Int_t           TriggerTOSHlt2Dst2PiD02MuMuDecision;
   Int_t           TriggerTOSHlt2Dst2PiD02KMuDecision;
   Int_t           TriggerTOSHlt2Dst2PiD02KPiDecision;
   Int_t           TriggerTOSHlt2PassThroughDecision;
   Int_t           TriggerTOSHlt2TransparentDecision;
   Int_t           TriggerTOSHlt2ForwardDecision;
   Int_t           TriggerTOSHlt2DebugEventDecision;
   Int_t           TriggerTOSHlt2CharmHadD02KKDecision;
   Int_t           TriggerTOSHlt2CharmHadD02KKWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02KPiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02KPiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02PiPiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02PiPiWideMassDecision;
   Int_t           TriggerTOSHlt2ExpressJPsiDecision;
   Int_t           TriggerTOSHlt2ExpressJPsiTagProbeDecision;
   Int_t           TriggerTOSHlt2ExpressLambdaDecision;
   Int_t           TriggerTOSHlt2ExpressKSDecision;
   Int_t           TriggerTOSHlt2ExpressDs2PhiPiDecision;
   Int_t           TriggerTOSHlt2ExpressBeamHaloDecision;
   Int_t           TriggerTOSHlt2ExpressDStar2D0PiDecision;
   Int_t           TriggerTOSHlt2ExpressHLT1PhysicsDecision;
   Int_t           TriggerTOSHlt2Bs2PhiGammaDecision;
   Int_t           TriggerTOSHlt2Bs2PhiGammaWideBMassDecision;
   Int_t           TriggerTOSHlt2Bd2KstGammaDecision;
   Int_t           TriggerTOSHlt2Bd2KstGammaWideKMassDecision;
   Int_t           TriggerTOSHlt2Bd2KstGammaWideBMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0PiDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0KDecision;
   Int_t           TriggerTOSHlt2CharmRareDecayD02MuMuDecision;
   Int_t           TriggerTOSHlt2B2HHDecision;
   Int_t           TriggerTOSHlt2MuonFromHLT1Decision;
   Int_t           TriggerTOSHlt2SingleMuonDecision;
   Int_t           TriggerTOSHlt2SingleMuonHighPTDecision;
   Int_t           TriggerTOSHlt2SingleMuonLowPTDecision;
   Int_t           TriggerTOSHlt2TFBc2JpsiMuXDecision;
   Int_t           TriggerTOSHlt2TFBc2JpsiMuXSignalDecision;
   Int_t           TriggerTOSHlt2DisplVerticesLowMassSingleDecision;
   Int_t           TriggerTOSHlt2DisplVerticesHighMassSingleDecision;
   Int_t           TriggerTOSHlt2DisplVerticesDoubleDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSinglePostScaledDecision;
   Int_t           TriggerTOSHlt2DisplVerticesHighFDSingleDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleDownDecision;
   Int_t           TriggerTOSHlt2B2HHPi0_MergedDecision;
   Int_t           TriggerTOSHlt2CharmHadD2HHHDecision;
   Int_t           TriggerTOSHlt2CharmHadD2HHHWideMassDecision;
   Int_t           TriggerTOSHlt2DiMuonDecision;
   Int_t           TriggerTOSHlt2DiMuonLowMassDecision;
   Int_t           TriggerTOSHlt2DiMuonJPsiDecision;
   Int_t           TriggerTOSHlt2DiMuonJPsiHighPTDecision;
   Int_t           TriggerTOSHlt2DiMuonPsi2SDecision;
   Int_t           TriggerTOSHlt2DiMuonBDecision;
   Int_t           TriggerTOSHlt2DiMuonZDecision;
   Int_t           TriggerTOSHlt2DiMuonDY1Decision;
   Int_t           TriggerTOSHlt2DiMuonDY2Decision;
   Int_t           TriggerTOSHlt2DiMuonDY3Decision;
   Int_t           TriggerTOSHlt2DiMuonDY4Decision;
   Int_t           TriggerTOSHlt2DiMuonDetachedDecision;
   Int_t           TriggerTOSHlt2DiMuonDetachedHeavyDecision;
   Int_t           TriggerTOSHlt2DiMuonDetachedJPsiDecision;
   Int_t           TriggerTOSHlt2DiMuonNoPVDecision;
   Int_t           TriggerTOSHlt2TriMuonDetachedDecision;
   Int_t           TriggerTOSHlt2TriMuonTauDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHWideMassDecision;
   Int_t           TriggerTOSHlt2ErrorEventDecision;
   Int_t           TriggerTOSHlt2Global;
   Int_t           TriggerTOSHlt2B2HHLTUnbiasedDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HH_D02KKDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HH_D02KPiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision;
   Int_t           TriggerTOSHlt2DiProtonDecision;
   Int_t           TriggerTOSHlt2DiProtonTFDecision;
   Int_t           TriggerTOSHlt2DiProtonLowMultDecision;
   Int_t           TriggerTOSHlt2DiProtonLowMultTFDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD2HMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HHMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision;
   Int_t           TriggerTOSHlt2diPhotonDiMuonDecision;
   Int_t           TriggerTOSHlt2LowMultMuonDecision;
   Int_t           TriggerTOSHlt2LowMultHadronDecision;
   Int_t           TriggerTOSHlt2LowMultPhotonDecision;
   Int_t           TriggerTOSHlt2LowMultElectronDecision;
   Int_t           TriggerTOSHlt2SingleTFElectronDecision;
   Int_t           TriggerTOSHlt2SingleTFVHighPtElectronDecision;
   Int_t           TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2KPPiDecision;
   Int_t           TriggerTOSHlt2SingleMuonVHighPTDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision;
   Int_t           TriggerTOSHlt2CharmHadMinBiasLambdaC2KPPiDecision;
   Int_t           TriggerTOSHlt2CharmHadMinBiasD02KPiDecision;
   Int_t           TriggerTOSHlt2CharmHadMinBiasD02KKDecision;
   Int_t           TriggerTOSHlt2CharmHadMinBiasDplus2hhhDecision;
   Int_t           TriggerTOSHlt2CharmHadMinBiasLambdaC2LambdaPiDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleDecision;
   Int_t           TriggerTOSHlt2DisplVerticesDoublePostScaledDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision;
   Int_t           TriggerTOSHlt2RadiativeTopoTrackTOSDecision;
   Int_t           TriggerTOSHlt2RadiativeTopoPhotonL0Decision;
   Int_t           TriggerTOSHlt2DiMuonPsi2SHighPTDecision;
   Int_t           TriggerTOSHlt2DoubleDiMuonDecision;
   Int_t           TriggerTOSHlt2DiMuonAndMuonDecision;
   Int_t           TriggerTOSHlt2DiMuonAndGammaDecision;
   Int_t           TriggerTOSHlt2DiMuonAndD0Decision;
   Int_t           TriggerTOSHlt2DiMuonAndDpDecision;
   Int_t           TriggerTOSHlt2DiMuonAndDsDecision;
   Int_t           TriggerTOSHlt2DiMuonAndLcDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision;
   Int_t           TriggerTOSHlt2TopoRad2BodyBBDTDecision;
   Int_t           TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision;
   Int_t           TriggerTOSHlt2LumiDecision;
   Int_t           TriggerTOSHlt2LowMultHadron_nofilterDecision;
   Int_t           TriggerTOSHlt2LowMultElectron_nofilterDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHKsDDDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0KS0Decision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision;
   Int_t           TriggerTOSHlt2ExpressD02KPiDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2KPKDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2PiPKDecision;
   Int_t           TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision;
   Int_t           TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision;
   Int_t           TriggerTOSHlt2DiPhiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision;
   Int_t           TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision;
   Int_t           TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision;
   Int_t           TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision;
   Int_t           TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision;
   Int_t           TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision;
   Int_t           TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision;
   Int_t           TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision;
   Int_t           TriggerTOSHlt2RadiativeTopoTrackDecision;
   Int_t           TriggerTOSHlt2RadiativeTopoPhotonDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02KKMuMuDecision;
   Int_t           TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_4piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_K3piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision;
   Int_t           TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision;
   Int_t           TriggerTOSHlt2DiMuonDetachedPsi2SDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision;
   Int_t           TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision;
   Int_t           TriggerTOSHlt2LowMultD2KPiDecision;
   Int_t           TriggerTOSHlt2LowMultD2KPiPiDecision;
   Int_t           TriggerTOSHlt2LowMultD2K3PiDecision;
   Int_t           TriggerTOSHlt2LowMultChiC2HHDecision;
   Int_t           TriggerTOSHlt2LowMultChiC2HHHHDecision;
   Int_t           TriggerTOSHlt2LowMultD2KPiWSDecision;
   Int_t           TriggerTOSHlt2LowMultD2KPiPiWSDecision;
   Int_t           TriggerTOSHlt2LowMultD2K3PiWSDecision;
   Int_t           TriggerTOSHlt2LowMultChiC2HHWSDecision;
   Int_t           TriggerTOSHlt2LowMultChiC2HHHHWSDecision;
   Int_t           TriggerTOSHlt2LowMultDDIncDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleLoosePSDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleHighFDDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSingleHighMassDecision;
   Int_t           TriggerTOSHlt2DisplVerticesSinglePSDecision;
   Int_t           TriggerTOSHlt2DisplVerticesDoublePSDecision;
   Int_t           TriggerDecL0B1gas;
   Int_t           TriggerDecL0B2gas;
   Int_t           TriggerDecL0Calo;
   Int_t           TriggerDecL0DiMuon;
   Int_t           TriggerDecL0DiMuonlowMult;
   Int_t           TriggerDecL0Electron;
   Int_t           TriggerDecL0GlobalPi0;
   Int_t           TriggerDecL0HCAL;
   Int_t           TriggerDecL0Hadron;
   Int_t           TriggerDecL0LocalPi0;
   Int_t           TriggerDecL0MuonMinbias;
   Int_t           TriggerDecL0Muon;
   Int_t           TriggerDecL0MuonLowMult;
   Int_t           TriggerDecL0PU;
   Int_t           TriggerDecL0PU20;
   Int_t           TriggerDecL0Photon;
   Int_t           TriggerDecL0SPD;
   Int_t           TriggerDecL0SPD40;
   Int_t           TriggerDecHlt1DiMuonHighMassDecision;
   Int_t           TriggerDecHlt1DiMuonLowMassDecision;
   Int_t           TriggerDecHlt1SingleMuonNoIPDecision;
   Int_t           TriggerDecHlt1SingleMuonHighPTDecision;
   Int_t           TriggerDecHlt1TrackAllL0Decision;
   Int_t           TriggerDecHlt1TrackMuonDecision;
   Int_t           TriggerDecHlt1TrackPhotonDecision;
   Int_t           TriggerDecHlt1LumiDecision;
   Int_t           TriggerDecHlt1LumiMidBeamCrossingDecision;
   Int_t           TriggerDecHlt1MBNoBiasDecision;
   Int_t           TriggerDecHlt1L0AnyDecision;
   Int_t           TriggerDecHlt1L0AnyRateLimitedDecision;
   Int_t           TriggerDecHlt1L0AnyNoSPDDecision;
   Int_t           TriggerDecHlt1L0AnyNoSPDRateLimitedDecision;
   Int_t           TriggerDecHlt1NoPVPassThroughDecision;
   Int_t           TriggerDecHlt1DiProtonLowMultDecision;
   Int_t           TriggerDecHlt1BeamGasNoBeamBeam1Decision;
   Int_t           TriggerDecHlt1BeamGasNoBeamBeam2Decision;
   Int_t           TriggerDecHlt1BeamGasBeam1Decision;
   Int_t           TriggerDecHlt1BeamGasBeam2Decision;
   Int_t           TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision;
   Int_t           TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision;
   Int_t           TriggerDecHlt1BeamGasCrossingForcedRecoDecision;
   Int_t           TriggerDecHlt1ODINTechnicalDecision;
   Int_t           TriggerDecHlt1Tell1ErrorDecision;
   Int_t           TriggerDecHlt1BeamGasCrossingParasiticDecision;
   Int_t           TriggerDecHlt1ErrorEventDecision;
   Int_t           TriggerDecHlt1Global;
   Int_t           TriggerDecHlt1MBMicroBiasVeloDecision;
   Int_t           TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision;
   Int_t           TriggerDecHlt1MBMicroBiasTStationDecision;
   Int_t           TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision;
   Int_t           TriggerDecHlt1DiProtonDecision;
   Int_t           TriggerDecHlt1VeloClosingMicroBiasDecision;
   Int_t           TriggerDecHlt1SingleElectronNoIPDecision;
   Int_t           TriggerDecHlt1TrackForwardPassThroughDecision;
   Int_t           TriggerDecHlt1TrackForwardPassThroughLooseDecision;
   Int_t           TriggerDecHlt1CharmCalibrationNoBiasDecision;
   Int_t           TriggerDecHlt1L0HighSumETJetDecision;
   Int_t           TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision;
   Int_t           TriggerDecHlt1BeamGasHighRhoVerticesDecision;
   Int_t           TriggerDecHlt1VertexDisplVertexDecision;
   Int_t           TriggerDecHlt1TrackAllL0TightDecision;
   Int_t           TriggerDecHlt2SingleElectronTFLowPtDecision;
   Int_t           TriggerDecHlt2SingleElectronTFHighPtDecision;
   Int_t           TriggerDecHlt2DiElectronHighMassDecision;
   Int_t           TriggerDecHlt2DiElectronBDecision;
   Int_t           TriggerDecHlt2Topo2BodySimpleDecision;
   Int_t           TriggerDecHlt2Topo3BodySimpleDecision;
   Int_t           TriggerDecHlt2Topo4BodySimpleDecision;
   Int_t           TriggerDecHlt2Topo2BodyBBDTDecision;
   Int_t           TriggerDecHlt2Topo3BodyBBDTDecision;
   Int_t           TriggerDecHlt2Topo4BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoMu2BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoMu3BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoMu4BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoE2BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoE3BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoE4BodyBBDTDecision;
   Int_t           TriggerDecHlt2IncPhiDecision;
   Int_t           TriggerDecHlt2IncPhiSidebandsDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHKsLLDecision;
   Int_t           TriggerDecHlt2Dst2PiD02PiPiDecision;
   Int_t           TriggerDecHlt2Dst2PiD02MuMuDecision;
   Int_t           TriggerDecHlt2Dst2PiD02KMuDecision;
   Int_t           TriggerDecHlt2Dst2PiD02KPiDecision;
   Int_t           TriggerDecHlt2PassThroughDecision;
   Int_t           TriggerDecHlt2TransparentDecision;
   Int_t           TriggerDecHlt2ForwardDecision;
   Int_t           TriggerDecHlt2DebugEventDecision;
   Int_t           TriggerDecHlt2CharmHadD02KKDecision;
   Int_t           TriggerDecHlt2CharmHadD02KKWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02KPiDecision;
   Int_t           TriggerDecHlt2CharmHadD02KPiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02PiPiDecision;
   Int_t           TriggerDecHlt2CharmHadD02PiPiWideMassDecision;
   Int_t           TriggerDecHlt2ExpressJPsiDecision;
   Int_t           TriggerDecHlt2ExpressJPsiTagProbeDecision;
   Int_t           TriggerDecHlt2ExpressLambdaDecision;
   Int_t           TriggerDecHlt2ExpressKSDecision;
   Int_t           TriggerDecHlt2ExpressDs2PhiPiDecision;
   Int_t           TriggerDecHlt2ExpressBeamHaloDecision;
   Int_t           TriggerDecHlt2ExpressDStar2D0PiDecision;
   Int_t           TriggerDecHlt2ExpressHLT1PhysicsDecision;
   Int_t           TriggerDecHlt2Bs2PhiGammaDecision;
   Int_t           TriggerDecHlt2Bs2PhiGammaWideBMassDecision;
   Int_t           TriggerDecHlt2Bd2KstGammaDecision;
   Int_t           TriggerDecHlt2Bd2KstGammaWideKMassDecision;
   Int_t           TriggerDecHlt2Bd2KstGammaWideBMassDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0PiDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0KDecision;
   Int_t           TriggerDecHlt2CharmRareDecayD02MuMuDecision;
   Int_t           TriggerDecHlt2B2HHDecision;
   Int_t           TriggerDecHlt2MuonFromHLT1Decision;
   Int_t           TriggerDecHlt2SingleMuonDecision;
   Int_t           TriggerDecHlt2SingleMuonHighPTDecision;
   Int_t           TriggerDecHlt2SingleMuonLowPTDecision;
   Int_t           TriggerDecHlt2TFBc2JpsiMuXDecision;
   Int_t           TriggerDecHlt2TFBc2JpsiMuXSignalDecision;
   Int_t           TriggerDecHlt2DisplVerticesLowMassSingleDecision;
   Int_t           TriggerDecHlt2DisplVerticesHighMassSingleDecision;
   Int_t           TriggerDecHlt2DisplVerticesDoubleDecision;
   Int_t           TriggerDecHlt2DisplVerticesSinglePostScaledDecision;
   Int_t           TriggerDecHlt2DisplVerticesHighFDSingleDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleDownDecision;
   Int_t           TriggerDecHlt2B2HHPi0_MergedDecision;
   Int_t           TriggerDecHlt2CharmHadD2HHHDecision;
   Int_t           TriggerDecHlt2CharmHadD2HHHWideMassDecision;
   Int_t           TriggerDecHlt2DiMuonDecision;
   Int_t           TriggerDecHlt2DiMuonLowMassDecision;
   Int_t           TriggerDecHlt2DiMuonJPsiDecision;
   Int_t           TriggerDecHlt2DiMuonJPsiHighPTDecision;
   Int_t           TriggerDecHlt2DiMuonPsi2SDecision;
   Int_t           TriggerDecHlt2DiMuonBDecision;
   Int_t           TriggerDecHlt2DiMuonZDecision;
   Int_t           TriggerDecHlt2DiMuonDY1Decision;
   Int_t           TriggerDecHlt2DiMuonDY2Decision;
   Int_t           TriggerDecHlt2DiMuonDY3Decision;
   Int_t           TriggerDecHlt2DiMuonDY4Decision;
   Int_t           TriggerDecHlt2DiMuonDetachedDecision;
   Int_t           TriggerDecHlt2DiMuonDetachedHeavyDecision;
   Int_t           TriggerDecHlt2DiMuonDetachedJPsiDecision;
   Int_t           TriggerDecHlt2DiMuonNoPVDecision;
   Int_t           TriggerDecHlt2TriMuonDetachedDecision;
   Int_t           TriggerDecHlt2TriMuonTauDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHWideMassDecision;
   Int_t           TriggerDecHlt2ErrorEventDecision;
   Int_t           TriggerDecHlt2Global;
   Int_t           TriggerDecHlt2B2HHLTUnbiasedDecision;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02PiPiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KKDecision;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KPiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision;
   Int_t           TriggerDecHlt2DiProtonDecision;
   Int_t           TriggerDecHlt2DiProtonTFDecision;
   Int_t           TriggerDecHlt2DiProtonLowMultDecision;
   Int_t           TriggerDecHlt2DiProtonLowMultTFDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision;
   Int_t           TriggerDecHlt2CharmSemilepD2HMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision;
   Int_t           TriggerDecHlt2diPhotonDiMuonDecision;
   Int_t           TriggerDecHlt2LowMultMuonDecision;
   Int_t           TriggerDecHlt2LowMultHadronDecision;
   Int_t           TriggerDecHlt2LowMultPhotonDecision;
   Int_t           TriggerDecHlt2LowMultElectronDecision;
   Int_t           TriggerDecHlt2SingleTFElectronDecision;
   Int_t           TriggerDecHlt2SingleTFVHighPtElectronDecision;
   Int_t           TriggerDecHlt2B2HHLTUnbiasedDetachedDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2KPPiDecision;
   Int_t           TriggerDecHlt2SingleMuonVHighPTDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision;
   Int_t           TriggerDecHlt2CharmHadMinBiasLambdaC2KPPiDecision;
   Int_t           TriggerDecHlt2CharmHadMinBiasD02KPiDecision;
   Int_t           TriggerDecHlt2CharmHadMinBiasD02KKDecision;
   Int_t           TriggerDecHlt2CharmHadMinBiasDplus2hhhDecision;
   Int_t           TriggerDecHlt2CharmHadMinBiasLambdaC2LambdaPiDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleDecision;
   Int_t           TriggerDecHlt2DisplVerticesDoublePostScaledDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision;
   Int_t           TriggerDecHlt2RadiativeTopoTrackTOSDecision;
   Int_t           TriggerDecHlt2RadiativeTopoPhotonL0Decision;
   Int_t           TriggerDecHlt2DiMuonPsi2SHighPTDecision;
   Int_t           TriggerDecHlt2DoubleDiMuonDecision;
   Int_t           TriggerDecHlt2DiMuonAndMuonDecision;
   Int_t           TriggerDecHlt2DiMuonAndGammaDecision;
   Int_t           TriggerDecHlt2DiMuonAndD0Decision;
   Int_t           TriggerDecHlt2DiMuonAndDpDecision;
   Int_t           TriggerDecHlt2DiMuonAndDsDecision;
   Int_t           TriggerDecHlt2DiMuonAndLcDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision;
   Int_t           TriggerDecHlt2TopoRad2BodyBBDTDecision;
   Int_t           TriggerDecHlt2TopoRad2plus1BodyBBDTDecision;
   Int_t           TriggerDecHlt2LumiDecision;
   Int_t           TriggerDecHlt2LowMultHadron_nofilterDecision;
   Int_t           TriggerDecHlt2LowMultElectron_nofilterDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHKsDDDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0KS0Decision;
   Int_t           TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision;
   Int_t           TriggerDecHlt2ExpressD02KPiDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2KPKDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2PiPPiDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2PiPKDecision;
   Int_t           TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision;
   Int_t           TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision;
   Int_t           TriggerDecHlt2DiPhiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision;
   Int_t           TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision;
   Int_t           TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision;
   Int_t           TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision;
   Int_t           TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision;
   Int_t           TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision;
   Int_t           TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision;
   Int_t           TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision;
   Int_t           TriggerDecHlt2RadiativeTopoTrackDecision;
   Int_t           TriggerDecHlt2RadiativeTopoPhotonDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_4piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision;
   Int_t           TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02KKMuMuDecision;
   Int_t           TriggerDecHlt2CharmSemilepD02KPiMuMuDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_4piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_K3piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_2K2piDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_3KpiDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_Ch2Decision;
   Int_t           TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision;
   Int_t           TriggerDecHlt2DiMuonDetachedPsi2SDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHXDst_hhXDecision;
   Int_t           TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision;
   Int_t           TriggerDecHlt2LowMultD2KPiDecision;
   Int_t           TriggerDecHlt2LowMultD2KPiPiDecision;
   Int_t           TriggerDecHlt2LowMultD2K3PiDecision;
   Int_t           TriggerDecHlt2LowMultChiC2HHDecision;
   Int_t           TriggerDecHlt2LowMultChiC2HHHHDecision;
   Int_t           TriggerDecHlt2LowMultD2KPiWSDecision;
   Int_t           TriggerDecHlt2LowMultD2KPiPiWSDecision;
   Int_t           TriggerDecHlt2LowMultD2K3PiWSDecision;
   Int_t           TriggerDecHlt2LowMultChiC2HHWSDecision;
   Int_t           TriggerDecHlt2LowMultChiC2HHHHWSDecision;
   Int_t           TriggerDecHlt2LowMultDDIncDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleLoosePSDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleHighFDDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision;
   Int_t           TriggerDecHlt2DisplVerticesSingleHighMassDecision;
   Int_t           TriggerDecHlt2DisplVerticesSinglePSDecision;
   Int_t           TriggerDecHlt2DisplVerticesDoublePSDecision;
   Int_t           rec_charge;
   Float_t         truetau;
   Float_t         truedsetamunu;
   Float_t         truedsphipi;
   Int_t           particleid;
   Float_t         FlightDistance;
   Float_t         FlightDistanceError;
   Float_t         mass;
   Float_t         LifeTime;
   Float_t         IP;
   Float_t         IPSig;
   Float_t         VertexChi2;
   Float_t         dira;
   Float_t         pt;
   Float_t         BPVIPCHI2;
   Float_t         BPVLTIME;
   Float_t         BPVLTIME225;
   Float_t         dimuonchargeproduct;
   Float_t         DOCAone;
   Float_t         DOCAtwo;
   Float_t         DOCAthree;
   Float_t         mass_p0p2;
   Float_t         smearedmass_p0p2;
   Float_t         mass_p1p2;
   Float_t         smearedmass_p1p2;
   Float_t         mass_p0p1;
   Float_t         smearedmass_p0p1;
   Float_t         smearedmass;
   Float_t         truemass_p0p2;
   Float_t         truemass_p1p2;
   Float_t         truemass_p0p1;
   Float_t         truermass_p0p2;
   Float_t         truermass_p1p2;
   Float_t         truermass_p0p1;
   Float_t         mass_Kpipi;
   Float_t         mass_KKpi1;
   Float_t         mass_KKpi2;
   Float_t         mass_3pi;
   Float_t         polarisationangle;
   Float_t         IP_p0p2;
   Float_t         IP_p1p2;
   Float_t         mass_phihypo;
   Float_t         mass_k0k2;
   Float_t         mass_k1k2;
   Float_t         mass_pi0m1m2;
   Float_t         mass_m0pi1m2;
   Float_t         mass_m0m1pi2;
   Float_t         mass_pi0pi1m2;
   Float_t         mass_pi0m1pi2;
   Float_t         mass_m0pi1pi2;
   Float_t         mass_pi0pi1pi2;
   Float_t         mass_k0m1m2;
   Float_t         mass_m0k1m2;
   Float_t         mass_m0m1k2;
   Float_t         mass_k0k1m2;
   Float_t         mass_k0m1k2;
   Float_t         mass_m0k1k2;
   Float_t         mass_k0k1k2;
   Float_t         mass_k0pi1pi2;
   Float_t         mass_pi0k1pi2;
   Float_t         mass_pi0pi1k2;
   Float_t         mass_pi0k1k2;
   Float_t         mass_k0pi1k2;
   Float_t         mass_k0k1pi2;
   Float_t         mass_m0pi1k2;
   Float_t         mass_m0k1pi2;
   Float_t         mass_pi0m1k2;
   Float_t         mass_pi0k1m2;
   Float_t         mass_k0pi1m2;
   Float_t         mass_k0m1pi2;
   Float_t         muon_opening_angle;
   Float_t         MC_phimass;
   Float_t         MC_phi_daughters_invariantmass;
   Int_t           isolationa;
   Int_t           isolationb;
   Int_t           isolationc;
   Float_t         isolationd;
   Float_t         isolatione;
   Float_t         isolationf;
   Float_t         iso;
   Float_t         CDF1;
   Float_t         CDF2;
   Float_t         CDF3;
   Float_t         GeoMVA;
   Float_t         geomvacheck;
   Int_t           BCK;
   Int_t           tauproduction;
   Float_t         productionweightMC10;
   Float_t         productionweighterrorMC10;
   Float_t         productionweightMC11v3;
   Float_t         productionweighterrorMC11v3;
   Int_t           production;
   Int_t           EventHash;
   Float_t         Laura_SumBDT;
   Float_t         p0_Laura_IsoBDT;
   Float_t         p1_Laura_IsoBDT;
   Float_t         p2_Laura_IsoBDT;
   Float_t         p0_cloneDist;
   Float_t         p1_cloneDist;
   Float_t         p2_cloneDist;
   Float_t         p0_track_Chi2Dof;
   Float_t         p1_track_Chi2Dof;
   Float_t         p2_track_Chi2Dof;
   Float_t         min_ANNmuon;
   Int_t           p0_int_charge;
   Float_t         p0_float_charge;
   Float_t         p0_ANNghost;
   Float_t         p0_TRACKghost;
   Float_t         p0_TRACKlikelihood;
   Float_t         p0_ANNpion;
   Float_t         p0_ANNmuon;
   Float_t         p0_ANNkaon;
   Float_t         p0_ANNproton;
   Float_t         p0_ANNelectron;
   Float_t         p0_Tchi;
   Float_t         p0_Vchi;
   Float_t         p0_Tdof;
   Float_t         p0_Vdof;
   Float_t         p0_observedV;
   Float_t         p0_observedIT;
   Float_t         p0_observedOT;
   Float_t         p0_observedTT;
   Float_t         p0_expectedV;
   Float_t         p0_expectedIT;
   Float_t         p0_expectedOT;
   Float_t         p0_expectedTT;
   Float_t         p0_isMuon;
   Float_t         p0_MuonAcc;
   Float_t         p0_PIDmupi;
   Float_t         p0_PIDmuk;
   Float_t         p0_PIDpip;
   Float_t         p0_PIDpk;
   Float_t         p0_PIDppi;
   Float_t         p0_BPVIPCHI2;
   Float_t         p0_pt;
   Float_t         p0_p;
   Float_t         p0_eta;
   Float_t         p0_phi;
   Float_t         p0_track_MatchChi2;
   Float_t         p0_NShared;
   Float_t         p0_MuLL;
   Float_t         p0_MuDLL;
   Float_t         p0_MuBkg;
   Float_t         p0_richMU;
   Float_t         p0_richK;
   Float_t         p0_richPI;
   Float_t         p0_ecalMU;
   Float_t         p0_hcalMU;
   Float_t         p0_track_Chi2;
   Float_t         p0_track_Dof;
   Float_t         p0_NCandCommonFake;
   Float_t         p0_OTbaddrifttime;
   Float_t         p0_OToutliers;
   Float_t         p0_mother_mother_mother_mother_mcpid;
   Float_t         p0_mother_mother_mother_mcpid;
   Float_t         p0_mother_mother_mcpid;
   Float_t         p0_mother_mcpid;
   Float_t         p0_mcpid;
   Float_t         p0_ghostcat;
   Float_t         p0_trackhistory;
   Float_t         p0_IP;
   Float_t         p0_IPSig;
   Float_t         p0_largestMClifetime;
   Int_t           p1_int_charge;
   Float_t         p1_float_charge;
   Float_t         p1_ANNghost;
   Float_t         p1_TRACKghost;
   Float_t         p1_TRACKlikelihood;
   Float_t         p1_ANNpion;
   Float_t         p1_ANNmuon;
   Float_t         p1_ANNkaon;
   Float_t         p1_ANNproton;
   Float_t         p1_ANNelectron;
   Float_t         p1_Tchi;
   Float_t         p1_Vchi;
   Float_t         p1_Tdof;
   Float_t         p1_Vdof;
   Float_t         p1_observedV;
   Float_t         p1_observedIT;
   Float_t         p1_observedOT;
   Float_t         p1_observedTT;
   Float_t         p1_expectedV;
   Float_t         p1_expectedIT;
   Float_t         p1_expectedOT;
   Float_t         p1_expectedTT;
   Float_t         p1_isMuon;
   Float_t         p1_MuonAcc;
   Float_t         p1_PIDmupi;
   Float_t         p1_PIDmuk;
   Float_t         p1_PIDpip;
   Float_t         p1_PIDpk;
   Float_t         p1_PIDppi;
   Float_t         p1_BPVIPCHI2;
   Float_t         p1_pt;
   Float_t         p1_p;
   Float_t         p1_eta;
   Float_t         p1_phi;
   Float_t         p1_track_MatchChi2;
   Float_t         p1_NShared;
   Float_t         p1_MuLL;
   Float_t         p1_MuDLL;
   Float_t         p1_MuBkg;
   Float_t         p1_richMU;
   Float_t         p1_richK;
   Float_t         p1_richPI;
   Float_t         p1_ecalMU;
   Float_t         p1_hcalMU;
   Float_t         p1_track_Chi2;
   Float_t         p1_track_Dof;
   Float_t         p1_NCandCommonFake;
   Float_t         p1_OTbaddrifttime;
   Float_t         p1_OToutliers;
   Float_t         p1_mother_mother_mother_mother_mcpid;
   Float_t         p1_mother_mother_mother_mcpid;
   Float_t         p1_mother_mother_mcpid;
   Float_t         p1_mother_mcpid;
   Float_t         p1_mcpid;
   Float_t         p1_ghostcat;
   Float_t         p1_trackhistory;
   Float_t         p1_IP;
   Float_t         p1_IPSig;
   Float_t         p1_largestMClifetime;
   Int_t           p2_int_charge;
   Float_t         p2_float_charge;
   Float_t         p2_ANNghost;
   Float_t         p2_TRACKghost;
   Float_t         p2_TRACKlikelihood;
   Float_t         p2_ANNpion;
   Float_t         p2_ANNmuon;
   Float_t         p2_ANNkaon;
   Float_t         p2_ANNproton;
   Float_t         p2_ANNelectron;
   Float_t         p2_Tchi;
   Float_t         p2_Vchi;
   Float_t         p2_Tdof;
   Float_t         p2_Vdof;
   Float_t         p2_observedV;
   Float_t         p2_observedIT;
   Float_t         p2_observedOT;
   Float_t         p2_observedTT;
   Float_t         p2_expectedV;
   Float_t         p2_expectedIT;
   Float_t         p2_expectedOT;
   Float_t         p2_expectedTT;
   Float_t         p2_isMuon;
   Float_t         p2_MuonAcc;
   Float_t         p2_PIDmupi;
   Float_t         p2_PIDmuk;
   Float_t         p2_PIDpip;
   Float_t         p2_PIDpk;
   Float_t         p2_PIDppi;
   Float_t         p2_BPVIPCHI2;
   Float_t         p2_pt;
   Float_t         p2_p;
   Float_t         p2_eta;
   Float_t         p2_phi;
   Float_t         p2_track_MatchChi2;
   Float_t         p2_NShared;
   Float_t         p2_MuLL;
   Float_t         p2_MuDLL;
   Float_t         p2_MuBkg;
   Float_t         p2_richMU;
   Float_t         p2_richK;
   Float_t         p2_richPI;
   Float_t         p2_ecalMU;
   Float_t         p2_hcalMU;
   Float_t         p2_track_Chi2;
   Float_t         p2_track_Dof;
   Float_t         p2_NCandCommonFake;
   Float_t         p2_OTbaddrifttime;
   Float_t         p2_OToutliers;
   Float_t         p2_mother_mother_mother_mother_mcpid;
   Float_t         p2_mother_mother_mother_mcpid;
   Float_t         p2_mother_mother_mcpid;
   Float_t         p2_mother_mcpid;
   Float_t         p2_mcpid;
   Float_t         p2_ghostcat;
   Float_t         p2_trackhistory;
   Float_t         p2_IP;
   Float_t         p2_IPSig;
   Float_t         p2_largestMClifetime;
   Float_t         OThits;
   Float_t         IThits;
   Float_t         TThits;
   Float_t         VELOhits;
   Int_t           SPDhits;
   Float_t         NgammaVLLLL;
   Float_t         NgammaVLLRR;
   Float_t         NgammaRAD;
   Float_t         NgammaVLLLL_RAD;
   Float_t         NgammaVLLRR_RAD;
   Float_t         MCNgammaVLLLL;
   Float_t         MCNgammaVLLRR;
   Float_t         MCNgammaRAD;
   Float_t         MCNgammaVLLLL_RAD;
   Float_t         MCNgammaVLLRR_RAD;

   // List of branches
   TBranch        *b_RUNNING_EVENT_NUMBER;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_TCK;   //!
   TBranch        *b_cleaningcut;   //!
   TBranch        *b_NumberPV;   //!
   TBranch        *b_Ncandidates;   //!
   TBranch        *b_NbestTracks;   //!
   TBranch        *b_L0Dec;   //!
   TBranch        *b_Hlt1Dec;   //!
   TBranch        *b_Hlt2Dec;   //!
   TBranch        *b_Hlt2Dec_unprescaled;   //!
   TBranch        *b_Hlt2DecOld;   //!
   TBranch        *b_L0Hlt1DecMu;   //!
   TBranch        *b_Hlt2DecMu;   //!
   TBranch        *b_Hlt2DecSingleMu;   //!
   TBranch        *b_Hlt2DecDhhh;   //!
   TBranch        *b_TriggerTISL0Muon;   //!
   TBranch        *b_TriggerTPSL0Muon;   //!
   TBranch        *b_TriggerTISHlt1TrackMuon;   //!
   TBranch        *b_TriggerTPSHlt1TrackMuon;   //!
   TBranch        *b_TriggerTISHlt2DiMuonDetached;   //!
   TBranch        *b_TriggerTPSHlt2DiMuonDetached;   //!
   TBranch        *b_TriggerTISHlt2TriMuonTau;   //!
   TBranch        *b_TriggerTPSHlt2TriMuonTau;   //!
   TBranch        *b_TriggerTISHlt2CharmSemilepD2HMuMu;   //!
   TBranch        *b_TriggerTPSHlt2CharmSemilepD2HMuMu;   //!
   TBranch        *b_TriggerTOSL0B1gas;   //!
   TBranch        *b_TriggerTOSL0B2gas;   //!
   TBranch        *b_TriggerTOSL0Calo;   //!
   TBranch        *b_TriggerTOSL0DiMuon;   //!
   TBranch        *b_TriggerTOSL0DiMuonlowMult;   //!
   TBranch        *b_TriggerTOSL0Electron;   //!
   TBranch        *b_TriggerTOSL0GlobalPi0;   //!
   TBranch        *b_TriggerTOSL0HCAL;   //!
   TBranch        *b_TriggerTOSL0Hadron;   //!
   TBranch        *b_TriggerTOSL0LocalPi0;   //!
   TBranch        *b_TriggerTOSL0MuonMinbias;   //!
   TBranch        *b_TriggerTOSL0Muon;   //!
   TBranch        *b_TriggerTOSL0MuonLowMult;   //!
   TBranch        *b_TriggerTOSL0PU;   //!
   TBranch        *b_TriggerTOSL0PU20;   //!
   TBranch        *b_TriggerTOSL0Photon;   //!
   TBranch        *b_TriggerTOSL0SPD;   //!
   TBranch        *b_TriggerTOSL0SPD40;   //!
   TBranch        *b_TriggerTOSHlt1DiMuonHighMassDecision;   //!
   TBranch        *b_TriggerTOSHlt1DiMuonLowMassDecision;   //!
   TBranch        *b_TriggerTOSHlt1SingleMuonNoIPDecision;   //!
   TBranch        *b_TriggerTOSHlt1SingleMuonHighPTDecision;   //!
   TBranch        *b_TriggerTOSHlt1TrackAllL0Decision;   //!
   TBranch        *b_TriggerTOSHlt1TrackMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt1TrackPhotonDecision;   //!
   TBranch        *b_TriggerTOSHlt1LumiDecision;   //!
   TBranch        *b_TriggerTOSHlt1LumiMidBeamCrossingDecision;   //!
   TBranch        *b_TriggerTOSHlt1MBNoBiasDecision;   //!
   TBranch        *b_TriggerTOSHlt1L0AnyDecision;   //!
   TBranch        *b_TriggerTOSHlt1L0AnyRateLimitedDecision;   //!
   TBranch        *b_TriggerTOSHlt1L0AnyNoSPDDecision;   //!
   TBranch        *b_TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision;   //!
   TBranch        *b_TriggerTOSHlt1NoPVPassThroughDecision;   //!
   TBranch        *b_TriggerTOSHlt1DiProtonLowMultDecision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasNoBeamBeam1Decision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasNoBeamBeam2Decision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasBeam1Decision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasBeam2Decision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasCrossingForcedRecoDecision;   //!
   TBranch        *b_TriggerTOSHlt1ODINTechnicalDecision;   //!
   TBranch        *b_TriggerTOSHlt1Tell1ErrorDecision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasCrossingParasiticDecision;   //!
   TBranch        *b_TriggerTOSHlt1ErrorEventDecision;   //!
   TBranch        *b_TriggerTOSHlt1Global;   //!
   TBranch        *b_TriggerTOSHlt1MBMicroBiasVeloDecision;   //!
   TBranch        *b_TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision;   //!
   TBranch        *b_TriggerTOSHlt1MBMicroBiasTStationDecision;   //!
   TBranch        *b_TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision;   //!
   TBranch        *b_TriggerTOSHlt1DiProtonDecision;   //!
   TBranch        *b_TriggerTOSHlt1VeloClosingMicroBiasDecision;   //!
   TBranch        *b_TriggerTOSHlt1SingleElectronNoIPDecision;   //!
   TBranch        *b_TriggerTOSHlt1TrackForwardPassThroughDecision;   //!
   TBranch        *b_TriggerTOSHlt1TrackForwardPassThroughLooseDecision;   //!
   TBranch        *b_TriggerTOSHlt1CharmCalibrationNoBiasDecision;   //!
   TBranch        *b_TriggerTOSHlt1L0HighSumETJetDecision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision;   //!
   TBranch        *b_TriggerTOSHlt1BeamGasHighRhoVerticesDecision;   //!
   TBranch        *b_TriggerTOSHlt1VertexDisplVertexDecision;   //!
   TBranch        *b_TriggerTOSHlt1TrackAllL0TightDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleElectronTFLowPtDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleElectronTFHighPtDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiElectronHighMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiElectronBDecision;   //!
   TBranch        *b_TriggerTOSHlt2Topo2BodySimpleDecision;   //!
   TBranch        *b_TriggerTOSHlt2Topo3BodySimpleDecision;   //!
   TBranch        *b_TriggerTOSHlt2Topo4BodySimpleDecision;   //!
   TBranch        *b_TriggerTOSHlt2Topo2BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2Topo3BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2Topo4BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoMu2BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoMu3BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoMu4BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoE2BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoE3BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoE4BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2IncPhiDecision;   //!
   TBranch        *b_TriggerTOSHlt2IncPhiSidebandsDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHKsLLDecision;   //!
   TBranch        *b_TriggerTOSHlt2Dst2PiD02PiPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2Dst2PiD02MuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2Dst2PiD02KMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2Dst2PiD02KPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2PassThroughDecision;   //!
   TBranch        *b_TriggerTOSHlt2TransparentDecision;   //!
   TBranch        *b_TriggerTOSHlt2ForwardDecision;   //!
   TBranch        *b_TriggerTOSHlt2DebugEventDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02KKDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02KKWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02KPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02KPiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02PiPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02PiPiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressJPsiDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressJPsiTagProbeDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressLambdaDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressKSDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressDs2PhiPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressBeamHaloDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressDStar2D0PiDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressHLT1PhysicsDecision;   //!
   TBranch        *b_TriggerTOSHlt2Bs2PhiGammaDecision;   //!
   TBranch        *b_TriggerTOSHlt2Bs2PhiGammaWideBMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2Bd2KstGammaDecision;   //!
   TBranch        *b_TriggerTOSHlt2Bd2KstGammaWideKMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2Bd2KstGammaWideBMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0PiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0KDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmRareDecayD02MuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2B2HHDecision;   //!
   TBranch        *b_TriggerTOSHlt2MuonFromHLT1Decision;   //!
   TBranch        *b_TriggerTOSHlt2SingleMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleMuonHighPTDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleMuonLowPTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TFBc2JpsiMuXDecision;   //!
   TBranch        *b_TriggerTOSHlt2TFBc2JpsiMuXSignalDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesLowMassSingleDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesHighMassSingleDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesDoubleDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSinglePostScaledDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesHighFDSingleDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleDownDecision;   //!
   TBranch        *b_TriggerTOSHlt2B2HHPi0_MergedDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2HHHDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2HHHWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonLowMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonJPsiDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonJPsiHighPTDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonPsi2SDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonBDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonZDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDY1Decision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDY2Decision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDY3Decision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDY4Decision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDetachedDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDetachedHeavyDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDetachedJPsiDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonNoPVDecision;   //!
   TBranch        *b_TriggerTOSHlt2TriMuonDetachedDecision;   //!
   TBranch        *b_TriggerTOSHlt2TriMuonTauDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2ErrorEventDecision;   //!
   TBranch        *b_TriggerTOSHlt2Global;   //!
   TBranch        *b_TriggerTOSHlt2B2HHLTUnbiasedDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HH_D02KKDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HH_D02KPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiProtonDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiProtonTFDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiProtonLowMultDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiProtonLowMultTFDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD2HMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HHMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2diPhotonDiMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultHadronDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultPhotonDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultElectronDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleTFElectronDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleTFVHighPtElectronDecision;   //!
   TBranch        *b_TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2KPPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2SingleMuonVHighPTDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadMinBiasLambdaC2KPPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadMinBiasD02KPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadMinBiasD02KKDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadMinBiasDplus2hhhDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadMinBiasLambdaC2LambdaPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesDoublePostScaledDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision;   //!
   TBranch        *b_TriggerTOSHlt2RadiativeTopoTrackTOSDecision;   //!
   TBranch        *b_TriggerTOSHlt2RadiativeTopoPhotonL0Decision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonPsi2SHighPTDecision;   //!
   TBranch        *b_TriggerTOSHlt2DoubleDiMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonAndMuonDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonAndGammaDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonAndD0Decision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonAndDpDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonAndDsDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonAndLcDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoRad2BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision;   //!
   TBranch        *b_TriggerTOSHlt2LumiDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultHadron_nofilterDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultElectron_nofilterDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHKsDDDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0KS0Decision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2ExpressD02KPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2KPKDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2PiPKDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiPhiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision;   //!
   TBranch        *b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision;   //!
   TBranch        *b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision;   //!
   TBranch        *b_TriggerTOSHlt2RadiativeTopoTrackDecision;   //!
   TBranch        *b_TriggerTOSHlt2RadiativeTopoPhotonDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02KKMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_4piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_K3piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2DiMuonDetachedPsi2SDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision;   //!
   TBranch        *b_TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultD2KPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultD2KPiPiDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultD2K3PiDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultChiC2HHDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultChiC2HHHHDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultD2KPiWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultD2KPiPiWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultD2K3PiWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultChiC2HHWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultChiC2HHHHWSDecision;   //!
   TBranch        *b_TriggerTOSHlt2LowMultDDIncDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleLoosePSDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleHighFDDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSingleHighMassDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesSinglePSDecision;   //!
   TBranch        *b_TriggerTOSHlt2DisplVerticesDoublePSDecision;   //!
   TBranch        *b_TriggerDecL0B1gas;   //!
   TBranch        *b_TriggerDecL0B2gas;   //!
   TBranch        *b_TriggerDecL0Calo;   //!
   TBranch        *b_TriggerDecL0DiMuon;   //!
   TBranch        *b_TriggerDecL0DiMuonlowMult;   //!
   TBranch        *b_TriggerDecL0Electron;   //!
   TBranch        *b_TriggerDecL0GlobalPi0;   //!
   TBranch        *b_TriggerDecL0HCAL;   //!
   TBranch        *b_TriggerDecL0Hadron;   //!
   TBranch        *b_TriggerDecL0LocalPi0;   //!
   TBranch        *b_TriggerDecL0MuonMinbias;   //!
   TBranch        *b_TriggerDecL0Muon;   //!
   TBranch        *b_TriggerDecL0MuonLowMult;   //!
   TBranch        *b_TriggerDecL0PU;   //!
   TBranch        *b_TriggerDecL0PU20;   //!
   TBranch        *b_TriggerDecL0Photon;   //!
   TBranch        *b_TriggerDecL0SPD;   //!
   TBranch        *b_TriggerDecL0SPD40;   //!
   TBranch        *b_TriggerDecHlt1DiMuonHighMassDecision;   //!
   TBranch        *b_TriggerDecHlt1DiMuonLowMassDecision;   //!
   TBranch        *b_TriggerDecHlt1SingleMuonNoIPDecision;   //!
   TBranch        *b_TriggerDecHlt1SingleMuonHighPTDecision;   //!
   TBranch        *b_TriggerDecHlt1TrackAllL0Decision;   //!
   TBranch        *b_TriggerDecHlt1TrackMuonDecision;   //!
   TBranch        *b_TriggerDecHlt1TrackPhotonDecision;   //!
   TBranch        *b_TriggerDecHlt1LumiDecision;   //!
   TBranch        *b_TriggerDecHlt1LumiMidBeamCrossingDecision;   //!
   TBranch        *b_TriggerDecHlt1MBNoBiasDecision;   //!
   TBranch        *b_TriggerDecHlt1L0AnyDecision;   //!
   TBranch        *b_TriggerDecHlt1L0AnyRateLimitedDecision;   //!
   TBranch        *b_TriggerDecHlt1L0AnyNoSPDDecision;   //!
   TBranch        *b_TriggerDecHlt1L0AnyNoSPDRateLimitedDecision;   //!
   TBranch        *b_TriggerDecHlt1NoPVPassThroughDecision;   //!
   TBranch        *b_TriggerDecHlt1DiProtonLowMultDecision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasNoBeamBeam1Decision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasNoBeamBeam2Decision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasBeam1Decision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasBeam2Decision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingForcedRecoDecision;   //!
   TBranch        *b_TriggerDecHlt1ODINTechnicalDecision;   //!
   TBranch        *b_TriggerDecHlt1Tell1ErrorDecision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingParasiticDecision;   //!
   TBranch        *b_TriggerDecHlt1ErrorEventDecision;   //!
   TBranch        *b_TriggerDecHlt1Global;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasVeloDecision;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasTStationDecision;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision;   //!
   TBranch        *b_TriggerDecHlt1DiProtonDecision;   //!
   TBranch        *b_TriggerDecHlt1VeloClosingMicroBiasDecision;   //!
   TBranch        *b_TriggerDecHlt1SingleElectronNoIPDecision;   //!
   TBranch        *b_TriggerDecHlt1TrackForwardPassThroughDecision;   //!
   TBranch        *b_TriggerDecHlt1TrackForwardPassThroughLooseDecision;   //!
   TBranch        *b_TriggerDecHlt1CharmCalibrationNoBiasDecision;   //!
   TBranch        *b_TriggerDecHlt1L0HighSumETJetDecision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision;   //!
   TBranch        *b_TriggerDecHlt1BeamGasHighRhoVerticesDecision;   //!
   TBranch        *b_TriggerDecHlt1VertexDisplVertexDecision;   //!
   TBranch        *b_TriggerDecHlt1TrackAllL0TightDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleElectronTFLowPtDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleElectronTFHighPtDecision;   //!
   TBranch        *b_TriggerDecHlt2DiElectronHighMassDecision;   //!
   TBranch        *b_TriggerDecHlt2DiElectronBDecision;   //!
   TBranch        *b_TriggerDecHlt2Topo2BodySimpleDecision;   //!
   TBranch        *b_TriggerDecHlt2Topo3BodySimpleDecision;   //!
   TBranch        *b_TriggerDecHlt2Topo4BodySimpleDecision;   //!
   TBranch        *b_TriggerDecHlt2Topo2BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2Topo3BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2Topo4BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoMu2BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoMu3BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoMu4BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoE2BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoE3BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoE4BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2IncPhiDecision;   //!
   TBranch        *b_TriggerDecHlt2IncPhiSidebandsDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHKsLLDecision;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02PiPiDecision;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02MuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02KMuDecision;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02KPiDecision;   //!
   TBranch        *b_TriggerDecHlt2PassThroughDecision;   //!
   TBranch        *b_TriggerDecHlt2TransparentDecision;   //!
   TBranch        *b_TriggerDecHlt2ForwardDecision;   //!
   TBranch        *b_TriggerDecHlt2DebugEventDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KKDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KKWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KPiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02PiPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02PiPiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressJPsiDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressJPsiTagProbeDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressLambdaDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressKSDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressDs2PhiPiDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressBeamHaloDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressDStar2D0PiDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressHLT1PhysicsDecision;   //!
   TBranch        *b_TriggerDecHlt2Bs2PhiGammaDecision;   //!
   TBranch        *b_TriggerDecHlt2Bs2PhiGammaWideBMassDecision;   //!
   TBranch        *b_TriggerDecHlt2Bd2KstGammaDecision;   //!
   TBranch        *b_TriggerDecHlt2Bd2KstGammaWideKMassDecision;   //!
   TBranch        *b_TriggerDecHlt2Bd2KstGammaWideBMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0PiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0KDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmRareDecayD02MuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2B2HHDecision;   //!
   TBranch        *b_TriggerDecHlt2MuonFromHLT1Decision;   //!
   TBranch        *b_TriggerDecHlt2SingleMuonDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleMuonHighPTDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleMuonLowPTDecision;   //!
   TBranch        *b_TriggerDecHlt2TFBc2JpsiMuXDecision;   //!
   TBranch        *b_TriggerDecHlt2TFBc2JpsiMuXSignalDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesLowMassSingleDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesHighMassSingleDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesDoubleDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSinglePostScaledDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesHighFDSingleDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleDownDecision;   //!
   TBranch        *b_TriggerDecHlt2B2HHPi0_MergedDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2HHHDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2HHHWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonLowMassDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonJPsiDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonJPsiHighPTDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonPsi2SDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonBDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonZDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY1Decision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY2Decision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY3Decision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY4Decision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetachedDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetachedHeavyDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetachedJPsiDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonNoPVDecision;   //!
   TBranch        *b_TriggerDecHlt2TriMuonDetachedDecision;   //!
   TBranch        *b_TriggerDecHlt2TriMuonTauDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2ErrorEventDecision;   //!
   TBranch        *b_TriggerDecHlt2Global;   //!
   TBranch        *b_TriggerDecHlt2B2HHLTUnbiasedDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02PiPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KKDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision;   //!
   TBranch        *b_TriggerDecHlt2DiProtonDecision;   //!
   TBranch        *b_TriggerDecHlt2DiProtonTFDecision;   //!
   TBranch        *b_TriggerDecHlt2DiProtonLowMultDecision;   //!
   TBranch        *b_TriggerDecHlt2DiProtonLowMultTFDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD2HMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2diPhotonDiMuonDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultMuonDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultHadronDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultPhotonDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultElectronDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleTFElectronDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleTFVHighPtElectronDecision;   //!
   TBranch        *b_TriggerDecHlt2B2HHLTUnbiasedDetachedDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2KPPiDecision;   //!
   TBranch        *b_TriggerDecHlt2SingleMuonVHighPTDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadMinBiasLambdaC2KPPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadMinBiasD02KPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadMinBiasD02KKDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadMinBiasDplus2hhhDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadMinBiasLambdaC2LambdaPiDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesDoublePostScaledDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision;   //!
   TBranch        *b_TriggerDecHlt2RadiativeTopoTrackTOSDecision;   //!
   TBranch        *b_TriggerDecHlt2RadiativeTopoPhotonL0Decision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonPsi2SHighPTDecision;   //!
   TBranch        *b_TriggerDecHlt2DoubleDiMuonDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonAndMuonDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonAndGammaDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonAndD0Decision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonAndDpDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonAndDsDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonAndLcDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoRad2BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2TopoRad2plus1BodyBBDTDecision;   //!
   TBranch        *b_TriggerDecHlt2LumiDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultHadron_nofilterDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultElectron_nofilterDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHKsDDDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0KS0Decision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2ExpressD02KPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2KPKDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2PiPPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2PiPKDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision;   //!
   TBranch        *b_TriggerDecHlt2DiPhiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision;   //!
   TBranch        *b_TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision;   //!
   TBranch        *b_TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision;   //!
   TBranch        *b_TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision;   //!
   TBranch        *b_TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision;   //!
   TBranch        *b_TriggerDecHlt2RadiativeTopoTrackDecision;   //!
   TBranch        *b_TriggerDecHlt2RadiativeTopoPhotonDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_4piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02KKMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02KPiMuMuDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_4piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_K3piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_2K2piDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_3KpiDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_Ch2Decision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetachedPsi2SDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHXDst_hhXDecision;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultD2KPiDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultD2KPiPiDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultD2K3PiDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultChiC2HHDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultChiC2HHHHDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultD2KPiWSDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultD2KPiPiWSDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultD2K3PiWSDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultChiC2HHWSDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultChiC2HHHHWSDecision;   //!
   TBranch        *b_TriggerDecHlt2LowMultDDIncDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleLoosePSDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleHighFDDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleHighMassDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSinglePSDecision;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesDoublePSDecision;   //!
   TBranch        *b_rec_charge;   //!
   TBranch        *b_truetau;   //!
   TBranch        *b_truedsetamunu;   //!
   TBranch        *b_truedsphipi;   //!
   TBranch        *b_particleid;   //!
   TBranch        *b_FlightDistance;   //!
   TBranch        *b_FlightDistanceError;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_LifeTime;   //!
   TBranch        *b_IP;   //!
   TBranch        *b_IPSig;   //!
   TBranch        *b_VertexChi2;   //!
   TBranch        *b_dira;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_BPVIPCHI2;   //!
   TBranch        *b_BPVLTIME;   //!
   TBranch        *b_BPVLTIME225;   //!
   TBranch        *b_dimuonchargeproduct;   //!
   TBranch        *b_DOCAone;   //!
   TBranch        *b_DOCAtwo;   //!
   TBranch        *b_DOCAthree;   //!
   TBranch        *b_mass_p0p2;   //!
   TBranch        *b_smearedmass_p0p2;   //!
   TBranch        *b_mass_p1p2;   //!
   TBranch        *b_smearedmass_p1p2;   //!
   TBranch        *b_mass_p0p1;   //!
   TBranch        *b_smearedmass_p0p1;   //!
   TBranch        *b_smearedmass;   //!
   TBranch        *b_truemass_p0p2;   //!
   TBranch        *b_truemass_p1p2;   //!
   TBranch        *b_truemass_p0p1;   //!
   TBranch        *b_truermass_p0p2;   //!
   TBranch        *b_truermass_p1p2;   //!
   TBranch        *b_truermass_p0p1;   //!
   TBranch        *b_mass_Kpipi;   //!
   TBranch        *b_mass_KKpi1;   //!
   TBranch        *b_mass_KKpi2;   //!
   TBranch        *b_mass_3pi;   //!
   TBranch        *b_polarisationangle;   //!
   TBranch        *b_IP_p0p2;   //!
   TBranch        *b_IP_p1p2;   //!
   TBranch        *b_mass_phihypo;   //!
   TBranch        *b_mass_k0k2;   //!
   TBranch        *b_mass_k1k2;   //!
   TBranch        *b_mass_pi0m1m2;   //!
   TBranch        *b_mass_m0pi1m2;   //!
   TBranch        *b_mass_m0m1pi2;   //!
   TBranch        *b_mass_pi0pi1m2;   //!
   TBranch        *b_mass_pi0m1pi2;   //!
   TBranch        *b_mass_m0pi1pi2;   //!
   TBranch        *b_mass_pi0pi1pi2;   //!
   TBranch        *b_mass_k0m1m2;   //!
   TBranch        *b_mass_m0k1m2;   //!
   TBranch        *b_mass_m0m1k2;   //!
   TBranch        *b_mass_k0k1m2;   //!
   TBranch        *b_mass_k0m1k2;   //!
   TBranch        *b_mass_m0k1k2;   //!
   TBranch        *b_mass_k0k1k2;   //!
   TBranch        *b_mass_k0pi1pi2;   //!
   TBranch        *b_mass_pi0k1pi2;   //!
   TBranch        *b_mass_pi0pi1k2;   //!
   TBranch        *b_mass_pi0k1k2;   //!
   TBranch        *b_mass_k0pi1k2;   //!
   TBranch        *b_mass_k0k1pi2;   //!
   TBranch        *b_mass_m0pi1k2;   //!
   TBranch        *b_mass_m0k1pi2;   //!
   TBranch        *b_mass_pi0m1k2;   //!
   TBranch        *b_mass_pi0k1m2;   //!
   TBranch        *b_mass_k0pi1m2;   //!
   TBranch        *b_mass_k0m1pi2;   //!
   TBranch        *b_muon_opening_angle;   //!
   TBranch        *b_MC_phimass;   //!
   TBranch        *b_MC_phi_daughters_invariantmass;   //!
   TBranch        *b_isolationa;   //!
   TBranch        *b_isolationb;   //!
   TBranch        *b_isolationc;   //!
   TBranch        *b_isolationd;   //!
   TBranch        *b_isolatione;   //!
   TBranch        *b_isolationf;   //!
   TBranch        *b_iso;   //!
   TBranch        *b_CDF1;   //!
   TBranch        *b_CDF2;   //!
   TBranch        *b_CDF3;   //!
   TBranch        *b_GeoMVA;   //!
   TBranch        *b_geomvacheck;   //!
   TBranch        *b_BCK;   //!
   TBranch        *b_tauproduction;   //!
   TBranch        *b_productionweightMC10;   //!
   TBranch        *b_productionweighterrorMC10;   //!
   TBranch        *b_productionweightMC11v3;   //!
   TBranch        *b_productionweighterrorMC11v3;   //!
   TBranch        *b_production;   //!
   TBranch        *b_EventHash;   //!
   TBranch        *b_Laura_SumBDT;   //!
   TBranch        *b_p0_Laura_IsoBDT;   //!
   TBranch        *b_p1_Laura_IsoBDT;   //!
   TBranch        *b_p2_Laura_IsoBDT;   //!
   TBranch        *b_p0_cloneDist;   //!
   TBranch        *b_p1_cloneDist;   //!
   TBranch        *b_p2_cloneDist;   //!
   TBranch        *b_p0_track_Chi2Dof;   //!
   TBranch        *b_p1_track_Chi2Dof;   //!
   TBranch        *b_p2_track_Chi2Dof;   //!
   TBranch        *b_min_ANNmuon;   //!
   TBranch        *b_p0_int_charge;   //!
   TBranch        *b_p0_float_charge;   //!
   TBranch        *b_p0_ANNghost;   //!
   TBranch        *b_p0_TRACKghost;   //!
   TBranch        *b_p0_TRACKlikelihood;   //!
   TBranch        *b_p0_ANNpion;   //!
   TBranch        *b_p0_ANNmuon;   //!
   TBranch        *b_p0_ANNkaon;   //!
   TBranch        *b_p0_ANNproton;   //!
   TBranch        *b_p0_ANNelectron;   //!
   TBranch        *b_p0_Tchi;   //!
   TBranch        *b_p0_Vchi;   //!
   TBranch        *b_p0_Tdof;   //!
   TBranch        *b_p0_Vdof;   //!
   TBranch        *b_p0_observedV;   //!
   TBranch        *b_p0_observedIT;   //!
   TBranch        *b_p0_observedOT;   //!
   TBranch        *b_p0_observedTT;   //!
   TBranch        *b_p0_expectedV;   //!
   TBranch        *b_p0_expectedIT;   //!
   TBranch        *b_p0_expectedOT;   //!
   TBranch        *b_p0_expectedTT;   //!
   TBranch        *b_p0_isMuon;   //!
   TBranch        *b_p0_MuonAcc;   //!
   TBranch        *b_p0_PIDmupi;   //!
   TBranch        *b_p0_PIDmuk;   //!
   TBranch        *b_p0_PIDpip;   //!
   TBranch        *b_p0_PIDpk;   //!
   TBranch        *b_p0_PIDppi;   //!
   TBranch        *b_p0_BPVIPCHI2;   //!
   TBranch        *b_p0_pt;   //!
   TBranch        *b_p0_p;   //!
   TBranch        *b_p0_eta;   //!
   TBranch        *b_p0_phi;   //!
   TBranch        *b_p0_track_MatchChi2;   //!
   TBranch        *b_p0_NShared;   //!
   TBranch        *b_p0_MuLL;   //!
   TBranch        *b_p0_MuDLL;   //!
   TBranch        *b_p0_MuBkg;   //!
   TBranch        *b_p0_richMU;   //!
   TBranch        *b_p0_richK;   //!
   TBranch        *b_p0_richPI;   //!
   TBranch        *b_p0_ecalMU;   //!
   TBranch        *b_p0_hcalMU;   //!
   TBranch        *b_p0_track_Chi2;   //!
   TBranch        *b_p0_track_Dof;   //!
   TBranch        *b_p0_NCandCommonFake;   //!
   TBranch        *b_p0_OTbaddrifttime;   //!
   TBranch        *b_p0_OToutliers;   //!
   TBranch        *b_p0_mother_mother_mother_mother_mcpid;   //!
   TBranch        *b_p0_mother_mother_mother_mcpid;   //!
   TBranch        *b_p0_mother_mother_mcpid;   //!
   TBranch        *b_p0_mother_mcpid;   //!
   TBranch        *b_p0_mcpid;   //!
   TBranch        *b_p0_ghostcat;   //!
   TBranch        *b_p0_trackhistory;   //!
   TBranch        *b_p0_IP;   //!
   TBranch        *b_p0_IPSig;   //!
   TBranch        *b_p0_largestMClifetime;   //!
   TBranch        *b_p1_int_charge;   //!
   TBranch        *b_p1_float_charge;   //!
   TBranch        *b_p1_ANNghost;   //!
   TBranch        *b_p1_TRACKghost;   //!
   TBranch        *b_p1_TRACKlikelihood;   //!
   TBranch        *b_p1_ANNpion;   //!
   TBranch        *b_p1_ANNmuon;   //!
   TBranch        *b_p1_ANNkaon;   //!
   TBranch        *b_p1_ANNproton;   //!
   TBranch        *b_p1_ANNelectron;   //!
   TBranch        *b_p1_Tchi;   //!
   TBranch        *b_p1_Vchi;   //!
   TBranch        *b_p1_Tdof;   //!
   TBranch        *b_p1_Vdof;   //!
   TBranch        *b_p1_observedV;   //!
   TBranch        *b_p1_observedIT;   //!
   TBranch        *b_p1_observedOT;   //!
   TBranch        *b_p1_observedTT;   //!
   TBranch        *b_p1_expectedV;   //!
   TBranch        *b_p1_expectedIT;   //!
   TBranch        *b_p1_expectedOT;   //!
   TBranch        *b_p1_expectedTT;   //!
   TBranch        *b_p1_isMuon;   //!
   TBranch        *b_p1_MuonAcc;   //!
   TBranch        *b_p1_PIDmupi;   //!
   TBranch        *b_p1_PIDmuk;   //!
   TBranch        *b_p1_PIDpip;   //!
   TBranch        *b_p1_PIDpk;   //!
   TBranch        *b_p1_PIDppi;   //!
   TBranch        *b_p1_BPVIPCHI2;   //!
   TBranch        *b_p1_pt;   //!
   TBranch        *b_p1_p;   //!
   TBranch        *b_p1_eta;   //!
   TBranch        *b_p1_phi;   //!
   TBranch        *b_p1_track_MatchChi2;   //!
   TBranch        *b_p1_NShared;   //!
   TBranch        *b_p1_MuLL;   //!
   TBranch        *b_p1_MuDLL;   //!
   TBranch        *b_p1_MuBkg;   //!
   TBranch        *b_p1_richMU;   //!
   TBranch        *b_p1_richK;   //!
   TBranch        *b_p1_richPI;   //!
   TBranch        *b_p1_ecalMU;   //!
   TBranch        *b_p1_hcalMU;   //!
   TBranch        *b_p1_track_Chi2;   //!
   TBranch        *b_p1_track_Dof;   //!
   TBranch        *b_p1_NCandCommonFake;   //!
   TBranch        *b_p1_OTbaddrifttime;   //!
   TBranch        *b_p1_OToutliers;   //!
   TBranch        *b_p1_mother_mother_mother_mother_mcpid;   //!
   TBranch        *b_p1_mother_mother_mother_mcpid;   //!
   TBranch        *b_p1_mother_mother_mcpid;   //!
   TBranch        *b_p1_mother_mcpid;   //!
   TBranch        *b_p1_mcpid;   //!
   TBranch        *b_p1_ghostcat;   //!
   TBranch        *b_p1_trackhistory;   //!
   TBranch        *b_p1_IP;   //!
   TBranch        *b_p1_IPSig;   //!
   TBranch        *b_p1_largestMClifetime;   //!
   TBranch        *b_p2_int_charge;   //!
   TBranch        *b_p2_float_charge;   //!
   TBranch        *b_p2_ANNghost;   //!
   TBranch        *b_p2_TRACKghost;   //!
   TBranch        *b_p2_TRACKlikelihood;   //!
   TBranch        *b_p2_ANNpion;   //!
   TBranch        *b_p2_ANNmuon;   //!
   TBranch        *b_p2_ANNkaon;   //!
   TBranch        *b_p2_ANNproton;   //!
   TBranch        *b_p2_ANNelectron;   //!
   TBranch        *b_p2_Tchi;   //!
   TBranch        *b_p2_Vchi;   //!
   TBranch        *b_p2_Tdof;   //!
   TBranch        *b_p2_Vdof;   //!
   TBranch        *b_p2_observedV;   //!
   TBranch        *b_p2_observedIT;   //!
   TBranch        *b_p2_observedOT;   //!
   TBranch        *b_p2_observedTT;   //!
   TBranch        *b_p2_expectedV;   //!
   TBranch        *b_p2_expectedIT;   //!
   TBranch        *b_p2_expectedOT;   //!
   TBranch        *b_p2_expectedTT;   //!
   TBranch        *b_p2_isMuon;   //!
   TBranch        *b_p2_MuonAcc;   //!
   TBranch        *b_p2_PIDmupi;   //!
   TBranch        *b_p2_PIDmuk;   //!
   TBranch        *b_p2_PIDpip;   //!
   TBranch        *b_p2_PIDpk;   //!
   TBranch        *b_p2_PIDppi;   //!
   TBranch        *b_p2_BPVIPCHI2;   //!
   TBranch        *b_p2_pt;   //!
   TBranch        *b_p2_p;   //!
   TBranch        *b_p2_eta;   //!
   TBranch        *b_p2_phi;   //!
   TBranch        *b_p2_track_MatchChi2;   //!
   TBranch        *b_p2_NShared;   //!
   TBranch        *b_p2_MuLL;   //!
   TBranch        *b_p2_MuDLL;   //!
   TBranch        *b_p2_MuBkg;   //!
   TBranch        *b_p2_richMU;   //!
   TBranch        *b_p2_richK;   //!
   TBranch        *b_p2_richPI;   //!
   TBranch        *b_p2_ecalMU;   //!
   TBranch        *b_p2_hcalMU;   //!
   TBranch        *b_p2_track_Chi2;   //!
   TBranch        *b_p2_track_Dof;   //!
   TBranch        *b_p2_NCandCommonFake;   //!
   TBranch        *b_p2_OTbaddrifttime;   //!
   TBranch        *b_p2_OToutliers;   //!
   TBranch        *b_p2_mother_mother_mother_mother_mcpid;   //!
   TBranch        *b_p2_mother_mother_mother_mcpid;   //!
   TBranch        *b_p2_mother_mother_mcpid;   //!
   TBranch        *b_p2_mother_mcpid;   //!
   TBranch        *b_p2_mcpid;   //!
   TBranch        *b_p2_ghostcat;   //!
   TBranch        *b_p2_trackhistory;   //!
   TBranch        *b_p2_IP;   //!
   TBranch        *b_p2_IPSig;   //!
   TBranch        *b_p2_largestMClifetime;   //!
   TBranch        *b_OThits;   //!
   TBranch        *b_IThits;   //!
   TBranch        *b_TThits;   //!
   TBranch        *b_VELOhits;   //!
   TBranch        *b_SPDhits;   //!
   TBranch        *b_NgammaVLLLL;   //!
   TBranch        *b_NgammaVLLRR;   //!
   TBranch        *b_NgammaRAD;   //!
   TBranch        *b_NgammaVLLLL_RAD;   //!
   TBranch        *b_NgammaVLLRR_RAD;   //!
   TBranch        *b_MCNgammaVLLLL;   //!
   TBranch        *b_MCNgammaVLLRR;   //!
   TBranch        *b_MCNgammaRAD;   //!
   TBranch        *b_MCNgammaVLLLL_RAD;   //!
   TBranch        *b_MCNgammaVLLRR_RAD;   //!

   readNtuple(TTree *tree=0);
   virtual ~readNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef readNtuple_cxx
readNtuple::readNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("Tau23Mu",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Tau23Mu","");
      chain->Add("/afs/cern.ch/work/p/pseyfert/public/Tau_MC/v9_original/MC12_inclB.root/Tau23Mu");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

readNtuple::~readNtuple()
{
   if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t readNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t readNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void readNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RUNNING_EVENT_NUMBER", &RUNNING_EVENT_NUMBER, &b_RUNNING_EVENT_NUMBER);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("TCK", &TCK, &b_TCK);
   fChain->SetBranchAddress("cleaningcut", &cleaningcut, &b_cleaningcut);
   fChain->SetBranchAddress("NumberPV", &NumberPV, &b_NumberPV);
   fChain->SetBranchAddress("Ncandidates", &Ncandidates, &b_Ncandidates);
   fChain->SetBranchAddress("NbestTracks", &NbestTracks, &b_NbestTracks);
   fChain->SetBranchAddress("L0Dec", &L0Dec, &b_L0Dec);
   fChain->SetBranchAddress("Hlt1Dec", &Hlt1Dec, &b_Hlt1Dec);
   fChain->SetBranchAddress("Hlt2Dec", &Hlt2Dec, &b_Hlt2Dec);
   fChain->SetBranchAddress("Hlt2Dec_unprescaled", &Hlt2Dec_unprescaled, &b_Hlt2Dec_unprescaled);
   fChain->SetBranchAddress("Hlt2DecOld", &Hlt2DecOld, &b_Hlt2DecOld);
   fChain->SetBranchAddress("L0Hlt1DecMu", &L0Hlt1DecMu, &b_L0Hlt1DecMu);
   fChain->SetBranchAddress("Hlt2DecMu", &Hlt2DecMu, &b_Hlt2DecMu);
   fChain->SetBranchAddress("Hlt2DecSingleMu", &Hlt2DecSingleMu, &b_Hlt2DecSingleMu);
   fChain->SetBranchAddress("Hlt2DecDhhh", &Hlt2DecDhhh, &b_Hlt2DecDhhh);
   fChain->SetBranchAddress("TriggerTISL0Muon", &TriggerTISL0Muon, &b_TriggerTISL0Muon);
   fChain->SetBranchAddress("TriggerTPSL0Muon", &TriggerTPSL0Muon, &b_TriggerTPSL0Muon);
   fChain->SetBranchAddress("TriggerTISHlt1TrackMuon", &TriggerTISHlt1TrackMuon, &b_TriggerTISHlt1TrackMuon);
   fChain->SetBranchAddress("TriggerTPSHlt1TrackMuon", &TriggerTPSHlt1TrackMuon, &b_TriggerTPSHlt1TrackMuon);
   fChain->SetBranchAddress("TriggerTISHlt2DiMuonDetached", &TriggerTISHlt2DiMuonDetached, &b_TriggerTISHlt2DiMuonDetached);
   fChain->SetBranchAddress("TriggerTPSHlt2DiMuonDetached", &TriggerTPSHlt2DiMuonDetached, &b_TriggerTPSHlt2DiMuonDetached);
   fChain->SetBranchAddress("TriggerTISHlt2TriMuonTau", &TriggerTISHlt2TriMuonTau, &b_TriggerTISHlt2TriMuonTau);
   fChain->SetBranchAddress("TriggerTPSHlt2TriMuonTau", &TriggerTPSHlt2TriMuonTau, &b_TriggerTPSHlt2TriMuonTau);
   fChain->SetBranchAddress("TriggerTISHlt2CharmSemilepD2HMuMu", &TriggerTISHlt2CharmSemilepD2HMuMu, &b_TriggerTISHlt2CharmSemilepD2HMuMu);
   fChain->SetBranchAddress("TriggerTPSHlt2CharmSemilepD2HMuMu", &TriggerTPSHlt2CharmSemilepD2HMuMu, &b_TriggerTPSHlt2CharmSemilepD2HMuMu);
   fChain->SetBranchAddress("TriggerTOSL0B1gas", &TriggerTOSL0B1gas, &b_TriggerTOSL0B1gas);
   fChain->SetBranchAddress("TriggerTOSL0B2gas", &TriggerTOSL0B2gas, &b_TriggerTOSL0B2gas);
   fChain->SetBranchAddress("TriggerTOSL0Calo", &TriggerTOSL0Calo, &b_TriggerTOSL0Calo);
   fChain->SetBranchAddress("TriggerTOSL0DiMuon", &TriggerTOSL0DiMuon, &b_TriggerTOSL0DiMuon);
   fChain->SetBranchAddress("TriggerTOSL0DiMuonlowMult", &TriggerTOSL0DiMuonlowMult, &b_TriggerTOSL0DiMuonlowMult);
   fChain->SetBranchAddress("TriggerTOSL0Electron", &TriggerTOSL0Electron, &b_TriggerTOSL0Electron);
   fChain->SetBranchAddress("TriggerTOSL0GlobalPi0", &TriggerTOSL0GlobalPi0, &b_TriggerTOSL0GlobalPi0);
   fChain->SetBranchAddress("TriggerTOSL0HCAL", &TriggerTOSL0HCAL, &b_TriggerTOSL0HCAL);
   fChain->SetBranchAddress("TriggerTOSL0Hadron", &TriggerTOSL0Hadron, &b_TriggerTOSL0Hadron);
   fChain->SetBranchAddress("TriggerTOSL0LocalPi0", &TriggerTOSL0LocalPi0, &b_TriggerTOSL0LocalPi0);
   fChain->SetBranchAddress("TriggerTOSL0MuonMinbias", &TriggerTOSL0MuonMinbias, &b_TriggerTOSL0MuonMinbias);
   fChain->SetBranchAddress("TriggerTOSL0Muon", &TriggerTOSL0Muon, &b_TriggerTOSL0Muon);
   fChain->SetBranchAddress("TriggerTOSL0MuonLowMult", &TriggerTOSL0MuonLowMult, &b_TriggerTOSL0MuonLowMult);
   fChain->SetBranchAddress("TriggerTOSL0PU", &TriggerTOSL0PU, &b_TriggerTOSL0PU);
   fChain->SetBranchAddress("TriggerTOSL0PU20", &TriggerTOSL0PU20, &b_TriggerTOSL0PU20);
   fChain->SetBranchAddress("TriggerTOSL0Photon", &TriggerTOSL0Photon, &b_TriggerTOSL0Photon);
   fChain->SetBranchAddress("TriggerTOSL0SPD", &TriggerTOSL0SPD, &b_TriggerTOSL0SPD);
   fChain->SetBranchAddress("TriggerTOSL0SPD40", &TriggerTOSL0SPD40, &b_TriggerTOSL0SPD40);
   fChain->SetBranchAddress("TriggerTOSHlt1DiMuonHighMassDecision", &TriggerTOSHlt1DiMuonHighMassDecision, &b_TriggerTOSHlt1DiMuonHighMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1DiMuonLowMassDecision", &TriggerTOSHlt1DiMuonLowMassDecision, &b_TriggerTOSHlt1DiMuonLowMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1SingleMuonNoIPDecision", &TriggerTOSHlt1SingleMuonNoIPDecision, &b_TriggerTOSHlt1SingleMuonNoIPDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1SingleMuonHighPTDecision", &TriggerTOSHlt1SingleMuonHighPTDecision, &b_TriggerTOSHlt1SingleMuonHighPTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1TrackAllL0Decision", &TriggerTOSHlt1TrackAllL0Decision, &b_TriggerTOSHlt1TrackAllL0Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1TrackMuonDecision", &TriggerTOSHlt1TrackMuonDecision, &b_TriggerTOSHlt1TrackMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1TrackPhotonDecision", &TriggerTOSHlt1TrackPhotonDecision, &b_TriggerTOSHlt1TrackPhotonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1LumiDecision", &TriggerTOSHlt1LumiDecision, &b_TriggerTOSHlt1LumiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1LumiMidBeamCrossingDecision", &TriggerTOSHlt1LumiMidBeamCrossingDecision, &b_TriggerTOSHlt1LumiMidBeamCrossingDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1MBNoBiasDecision", &TriggerTOSHlt1MBNoBiasDecision, &b_TriggerTOSHlt1MBNoBiasDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1L0AnyDecision", &TriggerTOSHlt1L0AnyDecision, &b_TriggerTOSHlt1L0AnyDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1L0AnyRateLimitedDecision", &TriggerTOSHlt1L0AnyRateLimitedDecision, &b_TriggerTOSHlt1L0AnyRateLimitedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1L0AnyNoSPDDecision", &TriggerTOSHlt1L0AnyNoSPDDecision, &b_TriggerTOSHlt1L0AnyNoSPDDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision", &TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision, &b_TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1NoPVPassThroughDecision", &TriggerTOSHlt1NoPVPassThroughDecision, &b_TriggerTOSHlt1NoPVPassThroughDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1DiProtonLowMultDecision", &TriggerTOSHlt1DiProtonLowMultDecision, &b_TriggerTOSHlt1DiProtonLowMultDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasNoBeamBeam1Decision", &TriggerTOSHlt1BeamGasNoBeamBeam1Decision, &b_TriggerTOSHlt1BeamGasNoBeamBeam1Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasNoBeamBeam2Decision", &TriggerTOSHlt1BeamGasNoBeamBeam2Decision, &b_TriggerTOSHlt1BeamGasNoBeamBeam2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasBeam1Decision", &TriggerTOSHlt1BeamGasBeam1Decision, &b_TriggerTOSHlt1BeamGasBeam1Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasBeam2Decision", &TriggerTOSHlt1BeamGasBeam2Decision, &b_TriggerTOSHlt1BeamGasBeam2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision", &TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision, &b_TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision", &TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision, &b_TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasCrossingForcedRecoDecision", &TriggerTOSHlt1BeamGasCrossingForcedRecoDecision, &b_TriggerTOSHlt1BeamGasCrossingForcedRecoDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1ODINTechnicalDecision", &TriggerTOSHlt1ODINTechnicalDecision, &b_TriggerTOSHlt1ODINTechnicalDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1Tell1ErrorDecision", &TriggerTOSHlt1Tell1ErrorDecision, &b_TriggerTOSHlt1Tell1ErrorDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasCrossingParasiticDecision", &TriggerTOSHlt1BeamGasCrossingParasiticDecision, &b_TriggerTOSHlt1BeamGasCrossingParasiticDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1ErrorEventDecision", &TriggerTOSHlt1ErrorEventDecision, &b_TriggerTOSHlt1ErrorEventDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1Global", &TriggerTOSHlt1Global, &b_TriggerTOSHlt1Global);
   fChain->SetBranchAddress("TriggerTOSHlt1MBMicroBiasVeloDecision", &TriggerTOSHlt1MBMicroBiasVeloDecision, &b_TriggerTOSHlt1MBMicroBiasVeloDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision", &TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision, &b_TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1MBMicroBiasTStationDecision", &TriggerTOSHlt1MBMicroBiasTStationDecision, &b_TriggerTOSHlt1MBMicroBiasTStationDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision", &TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision, &b_TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1DiProtonDecision", &TriggerTOSHlt1DiProtonDecision, &b_TriggerTOSHlt1DiProtonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1VeloClosingMicroBiasDecision", &TriggerTOSHlt1VeloClosingMicroBiasDecision, &b_TriggerTOSHlt1VeloClosingMicroBiasDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1SingleElectronNoIPDecision", &TriggerTOSHlt1SingleElectronNoIPDecision, &b_TriggerTOSHlt1SingleElectronNoIPDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1TrackForwardPassThroughDecision", &TriggerTOSHlt1TrackForwardPassThroughDecision, &b_TriggerTOSHlt1TrackForwardPassThroughDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1TrackForwardPassThroughLooseDecision", &TriggerTOSHlt1TrackForwardPassThroughLooseDecision, &b_TriggerTOSHlt1TrackForwardPassThroughLooseDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1CharmCalibrationNoBiasDecision", &TriggerTOSHlt1CharmCalibrationNoBiasDecision, &b_TriggerTOSHlt1CharmCalibrationNoBiasDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1L0HighSumETJetDecision", &TriggerTOSHlt1L0HighSumETJetDecision, &b_TriggerTOSHlt1L0HighSumETJetDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision", &TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision, &b_TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1BeamGasHighRhoVerticesDecision", &TriggerTOSHlt1BeamGasHighRhoVerticesDecision, &b_TriggerTOSHlt1BeamGasHighRhoVerticesDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1VertexDisplVertexDecision", &TriggerTOSHlt1VertexDisplVertexDecision, &b_TriggerTOSHlt1VertexDisplVertexDecision);
   fChain->SetBranchAddress("TriggerTOSHlt1TrackAllL0TightDecision", &TriggerTOSHlt1TrackAllL0TightDecision, &b_TriggerTOSHlt1TrackAllL0TightDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleElectronTFLowPtDecision", &TriggerTOSHlt2SingleElectronTFLowPtDecision, &b_TriggerTOSHlt2SingleElectronTFLowPtDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleElectronTFHighPtDecision", &TriggerTOSHlt2SingleElectronTFHighPtDecision, &b_TriggerTOSHlt2SingleElectronTFHighPtDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiElectronHighMassDecision", &TriggerTOSHlt2DiElectronHighMassDecision, &b_TriggerTOSHlt2DiElectronHighMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiElectronBDecision", &TriggerTOSHlt2DiElectronBDecision, &b_TriggerTOSHlt2DiElectronBDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Topo2BodySimpleDecision", &TriggerTOSHlt2Topo2BodySimpleDecision, &b_TriggerTOSHlt2Topo2BodySimpleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Topo3BodySimpleDecision", &TriggerTOSHlt2Topo3BodySimpleDecision, &b_TriggerTOSHlt2Topo3BodySimpleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Topo4BodySimpleDecision", &TriggerTOSHlt2Topo4BodySimpleDecision, &b_TriggerTOSHlt2Topo4BodySimpleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Topo2BodyBBDTDecision", &TriggerTOSHlt2Topo2BodyBBDTDecision, &b_TriggerTOSHlt2Topo2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Topo3BodyBBDTDecision", &TriggerTOSHlt2Topo3BodyBBDTDecision, &b_TriggerTOSHlt2Topo3BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Topo4BodyBBDTDecision", &TriggerTOSHlt2Topo4BodyBBDTDecision, &b_TriggerTOSHlt2Topo4BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoMu2BodyBBDTDecision", &TriggerTOSHlt2TopoMu2BodyBBDTDecision, &b_TriggerTOSHlt2TopoMu2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoMu3BodyBBDTDecision", &TriggerTOSHlt2TopoMu3BodyBBDTDecision, &b_TriggerTOSHlt2TopoMu3BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoMu4BodyBBDTDecision", &TriggerTOSHlt2TopoMu4BodyBBDTDecision, &b_TriggerTOSHlt2TopoMu4BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoE2BodyBBDTDecision", &TriggerTOSHlt2TopoE2BodyBBDTDecision, &b_TriggerTOSHlt2TopoE2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoE3BodyBBDTDecision", &TriggerTOSHlt2TopoE3BodyBBDTDecision, &b_TriggerTOSHlt2TopoE3BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoE4BodyBBDTDecision", &TriggerTOSHlt2TopoE4BodyBBDTDecision, &b_TriggerTOSHlt2TopoE4BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2IncPhiDecision", &TriggerTOSHlt2IncPhiDecision, &b_TriggerTOSHlt2IncPhiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2IncPhiSidebandsDecision", &TriggerTOSHlt2IncPhiSidebandsDecision, &b_TriggerTOSHlt2IncPhiSidebandsDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHKsLLDecision", &TriggerTOSHlt2CharmHadD02HHKsLLDecision, &b_TriggerTOSHlt2CharmHadD02HHKsLLDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Dst2PiD02PiPiDecision", &TriggerTOSHlt2Dst2PiD02PiPiDecision, &b_TriggerTOSHlt2Dst2PiD02PiPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Dst2PiD02MuMuDecision", &TriggerTOSHlt2Dst2PiD02MuMuDecision, &b_TriggerTOSHlt2Dst2PiD02MuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Dst2PiD02KMuDecision", &TriggerTOSHlt2Dst2PiD02KMuDecision, &b_TriggerTOSHlt2Dst2PiD02KMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Dst2PiD02KPiDecision", &TriggerTOSHlt2Dst2PiD02KPiDecision, &b_TriggerTOSHlt2Dst2PiD02KPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2PassThroughDecision", &TriggerTOSHlt2PassThroughDecision, &b_TriggerTOSHlt2PassThroughDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TransparentDecision", &TriggerTOSHlt2TransparentDecision, &b_TriggerTOSHlt2TransparentDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ForwardDecision", &TriggerTOSHlt2ForwardDecision, &b_TriggerTOSHlt2ForwardDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DebugEventDecision", &TriggerTOSHlt2DebugEventDecision, &b_TriggerTOSHlt2DebugEventDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02KKDecision", &TriggerTOSHlt2CharmHadD02KKDecision, &b_TriggerTOSHlt2CharmHadD02KKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02KKWideMassDecision", &TriggerTOSHlt2CharmHadD02KKWideMassDecision, &b_TriggerTOSHlt2CharmHadD02KKWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02KPiDecision", &TriggerTOSHlt2CharmHadD02KPiDecision, &b_TriggerTOSHlt2CharmHadD02KPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02KPiWideMassDecision", &TriggerTOSHlt2CharmHadD02KPiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02KPiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02PiPiDecision", &TriggerTOSHlt2CharmHadD02PiPiDecision, &b_TriggerTOSHlt2CharmHadD02PiPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02PiPiWideMassDecision", &TriggerTOSHlt2CharmHadD02PiPiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02PiPiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressJPsiDecision", &TriggerTOSHlt2ExpressJPsiDecision, &b_TriggerTOSHlt2ExpressJPsiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressJPsiTagProbeDecision", &TriggerTOSHlt2ExpressJPsiTagProbeDecision, &b_TriggerTOSHlt2ExpressJPsiTagProbeDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressLambdaDecision", &TriggerTOSHlt2ExpressLambdaDecision, &b_TriggerTOSHlt2ExpressLambdaDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressKSDecision", &TriggerTOSHlt2ExpressKSDecision, &b_TriggerTOSHlt2ExpressKSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressDs2PhiPiDecision", &TriggerTOSHlt2ExpressDs2PhiPiDecision, &b_TriggerTOSHlt2ExpressDs2PhiPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressBeamHaloDecision", &TriggerTOSHlt2ExpressBeamHaloDecision, &b_TriggerTOSHlt2ExpressBeamHaloDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressDStar2D0PiDecision", &TriggerTOSHlt2ExpressDStar2D0PiDecision, &b_TriggerTOSHlt2ExpressDStar2D0PiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressHLT1PhysicsDecision", &TriggerTOSHlt2ExpressHLT1PhysicsDecision, &b_TriggerTOSHlt2ExpressHLT1PhysicsDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Bs2PhiGammaDecision", &TriggerTOSHlt2Bs2PhiGammaDecision, &b_TriggerTOSHlt2Bs2PhiGammaDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Bs2PhiGammaWideBMassDecision", &TriggerTOSHlt2Bs2PhiGammaWideBMassDecision, &b_TriggerTOSHlt2Bs2PhiGammaWideBMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Bd2KstGammaDecision", &TriggerTOSHlt2Bd2KstGammaDecision, &b_TriggerTOSHlt2Bd2KstGammaDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Bd2KstGammaWideKMassDecision", &TriggerTOSHlt2Bd2KstGammaWideKMassDecision, &b_TriggerTOSHlt2Bd2KstGammaWideKMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Bd2KstGammaWideBMassDecision", &TriggerTOSHlt2Bd2KstGammaWideBMassDecision, &b_TriggerTOSHlt2Bd2KstGammaWideBMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0PiDecision", &TriggerTOSHlt2CharmHadD2KS0PiDecision, &b_TriggerTOSHlt2CharmHadD2KS0PiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0KDecision", &TriggerTOSHlt2CharmHadD2KS0KDecision, &b_TriggerTOSHlt2CharmHadD2KS0KDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmRareDecayD02MuMuDecision", &TriggerTOSHlt2CharmRareDecayD02MuMuDecision, &b_TriggerTOSHlt2CharmRareDecayD02MuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2B2HHDecision", &TriggerTOSHlt2B2HHDecision, &b_TriggerTOSHlt2B2HHDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2MuonFromHLT1Decision", &TriggerTOSHlt2MuonFromHLT1Decision, &b_TriggerTOSHlt2MuonFromHLT1Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleMuonDecision", &TriggerTOSHlt2SingleMuonDecision, &b_TriggerTOSHlt2SingleMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleMuonHighPTDecision", &TriggerTOSHlt2SingleMuonHighPTDecision, &b_TriggerTOSHlt2SingleMuonHighPTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleMuonLowPTDecision", &TriggerTOSHlt2SingleMuonLowPTDecision, &b_TriggerTOSHlt2SingleMuonLowPTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TFBc2JpsiMuXDecision", &TriggerTOSHlt2TFBc2JpsiMuXDecision, &b_TriggerTOSHlt2TFBc2JpsiMuXDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TFBc2JpsiMuXSignalDecision", &TriggerTOSHlt2TFBc2JpsiMuXSignalDecision, &b_TriggerTOSHlt2TFBc2JpsiMuXSignalDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesLowMassSingleDecision", &TriggerTOSHlt2DisplVerticesLowMassSingleDecision, &b_TriggerTOSHlt2DisplVerticesLowMassSingleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesHighMassSingleDecision", &TriggerTOSHlt2DisplVerticesHighMassSingleDecision, &b_TriggerTOSHlt2DisplVerticesHighMassSingleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesDoubleDecision", &TriggerTOSHlt2DisplVerticesDoubleDecision, &b_TriggerTOSHlt2DisplVerticesDoubleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSinglePostScaledDecision", &TriggerTOSHlt2DisplVerticesSinglePostScaledDecision, &b_TriggerTOSHlt2DisplVerticesSinglePostScaledDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesHighFDSingleDecision", &TriggerTOSHlt2DisplVerticesHighFDSingleDecision, &b_TriggerTOSHlt2DisplVerticesHighFDSingleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleDownDecision", &TriggerTOSHlt2DisplVerticesSingleDownDecision, &b_TriggerTOSHlt2DisplVerticesSingleDownDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2B2HHPi0_MergedDecision", &TriggerTOSHlt2B2HHPi0_MergedDecision, &b_TriggerTOSHlt2B2HHPi0_MergedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2HHHDecision", &TriggerTOSHlt2CharmHadD2HHHDecision, &b_TriggerTOSHlt2CharmHadD2HHHDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2HHHWideMassDecision", &TriggerTOSHlt2CharmHadD2HHHWideMassDecision, &b_TriggerTOSHlt2CharmHadD2HHHWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDecision", &TriggerTOSHlt2DiMuonDecision, &b_TriggerTOSHlt2DiMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonLowMassDecision", &TriggerTOSHlt2DiMuonLowMassDecision, &b_TriggerTOSHlt2DiMuonLowMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonJPsiDecision", &TriggerTOSHlt2DiMuonJPsiDecision, &b_TriggerTOSHlt2DiMuonJPsiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonJPsiHighPTDecision", &TriggerTOSHlt2DiMuonJPsiHighPTDecision, &b_TriggerTOSHlt2DiMuonJPsiHighPTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonPsi2SDecision", &TriggerTOSHlt2DiMuonPsi2SDecision, &b_TriggerTOSHlt2DiMuonPsi2SDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonBDecision", &TriggerTOSHlt2DiMuonBDecision, &b_TriggerTOSHlt2DiMuonBDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonZDecision", &TriggerTOSHlt2DiMuonZDecision, &b_TriggerTOSHlt2DiMuonZDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDY1Decision", &TriggerTOSHlt2DiMuonDY1Decision, &b_TriggerTOSHlt2DiMuonDY1Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDY2Decision", &TriggerTOSHlt2DiMuonDY2Decision, &b_TriggerTOSHlt2DiMuonDY2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDY3Decision", &TriggerTOSHlt2DiMuonDY3Decision, &b_TriggerTOSHlt2DiMuonDY3Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDY4Decision", &TriggerTOSHlt2DiMuonDY4Decision, &b_TriggerTOSHlt2DiMuonDY4Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDetachedDecision", &TriggerTOSHlt2DiMuonDetachedDecision, &b_TriggerTOSHlt2DiMuonDetachedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDetachedHeavyDecision", &TriggerTOSHlt2DiMuonDetachedHeavyDecision, &b_TriggerTOSHlt2DiMuonDetachedHeavyDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDetachedJPsiDecision", &TriggerTOSHlt2DiMuonDetachedJPsiDecision, &b_TriggerTOSHlt2DiMuonDetachedJPsiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonNoPVDecision", &TriggerTOSHlt2DiMuonNoPVDecision, &b_TriggerTOSHlt2DiMuonNoPVDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TriMuonDetachedDecision", &TriggerTOSHlt2TriMuonDetachedDecision, &b_TriggerTOSHlt2TriMuonDetachedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TriMuonTauDecision", &TriggerTOSHlt2TriMuonTauDecision, &b_TriggerTOSHlt2TriMuonTauDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDecision", &TriggerTOSHlt2CharmHadD02HHHHDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ErrorEventDecision", &TriggerTOSHlt2ErrorEventDecision, &b_TriggerTOSHlt2ErrorEventDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2Global", &TriggerTOSHlt2Global, &b_TriggerTOSHlt2Global);
   fChain->SetBranchAddress("TriggerTOSHlt2B2HHLTUnbiasedDecision", &TriggerTOSHlt2B2HHLTUnbiasedDecision, &b_TriggerTOSHlt2B2HHLTUnbiasedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision", &TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision, &b_TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision", &TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HH_D02KKDecision", &TriggerTOSHlt2CharmHadD02HH_D02KKDecision, &b_TriggerTOSHlt2CharmHadD02HH_D02KKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision", &TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HH_D02KPiDecision", &TriggerTOSHlt2CharmHadD02HH_D02KPiDecision, &b_TriggerTOSHlt2CharmHadD02HH_D02KPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision", &TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision", &TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision, &b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision", &TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision, &b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiProtonDecision", &TriggerTOSHlt2DiProtonDecision, &b_TriggerTOSHlt2DiProtonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiProtonTFDecision", &TriggerTOSHlt2DiProtonTFDecision, &b_TriggerTOSHlt2DiProtonTFDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiProtonLowMultDecision", &TriggerTOSHlt2DiProtonLowMultDecision, &b_TriggerTOSHlt2DiProtonLowMultDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiProtonLowMultTFDecision", &TriggerTOSHlt2DiProtonLowMultTFDecision, &b_TriggerTOSHlt2DiProtonLowMultTFDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision", &TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision, &b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision", &TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision, &b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision", &TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision, &b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision", &TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision, &b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD2HMuMuDecision", &TriggerTOSHlt2CharmSemilepD2HMuMuDecision, &b_TriggerTOSHlt2CharmSemilepD2HMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision", &TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision, &b_TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HHMuMuDecision", &TriggerTOSHlt2CharmSemilepD02HHMuMuDecision, &b_TriggerTOSHlt2CharmSemilepD02HHMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision", &TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision, &b_TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2diPhotonDiMuonDecision", &TriggerTOSHlt2diPhotonDiMuonDecision, &b_TriggerTOSHlt2diPhotonDiMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultMuonDecision", &TriggerTOSHlt2LowMultMuonDecision, &b_TriggerTOSHlt2LowMultMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultHadronDecision", &TriggerTOSHlt2LowMultHadronDecision, &b_TriggerTOSHlt2LowMultHadronDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultPhotonDecision", &TriggerTOSHlt2LowMultPhotonDecision, &b_TriggerTOSHlt2LowMultPhotonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultElectronDecision", &TriggerTOSHlt2LowMultElectronDecision, &b_TriggerTOSHlt2LowMultElectronDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleTFElectronDecision", &TriggerTOSHlt2SingleTFElectronDecision, &b_TriggerTOSHlt2SingleTFElectronDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleTFVHighPtElectronDecision", &TriggerTOSHlt2SingleTFVHighPtElectronDecision, &b_TriggerTOSHlt2SingleTFVHighPtElectronDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision", &TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision, &b_TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2KPPiDecision", &TriggerTOSHlt2CharmHadLambdaC2KPPiDecision, &b_TriggerTOSHlt2CharmHadLambdaC2KPPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2SingleMuonVHighPTDecision", &TriggerTOSHlt2SingleMuonVHighPTDecision, &b_TriggerTOSHlt2SingleMuonVHighPTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision", &TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision, &b_TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadMinBiasLambdaC2KPPiDecision", &TriggerTOSHlt2CharmHadMinBiasLambdaC2KPPiDecision, &b_TriggerTOSHlt2CharmHadMinBiasLambdaC2KPPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadMinBiasD02KPiDecision", &TriggerTOSHlt2CharmHadMinBiasD02KPiDecision, &b_TriggerTOSHlt2CharmHadMinBiasD02KPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadMinBiasD02KKDecision", &TriggerTOSHlt2CharmHadMinBiasD02KKDecision, &b_TriggerTOSHlt2CharmHadMinBiasD02KKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadMinBiasDplus2hhhDecision", &TriggerTOSHlt2CharmHadMinBiasDplus2hhhDecision, &b_TriggerTOSHlt2CharmHadMinBiasDplus2hhhDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadMinBiasLambdaC2LambdaPiDecision", &TriggerTOSHlt2CharmHadMinBiasLambdaC2LambdaPiDecision, &b_TriggerTOSHlt2CharmHadMinBiasLambdaC2LambdaPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleDecision", &TriggerTOSHlt2DisplVerticesSingleDecision, &b_TriggerTOSHlt2DisplVerticesSingleDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesDoublePostScaledDecision", &TriggerTOSHlt2DisplVerticesDoublePostScaledDecision, &b_TriggerTOSHlt2DisplVerticesDoublePostScaledDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision", &TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision, &b_TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision", &TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision, &b_TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision", &TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision, &b_TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2RadiativeTopoTrackTOSDecision", &TriggerTOSHlt2RadiativeTopoTrackTOSDecision, &b_TriggerTOSHlt2RadiativeTopoTrackTOSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2RadiativeTopoPhotonL0Decision", &TriggerTOSHlt2RadiativeTopoPhotonL0Decision, &b_TriggerTOSHlt2RadiativeTopoPhotonL0Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonPsi2SHighPTDecision", &TriggerTOSHlt2DiMuonPsi2SHighPTDecision, &b_TriggerTOSHlt2DiMuonPsi2SHighPTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DoubleDiMuonDecision", &TriggerTOSHlt2DoubleDiMuonDecision, &b_TriggerTOSHlt2DoubleDiMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonAndMuonDecision", &TriggerTOSHlt2DiMuonAndMuonDecision, &b_TriggerTOSHlt2DiMuonAndMuonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonAndGammaDecision", &TriggerTOSHlt2DiMuonAndGammaDecision, &b_TriggerTOSHlt2DiMuonAndGammaDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonAndD0Decision", &TriggerTOSHlt2DiMuonAndD0Decision, &b_TriggerTOSHlt2DiMuonAndD0Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonAndDpDecision", &TriggerTOSHlt2DiMuonAndDpDecision, &b_TriggerTOSHlt2DiMuonAndDpDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonAndDsDecision", &TriggerTOSHlt2DiMuonAndDsDecision, &b_TriggerTOSHlt2DiMuonAndDsDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonAndLcDecision", &TriggerTOSHlt2DiMuonAndLcDecision, &b_TriggerTOSHlt2DiMuonAndLcDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision", &TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision, &b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision", &TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision, &b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision", &TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision, &b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision", &TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision, &b_TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoRad2BodyBBDTDecision", &TriggerTOSHlt2TopoRad2BodyBBDTDecision, &b_TriggerTOSHlt2TopoRad2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision", &TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision, &b_TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LumiDecision", &TriggerTOSHlt2LumiDecision, &b_TriggerTOSHlt2LumiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultHadron_nofilterDecision", &TriggerTOSHlt2LowMultHadron_nofilterDecision, &b_TriggerTOSHlt2LowMultHadron_nofilterDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultElectron_nofilterDecision", &TriggerTOSHlt2LowMultElectron_nofilterDecision, &b_TriggerTOSHlt2LowMultElectron_nofilterDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHKsDDDecision", &TriggerTOSHlt2CharmHadD02HHKsDDDecision, &b_TriggerTOSHlt2CharmHadD02HHKsDDDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0KS0Decision", &TriggerTOSHlt2CharmHadD2KS0KS0Decision, &b_TriggerTOSHlt2CharmHadD2KS0KS0Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision", &TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision, &b_TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2ExpressD02KPiDecision", &TriggerTOSHlt2ExpressD02KPiDecision, &b_TriggerTOSHlt2ExpressD02KPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision", &TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision, &b_TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2KPKDecision", &TriggerTOSHlt2CharmHadLambdaC2KPKDecision, &b_TriggerTOSHlt2CharmHadLambdaC2KPKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision", &TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision, &b_TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision", &TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision, &b_TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision", &TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision, &b_TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2PiPKDecision", &TriggerTOSHlt2CharmHadLambdaC2PiPKDecision, &b_TriggerTOSHlt2CharmHadLambdaC2PiPKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision", &TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision, &b_TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision", &TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision, &b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision", &TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision, &b_TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiPhiDecision", &TriggerTOSHlt2DiPhiDecision, &b_TriggerTOSHlt2DiPhiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision", &TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision, &b_TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision", &TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision, &b_TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision", &TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision, &b_TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision", &TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision, &b_TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision", &TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision, &b_TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision", &TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision, &b_TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision", &TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision, &b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision", &TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision, &b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision", &TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision, &b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision", &TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision, &b_TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2RadiativeTopoTrackDecision", &TriggerTOSHlt2RadiativeTopoTrackDecision, &b_TriggerTOSHlt2RadiativeTopoTrackDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2RadiativeTopoPhotonDecision", &TriggerTOSHlt2RadiativeTopoPhotonDecision, &b_TriggerTOSHlt2RadiativeTopoPhotonDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision", &TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision", &TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision", &TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision, &b_TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02KKMuMuDecision", &TriggerTOSHlt2CharmSemilepD02KKMuMuDecision, &b_TriggerTOSHlt2CharmSemilepD02KKMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision", &TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision, &b_TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_4piDecision", &TriggerTOSHlt2CharmHadD02HHHH_4piDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_4piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_K3piDecision", &TriggerTOSHlt2CharmHadD02HHHH_K3piDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_K3piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision", &TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision", &TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision", &TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision", &TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision", &TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision, &b_TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision", &TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DiMuonDetachedPsi2SDecision", &TriggerTOSHlt2DiMuonDetachedPsi2SDecision, &b_TriggerTOSHlt2DiMuonDetachedPsi2SDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision", &TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision, &b_TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision", &TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision, &b_TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultD2KPiDecision", &TriggerTOSHlt2LowMultD2KPiDecision, &b_TriggerTOSHlt2LowMultD2KPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultD2KPiPiDecision", &TriggerTOSHlt2LowMultD2KPiPiDecision, &b_TriggerTOSHlt2LowMultD2KPiPiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultD2K3PiDecision", &TriggerTOSHlt2LowMultD2K3PiDecision, &b_TriggerTOSHlt2LowMultD2K3PiDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultChiC2HHDecision", &TriggerTOSHlt2LowMultChiC2HHDecision, &b_TriggerTOSHlt2LowMultChiC2HHDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultChiC2HHHHDecision", &TriggerTOSHlt2LowMultChiC2HHHHDecision, &b_TriggerTOSHlt2LowMultChiC2HHHHDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultD2KPiWSDecision", &TriggerTOSHlt2LowMultD2KPiWSDecision, &b_TriggerTOSHlt2LowMultD2KPiWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultD2KPiPiWSDecision", &TriggerTOSHlt2LowMultD2KPiPiWSDecision, &b_TriggerTOSHlt2LowMultD2KPiPiWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultD2K3PiWSDecision", &TriggerTOSHlt2LowMultD2K3PiWSDecision, &b_TriggerTOSHlt2LowMultD2K3PiWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultChiC2HHWSDecision", &TriggerTOSHlt2LowMultChiC2HHWSDecision, &b_TriggerTOSHlt2LowMultChiC2HHWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultChiC2HHHHWSDecision", &TriggerTOSHlt2LowMultChiC2HHHHWSDecision, &b_TriggerTOSHlt2LowMultChiC2HHHHWSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2LowMultDDIncDecision", &TriggerTOSHlt2LowMultDDIncDecision, &b_TriggerTOSHlt2LowMultDDIncDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleLoosePSDecision", &TriggerTOSHlt2DisplVerticesSingleLoosePSDecision, &b_TriggerTOSHlt2DisplVerticesSingleLoosePSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleHighFDDecision", &TriggerTOSHlt2DisplVerticesSingleHighFDDecision, &b_TriggerTOSHlt2DisplVerticesSingleHighFDDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision", &TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision, &b_TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSingleHighMassDecision", &TriggerTOSHlt2DisplVerticesSingleHighMassDecision, &b_TriggerTOSHlt2DisplVerticesSingleHighMassDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesSinglePSDecision", &TriggerTOSHlt2DisplVerticesSinglePSDecision, &b_TriggerTOSHlt2DisplVerticesSinglePSDecision);
   fChain->SetBranchAddress("TriggerTOSHlt2DisplVerticesDoublePSDecision", &TriggerTOSHlt2DisplVerticesDoublePSDecision, &b_TriggerTOSHlt2DisplVerticesDoublePSDecision);
   fChain->SetBranchAddress("TriggerDecL0B1gas", &TriggerDecL0B1gas, &b_TriggerDecL0B1gas);
   fChain->SetBranchAddress("TriggerDecL0B2gas", &TriggerDecL0B2gas, &b_TriggerDecL0B2gas);
   fChain->SetBranchAddress("TriggerDecL0Calo", &TriggerDecL0Calo, &b_TriggerDecL0Calo);
   fChain->SetBranchAddress("TriggerDecL0DiMuon", &TriggerDecL0DiMuon, &b_TriggerDecL0DiMuon);
   fChain->SetBranchAddress("TriggerDecL0DiMuonlowMult", &TriggerDecL0DiMuonlowMult, &b_TriggerDecL0DiMuonlowMult);
   fChain->SetBranchAddress("TriggerDecL0Electron", &TriggerDecL0Electron, &b_TriggerDecL0Electron);
   fChain->SetBranchAddress("TriggerDecL0GlobalPi0", &TriggerDecL0GlobalPi0, &b_TriggerDecL0GlobalPi0);
   fChain->SetBranchAddress("TriggerDecL0HCAL", &TriggerDecL0HCAL, &b_TriggerDecL0HCAL);
   fChain->SetBranchAddress("TriggerDecL0Hadron", &TriggerDecL0Hadron, &b_TriggerDecL0Hadron);
   fChain->SetBranchAddress("TriggerDecL0LocalPi0", &TriggerDecL0LocalPi0, &b_TriggerDecL0LocalPi0);
   fChain->SetBranchAddress("TriggerDecL0MuonMinbias", &TriggerDecL0MuonMinbias, &b_TriggerDecL0MuonMinbias);
   fChain->SetBranchAddress("TriggerDecL0Muon", &TriggerDecL0Muon, &b_TriggerDecL0Muon);
   fChain->SetBranchAddress("TriggerDecL0MuonLowMult", &TriggerDecL0MuonLowMult, &b_TriggerDecL0MuonLowMult);
   fChain->SetBranchAddress("TriggerDecL0PU", &TriggerDecL0PU, &b_TriggerDecL0PU);
   fChain->SetBranchAddress("TriggerDecL0PU20", &TriggerDecL0PU20, &b_TriggerDecL0PU20);
   fChain->SetBranchAddress("TriggerDecL0Photon", &TriggerDecL0Photon, &b_TriggerDecL0Photon);
   fChain->SetBranchAddress("TriggerDecL0SPD", &TriggerDecL0SPD, &b_TriggerDecL0SPD);
   fChain->SetBranchAddress("TriggerDecL0SPD40", &TriggerDecL0SPD40, &b_TriggerDecL0SPD40);
   fChain->SetBranchAddress("TriggerDecHlt1DiMuonHighMassDecision", &TriggerDecHlt1DiMuonHighMassDecision, &b_TriggerDecHlt1DiMuonHighMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt1DiMuonLowMassDecision", &TriggerDecHlt1DiMuonLowMassDecision, &b_TriggerDecHlt1DiMuonLowMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt1SingleMuonNoIPDecision", &TriggerDecHlt1SingleMuonNoIPDecision, &b_TriggerDecHlt1SingleMuonNoIPDecision);
   fChain->SetBranchAddress("TriggerDecHlt1SingleMuonHighPTDecision", &TriggerDecHlt1SingleMuonHighPTDecision, &b_TriggerDecHlt1SingleMuonHighPTDecision);
   fChain->SetBranchAddress("TriggerDecHlt1TrackAllL0Decision", &TriggerDecHlt1TrackAllL0Decision, &b_TriggerDecHlt1TrackAllL0Decision);
   fChain->SetBranchAddress("TriggerDecHlt1TrackMuonDecision", &TriggerDecHlt1TrackMuonDecision, &b_TriggerDecHlt1TrackMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt1TrackPhotonDecision", &TriggerDecHlt1TrackPhotonDecision, &b_TriggerDecHlt1TrackPhotonDecision);
   fChain->SetBranchAddress("TriggerDecHlt1LumiDecision", &TriggerDecHlt1LumiDecision, &b_TriggerDecHlt1LumiDecision);
   fChain->SetBranchAddress("TriggerDecHlt1LumiMidBeamCrossingDecision", &TriggerDecHlt1LumiMidBeamCrossingDecision, &b_TriggerDecHlt1LumiMidBeamCrossingDecision);
   fChain->SetBranchAddress("TriggerDecHlt1MBNoBiasDecision", &TriggerDecHlt1MBNoBiasDecision, &b_TriggerDecHlt1MBNoBiasDecision);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyDecision", &TriggerDecHlt1L0AnyDecision, &b_TriggerDecHlt1L0AnyDecision);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyRateLimitedDecision", &TriggerDecHlt1L0AnyRateLimitedDecision, &b_TriggerDecHlt1L0AnyRateLimitedDecision);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyNoSPDDecision", &TriggerDecHlt1L0AnyNoSPDDecision, &b_TriggerDecHlt1L0AnyNoSPDDecision);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyNoSPDRateLimitedDecision", &TriggerDecHlt1L0AnyNoSPDRateLimitedDecision, &b_TriggerDecHlt1L0AnyNoSPDRateLimitedDecision);
   fChain->SetBranchAddress("TriggerDecHlt1NoPVPassThroughDecision", &TriggerDecHlt1NoPVPassThroughDecision, &b_TriggerDecHlt1NoPVPassThroughDecision);
   fChain->SetBranchAddress("TriggerDecHlt1DiProtonLowMultDecision", &TriggerDecHlt1DiProtonLowMultDecision, &b_TriggerDecHlt1DiProtonLowMultDecision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasNoBeamBeam1Decision", &TriggerDecHlt1BeamGasNoBeamBeam1Decision, &b_TriggerDecHlt1BeamGasNoBeamBeam1Decision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasNoBeamBeam2Decision", &TriggerDecHlt1BeamGasNoBeamBeam2Decision, &b_TriggerDecHlt1BeamGasNoBeamBeam2Decision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasBeam1Decision", &TriggerDecHlt1BeamGasBeam1Decision, &b_TriggerDecHlt1BeamGasBeam1Decision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasBeam2Decision", &TriggerDecHlt1BeamGasBeam2Decision, &b_TriggerDecHlt1BeamGasBeam2Decision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision", &TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision, &b_TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision", &TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision, &b_TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingForcedRecoDecision", &TriggerDecHlt1BeamGasCrossingForcedRecoDecision, &b_TriggerDecHlt1BeamGasCrossingForcedRecoDecision);
   fChain->SetBranchAddress("TriggerDecHlt1ODINTechnicalDecision", &TriggerDecHlt1ODINTechnicalDecision, &b_TriggerDecHlt1ODINTechnicalDecision);
   fChain->SetBranchAddress("TriggerDecHlt1Tell1ErrorDecision", &TriggerDecHlt1Tell1ErrorDecision, &b_TriggerDecHlt1Tell1ErrorDecision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingParasiticDecision", &TriggerDecHlt1BeamGasCrossingParasiticDecision, &b_TriggerDecHlt1BeamGasCrossingParasiticDecision);
   fChain->SetBranchAddress("TriggerDecHlt1ErrorEventDecision", &TriggerDecHlt1ErrorEventDecision, &b_TriggerDecHlt1ErrorEventDecision);
   fChain->SetBranchAddress("TriggerDecHlt1Global", &TriggerDecHlt1Global, &b_TriggerDecHlt1Global);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasVeloDecision", &TriggerDecHlt1MBMicroBiasVeloDecision, &b_TriggerDecHlt1MBMicroBiasVeloDecision);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision", &TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision, &b_TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasTStationDecision", &TriggerDecHlt1MBMicroBiasTStationDecision, &b_TriggerDecHlt1MBMicroBiasTStationDecision);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision", &TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision, &b_TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision);
   fChain->SetBranchAddress("TriggerDecHlt1DiProtonDecision", &TriggerDecHlt1DiProtonDecision, &b_TriggerDecHlt1DiProtonDecision);
   fChain->SetBranchAddress("TriggerDecHlt1VeloClosingMicroBiasDecision", &TriggerDecHlt1VeloClosingMicroBiasDecision, &b_TriggerDecHlt1VeloClosingMicroBiasDecision);
   fChain->SetBranchAddress("TriggerDecHlt1SingleElectronNoIPDecision", &TriggerDecHlt1SingleElectronNoIPDecision, &b_TriggerDecHlt1SingleElectronNoIPDecision);
   fChain->SetBranchAddress("TriggerDecHlt1TrackForwardPassThroughDecision", &TriggerDecHlt1TrackForwardPassThroughDecision, &b_TriggerDecHlt1TrackForwardPassThroughDecision);
   fChain->SetBranchAddress("TriggerDecHlt1TrackForwardPassThroughLooseDecision", &TriggerDecHlt1TrackForwardPassThroughLooseDecision, &b_TriggerDecHlt1TrackForwardPassThroughLooseDecision);
   fChain->SetBranchAddress("TriggerDecHlt1CharmCalibrationNoBiasDecision", &TriggerDecHlt1CharmCalibrationNoBiasDecision, &b_TriggerDecHlt1CharmCalibrationNoBiasDecision);
   fChain->SetBranchAddress("TriggerDecHlt1L0HighSumETJetDecision", &TriggerDecHlt1L0HighSumETJetDecision, &b_TriggerDecHlt1L0HighSumETJetDecision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision", &TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision, &b_TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasHighRhoVerticesDecision", &TriggerDecHlt1BeamGasHighRhoVerticesDecision, &b_TriggerDecHlt1BeamGasHighRhoVerticesDecision);
   fChain->SetBranchAddress("TriggerDecHlt1VertexDisplVertexDecision", &TriggerDecHlt1VertexDisplVertexDecision, &b_TriggerDecHlt1VertexDisplVertexDecision);
   fChain->SetBranchAddress("TriggerDecHlt1TrackAllL0TightDecision", &TriggerDecHlt1TrackAllL0TightDecision, &b_TriggerDecHlt1TrackAllL0TightDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleElectronTFLowPtDecision", &TriggerDecHlt2SingleElectronTFLowPtDecision, &b_TriggerDecHlt2SingleElectronTFLowPtDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleElectronTFHighPtDecision", &TriggerDecHlt2SingleElectronTFHighPtDecision, &b_TriggerDecHlt2SingleElectronTFHighPtDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiElectronHighMassDecision", &TriggerDecHlt2DiElectronHighMassDecision, &b_TriggerDecHlt2DiElectronHighMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiElectronBDecision", &TriggerDecHlt2DiElectronBDecision, &b_TriggerDecHlt2DiElectronBDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Topo2BodySimpleDecision", &TriggerDecHlt2Topo2BodySimpleDecision, &b_TriggerDecHlt2Topo2BodySimpleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Topo3BodySimpleDecision", &TriggerDecHlt2Topo3BodySimpleDecision, &b_TriggerDecHlt2Topo3BodySimpleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Topo4BodySimpleDecision", &TriggerDecHlt2Topo4BodySimpleDecision, &b_TriggerDecHlt2Topo4BodySimpleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Topo2BodyBBDTDecision", &TriggerDecHlt2Topo2BodyBBDTDecision, &b_TriggerDecHlt2Topo2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Topo3BodyBBDTDecision", &TriggerDecHlt2Topo3BodyBBDTDecision, &b_TriggerDecHlt2Topo3BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Topo4BodyBBDTDecision", &TriggerDecHlt2Topo4BodyBBDTDecision, &b_TriggerDecHlt2Topo4BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoMu2BodyBBDTDecision", &TriggerDecHlt2TopoMu2BodyBBDTDecision, &b_TriggerDecHlt2TopoMu2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoMu3BodyBBDTDecision", &TriggerDecHlt2TopoMu3BodyBBDTDecision, &b_TriggerDecHlt2TopoMu3BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoMu4BodyBBDTDecision", &TriggerDecHlt2TopoMu4BodyBBDTDecision, &b_TriggerDecHlt2TopoMu4BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoE2BodyBBDTDecision", &TriggerDecHlt2TopoE2BodyBBDTDecision, &b_TriggerDecHlt2TopoE2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoE3BodyBBDTDecision", &TriggerDecHlt2TopoE3BodyBBDTDecision, &b_TriggerDecHlt2TopoE3BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoE4BodyBBDTDecision", &TriggerDecHlt2TopoE4BodyBBDTDecision, &b_TriggerDecHlt2TopoE4BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2IncPhiDecision", &TriggerDecHlt2IncPhiDecision, &b_TriggerDecHlt2IncPhiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2IncPhiSidebandsDecision", &TriggerDecHlt2IncPhiSidebandsDecision, &b_TriggerDecHlt2IncPhiSidebandsDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHKsLLDecision", &TriggerDecHlt2CharmHadD02HHKsLLDecision, &b_TriggerDecHlt2CharmHadD02HHKsLLDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02PiPiDecision", &TriggerDecHlt2Dst2PiD02PiPiDecision, &b_TriggerDecHlt2Dst2PiD02PiPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02MuMuDecision", &TriggerDecHlt2Dst2PiD02MuMuDecision, &b_TriggerDecHlt2Dst2PiD02MuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02KMuDecision", &TriggerDecHlt2Dst2PiD02KMuDecision, &b_TriggerDecHlt2Dst2PiD02KMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02KPiDecision", &TriggerDecHlt2Dst2PiD02KPiDecision, &b_TriggerDecHlt2Dst2PiD02KPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2PassThroughDecision", &TriggerDecHlt2PassThroughDecision, &b_TriggerDecHlt2PassThroughDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TransparentDecision", &TriggerDecHlt2TransparentDecision, &b_TriggerDecHlt2TransparentDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ForwardDecision", &TriggerDecHlt2ForwardDecision, &b_TriggerDecHlt2ForwardDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DebugEventDecision", &TriggerDecHlt2DebugEventDecision, &b_TriggerDecHlt2DebugEventDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KKDecision", &TriggerDecHlt2CharmHadD02KKDecision, &b_TriggerDecHlt2CharmHadD02KKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KKWideMassDecision", &TriggerDecHlt2CharmHadD02KKWideMassDecision, &b_TriggerDecHlt2CharmHadD02KKWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KPiDecision", &TriggerDecHlt2CharmHadD02KPiDecision, &b_TriggerDecHlt2CharmHadD02KPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KPiWideMassDecision", &TriggerDecHlt2CharmHadD02KPiWideMassDecision, &b_TriggerDecHlt2CharmHadD02KPiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02PiPiDecision", &TriggerDecHlt2CharmHadD02PiPiDecision, &b_TriggerDecHlt2CharmHadD02PiPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02PiPiWideMassDecision", &TriggerDecHlt2CharmHadD02PiPiWideMassDecision, &b_TriggerDecHlt2CharmHadD02PiPiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressJPsiDecision", &TriggerDecHlt2ExpressJPsiDecision, &b_TriggerDecHlt2ExpressJPsiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressJPsiTagProbeDecision", &TriggerDecHlt2ExpressJPsiTagProbeDecision, &b_TriggerDecHlt2ExpressJPsiTagProbeDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressLambdaDecision", &TriggerDecHlt2ExpressLambdaDecision, &b_TriggerDecHlt2ExpressLambdaDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressKSDecision", &TriggerDecHlt2ExpressKSDecision, &b_TriggerDecHlt2ExpressKSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressDs2PhiPiDecision", &TriggerDecHlt2ExpressDs2PhiPiDecision, &b_TriggerDecHlt2ExpressDs2PhiPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressBeamHaloDecision", &TriggerDecHlt2ExpressBeamHaloDecision, &b_TriggerDecHlt2ExpressBeamHaloDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressDStar2D0PiDecision", &TriggerDecHlt2ExpressDStar2D0PiDecision, &b_TriggerDecHlt2ExpressDStar2D0PiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressHLT1PhysicsDecision", &TriggerDecHlt2ExpressHLT1PhysicsDecision, &b_TriggerDecHlt2ExpressHLT1PhysicsDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Bs2PhiGammaDecision", &TriggerDecHlt2Bs2PhiGammaDecision, &b_TriggerDecHlt2Bs2PhiGammaDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Bs2PhiGammaWideBMassDecision", &TriggerDecHlt2Bs2PhiGammaWideBMassDecision, &b_TriggerDecHlt2Bs2PhiGammaWideBMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Bd2KstGammaDecision", &TriggerDecHlt2Bd2KstGammaDecision, &b_TriggerDecHlt2Bd2KstGammaDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Bd2KstGammaWideKMassDecision", &TriggerDecHlt2Bd2KstGammaWideKMassDecision, &b_TriggerDecHlt2Bd2KstGammaWideKMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Bd2KstGammaWideBMassDecision", &TriggerDecHlt2Bd2KstGammaWideBMassDecision, &b_TriggerDecHlt2Bd2KstGammaWideBMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0PiDecision", &TriggerDecHlt2CharmHadD2KS0PiDecision, &b_TriggerDecHlt2CharmHadD2KS0PiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0KDecision", &TriggerDecHlt2CharmHadD2KS0KDecision, &b_TriggerDecHlt2CharmHadD2KS0KDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmRareDecayD02MuMuDecision", &TriggerDecHlt2CharmRareDecayD02MuMuDecision, &b_TriggerDecHlt2CharmRareDecayD02MuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2B2HHDecision", &TriggerDecHlt2B2HHDecision, &b_TriggerDecHlt2B2HHDecision);
   fChain->SetBranchAddress("TriggerDecHlt2MuonFromHLT1Decision", &TriggerDecHlt2MuonFromHLT1Decision, &b_TriggerDecHlt2MuonFromHLT1Decision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuonDecision", &TriggerDecHlt2SingleMuonDecision, &b_TriggerDecHlt2SingleMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuonHighPTDecision", &TriggerDecHlt2SingleMuonHighPTDecision, &b_TriggerDecHlt2SingleMuonHighPTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuonLowPTDecision", &TriggerDecHlt2SingleMuonLowPTDecision, &b_TriggerDecHlt2SingleMuonLowPTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TFBc2JpsiMuXDecision", &TriggerDecHlt2TFBc2JpsiMuXDecision, &b_TriggerDecHlt2TFBc2JpsiMuXDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TFBc2JpsiMuXSignalDecision", &TriggerDecHlt2TFBc2JpsiMuXSignalDecision, &b_TriggerDecHlt2TFBc2JpsiMuXSignalDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesLowMassSingleDecision", &TriggerDecHlt2DisplVerticesLowMassSingleDecision, &b_TriggerDecHlt2DisplVerticesLowMassSingleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesHighMassSingleDecision", &TriggerDecHlt2DisplVerticesHighMassSingleDecision, &b_TriggerDecHlt2DisplVerticesHighMassSingleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesDoubleDecision", &TriggerDecHlt2DisplVerticesDoubleDecision, &b_TriggerDecHlt2DisplVerticesDoubleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSinglePostScaledDecision", &TriggerDecHlt2DisplVerticesSinglePostScaledDecision, &b_TriggerDecHlt2DisplVerticesSinglePostScaledDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesHighFDSingleDecision", &TriggerDecHlt2DisplVerticesHighFDSingleDecision, &b_TriggerDecHlt2DisplVerticesHighFDSingleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleDownDecision", &TriggerDecHlt2DisplVerticesSingleDownDecision, &b_TriggerDecHlt2DisplVerticesSingleDownDecision);
   fChain->SetBranchAddress("TriggerDecHlt2B2HHPi0_MergedDecision", &TriggerDecHlt2B2HHPi0_MergedDecision, &b_TriggerDecHlt2B2HHPi0_MergedDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2HHHDecision", &TriggerDecHlt2CharmHadD2HHHDecision, &b_TriggerDecHlt2CharmHadD2HHHDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2HHHWideMassDecision", &TriggerDecHlt2CharmHadD2HHHWideMassDecision, &b_TriggerDecHlt2CharmHadD2HHHWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDecision", &TriggerDecHlt2DiMuonDecision, &b_TriggerDecHlt2DiMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonLowMassDecision", &TriggerDecHlt2DiMuonLowMassDecision, &b_TriggerDecHlt2DiMuonLowMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonJPsiDecision", &TriggerDecHlt2DiMuonJPsiDecision, &b_TriggerDecHlt2DiMuonJPsiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonJPsiHighPTDecision", &TriggerDecHlt2DiMuonJPsiHighPTDecision, &b_TriggerDecHlt2DiMuonJPsiHighPTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonPsi2SDecision", &TriggerDecHlt2DiMuonPsi2SDecision, &b_TriggerDecHlt2DiMuonPsi2SDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonBDecision", &TriggerDecHlt2DiMuonBDecision, &b_TriggerDecHlt2DiMuonBDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonZDecision", &TriggerDecHlt2DiMuonZDecision, &b_TriggerDecHlt2DiMuonZDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY1Decision", &TriggerDecHlt2DiMuonDY1Decision, &b_TriggerDecHlt2DiMuonDY1Decision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY2Decision", &TriggerDecHlt2DiMuonDY2Decision, &b_TriggerDecHlt2DiMuonDY2Decision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY3Decision", &TriggerDecHlt2DiMuonDY3Decision, &b_TriggerDecHlt2DiMuonDY3Decision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY4Decision", &TriggerDecHlt2DiMuonDY4Decision, &b_TriggerDecHlt2DiMuonDY4Decision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetachedDecision", &TriggerDecHlt2DiMuonDetachedDecision, &b_TriggerDecHlt2DiMuonDetachedDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetachedHeavyDecision", &TriggerDecHlt2DiMuonDetachedHeavyDecision, &b_TriggerDecHlt2DiMuonDetachedHeavyDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetachedJPsiDecision", &TriggerDecHlt2DiMuonDetachedJPsiDecision, &b_TriggerDecHlt2DiMuonDetachedJPsiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonNoPVDecision", &TriggerDecHlt2DiMuonNoPVDecision, &b_TriggerDecHlt2DiMuonNoPVDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TriMuonDetachedDecision", &TriggerDecHlt2TriMuonDetachedDecision, &b_TriggerDecHlt2TriMuonDetachedDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TriMuonTauDecision", &TriggerDecHlt2TriMuonTauDecision, &b_TriggerDecHlt2TriMuonTauDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDecision", &TriggerDecHlt2CharmHadD02HHHHDecision, &b_TriggerDecHlt2CharmHadD02HHHHDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ErrorEventDecision", &TriggerDecHlt2ErrorEventDecision, &b_TriggerDecHlt2ErrorEventDecision);
   fChain->SetBranchAddress("TriggerDecHlt2Global", &TriggerDecHlt2Global, &b_TriggerDecHlt2Global);
   fChain->SetBranchAddress("TriggerDecHlt2B2HHLTUnbiasedDecision", &TriggerDecHlt2B2HHLTUnbiasedDecision, &b_TriggerDecHlt2B2HHLTUnbiasedDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02PiPiDecision", &TriggerDecHlt2CharmHadD02HH_D02PiPiDecision, &b_TriggerDecHlt2CharmHadD02HH_D02PiPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision", &TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KKDecision", &TriggerDecHlt2CharmHadD02HH_D02KKDecision, &b_TriggerDecHlt2CharmHadD02HH_D02KKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision", &TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision, &b_TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KPiDecision", &TriggerDecHlt2CharmHadD02HH_D02KPiDecision, &b_TriggerDecHlt2CharmHadD02HH_D02KPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision", &TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision", &TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision, &b_TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision", &TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision, &b_TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonDecision", &TriggerDecHlt2DiProtonDecision, &b_TriggerDecHlt2DiProtonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonTFDecision", &TriggerDecHlt2DiProtonTFDecision, &b_TriggerDecHlt2DiProtonTFDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonLowMultDecision", &TriggerDecHlt2DiProtonLowMultDecision, &b_TriggerDecHlt2DiProtonLowMultDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonLowMultTFDecision", &TriggerDecHlt2DiProtonLowMultTFDecision, &b_TriggerDecHlt2DiProtonLowMultTFDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision", &TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision", &TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision", &TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision", &TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD2HMuMuDecision", &TriggerDecHlt2CharmSemilepD2HMuMuDecision, &b_TriggerDecHlt2CharmSemilepD2HMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision", &TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision, &b_TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuDecision", &TriggerDecHlt2CharmSemilepD02HHMuMuDecision, &b_TriggerDecHlt2CharmSemilepD02HHMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision", &TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision, &b_TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2diPhotonDiMuonDecision", &TriggerDecHlt2diPhotonDiMuonDecision, &b_TriggerDecHlt2diPhotonDiMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultMuonDecision", &TriggerDecHlt2LowMultMuonDecision, &b_TriggerDecHlt2LowMultMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultHadronDecision", &TriggerDecHlt2LowMultHadronDecision, &b_TriggerDecHlt2LowMultHadronDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultPhotonDecision", &TriggerDecHlt2LowMultPhotonDecision, &b_TriggerDecHlt2LowMultPhotonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultElectronDecision", &TriggerDecHlt2LowMultElectronDecision, &b_TriggerDecHlt2LowMultElectronDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleTFElectronDecision", &TriggerDecHlt2SingleTFElectronDecision, &b_TriggerDecHlt2SingleTFElectronDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleTFVHighPtElectronDecision", &TriggerDecHlt2SingleTFVHighPtElectronDecision, &b_TriggerDecHlt2SingleTFVHighPtElectronDecision);
   fChain->SetBranchAddress("TriggerDecHlt2B2HHLTUnbiasedDetachedDecision", &TriggerDecHlt2B2HHLTUnbiasedDetachedDecision, &b_TriggerDecHlt2B2HHLTUnbiasedDetachedDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2KPPiDecision", &TriggerDecHlt2CharmHadLambdaC2KPPiDecision, &b_TriggerDecHlt2CharmHadLambdaC2KPPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuonVHighPTDecision", &TriggerDecHlt2SingleMuonVHighPTDecision, &b_TriggerDecHlt2SingleMuonVHighPTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision", &TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadMinBiasLambdaC2KPPiDecision", &TriggerDecHlt2CharmHadMinBiasLambdaC2KPPiDecision, &b_TriggerDecHlt2CharmHadMinBiasLambdaC2KPPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadMinBiasD02KPiDecision", &TriggerDecHlt2CharmHadMinBiasD02KPiDecision, &b_TriggerDecHlt2CharmHadMinBiasD02KPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadMinBiasD02KKDecision", &TriggerDecHlt2CharmHadMinBiasD02KKDecision, &b_TriggerDecHlt2CharmHadMinBiasD02KKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadMinBiasDplus2hhhDecision", &TriggerDecHlt2CharmHadMinBiasDplus2hhhDecision, &b_TriggerDecHlt2CharmHadMinBiasDplus2hhhDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadMinBiasLambdaC2LambdaPiDecision", &TriggerDecHlt2CharmHadMinBiasLambdaC2LambdaPiDecision, &b_TriggerDecHlt2CharmHadMinBiasLambdaC2LambdaPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleDecision", &TriggerDecHlt2DisplVerticesSingleDecision, &b_TriggerDecHlt2DisplVerticesSingleDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesDoublePostScaledDecision", &TriggerDecHlt2DisplVerticesDoublePostScaledDecision, &b_TriggerDecHlt2DisplVerticesDoublePostScaledDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision", &TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision, &b_TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision", &TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision, &b_TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision", &TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision, &b_TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision);
   fChain->SetBranchAddress("TriggerDecHlt2RadiativeTopoTrackTOSDecision", &TriggerDecHlt2RadiativeTopoTrackTOSDecision, &b_TriggerDecHlt2RadiativeTopoTrackTOSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2RadiativeTopoPhotonL0Decision", &TriggerDecHlt2RadiativeTopoPhotonL0Decision, &b_TriggerDecHlt2RadiativeTopoPhotonL0Decision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonPsi2SHighPTDecision", &TriggerDecHlt2DiMuonPsi2SHighPTDecision, &b_TriggerDecHlt2DiMuonPsi2SHighPTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DoubleDiMuonDecision", &TriggerDecHlt2DoubleDiMuonDecision, &b_TriggerDecHlt2DoubleDiMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonAndMuonDecision", &TriggerDecHlt2DiMuonAndMuonDecision, &b_TriggerDecHlt2DiMuonAndMuonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonAndGammaDecision", &TriggerDecHlt2DiMuonAndGammaDecision, &b_TriggerDecHlt2DiMuonAndGammaDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonAndD0Decision", &TriggerDecHlt2DiMuonAndD0Decision, &b_TriggerDecHlt2DiMuonAndD0Decision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonAndDpDecision", &TriggerDecHlt2DiMuonAndDpDecision, &b_TriggerDecHlt2DiMuonAndDpDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonAndDsDecision", &TriggerDecHlt2DiMuonAndDsDecision, &b_TriggerDecHlt2DiMuonAndDsDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonAndLcDecision", &TriggerDecHlt2DiMuonAndLcDecision, &b_TriggerDecHlt2DiMuonAndLcDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision", &TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision, &b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision", &TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision, &b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision", &TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision, &b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision", &TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision, &b_TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoRad2BodyBBDTDecision", &TriggerDecHlt2TopoRad2BodyBBDTDecision, &b_TriggerDecHlt2TopoRad2BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2TopoRad2plus1BodyBBDTDecision", &TriggerDecHlt2TopoRad2plus1BodyBBDTDecision, &b_TriggerDecHlt2TopoRad2plus1BodyBBDTDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LumiDecision", &TriggerDecHlt2LumiDecision, &b_TriggerDecHlt2LumiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultHadron_nofilterDecision", &TriggerDecHlt2LowMultHadron_nofilterDecision, &b_TriggerDecHlt2LowMultHadron_nofilterDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultElectron_nofilterDecision", &TriggerDecHlt2LowMultElectron_nofilterDecision, &b_TriggerDecHlt2LowMultElectron_nofilterDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHKsDDDecision", &TriggerDecHlt2CharmHadD02HHKsDDDecision, &b_TriggerDecHlt2CharmHadD02HHKsDDDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0KS0Decision", &TriggerDecHlt2CharmHadD2KS0KS0Decision, &b_TriggerDecHlt2CharmHadD2KS0KS0Decision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision", &TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision, &b_TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressD02KPiDecision", &TriggerDecHlt2ExpressD02KPiDecision, &b_TriggerDecHlt2ExpressD02KPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision", &TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision, &b_TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2KPKDecision", &TriggerDecHlt2CharmHadLambdaC2KPKDecision, &b_TriggerDecHlt2CharmHadLambdaC2KPKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision", &TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision, &b_TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2PiPPiDecision", &TriggerDecHlt2CharmHadLambdaC2PiPPiDecision, &b_TriggerDecHlt2CharmHadLambdaC2PiPPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision", &TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision, &b_TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2PiPKDecision", &TriggerDecHlt2CharmHadLambdaC2PiPKDecision, &b_TriggerDecHlt2CharmHadLambdaC2PiPKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision", &TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision, &b_TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision", &TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision, &b_TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision", &TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision, &b_TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiPhiDecision", &TriggerDecHlt2DiPhiDecision, &b_TriggerDecHlt2DiPhiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision", &TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision, &b_TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision", &TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision, &b_TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision", &TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision, &b_TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision", &TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision, &b_TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision", &TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision, &b_TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision", &TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision, &b_TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision", &TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision, &b_TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision", &TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision, &b_TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision", &TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision, &b_TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision", &TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision, &b_TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision);
   fChain->SetBranchAddress("TriggerDecHlt2RadiativeTopoTrackDecision", &TriggerDecHlt2RadiativeTopoTrackDecision, &b_TriggerDecHlt2RadiativeTopoTrackDecision);
   fChain->SetBranchAddress("TriggerDecHlt2RadiativeTopoPhotonDecision", &TriggerDecHlt2RadiativeTopoPhotonDecision, &b_TriggerDecHlt2RadiativeTopoPhotonDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_4piDecision", &TriggerDecHlt2CharmHadD02HHHHDst_4piDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_4piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision", &TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision", &TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision", &TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision", &TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision", &TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision, &b_TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision", &TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision", &TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision, &b_TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02KKMuMuDecision", &TriggerDecHlt2CharmSemilepD02KKMuMuDecision, &b_TriggerDecHlt2CharmSemilepD02KKMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02KPiMuMuDecision", &TriggerDecHlt2CharmSemilepD02KPiMuMuDecision, &b_TriggerDecHlt2CharmSemilepD02KPiMuMuDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_4piDecision", &TriggerDecHlt2CharmHadD02HHHH_4piDecision, &b_TriggerDecHlt2CharmHadD02HHHH_4piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_K3piDecision", &TriggerDecHlt2CharmHadD02HHHH_K3piDecision, &b_TriggerDecHlt2CharmHadD02HHHH_K3piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision", &TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision, &b_TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision", &TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_2K2piDecision", &TriggerDecHlt2CharmHadD02HHHH_2K2piDecision, &b_TriggerDecHlt2CharmHadD02HHHH_2K2piDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision", &TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_3KpiDecision", &TriggerDecHlt2CharmHadD02HHHH_3KpiDecision, &b_TriggerDecHlt2CharmHadD02HHHH_3KpiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision", &TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_Ch2Decision", &TriggerDecHlt2CharmHadD02HHHH_Ch2Decision, &b_TriggerDecHlt2CharmHadD02HHHH_Ch2Decision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision", &TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision, &b_TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetachedPsi2SDecision", &TriggerDecHlt2DiMuonDetachedPsi2SDecision, &b_TriggerDecHlt2DiMuonDetachedPsi2SDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHXDst_hhXDecision", &TriggerDecHlt2CharmHadD02HHXDst_hhXDecision, &b_TriggerDecHlt2CharmHadD02HHXDst_hhXDecision);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision", &TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision, &b_TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultD2KPiDecision", &TriggerDecHlt2LowMultD2KPiDecision, &b_TriggerDecHlt2LowMultD2KPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultD2KPiPiDecision", &TriggerDecHlt2LowMultD2KPiPiDecision, &b_TriggerDecHlt2LowMultD2KPiPiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultD2K3PiDecision", &TriggerDecHlt2LowMultD2K3PiDecision, &b_TriggerDecHlt2LowMultD2K3PiDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultChiC2HHDecision", &TriggerDecHlt2LowMultChiC2HHDecision, &b_TriggerDecHlt2LowMultChiC2HHDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultChiC2HHHHDecision", &TriggerDecHlt2LowMultChiC2HHHHDecision, &b_TriggerDecHlt2LowMultChiC2HHHHDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultD2KPiWSDecision", &TriggerDecHlt2LowMultD2KPiWSDecision, &b_TriggerDecHlt2LowMultD2KPiWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultD2KPiPiWSDecision", &TriggerDecHlt2LowMultD2KPiPiWSDecision, &b_TriggerDecHlt2LowMultD2KPiPiWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultD2K3PiWSDecision", &TriggerDecHlt2LowMultD2K3PiWSDecision, &b_TriggerDecHlt2LowMultD2K3PiWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultChiC2HHWSDecision", &TriggerDecHlt2LowMultChiC2HHWSDecision, &b_TriggerDecHlt2LowMultChiC2HHWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultChiC2HHHHWSDecision", &TriggerDecHlt2LowMultChiC2HHHHWSDecision, &b_TriggerDecHlt2LowMultChiC2HHHHWSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2LowMultDDIncDecision", &TriggerDecHlt2LowMultDDIncDecision, &b_TriggerDecHlt2LowMultDDIncDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleLoosePSDecision", &TriggerDecHlt2DisplVerticesSingleLoosePSDecision, &b_TriggerDecHlt2DisplVerticesSingleLoosePSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleHighFDDecision", &TriggerDecHlt2DisplVerticesSingleHighFDDecision, &b_TriggerDecHlt2DisplVerticesSingleHighFDDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision", &TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision, &b_TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleHighMassDecision", &TriggerDecHlt2DisplVerticesSingleHighMassDecision, &b_TriggerDecHlt2DisplVerticesSingleHighMassDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSinglePSDecision", &TriggerDecHlt2DisplVerticesSinglePSDecision, &b_TriggerDecHlt2DisplVerticesSinglePSDecision);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesDoublePSDecision", &TriggerDecHlt2DisplVerticesDoublePSDecision, &b_TriggerDecHlt2DisplVerticesDoublePSDecision);
   fChain->SetBranchAddress("rec_charge", &rec_charge, &b_rec_charge);
   fChain->SetBranchAddress("truetau", &truetau, &b_truetau);
   fChain->SetBranchAddress("truedsetamunu", &truedsetamunu, &b_truedsetamunu);
   fChain->SetBranchAddress("truedsphipi", &truedsphipi, &b_truedsphipi);
   fChain->SetBranchAddress("particleid", &particleid, &b_particleid);
   fChain->SetBranchAddress("FlightDistance", &FlightDistance, &b_FlightDistance);
   fChain->SetBranchAddress("FlightDistanceError", &FlightDistanceError, &b_FlightDistanceError);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("LifeTime", &LifeTime, &b_LifeTime);
   fChain->SetBranchAddress("IP", &IP, &b_IP);
   fChain->SetBranchAddress("IPSig", &IPSig, &b_IPSig);
   fChain->SetBranchAddress("VertexChi2", &VertexChi2, &b_VertexChi2);
   fChain->SetBranchAddress("dira", &dira, &b_dira);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("BPVIPCHI2", &BPVIPCHI2, &b_BPVIPCHI2);
   fChain->SetBranchAddress("BPVLTIME", &BPVLTIME, &b_BPVLTIME);
   fChain->SetBranchAddress("BPVLTIME225", &BPVLTIME225, &b_BPVLTIME225);
   fChain->SetBranchAddress("dimuonchargeproduct", &dimuonchargeproduct, &b_dimuonchargeproduct);
   fChain->SetBranchAddress("DOCAone", &DOCAone, &b_DOCAone);
   fChain->SetBranchAddress("DOCAtwo", &DOCAtwo, &b_DOCAtwo);
   fChain->SetBranchAddress("DOCAthree", &DOCAthree, &b_DOCAthree);
   fChain->SetBranchAddress("mass_p0p2", &mass_p0p2, &b_mass_p0p2);
   fChain->SetBranchAddress("smearedmass_p0p2", &smearedmass_p0p2, &b_smearedmass_p0p2);
   fChain->SetBranchAddress("mass_p1p2", &mass_p1p2, &b_mass_p1p2);
   fChain->SetBranchAddress("smearedmass_p1p2", &smearedmass_p1p2, &b_smearedmass_p1p2);
   fChain->SetBranchAddress("mass_p0p1", &mass_p0p1, &b_mass_p0p1);
   fChain->SetBranchAddress("smearedmass_p0p1", &smearedmass_p0p1, &b_smearedmass_p0p1);
   fChain->SetBranchAddress("smearedmass", &smearedmass, &b_smearedmass);
   fChain->SetBranchAddress("truemass_p0p2", &truemass_p0p2, &b_truemass_p0p2);
   fChain->SetBranchAddress("truemass_p1p2", &truemass_p1p2, &b_truemass_p1p2);
   fChain->SetBranchAddress("truemass_p0p1", &truemass_p0p1, &b_truemass_p0p1);
   fChain->SetBranchAddress("truermass_p0p2", &truermass_p0p2, &b_truermass_p0p2);
   fChain->SetBranchAddress("truermass_p1p2", &truermass_p1p2, &b_truermass_p1p2);
   fChain->SetBranchAddress("truermass_p0p1", &truermass_p0p1, &b_truermass_p0p1);
   fChain->SetBranchAddress("mass_Kpipi", &mass_Kpipi, &b_mass_Kpipi);
   fChain->SetBranchAddress("mass_KKpi1", &mass_KKpi1, &b_mass_KKpi1);
   fChain->SetBranchAddress("mass_KKpi2", &mass_KKpi2, &b_mass_KKpi2);
   fChain->SetBranchAddress("mass_3pi", &mass_3pi, &b_mass_3pi);
   fChain->SetBranchAddress("polarisationangle", &polarisationangle, &b_polarisationangle);
   fChain->SetBranchAddress("IP_p0p2", &IP_p0p2, &b_IP_p0p2);
   fChain->SetBranchAddress("IP_p1p2", &IP_p1p2, &b_IP_p1p2);
   fChain->SetBranchAddress("mass_phihypo", &mass_phihypo, &b_mass_phihypo);
   fChain->SetBranchAddress("mass_k0k2", &mass_k0k2, &b_mass_k0k2);
   fChain->SetBranchAddress("mass_k1k2", &mass_k1k2, &b_mass_k1k2);
   fChain->SetBranchAddress("mass_pi0m1m2", &mass_pi0m1m2, &b_mass_pi0m1m2);
   fChain->SetBranchAddress("mass_m0pi1m2", &mass_m0pi1m2, &b_mass_m0pi1m2);
   fChain->SetBranchAddress("mass_m0m1pi2", &mass_m0m1pi2, &b_mass_m0m1pi2);
   fChain->SetBranchAddress("mass_pi0pi1m2", &mass_pi0pi1m2, &b_mass_pi0pi1m2);
   fChain->SetBranchAddress("mass_pi0m1pi2", &mass_pi0m1pi2, &b_mass_pi0m1pi2);
   fChain->SetBranchAddress("mass_m0pi1pi2", &mass_m0pi1pi2, &b_mass_m0pi1pi2);
   fChain->SetBranchAddress("mass_pi0pi1pi2", &mass_pi0pi1pi2, &b_mass_pi0pi1pi2);
   fChain->SetBranchAddress("mass_k0m1m2", &mass_k0m1m2, &b_mass_k0m1m2);
   fChain->SetBranchAddress("mass_m0k1m2", &mass_m0k1m2, &b_mass_m0k1m2);
   fChain->SetBranchAddress("mass_m0m1k2", &mass_m0m1k2, &b_mass_m0m1k2);
   fChain->SetBranchAddress("mass_k0k1m2", &mass_k0k1m2, &b_mass_k0k1m2);
   fChain->SetBranchAddress("mass_k0m1k2", &mass_k0m1k2, &b_mass_k0m1k2);
   fChain->SetBranchAddress("mass_m0k1k2", &mass_m0k1k2, &b_mass_m0k1k2);
   fChain->SetBranchAddress("mass_k0k1k2", &mass_k0k1k2, &b_mass_k0k1k2);
   fChain->SetBranchAddress("mass_k0pi1pi2", &mass_k0pi1pi2, &b_mass_k0pi1pi2);
   fChain->SetBranchAddress("mass_pi0k1pi2", &mass_pi0k1pi2, &b_mass_pi0k1pi2);
   fChain->SetBranchAddress("mass_pi0pi1k2", &mass_pi0pi1k2, &b_mass_pi0pi1k2);
   fChain->SetBranchAddress("mass_pi0k1k2", &mass_pi0k1k2, &b_mass_pi0k1k2);
   fChain->SetBranchAddress("mass_k0pi1k2", &mass_k0pi1k2, &b_mass_k0pi1k2);
   fChain->SetBranchAddress("mass_k0k1pi2", &mass_k0k1pi2, &b_mass_k0k1pi2);
   fChain->SetBranchAddress("mass_m0pi1k2", &mass_m0pi1k2, &b_mass_m0pi1k2);
   fChain->SetBranchAddress("mass_m0k1pi2", &mass_m0k1pi2, &b_mass_m0k1pi2);
   fChain->SetBranchAddress("mass_pi0m1k2", &mass_pi0m1k2, &b_mass_pi0m1k2);
   fChain->SetBranchAddress("mass_pi0k1m2", &mass_pi0k1m2, &b_mass_pi0k1m2);
   fChain->SetBranchAddress("mass_k0pi1m2", &mass_k0pi1m2, &b_mass_k0pi1m2);
   fChain->SetBranchAddress("mass_k0m1pi2", &mass_k0m1pi2, &b_mass_k0m1pi2);
   fChain->SetBranchAddress("muon_opening_angle", &muon_opening_angle, &b_muon_opening_angle);
   fChain->SetBranchAddress("MC_phimass", &MC_phimass, &b_MC_phimass);
   fChain->SetBranchAddress("MC_phi_daughters_invariantmass", &MC_phi_daughters_invariantmass, &b_MC_phi_daughters_invariantmass);
   fChain->SetBranchAddress("isolationa", &isolationa, &b_isolationa);
   fChain->SetBranchAddress("isolationb", &isolationb, &b_isolationb);
   fChain->SetBranchAddress("isolationc", &isolationc, &b_isolationc);
   fChain->SetBranchAddress("isolationd", &isolationd, &b_isolationd);
   fChain->SetBranchAddress("isolatione", &isolatione, &b_isolatione);
   fChain->SetBranchAddress("isolationf", &isolationf, &b_isolationf);
   fChain->SetBranchAddress("iso", &iso, &b_iso);
   fChain->SetBranchAddress("CDF1", &CDF1, &b_CDF1);
   fChain->SetBranchAddress("CDF2", &CDF2, &b_CDF2);
   fChain->SetBranchAddress("CDF3", &CDF3, &b_CDF3);
   fChain->SetBranchAddress("GeoMVA", &GeoMVA, &b_GeoMVA);
   fChain->SetBranchAddress("geomvacheck", &geomvacheck, &b_geomvacheck);
   fChain->SetBranchAddress("BCK", &BCK, &b_BCK);
   fChain->SetBranchAddress("tauproduction", &tauproduction, &b_tauproduction);
   fChain->SetBranchAddress("productionweightMC10", &productionweightMC10, &b_productionweightMC10);
   fChain->SetBranchAddress("productionweighterrorMC10", &productionweighterrorMC10, &b_productionweighterrorMC10);
   fChain->SetBranchAddress("productionweightMC11v3", &productionweightMC11v3, &b_productionweightMC11v3);
   fChain->SetBranchAddress("productionweighterrorMC11v3", &productionweighterrorMC11v3, &b_productionweighterrorMC11v3);
   fChain->SetBranchAddress("production", &production, &b_production);
   fChain->SetBranchAddress("EventHash", &EventHash, &b_EventHash);
   fChain->SetBranchAddress("Laura_SumBDT", &Laura_SumBDT, &b_Laura_SumBDT);
   fChain->SetBranchAddress("p0_Laura_IsoBDT", &p0_Laura_IsoBDT, &b_p0_Laura_IsoBDT);
   fChain->SetBranchAddress("p1_Laura_IsoBDT", &p1_Laura_IsoBDT, &b_p1_Laura_IsoBDT);
   fChain->SetBranchAddress("p2_Laura_IsoBDT", &p2_Laura_IsoBDT, &b_p2_Laura_IsoBDT);
   fChain->SetBranchAddress("p0_cloneDist", &p0_cloneDist, &b_p0_cloneDist);
   fChain->SetBranchAddress("p1_cloneDist", &p1_cloneDist, &b_p1_cloneDist);
   fChain->SetBranchAddress("p2_cloneDist", &p2_cloneDist, &b_p2_cloneDist);
   fChain->SetBranchAddress("p0_track_Chi2Dof", &p0_track_Chi2Dof, &b_p0_track_Chi2Dof);
   fChain->SetBranchAddress("p1_track_Chi2Dof", &p1_track_Chi2Dof, &b_p1_track_Chi2Dof);
   fChain->SetBranchAddress("p2_track_Chi2Dof", &p2_track_Chi2Dof, &b_p2_track_Chi2Dof);
   fChain->SetBranchAddress("min_ANNmuon", &min_ANNmuon, &b_min_ANNmuon);
   fChain->SetBranchAddress("p0_int_charge", &p0_int_charge, &b_p0_int_charge);
   fChain->SetBranchAddress("p0_float_charge", &p0_float_charge, &b_p0_float_charge);
   fChain->SetBranchAddress("p0_ANNghost", &p0_ANNghost, &b_p0_ANNghost);
   fChain->SetBranchAddress("p0_TRACKghost", &p0_TRACKghost, &b_p0_TRACKghost);
   fChain->SetBranchAddress("p0_TRACKlikelihood", &p0_TRACKlikelihood, &b_p0_TRACKlikelihood);
   fChain->SetBranchAddress("p0_ANNpion", &p0_ANNpion, &b_p0_ANNpion);
   fChain->SetBranchAddress("p0_ANNmuon", &p0_ANNmuon, &b_p0_ANNmuon);
   fChain->SetBranchAddress("p0_ANNkaon", &p0_ANNkaon, &b_p0_ANNkaon);
   fChain->SetBranchAddress("p0_ANNproton", &p0_ANNproton, &b_p0_ANNproton);
   fChain->SetBranchAddress("p0_ANNelectron", &p0_ANNelectron, &b_p0_ANNelectron);
   fChain->SetBranchAddress("p0_Tchi", &p0_Tchi, &b_p0_Tchi);
   fChain->SetBranchAddress("p0_Vchi", &p0_Vchi, &b_p0_Vchi);
   fChain->SetBranchAddress("p0_Tdof", &p0_Tdof, &b_p0_Tdof);
   fChain->SetBranchAddress("p0_Vdof", &p0_Vdof, &b_p0_Vdof);
   fChain->SetBranchAddress("p0_observedV", &p0_observedV, &b_p0_observedV);
   fChain->SetBranchAddress("p0_observedIT", &p0_observedIT, &b_p0_observedIT);
   fChain->SetBranchAddress("p0_observedOT", &p0_observedOT, &b_p0_observedOT);
   fChain->SetBranchAddress("p0_observedTT", &p0_observedTT, &b_p0_observedTT);
   fChain->SetBranchAddress("p0_expectedV", &p0_expectedV, &b_p0_expectedV);
   fChain->SetBranchAddress("p0_expectedIT", &p0_expectedIT, &b_p0_expectedIT);
   fChain->SetBranchAddress("p0_expectedOT", &p0_expectedOT, &b_p0_expectedOT);
   fChain->SetBranchAddress("p0_expectedTT", &p0_expectedTT, &b_p0_expectedTT);
   fChain->SetBranchAddress("p0_isMuon", &p0_isMuon, &b_p0_isMuon);
   fChain->SetBranchAddress("p0_MuonAcc", &p0_MuonAcc, &b_p0_MuonAcc);
   fChain->SetBranchAddress("p0_PIDmupi", &p0_PIDmupi, &b_p0_PIDmupi);
   fChain->SetBranchAddress("p0_PIDmuk", &p0_PIDmuk, &b_p0_PIDmuk);
   fChain->SetBranchAddress("p0_PIDpip", &p0_PIDpip, &b_p0_PIDpip);
   fChain->SetBranchAddress("p0_PIDpk", &p0_PIDpk, &b_p0_PIDpk);
   fChain->SetBranchAddress("p0_PIDppi", &p0_PIDppi, &b_p0_PIDppi);
   fChain->SetBranchAddress("p0_BPVIPCHI2", &p0_BPVIPCHI2, &b_p0_BPVIPCHI2);
   fChain->SetBranchAddress("p0_pt", &p0_pt, &b_p0_pt);
   fChain->SetBranchAddress("p0_p", &p0_p, &b_p0_p);
   fChain->SetBranchAddress("p0_eta", &p0_eta, &b_p0_eta);
   fChain->SetBranchAddress("p0_phi", &p0_phi, &b_p0_phi);
   fChain->SetBranchAddress("p0_track_MatchChi2", &p0_track_MatchChi2, &b_p0_track_MatchChi2);
   fChain->SetBranchAddress("p0_NShared", &p0_NShared, &b_p0_NShared);
   fChain->SetBranchAddress("p0_MuLL", &p0_MuLL, &b_p0_MuLL);
   fChain->SetBranchAddress("p0_MuDLL", &p0_MuDLL, &b_p0_MuDLL);
   fChain->SetBranchAddress("p0_MuBkg", &p0_MuBkg, &b_p0_MuBkg);
   fChain->SetBranchAddress("p0_richMU", &p0_richMU, &b_p0_richMU);
   fChain->SetBranchAddress("p0_richK", &p0_richK, &b_p0_richK);
   fChain->SetBranchAddress("p0_richPI", &p0_richPI, &b_p0_richPI);
   fChain->SetBranchAddress("p0_ecalMU", &p0_ecalMU, &b_p0_ecalMU);
   fChain->SetBranchAddress("p0_hcalMU", &p0_hcalMU, &b_p0_hcalMU);
   fChain->SetBranchAddress("p0_track_Chi2", &p0_track_Chi2, &b_p0_track_Chi2);
   fChain->SetBranchAddress("p0_track_Dof", &p0_track_Dof, &b_p0_track_Dof);
   fChain->SetBranchAddress("p0_NCandCommonFake", &p0_NCandCommonFake, &b_p0_NCandCommonFake);
   fChain->SetBranchAddress("p0_OTbaddrifttime", &p0_OTbaddrifttime, &b_p0_OTbaddrifttime);
   fChain->SetBranchAddress("p0_OToutliers", &p0_OToutliers, &b_p0_OToutliers);
   fChain->SetBranchAddress("p0_mother_mother_mother_mother_mcpid", &p0_mother_mother_mother_mother_mcpid, &b_p0_mother_mother_mother_mother_mcpid);
   fChain->SetBranchAddress("p0_mother_mother_mother_mcpid", &p0_mother_mother_mother_mcpid, &b_p0_mother_mother_mother_mcpid);
   fChain->SetBranchAddress("p0_mother_mother_mcpid", &p0_mother_mother_mcpid, &b_p0_mother_mother_mcpid);
   fChain->SetBranchAddress("p0_mother_mcpid", &p0_mother_mcpid, &b_p0_mother_mcpid);
   fChain->SetBranchAddress("p0_mcpid", &p0_mcpid, &b_p0_mcpid);
   fChain->SetBranchAddress("p0_ghostcat", &p0_ghostcat, &b_p0_ghostcat);
   fChain->SetBranchAddress("p0_trackhistory", &p0_trackhistory, &b_p0_trackhistory);
   fChain->SetBranchAddress("p0_IP", &p0_IP, &b_p0_IP);
   fChain->SetBranchAddress("p0_IPSig", &p0_IPSig, &b_p0_IPSig);
   fChain->SetBranchAddress("p0_largestMClifetime", &p0_largestMClifetime, &b_p0_largestMClifetime);
   fChain->SetBranchAddress("p1_int_charge", &p1_int_charge, &b_p1_int_charge);
   fChain->SetBranchAddress("p1_float_charge", &p1_float_charge, &b_p1_float_charge);
   fChain->SetBranchAddress("p1_ANNghost", &p1_ANNghost, &b_p1_ANNghost);
   fChain->SetBranchAddress("p1_TRACKghost", &p1_TRACKghost, &b_p1_TRACKghost);
   fChain->SetBranchAddress("p1_TRACKlikelihood", &p1_TRACKlikelihood, &b_p1_TRACKlikelihood);
   fChain->SetBranchAddress("p1_ANNpion", &p1_ANNpion, &b_p1_ANNpion);
   fChain->SetBranchAddress("p1_ANNmuon", &p1_ANNmuon, &b_p1_ANNmuon);
   fChain->SetBranchAddress("p1_ANNkaon", &p1_ANNkaon, &b_p1_ANNkaon);
   fChain->SetBranchAddress("p1_ANNproton", &p1_ANNproton, &b_p1_ANNproton);
   fChain->SetBranchAddress("p1_ANNelectron", &p1_ANNelectron, &b_p1_ANNelectron);
   fChain->SetBranchAddress("p1_Tchi", &p1_Tchi, &b_p1_Tchi);
   fChain->SetBranchAddress("p1_Vchi", &p1_Vchi, &b_p1_Vchi);
   fChain->SetBranchAddress("p1_Tdof", &p1_Tdof, &b_p1_Tdof);
   fChain->SetBranchAddress("p1_Vdof", &p1_Vdof, &b_p1_Vdof);
   fChain->SetBranchAddress("p1_observedV", &p1_observedV, &b_p1_observedV);
   fChain->SetBranchAddress("p1_observedIT", &p1_observedIT, &b_p1_observedIT);
   fChain->SetBranchAddress("p1_observedOT", &p1_observedOT, &b_p1_observedOT);
   fChain->SetBranchAddress("p1_observedTT", &p1_observedTT, &b_p1_observedTT);
   fChain->SetBranchAddress("p1_expectedV", &p1_expectedV, &b_p1_expectedV);
   fChain->SetBranchAddress("p1_expectedIT", &p1_expectedIT, &b_p1_expectedIT);
   fChain->SetBranchAddress("p1_expectedOT", &p1_expectedOT, &b_p1_expectedOT);
   fChain->SetBranchAddress("p1_expectedTT", &p1_expectedTT, &b_p1_expectedTT);
   fChain->SetBranchAddress("p1_isMuon", &p1_isMuon, &b_p1_isMuon);
   fChain->SetBranchAddress("p1_MuonAcc", &p1_MuonAcc, &b_p1_MuonAcc);
   fChain->SetBranchAddress("p1_PIDmupi", &p1_PIDmupi, &b_p1_PIDmupi);
   fChain->SetBranchAddress("p1_PIDmuk", &p1_PIDmuk, &b_p1_PIDmuk);
   fChain->SetBranchAddress("p1_PIDpip", &p1_PIDpip, &b_p1_PIDpip);
   fChain->SetBranchAddress("p1_PIDpk", &p1_PIDpk, &b_p1_PIDpk);
   fChain->SetBranchAddress("p1_PIDppi", &p1_PIDppi, &b_p1_PIDppi);
   fChain->SetBranchAddress("p1_BPVIPCHI2", &p1_BPVIPCHI2, &b_p1_BPVIPCHI2);
   fChain->SetBranchAddress("p1_pt", &p1_pt, &b_p1_pt);
   fChain->SetBranchAddress("p1_p", &p1_p, &b_p1_p);
   fChain->SetBranchAddress("p1_eta", &p1_eta, &b_p1_eta);
   fChain->SetBranchAddress("p1_phi", &p1_phi, &b_p1_phi);
   fChain->SetBranchAddress("p1_track_MatchChi2", &p1_track_MatchChi2, &b_p1_track_MatchChi2);
   fChain->SetBranchAddress("p1_NShared", &p1_NShared, &b_p1_NShared);
   fChain->SetBranchAddress("p1_MuLL", &p1_MuLL, &b_p1_MuLL);
   fChain->SetBranchAddress("p1_MuDLL", &p1_MuDLL, &b_p1_MuDLL);
   fChain->SetBranchAddress("p1_MuBkg", &p1_MuBkg, &b_p1_MuBkg);
   fChain->SetBranchAddress("p1_richMU", &p1_richMU, &b_p1_richMU);
   fChain->SetBranchAddress("p1_richK", &p1_richK, &b_p1_richK);
   fChain->SetBranchAddress("p1_richPI", &p1_richPI, &b_p1_richPI);
   fChain->SetBranchAddress("p1_ecalMU", &p1_ecalMU, &b_p1_ecalMU);
   fChain->SetBranchAddress("p1_hcalMU", &p1_hcalMU, &b_p1_hcalMU);
   fChain->SetBranchAddress("p1_track_Chi2", &p1_track_Chi2, &b_p1_track_Chi2);
   fChain->SetBranchAddress("p1_track_Dof", &p1_track_Dof, &b_p1_track_Dof);
   fChain->SetBranchAddress("p1_NCandCommonFake", &p1_NCandCommonFake, &b_p1_NCandCommonFake);
   fChain->SetBranchAddress("p1_OTbaddrifttime", &p1_OTbaddrifttime, &b_p1_OTbaddrifttime);
   fChain->SetBranchAddress("p1_OToutliers", &p1_OToutliers, &b_p1_OToutliers);
   fChain->SetBranchAddress("p1_mother_mother_mother_mother_mcpid", &p1_mother_mother_mother_mother_mcpid, &b_p1_mother_mother_mother_mother_mcpid);
   fChain->SetBranchAddress("p1_mother_mother_mother_mcpid", &p1_mother_mother_mother_mcpid, &b_p1_mother_mother_mother_mcpid);
   fChain->SetBranchAddress("p1_mother_mother_mcpid", &p1_mother_mother_mcpid, &b_p1_mother_mother_mcpid);
   fChain->SetBranchAddress("p1_mother_mcpid", &p1_mother_mcpid, &b_p1_mother_mcpid);
   fChain->SetBranchAddress("p1_mcpid", &p1_mcpid, &b_p1_mcpid);
   fChain->SetBranchAddress("p1_ghostcat", &p1_ghostcat, &b_p1_ghostcat);
   fChain->SetBranchAddress("p1_trackhistory", &p1_trackhistory, &b_p1_trackhistory);
   fChain->SetBranchAddress("p1_IP", &p1_IP, &b_p1_IP);
   fChain->SetBranchAddress("p1_IPSig", &p1_IPSig, &b_p1_IPSig);
   fChain->SetBranchAddress("p1_largestMClifetime", &p1_largestMClifetime, &b_p1_largestMClifetime);
   fChain->SetBranchAddress("p2_int_charge", &p2_int_charge, &b_p2_int_charge);
   fChain->SetBranchAddress("p2_float_charge", &p2_float_charge, &b_p2_float_charge);
   fChain->SetBranchAddress("p2_ANNghost", &p2_ANNghost, &b_p2_ANNghost);
   fChain->SetBranchAddress("p2_TRACKghost", &p2_TRACKghost, &b_p2_TRACKghost);
   fChain->SetBranchAddress("p2_TRACKlikelihood", &p2_TRACKlikelihood, &b_p2_TRACKlikelihood);
   fChain->SetBranchAddress("p2_ANNpion", &p2_ANNpion, &b_p2_ANNpion);
   fChain->SetBranchAddress("p2_ANNmuon", &p2_ANNmuon, &b_p2_ANNmuon);
   fChain->SetBranchAddress("p2_ANNkaon", &p2_ANNkaon, &b_p2_ANNkaon);
   fChain->SetBranchAddress("p2_ANNproton", &p2_ANNproton, &b_p2_ANNproton);
   fChain->SetBranchAddress("p2_ANNelectron", &p2_ANNelectron, &b_p2_ANNelectron);
   fChain->SetBranchAddress("p2_Tchi", &p2_Tchi, &b_p2_Tchi);
   fChain->SetBranchAddress("p2_Vchi", &p2_Vchi, &b_p2_Vchi);
   fChain->SetBranchAddress("p2_Tdof", &p2_Tdof, &b_p2_Tdof);
   fChain->SetBranchAddress("p2_Vdof", &p2_Vdof, &b_p2_Vdof);
   fChain->SetBranchAddress("p2_observedV", &p2_observedV, &b_p2_observedV);
   fChain->SetBranchAddress("p2_observedIT", &p2_observedIT, &b_p2_observedIT);
   fChain->SetBranchAddress("p2_observedOT", &p2_observedOT, &b_p2_observedOT);
   fChain->SetBranchAddress("p2_observedTT", &p2_observedTT, &b_p2_observedTT);
   fChain->SetBranchAddress("p2_expectedV", &p2_expectedV, &b_p2_expectedV);
   fChain->SetBranchAddress("p2_expectedIT", &p2_expectedIT, &b_p2_expectedIT);
   fChain->SetBranchAddress("p2_expectedOT", &p2_expectedOT, &b_p2_expectedOT);
   fChain->SetBranchAddress("p2_expectedTT", &p2_expectedTT, &b_p2_expectedTT);
   fChain->SetBranchAddress("p2_isMuon", &p2_isMuon, &b_p2_isMuon);
   fChain->SetBranchAddress("p2_MuonAcc", &p2_MuonAcc, &b_p2_MuonAcc);
   fChain->SetBranchAddress("p2_PIDmupi", &p2_PIDmupi, &b_p2_PIDmupi);
   fChain->SetBranchAddress("p2_PIDmuk", &p2_PIDmuk, &b_p2_PIDmuk);
   fChain->SetBranchAddress("p2_PIDpip", &p2_PIDpip, &b_p2_PIDpip);
   fChain->SetBranchAddress("p2_PIDpk", &p2_PIDpk, &b_p2_PIDpk);
   fChain->SetBranchAddress("p2_PIDppi", &p2_PIDppi, &b_p2_PIDppi);
   fChain->SetBranchAddress("p2_BPVIPCHI2", &p2_BPVIPCHI2, &b_p2_BPVIPCHI2);
   fChain->SetBranchAddress("p2_pt", &p2_pt, &b_p2_pt);
   fChain->SetBranchAddress("p2_p", &p2_p, &b_p2_p);
   fChain->SetBranchAddress("p2_eta", &p2_eta, &b_p2_eta);
   fChain->SetBranchAddress("p2_phi", &p2_phi, &b_p2_phi);
   fChain->SetBranchAddress("p2_track_MatchChi2", &p2_track_MatchChi2, &b_p2_track_MatchChi2);
   fChain->SetBranchAddress("p2_NShared", &p2_NShared, &b_p2_NShared);
   fChain->SetBranchAddress("p2_MuLL", &p2_MuLL, &b_p2_MuLL);
   fChain->SetBranchAddress("p2_MuDLL", &p2_MuDLL, &b_p2_MuDLL);
   fChain->SetBranchAddress("p2_MuBkg", &p2_MuBkg, &b_p2_MuBkg);
   fChain->SetBranchAddress("p2_richMU", &p2_richMU, &b_p2_richMU);
   fChain->SetBranchAddress("p2_richK", &p2_richK, &b_p2_richK);
   fChain->SetBranchAddress("p2_richPI", &p2_richPI, &b_p2_richPI);
   fChain->SetBranchAddress("p2_ecalMU", &p2_ecalMU, &b_p2_ecalMU);
   fChain->SetBranchAddress("p2_hcalMU", &p2_hcalMU, &b_p2_hcalMU);
   fChain->SetBranchAddress("p2_track_Chi2", &p2_track_Chi2, &b_p2_track_Chi2);
   fChain->SetBranchAddress("p2_track_Dof", &p2_track_Dof, &b_p2_track_Dof);
   fChain->SetBranchAddress("p2_NCandCommonFake", &p2_NCandCommonFake, &b_p2_NCandCommonFake);
   fChain->SetBranchAddress("p2_OTbaddrifttime", &p2_OTbaddrifttime, &b_p2_OTbaddrifttime);
   fChain->SetBranchAddress("p2_OToutliers", &p2_OToutliers, &b_p2_OToutliers);
   fChain->SetBranchAddress("p2_mother_mother_mother_mother_mcpid", &p2_mother_mother_mother_mother_mcpid, &b_p2_mother_mother_mother_mother_mcpid);
   fChain->SetBranchAddress("p2_mother_mother_mother_mcpid", &p2_mother_mother_mother_mcpid, &b_p2_mother_mother_mother_mcpid);
   fChain->SetBranchAddress("p2_mother_mother_mcpid", &p2_mother_mother_mcpid, &b_p2_mother_mother_mcpid);
   fChain->SetBranchAddress("p2_mother_mcpid", &p2_mother_mcpid, &b_p2_mother_mcpid);
   fChain->SetBranchAddress("p2_mcpid", &p2_mcpid, &b_p2_mcpid);
   fChain->SetBranchAddress("p2_ghostcat", &p2_ghostcat, &b_p2_ghostcat);
   fChain->SetBranchAddress("p2_trackhistory", &p2_trackhistory, &b_p2_trackhistory);
   fChain->SetBranchAddress("p2_IP", &p2_IP, &b_p2_IP);
   fChain->SetBranchAddress("p2_IPSig", &p2_IPSig, &b_p2_IPSig);
   fChain->SetBranchAddress("p2_largestMClifetime", &p2_largestMClifetime, &b_p2_largestMClifetime);
   fChain->SetBranchAddress("OThits", &OThits, &b_OThits);
   fChain->SetBranchAddress("IThits", &IThits, &b_IThits);
   fChain->SetBranchAddress("TThits", &TThits, &b_TThits);
   fChain->SetBranchAddress("VELOhits", &VELOhits, &b_VELOhits);
   fChain->SetBranchAddress("SPDhits", &SPDhits, &b_SPDhits);
   fChain->SetBranchAddress("NgammaVLLLL", &NgammaVLLLL, &b_NgammaVLLLL);
   fChain->SetBranchAddress("NgammaVLLRR", &NgammaVLLRR, &b_NgammaVLLRR);
   fChain->SetBranchAddress("NgammaRAD", &NgammaRAD, &b_NgammaRAD);
   fChain->SetBranchAddress("NgammaVLLLL_RAD", &NgammaVLLLL_RAD, &b_NgammaVLLLL_RAD);
   fChain->SetBranchAddress("NgammaVLLRR_RAD", &NgammaVLLRR_RAD, &b_NgammaVLLRR_RAD);
   fChain->SetBranchAddress("MCNgammaVLLLL", &MCNgammaVLLLL, &b_MCNgammaVLLLL);
   fChain->SetBranchAddress("MCNgammaVLLRR", &MCNgammaVLLRR, &b_MCNgammaVLLRR);
   fChain->SetBranchAddress("MCNgammaRAD", &MCNgammaRAD, &b_MCNgammaRAD);
   fChain->SetBranchAddress("MCNgammaVLLLL_RAD", &MCNgammaVLLLL_RAD, &b_MCNgammaVLLLL_RAD);
   fChain->SetBranchAddress("MCNgammaVLLRR_RAD", &MCNgammaVLLRR_RAD, &b_MCNgammaVLLRR_RAD);
   Notify();
}

Bool_t readNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void readNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t readNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef readNtuple_cxx
