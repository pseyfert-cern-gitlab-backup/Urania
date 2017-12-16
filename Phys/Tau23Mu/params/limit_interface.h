#ifndef LIMITINTERFACE_H
#define LIMITINTERFACE_H 1
#include <Rtypes.h>
#include <TH2.h>
#include <iostream>
//#include "params.h"


#ifndef PARAMS
#define PARAMS 1

const int n_pidbins = 5;
//2012
//const int n_geobins = 8-1;
//2011
const int n_geobins = 7-1;

const int n_massbins = 6;

extern float geobinning[n_geobins+1];
extern float pidbinning[n_pidbins+1];

const bool etaveto = false;
const bool phiveto = true;

const TString pidll("min(p0_ANNmuon,min(p1_ANNmuon,p2_ANNmuon))");
const TString geoll("MN_BLEND_FLAT");

const float g_taumass = 1776.82;
//const float g_tauwidth = 9.16;
const float g_tauwidth1 = 9.16;
const float g_tauwidth2 = 9.16;



class TTree;
void fillmassbins(TTree*,TTree*);
void searchgeobinning(TTree*);
void searchpidbinning(TTree*);
TH1* makegeoreference(TTree*);

const bool reweighttau = true;
const bool reweightds  = false;

#endif //PARAMS

/** @class limit_interface limit_interface.h
 * @brief provide an interface to consistently fill histogramms
 *
 * @author Paul Seyfert <pseyfert@cern.ch>
 * @date   2012-03-16
 */

class limit_interface {
 private:
  int n_massbins;
  float l_pidbinning[n_pidbins+1];
  float l_geobinning[n_geobins+1];
  float lowmasslimit;
  float highmasslimit;
  TH2F* private_histo;
  TH2F* private_histo_P;
  TH2F* private_histo_M;
  static TString m_georefstring;
  static TString m_cutstring2011;
  static TString m_cutstring2012;

 public:
/**
* @brief the standard cut string for the tau23mu analysis (fiducial cuts, vetos, etc)
*
* @return TString to be used by TTree::Draw as cut. by default w/o parentheses
*/
  TString CutString() { std::cerr << "please specify 2011 or 2012" << std::endl; return ""; };

/**
* @brief the standard cut string for the tau23mu analysis (fiducial cuts, vetos, etc) for the 2011 data
*
* @return TString to be used by TTree::Draw as cut. by default w/o parentheses
*/
  TString CutString2011() { return m_cutstring2011; };


/**
* @brief the standard cut string for the tau23mu analysis (fiducial cuts, vetos, etc) for the 2012 data
*
* @return TString to be used by TTree::Draw as cut. by default w/o parentheses
*/
  TString CutString2012() { return m_cutstring2012; };



/**
* @brief the standard cut string for the classifier calibration
*
* @return TString to be used by TTree::Draw as cut. by default w/o parentheses and w/o productionweight
*/
  TString getGeoRefString() { return m_georefstring; };

/**
* @brief set a standard cut. NB: this is access to a static class member. i.e. you change the cut string for ALL existing instances and all instances which will be created!
*
* @param newstring the replacement for the GeoRefString as returned by getGeoRefString
*
* @return returns the stored string
*/
  TString setGeoRefString(TString newstring) { m_georefstring = newstring; return getGeoRefString(); };

/**
* @brief provides the GeoMVA binning
*
* @return the binning as C-array (readable by the TH1F constructor)
*/
  float* the_geobinning() {return l_geobinning;}


/**
* @brief provides the number of GeoMVA bins
*
* @return the number of bins (readable by the TH1F constructor)
*/
  int the_geobins() {return n_geobins;}


/**
* @brief provides the PidMVA binning
*
* @return the binning as C-array (readable by the TH1F constructor)
*/
  float* the_pidbinning() {return l_pidbinning;}


/**
* @brief provides the number of PidMVA bins
*
* @return the number of bins (readable by the TH1F constructor)
*/
  int the_pidbins() {return n_pidbins;}


/**
* @brief How the PidMVA is to be accessed on flat ntuples
* @code
*  limit_interface* li = new limit_interface();
*  TTree* signal = ...
*  signal->Draw(li->the_pid());
* @endcode
*
* @return A TString of the branchname/TFormula
*/
  TString the_pid() {return pidll;}

/**
* @brief How the GeoMVA is to be accessed on flat ntuples
* @code
*  limit_interface* li = new limit_interface();
*  TTree* signal = ...
*  signal->Draw(li->the_geo());
* @endcode
*
* @return A TString of the branchname/TFormula
*/
  TString the_geo() {return geoll;}



/**
* @brief constructor.
* ROOT dictionaries and libraries seem to have trouble with global variables. Therefore I read in the external defined array into the class.
*/
  limit_interface() {
    n_massbins = 8;
    if (m_georefstring == "NaN") {
      m_georefstring = "cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250";
      m_georefstring += "&&abs(mass_p0p2-1020.4)>20&&abs(mass_p1p2-1020.4)>20";
    }
//    TString m_cutstring = "cleaningcut";  /// cleaningcuts
//    m_cutstring += "&&TriggerTOSHlt1TrackMuonDecision&&TriggerTOSL0Muon";   
//    m_cutstring += "&&mass_p0p1>250";                                      /// clone veto
//    m_cutstring += "&&abs(mass_p0p2-1020.4)>20&&abs(mass_p1p2-1020.4)>20"; /// phi veto
//    m_cutstring2011 = m_cutstring;
//    m_cutstring2012 = m_cutstring;
//    m_cutstring2011 += "&&(TriggerTOSHlt2TriMuonTauDecision||TriggerTOSHlt2CharmSemilepD2HMuMuDecision)";
//    m_cutstring2012 += "&&TriggerTOSHlt2TriMuonTauDecision";


    m_cutstring2012 = "mass_p0p1 > 250 && abs(mass_p1p2 - 1019.5) > 20 && abs(mass_p0p2 - 1019.5) > 20 && mass_p1p2 > 450 && mass_p0p2 > 450 && cleaningcut && TriggerTOSL0Muon && TriggerTOSHlt1TrackMuonDecision && TriggerTOSHlt2TriMuonTauDecision";


    m_cutstring2011 = "mass_p0p1 > 250 && abs(mass_p1p2 - 1019.5) > 20 && abs(mass_p0p2 - 1019.5) > 20 && mass_p1p2 > 450 && mass_p0p2 > 450 && cleaningcut && TriggerTOSL0Muon && TriggerTOSHlt1TrackMuonDecision && (TriggerTOSHlt2TriMuonTauDecision || TriggerTOSHlt2CharmSemilepD2HMuMuDecision)";


    for (int i = 0 ; i <= n_pidbins ; ++i) {
      l_pidbinning[i] = pidbinning[i];
    }
    for (int i = 0 ; i <= n_geobins ; ++i) {
      l_geobinning[i] = geobinning[i];
    }

    for (int i = 0 ; i <= n_geobins ; ++i) {
//      geobinning[i]=l_geobinning[i];
    }
    lowmasslimit = g_taumass-20.;
    highmasslimit = g_taumass+20.;
    private_histo = GetCleanHistogram(TString("private"));
    private_histo_P = GetCleanHistogram(TString("private_P"));
    private_histo_M = GetCleanHistogram(TString("private_M"));
 
  }

/**
* @brief readjust the mass bins
*
* @param taumass the tau mass we expect to see in data in MeV/c^2
*/
  void set_central_mass(float taumass) {
    lowmasslimit = taumass - 20.;
    highmasslimit = taumass + 20.;
    refresh();
  }

/**
* @brief resets the mass scales of private histograms
*/
  void refresh() {
    TH2F* c = GetCleanHistogram("private_new");
    TH2F* cp = GetCleanHistogram("private_P_new");
    TH2F* cm = GetCleanHistogram("private_M_new");
    for (int m = 1 ; m <= n_massbins ; ++m) {
      for (int n = 1 ; n <= n_geobins*n_pidbins ; ++n) {
        int totbin = c->GetBin(m,n);
        c->SetBinContent(totbin,private_histo->GetBinContent(totbin));
        cp->SetBinContent(totbin,private_histo_P->GetBinContent(totbin));
        cm->SetBinContent(totbin,private_histo_M->GetBinContent(totbin));
      }
    }
    delete private_histo;
    delete private_histo_P;
    delete private_histo_M;
    private_histo = c;
    private_histo_P = cp;
    private_histo_M = cm;
    c->SetName("private");
    cp->SetName("private_P");
    cm->SetName("private_M");
    
  }
  virtual ~limit_interface() {
    delete private_histo;
    delete private_histo_P;
    delete private_histo_M;
  }
  /**
   * @brief get the 2d MVA bin number for a given GeoMVA and singlePID
   * overflow and underflow are NOT supported
   *
   * @param geobin binnumber in GeoMVA starting at 0
   * @param pidbin binnumber in singlePID starting at 0
   *
   * @return the unrolled binnumber starting at 0
   */
  int GetGlobalMVAbin(int geobin, int pidbin) ;

/////  /**
/////   * @brief get the 2d MVA bin number for a given GeoMVA and singlePID
/////   * overflow and underflow are NOT supported
/////   *
/////   * @param GeoMVA GeoMVA response (-1 .. 1)
/////   * @param singlePID singlePID response (-1 .. 1)
/////   *
/////   * @return the unrolled binnumber starting at 0
/////   */
/////  int GetGlobalMVAbin(float GeoMVA, float singlePID) ;
/////


/**
* @brief how many bins in PID do we have
*
* @return the number of PID bins
*/
  float GetNPIDbins() {
    return n_pidbins;
  }

/**
* @brief how many bins in GeoMVA do we have
*
* @return the number of GeoMVA bins
*/
  float GetNGeobins() {
    return n_geobins;
  }
/**
* @brief how many bins in mass do we have
*
* @return the number of mass bins
*/
  float GetNMassbins() {
    return n_massbins;
  }
 
/**
* @brief lower edge of a PID bin
*
* @param pidbin starting numbering at 0
*
* @return lower edge of the pidbin^th PID bin
*/
  float GetPIDlow(int pidbin) {
    return pidbinning[pidbin];
  }

/**
* @brief upper edge of a PID bin
*
* @param pidbin starting numbering at 0
*
* @return upper edge of the pidbin^th PID bin
*/
  float GetPIDhigh(int pidbin) {
    return pidbinning[1+pidbin];
  }
/**
* @brief lower edge of a GeoMVA bin
*
* @param geobin starting numbering at 0
*
* @return lower edge of the geobin^th GeoMVA bin
*/
  float GetGeolow(int geobin) {
    return l_geobinning[geobin];
  }
/**
* @brief upper edge of a GeoMVA bin
*
* @param geobin starting numbering at 0
*
* @return upper edge of the geobin^th GeoMVA bin
*/
  float GetGeohigh(int geobin) {
    return l_geobinning[1+geobin];
  }
/**
* @brief lower edge of a mass bin
*
* @param massbin starting numbering at 0
*
* @return lower edge of the massbin^th mass bin
*/
  float GetMasslow(int massbin) {
    return lowmasslimit+((float)massbin)*(highmasslimit-lowmasslimit)/((float)n_massbins);
  }
/**
* @brief upper edge of a mass bin
*
* @param massbin starting numbering at 0
*
* @return upper edge of the massbin^th mass bin
*/

  float GetMasshigh(int massbin) {
    return lowmasslimit+(1.+(float)massbin)*(highmasslimit-lowmasslimit)/((float)n_massbins);
  }



/**
* @brief obtain a blanco histogram in the correct binning
*
* @param name how the histogram should be called in root's memory magic
*
* @return pointer to the histogram (you take ownership)
*/
  TH2F* GetCleanHistogram(TString name = "2d-hist") {
    return new TH2F(name.Data(),name.Data(),n_pidbins*n_geobins,0,n_pidbins*n_geobins,n_massbins,lowmasslimit,highmasslimit);
  }

/**
* @brief obtain a clone of the interface's histogram
*
* @param name how the histogram should be called in root's memory magic
*
* @return pointer to the cloned histogram (you take ownership)
*/
  TH2F* GetFilledHistogram(TString name = "") {
    return (TH2F*)private_histo->Clone(name.Data());
  }

/**
* @brief obtain a clone of the interface's histogram for the upper limit
*
* @param name how the histogram should be called in root's memory magic
*
* @return pointer to the cloned histogram (you take ownership)
*/
  TH2F* GetFilledHistogram_PLUS(TString name = "") {
    return (TH2F*)private_histo_P->Clone(name.Data());
  }
/**
* @brief obtain a clone of the interface's histogram for the lower limit
*
* @param name how the histogram should be called in root's memory magic
*
* @return pointer to the cloned histogram (you take ownership)
*/
  TH2F* GetFilledHistogram_MINUS(TString name = "") {
    return (TH2F*)private_histo_M->Clone(name.Data());
  }

  void SetPrivate(int geobin, int pidbin, float mass, float content);


/**
* @brief store information in the internal histograms
*
* @param geobin number of the GeoMVA bin starting at 0
* @param pidbin number of the PID bin starting at 0
* @param mass massbin -- as a float due to inconsequence -- 
* @param content the content to be stored
* @param contentPLUS content + error
* @param contentMINUS content - error
*/
  void SetPrivate(int geobin, int pidbin, float mass, float content, float contentPLUS, float contentMINUS);

  ClassDef(limit_interface,3);
};

#endif

