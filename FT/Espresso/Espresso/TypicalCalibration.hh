/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file implements the abstract TypicalCalibration class
 */

#ifndef TYPICALCALIBRATION_H
#define TYPICALCALIBRATION_H

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "Calibration.hh"
#include "Vector.hh"
#include "Matrix.hh"

namespace Espresso
{

  /**
   * @class TypicalCalibration
   * @brief This base class implements the Calibration interface with a standard
   * way to store calibration parameters and covariances
   */
  class TypicalCalibration : public Calibration {
  public:

    /**
     * @brief Standard constructor specifing number of parameters.
     * @param[in] _numParams Number of parameters (not including 2x factor from delta parameters)
     */
    TypicalCalibration(unsigned int _numParams)
      : numParams(_numParams),
        coeffs(numParams),
        delta_coeffs(numParams),
        covariance(numParams,numParams),
        delta_covariance(numParams,numParams),
        cross_covariance(numParams,numParams)
    {
    }


    /**
     * @brief Constructor specifing number of parameters and their values.
     * @param[in] _numParams Number of parameters (not including 2x factor from delta parameters)
     * @param[in] _coeffs Values of (non-delta) calibration parameters
     * @param[in] _delta_coeffs Values of delta calibration parameters
     */
    TypicalCalibration(unsigned int _numParams,
                       const Vector& _coeffs, const Vector& _delta_coeffs)
      : numParams(_numParams),
        coeffs(_coeffs),
        delta_coeffs(_delta_coeffs),
        covariance(numParams,numParams),
        delta_covariance(numParams,numParams),
        cross_covariance(numParams,numParams)
    {
    }

    /**
     * @brief Constructor specifing number of parameters, their values, and their covariances.
     * @param[in] _numParams Number of parameters (not including 2x factor from delta parameters)
     * @param[in] _coeffs Values of (non-delta) calibration parameters
     * @param[in] _delta_coeffs Values of delta calibration parameters
     * @param[in] _covariance Covariance matrix of calibration (non-delta) parameters
     * @param[in] _delta_covariance Covariance matrix of calibration delta parameters
     * @param[in] _cross_covariance Covariance matrix of calibration non-delta parameters with delta parameters
     */
    TypicalCalibration(unsigned int _numParams,
                       const Vector& _coeffs, const Vector& _delta_coeffs,
                       const Matrix& _covariance, const Matrix& _delta_covariance, const Matrix& _cross_covariance)
      : numParams(_numParams),
        coeffs(_coeffs),
        delta_coeffs(_delta_coeffs),
        covariance(_covariance),
        delta_covariance(_delta_covariance),
        cross_covariance(_cross_covariance)
    {
    }

    /// Copy Constructor
    TypicalCalibration(const TypicalCalibration& rhs)
      : numParams(rhs.numParams),
        coeffs(rhs.coeffs),
        delta_coeffs(rhs.delta_coeffs),
        covariance(rhs.covariance),
        delta_covariance(rhs.delta_covariance),
        cross_covariance(rhs.cross_covariance)
    {
    }

    // /// Move Constructor
    // TypicalCalibration(TypicalCalibration&& rhs)
    //   : numParams(std::move(rhs.numParams)),
    //     coeffs(std::move(rhs.coeffs)),
    //     delta_coeffs(std::move(rhs.delta_coeffs)),
    //     covariance(std::move(rhs.covariance)),
    //     delta_covariance(std::move(rhs.delta_covariance)),
    //     cross_covariance(std::move(rhs.cross_covariance))
    // {
    // }



    /// Returns pointer to contents of Vector containing calibration parameters
    double* GetCoeffArray();

    /// Returns const pointer to contents of Vector containing calibration parameters
    const double* GetCoeffArray() const;

    virtual unsigned int NumParams() const override { return numParams; };

    virtual Vector GetCoeffs() const override { return coeffs; };
    virtual Vector GetDeltaCoeffs() const override { return delta_coeffs; };
    virtual Matrix GetCovarianceMatrix() const override { return covariance; };
    virtual Matrix GetDeltaCovarianceMatrix() const override { return delta_covariance; };
    virtual Matrix GetCrossCovarianceMatrix() const override { return cross_covariance; };

    virtual double GetCoeff(unsigned int k) const override;
    virtual double GetError(unsigned int k) const override;
    virtual double GetDeltaCoeff(unsigned int k) const override;
    virtual double GetDeltaError(unsigned int k) const override;
    virtual double GetCovariance(unsigned int k, unsigned int l) const override;
    virtual double GetCorrelation(unsigned int k, unsigned int l) const override;
    virtual double GetDeltaCovariance(unsigned int k, unsigned int l) const override;
    virtual double GetDeltaCorrelation(unsigned int k, unsigned int l) const override;
    virtual double GetCrossCovariance(unsigned int k, unsigned int l) const override;
    virtual double GetCrossCorrelation(unsigned int k, unsigned int l) const override;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Calibration);
      //ar & boost::serialization::base_object<Calibration>(*this);
      ar & BOOST_SERIALIZATION_NVP(numParams);
      ar & BOOST_SERIALIZATION_NVP(coeffs);
      ar & BOOST_SERIALIZATION_NVP(delta_coeffs);
      ar & BOOST_SERIALIZATION_NVP(covariance);
      ar & BOOST_SERIALIZATION_NVP(delta_covariance);
      ar & BOOST_SERIALIZATION_NVP(cross_covariance);
    }

  private:
    unsigned int numParams;
    Vector coeffs;
    Vector delta_coeffs;
    Matrix covariance;
    Matrix delta_covariance;
    Matrix cross_covariance;
  };
}

BOOST_CLASS_EXPORT_KEY(Espresso::TypicalCalibration)

#endif


/**
 * @}
 */
