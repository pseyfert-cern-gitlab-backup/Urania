#ifndef V0HHFITTER_TOYSTUDY_H
#define V0HHFITTER_TOYSTUDY_H 1

// STL include
#include <iosfwd>
#include <algorithm>
#include <functional>

// ROOT
#include "TString.h"


// RooFit
#include "RooFitResult.h"

// local
#include "string_tools.h"
#include "Fitter.h"
#include "FitterPulls.h"


/** @class ToyStudy V0hhFitter/ToyStudy.h
 *  
 *
 *  @author Matthew M Reid
 *  @date   2014-01-08
 */

/* Class to allow easy setup of toy studies given a few input parameters.
 *
 */

// This should load in the fitResult, modify it by changing yields/params then
// save a new snapshot. This should then be reloaded each time the MCstudy loops,
// wiggle parameters. Then the pulls calculated.

namespace V0hhFit {

    class ToyStudy {

        public:
            
            ClassDef(ToyStudy,1);
            explicit ToyStudy( Fitter* fitter, Int_t nSamples = 500,
                    Int_t mSystematics = 500, Int_t seed = 0 );

            virtual ~ToyStudy();


	    //=============================================================================
	    // Puts the generated values for each yield in data into the argset.
	    // Used in runToyStudy to monitor the fitting without poissonization.
	    //=============================================================================
	    virtual void actualizeYields( RooAbsData* data) const;

	    //=============================================================================
	    // Saves the RooFitResults in a TFile.
	    //=============================================================================
	    virtual void saveResults( const char* fileName ) const;
	    
            //=============================================================================
            // Does a MC study on the pdf. 
            // Sets seed for random generator (to enable many small independent toy studies
            // to be done in parallel).
            // Allows individual yield parameters to be set explicitly (setYields)
            // Allows to fix parameters (setFixedPars)
	    // Allows to use Minos on some parameters in the minosArgs
            //=============================================================================
            virtual void runToyStudy( const char* fitName = "fitResults", 
				      std::string setyields = "",
				      std::string setFixedPars = "",
				      std::string setMinos = "",
				      bool saveResults = false
				      ); 
            //=============================================================================
            // Does a MC study on the pdf. 
            // Sets seed for random generator (to enable many small independent toy studies
            // to be done in parallel).
            // Allows individual yield parameters to be set explicitly
            //=============================================================================
            virtual void runToyStudy_DP( const char* fitName = "fitResults", 
                    std::string setyields = "", std::string setFixedPars = ""); 

            //virtual void runSystematics( const char* fitName = "fitResults", const char* varyFixedParams = "" );
	    
            void fillVectors();
            void fillVectors( const RooArgSet* genParams );
            void fillVectors_SystI(RooFitResult* res_official = 0,  RooFitResult* res_toyMC = 0);
            void fillVectors_SystII(RooFitResult* res_official = 0,  RooFitResult* res_toyMC = 0);
            void dataMinNll();
			
            //=============================================================================
            // Perform Systematics studies due to fixing MC parameters
            //=============================================================================
            virtual void runSystI(  const char* fitName = "fitResults", 
									Fitter* fitterMC = 0, std::string setparameters = "", 
									Fitter::RandomMethod randomiser = Fitter::CORRELATION );
			
            //=============================================================================
            // Perform Systematics studies due to fixing MC parameters
            //=============================================================================
			/*
			virtual void runSystI(  const char* fitName, 
									RooFitResult* MCResult,
									std::vector<std::string> args,
									Fitter::RandomMethod randomiser = Fitter::CORRELATION );
			*/
            //=============================================================================
            // Perform Systematics studies due to fixing MC parameters, using parameters of
			// possibly different name in the MC fit.
            //=============================================================================
			virtual void runSystI(  const char* fitName, 
									RooFitResult* MCResult,
									std::vector<std::multimap<std::string,std::string> > args,
									std::vector<std::string> constPars,
									Fitter::RandomMethod randomiser = Fitter::CORRELATION );

            //=============================================================================
            // Perform Systematics studies due to constraining MC parameters
            //=============================================================================
			//			virtual void runSystI(  const char* fitName, 
			//									std::vector<std::string> args,
			//									double nSigmas = 1.,
			//									Fitter::RandomMethod randomiser = Fitter::CORRELATION );
			
            //=============================================================================
            // Perform Systematics studies due to the choice of the parametrisation BR fit 
            //=============================================================================
            virtual void runSystII(  const char* fitName = "fitResults", 
                    Fitter* fitter_official = 0); 

            //=============================================================================
            // Perform Systematics studies due to the choice of the parametrisation
            //=============================================================================
            virtual void runSystII_DP(  const char* fitName = "fitResults", 
                    Fitter* fitter_official = 0); 

            //virtual void runToyStudyAndSystematics(, Int_t seed = 0, 
            //        const char* varyFixedParams = "" );
            //=============================================================================
            // MIGRAD is able to find the minimum of your parameter space, however it can 
            // be subject to localised minima. A cross-check for this is to change the 
            // initial values of the fit and perform the fit again. If the true global 
            // minimum has been found then the function returns true.
            //=============================================================================
            virtual bool localMinimumChecker( const char* fitName = "fitResults", Int_t n = 100,
                    Fitter::RandomMethod method = Fitter::GAUSSIAN,
                    Double_t edmTol = 1.e-3, Bool_t extendedMode = kTRUE, Bool_t useMinos = kTRUE, Bool_t useSumW2Errors = kFALSE, 
                    Bool_t printResults = kFALSE );


            //=============================================================================
            virtual void plotValues(TString fileName) const;
	    //            //=============================================================================
	    //            virtual void plotErrorVsResiduals(TString fileName) const;
            //=============================================================================
            virtual void plotPulls(TString fileName) const;
            //=============================================================================
			virtual void plotResiduals(TString fileName) const;
            //=============================================================================
			virtual void plotResiduals(TString fileName, std::string paramName) const;
            //=============================================================================
            virtual void plotToyValues(TString fileName) const;
            //=============================================================================
            virtual void plotToyResiduals(TString fileName) const;
            //=============================================================================
            virtual void plotErrorVsResiduals(TString dir, TString fileName) const;
            //=============================================================================
            virtual void plotSystI(TString fileName, std::string paramName) const;
            //=============================================================================
            virtual void plotSystII(TString fileName) const;
            //=============================================================================
            virtual void writePulls(TString fileName) const;
            //=============================================================================
            virtual void plotNlls(TString fileName) const;
            //=============================================================================
            virtual void plotEdms(TString fileName) const;


            // getters and setters
            virtual void setNSamples( Int_t nSamples ) { m_nSamples = nSamples; }
            virtual void setMSystematics( Int_t mSystematics ) { m_mSystematics = mSystematics; }


            virtual Int_t getSeed() const { return m_seed; }
            void setSeed( Int_t seed ) ;

        protected:

        private:



            //=============================================================================
            // set parameters to the values listed in args, used for toys
            //=============================================================================
            void setToyInitialValues( const std::vector<std::string>& args,
                    RooArgSet& params );

            //=============================================================================
            // Function call to randomise all non-constant parameters within their ranges.
            // If the range value is true, the initial value is chosen by sampling a uniform
            // distribution over the allowed range of the variable, if it is false then 
            // the initial value is sampled from a Gaussian based on G( val, err ).
            //=============================================================================
            //void randomiseFitParams( Fitter::RandomMethod range = ALL );

            //=============================================================================
            // set systematic parameters to the values listed in args, used for systematic
            // studies such as varying a parameter that was fixed due to MC.
            //=============================================================================
            //void setSystematicInitialValues( std::vector<std::string> args );

            string_tools m_stringHelper;
            Fitter* m_fitter;
            Int_t m_nSamples;
            Int_t m_mSystematics;
            RooFitResult* m_dataResult;
            RooFitResult* m_result;
            Int_t m_seed;
            const char* m_datafitResultName;
            const char* m_toyfitParamsName;
            const char* m_systematicParamsName;
	    
            FitterPulls m_pulls;
			std::vector<RooFitResult*> m_allFitResults;
            RooArgSet m_wiggleCorrelation;
    };

    class CompareFitResultFunctor : public std::binary_function<RooFitResult*, RooFitResult*, bool> {
        public:
            bool operator()( RooFitResult* lhs, RooFitResult* rhs)
            {
                return ( lhs->minNll() < rhs->minNll() );
            }
    };

}

#endif // FAST_TOYSTUDY_H
