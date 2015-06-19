// $Id: $
// Include files 
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "TCut.h"
#include "RooWorkspace.h"
#include <list>

using namespace RooFit;

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <gangaID> <polarity> <calibdata_subID> "<<std::endl;
  std::cout << "\t<gangaID> is the ganga job ID "<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<calibdata_subID> is the subset of the calibration data used(0/1/2/..)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: ganga job ID
  // 2: Field oreientation (Up/Down)
  // 3: Calib. Data index
  if (argc != 4)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//

  gSystem->Load("libRooStats.so");

  TString fileRoot = "$DATADISK/gangadir_calib/workspace/powell/LocalXML/";
  
  //======================================================================
  // Ouput file from Test_EvtData.cpp
  //======================================================================
  TFile* f_Pi = new TFile(TString::Format(fileRoot+"%s/output/EvtData_18Momx4Etax4nTrk_CalPion_%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[3]).Data());
  if (!f_Pi) return 1;

  TFile* f_K = new TFile(TString::Format(fileRoot+"%s/output/EvtData_18Momx4Etax4nTrk_CalKaon_%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[3]).Data());
  if (!f_K) return 1;
  //======================================================================
  // Get RooWorkspace
  //======================================================================
  RooWorkspace* ws_Pi = (RooWorkspace*) f_Pi->Get("ws");
  ws_Pi->Print("v");
  RooWorkspace* ws_K = (RooWorkspace*) f_K->Get("ws");
  ws_K->Print("v");
  
  //======================================================================
  // Obtain RooDataSets
  //======================================================================
  RooDataSet* Kaon_Data = (RooDataSet*) ws_K->data("CalKaon");
  RooDataSet* Pion_Data = (RooDataSet*) ws_Pi->data("CalPion");

  //======================================================================
  // Import DataSets into TrackDataSet instances and declare weighting
  // variable:
  // - nsig_sw       : Raw calibration
  // - Wgt           : Bin weighted calibration 
  //======================================================================
  TrackDataSet* Pion_DataSet = new TrackDataSet("Calib. Pion",
                                                "",
                                                Pion_Data,
                                                *Pion_Data->get(),
                                                "Pi_P",
                                                "Pi_PT",
                                                "Pi_Eta",
                                                "Pi_CombDLLK",
                                                "Pi_CombDLLp",
                                                "",
                                                "Wgt");
  
  TrackDataSet* Kaon_DataSet = new TrackDataSet("Calib. Kaon",
                                                "",
                                                Kaon_Data,
                                                *Kaon_Data->get(),
                                                "K_P",
                                                "K_PT",
                                                "K_Eta",
                                                "K_CombDLLK",
                                                "K_CombDLLp",
                                                "",
                                                "Wgt");
  
  Pion_DataSet->Print("v");
  Kaon_DataSet->Print("v");

  cout<<Pion_DataSet->isWeighted()<<'\t'
      <<Kaon_DataSet->isWeighted()<<endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<TrackDataSet>* CalcKaon = new PerfCalculator<TrackDataSet>( Kaon_DataSet );
  PerfCalculator<TrackDataSet>* CalcPion = new PerfCalculator<TrackDataSet>( Pion_DataSet );
  
  //======================================================================
  // Define lists of PID cuts
  //======================================================================
  list<std::string> PIDCuts_Kaon;
  PIDCuts_Kaon.push_back("DLLK > 8.0");
  PIDCuts_Kaon.push_back("DLLK > 7.0");
  PIDCuts_Kaon.push_back("DLLK > 6.0");
  PIDCuts_Kaon.push_back("DLLK > 5.0");
  PIDCuts_Kaon.push_back("DLLK > 4.0");
  PIDCuts_Kaon.push_back("DLLK > 3.0");
  PIDCuts_Kaon.push_back("DLLK > 2.0");
  PIDCuts_Kaon.push_back("DLLK > 1.0");
  PIDCuts_Kaon.push_back("DLLK > 0.0");
  PIDCuts_Kaon.push_back("DLLK > -1.0");
  PIDCuts_Kaon.push_back("DLLK > -2.0");
  PIDCuts_Kaon.push_back("DLLK > -3.0");
  PIDCuts_Kaon.push_back("DLLK > -4.0");
  PIDCuts_Kaon.push_back("DLLK > -5.0");
  PIDCuts_Kaon.push_back("DLLK > -6.0");
  PIDCuts_Kaon.push_back("DLLK > -7.0");
  PIDCuts_Kaon.push_back("DLLK > -8.0");
  
  list<std::string> PIDCuts_Pion;
  PIDCuts_Pion.push_back("DLLK < 8.0");
  PIDCuts_Pion.push_back("DLLK < 7.0");
  PIDCuts_Pion.push_back("DLLK < 6.0");
  PIDCuts_Pion.push_back("DLLK < 5.0");
  PIDCuts_Pion.push_back("DLLK < 4.0");
  PIDCuts_Pion.push_back("DLLK < 3.0");
  PIDCuts_Pion.push_back("DLLK < 2.0");
  PIDCuts_Pion.push_back("DLLK < 1.0");
  PIDCuts_Pion.push_back("DLLK < 0.0");
  PIDCuts_Pion.push_back("DLLK < -1.0");
  PIDCuts_Pion.push_back("DLLK < -2.0");
  PIDCuts_Pion.push_back("DLLK < -3.0");
  PIDCuts_Pion.push_back("DLLK < -4.0");
  PIDCuts_Pion.push_back("DLLK < -5.0");
  PIDCuts_Pion.push_back("DLLK < -6.0");
  PIDCuts_Pion.push_back("DLLK < -7.0");
  PIDCuts_Pion.push_back("DLLK < -8.0");
  
  //======================================================================
  // Calculate mis-IDs
  //======================================================================
  const PIDRESULT::Container Pion_MisID = CalcPion->Perf(PIDCuts_Kaon,
                                                         kFALSE);
  
  const PIDRESULT::Container Kaon_MisID = CalcKaon->Perf(PIDCuts_Pion,
                                                         kFALSE);

  TGraphAsymmErrors* Pion_ID = CalcPion->Perf_Scan(PIDCuts_Pion,
                                                         kFALSE);
  Pion_ID->SetName("Pion ID Efficiency");
  
  TGraphAsymmErrors* Kaon_ID = CalcKaon->Perf_Scan(PIDCuts_Kaon,
                                                         kFALSE);
  Kaon_ID->SetName("Kaon ID Efficiency");
  
  
  //======================================================================
  // Generate ID vs mis-ID curves
  //======================================================================
  TGraphAsymmErrors* KaonSel_DLLScan = CalcKaon->Perf_Scan_ToFile(Pion_MisID,
                                                                  PIDCuts_Kaon,
                                                                  TString::Format("%s_k_%s.txt", 
                                                                                  argv[2],           
                                                                                  argv[3]).Data(),
                                                                  kFALSE);
  KaonSel_DLLScan->SetName("KaonSel_DLLScan");
  KaonSel_DLLScan->GetXaxis()->SetTitle("Kaon ID Efficiency");
  KaonSel_DLLScan->GetYaxis()->SetTitle("Pion Mis-ID Efficiency");

  TGraphAsymmErrors* PionSel_DLLScan = CalcPion->Perf_Scan_ToFile(Kaon_MisID,
                                                                  PIDCuts_Pion,
                                                                  TString::Format("%s_pi_%s.txt",
                                                                                  argv[2],           
                                                                                  argv[3]).Data(),
                                                                  kFALSE);
  PionSel_DLLScan->SetName("PionSel_DLLScan");
  PionSel_DLLScan->GetXaxis()->SetTitle("Pion ID Efficiency");
  PionSel_DLLScan->GetYaxis()->SetTitle("Kaon Mis-ID Efficiency");

  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile(TString::Format("EvtData_PerfCurves_%s_%s.root",
                                            argv[2], 
                                            argv[3]).Data(), "RECREATE");
  
  Kaon_ID->Write();
  Pion_ID->Write();
  KaonSel_DLLScan->Write();
  PionSel_DLLScan->Write();
  myfile->Close();

  //======================================================================
  // Clean up
  //======================================================================
  
  delete KaonSel_DLLScan;
  delete PionSel_DLLScan;
  delete Kaon_ID;
  delete Pion_ID;
  delete myfile;
  
  delete CalcKaon; 
  delete CalcPion;
  
  delete Kaon_DataSet;
  delete Pion_DataSet;
  
  delete ws_Pi;
  delete ws_K;
  delete f_Pi;
  delete f_K;
  
  return 0;
  
}

