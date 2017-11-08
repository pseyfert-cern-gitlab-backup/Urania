/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Tagger performance and calibration utilities
 * @details This header file declares many useful functions related to
 * calibrating and assessing tagging results.
 */

#ifndef ESPRESSO_TAGGINGRESULTMETRICS_HH 
#define ESPRESSO_TAGGINGRESULTMETRICS_HH 1

// Include files
#include "TaggingLikelihood.hh"
#include "GLMCalibration.hh"

namespace Espresso 
{

  /**
   * Tuple representing a value +/- statistical uncertainty +/- systematic uncertainty
   */
  using UncertainValue = std::tuple<double,double,double>;

  /**
   * @brief The tagging rate (or efficiency) of the tagger
   * @param[in] res Tagging result
   * @param[in] trueNum Optional; true number of events in case the number of untagged events is incorrectly stored in TaggingResult
   * @param[in] trueNum_eff Optional; weighted true number of events (&Sigma; w)<sup>2</sup>/&Sigma; w<sup>2</sup> in case the number of untagged events is incorrectly stored in TaggingResult
   * @return &epsilon; = (R+W)/(R+W+U) with uncertainties
   */
  UncertainValue TaggingRate(const TaggingResult& res, double trueNum = -1, double trueNum_eff = -1);
  
  /**
   * @brief The average mistag rate of the tagger
   * @param[in] res Tagging result
   * @return W/(R+W) with uncertainties
   */
  UncertainValue MistagRate(const TaggingResult& res);

  /**
   * @brief The squared dilution of the tagger
   * @param[in] res Tagging result
   * @return &lang;D<sup>2</sup>&rang;
   */
  UncertainValue DilutionSquared(const TaggingResult& res);

  /**
   * @brief The effective mistag rate of the tagger
   * @param[in] res Tagging result
   * @return (1 - &radic;&lang;D<sup>2</sup>&rang;)/2
   */
  UncertainValue EffectiveMistag(const TaggingResult& res);

  /**
   * @brief The tagging power of the tagger
   * @param[in] res Tagging result
   * @param[in] trueNum Optional; true number of events in case the number of untagged events is incorrectly stored in TaggingResult
   * @param[in] trueNum_eff Optional; weighted true number of events (&Sigma; w)<sup>2</sup>/&Sigma; w<sup>2</sup> in case the number of untagged events is incorrectly stored in TaggingResult
   * @return &epsilon; &lang;D<sup>2</sup>&rang;
   */
  UncertainValue TaggingPower(const TaggingResult& res, double trueNum = -1, double trueNum_eff = -1);
  
  /**
   * @brief Workhorse function to produce calibration
   * @details This function creates a tagging calibration with all possible options
   * @param[in] res Tagging result to calibrate
   * @param[in] glm GLM to use for calibration
   * @param[in] _L Regression link function to use
   * @param[in] method Covariance matrix correction method to use (defaults to None, though the EPM chooses differently)
   * @param[in] useNewtonRaphson Whether to perform faster root-finding maximization (defaults to false, though the EPM chooses differently)
   * @param[in] verbose Whether to print debugging output
   */
  GLMCalibration TaggingCalibrationCalculator(const TaggingResult& res, const GLMModel& glm,
					      Regression::LinkType _L = Regression::DefaultLinkType,
					      TaggingLikelihood::CovarianceCorrectionMethod method = TaggingLikelihood::CovarianceCorrectionMethod::None,
					      bool useNewtonRaphson = false,
					      bool verbose = false);

  /**
   * @brief Workhorse function to produce calibration
   * @details This overloaded function gives options for creating a GLMModel
   * @param[in] res Tagging result to calibrate
   * @param[in] degree Degree to use for the chosen GLM type
   * @param[in] _T Type of GLM to use
   * @param[in] _L Regression link function to use
   * @param[in] method Covariance matrix correction method to use (defaults to None, though the EPM chooses differently)
   * @param[in] useNewtonRaphson Whether to perform faster root-finding maximization (defaults to false, though the EPM chooses differently)
   * @param[in] verbose Whether to print debugging output
   */
  GLMCalibration TaggingCalibrationCalculator(const TaggingResult& res, int degree,
					      const GLMModel::GLMType _T,
					      Regression::LinkType _L = Regression::DefaultLinkType,
					      TaggingLikelihood::CovarianceCorrectionMethod method = TaggingLikelihood::CovarianceCorrectionMethod::None,
					      bool useNewtonRaphson = false,
					      bool verbose = false);

  /**
   * @brief Calculates the asymmetry in tagging result object
   * @details Uses a simple estimator &alpha; (R-W)/(R+W), where R and W are weighted and &alpha;
   * is a correction factor related to the dilution of the tagger
   * @param[out] asymm the asymmetry 
   * @param[out] err the error on the asymmetry
   * @param[in] table table of tagging results
   * @param[in] cal calibration object
   */
  void calcAsymmetry(double& asymm, double& err, const TaggingResult::TagTable& table, const Calibration* cal);

  /**
   * Calculates the asymmetry in tagging result object using likelihood maximization
   * @param[out] asymm the asymmetry
   * @param[out] err the error on the asymmetry
   * @param[in] table table of tagging results
   * @param[in] cal calibration object
   */
  void calcAsymmetryLikelihood(double& asymm, double& err, const TaggingResult::TagTable& table, const Calibration* cal);

  /**
   * @brief Hosmer-Lemeshow grouped deviance tests
   * @details The deviance of the model is D = G<sup>2</sup> = -2 log(ℒ).
   * For grouped data with g groups, it follows &chi;<sup>2</sup> distribution with
   * approximately g-2 d.o.f., with caveats when there are more than 2 fit parameters.
   * @param[in] Calibrated bin table to process
   * @param[in] PValue Whether to return a raw &chi;<sup>2</sup> value or convert to a p-value
   * @param[in] selfCalibrated Whether the model was calibrated on this dataset (for p-value)
   * @param[in] numParams Number of parameters in the model (for p-value)
   */
  double GroupedDevianceTest(const TaggingResult::BinTable& table, bool PValue = false, bool selfCalibrated = false, int numParams = 0);

  /**
   * @brief Hosmer-Lemeshow grouped Pearson test
   * @details The Pearson statistic is the sum of squared normalized residuals (Y-&pi;)/&pi;(1-&pi;).
   * For grouped data with g groups, it follows a &chi;<sup>2</sup> distribution with
   * approximately g-2 d.o.f., with caveats when there are more than 2 fit parameters.
   * In this case (one covariate; monotonic &omega;(&eta;); binning by quantiles), this is equivalent to the Hosmer-Lemeshow statstic C.
   * @param[in] Calibrated bin table to process
   * @param[in] PValue Whether to return a raw &chi;<sup>2</sup> value or convert to a p-value
   * @param[in] selfCalibrated Whether the model was calibrated on this dataset (for p-value)
   * @param[in] numParams Number of parameters in the model (for p-value)
   */
  double GroupedPearsonTest(const TaggingResult::BinTable& table, bool PValue = false, bool selfCalibrated = false, int numParams = 0);

  /**
   * @brief Ungrouped deviance test
   * @details The deviance of the model is D = G<sup>2</sup> = -2 log(ℒ).
   * For ungrouped data, this follows a normal distribution.
   * The returned value is the corresponding z-score.
   * However, there are numerical issues with the current implementation;
   * it seems that tiny variances are causing some problems in toy studies.
   * The returned value is either the corresponding z-score or the p-value.
   * @param[in] Calibrated bin table to process
   * @param[in] PValue Whether to return a raw z-score or convert to a p-value
   * @param[in] selfCalibrated Whether the model was calibrated on this dataset (for p-value)
   */
  double UngroupedDevianceTest(const TaggingResult& tag, bool PValue = false, bool selfCalibrated = false);

  /**
   * @brief Ungrouped Pearson X<sup>2</sup> test
   * @details The Pearson statistic is the sum of squared normalized residuals (Y-&pi;)/&pi;(1-&pi;).
   * For ungrouped data, this follows a normal distribution.
   * The returned value is either the corresponding z-score or the p-value.
   * @param[in] Calibrated bin table to process
   * @param[in] PValue Whether to return a raw z-score or convert to a p-value
   * @param[in] selfCalibrated Whether the model was calibrated on this dataset (for p-value)
   */
  double UngroupedPearsonTest(const TaggingResult& tag, bool PValue = false, bool selfCalibrated = false);

  /**
   * @brief Ungrouped Cressie-Read test
   * @details The Cressie-Read statistic is the sum 9/5(Y &pi;<sup>-2/3</sup> + (1-Y) (1-&pi;)<sup>-2/3</sup)
   * For ungrouped data, this follows a normal distribution.
   * The returned value is either the corresponding z-score or the p-value.
   * @param[in] Calibrated bin table to process
   * @param[in] PValue Whether to return a raw z-score or convert to a p-value
   * @param[in] selfCalibrated Whether the model was calibrated on this dataset (for p-value)
   */
  double UngroupedCressieReadTest(const TaggingResult& tag, bool PValue = false, bool selfCalibrated = false);

  /**
   * @brief Ungrouped Hosmer-le Cesssie S test
   * @details The S statistic is the sum of the squared (un-normalized) residuals Y-&pi;.
   * For ungrouped data, this follows a normal distribution.
   * The returned value is either the corresponding z-score or the p-value.
   * @param[in] Calibrated bin table to process
   * @param[in] PValue Whether to return a raw z-score or convert to a p-value
   * @param[in] selfCalibrated Whether the model was calibrated on this dataset (for p-value)
   */
  double UngroupedSTest(const TaggingResult& tag, bool PValue = false, bool selfCalibrated = false);

  /**
   * @brief Deviance of calibration model
   * Deviance D = G<sup>2</sup> = -2 log(ℒ)
   * @param[in] tag Tagging result, with calibration applied
   */
  double Deviance(const TaggingResult& tag);

  /**
   * @brief Brier score of calibration model
   * @details This is opular in machine learning and meteorology.
   * It is the unweighted sum of squares BS = &Sigma; (Y-&pi;)<sup>2</sup>,
   * which is related to the lCvHCH statistic S.
   * @param[in] tag Tagging result, with calibration applied
   */
  double BrierScore(const TaggingResult& tag);

  /**
   * @brief Akaike information criterion (AIC) of calibration model
   * @details This penalizes the deviance by twice the number of parameters, e.g.
   * \f[ AIC = -2 \log \mathcal{L} + 2k \f]
   * @param[in] tag Tagging result, with calibration applied
   * @param[in] numParams The number of parameters in the calibration model
   */
  double AIC(const TaggingResult& tag, int numParams);

  /**
   * @brief Bayesian information criterion (BIC) of calibration model
   * @details This is also known as the Schwarz criterion (SC).
   * This penalizes the deviance by the number of parameters times the natural
   * logarithm of the numbre of events, e.g.
   * \f[ BIC = -2 \log \mathcal{L} + k \log(N) \f]
   * @param[in] tag Tagging result, with calibration applied
   * @param[in] numParams The number of parameters in the calibration model
   */
  double BIC(const TaggingResult& tag, int numParams);

  /**
   * @brief Computes &chi;<sup>2</sup> difference between calibrations
   * @details This quantity is given by
   * \f[ (\hat \theta_1 - \hat \theta_2)^T (\sigma^2_1 + \sigma^2_2) (\hat \theta_1 - \hat \theta_1) \f]
   * If the number of parameters or link function differs, this returns 0.
   * This does *not* check that the basis are equivalent - this is the users responsibility!
   * @param[in] lhs First calibration object
   * @param[in] rhs Second calibration object
   */
  double CalibrationComparisonChi2(const Calibration& lhs, const Calibration& rhs);

}


#endif // ESPRESSO_TAGGINGRESULTMETRICS_HH


/**
 * @}
 */
