/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the TaggingLikelihood class
 */

#ifndef ESPRESSO_TAGGINGLIKELIHOOD_HH 
#define ESPRESSO_TAGGINGLIKELIHOOD_HH 1

// Include files
#include "Math/IFunction.h"

#include "TaggingResult.hh"
#include "GLMCalibrationFunction.hh"
#include "GLMModel.hh"
#include "Vector.hh"
#include "Matrix.hh"

namespace Espresso 
{
  
  /**
   * @class TaggingLikelihood
   * @brief Class that represents likelihood function for tagging result
   */
  class TaggingLikelihood : public ROOT::Math::IGradientFunctionMultiDim {
  public: 

    /**
     * @brief Standard constructor
     * @param[in] _tag Tagging result data
     * @param[in] _glm GLM for calibration function
     * @param[in] _L Regression link for calibration function
     */
    TaggingLikelihood(const TaggingResult& _tag, const GLMModel& _glm, Regression::LinkType _L);

    /// Copy constructor
    TaggingLikelihood(const TaggingLikelihood& rhs);

    /// Standard desctuctor
    virtual ~TaggingLikelihood();
    
    /**
     * @brief Returns deviance
     * @param[in] Theta Parameter values
     * @return Deviance D = -2log(ℒ)
     */
    double GetDeviance(const double* Theta) const;

    /**
     * @brief Returns the log-likelihood
     * @param[in] Theta Parameter values
     * @return Log-likelihood log(ℒ)
     */
    double GetLogLikelihood(const double* Theta) const;

    /**
     * @brief Returns the gradient of the log-likelihood
     * @param[in] Theta Parameter values
     * @return ∂log(ℒ)/∂&theta;<sub>i</sub>
     */
    Vector GetLogLikelihoodGradient(const double* Theta) const;

    /**
     * @brief Returns the hessian of the log-likelihood
     * @param[in] Theta Parameter values
     * @return ∂<sup>2</sup>log(ℒ)/∂&theta;<sub>i</sub>∂&theta;<sub>j</sub>
     */
    Matrix GetLogLikelihoodHessian(const double* Theta) const;

    /// Enum representing covariance correction methods
    enum class CovarianceCorrectionMethod {
      None, ///< no correction
      Yuehong, ///< correction from LHCb-INT-2012-017, multiplying covariance matrix by &Sigma;w<sup>2</sup>/&Sigma;w
      Markward, ///< correction from LHCb-INT-2011-044, multiplying VC<sup>-1</sup>
    };

    /**
     * Returns an observed covariance matrix, applying the appropriate corrections for the sWeights
     * @param[in] Theta Parameter values
     * @param[in] method Covariance matrix correction method to use
     */
    Matrix GetCovarianceMatrix(const double* Theta, CovarianceCorrectionMethod method = CovarianceCorrectionMethod::None) const;
    
    /**
     * @brief Sets values of log(L) and its gradient (first derivative) and hessian (second derivative).
     * @detail Skips setting any input that is a null pointer.
     * @param[in] Theta Parameter values
     * @param[out] f log(ℒ)
     * @param[out] df ∂log(ℒ)/∂&theta;<sub>i</sub>
     * @param[out] ddf ∂<sup>2</sup>log(ℒ)/∂&theta;<sub>i</sub>∂&theta;<sub>j</sub>
     */
    void GetLogLikelihoodData(const double* Theta, double* f, Vector* df, Matrix* ddf) const;

  private:
    void workhorse(const double* Theta, double* f, Vector* df, Matrix* ddf, bool squareWeights) const;

    // Implementing inherited public functions
  public:

    /**
     * Clones likelihood object
     */
    virtual TaggingLikelihood* Clone() const override;

    /**
     * @brief Number of parameters in the likelihood function.
     * @detail This includes the delta parameters.
     */
    virtual unsigned int NDim() const override { return 2*numParams;; }

    /**
     * Gradient of deviance function, for minimization
     * @param[in] Theta Array of values of calibration parameters &theta;<sub>i</sub>
     * @param[out] grad Gradient -2∂log(ℒ)/∂&theta;<sub>i</sub> at value &theta;<sub>i</sub>
     */
    virtual void Gradient(const double* Theta, double* grad) const override;

    /**
     * Value and gradient of deviance function, for minimization
     * @param[in] Theta Parameter values
     * @param[out] f Value -2log(ℒ) at value &theta;<sub>i</sub>
     * @param[out] df Gradient -2∂log(ℒ)/∂&theta;<sub>i</sub> at value &theta;<sub>i</sub>
     */
    virtual void FdF(const double* Theta, double& f, double* df) const override;

    // Implementing inherited private functions
  private:
    
    virtual double DoEval(const double* x) const override;
    virtual double DoDerivative(const double* x, unsigned int icoord) const override;
    
    struct BasisCache {
      Vector basis;
      double offset;
    };
    
    using BasisCacheTable = std::vector<BasisCache>;

  private:
    // unsigned int ndim;
    std::unique_ptr<GLMCalibrationFunction> func;
    const unsigned int numParams; // mostly unused; might want to use for handling GLMCalibratiobOBjects
    const Regression::LinkType L; // currently unused, might want to use this for handling GLMCalibrationObjects
    const TaggingResult& tag;
    BasisCacheTable cache;
    double* Thetalast; // for DoEval
    double* ThetaP;
    double* ThetaM;
  };
}

    
#endif // ESPRESSO_TAGGINGLIKELIHOOD_HH


/**
 * @}
 */
