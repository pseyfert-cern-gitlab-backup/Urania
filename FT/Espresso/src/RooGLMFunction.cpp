#include "RooRealVar.h"
#include "RooCategory.h"

#include <iostream>

#include "RooGLMFunction.hh"

using namespace Espresso;
  
RooGLMFunction::RooGLMFunction(const char *name, const char *title,
                               RooAbsReal& _eta,
                               Int_t _flavour,
			       std::unique_ptr<Espresso::GLMCalibrationFunction> _calfun,
			       const RooArgList& _coeffList,
			       const RooArgList& _deltacoeffList) :
  RooAbsReal(name,title),
  m_eta("eta","eta",this,_eta),
  m_coeffListProxy("!coeffs","list of coeffs",this),
  m_deltacoeffListProxy("!deltacoeffs","list of deltacoeffs",this),
  m_flavour(Espresso::FlavourFromInt( _flavour )),
  m_calfun(std::move(_calfun)),
  m_numCoeffs(_coeffList.getSize())
{
  m_coeffListProxy.add(_coeffList);
  m_deltacoeffListProxy.add(_deltacoeffList);
}

RooGLMFunction::RooGLMFunction(const RooGLMFunction& other, const char *name) :
  RooAbsReal(other,name),
  m_eta("eta",this,other.m_eta),
  m_coeffListProxy("!coeffs",this,other.m_coeffListProxy),
  m_deltacoeffListProxy("!deltacoeffs",this,other.m_deltacoeffListProxy),
  m_flavour(other.m_flavour),
  m_calfun(other.m_calfun->clone()),
  m_numCoeffs(other.m_numCoeffs)
{
}

std::size_t RooGLMFunction::getNumCoeffs() const { return m_numCoeffs; }

Double_t RooGLMFunction::evaluate() const 
{
  Double_t eta = m_eta;

  Espresso::Vector p(m_numCoeffs);
  Espresso::Vector dp(m_numCoeffs);
 
  RooFIter coeffIter = m_coeffListProxy.fwdIterator();
  RooAbsReal* coeff;
  std::size_t k = 0;
  while ((coeff = (RooAbsReal*)coeffIter.next())) {
    p[k] = coeff->getVal();
    ++k;
  }

  RooFIter deltacoeffIter = m_coeffListProxy.fwdIterator();
  RooAbsReal* deltacoeff;
  std::size_t dk = 0;
  while ((deltacoeff = (RooAbsReal*)deltacoeffIter.next())) {
    dp[dk] = deltacoeff->getVal();
    ++dk;
  }
  
  if (m_flavour == Espresso::Flavour::Pos)
    p += 0.5*dp;  
  else if (m_flavour == Espresso::Flavour::Neg)
    p -= 0.5*dp;
  return m_calfun->Value(eta,p.GetArray());  
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::RooGLMFunction)
