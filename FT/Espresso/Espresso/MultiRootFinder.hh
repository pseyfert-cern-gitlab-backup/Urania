/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * 
 * MultiRootFinder.hh describes the class Espresso::MultiRootFinder, as well as some of the 
 * types (typedefs, structs, and enums) that support it.
 */

#ifndef CALIBRATION_MULTIROOTFINDER
#define CALIBRATION_MULTIROOTFINDER

#include <functional>
#include <gsl/gsl_multiroots.h>

#include "Vector.hh"
#include "Matrix.hh"

namespace Espresso {

  /**
   * @brief A function taking a set of values (theta) and setting a vector function (f) and
   * its matrix derivative (df).
   */
  using MultiFDF = std::function< void(const double* theta, Vector* f, Matrix* df) >;

  /**
   * @brief This enum specifies the GSL solution strategy to be used for a vector problem.
   * @details The various stratgies are described by GSL at https://www.gnu.org/software/gsl/manual/html_node/Root-Finding-Algorithms-using-Derivatives.html
   * and https://www.gnu.org/software/gsl/manual/html_node/Algorithms-using-Derivatives.html.
   */
  enum class MultiSolutionMethod {
    Newton ///< gsl_multiroot_fdfsolver_newton
    , GNewton ///<  gsl_multiroot_fdfsolver_gnewton
    , HybridSJ ///< gsl_multiroot_fdfsolver_hybridsj
    , HybridJ ///< gsl_multiroot_fdfsolver_hybridj
  };
  
  /**
   * @class MultiRootFinder
   * @brief A root finding class 
   *
   * This class is a C++ wrapper around GSL root finding methods.
   */
  class MultiRootFinder {
  public:
    
    /**
     * This sets the number of dimensions of the function and the GSL algorithm to use,
     * and the class takes care of wheter to use gsl_root_fdf... or gsl_multiroot_fdf..., etc.
     *
     * @param[in] num The number of dimensions of the function
     * @param[in] funjac The MultiFDF function and derivative object
     * @param[in] method The GSL multiroot-finding algorithm to be used, which is Newton's method by default.
     */
    MultiRootFinder(std::size_t num, const MultiFDF& funjac, MultiSolutionMethod method = MultiSolutionMethod::Newton);

    /// destructor
    ~MultiRootFinder();

    /**
     * Returns the name of the GSL root-finding algorithm.
     * @return the name of the algorithm as a C++ string
     */
    std::string AlgorithmName();

    /**
     * Starting point for root finding.
     *
     * @param[in] guess Stamrting values of parameters.
     */
    void SetInitialGuess(const Vector& guess);

    /**
     * Performs the appropriate GSL root-finding algorithm.
     */
    int Solve();

    /**
     * Retrieve GSL solution.
     * @return Vector of values
     */
    Vector GetSolution();

  private:
    struct multi_params {
      std::size_t num;
      const MultiFDF& func;//void* func;
    };

  private:
    std::size_t num;

    const gsl_multiroot_fdfsolver_type* multi_type;
    gsl_multiroot_fdfsolver* multi_solver;
    gsl_multiroot_function_fdf fdf;
    gsl_vector* multi_values;
  };

}

#endif

/**
 * @}
 */
