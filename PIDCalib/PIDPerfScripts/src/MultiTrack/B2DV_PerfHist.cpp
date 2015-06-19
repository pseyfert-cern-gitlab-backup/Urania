// $Id: $
// Include files 
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/MultiPerfCalculator.h"
#include "PIDPerfTools/WeightDataSetTool.h"
#include "TFile.h"
#include "TTree.h"
#include "TH3F.h"
#include "TChain.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "TCut.h"
#include "RooWorkspace.h"
#include <list>
#include <sstream>
#include <map>

// Boost
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace RooFit;
using std::cout;
using std::endl;

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <reco_version> <polarity> <dataset_index> <Mode> <Data/MC>"<<std::endl;
  std::cout << "\t<reco_version> is the reconstruction version used to process the data (10/11/12)"<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<dataset_index> is one of (0/1/2/..)"<<std::endl;
  std::cout << "\t<Mode> is the signal mode." << std::endl;
  std::cout << "\t<Data/MC> is this 'Data' or 'MC'?" << std::endl;
  
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Reco Version (10,11,..)
  // 2: Field Orientation (Up/Down)
  // 3: Calib. Data index
  // 4: Signal Mode
  // 5: Data or MC?
  if (argc != 6)
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
  std::string Mode = argv[4];
  std::string polarity = argv[2];
  std::string dataset_index = argv[3];
  std::string data = argv[5];
  bool Data;
  if (data=="Data") Data = true;
  else if (data=="MC") Data = false;
  else return EXIT_FAILURE;

  //dataset_index is meaningless in the case of MC

  //=============================================================================
  // Obtain Calibration Samples
  //=============================================================================
  TFile* f_Pion = 0;
  if(Data) f_Pion = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_Pi_Mag%s_Strip%s_%s.root",
                                                 argv[1],
                                                 argv[2],
                                                 argv[2],
                                                 StripVersion.c_str(),
                                                 argv[3])).Data()
                                );

  else f_Pion = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_MC11a/Mag%s/DSt_Pi_Mag%s_Strip%sMC11a_0.root",
                                             argv[1],
                                             argv[2],
                                             argv[2],
                                             StripVersion.c_str())).Data()
                            );
  RooWorkspace* wsPion = (RooWorkspace*)f_Pion->Get("RSDStCalib");
  RooDataSet* Pion_Data = (RooDataSet*)wsPion->data( "data" );
  TFile * f_Kaon = 0;
  
  if(Data) f_Kaon = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_K_Mag%s_Strip%s_%s.root",
                                                 argv[1],
                                                 argv[2],
                                                 argv[2],
                                                 StripVersion.c_str(),
                                                 argv[3])).Data()                                              
                                );
  else f_Kaon = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_MC11a/Mag%s/DSt_K_Mag%s_Strip%sMC11a_0.root",
                                             argv[1],
                                             argv[2],
                                             argv[2],
                                             StripVersion.c_str())).Data()                                              
                            );
  RooWorkspace* wsKaon = (RooWorkspace*)f_Kaon->Get("RSDStCalib");
  RooDataSet* Kaon_Data = (RooDataSet*)wsKaon->data( "data" );

  //proton calibration sample
  //NB there is no MC version so the histograms will be the same in the files labelled Data and MC!
  TFile * f_Proton = 0;

  f_Proton = TFile::Open((TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/Lam0_P_Mag%s_Strip%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[2],
                                          StripVersion.c_str(),
                                          argv[3])).Data()                                              
                         );
  RooWorkspace* wsProton = (RooWorkspace*)f_Proton->Get("Lam0Calib");
  RooDataSet* Proton_Data = (RooDataSet*)wsProton->data( "data" );
  
  //=============================================================================
  // Obtain Signal Track Data
  //=============================================================================
  //A Map of signal tracks to their types and cuts
  typedef std::pair<std::string,std::string> Pear;
  std::map<std::string,Pear> SignalTracks;
  
  if (strcmp(argv[4],"B02D0Kstar_D02KK")==0){
    SignalTracks["D0KPlus"] = Pear("K","DLLK>0");
    SignalTracks["D0KMinus"] = Pear("K","DLLK>0");
    SignalTracks["KstarK"] = Pear("K","DLLK>3&&DLLpK<10");
    SignalTracks["KstarPi"] = Pear("Pi","DLLK<3");
  }
  else if (strcmp(argv[4],"B02D0Kstar_D02PiPi")==0){
    SignalTracks["D0PiPlus"] = Pear("Pi","DLLK<4");
    SignalTracks["D0PiMinus"] = Pear("Pi","DLLK<4");
    SignalTracks["KstarK"] = Pear("K","DLLK>3&&DLLpK<10");
    SignalTracks["KstarPi"] = Pear("Pi","DLLK<3");
  }
  else if (strcmp(argv[4],"B02D0Kstar_D02KPi")==0){
    SignalTracks["D0K"] = Pear("K","DLLK>0");
    SignalTracks["D0Pi"] = Pear("Pi","DLLK<4");
    SignalTracks["KstarK"] = Pear("K","DLLK>3&&DLLpK<10");
    SignalTracks["KstarPi"] = Pear("Pi","DLLK<3");
  }
  else if (strcmp(argv[4],"B2D0Pi_D02KPi")==0){
    SignalTracks["Bach"] = Pear("Pi","DLLK<0");
  }
  else if (strcmp(argv[4],"Lb2D0pPi_D02KPi")==0){
    //this is the case where the Lb2D0(KPi)pPi is mis-ID'd as B02D0(KPi)Kstar
    //so everything is the same apart from the id of the KstarK is changed to a proton
    //because this is the track that is mis-ID'd
    SignalTracks["D0K"] = Pear("K","DLLK>0");
    SignalTracks["D0Pi"] = Pear("Pi","DLLK<4");
    SignalTracks["KstarK"] = Pear("P","DLLK>3&&DLLpK<10");
    SignalTracks["KstarPi"] = Pear("Pi","DLLK<3");
  }
  else if (strcmp(argv[4],"B02D0Phi_D02KPi")==0){
    SignalTracks["D0K"] = Pear("K","DLLK>0");
    SignalTracks["D0Pi"] = Pear("Pi","DLLK<4");
    SignalTracks["PhiKPlus"] = Pear("K","DLLK>3");
    SignalTracks["PhiKMinus"] = Pear("K","DLLK>3");
  }
  else 
    return EXIT_FAILURE;

  //=============================================================================
  // Declare Binning Variables (RooBinnings)
  //=============================================================================
  RooBinning* Mom_Bin = new RooBinning(0,200000,"P");
  if (Mode=="B2D0Pi_D02KPi") Mom_Bin = new RooBinning(5000,100000,"P");
  RooBinning* Pt_Bin = new RooBinning(0,20000,"PT");
  if (Mode=="B2D0Pi_D02KPi") Pt_Bin = new RooBinning(500,10000,"PT");
  RooBinning* Eta_Bin = new RooBinning(1.5,5,"ETA");
  RooBinning* nTrk_Bin = new RooBinning(0,500,"nTrack");
  if (Mode!="B2D0Pi_D02KPi"&&Mode!="Donal"){    
    Mom_Bin->addBoundary(9300); // R1 Kaon Threshold
    Mom_Bin->addBoundary(17675);// R1 Proton Threshold
    Mom_Bin->addBoundary(15600);// R2 Kaon Threshold
    Mom_Bin->addBoundary(20000);
    Mom_Bin->addBoundary(23000);
    Mom_Bin->addBoundary(26000);
    Mom_Bin->addBoundary(29650);// R2 Proton Threshold
    Mom_Bin->addUniform(17, 30000, 200000);  
    Eta_Bin->addUniform(4, 1.5, 5);
  }
  else{
    //same binning for B2D0Pi and Donal
    Mom_Bin->addBoundary(9300); // R1 Kaon Threshold
    Mom_Bin->addBoundary(15600);// R2 Kaon Threshold
    Mom_Bin->addUniform(15, 19000, 100000);  
  
    Eta_Bin->addUniform(4, 1.5, 5);
    nTrk_Bin->addBoundary(50);
    nTrk_Bin->addBoundary(200);
    nTrk_Bin->addBoundary(300);
  }
  
    
  //=============================================================================
  // Declare Binning Schema (vector<RooBinnings*>) for any number of bin
  // Dimensions
  //=============================================================================
  std::vector<RooBinning*> BinSchema;
  BinSchema.push_back(Mom_Bin);
  //BinSchema.push_back(Pt_Bin);
  BinSchema.push_back(Eta_Bin);
  if (Mode=="B2D0Pi_D02KPi") BinSchema.push_back(nTrk_Bin);
  
  std::vector<RooBinning*>::iterator iter =  BinSchema.begin();
  cout<<"========== Binning Schema =========="<<endl;
  for(;iter!=BinSchema.end();++iter) 
  {
    (*iter)->Print();
  }
  cout<<"===================================="<<endl;
 
  //=============================================================================
  // Declare Instance of TrackDataSet for Calibration tracks within BinSchema
  //=============================================================================
  //EvtTrackDataSet for use with the B2D0Pi_D02KPi
  EvtTrackDataSet* Pion_DataSetAll_B2DX = 
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
                                        //nTrk_Bin->lowBound(), nTrk_Bin->highBound()
                                        -1.0, nTrk_Bin->highBound()
                                        ).Data(),
                        "nsig_sw"
                        );

  EvtTrackDataSet* Pion_DataSet_B2DX = (EvtTrackDataSet*) Pion_DataSetAll_B2DX->SetInBinSchema(BinSchema);
  delete Pion_DataSetAll_B2DX;

  Pion_DataSet_B2DX->Print("v");


  TrackDataSet* Pion_DataSetAll = 0;
  TrackDataSet* Pion_DataSet = 0;
  TrackDataSet* Kaon_DataSetAll = 0;
  TrackDataSet* Kaon_DataSet = 0;
  TrackDataSet* Proton_DataSetAll = 0;
  TrackDataSet* Proton_DataSet = 0;

  if(Mode!="B2D0Pi_D02KPi"){
    Pion_DataSetAll = 
      new TrackDataSet("Calib. Pion",
                       "",
                       Pion_Data,
                       *Pion_Data->get(),
                       "Pi_P",
                       "Pi_PT",
                       "Pi_Eta",
                       "Pi_CombDLLK",
                       "Pi_CombDLLp",
                       TString::Format("Pi_P>%f && Pi_P<%f &&" 
                                       //                                     "Pi_PT>%f && Pi_PT<%f &&"
                                       "Pi_Eta>%f && Pi_Eta<%f",
                                       Mom_Bin->lowBound(), Mom_Bin->highBound(),
                                       //                                     Pt_Bin->lowBound(), Pt_Bin->highBound(),
                                       Eta_Bin->lowBound(), Eta_Bin->highBound()
                                       ).Data(),
                       "nsig_sw"
                       );


    Pion_DataSet = (TrackDataSet*) Pion_DataSetAll->SetInBinSchema(BinSchema);
    delete Pion_DataSetAll;
    std::cout << "Made Pion TrackDataSet" << std::endl;
    Kaon_DataSetAll =  
      new TrackDataSet("Calib. Kaon",
                       "",
                       Kaon_Data,
                       *Kaon_Data->get(),
                       "K_P",
                       "K_PT",
                       "K_Eta",
                       "K_CombDLLK",
                       "K_CombDLLp",
                       TString::Format("K_P>%f && K_P<%f &&" 
                                       //                                     "K_PT>%f && K_PT<%f &&"
                                       "K_Eta>%f && K_Eta<%f",
                                       Mom_Bin->lowBound(), Mom_Bin->highBound(),
                                       //                                     Pt_Bin->lowBound(), Pt_Bin->highBound(),
                                       Eta_Bin->lowBound(), Eta_Bin->highBound()                                 
                                       ).Data(),
                       "nsig_sw"
                       );
  

    Kaon_DataSet = (TrackDataSet*) Kaon_DataSetAll->SetInBinSchema(BinSchema);
    delete Kaon_DataSetAll;
    std::cout << "Made Kaon TrackDataSet" << std::endl;

    Proton_DataSetAll =  
      new TrackDataSet("Calib. Proton",
                       "",
                       Proton_Data,
                       *Proton_Data->get(),
                       "P_P",
                       "P_PT",
                       "P_Eta",
                       "P_CombDLLK",
                       "P_CombDLLp",
                       TString::Format("P_P>%f && P_P<%f &&" 
                                       //                                     "P_PT>%f && P_PT<%f &&"
                                       "P_Eta>%f && P_Eta<%f",
                                       Mom_Bin->lowBound(), Mom_Bin->highBound(),
                                       //                                     Pt_Bin->lowBound(), Pt_Bin->highBound(),
                                       Eta_Bin->lowBound(), Eta_Bin->highBound()                                 
                                       ).Data(),
                       "nsig_sw"
                       );
  

    Proton_DataSet = (TrackDataSet*) Proton_DataSetAll->SetInBinSchema(BinSchema);
    delete Proton_DataSetAll;
    std::cout << "Made Proton TrackDataSet" << std::endl;

    Pion_DataSet->Print("v");
    Kaon_DataSet->Print("v");
    Proton_DataSet->Print("v");

  }
  delete Pion_Data;  
  delete Kaon_Data;
  delete Proton_Data;
  //=============================================================================
  // Make the perfHists
  //=============================================================================
  MultiPerfCalculator<TrackDataSet>* CalcKaon = new MultiPerfCalculator<TrackDataSet>( Kaon_DataSet );
  MultiPerfCalculator<TrackDataSet>* CalcPion = new MultiPerfCalculator<TrackDataSet>( Pion_DataSet );
  MultiPerfCalculator<EvtTrackDataSet>* CalcPion_B2DX = new MultiPerfCalculator<EvtTrackDataSet>( Pion_DataSet_B2DX );
  MultiPerfCalculator<TrackDataSet>* CalcProton = new MultiPerfCalculator<TrackDataSet>( Proton_DataSet );

  //histograms produced with the structure for saving sum of squares of weights errors
  TH1::SetDefaultSumw2(kTRUE);

  std::vector<TH1*> theHists;
  std::vector<TH1*> tempHists;  
  for (std::map<std::string,Pear>::iterator iter = SignalTracks.begin();
       iter !=SignalTracks.end(); iter++){
    std::cout << iter->first << std::endl;
    if (Mode=="B2D0Pi_D02KPi"){
      tempHists = CalcPion_B2DX->Many_Perf_Hists((iter->first).c_str(),
                                                 CalcPion_B2DX->RangeOfCuts(iter->second.second,8),
                                                 BinSchema,
                                                 kFALSE,
                                                 5); 
    }
    else if (iter->second.first=="K")
      tempHists = CalcKaon->Many_Perf_Hists((iter->first).c_str(),
                                            CalcKaon->RangeOfCuts(iter->second.second,5),
                                            BinSchema,
                                            kFALSE,
                                            5);
    else if (iter->second.first=="Pi") 
      tempHists = CalcPion->Many_Perf_Hists((iter->first).c_str(),
                                            CalcPion->RangeOfCuts(iter->second.second,5),
                                            BinSchema,
                                            kFALSE,
                                            5);
    else tempHists = CalcProton->Many_Perf_Hists((iter->first).c_str(),
                                                 CalcProton->RangeOfCuts(iter->second.second,5),
                                                 BinSchema,
                                                 kFALSE,
                                                 5);
    for(std::vector<TH1*>::iterator histIter = tempHists.begin();
        histIter != tempHists.end(); histIter++){
      theHists.push_back(*histIter);
    }
    tempHists.clear();
  } 
  //=============================================================================
  // Write Histograms to File
  //=============================================================================
  TFile * outFile = new TFile(("/data/lhcb/users/smithe/PIDCalib_2012/B2DV_PerfHists_Mag"+polarity+"_"+Mode+"_"+
                               boost::lexical_cast<std::string>(Mom_Bin->numBins()) +
                               "Momx" +
                               boost::lexical_cast<std::string>(Eta_Bin->numBins()) +
                               "Eta_index"+dataset_index+"_"+data+".root").c_str(),"recreate");
  outFile->cd();
  
  for (std::vector<TH1*>::iterator hist = theHists.begin();
       hist != theHists.end(); hist++){

    //when histograms are TH1::Add-ed a weighted average is taken
    (*hist)->SetBit(TH1::kIsAverage);
    
    if(!(*hist)->GetDefaultSumw2()) std::cout << "WARNING: Sumw2 errors not present." << std::endl;
    
    (*hist)->Write();
    delete *hist;
  }
  outFile->Close();
  
  delete Pion_DataSet;
  delete Pion_DataSet_B2DX;
  
  delete Kaon_DataSet;
  delete CalcKaon;
  delete CalcPion;
  delete CalcPion_B2DX;
  
  delete Mom_Bin;
  delete Pt_Bin;
  delete Eta_Bin;
  delete nTrk_Bin;
  
  delete outFile;
  
  return 0;
  
}
