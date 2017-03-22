#include "Statistics.hh"

#include <cassert>
#include <cmath>
#include <iostream>

#include <TEfficiency.h>

#include "Matrix.hh"
#include "RandomNumberGeneration.hh"
#include "Distribution.hh"

using namespace Espresso;

double Espresso::erfinv(double x) {
  // Stolen from TMath, GPL makes that ok?
  // returns  the inverse error function
  // x must be  -1<x<1
  
  int kMaxit    = 50;
  double kEps   = 1e-14;
  double kConst = 0.8862269254527579;     // sqrt(pi)/2.0
  
  // TAIL 
  if (std::abs(x) <= kEps)
    return kConst*x;
  
  // Newton iterations
  double erfi, derfi, y0,y1,dy0,dy1;
  if (std::abs(x) < 1.0) {
    erfi  = kConst*std::abs(x);
    y0    = erf(0.9*erfi);
    derfi = 0.1*erfi;
    for (int iter = 0; iter < kMaxit; iter++) {
      y1  = 1.0 - erfc(erfi);
      dy1 = std::abs(x) - y1;
      if (std::abs(dy1) < kEps) {
        if (x < 0)
          return -erfi;
        else
          return erfi;
      }
      dy0    = y1 - y0;
      derfi *= dy1/dy0;
      y0     = y1;
      erfi  += derfi;
      if (std::abs(derfi/erfi) < kEps) {
        if (x < 0)
          return -erfi;
        else
          return erfi;
      }
    }
  }
  return 0; //did not converge
}

Matrix Espresso::GramSchmidt(const Matrix& covariances) {
  
  // Initialize output matrix
  assert(covariances.size1() == covariances.size2());
  std::size_t k = covariances.size1();
  Matrix gs(k,k);
  gs.SetIdentity();
  
  /* Gram-Schmidt algorithm
     for i from 1 to k do
         vi <- vi/||vi||
         for j from i+1 to k to
             vj <- vj - proj[vi](vj)
         next j
     next i
  */

  // outer loop
  for (std::size_t i = 0; i < k; i++) {

    // normalization
    double w = 0.0;
    for (std::size_t l = 0; l < k; l++) {
      for (std::size_t m = 0; m < k; m++) {
	w += gs(i,l)*gs(i,m)*covariances(l,m);
      }
    }
    double z = sqrt(w);
    for (std::size_t l = 0; l < k; l++)
      gs(i,l) /= z;
    
    // inner loop
    for (std::size_t j = i+1; j < k; j++) {

      // remove projection
      double w = 0.0;
      for (std::size_t l = 0; l < k; l++) {
	for (std::size_t m = 0; m < k; m++) {
	  w += gs(i,l)*gs(j,m)*covariances(l,m);
	}
      }
      for (std::size_t l = 0; l < k; l++) {
        gs(j,l) = gs(j,l) - w*gs(i,l);
      }
    }
  }

  return gs;
}

Espresso::ConfidenceInterval Espresso::EfficiencyConfidenceInterval(double numPass, double numFail, double conf) {
  const double alpha = 1.0;
  const double beta = 1.0;
  const double aa =  numPass + alpha;
  const double bb =  numFail + beta;
  if (aa <= 0 and bb > 0) {
    return std::make_tuple(0.0,0.0,0.0);
  } else if (aa > 0 and bb <= 0) {
    return std::make_tuple(1.0,1.0,1.0);
  } else if (aa <= 0 and bb <= 0) {
    return std::make_tuple(0.5,0.5,0.5);
  } else {
    double eff = TEfficiency::BetaMode(aa,bb);
    double lower = TEfficiency::BetaCentralInterval(conf,aa,bb,false);
    double upper = TEfficiency::BetaCentralInterval(conf,aa,bb,true);
    return std::make_tuple(eff,lower,upper);
  }
}

