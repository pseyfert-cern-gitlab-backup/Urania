/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id$
 * Authors:                                                                  *
 *   Gerhard Raven
 *                                                                           *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_CUBICSPLINEPDF
#define ROO_CUBICSPLINEPDF

#include "RooRealProxy.h"
#include "RooListProxy.h"
#include "RooCubicSplineKnot.h"
#include "RooAbsGaussModelEfficiency.h"
#include "RooAbsPdf.h"

class RooRealVar;
class RooArgList ;
class TH1;
class TGraph;
class TGraphErrors;

class RooCubicSplinePdf : public  RooAbsPdf {
public:
  RooCubicSplinePdf() ;
  RooCubicSplinePdf(const char* name, const char* title, RooRealVar& x,
                    const std::vector<double>& knots,
                    const std::vector<double>& values,
                    const std::vector<double>& errors = std::vector<double>(),
                    double smooth = 0, bool constCoeffs = true);
  RooCubicSplinePdf(const char* name, const char* title, RooRealVar& x, const TGraph* graph,
                    bool constCoeffs = true);
  // smooth = 0: no smoothing, interpolating spline
  // smooth = Infty: extreme smoothing, resulting in a straight line (as the 2nd derivative is forced to zero)
  // TODO: map [0,Infty] -> [0,1]
  RooCubicSplinePdf(const char* name, const char* title, RooRealVar& x, const TH1* hist,
                    double smooth = 0, bool constCoeffs = true);
  RooCubicSplinePdf(const char* name, const char* title, RooRealVar& x, const TGraphErrors* graph,
                    double smooth = 0, bool constCoeffs = true);
  RooCubicSplinePdf(const char *name, const char *title, RooRealVar& x,
                    const char *knotBinningName, const RooArgList& coefList) ;
  RooCubicSplinePdf(const char* name, const char* title, RooRealVar& x,
                     const std::vector<double>& knots, const RooArgList& coefList);

  ~RooCubicSplinePdf() ;

  RooCubicSplinePdf(const RooCubicSplinePdf& other, const char* name = 0);
  TObject* clone(const char* newname) const { return new RooCubicSplinePdf(*this, newname); }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const;
  Double_t analyticalIntegral(Int_t code, const char* rangeName) const;

  Int_t getMaxVal(const RooArgSet& vars) const;
  Double_t maxVal(Int_t code) const;

  // for use as RooAbsGaussModelEfficiency...
  std::complex<double> productAnalyticalIntegral(Double_t umin, Double_t umax
                                                ,Double_t scale, Double_t offset
                                                ,const std::complex<double>& z) const;

  unsigned knotSize() const { return _aux.size(); }
  double u(int i) const { return _aux.u(i); }
  const std::vector<double>& knots() const { return _aux.knots(); }
  const RooArgList& coefficients() const { return _coefList; }

private:

  RooRealProxy _x;
  RooListProxy _coefList ;
  RooCubicSplineKnot _aux;

  void init(const char* name, const std::vector<double>& heights,
            const std::vector<double>& errors, double smooth, bool constCoeffs);

  Double_t evaluate() const;
  //
  // for use in RooGaussEfficiencyModel...
  std::complex<double> gaussIntegralE(bool left, const RooGaussModelAcceptance::M_n<4U>& dM,
                           const RooGaussModelAcceptance::K_n& K,
                           double offset, double* sc) const ;

  ClassDef(RooCubicSplinePdf,1) // CubicSpline polynomial PDF
};

#endif
