/*==================================================
Francesco Dettori 
ConfInTe: Confidence Interval Tester
 ===================================================*/
#include <iostream>
#include <string>
#include <fstream>
#include "root_libs.h"
#include <vector>
#include "Riostream.h"

// Root 
#include "TTree.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TStopwatch.h"
#include "TDatabasePDG.h"
#include "TMarker.h"

// RooFit 
#include "RooGlobalFunc.h"
#include "RooProfileLL.h"
#include "RooAbsPdf.h"
#include "RooStats/HypoTestResult.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooTreeDataStore.h"

// RooStats
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/MCMCCalculator.h"
#include "RooStats/UniformProposal.h"
#include "RooStats/FeldmanCousins.h"
#include "RooStats/FrequentistCalculator.h"
#include "RooStats/NumberCountingPdfFactory.h"
#include "RooStats/ConfInterval.h"
#include "RooStats/PointSetInterval.h"
#include "RooStats/LikelihoodInterval.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "RooStats/RooStatsUtils.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/HypoTestInverterResult.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/HypoTestInverter.h"
#include "RooStats/RatioOfProfiledLikelihoodsTestStat.h" 
#include "RooStats/TestStatistic.h"
#include "RooStats/SimpleLikelihoodRatioTestStat.h"


using namespace std;
using namespace RooFit ;
using namespace RooStats ;


class confinte{
 public: 
  confinte();
  ~confinte();
  
  RooWorkspace * m_ws; 
  ModelConfig *m_modelConfig; 
  RooAbsPdf *m_model; 
  RooDataSet *m_data; 
  TString m_obs_set; 
  TString m_POI_set; 
  FeldmanCousins *m_fc;
  PointSetInterval* m_interval;
  RooDataHist *m_points_histo; 
  Double_t m_nbs_input; 
  Double_t m_nbd_input; 
  TString m_dir; 
  TString m_prefix; 
  TString m_s_NBs;
  TString m_s_NBd;
  TString m_out_file;
  bool m_in_parallel;
  bool m_useConstr; 
  int m_n_bin; 
  
  void setWorkspace(TString fileName = "Bs2MuMu_Workspace.root", TString workspaceName = "w;1");
  void setModel(RooAbsPdf *pdf);
  void setModelConfig(TString modelconfig);
    
  void setObs(TString variables, TString obsname);
  void setPOI(TString variables);
  void setVName(TString bs, TString bd);
  void setOutFile(TString fname){ m_out_file = fname; }
  void setConstr(bool cn) { m_useConstr = cn; }
  void setData(TString fileName = "dataset.txt");
  void setData(RooDataSet* dataset);
  void addRandom(double n_events, TString pdf_name= "pdf_Bs_sig");
  void setDirAndPrefix(TString dir, TString prefix){
    m_dir = dir; 
    m_prefix = prefix; 
  }
  void setPointsToScan(RooDataHist * points){m_points_histo = points;}; 
  void setNBin(int nBin){m_n_bin = nBin;};
  
  RooFitResult * fitData();
  void plot(TString prefix);
  // Feldman Cousins
  PointSetInterval *FC_interval(double testSize= 0.05);
  void plotFC(PointSetInterval *interval, TString parameter = "N_Bs");
  void plotFC2D();
  // Profile likelihood
  ConfInterval *PL_interval(double testSize); 
  void plotPL(ConfInterval *lrint);
  // CLs
  HypoTestInverterResult *CLs_interval();

  void saveInfo();
  //  void saveFC();
  TTree* getTree();
  void saveBelt();
  void saveInterval();

  void setParallel(bool par) { m_in_parallel = par ;}
  
  void FeldmanCousinsInt(int nth_point, int n_points);
    
  
  void CreateParameterPoints() const;
 private: 
  bool m_configured; 
  mutable RooAbsData *m_pointsToTest;

};
