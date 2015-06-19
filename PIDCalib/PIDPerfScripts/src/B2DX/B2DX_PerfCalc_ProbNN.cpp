// $Id: $
// Include files 
#include "PIDPerfTools/RICHTrackDataSet.h"
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
#include <vector>
#include <boost/lexical_cast.hpp>
#include <iomanip>

using namespace RooFit;

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <gangaID> <polarity> <d0_finalstate> <calibdata_subID> "<<std::endl;
  std::cout << "\t<gangaID> is the ganga job ID "<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<d0_finalstate> is one of (kpi/k3pi/kk)"<<std::endl;
  std::cout << "\t<calibdata_subID> is the subset of the calibration data used(K/Pi)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: ganag job ID
  // 2: Field oreientation (Up/Down)
  // 3: D0 Final State (kpi,k3pi,kk)
  // 4: Calib. Data index
  if (argc != 5)
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
  TFile* f_Pi = new TFile(TString::Format(fileRoot+"%s/output/EvtData_18Momx4Etax4nTrk_CalPion_%s_%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[3],
                                          argv[4]).Data());
  if (!f_Pi) return 1;

  TFile* f_K = new TFile(TString::Format(fileRoot+"%s/output/EvtData_18Momx4Etax4nTrk_CalKaon_%s_%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[3],
                                          argv[4]).Data());
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
  RICHTrackDataSet* Pion_DataSet = new RICHTrackDataSet("Calib. Pion",
                                                        "",
                                                        Pion_Data,
                                                        *Pion_Data->get(),
                                                        "Pi_P",
                                                        "Pi_PT",
                                                        "Pi_Eta",
                                                        "nTracks",
                                                        "Pi_CombDLLK",
                                                        "Pi_CombDLLp",
                                                        "Pi_ProbNNK",
                                                        "Pi_ProbNNpi",
                                                        "Pi_ProbNNp",
                                                        "",
                                                        "Wgt");
  
  RICHTrackDataSet* Kaon_DataSet = new RICHTrackDataSet("Calib. Kaon",
                                                        "",
                                                        Kaon_Data,
                                                        *Kaon_Data->get(),
                                                        "K_P",
                                                        "K_PT",
                                                        "K_Eta",
                                                        "nTracks",
                                                        "K_CombDLLK",
                                                        "K_CombDLLp",
                                                        "K_ProbNNK",
                                                        "K_ProbNNpi",
                                                        "K_ProbNNp",
                                                        "",
                                                        "Wgt");
  
  Pion_DataSet->Print("v");
  Kaon_DataSet->Print("v");

  cout<<Pion_DataSet->isWeighted()<<'\t'
      <<Kaon_DataSet->isWeighted()<<endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<RICHTrackDataSet>* CalcKaon = new PerfCalculator<RICHTrackDataSet>( Kaon_DataSet );
  PerfCalculator<RICHTrackDataSet>* CalcPion = new PerfCalculator<RICHTrackDataSet>( Pion_DataSet );
  
  //======================================================================
  // Define lists of PID cuts
  //======================================================================
  list<std::string> PIDCuts_Kaon;
  list<std::string> PIDCuts_Pion;
  cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
  cout<<left
      <<std::setw(20)<<"PIDCuts_Kaon"
      <<std::setw(20)<<"PIDCuts_Pion"<<endl;
  cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
  for(int i=1; i<3; ++i)
  {
    PIDCuts_Kaon.push_back(      (TString::Format("ProbNNK > %.3f",i*0.01 )).Data());
    PIDCuts_Pion.push_back(      (TString::Format("ProbNNpi > %.3f",i*0.01)).Data());
    cout<<left
        <<std::setw(20)<<PIDCuts_Kaon.back()
        <<std::setw(20)<<PIDCuts_Pion.back()<<endl;
  }
  for(int i=1; i<3; ++i)
  {
    PIDCuts_Kaon.push_back(      (TString::Format("ProbNNK > %.3f",i*0.025 )).Data());
    PIDCuts_Pion.push_back(      (TString::Format("ProbNNpi > %.3f",i*0.025)).Data());
    cout<<left
        <<std::setw(20)<<PIDCuts_Kaon.back()
        <<std::setw(20)<<PIDCuts_Pion.back()<<endl;
  }
  for(int i=1; i<10; ++i)
  {
    PIDCuts_Kaon.push_back(      (TString::Format("ProbNNK > %.2f",i*0.1 )).Data());
    PIDCuts_Pion.push_back(      (TString::Format("ProbNNpi > %.2f",i*0.1)).Data());
    cout<<left
        <<std::setw(20)<<PIDCuts_Kaon.back()
        <<std::setw(20)<<PIDCuts_Pion.back()<<endl;
  }
  cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
  
  //======================================================================
  // Calculate mis-IDs
  //======================================================================
  const PIDRESULT::Container Pion_MisID = CalcPion->Perf(PIDCuts_Kaon,
                                                         kFALSE);
  
  const PIDRESULT::Container Kaon_MisID = CalcKaon->Perf(PIDCuts_Pion,
                                                         kFALSE);
  
  //======================================================================
  // Generate ID vs mis-ID curves
  //======================================================================
  TGraphAsymmErrors* KaonSel_DLLScan = CalcKaon->Perf_Scan_ToFile(Pion_MisID,
                                                                  PIDCuts_Kaon,
                                                                  TString::Format("%s_%s_k_%s.txt",
                                                                                  argv[3], 
                                                                                  argv[2],           
                                                                                  argv[4]).Data(),
                                                                  kFALSE);
  KaonSel_DLLScan->SetName("KaonSel_DLLScan");
  KaonSel_DLLScan->GetXaxis()->SetTitle("Kaon ID Efficiency");
  KaonSel_DLLScan->GetYaxis()->SetTitle("Pion Mis-ID Efficiency");

  TGraphAsymmErrors* PionSel_DLLScan = CalcPion->Perf_Scan_ToFile(Kaon_MisID,
                                                                  PIDCuts_Pion,
                                                                  TString::Format("%s_%s_pi_%s.txt",
                                                                                  argv[3], 
                                                                                  argv[2],           
                                                                                  argv[4]).Data(),
                                                                  kFALSE);
  PionSel_DLLScan->SetName("PionSel_DLLScan");
  PionSel_DLLScan->GetXaxis()->SetTitle("Pion ID Efficiency");
  PionSel_DLLScan->GetYaxis()->SetTitle("Kaon Mis-ID Efficiency");

  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile(TString::Format("EvtData_PerfCurves_%s_%s_%s.root",
                                            argv[3], 
                                            argv[2], 
                                            argv[4]).Data(), "RECREATE");
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
  
  delete ws_Pi;
  delete ws_K;
  delete f_Pi;
  delete f_K;
  
  return 0;
  
}

