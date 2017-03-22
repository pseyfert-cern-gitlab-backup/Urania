#include <algorithm>
#include <cmath>

#include "TaggingResultImpl.hh"

#include "TagCollector.hh"
#include "TaggingResultMetrics.hh"
#include "Statistics.hh"
#include "RandomNumberGeneration.hh"

using namespace Espresso;

// CONSTRUCTORS

TaggingResultImpl::TaggingResultImpl()
  : table(),
    isTableSorted_eta(false),
    isTableSorted_pi(false),
    isTableSorted_tau(false),
    NumEvents(0),
    NumTaggedEvents(0),
    NumRightTaggedEvents(0),
    NumWrongTaggedEvents(0),
    dilution(0.0),
    dilution_err(0.0),
    dilution_calerr(0.0)
{
  table.reserve(TaggingResultImpl::pre_reserve);
}

void TaggingResultImpl::sortByEta(bool force) const {
  if (!isTableSorted_eta or force) {
    auto comp = [] (const TaggingResult::TagInfo& lhs, const TaggingResult::TagInfo& rhs) {
      double lhseta = lhs.eta;
      double rhseta = rhs.eta;
      return lhseta < rhseta;
    };
    std::sort(table.begin(),table.end(),comp);
    isTableSorted_eta = true;
    isTableSorted_pi = false;
    isTableSorted_tau = false;
  }
}

void TaggingResultImpl::sortByPi(bool force) const {
  if (!isTableSorted_pi or force) {
    auto comp = [] (const TaggingResult::TagInfo& lhs, const TaggingResult::TagInfo& rhs) {
      double lhspi = lhs.pi;
      double rhspi = rhs.pi;
      return lhspi > rhspi; // reverse sorted since pi ~ 1 - eta; fewer operations
    };
    std::sort(table.begin(),table.end(),comp);
    isTableSorted_eta = false;
    isTableSorted_pi = true;
    isTableSorted_tau = false;
  }
}

void TaggingResultImpl::sortByTau(bool force) const {
  if (!isTableSorted_tau or force) {
    auto comp = [] (const TaggingResult::TagInfo& lhs, const TaggingResult::TagInfo& rhs) {
      double lhstau = lhs.tau;
      double rhstau = rhs.tau;
      return lhstau < rhstau;
    };
    std::sort(table.begin(),table.end(),comp);
    isTableSorted_eta = false;
    isTableSorted_pi = false;
    isTableSorted_tau = true;
  }
}

void TaggingResultImpl::sortByTau(double period) const {
  auto comp = [period] (const TaggingResult::TagInfo& lhs, const TaggingResult::TagInfo& rhs) {
    double lhstau = fmod(lhs.tau,period);
    double rhstau = fmod(rhs.tau,period);
    return lhstau < rhstau;
  };
  std::sort(table.begin(),table.end(),comp);
  isTableSorted_eta = false;
  isTableSorted_pi = false;
  isTableSorted_tau = true;
}

double TaggingResultImpl::EtaQuantile(double p) const 
{
  if (table.size()==0) return 0.5;
  auto value = [] (const TaggingResult::TagInfo& info) { return info.eta; };
  double q = quantile<TaggingResult::TagInfo>(p,table,value);
  return q;
}

std::vector<double> TaggingResultImpl::EtaQuantiles(int numGroups) const 
{
  if (table.size()==0) return std::vector<double>();
  auto value = [] (const TaggingResult::TagInfo& info) { return info.eta; };
  std::vector<double> qs = quantiles<TaggingResult::TagInfo>(numGroups,table,value);
  return qs;
}

void TaggingResultImpl::ApplyCalibration(const Calibration& cal) {
  
  if (table.size() == 0) return;
  
  for (auto& it : table) {
    
    // Calculate value
    double eta = it.eta;
    double omega = cal.Value(eta);
    double omegaGiven = cal.Value(eta,it.flavour);
    double omegaOscillated = cal.Value(eta,Opposite(it.flavour));
    double pi = (1-omegaGiven)*(1-it.pollution) + omegaOscillated*it.pollution;
      
    // Calculate derivative
    Vector dOmega = cal.Derivative(eta);
    Vector dOmegaGiven = cal.Derivative(eta,it.flavour);
    Vector dOmegaOscillated = cal.Derivative(eta,Opposite(it.flavour));
    Vector dpi = -1*dOmegaGiven*(1-it.pollution) + dOmegaOscillated*it.pollution;
    
    // Update
    it.omega = omega;
    it.domega = dOmega;
    it.pi = pi;
    it.dpi = dpi;
  }
  
  double count = 0.0;
  double countr = 0.0;
  double countw = 0.0;
  double eD2 = 0.0;
  double eD4 = 0.0;
  
  Vector dED2(table[0].domega.size());
  for (const auto& it : table) 
  {
    if (it.omega < 0.5) {
      double D = 1-2*it.omega;
      //D *= it.res_dilution;
      double D2 = D*D;
      eD2 += it.W*D2;
      eD4 += it.W*D2*D2;
      dED2 += -4.0*it.W*D*it.domega;
      count += it.W;
      if (it.correct)
        countr += it.W;
      else
        countw += it.W;
    }
  }
  
  NumTaggedEvents = count;
  NumRightTaggedEvents = countr;
  NumWrongTaggedEvents = countw;
  eD2 /= count;
  eD4 /= count;
  dED2 /= count;
  double var = eD4 - eD2*eD2;
  
  dilution = eD2;
  dilution_err = sqrt(var/(count-1));
  dilution_calerr = sqrt(dED2* (cal.GetCovarianceMatrix() * dED2));

  sortByPi(true);
}

TaggingResult::BinTable TaggingResultImpl::CreateBinTable(int numGroups) const {
  TaggingResult::BinTable bt(numGroups);
  if (table.size() == 0)
    return bt;
  sortByEta();
  auto value = [] (const TaggingResult::TagInfo& info) { return info.eta; };
  std::vector<double> qs = quantiles<TaggingResult::TagInfo>(numGroups,table,value);
  TaggingResult::TagTable::iterator it = table.begin();
  for (int group = 0; group <= numGroups; group++) {
    double q = qs[group];
    if (group > 0) {
      double eta = 0;
      double asymm = 0;
      double sumW = 0;
      double sumW2 = 0;
      double osc_dilution_sq = 0;
      while(it != table.end() && (*it).eta <= q) {
        double etak = (*it).eta;
        double wk = (*it).W;
        bool correct = (*it).correct;
        double pk = (*it).pollution;
        double dilk = 1-2*pk;
        eta += etak*wk;
        if (correct)
          asymm += wk*dilk;
        else
          asymm -= wk*dilk;
        sumW += wk;
        sumW2 += wk*wk;
        osc_dilution_sq += wk*dilk*dilk;
        ++it;
      }
      eta /= sumW;
      osc_dilution_sq /= sumW;
      asymm /= sumW;
      asymm /= osc_dilution_sq;
      double numeff = sumW*sumW/sumW2 * osc_dilution_sq;
      double rFrac = 0.5*(1+asymm);
      double wFrac = 0.5*(1-asymm);
      bt[group-1].lowEdge = qs[group-1];
      bt[group-1].highEdge = qs[group];
      bt[group-1].eta = eta;
      bt[group-1].numRight = rFrac * numeff;
      bt[group-1].numWrong = wFrac * numeff;
    }
  }
  return bt;
}

TaggingResult::BinTable TaggingResultImpl::CreateKernelSmoothedBinTable(TaggingResult::SmoothingOptions opts) const {
  int N = opts.num_points;
  double sigma = opts.sigma;
  
  TaggingResult::BinTable bt(N);
  if (table.size() == 0)
    return bt;
  sortByEta();

  int num = table.size();
  double min = table[0].eta;
  double max = table[num-1].eta;
  double delta = (max-min)/(double(N-1));

  int kmin = 0;

  for (int i = 0; i < N; i++) {

    double x = min + i*delta;
    double asymm = 0;
    double sumw = 0.0;
    double sumw2 = 0.0;
    double osc_dilution_sq = 0;

    for (int k = kmin; k < num; k++) {

      const TaggingResult::TagInfo& it = table[k];
      
      // Calculate value
      double eta = it.eta;

      // Skip
      if (eta < x - 4*sigma) {
       	continue;
	kmin++; // the next one has to start at least after this
      } else if (eta > x + 4*sigma) {
       	break;
      }

      double z = (eta-x)/sigma;
      double kernel = exp(-0.5*z*z);

      double dil = 1-2*it.pollution;
      double w = it.W*kernel;
      if (it.correct)
        asymm += w*dil;
      else
        asymm -= w*dil;
      sumw += w;
      sumw2 += w*w;
      osc_dilution_sq += w*dil*dil;
    }

    osc_dilution_sq /= sumw;
    asymm /= sumw;
    asymm /= osc_dilution_sq;
    double neff = sumw*sumw/sumw2 * osc_dilution_sq;
    double frac = 0.5*(1-asymm);
    double numPass = frac*neff;
    double numFail = neff-numPass;
    bt[i].lowEdge = x - 0.5*delta;
    bt[i].highEdge = x + 0.5*delta;
    bt[i].eta = x;
    bt[i].numRight = numFail;
    bt[i].numWrong = numPass;
  }
  return bt;
}

TaggingResult::BinTable TaggingResultImpl::CreateCalibratedBinTable(int numGroups) const {
  TaggingResult::BinTable bt(numGroups);
  if (table.size() == 0)
    return bt;
  sortByPi();
  auto value = [] (const TaggingResult::TagInfo& info) { return info.pi; }; // -1 because it is reverse sorted
  std::vector<double> qs = quantiles<TaggingResult::TagInfo>(numGroups,table,value);
  TaggingResult::TagTable::iterator it = table.begin();
  for (int group = 0; group <= numGroups; group++) {
    double q = qs[group];
    if (group > 0) {
      double eta = 0;
      double w = 0;
      double nr = 0;
      double nw = 0;
      double sumW = 0;
      double sumW2 = 0;
      while(it != table.end() && (*it).pi >= q) {
        double etak = 1 - (*it).pi;
        double wk = (*it).W;
        bool correct = (*it).correct;
        eta += etak*wk;
        w += wk;
        if (correct)
          nr += wk;
	else
          nw += wk;
        sumW += wk;
        sumW2 += wk*wk;
        ++it;
      }
      double numeff = sumW*sumW/sumW2;
      bt[group-1].lowEdge = qs[group-1];
      bt[group-1].highEdge = qs[group];
      bt[group-1].eta = eta / w;
      bt[group-1].numRight = nr/(nr+nw) * numeff;
      bt[group-1].numWrong = nw/(nr+nw) * numeff;
    }
  }
  return bt;
}

TaggingResult::TauTable TaggingResultImpl::CreateTauTable(int numGroups, TaggingResult::WrappingOptions wopts) const {
  double period = wopts.period;
  double tmax = wopts.maximum;
  
  TaggingResult::TauTable tt(numGroups);

  if (table.size() == 0)
    return tt;
  if (period != 0.0)
    sortByTau(period);
  else
    sortByTau();

  auto mtau = [period] (double tau) {
    if (period != 0) 
      return fmod(tau,period);
    else
      return tau;
  };

  // auto value = [] (const TaggingResult::TagInfo& info) { return info.tau; };
  // std::vector<double> qs = quantiles<TaggingResult::TagInfo>(numGroups,table,value);
  int num = table.size();
  double min = mtau(table[0].tau);
  double max = (tmax == -1) ? mtau(table[num-1].tau) : mtau(tmax);
  double delta = (max-min)/(double(numGroups));

  TaggingResult::TagTable::iterator it = table.begin();
  for (int group = 1; group <= numGroups; group++) {
    //double q = qs[group];
    BDecayModel bdm(CalibrationMode::ChargedBu);
    TagCollector tc(bdm);
    double tau = 0;
    double sumw = 0;
    while(it != table.end() && mtau((*it).tau) <= min+group*delta) {
      double tauk = mtau((*it).tau);
      double omegak = (*it).omega;
      double D = (1-2*omegak)*(*it).res_dilution;
      double eff_omega = 0.5*(1-D);
      double wk = (*it).W;
      bool correct = (*it).correct xor (*it).oscillated;
      if (correct)
        tc.AddTag(Flavour::Pos,Flavour::Pos,eff_omega,wk);
      else
        tc.AddTag(Flavour::Pos,Flavour::Neg,eff_omega,wk);
      tau += tauk*wk;
      sumw += wk;
      ++it;
    }
    tau /= sumw;
    double asymm, err;
    TaggingResult tr(tc.GetResult());
    calcAsymmetry(asymm,err,tr.GetTagTable(),nullptr);
    tt[group-1].lowEdge = min+(group-1)*delta;//qs[group-1];
    tt[group-1].highEdge = min+group*delta;//qs[group];
    tt[group-1].tau = tau;
    tt[group-1].asymm = asymm;
    tt[group-1].err = err;
  }
  return tt;
}

TaggingResult::TauTable TaggingResultImpl::CreateKernelSmoothedTauTable(TaggingResult::SmoothingOptions opts,
                                                                        TaggingResult::WrappingOptions wopts) const {
  
  int N = opts.num_points;
  double sigma = opts.sigma;
  double period = wopts.period;
  double tmax = wopts.maximum;

  TaggingResult::TauTable tt(N);
  if (table.size() == 0)
    return tt;
  if (period != 0)
    sortByTau(period);
  else
    sortByTau();

  auto mtau = [period] (double tau) {
    if (period != 0) 
      return fmod(tau,period);
    else
      return tau;
  };

  int num = table.size();
  double min = mtau(table[0].tau);
  double max = (tmax == -1) ? mtau(table[num-1].tau) : mtau(tmax);
  sigma *= std::abs(max-min);
  double delta = (max-min)/(double(N-1));

  int kmin = 0;

  for (int i = 0; i < N; i++) {

    double x = min + i*delta;
    double asymm = 0;
    double sumd2 = 0;

    /*
      Haiku:
      with max likelihood
      it could be more accurate
      but its much too slow
      BDecayModel bdm(CalibrationMode::ChargedBu);
      TagCollector tc(bdm);
    */

    for (int k = kmin; k < num; k++) {

      const TaggingResult::TagInfo& it = table[k];
      
      // Calculate value
      double tau = mtau(it.tau);

      // Skip
      if (tau < x - 4*sigma) {
       	continue;
        kmin++; // the next one has to start at least after this
      } else if (tau > x + 4*sigma) {
       	break;
      }

      double z = (tau-x)/sigma;
      double kernel = exp(-0.5*z*z);

      double omegak = it.omega;
      double wk = it.W*kernel;
      bool correct = it.correct xor it.oscillated;
      /*
	if (correct)
        tc.AddTag(Flavour::Pos,Flavour::Pos,omegak,wk);
	else
        tc.AddTag(Flavour::Pos,Flavour::Neg,omegak,wk);
      */
      double dilk = 1-2*omegak;
      dilk *= it.res_dilution;
      if (correct)
        asymm += wk*dilk;
      else
        asymm -= wk*dilk;
      sumd2 += wk*dilk*dilk;
    }
    /*
      double asymm, err;
      TaggingResult tr(tc.GetResult());
      calcAsymmetry(asymm,err,tr.GetTagTable(),nullptr);
    */
    asymm /= sumd2;
    tt[i].lowEdge = x - 0.5*delta;
    tt[i].highEdge = x + 0.5*delta;
    tt[i].tau = x;
    tt[i].asymm = asymm;
    tt[i].err = 1.0/sqrt(sumd2);
  }
  return tt;
}

const TaggingResult::TagTable& TaggingResultImpl::GetTagTable() const {
  return table;
}

void TaggingResultImpl::Reserve(std::size_t t) {
  table.reserve(t);
}

void TaggingResultImpl::AddTagInfo(const TaggingResult::TagInfo& info) 
{
  table.push_back(info);
}


void TaggingResultImpl::Increment(double _NumEvents, double _NumTaggedEvents,
                                  double _NumRightTaggedEvents, double _NumWrongTaggedEvents)
{
  
  NumEvents += _NumEvents;
  NumTaggedEvents += _NumTaggedEvents;
  NumRightTaggedEvents += _NumRightTaggedEvents;
  NumWrongTaggedEvents += _NumWrongTaggedEvents;
  SumW2 += _NumEvents*_NumEvents;
}

std::tuple<double,double,double> TaggingResultImpl::DilutionSquared() const
{
  return std::make_tuple(dilution,dilution_err,dilution_calerr);
}

