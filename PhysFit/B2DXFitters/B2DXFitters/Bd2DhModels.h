//---------------------------------------------------------------------------//
//                                                                           //
//  RooFit models for Bd -> D h                                              //
//                                                                           //
//  Header file                                                              //
//                                                                           //
//  Authors: Eduardo Rodrigues                                               //
//  Date   : 18 / 05 / 2011                                                  //
//                                                                           //
//---------------------------------------------------------------------------//

#ifndef BD2DHMODELS_H
#define BD2DHMODELS_H 1

// STL includes

// ROOT and RooFit includes
#include "RooRealVar.h"
#include "RooStringVar.h"
#include "RooAbsPdf.h"
#include "RooResolutionModel.h"
#include "RooWorkspace.h"
#include "TString.h"
#include "RooAbsReal.h" 

namespace Bd2DhModels {

  RooAbsPdf* build_Bd2DPi_BKG_MDFitter( RooAbsReal& mass,
					RooAbsReal& massDs,
					RooWorkspace* work,
					RooWorkspace* workInt,
					TString &samplemode,
					TString merge,
					Int_t dim,
					bool debug = true
					);

  RooAbsPdf* build_Bd2DK_BKG_MDFitter( RooWorkspace* work,
                                       RooWorkspace* workInt,
				       std::vector <RooAbsReal*> obs,
				       std::vector <TString> types,
                                       TString &samplemode,
				       TString merge = "",
				       bool debug = true
                                       );

  RooAbsPdf* buildExponentialPlusConstantPDF( RooAbsReal& obs,
                                              RooWorkspace* workInt,
                                              TString samplemode,
                                              TString typemode,
                                              bool debug = true);

  RooAbsPdf* buildJohnsonSUPDF( RooAbsReal& obs,
                                RooWorkspace* workInt,
                                TString samplemode,
                                TString typemode,
                                bool shiftMean = false,
                                bool debug = true);

  RooAbsPdf* buildCrystalBallPlusExponentialPDF( RooAbsReal& obs,
                                                 RooWorkspace* workInt,
                                                 TString samplemode,
                                                 TString typemode,
                                                 bool shiftMean = false,
                                                 bool debug = true);

  RooAbsPdf* buildCrystalBallPlusGaussianPDF( RooAbsReal& obs,
                                              RooWorkspace* workInt,
                                              TString samplemode,
                                              TString typemode,
                                              bool shiftMean = false,
                                              bool scaleWidths = false,
                                              bool debug = true);

  RooAbsPdf* buildCrystalBallPlusJohnsonSUPDF( RooAbsReal& obs,
                                               RooWorkspace* workInt,
                                               TString samplemode,
                                               TString typemode,
                                               bool shiftMean = false,
                                               bool scaleWidths = false,
                                               bool debug = true);
  
  RooAbsPdf* buildJohnsonSUPlusGaussianPDF( RooAbsReal& obs,
                                            RooWorkspace* workInt,
                                            TString samplemode,
                                            TString typemode,
                                            bool sameMean = true,
                                            bool shiftMean = false,
                                            bool debug = true);
  
  RooAbsPdf* buildJohnsonSUPlusGaussianPlusExponentialPDF( RooAbsReal& obs,
                                                           RooWorkspace* workInt,
                                                           TString samplemode,
                                                           TString typemode,
							   bool sameMean,
                                                           bool debug = true);
  
  
  RooAbsPdf* buildJohnsonSUPlus2GaussianPDF( RooAbsReal& obs,
                                             RooWorkspace* workInt,
                                             TString samplemode,
                                             TString typemode,
                                             bool sameMean = true,
                                             bool debug = true);

  RooAbsPdf* buildIpatiaPlusExponentialPDF(RooAbsReal& obs,
                                           RooWorkspace* workInt,
                                           TString samplemode,
                                           TString typemode,
                                           bool debug = true);

  RooAbsPdf* buildIpatiaPlusGaussianPDF(RooAbsReal& obs,
                                        RooWorkspace* workInt,
                                        TString samplemode,
                                        TString typemode,
                                        bool shiftMean = false,
                                        bool scaleTails = false,
                                        bool debug = true);

  RooAbsPdf* buildIpatiaPlusJohnsonSUPDF(RooAbsReal& obs,
                                         RooWorkspace* workInt,
                                         TString samplemode,
                                         TString typemode,
                                         bool shiftMean = false,
                                         bool scaleTails = false,
                                         bool debug = true);

  RooAbsPdf* buildIpatiaGaussConvPDF(RooRealVar& obs,
                                     RooWorkspace* workInt,
                                     TString samplemode,
                                     TString typemode,
                                     bool shiftMean = false,
                                     bool scaleTails = false,
                                     bool fft = true,
                                     bool debug = true);

  RooAbsPdf* buildHILLdini(RooAbsReal& obs,
                           RooWorkspace* workInt,
                           TString samplemode,
                           TString typemode,
                           bool debug); 

  RooAbsPdf* buildHORNSdini(RooAbsReal& obs,
			    RooWorkspace* workInt,
			    TString samplemode,
			    TString typemode,
			    bool debug); 

} // end of namespace

//=============================================================================

#endif  // BD2DHMODELS_H
 
