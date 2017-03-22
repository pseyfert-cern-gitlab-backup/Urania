/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header defines the abstract Calibration class.
 */

#ifndef ESPRESSO_CALIBRATION_HH
#define ESPRESSO_CALIBRATION_HH 1

// Include files
#include <iomanip>

#include "Tagging.hh"
#include "Statistics.hh"

namespace Espresso {

  // Forward declarations
  class Vector;
  class Matrix;

  /**
   * @class Calibration
   * @brief Abstract interface for objects that apply calibrations to tagging decisions.
   * @details A calibration model includes a number of parameters, asymmetry parameters, and their covariances.
   * This abstract interface represents a class that stores these values and implements the calibration functions &omega;(&eta;) and the true flavor-dependent calibration &omega;(&eta;,d').
   */
  class Calibration {
  public:

    /// Virtual destructor
    virtual ~Calibration() {};

    /**
     * @brief Computes &omega;(&eta;) ignoring the delta parameters.
     * @param[in] eta Uncalibrated value &eta; to be calibrated
     * @return The calibrated value &omega;
     */
    virtual double Value(double eta) const = 0;

    /**
     * @brief Computes &omega;(&eta;) averaged over the delta parameters.
     * @param[in] eta Uncalibrated value &eta; to be calibrated
     * @param[in] sigmaConf Width of confidence interval on either side, in units of &sigma;.
     * @return A confidence interval for the predicted probability
     */
    virtual ConfidenceInterval ValueRange(double eta, int sigmaConf) const = 0;

    /**
     * @brief Computes &omega;(&eta;) given a particular B flavor
     * @details This uses the tagging asymmetry parameters to correct &omega;
     * based on the B flavor.
     * @param[in] eta Uncalibrated value &eta; to be calibrated
     * @param[in] flavour The flavour (Flavour::Pos or Flavour::Neg) of the meson
     * @return The calibrated value &omega; factoring in the B flavor
     */
    virtual double Value(double eta, Flavour flavour) const = 0;

    /**
     * @brief Shortcut to Calibration::Value.
     */
    virtual double operator() (double eta) const { return Value(eta); };

    /**
     * @brief Computes d&omega;(&eta;,&theta;<sub>i</sub>)/d&theta;<sub>i</sub> averaged over the delta parameters.
     * @details The derivatives w.r.t. the delta parameters are ignored, and thus
     * the length of the vector is Calibration::NumParams().
     * @param[in] eta Value of &eta; at which to evaluate the gradient
     * @return The gradient of &omega;(&eta;,&theta;<sub>i</sub>) at the nominal calibration parameters
     */
    virtual Vector Derivative(double eta) const = 0;

    /**
     * @brief Computes d&omega;(&eta;,&theta;<sub>i</sub>)/d&theta;<sub>i</sub> given a particular B flavor
     * @details The derivatives w.r.t. the delta parameters are included, and thus the
     * length of the vector is twice Calibration::NumParams().
     * @param[in] eta Value of &eta; at which to evaluate the gradient
     * @param[in] flavour The flavour (Flavour::Pos or Flavour::Neg) of the meson
     * @return The gradient of &omega;(&eta;,&theta;<sub>i</sub>) at the nominal calibration parameters
     */
    virtual Vector Derivative(double eta, Flavour flavour) const = 0;

    /**
     * @brief Returns an "offset" value in the GLM sense
     * @details For example, this would be g<sub>0</sub> in the expansion
     * g(&omega;) = g<sub>0</sub> + &theta;<sub>i</sub> b(&eta;)<sup>i</sup>.
     * Usually the offset is g<sub>0</sub> = g(&eta;).
     *
     * @param[in] eta Value of &eta; at which to evaluate the gradient
     * @return Offset value; or simply &omega; (the default) if the calibration model isn't GLM
     */
    virtual double GetOffset(double eta) const { return Value(eta); }

    /**
     * @brief Returns GLM basis vector, if possible
     * @details Returns a vector of basis elements in the GLM sense, e.g. b(&eta;)<sup>i</sup> in the expansion
     * g(&omega;) = g<sub>0</sub> + &theta;<sub>i</sub> b(&eta;)<sup>i</sup>.
     * @param[in] eta Value of &eta; at which to evaluate the basis functions
     * @return GLM basis vector; or an empty vector if the calibration model isn't GLM
     */
    virtual Vector GetBasis(double eta) const = 0;

    /**
     * @brief Returns the number of parameters of the model
     * @details This does not count the delta parameters,
     * which doubles the total count.
     */
    virtual unsigned int NumParams() const = 0;

    /// Returns Vector of calibration parameters
    virtual Vector GetCoeffs() const = 0;

    /// Returns Vector of calibration delta parameters
    virtual Vector GetDeltaCoeffs() const = 0;

    /// Returns covariance matrix of calibration (non-delta) parameters
    virtual Matrix GetCovarianceMatrix() const = 0;

    /// Returns covariance matrix of calibration delta parameters
    virtual Matrix GetDeltaCovarianceMatrix() const = 0;

    /// Returns covariance matrix of calibration non-delta parameters with delta parameters
    virtual Matrix GetCrossCovarianceMatrix() const = 0;

    /**
     * @brief Returns the corresponding calibration (non-delta) parameter
     * @param[in] k index of parameter to return
     * @return &theta;<sub>k</sub>
     */
    virtual double GetCoeff(unsigned int k) const = 0;

    /**
     * @brief Returns uncertainty on the corresponding calibration (non-delta) parameter
     * @param[in] k index of parameter
     * @return &sigma;[&theta;<sub>k</sub>]
     */
    virtual double GetError(unsigned int k) const = 0;

    /**
     * @brief Returns the corresponding calibration delta parameter
     * @param[in] k index of parameter to return
     * @return &Delta;&theta;<sub>k</sub>
     */
    virtual double GetDeltaCoeff(unsigned int k) const = 0;

    /**
     * @brief Returns uncertainty on the corresponding calibration delta parameter
     * @param[in] k index of parameter
     * @return &sigma;[&Delta;&theta;<sub>k</sub>]
     */
    virtual double GetDeltaError(unsigned int k) const = 0;

    /**
     * @brief Returns the covariance between two (non-delta) parameters
     * @param[in] k index of first parameter
     * @param[in] l index of second parameter
     * @return Cov[&theta;<sub>k</sub>,&theta;<sub>l</sub>]
     */
    virtual double GetCovariance(unsigned int k, unsigned int l) const = 0;

    /**
     * @brief Returns the correlation between two (non-delta) parameters
     * @param[in] k index of first parameter
     * @param[in] l index of second parameter
     * @return Corr[&theta;<sub>k</sub>,&theta;<sub>l</sub>]
     */
    virtual double GetCorrelation(unsigned int k, unsigned int l) const = 0;

    /**
     * @brief Returns the covariance between two delta parameters
     * @param[in] k index of first parameter
     * @param[in] l index of second parameter
     * @return Cov[&Delta;&theta;<sub>k</sub>,&Delta;&theta;<sub>l</sub>]
     */
    virtual double GetDeltaCovariance(unsigned int k, unsigned int l) const = 0;

    /**
     * @brief Returns the correlation between two delta parameters
     * @param[in] k index of first parameter
     * @param[in] l index of second parameter
     * @return Corr[&Delta;&theta;<sub>k</sub>,&Delta;&theta;<sub>l</sub>]
     */
    virtual double GetDeltaCorrelation(unsigned int k, unsigned int l) const = 0;

    /**
     * @brief Returns the covariance between a non-delta and a delta parameters
     * @param[in] k index of non-delta parameter
     * @param[in] l index of delta parameter
     * @return Cov[&theta;<sub>k</sub>,&Delta;&theta;<sub>l</sub>]
     */
    virtual double GetCrossCovariance(unsigned int k, unsigned int l) const = 0;

    /**
     * @brief Returns the correlation between a non-delta and a delta parameters
     * @param[in] k index of non-delta parameter
     * @param[in] l index of delta parameter
     * @return Corr[&theta;<sub>k</sub>,&Delta;&theta;<sub>l</sub>]
     */
    virtual double GetCrossCorrelation(unsigned int k, unsigned int l) const = 0;

    /// Print to an std::ostream
    virtual void print(std::ostream& os) const;

    /// Uses virtual function Calibration::print to overload Calibration::operator<<
    friend std::ostream& operator<< (std::ostream& os, const Calibration& cal);

    /// Clones the function, returning a smart pointer
    std::unique_ptr<Calibration> clone() const { return std::unique_ptr<Calibration>(doClone()); }

  private:
    virtual Calibration* doClone() const = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {}
  };
}

#endif // ESPRESSO_CALIBRATION_HH

/**
 * @}
 */
