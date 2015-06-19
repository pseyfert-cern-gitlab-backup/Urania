
#ifndef SCAN
#define SCAN

#include "data.h"
#include "cuts.h"
#include "plots.h"
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>
#include "TEntryList.h"
#include "cutlocation.h"
#include "cutresult.h"
#include <fstream>

class scan 
{
 public:
  
  scan();
  scan(data* tuples, const cuts* mycuts, plots* myplots=NULL);
  scan(const cuts* mycuts, data* tuples, plots* myplots=NULL);
  virtual ~scan() {};

  bool setPlots(plots* myplots) {m_plots=myplots; return true; } ;
  
  bool RateScan(bool statsscan=true,double freq=0.1);
  bool ScanForBest(const unsigned int iterate=10, const char mode='r');
  bool Select100pc(void);
  bool StatsScan(const unsigned int ncut, const std::string & directory = "plots", bool saveAll=false);
  bool StatsScan(const std::string & directory = "plots", bool saveAll=false);
  
  bool PlotAll(const std::string & directory = "plots");
  bool PlotAllClever(const std::string & directory = "plots");
  
  bool ChooseCuts(void);
  
  
  int S(); //cached
  int B(); //cached
  int S(const unsigned int i); //cached
  int B(const unsigned int i); //cached
  double Sw(); //cached
  double Bw(); //cached
  double Sw(const unsigned int i); //cached
  double Bw(const unsigned int i); //cached
  double BoS();
  double SoB();
  double SoRSB();
  double CustomSoRSB();
  double CustomS();
  double CustomB();
  double dCustomS();
  double dCustomB();
  //double dCustomSoRSB();
  double Eff();
  double Eff(const unsigned int adata);
  double EffB();
  double EffB(const unsigned int adata);
  double dS();
  double dB();
  double dS(const unsigned int adata);
  double dB(const unsigned int adata);
  double dSw();
  double dBw();
  double dSw(const unsigned int adata);
  double dBw(const unsigned int adata);
  double dBoS();
  double dSoB();
  double dSoRSB();
  double dEff();
  double dEff(const unsigned int adata);
  double dEffB();
  double dEffB(const unsigned int adata);
  
  double Bw_C_E(); //cands per event, cached
  double Sw_C_E(); //cands per event, cached
  double B_C_E(const unsigned int adata); //cands per event, cached
  double S_C_E(const unsigned int adata); //cands per event, cached
  
  
  int S0(); //cached
  int B0(); //cached
  double Sw0(); //cached
  double Bw0(); //cached

  int S0(const unsigned int i); //cached
  int B0(const unsigned int i); //cached
  double Sw0(const unsigned int i); //cached
  double Bw0(const unsigned int i); //cached

  double B_C_E0(const unsigned int adata); //cands per event, cached
  double S_C_E0(const unsigned int adata); //cands per event, cached
  
  double Bw_C_E0(); //cands per event, cached
  double Sw_C_E0(); //cands per event, cached
  
  bool stats();
  
  bool custom(){ return m_useCustom;};
  void setCustom(bool custom){m_useCustom=custom; return; };
  
  
  

 protected:
  
  unsigned int m_ndataS;
  unsigned int m_ndataB;
  data* m_data;
  unsigned int m_ncuts;
  const cuts* m_cuts;
  plots* m_plots;
  cutresult last;
  cutresult zero;
  std::vector< cutresult > saved_results;
  
  bool cutResult(const cutlocation & location, const bool force=false);
  bool unCache() 
    {
      m_S_sum=m_B_sum=-1; m_Bw_sum=m_Sw_sum=m_dSw_sum=m_dBw_sum=-1.; 
      //std::cout << "ready to leave uncache" << std::endl;
      return true;
    }; 
  //function to call if you internally change m_location, m_s_ents, or m_s, or something
  bool nextByRate();
  bool nextByDiff(const unsigned int ncut, const int step=+1);
  double nextByAllVal(const unsigned int ncut, double (scan::* valPointer)(void), const char mode='h' ); //returns dSw h=highest l=lowest
  bool nextByVal(const unsigned int ncut, double (scan::* valPointer)(void), const char mode='h' ); //returns dSw h=highest l=lowest
  bool find100pc(const unsigned int ncut);
  bool shortstats();
  
  std::vector<unsigned int> orderHighest(const std::vector<double> & values);
  std::vector<unsigned int> orderRandom();
  
  bool save() { return save(last); };
  bool save(const cutresult & other) { if(!isSaved(other)) saved_results.push_back(other); return true;};
  
  bool load(const cutlocation alocation, const bool force=false) { 
    //std::cout << "looking for the cut" << alocation << std::endl;
    cutresult *nearest=&zero;
      for(std::vector< cutresult >::reverse_iterator loc=saved_results.rbegin();
	  loc!=saved_results.rend(); loc++)
	{
	  //std::cout << "testing" << *loc << "against" << nearest->location() << std::endl;
	  if((*loc)==alocation) return load(*loc,force);
	  if(loc->location()<alocation && loc->location()>nearest->location()) nearest= &(*loc);//{std::cout << "found" << loc->location() << std::endl; nearest= &(*loc);};
	  
	}
      
      //    std::map< cutlocation , cutresult >::const_iterator loc=saved_results.find(alocation);
    //std::cout << "looking for the cut" << alocation << std::endl;
    //if(loc == saved_results.end()) return false;
    //std::cout << "returning" << nearest->location() << std::endl;
    load(*nearest,force);
    return false;//false if it wasn't found
  };
  bool load(const cutresult & other, const bool force=false) {
    //std::cout << "loading the cut" << other.location() << "force?" << force << std::endl;
    if (!force && last.location()==other.location()) return true;
    last=other;
    return unCache();
  };
  bool load() {
    return load(zero);
  };
  //cutlocation nearestSaved() const {return nearestSaved(last);};
  //cutlocation nearestSaved(const cutresult & other)  const {return nearestSaved(other.location()); };
  
  /*cutlocation nearestSaved (const cutlocation & other) const
    {
      cutlocation nearest=zero;
      for(std::map< cutlocation , cutresult >::const_iterator loc=saved_results.begin();
	  loc!=saved_results.end(); loc++)
	{
	  if(loc->first==other) return loc->first;
	  if(loc->first<other && loc->first>nearest) nearest=loc->first;
	}
      
      return nearest;
      
      }*/
  bool nearestSaved(const unsigned int fix_location) {return nearestSaved(fix_location, last);};
  bool nearestSaved(const unsigned int fix_location, const cutresult & other)  {return nearestSaved(fix_location, other.location());};
  bool nearestSaved(const unsigned int fix_location, const cutlocation & other) 
    {
      cutresult* nearest=&zero;
      for(std::vector< cutresult >::reverse_iterator loc=saved_results.rbegin();
	  loc!=saved_results.rend(); loc++)
	{
	  if(*loc==other) return load(*loc);
	  if(loc->location().loc[fix_location]==other.loc[fix_location] && loc->location()<other && loc->location()>nearest->location()) nearest=&(*loc);
	}
      
      return load(*nearest);
      
    }
  cutresult constructResult(const cutlocation & next)
    {
      //std::cout << "constructResult called " << std::endl;
      //start at the closest, to minimise the multiplication time
      load(next);
      cutresult begin=last;
      //std::cout << "constructResult called " << std::endl;
      for(unsigned int i=0; i<next.loc.size(); i++)
	{
	  //find the nearest for one of the cuts
	  nearestSaved(i,next);
	  if(last==zero) 
	    {
	      cutlocation findnext =zero;
	      findnext.loc[i]=next.loc[i];
	      cutResult(findnext,true);//don't check twice!
	    }
	  //multiply the two cuts, to find the common entries
	  begin.intersect(last);
	  if(begin.S() == 0 && begin.B()==0) {begin.set_location(next); break;};
	  
	}
      m_data->calculateEventWeights(begin);
      //std::cout << "constructResult, calculated weights " << std::endl;
      //shortstats();
      
      return begin;
    }
  
  
  bool isSaved(const cutresult & other) const { return isSaved(other.location());};
  
  bool isSaved(const cutlocation & other) const
    {
      for(std::vector< cutresult >::const_iterator loc=saved_results.begin();
	  loc!=saved_results.end(); loc++) if(*loc==other) return true;
      
      return false;
      
    }

  int m_S_sum; //cached, -1 = not cached.
  int m_B_sum; //cached
  double m_Sw_sum; //cached
  double m_Bw_sum; //cached
  
  double m_dSw_sum; //cached
  double m_dBw_sum; //cached
  
  int m_S0_sum; //cached, -1 = not cached.
  int m_B0_sum; //cached
  double m_Sw0_sum; //cached
  double m_Bw0_sum; //cached
  
  bool m_scanned; //false if no overall parameter scan has been done, true otherwise
  
  double min_weight();
  double max_weight();

  inline int O(const double x) const { if(x<1.) return (int(log10(x))-1); else return (int(log10(x))); };
  //cast to int rounds to zero :S
  //typedef std::map< std::vector<unsigned int > , cutresult > cutresults;


 private:

  bool clean(std::vector<TEntryList *> & me);

  //ClassDef(scan,0)

  bool m_useCustom;
  
};
//TString data::Bstr = "B"



#endif
