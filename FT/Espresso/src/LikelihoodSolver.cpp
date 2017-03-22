// Include files
#include <iostream>
#include <cmath>

#include "LikelihoodSolver.hh"

using namespace Espresso;

LikelihoodSolver::LikelihoodSolver(const TaggingLikelihood& _lf, MultiSolutionMethod _method)
  : likelihoodFunction(_lf),
    method(_method),
    average(likelihoodFunction.NDim()),
    covariance(likelihoodFunction.NDim(),likelihoodFunction.NDim()),
    verbose(false)
{
}

void LikelihoodSolver::SetVals(const double* vals) {
  // std::copy(vals, vals + (degree+1), coeffs.begin());
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    average(k) = vals[k];
  }
}

void LikelihoodSolver::SetVals(const std::vector<double>& vals) {
  // std::copy(vals.begin(), vals.end(), coeffs.begin());
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    average(k) = vals[k];
  }
}

void LikelihoodSolver::GetVals(double* vals) {
  // std::copy(coeffs.begin(), coeffs.end(), vals);
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    vals[k] = average(k);
  }
}

void LikelihoodSolver::GetVals(std::vector<double>& vals) {
  vals.resize(likelihoodFunction.NDim());
  // std::copy(coeffs.begin(), coeffs.end(), vals.begin());
  for (unsigned int k = 0; k < likelihoodFunction.NDim(); k++)
  {
    vals[k] = average(k);
  }
}

void LikelihoodSolver::SetVals(const Vector& _vals) {
  average = _vals;
}


Vector LikelihoodSolver::GetVals()
{
  return average;
}

Matrix LikelihoodSolver::GetCovariance()
{
  return covariance;
}

double LikelihoodSolver::Solve()
{

  MultiFDF funjac = [this] (const double* theta, Vector* grad, Matrix* hessian) {
    return likelihoodFunction.GetLogLikelihoodData(theta,nullptr,grad,hessian);
  };

  MultiRootFinder rf(likelihoodFunction.NDim(),funjac,method);
  rf.Solve();
  average = rf.GetSolution();
  covariance = likelihoodFunction.GetCovarianceMatrix(average.GetArray());

  const double *xs = average.GetArray();
  double gof = likelihoodFunction.GetDeviance(xs);
  return gof;

}
