/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the abstract CalibrationFunction class.
 */

#ifndef ESPRESSO_CALIBRATIONFUNCTION_HH
#define ESPRESSO_CALIBRATIONFUNCTION_HH 1

// Include files
#include <memory>

#include "Vector.hh"

namespace Espresso {

  /**
   * @class CalibrationFunction
   * @brief Generic interface for a calibration function
   * @details Interface for a calibration function &omega;(&eta;).
   * This implements the form of the calibration function, while
   * the calibration parameters themselves must be passed in.
   * This is useful for the likelihood minimization feature.
   * The likelihood function is restricted to the class of GLM models,
   * which is not a big loss - this includes polynomial fits and
   * b-spline basis fits with any choice of link function.
   * Provides methods to return the calibrated value and derivative
   * w.r.t. the calibration parameters.
   */
  class CalibrationFunction {
  public:

    /// Trivial destructor
    virtual ~CalibrationFunction() {};

    /**
     * @brief Number of parameters in the calibration
     */
    virtual unsigned int NumParams() const = 0;

    /**
     * @brief Calibrated value &omega;(&eta;).
     * @param[in] eta Uncalibrated probability
     * @param[in] theta Calibration parameters
     * @return Calibrated probability &omega;
     */
    virtual double Value(double eta, const double* theta) const = 0;

    /**
     * @brief Returns one component of derivative of calibrated value
     * @param[in] eta Uncalibrated probability
     * @param[in] k Index of calibration parameter being differentiated by
     * @param[in] theta Calibration parameters
     * @return d&omega;(&eta;,&theta;<sub>i</sub>)/d&theta;<sub>k</sub>
     */
    virtual double Derivative(double eta, unsigned int k, const double* theta) const = 0;

    /**
     * @brief Returns full derivative of calibrated value
     * @param[in] eta Uncalibrated probability
     * @param[in] theta Calibration parameters
     * @return Vector d&omega;(&eta;,&theta;<sub>i</sub>)/d&theta;<sub>i</sub>
     */
    virtual Vector Derivative(double eta, const double* theta) const = 0;

    /// Print to an std::ostream
    virtual void print(std::ostream& os) const = 0;

    /// Uses virtual function CalibrationFunction::print to overload CalibrationFunction::operator<<
    friend std::ostream& operator<< (std::ostream& os, const CalibrationFunction& func) {
      func.print(os);
      return os;
    }

    /// Clones the function, returning a smart pointer
    std::unique_ptr<CalibrationFunction> clone() const { return std::unique_ptr<CalibrationFunction>(doClone()); }

  private:
    virtual CalibrationFunction* doClone() const = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {}
  };

}

#endif // ESPRESSO_CALIBRATIONFUNCTION_HH

/**
 * @}
 */
