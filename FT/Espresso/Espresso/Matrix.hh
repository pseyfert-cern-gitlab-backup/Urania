/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the Matrix class
 */

#ifndef ESPRESSO_MATRIX_HH 
#define ESPRESSO_MATRIX_HH 1

// Include files
#include <cstddef>
#include <iostream>
#include <gsl/gsl_matrix.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/nvp.hpp>

#include "GSLWrappers.hh"

namespace Espresso {
  
  class Vector;

  /**
   * @class Matrix
   * @brief C++ wrapper around gsl_matrix
   */
  class Matrix {
    friend class Vector;

  public:

    /**
     * @brief Standard constructor
     * @param[in] n Number of rows
     * @param[in] m Number of columns
     */
    explicit Matrix(std::size_t n, std::size_t m);

    /// Copy constructor
    Matrix(const Matrix& rhs);

    /// Swap operator
    friend void swap(Matrix& first, Matrix& second);

    /// Named constructor to produce a Vector that doesn't own pointer
    static Matrix SoftWrap(gsl_matrix* v);

    /// Destructor
    ~Matrix();

    /// Assignment operator
    Matrix& operator= (Matrix rhs);

    /// Printing operator
    friend std::ostream& operator<< (std::ostream& os, const Matrix& m);    

    // Size

    /// Returns number of rows of matrix
    std::size_t size1() const;

    /// Returns number of columns of matrix
    std::size_t size2() const;

    /**
     * @brief Creates a submatrix from a given matrix
     * @details This is implemented through gsl_matrix_submatrix,
     * which means it contains a pointer to another matrix -- potentially dangerous!
     * This could be improved by borrowing a technique from std::shard_ptr:
     * keeping the gsl_matrix* in memory until all pointerss via submatrices are done.
     * This would require converting submatrix pointer into original gsl_matrix -- is this possible?
     * @param[in] k1 Upper left row where submatrix begins
     * @param[in] k2 Upper left column where submatrix begins
     * @param[in] n1 Number of rows in submatrix
     * @param[in] n2 Number of columns in submatrix
     */
    Matrix Submatrix(int k1, int k2, int n1, int n2);

    // Access operations

    /**
     * @brief Returns value from matrix
     * @param[in] i Row index
     * @param[in] j Column index
     */
    double Get(std::size_t i, std::size_t j);

    /**
     * Sets value in matrix
     * @param[in] i Row index
     * @param[in] j Column index
     * @param[in] z Value to set
     */
    void Set(std::size_t i, std::size_t j, double z);

    /**
     * @brief Returns value from matrix
     * @param[in] i Row index
     * @param[in] j Column index
     */
    double operator() (std::size_t i, std::size_t j) const;

    /**
     * @brief Returns reference to value from matrix
     * @param[in] i Row index
     * @param[in] j Column index
     * @return A reference to the matrix entry that can be used to modify it.
     */
    double& operator() (std::size_t i, std::size_t j);

    // Arithmetic

    /// Performs matrix addition in place
    Matrix& operator+= (const Matrix& rhs);

    /// Matrix addition binary operator
    friend Matrix operator+ (Matrix lhs, const Matrix& rhs);

    /// Performs matrix subtraction in place
    Matrix& operator-= (const Matrix& rhs);

    /// Matrix subtraction binary operator
    friend Matrix operator- (Matrix lhs, const Matrix& rhs);

    /// Matrix multiplication in place
    Matrix& operator*= (const Matrix& rhs);

    /// Matrix multiplication binary operator
    friend Matrix operator* (Matrix lhs, const Matrix& rhs);

    /// Multiplies the matrix by a constant in place
    Matrix& operator*= (const double& rhs);

    /// Binary operator to multiply matrix by a constant on the right
    friend Matrix operator* (Matrix lhs, const double& rhs);

    /// Binary operator to multiply matrix by a constant on the left
    friend Matrix operator* (const double& lhs, Matrix rhs);

    /// Divides the matrix by a constant in place
    Matrix& operator/= (const double& rhs);

    /// Binary operator to divide matrix by a constant on the right
    friend Matrix operator/ (Matrix lhs, const double& rhs);

    /// Transposes matrix in place
    void Transpose();

    // Determinant and Factorizations

    /**
     * @brief Returns determinant of matrix
     * @details There is currently a bug -- this Must be called twice in a row (?).
     */
    double Determinant();

    /**
     * @brief Inverts the matrix in place
     * @param[in] verbose Whether to print debugging information
     */
    void Invert(bool verbose = false);

    /**
     * @brief Perfors the Cholesky decomposition of the matrix in place
     * @details After the decomposition, the entries are stored in the upper
     * triangle of the matrix.
     * @param[in] verbose Whether to print debugging information
     */
    void Cholesky(bool verbose = false);

    /**
     * @brief Solves the matrix equation Ax=b for x
     * @param[in] rhs Vector b
     * @return x
     */
    Vector LinearSolve(const Vector& rhs);

    // Special

    /// Resets the matrix to the zero matrix
    void Reset();

    /// Resets the matrix to a specified constant
    void Reset(double z);

    /// Resets the matrix to the identity matrix 
    void SetIdentity();
    
  private:
    /**
     * @brief Constructor from gsl_matrix
     * @param[in] _v Raw pointer to gsl_matrix
     * @param[sw] If true, the Matrix is a "soft wrap" that does not own the pointer
     */
    Matrix(gsl_matrix* _v, bool sw = false);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_NVP(n);
      ar & BOOST_SERIALIZATION_NVP(m);
      if (Archive::is_loading::value) v = reinterpret_cast<epm_gsl_matrix*>(gsl_matrix_calloc(n,m));
      ar & boost::serialization::make_nvp("matrix_numrows",v->size1);
      ar & boost::serialization::make_nvp("matrix_numcols",v->size2);
      ar & boost::serialization::make_nvp("matrix_numrows_store",v->tda);
      ar & boost::serialization::make_nvp("matrix_data",boost::serialization::make_array(v->data,(v->size1-1)*v->tda+v->size2));
      ar & BOOST_SERIALIZATION_NVP(_isSubmatrix);
      ar & BOOST_SERIALIZATION_NVP(softwrap);
    }

  private:
    std::size_t n;
    std::size_t m;
    epm_gsl_matrix* v;
    bool _isSubmatrix;
    bool softwrap;
  };
}

namespace boost {
  namespace serialization {

    template<class Archive>
    inline void save_construct_data(Archive& ar, const Espresso::Matrix* v, const unsigned int version) {
      std::size_t n = v->size1();
      std::size_t m = v->size2();
      ar << boost::serialization::make_nvp("matrix_construct_numrows",n);
      ar << boost::serialization::make_nvp("matrix_construct_numcols",m);
    }

    template<class Archive>
    inline void load_construct_data(Archive& ar, Espresso::Matrix* v, const unsigned int version) {
      std::size_t n,m;
      ar >> boost::serialization::make_nvp("matrix_construct_numrows",n);
      ar >> boost::serialization::make_nvp("matrix_construct_numcols",m);
      ::new(v)Espresso::Matrix(n,m);
    }
  }
}
    
#endif // ESPRESSO_MATRIX_HH


/**
 * @}
 */
