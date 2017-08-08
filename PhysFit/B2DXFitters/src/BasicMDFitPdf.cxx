//---------------------------------------------------------------------------//                                                                            
//                                                                           //                                                                                         
//  Basic PDFs used in the MDFit                                             //                                                                                
//                                                                           //                                                                             
//  Header file                                                              //                                                                                
//                                                                           //                                                                                         
//  Authors: Agnieszka Dziurda                                               //                                                                                         
//  Email  : agnieszka.dziurda@cern.ch                                       //                                                                                       
//  Date   : 08 / 08 / 2017                                                  //                                                                                                
//                                                                           //                                                                                                    
//---------------------------------------------------------------------------//       

// STL includes


// ROOT and RooFit includes
#include "TFile.h"
#include "RooArgList.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooExponential.h"
#include "RooWorkspace.h"
#include "RooCBShape.h" 
#include "RooExponential.h"
#include "RooWorkspace.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooGenericPdf.h"

// B2DXFitters includes
#include "B2DXFitters/BasicMDFitPdf.h"
#include "B2DXFitters/Bd2DhModels.h"
#include "B2DXFitters/GeneralUtils.h"
#include "B2DXFitters/RooIpatia2.h"
#include "B2DXFitters/RooApollonios.h"
#include "B2DXFitters/RooHILLdini.h"
#include "B2DXFitters/RooHORNSdini.h"


using namespace GeneralUtils;

namespace BasicMDFitPdf {



  //===============================================================================
  // Gaussian
  //===============================================================================
  RooAbsPdf* buildGaussPDF( RooAbsReal& obs,
                            RooWorkspace* workInt,
                            TString samplemode,
                            TString typemode,
                            bool shiftMean,
                            bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build Gaussian -------- "<<std::endl; }
    RooRealVar* mean = NULL;
    RooRealVar* sigma1Var =NULL;
    RooRealVar* shiftVar = NULL;
    RooFormulaVar *meanShiftVar = NULL;

    TString varName = obs.GetName();

    TString meanName = typemode+"_"+varName+"_mean_"+samplemode;
    mean = tryVar(meanName, workInt, debug);
    if(mean == NULL) mean = tryVar("Signal_"+varName+"_mean_"+samplemode, workInt, debug);
    if (shiftMean)
      {
	TString shiftVarName = typemode+"_"+varName+"_shift_"+samplemode;
	shiftVar = tryVar(shiftVarName, workInt, debug);
	TString meanShiftVarName = typemode+"_"+varName+"_meanShift_"+samplemode;
	meanShiftVar = new RooFormulaVar(meanShiftVarName.Data(), meanShiftVarName.Data(), "@0+@1", RooArgList(*mean,*shiftVar));
      }

    TString sigma1Name = typemode+"_"+varName+"_sigma_"+samplemode;
    sigma1Var = tryVar(sigma1Name, workInt, debug);

    RooGaussian* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_gauss_"+samplemode;
    if(shiftMean)
      pdf = new RooGaussian( pdfName.Data(), pdfName.Data(), obs, *meanShiftVar, *sigma1Var);
    else
      pdf = new RooGaussian( pdfName.Data(), pdfName.Data(), obs, *mean, *sigma1Var);

    CheckPDF( pdf, debug );
    return pdf;
  }
  

  //===============================================================================                                                                                                
  // Crystal Ball                                                                                                                                                  
  //===============================================================================                                                                              
  RooAbsPdf* buildCrystalBallPDF( RooAbsReal& obs,
                                  RooWorkspace* workInt,
                                  TString samplemode,
                                  TString typemode,
                                  bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build double Crystal Ball -------- "<<std::endl; }

    RooRealVar* mean = NULL;
    RooRealVar* alpha1Var = NULL;
    RooRealVar* n1Var = NULL;
    RooRealVar* sigma1Var =NULL;

    TString varName = obs.GetName();

    TString meanName = typemode+"_"+varName+"_mean_"+samplemode;
    mean = tryVar(meanName, workInt, debug);
    TString alpha1Name = typemode+"_"+varName+"_alpha_"+samplemode;
    alpha1Var = tryVar(alpha1Name, workInt, debug);
    TString n1Name = typemode+"_"+varName+"_n_"+samplemode;
    n1Var = tryVar(n1Name, workInt, debug);
    TString sigma1Name = typemode+"_"+varName+"_sigma_"+samplemode;
    sigma1Var = tryVar(sigma1Name, workInt, debug);

    RooCBShape* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_crystalBall_"+samplemode;
    pdf = new RooCBShape( pdfName.Data(), pdfName.Data(), obs, *mean, *sigma1Var, *alpha1Var, *n1Var);

    CheckPDF( pdf, debug );
    return pdf;
  }

  //=============================================================================== 
  // Exponential
  //=============================================================================== 
  RooAbsPdf* buildExponentialPDF(RooAbsReal& obs,
                                 RooWorkspace* workInt,
                                 TString samplemode,
                                 TString typemode,
                                 bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build Exponential -------- "<<std::endl; }

    RooRealVar* cB1Var = NULL;

    TString varName = obs.GetName();

    TString cB1VarName = typemode+"_"+varName+"_cB_"+samplemode;
    cB1Var = tryVar(cB1VarName, workInt, debug);

    RooAbsPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_expo_"+samplemode;
    pdf = new RooExponential( pdfName.Data(), pdfName.Data(), obs, *cB1Var);
    CheckPDF( pdf, debug );

    return pdf;
  }

  //===============================================================================  
  // Ipatia 
  //===============================================================================  
  RooAbsPdf* buildIpatiaPDF(RooAbsReal& mass,
                            RooWorkspace* workInt,
                            TString samplemode,
                            TString typemode,
                            bool shiftMean,
                            bool scaleTails,
                            bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build Ipatia -------- "<<std::endl; }

    RooRealVar* lVar = NULL;
    RooRealVar* zetaVar = NULL;
    RooRealVar* fbVar = NULL;
    RooRealVar* meanVar = NULL;
    RooRealVar* shiftVar = NULL;
    RooFormulaVar *meanShiftVar = NULL;
    RooRealVar* sigmaVar = NULL;

    RooRealVar* a1Var = NULL;
    RooRealVar* n1Var = NULL;
    RooRealVar* a2Var = NULL;
    RooRealVar* n2Var = NULL;

    RooRealVar* scaleaVar = NULL;
    RooRealVar* scalenVar = NULL;

    RooFormulaVar* a1VarScaled = NULL;
    RooFormulaVar* n1VarScaled = NULL;
    RooFormulaVar* a2VarScaled = NULL;
    RooFormulaVar* n2VarScaled = NULL;

    TString varName = mass.GetName();

    TString lVarName = typemode+"_"+varName+"_l_"+samplemode;
    lVar = tryVar(lVarName, workInt, debug);
    TString zetaVarName = typemode+"_"+varName+"_zeta_"+samplemode;
    zetaVar = tryVar(zetaVarName, workInt, debug);
    TString fbVarName = typemode+"_"+varName+"_fb_"+samplemode;
    fbVar = tryVar(fbVarName, workInt, debug);

    TString meanVarName = typemode+"_"+varName+"_mean_"+samplemode;
    meanVar = tryVar(meanVarName, workInt, debug);
    if (meanVar == NULL) meanVar = tryVar("Signal_"+varName+"_mean_"+samplemode, workInt, debug);
    if (shiftMean)
      {
	TString shiftVarName = typemode+"_"+varName+"_shift_"+samplemode;
	shiftVar = tryVar(shiftVarName, workInt, debug);
	TString meanShiftVarName = typemode+"_"+varName+"_meanShift_"+samplemode;
	meanShiftVar = new RooFormulaVar(meanShiftVarName.Data(), meanShiftVarName.Data(), "@0+@1", RooArgList(*meanVar,*shiftVar));
      }

    TString sigmaVarName = typemode+"_"+varName+"_sigma_"+samplemode;
    sigmaVar = tryVar(sigmaVarName, workInt, debug);
    if (sigmaVar == NULL) sigmaVar = tryVar("Signal_"+varName+"_sigma_"+samplemode, workInt, debug);

  
    TString a1VarName = typemode+"_"+varName+"_a1_"+samplemode;
    a1Var = tryVar(a1VarName, workInt, debug);
    if (a1Var == NULL) a1Var = tryVar("Signal_"+varName+"_a1_"+samplemode, workInt, debug);
    TString n1VarName = typemode+"_"+varName+"_n1_"+samplemode;
    n1Var = tryVar(n1VarName, workInt, debug);
    if (n1Var == NULL) a1Var = tryVar("Signal_"+varName+"_n1_"+samplemode, workInt, debug);
    TString a2VarName = typemode+"_"+varName+"_a2_"+samplemode;
    a2Var = tryVar(a2VarName, workInt, debug);
    if (a2Var == NULL) a1Var = tryVar("Signal_"+varName+"_a2_"+samplemode, workInt, debug);
    TString n2VarName = typemode+"_"+varName+"_n2_"+samplemode;
    n2Var = tryVar(n2VarName, workInt, debug);
    if (n2Var == NULL) n2Var = tryVar("Signal_"+varName+"_n2_"+samplemode, workInt, debug);

    if(scaleTails)
    {
      TString scaleaVarName = typemode+"_"+varName+"_ascale_"+samplemode;
      scaleaVar = tryVar(scaleaVarName, workInt, debug);
      if(scaleaVar == NULL) scaleaVar = tryVar("Signal_"+varName+"_ascale_"+samplemode, workInt, debug);

      TString scalenVarName = typemode+"_"+varName+"_nscale_"+samplemode;
      scalenVar = tryVar(scalenVarName, workInt, debug);
      if(scalenVar == NULL) scalenVar = tryVar("Signal_"+varName+"_nscale_"+samplemode, workInt, debug);

      TString a1VarScaledName = typemode+"_"+varName+"_a1scaled_"+samplemode;
      a1VarScaled = new RooFormulaVar(a1VarScaledName.Data(), a1VarScaledName.Data(), "@0*@1", RooArgList(*a1Var,*scaleaVar));

      TString a2VarScaledName = typemode+"_"+varName+"_a2scaled_"+samplemode;
      a2VarScaled = new RooFormulaVar(a2VarScaledName.Data(), a2VarScaledName.Data(), "@0*@1", RooArgList(*a2Var,*scaleaVar));

      TString n1VarScaledName = typemode+"_"+varName+"_n1scaled_"+samplemode;
      n1VarScaled = new RooFormulaVar(n1VarScaledName.Data(), n1VarScaledName.Data(), "@0*@1", RooArgList(*n1Var,*scalenVar));

      TString n2VarScaledName = typemode+"_"+varName+"_n2scaled_"+samplemode;
      n2VarScaled = new RooFormulaVar(n2VarScaledName.Data(), n2VarScaledName.Data(), "@0*@1", RooArgList(*n2Var,*scalenVar));

    }

    RooAbsPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_ipatia_"+samplemode;
    if(shiftMean)
      {
	if(scaleTails)
	  pdf = new RooIpatia2( pdfName.Data(), pdfName.Data(), mass, *lVar, *zetaVar, *fbVar, *sigmaVar, *meanShiftVar, *a1VarScaled, *n1VarScaled, *a2VarScaled, *n2VarScaled);
	else
	  pdf = new RooIpatia2( pdfName.Data(), pdfName.Data(), mass, *lVar, *zetaVar, *fbVar, *sigmaVar, *meanShiftVar, *a1Var, *n1Var, *a2Var, *n2Var);
      }
    else
      {
	if(scaleTails)
	  pdf = new RooIpatia2( pdfName.Data(), pdfName.Data(), mass, *lVar, *zetaVar, *fbVar, *sigmaVar, *meanVar, *a1VarScaled, *n1VarScaled, *a2VarScaled, *n2VarScaled);
	else
	  pdf = new RooIpatia2( pdfName.Data(), pdfName.Data(), mass, *lVar, *zetaVar, *fbVar, *sigmaVar, *meanVar, *a1Var, *n1Var, *a2Var, *n2Var);
      }

    CheckPDF( pdf, debug );

    return pdf;

  }

  //=============================================================================== 
  //  Apollonios 
  //=============================================================================== 

  RooAbsPdf* buildApolloniosPDF(RooAbsReal& mass,
                                RooWorkspace* workInt,
                                TString samplemode,
                                TString typemode,
                                bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build Apollonios -------- "<<std::endl; }

    RooRealVar* meanVar = NULL;
    RooRealVar* sigmaVar = NULL;
    RooRealVar* bVar = NULL;
    RooRealVar* aVar = NULL;
    RooRealVar* nVar = NULL;

    TString varName = mass.GetName();

    TString meanVarName = typemode+"_"+varName+"_mean_"+samplemode;
    meanVar = tryVar(meanVarName, workInt, debug);
    TString sigmaVarName = typemode+"_"+varName+"_sigma_"+samplemode;
    sigmaVar = tryVar(sigmaVarName, workInt, debug);
    TString aVarName = typemode+"_"+varName+"_a_"+samplemode;
    aVar = tryVar(aVarName, workInt, debug);
    TString bVarName = typemode+"_"+varName+"_b_"+samplemode;
    bVar = tryVar(bVarName, workInt, debug);
    TString nVarName = typemode+"_"+varName+"_n_"+samplemode;
    nVar = tryVar(nVarName, workInt, debug);

    RooAbsPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_apollonios_"+samplemode;
    pdf = new RooApollonios( pdfName.Data(), pdfName.Data(), mass, *meanVar, *sigmaVar, *bVar, *aVar, *nVar);
    CheckPDF( pdf, debug );

    return pdf;

  }

  //===============================================================================
  // RooHILLdini
  //===============================================================================

  RooAbsPdf* buildHILLdini(RooAbsReal& obs,
                           RooWorkspace* workInt,
                           TString samplemode,
                           TString typemode,
                           bool debug)
  {
    if ( debug == true )
      {
	std::cout<<"[INFO] BasicMDFitPdf::buildHILLdini(..)==> building RooHILLdini PDF ..."<<std::endl;
      }

    RooRealVar* aVar = NULL;
    RooRealVar* bVar = NULL;
    RooRealVar* csiVar = NULL;
    RooRealVar* shiftVar = NULL;
    RooRealVar* sigmaVar = NULL;
    RooRealVar* rVar = NULL;
    RooRealVar* fVar = NULL;

    TString varName = obs.GetName();

    TString aVarName = typemode+"_"+varName+"_a_"+samplemode;
    aVar = tryVar(aVarName, workInt, debug);
    TString bVarName = typemode+"_"+varName+"_b_"+samplemode;
    bVar = tryVar(bVarName, workInt, debug);
    TString csiVarName = typemode+"_"+varName+"_csi_"+samplemode;
    csiVar = tryVar(csiVarName, workInt, debug);
    TString shiftVarName = typemode+"_"+varName+"_shift_"+samplemode;
    shiftVar = tryVar(shiftVarName, workInt, debug);
    TString sigmaVarName = typemode+"_"+varName+"_sigma_"+samplemode;
    sigmaVar = tryVar(sigmaVarName, workInt, debug);
    TString rVarName = typemode+"_"+varName+"_R_"+samplemode;
    rVar = tryVar(rVarName, workInt, debug);
    TString fVarName = typemode+"_"+varName+"_frac_"+samplemode;
    fVar = tryVar(fVarName, workInt, debug);

    RooAbsPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_hill_"+samplemode;
    pdf = new RooHILLdini(pdfName.Data(), pdfName.Data(),obs, *aVar, *bVar, *csiVar, *shiftVar, *sigmaVar, *rVar, *fVar);
    CheckPDF( pdf, debug );

    return pdf;
  }

  //=============================================================================== 
  // RooHORNSdini
  //=============================================================================== 

  RooAbsPdf* buildHORNSdini(RooAbsReal& obs,
			    RooWorkspace* workInt,
			    TString samplemode,
			    TString typemode,
			    bool debug)
  {
    if ( debug == true )
      {
	std::cout<<"[INFO] BasicMDFitPdf::buildHORNSdini(..)==> building RooHORNSdini PDF ..."<<std::endl;
      }

    RooRealVar* aVar = NULL;
    RooRealVar* bVar = NULL;
    RooRealVar* csiVar = NULL;
    RooRealVar* shiftVar = NULL;
    RooRealVar* sigmaVar = NULL;
    RooRealVar* rVar = NULL;
    RooRealVar* fVar = NULL;

    TString varName = obs.GetName();

    TString aVarName = typemode+"_"+varName+"_a_"+samplemode;
    aVar = tryVar(aVarName, workInt, debug);
    TString bVarName = typemode+"_"+varName+"_b_"+samplemode;
    bVar = tryVar(bVarName, workInt, debug);
    TString csiVarName = typemode+"_"+varName+"_csi_"+samplemode;
    csiVar = tryVar(csiVarName, workInt, debug);
    TString shiftVarName = typemode+"_"+varName+"_shift_"+samplemode;
    shiftVar = tryVar(shiftVarName, workInt, debug);
    TString sigmaVarName = typemode+"_"+varName+"_sigma_"+samplemode;
    sigmaVar = tryVar(sigmaVarName, workInt, debug);
    TString rVarName = typemode+"_"+varName+"_R_"+samplemode;
    rVar = tryVar(rVarName, workInt, debug);
    TString fVarName = typemode+"_"+varName+"_frac_"+samplemode;
    fVar = tryVar(fVarName, workInt, debug);

    RooAbsPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_horns_"+samplemode;
    pdf = new RooHORNSdini(pdfName.Data(), pdfName.Data(),obs, *aVar, *bVar, *csiVar, *shiftVar, *sigmaVar, *rVar, *fVar);
    CheckPDF( pdf, debug );

    return pdf;

  }

  //=============================================================================== 
  // Double Gaussian 
  //=============================================================================== 
  RooAbsPdf* buildDoubleGaussPDF( RooAbsReal& obs,
                                  RooWorkspace* workInt,
                                  TString samplemode,
                                  TString typemode,
                                  bool widthRatio,
                                  bool sharedMean,
                                  bool separeteMean,
                                  bool shiftMean,
                                  bool debug)
  {

    if ( debug == true ) { std::cout<<"[INFO] --------- build double Gaussian -------- "<<std::endl; }

    RooRealVar* mean = NULL;
    RooRealVar* mean2 = NULL;
    RooRealVar* shiftVar = NULL;
    RooFormulaVar *meanShiftVar = NULL;
    RooRealVar* sigma1Var =NULL;
    RooRealVar* sigma2Var = NULL;
    RooRealVar* fracVar = NULL;
    RooFormulaVar* sigma1For = NULL;
    RooFormulaVar* sigma2For = NULL;
    RooRealVar* R = NULL;
    TString varName = obs.GetName();

    TString meanName = typemode+"_"+varName+"_mean_"+samplemode;
    if ( sharedMean ) { meanName = "Signal_"+varName+"_mean_"+samplemode; }
    mean = tryVar(meanName, workInt, debug);

    if ( separeteMean )
      {
        TString meanName2 = typemode+"_"+varName+"_mean2_"+samplemode;
        mean2 = tryVar(meanName2, workInt, debug);
      }

    if (shiftMean)
      {
	TString shiftVarName = typemode+"_"+varName+"_shift_"+samplemode;
	shiftVar = tryVar(shiftVarName, workInt, debug);
	TString meanShiftVarName = typemode+"_"+varName+"_meanShift_"+samplemode;
	meanShiftVar = new RooFormulaVar(meanShiftVarName.Data(), meanShiftVarName.Data(), "@0+@1", RooArgList(*mean,*shiftVar));
      }

    TString sigma1Name = typemode+"_"+varName+"_sigma1_"+samplemode;
    sigma1Var = tryVar(sigma1Name, workInt, debug);
    TString sigma2Name = typemode+"_"+varName+"_sigma2_"+samplemode;
    sigma2Var = tryVar(sigma2Name, workInt, debug);
    TString fracName = typemode+"_"+varName+"_frac_"+samplemode;
    fracVar = tryVar(fracName, workInt, debug);

    if ( widthRatio )
      {
	TString name = typemode+TString("_")+varName+TString("_R");
	R = new RooRealVar(name.Data(),name.Data(), 1.0, 0.8, 1.2);
	name = typemode+TString("_") + varName + TString("_sigmafg1_")+samplemode;
	sigma1For = new RooFormulaVar(name.Data(), name.Data(),"@0*@1", RooArgList(*sigma1Var,*R));
	if ( debug == true ) { std::cout<<"[INFO] Create/read "<<name<<std::endl; }
	name = typemode+TString("_") + varName + TString("_sigmafg2_")+samplemode;
	sigma2For = new RooFormulaVar(name.Data(), name.Data(),"@0*@1", RooArgList(*sigma2Var,*R));
	if ( debug == true ) { std::cout<<"[INFO] Create/read "<<name<<std::endl; }
      }

    RooGaussian* pdf1 = NULL;
    TString pdf1Name = typemode+"_"+varName+"_Gauss1_"+samplemode;
    RooGaussian* pdf2 = NULL;
    TString pdf2Name = typemode+"_"+varName+"_Gauss2_"+samplemode;

    if(shiftMean)
      {
	if (widthRatio)
	  {
	    pdf1 = new RooGaussian( pdf1Name.Data(), pdf1Name.Data(), obs, *meanShiftVar, *sigma1For);
	    pdf2 = new RooGaussian( pdf2Name.Data(), pdf2Name.Data(), obs, *meanShiftVar, *sigma2For);
	  }
	else
	  {
	    pdf1 = new RooGaussian( pdf1Name.Data(), pdf1Name.Data(), obs, *meanShiftVar, *sigma1Var);
	    pdf2 = new RooGaussian( pdf2Name.Data(), pdf2Name.Data(), obs, *meanShiftVar, *sigma2Var);
	  }
      }
    else if ( separeteMean )
      {
        if (widthRatio)
          {
            pdf1 = new RooGaussian( pdf1Name.Data(), pdf1Name.Data(), obs, *mean,  *sigma1For);
            pdf2 = new RooGaussian( pdf2Name.Data(), pdf2Name.Data(), obs, *mean2, *sigma2For);
          }
        else
          {
            pdf1 = new RooGaussian( pdf1Name.Data(), pdf1Name.Data(), obs, *mean, *sigma1Var);
            pdf2 = new RooGaussian( pdf2Name.Data(), pdf2Name.Data(), obs, *mean2, *sigma2Var);
          }
      }
    else
      {
	if (widthRatio)
	  {
	  pdf1 = new RooGaussian( pdf1Name.Data(), pdf1Name.Data(), obs, *mean, *sigma1For);
	  pdf2 = new RooGaussian( pdf2Name.Data(), pdf2Name.Data(), obs, *mean, *sigma2For);
	  }
	else
	  {
	    pdf1 = new RooGaussian( pdf1Name.Data(), pdf1Name.Data(), obs, *mean, *sigma1Var);
	  pdf2 = new RooGaussian( pdf2Name.Data(), pdf2Name.Data(), obs, *mean, *sigma2Var);
	  }
      }
    
  CheckPDF( pdf1, debug );
  CheckPDF( pdf2, debug);

  RooAddPdf* pdf = NULL;
  TString pdfName = typemode+"_"+varName+"_doubleGauss_"+samplemode;
  pdf = new RooAddPdf( pdfName.Data(), pdfName.Data(),  *pdf1, *pdf2, *fracVar);
  CheckPDF( pdf, debug );

  return pdf;

}


  //===============================================================================                                             
  // Double crystal ball function                                                                                                                                           
  //===============================================================================                                                                  

  RooAbsPdf* buildDoubleCrystalBallPDF( RooAbsReal& obs,
                                        RooWorkspace* workInt,
                                        TString samplemode,
                                        TString type,
                                        bool widthRatio,
                                        bool sharedMean,
                                        bool debug)
  {

    if ( debug == true ) { std::cout<<"[INFO] --------- build double Crystal Ball -------- "<<std::endl; }

    RooRealVar* mean = NULL;
    RooRealVar* alpha1Var = NULL;
    RooRealVar* alpha2Var =NULL;
    RooRealVar* n1Var = NULL;
    RooRealVar* n2Var =NULL;
    RooRealVar* sigma1Var =NULL;
    RooRealVar* sigma2Var = NULL;
    RooRealVar* fracVar = NULL;
    RooFormulaVar* sigma1For = NULL;
    RooFormulaVar* sigma2For = NULL;
    RooRealVar* R = NULL;

    TString varName = obs.GetName();

    TString meanName = type+"_"+varName+"_mean_"+samplemode;
    if ( sharedMean) { meanName = "Signal_"+varName+"_mean_"+samplemode; }
    mean = tryVar(meanName, workInt, debug);
    TString alpha1Name = type+"_"+varName+"_alpha1_"+samplemode;
    alpha1Var = tryVar(alpha1Name, workInt, debug);
    TString alpha2Name = type+"_"+varName+"_alpha2_"+samplemode;
    alpha2Var = tryVar(alpha2Name, workInt, debug);
    TString n1Name = type+"_"+varName+"_n1_"+samplemode;
    n1Var = tryVar(n1Name, workInt, debug);
    TString n2Name = type+"_"+varName+"_n2_"+samplemode;
    n2Var = tryVar(n2Name, workInt, debug);
    TString sigma1Name = type+"_"+varName+"_sigma1_"+samplemode;
    sigma1Var = tryVar(sigma1Name, workInt, debug);
    TString sigma2Name = type+"_"+varName+"_sigma2_"+samplemode;
    sigma2Var = tryVar(sigma2Name, workInt, debug);
    TString fracName = type+"_"+varName+"_frac_"+samplemode;
    fracVar = tryVar(fracName, workInt, debug);

    if ( widthRatio )
      {
	TString RName = type+TString("_")+varName+TString("_R_")+samplemode;
	R = tryVar(RName, workInt, debug);
	TString name = type+TString("_") + varName + TString("_sigmafcb1_")+samplemode;
	sigma1For = new RooFormulaVar(name.Data(), name.Data(),"@0*@1", RooArgList(*sigma1Var,*R));
	if ( debug == true ) { std::cout<<"[INFO] Create/read "<<name<<std::endl; }
	name = type+TString("_") + varName + TString("_sigmafcb2_")+samplemode;
	sigma2For = new RooFormulaVar(name.Data(), name.Data(),"@0*@1", RooArgList(*sigma2Var,*R));
	if ( debug == true ) { std::cout<<"[INFO] Create/read "<<name<<std::endl; }
      }

    RooAbsPdf* pdf = NULL;

    RooCBShape* pdf1 = NULL;
    TString pdf1Name = type+"_"+varName+"_crystalBall1_"+samplemode;
    RooCBShape* pdf2 = NULL;
    TString pdf2Name = type+"_"+varName+"_crystalBall2_"+samplemode;

    if ( widthRatio )
      {
	pdf1 = new RooCBShape( pdf1Name.Data(), pdf1Name.Data(), obs, *mean, *sigma1For, *alpha1Var, *n1Var);
	pdf2 = new RooCBShape( pdf2Name.Data(), pdf2Name.Data(), obs, *mean, *sigma2For, *alpha2Var, *n2Var);
      }
    else
      {
	pdf1 = new RooCBShape( pdf1Name.Data(), pdf1Name.Data(), obs, *mean, *sigma1Var, *alpha1Var, *n1Var);
	pdf2 = new RooCBShape( pdf2Name.Data(), pdf2Name.Data(), obs, *mean, *sigma2Var, *alpha2Var, *n2Var);
      }
    CheckPDF( pdf1, debug );
    CheckPDF( pdf2, debug);

    TString pdfName = type+"_"+varName+"_doubleCrystalBall_"+samplemode;
    pdf = new RooAddPdf( pdfName.Data(), pdfName.Data(), *pdf1, *pdf2, *fracVar);
    CheckPDF( pdf, debug );

    return pdf;
  }

  //=============================================================================== 
  // Double Exponential 
  //=============================================================================== 

  RooAbsPdf* buildDoubleExponentialPDF(RooAbsReal& obs,
                                       RooWorkspace* workInt,
                                       TString samplemode,
                                       TString typemode,
                                       bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build double Exponential -------- "<<std::endl; }

    RooRealVar* cB1Var = NULL;
    RooRealVar* cB2Var = NULL;
    RooRealVar* fracVar = NULL;

    TString varName = obs.GetName();

    TString cB1VarName = typemode+"_"+varName+"_cB1_"+samplemode;
    cB1Var = tryVar(cB1VarName, workInt, debug);
    TString cB2VarName = typemode+"_"+varName+"_cB2_"+samplemode;
    cB2Var = tryVar(cB2VarName, workInt, debug);
    TString fracName = typemode+"_"+varName+"_frac_"+samplemode;
    fracVar = tryVar(fracName, workInt, debug);

    RooAbsPdf* pdf1 = NULL;
    TString pdf1Name = typemode+"_"+varName+"_expo1_"+samplemode;
    pdf1 = new RooExponential( pdf1Name.Data(), pdf1Name.Data(), obs, *cB1Var);
    CheckPDF( pdf1, debug );

    RooAbsPdf* pdf2 = NULL;
    TString pdf2Name = typemode+"_"+varName+"_expo2_"+samplemode;
    pdf2 = new RooExponential( pdf2Name.Data(), pdf2Name.Data(), obs, *cB2Var);
    CheckPDF( pdf2, debug );

    RooAddPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_doubleExpo_"+samplemode;
    pdf = new RooAddPdf(pdfName.Data(), pdfName.Data(), RooArgList(*pdf1,*pdf2),*fracVar);
    CheckPDF( pdf, debug );

    return pdf;

  }


  //=============================================================================== 
  // Ezponential plus Gauss
  //=============================================================================== 

  RooAbsPdf* buildExponentialPlusGaussPDF(RooAbsReal& obs,
                                          RooWorkspace* workInt,
                                          TString samplemode,
                                          TString typemode,
                                          bool sharedMean,
                                          bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build Exponential plus Gaussian -------- "<<std::endl; }

    RooRealVar* mean = NULL;
    RooRealVar* sigma1Var =NULL;
    RooRealVar* fracVar = NULL;
    RooRealVar* cB1Var = NULL;

    TString varName = obs.GetName();

    TString meanName = typemode+"_"+varName+"_mean_"+samplemode;
    if ( sharedMean ) { meanName = "Signal_"+varName+"_mean_"+samplemode; }
    mean = tryVar(meanName, workInt, debug);
    TString sigma1Name = typemode+"_"+varName+"_sigma_"+samplemode;
    sigma1Var = tryVar(sigma1Name, workInt, debug);
    TString fracName = typemode+"_"+varName+"_frac_"+samplemode;
    fracVar = tryVar(fracName, workInt, debug);
    TString cB1VarName = typemode+"_"+varName+"_cB_"+samplemode;
    cB1Var = tryVar(cB1VarName, workInt, debug);
    RooExponential* pdf1 = NULL;
    TString pdf1Name = typemode+"_"+varName+"_expo1_"+samplemode;
    pdf1 = new RooExponential( pdf1Name.Data(), pdf1Name.Data(), obs, *cB1Var);
    CheckPDF( pdf1, debug );

    RooGaussian* pdf2 = NULL;
    TString pdf2Name = typemode+"_"+varName+"_gauss1_"+samplemode;
    pdf2 = new RooGaussian(pdf2Name.Data(),pdf2Name.Data(), obs,*mean,*sigma1Var);
    CheckPDF( pdf2, debug );

    RooAddPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_expoGauss_"+samplemode;
    pdf = new RooAddPdf(pdfName.Data(), pdfName.Data(), RooArgList(*pdf1,*pdf2),*fracVar);
    CheckPDF( pdf, debug );

    return pdf;
  }

  //=============================================================================== 
  //  Exponential Times Linear 
  //=============================================================================== 
  
  RooAbsPdf* buildExponentialTimesLinearPDF(RooAbsReal& obs,
                                            RooWorkspace* workInt,
                                            TString samplemode,
                                            TString typemode,
                                            bool debug)
  {

    if ( debug == true ) { std::cout<<"[INFO] --------- build Exponential times Linear -------- "<<std::endl; }

    RooRealVar* cB1Var = NULL;
    RooRealVar* shiftComb = NULL;
    TString varName = obs.GetName();
    TString shiftCombName = typemode+"_"+varName+"_shiftComb_"+samplemode;                                                           

    TString cB1VarName = typemode+"_"+varName+"_cB_"+samplemode;

    cB1Var = tryVar(cB1VarName, workInt, debug);
    shiftComb = tryVar(shiftCombName, workInt, debug);

    RooAbsPdf* pdf1 = NULL;
    TString pdf1Name = typemode+"_"+varName+"_expo_"+samplemode;
    pdf1 = new RooExponential( pdf1Name.Data(), pdf1Name.Data(), obs, *cB1Var);
    CheckPDF( pdf1, debug );

    RooAbsPdf* pdf2 = NULL;
    TString pdf2Name = typemode+"_"+varName+"_linear_"+samplemode;
    pdf2 = new RooGenericPdf( pdf2Name.Data(), "(@0 - @1)", RooArgList(obs,*shiftComb));
    CheckPDF( pdf2, debug );

    RooAbsPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_expoLinear_"+samplemode;
    pdf = new RooProdPdf(pdfName.Data(), pdfName.Data(), RooArgList(*pdf1,*pdf2));
    CheckPDF( pdf, debug );

    return pdf;
  }


  //===============================================================================  
  //  Exponential plus signal 
  //===============================================================================  


  RooAbsPdf* buildExponentialPlusSignalPDF(RooAbsReal& obs,
                                           RooWorkspace* workInt,
                                           TString samplemode,
                                           TString typemode,
                                           bool debug)
  {
    if ( debug == true ) { std::cout<<"[INFO] --------- build Exponential plus Signal -------- "<<std::endl; }
    RooRealVar* cDVar = NULL;
    RooRealVar* fracVar = NULL;
    RooAbsPdf* pdf0 = NULL;

    TString varName = obs.GetName();
    TString cDVarName = typemode+"_"+varName+"_cD_"+samplemode;
    cDVar = tryVar(cDVarName, workInt, debug);

    TString fracDsCombName = typemode+"_"+varName+"_fracD_"+samplemode;
    fracVar = tryVar(fracDsCombName, workInt, debug);

    pdf0 = trySignal(samplemode,varName,workInt, debug);

    RooExponential* pdf1 = NULL;
    TString pdf1Name = typemode+"_"+varName+"_Expo_"+samplemode;
    pdf1 = new RooExponential( pdf1Name.Data(), pdf1Name.Data(), obs, *cDVar );
    CheckPDF(pdf1, debug);

    RooAddPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_expoSignal_"+samplemode;
    pdf = new RooAddPdf( pdfName.Data(), pdfName.Data(),  RooArgList(*pdf1,*pdf0), *fracVar );
    CheckPDF(pdf, debug);

    return pdf;

  }
  


  //===============================================================================                               
  // Build exponential plus double Crystal Ball                                                                                                                           
  //=============================================================================== 
  RooAbsPdf* buildExponentialPlusDoubleCrystalBallPDF(RooAbsReal& obs, RooWorkspace* workInt,
                                                      TString samplemode, TString typemode, bool widthRatio, bool sharedMean, bool debug)
  {
    RooAbsPdf* pdf0 = buildExponentialPDF(obs, workInt, samplemode, typemode, debug);
    RooAbsPdf* pdf1 = buildDoubleCrystalBallPDF( obs, workInt, samplemode, typemode, widthRatio, sharedMean, debug);

    RooRealVar* fracVar = NULL;
    TString varName = obs.GetName();
    TString fracDsCombName = typemode+"_"+varName+"_fracD_"+samplemode;
    fracVar = tryVar(fracDsCombName, workInt, debug);

    RooAddPdf* pdf = NULL;
    TString pdfName = typemode+"_"+varName+"_expodCB_"+samplemode;
    pdf = new RooAddPdf( pdfName.Data(), pdfName.Data(),  RooArgList(*pdf1,*pdf0), *fracVar );
    CheckPDF(pdf, debug);

    return pdf;

  }

  //=============================================================================== 
  // get names of possible pdfs
  //=============================================================================== 
  std::vector <TString>getPdfNames(bool debug)
  {
    std::vector<TString> names;
    names.push_back("_gauss_");
    names.push_back("_crystalBall_");
    names.push_back("_expo_");

    names.push_back("_ipatia_");
    names.push_back("_apollonios_");
    names.push_back("_hill_");
    names.push_back("_horns_");
    
    names.push_back("_doubleGauss_");
    names.push_back("_doubleCrystalBall_");
    names.push_back("_doubleExpo_");
    
    names.push_back("_expoGauss_");
    names.push_back("_expoLinear_");
    names.push_back("_expoSignal_");
    names.push_back("_expodCB_");

    if (debug == true )
      {
	std::cout<<"[INFO] BasicMDFitPDfs are: "<<std::endl; 
	for ( const TString name : names )
	  {
	    std::cout<<name<<std::endl;
	  }
      }
    
    return names; 
  }

  //===============================================================================
  // try to get signal independly on the model 
  //===============================================================================

  RooAbsPdf* trySignal(TString samplemode, TString varName, RooWorkspace* workInt, bool debug)
  {
    RooAbsPdf* pdf= NULL;

    std::vector<TString> suffix = getPdfNames(); 

    std::vector<TString> suffix2;
    suffix2.push_back("");
    suffix2.push_back("_pol");
    suffix2.push_back("_year");
    suffix2.push_back("_pol_year");

    for ( unsigned i = 0; i < suffix.size(); i++)
      {
	for ( unsigned j = 0; j <suffix2.size(); j++ )
	  {
	    TString pdfName = "Signal_"+varName+suffix[i]+samplemode+suffix2[j];
	    pdf = (RooAbsPdf*) workInt -> pdf(pdfName.Data());
	    if ( pdf != NULL ){ break; }
	  }
	if ( pdf != NULL ){ break; }
      }

    CheckPDF(pdf,debug);
    return pdf;
  }


  //===============================================================================
  // Interface function for namespace, should be enough to call just this 
  //===============================================================================
  RooAbsPdf* buildAnalyticalShape(RooAbsReal& mass,
                                  RooWorkspace* workInt,
                                  TString samplemode,
                                  TString typemode,
                                  TString type,
                                  bool debug)
  {

    RooAbsPdf* pdf = NULL;
    TString varName = mass.GetName();

    Bool_t sharedMean = false;
    if ( type.Contains("SharedMean") == true ) { sharedMean = true; }
    Bool_t widthRatio = false;
    if ( type.Contains("WithWidthRatio") == true ) { widthRatio = true; }
    Bool_t separatedMean = false;
    if ( type.Contains("SeparatedMean") == true ) { separatedMean = true; }
    Bool_t shiftMean = false;
    if ( type.Contains("ShiftMean") == true ) { shiftMean = true; }
    Bool_t scaleWidths = false;
    if ( type.Contains("scaleWidths") == true ) { scaleWidths = true; }

    if ( type.Contains("HILL") )
      {
        pdf = buildHILLdini(mass, workInt, samplemode, typemode, debug);
      }
    else if ( type.Contains("HORNS") )
      {
        pdf = buildHORNSdini(mass, workInt, samplemode, typemode, debug);
      }
    else if ( type.Contains("Ipatia") or type.Contains("Hypatia") )
      {
        if ( type.Contains("Johnson") == true )
          {
            pdf = Bd2DhModels::buildIpatiaPlusJohnsonSUPDF(mass, workInt, samplemode, typemode, shiftMean, false, debug);
          }
        else
          {
            pdf =  buildIpatiaPDF( mass, workInt, samplemode, typemode, false, debug); //don't consider rescaled tails, for now                                       
	  }
      }
    else if ( type.Contains("Johnson") == true )
      {
        if ( type.Contains("PlusGaussianPlusExponential") == true  )
          {
            pdf = Bd2DhModels::buildJohnsonSUPlusGaussianPlusExponentialPDF(mass, workInt, samplemode, typemode, sharedMean, debug);
          }
        else if ( type.Contains("PlusGaussian") == true )
          {
            pdf = Bd2DhModels::buildJohnsonSUPlusGaussianPDF(mass, workInt, samplemode, typemode, sharedMean, shiftMean, debug);
          }
        else if( type.Contains("Plus2Gaussian") == true )
          {
            pdf = Bd2DhModels::buildJohnsonSUPlus2GaussianPDF(mass, workInt, samplemode, typemode, sharedMean, debug);
          }
        else if ( type == "Johnson" || type == "JohnsonSU" )
          {
            pdf = Bd2DhModels::buildJohnsonSUPDF(mass, workInt, samplemode, typemode, shiftMean, debug);
          }
        else
          {
	    std::cout<<"[ERROR] function: "<<type<<" not defined"<<std::endl;
          }
      }
    else if ( type.Contains("Apollonios") == true )
      {
        pdf =  buildApolloniosPDF( mass, workInt, samplemode, typemode, debug);
      }
    else if ( type.Contains("CrystalBall" ) )
      {
        if ( type.Contains("Exponential") )
          {
            pdf= BasicMDFitPdf::buildExponentialPlusDoubleCrystalBallPDF(mass, workInt, samplemode, typemode, widthRatio, sharedMean, debug);
          }
        else if ( type.Contains("DoubleCrystalBall") )
          {
            pdf =  BasicMDFitPdf::buildDoubleCrystalBallPDF( mass, workInt, samplemode, typemode, widthRatio, sharedMean, debug);
          }
        else if ( type.Contains("PlusGaussian") )
          {
            pdf = Bd2DhModels::buildCrystalBallPlusGaussianPDF(mass, workInt, samplemode, typemode, shiftMean, scaleWidths, debug);
          }
        else if ( type == "CrystalBall" )
          {
            pdf =  BasicMDFitPdf::buildCrystalBallPDF( mass, workInt, samplemode, typemode, debug);
          }
        else
          {
	    std::cout<<"[ERROR] function: "<<type<<" not defined"<<std::endl;
          }
      }
    else if ( type.Contains("Gaussian") )
      {
        if ( type.Contains("DoubleGaussian"))
          {
            pdf = buildDoubleGaussPDF( mass, workInt, samplemode, typemode, widthRatio, sharedMean, separatedMean, false, debug);
          }
        else if ( type == "Gaussian" )
          {
            pdf = buildGaussPDF( mass, workInt, samplemode, typemode, debug);
          }
        else
          {
	    std::cout<<"[ERROR] function: "<<type<<" not defined"<<std::endl;
          }
      }
    else if ( type.Contains("Exponential") )
      {
        if ( type == "ExponentialPlusGaussian" )
          {
            pdf = buildExponentialPlusGaussPDF(mass, workInt, samplemode, typemode, debug);
          }
        else if ( type == "Exponential" )
          {
            pdf = buildExponentialPDF(mass, workInt, samplemode, typemode, debug);
          }
        else if ( type == "DoubleExponential" )
          {
            pdf = buildDoubleExponentialPDF(mass, workInt, samplemode, typemode, debug);
          }
        else if ( type == "ExponentialTimesLinear" )
          {
            pdf = buildExponentialTimesLinearPDF(mass, workInt, samplemode, typemode, debug);
          }
        else if ( type == "ExponentialPlusSignal")
          {
            pdf = buildExponentialPlusSignalPDF(mass, workInt, samplemode, typemode, debug);
          }
        else
          {
	    std::cout<<"[ERROR] function: "<<type<<" not defined"<<std::endl;
          }
      }
    else
      {
	std::cout<<"[ERROR] Type of PDF: "<<type<<" is not specified. Please add to 'build_Signal_MDFitter' function."<<std::endl;
        return NULL;
      }

    return pdf;
  }



  
} // end of namespace

//=============================================================================








