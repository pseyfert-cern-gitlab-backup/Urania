//#include "TObject.h"
//#ifndef SlDec
//#define SlDec

#include "TMath.h"
#include "TLorentzVector.h"

#include <iostream>
using namespace std;

class TLorentzVector;

//class SLdec : public TObject {

class SemiDec {
    public:
        SemiDec(const TLorentzVector&, const TLorentzVector&, const TLorentzVector&);
        ~SemiDec();
        Double_t GetW() const;
        Double_t GetQ2() const;
        Double_t GetMM2() const;
        Double_t GetElCM() const;
        Double_t GetThetaL() const;
        Double_t GetPmiss() const;
        Double_t GetEmiss() const;
        void print();
    private:
        Double_t _bmass, _dmass, _bmass2, _dmass2;
        Double_t _q2, _mm2, _wvar, _emiss, _pmiss, _elcm ,_thl;
};

SemiDec::~SemiDec() {
}

SemiDec::SemiDec( const TLorentzVector & PB4v, const TLorentzVector & PD4v, const TLorentzVector & PL4v ) {

  _bmass=PB4v.M(); _bmass2=PB4v.M2();
  _dmass=PD4v.M(); _dmass2=PD4v.M2();

  TLorentzVector pW = PB4v - PD4v;
  TLorentzVector pY = PD4v + PL4v;
  TLorentzVector pNu = PB4v - pY;

  _q2 = pW.M2();
  _mm2 = pNu.M2();
  _wvar = PB4v.Dot(PD4v)/(_bmass*_dmass);
 
  _emiss = pNu.E();
  _pmiss = pNu.Rho();

  TLorentzVector pmu = PL4v;
  pmu.Boost(-PB4v.BoostVector());
  _elcm = pmu.E();

  TLorentzVector pWbframe = pW;
  pWbframe.Boost(-PB4v.BoostVector());
  TLorentzVector pmu1 = PL4v;
  TVector3 Wboost(-pW.X()/pW.T(),-pW.Y()/pW.T(),-pW.Z()/pW.T());
  //pmu1.Boost(-pW.BoostVector());
  pmu1.Boost(Wboost);

  _thl = pmu1.Angle(pWbframe.Vect());
  if( TMath::IsNaN(_thl) ) _thl=-10;
  //_thl = pmu1.Angle(pW.Vect());
  //cout << " vect > " << pW.E() << " pmu1.Print() " << pmu1.E() << endl ;
  _thl = pmu1.Angle(pWbframe.Vect());
}

void SemiDec::print()
{
  cout << _q2 << " " 
       << _wvar << " " 
       << _elcm << " " 
       << _thl << " " 
       << _emiss << " " 
       << _pmiss << endl; 
}
Double_t SemiDec::GetW() const { return _wvar; }
Double_t SemiDec::GetQ2() const { return _q2; }
Double_t SemiDec::GetMM2() const { return _mm2; }
Double_t SemiDec::GetElCM() const { return _elcm; }
Double_t SemiDec::GetThetaL() const { return _thl; }
Double_t SemiDec::GetPmiss() const { return _pmiss; }
Double_t SemiDec::GetEmiss() const { return _emiss; }

