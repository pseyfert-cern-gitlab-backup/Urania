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


int main()
{

  //A simple example of the usage of the Performance Histogram creation for use
  //with the MultiTrack PID calibration methods.
  //Should work 'out the box'...
  
  gSystem->Load("libRooStats.so");

  //=============================================================================
  // Obtain Calibration Sample
  //=============================================================================
  TFile* f_Pion = 0;
  f_Pion = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagUp/DSt_Pi_MagUp_Strip17_0.root");
  RooWorkspace* wsPion = (RooWorkspace*)f_Pion->Get("RSDStCalib");
  RooDataSet* Pion_Data = (RooDataSet*)wsPion->data( "data" );    

  //=============================================================================
  // Declare Binning Variables (RooBinnings)
  //=============================================================================
  RooBinning* Mom_Bin = new RooBinning(5000,100000,"P");
  RooBinning* Pt_Bin = new RooBinning(500,10000,"PT");
  RooBinning* Eta_Bin = new RooBinning(1.5,5,"ETA");
  RooBinning* nTrk_Bin = new RooBinning(0,500,"nTrack");


  //same binning for B2D0Pi and Donal
  Mom_Bin->addBoundary(9300); // R1 Kaon Threshold
  Mom_Bin->addBoundary(15600);// R2 Kaon Threshold
  Mom_Bin->addUniform(15, 19000, 100000);  
  
  Eta_Bin->addUniform(4, 1.5, 5);
  nTrk_Bin->addBoundary(50);
  nTrk_Bin->addBoundary(200);
  nTrk_Bin->addBoundary(300);
    
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
  // Declare Instance of TrackDataSet for Calibration tracks within BinSchema
  //=============================================================================
  //EvtTrackDataSet for use with the B2D0Pi_D02KPi
  EvtTrackDataSet* Pion_DataSetAll_B2DX = 
    new EvtTrackDataSet("Calib. Pion",
                        "",
                        Pion_Data,
                        *(Pion_Data->get()),
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
                                        ).Data(),
                        "nsig_sw");//specify sWeight as weight variable here to ensure no residual background in perf hist

  EvtTrackDataSet* Pion_DataSet_B2DX = (EvtTrackDataSet*) Pion_DataSetAll_B2DX->SetInBinSchema(BinSchema);
  delete Pion_DataSetAll_B2DX;
  //printing dataset after all cuts (which are the bounds of the binnings (see above)
  Pion_DataSet_B2DX->get(0);
  Pion_DataSet_B2DX->Print("v");

  //=============================================================================
  // Make the perfHist
  //=============================================================================
  MultiPerfCalculator<EvtTrackDataSet>* CalcPion_B2DX = new MultiPerfCalculator<EvtTrackDataSet>( Pion_DataSet_B2DX );

  //histograms produced with the structure for saving sum of squares of weights errors
  TH1::SetDefaultSumw2(kTRUE);
  
  std::vector<TH1*> histvec 
    = CalcPion_B2DX->Many_Perf_Hists("Pion",//prefix to name of the histogram
                                     CalcPion_B2DX->RangeOfCuts("DLLK<5",0),//range of pid cuts, 
                                     //second parameter is (half)range. returns a vector of strings e.g.
                                     //CalcPion_B2DX->RangeOfCuts("DLLK<5",1); would return {"DLLK<4","DLLK<5","DLLK<6"}
                                     BinSchema,//binning to use for the histogram
                                     kFALSE,//rejectNonNormalBins
                                     5);//minEntries
  //printVals set to kTRUE by the Perf_Hist function
  
  //=============================================================================
  // Write Histogram to File
  //=============================================================================
  TFile * outFile = new TFile("PerfHist_Pions_MagUp_index0_DLLK5.root","recreate");
  outFile->cd();
  for (std::vector<TH1*>::iterator hist = histvec.begin();
       hist != histvec.end(); hist++){

    //when histograms are TH1::Add-ed a weighted average is taken
    (*hist)->SetBit(TH1::kIsAverage);
    
    if(!(*hist)->GetDefaultSumw2()) std::cout << "WARNING: Sumw2 errors not present." << std::endl;
    
    (*hist)->Write();
    delete *hist;
  }
  outFile->Close();

  delete Pion_DataSet_B2DX;
  
  delete CalcPion_B2DX;
  
  delete Mom_Bin;
  delete Pt_Bin;
  delete Eta_Bin;
  delete nTrk_Bin;

  delete outFile;
  
  return 0;
  
}
