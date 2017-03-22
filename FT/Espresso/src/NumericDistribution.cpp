#include <cmath>

#include "NumericDistribution.hh"
#include "RootFinder.hh"
#include "RandomNumberGeneration.hh"

using namespace Espresso;

NumericDistribution::NumericDistribution()
  : interval(Espresso::NumericDistribution::Interval::UNBOUNDED),
    min(0.0),
    max(0.0),
    pdf([] (double) { return 0.0; }),
    cdf([] (double) { return 0.0; }),
    norm(1.0)
{
}

NumericDistribution::NumericDistribution(const Function& _pdf)
  : interval(Espresso::NumericDistribution::Interval::UNBOUNDED),
    min(0.0),
    max(0.0),
    pdf(_pdf),
    cdf([this] (double x) {
      return Espresso::IntegrateBelow(pdf,x);
    }),
    norm(Espresso::Integrate(pdf))
{
}

NumericDistribution::NumericDistribution(const Function& _pdf, const Function& _cdf)
  : interval(Espresso::NumericDistribution::Interval::UNBOUNDED),
    min(0.0),
    max(0.0),
    pdf(_pdf),
    cdf(_cdf),
    norm(1.0)
{
}

NumericDistribution::NumericDistribution(const Function& _pdf, double _limit, bool flipped)
  : interval((flipped) ? Espresso::NumericDistribution::Interval::UPPER_BOUNDED : Espresso::NumericDistribution::Interval::LOWER_BOUNDED),
    min((flipped) ? 0.0 : _limit),
    max((flipped) ? _limit : 0.0),
    pdf(_pdf),
    cdf(),
    norm((flipped) ? Espresso::IntegrateBelow(pdf,max) : Espresso::IntegrateAbove(pdf,min))
{
  if (flipped) {
    cdf = [this] (double x) {
      if (x >= max)
	return 1.0;
      else
	return Espresso::IntegrateBelow(pdf,x);
    };
  } else {
    cdf = [this] (double x) {
      if (x <= min)
	return 0.0;
      else
	return Espresso::Integrate(pdf,min,x);
    };
  }    
}

NumericDistribution::NumericDistribution(const Function& _pdf, const Function& _cdf, double _limit, bool flipped)
  : interval((flipped) ? Espresso::NumericDistribution::Interval::UPPER_BOUNDED : Espresso::NumericDistribution::Interval::LOWER_BOUNDED),
    min((flipped) ? 0.0 : _limit),
    max((flipped) ? _limit : 0.0),
    pdf(_pdf),
    cdf(_cdf),
    norm(1.0)
{
}

NumericDistribution::NumericDistribution(const Function& _pdf, double _min, double _max)
  : interval(Espresso::NumericDistribution::Interval::BOUNDED),
    min(_min),
    max(_max),
    pdf(_pdf),
    cdf([this] (double x) {
	if (x <= min) return 0.0;
	else if (x >= max) return 1.0;
	else return Espresso::Integrate(pdf,min,x);
      }),
    norm(Espresso::Integrate(pdf,min,max))
{
}

NumericDistribution::NumericDistribution(const Function& _pdf, const Function& _cdf, double _min, double _max)
  : interval(Espresso::NumericDistribution::Interval::BOUNDED),
    min(_min),
    max(_max),
    pdf(_pdf),
    cdf(_cdf),
    norm(1.0)
{
}

double NumericDistribution::GetMin() const {
  if (interval == Espresso::NumericDistribution::Interval::BOUNDED or interval == Espresso::NumericDistribution::Interval::LOWER_BOUNDED)
    return min;
  else
    return 0.0;
}

double NumericDistribution::GetMax() const {
  if (interval == Espresso::NumericDistribution::Interval::BOUNDED or interval == Espresso::NumericDistribution::Interval::UPPER_BOUNDED)
    return max;
  else
    return 0.0;
}

double NumericDistribution::GetCentral() const {
  if (interval == Espresso::NumericDistribution::Interval::BOUNDED) {
    return (min+max)/2.0;
  } else if (interval == Espresso::NumericDistribution::Interval::LOWER_BOUNDED) {
    if (min < 0)
      return 0.0;
    else if (min > 0)
      return 2*min;
    else
      return 1.0;
  } else if (interval == Espresso::NumericDistribution::Interval::UPPER_BOUNDED) {
    if (max > 0)
      return 0.0;
    else if (max < 0)
      return 2*max;
    else
      return -1.0;
  } else if (interval == Espresso::NumericDistribution::Interval::UNBOUNDED) {
    return 0.0;
  } else {
    return 0.0;
  }
}

double NumericDistribution::GetPDF(double x) const {
  if (interval == Espresso::NumericDistribution::Interval::UNBOUNDED) {
    return pdf(x)/norm;
  } else if (interval == Espresso::NumericDistribution::Interval::LOWER_BOUNDED) {
    if (x <= min)
      return 0.0;
    else
      return pdf(x)/norm;
  } else if (interval == Espresso::NumericDistribution::Interval::UPPER_BOUNDED) {
    if (x >= max)
      return 0.0;
    else
      return pdf(x)/norm;
  } else if (interval == Espresso::NumericDistribution::Interval::BOUNDED) {
    if (x <= min or x >= max)
      return 0.0;
    else
      return pdf(x)/norm;
  } else {
    return 0.0;
  }
}


double NumericDistribution::GetCDF(double x) const {
  // Some of this overlaps with checks in CreateNumericPDF
  // But it is here a cross-check for a manually defined CDF
  if (interval == Espresso::NumericDistribution::Interval::UNBOUNDED) {
    return cdf(x)/norm;
  } else if (interval == Espresso::NumericDistribution::Interval::LOWER_BOUNDED) {
    if (x <= min)
      return 0.0;
    else
      return (cdf(x)-cdf(min))/norm;
  } else if (interval == Espresso::NumericDistribution::Interval::UPPER_BOUNDED) {
    if (x >= max)
      return 1.0;
    else
      return cdf(x)/norm;
  } else if (interval == Espresso::NumericDistribution::Interval::BOUNDED) {
    if (x <= min)
      return 0.0;
    else if (x >= max)
      return 1.0;
    else
      return (cdf(x)-cdf(min))/norm;
  } else {
    return 0.0;
  }
}

double NumericDistribution::GetQuantile(double u) const {

  /* Solve x = F^-1(u) where F(x) = int(-infty,x) f(x') dx'
     i.e. Solve F(x) - u = 0
     This can be done with Newton's method
     Here, the Function is F(x) - u; the Jacobian is F'(x) = f(x)
  */
  
  FDF funjac = [u,this] (double c, double* f, double* df) {
    if (f != nullptr) {
      double z = GetCDF(c);
      *f = z-u;
    }
    if (df != nullptr) {
      double p = GetPDF(c);
      *df = p;
    }
  };  
  RootFinder alg(funjac,SolutionMethod::Newton);
  double coeff = GetCentral();
  alg.SetInitialGuess(coeff);
  alg.Solve();
  coeff = alg.GetSolution();
  return coeff;
}

double NumericDistribution::Expectation(const Function& f) const {

  Function prod = [&] (double x) {
    return f(x)*pdf(x)/norm;
  };
  double result;
  if (interval == Espresso::NumericDistribution::Interval::UNBOUNDED) {
    result = Espresso::Integrate(prod);
  } else if (interval == Espresso::NumericDistribution::Interval::LOWER_BOUNDED) {
    result = Espresso::IntegrateAbove(prod,min);
  } else if (interval == Espresso::NumericDistribution::Interval::UPPER_BOUNDED) {
    result = Espresso::IntegrateBelow(prod,max);
  } else if (interval == Espresso::NumericDistribution::Interval::BOUNDED) {
    result = Espresso::Integrate(prod,min,max);
  } else {
    result = 0.0;
  }
  return result;  
} 

double NumericDistribution::GetRandom() const {

  /* Use the inverse transform method
     Generate u ~ [0,1]
     Find quantile x = F^-1(u) where F(x) = int(-infty,x) f(x') dx'
     This follows the correct probability distribution.
  */
  
  double u = RandomNumberGeneration::Get();
  return GetQuantile(u);
}

double NumericDistribution::GetFourierCosTransform(double omega) const {
  Function Cos = [omega] (double t) {
    return cos(omega*t);
  };
  return Expectation(Cos);
}

double NumericDistribution::GetFourierSinTransform(double omega) const {
  Function Sin = [omega] (double t) {
    return sin(omega*t);
  };
  return Expectation(Sin);
}
