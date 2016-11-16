// $Id: $
// Include files
// std libs
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <cassert>
#include <algorithm>    // std::find
#include <iomanip>      // std::setprecision
#include <boost/algorithm/string.hpp>

// ROOT
#include "TCanvas.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraph.h"
#include "TKey.h"
#include "TLine.h"
#include "TAxis.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TObjArray.h"
#include "TSystem.h"
#include "TString.h"
#include "TEventList.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TTreeFormula.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TEntryList.h"

// RooFit
#include "RooWorkspace.h"
#include "RooAbsCollection.h"
#include "RooAbsData.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooAbsBinning.h"
#include "RooConstVar.h"
#include "RooFFTConvPdf.h"
#include "RooFormulaVar.h"
#include "RooMinuit.h"
#include "RooRandom.h"
#include "RooGaussian.h"
#include "RooUnblindPrecision.h"
#include "RooUnblindUniform.h"
#include "RooCmdArg.h"

// RooStats
#include "RooStats/SPlot.h"

// TMVA
#include "TMVA/Timer.h"

// local
#include "V0hhFitter/Fitter.h"
#include "V0hhFitter/Exceptions.h"
#include "V0hhFitter/ClientTree.h"
#include "V0hhFitter/string_tools.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Fitter
//
// 2014-01-08 : Matthew M Reid
//-----------------------------------------------------------------------------

using namespace V0hhFit;
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Fitter::Fitter(  ) 
    : TNamed(), m_nCores(2), m_rws(0), m_dataSetName("data"), m_modelName("model"),
    m_sWeightVarSetName("Weights"), m_plotParamsSetName("PlotParams"),
    m_globalPlotBins(100), m_plotBinMap(), m_paramBoxX1(0.60), m_paramBoxX2(0.95),
    m_paramBoxY1(0.70), m_paramBoxY2(0.93), m_paramBoxTextSize(0.028),
    m_paramBoxTextAlign(12) /* left adjusted, vertically centered */,
    m_paramBoxName("paramBox"), m_modelLineColor(kBlue),
    m_modelLineStyle(1), m_modelLineWidth(3), m_dataSetLineColor(kBlack),
    m_dataSetLineStyle(1), m_dataSetLineWidth(3), m_dataSetMarkerColor(kBlack),
    m_dataSetMarkerStyle(kFullSquare), m_dataSetMarkerSize(1),
    m_dataSetFillColor(kBlack), m_dataSetFillStyle(3001), 
    m_dataSetDrawOption("P"), m_pdfComponents(), m_pdfLineColorMap(),
    m_pdfLineStyleMap(), m_pdfLineWidthMap(), m_plotSubComponents(false),
    m_1DFitVarPartName(""), m_1DFitVarName("mass"), m_spectSetName("Spectators"),
    m_catSetName("Categories"), m_BlindString("Blinded"), m_ConstraintSetName("Constraints"),
    m_stringHelper(), 
    m_file(0), m_hasOwnership(kFALSE), m_lhcbStyle()
{
}

//-----------------------------------------------------------------------------
// overloaded constructor
//-----------------------------------------------------------------------------
Fitter::Fitter( const char* name, const char* title)
    : TNamed(name, title), m_nCores(2), m_rws(0), m_dataSetName("data"), m_modelName("model"),
    m_sWeightVarSetName("Weights"), m_plotParamsSetName("PlotParams"),
    m_globalPlotBins(100), m_plotBinMap(), m_paramBoxX1(0.60), m_paramBoxX2(0.95),
    m_paramBoxY1(0.70), m_paramBoxY2(0.93), m_paramBoxTextSize(0.028),
    m_paramBoxTextAlign(12) /* left adjusted, vertically centered */,
    m_paramBoxName("paramBox"), m_modelLineColor(kBlue),
    m_modelLineStyle(1), m_modelLineWidth(3), m_dataSetLineColor(kBlack),
    m_dataSetLineStyle(1), m_dataSetLineWidth(3), m_dataSetMarkerColor(kBlack),
    m_dataSetMarkerStyle(kFullSquare), m_dataSetMarkerSize(1),
    m_dataSetFillColor(kBlack), m_dataSetFillStyle(3001), 
    m_dataSetDrawOption("P"), m_pdfComponents(), m_pdfLineColorMap(),
    m_pdfLineStyleMap(), m_pdfLineWidthMap(), m_plotSubComponents(false),
    m_1DFitVarPartName(""), m_1DFitVarName("mass"), m_spectSetName("Spectators"),
    m_catSetName("Categories"), m_BlindString("Blinded"), m_ConstraintSetName("Constraints"),
    m_stringHelper(),
    m_file(0), m_hasOwnership(kFALSE), m_lhcbStyle()
{
}

//=============================================================================
// Takes the info from a TFile containing one and only one RooWorkspace.
//=============================================================================

void Fitter::addFileInfo( TFile *f )
{
    //Test the file pointer.
    if (f == NULL)
        throw GeneralException("Fitter::addFileInfo",
                "File not found!");
    RooWorkspace *w = (RooWorkspace*) Fitter::findItem(f,RooWorkspace::Class())->ReadObj();
    this->setWS(w,true);
    //Find the model name.
    m_modelName = Fitter::findModel(m_rws,m_modelName).c_str();
    //Have to perform several checks.
    //1DFitVarName
    if (m_rws->var(m_1DFitVarName) == NULL)
        throw WSRetrievalFailure("Fitter::addFileInfo",
                *m_rws, m_1DFitVarName, "1D fit variable");	
    f->Close();
}

//=============================================================================
// Add Spectator variables to the dataset
//=============================================================================
void Fitter::addSpectator(const char *name, Double_t xmin,
	Double_t xmax, const char *brName,
        const char *unit, const char *title,
        const char* setName)
{
    if (!m_rws) {
        throw GeneralException("Fitter::addSpectator",
                "No RooWorkspace object is defined.");
    }
    RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
            (!unit)?"":unit);
    if ( m_rws->import( var ) ) {
        throw WSImportFailure("Fitter::addSpectator", *m_rws, var);
    }
    if ( brName && strcmp( brName, "" ) != 0 ) {
        m_varNameToBranchName[name]=brName;
    }
    if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
        throw GeneralException("Fitter::addSpectator",
                "No spectator set name specified.");
    }
    if (m_rws->extendSet(m_spectSetName, name)) {
        throw WSImportFailure("Fitter::addSpectator", *m_rws, 
                m_spectSetName, name);
    }
    if (setName&&strcmp(setName,"")!=0) {
        if (m_rws->extendSet(setName, name)) {
            throw WSImportFailure("Fitter::addSpectator", *m_rws, 
                    setName, name);
        }
    }
}


//=============================================================================
// Reset the initial parameter values before a given fitName was performed.
//============================================================================
void Fitter::resetInitParameters( const char* fitName )
{
    if (!m_rws) {
        throw GeneralException("Fitter::resetInitParameters",
                "No RooWorkspace object is defined.");
    }

    RooFitResult* result = this->getFitResult( fitName );

    TString nameStr = TString::Format("%s_init_params", fitName);

    // Store the initial values from the fit to data and save a snapshot
    const RooArgList initParams = result->floatParsInit();
    RooArgSet initialParams( initParams );

    // save the snapshot
    m_rws->saveSnapshot( nameStr, initialParams, kTRUE );

    if ( !m_rws->loadSnapshot( nameStr ) )
    {
        throw WSRetrievalFailure("Fitter::resetInitParameters",
                *m_rws, nameStr.Data(), "initial parameters snapshot");
    }
}


//=============================================================================
void Fitter::addSpectator(const char *name, Double_t xmin,
	Double_t xmax, 
        Fitter::DoubleFun fun,
        const char *brName, const char *unit,
        const char *title, const char* setName) 
{
    if (!m_rws) {
        throw GeneralException("Fitter::addSpectator",
                "No RooWorkspace object is defined.");
    }
    RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
            (!unit)?"":unit);
    if (m_rws->import(var)) {
        throw WSImportFailure("Fitter::addSpectator", *m_rws, var);
    }
    if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
        throw GeneralException("Fitter::addSpectator",
                "No spectator set name specified.");
    }
    if (m_rws->extendSet(m_spectSetName, name)) {
        throw WSImportFailure("Fitter::addSpectator", *m_rws, 
                m_spectSetName, name);
    }
    if (brName&&strcmp(brName,"")!=0) {
        m_varNameToBranchName[name]=brName;
    }
    m_varNameToFunction[name]=fun;
    if (setName&&strcmp(setName,"")!=0) {
        if (m_rws->extendSet(setName, name)) {
            throw WSImportFailure("Fitter::addSpectator", *m_rws, 
                    setName, name);
        }
    }
}


//=============================================================================
void Fitter::addSpectator(const char *name, Double_t xmin,
	Double_t xmax, 
        TFormula& fun,
        const char *brName, const char *unit,
        const char *title, const char* setName) 
{
    if (!m_rws) {
        throw GeneralException("Fitter::addSpectator",
                "No RooWorkspace object is defined.");
    }
    RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
            (!unit)?"":unit);
    if (m_rws->import(var)) {
        throw WSImportFailure("Fitter::addSpectator", *m_rws, var);
    }
    if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
        throw GeneralException("Fitter::addSpectator",
                "No spectator set name specified.");
    }
    if (fun.GetNdim()!=1) {
        std::stringstream msg;
        msg << "Expected one dimension for TFormula " << fun.GetName()
            << ", got " << fun.GetNdim();
        throw GeneralException("Fitter::addSpectator",msg.str());
    }
    if (fun.GetNpar()!=0) {
        std::stringstream msg;
        msg << "Expected zero parameters for TFormula " << fun.GetName()
            << ", got " << fun.GetNpar();
        throw GeneralException("Fitter::addSpectator",msg.str());
    }
    if (m_rws->extendSet(m_spectSetName, name)) {
        throw WSImportFailure("Fitter::addSpectator", *m_rws, 
                m_spectSetName, name);
    }
    if (brName&&strcmp(brName,"")!=0) {
        m_varNameToBranchName[name]=brName;
    }
    m_varNameToFormula[name]=fun;
    if (setName&&strcmp(setName,"")!=0) {
        if (m_rws->extendSet(setName, name)) {
            throw WSImportFailure("Fitter::addSpectator", *m_rws, 
                    setName, name);
        }
    }
}

//=============================================================================
//Simply add a var to the workspace. For example, when you want some fit 
//parameters to depend on an external parameter.
//=============================================================================
void Fitter::addParameter(const char* name, Double_t min, Double_t max,const char* title, const char* unit)
{
    if (!m_rws) {
        throw GeneralException("Fitter::addParameter",
                "No RooWorkspace object is defined.");
    }

    RooRealVar param(name,(!title)?"":title,min,max,unit);

    if (m_rws->import(param)) {
        throw WSImportFailure("Fitter::addParameter", *m_rws, param);
    }

}

//=============================================================================
//Simply add a var to the workspace. For example, when you want some fit 
//parameters to depend on an external parameter.
//=============================================================================
void Fitter::addParameter(const char* name, Double_t val, Double_t min, Double_t max,const char* title, const char* unit)
{
    if (!m_rws) {
        throw GeneralException("Fitter::addParameter",
                "No RooWorkspace object is defined.");
    }

    RooRealVar param(name,(!title)?"":title,val,min,max,unit);

    if (m_rws->import(param)) {
        throw WSImportFailure("Fitter::addParameter", *m_rws, param);
    }

}

//=============================================================================
void Fitter::setConstraintString(const char* constraintstring){m_ConstraintSetName = constraintstring;}
//=============================================================================
const char* Fitter::getConstraintString() const {return m_ConstraintSetName;} 
//=============================================================================
void Fitter::setBlindString(const char* blindstring){m_BlindString = blindstring;}
//=============================================================================
const char* Fitter::getBlindString(){return m_BlindString;} 
//=============================================================================
void Fitter::setSpectatorSetName(const char* name) {m_spectSetName=name;}
//=============================================================================
const char* Fitter::getSpectatorSetName() {return m_spectSetName;}

//-----------------------------------------------------------------------------
// create a new RooWorkspace object
//-----------------------------------------------------------------------------
void Fitter::createWS( const char* name, const char* title)
{
    if (m_rws&&m_hasOwnership)
    {
        std::cout << "WARNING: Deleting existing RooWorkspace "
            << m_rws->GetName()
            << ". If a file is attached, it will be closed"
            << std::endl;
        delete m_rws; m_rws = 0;
        if (m_file) {
            delete m_file; m_file = 0;
        }
    }
    m_rws = new RooWorkspace(name, title);
    m_hasOwnership=kTRUE;
}

//-----------------------------------------------------------------------------
// add a prexisting RooWorkspace object
//-----------------------------------------------------------------------------
void Fitter::setWS(RooWorkspace* ws, Bool_t takeOwnership)
{
    if (m_rws&&m_hasOwnership)
    {
        std::cout << "WARNING: Deleting existing RooWorkspace "
            << m_rws->GetName()
            << ". If a file is attached, it will be closed"
            << std::endl;
        delete m_rws;
        if (m_file)
            delete m_file;
    }
    m_rws = ws;
    m_hasOwnership = takeOwnership;

}


//-----------------------------------------------------------------------------
// wiggle the parameter values by their errors
//-----------------------------------------------------------------------------
void Fitter::wiggleAllParams( Int_t seed, RandomMethod randomiser, const char* fitName, const char* varsName )
{
    // check that the parameters exist
    if (!m_rws)
    {
        throw GeneralException( "Fitter::wiggleAllParams",
                "Empty RooWorkspace." );
    }

    // get the model PDF
    RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );
    if (!model)
    {
        throw WSRetrievalFailure( "Fitter::wiggleAllParams"
                , *m_rws, m_modelName, "RooAbsPdf" );
    }

    // get the dataset
    RooDataSet *rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds)
    {
        throw WSRetrievalFailure("Fitter::wiggleAllParams",
                *m_rws, m_dataSetName, "RooDataSet");
    }


    wiggleAllParams( model, rds, randomiser, fitName, seed, varsName );

}


//=============================================================================
// generates a RooDataSet containing numEvents, using the pdf stored 
//=============================================================================
RooDataSet* Fitter::generate( UInt_t numEvents, Bool_t extended ) const
{
    // check that the ws exists
    if (!m_rws)
    {
        throw GeneralException("Fitter::generate",
                "No RooWorkspace object is defined");
    }

    // get the dataset
    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds)
    {
        throw WSRetrievalFailure("Fitter::generate"
                ,*m_rws, m_dataSetName, "RooDataSet");
    }

    // get the model PDF
    //std::cout << m_modelName << "\t" << GetModelName() << std::endl;
    RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );
    if (!model)
    {
        throw WSRetrievalFailure("Fitter::generate"
                ,*m_rws, m_modelName, "RooAbsPdf");
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds );

    if (!observables) 
    {
        std::stringstream msg;
        msg << "Failed to get the list of observables "
            << "for model PDF " << model->GetName()
            << " from dataset " << rds->GetName();
        throw GeneralException("Fitter::generate", msg.str() );
    }

    // perform the generation
    RooDataSet* data  = dynamic_cast<RooDataSet*>( model->generate( *observables, numEvents, RooFit::Extended( extended ) ) );
    delete observables; observables=0;
    return data;
}

//-----------------------------------------------------------------------------
// Set the parameter range, this is useful when specifying a default fitting range for
// example, or used for the NLL scan range.
// N.B. raises exception if varName does not exist in the workspace and if it is not a 
// e.
//-----------------------------------------------------------------------------
void Fitter::setParameterRange( const char* varName, const char* rangeName,
	double min, double max) 
{

    // check that the ws exists
    if (!m_rws)
    {
        throw GeneralException("Fitter::setRooRVRange",
                "No RooWorkspace object is defined");
    }

    // check if parameter exists...
    RooRealVar* var = dynamic_cast<RooRealVar*>( m_rws->var( varName ) );
    if (!var) {
        throw WSRetrievalFailure("Fitter::setParameterRange",
                *m_rws, varName, "RooRealVar");
    }

    var->setRange( rangeName, min, max );

}


//-----------------------------------------------------------------------------
// Set the parameter range, this is useful when specifying a default fitting range for
// example, or used for the NLL scan range.
// N.B. raises exception if varName does not exist in the workspace and if it is not a 
// e.
//-----------------------------------------------------------------------------
void Fitter::setParameterError( const char* varName, double error)
{
	
    // check that the ws exists
    if (!m_rws)
		throw GeneralException("Fitter::setRooRVRange",
							   "No RooWorkspace object is defined");
    // check if parameter exists...
    RooRealVar* var = dynamic_cast<RooRealVar*>( m_rws->var( varName ) );
    if (!var)
        throw WSRetrievalFailure("Fitter::setParameterRange",
								 *m_rws, varName, "RooRealVar");
	
    var->setError( error );	
}

//-----------------------------------------------------------------------------
// Get the parameter value, useful for grabbing final formula values
// orjust getting the final value of one fitted parameter.
//-----------------------------------------------------------------------------
double Fitter::getParameterValue( const char* name ) 
{

    // check that the ws exists
    if (!m_rws)
    {
        throw GeneralException("Fitter::getParameterValue",
                "No RooWorkspace object is defined");
    }

    // check if parameter exists...
    RooAbsReal* var = dynamic_cast<RooAbsReal*>( m_rws->var( name ) );
    if (!var) {
        throw WSRetrievalFailure("Fitter::getParameterValue",
                *m_rws, name, "RooAbsReal");
    }
    return var->getVal();

}

//-----------------------------------------------------------------------------
// Randomise the parameters in the fit based on the correlation matrix.
//-----------------------------------------------------------------------------
void Fitter::correlation_randomiser( const RooArgSet* params, int seed, const char* varsName, const char* fitName ) 
{

    // set random generator
    if( seed < 0 ) { // if seed is -ve then set it to use a time seed.
        seed = std::time(0);
    } 

    RooRandom::randomGenerator()->SetSeed( seed );

    RooFitResult* res = dynamic_cast<RooFitResult*>( this->getFitResult( fitName ) );

    // Create the p.d.f that represents the fit result as a multi-variate probability 
    // density function on the floating fit parameters, including correlations.
    RooAbsPdf* pdf = dynamic_cast<RooAbsPdf*>( res->createHessePdf( *params ) );

    // Create one new dataset with new values and parse it to the RooArgSet
    const RooArgSet* randomisedVars = pdf->generate( *params, 1 )->get();
    assert(randomisedVars);

    // save the snapshot
    m_rws->saveSnapshot( varsName, *randomisedVars, kTRUE );

    if ( !m_rws->loadSnapshot( varsName ) )
    {
        throw WSRetrievalFailure("Fitter::wiggleParams",
                *m_rws, varsName, "wiggle snapshot");
    }

    delete pdf; pdf = 0;

}


//-----------------------------------------------------------------------------
// Create a nll scan using user defined range and granularity and store the 
// output graph to a TFile. Lets say we wanted to scan as a function of BF. Instead
// of passing in the yield here we could 
//
// fitter.addParameter("bf_name", )
// fitter.addConstraint("bf_name", "@0*@1", "yield_name");
//-----------------------------------------------------------------------------
double Fitter::nllScan(const char* poiName, int steps, 
	  double min, double max,  
	  const char* fitName,
	  const char* outputFileName, 
	  bool update, double edmTol ) 
{

    // To be used immediately after the main fit to data.
    // check if FitResult exists
    std::string safe_fitName( fitName );
    const RooFitResult* fitResult = this->getFitResult( safe_fitName.c_str() );

    // check that the parameter name actually exists
    RooRealVar *poi = this->getVar( poiName ) ;

    std::string mode = (!update) ? "RECREATE" : "UPDATE" ;
    TFile* outputFile = new TFile( outputFileName, mode.c_str() );
    outputFile->cd();

    // Store the initial values from the fit to data and save a snapshot
    //const RooArgList initParams = fitResult->floatParsInit();
    //RooArgSet initialParams( initParams );
    //std::string initParsName = "nll_initial_params_" + safe_fitName;
    //m_rws->saveSnapshot( initParsName.c_str(), initialParams, kTRUE );

    double minnll = fitResult->minNll(), thisnll = minnll, refnll = thisnll, maxnll = thisnll;
    double rbest = poi->getVal(), rval = rbest;

    TGraph points( steps ); 
    points.SetName( "nll_scan_" + TString( poi->GetName() ) );

    double dx = ( max - min )/static_cast<double>( steps );

    RooFitResult * res=0;
    TMVA::Timer timer( steps, "Fitter::nllScan" );
    for(Int_t i(0); i < steps; ++i ) {

        if( i == 0 ) {
            resetInitParameters( safe_fitName.c_str() );
        }

        //        this->wiggleAllParams( params, i );
        rval = max - i * dx ;
        poi->setConstant(false);
        poi->setVal( rval );
        poi->setConstant(true);

        this->performFit( "nll_fitResults" );
        res = this->getFitResult( "nll_fitResults" );
        if(!res) {
            continue;
        }

        bool success = ( res->covQual()==3 && res->edm()<edmTol && res->status()==0 );
        if(!success) std::cout << "THE FIT DID NOT CONVERGE FOR PARAMETER " << poi->GetName() << " set to "  << rval << std::endl;

        thisnll = res->minNll();
        points.SetPoint(i, rval, thisnll - refnll);
        if (thisnll < minnll) { minnll = thisnll; rbest = rval; }
        if (rval <= rbest && thisnll > maxnll) { maxnll = thisnll;  } 

        timer.DrawProgressBar( i );
    }

    points.Sort();
    double ret = (maxnll - minnll);

    outputFile->cd();
    outputFile->WriteTObject( &points );
    outputFile->Close();
    delete outputFile; outputFile=0;

    // return to original state.
    loadSnapshot( safe_fitName.c_str() );

    return ret;
}


//-----------------------------------------------------------------------------
// Randomise the parameters in the fit based on the correlation matrix.
// Use case: fixed parameter in the fit which are floated by their MC info
//-----------------------------------------------------------------------------
void Fitter::correlation_randomiser_Fixed( const RooArgSet* params, int seed, const char* varsName, RooFitResult* MCResult) 
{

    // set random generator
    if( seed < 0 ) { // if seed is -ve then set it to use a time seed.
        seed = std::time(0);
    } 

    RooRandom::randomGenerator()->SetSeed( seed );

    // Create the p.d.f that represents the fit result as a multi-variate probability 
    // densisty function on the fixed parameters (in data), including correlations.
    RooAbsPdf* pdf = dynamic_cast<RooAbsPdf*>( MCResult->createHessePdf( *params ) );

    // Create one new dataset with new values and parse it to the RooArgSet
    const RooArgSet* randomisedVars = pdf->generate( *params, 1 )->get();
    assert(randomisedVars);

    // save the snapshot
    m_rws->saveSnapshot( varsName, *randomisedVars, kTRUE );

    if ( !m_rws->loadSnapshot( varsName ) )
    {
        throw WSRetrievalFailure("Fitter::wiggleParamsFixed",
                *m_rws, varsName, "wiggle snapshot");
    }

    delete pdf; pdf = 0;

}

//-----------------------------------------------------------------------------
// Randomise the parameters in the fit based on the correlation matrix.
// Use case: fixed parameter in the fit which are floated by their MC info
//-----------------------------------------------------------------------------
void Fitter::correlation_randomiser_Fixed( std::multimap<RooAbsReal*,RooAbsReal*> params, int seed, const char* varsName, RooFitResult* MCResult) 
{

    // set random generator
    if( seed < 0 ) { // if seed is -ve then set it to use a time seed.
        seed = std::time(0);
    } 

    RooRandom::randomGenerator()->SetSeed( seed );
    TRandom3 random( seed );	
    //Create the RooArgSet which will be randomized.
    RooArgSet* MCparams = new RooArgSet("MCparams");
    for (std::multimap<RooAbsReal*,RooAbsReal*>::iterator it = params.begin() ; it != params.end() ; ++it)
        //		if (std::string(it->second->GetName()).find("threshold") == std::string::npos)
        MCparams->add(*(it->second),true);

    // Create the p.d.f that represents the fit result as a multi-variate probability 
    // density function on the fixed parameters (in data), including correlations.

    RooAbsPdf* pdf = dynamic_cast<RooAbsPdf*>( MCResult->createHessePdf( *MCparams ) );

    // Create one new dataset with new values and parse it to the RooArgSet
    const RooArgSet* randomisedVars = pdf->generate( *MCparams, 1 )->get();	
    assert(randomisedVars);
    //	randomisedVars->Print("v");
    // save the snapshot
    RooArgSet* newVars = new RooArgSet("newVars");
    for (std::multimap<RooAbsReal*,RooAbsReal*>::iterator it = params.begin() ; it != params.end() ; ++it)
    {
        //			if (std::string(it->second->GetName()).find("threshold") != std::string::npos)
        //				continue;
        ((RooRealVar*) it->first)->setVal(
            ((RooRealVar*) &((*randomisedVars)[it->second->GetName()]) )->getVal()
            //											  this->getWS()->var(it->first->GetName())->getMin()
            );
        newVars->add(*it->first,true);
    }
    //	for (std::multimap<RooAbsReal*,RooAbsReal*>::iterator it = params.begin() ; it != params.end() ; ++it)
    //		{
    //			if (std::string(it->second->GetName()).find("threshold") == std::string::npos)
    //				continue;
    //			double val = ((RooRealVar*) it->first)->getVal();
    //			double factor = (random.Gaus( 0.0, 1.0 ) > 0)? 1.:-1.;
    //			((RooRealVar*) it->first)->setVal(val +factor*TMath::Abs( random.Gaus( 0.0, 2.0 ) ));
    //			newVars->add(*it->first,true);
    //		}
    newVars->Print("v");
    m_rws->saveSnapshot( varsName, *newVars, kTRUE );

    if ( !m_rws->loadSnapshot( varsName ) )
    {
        throw WSRetrievalFailure("Fitter::wiggleParamsFixed",
                *m_rws, varsName, "wiggle snapshot");
    }	
    delete pdf; pdf = 0;

}

//-----------------------------------------------------------------------------
// Randomise the parameters specified based on a gaussian distribution
// about its central value and error. Also works for asymmetric errors.
//-----------------------------------------------------------------------------
void Fitter::gaussian_randomiser( const RooArgSet* params, int seed, const char* varsName ) 
{
    RooArgSet randomisedVars;
    TRandom3 random( seed );
    RooFIter paramIter = params->fwdIterator();
    RooRealVar* var(0);
    double val(0.), newval(0.), posneg(0.), error(0.), genVal(0.);
    bool genVal_flag(false);
    while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
        std::string name( var->GetName() );
        std::string classname( var->ClassName() );
        if (classname!="RooRealVar") {
            continue; 
        }

        val = var->getVal();
        newval = val;
        genVal_flag = false;

        if ( var->hasAsymError() ) {
            posneg = random.Gaus( 0.0, 1.0 );
            if ( posneg > 0 ) {
                error  = TMath::Abs( var->getAsymErrorHi() );
                newval = val + TMath::Abs( random.Gaus( 0.0, error) );
            } else {
                error  = TMath::Abs( var->getAsymErrorLo() );
                newval = val - TMath::Abs( random.Gaus( 0.0, error ) );
            }
        } else if ( var->hasError() ) {
            error  = var->getError();
            while (!genVal_flag){
                genVal = random.Gaus( val, error );
                if( (genVal > var->getMin()) && (genVal < var->getMax()) ) {
                    genVal_flag = true;
                    newval = genVal;
                } 
            }
        }
        else
            std::cout << "WARNING: You're trying to randomize something which does not have an error (hint: It won't work)" << std::endl;

        setParameterValue( name.c_str(), newval );
        randomisedVars.add( *var );
    }

    // save the snapshot
    m_rws->saveSnapshot( varsName, randomisedVars, kTRUE );

    if ( !m_rws->loadSnapshot( varsName ) )
    {
        throw WSRetrievalFailure("Fitter::gaussian_randomiser",
                *m_rws, varsName, "wiggle snapshot");
    }
}


//-----------------------------------------------------------------------------
// Randomise the parameters specified based on a gaussian distribution
// about its central value and error. Also works for asymmetric errors.
//-----------------------------------------------------------------------------
void Fitter::gaussian_randomiser_Fixed( std::multimap<RooAbsReal*,RooAbsReal*> args, int seed, const char* varsName ) 
{
    RooArgSet randomisedVars;
    TRandom3 random( seed );
    RooRealVar* var   = NULL;
    RooRealVar* varMC = NULL;
    double val(0.), newval(0.), posneg(0.), error(0.), genVal(0.);
    bool genVal_flag(false);
    for (std::multimap<RooAbsReal*,RooAbsReal*>::iterator it = args.begin() ; it != args.end() ; ++it)
    {
        var   = (RooRealVar*) it->first;
        varMC = (RooRealVar*) it->second;
        std::string name( var->GetName() );
        std::string classname( var->ClassName() );
        if (classname!="RooRealVar") {
            continue; 
        }
        classname = varMC->ClassName() ;
        if (classname!="RooRealVar") {
            continue; 
        }			
        val = var->getVal();
        newval = val;
        genVal_flag = false;

        if ( varMC->hasAsymError() ) {
            posneg = random.Gaus( 0.0, 1.0 );
            if ( posneg > 0 ) {
                error  = TMath::Abs( varMC->getAsymErrorHi() );
                newval = val + TMath::Abs( random.Gaus( 0.0, error) );
            } else {
                error  = TMath::Abs( varMC->getAsymErrorLo() );
                newval = val - TMath::Abs( random.Gaus( 0.0, error ) );
            }
        } else if ( varMC->hasError() ) {
            error  = varMC->getError();
            while (!genVal_flag){
                genVal = random.Gaus( val, error );
                if( (genVal > varMC->getMin()) && (genVal < varMC->getMax()) ) {
                    genVal_flag = true;
                    newval = genVal;
                } 
            }
        }
        else
            std::cout << "WARNING: You're trying to randomize something which does not have an error (hint: It won't work)" << std::endl;

        setParameterValue( name.c_str(), newval, true );
        randomisedVars.add( *var );
    }

    // save the snapshot
    m_rws->saveSnapshot( varsName, randomisedVars, kTRUE );

    if ( !m_rws->loadSnapshot( varsName ) )
    {
        throw WSRetrievalFailure("Fitter::gaussian_randomiser",
                *m_rws, varsName, "wiggle snapshot");
    }
}

//-----------------------------------------------------------------------------
// Randomise the parameters uniformly within their specified range.
//-----------------------------------------------------------------------------
void Fitter::uniform_randomiser( const RooArgSet* params, int seed, const char* varsName ) 
{

    RooArgSet randomisedVars;
    TRandom3 random( seed );
    RooFIter paramIter = params->fwdIterator();
    RooRealVar* var(0);
    double newval(0.);
    while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
        std::string name( var->GetName() );
        std::string classname( var->ClassName() );
        if (classname!="RooRealVar") {
            continue; 
        }

        newval = random.Uniform( var->getMin(), var->getMax() );

        setParameterValue( name.c_str(), newval );
        randomisedVars.add( *var );
    }

    // save the snapshot
    m_rws->saveSnapshot( varsName, randomisedVars, kTRUE );

    if ( !m_rws->loadSnapshot( varsName ) )
    {
        throw WSRetrievalFailure("Fitter::uniform_randomiser",
                *m_rws, varsName, "wiggle snapshot");
    }

}

//-----------------------------------------------------------------------------
// wiggle the parameter values by their errors
//-----------------------------------------------------------------------------
void Fitter::wiggleParams( const RooArgSet* fitParams, 
	RandomMethod randomiser, const char* fitName,
	Int_t seed, const char* varsName ) 
{

    // check that fitName is valid, no need to load the snapshot though..
    if (fitName&&strcmp(fitName,"")!=0)
    {
        //    if (!m_rws->loadSnapshot(fitName))
        //    {
        throw WSRetrievalFailure("Fitter::wiggleParams"
                ,*m_rws, fitName, "fitName not valid");
        //   }
    }

    TRandom3 rand( seed );
    double randomVal(0);
    switch( randomiser ) {
        case GAUSSIAN:
            gaussian_randomiser( fitParams, seed, varsName );
            break;  
        case CORRELATION:
            correlation_randomiser( fitParams, seed, varsName, fitName );
            break;
        case UNIFORM:
            uniform_randomiser( fitParams, seed, varsName );
            break;
        case ALL:
            randomVal = rand.Uniform( 0., 1. );
            if( randomVal <= 0.3333  ) {
                uniform_randomiser( fitParams, seed, varsName );
            } else if( randomVal > 0.3333 && randomVal <= 0.6666) {
                gaussian_randomiser( fitParams, seed, varsName );
            } else {
                correlation_randomiser( fitParams, seed, varsName, fitName );
            }
            break;
        case NONE:
            std::cout << "INFO: Fitter::wiggleParams - no randomisation applied to initial parameters.\n";
            break;
        default:
            std::cout << "INFO: Fitter::wiggleParams - using default correlation randomiser.\n";
            correlation_randomiser( fitParams, seed, varsName, fitName );
            break;
    }

}

//-----------------------------------------------------------------------------
/// Wiggle only the set of parameters that have been specified varsList
//-----------------------------------------------------------------------------
void Fitter::wiggleParams( std::string& varsList, RandomMethod randomiser,
	const char* fitName, Int_t seed, const char* varsName ) 
{

    //put dependents names in a vector
    std::vector<std::string> dependents_vec;
    m_stringHelper.replaceAll( varsList, " ", "" ); // remove all whitespaces
    m_stringHelper.split( dependents_vec, varsList, "," );

    if( dependents_vec.empty() || varsList == "" ) {
        std::stringstream msg;
        msg << "Failed to parse the parameter string: reads =>  " << varsList;
        throw GeneralException("Fitter::wiggleParams", msg.str() );        
    }

    RooArgSet depSet;

    //checking we have all the dependents
    RooAbsReal* var = 0;
    std::vector<std::string>::const_iterator iter = dependents_vec.begin();
    const std::vector<std::string>::const_iterator end = dependents_vec.end();

    for ( ; iter != end; ++iter) {
        var = dynamic_cast<RooAbsReal*>( m_rws->obj( iter->c_str() ) );
        if(!var) {
            throw WSRetrievalFailure("Fitter::wiggleParams",
                    *m_rws, iter->c_str(), "RooAbsReal");
        }    
        depSet.add( *var );
    }

    wiggleParams( dynamic_cast<RooArgSet*>(&depSet), randomiser, fitName, seed, varsName );
}

//-----------------------------------------------------------------------------
// wiggle the parameter values by their errors
// from the MC fit for systematic studies concerning fixed parameters
//-----------------------------------------------------------------------------
void Fitter::wiggleParamsFixed( const RooArgSet* fitParams, 
	RandomMethod randomiser, RooFitResult* MCResult, const char* fitName,
        Int_t seed, const char* varsName ) 
{

    // check that the plot variable is in the list of observables
    if (fitName&&strcmp(fitName,"")!=0)
    {
        if (!m_rws->loadSnapshot(fitName))
        {
            throw WSRetrievalFailure("Fitter::wiggleParamsFixed"
                    ,*m_rws, fitName, "fit snapshot");
        }
    }

    TRandom3 rand( seed );
    double randomVal(0);
    switch( randomiser ) {
        case GAUSSIAN:
            gaussian_randomiser( fitParams, seed, varsName );
            break;  
        case CORRELATION:
            correlation_randomiser_Fixed( fitParams, seed, varsName, MCResult);
            break;
        case UNIFORM:
            uniform_randomiser( fitParams, seed, varsName );
            break;
        case ALL:
            randomVal = rand.Uniform( 0., 1. );
            if( randomVal <= 0.3333  ) {
                uniform_randomiser( fitParams, seed, varsName );
            } else if( randomVal > 0.3333 && randomVal <= 0.6666) {
                gaussian_randomiser( fitParams, seed, varsName );
            } else {
                correlation_randomiser( fitParams, seed, varsName, fitName );
            }
            break;
        case NONE:
            std::cout << "INFO: Fitter::wiggleParamsFixed - no randomisation applied to initial parameters.\n";
            break;
        default:
            std::cout << "INFO: Fitter::wiggleParamsFixed - using default correlation randomiser.\n";
            correlation_randomiser_Fixed( fitParams, seed, varsName,  MCResult);
            break;
    }
}

//-----------------------------------------------------------------------------
// Wiggle only the set of parameters that have been specified varsList 
// from the MC fit for systematic studies concerning fixed parameters
//-----------------------------------------------------------------------------
void Fitter::wiggleParamsFixed( std::string& varsList, RandomMethod randomiser,
	RooFitResult* MCResult, const char* fitName, Int_t seed, const char* varsName ) 
{
    //put dependents names in a vector
    std::vector<std::string> dependents_vec;
    m_stringHelper.replaceAll( varsList, " ", "" ); // remove all whitespaces
    m_stringHelper.split( dependents_vec, varsList, "," );

    if( dependents_vec.empty() || varsList == "" ) {
        std::stringstream msg;
        msg << "Failed to parse the parameter string: reads =>  " << varsList;
        throw GeneralException("Fitter::wiggleParamsFixed", msg.str() );        
    }

    RooArgSet depSet;

    //checking we have all the dependents inside the current WS (data)
    RooAbsReal* var = 0;
    std::vector<std::string>::const_iterator iter = dependents_vec.begin();
    const std::vector<std::string>::const_iterator end = dependents_vec.end();

    for ( ; iter != end; ++iter) {
        var = dynamic_cast<RooAbsReal*>( m_rws->obj( iter->c_str() ) );
        if(!var){
            throw WSRetrievalFailure("Fitter::wiggleParamsFixed",
                    *m_rws, iter->c_str(), "RooAbsReal");
        }    
        depSet.add( *var );
    }

    wiggleParamsFixed( dynamic_cast<RooArgSet*>(&depSet), randomiser, MCResult, fitName, seed, varsName );
}

//-----------------------------------------------------------------------------
// Wiggle only the set of parameters that have been specified varsList 
// from the MC fit for systematic studies concerning fixed parameters
// The map is mandatory as some parameters may have a different name in
// the MC fit. Also, several parameters can point to the same name.
// At last, some parameters may be constant in the MC fit and still be in the
// map. These must be precised in the constPars argument.
//-----------------------------------------------------------------------------
void Fitter::wiggleParamsFixed( std::vector<std::multimap<std::string,std::string> > varsList,
        std::vector<std::string> constPars ,
        RandomMethod randomiser,
        RooFitResult* MCResult,
        const char* fitName,
        Int_t seed,
        const char* varsName) 
{

    // check that the plot variable is in the list of observables
    if (fitName&&strcmp(fitName,"")!=0)
        if (!m_rws->loadSnapshot(fitName))
            throw WSRetrievalFailure("Fitter::wiggleParamsFixed"
                    ,*m_rws, fitName, "fit snapshot");
    TRandom3 rand( seed );

    // Loop over the multimap to translate the pair of param. names to a pair of RooAbsArgs.
    std::vector<std::multimap<RooAbsReal*,RooAbsReal*> > varVectors;
    for (std::vector<std::multimap<std::string,std::string> >::iterator itVector = varsList.begin() ; itVector != varsList.end() ; itVector++)
    {
        std::multimap<RooAbsReal*,RooAbsReal*> vars;
        for (std::multimap<std::string,std::string>::iterator it = itVector->begin() ; it != itVector->end() ; it++)		
        {
            //First, let us see if we are looking to a constant parameter.
            bool isConstant = false;
            for (std::vector<std::string>::iterator itConst = constPars.begin() ; itConst != constPars.end() ; ++itConst)
                isConstant += (it->first == *itConst);

            RooAbsReal* arg1 = m_rws->var(it->first .c_str());
            RooAbsReal* arg2 = NULL;
            int index = MCResult->floatParsFinal().index(it->second.c_str());
            //					MCResult->Print("v");
            if (index == -1 && !isConstant)
            {
                std::cout << "Variable " << it->second << " not found in the RooFitResult!" << std::endl;				
                MCResult->Print();

            }
            else if (it->first.find("threshold") != std::string::npos)
                arg2 = (RooAbsReal*) (&MCResult->constPars()[MCResult->constPars().index(it->second.c_str())]);
            else
                arg2 = (RooAbsReal*) (&MCResult->floatParsFinal()[index]);
            if (arg1 == NULL)
            {
                std::cout << "Variable " << it->first << " not found in the workspace!" << std::endl;
                std::exit(1);
            }
            vars.insert(std::make_pair(arg1,arg2));
        }
        varVectors.push_back(vars);
        switch( randomiser ) {
            case GAUSSIAN:
                std::cout << "NOT IMPLEMENTED YET" << std::endl;
                //					gaussian_randomiser_Fixed( vars, seed, varsName );
                break;  				
            case CORRELATION:
                correlation_randomiser_Fixed( vars , seed, varsName, MCResult);
                break;
            case UNIFORM:
                std::cout << "NOT IMPLEMENTED YET" << std::endl;
                //		uniform_randomiser( fitParams, seed, varsName );
                break;
            case ALL:
                std::cout << "NOT IMPLEMENTED YET" << std::endl;
                /*
                   randomVal = rand.Uniform( 0., 1. );
                   if( randomVal <= 0.3333  ) {
                   uniform_randomiser( fitParams, seed, varsName );
                   } else if( randomVal > 0.3333 && randomVal <= 0.6666) {
                   gaussian_randomiser( fitParams, seed, varsName );
                   } else {
                   correlation_randomiser( fitParams, seed, varsName, fitName );
                   }
                   */
                break;
            case NONE:
                std::cout << "INFO: Fitter::wiggleParamsFixed - no randomisation applied to initial parameters.\n";
                break;

            default:
                //		std::cout << "INFO: Fitter::wiggleParamsFixed - using default correlation randomiser.\n";
                //		correlation_randomiser_Fixed( fitParams, seed, varsName,  MCResult);
                break;
        }
    }
}

//-----------------------------------------------------------------------------
// wiggle the parameter values by their errors
//-----------------------------------------------------------------------------
void Fitter::wiggleAllParams( RooAbsPdf* model, RooDataSet *rds, RandomMethod randomiser,
	const char* fitName, Int_t seed, const char* varsName )
{

    // Get the current variables in the model.
    //const RooArgSet* fitParams = const_cast<RooArgSet*>( model->getParameters( *rds ) );
    const RooArgSet* fitParams = model->getParameters( *rds );//->selectByAttrib("Constant",kFALSE)

    this->wiggleParams( fitParams, randomiser, fitName, seed, varsName );

    delete fitParams; fitParams = 0;

}

//-----------------------------------------------------------------------------
// attach a file for writing out the RooWorkspace
//-----------------------------------------------------------------------------
void Fitter::attachFile(const char* filename, const char* options)
{
    if (m_file)
    {
        std::cout << "WARNING: Deleting existing TFile " << m_file->GetName()
            << std::endl;
        delete m_file;
    }
    TFile *f=TFile::Open(filename, options);
    if (!f || f->IsZombie())
    {
        throw IOFailure("Fitter::AttachFile", filename, options);
    }
    m_file=f;
}

//-----------------------------------------------------------------------------
// load an existing RooWorkspace from file,
// and optionally attach the file for writing any changes to the
// RooWorkspace
//-----------------------------------------------------------------------------
void Fitter::loadWS( const char* filename, const char* wsName,
        Bool_t attachFile)
{
    const char *mode=(!attachFile)?"READ":"UPDATE";
    TFile *f=TFile::Open(filename, mode);
    if (!f || f->IsZombie())
    {
        throw IOFailure("Fitter::loadWS", filename, mode);
    }

    RooWorkspace *rws = dynamic_cast<RooWorkspace*>(f->Get(wsName));
    if (!rws)
    {
        throw TDirectoryError("Fitter::loadWS", *f, wsName);
    }
    if (m_hasOwnership&&m_rws)
    {
        std::cout << "WARNING: Deleting existing RooWorkspace " << m_rws->GetName()
            << std::endl;
        delete m_rws; m_rws=0;
    }
    m_rws=rws;
    m_hasOwnership=kFALSE;
    if (attachFile)
    {
        if (m_file)
        {
            std::cout << "WARNING: Deleting existing TFile " << m_file->GetName()
                << std::endl;
            delete m_file; m_file=0;
        }
        m_file=f;
    }

    RooRealVar* finalModelNameVar = m_rws->var("ModelName");
    if ( !finalModelNameVar ) {
        throw WSRetrievalFailure( "Fitter::loadWS",
                *m_rws, "ModelName", "RooRealVar" );
    }
    TString name = finalModelNameVar->GetTitle();
    m_modelName = name.Data();
}

//-----------------------------------------------------------------------------
// save the workspace to the attached file
//-----------------------------------------------------------------------------
void Fitter::saveWS()
{
    if (!m_file)
    {
        throw GeneralException("Fitter::SaveWS",
                "No output file specified. Cannot save workspace.");
    }

    // We need to store the latest instance of the model name incase
    // any alias/contraints were applied.
    RooRealVar finalModelName( "ModelName", getModelName(), 1 );
    if ( m_rws->import( finalModelName, RooFit::RecycleConflictNodes() ) ) {
    // if ( m_rws->import( finalModelName ) ) { // v1r0 Script
        throw WSImportFailure("Fitter::saveWS",
                *m_rws, finalModelName);
    }

    m_file->cd();
    m_rws->Write();
}

//-----------------------------------------------------------------------------
// save the workspace to the specified file
//-----------------------------------------------------------------------------
void Fitter::saveWS(const char* filename, Bool_t recreateFile)
{
    const char* mode=(recreateFile)?"RECREATE":"UPDATE";
    attachFile(filename, mode);

    // We need to store the latest instance of the model name incase
    // any alias/contraints were applied.
    RooRealVar finalModelName( "ModelName", getModelName(), 1 );
    if ( m_rws->import( finalModelName, RooFit::RecycleConflictNodes()) ) {
    // if ( m_rws->import( finalModelName) ) { // v1r0 Script
        throw WSImportFailure("Fitter::saveWS",
                *m_rws, finalModelName);
    }    
    m_file->cd();
    m_rws->Write();
}

//-----------------------------------------------------------------------------
// Save the workspace to the specified file
// Since we don't own the file, we should release ownership
//-----------------------------------------------------------------------------
void Fitter::saveWS(TFile* f)
{
    if (!f) { 
        throw GeneralException("Fitter::SaveWS",
                "No output file specified. Cannot save workspace.");
    }

    // We need to store the latest instance of the model name incase
    // any alias/contraints were applied.
    RooRealVar finalModelName( "ModelName", getModelName(), 1 );
    if ( m_rws->import( finalModelName ) ) {
        throw WSImportFailure("Fitter::saveWS",
                *m_rws, finalModelName);
    }    

    f->cd();
    m_rws->Write();

    if (m_hasOwnership) {
        std::cout << "WARNING: Releasing ownership of RooWorkspace to TFile " << f->GetName()
            << std::endl;
    }
    m_hasOwnership=kFALSE;
}

//-----------------------------------------------------------------------------
// create a reduced data set with name "newName" using cut "cut"
// If saveToWS is true, then the new data set is saved to the workspace,
// otherwise a pointer to the new data set is returned
//-----------------------------------------------------------------------------
RooDataSet* Fitter::createReducedDataSet(const char* newName,
               const char* cut,
               Bool_t saveToWS) 
{
    if (!m_rws)
    {
        throw GeneralException("Fitter::createReducedDataSet",
                "No RooWorkspace object is defined");
    }
    if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
    {
        throw GeneralException("Fitter::createReducedDataSet",
                "No RooDataSet name defined");
    }
    RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
    if (!rds)
    {
        throw WSRetrievalFailure("Fitter::createReducedDataSet",
                *m_rws, m_dataSetName, "RooDataSet");
    }
    RooDataSet* rds_reduced = dynamic_cast<RooDataSet*>( rds->reduce( cut ) );
    if (!rds_reduced)
    {
        std::stringstream msg;
        msg << "Failed to create reduced data set with cut " << cut;

        throw GeneralException("Fitter::createReducedDataSet",
                msg.str());
    }
    rds_reduced->SetName(newName);
    if (saveToWS) {
        if (m_rws->import( *rds_reduced ) ) {
            throw WSImportFailure("Fitter::createReducedDataSet",
                    *m_rws, *rds_reduced);
        }
        return 0;
    }
    return rds_reduced;
}


//-----------------------------------------------------------------------------
// create a reduced data set with name "newName" using range "range"
// If saveToWS is true, then the new data set is saved to the workspace,
// otherwise a pointer to the new data set is returned
// multiple range can be specified using a colon separator
//-----------------------------------------------------------------------------
RooDataSet* Fitter::createReducedDataSetByRange(const char* newName,
        const char* range,
        Bool_t saveToWS) 
{
    if (!m_rws)
    {
        throw GeneralException("Fitter::createReducedDataSetByRange",
                "No RooWorkspace object is defined");
    }
    if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
    {
        throw GeneralException("Fitter::createReducedDataSetByRange",
                "No RooDataSet name defined");
    }
    if (!range||strcmp(range,"")==0)
    {
        throw GeneralException("Fitter::createReducedDataSetByRange",
                "No range defined");
    }

    RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
    if (!rds)
    {
        throw WSRetrievalFailure("Fitter::createReducedDataSetByRange",
                *m_rws, m_dataSetName, "RooDataSet");
    }
    std::string str( range );
    std::vector<std::string> args;
    m_stringHelper.replaceAll( str, " ", "" ); // remove all whitespaces
    m_stringHelper.split( args, str, ";" );

    RooDataSet* rds_reduced = 0;

    std::cout << "Fitter::createReducedDataSetByRange: Got " 
        << args.size() << " ranges: " << str << std::endl;

    switch (args.size()) {
        case 0:
            {
                throw GeneralException("Fitter::createReducedDataSetByRange",
                        "Unable to get list of ranges");
                break;
            }
        case 1:
            {
                std::string r1=args.at(0);
                rds_reduced = dynamic_cast<RooDataSet*>( rds->reduce( RooFit::CutRange( r1.c_str() ) ) );
                break;
            }
        case 2:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                rds_reduced = dynamic_cast<RooDataSet*>(rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str())));
                break;
            }
        case 3:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                std::string r3=args.at(2);
                rds_reduced = dynamic_cast<RooDataSet*>(rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str()),
                            RooFit::CutRange(r3.c_str())));
                break;
            }
        case 4:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                std::string r3=args.at(2);
                std::string r4=args.at(3);
                rds_reduced = dynamic_cast<RooDataSet*>(rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str()),
                            RooFit::CutRange(r3.c_str()),
                            RooFit::CutRange(r4.c_str())));
                break;
            }
        case 5:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                std::string r3=args.at(2);
                std::string r4=args.at(3); 
                std::string r5=args.at(4);
                rds_reduced = dynamic_cast<RooDataSet*>( rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str()),
                            RooFit::CutRange(r3.c_str()),
                            RooFit::CutRange(r4.c_str()),
                            RooFit::CutRange(r5.c_str())));
                break;
            }
        case 6:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                std::string r3=args.at(2);
                std::string r4=args.at(3); 
                std::string r5=args.at(4);
                std::string r6=args.at(5);
                rds_reduced = dynamic_cast<RooDataSet*>( rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str()),
                            RooFit::CutRange(r3.c_str()),
                            RooFit::CutRange(r4.c_str()),
                            RooFit::CutRange(r5.c_str()),
                            RooFit::CutRange(r6.c_str())));
                break;
            }
        case 7:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                std::string r3=args.at(2);
                std::string r4=args.at(3); 
                std::string r5=args.at(4);
                std::string r6=args.at(5);
                std::string r7=args.at(6);
                rds_reduced = dynamic_cast<RooDataSet*>( rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str()),
                            RooFit::CutRange(r3.c_str()),
                            RooFit::CutRange(r4.c_str()),
                            RooFit::CutRange(r5.c_str()),
                            RooFit::CutRange(r6.c_str()),
                            RooFit::CutRange(r7.c_str())));
                break;
            }
        case 8:
            {
                std::string r1=args.at(0);
                std::string r2=args.at(1);
                std::string r3=args.at(2);
                std::string r4=args.at(3); 
                std::string r5=args.at(4);
                std::string r6=args.at(5);
                std::string r7=args.at(6);
                std::string r8=args.at(7);
                rds_reduced = dynamic_cast<RooDataSet*>( rds->reduce(RooFit::CutRange(r1.c_str()),
                            RooFit::CutRange(r2.c_str()),
                            RooFit::CutRange(r3.c_str()),
                            RooFit::CutRange(r4.c_str()),
                            RooFit::CutRange(r5.c_str()),
                            RooFit::CutRange(r6.c_str()),
                            RooFit::CutRange(r7.c_str()),
                            RooFit::CutRange(r8.c_str())) );
                break;
            }
        default:
            {
                std::stringstream msg;
                msg << "No more than 8 ranges supported, but " << args.size()
                    << " requested";
                throw GeneralException("Fitter::createReducedDataSetByRange",
                        msg.str() );
                break;
            }    
    }

    if ( !rds_reduced )
    {
        std::stringstream msg;
        msg << "Failed to create reduced data set with cut range " << str;

        throw GeneralException("Fitter::createReducedDataSetByRange",
                msg.str());
    }

    // set a new name for the dataset
    rds_reduced->SetName(newName);
    if ( saveToWS ) {
        if (m_rws->import( *rds_reduced ) ) {
            throw WSImportFailure("Fitter::createReducedDataSetByRange",
                    *m_rws, *rds_reduced);
        }
        return 0;
    }

    return rds_reduced;

}


//=============================================================================
// Import the given dataset.
//=============================================================================  
void Fitter::importDataSet(RooDataSet* theData)
{
    if (!m_rws) {
        throw GeneralException("RooSimpleFitter::importDataSet",
                "No RooWorkspace object is defined.");
    }

    if (m_rws->import( *theData ) ) {
        throw WSImportFailure("RooFitter::importDataSet",
                *m_rws, *theData);
    }

}

//-----------------------------------------------------------------------------
// perform the fit of the specified model PDF to the specified data
//-----------------------------------------------------------------------------
void Fitter::performFit(const char* fitName, Bool_t useMinos,
        Bool_t verboseMode, Bool_t saveSnapshot, Bool_t printResults,
        Bool_t useSumW2Errors, Bool_t extendedMode)
{
    if (!m_rws)
    {
        throw GeneralException("Fitter::performFit",
                "No RooWorkspace object is defined");
    }
    if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
    {
        throw GeneralException("Fitter::performFit",
                "No RooDataSet name defined");
    }

    RooDataSet *rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds)
    {
        throw WSRetrievalFailure("Fitter::performFit",
                *m_rws, m_dataSetName, "RooDataSet");
    }
    if (rds->numEntries()==0) {
        throw GeneralException("Fitter::performFit",
                "Request to perform fit to data set with no entries");
    }

    RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );
    if (!model)
    {
        throw WSRetrievalFailure("Fitter::performFit",
                *m_rws, m_modelName, "RooAbsPdf");
    }


    const RooArgSet* theConstraints = m_rws->set( m_ConstraintSetName );

    RooFitResult* res = model->fitTo(*rds, 
            RooFit::Extended(extendedMode),
            RooFit::NumCPU(m_nCores),
            RooFit::Timer(kTRUE),
            RooFit::Minos(useMinos),
            // RooFit::Strategy(2),
            RooFit::SumW2Error(useSumW2Errors),
            RooFit::Verbose(verboseMode),
            RooFit::Save(kTRUE),
            RooFit::ExternalConstraints( *theConstraints )
            //RooFit::PrintLevel(-1)
            //RooFit::PrintEvalErrors(-1)
            );

    if (printResults && res) {
        res->Print("v");
    }

    if (saveSnapshot) {
        const RooArgSet* fitParams = model->getParameters(*rds);
        assert(fitParams);
        m_rws->saveSnapshot(fitName,*fitParams,kTRUE);
    }

    TString fitResName = TString::Format("rfres_%s", fitName);
    res->SetName( fitResName );
    if ( m_rws->import( *res, kTRUE ) ) {
        throw WSImportFailure("Fitter::performFit",
                *m_rws, *res);
    }

    delete res; res=0;
}


//=============================================================================
//add a constraint on varname with formula and dependents of the formula
//varname and all the dependents must all be already in the workspace
//=============================================================================
void Fitter::addConstraint(const char* varname, 
        const char* formula, 
        const char* dependents)
{
    //put dependents names in a vector
    std::vector<std::string> dependents_vec;
    std::string dummy( dependents );  
    m_stringHelper.replaceAll( dummy, " ", "" ); // remove all whitespaces
    m_stringHelper.split( dependents_vec, dummy, "," );
  
    RooArgList depList;
  
    //checking we have all the dependents
    RooAbsReal* var = 0;
    std::vector<std::string>::const_iterator iter = dependents_vec.begin();
    const std::vector<std::string>::const_iterator end = dependents_vec.end();
  
    for ( ; iter != end; ++iter) {
        var = dynamic_cast<RooAbsReal*>( m_rws->obj( iter->c_str() ) );
        if(!var){
            throw WSRetrievalFailure("Fitter::addConstraint",
                    *m_rws, iter->c_str(), "RooAbsReal");
        }    
        depList.add(*var);
    }
    //checking that the var we are constraining is there
    var = dynamic_cast<RooAbsReal*>( m_rws->obj( varname ) );
    if(!var){
        throw WSRetrievalFailure("Fitter::addConstraint",
                *m_rws, varname, "RooAbsReal");
    }
    
    //make the rooformulavar
    std::stringstream newname;
    newname << varname << "_function";
    RooFormulaVar function( newname.str().c_str(), "", formula, depList ) ;
    //import it first since import clones the object and to get the address of
    //it in the RooWorkspace one must get it again
    if ( m_rws->import( function ) ) {
        throw WSImportFailure("Fitter::addConstraint",
                *m_rws, function);
    }
  
    RooAbsReal* newvar = dynamic_cast<RooAbsReal*>( m_rws->obj( newname.str().c_str() ) );
    if(!newvar){
        throw WSRetrievalFailure("Fitter::addConstraint",
                *m_rws, newname.str().c_str(), "RooAbsReal");
    }
  
    ClientTree theTree( var, getOldObjects() );
  
    std::vector<std::string> commands = theTree.clientReplace( var, newvar, *this );
    std::vector<std::string> trashes = theTree.getModifiedObjectNames();
  
    iter = commands.begin();
    const std::vector<std::string>::const_iterator enditer = commands.end();
    for ( ; iter != enditer; ++iter ) { 
        if ( iter->find("EDIT") != std::string::npos ) {
            RooAbsArg* arg = m_rws->factory( iter->c_str() );
            if (arg == NULL)
            {
                std::cout <<"FATAL: This has not been processed: " << iter->c_str() << std::endl;
                std::exit(1);
            }
        }
        else {
            std::stringstream msg;
            msg << "Bad RooFactoryWSTool command " << *iter << ".";
            throw GeneralException( "Fitter::addConstraint", msg.str() );
        }
    }

    //put all modified objects in the old objects vector
    iter = trashes.begin();
    const std::vector<std::string>::const_iterator endit = trashes.end();
    for ( ; iter != endit; ++iter ) {
        scrap( iter->c_str() );
    }
}

//=============================================================================
// create the (usually B mass) variable to be fit over
//=============================================================================
void Fitter::make1DFitVar(Float_t xmin, Float_t xmax, 
        const char* unit, const char* title) 
{
    if (!m_rws) {
        throw GeneralException("Fitter::make1DFitVar",
                "No RooWorkspace object is defined.");
    }

    if (!m_1DFitVarName||strcmp(m_1DFitVarName,"")==0) {
        throw GeneralException("Fitter::make1DFitVar",
                "No variable name specified.");
    }

    RooRealVar var( m_1DFitVarName, ( !title ) ? "" : title, xmin, xmax,
            ( !unit ) ? "MeV/c^{2}" : unit );

    if ( m_rws->import( var ) ) {
        throw WSImportFailure( "Fitter::make1DFitVar", *m_rws, var );
    }

}

//-----------------------------------------------------------------------------
// Perform a binned fit to the model PDF
// A binned clone of the data is made, which is then used to fit the PDF
// The default binning for each variable in the original dataset is used
// The number of bins for a given variable can be changed using the
// SetBins method
// By default, a maximum likelihood fit is performed. If useChi2Method is
// set to true, then a chi^2 fit is performed instead
//-----------------------------------------------------------------------------
void Fitter::performBinnedFit(const char* fitName,
        Bool_t saveSnapshot, Bool_t printResults,
        Bool_t useSumW2Errors, 
        Bool_t extendedMode,
        Bool_t useChi2Method )
{
    if (!m_rws) {
        throw GeneralException("Fitter::performBinnedFit",
                "No RooWorkspace object is defined");
    }

    if (!m_dataSetName||strcmp(m_dataSetName,"")==0) {

        throw GeneralException("Fitter::performBinnedFit",
                "No RooDataSet name defined");
    }

    RooDataSet *rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );

    if (!rds) {

        throw WSRetrievalFailure( "Fitter::performBinnedFit",
                *m_rws, m_dataSetName, "RooDataSet");
    }

    if (rds->numEntries()==0) {
        throw GeneralException("Fitter::performBinnedFit",
                "Request to perform fit to data set with no entries");
    }

    // get the model PDF
    RooAbsPdf* model = dynamic_cast<RooAddPdf*>( m_rws->pdf( m_modelName ) );
    if (!model)
    {
        throw WSRetrievalFailure("Fitter::performBinnedFit"
                ,*m_rws, m_modelName, "RooAbsPdf");
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds ) ;
    assert(observables);

    TString binnedName  = TString::Format( "%s_binned", rds->GetName() );
    TString binnedTitle = TString::Format( "%s_binned", rds->GetTitle() );

    RooArgSet* obsCpy = dynamic_cast<RooArgSet*>( observables->Clone() );

    RooDataHist* hist = 0;
    try {
        hist = new RooDataHist(binnedName.Data(),
                binnedTitle.Data(),
                *obsCpy, *rds);
    }
    catch ( std::bad_alloc& e ) {
        std::stringstream msg;
        msg << "Got std::bad_alloc when creating new RooDataHist "
            << binnedName;
        throw GeneralException( "Fitter::performBinnedFit",
                msg.str() );
    }
    if ( !hist ) {
        throw GeneralException( "Fitter::performBinnedFit",
                "Failed to make binned copy of input data set" );
    }

    const RooArgSet* theConstraints = m_rws->set( m_ConstraintSetName );

    RooFitResult* res = 0;
    if (!useChi2Method) {

        res = model->fitTo(*hist, RooFit::Extended(extendedMode),
                RooFit::NumCPU(m_nCores),
                RooFit::Timer(kTRUE),
                RooFit::SumW2Error(useSumW2Errors),
                RooFit::Save(kTRUE),
                RooFit::PrintLevel(0),
                RooFit::ExternalConstraints( *theConstraints )
                );
    } else {

        RooAbsData::ErrorType errType= !useSumW2Errors ? RooAbsData::Poisson : RooAbsData::SumW2;
        res = model->chi2FitTo(*hist, RooFit::Extended(extendedMode),
                RooFit::NumCPU(m_nCores),
                RooFit::DataError(errType),
                RooFit::Timer(kTRUE),
                RooFit::Save(kTRUE),
                RooFit::PrintLevel(0),
                RooFit::ExternalConstraints( *theConstraints )
                );
    }

    if (printResults&&res) {
        res->Print("v");
    }

    if ( saveSnapshot ) {
        const RooArgSet* fitParams = model->getParameters(*rds);
        assert( fitParams );
        m_rws->saveSnapshot( fitName, *fitParams, kTRUE );
    }

    TString fitResName = TString::Format( "rfres_%s", fitName );
    res->SetName( fitResName );
    if ( m_rws->import( *res, kTRUE ) ) {
        throw WSImportFailure("Fitter::performBinnedFit",
                *m_rws, *res );
    }
    delete res; res=0;
    delete hist; hist=0;
}

//-----------------------------------------------------------------------------
void Fitter::performIterativeBinnedFit( std::vector<Int_t>& minuitStrategies,
        const char* fitName, 
        Bool_t saveSnapshot, Bool_t printResults,
        Bool_t useSumW2Errors, 
        Bool_t extendedMode,
        Bool_t useChi2Method )
{
    if (!m_rws) {

        throw GeneralException("Fitter::performIterativeBinnedFit",
                "No RooWorkspace object is defined");
    }

    if (!m_dataSetName||strcmp(m_dataSetName,"")==0) {
        throw GeneralException("Fitter::performIterativeBinnedFit",
                "No RooDataSet name defined");
    }

    RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
    if (!rds) {
        throw WSRetrievalFailure("Fitter::performIterativeBinnedFit",
                *m_rws, m_dataSetName, "RooDataSet");
    }
    if (rds->numEntries()==0) {
        throw GeneralException("Fitter::performIterativeBinnedFit",
                "Request to perform fit to data set with no entries");
    }

    // get the model PDF
    RooAddPdf* model = dynamic_cast<RooAddPdf*>( m_rws->pdf( m_modelName ) );
    if (!model) {
        throw WSRetrievalFailure("Fitter::performIterativeBinnedFit"
                ,*m_rws, m_modelName, "RooAddPdf");
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds );
    assert( observables );
    observables->Print();

    TString binnedName  = TString::Format( "%s_binned", rds->GetName()  );
    TString binnedTitle = TString::Format( "%s_binned", rds->GetTitle() );

    RooArgSet* obsCpy = dynamic_cast<RooArgSet*>( observables->Clone() );

    RooDataHist* hist = 0;
    try {
        hist = new RooDataHist( binnedName.Data(),
                binnedTitle.Data(),
                *obsCpy, *rds );
    }
    catch ( std::bad_alloc& e ) {
        std::stringstream msg;
        msg << "Got std::bad_alloc when creating new RooDataHist "
            << binnedName;
        throw GeneralException( "Fitter::performIterativeBinnedFit",
                msg.str() );
    }
    if ( !hist ) {
        throw GeneralException( "Fitter::performIterativeBinnedFit",
                "Failed to make binned copy of input data set" );
    }

    if ( minuitStrategies.empty() ) {
        throw GeneralException("Fitter::performIterativeBinnedFit",
                "vector<Int_t> empty");
    }

    const RooArgSet* theConstraints = m_rws->set( m_ConstraintSetName );

    RooFitResult* res = 0;
    std::vector<Int_t>::iterator itr = minuitStrategies.begin();
    for( ; itr < minuitStrategies.end(); ++itr ) {

        if ( !useChi2Method ) {

            res = model->fitTo( *hist, RooFit::Extended( extendedMode ),
                    RooFit::NumCPU( m_nCores ),
                    RooFit::Timer( kTRUE ),
                    RooFit::SumW2Error( useSumW2Errors ),
                    RooFit::Save( kTRUE ),
                    RooFit::Strategy( *itr ),
                    RooFit::PrintLevel(3),
                    RooFit::ExternalConstraints( *theConstraints )
                    );
        }
        else  {

            RooAbsData::ErrorType errType= ! useSumW2Errors ? RooAbsData::Poisson : RooAbsData::SumW2;
            res = model->chi2FitTo( *hist, RooFit::Extended( extendedMode ),
                    RooFit::NumCPU( m_nCores ),
                    RooFit::DataError( errType ),
                    RooFit::Timer( kTRUE ),
                    RooFit::Save( kTRUE ),
                    RooFit::Strategy( *itr ),
                    RooFit::PrintLevel( 3 ),
                    RooFit::ExternalConstraints( *theConstraints )
                    );
        }
    }//Loop over MINUIT Strategies

    if ( printResults && res ) {
        res->Print("v");
    }

    if (saveSnapshot) {
        const RooArgSet* fitParams = model->getParameters(*rds);
        assert(fitParams);
        m_rws->saveSnapshot(fitName,*fitParams,kTRUE);
    }

    TString fitResName = TString::Format( "rfres_%s", fitName );
    res->SetName( fitResName );
    if ( m_rws->import( *res, kTRUE ) ) {
        throw WSImportFailure( "Fitter::performIterativeBinnedFit",
                *m_rws, *res );
    }
    delete res; res=0;
    delete hist; hist=0;
}


//-----------------------------------------------------------------------------
// Calculate SWeights (Note that newName is only used when the RooDataSet
// is cloned). To use the current values for the fit parameters
// (instead of loading a snapshot), specify an empty string
// If no newName is specified, then the dataset with wrights will be called
// {origName}_withWeights, where {origName} is the name of the input dataset
//-----------------------------------------------------------------------------
void Fitter::calculateSWeights(const char* fitName,
        const char* newName)
{
    if (!m_rws) {
        throw GeneralException( "Fitter::calculateSWeights",
                "No RooWorkspace object is defined!" );
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure( "Fitter::calculateSWeights"
                ,*m_rws, m_dataSetName, "RooDataSet" );
    }

    RooAddPdf* model = dynamic_cast<RooAddPdf*>( m_rws->pdf( m_modelName ) );
    if ( !model ) {
        throw WSRetrievalFailure( "Fitter::calculateSWeights"
                ,*m_rws, m_modelName, "RooAddPdf" );
    }

    // make a copy of the RooAddPdf (otherwise sPlots does not work)
    RooAddPdf* modelClone = dynamic_cast<RooAddPdf*>( model->cloneTree() );
    assert( modelClone );

    const RooArgList yields = modelClone->coefList();

    if ( fitName && strcmp( fitName, "" ) != 0 ) {
        std::cout << "INFO: loading snapshot " << fitName << std::endl;
        if ( !m_rws->loadSnapshot( fitName ) ) {
            throw WSRetrievalFailure( "Fitter::calculateSWeights",
                    *m_rws, fitName, "fit snapshot" );
        }
    }
    if ( strcmp( newName, m_dataSetName ) == 0 ) {
        std::stringstream msg;
        msg << "Requested RooDataSet name " << newName 
            << " is the same as the current dataset";
        throw GeneralException("Fitter::calculateSWeights",
                msg.str());
    }

    TString weightedName = newName;
    if ( !newName || strcmp( newName, "" ) == 0 ) {
        weightedName.Form("%s_withWeights", rds->GetName());
        std::cout << "WARNING: No new RooDataSet name specified for "
            << " RooDataSet with weights. "
            << "Will use the name " << weightedName << std::endl;
    }

    // create sPlot object
    std::cout << "Constructing sWeights..." << std::endl;
    RooStats::SPlot* splot = new RooStats::SPlot( "sPlot", "An sPlot",
            *rds, modelClone,
            yields, RooArgSet(),
            kTRUE, kTRUE,
            weightedName.Data());


    RooDataSet* rds_withWeights = splot->GetSDataSet();
    if ( !rds_withWeights ) {
        throw GeneralException( "Fitter::calculateSWeights",
                "No dataset with sWeight variables returned by sPlot object!" );
    }

    std::cout << "Checking SWeights:" << std::endl;
    RooRealVar *arg = 0;
    TIterator *iter = yields.createIterator();
    assert( iter );
    while ( (arg = dynamic_cast<RooRealVar*>( iter->Next() ) ) ) {
        std::cout << "Yield " << arg->GetName()
            << " = " << arg->getVal()
            << " . From sWeights it is "
            << splot->GetYieldFromSWeight( arg->GetName() )
            << " . " << std::endl;
    }

    if( m_rws->import( *rds_withWeights ) ) {
        throw WSImportFailure( "Fitter::calculateSWeights",
                *m_rws, *rds_withWeights );
    }
    m_dataSetName = ( m_rws->data( weightedName ) )->GetName();

    RooArgSet weights( splot->GetSWeightVars() );
    if ( weights.getSize() < 1 ) {
        std::stringstream msg;
        msg << "Failed to get RooArgSet of sWeight variables";
        throw GeneralException( "Fitter::calculateSWeights",
                msg.str() );
    }

    if (m_rws->defineSet( m_sWeightVarSetName, weights ) ) {
        throw WSImportFailure("Fitter::calculateSWeights",
                *m_rws, weights, m_sWeightVarSetName );
    }

    // replace current name with weighted dataset
    delete modelClone; modelClone=0;
    delete splot; splot=0;
}


//-----------------------------------------------------------------------------
// Add dummy sWeights. The yieldName should be the name of the signal
// yield variable for that species. This will be assigned a weight of one.
// All other yields be assigned a weight of zero.
// One reason for using this method would be to assign dummy weights to 
// signal-associated Monte Carlo so that the selection code can be used
// on data and MC.
// if no newName is specified, then the dataset with weights will be called
// {origName}_withWeights, where {origName} is the name of the input dataset
//-----------------------------------------------------------------------------
void Fitter::createDummySWeights(const char* sVariable,
        Float_t weight,
        const char* newName,
        Bool_t appendToDataSet)
{

    if (!m_rws) {
        throw GeneralException( "Fitter::createDummySWeights",
                "No RooWorkspace object is defined!" );
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data(  m_dataSetName ) );
    if ( !rds ) {
        throw WSRetrievalFailure( "Fitter::createDummySWeights",
                *m_rws, m_dataSetName, "RooDataSet" );
    }

    TString weightedName = newName;
    if ( !appendToDataSet ) {
        if ( strcmp(newName, m_dataSetName ) == 0 ) {
            std::stringstream msg;
            msg << "Requested RooDataSet name " << newName 
                << " is the same as the current dataset";
            throw GeneralException( "Fitter::calculateSWeights",
                    msg.str() );
        }
        if ( !newName || strcmp( newName, "" ) == 0 ) {
            weightedName.Form("%s_withWeights", rds->GetName());
            std::cout << "WARNING: No new RooDataSet name specified for "
                << " RooDataSet with weights. "
                << "Will use the name " << weightedName << std::endl;
        }
    }

    RooDataSet* rds_withWeights = 0;
    if (appendToDataSet) {
        rds_withWeights = rds;
    } else {
        rds_withWeights = dynamic_cast<RooDataSet*>( rds->Clone( weightedName ) );
    }

    RooRealVar sWeight( sVariable, "", weight );
    rds_withWeights->addColumn( sWeight );

    if ( !appendToDataSet ) {
        if( m_rws->import( *rds_withWeights ) ) {
            throw WSImportFailure( "Fitter::calculateSWeights",
                    *m_rws, *rds_withWeights );
        }
        m_dataSetName = ( m_rws->data( weightedName ) )->GetName();
    }
    else {
        if( m_rws->import( sWeight ) ) {
            throw WSImportFailure( "Fitter::calculateSWeights",
                    *m_rws, sWeight );
        }
    }

    if ( m_rws->extendSet( m_sWeightVarSetName, sVariable ) ) {
        throw WSImportFailure( "Fitter::calculateSWeights",
                *m_rws, m_sWeightVarSetName, sVariable, kFALSE );
    }
}

//-----------------------------------------------------------------------------
// create a weighted dataset for a given sWeight species (sVariable).
// Note that the sWeight variables are named {yieldName}_sw,
// where {yieldName} is the name of the yield for a given species
// If saveToWS is false, then the dataset is returned (note it should be
// manually deleted), otherwise, a NULL pointer is returned, and the dataset
// is imported into the workspace
//-----------------------------------------------------------------------------
RooDataSet* Fitter::createWeightedDataSet( const char* newName,
        const char* sVariable, const char* fitName, 
        //const char* dataSetWithWeightsName,
        Bool_t saveToWS )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::createWeightedDataSet",
                "No RooWorkspace object is defined!" );
    }
    /*
       TString weightedName=dataSetWithWeightsName;
       if (!dataSetWithWeightsName||strcmp(dataSetWithWeightsName,"")==0)
       {
       weightedName.Form("%s_withWeights", m_dataSetName);
       std::cout << "WARNING: No new RooDataSet name specified for "
       << " RooDataSet with weights. "
       << "Will use the name " << weightedName << std::endl;
       }
       */
    if ( fitName && strcmp( fitName, "" ) != 0 ) {
        std::cout << "INFO: Loading snapshot " << fitName << std::endl;
        if ( !m_rws->loadSnapshot( fitName ) ) {
            throw WSRetrievalFailure("Fitter::createWeightedDataSet",
                    *m_rws, fitName, "fit snapshot");
        }
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure( "Fitter::createWeightedDataSet",
                *m_rws, m_dataSetName, "RooDataSet" );
    }

    RooRealVar* sVar=0;
    std::string varname( sVariable );
    sVar = m_rws->var( varname.c_str() );
    if ( !sVar ) {
        varname += "_sw";
        sVar = m_rws->var( varname.c_str() );
        if ( !sVar ) {
            throw WSRetrievalFailure( "Fitter::createWeightedDataSet",
                    *m_rws, sVariable, "RooRealVar" );
        }
    }

    RooDataSet* rds_ws = new RooDataSet( newName, rds->GetTitle(),
            rds, *( rds->get() ), 0, varname.c_str() );

    if (saveToWS) {

        if( m_rws->import( *rds_ws ) ) {
            delete rds_ws; rds_ws = 0;
            throw WSImportFailure("Fitter::createWeightedDataSet"
                    ,*m_rws, *rds_ws);
        }
        delete rds_ws;
        rds_ws=0;
    }
    return rds_ws;
}


//-----------------------------------------------------------------------------
// Save a weighted dataset for each sWeight species. By default, the new
// datasets will be of the form {origName}_{sVariable}, where {origName}
// is the name of the original RooDataSet, and sVariable is the name of the
//  sWeight for a particular species. If prefix is specified, then {origName}
// is replace by prefix.
//-----------------------------------------------------------------------------
void Fitter::saveWeightedDataSets( const char* fitName, 
        const char* prefix )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::saveWeightedDataSets",
                "No RooWorkspace object is defined!" );
    }

    const RooArgSet* weights = m_rws->set( m_sWeightVarSetName );
    if ( !weights ) {
        throw WSRetrievalFailure( "Fitter::saveWeightedDataSets",
                *m_rws, m_sWeightVarSetName, "RooArgSet" );
    }
    /*
       TString weightedName=dataSetWithWeightsName;
       if (!dataSetWithWeightsName||strcmp(dataSetWithWeightsName,"")==0)
       {
       weightedName.Form("%s_withWeights", m_dataSetName);
       std::cout << "WARNING: No new RooDataSet name specified for "
       << " RooDataSet with weights. "
       << "Will use the name " << weightedName << std::endl;
       }
       */
    if ( fitName && strcmp( fitName, "" ) !=0 ) {
        std::cout << "INFO: Loading snapshot " << fitName << std::endl;
        if ( !m_rws->loadSnapshot( fitName ) ) {
            throw WSRetrievalFailure( "Fitter::saveWeightedDataSets",
                    *m_rws, fitName, "fit snapshot" );
        }
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure( "Fitter::saveWeightedDataSets",
                *m_rws, m_dataSetName, "RooDataSet" );
    }

    const char* oldName = rds->GetName();
    TIterator *it = weights->createIterator();
    RooRealVar* v = 0;
    while ( (v= dynamic_cast<RooRealVar*>( it->Next() ) ) ) {

        std::string sVariable( v->GetName() );
        std::string newName = ( !prefix || strcmp( prefix, "" ) == 0 ) ? oldName : prefix;
        newName += "_";
        newName += sVariable;
        this->createWeightedDataSet( newName.c_str(), sVariable.c_str(), fitName, kTRUE );
    }

    delete it; it=0;

}


//-----------------------------------------------------------------------------
// Plots the pulls between the observable with name 'name' and the 
// combined signal+background model PDF
// NB. The variable must be an observable in the model PDF
//
// The function returns a RooHist pointer. Note that the user is responsible
//for deleting this object.
//-----------------------------------------------------------------------------
RooPlot* Fitter::plotFitPulls( const char* name,
        const char* fitName, double pmsigma, double pmline )
{
    // get the fit results plot
    RooPlot* rp = this->plotFitResults(name, fitName, "", "", kFALSE);

    std::string histName = this->getDataHistName();
    std::string curveName = this->getModelCurveName( name );

    RooHist* hist = rp->pullHist( histName.c_str(), curveName.c_str(), kFALSE);
    // RooHist* hist = rp->pullHist( histName.c_str(), curveName.c_str() ); \\ trunk Louis
    if( !hist ) {
        throw GeneralException( "Fitter::plotFitPulls",
                "Pull plot is NULL and was not created!");
    }
    // use the same fill color as is used for the line color of the model PDF
    hist->SetFillColor( m_modelLineColor );
    hist->SetLineColor( kBlack );


    RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "Fitter::plotFitPulls",
                *m_rws, name, "RooRealVar");
    }

    RooPlot* rp_pull = var->frame( rp->GetNbinsX() );

    // set the maximum range of the pull histograms, defaults to +/- 5
    rp_pull->SetMinimum( -pmsigma );
    rp_pull->SetMaximum( pmsigma );

    TAxis* xAxis = rp_pull->GetXaxis();

    // Add the 2 sigma lines to the plot
    double xMin = xAxis->GetXmin();
    double xMax = xAxis->GetXmax();

    TLine* midLine = 0;
    TLine* uppLine = 0;
    TLine* lowLine = 0;

    midLine = new TLine( xMin,  0., xMax,  0. );
    uppLine = new TLine( xMin,  pmline, xMax,  pmline );
    lowLine = new TLine( xMin, -pmline, xMax, -pmline );

    uppLine->SetLineColor( kRed );
    lowLine->SetLineColor( kRed );

    // N.B. addPlotable transfers ownership of the RooHist
    rp_pull->addPlotable( hist, "E1" );
    rp_pull->addObject( lowLine );
    rp_pull->addObject( midLine );
    rp_pull->addObject( uppLine );

    delete rp; rp=0;
    return rp_pull;

}


//-----------------------------------------------------------------------------
// Plot the observable with name 'name', showing the fit results
// NB. The variable must be an observable in the model PDF
//
// Optionally, a range can be specified. This will be used to extrapolate the
// yields to the given range. The function will raise an exception if the
// range does not exist for the given observable.
//
// By default, the extrapolated yields will be labelled "yieldTitle (range)".
// If rangeTitle is specified, then the label will be "yieldTitle (rangeTitle)"
//
// If sumWErrors is true, then plot sum-of-weights-squared errors (default is
// Poissonian errors). RooFit will force sum-of-weights-squared errors if the
// dataset is weighted.
//
// The function returns a RooPlot pointer. Note that the user is responsible
//for deleting this object.
//-----------------------------------------------------------------------------
RooPlot* Fitter::plotFitResults( const char* name,
        const char* fitName,
        const char* range,
        const char* rangeTitle,
        Bool_t sumW2Errors )
{

    if (!m_rws) {
        throw GeneralException("Fitter::plotFitResults",
                "No RooWorkspace object is defined!");
    }
    // check that name is specified
    if ( !name || strcmp( name, "" ) == 0 ) {
        throw GeneralException( "Fitter::plotFitResults",
                "No variable name has been specified!" );
    }

    // get the dataset
    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds)
    {
        throw WSRetrievalFailure("Fitter::plotFitResults"
                ,*m_rws, m_dataSetName, "RooDataSet");
    }

    // get the model PDF
    RooAddPdf* model = dynamic_cast<RooAddPdf*>( m_rws->pdf( m_modelName ) );
    if (!model) {
        throw WSRetrievalFailure( "Fitter::plotFitResults",
                *m_rws, m_modelName, "RooAddPdf" );
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds );
    if ( !observables ) {
        std::stringstream msg;
        msg << "Failed to get the list of observables "
            << "for model PDF " << model->GetName()
            << " from dataset " << rds->GetName();
        throw GeneralException( "Fitter::plotFitResults", msg.str() );
    }

    // get the plot variable
    RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure("Fitter::plotFitResults",
                *m_rws, name, "RooRealVar" );
    }

    // check that the plot variable is in the list of observables
    if ( !observables->contains( *var ) ) {
        std::stringstream msg;
        msg << "Plot variable " << name << " is not in the list of observables "
            << "for model PDF " << model->GetName();
        throw GeneralException( "Fitter::plotFitResults", msg.str() );
    }

    if ( fitName && strcmp( fitName, "" ) !=0 ) {
        if ( !m_rws->loadSnapshot( fitName ) ) {
            throw WSRetrievalFailure( "Fitter::plotFitResults",
                    *m_rws, fitName, "fit snapshot" );
        }
    }

    // get the plot parameters
    const RooArgSet* paramsTmp = m_rws->set( m_plotParamsSetName );
    if ( !paramsTmp ) {
        paramsTmp = model->getParameters(*rds);
        if (!paramsTmp) {
            throw WSRetrievalFailure( "Fitter::plotFitResults",
                    *m_rws, m_plotParamsSetName, "RooArgSet" );
        }
    }
    // get the RooFitResult
    const RooFitResult* rfres = this->getFitResult( fitName );

    const RooArgList& yieldList = model->coefList();
    const RooArgList& pdfList = model->pdfList();

    const RooArgSet& yields(yieldList);

    // clone the plot parameter set
    RooArgSet* params = dynamic_cast<RooArgSet*>( paramsTmp->Clone( "params" ) );

    // add yields (ignore duplicate warnings)
    params->add( yields, kTRUE );

    // make the RooPlot
    Int_t nPlotBins = getPlotBinsInt( name );

    RooPlot* rp = var->frame( RooFit::Bins( nPlotBins ) );
    if ( !rp ) {
        std::stringstream msg;
        msg << "Failed to get RooPlot for RooRealVar " << name;
        throw GeneralException( "Fitter::plotFitResults", msg.str() );
    }

    RooAbsData::ErrorType errorType = ( !sumW2Errors ) ? RooAbsData::Poisson
        :RooAbsData::SumW2;
    //rp->GetYaxis()->SetTitleOffset(1.2);
    if ( strcmp( var->GetTitle(), "" ) == 0 ) {
        rp->GetXaxis()->SetTitle( TString::Format( "%s %s", var->GetName(),
                    rp->GetXaxis()->GetTitle() ) );
    }

    RooLinkedList argList;
    RooCmdArg* arg = 0;
    try {
        arg = new RooCmdArg( RooFit::LineColor( m_dataSetLineColor ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }

    try {
        arg = new RooCmdArg( RooFit::LineStyle( m_dataSetLineStyle ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::LineWidth( m_dataSetLineWidth ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::MarkerColor( m_dataSetMarkerColor ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::MarkerStyle( m_dataSetMarkerStyle ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::MarkerSize( m_dataSetMarkerSize ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::FillColor( m_dataSetFillColor ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::FillStyle( m_dataSetFillStyle ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::DrawOption( m_dataSetDrawOption ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    try {
        arg = new RooCmdArg( RooFit::DataError( errorType ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg" );
    }
    rds->plotOn( rp, argList );

    model->plotOn( rp, RooFit::LineColor( m_modelLineColor ),
            RooFit::LineStyle( m_modelLineStyle ),
            RooFit::LineWidth( m_modelLineWidth ) 
            );

    // show the PDF components
    if ( m_pdfComponents.size() > 0 ) {

        for (std::vector<std::string>::iterator compName=m_pdfComponents.begin();
                compName!=m_pdfComponents.end(); ++compName )
        {
            const char* c_compName=compName->c_str();
            const Color_t& col = getPdfComponentLineColor(c_compName);
            const Style_t& style = getPdfComponentLineStyle(c_compName);
            const Width_t& width = getPdfComponentLineWidth(c_compName);

            model->plotOn(rp, RooFit::Components(c_compName),
                    RooFit::LineColor(col), RooFit::LineStyle(style),
                    RooFit::LineWidth(width)
                    );
        }
    }

    TPaveText *pv =0;
    try {
        pv = new TPaveText( m_paramBoxX1, m_paramBoxY1,
                m_paramBoxX2, m_paramBoxY2, "BRNDC" );
    }
    catch ( std::bad_alloc& e ) {
        throw GeneralException( "Fitter::plotFitResults",
                "Got std::bad_alloc when creating new TPaveText" );
    }
    pv->SetName( m_paramBoxName );
    pv->SetFillColor( 0 );
    pv->SetBorderSize( 0 );
    pv->SetTextAlign( m_paramBoxTextAlign );
    pv->SetTextSize( m_paramBoxTextSize );
    pv->SetFillStyle( 4001 );


    // add parameter box
    TIterator *pIter = params->createIterator();
    RooAbsReal *pvar = 0;
    while ( (pvar=dynamic_cast<RooAbsReal*>( pIter->Next() ) ) ) {

        assert( pvar );
        // swap name and title if title is specified, 
        // else use the original name
        const char* ptitle="";
        if ( pvar->GetTitle() != 0 && strcmp( pvar->GetTitle(), "" ) != 0 ) {
            ptitle=pvar->GetTitle();
        }
        else {
            ptitle = pvar->GetName();
        }

        RooAbsReal* pvarTmp = dynamic_cast<RooAbsReal*>( pvar->Clone( ptitle ) );
        assert( pvarTmp );

        TString *formatted = this->format( pvarTmp, rfres, 1, "NEPLU" ) ;
        //TString *formatted=pvarTmp->format(1, "NEPLU");
        pv->AddText( formatted->Data() );

        delete formatted; formatted=0;
        delete pvarTmp; pvarTmp=0;
    }
    if ( range && strcmp( range, "" ) != 0 ) {
        //        TIterator* it = yields.createIterator();
        RooAbsPdf* pdfComp=0;
        RooRealVar* yield=0;
        RooRealVar *fracInRange=0;
        RooRealVar *yieldInRange=0;
        TString yieldName="";
        //        TString yieldTitle="";
        for ( Int_t i=0; i < pdfList.getSize(); ++i ) {
            yield = dynamic_cast<RooRealVar*>( yieldList.at( i ) );
            pdfComp = dynamic_cast<RooAbsPdf*>( pdfList.at( i ) );
            assert( yield );
            assert( pdfComp );
            fracInRange = dynamic_cast<RooRealVar*>( pdfComp->createIntegral(
                        *observables,
                        RooFit::NormSet(*observables),
                        RooFit::Range(range) ) );
            assert( fracInRange );
            // yieldName.Form("%s_inRange", yield->GetName());
            if ( !rangeTitle || strcmp( rangeTitle, "" ) == 0 ) {
                yieldName.Form( "%s (in '%s' range)", yield->GetTitle(),
                        range );
            }
            else {
                yieldName.Form( "%s (%s)", yield->GetTitle(),
                        rangeTitle );
            }
            try {
                yieldInRange = new RooRealVar( yieldName.Data(), ""
                        , 0, rds->numEntries() );
            }
            catch (std::bad_alloc& e) {
                std::stringstream msg;
                msg << "Got std::bad_alloc when creating new RooRealVar "
                    << yieldName;
                throw GeneralException("Fitter::plotFitResults",
                        msg.str());
            }
            yieldInRange->setVal( fracInRange->getVal() * yield->getVal() );
            yieldInRange->setError( fracInRange->getVal() * yield->getError() );
            TString *formatted = yieldInRange->format( 1, "NEPLU" );
            pv->AddText( formatted->Data() );

            delete formatted; formatted=0;
            delete yieldInRange; yieldInRange=0;
            delete fracInRange; fracInRange=0;
        }
    }

    delete pIter; pIter = 0;

    // rpnow takes ownership of pv
    rp->addObject(pv);

    return rp;
}


//=============================================================================
//add a gaussian constraint on varname to the list of constraints that will 
//be applied to the model in the fit function. 
//=============================================================================
void Fitter::addGaussianConstraint( const char* varname,
        double value,
        double sigma,
        double extend_sig )
{

    //checking that the var we are constraining is there
    RooAbsReal* var = dynamic_cast<RooAbsReal*>( m_rws->obj( varname ) );
    if( !var ) {
        throw WSRetrievalFailure( "Fitter::addGaussianConstraint",
                *m_rws, varname, "RooAbsReal" );
    }

    // will have a range that may need extending, if variable is a RooRealVar
    if( std::string( var->ClassName() ) == "RooRealVar" ) { 

        RooRealVar* realvar = m_rws->var( varname );
        if( !realvar ) {
            throw WSRetrievalFailure( "Fitter::addGaussianConstraint",
                    *m_rws, varname, "RooRealVar" );
        }
        //   Idea is to extend the range of the fit i
        // Check that the value of the variable is within the contraint value and errors
        bool in_range_lower = ( value > realvar->getMin() ) ;
        bool in_range_upper = ( value < realvar->getMax() );

        // set range to be 100 sigma of the constraint value, given constraints apply a prior
        // we should know this in advance to be reasonable.
        if (!in_range_lower) { // need to extend the minimum range
            realvar->setMin( value - extend_sig * sigma ) ;
        }
        if(!in_range_upper) { // need to extend the maximum range
            realvar->setMax( value + extend_sig * sigma );
        }
        // If Gaussian constrained the variable needs to be able to float
        realvar->setConstant( kFALSE );
        realvar->setVal( value );
    }
    // If the variable is already Gaussian-constrained, we just need to modify the error.
    if (m_rws->pdf((std::string(varname)+"_gaussconstraint").c_str()) != NULL)
    {
        this->setParameterValue((std::string(varname)+"_gaussconstraint_mean").c_str(),value,true);
        this->setParameterValue((std::string(varname)+"_gaussconstraint_sigma").c_str(),sigma,true);
        std::cout << "Fitter::addGaussianConstraint - changing the constraints on variable " 
            <<  varname << ": (" << value << "," << sigma << ") -> ("
            << this->getParameterValue((std::string(varname)+"_gaussconstraint_mean" ).c_str()) << " "
            << this->getParameterValue((std::string(varname)+"_gaussconstraint_sigma").c_str()) << ")"
            << std::endl;
    }
    else
    {
        // make the gaussian constraint
        std::stringstream theName;
        theName << varname << "_gaussconstraint";
        RooRealVar mean((theName.str()+"_mean").c_str(),"",value);
        RooRealVar sig((theName.str()+"_sigma").c_str(),"",sigma);
        RooGaussian fconstraint( theName.str().c_str(), "", *var, mean, sig);

        //import it
        if ( m_rws->import( fconstraint, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
            throw WSImportFailure( "Fitter::addGaussianConstraint",
                    *m_rws, fconstraint );
        }

        std::cout << "Fitter::addGaussianConstraint - constraining variable " <<  varname << " (" << 
            value << "," << sigma << ")."<< std::endl;
        //check if there is a set of constraints already in the workspace
        const RooArgSet* set = m_rws->set( m_ConstraintSetName );
        if ( !set ) {
            //if there isn't, make one.
            m_rws->defineSet( m_ConstraintSetName, theName.str().c_str() );
        }
        else {
            //if there is, add this constraint to the set
            m_rws->extendSet( m_ConstraintSetName, theName.str().c_str() );
        }
    }
}


//=============================================================================
// resets all constraints to default values, removing anything cached 
//=============================================================================
void Fitter::resetGaussianConstraints() 
{

    if ( !m_rws ) {
        throw GeneralException( "Fitter::resetGaussianConstraints",
                "No RooWorkspace object is defined!" );
    }

    // get the list of constraint pdfs. At present these are all Gaussian 
    // constraints.
    const RooArgSet* theConstraints = m_rws->set( this->getConstraintString() );
    if( !theConstraints ) {
        std::cerr << "Fitter::resetConstraints -- No constraint pdfs have been set." << std::endl;
        return;
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure( "Fitter::resetGaussianConstraints",
                *m_rws, m_dataSetName, "RooDataSet" );
    }

    TIterator* iter = theConstraints->createIterator();
    RooAbsPdf* pdf = 0;
    double value(0.),sigma(0.);
    while((pdf = dynamic_cast<RooGaussian*>(iter->Next()))) {
        TString name = pdf->GetName();
        name.ReplaceAll("_gaussconstraint","");		
        std::cout << "Fitter::resetGaussianConstraints - resetting constraint for variable " <<  name << std::endl;
        value = this->getParameterValue((name+"_gaussconstraint_mean").Data());
        sigma = this->getParameterValue((name+"_gaussconstraint_sigma").Data());
        this->addGaussianConstraint( name, value, sigma );
    }
    delete iter; iter=0;
}

//-----------------------------------------------------------------------------
// Plot the specified variable with name 'name'
// NB. The variable must exist in the dataset
//
// If a range is specified, then the variable is plotted over this range.
// This function will raise an exception is the range does not exist
//
// If sumWErrors is true, then plot sum-of-weights-squared errors (default is
// Poissonian errors). RooFit will force sum-of-weights-squared errors if
// the dataset is weighted.
//
// If a RooPlot pointer is given as argument, then the variable is plotted
// on the existing RooPlot
//
// If scale is >0, then the plot will be rescaled by the specified amount
//
// If newname is set, then the dataset is renamed in the RooPlot.
// This is useful if several datasets need to be plotted on the same RooPlot
//
// If ymin/ymax is >0, then the minimum/maximum of the plot is set to
// this value, overriding RooPlot's default values
//-----------------------------------------------------------------------------
RooPlot* Fitter::plotVariable( const char* name, const char* cut,
        const char* range,
        Bool_t sumW2Errors, RooPlot* frame,
        Double_t scale, const char* newname,
        Double_t ymin, Double_t ymax )
{
    if ( !m_rws ) {
        throw GeneralException( "Fitter::plotVariable",
                "No RooWorkspace object is defined!" );
    }
    // check that name is specified
    if ( !name || strcmp( name, "" ) == 0 ) {
        throw GeneralException( "Fitter::plotVariable",
                "No variable name has been specified!" );
    }

    const RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "Fitter::plotVariable",
                *m_rws, name, "RooRealVar" );
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure( "Fitter::plotVariable",
                *m_rws, m_dataSetName, "RooDataSet" );
    }
    Int_t nPlotBins = getPlotBinsInt( name );

    // get the RooPlot object
    RooPlot* rp = 0;

    if ( !frame ) {
        rp = var->frame( RooFit::Bins( nPlotBins ), RooFit::Range( range ) );
        if ( !rp ) {
            std::stringstream msg;
            msg << "Failed to get RooPlot for RooRealVar " << var->GetName();
            throw GeneralException("Fitter::plotVariable", msg.str() );
        }
        if ( strcmp( var->GetTitle(), "" ) == 0 ) {
            rp->GetXaxis()->SetTitle( TString::Format("%s %s", var->GetName(),
                        rp->GetXaxis()->GetTitle() ) );
        }
    }
    else {
        rp = frame;
    }

    RooAbsData::ErrorType errorType = (!sumW2Errors)?RooAbsData::Poisson
        :RooAbsData::SumW2;

    if (scale<0) {
        scale = 0;
    }

    RooLinkedList argList;
    RooCmdArg* arg = 0;

    arg = new RooCmdArg( RooFit::LineColor( m_dataSetLineColor ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::LineStyle( m_dataSetLineStyle ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::LineWidth( m_dataSetLineWidth ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::MarkerColor( m_dataSetMarkerColor ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::MarkerStyle( m_dataSetMarkerStyle ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::MarkerSize( m_dataSetMarkerSize ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::FillColor( m_dataSetFillColor ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::FillStyle( m_dataSetFillStyle ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::DrawOption( m_dataSetDrawOption ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    arg = new RooCmdArg( RooFit::DataError( errorType ) );
    argList.Add( arg->Clone() );
    delete arg; arg=0;

    if ( scale!=0 ) {
        arg = new RooCmdArg( RooFit::Rescale( scale ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }

    if ( strcmp( newname, "" ) !=0 ) {
        arg = new RooCmdArg( RooFit::Name( newname ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }
    if ( strcmp( cut, "" ) != 0 ) {
        arg = new RooCmdArg( RooFit::Cut( cut ) );
        argList.Add( arg->Clone() );
        delete arg; arg=0;
    }

    rds->plotOn( rp, argList );
    rp->SetMaximum( rp->GetMaximum() ); //why do this? surely this is by default...

    if ( scale != 0 ) {
        rp->SetMaximum( rp->GetMaximum() * scale );
        rp->SetMinimum( rp->GetMinimum() * scale );
    }

    if ( ymax != 0 ) {
        rp->SetMaximum( ymax );
    }
    if (ymin!=0) {
        rp->SetMinimum( ymin );
    }

    return rp;
}

//-----------------------------------------------------------------------------
RooPlot* Fitter::plotLikelihoodScan( const char* name,
        const char* fitName,
        const char* range,
        Color_t pllColor,
        Bool_t plotProfileLL )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::plotLikelihoodScan",
                "No RooWorkspace object is defined!" );
    }
    // check that name is specified
    if ( !name || strcmp( name, "" ) == 0 ) {
        throw GeneralException( "Fitter::plotLikelihoodScan",
                "No variable name has been specified!" );
    }

    const RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "Fitter::plotLikelihoodScan",
                *m_rws, name, "RooRealVar" );
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if ( !rds ) {
        throw WSRetrievalFailure( "Fitter::plotLikelihoodScan",
                *m_rws, m_dataSetName, "RooDataSet" );
    }

    RooAddPdf* model = dynamic_cast<RooAddPdf*>( m_rws->pdf( m_modelName ) );
    if (!model) {
        throw WSRetrievalFailure( "Fitter::plotLikelihoodScan",
                *m_rws, m_modelName, "RooAbsPdf" );
    }

    // check that the variable is a parameter in the model PDF
    const RooArgSet* params = model->getParameters(*rds);
    assert( params );
    if ( !params->contains( *var ) )
    {
        std::stringstream msg;
        msg << var->GetName() << " not a parameter of the model PDF "
            << model->GetName();
        throw GeneralException( "Fitter::plotLikelihoodScan",
                msg.str() );
    }

    if ( fitName && strcmp( fitName, "" ) != 0 ) {
        if ( !m_rws->loadSnapshot( fitName ) ) {
            throw WSRetrievalFailure( "Fitter::plotLikelihoodScan"
                    ,*m_rws, fitName, "fit snapshot" );
        }
    }

    const RooArgSet* theConstraints = m_rws->set( m_ConstraintSetName );

    // NLL
    RooAbsReal* nll = model->createNLL( *rds, 
            RooFit::NumCPU( m_nCores ),
            RooFit::Extended( kTRUE ), 
            RooFit::Verbose( kFALSE ), 
            RooFit::ExternalConstraints( *theConstraints ) 
            );

    // minimise likelikood w.r.t. all parameters before making plots
    RooMinuit tminuit( *nll );
    tminuit.setPrintLevel( -1 );
    tminuit.setNoWarn();
    tminuit.migrad();
    tminuit.hesse();

    TString title   = TString::Format( "(Profile) Log likelihood for %s ", name );
    Int_t nPlotBins = getPlotBinsInt( name );

    // get the RooPlot object
    RooPlot* rp = var->frame( RooFit::Bins( nPlotBins ), RooFit::Range( range ),
            RooFit::Title( title ) );
    if (!rp) {
        std::stringstream msg;
        msg << "Failed to get RooPlot for RooRealVar " << name;
        throw GeneralException( "Fitter::plotProfileLikelihood",
                msg.str() );
    }
    if ( plotProfileLL ) {
        RooArgSet vars( *var );
        RooAbsReal* pll = nll->createProfile( vars );
        pll->plotOn( rp, RooFit::LineColor( pllColor ), RooFit::ShiftToZero() );
    }

    loadSnapshot( fitName ); // reload the fitResult.
    return rp;
}

//-----------------------------------------------------------------------------
// create the named set "Plot Parameters" (or name set by the
// setPlotParameterSetName method) with contents from the colon-separated list
// contentList. This is used to indicate what variables should be plotted.
// If this set does not exist in the workspace, then all parameters in the
// pdf are plotted
//-----------------------------------------------------------------------------
void Fitter::setPlotParameters( const char* contentList )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::setPlotParameters",
                "No RooWorkspace object is defined." );
    }

    std::string content_list( contentList );
    m_stringHelper.replaceAll( content_list, " ", "" ); // remove all whitespaces

    if ( m_rws->defineSet( m_plotParamsSetName, content_list.c_str() ) )
    {
        throw WSImportFailure( "Fitter::setPlotParameters",
                *m_rws, m_plotParamsSetName, content_list, kTRUE );
    }
}

//-----------------------------------------------------------------------------
// Add the parameter paramName to the named set "Plot Parameters"
// (or name set by the setPlotParameterSetName method)
// This is used to indicate what variables should be plotted.
// If this set does not exist in the workspace, then all parameters
// in the pdf are plotted
//-----------------------------------------------------------------------------
void Fitter::addPlotParameter( const char* paramName )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::addPlotParameter",
                "No RooWorkspace object is defined!" );
    }

    if ( !paramName || strcmp( paramName, "" ) == 0 ) {
        throw GeneralException( "Fitter::addPlotParameter",
                "No fit name given" );
    }
    if ( m_rws->extendSet( m_plotParamsSetName, paramName ) ) {
        throw WSImportFailure("Fitter::addPlotParameter",
                *m_rws, m_plotParamsSetName, paramName, kFALSE );
    }
}

//-----------------------------------------------------------------------------
// Load the snapshot of the fit parameters given by name fitName
// Will raise an exception if the fit name does not exist in the
// workspace
//-----------------------------------------------------------------------------
void Fitter::loadSnapshot( const char* fitName )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::loadSnapshot",
                "No RooWorkspace object is defined!" );
    }

    if ( !fitName || strcmp( fitName, "" ) == 0 ) {
        throw GeneralException( "Fitter::loadSnapshot",
                "No fit name given" );
    }

    if ( !m_rws->loadSnapshot( fitName ) ) {
        throw WSRetrievalFailure( "Fitter::loadSnapshot",
                *m_rws, fitName, "fit snapshot" );
    }
}

//-----------------------------------------------------------------------------
void Fitter::setRange(const char* name, Float_t min, Float_t max,
        const char* range) 
{
    if (!m_rws) {
        throw GeneralException( "Fitter::setRange",
                "No RooWorkspace object is defined!" );
    }

    if ( !name || strcmp( name, "" ) == 0 ) {
        throw GeneralException( "Fitter::setRange",
                "No variable name given" );
    }

    RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "Fitter::setRange", *m_rws,
                name, "RooRealVar" );
    }

    var->setRange( range, min, max );
}

//-----------------------------------------------------------------------------
// Add the plot component "name" to the list of PDF components to plot
// NB: there is no check that the PDF component exists in the RooWorkspace
//-----------------------------------------------------------------------------
void Fitter::addPdfAttributes(const char* name, Color_t lineCol,
        Style_t lineStyle, Width_t lineWidth)
{
    if ( std::find( m_pdfComponents.begin(),
                m_pdfComponents.end(), name ) != m_pdfComponents.end() ) {
        std::stringstream msg;
        msg << "PDF component " << name << " is already in the list of "
            << "components to plot";
        throw GeneralException("Fitter::addPdfComponent", msg.str() );
    }
    assert( m_pdfLineColorMap.find( name ) == m_pdfLineColorMap.end() );
    assert( m_pdfLineStyleMap.find( name ) == m_pdfLineStyleMap.end() );
    assert( m_pdfLineWidthMap.find( name ) == m_pdfLineWidthMap.end() );

    m_pdfComponents.push_back( name );
    m_pdfLineColorMap[ name ] = lineCol;
    m_pdfLineStyleMap[ name ] = lineStyle;
    m_pdfLineWidthMap[ name ] = lineWidth;
}

//-----------------------------------------------------------------------------
// set the line color, style and width of the specified PDF component
// Will raise an exception if it is not in the list of components
//-----------------------------------------------------------------------------
void Fitter::setPdfComponentLineColor(const char* name, Color_t col)
{
    if ( std::find( m_pdfComponents.begin(),
                m_pdfComponents.end(), name ) == m_pdfComponents.end() ) {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
            << "components to plot";
        throw GeneralException( "Fitter::setPdfComponentLineColor",
                msg.str() );
    }
    assert( m_pdfLineColorMap.find( name ) != m_pdfLineColorMap.end() );
    m_pdfLineColorMap[ name ] = col;
}

//-----------------------------------------------------------------------------
void Fitter::setPdfComponentLineStyle( const char* name, Style_t style)
{
    if (std::find( m_pdfComponents.begin(),
                m_pdfComponents.end(), name ) == m_pdfComponents.end() ) {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
            << "components to plot";
        throw GeneralException( "Fitter::setPdfComponentLineStyle",
                msg.str() );
    }
    assert( m_pdfLineStyleMap.find( name ) != m_pdfLineStyleMap.end() );
    m_pdfLineStyleMap[ name ] = style;
}

//-----------------------------------------------------------------------------
void Fitter::setPdfComponentLineWidth( const char* name, Width_t width )
{
    if ( std::find( m_pdfComponents.begin(),
                m_pdfComponents.end(), name ) == m_pdfComponents.end() ) {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
            << "components to plot";
        throw GeneralException( "Fitter::setPdfComponentLineWidth",
                msg.str() );
    }
    assert( m_pdfLineWidthMap.find( name ) != m_pdfLineWidthMap.end() );
    m_pdfLineWidthMap[ name ] = width;
}


//-----------------------------------------------------------------------------
void Fitter::setPdfComponentLineAttributes( const char* name, Color_t col,	
        Style_t style, Width_t width )
{
    if ( std::find( m_pdfComponents.begin(),
                m_pdfComponents.end(), name ) == m_pdfComponents.end() )
    {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
            << "components to plot";
        throw GeneralException( "Fitter::setPdfComponentLineAttributes",
                msg.str() );
    }
    assert( m_pdfLineColorMap.find( name ) != m_pdfLineColorMap.end() );
    assert( m_pdfLineStyleMap.find( name ) != m_pdfLineStyleMap.end() );
    assert( m_pdfLineWidthMap.find( name ) != m_pdfLineWidthMap.end() );
    m_pdfLineColorMap[ name ] = col;
    m_pdfLineStyleMap[ name ] = style;
    m_pdfLineWidthMap[ name ] = width;
}

//-----------------------------------------------------------------------------
// plot all model sub-components
//-----------------------------------------------------------------------------

void Fitter::setPlotSubComponents(bool plotSubComponents)
{
    m_plotSubComponents = plotSubComponents;
}

//-----------------------------------------------------------------------------
// Remove the plot component "name" from the list of PDF components to plot
// Will raise an exception if it is not in the list of components
//-----------------------------------------------------------------------------
void Fitter::removePdfComponent( const char* name )
{
    if ( std::find( m_pdfComponents.begin(),
                m_pdfComponents.end(), name ) == m_pdfComponents.end() ) {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
            << "components to plot";
        throw GeneralException( "Fitter::setPdfComponentLineAttributes",
                msg.str() );
    }
    assert( m_pdfLineColorMap.find( name ) != m_pdfLineColorMap.end());
    assert( m_pdfLineStyleMap.find( name ) != m_pdfLineStyleMap.end());
    assert( m_pdfLineWidthMap.find( name ) != m_pdfLineWidthMap.end());
    m_pdfLineColorMap.erase( name );
    m_pdfLineStyleMap.erase( name );
    m_pdfLineWidthMap.erase( name );
    std::vector<std::string>::iterator it = std::find( m_pdfComponents.begin(),
            m_pdfComponents.end(),
            name );
    m_pdfComponents.erase( it );
}

//-----------------------------------------------------------------------------
// Clear the list of PDF components to plot
//-----------------------------------------------------------------------------
void Fitter::clearPdfComponents()
{
    m_pdfComponents.clear();
    m_pdfLineColorMap.clear();
    m_pdfLineStyleMap.clear();
    m_pdfLineWidthMap.clear();
}

//-----------------------------------------------------------------------------
// set name of the category.
//-----------------------------------------------------------------------------
void Fitter::setCategoryName(const char* name)
{
    m_catSetName=name;
}


//-----------------------------------------------------------------------------
// set name of the category.
//-----------------------------------------------------------------------------
const char* Fitter::getCategoryName( ) const
{
    return m_catSetName;
}



//-----------------------------------------------------------------------------
// set name of the model PDF (NB. the model must be a RooAbsPdf instance,
// or inherit from it)
//-----------------------------------------------------------------------------
void Fitter::setModelName(const char* name)
{
    m_modelName=name;
}

//-----------------------------------------------------------------------------
// set the dataset name (NB. the data set must be unbinned)
//-----------------------------------------------------------------------------
void Fitter::setDataSetName(const char* name)
{
    m_dataSetName=name;
}

//-----------------------------------------------------------------------------
// set the name of the named set containing the sWeight variables
//-----------------------------------------------------------------------------
void Fitter::setSWeightSetName(const char* name)
{
    m_sWeightVarSetName=name;
}

//-----------------------------------------------------------------------------
// set the name of the named set containing the plot parameters
//-----------------------------------------------------------------------------
void Fitter::setPlotParameterSetName(const char* name)
{
    m_plotParamsSetName=name;
}

//-----------------------------------------------------------------------------
// set the line attributes of the model PDF
//-----------------------------------------------------------------------------
void Fitter::setModelLineColor(Color_t col)
{
    m_modelLineColor=col;
}

//-----------------------------------------------------------------------------
void Fitter::setModelLineStyle(Style_t style)
{
    m_modelLineStyle=style;
}

//-----------------------------------------------------------------------------
void Fitter::setModelLineWidth(Width_t width)
{
    m_modelLineWidth=width;
}

//-----------------------------------------------------------------------------
void Fitter::setModelLineAttributes(Color_t col, Style_t style,
        Width_t width)
{
    m_modelLineColor=col;
    m_modelLineStyle=style;
    m_modelLineWidth=width;
}

//-----------------------------------------------------------------------------
// set the dataset line attributes
//-----------------------------------------------------------------------------
void Fitter::setDataSetLineColor(Color_t col)
{
    m_dataSetLineColor=col;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetLineStyle(Style_t style)
{
    m_dataSetLineStyle=style;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetLineWidth(Width_t width)
{
    m_dataSetLineWidth=width;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetLineAttributes(Color_t col,
        Style_t style, Width_t width)
{
    m_dataSetLineColor=col;
    m_dataSetLineStyle=style;
    m_dataSetLineWidth=width;
}

//-----------------------------------------------------------------------------
// set the dataset marker attributes
//-----------------------------------------------------------------------------
void Fitter::setDataSetMarkerColor(Color_t col)
{
    m_dataSetMarkerColor=col;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetMarkerStyle(Style_t style)
{
    m_dataSetMarkerStyle=style;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetMarkerSize(Size_t size)
{
    m_dataSetMarkerSize=size;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetMarkerAttributes(Color_t col,
        Style_t style, Size_t size)
{
    m_dataSetMarkerColor=col;
    m_dataSetMarkerStyle=style;
    m_dataSetMarkerSize=size;
}

//-----------------------------------------------------------------------------
// set the dataset fill attributes
//-----------------------------------------------------------------------------
void Fitter::setDataSetFillColor(Color_t col)
{
    m_dataSetFillColor=col;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetFillStyle(Style_t style)
{
    m_dataSetFillStyle=style;
}

//-----------------------------------------------------------------------------
void Fitter::setDataSetFillAttributes(Color_t col,
        Style_t style)
{
    m_dataSetFillColor=col;
    m_dataSetFillStyle=style;
}

//-----------------------------------------------------------------------------
// set the dataset draw options (see TGraphPainter for details)
//-----------------------------------------------------------------------------
void Fitter::setDataSetDrawOption(const char* opt)
{
    m_dataSetDrawOption=opt;
}

//-----------------------------------------------------------------------------
// set the parameter box attributes
//-----------------------------------------------------------------------------
void Fitter::setParamBoxX1(Float_t x)
{
    if (x>1||x<0) {
        std::stringstream msg;
        msg << "New value for parameter box X1 (" 
            << x << ") is out of range";
        throw GeneralException("Fitter::setParamBoxX1",
                msg.str());
    }
    if (x>m_paramBoxX2) {
        std::stringstream msg;
        msg << "New value for parameter box X1 (" 
            << x << ") greater than parameter box X2 ("
            << m_paramBoxX2 << ")";
        throw GeneralException("Fitter::setParamBoxX1",
                msg.str());
    }
    m_paramBoxX1=x;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxX2(Float_t x)
{
    if (x>1||x<0) {
        std::stringstream msg;
        msg << "New value for parameter box X2 (" 
            << x << ") is out of range";
        throw GeneralException("Fitter::setParamBoxX2",
                msg.str());
    }
    if (x<m_paramBoxX1) {
        std::stringstream msg;
        msg << "New value for parameter box X2 (" 
            << x << ") less than parameter box X1 ("
            << m_paramBoxX1 << ")";
        throw GeneralException("Fitter::setParamBoxX2",
                msg.str());
    }
    m_paramBoxX2=x;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxY1(Float_t x)
{
    if (x>1||x<0) {
        std::stringstream msg;
        msg << "New value for parameter box Y1 (" 
            << x << ") is out of range";
        throw GeneralException("Fitter::setParamBoxY1",
                msg.str());
    }
    if (x>m_paramBoxX2) {
        std::stringstream msg;
        msg << "New value for parameter box Y1 (" 
            << x << ") greater than parameter box Y2 ("
            << m_paramBoxY2 << ")";
        throw GeneralException("Fitter::setParamBoxY1",
                msg.str());
    }
    m_paramBoxY1=x;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxY2(Float_t x)
{
    if (x>1||x<0) {
        std::stringstream msg;
        msg << "New value for parameter box Y2 (" 
            << x << ") is out of range";
        throw GeneralException("Fitter::setParamBoxY2",
                msg.str());
    }
    if (x<m_paramBoxY1) {
        std::stringstream msg;
        msg << "New value for parameter box Y2 (" 
            << x << ") less than parameter box Y1 ("
            << m_paramBoxY1 << ")";
        throw GeneralException("Fitter::setParamBoxY2",
                msg.str());
    }
    m_paramBoxY2=x;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxTextSize(Float_t size)
{
    m_paramBoxTextSize=size;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxTextAlign(Int_t align)
{
    m_paramBoxTextAlign=align;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxName(const char* name)
{
    m_paramBoxName=name;
}

//-----------------------------------------------------------------------------
void Fitter::setParamBoxAttributes(const char* name,
        Float_t x1, Float_t y1,
        Float_t x2, Float_t y2,
        Float_t textSize, Int_t textAlign)
{
    m_paramBoxX1=x1;
    m_paramBoxX2=x2;
    m_paramBoxY1=y1;
    m_paramBoxY2=y2;
    m_paramBoxTextSize=textSize;
    m_paramBoxTextAlign=textAlign;
    m_paramBoxName=name;
}

//-----------------------------------------------------------------------------
// Set the number of global bins to use in subsequent plots
//-----------------------------------------------------------------------------
void Fitter::setPlotBins(Int_t nBins)
{
    m_globalPlotBins=nBins;
}

//-----------------------------------------------------------------------------
// Set the number of bins to use in subsequent plots for the given variable
// this will override the number of global bins
//-----------------------------------------------------------------------------
void Fitter::setPlotBins(const char* name, Int_t nBins)
{
    m_plotBinMap[name]=nBins;
}

//-----------------------------------------------------------------------------
// Set the default number of bins for a given RooRealVar
// Optionally, set the number of bins for a given named range
// If you want to set asymmetric bins, then you should manipulate 
// the RooRealVar object directly using the GetVar method
// Will raise an exception if the requested variable does not exist in the
// workspace
//-----------------------------------------------------------------------------
void Fitter::setBins(const char* name, Int_t nBins, 
        const char* range) 
{
    if (!m_rws) {
        throw GeneralException( "Fitter::setBins",
                "No RooWorkspace object is defined!" );
    }
    RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "Fitter::setBins",
                *m_rws, name, "RooRealVar" );
    }
    var->setBins( nBins, range );
}

//-----------------------------------------------------------------------------
// get the yield in a given range
//-----------------------------------------------------------------------------
RooRealVar* Fitter::getYield( const char* name, const char* range,
        const char* fitName, Bool_t returnClone ) const
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getYield",
                "No RooWorkspace object is defined!" );
    }

    if ( fitName && strcmp( fitName, "" ) != 0 ) {
        if ( !m_rws->loadSnapshot( fitName ) ) {
            throw WSRetrievalFailure( "Fitter::getYield",
                    *m_rws, fitName, "fit snapshot" );
        } 
    }

    // get the model PDF
    RooAddPdf* model = dynamic_cast<RooAddPdf*>( m_rws->pdf( m_modelName ) );
    if (!model) {
        throw WSRetrievalFailure( "Fitter::getYield",
                *m_rws, m_modelName, "RooAbsPdf" );
    }  

    RooDataSet *rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure( "Fitter::getYield",
                *m_rws, m_dataSetName, "RooDataSet" );
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds );
    assert( observables );

    const RooArgList& yieldList = model->coefList();
    const RooArgList& pdfList = model->pdfList();

    const RooRealVar* yield = dynamic_cast<RooRealVar*>( yieldList.find( name ) );
    if ( !yield ) {
        std::stringstream msg;
        msg << "Failed to get yield name " << name << " from the list of yields";
        throw GeneralException( "Fitter::getYield", msg.str() );
    }

    if ( !range && strcmp( range, "" ) == 0 ) {
        if ( returnClone ) {
            return dynamic_cast<RooRealVar*>( yield->Clone() );
        } else {
            return dynamic_cast<RooRealVar*>( yieldList.find( name ) );
        }
    }

    const RooAbsPdf* pdf = dynamic_cast<RooAbsPdf*>( pdfList.at( yieldList.index( yield ) ) );
    if ( !pdf ) {
        std::stringstream msg;
        msg << "Failed to get PDF component corresponding to yield " << name 
            << " from the list of PDFs";
        throw GeneralException( "Fitter::getYield", msg.str() );
    }

    RooRealVar* fracInRange = dynamic_cast<RooRealVar*>( pdf->createIntegral( 
                *observables, RooFit::NormSet( *observables ), 
                RooFit::Range( range ) )
            );
    assert( fracInRange );

    RooRealVar* yieldInRange = new RooRealVar( TString::Format( "%s_%s", name, range ).Data(),
            yield->GetTitle(), 0, rds->numEntries() );
    yieldInRange->setVal( fracInRange->getVal() * yield->getVal() );
    yieldInRange->setError( fracInRange->getVal() * yield->getError() );

    return yieldInRange;

}

//-----------------------------------------------------------------------------
// get the currently attached workspace
//-----------------------------------------------------------------------------
const RooWorkspace* Fitter::getWS() const {
    return m_rws;
}

//-----------------------------------------------------------------------------
RooWorkspace* Fitter::getWS() { // mutator version
    return m_rws;
}


//-----------------------------------------------------------------------------
// get a variable from the workspace by name
//-----------------------------------------------------------------------------
const RooRealVar* Fitter::getVar(const char* name) const {

    if ( !m_rws ) {
        throw GeneralException( "Fitter::getVar",
                "No RooWorkspace object is defined!" );
    }
    const RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "Fitter::getVar",
                *m_rws, name, "RooRealVar" );
    }
    return var;
}

//-----------------------------------------------------------------------------
RooRealVar* Fitter::getVar( const char* name )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getVar",
                "No RooWorkspace object is defined!" );
    }

    RooRealVar* var = m_rws->var(name);
    if (!var) {
        throw WSRetrievalFailure( "Fitter::getVar",
                *m_rws, name, "RooRealVar" );
    }

    return var;
}


//-----------------------------------------------------------------------------
// get a dataset from the workspace by name
/*  OLD VERSION, NEW VERSION RETURNS THE ACTUAL RooDataSet*
//-----------------------------------------------------------------------------
const RooAbsData* Fitter::getDataSet(const char* name) const
{
if ( !m_rws )
{
throw GeneralException("Fitter::getDataSet",
"No RooWorkspace object is defined!");
}
const RooAbsData* rws = dynamic_cast< RooAbsData*>( m_rws->data( name ) );
if ( !rws )
{
throw WSRetrievalFailure("Fitter::getDataSet",
 *m_rws, name, "RooAbsData");
 }
 return rws;
 }


//-----------------------------------------------------------------------------
// get a dataset from the workspace by name
//-----------------------------------------------------------------------------
RooAbsData* Fitter::getDataSet(const char* name)
{
if (!m_rws)
{
throw GeneralException("Fitter::getDataSet",
"No RooWorkspace object is defined!");
}
RooAbsData* rws = m_rws->data(name);
if (!rws)
{
throw WSRetrievalFailure("Fitter::getDataSet",
 *m_rws, name, "RooAbsData");
 }
 return rws;
 }
*/

//-----------------------------------------------------------------------------
// Gets the dataset out of the rooworkspace with the given name
// Raises an exception if not found.
// Caller is responsible for deletion.
//-----------------------------------------------------------------------------
RooDataSet* Fitter::getDataSet( const char* name )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getDataSet",
                "No RooWorkspace object is defined." );
    }

    RooDataSet* theData = dynamic_cast<RooDataSet*>( m_rws->data( name ) );
    if ( !theData ) {
        throw WSRetrievalFailure( "Fitter::getDataSet",
                *m_rws, name, "RooAbsData" );
    }
    return theData;
}


//-----------------------------------------------------------------------------
// Gets the dataset out of the rooworkspace with the given name
// Raises an exception if not found.
// Caller is responsible for deletion.
//-----------------------------------------------------------------------------
const RooDataSet* Fitter::getDataSet( const char* name ) const
{
    if ( !m_rws ) {
        throw GeneralException( "Fitter::getDataSet",
                "No RooWorkspace object is defined." );
    }
    const RooDataSet* theData = dynamic_cast<RooDataSet*>( m_rws->data( name ) );
    if ( !theData ) {
        throw WSRetrievalFailure( "Fitter::getDataSet",
                *m_rws, name, "RooAbsData" );
    }
    return theData;
}


//-----------------------------------------------------------------------------
// get the RooDataSet with the name given by GetDataSetName()
//-----------------------------------------------------------------------------
const RooDataSet* Fitter::getDataSet() const
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getDataSet",
                "No RooWorkspace object is defined!" );
    }
    const RooDataSet* rws = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if ( !rws )
    {
        throw WSRetrievalFailure( "Fitter::getDataSet",
                *m_rws, m_dataSetName , "RooDataSet" );
    }
    return rws;
}

//-----------------------------------------------------------------------------
RooDataSet* Fitter::getDataSet()
{
    if ( !m_rws ) {
        throw GeneralException( "Fitter::getDataSet",
                "No RooWorkspace object is defined!" );
    }

    RooDataSet* rws = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if ( !rws ) {
        throw WSRetrievalFailure( "Fitter::getDataSet",
                *m_rws, m_dataSetName, "RooDataSet" );
    }
    return rws;
}


//-----------------------------------------------------------------------------
// get the PDF with the name given by getModelName()
//-----------------------------------------------------------------------------
const RooAbsPdf* Fitter::getModel() const
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getModel",
                "No RooWorkspace object is defined!" );
    }
    const RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );
    if ( !model ) {
        throw WSRetrievalFailure( "Fitter::getModel",
                *m_rws, m_modelName, "RooAbsPdf" );
    }
    return model;
}

//-----------------------------------------------------------------------------
RooAbsPdf* Fitter::getModel()
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getModel",
                "No RooWorkspace object is defined!" );
    }
    RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );
    if (!model)
    {
        throw WSRetrievalFailure( "Fitter::getModel",
                *m_rws, m_modelName, "RooAbsPdf" );
    }
    return model;
}


//-----------------------------------------------------------------------------
// get a RooAbsPdf from the workspace and float all the parameters
//-----------------------------------------------------------------------------
void Fitter::floatAllParams( const char* pdfName ) 
{
    RooAbsPdf* model = 0;

    if( !pdfName || strcmp( pdfName, "" ) == 0 ) {
        std::cout << "Fitter::floatAllParams - No pdf specified will default to " << m_modelName 
            << std::endl;
        model =  dynamic_cast<RooAbsPdf*>( this->getPdf( this->getModelName() ) );
    } else {
        model = dynamic_cast<RooAbsPdf*>( this->getPdf( pdfName ) );
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( getDataSet() );

    // Get the current variables in the model.
    const RooArgSet* fitParams = model->getParameters( *rds ) ;
    if ( !fitParams ) {
        std::stringstream msg;
        msg << "Failed to get the list of observables "
            << "for model PDF " << model->GetName()
            << " from dataset " << rds->GetName();
        throw GeneralException( "Fitter::floatAllParams", msg.str() );
    }

    // loop over parameters and set to const
    TIterator* cIter = fitParams->createIterator();
    RooRealVar* obj = 0; 
    while( ( obj = dynamic_cast<RooRealVar*>( cIter->Next() ) ) ) {
        obj->setConstant( kFALSE );
    }

    delete fitParams; fitParams=0;
    delete cIter; cIter=0;
}


//-----------------------------------------------------------------------------
// get a RooAbsPdf from the workspace and fix all the parameters
//-----------------------------------------------------------------------------
void Fitter::fixAllParams( const char* pdfName ) 
{
    RooAbsPdf* model = 0;

    if( !pdfName||strcmp(pdfName,"")==0 ) {
        std::cout << "Fitter::floatAllParams - No pdf specified will default to " << m_modelName 
            << std::endl;
        model =  dynamic_cast<RooAbsPdf*>( this->getPdf( this->getModelName() ) );
    } else {
        model = dynamic_cast<RooAbsPdf*>( this->getPdf( pdfName ) );
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>( getDataSet() );

    // Get the current variables in the model.
    const RooArgSet* fitParams = model->getParameters( *rds );
    if ( !fitParams ) {
        std::stringstream msg;
        msg << "Failed to get the list of observables "
            << "for model PDF " << model->GetName()
            << " from dataset " << rds->GetName();
        throw GeneralException( "Fitter::fixAllParams", msg.str() );
    }

    // loop over parameters and set to const
    TIterator* cIter = fitParams->createIterator();
    RooRealVar* obj = 0; 
    while( ( obj = dynamic_cast<RooRealVar*>( cIter->Next() ) ) ) {
        obj->setConstant( kTRUE );
    }

    delete fitParams; fitParams=0;
    delete cIter; cIter=0;

}


//-----------------------------------------------------------------------------
// get a RooAbsPdf from the workspace by name
//-----------------------------------------------------------------------------
const RooAbsPdf* Fitter::getPdf(const char* name) const
{
    if ( !m_rws ) {
        throw GeneralException( "Fitter::getPdf",
                "No RooWorkspace object is defined!" );
    }

    const RooAbsPdf* pdf = m_rws->pdf( name );
    if (!pdf) {
        throw WSRetrievalFailure( "Fitter::getPdf",
                *m_rws, name, "RooAbsPdf" );
    }
    return pdf;
}


//-----------------------------------------------------------------------------
RooAbsPdf* Fitter::getPdf(const char* name)
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getPdf",
                "No RooWorkspace object is defined!" );
    }

    RooAbsPdf* pdf = m_rws->pdf(name);
    if (!pdf) {
        throw WSRetrievalFailure( "Fitter::getPdf",
                *m_rws, name, "RooAbsPdf" );
    }
    return pdf;
}


//-----------------------------------------------------------------------------
// Get the named set with the given name from the workspace
// Will raise an exception if the set does not exist in the workspace
//-----------------------------------------------------------------------------
const RooArgSet* Fitter::getNamedSet(const char* name) const
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getNamedSet",
                "No RooWorkspace object is defined!" );
    }

    const RooArgSet* set = m_rws->set( name );
    if ( !set ) {
        throw WSRetrievalFailure("Fitter::getNamedSet",
                *m_rws, name, "RooArgSet" );
    }
    return set;
}

//-----------------------------------------------------------------------------
const RooFitResult* Fitter::getFitResult(const char* fitName) const 
{
    if (!m_rws)  {
        throw GeneralException( "Fitter::getFitResult",
                "No RooWorkspace object is defined!" );
    }

    TString fitResName = TString::Format( "rfres_%s", fitName );
    const RooFitResult* rfres = dynamic_cast<RooFitResult*>( m_rws->obj( fitResName ) );
    if ( !rfres ) {
        throw WSRetrievalFailure( "Fitter::getFitResult",
                *m_rws, fitResName.Data(), "RooFitResult" );
    }
    return rfres;
}

//-----------------------------------------------------------------------------
RooFitResult* Fitter::getFitResult(const char* fitName) 
{
    if (!m_rws) {
        throw GeneralException( "Fitter::getFitResult",
                "No RooWorkspace object is defined!" );
    }
    TString fitResName = TString::Format( "rfres_%s", fitName );
    RooFitResult* rfres = dynamic_cast<RooFitResult*>( m_rws->obj( fitResName ) );
    if ( !rfres ) {
        throw WSRetrievalFailure( "Fitter::getFitResult",
                *m_rws, fitResName.Data(), "RooFitResult" );
    }
    return rfres;
}

//-----------------------------------------------------------------------------
const char* Fitter::getDataSetName() const {return m_dataSetName;}

//-----------------------------------------------------------------------------
const char* Fitter::getModelName() const {return m_modelName;}

//-----------------------------------------------------------------------------
const char* Fitter::getSWeightSetName() const {return m_sWeightVarSetName;}

//-----------------------------------------------------------------------------
const char* Fitter::getPlotParamsSetName() const {return m_plotParamsSetName;}

//-----------------------------------------------------------------------------
// get the line color of the model PDF
//-----------------------------------------------------------------------------
const Color_t& Fitter::getModelLineColor() const
{
    return m_modelLineColor;
}

//-----------------------------------------------------------------------------
// get the line style of the model PDF
//-----------------------------------------------------------------------------
const Style_t& Fitter::getModelLineStyle() const
{
    return m_modelLineStyle;
}

//-----------------------------------------------------------------------------
// get the line width of the model PDF
//-----------------------------------------------------------------------------
const Width_t& Fitter::getModelLineWidth() const
{
    return m_modelLineWidth;
}

//-----------------------------------------------------------------------------
// get the line color, style and width of the specified PDF component
// Will raise an exception if it is not in the list of components
//-----------------------------------------------------------------------------
const Color_t& Fitter::getPdfComponentLineColor(const char* name) const
{
    std::map<std::string,Color_t>::const_iterator it = m_pdfLineColorMap.find(name);
    if (it==m_pdfLineColorMap.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is not in  the list of components to plot";
        throw GeneralException("Fitter::getPdfComponentLineColor", msg.str());
    }
    return it->second;
}

//-----------------------------------------------------------------------------
const Style_t& Fitter::getPdfComponentLineStyle(const char* name) const
{
    std::map<std::string,Style_t>::const_iterator it = m_pdfLineStyleMap.find(name);
    if (it==m_pdfLineStyleMap.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is not in the list of components to plot";
        throw GeneralException("Fitter::getPdfComponentLineStyle", msg.str());
    }
    return it->second;
}

//-----------------------------------------------------------------------------
const Width_t& Fitter::getPdfComponentLineWidth(const char* name) const
{
    std::map<std::string,Width_t>::const_iterator it = m_pdfLineWidthMap.find(name);
    if (it==m_pdfLineWidthMap.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is not in the list of components to plot";
        throw GeneralException("Fitter::getPdfComponentLineWidth", msg.str());
    }
    return it->second;
}

//-----------------------------------------------------------------------------
// get the dataset line color
//-----------------------------------------------------------------------------
const Color_t& Fitter::getDataSetLineColor() const
{
    return m_dataSetLineColor;
}

//-----------------------------------------------------------------------------
// get the dataset line style
//-----------------------------------------------------------------------------
const Style_t& Fitter::getDataSetLineStyle() const
{
    return m_dataSetLineStyle;
}

//-----------------------------------------------------------------------------
// get the dataset line width
//-----------------------------------------------------------------------------
const Width_t& Fitter::getDataSetLineWidth() const
{
    return m_dataSetLineWidth;
}

//-----------------------------------------------------------------------------
// get the dataset marker color
//-----------------------------------------------------------------------------
const Color_t& Fitter::getDataSetMarkerColor() const
{
    return m_dataSetMarkerColor;
}

//-----------------------------------------------------------------------------
// get the dataset marker style
//-----------------------------------------------------------------------------
const Style_t& Fitter::getDataSetMarkerStyle() const
{
    return m_dataSetMarkerStyle;
}

//-----------------------------------------------------------------------------
// get the dataset marker width
//-----------------------------------------------------------------------------
const Size_t& Fitter::getDataSetMarkerSize() const
{
    return m_dataSetMarkerSize;
}

//-----------------------------------------------------------------------------
// get the dataset fill color
//-----------------------------------------------------------------------------
const Color_t& Fitter::getDataSetFillColor() const
{
    return m_dataSetFillColor;
}

//-----------------------------------------------------------------------------
// get the dataset fill style
//-----------------------------------------------------------------------------
const Style_t& Fitter::getDataSetFillStyle() const
{
    return m_dataSetFillStyle;
}

//-----------------------------------------------------------------------------
// get the dataset draw options (see TGraphPainter for details)
//-----------------------------------------------------------------------------
const char* Fitter::getDataSetDrawOption() const
{
    return m_dataSetDrawOption;
}

//-----------------------------------------------------------------------------
// Get the file we want to save the WS in
//-----------------------------------------------------------------------------

const TFile* Fitter::getFile() const {
	return m_file;
}

//-----------------------------------------------------------------------------
// get the parameter box attributes
//-----------------------------------------------------------------------------
const Float_t& Fitter::getParamBoxX1() const
{
    return m_paramBoxX1;
}

//-----------------------------------------------------------------------------
const Float_t& Fitter::getParamBoxX2() const
{
    return m_paramBoxX2;
}

//-----------------------------------------------------------------------------
const Float_t& Fitter::getParamBoxY1() const
{
    return m_paramBoxY1;
}

//-----------------------------------------------------------------------------
const Float_t& Fitter::getParamBoxY2() const
{
    return m_paramBoxY2;
}

//-----------------------------------------------------------------------------
const Float_t& Fitter::getParamBoxTextSize() const
{
    return m_paramBoxTextSize;
}

//-----------------------------------------------------------------------------
const Int_t& Fitter::getParamBoxTextAlign() const
{
    return m_paramBoxTextAlign;
}

//-----------------------------------------------------------------------------
const char* Fitter::getParamBoxName() const
{
    return m_paramBoxName;
}

//-----------------------------------------------------------------------------
// Get the number of plot bins
// If a name is specified, returns the number of bins for a given
// variable (raises an exception if the number of bins have not
// been defined for this variable)
//-----------------------------------------------------------------------------
const Int_t& Fitter::getPlotBins(const char* name) const
{
    if (!name||strcmp(name,"")==0)
    {
        return m_globalPlotBins;
    }
    std::map<std::string, Int_t>::const_iterator it;
    it = m_plotBinMap.find(name);
    if (it==m_plotBinMap.end())
    {
        std::stringstream msg;
        msg << "Variable " << name << " is not in the map of variable name to plot bins";
        throw GeneralException("Fitter::getPlotBins", msg.str());
    }
    return it->second;
}


//-----------------------------------------------------------------------------
// Get the number of plot bins.
// Returns the number of bins for this variable, if defined, else
// returns the global number of bins
//-----------------------------------------------------------------------------
const Int_t& Fitter::getPlotBinsInt(const char* name) const {
    std::map<std::string, Int_t>::const_iterator it = m_plotBinMap.find(name);
    if (it==m_plotBinMap.end()) return m_globalPlotBins;
    else return it->second;
}

//-----------------------------------------------------------------------------
// Get the name of the data histogram in a RooPlot of the specified
// fit variable.
// This function is used to get the pull plot.
// NB. You may need to be override this method in a derived class.
//-----------------------------------------------------------------------------
std::string Fitter::getDataHistName() const {
    // construct the histogram name from the dataset name
    std::stringstream ss_histName;
    ss_histName << "h_" << this->getDataSetName();
    return ss_histName.str();
}

//-----------------------------------------------------------------------------
// Get the name of the model PDF curve in a RooPlot of the specified
// fit variable.
// This function is used to get the pull plot.
// NB. You may need to be override this method in a derived class.
//-----------------------------------------------------------------------------
std::string Fitter::getModelCurveName(const char* name) const {
    // construct the curve name for the model PDF
    std::stringstream ss_curveName;
    ss_curveName << this->getModelName() << "_Norm[" << name << "]";
    return ss_curveName.str();
}

//-----------------------------------------------------------------------------
// create a formatting TString for an abitrary RooAbsArg object
//-----------------------------------------------------------------------------
TString* Fitter::format(RooAbsReal* var, const RooFitResult* rfit,
        Int_t sigDigits, const char *options) const
{
    // To control what is shown use the following options
    // N = show name
    // H = hide value
    // E = show error
    // U = show unit
    //
    // To control how it is shown use these options
    // L = TLatex mode
    // X = Latex mode
    // Y = Latex table mode ( '=' replaced by '&' )
    // V = make name \verbatim in Latex mode
    // P = use error to control shown precision
    // F = force fixed precision
    assert(var);
    assert(rfit);

    // if this is a RooRealVar, then just return the standard method
    RooRealVar* rvar = dynamic_cast<RooRealVar*>(var);
    if (rvar) return rvar->format(sigDigits, options);

    // otherwise, we have to calculate things ourself
    //cout << "format = " << options << endl ;

    // parse the options string
    TString opts(options);
    opts.ToLower();
    Bool_t showName= opts.Contains("n");
    Bool_t hideValue= opts.Contains("h");
    Bool_t showError= opts.Contains("e");
    Bool_t showUnit= opts.Contains("u");
    Bool_t tlatexMode= opts.Contains("l");
    Bool_t latexMode= opts.Contains("x");
    Bool_t latexTableMode = opts.Contains("y") ;
    Bool_t latexVerbatimName = opts.Contains("v") ;

    if (latexTableMode) latexMode = kTRUE ;
    Double_t value = var->getVal();
    Double_t error = var->getPropagatedError(*rfit);
    TString unit = var->getUnit();

    Bool_t hasError=(error!=0);

    Bool_t useErrorForPrecision= (((showError && hasError && !var->isConstant()) || opts.Contains("p")) && !opts.Contains("f")) ;
    // calculate the precision to use
    if(sigDigits < 1) sigDigits= 1;
    Int_t leadingDigitVal = 0;
    if (useErrorForPrecision) {    
        leadingDigitVal = (Int_t)floor(log10(fabs(error+1e-10)));
        if (value==0&&error==0) leadingDigitVal=0 ;
    } else {
        leadingDigitVal = (Int_t)floor(log10(fabs(value+1e-10)));
        if (value==0) leadingDigitVal=0 ;
    }
    Int_t leadingDigitErr= (Int_t)floor(log10(fabs(error)));
    Int_t whereVal= leadingDigitVal - sigDigits + 1;
    Int_t whereErr= leadingDigitErr - sigDigits + 1;
    char fmtVal[16], fmtErr[16];

    if (value<0) whereVal -= 1 ;
    snprintf(fmtVal,16,"%%.%df", whereVal < 0 ? -whereVal : 0);
    snprintf(fmtErr,16,"%%.%df", whereErr < 0 ? -whereErr : 0);
    TString *text= new TString();
    if(latexMode) text->Append("$");
    // begin the string with "<name> = " if requested
    if(showName) {
        if (latexTableMode && latexVerbatimName) {
            text->Append("\\verb+") ;
        }
        text->Append(var->getPlotLabel());
        if (latexVerbatimName) text->Append("+") ;

        if (!latexTableMode) {
            text->Append(" = ");
        } else {
            text->Append(" $ & $ ");
        }
    }

    // Add leading space if value is positive
    if (value>=0) text->Append(" ") ;

    // append our value if requested
    char buffer[256];
    if(!hideValue) {
        // The following lines are copied from
        // RooRealVar::chopAt
        // They don't actually seem to do anything,
        // but I thought I better put them in here in case
        // they're implemented in the future
        //  Double_t scale= pow(10.0,whereVal);
        //     Int_t trunc= (Int_t)floor(value/scale + 0.5);
        //     Double_t ca = (Double_t)trunc*scale;

        snprintf(buffer, 256,fmtVal, value);
        text->Append(buffer);
    }

    // append our error if requested and this variable is not constant
    if(hasError && showError) {
        if(tlatexMode) {
            text->Append(" #pm ");
        }
        else if(latexMode) {
            text->Append("\\pm ");
        }
        else {
            text->Append(" +/- ");
        }
        snprintf(buffer, 256,fmtErr, error);
        text->Append(buffer);
    }  

    // append our units if requested
    if(!unit.IsNull() && showUnit) {
        text->Append(' ');
        text->Append(unit);
    }
    if(latexMode) text->Append("$");
    return text;
}

//-----------------------------------------------------------------------------
void Fitter::makeMassDataSet( TTree* tt, const char* BMassVarname, const char* name,
        const char* title, const char* cuts, const char* weightVarName )
{

    // If weighted, save weight var name
    if (!std::string(weightVarName).empty()) {
        m_weightVarName = weightVarName;

		if (!tt->FindBranch(weightVarName)) {
			throw GeneralException( "Fitter::makeMassDataSet",
				"Weight variable does not exist in tree." );
		}
    }   

    //TFile *f_temp = 0;
    // Some arbitrary TFile to avoid nasty TTree before TFile errors.
    TFile *f_temp = new TFile( "temp_data_file_121.root", "RECREATE" );
    TTree *clone  = new TTree( "clone", "tree" );

    if (!m_rws) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "No RooWorkspace object is defined." );
    }

    if ( !tt ) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "Expected pointer to TTree as argument, got NULL pointer." );
    }

    RooRealVar* mass = m_rws->var( m_1DFitVarName );
    if ( !mass ) {
        throw WSRetrievalFailure( "Fitter::makeMassDataSet",
                *m_rws, m_1DFitVarName, "RooRealVar" );
    }

    if ( !BMassVarname || strcmp( BMassVarname, "" ) == 0 ) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "No B mass branch name specified." );
    }
    if ( !name || strcmp( name, "" ) == 0 ) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "No RooDataSet name specified." );
    }
    if( tt->GetEntries() == 0 ) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "TTree has zero entries." );
    }


    //clone for internal use  
    //TTree* clone = dynamic_cast<TTree*>( tt->CloneTree() );
    clone = dynamic_cast<TTree*>( tt->CloneTree() );

    Long64_t nTotal = clone->GetEntries();
    if ( nTotal == 0 ) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "No entries in input TTree." );
    }
    TEntryList* elist = 0;

    if ( clone->GetEntryList() ) {
        std::cout << "I have an entrylist" << std::endl;
    }

    clone->SetBranchStatus( "*", 1 );

    std::stringstream namestream;
    namestream << name;

    if ( cuts && strcmp( cuts, "" ) != 0 ) {
        clone->Draw( ( ">>elist" + namestream.str() ).c_str(), cuts, "entryList" );
        elist = dynamic_cast<TEntryList*>( gDirectory->Get( ( "elist" + namestream.str() ).c_str() ) );
        if ( !elist ) {
            std::stringstream msg;
            msg << "Failed to retrieve TEntryList for cuts " << cuts;
            throw GeneralException( "Fitter::makeMassDataSet",
                    msg.str() );
        }
        clone->SetEntryList( elist );
    }

    // TTree* ttReduced = tt->CopyTree(cuts);
    Long64_t nentries = !elist?clone->GetEntries():elist->GetN();
    if ( nentries == 0 ) {
        throw GeneralException( "Fitter::makeMassDataSet",
                "No entries in TTree after cuts." );
    }

    Float_t M_f = 0;
    Double_t M = 0;

    Double_t weightVal = 0;
    // if this is a TChain, then we need to use the daughters method
    clone->SetBranchStatus( "*", 1 );

    TChain* ch = 0;
    ch = dynamic_cast<TChain*>( clone );
    std::string masstype = ch ? getBranchType( ch, BMassVarname ) : getBranchType( clone, BMassVarname );
    if ( !ch ) {
        if ( masstype.compare( "Float_t" ) == 0 ) { 
            clone->SetBranchAddress( BMassVarname, &M_f );
        }
        else if ( masstype.compare( "Double_t" ) == 0 ) {
            clone->SetBranchAddress( BMassVarname, &M );
        }
        else {
            std::stringstream msg;
            msg << "Got unexpected type " << masstype << " for variable " 
                << BMassVarname;
            throw GeneralException("Fitter::makeBMassDataSet", msg.str() );
        }

        if (!std::string(m_weightVarName).empty()) clone->SetBranchAddress(weightVarName, &weightVal);
    }
    else {
        if (masstype.compare( "Float_t" )==0) { 
            ch->SetBranchAddress( BMassVarname, &M_f );
        }
        else if (masstype.compare( "Double_t" ) == 0 ) {
            ch->SetBranchAddress( BMassVarname, &M );
        }
        else {
            std::stringstream msg;
            msg << "Got unexpected type " << masstype << " for variable " 
                << BMassVarname;
            throw GeneralException("Fitter::makeBMassDataSet", msg.str() );
        }
    }

    RooArgSet observables( *mass );
    RooArgSet args( *mass );

    // TODO: check whether definition still holds for the weight
    //RooArgSet args;
    //args.addClone(*mass);

    // If weighted, add weight var to args.
    // If weight var is not present, weighting fails silently!

    RooRealVar * weight = 0;

    if (!std::string(m_weightVarName).empty()) {
        weight = new RooRealVar(weightVarName, weightVarName, -1.1, 10);
        args.add(*weight);
    }  

    std::map<std::string, void*> varMap;
    std::map<std::string, Int_t*> catMap;

    const RooArgSet* extraArgs = m_rws->set( m_spectSetName );

    if (extraArgs) {
        TIterator *it = extraArgs->createIterator();
        std::string varName;
        RooRealVar* v = 0;
        while ( (v=dynamic_cast<RooRealVar*>( it->Next() ) ) )
        {
            varName=v->GetName();
            if ( !args.add( *v ) ) {
                std::stringstream msg;
                msg << "Request to add RooRealVar " << varName 
                    << " to dataset, which has already been included";
                throw GeneralException("Fitter::makeBMassDataSet", msg.str() );
            }
            std::string branchName = varName;
            if ( m_varNameToBranchName.find( varName ) != m_varNameToBranchName.end() ) {
                branchName = m_varNameToBranchName[varName];
            }

            std::string type = getBranchType(clone, branchName);
            if (type.compare("Float_t")==0) {
                varMap[varName] = new Float_t();
            }
            else if (type.compare("Double_t")==0) {
                varMap[varName] = new Double_t();
            }
            else if (type.compare("Int_t")==0) {
                varMap[varName] = new Int_t();
            }
            else if (type.compare("UInt_t")==0) {
                varMap[varName] = new UInt_t();
            }
            else {
                std::stringstream msg;
                msg << "Got unexpected type " << type << " for variable " << varName;
                throw GeneralException("Fitter::makeBMassDataSet", msg.str());
            }
            if (!ch) {
                clone->SetBranchAddress(branchName.c_str(), varMap[varName]);
            }
            else {
                ch->SetBranchAddress(branchName.c_str(), varMap[varName]);
            }
        }
    }

    RooDataSet *rds = new RooDataSet(name, title?title:"", args);
    Long64_t entry=0;
    Long64_t localEntry=0;
    Long64_t entryNumber=0;

    for (entry=0; entry<nentries; ++entry)
    {
        entryNumber=clone->GetEntryNumber(entry);
        if (entryNumber<0) {
            std::stringstream msg;
            msg << "Got invalid entry number " << entryNumber;
            throw GeneralException("Fitter::makeBMassDataSet", msg.str());
        }
        if (ch) {
            localEntry = ch->LoadTree(entryNumber);
            if (localEntry<0) {
                std::stringstream msg;
                msg << "Got invalid entry number in current tree " << localEntry;
                throw GeneralException("Fitter::makeBMassDataSet", msg.str());
            }
        }

        Int_t nb;
        nb=clone->GetEntry(entryNumber);
        if (nb<=0) {
            std::stringstream msg;
            msg << "Got invalid number of bytes " << nb 
                << " for entry " << entry;
            throw GeneralException("Fitter::makeBMassDataSet", msg.str());
        }

        if (masstype.compare("Float_t")==0) M=static_cast<Double_t>(M_f);

        if ( (mass->inRange(M,0)) ) {

            mass->setVal(M);
            if (!std::string(m_weightVarName).empty()) weight->setVal(weightVal);
            
            Bool_t passed=kTRUE;
            if (varMap.size()!=0) {
                for (std::map<std::string, void*>::iterator it=varMap.begin();
                        it!=varMap.end(); ++it)
                {
                    std::string vname=(it->first);
                    void *val=(it->second);
                    assert (val!=0);
                    std::string branchName=vname;
                    if (m_varNameToBranchName.find(vname)!=m_varNameToBranchName.end()) {
                        branchName=m_varNameToBranchName[vname];
                    }
                    Double_t v;
                    std::string type=getBranchType(clone, branchName);
                    if (type.compare("Float_t")==0) {
                        Float_t* ptr=static_cast<Float_t*>(val);
                        assert(ptr);
                        v=(Double_t)(*ptr);
                    }
                    else if (type.compare("Double_t")==0) {
                        Double_t* ptr = static_cast<Double_t*>(val);
                        assert(ptr);
                        v=(Double_t)(*ptr);
                    }
                    else if (type.compare("Int_t")==0) {
                        Int_t* ptr = static_cast<Int_t*>(val);
                        assert(ptr);
                        v=(Double_t)(*ptr);
                    }
                    else if (type.compare("UInt_t")==0) {
                        UInt_t* ptr = static_cast<UInt_t*>(val);
                        assert(ptr);
                        v=(Double_t)(*ptr);
                    }
                    else {
                        std::stringstream msg;
                        msg << "Got unexpected type " << type << " for variable " 
                            << vname;
                        throw GeneralException("Fitter::makeBMassDataSet",
                                msg.str());
                    }
                    if (!args.find(vname.c_str())) {
                        std::stringstream msg;
                        msg << "Unable to find variable name " << vname << " in RooArgSet";
                        throw GeneralException("Fitter::makeBMassDataSet",
                                msg.str());
                    }
                    RooRealVar *var=dynamic_cast<RooRealVar*>(&args[vname.c_str()]);
                    if (!var) {
                        std::stringstream msg;
                        msg << "Unable to cast RooAbsArg " << vname << " to a RooRealVar";
                        throw GeneralException("Fitter::makeBMassDataSet",
                                msg.str());
                    }
                    if (m_varNameToFunction.find(vname)!=m_varNameToFunction.end()) { 
                        DoubleFun fun = m_varNameToFunction[vname];
                        assert(fun);
                        v = fun(v);
                        if (!var->inRange(v,0)) {
                            passed=kFALSE;
                            break;
                        }
                        var->setVal(v);
                    }
                    else if (m_varNameToFormula.find(vname)!=m_varNameToFormula.end()) {
                        TFormula& fun = m_varNameToFormula[vname];
                        v = fun.Eval(v);
                        if (!var->inRange(v,0)) {
                            passed=kFALSE;
                            break;
                        }
                        var->setVal(v);
                    }
                    else {
                        if (!var->inRange(v,0))
                        {
                            passed=kFALSE;
                            break;
                        }
                        var->setVal(v);
                    }
                }
            }
            if (!passed) continue;
            rds->add(args);
        }
    }  // loop over entries


    if (rds->numEntries()==0) {
        throw GeneralException("Fitter::makeBMassDataSet",
                "No entries selected!");
    }
    std::cout << "Fitter::makeBMassDataSet: Initial entries = "
        << nTotal << std::endl;
    if (cuts&&strlen(cuts)>0) {
        std::cout << "Fitter::makeBMassDataSet: Entries passing selection cut (" 
            << cuts << ") = " << nentries << std::endl;
    }
    std::cout << "Fitter::makeBMassDataSet: Selected entries = " 
        << rds->numEntries() << std::endl;

    if ( m_rws->import( *rds ) ) {
        throw WSImportFailure( "Fitter::makeBMassDataSet", *m_rws, *rds );
    }

    for (std::map<std::string, void*>::iterator i=varMap.begin();
            i!=varMap.end(); ++i) {
        std::string vname = i->first;
        void* val = i->second;
        if (val==0) continue;
        std::string branchName=vname;
        if (m_varNameToBranchName.find(vname)!=m_varNameToBranchName.end()) {
            branchName=m_varNameToBranchName[vname];
        }
        std::string type=getBranchType(clone, branchName);
        if (type.compare("Float_t")==0) {
            delete static_cast<Float_t*>(val);
        }
        else if (type.compare("Double_t")==0) {
            delete static_cast<Double_t*>(val);
        }
        else if (type.compare("Int_t")==0) {
            delete static_cast<Int_t*>(val);
        }
        else if (type.compare("UInt_t")==0) {
            delete static_cast<UInt_t*>(val);
        }
        else {
            std::stringstream msg;
            msg << "Got invalid data type " << type; 
            throw GeneralException("Fitter::makeBMassDataSet", msg.str());
        }
    }

    varMap.clear();
    f_temp->Close();
    delete f_temp; f_temp = 0;

    // remove the temp datafile permanently.
    TSystemFile sysFile( "temp_data_file_121.root", "." );
    sysFile.Delete();
}


//=============================================================================
// Sets the parameter in workspace described by varname, constant or floating.
//=============================================================================
void Fitter::setParameterConstant(const char* varname, bool constant )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::setParameterConstant",
                "No RooWorkspace object is defined" );
    }

    RooRealVar* var = m_rws->var( varname );
    if( !var ) {
        throw WSRetrievalFailure("Fitter::setParameterConstant",
                *m_rws, varname, "RooRealVar" );
    }
    var->setConstant( constant );
}


//=============================================================================
// Sets the parameter in workspace described by varname, constant to value.
//=============================================================================
void Fitter::setParameterConstant(const char* varname, double value )
{
    if (!m_rws) {
        throw GeneralException( "Fitter::setParameterConstant",
                "No RooWorkspace object is defined" );
    }
    RooRealVar* var = m_rws->var( varname );
    if( !var ) {
        throw WSRetrievalFailure( "Fitter::setParameterConstant",
                *m_rws, varname, "RooRealVar" );
    }
    var->setConstant( kFALSE );
    var->setVal( value );
    var->setConstant( kTRUE );

}

// Sets the value of the parameter, defined by varname, to value. does not set constant.
void Fitter::setParameterValue(const char* varname, double value, bool isConst)
{
    if (!m_rws) {
        throw GeneralException( "Fitter::setParameterValue",
                "No RooWorkspace object is defined" );
    }
    RooRealVar* var = m_rws->var( varname );
    if( !var ) {
        throw WSRetrievalFailure( "Fitter::setParameterValue",
                *m_rws, varname, "RooRealVar" );
    }
    var->setConstant( kFALSE );
    var->setVal( value );
    var->setConstant( isConst );

}

//=============================================================================
void Fitter::setnCPU( int n ) { m_nCores = n; }

//=============================================================================
int Fitter::getnCPU() const { return m_nCores; }
//=============================================================================

//=============================================================================
void Fitter::set1DFitVarName(const char* name) { m_1DFitVarName = name; }

//=============================================================================
const char* Fitter::get1DFitVarName() { return m_1DFitVarName; }
//=============================================================================

//=============================================================================
// calculates the likelihood ratio of the default fit and the fit 
// with the given parameter set to zero
//=============================================================================
double Fitter::likelihoodRatio(const char* paramName, const char* fitName)
{
    const RooFitResult* theresult = this->getFitResult( fitName );
    if (!theresult){
        throw GeneralException("Fitter::likelihoodRatio",
                "Default fit has not been performed."); 
    }
    // Minimized log(L) value of nominal fit.
    Double_t NLL_init = theresult->minNll();

    std::vector<std::string> args; // Check if we're setting multiple parameters to zero.
    std::string paramNameStr( paramName ); 
    // I would love to use boost here but it is just not worth it for the CINT part, at least this way we
    // can use this all in python via cintex.
    m_stringHelper.replaceAll( paramNameStr, " ", "" ); // remove all whitespaces
    m_stringHelper.split( args, paramNameStr, "," );

    if( args.size() < 2 ) {
        // Get the variable to check it exists.
        RooRealVar* theParam = m_rws->var( paramNameStr.c_str() );
        if ( !theParam ) {
            throw WSRetrievalFailure( "Fitter::likelihoodRatio",
                    *m_rws, paramNameStr.c_str(), "RooRealVar" );
        }
        //set the param value to zero
        setParameterConstant( paramNameStr.c_str(), 0. );
    }
    else {
        std::vector<std::string>::const_iterator iter = args.begin();
        const std::vector<std::string>::const_iterator enditer = args.end();
        for ( ; iter != enditer; ++iter ) {
            // Get the variable to check it exists.
            RooRealVar* theParam = m_rws->var( iter->c_str() );
            if (!theParam) {
                throw WSRetrievalFailure("Fitter::likelihoodRatio",
                        *m_rws, *iter, "RooRealVar");
            }
            //set the param value to zero
            setParameterConstant( iter->c_str(), 0. );
        }
    }

    std::string thefitName( fitName );

    performFit( ( thefitName + "_constparams" ).c_str() );
    RooFitResult* thenewFitResult = getFitResult( ( thefitName + "_constparams" ).c_str() );
    Double_t NLL_fin = thenewFitResult->minNll();

    double significance = - 2.0 * ( NLL_init - NLL_fin ) ;
    significance = (significance > 0.0) ? TMath::Sqrt(significance) : -999.0;
    std::cout << "Significance ratio = " << significance << 
        " when removing ";

    std::vector<std::string>::const_iterator iter = args.begin();
    const std::vector<std::string>::const_iterator enditer = args.end();
    for (; iter != enditer; ++iter) {
        if( *iter == args.back() ) {
            std::cout << *iter << ".";
        } else {
            std::cout << *iter << ", ";
        }
    }
    std::cout << std::endl;

    // have to reset the parameters, in order to be able to do something with (Splots) afterwards
    loadSnapshot( fitName );

    return significance;
}

//=============================================================================
// Protected method that returns the type of variable in the brName of the
// supplied TTree.
//=============================================================================
std::string Fitter::getBranchType(TTree* tt, std::string brName) 
{
    assert(tt);
    TChain* ch=dynamic_cast<TChain*>(tt);
    TBranch* br = ch==0?tt->GetBranch(brName.c_str()):ch->GetBranch(brName.c_str());
    if (!br) {
        std::stringstream msg;
        msg << "Unable to retrieve branch with name " << brName << " from TTree "
            << tt->GetName();
        throw GeneralException("Fitter::getBranchType", msg.str());
    }
    return ( dynamic_cast<TLeaf*>( br->GetListOfLeaves()->At(0) ) )->GetTypeName();
}


//=============================================================================
// Write a txt file for the fit result floating parameters
//=============================================================================
TString Fitter::renameVar( TString thename ) {
    TString name = thename;
    //thename.ReplaceAll(,"\\mp","\\pm");
    name.ReplaceAll( "#", "\\" );
    return name;
}


//=============================================================================
// Write a txt file for the fit result floating parameters
//=============================================================================
void Fitter::writeTable( const char* nameOutput, const char* fitName ) 
{

    const RooFitResult* theresult = this->getFitResult( fitName );
    if (!theresult){
        throw GeneralException("Fitter::writeTable",
                "Default fit has not been performed."); 
    }

    RooArgList& list = (RooArgList &) theresult->floatParsFinal();
    int size = list.getSize();

    //plot fitResults in latex and correlation matrix in a picture
    std::string fnameLatex = std::string(nameOutput) + ".tex";
    std::ofstream ofile;
    ofile.open( fnameLatex.c_str() );
    if ( !ofile.is_open() ) return;
    ofile << "\\begin{tabular}{lc}" << std::endl;

    for ( int i = 0; i < size; ++i ) {
        RooRealVar* var = dynamic_cast<RooRealVar*>( list.at(i) );
        TString name = renameVar( var->GetName() );
        double errHi = var->getErrorHi();
        double errLo = var->getErrorLo();
        int nDig1, nDig2;
        getDigits(errLo,errHi,nDig1,nDig2);
        if (nDig1>1)
            ofile << std::setprecision(0) << std::fixed;
        else if (nDig1==1)
            ofile << std::setprecision(1) << std::fixed;
        else if (nDig1==0)
            ofile << std::setprecision(nDig2+1) << std::fixed;
        ofile << "$ " << name << " $" 
            << " & $ " << var->getVal() << "^{+" << var->getErrorHi() << " }_{ " << var->getErrorLo() << "}$\\\\" 
            << std::endl;
    }
    ofile << "\\end{tabular}" << std::endl;
    ofile.close();

}


//=============================================================================
// Get the number of significant digits and round the numbers accordingly.=============================================================================
void Fitter::getDigits(double err,double err2, int& nDig1, int& nDig2) 
{

    // get the number of significant digits and round the numbers accordingly
    // number of significant digits before the "."
    int ierr = (int) err;
    int ierr2 = (int) err2;
    std::string serr = m_stringHelper.to_string<int>(ierr);
    if (ierr==0) serr = "";
    nDig1 = serr.size();
    // position of the first significant digit in case                                                                                                       
    std::ostringstream ss;
    double err0 = 0;
    int ierr0 = 0;
    if (fabs(err-ierr)>fabs(err2-ierr2)) {
        err0 = err;
        ierr0 = ierr;
    }
    else {
        err0 = err2;
        ierr0 = ierr2;
    }
    ss << std::scientific << (err0-ierr0);
    std::string snDig2 = ss.str();

    m_stringHelper.replaceBefore(snDig2,"e-");
    std::istringstream ( snDig2 ) >> nDig2;

}


//=============================================================================
// Plot 2d correlation between floating parameters.
//=============================================================================
TH2* Fitter::plotCorrelationHist( const char* fitName, double labelsize ) 
{

    RooFitResult* theresult = dynamic_cast<RooFitResult*>( getFitResult( fitName ) );
    if (!theresult){
        throw GeneralException("Fitter::plotCorrelationHist",
                "Default fit has not been performed."); 
    }

    //gStyle->SetPaintTextFormat(".2f");
    TH2* hcorr = theresult->correlationHist( "hcorr" );
    hcorr->SetStats( kFALSE );
    hcorr->SetTitle( "" );
    //hcorr->LabelsDeflate("X");
    //hcorr->LabelsDeflate("Y");
    // set the x-axis vertical to save space!
    hcorr->SetLabelSize( labelsize, "x" );
    hcorr->SetLabelSize( labelsize, "y" );
    hcorr->LabelsOption( "v" );

    if ( theresult->floatParsFinal().getSize() < 10 ) hcorr->SetMarkerSize( 2 );
    /*for ( int i = 0; i < size; ++i ){
      RooRealVar* var = dynamic_cast<RooRealVar*>( list.at(i) );
      hcorr -> GetXaxis() -> SetBinLabel( i+1, renameVarRoot(var->GetName()).c_str());
      hcorr -> GetYaxis() -> SetBinLabel( i+1, renameVarRoot(var->GetName()).c_str());
      for ( int j = 0; j < size; ++j ){
      RooRealVar* varj = dynamic_cast<RooRealVar*>( list.at(j) );
      double corr = mFitResult->correlation(var->GetName(),varj->GetName());
      if (corr==0) corr = 1e-8;
      hcorr -> SetBinContent( i+1, j+1 , corr );
      }
      }*/
    //hcorr->Draw("textcolz");

    return hcorr;
}

//=============================================================================
// Public method that converts a RooArgList to a RooArgSet
//=============================================================================
RooArgSet* Fitter::RooArgList2Set(const RooArgList* theList)
{
    RooArgSet* returnSet = new RooArgSet( *theList );

    return returnSet;

}

//=============================================================================
// Public method that converts a RooArgSet to a RooArgList
//=============================================================================
RooArgList* Fitter::RooArgSet2List(const RooArgSet* theSet)
{
    RooArgList* returnList = new RooArgList();

    RooAbsArg* arg = 0;
    TIterator* iter = theSet->createIterator();
    while ((arg=dynamic_cast<RooAbsArg*>( iter->Next() ) ) ) {

        if( !returnList->add( *arg ) ) {
            std::stringstream msg;
            msg << "Failed to add " << arg->GetName() << " to RooArgList.";
            throw GeneralException("Fitter::RooArgSet2List",msg.str() );
        }
    }

    delete iter; iter = 0;
    return returnList;
}

//=============================================================================
// Static method to find an object 
//=============================================================================
TKey* Fitter::findItem(TFile* f, TClass* classType)
{
    if (f == NULL)
        throw GeneralException("Fitter::findItem", "File not found!");
    TList *listOfKeys = f->GetListOfKeys();  
    if (listOfKeys == NULL)
        throw GeneralException("Fitter::findItem", "No list of keys in the considered file.");

    TIterator* it = listOfKeys->MakeIterator();
    bool found(false);
    TKey *result = NULL;
    TKey* key = NULL;
    while ((key = (TKey*) it->Next()) != NULL)
    {
        if (std::string(key->GetClassName()) == std::string(classType->GetName()))
        {
            if (!found)
            {
                found = true;
                result = key;
            }
            else if (found)
                throw GeneralException("Fitter::findItem",
                        (std::string("Found two objects of the class ")+classType->GetName()));
        }
    }
    if (result == NULL || found == false)
        throw GeneralException("Fitter::findItem",
                (std::string("Found no object of the class ")+classType->GetName()));

    return result;
}

//=============================================================================
// Static method to find an object 
//=============================================================================
std::vector<TKey*> Fitter::findAllItems(TFile* f, TClass* classType)
{
    if (f == NULL)
        throw GeneralException("Fitter::findAllItems", "File not found!");

    TList *listOfKeys = f->GetListOfKeys();
    if (listOfKeys == NULL)
        throw GeneralException("Fitter::findAllItems", "No list of keys in the considered file.");
    TIterator* it = listOfKeys->MakeIterator();
    std::vector<TKey*> result;
    TKey* key = NULL;
    while ((key = (TKey*) it->Next()) != NULL)
        if (key->GetClassName() == classType->GetName())
            result.push_back(key);

    if (result.size() == 0) 
        throw GeneralException("Fitter::findAllItems",
                (std::string("Found no object of the class ")+classType->GetName()));	
    return result;
}

//=============================================================================
// Static method to find the newest version of the model with a name scheme
// beginning with modelBase.
//=============================================================================
std::string Fitter::findModel(RooWorkspace* w, const char* modelBase)
{
    if (w == NULL)
        throw GeneralException("Fitter::findModel", "Workspace not found!");

    RooArgSet listOfPdfs = w->allPdfs();
    if (listOfPdfs.getSize() == 0)
        throw WSRetrievalFailure("Fitter::findModel",*w, "(anything)", "RooAbsPdf");
    TIterator* it = listOfPdfs.createIterator();
    RooAbsPdf* pdf = NULL;
    std::string result(modelBase);
    bool found(false);
    while ((pdf = (RooAbsPdf*) it->Next()) != NULL)
    {
        std::string pdfName = pdf->GetName();
        if (pdfName.find(modelBase) != std::string::npos && pdfName.find(result.c_str()) != std::string::npos)
        {
            found = true;
            result = pdfName;
        }
    }
    if (!found)
        throw WSRetrievalFailure("Fitter::findModel",*w, (std::string("beginning by ")+modelBase).c_str(), "RooAbsPdf");
    return result;

}

//=============================================================================
// Method to find the newest version of the model
//=============================================================================
std::string Fitter::findModel(const char* modelBase) const
{
    const RooWorkspace *w  = this->getWS();
    RooArgSet listOfPdfs = w->allPdfs();
    if (listOfPdfs.getSize() == 0)
        throw WSRetrievalFailure("Fitter::findModel",*w, "(anything)", "RooAbsPdf");

    TIterator* it = listOfPdfs.createIterator();
    RooAbsPdf* pdf = NULL;
    std::string result(modelBase);
    bool found(false);
    while ((pdf = (RooAbsPdf*) it->Next()) != NULL)
    {
        std::string pdfName = pdf->GetName();
        if (pdfName.find(modelBase) != std::string::npos && pdfName.find(result.c_str()) != std::string::npos)
        {
            found = true;
            result = pdfName;
        }
    }
    if (!found)
        throw WSRetrievalFailure("Fitter::findModel",*w, (std::string("beginning by ")+modelBase).c_str(), "RooAbsPdf");

    delete it; it = 0;
    return result;  
}

//=============================================================================
// Puts the parameter with oldname into the m_OldVersions vector. Raises
// exception if the parameter is not in the workspace.
//=============================================================================
void Fitter::scrap(const char* oldname)
{
    std::string name( oldname );
    RooAbsArg* object = dynamic_cast<RooAbsArg*>( m_rws->obj( oldname ) );
    if ( !object ) {
        std::stringstream msg;
        msg << "Tried to scrap object - " << oldname << ", which is not in the workspace.";
        throw GeneralException( "Fitter::scrap", msg.str() );
    }
    m_OldVersions.push_back( name );
}

// list of old objects
std::vector<std::string> Fitter::getOldObjects() const
{ 
    return m_OldVersions; 
}

//=============================================================================
// Returns the total yield over all simulataneous fits.
//=============================================================================
double Fitter::sumYields() 
{
    if ( !m_rws ) {
        throw GeneralException( "Fitter::sumYields",
                "No RooWorkspace object is defined." );
    }

    // Get the mass variable
    RooRealVar* mass = m_rws->var( m_1DFitVarName );
    if ( !mass ) {
        throw WSRetrievalFailure( "Fitter::sumYields",
                *m_rws, m_1DFitVarName, "RooRealVar" ); 
    }

    const RooDataSet* rds = getDataSet();

    //Get the stuff I need from the workspace
    RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );  
    if ( !model ) { 
        throw WSRetrievalFailure( "Fitter::sumYields",
                *m_rws, m_modelName, "RooAbsPdf" ); 
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds );

    if (!observables) {
        std::stringstream msg;
        msg << "Failed to get the list of observables "
            << "for model PDF " << model->GetName()
            << " from dataset " << rds->GetName();
        throw GeneralException("Fitter::sumYields", msg.str() );
    }

    // grab the expectect number of events from fit.
    return model->expectedEvents( observables );
}


//=============================================================================
// Blind the given variable, raises exception if varname is not in workspace.
// centralValue and scale are arguments to the RooUnblindPrecision constructor
// that define the blinding transformation.
// Uses member variable for blindstring.
//=============================================================================
void Fitter::blindParameter(const char* varname,
        double scale)
{
    if (!m_rws) {
        throw GeneralException( "Fitter::blindParameter",
                "No RooWorkspace object is defined" );
    }

    RooAbsReal* var = m_rws->var( varname );
    if( !var ) {
        throw WSRetrievalFailure( "Fitter::blindParameter",
                *m_rws, varname, "RooRealVar" );
    }

    std::stringstream blindvarname;
    blindvarname << "ub_" << varname;

    //use RooUnblindUniform for the timebeing, maybe switch in the future.  
    //RooUnblindPrecision blindvar(blindvarname.str().c_str(),"",m_BlindString,
    //                             centralValue, scale, *var);

    RooUnblindUniform blindvar( blindvarname.str().c_str(), "", m_BlindString,
            scale, *var );

    //import it first since import clones the object and to get the address of
    //it in the RooWorkspace one must get it again
    if ( m_rws->import( blindvar ) ) {
        throw WSImportFailure( "Fitter::blindParameter",
                *m_rws, blindvar );
    }

    RooAbsReal* newblindvar = dynamic_cast<RooAbsReal*>(
            m_rws->obj( blindvarname.str().c_str() ) );

    if( !newblindvar ) {
        throw WSRetrievalFailure( "Fitter::blindParameter",
                *m_rws, blindvarname.str().c_str(), "RooUnblindPrecision" );
    }

    ClientTree theTree( var, getOldObjects() );

    std::vector<std::string> commands = theTree.clientReplace( var, newblindvar, *this );
    std::vector<std::string> trashes = theTree.getModifiedObjectNames();

    for ( std::vector<std::string>::iterator iter = commands.begin();
            iter != commands.end(); ++iter) {
        //std::cout << iter->c_str() << std::endl;
        if ( iter->find("EDIT") != std::string::npos ) {
            m_rws->factory( iter->c_str() );
        }
        else {
            std::stringstream msg;
            msg << "Bad RooFactoryWSTool command " << *iter << ".";
            throw GeneralException( "Fitter::blindParameter", msg.str() );
        }
    }

    //put all modified objects in the old objects vector
    for ( std::vector<std::string>::iterator iter = trashes.begin();
            iter != trashes.end(); ++iter ) {
        scrap( iter->c_str() );
    }

}


//=============================================================================
// likesRatioPlot will plot the change in the likelihood profile.
//=============================================================================
/*void Fitter::likesRatioPlot(TString fitName, TString compName, UInt_t toyScaleFactor, UInt_t numBins, Double_t startRange,
  Double_t endRange, Double_t toyCompsLegTextSize,
  Double_t toyCompsLegPosXStart, Double_t toyCompsLegPosYStart,
  Double_t toyCompsLegPosXEnd, Double_t toyCompsLegPosYEnd,
  Bool_t drawDataVsToyLeg, Bool_t drawToyCompsLeg, Bool_t doLog,
  Bool_t useROOTDefaultYAxisRange, Double_t minYAxisValue)
  {
  const RooFitResult* result = this->getFitResult( fitName );
// check that there is a result
if (result == 0) {
std::cerr << "ERROR in Fitter::likesRatioPlot : No fit result to use." << std::endl;
return;
}

// Get the model.
RooAbsPdf* model = dynamic_cast<RooAbsPdf*>( m_rws->pdf( m_modelName ) );
if (!model) {
throw WSRetrievalFailure( "Fitter::likesRatioPlot",
 *m_rws, m_modelName, "RooAbsPdf" );
 }


// form likelihood ratio formula by iterating through components
TString formulaNumStr = "@";
TString formulaDenStr = "@";
Int_t componentNum(0);
Bool_t correctCompNameGiven(kFALSE);
RooArgSet* components = model->getComponents();
TIterator tIter = components->createIterator();
RooAbsPdf
for (vector<FitAbsComponent*>::iterator iter = components_.begin(); iter != components_.end(); ++iter)
{
if ((*iter)->fit())
{
// numerator formula
if ((*iter)->name() == compName)
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
componentNum++;
}
}
if (!correctCompNameGiven)
{
cerr << "ERROR in FitModel::doLLRPlot : Incorrect component given." << endl;
return;
}
TString formulaStr = "(";
formulaStr += formulaNumStr;
formulaStr += ")/(";
formulaStr += formulaDenStr;
formulaStr += ")";
RooFormulaVar likesRatioFunc("likesRatio","",formulaStr,allPdfs_);

// don't want to change data_, so make a copy
RooDataSet* dataset = new RooDataSet(*data_,"dataset");

// histo for data
TH1F LLRHisto_Dat("LLRHisto_Dat","",numBins,startRange,endRange);

// Loop over data events and calculate likelihood ratio for each event, write value to histo
RooRealVar* likesRatio = (RooRealVar*)dataset->addColumn(likesRatioFunc);
for (Int_t i = 0; i < this->getDataNumEntries(); i++)
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
vector<TH1F> componentToyHistos;
vector<TString> componentNames;

// RooArgList required when we create empty RooDataSet* and pass as prototype to the generate method
RooArgList varList("varList");
if (fitVarList_) varList.add(*fitVarList_);
if (otherVarList_) varList.add(*otherVarList_);
if (this->doAsym()) varList.add(*qB_);

// iterate through the components, generate toy, and histogram likelihood ratios
Int_t numComps(0), numeratorComp(-99);
for (vector<FitAbsComponent*>::iterator iter = components_.begin(); iter != components_.end(); ++iter)
{
    if ((*iter)->fit())
    {
        if ((*iter)->name() == compName) {
            numeratorComp = numComps;
        }

        componentNames.push_back((*iter)->name());
        (*iter)->addToyEvents(toyScaleFactor*(static_cast<int>((*iter)->eventsVal())));
        RooDataSet* toyComponentDataSet = new RooDataSet("toyComponentDataSet","toyComponentDataSet",varList);
        toyComponentDataSet = (*iter)->generate(toyComponentDataSet,random_,kFALSE);
        TString toyTH1FName = "LLRHisto_Toy_"; toyTH1FName += (*iter)->name();
        TH1F LLRHisto_Toy_Comp(toyTH1FName,"",numBins,startRange,endRange);
        RooFormulaVar likesRatioFunc_toyComp("likesRatio_toyComp","",formulaStr,allPdfs_);
        RooRealVar* likesRatio_toyComp = (RooRealVar*)toyComponentDataSet->addColumn(likesRatioFunc_toyComp);
        for (UInt_t i = 0; i < (toyScaleFactor*(static_cast<UInt_t>((*iter)->eventsVal()))); i++)
        {
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
}

// make plots
FitLikesRatioPlot likelihoodsPlot(compName);
Double_t toyScaleFactorD = (Double_t)toyScaleFactor;
likelihoodsPlot.dataVsToyPlot(LLRHisto_Dat,componentToyHistos,toyScaleFactorD,numBins,startRange,endRange,drawDataVsToyLeg,doLog,useROOTDefaultYAxisRange,minYAxisValue);
likelihoodsPlot.toyCompsPlot(componentToyHistos,componentNames,numComps,numeratorComp,toyScaleFactorD,numBins,startRange,endRange,toyCompsLegTextSize,toyCompsLegPosXStart,
        toyCompsLegPosYStart,toyCompsLegPosXEnd,toyCompsLegPosYEnd,drawToyCompsLeg,doLog,useROOTDefaultYAxisRange,minYAxisValue);
}*/


//=============================================================================
// getSnapshot returns a const RooArgSet* of the variables in the snapshot if 
// it exists.
//=============================================================================
const RooArgSet* Fitter::getSnapshot( const char* snapName ) const {

    if (!m_rws) {
        throw GeneralException( "Fitter::getSnapshot",
                "No RooWorkspace object is defined" );
    }

    const RooArgSet* params = m_rws->getSnapshot( snapName );

    if( !params ) {
        std::stringstream msg;
        msg << "No snapshot found with name " << snapName;
        throw GeneralException( "Fitter::getSnapshot", msg.str() );
    }

    assert( params );

    return params;
}

//=============================================================================
// mutable version getSnapshot returns a RooArgSet* of the variables in the 
// snapshotit exists.
//=============================================================================
RooArgSet* Fitter::getSnapshot( const char* snapName ) {

    if (!m_rws) {
        throw GeneralException( "Fitter::getSnapshot",
                "No RooWorkspace object is defined" );
    }

    RooArgSet* params = const_cast<RooArgSet*>( m_rws->getSnapshot( snapName ) );

    if( !params ) {
        std::stringstream msg;
        msg << "No snapshot found with name " << snapName;
        throw GeneralException( "Fitter::getSnapshot", msg.str() );
    }

    assert( params );

    return params;
}

//=================================================================================
// Method to produce a new root file from the fit results, in each only the 
// variables considered in the Laura++ package for the KShh DP analysis are saved.
//=================================================================================
void Fitter::saveDPInfo( Double_t Yield_sig_tot, Double_t Yield_bkg_tot, 
        Double_t Yield_cross_tot,  
        const char* fileName, const char* mode, 
        Double_t minRange, Double_t maxRange)
{

    if (!m_rws) {
        throw GeneralException( "Fitter::saveDPInfo",
                "No RooWorkspace object is defined" );
    }

    std::string modesName = mode;
    TFile *file = TFile::Open( fileName, "READ" );
    std::cout << fileName << std::endl;
    std::string treeName_aux = mode;
    std::string KS_type = "";
    if (modesName.find("DD") != std::string::npos){
        KS_type = "DD";
    } else {
        KS_type = "LL";
    }
    m_stringHelper.replaceAll( treeName_aux, "Bd2KS", "" ); 
    m_stringHelper.replaceAll( treeName_aux, "Bs2KS", "" ); 
    m_stringHelper.replaceAll( treeName_aux, "DD", "" ); 
    m_stringHelper.replaceAll( treeName_aux, "LL", "" ); 
    TString treeName = "B2KShh"+KS_type+"/B2"+treeName_aux+"KS";
    TTree* tree =  dynamic_cast<TTree*>( file->Get( treeName ) );

    // Pre-calculaion of the yields 'ratio'
    Double_t totYield_Entries(0), totYields(0), fSig(0.), fBkg(0.), fCross(0.);
    Double_t Yield_sig(0.), Yield_bkg(0.), Yield_cross(0.);

    std::ostringstream strs_min;
    std::ostringstream strs_max;
    strs_min << minRange;
    std::string str_min = strs_min.str();
    strs_max << maxRange;
    std::string str_max = strs_max.str();
    TString minRange_str = str_min;
    TString maxRange_str = str_max;

    totYield_Entries = tree->GetEntries("B_M > "+minRange_str+" && B_M < "+maxRange_str);
    std::cout << "Total Entries = " << totYield_Entries << std::endl;
    totYields = Yield_sig_tot + Yield_bkg_tot + Yield_cross_tot;
    fSig   = Yield_sig_tot/totYields;
    fBkg   = Yield_bkg_tot/totYields;
    fCross = Yield_cross_tot/totYields;
    Yield_sig   = fSig*totYield_Entries;
    Yield_bkg   = fBkg*totYield_Entries;
    Yield_cross = fCross*totYield_Entries;

    Double_t B_M(0.);
    Double_t m12Sq_Bd2pipiKS(0.), m13Sq_Bd2pipiKS(0.), m23Sq_Bd2pipiKS(0.), mPrime_Bd2pipiKS(0.), thPrime_Bd2pipiKS(0.);
    Double_t m12Sq_Bs2pipiKS(0.), m13Sq_Bs2pipiKS(0.), m23Sq_Bs2pipiKS(0.), mPrime_Bs2pipiKS(0.), thPrime_Bs2pipiKS(0.);
    Double_t m12Sq_Bd2KpiKS(0.) , m13Sq_Bd2KpiKS(0.) , m23Sq_Bd2KpiKS(0.) , mPrime_Bd2KpiKS(0.) , thPrime_Bd2KpiKS(0.);
    Double_t m12Sq_Bs2KpiKS(0.) , m13Sq_Bs2KpiKS(0.) , m23Sq_Bs2KpiKS(0.) , mPrime_Bs2KpiKS(0.) , thPrime_Bs2KpiKS(0.);
    Double_t m12Sq_Bd2piKKS(0.) , m13Sq_Bd2piKKS(0.) , m23Sq_Bd2piKKS(0.) , mPrime_Bd2piKKS(0.) , thPrime_Bd2piKKS(0.);
    Double_t m12Sq_Bs2piKKS(0.) , m13Sq_Bs2piKKS(0.) , m23Sq_Bs2piKKS(0.) , mPrime_Bs2piKKS(0.) , thPrime_Bs2piKKS(0.);
    Double_t m12Sq_Bd2KKKS(0.)  , m13Sq_Bd2KKKS(0.)  , m23Sq_Bd2KKKS(0.)  , mPrime_Bd2KKKS(0.)  , thPrime_Bd2KKKS(0.);
    Double_t m12Sq_Bs2KKKS(0.)  , m13Sq_Bs2KKKS(0.)  , m23Sq_Bs2KKKS(0.)  , mPrime_Bs2KKKS(0.)  , thPrime_Bs2KKKS(0.);

    tree->SetBranchAddress("m12Sq_Bd2pipiKS"  , &m12Sq_Bd2pipiKS);
    tree->SetBranchAddress("m13Sq_Bd2pipiKS"  , &m13Sq_Bd2pipiKS);
    tree->SetBranchAddress("m23Sq_Bd2pipiKS"  , &m23Sq_Bd2pipiKS);
    tree->SetBranchAddress("mPrime_Bd2pipiKS" , &mPrime_Bd2pipiKS);
    tree->SetBranchAddress("thPrime_Bd2pipiKS", &thPrime_Bd2pipiKS);
    tree->SetBranchAddress("m12Sq_Bd2KpiKS"   , &m12Sq_Bd2KpiKS);
    tree->SetBranchAddress("m13Sq_Bd2KpiKS"   , &m13Sq_Bd2KpiKS);
    tree->SetBranchAddress("m23Sq_Bd2KpiKS"   , &m23Sq_Bd2KpiKS);
    tree->SetBranchAddress("mPrime_Bd2KpiKS"  , &mPrime_Bd2KpiKS);
    tree->SetBranchAddress("thPrime_Bd2KpiKS" , &thPrime_Bd2KpiKS);
    tree->SetBranchAddress("m12Sq_Bd2piKKS"   , &m12Sq_Bd2piKKS);
    tree->SetBranchAddress("m13Sq_Bd2piKKS"   , &m13Sq_Bd2piKKS);
    tree->SetBranchAddress("m23Sq_Bd2piKKS"   , &m23Sq_Bd2piKKS);
    tree->SetBranchAddress("mPrime_Bd2piKKS"  , &mPrime_Bd2piKKS);
    tree->SetBranchAddress("thPrime_Bd2piKKS" , &thPrime_Bd2piKKS);
    tree->SetBranchAddress("m12Sq_Bd2KKKS"    , &m12Sq_Bd2KKKS);
    tree->SetBranchAddress("m13Sq_Bd2KKKS"    , &m13Sq_Bd2KKKS);
    tree->SetBranchAddress("m23Sq_Bd2KKKS"    , &m23Sq_Bd2KKKS);
    tree->SetBranchAddress("mPrime_Bd2KKKS"   , &mPrime_Bd2KKKS);
    tree->SetBranchAddress("thPrime_Bd2KKKS"  , &thPrime_Bd2KKKS);
    tree->SetBranchAddress("m12Sq_Bs2pipiKS"  , &m12Sq_Bs2pipiKS);
    tree->SetBranchAddress("m13Sq_Bs2pipiKS"  , &m13Sq_Bs2pipiKS);
    tree->SetBranchAddress("m23Sq_Bs2pipiKS"  , &m23Sq_Bs2pipiKS);
    tree->SetBranchAddress("mPrime_Bs2pipiKS" , &mPrime_Bs2pipiKS);
    tree->SetBranchAddress("thPrime_Bs2pipiKS", &thPrime_Bs2pipiKS);
    tree->SetBranchAddress("m12Sq_Bs2KpiKS"   , &m12Sq_Bs2KpiKS);
    tree->SetBranchAddress("m13Sq_Bs2KpiKS"   , &m13Sq_Bs2KpiKS);
    tree->SetBranchAddress("m23Sq_Bs2KpiKS"   , &m23Sq_Bs2KpiKS);
    tree->SetBranchAddress("mPrime_Bs2KpiKS"  , &mPrime_Bs2KpiKS);
    tree->SetBranchAddress("thPrime_Bs2KpiKS" , &thPrime_Bs2KpiKS);
    tree->SetBranchAddress("m12Sq_Bs2KpiKS"   , &m12Sq_Bs2KpiKS);
    tree->SetBranchAddress("m12Sq_Bs2piKKS"   , &m12Sq_Bs2piKKS);
    tree->SetBranchAddress("m13Sq_Bs2piKKS"   , &m13Sq_Bs2piKKS);
    tree->SetBranchAddress("m23Sq_Bs2piKKS"   , &m23Sq_Bs2piKKS);
    tree->SetBranchAddress("mPrime_Bs2piKKS"  , &mPrime_Bs2piKKS);
    tree->SetBranchAddress("thPrime_Bs2piKKS" , &thPrime_Bs2piKKS);
    tree->SetBranchAddress("m12Sq_Bs2KKKS"    , &m12Sq_Bs2KKKS);
    tree->SetBranchAddress("m13Sq_Bs2KKKS"    , &m13Sq_Bs2KKKS);
    tree->SetBranchAddress("m23Sq_Bs2KKKS"    , &m23Sq_Bs2KKKS);
    tree->SetBranchAddress("mPrime_Bs2KKKS"   , &mPrime_Bs2KKKS);
    tree->SetBranchAddress("thPrime_Bs2KKKS"  , &thPrime_Bs2KKKS);

    tree->SetBranchAddress("B_M", &B_M);

    std::string fileName_aux = fileName;
    m_stringHelper.replaceAll( fileName_aux, ".root", "" ); 
    TString new_fileName = fileName_aux+"_"+mode+".root";
    TFile* newFile = new TFile(new_fileName, "RECREATE");
    TTree *fitResults = new TTree("fitResults", "fitResults");

    Double_t m12(0.), m13(0.), m23(0.), m12Sq(0.), m13Sq(0.), m23Sq(0.); 
    Double_t mPrime(0.), thPrime(0.);
    Int_t iExpt(0);

    fitResults->Branch("m12",        &m12);
    fitResults->Branch("m12Sq",      &m12Sq);
    fitResults->Branch("m13",        &m13);
    fitResults->Branch("m13Sq",      &m13Sq);
    fitResults->Branch("m23",        &m23);
    fitResults->Branch("m23Sq",      &m23Sq);
    fitResults->Branch("mPrime",     &mPrime);
    fitResults->Branch("thPrime",    &thPrime);
    fitResults->Branch("Yield_sig",  &Yield_sig);
    fitResults->Branch("Yield_bkg",  &Yield_bkg);
    fitResults->Branch("Yield_cross",&Yield_cross);
    fitResults->Branch("B_M",        &B_M);
    fitResults->Branch("iExpt",      &iExpt);

    for(int ievent=0; ievent< tree->GetEntries(); ievent++) {
        Long64_t nbytes = tree->GetEntry(ievent);
        if (nbytes < 0) break;

        if (modesName.find("Bd2KSpipi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2pipiKS/10e5);
            m12Sq   = m12Sq_Bd2pipiKS/10e5;
            m13     = sqrt(m13Sq_Bd2pipiKS/10e5);
            m13Sq   = m13Sq_Bd2pipiKS/10e5;
            m23     = sqrt(m23Sq_Bd2pipiKS/10e5);
            m23Sq   = m23Sq_Bd2pipiKS/10e5;
            mPrime  = mPrime_Bd2pipiKS; 
            thPrime = thPrime_Bd2pipiKS; 
        } else if (modesName.find("Bs2KSpipi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2pipiKS/10e5);
            m12Sq   = m12Sq_Bs2pipiKS/10e5;
            m13     = sqrt(m13Sq_Bs2pipiKS/10e5);
            m13Sq   = m13Sq_Bs2pipiKS/10e5;
            m23     = sqrt(m23Sq_Bs2pipiKS/10e5);
            m23Sq   = m23Sq_Bs2pipiKS/10e5;
            mPrime  = mPrime_Bs2pipiKS; 
            thPrime = thPrime_Bs2pipiKS; 
        } else if (modesName.find("Bd2KSKpi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2KpiKS/10e5);
            m12Sq   = m12Sq_Bd2KpiKS/10e5;
            m13     = sqrt(m13Sq_Bd2KpiKS/10e5);
            m13Sq   = m13Sq_Bd2KpiKS/10e5;
            m23     = sqrt(m23Sq_Bd2KpiKS/10e5);
            m23Sq   = m23Sq_Bd2KpiKS/10e5;
            mPrime  = mPrime_Bd2KpiKS; 
            thPrime = thPrime_Bd2KpiKS; 
        } else if (modesName.find("Bs2KSKpi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2KpiKS/10e5);
            m12Sq   = m12Sq_Bs2KpiKS/10e5;
            m13     = sqrt(m13Sq_Bs2KpiKS/10e5);
            m13Sq   = m13Sq_Bs2KpiKS/10e5;
            m23     = sqrt(m23Sq_Bs2KpiKS/10e5);
            m23Sq   = m23Sq_Bs2KpiKS/10e5;
            mPrime  = mPrime_Bs2KpiKS; 
            thPrime = thPrime_Bs2KpiKS; 
        } else if (modesName.find("Bd2KSpiK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2piKKS/10e5);
            m12Sq   = m12Sq_Bd2piKKS/10e5;
            m13     = sqrt(m13Sq_Bd2piKKS/10e5);
            m13Sq   = m13Sq_Bd2piKKS/10e5;
            m23     = sqrt(m23Sq_Bd2piKKS/10e5);
            m23Sq   = m23Sq_Bd2piKKS/10e5;
            mPrime  = mPrime_Bd2piKKS; 
            thPrime = thPrime_Bd2piKKS; 
        } else if (modesName.find("Bs2KSpiK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2piKKS/10e5);
            m12Sq   = m12Sq_Bs2piKKS/10e5;
            m13     = sqrt(m13Sq_Bs2piKKS/10e5);
            m13Sq   = m13Sq_Bs2piKKS/10e5;
            m23     = sqrt(m23Sq_Bs2piKKS/10e5);
            m23Sq   = m23Sq_Bs2piKKS/10e5;
            mPrime  = mPrime_Bs2piKKS; 
            thPrime = thPrime_Bs2piKKS; 
        } else if (modesName.find("Bd2KSKK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2KKKS/10e5);
            m12Sq   = m12Sq_Bd2KKKS/10e5;
            m13     = sqrt(m13Sq_Bd2KKKS/10e5);
            m13Sq   = m13Sq_Bd2KKKS/10e5;
            m23     = sqrt(m23Sq_Bd2KKKS/10e5);
            m23Sq   = m23Sq_Bd2KKKS/10e5;
            mPrime  = mPrime_Bd2KKKS; 
            thPrime = thPrime_Bd2KKKS; 
        } else if (modesName.find("Bs2KSKK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2KKKS/10e5);
            m12Sq   = m12Sq_Bs2KKKS/10e5;
            m13     = sqrt(m13Sq_Bs2KKKS/10e5);
            m13Sq   = m13Sq_Bs2KKKS/10e5;
            m23     = sqrt(m23Sq_Bs2KKKS/10e5);
            m23Sq   = m23Sq_Bs2KKKS/10e5;
            mPrime  = mPrime_Bs2KKKS; 
            thPrime = thPrime_Bs2KKKS; 
        }
        iExpt   = 0;
        if ( B_M > minRange  && B_M < maxRange ) {
            fitResults->Fill();
        }
    }


    fitResults->Write("", TObject::kOverwrite);
    newFile->Close();

}

//=================================================================================
// Method to produce a new root file from the fit results, in each only the 
// variables considered in the Laura++ package for the KShh DP analysis are saved.
//=================================================================================
void Fitter::saveDPInfo_Syst( Double_t Yield_sig_tot, Double_t Yield_bkg_tot, 
        Double_t Yield_cross_tot,  
        const char* fileName, const char* mode, 
        Double_t minRange, Double_t maxRange)
{

    if (!m_rws) {
        throw GeneralException( "Fitter::saveDPInfo",
                "No RooWorkspace object is defined" );
    }

    std::cout << "HERE! : " << fileName << std::endl;
    std::string modesName = mode;
    TFile *file = TFile::Open( fileName, "READ" );
    std::cout << fileName << std::endl;
    std::string treeName_aux = mode;
    std::string KS_type = "";
    if (modesName.find("DD") != std::string::npos){
        KS_type = "DD";
    } else {
        KS_type = "LL";
    }
    m_stringHelper.replaceAll( treeName_aux, "Bd2KS", "" ); 
    m_stringHelper.replaceAll( treeName_aux, "Bs2KS", "" ); 
    m_stringHelper.replaceAll( treeName_aux, "DD", "" ); 
    m_stringHelper.replaceAll( treeName_aux, "LL", "" ); 
    TString treeName = "B2KShh"+KS_type+"/B2"+treeName_aux+"KS";
    TTree* tree =  dynamic_cast<TTree*>( file->Get( treeName ) );

    // Pre-calculaion of the yields 'ratio'
    Double_t totYield_Entries(0), totYields(0), fSig(0.), fBkg(0.), fCross(0.);
    Double_t Yield_sig(0.), Yield_bkg(0.), Yield_cross(0.);
    std::ostringstream strs_min;
    std::ostringstream strs_max;
    strs_min << minRange;
    std::string str_min = strs_min.str();
    strs_max << maxRange;
    std::string str_max = strs_max.str();
    TString minRange_str = str_min;
    TString maxRange_str = str_max;

    std::string Ref_aux = fileName;
    m_stringHelper.replaceAll( Ref_aux, ".root", "_Bs2KS"+treeName_aux+KS_type+"_Ref.root" ); 
    TString refFileName = Ref_aux;
    TFile *fileRef = TFile::Open( refFileName, "READ" );
    TTree* treeRef =  dynamic_cast<TTree*>( fileRef->Get( "fitResults" ) );
    totYield_Entries = treeRef->GetEntries();
    totYields = Yield_sig_tot + Yield_bkg_tot + Yield_cross_tot;
    fSig   = Yield_sig_tot/totYields;
    fBkg   = Yield_bkg_tot/totYields;
    fCross = Yield_cross_tot/totYields;
    Yield_sig   = fSig*totYield_Entries;
    Yield_bkg   = fBkg*totYield_Entries;
    Yield_cross = fCross*totYield_Entries;

    Double_t B_M(0.);
    Double_t m12Sq_Bd2pipiKS(0.), m13Sq_Bd2pipiKS(0.), m23Sq_Bd2pipiKS(0.), mPrime_Bd2pipiKS(0.), thPrime_Bd2pipiKS(0.);
    Double_t m12Sq_Bs2pipiKS(0.), m13Sq_Bs2pipiKS(0.), m23Sq_Bs2pipiKS(0.), mPrime_Bs2pipiKS(0.), thPrime_Bs2pipiKS(0.);
    Double_t m12Sq_Bd2KpiKS(0.) , m13Sq_Bd2KpiKS(0.) , m23Sq_Bd2KpiKS(0.) , mPrime_Bd2KpiKS(0.) , thPrime_Bd2KpiKS(0.);
    Double_t m12Sq_Bs2KpiKS(0.) , m13Sq_Bs2KpiKS(0.) , m23Sq_Bs2KpiKS(0.) , mPrime_Bs2KpiKS(0.) , thPrime_Bs2KpiKS(0.);
    Double_t m12Sq_Bd2piKKS(0.) , m13Sq_Bd2piKKS(0.) , m23Sq_Bd2piKKS(0.) , mPrime_Bd2piKKS(0.) , thPrime_Bd2piKKS(0.);
    Double_t m12Sq_Bs2piKKS(0.) , m13Sq_Bs2piKKS(0.) , m23Sq_Bs2piKKS(0.) , mPrime_Bs2piKKS(0.) , thPrime_Bs2piKKS(0.);
    Double_t m12Sq_Bd2KKKS(0.)  , m13Sq_Bd2KKKS(0.)  , m23Sq_Bd2KKKS(0.)  , mPrime_Bd2KKKS(0.)  , thPrime_Bd2KKKS(0.);
    Double_t m12Sq_Bs2KKKS(0.)  , m13Sq_Bs2KKKS(0.)  , m23Sq_Bs2KKKS(0.)  , mPrime_Bs2KKKS(0.)  , thPrime_Bs2KKKS(0.);

    tree->SetBranchAddress("m12Sq_Bd2pipiKS"  , &m12Sq_Bd2pipiKS);
    tree->SetBranchAddress("m13Sq_Bd2pipiKS"  , &m13Sq_Bd2pipiKS);
    tree->SetBranchAddress("m23Sq_Bd2pipiKS"  , &m23Sq_Bd2pipiKS);
    tree->SetBranchAddress("mPrime_Bd2pipiKS" , &mPrime_Bd2pipiKS);
    tree->SetBranchAddress("thPrime_Bd2pipiKS", &thPrime_Bd2pipiKS);
    tree->SetBranchAddress("m12Sq_Bd2KpiKS"   , &m12Sq_Bd2KpiKS);
    tree->SetBranchAddress("m13Sq_Bd2KpiKS"   , &m13Sq_Bd2KpiKS);
    tree->SetBranchAddress("m23Sq_Bd2KpiKS"   , &m23Sq_Bd2KpiKS);
    tree->SetBranchAddress("mPrime_Bd2KpiKS"  , &mPrime_Bd2KpiKS);
    tree->SetBranchAddress("thPrime_Bd2KpiKS" , &thPrime_Bd2KpiKS);
    tree->SetBranchAddress("m12Sq_Bd2piKKS"   , &m12Sq_Bd2piKKS);
    tree->SetBranchAddress("m13Sq_Bd2piKKS"   , &m13Sq_Bd2piKKS);
    tree->SetBranchAddress("m23Sq_Bd2piKKS"   , &m23Sq_Bd2piKKS);
    tree->SetBranchAddress("mPrime_Bd2piKKS"  , &mPrime_Bd2piKKS);
    tree->SetBranchAddress("thPrime_Bd2piKKS" , &thPrime_Bd2piKKS);
    tree->SetBranchAddress("m12Sq_Bd2KKKS"    , &m12Sq_Bd2KKKS);
    tree->SetBranchAddress("m13Sq_Bd2KKKS"    , &m13Sq_Bd2KKKS);
    tree->SetBranchAddress("m23Sq_Bd2KKKS"    , &m23Sq_Bd2KKKS);
    tree->SetBranchAddress("mPrime_Bd2KKKS"   , &mPrime_Bd2KKKS);
    tree->SetBranchAddress("thPrime_Bd2KKKS"  , &thPrime_Bd2KKKS);
    tree->SetBranchAddress("m12Sq_Bs2pipiKS"  , &m12Sq_Bs2pipiKS);
    tree->SetBranchAddress("m13Sq_Bs2pipiKS"  , &m13Sq_Bs2pipiKS);
    tree->SetBranchAddress("m23Sq_Bs2pipiKS"  , &m23Sq_Bs2pipiKS);
    tree->SetBranchAddress("mPrime_Bs2pipiKS" , &mPrime_Bs2pipiKS);
    tree->SetBranchAddress("thPrime_Bs2pipiKS", &thPrime_Bs2pipiKS);
    tree->SetBranchAddress("m12Sq_Bs2KpiKS"   , &m12Sq_Bs2KpiKS);
    tree->SetBranchAddress("m13Sq_Bs2KpiKS"   , &m13Sq_Bs2KpiKS);
    tree->SetBranchAddress("m23Sq_Bs2KpiKS"   , &m23Sq_Bs2KpiKS);
    tree->SetBranchAddress("mPrime_Bs2KpiKS"  , &mPrime_Bs2KpiKS);
    tree->SetBranchAddress("thPrime_Bs2KpiKS" , &thPrime_Bs2KpiKS);
    tree->SetBranchAddress("m12Sq_Bs2KpiKS"   , &m12Sq_Bs2KpiKS);
    tree->SetBranchAddress("m12Sq_Bs2piKKS"   , &m12Sq_Bs2piKKS);
    tree->SetBranchAddress("m13Sq_Bs2piKKS"   , &m13Sq_Bs2piKKS);
    tree->SetBranchAddress("m23Sq_Bs2piKKS"   , &m23Sq_Bs2piKKS);
    tree->SetBranchAddress("mPrime_Bs2piKKS"  , &mPrime_Bs2piKKS);
    tree->SetBranchAddress("thPrime_Bs2piKKS" , &thPrime_Bs2piKKS);
    tree->SetBranchAddress("m12Sq_Bs2KKKS"    , &m12Sq_Bs2KKKS);
    tree->SetBranchAddress("m13Sq_Bs2KKKS"    , &m13Sq_Bs2KKKS);
    tree->SetBranchAddress("m23Sq_Bs2KKKS"    , &m23Sq_Bs2KKKS);
    tree->SetBranchAddress("mPrime_Bs2KKKS"   , &mPrime_Bs2KKKS);
    tree->SetBranchAddress("thPrime_Bs2KKKS"  , &thPrime_Bs2KKKS);

    tree->SetBranchAddress("B_M", &B_M);

    std::string fileName_aux = fileName;
    m_stringHelper.replaceAll( fileName_aux, ".root", "" ); 
    TString new_fileName = fileName_aux+"_"+mode+"_SystII_sigShape.root";
    TFile* newFile = new TFile(new_fileName, "RECREATE");
    TTree *fitResults = new TTree("fitResults", "fitResults");

    Double_t m12(0.), m13(0.), m23(0.), m12Sq(0.), m13Sq(0.), m23Sq(0.); 
    Double_t mPrime(0.), thPrime(0.);
    Int_t iExpt(0);

    fitResults->Branch("m12",        &m12);
    fitResults->Branch("m12Sq",      &m12Sq);
    fitResults->Branch("m13",        &m13);
    fitResults->Branch("m13Sq",      &m13Sq);
    fitResults->Branch("m23",        &m23);
    fitResults->Branch("m23Sq",      &m23Sq);
    fitResults->Branch("mPrime",     &mPrime);
    fitResults->Branch("thPrime",    &thPrime);
    fitResults->Branch("Yield_sig",  &Yield_sig);
    fitResults->Branch("Yield_bkg",  &Yield_bkg);
    fitResults->Branch("Yield_cross",&Yield_cross);
    fitResults->Branch("B_M",        &B_M);
    fitResults->Branch("iExpt",      &iExpt);

    for(int ievent=0; ievent< tree->GetEntries(); ievent++) {
        Long64_t nbytes = tree->GetEntry(ievent);
        if (nbytes < 0) break;

        if (modesName.find("Bd2KSpipi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2pipiKS/10e5);
            m12Sq   = m12Sq_Bd2pipiKS/10e5;
            m13     = sqrt(m13Sq_Bd2pipiKS/10e5);
            m13Sq   = m13Sq_Bd2pipiKS/10e5;
            m23     = sqrt(m23Sq_Bd2pipiKS/10e5);
            m23Sq   = m23Sq_Bd2pipiKS/10e5;
            mPrime  = mPrime_Bd2pipiKS; 
            thPrime = thPrime_Bd2pipiKS; 
        } else if (modesName.find("Bs2KSpipi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2pipiKS/10e5);
            m12Sq   = m12Sq_Bs2pipiKS/10e5;
            m13     = sqrt(m13Sq_Bs2pipiKS/10e5);
            m13Sq   = m13Sq_Bs2pipiKS/10e5;
            m23     = sqrt(m23Sq_Bs2pipiKS/10e5);
            m23Sq   = m23Sq_Bs2pipiKS/10e5;
            mPrime  = mPrime_Bs2pipiKS; 
            thPrime = thPrime_Bs2pipiKS; 
        } else if (modesName.find("Bd2KSKpi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2KpiKS/10e5);
            m12Sq   = m12Sq_Bd2KpiKS/10e5;
            m13     = sqrt(m13Sq_Bd2KpiKS/10e5);
            m13Sq   = m13Sq_Bd2KpiKS/10e5;
            m23     = sqrt(m23Sq_Bd2KpiKS/10e5);
            m23Sq   = m23Sq_Bd2KpiKS/10e5;
            mPrime  = mPrime_Bd2KpiKS; 
            thPrime = thPrime_Bd2KpiKS; 
        } else if (modesName.find("Bs2KSKpi") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2KpiKS/10e5);
            m12Sq   = m12Sq_Bs2KpiKS/10e5;
            m13     = sqrt(m13Sq_Bs2KpiKS/10e5);
            m13Sq   = m13Sq_Bs2KpiKS/10e5;
            m23     = sqrt(m23Sq_Bs2KpiKS/10e5);
            m23Sq   = m23Sq_Bs2KpiKS/10e5;
            mPrime  = mPrime_Bs2KpiKS; 
            thPrime = thPrime_Bs2KpiKS; 
        } else if (modesName.find("Bd2KSpiK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2piKKS/10e5);
            m12Sq   = m12Sq_Bd2piKKS/10e5;
            m13     = sqrt(m13Sq_Bd2piKKS/10e5);
            m13Sq   = m13Sq_Bd2piKKS/10e5;
            m23     = sqrt(m23Sq_Bd2piKKS/10e5);
            m23Sq   = m23Sq_Bd2piKKS/10e5;
            mPrime  = mPrime_Bd2piKKS; 
            thPrime = thPrime_Bd2piKKS; 
        } else if (modesName.find("Bs2KSpiK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2piKKS/10e5);
            m12Sq   = m12Sq_Bs2piKKS/10e5;
            m13     = sqrt(m13Sq_Bs2piKKS/10e5);
            m13Sq   = m13Sq_Bs2piKKS/10e5;
            m23     = sqrt(m23Sq_Bs2piKKS/10e5);
            m23Sq   = m23Sq_Bs2piKKS/10e5;
            mPrime  = mPrime_Bs2piKKS; 
            thPrime = thPrime_Bs2piKKS; 
        } else if (modesName.find("Bd2KSKK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bd2KKKS/10e5);
            m12Sq   = m12Sq_Bd2KKKS/10e5;
            m13     = sqrt(m13Sq_Bd2KKKS/10e5);
            m13Sq   = m13Sq_Bd2KKKS/10e5;
            m23     = sqrt(m23Sq_Bd2KKKS/10e5);
            m23Sq   = m23Sq_Bd2KKKS/10e5;
            mPrime  = mPrime_Bd2KKKS; 
            thPrime = thPrime_Bd2KKKS; 
        } else if (modesName.find("Bs2KSKK") != std::string::npos) {
            m12     = sqrt(m12Sq_Bs2KKKS/10e5);
            m12Sq   = m12Sq_Bs2KKKS/10e5;
            m13     = sqrt(m13Sq_Bs2KKKS/10e5);
            m13Sq   = m13Sq_Bs2KKKS/10e5;
            m23     = sqrt(m23Sq_Bs2KKKS/10e5);
            m23Sq   = m23Sq_Bs2KKKS/10e5;
            mPrime  = mPrime_Bs2KKKS; 
            thPrime = thPrime_Bs2KKKS; 
        }
        iExpt   = 0;
        if ( B_M > minRange  && B_M < maxRange ) {
            fitResults->Fill();
        }
    }


    fitResults->Write("", TObject::kOverwrite);
    newFile->Close();

}


//=============================================================================
// Destructor
//=============================================================================
void Fitter::setGlobalKillBelowError( RooFit::MsgLevel msg ) {

    RooMsgService::instance().setGlobalKillBelow( msg );
}

//=============================================================================
// Destructor
//=============================================================================
Fitter::~Fitter()
{
    if ( m_hasOwnership && m_rws )
    {
        // If we created the RooWorkspace, then we are in charge of deleting it.
        // If it was loaded from a TFile, then it will be deleted automatically
        // when the file is closed.
        delete m_rws; m_rws=0;
    }
    //m_file->Close();
    delete m_file; m_file=0;
}
//=============================================================================
