/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Common statistical functions
 * @details This header file is an interface for GSL integration methods
 * and defines some common useful statistical operations.
 */

#ifndef CALIBRATION_STATISTICS
#define CALIBRATION_STATISTICS

#include <cmath>
#include <tuple>

#include "Matrix.hh"
#include "Distribution.hh"

namespace Espresso {
  
  /**
   * @brief Finds quantile using the Hyndman and Fan type 7 algorithm
   * @details This assumes that the structure has been sorted already by this value,
   * which is a limiting assumption that could be fixed (at some price)
   * @param[in] p Quantile to compute
   * @param[in] table Vector of type/class/struct of type T
   * @param[in] value A rule to compute the target quantity from the type T
   */
  template <class T>
  double quantile(double p, const std::vector<T>& table, std::function<double(const T&)> value) 
  {
    int n = table.size();
    int j = static_cast<int>(floor((n-1)*p+1));
    double xj = value(table[j-1]);
    double xjp1 = value(table[j]);
    double g = (n-1)*p + 1 - j;
    double q = (1-g)*xj + g*xjp1;
    return q;
  }

  /**
   * @brief Finds quantiles using the Hyndman and Fan type 7 algorithm
   * @details This assumes that the structure has been sorted already by this value,
   * which is a limiting assumption that could be fixed (at some price)
   * @param[in] numGroups Number of qunatiles to compute (e.g. 4 for quartiles, 10 for deciles, etc.)
   * @param[in] table Vector of type/class/struct of type T
   * @param[in] value A rule to compute the target quantity from the type T
   */
  template <class T>
  std::vector<double> quantiles(int numGroups, const std::vector<T>& table, std::function<double(const T&)> value) 
  {
    std::vector<double> qs(numGroups+1,0.0);
    for (int group = 0; group <= numGroups; group++) {
      double p = static_cast<double>(group)/numGroups;
      qs[group] = quantile(p,table,value);
    }
    return qs;
  }

  double erfinv(double x);

  Matrix GramSchmidt(const Matrix& covariances);

  /**
   * A tuple of three doubles
   * First is value
   * Second is lower bound
   * Third is upper bound
   */
  using ConfidenceInterval = std::tuple<double,double,double>;

  /** 
   * Calculates the Bayesian confidence interval, returning a tuple
   * whose elements are the fraction, lower bound, and upper bound.
   * @param[in] numPass (Effective) number of events passing cut
   * @param[in] numFail (Effective) number of events failing cut
   * @param[in] conf Percentile confidence interval
   */
  ConfidenceInterval EfficiencyConfidenceInterval(double numPass, double numFail, double conf = 0.682689492137);

}

#endif

/**
 * @}
 */
