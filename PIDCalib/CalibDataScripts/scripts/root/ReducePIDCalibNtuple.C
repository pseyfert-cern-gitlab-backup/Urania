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


void ProcessLine(TString lineName, TString treeName, TFile *inFile, TFile *outFile);

void ReducePIDCalibNtuple(TString fileNameIn="~/lixo/PID_Modes.root", TString fileNameOut = "~/lixo/Output_PID_Modes.root", TString lineName = 
"DSt2D0Pi_D02RSKPiTuple")
{
  std::cout << "fileNameIn = "<< fileNameIn << std::endl;
  std::cout << "fileNameOut = "<< fileNameOut << std::endl;
  //std::vector<TString> lineNameVector;
  //std::vector<TString>::iterator itLine;
  //lineNameVector.push_back("JpsiFromBNoPIDNoMipTuple");
  //lineNameVector.push_back("DSt2D0Pi_D02RSKPiTuple");
  //lineNameVector.push_back("Lam02PPi_LoPTuple");
  //lineNameVector.push_back("Lam02PPi_HiPTuple");
  
  TFile *inFile = TFile::Open(fileNameIn, "READ");
  TFile outFile(fileNameOut,"RECREATE");

  //for ( itLine = lineNameVector.begin() ; itLine < lineNameVector.end(); itLine++ )
  //{
    //TString lineName = *itLine;
    TString TreeName = "CalibPID";
    ProcessLine(lineName, TreeName, inFile, &outFile);
  //}
  outFile.Close();
}

void ProcessLine(TString lineName, TString treeName, TFile *inFile, TFile *outFile)
{
  std::cout << "Processing line "<< lineName << ", Tree = " << treeName << std::endl;

  //TTree* inTree = (TTree*) inFile->Get(lineName+"/"+treeName);
  TTree* inTree = (TTree*) inFile->Get(treeName);

  //outFile->mkdir(lineName);
  //outFile->cd(lineName);
  TTree outTree(treeName, inTree->GetTitle());

  std::cout << "Getting variables from " << lineName << " ...!" <<std::endl;
  std::vector<TString> varVector;
  std::vector<TString>::iterator it;

  Int_t numPrefixs = 1;
  if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0)  numPrefixs = 2;
  if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) numPrefixs = 2;

  std::cout << lineName << " has " << numPrefixs << " Prefixs...!" <<std::endl;

  for (Int_t j = 0; j < numPrefixs; j++)
  { 
    TString prefix = "";
    if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
      prefix = "Mu0";
      if (j==1) prefix = "Mu1";
    }
    if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
      prefix = "K";
      if (j==1) prefix = "Pi";
    }
    if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) {
      prefix = "P";
    }

    //kinematic variables
    varVector.push_back(prefix + "_P");
    varVector.push_back(prefix + "_PT");
    varVector.push_back(prefix + "_ETA");
    varVector.push_back(prefix + "_TRACK_P");
    varVector.push_back(prefix + "_TRACK_PT");
    varVector.push_back(prefix + "_TRACK_Eta");
  }
  varVector.push_back("Jpsi_M");
  varVector.push_back("Jpsi_MM");
  varVector.push_back("DSt_M");
  varVector.push_back("D0_M");
  varVector.push_back("Lam0_M");
  varVector.push_back("nTracks");
  varVector.push_back("runNumber");

  for ( it = varVector.begin() ; it < varVector.end(); it++ ) std::cout << " colName  to be included " << *it << std::endl;

  Int_t nB = inTree->GetNbranches();
  std::cout << "nB="<< nB <<std::endl;

  Int_t nNewB = varVector.size() + 2; // 2 more variables for secutity
  Double_t *inD = new Double_t[nNewB];
  Int_t idxD = 0;
  for(Int_t i = 0; i<nB; i++)
  {
    TObject *to = inTree->GetListOfBranches()->At(i); 	
    TBranch* tb = dynamic_cast<TBranch*>(to);
    TString colName = tb->GetName();
    TString title = tb->GetTitle();
    TString type = title;
    type = type.Data()[type.Length()-1];
    //std::cout << "verifying  column " << colName;
    Bool_t includeColumn = false;
    for ( it = varVector.begin() ; it < varVector.end(); it++ )
    {
      TString colName2 = *it;
      if (colName2.CompareTo(colName)==0){
        includeColumn = true;
        break;
      }
    }
    if (!includeColumn) {
      //std::cout << std::endl;
      continue;
    }
    //std::cout << " ========> included ...!!" << std::endl;

    if (type.CompareTo("D")!=0) {
      std::cout << " ========> ERROR: Variable "<< colName << " is not Doble. It is Defined as " << type << std::endl;
      std::cout << " ========> ERROR: Variable "<< colName << " is not Doble. It is Defined as " << type << std::endl;
      continue;
    }

    inTree->SetBranchAddress(colName, &inD[idxD]);
    outTree.Branch(colName, &inD[idxD], title);
    idxD++;
  }

  Int_t nEntries = (Int_t) inTree->GetEntries();

  for (Int_t i = 0; i < nEntries; i++)
  {  
    Int_t printEntry = 100000;
    if (div((i),printEntry).rem == 0) {
      std::cout << "***************************************************************" << std::endl;
      std::cout << " entry #: " << i << "/" << nEntries << std::endl;
    }
    inTree->GetEntry(i);
    outTree.Fill();
  } 
  
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "-------------"<< lineName <<"-------------" << std::endl;
  std::cout << "entries: " << nEntries << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "columns: " << varVector.size() << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << " The End " << std::endl;

  outTree.Write();

  delete inD;
}


