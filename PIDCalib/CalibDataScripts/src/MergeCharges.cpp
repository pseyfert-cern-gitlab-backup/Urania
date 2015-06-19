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
  if((strcmp(argv[1],"DSt")==0)||(strcmp(argv[1],"DSt_MuonUnBiased")==0))
    ws_name = "RSDStCalib";
  else if((strcmp(argv[1],"Lam0")==0)||(strcmp(argv[1],"Lam0_MuonUnBiased")==0))
    ws_name = "Lam0Calib";
  else if(strcmp(argv[1],"K0S")==0)
    ws_name = "K0SCalib";
  else if(strcmp(argv[1],"Jpsi")==0)
    ws_name = "JpsiCalib";
  else 
  {
    cout<<"Unknow Mother particle: "<<argv[1]<<endl;
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
                                      Myws_Neg);
  if(Mydata_Neg==NULL)
  {
    cout<<"No DataSet (Negative) Found"<<endl;
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
                                      Myws_Pos);
  if(Mydata_Pos==NULL)
  {
    cout<<"No DataSet (Positive) Found"<<endl;
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
    cout<<"No Set 'Categories'"<<endl;
    //exit(1);
  }
  if(EventVars==NULL)
  {
    cout<<"No Set 'Event variables'"<<endl;
    exit(1);
  }
  if(TrackVars==NULL)
  {
    cout<<"No Set 'Track variables'"<<endl;
    exit(1);
  }
  
  RooArgSet* Params = new RooArgSet("Params");
  Params->add(*sWeight);
  if(Cats!=NULL)
    Params->add(*Cats);
  Params->add(*EventVars);
  Params->add(*TrackVars);

  //=============================================================================
  // Configure tight mass cut 
  //=============================================================================
  TString MassCut;
  float mass_D0    = 1864.83;          // MeV
  float mass_Delm  = 2010.25 - mass_D0;// MeV
  float mass_Lam0  = 1115.68;          // MeV
  float mass_KS0   = 497.61;           // MeV
  float mass_Jpsi  = 3096;             // MeV
  float width_D0   = 45;               // MeV
  float width_Delm = 4.5;              // MeV
  float width_Lam0 = 6.5;              // MeV
  float width_KS0  = 23.0;             // MeV
  float width_Jpsi  = 50.0;             // MeV
    
  if((strcmp(argv[1],"DSt")==0)||(strcmp(argv[1],"DSt_MuonUnBiased")==0))
    MassCut.Form("mass>%.2f && "
                 "mass<%.2f && "
                 "delm>%.2f && "
                 "delm<%.2f",
                 mass_D0 - width_D0,
                 mass_D0 + width_D0,
                 mass_Delm - width_Delm,
                 mass_Delm + width_Delm);
  else if((strcmp(argv[1],"Lam0")==0)||(strcmp(argv[1],"Lam0_MuonUnBiased")==0))
    MassCut.Form("mass>%.2f && "
                 "mass<%.2f",
                 mass_Lam0 - width_Lam0,
                 mass_Lam0 + width_Lam0);                 
  else if(strcmp(argv[1],"K0S")==0)
    MassCut.Form("mass>%.2f && "
                 "mass<%.2f",
                 mass_KS0 - width_KS0,
                 mass_KS0 + width_KS0);  
  else if(strcmp(argv[1],"Jpsi")==0)
    MassCut.Form("mass>%.2f && "
                 "mass<%.2f",
                 mass_Jpsi - width_Jpsi,
                 mass_Jpsi + width_Jpsi);  
  //cout<<"MassCut: "<<argv[1]<<'\t'<<MassCut.Data()<<endl;
  
  //=============================================================================
  // Merge +ve and -ve datasets and associate with states in RooCategory Charges
  //=============================================================================
  RooDataSet* DataSet_comb = new RooDataSet(TString::Format("%s %s",argv[1],argv[3]).Data()
                                            ,"Combined DataSet"
                                            ,*Params
                                            ,Index(Charges)
                                            ,Import("Negative", *Mydata_Neg)
                                            ,Import("Positive", *Mydata_Pos)
                                            //,Cut(MassCut.Data())
                                            ); 
  DataSet_comb->Print("v");
  
  cout<<"****** Neg Sum:    "<<Mydata_Neg->numEntries()  <<endl;
  cout<<"****** Pos Sum:    "<<Mydata_Pos->numEntries()  <<endl;
  cout<<"****** Merged Sum: "<<DataSet_comb->numEntries()<<endl;
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
                       RooWorkspace*& ws)
{
  cout<<"In getDataSet"<<endl;

  TString path = TString::Format("%s/",Path);
  TFile* f = NULL;
  
  //=============================================================================
  // Open file
  //=============================================================================
  f = new TFile(TString::Format(path+"%s_%s%s_Mag%s_Strip%s_%s.root",
                                MumName,
                                PartName,
                                Charge,
                                FieldPolarity,
                                StripVersion,
                                Index).Data());
  if(f==NULL)
  {
    cout<<"No File "<<TString::Format(path+"%s_%s%s_Mag%s_Strip%s_%s.root",
                                      MumName,
                                      PartName,
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
    cout<<"No Workspace '"<<WorkspaceName<<"'"<<endl;
    exit(1);
  }
  if(ws->data("data_wSWeights")!=NULL)
    return (RooDataSet*)ws->data("data_wSWeights");
  else
  {
    return NULL;
  }
}

