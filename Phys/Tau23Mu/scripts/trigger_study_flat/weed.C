#define weed_cxx
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
    //if (!sigmc)&&(!((mass<1758.8&&mass>1748.8)||(mass<1808.8&&mass>1798.8))) continue;
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
  if (!(TriggerTOSHlt2TriMuonTauDecision)) return true;

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


  for (unsigned j = 0 ; j < index("maxhlt1") ; ++j) {
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


    if (0.5 < TriggerTOSHlt1DiMuonHighMassDecision) junkies[index("TriggerTOSHlt1DiMuonHighMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1DiMuonLowMassDecision) junkies[index("TriggerTOSHlt1DiMuonLowMassDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1SingleMuonNoIPDecision) junkies[index("TriggerTOSHlt1SingleMuonNoIPDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1SingleMuonHighPTDecision) junkies[index("TriggerTOSHlt1SingleMuonHighPTDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1TrackAllL0Decision) junkies[index("TriggerTOSHlt1TrackAllL0Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1TrackMuonDecision) junkies[index("TriggerTOSHlt1TrackMuonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1TrackPhotonDecision) junkies[index("TriggerTOSHlt1TrackPhotonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1LumiDecision) junkies[index("TriggerTOSHlt1LumiDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1LumiMidBeamCrossingDecision) junkies[index("TriggerTOSHlt1LumiMidBeamCrossingDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1MBNoBiasDecision) junkies[index("TriggerTOSHlt1MBNoBiasDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1L0AnyDecision) junkies[index("TriggerTOSHlt1L0AnyDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1L0AnyRateLimitedDecision) junkies[index("TriggerTOSHlt1L0AnyRateLimitedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1L0AnyNoSPDDecision) junkies[index("TriggerTOSHlt1L0AnyNoSPDDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision) junkies[index("TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1NoPVPassThroughDecision) junkies[index("TriggerTOSHlt1NoPVPassThroughDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1DiProtonLowMultDecision) junkies[index("TriggerTOSHlt1DiProtonLowMultDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasNoBeamBeam1Decision) junkies[index("TriggerTOSHlt1BeamGasNoBeamBeam1Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasNoBeamBeam2Decision) junkies[index("TriggerTOSHlt1BeamGasNoBeamBeam2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasBeam1Decision) junkies[index("TriggerTOSHlt1BeamGasBeam1Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasBeam2Decision) junkies[index("TriggerTOSHlt1BeamGasBeam2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision) junkies[index("TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision) junkies[index("TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasCrossingForcedRecoDecision) junkies[index("TriggerTOSHlt1BeamGasCrossingForcedRecoDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1ODINTechnicalDecision) junkies[index("TriggerTOSHlt1ODINTechnicalDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1Tell1ErrorDecision) junkies[index("TriggerTOSHlt1Tell1ErrorDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasCrossingParasiticDecision) junkies[index("TriggerTOSHlt1BeamGasCrossingParasiticDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1ErrorEventDecision) junkies[index("TriggerTOSHlt1ErrorEventDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1Global) junkies[index("TriggerTOSHlt1Global")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1MBMicroBiasVeloDecision) junkies[index("TriggerTOSHlt1MBMicroBiasVeloDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision) junkies[index("TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1MBMicroBiasTStationDecision) junkies[index("TriggerTOSHlt1MBMicroBiasTStationDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision) junkies[index("TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1DiProtonDecision) junkies[index("TriggerTOSHlt1DiProtonDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1VeloClosingMicroBiasDecision) junkies[index("TriggerTOSHlt1VeloClosingMicroBiasDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1SingleElectronNoIPDecision) junkies[index("TriggerTOSHlt1SingleElectronNoIPDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1TrackForwardPassThroughDecision) junkies[index("TriggerTOSHlt1TrackForwardPassThroughDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1TrackForwardPassThroughLooseDecision) junkies[index("TriggerTOSHlt1TrackForwardPassThroughLooseDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1CharmCalibrationNoBiasDecision) junkies[index("TriggerTOSHlt1CharmCalibrationNoBiasDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1L0HighSumETJetDecision) junkies[index("TriggerTOSHlt1L0HighSumETJetDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision) junkies[index("TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1BeamGasHighRhoVerticesDecision) junkies[index("TriggerTOSHlt1BeamGasHighRhoVerticesDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1VertexDisplVertexDecision) junkies[index("TriggerTOSHlt1VertexDisplVertexDecision")].m_tos += 1.;
    if (0.5 < TriggerTOSHlt1TrackAllL0TightDecision) junkies[index("TriggerTOSHlt1TrackAllL0TightDecision")].m_tos += 1.;



    if (0.5 < TriggerDecHlt1DiMuonHighMassDecision) junkies[index("TriggerDecHlt1DiMuonHighMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1DiMuonLowMassDecision) junkies[index("TriggerDecHlt1DiMuonLowMassDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1SingleMuonNoIPDecision) junkies[index("TriggerDecHlt1SingleMuonNoIPDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1SingleMuonHighPTDecision) junkies[index("TriggerDecHlt1SingleMuonHighPTDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1TrackAllL0Decision) junkies[index("TriggerDecHlt1TrackAllL0Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1TrackMuonDecision) junkies[index("TriggerDecHlt1TrackMuonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1TrackPhotonDecision) junkies[index("TriggerDecHlt1TrackPhotonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1LumiDecision) junkies[index("TriggerDecHlt1LumiDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1LumiMidBeamCrossingDecision) junkies[index("TriggerDecHlt1LumiMidBeamCrossingDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1MBNoBiasDecision) junkies[index("TriggerDecHlt1MBNoBiasDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1L0AnyDecision) junkies[index("TriggerDecHlt1L0AnyDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1L0AnyRateLimitedDecision) junkies[index("TriggerDecHlt1L0AnyRateLimitedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1L0AnyNoSPDDecision) junkies[index("TriggerDecHlt1L0AnyNoSPDDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1L0AnyNoSPDRateLimitedDecision) junkies[index("TriggerDecHlt1L0AnyNoSPDRateLimitedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1NoPVPassThroughDecision) junkies[index("TriggerDecHlt1NoPVPassThroughDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1DiProtonLowMultDecision) junkies[index("TriggerDecHlt1DiProtonLowMultDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasNoBeamBeam1Decision) junkies[index("TriggerDecHlt1BeamGasNoBeamBeam1Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasNoBeamBeam2Decision) junkies[index("TriggerDecHlt1BeamGasNoBeamBeam2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasBeam1Decision) junkies[index("TriggerDecHlt1BeamGasBeam1Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasBeam2Decision) junkies[index("TriggerDecHlt1BeamGasBeam2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision) junkies[index("TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision) junkies[index("TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasCrossingForcedRecoDecision) junkies[index("TriggerDecHlt1BeamGasCrossingForcedRecoDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1ODINTechnicalDecision) junkies[index("TriggerDecHlt1ODINTechnicalDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1Tell1ErrorDecision) junkies[index("TriggerDecHlt1Tell1ErrorDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasCrossingParasiticDecision) junkies[index("TriggerDecHlt1BeamGasCrossingParasiticDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1ErrorEventDecision) junkies[index("TriggerDecHlt1ErrorEventDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1Global) junkies[index("TriggerDecHlt1Global")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1MBMicroBiasVeloDecision) junkies[index("TriggerDecHlt1MBMicroBiasVeloDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision) junkies[index("TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1MBMicroBiasTStationDecision) junkies[index("TriggerDecHlt1MBMicroBiasTStationDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision) junkies[index("TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1DiProtonDecision) junkies[index("TriggerDecHlt1DiProtonDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1VeloClosingMicroBiasDecision) junkies[index("TriggerDecHlt1VeloClosingMicroBiasDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1SingleElectronNoIPDecision) junkies[index("TriggerDecHlt1SingleElectronNoIPDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1TrackForwardPassThroughDecision) junkies[index("TriggerDecHlt1TrackForwardPassThroughDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1TrackForwardPassThroughLooseDecision) junkies[index("TriggerDecHlt1TrackForwardPassThroughLooseDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1CharmCalibrationNoBiasDecision) junkies[index("TriggerDecHlt1CharmCalibrationNoBiasDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1L0HighSumETJetDecision) junkies[index("TriggerDecHlt1L0HighSumETJetDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision) junkies[index("TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1BeamGasHighRhoVerticesDecision) junkies[index("TriggerDecHlt1BeamGasHighRhoVerticesDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1VertexDisplVertexDecision) junkies[index("TriggerDecHlt1VertexDisplVertexDecision")].m_evt += 1.;
    if (0.5 < TriggerDecHlt1TrackAllL0TightDecision) junkies[index("TriggerDecHlt1TrackAllL0TightDecision")].m_evt += 1.;





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

  for (unsigned j = 0 ; j < index("maxhlt1") ; ++j) {
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


      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1DiMuonHighMassDecision) { spotted = true; junkies[index("TriggerTOSHlt1DiMuonHighMassDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1DiMuonLowMassDecision) { spotted = true; junkies[index("TriggerTOSHlt1DiMuonLowMassDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1SingleMuonNoIPDecision) { spotted = true; junkies[index("TriggerTOSHlt1SingleMuonNoIPDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1SingleMuonHighPTDecision) { spotted = true; junkies[index("TriggerTOSHlt1SingleMuonHighPTDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1TrackAllL0Decision) { spotted = true; junkies[index("TriggerTOSHlt1TrackAllL0Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1TrackMuonDecision) { spotted = true; junkies[index("TriggerTOSHlt1TrackMuonDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1TrackPhotonDecision) { spotted = true; junkies[index("TriggerTOSHlt1TrackPhotonDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1LumiDecision) { spotted = true; junkies[index("TriggerTOSHlt1LumiDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1LumiMidBeamCrossingDecision) { spotted = true; junkies[index("TriggerTOSHlt1LumiMidBeamCrossingDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1MBNoBiasDecision) { spotted = true; junkies[index("TriggerTOSHlt1MBNoBiasDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1L0AnyDecision) { spotted = true; junkies[index("TriggerTOSHlt1L0AnyDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1L0AnyRateLimitedDecision) { spotted = true; junkies[index("TriggerTOSHlt1L0AnyRateLimitedDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1L0AnyNoSPDDecision) { spotted = true; junkies[index("TriggerTOSHlt1L0AnyNoSPDDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision) { spotted = true; junkies[index("TriggerTOSHlt1L0AnyNoSPDRateLimitedDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1NoPVPassThroughDecision) { spotted = true; junkies[index("TriggerTOSHlt1NoPVPassThroughDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1DiProtonLowMultDecision) { spotted = true; junkies[index("TriggerTOSHlt1DiProtonLowMultDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasNoBeamBeam1Decision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasNoBeamBeam1Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasNoBeamBeam2Decision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasNoBeamBeam2Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasBeam1Decision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasBeam1Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasBeam2Decision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasBeam2Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasCrossingEnhancedBeam1Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasCrossingEnhancedBeam2Decision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasCrossingForcedRecoDecision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasCrossingForcedRecoDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1ODINTechnicalDecision) { spotted = true; junkies[index("TriggerTOSHlt1ODINTechnicalDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1Tell1ErrorDecision) { spotted = true; junkies[index("TriggerTOSHlt1Tell1ErrorDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasCrossingParasiticDecision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasCrossingParasiticDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1ErrorEventDecision) { spotted = true; junkies[index("TriggerTOSHlt1ErrorEventDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1Global) { spotted = true; junkies[index("TriggerTOSHlt1Global")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1MBMicroBiasVeloDecision) { spotted = true; junkies[index("TriggerTOSHlt1MBMicroBiasVeloDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision) { spotted = true; junkies[index("TriggerTOSHlt1MBMicroBiasVeloRateLimitedDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1MBMicroBiasTStationDecision) { spotted = true; junkies[index("TriggerTOSHlt1MBMicroBiasTStationDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision) { spotted = true; junkies[index("TriggerTOSHlt1MBMicroBiasTStationRateLimitedDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1DiProtonDecision) { spotted = true; junkies[index("TriggerTOSHlt1DiProtonDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1VeloClosingMicroBiasDecision) { spotted = true; junkies[index("TriggerTOSHlt1VeloClosingMicroBiasDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1SingleElectronNoIPDecision) { spotted = true; junkies[index("TriggerTOSHlt1SingleElectronNoIPDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1TrackForwardPassThroughDecision) { spotted = true; junkies[index("TriggerTOSHlt1TrackForwardPassThroughDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1TrackForwardPassThroughLooseDecision) { spotted = true; junkies[index("TriggerTOSHlt1TrackForwardPassThroughLooseDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1CharmCalibrationNoBiasDecision) { spotted = true; junkies[index("TriggerTOSHlt1CharmCalibrationNoBiasDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1L0HighSumETJetDecision) { spotted = true; junkies[index("TriggerTOSHlt1L0HighSumETJetDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasCrossingForcedRecoFullZDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1BeamGasHighRhoVerticesDecision) { spotted = true; junkies[index("TriggerTOSHlt1BeamGasHighRhoVerticesDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1VertexDisplVertexDecision) { spotted = true; junkies[index("TriggerTOSHlt1VertexDisplVertexDecision")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSHlt1TrackAllL0TightDecision) { spotted = true; junkies[index("TriggerTOSHlt1TrackAllL0TightDecision")].m_tos += 1.; allentries_tos+=1.;break;}


      checkingPlace++;
      if (checkingPlace==order.size()) {spotted = true; allentries_tos+=1.;break;}
    }
    spotted = false;
    checkingPlace = 0u;
    while (!spotted) {
      unsigned checkingLine = 0u;


      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1DiMuonHighMassDecision) { spotted = true; junkies[index("TriggerDecHlt1DiMuonHighMassDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1DiMuonLowMassDecision) { spotted = true; junkies[index("TriggerDecHlt1DiMuonLowMassDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1SingleMuonNoIPDecision) { spotted = true; junkies[index("TriggerDecHlt1SingleMuonNoIPDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1SingleMuonHighPTDecision) { spotted = true; junkies[index("TriggerDecHlt1SingleMuonHighPTDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1TrackAllL0Decision) { spotted = true; junkies[index("TriggerDecHlt1TrackAllL0Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1TrackMuonDecision) { spotted = true; junkies[index("TriggerDecHlt1TrackMuonDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1TrackPhotonDecision) { spotted = true; junkies[index("TriggerDecHlt1TrackPhotonDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1LumiDecision) { spotted = true; junkies[index("TriggerDecHlt1LumiDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1LumiMidBeamCrossingDecision) { spotted = true; junkies[index("TriggerDecHlt1LumiMidBeamCrossingDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1MBNoBiasDecision) { spotted = true; junkies[index("TriggerDecHlt1MBNoBiasDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1L0AnyDecision) { spotted = true; junkies[index("TriggerDecHlt1L0AnyDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1L0AnyRateLimitedDecision) { spotted = true; junkies[index("TriggerDecHlt1L0AnyRateLimitedDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1L0AnyNoSPDDecision) { spotted = true; junkies[index("TriggerDecHlt1L0AnyNoSPDDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1L0AnyNoSPDRateLimitedDecision) { spotted = true; junkies[index("TriggerDecHlt1L0AnyNoSPDRateLimitedDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1NoPVPassThroughDecision) { spotted = true; junkies[index("TriggerDecHlt1NoPVPassThroughDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1DiProtonLowMultDecision) { spotted = true; junkies[index("TriggerDecHlt1DiProtonLowMultDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasNoBeamBeam1Decision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasNoBeamBeam1Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasNoBeamBeam2Decision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasNoBeamBeam2Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasBeam1Decision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasBeam1Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasBeam2Decision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasBeam2Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasCrossingEnhancedBeam1Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasCrossingEnhancedBeam2Decision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasCrossingForcedRecoDecision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasCrossingForcedRecoDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1ODINTechnicalDecision) { spotted = true; junkies[index("TriggerDecHlt1ODINTechnicalDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1Tell1ErrorDecision) { spotted = true; junkies[index("TriggerDecHlt1Tell1ErrorDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasCrossingParasiticDecision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasCrossingParasiticDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1ErrorEventDecision) { spotted = true; junkies[index("TriggerDecHlt1ErrorEventDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1Global) { spotted = true; junkies[index("TriggerDecHlt1Global")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1MBMicroBiasVeloDecision) { spotted = true; junkies[index("TriggerDecHlt1MBMicroBiasVeloDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision) { spotted = true; junkies[index("TriggerDecHlt1MBMicroBiasVeloRateLimitedDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1MBMicroBiasTStationDecision) { spotted = true; junkies[index("TriggerDecHlt1MBMicroBiasTStationDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision) { spotted = true; junkies[index("TriggerDecHlt1MBMicroBiasTStationRateLimitedDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1DiProtonDecision) { spotted = true; junkies[index("TriggerDecHlt1DiProtonDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1VeloClosingMicroBiasDecision) { spotted = true; junkies[index("TriggerDecHlt1VeloClosingMicroBiasDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1SingleElectronNoIPDecision) { spotted = true; junkies[index("TriggerDecHlt1SingleElectronNoIPDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1TrackForwardPassThroughDecision) { spotted = true; junkies[index("TriggerDecHlt1TrackForwardPassThroughDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1TrackForwardPassThroughLooseDecision) { spotted = true; junkies[index("TriggerDecHlt1TrackForwardPassThroughLooseDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1CharmCalibrationNoBiasDecision) { spotted = true; junkies[index("TriggerDecHlt1CharmCalibrationNoBiasDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1L0HighSumETJetDecision) { spotted = true; junkies[index("TriggerDecHlt1L0HighSumETJetDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasCrossingForcedRecoFullZDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1BeamGasHighRhoVerticesDecision) { spotted = true; junkies[index("TriggerDecHlt1BeamGasHighRhoVerticesDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1VertexDisplVertexDecision) { spotted = true; junkies[index("TriggerDecHlt1VertexDisplVertexDecision")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecHlt1TrackAllL0TightDecision) { spotted = true; junkies[index("TriggerDecHlt1TrackAllL0TightDecision")].m_evt += 1.; allentries_evt+=1.;break;}

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
    std::cout << givethehlt1(j) << "\t\t" << sigjun[j].m_evt << "\t\t\t" << sigjun[j].m_tos << std::endl;
  }
  std::cout << "\n\n\ncummulative background efficiencies" << std::endl;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    std::cout << givethehlt1(j) << "\t\t" << bkgjun[j].m_evt << "\t\t\t" << bkgjun[j].m_tos << std::endl;
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
      std::cout << givethehlt1(j) << "\t&\t" << sigjun[j].m_tos << "\t&\t" << bkgjun[j].m_tos << "\t&\t" << fom << "\\\\" << std::endl;
    } else {
      std::cout << givethehlt1(j) << "\t&\t" << sigjun[j].m_evt << "\t&\t" << bkgjun[j].m_evt << "\t&\t" << fom << "\\\\" << std::endl;
    }

  }

  return 0;
}
