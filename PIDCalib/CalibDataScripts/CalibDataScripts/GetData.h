// $Id: $
#ifndef CALIBDATASCRIPTS_GETDATA_H 
#define CALIBDATASCRIPTS_GETDATA_H 1

// Include files
#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "boost/lexical_cast.hpp"

#include <vector>

/*
 * @author Andrew Powell (LHCb)04
 *  @date   2011-06-17
 */

void GetData(TTree*& t,
             TString path,
             const char* jobID,
             int subjobID_Min,
             int subjobID_Max,
             const char* FileName,
             const char* SubDir_TreeName)
{ 
  
  TChain* tc = new TChain(SubDir_TreeName);
  
  for(int i = subjobID_Min; 
      i<=subjobID_Max; 
      ++i)
  {
    tc->Add(TString::Format(path+"%s/%s/output/%s",
                            jobID,
                            (boost::lexical_cast<std::string>(i)).c_str(),
                            FileName).Data());
  }
  t = dynamic_cast<TTree*>(tc); 
  std::cout<<"subjob min-ID: "<<subjobID_Min<<'\t'
           <<"subjob max-ID: "<<subjobID_Max<<'\t'
           <<"events: "       <<t->GetEntries()
           <<std::endl;

}

void GetData(TTree*& t,
             std::vector<const char*> files,
             const char* SubDir_TreeName)
{ 
  
  TChain* tc = new TChain(SubDir_TreeName);
  
  std::vector<const char*>::iterator itr;
  for(itr=files.begin(); itr!=files.end(); ++itr)// Loop over ganga IDs
  { 
    //std::cout<<*itr<<std::endl;
    tc->Add(*itr);
  }
  
  t = dynamic_cast<TTree*>(tc); 
  std::cout<<"Events: "<<t->GetEntries()
           <<std::endl;

}


void GetData(TTree*& t,
             TString path,
             const char* jobID,
             const char* FileName,
             const char* SubDir_TreeName)
{ 
  TFile* f = TFile::Open(TString::Format(path+"%s/output/%s",
                                         jobID,
                                         FileName).Data(), 
                         "READ");
  t = (TTree*)f->Get(SubDir_TreeName);
  std::cout<<t<<'\t'<<t->GetEntries()<<std::endl;
}

void GetData(TTree*& t,
             TString path,
             const char* FileName,
             const char* SubDir_TreeName)
{ 
  TFile* f = TFile::Open(TString::Format(path+"%s",
                                         FileName).Data(), 
                         "READ");
  t = (TTree*)f->Get(SubDir_TreeName);
  std::cout<<t<<'\t'<<t->GetEntries()<<std::endl;
}

#endif // CALIBDATASCRIPTS_GETDATA_H


