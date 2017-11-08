/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the GLMCalibrationFunction class.
 */

#ifndef ESPRESSO_GLMCALIBRATIONFUNCTION_HH
#define ESPRESSO_GLMCALIBRATIONFUNCTION_HH 1

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "CalibrationFunction.hh"
#include "GLMModel.hh"
#include "RegressionFunctions.hh"

namespace Espresso {

  /**
   * @class GLMCalibrationFunction
   * @brief Implementation of the CalibrationFunction interface
   * for a generalized linear model (GLM).
   * @details A GLM calibration function consists of a GLM itself (represented with the class GLMModel)
   * and a link function (represented by Regression::LinkType). Together these model a function
   * g(&omega;) = g<sub>0</sub> + &theta;<sub>i</sub> b(&eta;)<sup>i</sup>.
   * The basis functions b(&eta;)<sup>i</sup> can be polynomials or splines, as specified by the GLMModel,
   * and their values are cached when possible for performance.
   */

  class GLMCalibrationFunction : public CalibrationFunction {
  public:

    /// Default
    GLMCalibrationFunction();

    /// Standard constructor
    GLMCalibrationFunction(const GLMModel& _glm, Regression::LinkType _L = Regression::DefaultLinkType);

    GLMCalibrationFunction(const GLMCalibrationFunction& rhs);

    GLMCalibrationFunction& operator= (GLMCalibrationFunction func);

    /// Standard destructor
    virtual ~GLMCalibrationFunction() {};

    virtual unsigned int NumParams() const override { return length; }

    Regression::LinkType CalibrationLink() const { return L; }

    std::unique_ptr<GLMModel> CalibrationModel() const { return glm->clone(); }

    virtual double Value(double eta, const double* theta) const override;

    virtual double Derivative(double eta, unsigned int k, const double* theta) const override;

    virtual Vector Derivative(double eta, const double* theta) const override;

    double GetOffset(double eta) const;

    Vector GetBasis(double eta) const;

    void print(std::ostream& os) const override;

    static double Value(Vector glmBasis, Regression::LinkType L, const double* theta, double offset = 0);

    static double Derivative(Vector glmBasis, Regression::LinkType L, unsigned int k, const double* theta, double offset = 0);

    static Vector Derivative(Vector glmBasis, Regression::LinkType L, const double* theta, double offset = 0);

    /// Clones the function, returning a smart pointer
    std::unique_ptr<GLMCalibrationFunction> clone() const { return std::unique_ptr<GLMCalibrationFunction>(doClone()); }

  private:

    void updateCache(double eta) const;

    virtual GLMCalibrationFunction* doClone() const override {
      return new GLMCalibrationFunction(*this);
    };

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CalibrationFunction);
      //ar & boost::serialization::base_object<CalibrationFunction>(*this);
      ar & BOOST_SERIALIZATION_NVP(glm);
      ar & BOOST_SERIALIZATION_NVP(length);
      ar & BOOST_SERIALIZATION_NVP(L);
    }

 private:
    std::unique_ptr<GLMModel> glm;
    unsigned int length;
    Regression::LinkType L;
    mutable double etac;
    mutable double offsetc;
    mutable Vector basisc;
  };

}

// namespace boost {
//   namespace serialization {

//     template<class Archive>
//     inline void save_construct_data(Archive& ar, const Espresso::GLMCalibrationFunction* v, const unsigned int version) {
//       ar << v->NumParams()-1;
//     }

//     template<class Archive>
//     inline void load_construct_data(Archive& ar, Espresso::GLMCalibrationFunction* v, const unsigned int version) {
//       unsigned int degree;
//       ar >> degree;
//       ::new(v)Espresso::GLMCalibrationFunction(degree);
//     }
//   }
// }

BOOST_CLASS_EXPORT_KEY(Espresso::GLMCalibrationFunction)

#endif // ESPRESSO_POLYCALIBRATIONFUNCTION_HH

/**
 * @}
 */
