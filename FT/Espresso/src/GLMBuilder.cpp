// Include files 
#include "RooRealVar.h"
#include "RooCategory.h"

#include <fstream>
#include <boost/lexical_cast.hpp>

// local
#include "GLMBuilder.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : GLMBuilder
//
// 2017-03-25 : Vincenzo Battista, Jack Wimberley
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

using namespace Espresso;

std::tuple<RooArgList,RooArgList,RooMultiVarGaussian,
           RooGLMFunction,RooGLMFunction> Espresso::createRooGLMCalibration(const char *name, const char *title,
                                                                            RooAbsReal& _eta,
                                                                            std::string _calName,
                                                                            std::string _calFileName) {

  RooArgList m_coeffList(("plist_"+boost::lexical_cast<std::string>(name)).c_str());
  RooArgList m_deltacoeffList(("dplist_"+boost::lexical_cast<std::string>(name)).c_str());
  RooArgList m_allcoeffList(("allplist_"+boost::lexical_cast<std::string>(name)).c_str());
  std::size_t m_numCoeffs;
  
  // LOAD CALIBRATION
  std::ifstream reader(_calFileName);
  GLMCalibration m_cal = GLMCalibration::Deserialize(_calName, reader);
  std::unique_ptr<GLMCalibrationFunction> m_calfun = m_cal.getCalibrationFunction();

  // CREATE COEFFICIENT LISTS
  Vector coeffs = m_cal.GetCoeffs();
  Vector deltacoeffs = m_cal.GetDeltaCoeffs();
  m_numCoeffs = coeffs.size();
  if(m_numCoeffs != deltacoeffs.size())
    assert(0);
  for (std::size_t k=0; k<m_numCoeffs; ++k)
  {
    double cerr = 10*m_cal.GetError(k);
    RooRealVar* coeff = new RooRealVar( ("p_"+boost::lexical_cast<std::string>(k)+"_"+boost::lexical_cast<std::string>(name)).c_str(),
                                        ("p_{"+boost::lexical_cast<std::string>(k)+"}"+boost::lexical_cast<std::string>(title)).c_str(),
                                        coeffs[k],coeffs[k]-cerr,coeffs[k]+cerr);
    m_coeffList.add( *coeff );
    m_allcoeffList.add( *coeff );
  }
  
  for (std::size_t k=0; k<m_numCoeffs; ++k)
  {
    double dcerr = 10*m_cal.GetDeltaError(k);
    RooRealVar* dcoeff = new RooRealVar( ("dp_"+boost::lexical_cast<std::string>(k)+"_"+boost::lexical_cast<std::string>(name)).c_str(),
                                         ("#Delta p_{"+boost::lexical_cast<std::string>(k)+"}"+boost::lexical_cast<std::string>(title)).c_str(),
                                         deltacoeffs[k],deltacoeffs[k]-dcerr,deltacoeffs[k]+dcerr);
    m_deltacoeffList.add( *dcoeff );
    m_allcoeffList.add( *dcoeff );
  }

  // CREATE COVARIANCE MATRIX
  std::string covariance_name = ("covariance_"+boost::lexical_cast<std::string>(name));
  std::string covariance_title = ("covariance_"+boost::lexical_cast<std::string>(title));
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
  RooMultiVarGaussian m_covariance(covariance_name.c_str(),
				   covariance_title.c_str(),
				   m_allcoeffList, mu, sigma); // or maybe this should be a std::unique_ptr, etc

  // CREATE TWO ROOGLMFUNCTION OBJECTS
  std::string pos_name = ("b_"+boost::lexical_cast<std::string>(name));
  std::string pos_title = ("b_"+boost::lexical_cast<std::string>(title));
  RooGLMFunction omega_b(pos_name.c_str(),pos_title.c_str(),_eta,1,m_calfun->clone(),m_coeffList,m_deltacoeffList);

  std::string neg_name = ("bbar_"+boost::lexical_cast<std::string>(name));
  std::string neg_title = ("bbar_"+boost::lexical_cast<std::string>(title));
  RooGLMFunction omega_bbar(neg_name.c_str(),neg_title.c_str(),_eta,-1,m_calfun->clone(),m_coeffList,m_deltacoeffList);

  // RETURN LIST OF OBJECTS
  auto list = std::make_tuple(m_coeffList,m_deltacoeffList,m_covariance,omega_b,omega_bbar);
  return list;
}

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

GLMBuilder::GLMBuilder(const char *name, const char *title,
                     RooAbsReal& _eta,
                     std::string _calName,
                     std::string _calFileName)
  : components(createRooGLMCalibration(name,title,_eta,_calName,_calFileName))
{
}

//=============================================================================
// Destructor
//=============================================================================
GLMBuilder::~GLMBuilder() {} 

//=============================================================================
