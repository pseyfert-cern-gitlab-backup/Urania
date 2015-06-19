// $Id: $
// Include files 
#include "PIDPerfTools/MUONTrackDataSet.h"
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
            << " <reco_version> <polarity> <dataset_index>"<<std::endl;
  std::cout << "\t<reco_version> is the reconstruction version used to process the data (10/11/12)"<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<dataset_index> is one of (0/1/2/..)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Reco Version (10,11,12..)
  // 2: Field Orientation (Up/Down)
  // 3: Calib. Data index
  if (argc != 4)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  gSystem->Load("libRooStats.so");
  
    string StripVersion;
  if(strcmp(argv[1],"10")==0)
    StripVersion = "13b";
  else if(strcmp(argv[1],"11")==0)
    StripVersion = "15";
  else if(strcmp(argv[1],"12")==0)
    StripVersion = "17";
  else
    return EXIT_FAILURE;

  //======================================================================
  // Ouput file from Test_EvtData.cpp
  //======================================================================
    TFile* f_Pi = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_Pi_Mag%s_Strip%s_%s.root",
                                             argv[1],
                                             argv[2],
                                             argv[2],
                                             StripVersion.c_str(),
                                             argv[3])).Data()
                            );
  if (!f_Pi) return 1;
  
  TFile* f_K = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_K_Mag%s_Strip%s_%s.root",
                                            argv[1],
                                            argv[2],
                                            argv[2],
                                            StripVersion.c_str(),
                                            argv[3])).Data()                                              
                           );
  if (!f_K) return 1;

  //======================================================================
  // Get RooWorkspace
  //======================================================================
  RooWorkspace* ws_Pi = (RooWorkspace*) f_Pi->Get("RSDStCalib");
  ws_Pi->Print("v");
  RooWorkspace* ws_K = (RooWorkspace*) f_K->Get("RSDStCalib");
  ws_K->Print("v");
  
  //======================================================================
  // Get DataSets
  //======================================================================
  RooDataSet* Pion_Data = (RooDataSet*)ws_Pi->data( "data" );
  RooDataSet* Kaon_Data = (RooDataSet*)ws_K->data( "data" );
  
  MUONTrackDataSet* Pion_DataSet = new MUONTrackDataSet("Calib. Pion",
                                                        "",
                                                        Pion_Data,
                                                        *Pion_Data->get(),
                                                        "Pi_P",
                                                        "Pi_PT",
                                                        "Pi_Eta",
                                                        "nTracks",
                                                        "Pi_CombDLLK",
                                                        "Pi_CombDLLp",
                                                        "Pi_CombDLLmu",
                                                        "Pi_IsMuon",
                                                        "Pi_IsMuonLoose",
                                                        "Pi_nShared"
                                                        "",
                                                        "nsig_sw");
  
  MUONTrackDataSet* Kaon_DataSet = new MUONTrackDataSet("Calib. Kaon",
                                                        "",
                                                        Kaon_Data,
                                                        *Kaon_Data->get(),
                                                        "K_P",
                                                        "K_PT",
                                                        "K_Eta",
                                                        "nTracks",
                                                        "K_CombDLLK",
                                                        "K_CombDLLp",
                                                        "K_CombDLLmu",
                                                        "K_IsMuon",
                                                        "K_IsMuonLoose",
                                                        "K_nShared",
                                                        "",
                                                        "nsig_sw");
  
  Pion_DataSet->Print("v");
  Kaon_DataSet->Print("v");

  cout<<Pion_DataSet->isWeighted()<<'\t'
      <<Kaon_DataSet->isWeighted()<<endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<MUONTrackDataSet>* CalcKaon = new PerfCalculator<MUONTrackDataSet>( Kaon_DataSet );
  PerfCalculator<MUONTrackDataSet>* CalcPion = new PerfCalculator<MUONTrackDataSet>( Pion_DataSet );
   
  //======================================================================
  // Define lists of PID cuts 
  //======================================================================
  list<std::string> PIDCuts_Kaon;
  list<std::string> PIDCuts_Pion;
  cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
  cout<<left
      <<std::setw(20)<<"PIDCuts_Kaon"
      <<std::setw(20)<<"PIDCuts_Pion"
      <<endl;
  cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
  for(int i=-12; i<13; ++i)
  {
    PIDCuts_Kaon.push_back( ( TString::Format("DLLmu > %s",
                                             (boost::lexical_cast<string>(i)).c_str()) ).Data() );
    PIDCuts_Pion.push_back( ( TString::Format("DLLmu < %s",
                                             (boost::lexical_cast<string>(i)).c_str()) ).Data());
    cout<<left
        <<std::setw(20)<<PIDCuts_Kaon.back()
        <<std::setw(20)<<PIDCuts_Pion.back()<<endl;
  }
  cout<<setfill('-')<<setw(40)<<"-"<<setfill(' ')<<endl;
  
  //======================================================================
  // Declare TFile for Saving Graphs
  //======================================================================
  TFile *myfile = new TFile("Perf_DLLK_MC.root", "RECREATE");
  
  //======================================================================
  // Perform ID Scans
  //======================================================================
  TGraphAsymmErrors* DLLK_ScanK = CalcKaon->Perf_Scan(PIDCuts_Kaon,
                                                      kFALSE);
  DLLK_ScanK->SetName("DLLK_Kaon");
  
  TGraphAsymmErrors* DLLK_ScanPi = CalcPion->Perf_Scan(PIDCuts_Pion,
                                                       kFALSE);
  DLLK_ScanPi->SetName("DLLK_Pion");
  
  //======================================================================
  // Save graphs to file
  //======================================================================
  DLLK_ScanK->Write();
  DLLK_ScanPi->Write();
  delete DLLK_ScanK;
  delete DLLK_ScanPi;

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
  TGraphAsymmErrors* KaonSel_Scan = CalcKaon->Perf_Scan(Pion_MisID,
                                                        PIDCuts_Kaon,
                                                        kFALSE);
  KaonSel_Scan->SetName("KaonSel_Scan");
  KaonSel_Scan->GetXaxis()->SetTitle("Kaon ID Efficiency");
  KaonSel_Scan->GetYaxis()->SetTitle("Pion Mis-ID Efficiency");

  TGraphAsymmErrors* PionSel_Scan = CalcPion->Perf_Scan(Kaon_MisID,
                                                        PIDCuts_Pion,
                                                        kFALSE);
  PionSel_Scan->SetName("PionSel_Scan");
  PionSel_Scan->GetXaxis()->SetTitle("Pion ID Efficiency");
  PionSel_Scan->GetYaxis()->SetTitle("Kaon Mis-ID Efficiency");

  //======================================================================
  // Save graphs to file
  //======================================================================  
  KaonSel_Scan->Write();
  PionSel_Scan->Write();

  //======================================================================
  // Define Plot Binning
  //======================================================================
  RooBinning* Mom_Bin = new RooBinning(2000., 100000., "P");
  Mom_Bin->addUniform(45,2000.,100000);
  RooBinning* Pt_Bin = new RooBinning(0., 12000., "PT");
  Pt_Bin->addUniform(45,0.,12000);
  RooBinning* Eta_Bin = new RooBinning(1.5, 5.0, "ETA");
  Eta_Bin->addUniform(30, 1.5, 5.0);
  RooBinning* NTrk_Bin = new RooBinning(0, 400, "nTrack");
  NTrk_Bin->addUniform(50, 0, 400);

  vector<RooBinning*> BinSchema;
  BinSchema.push_back(Mom_Bin);
  BinSchema.push_back(Pt_Bin);
  BinSchema.push_back(Eta_Bin);
  BinSchema.push_back(NTrk_Bin);
  
  //=====================================================================
  // Define Cuts
  //=====================================================================
  vector<std::string> PIDCuts;
  PIDCuts.push_back("DLLmu > 0.0");
  PIDCuts.push_back("DLLmu > 5.0");

  vector<TH1F*> KaonPlots;
  vector<TH1F*> PionPlots;
  
  vector<std::string>::iterator cut_itr;
  vector<RooBinning*>::iterator bin_itr;
  int i=0;
  for(cut_itr=PIDCuts.begin(); cut_itr!=PIDCuts.end(); ++cut_itr, ++i)
  {
    for(bin_itr=BinSchema.begin(); bin_itr!=BinSchema.end(); ++bin_itr)
    {  
      TH1F* K_dummy = CalcKaon->Perf(*cut_itr,
                                     *bin_itr);
      K_dummy->SetName(TString::Format("Kaon_%s_%s",
                                       (*bin_itr)->GetName(),
                                       (boost::lexical_cast<string>(i*5)).c_str()
                                       ).Data());
      KaonPlots.push_back(K_dummy);

      TH1F* Pi_dummy = CalcPion->Perf(*cut_itr,
                                      *bin_itr);
      Pi_dummy->SetName(TString::Format("Pion_%s_%s",
                                        (*bin_itr)->GetName(),
                                        (boost::lexical_cast<string>(i*5)).c_str()
                                        ).Data());
      PionPlots.push_back(Pi_dummy);
      
    }
    
  }

  //======================================================================
  // Save graphs to file
  //======================================================================
  vector<TH1F*>::iterator his_itr;
  for(his_itr=KaonPlots.begin(); his_itr!=KaonPlots.end(); ++his_itr)
  {
    (*his_itr)->Write();
    delete (*his_itr);
  }
  for(his_itr=PionPlots.begin(); his_itr!=PionPlots.end(); ++his_itr)
  {
    (*his_itr)->Write();
    delete (*his_itr);
  }
  
  //======================================================================
  // Clean up
  //======================================================================
  myfile->Close();
  delete myfile;
  
  delete CalcPion; 
  delete CalcKaon; 
  
  delete Pion_DataSet;
  delete Kaon_DataSet;
  
  delete ws_Pi;
  delete ws_K;
  delete f_Pi;
  delete f_K;
  
  return 0;
  
}

