/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the DiracDeltaDistribution class.
 */

#ifndef ESPRESSO_DIRACDELTADISTRIBUTION_HH 
#define ESPRESSO_DIRACDELTADISTRIBUTION_HH 1

#include <cmath>
#include <limits>

#include "Distribution.hh"

namespace Espresso {
  
  /**
   * @class DiracDeltaDistribution
   * @brief Trivial distribution for a constant variable.
   */
  class DiracDeltaDistribution : public Distribution {
  public:

    // constructors

    /**
     * @brief Constructor
     * @details Constructs dirac delta distribution &delta;(x-x<sub>0</sub>).
     * @param[in] _val Single value x<sub>0</sub> where distribution is supported
     */
    DiracDeltaDistribution(const double &_val) : val(_val) {}

    /// Copy constructor
    DiracDeltaDistribution(const DiracDeltaDistribution& rhs) : val(rhs.val) {}

    /// Move constructor
    DiracDeltaDistribution(DiracDeltaDistribution&& rhs) : val(std::move(rhs.val)) {}

    virtual ~DiracDeltaDistribution() override {};

    /**
     * @brief Get the lower bound of the distribution
     * @details For the dirac distribution, the minimum and
     * maximum supported values are both x<sub>0</sub>.
     * @return x<sub>0</sub>
     */
    virtual double GetMin() const override { return val; };

    /**
     * @brief Get the upper bound of the distribution
     * @details For the dirac distribution, the minimum and
     * maximum supported values are both x<sub>0</sub>.
     * @return x<sub>0</sub>
     */
    virtual double GetMax() const override { return val; };
    
    /**
     * @brief Gets the value of the PDF at this point.
     * @details Of course the value of the delta function is infinite,
     * so this returns NaN.
     * @param[in] x variable value
     * @return either 0 or NaN
     */
    virtual double GetPDF(double x) const override { return (x == val) ? std::numeric_limits<double>::quiet_NaN() : 0.0; };

    /**
     * @brief Gets the value of the CDF.
     * @param[in] x variable value
     * @return x &ge; x<sub>0</sub>
     */
    virtual double GetCDF(double x) const override { return (x >= val) ? 1.0 : 0.0; };

    virtual double GetQuantile(double p) const override { return val; };

    /**
     * @brief Calculates the expectation value of the function across this distribution.
     * @param[in] f function to find expectation of
     * @return f(x<sub>0</sub>)
     */
    virtual double Expectation(const Function& f) const override { return f(val); };

    /**
     * @brief Samples a random number from the distribution
     * @details A random number from the Dirac delta distribution is trivial.
     */
    virtual double GetRandom() const override { return val; };

    /**
     * @brief Returns Fourier cosine transform of distribution
     * @param[in] omega Fourier frequency &omega;
     . @return cos(&omega;x<sub>0</sub>)
     */
    virtual double GetFourierCosTransform(double omega) const override { return cos(omega*val); };

    /**
     * @brief Returns Fourier sine transform of distribution
     * @param[in] omega Fourier frequency &omega;
     . @return sin(&omega;x<sub>0</sub>)
     */
    virtual double GetFourierSinTransform(double omega) const override { return sin(omega*val); };

  private:
    virtual DiracDeltaDistribution* doClone() const override { return new DiracDeltaDistribution(*this); }

  private:
    double val;

  };

}

#endif // ESPRESSO_DIRACDELTADISTRIBUTION_HH


/**
 * @}
 */
