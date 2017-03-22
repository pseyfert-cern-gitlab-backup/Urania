// Include files
#include "TagCollector.hh"

// local
#include "TaggingResult.hh"
#include "Vector.hh"
#include "StandardCalibration.hh"
#include "Statistics.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : TagCollector
//
// 2015-06-02 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

unsigned int TagCollector::count = 0;
unsigned int TagCollector::ExpectedNumberOfEvents = TaggingResult::PreReserveSize();

//=============================================================================
// Standard constructor, initializes variablesx
//=============================================================================
TagCollector::TagCollector(const BDecayModel& _decModel, std::shared_ptr<Calibration> _cal)
  : mode(_decModel.GetMode()),
    decModel(_decModel),
    cal(_cal),
    res(),
    numEvents(0),
    reserved(false),
    verbose(false),
    thiscount(++count)
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "CONSTRUCTING TAGCOLLECTOR #" << thiscount << std::endl;
}

TagCollector::TagCollector(const TagCollector& rhs)
  : mode(rhs.mode),
    decModel(rhs.decModel),
    cal(rhs.cal),
    res(rhs.res),
    numEvents(rhs.numEvents),
    reserved(rhs.reserved),
    verbose(rhs.verbose),
    thiscount(++count)
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "COPYING TAGCOLLECTOR #" << rhs.thiscount << "TO " << thiscount << std::endl;
}

TagCollector::TagCollector(TagCollector&& rhs)
  : mode(std::move(rhs.mode)),
    decModel(std::move(rhs.decModel)),
    cal(std::move(rhs.cal)),
    res(std::move(rhs.res)),
    numEvents(std::move(rhs.numEvents)),
    reserved(std::move(rhs.reserved)),
    verbose(std::move(rhs.verbose)),
    thiscount(std::move(rhs.thiscount))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "MOVING TAGCOLLECTOR #" << thiscount << std::endl;
}

//=============================================================================
// Destructor
//=============================================================================
TagCollector::~TagCollector() {
  if (Espresso::PrintHardDebugInfo)
    std::cout << "DESTROYING TAGCOLLECTOR" << std::endl;
}

//=============================================================================

void TagCollector::AddTag(Flavour decay, Flavour pred, double eta, double weight, double time, double time_res) {

  //  static int numEvents = 0;
  numEvents += 1;

  // Do something about non-calibration modes later; skip for now
  if (decay == Flavour::Unknown)
    return;

  // ACCOUNT FOR OSCILLATION
  double cphase = 0.0;
  double cphase_naive = cos(ModeFrequency.at(mode)*time);
  double dcphase = 0.0;
  double dcphase_naive = 0.5*(1+cos(2*ModeFrequency.at(mode)*time));
  if (time_res != 0) {
    const ResolutionModel& model = decModel.GetResolutionModel();
    std::unique_ptr<Distribution> dist = model(time,time_res);
    cphase = dist->GetFourierCosTransform(ModeFrequency.at(mode));
    dcphase = 0.5*(1+dist->GetFourierCosTransform(2*ModeFrequency.at(mode)));
  } else {
    cphase = cphase_naive;
    dcphase = dcphase_naive;
  }

  double res_dilution = cphase/cphase_naive; // used in plotting; ignores production asymmetries

  // delta gamma, assumed to be constant over resolution
  double dgt = 1.0/cosh(0.5*ModeDeltaGamma.at(mode)*time);
  cphase *= dgt;
  dcphase *= dgt*dgt;

  // total oscillation probability
  double prod_asymm = decModel.GetAsymmetry();
  double osc_dilution = cphase;
  double osc_dilution_delta = 0.5*prod_asymm*(1-dcphase);
  if (decay == Flavour::Pos)
    osc_dilution += osc_dilution_delta;
  else
    osc_dilution -= osc_dilution_delta;

  double oscWeight = std::abs(osc_dilution);

  int osc = static_cast<int>(osc_dilution / oscWeight);
  bool hasOsc = (osc == -1);
  Flavour prod;
  if (hasOsc) {
    if (decay == Flavour::Pos) prod = Flavour::Neg;
    else prod = Flavour::Pos;
  } else {
    prod = decay;
  }
  double NumEvents = weight;
  double NumTaggedEvents = 0.0;
  double NumRightTaggedEvents = 0.0;
  double NumWrongTaggedEvents = 0.0;
  double pollution = 0.0;

  // Skip untagged events
  if (pred != Flavour::Unknown)  {

    double omega = (cal) ? cal->Value(eta) : eta;

    pollution = 0.5*(1-oscWeight);

    // Calculating pi and dp
    bool correct = (prod==pred);

    if (omega < 0.5) {
      NumTaggedEvents = weight;
      if (correct)
	NumRightTaggedEvents = weight;
      else
	NumWrongTaggedEvents = weight;
    }

    // FCN Info
    TaggingResult::TagInfo info = {
      prod,
      pred,
      correct,
      hasOsc,
      eta,
      time,
      res_dilution,
      pollution,
      0.5,//omega,
      Vector(1),//dOmega,
      0.5,//pi,
      Vector(1),//dpi,
      weight
    };

    res.AddTagInfo(info);

  }

  res.Increment(NumEvents,NumTaggedEvents,
                NumRightTaggedEvents,NumWrongTaggedEvents);
                // pollution,OscDilution,OscDilutionSq,
                // observedDK,
                // observedCDK,
                // observedC2DK);

  // Check to see if we've reached the magic number
  //  static bool reserved = false;
  if (!reserved) {
    std::size_t size = res.GetTagTable().size();
    if (size == TaggingResult::PreReserveSize()) {
      double pass = TaggingResult::PreReserveSize();
      double fail = numEvents - pass;
      double frac_upper;
      std::tie(std::ignore,std::ignore,frac_upper) = EfficiencyConfidenceInterval(pass,fail,0.95);
      double upper = round(frac_upper * ExpectedNumberOfEvents);
      std::size_t newsize = static_cast<std::size_t>(upper);
      res.Reserve(newsize);
      if (Espresso::PrintHardDebugInfo) {
        std::cout << "RESERVING SPACE FOR TAGGINGRESULT #" << thiscount << ":" << std::endl;
        std::cout << "NUMBER OF EVENTS = " << numEvents << "AND NUMBER OF TAGS = " << pass << std::endl;
        std::cout << "EXPECTED NUMBER OF EVENTS = " << ExpectedNumberOfEvents << std::endl;
        std::cout << " ==> RESERVING " << newsize << " TAGS " << std::endl;
      }
      reserved = true;
    }
  }


}

const TaggingResult& TagCollector::GetResult() const {

  if (cal) {
    res.ApplyCalibration(*cal);
  } else {
    StandardCalibration sc;
    res.ApplyCalibration(sc);
  }

  return res;
}
