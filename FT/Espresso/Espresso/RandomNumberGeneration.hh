/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Interface for STL random number generation
 */

#ifndef CALIBRATION_RANDOMNUMBERGENERATION
#define CALIBRATION_RANDOMNUMBERGENERATION

#include <random>

#include "Distribution.hh"

namespace Espresso {

  namespace RandomNumberGeneration {

    /**
     * (Re)sets the RNG seed so that results are reproducible.
     * @param[in] _seed The new uint seed
     */
    void SetSeed(unsigned int _seed);

    /**
     * Uniform random number generator
     *
     * @return a random number from the range [0,1]
     */
    double Get();
  
    /**
     * Uniform random integer type argument
     * @param[in] min minimum
     * @param[in] max maximum
     * @return a random integer from the range [min,max]
     */
    template <typename T>
    T GetInteger(T min, T max);

    /**
     * Uniform random number generator
     *
     * @param[in] min minimum
     * @param[in] max maximum
     * @return a random number from the range [min,max]
     */
    double GetUniform(double min, double max);
  
    /**
     * Gaussian random number generator with pdf
     * \f[ \mathrm{pdf}(x) = \frac{1}{\sqrt{2 \pi}} \exp \left( - \frac{1}{2} x^2 \right) \f]
     *
     * @return a random number with mean 0 and standard deviation 1
   
     */
    double GetNorm();
  
    /**
     * Gaussian random number generator with pdf
     * \f[ \mathrm{pdf}(x) = \frac{1}{\sigma \sqrt{2 \pi}} \exp \left( - \frac{1}{2} \left[ \frac{x-\mu}{\sigma} \right]^2 \right) \f]
     *
     * @param[in] mu the mean of the distribution
     * @param[in] sigma the width of the distribution
     */
    double GetNorm(double mu, double sigma);
  
    /**
     * Exponential random number generator with pdf
     * \f[ pdf(t < t_{min}) = 0, \quad pdf(t > t_{min}) = \frac{1}{\tau} \exp \left( - \frac{t-t_{min}}{\tau} \right) \f] 
     *
     * @param[in] min the minimum t<sub>min</sub> of the distribution
     * @param[in] fall the decay rate &tau; of the distribution
     */
    double GetExpo(double min, double fall);
  
    /**
     * @brief Random number generator that samples a number from the given distribution.
     * @details This is done numerically with the inverse transform method, by generating a
     * random number u between 0 and 1 and solving for u = cdf(x).
     *
     * @param[in] pdf distribution of random number
     */
    double Get(Distribution &pdf);
  
    /**
     * @brief Get a random iterator in a container
     * @param[in] begin Starting iterator
     * @param[in] end End iterator
     */
    template <typename T>
    T GetRandomIterator(T begin, T end) {
      const unsigned long n = std::distance(begin,end);
      unsigned long k;
      do {
	k = n*Get();
      } while (k >= n);
      std::advance(begin,k);
      return begin;
    }

  }

}

#endif

  /**
   * @}
   */
