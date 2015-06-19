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
  // 1: Reco Version (10,11,12,..)
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
  TFile* f_Pi = new TFile((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_Pi_Mag%s_Strip%s_%s.root",
                                           argv[1],
                                           argv[2],
                                           argv[2],
                                           StripVersion.c_str(),
                                           argv[3])).Data()
                          );
  if (!f_Pi) return 1;

  TFile* f_P = new TFile((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/Lam0_P_Mag%s_Strip%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[2],
                                          StripVersion.c_str(),
                                          argv[3])).Data()                                              
                         );
  if (!f_P) return 1;

  //======================================================================
  // Get RooWorkspace
  //======================================================================
  RooWorkspace* ws_Pi = (RooWorkspace*) f_Pi->Get("RSDStCalib");
  ws_Pi->Print("v");
  RooWorkspace* ws_P = (RooWorkspace*) f_P->Get("Lam0Calib");
  ws_P->Print("v");
  
  //======================================================================
  // Get DataSets
  //======================================================================
  RooDataSet* Pion_Data = (RooDataSet*)ws_Pi->data( "data" );
  RooDataSet* Proton_Data = (RooDataSet*)ws_P->data( "data" );
  
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
                                                      "Pi_P<100000",
                                                      "nsig_sw");
  
  EvtTrackDataSet* Proton_DataSet = new EvtTrackDataSet("Calib. Proton",
                                                        "",
                                                        Proton_Data,
                                                        *Proton_Data->get(),
                                                        "P_P",
                                                        "P_PT",
                                                        "P_Eta",
                                                        "nTracks",
                                                        "P_CombDLLK",
                                                        "P_CombDLLp",
                                                        "P_P<100000",
                                                        "nsig_sw");
  
  Pion_DataSet->Print("v");
  Proton_DataSet->Print("v");

  cout<<Pion_DataSet->isWeighted()<<'\t'
      <<Proton_DataSet->isWeighted()<<endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<EvtTrackDataSet>* CalcProton = new PerfCalculator<EvtTrackDataSet>( Proton_DataSet );
  PerfCalculator<EvtTrackDataSet>* CalcPion = new PerfCalculator<EvtTrackDataSet>( Pion_DataSet );
  
  PIDRESULT Proton_0 = CalcProton->Perf("DLLp > 0", kFALSE);

  PIDRESULT Pion_0 = CalcPion->Perf("DLLp > 0", kFALSE);

  cout<<Proton_0.Eff<<'\t'<<Proton_0.Err_Lo<<'\t'<<Proton_0.Err_Hi<<endl;
  cout<<Pion_0.Eff<<'\t'<<Pion_0.Err_Lo<<'\t'<<Pion_0.Err_Hi<<endl;
  
  PIDRESULT Proton_5 = CalcProton->Perf("DLLp > 5", kFALSE);

  PIDRESULT Pion_5 = CalcPion->Perf("DLLp > 5", kFALSE);

  cout<<Proton_5.Eff<<'\t'<<Proton_5.Err_Lo<<'\t'<<Proton_5.Err_Hi<<endl;
  cout<<Pion_5.Eff<<'\t'<<Pion_5.Err_Lo<<'\t'<<Pion_5.Err_Hi<<endl;
  
  //======================================================================
  // Define Plot Binning
  //======================================================================
  RooBinning* Mom_Bin = new RooBinning(2000., 100000., "P");
  Mom_Bin->addUniform(30,2000,40000);
  Mom_Bin->addUniform(17,40000,66000);
  Mom_Bin->addUniform(2,66000, 70000);
  Mom_Bin->addUniform(2,70000, 75000);
  Mom_Bin->addUniform(4,75000, 85000);
  Mom_Bin->addUniform(2,85000, 100000);
  RooBinning* Pt_Bin = new RooBinning(0., 20000., "PT");
  Pt_Bin->addUniform(100,0.,20000);
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
  // DLL(P - pi) > 0
  //=====================================================================

  vector<std::string> DLLCuts;
  DLLCuts.push_back("DLLp > 0.0");
  DLLCuts.push_back("DLLp > 5.0");
  //DLLCuts.push_back("DLLp > 10.0");

  vector<TH1F*> ProtonPlots;
  vector<TH1F*> PionPlots;
  
  vector<std::string>::iterator cut_itr;
  vector<RooBinning*>::iterator bin_itr;
  int i=0;
  for(cut_itr=DLLCuts.begin(); cut_itr!=DLLCuts.end(); ++cut_itr, ++i)
  {
    for(bin_itr=BinSchema.begin(); bin_itr!=BinSchema.end(); ++bin_itr)
    {  
      TH1F* P_dummy = CalcProton->Perf(*cut_itr,
                                     *bin_itr);
      P_dummy->SetName(TString::Format("Proton_%s_%s",
                                       (*bin_itr)->GetName(),
                                       (boost::lexical_cast<string>(i*5)).c_str()
                                       ).Data());
      ProtonPlots.push_back(P_dummy);

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
  TFile *myfile = new TFile(TString::Format("PPi_Separation_Mag%s_Strip%s.root",
                                            argv[2],
                                            StripVersion.c_str()).Data()
                            , "RECREATE");
  
  vector<TH1F*>::iterator his_itr;
  for(his_itr=ProtonPlots.begin(); his_itr!=ProtonPlots.end(); ++his_itr)
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
  delete CalcProton; 
  
  delete Pion_DataSet;
  delete Proton_DataSet;
  
  delete ws_Pi;
  delete ws_P;
  delete f_Pi;
  delete f_P;
  
  return 0;
  
}

