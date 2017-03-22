#include <iostream>
#include <iomanip>
#include <cmath>

// Include files 
#include "Vector.hh"
#include "Matrix.hh"

// local
#include "TypicalCalibration.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : TypicalCalibration
//
// 2015-05-13 : Jack Wimberley
//-----------------------------------------------------------------------------

using namespace Espresso;

double* TypicalCalibration::GetCoeffArray() {
  return coeffs.GetArray();
}

const double* TypicalCalibration::GetCoeffArray() const {
  return coeffs.GetArray();
}

double TypicalCalibration::GetCoeff(unsigned int k) const
{
  return coeffs(k);
}

double TypicalCalibration::GetDeltaCoeff(unsigned int k) const
{
  return delta_coeffs(k);
}

double TypicalCalibration::GetError(unsigned int k) const
{
  return sqrt(covariance(k,k));
}

double TypicalCalibration::GetDeltaError(unsigned int k) const
{
  return sqrt(delta_covariance(k,k));
}

double TypicalCalibration::GetCovariance(unsigned int k, unsigned int l) const
{
  return covariance(k,l);
}

double TypicalCalibration::GetCorrelation(unsigned int k, unsigned int l) const
{
  double z = GetCovariance(k,l);
  z /= GetError(k);
  z /= GetError(l);
  return z;
}

double TypicalCalibration::GetDeltaCovariance(unsigned int k, unsigned int l) const
{
  return delta_covariance(k,l);
}

double TypicalCalibration::GetDeltaCorrelation(unsigned int k, unsigned int l) const
{
  double z = GetDeltaCovariance(k,l);
  z /= GetDeltaError(k);
  z /= GetDeltaError(l);
  return z;
}

double TypicalCalibration::GetCrossCovariance(unsigned int k, unsigned int l) const
{
  return cross_covariance(k,l);
}

double TypicalCalibration::GetCrossCorrelation(unsigned int k, unsigned int l) const
{
  double z = GetCrossCovariance(k,l);
  z /= GetError(k);
  z /= GetDeltaError(l);
  return z;
}

BOOST_CLASS_EXPORT_IMPLEMENT(Espresso::TypicalCalibration)

//=============================================================================
