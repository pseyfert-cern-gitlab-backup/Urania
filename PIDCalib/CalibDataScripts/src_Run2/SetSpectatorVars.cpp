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

  Mfit.AddSpectator("nSPDHits",
                    0.,
                    1000.,
                    "nSPDhits",
                    "",
                    "Number of hits in the SPD",
                    "Event variables");

  Mfit.AddSpectator("runNumber",
                    0,
                    999999,
                    "runNumber",
                    "",
                    "Run Number",
                    "Event variables");
   Mfit.AddSpectator("nRich1Hits",
                    0,
                    10000,
                    "nRich1Hits",
                    "",
                    "No. RICH1 Pixel Hits",
                    "Event variables");
  
  Mfit.AddSpectator("nRich2Hits",
                    0,
                    10000,
                    "nRich2Hits",
                    "",
                    "No. RICH2 Pixel Hits",
                    "Event variables");
 Mfit.AddSpectator("nPVs",              // Name in DataSet
                    0,                  // Min value
                    20,                 // Max value
                    "nPVs",              // Branch name
                    "",                 // Units
                    "No. PV in Event",  // Title
                    "Event variables"); // NamedSet
}




void SetSpecVars_ElectronVars(RooPhysFit::RooDMassFitter& Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple)
{
  //======================================
  // Electron Variables
  //======================================
  Mfit.AddSpectator(TString::Format("%s_HasBremAdded", parPrefix_DataSet).Data(), 
                    0,
                    10, 
                    TString::Format("%s_HasBremAdded", parPrefix_nTuple).Data(),
                    "",
                    "Were bremsstrahlung photons added to electron",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_hasCalo", parPrefix_DataSet).Data(),
                    -1,
                    2,
                    TString::Format("%s_hasCalo", parPrefix_nTuple).Data(),
                    "",
                    "Does this particle have CALO clusters",
                    "Track variables");
 
  Mfit.AddSpectator(TString::Format("%s_CaloRegion", parPrefix_DataSet).Data(), 
                    0,
                    10, 
                    TString::Format("%s_CaloRegion", parPrefix_nTuple).Data(),
                    "",
                    "Region of calo electron hit (0=Unknown, 1=Beam pipe, 2=Inner, 3=Middle, 4=Outer)",
                    "Track variables");
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


void SetSpecVars_StdDLLs2015(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - Std DLLs
  //======================================




  Mfit.AddSpectator(TString::Format("%s_Tesla_CombDLLK", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDK", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(K - #pi)",
                    "Track variables");

Mfit.AddSpectator(TString::Format("%s_CombDLLK", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_Brunel_PIDK", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(K - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_Tesla_CombDLLp", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDp", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(p - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_CombDLLp", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_Brunel_PIDp", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(p - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Tesla_CombDLLmu", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDmu", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(#mu - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_CombDLLmu", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_Brunel_PIDmu", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(#mu - #pi)",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_Tesla_CombDLLe", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_PIDe", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(e - #pi)",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_CombDLLe", parPrefix_DataSet).Data(), 
                    -1001.,
                    150., 
                    TString::Format("%s_Brunel_PIDe", parPrefix_nTuple).Data(),
                    "",
                    "Comb. DLL(e - #pi)",
                    "Track variables");





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
  Mfit.AddSpectator(TString::Format("%s_V1ProbNNK", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V1ProbNNk", parPrefix_nTuple).Data(),
                    "",
                    "ANN prob. Kv1",   
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_V1ProbNNpi", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V1ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv1", 
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V1ProbNNp", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V1ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv1", 
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_V1ProbNNmu", parPrefix_DataSet).Data(),
                    -3, 
                    3.,
                    TString::Format("%s_Brunel_V1ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv1",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_V1ProbNNe", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V1ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev1","Track variables");


  Mfit.AddSpectator(TString::Format("%s_Tesla_V1ProbNNK", parPrefix_DataSet).Data(),
                    -3.,
                    3.,   
                    TString::Format("%s_V1ProbNNk", parPrefix_nTuple).Data(),
                    "",
                    "ANN prob. Kv1",
                    "Track variables");   
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V1ProbNNpi", parPrefix_DataSet).Data(),
                    -3.,
                    3.,   
                    TString::Format("%s_V1ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv1",
                    "Track variables");   
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V1ProbNNp", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V1ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv1",
                    "Track variables");   
  
  Mfit.AddSpectator(TString::Format("%s_Tesla_V1ProbNNmu", parPrefix_DataSet).Data(),
                    -3,
                    3., 
                    TString::Format("%s_V1ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv1",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V1ProbNNe", parPrefix_DataSet).Data(),
                    -3.,
                    3., 
                    TString::Format("%s_V1ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev1","Track variables");



/*
  Mfit.AddSpectator(TString::Format("%s_V2ProbNNK", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V2ProbNNk", parPrefix_nTuple).Data(),
                    "",
		    "ANN prob. Kv2",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V2ProbNNpi", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V2ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv2",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V2ProbNNp", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V2ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv2",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_V2ProbNNmu", parPrefix_DataSet).Data(), 
                    -3,
                    3., 
                    TString::Format("%s_Brunel_V2ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv2",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V2ProbNNe", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V2ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev2",
                    "Track variables");




  Mfit.AddSpectator(TString::Format("%s_Tesla_V2ProbNNK", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V2ProbNNk", parPrefix_nTuple).Data(),
                    "",
                    "ANN prob. Kv2",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V2ProbNNpi", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V2ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv2",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V2ProbNNp", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V2ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv2",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V2ProbNNmu", parPrefix_DataSet).Data(),
                    -3,
                    3.,
                    TString::Format("%s_V2ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv2",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V2ProbNNe", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V2ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev2","Track variables");




 Mfit.AddSpectator(TString::Format("%s_V3ProbNNK", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V3ProbNNk", parPrefix_nTuple).Data(),
                    "",
                     "ANN Prob. Kv3",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V3ProbNNpi", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V3ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv3",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V3ProbNNp", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V3ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv3",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_V3ProbNNmu", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V3ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv3",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V3ProbNNe", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_Brunel_V3ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev3",
                    "Track variables");


   Mfit.AddSpectator(TString::Format("%s_Tesla_V3ProbNNK", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V3ProbNNk", parPrefix_nTuple).Data(),
                    "",
                    "ANN prob. Kv3",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V3ProbNNpi", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V3ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv3",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V3ProbNNp", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V3ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv3",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V3ProbNNmu", parPrefix_DataSet).Data(),
                    -3,
                    3.,
                    TString::Format("%s_V3ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv3",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V3ProbNNe", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V3ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev3","Track variables");

*/


   Mfit.AddSpectator(TString::Format("%s_V4ProbNNK", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V4ProbNNk", parPrefix_nTuple).Data(),
                    "",
                    "ANN prob. Kv4",   
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_V4ProbNNpi", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V4ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv4", 
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V4ProbNNp", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V4ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv4", 
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_V4ProbNNmu", parPrefix_DataSet).Data(),
                    -3, 
                    3.,
                    TString::Format("%s_Brunel_V4ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv4",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_V4ProbNNe", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V4ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev4", "Track variables");


 Mfit.AddSpectator(TString::Format("%s_Tesla_V4ProbNNK", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V4ProbNNk", parPrefix_nTuple).Data(),
                    "",
                    "ANN prob. Kv4",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V4ProbNNpi", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V4ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv4",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V4ProbNNp", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V4ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv4",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V4ProbNNmu", parPrefix_DataSet).Data(),
                    -3,
                    3.,
                    TString::Format("%s_V4ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv4",
                    "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_Tesla_V4ProbNNe", parPrefix_DataSet).Data(),
                    -3.,
                    3.,
                    TString::Format("%s_V4ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev4","Track variables");




Mfit.AddSpectator(TString::Format("%s_V1ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V1ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv1",
                    "Track variables");

/*
Mfit.AddSpectator(TString::Format("%s_V2ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V2ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv2",
                    "Track variables");
Mfit.AddSpectator(TString::Format("%s_V3ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V3ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv3",
                    "Track variables");
*/
Mfit.AddSpectator(TString::Format("%s_V4ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_Brunel_V4ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv4",
                    "Track variables");


Mfit.AddSpectator(TString::Format("%s_Tesla_V1ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_V1ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv1",
                    "Track variables");
  
/*                       
Mfit.AddSpectator(TString::Format("%s_Tesla_V2ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_V2ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv2",
                    "Track variables");
Mfit.AddSpectator(TString::Format("%s_Tesla_V3ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_V3ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv3",
                    "Track variables");
*/
Mfit.AddSpectator(TString::Format("%s_Tesla_V4ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_V4ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv4",
                    "Track variables");

}


void SetSpecVars_ANNVars2012(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple)
{
  //======================================
  // Track PID Variables - ANN Probs
  //======================================
  Mfit.AddSpectator(TString::Format("%s_V2ProbNNK", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V2ProbNNk", parPrefix_nTuple).Data(),
                    "",
		    "ANN prob. Kv2",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V2ProbNNpi", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V2ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv2",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V2ProbNNp", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V2ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv2",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_V2ProbNNmu", parPrefix_DataSet).Data(), 
                    -3,
                    3., 
                    TString::Format("%s_V2ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv2",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V2ProbNNe", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V2ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev2",
                    "Track variables");


 Mfit.AddSpectator(TString::Format("%s_V3ProbNNK", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V3ProbNNk", parPrefix_nTuple).Data(),
                    "",
                     "ANN Prob. Kv3",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V3ProbNNpi", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V3ProbNNpi", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #piv3",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V3ProbNNp", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V3ProbNNp", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. pv3",
                    "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_V3ProbNNmu", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V3ProbNNmu", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. #muv3",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_V3ProbNNe", parPrefix_DataSet).Data(), 
                    -3.,
                    3., 
                    TString::Format("%s_V3ProbNNe", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ev3",
                    "Track variables");
Mfit.AddSpectator(TString::Format("%s_V2ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_V2ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv2",
                    "Track variables");
Mfit.AddSpectator(TString::Format("%s_V3ProbNNghost", parPrefix_DataSet).Data()\
,
                    -3.,
                    3.,
                    TString::Format("%s_V3ProbNNghost", parPrefix_nTuple).Data(),
                    "",
                    "ANN Prob. ghostv3",
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

 Mfit.AddSpectator(TString::Format("%s_trackcharge", parPrefix_DataSet).Data(), 
                    -2, 
                    2, 
                    TString::Format("%s_trackcharge", parPrefix_nTuple).Data(),
                    "",
                    "Track charge",
                    "Track variables");
}


void SetSpecVars_KinematicVars2015(RooPhysFit::RooDMassFitter& Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple)
{
  //======================================
  // Track Kinematic Variables
  //======================================


 Mfit.AddSpectator(TString::Format("%s_trackcharge", parPrefix_DataSet).Data(), 
                    -2, 
                    2, 
                    TString::Format("%s_trackcharge", parPrefix_nTuple).Data(),
                    "",
                    "Track charge",
                    "Track variables");
  Mfit.AddSpectator(TString::Format("%s_Tesla_P", parPrefix_DataSet).Data(), 
                    0, 
                    500000, 
                    TString::Format("%s_P", parPrefix_nTuple).Data(),
                    "MeV/c",
                    "Track Momentum",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Tesla_PT", parPrefix_DataSet).Data(), 
                    0, 
                    200000, 
                    TString::Format("%s_PT", parPrefix_nTuple).Data(),
                    "MeV/c",
                    "Transverse Momentum",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Tesla_Eta", parPrefix_DataSet).Data(), 
                    1, 
                    6, 
                    TString::Format("%s_ETA", parPrefix_nTuple).Data(),
                    "",
                    "Psuedo Rapidity",
                    "Track variables");
  Mfit.AddSpectator(TString::Format("%s_Tesla_Phi", parPrefix_DataSet).Data(), 
                    -1.*pi, 
                    pi, 
                    TString::Format("%s_PHI", parPrefix_nTuple).Data(),
                    "",
                    "Track phi",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_P", parPrefix_DataSet).Data(), 
                    0, 
                    500000, 
                    TString::Format("%s_Brunel_P", parPrefix_nTuple).Data(),
                    "MeV/c",
                    "Track Momentum",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_PT", parPrefix_DataSet).Data(), 
                    0, 
                    200000, 
                    TString::Format("%s_Brunel_PT", parPrefix_nTuple).Data(),
                    "MeV/c",
                    "Transverse Momentum",
                    "Track variables");

  Mfit.AddSpectator(TString::Format("%s_Eta", parPrefix_DataSet).Data(), 
                    1, 
                    6, 
                    TString::Format("%s_Brunel_ETA", parPrefix_nTuple).Data(),
                    "",
                    "Psuedo Rapidity",
                    "Track variables");
  Mfit.AddSpectator(TString::Format("%s_Phi", parPrefix_DataSet).Data(), 
                    -1.*pi, 
                    pi, 
                    TString::Format("%s_Brunel_PHI", parPrefix_nTuple).Data(),
                    "",
                    "Track phi",
                    "Track variables");
}


void SetSpecVars_RICHVars(RooPhysFit::RooDMassFitter& Mfit,
                          const char* parPrefix_DataSet,
                          const char* parPrefix_nTuple)
{
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_pi", parPrefix_DataSet).Data(),
                   -2.,
                   2.,
		    TString::Format("%s_RICHThresholdPi", parPrefix_nTuple).Data(),"",
                   "Track RICH threshold for pions",
                   "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_K", parPrefix_DataSet).Data(),
                   -2.,
                   2.,
		    TString::Format("%s_RICHThresholdKa", parPrefix_nTuple).Data(),"",
                   "Track RICH threshold for kaons",
                   "Track variables");
  
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_p", parPrefix_DataSet).Data(),
                   -2.,
                   2., 
		    TString::Format("%s_RICHThresholdPr", parPrefix_nTuple).Data(),"",
                   "Track RICH threshold for protons",
                   "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_mu", parPrefix_DataSet).Data(),
                   -2., 
                   2.,
		    TString::Format("%s_RICHThresholdMu", parPrefix_nTuple).Data(),"",
                   "Track RICH threshold for muons",
                   "Track variables");
                    
  Mfit.AddSpectator(TString::Format("%s_RICHThreshold_e", parPrefix_DataSet).Data(),
                   -2., 
                   2.,
		    TString::Format("%s_RICHThresholdEl", parPrefix_nTuple).Data(),"",
                   "Track RICH threshold for electrons",
                   "Track variables");
                   
  Mfit.AddSpectator(TString::Format("%s_RICHAerogelUsed", parPrefix_DataSet).Data(),
                   -2.,
                   2., 
		    TString::Format("%s_RICHAerogelUsed", parPrefix_nTuple).Data(),"",
                   "Track has Aerogel information",
                   "Track variables");

  Mfit.AddSpectator(TString::Format("%s_RICH1GasUsed", parPrefix_DataSet).Data(),
                   -2., 
                   2., 
		    TString::Format("%s_RICH1GasUsed", parPrefix_nTuple).Data(),"",
                   "Track has RICH1 gas information",
                   "Track variables");

  Mfit.AddSpectator(TString::Format("%s_RICH2GasUsed", parPrefix_DataSet).Data(),
                   -2., 
                   2., 
		    TString::Format("%s_RICH2GasUsed", parPrefix_nTuple).Data(),"",
                   "Track has RICH2 gas information",
                   "Track variables");
                   
  Mfit.AddSpectator(TString::Format("%s_hasRich", parPrefix_DataSet).Data(),
                    -1.,
                    2.,
                    TString::Format("%s_hasRich", parPrefix_nTuple).Data(),"",
                    "Track has RICH information",
                    "Track variables");
}


 


void SetSpecVars_MuonTisTosTagged(RooPhysFit::RooDMassFitter& Mfit,
				  const char* parPrefix_DataSet,
				  const char* parPrefix_nTuple)
{
 //======================================
  // Muon TIS TOS Tagged variables
  //======================================
const char* opar;
  if(strcmp(parPrefix_nTuple,"mup")==0){
    opar="mum";}
  else{opar="mup";}

  std::cout<< parPrefix_nTuple<< " " <<opar<< " MUON DEBUG"<<std::endl;

 Mfit.AddSpectator(TString::Format("%s_Probe_TIS", parPrefix_DataSet).Data(),
                    -1.,
                    2.,
		   TString::Format("%s_MuonUnbiasedHLT1", parPrefix_nTuple).Data()," ",
                    "Probe tracks satistfies the TIS criteria",
                    "Track variables");

 Mfit.AddSpectator(TString::Format("%s_Tag_TOS", parPrefix_DataSet).Data(),
                   -1.,
                    2.,
 		   TString::Format("%s_MuonTOS", opar)," ",
                    "Tag track (ie the other one) satistfied the TOS criteria",
                    "Track variables");
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
                    "",
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
  /*
   Mfit.AddSpectator(TString::Format("%s_IsMuonTight", parPrefix_DataSet).Data(), 
                    -1001.,
                    2., 
                    TString::Format("%s_isMuonTight", parPrefix_nTuple).Data(),
                    "",
                    "Pass IsMuonTight Requirement Flag",
                   "Track variables");
  */
  Mfit.AddSpectator(TString::Format("%s_nShared", parPrefix_DataSet).Data(), 
                    -2.,
                    500., 
                    TString::Format("%s_NShared", parPrefix_nTuple).Data(),
                    "",
                    "Number of tracks w/ shared MUON hits",
                    "Track variables");
}

void SetSpecVars_KPiMuonUNB(RooPhysFit::RooDMassFitter& Mfit,
                                  const char* parPrefix_DataSet,
                                  const char* parPrefix_nTuple)
{
 //======================================                                       
  // Muon TIS TOS Tagged variables on kaons and pions                                             
  //======================================                                      

 Mfit.AddSpectator(TString::Format("%s_Unbias_HLT1", parPrefix_DataSet).Data(),
                    -1.,
                    2.,
		   TString::Format("%s_MuonUnbiasedHLT1", parPrefix_nTuple).Data()," ",
                    "Track satistfies the TIS at HLT1 ",
                    "Track variables");

 // Mfit.AddSpectator(TString::Format("%s_", parPrefix_DataSet).Data(),
 //                    -1.,
 //                    2.,
 //		   TString::Format("%s_UT2_MuonTisTagged", parPrefix_nTuple).Data()," ",
 //                    "Probe tracks satistfies the TIS criteria and HLt1+2",
 //                  "Track variables");

}


void SetSpecVars_PMuonUNB(RooPhysFit::RooDMassFitter& Mfit,
                                  const char* parPrefix_DataSet,
                                  const char* parPrefix_nTuple)
{
 //======================================                                       
  // Muon TIS TOS Tagged variables on protons                                           
  //======================================                                      

 Mfit.AddSpectator(TString::Format("%s_Unbias_HLT1", parPrefix_DataSet).Data(),
                    -1.,
                    2.,
		   TString::Format("%s_MuonUnbiasedHLT1", parPrefix_nTuple).Data()," ",
                    "Probe tracks satistfies the TIS criteria",
                    "Track variables");

}

