// Include files
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <ctime>

#include "TMath.h" // replace

// local
#include "TaggingResultMetrics.hh"
#include "Statistics.hh"
#include "LikelihoodMaximizer.hh"
#include "LikelihoodSolver.hh"
#include "RootFinder.hh"
#include "GLMPolynomial.hh"
#include "GLMBSpline.hh"
#include "GLMNSpline.hh"

namespace Espresso
{

  bool UseLikelihood = true;

  UncertainValue TaggingRate(const TaggingResult& res, double trueNum, double trueNum_eff)
  {
    double num = (trueNum < 0) ? res.GetNumEvents() : trueNum;
    double effnum = (trueNum_eff < 0) ? res.GetEffNumEvents() : trueNum_eff;
    double rate = res.GetNumTaggedEvents() / num;
    double ttag = res.GetNumTaggedEvents();
    double utag = num - ttag;
    double err = sqrt(ttag*utag / effnum) / num;
    return std::make_tuple(rate,err,0.0);
  }

  UncertainValue MistagRate(const TaggingResult& res)
  {
    double ttag = res.GetNumTaggedEvents();
    double rtag = res.GetNumRightTaggedEvents();
    double wtag = res.GetNumWrongTaggedEvents();
    double tag_omega = wtag/ttag;
    double tag_omega_err = sqrt( rtag*wtag / ttag) / ttag;
    return std::make_tuple(tag_omega,tag_omega_err,0.0);
  }

  // UncertainValue WeightTaggingPower(const TaggingResult& res, double trueNum, double trueNum_eff)
  // {
  //   double tag_rate, tag_rate_err;
  //   std::tie(tag_rate,tag_rate_err,std::ignore) = TaggingRate(res,trueNum,trueNum_eff);
  //   double eCD = res.GetSignedMoment(1);
  //   double eCD_err = res.GetSignedMomentError(1);
  //   double eD2 = res.GetUnsignedMoment(2);
  //   double eD2_err = res.GetUnsignedMomentError(2);
  //   double cov = res.GetUSCovariance(2,1);
  //   double tag_power_actual = tag_rate*eCD*eCD/eD2;
  //   double tag_power_actual_err = tag_power_actual * sqrt(pow(tag_rate_err/tag_rate,2) +
  //                                                         pow(2*eCD_err/eCD,2) +
  //                                                         pow(eD2_err/eD2,2)
  //                                                         -4*cov/(eCD*eD2));
  //   return std::make_tuple(tag_power_actual,tag_power_actual_err,0.0);
  // }

  UncertainValue TaggingPower(const TaggingResult& res, double trueNum, double trueNum_eff)
  {
    double eD2, err, calerr;
    std::tie(eD2,err,calerr) = DilutionSquared(res);
    double tag_rate, tag_rate_err;
    std::tie(tag_rate, tag_rate_err, std::ignore) = TaggingRate(res, trueNum, trueNum_eff);
    double tag_power = tag_rate*eD2;
    double tag_power_err = tag_power * sqrt(pow(tag_rate_err/tag_rate,2) + pow(err/eD2,2));
    double tag_power_calerr = tag_rate*calerr;
    return std::make_tuple(tag_power,tag_power_err,tag_power_calerr);
  }

  UncertainValue EffectiveMistag(const TaggingResult& res)
  {
    double eD2, err, calerr;
    std::tie(eD2,err,calerr) = DilutionSquared(res);
    double effom = 0.5*(1-sqrt(eD2));
    double effom_err = err/(4.0*sqrt(eD2));
    double effom_calerr = calerr/(4.0*sqrt(eD2));
    return std::make_tuple(effom,effom_err,effom_calerr);
  }

  UncertainValue DilutionSquared(const TaggingResult& tag)
  {
    return tag.DilutionSquared();
  }


  GLMCalibration TaggingCalibrationCalculator(const TaggingResult& res, const GLMModel& glm, Regression::LinkType _L,
					      TaggingLikelihood::CovarianceCorrectionMethod method,
					      bool useNewtonRaphson, bool verbose)
  {

    // CALIBRATION
    TaggingLikelihood lf(res,glm,_L);
    std::unique_ptr<Solver> sc;

    if (useNewtonRaphson) {
      std::cout << "SOLVING VIA GSL NEWTON-RAPHSON... " << std::endl;
      sc = std::make_unique<LikelihoodSolver>(lf);
    } else {
      std::cout << "SOLVING VIA MINUIT MAXIMIZATION... " << std::endl;
      sc = std::make_unique<LikelihoodMaximizer>(lf);
    }

    std::clock_t gsl_start = std::clock();
    sc->Solve();
    std::clock_t gsl_stop = std::clock();
    double gsl_time = (gsl_stop-gsl_start) / static_cast<double>(CLOCKS_PER_SEC);
    std::cout << gsl_time << " seconds elapsed.\n\n";

    Vector all_coeffs = sc->GetVals();
    Matrix all_covariance = lf.GetCovarianceMatrix(all_coeffs.GetArray(),method);

    Vector coeffs(glm.NumParams());
    Vector delta_coeffs(glm.NumParams());
    Matrix covariance(glm.NumParams(),glm.NumParams());
    Matrix delta_covariance(glm.NumParams(),glm.NumParams());
    Matrix cross_covariance(glm.NumParams(),glm.NumParams());
    for (unsigned int i = 0; i < glm.NumParams(); i++) {
      coeffs[i] = all_coeffs[i];
      delta_coeffs[i] = all_coeffs[i+glm.NumParams()];
      for (unsigned int j = 0; j < glm.NumParams(); j++) {
	covariance(i,j) = all_covariance(i,j);
	delta_covariance(i,j) = all_covariance(i+glm.NumParams(),j+glm.NumParams());
	cross_covariance(i,j) = all_covariance(i,j+glm.NumParams());
      }
    }

    return GLMCalibration(glm,_L,
			  coeffs,delta_coeffs,
			  covariance,delta_covariance,cross_covariance);


  }

  GLMCalibration TaggingCalibrationCalculator(const TaggingResult& res, int degree, GLMModel::GLMType T, Regression::LinkType L,
					       TaggingLikelihood::CovarianceCorrectionMethod method,
                                               bool useNewtonRaphson, bool verbose)
  {
    std::unique_ptr<GLMModel> pglm = GLMModel::CreateModel(T,degree,res,L);
    return TaggingCalibrationCalculator(res,*pglm,L,method,useNewtonRaphson,verbose);
  }

  void calcAsymmetryLikelihood(double& asymm, double& err, const TaggingResult::TagTable& table, const Calibration* cal) {
    FDF dloglik = [&] (double x, double* dll, double* ddll) {
      /*
	log L = log[(1+TDA/2)]
	and D log L / dA = sum (TD/(1+TD*A))
	But, can go outside range [-1,1]
	(1) Change variables to x = A/sqrt(1-A^2)
	-> A = x/sqrt(1+x^2)
	-> d/dx of term is (1-a^2)^3/2 * {{ TD/(1+a*TD) }}
	-> d^2/dx^2 of term is -(1-a^2)^2 * {{ (D^2(1+2a^2) + 3*TD*a)/(1+TD*a)^2 }}
	-> if |A| > 1, p = 0, dp = inf, ddp = inf
	(2) Add Jeffrey's prior 1/sqrt[p*(1-p)]
	-> = 2/sqrt(1-A^2) = 2 sqrt(1+x^2)
	-> log = log(2) + 1/2 log (1+x^2)
	-> d/dx = x/(1+x^2) = a*sqrt(1-a^2)
	-> d^2/dx^2 = 1-3*a^2 + 2*a^4
      */
      double sx = 1.0/sqrt(1+x*x);
      double a = x*sx;
      double a2 = a*a;
      double a4 = a2*a2;
      double f = 1-a2;
      double sf = sqrt(f);
      if (dll) *dll = 0;
      if (ddll) *ddll = 0;
      for (const auto& it : table) {
	int T = (it.predFlavour == Flavour::Pos) ? +1 : -1;
	double D = 1-2*it.omega;
	D *= it.res_dilution;
	double TD = T*D;
	double TDA = TD*a;
	double den = 1.0/(1.0+TDA);
	if (dll) *dll += it.W*TD*den;
	if (ddll) *ddll += it.W*(D*D*(1+2*a2)+3*TDA)*den*den;
      }
      if (dll) *dll *= sf*sf*sf;
      if (ddll) *ddll *= -1*f*f;
      if (dll) *dll += a*sf;
      if (ddll) *ddll += 1-3*a2+2*a4;
    };
    RootFinder alg(dloglik,SolutionMethod::Steffenson);
    alg.SetInitialGuess(0.0);
    alg.Solve();
    double x = alg.GetSolution();
    double invvar;
    dloglik(x,nullptr,&invvar);
    double xerr = 1.0/sqrt(-1*invvar);

    // transform
    double sx = 1.0/sqrt(1+x*x);
    asymm = x*sx;
    err = xerr*sx*sx*sx;
    //std::cout << "x = " << x << " +/- " << xerr << " => asymm = " << asymm << " +/- " << err << std::endl;
  }

  void calcAsymmetry(double& asymm, double& err, const TaggingResult::TagTable& table, const Calibration* cal) {

    double num = 0.0;
    double den = 0.0; // also the error, also = tagging power * numEvents
    double count = 0.0;

    for (const auto& it : table) {

      // Calculate value
      double eta = it.eta;
      double omega, omegaDelta;
      if (cal) {
 	omega = cal->Value(eta);
	omegaDelta = cal->Value(eta,Flavour::Pos) - cal->Value(eta,Flavour::Neg);
      } else {
 	omega = eta;
 	omegaDelta = 0.0;
      }
      double D = 1-2*omega;
      D *= it.res_dilution;
      int F = (it.predFlavour == Flavour::Pos) ? +1 : -1;
      double z = (1-F*omegaDelta);
      double x = D/z;
      count += it.W;
      num += it.W*F*x;
      den += it.W*x*x;
    }
    err = 1.0/sqrt(den);
    num /= count;
    den /= count;
    asymm = num/den;
  }

  Espresso::ConfidenceInterval KernelSmoothedOmega(double x, const TaggingResult& tag,
						   double sigma, const Calibration* cal) {


    tag.sortByEta();
    const TaggingResult::TagTable& table = tag.GetTagTable();

    double count = 0.0;
    double sumw = 0.0;
    double sumw2 = 0.0;

    for (const auto& it : table) {

      // Calculate value
      double eta = it.eta;
      double omega;
      if (cal) {
	omega = cal->Value(eta);
      } else {
	omega = eta;
      }

      // Skip
      if (omega < x - 4*sigma)
       	continue;
      else if (omega > x + 4*sigma)
       	break;

      double z = (omega-x)/sigma;
      double kernel = exp(-0.5*z*z);

      int y = (it.correct) ? 0 : 1;
      count += it.W*kernel*y;
      double w = it.W*kernel;
      sumw += w;
      sumw2 += w*w;
    }

    double frac = count / sumw;
    double neff = sumw*sumw/sumw2;
    double numPass = frac*neff;
    double numFail = neff-numPass;
    return Espresso::EfficiencyConfidenceInterval(numPass,numFail);
  }

  // TaggingResult::BinTable createBinnedCalibratedTagTable(const TaggingResult& tag, int numGroups) {
  //   TaggingResult::BinTable bt(numGroups);
  //   auto value = [] (const CalibratedTagInfo& info) { return info.pi; };
  //   std::vector<double> qs = quantiles<CalibratedTagInfo>(numGroups,caltable,value);
  //   CalibratedTagTable::const_iterator it = caltable.begin();
  //   for (int group = 0; group <= numGroups; group++) {
  //     double p = static_cast<double>(group)/numGroups;
  //     double q = qs[group];
  //     //std::cout << group << ": " << p << "% => q = " << q;
  //     if (group > 0) {
  //       double eta = 0;
  //       double w = 0;
  //       double nr = 0;
  //       double nw = 0;
  //       double sumW = 0;
  //       double sumW2 = 0;
  //       while(it != caltable.end() && (*it).pi <= q) {
  //         double etak = 1 - (*it).pi;
  //         double wk = (*it).W;
  //         bool correct = (*it).correct;
  //         eta += etak*wk;
  //         w += wk;
  //         if (correct)
  //           nr += wk;
  //         else
  //           nw += wk;
  //         sumW += wk;
  //         sumW2 += wk*wk;
  //         ++it;
  //       }
  //       bt[group-1].lowEdge = qs[group-1];
  //       bt[group-1].highEdge = qs[group];
  //       bt[group-1].eta = eta / w;
  //       //std::cout << " and eta = " << eta / w << std::endl;
  //       bt[group-1].numRight = nr;
  //       bt[group-1].numWrong = nw;
  //       bt[group-1].numEff = sumW*sumW/sumW2;
  //     }
  //   }
  //   return bt;
  // }

  double GroupedDevianceTest(const TaggingResult::BinTable& table, bool PValue, bool selfCalibrated, int numParams) {
    double D = 0; // or G2
    for (auto bin : table) {
      double predNumRight = (1-bin.eta)*(bin.numRight+bin.numWrong);
      double predNumWrong = bin.eta*(bin.numRight+bin.numWrong);
      double a = bin.numRight*log(bin.numRight/predNumRight);
      double b = bin.numWrong*log(bin.numWrong/predNumWrong);
      D += 2*(a+b);
    }
    if (PValue) {
      double dof = table.size();
      if (selfCalibrated) dof -= numParams;
      double p = TMath::Prob(D,dof);
      return p;
    } else {
      return D;
    }
  }

  double GroupedPearsonTest(const TaggingResult::BinTable& table, bool PValue, bool selfCalibrated, int numParams) {
    double X2 = 0;
    for (auto bin : table) {
      double predNumWrong = bin.eta*(bin.numRight+bin.numWrong);
      double resid = bin.numWrong - predNumWrong;
      double var = bin.eta*(1-bin.eta)*(bin.numRight+bin.numWrong);
      X2 += resid*resid/var;
    }
    if (PValue) {
      double dof = table.size();
      if (selfCalibrated) dof -= numParams;
      double p = TMath::Prob(X2,dof);
      return p;
    } else {
      return X2;
    }
  }

  Matrix InformationMatrix(const TaggingResult::TagTable& table) {

    int num = table[0].dpi.size();
    Matrix fisher(num,num);

    for (const auto& it : table) {
      double ppinv = it.pi*(1-it.pi);
      Matrix mtemp(num,num);
      for (int k = 0; k < num; k++) {
        for (int l = 0; l < num; l++) {
          mtemp(k,l) = it.dpi[k]*it.dpi[l]/ppinv;
        }
      }
      fisher += it.W*mtemp;
    }

    return fisher;
  }

  Vector GenericScoreVector(const TaggingResult::TagTable& table, std::function<double(bool,double)> metric) {

    int num = table[0].dpi.size();
    Vector score(num);

    for (const auto& it : table) {
      Vector grad(num);
      for (unsigned int k = 0; k < num; k++) {
        double pip = it.dpi[k];
        grad(k) = pip*(metric(true,it.pi)-metric(false,it.pi));
      }
      score += it.W*grad;
    }

    return score;
  }

  // CalibratedTagTable getCalibratedTagTable(const TaggingResult::TagTable& table, const Calibration* cal, bool useDeltas) {

  //   int num = 1;
  //   if (cal) {
  //     if (useDeltas) num = 2*(cal->NumParams());
  //     else num = cal->NumParams();
  //   }

  //   CalibratedTagTable caltable;
  //   caltable.reserve(table.size());

  //   for (const auto& it : table) {

  //     // Calculate correct?
  //     bool correct = it.correct;

  //     // Calculate value
  //     double eta = it.eta;
  //     double omega = eta;
  //     if (cal) {
  //       if (useDeltas) omega = cal->Value(eta,it.flavour);
  //       else omega = cal->Value(eta);
  //     }

  //     double pC = 1-it.pollution;//0.5*(1+it.Dosc);
  //     double pi = iff(1-omega,pC);

  //     // Calculate derivative
  //     Vector dpi(num);
  //     if (cal) {
  //       if (useDeltas) dpi = cal->Derivative(eta,it.flavour);
  //       else dpi = cal->Derivative(eta);
  //     } else {
  //       dpi[0] = 1.0;
  //     }
  //     for (unsigned int k = 0; k < num; k++) {
  //       dpi[k] = -1*dpi[k]*(2*pC-1);
  //     }

  //     // Append
  //     caltable.push_back({correct,pi,dpi,it.W});

  //   }

  //   // Sort
  //   auto comp = [] (const CalibratedTagInfo& lhs, const CalibratedTagInfo& rhs) {
  //     return lhs.pi < rhs.pi;
  //   };
  //   std::sort(caltable.begin(),caltable.end(),comp);

  //   // Return
  //   return caltable;

  // }

  double GenericMetric(const TaggingResult::TagTable& table, std::function<double(bool,double)> metric, bool selfCalibrated)
  {

    double difference = 0.0;
    double variance = 0.0; // to be reduced by a quadratic form

    for (const auto& it : table)
    {
      double t = metric(true,it.pi);
      double f = metric(false,it.pi);
      double obs = (it.correct) ? t : f;
      double exp = it.pi*t + (1-it.pi)*f;
      double diff = obs - exp;
      double var = it.pi*(t-exp)*(t-exp) + (1-it.pi)*(f-exp)*(f-exp);
      difference += it.W*diff;
      variance += it.W*var;
    }

    if (selfCalibrated) {
      Matrix fisher = InformationMatrix(table);
      Vector score = GenericScoreVector(table, metric);
      Vector scorep = fisher.LinearSolve(score); // fisher^-1 * score
      variance -= score * scorep;
    }

    if (variance > 0) {
      double z = (difference)/sqrt(variance);
      return z;
    } else {
      return 0;
    }
  }


  double UngroupedDevianceTest(const TaggingResult& tag, bool PValue, bool selfCalibrated) {

    auto deviance = [] (bool c, double p) {
      if (c)
        return -2*log(p);
      else
        return -2*log(1-p);
    };
    double z = GenericMetric(tag.GetTagTable(),deviance,selfCalibrated);
    if (PValue) {
      double p = TMath::Erf(std::fabs(z)/sqrt(2.0));
      return p;
    } else {
      return z;
    }
  }

  double UngroupedPearsonTest(const TaggingResult& tag, bool PValue, bool selfCalibrated) {
    auto pearson = [] (bool c, double p) {
      double den = p*(1-p);
      if (c)
        return (1-p)*(1-p)/den;
      else
        return p*p/den;
    };
    double z = GenericMetric(tag.GetTagTable(),pearson,selfCalibrated);
    if (PValue) {
      double p = TMath::Erf(std::fabs(z)/sqrt(2.0));
      return p;
    } else {
      return z;
    }
  }

  double UngroupedCressieReadTest(const TaggingResult& tag, bool PValue, bool selfCalibrated) {
    auto cressie_read = [] (bool c, double p) {
      double den = p*(1-p);
      if (c)
        return 9.0/5.0*(pow(p,-2.0/3.0)-1);
      else
        return 9.0/5.0*(pow(1-p,-2.0/3.0)-1);
    };
    double z = GenericMetric(tag.GetTagTable(),cressie_read,selfCalibrated);
    if (PValue) {
      double p = TMath::Erf(std::fabs(z)/sqrt(2.0));
      return p;
    } else {
      return z;
    }
  }

  double UngroupedSTest(const TaggingResult& tag, bool PValue, bool selfCalibrated) {

    auto chch = [] (bool c, double p) {
      if (c)
        return (1-p)*(1-p);
      else
        return p*p;
    };
    double z = GenericMetric(tag.GetTagTable(),chch,selfCalibrated);
    if (PValue) {
      double p = TMath::Erf(std::fabs(z)/sqrt(2.0));
      return p;
    } else {
      return z;
    }
  }

  double Deviance(const TaggingResult& tag) {
    double deviance = 0.0;
    double sumW = 0.0;
    double sumW2 = 0.0;
    const TaggingResult::TagTable& table = tag.GetTagTable();
    for (const auto& it : table) {
      sumW += it.W;
      sumW2 += it.W*it.W;
      if (it.correct)
        deviance += -2*log(it.pi)*it.W;
      else
        deviance += -2*log(1-it.pi)*it.W;
    }
    deviance *= sumW/sumW2; // essentially yuehong's correction
    return deviance;
  }

  double BrierScore(const TaggingResult& tag) {
    double brier = 0.0;
    double sumW = 0.0;
    double sumW2 = 0.0;
    const TaggingResult::TagTable& table = tag.GetTagTable();
    for (const auto& it : table) {
      sumW += it.W;
      sumW2 += it.W*it.W;
      if (it.correct)
        brier += it.pi*it.pi*it.W;
      else
        brier += (1-it.pi)*(1-it.pi)*it.W;
    }
    brier *= sumW/sumW2; // essentially yuehong's correction
    return brier;
  }

  double AIC(const TaggingResult& tag, int numParams) {
    double deviance = Deviance(tag);
    return deviance + 2*numParams;
  }

  double BIC(const TaggingResult& tag, int numParams) {
    double deviance = Deviance(tag);
    double num_eff = tag.GetEffNumEvents(); // both sumW2 corrected
    return deviance + numParams*log(num_eff);

  }

  double CalibrationComparisonChi2(const Calibration& lhs, const Calibration& rhs) {

    if (lhs.NumParams() != rhs.NumParams())
      return 0;

    std::size_t size = lhs.NumParams();
    Vector n = lhs.GetCoeffs() - rhs.GetCoeffs();
    Vector d = lhs.GetCoeffs() - rhs.GetCoeffs();
    Matrix ncov = lhs.GetCovarianceMatrix() + rhs.GetCovarianceMatrix();
    Matrix dcov = lhs.GetDeltaCovarianceMatrix() + rhs.GetDeltaCovarianceMatrix();
    Matrix ccov = lhs.GetCrossCovarianceMatrix() + rhs.GetCrossCovarianceMatrix();
    Vector v(2*size);
    Matrix cov(2*size,2*size);
    for (unsigned int k = 0; k < size; k++) {
      v[k] = n[k];
      v[k+size] = d[k];
      for (unsigned int l = 0; l < size; l++) {
	cov(k,l) = ncov(k,l);
	cov(k+size,l) = ccov(k,l);
	cov(k,l+size) = ccov(k,l);
	cov(k+size,l+size) = dcov(k,l);
      }
    }

    double chi2 = v*cov.LinearSolve(v);
    return chi2;
  }

}

