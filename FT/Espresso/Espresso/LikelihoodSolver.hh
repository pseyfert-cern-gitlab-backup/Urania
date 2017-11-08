/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the LikelihoodSolver class.
 */

#ifndef CALIBRATION_LIKELIHOODSOLVER
#define CALIBRATION_LIKELIHOODSOLVER

#include "Math/IFunction.h"

#include "Solver.hh"
#include "CalibrationFunction.hh"
#include "TaggingResult.hh"
#include "TaggingLikelihood.hh"
#include "MultiRootFinder.hh"

namespace Espresso {

  /**
   * @class LikelihoodSolver
   * @brief Implementation of Solver that maximizes the tagging likelihood using GSL
   */
  class LikelihoodSolver : public Solver {
  public:
    
    /**
     * @brief Standard constructor creating object that will maximize the likelihood
     * using GSL's root finding tools.
     * @param[in] _lf The likelihood object to be maximized
     * @param[in] _method The MultiSolution to be used; HybridSJ seems to be the fastest and is the default
     */
    LikelihoodSolver(const TaggingLikelihood& _lf, MultiSolutionMethod _method = MultiSolutionMethod::HybridSJ);

    virtual double Solve() override;

    virtual void SetVals(const double* vals) override;
    virtual void SetVals(const std::vector<double>& vals) override;
    virtual void SetVals(const Vector& vals) override;

    virtual void GetVals(double* vals) override;
    virtual void GetVals(std::vector<double>& vals) override;
    virtual Vector GetVals() override;

    virtual Matrix GetCovariance() override;

    void SetVerbose(bool _verbose) { verbose = _verbose; }

  private:
    TaggingLikelihood likelihoodFunction;
    MultiSolutionMethod method;
    Vector average;
    Matrix covariance;
    bool verbose;
  };

}

#endif

/**
 * @}
 */
