// Include files
#define _USE_MATH_DEFINES
#include <cmath>

#include "RegressionFunctions.hh"
#include "Statistics.hh"

double Espresso::Regression::InvLink(double eta, LinkType link) {
  double val = 0.0;
  if (link == LinkType::Mistag) 
    val = eta; 
  else if (link == LinkType::Logit) 
    val = log(1-eta)-log(eta);
  else if (link == LinkType::Probit) 
    val = sqrt(2.0)*Espresso::erfinv(1-2*eta);
  else if (link == LinkType::Cauchit) 
    val = -tan(M_PI*eta-M_PI_2);
  else
    val = 0;
  if (std::isnan(val)) std::cout << __LINE__ << ": " << eta << " => " << val << std::endl;
  return val;
}

double Espresso::Regression::DInvLink(double eta, LinkType link) {
  double val = 0.0;
  if (link == LinkType::Mistag) 
    val = 1; 
  else if (link == LinkType::Logit) 
    val = -1.0/(eta*(1-eta));
  else if (link == LinkType::Probit) 
    val = -exp(Espresso::erfinv(1-2*eta)*Espresso::erfinv(1-2*eta))*sqrt(2.0*M_PI);
  else if (link == LinkType::Cauchit) 
    val = -M_PI*(1+tan(M_PI*eta-M_PI_2)*tan(M_PI*eta-M_PI_2));
  else
    val = 0;
  if (std::isnan(val)) std::cout << __LINE__ << ": " << eta << " => " << val << std::endl;
  return val;
}

double Espresso::Regression::Link(double g, LinkType link) {
  double val = 0.0;
  if (link == LinkType::Mistag) 
    val = g; 
  else if (link == LinkType::Logit) 
    val = 1.0/(1+exp(g));
  else if (link == LinkType::Probit) 
    val = 0.5*(1.0 - erf(g/sqrt(2.0)));
  else if (link == LinkType::Cauchit) 
    val = 0.5 - atan(g)/M_PI;
  else
    val = 0;
  if (std::isnan(val)) std::cout << __LINE__ << ": " << g << " => " << val << std::endl;
  return val;
}

double Espresso::Regression::DLink(double g, LinkType link) {
  double val = 0.0;
  if (link == LinkType::Mistag) 
    val = 1; 
  else if (link == LinkType::Logit) 
    val = -0.5/(1+cosh(g)); // = pi*(1-pi), pi = Link(g)
  else if (link == LinkType::Probit) 
    val = -exp(-0.5*g*g)/sqrt(2.0*M_PI);
  else if (link == LinkType::Cauchit) 
    val = -1.0/(M_PI*(1+g*g)); // or Sin(M_PI*p)^2/M_PI
  else
    val = 0;
  if (std::isnan(val)) std::cout << __LINE__ << ": " << g << " => " << val << std::endl;
  return val;
}
