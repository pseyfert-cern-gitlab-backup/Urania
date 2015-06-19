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
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Reco Version (10,11,..)
 if (argc != 2)
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

  gSystem->Load("libRooStats.so");

  const char* Polarity[] = {"Down","Up"};
  const char*Mode[] = {"kpi", "kk", "pipi"};

  TCanvas* canvas_Mass = new TCanvas("No. Tracks", "", 800, 600);
  RooPlot* Sig_nTracks[6];
  canvas_Mass->Divide(3,2);
  int i=0;
  for(int pol=0; pol<2; ++pol)
  {
    for(int mod=0; mod<3; ++mod)
    {
      
      //=============================================================================
      // Obtain Signal Track Data
      //=============================================================================
      int SVsize = StripVersion.size();
      string StripVersion_Paolo = (strcmp(&(StripVersion.at(SVsize-1)),"b")!=0) ? 
        StripVersion : StripVersion.substr(0,StripVersion.size()-1);
      cout<<StripVersion_Paolo<<endl;

      TString path = "/data/lhcb/users/gandini/gangaOutput/workspace/gandini/"
        "LocalXML/Summer2011/nTuple_Oxford/data/28August2011/Stripping"+StripVersion_Paolo;
  
      cout<<i<<'\t'<<StripVersion_Paolo<<'\t'<<Mode[mod]<<endl;

      TFile* f_Sig = TFile::Open(TString::Format(path+"/b2dpi_d2%s_%s.root",
                                                 Mode[mod],
                                                 (ToLower(Polarity[pol])).Data()).Data());
      TTree* t_Sig = (TTree*)f_Sig->Get("Bu2D0X");

      //=============================================================================
      // Create Instance of EvtTrackDataSet for Signal tracks which calibration 
      // tracks will be weighted to
      //=============================================================================
      RooRealVar Mom("Bach_P", Mode[mod], 5000, 100000, "MeV/c");
      RooRealVar Pt("Bach_PT", "", 500, 10000, "MeV/c");
      RooRealVar Eta("Bach_TRACK_Eta", "", 1.5, 5.0, "");
      RooRealVar DLLK("Bach_PIDK", "", -150, 150, "");
      RooRealVar DLLp("Bach_PIDp", "", -150, 150, "");
      RooRealVar nTracks("nTracks", "", 0, 500);
      RooRealVar BMass("Bu_DPVCFIT_M_RESC", Mode[mod], 5278.83-50.0, 5278.83+50.0, "MeV/c^{2}");
      RooRealVar DMass("D0_M_RESC", "", 1864.78-25.0, 1864.78+25.0, "MeV/c^{2}");
      RooRealVar DFlightDist("D0_FD_ZSIG", "", 0, 100000);
      RooRealVar BuL0Had_TOS("BuL0HadronDecision_TOS", "", -1, 2);
      RooRealVar BuL0Glo_TIS("BuL0Global_TIS", "", -1, 2);
      RooRealVar BuHltTop2_TOS("BuHlt2Topo2BodyBBDTDecision_TOS", "", -1, 2);
      RooRealVar BuHltTop3_TOS("BuHlt2Topo3BodyBBDTDecision_TOS", "", -1, 2);
      RooRealVar BuHltTop4_TOS("BuHlt2Topo4BodyBBDTDecision_TOS", "", -1, 2);
      RooRealVar DMass_MisIDVETO("D0_M_DOUBLESW", "", 0, 10000, "MeV/c^{2}");

      double BDT_min;
      string DDaught1_name;
      string DDaught2_name;
      double DDaught1_DLLKmin, DDaught1_DLLKmax;
      double DDaught2_DLLKmin, DDaught2_DLLKmax;
      if(strcmp(Mode[mod],"kpi")==0)
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
      else if(strcmp(Mode[mod],"kk")==0)
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
      else if(strcmp(Mode[mod],"pipi")==0)
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

      cout<<Mode[mod]<<'\t'<<BDT_min<<'\t'<<DDaught1_name<<'\t'<<DDaught2_name<<'\t'
          <<DDaught1_DLLKmin<<'\t'<<DDaught2_DLLKmin<<'\t'
          <<DDaught1_DLLKmax<<'\t'<<DDaught2_DLLKmax<<'\t'<<endl;

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
  
      string L0TriggerReq  = "(BuL0HadronDecision_TOS || BuL0Global_TIS)==1";
      string HLTTriggerReq = "(BuHlt2Topo2BodyBBDTDecision_TOS || "
        "BuHlt2Topo3BodyBBDTDecision_TOS || "
        "BuHlt2Topo4BodyBBDTDecision_TOS)==1";
      string TriggerReq = L0TriggerReq+"&&"+HLTTriggerReq;
      string DoubleSwap = "abs(D0_M_DOUBLESW-1864.78)>15.0";
      string Cuts = (strcmp(Mode[mod],"kpi")==0) ? TriggerReq+"&&"+DoubleSwap : TriggerReq;
      cout<<Cuts<<endl;
      
      RooDataSet* Sig_DataSet = new RooDataSet( "B->DPi Pion",
                                                "Signal Track",
                                                t_Sig,
                                                SigVars,                                          
                                                Cuts.c_str());
      const RooArgSet* SigDataVars = Sig_DataSet->get(0);
      //Sig_nTracks[i] = ((RooRealVar*)SigDataVars->find("Bu_DPVCFIT_M_RESC"))->frame(5100,5700);
      Sig_nTracks[i] = ((RooRealVar*)SigDataVars->find("Bach_P"))->frame(0,100000);
  
      Sig_DataSet->plotOn(Sig_nTracks[i], 
                          //DataError(RooAbsData::SumW2), 
                          LineColor(kBlue),  
                          MarkerColor(kBlue), 
                          Binning(50)) ;
      canvas_Mass->cd(i+1);
      Sig_nTracks[i]->Draw();

      //delete Sig_nTracks;
      delete Sig_DataSet;

      ++i;

    }//mode

  }//pol  

  canvas_Mass->SaveAs("Mom.eps");

  for(i=0; i<6; ++i)
    delete Sig_nTracks[i];
  
  return EXIT_SUCCESS;
}

//=============================================================================
