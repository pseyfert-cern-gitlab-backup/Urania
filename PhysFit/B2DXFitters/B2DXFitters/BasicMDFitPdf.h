//---------------------------------------------------------------------------//
//                                                                           /
//  Basic PDFs used in the MDFit                                             //
//                                                                           //
//  Header file                                                              //
//                                                                           //
//  Authors: Agnieszka Dziurda                                               //
//  Email  : agnieszka.dziurda@cern.ch                                       //
//  Date   : 08 / 08 / 2017                                                  //
//                                                                           //
//---------------------------------------------------------------------------//

#ifndef BASICMDFITPDF_H
#define BASICMDFITPDF_H 1

// STL includes

// ROOT and RooFit includes
#include "RooAbsPdf.h"
#include "RooWorkspace.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooProdPdf.h"
#include "RooAbsReal.h"

#include <vector>

namespace BasicMDFitPdf {


  // Basic PDFs //
  RooAbsPdf* buildGaussPDF( RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool shiftMean = false, bool debug = false);
  RooAbsPdf* buildCrystalBallPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false);
  RooAbsPdf* buildExponentialPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false); 
  
  // More funcy basic functions //
  RooAbsPdf* buildIpatiaPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, 
			    bool shiftMean = false, bool scaleTails = false, bool debug = false);
  RooAbsPdf* buildApolloniosPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false);
  RooAbsPdf* buildHILLdini(RooAbsReal& obs, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug=false);
  RooAbsPdf* buildHORNSdini(RooAbsReal& obs, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug=false);

  // "Double" shapes //   
  RooAbsPdf* buildDoubleCrystalBallPDF( RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, 
					bool widthRatio = false, bool sharedMean = false, bool debug = false);
  RooAbsPdf* buildDoubleGaussPDF( RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, 
				  bool widthRatio = false, bool sharedMean =false, bool separeteMean=false, bool shiftMean=false, bool debug = false);
  RooAbsPdf* buildDoubleExponentialPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false);


  // Exponential variations (with Signal, Gaussian, Crystal Ball etc //
  RooAbsPdf* buildExponentialPlusGaussPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, 
					  bool sharedMean = false, bool debug = false);
  RooAbsPdf* buildExponentialTimesLinearPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false);
  RooAbsPdf* buildExponentialPlusSignalPDF(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false);
  RooAbsPdf* buildExponentialPlusDoubleCrystalBallPDF(RooAbsReal& obs, RooWorkspace* workInt, TString samplemode, TString typemode, 
						      bool widthRatio = false, bool sharedMean = false, bool debug = false);
  

  // get names of possible models // 
  std::vector <TString> getPdfNames(bool debug = false); 
  
  // Get Signal PDF independly of the type //
  RooAbsPdf* trySignal(TString samplemode, TString varName, RooWorkspace* workInt, bool debug);

  // Interface function for namespace, should be enough to call just this // 
  RooAbsPdf* buildAnalyticalShape(RooAbsReal& mass, RooWorkspace* workInt, TString samplemode, TString typemode, TString type, bool debug = false );



} // end of namespace

//=============================================================================

#endif  //BASICMDFITPDF_H
