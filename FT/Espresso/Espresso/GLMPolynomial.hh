/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the GLMPolynomial class
 */

#ifndef ESPRESSO_GLMPOLYNOMIAL_HH
#define ESPRESSO_GLMPOLYNOMIAL_HH 1

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "GLMModel.hh"
#include "Matrix.hh"

namespace Espresso {

  /**
   * @class GLMPolynomial
   * @brief A simple n-th degree polynomial GLM (X, X<sup>2</sup>, ..., X<sup>n</sup>)
   */
  class GLMPolynomial : public GLMModel {
  public:

    /// Standard constructor
    GLMPolynomial(unsigned int _degree)
      : degree(_degree),
        basis(degree+1,degree+1)
    {
      basis.SetIdentity();
    }

    /// Standard constructor
    GLMPolynomial(unsigned int _degree, const Matrix& _basis)
      : degree(_degree),
        basis(_basis)
    {
    }

    /// Copy constructor
    GLMPolynomial(const GLMPolynomial& rhs)
      : degree(rhs.degree),
	basis(rhs.basis)
    {
    }

    /// Standard destructor
    virtual ~GLMPolynomial() {};

    virtual bool SubtractEta() const override { return true; }

    virtual bool PreProcessWithLink() const override { return true; }

    virtual unsigned int NumParams() const override { return degree+1; }

    virtual Vector GetBasis(double eta) const override;

    std::string PolyBasisString(bool latex = false) const;

    virtual void print(std::ostream& os) const override;

  private:
    virtual GLMPolynomial* doClone() const override {
      return new GLMPolynomial(*this);
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(GLMModel);
      //ar & boost::serialization::base_object<GLMModel>(*this);
      ar & BOOST_SERIALIZATION_NVP(degree);
      ar & BOOST_SERIALIZATION_NVP(basis);
    }

  private:
    unsigned int degree;
    Matrix basis;
  };

}

namespace boost {
  namespace serialization {

    template<class Archive>
    inline void save_construct_data(Archive& ar, const Espresso::GLMPolynomial* v, const unsigned int version) {
      std::size_t degree = v->NumParams()-1;
      ar << boost::serialization::make_nvp("poly_construct_degree",degree);
    }

    template<class Archive>
    inline void load_construct_data(Archive& ar, Espresso::GLMPolynomial* v, const unsigned int version) {
      unsigned int degree;
      ar >> boost::serialization::make_nvp("poly_construct_degree",degree);
      ::new(v)Espresso::GLMPolynomial(degree);
    }
  }
}

BOOST_CLASS_EXPORT_KEY(Espresso::GLMPolynomial)

#endif // ESPRESSO_GLMPOLYNOMIAL_HH

/**
 * @}
 */
