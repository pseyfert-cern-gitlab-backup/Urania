
#ifndef PLOTS
#define PLOTS

#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCint.h>
#include <TMath.h>
#include <TTree.h>
#include <TString.h>
#include <TStopwatch.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <fstream>
#include "stdio.h"
#include "string"
#include "TStyle.h"
#include "Riostream.h"
#include "TAxis.h"
#include <TRandom3.h>
#include <cctype>
#include <cmath>
#include <vector>
#include <TArrow.h>
#include "TH1F.h"
#include "TH1.h"
#include "THStack.h"



class plots 
{
 public:
  
  plots();
  plots(const std::string& plotfile);
  virtual ~plots();
  
  void stacked(const bool stack) { m_stacked=stack; };
  bool stacked(void) { return m_stacked; };
  
  
  
  bool plot(const std::vector<double> & X,const std::vector<double> & Y,const std::string& name, const std::string& xname="X", const std::string& yname="Y", const std::string& directory="plots");
  bool plot(const std::vector<double> & X,const std::vector<double> & Y,const std::vector<double> & Xerr,const std::vector<double> & Yerr,const std::string& name, const std::string& xname="X", const std::string& yname="Y", const std::string& directory="plots");
  
  bool plot(const unsigned int & arrow,const std::vector<double> & X,const std::vector<double> & Y,const std::string& name, const std::string& xname="X", const std::string& yname="Y", const std::string& directory="plots");

  bool plot(const unsigned int & arrow,const std::vector<double> & X,const std::vector<double> & Y,const std::vector<double> & Xerr,const std::vector<double> & Yerr,const std::string& name, const std::string& xname="X", const std::string& yname="Y", const std::string& directory="plots");
  
  bool plot(std::vector<TH1F*> histos, const std::string& name, const std::string& directory="plots");
  bool plot(std::vector<TH1F*> histos, const std::vector<TString> leg_entries, const std::string& name, const std::string& directory="plots");
  bool plot(std::vector<TH1F*> histos, const std::string& name, const double min, const double max, const bool log=false, const std::string& directory="plots");
  bool plot(std::vector<TH1F*> histos, const std::vector<TString> leg_entries, const std::string& name, const double min, const double max, const bool log=false, const std::string& directory="plots");

  bool mkdir(const std::string& directory);
  bool cd(const std::string& directory);

  //EColor colour(const unsigned int i) const { return m_colour[i%m_colour.size()]; };
  
  

  //protected:
  

 private:
  TFile* m_plotfile;
  bool m_stacked;
  
  //std::vector<const EColor> m_colours;
  
  
  //ClassDef(plots,0)
  
};




#endif
