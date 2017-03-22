/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the UniformDistribution class
 */

#ifndef CALIBRATION_NUMERICDISTRIBUTION
#define CALIBRATION_NUMERICDISTRIBUTION

#include <iostream>

#include "Function.hh"
#include "Distribution.hh"

namespace Espresso {

  /**
   * @class NumericDistribution
   * @brief A probability distribution class
   * @details This class represents a probability distribution, and contains a pdf and upper/lower bounds as necessary.
   * The cdf is evaluated numerically by default, but an analytic (or at least non-numerical integration) cdf can be specified.
   * It has some checks to make sure that the distribution has unit norm, so you can be somewhat sloppy in passing the pdf,
   * but beware that I haven't tested all of these.
   * Statistical properties and random number generation are done numerically.
   * There are some hack-ish overrides in case the distribution is uniform, gaussian, or exponential,
   * in which case there are much better options than numerical integration.
   */
  class NumericDistribution : public Distribution {

  public:
    
    /**
     * This enumeration defines distribution types
     * by specifying how their range is bounded, if at all.
     */
    enum class Interval {
      BOUNDED,
      UPPER_BOUNDED,
      LOWER_BOUNDED,
      UNBOUNDED
    };  

    // CONSTRUCTORS

    /**
     * Empty constructor
     */
    NumericDistribution();
    
    /**
     * This sets the pdf of the distribution, which is assumed to be unbounded,
     * and whose cdf is computed numerically.
     *
     * @param[in] _pdf the probability density function
     */
    NumericDistribution(const Function& _pdf);

    /**
     * This sets the pdf of the distribution bounded on one side,
     * and whose cdf is computed numerically.
     *
     * @param[in] _pdf the probability density function
     * @param[in] _limit the limiting bound of the distribution
     * @param[in] flipped false for a lower bounded distribution and true for an upper bounded distribution
     */
    NumericDistribution(const Function& _pdf, double _limit, bool flipped = false);

    /**
     * This sets the pdf of the distribution bounded on both sides,
     * and whose cdf is computed numerically.
     *
     * @param[in] _pdf the probability density function
     * @param[in] _min the minimum bound of the distribution
     * @param[in] _max the maximum bound of the distribution
     */
    NumericDistribution(const Function& _pdf, double _min, double _max);

    /**
     * This sets the pdf of the distribution, which is assumed to be unbounded,
     * and also the cdf.
     *
     * @param[in] _pdf the probability density function
     * @param[in] _cdf the cumulative density function
     */
    NumericDistribution(const Function& _pdf, const Function& _cdf);

    /**
     * This sets the pdf of the distribution bounded on one side,
     * and also the cdf.
     *
     * @param[in] _pdf the probability density function
     * @param[in] _cdf the cumulative density function
     * @param[in] _limit the limiting bound of the distribution
     * @param[in] flipped false for a lower bounded distribution and true for an upper bounded distribution
     */
    NumericDistribution(const Function& _pdf, const Function& _cdf, double _limit, bool flipped = false);

    /**
     * This sets the pdf of the distribution bounded on both sides,
     * and also the cdf.
     *
     * @param[in] _pdf the probability density function
     * @param[in] _cdf the cumulative density function
     * @param[in] _min the minimum bound of the distribution
     * @param[in] _max the maximum bound of the distribution
     */
    NumericDistribution(const Function& _pdf, const Function& _cdf, double _min, double _max);

    /// Copy constructor
    NumericDistribution(const NumericDistribution& rhs) 
      : interval(rhs.interval),
        min(rhs.min),
        max(rhs.max),
        pdf(rhs.pdf),
        cdf(rhs.cdf),
        norm(rhs.norm)
    {
      //std::cout << "copying numeric distribution named " << name << " as NumericDistribution" << std::endl;
    }


    /// Move constructor
    NumericDistribution(NumericDistribution&& rhs) 
      : interval(std::move(rhs.interval)),
        min(std::move(rhs.min)),
        max(std::move(rhs.max)),
        pdf(std::move(rhs.pdf)),
        cdf(std::move(rhs.cdf)),
        norm(std::move(rhs.norm))
    {
      //std::cout << "moving numeric distribution as NumericDistribution" << std::endl;
    }

    virtual double GetMin() const override;
    virtual double GetMax() const override;
    virtual double GetPDF(double x) const override;
    virtual double GetCDF(double x) const override;
    virtual double GetQuantile(double p) const override;
    virtual double Expectation(const Function& f) const override;
    virtual double GetRandom() const override;

    virtual double GetFourierCosTransform(double omega) const override;
    virtual double GetFourierSinTransform(double omega) const override;

    double GetCentral() const;

    void SetName(std::string _name) { name = _name; };

  private:
    virtual NumericDistribution* doClone() const override { return new NumericDistribution(*this); }

  private:
    
    NumericDistribution::Interval interval;
    double min;
    double max;

    Function pdf;
    Function cdf;
    double norm;

    std::string name = "default";
  };

}

#endif

/**
 * @}
 */
