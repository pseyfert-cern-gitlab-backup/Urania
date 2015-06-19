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
  // Obtain Calibration Samples
  //======================================================================
  TFile* f_Pion = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_Pi_Mag%s_Strip%s_%s.root",
                                               argv[1],
                                               argv[2],
                                               argv[2],
                                               StripVersion.c_str(),
                                               argv[3])).Data()
                              );
  RooWorkspace* wsPion = (RooWorkspace*)f_Pion->Get("RSDStCalib");
  RooDataSet* Pion_Data = (RooDataSet*)wsPion->data( "data" );

  TFile* f_Kaon = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_K_Mag%s_Strip%s_%s.root",
                                               argv[1],
                                               argv[2],
                                               argv[2],
                                               StripVersion.c_str(),
                                               argv[3])).Data()                                              
                              );
  RooWorkspace* wsKaon = (RooWorkspace*)f_Kaon->Get("RSDStCalib");
  RooDataSet* Kaon_Data = (RooDataSet*)wsKaon->data( "data" );
  
  //======================================================================
  // Import DataSets into TrackDataSet instances and declare weighting
  // variable:
  // - nsig_sw       : Raw calibration
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
  // Define binning schema
  //======================================================================
  RooBinning* P_Bin = new RooBinning(2000., 100000., "P");
  //RooBinning* PT_Bin = new RooBinning(200., 100000., "PT");
  RooBinning* ETA_Bin = new RooBinning(1.5, 5.5, "ETA");
  P_Bin->addUniform(5,2000,100000);
  ETA_Bin->addUniform(4,1.5,5.5);

  //======================================================================
  // Output to screen PID tables
  //======================================================================
  PIDTable* PionTab = CalcPion->Table("DLLK < 6.0",
                                      P_Bin,
                                      ETA_Bin);
  
  PIDTable* KaonTab  = CalcKaon->Table("DLLK > 6.0 && DLLpK < 2.0",
                                       P_Bin,
                                       ETA_Bin);
  PionTab->PrintTable(std::cout,
                      kFALSE);
  
  KaonTab->PrintTable(std::cout,
                      kFALSE);

  const TH2F* PionTab_Hist = PionTab->GetPerfHist2D();
  const TH2F* KaonTab_Hist = KaonTab->GetPerfHist2D();
  
  TFile* myFile = new TFile("PIDTables.root","RECREATE");
  PionTab_Hist->Write();
  KaonTab_Hist->Write();
  //======================================================================
  // Clean up
  //======================================================================
  delete myFile;

  delete PionTab;
  delete KaonTab;

  delete CalcKaon; 
  delete CalcPion;
  
  delete Kaon_DataSet;
  delete Pion_DataSet;
  
  return 0;
  
}

