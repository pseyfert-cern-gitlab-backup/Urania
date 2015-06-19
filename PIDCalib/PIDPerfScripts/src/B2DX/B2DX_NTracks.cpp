// $Id: $
// Include files
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "TCut.h"
#include "RooWorkspace.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"

#include <list>
//-----------------------------------------------------------------------------
// Implementation file for class : NtracksComp
//
// 2011-11-13 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------
using namespace RooFit;

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <reco_version> <polarity> <d0_finalstate> <dataset_index> "<<std::endl;
  std::cout << "\t<reco_version> is the reconstruction version used to process the data (10/11)"<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<d0_finalstate> is one of (Kpi/K3pi/KK/pipi)"<<std::endl;
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
  else
    return EXIT_FAILURE;

  TFile* f_Kaon = TFile::Open(TString::Format("$CALIBDATASTORE/Reco%s_DATA/Mag%s/DSt_K_Mag%s_Strip%s_%s.root", 
                                              argv[1],
                                              argv[2],
                                              argv[2],
                                              StripVersion.c_str(),
                                              argv[4]).Data());
  RooWorkspace* wsKaon = (RooWorkspace*)f_Kaon->Get("RSDStCalib");
  RooDataSet* Kaon_Data = (RooDataSet*)wsKaon->data( "data" );
  
  RooPlot* Cal_nTracks = ((RooRealVar*)wsKaon->var("nTracks"))->frame(0,600);

  RooDataSet* data_w = new RooDataSet(Kaon_Data->GetName(),
                                      Kaon_Data->GetTitle(),
                                      Kaon_Data,
                                      *Kaon_Data->get(),
                                      0,
                                      "nsig_sw");

  //=============================================================================
  // Obtain Signal Track Data
  //=============================================================================
  int SVsize = StripVersion.size();
  string StripVersion_Paolo = (strcmp(&(StripVersion.at(SVsize-1)),"b")!=0) ? 
    StripVersion : StripVersion.substr(0,StripVersion.size()-1);
  cout<<StripVersion_Paolo<<endl;

  TString path = "/data/lhcb/users/gandini/gangaOutput/workspace/gandini/"
    "LocalXML/Summer2011/nTuple_Oxford/data/28August2011/Stripping"+StripVersion_Paolo;
  
  TFile* f_Sig = TFile::Open(TString::Format(path+"/b2dpi_d2%s_%s.root",
                                             (ToLower(argv[3])).Data(),
                                             (ToLower(argv[2])).Data()).Data());
  TTree* t_Sig = (TTree*)f_Sig->Get("Bu2D0X");

  //=============================================================================
  // Create Instance of EvtTrackDataSet for Signal tracks which calibration 
  // tracks will be weighted to
  //=============================================================================
  RooRealVar Mom("Bach_P", "", 5000, 100000, "MeV/c");
  RooRealVar Pt("Bach_PT", "", 500, 10000, "MeV/c");
  RooRealVar Eta("Bach_TRACK_Eta", "", 1.5, 5.0, "");
  RooRealVar DLLK("Bach_PIDK", "", -150, 150, "");
  RooRealVar DLLp("Bach_PIDp", "", -150, 150, "");
  RooRealVar nTracks("nTracks", "", 0, 500);
  RooRealVar BMass("Bu_DPVCFIT_M_RESC", "", 5278.83-50.0, 5278.83+50.0, "MeV/c^{2}");
  RooRealVar DMass("D0_M_RESC", "", 1864.78-25.0, 1864.78+25.0, "MeV/c^{2}");
  RooRealVar DFlightDist("D0_FD_ZSIG", "", 0, 100000);
  RooRealVar BuL0Had_TOS("BuL0HadronDecision_TOS", "", -1, 2);
  RooRealVar BuL0Glo_TIS("BuL0Global_TIS", "", -1, 2);
  RooRealVar BuHltTop2_TOS("BuHlt2Topo2BodyBBDTDecision_TOS", "", -1, 2);
  RooRealVar BuHltTop3_TOS("BuHlt2Topo3BodyBBDTDecision_TOS", "", -1, 2);
  RooRealVar BuHltTop4_TOS("BuHlt2Topo4BodyBBDTDecision_TOS", "", -1, 2);
  RooRealVar DMass_MisIDVETO("D0_M_DOUBLESW", "", 0, 5500, "MeV/c^{2}");

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
  SigVars.add(BuL0Had_TOS);
  SigVars.add(BuL0Glo_TIS);
  SigVars.add(BuHltTop2_TOS);
  SigVars.add(BuHltTop3_TOS);
  SigVars.add(BuHltTop4_TOS);
  
  string L0TriggerReq  = "(BuL0HadronDecision_TOS==1 || BuL0Global_TIS==1)";
  string HLTTriggerReq = "(BuHlt2Topo2BodyBBDTDecision_TOS==1 || "
    "BuHlt2Topo3BodyBBDTDecision_TOS==1 || "
    "BuHlt2Topo4BodyBBDTDecision_TOS==1)";
  string TriggerReq = L0TriggerReq+"&&"+HLTTriggerReq;
  string DoubleSwap = "abs(D0_M_DOUBLESW-1864.78)>15.0";
  string Cuts = (strcmp(argv[3],"kpi")!=0) ? TriggerReq+"&&"+DoubleSwap : TriggerReq;

  RooDataSet* Sig_DataSet = new RooDataSet( "B->DPi Pion",
                                            "Signal Track",
                                            t_Sig,
                                            SigVars,                                          
                                            Cuts.c_str());
  const RooArgSet* SigDataVars = Sig_DataSet->get(0);
  RooPlot* Sig_nTracks = ((RooRealVar*)SigDataVars->find("nTracks"))->frame(0,600);
  
  TCanvas* canvas_NTrks = new TCanvas("No. Tracks", "", 800, 600);
  data_w->plotOn(Cal_nTracks, DataError(RooAbsData::SumW2), LineColor(kRed),  MarkerColor(kRed), Binning(60)) ;
  (Cal_nTracks->GetYaxis())->SetRangeUser(1,800000);
  Sig_DataSet->plotOn(Sig_nTracks, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(60)) ;
  (Sig_nTracks->GetYaxis())->SetRangeUser(1,800000);
  canvas_NTrks->cd();
  Cal_nTracks->Draw();
  Sig_nTracks->Draw("same");
  canvas_NTrks->SetLogy(1);

  canvas_NTrks->SaveAs("Test.eps");

  delete canvas_NTrks;
  
  delete Sig_DataSet;
  
  delete data_w;

  return EXIT_SUCCESS;
}

//=============================================================================
