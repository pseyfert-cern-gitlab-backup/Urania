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
            << " <reco_version> <polarity> <dataset_index>"<<std::endl;
  std::cout << "\t<reco_version> is the reconstruction version used to process the data (10/11)"<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<dataset_index> is one of (0/1/2/..)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Reco Version (10,11,..)
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
  
  RICHTrackDataSet* Pion_DataSet = new RICHTrackDataSet("Calib. Pion",
                                                        "",
                                                        Pion_Data,
                                                        *Pion_Data->get(),
                                                        "Pi_P",
                                                        "Pi_PT",
                                                        "Pi_Eta",
                                                        "nLong",
                                                        "Pi_CombDLLK",
                                                        "Pi_CombDLLp",
                                                        "Pi_ProbNNK",
                                                        "Pi_ProbNNpi",
                                                        "Pi_ProbNNp",
                                                        "Pi_P<100000 && Charge==Charge::Positive",
                                                        "nsig_sw");
  
  RICHTrackDataSet* Kaon_DataSet = new RICHTrackDataSet("Calib. Kaon",
                                                        "",
                                                        Kaon_Data,
                                                        *Kaon_Data->get(),
                                                        "K_P",
                                                        "K_PT",
                                                        "K_Eta",
                                                        "nLong",
                                                        "K_CombDLLK",
                                                        "K_CombDLLp",
                                                        "K_ProbNNK",
                                                        "K_ProbNNpi",
                                                        "K_ProbNNp",
                                                        "K_P<100000 && Charge==Charge::Positive",
                                                        "nsig_sw");
  
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
  list<std::string> PIDCuts_KaonMisID;
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
  // Declare TFile for Saving Graphs
  //======================================================================
  TFile *myfile = new TFile(TString::Format("Perf_ProbNNK_Mag%s_Strip%s.root",
                                            argv[2],
                                            StripVersion.c_str()).Data(), 
                            "RECREATE");

  //======================================================================
  // Perform ID Scans
  //======================================================================
  TGraphAsymmErrors* ProbNNK_ScanK = CalcKaon->Perf_Scan(PIDCuts_Kaon,
                                                         kFALSE);
  ProbNNK_ScanK->SetName("ProbNNK_Kaon");
  
  TGraphAsymmErrors* ProbNNK_ScanPi = CalcPion->Perf_Scan(PIDCuts_Pion,
                                                          kFALSE);
  ProbNNK_ScanPi->SetName("ProbNNK_Pion");
  
  //======================================================================
  // Save graphs to file
  //======================================================================
  ProbNNK_ScanK->Write();
  ProbNNK_ScanPi->Write();
  delete ProbNNK_ScanK;
  delete ProbNNK_ScanPi;

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
  vector<std::string> PIDCuts_ProbNNK;
  PIDCuts_ProbNNK.push_back("ProbNNK > 0.2");
  PIDCuts_ProbNNK.push_back("ProbNNK > 0.4");
  vector<std::string> PIDCuts_ProbNNpi;
  PIDCuts_ProbNNpi.push_back("ProbNNpi > 0.2");
  PIDCuts_ProbNNpi.push_back("ProbNNpi > 0.4");

  vector<TH1F*> KaonPlots;
  vector<TH1F*> PionPlots;
  
  vector<std::string>::iterator cut_itr;
  vector<RooBinning*>::iterator bin_itr;
  //=====================================================================
  // Loop over all Binnings and Make Corresponding Plots
  //=====================================================================
  for(bin_itr=BinSchema.begin(); bin_itr!=BinSchema.end(); ++bin_itr)
  { 
    int i=1;
    //===================================================================
    // Loop over all ProbNNK cuts
    //===================================================================
    for(cut_itr=PIDCuts_ProbNNK.begin(); cut_itr!=PIDCuts_ProbNNK.end(); ++cut_itr, ++i)
    {
      TH1F* K_dummy = CalcKaon->Perf(*cut_itr,
                                     *bin_itr);
      K_dummy->SetName(TString::Format("Kaon_%s_ProbNNK_%s",
                                       (*bin_itr)->GetName(),
                                       (boost::lexical_cast<string>(i*2)).c_str()
                                       ).Data());
      KaonPlots.push_back(K_dummy);

      TH1F* Pi_dummy = CalcPion->Perf(*cut_itr,
                                      *bin_itr);
      Pi_dummy->SetName(TString::Format("Pion_%s_ProbNNK_%s",
                                        (*bin_itr)->GetName(),
                                        (boost::lexical_cast<string>(i*2)).c_str()
                                        ).Data());
      PionPlots.push_back(Pi_dummy);
    }
    i=1;
    //===================================================================
    // Loop over all ProbNNpi cuts
    //===================================================================
    for(cut_itr=PIDCuts_ProbNNpi.begin(); cut_itr!=PIDCuts_ProbNNpi.end(); ++cut_itr, ++i)
    {
      TH1F* K_dummy = CalcKaon->Perf(*cut_itr,
                                     *bin_itr);
      K_dummy->SetName(TString::Format("Kaon_%s_ProbNNpi_%s",
                                       (*bin_itr)->GetName(),
                                       (boost::lexical_cast<string>(i*2)).c_str()
                                       ).Data());
      KaonPlots.push_back(K_dummy);

      TH1F* Pi_dummy = CalcPion->Perf(*cut_itr,
                                      *bin_itr);
      Pi_dummy->SetName(TString::Format("Pion_%s_ProbNNpi_%s",
                                        (*bin_itr)->GetName(),
                                        (boost::lexical_cast<string>(i*2)).c_str()
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

