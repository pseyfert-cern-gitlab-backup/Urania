#define generatorclass_cxx
#include "generatorclass.h"
#include <stdlib.h>
#include <TH2.h>
#include <iostream>
#include <map>
#include <TStyle.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <TRandom3.h>
#include <Math/Vector4D.h>
//#include "profiler.h"

void generatorclass::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L generatorclass.C
  //      Root > generatorclass t
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
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  TFile* fout = new TFile("output.root","recreate");
  TNtuple* dalitz = new TNtuple("dalitz","Dalitz_Plot","m02:m12:m01");
  TRandom* rnd = new TRandom3();
  Long64_t nbytes = 0, nb = 0;
  std::map<unsigned,unsigned> taus;
  unsigned m_didntfindmuons(0u);
  unsigned m_written(0u);
  unsigned m_didntfindenough(0u);
   //ProfilerStart("profile");
  int prompted = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    taus.clear();
    for (Int_t u = 0 ; u < NPart ; ++u) {
      if (15==abs(pdgId[u])) {
        taus[u] = 0u;
      }
    }
    for (Int_t u = 0 ; u < NPart ; ++u) {
      if ((13==abs(pdgId[u])) && (15==abs(pdgIdMother[u]))) {
        taus[indexMother[u]] += 1;
      }
    }
    std::map<unsigned,unsigned>::const_iterator iter;
    for ( iter=taus.begin() ; taus.end() != iter ; ++iter ) {
      if (3u != iter->second) {
        unsigned mucount(0u);
        if (13==abs(pdgIdDau1[iter->first])) mucount++;
        if (13==abs(pdgIdDau2[iter->first])) mucount++;
        if (13==abs(pdgIdDau3[iter->first])) mucount++;
        if (13==abs(pdgIdDau4[iter->first])) mucount++;
        if (13==abs(pdgIdDau5[iter->first])) mucount++;
        if (13==abs(pdgIdDau6[iter->first])) mucount++;
        if (3u==mucount) m_didntfindenough++;
        continue;
      }
      Int_t theos = 3000;
      Int_t thess1 = 3000;
      Int_t thess2 = 3000;
      for (Int_t u = 0 ; u < NPart ; ++u) {
        if ((13==abs(pdgId[u])) && (15==abs(pdgIdMother[u]))) {
          if (iter->first == indexMother[u]) {
            if (pdgId[u] * pdgId[(Int_t)indexMother[u]] < 0) {
              theos = u;
              continue;
            }
            if (thess1 >2999) thess1 = u;
            else thess2 = u;
          } /// muon from THE tau
        } /// interesting muon from A interesting tau
      } /// loop to find the muons
      if (3==prompted) {
        Int_t i = theos;
        ROOT::Math::PxPyPzEVector vec(px[i],py[i],pz[i],e[i]);
        std::cout << "mumass = " << vec.M() << std::endl;
        i = indexMother[i];
        vec = ROOT::Math::PxPyPzEVector(px[i],py[i],pz[i],e[i]);
        std::cout << "taumass = " << vec.M() << std::endl;
        ROOT::Math::PxPyPzEVector vecos(px[theos],py[theos],pz[theos],e[theos]);
        ROOT::Math::PxPyPzEVector vecss1(px[thess1],py[thess1],pz[thess1],e[thess1]);
        ROOT::Math::PxPyPzEVector vecss2(px[thess2],py[thess2],pz[thess2],e[thess2]);
        vecos += vecss1;
        vecos += vecss2;
        std::cout << "recmass = " << vecos.M() << std::endl;
        prompted++;
      }
      if (prompted<3) prompted++;
      if (theos <3000 && thess1 <3000 && thess2 <3000) {
        ROOT::Math::PxPyPzEVector vecos(px[theos],py[theos],pz[theos],e[theos]);
        ROOT::Math::PxPyPzEVector vecss1(px[thess1],py[thess1],pz[thess1],e[thess1]);
        ROOT::Math::PxPyPzEVector vecss2(px[thess2],py[thess2],pz[thess2],e[thess2]);
        if (fabs(vecss1.E() - e[thess1])/e[thess1] >0.01) {
          std::cout << "ERROR" << std::endl;
          return ;
        }
        double m02 = (vecos+vecss1).M();
        double m12 = (vecos+vecss2).M();
        double m01 = (vecss1+vecss2).M();


        if (rnd->Rndm() > .5)
          dalitz->Fill(m02,m12,m01);
        else
          dalitz->Fill(m12,m02,m01);
        m_written++;
      } else {
        m_didntfindmuons++;
      }

    } /// loop over taus
  }
   //ProfilerStop();
  std::cout << m_written << " tau went well" << std::endl;
  std::cout << "where are the three? " <<      m_didntfindmuons << std::endl;
  std::cout << "NPart too small!!!!! " <<      m_didntfindenough << std::endl;
  fout->WriteTObject(dalitz);
  fout->Close();

}
