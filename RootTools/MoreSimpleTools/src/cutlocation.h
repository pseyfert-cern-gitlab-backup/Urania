
#ifndef CUTLOCATION
#define CUTLOCATION

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
#include <vector>
//#include <algorithm>
//#include "cutresult.h"

class cutresult;


class cutlocation 
{
 public:
  
  cutlocation();
  cutlocation(const unsigned int & ncuts);
  cutlocation(const unsigned int & ncuts, const unsigned int & nval);
  cutlocation(const std::vector<unsigned int> & location);
  cutlocation(const cutresult & location);
  
  
  virtual ~cutlocation() {};
  
  cutlocation& operator=(const std::vector<unsigned int> & newloc) {  loc=newloc; return *this; };
  cutlocation& operator=(const cutlocation & newloc) {  return (*this)=newloc.loc; };
  cutlocation& operator=(const cutresult & newloc);// {  return (*this)=newloc.location(); };
  
  bool operator!=(const cutresult& compare) const;
  bool operator!=(const cutlocation& compare) const {return (*this)!=compare.loc;};
  bool operator!=(const std::vector<unsigned int> & compare) const;
  bool operator==(const cutresult& compare) const;
  bool operator==(const cutlocation& compare) const {return (*this)==compare.loc;};
  bool operator==(const std::vector<unsigned int> & compare) const;

  bool operator<(const cutlocation & compare) const;
  bool operator>(const cutlocation & compare) const ;
  // bool operator<(const std::vector<unsigned int> & compare) const ;
  // bool operator>(const std::vector<unsigned int> & compare) const ;
  cutlocation operator^(const cutlocation & compare) const {return (*this)^(compare.loc);};
  cutlocation operator^(const std::vector<unsigned int> & compare) const;
  
  unsigned int sum() const
    {
      unsigned int msum=0;
      for(std::vector<unsigned int>::const_iterator itl=loc.begin();itl!=loc.end();itl++)
	{
	  msum+=*itl;
	}
      return msum;
    }
  
  std::vector<unsigned int> loc;
  
  friend std::ostream& operator<<(std::ostream& out, const cutlocation& location)
    {
      for(unsigned int i=0; i< location.loc.size(); i++) out << location.loc[i] << " ";      
      return out;
    }
  
 protected:
  //std::vector<unsigned int> loc;
    
 private:

  //ClassDef(cutlocation,0)
  
};
//TString data::Bstr = "B"



#endif
