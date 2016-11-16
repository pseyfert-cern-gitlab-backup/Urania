#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "TFile.h"
#include "TString.h"
#include "TChain.h"
#include "TSystem.h"
#include "TDirectory.h"
#include "TEventList.h"

typedef std::vector< std::pair< std::pair<UInt_t, UInt_t>,
                                Long64_t > > RunRangeEntriesVect;
typedef std::vector< std::pair<UInt_t, UInt_t> > RunRangeVect;
typedef std::map<UInt_t, Long64_t> RunMap;
const std::string sec(80, '*');

/** Divide the number of entries (nentries) by maxEntries
    If the remainder is less than 90% of maxEntries, reduce maxEntries
    by 1%. Continue until the remainder is within 90% of maxEntries, (
    the "90%" value can be changed by specifying minFraction)
    or there is no remainder.
    If maxEntries does not change after reducing by 1% (this can be changed by 
    specifying the stepFraction, which is possible if maxEntries
    is small, then return the current maxEntries.
    If verbose is true, print status messages.
    Returns the reduced maxEntries.
*/
Long64_t GetMaxEntries(const Long64_t& nentries, 
                       const Long64_t& maxEntries_init=2e6,
                       bool verbose=true,
                       Float_t stepFraction=0.01,
                       Float_t minFraction=0.9)
{
  Long64_t maxEntries=maxEntries_init;
  Long64_t step=(Long64_t)(stepFraction*maxEntries_init);
  
  
  if (step!=0 and not (nentries<((Long64_t)(minFraction*maxEntries)))) {
    bool remanderTooLarge = true;
    
    while ( remanderTooLarge )
    {
      // if there's no remainder, then keep maxEntries
      if (nentries%maxEntries==0) {
        break;
      }
      Long64_t newMaxEntries = maxEntries-step;
      if (newMaxEntries==maxEntries) {
        break;
      }
      maxEntries = newMaxEntries;
      remanderTooLarge = nentries%maxEntries<((Long64_t)(minFraction*maxEntries));
    }
  }
  if (verbose) {
    std::cout << "Number of entries = " << nentries << std::endl;
    std::cout << "Step fraction = " << stepFraction << std::endl;
    std::cout << "Minimum remainder fraction = " << minFraction << std::endl;
    std::cout << "Initial maxEntries = " << maxEntries_init << std::endl;
    std::cout << "Final maxEntries = " << maxEntries << std::endl;
  }
  return maxEntries;
}

/** Fill a map of runNumber to number of entries (runMap) from
    the TChain ch. If cuts are specified, then only that pass the cuts
    are considered.
    Will exit (with return code 1) if the chain contains no entries,
    either before or after cuts, or the TEventList of selected entries
    can't be retrieved from the current TDirectory. Returns true 
    otherwise.
    If verbose is true, print status messages.
    Returns the number of entries used to fill the run map.
*/
Long64_t FillRunMap(TChain& ch, RunMap& runMap,
                    const std::string& cuts="", bool verbose=true)
{
  Long64_t nentries = ch.GetEntries();
  if (verbose) std::cout << "nEntries = " << nentries << std::endl;
  if (nentries==0) 
  {
    std::cerr << "No entries in TChain " << ch.GetName() << std::endl;
    exit(1);
  }
  Long64_t nentries_sel = nentries;
  TEventList* elist = NULL;
  if (cuts!="") {
    ch.Draw(">>elist", cuts.c_str());
    gDirectory->GetObject("elist", elist);
    if (elist==NULL) {
      std::cerr << "Failed to retrieve TEventList 'elist'" << std::endl;
      exit(1);
    }
    nentries_sel=elist->GetN();
    if (nentries_sel==0) {
      std::cerr << "No entries selected after cuts '" << cuts
                << "'" << std::endl;
      exit(1);
    }
    if (verbose) {
      std::cout << "Selected entries: " 
                << nentries_sel << std::endl;
    }
  }
  
  // set run-number branch address
  
  ch.SetBranchStatus("*",0);
  ch.SetBranchStatus("runNumber",1);
  UInt_t runNumber = 0;
  ch.SetBranchAddress("runNumber", &runNumber);
  
  // loop over entries, and fill map of run number to number of entries
  RunMap::iterator it_runMap;
  for (Long64_t ientry=0; ientry<nentries; ++ientry)
  {
    ch.GetEntry(ientry);
    if ( (elist!=NULL) && (!(elist->Contains(ientry))) ) continue;
    it_runMap = runMap.find(runNumber);
    if (it_runMap==runMap.end())
    {
      it_runMap=runMap.insert(runMap.begin(), 
                              std::make_pair(runNumber, 0));
    }
    ++(it_runMap->second);
  }
  if (elist!=NULL) {
    elist->SetDirectory(0);
    delete elist;
    elist=NULL;
  }
  return nentries_sel;
}

// Each entry contains a pair, where the first
// is another pair corresponding to the minimum and maximum run
// whilst the second is the number of entries within this run range
RunRangeEntriesVect GetRunRanges(const RunMap& runMap,
                                 const Long64_t& maxEntries=2e6,
                                 bool verbose=true)
{
  
  RunRangeEntriesVect runRangeEntriesList;
  
  RunMap::const_iterator it_runMin=runMap.begin();
  while (it_runMin!=runMap.end()) 
  {
    UInt_t currentCount=0;
    if (it_runMin->second>maxEntries)
    {
      const UInt_t& runNum=it_runMin->first;
        std::cout << "WARNING: " << "Run " << runNum
                  << " has more than " << maxEntries
                  << " entries (" << it_runMin->second << ")" 
                  << "." << std::endl;
        runRangeEntriesList.push_back( std::make_pair( 
            std::make_pair(runNum, runNum), it_runMin->second) );
        it_runMin++;
    }
    else
    {
      RunMap::const_iterator it_runMax = it_runMin;
      while ( (currentCount<=maxEntries) && (it_runMax!=runMap.end()) ) 
      {                
        currentCount+=it_runMax->second;
        it_runMax++;
      }
      it_runMax--;
      if (currentCount>maxEntries) {
        currentCount-=it_runMax->second;
        it_runMax--;
      }
      runRangeEntriesList.push_back( std::make_pair( 
            std::make_pair(it_runMin->first, it_runMax->first),
            currentCount) );
      it_runMin=it_runMax;
      it_runMin++;
    }
  }
  
  if (verbose) 
  {
    std::cout << "Run-range list (maxEntries = " << maxEntries << ")"
              << std::endl;
    std::cout << "[" << std::endl;
    for ( RunRangeEntriesVect::const_iterator it=runRangeEntriesList.begin();
          it!=runRangeEntriesList.end(); ++it ) 
    {
      std::cout << "  (" << (it->first).first 
                << " : " << (it->first).second << "), "
                << "nEntries = " << it->second << std::endl;
    }
    std::cout << std::endl << "]" << std::endl;
  }
  
  return runRangeEntriesList;
}

// first is the run map, second is the maxEntries
RunRangeEntriesVect GetRunRanges(const std::string& tupleDirname_loP,
                                 const std::string& tupleDirname_hiP,
                                 const std::vector<std::string>& inputFilenames,
                                 const std::string& cuts="",
                                 const std::string& tupleName="CalibPID",
                                 const Long64_t& maxEntries_init=2e6,
                                 const std::string& partName="P",
                                 bool verbose=true,
                                 const Float_t& maxEntriesStepFrac=0.01,
                                 const Float_t& maxEntriesMinFrac=0.9)
{                  
    
  std::string cuts_loP = "("+partName+"_P<40000)";
  std::string cuts_hiP = "("+partName+"_P>40000)";
  if (!cuts.empty()) {
    cuts_loP+=" && " + cuts;
    cuts_hiP+=" && " + cuts;
  }
  std::string tupleFullName_loP = tupleDirname_loP+"/"+tupleName;
  std::string tupleFullName_hiP = tupleDirname_hiP+"/"+tupleName;

  TChain ch_loP(tupleFullName_loP.c_str());
  TChain ch_hiP(tupleFullName_hiP.c_str());

  for (std::vector<std::string>::const_iterator it=inputFilenames.begin();
       it!=inputFilenames.end(); ++it) 
  {
    ch_loP.Add(it->c_str());
    ch_hiP.Add(it->c_str());
  }
  
  // fill the run map
  RunMap runMap;
  Long64_t nentries_sel_loP = FillRunMap(ch_loP, runMap, cuts_loP, verbose);
  Long64_t nentries_sel_hiP = FillRunMap(ch_hiP, runMap, cuts_hiP, verbose);
  
  Long64_t maxEntries = GetMaxEntries(nentries_sel_loP+nentries_sel_hiP,
                                      maxEntries_init, verbose,
                                      maxEntriesStepFrac,
                                      maxEntriesMinFrac);
 
  // get the run range list
  return GetRunRanges(runMap, maxEntries, verbose);
}
   
// first is the run map, second is the maxEntries
RunRangeEntriesVect GetRunRanges(const std::string& tupleDirname, 
                                 const std::vector<std::string>& inputFilenames,
                                 const std::string& cuts="",
                                 const std::string& tupleName="CalibPID",
                                 const Long64_t& maxEntries_init=2e6,
                                 bool verbose=true,
                                 const Float_t& maxEntriesStepFrac=0.01,
                                 const Float_t& maxEntriesMinFrac=0.9)
{                  
    
  std::string tupleFullName = tupleDirname+"/"+tupleName;

  TChain ch(tupleFullName.c_str());
  
  for (std::vector<std::string>::const_iterator it=inputFilenames.begin();
       it!=inputFilenames.end(); ++it) 
  {
    ch.Add(it->c_str());
  }
  
  // fill the run map
  RunMap runMap;
  Long64_t nentries_sel = FillRunMap(ch, runMap, cuts, verbose);
  
  Long64_t maxEntries = GetMaxEntries(nentries_sel, maxEntries_init,
                                      verbose, maxEntriesStepFrac,
                                      maxEntriesMinFrac);
  
  // get the run range list
  return GetRunRanges(runMap, maxEntries, verbose);
}

///////////////////////////////////////////////////////////////
// For testing
///////////////////////////////////////////////////////////////
void FillToyData(TTree& tt,
                 const RunMap& passedMap_hiP,
                 const RunMap& failedMap_hiP,                 
                 const RunMap& passedMap_loP = RunMap(),
                 const RunMap& failedMap_loP = RunMap()
                 )
{
  UInt_t runNumber=0;
  Float_t mom=-1;
  Int_t tisTag=-1;

  // add the branches
  tt.Branch("runNumber", &runNumber);
  tt.Branch("P_P", &mom);
  tt.Branch("P_MuonTisTagged", &tisTag);

  /***** fill the high-momentum entries *****/
  mom=60000.0;
  
  // fill the passed entries
  tisTag=1;
  for (RunMap::const_iterator it=passedMap_hiP.begin(); 
       it!=passedMap_hiP.end(); ++it) 
  {
    runNumber = it->first;
    Long64_t nentries = it->second;
    for (Long64_t i=0; i<nentries; ++i) tt.Fill();
  }
  
  // fill the failed entries
  tisTag=0;
  for (RunMap::const_iterator it=failedMap_hiP.begin(); 
       it!=failedMap_hiP.end(); ++it) 
  {
    runNumber = it->first;
    Long64_t nentries = it->second;
    for (Long64_t i=0; i<nentries; ++i) tt.Fill();
  }

  /***** fill the low-momentum entries *****/
  mom=30000.0;
  
  if (!passedMap_loP.empty()) 
  {
    // fill the passed entries
    tisTag=1;
    for (RunMap::const_iterator it=passedMap_loP.begin(); 
         it!=passedMap_loP.end(); ++it) 
    {
      runNumber = it->first;
      Long64_t nentries = it->second;
      for (Long64_t i=0; i<nentries; ++i) tt.Fill();
    }
  }
  
  if (!failedMap_loP.empty())
  {
    // fill the failed entries
    tisTag=0;
    for (RunMap::const_iterator it=failedMap_loP.begin(); 
         it!=failedMap_loP.end(); ++it) 
    {
      runNumber = it->first;
      Long64_t nentries = it->second;
      for (Long64_t i=0; i<nentries; ++i) tt.Fill();
    }
  }
}

void MakeToyData_File1_HiP(Bool_t recreate=kTRUE) 
{
  const char* fname = "toydata_1.root";
  const char* ntpdir = "HiPTuple";
  const char* ntpname = "CalibPID";
  const char* mode = (recreate) ? "RECREATE" : "UPDATE";
  TFile* f = TFile::Open(fname, mode);
  if (f==NULL) 
  {
    std::cerr << "Failed to open file " << fname
              << " with access mode \"" << mode << "\""
              << std::endl;
    exit(1);
  }
  TDirectory* d = f->mkdir(ntpdir);
  d->cd();
  TTree* tt = new TTree(ntpname, "");
  
  RunMap passedMap, failedMap;
  
  passedMap[0]=20;
  passedMap[1]=25;
  passedMap[2]=40;

  failedMap[0]=2;
  failedMap[1]=2;
  failedMap[2]=4;

  FillToyData(*tt, passedMap, failedMap);
  
  d->cd();
  f->Write();
  delete f;
  f=NULL;
  tt=NULL;
}

void MakeToyData_File1_LoP(Bool_t recreate=kTRUE) 
{
  const char* fname = "toydata_1.root";
  const char* ntpdir = "LoPTuple";
  const char* ntpname = "CalibPID";
  const char* mode = (recreate) ? "RECREATE" : "UPDATE";
  TFile* f = TFile::Open(fname, mode);
  if (f==NULL) 
  {
    std::cerr << "Failed to open file " << fname
              << " with access mode \"" << mode << "\""
              << std::endl;
    exit(1);
  }
  TDirectory* d = f->mkdir(ntpdir);
  d->cd();
  TTree* tt = new TTree(ntpname, "");
  
  RunMap passedMap_loP, failedMap_loP;
  
  passedMap_loP[0]=23;
  passedMap_loP[1]=27;
  passedMap_loP[2]=38;

  failedMap_loP[0]=7;
  failedMap_loP[1]=8;
  failedMap_loP[2]=10;

  RunMap passedMap_hiP, failedMap_hiP;
  
  passedMap_hiP[0]=1;
  passedMap_hiP[1]=1;
  passedMap_hiP[2]=3;

  failedMap_hiP[0]=1;
  failedMap_hiP[1]=1;
  failedMap_hiP[2]=1;

  FillToyData(*tt, passedMap_hiP, failedMap_hiP,
              passedMap_loP, failedMap_loP
              );
  
  f->Write();
  delete f;
  f=NULL;
  tt=NULL;
}

void MakeToyData_File2_HiP(Bool_t recreate=kTRUE) 
{
  const char* fname = "toydata_2.root";
  const char* ntpdir = "HiPTuple";
  const char* ntpname = "CalibPID";
  const char* mode = (recreate) ? "RECREATE" : "UPDATE";
  TFile* f = TFile::Open(fname, mode);
  if (f==NULL) 
  {
    std::cerr << "Failed to open file " << fname
              << " with access mode \"" << mode << "\""
              << std::endl;
    exit(1);
  }
  TDirectory* d = f->mkdir(ntpdir);
  d->cd();
  TTree* tt = new TTree(ntpname, "");
  
  RunMap passedMap, failedMap;
  
  passedMap[0]=18;
  passedMap[1]=22;
  passedMap[2]=60;
  passedMap[3]=28;
  passedMap[4]=19;
  passedMap[5]=45;
  
  failedMap[0]=0;
  failedMap[1]=1;
  failedMap[2]=6;
  failedMap[3]=2;
  failedMap[4]=1;
  failedMap[5]=5;

  FillToyData(*tt, passedMap, failedMap);
  
  tt->Write();
  delete f;
  f=NULL;
  tt=NULL;
}

void MakeToyData_File2_LoP(Bool_t recreate=kTRUE) 
{
  const char* fname = "toydata_2.root";
  const char* ntpdir = "LoPTuple";
  const char* ntpname = "CalibPID";
  const char* mode = (recreate) ? "RECREATE" : "UPDATE";
  TFile* f = TFile::Open(fname, mode);
  if (f==NULL) 
  {
    std::cerr << "Failed to open file " << fname
              << " with access mode \"" << mode << "\""
              << std::endl;
    exit(1);
  }
  TDirectory* d = f->mkdir(ntpdir);
  d->cd();
  TTree* tt = new TTree(ntpname, "");
  
  RunMap passedMap_loP, failedMap_loP;
  
  passedMap_loP[0]=18;
  passedMap_loP[1]=20;
  passedMap_loP[2]=59;
  passedMap_loP[3]=29;
  passedMap_loP[4]=22;
  passedMap_loP[5]=47;
  passedMap_loP[6]=1;

  failedMap_loP[0]=5;
  failedMap_loP[1]=3;
  failedMap_loP[2]=13;
  failedMap_loP[3]=9;
  failedMap_loP[4]=6;
  failedMap_loP[5]=12;
  failedMap_loP[6]=3;

  RunMap passedMap_hiP, failedMap_hiP;
  
  passedMap_hiP[1]=1;
  passedMap_hiP[2]=5;
  passedMap_hiP[3]=2;
  passedMap_hiP[4]=2;
  passedMap_hiP[5]=4;

  failedMap_hiP[0]=1;
  failedMap_hiP[1]=1;
  failedMap_hiP[2]=1;
  failedMap_hiP[3]=1;
  failedMap_hiP[5]=1;

  FillToyData(*tt, passedMap_hiP, failedMap_hiP,
              passedMap_loP, failedMap_loP
              );
  
  f->Write();
  delete f;
  f=NULL;
  tt=NULL;
}


void MakeToyData()
{
  MakeToyData_File1_HiP();
  MakeToyData_File2_HiP();
  MakeToyData_File1_LoP(kFALSE);
  MakeToyData_File2_LoP(kFALSE);
}

std::string TestString(bool passed)
{
  std::string s_passed = (passed)?"PASSED":"FAILED";
  return s_passed;
}

/// Test GetMaxaxEntries
void TestGetMaxEntries(bool applyCuts=kFALSE)
{
  const std::string s_applyCuts = (applyCuts) ? " (with cuts)" : " (no cuts)";
  const std::string cuts = (applyCuts) ? "P_MuonTisTagged==1" : "";
  
  std::cout << sec << std::endl;
  std::cout << "Running TestGetMaxEntries" 
            << s_applyCuts << "." << std::endl;
  
  // get the HiP nTuple from the two files
  const std::string fname1="toydata_1.root";
  const std::string fname2="toydata_2.root";
  const std::string ntpname="HiPTuple/CalibPID";
  TChain ch(ntpname.c_str());
  if (ch.Add(fname1.c_str(), -1)==0) {
    std::cerr << "Failed to add file "
        << fname1 << " to chain " << ntpname
        << " (or no entries found)." << std::endl;
    exit(1);
  }
  if (ch.Add(fname2.c_str(), -1)==0) {
    std::cerr << "Failed to add file "
        << fname2 << " to chain " << ntpname
        << " (or no entries found)." << std::endl;
    exit(1);
  }
  
  Long64_t nentries_expected = (applyCuts) ? 277 : 300;
  Long64_t nentries_true = ch.GetEntries(cuts.c_str());
  if (nentries_true!=nentries_expected) {
    std::cerr << "Problem with TChain " << ntpname
              << ". Expected " << nentries_expected 
              << " entries, got " 
              << nentries_true << "." << std::endl;
    exit(1);
  }
  
  /// Run the test
  Long64_t maxEntries_init=110;
  Long64_t maxEntries_expected = (applyCuts) ? 95 : 103;
  
  Long64_t maxEntries = GetMaxEntries(nentries_true,
    maxEntries_init, false);
  
  bool passed = (maxEntries==maxEntries_expected);
  std::cout << "TestGetMaxEntries: " << TestString(passed)
            << std::endl;
  if (!passed) {
    std::cerr << "TestGetMaxEntries test failed. Expected "
              << maxEntries_expected << ", got " << maxEntries
              << "." << std::endl;
    exit(1);
  }
}


/// Test FillRunMap
void TestFillRunMap(bool applyCuts=false)
{
  const std::string s_applyCuts = (applyCuts) ? " (with cuts)" : " (no cuts)";
  const std::string cuts = (applyCuts) ? "P_MuonTisTagged==1" : "";
  
  std::cout << sec << std::endl;
  std::cout << "Running TestFillRunMap" << s_applyCuts 
            << "." << std::endl;
 
  // get the HiP nTuple from the two files
  const std::string fname1="toydata_1.root";
  const std::string fname2="toydata_2.root";
  const std::string ntpname="HiPTuple/CalibPID";
  TChain ch(ntpname.c_str());
  if (ch.Add(fname1.c_str(), -1)==0) {
    std::cerr << "Failed to add file "
        << fname1 << " to chain " << ntpname
        << " (or no entries found)." << std::endl;
    exit(1);
  }
  if (ch.Add(fname2.c_str(), -1)==0) {
    std::cerr << "Failed to add file "
        << fname2 << " to chain " << ntpname
        << " (or no entries found)." << std::endl;
    exit(1);
  }
  
  Long64_t nentries_expected = (applyCuts) ? 277 : 300;
  Long64_t nentries_true = ch.GetEntries(cuts.c_str());
  if (nentries_true!=nentries_expected) {
    std::cerr << "Problem with TChain " << ntpname
              << ". Expected " << nentries_expected 
              << " entries, got " 
              << nentries_true << "." << std::endl;
    exit(1);
  }
  
  // Run the test of nentries
  RunMap runMap;
  Long64_t nentries = FillRunMap(ch, runMap, cuts, false);
  bool passed = (nentries==nentries_expected);
  std::cout << "TestFillRunMap: Test nentries - " 
            << TestString(passed)
            << std::endl;
  if (!passed) {
    std::cerr << "TestFillRunMap test failed. Expected "
              << nentries_expected << " entries, "
              << "got " << nentries << "." << std::endl;
    exit(1);
  }
  
  RunMap expectedRunMap;
  
  expectedRunMap[0] = (applyCuts) ? 38 : 40;
  expectedRunMap[1] = (applyCuts) ? 47 : 50;
  expectedRunMap[2] = (applyCuts) ? 100 : 110;
  expectedRunMap[3] = (applyCuts) ? 28 : 30;
  expectedRunMap[4] = (applyCuts) ? 19 : 20;
  expectedRunMap[5] = (applyCuts) ? 45 : 50;
  
  // check that the run map has the expected number
  // of keys
  passed = (runMap.size()==expectedRunMap.size());
  std::cout << "TestFillRunMap: Test run map length - " 
            << TestString(passed) << std::endl;
  if (!passed) {
    std::cerr << "TestFillRunMap test failed. Expected "
              << expectedRunMap.size() << " runs in run map, "
              << "got " << runMap.size() << "." << std::endl;
    exit(1);
  }
  
  
  for (RunMap::const_iterator it_exp=expectedRunMap.begin();
    it_exp!=expectedRunMap.end(); ++it_exp) {
    const UInt_t& runNumber = it_exp->first;
    const Long64_t& expectedEntries = it_exp->second;
        
    RunMap::const_iterator it = runMap.find(runNumber);

    // test that the run number exists
    passed = (it!=runMap.end());
    std::cout << "TestFillRunMap: Test run "
              << runNumber << " exists - " 
              << TestString(passed) << std::endl;
    if (!passed) {
      std::cerr << "TestFillRunMap test failed. Run number "
                << runNumber << " not found in run map."
                << std::endl;
      exit(1);
    }
    
    // test that the number of entries is correct
    const Long64_t& entries = it->second;
    passed = (expectedEntries==entries);
    std::cout << "TestFillRunMap: Test run "
              << runNumber << " nentries - " 
              << TestString(passed) << std::endl;
    if (!passed) {
      std::cerr << "TestFillRunMap test failed. Expected "
                << expectedEntries << " entries for run number "
                << runNumber << ", got " << entries << "."
                << std::endl;
      exit(1);
    }              
  }
}

/// Run test of the regular method without/with cuts
void TestGetRunRanges(const bool& applyCuts=false)
{
  const std::string s_applyCuts = (applyCuts) ? " (with cuts)" : " (no cuts)";
  const std::string cuts = (applyCuts) ? "P_MuonTisTagged==1" : "";
  
  std::cout << sec << std::endl;
  std::cout << "Running TestGetRunRanges" << s_applyCuts 
            << "." << std::endl;
 
  const char* ntpdir = "HiPTuple";
  const char* ntpname = "CalibPID";
   
  std::vector<std::string> inputFilenames;
  inputFilenames.push_back("toydata_1.root");
  inputFilenames.push_back("toydata_2.root");

  Long64_t maxEntries_init = 110;
  
  RunRangeEntriesVect v = GetRunRanges(ntpdir, inputFilenames, cuts, ntpname,
                                       maxEntries_init, false);
  
  RunRangeEntriesVect v_exp;
  if (!applyCuts) {
    v_exp.push_back( std::make_pair( std::make_pair(0,1), 90 ) );
    v_exp.push_back( std::make_pair( std::make_pair(2,2), 110 ) );
    v_exp.push_back( std::make_pair( std::make_pair(3,5), 100 ) );
  } 
  else {
    v_exp.push_back( std::make_pair( std::make_pair(0,1), 85 ) );
    v_exp.push_back( std::make_pair( std::make_pair(2,2), 100 ) );
    v_exp.push_back( std::make_pair( std::make_pair(3,5), 92 ) );
  } 
  
  // check that the run-range vector has the expected number
  // of entries
  bool passed = (v.size()==v_exp.size());
  std::cout << "TestGetRunRanges: Test run-range entries vector - " 
            << TestString(passed) << "." << std::endl;
  if (!passed) {
    std::cerr << "TestGetRunRanges test failed. Expected "
              << v_exp.size() << " run ranges, "
              << "got " << v.size() << "." << std::endl;
    exit(1);
  }
  for (UInt_t i=0; i<v_exp.size(); ++i)
  {
    const std::pair<UInt_t,UInt_t>& expectedRunRange = (v_exp[i]).first;
    const Long64_t& expectedEntries = (v_exp[i]).second;
    
    const std::pair<UInt_t,UInt_t>& runRange = (v[i]).first;
    const Long64_t& entries = (v[i]).second;
    
    // test that the run range is correct
    passed = ( expectedRunRange.first == runRange.first );
    passed &= ( expectedRunRange.second == runRange.second );

    std::cout << "TestGetRunRanges: Test run range with index "
              << i << " is correct - " 
              << TestString(passed) << "." << std::endl;
    if (!passed) {
      std::cerr << "TestGetRunRanges test failed. Expected run range "
                << "(" << expectedRunRange.first 
                << ", " << expectedRunRange.second
                << ") for run range with index " << i 
                << ", got (" << runRange.first 
                << ", " << runRange.second << ")." 
                << std::endl;
      exit(1);
    }
    
    // test that the number of entries is correct
    passed = (expectedEntries==entries);
    std::cout << "TestGetRunRanges: Test run range with index "
              << i << " has correct number of entries - " 
              << TestString(passed) << "." << std::endl;
    if (!passed) {
      std::cerr << "TestGetRunRanges test failed. Expected "
                << expectedEntries 
                << " entries for run range with index "
                << i << ", got " << entries << "."
                << std::endl;
      exit(1);
    }
  }
}

/// Run test of the "Lambda0" method without/with cuts
void TestGetRunRanges_Lam0(const bool& applyCuts=false)
{
  bool verbose=false;

  const std::string s_applyCuts = (applyCuts) ? " (with cuts)" : " (no cuts)";
  const std::string cuts = (applyCuts) ? "P_MuonTisTagged==1" : "";
  
  std::cout << sec << std::endl;
  std::cout << "Running TestGetRunRanges_Lam0" << s_applyCuts 
            << "." << std::endl;
 
  const char* ntpdir_hiP = "HiPTuple";
  const char* ntpdir_loP = "LoPTuple";
  const char* ntpname = "CalibPID";
   
  std::vector<std::string> inputFilenames;
  inputFilenames.push_back("toydata_1.root");
  inputFilenames.push_back("toydata_2.root");

  Long64_t maxEntries_init = 200;
                                 
  RunRangeEntriesVect v = GetRunRanges(ntpdir_loP, ntpdir_hiP, inputFilenames, 
                                       cuts, ntpname, maxEntries_init, "P",
                                       verbose);
  
        
  RunRangeEntriesVect v_exp;
  if (!applyCuts) {
    v_exp.push_back( std::make_pair( std::make_pair(0,0), 93 ) );
    v_exp.push_back( std::make_pair( std::make_pair(1,1), 108 ) );
    v_exp.push_back( std::make_pair( std::make_pair(2,2), 230 ) );
    v_exp.push_back( std::make_pair( std::make_pair(3,4), 116 ) );
    v_exp.push_back( std::make_pair( std::make_pair(5,6), 113 ) );
  } 
  else {
    v_exp.push_back( std::make_pair( std::make_pair(0,1), 173 ) );
    v_exp.push_back( std::make_pair( std::make_pair(2,2), 197 ) );
    v_exp.push_back( std::make_pair( std::make_pair(3,6), 191 ) );
  } 
  
  // check that the run-range vector has the expected number
  // of entries
  bool passed = (v.size()==v_exp.size());
  std::cout << "TestGetRunRanges: Test run-range entries vector - " 
            << TestString(passed) << "." << std::endl;
  if (!passed) {
    std::cerr << "TestGetRunRanges test failed. Expected "
              << v_exp.size() << " run ranges, "
              << "got " << v.size() << "." << std::endl;
    exit(1);
  }
  for (UInt_t i=0; i<v_exp.size(); ++i)
  {
    const std::pair<UInt_t,UInt_t>& expectedRunRange = (v_exp[i]).first;
    const Long64_t& expectedEntries = (v_exp[i]).second;
    
    const std::pair<UInt_t,UInt_t>& runRange = (v[i]).first;
    const Long64_t& entries = (v[i]).second;
    
    // test that the run range is correct
    passed = ( expectedRunRange.first == runRange.first );
    passed &= ( expectedRunRange.second == runRange.second );

    std::cout << "TestGetRunRanges_Lam0: Test run range with index "
              << i << " is correct - " 
              << TestString(passed) << "." << std::endl;
    if (!passed) {
      std::cerr << "TestGetRunRanges_Lam0 test failed. Expected run range "
                << "(" << expectedRunRange.first 
                << ", " << expectedRunRange.second
                << ") for run range with index " << i 
                << ", got (" << runRange.first 
                << ", " << runRange.second << ")." 
                << std::endl;
      exit(1);
    }
    
    // test that the number of entries is correct
    passed = (expectedEntries==entries);
    std::cout << "TestGetRunRanges_Lam0: Test run range with index "
              << i << " has correct number of entries - " 
              << TestString(passed) << "." << std::endl;
    if (!passed) {
      std::cerr << "TestGetRunRanges_Lam0 test failed. Expected "
                << expectedEntries 
                << " entries for run range with index "
                << i << ", got " << entries << "."
                << std::endl;
      exit(1);
    }
  }  
}

// If run on the command-line, the script will run tests of the functionality
// of the scripts
void GetRunRanges()
{
  // create the toy nTuples
  MakeToyData(); 

  // test that the maxEntries method works as expected
  TestGetMaxEntries(); 
 
  // test that the maxEntries method works as expected (with cuts)
  TestGetMaxEntries(kTRUE); 
  
  // test that the FillRunMap methods works as expected
  TestFillRunMap();
  
  // test that the FillRunMap methods works as expected with cuts
  TestFillRunMap(kTRUE); 

  TestGetRunRanges(); // no cuts, regular method
  TestGetRunRanges(kTRUE); // test with cuts, regular method
  TestGetRunRanges_Lam0(); // no cuts, Lamda0 method
  TestGetRunRanges_Lam0(kTRUE); // test with cuts, Lambda0 method
}
