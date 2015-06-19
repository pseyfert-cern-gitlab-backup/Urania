// $Id: $
#ifndef CALIBDATASCRIPTS_DSTFIT_H 
#define CALIBDATASCRIPTS_DSTFIT_H 1

/*
 *  @author Andrew Powell (LHCb)04
 *  @date   2011-06-14
 */

// Include files
#include "RooPhysFitter/RooDstarD0MassFitter.h"
#include "CalibDataScripts/LHCbStyle.h"

// Type Definitions
typedef void (*fptr)(RooDMassFitter*, 
                     const char*,
                     const char*);

void DStFit(TTree* tt, 
            const char* charge,
            const char* pName,
            const char* wsName,
            const char* fName,
            const char* dsName,
            const char* d0Name,
            const char* delmName,
            std::vector<fptr>& fun_vec)
{
  
  //==================================================//
  // Constants
  //==================================================//
  Float_t d0MassPDG=1864.83;
  Float_t delmPDG=145.421;
  //Float_t piPDG=139.57018;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooDstarD0MassFitter* massFitter = new RooDstarD0MassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(d0Name);
  massFitter->SetDelmName(delmName);
  massFitter->MakeDMassVar(d0MassPDG-70,
                           d0MassPDG+70,
                           "MeV/c^{2}",
                           "m_{K#pi}");
  massFitter->MakeDelmVar(delmPDG-6.0,
                          delmPDG+7.0,
                          "MeV/c^{2}",
                          "m_{K#pi#pi_{s}}-m_{K#pi}");

  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout<<"Adding Spectator Vars"<<std::endl;
    (*itr)(massFitter, pName, pName);
  }
  
  //==================================================//
  // Select tracks with specific charge
  //==================================================//
  TString chrg="";
  if(strcmp(charge, "Positive")==0)
    chrg = "1.0";
  else if(strcmp(charge,"Negative")==0)
    chrg = "-1.0";
  else{
    std::cout<<"Unexpected charge type "<<charge<<std::endl;
    exit(1);
  }

  massFitter->MakeDelmDataSet(tt, 
                              "D0_M", 
                              "DSt_M", 
                              dsName, 
                              "", 
                              TString::Format("%s_hasRich == 1.0 && "
                                              "DSt_BKGCAT == 0.0 && "
                                              "%s_Q == "+chrg, pName, pName).Data(),
                              kFALSE);

  RooRealVar Dummy_sw("nsig_sw", 
                      "",
                      1.0);
  (massFitter->GetDataSet())->addColumn(Dummy_sw);
  
  (massFitter->GetWS())->import(Dummy_sw);
  
  if ((massFitter->GetWS())->extendSet("Weights", "nsig_sw"))
  {
    
    throw WSImportFailure("MyFunc",
                          *(massFitter->GetWS()), "Weights", "myWeight", kFALSE);
  }
  
  
  massFitter->SaveWS();
  
  
  //==================================================// 
  // Clean up
  //==================================================//
  delete massFitter;
  
}
#endif // CALIBDATASCRIPTS_DSTFIT_H
