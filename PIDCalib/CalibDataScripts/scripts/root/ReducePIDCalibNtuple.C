#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TCut.h"
#include <Riostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <cmath> 
#include "TSystem.h"
#include "TObjArray.h"

void ProcessLine(TString lineName, TString treeName, 
                 TFile *inFile, TFile *outFile, TString suffix="");

void MergeProtonSamples(TString fileNameLowP,
                        TString fileNameHiP,
                        TString fileNameOut) 
{
  std::cout << "Input filename (low P) = "<< fileNameLowP << std::endl;
  std::cout << "Input filename (high P) = "<< fileNameHiP << std::endl;
  std::cout << "Output filename = "<< fileNameOut << std::endl;

  const char* TreeName = "CalibPID";

  TChain ch(TreeName);
  Int_t nb = 0;

  // add low P TTree
  nb = ch.Add(fileNameLowP, -1);
  if (nb<=0) {
    std::cout << "ERROR: Invalid TTree " << TreeName << " in TFile "
              << fileNameLowP << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // add high P TTree
  nb = ch.Add(fileNameLowP, -1);
  if (nb<=0) {
    std::cout << "ERROR: Invalid TTree " << TreeName << " in TFile "
              << fileNameLowP << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Merged entries: " << ch.GetEntries() << std::endl;
  
  // merge TTrees into output file
  ch.Merge(fileNameOut);
}

void ReducePIDCalibNtuple(TString fileNameIn="~/lixo/PID_Modes.root", 
                          TString fileNameOut = "~/lixo/Output_PID_Modes.root",
                          TString lineName = "DSt2D0Pi_D02RSKPiTuple",
                          TString prefix="")
{
  std::cout << "Input filename = "<< fileNameIn << std::endl;
  std::cout << "Output filename = "<< fileNameOut << std::endl;
  std::cout << "Line name = " << lineName << std::endl;
  if (prefix.CompareTo("")!=0) {
    std::cout << "Prefix = " << prefix << std::endl;
  }
  //std::vector<TString> lineNameVector;
  //std::vector<TString>::iterator itLine;
  //lineNameVector.push_back("JpsiFromBNoPIDNoMipTuple");
  //lineNameVector.push_back("DSt2D0Pi_D02RSKPiTuple");
  //lineNameVector.push_back("Lam02PPi_LoPTuple");
  //lineNameVector.push_back("Lam02PPi_HiPTuple");
  
  TFile *inFile = TFile::Open(fileNameIn, "READ");
  if (!inFile||inFile->IsZombie()) {
    std::cout << "ERROR: Failed to open file " << fileNameIn << " for reading"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  
  //for ( itLine = lineNameVector.begin() ; itLine < lineNameVector.end(); itLine++ )
  //{
  //TString lineName = *itLine;
  const char* TreeName = "CalibPID";
  TString TreeFullName = TString::Format("%s/%s", lineName.Data(), TreeName);
  TTree* inTree = NULL;
  gDirectory->GetObject(TreeFullName, inTree);
  if (!inTree) {
    std::cout << "ERROR: No input TTree named " << TreeFullName << " found in TFile " 
              >> fileNameIn << std::endl;
    exit(EXIT_FAILURE);
  }

  ProcessLine(lineName, inTree, fileNameOut, prefix);

  //}
  //outFile->Close();
  //inFile->Close();
  delete inFile;
}

void ReducePIDCalibNtuple(std::vector<TString>& fileNamesIn,
                          TString fileNameOut = "~/lixo/Output_PID_Modes.root",
                          TString lineName = "DSt2D0Pi_D02RSKPiTuple",
                          TString prefix="")
{
  std::cout << "Input filenames: " << std::endl;
  
  for (Int_t iname = 0; iname<fileNamesIn.size(); ++iname) {
    std::cout << iname << ":    "<< fileNamesIn[iname] << std::endl;
  }
  std::cout << "Output filename = "<< fileNameOut << std::endl;
  std::cout << "Line name = " << lineName << std::endl;
  if (prefix.CompareTo("")!=0) {
    std::cout << "Prefix = " << prefix << std::endl;
  }

  const char* TreeName = "CalibPID";
  TString TreeFullName = TString::Format("%s/%s", lineName.Data(), TreeName);
  TChain* inChain = new TChain(TreeFullName);
  for (std::vector<TString>::iterator itName=fileNamesIn.begin();
       itName!=fileNamesIn.end(); ++itName) {
    inChain->Add(*itName);
  }
  ProcessLine(lineName, inChain, fileNameOut, prefix);

  //outFile->Close();
  delete inChain;
}

void ProcessLine(TString lineName, TTree *inTree, TString fileNameOut, TString pref="")
{
 
  TString treeName = inTree->GetName();
  std::cout << "Processing line "<< lineName << ", Tree = " << treeName << std::endl;

  //TTree* inTree = (TTree*) inFile->Get(lineName+"/"+treeName);
  //   TTree* inTree = (TTree*) inFile->Get(treeName);

  inTree->SetBranchStatus("*",0);
  
  //outFile->mkdir(lineName);
  //outFile->cd(lineName);

  std::cout << "Getting variables from " << lineName << " ...!" <<std::endl;
  std::vector<TString> varVector;
  std::vector<TString>::iterator it;

  TString prefix="";
  
  if (pref.CompareTo("")!=0) {
    prefix=pref;
    
    if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
      if ((prefix.CompareTo("Mu0")!=0)&&(prefix.CompareTo("Mu1")!=0)) {
        std::cout << "Expected 'Mu0' or 'Mu1' for prefix, got " << pref << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
      if ((prefix.CompareTo("K")!=0)&&(prefix.CompareTo("Pi")!=0)) {
        std::cout << "Expected 'K' or 'Pi' for prefix, got " << pref << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) {
      if ((prefix.CompareTo("P")!=0)) {
        std::cout << "Expected 'P' for prefix, got " << pref << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else {
      std::cout << "ERROR: Unknown line " << lineName << std::endl;
      exit(EXIT_FAILURE);
    }
    
    std::cout << "Specified prefix: " << prefix << std::endl;

    //kinematic variables
    varVector.push_back(prefix + "_P");
    varVector.push_back(prefix + "_PT");
    varVector.push_back(prefix + "_ETA");
    varVector.push_back(prefix + "_TRACK_P");
    varVector.push_back(prefix + "_TRACK_PT");
    varVector.push_back(prefix + "_TRACK_Eta");
  }
  else {
    Int_t numPrefixes = 1;
    if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0)  numPrefixes = 2;
    else if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) numPrefixes = 2;
    else if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) numPrefixes=1;
    else if ((lineName.CompareTo("K0S2PiPiTuple")==0)) numPrefixes=2;
    else {
      std::cout << "ERROR: Unknown line " << lineName << std::endl;
      exit(EXIT_FAILURE);
    }
    
    std::cout << lineName << " has " << numPrefixes << " Prefixes...!" <<std::endl;
    
    for (Int_t j = 0; j < numPrefixes; j++)
    { 
      prefix = "";
      if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
        prefix = "Mu0";
        if (j==1) prefix = "Mu1";
      }
      else if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
        prefix = "K";
        if (j==1) prefix = "Pi";
      }
      else if (lineName.CompareTo("K0S2PiPiTuple")==0) {
        prefix="Pi0";
        if (j==1) prefix = "Pi1";
      }
      else {
        prefix = "P";
      }
      
      //kinematic variables
      varVector.push_back(prefix + "_P");
      varVector.push_back(prefix + "_PT");
      varVector.push_back(prefix + "_ETA");
      varVector.push_back(prefix + "_TRACK_P");
      varVector.push_back(prefix + "_TRACK_PT");
      varVector.push_back(prefix + "_TRACK_Eta");
      
      // DLL/ANN variables
      
    }
  }
  
  varVector.push_back("Jpsi_M");
  varVector.push_back("Jpsi_MM");
  varVector.push_back("DSt_M");
  varVector.push_back("D0_M");
  varVector.push_back("Lam0_M");
  varVector.push_back("K0S_M");
  varVector.push_back("nTracks");
  varVector.push_back("runNumber");

  TObjArray* branches = inTree->GetListOfBranches();
  for ( it = varVector.begin() ; it < varVector.end();  ) {
    if (!branches->FindObject(*it)) {
      std::cout << "WARNING: Ignoring non-existant colName " << *it << std::endl;
      varVector.erase(it);
    }
    else {
      std::cout << "colName to be included: " << *it << std::endl;
      inTree->SetBranchStatus(*it, kTRUE);
      it++;
    }
  }
  
  TFile *outFile = TFile::Open(fileNameOut,"RECREATE");
  if (!outFile||outFile->IsZombie()) {
    std::cout << "ERROR: Failed to open file " << fileNameOut << " for writing"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  TTree* outTree = inTree->CloneTree();
  

 //  Int_t nB = inTree->GetNbranches();
//   std::cout << "nB="<< nB <<std::endl;

//   Int_t nNewB = varVector.size() + 2; // 2 more variables for secutity
//   Double_t *inD = new Double_t[nNewB];
//   Int_t idxD = 0;
//   for(Int_t i = 0; i<nB; i++)
//   {
//     TObject *to = inTree->GetListOfBranches()->At(i); 	
//     TBranch* tb = dynamic_cast<TBranch*>(to);
//     TString colName = tb->GetName();
//     TString title = tb->GetTitle();
//     TString type = ((TLeaf*)tb->GetListOfLeaves()->At(0))->GetTypeName();
//     //std::cout << "verifying  column " << colName;
//     Bool_t includeColumn = false;
//     for ( it = varVector.begin() ; it < varVector.end(); it++ )
//     {
//       TString colName2 = *it;
//       if (colName2.CompareTo(colName)==0){
//         includeColumn = true;
//         break;
//       }
//     }
//     if (!includeColumn) {
//       //std::cout << std::endl;
//       continue;
//     }
//     //std::cout << " ========> included ...!!" << std::endl;

//     if (type.CompareTo("Double_t")!=0) {
//       std::cout << " ========> ERROR: Variable "<< colName << " is not Double. It is Defined as " 
//                 << type << std::endl;
//       std::cout << " ========> ERROR: Variable "<< colName << " is not Double. It is Defined as " 
//                 << type << std::endl;
//       continue;
//     }
    
//     inTree->SetBranchAddress(colName, &inD[idxD]);
//     outTree->Branch(colName, &inD[idxD], title);
//     idxD++;
//   }

  Int_t nEntries = (Int_t) inTree->GetEntries();

//   for (Int_t i = 0; i < nEntries; i++)
//   {  
//     Int_t printEntry = 100000;
//     if ((i%printEntry) == 0) {
//       std::cout << "***************************************************************" << std::endl;
//       std::cout << " entry #: " << i << "/" << nEntries << std::endl;
//     }
//     inTree->GetEntry(i);
//     outTree->Fill();
//   } 
  
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "-------------"<< lineName <<"-------------" << std::endl;
  std::cout << "Initial entries: " << nEntries << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "Initial columns: " << varVector.size() << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;

  outFile->cd();
  
  outTree->Print();
  outTree->Write();  
  delete outFile;
  //  delete[] inD;
}


