// $Id: $
// Include files
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "TFile.h"
#include "TSystem.h"

// namespaces
using namespace std;

// local
RooDataSet* getDataSet(const char* Path,
                       const char* MumName,
                       const char* PartName,
                       const char* Charge,
                       const char* FieldPolarity,
                       const char* StripVersion,
                       const char* Index,
                       const char* WorkspaceName,
                       RooWorkspace*& ws);

using namespace RooFit;

//-----------------------------------------------------------------------------
// Implementation file for class : MergeProtonLines
//
// 2011-06-09 : Andrew Powell (LHCb)04
//
// Example Usage:
// $CALIBDATASCRIPTSROOT/$CMTCONFIG/MergeProtonLines.exe DSt $PWD Pi Down 15 $PWD 0
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Path to datafiles 
  // 2: Particle Name
  // 3: Charge
  // 4: Field Orientation (Up or Down)
  // 5: Stripping Version
  // 6: Output Path
  // 7. Index
  if (argc != 8) 
  {
    cout<<"argc == "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  gSystem->Load("libRooFit.so");

  //=============================================================================
  // Assign the workspace name
  //=============================================================================
  const char* ws_name = "IncLcCalib";

  //=============================================================================
  // Get pointers to LoP dataset and workspace 
  //=============================================================================
  RooWorkspace* Myws_LoP = NULL;
  RooDataSet* Mydata_LoP = getDataSet(argv[1],
                                      "P",
                                      argv[3],
                                      "IncLc",
                                      argv[4],
                                      argv[5],
                                      argv[7],
                                      ws_name,
                                      Myws_LoP);
  if(Mydata_LoP==NULL)
  {
    cerr<<"No DataSet (Negative) Found"<<endl;
    return EXIT_FAILURE;
  }

  //=============================================================================
  // Get pointers to hiP dataset and workspace 
  //=============================================================================
  RooWorkspace* Myws_hiP = NULL;
  RooDataSet* Mydata_hiP = getDataSet(argv[1],
                                      "P",
                                      argv[3],
                                      "LcfB",
                                      argv[4],
                                      argv[5],
                                      argv[7],
                                      ws_name,
                                      Myws_hiP);
  if(Mydata_hiP==NULL)
  {
    cerr<<"No DataSet (Positive) Found"<<endl;
    return EXIT_FAILURE;
  }

  //=============================================================================
  // Declare RooArgSets to be stored in merged workspace  
  //=============================================================================
  cout<<"Obtaining workspace sets "<<Mydata_LoP<<'\t'<<Mydata_hiP<<endl;
  const RooArgSet* Cats       = Myws_LoP->set("Categories");
  const RooArgSet* EventVars  = Myws_LoP->set("Event variables");
  const RooArgSet* TrackVars  = Myws_LoP->set("Track variables");
  const RooArgSet* WeightVars = Myws_LoP->set("Weights");

  cout<<"Workspace sets Obtained"<<endl;
  
  if(Cats==NULL)
  {
    cerr<<"No Set 'Categories'"<<endl;
    //exit(1);
  }
  if(EventVars==NULL)
  {
    cerr<<"No Set 'Event variables'"<<endl;
    exit(1);
  }
  if(TrackVars==NULL)
  {
    cerr<<"No Set 'Track variables'"<<endl;
    exit(1);
  }
  if(WeightVars==NULL)
  {
    cerr<<"No Set 'Weight variables'"<<endl;
    exit(1);
  }

  //=============================================================================
  // Append Lo and Hi P datasets 
  //=============================================================================
  RooDataSet* Mydata_All = (RooDataSet*)Mydata_LoP->Clone();
  Mydata_All->append(*Mydata_hiP);
  
  cout<<"****** LoP Sum:   "<<Mydata_LoP->numEntries()<<endl;
  cout<<"****** hiP Sum:   "<<Mydata_hiP->numEntries()<<endl;
  cout<<"****** All Sum:   "<<Mydata_All->numEntries()<<endl;
  
  delete Mydata_LoP;
  delete Mydata_hiP;
  
  
  //=============================================================================
  // Import dataset and RooArgSets into workspace and save to file 
  //=============================================================================
  RooWorkspace* m_ws = new RooWorkspace(ws_name);
  m_ws->import(*Mydata_All, Rename("data_wSWeights"));
  if(Cats!=NULL)
    m_ws->defineSet("Categories",*Cats);
  m_ws->defineSet("Event variables",*EventVars);
  m_ws->defineSet("Track variables",*TrackVars);
  m_ws->defineSet("Weight variables",*WeightVars);
  m_ws->writeToFile(TString::Format("%s/TotLc_%s%s_Mag%s_Strip%s_%s.root",
                                    argv[6],
                                    "P",
                                    argv[3],
                                    argv[4],
                                    argv[5],
                                    argv[7]).Data(), 
                    kTRUE);
  m_ws->Print("v");

  //=============================================================================
  // Clean up 
  //=============================================================================
  delete m_ws;

return EXIT_SUCCESS;

}

//=============================================================================
// Function returning a pointer to desired RooDataSet. Caller of function takes  
// ownership of RooDataSet and is responsible for removing it from the stack.
//=============================================================================
RooDataSet* getDataSet(const char* Path,
                       const char* PartName,
                       const char* Charge,
                       const char* MomType,
                       const char* FieldPolarity,
                       const char* StripVersion,
                       const char* Index,
                       const char* WorkspaceName,
                       RooWorkspace*& ws)
{
  cout<<"In getDataSet"<<endl;

  TString path = TString::Format("%s/",Path);
  TFile* f = NULL;
  
  //=============================================================================
  // Open file
  //=============================================================================
  f = new TFile(TString::Format(path+"%s_P%s_Mag%s_Strip%s_%s.root",
				MomType,     Charge,
                                FieldPolarity,
                                StripVersion,
                                Index).Data());
  if(f==NULL)
  {
    cerr<<"No File "<<TString::Format(path+"%s_P%s_Mag%s_Strip%s_%s.root",
				      MomType,
                                      Charge,
                                      FieldPolarity,
                                      StripVersion,
                                      Index).Data()<<endl;
    exit(1);
  }

  //=============================================================================
  // Obtain pointer to Workspace and DataSet 
  //=============================================================================
  if(f->Get(WorkspaceName)!=NULL)
    ws=(RooWorkspace*)f->Get(WorkspaceName);
  else
  {
    cerr<<"No Workspace '"<<WorkspaceName<<"'"<<endl;
    exit(1);
  }
  if(ws->data("data_wSWeights")!=NULL)
    return (RooDataSet*)ws->data("data_wSWeights");
  else
  {
    return NULL;
  }
}

