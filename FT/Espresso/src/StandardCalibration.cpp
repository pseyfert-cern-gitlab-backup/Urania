// Include files 
#include "Vector.hh"
#include "Matrix.hh"
#include <cmath>
#include <algorithm>

// local
#include "StandardCalibration.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : StandardCalibration
//
// 2015-05-14 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
StandardCalibration::StandardCalibration()
  : L(Regression::LinkType::Mistag),
    m_eta(0.0),
    m_p0(0.0),
    m_p1(1.0),
    m_dp0(0.0),
    m_dp1(0.0),
    m_etaerr(0.0),
    m_p0err(0.0),
    m_p1err(0.0),
    m_dp0err(0.0),
    m_dp1err(0.0),
    m_p0p1corr(0.0),
    m_p0dp0corr(0.0),
    m_p0dp1corr(0.0),
    m_p1dp0corr(0.0),
    m_p1dp1corr(0.0),
    m_dp0dp1corr(0.0)
{
}

//=============================================================================
// Perform calibration
//=============================================================================
double StandardCalibration::Value(double eta) const
{
  double x = Regression::InvLink(eta,L);
  double y = m_eta + m_p0 + m_p1*(x-m_eta);
  double omega = Regression::Link(y,L);
  return omega;
}

ConfidenceInterval StandardCalibration::ValueRange(double eta, int sigmaConf) const
{
  double x = Regression::InvLink(eta,L);
  double y = m_eta + m_p0 + m_p1*(x-m_eta);
  double diff = x-m_eta;
  double delta = sqrt(m_p0err*m_p0err+2*m_p0p1corr*m_p0err*m_p1err*diff+m_p1err*m_p1err*diff*diff);
  double yhigh = y + sigmaConf*delta;
  double ylow = y - sigmaConf*delta;
  double omega = Regression::Link(y,L);
  double omegaHigh = Regression::Link(yhigh,L);
  double omegaLow = Regression::Link(ylow,L);
  ConfidenceInterval range = std::make_tuple(omega,omegaLow,omegaHigh);
  return range;
}

double StandardCalibration::Value(double eta, Flavour flavour) const
{
  double x = Regression::InvLink(eta,L);
  double y = m_eta + m_p0 + m_p1*(x-m_eta);
  double dy = m_dp0 + m_dp1*(x-m_eta);
  if (flavour == Flavour::Pos)
    y += 0.5*dy;
  else if (flavour == Flavour::Neg)
    y -= 0.5*dy;
  double omega = Regression::Link(y,L);
  return omega;
}

Vector StandardCalibration::Derivative(double eta) const
{
  // ilink(omega) = m_eta + m_p0 + m_p1*(ilink(eta)-m_eta)
  // => d[ilink(omega)]/d[omega] * d[omega]/d[p0] = 1
  // etc.
  Vector grad(2);
  grad[0] = 1;
  grad[1] = eta-m_eta;
  double omega = this->operator()(eta);
  double dilink = Regression::DInvLink(omega,L);
  grad /= dilink;
  return grad;
}

Vector StandardCalibration::Derivative(double eta, Flavour flavour) const
{
  // ilink(omega) = m_eta + m_p0 + m_p1*(ilink(eta)-m_eta)
  // => d[ilink(omega)]/d[omega] * d[omega]/d[p0] = 1
  // etc.
  Vector grad(4);
  grad[0] = 1;
  grad[1] = eta-m_eta;
  double x = 0.0;
  if (flavour == Flavour::Pos)
    x = 0.5;
  else if (flavour == Flavour::Neg)
    x = -0.5;
  grad[2] = x*grad[0];
  grad[3] = x*grad[1];
  double omega = this->Value(eta,flavour);
  double dilink = Regression::DInvLink(omega,L);
  grad /= dilink;
  return grad;
}

double StandardCalibration::GetOffset(double eta) const {
  return Regression::InvLink(eta,L);
}

Vector StandardCalibration::GetBasis(double eta) const {
  return Vector({m_p0,(m_p1-1)*(eta-m_eta)});
}

Vector StandardCalibration::GetCoeffs() const 
{
  Vector v(2);
  v(0) = GetCoeff(0);
  v(1) = GetCoeff(1);
  return v;
}

Vector StandardCalibration::GetDeltaCoeffs() const 
{
  Vector v(2);
  v(0) = GetDeltaCoeff(0);
  v(1) = GetDeltaCoeff(1);
  return v;
}

Matrix StandardCalibration::GetCovarianceMatrix() const
{
  Matrix cov(2,2);
  cov(0,0) = GetCovariance(0,0);
  cov(1,1) = GetCovariance(1,1);
  cov(0,1) = GetCovariance(0,1);
  cov(1,0) = GetCovariance(0,1);
  return cov;
}

Matrix StandardCalibration::GetDeltaCovarianceMatrix() const
{
  Matrix cov(2,2);
  cov(0,0) = GetDeltaCovariance(0,0);
  cov(1,1) = GetDeltaCovariance(1,1);
  cov(0,1) = GetDeltaCovariance(0,1);
  cov(1,0) = GetDeltaCovariance(0,1);
  return cov;
}

Matrix StandardCalibration::GetCrossCovarianceMatrix() const
{
  Matrix cov(2,2);
  cov(0,0) = GetCrossCovariance(0,0);
  cov(1,1) = GetCrossCovariance(1,1);
  cov(0,1) = GetCrossCovariance(0,1);
  cov(1,0) = GetCrossCovariance(0,1);
  return cov;
}

double StandardCalibration::GetCoeff(unsigned int k) const {
  switch (k)  
  {
  case 0: return 1-2*(m_eta+m_p0);
  case 1: return m_p1;
  default: return 0.0;
  }
}

double StandardCalibration::GetError(unsigned int k) const {
  switch (k)  
  {
  case 0: return m_p0err;
  case 1: return m_p1err;
  default: return 0.0;
  }
}

double StandardCalibration::GetDeltaCoeff(unsigned int k) const {
  switch (k)  
  {
  case 0: return m_dp0;
  case 1: return m_dp1;
  default: return 0.0;
  }
}

double StandardCalibration::GetDeltaError(unsigned int k) const {
  switch (k)  
  {
  case 0: return m_dp0err;
  case 1: return m_dp1err;
  default: return 0.0;
  }
}

double StandardCalibration::GetCovariance(unsigned int k, unsigned int l) const {
  double rho = StandardCalibration::GetCorrelation(k,l);
  double a, b;
  switch (k)  
  {
  case 0: a = m_p0err; break;
  case 1: a = m_p1err; break;
  default: a = 0.0;
  }
  switch (l)  
  {
  case 0: b = m_p0err; break;
  case 1: b = m_p1err; break;
  default: b = 0.0;
  }
  return rho*a*b;
}

double StandardCalibration::GetCorrelation(unsigned int k, unsigned int l) const {
  if (k >= 2 or l >= 2)
    return 0.0;
  if (k==l)
    return 1.0;
  return -m_p0p1corr;
}

double StandardCalibration::GetDeltaCovariance(unsigned int k, unsigned int l) const
{
  double rho = GetDeltaCorrelation(k,l);
  double a, b;
  switch (k)  
  {
  case 0: a = m_dp0err; break;
  case 1: a = m_dp1err; break;    
  default: a = 0.0;
  }
  switch (l)  
  {
  case 0: b = m_dp0err; break;
  case 1: b = m_dp1err; break;    
  default: b = 0.0;
  }
  return rho*a*b;
}

double StandardCalibration::GetDeltaCorrelation(unsigned int k, unsigned int l) const
{
  if (k >= 2 or l >= 2)
    return 0.0;
  if (k==l)
    return 1.0;
  return -m_dp0dp1corr;
}

double StandardCalibration::GetCrossCovariance(unsigned int k, unsigned int l) const
{
  double rho = GetCrossCorrelation(k,l);
  double a, b;
  switch (k)  
  {
  case 0: a = m_p0err; break;
  case 1: a = m_p1err; break;    
  default: a = 0.0;
  }
  switch (l)  
  {
  case 0: b = m_dp0err; break;
  case 1: b = m_dp1err; break;    
  default: b = 0.0;
  }
  return rho*a*b;
}

double StandardCalibration::GetCrossCorrelation(unsigned int k, unsigned int l) const
{
  if (k >= 2 or l >= 2)
    return 0.0;
  
  switch (k) 
  {
  case 0:
    switch (l) 
    {
    case 0: return m_p0dp0corr;
    case 1: return -m_p0dp1corr;
    default: return 0.0;
    }
  case 1:
    switch (l) 
    {
    case 0: return -m_p1dp0corr;
    case 1: return m_p1dp1corr;
    default: return 0.0;
    }
  default: return 0.0;
  }
}

void StandardCalibration::print(std::ostream& os) const
{
  os << std::endl;
  if (L == Regression::LinkType::Mistag) {
    os << " -- MISTAG BASIS --" << std::endl;
  } else if (L == Regression::LinkType::Logit) {
    os << " -- LOGIT BASIS --" << std::endl;
  } else if (L == Regression::LinkType::Probit) {
    os << " -- PROBIT BASIS --" << std::endl;
  } else if (L == Regression::LinkType::Cauchit) {
    os << " -- CAUCHIT BASIS --" << std::endl;
  }
  os << std::endl;
  os << "<eta> = " << std::setprecision(5) << this->Eta()
     << " +-" << std::setprecision(5) << this->EtaErr() << std::endl;;
  os << "δp0 = " << std::setprecision(5) << this->P0()
     << " +-" << std::setprecision(5) << this->P0Err()
     << std::endl;;
  os << "p1 = " << std::setprecision(5) << this->P1()
     << " +-" << std::setprecision(5) << this->P1Err()
     << std::endl;
  os << "Δp0 = " << std::setprecision(5) << this->DeltaP0()
     << " +-" << std::setprecision(5) << this->DeltaP0Err()
     << std::endl;;
  os << "Δp1 = " << std::setprecision(5) << this->DeltaP1()
     << " +-" << std::setprecision(5) << this->DeltaP1Err()
     << std::endl;
  
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::StandardCalibration)

//=============================================================================
