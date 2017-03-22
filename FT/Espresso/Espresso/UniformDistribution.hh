/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the UniformDistribution class
 */

#ifndef ESPRESSO_UNIFORMDISTRIBUTION_HH 
#define ESPRESSO_UNIFORMDISTRIBUTION_HH 1

// Include files
#include "Distribution.hh"

namespace Espresso 
{
  
  /**
   * @class UniformDistribution
   * @brief Class representing uniform distribution class
   */
  class UniformDistribution : public Distribution {
  public: 
    
    // constructors
    
    /**
     * @brief Creates uniform distribution with specified minimum and maximum
     * @param[in] _min minimum
     * @param[in] _max maximum
     */
    UniformDistribution(double _min, double _max);
    
    /// Copy constructor
    UniformDistribution(const UniformDistribution& rhs);

    /// Move constructor
    UniformDistribution(UniformDistribution&& rhs);

    virtual ~UniformDistribution() override {};
    
    virtual double GetMin() const override { return min; };
    virtual double GetMax() const override { return max; };
    virtual double GetPDF(double x) const override;
    virtual double GetCDF(double x) const override;
    virtual double GetQuantile(double p) const override;
    virtual double Expectation(const Function& f) const override;
    double GetRandom() const override;
    virtual double GetFourierCosTransform(double omega) const override;
    virtual double GetFourierSinTransform(double omega) const override;
    
  private:
    virtual UniformDistribution* doClone() const override { return new UniformDistribution(*this); }

  private:
    double min;
    double max;

  };

}

#endif // ESPRESSO_UNIFORMDISTRIBUTION_HH
  

/**
 * @}
 */
