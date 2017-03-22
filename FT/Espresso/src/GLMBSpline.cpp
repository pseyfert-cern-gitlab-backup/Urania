// Include files 
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

// local
#include "GLMBSpline.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : GLMBSpline
//
// 2015-09-17 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

Vector GLMBSpline::GetBasis(double eta) const {
  
  eta = std::max(eta,nodes[0]);
  eta = std::min(eta,nodes[size-1]);

  std::fill(b1.begin(),b1.end(),0.0);
  std::fill(b2.begin(),b2.end(),0.0);
  std::fill(b3.begin(),b3.end(),0.0);
  std::fill(b4.begin(),b4.end(),0.0);

  // Initial condition
  for (std::size_t i = 0; i < size+5; i++) {
    if (tau[i] <= eta and eta < tau[i+1]) {
      b1[i] = 1.0;
      break;
    }
  }

  // First iteration
  for (std::size_t i = 0; i < size+4; i++) {
    if (b1[i])
      b2[i] += (eta-tau[i])/(tau[i+1]-tau[i]) * b1[i];
    if (b1[i+1])
      b2[i] += (tau[i+2]-eta)/(tau[i+2]-tau[i+1]) * b1[i+1];
  }

  for (std::size_t i = 0; i < size+3; i++) {
    if (b2[i])
      b3[i] += (eta-tau[i])/(tau[i+2]-tau[i]) * b2[i];
    if (b2[i+1])
      b3[i] += (tau[i+3]-eta)/(tau[i+3]-tau[i+1]) * b2[i+1];
  }

  for (std::size_t i = 0; i < size+2; i++) {
    if (b3[i])
      b4[i] += (eta-tau[i])/(tau[i+3]-tau[i]) * b3[i];
    if (b3[i+1])
      b4[i] += (tau[i+4]-eta)/(tau[i+4]-tau[i+1]) * b3[i+1];
  }

  return Vector(b4);
}

void GLMBSpline::print(std::ostream& os) const {
  os << " -- B-SPLINE BASIS -- " << std::endl;
  os << " NODES LOCATIONS:";
  for (unsigned int k = 0; k < size; k++) {
    if (k != 0) os << ", ";
    os << std::setprecision(3) << nodes[k];
  }
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::GLMBSpline)
