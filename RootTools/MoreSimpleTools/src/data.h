
#ifndef DATA
#define DATA

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
#include <map>
#include <set>
#include <utility>
#include <TArrow.h>
#include "TH1F.h"
#include "TH1.h"
#include "TEventList.h"
#include "TEntryList.h"
#include "cutlocation.h"
#include "cutresult.h"


class data 
{
public:
  
  data();
  data(const std::string& weightListName);
  virtual ~data();
  
  //bool entries(TString & cut, std::vector<int> & s, std::vector<int> b, std::vector<double>& sw, std::vector<double> & bw );
  bool entries(TString & cut, const cutresult & input, cutresult & output);
  bool entries(TString & cut, cutresult & output);
  
  double s_weights(const unsigned int i) const {if(!m_prepared || i>=m_s_weights.size()) return 0.; return m_s_weights[i];};
  double b_weights(const unsigned int i) const {if(!m_prepared || i>=m_b_weights.size()) return 0.; return m_b_weights[i];};
  std::vector<double> s_weights() const {return m_s_weights;};
  std::vector<double> b_weights() const {return m_b_weights;};

  
  TString s_names(const unsigned int i) const {if(!m_prepared || i>=m_s_weights.size()) return ""; return m_s_user_names[i];};
  TString b_names(const unsigned int i) const {if(!m_prepared || i>=m_b_weights.size()) return ""; return m_b_user_names[i];};
  std::vector<TString> s_names() const { return m_s_user_names;};
  std::vector<TString> b_names() const { return m_b_user_names;};
  
  bool print(TString cut="");
  bool print(TString cut,cutresult & output);
  
  unsigned int NSFiles() const { return m_s_file_names.size(); };
  unsigned int NBFiles() const { return m_b_file_names.size(); };
  
  
  std::vector<TH1F*> graphThis(const std::string xname, const cutresult & output, const TString cuts="1");
  std::vector<TH1F*> graphThis(const std::string xname, const cutresult & output, double Rmin, double Rmax, const TString cuts="1");
  //std::vector<TH1F*> graphThis(const std::string xname, const TString cut="1");
  
  bool calculateEventWeights(cutresult & result);

protected:
  
  std::vector<double > m_s_weights;
  std::vector<double > m_b_weights;
  
  std::vector<TString> m_s_file_names;
  std::vector<TString> m_b_file_names;
  std::vector<TString> m_s_tuple_names;
  std::vector<TString> m_b_tuple_names;
  std::vector<TString> m_s_user_names;
  std::vector<TString> m_b_user_names;
  
  std::vector<TFile*> m_s_files;
  std::vector<TFile*> m_b_files;
  std::vector<TTree*> m_s_tuples;
  std::vector<TTree*> m_b_tuples;
  
  bool readWeightFile(const std::string& weightListName);
  bool loadTuples(void);
  
  typedef std::pair<long unsigned int, long unsigned int> runEvent;
  typedef std::map< runEvent, double > runEventWeight;
  typedef std::map< runEvent, long unsigned int > runEventCount;
  typedef std::vector< runEvent > runEventVector;
  typedef std::set<runEvent> runEventSet;
  //typedef std::vector< std::vector< runEvent > > runEventVector;
  
  //                           Run#         Event#             weight
  //  bool calculateEventWeights(cutresult & result);
  //bool addWeights(void);
  
  bool fillEventVector();
  
  //bool elisttovec(TEntryList * elist, std::vector<long unsigned int> & avec);
  //TEntryList * vectoelist(const std::vector<long unsigned int> & avec, const TTree* atree);
  //TEntryList * vectoelist(const std::vector<long unsigned int> * avec, const TTree* atree);
  //TEntryList * vectoelist(const std::vector<long unsigned int>::const_iterator & beg,const std::vector<long unsigned int>::const_iterator & end, const TTree* atree);
  
  
  friend std::ostream & operator<<(std::ostream & output, const data::runEvent & evtct)
  {
    output << "("<< (evtct.first) << " " << (evtct.second) << ")";
    return output;
  };
  
  friend std::ostream & operator<<(std::ostream & output, const data::runEventCount & evtct)
  {
    output << "[\n";
    for(data::runEventCount::const_iterator mit=evtct.begin(); mit!=evtct.end(); mit++)
    {
      output << "("<< (mit->first.first) << " " << (mit->first.second) << ") " << (mit->second) << "\n" ;
    }
    output << "]\n";
    return output;
  };
  
  

private:
  //ClassDef(data,0)

  //std::string BStr;
  const TString Bstr; //= "B"
  const TString Sstr; //= "S"
  const TString Estr; //= "E"
  const TString Rstr; //= "R"
  const TString Cstr; //= "#"
  const char* delimiters;// = " \t\n;";
  
  TString eventColumn;//the column defined with E
  TString runColumn;//the column defined with R
  

  bool m_prepared;
  bool m_weightBranch;

  std::vector< runEventVector > runEventVector_s;
  std::vector< runEventVector > runEventVector_b;
  
  //ClassDef(data,0)
  
};
//TString data::Bstr = "B"



#endif
