//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 24 11:55:23 2013 by ROOT version 5.34/04
// from TTree Tau23Mu/Tau23Mu
// found on file: mc_MC10tau23mu_UP_TRUTHATTEMPT_sm0_flat_83099evts.root
//////////////////////////////////////////////////////////

#ifndef flat_h
#define flat_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class flat {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RUNNING_EVENT_NUMBER;
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           TCK;
   Float_t         Strip15And17;
   Int_t           cleaningcut;
   Int_t           jonpid;
   Int_t           jongeo;
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
   Int_t           TriggerDecHlt1DiMuonHighMass;
   Int_t           TriggerDecHlt1DiMuonLowMass;
   Int_t           TriggerDecHlt1SingleMuonNoIP;
   Int_t           TriggerDecHlt1SingleMuonHighPT;
   Int_t           TriggerDecHlt1TrackAllL0;
   Int_t           TriggerDecHlt1TrackMuon;
   Int_t           TriggerDecHlt1TrackPhoton;
   Int_t           TriggerDecHlt1Lumi;
   Int_t           TriggerDecHlt1LumiMidBeamCrossing;
   Int_t           TriggerDecHlt1MBNoBias;
   Int_t           TriggerDecHlt1L0Any;
   Int_t           TriggerDecHlt1L0AnyRateLimited;
   Int_t           TriggerDecHlt1L0AnyNoSPD;
   Int_t           TriggerDecHlt1L0AnyNoSPDRateLimited;
   Int_t           TriggerDecHlt1NoPVPassThrough;
   Int_t           TriggerDecHlt1DiProtonLowMult;
   Int_t           TriggerDecHlt1BeamGasNoBeamBeam1;
   Int_t           TriggerDecHlt1BeamGasNoBeamBeam2;
   Int_t           TriggerDecHlt1BeamGasBeam1;
   Int_t           TriggerDecHlt1BeamGasBeam2;
   Int_t           TriggerDecHlt1BeamGasCrossingEnhancedBeam1;
   Int_t           TriggerDecHlt1BeamGasCrossingEnhancedBeam2;
   Int_t           TriggerDecHlt1BeamGasCrossingForcedReco;
   Int_t           TriggerDecHlt1ODINTechnical;
   Int_t           TriggerDecHlt1Tell1Error;
   Int_t           TriggerDecHlt1BeamGasCrossingParasitic;
   Int_t           TriggerDecHlt1ErrorEvent;
   Int_t           TriggerDecHlt1Global;
   Int_t           TriggerDecHlt1MBMicroBiasVelo;
   Int_t           TriggerDecHlt1MBMicroBiasVeloRateLimited;
   Int_t           TriggerDecHlt1MBMicroBiasTStation;
   Int_t           TriggerDecHlt1MBMicroBiasTStationRateLimited;
   Int_t           TriggerDecHlt1DiProton;
   Int_t           TriggerDecHlt1VeloClosingMicroBias;
   Int_t           TriggerDecHlt2SingleElectronTFLowPt;
   Int_t           TriggerDecHlt2SingleElectronTFHighPt;
   Int_t           TriggerDecHlt2DiElectronHighMass;
   Int_t           TriggerDecHlt2DiElectronB;
   Int_t           TriggerDecHlt2Topo2BodySimple;
   Int_t           TriggerDecHlt2Topo3BodySimple;
   Int_t           TriggerDecHlt2Topo4BodySimple;
   Int_t           TriggerDecHlt2Topo2BodyBBDT;
   Int_t           TriggerDecHlt2Topo3BodyBBDT;
   Int_t           TriggerDecHlt2Topo4BodyBBDT;
   Int_t           TriggerDecHlt2TopoMu2BodyBBDT;
   Int_t           TriggerDecHlt2TopoMu3BodyBBDT;
   Int_t           TriggerDecHlt2TopoMu4BodyBBDT;
   Int_t           TriggerDecHlt2TopoE2BodyBBDT;
   Int_t           TriggerDecHlt2TopoE3BodyBBDT;
   Int_t           TriggerDecHlt2TopoE4BodyBBDT;
   Int_t           TriggerDecHlt2IncPhi;
   Int_t           TriggerDecHlt2IncPhiSidebands;
   Int_t           TriggerDecHlt2CharmHadD02HHKsLL;
   Int_t           TriggerDecHlt2Dst2PiD02PiPi;
   Int_t           TriggerDecHlt2Dst2PiD02MuMu;
   Int_t           TriggerDecHlt2Dst2PiD02KMu;
   Int_t           TriggerDecHlt2Dst2PiD02KPi;
   Int_t           TriggerDecHlt2PassThrough;
   Int_t           TriggerDecHlt2Transparent;
   Int_t           TriggerDecHlt2Forward;
   Int_t           TriggerDecHlt2DebugEvent;
   Int_t           TriggerDecHlt2CharmHadD02KK;
   Int_t           TriggerDecHlt2CharmHadD02KKWideMass;
   Int_t           TriggerDecHlt2CharmHadD02KPi;
   Int_t           TriggerDecHlt2CharmHadD02KPiWideMass;
   Int_t           TriggerDecHlt2CharmHadD02PiPi;
   Int_t           TriggerDecHlt2CharmHadD02PiPiWideMass;
   Int_t           TriggerDecHlt2ExpressJPsi;
   Int_t           TriggerDecHlt2ExpressJPsiTagProbe;
   Int_t           TriggerDecHlt2ExpressLambda;
   Int_t           TriggerDecHlt2ExpressKS;
   Int_t           TriggerDecHlt2ExpressDs2PhiPi;
   Int_t           TriggerDecHlt2ExpressBeamHalo;
   Int_t           TriggerDecHlt2ExpressDStar2D0Pi;
   Int_t           TriggerDecHlt2ExpressHLT1Physics;
   Int_t           TriggerDecHlt2Bs2PhiGamma;
   Int_t           TriggerDecHlt2Bs2PhiGammaWideBMass;
   Int_t           TriggerDecHlt2Bd2KstGamma;
   Int_t           TriggerDecHlt2Bd2KstGammaWideKMass;
   Int_t           TriggerDecHlt2Bd2KstGammaWideBMass;
   Int_t           TriggerDecHlt2CharmHadD2KS0Pi;
   Int_t           TriggerDecHlt2CharmHadD2KS0K;
   Int_t           TriggerDecHlt2CharmRareDecayD02MuMu;
   Int_t           TriggerDecHlt2B2HH;
   Int_t           TriggerDecHlt2MuonFromHLT1;
   Int_t           TriggerDecHlt2SingleMuon;
   Int_t           TriggerDecHlt2SingleMuonHighPT;
   Int_t           TriggerDecHlt2SingleMuonLowPT;
   Int_t           TriggerDecHlt2TFBc2JpsiMuX;
   Int_t           TriggerDecHlt2TFBc2JpsiMuXSignal;
   Int_t           TriggerDecHlt2DisplVerticesLowMassSingle;
   Int_t           TriggerDecHlt2DisplVerticesHighMassSingle;
   Int_t           TriggerDecHlt2DisplVerticesDouble;
   Int_t           TriggerDecHlt2DisplVerticesSinglePostScaled;
   Int_t           TriggerDecHlt2DisplVerticesHighFDSingle;
   Int_t           TriggerDecHlt2DisplVerticesSingleDown;
   Int_t           TriggerDecHlt2B2HHPi0_Merged;
   Int_t           TriggerDecHlt2CharmHadD2HHH;
   Int_t           TriggerDecHlt2CharmHadD2HHHWideMass;
   Int_t           TriggerDecHlt2DiMuon;
   Int_t           TriggerDecHlt2DiMuonLowMass;
   Int_t           TriggerDecHlt2DiMuonJPsi;
   Int_t           TriggerDecHlt2DiMuonJPsiHighPT;
   Int_t           TriggerDecHlt2DiMuonPsi2S;
   Int_t           TriggerDecHlt2DiMuonB;
   Int_t           TriggerDecHlt2DiMuonZ;
   Int_t           TriggerDecHlt2DiMuonDY1;
   Int_t           TriggerDecHlt2DiMuonDY2;
   Int_t           TriggerDecHlt2DiMuonDY3;
   Int_t           TriggerDecHlt2DiMuonDY4;
   Int_t           TriggerDecHlt2DiMuonDetached;
   Int_t           TriggerDecHlt2DiMuonDetachedHeavy;
   Int_t           TriggerDecHlt2DiMuonDetachedJPsi;
   Int_t           TriggerDecHlt2DiMuonNoPV;
   Int_t           TriggerDecHlt2TriMuonDetached;
   Int_t           TriggerDecHlt2TriMuonTau;
   Int_t           TriggerDecHlt2CharmHadD02HHHH;
   Int_t           TriggerDecHlt2CharmHadD02HHHHWideMass;
   Int_t           TriggerDecHlt2ErrorEvent;
   Int_t           TriggerDecHlt2Global;
   Int_t           TriggerDecHlt2B2HHLTUnbiased;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02PiPi;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02PiPiWideMass;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KK;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KKWideMass;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KPi;
   Int_t           TriggerDecHlt2CharmHadD02HH_D02KPiWideMass;
   Int_t           TriggerDecHlt2CharmHadD2KS0H_D2KS0Pi;
   Int_t           TriggerDecHlt2CharmHadD2KS0H_D2KS0K;
   Int_t           TriggerDecHlt2DiProton;
   Int_t           TriggerDecHlt2DiProtonTF;
   Int_t           TriggerDecHlt2DiProtonLowMult;
   Int_t           TriggerDecHlt2DiProtonLowMultTF;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWS;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWS;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNu;
   Int_t           TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNu;
   Int_t           TriggerDecHlt2CharmSemilepD2HMuMu;
   Int_t           TriggerDecHlt2CharmSemilepD2HMuMuWideMass;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMu;
   Int_t           TriggerDecHlt2CharmSemilepD02HHMuMuWideMass;
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
   Float_t         truetau;
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
   Float_t         BPVLTIME225;
   Float_t         minPIDmupi;
   Float_t         minPIDmuk;
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
   Float_t         truermass_p0p2;
   Float_t         truermass_p1p2;
   Float_t         truermass_p0p1;
   Float_t         mass_Kpipi;
   Float_t         mass_KKpi1;
   Float_t         mass_KKpi2;
   Float_t         mass_3pi;
   Float_t         Dalitz_m12;
   Float_t         Dalitz_m23;
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
   Float_t         ptorderedp0_IPSig;
   Float_t         ptorderedp1_IPSig;
   Float_t         ptorderedp2_IPSig;
   Float_t         ptorderedp0_pt;
   Float_t         ptorderedp1_pt;
   Float_t         ptorderedp2_pt;
   Float_t         ptorderedp0_p0_track_Chi2Dof;
   Float_t         ptorderedp1_p1_track_Chi2Dof;
   Float_t         ptorderedp2_p2_track_Chi2Dof;
   Float_t         ptorderedp0_PIDmupi;
   Float_t         ptorderedp1_PIDmupi;
   Float_t         ptorderedp2_PIDmupi;
   Float_t         ptorderedp0_PIDmuk;
   Float_t         ptorderedp1_PIDmuk;
   Float_t         ptorderedp2_PIDmuk;
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
   Float_t         PIDMVA;
   Float_t         noptPIDMVA;
   Float_t         GeoMVA;
   Float_t         geomvacheck;
   Float_t         GeoMVA_pol;
   Float_t         GeoMVA_dimu;
   Float_t         GeoMVA_poldimu;
   Float_t         Dalitz;
   Float_t         Dalitz_glcut;
   Float_t         Dalitz_eta;
   Float_t         Dalitz_cat;
   Float_t         smeared_Dalitz;
   Float_t         smeared_Dalitz_glcut;
   Float_t         smeared_Dalitz_eta;
   Float_t         smeared_Dalitz_cat;
   Int_t           BCK;
   Int_t           tauproduction;
   Float_t         productionweightMC10;
   Float_t         productionweighterrorMC10;
   Float_t         productionweightMC11;
   Float_t         productionweighterrorMC11;
   Float_t         productionweightMC11v2;
   Float_t         productionweighterrorMC11v2;
   Float_t         productionweightMC11v3;
   Float_t         productionweighterrorMC11v3;
   Int_t           production;
   Int_t           EventHash;
   Float_t         p0_cloneDist;
   Float_t         p1_cloneDist;
   Float_t         p2_cloneDist;
   Float_t         p0_track_Chi2Dof;
   Float_t         p1_track_Chi2Dof;
   Float_t         p2_track_Chi2Dof;
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
   Float_t         p0_singlePID;
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
   Int_t           p0_mcpid;
   Float_t         p0_ghostcat;
   Float_t         p0_trackhistory;
   Float_t         p0_IP;
   Float_t         p0_IPSig;
   Float_t         p0_largestMClifetime;
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
   Float_t         p1_singlePID;
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
   Int_t           p1_mcpid;
   Float_t         p1_ghostcat;
   Float_t         p1_trackhistory;
   Float_t         p1_IP;
   Float_t         p1_IPSig;
   Float_t         p1_largestMClifetime;
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
   Float_t         p2_singlePID;
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
   Int_t           p2_mcpid;
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
   Float_t         NeuroBayes_0x109cf818;
   Float_t         NeuroBayes_0x119cf818;
   Float_t         NeuroBayes_0x129cf818;
   Float_t         NeuroBayes_0x141cf818;
   Float_t         NeuroBayes_0x143cf818;
   Float_t         NeuroBayes_0x145cf818;
   Float_t         NeuroBayes_0x149c1818;
   Float_t         NeuroBayes_0x149ce018;
   Float_t         NeuroBayes_0x149ce718;
   Float_t         NeuroBayes_0x149cf818;
   Float_t         NeuroBayes_0x149d1818;
   Float_t         NeuroBayes_0x1c9cf818;

   // List of branches
   TBranch        *b_RUNNING_EVENT_NUMBER;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_TCK;   //!
   TBranch        *b_Strip15And17;   //!
   TBranch        *b_cleaningcut;   //!
   TBranch        *b_jonpid;   //!
   TBranch        *b_jongeo;   //!
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
   TBranch        *b_TriggerDecHlt1DiMuonHighMass;   //!
   TBranch        *b_TriggerDecHlt1DiMuonLowMass;   //!
   TBranch        *b_TriggerDecHlt1SingleMuonNoIP;   //!
   TBranch        *b_TriggerDecHlt1SingleMuonHighPT;   //!
   TBranch        *b_TriggerDecHlt1TrackAllL0;   //!
   TBranch        *b_TriggerDecHlt1TrackMuon;   //!
   TBranch        *b_TriggerDecHlt1TrackPhoton;   //!
   TBranch        *b_TriggerDecHlt1Lumi;   //!
   TBranch        *b_TriggerDecHlt1LumiMidBeamCrossing;   //!
   TBranch        *b_TriggerDecHlt1MBNoBias;   //!
   TBranch        *b_TriggerDecHlt1L0Any;   //!
   TBranch        *b_TriggerDecHlt1L0AnyRateLimited;   //!
   TBranch        *b_TriggerDecHlt1L0AnyNoSPD;   //!
   TBranch        *b_TriggerDecHlt1L0AnyNoSPDRateLimited;   //!
   TBranch        *b_TriggerDecHlt1NoPVPassThrough;   //!
   TBranch        *b_TriggerDecHlt1DiProtonLowMult;   //!
   TBranch        *b_TriggerDecHlt1BeamGasNoBeamBeam1;   //!
   TBranch        *b_TriggerDecHlt1BeamGasNoBeamBeam2;   //!
   TBranch        *b_TriggerDecHlt1BeamGasBeam1;   //!
   TBranch        *b_TriggerDecHlt1BeamGasBeam2;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingEnhancedBeam1;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingEnhancedBeam2;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingForcedReco;   //!
   TBranch        *b_TriggerDecHlt1ODINTechnical;   //!
   TBranch        *b_TriggerDecHlt1Tell1Error;   //!
   TBranch        *b_TriggerDecHlt1BeamGasCrossingParasitic;   //!
   TBranch        *b_TriggerDecHlt1ErrorEvent;   //!
   TBranch        *b_TriggerDecHlt1Global;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasVelo;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasVeloRateLimited;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasTStation;   //!
   TBranch        *b_TriggerDecHlt1MBMicroBiasTStationRateLimited;   //!
   TBranch        *b_TriggerDecHlt1DiProton;   //!
   TBranch        *b_TriggerDecHlt1VeloClosingMicroBias;   //!
   TBranch        *b_TriggerDecHlt2SingleElectronTFLowPt;   //!
   TBranch        *b_TriggerDecHlt2SingleElectronTFHighPt;   //!
   TBranch        *b_TriggerDecHlt2DiElectronHighMass;   //!
   TBranch        *b_TriggerDecHlt2DiElectronB;   //!
   TBranch        *b_TriggerDecHlt2Topo2BodySimple;   //!
   TBranch        *b_TriggerDecHlt2Topo3BodySimple;   //!
   TBranch        *b_TriggerDecHlt2Topo4BodySimple;   //!
   TBranch        *b_TriggerDecHlt2Topo2BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2Topo3BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2Topo4BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2TopoMu2BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2TopoMu3BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2TopoMu4BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2TopoE2BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2TopoE3BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2TopoE4BodyBBDT;   //!
   TBranch        *b_TriggerDecHlt2IncPhi;   //!
   TBranch        *b_TriggerDecHlt2IncPhiSidebands;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHKsLL;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02PiPi;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02MuMu;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02KMu;   //!
   TBranch        *b_TriggerDecHlt2Dst2PiD02KPi;   //!
   TBranch        *b_TriggerDecHlt2PassThrough;   //!
   TBranch        *b_TriggerDecHlt2Transparent;   //!
   TBranch        *b_TriggerDecHlt2Forward;   //!
   TBranch        *b_TriggerDecHlt2DebugEvent;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KK;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KKWideMass;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KPi;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02KPiWideMass;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02PiPi;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02PiPiWideMass;   //!
   TBranch        *b_TriggerDecHlt2ExpressJPsi;   //!
   TBranch        *b_TriggerDecHlt2ExpressJPsiTagProbe;   //!
   TBranch        *b_TriggerDecHlt2ExpressLambda;   //!
   TBranch        *b_TriggerDecHlt2ExpressKS;   //!
   TBranch        *b_TriggerDecHlt2ExpressDs2PhiPi;   //!
   TBranch        *b_TriggerDecHlt2ExpressBeamHalo;   //!
   TBranch        *b_TriggerDecHlt2ExpressDStar2D0Pi;   //!
   TBranch        *b_TriggerDecHlt2ExpressHLT1Physics;   //!
   TBranch        *b_TriggerDecHlt2Bs2PhiGamma;   //!
   TBranch        *b_TriggerDecHlt2Bs2PhiGammaWideBMass;   //!
   TBranch        *b_TriggerDecHlt2Bd2KstGamma;   //!
   TBranch        *b_TriggerDecHlt2Bd2KstGammaWideKMass;   //!
   TBranch        *b_TriggerDecHlt2Bd2KstGammaWideBMass;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0Pi;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0K;   //!
   TBranch        *b_TriggerDecHlt2CharmRareDecayD02MuMu;   //!
   TBranch        *b_TriggerDecHlt2B2HH;   //!
   TBranch        *b_TriggerDecHlt2MuonFromHLT1;   //!
   TBranch        *b_TriggerDecHlt2SingleMuon;   //!
   TBranch        *b_TriggerDecHlt2SingleMuonHighPT;   //!
   TBranch        *b_TriggerDecHlt2SingleMuonLowPT;   //!
   TBranch        *b_TriggerDecHlt2TFBc2JpsiMuX;   //!
   TBranch        *b_TriggerDecHlt2TFBc2JpsiMuXSignal;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesLowMassSingle;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesHighMassSingle;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesDouble;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSinglePostScaled;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesHighFDSingle;   //!
   TBranch        *b_TriggerDecHlt2DisplVerticesSingleDown;   //!
   TBranch        *b_TriggerDecHlt2B2HHPi0_Merged;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2HHH;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2HHHWideMass;   //!
   TBranch        *b_TriggerDecHlt2DiMuon;   //!
   TBranch        *b_TriggerDecHlt2DiMuonLowMass;   //!
   TBranch        *b_TriggerDecHlt2DiMuonJPsi;   //!
   TBranch        *b_TriggerDecHlt2DiMuonJPsiHighPT;   //!
   TBranch        *b_TriggerDecHlt2DiMuonPsi2S;   //!
   TBranch        *b_TriggerDecHlt2DiMuonB;   //!
   TBranch        *b_TriggerDecHlt2DiMuonZ;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY1;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY2;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY3;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDY4;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetached;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetachedHeavy;   //!
   TBranch        *b_TriggerDecHlt2DiMuonDetachedJPsi;   //!
   TBranch        *b_TriggerDecHlt2DiMuonNoPV;   //!
   TBranch        *b_TriggerDecHlt2TriMuonDetached;   //!
   TBranch        *b_TriggerDecHlt2TriMuonTau;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHH;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HHHHWideMass;   //!
   TBranch        *b_TriggerDecHlt2ErrorEvent;   //!
   TBranch        *b_TriggerDecHlt2Global;   //!
   TBranch        *b_TriggerDecHlt2B2HHLTUnbiased;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02PiPi;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02PiPiWideMass;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KK;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KKWideMass;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KPi;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD02HH_D02KPiWideMass;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0H_D2KS0Pi;   //!
   TBranch        *b_TriggerDecHlt2CharmHadD2KS0H_D2KS0K;   //!
   TBranch        *b_TriggerDecHlt2DiProton;   //!
   TBranch        *b_TriggerDecHlt2DiProtonTF;   //!
   TBranch        *b_TriggerDecHlt2DiProtonLowMult;   //!
   TBranch        *b_TriggerDecHlt2DiProtonLowMultTF;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWS;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWS;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNu;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNu;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD2HMuMu;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD2HMuMuWideMass;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMu;   //!
   TBranch        *b_TriggerDecHlt2CharmSemilepD02HHMuMuWideMass;   //!
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
   TBranch        *b_truetau;   //!
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
   TBranch        *b_BPVLTIME225;   //!
   TBranch        *b_minPIDmupi;   //!
   TBranch        *b_minPIDmuk;   //!
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
   TBranch        *b_truermass_p0p2;   //!
   TBranch        *b_truermass_p1p2;   //!
   TBranch        *b_truermass_p0p1;   //!
   TBranch        *b_mass_Kpipi;   //!
   TBranch        *b_mass_KKpi1;   //!
   TBranch        *b_mass_KKpi2;   //!
   TBranch        *b_mass_3pi;   //!
   TBranch        *b_Dalitz_m12;   //!
   TBranch        *b_Dalitz_m23;   //!
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
   TBranch        *b_ptorderedp0_IPSig;   //!
   TBranch        *b_ptorderedp1_IPSig;   //!
   TBranch        *b_ptorderedp2_IPSig;   //!
   TBranch        *b_ptorderedp0_pt;   //!
   TBranch        *b_ptorderedp1_pt;   //!
   TBranch        *b_ptorderedp2_pt;   //!
   TBranch        *b_ptorderedp0_p0_track_Chi2Dof;   //!
   TBranch        *b_ptorderedp1_p1_track_Chi2Dof;   //!
   TBranch        *b_ptorderedp2_p2_track_Chi2Dof;   //!
   TBranch        *b_ptorderedp0_PIDmupi;   //!
   TBranch        *b_ptorderedp1_PIDmupi;   //!
   TBranch        *b_ptorderedp2_PIDmupi;   //!
   TBranch        *b_ptorderedp0_PIDmuk;   //!
   TBranch        *b_ptorderedp1_PIDmuk;   //!
   TBranch        *b_ptorderedp2_PIDmuk;   //!
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
   TBranch        *b_PIDMVA;   //!
   TBranch        *b_noptPIDMVA;   //!
   TBranch        *b_GeoMVA;   //!
   TBranch        *b_geomvacheck;   //!
   TBranch        *b_GeoMVA_pol;   //!
   TBranch        *b_GeoMVA_dimu;   //!
   TBranch        *b_GeoMVA_poldimu;   //!
   TBranch        *b_Dalitz;   //!
   TBranch        *b_Dalitz_glcut;   //!
   TBranch        *b_Dalitz_eta;   //!
   TBranch        *b_Dalitz_cat;   //!
   TBranch        *b_smeared_Dalitz;   //!
   TBranch        *b_smeared_Dalitz_glcut;   //!
   TBranch        *b_smeared_Dalitz_eta;   //!
   TBranch        *b_smeared_Dalitz_cat;   //!
   TBranch        *b_BCK;   //!
   TBranch        *b_tauproduction;   //!
   TBranch        *b_productionweightMC10;   //!
   TBranch        *b_productionweighterrorMC10;   //!
   TBranch        *b_productionweightMC11;   //!
   TBranch        *b_productionweighterrorMC11;   //!
   TBranch        *b_productionweightMC11v2;   //!
   TBranch        *b_productionweighterrorMC11v2;   //!
   TBranch        *b_productionweightMC11v3;   //!
   TBranch        *b_productionweighterrorMC11v3;   //!
   TBranch        *b_production;   //!
   TBranch        *b_EventHash;   //!
   TBranch        *b_p0_cloneDist;   //!
   TBranch        *b_p1_cloneDist;   //!
   TBranch        *b_p2_cloneDist;   //!
   TBranch        *b_p0_track_Chi2Dof;   //!
   TBranch        *b_p1_track_Chi2Dof;   //!
   TBranch        *b_p2_track_Chi2Dof;   //!
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
   TBranch        *b_p0_singlePID;   //!
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
   TBranch        *b_p0_mcpid;   //!
   TBranch        *b_p0_ghostcat;   //!
   TBranch        *b_p0_trackhistory;   //!
   TBranch        *b_p0_IP;   //!
   TBranch        *b_p0_IPSig;   //!
   TBranch        *b_p0_largestMClifetime;   //!
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
   TBranch        *b_p1_singlePID;   //!
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
   TBranch        *b_p1_mcpid;   //!
   TBranch        *b_p1_ghostcat;   //!
   TBranch        *b_p1_trackhistory;   //!
   TBranch        *b_p1_IP;   //!
   TBranch        *b_p1_IPSig;   //!
   TBranch        *b_p1_largestMClifetime;   //!
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
   TBranch        *b_p2_singlePID;   //!
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
   TBranch        *b_NeuroBayes_0x109cf818;   //!
   TBranch        *b_NeuroBayes_0x119cf818;   //!
   TBranch        *b_NeuroBayes_0x129cf818;   //!
   TBranch        *b_NeuroBayes_0x141cf818;   //!
   TBranch        *b_NeuroBayes_0x143cf818;   //!
   TBranch        *b_NeuroBayes_0x145cf818;   //!
   TBranch        *b_NeuroBayes_0x149c1818;   //!
   TBranch        *b_NeuroBayes_0x149ce018;   //!
   TBranch        *b_NeuroBayes_0x149ce718;   //!
   TBranch        *b_NeuroBayes_0x149cf818;   //!
   TBranch        *b_NeuroBayes_0x149d1818;   //!
   TBranch        *b_NeuroBayes_0x1c9cf818;   //!

   flat(TTree *tree=0);
   virtual ~flat();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef flat_cxx
flat::flat(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mc_MC10tau23mu_UP_TRUTHATTEMPT_sm0_flat_83099evts.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("mc_MC10tau23mu_UP_TRUTHATTEMPT_sm0_flat_83099evts.root");
      }
      f->GetObject("Tau23Mu",tree);

   }
   Init(tree);
}

flat::~flat()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t flat::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t flat::LoadTree(Long64_t entry)
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

void flat::Init(TTree *tree)
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
   fChain->SetBranchAddress("Strip15And17", &Strip15And17, &b_Strip15And17);
   fChain->SetBranchAddress("cleaningcut", &cleaningcut, &b_cleaningcut);
   fChain->SetBranchAddress("jonpid", &jonpid, &b_jonpid);
   fChain->SetBranchAddress("jongeo", &jongeo, &b_jongeo);
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
   fChain->SetBranchAddress("TriggerDecHlt1DiMuonHighMass", &TriggerDecHlt1DiMuonHighMass, &b_TriggerDecHlt1DiMuonHighMass);
   fChain->SetBranchAddress("TriggerDecHlt1DiMuonLowMass", &TriggerDecHlt1DiMuonLowMass, &b_TriggerDecHlt1DiMuonLowMass);
   fChain->SetBranchAddress("TriggerDecHlt1SingleMuonNoIP", &TriggerDecHlt1SingleMuonNoIP, &b_TriggerDecHlt1SingleMuonNoIP);
   fChain->SetBranchAddress("TriggerDecHlt1SingleMuonHighPT", &TriggerDecHlt1SingleMuonHighPT, &b_TriggerDecHlt1SingleMuonHighPT);
   fChain->SetBranchAddress("TriggerDecHlt1TrackAllL0", &TriggerDecHlt1TrackAllL0, &b_TriggerDecHlt1TrackAllL0);
   fChain->SetBranchAddress("TriggerDecHlt1TrackMuon", &TriggerDecHlt1TrackMuon, &b_TriggerDecHlt1TrackMuon);
   fChain->SetBranchAddress("TriggerDecHlt1TrackPhoton", &TriggerDecHlt1TrackPhoton, &b_TriggerDecHlt1TrackPhoton);
   fChain->SetBranchAddress("TriggerDecHlt1Lumi", &TriggerDecHlt1Lumi, &b_TriggerDecHlt1Lumi);
   fChain->SetBranchAddress("TriggerDecHlt1LumiMidBeamCrossing", &TriggerDecHlt1LumiMidBeamCrossing, &b_TriggerDecHlt1LumiMidBeamCrossing);
   fChain->SetBranchAddress("TriggerDecHlt1MBNoBias", &TriggerDecHlt1MBNoBias, &b_TriggerDecHlt1MBNoBias);
   fChain->SetBranchAddress("TriggerDecHlt1L0Any", &TriggerDecHlt1L0Any, &b_TriggerDecHlt1L0Any);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyRateLimited", &TriggerDecHlt1L0AnyRateLimited, &b_TriggerDecHlt1L0AnyRateLimited);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyNoSPD", &TriggerDecHlt1L0AnyNoSPD, &b_TriggerDecHlt1L0AnyNoSPD);
   fChain->SetBranchAddress("TriggerDecHlt1L0AnyNoSPDRateLimited", &TriggerDecHlt1L0AnyNoSPDRateLimited, &b_TriggerDecHlt1L0AnyNoSPDRateLimited);
   fChain->SetBranchAddress("TriggerDecHlt1NoPVPassThrough", &TriggerDecHlt1NoPVPassThrough, &b_TriggerDecHlt1NoPVPassThrough);
   fChain->SetBranchAddress("TriggerDecHlt1DiProtonLowMult", &TriggerDecHlt1DiProtonLowMult, &b_TriggerDecHlt1DiProtonLowMult);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasNoBeamBeam1", &TriggerDecHlt1BeamGasNoBeamBeam1, &b_TriggerDecHlt1BeamGasNoBeamBeam1);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasNoBeamBeam2", &TriggerDecHlt1BeamGasNoBeamBeam2, &b_TriggerDecHlt1BeamGasNoBeamBeam2);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasBeam1", &TriggerDecHlt1BeamGasBeam1, &b_TriggerDecHlt1BeamGasBeam1);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasBeam2", &TriggerDecHlt1BeamGasBeam2, &b_TriggerDecHlt1BeamGasBeam2);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingEnhancedBeam1", &TriggerDecHlt1BeamGasCrossingEnhancedBeam1, &b_TriggerDecHlt1BeamGasCrossingEnhancedBeam1);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingEnhancedBeam2", &TriggerDecHlt1BeamGasCrossingEnhancedBeam2, &b_TriggerDecHlt1BeamGasCrossingEnhancedBeam2);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingForcedReco", &TriggerDecHlt1BeamGasCrossingForcedReco, &b_TriggerDecHlt1BeamGasCrossingForcedReco);
   fChain->SetBranchAddress("TriggerDecHlt1ODINTechnical", &TriggerDecHlt1ODINTechnical, &b_TriggerDecHlt1ODINTechnical);
   fChain->SetBranchAddress("TriggerDecHlt1Tell1Error", &TriggerDecHlt1Tell1Error, &b_TriggerDecHlt1Tell1Error);
   fChain->SetBranchAddress("TriggerDecHlt1BeamGasCrossingParasitic", &TriggerDecHlt1BeamGasCrossingParasitic, &b_TriggerDecHlt1BeamGasCrossingParasitic);
   fChain->SetBranchAddress("TriggerDecHlt1ErrorEvent", &TriggerDecHlt1ErrorEvent, &b_TriggerDecHlt1ErrorEvent);
   fChain->SetBranchAddress("TriggerDecHlt1Global", &TriggerDecHlt1Global, &b_TriggerDecHlt1Global);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasVelo", &TriggerDecHlt1MBMicroBiasVelo, &b_TriggerDecHlt1MBMicroBiasVelo);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasVeloRateLimited", &TriggerDecHlt1MBMicroBiasVeloRateLimited, &b_TriggerDecHlt1MBMicroBiasVeloRateLimited);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasTStation", &TriggerDecHlt1MBMicroBiasTStation, &b_TriggerDecHlt1MBMicroBiasTStation);
   fChain->SetBranchAddress("TriggerDecHlt1MBMicroBiasTStationRateLimited", &TriggerDecHlt1MBMicroBiasTStationRateLimited, &b_TriggerDecHlt1MBMicroBiasTStationRateLimited);
   fChain->SetBranchAddress("TriggerDecHlt1DiProton", &TriggerDecHlt1DiProton, &b_TriggerDecHlt1DiProton);
   fChain->SetBranchAddress("TriggerDecHlt1VeloClosingMicroBias", &TriggerDecHlt1VeloClosingMicroBias, &b_TriggerDecHlt1VeloClosingMicroBias);
   fChain->SetBranchAddress("TriggerDecHlt2SingleElectronTFLowPt", &TriggerDecHlt2SingleElectronTFLowPt, &b_TriggerDecHlt2SingleElectronTFLowPt);
   fChain->SetBranchAddress("TriggerDecHlt2SingleElectronTFHighPt", &TriggerDecHlt2SingleElectronTFHighPt, &b_TriggerDecHlt2SingleElectronTFHighPt);
   fChain->SetBranchAddress("TriggerDecHlt2DiElectronHighMass", &TriggerDecHlt2DiElectronHighMass, &b_TriggerDecHlt2DiElectronHighMass);
   fChain->SetBranchAddress("TriggerDecHlt2DiElectronB", &TriggerDecHlt2DiElectronB, &b_TriggerDecHlt2DiElectronB);
   fChain->SetBranchAddress("TriggerDecHlt2Topo2BodySimple", &TriggerDecHlt2Topo2BodySimple, &b_TriggerDecHlt2Topo2BodySimple);
   fChain->SetBranchAddress("TriggerDecHlt2Topo3BodySimple", &TriggerDecHlt2Topo3BodySimple, &b_TriggerDecHlt2Topo3BodySimple);
   fChain->SetBranchAddress("TriggerDecHlt2Topo4BodySimple", &TriggerDecHlt2Topo4BodySimple, &b_TriggerDecHlt2Topo4BodySimple);
   fChain->SetBranchAddress("TriggerDecHlt2Topo2BodyBBDT", &TriggerDecHlt2Topo2BodyBBDT, &b_TriggerDecHlt2Topo2BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2Topo3BodyBBDT", &TriggerDecHlt2Topo3BodyBBDT, &b_TriggerDecHlt2Topo3BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2Topo4BodyBBDT", &TriggerDecHlt2Topo4BodyBBDT, &b_TriggerDecHlt2Topo4BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2TopoMu2BodyBBDT", &TriggerDecHlt2TopoMu2BodyBBDT, &b_TriggerDecHlt2TopoMu2BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2TopoMu3BodyBBDT", &TriggerDecHlt2TopoMu3BodyBBDT, &b_TriggerDecHlt2TopoMu3BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2TopoMu4BodyBBDT", &TriggerDecHlt2TopoMu4BodyBBDT, &b_TriggerDecHlt2TopoMu4BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2TopoE2BodyBBDT", &TriggerDecHlt2TopoE2BodyBBDT, &b_TriggerDecHlt2TopoE2BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2TopoE3BodyBBDT", &TriggerDecHlt2TopoE3BodyBBDT, &b_TriggerDecHlt2TopoE3BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2TopoE4BodyBBDT", &TriggerDecHlt2TopoE4BodyBBDT, &b_TriggerDecHlt2TopoE4BodyBBDT);
   fChain->SetBranchAddress("TriggerDecHlt2IncPhi", &TriggerDecHlt2IncPhi, &b_TriggerDecHlt2IncPhi);
   fChain->SetBranchAddress("TriggerDecHlt2IncPhiSidebands", &TriggerDecHlt2IncPhiSidebands, &b_TriggerDecHlt2IncPhiSidebands);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHKsLL", &TriggerDecHlt2CharmHadD02HHKsLL, &b_TriggerDecHlt2CharmHadD02HHKsLL);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02PiPi", &TriggerDecHlt2Dst2PiD02PiPi, &b_TriggerDecHlt2Dst2PiD02PiPi);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02MuMu", &TriggerDecHlt2Dst2PiD02MuMu, &b_TriggerDecHlt2Dst2PiD02MuMu);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02KMu", &TriggerDecHlt2Dst2PiD02KMu, &b_TriggerDecHlt2Dst2PiD02KMu);
   fChain->SetBranchAddress("TriggerDecHlt2Dst2PiD02KPi", &TriggerDecHlt2Dst2PiD02KPi, &b_TriggerDecHlt2Dst2PiD02KPi);
   fChain->SetBranchAddress("TriggerDecHlt2PassThrough", &TriggerDecHlt2PassThrough, &b_TriggerDecHlt2PassThrough);
   fChain->SetBranchAddress("TriggerDecHlt2Transparent", &TriggerDecHlt2Transparent, &b_TriggerDecHlt2Transparent);
   fChain->SetBranchAddress("TriggerDecHlt2Forward", &TriggerDecHlt2Forward, &b_TriggerDecHlt2Forward);
   fChain->SetBranchAddress("TriggerDecHlt2DebugEvent", &TriggerDecHlt2DebugEvent, &b_TriggerDecHlt2DebugEvent);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KK", &TriggerDecHlt2CharmHadD02KK, &b_TriggerDecHlt2CharmHadD02KK);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KKWideMass", &TriggerDecHlt2CharmHadD02KKWideMass, &b_TriggerDecHlt2CharmHadD02KKWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KPi", &TriggerDecHlt2CharmHadD02KPi, &b_TriggerDecHlt2CharmHadD02KPi);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02KPiWideMass", &TriggerDecHlt2CharmHadD02KPiWideMass, &b_TriggerDecHlt2CharmHadD02KPiWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02PiPi", &TriggerDecHlt2CharmHadD02PiPi, &b_TriggerDecHlt2CharmHadD02PiPi);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02PiPiWideMass", &TriggerDecHlt2CharmHadD02PiPiWideMass, &b_TriggerDecHlt2CharmHadD02PiPiWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressJPsi", &TriggerDecHlt2ExpressJPsi, &b_TriggerDecHlt2ExpressJPsi);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressJPsiTagProbe", &TriggerDecHlt2ExpressJPsiTagProbe, &b_TriggerDecHlt2ExpressJPsiTagProbe);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressLambda", &TriggerDecHlt2ExpressLambda, &b_TriggerDecHlt2ExpressLambda);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressKS", &TriggerDecHlt2ExpressKS, &b_TriggerDecHlt2ExpressKS);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressDs2PhiPi", &TriggerDecHlt2ExpressDs2PhiPi, &b_TriggerDecHlt2ExpressDs2PhiPi);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressBeamHalo", &TriggerDecHlt2ExpressBeamHalo, &b_TriggerDecHlt2ExpressBeamHalo);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressDStar2D0Pi", &TriggerDecHlt2ExpressDStar2D0Pi, &b_TriggerDecHlt2ExpressDStar2D0Pi);
   fChain->SetBranchAddress("TriggerDecHlt2ExpressHLT1Physics", &TriggerDecHlt2ExpressHLT1Physics, &b_TriggerDecHlt2ExpressHLT1Physics);
   fChain->SetBranchAddress("TriggerDecHlt2Bs2PhiGamma", &TriggerDecHlt2Bs2PhiGamma, &b_TriggerDecHlt2Bs2PhiGamma);
   fChain->SetBranchAddress("TriggerDecHlt2Bs2PhiGammaWideBMass", &TriggerDecHlt2Bs2PhiGammaWideBMass, &b_TriggerDecHlt2Bs2PhiGammaWideBMass);
   fChain->SetBranchAddress("TriggerDecHlt2Bd2KstGamma", &TriggerDecHlt2Bd2KstGamma, &b_TriggerDecHlt2Bd2KstGamma);
   fChain->SetBranchAddress("TriggerDecHlt2Bd2KstGammaWideKMass", &TriggerDecHlt2Bd2KstGammaWideKMass, &b_TriggerDecHlt2Bd2KstGammaWideKMass);
   fChain->SetBranchAddress("TriggerDecHlt2Bd2KstGammaWideBMass", &TriggerDecHlt2Bd2KstGammaWideBMass, &b_TriggerDecHlt2Bd2KstGammaWideBMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0Pi", &TriggerDecHlt2CharmHadD2KS0Pi, &b_TriggerDecHlt2CharmHadD2KS0Pi);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0K", &TriggerDecHlt2CharmHadD2KS0K, &b_TriggerDecHlt2CharmHadD2KS0K);
   fChain->SetBranchAddress("TriggerDecHlt2CharmRareDecayD02MuMu", &TriggerDecHlt2CharmRareDecayD02MuMu, &b_TriggerDecHlt2CharmRareDecayD02MuMu);
   fChain->SetBranchAddress("TriggerDecHlt2B2HH", &TriggerDecHlt2B2HH, &b_TriggerDecHlt2B2HH);
   fChain->SetBranchAddress("TriggerDecHlt2MuonFromHLT1", &TriggerDecHlt2MuonFromHLT1, &b_TriggerDecHlt2MuonFromHLT1);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuon", &TriggerDecHlt2SingleMuon, &b_TriggerDecHlt2SingleMuon);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuonHighPT", &TriggerDecHlt2SingleMuonHighPT, &b_TriggerDecHlt2SingleMuonHighPT);
   fChain->SetBranchAddress("TriggerDecHlt2SingleMuonLowPT", &TriggerDecHlt2SingleMuonLowPT, &b_TriggerDecHlt2SingleMuonLowPT);
   fChain->SetBranchAddress("TriggerDecHlt2TFBc2JpsiMuX", &TriggerDecHlt2TFBc2JpsiMuX, &b_TriggerDecHlt2TFBc2JpsiMuX);
   fChain->SetBranchAddress("TriggerDecHlt2TFBc2JpsiMuXSignal", &TriggerDecHlt2TFBc2JpsiMuXSignal, &b_TriggerDecHlt2TFBc2JpsiMuXSignal);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesLowMassSingle", &TriggerDecHlt2DisplVerticesLowMassSingle, &b_TriggerDecHlt2DisplVerticesLowMassSingle);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesHighMassSingle", &TriggerDecHlt2DisplVerticesHighMassSingle, &b_TriggerDecHlt2DisplVerticesHighMassSingle);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesDouble", &TriggerDecHlt2DisplVerticesDouble, &b_TriggerDecHlt2DisplVerticesDouble);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSinglePostScaled", &TriggerDecHlt2DisplVerticesSinglePostScaled, &b_TriggerDecHlt2DisplVerticesSinglePostScaled);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesHighFDSingle", &TriggerDecHlt2DisplVerticesHighFDSingle, &b_TriggerDecHlt2DisplVerticesHighFDSingle);
   fChain->SetBranchAddress("TriggerDecHlt2DisplVerticesSingleDown", &TriggerDecHlt2DisplVerticesSingleDown, &b_TriggerDecHlt2DisplVerticesSingleDown);
   fChain->SetBranchAddress("TriggerDecHlt2B2HHPi0_Merged", &TriggerDecHlt2B2HHPi0_Merged, &b_TriggerDecHlt2B2HHPi0_Merged);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2HHH", &TriggerDecHlt2CharmHadD2HHH, &b_TriggerDecHlt2CharmHadD2HHH);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2HHHWideMass", &TriggerDecHlt2CharmHadD2HHHWideMass, &b_TriggerDecHlt2CharmHadD2HHHWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuon", &TriggerDecHlt2DiMuon, &b_TriggerDecHlt2DiMuon);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonLowMass", &TriggerDecHlt2DiMuonLowMass, &b_TriggerDecHlt2DiMuonLowMass);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonJPsi", &TriggerDecHlt2DiMuonJPsi, &b_TriggerDecHlt2DiMuonJPsi);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonJPsiHighPT", &TriggerDecHlt2DiMuonJPsiHighPT, &b_TriggerDecHlt2DiMuonJPsiHighPT);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonPsi2S", &TriggerDecHlt2DiMuonPsi2S, &b_TriggerDecHlt2DiMuonPsi2S);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonB", &TriggerDecHlt2DiMuonB, &b_TriggerDecHlt2DiMuonB);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonZ", &TriggerDecHlt2DiMuonZ, &b_TriggerDecHlt2DiMuonZ);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY1", &TriggerDecHlt2DiMuonDY1, &b_TriggerDecHlt2DiMuonDY1);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY2", &TriggerDecHlt2DiMuonDY2, &b_TriggerDecHlt2DiMuonDY2);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY3", &TriggerDecHlt2DiMuonDY3, &b_TriggerDecHlt2DiMuonDY3);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDY4", &TriggerDecHlt2DiMuonDY4, &b_TriggerDecHlt2DiMuonDY4);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetached", &TriggerDecHlt2DiMuonDetached, &b_TriggerDecHlt2DiMuonDetached);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetachedHeavy", &TriggerDecHlt2DiMuonDetachedHeavy, &b_TriggerDecHlt2DiMuonDetachedHeavy);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonDetachedJPsi", &TriggerDecHlt2DiMuonDetachedJPsi, &b_TriggerDecHlt2DiMuonDetachedJPsi);
   fChain->SetBranchAddress("TriggerDecHlt2DiMuonNoPV", &TriggerDecHlt2DiMuonNoPV, &b_TriggerDecHlt2DiMuonNoPV);
   fChain->SetBranchAddress("TriggerDecHlt2TriMuonDetached", &TriggerDecHlt2TriMuonDetached, &b_TriggerDecHlt2TriMuonDetached);
   fChain->SetBranchAddress("TriggerDecHlt2TriMuonTau", &TriggerDecHlt2TriMuonTau, &b_TriggerDecHlt2TriMuonTau);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHH", &TriggerDecHlt2CharmHadD02HHHH, &b_TriggerDecHlt2CharmHadD02HHHH);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HHHHWideMass", &TriggerDecHlt2CharmHadD02HHHHWideMass, &b_TriggerDecHlt2CharmHadD02HHHHWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2ErrorEvent", &TriggerDecHlt2ErrorEvent, &b_TriggerDecHlt2ErrorEvent);
   fChain->SetBranchAddress("TriggerDecHlt2Global", &TriggerDecHlt2Global, &b_TriggerDecHlt2Global);
   fChain->SetBranchAddress("TriggerDecHlt2B2HHLTUnbiased", &TriggerDecHlt2B2HHLTUnbiased, &b_TriggerDecHlt2B2HHLTUnbiased);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02PiPi", &TriggerDecHlt2CharmHadD02HH_D02PiPi, &b_TriggerDecHlt2CharmHadD02HH_D02PiPi);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02PiPiWideMass", &TriggerDecHlt2CharmHadD02HH_D02PiPiWideMass, &b_TriggerDecHlt2CharmHadD02HH_D02PiPiWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KK", &TriggerDecHlt2CharmHadD02HH_D02KK, &b_TriggerDecHlt2CharmHadD02HH_D02KK);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KKWideMass", &TriggerDecHlt2CharmHadD02HH_D02KKWideMass, &b_TriggerDecHlt2CharmHadD02HH_D02KKWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KPi", &TriggerDecHlt2CharmHadD02HH_D02KPi, &b_TriggerDecHlt2CharmHadD02HH_D02KPi);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD02HH_D02KPiWideMass", &TriggerDecHlt2CharmHadD02HH_D02KPiWideMass, &b_TriggerDecHlt2CharmHadD02HH_D02KPiWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0H_D2KS0Pi", &TriggerDecHlt2CharmHadD2KS0H_D2KS0Pi, &b_TriggerDecHlt2CharmHadD2KS0H_D2KS0Pi);
   fChain->SetBranchAddress("TriggerDecHlt2CharmHadD2KS0H_D2KS0K", &TriggerDecHlt2CharmHadD2KS0H_D2KS0K, &b_TriggerDecHlt2CharmHadD2KS0H_D2KS0K);
   fChain->SetBranchAddress("TriggerDecHlt2DiProton", &TriggerDecHlt2DiProton, &b_TriggerDecHlt2DiProton);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonTF", &TriggerDecHlt2DiProtonTF, &b_TriggerDecHlt2DiProtonTF);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonLowMult", &TriggerDecHlt2DiProtonLowMult, &b_TriggerDecHlt2DiProtonLowMult);
   fChain->SetBranchAddress("TriggerDecHlt2DiProtonLowMultTF", &TriggerDecHlt2DiProtonLowMultTF, &b_TriggerDecHlt2DiProtonLowMultTF);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWS", &TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWS, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWS);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWS", &TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWS, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWS);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNu", &TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNu, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNu);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNu", &TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNu, &b_TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNu);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD2HMuMu", &TriggerDecHlt2CharmSemilepD2HMuMu, &b_TriggerDecHlt2CharmSemilepD2HMuMu);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD2HMuMuWideMass", &TriggerDecHlt2CharmSemilepD2HMuMuWideMass, &b_TriggerDecHlt2CharmSemilepD2HMuMuWideMass);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMu", &TriggerDecHlt2CharmSemilepD02HHMuMu, &b_TriggerDecHlt2CharmSemilepD02HHMuMu);
   fChain->SetBranchAddress("TriggerDecHlt2CharmSemilepD02HHMuMuWideMass", &TriggerDecHlt2CharmSemilepD02HHMuMuWideMass, &b_TriggerDecHlt2CharmSemilepD02HHMuMuWideMass);
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
   fChain->SetBranchAddress("truetau", &truetau, &b_truetau);
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
   fChain->SetBranchAddress("BPVLTIME225", &BPVLTIME225, &b_BPVLTIME225);
   fChain->SetBranchAddress("minPIDmupi", &minPIDmupi, &b_minPIDmupi);
   fChain->SetBranchAddress("minPIDmuk", &minPIDmuk, &b_minPIDmuk);
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
   fChain->SetBranchAddress("truermass_p0p2", &truermass_p0p2, &b_truermass_p0p2);
   fChain->SetBranchAddress("truermass_p1p2", &truermass_p1p2, &b_truermass_p1p2);
   fChain->SetBranchAddress("truermass_p0p1", &truermass_p0p1, &b_truermass_p0p1);
   fChain->SetBranchAddress("mass_Kpipi", &mass_Kpipi, &b_mass_Kpipi);
   fChain->SetBranchAddress("mass_KKpi1", &mass_KKpi1, &b_mass_KKpi1);
   fChain->SetBranchAddress("mass_KKpi2", &mass_KKpi2, &b_mass_KKpi2);
   fChain->SetBranchAddress("mass_3pi", &mass_3pi, &b_mass_3pi);
   fChain->SetBranchAddress("Dalitz_m12", &Dalitz_m12, &b_Dalitz_m12);
   fChain->SetBranchAddress("Dalitz_m23", &Dalitz_m23, &b_Dalitz_m23);
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
   fChain->SetBranchAddress("ptorderedp0_IPSig", &ptorderedp0_IPSig, &b_ptorderedp0_IPSig);
   fChain->SetBranchAddress("ptorderedp1_IPSig", &ptorderedp1_IPSig, &b_ptorderedp1_IPSig);
   fChain->SetBranchAddress("ptorderedp2_IPSig", &ptorderedp2_IPSig, &b_ptorderedp2_IPSig);
   fChain->SetBranchAddress("ptorderedp0_pt", &ptorderedp0_pt, &b_ptorderedp0_pt);
   fChain->SetBranchAddress("ptorderedp1_pt", &ptorderedp1_pt, &b_ptorderedp1_pt);
   fChain->SetBranchAddress("ptorderedp2_pt", &ptorderedp2_pt, &b_ptorderedp2_pt);
   fChain->SetBranchAddress("ptorderedp0_p0_track_Chi2Dof", &ptorderedp0_p0_track_Chi2Dof, &b_ptorderedp0_p0_track_Chi2Dof);
   fChain->SetBranchAddress("ptorderedp1_p1_track_Chi2Dof", &ptorderedp1_p1_track_Chi2Dof, &b_ptorderedp1_p1_track_Chi2Dof);
   fChain->SetBranchAddress("ptorderedp2_p2_track_Chi2Dof", &ptorderedp2_p2_track_Chi2Dof, &b_ptorderedp2_p2_track_Chi2Dof);
   fChain->SetBranchAddress("ptorderedp0_PIDmupi", &ptorderedp0_PIDmupi, &b_ptorderedp0_PIDmupi);
   fChain->SetBranchAddress("ptorderedp1_PIDmupi", &ptorderedp1_PIDmupi, &b_ptorderedp1_PIDmupi);
   fChain->SetBranchAddress("ptorderedp2_PIDmupi", &ptorderedp2_PIDmupi, &b_ptorderedp2_PIDmupi);
   fChain->SetBranchAddress("ptorderedp0_PIDmuk", &ptorderedp0_PIDmuk, &b_ptorderedp0_PIDmuk);
   fChain->SetBranchAddress("ptorderedp1_PIDmuk", &ptorderedp1_PIDmuk, &b_ptorderedp1_PIDmuk);
   fChain->SetBranchAddress("ptorderedp2_PIDmuk", &ptorderedp2_PIDmuk, &b_ptorderedp2_PIDmuk);
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
   fChain->SetBranchAddress("PIDMVA", &PIDMVA, &b_PIDMVA);
   fChain->SetBranchAddress("noptPIDMVA", &noptPIDMVA, &b_noptPIDMVA);
   fChain->SetBranchAddress("GeoMVA", &GeoMVA, &b_GeoMVA);
   fChain->SetBranchAddress("geomvacheck", &geomvacheck, &b_geomvacheck);
   fChain->SetBranchAddress("GeoMVA_pol", &GeoMVA_pol, &b_GeoMVA_pol);
   fChain->SetBranchAddress("GeoMVA_dimu", &GeoMVA_dimu, &b_GeoMVA_dimu);
   fChain->SetBranchAddress("GeoMVA_poldimu", &GeoMVA_poldimu, &b_GeoMVA_poldimu);
   fChain->SetBranchAddress("Dalitz", &Dalitz, &b_Dalitz);
   fChain->SetBranchAddress("Dalitz_glcut", &Dalitz_glcut, &b_Dalitz_glcut);
   fChain->SetBranchAddress("Dalitz_eta", &Dalitz_eta, &b_Dalitz_eta);
   fChain->SetBranchAddress("Dalitz_cat", &Dalitz_cat, &b_Dalitz_cat);
   fChain->SetBranchAddress("smeared_Dalitz", &smeared_Dalitz, &b_smeared_Dalitz);
   fChain->SetBranchAddress("smeared_Dalitz_glcut", &smeared_Dalitz_glcut, &b_smeared_Dalitz_glcut);
   fChain->SetBranchAddress("smeared_Dalitz_eta", &smeared_Dalitz_eta, &b_smeared_Dalitz_eta);
   fChain->SetBranchAddress("smeared_Dalitz_cat", &smeared_Dalitz_cat, &b_smeared_Dalitz_cat);
   fChain->SetBranchAddress("BCK", &BCK, &b_BCK);
   fChain->SetBranchAddress("tauproduction", &tauproduction, &b_tauproduction);
   fChain->SetBranchAddress("productionweightMC10", &productionweightMC10, &b_productionweightMC10);
   fChain->SetBranchAddress("productionweighterrorMC10", &productionweighterrorMC10, &b_productionweighterrorMC10);
   fChain->SetBranchAddress("productionweightMC11", &productionweightMC11, &b_productionweightMC11);
   fChain->SetBranchAddress("productionweighterrorMC11", &productionweighterrorMC11, &b_productionweighterrorMC11);
   fChain->SetBranchAddress("productionweightMC11v2", &productionweightMC11v2, &b_productionweightMC11v2);
   fChain->SetBranchAddress("productionweighterrorMC11v2", &productionweighterrorMC11v2, &b_productionweighterrorMC11v2);
   fChain->SetBranchAddress("productionweightMC11v3", &productionweightMC11v3, &b_productionweightMC11v3);
   fChain->SetBranchAddress("productionweighterrorMC11v3", &productionweighterrorMC11v3, &b_productionweighterrorMC11v3);
   fChain->SetBranchAddress("production", &production, &b_production);
   fChain->SetBranchAddress("EventHash", &EventHash, &b_EventHash);
   fChain->SetBranchAddress("p0_cloneDist", &p0_cloneDist, &b_p0_cloneDist);
   fChain->SetBranchAddress("p1_cloneDist", &p1_cloneDist, &b_p1_cloneDist);
   fChain->SetBranchAddress("p2_cloneDist", &p2_cloneDist, &b_p2_cloneDist);
   fChain->SetBranchAddress("p0_track_Chi2Dof", &p0_track_Chi2Dof, &b_p0_track_Chi2Dof);
   fChain->SetBranchAddress("p1_track_Chi2Dof", &p1_track_Chi2Dof, &b_p1_track_Chi2Dof);
   fChain->SetBranchAddress("p2_track_Chi2Dof", &p2_track_Chi2Dof, &b_p2_track_Chi2Dof);
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
   fChain->SetBranchAddress("p0_singlePID", &p0_singlePID, &b_p0_singlePID);
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
   fChain->SetBranchAddress("p0_mcpid", &p0_mcpid, &b_p0_mcpid);
   fChain->SetBranchAddress("p0_ghostcat", &p0_ghostcat, &b_p0_ghostcat);
   fChain->SetBranchAddress("p0_trackhistory", &p0_trackhistory, &b_p0_trackhistory);
   fChain->SetBranchAddress("p0_IP", &p0_IP, &b_p0_IP);
   fChain->SetBranchAddress("p0_IPSig", &p0_IPSig, &b_p0_IPSig);
   fChain->SetBranchAddress("p0_largestMClifetime", &p0_largestMClifetime, &b_p0_largestMClifetime);
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
   fChain->SetBranchAddress("p1_singlePID", &p1_singlePID, &b_p1_singlePID);
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
   fChain->SetBranchAddress("p1_mcpid", &p1_mcpid, &b_p1_mcpid);
   fChain->SetBranchAddress("p1_ghostcat", &p1_ghostcat, &b_p1_ghostcat);
   fChain->SetBranchAddress("p1_trackhistory", &p1_trackhistory, &b_p1_trackhistory);
   fChain->SetBranchAddress("p1_IP", &p1_IP, &b_p1_IP);
   fChain->SetBranchAddress("p1_IPSig", &p1_IPSig, &b_p1_IPSig);
   fChain->SetBranchAddress("p1_largestMClifetime", &p1_largestMClifetime, &b_p1_largestMClifetime);
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
   fChain->SetBranchAddress("p2_singlePID", &p2_singlePID, &b_p2_singlePID);
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
   fChain->SetBranchAddress("NeuroBayes_0x109cf818", &NeuroBayes_0x109cf818, &b_NeuroBayes_0x109cf818);
   fChain->SetBranchAddress("NeuroBayes_0x119cf818", &NeuroBayes_0x119cf818, &b_NeuroBayes_0x119cf818);
   fChain->SetBranchAddress("NeuroBayes_0x129cf818", &NeuroBayes_0x129cf818, &b_NeuroBayes_0x129cf818);
   fChain->SetBranchAddress("NeuroBayes_0x141cf818", &NeuroBayes_0x141cf818, &b_NeuroBayes_0x141cf818);
   fChain->SetBranchAddress("NeuroBayes_0x143cf818", &NeuroBayes_0x143cf818, &b_NeuroBayes_0x143cf818);
   fChain->SetBranchAddress("NeuroBayes_0x145cf818", &NeuroBayes_0x145cf818, &b_NeuroBayes_0x145cf818);
   fChain->SetBranchAddress("NeuroBayes_0x149c1818", &NeuroBayes_0x149c1818, &b_NeuroBayes_0x149c1818);
   fChain->SetBranchAddress("NeuroBayes_0x149ce018", &NeuroBayes_0x149ce018, &b_NeuroBayes_0x149ce018);
   fChain->SetBranchAddress("NeuroBayes_0x149ce718", &NeuroBayes_0x149ce718, &b_NeuroBayes_0x149ce718);
   fChain->SetBranchAddress("NeuroBayes_0x149cf818", &NeuroBayes_0x149cf818, &b_NeuroBayes_0x149cf818);
   fChain->SetBranchAddress("NeuroBayes_0x149d1818", &NeuroBayes_0x149d1818, &b_NeuroBayes_0x149d1818);
   fChain->SetBranchAddress("NeuroBayes_0x1c9cf818", &NeuroBayes_0x1c9cf818, &b_NeuroBayes_0x1c9cf818);
   Notify();
}

Bool_t flat::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void flat::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t flat::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef flat_cxx
