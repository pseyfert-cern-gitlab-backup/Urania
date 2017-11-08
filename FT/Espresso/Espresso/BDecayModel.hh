/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the BDecayModel class.
 */

#ifndef ESPRESSO_BDECAYMODEL
#define ESPRESSO_BDECAYMODEL

#include "TemplateTools.hh"
#include "Tagging.hh"
#include "NormalDistribution.hh"
#include "ExponentialDistribution.hh"
#include "DiracDeltaDistribution.hh"

namespace Espresso {

  using ResolutionModel = std::function<std::unique_ptr<Distribution>(double,double)>;
  
  /**
   * @class BDecayModel
   * @brief Class to represent the decay and reconstruction properties of a B meson
   * @details A complete B decay model, for calibration and toy studies.
   * Contains information including constants like lifetime, oscillation frequency, and production asymmetry,
   * and the lifetime resolution model for the B species and decay.
   * 
   */
  class BDecayModel {

  public:

    /**
     * @brief Default constructor
     * @details Creates default decay model for given CalibrationMode
     * (e.g. B species B<sup>+</sup>, B<sup>0</sup>, or B<sub>s</sub>).
     */
    BDecayModel(CalibrationMode _mode = CalibrationMode::ChargedBu);

    /// Copy constructor
    BDecayModel(const BDecayModel& rhs);

    /// Move constructor
    BDecayModel(BDecayModel&& rhs);

    /// Destructor
    ~BDecayModel();
    
    /**
     * Returns CalibrationMode (e.g. B species B<sup>+</sup>, B<sup>0</sup>, or B<sub>s</sub>) of this decay model.
     */
    CalibrationMode GetMode() const { return mode; }

    /**
     * Returns the production asymmetry
     */
    double GetAsymmetry() const { return m_asymmetry; }

    /**
     * Sample from the decay time distribution of the model.
     * This includes the effect of the decay time acceptance.
     */
    double SampleDecayTime() const;

    /**
     * Sample from the resolution distribution of the model.
     * This corresponds more properly to the "DecayTreeFitter" resolution
     * that parameterizes the resolution model of the decay.
     * The model assumes this to be independent of the lifetime.
     * Given a lifetime and resolution, the ResolutionModel gives the actual
     * resolution distribution, which can depend on the lifetime and resolution.
     */
    double SampleResolution() const;

    /**
     * Returns the resolution model
     */
    const ResolutionModel& GetResolutionModel() const;

    /**
     * @brief Sets the production asymmetry
     */
    void SetAsymmetry(double a) { m_asymmetry = a; }

    /**
     * @brief Sets the acceptance function (used for a toy tagger)
     */
    void SetAcceptanceFunc(Function func) { m_AcceptanceFunc = func; }

    /**
     * @brief Sets the lifetime distribution via a smart pointer to a distribution,
     * transferring ownership of the distribution.
     */
    void SetLifetimeDist(std::unique_ptr<Distribution>&& pdist) {
      m_LifetimeDist = std::move(pdist);
    }

    /**
     * @brief Sets the lifetime distribution via a Distribution reference,
     * making a copy of the Distribution owned by the BDecayModel.
     */
    template<typename T>
    void  SetLifetimeDist(T&& dist) {
      m_LifetimeDist = std::make_unique<typename std::decay<T>::type>(std::forward<T>(dist));
    }    
    
    /**
     * Sets the resolution distribution via a smart pointer to a distribution,
     * transferring ownership of the distribution.
     */
    void SetResolutionDist(std::unique_ptr<Distribution>&& pdist) {
      m_ResolutionDist = std::move(pdist);
    }

    /**
     * Sets the resolution distribution via a Distribution reference,
     * making a copy of the Distribution owned by the BDecayModel.
     */
    template<typename T>
    void  SetResolutionDist(T&& dist) {
      m_ResolutionDist = std::make_unique<typename std::decay<T>::type>(std::forward<T>(dist));
    }    

    /**
     * Sets the resolution model of the decay model by passing a ResolutionModel function object/pointer.
     */
    void SetResolutionModel(const ResolutionModel& model) { m_ResolutionModel = model; }

  private:
    CalibrationMode mode;
    double m_asymmetry;
    Function m_AcceptanceFunc;
    std::unique_ptr<Distribution> m_LifetimeDist;
    std::unique_ptr<Distribution> m_ResolutionDist;
    ResolutionModel m_ResolutionModel;
  };


  // SINGLETONS
  const std::map<CalibrationMode, ExponentialDistribution>& DefLifetimeDist(); // tau distribution
  
  const double& DefAcceptanceCutoff(); // for default acceptance function
  const Function& DefAcceptanceFunc();
  
  const double& DefResolution(); // for default resolution function
  const DiracDeltaDistribution& DefResolutionDist(); // tauerr distribution
  const ResolutionModel& DefResolutionModel(); // takes tau, tauerr => smeared tau

}

#endif

/**
 * @}
 */

