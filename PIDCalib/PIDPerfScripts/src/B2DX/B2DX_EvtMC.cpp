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

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <polarity> <d0_finalstate> <bachelorID> "<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<d0_finalstate> is one of (Kpi/K3pi/KK)"<<std::endl;
  std::cout << "\t<bachelorID> is one of (K/Pi)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Field Orientation (Up/Down)
  // 2: D0 Final State (Kpi,K3pi,KK)
  // 3: Bachelor ID (K/Pi)
  if (argc != 4)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//

  gSystem->Load("libRooStats.so");

  //=============================================================================
  // Obtain Calibration Samples
  //=============================================================================
  
  TFile* f_Pion = TFile::Open(TString::Format("$CALIBDATASTORE/MC10/Mag%s/DSt_Pi_Mag%s_MC10.root", 
                                              argv[1],
                                              argv[1]).Data());
  RooWorkspace* wsPion = (RooWorkspace*)f_Pion->Get("RSDStCalib");
  RooDataSet* Pion_Data = (RooDataSet*)wsPion->data( "data" );

  TFile* f_Kaon = TFile::Open(TString::Format("$CALIBDATASTORE/MC10/Mag%s/DSt_K_Mag%s_MC10.root", 
                                              argv[1],
                                              argv[1]).Data());
  RooWorkspace* wsKaon = (RooWorkspace*)f_Kaon->Get("RSDStCalib");
  RooDataSet* Kaon_Data = (RooDataSet*)wsKaon->data( "data" );
  
  //=============================================================================
  // Obtain Signal Track Data
  //=============================================================================
  const char* PartName = (strcmp(argv[3],"K")==0) ? argv[3] : ToLower(argv[3]);
  
  TFile* f_Sig = TFile::Open(TString::Format("$CALIBDATASTORE/Ref_MC/Bu_D0%s,%s_%s_reco_as_B2D%sFAV.root",
                                             PartName,
                                             argv[2],
                                             argv[1],
                                             argv[3]).Data());
  TTree* t_Sig = (TTree*)f_Sig->Get("Bu2D0X");

  //=============================================================================
  // Declare Binning Schema (RooBinnings)
  //=============================================================================
  RooBinning* Mom_Bin = new RooBinning(5000,100000,"P");
  RooBinning* Pt_Bin = new RooBinning(500,10000,"PT");
  RooBinning* Eta_Bin = new RooBinning(1.5,5,"ETA");
  RooBinning* nTrk_Bin = new RooBinning(0,500,"nTrack");
  
  Mom_Bin->addBoundary(9300); // R1 Kaon Threshold
  Mom_Bin->addBoundary(15600);// R2 Kaon Threshold
  Mom_Bin->addUniform(15, 19000, 100000);  
  
  Eta_Bin->addUniform(4, 1.5, 5);
  nTrk_Bin->addBoundary(50);
  nTrk_Bin->addBoundary(200);
  nTrk_Bin->addBoundary(300);

  vector<RooBinning*> BinSchema;
  BinSchema.push_back(Mom_Bin);
  //BinSchema.push_back(Pt_Bin);
  BinSchema.push_back(Eta_Bin);
  BinSchema.push_back(nTrk_Bin);

  vector<RooBinning*>::iterator iter =  BinSchema.begin();
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
  RooRealVar BMass("Bu_DPVCFIT_M", "", 5279.17-50.0, 5279.17+50.0, "MeV/c^{2}");
  RooRealVar DMass("D0_M", "", 1864.83-25.0, 1864.83+25.0, "MeV/c^{2}");
  RooRealVar DFlightDist("D0_FD_ZSIG", "", 0, 100000);
  RooRealVar DMass_MisIDVETO("D0_M_DOUBLESW", "", 0, 5500, "MeV/c^{2}");
  RooRealVar BBkgCat("Bu_BKGCAT", "", -1, 1);

  double BDT_min;
  string DDaught1_name;
  string DDaught2_name;
  double DDaught1_DLLKmin, DDaught1_DLLKmax;
  double DDaught2_DLLKmin, DDaught2_DLLKmax;
  if(strcmp(argv[3],"kpi")!=0)
  {
    BDT_min = 0.92;
    DDaught1_name = "K_PIDK";
    DDaught2_name = "Pi_PIDK";
    DDaught1_DLLKmin = 2.0;
    DDaught2_DLLKmin = -200.0;
    DDaught1_DLLKmax = 200.0;
    DDaught2_DLLKmax = -2.0;
  }
  else if(strcmp(argv[3],"kk")!=0)
  {
    BDT_min = 0.80;
    DDaught1_name = "K0_PIDK";
    DDaught2_name = "K1_PIDK";
    DDaught1_DLLKmin = 2.0;
    DDaught2_DLLKmin = 2.0;
    DDaught1_DLLKmax = 200.0;
    DDaught2_DLLKmax = 200.0;
  }
  else if(strcmp(argv[3],"pipi")!=0)
  {
    BDT_min = 0.80;
    DDaught1_name = "Pi0_PIDK";
    DDaught2_name = "Pi1_PIDK";
    DDaught1_DLLKmin = -200.0;
    DDaught2_DLLKmin = -200.0;
    DDaught1_DLLKmax = -2.0;
    DDaught2_DLLKmax = -2.0;
  }
  else
    return EXIT_FAILURE;

  RooRealVar BDT("BDT", "", BDT_min, 1.0, "");
  RooRealVar DDaught1_DLLK( DDaught1_name.c_str(), "", DDaught1_DLLKmin, DDaught1_DLLKmax);
  RooRealVar DDaught2_DLLK( DDaught2_name.c_str(), "", DDaught2_DLLKmin, DDaught2_DLLKmax);

  RooArgSet Vars(Mom,
                 Pt,
                 Eta,
                 DLLK,
                 DLLp,
                 nTracks,
                 BMass,
                 DMass,
                 BDT);
  Vars.add(BBkgCat);
  Vars.add(DFlightDist);
  Vars.add(DDaught1_DLLK);
  Vars.add(DDaught2_DLLK);
  Vars.add(DMass_MisIDVETO);
  
  string DoubleSwap = "abs(D0_M_DOUBLESW-1864.78)>15.0";

  EvtTrackDataSet* Sig_DataSet = new EvtTrackDataSet( "B->DK Kaon",
                                                      "Signal Track",
                                                      t_Sig,
                                                      Vars,
                                                      "Bach_P",
                                                      "Bach_PT",
                                                      "Bach_TRACK_Eta",
                                                      "nTracks",
                                                      "Bach_PIDK",
                                                      "Bach_PIDp",
                                                      DoubleSwap);
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
  // Create a 'Bin' Weigthed Copy of Pion_DataSet 
  //=============================================================================
  EvtTrackDataSet* Weighted_PionBin = 
    (EvtTrackDataSet*)WeightPion->WeightInBins("Wgt",
                                               kTRUE,
                                               "",
                                               "nsig_sw"
                                               );
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
  // Create a 'Bin' Weigthed Copy of Kaon_DataSet
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
                                                             "Pos",
                                                             Weighted_PionBin,
                                                             *Weighted_PionBin->get(),
                                                             "",
                                                             "nsig_sw");

  EvtTrackDataSet* Weighted_KaonBin_sw = new EvtTrackDataSet("Test",
                                                             "Pos",
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
  string Postfix = (strcmp(argv[3],"K")==0) ? "Kaon" : "Pion";
  ws->import(*ANDPion_Sig_DataSet, Rename(("ANDPion_Sig_"+Postfix).c_str()) );
  ws->import(*ANDKaon_Sig_DataSet, Rename(("ANDKaon_Sig_"+Postfix).c_str()) );
  ws->import(*Weighted_PionBin, Rename("CalPion"));
  ws->import(*Weighted_KaonBin, Rename("CalKaon"));
  TString FileOut = "EvtMC_" + 
    boost::lexical_cast<std::string>(Mom_Bin->numBins()) +
    "Momx" + 
    boost::lexical_cast<std::string>(Eta_Bin->numBins()) +
    "Etax" +
    boost::lexical_cast<std::string>(nTrk_Bin->numBins()) +
    "nTrk_%s_%s_%s.root";
  ws->writeToFile(TString::Format(FileOut.Data(), 
                                  argv[1], 
                                  argv[2],
                                  argv[3]).Data());

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

