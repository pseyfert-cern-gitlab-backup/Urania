/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the GLMCalibration class.
 */

#ifndef POLYCALIBRATION_H
#define POLYCALIBRATION_H

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "GLMCalibrationFunction.hh"
#include "TypicalCalibration.hh"

namespace Espresso
{

  /**
   * @class GLMCalibration
   * @brief Objects that applies a generalized linear model (GLM) calibration to tagging decisions.
   * @details This is a concrete implementation of Calibration for GLMs.
   * It inherits the storage and interface to the tagging parameter values and covariances
   * from TypicalCalibration. The GLM function itself is performed through the GLMCalibrationFunction class,
   * which is either directly passed to the constructor or created within the constructor.
   */
  class GLMCalibration : public TypicalCalibration {
  public:

    /// Default constructor
    GLMCalibration();

    /**
     * Construct blank calibration by passing GLM basis, construction calibration function
     * @param[in] _glm generalized linear model basis
     * @param[in] _L Link used to transform &omega; and &eta;
     */
    GLMCalibration(const GLMModel& _glm, Regression::LinkType _L = Regression::DefaultLinkType);

    /**
     * Construct empty calibration by passing calibration function
     * @param[in] _func calibration function
     */
    GLMCalibration(const GLMCalibrationFunction& _func);

    /**
     * Construct calibration passing polynomial basis and parameter values.
     * @param[in] _glm generalized linear model basis
     * @param[in] _L Link used to transform &omega; and &eta;
     * @param[in] _coeffs Values of (non-delta) calibration parameters
     * @param[in] _delta_coeffs Values of delta calibration parameters
     */
    GLMCalibration(const GLMModel& _glm, Regression::LinkType _L,
		   const Vector& _coeffs, const Vector& _delta_coeffs);

    /**
     * Construct calibration passing polynomial basis and parameter values.
     * @param[in] _func calibration function
     * @param[in] _coeffs Values of (non-delta) calibration parameters
     * @param[in] _delta_coeffs Values of delta calibration parameters
     */
    GLMCalibration(const GLMCalibrationFunction& _func,
		   const Vector& _coeffs, const Vector& _delta_coeffs);

    /**
     * Construct calibration passing polynomial basis, parameter values, and covariances.
     * @param[in] _glm generalized linear model basis
     * @param[in] _L Link used to transform &omega; and &eta;
     * @param[in] _coeffs Values of (non-delta) calibration parameters
     * @param[in] _delta_coeffs Values of delta calibration parameters
     * @param[in] _covariance Covariance matrix of calibration (non-delta) parameters
     * @param[in] _delta_covariance Covariance matrix of calibration delta parameters
     * @param[in] _cross_covariance Covariance matrix of calibration non-delta parameters with delta parameters
     */
    GLMCalibration(const GLMModel& _glm, Regression::LinkType _L,
		   const Vector& _coeffs, const Vector& _delta_coeffs,
		   const Matrix& _covariance, const Matrix& _delta_covariance, const Matrix& _cross_covariance);

    /**
     * Construct calibration passing polynomial basis, parameter values, and covariances.
     * @param[in] _func calibration function
     * @param[in] _coeffs Values of (non-delta) calibration parameters
     * @param[in] _delta_coeffs Values of delta calibration parameters
     * @param[in] _covariance Covariance matrix of calibration (non-delta) parameters
     * @param[in] _delta_covariance Covariance matrix of calibration delta parameters
     * @param[in] _cross_covariance Covariance matrix of calibration non-delta parameters with delta parameters
     */
    GLMCalibration(const GLMCalibrationFunction& _func,
		   const Vector& _coeffs, const Vector& _delta_coeffs,
		   const Matrix& _covariance, const Matrix& _delta_covariance, const Matrix& _cross_covariance);

    /// Copy Constructor
    GLMCalibration(const GLMCalibration& rhs);

    /// A catch-all exception for problems with the XML calibration archive
    struct DeserializationException : public std::runtime_error {
      DeserializationException()
	: std::runtime_error("The XML archive requested does not exist or is corrupted.")
      {
      }
    };

    /// Construct GLMCalibration by loading from archive file
    static GLMCalibration Deserialize(std::string name, std::ifstream& ifs);

    /// Save GLMCalibration to an archive file
    void Serialize(std::string name, std::ofstream& ofs) const;

    /// Returns calibration link (e.g. mistag (identity), logit, probit, cauchit
    Regression::LinkType CalibrationLink() const { return func.CalibrationLink(); }

    /// Returns GLMModel (e.g. polynomial, b-spline, or n-spline
    std::unique_ptr<GLMModel> CalibrationModel() const { return func.CalibrationModel(); }

    /// Returns GLMCalibrationFunction
    std::unique_ptr<GLMCalibrationFunction> getCalibrationFunction() const { return func.clone(); }

    virtual double Value(double eta) const override;
    virtual Vector Derivative(double eta) const override;
    virtual ConfidenceInterval ValueRange(double eta, int sigmaConf) const override;
    virtual double Value(double eta, Flavour flavour) const override;
    virtual Vector Derivative(double eta,Flavour flavour) const override;

    virtual double GetOffset(double eta) const override { return func.GetOffset(eta); }
    virtual Vector GetBasis(double eta) const override { return func.GetBasis(eta); }

    virtual void print(std::ostream& os) const override;

  private:
    virtual GLMCalibration* doClone() const override {
      return new GLMCalibration(*this);
    };

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TypicalCalibration);
      //ar & boost::serialization::base_object<TypicalCalibration>(*this);
      ar & BOOST_SERIALIZATION_NVP(func);
    }

  private:
    GLMCalibrationFunction func;
  };

}

BOOST_CLASS_EXPORT_KEY(Espresso::GLMCalibration)

#endif


/**
 * @}
 */
