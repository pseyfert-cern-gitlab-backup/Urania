/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the ExponentialDistribution class.
 */

#ifndef ESPRESSO_EXPONENTIALDISTRIBUTION_HH 
#define ESPRESSO_EXPONENTIALDISTRIBUTION_HH 1

// Include files
#include "Distribution.hh"

namespace Espresso 
{
  
  /**
   * @class ExponentialDistribution
   * @brief Class representing exponential distribution
   */
  class ExponentialDistribution : public Distribution {
  public: 
    /**
     * @brief Creates an exponential distribution with the specified minimum and decay rate
     * @param[in] _min the minimum t<sub>min</sub> of the distribution
     * @param[in] _fall the decay rate &tau; of the distribution
     */
    ExponentialDistribution(double _min, double _fall);

    /// Copy constructor
    ExponentialDistribution(const ExponentialDistribution& rhs);

    /// Move constructor
    ExponentialDistribution(ExponentialDistribution&& rhs);

    virtual ~ExponentialDistribution() override {};
    
    virtual double GetMin() const override { return min; };
    virtual double GetMax() const override { return 0.0; };
    virtual double GetPDF(double x) const override;
    virtual double GetCDF(double x) const override;
    virtual double GetQuantile(double p) const override;
    virtual double Expectation(const Function& f) const override;
    virtual double GetRandom() const override;
    virtual double GetFourierCosTransform(double omega) const override;
    virtual double GetFourierSinTransform(double omega) const override;
    
  private:
    virtual ExponentialDistribution* doClone() const override { return new ExponentialDistribution(*this); }

  private:
    double min;
    double fall;
  };

}
#endif // ESPRESSO_EXPONENTIALDISTRIBUTION_HH
  

/**
 * @}
 */
