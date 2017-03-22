/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header defines the abstract StandardCalibration class.
 */

#ifndef STANDARDCALIBRATION_H
#define STANDARDCALIBRATION_H

// Include files
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "Calibration.hh"
#include "RegressionFunctions.hh"

namespace Espresso
{
  // Forward declarations
  class Matrix;

  /**
   * @class StandardCalibration
   * @brief Standard 2x2 parameter linear calibration, with optional link.
   * @details This class implements the standard linear calibration,
   * with two parameters, two delta parameters, and a link function g:
   * \f[ g(\omega) = g(\eta_0) + p_0 + p_1 \left( g(\eta) - g(\eta_0)\right)\f]
   * So, p<sub>0</sub> corresponds actually to what is sometimes called &Delta;p<sub>0</sub>.
   * The class gives double& access to all parameters so that they can be set
   * using the input/output utility declareProperty( "variableName", double variable&).
   * This is maybe not the best solution, but I didn't want to modify the declareProperty tool.
   * The actual implmentation in the code uses
   * \f[ g(\omega) = g(\eta) + p_0 + p_1 \left( g(\eta) - g(\eta_0)\right)\f]
   * which differs from the above by p<sub>1</sub> &rarr; p<sub>1</sub> - 1.
   * The tool that read the calibration settings from the options file performs this transformation.
   */
  class StandardCalibration : public Calibration {
  public:

    /**
     * @brief Default constructor
     * @details Simple constructor that creates a trivial calibration
     * where &omega;(&eta;) = &eta;.
     */
    StandardCalibration();

    virtual double Value(double eta) const override;
    virtual ConfidenceInterval ValueRange(double eta, int sigmaConf) const override;
    virtual double Value(double eta, Flavour flavour) const override;
    virtual Vector Derivative(double eta) const override;
    virtual Vector Derivative(double eta, Flavour flavour) const override;

    virtual double GetOffset(double eta) const override;
    virtual Vector GetBasis(double eta) const override;

    virtual unsigned int NumParams() const override { return 2; };

    virtual Vector GetCoeffs() const override;
    virtual Vector GetDeltaCoeffs() const override;
    virtual Matrix GetCovarianceMatrix() const override;
    virtual Matrix GetDeltaCovarianceMatrix() const override;
    virtual Matrix GetCrossCovarianceMatrix() const override;

    virtual double GetCoeff(unsigned int) const override;
    virtual double GetError(unsigned int) const override;
    virtual double GetDeltaCoeff(unsigned int) const override;
    virtual double GetDeltaError(unsigned int) const override;
    virtual double GetCovariance(unsigned int k, unsigned int l) const override;
    virtual double GetCorrelation(unsigned int k, unsigned int l) const override;
    virtual double GetDeltaCovariance(unsigned int k, unsigned int l) const override;
    virtual double GetDeltaCorrelation(unsigned int k, unsigned int l) const override;
    virtual double GetCrossCovariance(unsigned int k, unsigned int l) const override;
    virtual double GetCrossCorrelation(unsigned int k, unsigned int l) const override;

    virtual void print(std::ostream& os) const override;

    // Access link
    Regression::LinkType& Link() { return L; };
    const Regression::LinkType& Link() const { return L; };

    // Access parameters
    double& Eta() { return m_eta; };
    double& P0() { return m_p0; };
    double& P1() { return m_p1; };
    double& DeltaP0() { return m_dp0; };
    double& DeltaP1() { return m_dp1; };

    const double& Eta() const { return m_eta; };
    const double& P0() const { return m_p0; };
    const double& P1() const { return m_p1; };
    const double& DeltaP0() const { return m_dp0; };
    const double& DeltaP1() const { return m_dp1; };

    // Access Errors
    double& EtaErr() { return m_etaerr; };
    double& P0Err() { return m_p0err; };
    double& P1Err() { return m_p1err; };
    double& DeltaP0Err() { return m_dp0err; };
    double& DeltaP1Err() { return m_dp1err; };

    const double& EtaErr() const { return m_etaerr; };
    const double& P0Err() const { return m_p0err; };
    const double& P1Err() const { return m_p1err; };
    const double& DeltaP0Err() const { return m_dp0err; };
    const double& DeltaP1Err() const { return m_dp1err; };

    // Access Correlations
    double& P0P1Corr() { return m_p0p1corr; };
    double& P0DeltaP0Corr() { return m_p0dp0corr; };
    double& P0DeltaP1Corr() { return m_p0dp1corr; };
    double& P1DeltaP0Corr() { return m_p1dp0corr; };
    double& P1DeltaP1Corr() { return m_p1dp1corr; };
    double& DeltaP0DeltaP1Corr() { return m_dp0dp1corr; };

    const double& P0P1Corr() const { return m_p0p1corr; };
    const double& P0DeltaP0Corr() const { return m_p0dp0corr; };
    const double& P0DeltaP1Corr() const { return m_p0dp1corr; };
    const double& P1DeltaP0Corr() const { return m_p1dp0corr; };
    const double& P1DeltaP1Corr() const { return m_p1dp1corr; };
    const double& DeltaP0DeltaP1Corr() const { return m_dp0dp1corr; };

  private:
    virtual StandardCalibration* doClone() const override {
      return new StandardCalibration(*this);
    };

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Calibration);
     //ar & boost::serialization::base_object<Calibration>(*this);
      ar & BOOST_SERIALIZATION_NVP(L);
      ar & BOOST_SERIALIZATION_NVP(m_eta);
      ar & BOOST_SERIALIZATION_NVP(m_p0);
      ar & BOOST_SERIALIZATION_NVP(m_p1);
      ar & BOOST_SERIALIZATION_NVP(m_dp0);
      ar & BOOST_SERIALIZATION_NVP(m_dp1);
      ar & BOOST_SERIALIZATION_NVP(m_etaerr);
      ar & BOOST_SERIALIZATION_NVP(m_p0err);
      ar & BOOST_SERIALIZATION_NVP(m_p1err);
      ar & BOOST_SERIALIZATION_NVP(m_dp0err);
      ar & BOOST_SERIALIZATION_NVP(m_dp1err);
      ar & BOOST_SERIALIZATION_NVP(m_p0p1corr);
      ar & BOOST_SERIALIZATION_NVP(m_p0dp0corr);
      ar & BOOST_SERIALIZATION_NVP(m_p0dp1corr);
      ar & BOOST_SERIALIZATION_NVP(m_p1dp0corr);
      ar & BOOST_SERIALIZATION_NVP(m_p1dp1corr);
      ar & BOOST_SERIALIZATION_NVP(m_dp0dp1corr);
    }

  private:

    Regression::LinkType L;

    double m_eta;
    double m_p0;
    double m_p1;
    double m_dp0;
    double m_dp1;

    double m_etaerr;
    double m_p0err;
    double m_p1err;
    double m_dp0err;
    double m_dp1err;

    double m_p0p1corr;
    double m_p0dp0corr;
    double m_p0dp1corr;
    double m_p1dp0corr;
    double m_p1dp1corr;
    double m_dp0dp1corr;
  };
}

BOOST_CLASS_EXPORT_KEY(Espresso::StandardCalibration)

#endif


/**
 * @}
 */
