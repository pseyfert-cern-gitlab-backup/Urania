// Include files 
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

// local
#include "GLMNSpline.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : GLMNSpline
//
// 2015-09-17 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

Vector GLMNSpline::GetBasis(double eta) const {
  
  Vector vals(size);
  vals[0] = 1;
  vals[1] = eta;
  std::vector<double> cub(size,0.0);
  for (std::size_t k = 0; k < size; k++)
    cub[k] = (eta >= nodes[k]) ? pow(eta-nodes[k],3) : 0.0;
  std::vector<double> dk(size,0.0);
  for (std::size_t k = 0; k < size-1; k++)
    dk[k] = (cub[k] - cub[size-1])/(nodes[size-1] - nodes[k]);
  for (std::size_t k = 0; k < size-2; k++)
    vals[k+2] = dk[k]-dk[size-2];
  vals = basis*vals;
  return vals;
}

std::string GLMNSpline::NSplineBasisString(bool latex) const {
  // LOOP OVER ALL NEEDED N-SPLINES
  int num = basis.size1();
  std::stringstream ss;
  if (latex) ss << "\\begin{align*}\n";
  for (int n = 0; n < num; n++) {
    ss << "P_" << n << "(x)";
    if (latex) ss << " &= ";
    else ss << " = ";

    int precision = (latex) ? 3 : 4;
    for (int k = n; k >= 0; k--) {
      double val = basis(n,k);
      if (n > 0) ss << std::showpos;
      if (k == 0 or val != 1) ss << std::setprecision(precision) << val;
      if (n > 0) ss << std::noshowpos;
      if (k == 1) ss << "x ";
      if (k >= 2) ss << "n" << k << "(x) ";
    }
    if (latex) ss << "\\\\\n";
    else ss << std::endl;
  }

  if (latex) ss << "\\end{align*}";
  std::string s = ss.str();
  return s;
}

void GLMNSpline::print(std::ostream& os) const {
  os << " -- N-SPLINE BASIS -- " << std::endl;
  os << " NODES LOCATIONS:";
  for (unsigned int k = 0; k < size; k++) {
    if (k != 0) os << ", ";
    os << std::setprecision(3) << nodes[k];
  }
  os << std::endl << std::endl;
  os << " BASIS ROTATION: " << std::endl;
  os << NSplineBasisString();
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::GLMNSpline)
