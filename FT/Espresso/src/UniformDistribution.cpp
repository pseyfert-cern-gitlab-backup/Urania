// Include files 
#include <cmath>

// local
#include "Tagging.hh"
#include "RandomNumberGeneration.hh"
#include "UniformDistribution.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : UniformDistribution
//
// 2015-07-04 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
UniformDistribution::UniformDistribution(double _min, double _max)
  : min(std::move(_min)),
    max(std::move(_max))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "constructing distribution as UniformDistribution" << std::endl;
}

UniformDistribution::UniformDistribution(const UniformDistribution& rhs) 
 : min(rhs.min),
   max(rhs.max)
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "copying distribution as UniformDistribution" << std::endl;
}

UniformDistribution::UniformDistribution(UniformDistribution&& rhs) 
 : min(std::move(rhs.min)),
   max(std::move(rhs.max))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "moving distribution as UniformDistribution" << std::endl;
}

//=============================================================================

double UniformDistribution::GetPDF(double x) const {
  if (x < min or x > max)
    return 0.0;
  else
    return 1.0/(max-min);
}

double UniformDistribution::GetCDF(double x) const {
    if (x <= min)
      return 0.0;
    else if (x >= max)
      return 1.0;
    else
      return (x-min)/(max-min);
}

double UniformDistribution::GetQuantile(double p) const {
  return min + p*(max-min);
}

double UniformDistribution::Expectation(const Function& f) const {
  double result = Espresso::Integrate(f,min,max);
  result /= (max-min);
  return result;  
} 

double UniformDistribution::GetRandom() const {
  double min = GetMin();
  double max = GetMax();
  return RandomNumberGeneration::GetUniform(min,max);
}

double UniformDistribution::GetFourierCosTransform(double omega) const {
  /* The integral of cos(omega t) from min to max is
     1/omega sin(omega t) at max - min
  */
  double val = sin(omega*max) - sin(omega*min);
  val /= omega;
  return val;
}

double UniformDistribution::GetFourierSinTransform(double omega) const {
  /* The integral of sin(omega t) from min to max is
     1/omega -cos(omega t) at max - min
  */
  double val = cos(omega*min) - cos(omega*max);
  val /= omega;
  return val;
}


