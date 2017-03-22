#include "RandomNumberGeneration.hh"

using namespace Espresso;

using DEV_TYPE = std::random_device;
using RNG_TYPE = std::default_random_engine;
using UNI_TYPE = std::uniform_real_distribution<double>;
using NORM_TYPE = std::normal_distribution<double>;
template <typename T>
using INT_TYPE = std::uniform_int_distribution<T>;

static DEV_TYPE _dev;
static RNG_TYPE _rng {};
static UNI_TYPE _uni(0.0,1.0);
static NORM_TYPE _norm(0.0,1.0);

void RandomNumberGeneration::SetSeed(unsigned int _seed) {
  _rng.seed(_seed);
}

double RandomNumberGeneration::Get() {
  return _uni(_rng);
}

template <typename T>
T RandomNumberGeneration::GetInteger(T min, T max) {
  INT_TYPE<T> _int(min,max);
  return _int(_rng);
}
template int RandomNumberGeneration::GetInteger(int,int);
template long RandomNumberGeneration::GetInteger(long,long);
template long long RandomNumberGeneration::GetInteger(long long,long long);
template unsigned int RandomNumberGeneration::GetInteger(unsigned int,unsigned int);
template unsigned long RandomNumberGeneration::GetInteger(unsigned long,unsigned long);
template unsigned long long RandomNumberGeneration::GetInteger(unsigned long long,unsigned long long);

double RandomNumberGeneration::Get(Distribution &pdf) {
  return pdf.GetRandom();
}

double RandomNumberGeneration::GetNorm() {
  return _norm(_rng);
}

double RandomNumberGeneration::GetExpo(double min, double tau) {
  /* Set cutoff probability at CDF ~ 1e-10
     <=> 1.0 - (1.0 - exp(-(x-min)/fall)) = exp(-(x-min)/fall) ~ 1e-10
     <=> (x-min)/fall = 10
     <=> x = min + 10*fall
  */
  double max = min + 10*tau;
  double alpha = exp(-min/tau);
  double beta = exp(-max/tau);
  double u = RandomNumberGeneration::Get();
  double t = -tau * log(beta + u*(alpha - beta));  

  return t;
}

double RandomNumberGeneration::GetNorm(double mu, double sigma) {
  double z = _norm(_rng);
  return mu + sigma*z;
}

double RandomNumberGeneration::GetUniform(double min, double max) {
  UNI_TYPE _buni(min,max);
  double u = _buni(_rng);
  return u;
}
