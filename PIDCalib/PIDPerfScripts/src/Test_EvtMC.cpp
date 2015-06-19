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

int main(void)
{
  gSystem->Load("libRooStats.so");

  //=============================================================================
  // Obtain Calibration Samples
  //=============================================================================
  TFile* f_Pion = TFile::Open("$CALIBDATASTORE/Reco08_MC10/MagUp/DSt_Pi_MagUp_Strip12MC10.root");
  RooWorkspace* wsPion = (RooWorkspace*)f_Pion->Get("RSDStCalib");
  RooDataSet* Pion_Data = (RooDataSet*)wsPion->data( "data" );

  TFile* f_Kaon = TFile::Open("$CALIBDATASTORE/Reco08_MC10/MagUp/DSt_K_MagUp_Strip12MC10.root");
  RooWorkspace* wsKaon = (RooWorkspace*)f_Kaon->Get("RSDStCalib");
  RooDataSet* Kaon_Data = (RooDataSet*)wsKaon->data( "data" );
  
  //=============================================================================
  // Obtain Signal Track Data
  //=============================================================================
  TFile* f_Sig = TFile::Open("$CALIBDATASTORE/Ref_MC/Bu_D0K,Kpi_Up_reco_as_B2DKFAV.root");
  TTree* t_Sig = (TTree*)f_Sig->Get("Bu2D0X");

  //=============================================================================
  // Declare Binning Variables (RooBinnings)
  //=============================================================================
  RooBinning* Mom_Bin = new RooBinning(5000,100000,"P");
  RooBinning* Pt_Bin = new RooBinning(500,20000,"PT");
  RooBinning* Eta_Bin = new RooBinning(1.5,5,"ETA");
  RooBinning* nTrk_Bin = new RooBinning(0,500,"nTrack");
  
  Mom_Bin->addBoundary(9300); // R1 Kaon Threshold
  Mom_Bin->addBoundary(17675);// R1 Proton Threshold
  Mom_Bin->addBoundary(15600);// R2 Kaon Threshold
  Mom_Bin->addBoundary(20000);
  Mom_Bin->addBoundary(23000);
  Mom_Bin->addBoundary(26000);
  Mom_Bin->addBoundary(29650);// R2 Proton Threshold
  //Mom_Bin->addUniform(10, 30000, 100000);  
  
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
  //BinSchema.push_back(nTrk_Bin);

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
  RooRealVar BMass("Bu_DPVCFIT_M", "", 5279.17-50.0, 5279.17+50.0, "MeV/c^{2}");
  RooRealVar DMass("D0_M", "", 1864.83-25.0, 1864.83+25.0, "MeV/c^{2}");
  RooRealVar BDT("BDT", "", 0.92, 1.0, "");
  RooRealVar BBkgCat("Bu_BKGCAT", "", -1, 1);

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

  EvtTrackDataSet* Sig_DataSet = new EvtTrackDataSet( "B->DK Kaon",
                                                      "Signal Track",
                                                      t_Sig,
                                                      Vars,
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
                                        ).Data()  );
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
  ws->import(*ANDPion_Sig_DataSet, Rename("ANDPion_Sig_Kaon"));
  ws->import(*ANDKaon_Sig_DataSet, Rename("ANDKaon_Sig_Kaon"));
  ws->import(*Weighted_PionBin, Rename("CalPion"));
  ws->import(*Weighted_KaonBin, Rename("CalKaon"));
  ws->writeToFile( (TString("EvtMCKaon_" + 
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

