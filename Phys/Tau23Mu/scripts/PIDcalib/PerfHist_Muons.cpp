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
            << "<polarity> <dataset_index> [<charge>]"<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<dataset_index> is one of (0, 1 or 2)"<<std::endl;
  std::cout << "\t<charge> is optional (Plus/Minus)" << std::endl;

  std::cout << "if no charge is given, the samples are so large, that you need to chose the right \"step\" in the code... sorry" << std::endl;
} 

int val(int step, int argc, char* argv[]);

//int main()
int main(int argc, char* argv[])
{
  //A simple example of the usage of the Performance Histogram creation for use
  //with the MultiTrack PID calibration methods.
  //Should work 'out the box'...
  if (argc != 3 && argc !=4)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  } 
  gSystem->Load("libRooStats.so");

  if (argc==4) {
  for (int v = 0 ; v < 4 ; ++v) {
    val(v, argc, argv);
  } }else {
    ///// MEMORY LEAK
    val(3, argc, argv);
  }
  
  return 0;
}


int val(int step, int argc, char* argv[])
{

  //=============================================================================
  // Obtain Calibration Sample
  //=============================================================================
  TFile* f_Muon = 0;
  if (3==argc) {
    f_Muon = TFile::Open((TString::Format("$CALIBDATASTORE/Reco12_DATA/Mag%s/Jpsi_Mu_Mag%s_Strip17_%s.root", argv[1], argv[1], argv[2])).Data());
    cout << TString::Format("$CALIBDATASTORE/Reco12_DATA/Mag%s/Jpsi_Mu_Mag%s_Strip17_%s.root", argv[1], argv[1], argv[2]) << endl;
  } else {
    f_Muon = TFile::Open((TString::Format("$CALIBDATASTORE/Reco12_DATA/Mag%s/Jpsi_Mu%s_Mag%s_Strip17_%s.root", argv[1], argv[3], argv[1], argv[2])).Data());
    cout << TString::Format("$CALIBDATASTORE/Reco12_DATA/Mag%s/Jpsi_Mu%s_Mag%s_Strip17_%s.root", argv[1], argv[3], argv[1], argv[2]) << endl;
  }
  //f_Muon = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagUp/Jpsi_Mu_MagUp_Strip17_0.root");
  //f_Muon = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagUp/Jpsi_Mu_MagUp_Strip17_1.root");
  //f_Muon = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagUp/Jpsi_Mu_MagUp_Strip17_2.root");
  //f_Muon = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagDown/Jpsi_Mu_MagDown_Strip17_0.root");
  //f_Muon = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagDown/Jpsi_Mu_MagDown_Strip17_1.root");
  //f_Muon = TFile::Open("$CALIBDATASTORE/Reco12_DATA/MagDown/Jpsi_Mu_MagDown_Strip17_2.root");
  RooWorkspace* wsMuon = (RooWorkspace*)f_Muon->Get("JpsiCalib");
  RooDataSet* Muon_Data = (RooDataSet*)wsMuon->data( "data" );    

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
  //Mom_Bin->addUniform(3, 19000, 100000);  
  Mom_Bin->addUniform(2, 19000, 100000);  
  
  //Eta_Bin->addUniform(4, 1.5, 5);
  Eta_Bin->addUniform(3, 1.5, 5);
  nTrk_Bin->addBoundary(50);
  nTrk_Bin->addBoundary(200);
  //nTrk_Bin->addBoundary(300);
    
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
  EvtTrackDataSet* Muon_DataSetAll = 
    new EvtTrackDataSet("Calib. Muon",
                        "",
                        Muon_Data,
                        *(Muon_Data->get()),
                        "Mu_P",
                        "Mu_PT",
                        "Mu_Eta",
                        "nTracks",
                        "Mu_ProbNNmu",
                        "Mu_CombDLLmu",
                        TString::Format("Mu_P>%f && Mu_P<%f &&" 
                                        "Mu_PT>%f && Mu_PT<%f &&"
                                        "Mu_Eta>%f && Mu_Eta<%f &&"
                                        "nTracks>%f && nTracks<%f",
                                        Mom_Bin->lowBound(), Mom_Bin->highBound(),
                                        Pt_Bin->lowBound(), Pt_Bin->highBound(),
                                        Eta_Bin->lowBound(), Eta_Bin->highBound(),
                                        nTrk_Bin->lowBound(), nTrk_Bin->highBound()
                                        ).Data(),
                        "nsig_sw");//specify sWeight as weight variable here to ensure no residual background in perf hist

  EvtTrackDataSet* Muon_DataSet = (EvtTrackDataSet*) Muon_DataSetAll->SetInBinSchema(BinSchema);
  delete Muon_DataSetAll;
  //printing dataset after all cuts (which are the bounds of the binnings (see above)
  Muon_DataSet->get(0);
  Muon_DataSet->Print("v");

  //=============================================================================
  // Make the perfHist
  //=============================================================================
  PerfCalculator<EvtTrackDataSet>* CalcMuon = new PerfCalculator<EvtTrackDataSet>( Muon_DataSet );
  TH1 * theHist = 0;
  float cutvalue;
  if (0==step) cutvalue = 0.27;
  if (1==step) cutvalue = 0.57;
  if (2==step) cutvalue = 0.75;
  if (3==step) cutvalue = 0.81;
  theHist = CalcMuon->Perf_Hist(TString::Format("ANN > %4.2f",cutvalue).Data(),//0.447",//"Muon_DLLmu > 1 & Muon_DLLmuk > 20",//name of the histogram
                                     TString::Format("Mu_ProbNNmu>%f",cutvalue).Data(),//"Mu_CombDLLmu>1 && (Mu_CombDLLmu - Mu_CombDLLK) > 20",//pid cut
                                     BinSchema,//binning to use for the histogram
                                     kFALSE,//rejectNonNormalBins
                                     5);//minEntries
  //printVals set to kTRUE by the Perf_Hist function
  
  //=============================================================================
  // Write Histogram to File
  //=============================================================================
  //TFile * outFile = new TFile("PerfHist_Muons_MagDown_index2_DLLmu1muk20.root","recreate");
  cutvalue *= 100;
  TFile * outFile;
  if (3==argc)
    outFile  = new TFile(TString::Format("PerfHist_Muons_Mag%s_index%s_ProbNN0%2.0f.root", argv[1], argv[2], cutvalue),"recreate");
  if (4==argc)
    outFile  = new TFile(TString::Format("PerfHist_Muons_%s_Mag%s_index%s_ProbNN0%2.0f.root", argv[3], argv[1], argv[2], cutvalue),"recreate");
  cout << TString::Format("PerfHist_Muons_Mag%s_index%s_ProbNN0%2.0f.root", argv[1], argv[2], cutvalue) << endl;
  outFile->cd();
  theHist->Write();
  outFile->Close();

  delete Muon_DataSet;
  
  delete CalcMuon;
  
  delete Mom_Bin;
  delete Pt_Bin;
  delete Eta_Bin;
  delete nTrk_Bin;
  
  delete theHist;
  delete outFile;
  
  return 0;
  
}
