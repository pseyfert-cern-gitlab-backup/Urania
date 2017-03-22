#include "BDecayModel.hh"

#include "RandomNumberGeneration.hh"

using namespace Espresso;

// DEFAULT PDFS
// LIFETIME
const std::map<CalibrationMode, ExponentialDistribution>& Espresso::DefLifetimeDist() {
  static std::map<CalibrationMode, ExponentialDistribution> dist = {
    {CalibrationMode::ChargedBu, ExponentialDistribution(0.0,ModeLifetime.at(CalibrationMode::ChargedBu))},
    {CalibrationMode::NeutralBd, ExponentialDistribution(0.0,ModeLifetime.at(CalibrationMode::NeutralBd))},
    {CalibrationMode::NeutralBs, ExponentialDistribution(0.0,ModeLifetime.at(CalibrationMode::NeutralBs))}
  };
  return dist;
}

// ACCEPTANCE
const double& Espresso::DefAcceptanceCutoff() {
  static double cutoff = 0.1;
  return cutoff;
}

const Function& Espresso::DefAcceptanceFunc() {
  static Function func = [] (double tau) {
    double cutoff = Espresso::DefAcceptanceCutoff();
    if (tau < cutoff)
      return 0.0;
    else
      return 1.0;
  };
  return func;
}

// RESOLUTION
const double& Espresso::DefResolution() {
  static double res = 0.045;
  return res;
}

const DiracDeltaDistribution& Espresso::DefResolutionDist() {
  static DiracDeltaDistribution dist(DefResolution());
  return dist;
}

const ResolutionModel& Espresso::DefResolutionModel() {
  static ResolutionModel model = [] (double tau, double tauerr) {
    auto _dist = std::make_unique<NormalDistribution>(tau,tauerr);
    return _dist;
  };
  return model;
}

BDecayModel::BDecayModel(CalibrationMode _mode)
  : mode(_mode),
    m_asymmetry(0.0),
    m_AcceptanceFunc(Espresso::DefAcceptanceFunc()),
    m_LifetimeDist(nullptr),
    m_ResolutionDist(nullptr),
    m_ResolutionModel(Espresso::DefResolutionModel())
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "CONSTRUCTING BDECAYMODEL... ";
  SetLifetimeDist(Espresso::DefLifetimeDist().at(_mode));
  SetResolutionDist(Espresso::DefResolutionDist());
  if (Espresso::PrintHardDebugInfo)
    std::cout << "done" << std::endl;
}

/// Copy constructor
BDecayModel::BDecayModel(const BDecayModel& rhs)
  : mode(rhs.mode),
    m_asymmetry(rhs.m_asymmetry),
    m_AcceptanceFunc(rhs.m_AcceptanceFunc),
    m_LifetimeDist(rhs.m_LifetimeDist->clone()),
    m_ResolutionDist(rhs.m_ResolutionDist->clone()),
    m_ResolutionModel(rhs.m_ResolutionModel)
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "COPYING BDECAYMODEL" << std::endl;
}

/// Move constructor
BDecayModel::BDecayModel(BDecayModel&& rhs)
  : mode(std::move(rhs.mode)),
    m_asymmetry(std::move(rhs.m_asymmetry)),
    m_AcceptanceFunc(std::move(rhs.m_AcceptanceFunc)),
    m_LifetimeDist(std::move(rhs.m_LifetimeDist)),
    m_ResolutionDist(std::move(rhs.m_ResolutionDist)),
    m_ResolutionModel(std::move(rhs.m_ResolutionModel))
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "MOVING BDECAYMODEL" << std::endl;
}

BDecayModel::~BDecayModel() 
{
  if (Espresso::PrintHardDebugInfo)
    std::cout << "DESTROYING BDECAYMODEL" << std::endl;
}

double BDecayModel::SampleDecayTime() const {
  double tau, acc, thresh;
  do {
    tau = m_LifetimeDist->GetRandom();
    acc = m_AcceptanceFunc(tau);
    thresh = RandomNumberGeneration::Get();
  } while (acc < thresh);
  return tau;
}

double BDecayModel::SampleResolution() const {
  return m_ResolutionDist->GetRandom();
}

const ResolutionModel& BDecayModel::GetResolutionModel() const {
  return m_ResolutionModel;
}

// std::unique_ptr<Distribution> BDecayModel::GetResolutionDist(double t, double w) const {
//   std::cout << "time = " << t << " and width = " << w << std::endl;
//   return m_ResolutionModel(t,w);
// }
