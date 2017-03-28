/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the GLMNSpline class.
 */

#ifndef ESPRESSO_GLMNSPLINE_HH
#define ESPRESSO_GLMNSPLINE_HH 1

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "GLMModel.hh"
#include "Matrix.hh"

namespace Espresso {

  /** @class GLMNSpline
   * @brief Implementation of an n-spline GLM
   * @details This implemention the abstract GLMModel interface represents a cubic n-spline calibration model.
   * Given N nodes, including the lower and upper bound, there are N degrees of freedom in the b-spline model.
   * Interpolation outside of the region defined by the boundary nodes is possible because the function
   * is constrained to be linear at the boundaries.
   * The algorithm to calculate the n-splines is taken from "The Elements of Statistical Learning" by
   * Hastie, Tibshirani, and Friedman, 2nd edition. More mathematical detail is available there.
   */
  class GLMNSpline : public GLMModel {
  public:

    /// Empty constructor
    GLMNSpline()
      : nodes(),
        size(0),
        basis(std::size_t(0),std::size_t(0))
    {
    }

    /// Standard constructor
    GLMNSpline(const std::vector<double>& _nodes)
      : nodes(_nodes),
        size(nodes.size()),
        basis(size,size)

    {
      basis.SetIdentity();
      GetBasis(0.0);
    }

    /// Standard constructor
    GLMNSpline(const GLMNSpline& rhs, const Matrix& _basis)
      : nodes(rhs.nodes),
        size(nodes.size()),
        basis(_basis)
    {
      GetBasis(0.0);
    }

    /// Standard destructor
    virtual ~GLMNSpline() {};

    std::vector<double> GetNodes() const { return nodes; }

    virtual bool SubtractEta() const override { return true; }

    virtual bool PreProcessWithLink() const override { return true; }

    virtual unsigned int NumParams() const override { return size; }

    virtual Vector GetBasis(double eta) const override;

    std::string NSplineBasisString(bool latex = false) const;

    virtual void print(std::ostream& os) const override;

  private:
    virtual GLMNSpline* doClone() const override {
      return new GLMNSpline(*this);
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(GLMModel);
      //ar & boost::serialization::base_object<GLMModel>(*this);
      ar & BOOST_SERIALIZATION_NVP(nodes);
      ar & BOOST_SERIALIZATION_NVP(size);
      ar & BOOST_SERIALIZATION_NVP(basis);
    }

  private:
    std::vector<double> nodes;
    unsigned int size;
    Matrix basis;
  };

}

namespace boost {
  namespace serialization {

    template<class Archive>
    inline void save_construct_data(Archive& ar, const Espresso::GLMNSpline* v, const unsigned int version) {
      std::vector<double> nodes = v->GetNodes();
      ar << BOOST_SERIALIZATION_NVP(nodes);
    }

    template<class Archive>
    inline void load_construct_data(Archive& ar, Espresso::GLMNSpline* v, const unsigned int version) {
      std::vector<double> nodes;
      ar >> BOOST_SERIALIZATION_NVP(nodes);
      ::new(v)Espresso::GLMNSpline(nodes);
    }
  }
}

BOOST_CLASS_EXPORT_KEY(Espresso::GLMNSpline)

#endif // ESPRESSO_GLMNSPLINE_HH

/**
 * @}
 */
