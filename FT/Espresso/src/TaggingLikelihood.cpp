#include <memory>

// root
#include "TMath.h"

// local
#include "TaggingLikelihood.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : TaggingLikelihood
//
// 2015-06-22 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TaggingLikelihood::TaggingLikelihood(const TaggingResult& _tag, const GLMModel& _glm, Regression::LinkType _L)
  : func(new GLMCalibrationFunction(_glm,_L)),
    numParams(func->NumParams()),
    L(_L),
    tag(_tag),
    cache(tag.GetTagTable().size(),{Vector(numParams),0.0}),
    Thetalast(new double[2*numParams]),
    ThetaP(new double[numParams]),
    ThetaM(new double[numParams])
{
  // CREATE BASIS CACHE
  const TaggingResult::TagTable& table = tag.GetTagTable();
  std::size_t size = table.size();
  for (std::size_t i = 0; i < size; i++) {
    if (table[i].eta >= 1) std::cout << "ERROR: " << __FILE__ << " x " << __LINE__ << std::endl;
    cache[i].basis = func->GetBasis(table[i].eta);
    cache[i].offset = func->GetOffset(table[i].eta);
  }
}

TaggingLikelihood::TaggingLikelihood(const TaggingLikelihood& rhs)
  : func(rhs.func->clone()),
    numParams(rhs.numParams),
    L(rhs.L),
    tag(rhs.tag),
    cache(rhs.cache),
    Thetalast(new double[2*numParams]),
    ThetaP(new double[numParams]),
    ThetaM(new double[numParams])
{
}

// TaggingLikelihood::TaggingLikelihood(const TaggingResult& _tag, std::unique_ptr<CalibrationFunction> _func)
//  : func(std::move(_func)),
//    tag(_tag)
// {
// }

TaggingLikelihood::~TaggingLikelihood() {
  if (Thetalast != nullptr)
    delete[] Thetalast;
  if (ThetaP != nullptr)
    delete[] ThetaP;
  if (ThetaM != nullptr)
    delete[] ThetaM;
}

//=============================================================================

TaggingLikelihood* TaggingLikelihood::Clone() const
{
  return new TaggingLikelihood(*this);
}


double TaggingLikelihood::DoEval(const double* Theta) const
{
  double loglik = 0.0;
  GetLogLikelihoodData(Theta,&loglik,nullptr,nullptr);
  loglik *= -2;
  return loglik;
}

double TaggingLikelihood::DoDerivative(const double* Theta, unsigned int icoord) const
{
  // // OPTIMIZATION HACK
  // /* If parameters are reused, it appears to usually be during consecutive calls
  //    So, just store the last values and results */
  // static bool firstRun = true;
  // static unsigned int icoordlast = 0;
  // static double loglikdlast = 0.0;

  // bool skip = true;
  // if (firstRun) {
  //   skip = false;
  //   firstRun = false;
  // } else if (icoord != icoordlast) {
  //   skip = false;
  // } else {
  //   for (unsigned int k = 0; k < 2*numParams; k++) {
  //     if (std::abs(Theta[k] - Thetalast[k]) >= 10*std::numeric_limits<double>::epsilon()) {
  //       skip = false;
  //       break;
  //     }
  //   }
  // }

  // if (skip) {
  //   return loglikdlast;
  // }

  for (unsigned int i = 0; i < numParams; i++) {
    ThetaP[i] = Theta[i] + 0.5*Theta[i+numParams];
    ThetaM[i] = Theta[i] - 0.5*Theta[i+numParams];
  }

  double loglikd = 0.0;
  const TaggingResult::TagTable& table = tag.GetTagTable();
  std::size_t size = table.size();
  for (std::size_t entry = 0; entry < size; entry++) {
    const TaggingResult::TagInfo& it = table[entry];

    double W = it.W;

    double omegaP = GLMCalibrationFunction::Value(cache[entry].basis,L,ThetaP,cache[entry].offset);
    double omegaM = GLMCalibrationFunction::Value(cache[entry].basis,L,ThetaM,cache[entry].offset);
    double omegaGiven, omegaOscillated;
    if (it.flavour == Flavour::Pos) {
      omegaGiven = omegaP;
      omegaOscillated = omegaM;
    } else {
      omegaGiven = omegaM;
      omegaOscillated = omegaP;
    }
    double pi = (1-omegaGiven)*(1-it.pollution) + omegaOscillated*it.pollution;

    double domegaP, domegaM;
    if (icoord < numParams) { // regular parameters
      domegaP = GLMCalibrationFunction::Derivative(cache[entry].basis,L,icoord,ThetaP,cache[entry].offset);
      domegaM = GLMCalibrationFunction::Derivative(cache[entry].basis,L,icoord,ThetaM,cache[entry].offset);
    } else { // delta parameters
      domegaP = 0.5 * GLMCalibrationFunction::Derivative(cache[entry].basis,L,icoord-numParams,ThetaP,cache[entry].offset);
      domegaM = -0.5 * GLMCalibrationFunction::Derivative(cache[entry].basis,L,icoord-numParams,ThetaM,cache[entry].offset);
    }
    double domegaGiven, domegaOscillated;
    if (it.flavour == Flavour::Pos) {
      domegaGiven = domegaP;
      domegaOscillated = domegaM;
    } else {
      domegaGiven = domegaM;
      domegaOscillated = domegaP;
    }
    double dpi = -1*domegaGiven*(1-it.pollution) + domegaOscillated*it.pollution;

    double val = (it.correct) ? dpi/pi : -dpi/(1-pi);
    loglikd += W*val;
  }

  loglikd *= -2;
  // loglikdlast = loglikd;
  // for (unsigned int k = 0; k < 2*numParams; k++) {
  //   Thetalast[k] = Theta[k];
  // }
  // icoordlast = icoord;

  return loglikd;

}

void TaggingLikelihood::Gradient(const double* Theta, double* grad) const
{

  Vector df(NDim());
  GetLogLikelihoodData(Theta,nullptr,&df,nullptr);
  df *= -2;

  for (unsigned int icoord = 0; icoord < NDim(); icoord++) {
    grad[icoord] = df(icoord);
  }

}

void TaggingLikelihood::FdF(const double* Theta, double& loglik, double* grad) const
{

  double f = 0.0;
  Vector df(NDim());
  GetLogLikelihoodData(Theta,&f,&df,nullptr);
  f *= -2;
  df *= -2;

  loglik = f;
  for (unsigned int icoord = 0; icoord < NDim(); icoord++) {
    grad[icoord] = df(icoord);
  }

}

double TaggingLikelihood::GetDeviance(const double* Theta) const
{
  return DoEval(Theta);
}

double TaggingLikelihood::GetLogLikelihood(const double* Theta) const
{
  double loglik = 0.0;
  GetLogLikelihoodData(Theta,&loglik,nullptr,nullptr);
  return loglik;
}

Vector TaggingLikelihood::GetLogLikelihoodGradient(const double* Theta) const
{
  Vector grad(NDim());
  GetLogLikelihoodData(Theta,nullptr,&grad,nullptr);
  return grad;
}

Matrix TaggingLikelihood::GetLogLikelihoodHessian(const double* Theta) const {
  Matrix hessian(NDim(),NDim());
  GetLogLikelihoodData(Theta,nullptr,nullptr,&hessian);
  return hessian;
}

Matrix TaggingLikelihood::GetCovarianceMatrix(const double* Theta, TaggingLikelihood::CovarianceCorrectionMethod method) const {
  // Covariance matrix
  // Below, hessian = -1V^{-1}, sqhessian = -C^{-1}
  // So, VC^{-1}V = -hessian^{-1} sqhessian hessian^{-1}
  Matrix hessian(NDim(),NDim());
  workhorse(Theta,nullptr,nullptr,&hessian,false);
  hessian.Invert();
  hessian *= -1;
  if (method == TaggingLikelihood::CovarianceCorrectionMethod::None) {
    return hessian;
  } else if (method == TaggingLikelihood::CovarianceCorrectionMethod::Yuehong) {
    double sumw = 0;
    double sumw2 = 0;
    for (const auto& it : tag.GetTagTable()) {
      sumw += it.W;
      sumw2 += it.W*it.W;
    }
    double corr = sumw2/sumw;
    hessian *= corr;
    return hessian;
  } else if (method == TaggingLikelihood::CovarianceCorrectionMethod::Markward) {
    Matrix sqhessian(NDim(),NDim());
    workhorse(Theta,nullptr,nullptr,&sqhessian,true);
    sqhessian *= -1;
    Matrix cov = hessian*(sqhessian*hessian);
    return cov;
  } else {
    return hessian;
  }
}

void TaggingLikelihood::GetLogLikelihoodData(const double* Theta, double* f, Vector* df, Matrix* ddf) const {
  workhorse(Theta,f,df,ddf,false);
}

void TaggingLikelihood::workhorse(const double* Theta, double* f, Vector* df, Matrix* ddf, bool squareWeights) const {

  bool setF = (f != nullptr);
  bool setDF = (df != nullptr);
  bool setDDF = (ddf != nullptr);

  if (setF) *f = 0.0;
  if (setDF) df->Reset();
  if (setDDF) ddf->Reset();

  for (unsigned int i = 0; i < numParams; i++) {
    ThetaP[i] = Theta[i] + 0.5*Theta[i+numParams];
    ThetaM[i] = Theta[i] - 0.5*Theta[i+numParams];
  }

  const TaggingResult::TagTable& table = tag.GetTagTable();
  std::size_t size = table.size();
  for (std::size_t entry = 0; entry < size; entry++) {
    const TaggingResult::TagInfo& it = table[entry];

    double W = (squareWeights) ? it.W*it.W : it.W;

    double omegaP = GLMCalibrationFunction::Value(cache[entry].basis,L,ThetaP,cache[entry].offset);
    double omegaM = GLMCalibrationFunction::Value(cache[entry].basis,L,ThetaM,cache[entry].offset);
    double omegaGiven, omegaOscillated;
    if (it.flavour == Flavour::Pos) {
      omegaGiven = omegaP;
      omegaOscillated = omegaM;
    } else {
      omegaGiven = omegaM;
      omegaOscillated = omegaP;
    }
    double pi = (1-omegaGiven)*(1-it.pollution) + omegaOscillated*it.pollution;


    if (setF) {
      double val = (it.correct) ? log(pi) : log(1-pi);
      *f += W*val;
    }

    if (setDF or setDDF) {
      Vector gradP = GLMCalibrationFunction::Derivative(cache[entry].basis,L,ThetaP,cache[entry].offset);
      Vector gradM = GLMCalibrationFunction::Derivative(cache[entry].basis,L,ThetaM,cache[entry].offset);
      for (unsigned int i = 0; i < NDim(); i++) {
        double domegaP, domegaM;
        if (i < numParams) { // regular parameters
          domegaP = gradP[i];
          domegaM = gradM[i];
        } else { // delta parameters
          domegaP = 0.5 * gradP[i-numParams];
          domegaM = -0.5 * gradM[i-numParams];
        }
        double domegaGiven, domegaOscillated;
        if (it.flavour == Flavour::Pos) {
          domegaGiven = domegaP;
          domegaOscillated = domegaM;
        } else {
          domegaGiven = domegaM;
          domegaOscillated = domegaP;
        }

        double dpi = -1*domegaGiven*(1-it.pollution) + domegaOscillated*it.pollution;
        if (setDF) {
          double val = (it.correct) ? dpi/pi : -dpi/(1-pi);
          (*df)[i] += W*val;
        }

        if (setDDF) {
          for (unsigned int j = 0; j < NDim(); j++) {
            double domegaP_j, domegaM_j;
            if (j < numParams) { // regular parameters
              domegaP_j = gradP[j];
              domegaM_j = gradM[j];
            } else { // delta parameters
              domegaP_j = 0.5 * gradP[j-numParams];
              domegaM_j = -0.5 * gradM[j-numParams];
            }
            double domegaGiven_j, domegaOscillated_j;
            if (it.flavour == Flavour::Pos) {
              domegaGiven_j = domegaP_j;
              domegaOscillated_j = domegaM_j;
            } else {
              domegaGiven_j = domegaM_j;
              domegaOscillated_j = domegaP_j;
            }
            double dpi_j = -1*domegaGiven_j*(1-it.pollution) + domegaOscillated_j*it.pollution;
            double val = (it.correct) ? -dpi*dpi_j/(pi*pi) : -dpi*dpi_j/((1-pi)*(1-pi));
            (*ddf)(i,j) += W*val;
          }
        }
      }
    }
  }
}
