#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

#include <gsl/gsl_errno.h>

#include "RootFinder.hh"

using namespace Espresso;

RootFinder::RootFinder(const FDF& funjac, SolutionMethod method)
{
  if (method == SolutionMethod::Newton) {
    type = gsl_root_fdfsolver_newton;
  } else if (method == SolutionMethod::Secant) {
    type = gsl_root_fdfsolver_secant;
  } else if (method == SolutionMethod::Steffenson) {
    type = gsl_root_fdfsolver_steffenson;
  } else {
    // This should never be reached
    type = gsl_root_fdfsolver_newton;
  }

  solver = gsl_root_fdfsolver_alloc(type);

  fdf.f = [] (double x, void* p) -> double {
    FDF* func = static_cast<FDF*>(p);
    double val = 0.0;
    (*func)(x,&val,nullptr);
    return val;
  };
  
  fdf.df = [] (double x, void* p) -> double {	
    FDF* func = static_cast<FDF*>(p);
    double val = 0.0;
    (*func)(x,nullptr,&val);
    return val;
  };
  
  fdf.fdf = [] (double x, void* p, double* f, double* df) {
    FDF* func = static_cast<FDF*>(p);
    (*func)(x,f,df);
  };
  
  fdf.params = const_cast<void*>(static_cast<const void*>(&funjac));

  value = 0.0;
}

RootFinder::~RootFinder() {
  if (solver != NULL)
    gsl_root_fdfsolver_free(solver);
}

std::string RootFinder::AlgorithmName() {
  const char* cname = gsl_root_fdfsolver_name(solver);
  std::string name(cname, strnlen(cname,100));
  return name;
}

void RootFinder::SetInitialGuess(double guess) {
  value = guess;
}

int RootFinder::Solve() {

  int status;
  size_t iter = 0;
    
  gsl_root_fdfsolver_set(solver,&fdf,value);
  
  double value0;
  do {
    iter++;
    status = gsl_root_fdfsolver_iterate(solver);
    value0 = value;
    value = gsl_root_fdfsolver_root(solver);
    if (status) // check if solver is stuck
      break;
    status = gsl_root_test_delta(value, value0, 0, 1e-7);
  } while (status == GSL_CONTINUE && iter < 1000);
  
  return status;
}

double RootFinder::GetSolution() {
  return value;
}
