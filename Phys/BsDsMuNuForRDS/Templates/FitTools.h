#ifndef RecoTools_h
#define RecoTools_h

#include "TRandom3.h"
#include "TTreeFormula.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooNLLVar.h"

#include <time.h>
#include <string>
#include <vector>

using namespace std;

class FitTools {

 public:

  FitTools(string inf, string fl, int dbg, bool sigO, bool addCon);

  void MyPlot(RooRealVar *myma, RooDataHist *adt, RooAbsPdf *apdf, int idx);
  
  //Config 
  void configure(string range, bool arange, string confF);
  vector<double> ReadVecFromFile(string filen, vector<string> parnames);
  double ReadValFromFile(string filen, string parname);

  //Fitting
  void doFit();
  void loadPDFs(string conf);
  void doTau();
  void doTwoD();
  void doSameSign();
  void doMCmat();
  bool f_doTau;
  bool f_doSameSign;
  bool f_doTwoD;
  bool f_doMCmat;
  bool f_addCon;
  bool f_sigOnly;
  int f_useTauPdfs;
  int f_useQsquare, f_useEmu;
  int f_applyTauCut;
  int f_applyIsoCut;
  int f_applyBMCut;
  RooArgSet *f_my_pdfs;
  RooArgSet *f_my_yields;

 private:

  RooAbsPdf * p_misid;
  int f_debug;
  string f_range;
  string f_infi;
  string f_flag;
  string f_confFl;
  bool f_applyRange;
  int f_hbins, f_qbins, f_ebins, f_mbins;
  int f_doPhiPi, f_addDs1p;

  double f_fit_range_min;
  double f_fit_range_max;

  int f_drawbins;

  //The Variable
  RooRealVar *mass, *qsquare, *mmsq, *emu;
  double fl_nentries, fl_Bmass;
  double fl_q2;
  double fl_Emu;
  double fl_MM2;
  RooNLLVar *nll;
  RooRealVar *BR_dspi;
  RooRealVar *BR_dsgam;
  RooFormulaVar *RDsConstr;
  RooFormulaVar *Ds0StaConstr;
  RooFormulaVar *DsStaConstr;


  //PDFs
  RooAbsPdf *f_sig_pdf;
  RooAbsPdf *f_dstau_pdf, *f_ds1pmu_pdf;
  RooAbsPdf *f_dsta_pdf;
  RooAbsPdf *f_dstatau_pdf;
  RooAbsPdf *f_ds0sta_pdf, *f_ds1ptau_pdf;
  RooAbsPdf *f_ds0statau_pdf;
  RooAbsPdf *f_dcharm_pdf;
  RooAbsPdf *f_sideb_pdf;
  RooAbsPdf *f_dstrcom_pdf;
  RooAbsPdf *f_LbLcDs_pdf;
  RooAbsPdf *f_BsDsDs_pdf;
  RooAbsPdf *f_BdDstDs_pdf;
  RooAbsPdf *f_BuD0Ds_pdf;
  RooAbsPdf *f_taubkg_pdf;

};


#endif

