#define crack_cxx
#include "crack.h"
#include <TH2.h>
#include <algorithm>
#include <math.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "flathlt2.h"
#include "iostream"

float g_punzialpha = 2.;

float g_geocut = 0.05;
float g_pidcut = 0.10;

std::vector<crack_junkie> sigjun;
std::vector<crack_junkie> bkgjun;

bool crack::skip_event(bool sigmc) {
    if (sigmc&&(!(truetau==15))) return true;
    {
    bool a = !sigmc;
    bool b = (mass<1758.8&&mass>1748.8);
    bool c = (mass<1808.8&&mass>1798.8);
    bool d = b || c;
    bool e = !d;
    if (a&&e) return true;
    //if (!sigmc)&&(!((mass<1758.8&&mass>1748.8)||(mass<1808.8&&mass>1798.8))) return true;
    }
    if (!(cleaningcut)) return true;
    if (!(L0Dec)) return true;
    if (!(Hlt1Dec)) return true;
    if (!(cleaningcut)) return true;
    if (!(mass_p0p1>250.)) return true;
    if (!(fabs(mass_p0p2-1020.4)>20.)) return true;
    if (!(fabs(mass_p1p2-1020.4)>20.)) return true;
    if (std::min(p0_ANNmuon,std::min(p1_ANNmuon,p2_ANNmuon))<g_pidcut) return true;
    if (BLEND_MN_FLAT<g_geocut) return true;
    if (!(LifeTime<0.025&&LifeTime>-0.01)) return true;
    if (!(dira>0.99)) return true;
    return false;
}

std::vector<crack_junkie> crack::Loop(bool sigmc = true)
{
  //   In a ROOT session, you can do:
  //      Root > .L crack.C
  //      Root > crack t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  
  std::vector<crack_junkie> junkies;

  if (fChain == 0) return junkies;

  Long64_t nentries = fChain->GetEntriesFast();


  for (unsigned j = 0 ; j < index("maxindex") ; ++j) {
    crack_junkie junk;
    junk.reset();
    junkies.push_back(junk);
  }

  Long64_t nbytes = 0, nb = 0;
  float allentries = 0.;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    if (skip_event(sigmc)) continue;

    allentries += 1.;


    if (0.5 < TriggerTOSHlt2SingleElectronTFLowPtDecision) junkies[index("TriggerTOSHlt2SingleElectronTFLowPtDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleElectronTFHighPtDecision) junkies[index("TriggerTOSHlt2SingleElectronTFHighPtDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiElectronHighMassDecision) junkies[index("TriggerTOSHlt2DiElectronHighMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiElectronBDecision) junkies[index("TriggerTOSHlt2DiElectronBDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Topo2BodySimpleDecision) junkies[index("TriggerTOSHlt2Topo2BodySimpleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Topo3BodySimpleDecision) junkies[index("TriggerTOSHlt2Topo3BodySimpleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Topo4BodySimpleDecision) junkies[index("TriggerTOSHlt2Topo4BodySimpleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Topo2BodyBBDTDecision) junkies[index("TriggerTOSHlt2Topo2BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Topo3BodyBBDTDecision) junkies[index("TriggerTOSHlt2Topo3BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Topo4BodyBBDTDecision) junkies[index("TriggerTOSHlt2Topo4BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoMu2BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoMu2BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoMu3BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoMu3BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoMu4BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoMu4BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoE2BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoE2BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoE3BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoE3BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoE4BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoE4BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2IncPhiDecision) junkies[index("TriggerTOSHlt2IncPhiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2IncPhiSidebandsDecision) junkies[index("TriggerTOSHlt2IncPhiSidebandsDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHKsLLDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHKsLLDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Dst2PiD02PiPiDecision) junkies[index("TriggerTOSHlt2Dst2PiD02PiPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Dst2PiD02MuMuDecision) junkies[index("TriggerTOSHlt2Dst2PiD02MuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Dst2PiD02KMuDecision) junkies[index("TriggerTOSHlt2Dst2PiD02KMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Dst2PiD02KPiDecision) junkies[index("TriggerTOSHlt2Dst2PiD02KPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2PassThroughDecision) junkies[index("TriggerTOSHlt2PassThroughDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TransparentDecision) junkies[index("TriggerTOSHlt2TransparentDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DebugEventDecision) junkies[index("TriggerTOSHlt2DebugEventDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02KKDecision) junkies[index("TriggerTOSHlt2CharmHadD02KKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02KKWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02KKWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02KPiDecision) junkies[index("TriggerTOSHlt2CharmHadD02KPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02KPiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02KPiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02PiPiDecision) junkies[index("TriggerTOSHlt2CharmHadD02PiPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02PiPiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02PiPiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2ExpressLambdaDecision) junkies[index("TriggerTOSHlt2ExpressLambdaDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2ExpressDs2PhiPiDecision) junkies[index("TriggerTOSHlt2ExpressDs2PhiPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2ExpressDStar2D0PiDecision) junkies[index("TriggerTOSHlt2ExpressDStar2D0PiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2ExpressHLT1PhysicsDecision) junkies[index("TriggerTOSHlt2ExpressHLT1PhysicsDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Bs2PhiGammaDecision) junkies[index("TriggerTOSHlt2Bs2PhiGammaDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Bs2PhiGammaWideBMassDecision) junkies[index("TriggerTOSHlt2Bs2PhiGammaWideBMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Bd2KstGammaDecision) junkies[index("TriggerTOSHlt2Bd2KstGammaDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Bd2KstGammaWideKMassDecision) junkies[index("TriggerTOSHlt2Bd2KstGammaWideKMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2Bd2KstGammaWideBMassDecision) junkies[index("TriggerTOSHlt2Bd2KstGammaWideBMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0PiDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0PiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0KDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0KDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmRareDecayD02MuMuDecision) junkies[index("TriggerTOSHlt2CharmRareDecayD02MuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2B2HHDecision) junkies[index("TriggerTOSHlt2B2HHDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2MuonFromHLT1Decision) junkies[index("TriggerTOSHlt2MuonFromHLT1Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleMuonDecision) junkies[index("TriggerTOSHlt2SingleMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleMuonHighPTDecision) junkies[index("TriggerTOSHlt2SingleMuonHighPTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleMuonLowPTDecision) junkies[index("TriggerTOSHlt2SingleMuonLowPTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TFBc2JpsiMuXDecision) junkies[index("TriggerTOSHlt2TFBc2JpsiMuXDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TFBc2JpsiMuXSignalDecision) junkies[index("TriggerTOSHlt2TFBc2JpsiMuXSignalDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesLowMassSingleDecision) junkies[index("TriggerTOSHlt2DisplVerticesLowMassSingleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesHighMassSingleDecision) junkies[index("TriggerTOSHlt2DisplVerticesHighMassSingleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesDoubleDecision) junkies[index("TriggerTOSHlt2DisplVerticesDoubleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSinglePostScaledDecision) junkies[index("TriggerTOSHlt2DisplVerticesSinglePostScaledDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesHighFDSingleDecision) junkies[index("TriggerTOSHlt2DisplVerticesHighFDSingleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleDownDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleDownDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2B2HHPi0_MergedDecision) junkies[index("TriggerTOSHlt2B2HHPi0_MergedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2HHHDecision) junkies[index("TriggerTOSHlt2CharmHadD2HHHDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2HHHWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD2HHHWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDecision) junkies[index("TriggerTOSHlt2DiMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonLowMassDecision) junkies[index("TriggerTOSHlt2DiMuonLowMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonJPsiDecision) junkies[index("TriggerTOSHlt2DiMuonJPsiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonJPsiHighPTDecision) junkies[index("TriggerTOSHlt2DiMuonJPsiHighPTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonPsi2SDecision) junkies[index("TriggerTOSHlt2DiMuonPsi2SDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonBDecision) junkies[index("TriggerTOSHlt2DiMuonBDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonZDecision) junkies[index("TriggerTOSHlt2DiMuonZDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDY1Decision) junkies[index("TriggerTOSHlt2DiMuonDY1Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDY2Decision) junkies[index("TriggerTOSHlt2DiMuonDY2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDY3Decision) junkies[index("TriggerTOSHlt2DiMuonDY3Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDY4Decision) junkies[index("TriggerTOSHlt2DiMuonDY4Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDetachedDecision) junkies[index("TriggerTOSHlt2DiMuonDetachedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDetachedHeavyDecision) junkies[index("TriggerTOSHlt2DiMuonDetachedHeavyDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDetachedJPsiDecision) junkies[index("TriggerTOSHlt2DiMuonDetachedJPsiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonNoPVDecision) junkies[index("TriggerTOSHlt2DiMuonNoPVDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TriMuonDetachedDecision) junkies[index("TriggerTOSHlt2TriMuonDetachedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TriMuonTauDecision) junkies[index("TriggerTOSHlt2TriMuonTauDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2ErrorEventDecision) junkies[index("TriggerTOSHlt2ErrorEventDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2B2HHLTUnbiasedDecision) junkies[index("TriggerTOSHlt2B2HHLTUnbiasedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KKDecision) junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KPiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiProtonDecision) junkies[index("TriggerTOSHlt2DiProtonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiProtonTFDecision) junkies[index("TriggerTOSHlt2DiProtonTFDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiProtonLowMultDecision) junkies[index("TriggerTOSHlt2DiProtonLowMultDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiProtonLowMultTFDecision) junkies[index("TriggerTOSHlt2DiProtonLowMultTFDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD2HMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD2HMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision) junkies[index("TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2diPhotonDiMuonDecision) junkies[index("TriggerTOSHlt2diPhotonDiMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultMuonDecision) junkies[index("TriggerTOSHlt2LowMultMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultHadronDecision) junkies[index("TriggerTOSHlt2LowMultHadronDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultPhotonDecision) junkies[index("TriggerTOSHlt2LowMultPhotonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultElectronDecision) junkies[index("TriggerTOSHlt2LowMultElectronDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleTFElectronDecision) junkies[index("TriggerTOSHlt2SingleTFElectronDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleTFVHighPtElectronDecision) junkies[index("TriggerTOSHlt2SingleTFVHighPtElectronDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision) junkies[index("TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPPiDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2SingleMuonVHighPTDecision) junkies[index("TriggerTOSHlt2SingleMuonVHighPTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesDoublePostScaledDecision) junkies[index("TriggerTOSHlt2DisplVerticesDoublePostScaledDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2RadiativeTopoTrackTOSDecision) junkies[index("TriggerTOSHlt2RadiativeTopoTrackTOSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2RadiativeTopoPhotonL0Decision) junkies[index("TriggerTOSHlt2RadiativeTopoPhotonL0Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonPsi2SHighPTDecision) junkies[index("TriggerTOSHlt2DiMuonPsi2SHighPTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DoubleDiMuonDecision) junkies[index("TriggerTOSHlt2DoubleDiMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonAndMuonDecision) junkies[index("TriggerTOSHlt2DiMuonAndMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonAndGammaDecision) junkies[index("TriggerTOSHlt2DiMuonAndGammaDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonAndD0Decision) junkies[index("TriggerTOSHlt2DiMuonAndD0Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonAndDpDecision) junkies[index("TriggerTOSHlt2DiMuonAndDpDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonAndDsDecision) junkies[index("TriggerTOSHlt2DiMuonAndDsDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonAndLcDecision) junkies[index("TriggerTOSHlt2DiMuonAndLcDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoRad2BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoRad2BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision) junkies[index("TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultHadron_nofilterDecision) junkies[index("TriggerTOSHlt2LowMultHadron_nofilterDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultElectron_nofilterDecision) junkies[index("TriggerTOSHlt2LowMultElectron_nofilterDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHKsDDDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHKsDDDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0KS0Decision) junkies[index("TriggerTOSHlt2CharmHadD2KS0KS0Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2ExpressD02KPiDecision) junkies[index("TriggerTOSHlt2ExpressD02KPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPKDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPKDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision) junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiPhiDecision) junkies[index("TriggerTOSHlt2DiPhiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision) junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision) junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision) junkies[index("TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision) junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision) junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision) junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision) junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2RadiativeTopoTrackDecision) junkies[index("TriggerTOSHlt2RadiativeTopoTrackDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2RadiativeTopoPhotonDecision) junkies[index("TriggerTOSHlt2RadiativeTopoPhotonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02KKMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02KKMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision) junkies[index("TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_4piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_4piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_K3piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_K3piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DiMuonDetachedPsi2SDecision) junkies[index("TriggerTOSHlt2DiMuonDetachedPsi2SDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision) junkies[index("TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultD2KPiDecision) junkies[index("TriggerTOSHlt2LowMultD2KPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultD2KPiPiDecision) junkies[index("TriggerTOSHlt2LowMultD2KPiPiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultD2K3PiDecision) junkies[index("TriggerTOSHlt2LowMultD2K3PiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultChiC2HHDecision) junkies[index("TriggerTOSHlt2LowMultChiC2HHDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultChiC2HHHHDecision) junkies[index("TriggerTOSHlt2LowMultChiC2HHHHDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultD2KPiWSDecision) junkies[index("TriggerTOSHlt2LowMultD2KPiWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultD2KPiPiWSDecision) junkies[index("TriggerTOSHlt2LowMultD2KPiPiWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultD2K3PiWSDecision) junkies[index("TriggerTOSHlt2LowMultD2K3PiWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultChiC2HHWSDecision) junkies[index("TriggerTOSHlt2LowMultChiC2HHWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultChiC2HHHHWSDecision) junkies[index("TriggerTOSHlt2LowMultChiC2HHHHWSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2LowMultDDIncDecision) junkies[index("TriggerTOSHlt2LowMultDDIncDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleLoosePSDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleLoosePSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighFDDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleHighFDDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighMassDecision) junkies[index("TriggerTOSHlt2DisplVerticesSingleHighMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesSinglePSDecision) junkies[index("TriggerTOSHlt2DisplVerticesSinglePSDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt2DisplVerticesDoublePSDecision) junkies[index("TriggerTOSHlt2DisplVerticesDoublePSDecision")].m_tos += 1.;

    if (0.5 < TriggerDecHlt2SingleElectronTFLowPtDecision) junkies[index("TriggerDecHlt2SingleElectronTFLowPtDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleElectronTFHighPtDecision) junkies[index("TriggerDecHlt2SingleElectronTFHighPtDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiElectronHighMassDecision) junkies[index("TriggerDecHlt2DiElectronHighMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiElectronBDecision) junkies[index("TriggerDecHlt2DiElectronBDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Topo2BodySimpleDecision) junkies[index("TriggerDecHlt2Topo2BodySimpleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Topo3BodySimpleDecision) junkies[index("TriggerDecHlt2Topo3BodySimpleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Topo4BodySimpleDecision) junkies[index("TriggerDecHlt2Topo4BodySimpleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Topo2BodyBBDTDecision) junkies[index("TriggerDecHlt2Topo2BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Topo3BodyBBDTDecision) junkies[index("TriggerDecHlt2Topo3BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Topo4BodyBBDTDecision) junkies[index("TriggerDecHlt2Topo4BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoMu2BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoMu2BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoMu3BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoMu3BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoMu4BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoMu4BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoE2BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoE2BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoE3BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoE3BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoE4BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoE4BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2IncPhiDecision) junkies[index("TriggerDecHlt2IncPhiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2IncPhiSidebandsDecision) junkies[index("TriggerDecHlt2IncPhiSidebandsDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHKsLLDecision) junkies[index("TriggerDecHlt2CharmHadD02HHKsLLDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Dst2PiD02PiPiDecision) junkies[index("TriggerDecHlt2Dst2PiD02PiPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Dst2PiD02MuMuDecision) junkies[index("TriggerDecHlt2Dst2PiD02MuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Dst2PiD02KMuDecision) junkies[index("TriggerDecHlt2Dst2PiD02KMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Dst2PiD02KPiDecision) junkies[index("TriggerDecHlt2Dst2PiD02KPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2PassThroughDecision) junkies[index("TriggerDecHlt2PassThroughDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TransparentDecision) junkies[index("TriggerDecHlt2TransparentDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DebugEventDecision) junkies[index("TriggerDecHlt2DebugEventDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02KKDecision) junkies[index("TriggerDecHlt2CharmHadD02KKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02KKWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02KKWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02KPiDecision) junkies[index("TriggerDecHlt2CharmHadD02KPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02KPiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02KPiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02PiPiDecision) junkies[index("TriggerDecHlt2CharmHadD02PiPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02PiPiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02PiPiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2ExpressLambdaDecision) junkies[index("TriggerDecHlt2ExpressLambdaDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2ExpressDs2PhiPiDecision) junkies[index("TriggerDecHlt2ExpressDs2PhiPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2ExpressDStar2D0PiDecision) junkies[index("TriggerDecHlt2ExpressDStar2D0PiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2ExpressHLT1PhysicsDecision) junkies[index("TriggerDecHlt2ExpressHLT1PhysicsDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Bs2PhiGammaDecision) junkies[index("TriggerDecHlt2Bs2PhiGammaDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Bs2PhiGammaWideBMassDecision) junkies[index("TriggerDecHlt2Bs2PhiGammaWideBMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Bd2KstGammaDecision) junkies[index("TriggerDecHlt2Bd2KstGammaDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Bd2KstGammaWideKMassDecision) junkies[index("TriggerDecHlt2Bd2KstGammaWideKMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2Bd2KstGammaWideBMassDecision) junkies[index("TriggerDecHlt2Bd2KstGammaWideBMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0PiDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0PiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0KDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0KDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmRareDecayD02MuMuDecision) junkies[index("TriggerDecHlt2CharmRareDecayD02MuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2B2HHDecision) junkies[index("TriggerDecHlt2B2HHDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2MuonFromHLT1Decision) junkies[index("TriggerDecHlt2MuonFromHLT1Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleMuonDecision) junkies[index("TriggerDecHlt2SingleMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleMuonHighPTDecision) junkies[index("TriggerDecHlt2SingleMuonHighPTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleMuonLowPTDecision) junkies[index("TriggerDecHlt2SingleMuonLowPTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TFBc2JpsiMuXDecision) junkies[index("TriggerDecHlt2TFBc2JpsiMuXDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TFBc2JpsiMuXSignalDecision) junkies[index("TriggerDecHlt2TFBc2JpsiMuXSignalDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesLowMassSingleDecision) junkies[index("TriggerDecHlt2DisplVerticesLowMassSingleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesHighMassSingleDecision) junkies[index("TriggerDecHlt2DisplVerticesHighMassSingleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesDoubleDecision) junkies[index("TriggerDecHlt2DisplVerticesDoubleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSinglePostScaledDecision) junkies[index("TriggerDecHlt2DisplVerticesSinglePostScaledDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesHighFDSingleDecision) junkies[index("TriggerDecHlt2DisplVerticesHighFDSingleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleDownDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleDownDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2B2HHPi0_MergedDecision) junkies[index("TriggerDecHlt2B2HHPi0_MergedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2HHHDecision) junkies[index("TriggerDecHlt2CharmHadD2HHHDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2HHHWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD2HHHWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDecision) junkies[index("TriggerDecHlt2DiMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonLowMassDecision) junkies[index("TriggerDecHlt2DiMuonLowMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonJPsiDecision) junkies[index("TriggerDecHlt2DiMuonJPsiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonJPsiHighPTDecision) junkies[index("TriggerDecHlt2DiMuonJPsiHighPTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonPsi2SDecision) junkies[index("TriggerDecHlt2DiMuonPsi2SDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonBDecision) junkies[index("TriggerDecHlt2DiMuonBDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonZDecision) junkies[index("TriggerDecHlt2DiMuonZDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDY1Decision) junkies[index("TriggerDecHlt2DiMuonDY1Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDY2Decision) junkies[index("TriggerDecHlt2DiMuonDY2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDY3Decision) junkies[index("TriggerDecHlt2DiMuonDY3Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDY4Decision) junkies[index("TriggerDecHlt2DiMuonDY4Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDetachedDecision) junkies[index("TriggerDecHlt2DiMuonDetachedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDetachedHeavyDecision) junkies[index("TriggerDecHlt2DiMuonDetachedHeavyDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDetachedJPsiDecision) junkies[index("TriggerDecHlt2DiMuonDetachedJPsiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonNoPVDecision) junkies[index("TriggerDecHlt2DiMuonNoPVDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TriMuonDetachedDecision) junkies[index("TriggerDecHlt2TriMuonDetachedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TriMuonTauDecision) junkies[index("TriggerDecHlt2TriMuonTauDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2ErrorEventDecision) junkies[index("TriggerDecHlt2ErrorEventDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2B2HHLTUnbiasedDecision) junkies[index("TriggerDecHlt2B2HHLTUnbiasedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HH_D02PiPiDecision) junkies[index("TriggerDecHlt2CharmHadD02HH_D02PiPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KKDecision) junkies[index("TriggerDecHlt2CharmHadD02HH_D02KKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KPiDecision) junkies[index("TriggerDecHlt2CharmHadD02HH_D02KPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiProtonDecision) junkies[index("TriggerDecHlt2DiProtonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiProtonTFDecision) junkies[index("TriggerDecHlt2DiProtonTFDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiProtonLowMultDecision) junkies[index("TriggerDecHlt2DiProtonLowMultDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiProtonLowMultTFDecision) junkies[index("TriggerDecHlt2DiProtonLowMultTFDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD2HMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilepD2HMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision) junkies[index("TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2diPhotonDiMuonDecision) junkies[index("TriggerDecHlt2diPhotonDiMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultMuonDecision) junkies[index("TriggerDecHlt2LowMultMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultHadronDecision) junkies[index("TriggerDecHlt2LowMultHadronDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultPhotonDecision) junkies[index("TriggerDecHlt2LowMultPhotonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultElectronDecision) junkies[index("TriggerDecHlt2LowMultElectronDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleTFElectronDecision) junkies[index("TriggerDecHlt2SingleTFElectronDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleTFVHighPtElectronDecision) junkies[index("TriggerDecHlt2SingleTFVHighPtElectronDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2B2HHLTUnbiasedDetachedDecision) junkies[index("TriggerDecHlt2B2HHLTUnbiasedDetachedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPPiDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2KPPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2SingleMuonVHighPTDecision) junkies[index("TriggerDecHlt2SingleMuonVHighPTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesDoublePostScaledDecision) junkies[index("TriggerDecHlt2DisplVerticesDoublePostScaledDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2RadiativeTopoTrackTOSDecision) junkies[index("TriggerDecHlt2RadiativeTopoTrackTOSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2RadiativeTopoPhotonL0Decision) junkies[index("TriggerDecHlt2RadiativeTopoPhotonL0Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonPsi2SHighPTDecision) junkies[index("TriggerDecHlt2DiMuonPsi2SHighPTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DoubleDiMuonDecision) junkies[index("TriggerDecHlt2DoubleDiMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonAndMuonDecision) junkies[index("TriggerDecHlt2DiMuonAndMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonAndGammaDecision) junkies[index("TriggerDecHlt2DiMuonAndGammaDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonAndD0Decision) junkies[index("TriggerDecHlt2DiMuonAndD0Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonAndDpDecision) junkies[index("TriggerDecHlt2DiMuonAndDpDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonAndDsDecision) junkies[index("TriggerDecHlt2DiMuonAndDsDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonAndLcDecision) junkies[index("TriggerDecHlt2DiMuonAndLcDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision) junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoRad2BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoRad2BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2TopoRad2plus1BodyBBDTDecision) junkies[index("TriggerDecHlt2TopoRad2plus1BodyBBDTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultHadron_nofilterDecision) junkies[index("TriggerDecHlt2LowMultHadron_nofilterDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultElectron_nofilterDecision) junkies[index("TriggerDecHlt2LowMultElectron_nofilterDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHKsDDDecision) junkies[index("TriggerDecHlt2CharmHadD02HHKsDDDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0KS0Decision) junkies[index("TriggerDecHlt2CharmHadD2KS0KS0Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2ExpressD02KPiDecision) junkies[index("TriggerDecHlt2ExpressD02KPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPKDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2KPKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPPiDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPKDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision) junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision) junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiPhiDecision) junkies[index("TriggerDecHlt2DiPhiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision) junkies[index("TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision) junkies[index("TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision) junkies[index("TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision) junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision) junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision) junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision) junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2RadiativeTopoTrackDecision) junkies[index("TriggerDecHlt2RadiativeTopoTrackDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2RadiativeTopoPhotonDecision) junkies[index("TriggerDecHlt2RadiativeTopoPhotonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_4piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_4piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02KKMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilepD02KKMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmSemilepD02KPiMuMuDecision) junkies[index("TriggerDecHlt2CharmSemilepD02KPiMuMuDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_4piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_4piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_K3piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_K3piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_2K2piDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_2K2piDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_3KpiDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_3KpiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_Ch2Decision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_Ch2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DiMuonDetachedPsi2SDecision) junkies[index("TriggerDecHlt2DiMuonDetachedPsi2SDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHXDst_hhXDecision) junkies[index("TriggerDecHlt2CharmHadD02HHXDst_hhXDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision) junkies[index("TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultD2KPiDecision) junkies[index("TriggerDecHlt2LowMultD2KPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultD2KPiPiDecision) junkies[index("TriggerDecHlt2LowMultD2KPiPiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultD2K3PiDecision) junkies[index("TriggerDecHlt2LowMultD2K3PiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultChiC2HHDecision) junkies[index("TriggerDecHlt2LowMultChiC2HHDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultChiC2HHHHDecision) junkies[index("TriggerDecHlt2LowMultChiC2HHHHDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultD2KPiWSDecision) junkies[index("TriggerDecHlt2LowMultD2KPiWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultD2KPiPiWSDecision) junkies[index("TriggerDecHlt2LowMultD2KPiPiWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultD2K3PiWSDecision) junkies[index("TriggerDecHlt2LowMultD2K3PiWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultChiC2HHWSDecision) junkies[index("TriggerDecHlt2LowMultChiC2HHWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultChiC2HHHHWSDecision) junkies[index("TriggerDecHlt2LowMultChiC2HHHHWSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2LowMultDDIncDecision) junkies[index("TriggerDecHlt2LowMultDDIncDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleLoosePSDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleLoosePSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleHighFDDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleHighFDDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSingleHighMassDecision) junkies[index("TriggerDecHlt2DisplVerticesSingleHighMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesSinglePSDecision) junkies[index("TriggerDecHlt2DisplVerticesSinglePSDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt2DisplVerticesDoublePSDecision) junkies[index("TriggerDecHlt2DisplVerticesDoublePSDecision")].m_evt += 1.;



  }

  for (unsigned j = 0 ; j < junkies.size() ; ++j) {
    junkies[j].m_evt = junkies[j].m_evt / allentries;
    junkies[j].m_tos = junkies[j].m_tos / allentries;
    junkies[j].m_tis = junkies[j].m_tis / allentries;
  }
  return junkies;
  for (unsigned j = 0 ; j < junkies.size() ; ++j) {
    std::cout << j << "\t\t" << junkies[j].m_evt << "\t\t\t" << junkies[j].m_tos << std::endl;
  }
}


std::vector<crack_junkie> crack::AddLoop(bool sigmc, std::vector<unsigned> order)
{

  std::vector<crack_junkie> junkies;

  if (fChain == 0) return junkies;

  Long64_t nentries = fChain->GetEntriesFast();

  for (unsigned j = 0 ; j < index("maxindex") ; ++j) {
    crack_junkie junk;
    junk.reset();
    junkies.push_back(junk);
  }

  Long64_t nbytes = 0, nb = 0;
  float allentries_tos = 0.;
  float allentries_evt = 0.;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    if (skip_event(sigmc)) continue;


    bool spotted = false;
    unsigned checkingPlace = 0u;
    while (!spotted) {
      unsigned checkingLine = 0u;
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleElectronTFLowPtDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleElectronTFLowPtDecision")].m_tos += 1.;  allentries_tos+=1.;break;} 
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleElectronTFHighPtDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleElectronTFHighPtDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiElectronHighMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiElectronHighMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiElectronBDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiElectronBDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Topo2BodySimpleDecision) { spotted = true; junkies[index("TriggerTOSHlt2Topo2BodySimpleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Topo3BodySimpleDecision) { spotted = true; junkies[index("TriggerTOSHlt2Topo3BodySimpleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Topo4BodySimpleDecision) { spotted = true; junkies[index("TriggerTOSHlt2Topo4BodySimpleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Topo2BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2Topo2BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Topo3BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2Topo3BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Topo4BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2Topo4BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoMu2BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoMu2BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoMu3BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoMu3BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoMu4BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoMu4BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoE2BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoE2BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoE3BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoE3BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoE4BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoE4BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2IncPhiDecision) { spotted = true; junkies[index("TriggerTOSHlt2IncPhiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2IncPhiSidebandsDecision) { spotted = true; junkies[index("TriggerTOSHlt2IncPhiSidebandsDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHKsLLDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHKsLLDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Dst2PiD02PiPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2Dst2PiD02PiPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Dst2PiD02MuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2Dst2PiD02MuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Dst2PiD02KMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2Dst2PiD02KMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Dst2PiD02KPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2Dst2PiD02KPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2PassThroughDecision) { spotted = true; junkies[index("TriggerTOSHlt2PassThroughDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TransparentDecision) { spotted = true; junkies[index("TriggerTOSHlt2TransparentDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DebugEventDecision) { spotted = true; junkies[index("TriggerTOSHlt2DebugEventDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02KKDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02KKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02KKWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02KKWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02KPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02KPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02KPiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02KPiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02PiPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02PiPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02PiPiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02PiPiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2ExpressLambdaDecision) { spotted = true; junkies[index("TriggerTOSHlt2ExpressLambdaDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2ExpressDs2PhiPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2ExpressDs2PhiPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2ExpressDStar2D0PiDecision) { spotted = true; junkies[index("TriggerTOSHlt2ExpressDStar2D0PiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2ExpressHLT1PhysicsDecision) { spotted = true; junkies[index("TriggerTOSHlt2ExpressHLT1PhysicsDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Bs2PhiGammaDecision) { spotted = true; junkies[index("TriggerTOSHlt2Bs2PhiGammaDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Bs2PhiGammaWideBMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2Bs2PhiGammaWideBMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Bd2KstGammaDecision) { spotted = true; junkies[index("TriggerTOSHlt2Bd2KstGammaDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Bd2KstGammaWideKMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2Bd2KstGammaWideKMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2Bd2KstGammaWideBMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2Bd2KstGammaWideBMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0PiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0PiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0KDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0KDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmRareDecayD02MuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmRareDecayD02MuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2B2HHDecision) { spotted = true; junkies[index("TriggerTOSHlt2B2HHDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2MuonFromHLT1Decision) { spotted = true; junkies[index("TriggerTOSHlt2MuonFromHLT1Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleMuonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleMuonHighPTDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleMuonHighPTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleMuonLowPTDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleMuonLowPTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TFBc2JpsiMuXDecision) { spotted = true; junkies[index("TriggerTOSHlt2TFBc2JpsiMuXDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TFBc2JpsiMuXSignalDecision) { spotted = true; junkies[index("TriggerTOSHlt2TFBc2JpsiMuXSignalDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesLowMassSingleDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesLowMassSingleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesHighMassSingleDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesHighMassSingleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesDoubleDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesDoubleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSinglePostScaledDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSinglePostScaledDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesHighFDSingleDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesHighFDSingleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleDownDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleDownDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2B2HHPi0_MergedDecision) { spotted = true; junkies[index("TriggerTOSHlt2B2HHPi0_MergedDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2HHHDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2HHHDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2HHHWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2HHHWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonLowMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonLowMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonJPsiDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonJPsiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonJPsiHighPTDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonJPsiHighPTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonPsi2SDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonPsi2SDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonBDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonBDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonZDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonZDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDY1Decision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDY1Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDY2Decision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDY2Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDY3Decision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDY3Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDY4Decision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDY4Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDetachedDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDetachedDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDetachedHeavyDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDetachedHeavyDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDetachedJPsiDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDetachedJPsiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonNoPVDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonNoPVDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TriMuonDetachedDecision) { spotted = true; junkies[index("TriggerTOSHlt2TriMuonDetachedDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TriMuonTauDecision) { spotted = true; junkies[index("TriggerTOSHlt2TriMuonTauDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2ErrorEventDecision) { spotted = true; junkies[index("TriggerTOSHlt2ErrorEventDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2B2HHLTUnbiasedDecision) { spotted = true; junkies[index("TriggerTOSHlt2B2HHLTUnbiasedDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HH_D02PiPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HH_D02PiPiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KKDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KKWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HH_D02KPiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0PiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0KDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiProtonDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiProtonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiProtonTFDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiProtonTFDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiProtonLowMultDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiProtonLowMultDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiProtonLowMultTFDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiProtonLowMultTFDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD2HMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD2HMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD2HMuMuWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2diPhotonDiMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt2diPhotonDiMuonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultMuonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultHadronDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultHadronDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultPhotonDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultPhotonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultElectronDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultElectronDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleTFElectronDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleTFElectronDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleTFVHighPtElectronDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleTFVHighPtElectronDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision) { spotted = true; junkies[index("TriggerTOSHlt2B2HHLTUnbiasedDetachedDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2SingleMuonVHighPTDecision) { spotted = true; junkies[index("TriggerTOSHlt2SingleMuonVHighPTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesDoublePostScaledDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesDoublePostScaledDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleHighMassPostScaledDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleHighFDPostScaledDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleMVPostScaledDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2RadiativeTopoTrackTOSDecision) { spotted = true; junkies[index("TriggerTOSHlt2RadiativeTopoTrackTOSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2RadiativeTopoPhotonL0Decision) { spotted = true; junkies[index("TriggerTOSHlt2RadiativeTopoPhotonL0Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonPsi2SHighPTDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonPsi2SHighPTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DoubleDiMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt2DoubleDiMuonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonAndMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonAndMuonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonAndGammaDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonAndGammaDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonAndD0Decision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonAndD0Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonAndDpDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonAndDpDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonAndDsDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonAndDsDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonAndLcDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonAndLcDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoRad2BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoRad2BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision) { spotted = true; junkies[index("TriggerTOSHlt2TopoRad2plus1BodyBBDTDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultHadron_nofilterDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultHadron_nofilterDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultElectron_nofilterDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultElectron_nofilterDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHKsDDDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHKsDDDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0KS0Decision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0KS0Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0KS0WideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2ExpressD02KPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2ExpressD02KPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPPiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPKDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2KPKWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPPiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPKDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadLambdaC2PiPKWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD2KS0H_D2KS0DDKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiPhiDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiPhiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2PiMuMuSSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilep3bodyD2KMuMuSSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision) { spotted = true; junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0LLKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision) { spotted = true; junkies[index("TriggerTOSHlt2LambdaC_LambdaC2Lambda0DDKDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2RadiativeTopoTrackDecision) { spotted = true; junkies[index("TriggerTOSHlt2RadiativeTopoTrackDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2RadiativeTopoPhotonDecision) { spotted = true; junkies[index("TriggerTOSHlt2RadiativeTopoPhotonDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_4piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_4piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_K3piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_K3piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_2K2piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_2K2piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_3KpiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_3KpiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_Ch2Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHHDst_Ch2WideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02PiPiMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02KKMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02KKMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmSemilepD02KPiMuMuDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_4piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_4piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_4piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_K3piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_K3piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_K3piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_KKpipiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_KKpipiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_2K2piDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_2K2piWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_3KpiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_3KpiWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_Ch2Decision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHHH_Ch2WideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DiMuonDetachedPsi2SDecision) { spotted = true; junkies[index("TriggerTOSHlt2DiMuonDetachedPsi2SDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHXDst_hhXDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2CharmHadD02HHXDst_hhXWideMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultD2KPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultD2KPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultD2KPiPiDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultD2KPiPiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultD2K3PiDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultD2K3PiDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultChiC2HHDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultChiC2HHDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultChiC2HHHHDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultChiC2HHHHDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultD2KPiWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultD2KPiWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultD2KPiPiWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultD2KPiPiWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultD2K3PiWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultD2K3PiWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultChiC2HHWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultChiC2HHWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultChiC2HHHHWSDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultChiC2HHHHWSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2LowMultDDIncDecision) { spotted = true; junkies[index("TriggerTOSHlt2LowMultDDIncDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleLoosePSDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleLoosePSDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighFDDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleHighFDDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleVeryHighFDDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSingleHighMassDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSingleHighMassDecision")].m_tos += 1.;  allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesSinglePSDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesSinglePSDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt2DisplVerticesDoublePSDecision) { spotted = true; junkies[index("TriggerTOSHlt2DisplVerticesDoublePSDecision")].m_tos += 1.; allentries_tos+=1.;break;}

      checkingPlace++;
      if (checkingPlace==order.size()) {spotted = true; allentries_tos+=1.;break;}
    }
    spotted = false;
    checkingPlace = 0u;
    while (!spotted) {
      unsigned checkingLine = 0u;
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleElectronTFLowPtDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleElectronTFLowPtDecision")].m_evt += 1.;  allentries_evt+=1.;break;} 
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleElectronTFHighPtDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleElectronTFHighPtDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiElectronHighMassDecision) { spotted = true; junkies[index("TriggerDecHlt2DiElectronHighMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiElectronBDecision) { spotted = true; junkies[index("TriggerDecHlt2DiElectronBDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Topo2BodySimpleDecision) { spotted = true; junkies[index("TriggerDecHlt2Topo2BodySimpleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Topo3BodySimpleDecision) { spotted = true; junkies[index("TriggerDecHlt2Topo3BodySimpleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Topo4BodySimpleDecision) { spotted = true; junkies[index("TriggerDecHlt2Topo4BodySimpleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Topo2BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2Topo2BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Topo3BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2Topo3BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Topo4BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2Topo4BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoMu2BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoMu2BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoMu3BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoMu3BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoMu4BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoMu4BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoE2BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoE2BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoE3BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoE3BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoE4BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoE4BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2IncPhiDecision) { spotted = true; junkies[index("TriggerDecHlt2IncPhiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2IncPhiSidebandsDecision) { spotted = true; junkies[index("TriggerDecHlt2IncPhiSidebandsDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHKsLLDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHKsLLDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Dst2PiD02PiPiDecision) { spotted = true; junkies[index("TriggerDecHlt2Dst2PiD02PiPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Dst2PiD02MuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2Dst2PiD02MuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Dst2PiD02KMuDecision) { spotted = true; junkies[index("TriggerDecHlt2Dst2PiD02KMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Dst2PiD02KPiDecision) { spotted = true; junkies[index("TriggerDecHlt2Dst2PiD02KPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2PassThroughDecision) { spotted = true; junkies[index("TriggerDecHlt2PassThroughDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TransparentDecision) { spotted = true; junkies[index("TriggerDecHlt2TransparentDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DebugEventDecision) { spotted = true; junkies[index("TriggerDecHlt2DebugEventDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02KKDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02KKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02KKWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02KKWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02KPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02KPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02KPiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02KPiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02PiPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02PiPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02PiPiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02PiPiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2ExpressLambdaDecision) { spotted = true; junkies[index("TriggerDecHlt2ExpressLambdaDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2ExpressDs2PhiPiDecision) { spotted = true; junkies[index("TriggerDecHlt2ExpressDs2PhiPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2ExpressDStar2D0PiDecision) { spotted = true; junkies[index("TriggerDecHlt2ExpressDStar2D0PiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2ExpressHLT1PhysicsDecision) { spotted = true; junkies[index("TriggerDecHlt2ExpressHLT1PhysicsDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Bs2PhiGammaDecision) { spotted = true; junkies[index("TriggerDecHlt2Bs2PhiGammaDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Bs2PhiGammaWideBMassDecision) { spotted = true; junkies[index("TriggerDecHlt2Bs2PhiGammaWideBMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Bd2KstGammaDecision) { spotted = true; junkies[index("TriggerDecHlt2Bd2KstGammaDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Bd2KstGammaWideKMassDecision) { spotted = true; junkies[index("TriggerDecHlt2Bd2KstGammaWideKMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2Bd2KstGammaWideBMassDecision) { spotted = true; junkies[index("TriggerDecHlt2Bd2KstGammaWideBMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0PiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0PiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0KDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0KDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmRareDecayD02MuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmRareDecayD02MuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2B2HHDecision) { spotted = true; junkies[index("TriggerDecHlt2B2HHDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2MuonFromHLT1Decision) { spotted = true; junkies[index("TriggerDecHlt2MuonFromHLT1Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleMuonDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleMuonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleMuonHighPTDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleMuonHighPTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleMuonLowPTDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleMuonLowPTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TFBc2JpsiMuXDecision) { spotted = true; junkies[index("TriggerDecHlt2TFBc2JpsiMuXDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TFBc2JpsiMuXSignalDecision) { spotted = true; junkies[index("TriggerDecHlt2TFBc2JpsiMuXSignalDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesLowMassSingleDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesLowMassSingleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesHighMassSingleDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesHighMassSingleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesDoubleDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesDoubleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSinglePostScaledDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSinglePostScaledDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesHighFDSingleDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesHighFDSingleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleDownDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleDownDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2B2HHPi0_MergedDecision) { spotted = true; junkies[index("TriggerDecHlt2B2HHPi0_MergedDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2HHHDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2HHHDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2HHHWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2HHHWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonLowMassDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonLowMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonJPsiDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonJPsiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonJPsiHighPTDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonJPsiHighPTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonPsi2SDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonPsi2SDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonBDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonBDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonZDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonZDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDY1Decision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDY1Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDY2Decision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDY2Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDY3Decision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDY3Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDY4Decision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDY4Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDetachedDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDetachedDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDetachedHeavyDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDetachedHeavyDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDetachedJPsiDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDetachedJPsiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonNoPVDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonNoPVDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TriMuonDetachedDecision) { spotted = true; junkies[index("TriggerDecHlt2TriMuonDetachedDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TriMuonTauDecision) { spotted = true; junkies[index("TriggerDecHlt2TriMuonTauDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2ErrorEventDecision) { spotted = true; junkies[index("TriggerDecHlt2ErrorEventDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2B2HHLTUnbiasedDecision) { spotted = true; junkies[index("TriggerDecHlt2B2HHLTUnbiasedDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HH_D02PiPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HH_D02PiPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HH_D02PiPiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KKDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HH_D02KKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HH_D02KKWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HH_D02KPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HH_D02KPiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0PiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0KDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiProtonDecision) { spotted = true; junkies[index("TriggerDecHlt2DiProtonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiProtonTFDecision) { spotted = true; junkies[index("TriggerDecHlt2DiProtonTFDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiProtonLowMultDecision) { spotted = true; junkies[index("TriggerDecHlt2DiProtonLowMultDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiProtonLowMultTFDecision) { spotted = true; junkies[index("TriggerDecHlt2DiProtonLowMultTFDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02PiMuNuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD2HMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD2HMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD2HMuMuWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2diPhotonDiMuonDecision) { spotted = true; junkies[index("TriggerDecHlt2diPhotonDiMuonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultMuonDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultMuonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultHadronDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultHadronDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultPhotonDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultPhotonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultElectronDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultElectronDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleTFElectronDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleTFElectronDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleTFVHighPtElectronDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleTFVHighPtElectronDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2B2HHLTUnbiasedDetachedDecision) { spotted = true; junkies[index("TriggerDecHlt2B2HHLTUnbiasedDetachedDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2KPPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2SingleMuonVHighPTDecision) { spotted = true; junkies[index("TriggerDecHlt2SingleMuonVHighPTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesDoublePostScaledDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesDoublePostScaledDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleHighMassPostScaledDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleHighFDPostScaledDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleMVPostScaledDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2RadiativeTopoTrackTOSDecision) { spotted = true; junkies[index("TriggerDecHlt2RadiativeTopoTrackTOSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2RadiativeTopoPhotonL0Decision) { spotted = true; junkies[index("TriggerDecHlt2RadiativeTopoPhotonL0Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonPsi2SHighPTDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonPsi2SHighPTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DoubleDiMuonDecision) { spotted = true; junkies[index("TriggerDecHlt2DoubleDiMuonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonAndMuonDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonAndMuonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonAndGammaDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonAndGammaDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonAndD0Decision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonAndD0Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonAndDpDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonAndDpDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonAndDsDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonAndDsDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonAndLcDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonAndLcDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoRad2BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoRad2BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2TopoRad2plus1BodyBBDTDecision) { spotted = true; junkies[index("TriggerDecHlt2TopoRad2plus1BodyBBDTDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultHadron_nofilterDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultHadron_nofilterDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultElectron_nofilterDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultElectron_nofilterDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHKsDDDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHKsDDDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0KS0Decision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0KS0Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0KS0WideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2ExpressD02KPiDecision) { spotted = true; junkies[index("TriggerDecHlt2ExpressD02KPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2KPPiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPKDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2KPKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2KPKWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPPiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPKDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadLambdaC2PiPKWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0DDPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD2KS0H_D2KS0DDKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiPhiDecision) { spotted = true; junkies[index("TriggerDecHlt2DiPhiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_4piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_K3piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_KKpipiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_2K2piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_3KpiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDstNoHltOne_Ch2WideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilep3bodyD2PiMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilep3bodyD2PiMuMuSSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilep3bodyD2KMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilep3bodyD2KMuMuSSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilep3bodyLambdac2PMuMuSSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision) { spotted = true; junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0LLPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision) { spotted = true; junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0LLKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision) { spotted = true; junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0DDPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision) { spotted = true; junkies[index("TriggerDecHlt2LambdaC_LambdaC2Lambda0DDKDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2RadiativeTopoTrackDecision) { spotted = true; junkies[index("TriggerDecHlt2RadiativeTopoTrackDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2RadiativeTopoPhotonDecision) { spotted = true; junkies[index("TriggerDecHlt2RadiativeTopoPhotonDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_4piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_4piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_4piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_K3piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_K3piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_KKpipiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_KKpipiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_2K2piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_2K2piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_3KpiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_3KpiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_Ch2Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHHDst_Ch2WideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02PiPiMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02KKMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02KKMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmSemilepD02KPiMuMuDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmSemilepD02KPiMuMuDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_4piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_4piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_4piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_K3piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_K3piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_K3piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_KKpipiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_KKpipiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_2K2piDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_2K2piDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_2K2piWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_3KpiDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_3KpiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_3KpiWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_Ch2Decision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_Ch2Decision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHHH_Ch2WideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DiMuonDetachedPsi2SDecision) { spotted = true; junkies[index("TriggerDecHlt2DiMuonDetachedPsi2SDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHXDst_hhXDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHXDst_hhXDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision) { spotted = true; junkies[index("TriggerDecHlt2CharmHadD02HHXDst_hhXWideMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultD2KPiDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultD2KPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultD2KPiPiDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultD2KPiPiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultD2K3PiDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultD2K3PiDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultChiC2HHDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultChiC2HHDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultChiC2HHHHDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultChiC2HHHHDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultD2KPiWSDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultD2KPiWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultD2KPiPiWSDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultD2KPiPiWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultD2K3PiWSDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultD2K3PiWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultChiC2HHWSDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultChiC2HHWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultChiC2HHHHWSDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultChiC2HHHHWSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2LowMultDDIncDecision) { spotted = true; junkies[index("TriggerDecHlt2LowMultDDIncDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleLoosePSDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleLoosePSDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleHighFDDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleHighFDDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleVeryHighFDDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSingleHighMassDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSingleHighMassDecision")].m_evt += 1.;  allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesSinglePSDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesSinglePSDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt2DisplVerticesDoublePSDecision) { spotted = true; junkies[index("TriggerDecHlt2DisplVerticesDoublePSDecision")].m_evt += 1.; allentries_evt+=1.;break;}

      checkingPlace++;
      if (checkingPlace==order.size()) {spotted = true; allentries_evt+=0.;break;}
  }

  }

  for (unsigned j = 0 ; j < junkies.size() ; ++j) {
    junkies[j].m_tos = junkies[j].m_tos / allentries_evt;
    junkies[j].m_evt = junkies[j].m_evt / allentries_evt;
  }
  return junkies;
  for (unsigned j = 0 ; j < junkies.size() ; ++j) {
    std::cout << j << "\t\t" << junkies[j].m_evt << "\t\t\t" << junkies[j].m_tos << std::endl;
  }
}
float punzidecsort(unsigned a, unsigned b) {
  return ( sigjun[a].m_evt / (g_punzialpha/2. + sqrt(bkgjun[a].m_evt)) ) > ( sigjun[b].m_evt / (g_punzialpha/2. + sqrt(bkgjun[b].m_evt)) );
}
float punzitossort(unsigned a, unsigned b) {
  return ( sigjun[a].m_tos / (g_punzialpha/2. + sqrt(bkgjun[a].m_tos)) ) > ( sigjun[b].m_tos / (g_punzialpha/2. + sqrt(bkgjun[b].m_tos)) );
}

int main(int argc, char** argv) {
  bool m_tos = false;
  if (argc >= 4) {
    m_tos = true;
  }
  if (argc >= 3) {
    g_geocut = atof(argv[1]);
    g_pidcut = atof(argv[2]);
  }
  TChain* t = new TChain("Tau23Mu");
  t->Add("2012UP.root");
  t->Add("2012DOWN.root");
  crack c(t);
  std::cout << "reading data" << std::endl;
  bkgjun = c.Loop(false);
  TChain* s = new TChain("Tau23Mu");
  s->Add("tau23mu_blend.root");
  crack d(s);
  std::cout << "reading MC" << std::endl;
  sigjun = d.Loop(true);

  std::vector<unsigned> indizes;
  for (unsigned u = 0u ; u < sigjun.size() ; ++u) {
    indizes.push_back(u);
  }
  std::cout << "sorting" << std::endl;
  if (m_tos) {
    std::sort(indizes.begin(),indizes.end(),punzitossort);
  } else {
    std::sort(indizes.begin(),indizes.end(),punzidecsort);
  }


  std::cout << "reading data" << std::endl;
  bkgjun = c.AddLoop(false, indizes);
  std::cout << "reading MC" << std::endl;
  sigjun = d.AddLoop(true, indizes);

  std::cout << "cummulative signal efficiencies" << std::endl;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    std::cout << givethename(j) << "\t\t" << sigjun[j].m_evt << "\t\t\t" << sigjun[j].m_tos << std::endl;
  }
  std::cout << "\n\n\ncummulative background efficiencies" << std::endl;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    std::cout << givethename(j) << "\t\t" << bkgjun[j].m_evt << "\t\t\t" << bkgjun[j].m_tos << std::endl;
  }

  std::cout << "EVT table" << std::endl;
  float sumsig = 0.;
  float sumbkg = 0.;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    if (m_tos) {
      sumsig+= sigjun[j].m_tos;
      sumbkg+= bkgjun[j].m_tos;
    } else {
      sumsig+= sigjun[j].m_evt;
      sumbkg+= bkgjun[j].m_evt;
    }
    float fom = sqrt(sumbkg)/sumsig;
    if (m_tos) {
      std::cout << givethename(j) << "\t&\t" << sigjun[j].m_tos << "\t&\t" << bkgjun[j].m_tos << "\t&\t" << fom << "\\\\" << std::endl;
    } else {
      std::cout << givethename(j) << "\t&\t" << sigjun[j].m_evt << "\t&\t" << bkgjun[j].m_evt << "\t&\t" << fom << "\\\\" << std::endl;
    }

  }

  return 0;
}
