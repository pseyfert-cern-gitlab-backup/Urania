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
#include <set>
#include <cstdlib>
#include <cmath> 
#include "TSystem.h"


// local
void ProcessLine(TString fileName, 
		Int_t minJob, 
		Int_t maxJob, 
		TString lineName, 
		TString treeName, 
		TFile *outFile, 
		std::pair <double, double> runLimits, 
                set<double> excludeRunSet,
		Bool_t putMuonProbTag=false);


//void ChopUpMuonTree(TString inFileName, Int_t minJob, Int_t maxJob, TString outFileStart, TString runLimitsFile)
//{
int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Input File Name
  // 2: Min Job
  // 3: Max Job
  // 4: Output File Name Prefix
  // 5: Run Limits File Name
  // 6: Exclude Run Numbers File Name
  if (argc != 7) 
  {
    cout<<"argc == "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//

  TString inFileName = TString(argv[1]); 
  Int_t minJob = atoi(argv[2]);
  Int_t maxJob = atoi(argv[3]);
  TString outFileStart = TString(argv[4]); 
  TString runLimitsFile = TString(argv[5]); 
  TString excludeRunNumbersFile = TString(argv[6]); 

  std::cout << "Opening Run Limits File " << runLimitsFile << " ...!" <<std::endl;
  FILE *fp = fopen(runLimitsFile,"r");
  if (fp <= 0){
    std::cout << "Sorry can not open File " << runLimitsFile << " ...!" <<std::endl;
    return EXIT_FAILURE;
  }

  vector <pair <double, double> > runVector;
  while(fp){
    float min, max;
    if (fscanf(fp, "%f %f", &min, &max) < 0)break;
    pair <double, double> runLimits; 
    runLimits.first = min; 
    runLimits.second = max; 
    runVector.push_back(runLimits);
  }
  std::cout << "Found " << runVector.size() << " run limits ...!" <<std::endl;
  fclose(fp);

  set <double> excludeRunSet;

  if (excludeRunNumbersFile.CompareTo("NO_FILE") != 0) {
    std::cout << "Opening Exclude RunNumbers File " << excludeRunNumbersFile << " (exclude runNumbers File)!" <<std::endl;
    FILE *fpe = fopen(excludeRunNumbersFile,"r");
    if (fpe <= 0){
      std::cout << "Sorry can not open File " << excludeRunNumbersFile << " (exclude runNumbers File)!" <<std::endl;
      return EXIT_FAILURE;
    }
    while(fpe){
      float runNumber;
      if (fscanf(fpe, "%f", &runNumber) < 0)break;
      excludeRunSet.insert(runNumber);
    }
    std::cout << "Found " << excludeRunSet.size() << " runNumbers to Exclude ...!" <<std::endl;
    fclose(fpe);
  }

  set <double>::iterator itEx;
  for (itEx = excludeRunSet.begin(); itEx != excludeRunSet.end(); itEx++){
    std::cout << " -" << *itEx <<std::endl;
  }

  std::vector<TString> lineNameVector;
  std::vector<TString>::iterator itLine;
//  lineNameVector.push_back("JpsiFromBNoPIDTuple");
  lineNameVector.push_back("JpsiFromBNoPIDNoMipTuple");
  lineNameVector.push_back("DSt2D0Pi_D02RSKPiTuple");
  lineNameVector.push_back("Lam02PPi_LoPTuple");
  lineNameVector.push_back("Lam02PPi_HiPTuple");
  
  vector <pair <double, double> >::iterator it;
  Int_t i = 0;
  for (it = runVector.begin(); it != runVector.end(); it++){
    char buffer[5];
    sprintf(buffer, "%d", i);
    TString  outFileName = outFileStart + TString(buffer) + ".root";
    TFile *g = new TFile(outFileName,"RECREATE");
    for ( itLine = lineNameVector.begin() ; itLine < lineNameVector.end(); itLine++ )
    {
      TString lineName = *itLine;
      ProcessLine(inFileName, minJob, maxJob, lineName, "CalibPID", g, *it, excludeRunSet, lineName.Contains("Jpsi"));
    }
    
    g->Close();
    i++;
  }

  return EXIT_SUCCESS;

}

void ProcessLine(TString fileName, Int_t minJob, Int_t maxJob, TString lineName, TString treeName, TFile *outFile, std::pair <double, double> runLimits, set<double> excludeRunSet, Bool_t putMuonProbTag)
{
  std::cout << "Processing line "<< lineName << " ...!" <<std::endl;
  std::cout << "minJob =  "<< minJob << std::endl;
  std::cout << "maxJob =  "<< maxJob << std::endl;

  TChain* inTree = new TChain(lineName + "/" + treeName);
  for(Int_t i = minJob; i <= maxJob; i++){
    char buffer[15];
    sprintf(buffer, "%d", i);
    TString num(buffer);
    TString file = fileName;
    file.ReplaceAll("_FILE_NUMBER_", num);
    std::cout << "file = " <<file<< std::endl;
    ifstream ifile(file);
    if (!ifile) continue;
    else ifile.close();
    std::cout << "before add: file = " <<file<< std::endl;
    inTree->AddFile(file);
  }

  outFile->mkdir(lineName);
  outFile->cd(lineName);
  TTree *outTree = new TTree(treeName, inTree->GetTitle());
 
 // This part is to build an ntuple with NOT ALL the columns 
 // std::vector<TString> columnNameVector;
 // std::vector<TString>::iterator it;
 // columnNameVector.push_back("B_M");
 // columnNameVector.push_back("B_PT");

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
    TString colName = TString(tb->GetName());
    TString title = TString(tb->GetTitle());
    TString type = TString(tb->GetTitle());
    type = type.Data()[type.Length()-1];

    //Bool_t includeColumn = false;
    //for ( it = columnNameVector.begin() ; it < columnNameVector.end(); it++ )
    //{
    //  TString colName2 = *it;
    //  if (colName2.CompareTo(colName)==0){
    //    includeColumn = true;
    //    break;
    //  }
    //}
    //if (!includeColumn) continue;

    if (type.CompareTo("F")==0)
    {
      if ((!(title.Contains("[3]")))&&(!(title.Contains("[nPV]")))) 
      {
        mapColName[colName] = idxF;
        inTree->SetBranchAddress(colName, &inF[idxF]);
        outTree->Branch(colName, &inF[idxF], title);
        idxF++;
      }
      if (title.Contains("[nPV]"))
      {
        inTree->SetBranchAddress(colName, &inF_100[idxF_100]);
        outTree->Branch(colName, &inF_100[idxF_100], title);
        idxF_100++;
      }
      if (title.Contains("[3]")) 
      {
        inTree->SetBranchAddress(colName, &inF_3_3[idxF_3_3]);
        outTree->Branch(colName, &inF_3_3[idxF_3_3], title);
        idxF_3_3++;
      }
    }
    if (type.CompareTo("I")==0)
    {
      mapColName[colName] = idxI;
      inTree->SetBranchAddress(colName, &inI[idxI]);
      outTree->Branch(colName, &inI[idxI], title);
      idxI++;
    }
    if (type.CompareTo("D")==0)
    {
      mapColName[colName] = idxD;
      inTree->SetBranchAddress(colName, &inD[idxD]);
      outTree->Branch(colName, &inD[idxD], title);
      idxD++;
    }
    if (type.CompareTo("O")==0){
      mapColName[colName] = idxO;
      inTree->SetBranchAddress(colName, &inO[idxO]);
      outTree->Branch(colName, &inO[idxO], title);
      idxO++;
    }
    if (type.CompareTo("S")==0){
      mapColName[colName] = idxS;
      inTree->SetBranchAddress(colName, &inS[idxS]);
      outTree->Branch(colName, &inS[idxS], title);
      idxS++;
    }
    if (type.CompareTo("i")==0){
      mapColName[colName] = idxii;
      inTree->SetBranchAddress(colName, &inii[idxii]);
      outTree->Branch(colName, &inii[idxii], title);
      idxii++;
    }
    if (type.CompareTo("l")==0){
      mapColName[colName] = idxll;
      inTree->SetBranchAddress(colName, &inll[idxll]);
      outTree->Branch(colName, &inll[idxll], title);
      idxll++;
    }
  }

  Bool_t mu0Prob, mu0Tag, mu1Prob, mu1Tag;

  if (putMuonProbTag) {
    outTree->Branch("Mu0_Prob", &mu0Prob, "Mu0_Prob/O");
    outTree->Branch("Mu0_Tag",  &mu0Tag,  "Mu0_Tag/O");
    outTree->Branch("Mu1_Prob", &mu1Prob, "Mu1_Prob/O");
    outTree->Branch("Mu1_Tag",  &mu1Tag,  "Mu1_Tag/O");
  }

  Int_t nEntries = (Int_t) inTree->GetEntries();
 
  for (Int_t i = 0; i < nEntries; i++)
  {  
    if (div((i),500000).rem == 0) std::cout << " entry #: " << i << "/" << nEntries << std::endl;

    inTree->GetEntry(i);

    if ((inD[mapColName["runNumber"]] < runLimits.first) || (inD[mapColName["runNumber"]] >= runLimits.second)) continue;
    if (excludeRunSet.find(inD[mapColName["runNumber"]]) != excludeRunSet.end()) continue;
    
    if (putMuonProbTag) {

      for (Int_t j = 0; j < 2; j++)
      {   
        Bool_t prob=false, tag=false;
        TString prefix = "Mu0"; 
        if (j==1) prefix = "Mu1";
  
        if (div((i),500000).rem == 0) {
          std::cout <<  prefix+"_InMuonAcc = " << inD[mapColName[prefix+"_InMuonAcc"]]; 
          std::cout << ",  (int)" <<  prefix+"_InMuonAcc = " << ((int)inD[mapColName[prefix+"_InMuonAcc"]]); 
          std::cout <<  ", " + prefix+"_TRCHI2DOF = " << inD[mapColName[prefix+"_TRCHI2DOF"]]; 
          std::cout <<  ", " + prefix+"_isMuon = " << inO[mapColName[prefix+"_isMuon"]]; 
          std::cout <<  ", " + prefix+"_P = " << inD[mapColName[prefix+"_P"]] ; 
          std::cout <<  ", " + prefix+"_PT = " << inD[mapColName[prefix+"_PT"]]; 
          std::cout <<  ", " + prefix+"_MIP_PV = " << inD[mapColName[prefix+"_MIP_PV"]]; 
          std::cout <<  ", " + prefix+"_MIPCHI2_PV = " << inD[mapColName[prefix+"_MIPCHI2_PV"]] << std::endl; 
        }

        if (lineName.CompareTo("JpsiNtp")==0) {
  
          if (          ((int)inD[mapColName[prefix+"_InMuonAcc"]]) ==1 && 
                              fabs(inD[mapColName[prefix + "_P"]])>3000 && 
                                   inD[mapColName[prefix + "_PT"]] >800 && 
                               inD[mapColName[prefix+"_TRCHI2DOF"]]<3     )     prob=true;
          if (                                                prob && 
                                 inO[mapColName[prefix+"_isMuon"]]==1 && 
                              fabs(inD[mapColName[prefix+"_P"]])>6000 && 
                                   inD[mapColName[prefix+"_PT"]]>1500 )     tag=true;
          if (                                                prob && 
                      ((inD[mapColName[prefix+"_CaloEcalE"]] < -10 || inD[mapColName[prefix+"_CaloEcalE"]]> 1000.) || 
                      (inD[mapColName[prefix+"_CaloHcalE"]] <1000 || inD[mapColName[prefix+"_CaloHcalE"]]> 4000 )))    prob=false;
        }
        if ((lineName.CompareTo("JpsiFromBNtp")==0)||(lineName.CompareTo("JpsiFromBNoPIDTuple")==0)) {
          if (        ((int)inD[mapColName[prefix+"_InMuonAcc"]]) ==1 && 
                              fabs(inD[mapColName[prefix+"_P"]])>3000 && 
                                   inD[mapColName[prefix+"_PT"]] >800 && 
                               inD[mapColName[prefix+"_TRCHI2DOF"]]<3 &&
                               inD[mapColName[prefix+"_MIP_PV"]]>0.05 &&
                               inD[mapColName[prefix+"_MIPCHI2_PV"]]>25 )     prob=true;
          if (                                                prob && 
                                 inO[mapColName[prefix+"_isMuon"]]==1 && 
                              fabs(inD[mapColName[prefix+"_P"]])>6000 && 
                                   inD[mapColName[prefix+"_PT"]]>1500 && 
                               inD[mapColName[prefix+"_MIP_PV"]]>0.12 )      tag=true;
          if (                                                prob && 
             ((inD[mapColName[prefix+"_CaloEcalE"]] < -10 || inD[mapColName[prefix+"_CaloEcalE"]]> 1000.) || 
             (inD[mapColName[prefix+"_CaloHcalE"]] <1000 || inD[mapColName[prefix+"_CaloHcalE"]]> 4000 )))    prob=false;
        }  
        if (lineName.CompareTo("JpsiFromBNoPIDNoMipTuple")==0) {
          if (        ((int)inD[mapColName[prefix+"_InMuonAcc"]]) ==1 && 
                              fabs(inD[mapColName[prefix+"_P"]])>3000 && 
                                   inD[mapColName[prefix+"_PT"]] >800 && 
                              inD[mapColName[prefix+"_TRCHI2DOF"]]<3   )    prob=true;
          if (                                                prob && 
                                 inO[mapColName[prefix+"_isMuon"]]==1 && 
                              fabs(inD[mapColName[prefix+"_P"]])>6000 && 
                                   inD[mapColName[prefix+"_PT"]]>1500 && 
                               inD[mapColName[prefix+"_MIPCHI2_PV"]]>25 )     tag=true;
        }

        if (j==0) {mu0Prob = prob; mu0Tag = tag;}
        else   {mu1Prob = prob; mu1Tag = tag;}
      }

      if (div((i),500000).rem == 0) {
          std::cout << " mu0Prob = " << mu0Prob;
          std::cout << ", mu0Tag = " << mu0Tag;
          std::cout << ", mu1Prob = " << mu1Prob;
          std::cout << ", mu1Tag = " << mu1Tag << std::endl;
      }

    } //end putMuonProbTag
    
    outTree->Fill();

  } //end loop nEntries
  
  std::cout << " The End " << std::endl;

  outTree->Write();
}



