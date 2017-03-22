/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the GLMBSpline class.
 */

#ifndef ESPRESSO_GLMBSPLINE_HH
#define ESPRESSO_GLMBSPLINE_HH 1

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "GLMModel.hh"

namespace Espresso {

  /**
   * @class GLMBSpline
   * @brief Implementation of a b-spline GLM
   * @details This implemention the abstract GLMModel interface represents a cubic b-spline calibration model.
   * Given N nodes, including the lower and upper bound, there are N+2 degrees of freedom in the b-spline model.
   * No interpolation outside of the region defined by the boundary nodes is possible.
   * The algorithm to calculate the b-splines is taken from "The Elements of Statistical Learning" by
   * Hastie, Tibshirani, and Friedman, 2nd edition. More mathematical detail is available there.
   */
  class GLMBSpline : public GLMModel {
  public:

    /// Standard constructor
    GLMBSpline(const std::vector<double>& _nodes)
      : nodes(_nodes),
	size(nodes.size()),
	tau(size+6,0.0),
	b1(size+5,0.0),
	b2(size+4,0.0),
	b3(size+3,0.0),
	b4(size+2,0.0)
    {
      for (std::size_t i = 0; i < 3; i++)
	tau[i] = nodes[0];
      for (std::size_t i = 3; i < size+3; i++)
	tau[i] = nodes[i-3];
      for (std::size_t i = size+3; i < size+6; i++)
	tau[i] = nodes[size-1];
      GetBasis(0.0);
    }

    /// Standard constructor
    GLMBSpline(const GLMBSpline& rhs)
      : nodes(rhs.nodes),
	size(nodes.size()),
	tau(size+6,0.0),
	b1(size+5,0.0),
	b2(size+4,0.0),
	b3(size+3,0.0),
	b4(size+2,0.0)
    {
      for (std::size_t i = 0; i < 3; i++)
	tau[i] = nodes[0];
      for (std::size_t i = 3; i < size+3; i++)
	tau[i] = nodes[i-3];
      for (std::size_t i = size+3; i < size+6; i++)
	tau[i] = nodes[size-1];
      GetBasis(0.0);
    }


    /// Standard destructor
    virtual ~GLMBSpline() {};

    std::vector<double> GetNodes() const { return nodes; }

    virtual bool SubtractEta() const override { return true; }

    virtual bool PreProcessWithLink() const override { return false; }

    virtual unsigned int NumParams() const override { return size+2; }

    virtual Vector GetBasis(double eta) const override;

    virtual void print(std::ostream& os) const override;

  private:
    virtual GLMBSpline* doClone() const override {
      return new GLMBSpline(*this);
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(GLMModel);
      //ar & boost::serialization::base_object<GLMModel>(*this);
      ar & BOOST_SERIALIZATION_NVP(nodes);
      ar & BOOST_SERIALIZATION_NVP(size);
      ar & BOOST_SERIALIZATION_NVP(tau);
    }

  private:
    std::vector<double> nodes;
    unsigned int size;
    mutable std::vector<double> tau;
    mutable std::vector<double> b1;
    mutable std::vector<double> b2;
    mutable std::vector<double> b3;
    mutable std::vector<double> b4;
  };

}

namespace boost {
  namespace serialization {

    template<class Archive>
    inline void save_construct_data(Archive& ar, const Espresso::GLMBSpline* v, const unsigned int version) {
      std::vector<double> nodes = v->GetNodes();
      ar << BOOST_SERIALIZATION_NVP(nodes);
    }

    template<class Archive>
    inline void load_construct_data(Archive& ar, Espresso::GLMBSpline* v, const unsigned int version) {
      std::vector<double> nodes;
      ar >> BOOST_SERIALIZATION_NVP(nodes);
      ::new(v)Espresso::GLMBSpline(nodes);
    }
  }
}

BOOST_CLASS_EXPORT_KEY(Espresso::GLMBSpline)

#endif // ESPRESSO_GLMBSPLINE_HH

/**
 * @}
 */
