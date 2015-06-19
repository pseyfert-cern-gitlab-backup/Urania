// $Id: $
// Include files
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "TFile.h"
#include "TSystem.h"

// namespaces
using std::endl;
using std::cout;
using std::cerr;

// local
RooDataSet* getDataSet(const char* Path,
                       const char* MumName,
                       const char* PartName,
                       const char* Charge,
                       const char* FieldPolarity,
                       const char* StripVersion,
                       const char* Index,
                       const char* WorkspaceName,
                       const char* BremSuffix,
                       RooWorkspace*& ws);

using namespace RooFit;

//-----------------------------------------------------------------------------
// Implementation file for class : MergeCharges
//
// 2011-06-09 : Andrew Powell (LHCb)04
//
// Example Usage:
// $CALIBDATASCRIPTSROOT/$CMTCONFIG/MergeCharges.exe DSt $PWD Pi Down 15 $PWD 0
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Mother Particle
  // 2: Path to datafiles
  // 3: Particle Name
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
  // Define RooCategory for +ve/-ve charges
  //=============================================================================
  RooCategory Charges("Charge", "Track Charge");
  Charges.defineType("Positive");
  Charges.defineType("Negative");

  //=============================================================================
  // Assign a workspace name depending on Mother Particle
  //=============================================================================
  const char* ws_name = NULL;
  const char* bremSuffix = "";
  if((strcmp(argv[1],"DSt")==0)||(strcmp(argv[1],"DSt_MuonUnBiased")==0)) {
    ws_name = "RSDStCalib";
  } else if((strcmp(argv[1],"Lam0")==0)||(strcmp(argv[1],"Lam0_MuonUnBiased")==0)) {
    ws_name = "Lam0Calib";
  } else if((strcmp(argv[1],"Jpsi")==0)&&(strcmp(argv[3],"e")==0)) {
    ws_name = "JpsieeCalib";
    bremSuffix = "_Brem";
  } else if(strcmp(argv[1],"Jpsi")==0) {
    ws_name = "JpsiCalib";
  } else {
    cerr<<"Unknow Mother particle: "<<argv[1]<<endl;
    return EXIT_FAILURE;
  }

  //=============================================================================
  // Get pointers to -ve dataset and workspace
  //=============================================================================
  RooWorkspace* Myws_Neg = NULL;
  RooDataSet* Mydata_Neg = getDataSet(argv[2],
                                      argv[1],
                                      argv[3],
                                      "Minus",
                                      argv[4],
                                      argv[5],
                                      argv[7],
                                      ws_name,
                                      bremSuffix,
                                      Myws_Neg);
  if(Mydata_Neg==NULL)
  {
    cerr<<"DataSet (Negative) not found"<<endl;
    return EXIT_FAILURE;
  }

  //=============================================================================
  // Get pointers to +ve dataset and workspace
  //=============================================================================
  RooWorkspace* Myws_Pos = NULL;
  RooDataSet* Mydata_Pos = getDataSet(argv[2],
                                      argv[1],
                                      argv[3],
                                      "Plus",
                                      argv[4],
                                      argv[5],
                                      argv[7],
                                      ws_name,
                                      bremSuffix,
                                      Myws_Pos);
  if(Mydata_Pos==NULL)
  {
    cerr<<"DataSet (Positive) not found"<<endl;
    return EXIT_FAILURE;
  }

  //=============================================================================
  // Declare RooArgSets to be stored in merged workspace
  //=============================================================================
  cout<<"Obtaining workspace sets "<<Mydata_Neg<<'\t'<<Mydata_Pos<<endl;
  const RooArgSet* Cats      = Myws_Neg->set("Categories");
  const RooArgSet* EventVars = Myws_Neg->set("Event variables");
  const RooArgSet* TrackVars = Myws_Neg->set("Track variables");
  RooRealVar* sWeight  = (RooRealVar*)(Myws_Neg->allVars()).find("nsig_sw");
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

  RooArgSet* Params = new RooArgSet("Params");
  Params->add(*sWeight);
  if(Cats!=NULL)
    Params->add(*Cats);
  Params->add(*EventVars);
  Params->add(*TrackVars);

  //=============================================================================
  // Merge +ve and -ve datasets and associate with states in RooCategory Charges
  //=============================================================================
  RooDataSet* DataSet_comb = new RooDataSet(TString::Format("%s %s",argv[1],argv[3]).Data()
                                            ,"Combined DataSet"
                                            ,*Params
                                            ,Index(Charges)
                                            ,Import("Negative", *Mydata_Neg)
                                            ,Import("Positive", *Mydata_Pos)
                                            );

  if (strcmp(ws_name, "JpsieeCalib") == 0) {
    bremSuffix = "_NoBrem";

    RooWorkspace* Myws_Neg_NoBrem = NULL;
    RooDataSet* Mydata_Neg_NoBrem = getDataSet(argv[2],
                                        argv[1],
                                        argv[3],
                                        "Minus",
                                        argv[4],
                                        argv[5],
                                        argv[7],
                                        ws_name,
                                        bremSuffix,
                                        Myws_Neg_NoBrem);
    if(Mydata_Neg_NoBrem==NULL)
    {
      cerr<<"DataSet (Negative, No brem) not found"<<endl;
      return EXIT_FAILURE;
    }

    RooWorkspace* Myws_Pos_NoBrem = NULL;
    RooDataSet* Mydata_Pos_NoBrem = getDataSet(argv[2],
                                        argv[1],
                                        argv[3],
                                        "Plus",
                                        argv[4],
                                        argv[5],
                                        argv[7],
                                        ws_name,
                                        bremSuffix,
                                        Myws_Pos_NoBrem);
    if(Mydata_Pos_NoBrem==NULL)
    {
      cerr<<"DataSet (Positive, No brem) not found"<<endl;
      return EXIT_FAILURE;
    }

    RooDataSet* DataSet_comb_NoBrem = new RooDataSet(TString::Format("%s %s",argv[1],argv[3]).Data()
                                              ,"Combined DataSet"
                                              ,*Params
                                              ,Index(Charges)
                                              ,Import("Negative", *Mydata_Neg_NoBrem)
                                              ,Import("Positive", *Mydata_Pos_NoBrem)
                                              );

    DataSet_comb->append(*DataSet_comb_NoBrem);

    DataSet_comb->Print("v");

    cout<<"****** Neg Brem Sum:    "<<Mydata_Neg->numEntries()  <<endl;
    cout<<"****** Pos Brem Sum:    "<<Mydata_Pos->numEntries()  <<endl;
    cout<<"****** Neg No Brem Sum: "<<Mydata_Neg_NoBrem->numEntries()  <<endl;
    cout<<"****** Pos No Brem Sum: "<<Mydata_Pos_NoBrem->numEntries()  <<endl;
    cout<<"****** Merged Sum:      "<<DataSet_comb->numEntries()<<endl;

    delete Mydata_Neg_NoBrem;
    delete Mydata_Pos_NoBrem;

  } else {

    DataSet_comb->Print("v");

    cout<<"****** Neg Sum:    "<<Mydata_Neg->numEntries()  <<endl;
    cout<<"****** Pos Sum:    "<<Mydata_Pos->numEntries()  <<endl;
    cout<<"****** Merged Sum: "<<DataSet_comb->numEntries()<<endl;

  }
  
  //cout<<"****** NB. Merged Sum != (Neg + Pos) since a tight mass cut is applied to these events"<<endl;

  //=============================================================================
  // Import dataset and RooArgSets into workspace and save to file
  //=============================================================================
  RooWorkspace* m_ws = new RooWorkspace(ws_name);
  m_ws->import(*DataSet_comb, Rename("data"));
  if(Cats!=NULL)
    m_ws->defineSet("Categories",*Cats);
  m_ws->defineSet("Event variables",*EventVars);
  m_ws->defineSet("Track variables",*TrackVars);
  m_ws->writeToFile(TString::Format("%s/%s_%s_Mag%s_Strip%s_%s.root",
                                    argv[6],
                                    argv[1],
                                    argv[3],
                                    argv[4],
                                    argv[5],
                                    argv[7]).Data(),
                    kTRUE);
  m_ws->Print("v");

  //=============================================================================
  // Clean up
  //=============================================================================
  delete Params;
  delete Mydata_Neg;
  delete Mydata_Pos;
  delete m_ws;

return EXIT_SUCCESS;

}

//=============================================================================
// Function returning a pointer to desired RooDataSet. Caller of function takes
// ownership of RooDataSet and is responsible for removing it from the stack.
//=============================================================================
RooDataSet* getDataSet(const char* Path,
                       const char* MumName,
                       const char* PartName,
                       const char* Charge,
                       const char* FieldPolarity,
                       const char* StripVersion,
                       const char* Index,
                       const char* WorkspaceName,
                       const char* BremSuffix,
                       RooWorkspace*& ws)
{
  cout<<"In getDataSet"<<endl;

  TString path = TString::Format("%s/",Path);
  TFile* f = NULL;

  //=============================================================================
  // Open file
  //=============================================================================
  f = new TFile(TString::Format(path+"%s_%s%s_Mag%s_Strip%s%s_%s.root",
                                MumName,
                                PartName,
                                Charge,
                                FieldPolarity,
                                StripVersion,
                                BremSuffix,
                                Index).Data());
  if(f==NULL)
  {
    cerr<<"No File "<<TString::Format(path+"%s_%s%s_Mag%s_Strip%s%s_%s.root",
                                      MumName,
                                      PartName,
                                      Charge,
                                      FieldPolarity,
                                      StripVersion,
                                      BremSuffix,
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

