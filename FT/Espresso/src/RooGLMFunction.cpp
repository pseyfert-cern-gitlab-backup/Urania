#include "RooRealVar.h"
#include "RooCategory.h"

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

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

std::tuple<RooArgList,RooArgList,RooMultiVarGaussian,
	   RooGLMFunction,RooGLMFunction> Espresso::createRooGLMCalibration(const char *name, const char *title,
									    RooAbsReal& _eta,
									    std::string _calName,
									    std::string _calFileName) {
  RooArgList m_coeffList;
  RooArgList m_deltacoeffList;
  RooArgList m_allcoeffList;
  std::size_t m_numCoeffs;
  
  // LOAD CALIBRATION
  std::ifstream reader(_calFileName);
  Espresso::GLMCalibration m_cal = Espresso::GLMCalibration::Deserialize(_calName, reader);
  std::unique_ptr<Espresso::GLMCalibrationFunction> m_calfun = m_cal.getCalibrationFunction();

  // CREATE COEFFICIENT LISTS
  Espresso::Vector coeffs = m_cal.GetCoeffs();
  Espresso::Vector deltacoeffs = m_cal.GetDeltaCoeffs();
  m_numCoeffs = coeffs.size();
  if(m_numCoeffs != deltacoeffs.size())
    assert(0);
  for (std::size_t k=0; k<m_numCoeffs; ++k)
  {
    RooRealVar* coeff = new RooRealVar( ("p_"+boost::lexical_cast<std::string>(k)+"_"+boost::lexical_cast<std::string>(name)).c_str(),
                                        ("p_{"+boost::lexical_cast<std::string>(k)+"}"+boost::lexical_cast<std::string>(title)).c_str(),
                                        coeffs[k],-100.0,100.0);
    m_coeffList.add( *coeff );
    m_allcoeffList.add( *coeff );
    RooRealVar* dcoeff = new RooRealVar( ("dp_"+boost::lexical_cast<std::string>(k)+"_"+boost::lexical_cast<std::string>(name)).c_str(),
                                         ("#Delta p_{"+boost::lexical_cast<std::string>(k)+"}"+boost::lexical_cast<std::string>(title)).c_str(),
                                         deltacoeffs[k],-100.0,100.0);
    m_deltacoeffList.add( *dcoeff );
    m_allcoeffList.add( *dcoeff );
  }

  // CREATE CONSTRAINT MATRIX
  std::string constraint_name = ("constraint_"+boost::lexical_cast<std::string>(name));
  std::string constraint_title = ("constraint_"+boost::lexical_cast<std::string>(title));
  TVectorD mu(2*m_numCoeffs);
  TMatrixDSym sigma(2*m_numCoeffs);
  for (std::size_t row = 0; row < m_numCoeffs; ++row) {
    mu[row] = m_cal.GetCoeff(row);
    mu[row+m_numCoeffs] = m_cal.GetDeltaCoeff(row);
    for (std::size_t col = row; col < m_numCoeffs; ++col) {
      sigma[row][col] = m_cal.GetCovariance(row,col);
      sigma[row][col+m_numCoeffs] = m_cal.GetCrossCovariance(row,col);
      sigma[col][row+m_numCoeffs] = m_cal.GetCrossCovariance(col,row);
      sigma[row+m_numCoeffs][col+m_numCoeffs] = m_cal.GetDeltaCovariance(row,col);
    }
  }
  // fill in lower diagonal
  for (std::size_t row = 0; row < 2*m_numCoeffs; ++row) {
    for (std::size_t col = 0; col < row; ++col) {
      sigma[row][col] = sigma[col][row];
    }
  }
  RooMultiVarGaussian m_constraint(constraint_name.c_str(),
				   constraint_title.c_str(),
				   m_allcoeffList, mu, sigma); // or maybe this should be a std::unique_ptr, etc
  
  // CREATE TWO ROOGLMFUNCTION OBJECTS
  std::string pos_name = ("b_"+boost::lexical_cast<std::string>(name));
  std::string pos_title = ("b_"+boost::lexical_cast<std::string>(title));
  RooGLMFunction omega_b(pos_name.c_str(),pos_title.c_str(),_eta,1,m_calfun->clone(),m_coeffList,m_deltacoeffList);

  std::string neg_name = ("bbar_"+boost::lexical_cast<std::string>(name));
  std::string neg_title = ("bbar_"+boost::lexical_cast<std::string>(title));
  RooGLMFunction omega_bbar(neg_name.c_str(),neg_title.c_str(),_eta,-1,m_calfun->clone(),m_coeffList,m_deltacoeffList);

  // RETURN LIST OF OBJECTS
  auto list = std::make_tuple(m_coeffList,m_deltacoeffList,m_constraint,omega_b,omega_bbar);
  return list;
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
