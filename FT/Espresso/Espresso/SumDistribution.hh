/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the SumDistribution class
 */

#ifndef CALIBRATION_SUMDISTRIBUTION
#define CALIBRATION_SUMDISTRIBUTION

#include <memory>

#include "Distribution.hh"

namespace Espresso {

  /**
   * @class SumDistribution
   * @brief A distribution that is a mixture of two other distributions
   */ 
  class SumDistribution : public Distribution {
  public:

    // constructor
    /**
     * Combines two PDFs with the given coefficients.
     * If the coefficients don't sum to unity, they are rescaled.
     *
     * @param[in] _pdf1 First pdf
     * @param[in] _pdf2 Second pdf
     * @param[in] _f1 Coefficient of first pdf
     * @param[in] _f2 Coefficient of second pdf
     */
    SumDistribution(std::unique_ptr<Distribution>&& _pdf1, std::unique_ptr<Distribution>&& _pdf2, double _f1, double _f2);
	
    /// Copy constructor
    SumDistribution(const SumDistribution& rhs);

    /// Move constructor
    SumDistribution(SumDistribution&& rhs);

    // destructor
    virtual ~SumDistribution() override {}

    /**
     * Get the lower bound of the distribution
     *
     * @return either the lower bound or 0.0 if there is none. 
     */
    virtual double GetMin() const override;
    
    /**
     * Get the upper bound of the distribution
     *
     * @return either the upper bound or 0.0 if there is none. 
     */
    virtual double GetMax() const override;

    /**
     * Gets the value of the PDF.
     * 
     * @param[in] x variable value
     * @return pdf(x)
     */
    virtual double GetPDF(double x) const override;

    /**
     * Gets the value of the CDF.
     * 
     * @param[in] x variable value
     * @return cdf(x)
     */
    virtual double GetCDF(double x) const override;

    virtual double GetQuantile(double p) const override;

    /**
     * Calculates the expectation value of the function across this distribution.
     * 
     * @param[in] f function to find expectation of
     * @return the expectation value \f[ \int_{x_\mathrm{min}}^{x_\mathrm{max}} f(x) \mathrm{pdf}(x) \, dx \f]
     */
    virtual double Expectation(const Function& f) const override;

    /**
     * Generates a random number using the inverse transform method
     */
    virtual double GetRandom() const override;

    virtual double GetFourierCosTransform(double omega) const override;
    virtual double GetFourierSinTransform(double omega) const override;

  private:
    virtual SumDistribution* doClone() const override { return new SumDistribution(*this); }

  private:
    std::unique_ptr<Distribution> pdf1;
    std::unique_ptr<Distribution> pdf2;
    double f1;
    double f2;
  };

}

#endif

/**
 * @}
 */
