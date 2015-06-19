// $Id: $
#ifndef CALIBDATASCRIPTS_SETSPECTATORVARS_H 
#define CALIBDATASCRIPTS_SETSPECTATORVARS_H 1

// Include files
#include "RooPhysFitter/RooDMassFitter.h"

using namespace RooPhysFit;

#define UNUSED_ARGUMENT(x) (void)x

/*  @author Andrew Powell (LHCb)04
 *  @date   2011-06-10
 */

void SetSpecVars_EvtVars2012(RooDMassFitter* Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit->AddSpectator("nTracks",                   // Name in DataSet
                     0,                           // Min value
                     1000,                        // Max value
                     "nTracks",                   // Branch name
                     "",                          // Units
                     "No. Best Tracks in Event",  // Title
                     "Event variables");          // NamedSet  

  Mfit->AddSpectator("runNumber",
                     111761,
                     999999,
                     "runNumber",
                     "",
                     "Run Number",
                     "Event variables");
  
}

void SetSpecVars_EvtVars2011(RooDMassFitter* Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit->AddSpectator("nTracks",                   // Name in DataSet
                     0,                           // Min value
                     1000,                        // Max value
                     "nTracks",                   // Branch name
                     "",                          // Units
                     "No. Best Tracks in Event",  // Title
                     "Event variables");          // NamedSet  

  Mfit->AddSpectator("runNumber",
                     87660,
                     104300,
                     "runNumber",
                     "",
                     "Run Number",
                     "Event variables");
  
}

void SetSpecVars_MCEvtVars2011(RooDMassFitter* Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit->AddSpectator("nTracks",                   // Name in DataSet
                     0,                           // Min value
                     1000,                        // Max value
                     "nTracks",                   // Branch name
                     "",                          // Units
                     "No. Best Tracks in Event",  // Title
                     "Event variables");          // NamedSet
}

void SetSpecVars_StdDLLs2011(RooDMassFitter* Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - Std DLLs
  //======================================
  Mfit->AddSpectator(TString::Format("%s_CombDLLK", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDK", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(K - #pi)",
                     "Track variables");
  
  Mfit->AddSpectator(TString::Format("%s_CombDLLp", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDp", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(p - #pi)",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_CombDLLmu", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDmu", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(#mu - #pi)",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_CombDLLe", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDe", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(e - #pi)",
                     "Track variables");

}

void SetSpecVars_EvtVars(RooDMassFitter* Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit->AddSpectator("nPV",              // Name in DataSet
                     0,                  // Min value
                     20,                 // Max value
                     "nPV",              // Branch name
                     "",                 // Units
                     "No. PV in Event",  // Title
                     "Event variables"); // NamedSet

  Mfit->AddSpectator("nTracks", 
                     0, 
                     1000, 
                     "nTracks",
                     "",
                     "No. Tracks in Event", 
                     "Event variables");

  Mfit->AddSpectator("nLong", 
                     0, 
                     1000, 
                     "nLong",
                     "",
                     "No. Long tracks in Event", 
                     "Event variables");

  Mfit->AddSpectator("nRich1_Hits",
                     0,
                     10000,
                     "nRICH1Hits",
                     "",
                     "No. RICH1 Pixel Hits",
                     "Event variables");
  
  Mfit->AddSpectator("nRich2_Hits",
                     0,
                     10000,
                     "nRICH2Hits",
                     "",
                     "No. RICH1 Pixel Hits",
                     "Event variables");
}

void SetSpecVars_MCEvtVars(RooDMassFitter* Mfit,
                           const char* parPrefix_DataSet,
                           const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);
  
  Mfit->AddSpectator("nPV",              // Name in DataSet
                     0,                  // Min value
                     20,                 // Max value
                     "nPV",              // Branch name
                     "",                 // Units
                     "No. PV in Event",  // Title
                     "Event variables"); // NamedSet

  Mfit->AddSpectator("nTracks", 
                     0, 
                     1000, 
                     "nTracks",
                     "",
                     "No. Tracks in Event", 
                     "Event variables");

  Mfit->AddSpectator("nLong", 
                     0, 
                     1000, 
                     "nLong",
                     "",
                     "No. Long tracks in Event", 
                     "Event variables");

  Mfit->AddSpectator("nRich_Hits",
                     0,
                     20000,
                     "nRICHHits",
                     "",
                     "No. RICH Pixel Hits",
                     "Event variables");

}

void SetSpecVars_StdDLLs(RooDMassFitter* Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - Std DLLs
  //======================================
  Mfit->AddSpectator(TString::Format("%s_CombDLLK", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDK", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(K - #pi)",
                     "Track variables");
  
  Mfit->AddSpectator(TString::Format("%s_CombDLLp", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDp", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(p - #pi)",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_CombDLLmu", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDmu", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(#mu - #pi)",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_CombDLLe", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_PIDe", parPrefix_nTuple).Data(),
                     "",
                     "Comb. DLL(e - #pi)",
                     "Track variables");
  
  Mfit->AddSpectator(TString::Format("%s_RichDLLK", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_RICHDLLK", parPrefix_nTuple).Data(),
                     "",
                     "RICH DLL(K - #pi)",
                     "Track variables");
  
  Mfit->AddSpectator(TString::Format("%s_RichDLLp", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_RICHDLLp", parPrefix_nTuple).Data(),
                     "",
                     "RICH DLL(p - #pi)",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_RichDLLmu", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_RICHDLLmu", parPrefix_nTuple).Data(),
                     "",
                     "RICH DLL(#mu - #pi)",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_RichDLLe", parPrefix_DataSet).Data(), 
                     -150.,
                     150., 
                     TString::Format("%s_RICHDLLe", parPrefix_nTuple).Data(),
                     "",
                     "RICH DLL(#mu - #pi)",
                     "Track variables");
}

void SetSpecVars_NeuroBayesVars(RooDMassFitter* Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - NeuroBayes Probs
  //======================================
  Mfit->AddSpectator(TString::Format("%s_ProbNNK", parPrefix_DataSet).Data(), 
                     0.,
                     1., 
                     TString::Format("%s_ProbNNk", parPrefix_nTuple).Data(),
                     "",
                     "NeuroBayes Prob. K",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_ProbNNpi", parPrefix_DataSet).Data(), 
                     0.,
                     1., 
                     TString::Format("%s_ProbNNpi", parPrefix_nTuple).Data(),
                     "",
                     "NeuroBayes Prob. #pi",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_ProbNNp", parPrefix_DataSet).Data(), 
                     0.,
                     1., 
                     TString::Format("%s_ProbNNp", parPrefix_nTuple).Data(),
                     "",
                     "NeuroBayes Prob. p",
                     "Track variables");
  
  Mfit->AddSpectator(TString::Format("%s_ProbNNmu", parPrefix_DataSet).Data(), 
                     -1001.,
                     1., 
                     TString::Format("%s_ProbNNmu", parPrefix_nTuple).Data(),
                     "",
                     "NeuroBayes Prob. #mu",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_ProbNNe", parPrefix_DataSet).Data(), 
                     -1001.,
                     1., 
                     TString::Format("%s_ProbNNe", parPrefix_nTuple).Data(),
                     "",
                     "NeuroBayes Prob. e",
                     "Track variables");
    
}

void SetSpecVars_KinematicVars(RooDMassFitter* Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple)
{
  //======================================
  // Track Kinematic Variables
  //======================================
  Mfit->AddSpectator(TString::Format("%s_P", parPrefix_DataSet).Data(), 
                     0, 
                     500000, 
                     TString::Format("%s_P", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track Momentum",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_PT", parPrefix_DataSet).Data(), 
                     0, 
                     200000, 
                     TString::Format("%s_PT", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Transverse Momentum",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_Eta", parPrefix_DataSet).Data(), 
                     1, 
                     6, 
                     TString::Format("%s_TRACK_Eta", parPrefix_nTuple).Data(),
                     "",
                     "Psuedo Rapidity",
                     "Track variables");
}

void SetSpecVars_HamishVars(RooDMassFitter* Mfit,
                            const char* parPrefix_DataSet,
                            const char* parPrefix_nTuple)
{
  //======================================
  // Track Kinematic Variables Requaested by Hamish Gordon
  //======================================
  Mfit->AddSpectator(TString::Format("%s_PX", parPrefix_DataSet).Data(), 
                     -40000, 
                     40000, 
                     TString::Format("%s_PX", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track X-Axis Momentum",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_PY", parPrefix_DataSet).Data(), 
                     -40000, 
                     40000, 
                     TString::Format("%s_PY", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track Y-Axis Momentum",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_PZ", parPrefix_DataSet).Data(), 
                     0, 
                     800000, 
                     TString::Format("%s_PZ", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track Z-Axis Momentum",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_Phi", parPrefix_DataSet).Data(), 
                     -4, 
                     4, 
                     TString::Format("%s_TRACK_Phi", parPrefix_nTuple).Data(),
                     "",
                     "Azimuthal Angle",
                     "Track variables");
}

void SetSpecVars_RadRadius(RooDMassFitter* Mfit,
                           const char* parPrefix_DataSet,
                           const char* parPrefix_nTuple)
{
  //======================================
  // Radiator Entrance Radii Variables
  //======================================
  Mfit->AddSpectator(TString::Format("%s_Aerogel_Rho", parPrefix_DataSet).Data(), 
                     -1., 
                     400, 
                     TString::Format("%s_Aerogel_Rho", parPrefix_nTuple).Data(),
                     "mm",
                     "Radius of Entry Point",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_Rich1Gas_Rho", parPrefix_DataSet).Data(), 
                     -1., 
                     400, 
                     TString::Format("%s_Rich1Gas_Rho", parPrefix_nTuple).Data(),
                     "mm",
                     "Radius of Entry Point",
                     "Track variables");
  
  Mfit->AddSpectator(TString::Format("%s_Rich2Gas_Rho", parPrefix_DataSet).Data(), 
                     -1., 
                     4000, 
                     TString::Format("%s_Rich2Gas_Rho", parPrefix_nTuple).Data(),
                     "mm",
                     "Radius of Entry Point",
                     "Track variables");
}

void SetSpecVars_RICHCategories(RooDMassFitter* Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple)
{
  //======================================
  // Categories Associated with the RICH
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  std::vector<std::string> types;
  std::vector<Int_t> indices;
  
  types.push_back("Above Threshold");
  types.push_back("Below Threshold");
  indices.push_back(1);
  indices.push_back(0);
  Mfit->AddCategory("Rich_Threshold", types, indices, 
                    TString::Format("%s_RICHThreshold", parPrefix_nTuple).Data(),
                    "Track RICH Threshold for Given Hypo");
  
  types.clear();
  indices.clear();
  types.push_back("Available");
  types.push_back("Unavailable");
  indices.push_back(1);
  indices.push_back(0);
  //Mfit->AddCategory("Aerogel_Info",  types, indices, 
  //                  TString::Format("%s_RICHAerogelUsed", parPrefix_nTuple).Data(),
  //                  "Track Aerogel Information");
  //Mfit->AddCategory("Rich1Gas_Info", types, indices, 
  //                  TString::Format("%s_RICH1GasUsed", parPrefix_nTuple).Data(),
  //                  "Track RICH1-Gas Information");
  //Mfit->AddCategory("Rich2Gas_Info", types, indices, 
  //                  TString::Format("%s_RICH2GasUsed", parPrefix_nTuple).Data(),
  //                  "Track RICH2-Gas Information");
  Mfit->AddCategory("Rich_Info",  types, indices, 
                    TString::Format("%s_hasRich", parPrefix_nTuple).Data(),
                    "Track RICH Information");
  
}

void SetSpecVars_MUONCategories(RooDMassFitter* Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple)
{
  //======================================
  // Categories Associated with the MUONs
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  std::vector<std::string> types;
  std::vector<Int_t> indices;
  
  types.push_back("Pass");
  types.push_back("Fail");
  indices.push_back(1);
  indices.push_back(0);
  Mfit->AddCategory("IsMuon", types, indices, 
                    TString::Format("%s_isMuon", parPrefix_nTuple).Data(),
                    "Track Passess IsMuon Requirement Flag");
  /*
  types.clear();
  indices.clear();
  
  types.push_back("True");
  types.push_back("False");
  types.push_back("Unknown");
  indices.push_back(1);
  indices.push_back(0);
  indices.push_back(-1000);
  Mfit->AddCategory("InMuonAcc", types, indices, 
                    TString::Format("%s_InMuonAcc", parPrefix_nTuple).Data());
  */
}

void SetSpecVars_MuonVars(RooDMassFitter* Mfit,
                          const char* parPrefix_DataSet,
                          const char* parPrefix_nTuple)
{
  //======================================
  // Muon PID Variables
  //======================================
  Mfit->AddSpectator(TString::Format("%s_InMuonAcc", parPrefix_DataSet).Data(), 
                     -1001.,
                     2., 
                     TString::Format("%s_InMuonAcc", parPrefix_nTuple).Data(),
                     "",
                     "In Muon Acceptance Flag",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_IsMuon", parPrefix_DataSet).Data(), 
                     -1001.,
                     2., 
                     TString::Format("%s_isMuon", parPrefix_nTuple).Data(),
                     "",
                     "Pass IsMuon Requirement Flag",
                     "Track variables");

  Mfit->AddSpectator(TString::Format("%s_IsMuonLoose", parPrefix_DataSet).Data(), 
                     -1001.,
                     2., 
                     TString::Format("%s_isMuonLoose", parPrefix_nTuple).Data(),
                     "",
                     "Pass IsMuonLoose Requirement Flag",
                     "Track variables");

  /*Mfit->AddSpectator(TString::Format("%s_IsMuonTight", parPrefix_DataSet).Data(), 
                     -1001.,
                     2., 
                     TString::Format("%s_isMuonTight", parPrefix_nTuple).Data(),
                     "",
                     "Pass IsMuonTight Requirement Flag",
                     "Track variables");
  */

  Mfit->AddSpectator(TString::Format("%s_nShared", parPrefix_DataSet).Data(), 
                     -2.,
                     500., 
                     TString::Format("%s_NShared", parPrefix_nTuple).Data(),
                     "",
                     "Number of tracks w/ shared MUON hits",
                     "Track variables");
}

#endif // CALIBDATASCRIPTS_SETSPECTATORVARS_H
