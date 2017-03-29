/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the Vector class
 */

#ifndef ESPRESSO_VECTOR_HH 
#define ESPRESSO_VECTOR_HH 1

// Include files
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include <gsl/gsl_vector.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/nvp.hpp>

#include "GSLWrappers.hh"

namespace Espresso {

  class Matrix;
  
  /**
   * @class Vector
   * @brief C++ wrapper and gsl_vector
   */

  class Vector {
    friend class Matrix;

  public:

    /**
     * @brief Standard constructor
     * @param[in] n Number of entries
     */
    explicit Vector(std::size_t n);

    /// Copy constructor
    Vector(const Vector& rhs);

    /// Constructor from std::vector
    Vector(const std::vector<double>& vec);

    /// Swap operator
    friend void swap(Vector& first, Vector& second);

    /// Named constructor to produce a Vector that doesn't own pointer
    // static Vector SoftWrap(std::size_t n, gsl_vector* v);
    static Vector SoftWrap(gsl_vector* v);

    /// Destructor
    ~Vector();

    /// Assignment operator
    Vector& operator= (Vector rhs);

    /// Printing operator
    friend std::ostream& operator<< (std::ostream& os, const Vector& v);

    /// Size
    std::size_t size() const;

    // Access

    /// Get array pointer
    double* GetArray();
    
    /// Get constant array pointer
    const double* GetArray() const;
    
    /**
     * @brief Returns value from vector
     * @param[in] k Index
     */
    double Get(std::size_t k) const;

    /**
     * Sets value in vector
     * @param[in] k Index
     * @param[in] z Value to set
     */
    void Set(std::size_t k, double z);

    /**
     * @brief Returns value from vector
     * @details This should be deprecated
     * @param[in] k Index
     */
    double operator() (std::size_t k) const;

    /**
     * @brief Returns reference value from vector
     * @details This should be deprecated
     * @param[in] k Index
     * @return A reference to the vector entry that can be used to modify it.
     */
    double& operator() (std::size_t k);

    /**
     * @brief Returns value from vector
     * @param[in] k Index
     */
    double operator[] (std::size_t k) const;

    /**
     * @brief Returns reference value from vector
     * @param[in] k Index
     * @return A reference to the vector entry that can be used to modify it.
     */
    double& operator[] (std::size_t k);

    // Arithmetic

    /// Performs vector addition in place
    Vector& operator+= (const Vector& rhs);

    /// Vector addition binary operator
    friend Vector operator+ (Vector lhs, const Vector& rhs);

    /// Performs vector subtraction in place
    Vector& operator-= (const Vector& rhs);

    /// Vector subtraction binary operator
    friend Vector operator- (Vector lhs, const Vector& rhs);

    /// Multiplies the vector by a constant in place
    Vector& operator*= (const double& rhs);

    /// Binary operator to multiply vector by a constant on the right
    friend Vector operator* (Vector lhs, const double& rhs);

    /// Binary operator to multiply vector by a constant on the left
    friend Vector operator* (const double& lhs, Vector rhs);

    /// Divides the vector by a constant in place
    Vector& operator/= (const double& rhs);

    /// Binary operator to divide vector by a constant on the right
    friend Vector operator/ (Vector lhs, const double& rhs);

    /// Multiplies the vector by a matrix on the left
    Vector& operator*= (const Matrix& lhs);

    /// Binary operator to multiply vector by a Matrix on the right
    friend Vector operator* (Vector lhs, const Matrix& rhs);

    /// Binary operator to multiply vector by a Matrix on the left
    friend Vector operator* (const Matrix& lhs, Vector rhs);

    /// Performs inner product of vectors
    friend double operator* (const Vector& lhs, const Vector& rhs);

    // Special
    void Reset();
    void Reset(double z);
    void SetBasis(std::size_t k);

  private:    
    /**
     * @brief Constructor from gsl_vector
     * @param[in] _v Raw pointer to gsl_vector
     * @param[sw] If true, the Vector is a "soft wrap" that does not own the pointer
     */
    Vector(gsl_vector* _v, bool sw = false);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_NVP(n);
      if (Archive::is_loading::value) v = reinterpret_cast<epm_gsl_vector*>(gsl_vector_calloc(n));
      ar & boost::serialization::make_nvp("vector_size",v->size);
      ar & boost::serialization::make_nvp("vector_data",boost::serialization::make_array(v->data,v->size));
      ar & BOOST_SERIALIZATION_NVP(softwrap);
    }

  private:
    std::size_t n;
    epm_gsl_vector* v;
    bool softwrap;
  };
}

namespace boost {
  namespace serialization {

    template<class Archive>
    inline void save_construct_data(Archive& ar, const Espresso::Vector* v, const unsigned int version) {
      std::size_t n = v->size();
      ar << boost::serialization::make_nvp("vector_construct_size",n);
    }

    template<class Archive>
    inline void load_construct_data(Archive& ar, Espresso::Vector* v, const unsigned int version) {
      std::size_t n;
      ar >> boost::serialization::make_nvp("vector_construct_size",n);
      ::new(v)Espresso::Vector(n);
    }
  }
}

#endif // ESPRESSO_VECTOR_HH


/**
 * @}
 */
