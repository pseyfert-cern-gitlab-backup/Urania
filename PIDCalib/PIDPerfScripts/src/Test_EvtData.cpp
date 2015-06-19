// $Id: $
// Include files 
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/WeightDataSetTool.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "TCut.h"
#include "RooWorkspace.h"
#include <list>
// Boost
#include <boost/lexical_cast.hpp>

using namespace RooFit;
using std::cout;
using std::endl;

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

  //=============================================================================
  // Obtain Calibration Samples
  //============================================================================= 
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

  //=============================================================================
  // Obtain Signal Track Data
  //=============================================================================
  TFile* f_Sig = TFile::Open(TString::Format("$CALIBDATASTORE/Ref_DATA/b2dk_d2kpi_%s.root",
                                             (ToLower(argv[2])).Data()).Data()
                             );
  TTree* t_Sig = (TTree*)f_Sig->Get("Bu2D0X");

  //=============================================================================
  // Declare Binning Variables (RooBinnings)
  //=============================================================================
  RooBinning* Mom_Bin = new RooBinning(5000,100000,"P");
  RooBinning* Pt_Bin = new RooBinning(500,20000,"PT");
  RooBinning* Eta_Bin = new RooBinning(1.5,5,"ETA");
  RooBinning* nTrk_Bin = new RooBinning(0,400,"nTrack");
  
  Mom_Bin->addBoundary(9300); // R1 Kaon Threshold
  Mom_Bin->addBoundary(17675);// R1 Proton Threshold
  Mom_Bin->addBoundary(15600);// R2 Kaon Threshold
  Mom_Bin->addBoundary(20000);
  Mom_Bin->addBoundary(23000);
  Mom_Bin->addBoundary(26000);
  Mom_Bin->addBoundary(29650);// R2 Proton Threshold
  Mom_Bin->addUniform(10, 30000, 100000);  
  
  Eta_Bin->addUniform(4, 1.5, 5);
  nTrk_Bin->addBoundary(50);
  nTrk_Bin->addBoundary(100);
  nTrk_Bin->addBoundary(200);

  //=============================================================================
  // Declare Binning Schema (vector<RooBinnings*>) for any number of bin
  // Dimensions
  //=============================================================================
  std::vector<RooBinning*> BinSchema;
  BinSchema.push_back(Mom_Bin);
  //BinSchema.push_back(Pt_Bin);
  BinSchema.push_back(Eta_Bin);
  BinSchema.push_back(nTrk_Bin);

  std::vector<RooBinning*>::iterator iter =  BinSchema.begin();
  cout<<"========== Binning Schema =========="<<endl;
  for(;iter!=BinSchema.end();++iter) 
  {
    (*iter)->Print();
  }
  cout<<"===================================="<<endl;  

  //=============================================================================
  // Create Instance of EvtTrackDataSet for Signal tracks which calibration 
  // tracks will be weighted to
  //=============================================================================
  RooRealVar Mom("Bach_P", "", Mom_Bin->lowBound(), Mom_Bin->highBound(), "MeV/c");
  RooRealVar Pt("Bach_PT", "", Pt_Bin->lowBound(), Pt_Bin->highBound(), "MeV/c");
  RooRealVar Eta("Bach_TRACK_Eta", "", Eta_Bin->lowBound(), Eta_Bin->highBound(), "");
  RooRealVar DLLK("Bach_PIDK", "", -150, 150, "");
  RooRealVar DLLp("Bach_PIDp", "", -150, 150, "");
  RooRealVar nTracks("nTracks", "", nTrk_Bin->lowBound(), nTrk_Bin->highBound());
  RooRealVar BMass("Bu_DPVCFIT_M", "", 5274.19-50.0, 5274.19+50.0, "MeV/c^{2}");
  RooRealVar DMass("D0_M", "", 1862.67-25.0, 1862.67+25.0, "MeV/c^{2}");
  RooRealVar BDT("BDT", "", 0.92, 1.0, "");
 
  EvtTrackDataSet* Sig_DataSet = new EvtTrackDataSet( "B->DPi Pion",
                                                      "Signal Track",
                                                      t_Sig,
                                                      RooArgSet(Mom,
                                                                Pt,
                                                                Eta,
                                                                DLLK,
                                                                DLLp,
                                                                nTracks,
                                                                BMass,
                                                                DMass,
                                                                BDT),
                                                      "Bach_P",
                                                      "Bach_PT",
                                                      "Bach_TRACK_Eta",
                                                      "nTracks",
                                                      "Bach_PIDK",
                                                      "Bach_PIDp");
  Sig_DataSet->get(0);
  Sig_DataSet->Print("v");

  //=============================================================================
  // Declare Instance of EvtTrackDataSet for Calibration tracks within BinSchema
  //=============================================================================
  EvtTrackDataSet* Pion_DataSetAll = 
    new EvtTrackDataSet("Calib. Pion",
                        "",
                        Pion_Data,
                        *Pion_Data->get(),
                        "Pi_P",
                        "Pi_PT",
                        "Pi_Eta",
                        "nTracks",
                        "Pi_CombDLLK",
                        "Pi_CombDLLp",
                        TString::Format("Pi_P>%f && Pi_P<%f &&" 
                                        "Pi_PT>%f && Pi_PT<%f &&"
                                        "Pi_Eta>%f && Pi_Eta<%f &&"
                                        "nTracks>%f && nTracks<%f",
                                        Mom_Bin->lowBound(), Mom_Bin->highBound(),
                                        Pt_Bin->lowBound(), Pt_Bin->highBound(),
                                        Eta_Bin->lowBound(), Eta_Bin->highBound(),
                                        nTrk_Bin->lowBound(), nTrk_Bin->highBound()
                                        ).Data() 
                        );
  delete  Pion_Data;
  EvtTrackDataSet* Pion_DataSet = (EvtTrackDataSet*) Pion_DataSetAll->SetInBinSchema(BinSchema);
  delete Pion_DataSetAll;

  EvtTrackDataSet* Kaon_DataSetAll = 
    new EvtTrackDataSet("Calib. Kaon",
                        "",
                        Kaon_Data,
                        *Kaon_Data->get(),
                        "K_P",
                        "K_PT",
                        "K_Eta",
                        "nTracks",
                        "K_CombDLLK",
                        "K_CombDLLp",
                        TString::Format("K_P>%f && K_P<%f &&" 
                                        "K_PT>%f && K_PT<%f &&"
                                        "K_Eta>%f && K_Eta<%f &&"
                                        "nTracks>%f && nTracks<%f",
                                        Mom_Bin->lowBound(), Mom_Bin->highBound(),
                                        Pt_Bin->lowBound(), Pt_Bin->highBound(),
                                        Eta_Bin->lowBound(), Eta_Bin->highBound(),
                                        nTrk_Bin->lowBound(), nTrk_Bin->highBound()                                 
                                        ).Data()  
                        );
  
  delete Kaon_Data;
  EvtTrackDataSet* Kaon_DataSet = (EvtTrackDataSet*) Kaon_DataSetAll->SetInBinSchema(BinSchema);
  delete Kaon_DataSetAll;

  Pion_DataSet->Print("v");
  Kaon_DataSet->Print("v");
 
  //=============================================================================
  // Create an Instnace of WeightDataSetTool for the Pion Tracks
  //=============================================================================
  WeightDataSetTool<EvtTrackDataSet>* WeightPion = 
    new WeightDataSetTool<EvtTrackDataSet>( Sig_DataSet,
                                            Pion_DataSet,
                                            BinSchema );
  
  //=============================================================================
  // Make a Copy of the Signal DataSet with Events Only in those Bins that 
  // Contained Pion Calibration Tracks
  //=============================================================================
  EvtTrackDataSet* ANDPion_Sig_DataSet =  
    (EvtTrackDataSet*)WeightPion->ANDInBins("nsig_sw",
                                            "");
  ANDPion_Sig_DataSet->printValue(cout);
  cout<<endl;
  
  //=============================================================================
  // Create a 'Bin' Weighted Copy of Pion_DataSet 
  //=============================================================================
  EvtTrackDataSet* Weighted_PionBin = 
    (EvtTrackDataSet*)WeightPion->WeightInBins("Wgt",
                                               kTRUE,
                                               "",
                                               "nsig_sw");

  delete WeightPion;
  delete Pion_DataSet;

  //=============================================================================
  // Create an Instnace of WeightDataSetTool for the Kaon Tracks
  //=============================================================================
  WeightDataSetTool<EvtTrackDataSet>* WeightKaon = 
    new WeightDataSetTool<EvtTrackDataSet>( Sig_DataSet,
                                            Kaon_DataSet,
                                            BinSchema );
  
  //=============================================================================
  // Make a Copy of the Signal DataSet with Events Only in those Bins that 
  // Contained Kaon Calibration Tracks
  //=============================================================================
  EvtTrackDataSet* ANDKaon_Sig_DataSet =  
    (EvtTrackDataSet*)WeightKaon->ANDInBins("nsig_sw",
                                            "");
  
  ANDKaon_Sig_DataSet->printValue(cout);
  cout<<endl;

  //=============================================================================
  // Create a 'Bin' Weighted Copy of Kaon_DataSet
  //=============================================================================  
  EvtTrackDataSet* Weighted_KaonBin = 
    (EvtTrackDataSet*)WeightKaon->WeightInBins("Wgt",
                                               kTRUE,
                                               "",
                                               "nsig_sw");
  delete WeightKaon;
  delete Kaon_DataSet;

  delete Sig_DataSet;
  Weighted_PionBin->get(0);
  Weighted_PionBin->Print("v");
  Weighted_KaonBin->get(0);
  Weighted_KaonBin->Print("v");

  //=============================================================================
  // Weight with New Weight Variable 
  //=============================================================================
  EvtTrackDataSet* Weighted_PionBin_sw = new EvtTrackDataSet("Test",
                                                             "",
                                                             Weighted_PionBin,
                                                             *Weighted_PionBin->get(),
                                                             "",
                                                             "nsig_sw");

  EvtTrackDataSet* Weighted_KaonBin_sw = new EvtTrackDataSet("Test",
                                                             "",
                                                             Weighted_KaonBin,
                                                             *Weighted_KaonBin->get(),
                                                             "",
                                                             "nsig_sw");

  cout<<Weighted_PionBin_sw->isWeighted()<<'\t'
      <<Weighted_KaonBin_sw->isWeighted()<<endl;
  Weighted_PionBin_sw->printValue(cout);
  cout<<endl;
  Weighted_KaonBin_sw->printValue(cout);
  cout<<endl;
  delete Weighted_PionBin_sw;
  delete Weighted_KaonBin_sw;
  
  EvtTrackDataSet* Weighted_PionBin_wgt = new EvtTrackDataSet("Test",
                                                              "",
                                                              Weighted_PionBin,
                                                              *Weighted_PionBin->get(),
                                                              "",
                                                              "Wgt");

  EvtTrackDataSet* Weighted_KaonBin_wgt = new EvtTrackDataSet("Test",
                                                              "",
                                                              Weighted_KaonBin,
                                                              *Weighted_KaonBin->get(),
                                                              "",
                                                              "Wgt");

  cout<<Weighted_PionBin_wgt->isWeighted()<<'\t'
      <<Weighted_KaonBin_wgt->isWeighted()<<endl;
  Weighted_PionBin_wgt->printValue(cout);
  cout<<endl;
  Weighted_KaonBin_wgt->printValue(cout);
  cout<<endl;
  
  //=============================================================================
  // Write to File within a RooWorkspace
  //=============================================================================
  RooWorkspace* ws = new RooWorkspace("ws","");
  ws->import(*ANDPion_Sig_DataSet, Rename("ANDPion_Sig_Pion"));
  ws->import(*ANDKaon_Sig_DataSet, Rename("ANDKaon_Sig_Pion"));
  ws->import(*Weighted_PionBin, Rename("CalPion"));
  ws->import(*Weighted_KaonBin, Rename("CalKaon"));
  ws->writeToFile( (TString("EvtDataPion_" + 
                            boost::lexical_cast<std::string>(Mom_Bin->numBins()) +
                            "Momx" + 
                            boost::lexical_cast<std::string>(Eta_Bin->numBins()) +
                            "Etax" +
                            boost::lexical_cast<std::string>(nTrk_Bin->numBins()) +
                            "nTrk.root")).Data()
                   );

  delete Weighted_PionBin;
  delete Weighted_KaonBin;
  delete ANDPion_Sig_DataSet;
  delete ANDKaon_Sig_DataSet;

  delete Mom_Bin;
  delete Pt_Bin;
  delete Eta_Bin;
  delete nTrk_Bin;
  delete ws;

  delete Weighted_PionBin_wgt;
  delete Weighted_KaonBin_wgt;
  
  return 0;
  
}

