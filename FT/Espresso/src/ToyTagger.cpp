#include <iostream>
#include <fstream>

#include "ToyTagger.hh"

#include "Statistics.hh"
#include "RandomNumberGeneration.hh"
#include "TagCollector.hh"
#include "TaggingResult.hh"

#include <cmath>
using namespace Espresso;

// DEFAULT PDFS
const std::map<CalibrationMode, const BDecayModel>& Espresso::DefDecModel() {
  static const std::map<CalibrationMode, const BDecayModel> defmodel = {
    {CalibrationMode::ChargedBu, BDecayModel(CalibrationMode::ChargedBu)},
    {CalibrationMode::NeutralBd, BDecayModel(CalibrationMode::NeutralBd)},
    {CalibrationMode::NeutralBs, BDecayModel(CalibrationMode::NeutralBs)},
  };
  return defmodel;
}

ToyTagger::ToyTagger(CalibrationMode _mode, const Distribution& _pdf, const Calibration* _smear_cal)
  : analytic(true),
    mode(_mode),
    decModel(&Espresso::DefDecModel().at(mode)),
    pdf(&_pdf),
    bootres(nullptr),
    smear_cal(_smear_cal),
    BackgroundFraction(0.0),
    SidebandRatio(1.0),
    m_forgetResolution(false),
    verbose(false)
{
}

ToyTagger::ToyTagger(const BDecayModel& _decModel, const Distribution& _pdf, const Calibration* _smear_cal)
  : analytic(true),
    mode(_decModel.GetMode()),
    decModel(&_decModel),
    pdf(&_pdf),
    bootres(nullptr),
    smear_cal(_smear_cal),
    BackgroundFraction(0.0),
    SidebandRatio(1.0),
    m_forgetResolution(false),
    verbose(false)
{
}

ToyTagger::ToyTagger(const TaggingResult& _bootres)
  : analytic(false),
    mode(),
    decModel(nullptr),
    pdf(nullptr),
    bootres(&_bootres),
    smear_cal(nullptr),
    BackgroundFraction(0.0),
    SidebandRatio(1.0),
    m_forgetResolution(false),
    verbose(false)
{
}

void ToyTagger::SetBackgroundFraction(double _BackgroundFraction) {
  BackgroundFraction = _BackgroundFraction;
}

void ToyTagger::SetSidebandRatio(double _SidebandRatio) {
  SidebandRatio = _SidebandRatio;
}

TaggingResult ToyTagger::GetToyTaggingResult(unsigned int NumEvents, bool save) {

  std::ofstream csvtable;
  if (save)
    csvtable.open("toystudy.csv");

  TaggingResult res;
  
  if (analytic) {
    
    TagCollector tc(*decModel);
    tc.SetVerbose(verbose);
    
    for (unsigned int toy = 0; toy < NumEvents; toy++) {

      bool Bkg = (RandomNumberGeneration::Get() <= BackgroundFraction);
      bool inSideband = false;
      if (Bkg) {
	double sbProb = SidebandRatio/(SidebandRatio + 1.0);
	inSideband = (RandomNumberGeneration::Get() <= sbProb);
      }
      double sw = (inSideband) ? -1.0/SidebandRatio : 1.0;
      
      double a = decModel->GetAsymmetry();
      double p = 0.5*(1-a);
      bool initNeg = (RandomNumberGeneration::Get() <= p);
      Flavour realFlavor = (initNeg) ? Flavour::Neg : Flavour::Pos;
      
      double eta = pdf->GetRandom();
      double omega;
      if (smear_cal)
	omega = smear_cal->Value(eta,realFlavor);
      else
	omega = eta;
      bool correct = (Bkg) ? (RandomNumberGeneration::Get() < 0.5) : (RandomNumberGeneration::Get() >= omega);
      Flavour predFlavor = (initNeg) ? ((correct) ? Flavour::Neg : Flavour::Pos) : ((correct) ? Flavour::Pos : Flavour::Neg);
      
      if (save)
	csvtable << correct << ", " << (log(1-eta) - log(eta)) << "\n";
      
      double time = decModel->SampleDecayTime();
      double width = decModel->SampleResolution();
      double dtime;
      if (m_forgetResolution) {
	const ResolutionModel& rm = DefResolutionModel();
	std::unique_ptr<Distribution> resDist = rm(time,width);
	dtime = resDist->GetRandom();
      } else {
	std::unique_ptr<Distribution> resDist = decModel->GetResolutionModel()(time,width);
	dtime = resDist->GetRandom();
      }
      
      double phase = ModeFrequency.at(mode)*time;
      double phase2 = 0.5*ModeDeltaGamma.at(mode)*time;
      double oscProb = 0.5*(1-cos(phase)/cosh(phase2));
      
      bool hasOsc = (RandomNumberGeneration::Get() <= oscProb);
      Flavour decayFlavor = (initNeg) ? ((hasOsc) ? Flavour::Pos : Flavour::Neg) : ((hasOsc) ? Flavour::Neg : Flavour::Pos);
      
      tc.AddTag(decayFlavor,predFlavor,eta,sw,dtime,width);
    }
    res = tc.GetResult();

  } else {

    const TaggingResult::TagTable& table = bootres->GetTagTable();
    for (unsigned int toy = 0; toy < NumEvents; toy++) {
      auto it = RandomNumberGeneration::GetRandomIterator(table.begin(),table.end());
      if (save)
	csvtable << it->correct << ", " << (log(1-it->eta) - log(it->eta)) << "\n";
      res.AddTagInfo(*it);
    }
  }

  if (save)
    csvtable.close();
  
  return res;
}
