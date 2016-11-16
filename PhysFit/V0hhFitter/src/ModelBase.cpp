// $Id: $
// Include files
// C++ libraries
#include <sstream>
#include <iostream>

// Boost
//#include <boost/algorithm/string.hpp>

// RooFit
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooPlot.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooVoigtian.h"
#include "RooSimultaneous.h"
#include "RooFitResult.h"
#include "RooUnblindPrecision.h"
#include "RooUnblindUniform.h"
#include "RooStats/SPlot.h"
#include "RooMCStudy.h"
#include "RooRandom.h"
#include "RooKeysPdf.h"
#include "RooDecay.h"
#include "RooGaussModel.h"
#include "RooAddModel.h"
#include "RooBifurGauss.h"
#include "RooArgusBG.h"
#include "RooFFTConvPdf.h"

// ROOT 
#include "TChain.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TString.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TEntryList.h"
#include "TAxis.h"
#include "TPaveLabel.h"
#include "TRandom.h"
#include "TH1F.h"

// local
#include "V0hhFitter/ModelBase.h"
#include "V0hhFitter/ClientTree.h"
#include "V0hhFitter/Exceptions.h"
#include "V0hhFitter/RooCruijff.h"
#include "V0hhFitter/RooCruijffSimple.h"
#include "V0hhFitter/RooAmorosoPdf.h"
#include "V0hhFitter/RooApollonios.h"
#include "V0hhFitter/RooHypatia.h"
#include "V0hhFitter/RooHypatia2.h"
#include "V0hhFitter/FitterLikesRatioPlot.h"

//-----------------------------------------------------------------------------
// Implementation file for class : ModelBase
//
// 2014-01-08 : Matthew M Reid
// 
//-----------------------------------------------------------------------------

using V0hhFit::IOFailure;
using V0hhFit::TDirectoryError;
using V0hhFit::GeneralException;
using V0hhFit::WSImportFailure;
using V0hhFit::WSRetrievalFailure;
using namespace V0hhFit;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
ModelBase::ModelBase(  ) : Fitter() {
}

//=============================================================================
// Constructor with name and title.
//=============================================================================
ModelBase::ModelBase( const char* name, const char* title ) 
    : Fitter(name, title) {
}

//=============================================================================
// Bifurcated Gaussian p.d.f with different widths on left and right side of 
// maximum value, from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeBiFurGauss(const char* pdfName, RooRealVar& mu, 
        RooRealVar& sigL, RooRealVar& sigRoSigL,
        const char* sigRName, const char* sigRTitle)                    
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeBiFurGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeBiFurGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = static_cast<std::string>(pdfName);
    
    RooFormulaVar sigR(sigRName, sigRTitle, "@0*@1", 
            RooArgList( sigRoSigL,sigL ) );
    sigR.setUnit( sigL.getUnit() );

    RooBifurGauss bfg0( theName.c_str(), "", *mass, mu, sigL, sigR);

    if (m_rws->import( bfg0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeBiFurGauss",
                *m_rws, bfg0);
    }
}

//=============================================================================
// Bifurcated Gaussian p.d.f with different widths on left and right side of 
// maximum value, from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeBiFurGauss(const char* pdfName, 
                    Float_t mu_start, Float_t mu_min, Float_t mu_max, 
                    Float_t sigL_start, Float_t sigL_min, Float_t sigL_max,
                    Float_t sigRoSigL_start, Float_t sigRoSigL_min, Float_t sigRoSigL_max,
                    const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeBiFurGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeBiFurGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    
    TString muTitle="";
    TString sigLTitle="";
    TString sigRoSigLTitle="";
    TString sigRTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigLTitle="#sigma_{L}";
        sigRoSigLTitle="#sigma_{R}/#sigma_{L}";
        sigRTitle="#sigma_{R}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sigLTitle.Form("%s #sigma_{L}", m_1DFitVarPartName);
        sigRoSigLTitle.Form("%s #sigma_{R}/#sigma_{L}", m_1DFitVarPartName);
        sigRTitle.Form("%s #sigma_{R}", m_1DFitVarPartName);
    }

    std::string theName = static_cast<std::string>(pdfName);

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sigL((theName+"_sigmaL").c_str(), sigLTitle.Data(),
            sigL_start, sigL_min, sigL_max, unit);

    RooRealVar sigRoSigL( (theName+"_sRoSL").c_str(), sigRoSigLTitle.Data(),
            sigRoSigL_start, sigRoSigL_min, sigRoSigL_max, unit);

    RooFormulaVar sigR( (theName+"_sigmaR").c_str(), sigRTitle.Data(), "@0*@1", 
            RooArgList( sigRoSigL,sigL ) );
    sigR.setUnit( sigL.getUnit() );

    RooBifurGauss bfg0( theName.c_str(), "", *mass, mu, sigL, sigR);

    if (m_rws->import( bfg0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeBiFurGauss",
                *m_rws, bfg0);
    }
}

//=============================================================================
// Argus from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeArgus(const char* pdfName, RooRealVar& endpoint, RooRealVar& c )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgus", 
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgus",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = static_cast<std::string>(pdfName);

    RooArgusBG ag0( theName.c_str(), "", *mass, endpoint, c );

    if (m_rws->import( ag0, RooFit::RecycleConflictNodes( kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeArgus",
                *m_rws, ag0);
    }
}

//=============================================================================
// Argus from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeArgus(const char* pdfName, 
        Float_t endpoint_start, Float_t endpoint_min, Float_t endpoint_max, 
        Float_t c_start, Float_t c_min, Float_t c_max,
        const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgus",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgus",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString endpointTitle="";
    TString cTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        endpointTitle="Kinematic Endpoint";
        cTitle="Argus Parameter";
    }
    else {
        endpointTitle.Form("%s Kinematic Endpointu", m_1DFitVarPartName);
        cTitle.Form("%s Argus Parameter", m_1DFitVarPartName);
    }

    std::string theName = static_cast<std::string>(pdfName);

    RooRealVar endpoint((theName+"_endpoint").c_str(), endpointTitle.Data(), endpoint_start,
            endpoint_min, endpoint_max, unit);
    RooRealVar c((theName+"_c").c_str(), cTitle.Data(),
            c_start, c_min, c_max );
    RooArgusBG argus0( pdfName, "", *mass, endpoint, c );

    if (m_rws->import( argus0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeArgus",
                *m_rws, argus0);
    }
}

//=============================================================================
// Argus from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeArgus(const char* pdfName, 
						  Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
						  Float_t slope0, Float_t slope_min, Float_t slope_max, 
						  Float_t power0, Float_t power_min, Float_t power_max,
						  const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgus",
							   "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgus",
								 *m_rws, m_1DFitVarName, "RooRealVar");
    }
	
    std::string theName = static_cast<std::string>(pdfName);    
    TString threshTitle="";
    TString slopeTitle="";
    TString powerTitle="";
	
    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        threshTitle="threshold";
        slopeTitle="slope";
        powerTitle="power";
		
    } else {

        threshTitle.Form("%s threshold", m_1DFitVarPartName);
        slopeTitle.Form("%s slope", m_1DFitVarPartName);
        powerTitle.Form("%s power", m_1DFitVarPartName);
    }

    // Create Argus
    RooRealVar pThreshold((theName+"_threshold").c_str(), threshTitle.Data(), pThresh0, pThresh_min, pThresh_max,unit);
    RooRealVar slope((theName+"_slope").c_str(), slopeTitle.Data(), slope0, slope_min, slope_max);
    RooRealVar power((theName+"_power").c_str(), powerTitle.Data(), power0, power_min, power_max);


    RooArgusBG arg((theName).c_str(),"", *mass, pThreshold, slope, power);

    if (m_rws->import( arg, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure( "ModelBase::makeArgus",
                *m_rws, arg );
    }
}

//=============================================================================
// Single Gaussian with single mean from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeSingleGauss(const char* pdfName,RooRealVar& mu, RooRealVar& sig0)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeSingleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeSingleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    RooGaussian g0( pdfName, "", *mass, mu, sig0);

    if (m_rws->import( g0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeSingleGauss",
                *m_rws, g0);
    }
}

//=============================================================================
// Single Gaussian with single mean from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeSingleGauss(const char* pdfName,Float_t mu_start, Float_t mu_min,
        Float_t mu_max, Float_t sig0_start,
        Float_t sig0_min, Float_t sig0_max,
        const char* unit)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeSingleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeSingleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString sig0Title="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sig0Title="#sigma_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
            sig0_start, sig0_min, sig0_max, unit);
    RooGaussian g0( theName.c_str(), "", *mass, mu, sig0);

    if (m_rws->import( g0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeSingleGauss",
                *m_rws, g0);
    }
}

//=============================================================================
// Double Gaussian with single mean from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeDoubleGauss(const char* pdfName,RooRealVar& mu, RooRealVar& sig0,
        RooRealVar& sig1oSig0,
        RooRealVar& coreFrac,
        const char* sig1Name,
        const char* sig1Title)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig0);
    RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
            RooArgList(sig1oSig0,sig0));
    sig1.setUnit(sig0.getUnit());

    RooGaussian g1((theName+"_g1").c_str(), "", *mass, mu, sig1);
    RooAddPdf doubleg(pdfName, "",RooArgList(g0,g1),RooArgList(coreFrac));

    if (m_rws->import( doubleg, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeDoubleGauss",
                *m_rws, doubleg);
    }
}

//=============================================================================
// Double Gaussian with single mean from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeDoubleGauss(const char* pdfName,Float_t mu_start, Float_t mu_min,
        Float_t mu_max, Float_t sig0_start,
        Float_t sig0_min, Float_t sig0_max,
        Float_t sig1oSig0_start,
        Float_t sig1oSig0_min,
        Float_t sig1oSig0_max,
        Float_t coreFrac_start,
        const char* unit)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString sig0Title="";
    TString sig1oSig0Title="";
    TString sig1Title="";
    TString coreFracTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sig0Title="#sigma_{core}";
        sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
        sig1Title="#sigma_{tail}";
        coreFracTitle="f_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
        sig1Title.Form("%s #sigma_{tail}", m_1DFitVarPartName);
        sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_1DFitVarPartName);
        coreFracTitle.Form("%s f_{core}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
            sig0_start, sig0_min, sig0_max, unit);
    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig0);

    RooRealVar sig1oSig0((theName+"_s1oS0").c_str(), sig1oSig0Title.Data(),
            sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);

    RooFormulaVar sig1((theName+"_sigma1").c_str(), sig1Title.Data(), "@0*@1", 
            RooArgList(sig1oSig0,sig0));
    sig1.setUnit(unit);

    RooGaussian g1((theName+"_g1").c_str(), "", *mass, mu, sig1);

    RooRealVar coreFrac((theName+"_coreFrac").c_str(), coreFracTitle.Data(),
            coreFrac_start,0.0,1);

    RooAddPdf doubleg(pdfName, "",RooArgList(g0,g1),RooArgList(coreFrac));

    if ( m_rws->import( doubleg, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeDoubleGauss",
                *m_rws, doubleg);
    }
}

//=============================================================================
// Double Gaussian with single mean from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeDoubleGauss(const char* pdfName,
				Float_t mu_start, Float_t mu_min, Float_t mu_max,
				Float_t dM_start, Float_t dM_min, Float_t dM_max,
				Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
				Float_t sig1oSig0_start, Float_t sig1oSig0_min, Float_t sig1oSig0_max,
				Float_t coreFrac_start,
				const char* unit)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString dMTitle="";
    TString sig0Title="";
    TString sig1oSig0Title="";
    TString sig1Title="";
    TString coreFracTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        dMTitle="#/Delta(m)";
        sig0Title="#sigma_{core}";
        sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
        sig1Title="#sigma_{tail}";
        coreFracTitle="f_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        dMTitle.Form("%s #/Delta(m)",m_1DFitVarPartName);
        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
        sig1Title.Form("%s #sigma_{tail}", m_1DFitVarPartName);
        sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_1DFitVarPartName);
        coreFracTitle.Form("%s f_{core}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
		  mu_min, mu_max, unit);
    RooRealVar dM((theName+"_dM").c_str(), dMTitle.Data(), dM_start,
		  dM_min, dM_max, unit);
    
    RooFormulaVar mu1((theName+"_mu1").c_str(), "@0+@1",RooArgSet(mu,dM));
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
		    sig0_start, sig0_min, sig0_max, unit);
    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig0);
    
    RooRealVar sig1oSig0((theName+"_s1oS0").c_str(), sig1oSig0Title.Data(),
			 sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
    
    RooFormulaVar sig1((theName+"_sigma1").c_str(), sig1Title.Data(), "@0*@1", 
		       RooArgList(sig1oSig0,sig0));
    sig1.setUnit(unit);
    
    RooGaussian g1((theName+"_g1").c_str(), "", *mass, mu1, sig1);
    
    RooRealVar coreFrac((theName+"_coreFrac").c_str(), coreFracTitle.Data(),
			coreFrac_start,0.0,1);
    
    RooAddPdf doubleg(pdfName, "",RooArgList(g0,g1),RooArgList(coreFrac));

    if ( m_rws->import( doubleg, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeDoubleGauss",
                *m_rws, doubleg);
    }
}

//=============================================================================
// Voigtian is an efficient implementation of the convolution of a Breit-Wigner 
// with a Gaussian, making use of the complex error function, from RooRealVars, 
// and import to workspace
//=============================================================================
void ModelBase::makeSingleVoigtian( const char* pdfName, RooRealVar& mu, 
        RooRealVar& width0, RooRealVar& sig0 )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeSingleVoigtian",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeSingleVoigtian",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = static_cast<std::string>(pdfName);

    RooVoigtian v0( theName.c_str(), "", *mass, mu, width0, sig0 );

    if (m_rws->import( v0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure( "ModelBase::makeSingleVoigtian",
                *m_rws, v0 );
    }
}


//=============================================================================
// Voigtian is an efficient implementation of the convolution of a Breit-Wigner 
// with a Gaussian, making use of the complex error function, from RooRealVars, 
// and import to workspace
//=============================================================================
void ModelBase::makeSingleVoigtian( const char* pdfName,  
        Float_t mu_start, Float_t mu_min, Float_t mu_max, 
        Float_t width0_start, Float_t width0_min, Float_t width0_max,
        Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
        const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeSingleVoigtian",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeSingleVoigtian",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString sig0Title="";
    TString width0Title="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sig0Title="#sigma_{core}";
        width0Title="#gamma_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
        width0Title.Form("%s #gamma_{core}", m_1DFitVarPartName);
    }

    std::string theName = static_cast<std::string>(pdfName);

    // create the Voigtian
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar width0((theName+"_width0").c_str(), width0Title.Data(),
            width0_start, width0_min, width0_max, unit);
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
            sig0_start, sig0_min, sig0_max, unit);

    RooVoigtian v0( theName.c_str(), "", *mass, mu, width0, sig0 );

    if (m_rws->import( v0, RooFit::RecycleConflictNodes(kTRUE ) ) ) {
        throw WSImportFailure( "ModelBase::makeSingleVoigtian",
                *m_rws, v0 );
    }
}

//=============================================================================
// Single Crystal ball with single mean from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeSingleCB( const char* pdfName, RooRealVar& mu, 
        RooRealVar& sig0, RooRealVar& alpha0,
        RooRealVar& n0 )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeSingleCB",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeSingleCB",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    RooCBShape cb0( theName.c_str(), "", *mass, mu, sig0, alpha0, n0 );

    if (m_rws->import( cb0, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure( "ModelBase::makeSingleCB",
                *m_rws, cb0 );
    }
}

//=============================================================================
// Single Crystal ball with single mean from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeSingleCB(const char* pdfName, 
        Float_t mu_start, Float_t mu_min, Float_t mu_max, 
        Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
        Float_t alpha0_start, Float_t alpha0_min, Float_t alpha0_max,
        Float_t n0_start, Float_t n0_min, Float_t n0_max,
        const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeSingleCB",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeSingleCB",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString sig0Title="";
    TString alpha0Title="";
    TString n0Title="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sig0Title="#sigma_{core}";
        alpha0Title="#alpha_{core}";
        n0Title="n_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
        alpha0Title.Form("%s #alpha_{core}", m_1DFitVarPartName);
        n0Title.Form("%s n_{core}", m_1DFitVarPartName);
    }

    std::string theName = static_cast<std::string>( pdfName );

    // create the crystal ball
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
            sig0_start, sig0_min, sig0_max, unit);
    RooRealVar alpha0((theName+"_alpha0").c_str(), alpha0Title.Data(),
            alpha0_start, alpha0_min, alpha0_max, unit);
    RooRealVar n0((theName+"_n0").c_str(), n0Title.Data(),
            n0_start, n0_min, n0_max, unit);
    RooCBShape cb0( theName.c_str(), "", *mass, mu, sig0, alpha0, n0 );

    if ( m_rws->import( cb0, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeSingleCB",
                *m_rws, cb0);
    }
}

//=============================================================================
// Double Crystal ball with single mean from RooRealVars, and import to workspace
//=============================================================================
void ModelBase::makeDoubleCB(const char* pdfName, RooRealVar& mu, 
        RooRealVar& sig0, RooRealVar& sig1oSig0, 
        RooRealVar& alpha0, RooRealVar& alpha1oAlpha0,
        RooRealVar& n0, RooRealVar& n1oN0,
        RooRealVar& coreFrac, 
        const char* sig1Name, const char* sig1Title,
        const char* alpha1Name, const char* alpha1Title,
        const char* n1Name, const char* n1Title)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleCB",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleCB",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    RooCBShape cb0((theName+"_cb0").c_str(), "", *mass, mu, sig0, alpha0, n0 );
    RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
            RooArgList(sig1oSig0,sig0));
    sig1.setUnit( sig0.getUnit() );

    RooFormulaVar alpha1( alpha1Name, alpha1Title, "@0*@1", 
            RooArgList(alpha1oAlpha0,alpha0));
    alpha1.setUnit( alpha0.getUnit() );

    RooFormulaVar n1( n1Name, n1Title, "@0*@1", 
            RooArgList(n1oN0,n0));
    n1.setUnit( n0.getUnit() );

    RooCBShape cb1((theName+"_cb1").c_str(), "", *mass, mu, sig1, alpha1, n1 );

    RooAddPdf doublecb( pdfName, "", RooArgList( cb0, cb1 ), RooArgList( coreFrac ) );

    if (m_rws->import( doublecb, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure( "ModelBase::makeDoubleCB",
                *m_rws, doublecb );
    }
}


//=============================================================================
// Double Crystal ball with single mean from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeDoubleCB(const char* pdfName, 
        Float_t mu_start, Float_t mu_min, Float_t mu_max, 
        Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
        Float_t sig1oSig0_start, Float_t sig1oSig0_min, Float_t sig1oSig0_max,
        Float_t alpha0_start, Float_t alpha0_min, Float_t alpha0_max,
        Float_t alpha1oAlpha0_start, Float_t alpha1oAlpha0_min, Float_t alpha1oAlpha0_max,
        Float_t n0_start, Float_t n0_min, Float_t n0_max,
        Float_t n1oN0_start, Float_t n1oN0_min, Float_t n1oN0_max,
        Float_t coreFrac_start,
        const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleCB",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleCB",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";

    TString sig0Title="";
    TString sig1oSig0Title="";
    TString sig1Title="";

    TString alpha0Title="";
    TString alpha1oAlpha0Title="";
    TString alpha1Title="";

    TString n0Title="";
    TString n1oN0Title="";
    TString n1Title="";

    TString coreFracTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";

        sig0Title="#sigma_{core}";
        sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
        sig1Title="#sigma_{tail}";

        alpha0Title="#alpha_{core}";
        alpha1oAlpha0Title="#alpha_{tail}/#alpha_{core}";
        alpha1Title="#alpha_{tail}";

        n0Title="n_{core}";
        n1oN0Title="n_{tail}/n_{core}";
        n1Title="n_{tail}";

        coreFracTitle="f_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);

        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
        sig1Title.Form("%s #sigma_{tail}", m_1DFitVarPartName);
        sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_1DFitVarPartName);

        alpha0Title.Form("%s #alpha_{core}", m_1DFitVarPartName);
        alpha1Title.Form("%s #alpha_{tail}", m_1DFitVarPartName);
        alpha1oAlpha0Title.Form("%s #alpha_{tail}/#alpha_{core}", m_1DFitVarPartName);        

        n0Title.Form("%s n_{core}", m_1DFitVarPartName);
        n1Title.Form("%s n_{tail}", m_1DFitVarPartName);
        n1oN0Title.Form("%s n_{tail}/n_{core}", m_1DFitVarPartName);

        coreFracTitle.Form("%s f_{core}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    // create the first crystal ball
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
            sig0_start, sig0_min, sig0_max, unit);
    RooRealVar alpha0((theName+"_alpha0").c_str(), alpha0Title.Data(),
            alpha0_start, alpha0_min, alpha0_max, unit);
    RooRealVar n0((theName+"_n0").c_str(), n0Title.Data(),
            n0_start, n0_min, n0_max, unit);
    RooCBShape cb0( (theName+"_cb0").c_str(), "", *mass, mu, sig0, alpha0, n0 );


    // create the second crystal ball
    RooRealVar sig1oSig0( (theName+"_s1oS0").c_str(), sig1oSig0Title.Data(),
            sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
    RooFormulaVar sig1( (theName+"_sigma1").c_str(), sig1Title.Data(), "@0*@1", 
            RooArgList(sig1oSig0,sig0));
    sig1.setUnit(unit);

    RooRealVar alpha1oAlpha0( (theName+"_alpha1oAlpha0").c_str(), alpha1oAlpha0Title.Data(),
            alpha1oAlpha0_start, alpha1oAlpha0_min, alpha1oAlpha0_max);
    RooFormulaVar alpha1( (theName+"_alpha1").c_str(), alpha1Title.Data(), "@0*@1", 
            RooArgList(alpha1oAlpha0,alpha0));
    //alpha1.setUnit(unit);
    RooRealVar n1oN0( (theName+"_n1oN0").c_str(), n1oN0Title.Data(),
            n1oN0_start, n1oN0_min, n1oN0_max);
    RooFormulaVar n1( (theName+"_n1").c_str(), n1Title.Data(), "@0*@1", 
            RooArgList(n1oN0,n0));
    //n1.setUnit(unit);

    RooCBShape cb1( (theName+"_cb1").c_str(), "", *mass, mu, sig1, alpha1, n1 );


    // add the two crystal ball functions together.
    RooRealVar coreFrac( ( theName+"_coreFrac" ).c_str(), coreFracTitle.Data(),
            coreFrac_start, 0.0, 1.0);
    RooAddPdf doublecb( pdfName, "", RooArgList( cb0, cb1 ), RooArgList(coreFrac) );

    if ( m_rws->import( doublecb, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeDoubleCB",
                *m_rws, doublecb);
    }
}

//=============================================================================
// Double Crystal ball with single sigma from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeDoubleCBDiffMeans(const char* pdfName, 						
        Float_t mu_start, Float_t mu_min, Float_t mu_max, 
        Float_t dM_start, Float_t dM_min, Float_t dM_max,
        Float_t sig_start, Float_t sig_min, Float_t sig_max,
        Float_t alpha0_start, Float_t alpha0_min, Float_t alpha0_max,
        Float_t alpha1oAlpha0_start, Float_t alpha1oAlpha0_min, Float_t alpha1oAlpha0_max,
        Float_t n0_start, Float_t n0_min, Float_t n0_max,
        Float_t n1oN0_start, Float_t n1oN0_min, Float_t n1oN0_max,
        Float_t coreFrac_start,
        const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleCB",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleCB",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString mu1Title="";
    TString dMTitle="";

    TString sigTitle="";

    TString alpha0Title="";
    TString alpha1oAlpha0Title="";
    TString alpha1Title="";

    TString n0Title="";
    TString n1oN0Title="";
    TString n1Title="";

    TString coreFracTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        mu1Title="#mu_{1}";
        dMTitle="#Delta(M)";
        sigTitle="#sigma_{core}";

        alpha0Title="#alpha_{core}";
        alpha1oAlpha0Title="#alpha_{tail}/#alpha_{core}";
        alpha1Title="#alpha_{tail}";

        n0Title="n_{core}";
        n1oN0Title="n_{tail}/n_{core}";
        n1Title="n_{tail}";

        coreFracTitle="f_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        mu1Title.Form("%s #mu_{1}", m_1DFitVarPartName);
        dMTitle.Form("%s #Delta(M)",m_1DFitVarPartName);
        sigTitle.Form("%s #sigma_{core}", m_1DFitVarPartName);

        alpha0Title.Form("%s #alpha_{core}", m_1DFitVarPartName);
        alpha1Title.Form("%s #alpha_{tail}", m_1DFitVarPartName);
        alpha1oAlpha0Title.Form("%s #alpha_{tail}/#alpha_{core}", m_1DFitVarPartName);        

        n0Title.Form("%s n_{core}", m_1DFitVarPartName);
        n1Title.Form("%s n_{tail}", m_1DFitVarPartName);
        n1oN0Title.Form("%s n_{tail}/n_{core}", m_1DFitVarPartName);

        coreFracTitle.Form("%s f_{core}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    // create the first crystal ball
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(),
            sig_start, sig_min, sig_max, unit);
    RooRealVar alpha0((theName+"_alpha0").c_str(), alpha0Title.Data(),
            alpha0_start, alpha0_min, alpha0_max, unit);
    RooRealVar n0((theName+"_n0").c_str(), n0Title.Data(),
            n0_start, n0_min, n0_max, unit);
    RooCBShape cb0( (theName+"_cb0").c_str(), "", *mass, mu, sig, alpha0, n0 );

    // create the second crystal ball
    RooRealVar dM((theName+"_dM").c_str(), dMTitle.Data(), dM_start,
            dM_min, dM_max, unit);
    RooFormulaVar mu1( (theName+"_mu1").c_str(), mu1Title.Data(), "@0+@1", 
            RooArgList(dM,mu));
    mu1.setUnit(unit);

    RooRealVar alpha1oAlpha0( (theName+"_alpha1oAlpha0").c_str(), alpha1oAlpha0Title.Data(),
            alpha1oAlpha0_start, alpha1oAlpha0_min, alpha1oAlpha0_max);
    RooFormulaVar alpha1( (theName+"_alpha1").c_str(), alpha1Title.Data(), "@0*@1", 
            RooArgList(alpha1oAlpha0,alpha0));
    //alpha1.setUnit(unit);
    RooRealVar n1oN0( (theName+"_n1oN0").c_str(), n1oN0Title.Data(),
            n1oN0_start, n1oN0_min, n1oN0_max);
    RooFormulaVar n1( (theName+"_n1").c_str(), n1Title.Data(), "@0*@1", 
            RooArgList(n1oN0,n0));
    //n1.setUnit(unit);

    RooCBShape cb1( (theName+"_cb1").c_str(), "", *mass, mu1, sig, alpha1, n1 );


    // add the two crystal ball functions together.
    RooRealVar coreFrac( ( theName+"_coreFrac" ).c_str(), coreFracTitle.Data(),
            coreFrac_start, 0.0, 1.0);
    RooAddPdf doublecb( pdfName, "", RooArgList( cb0, cb1 ), RooArgList(coreFrac) );

    if ( m_rws->import( doublecb, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeDoubleCB",
                *m_rws, doublecb);
    }
}

//=============================================================================
// Double Crystal ball with a single mean and width from Float_ts, and import to workspace
//=============================================================================
void ModelBase::makeDoubleCB(const char* pdfName, 
        Float_t mu_start, Float_t mu_min, Float_t mu_max, 
        Float_t sig_start, Float_t sig_min, Float_t sig_max,
        Float_t alpha0_start, Float_t alpha0_min, Float_t alpha0_max,
        Float_t alpha1oAlpha0_start, Float_t alpha1oAlpha0_min, Float_t alpha1oAlpha0_max,
        Float_t n0_start, Float_t n0_min, Float_t n0_max,
        Float_t n1oN0_start, Float_t n1oN0_min, Float_t n1oN0_max,
        Float_t coreFrac_start,
        const char* unit )
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeDoubleCB",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeDoubleCB",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";

    TString sigTitle="";

    TString alpha0Title="";
    TString alpha1oAlpha0Title="";
    TString alpha1Title="";

    TString n0Title="";
    TString n1oN0Title="";
    TString n1Title="";

    TString coreFracTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";

        sigTitle="#sigma_{core}";

        alpha0Title="#alpha_{core}";
        alpha1oAlpha0Title="#alpha_{tail}/#alpha_{core}";
        alpha1Title="#alpha_{tail}";

        n0Title="n_{core}";
        n1oN0Title="n_{tail}/n_{core}";
        n1Title="n_{tail}";

        coreFracTitle="f_{core}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);

        sigTitle.Form("%s #sigma", m_1DFitVarPartName);

        alpha0Title.Form("%s #alpha_{core}", m_1DFitVarPartName);
        alpha1Title.Form("%s #alpha_{tail}", m_1DFitVarPartName);
        alpha1oAlpha0Title.Form("%s #alpha_{tail}/#alpha_{core}", m_1DFitVarPartName);        

        n0Title.Form("%s n_{core}", m_1DFitVarPartName);
        n1Title.Form("%s n_{tail}", m_1DFitVarPartName);
        n1oN0Title.Form("%s n_{tail}/n_{core}", m_1DFitVarPartName);

        coreFracTitle.Form("%s f_{core}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    // create the first crystal ball
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(),
            sig_start, sig_min, sig_max, unit);
    RooRealVar alpha0((theName+"_alpha0").c_str(), alpha0Title.Data(),
            alpha0_start, alpha0_min, alpha0_max, unit);
    RooRealVar n0((theName+"_n0").c_str(), n0Title.Data(),
            n0_start, n0_min, n0_max, unit);
    RooCBShape cb0( (theName+"_cb0").c_str(), "", *mass, mu, sig, alpha0, n0 );


    // create the second crystal ball
    RooRealVar alpha1oAlpha0( (theName+"_alpha1oAlpha0").c_str(), alpha1oAlpha0Title.Data(),
            alpha1oAlpha0_start, alpha1oAlpha0_min, alpha1oAlpha0_max);
    RooFormulaVar alpha1( (theName+"_alpha1").c_str(), alpha1Title.Data(), "@0*@1", 
            RooArgList(alpha1oAlpha0,alpha0));
    //alpha1.setUnit(unit);
    RooRealVar n1oN0( (theName+"_n1oN0").c_str(), n1oN0Title.Data(),
            n1oN0_start, n1oN0_min, n1oN0_max);
    RooFormulaVar n1( (theName+"_n1").c_str(), n1Title.Data(), "@0*@1", 
            RooArgList(n1oN0,n0));
    //n1.setUnit(unit);

    RooCBShape cb1( (theName+"_cb1").c_str(), "", *mass, mu, sig, alpha1, n1 );


    // add the two crystal ball functions together.
    RooRealVar coreFrac( ( theName+"_coreFrac" ).c_str(), coreFracTitle.Data(),
            coreFrac_start, 0.0, 1.0);
    RooAddPdf doublecb( pdfName, "", RooArgList( cb0, cb1 ), RooArgList(coreFrac) );

    if ( m_rws->import( doublecb, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("ModelBase::makeDoubleCB",
                *m_rws, doublecb);
    }
}

//=============================================================================
// Argus function convoluted with a Gaussian for partially reconstructed bkg
//=============================================================================
void ModelBase::makeArgusConvGauss( const char* pdfName, Float_t sigGauss, 
				    Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
				    Float_t slope0, Float_t slope_min, Float_t slope_max, 
				    Float_t power0, Float_t power_min, Float_t power_max ) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgusConvGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);

    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgusConvGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    TString muTitle="";
    TString sigTitle="";

    TString threshTitle="";
    TString slopeTitle="";
    TString powerTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigTitle="#sigma";

        threshTitle="threshold";
        slopeTitle="slope";
        powerTitle="power";

    } else {
        muTitle.Form("%s #mu", m_1DFitVarPartName); 
        sigTitle.Form("%s #sigma", m_1DFitVarPartName); 

        threshTitle.Form("%s threshold", m_1DFitVarPartName);
        slopeTitle.Form("%s slope", m_1DFitVarPartName);
        powerTitle.Form("%s power", m_1DFitVarPartName);
    }

    // create first the Gaussian
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), 0);    
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sigGauss);    

    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig);

    // Create Argus
    RooRealVar pThreshold((theName+"_threshold").c_str(), threshTitle.Data(), pThresh0, pThresh_min, pThresh_max);
    RooRealVar slope((theName+"_slope").c_str(), slopeTitle.Data(), slope0, slope_min, slope_max);    
    RooRealVar power((theName+"_power").c_str(), powerTitle.Data(), power0, power_min, power_max);    


    RooArgusBG arg((theName+"_argus").c_str(),"", *mass, pThreshold, slope, power);

    // Convolute the Gaussian + Argus
    RooFFTConvPdf argusNgauss( pdfName, "", *mass, arg, g0);
    argusNgauss.setBufferFraction(0.5);

    if (m_rws->import( argusNgauss, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure( "ModelBase::makeArgusConvGauss",
                *m_rws, argusNgauss );
    }
}

//=============================================================================
// Argus function convoluted with a Gaussian for partially reconstructed bkg
//=============================================================================
void ModelBase::makeArgusConvGauss( const char* pdfName,
        Float_t sigGauss0, Float_t sigGauss_min, Float_t sigGauss_max,
        Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
        Float_t slope0, Float_t slope_min, Float_t slope_max, 
        Float_t power0, Float_t power_min, Float_t power_max ) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgusConvGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);

    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgusConvGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    TString muTitle="";
    TString sigTitle="";

    TString threshTitle="";
    TString slopeTitle="";
    TString powerTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigTitle="#sigma";

        threshTitle="threshold";
        slopeTitle="slope";
        powerTitle="power";

    } else {
        muTitle.Form("%s #mu", m_1DFitVarPartName); 
        sigTitle.Form("%s #sigma", m_1DFitVarPartName); 

        threshTitle.Form("%s threshold", m_1DFitVarPartName);
        slopeTitle.Form("%s slope", m_1DFitVarPartName);
        powerTitle.Form("%s power", m_1DFitVarPartName);
    }

    // create first the Gaussian
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), 0);    
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sigGauss0, sigGauss_min, sigGauss_max);
    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig);

    // Create Argus
    RooRealVar pThreshold((theName+"_threshold").c_str(), threshTitle.Data(), pThresh0, pThresh_min, pThresh_max);    
    RooRealVar slope((theName+"_slope").c_str(), slopeTitle.Data(), slope0, slope_min, slope_max);    
    RooRealVar power((theName+"_power").c_str(), powerTitle.Data(), power0, power_min, power_max);    


    RooArgusBG arg((theName+"_argus").c_str(),"", *mass, pThreshold, slope, power);

    // Convolute the Gaussian + Argus
    RooFFTConvPdf argusNgauss( pdfName, "", *mass, arg, g0);
    argusNgauss.setBufferFraction(0.5);

    if (m_rws->import( argusNgauss, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure( "ModelBase::makeArgusConvGauss",
                *m_rws, argusNgauss );
    }
}

//=============================================================================
// Argus function convoluted with a Gaussian for partially reconstructed bkg
//=============================================================================
void ModelBase::makeArgusConvGaussFixed( const char* pdfName, Float_t sigGauss, 
        Float_t pThresh0, Float_t slope0, Float_t power0 ) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgusConvGaussFixed",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgusConvGaussFixed",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    TString muTitle="";
    TString sigTitle="";

    TString threshTitle="";
    TString slopeTitle="";
    TString powerTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigTitle="#sigma";

        threshTitle="threshold";
        slopeTitle="slope";
        powerTitle="power";

    } else {
        muTitle.Form("%s #mu", m_1DFitVarPartName); 
        sigTitle.Form("%s #sigma", m_1DFitVarPartName); 

        threshTitle.Form("%s threshold", m_1DFitVarPartName);
        slopeTitle.Form("%s slope", m_1DFitVarPartName);
        powerTitle.Form("%s power", m_1DFitVarPartName);
    }

    // create first the Gaussian
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), 0);    
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sigGauss);    

    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig);

    // Create Argus
    RooRealVar pThreshold((theName+"_threshold").c_str(), threshTitle.Data(), pThresh0);    
    RooRealVar slope((theName+"_slope").c_str(), slopeTitle.Data(), slope0);    
    RooRealVar power((theName+"_power").c_str(), powerTitle.Data(), power0);    


    RooArgusBG arg((theName+"_argus").c_str(),"", *mass, pThreshold, slope, power);

    // Convolute the Gaussian + Argus
    RooFFTConvPdf argusNgauss( pdfName, "", *mass, arg, g0);
    argusNgauss.setBufferFraction(0.5);

    if (m_rws->import( argusNgauss, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure( "ModelBase::makeArgusConvGaussFixed",
                *m_rws, argusNgauss );
    }
}

//=============================================================================
// Argus function convoluted with a Gaussian for partially reconstructed bkg
// An extra exponential pdf is added to account for spurios events after threshold
//=============================================================================
void ModelBase::makeArgusConvGaussNExp( const char* pdfName, Float_t sigGauss, 
        Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
        Float_t slope0, Float_t slope_min, Float_t slope_max, 
        Float_t power0, Float_t power_min, Float_t power_max,
        Float_t c1_start,  Float_t c1_min, Float_t c1_max,
	Float_t coreFrac_start ) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeArgusConvGaussNExp",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeArgusConvGaussNExp",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    TString muTitle="";
    TString sigTitle="";
    
    TString threshTitle="";
    TString slopeTitle="";
    TString powerTitle="";

    TString c1Title="";
    TString coreFracTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigTitle="#sigma";
        
	threshTitle="threshold";
	slopeTitle="slope";
	powerTitle="power";
         
        c1Title="#nabla";
	coreFracTitle="f_{core}";

    } else {
        muTitle.Form("%s #mu", m_1DFitVarPartName); 
        sigTitle.Form("%s #sigma", m_1DFitVarPartName); 

	threshTitle.Form("%s threshold", m_1DFitVarPartName);
	slopeTitle.Form("%s slope", m_1DFitVarPartName);
	powerTitle.Form("%s power", m_1DFitVarPartName);

	c1Title.Form("%s #nabla", m_1DFitVarPartName);
	coreFracTitle.Form("%s f_{core}", m_1DFitVarPartName);

    }
    
    // create first the Gaussian
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), 0);    
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sigGauss);    

    RooGaussian g0((theName+"_g0").c_str(), "", *mass, mu, sig);

    // Create Argus
    RooRealVar pThreshold((theName+"_threshold").c_str(), threshTitle.Data(), pThresh0, pThresh_min, pThresh_max);    
    RooRealVar slope((theName+"_slope").c_str(), slopeTitle.Data(), slope0, slope_min, slope_max);    
    RooRealVar power((theName+"_power").c_str(), powerTitle.Data(), power0, power_min, power_max);    


    RooArgusBG arg((theName+"_argus").c_str(),"", *mass, pThreshold, slope, power);

    // Convolute the Gaussian + Argus
    RooFFTConvPdf argusNgauss( pdfName, "", *mass, arg, g0);
    argusNgauss.setBufferFraction(0.5);
  
    // Define the exponential
    RooRealVar c1((theName+"_slope_bkg").c_str(), c1Title.Data(), c1_start, c1_min,
            c1_max);
    RooExponential BkgModel((theName+"_bkg").c_str(),"",*mass,c1);

    RooRealVar coreFrac((theName+"_coreFrac").c_str(), coreFracTitle.Data(),
            coreFrac_start,0.0,1);
    RooAddPdf argusNgaussNexp(pdfName, "",RooArgList(argusNgauss,BkgModel),RooArgList(coreFrac));

    if (m_rws->import( argusNgaussNexp, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure( "ModelBase::makeArgusConvGaussNExp",
                *m_rws, argusNgaussNexp );
    }
}

void ModelBase::makeTripleGauss(const char* pdfName,
        RooRealVar& mu,
        RooRealVar& sig0,
        RooRealVar& sig1oSig0,
        RooRealVar& sig2oSig0,
        RooRealVar& coreFrac0,
        RooRealVar& coreFrac1,
        const char* sig1Name,
        const char* sig1Title) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeTripleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeTripleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)pdfName;

    RooGaussian g0((theName+"_gauss0").c_str(), "", *mass, mu, sig0);
    RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
            RooArgList(sig1oSig0,sig0));
    RooFormulaVar sig2(sig1Name, sig1Title, "@0*@1", 
            RooArgList(sig2oSig0,sig0));
    sig1.setUnit(sig0.getUnit());

    RooGaussian g1((theName+"_gauss1").c_str(), "", *mass, mu, sig1);
    RooGaussian g2((theName+"_gauss2").c_str(), "", *mass, mu, sig2);

    RooAddPdf triplegauss(pdfName, "",
            RooArgList(g0,g1,g2),
            RooArgList(coreFrac0,coreFrac1));
    if ( m_rws->import( triplegauss, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeTripleGauss",
                *m_rws, triplegauss);
    }
}

void ModelBase::makeTripleGauss(const char* pdfName,
        Float_t mu_start, Float_t mu_min,
        Float_t mu_max, Float_t sig0_start,
        Float_t sig0_min, Float_t sig0_max,
        Float_t sig1oSig0_start,
        Float_t sig1oSig0_min,
        Float_t sig1oSig0_max,
        Float_t sig2oSig0_start,
        Float_t sig2oSig0_min,
        Float_t sig2oSig0_max,
        Float_t coreFrac0_start,
        Float_t coreFrac1_start,
        const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeTripleGauss",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeTripleGauss",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString muTitle="";
    TString sig0Title="";
    TString sig1oSig0Title="";
    TString sig1Title="";
    TString sig2Title="";
    TString sig2oSig0Title="";
    TString coreFrac0Title="";
    TString coreFrac1Title="";
    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sig0Title="#sigma_{core}";
        sig1oSig0Title="#sigma_{tail-1}/#sigma_{core}";
        sig2oSig0Title="#sigma_{tail-2}/#sigma_{core}";
        sig1Title="#sigma_{tail-1}";
        sig2Title="#sigma_{tail-2}";
        coreFrac0Title="f_{core}";
        coreFrac1Title="f_{wide}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sig0Title.Form("%s #sigma_{core}", m_1DFitVarPartName);
        sig1Title.Form("%s #sigma_{tail-1}", m_1DFitVarPartName);
        sig2Title.Form("%s #sigma_{tail-2}", m_1DFitVarPartName);
        sig1oSig0Title.Form("%s #sigma_{tail-1}/#sigma_{core}", m_1DFitVarPartName);
        sig2oSig0Title.Form("%s #sigma_{tail-2}/#sigma_{core}", m_1DFitVarPartName);
        coreFrac0Title.Form("%s f_{core}", m_1DFitVarPartName);
        coreFrac1Title.Form("%s f_{wide}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start,
            mu_min, mu_max, unit);
    RooRealVar sig0((theName+"_sigma0").c_str(), sig0Title.Data(),
            sig0_start, sig0_min, sig0_max, unit);
    RooGaussian g0((theName+"_gauss0").c_str(), "", *mass, mu, sig0);

    RooRealVar sig1oSig0((theName+"_s1oS0").c_str(), sig1oSig0Title.Data(),
            sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
    RooRealVar sig2oSig0((theName+"_s2oS0").c_str(), sig2oSig0Title.Data(),
            sig2oSig0_start, sig2oSig0_min, sig2oSig0_max);

    RooFormulaVar sig1((theName+"_sigma1").c_str(), sig1Title.Data(), "@0*@1", 
            RooArgList(sig1oSig0,sig0));
    sig1.setUnit(unit);
    RooFormulaVar sig2((theName+"_sigma2").c_str(), sig2Title.Data(), "@0*@1", 
            RooArgList(sig2oSig0,sig0));
    sig2.setUnit(unit);

    RooGaussian g1("dmass_sig_gauss1", "", *mass, mu, sig1);
    RooGaussian g2("dmass_sig_gauss2", "", *mass, mu, sig2);

    RooRealVar coreFrac0("dmass_sig_coreFrac0", coreFrac0Title.Data(),
            coreFrac0_start,0.0,1);
    RooRealVar coreFrac1("dmass_sig_coreFrac1", coreFrac1Title.Data(),
            coreFrac1_start,0.0,1);

    RooAddPdf triplegauss(pdfName, "", 
            RooArgList(g0,g1,g2),
            RooArgList(coreFrac0,coreFrac1));
    if ( m_rws->import( triplegauss, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeTripleGauss",
                *m_rws, triplegauss);
    }
}

void ModelBase::makeCruijff(const char* pdfName,
        RooRealVar& mu, RooRealVar& sigL,
        RooRealVar& sigR, RooRealVar& alphaL,
        RooRealVar& alphaR) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeCruijff",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeCruijff",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    RooCruijff theCruijff(pdfName, "", *mass, mu, sigL, sigR, alphaL,
            alphaR);

    if ( m_rws->import( theCruijff, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeCruijff",
                *m_rws, theCruijff);
    }
}


void ModelBase::makeCruijff(const char* pdfName,
        Float_t mu_start, Float_t mu_min,
        Float_t mu_max, Float_t sigL_start,
        Float_t sigL_min, Float_t sigL_max,
        Float_t sigR_start, Float_t sigR_min,
        Float_t sigR_max, Float_t alphaL_start,
        Float_t alphaL_min, Float_t alphaL_max,
        Float_t alphaR_start, Float_t alphaR_min,
        Float_t alphaR_max, const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeCruijff",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeCruijff",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString muTitle="";
    TString sigLTitle="";
    TString alphaLTitle="";
    TString sigRTitle="";
    TString alphaRTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigLTitle="#sigma_{L}";
        alphaLTitle="#alpha_{L}";
        sigRTitle="#sigma_{R}";
        alphaRTitle="#alpha_{R}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sigLTitle.Form("%s #sigma_{L}", m_1DFitVarPartName);
        alphaLTitle.Form("%s #alpha_{L}", m_1DFitVarPartName);
        sigRTitle.Form("%s #sigma_{R}", m_1DFitVarPartName);
        alphaRTitle.Form("%s #alpha_{R}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start, mu_min, mu_max, unit);
    RooRealVar sigL((theName+"_sigmaL").c_str(), sigLTitle.Data(), sigL_start, sigL_min, 
            sigL_max, unit);
    RooRealVar alphaL((theName+"_alphaL").c_str(), alphaLTitle.Data(), alphaL_start,
            alphaL_min, alphaL_max);
    RooRealVar sigR((theName+"_sigmaR").c_str(), sigRTitle.Data(), sigR_start, sigR_min, 
            sigR_max, unit);
    RooRealVar alphaR((theName+"_alphaR").c_str(), alphaRTitle.Data(), alphaR_start,
            alphaR_min, alphaR_max);

    RooCruijff theCruijff(pdfName, "", *mass, mu, sigL, sigR, alphaL, alphaR);  

    if ( m_rws->import( theCruijff, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeCruijff",
                *m_rws, theCruijff);
    }
}

void ModelBase::makeCruijff(const char* pdfName,
        RooRealVar& mu, RooRealVar& sig,
        RooRealVar& alphaL, RooRealVar& alphaR) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeCruijff",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeCruijff",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    RooCruijffSimple theCruijff(pdfName, "", *mass, mu, sig, alphaL, alphaR);
    if ( m_rws->import( theCruijff, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeCruijff",
                *m_rws, theCruijff);
    }
}

void ModelBase::makeCruijff(const char* pdfName,
        Float_t mu_start, Float_t mu_min,
        Float_t mu_max, Float_t sig_start,
        Float_t sig_min, Float_t sig_max,
        Float_t alphaL_start, Float_t alphaL_min,
        Float_t alphaL_max,
        Float_t alphaR_start, Float_t alphaR_min,
        Float_t alphaR_max, const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeCruijff",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeCruijff",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString muTitle="";
    TString sigTitle="";
    TString alphaLTitle="";
    TString alphaRTitle="";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle="#mu";
        sigTitle="#sigma";
        alphaLTitle="#alpha_{L}";
        alphaRTitle="#alpha_{R}";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sigTitle.Form("%s #sigma", m_1DFitVarPartName);
        alphaLTitle.Form("%s #alpha_{L}", m_1DFitVarPartName);
        alphaRTitle.Form("%s #alpha_{R}", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start, mu_min, mu_max, unit);
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sig_start, sig_min, 
            sig_max, unit);
    RooRealVar alphaL((theName+"_alphaL").c_str(), alphaLTitle.Data(), alphaL_start,
            alphaL_min, alphaL_max);
    RooRealVar alphaR((theName+"_alphaR").c_str(), alphaRTitle.Data(), alphaR_start,
            alphaR_min, alphaR_max);

    RooCruijffSimple theCruijff(pdfName, "", *mass, mu, sig, alphaL, alphaR);
    if ( m_rws->import(theCruijff, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeCruijff",
                *m_rws, theCruijff);
    }
}

//=============================================================================
// make and import the Apollonios pdf 
//=============================================================================

void ModelBase::makeApollonios(const char* pdfName,
        Float_t mu_start, Float_t mu_min,
        Float_t mu_max,   Float_t sig_start,
        Float_t sig_min,  Float_t sig_max,
        Float_t b_start,  Float_t b_min,
        Float_t b_max,    Float_t a_start,
        Float_t a_min,    Float_t a_max,
        Float_t n_start,  Float_t n_min,
        Float_t n_max,    const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeApollonios",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeApollonios",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString muTitle  = "";
    TString sigTitle = "";
    TString bTitle   = "";
    TString aTitle   = "";
    TString nTitle   = "";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        muTitle  = "#mu";
        sigTitle = "#sigma";
        bTitle   = "b";
        aTitle   = "a";
        nTitle   = "n";
    }
    else {
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        sigTitle.Form("%s #sigma", m_1DFitVarPartName);
        bTitle.Form("%s b", m_1DFitVarPartName);
        aTitle.Form("%s a", m_1DFitVarPartName);
        nTitle.Form("%s n", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start, mu_min, mu_max, unit);
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sig_start, sig_min, sig_max, unit);

    RooRealVar b((theName+"_b").c_str(), bTitle.Data(), b_start, b_min, b_max);
    RooRealVar a((theName+"_a").c_str(), aTitle.Data(), a_start, a_min, a_max);
    RooRealVar n((theName+"_n").c_str(), nTitle.Data(), n_start, n_min, n_max);

    RooApollonios theApollonios(pdfName, "", *mass, mu, sig, b, a, n);
    if ( m_rws->import(theApollonios, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeApollonios",
                *m_rws, theApollonios);
    }
}


//=============================================================================
// make and import the Amoroso pdf 
//=============================================================================

void ModelBase::makeAmoroso(const char* pdfName,
        Float_t a_start,     Float_t a_min,
        Float_t a_max,       Float_t theta_start,
        Float_t theta_min,   Float_t theta_max,
        Float_t alpha_start, Float_t alpha_min,
        Float_t alpha_max,   Float_t beta_start,
  	Float_t beta_min,    Float_t beta_max,
	const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeAmoroso",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeAmoroso",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString aTitle     = "";
    TString thetaTitle = "";
    TString alphaTitle = "";
    TString betaTitle  = "";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        aTitle     = "a";
        thetaTitle = "#theta";
        alphaTitle = "#alpha";
        betaTitle  = "#beta";
    }
    else {
        aTitle.Form("%s a", m_1DFitVarPartName);
        thetaTitle.Form("%s #theta", m_1DFitVarPartName);
        alphaTitle.Form("%s #alpha", m_1DFitVarPartName);
        betaTitle.Form("%s #beta", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar a((theName+"_a").c_str(), aTitle.Data(), a_start, a_min, a_max, unit);
    RooRealVar theta((theName+"_theta").c_str(), thetaTitle.Data(), theta_start, theta_min, theta_max, unit);
    RooRealVar alpha((theName+"_alpha").c_str(), alphaTitle.Data(), alpha_start, alpha_min, alpha_max, unit);
    RooRealVar beta((theName+"_beta").c_str(), betaTitle.Data(), beta_start, beta_min, beta_max, unit);

    RooAmorosoPdf theAmoroso(pdfName, "", *mass, a, theta, alpha, beta);
    if ( m_rws->import(theAmoroso, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeAmoroso",
                *m_rws, theAmoroso);
    }
}

//=============================================================================
// make and import the Hypatia pdf 
//=============================================================================

void ModelBase::makeHypatia(const char* pdfName,
        Float_t l_start,   Float_t l_min,
        Float_t l_max,     Float_t zeta_start,
        Float_t zeta_min,  Float_t zeta_max,
        Float_t fb_start,  Float_t sig_start,
  	Float_t sig_min,   Float_t sig_max,
	Float_t mu_start,  Float_t mu_min,
	Float_t mu_max,    Float_t a_start, 
	Float_t a_min,     Float_t a_max, 
        Float_t n_start,   Float_t n_min, 
	Float_t n_max,     const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeHypatia",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeHypatia",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString lTitle     = "";
    TString zetaTitle  = "";
    TString fbTitle    = "";
    TString sigTitle   = "";
    TString muTitle    = "";
    TString aTitle     = "";
    TString nTitle     = "";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        lTitle     = "#l";
        zetaTitle  = "#Z";
        fbTitle    = "f_{b}";
        sigTitle   = "#sigma";
        muTitle    = "#mu";
        aTitle     = "a";
        nTitle     = "n";
    }
    else {
        lTitle.Form("%s l", m_1DFitVarPartName);
        zetaTitle.Form("%s zeta", m_1DFitVarPartName);
        fbTitle.Form("%s fb", m_1DFitVarPartName);
        sigTitle.Form("%s #sigma", m_1DFitVarPartName);
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        aTitle.Form("%s a", m_1DFitVarPartName);
        nTitle.Form("%s n", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;


    RooRealVar l((theName+"_l").c_str(), lTitle.Data(), l_start, l_min, l_max);
    RooRealVar zeta((theName+"_zeta").c_str(), zetaTitle.Data(), zeta_start, zeta_min, zeta_max);
    RooRealVar fb((theName+"_fb").c_str(), fbTitle.Data(), fb_start);
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sig_start, sig_min, sig_max, unit);
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start, mu_min, mu_max, unit);
    RooRealVar a((theName+"_a").c_str(), aTitle.Data(), a_start, a_min, a_max);
    RooRealVar n((theName+"_n").c_str(), nTitle.Data(), n_start, n_min, n_max);

    RooHypatia theHypatia(pdfName, "", *mass, l, zeta, fb, sig, mu, a, n);
    if ( m_rws->import(theHypatia, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeHypatia",
                *m_rws, theHypatia);
    }
}

//=============================================================================
// make and import the Hypatia2 pdf 
//=============================================================================

void ModelBase::makeHypatia2(const char* pdfName,
        Float_t l_start,   Float_t l_min,
        Float_t l_max,     Float_t zeta_start,
        Float_t zeta_min,  Float_t zeta_max,
        Float_t fb_start,  Float_t sig_start,
  	Float_t sig_min,   Float_t sig_max,
	Float_t mu_start,  Float_t mu_min,
	Float_t mu_max,    Float_t a_start, 
	Float_t a_min,     Float_t a_max, 
        Float_t n_start,   Float_t n_min, 
	Float_t n_max,     Float_t a2_start,     
	Float_t a2_min,    Float_t a2_max, 
	Float_t n2_start,  Float_t n2_min, 
	Float_t n2_max,    const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeHypatia2",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeHypatia2",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString lTitle     = "";
    TString zetaTitle  = "";
    TString fbTitle    = "";
    TString sigTitle   = "";
    TString muTitle    = "";
    TString aTitle     = "";
    TString nTitle     = "";
    TString a2Title    = "";
    TString n2Title    = "";

    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        lTitle     = "#l";
        zetaTitle  = "#Z";
        fbTitle    = "f_{b}";
        sigTitle   = "#sigma";
        muTitle    = "#mu";
        aTitle     = "a";
        nTitle     = "n";
        a2Title    = "a2";
        n2Title    = "n2";
    }
    else {
        lTitle.Form("%s l", m_1DFitVarPartName);
        zetaTitle.Form("%s zeta", m_1DFitVarPartName);
        fbTitle.Form("%s fb", m_1DFitVarPartName);
        sigTitle.Form("%s #sigma", m_1DFitVarPartName);
        muTitle.Form("%s #mu", m_1DFitVarPartName);
        aTitle.Form("%s a", m_1DFitVarPartName);
        nTitle.Form("%s n", m_1DFitVarPartName);
        a2Title.Form("%s a2", m_1DFitVarPartName);
        n2Title.Form("%s n2", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;


    RooRealVar l((theName+"_l").c_str(), lTitle.Data(), l_start, l_min, l_max);
    RooRealVar zeta((theName+"_zeta").c_str(), zetaTitle.Data(), zeta_start, zeta_min, zeta_max);
    RooRealVar fb((theName+"_fb").c_str(), fbTitle.Data(), fb_start);
    RooRealVar sig((theName+"_sigma").c_str(), sigTitle.Data(), sig_start, sig_min, sig_max, unit);
    RooRealVar mu((theName+"_mu").c_str(), muTitle.Data(), mu_start, mu_min, mu_max, unit);
    RooRealVar a((theName+"_a").c_str(), aTitle.Data(), a_start, a_min, a_max);
    RooRealVar n((theName+"_n").c_str(), nTitle.Data(), n_start, n_min, n_max);
    RooRealVar a2((theName+"_a2").c_str(), a2Title.Data(), a2_start, a2_min, a2_max);
    RooRealVar n2((theName+"_n2").c_str(), n2Title.Data(), n2_start, n2_min, n2_max);

    RooHypatia2 theHypatia2(pdfName, "", *mass, l, zeta, fb, sig, mu, a, n, a2, n2);
    if ( m_rws->import(theHypatia2, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeHypatia2",
                *m_rws, theHypatia2);
    }
}

//=============================================================================
// make and import first order ChebyChev polynomial using RooRealVar for grad
//=============================================================================
void ModelBase::makeChebychev(const char* pdfName, RooRealVar& grad) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeChebychev",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeChebychev",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    RooChebychev dMassBkgModel(pdfName,"",*mass,RooArgList(grad));
    if ( m_rws->import( dMassBkgModel, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeChebychev",
                *m_rws, dMassBkgModel);
    }
}

//=============================================================================
// make and import first order ChebyChev polynomial using Float_ts for grad
//=============================================================================
void ModelBase::makeChebychev(const char* pdfName, Float_t grad_start, Float_t grad_min,
        Float_t grad_max,const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeChebychev",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeChebychev",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TString invMassUnit="";
    if (unit&&strcmp(unit,"")!=0) {
        invMassUnit.Form("(%s)^{-1}", unit);
    }
    TString gradTitle="";
    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        gradTitle="#nabla";
    }
    else {
        gradTitle.Form("%s #nabla", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;
    RooRealVar grad((theName+"_poly_c1").c_str(), gradTitle.Data(), grad_start, grad_min,
            grad_max, invMassUnit);
    RooChebychev dMassBkgModel(pdfName,"",*mass,RooArgList(grad));
    if ( m_rws->import( dMassBkgModel, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeChebychev",
                *m_rws, dMassBkgModel);
    }
}

//=============================================================================
// make and import second order ChebyChev polynomial using Float_ts
//=============================================================================
void ModelBase::makeChebychev2(const char* pdfName, Float_t c1_start, 
        Float_t c1_min, Float_t c1_max, Float_t c2_start, Float_t c2_min,
        Float_t c2_max, const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeChebychev",
                "No RooWorkspace object is defined.");
    }

    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeChebychev",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString invMassUnit="";
    if (unit&&strcmp(unit,"")!=0) {
        invMassUnit.Form("(%s)^{-1}", unit);
    }

    TString c1Title="";
    TString c2Title="";
    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        c1Title="c1";
        c1Title="c2";
    }
    else {
        c1Title.Form("%s c1", m_1DFitVarPartName);
        c2Title.Form("%s c2", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;

    RooRealVar c1((theName+"_poly_c1").c_str(), c1Title.Data(), c1_start, c1_min,
            c1_max, invMassUnit);
    RooRealVar c2((theName+"_poly_c2").c_str(), c2Title.Data(), c2_start, c2_min,
            c2_max, invMassUnit);

    RooChebychev dMassBkgModel(pdfName,"",*mass,RooArgList(c1, c2));

    if ( m_rws->import( dMassBkgModel, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeChebychev",
                *m_rws, dMassBkgModel);
    }
}

//=============================================================================
//Create and import exponential function to the workspace (using RooRealVars or
//Float_ts).
//=============================================================================
void ModelBase::makeExponential(const char* pdfName, RooRealVar& c1) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeExponential",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase:makeExponential",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    RooExponential MassBkgModel(pdfName,"",*mass,c1);
    if ( m_rws->import( MassBkgModel, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeExponential",
                *m_rws, MassBkgModel);
    }
}
//=============================================================================
void ModelBase::makeExponential(const char* pdfName, Float_t c1_start, Float_t c1_min,
        Float_t c1_max,const char* unit) 
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeExponential",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase:makeExponentialBkg",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    TString c1Title="";
    if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
        c1Title="#nabla";
    }
    else {
        c1Title.Form("%s #nabla", m_1DFitVarPartName);
    }

    std::string theName = (std::string)pdfName;
    RooRealVar c1((theName+"_slope").c_str(), c1Title.Data(), c1_start, c1_min,
            c1_max, unit);
    RooExponential dMassBkgModel(pdfName,"",*mass,c1);
    if ( m_rws->import( dMassBkgModel, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeExponential",
                *m_rws, dMassBkgModel);
    }
}

//=============================================================================
// make and import a RooKeysPdf suitable for the current B Mass var and
// dataset.
//=============================================================================
void ModelBase::makeKeysPdf(const char* name, const char* title)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeKeysPdf",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("ModelBase::makeKeysPdf",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    RooDataSet* data = (RooDataSet*)m_rws->data(m_dataSetName);
    if (!data) {
        throw WSRetrievalFailure("ModelBase::makeKeysPdf",
                *m_rws, m_dataSetName, "RooDataSet");
    }

    RooKeysPdf theKeys(name, title, *mass, *data);
    if ( m_rws->import( theKeys, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeKeysPdf",
                *m_rws, theKeys);
    }

}

//=============================================================================
// make a RooDecay pdf and import it
//=============================================================================
void ModelBase::makeRooDecay(const char* name,
        Float_t tau_start, Float_t tau_min, Float_t tau_max,
        const char* resModelName,
        const char* title)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeRooDecay",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* time = m_rws->var(m_1DFitVarName);
    if (!time) {
        throw WSRetrievalFailure("ModelBase::makeRooDecay",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    RooResolutionModel* resModel = dynamic_cast<RooResolutionModel*>(m_rws->pdf(resModelName));
    if (!resModel) {
        throw WSRetrievalFailure("ModelBase::makeRooDecay",
                *m_rws, resModelName, "RooAbsAnaConvPdf");
    }

    std::string theName = (std::string)name;

    RooRealVar tau((theName+"_tau").c_str(),"",tau_start,tau_min,tau_max,"");

    RooDecay theDecay(name, title, *time, tau, *resModel, RooDecay::SingleSided);

    if ( m_rws->import( theDecay, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeRooDecay",
                *m_rws, theDecay);
    }

}

//=============================================================================
// make a RooGaussResolutionModel and import it
//=============================================================================  
void ModelBase::makeGaussResModel(const char* name,
        Float_t mu_start, Float_t mu_min, Float_t mu_max,
        Float_t sigma_start, Float_t sigma_min, Float_t sigma_max,
        const char* title)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::makeGaussResModel",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* time = m_rws->var(m_1DFitVarName);
    if (!time) {
        throw WSRetrievalFailure("ModelBase::makeGaussResModel",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    std::string theName = (std::string)name;

    RooRealVar mu((theName+"_mu").c_str(),"",mu_start,mu_min,mu_max,"");
    RooRealVar sigma((theName+"_sigma").c_str(),"",sigma_start,sigma_min,sigma_max,"");

    RooGaussModel theGaussModel(name, title, *time, mu, sigma);

    if ( m_rws->import( theGaussModel, RooFit::RecycleConflictNodes(kTRUE) ) ) {
        throw WSImportFailure("ModelBase::makeGaussResModel",
                *m_rws, theGaussModel);
    }

}


//=============================================================================
// make a RooGaussResolutionModel with acceptance pdf included and import it
//=============================================================================  
/*void ModelBase::makeGaussResModelAcc(const char* name,
//resolution model parameters
Float_t mu_start, Float_t mu_min, Float_t mu_max,
Float_t sigma_start, Float_t sigma_min, Float_t sigma_max,
//acceptance parameters
Float_t accshape_val_start, Float_t accshape_val_min, Float_t accshape_val_max, 
Int_t nBinsAcceptance,
const char* title)
{
if (!m_rws) {
throw GeneralException("ModelBase::makeGaussResModelAcc",
"No RooWorkspace object is defined.");
}
RooRealVar* time = m_rws->var(m_1DFitVarName);
if (!time) {
throw WSRetrievalFailure("ModelBase::makeGaussResModelAcc",
 *m_rws, m_1DFitVarName, "RooRealVar");
 }


// set up pdf  
// acceptance
RooRealVar accshape("accshape", "accshape", accshape_val_start, accshape_val_min, accshape_val_max);
Acceptance acc("acc", "acc", *time, accshape);

// create binned approximation
RooUniformBinning accbinning(time->getMin(), time->getMax(),nBinsAcceptance, "accbinning");

time->setBinning(accbinning, "accbinning");

//make a binned version of acceptance
RooBinnedPdf accBinned("accBinned", "accBinned", *time, "accbinning", acc);

// tell RooBinnedPdf that we"re not really dealing with a PDF, so there is
// nothing to normalise, and we can force the normalisation integral to 1
accBinned.setForceUnitIntegral(kTRUE);

// resolution model B decay
std::string theName = (std::string)name;
RooRealVar mu((theName+"_mu").c_str(),"",mu_start,mu_min,mu_max,"");
RooRealVar sigma((theName+"_sigma").c_str(),"",sigma_start,sigma_min,sigma_max,"");
RooGaussModel theGaussModel(name, title, *time, mu, sigma);

// put the resolution model and the acceptance together
RooEffResModel accresmodel("accresmodel", "accresmodel",theGaussModel, accBinned);

if (m_rws->import(accresmodel)) {
throw WSImportFailure("ModelBase::makeGaussResModelAcc",
 *m_rws, accresmodel);
 }

 } */
//=============================================================================

//=============================================================================
// make a RooAddModel (triple gaussian) with acceptance pdf included and import it
//=============================================================================
/*
   void ModelBase::makeTripleGaussResModelAcc(const char* name,
//resolution model parameters
Float_t mu_start, Float_t mu_min, Float_t mu_max,
Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
Float_t sig1oSig0_start,Float_t sig1oSig0_min,Float_t sig1oSig0_max,
Float_t sig2oSig0_start,Float_t sig2oSig0_min,Float_t sig2oSig0_max,
Float_t coreFrac0_start,
Float_t coreFrac1_start,
//acceptance parameters
Float_t accshape_val_start, Float_t accshape_val_min, Float_t accshape_val_max, 
Int_t nBinsAcceptance,
const char* title)
{
if (!m_rws) {
throw GeneralException("ModelBase::makeTripleGaussResModelAcc",
"No RooWorkspace object is defined.");
}
RooRealVar* time = m_rws->var(m_1DFitVarName);
if (!time) {
throw WSRetrievalFailure("ModelBase::makeTripleGaussResModelAcc",
 *m_rws, m_1DFitVarName, "RooRealVar");
 }


// set up pdf  
// acceptance
RooRealVar accshape("accshape", "accshape", accshape_val_start, accshape_val_min, accshape_val_max);
Acceptance acc("acc", "acc", *time, accshape);

// create binned approximation
RooUniformBinning accbinning(time->getMin(), time->getMax(),nBinsAcceptance, "accbinning");

time->setBinning(accbinning, "accbinning");

//make a binned version of acceptance
RooBinnedPdf accBinned("accBinned", "accBinned", *time, "accbinning", acc);

// tell RooBinnedPdf that we"re not really dealing with a PDF, so there is
// nothing to normalise, and we can force the normalisation integral to 1
accBinned.setForceUnitIntegral(kTRUE);

// resolution model B decay
TString sig1oSig0Title="";
TString sig1Title="";
TString sig2Title="";
TString sig2oSig0Title="";
TString coreFrac0Title="";
TString coreFrac1Title="";
if (!m_1DFitVarPartName||strcmp(m_1DFitVarPartName,"")==0) {
sig1oSig0Title="#sigma_{tail-1}/#sigma_{core}";
sig2oSig0Title="#sigma_{tail-2}/#sigma_{core}";
sig1Title="#sigma_{tail-1}";
sig2Title="#sigma_{tail-2}";
coreFrac0Title="f_{core}";
coreFrac1Title="f_{wide}";
}
else {
sig1Title.Form("%s #sigma_{tail-1}", m_1DFitVarPartName);
sig2Title.Form("%s #sigma_{tail-2}", m_1DFitVarPartName);
sig1oSig0Title.Form("%s #sigma_{tail-1}/#sigma_{core}", m_1DFitVarPartName);
sig2oSig0Title.Form("%s #sigma_{tail-2}/#sigma_{core}", m_1DFitVarPartName);
coreFrac0Title.Form("%s f_{core}", m_1DFitVarPartName);
coreFrac1Title.Form("%s f_{wide}", m_1DFitVarPartName);
}

std::string theName = (std::string)name;
RooRealVar mu((theName+"_mu").c_str(),"",mu_start,mu_min,mu_max,"");
RooRealVar sig0((theName+"_sig0").c_str(),"",sig0_start,sig0_min,sig0_max,"");

RooGaussModel g0((theName+"_gauss0").c_str(), "", *time, mu, sig0);

RooRealVar sig1oSig0((theName+"_s1oS0").c_str(), sig1oSig0Title.Data(),
        sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
RooRealVar sig2oSig0((theName+"_s2oS0").c_str(), sig2oSig0Title.Data(),
        sig2oSig0_start, sig2oSig0_min, sig2oSig0_max);

RooFormulaVar sig1((theName+"_sigma1").c_str(), sig1Title.Data(), "@0*@1", 
        RooArgList(sig1oSig0,sig0));

RooFormulaVar sig2((theName+"_sigma2").c_str(), sig2Title.Data(), "@0*@1", 
        RooArgList(sig2oSig0,sig0));

RooGaussModel g1((theName+"_gauss1").c_str(), "", *time, mu, sig1);
RooGaussModel g2((theName+"_gauss2").c_str(), "", *time, mu, sig2);

RooRealVar coreFrac0((theName+"_coreFrac0").c_str(), coreFrac0Title.Data(),
        coreFrac0_start,0.0,1);
RooRealVar coreFrac1((theName+"_coreFrac1").c_str(), coreFrac1Title.Data(),
        coreFrac1_start,0.0,1);

RooAddModel theTripleGaussModel(name, title, 
        RooArgList(g0,g1,g2),
        RooArgList(coreFrac0,coreFrac1));

// put the resolution model and the acceptance together
RooEffResModel accresmodel("accresmodel", "accresmodel",theTripleGaussModel, accBinned);

if (m_rws->import(accresmodel)) {
    throw WSImportFailure("ModelBase::makeTripleGaussResModelAcc",
            *m_rws, accresmodel);
}

}
*/
//=============================================================================


//=============================================================================
//exports pdf with given name from workspace to file with given name.
//With optional new name inside the file.
//=============================================================================
void ModelBase::exportPDF(const char* pdfname,
        const char* filename,
        const char* wsname,
        const char* newname)

{
    if (!m_rws) {
        throw GeneralException("ModelBase::exportPDF",
                "No RooWorkspace object is defined.");
    }
    RooAbsPdf* thePdf = m_rws->pdf(pdfname);
    if (!thePdf) {
        throw WSRetrievalFailure("ModelBase::exportPDF",
                *m_rws, pdfname, "RooRealVar");
    }
    RooAbsPdf* clone = (RooAbsPdf*)thePdf->Clone();
    RooWorkspace* ws = new RooWorkspace(wsname);
    if (strcmp(newname,"")==0) ws->import(*clone);
    else ws->import(*clone, RooFit::RenameVariable(pdfname, newname) );
    ws->writeToFile(filename);
    delete clone;
    clone=0;
    delete ws;
    ws=0;  
}

//=============================================================================
// Gets a pdf from the workspace, user responsible for deletion
//=============================================================================
RooAbsPdf* ModelBase::getPDF(const char* pdfname)
{
    if (!m_rws) {
        throw GeneralException("ModelBase::getPDF",
                "No RooWorkspace object is defined.");
    }
    RooAbsPdf* thePdf = m_rws->pdf(pdfname);
    if (!thePdf) {
        throw WSRetrievalFailure("ModelBase::getPDF",
                *m_rws, pdfname, "RooRealVar");
    }
    RooAbsPdf* clone = (RooAbsPdf*)thePdf->Clone();
    return clone;

}


/*
void ModelBase::likesRatioPlot(TString fitName, TString compName, UInt_t toyScaleFactor, UInt_t numBins, Double_t startRange,
			      Double_t endRange, Double_t toyCompsLegTextSize,
			      Double_t toyCompsLegPosXStart, Double_t toyCompsLegPosYStart,
			      Double_t toyCompsLegPosXEnd, Double_t toyCompsLegPosYEnd,
			      Bool_t drawDataVsToyLeg, Bool_t drawToyCompsLeg, Bool_t doLog,
			      Bool_t useROOTDefaultYAxisRange, Double_t minYAxisValue)
{

    RooFitResult* result = dynamic_cast<RooFitResult*>( this->getFitResult( fitName ) );

    // check that there is a result
    if ( result == 0) {

        std::cerr << "ERROR in ModelBase::likesRatioPlot : No fit result to use." << std::endl;
        return;
    }

    // form likelihood ratio formula by iterating through components
    TString formulaNumStr = "@";
    TString formulaDenStr = "@";
    Int_t componentNum(0);
    Bool_t correctCompNameGiven(kFALSE);
    RooArgSet components = m_rws->allPdfs();
    RooArgList allPdfs = RooArgSet2List( &components );

    TIterator* iter = components.createIterator();
    RooAbsPdf* arg=0;
    while((arg=(RooAbsPdf*)iter->Next())) {

        // numerator formula
        if (TString(arg->GetName()) == compName)
        {
            formulaNumStr += componentNum;
            correctCompNameGiven = kTRUE;
        }
        // denominator formula
        if (componentNum == 0)
        {
            formulaDenStr += componentNum;
        }
        else
        {
            formulaDenStr += "+@";
            formulaDenStr += componentNum;
        }
        ++componentNum;
    }
    delete iter; iter=0;

    if (!correctCompNameGiven)
    {
        std::cerr << "ERROR in FitModel::doLLRPlot : Incorrect component given." << std::endl;
        return;
    }

    TString formulaStr = "(";
    formulaStr += formulaNumStr;
    formulaStr += ")/(";
    formulaStr += formulaDenStr;
    formulaStr += ")";
    RooFormulaVar likesRatioFunc( "likesRatio", "", formulaStr, allPdfs);

    // don't want to change data_, so make a copy
    RooDataSet* dataset = new RooDataSet( *getDataSet(), "datasetCopy" );

    // histo for data
    TH1F LLRHisto_Dat( "LLRHisto_Dat", "", numBins, startRange, endRange );

    // Loop over data events and calculate likelihood ratio for each event, write value to histo
    RooRealVar* likesRatio = (RooRealVar*)dataset->addColumn(likesRatioFunc);
    for (Int_t i = 0; i < getDataSet()->sumEntries(); i++)
    {
        RooArgSet* datarow;
        datarow = (RooArgSet*)dataset->get(i);
        RooRealVar* datarowRatio = (RooRealVar*)datarow->find("likesRatio");
        LLRHisto_Dat.Fill(datarowRatio->getVal());
    }
    LLRHisto_Dat.Sumw2();
    likesRatio = 0; // to get rid of unused variable warning

    // clean up
    delete dataset; dataset = 0;

    // now generate a high-stats toy sample and find likelihood ratio for each event (using same PDFs as used for data)

    // toy TH1F for each component
    std::vector<TH1F> componentToyHistos;
    std::vector<TString> componentNames;

    // RooArgList required when we create empty RooDataSet* and pass as prototype to the generate method
    RooArgList varList("varList");
    if (fitVarList_) varList.add(*fitVarList_);
    if (otherVarList_) varList.add(*otherVarList_);
    //if (this->doAsym()) varList.add(*qB_);

    // iterate through the components, generate toy, and histogram likelihood ratios
    Int_t numComps(0), numeratorComp(-99);
    iter = components->createIterator();
    RooAbsPdf* arg=0;
    while((arg=(RooAbsPdf*)iter->Next())) {
        if ( TString( arg->GetName() ) == compName) {
            numeratorComp = numComps;
        }

        componentNames.push_back( arg->GetName() );
        //(*iter)->addToyEvents( toyScaleFactor * ( static_cast<int>( (*iter)->eventsVal() ) ) );
        RooDataSet* toyComponentDataSet = new RooDataSet("toyComponentDataSet","toyComponentDataSet", varList);
        toyComponentDataSet = arg->generate( toyComponentDataSet, kFALSE );
        TString toyTH1FName = "LLRHisto_Toy_"; toyTH1FName += TString( arg->GetName() );
        TH1F LLRHisto_Toy_Comp( toyTH1FName, "", numBins, startRange, endRange );
        RooFormulaVar likesRatioFunc_toyComp( "likesRatio_toyComp", "", formulaStr, allPdfs );
        RooRealVar* likesRatio_toyComp = (RooRealVar*)toyComponentDataSet->addColumn(likesRatioFunc_toyComp);
        
        for ( UInt_t i = 0; i < (toyScaleFactor * ( static_cast<UInt_t>( (*iter)->eventsVal() ) ) ); ++i) {

            RooArgSet* toycomprow;
            toycomprow = (RooArgSet*)toyComponentDataSet->get(i);
            RooRealVar* toycomprowRatio = (RooRealVar*)toycomprow->find("likesRatio_toyComp");
            LLRHisto_Toy_Comp.Fill(toycomprowRatio->getVal());
        }
        componentToyHistos.push_back(LLRHisto_Toy_Comp);
        delete toyComponentDataSet; toyComponentDataSet = 0;
        likesRatio_toyComp = 0; // to get rid of unused variable warning
        numComps++;
    }

    delete iter; iter=0;
    // make plots
    FitterLikesRatioPlot likelihoodsPlot(compName);
    Double_t toyScaleFactorD = (Double_t)toyScaleFactor;
    likelihoodsPlot.dataVsToyPlot(LLRHisto_Dat,componentToyHistos,toyScaleFactorD,numBins,startRange,endRange,drawDataVsToyLeg,doLog,useROOTDefaultYAxisRange,minYAxisValue);
    likelihoodsPlot.toyCompsPlot(componentToyHistos,componentNames,numComps,numeratorComp,toyScaleFactorD,numBins,startRange,endRange,toyCompsLegTextSize,toyCompsLegPosXStart,
            toyCompsLegPosYStart,toyCompsLegPosXEnd,toyCompsLegPosYEnd,drawToyCompsLeg,doLog,useROOTDefaultYAxisRange,minYAxisValue);

}
*/




//=============================================================================
// Gets the dataset out of the rooworkspace with the given name
// Raises an exception if not found.
// Caller is responsible for deletion.
//=============================================================================
/*RooDataSet* ModelBase::GetDataSet(const char* name)
  {
  if (!m_rws) {
  throw GeneralException("ModelBase::GetDataSet",
  "No RooWorkspace object is defined.");
  }
  RooAbsData* theData = m_rws->data(name);
  if (!theData) {
  throw WSRetrievalFailure("ModelBase::GetDataSet",
 *m_rws, name, "RooAbsData");
 }
 RooDataSet* cloneOfData = (RooDataSet*)theData->Clone();
 cloneOfData->SetName(name);
 return cloneOfData;
 }*/

//=============================================================================
//void ModelBase::SetBMassBkgModelName(const char* name) {m_BMassBkgModelName=name;}
////=============================================================================
//const char* ModelBase::GetBMassBkgModelName() {return m_BMassBkgModelName;}
//=============================================================================


//=============================================================================
// Destructor
//=============================================================================
ModelBase::~ModelBase() {}
//=============================================================================
