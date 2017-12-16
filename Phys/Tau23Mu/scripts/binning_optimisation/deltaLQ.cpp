#include "deltaLQ.h"
#include <iostream>
#include <algorithm>
#include "logstream.h"
#include "convert.h"
#include "TH1.h"
#include "TMath.h"
#include "TFile.h"

TH1F* sighist1=NULL;
TH1F* sighist2=NULL;
TH1* bkghist=NULL;


binning::~binning() {}

/**
 * @brief 
 */
void binning::reset() {
  for (unsigned i = 0 ; i < m_array.size() ; ++i) {
    m_array[i]=i;
  }
}

void binning::set_fine_binning(std::vector<float> input) {
  m_allowed_steps.clear();
  for (unsigned u = 0 ; u < input.size() ; ++u) {
    m_allowed_steps.push_back(input[u]);
  }
  return ;
}

binning::binning(float loweredge = -1.f, float upperedge = 1.f, unsigned gridpoints = 20u, unsigned bins = 5u, std::string name = "value") : m_name(name) {
  if (1>=bins) {
    logstreams::fatal << "attempt to create binning without bin boundaries" << std::endl;
  }
  if (gridpoints < bins) {
    logstreams::fatal << "attempt to create more bins than possible on that grid" << std::endl;
  }
  m_allowed_steps.clear();
  m_array.clear();
  m_allowed_steps.reserve(gridpoints);
  m_array.reserve(bins-1);
  float binwidth = (upperedge-loweredge);
  for (unsigned i = 0 ; i < gridpoints ; ++i) {
    m_allowed_steps.push_back(loweredge + ((float)i+1) * binwidth / ((float) gridpoints+1));
  }
  for (unsigned i = 0 ; i < bins - 1 ; ++i) {
    m_array.push_back(i);
  }

}

/**
* @brief 
*/
void binning::debug_statement() {
  logstreams::info << "binning for variable " << m_name << std::endl;
  logstreams::info << "gridpoints:\n";
  unsigned k = 0;
  while (k < m_allowed_steps.size()) {
    if (binary_search(m_array.begin(),m_array.end(),k))
      logstreams::info << "\033[01m";
    logstreams::info << m_allowed_steps[k++] << "\t";
//    if (binary_search(m_array.begin(),m_array.end(),k))
      logstreams::info << "\033[0m";
  }
  logstreams::info << "\ncurrent bin boundaries sit at:\n";
  k=0;
  while (k < m_array.size()) {
    logstreams::info << m_array[k++] << "\t";
  }
  logstreams::info << std::endl;
}

bool binning::sane() {
  bool retval = true;
  //  for (unsigned i = 0 ; i < m_array.size()-1 ; ++i) { // upper limit: the last has no following one
  //    retval = retval && (m_array[i]<m_array[i+1]);
  //
  // sorry, I found the while loop cooler

  unsigned i = 0;
  while (retval && (i < (m_array.size()-1))) {
    retval = (m_array[i]<m_array[++i]) && retval;
  }
  return retval && (m_array[m_array.size()-1]<m_allowed_steps.size());
}

/**
 * @brief 
 *
 * @param binBoundaryNumber
 *
 * @return 
 */
bool binning::next_up_free(unsigned binBoundaryNumber) {
  logstreams::debug << "checking next for boundary " << binBoundaryNumber << " call is_free for " << m_array[binBoundaryNumber]+1 << std::endl;
  unsigned current_gridpoint = m_array[binBoundaryNumber];
  return is_free(current_gridpoint+1);
}

/**
 * @brief 
 *
 * @param number of the bin boundary which shall be moved (numbers starting at 0)
 *
 * @return false if incrementation wasn't possible (end of range)
 */
bool binning::increment(unsigned cur) {
  logstreams::debug << "called increment for boundary " << cur << std::endl;
  logstreams::debug << "sitting at " << m_array[cur] << " so checking the next" << std::endl;
  if (next_up_free(cur)) {
    logstreams::debug << "simple" << std::endl;
    m_array[cur]++;
    return true;
  } else {
    if (0!=cur) {// there is no lower bin boundery to move
      if (increment(cur-1)) {
        logstreams::debug << "lower has successfully responded, approach it." << std::endl;
        reset_boundary(cur);
        return true;
      } else {
        logstreams::debug << "seems we're at the end. pass it upwards." << std::endl;
        return false;
      }
    } else {
      logstreams::debug << "lowest boundary cannot be moved" << std::endl;
      return false;
    }
  }
  logstreams::debug << "this shall never happen" << std::endl;
  return true;
}

/**
* @brief 
*
* @param binnumber
*
* @return 
*/
std::string binning::cutstring(unsigned binnumber) {
  logstreams::debug << "cutstring for bin " << binnumber << std::endl;
  if (binnumber>m_array.size()) {
    logstreams::error << "requested binrange out of binning range" << std::endl;
    return "";
  }
  std::string retval("");
  if (0!=binnumber) {
    retval += m_name;
    retval += ">" + stringify(m_allowed_steps[m_array[binnumber-1]]);
    if (m_array.size()==binnumber) {
      logstreams::debug << "this is the last bin" << std::endl;
      return retval;
    }
    retval += "&&";
  }
  retval += m_name;
  retval += "<" + stringify(m_allowed_steps[m_array[binnumber]]);

  return retval;
}

/**
 * @brief 
 *
 * @param cur
 */
void binning::reset_boundary(unsigned cur) {
  logstreams::debug << "this boundary (" << cur << ") is to be shifted to the left" << std::endl;
  if (0==cur)
    m_array[cur]=0;
  else {
    logstreams::debug << "the next to the left sits at point " << m_array[cur-1] << " so go to the next." << std::endl;
    logstreams::debug << "moving from " << m_array[cur] << "\t to " << m_array[cur-1]+1 << std::endl;
    m_array[cur] = m_array[cur-1]+1;
  }
  return;
}

/**
 * @brief 
 *
 * @param gridpoint
 *
 * @return 
 */
bool binning::is_free(unsigned gridpoint) {
  logstreams::debug << "is_free called for gridpoint " << gridpoint << std::endl;
  if (binary_search(m_array.begin(),m_array.end(),gridpoint))
    logstreams::debug << "this is occupied" << std::endl;
  else
    logstreams::debug << "this free" << std::endl;
  if (m_allowed_steps.size() <= gridpoint) logstreams::debug << "this is out of range" << std::endl;
  else logstreams::debug << "this is in range" << std::endl;
  if (m_allowed_steps.size() <= gridpoint) return false;
  return !binary_search(m_array.begin(),m_array.end(),gridpoint);
} ;


class binningholder;

//namespace binningholder
//{
//  using namespace binningholder;
  /**
   * @brief 
   */
  binningholder::binningholder() {
  }

  /**
   * @brief 
   *
   * @param TTree doesn't take ownership
   */
  void binningholder::setSignal(TTree* signal) {
    m_sig = signal;
  }

  /**
   * @brief 
   *
   * @param TTree doesn't take ownership
   */
  void binningholder::setBackground(TTree* background) {
    m_bkg = background;
  }

  /**
   * @brief 
   *
   * @param figure_of_merit doesn't take ownership
   */
  void binningholder::setFoM(ffigure_of_merit fom) {
    m_fom = fom;
  }

  /**
   * @brief 
   *
   * @param binning doesn't take ownership
   */
  void binningholder::setBinning(binning* bin) {
    m_binning = bin;
  }

bool binning::operator==(binning other) {
  if (m_allowed_steps.size() != other.m_allowed_steps.size()) return false;
  if (m_array.size() != other.m_array.size()) return false;
  for (unsigned b = 0 ; b < m_array.size() ;++b)
    if (m_array[b]!=other.m_array[b]) return false;
  for (unsigned b = 0 ; b < m_allowed_steps.size() ;++b)
    if (m_allowed_steps[b]!=other.m_allowed_steps[b]) return false;
  return true;
}

bool g_calib = false;

  /**
   * @brief 
   *
   * @return 
   */
float binningholder::compute(std::string restriction, std::string additional_restriction, unsigned bin) {
  TH1* calhist ;
  TFile* ff = NULL;
  logstreams::warn << "binningholder::compute(const std::string " << restriction << ", std::string " << additional_restriction << ", unsigned " << bin << ")" << std::endl;
  if (NULL==sighist1) sighist1 = new TH1F("m_sighist1","m_sighist",1,0.,100000.);
  if (NULL==sighist2) sighist2 = new TH1F("m_sighist2","m_sighist",1,0.,100000.);
  if (NULL==bkghist) bkghist = new TH1F("m_bkghist","m_bkghist",1,0.,100000.);
  //  TFile* ff = new TFile("calibrationhist.root","read");
  //  TH1* calhist ;
  //  ff->GetObject("calibration",calhist);
  //TH1* calhist = (TH1*)ff->Get("calibration");
  int bkgevents;
  float numer;
  float denom;
  float calib;
  float uncalib;
  // worker classes in background ... I guess ... prevent this from working
  //#pragma omp parallel sections
  {
    logstreams::debug << m_binning->cutstring(bin).c_str() << std::endl;
    //#pragma omp section
    {
      logstreams::debug << "one" << std::endl;
      m_bkg->Draw("mass>>m_bkghist",Form("(%s)*(%s)*(%s)",restriction.c_str(),m_binning->cutstring(bin).c_str(),additional_restriction.c_str()));
      logstreams::debug << "background cutstring is " << Form("(%s)*(%s)*(%s)",restriction.c_str(),m_binning->cutstring(bin).c_str(),additional_restriction.c_str()) << std::endl;
      bkgevents = bkghist->GetEntries();
      logstreams::debug << "two" << std::endl;
    }
    //#pragma omp section
    {
      m_sig->Draw("mass>>m_sighist1",Form("(%s)*(%s)*1*(%s)*(%s)",restriction.c_str(),m_binning->cutstring(bin).c_str(),additional_restriction.c_str() , ((g_calib)?(Form("w_%s",m_geoname.c_str())):("1"))));
      logstreams::debug << "three" << std::endl;
      logstreams::debug << "cutstring for the numerator is " << Form("(%s)*(%s)*1*(%s)*(%s)",restriction.c_str(),m_binning->cutstring(bin).c_str(),additional_restriction.c_str() , ((g_calib)?(Form("w_%s",m_geoname.c_str())):("1"))) << std::endl;
      numer = sighist1->GetSum();
      logstreams::debug << "four" << std::endl;
    }
    //#pragma omp section
    {
      m_sig->Draw("mass>>m_sighist2",Form("(%s)*1*(%s)",restriction.c_str(),((g_calib)?(Form("w_%s",m_geoname.c_str())):("1"))));
      logstreams::debug << "cutstring for the denominator is " << Form("(%s)*1",restriction.c_str()) << std::endl;
      denom = sighist2->GetSum();
    }

    logstreams::warn << "for cut " << m_binning->cutstring(bin) << " denom is " << denom << std::endl;
    if (0==numer) {
    
      bkghist ->Reset();
      sighist2->Reset();
      sighist1->Reset();  
      if (ff) {
        ff->Close();
        delete ff;
      }
      logstreams::warn << "binningholder::compute(const std::string " << restriction << ", std::string " << additional_restriction << ", unsigned " << bin << "), cut " << m_binning->cutstring(bin) << " = 0." << std::endl;
      return 0.;
    }
    uncalib = numer/denom; ///sorry for the name
    if (std::isnan(uncalib)) {
      logstreams::error << "tried to compute " << numer << "/" << denom << std::endl;
      logstreams::error << "restriction = " << restriction << std::endl;
      logstreams::error << "cutstring = " << m_binning->cutstring(bin) << std::endl;
      logstreams::error << "command m_sig->Draw(\"mass>>m_sighist2\",\""<<Form("(%s)*1",restriction.c_str())<<"\");"<<std::endl;
      logstreams::error << "tree name " << m_sig->GetName() << std::endl;
    }


    logstreams::debug << "deviation of " << uncalib << " - " << calib << " = " << uncalib - calib << std::endl;
  }
  bkghist ->Reset();
  sighist2->Reset();
  sighist1->Reset();
  if (ff) {
    ff->Close();
    delete ff;
  }
  float fbkgevents;
  if (0==bkgevents)
    fbkgevents = 0.0001;
  else
    fbkgevents = bkgevents;
  float returnvalue = m_fom(fbkgevents,((g_calib)?(uncalib):(uncalib)));
  logstreams::warn << "binningholder::compute(const std::string " << restriction << ", std::string " << additional_restriction << ", unsigned " << bin << "), cut " << m_binning->cutstring(bin) << " = " << returnvalue << std::endl;
  return returnvalue;

}

float binningholder::compute_additive_fom(std::string restriction, std::string additional_restriction) {
  logstreams::warn << "binningholder::compute_additive_fom(const std::string " << restriction << ", std::string " << additional_restriction << ")" << std::endl;
  float retval = 0.f;
  logstreams::debug << "need to compute something for " << m_binning->nBins() << " bins" << std::endl;
  for (unsigned k = 0 ; k < m_binning->nBins() ; ++k) {
    retval+=binningholder::compute(restriction,additional_restriction,k);
  }
  logstreams::warn << "binningholder::compute_additive_fom(const std::string " << restriction << ", std::string " << additional_restriction << ") = " << retval << std::endl;
  return retval;
}

//}

float g_punzi_a = 3.;
float g_cls_norm = .01;// 1 ~~ 1e-9

float cls_fom(int bkg, float sigeff) {
  double Qsb = TMath::Poisson(sigeff*g_cls_norm+bkg,sigeff*g_cls_norm+bkg) / TMath::Poisson(sigeff*g_cls_norm+bkg,bkg);
  if (isnan(Qsb) || isinf(Qsb)) logstreams::error << "insane Qsb" << std::endl;
  double denom = TMath::Poisson(sigeff*g_cls_norm+bkg,bkg);
  if (isnan(denom) || isinf(denom)) logstreams::error << "insane denom" << std::endl;
  if (isnan(denom) || isinf(denom)) logstreams::error << "insane denom: Poisson(" << sigeff*g_cls_norm+bkg << "," << bkg << ")" << std::endl;
  if (0.==denom) logstreams::error << "zero denom: Poisson(" << sigeff*g_cls_norm+bkg << "," << bkg << ")" << std::endl;
  double Qb = TMath::Poisson(bkg,sigeff*g_cls_norm+bkg) / TMath::Poisson(bkg,bkg);
  if (isnan(Qb) || isinf(Qb)) logstreams::error << "insane Qb" << std::endl;
  double returnvalue =  2*(TMath::Log(Qsb)-TMath::Log(Qb));
  if (isnan(returnvalue) || isinf(returnvalue)) logstreams::error << "insane DeltaLQ" << std::endl;
  return 2*(TMath::Log(Qsb)-TMath::Log(Qb));
}

float cls_ffom(float bkg, float sigeff) {
  double Qsb = TMath::Poisson(sigeff*g_cls_norm+bkg,sigeff*g_cls_norm+bkg) / TMath::Poisson(sigeff*g_cls_norm+bkg,bkg);
  if (isnan(Qsb) || isinf(Qsb)) logstreams::error << "insane Qsb" << std::endl;
  double denom = TMath::Poisson(sigeff*g_cls_norm+bkg,bkg);
  if (isnan(denom) || isinf(denom)) logstreams::error << "insane denom" << std::endl;
  if (isnan(denom) || isinf(denom)) logstreams::error << "insane denom: Poisson(" << sigeff*g_cls_norm+bkg << "," << bkg << ")" << std::endl;
  if (0.==denom) logstreams::error << "zero denom: Poisson(" << sigeff*g_cls_norm+bkg << "," << bkg << ")" << std::endl;
  double Qb = TMath::Poisson(bkg,sigeff*g_cls_norm+bkg) / TMath::Poisson(bkg,bkg);
  if (isnan(Qb) || isinf(Qb)) logstreams::error << "insane Qb" << std::endl;
  double returnvalue =  2*(TMath::Log(Qsb)-TMath::Log(Qb));
  if (isnan(returnvalue) || isinf(returnvalue)) logstreams::error << "insane DeltaLQ" << std::endl;
  return 2*(TMath::Log(Qsb)-TMath::Log(Qb));
}

float punzi_fom(int bkg, float sigeff) {
  return sigeff/(g_punzi_a/2. + TMath::Sqrt(bkg));
}
float punzi_ffom(float bkg, float sigeff) {
  return sigeff/(g_punzi_a/2. + TMath::Sqrt(bkg));
}



multibinholder::multibinholder() {
}

bool multibinholder::increment() {
  return multibinholder::increment_binning(0u);
}

bool multibinholder::increment_binning(unsigned k) {
  if (k>=m_binnings.size()) return false;
  if (m_binnings[k]->increment()) return true;
  else {
    if (increment_binning(k+1)) {
      m_binnings[k]->reset();
      return true;
    }
    return false;
  }
}

void multibinholder::addBinning(binning* b) {
  trunkationholder::m_binning = b;
  m_binnings.push_back(b);
}

float multibinholder::compute_additive_fom(std::string restriction) {
  logstreams::warn << "multibinholder::compute_additive_fom(const std::string " << restriction << ")" << std::endl;
  float retval = this->compute_additive_fom(restriction,"1",0u);
  logstreams::warn << "multibinholder::compute_additive_fom(const std::string " << restriction << ") = " << retval << std::endl;
  return retval;
}

float multibinholder::compute_additive_fom(const std::string restriction, std::string additional_restriction, unsigned level) {
  logstreams::warn << "multibinholder::compute_additive_fom(const std::string " << restriction <<", std::string "<< additional_restriction << ",  unsigned " << level << ")" << std::endl;
  float retval = 0.f;
  if (m_binnings.size()-1>level) {
    for (unsigned k = 0 ; k < m_binnings[level]->nBins() ; ++k) {
      std::string thisrestriction = additional_restriction + "*("+m_binnings[level]->cutstring(k)+ ")";
      retval += multibinholder::compute_additive_fom(restriction,thisrestriction,level+1);
    }
    logstreams::warn << "multibinholder::compute_additive_fom(const std::string " << restriction <<", std::string "<< additional_restriction << ",  unsigned " << level << ") = " << retval << std::endl;
    return retval;
  } else {
    retval += binningholder::compute_additive_fom(restriction,additional_restriction);
    logstreams::warn << "multibinholder::compute_additive_fom(const std::string " << restriction <<", std::string "<< additional_restriction << ",  unsigned " << level << ") = " << retval << std::endl;
    return retval;
  }
}

float multitrunkbinholder::compute_additive_fom(const std::string restriction, std::string additional_restriction, unsigned level) {
  logstreams::warn << "multitrunkbinholder::compute_additive_fom(const std::string " << restriction <<", std::string "<< additional_restriction << ",  unsigned " << level << ")" << std::endl;
  float retval = 0.f;
  if (m_binnings.size()-1>level) {
    for (unsigned k = 0 ; k < m_binnings[level]->nBins() ; ++k) {
      std::string thisrestriction = additional_restriction + "*("+m_binnings[level]->cutstring(k)+ ")";
      retval += multibinholder::compute_additive_fom(restriction,thisrestriction,level+1);
    }
    logstreams::warn << "multitrunkbinholder::compute_additive_fom(const std::string " << restriction <<", std::string "<< additional_restriction << ",  unsigned " << level << ") = " << retval << std::endl;
    return retval;
  } else {
    retval += trunkationholder::compute_additive_fom(restriction,additional_restriction);
    logstreams::warn << "multitrunkbinholder::compute_additive_fom(const std::string " << restriction <<", std::string "<< additional_restriction << ",  unsigned " << level << ") = " << retval << std::endl;
    return retval;
  }
}


float trunkationholder::compute(std::string restriction, std::string additional_restriction, unsigned bin) {
  float retval = 0.f;
  logstreams::warn << "trunkationholder::compute(std::string " << restriction << ", std::string " << additional_restriction << ", unsigned " << bin << ")" << std::endl;
  if (0u==bin) retval = 0.f;
  else retval = binningholder::compute(restriction, additional_restriction, bin);
  logstreams::warn << "trunkationholder::compute(std::string " << restriction << ", std::string " << additional_restriction << ", unsigned " << bin << ") = " << retval << std::endl;
  return retval;
} 


//void brainfuck::addFucker(binning* fuck) {
//  m_fucker = fuck;
//}
