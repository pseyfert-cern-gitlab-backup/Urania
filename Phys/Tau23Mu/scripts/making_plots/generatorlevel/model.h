#include <iostream>
#include <math.h>

class model {
  private:
    std::pair<double,double> m_LLLL;
    std::pair<double,double> m_LLRR;
    std::pair<double,double> m_rad;
    std::pair<double,double> m_rad_L;
    std::pair<double,double> m_rad_R;
    std::pair<double,double> m_flat;
    unsigned m_entries;
    double m_normfac;
  public:
    model() :
      m_LLLL (std::pair<double,double>(0.,0.)),
      m_LLRR (std::pair<double,double>(0.,0.)),      
      m_rad  (std::pair<double,double>(0.,0.)),
      m_rad_L(std::pair<double,double>(0.,0.)),
      m_rad_R(std::pair<double,double>(0.,0.)),
      m_flat(std::pair<double,double>(0.,0.)),
      m_entries(0u),
      m_normfac(0.)
  {} ;
    void fill(double m01,double m02, double m12) {
      double ll = gammaVLLLL(m01*m01,m02*m02,m12*m12);
      double lr = gammaVLLRR(m01*m01,m02*m02,m12*m12);
      double rad = gammaRAD(m01*m01,m02*m02,m12*m12);
      double rad_l = interferenceVLLLL_RAD(m01*m01,m02*m02,m12*m12);
      double rad_r = interferenceVLLRR_RAD(m01*m01,m02*m02,m12*m12);
      double flat = 1.;

      m_LLLL.first += ll;
      m_LLRR.first += lr;
      m_rad.first  += rad;
      m_rad_L.first+= rad_l;
      m_rad_R.first+= rad_r;
      m_flat.first+= flat;

      m_LLLL.second+= ll*ll;
      m_LLRR.second+= lr*lr;
      m_rad.second+= rad*rad;
      m_rad_L.second+= rad_l*rad_l;
      m_rad_R.second+= rad_r*rad_r;
      m_flat.second+= flat*flat;

      m_entries++;
      return;
    };
    void printthis(std::pair<double,double> paar, std::string name) {
      std::cout << " ===   " << name << " with " << m_entries << " events  === " << std::endl;
      double res                   =     paar.first/((double)m_entries);
      //double err                   = sqrt((m_entries*paar.second - paar.first*paar.first)*m_normfac);
      double err                   = sqrt(1./(m_entries-1.)) * sqrt((1./m_entries*paar.second)-(1./m_entries*paar.first)*(1./m_entries*paar.first));
      std::cout << "    " << res << " pm " << err << std::endl << std::endl << std::endl;
    }
    void print() {
      m_normfac = 1./(m_entries * m_entries * (m_entries -1));
      printthis(m_LLLL,"LLLL");
      printthis(m_LLRR,"LLRR");
      printthis(m_rad,"rad");
      printthis(m_rad_L,"rad_L");
      printthis(m_rad_R,"rad_R");
      printthis(m_flat,"flat");

    };
};

