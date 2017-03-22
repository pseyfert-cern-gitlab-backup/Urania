#include <iostream>
#include <algorithm>

#include "SumDistribution.hh"
#include "RootFinder.hh"
#include "Function.hh"
#include "RandomNumberGeneration.hh"

using Espresso::SumDistribution;

SumDistribution::SumDistribution(std::unique_ptr<Distribution>&& _pdf1, std::unique_ptr<Distribution>&& _pdf2, double _f1, double _f2)
  : pdf1(std::move(_pdf1)),
    pdf2(std::move(_pdf2)),
    f1(std::move(_f1)),
    f2(std::move(_f2))
{
  double sum = f1 + f2;
  if (sum != 1.0) {
    f1 /= sum;
    f2 /= sum;
  }
}

SumDistribution::SumDistribution(const SumDistribution& rhs)
  : pdf1(rhs.pdf1->clone()),
    pdf2(rhs.pdf2->clone()),
    f1(rhs.f1),
    f2(rhs.f2)
{
  std::cout << "copying distribution as SumDistribution" << std::endl;
}

SumDistribution::SumDistribution(SumDistribution&& rhs)
  : pdf1(std::move(rhs.pdf1)),
    pdf2(std::move(rhs.pdf2)),
    f1(std::move(rhs.f1)),
    f2(std::move(rhs.f2))
{
  std::cout << "moving distribution as SumDistribution" << std::endl;
}


double SumDistribution::GetMin() const {
  double m1 = pdf1->GetMin();
  double m2 = pdf2->GetMin();
  return std::min(m1,m2);
}

double SumDistribution::GetMax() const {
  double m1 = pdf1->GetMax();
  double m2 = pdf2->GetMax();
  return std::max(m1,m2);
}

double SumDistribution::GetPDF(double x) const {
  double val1 = pdf1->GetPDF(x);
  double val2 = pdf2->GetPDF(x);
  return f1*val1 + f2*val2;
}


double SumDistribution::GetCDF(double x) const {
  double val1 = pdf1->GetCDF(x);
  double val2 = pdf2->GetCDF(x);
  return f1*val1 + f2*val2;
}

double SumDistribution::GetQuantile(double u) const {
  /* Solve x = F^-1(u) where F(x) = int(-infty,x) f(x') dx'
     i.e. Solve F(x) - u = 0
     This can be done with Newton's method
     Here, the Function is F(x) - u; the Jacobian is F'(x) = f(x)
  */

  FDF funjac = [u,this] (double c, double* f, double* df) {
    if (f != nullptr) {
      double val1 = pdf1->GetCDF(c);
      double val2 = pdf2->GetCDF(c);
      double z = f1*val1 + f2*val2;
      *f = z-u;
    }
    if (df != nullptr) {
      double p1 = pdf1->GetPDF(c);
      double p2 = pdf2->GetPDF(c);
      double p = f1*p1 + f2*p2;
      *df = p;
    }
  };
  RootFinder alg(funjac,SolutionMethod::Newton);
  double m1 = pdf1->GetQuantile(0.5);
  double m2 = pdf2->GetQuantile(0.5);
  double coeff = f1*m1+f2*m2;
  alg.SetInitialGuess(coeff);
  alg.Solve();
  coeff = alg.GetSolution();
  return coeff;
}

double SumDistribution::Expectation(const Function& f) const {
  double val1 = pdf1->Expectation(f);
  double val2 = pdf2->Expectation(f);
  return f1*val1 + f2*val2;
}

double SumDistribution::GetRandom() const {
  double u = RandomNumberGeneration::Get();
  if (u <= f1) {
    return pdf1->GetRandom();
  } else {
    return pdf2->GetRandom();
  }
}

double SumDistribution::GetFourierCosTransform(double omega) const {
  double val1 = pdf1->GetFourierCosTransform(omega);
  double val2 = pdf2->GetFourierCosTransform(omega);
  return f1*val1 + f2*val2;
}

double SumDistribution::GetFourierSinTransform(double omega) const {
  double val1 = pdf1->GetFourierSinTransform(omega);
  double val2 = pdf2->GetFourierSinTransform(omega);
  return f1*val1 + f2*val2;
}
