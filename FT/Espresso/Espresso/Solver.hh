/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * This header time defines the abstract Solver class.
 */

#ifndef CALIBRATION_SOLVER
#define CALIBRATION_SOLVER

#include "Vector.hh"
#include "Matrix.hh"

namespace Espresso {

  /**
   * @class Solver
   * @brief This class is an interface for a an algorithm that estimates a vector of values and a covariance matrix.
   */
  class Solver {
  public:
    
    /** 
     * @brief Solves for the calibration parameters, which are stored internally.
     * @return A figure of merit for the solution
     */
    virtual double Solve() = 0;

    /**
     * @brief Sets the initial calibration parameters before root finding.
     * @param[in] vals C array of parameters to used
     */
    virtual void SetVals(const double* vals) = 0;

    /**
     * @brief Sets the initial calibration parameters before root finding.
     * @param[in] vals C++ vector of parameters to used
     */
    virtual void SetVals(const std::vector<double>& vals) = 0;

    /**
     * @brief Sets the initial calibration parameters before root finding.
     * @param[in] vals Vector of parameters to used
     */
    virtual void SetVals(const Vector& vals) = 0;

    /**
     * @brief Retrieves the calibration parameters.
     * @param[out] vals C array to write parameters to
     */
    virtual void GetVals(double* vals) = 0;

    /**
     * @brief Retrieves the calibration parameters.
     * @param[out] vals C++ vector to write parameters to
     */
    virtual void GetVals(std::vector<double>& vals) = 0;

    /**
     * @brief Returns the calibration parameters.
     * @return Vector containing parameters
     */
    virtual Vector GetVals() = 0;

    /**
     * @brief Returns the empirical covariance matrix estimated by the solution procedure.
     * @return covariance matrix
     */
    virtual Matrix GetCovariance() = 0;

  };

}

#endif

/**
 * @}
 */
