/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file defines the TagCollector class
 */

#ifndef ESPRESSO_TAGCOLLECTOR_HH 
#define ESPRESSO_TAGCOLLECTOR_HH 1

// Include files
#include "TaggingResult.hh"

namespace Espresso 
{

  /**
   * @class TagCollector TagCollector.hh Espresso/TagCollector.hh
   * @brief Class that collects tagging decisions and produces a TaggingResult
   */
  class TagCollector {
  public: 
    
    // CONSTRUCTOR
    /**
     * Allows specification of B flavour and the degree of calibration that will be performed,
     * so that the proper number of moments will be computed and stored.
     *
     * @param[in] _decModel Decay model for the B flavour (ChargedBu, NeutralBd, NeutralBs); ChargedBu by default
     * @param[in] _cal an optional Calibration object used to compute tagging power
     */
    TagCollector(const BDecayModel& _decModel, std::shared_ptr<Calibration> _cal = nullptr);

    /// Copy constructor
    TagCollector(const TagCollector& rhs);

    /// Move constructor
    TagCollector(TagCollector&& rhs);

    // DESTRUCTOR
    ~TagCollector();
  
    // SET INFO
    /**
     * Add a new tag decision
     *
     * @param[in] decay Flavour of the signal B at decay time
     * @param[in] pred Predicted flavour of the signal B
     * @param[in] eta Assigned mistag of this prediction
     * @param[in] weight Weight of the event (e.g. sWeight of the signal B)
     * @param[in] time Decay time of the signal B
     * @param[in] time_res Resolution on the decay time
     */
    void AddTag(Flavour decay, Flavour pred, double eta, double weight = 1.0, double time = 0.0, double time_res = 0.0);
  
    /**
     * Signals that no more tagging decisions will be added.
     */
    const TaggingResult& GetResult() const;
  
    /*
     * Turn on (or off) the verbose setting,
     * which prints extra information about expected and simulated moments.
     */
    void SetVerbose(bool _verbose) { verbose = _verbose; };

    static void setExpectedNumberOfEvents(unsigned int num) 
    {
      std::cout << "SETING EXPECTED NUMBER OF EVENTS = " << num << std::endl;
      ExpectedNumberOfEvents = num;
    }

  private:
    CalibrationMode mode;
    Espresso::BDecayModel decModel;
    std::shared_ptr<Calibration> cal;
    mutable TaggingResult res;
    unsigned int numEvents;
    bool reserved;
    bool verbose;

    unsigned int thiscount;
    static unsigned int count;
    static unsigned int ExpectedNumberOfEvents;
  };

}

#endif // ESPRESSO_TAGCOLLECTOR_HH


/**
 * @}
 */
