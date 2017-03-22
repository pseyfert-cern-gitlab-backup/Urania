// Include files
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

// local
#include "GLMPolynomial.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : GLMPolynomial
//
// 2015-09-17 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

Vector GLMPolynomial::GetBasis(double X) const {
  Vector vec(degree+1);
  for (unsigned int k = 0; k <= degree; k++) {
    double z = 0.0;
    for (unsigned int l = 0; l <= degree; l++)
      z += basis(k,l)*pow(X,l);
    vec[k] = z;
  }
  return vec;
}

std::string GLMPolynomial::PolyBasisString(bool latex) const {
  // LOOP OVER ALL NEEDED POLYNOMIALS
  int num = basis.size1();
  std::stringstream ss;
  if (latex) ss << "\\begin{align*}\n";
  for (int n = 0; n < num; n++) {
    ss << "P_" << n << "(x)";
    if (latex) ss << " &= ";
    else ss << " = ";

    int precision = (latex) ? 3 : 4;
    //const int nn = basis.size2()-1;
    for (int k = n; k >= 0; k--) {
      double val = basis(n,k);
      if (n > 0) ss << std::showpos;
      if (k == 0 or val != 1) ss << std::setprecision(precision) << val;
      if (n > 0) ss << std::noshowpos;
      if (k == 1) ss << "x ";
      if (k >= 2) ss << "x^" << k << " ";
    }
    if (latex) ss << "\\\\\n";
    else ss << std::endl;
  }

  if (latex) ss << "\\end{align*}";
  std::string s = ss.str();
  return s;
}

void GLMPolynomial::print(std::ostream& os) const {
  os << " -- POLYNOMIAL BASIS -- " << std::endl;
  os << PolyBasisString();
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::GLMPolynomial)
