// Include files
#include <iostream>
#include <cmath>

// root
#include "TMath.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"

#include "LikelihoodMaximizer.hh"

using namespace Espresso;

// LikelihoodMaximizer::LikelihoodMaximizer(const TaggingResult& _tag, unsigned int _degree, PolyBasis _basis)
//   : degree(_degree),
//     basis(_basis),
//     tag(_tag),
//     likelihoodFunction(_tag,_degree,_basis),
//     average(degree+1),
//     covariance(degree+1,degree+1),
//     verbose(false)
// {
// }

LikelihoodMaximizer::LikelihoodMaximizer(const TaggingLikelihood& _lf)
  : likelihoodFunction(_lf),
    average(likelihoodFunction.NDim()),
    covariance(likelihoodFunction.NDim(),likelihoodFunction.NDim()),
    verbose(false)
{
}

void LikelihoodMaximizer::SetVals(const double* vals) {
  // std::copy(vals, vals + (degree+1), coeffs.begin());
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    average(k) = vals[k];
  }
}

void LikelihoodMaximizer::SetVals(const std::vector<double>& vals) {
  // std::copy(vals.begin(), vals.end(), coeffs.begin());
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    average(k) = vals[k];
  }
}

void LikelihoodMaximizer::GetVals(double* vals) {
  // std::copy(coeffs.begin(), coeffs.end(), vals);
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    vals[k] = average(k);
  }
}

void LikelihoodMaximizer::GetVals(std::vector<double>& vals) {
  vals.resize(likelihoodFunction.NDim());
  // std::copy(coeffs.begin(), coeffs.end(), vals.begin());
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    vals[k] = average(k);
  }
}

void LikelihoodMaximizer::SetVals(const Vector& _vals) {
  average = _vals;
}


Vector LikelihoodMaximizer::GetVals()
{
  return average;
}

Matrix LikelihoodMaximizer::GetCovariance()
{
  return covariance;
}

double LikelihoodMaximizer::Solve()
{
  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit","Migrad");
  min->SetMaxFunctionCalls(1000000);
  min->SetTolerance(1e-5);
  min->SetPrintLevel(-1);

  min->SetFunction(likelihoodFunction);
  int N = likelihoodFunction.NDim();
  for (int i = 0; i < N; i++)
  {
    char name[5];
    if (i < N/2)
      sprintf(name,"p%d",i);
    else
      sprintf(name,"dp%d",i-N/2);
    min->SetVariable(i,name,average(i),0.0005);
  }
  bool success = min->Minimize();

  if (success)
  {
    const double *xs = min->X();
    for (unsigned int i = 0; i < likelihoodFunction.NDim(); i++)
      average(i) = xs[i];
    covariance = likelihoodFunction.GetCovarianceMatrix(average.GetArray());
    double gof = likelihoodFunction.GetDeviance(xs);
    return gof;

  } else {
    std::cerr << "ERROR: MINIMIZATION DID NOT CONVERGE" << std::endl;
    return 0.0;
  }

  return 0.0;

}
