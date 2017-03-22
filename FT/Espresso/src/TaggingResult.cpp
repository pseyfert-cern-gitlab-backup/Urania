#include "TaggingResult.hh"

#include <TAxis.h>

#include "TaggingResultImpl.hh"

using namespace Espresso;

//////////////////////////////
// SPECIAL MEMBER FUNCTIONS //
//////////////////////////////

// Constructor
TaggingResult::TaggingResult()
  : pImpl(std::make_unique<TaggingResultImpl>()) 
{
}

// Destructor
TaggingResult::~TaggingResult() = default;

// Copy operations
TaggingResult::TaggingResult(const TaggingResult& rhs)
  : pImpl(std::make_unique<TaggingResultImpl>(*rhs.pImpl))
{
}

TaggingResult& TaggingResult::operator=(const TaggingResult& rhs) 
{
  *pImpl = *rhs.pImpl;
  return *this;
}

// Move operations
TaggingResult::TaggingResult(TaggingResult&&) = default;
TaggingResult& TaggingResult::operator=(TaggingResult&&) = default;

//////////////////////
// Member Functions //
//////////////////////

double TaggingResult::GetNumEvents() const {
  return pImpl->GetNumEvents();
}

double TaggingResult::GetEffNumEvents() const {
  return pImpl->GetEffNumEvents();
}

double TaggingResult::GetNumTaggedEvents() const {
  return pImpl->GetNumTaggedEvents();
}

double TaggingResult::GetNumRightTaggedEvents() const {
  return pImpl->GetNumRightTaggedEvents();
}

double TaggingResult::GetNumWrongTaggedEvents() const {
  return pImpl->GetNumWrongTaggedEvents();
}

void TaggingResult::sortByEta(bool force) const {
  pImpl->sortByEta(force);
}

void TaggingResult::sortByPi(bool force) const {
  pImpl->sortByPi(force);
}

void TaggingResult::sortByTau(bool force) const {
  pImpl->sortByTau(force);
}

void TaggingResult::sortByTau(double period) const {
  pImpl->sortByTau(period);
}

double TaggingResult::EtaQuantile(double p) const 
{
  return pImpl->EtaQuantile(p);
}

std::vector<double> TaggingResult::EtaQuantiles(int numGroups) const 
{
  return pImpl->EtaQuantiles(numGroups);
}


void TaggingResult::ApplyCalibration(const Calibration& cal) {
  pImpl->ApplyCalibration(cal);
}

TaggingResult::BinTable TaggingResult::CreateCalibratedBinTable(int numGroups) const {
  return pImpl->CreateCalibratedBinTable(numGroups);
}

TaggingResult::BinTable TaggingResult::CreateBinTable(int numGroups) const {
  return pImpl->CreateBinTable(numGroups);
}

TaggingResult::BinTable TaggingResult::CreateKernelSmoothedBinTable(TaggingResult::SmoothingOptions opts) const {
  return pImpl->CreateKernelSmoothedBinTable(opts);
}

TaggingResult::TauTable TaggingResult::CreateTauTable(int numGroups, TaggingResult::WrappingOptions wopts) const {
  return pImpl->CreateTauTable(numGroups, wopts);
}

TaggingResult::TauTable TaggingResult::CreateKernelSmoothedTauTable(TaggingResult::SmoothingOptions opts,
                                                                    TaggingResult::WrappingOptions wopts) const {
  return pImpl->CreateKernelSmoothedTauTable(opts, wopts);
}

const TaggingResult::TagTable& TaggingResult::GetTagTable() const {
  return pImpl->GetTagTable();
}

namespace Espresso 
{
  std::ostream& operator<< (std::ostream& os, const TaggingResult& res) {
    
    std::cout << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "------ TAGGING RESULT ------" << std::endl;
    std::cout << "----------------------------" << std::endl;

    std::cout << "NUM. EVENTS               = " << res.GetNumEvents() << std::endl;
    std::cout << "NUM. TAGGED EVENTS        = " << res.GetNumTaggedEvents() << std::endl;
    std::cout << "CORRECTLY TAGGED FRACTION = " << (res.GetNumRightTaggedEvents() / res.GetNumTaggedEvents()) << std::endl;
    
    return os;
    
  }

  std::ostream& operator<< (std::ostream& os, const TaggingResult::BinInfo& info) {
    os << info.eta << ", "
       << info.numWrong << ", "
       << info.numRight;
    return os;
  }
  
  std::ostream& operator<< (std::ostream& os, const TaggingResult::BinTable& table) {
    os << "PROB, PASS, FAIL" << std::endl;
    for (const auto& info : table) {
      os << info << std::endl;
    }
    return os;
  }

}

std::size_t TaggingResult::PreReserveSize() {
  return TaggingResultImpl::PreReserveSize();
}

void TaggingResult::Reserve(std::size_t t) {
  return pImpl->Reserve(t);
}

void TaggingResult::AddTagInfo(const TagInfo& info) 
{
  pImpl->AddTagInfo(info);
}


void TaggingResult::Increment(double _NumEvents, double _NumTaggedEvents,
                              double _NumRightTaggedEvents, double _NumWrongTaggedEvents)
{
  pImpl->Increment(_NumEvents, _NumTaggedEvents,
                   _NumRightTaggedEvents, _NumWrongTaggedEvents);
}

std::tuple<double,double,double> TaggingResult::DilutionSquared() const 
{
  return pImpl->DilutionSquared();
}
