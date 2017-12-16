#include <vector>
#include <string>
#include "TTree.h"
#include "TH1F.h"

#ifndef BINNING_H 
#define BINNING_H 1
/** @class binning
* @brief 
*/
class binningholder;

float cls_fom(int bkg, float sigeff);
float punzi_fom(int bkg, float sigeff);
float cls_ffom(float bkg, float sigeff);
float punzi_ffom(float bkg, float sigeff);

extern float g_punzi_a;
extern float g_cls_norm;
extern bool g_calib;

extern  TH1F* sighist1;
extern  TH1F* sighist2;
extern  TH1* bkghist;

class binning {
  public:
    binning(float, float, unsigned, unsigned, std::string);
    virtual ~binning() ;
    bool operator==(binning);
    bool next_up_free(unsigned cur) ;
    bool set (std::vector<unsigned> vec) {
      std::vector<unsigned> backup = m_array;
      if (vec.size()!=m_array.size()) return false;
      for (unsigned i = 1 ; i < m_array.size() ; ++i)
        if (m_array[i-1] >= m_array[i]) return false;
      for (unsigned i = 0 ; i < m_array.size() ; ++i)
        m_array[i] = vec[i];
      return true;
    }
    bool increment(unsigned cur) ;
    bool increment() {return increment(m_array.size()-1);};
    void reset();
    void reset_boundary(unsigned cur) ;
    bool sane();
    /// starting from 0, counting bins
    std::string cutstring(unsigned binnumber) ;
    void debug_statement();
    unsigned nBins() {return m_array.size()+1;}
    std::vector<unsigned> boundaries() {return m_array;}
    std::vector<float> fine_binning() {return m_allowed_steps;}
    void set_fine_binning(std::vector<float> input) ;

  private:
    /// holds the gridpoint numbers (starting from 0)
    std::vector<unsigned> m_array;

    /// holds the grid
    std::vector<float> m_allowed_steps; 
    bool is_free(unsigned test);
    std::string m_name;
  friend class binningholder;
    

};

typedef float (*figure_of_merit)(int, float);
typedef float (*ffigure_of_merit)(float, float);

class binningholder {
  public:
    binningholder();
    void setSignal(TTree*);
    void setBackground(TTree*);
    void setFoM(ffigure_of_merit);
    void setBinning(binning*);
    float compute_additive_fom(std::string restriction, std::string additional_restriction = "1");
    void setGeoNAME(std::string n) {m_geoname = n;};

  protected:
    virtual float compute(std::string restriction, std::string additional_restriction, unsigned bin);
    ffigure_of_merit m_fom;
    TTree* m_sig;
    TTree* m_bkg;
    binning* m_binning;
    std::string m_geoname;
};

class trunkationholder : public binningholder {
  protected:
    virtual float compute(std::string restriction, std::string additional_restriction, unsigned bin) ;
};

class multibinholder : public trunkationholder {
  public:
    multibinholder();
    bool increment() ;
    bool increment_binning(unsigned) ;
    float compute_additive_fom(std::string restriction);
    virtual float compute_additive_fom(std::string restriction, std::string additional_restriction, unsigned level);
    void setBinning(binning* b) {addBinning(b);};
    void addBinning(binning*);
    void reset() {for (unsigned k = 0 ; k < m_binnings.size() ; ++k) m_binnings[k]->reset();};
  protected:
    std::vector<binning*> m_binnings;
};

class multitrunkbinholder : public multibinholder {
  public:
    float compute_additive_fom(std::string restriction) {return multibinholder::compute_additive_fom(restriction);}
    virtual float compute_additive_fom(std::string restriction, std::string additional_restriction, unsigned level);
};

//class brainfuck : public binningholder {
//  public:
//    void addFucker(binning*);
//  private:
//    binning* m_fucker;
//
//};

#endif
