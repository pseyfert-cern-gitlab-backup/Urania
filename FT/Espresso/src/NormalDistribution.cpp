// Include files 
#include <cmath>

// local
#include "Tagging.hh"
#include "RandomNumberGeneration.hh"
#include "NormalDistribution.hh"
#include "Statistics.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : NormalDistribution
//
// 2015-07-04 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;


//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
NormalDistribution::NormalDistribution(double _mu, double _sigma)
  : mu(std::move(_mu)),
    sigma(std::move(_sigma))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "constructing distribution as NormalDistribution" << std::endl;
}

NormalDistribution::NormalDistribution(const NormalDistribution& rhs) 
 : mu(rhs.mu),
   sigma(rhs.sigma)
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "copying distribution as NormalDistribution" << std::endl;
}

NormalDistribution::NormalDistribution(NormalDistribution&& rhs) 
 : mu(std::move(rhs.mu)),
   sigma(std::move(rhs.sigma))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "moving distribution as NormalDistribution" << std::endl;
}

//=============================================================================

double NormalDistribution::GetPDF(double x) const {
  double z = (x - mu) / (sigma);
  double g = exp(-0.5*z*z)/(sigma*sqrt(2*3.14159265359));
  return g;
}

double NormalDistribution::GetCDF(double x) const {
  double z = (x - mu) / (sigma);
  double cdf = 0.5*(1+erf(z/sqrt(2.0)));
  return cdf;
}

double NormalDistribution::GetQuantile(double p) const {
  double z = sqrt(2.0)*erfinv(2*p-1);
  double x = mu + z*sigma;
  return x;
}

double NormalDistribution::Expectation(const Function& f) const {
  Function prod = [&f,this] (double x) {
    double z = (x - mu) / (sigma);
    double g = exp(-0.5*z*z)/(sigma*sqrt(2*3.14159265359));
    return f(x)*g;
  };
  double result = Espresso::Integrate(prod);
  return result;  
} 

double NormalDistribution::GetRandom() const {
  return RandomNumberGeneration::GetNorm(mu,sigma);
}

double NormalDistribution::GetFourierCosTransform(double omega) const {
  // The fourier transform of a gaussian is a gaussian
  double z = omega*sigma;
  return cos(omega*mu)*exp(-0.5*z*z);
}

double NormalDistribution::GetFourierSinTransform(double omega) const {
  // The fourier transform of a gaussian is a gaussian
  double z = omega*sigma;
  return sin(omega*mu)*exp(-0.5*z*z);
}
