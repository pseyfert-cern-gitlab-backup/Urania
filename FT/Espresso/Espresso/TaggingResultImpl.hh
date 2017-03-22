/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief This header file implements the TaggingResultImpl class
 */

#ifndef CALIBRATION_TAGGINGRESULTIMPL
#define CALIBRATION_TAGGINGRESULTIMPL

#include "Tagging.hh"
#include "TaggingResult.hh"
#include "Calibration.hh"
#include "BDecayModel.hh"

namespace Espresso {
  

  /**
   * @class TaggingResultImpl
   * @brief This class implements the methods in TaggingResult via the pimpl idiom
   * @brief Refer to TaggingResult for documentation of the various methods
   */
  class TaggingResultImpl {
  
  public:

    // Default constructor
    TaggingResultImpl();

    // Copy construtor
    TaggingResultImpl(const TaggingResultImpl&) = default;

    // Copy assignment
    TaggingResultImpl& operator=(const TaggingResultImpl&) = default;

    // Move constructor
    TaggingResultImpl(TaggingResultImpl&&) = default;

    // Move assignment
    TaggingResultImpl& operator=(TaggingResultImpl&&) = default;

    // Member methods
    double GetNumEvents() const { return NumEvents; };
    double GetEffNumEvents() { return NumEvents*NumEvents/SumW2; };
    double GetNumTaggedEvents() const { return NumTaggedEvents; };
    double GetNumRightTaggedEvents() const { return NumRightTaggedEvents; };
    double GetNumWrongTaggedEvents() const { return NumWrongTaggedEvents; };

    void sortByEta(bool force = true) const;
    void sortByPi(bool force = true) const;
    void sortByTau(bool force = true) const;
    void sortByTau(double period) const;

    double EtaQuantile(double p) const;
    std::vector<double> EtaQuantiles(int numGroups) const;
    

    void ApplyCalibration(const Calibration& cal);

    TaggingResult::BinTable CreateCalibratedBinTable(int numGroups = 10) const;
    TaggingResult::BinTable CreateBinTable(int numGroups = 10) const;
    TaggingResult::BinTable CreateKernelSmoothedBinTable(TaggingResult::SmoothingOptions opts = {1000,0.01}) const;
    TaggingResult::TauTable CreateTauTable(int numGroups = 10, TaggingResult::WrappingOptions wopts = {0.0,-1}) const;
    TaggingResult::TauTable CreateKernelSmoothedTauTable(TaggingResult::SmoothingOptions opts = {1000,0.05},
                                                         TaggingResult::WrappingOptions wopts = {0.0,-1}) const;

    const TaggingResult::TagTable& GetTagTable() const;

    void AddTagInfo(const TaggingResult::TagInfo& info);
    void Increment(double _NumEvents, double _NumTaggedEvents,
                   double _NumRightTaggedEvents, double _NumWrongTaggedEvents);
    
    std::tuple<double,double,double> DilutionSquared() const;
    
    static std::size_t PreReserveSize() { return pre_reserve; }
    void Reserve(std::size_t r);

  private:
    static const std::size_t pre_reserve = 1000;

  private:

    // Memory store off tagging data
    mutable TaggingResult::TagTable table; // mutable because we sort it
    mutable bool isTableSorted_eta;
    mutable bool isTableSorted_pi;
    mutable bool isTableSorted_tau;

    // Calibration-independent information
    double NumEvents;
    double NumTaggedEvents;
    double NumRightTaggedEvents;
    double NumWrongTaggedEvents;
    double SumW2;

    // Dilution
    double dilution;
    double dilution_err;
    double dilution_calerr;
    
  };
}

#endif

/**
 * @}
 */
