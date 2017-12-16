#include "readNtuple.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <TH1F.h>
#include <TVector3.h>
#include <TMath.h>
#include <math.h>

#include "NeuroBayesExpert.hh"
// ---------------------------------------------------------------

// ---------------------------------------------------------------
readNtuple* expert(int varset = 0x149cf818, int version = 1, TTree* tree = NULL) 
{
  std::cout << "Start NeuroBayes Setup" << std::endl
    << "======================" << std::endl
    << std::endl;

  //
  // prepare skimmed ntuple
  //
  //create NeuroBayes instance
  //

  Expert* expert  = new Expert(Form("tau23mu_v%d_%x.nb",version,varset));
  float response;


  readNtuple* ntuple = new readNtuple(tree);
  TBranch* b_nb = ntuple->fChain->Branch(Form("NeuroBayes_v%d_0x%x",version,varset),&response,Form("NeuroBayes_v%d_0x%x/F",version,varset));
  /// do variable initialization here


  int varcount(0);
  if (varset & 1 << 0) {
    varcount++;
  }
  //inputvector.push_back(fffntuple->FlightDistanceError);
  if (varset & 1 << 1) {
    varcount++;
  }
  if (varset & 1 << 20) {
    varcount++;
  }
  if (varset & 1 << 2) {
    varcount++;
  }
  if (varset & 1 << 3) {
    varcount++;
  }
  if (varset & 1 << 4) {
    varcount++;
  }
  if (varset & 1 << 18) {
    varcount++;
  }
  if (varset & 1 << 19) {
    varcount++;
  }
  if (varset & 1 << 5) {
    varcount++;
  }
  if (varset & 1 << 6) {
    varcount++;
  }
  if (varset & 1 << 7) {
    varcount++;
  }
  if (varset & 1 << 8) {
    varcount++;
  }
  if (varset & 1 << 9) {
    varcount++;
  }
  if (varset & 1 << 10) {
    varcount++;
  }
  if (varset & 1 << 11) {
    varcount++;
  }
  if (varset & 1 << 12) {
    varcount++;
  }
  if (varset & 1 << 13) {
    varcount++;
  }
  if (varset & 1 << 14) {
    varcount++;
  }
  if (varset & 1 << 15) {
    varcount++;
  }
  if (varset & 1 << 16) {
    varcount++;
  }
  if (varset & 1 << 21) {
    varcount++;
  }
  if (varset & 1 << 21) {
    varcount++;
  }
  if (varset & 1 << 21) {
    varcount++;
  }
  if (varset & 1 << 22) {
    varcount++;
  }
  if (varset & 1 << 22) {
    varcount++;
  }
  if (varset & 1 << 22) {
    varcount++;
  }
  if (varset & 1 << 23) {
    varcount++;
  }
  if (varset & 1 << 24) {
    varcount++;
  }
  if (varset & 1 << 25) {
    varcount++;
  }
  if (varset & 1 << 26) {
    varcount++;
  }
  if (varset & 1 << 27) {
    varcount++;
  }
  if (varset & 1 << 27) {
    varcount++;
  }
  if (varset & 1 << 27) {
    varcount++;
  }
  if (varset & 1 << 28) {
    varcount++;
  }
  if (varset & 1 << 28) {
    varcount++;
  }
  if (varset & 1 << 28) {
    varcount++;
  }
  if (varset & 1 << 29) {
    varcount++;
  }
  if (varset & 1 << 30) {
    varcount++;
  }
  if (varset & 1 << 31) {
    varcount++;
    varcount++;
  }


  std::vector<float> inputvector;
  float* InputArray  = new float[varcount]; // array to hold input data

  std::cout << "initialised. now loop." << std::endl;
  // start event loop here
  Long64_t nentries = ntuple->fChain->GetEntries();
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if (nentries>20) {
      if (jentry % (int)((double)nentries/10.0) == 0)
        std::cout << "now read entry " << jentry << " of " << nentries <<  std::endl;
    } else {
      std::cout << "now read entry " << jentry << " of " << nentries <<  std::endl;
    }
    Long64_t ientry = ntuple->LoadTree(jentry);
    if (ientry < 0) break;
    ntuple->fChain->GetEntry(jentry);
    inputvector.clear();


    if (varset & 1 << 0) {
      inputvector.push_back(ntuple->FlightDistance);
    }
    //inputvector.push_back(ntuple->FlightDistanceError);
    if (varset & 1 << 1) {
      inputvector.push_back(ntuple->FlightDistance/ntuple->FlightDistanceError);
    }
    if (varset & 1 << 20) {
      inputvector.push_back(TMath::Exp(-1000*ntuple->LifeTime));
    }
    if (varset & 1 << 2) {
      inputvector.push_back(ntuple->IP);
    }
    if (varset & 1 << 3) {
      if (!(ntuple->IPSig==ntuple->IPSig)) {
        inputvector.push_back(-999);
      } else {
        inputvector.push_back(ntuple->IPSig);
      }
    }
    if (varset & 1 << 4) {
      inputvector.push_back(ntuple->VertexChi2);
    }
    if (varset & 1 << 18) {
      inputvector.push_back(acos(ntuple->dira));
    }
    if (varset & 1 << 19) {
      inputvector.push_back(ntuple->pt);
    }
    if (varset & 1 << 5) {
      inputvector.push_back(ntuple->p0_IP);
    }
    if (varset & 1 << 6) {
      inputvector.push_back(ntuple->p1_IP);
    }
    if (varset & 1 << 7) {
      inputvector.push_back(ntuple->p2_IP);
    }
    if (varset & 1 << 8) {
      inputvector.push_back(ntuple->p0_IPSig);
    }
    if (varset & 1 << 9) {
      inputvector.push_back(ntuple->p1_IPSig);
    }
    if (varset & 1 << 10) {
      inputvector.push_back(ntuple->p2_IPSig);
    }
    if (varset & 1 << 11) {
      inputvector.push_back(ntuple->Laura_SumBDT);
    }


    if (varset & 1 << 12) {
      inputvector.push_back(std::min(ntuple->p0_IPSig,std::min(ntuple->p1_IPSig,ntuple->p2_IPSig)));
    }


    if (varset & 1 << 13) {
      inputvector.push_back(ntuple->DOCAone);
    }
    if (varset & 1 << 14) {
      inputvector.push_back(ntuple->DOCAtwo);
    }
    if (varset & 1 << 15) {
      inputvector.push_back(ntuple->DOCAthree);
    }

    if (varset & 1 << 16) {
      inputvector.push_back(std::max(std::max(ntuple->DOCAone,ntuple->DOCAtwo),ntuple->DOCAthree));
    }



    if (varset & 1 << 21) {
      inputvector.push_back(ntuple->isolationa);
    }
    if (varset & 1 << 21) {
      inputvector.push_back(ntuple->isolationb);
    }
    if (varset & 1 << 21) {
      inputvector.push_back(ntuple->isolationc);
    }
    if (varset & 1 << 22) {
      inputvector.push_back(ntuple->isolationd);
    }
    if (varset & 1 << 22) {
      inputvector.push_back(ntuple->isolatione);
    }
    if (varset & 1 << 22) {
      inputvector.push_back(ntuple->isolationf);
    }
    if (varset & 1 << 23) {
      inputvector.push_back(ntuple->iso);
    }
    if (varset & 1 << 24) {
      inputvector.push_back((1==ntuple->CDF1)?(-999):(ntuple->CDF1));
    }
    if (varset & 1 << 25) {
      inputvector.push_back((1==ntuple->CDF2)?(-999):(ntuple->CDF2));
    }
    if (varset & 1 << 26) {
      inputvector.push_back((1==ntuple->CDF3)?(-999):(ntuple->CDF3));
    }

    //   inputvector.push_back(ntuple->IP_p0p2);
    //   factory->AddVariable("IP_p1p2");


    //   factory->AddVariable("p0_pt");
    //   factory->AddVariable("p1_pt");
    //   factory->AddVariable("p2_pt");
    //   factory->AddVariable("p0_eta");
    //   factory->AddVariable("p1_eta");
    //   factory->AddVariable("p2_eta");
    if (varset & 1 << 27) {
      inputvector.push_back(ntuple->p0_track_Chi2Dof);
    }
    if (varset & 1 << 27) {
      inputvector.push_back(ntuple->p1_track_Chi2Dof);
    }
    if (varset & 1 << 27) {
      inputvector.push_back(ntuple->p2_track_Chi2Dof);
    }

    if (varset & 1 << 28) {
      inputvector.push_back(ntuple->p0_track_MatchChi2);
    }
    if (varset & 1 << 28) {
      inputvector.push_back(ntuple->p1_track_MatchChi2);
    }
    if (varset & 1 << 28) {
      inputvector.push_back(ntuple->p2_track_MatchChi2);
    }

    if (varset & 1 << 29) {
      inputvector.push_back(std::max(ntuple->p0_track_MatchChi2,std::max(ntuple->p1_track_MatchChi2,ntuple->p2_track_MatchChi2)));
    }

    if (varset & 1 << 30) {
      inputvector.push_back(ntuple->polarisationangle);
    }
    if (varset & 1 << 31) {
      inputvector.push_back(ntuple->mass_p0p2);
      inputvector.push_back(ntuple->mass_p1p2);
    }



    bool valid = true;
    for (unsigned i = 0 ; i < inputvector.size() ; ++i) {
      if (!(inputvector[i]==inputvector[i])) valid = false;
      InputArray[i] = (inputvector[i]);
    }
    if (!valid || 0==ntuple->cleaningcut) {
      response = -999.;
    } else {
      response = expert->nb_expert(InputArray);
    }
    b_nb->Fill();


  }// for
  // end event loop
  std::cout << "done looping" << std::endl;


  delete InputArray;
  delete expert;

  return ntuple;

} // void expert

int main(int argc, char** argv) {
  if (2>argc) {
    std::cout << "USAGE expert <varset=0x149cf818> <version=1> <filename(s)>" << std::endl;
    return 1;
  }
  char* buffer;
  int var = strtol(argv[1],&buffer,0);
  int ver = strtol(argv[2],&buffer,0);
  //for (int i = 2 ; i < argc ; ++i) {
  //  TFile* ff = new TFile(argv[i],"update");
  //  TTree* tree;
  //  ff->GetObject("Tau23Mu",tree);
  //  printf("run with varset 0x%x\n",var);
  //  readNtuple* tup = expert(var,tree);
  //  ff->WriteTObject(tree);
  //  ff->Close();
  //  delete ff;
  //  delete tup;
  //}

  for (int i = 3 ; i < argc ; ++i) {
    TFile* ff = new TFile(argv[i],"update");
    std::map<std::string,int> done;
    for (int treeid = 0 ; treeid < ff->GetListOfKeys()->GetEntries() ; ++treeid) {
      done[ff->GetListOfKeys()->At(treeid)->GetName()] = 0;
    }
    ff->Close();
    delete ff;
    for (std::map<std::string,int>::iterator  it  = done.begin() ; it != done.end() ; ++it) {
      if (1==it->second) continue;
      printf("now initiating tree %s in file %s for setting 0x%x\n", it->first.c_str(), argv[i], var);
      TFile* ff = new TFile(argv[i],"update");
      TTree* tree;
      ff->GetObject((((std::string)it->first).c_str()),tree);
      printf("run with varset 0x%x\n",var);
      readNtuple* tup = expert(var,ver,tree);
      ff->WriteTObject(tree);
      ff->Close();
      delete ff;
      delete tup;
      //TFile* ff_out = new TFile(argv[i+1],"update");
      //outtree = intree->CloneTree(0);
      //printf("now doing tree %s in file %s for setting 0x%x\n", it->first.c_str(), argv[i], varset);
      //outtree = TMVACC("",varset,intree,outtree);
      //printf("now done tree %s in file %s for setting 0x%x\n", it->first.c_str(), argv[i], varset);
      //std::cout << "tree to be written is " << outtree << std::endl;
      //ff_out->WriteTObject(outtree);
      //printf("now written outtree\n");
      //done[it->first] = 1;
      //ff_in->Close();
      //printf("closed first file\n");
      //ff_out->Close();
      //printf("closed second file\n");
      //delete ff_in;
      //printf("deleted first file\n");
      //delete ff_out;
      //printf("deleted second file\n");
    }
  }


  return 0;
}
