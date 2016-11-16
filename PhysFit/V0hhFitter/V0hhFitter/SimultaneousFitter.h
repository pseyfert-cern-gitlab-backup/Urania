// $Id: $
#ifndef V0HHFITTER_SIMULTANEOUSFITTER_H 
#define V0HHFITTER_SIMULTANEOUSFITTER_H 1

// STL include
#include <string>
#include <map>

// Local include
#include "ModelBase.h"


// forward declarations
class TTree;

/** @class Simultaneousfitter SimultaneousFitter/SimultaneousFitter.hpp
 *  
 *
 *  @author Matthew M Reid
 *  @date   2014-01-08
 */

/* Class to extend the functionality of RooPhysFitter to provide helper functions
   to create a model and unbinned data set for a single descriminating variable. 
   In principle, the variable can be any physical parameter.
 */

namespace V0hhFit {

  class SimultaneousFitter : public ModelBase {
  public:
    ClassDef(SimultaneousFitter,1);
    
    typedef Double_t(*DoubleFun)(Double_t a);
    // the following is a dummy variable that seems to be necessary for rootcint to understand the DoubleFun typedef
    DoubleFun m_currentFunc;
    
    //=============================================================================
    // Standard constructor
    //=============================================================================
            SimultaneousFitter( ); 

            //=============================================================================
            // Constructor with name and title.
            //=============================================================================
            SimultaneousFitter( const char* name, const char* title);

            //=============================================================================
            // Virtual destructor.
            //=============================================================================
            virtual ~SimultaneousFitter( ); ///< Destructor
            
            
            //=============================================================================
            //combines all datasets already in the workspace into one with a RooCategory as an index
            //that has the names of the individual datasets as types. name and title are of the new
            //combined dataset.
            //=============================================================================
            virtual void combineDataSets();    

            //=============================================================================
            //Import any RooAbsPdf from a file and put it in the workspace,
            //can be be saved within a RooWorkspace in the input file, in which
            //case specify the name in the input parameter.
            //Optionally set all parameters of this pdf constant with
            //setConstant flag.
            //=============================================================================
            virtual void importPDFFromFile(const char* filename, const char* pdfname,
                    const char* newname, const char* wsname = "", Bool_t setConstant = kFALSE );

	    //=============================================================================
      	    //Import any RooRealvar from a file and put it in the workspace,
	    //must be saved within a RooWorkspace in in the input file
	    //=============================================================================
	    virtual void importVarFromFile(const char* fileName, const char* varName,
		    const char* newName, const char* wsName = "");

	    //=============================================================================
	    // Get value of a RooRealvar from a file  within the RooWorkspace
	    //=============================================================================
	    std::vector<Double_t> importVarValueFromFile(const char* fileName, const char* varName,
	            const char* wsName);
            //=============================================================================
            // Export all pdfs in the current fitter workspace to a workspace in a file
            //=============================================================================
            virtual void exportAllPDFsToFile(const char* filename, const char* wsname);

            //=============================================================================
            // Export a named pdf in the current fitter workspace to another
            // workspace in a file
            //=============================================================================
            virtual void exportPDFToFile(const char* filename, const char* wsname,
                                         const char* pdfname, const char* newname = "");

            //=============================================================================
            // Creates the necessary named sets in the workspace for each pdf category
            //=============================================================================
            virtual void createPDFSets();

            //=============================================================================
            //Adds the comma separate list of pdfs to the named set corresponding to
            //that category
            //=============================================================================
            virtual void addPDFs(const char* categoryName, const char* pdfs);

            //=============================================================================
            //Add the variables to the workspace that will be used as yields for the 
            //given category. Puts them in a named set.
            //=============================================================================
            virtual void addYields(const char* categoryName);

            //=============================================================================
            //Picks up the relevant named sets of pdfs and yields in each category and
            //builds RooAddPdfs out of them.
            //=============================================================================
            virtual void buildAddPdfs();

            //=============================================================================
            // Creates a RooSimultaneous object from all the RooAddPdfs that are in the
            // workspace and have names that correspond to those in the category.
            //=============================================================================
            virtual void buildModel();

            //=============================================================================
            // Overriding the implementation in RooPhysFitter to perform the fit 
            // to the RooSimultaneous model
            //=============================================================================
            /*
             virtual void performFit(const char* fitName="fitResults", Bool_t useMinos = kFALSE, 
                    Bool_t verboseMode = kFALSE, Bool_t saveSnapshot=kTRUE,
                    Bool_t printResults=kFALSE, Bool_t useSumW2Errors=kFALSE, 
                    Bool_t extendedMode=kTRUE );
            */

            //=============================================================================
            // calculate SWeights (Note that newName is only used when the RooDataSet
            // is cloned). To use the current values for the fit parameters
            // (instead of loading a snapshot), specify an empty string
            // If no newName is specified, then the dataset with weights will be called
            // {origName}_withWeights, where {origName} is the name of the input dataset
			// The cFactors list serves as a container to precise the name of the species
			// for which the c-factors should be calculated.
            //=============================================================================
            virtual void calculateSWeights(const char* fitName,
										   const char* sliceName,
										   bool saveCfactors = false);
			
            //=============================================================================
            // 
            //=============================================================================			
			double calculateSPlotFactors(const char * sliceName, const char * signalYieldName, bool createVar = false);


			//==============================================================================
			//Pass in sliceName as called in SimultaneousFitter::calculateSWeights method,
			//pass in a filename for which you need to store sWeights in,
			//pass in the treename of the file,
			//pass in newfilename which will be created with the signal sweights as branch,
			//pass in the sigpdfname, the categoryname as called by addYields method,
			//and the cut for which the new file will be created with.
			//==============================================================================

			void fillwithSWeights(const char* sliceName, std::string filename, std::string treename, std::string newfilename, std::string sigpdfname, std::string categoryname, std::string cut);

            //=============================================================================
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
            // If printChi2 is true, then the chi^2, and number of degrees of freedom
            // of the fit are shown.
            //
            // If a chi^2 test statistic has been set, then this will be calculated,
            // and the p-value and significance will be determined and plotted
            //
            // If the fit was produced in extended mode, and the chi^2 or a
            // chi^2 test statistic have been requested, then extendedMode should
            // be set to true.
            //
            // excludedComponents is a comma separated list of pdf components on the slice
            // that are not to be plotted
            //
            // The function returns a RooPlot pointer. Note that the user is responsible
            // for deleting this object.
            //=============================================================================
            virtual RooPlot* plotFitResults(const char* name,
                    const char* slicename,
                    const char* fitName="fitResults",
                    const char* excludedComponents="",
                    Bool_t sumW2Errors=kFALSE
                    );

            //=============================================================================
            // Saves the plots of the mass distribution and the pull distrubution 
            // will also apply a title axis
            //=============================================================================
            void plotPrettyMassAndPull( TString saveName, std::string xtitle, 
										TString slicename, std::string fitName = "fitResults", std::string scale = "normal" ) ;
			
            //=============================================================================
            // Saves the plots of the mass distribution and the pull distrubution (e.g. MC) 
            //=============================================================================
            void plotMassAndPull( TString saveName, std::string xtitle, 
								  TString slicename, std::string fitName = "fitResults", std::string scale = "normal" ) ;
			
            //=============================================================================
            // Saves the plots of the mass distribution (e.g. data fit) 
            //=============================================================================
            void plotMass( TString saveName, std::string xtitle, 
						   TString slicename, std::string scale = "normal") ;

            //=============================================================================
            /// Simple function to plot a variable with given weight from given dataset.
            /// Written primarily to plot vars from sWeighted datasets. May be updated.
            //=============================================================================
            virtual RooPlot* makePlot(const char* varName,
									  const char* datasetName,
									  const char* wgtVarName="",
									  Bool_t sumW2Errors=kFALSE
									  );
			
            /** Returns the total yield over all fits. Over-ride
			 */
            virtual double sumYields();


            /** Perform a likelihood scan of the model PDF, and plot the results 
              for variable with name 'name'.
              NB. The variable must be a parameter in the model PDF.

              If a fit range ("range") is specified, then the variable is plotted
              over this range. This function will raise an exception is the range
              does not exist.

              If "plotProfileLL" is true, then the profile likelihood estimator 
              (the NLL minimised w.r.t. all nuisance parameters) is also determined 
              and plotted. 

              The default line colors are blue for the NLL, and red for the "
              profile likelihood.

              These values can be overridded by specifying "llColor" and "pllColor".
             */
            /*virtual RooPlot* plotLikelihoodScan(const char* name,
              const char* fitName="fitResults",
              const char* range="",
              Bool_t plotProfileLL=kTRUE,
              Color_t llColor=kBlue,
              Color_t pllColor=kRed);*/


            /** Plots the pulls between the observable with name "name" 
              for the model PDF.
              NB. The variable must be an observable in the model PDF.
              If a "fitName" is given, then this fit snapshot be loaded,
              else the current fit values are used.
              The function returns a RooPlot pointer. Note that the user is 
              responsible for deleting this object.
             */
            virtual RooPlot* plotFitPulls(const char* name, const char* slicename,
                    const char* fitName="", double pmsigma = 5.0, double pmline = 2.0 );


            //=============================================================================
            // Gets the yield of the given pdf in the range given
            //=============================================================================
            virtual double getYield(const char* pdfname, const char* yieldname,
                    double start, double stop, Bool_t getError = kFALSE);



            //=============================================================================
            // Returns the chi2 goodness of fit measure for a given slice of data 
            // and the projected pdf
            //=============================================================================
            double chi2FitMeasure( const char* name, const char* slicename,
                    const char* fitName );


            //=============================================================================
            // Returns the probability goodness of fit measure for a given slice of data 
            // and the projected pdf
            //=============================================================================
            double probFitMeasure( const char* name, const char* slicename,
                    const char* fitName );


            //=============================================================================
            // Does a simple RooMCStudy on the pdf. 
            // Sets seed for random generator (to enable many small independent toy studies
            // to be done in parallel).
            // Allows statistics to be scaled by an overall factor (multiplies all yields
            // by this number before performing the study.
            // Set binnedMode flag to kFALSE to do unbinned fits in all the toys, default
            // is binned.
            //=============================================================================
            virtual void doRooMCStudy(Int_t nSamples, const char* fname, UInt_t seed, 
                    Double_t nEvtPerSampleScaleFactor=1.0,
                    Bool_t binnedMode = kTRUE);


            //Set the option of allowing yields to fluctuate to negative values
            virtual void setNegativeYields(bool neg);


        protected:

            //-----------------------------------------------------------------------------
            // Get the name of the data histogram in a RooPlot of the specified
            // fit variable.
            // This function is used to get the pull plot.
            // NB. You may need to be override this method in a derived class.
            //-----------------------------------------------------------------------------
            std::string getDataHistName( const char* slicename ) const ;

            //-----------------------------------------------------------------------------
            // Get the name of the model PDF curve in a RooPlot of the specified
            // fit variable.
            // This function is used to get the pull plot.
            // NB. You may need to be override this method in a derived class.
            //-----------------------------------------------------------------------------
            std::string getModelCurveName(const char* name) const ;



            //=============================================================================
            //flag to set negative freedom for the yields
            //defaults to true
            //=============================================================================
            bool m_NegYields;



        private:

    };

}
#endif // V0HHFITTER_SIMULTANEOUSFITTER_H
