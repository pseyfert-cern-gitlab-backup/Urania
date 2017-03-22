/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file implements the TaggingResult class
 */

#ifndef CALIBRATION_TAGGINGRESULT
#define CALIBRATION_TAGGINGRESULT

#include "RegressionFunctions.hh"
#include "Calibration.hh"
#include "BDecayModel.hh"
#include "Vector.hh"

namespace Espresso {
  
  // Forward declarations
  class TagCollector;
  class ToyTagger;
  class TaggingResultImpl;

  /**
   * @class TaggingResult
   * @brief Stores statistics of a set of tags 
   *
   * TaggingResult is an object which takes tagging decisions (on a self-tagging calibration mode) one-one-by one
   * and then, when the tagging complete, stores the statistical properties of this set of tagging decisions.
   * This includes the number of events, the observed moments &lang;D<sup>k</sup>&rang; and &lang;D<sup>k</sup>&rang;<sub>S</sub>,
   * and the covariance matrix of these observed moments.
   * When the self-tagging calibration mode is a neutral B decay,
   * this class performs the "lifetime tagging" logic that factors out oscillation.
   */

  class TaggingResult {

    friend TagCollector;
    friend ToyTagger;
  
  public:

    /// Default constructor
    TaggingResult();

    /// Trivial destructor
    virtual ~TaggingResult();
    
    /// Copy constructor
    TaggingResult(const TaggingResult& rhs);

    /// Copy assignment
    TaggingResult& operator=(const TaggingResult&);

    /// Move constructor
    TaggingResult(TaggingResult&&);
    
    /// Move assignment
    TaggingResult& operator=(TaggingResult&&);

    // GET INFO

    /**
     * @brief Retrieve the number of events tagged.
     * @return Number of events
     */ 
    double GetNumEvents() const;

    /**
     * @brief Retrieve the effective number of events tagged, accounting for weights.
     * @return Effective number of events
     */ 
    double GetEffNumEvents() const;

    /**
     * @brief Retrieve the number of events where a tag decision is made
     * @return Number of tagged events
     */ 
    double GetNumTaggedEvents() const;

    /**
     * @brief Retrieve the number of events where a correct tag decision is made
     * @return Number of tagged events
     */ 
    double GetNumRightTaggedEvents() const;

    /**
     * @brief Retrieve the number of events where an incorrect tag decision is made
     * @return Number of tagged events
     */ 
    double GetNumWrongTaggedEvents() const;

    /**
     * @brief Sorts the tagging results table
     * @details A check to see if this has already been done saves time
     * @param[in] If true, overrides the check to see if the table is sorted already
     */
    void sortByEta(bool force = true) const;

    /**
     * @brief Sorts the tagging results table by calibrated value
     * @details A check to see if this has already been done saves time
     * @param[in] If true, overrides the check to see if the table is sorted already
     */
    void sortByPi(bool force = true) const;

    /**
     * @brief Sorts the tagging results table by decay time
     * @details A check to see if this has already been done saves time
     * @param[in] If true, overrides the check to see if the table is sorted already
     */
    void sortByTau(bool force = true) const;
    
    /**
     * @brief Sorts the tagging results table by decay time modulo some period.
     * @details This is useful for Bs decays, which oscillate very quickly
     * @param[in] period Period to apply when sorting (in picoseconds) 
     */
    void sortByTau(double period) const;

    /**
     * @brief Returns the &eta; value that is the p-th quantile
     * @details Implements Hyndman and Fan type 7 algorithm,
     * the default quantile algorithm in S and R.
     * @param[in] p Quantile to compute
     */ 
    double EtaQuantile(double p) const;

    /**
     * @brief Returns a vector the &eta; values for the quantiles
     * of the tagger's &eta; distribution.
     * @param[in] numGroups number of quantile groups; e.g. 4 for quartiles
     */ 
    std::vector<double> EtaQuantiles(int numGroups) const;

    void ApplyCalibration(const Calibration& cal);

    /// Printing operator
    friend std::ostream& operator<< (std::ostream& os, const TaggingResult& res);

    /**
     * @struct BinInfo
     * @brief Tagging results in an bin of &eta; (or sometimes &omega; or &pi;).
     * @details Stores the average predicted mistag in a bin along with numbers of 
     * correctly and incorrectly tagged events.
     * This class has a function (CreateBinTable) to bin the dataset by the predicted mistag &eta;.
     * Some functions in TaggingResultMetrics.hh piggyback on this struct to compute
     * Hosmer-Lemeshow statistics, which are binned in &omega;,
     * which is different because of the delta parameters.
     */
    struct BinInfo {
      double eta; /// average mistag probability
      double lowEdge; /// lower bin edge
      double highEdge; /// upper bin edge
      double numRight; /// Effective number of correctly tagged events
      double numWrong; /// Effective number of incorrectly tagged events
    };


    /// Printing operator
    friend std::ostream& operator<< (std::ostream& os, const BinInfo& info);

    using BinTable = std::vector<BinInfo>;
    
    /**
     * @struct TauInfo
     * @brief Tagging results in a decay time bin
     */
    struct TauInfo {
      double tau; ///< Average lifetime in bin
      double lowEdge; ///< Lower bin edge
      double highEdge; ///< Upper bin edge
      double asymm; ///< Asymmetry in this lifetime bin
      double err; ///< Uncertainty on asymmetry
    };

    using TauTable = std::vector<TauInfo>;
    
    /// Printing operator
    friend std::ostream& operator<< (std::ostream& os, const BinTable& table);

    /**
     * @struct SmoothingOptions
     * @brief Options on how to apply kernel smoothing to discrete data
     */
    struct SmoothingOptions {
      int num_points; ///< Number of points at which to compute kernel smoothed values
      double sigma; ///< Kernel width in x-axis; this is dangerously used for &eta; and decay time, which have different scales
    };
    
    /**
     * @struct WrappingOptions
     * @brief Options on how to treat decay time when creating a TauTable
     */
    struct WrappingOptions {
      double period; ///< Modulus (in ps) with which to enter decay time in TauTable; useful for B<sub>s</sub>
      double maximum; ///< Maximum decay time (in ps) to enter into TauTable; useful for B<sub>d</sub>
    };
    
    /**
     * @brief Creates a contingency table of accuracy vs predicted accuracy
     * @details Creates a table of observed correctly tagged fraction
     * vs. predicted fraction, e.g. \htmlonly &pi;&#770;\endhtmlonly vs. &pi;,
     * that factors in oscillation dilution and tagging asymmetry.
     * This could be made a graphic, but is is mostly useful for 
     * goodness-of-fit diagnostics (e.g. Hosmer-Lemeshow tests)
     * @param[in] numGroups Number of bins of &pi;
     */
    BinTable CreateCalibratedBinTable(int numGroups = 10) const;

    /**
     * Creates a table of observed mistag fraction vs. predicted mistag
     * fraction, e.g. &omega; vs. &eta;,
     * that factors in oscillation dilution but not tagging asymmetry.
     * Graphing this produces the standard &omega; vs &eta; graph,
     * or its nearest equivalent for neutral modes.
     * @param[in] numGroups Number of bins of &eta;
     */
    BinTable CreateBinTable(int numGroups = 10) const;

    /**
     * Creates a large table of observed mistag fraction vs. predicted mistag
     * fraction, e.g. &omega; vs. &eta;,
     * Uses gaussian kernel
     * smoothing to smooth the outcome variable.
     * Graphing this produces the standard &omega; vs &eta; graph,
     * or its nearest equivalent for neutral modes, with
     * slightly more detail than a binned table.
     * @param[in] opts Struct with members `num_points`, number of points in smoothed table, and `sigma`, width of gaussian smoothing kernel
     */
    BinTable CreateKernelSmoothedBinTable(SmoothingOptions opts = {1000,0.01}) const;

    /**
     * Creates a table of tagged asymmetry
     * as a function of decay time. The asymmetry is calculated with event
     * by event weighting and corrected for the effective dilution, and so
     * the curve should be cos(&Delta;m t).
     * @param[in] numGroups Number of bins of &tau;
     * @param[in] wopts Struct with members `period`, oscillation period to use as modulus (0 is default/none), and `maximum`, maximum lifetime to consider (-1 is default/none)
     */
    TauTable CreateTauTable(int numGroups = 10, WrappingOptions wopts = {0.0,-1}) const;

    /**
     * Creates a table of tagged asymmetry
     * as a function of decay time. The asymmetry is calculated with event
     * by event weighting and corrected for the effective dilution, and so
     * the curve should be cos(&Delta;m t).
     * @param[in] opts Struct with members `num_points`, number of points in smoothed table, and `sigma`, width of gaussian smoothing kernel
     * @param[in] wopts Struct with members `period`, oscillation period to use as modulus (0 is default/none), and `maximum`, maximum lifetime to consider (-1 is default/none)
     */
    TauTable CreateKernelSmoothedTauTable(SmoothingOptions opts = {1000,0.01}, WrappingOptions wopts = {0.0,-1}) const;

    /**
     * @struct TagInfo
     * @brief Stores all the information pertinent to a flavor tag for a single event
     * @details This includes the predicted production flavour and mistag, the real decay
     * flavour of the signal B, and information related to the decay time of the B.
     * For caching purposes during calibration, it also includes entries for the calibrated
     * mistag value and its derivative w.r.t. the tagging parameters.
     */
    struct TagInfo {
      Flavour flavour; ///< True flavour of the signal B at decay
      Flavour predFlavour; ///< Predicted production flavour of the signal B
      bool correct; ///< Whether or not the predicted production flavour agrees with the decay flavor (redundant)
      bool oscillated; ///< Whether or not the signal B is more likely than not to have oscillated
      double eta; ///< The predicted mistag probability of the tag decision
      double tau; ///< The decay time of the signal B (tau is a misleading notation)
      double res_dilution; ///< The overall dilution due to the lifetime resolution
      double pollution; ///< The overall probability that the decay flavour of the B is not its production flavor, factoring in lifetime resolution and production asymmetry
      double omega; ///< The calibrated mistag probability
      Vector domega; ///< Derivative of the calibrated mistag probability
      double pi; ///< The combined probability that the predicted production flavour equals the decay flavour
      Vector dpi; ///< Derivative of the combined probability
      double W; ///< Weight
    };

    using TagTable = std::vector<TagInfo>;
    
    /**
     * Returns a reference to the table of tagging results.
     */
    const TagTable& GetTagTable() const;
    
    /**
     * Returns a tuple representing the value +/- statistical uncertainty
     * +/- systematic uncertainty of the calibration dilution squared &lang;D<sup>2</sup>&rang;.
     */
    std::tuple<double,double,double> DilutionSquared() const;

  private:
    void AddTagInfo(const TagInfo& info);
    void Increment(double _NumEvents, double _NumTaggedEvents,
                   double _NumRightTaggedEvents, double _NumWrongTaggedEvents);

  private:
    static std::size_t PreReserveSize();
    void Reserve(std::size_t r);

  private:
    std::unique_ptr<TaggingResultImpl> pImpl;
    
  };
}

#endif

/**
 * @}
 */
