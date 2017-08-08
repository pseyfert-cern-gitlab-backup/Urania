#ifndef Bs2Dsh2011TDAnaModels_H
#define Bs2Dsh2011TDAnaModels_H 1


#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooResolutionModel.h"
#include "RooWorkspace.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooProdPdf.h"
#include "RooArgList.h"
#include "RooAbsReal.h"

#include <vector> 

namespace Bs2Dsh2011TDAnaModels {
  
    
  RooAbsPdf* buildComboPIDKPDF(RooAbsReal& mass, RooWorkspace* workInt, RooWorkspace* work, 
			       TString samplemode, TString typemode, TString merge, bool debug = false);
  
  RooAbsPdf* buildShiftedDoubleCrystalBallPDF(RooAbsReal& mass, RooWorkspace* workInt,
					      TString samplemode, TString typemode, bool debug = false);
  		      
  RooExtendPdf* buildExtendPdfSpecBkgMDFit( RooWorkspace* workInt, RooWorkspace* work, std::vector <TString> types,
					    TString samplemode, TString typemode, TString typemodeDs = "", 
					    TString merge = "", 
					    int dim = 1, TString signalDs = "", bool debug = false);

  RooExtendPdf* buildExtendPdfMDFit( RooWorkspace* workInt, RooWorkspace* work,
				     std::vector <RooAbsReal*> obs,
                                     std::vector <TString> types,
				     TString samplemode, TString typemode, TString typemodeDs = "",
                                     TString merge = "" , bool debug =false);

  RooProdPdf* buildProdPdfSpecBkgMDFit( RooWorkspace* workInt, RooWorkspace* work, std::vector <TString> types,
					TString samplemode, TString typemode, TString typemodeDs = "", 
					TString merge = "",  
					int dim = 1, TString signalDs = "", bool debug = false);

  RooProdPdf* buildProdPdfMDFit( RooWorkspace* workInt, RooWorkspace* work,
				 std::vector <RooAbsReal*> obs,
				 std::vector <TString> types,
				 TString samplemode, TString typemode, TString typemodeDs = "",
                                 TString merge= "", bool debug=false);

  RooAbsPdf* buildMergedPdfMDFit(RooWorkspace* workInt, RooWorkspace* work,
                                 std::pair <RooAbsReal*,TString> obs_shape,
                                 TString samplemode, TString typemode, TString typemodeDs, TString merge, bool debug);


  RooAbsPdf* buildMergedSpecBkgMDFit(RooWorkspace* workInt, RooWorkspace* work,
                                     TString samplemode, TString typemode, TString typemodeDs, TString merge,
                                     int dim, TString signalDs, bool debug = false);

  RooAbsPdf* buildMassPdfSpecBkgMDFit(RooWorkspace* work,
				      TString samplemode, TString typemode, TString typemodeDs = "",
				      bool charmShape = false, bool debug = false);

  RooAbsPdf* buildPIDKShapeMDFit(RooWorkspace* work,
				 TString samplemode, TString typemode, TString typemodeDs = "",
				 bool debug = false);
  

  //===============================================================================
  // Read Bs (or Ds for dsMass == true ) shape from workspace
  //===============================================================================

  RooAbsPdf* ObtainMassShape(RooWorkspace* work,
                             TString mode,
			     TString year, 
			     bool dsMass,
			     RooRealVar& lumRatio,
			     bool debug = false);

  //===============================================================================
  // Read PIDK shape from workspace 
  //===============================================================================

  RooAbsPdf* ObtainPIDKShape(RooWorkspace* work,
                             TString mode,
			     TString pol,
			     TString year,
                             RooRealVar& lumRatio,
			     bool DsMode = false,
			     bool debug = false);

  //===============================================================================
  // Create RooProdPdf with (Bs, Ds, PIDK) shapes from workspace  
  //===============================================================================
  
  RooProdPdf* ObtainRooProdPdfForMDFitter(RooWorkspace* work,
                                          TString mode,
					  TString pol,
					  TString year,
                                          RooRealVar& lumRatio,
					  RooAbsPdf* pdf_Ds = NULL,
					  Int_t dim = 3, 
                                          bool debug = false);

  RooProdPdf* GetRooProdPdfDim(TString& mode,
			       TString& samplemode, 
			       RooAbsPdf* pdf_Bs = NULL,
			       RooAbsPdf* pdf_Ds = NULL,
			       RooAbsPdf* pdf_PIDK = NULL,
			       Int_t dim = 3,
			       bool debug = false);
  //===============================================================================
  // Create RooProdPdf with (Bs mass, Ds mass, PIDK, time) shapes from workspace
  //===============================================================================

  RooProdPdf* ObtainRooProdPdfForFullFitter(RooWorkspace* work,
                                            TString mode,
                                            TString pol,
					    TString year,
                                            RooRealVar& lumRatio,
                                            RooAbsPdf* pdf_Time,
                                            RooAbsPdf* pdf_Ds = NULL,
                                            bool debug = false);
    
  //===============================================================================
  // Background 2D model for Bs->DsPi mass fitter.
  //===============================================================================

  RooAbsPdf* build_Bs2DsPi_BKG_MDFitter( RooAbsReal& mass, RooAbsReal& massDs,
					 RooWorkspace* work,RooWorkspace* workInt,
					 TString &samplemode, TString merge = "", Int_t dim = 1, bool debug = false);
  
  //===============================================================================
  // Background 2D model for Bs->DsPi mass fitter.
  //===============================================================================

  RooAbsPdf*  build_Bs2DsK_BKG_MDFitter(RooAbsReal& mass, RooAbsReal& massDs,
					RooWorkspace* work, RooWorkspace* workInt,
					TString &samplemode, TString merge = "", Int_t dim =1 , bool debug = false);

  //===============================================================================
  // Load RooKeysPdf from workspace.
  //===============================================================================
  RooKeysPdf* GetRooKeysPdfFromWorkspace(RooWorkspace* work, TString& name, bool debug = false);
  
  //===============================================================================
  // Load RooHistPdf from workspace.
  //===============================================================================
  RooHistPdf* GetRooHistPdfFromWorkspace(RooWorkspace* work, TString& name, bool debug = false);

  //===============================================================================
  // Load RooAddPdf from workspace.
  //===============================================================================
  RooAddPdf* GetRooAddPdfFromWorkspace(RooWorkspace* work, TString& name, bool debug=false);

  //===============================================================================
  // Load RooBinned1DPdf from workspace.
  //===============================================================================
  RooAbsPdf* GetRooBinned1DFromWorkspace(RooWorkspace* work, TString& name, bool  debug = false);
  
  //===============================================================================
  // Load RooAbsPdf from workspace.
  //===============================================================================
  RooAbsPdf* GetRooAbsPdfFromWorkspace(RooWorkspace* work, TString& name, bool debug  = false );

  Double_t  CheckEvts( RooWorkspace* workInt, TString samplemode, TString typemode, bool debug = false);

  RooArgList* AddEPDF(RooArgList* list, RooExtendPdf* pdf, RooRealVar *numEvts, bool debug = false); 
  RooArgList* AddEPDF(RooArgList* list, RooExtendPdf* pdf, Double_t ev, bool debug = false);

  
  RooAbsPdf* mergePdf(RooAbsPdf* pdf1, RooAbsPdf* pdf2, TString merge, TString lum,RooWorkspace* workInt, bool debug = false);
  RooAbsPdf* tryPdf(TString name, RooWorkspace* workInt, bool debug );
  //RooAbsPdf* trySignal(TString samplemode, TString varName, RooWorkspace* workInt, bool debug); 

  TString findRooKeysPdf(std::vector <std::vector <TString> > pdfNames, TString var, TString smp, bool debug);
  TString getShapeType(std::vector <TString> types, const TString var, const TString typemode); 
  std::vector<TString> getShapesType(std::vector <TString> types, std::vector <TString> vars, const TString typemode, bool debug = false);
  std::vector<TString> getShapesType(std::vector <TString> types, std::vector <RooAbsReal*> vars, const TString typemode, bool debug );
  std::pair <RooAbsReal*, TString> getObservableAndShape(std::vector <TString> types, std::vector <RooAbsReal*> vars,Int_t i);

}

#endif
