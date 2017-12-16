#ifndef GAMMA_H
#define GAMMA_H 1

static const double mumass = 105.752;
static const double taumass = 1776.41;

extern float Number;
extern float norm;
extern float normR;
extern float normRAD;
extern float normRAD_L;
extern float normRAD_R;


float gammaVLLLL(const double m12sq, const double m23sq, const double m13sq) {
  /// following the notation of 0707.0988
  // in ntuple daughters 0 and 1 have the same sign
  double denom = taumass;
  denom = denom*denom*denom;
  double num = m12sq*(taumass*taumass + (mumass*mumass - m12sq  )) -  2* (mumass*mumass * (taumass*taumass + mumass*mumass) );
  return num/denom*Number/norm;
}

float gammaVLLRR(const double m12sq, const double m23sq, const double m13sq) {
  /// following the notation of 0707.0988
  // in ntuple daughters 0 and 1 have the same sign
  double denom = taumass;
  denom = denom*denom*denom;
  double num = -24.*mumass*mumass*(taumass*taumass+mumass*mumass - m12sq/3.) - 4.*(m13sq*m13sq+m23sq*m23sq) + 4.*(taumass*taumass+3.*mumass*mumass) * (m13sq+m23sq) ;
  return num/denom*Number/normR;
}



float gammaRAD(const double m12sq, const double m23sq, const double m13sq) {
  /// following the notation of 0707.0988
  // in ntuple daughters 0 and 1 have the same sign
  double denom = taumass*taumass*taumass;
  double a = taumass*taumass;
  double b = mumass*mumass;
  double c = m13sq;
  double d = m23sq;
  double e = m12sq;
  denom = denom*c*d*c*d;
    //mathematica output
  double num = 
    -6*b*c*c*d*d - 6*b*b*c*d*(c + d) + 2*b*b*b*(c + d)*(c + d) +
     2*a*a*b*(c*c + c*d + d*d) -
      2*a*b*(3*c*d*(c + d) + b*(2*c*c + 3*c*d + 2*d*d)) +
       c*d*(c*c*c + c*c*d + c*d*d + d*d*d + 4*c*d*e + (c + d)*e*e);

  return num/denom*Number/normRAD;

}

float interferenceVLLLL_RAD(const double m12sq, const double m23sq, const double m13sq) {
  /// following the notation of 0707.0988
  // in ntuple daughters 0 and 1 have the same sign
  double denom = taumass*taumass*taumass;
  double a = taumass*taumass;
  double b = mumass*mumass;
  double c = m13sq;
  double d = m23sq;
  double e = m12sq;
  denom = denom*c*d;
  double num = a*b*(c+d) - b*(6*c*d+b*(c+d)) + 2*c*d*e;
  return num/denom*Number/normRAD_L;

}
float interferenceVLLRR_RAD(const double m12sq, const double m23sq, const double m13sq) {
  /// following the notation of 0707.0988
  // in ntuple daughters 0 and 1 have the same sign
  double denom = taumass*taumass*taumass;
  double a = taumass*taumass;
  double b = mumass*mumass;
  double c = m13sq;
  double d = m23sq;
  double e = m12sq;
  denom = denom*c*d;
  double num = a*b*c + a*(b+c)*d - b*(3*c*d+b*(c+d)) - c*d*e;
  return num/denom*Number/normRAD_R;
}

#endif
