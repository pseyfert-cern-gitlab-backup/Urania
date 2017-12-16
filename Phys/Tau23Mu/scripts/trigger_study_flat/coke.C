#define coke_cxx
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
  if (!(TriggerTOSHlt1TrackMuonDecision)) return true;

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


  for (unsigned j = 0 ; j < index("maxl0") ; ++j) {
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

    if (0.5 < TriggerTOSL0B1gas) junkies[index("TriggerTOSL0B1gas")].m_tos += 1.;
    if (0.5 < TriggerTOSL0B2gas) junkies[index("TriggerTOSL0B2gas")].m_tos += 1.;
    if (0.5 < TriggerTOSL0Calo) junkies[index("TriggerTOSL0Calo")].m_tos += 1.;
    if (0.5 < TriggerTOSL0DiMuon) junkies[index("TriggerTOSL0DiMuon")].m_tos += 1.;
    if (0.5 < TriggerTOSL0DiMuonlowMult) junkies[index("TriggerTOSL0DiMuonlowMult")].m_tos += 1.;
    if (0.5 < TriggerTOSL0Electron) junkies[index("TriggerTOSL0Electron")].m_tos += 1.;
    if (0.5 < TriggerTOSL0GlobalPi0) junkies[index("TriggerTOSL0GlobalPi0")].m_tos += 1.;
    if (0.5 < TriggerTOSL0HCAL) junkies[index("TriggerTOSL0HCAL")].m_tos += 1.;
    if (0.5 < TriggerTOSL0Hadron) junkies[index("TriggerTOSL0Hadron")].m_tos += 1.;
    if (0.5 < TriggerTOSL0LocalPi0) junkies[index("TriggerTOSL0LocalPi0")].m_tos += 1.;
    if (0.5 < TriggerTOSL0MuonMinbias) junkies[index("TriggerTOSL0MuonMinbias")].m_tos += 1.;
    if (0.5 < TriggerTOSL0Muon) junkies[index("TriggerTOSL0Muon")].m_tos += 1.;
    if (0.5 < TriggerTOSL0MuonLowMult) junkies[index("TriggerTOSL0MuonLowMult")].m_tos += 1.;
    if (0.5 < TriggerTOSL0PU) junkies[index("TriggerTOSL0PU")].m_tos += 1.;
    if (0.5 < TriggerTOSL0PU20) junkies[index("TriggerTOSL0PU20")].m_tos += 1.;
    if (0.5 < TriggerTOSL0Photon) junkies[index("TriggerTOSL0Photon")].m_tos += 1.;
    if (0.5 < TriggerTOSL0SPD) junkies[index("TriggerTOSL0SPD")].m_tos += 1.;
    if (0.5 < TriggerTOSL0SPD40) junkies[index("TriggerTOSL0SPD40")].m_tos += 1.;


    if (0.5 < TriggerDecL0B1gas) junkies[index("TriggerDecL0B1gas")].m_evt += 1.;
    if (0.5 < TriggerDecL0B2gas) junkies[index("TriggerDecL0B2gas")].m_evt += 1.;
    if (0.5 < TriggerDecL0Calo) junkies[index("TriggerDecL0Calo")].m_evt += 1.;
    if (0.5 < TriggerDecL0DiMuon) junkies[index("TriggerDecL0DiMuon")].m_evt += 1.;
    if (0.5 < TriggerDecL0DiMuonlowMult) junkies[index("TriggerDecL0DiMuonlowMult")].m_evt += 1.;
    if (0.5 < TriggerDecL0Electron) junkies[index("TriggerDecL0Electron")].m_evt += 1.;
    if (0.5 < TriggerDecL0GlobalPi0) junkies[index("TriggerDecL0GlobalPi0")].m_evt += 1.;
    if (0.5 < TriggerDecL0HCAL) junkies[index("TriggerDecL0HCAL")].m_evt += 1.;
    if (0.5 < TriggerDecL0Hadron) junkies[index("TriggerDecL0Hadron")].m_evt += 1.;
    if (0.5 < TriggerDecL0LocalPi0) junkies[index("TriggerDecL0LocalPi0")].m_evt += 1.;
    if (0.5 < TriggerDecL0MuonMinbias) junkies[index("TriggerDecL0MuonMinbias")].m_evt += 1.;
    if (0.5 < TriggerDecL0Muon) junkies[index("TriggerDecL0Muon")].m_evt += 1.;
    if (0.5 < TriggerDecL0MuonLowMult) junkies[index("TriggerDecL0MuonLowMult")].m_evt += 1.;
    if (0.5 < TriggerDecL0PU) junkies[index("TriggerDecL0PU")].m_evt += 1.;
    if (0.5 < TriggerDecL0PU20) junkies[index("TriggerDecL0PU20")].m_evt += 1.;
    if (0.5 < TriggerDecL0Photon) junkies[index("TriggerDecL0Photon")].m_evt += 1.;
    if (0.5 < TriggerDecL0SPD) junkies[index("TriggerDecL0SPD")].m_evt += 1.;
    if (0.5 < TriggerDecL0SPD40) junkies[index("TriggerDecL0SPD40")].m_evt += 1.;




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

  for (unsigned j = 0 ; j < index("maxl0") ; ++j) {
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


      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0B1gas) { spotted = true; junkies[index("TriggerTOSL0B1gas")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0B2gas) { spotted = true; junkies[index("TriggerTOSL0B2gas")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0Calo) { spotted = true; junkies[index("TriggerTOSL0Calo")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0DiMuon) { spotted = true; junkies[index("TriggerTOSL0DiMuon")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0DiMuonlowMult) { spotted = true; junkies[index("TriggerTOSL0DiMuonlowMult")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0Electron) { spotted = true; junkies[index("TriggerTOSL0Electron")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0GlobalPi0) { spotted = true; junkies[index("TriggerTOSL0GlobalPi0")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0HCAL) { spotted = true; junkies[index("TriggerTOSL0HCAL")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0Hadron) { spotted = true; junkies[index("TriggerTOSL0Hadron")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0LocalPi0) { spotted = true; junkies[index("TriggerTOSL0LocalPi0")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0MuonMinbias) { spotted = true; junkies[index("TriggerTOSL0MuonMinbias")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0Muon) { spotted = true; junkies[index("TriggerTOSL0Muon")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0MuonLowMult) { spotted = true; junkies[index("TriggerTOSL0MuonLowMult")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0PU) { spotted = true; junkies[index("TriggerTOSL0PU")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0PU20) { spotted = true; junkies[index("TriggerTOSL0PU20")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0Photon) { spotted = true; junkies[index("TriggerTOSL0Photon")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0SPD) { spotted = true; junkies[index("TriggerTOSL0SPD")].m_tos += 1.; allentries_tos+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerTOSL0SPD40) { spotted = true; junkies[index("TriggerTOSL0SPD40")].m_tos += 1.; allentries_tos+=1.;break;}


      checkingPlace++;
      if (checkingPlace==order.size()) {spotted = true; allentries_tos+=1.;break;}
    }
    spotted = false;
    checkingPlace = 0u;
    while (!spotted) {
      unsigned checkingLine = 0u;


      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0B1gas) { spotted = true; junkies[index("TriggerDecL0B1gas")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0B2gas) { spotted = true; junkies[index("TriggerDecL0B2gas")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0Calo) { spotted = true; junkies[index("TriggerDecL0Calo")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0DiMuon) { spotted = true; junkies[index("TriggerDecL0DiMuon")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0DiMuonlowMult) { spotted = true; junkies[index("TriggerDecL0DiMuonlowMult")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0Electron) { spotted = true; junkies[index("TriggerDecL0Electron")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0GlobalPi0) { spotted = true; junkies[index("TriggerDecL0GlobalPi0")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0HCAL) { spotted = true; junkies[index("TriggerDecL0HCAL")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0Hadron) { spotted = true; junkies[index("TriggerDecL0Hadron")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0LocalPi0) { spotted = true; junkies[index("TriggerDecL0LocalPi0")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0MuonMinbias) { spotted = true; junkies[index("TriggerDecL0MuonMinbias")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0Muon) { spotted = true; junkies[index("TriggerDecL0Muon")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0MuonLowMult) { spotted = true; junkies[index("TriggerDecL0MuonLowMult")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0PU) { spotted = true; junkies[index("TriggerDecL0PU")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0PU20) { spotted = true; junkies[index("TriggerDecL0PU20")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0Photon) { spotted = true; junkies[index("TriggerDecL0Photon")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0SPD) { spotted = true; junkies[index("TriggerDecL0SPD")].m_evt += 1.; allentries_evt+=1.;break;}
      if (checkingLine++ == order[checkingPlace]) if (0.5 < TriggerDecL0SPD40) { spotted = true; junkies[index("TriggerDecL0SPD40")].m_evt += 1.; allentries_evt+=1.;break;}

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


  std::cout << "exclusive signal efficiencies" << std::endl;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    std::cout << givethel0(j) << "\t\t" << sigjun[j].m_evt << "\t\t\t" << sigjun[j].m_tos << std::endl;
  }
  std::cout << "\n\n\nexclusive background efficiencies" << std::endl;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    std::cout << givethel0(j) << "\t\t" << bkgjun[j].m_evt << "\t\t\t" << bkgjun[j].m_tos << std::endl;
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
    std::cout << givethel0(j) << "\t\t" << sigjun[j].m_evt << "\t\t\t" << sigjun[j].m_tos << std::endl;
  }
  std::cout << "\n\n\ncummulative background efficiencies" << std::endl;
  for (unsigned i = 0 ; i < indizes.size() ; ++i) {
    unsigned j = indizes[i];
    std::cout << givethel0(j) << "\t\t" << bkgjun[j].m_evt << "\t\t\t" << bkgjun[j].m_tos << std::endl;
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
      std::cout << givethel0(j) << "\t&\t" << sigjun[j].m_tos << "\t&\t" << bkgjun[j].m_tos << "\t&\t" << fom << "\\\\" << std::endl;
    } else {
      std::cout << givethel0(j) << "\t&\t" << sigjun[j].m_evt << "\t&\t" << bkgjun[j].m_evt << "\t&\t" << fom << "\\\\" << std::endl;
    }

  }

  return 0;
}
