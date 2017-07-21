#include "GLMCalibrationFunction.hh"

#include <iomanip>

#include "GLMPolynomial.hh"

using namespace Espresso;

GLMCalibrationFunction::GLMCalibrationFunction()
  : glm(std::make_unique<GLMPolynomial>(1)),
    length(glm->NumParams()),
    L(Regression::DefaultLinkType),
    etac(0.5),
    offsetc(0.0),
    basisc(this->GetBasis(etac))
{
}

GLMCalibrationFunction::GLMCalibrationFunction(const GLMModel& _glm, Regression::LinkType _L)
  : glm(_glm.clone()),
    length(glm->NumParams()),
    L(_L),
    etac(0.5),
    offsetc(0.0),
    basisc(this->GetBasis(etac))
{
}

GLMCalibrationFunction::GLMCalibrationFunction(const GLMCalibrationFunction& rhs)
  : glm(rhs.glm->clone()),
    length(rhs.length),
    L(rhs.L),
    etac(0.5),
    offsetc(0.0),
    basisc(this->GetBasis(etac))
{
}

GLMCalibrationFunction& GLMCalibrationFunction::operator= (GLMCalibrationFunction rhs) {
  glm.swap(rhs.glm);
  length = rhs.length;
  L = rhs.L;
  etac = rhs.etac;
  basisc = rhs.basisc;
  return *this;
}

double GLMCalibrationFunction::GetOffset(double eta) const {
  if (glm->SubtractEta()) {
    return Regression::InvLink(eta,L);
  } else {
    return 0.0;
  }
}

Vector GLMCalibrationFunction::GetBasis(double eta) const {
  if (glm->PreProcessWithLink()) {
    return glm->GetBasis(Regression::InvLink(eta,L));
  } else {
    return glm->GetBasis(eta);
  }
}

double GLMCalibrationFunction::Value(double eta, const double* theta) const {
  if (eta != etac)
    updateCache(eta);
  return Value(basisc,L,theta,offsetc);
}

double GLMCalibrationFunction::Derivative(double eta, unsigned int k, const double* theta) const {
  if (eta != etac)
    updateCache(eta);
  return Derivative(basisc,L,k,theta,offsetc);
}

Vector GLMCalibrationFunction::Derivative(double eta, const double* theta) const {
  if (eta != etac)
    updateCache(eta);
  return Derivative(basisc,L,theta,offsetc);
}

void GLMCalibrationFunction::updateCache(double eta) const {
  etac = eta;
  offsetc = this->GetOffset(eta);
  basisc = this->GetBasis(eta);
}

void GLMCalibrationFunction::print(std::ostream& os) const {
  if (L == Regression::LinkType::Mistag) {
    os << " -- MISTAG BASIS --" << std::endl;
  } else if (L == Regression::LinkType::Logit) {
    os << " -- LOGIT BASIS --" << std::endl;
  } else if (L == Regression::LinkType::Probit) {
    os << " -- PROBIT BASIS --" << std::endl;
  } else if (L == Regression::LinkType::Cauchit) {
    os << " -- CAUCHIT BASIS --" << std::endl;
  } else if (L == Regression::LinkType::RLogit) {
    os << " -- RLOGIT BASIS --" << std::endl; 
  } else if (L == Regression::LinkType::RProbit) {
    os << " -- RPROBIT BASIS --" << std::endl; 
  } else if (L == Regression::LinkType::RCauchit) {
    os << " -- RCAUCHIT BASIS --" << std::endl; 
  }
  os << std::endl;
  os << *glm;
}

double GLMCalibrationFunction::Value(Vector glmBasis, Regression::LinkType L, const double* theta, double offset) {
  double Eta = offset;
  for (unsigned int k = 0; k < glmBasis.size(); k++)
    Eta += theta[k] * glmBasis[k];
  return Regression::Link(Eta,L);
}

double GLMCalibrationFunction::Derivative(Vector glmBasis, Regression::LinkType L, unsigned int k, const double* theta, double offset) {
  double Eta = offset;
  for (unsigned int k = 0; k < glmBasis.size(); k++)
    Eta += theta[k] * glmBasis[k];
  double dLinkdEta = Regression::DLink(Eta,L);
  double dEtadTheta = glmBasis[k];
  return dLinkdEta*dEtadTheta;
}

Vector GLMCalibrationFunction::Derivative(Vector glmBasis, Regression::LinkType L, const double* theta, double offset) {
  double Eta = offset;
  for (unsigned int k = 0; k < glmBasis.size(); k++) {
    Eta += theta[k] * glmBasis[k];
  }
  double dLinkdEta = Regression::DLink(Eta,L);
  return dLinkdEta*glmBasis;
}
 
BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::GLMCalibrationFunction)
