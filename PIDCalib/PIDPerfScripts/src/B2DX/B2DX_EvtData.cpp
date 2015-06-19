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
#include "TCanvas.h"
#include "RooPlot.h"

// Boost
#include <boost/lexical_cast.hpp>

using namespace RooFit;

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <reco_version> <polarity> <d0_finalstate> <dataset_index> "<<std::endl;
  std::cout << "\t<reco_version> is the reconstruction version used to process the data (10/11)"<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<d0_finalstate> is one of (kpi/kk/pipi)"<<std::endl;
  std::cout << "\t<dataset_index> is one of (0/1/2/..)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Reco Version (10,11,..)
  // 2: Field Orientation (Up/Down)
  // 3: D0 Final State (kpi,k3pi,kk)
  // 4: Calib. Data index
  if (argc != 5)
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

  //=============================================================================
  // Obtain Calibration Samples
  //=============================================================================
   
  TFile* f_Pion = TFile::Open(TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_Pi_Mag%s_Strip%s_%s.root", 
                                              argv[1],
                                              argv[2],
                                              argv[2],
                                              StripVersion.c_str(),
                                              argv[4]).Data());
  RooWorkspace* wsPion = (RooWorkspace*)f_Pion->Get("RSDStCalib");
  RooDataSet* Pion_Data = (RooDataSet*)wsPion->data( "data" );

  TFile* f_Kaon = TFile::Open(TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_K_Mag%s_Strip%s_%s.root", 
                                              argv[1],
                                              argv[2],
                                              argv[2],
                                              StripVersion.c_str(),
                                              argv[4]).Data());
  RooWorkspace* wsKaon = (RooWorkspace*)f_Kaon->Get("RSDStCalib");
  RooDataSet* Kaon_Data = (RooDataSet*)wsKaon->data( "data" );
 
  //=============================================================================
  // Obtain Signal Track Data
  //=============================================================================
  int SVsize = StripVersion.size();
  string StripVersion_Paolo = (strcmp(&(StripVersion.at(SVsize-1)),"b")!=0) ? 
    StripVersion : StripVersion.substr(0,StripVersion.size()-1);
  cout<<StripVersion_Paolo<<endl;
  
  //  TString path = "/data/lhcb/users/gandini/gangaOutput/workspace/gandini/"
  //  "LocalXML/Summer2011/nTuple_Oxford/data/28August2011/Stripping"+StripVersion_Paolo;
  
  TString path = "/data/lhcb/users/gandini/gangaOutput/workspace/gandini/LocalXML/Paper/Stripping17/TMVA";

  TFile* f_Sig = TFile::Open(TString::Format(path+"/b2dpi_d2%s_%s.root",
                                             (ToLower(argv[3])).Data(),
                                             (ToLower(argv[2])).Data()).Data());
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
  RooRealVar BMass("Bu_DPVCFIT_M_RESC", argv[3], 5278.83-50.0, 5278.83+50.0, "MeV/c^{2}");
  RooRealVar DMass("D0_M_RESC", "", 1864.78-25.0, 1864.78+25.0, "MeV/c^{2}");
  RooRealVar DFlightDist("D0_FD_ZSIG", "", 0, 100000);
  RooRealVar BuL0Had_TOS("BuL0HadronDecision_TOS", "", -1, 2);
  RooRealVar BuL0Glo_TIS("BuL0Global_TIS", "", -1, 2);
  RooRealVar BuHltTop2_TOS("BuHlt2Topo2BodyBBDTDecision_TOS", "", -1, 2);
  RooRealVar BuHltTop3_TOS("BuHlt2Topo3BodyBBDTDecision_TOS", "", -1, 2);
  RooRealVar BuHltTop4_TOS("BuHlt2Topo4BodyBBDTDecision_TOS", "", -1, 2);
  RooRealVar DMass_MisIDVETO("D0_M_DOUBLESW", "", 0, 10000, "MeV/c^{2}");
  RooRealVar JPSI_VETO("jpsi_veto_raw", "", 0, 7000);

  double BDT_min;
  string DDaught1_name;
  string DDaught2_name;
  double DDaught1_DLLKmin, DDaught1_DLLKmax;
  double DDaught2_DLLKmin, DDaught2_DLLKmax;
  if(strcmp(argv[3],"kpi")==0)
  {
    cout<<"In kpi Cuts"<<endl;
    BDT_min = 0.92;
    DDaught1_name = "K_PIDK";
    DDaught2_name = "P_PIDK";
    DDaught1_DLLKmin = 2.0;
    DDaught2_DLLKmin = -200.0;
    DDaught1_DLLKmax = 200.0;
    DDaught2_DLLKmax = 2.0;
  }
  else if(strcmp(argv[3],"kk")==0)
  {
    cout<<"In kk Cuts"<<endl;
    BDT_min = 0.80;
    DDaught1_name = "K0_PIDK";
    DDaught2_name = "K1_PIDK";
    DDaught1_DLLKmin = 2.0;
    DDaught2_DLLKmin = 2.0;
    DDaught1_DLLKmax = 200.0;
    DDaught2_DLLKmax = 200.0;
  }
  else if(strcmp(argv[3],"pipi")==0)
  {
    cout<<"In pipi Cuts"<<endl;
    BDT_min = 0.80;
    DDaught1_name = "P0_PIDK";
    DDaught2_name = "P1_PIDK";
    DDaught1_DLLKmin = -200.0;
    DDaught2_DLLKmin = -200.0;
    DDaught1_DLLKmax = 2.0;
    DDaught2_DLLKmax = 2.0;
  }
  else
    return EXIT_FAILURE;

  cout<<argv[3]<<'\t'<<BDT_min<<'\t'<<DDaught1_name<<'\t'<<DDaught2_name<<'\t'
      <<DDaught1_DLLKmin<<'\t'<<DDaught1_DLLKmax<<'\t'
      <<DDaught2_DLLKmin<<'\t'<<DDaught2_DLLKmax<<'\t'<<endl;

  RooRealVar BDT("BDT", "", BDT_min, 1.0, "");
  RooRealVar DDaught1_DLLK( DDaught1_name.c_str(), "", DDaught1_DLLKmin, DDaught1_DLLKmax);
  RooRealVar DDaught2_DLLK( DDaught2_name.c_str(), "", DDaught2_DLLKmin, DDaught2_DLLKmax);
  
  RooArgSet SigVars(Mom,
                    Pt,
                    Eta,
                    DLLK,
                    DLLp,
                    nTracks,
                    BMass,
                    DMass,
                    BDT);
  SigVars.add(DFlightDist);
  SigVars.add(DDaught1_DLLK);
  SigVars.add(DDaught2_DLLK);
  SigVars.add(DMass_MisIDVETO);
  SigVars.add(JPSI_VETO);
  SigVars.add(BuL0Had_TOS);
  SigVars.add(BuL0Glo_TIS);
  SigVars.add(BuHltTop2_TOS);
  SigVars.add(BuHltTop3_TOS);
  SigVars.add(BuHltTop4_TOS);
  
  string L0TriggerReq  = "(BuL0HadronDecision_TOS || BuL0Global_TIS)==1";
  string HLTTriggerReq = "(BuHlt2Topo2BodyBBDTDecision_TOS || "
    "BuHlt2Topo3BodyBBDTDecision_TOS || "
    "BuHlt2Topo4BodyBBDTDecision_TOS)==1";
  string TriggerReq = L0TriggerReq+"&&"+HLTTriggerReq;
  string DoubleSwap = "abs(D0_M_DOUBLESW-1864.78)>15.0";
  string JPsiVeto = "abs(jpsi_veto_raw - 1864.78)>22.0";
  string Cuts = (strcmp(argv[3],"kpi")==0) ? TriggerReq+"&&"+JPsiVeto+"&&"+DoubleSwap : TriggerReq+"&&"+JPsiVeto;
  cout<<Cuts<<endl;

  EvtTrackDataSet* Sig_DataSet = new EvtTrackDataSet( "B->DPi Pion",
                                                      "Signal Track",
                                                      t_Sig,
                                                      SigVars,
                                                      "Bach_P",
                                                      "Bach_PT",
                                                      "Bach_TRACK_Eta",
                                                      "nTracks",
                                                      "Bach_PIDK",
                                                      "Bach_PIDp",
                                                      Cuts );
  const RooArgSet* SigDataVars = Sig_DataSet->get(0);
  Sig_DataSet->Print("v");
  RooPlot* Sig_Plot = ((RooRealVar*)SigDataVars->find("Bu_DPVCFIT_M_RESC"))->frame(5100,5700);
  Sig_DataSet->plotOn(Sig_Plot, 
                      LineColor(kBlue),  
                      MarkerColor(kBlue), 
                      Binning(70)) ;
  TCanvas* canvas_Mass = new TCanvas("Mass", argv[3], 800, 600);
  canvas_Mass->cd();
  Sig_Plot->Draw();
  canvas_Mass->SaveAs((TString::Format("Mass_%s_%s_%s.eps", 
                                       argv[2], 
                                       argv[3],
                                       argv[4])).Data());
  delete Sig_Plot;
  delete canvas_Mass;
  
  //=============================================================================
  // Pion - Declare Instance of EvtTrackDataSet for Calibration tracks within BinSchema
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

  Pion_DataSet->Print("v");

  //=============================================================================
  // Create an Instnace of WeightDataSetTool for the Pion Tracks
  //=============================================================================
  WeightDataSetTool<EvtTrackDataSet>* WeightPion = 
    new WeightDataSetTool<EvtTrackDataSet>( Sig_DataSet,
                                            Pion_DataSet,
                                            BinSchema );
  
  //=============================================================================
  // Pion - Make a Copy of the Signal DataSet with Events Only in those Bins that 
  // Contained Pion Calibration Tracks
  //=============================================================================
  //EvtTrackDataSet* ANDPion_Sig_DataSet =  
  //  (EvtTrackDataSet*)WeightPion->ANDInBins("nsig_sw",
  //                                          "");
  //ANDPion_Sig_DataSet->printValue(cout);
  //cout<<endl;
  
  //=============================================================================
  // Pion - Create a 'Bin' Weighted Copy of Pion_DataSet 
  //=============================================================================
  EvtTrackDataSet* Weighted_PionBin = 
    (EvtTrackDataSet*)WeightPion->WeightInBins("Wgt",
                                               kTRUE,
                                               "",
                                               "nsig_sw");

  delete WeightPion;
  delete Pion_DataSet;

  Weighted_PionBin->get(0);
  Weighted_PionBin->Print("v");

  //=============================================================================
  // Pion - Weight with New Weight Variable 
  //=============================================================================
  //EvtTrackDataSet* Weighted_PionBin_sw = new EvtTrackDataSet("Test",
  //                                                           "",
  //                                                           Weighted_PionBin,
  //                                                          *Weighted_PionBin->get(),
  //                                                           "",
  //                                                          "nsig_sw");

  //cout<<Weighted_PionBin_sw->isWeighted()<<endl;
  //Weighted_PionBin_sw->printValue(cout);
  //cout<<endl;
  //delete Weighted_PionBin_sw;
  
  //EvtTrackDataSet* Weighted_PionBin_wgt = new EvtTrackDataSet("Test",
  //                                                            "",
  //                                                            Weighted_PionBin,
  //                                                            *Weighted_PionBin->get(),
  //                                                            "",
  //                                                            "Wgt");

  //cout<<Weighted_PionBin_wgt->isWeighted()<<endl;
  //Weighted_PionBin_wgt->printValue(cout);
  //cout<<endl;

  //delete Weighted_PionBin_wgt;

  //=============================================================================
  // Kaon - Declare Instance of EvtTrackDataSet for Calibration tracks within BinSchema
  //=============================================================================
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

  Kaon_DataSet->Print("v");
 
  //=============================================================================
  // Create an Instnace of WeightDataSetTool for the Kaon Tracks
  //=============================================================================
  WeightDataSetTool<EvtTrackDataSet>* WeightKaon = 
    new WeightDataSetTool<EvtTrackDataSet>( Sig_DataSet,
                                            Kaon_DataSet,
                                            BinSchema );
  
  //=============================================================================
  // Koan - Make a Copy of the Signal DataSet with Events Only in those Bins that 
  // Contained Kaon Calibration Tracks
  //=============================================================================
  //EvtTrackDataSet* ANDKaon_Sig_DataSet =  
  //  (EvtTrackDataSet*)WeightKaon->ANDInBins("nsig_sw",
  //                                          "");
  
  //ANDKaon_Sig_DataSet->printValue(cout);
  //cout<<endl;

  //=============================================================================
  // Kaon - Create a 'Bin' Weighted Copy of Kaon_DataSet
  //=============================================================================  
  EvtTrackDataSet* Weighted_KaonBin = 
    (EvtTrackDataSet*)WeightKaon->WeightInBins("Wgt",
                                               kTRUE,
                                               "",
                                               "nsig_sw");
  delete WeightKaon;
  delete Kaon_DataSet;
  delete Sig_DataSet;

  Weighted_KaonBin->get(0);
  Weighted_KaonBin->Print("v");

  //=============================================================================
  // Koan - Weight with New Weight Variable 
  //=============================================================================
  //EvtTrackDataSet* Weighted_KaonBin_sw = new EvtTrackDataSet("Test",
  //                                                           "",
  //                                                           Weighted_KaonBin,
  //                                                           *Weighted_KaonBin->get(),
  //                                                           "",
  //                                                           "nsig_sw");

  //cout<<Weighted_KaonBin_sw->isWeighted()<<endl;
  //Weighted_KaonBin_sw->printValue(cout);
  //cout<<endl;
  //delete Weighted_KaonBin_sw;

  //EvtTrackDataSet* Weighted_KaonBin_wgt = new EvtTrackDataSet("Test",
  //                                                            "",
  //                                                            Weighted_KaonBin,
  //                                                            *Weighted_KaonBin->get(),
  //                                                            "",
  //                                                            "Wgt");

  //cout<<Weighted_KaonBin_wgt->isWeighted()<<endl;
  //Weighted_KaonBin_wgt->printValue(cout);
  //cout<<endl;

  //delete Weighted_KaonBin_wgt;
  
  //=============================================================================
  // Write to File within a RooWorkspace
  //=============================================================================
  TString FileOut = "EvtData_" + 
    boost::lexical_cast<std::string>(Mom_Bin->numBins()) +
    "Momx" + 
    boost::lexical_cast<std::string>(Eta_Bin->numBins()) +
    "Etax" +
    boost::lexical_cast<std::string>(nTrk_Bin->numBins()) +
    "nTrk_%s_%s_%s_%s.root";

  //RooWorkspace* ws_Sig = new RooWorkspace("ws","");
  //ws_Sig->import(*ANDPion_Sig_DataSet, Rename("ANDPion_Sig_Pion"));
  //delete ANDPion_Sig_DataSet;
  //ws_Sig->import(*ANDKaon_Sig_DataSet, Rename("ANDKaon_Sig_Pion"));
  //delete ANDKaon_Sig_DataSet;
  
  //ws_Sig->writeToFile(TString::Format(FileOut.Data(),
  //                                    "Sig",
  //                                    argv[1], 
  //                                    argv[2], 
  //                                    argv[3]).Data());
  //delete ws_Sig;
  
  RooWorkspace* ws_CalPion = new RooWorkspace("ws","");
  ws_CalPion->import(*Weighted_PionBin, Rename("CalPion"));
  delete Weighted_PionBin;
  
  RooWorkspace* ws_CalKaon = new RooWorkspace("ws","");
  ws_CalKaon->import(*Weighted_KaonBin, Rename("CalKaon"));
  delete Weighted_KaonBin;
  
  ws_CalPion->writeToFile(TString::Format(FileOut.Data(),
                                          "CalPion",
                                          argv[2], 
                                          argv[3], 
                                          argv[4]).Data());

  delete ws_CalPion;

  ws_CalKaon->writeToFile(TString::Format(FileOut.Data(),
                                          "CalKaon",
                                          argv[2], 
                                          argv[3], 
                                          argv[4]).Data());

  delete ws_CalKaon;
  
  delete Mom_Bin;
  delete Pt_Bin;
  delete Eta_Bin;
  delete nTrk_Bin;
  
  return EXIT_SUCCESS;
  
}

