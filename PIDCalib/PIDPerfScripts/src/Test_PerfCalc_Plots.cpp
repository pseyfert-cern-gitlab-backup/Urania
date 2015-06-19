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
#include <vector>
#include <boost/lexical_cast.hpp>

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
  
  std::string StripVersion;
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
  
  EvtTrackDataSet* Pion_DataSet = new EvtTrackDataSet("Calib. Pion",
                                                      "",
                                                      Pion_Data,
                                                      *Pion_Data->get(),
                                                      "Pi_P",
                                                      "Pi_PT",
                                                      "Pi_Eta",
                                                      "nTracks",
                                                      "Pi_CombDLLK",
                                                      "Pi_CombDLLp",
                                                      "Charge==Charge::Positive && Pi_P<100000",
                                                      "nsig_sw");
  
  EvtTrackDataSet* Kaon_DataSet = new EvtTrackDataSet("Calib. Kaon",
                                                      "",
                                                      Kaon_Data,
                                                      *Kaon_Data->get(),
                                                      "K_P",
                                                      "K_PT",
                                                      "K_Eta",
                                                      "nTracks",
                                                      "K_CombDLLK",
                                                      "K_CombDLLp",
                                                      "Charge==Charge::Positive && K_P<100000",
                                                      "nsig_sw");
  
  Pion_DataSet->Print("v");
  Kaon_DataSet->Print("v");

  std::cout<<Pion_DataSet->isWeighted()<<'\t'
           <<Kaon_DataSet->isWeighted()<<std::endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<EvtTrackDataSet>* CalcKaon = new PerfCalculator<EvtTrackDataSet>( Kaon_DataSet );
  PerfCalculator<EvtTrackDataSet>* CalcPion = new PerfCalculator<EvtTrackDataSet>( Pion_DataSet );
  
  PIDRESULT Kaon_0 = CalcKaon->Perf("DLLK > 0");

  PIDRESULT Pion_0 = CalcPion->Perf("DLLK > 0");

  std::cout<<Kaon_0.Eff<<'\t'<<Kaon_0.Err_Lo<<'\t'<<Kaon_0.Err_Hi<<std::endl;
  std::cout<<Pion_0.Eff<<'\t'<<Pion_0.Err_Lo<<'\t'<<Pion_0.Err_Hi<<std::endl;
  
  PIDRESULT Kaon_5 = CalcKaon->Perf("DLLK > 5");

  PIDRESULT Pion_5 = CalcPion->Perf("DLLK > 5");

  std::cout<<Kaon_5.Eff<<'\t'<<Kaon_5.Err_Lo<<'\t'<<Kaon_5.Err_Hi<<std::endl;
  std::cout<<Pion_5.Eff<<'\t'<<Pion_5.Err_Lo<<'\t'<<Pion_5.Err_Hi<<std::endl;
  
  //======================================================================
  // Define Plot Binning
  //======================================================================
  RooBinning* Mom_Bin = new RooBinning(2000., 100000., "P");
  Mom_Bin->addUniform(60,2000.,100000);
  RooBinning* Pt_Bin = new RooBinning(0., 20000., "PT");
  Pt_Bin->addUniform(100,0.,20000);
  RooBinning* Eta_Bin = new RooBinning(1.5, 5.0, "ETA");
  Eta_Bin->addUniform(30, 1.5, 5.0);
  RooBinning* NTrk_Bin = new RooBinning(0, 400, "nTrack");
  NTrk_Bin->addUniform(50, 0, 400);

  std::vector<RooBinning*> BinSchema;
  BinSchema.push_back(Mom_Bin);
  BinSchema.push_back(Pt_Bin);
  BinSchema.push_back(Eta_Bin);
  BinSchema.push_back(NTrk_Bin);
  
  //=====================================================================
  // DLL(K - pi) > 0
  //=====================================================================

  std::vector<std::string> DLLCuts;
  DLLCuts.push_back("DLLK > 0.0");
  DLLCuts.push_back("DLLK > 5.0");
  DLLCuts.push_back("DLLK > 10.0");

  std::vector<TGraphAsymmErrors*> KaonPlots;
  std::vector<TGraphAsymmErrors*> PionPlots;
  
  std::vector<std::string>::iterator cut_itr;
  std::vector<RooBinning*>::iterator bin_itr;
  int i=0;
  for(cut_itr=DLLCuts.begin(); cut_itr!=DLLCuts.end(); ++cut_itr, ++i)
  {
    for(bin_itr=BinSchema.begin(); bin_itr!=BinSchema.end(); ++bin_itr)
    {  
      TGraphAsymmErrors* K_dummy = CalcKaon->Perf_BayesErrors(*cut_itr,
                                                              *bin_itr);
      K_dummy->SetName(TString::Format("Kaon_%s_%s",
                                       (*bin_itr)->GetName(),
                                       (boost::lexical_cast<std::string>(i*5)).c_str()
                                       ).Data());
      KaonPlots.push_back(K_dummy);

      TGraphAsymmErrors* Pi_dummy = CalcPion->Perf_BayesErrors(*cut_itr,
                                                               *bin_itr);
      Pi_dummy->SetName(TString::Format("Pion_%s_%s",
                                        (*bin_itr)->GetName(),
                                        (boost::lexical_cast<std::string>(i*5)).c_str()
                                        ).Data());
      PionPlots.push_back(Pi_dummy);
      
    }
    
  }
  

  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile("Strip13b_MagUp_Pos_Perf.root", "RECREATE");
  
  std::vector<TGraphAsymmErrors*>::iterator his_itr;
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
  myfile->Close();

  //======================================================================
  // Clean up
  //======================================================================
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

