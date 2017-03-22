/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Constants related to B tagging
 */

#ifndef CALIBRATION_TAGGING
#define CALIBRATION_TAGGING

#include <map>

namespace Espresso {

  const bool PrintHardDebugInfo = false;

  const bool UseLifetimeWeights = false;

  /**
   * This enumerates the flavour of B particles
   */
  enum class Flavour {
    Neg = -1, ///< B<sup>-</sup>, <span style="text-decoration:overline;">B</span> <sup>0</sup>, <span style="text-decoration:overline;">B</span><sub>s</sub>
      Unknown = 0, ///< Unknown flavour
      Pos = 1 ///< B<sup>+</sup>, B<sup>0</sup>, B<sub>s</sub>
      };
  
  inline Flavour FlavourFromInt(int t) 
  {
    Flavour f;
    if (t == 0)
      f = Flavour::Unknown;
    else if (t > 0)
      f = Flavour::Pos;
    else
      f = Flavour::Neg;
    
    return f;
  }
  
  inline Flavour Opposite(Flavour f)
  {
    if (f == Flavour::Pos)
      return Flavour::Neg;
    else if (f == Flavour::Neg)
      return Flavour::Pos;
    else
      return Flavour::Unknown;
  }
  
  
  /**
   * This enumerates the types of physical B decay modes
   */
  enum class CalibrationMode {
    ChargedBu, ///< B<sup>&plusmn;</sup> decays
      NeutralBd, ///< B<sup>0</sup> and <span style="text-decoration: overline;">B</span><sup>0</sup> decays
      NeutralBs, ///< B<sub>s</sub> and <span style="text-decoration: overline;">B</span><sub>s</sub> decays
      NUM=NeutralBs+1 ///< a counter
  };
  const int NumCalibrationModes = static_cast<int>(CalibrationMode::NUM);

  // Δm in units of 1e12 hbar/sec
  const double BuDeltaM = 0.0; ///< &Delta;m between B<sup>+</sup> and B<sup>-</sup> in units of 10<sup>12</sup> ℏ/sec
  const double BuDeltaMErr = 0.0; ///< experimental error on &Delta;m between B<sup>+</sup> and B<sup>-</sup> in units of 10<sup>12</sup> ℏ/sec
  const double BdDeltaM = 0.510; ///< &Delta;m between B<sup>0</sup> and <span style="text-decoration:overline;">B</span><sup>0</sup> in units of 10<sup>12</sup> ℏ/sec
  const double BdDeltaMErr = 0.003; ///< error on &Delta;m between B<sup>0</sup> and <span style="text-decoration:overline;">B</span><sup>0</sup> in units of 10<sup>12</sup> ℏ/sec
  const double BsDeltaM = 17.761; ///< &Delta;m between B<sub>s</sub> and <span style="text-decoration:overline;">B</span><sub>s</sub> in units of 10<sup>12</sup> ℏ/sec
  const double BsDeltaMErr = 0.022; ///< error on &Delta;m between B<sub>s</sub> and <span style="text-decoration:overline;">B</span><sub>s</sub> in units of 10<sup>12</sup> ℏ/sec 
  
  /// map from calibration mode type to &Delta;m
  const std::map<CalibrationMode, double> ModeFrequency = {
    {CalibrationMode::ChargedBu, BuDeltaM},
    {CalibrationMode::NeutralBd, BdDeltaM},
    {CalibrationMode::NeutralBs, BsDeltaM},
  }; 

  /// map from calibration mode type to experimental error on &Delta;m
  const std::map<CalibrationMode, double> ModeFrequencyErr = {
    {CalibrationMode::ChargedBu, BuDeltaMErr},
    {CalibrationMode::NeutralBd, BdDeltaMErr},
    {CalibrationMode::NeutralBs, BsDeltaMErr},
  }; 

  // Lifetime in units of 1e-12 s
  const double BuLifetime = 1.638; ///< lifetime &tau; of B<sup>&plusmn;</sup>
  const double BuLifetimeErr = 0.004; ///< experimental error on lifetime &tau; of B<sup>&plusmn;</sup>
  const double BdLifetime = 1.519; ///< lifetime &tau; of B<sup>0</sup>
  const double BdLifetimeErr = 0.005; ///< experimental error on lifetime &tau; of B<sup>0</sup>
  const double BsLifetime = 1.512; ///< lifetime &tau; of B<sub>s</sub>
  const double BsLifetimeErr = 0.007; ///< experimental error on lifetime &tau; of B<sub>s</sub>

  /// map from calibration mode type to B lifetime
  const std::map<CalibrationMode, double> ModeLifetime = {
    {CalibrationMode::ChargedBu, BuLifetime},
    {CalibrationMode::NeutralBd, BdLifetime},
    {CalibrationMode::NeutralBs, BsLifetime},
  }; 

  /// map from calibration mode type to experimental error on B lifetime
  const std::map<CalibrationMode, double> ModeLifetimeErr = {
    {CalibrationMode::ChargedBu, BuLifetimeErr},
    {CalibrationMode::NeutralBd, BdLifetimeErr},
    {CalibrationMode::NeutralBs, BsLifetimeErr},
  }; 

  // Delta gamma in units of 1e12 1/s
  const double BuDeltaGamma = 0.0;
  const double BuDeltaGammaErr = 0.0;
  const double BdDeltaGamma = 0.0;
  const double BdDeltaGammaErr = 0.06;
  const double BsDeltaGamma = 0.0913;
  const double BsDeltaGammaErr = 0.008;  

  /// map from calibration mode type to B &Delta;&Gamma;
  const std::map<CalibrationMode, double> ModeDeltaGamma = {
    {CalibrationMode::ChargedBu, BuDeltaGamma},
    {CalibrationMode::NeutralBd, BdDeltaGamma},
    {CalibrationMode::NeutralBs, BsDeltaGamma},
  }; 

  /// map from calibration mode type to experimental error on B &Delta;&Gamma;
  const std::map<CalibrationMode, double> ModeDeltaGammaErr = {
    {CalibrationMode::ChargedBu, BuDeltaGammaErr},
    {CalibrationMode::NeutralBd, BdDeltaGammaErr},
    {CalibrationMode::NeutralBs, BsDeltaGammaErr},
  }; 

  inline double iff(double p1, double p2) {
    double piff = 2*p1*p2 - p1 - p2 + 1.0;
    return piff;
  }
  
  inline double d_iff(double p1, double p2) {
    return (2*p2-1)*p1;
  }

}

#endif

/**
 * @}
 */

