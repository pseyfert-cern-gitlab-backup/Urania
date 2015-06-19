// Include files 

#include "RooPhysFitter/RooDMassFitter.h"
#include <boost/math/constants/constants.hpp>

// local
#include "CalibDataScripts/SetSpectatorVars.h"

//-----------------------------------------------------------------------------
// Implementation file for class : SetSpectatorVars
//
// 2013-11-18 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

#define UNUSED_ARGUMENT(x) (void)x
const float pi = boost::math::constants::pi<float>();

void SetSpecVars_EvtVars2012(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit.AddSpectator("nTracks",                   // Name in DataSet
                    0,                           // Min value
                    1000,                        // Max value
                    "nTracks",                   // Branch name
                    "",                          // Units
                    "No. Best Tracks in Event",  // Title
                    "Event variables");          // NamedSet  

  Mfit.AddSpectator("runNumber",
                    111761,
                    999999,
                    "runNumber",
                    "",
                    "Run Number",
                    "Event variables");
  
}

void SetSpecVars_EvtVars2011(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit.AddSpectator("nTracks",                   // Name in DataSet
                    0,                           // Min value
                    1000,                        // Max value
                    "nTracks",                   // Branch name
                    "",                          // Units
                    "No. Best Tracks in Event",  // Title
                    "Event variables");          // NamedSet  

  Mfit.AddSpectator("runNumber",
                    87660,
                    104300,
                    "runNumber",
                    "",
                    "Run Number",
                    "Event variables");
}

void SetSpecVars_MCEvtVars2011(RooPhysFit::RooDMassFitter& Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit.AddSpectator("nTracks",                   // Name in DataSet
                    0,                           // Min value
                    1000,                        // Max value
                    "nTracks",                   // Branch name
                    "",                          // Units
                    "No. Best Tracks in Event",  // Title
                    "Event variables");          // NamedSet
}

void SetSpecVars_StdDLLs2011(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - Std DLLs
  //======================================
  Mfit.AddSpectator(TString::Format("%s_CombDLLK", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDK", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(K - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_CombDLLp", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDp", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(p - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_CombDLLmu", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDmu", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(#mu - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_CombDLLe", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDe", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(e - #pi)",
                    "Track variables");
}

void SetSpecVars_EvtVars(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);

  Mfit.AddSpectator("nPV",              // Name in DataSet
                    0,                  // Min value
                    20,                 // Max value
                    "nPV",              // Branch name
                    "",                 // Units
                    "No. PV in Event",  // Title
                    "Event variables"); // NamedSet

  Mfit.AddSpectator("nTracks", 
                    0, 
                    1000, 
                    "nTracks",
                    "",
                    "No. Tracks in Event", 
                    "Event variables");

  Mfit.AddSpectator("nLong", 
                    0, 
                    1000, 
                    "nLong",
                    "",
                    "No. Long tracks in Event", 
                    "Event variables");

  Mfit.AddSpectator("nRich1_Hits",
                    0,
                    10000,
                    "nRICH1Hits",
                    "",
                    "No. RICH1 Pixel Hits",
                    "Event variables");
  
  Mfit.AddSpectator("nRich2_Hits",
                    0,
                    10000,
                    "nRICH2Hits",
                    "",
                    "No. RICH1 Pixel Hits",
                    "Event variables");
}

void SetSpecVars_MCEvtVars(RooPhysFit::RooDMassFitter& Mfit,
                           const char* parPrefix_DataSet,
                           const char* parPrefix_nTuple)
{
  //======================================
  // Event Variables
  //======================================
  UNUSED_ARGUMENT(parPrefix_DataSet);
  UNUSED_ARGUMENT(parPrefix_nTuple);
  
  Mfit.AddSpectator("nPV",              // Name in DataSet
                    0,                  // Min value
                    20,                 // Max value
                    "nPV",              // Branch name
                     "",                 // Units
                    "No. PV in Event",  // Title
                    "Event variables"); // NamedSet

  Mfit.AddSpectator("nTracks", 
                    0, 
                    1000, 
                    "nTracks",
                    "",
                    "No. Tracks in Event", 
                    "Event variables");

  Mfit.AddSpectator("nLong", 
                    0, 
                    1000, 
                    "nLong",
                    "",
                    "No. Long tracks in Event", 
                    "Event variables");

  Mfit.AddSpectator("nRich_Hits",
                    0,
                    20000,
                    "nRICHHits",
                    "",
                    "No. RICH Pixel Hits",
                    "Event variables");
}

void SetSpecVars_StdDLLs(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - Std DLLs
  //======================================
  Mfit.AddSpectator(TString::Format("%s_CombDLLK", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_PIDK", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(K - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_CombDLLp", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_PIDp", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(p - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_CombDLLmu", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_PIDmu", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(#mu - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_CombDLLe", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_PIDe", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(e - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_RichDLLK", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_RICHDLLK", parPrefix_nTuple).Data(),
                    "",
                    "RICH DLL(K - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_RichDLLp", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_RICHDLLp", parPrefix_nTuple).Data(),
                    "",
                    "RICH DLL(p - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_RichDLLmu", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_RICHDLLmu", parPrefix_nTuple).Data(),
                    "",
                    "RICH DLL(#mu - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_RichDLLe", parPrefix_DataSet).Data(), 
                    -150.,
                    150., 
                    TString::Format("%s_RICHDLLe", parPrefix_nTuple).Data(),
                    "",
                    "RICH DLL(#mu - #pi)",
                    "Track variables");
}

void SetSpecVars_ANNVars(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - ANN Probs
  //======================================
  Mfit.AddSpectator(TString::Format("%s_ProbNNK", parPrefix_DataSet).Data(), 
                    0.,
                    1., 
                    TString::Format("%s_ProbNNk", parPrefix_nTuple).Data(),
                    "",
                     "ANN Prob. K",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_ProbNNpi", parPrefix_DataSet).Data(), 
                    0.,
                    1., 
                    TString::Format("%s_ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #pi",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_ProbNNp", parPrefix_DataSet).Data(), 
                    0.,
                    1., 
                    TString::Format("%s_ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. p",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_ProbNNmu", parPrefix_DataSet).Data(), 
                    -1001.,
                    1., 
                    TString::Format("%s_ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #mu",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_ProbNNe", parPrefix_DataSet).Data(), 
                    -1001.,
                    1., 
                    TString::Format("%s_ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. e",
                    "Track variables");
}

void SetSpecVars_KinematicVars(RooPhysFit::RooDMassFitter& Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple)
{
  //======================================
  // Track Kinematic Variables
  //======================================
  Mfit.AddSpectator(TString::Format("%s_P", parPrefix_DataSet).Data(), 
                    0, 
                    500000, 
                    TString::Format("%s_P", parPrefix_nTuple).Data(),
                    "MeV/c",
                    "Track Momentum",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_PT", parPrefix_DataSet).Data(), 
                    0, 
                    200000, 
                    TString::Format("%s_PT", parPrefix_nTuple).Data(),
                    "MeV/c",
                    "Transverse Momentum",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Eta", parPrefix_DataSet).Data(), 
                    1, 
                    6, 
                    TString::Format("%s_ETA", parPrefix_nTuple).Data(),
                    "",
                    "Psuedo Rapidity",
                    "Track variables");
  Mfit.AddSpectator(TString::Format("%s_Phi", parPrefix_DataSet).Data(), 
                    -1.*pi, 
                    pi, 
                    TString::Format("%s_PHI", parPrefix_nTuple).Data(),
                    "",
                    "Track phi",
                    "Track variables");
}

void SetSpecVars_HamishVars(RooPhysFit::RooDMassFitter& Mfit,
                            const char* parPrefix_DataSet,
                            const char* parPrefix_nTuple)
{
  //======================================
  // Track Kinematic Variables Requaested by Hamish Gordon
  //======================================
  Mfit.AddSpectator(TString::Format("%s_PX", parPrefix_DataSet).Data(), 
                     -40000, 
                     40000, 
                     TString::Format("%s_PX", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track X-Axis Momentum",
                     "Track variables");

  Mfit.AddSpectator(TString::Format("%s_PY", parPrefix_DataSet).Data(), 
                     -40000, 
                     40000, 
                     TString::Format("%s_PY", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track Y-Axis Momentum",
                     "Track variables");

  Mfit.AddSpectator(TString::Format("%s_PZ", parPrefix_DataSet).Data(), 
                     0, 
                     800000, 
                     TString::Format("%s_PZ", parPrefix_nTuple).Data(),
                     "MeV/c",
                     "Track Z-Axis Momentum",
                     "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Phi", parPrefix_DataSet).Data(), 
                     -4, 
                     4, 
                     TString::Format("%s_TRACK_Phi", parPrefix_nTuple).Data(),
                     "",
                     "Azimuthal Angle",
                     "Track variables");
}

void SetSpecVars_RadRadius(RooPhysFit::RooDMassFitter& Mfit,
                           const char* parPrefix_DataSet,
                           const char* parPrefix_nTuple)
{
  //======================================
  // Radiator Entrance Radii Variables
  //======================================
  Mfit.AddSpectator(TString::Format("%s_Aerogel_Rho", parPrefix_DataSet).Data(), 
                     -1., 
                     400, 
                     TString::Format("%s_Aerogel_Rho", parPrefix_nTuple).Data(),
                     "mm",
                     "Radius of Entry Point",
                     "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Rich1Gas_Rho", parPrefix_DataSet).Data(), 
                     -1., 
                     400, 
                     TString::Format("%s_Rich1Gas_Rho", parPrefix_nTuple).Data(),
                     "mm",
                     "Radius of Entry Point",
                     "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_Rich2Gas_Rho", parPrefix_DataSet).Data(), 
                     -1., 
                     4000, 
                     TString::Format("%s_Rich2Gas_Rho", parPrefix_nTuple).Data(),
                     "mm",
                     "Radius of Entry Point",
                     "Track variables");
}

void SetSpecVars_RICHVars(RooPhysFit::RooDMassFitter& Mfit,
                          const char* parPrefix_DataSet,
                          const char* parPrefix_nTuple)
{
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_pi", parPrefix_DataSet).Data(),
                   -2.,
                   2.,
		    TString::Format("%s_RICHThresholdPi", parPrefix_nTuple).Data()," ",
                   "Track RICH threshold for pions",
                   "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_K", parPrefix_DataSet).Data(),
                   -2.,
                   2.,
		    TString::Format("%s_RICHThresholdKa", parPrefix_nTuple).Data()," ",
                   "Track RICH threshold for kaons",
                   "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_p", parPrefix_DataSet).Data(),
                   -2.,
                   2., 
		    TString::Format("%s_RICHThresholdPr", parPrefix_nTuple).Data()," ",
                   "Track RICH threshold for protons",
                   "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_mu", parPrefix_DataSet).Data(),
                   -2., 
                   2.,
		    TString::Format("%s_RICHThresholdMu", parPrefix_nTuple).Data()," ",
                   "Track RICH threshold for muons",
                   "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_e", parPrefix_DataSet).Data(),
                   -2., 
                   2.,
		    TString::Format("%s_RICHThresholdEl", parPrefix_nTuple).Data()," ",
                   "Track RICH threshold for electrons",
                   "Track variables");
                   
  Mfit.AddSpectator(TString::Format("%s_RICHAerogelUsed", parPrefix_DataSet).Data(),
                   -2.,
                   2., 
		    TString::Format("%s_RICHAerogelUsed", parPrefix_nTuple).Data()," ",
                   "Track has Aerogel information",
                   "Track variables");

  Mfit.AddSpectator(TString::Format("%s_RICH1GasUsed", parPrefix_DataSet).Data(),
                   -2., 
                   2., 
		    TString::Format("%s_RICH1GasUsed", parPrefix_nTuple).Data()," ",
                   "Track has RICH1 gas information",
                   "Track variables");

  Mfit.AddSpectator(TString::Format("%s_RICH2GasUsed", parPrefix_DataSet).Data(),
                   -2., 
                   2., 
		    TString::Format("%s_RICH2GasUsed", parPrefix_nTuple).Data()," ",
                   "Track has RICH2 gas information",
                   "Track variables");
                   
  Mfit.AddSpectator(TString::Format("%s_hasRich", parPrefix_DataSet).Data(),
                    -1.,
                    2.,
                    TString::Format("%s_hasRich", parPrefix_nTuple).Data()," ",
                    "Track has RICH information",
                    "Track variables");
}

void SetSpecVars_RICHCategories(RooPhysFit::RooDMassFitter& Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple)
{
  //======================================
  // Categories Associated with the RICH
  //======================================
  std::vector<std::string> types;
  std::vector<Int_t> indices;

  types.push_back("AboveThreshold");
  types.push_back("BelowThreshold");
  types.push_back("Unknown"); // Rich_Info==Rich_Info::Unavailable
  indices.push_back(1);
  indices.push_back(0);
  indices.push_back(-1);
  
  /*  Mfit.AddCategory("RichThreshold", types, indices, 
                    TString::Format("%s_RICHThreshold", parPrefix_nTuple).Data(),
                    "Track RICH threshold for assigned hypothesis",
                     "Track variables"); */
  
  Mfit.AddCategory(TString::Format("%s_Threshold_pi", parPrefix_DataSet).Data(),
                   types, indices,
                    TString::Format("%s_RICHThresholdPi", parPrefix_nTuple).Data(),
                    "Track RICH threshold for pions");
                    
  Mfit.AddCategory(TString::Format("%s_Threshold_K", parPrefix_DataSet).Data(),
                   types, indices,
                    TString::Format("%s_RICHThresholdKa", parPrefix_nTuple).Data(),
                    "Track RICH threshold for kaons");
  
  Mfit.AddCategory(TString::Format("%s_Threshold_p", parPrefix_DataSet).Data(),
                   types, indices,
                    TString::Format("%s_RICHThresholdPr", parPrefix_nTuple).Data(),
                    "Track RICH threshold for protons");
                    
  Mfit.AddCategory(TString::Format("%s_Threshold_mu", parPrefix_DataSet).Data(),
                   types, indices,
                    TString::Format("%s_RICHThresholdMu", parPrefix_nTuple).Data(),
                    "Track RICH threshold for muons");
                    
  Mfit.AddCategory(TString::Format("%s_Threshold_e", parPrefix_DataSet).Data(),
                   types, indices,
                    TString::Format("%s_RICHThresholdEl", parPrefix_nTuple).Data(),
                    "Track RICH threshold for electrons");
                    
                    
  types.clear();
  indices.clear();
  types.push_back("Available");
  types.push_back("Unavailable");
  indices.push_back(1);
  indices.push_back(0);

  Mfit.AddCategory(TString::Format("%s_Rich_Info", parPrefix_DataSet).Data(),
                   types, indices, 
                   TString::Format("%s_hasRich", parPrefix_nTuple).Data(),
                   "Track has RICH Information");

  types.push_back("Unknown");
  indices.push_back(-1);

  Mfit.AddCategory(TString::Format("%s_Aerogel_Info", parPrefix_DataSet).Data(),
                   types, indices, 
                   TString::Format("%s_RICHAerogelUsed", parPrefix_nTuple).Data(),
                   "Track has Aerogel information");

  Mfit.AddCategory(TString::Format("%s_Rich1Gas_Info", parPrefix_DataSet).Data(),
                   types, indices, 
                   TString::Format("%s_RICH1GasUsed", parPrefix_nTuple).Data(),
                   "Track has RICH1 gas information");

  Mfit.AddCategory(TString::Format("%s_Rich2Gas_Info", parPrefix_DataSet).Data(),
                   types, indices, 
                   TString::Format("%s_RICH2GasUsed", parPrefix_nTuple).Data(),
                   "Track has RICH2 gas information");
  
}

void SetSpecVars_MUONCategories(RooPhysFit::RooDMassFitter& Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple)
{
  //======================================
  // Categories Associated with the MUONs
  //======================================
  std::vector<std::string> types;
  std::vector<Int_t> indices;
  
  types.push_back("Available");
  types.push_back("Unavailable");
  indices.push_back(1);
  indices.push_back(0);

  Mfit.AddCategory(TString::Format("%s_Muon_Info", parPrefix_DataSet).Data(),
                   types, indices, 
                   TString::Format("%s_hasMuon", parPrefix_nTuple).Data(),
                   "Track has muon information");
}

void SetSpecVars_MuonVars(RooPhysFit::RooDMassFitter& Mfit,
                          const char* parPrefix_DataSet,
                          const char* parPrefix_nTuple)
{
  //======================================
  // Muon PID Variables
  //======================================
  Mfit.AddSpectator(TString::Format("%s_hasMuon", parPrefix_DataSet).Data(),
                    -1.,
                    2.,
                    TString::Format("%s_hasMuon", parPrefix_nTuple).Data(),
                    "Track has muon information",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_InMuonAcc", parPrefix_DataSet).Data(), 
                    -1001.,
                    2., 
                    TString::Format("%s_InMuonAcc", parPrefix_nTuple).Data(),
                    "",
                    "In Muon Acceptance Flag",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_IsMuon", parPrefix_DataSet).Data(), 
                    -1001.,
                    2., 
                    TString::Format("%s_isMuon", parPrefix_nTuple).Data(),
                    "",
                    "Pass IsMuon Requirement Flag",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_IsMuonLoose", parPrefix_DataSet).Data(), 
                    -1001.,
                    2., 
                    TString::Format("%s_isMuonLoose", parPrefix_nTuple).Data(),
                    "",
                    "Pass IsMuonLoose Requirement Flag",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_nShared", parPrefix_DataSet).Data(), 
                    -2.,
                    500., 
                    TString::Format("%s_NShared", parPrefix_nTuple).Data(),
                    "",
                    "Number of tracks w/ shared MUON hits",
                    "Track variables");
}

