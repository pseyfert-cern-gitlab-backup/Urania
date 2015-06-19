// $Id: $
// Include files 
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TFile.h"
#include <cstdlib>
#include <list>
#include <utility>

// local
#include "PIDPerfTools/PIDPerfPlot.h"

int main(void)
{
  gSystem->Load("libRooStats.so");

  PIDPerfPlot<TGraphAsymmErrors>* MyPlot = new PIDPerfPlot<TGraphAsymmErrors>;
  
  TFile* f = new TFile("$PIDPERFSCRIPTSROOT/test/KPi_Neg_Separation_MagDown_Bayes_Strip15.root");
  
  std::list<TGraphAsymmErrors*> PionData;
  PionData.push_back((TGraphAsymmErrors*)f->Get("Pion_P_0"));
  PionData.push_back((TGraphAsymmErrors*)f->Get("Pion_P_5"));
  std::list<std::pair<double,double> > Pion_MarkerConf;
  Pion_MarkerConf.push_back(std::make_pair (1,25));
  Pion_MarkerConf.push_back(std::make_pair (1,21));
  std::string pion_label = "#pi #rightarrow K";
  std::pair<double,double> pi_label_pos;
  pi_label_pos = std::make_pair (25000., 0.20); // can't pass this directly. Why?
  MyPlot->AddDataSeries(PionData,
                        Pion_MarkerConf,
                        pion_label,
                        pi_label_pos);
 
  std::list<TGraphAsymmErrors*> KaonData;
  KaonData.push_back((TGraphAsymmErrors*)f->Get("Kaon_P_0"));
  KaonData.push_back((TGraphAsymmErrors*)f->Get("Kaon_P_5"));
  std::list<std::pair<double,double> > Kaon_MarkerConf;
  Kaon_MarkerConf.push_back(std::make_pair (2,24));
  Kaon_MarkerConf.push_back(std::make_pair (2,20));
  std::string kaon_label = "K #rightarrow K";
  std::pair<double,double> k_label_pos;
  k_label_pos = std::make_pair (25000., 0.75); // can't pass this directly. Why?
  MyPlot->AddDataSeries(KaonData,
                        Kaon_MarkerConf,
                        kaon_label,
                        k_label_pos);

  MyPlot->ApplyConfig( );
  MyPlot->SetAxisTitles("Momentum [MeV/c]",
                        "Efficiency");
  MyPlot->Draw();

  return EXIT_SUCCESS;
}
