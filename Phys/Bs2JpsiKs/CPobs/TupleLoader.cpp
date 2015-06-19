// #############################################################################
// Phys/Bs2JpsiKs Package
// Analyise Arguments, Name Files, Load NTuples
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes ***
#include "TupleLoader.h"

// #############################################################################
// *** Analyse Arguments ***
int decodeArgs(const int argc, char** const argv, TString& module,
               TString& data, TString& step, TString& dir, TString& decay,
               TString& weightMethod, bool& hasOpt) {

  // *** Initial Checks & Call for help ***
  if (argc<2) {
    help(argv[0]);
    return 1;
  }
  if ((TString(argv[1])=="--help") || (TString(argv[1])=="--h")) {
    help(argv[0]);
    return 0;
  }

  // *** Mandatory Arguments ***
  module       = TString(argv[0]);
  data         = TString(argv[1]);
  step         = (argc>2 ? TString(argv[2]) : m_NNInitialise);

  // *** Optional Arguments ***
  bool foundOpt = false;
  hasOpt = false;
  if (argc>3) {
    for (int i = 3; i<argc; i++) {
      if (TString(argv[i])=="OptArg") { // General settings
        foundOpt = true;
        dir = TString(argv[i+1]);
        decay = (argc>i+2 ? TString(argv[i+2]) : m_B2JpsiKs);
        weightMethod = (argc>i+3 ? TString(argv[i+3]) : m_random);
        break;
      } else { // Module specific settings
        hasOpt = true;
      }
    }
  }
  // Default settings
  if (!foundOpt) {
    dir          = (module==m_slimtuple ? m_castor : m_local);
    decay        = m_B2JpsiKs;
    weightMethod = m_random;
  }


  // *** Error Analysis ***
  int error = 0;

  // Valid Input?
  if (!(isSigMC(data) || isLHCb(data) || data==m_IncJpsi)) {
    std::cout << "ERROR: Unknown data type " << data << std::endl;
    error = -1;
  }
  if (!(step==m_NNInitialise || step==m_NNKstar || step==m_NNUnbiased ||
        step==m_NNSecond || step==m_NNAnalyse)) {
    std::cout << "ERROR: Unknown selection step " << step << std::endl;
    error = -2;
  }
  if (!(dir==m_castor || dir==m_local)) {
    std::cout << "WARNING: Unknown data directory = " << dir << std::endl;
  }
  if (!(decay==m_B2JpsiKs)) {
    std::cout << "ERROR: Decay channel " << decay
              << " is not supported" << std::endl;
    error = -3;
  }
  if (!(weightMethod==m_downscaled || weightMethod==m_random ||
        weightMethod==m_weighted || weightMethod==m_noweight)) {
    std::cout << "ERROR: Unknown weighting method "
              << weightMethod << std::endl;
    error = -5;
  }

  // *** Set Directory ***
  if (dir==m_castor) { // data should be read from castor
    dir = "root://castorlhcb.cern.ch//castor/cern.ch/grid/lhcb/user/f/fkruse/Tuples201403/";
  } else if (dir==m_local) { // data can be read locally
    dir = "";
  }

  // *** Result of Decoding ***
  std::cout << "########################################" << std::endl;
  if (error==0) {
    std::cout << "Successfully decoded arguments " << std::endl;
  } else {
    std::cout << "FAILED to decode arguments " << std::endl;
  }
  std::cout << "            module: " << module       << std::endl;
  std::cout << "       data sample: " << data         << std::endl;
  std::cout << "    selection step: " << step         << std::endl;
  std::cout << "         directory: " << dir          << std::endl;
  std::cout << "        decay mode: " << decay        << std::endl;
  std::cout << "  weighting method: " << weightMethod << std::endl;
  std::cout << "     found opt arg: " << (hasOpt ? "Yes" : "No") << std::endl;
  std::cout << "########################################" << std::endl;

  // *** Error Handling ***
  if (error<0) help(argv[0]);
  
  return error;
}

// #############################################################################
// *** Help/Manual ***
void help(const TString module) {
    std::cout << std::endl;
    std::cout << "HELP:\n Function should be called as: ";
    if (module==m_slimtuple)
      std::cout << module << " data" << std::endl;
    else
      std::cout << module << " data step [optional arguments]" << std::endl;
    std::cout << "The General optional arguments should be called as: ";
    std::cout << "OptArg dir [decay] [weight]" << std::endl;
    std::cout << "Module specific arguments simply follow ``step''" << std::endl;

    std::cout << "The arguments are:" << std::endl;
    std::cout << "``data'' specifies which data type to run." <<
      "Supported: " << m_LHCb2011 << ", " << m_LHCb2011Prescaled << ", " <<
      m_LHCb2012 << ", " << m_LHCb2012Prescaled << ", " <<
      m_SigBd << ", " << m_SigBdPrescaled << ", " <<
      m_SigBs << ", " << m_SigBsPrescaled << ", " <<
      m_SigKstar << ", " << m_SigKstarWM << ", " << m_IncJpsi << std::endl;
    std::cout << "``step'' specifies which stage of the selection is run." <<
      "Supported: " << m_NNInitialise << ", " << m_NNKstar << ", " <<
      m_NNUnbiased << ", " << m_NNSecond << ", " << m_NNAnalyse << std::endl;
    std::cout << "``dir'' specifies the directory for the data." <<
      " Supported: " << m_castor << ", " << m_local << " (default)" <<
      ", or any directory" << std::endl;
    std::cout << "``decay'' specifies which decay channel to run." <<
      " Supported: " << m_B2JpsiKs << " (default)" << std::endl;
    std::cout << "``weight'' specifies the weighting method." <<
      " Supported: " << m_downscaled << ", " << m_random << " (default), " <<
      m_weighted << ", " << m_noweight << std::endl;
    std::cout << std::endl;
}

// #############################################################################
// *** File Naming: Root files ***
TString makeFileName(const TString module, const TString data,
                     const TString step, const TString dir,
                     const TString decay, const TString weightMethod) {
  
  // Name Components
  TString modName = "";
  if (module==m_slimtuple) {
    modName = "Slim";
  } else if (module==m_weighting) {
    modName = "Weights";
  } else if (module==m_expert || module==m_TMVA_expert) {
    modName = "NetOut";
  } else if (module==m_optimisation) {
    modName = "Opt";
  } else {
    std::cout << "ERROR: Module " << module
              << " is not associated with a ROOT file." << std::endl;
    return "";
  }

  // Return String
  TString theFile = "";
  if (dir.Contains(".root")) {
    // Get the sample tag
    unsigned int c = dir.Last('/');
    theFile = (dir(c+1,dir.Length()-c));
    // theFile = decay-tag-modName.root
    theFile = decay+"-"
              +theFile.ReplaceAll(".root", TString("-"+modName+".root"));
  } else if (module==m_slimtuple) {
    theFile = decay+"-"+data+"-"+modName+".root";
  } else if (weightMethod==m_random) {
    theFile = decay+"-"+data+"-"+modName+"-"+step+".root";
  } else {
    theFile = decay+"-"+data+"-"+modName+"-"+step+"-"+weightMethod+".root";
  }

  std::cout << "Made Root file(name): " << theFile << std::endl;
  return theFile;
}

// #############################################################################
// *** File Naming: MVA training expertise ***
TString mvaFileName(const TString decay, const TString step,
                    const unsigned int tracktype, const TString ext) {
  TString filename = decay+"-"+step;
  char fileTail[25];
  sprintf(fileTail,"-%i.", tracktype);
  filename.Append(fileTail);
  filename.Append(ext);
  std::cout << "MVA training file(name): " << filename << std::endl;
  return filename;
}

// #############################################################################
// *** Load Data ***
IB2JpsiX* loadTuple(const TString module, const TString data,
                    const TString step, const TString dir,
                    const TString decay, const TString weightMethod) {
  // *** Select Supported Decay Mode ***
  IB2JpsiX* ntuple = 0;
  if (decay==m_B2JpsiKs) {
    ntuple = loadB2JpsiKsTuple(module, data, step, dir, decay, weightMethod);
  } else {
    std::cout << "ERROR: Decay Mode is currently not supported." << std::endl;
  }

  return ntuple;
}

// #############################################################################
B2JpsiKs* loadB2JpsiKsTuple(const TString module, const TString data,
                            const TString step, const TString dir,
                            const TString decay, const TString weightMethod) {
  // *** Guard Clause ***
  if (decay!=m_B2JpsiKs) {
    std::cout << "ERROR: Calling the wrong instance of IB2JpsiX for decay "
              << decay << std::endl;
    return 0;
  }

  // *** Construct Chain ***
  // 1. Tree
  TString line  = (module==m_slimtuple ? "Bd2JpsiKS" : "Slim_"+decay+"_Tuple");

  // 2. File
  TString file1 = ""; TString file2 = ""; TString file3 = ""; TString file4 = "";
  
  if (dir.Contains(".root")) { // case where file name is give 
    file1 = dir;
  } else if (module!=m_slimtuple) {
    file1 = "B2JpsiKs-"+data+"-Slim.root";
  } else { // Select DaVinci tuple for slimming
    if (data==m_LHCb2011) {
      file1 = dir+"B2JpsiKSDetached_data_Stripping20r1_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      //file1 = dir+"B2JpsiKSDetached_data_Stripping20r1_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
    } else if (data==m_LHCb2011Prescaled) {
      file1 = dir+"B2JpsiKSPrescaled_data_Stripping20r1_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      //file1 = dir+"B2JpsiKSPrescaled_data_Stripping20r1_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
    } else if (data==m_LHCb2012) {
      file1 = dir+"B2JpsiKSDetached_data_Stripping20r1_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      //file1 = dir+"B2JpsiKSDetached_data_Stripping20r0_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
    } else if (data==m_LHCb2012Prescaled) {
      file1 = dir+"B2JpsiKSPrescaled_data_Stripping20r0_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      //file1 = dir+"B2JpsiKSPrescaled_data_Stripping20r0_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
    } else if (data==m_LHCbAll) {
      file1 = dir+"B2JpsiKSDetached_data_Stripping20r1_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      file2 = dir+"B2JpsiKSDetached_data_Stripping20r0_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      //file1 = dir+"B2JpsiKSDetached_data_Stripping20r1_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
      //file2 = dir+"B2JpsiKSDetached_data_Stripping20r0_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
    } else if (data==m_LHCbAllPrescaled) {
      file1 = dir+"B2JpsiKSPrescaled_data_Stripping20r1_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      file2 = dir+"B2JpsiKSPrescaled_data_Stripping20r0_DVv33r6p1_FTr162594_v2_20131007_fkruse_combined_tupleA.root";
      //file1 = dir+"B2JpsiKSPrescaled_data_Stripping20r1_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
      //file2 = dir+"B2JpsiKSPrescaled_data_Stripping20r0_DVv33r9_FTr167275_v3_20140306_fkruse_combined_tupleA.root";
    } else if (data==m_SigBd) {
      file1 = dir+
      "B2JpsiKSDetached_Sim08_2012_Pythia6_Bd2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file2 = dir+
      "B2JpsiKSDetached_Sim08_2012_Pythia8_Bd2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
    } else if (data==m_SigBdPrescaled) {
      file1 = dir+
      "B2JpsiKSPrescaled_Sim08_2012_Pythia6_Bd2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file2 = dir+
      "B2JpsiKSPrescaled_Sim08_2012_Pythia8_Bd2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
    } else if (data==m_SigBs) {
      file1 = dir+
      "B2JpsiKSDetached_Sim08_2012_Pythia6_Bs2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file2 = dir+
      "B2JpsiKSDetached_Sim08_2012_Pythia8_Bs2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
    } else if (data==m_SigBsPrescaled) {
      file1 = dir+
      "B2JpsiKSPrescaled_Sim08_2012_Pythia6_Bs2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file2 = dir+
      "B2JpsiKSPrescaled_Sim08_2012_Pythia8_Bs2JpsiKS_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
    } else if (data==m_SigKstar || data==m_SigKstarWM) {
      file1 = dir+
      "B2JpsiKSDetached_Sim08a_2012_Pythia6_Bd2JpsiKst_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file2 = dir+
      "B2JpsiKSDetached_Sim08a_2012_Pythia8_Bd2JpsiKst_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file3 = dir+
      "B2JpsiKSDetached_Sim08c_2012_Pythia6_Bd2JpsiKst_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file4 = dir+
      "B2JpsiKSDetached_Sim08c_2012_Pythia8_Bd2JpsiKst_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
    } else if (data==m_IncJpsi) {
      file1 = dir +
      "B2JpsiKSPrescaled_Sim08_2012_Pythia6_inclJpsi_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
      file2 = dir +
      "B2JpsiKSPrescaled_Sim08_2012_Pythia8_inclJpsi_Stripping20_DVv33r9_FTr167275MCTune_v8_20140303_fkruse_combined_tupleA.root";
    }
  }

  // 3. Error Handling
  if (file1=="") {
    std::cout << "ERROR: Did not find file-specification for data set " << data
              << " and decay channel " << decay << std::endl;
    return 0;
  } else {
    std::cout << "Found file: " << file1 << " for line " << line << std::endl;
    if (file2!="") {
      std::cout << "Found file: " << file2 << " for line " << line << std::endl;
    }
    if (file3!="") {
      std::cout << "Found file: " << file3 << " for line " << line << std::endl;
    }
    if (file4!="") {
      std::cout << "Found file: " << file4 << " for line " << line << std::endl;
    }
  }
  
  // *** Load Chain ***
  TChain* chain = (TChain *)
    loadChain(file1, file2, file3, file4, line, module, data, step, dir, decay, weightMethod);
  if (chain==0 || chain->GetEntries()==0) return 0;
  
  // *** Construct NTuple ***
  B2JpsiKs* ntuple = new B2JpsiKs(chain, module, data, step, dir);

  return ntuple;
}

// #############################################################################
// *** Make Chain ***
TChain* loadChain(const TString file1, const TString file2, const TString file3,
                  const TString file4, const TString line, const TString module,
                  const TString data, const TString step, const TString dir,
                  const TString decay, const TString weightMethod) {
  
  // *** Define chain ***
  TChain* chain = new TChain(line, "");
  chain->Add(file1);
  if (file2!="") chain->Add(file2);
  if (file3!="") chain->Add(file3);
  if (file4!="") chain->Add(file4);
  std::cout << "Total number of entries: " << chain->GetEntries() << std::endl;
  
  // Error Handling
  if (chain->GetEntries()==0) {
    std::cout << "ERROR: File is not loaded properly" << std::endl;
    return 0; // Catch the error later
  }

  // *** Add Friends ***
  // weighting wants the previous expert file to cut on its net output
  // teacher & expert want associated weighting file to get the sWeights
  // analysis tools want the last expert file to cut on its net output
  TString friendFileName = "";
  TString friendTreeName = "";
  if (module==m_weighting && step!=m_NNKstar) {
    TString previousStep = (step==m_NNUnbiased ? m_NNKstar :
                           (step==m_NNSecond ? m_NNUnbiased : m_NNSecond));
    friendFileName = makeFileName(m_expert, data, previousStep, dir,
                                  decay, weightMethod);
    friendTreeName = "NetTree";
  } else if (module==m_teacher || module==m_expert || module==m_TMVA_teacher || module==m_TMVA_expert) {
    friendFileName = makeFileName(m_weighting, data, step, dir, decay,
                                  weightMethod);
    friendTreeName = "WeightTree";
  } else if (module==m_optimisation) {
    friendFileName = makeFileName(m_expert, data, m_NNSecond, dir,
                                  decay, weightMethod);
    friendTreeName = "NetTree";
  }

  if (friendFileName!="") {
    TFile* friendFile = TFile::Open(friendFileName);
    if (!friendFile) return 0;
    TTree* friendTree = (TTree*)friendFile->Get(friendTreeName);
    if (!friendTree) return 0;
    chain->AddFriend(friendTree);
    std::cout << "Opened " << friendFileName << std::endl;
  } else {
    std::cout << "No need to add friends" << std::endl;
  }
  
  // *** Return ***
  return chain;
} 

// #############################################################################
Long64_t printFrac(const Long64_t nentries) {
  return TMath::Max((Long64_t) nentries/50, (Long64_t) 25000);
};

// #############################################################################
