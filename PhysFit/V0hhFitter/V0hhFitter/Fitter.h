// $Id: $
#ifndef V0HHFITTER_FITTER_H
#define V0HHFITTER_FITTER_H 1

// Include files
// STL include
#include <string>
#include <map>
#include <functional> // c++11 std::function

// ROOT
#include "Rtypes.h"
#include "TNamed.h"
#include "TAttLine.h"
#include "TH2.h"
#include "TFormula.h"

// RooFit
#include "RooCmdArg.h"
#include "RooAbsPdf.h"
#include "RooDataHist.h"
#include "RooMsgService.h"
#include "RooGlobalFunc.h"


// Local includes
#include "FitterBase.h"
#include "LHCbStyle.h"
#include "string_tools.h"
#include "FitterPulls.h"

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
class RooFitResult;
//class RooCmdArg;

/** @class Fitter Fitter.hpp Fitter/Fitter.hpp

  Class to perform handle the fitting of unbinned data with one or more
  physical parameters (e.g. reconstructed mass of a particle) to a model PDF,
  constructing sWeights, creating reduced datasets and plotting fit results.
  Note that the model PDF must be of type RooAddPdf (or inherit from it),
  since several methods (include the construction of the sPlot and the 
  plotting methods) require a RooArgList of coefficients and PDFs.

  @author Matthew M Reid
  @date   2014-01-08
 */

namespace V0hhFit // Fiting Analysis Simulataneous Toys
{
	class Fitter : public TNamed, public FitterBase
	{
		public:
			// Randomisation enumerator.
			enum RandomMethod{ UNIFORM = 0, GAUSSIAN, CORRELATION, ALL, NONE };
			ClassDef(Fitter,1);

			typedef Double_t(*DoubleFun)(Double_t a);
			// the following is a dummy variable that seems to be necessary for rootcint to understand the DoubleFun typedef
			//std::function m_currentFunc;
			DoubleFun m_currentFunc;


			/// Standard constructor.
			Fitter( );

			/** Overloaded constructor.
			  @param name name of the (TNamed) object.
			  @param title title of the (TNamed) object.
			 */
			Fitter( const char* name, const char* title );

			virtual ~Fitter( ); ///< Destructor


			/// Create the (usually B mass) variable to be fit over
			virtual void make1DFitVar(Float_t xmin, Float_t xmax, const char* unit="MeV/c^{2}",
					const char* title="");


			/** Create a new RooWorkspace object.
			  @param name Name of the RooWorkspace.
			  @param title Title of the RooWorkspace.
			 */
			virtual void createWS( const char* name, const char* title="");


			/** Add a prexisting RooWorkspace object.
			  @param ws A pointer to the RooWorkspace object.
			  @param takeOwnership A flag indicating whether the Fitter
			  object should (true) take ownership of the RooWorkspace or
			  (false) if the user should be responsible for deleting it.
			 */
			virtual void setWS(RooWorkspace* ws, Bool_t takeOwnership=kFALSE);


			/// Allows to add all infos available in a given TFile to the current fitter.
			virtual void addFileInfo( TFile* f);

			/** Attach a file for writing out the RooWorkspace.
			  @param filename The name of the output TFile.
			  @param options The TFile access mode.
			 */
			virtual void attachFile(const char* filename, const char* options);


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
					Bool_t attachFile=kFALSE);


			/// Save the workspace to the attached file.
			virtual void saveWS();

			/** Reset the initial parameter values before a given fitName 
			 * was performed.
			 @param fitName - The fitname containing the initial parameters.
			 */
			void resetInitParameters( const char* fitName = "fitResults" );


			/** Save the workspace to the specified file (if a file is already
			  attached, it will be detached).
			  @param filename The name the output file.
			  @param recreateFile A flag indicating whether the file should be
			  opened in (true) RECREATE or (false) UPDATE mode.
			 */
			virtual void saveWS(const char* filename, Bool_t recreateFile=kTRUE);


			/** Save the workspace to the already open TFile. N.B. Since we don't
			  necessarily own the file, we should release ownership of the
			  RooWorkspace.
			  @param f A pointer to the input TFile.
			 */
			virtual void saveWS(TFile* f);


			/** Create a reduced data set with name "newName" using cut "cut".
			  If saveToWS is true, then the new data set is saved to the workspace,
			  otherwise a pointer to the new data set is returned.
			 */
			virtual RooDataSet* createReducedDataSet(const char* newName,
					const char* cut,
					Bool_t saveToWS=kTRUE);


			/** Create a reduced data set with name "newName" using the 
			  named range "range".
			  If saveToWS is true, then the new data set is saved to the workspace,
			  otherwise a pointer to the new data set is returned.
			 */
			virtual RooDataSet* createReducedDataSetByRange(const char* newName,
					const char* range,
					Bool_t saveToWS=kTRUE);


			/** Calculates the likelihood ratio of the default fit and the fit 
			  with the given parameter set to zero
			  @param paramName - variable name to set.
			  @param fitName - nominal fit result.
			 */
			virtual double likelihoodRatio(const char* paramName, const char* fitName);


			/** Generates a RooDataSet containing numEvents, using the pdf stored 
			  @param numEvents provides the number of events to be generated.
			  @param extended - poissonially vary the number of events, or not.
			 */
			virtual RooDataSet* generate( UInt_t numEvents, Bool_t extended = kTRUE ) const;


			/** Returns const RooArgSet* of the variables saved to a given snapshot in the
			  workspace.
			  @param snapName - poissonially vary the number of events, or not.
			 */
			virtual const RooArgSet* getSnapshot( const char* snapName ) const;

			/** Returns a mutator version RooArgSet* of the variables saved to a given snapshot in the
			  workspace.
			  @param snapName - poissonially vary the number of events, or not.
			 */
			virtual RooArgSet* getSnapshot( const char* snapName );

			/** Perform a maximum likelihood fit of the specified model 
			  PDF to the specified dataset.
			  The RooFitResult will be saved to rfres_$(fitName), where $(fitName)
			  is the specified fitName.
			  @param fitName The name of the RooFitResult (must be unique).
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
					Bool_t extendedMode = kTRUE );

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
					Bool_t useChi2Method=kFALSE);

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
					Bool_t useChi2Method=kFALSE);


			/** Perform a maximum likelihood fit of the specified model 
			  PDF to the specified dataset.
			  The RooFitResult will be saved to rfres_$(fitName), where $(fitName)
			  is the specified fitName.
			  @param fitName The name of the RooFitResult (must be unique).
			  @param saveSnapshot If true, then a snapshot will be saved to the
			  RooWorkspace.
			  @param printResults If true, then the fit results will be print
			  to standard output.
			  @param useSumW2Errors If true, then use sum-of-weights^2 errors
			  instead of Gaussian errors (this option will be forced if the 
			  dataset is weighted).
			  @param extendedMode If true, a extended maximum likelihood fit.
			 */
			/*virtual void likesRatioPlot(TString compName, UInt_t toyScaleFactor, 
			  UInt_t numBins = 50, Double_t startRange = 0.0,
			  Double_t endRange = 1.0, Double_t toyCompsLegTextSize = 0.045,
			  Double_t toyCompsLegPosXStart = 0.30, Double_t toyCompsLegPosYStart = 0.40,
			  Double_t toyCompsLegPosXEnd = 0.75, Double_t toyCompsLegPosYEnd = 0.85,
			  Bool_t drawDataVsToyLeg = kTRUE, Bool_t drawToyCompsLeg = kTRUE, 
			  Bool_t doLog = kTRUE, Bool_t useROOTDefaultYAxisRange = kTRUE, 
			  Double_t minYAxisValue = 0.9 );
			 */               

			/** Returns the total yield over all fits.
			 */
			virtual double sumYields();


			/** Calculate SWeights (Note that newName is only used when the RooDataSet
			  is cloned) for the fit results named "fitName".
			  To use the current values for the fit parameters (instead of 
			  loading a snapshot), specify an empty string for fitName.
			  If no newName is specified, then the dataset with weights will be 
			  called "{origName}_withWeights", where {origName} is the name of the 
			  input dataset.
			 */
			virtual void calculateSWeights(const char* fitName="fitResults", 
					const char* newName="");

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
					Bool_t appendToDataSet=kFALSE);

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
					Bool_t saveToWS=kTRUE);

			/** 
			  Import the given dataset.
			 */
			virtual void importDataSet( RooDataSet* theData );


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
					const char* prefix="");

			// Create a dataset with name "name" from a TTree tt.
			// The branch name in the TTree for the B0 mass is specified by "BMassVarname"
			// If the data set name is specified, then the value set by the SetDataSetName method
			// will be overwritten with the new name, otherwise the name set by the SetDataSetName
			// method will be used as the data set name
			virtual void makeMassDataSet( TTree* tt, const char* BMassVarname, const char* name,
					const char* title, const char* cuts = "", const char* weightVarName = "");


			/// wiggle all the parameters of the fit by their error
			// user can specify what type of randomisation to use
			// GAUSSIAN --> value is changed within the gussian error
			// CORRELATION (default) --> values are varied by the correlation matrix.
			// UNIFORM --> values varied by uniform distribution over their range.
			// ALL --> a ~1/3 probability of any of the above to be performed.
			virtual void wiggleAllParams( Int_t seed = -1, RandomMethod randomiser = CORRELATION, 
					const char* fitName="fitResults", const char* varsName = "wiggled_All_params");

			/// wiggle the parameter values by their errors
			virtual void wiggleAllParams( RooAbsPdf* model, RooDataSet *rds, RandomMethod randomiser = CORRELATION, const char* fitName="fitResults",
					Int_t seed = -1, const char* varsName = "wiggled_All_params" );

			/// Wiggle only the set of parameters that have been specified varsList
			virtual void wiggleParams( std::string& varsList, 
					RandomMethod randomiser = CORRELATION,
					const char* fitName="fitResults", Int_t seed = -1,
					const char* varsName = "wiggled_params" );


			/// Wiggle only the set of parameters that have been specified fitParams.
			virtual void wiggleParams( const RooArgSet* fitParams, 
					RandomMethod randomiser = CORRELATION,
					const char* fitName="fitResults", Int_t seed = -1, 
					const char* varsName = "wiggled_params" ) ;

			/// Wiggle only the set of parameters that have been specified varsList
			/// Case use: systematic studies using MC info (data param is fixed)
			virtual void wiggleParamsFixed( std::string& varsList, 
					RandomMethod randomiser = CORRELATION,
					RooFitResult* MCResult = 0, 
					const char* fitName="fitResults", Int_t seed = -1,
					const char* varsName = "wiggled_params" );

			/// Wiggle only the set of parameters that have been specified varsList
			/// Case use: systematic studies using MC info (data param is fixed)
			virtual void wiggleParamsFixed( std::vector<std::multimap<std::string,std::string> > args,
					std::vector<std::string> constPars, 
					RandomMethod randomiser = CORRELATION,
					RooFitResult* MCResult = 0, 
					const char* fitName="fitResults", Int_t seed = -1,
					const char* varsName = "wiggled_params");


			/// Wiggle only the set of parameters that have been specified fitParams.
			/// Case use: systematic studies using MC info (data param is fixed)
			virtual void wiggleParamsFixed( const RooArgSet* fitParams, 
					RandomMethod randomiser = CORRELATION,
					RooFitResult* MCResult = 0, 
					const char* fitName="fitResults", Int_t seed = -1, 
					const char* varsName = "wiggled_params" ) ;

			/// Randomise the parameters in the fit based on the correlation matrix.
			virtual void correlation_randomiser( const RooArgSet* params, int seed, const char* varsName, const char* fitName ) ;
			/// Randomise the parameters in the fit based on the correlation matrix from MC into data (fixed)
			virtual void correlation_randomiser_Fixed( const RooArgSet* params, int seed, const char* varsName, RooFitResult* MCResult);
			/// Randomise the parameters in the fit based on the correlation matrix from MC into data (fixed)
			virtual void correlation_randomiser_Fixed( std::multimap<RooAbsReal*, RooAbsReal*> params, int seed, const char* varsName, RooFitResult* MCResult);
			// Randomise the parameters specified based on a gaussian distribution
			// about its central value and error. Also works for asymmetric errors.
			virtual void gaussian_randomiser( const RooArgSet* params, int seed, const char* varsName ) ;
			// Randomise the parameters specified based on a gaussian distribution
			// about its central value and error. Also works for asymmetric errors.
			virtual void gaussian_randomiser_Fixed( std::multimap<RooAbsReal*,RooAbsReal*> vars, int seed, const char* varsName ) ;
			/// Randomise the parameters uniformly within their specified range.
			virtual void uniform_randomiser( const RooArgSet* params, int seed, const char* varsName ) ;


			/** Plots the pulls between the observable with name "name" 
			  for the model PDF.
			  NB. The variable must be an observable in the model PDF.
			  If a "fitName" is given, then this fit snapshot be loaded,
			  else the current fit values are used.
			  The function returns a RooPlot pointer. Note that the user is 
			  responsible for deleting this object.
			 */
			virtual RooPlot* plotFitPulls(const char* name,
					const char* fitName="fitResults", double pmsigma = 5.0, double pmline = 2.0 );

			/** Plot the observable with name 'name', showing the fit results with
			  name 'fitName'.
			  NB. The variable must be an observable in the model PDF

			  Optionally, a fit range ("range") can be specified. This will be 
			  used to extrapolate the yields to the given range. The function 
			  will raise an exception if the range does not exist for the given 
			  observable.

			  By default, the extrapolated yields will be labelled "yieldTitle 
			  (range)". If "rangeTitle" is specified, then the label will be 
			  "yieldTitle (rangeTitle)".

			  If "sumWErrors" is true, then plot sum-of-weights-squared errors 
			  (default is Gaussian errors). N.B. RooFit will force 
			  sum-of-weights-squared errors if the dataset is weighted.

			  The function returns a RooPlot pointer. Note that the user is 
			  responsible for deleting this object.
			 */
			virtual RooPlot* plotFitResults(const char* name,
					const char* fitName="fitResults",
					const char* range="",
					const char* rangeTitle="",
					Bool_t sumW2Errors=kFALSE);


			/**  Sets all the parameters of a given pdf to constant. If no argument
			 * specified then it defaults to using m_modelName.
			 */
			virtual void fixAllParams( const char* pdfName = "" ) ;


			/**  Sets all the parameters of a given pdf to float. If no argument
			 * specified then it defaults to using m_modelName.
			 */
			virtual void floatAllParams( const char* pdfName = "" ) ;



			/**  Plot a 2D correlation histogram of all floating variables in the fit.
			 */
			virtual TH2* plotCorrelationHist( const char* fitName="fitResults",
					double labelsize = 0.022);


			/** Write out the fitted parameter values to a latex style table.
			 *  Could probably make this a little more configurable as at the 
			 *  moment will produce asymmetric errors by default. Maybe some other formatting
			 *  but this is difficult since the names won't be in latex form anyway...
			 */
			virtual void writeTable(const char* nameOutput, const char* fitName = "fitResults" ) ;


			/** Add a constraint to the fit. For example constraining the Bs mass to be fixed by the
			 * pdg \Delta m = \mBs-\mBd mass difference. In this case there will be one free parameter
			 * Bd_SignalMean and now Bs_SignalMean = Bd_SignalMean + 86.8
			 Raises exception if any of varname or dependents are not in the workspace.
			 This version uses ClientTree class.
			 @param varname - the variable name for instance Bs_SignalMean.
			 @param formula - the formula string that will constrain varname, i.e. "@0 + 86.8"
			 @param dependents - dependents is a comma separated list, @<index> in formula corresponds to
			 position in that list. "Bd_SignalMean"

			 */
			virtual void addConstraint(const char* varname,
					const char* formula,
					const char* dependents);


			//=============================================================================
			//puts the given varname in the vector of old object names,
			//raises exception if object is not in workspace.
			//=============================================================================
			virtual void scrap(const char* oldname);

			//=============================================================================
			//Simplifies the RooWorkspace by only taking the newest versions of the objects
			//and simplifying the name.
			//=============================================================================
			//		virtual void buildNewWorkspace(const char* newName);




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
					Double_t ymin=0, Double_t ymax=0);

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
			  @param name - variable name to scan.
			  @param fitName - loads the fit parameter snapshot.
			  @param range - if the setRange function has been invoked we can use that
			  range name to specify the lower and upper bound from which the scan will
			  be made.
			  @param plotProfileLL - pretty stupid option as clearly one would always 
			  want to plot this why else call this function.
			  @param pllColor - set the 

			 */
			//COMMENTOUT
			virtual RooPlot* plotLikelihoodScan(const char* name,
					const char* fitName="fitResults",
					const char* range="", 
					Color_t pllColor=kRed, 
					Bool_t plotProfileLL=kTRUE );


			/** Create a nll scan using user defined range and granularity and store the 
			 * output graph to a TFile. Lets say we wanted to scan as a function of BF
			 * Instead of passing in the yield here we could 
			 *   fitter.addParameter("bf_name", )
			 *   fitter.addConstraint("bf_name", "@0*@1", "yield_name");
			 *  
			 * @param poiName - parameter of interest to scan over.
			 * @param steps - number of sampling points.
			 * @param min - lower bound of scan range.
			 * @param max - upper bound of scan range.
			 * @param fitName - the nominal fit result.
			 * @param outputFileName - filename to save the graphs to.
			 * @param update - boolean whether to open file in update mode of recreate.
			 * @edmTol - 
			 */   
			virtual double nllScan(const char* poiName, int steps, 
					double min, double max,  
					const char* fitName = "fitResults",
					const char* outputFileName = "nllScans.root", 
					bool update = false, double edmTol=1.e-3 ) ;


			/** Create the named set "Plot Parameters" with contents from the
			  colon-separated list "contentList". This is used to indicate 
			  which variables should be plotted.
			  N.B. If this set does not exist in the workspace, then all parameters 
			  in the pdf are plotted.
			 */
			virtual void setPlotParameters(const char* contentList);


			/** Add the parameter "paramName" to the named set "Plot Parameters".
			  This is used to indicate what variables should be plotted.
			  If this set does not exist in the workspace, then all parameters 
			  in the pdf are plotted.
			 */
			virtual void addPlotParameter(const char* paramName);

			/** Load the snapshot of the fit parameters given by name "fitName".
			  Will raise an exception if the snapshot does not exist in the
			  workspace.
			 */
			virtual void loadSnapshot(const char* fitName);

			/** Add the range "range" for the specified variable "name", with limits
			  ["min", "max"].
			  If the range name already exists, then it is overwritten. 
			  If no range is specified, then the  default range is overwritten.
			  This method raises an exception if the variable does not exists in the
			  workspace.
			 */
			virtual void setRange(const char* name, Float_t min, Float_t max, 
					const char* range="");

			/** Add the plot component "name" to the list of PDF components to plot
			  N.B. There is no check that the PDF component exists in the 
			  RooWorkspace.
			  @param name Name of the PDF component to add.
			  @param lineCol The line color used when plotting the PDF component.
			  @param lineStyle The line style used when plotting the PDF component.
			  @param lineWidth The line width used when plotting the PDF component.
			 */
			virtual void addPdfAttributes(const char* name, Color_t lineCol=kBlue,
					Style_t lineStyle=kDashed,
					Width_t lineWidth=3);

			/**  Add a gaussian constraint on varname to the list of constraints that will 
			  be applied to the model in the fit function. 
			  N.B. raises exception if name does not exist in the workspace.
			 */
			virtual void addGaussianConstraint(const char* varname,
					double value, double sigma, double extend_sig=10);

			/**  Resets all Gaussian constraints to default params, removes cached integral also.
			 */
			virtual void resetGaussianConstraints();

			/**  Centers all Gaussian constraints to params values in the RooArgSet
			 */
			//		virtual void centerGaussianConstraints(RooArgSet& finParams);

			/**  Randomizes a value of all gaussian constraints 
			 */
			//		virtual void randomizeGaussianConstraints();

			/**  Randomizes a value of all gaussian constraints 
			 */
			//            virtual void varyGaussianConstraints(RooArgSet initConstraints,std::vector<std::string> args, double nSigmas,double seed);

			//=============================================================================  
			// add a "spectator" variable (not used as a fit variable)
			// Optionally, it can added to a named set in the workspace by specifying 
			// "setName" if the branch name in the TTree, brName, is not specified, it is
			//  assumed that it has the same name as the RooRealVar
			//=============================================================================
			virtual void addSpectator(const char* name, Double_t xmin, Double_t xmax,
					const char* brName="", const char* unit="",
					const char* title="", const char* setName="");

			//=============================================================================
			// Add a "spectator" variable (not used as a fit variable)
			// similar to the above addSpectator method, except that a pointer to a function 
			// is used as an argument. The function will take the branch value
			// (converted to a double) ,and return another double
			// For example, this function can be used to store the natural logarithm using 
			// std::log
			//=============================================================================  
			virtual void addSpectator(const char* name, Double_t xmin, Double_t xmax,
					Fitter::DoubleFun fun,
					const char* brName="",
					const char* unit="", const char* title="",
					const char* setName="");


			//=============================================================================
			// Blind the given variable, raises exception if varname is not in workspace.
			// centralValue and scale are arguments to the RooUnblindPrecision constructor
			// that define the blinding transformation.
			// Uses member variable for blindstring.
			//=============================================================================
			virtual void blindParameter(const char* varname, double scale);

			//=============================================================================
			// Add a "spectator" variable (not used as a fit variable)
			// similar to the above addSpectator method, except that a generic TFormula is
			// used as an argument. The method will raise an exception if the number of 
			// dimensions is nit unity. In addition, the method does not accept any 
			// parameters.
			//=============================================================================
			virtual void addSpectator(const char* name, Double_t xmin, Double_t xmax,
					TFormula& fun, const char* brName="",
					const char* unit="", const char* title="",
					const char* setName="");

			//=============================================================================
			//Simply add a var to the workspace. For example, when you want some fit parameters 
			//to depend on an external parameter.
			//=============================================================================
			virtual void addParameter(const char* name, Double_t min, Double_t max,
					const char* title="", const char* unit="");

			//=============================================================================
			//Simply add a var to the workspace. For example, when you want some fit parameters 
			//to depend on an external parameter.
			//=============================================================================
			virtual void addParameter(const char* name, Double_t val, Double_t min, Double_t max,
					const char* title="", const char* unit="");

			//=============================================================================
			// Getters and Setters.
			//=============================================================================
			virtual void setBlindString(const char* blindstring);
			virtual void setSpectatorSetName(const char* name);

			virtual const char* getBlindString();
			virtual const char* getSpectatorSetName();

			/** Get the parameter value, useful for grabbing final formula values
			  or just getting the final value of one fitted parameter.
			  N.B. raises exception if name does not exist in the workspace.
			 */
			virtual double getParameterValue( const char* name );


			/** Set the parameter range, this is useful when specifying a default fitting range for
			 * example, or used for the NLL scan range.
			 N.B. raises exception if varName does not exist in the workspace and if it is not a
			 RooRealVar variable.
			 */
			virtual void setParameterRange( const char* varName, const char* rangeName,
					double min, double max );

			/** Set the parameter error, this is useful to handle the systematics evaluation
			  of a parameter fixed by theory (e.g: a mass threshold).
			 */
			virtual void setParameterError( const char* varName, double error);			

			/** Set the line color of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual void setPdfComponentLineColor(const char* name, Color_t col);
			/** Set the line style of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual void setPdfComponentLineStyle(const char* name, Style_t style);
			/** Set the line width of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual void setPdfComponentLineWidth(const char* name, Width_t width);
			/** Set the line color, style and width of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual void setPdfComponentLineAttributes(const char* name, Color_t col,
					Style_t style, Width_t width);

			/** Remove the plot component "name" from the list of PDF components to 
			  plot.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual void removePdfComponent(const char* name);

			/// Clear the list of PDF components to plot.
			virtual void clearPdfComponents();

			/// Plot all model sub-components
			virtual void setPlotSubComponents(bool plotSubComponents);

			/** Set the name of the category.
			 */
			virtual void setCategoryName(const char* name);
			virtual const char* getCategoryName() const;

			/** Set the name of the model PDF (NB. the model must be a RooAddPdf 
			  instance, or inherit from it).
			 */
			virtual void setModelName(const char* name);

			/// Set the dataset name (NB. the data set must be unbinned).
			virtual void setDataSetName(const char* name); 

			/// Set the name of the named set containing the sWeight variables.
			virtual void setSWeightSetName(const char* name);

			/// Set the name of the named set containing the plot parameters.
			virtual void setPlotParameterSetName(const char* name);


			/// Set the line color of the model PDF.
			virtual void setModelLineColor(Color_t col);

			/// Set the line style of the model PDF.
			virtual void setModelLineStyle(Style_t style);

			/// Set the line width of the model PDF.
			virtual void setModelLineWidth(Width_t width);

			/// Set the line attributes of the model PDF.
			virtual void setModelLineAttributes(Color_t col, Style_t style, Width_t width);

			/// Set the dataset line color.
			virtual void setDataSetLineColor(Color_t col);

			/// Set the dataset line style.
			virtual void setDataSetLineStyle(Style_t style);

			/// Set the dataset line width.
			virtual void setDataSetLineWidth(Width_t width);

			/// Set the dataset line attributes.
			virtual void setDataSetLineAttributes(Color_t col, Style_t style, Width_t width);  

			/// Set the dataset marker color.
			virtual void setDataSetMarkerColor(Color_t col);

			/// Set the dataset marker style.
			virtual void setDataSetMarkerStyle(Style_t style);

			/// Set the dataset marker size.
			virtual void setDataSetMarkerSize(Size_t size);

			/// Set the dataset marker attributes.
			virtual void setDataSetMarkerAttributes(Color_t col, Style_t style, Size_t size);  

			/// Set the dataset fill color.
			virtual void setDataSetFillColor(Color_t col);

			/// Set the dataset fill style.
			virtual void setDataSetFillStyle(Style_t style);

			/// Set the dataset fill attributes.
			virtual void setDataSetFillAttributes(Color_t col, Style_t style);

			/// Set the dataset draw options (see TGraphPainter for details).
			virtual void setDataSetDrawOption(const char* opt);

			/// Set the parameter box X1.
			virtual void setParamBoxX1(Float_t x);
			/// Set the parameter box X2.
			virtual void setParamBoxX2(Float_t x);
			/// Set the parameter box Y1.
			virtual void setParamBoxY1(Float_t x);
			/// Set the parameter box Y2.
			virtual void setParamBoxY2(Float_t x);

			/// Set the parameter box text size.
			virtual void setParamBoxTextSize(Float_t size);

			/// Set the parameter box text alignment (see TAttText for details).
			virtual void setParamBoxTextAlign(Int_t align);

			/// Set the name of the parameter box.
			virtual void setParamBoxName(const char* name);

			/// Set the parameter box attributes.
			virtual void setParamBoxAttributes(const char* name, Float_t x1, Float_t y1,
					Float_t x2, Float_t y2,
					Float_t textSize=0.03, Int_t textAlign=12);

			/// Set the number of global bins to use in subsequent plots.
			virtual void setPlotBins(Int_t nBins);

			/** Set the number of bins to use in subsequent plots for the given variable.
			  N.B. This will override the number of global bins.
			 */
			virtual void setPlotBins(const char* name, Int_t nBins);


			/** Set the default number of bins for a given RooRealVar.
			  Optionally, set the number of bins for a given named range.
			  If you want to set the number of bins for a given named binning,
			  then you should manipulate the RooRealVar object directly 
			  using the GetVar method.
			  Will raise an exception if the requested variable does not exist in the
			  workspace.
			 */
			virtual void setBins(const char* name, Int_t nBins, const char* range=0);

			/** Get the specified yield.
			  If a range is given, then a new RooRealVar is creating containing 
			  the yield, otherwise, a clone of the original yield is returned, 
			  unless returnClone is false.
			  If fitName is specified, then the fit result snapshot is loaded first.
			 */
			virtual RooRealVar* getYield(const char* name, const char* range="",
					const char* fitName="", Bool_t returnClone=kTRUE) const;

			//! Get the currently attached workspace.
			virtual const RooWorkspace* getWS() const;
			//! Get the currently attached workspace, mutator version.
			virtual RooWorkspace* getWS(); 

			/// Get a variable from the workspace by name.
			virtual const RooRealVar* getVar(const char* name) const;
			virtual RooRealVar* getVar(const char* name); /// mutator version

			/*!
			  Gets the dataset out of the rooworkspace with the given name.
			  Raises an exception if not found. Caller is responsible for deletion.
			  \param name -  The name of the dataset.
			 */
			virtual const RooDataSet* getDataSet(const char* name) const;
			virtual RooDataSet* getDataSet(const char* name); /// mutator version


			/// Get the RooDataSet with the name given by GetDataSetName().
			virtual const RooDataSet* getDataSet() const;
			virtual RooDataSet* getDataSet(); /// mutator version

			/// Get the data set name.
			virtual const char* getDataSetName() const;

			/// Get the PDF with the name given by GetModelName().
			virtual const RooAbsPdf* getModel() const;
			virtual RooAbsPdf* getModel(); /// mutator version

			/// Get the model name.
			virtual const char* getModelName() const;

			/// Get the sWeight set name.
			virtual const char* getSWeightSetName() const;

			/// Get the plot parameters named set name.
			virtual const char* getPlotParamsSetName() const;

			/// Get a RooAbsPdf from the workspace by name.
			virtual const RooAbsPdf* getPdf(const char* name) const;
			virtual RooAbsPdf* getPdf(const char* name); /// mutator version

			/** Get the named set with the given name from the workspace.
			  Will raise an exception if the set does not exist in the workspace.
			 */
			const RooArgSet* getNamedSet(const char* name) const;

			/** Retrieve the fit result (rfres_${fitName} from the workspace.
			  Will raise an exception if the fit result does not exist in the 
			  workspace.
			 */
			virtual const RooFitResult* getFitResult(const char* fitName) const;
			virtual RooFitResult* getFitResult(const char* fitName); /// mutator version

			/// Get the line color of the model PDF
			virtual const Color_t& getModelLineColor() const;
			/// Get the line style of the model PDF
			virtual const Style_t& getModelLineStyle() const;
			/// Get the line width of the model PDF
			virtual const Width_t& getModelLineWidth() const;

			/** Get the line color of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual const Color_t& getPdfComponentLineColor(const char* name) const;
			/** Get the line style of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual const Style_t& getPdfComponentLineStyle(const char* name) const;
			/** Get the line width of the specified PDF component.
			  N.B. Will raise an exception if it is not in the list of components.
			 */
			virtual const Width_t& getPdfComponentLineWidth(const char* name) const;

			/// Get the dataset line color.
			virtual const Color_t& getDataSetLineColor() const;
			/// Get the dataset line style.
			virtual const Style_t& getDataSetLineStyle() const;
			/// Get the dataset line width.
			virtual const Width_t& getDataSetLineWidth() const;

			/// Get the dataset marker color.
			virtual const Color_t& getDataSetMarkerColor() const;
			/// Get the dataset marker style.
			virtual const Style_t& getDataSetMarkerStyle() const;
			/// Get the dataset marker width.
			virtual const Size_t& getDataSetMarkerSize() const;

			/// Get the dataset fill color.
			virtual const Color_t& getDataSetFillColor() const;
			/// Get the dataset fill style.
			virtual const Style_t& getDataSetFillStyle() const;

			/// Get the dataset draw options (see TGraphPainter for details).
			virtual const char* getDataSetDrawOption() const;

			/// Get the file in which we want to save the RWS.
			virtual const TFile* getFile() const;

			/// Get the parameter box X1.
			virtual const Float_t& getParamBoxX1() const;
			/// Get the parameter box X2.
			virtual const Float_t& getParamBoxX2() const;
			/// Get the parameter box Y1.
			virtual const Float_t& getParamBoxY1() const;
			/// Get the parameter box Y2.
			virtual const Float_t& getParamBoxY2() const;

			/// Get the parameter box text size.
			virtual const Float_t& getParamBoxTextSize() const;

			/// Get the paramter box text alignment.
			virtual const Int_t& getParamBoxTextAlign() const;

			/// Get the parameter box name.
			virtual const char* getParamBoxName() const;

			/** Get the number of plot bins.
			  If a name is specified, returns the number of bins for a given
			  variable (raises an exception if the number of bins have not
			  been defined for this variable)
			 */
			virtual const Int_t& getPlotBins(const char* name="") const;

			/// Sets the parameter in workspace described by varname, constant to value.
			virtual void setGlobalKillBelowError( RooFit::MsgLevel msg = RooFit::ERROR );

			/// Sets the parameter in workspace described by varname, constant or floating.
			virtual void setParameterConstant( const char* varname, bool constant = true);

			/// Sets the parameter in workspace described by varname, constant to value.
			virtual void setParameterConstant( const char* varname, double value );

			/// Sets the value of the parameter, defined by varname, to value. does not set constant.
			virtual void setParameterValue(const char* varname, double value, bool isConst = false );

			virtual void set1DFitVarName(const char* name);
			virtual const char* get1DFitVarName();

			/** Set the number of parallel jobs to used for 
			  the MIGRAD minimisation of the NLL.
			 */
			virtual void setnCPU( int n );


			/** returns the list of old object names
			 */
			virtual std::vector<std::string> getOldObjects() const;


			/** Set the number of parallel jobs to used for 
			  the MIGRAD minimisation of the NLL.
			 */
			virtual int getnCPU() const;

			void setConstraintString(const char* constraintstring);
			const char* getConstraintString() const; 

			void saveDPInfo( Double_t Yield_sig_tot, Double_t Yield_bkg_tot, Double_t Yield_cross_tot, 
				const char* fileName, const char* mode, Double_t minRange, Double_t maxRange);
			void saveDPInfo_Syst( Double_t Yield_sig_tot, Double_t Yield_bkg_tot, Double_t Yield_cross_tot, 
				const char* fileName, const char* mode, Double_t minRange, Double_t maxRange);

			// methods
			//=============================================================================
			// Converts a RooArgSet to a RooArgList
			//=============================================================================
			RooArgList* RooArgSet2List(const RooArgSet* theSet);
			//=============================================================================
			// Converts a RooArgList to a RooArgSet
			//=============================================================================
			RooArgSet* RooArgList2Set(const RooArgList* theList);
			//=============================================================================
			// Finds an object of class Class in the file f.
			//=============================================================================
			static TKey* findItem(TFile* f, TClass* classType);
			//=============================================================================
			// Finds all objects of class Class in the file f.
			//=============================================================================
			static std::vector<TKey*> findAllItems(TFile* f, TClass* classType);
			//=============================================================================
			// Finds the newest version of the model in a file.
			//=============================================================================
			static std::string findModel(RooWorkspace *w, const char* modelBase = "model");
			//=============================================================================
			// Finds the newest version of the model in a file.
			//=============================================================================
			std::string findModel(const char* modelBase = "model") const;

		protected:

			/** Get the number of plot bins.
			  Returns the number of bins for this variable, if defined, else
			  returns the global number of bins
			 */
			const Int_t& getPlotBinsInt(const char* name) const;

			/** get the name of the data histogram in a RooPlot.
			  This function is used to get the pull plot.
			  NB. You may need to be override this method in a derived class.
			 */
			std::string getDataHistName() const;

			/** get the name of the model PDF curve in a RooPlot of the specified
			  fit variable.
			  This function is used to get the pull plot.
			  NB. You may need to be override this method in a derived class.
			 */
			std::string getModelCurveName(const char* var) const;

			// data members

			/// The number of CPU cores to run in parallel
			int m_nCores;

			/// The workspace containing the PDFs, datasets and variables of interest.
			RooWorkspace *m_rws;

			/// Name of the RooDataSet.
			const char* m_dataSetName;
			/// Name of the model PDF.
			const char* m_modelName;

			/// Name of the named set containing the sWeight variables (default "SWeight Variables")
			const char* m_sWeightVarSetName;

			/// Name of the named set containing the parameters to plot (default "Plot Paramaeters")
			const char* m_plotParamsSetName;

			/// Number of (global) plot bins.
			Int_t m_globalPlotBins;

			/// Map of variable name to plot bins.
			std::map<std::string, Int_t> m_plotBinMap;

			/// Parameter box X1
			Float_t m_paramBoxX1;
			/// Parameter box X2
			Float_t m_paramBoxX2;
			/// Parameter box Y1
			Float_t m_paramBoxY1;
			/// Parameter box Y2
			Float_t m_paramBoxY2;

			/// Text size of parameter box (fit result plots only).
			Float_t m_paramBoxTextSize;

			/// Text alignment of parameter box (fit result plots only).
			Int_t m_paramBoxTextAlign;

			/// Name of TPaveText parameter box (fit result plots only).
			const char* m_paramBoxName;

			/// Line color used to plot the model PDF
			Color_t m_modelLineColor;
			/// Line style used to plot the model PDF
			Style_t m_modelLineStyle;
			/// Line width used to plot the model PDF
			Width_t m_modelLineWidth;

			/// Line color used to plot the dataset
			Color_t m_dataSetLineColor;
			/// Line style used to plot the dataset
			Style_t m_dataSetLineStyle;
			// Line width used to plot the dataset
			Width_t m_dataSetLineWidth;

			/// Marker color used to plot the dataset
			Color_t m_dataSetMarkerColor;
			/// Marker style used to plot the dataset
			Style_t m_dataSetMarkerStyle;
			/// Marker width used to plot the dataset
			Size_t m_dataSetMarkerSize;

			/// Fill color used to plot the dataset
			Color_t m_dataSetFillColor;
			/// Fill style used to plot the dataset
			Style_t m_dataSetFillStyle;

			/// TGraph option used to plot RooDataSet
			const char* m_dataSetDrawOption;

			/// List of PDF components to plot
			std::vector<std::string> m_pdfComponents;

			/// Map of PDF component to line color
			std::map<std::string, Color_t> m_pdfLineColorMap;
			/// Map of PDF component to line style
			std::map<std::string, Style_t> m_pdfLineStyleMap;
			/// Map of PDF component to line width
			std::map<std::string, Style_t> m_pdfLineWidthMap;

			/// Plot all pdf sub components
			bool m_plotSubComponents;

			//methods
			std::string getBranchType(TTree* tt, std::string brName);

			const char* m_1DFitVarPartName;
			const char* m_1DFitVarName;
			const char* m_spectSetName;
			const char* m_catSetName;

			/// Use for the blinding string.
			const char* m_BlindString;

			/// Weight variable name for weighted data sets
			std::string m_weightVarName;

			///Name of set of gaussian constraints in the workspace
			const char* m_ConstraintSetName;

			string_tools m_stringHelper;

			//=============================================================================
			// vector of old names of objects, these have been updated and are no longer needed
			// but you can't remove objects from RooWorkspaces so...
			//=============================================================================
			std::vector<std::string> m_OldVersions;

			// map of the RooRealVar name of the spectator to the leaf name in the TTree
			std::map< std::string, std::string > m_varNameToBranchName;

			// map of the RooRealVar name of the spectator to the function to be applied
			// to the leaf value  
			std::map< std::string, Fitter::DoubleFun > m_varNameToFunction;

			// map of the RooRealVar name of the spectator to the TFormula to be applied
			// to the leaf value  
			std::map< std::string, TFormula > m_varNameToFormula;  

		private:

			/// Rename the variable name so it can be written in latex format
			TString renameVar( TString );

			/// Get the number of significant digits and round the numbers accordingly  
			void getDigits(double err,double err2, int& nDig1, int& nDig2) ;

			/** create a formatting TString for an abitrary RooAbsArg object
			  To control what is shown use the following options
			  N = show name
			  H = hide value
			  E = show error
			  U = show unit

			  To control how it is shown use these options
			  L = TLatex mode
			  X = Latex mode
			  Y = Latex table mode ( '=' replaced by '&' )
			  V = Make name \verbatim in Latex mode
			  P = use error to control shown precision
			  F = force fixed precision
			 */
			TString* format(RooAbsReal* var, const RooFitResult* rfit,
					Int_t sigDigits=1, const char* options="NEPLU") const;

			// data members

			/// The output file to write the RooWorkspace to
			TFile *m_file;

			/** Flag setis  if we own (and are therefore responsible for deleting) 
			  the current RooWorkspace.
			 */
			Bool_t m_hasOwnership;

			/// the standard lhcb root style set
			LHCbStyle m_lhcbStyle;

			//FitterPulls m_pulls;

	};
}
#endif // V0HHFITTER_FITTER_H
