// Include files
#include "Vector.hh"

// local
#include "Matrix.hh"

#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cassert>

#include <gsl/gsl_blas.h>
#include "gsl/gsl_linalg.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Matrix
//
// 2015-05-09 : Jack Wimberley
//-----------------------------------------------------------------------------

namespace Espresso
{

  // Constructor
  Matrix::Matrix(std::size_t _n, std::size_t _m)
    : n(_n),
      m(_m),
      v(gsl_matrix_calloc(n,m)),
      _isSubmatrix(false),
      softwrap(false)
  {
    Reset();
  }

  // Copy constructor
  Matrix::Matrix(const Matrix& rhs)
    : n(rhs.n),
      m(rhs.m),
      v(gsl_matrix_calloc(rhs.v->size1,rhs.v->size2)),
      _isSubmatrix(false),
      softwrap(false)
  {
    gsl_matrix_memcpy(v,rhs.v);
  }

  // Private constructor
  Matrix::Matrix(gsl_matrix* _v, bool sw)
    : n(_v->size1),
      m(_v->size2),
      v(_v),
      _isSubmatrix(false),
      softwrap(sw)
  {
  }

  // Making a soft-wrap matrix
  Matrix Matrix::SoftWrap(gsl_matrix* _v) {
    return Matrix(_v,true);
  }

  // Swap operator
  void swap(Matrix& first, Matrix& second) {
    std::size_t ntemp = first.n;
    first.n = second.n;
    second.n = ntemp;
    std::size_t mtemp = first.m;
    first.m = second.m;
    second.m = mtemp;
    gsl_matrix* temp = first.v;
    first.v = second.v;
    second.v = temp;
    bool btemp = first._isSubmatrix;
    first._isSubmatrix = second._isSubmatrix;
    second._isSubmatrix = btemp;
    btemp = first.softwrap;
    first.softwrap = second.softwrap;
    second.softwrap = btemp;
  }

  // Destructor
  Matrix::~Matrix() {
    if (not (_isSubmatrix or softwrap)) {
      gsl_matrix_free(v);
    }
  }

  // Assignment operator
  Matrix& Matrix::operator= (Matrix rhs) {
    swap(*this,rhs);
    return *this;
  }

  // Printing operator
  std::ostream& operator<< (std::ostream& os, const Matrix& m) {
    for (unsigned int row = 0; row < m.size1(); row++) {
      for (unsigned int col = 0; col < m.size2(); col++) {
        os << std::setprecision(8)
           << std::setw(14)
           << m(row,col)
           << " | ";
      }
      os << std::endl;
    }
    return os;
  }

  // Size
  std::size_t Matrix::size1() const {
    return n;
  }

  std::size_t Matrix::size2() const {
    return m;
  }

  //=============================================================================
  // Arithmetic operators
  //=============================================================================
  Matrix& Matrix::operator+= (const Matrix& rhs) {
    const gsl_matrix* u = rhs.v;
    gsl_matrix_add(v, u);
    return *this;
  }
  Matrix operator+ (Matrix lhs, const Matrix& rhs) {
    return lhs += rhs;
  }

  Matrix& Matrix::operator-= (const Matrix& rhs) {
    const gsl_matrix* u = rhs.v;
    gsl_matrix_sub(v,u);
    return *this;
  }
  Matrix operator- (Matrix lhs, const Matrix& rhs) {
    return lhs -= rhs;
  }

  Matrix& Matrix::operator*= (const Matrix& rhs) {
    gsl_matrix* mnew = gsl_matrix_calloc(v->size1,v->size2);
    gsl_blas_dgemm(CblasNoTrans,CblasNoTrans, 1.0, v, rhs.v, 0.0, mnew);
    gsl_matrix_free(v);
    this->v = mnew;
    return *this;
  }
  Matrix operator* (Matrix lhs, const Matrix& rhs) {
    return lhs *= rhs;
  }

  Matrix& Matrix::operator*= (const double& rhs) {
    gsl_matrix_scale(v,rhs);
    return *this;
  }
  Matrix operator* (Matrix lhs, const double& rhs) {
    return lhs *= rhs;
  }
  Matrix operator* (const double& lhs, Matrix rhs) {
    return rhs *= lhs;
  }

  Matrix& Matrix::operator/= (const double& rhs) {
    gsl_matrix_scale(v,1.0/rhs);
    return *this;
  }
  Matrix operator/ (Matrix lhs, const double& rhs) {
    return lhs /= rhs;
  }

  void Matrix::Transpose() {
    assert(size1() == size2());
    gsl_matrix_transpose(v);
  }

  Matrix Matrix::Submatrix(int k1, int k2, int n1, int n2) {
    gsl_matrix_view view = gsl_matrix_submatrix(this->v, k1, k2, n1, n2);
    gsl_matrix* newv = &view.matrix;
    Matrix sub(newv);
    sub._isSubmatrix = true;
    return sub;
  }

  // Access

  double Matrix::Get(std::size_t i, std::size_t j) {
    return gsl_matrix_get(v,i,j);
  }

  void Matrix::Set(std::size_t i, std::size_t j, double z) {
    gsl_matrix_set(v,i,j,z);
  }

  double Matrix::operator() (std::size_t i, std::size_t j) const {
    return *gsl_matrix_const_ptr(v,i,j);
  }

  double& Matrix::operator() (std::size_t i, std::size_t j) {
    return *gsl_matrix_ptr(v,i,j);
  }

  // Determinant

  double Matrix::Determinant() {
    std::size_t s = size1();
    assert (size2() == s);
    gsl_matrix* lu = gsl_matrix_calloc(s,s);
    gsl_matrix_memcpy(lu,v);
    gsl_permutation* p = gsl_permutation_alloc(s);
    gsl_permutation_init(p);
    int signum;
    gsl_linalg_LU_decomp(lu,p,&signum);
    double det = gsl_linalg_LU_det(lu,signum);
    gsl_matrix_free(lu);
    gsl_permutation_free(p);
    return det;
  }

  void Matrix::Invert(bool verbose) {
    std::size_t s = size1();
    gsl_permutation* p = gsl_permutation_alloc(s);
    gsl_permutation_init(p);
    int signum;
    gsl_linalg_LU_decomp(v,p,&signum);
    gsl_matrix* inverse = gsl_matrix_calloc(s,s);
    gsl_linalg_LU_invert(v,p,inverse);
    gsl_matrix_memcpy(v,inverse);
  }

  void Matrix::Cholesky(bool verbose) {

    if (verbose) {
      std::cout << std::endl;
      std::cout << "-----------------------------------------" << std::endl;
      std::cout << "COVARIANCE MATRIX CHOLESKY DECOMPOSITION:" << std::endl;
      std::cout << "-----------------------------------------" << std::endl;
    }

    if (verbose) {
      std::cout << "BEFORE DECOMPOSITION:" << std::endl;
      std::cout << *this << std::endl;
    }

    // SET LENGTHS
    std::size_t length = size1();
    assert(size2() == length);

    // IS THIS POSITIVE DEFINITE?
    bool posdef = gsl_matrix_ispos(v);

    // HACK: ALWAYS USE GMW81
    posdef = false;

    // GSL ALGORITHM
    if (posdef) {
      if (verbose)
        std::cout << "MATRIX IS POSITIVE DEFINITE; USING GSL CHOLESKY DECOMPOSITION" << std::endl;
      gsl_linalg_cholesky_decomp(v);
      for (unsigned int row = 0; row < length; row++)
        for (unsigned int col = row+1; col < length; col++)
          (*this)(row,col) = 0.0;
      return;
    }

    // OTHERWISE, GMW81 ALGORITHM
    assert(not posdef);
    if (verbose)
      std::cout << "MATRIX IS NOT POSITIVE DEFINITE; USING GMW81 ALGORITHM" << std::endl;

    // CHOLESKY-BANACHIEWICZ ALGORITHM
    /* This requires all the elements to the above and left
       to have been calculated already
       So, loop through starting from the top left
    */

    // LDL FACTORIZATION
    Matrix unitlower(length,length);
    unitlower.SetIdentity();
    Matrix diagonal(length,length);
    diagonal.SetIdentity();

    auto diagonal_entry = [this,&diagonal,&unitlower] (unsigned int j) -> double {
      double z = 0.0;
      // std::cout << "D(" << j << ") = " << z;
      for (unsigned int k = 0; k < j; k++) {
        double a = diagonal(k,k);
        double b = unitlower(j,k);
        z -= a*b*b;
        // std::cout << std::endl << "a = " << a << std::endl;
        // std::cout << "b = " << b << std::endl;
        // std::cout << " -> " << z;
      }
      z += (*this)(j,j);
      // std::cout << " -> " << z << std::endl;
      return z;
    };
    auto unitlower_entry = [this,&diagonal,&unitlower] (unsigned int i, unsigned int j) -> double {
      double z = 0.0;
      // std::cout << "L(" << i << "," << j << ") = " << z;
      for (unsigned int k = 0; k < j; k++) {
        assert(i>k);
        assert(j>k);
        double a = diagonal(k,k);
        double b = unitlower(i,k);
        double c = unitlower(j,k);
        // std::cout << std::endl << "a = " << a << std::endl;
        // std::cout << "b = " << b << std::endl;
        // std::cout << "c = " << c << std::endl;
        z -= a*b*c;
        // std::cout << " -> " << z;
      }
      z += (*this)(i,j);
      // std::cout << " -> " << z;
      z /= diagonal(j,j);
      // std::cout << " -> " << z << std::endl;
      return z;
    };
    for (unsigned int row = 0; row < length; row++) {
      for (unsigned int col = 0; col < length; col++) {
        if (row == col)
          diagonal(row,col) = diagonal_entry(col);
        if (row > col)
          unitlower(row,col) = unitlower_entry(row,col);
        // std::cout << diagonal << std::endl;
        // std::cout << unitlower << std::endl;
        // std::cin.get();
        if (col > row)
          break;
      }
    }

    // IS THIS LDL?
    if (verbose) {
      Matrix ult(unitlower);
      ult.Transpose();
      Matrix test = diagonal * ult;
      test = unitlower * test;
      bool ldl = true;
      for (unsigned int row = 0; row < length; row ++) {
        for (unsigned int col = 0; col < length; col++) {
          ldl = ldl and (std::fabs((*this)(row,col) - test(row,col)) < std::numeric_limits<double>::epsilon());
        }
      }
      if (ldl)
        std::cout << "LDL FACTORIZATION SUCCESSFUL" << std::endl;
      else
        std::cout << "ERROR: LDL FACTORIZATION UNSUCCESSFUL" << std::endl;
    }

    // If this is positive definite, return
    posdef = true;
    for (unsigned int row = 0; row < length; row++) {
      if (diagonal(row,row) <= 0.0)
        posdef = false;
    }

    if (not posdef) {

      if (verbose)
        std::cout << "DOING CORRECTION" << std::endl;

      // Max. off-diag entry in this
      double chi = 0.0;
      for (unsigned int row = 0; row < length; row++) {
        for (unsigned int col = 0; col < row; col++) {
          chi = std::max(chi,(*this)(row,col));
        }
      }

      // Max. diag entry in this
      double eta = 0.0;
      for (unsigned int row = 0; row < length; row++) {
        eta = std::max(eta,(*this)(row,row));
      }

      // Beta parameter
      double beta2 = std::max(eta,chi/sqrt(length*length-1));
      beta2 = std::max(beta2,std::numeric_limits<double>::epsilon());

      // Iteration matix
      // At each step, only the first length-k+1 elements should be used
      Matrix Ak(length,length);

      for (unsigned int row = 0; row < length; row++) {
        for (unsigned int col = 0; col < length; col++) {
          Ak(row,col) = (*this)(row,col);
        }
      }

      double ak;
      Matrix abark(length,length);
      Vector ck(length);
      double ckmax;
      double aknew;

      // NOW LOOP
      for (unsigned int k = 0; k < length; k++) {

        // Set abar and c
        ak = Ak(0,0);
        for (unsigned int row = 0; row < length-k-1; row++) {
          ck(row) = Ak(row+1,0);
          for (unsigned int col = 0; col < length-k-1; col++) {
            abark(row,col) = Ak(row+1,col+1);
          }
        }

        // Set delta
        ckmax = 0.0;
        for (unsigned int row = 0; row < length-k-1; row++) {
          ckmax = std::max(ckmax,ck(row));
        }
        aknew = std::max(std::numeric_limits<double>::epsilon(), 1.0*std::fabs(ak));
        aknew = std::max(aknew,ckmax*ckmax/(beta2));

        // Adjust L
        for (unsigned int row = 0; row < length-k-1; row++) {
          unitlower(k+1+row,k) = ck(row)/(aknew);
        }

        // Adjust D
        diagonal(k,k) = aknew;

        // Adjust Ak
        for (unsigned int row = 0; row < length-k-1; row++) {
          for (unsigned int col = 0; col < length-k-1; col++) {
            Ak(row,col) = abark(row,col) - ck(row)*ck(col)/aknew;
          }
        }
      }
    }

    Matrix sqrtDiagonal(length,length);
    for (unsigned int row = 0; row < length; row++) {
      sqrtDiagonal(row,row) = sqrt(diagonal(row,row));
      for (unsigned int col = 0; col < row; col++) {
        sqrtDiagonal(row,col) = 0.0;
        sqrtDiagonal(col,row) = 0.0;
      }
    }

    unitlower *= sqrtDiagonal;
    if (not _isSubmatrix) {
      *this = unitlower;
    } else {
      for (unsigned int row = 0; row < length; row++) {
        for (unsigned int col = 0; col < length; col++) {
          (*this)(row,col) = unitlower(row,col);
        }
      }
    }

    if (verbose) {
      std::cout << "AFTER DECOMPOSITION:" << std::endl;
      std::cout << *this << std::endl;
    }

  }

  Vector Matrix::LinearSolve(const Vector& rhs) {
    std::size_t s = size1();
    assert (size2() == s);
    gsl_matrix* lu = gsl_matrix_calloc(s,s);
    gsl_matrix_memcpy(lu,v);
    gsl_permutation* p = gsl_permutation_alloc(s);
    gsl_permutation_init(p);
    int signum;
    gsl_linalg_LU_decomp(lu,p,&signum);
    const gsl_vector *b = rhs.v;
    gsl_vector *x = gsl_vector_calloc(s);
    gsl_linalg_LU_solve(lu,p,b,x);
    gsl_matrix_free(lu);
    gsl_permutation_free(p);
    return Vector(x);
  }


  // Special
  void Matrix::Reset() {
    gsl_matrix_set_zero(v);
  }

  void Matrix::Reset(double z) {
    gsl_matrix_set_all(v,z);
  }

  void Matrix::SetIdentity() {
    gsl_matrix_set_identity(v);
  }

}

//=============================================================================
