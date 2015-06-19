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

int main(void)
{
  gSystem->Load("libRooStats.so");
  
  //======================================================================
  // Ouput file from Test_EvtData.cpp
  //======================================================================
  TFile* f = new TFile("EvtMCKaon_32Momx4Etax4nTrk.root");
  if (!f) return 1;

  //======================================================================
  // Get RooWorkspace
  //======================================================================
  RooWorkspace* ws = (RooWorkspace*) f->Get("ws");
  ws->Print("v");
  
  //======================================================================
  // Obtain RooDataSets
  //======================================================================
  RooDataSet* Kaon_Data = (RooDataSet*) ws->data("CalKaon");
  RooDataSet* Pion_Data = (RooDataSet*) ws->data("CalPion");

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
                                                "nsig_sw");
  
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
                                                "nsig_sw");
  
  Pion_DataSet->Print("v");
  Kaon_DataSet->Print("v");

  std::cout<<Pion_DataSet->isWeighted()<<'\t'
           <<Kaon_DataSet->isWeighted()<<std::endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<TrackDataSet>* CalcKaon = new PerfCalculator<TrackDataSet>( Kaon_DataSet );
  PerfCalculator<TrackDataSet>* CalcPion = new PerfCalculator<TrackDataSet>( Pion_DataSet );
  
  //======================================================================
  // Define lists of PID cuts
  //======================================================================
  std::list<std::string> PIDCuts_Kaon;
  PIDCuts_Kaon.push_back("DLLK > 8.0");
  PIDCuts_Kaon.push_back("DLLK > 6.0");
  PIDCuts_Kaon.push_back("DLLK > 4.0");
  PIDCuts_Kaon.push_back("DLLK > 2.0");
  PIDCuts_Kaon.push_back("DLLK > 0.0");
  PIDCuts_Kaon.push_back("DLLK > -2.0");
  PIDCuts_Kaon.push_back("DLLK > -4.0");
  PIDCuts_Kaon.push_back("DLLK > -6.0");
  PIDCuts_Kaon.push_back("DLLK > -8.0");
  
  std::list<std::string> PIDCuts_Pion;
  PIDCuts_Pion.push_back("DLLK < 8.0");
  PIDCuts_Pion.push_back("DLLK < 6.0");
  PIDCuts_Pion.push_back("DLLK < 4.0");
  PIDCuts_Pion.push_back("DLLK < 2.0");
  PIDCuts_Pion.push_back("DLLK < 0.0");
  PIDCuts_Pion.push_back("DLLK < -2.0");
  PIDCuts_Pion.push_back("DLLK < -4.0");
  PIDCuts_Pion.push_back("DLLK < -6.0");
  PIDCuts_Pion.push_back("DLLK < -8.0");
  
  //======================================================================
  // Calculate mis-IDs
  //======================================================================
  const PIDRESULT::Container Pion_MisID = CalcPion->Perf(PIDCuts_Kaon,
                                                         kTRUE);
  
  const PIDRESULT::Container Kaon_MisID = CalcKaon->Perf(PIDCuts_Pion,
                                                         kTRUE);
  
  //======================================================================
  // Generate ID vs mis-ID curves
  //======================================================================
  TGraphAsymmErrors* KaonSel_DLLScan = CalcKaon->Perf_Scan(Pion_MisID,
                                                           PIDCuts_Kaon,
                                                           kTRUE);
  KaonSel_DLLScan->SetName("KaonSel_DLLScan");
  KaonSel_DLLScan->GetXaxis()->SetTitle("Kaon ID Efficiency");
  KaonSel_DLLScan->GetYaxis()->SetTitle("Pion Mis-ID Efficiency");

  TGraphAsymmErrors* PionSel_DLLScan = CalcPion->Perf_Scan(Kaon_MisID,
                                                           PIDCuts_Pion,
                                                           kTRUE);
  PionSel_DLLScan->SetName("PionSel_DLLScan");
  PionSel_DLLScan->GetXaxis()->SetTitle("Pion ID Efficiency");
  PionSel_DLLScan->GetYaxis()->SetTitle("Kaon Mis-ID Efficiency");

  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile("EvtData_PerfCurves_Raw.root", "RECREATE");
  KaonSel_DLLScan->Write();
  PionSel_DLLScan->Write();
  myfile->Close();

  //======================================================================
  // Clean up
  //======================================================================
  delete KaonSel_DLLScan;
  delete PionSel_DLLScan;
  delete myfile;
  
  delete CalcKaon; 
  delete CalcPion;
  
  delete Kaon_DataSet;
  delete Pion_DataSet;
  
  delete ws;
  delete f;
  
  return 0;
  
}

