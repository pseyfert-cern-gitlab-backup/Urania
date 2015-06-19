
#ifndef CUTRESULT
#define CUTRESULT

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
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include "TEntryList.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include "cutlocation.h"

//typedef std::map< std::vector<unsigned int > , cutresult > cutresults;

//class cutlocation;


class cutresult 
{
 public:
  
  cutresult();
  cutresult(const cutlocation & location,
	    const std::vector< std::vector<unsigned long> > & ents_s,
	    const std::vector< std::vector<unsigned long> > & ents_b,
	    const std::vector<double> & cand_s,
	    const std::vector<double> & cand_b
	    );
  
  
  cutresult(size_t s_size, size_t b_size, size_t c_size);
  cutresult(const cutlocation& location, size_t s_size, size_t b_size);
  //cutresult(const cutresult* other) {copyFrom(other);};
  virtual ~cutresult() {};
  
  
  cutlocation location(void) const {return m_location;};
  std::vector< std::vector<unsigned long> >::const_iterator S_Ents_begin() const {return m_s_ents.begin();}; //list of entries for current cut
  std::vector< std::vector<unsigned long> >::const_iterator B_Ents_begin() const {return m_b_ents.begin();}; //list of entries for current vut
  std::vector<unsigned long>::const_iterator S_Ents_begin(unsigned int adata) const {return (m_s_ents[adata].begin());}; //list of entries for current cut
  std::vector<unsigned long>::const_iterator B_Ents_begin(unsigned int adata) const {return (m_b_ents[adata].begin());}; //list of entries for current vut
  std::vector< std::vector<unsigned long> >::const_iterator S_Ents_end() const {return m_s_ents.end();}; //list of entries for current cut
  std::vector< std::vector<unsigned long> >::const_iterator B_Ents_end() const {return m_b_ents.end();}; //list of entries for current vut
  std::vector<unsigned long>::const_iterator S_Ents_end(unsigned int adata) const {return (m_s_ents[adata].end());}; //list of entries for current cut
  std::vector<unsigned long>::const_iterator B_Ents_end(unsigned int adata) const {return (m_b_ents[adata].end());}; //list of entries for current cut
  TEntryList * S_Ents(unsigned int adata, const TTree* atree) const {return vectoelist(m_s_ents[adata],atree);}; //list of entries for current cut
  TEntryList * B_Ents(unsigned int adata, const TTree* atree) const {return vectoelist(m_b_ents[adata],atree);}; //list of entries for current cut
  
  bool set_S_Ents(unsigned int adata, std::vector<unsigned long> & entry) {m_s_ents[adata]=entry; return true;}; //list of entries for current cut
  bool set_B_Ents(unsigned int adata, std::vector<unsigned long> & entry) {m_b_ents[adata]=entry; return true;}; //list of entries for current cut
  bool set_S_Ents(unsigned int adata,TEntryList * entry) { return elisttovec(entry,m_s_ents[adata]);}; //list of entries for current cut
  bool set_B_Ents(unsigned int adata,TEntryList * entry) { return  elisttovec(entry,m_b_ents[adata]);}; //list of entries for current cut
  bool set_S_Ents(std::vector< std::vector<unsigned long> > & entry) {m_s_ents=entry; return true;}; //list of entries for current cut
  bool set_B_Ents(std::vector< std::vector<unsigned long> > & entry) {m_b_ents=entry; return true;}; //list of entries for current cut
  
  bool set_location(const cutlocation & alocation) {m_location=alocation; return true;};
  
  //bool add_S(const unsigned int adata, const unsigned long & entry) { m_s_ents[adata].push_back(entry); return true; };
  //bool add_B(const unsigned int adata, const unsigned long & entry) { m_b_ents[adata].push_back(entry); return true; };
  
  
  bool clear();
  
  
  int S() const;
  int B() const;
  int S(const unsigned int adata) const {return m_s_ents[adata].size();}; //cached
  int B(const unsigned int adata) const {return m_b_ents[adata].size();}; //cached
 
  double B_C_E(const unsigned int adata) const {return m_cb[adata];}; //cands per event
  double S_C_E(const unsigned int adata) const {return m_cs[adata];}; //cands per event
  std::vector<double>::const_iterator B_C_E_begin() const {return m_cb.begin();}; //cands per event
  std::vector<double>::const_iterator S_C_E_begin() const {return m_cs.begin();}; //cands per event
  std::vector<double>::const_iterator B_C_E_end() const {return m_cb.end();}; //cands per event
  std::vector<double>::const_iterator S_C_E_end() const {return m_cs.end();}; //cands per event
  
  bool set_B_C_E(const unsigned int adata, const double val) { m_cb[adata]=val; return true;}; //cands per event
  bool set_S_C_E(const unsigned int adata, const double val) { m_cs[adata]=val; return true;}; //cands per event
  bool set_B_C_E(const std::vector<double> & val) {m_cb=val; return true;}; //cands per event
  bool set_S_C_E(const std::vector<double> & val) {m_cs=val; return true;}; //cands per event
  
  //cutresult& operator=(const cutresult& other) { copyFrom(other); return *this; };
  
  bool operator!=(const cutresult& compare) const
    {
      return m_location!=compare.location();
    };
  
  bool operator!=(const cutlocation& compare) const
    {
      return m_location!=compare;
    };
  
  bool operator==(const cutresult& compare) const
    {
      return m_location==compare.location();
    };
  
  bool operator==(const cutlocation& compare) const
    {
      return m_location==compare;
    };
  
  
  bool operator<(const cutresult& compare) const
    {
      return m_location<compare.m_location;
    };
  
  
  bool operator>(const cutresult& compare) const
    {
      return m_location>compare.m_location;
    };
  
  
  cutresult& intersect(const cutresult& other);
  
  bool operator==(const std::vector<unsigned int> & compare) const 
    {
      return m_location==compare;
    };
  
  friend std::ostream& operator<<(std::ostream& out, const cutresult & result)
    {
      out << result.location() << " " << result.S() << " " << result.B() << result.m_cs.size() << " " << result.m_cb.size();
      return out;
    }
  
  
 protected:
  
  cutlocation m_location;
  std::vector<double> m_cs;
  std::vector<double> m_cb;
  
  std::vector< std::vector<unsigned long> > m_s_ents; //list of entries for current cut
  std::vector< std::vector<unsigned long> > m_b_ents; //list of entries for current vut
  
  //  std::vector< std::vector<unsigned long> > m_s_ents; //list of entries for current cut
  //  std::vector< std::vector<unsigned long> > m_b_ents; //list of entries for current vut
  
  //void copyFrom(const cutresult& other);
  
  //typedef std::vector< std::vector<unsigned long> > dvec;
  
  bool elisttovec(TEntryList * elist, std::vector<unsigned long> & avec);
  //TEntryList * vectoelist(const std::vector<unsigned long> & avec, const TTree* atree) const;
  TEntryList * vectoelist(const std::vector<unsigned long> * avec, const TTree* atree) const;
  TEntryList * vectoelist(const std::vector<unsigned long>::const_iterator & beg,
                          const std::vector<unsigned long>::const_iterator & end, 
                          const TTree* atree) const;
  
  TEntryList * vectoelist(const std::vector<unsigned long> & avec, const TTree* atree) const;
  
  bool elisttoset(TEntryList * elist, std::set<unsigned long> & aset);
  //TEntryList * vectoelist(const std::vector<unsigned long> & avec, const TTree* atree) const;
  TEntryList * settoelist(const std::set<unsigned long> * aset, const TTree* atree) const;
  TEntryList * settoelist(const std::set<unsigned long>::const_iterator & beg,
                          const std::set<unsigned long>::const_iterator & end, 
                          const TTree* atree) const;
  
  TEntryList * settoelist(const std::set<unsigned long> & aset, const TTree* atree) const;
  
  
 private:
    
  //ClassDef(cutresult,0)
  
};
//TString data::Bstr = "B"



#endif
