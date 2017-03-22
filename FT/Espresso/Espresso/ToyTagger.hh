/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the ToyTagger class
 */

#ifndef CALIBRATION_TOYTAGGER
#define CALIBRATION_TOYTAGGER

#include "BDecayModel.hh"
#include "Calibration.hh"

namespace Espresso { 
  
  // Forward Declarations
  class TaggingResult;
  
  /**
   * @class ToyTagger
   * @brief Fake tagging algorithm
   * @details ToyTagger is a class which emulates a real tagger
   * acting on a Bu, Bd, or Bs decay mode.
   * 
   */
  class ToyTagger {
  public:

    /**
     * @brief Simple constructor.
     * @details Allows specification of B flavour,
     * distribution of predicted mistag &eta;
     * and a Calibration object that produces mis-calibration &omega;(&eta;).
     * The default lifetime model for the specified flavour is assumed.
     *
     * @param[in] _mode is the B flavour (ChargedBu, NeutralBd, NeutralBs)
     * @param[in] _pdf is the distribution of the predicted ilution
     * @param[in] _smear_cal is the (mis)calibration object
     */
    ToyTagger(CalibrationMode _mode, const Distribution& _pdf, const Calibration* _smear_cal = nullptr);

    /**
     * @brief Constructor with more lifetime customization options.
     * @details Allows specification of custom BDecayModel,
     * distribution of predicted mistag &eta;
     * and a Calibration object that produces mis-calibration &omega;(&eta;).
     * The custom BDecayModel can have a non-standard lifetime, lifetime acceptance model,
     * and lifetime resolution model.
     * @param[in] _decModel is the model of the B decay
     * @param[in] _pdf is the distribution of the predicted ilution
     * @param[in] _smear_cal is the (mis)calibration object
     */
    ToyTagger(const BDecayModel& _decModel, const Distribution& _pdf, const Calibration* _smear_cal = nullptr);

    /**
     * @brief Simple constructor.
     * @details Allows specification of a TaggingResult object to bootstrap from
     * and a Calibration object that produces mis-calibration &omega;(&eta;).
     * The default lifetime model for the specified flavour is assumed.
     *
     * @param[in] _bootres The TaggingResult to bootstrap
     * @param[in] _smear_cal is the (mis)calibration object
     */
    ToyTagger(const TaggingResult& _bootres);

    /// Trivial destructor
    ~ToyTagger() {}


    /**
     * Sets the fraction of generated events which will be background (up to binomial fluctuations).
     * This is 0 by default.
     * The eta distribution of the background is identical to that of the signal,
     * and the mistag rate is a constant 50%.
     * @param[in] _BackgroundFraction The fraction of the generated events which will be background.
     * @param[in] _SidebandRatio The ratio of the width of the sideband region to the signal region (typically 1)
     */
    void SetBackgroundFraction(double _BackgroundFraction);

    /**
     * Sets the ratio of the width of the sideband region to the signal region.
     * This is 1 by default. Changing this ratio changes the values of the toy sWeights;
     * the bigger this value is, the closer the sideband sWeights are to 0.
     * @param[in] _SidebandRatio The ratio of the width of the sideband region to the signal region.
     */
    void SetSidebandRatio(double _SidebandRatio);

    /**
     * This performs a toy study, calculates the moments <D^k> and <CD^k>,
     * and returns them inside a TaggingResult object.
     *
     * @param[in] NumEvents Number of events for toy study
     * @param[in] save Whether to print out the generated toy sample to a csv file
     */
    TaggingResult GetToyTaggingResult(unsigned int NumEvents, bool save = false);

    /**
     * Configures the toy model to "forget" the generator resolution model
     * and use the default resolution model when calculating oscillation probabilities.
     * Later, this should be expaanded to simply allow a different "reconstruction" resolution model
     * than generation resolution model.
     * 
     */
    void ForgetResolution(bool b) { m_forgetResolution = b; }
    
    /**
     * Turn on (or off) the verbose setting,
     * which prints extra information about expected and simulated moments.
     */
    void SetVerbose(bool _verbose) { verbose = _verbose; }

  private:

    const bool analytic;
    CalibrationMode mode;
    const Espresso::BDecayModel* decModel;
    const Espresso::Distribution* pdf;
    const Espresso::TaggingResult* bootres;
    const Calibration* smear_cal;
    double BackgroundFraction;
    double SidebandRatio;
    bool m_forgetResolution;
    bool verbose;

  };

  /**
   * Default BDecayModel if none is specified
   */
  const std::map<CalibrationMode, const BDecayModel>& DefDecModel();

}

#endif


/**
 * @}
 */
