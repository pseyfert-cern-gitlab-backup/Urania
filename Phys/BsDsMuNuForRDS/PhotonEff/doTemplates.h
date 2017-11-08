#ifndef doTemplates_h
#define doTemplates_h

#include "TTreeFormula.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooNLLVar.h"

#include <time.h>
#include <string>
#include <vector>

using namespace std;

class TemplateTools {

 public:

  TemplateTools(string inf, string fl, int debug);

  void ExpPlot(RooDataSet *adt, RooAbsPdf *apdf, string flg);
  
 private:

  RooAbsPdf * p_misid;
  bool f_isMC;
  bool f_isNewMC;
  bool f_doSB;
  bool f_doSS;
  bool f_doFake;
  bool f_doRooKeys;
  bool f_doMCmatch;
  bool f_doFF;
  int f_doPhiPi;
  int f_matchPar;
  int f_binFF;
  string f_range;
  string f_infi;
  string f_flag;
  bool f_applyRange;
  bool f_doTau;
  bool f_doTrueDs;
  int m_debug;
  double f_fit_range_min;
  double f_fit_range_max;
  double maxMass;
  int f_hbins;
  int f_qbins;
  int f_ebins;
  int f_mbins;
  int f_applyTauCut;
  int f_applyIsoCut;
  int f_applyBMCut;
  int f_drawbins;

  //The Variable
  RooRealVar *mass, *qsquare, *mmsq, *emu;
  double fl_nentries, fl_Bmass;
  float fl_q2;
  double fl_Emu;
  double fl_MM2;
  RooNLLVar *nll;

  //The priors business.
  int IDX_Prior;
  vector<string> sum;
  RooArgList terms;

  //Configure Output
  TTree *RootTree;
  double t_nbs, t_nbd;

};

#endif
