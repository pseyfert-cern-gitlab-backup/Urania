// $Id: $
#ifndef V0HHFITTER_MODELBASE_H 
#define V0HHFITTER_MODELBASE_H 1

// Include files
#include "Fitter.h"

#include <map>
#include <string>
#include "TFormula.h"

// forward declarations
class TTree;

/** @class RooSimultaneousfitter RooSimultaneous/ModelBase.h
 *  
 *
 *  @author Edmund Smith (LHCB)
 *  @date   2013-01-21
 */

/* Class to extend the functionality of Fitter to provide helper functions
   to create a model and unbinned data set for a single descriminating variable. 
   In principle, the variable can be any physical parameter.
 */

namespace V0hhFit {

    class ModelBase : public Fitter {

        public:
            ClassDef( ModelBase, 1 );

            // Standard constructor
            ModelBase( ); 

            // Constructor with name and title.
            ModelBase( const char* name, const char* title);

            //=============================================================================
            // Bifurcated Gaussian p.d.f with different widths on left and right side of 
            // maximum value, from RooRealVars, and import to workspace
            //=============================================================================
            void makeBiFurGauss(const char* pdfName, RooRealVar& mu, 
                    RooRealVar& sigL, RooRealVar& sigRoSigL,
                    const char* sigRName, const char* sigRTitle );

            //=============================================================================
            // Bifurcated Gaussian p.d.f with different widths on left and right side of 
            // maximum value, from RooRealVars, and import to workspace
            //=============================================================================
            void makeBiFurGauss(const char* pdfName, 
                    Float_t mu_start, Float_t mu_min, Float_t mu_max, 
                    Float_t sigL_start, Float_t sigL_min, Float_t sigL_max,
                    Float_t sigRoSigL_start, Float_t sigRoSigL_min, Float_t sigRoSigL_max,
                    const char* unit="MeV/c^{2}" );

            //=============================================================================
            // Argus from Float_ts, and import to workspace
            //=============================================================================
            void makeArgus(const char* pdfName, 
                    Float_t endpoint_start, Float_t endpoint_min, Float_t endpoint_max, 
                    Float_t c_start, Float_t c_min, Float_t c_max,
                    const char* unit="MeV/c^{2}" );

            //=============================================================================
            // Argus from RooRealVars, and import to workspace
            //=============================================================================
            void makeArgus(const char* pdfName, RooRealVar& endpoint, RooRealVar& c );

            //=============================================================================
            // Voigtian is an efficient implementation of the convolution of a Breit-Wigner 
            // with a Gaussian, making use of the complex error function, from RooRealVars, 
            // and import to workspace
            //=============================================================================
            void makeSingleVoigtian( const char* pdfName, RooRealVar& mu, 
                    RooRealVar& width0, RooRealVar& sig0 );

            //=============================================================================
            // Voigtian is an efficient implementation of the convolution of a Breit-Wigner 
            // with a Gaussian, making use of the complex error function, from Float_ts, 
            // and import to workspace
            //=============================================================================
            void makeSingleVoigtian( const char* pdfName,  
                    Float_t mu_start, Float_t mu_min, Float_t mu_max, 
                    Float_t width0_start, Float_t width0_min, Float_t width0_max,
                    Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
                    const char* unit="MeV/c^{2}" );

            //=============================================================================
            // Single Crystal ball with single mean from RooRealVars, and import to workspace
            //=============================================================================
            void makeSingleCB( const char* pdfName, RooRealVar& mu, 
                    RooRealVar& sig0, RooRealVar& alpha0,
                    RooRealVar& n0 );

            //=============================================================================
            // Single Crystal ball with single mean from Float_ts, and import to workspace
            //=============================================================================
            void makeSingleCB(const char* pdfName, 
                    Float_t mu_start, Float_t mu_min, Float_t mu_max, 
                    Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
                    Float_t alpha0_start, Float_t alpha0_min, Float_t alpha0_max,
                    Float_t n0_start, Float_t n0_min, Float_t n0_max,
                    const char* unit="MeV/c^{2}" );

            //=============================================================================
            // Double Crystal ball with single mean from RooRealVars, and import to workspace
            //=============================================================================
            void makeDoubleCB(const char* pdfName, RooRealVar& mu, 
                    RooRealVar& sig0, RooRealVar& sig1oSig0, 
                    RooRealVar& alpha0, RooRealVar& alpha1oAlpha0,
                    RooRealVar& n0, RooRealVar& n1oN0,
                    RooRealVar& coreFrac,
                    const char* sig1Name, const char* sig1Title,
                    const char* alpha1Name, const char* alpha1Title,
                    const char* n1Name, const char* n1Title);

            //=============================================================================
            // Double Crystal ball with single mean from Float_ts, and import to workspace
            //=============================================================================
            void makeDoubleCB(const char* pdfName, Float_t mu_start, Float_t mu_min,
                    Float_t mu_max, Float_t sig0_start, Float_t sig0_min, 
                    Float_t sig0_max, Float_t sig1oSig0_start, Float_t sig1oSig0_min, 
                    Float_t sig1oSig0_max, Float_t alpha0_start, Float_t alpha0_min, 
                    Float_t alpha0_max, Float_t alpha1oAlpha0_start, Float_t alpha1oAlpha0_min,
                    Float_t alpha1oAlpha0_max, Float_t n0_start, Float_t n0_min,
                    Float_t n0_max, Float_t n1oN0_start, Float_t n1oN0_min, Float_t n1oN0_max,
                    Float_t coreFrac_start, const char* unit="MeV/c^{2}" );

            //=============================================================================
            // Double Crystal ball with single mean from Float_ts, and import to workspace
            //=============================================================================
            void makeDoubleCBDiffMeans(const char* pdfName,
									   Float_t mu_start, Float_t mu_min, Float_t mu_max,
									   Float_t dM_start, Float_t dM_min, Float_t dM_max,
									   Float_t sig_start, Float_t sig_min, Float_t sig_max,
									   Float_t alpha0_start, Float_t alpha0_min, Float_t alpha0_max,
									   Float_t alpha1oAlpha0_start, Float_t alpha1oAlpha0_min, Float_t alpha1oAlpha0_max,
									   Float_t n0_start, Float_t n0_min, Float_t n0_max,
									   Float_t n1oN0_start, Float_t n1oN0_min, Float_t n1oN0_max,
									   Float_t coreFrac_start, const char* unit="MeV/c^{2}" );
			
            //=============================================================================
            // Double Crystal ball with single mean from Float_ts, and import to workspace
            //=============================================================================
            void makeDoubleCB(const char* pdfName, Float_t mu_start, Float_t mu_min,
							  Float_t mu_max, Float_t sig_start, Float_t sig_min, 
							  Float_t sig_max, Float_t alpha0_start, Float_t alpha0_min, 
							  Float_t alpha0_max, Float_t alpha1oAlpha0_start, Float_t alpha1oAlpha0_min,
							  Float_t alpha1oAlpha0_max, Float_t n0_start, Float_t n0_min,
							  Float_t n0_max, Float_t n1oN0_start, Float_t n1oN0_min, Float_t n1oN0_max,
							  Float_t coreFrac_start, const char* unit="MeV/c^{2}" );

            //=============================================================================
            // Single Gaussian with single mean from RooRealVars, and import to workspace
            //=============================================================================
            virtual void makeSingleGauss(const char* pdfName, RooRealVar& mu, RooRealVar& sig0);

            //=============================================================================
            // Single Gaussian with single mean from Float_ts, and import to workspace
            //=============================================================================
            virtual void makeSingleGauss(const char* pdfName,Float_t mu_start, Float_t mu_min,
                    Float_t mu_max, Float_t sig0_start,
                    Float_t sig0_min, Float_t sig0_max,
                    const char* unit="MeV/c^{2}");


            // Double Gaussian with single mean from RooRealVars
            virtual void makeDoubleGauss(const char* pdfName, RooRealVar& mu, 
                    RooRealVar& sig0, RooRealVar& sig1oSig0,
                    RooRealVar& coreFrac,
                    const char* sig1Name, const char* sig1Title);

            // Double Gaussian with single mean from Float_ts
            virtual void makeDoubleGauss(const char* pdfName, Float_t mu_start, Float_t mu_min, Float_t mu_max,
										 Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
										 Float_t sig1oSig0_start, Float_t sig1oSig0_min,
										 Float_t sig1oSig0_max, Float_t coreFrac_start,
										 const char* unit="MeV/c^{2}");    
			
            // Double Gaussian with diff mean from Float_ts
            virtual void makeDoubleGauss(const char* pdfName,
					 Float_t mu_start, Float_t mu_min, Float_t mu_max,
					 Float_t dM_start, Float_t dM_min, Float_t dM_max,
					 Float_t sig0_start, Float_t sig0_min, Float_t sig0_max,
					 Float_t sig1oSig0_start, Float_t sig1oSig0_min,
					 Float_t sig1oSig0_max, Float_t coreFrac_start,
					 const char* unit="MeV/c^{2}");    

			// Make generalized Argus
            virtual void makeArgus(const char* pdfName,
				   Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
				   Float_t slope0, Float_t slope_min, Float_t slope_max, 
				   Float_t power0, Float_t power_min, Float_t power_max,
				   const char* unit = "MeV/c^{2}"); 

            // Argus convolution with a Gaussian
			virtual void makeArgusConvGauss( const char* pdfName, Float_t sigGauss,
											 Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max,
											 Float_t slope0, Float_t slope_min, Float_t slope_max,
											 Float_t power0, Float_t power_min, Float_t power_max );
			
            // Argus convolution with a Gaussian
            virtual void makeArgusConvGauss(const char* pdfName,
											Float_t sigGauss0, Float_t sigGauss_min, Float_t sigGauss_max,
											Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
											Float_t slope0, Float_t slope_min, Float_t slope_max, 
											Float_t power0, Float_t power_min, Float_t power_max ); 
			
            // Argus convolution with a Gaussian, but fixed
            virtual void makeArgusConvGaussFixed(const char* pdfName, Float_t sigGauss, 
						 Float_t pThresh0, Float_t slope0, Float_t power0 ); 


            // Argus convolution with a Gaussian + Exp for the bkg
	    virtual void makeArgusConvGaussNExp( const char* pdfName, Float_t sigGauss, 
        	   Float_t pThresh0, Float_t pThresh_min, Float_t pThresh_max, 
		   Float_t slope0, Float_t slope_min, Float_t slope_max, 
		   Float_t power0, Float_t power_min, Float_t power_max,
		   Float_t c1_start,  Float_t c1_min, Float_t c1_max,
		   Float_t coreFrac_start ); 

            // triple Gaussian pdf
            virtual void makeTripleGauss(const char* pdfName,
                    RooRealVar& mu,
                    RooRealVar& sig0,
                    RooRealVar& sig1oSig0,
                    RooRealVar& sig2oSig0,
                    RooRealVar& coreFrac0,
                    RooRealVar& coreFrac1,
                    const char* sig1Name,
                    const char* sig1Title);

            virtual void makeTripleGauss(const char* pdfName,
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
                    const char* unit="MeV/c^{2}");

            // single Cruijff PDF
            virtual void makeCruijff( const char* pdfName,
                    RooRealVar& mu, RooRealVar& sigL, 
                    RooRealVar& sigR, RooRealVar& alphaL,
                    RooRealVar& alphaR );

            virtual void makeCruijff( const char* pdfName,
                    Float_t mu_start, Float_t mu_min, Float_t mu_max,
                    Float_t sigL_start, Float_t sigL_min, 
                    Float_t sigL_max, Float_t sigR_start,
                    Float_t sigR_min, Float_t sigR_max,
                    Float_t alphaL_start, Float_t alphaL_min,
                    Float_t alphaL_max, Float_t alphaR_start,
                    Float_t alphaR_min, Float_t alphaR_max,
                    const char* unit="MeV/c^{2}");

            // single Cruijff PDF with common sigma
            virtual void makeCruijff( const char* pdfName,
                    RooRealVar& mu, RooRealVar& sig,
                    RooRealVar& alphaL, RooRealVar& alphaR );

            virtual void makeCruijff( const char* pdfName,
                    Float_t mu_start, Float_t mu_min, Float_t mu_max,
                    Float_t sig_start, Float_t sig_min, 
                    Float_t sig_max,
                    Float_t alphaL_start, Float_t alphaL_min,
                    Float_t alphaL_max, Float_t alphaR_start,
                    Float_t alphaR_min, Float_t alphaR_max,
                    const char* unit="MeV/c^{2}");

	    virtual void makeApollonios(const char* pdfName,
        	    Float_t mu_start, Float_t mu_min,
		    Float_t mu_max,   Float_t sig_start,
		    Float_t sig_min,  Float_t sig_max,
		    Float_t b_start,  Float_t b_min,
		    Float_t b_max,    Float_t a_start,
		    Float_t a_min,    Float_t a_max,
		    Float_t n_start,  Float_t n_min,
		    Float_t n_max,    const char* unit="MeV/c^{2}");
 
	    virtual void makeAmoroso(const char* pdfName,
        	    Float_t a_start,     Float_t a_min,
      	 	    Float_t a_max,       Float_t theta_start,
      		    Float_t theta_min,   Float_t theta_max,
     		    Float_t alpha_start, Float_t alpha_min,
     		    Float_t alpha_max,   Float_t beta_start,
  		    Float_t beta_min,    Float_t beta_max,
		    const char* unit="MeV/c^{2}");

	    virtual void makeHypatia(const char* pdfName,
       	   	    Float_t l_start,   Float_t l_min,
    		    Float_t l_max,     Float_t zeta_start,
       		    Float_t zeta_min,  Float_t zeta_max,
    		    Float_t fb_start,  Float_t sigma_start,
  	   	    Float_t sigma_min, Float_t sigma_max,
		    Float_t mu_start,  Float_t mu_min,
		    Float_t mu_max,    Float_t a_start, 
		    Float_t a_min,     Float_t a_max, 
      		    Float_t n_start,   Float_t n_min, 
		    Float_t n_max,     const char* unit="MeV/c^{2}");

	    virtual void makeHypatia2(const char* pdfName,
       	   	    Float_t l_start,   Float_t l_min,
    		    Float_t l_max,     Float_t zeta_start,
       		    Float_t zeta_min,  Float_t zeta_max,
    		    Float_t fb_start,  Float_t sigma_start,
  	   	    Float_t sigma_min, Float_t sigma_max,
		    Float_t mu_start,  Float_t mu_min,
		    Float_t mu_max,    Float_t a_start, 
		    Float_t a_min,     Float_t a_max, 
      		    Float_t n_start,   Float_t n_min, 
		    Float_t n_max,     Float_t a2_start,     
		    Float_t a2_min,    Float_t a2_max, 
		    Float_t n2_start,  Float_t n2_min, 
	    	    Float_t n2_max,    const char* unit="MeV/c^{2}"); 

		//makes a first order - linear - Chebychev polynomial for use as
		//combinatoric background
		virtual void makeChebychev(const char* pdfName, RooRealVar& grad);
		virtual void makeChebychev(const char* pdfName, Float_t grad_start, Float_t grad_min, Float_t grad_max,
								   const char* unit="MeV/c^{2}");
		//makes a second order - linear - Chebychev polynomial for use as
		//combinatoric background
		virtual void makeChebychev2(const char* pdfName,
									Float_t c1_start, Float_t c1_min, Float_t c1_max,
									Float_t c2_start, Float_t c2_min, Float_t c2_max,
									const char* unit="MeV/c^{2}");
		
            //Exponential Background
            virtual void makeExponential(const char* pdfName, RooRealVar& c1);
            virtual void makeExponential(const char* pdfName, Float_t c1_start, Float_t c1_min, Float_t c1_max,
                    const char* unit="MeV/c^{2}");
            //makes a Keys pdf
            virtual void makeKeysPdf(const char* name, const char* title="");

            //************** DECAY TIME PDFS ***************//
            //make a RooDecay pdf
            virtual void makeRooDecay(const char* name,
                    Float_t tau_start, Float_t tau_min, Float_t tau_max,
                    const char* resModelName,
                    const char* title="");

            virtual void makeGaussResModel(const char* name,
                    Float_t mu_start, Float_t mu_min, Float_t mu_max,
                    Float_t sigma_start, Float_t sigma_min, Float_t sigma_max,
                    const char* title="");

            /*
            //=============================================================================
            // make a RooGaussResolutionModel with acceptance pdf included and import it
            //=============================================================================
            void makeGaussResModelAcc(const char* name,
            //resolution model parameters
            Float_t mu_start, Float_t mu_min, Float_t mu_max,
            Float_t sigma_start, Float_t sigma_min, Float_t sigma_max,
            //acceptance parameters
            Float_t accshape_val_start,Float_t accshape_val_min, Float_t accshape_val_max, 
            Int_t nBinsAcceptance,
            const char* title="");

            //=============================================================================
            // make a RooAddModel (triple gaussian) with acceptance pdf included and import it
            //=============================================================================
            void makeTripleGaussResModelAcc(const char* name,
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
            const char* title="");
             */

            //=============================================================================
            // !!!!!!!!!!!! ADD THIS WHEN HAVE TIME NICE WAY TO CHECK LIKELIHOODS
            // Calculates the likelihood ratio of the default fit and the fit over toys
            // to make a comparison.
            //=============================================================================
            /*  
                virtual void likesRatioPlot(TString fitName, TString compName, UInt_t toyScaleFactor, UInt_t numBins = 50, Double_t startRange = 0.0,
                Double_t endRange = 1.0, Double_t toyCompsLegTextSize = 0.045,
                Double_t toyCompsLegPosXStart = 0.30, Double_t toyCompsLegPosYStart = 0.40,
                Double_t toyCompsLegPosXEnd = 0.75, Double_t toyCompsLegPosYEnd = 0.85,
                Bool_t drawDataVsToyLeg = kTRUE, Bool_t drawToyCompsLeg = kTRUE, Bool_t doLog = kTRUE,
                Bool_t useROOTDefaultYAxisRange = kTRUE, Double_t minYAxisValue = 0.9);
             */              

            //exports pdf with given name from workspace to file
            //with given name.
            //with optional new name inside the file.
            virtual void exportPDF(const char* pdfname,
                    const char* filename,
                    const char* wsname,
                    const char* newname = ""
                    );

            // Gets a pdf from the workspace, user responsible for deletion.
            virtual RooAbsPdf* getPDF(const char* pdfname);

            //Gets the dataset out of the rooworkspace with the given name
            //Raises an exception if not found.
            //Caller is responsible for deletion.
            //RooDataSet* GetDataSet(const char* name);

            //void SetBMassBkgModelName(const char* name);
            //const char* GetBMassBkgModelName();

            virtual ~ModelBase( ); ///< Destructor

        protected:


        private:
    };

}

#endif // V0HHFITTER_MODELBASE_H
