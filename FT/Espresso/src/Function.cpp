#include "Function.hh"

#include <gsl/gsl_integration.h>

using namespace Espresso;

double Espresso::Integrate(Function f) {
  gsl_function F;
  F.function = [] (double x, void* p) {
    return (*static_cast<Function*>(p))(x);
  };
  F.params = &f;
  gsl_integration_workspace* w = gsl_integration_workspace_alloc (10000);
  double result, error;
  gsl_integration_qagi (&F,0,1e-7,10000,w,&result,&error);
  return result;
}

double Espresso::IntegrateBelow(Function f, double max) {
  gsl_function F;
  F.function = [] (double x, void* p) {
    return (*static_cast<Function*>(p))(x);
  };
  F.params = &f;
  gsl_integration_workspace* w = gsl_integration_workspace_alloc (10000);
  double result, error;
  gsl_integration_qagil (&F,max,0,1e-7,10000,w,&result,&error);
  return result;
}

double Espresso::IntegrateAbove(Function f, double min) {
  gsl_function F;
  F.function = [] (double x, void* p) {
    return (*static_cast<Function*>(p))(x);
  };
  F.params = &f;
  gsl_integration_workspace* w = gsl_integration_workspace_alloc (10000);
  double result, error;
  gsl_integration_qagiu (&F,min,0,1e-7,10000,w,&result,&error);
  return result;
}

double Espresso::Integrate(Function f, double min, double max) {
  gsl_function F;
  F.function = [] (double x, void* p) {
    return (*static_cast<Function*>(p))(x);
  };
  F.params = &f;
  gsl_integration_workspace* w = gsl_integration_workspace_alloc (10000);
  double result, error;
  gsl_integration_qag (&F,min,max,0,1e-7,6,10000,w,&result,&error);
  return result;  
}
