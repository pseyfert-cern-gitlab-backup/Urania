#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "TChain.h"

/** For the given list of input files produced by the ChopTrees script,
    checks that:
    1) The number of entries in the chopped trees are as expected.
    2) The run ranges in the chopped trees are as expected (in that
    there is no difference in the number of entries with/without
    imposing the run-range cuts).
    
    @param tupleName The name of the nTuple to check (incl. the directory
    name).
    @param inFileNames The list of input filenames.
    @param index The "ChopTree" file index (used for printing test messages).
    @param expectedEntries The number of entries expected in the input files.
    @param runMin The minimum run number of the nTuples in the input files.
    @param runMax The maximum run number of the nTuples in the input files.
    @param cuts An optional string of selection cuts, which will applied 
    prior to testing.
    
    Returns false (and stops further testing) if one of the tests failed.
    Returns true if all tests passed.
*/    
Bool_t ValidateChoppedTrees(const std::string& tupleName, 
                            const std::vector<std::string>& inFileNames,
                            const UInt_t& index,
                            const Long64_t& expectedEntries,
                            const UInt_t& runMin,
                            const UInt_t& runMax,
                            const std::string& cuts="")
{
    TChain ch(tupleName.c_str());
    
    for (std::vector<std::string>::const_iterator it=inFileNames.begin();
         it!=inFileNames.end(); ++it) {
            ch.Add(it->c_str());
    }
    
    std::string s_cuts = (cuts=="") ? "" : " (with cuts \""+cuts+"\") ";
    
    // Check that the number of entries is correct
    Long64_t nEntries = ch.GetEntries(cuts.c_str());
    std::cout << "Got " << nEntries << " entries to check "
	      << "(total entries = " << ch.GetEntries() 
              << ")" << std::endl;
    Bool_t passed = (nEntries==expectedEntries);
    std::string s_passed = (passed) ? "PASSED" : "FAILED";
    std::cout << "Test of number of entries for index " << index
              << s_cuts << ": " << s_passed << std::endl;
    if (!passed) {
        std::cerr << "Test of nEntries failed for nTuple " 
                  << tupleName << ", index " << index 
                  << ": Expected " << expectedEntries
                  << " entries, got " << nEntries << "." << std::endl;
        return passed;
    }
    
    // Check that the run ranges are correct
    std::stringstream ss_cuts_run;
    ss_cuts_run << "runNumber>=" << runMin << " && "
                << "runNumber<=" << runMax;
    if (cuts!="") ss_cuts_run << " && " << cuts;

    Long64_t nEntries_run = ch.GetEntries(ss_cuts_run.str().c_str());
    std::cout << "Got " << nEntries_run << " entries in run range "
	      << "(total entries = " << ch.GetEntries() 
              << ")" << std::endl;
    passed = (nEntries_run==nEntries);
    s_passed = (passed) ? "PASSED" : "FAILED";
    std::cout << "Test of run range for index " << index
              << ": " << s_passed << std::endl;
    if (!passed) {
        std::cerr << "Test of run range failed for nTuple " 
                  << tupleName << ", index " << index 
                  << ": Got " << nEntries_run 
                  << " entries after applying run-range cut, "
                  << "expected " << nEntries << std::endl;
        return passed;
    }
    return true;
}

/** For the given list of Lambda0 calibration files produced 
    by the ChopTrees script, checks that:
    1) The number of entries in the chopped trees are as expected.
    2) The run ranges in the chopped trees are as expected (in that
    there is no difference in the number of entries with/without
    imposing the run-range cuts).
    
    @param tupleName_loP The name of the loP nTuple to check 
    (incl. the directory name).
    @param tupleName_hiP The name of the loP nTuple to check 
    (incl. the directory name).
    @param inFileNames The list of input filenames.
    @param index The "ChopTree" file index (used for printing test messages).
    @param expectedEntries The number of entries expected in the input files.
    @param runMin The minimum run number of the nTuples in the input files.
    @param runMax The maximum run number of the nTuples in the input files.
    @param cuts An optional string of selection cuts, which will applied 
    prior to testing.
    
    Returns false (and stops further testing) if one of the tests failed.
    Returns true if all tests passed.
*/    
Bool_t ValidateChoppedTrees(const std::string& tupleName_loP,
                            const std::string& tupleName_hiP, 
                            const std::vector<std::string>& inFileNames,
                            const UInt_t& index,
                            const Long64_t& expectedEntries,
                            const UInt_t& runMin,
                            const UInt_t& runMax,
                            const std::string& cuts="",
                            const std::string& partName="P") 
{
    TChain ch_loP(tupleName_loP.c_str());
    TChain ch_hiP(tupleName_hiP.c_str());

    for (std::vector<std::string>::const_iterator it=inFileNames.begin();
         it!=inFileNames.end(); ++it) {
            ch_loP.Add(it->c_str());
            ch_hiP.Add(it->c_str());
    }
    
    std::string s_cuts = (cuts=="") ? "" : " (with cuts \""+cuts+"\") ";
    
    std::stringstream ss_cuts_loP;
    ss_cuts_loP << partName << "_P<40000.0";
    std::stringstream ss_cuts_hiP;
    ss_cuts_hiP << partName << "_P>40000.0";
    if (cuts!="") {
        ss_cuts_loP << " && " << cuts;
        ss_cuts_hiP << " && " << cuts;
    }   
    
    // Check that the number of entries is correct
    Long64_t nEntries_loP = ch_loP.GetEntries(ss_cuts_loP.str().c_str());
    Long64_t nEntries_hiP = ch_hiP.GetEntries(ss_cuts_hiP.str().c_str());
    Long64_t nEntries = nEntries_loP+nEntries_hiP;
    std::cout << "Got " << nEntries_loP << " LoP entries to check "
	    << "(total entries = " << ch_loP.GetEntries() 
	    << ")" << std::endl;
    std::cout << "Got " << nEntries_hiP << " HiP entries to check "
	    << "(total entries = " << ch_hiP.GetEntries() 
	    << ")" << std::endl; 
    Bool_t passed = (nEntries==expectedEntries);
    std::string s_passed = (passed) ? "PASSED" : "FAILED";
    std::cout << "Test of number of entries for index " << index
              << s_cuts << ": " << s_passed << std::endl;
    if (!passed) {
        std::cerr << "Test of nEntries failed for nTuples " 
                  << tupleName_loP << " and " << tupleName_hiP 
                  << ", index " << index << ": Expected " 
                  << expectedEntries << " entries, got " 
                  << nEntries << "." << std::endl;
        return passed;
    }
    
    // Check that the run ranges are correct
    std::stringstream ss_cuts_loP_run;
    ss_cuts_loP_run << "runNumber>=" << runMin 
                    << " && " << "runNumber<=" << runMax;
    ss_cuts_loP_run << " && " << ss_cuts_loP.str();
    std::stringstream ss_cuts_hiP_run;
    ss_cuts_hiP_run << "runNumber>=" << runMin
                    << " && " << "runNumber<=" << runMax;
    ss_cuts_hiP_run << " && " << ss_cuts_hiP.str();
    
    Long64_t nEntries_loP_run = ch_loP.GetEntries(
        ss_cuts_loP_run.str().c_str());
    Long64_t nEntries_hiP_run = ch_hiP.GetEntries(
        ss_cuts_hiP_run.str().c_str());
    Long64_t nEntries_run = nEntries_loP_run+nEntries_hiP_run;
    std::cout << "Got " << nEntries_loP_run << " LoP entries in run range "
	    << "(total entries = " << ch_loP.GetEntries() 
	    << ")" << std::endl;
    std::cout << "Got " << nEntries_hiP_run << " HiP entries in run range "
	    << "(total entries = " << ch_hiP.GetEntries() 
	    << ")" << std::endl;
 
    passed = (nEntries_run==nEntries);
    s_passed = (passed) ? "PASSED" : "FAILED";
    std::cout << "Test of run range for index " << index
              << ": " << s_passed << std::endl;
    if (!passed) {
        std::cerr << "Test of run range failed for nTuples " 
                  << tupleName_loP << " and " << tupleName_hiP 
                  << ", index " << index << ": Got " << nEntries_run 
                  << " entries after applying run-range cut, "
                  << "expected " << nEntries << std::endl;
        return passed;
    }
    return true;
}
