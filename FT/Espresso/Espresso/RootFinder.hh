/**
 * @addtogroup gr_espresso
 * @{
 */
/**

 * @file
 * @brief RootFinder.hh describes the class Espresso::RootFinder, as well as some of the 
 * types (typedefs, structs, and enums) that support it.
 */
#ifndef CALIBRATION_ROOTFINDER
#define CALIBRATION_ROOTFINDER

#include <functional>
#include <gsl/gsl_roots.h>

namespace Espresso {

  /**
   * @brief A function from the set of calibration parameters to a FDF.
   */
  using FDF = std::function< void(double x, double* f, double* df) >;

  /**
   * @brief This enum specifies the GSL solution strategy to be used for a scalar problem.
   * @details The various stratgies are described by GSL at https://www.gnu.org/software/gsl/manual/html_node/Root-Finding-Algorithms-using-Derivatives.html
   * and https://www.gnu.org/software/gsl/manual/html_node/Algorithms-using-Derivatives.html.
   */
  enum class SolutionMethod {
    Newton ///< gsl_root_fdfsolver_newton
    , Secant ///< gsl_root_fdfsolver_secant
    , Steffenson ///< gsl_root_fdfsolver_steffenson
  };

  /**
   * @class RootFinder
   * @brief This class is a C++ wrapper around GSL root finding methods.
   */
  class RootFinder {
  public:
    
    // Constructors

    /**
     * @brief Standard constructor
     * @details This sets the number of dimensions of the function and the GSL algorithm to use,
     * and the class takes care of wheter to use gsl_root_fdf... or gsl_multiroot_fdf..., etc.
     * @param[in] funjac The FDF function and derivative object
     * @param[in] method The GSL root-finding algorithm to be used, which is Newton's method by default.
     */
    RootFinder(const FDF& funjac, SolutionMethod method = SolutionMethod::Newton);

    /// Destructor
    ~RootFinder();

    /**
     * @brief Returns the name of the GSL root-finding algorithm.
     */
    std::string AlgorithmName();

    /**
     * @brief Sets starting point for root finding.
     * @param[in] guess Starting value of parameter.
     */
    void SetInitialGuess(double guess);

    /**
     * Performs the appropriate GSL root-finding algorithm.
     * Returns GSL status code.
     * These are part of a C-style unnamed enum:
     enum  { 
     GSL_SUCCESS = 0, GSL_FAILURE = -1, GSL_CONTINUE = -2, GSL_EDOM = 1, 
     GSL_ERANGE = 2, GSL_EFAULT = 3, GSL_EINVAL = 4, GSL_EFAILED = 5, 
     GSL_EFACTOR = 6, GSL_ESANITY = 7, GSL_ENOMEM = 8, GSL_EBADFUNC = 9, 
     GSL_ERUNAWAY = 10, GSL_EMAXITER = 11, GSL_EZERODIV = 12, GSL_EBADTOL = 13, 
     GSL_ETOL = 14, GSL_EUNDRFLW = 15, GSL_EOVRFLW = 16, GSL_ELOSS = 17, 
     GSL_EROUND = 18, GSL_EBADLEN = 19, GSL_ENOTSQR = 20, GSL_ESING = 21, 
     GSL_EDIVERGE = 22, GSL_EUNSUP = 23, GSL_EUNIMPL = 24, GSL_ECACHE = 25, 
     GSL_ETABLE = 26, GSL_ENOPROG = 27, GSL_ENOPROGJ = 28, GSL_ETOLF = 29, 
     GSL_ETOLX = 30, GSL_ETOLG = 31, GSL_EOF = 32 
     }
     * Making an equivalent C++ named enum would be nice!
     */
    int Solve();

    /**
     * Returns the vector of values from the GSL solution.
     */
    double GetSolution();

  private:

    const gsl_root_fdfsolver_type* type;
    gsl_root_fdfsolver* solver;
    gsl_function_fdf fdf;
    double value;

  };

}

#endif

/**
 * @}
 */
