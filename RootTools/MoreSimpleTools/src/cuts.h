
#ifndef CUTS
#define CUTS

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
#include "data.h"
#include "TEntryList.h"
#include "cutresult.h"
#include "cutlocation.h"

class cuts 
{
 public:
  
  cuts();
  cuts(const std::string& cutListName);
  virtual ~cuts() {};

  TString decodeCuts(const cutresult& location) const;
  TString decodeCuts(const cutlocation& location) const;
  TString decodeCuts(const unsigned int ncut, const unsigned int location) const;
  double decodeValue(const unsigned int ncut, const unsigned int location) const;
  TString decodeName(const unsigned int ncut) const;
  TString decodeName(const TString acut) const;
  //TString decodeCuts();
  
  bool print(data* tuples) const;
  bool print() const;
  cutlocation location_max() const  { if(!m_prepared) return cutlocation(0); return m_location_max;};
  int location_max(const unsigned int ncut) const  { if(!m_prepared || ncut>m_location_max.loc.size()) return -1; return m_location_max.loc[ncut];};
  bool arrangeList(data* tuples);
  bool cut_result(data* tuples, cutresult &output) const;
  bool cut_result(data* tuples, const cutresult &input, cutresult &output) const;
  
  unsigned int NCuts() const { if(!m_prepared) return 0; return m_ncuts;};
  unsigned int NPlots() const { if(!m_prepared) return 0; return m_plot_names.size();};
  TString cut_name(const unsigned int ncut) const { if(ncut>m_cut_names.size()) return ""; return m_cut_names[ncut]; };
  TString plot_name(const unsigned int nplot) const { if(nplot>m_plot_names.size()) return ""; return m_plot_names[nplot]; };
  
  TString cut_range(const unsigned int ncut) const 
    {
      if(ncut>m_location_max.loc.size()) return "";
      return ( decodeCuts(ncut,0)+And+
	       "("+Not+"("+decodeCuts(ncut,m_location_max.loc[ncut])+"))"
	       ); 
    }
  
  TString plot_range(const unsigned int nplot) const 
    {
      if(nplot>m_plot_names.size()) return "";
      return (m_plot_range[nplot]);
      
    }
  
  bool choose_cuts(cutlocation &res) const;
  
  double plot_hi(const unsigned int nplot) const
  {
    if(nplot>m_plot_names.size()) return 0.;
    return (m_plot_hi[nplot]);
  }
  
  double plot_low(const unsigned int nplot) const
  {
    if(nplot>m_plot_names.size()) return 0.;
    return (m_plot_low[nplot]);
  }
  

 protected:
  
  int m_ncuts;
  std::vector<double > m_lower;
  std::vector<double > m_higher;
  std::vector<double > m_step;
  cutlocation m_location_max;
  
  std::vector<TString> m_cut_names;
  std::vector<TString> m_plot_names;
  std::vector<TString> m_plot_range;
  
  std::vector<double> m_plot_low;
  std::vector<double> m_plot_hi;
  
  
  bool readCutFile(const std::string& cutListName);
  //bool loadTuples(void);
  //bool arrangeList(data* tuples);
  bool swap(double &l, double&h);
  bool swap(TString &l, TString &h);
  

 private:
  //ClassDef(data,0)

    //std::string BStr;
  const TString Pstr; //= "!"
  const TString Cstr; //= "#"
  const TString And; //= "&&"
  const TString Not; //= "!"
  const char* delimiters;// = " \t\n;";
  const char* cutchars;// = "  =><!";
  
  bool m_prepared;
  
  //ClassDef(cuts,0)
  
};
//TString data::Bstr = "B"



#endif
