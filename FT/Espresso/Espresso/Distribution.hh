/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the abstract Distribution class.
 */

#ifndef CALIBRATION_DISTRIBUTION
#define CALIBRATION_DISTRIBUTION

#include <iostream>
#include <vector>
#include <memory>

#include "Function.hh"

namespace Espresso {

  /**
   * @class Distribution
   * @brief Virtual interface for distribution classes
   */
  class Distribution {

  public:
    
    /// Trivial destructor
    virtual ~Distribution() {}

    /**
     * @brief Get the lower bound of the distribution
     * @return either the lower bound or 0.0 if there is none. 
     */
    virtual double GetMin() const = 0;
    
    /**
     * @brief Get the upper bound of the distribution
     * @return either the upper bound or 0.0 if there is none. 
     */
    virtual double GetMax() const = 0;

    /**
     * @brief Gets the value of the PDF at this point.
     * @param[in] x variable value
     * @return pdf(x)
     */
    virtual double GetPDF(double x) const = 0;

    /**
     * @brief Gets the value of the CDF.
     * @param[in] x variable value
     * @return cdf(x)
     */
    virtual double GetCDF(double x) const = 0;

    /**
     * @brief Gets the quantile of the given probability,
     * e.g. the inverse of the CDF.
     * @param[in] x variable value
     * @return cdf(x)
     */
    virtual double GetQuantile(double p) const = 0;
    
    virtual std::vector<double> GetQuantiles(int numGroups) const {
      std::vector<double> qs(numGroups+1,0.0);
      for (int group = 0; group <= numGroups; group++) {
	double p = static_cast<double>(group)/numGroups;
	qs[group] = GetQuantile(p);
      }
      return qs;
    };
    
    /**
     * @brief Calculates the expectation value of the function across this distribution.
     * @param[in] f function to find expectation of
     * @return the expectation value E[f(x)]
     */
    virtual double Expectation(const Function& f) const = 0;

    /**
     * @brief Samples a random number from the distribution
     */
    virtual double GetRandom() const = 0;

    /**
     * @brief Returns Fourier cos transform of distribution
     * @param[in] omega Fourier frequency &omega;
     * @return E[cos(&omega;t)]
     */
    virtual double GetFourierCosTransform(double omega) const = 0;

    /**
     * Returns Fourier sin transform of distribution
     *
     * @param[in] omega Fourier frequency &omega;
     * @return E[sin(&omega;t)]
     */
    virtual double GetFourierSinTransform(double omega) const = 0;

    std::unique_ptr<Distribution> clone() { return std::unique_ptr<Distribution>(doClone()); } 

  private:
    virtual Distribution* doClone() const = 0;

  };

}


#endif

/**
 * @}
 */
