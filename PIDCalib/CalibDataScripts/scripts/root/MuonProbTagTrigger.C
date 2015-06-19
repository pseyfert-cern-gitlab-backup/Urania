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


void ProcessLine(TString lineName, TString treeName, TFile *inFile, TFile *outFile, Bool_t putMuonProbTag);

void MuonProbTagTrigger(TString fileNameIn, TString fileNameOut)
//void MuonProbTagTrigger()
{
//  TString fileNameIn; TString fileNameOut;
  std::cout << "fileNameIn = "<< fileNameIn << std::endl;
  std::cout << "fileNameOut = "<< fileNameOut << std::endl;
  std::vector<TString> lineNameVector;
  std::vector<TString>::iterator itLine;
  lineNameVector.push_back("GetIntegratedLuminosity");
  lineNameVector.push_back("JpsiFromBNoPIDNoMipTuple");
  lineNameVector.push_back("DSt2D0Pi_D02RSKPiTuple");
  lineNameVector.push_back("Lam02PPi_LoPTuple");
  lineNameVector.push_back("Lam02PPi_HiPTuple");
  
  TFile *inFile = TFile::Open(fileNameIn, "READ");
  //TFile *outFile = new TFile(fileNameOut,"RECREATE");
  TFile outFile(fileNameOut,"RECREATE");

  for ( itLine = lineNameVector.begin() ; itLine < lineNameVector.end(); itLine++ )
  {
    TString lineName = *itLine;
    TString TreeName = "CalibPID";
    if (lineName.CompareTo("GetIntegratedLuminosity")==0) TreeName = "LumiTuple";
    ProcessLine(lineName, TreeName, inFile, &outFile, lineName.Contains("Jpsi"));
  }
  outFile.Close();
}

void ProcessLine(TString lineName, TString treeName, TFile *inFile, TFile *outFile, Bool_t putMuonProbTag)
{
  std::cout << "Processing line "<< lineName << ", Tree = " << treeName << std::endl;

  TTree* inTree = (TTree*) inFile->Get(lineName+"/"+treeName);

  outFile->mkdir(lineName);
  outFile->cd(lineName);
  TTree outTree(treeName, inTree->GetTitle());

  if (lineName.CompareTo("GetIntegratedLuminosity")==0) {
    Double_t IntegratedLuminosity = 0;
    Double_t IntegratedLuminosityErr = 0;
    inTree->SetBranchAddress("IntegratedLuminosity", &IntegratedLuminosity);
    inTree->SetBranchAddress("IntegratedLuminosityErr", &IntegratedLuminosityErr);
    outTree.Branch("IntegratedLuminosity", &IntegratedLuminosity, "IntegratedLuminosity/D");
    outTree.Branch("IntegratedLuminosityErr", &IntegratedLuminosityErr, "IntegratedLuminosityErr/D");
    
    Int_t nEntries = (Int_t) inTree->GetEntries();
    for (Int_t i = 0; i < nEntries; i++)
    {  
      inTree->GetEntry(i);
      outTree.Fill();
    }
    outTree.Write();
    return;
  }

//  std::vector<TString> partVector = GetVectorPart(lineName);
  std::vector<TString> partVector;
  if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
    partVector.push_back("Mu0");
    partVector.push_back("Mu1");
    std::cout << "added Mu0 and Mu1 " << std::endl;
  }
  if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
    partVector.push_back("K");
    partVector.push_back("Pi");
    std::cout << "added K and Pi " << std::endl;
  }
  if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) {
    partVector.push_back("P");
    std::cout << "added P " << std::endl;
  }


  std::vector<TString>::iterator it;
  for ( it = partVector.begin() ; it < partVector.end(); it++ ) std::cout << " particle  to be considered " << *it << std::endl;

//  std::vector<TString> varVector = GetVectorVar(lineName);
  std::cout << "Getting variables from " << lineName << " ...!" <<std::endl;

  std::vector<TString> varVector;

  Int_t numPrefixs = 1;
  if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0)  numPrefixs = 2;
  if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) numPrefixs = 2;
  if (lineName.CompareTo("Lam02PPi_LoPTuple")==0) numPrefixs = 1;
  if (lineName.CompareTo("Lam02PPi_HiPTuple")==0) numPrefixs = 1;


  std::cout << lineName << " has " << numPrefixs << " Prefixs...!" <<std::endl;

//  varVector.clear();

  for (Int_t j = 0; j < numPrefixs; j++)
  { 
    TString prefix = "";
    
    if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
      varVector.push_back("Jpsi_M");
      varVector.push_back("Jpsi_MM");
      prefix = "Mu0";
      if (j==1) prefix = "Mu1";

      // prob and tag variables
      varVector.push_back(prefix + "_TRCHI2DOF");
      varVector.push_back(prefix + "_MIP_PV");
      varVector.push_back(prefix + "_MIPCHI2_PV");
      varVector.push_back(prefix + "_CaloEcalE");
      varVector.push_back(prefix + "_CaloHcalE");
    }

    if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
      varVector.push_back("DSt_M");
      varVector.push_back("D0_M");
      prefix = "K";
      if (j==1) prefix = "Pi";
      varVector.push_back(prefix + "_hasRich");
    }

    if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) {
      varVector.push_back("Lam0_M");
      prefix = "P";
      varVector.push_back(prefix + "_hasRich");
    }

    //trigger variables
    varVector.push_back(prefix + "_L0MuonDecision_TIS");
    varVector.push_back(prefix + "_L0DiMuonDecision_TIS");
    varVector.push_back(prefix + "_L0PhotonDecision_TIS");
    varVector.push_back(prefix + "_L0ElectronDecision_TIS");
    varVector.push_back(prefix + "_L0HadronDecision_TIS");
    varVector.push_back(prefix + "_Hlt1TrackAllL0Decision_TIS");
    varVector.push_back(prefix + "_Hlt1TrackMuonDecision_TIS");
    varVector.push_back(prefix + "_Hlt2GlobalDecision_TIS");
    varVector.push_back(prefix + "_Hlt2Global_TIS");
    varVector.push_back(prefix + "_Q");

    //event variables
    varVector.push_back("nTracks");
    varVector.push_back("runNumber");

    //standard dll variables
    varVector.push_back(prefix + "_PIDK");
    varVector.push_back(prefix + "_PIDp");
    varVector.push_back(prefix + "_PIDmu");
    varVector.push_back(prefix + "_PIDe");

    //neuro bayes variables
    varVector.push_back(prefix + "_ProbNNk");
    varVector.push_back(prefix + "_ProbNNpi");
    varVector.push_back(prefix + "_ProbNNp");
    varVector.push_back(prefix + "_ProbNNmu");
    varVector.push_back(prefix + "_ProbNNe");

    //kinematic variables
    varVector.push_back(prefix + "_P");
    varVector.push_back(prefix + "_PT");
    varVector.push_back(prefix + "_ETA");
    varVector.push_back(prefix + "_TRACK_P");
    varVector.push_back(prefix + "_TRACK_PT");
    varVector.push_back(prefix + "_TRACK_Eta");

    //muon variables
    varVector.push_back(prefix + "_InMuonAcc");
    varVector.push_back(prefix + "_isMuon");
    varVector.push_back(prefix + "_isMuonLoose");
    varVector.push_back(prefix + "_isMuonTight");
    varVector.push_back(prefix + "_NShared");
    varVector.push_back(prefix + "_MuonDist2");
  }


  for ( it = varVector.begin() ; it < varVector.end(); it++ ) std::cout << " colName  to be included " << *it << std::endl;

  Int_t nB = inTree->GetNbranches();
  std::cout << "nB="<< nB <<std::endl;
  Float_t *inF = new Float_t[nB]; 
  Float_t inF_3_3 [30][3][3];
  Float_t inF_100 [30][100];
  Int_t *inI = new Int_t[nB];
  Double_t *inD = new Double_t[nB];
  Bool_t *inO = new Bool_t[nB];
  Short_t *inS = new Short_t[nB];
  UInt_t *inii = new UInt_t[nB];
  ULong64_t *inll = new ULong64_t[nB];

  Int_t idxF = 0;
  Int_t idxF_3_3 = 0;
  Int_t idxF_100 = 0;
  Int_t idxI = 0;
  Int_t idxD = 0;
  Int_t idxO = 0;
  Int_t idxS = 0;
  Int_t idxii = 0;
  Int_t idxll = 0;

  std::map<TString,int> mapColName;
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

    if (type.CompareTo("F")==0)
    {
      if ((!(title.Contains("[3]")))&&(!(title.Contains("[nPV]")))) 
      {
        mapColName[colName] = idxF;
        inTree->SetBranchAddress(colName, &inF[idxF]);
        outTree.Branch(colName, &inF[idxF], title);
        idxF++;
      }
      if (title.Contains("[nPV]"))
      {
        inTree->SetBranchAddress(colName, &inF_100[idxF_100]);
        outTree.Branch(colName, &inF_100[idxF_100], title);
        idxF_100++;
      }
      if (title.Contains("[3]")) 
      {
        inTree->SetBranchAddress(colName, &inF_3_3[idxF_3_3]);
        outTree.Branch(colName, &inF_3_3[idxF_3_3], title);
        idxF_3_3++;
      }
    }
    if (type.CompareTo("I")==0)
    {
      mapColName[colName] = idxI;
      inTree->SetBranchAddress(colName, &inI[idxI]);
      outTree.Branch(colName, &inI[idxI], title);
      idxI++;
    }
    if (type.CompareTo("D")==0)
    {
      mapColName[colName] = idxD;
      inTree->SetBranchAddress(colName, &inD[idxD]);
      outTree.Branch(colName, &inD[idxD], title);
      idxD++;
    }
    if (type.CompareTo("O")==0){
      mapColName[colName] = idxO;
      inTree->SetBranchAddress(colName, &inO[idxO]);
      outTree.Branch(colName, &inO[idxO], title);
      idxO++;
    }
    if (type.CompareTo("S")==0){
      mapColName[colName] = idxS;
      inTree->SetBranchAddress(colName, &inS[idxS]);
      outTree.Branch(colName, &inS[idxS], title);
      idxS++;
    }
    if (type.CompareTo("i")==0){
      mapColName[colName] = idxii;
      inTree->SetBranchAddress(colName, &inii[idxii]);
      outTree.Branch(colName, &inii[idxii], title);
      idxii++;
    }
    if (type.CompareTo("l")==0){
      mapColName[colName] = idxll;
      inTree->SetBranchAddress(colName, &inll[idxll]);
      outTree.Branch(colName, &inll[idxll], title);
      idxll++;
    }
  }

  Bool_t mu0Prob, mu0Tag, mu1Prob, mu1Tag;

  if (putMuonProbTag) {
    outTree.Branch("Mu0_Prob", &mu0Prob, "Mu0_Prob/O");
    outTree.Branch("Mu0_Tag",  &mu0Tag,  "Mu0_Tag/O");
    outTree.Branch("Mu1_Prob", &mu1Prob, "Mu1_Prob/O");
    outTree.Branch("Mu1_Tag",  &mu1Tag,  "Mu1_Tag/O");
  }

  Int_t nEntries = (Int_t) inTree->GetEntries();
  TString triggCriterio = "TriggerCriterio: (L0Mu||L0DiMu||L0Pho||L0Ele||L0Had)&&(Hlt1TrkAllL0||Hlt1TrkMu)&&(Hlt2Glob)";
  TString probCriterio = "ProbCriterio: (InMuonAcc==1)&&(P>3000)&&(PT>800)&&(TrChi2Dof<3)";
  TString  tagCriterio = "TagCriterio : (prob)&&(isMuon)&&(P>6000)&&(PT>1500)&&(MipChi2PV>25)";
 
  Int_t nEntriesSaved = 0;
  for (Int_t i = 0; i < nEntries; i++)
  {  
    Int_t printEntry = 100000;
    if (div((i),printEntry).rem == 0) {
      std::cout << "***************************************************************" << std::endl;
      std::cout << " entry #: " << i << "/" << nEntries << std::endl;
    }
    inTree->GetEntry(i);

    Bool_t decisionTIS = false;

    for ( it = partVector.begin() ; it < partVector.end(); it++ ) {
      TString prefix = *it; 
      Bool_t  L0Muon    = inO[mapColName[prefix+"_L0MuonDecision_TIS"]];
      Bool_t  L0DiMuon  = inO[mapColName[prefix+"_L0DiMuonDecision_TIS"]];
      Bool_t  L0Photon  = inO[mapColName[prefix+"_L0PhotonDecision_TIS"]];
      Bool_t  L0Electron = inO[mapColName[prefix+"_L0ElectronDecision_TIS"]];
      Bool_t  L0Hadron  = inO[mapColName[prefix+"_L0HadronDecision_TIS"]];
      Bool_t  Hlt1TrackAllL0  = inO[mapColName[prefix+"_Hlt1TrackAllL0Decision_TIS"]];
      Bool_t  Hlt1TrackMuon   = inO[mapColName[prefix+"_Hlt1TrackMuonDecision_TIS"]];
      Bool_t  Hlt2GlobalDec  = inO[mapColName[prefix+"_Hlt2GlobalDecision_TIS"]];
      Bool_t  Hlt2Global  = inO[mapColName[prefix+"_Hlt2Global_TIS"]];

      Bool_t partDecTIS = (L0Muon||L0DiMuon||L0Photon||L0Electron||L0Hadron)&&(Hlt1TrackAllL0||Hlt1TrackMuon)&&(Hlt2Global);
      decisionTIS = (decisionTIS||partDecTIS);

      if (div((i),printEntry).rem == 0) {
          std::cout << "---------------------------------------------------------" << std::endl;
          std::cout <<  prefix+"_L0Muon = " << L0Muon << std::endl;  
          std::cout <<  prefix+"_L0DiMuon = " << L0DiMuon << std::endl; 
          std::cout <<  prefix+"_L0Photon = " << L0Photon << std::endl; 
          std::cout <<  prefix+"_L0Electron = " << L0Electron << std::endl; 
          std::cout <<  prefix+"_L0Hadron = " << L0Hadron << std::endl; 
          std::cout <<  prefix+"_Hlt1TrackAllL0 = " << Hlt1TrackAllL0 << std::endl; 
          std::cout <<  prefix+"_Hlt1TrackMuon = " << Hlt1TrackMuon << std::endl; 
          std::cout <<  prefix+"_Hlt2Global = " << Hlt2Global << std::endl; 
          std::cout <<  prefix+"_Hlt2GlobalDec = " << Hlt2GlobalDec << std::endl; 
          std::cout << "---------------------------------------------------------" << std::endl;
          std::cout <<  prefix+"_partDecTIS = " << partDecTIS << ": " << triggCriterio << std::endl; 
      }
     if (putMuonProbTag) {
        Double_t inMuonAcc = inD[mapColName[prefix+"_InMuonAcc"]];
        Int_t intInMuonAcc = ((int)inMuonAcc);
        Double_t TrChi2Dof = inD[mapColName[prefix+"_TRCHI2DOF"]];
        Bool_t  isMuon     = inO[mapColName[prefix+"_isMuon"]];
        Double_t P         = fabs(inD[mapColName[prefix+"_P"]]);
        Double_t PT        = inD[mapColName[prefix+"_PT"]];
        Double_t MipPV     = inD[mapColName[prefix+"_MIP_PV"]];
        Double_t MipChi2PV = inD[mapColName[prefix+"_MIPCHI2_PV"]];

        if (div((i),printEntry).rem == 0) {
          std::cout << "---------------------------------------------------------" << std::endl;
          std::cout <<  prefix+"_InMuonAcc = " << inMuonAcc << std::endl; 
          std::cout << "(int)" <<  prefix+"_InMuonAcc = " << intInMuonAcc << std::endl; 
          std::cout << prefix+"_TRCHI2DOF = " << TrChi2Dof << std::endl; 
          std::cout << prefix+"_isMuon = " << isMuon << std::endl; 
          std::cout << prefix+"_P = " << P << std::endl; 
          std::cout << prefix+"_PT = " << PT << std::endl; 
          std::cout << prefix+"_MIP_PV = " << MipPV << std::endl; 
          std::cout << prefix+"_MIPCHI2_PV = " << MipChi2PV << std::endl; 
        }

        Bool_t prob=false, tag=false;

        if ((intInMuonAcc==1) && (P > 3000.00) && (PT > 800.00) && ( TrChi2Dof < 3.0)) prob=true;
        if (prob && isMuon && (P > 6000.00) && (PT > 1500.00) && ( MipChi2PV > 25.0))  tag=true;

        if (div((i),printEntry).rem == 0) {
          std::cout << "---------------------------------------------------------" << std::endl;
          std::cout << prefix << "Prob = " << prob << ": " << probCriterio << std::endl;
          std::cout << prefix << "Tag = " << tag << ": " << tagCriterio << std::endl;
        }

        if (prefix.CompareTo("Mu0")==0) {mu0Prob = prob; mu0Tag = tag;}
        if (prefix.CompareTo("Mu1")==0) {mu1Prob = prob; mu1Tag = tag;}
      }
    } 

    if (div((i),printEntry).rem == 0) {
      std::cout << "---------------------------------------------------------" << std::endl;
      std::cout <<  "decisionTIS = " << decisionTIS << std::endl;
    }
    if (decisionTIS) {
      nEntriesSaved++;
      outTree.Fill();
    }
  } 
  
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "-------------"<< lineName <<"-------------" << std::endl;
  std::cout << "entries before: " << nEntries << std::endl;
  std::cout << "entries after: " << nEntriesSaved << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "columns before: " << nB << std::endl;
  std::cout << "columns after: " << varVector.size() << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << "---------------------------------------------------------" << std::endl;
  std::cout << " The End " << std::endl;

  outTree.Write();

  delete inF;
  delete inI;
  delete inD;
  delete inO;
  delete inS;
  delete inii;
  delete inll;
}


std::vector<TString> GetVectorVar(TString lineName)
{
  std::cout << "Getting variables from " << lineName << " ...!" <<std::endl;

  std::vector<TString> varVector;

  Int_t numPrefixs = 1;
  if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0)  numPrefixs = 2;
  if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) numPrefixs = 2;
  if (lineName.CompareTo("Lam02PPi_LoPTuple")==0) numPrefixs = 1;
  if (lineName.CompareTo("Lam02PPi_HiPTuple")==0) numPrefixs = 1;


  std::cout << lineName << " has " << numPrefixs << " Prefixs...!" <<std::endl;

//  varVector.clear();

  for (Int_t j = 0; j < numPrefixs; j++)
  { 
    TString prefix = "";
    
    if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
      varVector.push_back("Jpsi_M");
      varVector.push_back("Jpsi_MM");
      prefix = "Mu0";
      if (j==1) prefix = "Mu1";

      // prob and tag variables
      varVector.push_back(prefix + "_TRCHI2DOF");
      varVector.push_back(prefix + "_MIP_PV");
      varVector.push_back(prefix + "_MIPCHI2_PV");
      varVector.push_back(prefix + "_CaloEcalE");
      varVector.push_back(prefix + "_CaloHcalE");
    }

    if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
      varVector.push_back("DSt_M");
      varVector.push_back("D0_M");
      prefix = "K";
      if (j==1) prefix = "Pi";
      varVector.push_back(prefix + "_hasRich");
    }

    if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) {
      varVector.push_back("Lam0_M");
      prefix = "P";
      varVector.push_back(prefix + "_hasRich");
    }

    //trigger variables
    varVector.push_back(prefix + "_L0MuonDecision_TIS");
    varVector.push_back(prefix + "_L0DiMuonDecision_TIS");
    varVector.push_back(prefix + "_L0PhotonDecision_TIS");
    varVector.push_back(prefix + "_L0ElectronDecision_TIS");
    varVector.push_back(prefix + "_L0HadronDecision_TIS");
    varVector.push_back(prefix + "_Hlt1TrackAllL0Decision_TIS");
    varVector.push_back(prefix + "_Hlt1TrackMuonDecision_TIS");
    varVector.push_back(prefix + "_Hlt2GlobalDecision_TIS");
    varVector.push_back(prefix + "_Hlt2Global_TIS");
    varVector.push_back(prefix + "_Q");

    //event variables
    varVector.push_back("nTracks");
    varVector.push_back("runNumber");

    //standard dll variables
    varVector.push_back(prefix + "_PIDK");
    varVector.push_back(prefix + "_PIDp");
    varVector.push_back(prefix + "_PIDmu");
    varVector.push_back(prefix + "_PIDe");

    //neuro bayes variables
    varVector.push_back(prefix + "_ProbNNk");
    varVector.push_back(prefix + "_ProbNNpi");
    varVector.push_back(prefix + "_ProbNNp");
    varVector.push_back(prefix + "_ProbNNmu");
    varVector.push_back(prefix + "_ProbNNe");

    //kinematic variables
    varVector.push_back(prefix + "_P");
    varVector.push_back(prefix + "_PT");
    varVector.push_back(prefix + "_ETA");
    varVector.push_back(prefix + "_TRACK_P");
    varVector.push_back(prefix + "_TRACK_PT");
    varVector.push_back(prefix + "_TRACK_Eta");

    //muon variables
    varVector.push_back(prefix + "_InMuonAcc");
    varVector.push_back(prefix + "_isMuon");
    varVector.push_back(prefix + "_isMuonLoose");
    varVector.push_back(prefix + "_isMuonTight");
    varVector.push_back(prefix + "_NShared");
    varVector.push_back(prefix + "_MuonDist2");
  }

 return varVector;
}



std::vector<TString> GetVectorPart(TString lineName)
{
  std::cout << "Getting particles from " << lineName << " ...!" <<std::endl;
  std::vector<TString> partVector;
//  partVector.clear();
  if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
    partVector.push_back("Mu0");
    partVector.push_back("Mu1");
  }
  if (lineName.CompareTo("DSt2D0Pi_D02RSKPiTuple")==0) {
    partVector.push_back("K");
    partVector.push_back("Pi");
  }
  if ((lineName.CompareTo("Lam02PPi_LoPTuple")==0)||(lineName.CompareTo("Lam02PPi_HiPTuple")==0)) {
    partVector.push_back("P");
  }
  return partVector;
}



