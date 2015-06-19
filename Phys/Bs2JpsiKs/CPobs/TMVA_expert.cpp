// #############################################################################
// Phys/Bs2JpsiKs Package
// Boosted Decision Tree Expert
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes ***
// General C++
#include <iostream>

// Root
#include <TBranch.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>

#include <TMVA/Config.h>
#include <TMVA/Factory.h>
#include <TMVA/MethodCuts.h>
#include <TMVA/Reader.h>
#include <TMVA/Tools.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// #############################################################################
// *** Declarations ***
void fillBDTExpert(const TString ID, IB2JpsiX* trainTuple, 
                   float& bdtVar, TMVA::Reader *reader);

// #############################################################################
// *** Expert ***
int runExpert(const TString module, const TString data, const TString step,
              const TString dir, const TString decay,
              const TString weightMethod, const TString BDTtraining) {
                       
// ***** PART 0: Initialise ***** //
////////////////////////////////////

  std::cout << "\n PROGRESS: Loading Data \n" << std::endl;

  // *** Load NTuple ***
  IB2JpsiX* trainTuple = loadTuple(module, data, step, dir, decay, weightMethod);
  if (!trainTuple) {
    std::cout << "ERROR: Ntuple could not be loaded" << std::endl;
    return -1;
  }

  // *** Set Output ***
  TString outFileName = makeFileName(module, data, step, dir, decay,
                                     weightMethod);
  // Error Handling
  if (outFileName=="") {
    std::cout << "ERROR: Failed to generate output file." << std::endl;
    return -1;
  }
  TFile *outfile = new TFile(outFileName, "RECREATE");
  outfile->cd();

// ***** PART I: Initialise Reader ***** //
///////////////////////////////////////////

    std::cout << "\n PROGRESS: Preparing TMVA Expert \n" << std::endl;

  // *** Declare Selection Variables ***
  float dtfcVar = -999;
  float otclVar = -999;
  float primVar = -999;
  float spdmVar = -999;
  float b0meVar = -999;
  float b0ptVar = -999;
  float bch2Var = -999;
  float bmomVar = -999;
  float diraVar = -999;
  float jchiVar = -999;
  float jipcVar = -999;
  float jmasVar = -999;
  float jmmeVar = -999;
  float jmomVar = -999;
  float jpptVar = -999;
  float kipcVar = -999;
  float kschVar = -999;
  float ksezVar = -999;
  float ksfdVar = -999;
  float ksmeVar = -999;
  float ksmmVar = -999;
  float ksmoVar = -999;
  float ksptVar = -999;
  float kstaVar = -999;
  float muicVar = -999;
  float muidVar = -999;
  float muipVar = -999;
  float mumoVar = -999;
  float muptVar = -999;
  float mutkVar = -999;
  float pidkVar = -999;
  float pigpVar = -999;
  float piicVar = -999;
  float piipVar = -999;
  float pimoVar = -999;
  float piptVar = -999;
  float pitkVar = -999;

  // *** Create TMVA Reader for Long KS ***
  TMVA::Reader *reader_LL = new TMVA::Reader("Color:!Silent");

  trainTuple->defineConstants(step, 3);
  fillBDTExpert("dtfc", trainTuple, dtfcVar, reader_LL);
  fillBDTExpert("otcl", trainTuple, otclVar, reader_LL);
  fillBDTExpert("prim", trainTuple, primVar, reader_LL);
  fillBDTExpert("spdm", trainTuple, spdmVar, reader_LL);
  fillBDTExpert("b0me", trainTuple, b0meVar, reader_LL);
  fillBDTExpert("b0pt", trainTuple, b0ptVar, reader_LL);
  fillBDTExpert("bch2", trainTuple, bch2Var, reader_LL);
  fillBDTExpert("bmom", trainTuple, bmomVar, reader_LL);
  fillBDTExpert("dira", trainTuple, diraVar, reader_LL);
  fillBDTExpert("jchi", trainTuple, jchiVar, reader_LL);
  fillBDTExpert("jipc", trainTuple, jipcVar, reader_LL);
  fillBDTExpert("jmas", trainTuple, jmasVar, reader_LL);
  fillBDTExpert("jmme", trainTuple, jmmeVar, reader_LL);
  fillBDTExpert("jmom", trainTuple, jmomVar, reader_LL);
  fillBDTExpert("jppt", trainTuple, jpptVar, reader_LL);
  fillBDTExpert("kipc", trainTuple, kipcVar, reader_LL);
  fillBDTExpert("ksch", trainTuple, kschVar, reader_LL);
  fillBDTExpert("ksez", trainTuple, ksezVar, reader_LL);
  fillBDTExpert("ksfd", trainTuple, ksfdVar, reader_LL);
  fillBDTExpert("ksme", trainTuple, ksmeVar, reader_LL);
  fillBDTExpert("ksmm", trainTuple, ksmmVar, reader_LL);
  fillBDTExpert("ksmo", trainTuple, ksmoVar, reader_LL);
  fillBDTExpert("kspt", trainTuple, ksptVar, reader_LL);
  fillBDTExpert("ksta", trainTuple, kstaVar, reader_LL);
  fillBDTExpert("muic", trainTuple, muicVar, reader_LL);
  fillBDTExpert("muid", trainTuple, muidVar, reader_LL);
  fillBDTExpert("muip", trainTuple, muipVar, reader_LL);
  fillBDTExpert("mumo", trainTuple, mumoVar, reader_LL);
  fillBDTExpert("mupt", trainTuple, muptVar, reader_LL);
  fillBDTExpert("mutk", trainTuple, mutkVar, reader_LL);
  fillBDTExpert("pidk", trainTuple, pidkVar, reader_LL);
  fillBDTExpert("pigp", trainTuple, pigpVar, reader_LL);
  fillBDTExpert("piic", trainTuple, piicVar, reader_LL);
  fillBDTExpert("piip", trainTuple, piipVar, reader_LL);
  fillBDTExpert("pimo", trainTuple, pimoVar, reader_LL);
  fillBDTExpert("pipt", trainTuple, piptVar, reader_LL);
  fillBDTExpert("pitk", trainTuple, pitkVar, reader_LL);

  reader_LL->BookMVA("myBDT", "weights/TMVA_BDT_"+BDTtraining+"_LL.weights.xml");

  // *** Create TMVA Reader for Down KS ***
  TMVA::Reader *reader_DD = new TMVA::Reader("Color:!Silent");

  trainTuple->defineConstants(step, 5);
  fillBDTExpert("dtfc", trainTuple, dtfcVar, reader_DD);
  fillBDTExpert("otcl", trainTuple, otclVar, reader_DD);
  fillBDTExpert("prim", trainTuple, primVar, reader_DD);
  fillBDTExpert("spdm", trainTuple, spdmVar, reader_DD);
  fillBDTExpert("b0me", trainTuple, b0meVar, reader_DD);
  fillBDTExpert("b0pt", trainTuple, b0ptVar, reader_DD);
  fillBDTExpert("bch2", trainTuple, bch2Var, reader_DD);
  fillBDTExpert("bmom", trainTuple, bmomVar, reader_DD);
  fillBDTExpert("dira", trainTuple, diraVar, reader_DD);
  fillBDTExpert("jchi", trainTuple, jchiVar, reader_DD);
  fillBDTExpert("jipc", trainTuple, jipcVar, reader_DD);
  fillBDTExpert("jmas", trainTuple, jmasVar, reader_DD);
  fillBDTExpert("jmme", trainTuple, jmmeVar, reader_DD);
  fillBDTExpert("jmom", trainTuple, jmomVar, reader_DD);
  fillBDTExpert("jppt", trainTuple, jpptVar, reader_DD);
  fillBDTExpert("kipc", trainTuple, kipcVar, reader_DD);
  fillBDTExpert("ksch", trainTuple, kschVar, reader_DD);
  fillBDTExpert("ksez", trainTuple, ksezVar, reader_DD);
  fillBDTExpert("ksfd", trainTuple, ksfdVar, reader_DD);
  fillBDTExpert("ksme", trainTuple, ksmeVar, reader_DD);
  fillBDTExpert("ksmm", trainTuple, ksmmVar, reader_DD);
  fillBDTExpert("ksmo", trainTuple, ksmoVar, reader_DD);
  fillBDTExpert("kspt", trainTuple, ksptVar, reader_DD);
  fillBDTExpert("ksta", trainTuple, kstaVar, reader_DD);
  fillBDTExpert("muic", trainTuple, muicVar, reader_DD);
  fillBDTExpert("muid", trainTuple, muidVar, reader_DD);
  fillBDTExpert("muip", trainTuple, muipVar, reader_DD);
  fillBDTExpert("mumo", trainTuple, mumoVar, reader_DD);
  fillBDTExpert("mupt", trainTuple, muptVar, reader_DD);
  fillBDTExpert("mutk", trainTuple, mutkVar, reader_DD);
  fillBDTExpert("pidk", trainTuple, pidkVar, reader_DD);
  fillBDTExpert("pigp", trainTuple, pigpVar, reader_DD);
  fillBDTExpert("piic", trainTuple, piicVar, reader_DD);
  fillBDTExpert("piip", trainTuple, piipVar, reader_DD);
  fillBDTExpert("pimo", trainTuple, pimoVar, reader_DD);
  fillBDTExpert("pipt", trainTuple, piptVar, reader_DD);
  fillBDTExpert("pitk", trainTuple, pitkVar, reader_DD);

  reader_DD->BookMVA("myBDT", "weights/TMVA_BDT_"+BDTtraining+"_DD.weights.xml");

// ***** PART II: Create Tree ***** //
//////////////////////////////////////
  
  std::cout << "\n PROGRESS: Creating Tree \n" << std::endl; 

  // *** Initialise ***
  // Variables
  const int nleafs = 25;
  ULong64_t eventNumber = 0;
  UInt_t runNumber = 0;
  unsigned int nPVs  = 0;
  Int_t tracktype = 0;
  Float_t sweight[nleafs];
  Float_t netOutput[nleafs];
  Double_t mass[nleafs];
  Double_t time[nleafs];
  unsigned int unbiased = 0;

  // Tree
  TTree* outtree = new TTree("NetTree", "Neural Net Tree");
  outtree->Branch("eventNumberNet", &eventNumber, "eventNumberNet/l");
  outtree->Branch("runNumberNet",   &runNumber,   "runNumberNet/i");
  outtree->Branch("nPVsNet",        &nPVs,        "nPVsNet/I");
  outtree->Branch("tracktypeNet",   &tracktype,   "tracktypeNet/I");
  outtree->Branch("sweightNet",     &sweight,     "sweightNet[nPVsNet]/F");
  outtree->Branch("netOutput",      &netOutput,   "netOutput[nPVsNet]/F");
  outtree->Branch("massNet",        &mass,        "massNet[nPVsNet]/D");
  outtree->Branch("timeNet",        &time,        "timeNet[nPVsNet]/D");
  if (step==m_NNUnbiased) {
    outtree->Branch("unbiased", &unbiased, "unbiased/I");
  }
  outtree->SetDirectory(outfile); 

  // *** Fill Tree ***
  std::cout << "\n PROGRESS: Running TMVA Expert \n" << std::endl; 
  const Long64_t nentries = trainTuple->nEntries();
  const Long64_t printMod = printFrac(nentries); 
  Long64_t nFailed = 0;
  Long64_t nGood = 0;

  std::cout << "EXPERT: Will loop over " << nentries << " entries." << std::endl;
  for (Long64_t i=0; i<nentries;i++) {
    trainTuple->GetChain()->GetEntry(i);

    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }

    // Fill Variables
    runNumber   = trainTuple->getRunNumber();
    eventNumber = trainTuple->getEventNumber();
    nPVs        = trainTuple->primaries();
    tracktype   = trainTuple->TrackType();
    unbiased    = trainTuple->isUnbiased();

    trainTuple->defineConstants(step, tracktype);
    for (unsigned int pv = 0; pv!= nPVs; pv++) {
      // Fill Arrays
      sweight[pv] = trainTuple->weightVal(pv);
      mass[pv]    = trainTuple->mass(pv);
      time[pv]    = trainTuple->time(pv);

      // Get Neural Net Output
      if (sweight[pv]>-7) {

        // Array for TMVA
        TString varName = "";
        trainTuple->fillVar("dtfc", pv, varName, dtfcVar);
        trainTuple->fillVar("otcl", pv, varName, otclVar);
        trainTuple->fillVar("prim", pv, varName, primVar);
        trainTuple->fillVar("spdm", pv, varName, spdmVar);
        trainTuple->fillVar("b0me", pv, varName, b0meVar);
        trainTuple->fillVar("b0pt", pv, varName, b0ptVar);
        trainTuple->fillVar("bch2", pv, varName, bch2Var);
        trainTuple->fillVar("bmom", pv, varName, bmomVar);
        trainTuple->fillVar("dira", pv, varName, diraVar);
        trainTuple->fillVar("jchi", pv, varName, jchiVar);
        trainTuple->fillVar("jipc", pv, varName, jipcVar);
        trainTuple->fillVar("jmas", pv, varName, jmasVar);
        trainTuple->fillVar("jmme", pv, varName, jmmeVar);
        trainTuple->fillVar("jmom", pv, varName, jmomVar);
        trainTuple->fillVar("jppt", pv, varName, jpptVar);
        trainTuple->fillVar("kipc", pv, varName, kipcVar);
        trainTuple->fillVar("ksch", pv, varName, kschVar);
        trainTuple->fillVar("ksez", pv, varName, ksezVar);
        trainTuple->fillVar("ksfd", pv, varName, ksfdVar);
        trainTuple->fillVar("ksme", pv, varName, ksmeVar);
        trainTuple->fillVar("ksmm", pv, varName, ksmmVar);
        trainTuple->fillVar("ksmo", pv, varName, ksmoVar);
        trainTuple->fillVar("kspt", pv, varName, ksptVar);
        trainTuple->fillVar("ksta", pv, varName, kstaVar);
        trainTuple->fillVar("muic", pv, varName, muicVar);
        trainTuple->fillVar("muid", pv, varName, muidVar);
        trainTuple->fillVar("muip", pv, varName, muipVar);
        trainTuple->fillVar("mumo", pv, varName, mumoVar);
        trainTuple->fillVar("mupt", pv, varName, muptVar);
        trainTuple->fillVar("mutk", pv, varName, mutkVar);
        trainTuple->fillVar("pidk", pv, varName, pidkVar);
        trainTuple->fillVar("pigp", pv, varName, pigpVar);
        trainTuple->fillVar("piic", pv, varName, piicVar);
        trainTuple->fillVar("piip", pv, varName, piipVar);
        trainTuple->fillVar("pimo", pv, varName, pimoVar);
        trainTuple->fillVar("pipt", pv, varName, piptVar);
        trainTuple->fillVar("pitk", pv, varName, pitkVar);

        if (tracktype==m_LL) {
          netOutput[pv] = reader_LL->EvaluateMVA("myBDT");
        } else if (tracktype==m_DD && step==m_NNKstar) {
          netOutput[pv] = 1.;
        } else if (tracktype==m_DD) {
          netOutput[pv] = reader_DD->EvaluateMVA("myBDT");;
        } else {
          netOutput[pv] = ErrorCodes::Error;
        }
        nGood++;  
      } else {
        netOutput[pv] = sweight[pv];
        nFailed++;
      }
    } // pvs
    outtree->Fill();
  }
  
  // *** Results ***
  std::cout << "########################################" << std::endl;
  std::cout << "  RESULTS" << std::endl;
  std::cout << "  # Events with netOutput assigned: " << nGood   << std::endl;
  std::cout << "  # Events failing previous cuts  : " << nFailed << std::endl; 
  std::cout << "########################################" << std::endl;

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
  outfile->cd();
  outtree->Write();
  outfile->Close();
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
} 

// #############################################################################
void fillBDTExpert(const TString ID, IB2JpsiX* trainTuple,
                   float& bdtVar, TMVA::Reader *reader) {
  int varID = (trainTuple->mvaVars->find(ID)->second);
  if (varID>=0) {
    TString name = "";
    float value = -999.;
    trainTuple->fillVar(ID, 0, name, value);
    reader->AddVariable(name, &bdtVar);
  }
}

// #############################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, data, step, dir, decay, weightMethod;
  bool hasOpt;
  int out = decodeArgs(argc, argv,
                       module, data, step, dir, decay, weightMethod, hasOpt);
  if (out!=0) return out;

  // Extra argument
  TString BDTtraining = "Def_Dep3";
  if (hasOpt) {
    BDTtraining = (argc>3 ? argv[3] : "Def_Dep3");
    std::cout << "Extra Arguments for " << module << std::endl;
    std::cout << "  Training: " << BDTtraining << std::endl;
    std::cout << "########################################" << std::endl;
  }
   
  // *** Main Function ***
  return runExpert(module, data, step, dir, decay, weightMethod, BDTtraining);
}

// #############################################################################
