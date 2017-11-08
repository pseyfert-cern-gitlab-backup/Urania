#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

#include <gsl/gsl_errno.h>

#include "MultiRootFinder.hh"

using namespace Espresso;

MultiRootFinder::MultiRootFinder(std::size_t _num, const MultiFDF& funjac, MultiSolutionMethod method)
  : num(_num)
{
  if (method == MultiSolutionMethod::Newton) {
    multi_type = gsl_multiroot_fdfsolver_newton;
  } else if (method == MultiSolutionMethod::HybridSJ) {
    multi_type = gsl_multiroot_fdfsolver_hybridsj;
  } else if (method == MultiSolutionMethod::HybridJ) {
    multi_type = gsl_multiroot_fdfsolver_hybridj;
  } else if (method == MultiSolutionMethod::GNewton) {
    multi_type = gsl_multiroot_fdfsolver_gnewton;
  } else {
    // This should never be reached!
    multi_type = gsl_multiroot_fdfsolver_newton;
  }

  multi_solver = gsl_multiroot_fdfsolver_alloc(multi_type,num);

  fdf.n = num;

  fdf.f = [] (const gsl_vector* x, void* p, gsl_vector* f) -> int {
    multi_params *ps = static_cast<multi_params*>(p);
    Vector grad = Vector::SoftWrap(f);
    ps->func(x->data,&grad,nullptr);
    return GSL_SUCCESS;
  };

  fdf.df = [] (const gsl_vector* x, void* p, gsl_matrix* J) -> int {
    multi_params *ps = static_cast<multi_params*>(p);
    Matrix hessian = Matrix::SoftWrap(J);
    ps->func(x->data,nullptr,&hessian);
    return GSL_SUCCESS;
  };

  fdf.fdf = [] (const gsl_vector* x, void* p, gsl_vector* f, gsl_matrix* J) -> int {
    multi_params *ps = static_cast<multi_params*>(p);
    Vector grad = Vector::SoftWrap(f);
    Matrix hessian = Matrix::SoftWrap(J);
    ps->func(x->data,&grad,&hessian);
    return GSL_SUCCESS;
  };

  multi_params* my_multi_params = new multi_params({num,funjac});
  fdf.params = static_cast<void*>(my_multi_params);

  multi_values = gsl_vector_alloc(num);
  for (unsigned int k = 0; k < num; k++) {
    gsl_vector_set (multi_values,k,0.0);
  }

}

MultiRootFinder::~MultiRootFinder() {
  if (multi_solver != NULL)
    gsl_multiroot_fdfsolver_free(multi_solver);
  if (multi_values != NULL)
    gsl_vector_free(multi_values);
}

std::string MultiRootFinder::AlgorithmName() {
  const char* cname = gsl_multiroot_fdfsolver_name(multi_solver);
  std::string name(cname, strnlen(cname,100));
  return name;
}

void MultiRootFinder::SetInitialGuess(const Vector& c) {
  std::size_t size = c.size();
  for (unsigned int k = 0; k < size; k++) {
    gsl_vector_set (multi_values,k,c(k));
  }
}

int MultiRootFinder::Solve() {

  int status;
  size_t iter = 0;

  gsl_multiroot_fdfsolver_set(multi_solver,&fdf,multi_values);

  do {
    iter++;
    status = gsl_multiroot_fdfsolver_iterate(multi_solver);
    if (status) // check if solver is stuck
      break;
    status = gsl_multiroot_test_residual(multi_solver->f, 1e-7);
  } while (status == GSL_CONTINUE && iter < 1000);

  return status;

}

Vector MultiRootFinder::GetSolution() {
  Vector v(num);
  for (unsigned int k = 0; k < num; k++) {
    v(k) = gsl_vector_get(multi_solver->x,k);
  }
  return v;
}
