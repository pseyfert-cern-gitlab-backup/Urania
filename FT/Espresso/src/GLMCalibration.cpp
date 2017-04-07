#include "GLMCalibration.hh"

#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include "GLMPolynomial.hh"
#include "GLMBSpline.hh"
#include "GLMNSpline.hh"
#include "GLMCalibration.hh"
#include "StandardCalibration.hh"

using namespace Espresso;

GLMCalibration::GLMCalibration()
  : TypicalCalibration(2),
    func(GLMPolynomial(1),Regression::DefaultLinkType)
{
}

GLMCalibration::GLMCalibration(const GLMModel& _glm, Regression::LinkType _L)
  : TypicalCalibration(_glm.NumParams()),
    func(_glm,_L)
{
}

GLMCalibration::GLMCalibration(const GLMCalibrationFunction& _func)
  : TypicalCalibration(_func.NumParams()),
    func(_func)
{
}

GLMCalibration::GLMCalibration(const GLMModel& _glm, Regression::LinkType _L,
			       const Vector& _coeffs, const Vector& _delta_coeffs)
  : TypicalCalibration(_glm.NumParams(),_coeffs,_delta_coeffs),
    func(_glm,_L)
{
}

GLMCalibration::GLMCalibration(const GLMCalibrationFunction& _func,
			       const Vector& _coeffs, const Vector& _delta_coeffs)
  : TypicalCalibration(_func.NumParams(),_coeffs,_delta_coeffs),
    func(_func)
{
}

GLMCalibration::GLMCalibration(const GLMModel& _glm, Regression::LinkType _L,
			       const Vector& _coeffs, const Vector& _delta_coeffs,
			       const Matrix& _covariance, const Matrix& _delta_covariance, const Matrix& _cross_covariance)
  : TypicalCalibration(_glm.NumParams(),_coeffs,_delta_coeffs,_covariance,_delta_covariance,_cross_covariance),
    func(_glm,_L)
{
}

GLMCalibration::GLMCalibration(const GLMCalibrationFunction& _func,
			       const Vector& _coeffs, const Vector& _delta_coeffs,
			       const Matrix& _covariance, const Matrix& _delta_covariance, const Matrix& _cross_covariance)
  : TypicalCalibration(_func.NumParams(),_coeffs,_delta_coeffs,_covariance,_delta_covariance,_cross_covariance),
    func(_func)
{
}

GLMCalibration::GLMCalibration(const GLMCalibration& rhs)
  : TypicalCalibration(rhs),
    func(rhs.func)
{
}

GLMCalibration GLMCalibration::Deserialize(std::string name, std::ifstream& ifs) {
  try {
    boost::archive::xml_iarchive ia(ifs);
    ia.register_type<Espresso::GLMPolynomial>();
    ia.register_type<Espresso::GLMNSpline>();
    ia.register_type<Espresso::GLMBSpline>();
    ia.register_type<Espresso::GLMCalibrationFunction>();
    ia.register_type<Espresso::StandardCalibration>();
    ia.register_type<Espresso::GLMCalibration>();
    Espresso::GLMCalibration cal;
    std::string name = "blank";
    ia >> boost::serialization::make_nvp(name.c_str(),cal);
    return std::move(cal);
  } catch (boost::archive::archive_exception ex) {
    throw DeserializationException();
  }
}

void GLMCalibration::Serialize(std::string name, std::ofstream& ofs) const {
  boost::archive::xml_oarchive oa(ofs);
  oa.register_type<Espresso::GLMPolynomial>();
  oa.register_type<Espresso::GLMNSpline>();
  oa.register_type<Espresso::GLMBSpline>();
  oa.register_type<Espresso::GLMCalibrationFunction>();
  oa.register_type<Espresso::GLMCalibration>();
  oa.register_type<Espresso::StandardCalibration>();
  oa << boost::serialization::make_nvp(name.c_str(),*this);
}

double GLMCalibration::Value(double eta) const {
  return func.Value(eta,GetCoeffArray());
}

Vector GLMCalibration::Derivative(double eta) const {
  return func.Derivative(eta,GetCoeffArray());
}

ConfidenceInterval GLMCalibration::ValueRange(double eta, int sigmaConf) const {
  // Get value and derivative
  double omega = Value(eta);
  Vector domega = Derivative(eta);

  // Value and derivative has correction for link function
  // Must undo this and go into log-odds space
  Regression::LinkType L = func.CalibrationLink();
  double y = Regression::InvLink(omega,L);
  Vector dy = domega/Regression::DLink(y,L);

  // Matrix Magic
  const Matrix& cov = GetCovarianceMatrix();
  double delta = sqrt(dy*(cov*dy));
  double yhigh = y + sigmaConf*delta;
  double ylow = y - sigmaConf*delta;
  double omegaHigh = Regression::Link(yhigh,L);
  double omegaLow = Regression::Link(ylow,L);
  ConfidenceInterval range = std::make_tuple(omega,omegaLow,omegaHigh);
  return range;
}

double GLMCalibration::Value(double eta, Flavour flavour) const {
  Vector p = GetCoeffs();
  Vector dp = GetDeltaCoeffs();
  if (flavour == Flavour::Pos)
    p += 0.5*dp;
  else if (flavour == Flavour::Neg)
    p -= 0.5*dp;
  return func.Value(eta,p.GetArray());
}

Vector GLMCalibration::Derivative(double eta,Flavour flavour) const {
  Vector p = GetCoeffs();
  Vector dp = GetDeltaCoeffs();
  if (flavour == Flavour::Pos)
    p += 0.5*dp;
  else if (flavour == Flavour::Neg)
    p -= 0.5*dp;
  Vector grad(2*(func.NumParams()));
  for (unsigned int k =  0; k < func.NumParams(); k++) {
    double d = func.Derivative(eta,k,p.GetArray());
    grad[k] = d;
    if (flavour == Flavour::Pos)
      grad[k+func.NumParams()] = 0.5*d;
    else if (flavour == Flavour::Neg)
      grad[k+func.NumParams()] = -0.5*d;
  }
  return grad;
}

void GLMCalibration::print(std::ostream& os) const {
  os << std::endl;
  os << func;
  os << std::endl;
  Calibration::print(os);
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::GLMCalibration)
