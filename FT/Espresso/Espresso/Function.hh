/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines a Function type and is an interface for GSL integration methods.
 */

#ifndef CALIBRATION_FUNCTION
#define CALIBRATION_FUNCTION

#include <functional>

namespace Espresso {

  /**
   * Shorthand for a scalar (double) std::function,
   * which can be easily created in C++11 as a lambda function.
   */
  using Function = std::function<double(double)>;

  /**
   * Integrates a function from -&infin; to &infin; via gsl_integration_qagi.
   *
   * @param[in] f function to integrate
   */
  double Integrate(Function f);

  /**
   * Integrates a function within some bounds via gsl_integration_qag.
   *
   * @param[in] f function to integrate
   * @param[in] min minimum of integration region
   * @param[in] max maximum of integration region
   */
  double Integrate(Function f, double min, double max);

  /**
   * Integrates a function from some lower bound to &infin; via gsl_integration_qagiu.
   *
   * @param[in] f function to integrate
   * @param[in] min minimum of integration region
   */
  double IntegrateAbove(Function f, double min);

  /**
   * Integrates a function from -&infin; to some upper bound via gsl_integration_qagil.
   *
   * @param[in] f function to integrate
   * @param[in] max maximum of integration region
   */
  double IntegrateBelow(Function f, double max);

}

#endif

/**
 * @}
 */

