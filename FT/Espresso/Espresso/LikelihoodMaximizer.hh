/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the LikelihoodMaximizer class.
 */

#ifndef CALIBRATION_LIKELIHOODMAXIMIZER
#define CALIBRATION_LIKELIHOODMAXIMIZER

#include "Math/IFunction.h"

#include "Solver.hh"
#include "CalibrationFunction.hh"
#include "TaggingResult.hh"
#include "TaggingLikelihood.hh"

namespace Espresso {

  /**
   * @class LikelihoodMaximizer
   * @brief Implementation of Solver that maximizes the tagging likelihood using Minuit
   */
  class LikelihoodMaximizer : public Solver {
  public:
    
    /**
     * @brief Standard constructor
     * @param[in] _lf TaggingLikelihood to maximize
     */
    LikelihoodMaximizer(const TaggingLikelihood& _lf);

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
    Vector average;
    Matrix covariance;
    bool verbose;
  };

}

#endif

/**
 * @}
 */
