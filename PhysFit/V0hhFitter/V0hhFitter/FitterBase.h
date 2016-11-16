// $Id: $
#ifndef V0HHFITTER_FITTERBASE_H
#define V0HHFITTER_FITTERBASE_H 1

// Include files
// STL include
#include <string>
#include <map>

// ROOT
#include "Rtypes.h"
#include "TNamed.h"
#include "TAttLine.h"

// RooFit
#include "RooCmdArg.h"
#include "RooAbsPdf.h"
#include "RooDataHist.h"


// Local includes
//#include "FitterBase.h"

/// forward declarations
// ROOT
class TFile;

// RooFit
class RooWorkspace;
class RooAbsData;
class RooDataSet;
// class RooDataHist;
class RooAbsReal;
class RooRealVar;
class RooPlot;
// class RooAbsPdf;
class RooAddPdf;
class RooArgSet;
class RooHist;
//class RooCmdArg;

/** @class FitterBase FitterBase.h V0hhFitter/FitterBase.h

  Pure abstract base class for the fitting framework

  @author Matthew M Reid
  @date   2014-01-08
 */

namespace V0hhFit // Fiting Analysis Simulataneous Toys
{
    class FitterBase
    {

    public:
      /** Create a new RooWorkspace object.
	  @param name Name of the RooWorkspace.
	  @param title Title of the RooWorkspace.
      */
      virtual void createWS( const char* name, const char* title="") = 0;
      
      /** Add a prexisting RooWorkspace object.
	  @param ws A pointer to the RooWorkspace object.
	  @param takeOwnership A flag indicating whether the Fitter
	  object should (true) take ownership of the RooWorkspace or
	  (false) if the user should be responsible for deleting it.
      */
      virtual void setWS(RooWorkspace* ws, Bool_t takeOwnership=kFALSE) = 0;
      
      /** Attach a file for writing out the RooWorkspace.
	  @param filename The name of the output TFile.
	  @param options The TFile access mode.
      */
      virtual void attachFile(const char* filename, const char* options) = 0;
      
      
      /** Load an existing RooWorkspace from file,
	  and optionally attach the file for writing any changes to the
	  RooWorkspace.
	  @param filename The name of the input TFile.
	  @param wsName The name of the RooWorkspace.
	  @param attachFile A flag indicating whether the file
	  should be attached (opened in UPDATE mode to allow 
	  changes to the RooWorkspace.
      */
      virtual void loadWS( const char* filename, const char* wsName,
			   Bool_t attachFile=kFALSE) = 0;

      /// Save the workspace to the attached file.
      virtual void saveWS() = 0;
      
      /** Save the workspace to the specified file (if a file is already
	  attached, it will be detached).
	  @param filename The name the output file.
	  @param recreateFile A flag indicating whether the file should be
	  opened in (true) RECREATE or (false) UPDATE mode.
      */
      virtual void saveWS( const char* filename, Bool_t recreateFile=kTRUE ) = 0;
      
      /** Save the workspace to the already open TFile. N.B. Since we don't
	  necessarily own the file, we should release ownership of the
	  RooWorkspace.
	  @param f A pointer to the input TFile.
      */
      virtual void saveWS( TFile* f ) = 0;
      
      /** Create a reduced data set with name "newName" using cut "cut".
	  If saveToWS is true, then the new data set is saved to the workspace,
	  otherwise a pointer to the new data set is returned.
      */
      virtual RooDataSet* createReducedDataSet(const char* newName,
					       const char* cut,
					       Bool_t saveToWS=kTRUE) = 0;
      
      /** Create a reduced data set with name "newName" using the 
	  named range "range".
	  If saveToWS is true, then the new data set is saved to the workspace,
	  otherwise a pointer to the new data set is returned.
      */
      virtual RooDataSet* createReducedDataSetByRange(const char* newName,
						      const char* range,
						      Bool_t saveToWS=kTRUE) = 0;
      
      
      /** Perform a maximum likelihood fit of the specified model 
	  PDF to the specified dataset.
	  The RooFitResult will be saved to rfres_$(fitName), where $(fitName)
	  is the specified fitName.
	  @param fitName The name of the RooFitResult (must be unique).
	  the MIGRAD minimisation.
	  @param saveSnapshot If true, then a snapshot will be saved to the
	  RooWorkspace.
	  @param printResults If true, then the fit results will be print
	  to standard output.
	  @param useSumW2Errors If true, then use sum-of-weights^2 errors
	  instead of Gaussian errors (this option will be forced if the 
	  dataset is weighted).
	  @param extendedMode If true, a extended maximum likelihood fit.
      */
      virtual void performFit(const char* fitName="fitResults", Bool_t useMinos = kFALSE,
			      Bool_t verboseMode = kFALSE, Bool_t saveSnapshot = kTRUE, 
			      Bool_t printResults = kFALSE, Bool_t useSumW2Errors = kFALSE, 
			      Bool_t extendedMode = kTRUE ) = 0;
      
      /** Perform a binned fit to the model PDF.
	  A binned clone of the data is made, which is then used to fit the PDF.
	  The default binning for each variable in the original dataset is used.
	  The number of bins for a given variable can be changed using the
	  SetBins method.
	  By default, a maximum likelihood fit is performed. If useChi2Method is
	  set to true, then a chi^2 fit is performed instead.
	  For descriptions of the other arguments, see the PerformFit method.
      */
      virtual void performBinnedFit(const char* fitName="fitResults",
                    Bool_t saveSnapshot=kTRUE, Bool_t printResults=kFALSE,
                    Bool_t useSumW2Errors=kFALSE, 
                    Bool_t extendedMode=kTRUE,
                    Bool_t useChi2Method=kFALSE) = 0;

      /** Perform an iterative binned fit to the model PDF, for a given
	  list of Minuit strategies.
	  For descriptions of the other arguments, see the PerformFit and 
	  PerformBinndFit methods.
      */
      virtual void performIterativeBinnedFit( std::vector<Int_t>& minuitStrategies,
					      const char* fitName="fitResults",
					      Bool_t saveSnapshot=kTRUE,
					      Bool_t printResults=kFALSE,
					      Bool_t useSumW2Errors=kFALSE, 
					      Bool_t extendedMode=kTRUE,
					      Bool_t useChi2Method=kFALSE) = 0;
      
      /** Calculate SWeights (Note that newName is only used when the RooDataSet
	  is cloned) for the fit results named "fitName".
	  To use the current values for the fit parameters (instead of 
	  loading a snapshot), specify an empty string for fitName.
	  If no newName is specified, then the dataset with weights will be 
	  called "{origName}_withWeights", where {origName} is the name of the 
	  input dataset.
      */
      virtual void calculateSWeights(const char* fitName="fitResults", 
				     const char* newName="") = 0;
      
      /** Add dummy sWeight. The argument "sVariable" should be set to the
	  name of the sWeight variable.
	  This will be assigned a weight of unity by default, unless "weight" is 
	  specified.
	  One reason for using this method would be to assign dummy weights to 
	  signal-associated Monte Carlo so that the selection code can be used
	  on data and MC.
	  If no "newName" is specified, then the dataset with weights will be 
	  called "{origName}_withWeights", where {origName} is the name of 
	  the input dataset.
	  If "appendToDataSet" is true, then the dummy sWeight is added to the 
	  current data set. In this case, "newName" is ignored.
      */
      virtual void createDummySWeights(const char* sVariable,
				       Float_t weight=1.,
				       const char* newName="",
				       Bool_t appendToDataSet=kFALSE) = 0;
      
            /** Create a weighted dataset for a given sWeight species (sVariable).
              Note that the sWeight variables are named "{dsName}_{yieldName}_sw",
              where {dsName} is the name of the dataset and {yieldName} is the 
              name of the yield for a given species.
              If a "fitName" is given, then this fit snapshot be loaded,
              else the current fit values are used.
              If "saveToWS" is false, then the dataset is returned (note it 
              should be manually deleted), otherwise, a NULL pointer is returned, 
              and the dataset is imported into the workspace.
             */
            virtual RooDataSet* createWeightedDataSet(const char* newName, 
                    const char* sVariable,
                    const char* fitName="",
                    Bool_t saveToWS=kTRUE) = 0;

            /** 
              Import the given dataset.
             */
            virtual void importDataSet( RooDataSet* theData ) = 0;


            /** Save a weighted dataset for each sWeight species. 
              By default, the new datasets will be of the 
              form "{origName}_{sVariable}", where
              {origName} is the name of the original RooDataSet, and sVariable
              is the name of the sWeight for a particular species.
              If a "fitName" is given, then this fit snapshot be loaded,
              else the current fit values are used.
              If "prefix" is specified, then {origName} is replace by prefix.
             */
            virtual void saveWeightedDataSets(const char* fitName="",
                    const char* prefix="") = 0;


            /** Plot the specified variable with name 'name'
              NB. The variable must exist in the dataset.

              If a fit range ("range") is specified, then the variable is 
              plotted over this range. This function will raise an exception 
              is the range does not exist.

              If "sumWErrors" is true, then plot sum-of-weights-squared errors 
              (default is Gaussian errors). RooFit will force sum-of-weights-squared 
              errors if the dataset is weighted.

              If a RooPlot pointer ("frame") is given as argument, then the variable 
              is plotted on the existing RooPlot.

              If "scale" is >0, then the plot will be rescaled by the specified amount.

              If "newname" is set, then the dataset is renamed in the RooPlot.
              This is useful if several datasets need to be plotted on the same 
              RooPlot.

              If "ymin" or "ymax" are >0, then the minimum/maximum of the plot is 
              set to this value, overriding RooPlot's default values.
             */
            virtual RooPlot* plotVariable(const char* name, const char* cut="",
                    const char* range="",
                    Bool_t sumW2Errors=kFALSE, RooPlot* frame=0,
                    Double_t scale=0, const char* newname="",
                    Double_t ymin=0, Double_t ymax=0) = 0;

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
                    Color_t llColor=kBlue,
                    Color_t pllColor=kRed, 
                    Bool_t plotProfileLL=kTRUE ) = 0;
	    */
            /** Generates a RooDataSet containing numEvents, using the pdf stored 
             */ 
            virtual RooDataSet* generate( UInt_t numEvents, Bool_t extended = kTRUE ) const = 0;


            /** Calculates the likelihood ratio of the default fit and the fit 
              with the given parameter set to zero
             */
            virtual double likelihoodRatio(const char* paramName, const char* fitName) = 0;
    };

}

#endif // V0HHFITTER_FITTERBASE_H
