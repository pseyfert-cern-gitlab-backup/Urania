// Include files 
#include <cmath>

// local
#include "Tagging.hh"
#include "Function.hh"
#include "RandomNumberGeneration.hh"
#include "ExponentialDistribution.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : ExponentialDistribution
//
// 2015-07-04 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;


//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
ExponentialDistribution::ExponentialDistribution(double _min, double _fall)
  : min(std::move(_min)),
    fall(std::move(_fall))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "constructing distribution as ExponentialDistribution" << std::endl;
}

ExponentialDistribution::ExponentialDistribution(const ExponentialDistribution& rhs) 
 : min(rhs.min),
   fall(rhs.fall)
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "copying distribution as ExponentialDistribution" << std::endl;
}

ExponentialDistribution::ExponentialDistribution(ExponentialDistribution&& rhs) 
 : min(std::move(rhs.min)),
   fall(std::move(rhs.fall))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "moving distribution as ExponentialDistribution" << std::endl;
}

//=============================================================================

double ExponentialDistribution::GetPDF(double x) const {
  if (x < min)
    return 0.0;
  else
    return exp(-(x-min)/fall)/fall;
}

double ExponentialDistribution::GetCDF(double x) const {
  if (x < min)
    return 0.0;
  else
    return 1.0 - exp(-(x-min)/fall);
}

double ExponentialDistribution::GetQuantile(double p) const {
  double x = min - fall*log(1.0 - p);
  return x;
}

double ExponentialDistribution::Expectation(const Function& f) const {
  Function prod = [&f,this] (double x) {
    double pdf = exp(-(x-min)/fall)/fall;
    return f(x)*pdf;
  };
  double result = Espresso::IntegrateAbove(prod,min);
  return result;  
} 

double ExponentialDistribution::GetRandom() const {
  return RandomNumberGeneration::GetExpo(min,fall);
}

double ExponentialDistribution::GetFourierCosTransform(double omega) const {
  double pfall = omega*fall;
  double pmin = omega*min;
  return (cos(pmin)-pfall*sin(pmin))/(1+pfall*pfall);
}

double ExponentialDistribution::GetFourierSinTransform(double omega) const {
  double pfall = omega*fall;
  double pmin = omega*min;
  return (sin(pmin)+pfall*cos(pmin))/(1+pfall*pfall);
}
