#include <iterator>     // std::distance
#include <ctime>

// Local include
#include "V0hhFitter/ToyStudy.h"
#include "V0hhFitter/string_tools.h"

// RooFit 
#include "RooLinkedListIter.h"
#include "Roo1DTable.h"
#include "RooAbsCategory.h"
#include "RooAbsReal.h"
#include "RooAbsCollection.h"
#include "RooCategory.h"
#include "RooCatType.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooMsgService.h"

// ROOT
#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "TRandom3.h"

// TMVA used for timer
#include "TMVA/Timer.h"

using namespace V0hhFit;


ToyStudy::ToyStudy( Fitter* fitter, Int_t nSamples, Int_t mSystematics, Int_t seed ) :
    m_stringHelper(), m_fitter(fitter),
    m_nSamples( nSamples ), m_mSystematics( mSystematics ),
    m_dataResult(0), m_result(0), m_seed(seed), m_datafitResultName("fitResults"),
    m_toyfitParamsName("toy_params"), m_systematicParamsName("systematic_params") 
{}

ToyStudy::~ToyStudy() 
{
    if( m_result ) {
        //delete m_result; m_result=0;
    }
    if( m_dataResult ) {
        //delete m_dataResult; m_dataResult=0;
    }
}

//=============================================================================
// Saves all the results in a TFile. Deletes them afterwards as they are no
// more needed.
//=============================================================================
void ToyStudy::saveResults(const char* fileName) const
{
    TFile *f  = TFile::Open(fileName,"RECREATE");
    for (std::vector<RooFitResult*>::const_iterator it = m_allFitResults.begin() ; it != m_allFitResults.end() ; it++)
        (*it)->Write();
    f->Save();
    f->Close();
    std::cout << "Results saved!" << std::endl;
}

//=============================================================================
// MIGRAD is able to find the minimum of your parameter space, however it can 
// be subject to localised minima. A cross-check for this is to change the 
// initial values of the fit and perform the fit again. If the true global 
// minimum has been found then the function returns true.
//=============================================================================
bool ToyStudy::localMinimumChecker( const char* fitName, Int_t n,  
        Fitter::RandomMethod method, Double_t edmTol, Bool_t extendedMode, Bool_t useMinos, Bool_t useSumW2Errors, 
        Bool_t printResults) 
{ 

    // need to refit having set the initial parameters to some new values.
    // first need the original fit model
    RooFitResult* theresult = dynamic_cast<RooFitResult*>( m_fitter->getFitResult( fitName ) );
    if (!theresult){
        std::stringstream msg;
        msg << "fit called " << fitName << " has not been performed.";
        throw GeneralException("ToyStudy::localMinimumChecker", msg.str() ); 
    }

    TRandom3 rand(m_seed*m_seed);

    double bestNll = theresult->minNll(), thisnll(bestNll), minnll(thisnll);

    m_fitter->loadSnapshot( fitName );
    std::vector< RooFitResult* > listOfNewMinNllFits;
    bool success(false);

    string_tools stringHelper;

    RooFit::MsgLevel msg = RooMsgService::instance().globalKillBelow();
    m_fitter->setGlobalKillBelowError( RooFit::ERROR ); // Make it quiet

    Int_t fail_counter(0);
    TMVA::Timer timer( n, "ToyStudy::localMinimumChecker" );
    for ( Int_t i(0); i < n; ++i ) {
        // new random seed.
        m_seed += i;

        // load the original fit parameters
        m_fitter->loadSnapshot( fitName );

        // randomise the initial parameters based on their error
        m_fitter->wiggleAllParams( m_seed, method, fitName );
        //randomiseFitParams( method );

        std::string name = "localMinimumChecker_" + stringHelper.to_string<int>(i);
        // do the fit
        m_fitter->performFit( name.c_str() , 
                useMinos, // default is to use minos, this can sometimes lead to improved minima
                // but can also lead to numerical instability.... hmmn user can decide!
                kFALSE, // never verbose, could make it an option...
                kFALSE, // do not save a snapshot
                printResults, //print the fitResult each time.
                useSumW2Errors,
                extendedMode
                ) ;

        // Get the fit result and see if it is better than the nominal fit
        //RooFitResult* res = m_fitter->getFitResult( name.c_str() );

        thisnll = m_fitter->getFitResult( name.c_str() )->minNll();
        success = ( m_fitter->getFitResult( name.c_str() )->covQual()==3 
                && m_fitter->getFitResult( name.c_str() )->edm() < edmTol 
                && m_fitter->getFitResult( name.c_str() )->status() == 0 );
        if(!success) {
            ++fail_counter;
        }
        if (thisnll < minnll) { 
            minnll = thisnll ;
            listOfNewMinNllFits.push_back( m_fitter->getFitResult( name.c_str() ) );
        }

        timer.DrawProgressBar( i );
    }

    std::cout << "INFO: ToyStudy::localMinimumChecker - Requested " << n << " fits, where " << fail_counter << " failed to converge."  << std::endl;

    bool status(false);
    // get the size of the 
    if( listOfNewMinNllFits.empty() ) {
        status = true;
    } 
    else {

        RooArgList nominalNllFit( theresult->floatParsFinal() );

        // IT WOULD NE NEAT TO HAVE SOME DETAIL ANALYSIS OF THE VARIABLES AND THE ORIGINAL 
        // FITTED VALUES COMPARED TO THE NOMINAL HERE!!!!
        // Clean up if necessary too might aswell!
        std::cout << "INFO: ToyStudy::localMinimumChecker - Nominal fit returns nll value of " << bestNll << std::endl;
        std::cout << "INFO: ToyStudy::localMinimumChecker - " << listOfNewMinNllFits.size() << " better nll values were found" << std::endl;

        // sort the function
        std::sort( listOfNewMinNllFits.begin(), listOfNewMinNllFits.end(), CompareFitResultFunctor() );

        std::vector< RooFitResult* >::iterator iter = listOfNewMinNllFits.begin();
        const std::vector< RooFitResult* >::const_iterator enditer =  listOfNewMinNllFits.end();
        for(; iter != enditer; ++iter ) {

            size_t position = std::distance( listOfNewMinNllFits.begin(), iter );
            RooArgList newNllFit( (*iter)->floatParsFinal() ) ;

            std::cout << "INFO: ToyStudy::localMinimumChecker - " << position + 1<< ": found a better nll value by " << bestNll - (*iter)->minNll() << std::endl;
            std::cout << "     Variable      |    Nominal Value    |    New Value    |    Difference  " << std::endl;
            std::cout << " -----------------   -------------------   ---------------   --------------" << std::endl;

            RooAbsReal* nomVar = 0;
            RooAbsReal* altVar = 0;

            TIterator* nomIt = nominalNllFit.createIterator();
            TIterator* altIt = newNllFit.createIterator();
            while ( (nomVar = dynamic_cast<RooAbsReal*>( nomIt->Next() ) ) 
                    && ( altVar = dynamic_cast<RooAbsReal*>( altIt->Next() ) ) ) {

                if( TString(nomVar->GetName()) != TString(altVar->GetName()) ) {
                    std::stringstream msg;
                    msg << "Variables " << nomVar->GetName() << " and " << altVar->GetName() << " are not the same, something has gone wrong as variables should be the same.";
                    throw GeneralException("ToyStudy::localMinimumChecker", msg.str() ); 
                }

                if ( nomVar->getVal() != altVar->getVal() ) {
                    double diff = nomVar->getVal() - altVar->getVal();
                    std::cout << nomVar->GetName() << "    |    " << nomVar->getVal() << "    |    " << 
                        altVar->getVal() << "    |    " << diff << std::endl;
                }
            }

            std::cout << " --------------------------------------------------------------------------" << std::endl;

            delete nomIt; nomIt=0;
            delete altIt; altIt=0;

            (*iter)->Print("V");
            std::cout << std::endl;
            std::cout << std::endl;

        }    
    }

    m_fitter->setGlobalKillBelowError( msg ); // Reset the verbosity

    return status;

}

//=============================================================================
// Puts the generated values for each yield in data into the argset.
// Used in runToyStudy to monitor the fitting without poissonization.
//=============================================================================
void ToyStudy::actualizeYields( RooAbsData* data) const
{
    //Normally there should be only one RooCategory object in there. If not, we're running into trouble.
    const RooArgSet* args = data->get();
    TIterator *iter = args->createIterator();
    RooAbsCategory *cat = NULL;
    while(TObject* temp = iter->Next())
    {
        if (temp->InheritsFrom("RooAbsCategory"))
        {
            if (cat == NULL)
                cat = (RooAbsCategory*) temp;
            else
            {
                std::stringstream msg;
                msg << "More than one category found in the dataset " 
                    << data->GetName() << ": " <<std::endl
                    << cat->GetName() << std::endl
                    << temp->GetName() << std::endl;
                throw GeneralException("ToyStudy::actualizeYields",msg.str());
            }
        }
    }
    if (!cat)
    {
        std::stringstream msg;
        msg << "No category found in the dataset!";
        throw GeneralException("ToyStudy::actualizeYields",msg.str());
    }
    int numTypes = cat->numTypes();  
    for (int i = 0 ; i < numTypes ; ++i)
    {
        const RooCatType* tempCatType = cat->lookupType(i);
        //We should have a corresponding yield in the params.
        TString tempName = TString(tempCatType->GetName())+"_pdf_"+tempCatType->GetName()+"_Yield";
        TString cut = TString(cat->GetName())+"=="+cat->GetName()+"::"+tempCatType->GetName();
        //Insert a test for the presence of the yield.
        //double testVal = params->getRealValue(tempName.Data());
        //bool flag = params->setRealValue(tempName.Data(),
        //        ((data->reduce(RooFit::Cut(cut)) )) -> sumEntries(),
        //        kTRUE);
        //      if (!flag)     
        //	{
        //	  std::stringstream msg;
        //	  msg << "Variable " << tempName << " not found in the RooArgSet.";
        //	  throw GeneralException("ToyStudy::actualizeYields",msg.str());
        //	}     
    }
}

//=============================================================================
// Does a MC study on the pdf. 
// Sets seed for random generator (to enable many small independent toy studies
// to be done in parallel).
// Allows individual yield parameters to be set explicitly
//=============================================================================
void ToyStudy::runToyStudy_DP( const char* fitName, std::string setyields, std::string setFixedPars)  
{
    m_datafitResultName = fitName;
    std::vector<std::string> args; // Check if we're setting multiple parameters to new values.

    m_stringHelper.replaceAll( setyields, " ", "" ); // removes all whitespace
    if( setyields != "" ) {
        m_stringHelper.split( args, setyields, "," );
    }

    if( args.empty() && TString(setyields).Contains("=") ) {
        args.push_back(setyields);
    }

    // Set fixed parameters in the fit
    std::vector<std::string> argsFitter; 

    m_stringHelper.replaceAll( setFixedPars, " ", "" ); // removes all whitespace
    if( setFixedPars != "" ) {
        m_stringHelper.split( argsFitter, setFixedPars, "," );
    }
    if( argsFitter.empty()) {
        argsFitter.push_back(setFixedPars);
    }

    // Store the result from the fit to data, useful for comparison
    m_dataResult = m_fitter->getFitResult( m_datafitResultName );
    dataMinNll();

    // Store the initial values from the fit to data and save a snapshot
    const RooArgList& initParams = m_dataResult->floatParsInit();
    const RooArgList& finParams = m_dataResult->floatParsFinal();
    RooArgSet finalParams( finParams );
    RooArgSet initialParams( initParams );

    // set the initial toy parameter values, if any need to be changed
    // will save it under the m_toyfitParamsName name .
    if( !args.empty() ) {
        setToyInitialValues( args, finalParams );
    }

    bool goodfit(false);

    RooDataSet* dataMC = 0;
    std::string pdfName = m_fitter->getModelName();
    std::string datasetName = m_fitter->getDataSetName();
    Int_t iExp(0), event(0);
    Int_t control(10), ci(0);
    bool ok(true);

    TMVA::Timer timer( m_nSamples, "ToyStudy::runToyStudy" );
    while ( iExp < m_nSamples ) {

        // get a copy of the original truth parameters.
        RooArgSet finalParamscopy = finalParams;

        if( ci == (control) ) {
            ok = false;
            break;
        }

        // load the nominal fit values for generation
        m_fitter->loadSnapshot( m_datafitResultName );

        // If we have set some default parameters, then we can call those here
        // and load that snap shot.
        if( !args.empty() ) {
            m_fitter->loadSnapshot( m_toyfitParamsName );
        }

        // generate the toy data
        double generatedYields = m_fitter->sumYields();
        dataMC = m_fitter->generate( generatedYields, kTRUE ); // Always use Poisson dist

        const RooArgSet* theConstraints = m_fitter->getWS()->set( m_fitter->getConstraintString() );
        if( !argsFitter.empty() ) {
            for(std::vector<std::string>::iterator it_args = argsFitter.begin(); it_args != argsFitter.end(); ++it_args) {
                m_fitter->getWS()->var( (*it_args).c_str() )->setConstant( kTRUE );
            }
        }

        m_result = m_fitter->getWS()->pdf( pdfName.c_str() )->fitTo( *dataMC, 
                RooFit::NumCPU( m_fitter->getnCPU() ),
                RooFit::Extended( kTRUE ),
                RooFit::Save( kTRUE ),
                RooFit::PrintLevel(-1),
                RooFit::PrintEvalErrors(-1),
                RooFit::ExternalConstraints( *theConstraints )
                );

        ++event;

        goodfit = m_result->covQual()==3 && m_result->edm()<1e-3 && m_result->status()==0;

        if ( !goodfit ) {   
            ++m_seed;
            ci++;
            // reset the initial parameters.
            delete dataMC; dataMC=0;
            std::cerr << "ToyStudy::runToyStudy -- Bad fit (covQual, edm, status) = (" << m_result->covQual() 
                << ", " << m_result->edm() << ", " << m_result->status()  << ")" << std::endl;
            delete m_result; m_result=0;
            continue;
        } 
        ci = 0; // reset the max fitting loop iExp

        RooArgSet finalParamsRev( m_result->floatParsInit() );
        fillVectors( &finalParamsRev );

        ++iExp;
        // reset the initial parameters.
        ++m_seed;
        delete dataMC; dataMC=0;
        delete m_result; m_result=0;
        timer.DrawProgressBar( iExp );
    }
    if(!ok) {
        std::stringstream msg;
        msg << "Failed to find convergent fit after " << ci << " iterations.";
        throw GeneralException("ToyStudy::runToyStudy", msg.str() );
    }

    std::cout << "ToyStudy::runToyStudy - Total number of failed toys: " << event - iExp << std::endl;

}

//=============================================================================
// Does a MC study on the pdf. 
// Sets seed for random generator (to enable many small independent toy studies
// to be done in parallel).
// Allows individual yield parameters to be set explicitly
// Additional parameters used in the KShh BR fit
//=============================================================================
void ToyStudy::runToyStudy( const char* fitName, std::string setyields, std::string setFixedPars, std::string setMinos, bool saveResults)  
{
    m_datafitResultName = fitName;
    std::vector<std::string> args; // Check if we're setting multiple parameters to new values.
    std::string pdfName = m_fitter->getModelName();
    std::cout << pdfName << std::endl;
    m_stringHelper.replaceAll( setyields, " ", "" ); // removes all whitespace
    if( setyields != "" ) {
        m_stringHelper.split( args, setyields, "," );
    }

    if( args.empty() && TString(setyields).Contains("=") ) {
        args.push_back(setyields);
    }

    // Set fixed parameters in the fit
    std::vector<std::string> argsFitter; 

    m_stringHelper.replaceAll( setFixedPars, " ", "" ); // removes all whitespace
    if( setFixedPars != "" ) {
        m_stringHelper.split( argsFitter, setFixedPars, "," );
    }
    if( argsFitter.empty()) {
        argsFitter.push_back(setFixedPars);
    }

    // Set the Minos parameters
    std::vector<std::string> argsMinos;

    m_stringHelper.replaceAll( setMinos, " ", "" ); // removes all whitespace
    if( setMinos != "" ) {
        m_stringHelper.split( argsMinos, setMinos, "," );
    }
    if( argsMinos.empty()) {
        //    argsMinos.push_back(setMinos);
    }
    RooArgSet minosArgs;
    for (std::vector<std::string>::iterator itMinos = argsMinos.begin() ; itMinos != argsMinos.end() ; ++itMinos)
    {
        RooRealVar *tempVar = m_fitter->getWS()->var(itMinos->c_str());
        if (tempVar == NULL)
        {
            std::stringstream msg;
            msg << "Did not find the variable " << *itMinos << " in the fitter workspace.";
            throw GeneralException("ToyStudy::runToyStudy", msg.str() ); 
        }
        minosArgs.add(*tempVar);      
    }
    minosArgs.Print("v");
    // Store the result from the fit to data, useful for comparison
    m_dataResult = m_fitter->getFitResult( m_datafitResultName );
    dataMinNll();

    // Store the initial values from the fit to data and save a snapshot
    const RooArgList& initParams = m_dataResult->floatParsInit();
    const RooArgList& finParams = m_dataResult->floatParsFinal();
    RooArgSet finalParams( finParams );
    RooArgSet initialParams( initParams );

    // set the initial toy parameter values, if any need to be changed
    // will save it under the m_toyfitParamsName name .
    if( !args.empty() ) {
        setToyInitialValues( args, finalParams );
    }

    bool goodfit(false);

    RooDataSet* dataMC = 0;

    std::string datasetName = m_fitter->getDataSetName();
    Int_t iExp(0), event(0);
    Int_t control(20), ci(0);
    bool ok(true);

    TMVA::Timer timer( m_nSamples, "ToyStudy::runToyStudy" );  
    std::clock_t time1;
    std::clock_t time2;
    time1 = std::clock();

    RooRealVar *tempVar = NULL;
    while ( iExp < m_nSamples ) {
        std::cout << "Fit n." << iExp << "(" << event << ")" << std::endl;  
        // get a copy of the original truth parameters.
        RooArgSet finalParamscopy = finalParams;

        if( ci == (control) ) {
            ok = false;
            break;
        }

        // load the nominal fit values for generation
        m_fitter->loadSnapshot( m_datafitResultName );

        // If we have set some default parameters, then we can call those here
        // and load that snap shot.
        if( !args.empty() ) {
            m_fitter->loadSnapshot( m_toyfitParamsName );
        }

        // generate the toy data
        double generatedYields = m_fitter->sumYields();
        m_fitter->resetGaussianConstraints();
        dataMC = m_fitter->generate( generatedYields, kTRUE ); // Always use Poisson dist
        time2 = std::clock() - time1;
        std::time_t start = std::time(NULL);

        const RooArgSet* theConstraints = m_fitter->getWS()->set( m_fitter->getConstraintString() );
        if( !argsFitter.empty() ) {
            for(std::vector<std::string>::iterator it_args = argsFitter.begin(); it_args != argsFitter.end(); ++it_args) {
                if (*it_args==std::string(""))
                    continue;
                tempVar = m_fitter->getWS()->var( (*it_args).c_str() );
                if (tempVar == NULL)
                {
                    std::cout << "VARIABLE " << *it_args << " NOT FOUND!" << std::endl;
                    continue;
                }
                tempVar->setConstant( kTRUE );	  
            }
        }
        m_result = m_fitter->getWS()->pdf( pdfName.c_str() )->fitTo( *dataMC, 
                RooFit::NumCPU( m_fitter->getnCPU() ),
                RooFit::Extended( kTRUE ),
                RooFit::Save( kTRUE ),
                RooFit::PrintLevel(-1),
                RooFit::PrintEvalErrors(-1),
                RooFit::ExternalConstraints( *theConstraints )
                );
        m_result->Print("v");    
        ++event;
        goodfit = m_result->covQual()==3 && m_result->edm()<1e-2 && m_result->status()==0;
        std::cout << "Time: " << time2/(double)(CLOCKS_PER_SEC/1000) << " " << (std::clock() - time1)/(double)(CLOCKS_PER_SEC/1000) << " " << std::time(NULL)-start << std::endl;
        if (saveResults)
        {
            std::stringstream ss;
            ss << event;
            std::string s_event = ss.str();
            std::string suffix;
            if (!goodfit)
                suffix = "-FAILED";
            m_result->SetName(("fitResults"+suffix+"-"+s_event).c_str());	
            m_result->SetTitle("");
            m_allFitResults.push_back(m_result);
        }
        if ( !goodfit ) {   
            ++m_seed;
            ci++;
            // reset the initial parameters.
            delete dataMC; dataMC=0;
            std::cerr << "ToyStudy::runToyStudy -- Bad fit (covQual, edm, status) = (" << m_result->covQual() 
                << ", " << m_result->edm() << ", " << m_result->status()  << ")" << std::endl;
            //      delete m_result; m_result=0;
            continue;
        }       
        else {
            //	m_result->Print("v");
        }
        ci = 0; // reset the max fitting loop iExp

        RooArgSet finalParamsRev( m_result->floatParsInit() );
        fillVectors( &finalParamsRev );
        ++iExp;
        // reset the initial parameters.
        ++m_seed;
        delete dataMC; dataMC=0;
        timer.DrawProgressBar( iExp );
        std::cout << "End of the loop" << std::endl;
    }
    if(!ok) {
        std::stringstream msg;
        msg << "Failed to find convergent fit after " << ci << " iterations.";
        throw GeneralException("ToyStudy::runToyStudy", msg.str() );
    } 
    std::cout << "ToyStudy::runToyStudy - Total number of failed toys: " << event - iExp << std::endl;
}

//=============================================================================
void ToyStudy::plotValues(TString fileName) const
{
    m_pulls.plotValues(fileName);
}

void ToyStudy::plotPulls(TString fileName) const
{
    m_pulls.plotPulls(fileName);
}

void ToyStudy::plotResiduals(TString fileName) const
{
    m_pulls.plotResiduals(fileName);
}

void ToyStudy::plotResiduals(TString fileName, std::string paramName) const
{
    m_pulls.plotResiduals(fileName,paramName);
}

void ToyStudy::plotToyResiduals(TString fileName) const
{
    m_pulls.plotToyResiduals(fileName);
}

void ToyStudy::plotErrorVsResiduals(TString dir, TString fileName) const
{
    m_pulls.plotErrorVsResiduals(dir, fileName);
}

void ToyStudy::plotToyValues(TString fileName) const
{
    m_pulls.plotToyValues(fileName);
}

void ToyStudy::plotSystI(TString fileName, std::string paramName) const
{
    m_pulls.plotSystI(fileName, paramName);
}

void ToyStudy::plotSystII(TString fileName) const
{
    m_pulls.plotSystII(fileName);
}

void ToyStudy::writePulls(TString fileName) const
{
    m_pulls.writeVectors(fileName);
}

void ToyStudy::plotNlls(TString fileName) const
{
    m_pulls.plotNlls(fileName);
}

void ToyStudy::plotEdms(TString fileName) const
{
    m_pulls.plotEdms(fileName);
}

//=============================================================================
// fill all values based on the fit result
//=============================================================================
void ToyStudy::fillVectors(const RooArgSet* genParams )
{
    // check that there is a result
    if (m_result==0) {
        std::cerr << "ERROR in ToyStudy::fillVectors : No fit result to use." << std::endl;
        return;
    }

    m_pulls.fillVectors( genParams, NULL, m_result );
    //m_pulls.fillVectors( genParams, m_result );
}


//=============================================================================
// fill all values based on the fit result
//=============================================================================
void ToyStudy::fillVectors()
{
    // check that there is a result
    if (m_result==0) {
        std::cerr << "ERROR in ToyStudy::fillVectors : No fit result to use." << std::endl;
        return;
    }

    m_pulls.fillVectors( m_result );
}

//=============================================================================
// fill data results for Systematics Type I studies
//=============================================================================
void ToyStudy::fillVectors_SystI( RooFitResult* res_official,  RooFitResult* res_toyMC)
{
    // check that there is a result
    if ((res_official==0) || (res_toyMC==0)){
        std::cerr << "ERROR in ToyStudy::fillVectors : No fit result to use." << std::endl;
        return;
    }

    m_pulls.fillVectors_Syst( res_official, res_toyMC );
}

//=============================================================================
// fill data results for Systematics Type II studies
//=============================================================================
void ToyStudy::fillVectors_SystII( RooFitResult* res_official,  RooFitResult* res_toyMC)
{
    // check that there is a result
    if ((res_official==0) || (res_toyMC==0)){
        std::cerr << "ERROR in ToyStudy::fillVectors : No fit result to use." << std::endl;
        return;
    }
    m_pulls.fillVectors_SystII( res_official, res_toyMC );
}

//=============================================================================
// set the data fit result
//=============================================================================
void ToyStudy::dataMinNll()
{
    // check that there is a result
    if (m_dataResult==0) {
        std::cerr << "ERROR in ToyStudy::dataMinNll : No fit result to use." << std::endl;
        return;
    }

    m_pulls.dataFitResult( m_dataResult );
}

//=============================================================================
// set the seed of the toy study
//=============================================================================
void ToyStudy::setSeed( Int_t seed ) {
    RooRandom::randomGenerator()->SetSeed( seed );
    m_seed = seed;
}

// To be run after all parameters are set to values after fit.
// Then the yields for example can be modified here only.
void ToyStudy::setToyInitialValues( const std::vector<std::string>& args,
				    RooArgSet& params ) 
{
    if( args.empty() ) { return; }

    std::vector<std::string>::const_iterator iter = args.begin();
    const std::vector<std::string>::const_iterator enditer = args.end();
    for ( ; iter != enditer; ++iter ) {

        // now need to split by the varable and value,
        std::vector<std::string> vartovalue;
        m_stringHelper.split( vartovalue, *iter, "=" );

        if( vartovalue.empty() || vartovalue.size() != 2 ) {
            throw GeneralException("ToyStudy::setToyInitialValues",
                    "Unable to parse " + *iter );
            break;
        }

        std::string parameterName = vartovalue.front();

        // make sure the variable exists in the fitted parameter space
        RooRealVar* var = dynamic_cast<RooRealVar*>( params.find( parameterName.c_str() ) );
        if ( !var ) {
            throw WSRetrievalFailure("ToyStudy::setToyInitialValues",
                    *m_fitter->getWS(), parameterName.c_str(), "RooRealVar" );
        }

        // now get and set the required value of the parameter
        double value = m_stringHelper.to_number<double>( vartovalue.back() );
        var->setVal( value );
        std::cout <<"INFO: ToyStudy::setToyInitialValues - setting " << parameterName << " value to " << value << std::endl;
    }

    // save the snapshot
    m_fitter->getWS()->saveSnapshot( m_toyfitParamsName, params, kTRUE );

    // load it ready for use
    if ( !m_fitter->getWS()->loadSnapshot( m_toyfitParamsName ) )
    {
        throw WSRetrievalFailure("Fitter::setToyInitialValues",
                *m_fitter->getWS(), m_toyfitParamsName, " toy parameters snapshot");
    }

}

//=============================================================================
// Perform parameter scans to determined systematics effects due to the use of
// fixed parameters in the fit to data -- aka Systematics I   
//=============================================================================
void ToyStudy::runSystI(  const char* fitName, Fitter* fitterMC, std::string setparameters,  
        Fitter::RandomMethod randomiser ) 
{
    m_datafitResultName = fitName; // Store the fit to data result name
    std::vector<std::string> args; // Parameters to be changed

    m_stringHelper.replaceAll( setparameters, " ", "" ); // removes all whitespace
    if( setparameters != "" ) {
        m_stringHelper.split( args, setparameters, "," ); // passes the list of parameters
    }

    // Store the result from the fit to data
    m_dataResult = m_fitter->getFitResult( m_datafitResultName );
    dataMinNll();

    // Store the initial values from the fit to data and save a snapshot
    const RooArgList initParams = m_dataResult->floatParsInit();
    RooArgSet initialParams( initParams );
    m_fitter->getWS()->saveSnapshot( "initial_params", initialParams, kTRUE );

    // Get information from MC fit
    RooFitResult* MCResult = dynamic_cast<RooFitResult*>( fitterMC->getWS()->obj( "rfres_fitResults" ) );

    // Final name of the fit model
    RooRealVar* nameModelScheme = m_fitter->getWS()->var("ModelName");
    TString nameModel = nameModelScheme->GetTitle();
    std::string pdfName = nameModel.Data();

    // Additional informations and data
    std::string datasetName = m_fitter->getDataSetName();
    RooDataSet* data = m_fitter->getDataSet((datasetName).c_str());
    std::string paramWiggleName("");
    Int_t iExp(0);
    bool goodfit(false);

    TMVA::Timer timer( m_nSamples, "ToyStudy::runSystI" );
    // Loop over all the parameters 
    for(std::vector<std::string>::const_iterator it_par = args.begin(); it_par != args.end(); ++it_par){

        std::cout << "ToyStudy::runSystI - Initialising systematics for parameter: " << (*it_par) << std::endl;

        // Loop over the number of experiments
        while ( iExp < m_nSamples ) {

            // Load data initial parameters parameters
            m_fitter->loadSnapshot( "initial_params" );

            // Vary given parameter within its correlation matrix
            paramWiggleName = (*it_par);
            m_fitter->wiggleParamsFixed( paramWiggleName, randomiser, MCResult, m_datafitResultName);

            // Ommiting warning messages
            RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
            gErrorIgnoreLevel = kWarning;

            // Perform the fit to the data again with a different parameter value
            m_result = m_fitter->getWS()->pdf( pdfName.c_str() )->fitTo( *data, 
                    RooFit::NumCPU( m_fitter->getnCPU() ),
                    RooFit::Extended( kTRUE ),
                    RooFit::Save( kTRUE ),
                    RooFit::PrintLevel(-1),
                    RooFit::PrintEvalErrors(-1),
                    RooFit::ExternalConstraints( *( m_fitter->getWS()->set(  m_fitter->getConstraintString() ) ) ),
                    RooFit::Strategy(2)
                    );

            goodfit = m_result->covQual()==3 && m_result->edm()<1e-3 && m_result->status()==0;

            if ( !goodfit ) {   
                // reset the initial parameters.
                delete m_result; m_result=0;
                continue;
            }

            fillVectors();
            ++iExp;
            delete m_result; m_result=0;
            timer.DrawProgressBar( iExp );
        }
    }    
}

//=============================================================================
// Perform parameter scans to determined systematics effects due to the use of
// fixed parameters in the fit to data -- aka Systematics I   
//=============================================================================
void ToyStudy::runSystI(  const char* fitName,
		RooFitResult* MCResult,
		std::vector<std::multimap<std::string,std::string> > args,
		std::vector<std::string> constPars,
		Fitter::RandomMethod randomiser ) 
{
    m_datafitResultName = fitName; // Store the fit to data result name

    // Store the result from the fit to data
    m_dataResult = m_fitter->getFitResult( m_datafitResultName );
    m_dataResult->SetName("dataFit");
    m_allFitResults.push_back(m_dataResult);
    dataMinNll();

    // Store the initial values from the fit to data and save a snapshot
    const RooArgList initParams = m_dataResult->floatParsInit();
    RooArgSet initialParams( initParams );
    m_fitter->getWS()->saveSnapshot( "initial_params", initialParams, kTRUE );  

    // Final name of the fit model
    std::string pdfName = m_fitter->getModelName();
    // Additional informations and data
    std::string datasetName = m_fitter->getDataSetName();
    RooDataSet* data = m_fitter->getDataSet((datasetName).c_str());

    Int_t iExp(0);
    bool goodfit(false);

    TMVA::Timer timer( m_nSamples, "ToyStudy::runSystI" );
    // Loop over all the parameters 
    int seed = m_seed;
    unsigned int nExp(1),nFailed(0);
    std::vector<std::vector<double> > vals; //for monitoring
    while ( iExp < m_nSamples ) {      
        // Load data initial parameters parameters
        m_fitter->loadSnapshot( "initial_params" );
        RooAbsPdf *model = m_fitter->getModel();
        RooArgSet *obs = model->getParameters(*data);
        TIterator *it = obs->createIterator();
        RooAbsArg *arg = NULL;
        while ((arg = (RooAbsArg*) it->Next()) != NULL)
            if (std::string(arg->GetName()).find("Yield") == std::string::npos && std::string(arg->GetName()).find("dummy") == std::string::npos)
            {
                //					std::cout << "WARNING: Setting " << arg->GetName() << " constant." << std::endl;
                //					m_fitter->setParameterConstant(arg->GetName(),true);
                //					m_fitter->setParameterValue(arg->GetName(),m_fitter->getParameterValue(arg->GetName()),true);
                //					fitter.getWS()->var(arg->GetName())->setConstant(kTRUE);
            }

        pdfName = m_fitter->getModelName();
        // Vary given parameter within its correlation matrix
        m_fitter->wiggleParamsFixed( args, constPars, randomiser, MCResult, m_datafitResultName,seed);
        seed++;
        // Ommiting warning messages
        RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
        gErrorIgnoreLevel = kWarning;      
        // Perform the fit to the data again with a different parameter value
        m_fitter->performFit("fitResults_Syst",false);
        m_result = m_fitter->getFitResult("fitResults_Syst");
        m_result->Print();
        goodfit = m_result->covQual()==3 && m_result->edm()<1. && m_result->status()==0;      
        std::stringstream ss;
        ss << nExp;
        std::string s_event = ss.str();
        std::string suffix;
        if (!goodfit)
            suffix = "_FAILED";
        m_result->SetName(("fitResults"+suffix+"_"+s_event).c_str());	
        m_result->SetTitle("");
        m_allFitResults.push_back(m_result);

        nExp++;
        if ( !goodfit ) {   
            // reset the initial parameters.
            //	delete m_result; m_result=0;
            std::cout << "Failed fit!" << std::endl;
            m_result->Print();
            nFailed++;
            m_result=0;
            if (nFailed == 3)
            {
                std::stringstream msg;
                msg << "Failed to find convergent fit after " << nFailed << " iterations.";
                throw GeneralException("ToyStudy::runToyStudy", msg.str() );
            }
            continue;
        }

        nFailed = 0;
        ++iExp;      
        fillVectors_SystI(m_dataResult,m_result);
        timer.DrawProgressBar( iExp );
        std::cout << iExp << "/" << m_nSamples << "  (" << nExp << ")" << std::endl;
    }
    std::cout << iExp << " experiments generated." << std::endl;
}

//=============================================================================
// Generate ToyMC samples from a given PDF model and fitting with the benchmark
// PDF shape. -- aka Systematics Type II   
//=============================================================================
void ToyStudy::runSystII(  const char* fitName, Fitter* fitter_official)   
{

    m_datafitResultName = fitName; // Store the fit to data result name for alternative mode
    const char* m_datafitResutName_benchmark = fitName; // Kept the same name in both for simplification	

    // Store the result from the fit to data
    m_dataResult = m_fitter->getFitResult( m_datafitResultName );
    dataMinNll();

    // Store the initial values from the benchmark fit to data and save a snapshot
    RooFitResult* dataResult_benchmark = fitter_official->getFitResult( m_datafitResutName_benchmark );
    const RooArgList initParams = dataResult_benchmark->floatParsInit();
    const RooArgList fitParams  = dataResult_benchmark->floatParsFinal();

    RooArgSet initialParams( initParams );
    RooArgSet finalParams( fitParams );
    //fitter_official->getWS()->saveSnapshot( "initial_params", initialParams, kTRUE );
    fitter_official->getWS()->saveSnapshot( "fitResults", finalParams, kTRUE );

    // Final name of the benchmark fit model pdf
    RooRealVar* nameModelScheme = fitter_official->getWS()->var("ModelName");
    TString nameModel = nameModelScheme->GetTitle();
    std::string pdfName = fitter_official->getModelName();

    // Toy MC sample 
    RooDataSet* dataToyMC = 0;

    Int_t iExp(0);
    bool goodfit(false);

    TMVA::Timer timer( m_nSamples, "ToyStudy::runSystII" );

    std::cout << "ToyStudy::runSystII - Initialising systematics studies Type II " << std::endl;

    // Loop over the number of experiments
    unsigned int nBad(0);
    unsigned int nExp(0);
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
    while ( iExp < m_nSamples ) {

        // Load snapshot of the fit results of the alternative model
        m_fitter->loadSnapshot( m_datafitResultName );

        // Generate ToyMC sample from the alternative model
        dataToyMC = m_fitter->generate( m_fitter->sumYields() , kTRUE ); // Allways use Poisson dist

        // Load initial values of benchmark model
        //fitter_official->loadSnapshot( "initial_params" );
        fitter_official->loadSnapshot( "fitResults" );

        // Ommiting warning messages
        gErrorIgnoreLevel = kWarning;

        // Perform the fit to the ToyMC samples with the benchmark model
        m_result = fitter_official->getWS()->pdf( pdfName.c_str() )->fitTo( *dataToyMC, 
                RooFit::NumCPU( 4 ),
                RooFit::Extended( kTRUE ),
                RooFit::Save( kTRUE ),
                //RooFit::Minos( kTRUE),
                RooFit::PrintLevel(-1),
                RooFit::PrintEvalErrors(-1),
                RooFit::ExternalConstraints( *( fitter_official->getWS()->set(  fitter_official->getConstraintString() ) ) )
                );
        // And with the concurrent model
        dataResult_benchmark = m_fitter->getWS()->pdf( pdfName.c_str() )->fitTo( *dataToyMC, 
                RooFit::NumCPU( 4 ),
                RooFit::Extended( kTRUE ),
                RooFit::Save( kTRUE ),
                //RooFit::Minos( kTRUE),
                RooFit::PrintLevel(-1),
                RooFit::PrintEvalErrors(-1),
                RooFit::ExternalConstraints( *( m_fitter->getWS()->set(  m_fitter->getConstraintString() ) ) )
                );
        std::stringstream ss;
        ss << nExp;
        std::string s_event = ss.str();
        std::string suffix;
        //        m_result->Print("V"); 
        goodfit = m_result->covQual()==3 && m_result->edm()<1e-1 && m_result->status()==0;
        if (!goodfit)
        {
            std::cout << "Official fit failed! (" << m_result->covQual() << "," << m_result->edm() << "," << m_result->status() << ")" << std::endl;
            suffix = "_FAILED";
        }
        m_result->SetName(("fitResults-Official-"+suffix+"_"+s_event).c_str());
        m_result->SetTitle("");
        m_allFitResults.push_back(m_result);

        goodfit = dataResult_benchmark->covQual()==3 && dataResult_benchmark->edm()<1e-1 && dataResult_benchmark->status()==0;
        if (!goodfit)
            suffix = "_FAILED";
        dataResult_benchmark->SetName(("fitResults-BenchMark-"+suffix+"_"+s_event).c_str());
        dataResult_benchmark->SetTitle("");
        m_allFitResults.push_back(dataResult_benchmark);
        nExp++;
        if ( !goodfit )
        {
            std::cout << "Official fit failed! (" << m_result->covQual() << "," << m_result->edm() << "," << m_result->status() << ")" << std::endl;
            nBad++;
            if (nBad == 5)
            {
                std::cout << "Too many have fallen :'(" << std::endl;
                return;
            }
            continue;
        }
        nBad = 0;
        fillVectors_SystII(dataResult_benchmark, m_result);
        ++iExp;
        timer.DrawProgressBar( iExp );
    }    
    RooFitResult *res = (m_fitter->getFitResult( m_datafitResultName ));
    res->SetName("dataFit");
    m_allFitResults.push_back(res);
}

//=============================================================================
// Generate ToyMC samples from a given PDF model and fitting with the benchmark
// PDF shape. -- aka Systematics Type II   
//=============================================================================
void ToyStudy::runSystII_DP(  const char* fitName, Fitter* fitter_official)   
{

    m_datafitResultName = fitName; // Store the fit to data result name for alternative mode
    const char* m_datafitResutName_benchmark = fitName; // Kept the same name in both for simplification	

    // Store the result from the fit to data
    m_dataResult = m_fitter->getFitResult( m_datafitResultName );
    dataMinNll();

    // Store the initial values from the benchmark fit to data and save a snapshot
    RooFitResult* dataResult_benchmark = fitter_official->getFitResult( m_datafitResutName_benchmark );
    const RooArgList initParams = dataResult_benchmark->floatParsInit();
    const RooArgList fitParams  = dataResult_benchmark->floatParsFinal();

    RooArgSet initialParams( initParams );
    RooArgSet finalParams( fitParams );
    //fitter_official->getWS()->saveSnapshot( "initial_params", initialParams, kTRUE );
    fitter_official->getWS()->saveSnapshot( "fitResults", finalParams, kTRUE );

    // Final name of the benchmark fit model pdf
    RooRealVar* nameModelScheme = fitter_official->getWS()->var("ModelName");
    TString nameModel = nameModelScheme->GetTitle();
    std::string pdfName = nameModel.Data();

    // Toy MC sample 
    RooDataSet* dataToyMC = 0;

    Int_t iExp(0);
    bool goodfit(false);

    TMVA::Timer timer( m_nSamples, "ToyStudy::runSystII" );

    std::cout << "ToyStudy::runSystII - Initialising systematics studies Type II " << std::endl;

    // Loop over the number of experiments
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
    while ( iExp < m_nSamples ) {

        // Load snapshot of the fit results of the alternative model
        m_fitter->loadSnapshot( m_datafitResultName );

        // Generate ToyMC sample from the alternative model
        dataToyMC = m_fitter->generate( m_fitter->sumYields() , kTRUE ); // Allways use Poisson dist

        // Load initial values of benchmark model
        //fitter_official->loadSnapshot( "initial_params" );
        fitter_official->loadSnapshot( "fitResults" );

        // Ommiting warning messages
        gErrorIgnoreLevel = kWarning;

        // Perform the fit to the ToyMC samples with the benchmark model
        m_result = fitter_official->getWS()->pdf( pdfName.c_str() )->fitTo( *dataToyMC, 
                RooFit::NumCPU( 4 ),
                RooFit::Extended( kTRUE ),
                RooFit::Save( kTRUE ),
                //RooFit::Minos( kTRUE),
                RooFit::PrintLevel(-1),
                RooFit::PrintEvalErrors(-1),
                RooFit::ExternalConstraints( *( fitter_official->getWS()->set(  fitter_official->getConstraintString() ) ) )
                );
        //m_result->Print("V"); 
        goodfit = m_result->covQual()==3 && m_result->edm()<1e-3 && m_result->status()==0;

        if ( !goodfit ) {   
            // reset the initial parameters.
            delete m_result; m_result=0;
            continue;
        }

        fillVectors_SystII(dataResult_benchmark, m_result);
        ++iExp;
        delete m_result; m_result=0;
        timer.DrawProgressBar( iExp );
    }    
}
