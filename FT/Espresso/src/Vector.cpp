// Include files
#include "Matrix.hh"

// local
#include "Vector.hh"

#include <iomanip>

#include <gsl/gsl_blas.h>

namespace Espresso
{

  // Constructor
  Vector::Vector(std::size_t _n)
    : n(_n),
      v(gsl_vector_calloc(n)),
      softwrap(false)
  {
    Reset();
  }

  // Copy constructor
  Vector::Vector(const Vector& rhs)
    : n(rhs.n),
      v(gsl_vector_alloc(rhs.v->size)),
      softwrap(false)
  {
    gsl_vector_memcpy(v,rhs.v);
  }

  // Constructor from std::vector
  Vector::Vector(const std::vector<double>& _v)
    : Vector(_v.size())
  {
    for (unsigned int i = 0; i < _v.size(); i++)
      (*this)[i] = _v[i];
  }

  // Private constructor
  Vector::Vector(gsl_vector* _v, bool sw)
    : n(_v->size),
      v(_v),
      softwrap(sw)
  {
  }

  // Making a soft-wrap vector
  Vector Vector::SoftWrap(gsl_vector* _v) {
    return Vector(_v,true);
  }

  // Swap operator
  void swap(Vector& first, Vector& second) {
    std::size_t ntemp = first.n;
    first.n = second.n;
    second.n = ntemp;
    gsl_vector* temp = first.v;
    first.v = second.v;
    second.v = temp;
    bool btemp = first.softwrap;
    first.softwrap = second.softwrap;
    second.softwrap = btemp;
  }

  // Destructor
  Vector::~Vector() {
    if (not softwrap) {
      gsl_vector_free(v);
    }
  }

  // Assignment
  Vector& Vector::operator= (Vector rhs) {
    swap(*this,rhs);
    return *this;
  }

  // Printing
  std::ostream& operator<< (std::ostream& os, const Vector& v) {
    for (unsigned int row = 0; row < v.size(); row++) {
      os << std::setprecision(3)
         << std::setw(9)
         << v(row);
      if (row != v.size()-1) os << " | ";
    }
    return os;
  }

  std::size_t Vector::size() const { return n; }

  // Access
  double* Vector::GetArray() {
    return v->data;
  }

  const double* Vector::GetArray() const {
    return v->data;
  }

  double Vector::Get(std::size_t k) const {
    return gsl_vector_get(v,k);
  }

  void Vector::Set(std::size_t k, double z) {
    gsl_vector_set(v,k,z);
  }

  // DEPRECATE!
  double Vector::operator() (std::size_t k) const {
    return *gsl_vector_const_ptr(v,k);
  }

  // DEPRECATE!
  double& Vector::operator() (std::size_t k) {
    return *gsl_vector_ptr(v,k);
  }

  double Vector::operator[] (std::size_t k) const {
    return *gsl_vector_const_ptr(v,k);
  }

  double& Vector::operator[] (std::size_t k) {
    return *gsl_vector_ptr(v,k);
  }

  // Arithmetic
  Vector& Vector::operator+= (const Vector& rhs) {
    const gsl_vector* u = rhs.v;
    gsl_vector_add(v, u);
    return *this;
  }
  Vector operator+ (Vector lhs, const Vector& rhs) {
    return lhs += rhs;
  }

  Vector& Vector::operator-= (const Vector& rhs) {
    const gsl_vector* u = rhs.v;
    gsl_vector_sub(v, u);
    return *this;
  }
  Vector operator- (Vector lhs, const Vector& rhs) {
    return lhs -= rhs;
  }

  Vector& Vector::operator*= (const double& rhs) {
    gsl_vector_scale(v,rhs);
    return *this;
  }
  Vector operator* (Vector lhs, const double& rhs) {
    return lhs *= rhs;
  }
  Vector operator* (const double& lhs, Vector rhs) {
    return rhs *= lhs;
  }

  Vector& Vector::operator/= (const double& rhs) {
    gsl_vector_scale(v,1.0/rhs);
    return *this;
  }
  Vector operator/ (Vector lhs, const double& rhs) {
    return lhs /= rhs;
  }

  Vector& Vector::operator*= (const Matrix& lhs) {
    gsl_vector* vnew = gsl_vector_calloc(v->size);
    gsl_blas_dgemv(CblasNoTrans, 1.0, lhs.v, v, 0.0, vnew);
    gsl_vector_free(v);
    this->v = vnew;
    return *this;
  }
  Vector operator* (Vector lhs, const Matrix& rhs) {
    return lhs *= rhs;
  }
  Vector operator* (const Matrix& lhs, Vector rhs) {
    return rhs *= lhs;
  }

  double operator* (const Vector& lhs, const Vector& rhs)
  {
    double result;
    gsl_blas_ddot(lhs.v,rhs.v,&result);
    return result;
  }

  // Special
  void Vector::Reset() {
    gsl_vector_set_zero(v);
  }

  void Vector::Reset(double z) {
    gsl_vector_set_all(v,z);
  }

  void Vector::SetBasis(std::size_t k) {
    gsl_vector_set_basis(v,k);
  }

}
