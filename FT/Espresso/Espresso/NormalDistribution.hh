/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the NormalDistribution class
 */

#ifndef ESPRESSO_NORMALDISTRIBUTION_HH 
#define ESPRESSO_NORMALDISTRIBUTION_HH 1

#include "Distribution.hh"

namespace Espresso {
  
  /**
   * @class NormalDistribution
   * @brief Class representing normal distribution
   */
  class NormalDistribution : public Distribution {
  public:

    // constructors

    /**
     * @brief Creates normal distribution with specified mean and width
     * @param[in] _mu the mean of the distribution
     * @param[in] _sigma the width of the distribution
     */
    NormalDistribution(double _mu, double _sigma);

    /// Copy constructor
    NormalDistribution(const NormalDistribution& rhs);

    /// Move constructor
    NormalDistribution(NormalDistribution&& rhs);

    virtual ~NormalDistribution() override {};

    virtual double GetMin() const override { return 0.0; };
    virtual double GetMax() const override { return 0.0; };
    virtual double GetPDF(double x) const override;
    virtual double GetCDF(double x) const override;
    virtual double GetQuantile(double p) const override;
    virtual double Expectation(const Function& f) const override;
    virtual double GetRandom() const override;
    virtual double GetFourierCosTransform(double omega) const override;
    virtual double GetFourierSinTransform(double omega) const override;

  private:
    virtual NormalDistribution* doClone() const override { return new NormalDistribution(*this); }

  private:
    double mu;
    double sigma;
  };

}

#endif // ESPRESSO_NORMALDISTRIBUTION_HH

/**
 * @}
 */
