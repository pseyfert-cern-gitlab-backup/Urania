// $Id: $
#ifndef ROOPHYSFITTER_ROOPHYSFITTER_H
#define ROOPHYSFITTER_ROOPHYSFITTER_H 1

// Include files
#include "Rtypes.h"
#include "TNamed.h"
#include "TAttLine.h"
#include "RooCmdArg.h"
#include "RooAbsPdf.h"
#include "RooDataHist.h"

#include <string>
#include <map>
// Boost
#include <boost/tokenizer.hpp>

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
//class RooCmdArg;

/** @class RooPhysfitter RooPhysFitter.h RooPhysFitter/RooPhysFitter.h
 *
 *
 *  @author Philip Hunt
 *  @date   2011-05-11
 */

/* Class to perform handle the fitting of unbinned data with one or more
   physical parameters (e.g. reconstructed mass of a particle) to a model PDF,
   constructing sWeights, creating reduced datasets and plotting fit results.
   Note that the model PDF must be of type RooAddPdf (or inherit from it),
   since several methods (include the construction of the sPlot and the plotting
   methods) require a RooArgList of coefficients and PDFs
*/
namespace RooPhysFit
{
class RooPhysFitter : public TNamed
{
public:
  ClassDef(RooPhysFitter,1);

  enum PlotChi2TestStat{ NoTestStat, PearsonsChi2, YatesChi2, LLRatio};

  typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

  /// Standard constructor
  RooPhysFitter( );
  RooPhysFitter( const char* name, const char* title );
  
  // create a new RooWorkspace object
  void CreateWS( const char* name, const char* title="");

  // add a prexisting RooWorkspace object
  void SetWS(RooWorkspace* ws, Bool_t takeOwnership=kFALSE);
  
  // attach a file for writing out the RooWorkspace
  void AttachFile(const char* filename, const char* options);
  
  
  // load an existing RooWorkspace from file,
  // and optionally attach the file for writing any changes to the
  // RooWorkspace
  void LoadWS( const char* filename, const char* wsName,
               Bool_t attachFile=kFALSE);
  
  // save the workspace to the attached file
  void SaveWS();
  
  // save the workspace to the specified file (if a file is already
  // attached, it will be detached
  void SaveWS(const char* filename, Bool_t recreateFile=kTRUE);
 
  // Save the workspace to the already open TFile. Since we don't
  // necessarily own the file, we should release ownership of the
  // RooWorkspace
  void SaveWS(TFile* f);

  // Create a reduced data set with name "newName" using cut "cut"
  // If saveToWS is true, then the new data set is saved to the workspace,
  // otherwise a pointer to the new data set is returned
  RooDataSet* CreateReducedDataSet(const char* newName,
                                   const char* cut,
                                   Bool_t saveToWS=kTRUE);
  
  // Create a reduced data set with name "newName" using the named range "range"
  // If saveToWS is true, then the new data set is saved to the workspace,
  // otherwise a pointer to the new data set is returned
  RooDataSet* CreateReducedDataSetByRange(const char* newName,
                                          const char* range,
                                          Bool_t saveToWS=kTRUE);


  // perform the fit of the specified model PDF to the specified data
  // the RooFitResult will be saved to rfres_$(fitName}, where ${fitName}
  // is the specified fitName
  void PerformFit(const char* fitName="fitResults", Int_t nCores=4,
                  Bool_t saveSnapshot=kTRUE, Bool_t printResults=kFALSE,
                  Bool_t useSumW2Errors=kFALSE, Bool_t extendedMode=kTRUE);

  // Perform a binned fit to the model PDF
  // A binned clone of the data is made, which is then used to fit the PDF
  // The default binning for each variable in the original dataset is used
  // The number of bins for a given variable can be changed using the
  // SetBins method
  // By default, a maximum likelihood fit is performed. If useChi2Method is
  // set to true, then a chi^2 fit is performed instead
  void PerformBinnedFit(const char* fitName="fitResults", Int_t nCores=4,
                        Bool_t saveSnapshot=kTRUE, Bool_t printResults=kFALSE,
                        Bool_t useSumW2Errors=kFALSE, 
                        Bool_t extendedMode=kTRUE,
                        Bool_t useChi2Method=kFALSE);

  void PerformIterativeBinnedFit( std::vector<Int_t>& minuitStrategies,
                                  const char* fitName="fitResults", Int_t nCores=4,
                                  Bool_t saveSnapshot=kTRUE, Bool_t printResults=kFALSE,
                                  Bool_t useSumW2Errors=kFALSE, 
                                  Bool_t extendedMode=kTRUE,
                                  Bool_t useChi2Method=kFALSE);

  // Calculate SWeights (Note that newName is only used when the RooDataSet
  // is cloned)
  // to use the current values for the fit parameters (instead of loading a snapshot),
  //  specify an empty string
  // if no newName is specified, then the dataset with weights will be called
  // {origName}_withWeights, where {origName} is the name of the input dataset
  void CalculateSWeights(const char* fitName="fitResults", const char* newName="");

  // Add dummy sWeight. sVariable should be the name of the sWeight variable.
  // This will be assigned a weight of one by default, unless weight is 
  // specified.
  // One reason for using this method would be to assign dummy weights to 
  // signal-associated Monte Carlo so that the selection code can be used
  // on data and MC.
  // If no newName is specified, then the dataset with weights will be called
  // {origName}_withWeights, where {origName} is the name of the input dataset
  // If appendToDataSet is true, then the dummy sWeight is added to the current
  // data set. In this case, newName is ignored.
  void CreateDummySWeights(const char* sVariable,
                           Float_t weight=1.,
                           const char* newName="",
                           Bool_t appendToDataSet=kFALSE);

  // Create a weighted dataset for a given sWeight species (sVariable).
  // Note that the sWeight variables are named {dsName}_{yieldName}_sw,
  // where {dsName} is the name of the dataset and {yieldName} is the name of the yield
  // for a given species
  // If saveToWS is false, then the dataset is returned (note it should be manually deleted),
  // otherwise, a NULL pointer is returned, and the dataset is imported into the workspace
  RooDataSet* CreateWeightedDataSet(const char* newName, const char* sVariable,
                                    const char* fitName="", 
                                    // const char* dataSetWithWeightsName="",
                                    Bool_t saveToWS=kTRUE);
  
  // save a weighted dataset for each sWeight species. By default, the new datasets
  // will be of the form {origName}_{sVariable}, where {origName} is the name of the
  // original RooDataSet, and sVariable is the name of the sWeight for a particular species
  // If prefix is specified, then {origName} is replace by prefix
  // If saveToWS is false, then the dataset is returned (note it should be manually deleted),
  // otherwise, a NULL pointer is returned, and the dataset is imported into the workspace
  void SaveWeightedDataSets(const char* fitName="", 
                            //const char* dataSetWithWeightsName="",
                            const char* prefix="");
  
  
  // Plot the observable with name 'name', showing the fit results
  // NB. The variable must be an observable in the model PDF
  //
  // Optionally, a range can be specified. This will be used to extrapolate the
  // yields to the given range. The function will raise an exception if the range does not
  // exist for the given observable.
  //
  // By default, the extrapolated yields will be labelled "yieldTitle (range)".
  // If rangeTitle is specified, then the label will be "yieldTitle (rangeTitle)"
  //
  // If sumWErrors is true, then plot sum-of-weights-squared errors (default is
  // Poissonian errors). RooFit will force sum-of-weights-squared errors if the dataset is
  // weighted
  //
  // If printChi2 is true, then the chi^2, and number of degrees of freedom
  // of the fit are shown
  //
  // If a chi^2 test statistic has been set, then this will be calculated
  // and plotted.
  //
  // If the fit was produced in extended mode, and the chi^2 or a
  // chi^2 test statistic have been requested, then extendedMode should
  // be set to true.
  //
  // The function returns a RooPlot pointer. Note that the user is responsible for deleting
  // this object
  RooPlot* PlotFitResults(const char* name,
                          const char* fitName="fitResults",
                          const char* range="",
                          const char* rangeTitle="",
                          Bool_t sumW2Errors=kFALSE,
                          Bool_t printChi2=kTRUE,
                          Bool_t extendedMode=kTRUE,
                          Int_t nChi2FitCores=4);
  
  
  // Plot the specified variable with name 'name'
  // NB. The variable must exist in the dataset
  //
  // If a range is specified, then the variable is plotted over this range. This function will
  // raise an exception is the range does not exist
  //
  // If sumWErrors is true, then plot sum-of-weights-squared errors (default is
  // Poissonian errors). RooFit will force sum-of-weights-squared errors if the dataset is
  // weighted
  //
  // If a RooPlot pointer is given as argument, then the variable is plotted
  // on the existing RooPlot
  //
  // if scale is >0, then the plot will be rescaled by the specified amount
  //
  // If newname is set, then the dataset is renamed in the RooPlot.
  // This is useful if several datasets need to be plotted on the same RooPlot
  //
  // If ymin/ymax is >0, then the minimum/maximum of the plot is set to this value,
  // overriding RooPlot's default values
  RooPlot* PlotVariable(const char* name, const char* cut="",
                        const char* range="",
                        Bool_t sumW2Errors=kFALSE, RooPlot* frame=0,
                        Double_t scale=0, const char* newname="",
                        Double_t ymin=0, Double_t ymax=0);

  // Perform a likelihood scan of the model PDF, and plot the results for variable with name 'name'
  // NB. The variable must be a parameter in the model PDF
  //
  // If a range is specified, then the variable is plotted over this range. This function will
  // raise an exception is the range does not exist
  //
  // nCores is used to specify the number of parallel jobs to used for the MIGRAD minimisation
  // of the NLL
  //
  // If plotProfileLL is true, then the profile likelihood estimator (the NLL minimised
  // w.r.t. all nuisance parameters) is also determined and plotted
  //
  // The default line colors are blue for the NLL, and red for the profile likelihood.
  // These values can be overridded by specifying llColor and pllColor.
  RooPlot* PlotLikelihoodScan(const char* name,
                              const char* fitName="fitResults",
                              const char* range="", Int_t nCores=4,
                              Bool_t plotProfileLL=kTRUE,
                              Color_t llColor=kBlue,
                              Color_t pllColor=kRed);
  
  
  // Create the named set "Plot Parameters" with contents from the RooArgSet params,
  // overwriting the current set if it exists.
  // This is used to indicate what variables should be plotted.
  // If this set does not exist in the workspace, then all parameters in the pdf are plotted
  
  ///      void SetPlotParameters(const RooArgSet& params);
  
  // Create the named set "Plot Parameters" with contents from the colon-separated list
  // contentList. This is used to indicate what variables should be plotted.
  // If this set does not exist in the workspace, then all parameters in the pdf are plotted
  void SetPlotParameters(const char* contentList);
  
  
  // Add the parameter paramName to the named set "Plot Parameters"
  // This is used to indicate what variables should be plotted.
  // If this set does not exist in the workspace, then all parameters in the pdf are plotted
  void AddPlotParameter(const char* paramName);
  
  // Add the parameter param to the named set "Plot Parameters"
  // This is used to indicate what variables should be plotted.
  // If this set does not exist in the workspace, then all parameters in the pdf are plotted
  ///      void AddPlotParameter(const RooRealVar& param);
  
  
  // Load the snapshot of the fit parameters given by name fitName
  // Will raise an exception if the snapshot does not exist in the
  // workspace
  void LoadSnapshot(const char* fitName);

  // Add a range for the specified variable. If the range name already
  // exists, then it is overwritten. If no range is specified, then the 
  // default range is overwritten
  // This method raises an exception if the variable does not exists in the
  // workspace
  void SetRange(const char* name, Float_t min, Float_t max, 
                const char* range="");
  
  // Add the plot component "name" to the list of PDF components to plot
  // NB: there is no check that the PDF component exists in the RooWorkspace
  void AddPdfComponent(const char* name, Color_t lineCol=kBlue,
                       Style_t lineStyle=kDashed,
                       Width_t lineWidth=3);
  

  // set the line color, style and width of the specified PDF component
  // Will raise an exception if it is not in the list of components
  void SetPdfComponentLineColor(const char* name, Color_t col);
  void SetPdfComponentLineStyle(const char* name, Style_t style);
  void SetPdfComponentLineWidth(const char* name, Width_t width);
  void SetPdfComponentLineAttributes(const char* name, Color_t col,
                                     Style_t style, Width_t width);
  
  // Remove the plot component "name" from the list of PDF components to plot
  // Will raise an exception if it is not in the list of components
  void RemovePdfComponent(const char* name);
  
  // Clear the list of PDF components to plot
  void ClearPdfComponents();
  
  
  // set name of the model PDF (NB. the model must be a RooAddPdf instance, or inherit from it)
  void SetModelName(const char* name);
  
  // set the dataset name (NB. the data set must be unbinned)
  void SetDataSetName(const char* name);

  // Set the binnined test statistic to plot (fit results plot only)
  //
  //
  // NoTestStat indicates that no test statistic should be used.
  // PearsonsChi2 indictates that a Pearson's chi^2 test should be used.
  // YatesChi2 indicates that a Pearson's chi^2 test with Yates'
  // correction should be used.
  // LLRatio indidates that a log likelihood ratio test statistic should
  // be used
  // RandomSampling indicates that a toy random sampling
  //
  // The null hypothesis for such a goodness-of-fit is that the PDF
  // describes the data.
  // As such, a small p-value means that the PDF is not well-described
  // by the data.
  // Conversely, a very large p-value probably means there was a problem
  // with the chi^2 fit (e.g. very large uncertainties, or low statistics)
  // 
  // Note that the Pearson's chi^2 test tends to overestimate the
  // statistical significance for low statistics, since the test
  // statistic is no longer well described by the chi^2 distribution.
  // The general rule of thumb is that the test should not be used if more
  // than 20% of the bins have expected frequencies below 5.
  // In this case, a more realistic result can be found by applying
  // Yate's continuity correction. However, this correction has a tendency
  // to overcompensate, resulting in an increased probability of
  // committing a type II error.
  // An alternative in these cases is to use a likelihood ratio test,
  // which tends to approximate the chi^2 distribution better than
  // Pearson's chi^2 test in the case where |Oi - Ei| > Ei, where
  // Oi and Ei are the observed and expected freequencies in bin i
  // respectively.
  //
  // In the case where the sample is very small (say a few hundred events
  // or less), it is preferable to use an exact test, such as a multinomial
  // exact test, or a toy MC study in which data is generated from the PDF
  // using random sampling, and a p-value is determined from the number
  // of datasets from N samples with the same or larger value for the
  // Pearson's chi^2 (or similar test statistic)
  //
  // A random sampling method can be employed by setting m_chi2MCStudyFlag
  // to true (using the SetChi2MCStudyFlag method)
  // The number of toys can be adjusting using the SetNumChi2Toys method
  //
  // The test statistic to use with the sampling method is determined
  // from what plot test statistic is set by this method (if no test
  // statistic is set, then the MC sampling will not be performed)
  void SetChi2TestStat(RooPhysFitter::PlotChi2TestStat stat);
  
  // should we perform an MC random sampling study to determine the
  // goodness-of-fit?
  void SetChi2MCStudyFlag(Bool_t flag);
  
  // set the number of toys to use for the MC sampling study
  void SetNumChi2Toys(UInt_t nToys);
  
  
  // set the name of the named set containing the sWeight variables
  void SetSWeightSetName(const char* name);
  
  // set the name of the named set containing the plot parameters
  void SetPlotParameterSetName(const char* name);
  
  
  // set the line attributes of the model PDF
  void SetModelLineColor(Color_t col);
  void SetModelLineStyle(Style_t style);
  void SetModelLineWidth(Width_t width);
  void SetModelLineAttributes(Color_t col, Style_t style, Width_t width);
  
  
  // set the dataset line attributes
  void SetDataSetLineColor(Color_t col);
  void SetDataSetLineStyle(Style_t style);
  void SetDataSetLineWidth(Width_t width);
  void SetDataSetLineAttributes(Color_t col, Style_t style, Width_t width);
  
  
  // set the dataset marker attributes
  void SetDataSetMarkerColor(Color_t col);
  void SetDataSetMarkerStyle(Style_t style);
  void SetDataSetMarkerSize(Size_t size);
  void SetDataSetMarkerAttributes(Color_t col, Style_t style, Size_t size);
  
  
  // set the dataset fill attributes
  void SetDataSetFillColor(Color_t col);
  void SetDataSetFillStyle(Style_t style);
  void SetDataSetFillAttributes(Color_t col, Style_t style);
  
  
  // set the dataset draw options (see TGraphPainter for details)
  void SetDataSetDrawOption(const char* opt);
  
  // set the parameter box attributes
  void SetParamBoxX1(Float_t x);
  void SetParamBoxX2(Float_t x);
  void SetParamBoxY1(Float_t x);
  void SetParamBoxY2(Float_t x);
  
  void SetParamBoxTextSize(Float_t size);
  void SetParamBoxTextAlign(Int_t align);
  void SetParamBoxName(const char* name);
  
  void SetParamBoxAttributes(const char* name, Float_t x1, Float_t y1,
                             Float_t x2, Float_t y2,
                             Float_t textSize=0.03, Int_t textAlign=12);
  
  // Set the number of global bins to use in subsequent plots
  void SetPlotBins(Int_t nBins);
  
  // Set the number of bins to use in subsequent plots for the given variable
  // this will override the number of global bins
  void SetPlotBins(const char* name, Int_t nBins);
  
  
  // Set the number of global bins to use when calculating the chi2 or
  // binned test statistic.
  void SetChi2Bins(Int_t nBins);
  
  // Set the number of global bins to use when calculating the chi2 or
  // binned test statistic for the given variable.
  // This will override the number of global bins
  void SetChi2Bins(const char* name, Int_t nBins);
  
  // Set the default number of bins for a given RooRealVar
  // Optionally, set the number of bins for a given named range
  // If you want to set the number of bins for a given named binning,
  // then you should manipulate the RooRealVar object directly 
  // using the GetVar method
  // Will raise an exception if the requested variable does not exist in the
  // workspace
  void SetBins(const char* name, Int_t nBins, const char* range=0);
  
  // Get the specified yield
  // If a range is given, then a new RooRealVar is creating containing the yield,
  // otherwise, a clone of the original yield is returned, unless returnClone is false.
  // If fitName is specified, then the fit result snapshot is loaded first
  RooRealVar* GetYield(const char* name, const char* range="",
                       const char* fitName="", Bool_t returnClone=kTRUE) const;
  
  // get the currently attached workspace
  const RooWorkspace* GetWS() const;
  RooWorkspace* GetWS(); // mutator version
  
  // get a variable from the workspace by name
  const RooRealVar* GetVar(const char* name) const;
  RooRealVar* GetVar(const char* name); // mutator version
  
  // get a dataset from the workspace by name
  const RooAbsData* GetDataSet(const char* name) const;
  RooAbsData* GetDataSet(const char* name); // mutator version
  
  // get the RooDataSet with the name given by GetDataSetName()
  const RooDataSet* GetDataSet() const;
  RooDataSet* GetDataSet(); // mutator version
  const char* GetDataSetName() const;
  
  // get the PDF with the name given by GetModelName()
  const RooAddPdf* GetModel() const;
  RooAddPdf* GetModel(); // mutator version
  const char* GetModelName() const;

  const char* GetSWeightSetName() const;
  const char* GetPlotParamsSetName() const;
  
  // get a RooAbsPdf from the workspace by name
  const RooAbsPdf* GetPdf(const char* name) const;
  RooAbsPdf* GetPdf(const char* name);
  
  // Get the named set with the given name from the workspace
  // Will raise an exception if the set does not exist in the workspace
  const RooArgSet* GetNamedSet(const char* name) const;
  
  // retrieve the fit result (rfres_${fitName} from the workspace
  // Will raise an exception if the fit result does not exist in the workspace
  const RooFitResult* GetFitResult(const char* fitName) const;
  RooFitResult* GetFitResult(const char* fitName); // mutator version

  // get the test statistic to plot (fit result plots only)
  RooPhysFitter::PlotChi2TestStat GetChi2TestStat() const;
  
  // should we perform an MC random sampling study to determine the
  // goodness-of-fit?
  Bool_t GetChi2MCStudyFlag() const;
  
  // get the number of toys to use for the MC sampling study
  UInt_t GetNumChi2Toys() const;
  
  // get the line color of the model PDF
  Color_t GetModelLineColor() const;
  // get the line style of the model PDF
  Style_t GetModelLineStyle() const;
  // get the line width of the model PDF
  Width_t GetModelLineWidth() const;
  
  // get the line color, style and width of the specified PDF component
  // Will raise an exception if it is not in the list of components
  Color_t GetPdfComponentLineColor(const char* name);
  Style_t GetPdfComponentLineStyle(const char* name);
  Width_t GetPdfComponentLineWidth(const char* name);

  // get the dataset line color
  Color_t GetDataSetLineColor() const;
  // get the dataset line style
  Style_t GetDataSetLineStyle() const;
  // get the dataset line width
  Width_t GetDataSetLineWidth() const;
  
  // get the dataset marker color
  Color_t GetDataSetMarkerColor() const;
  // get the dataset marker style
  Style_t GetDataSetMarkerStyle() const;
  // get the dataset marker width
  Size_t GetDataSetMarkerSize() const;

  // get the dataset fill color
  Color_t GetDataSetFillColor() const;
  // get the dataset fill style
  Style_t GetDataSetFillStyle() const;
  
  // get the dataset draw options (see TGraphPainter for details)
  const char* GetDataSetDrawOption() const;
  
  // get the parameter box attributes
  Float_t GetParamBoxX1() const;
  Float_t GetParamBoxX2() const;
  Float_t GetParamBoxY1() const;
  Float_t GetParamBoxY2() const;
  
  Float_t GetParamBoxTextSize() const;
  Int_t GetParamBoxTextAlign() const;
  const char* GetParamBoxName() const;
  
  // Get the number of plot bins
  // If a name is specified, returns the number of bins for a given
  // variable (raises an exception if the number of bins have not
  // been defined for this variable)
  Int_t GetPlotBins(const char* name="");
  
  // Get the number of chi2 bins
  // If a name is specified, returns the number of bins for a given
  // variable (raises an exception if the number of bins have not
  // been defined for this variable)
  Int_t GetChi2Bins(const char* name="");
  
  virtual ~RooPhysFitter( ); ///< Destructor
  
protected:
    /// methods

    // Get the number of degrees of freedom for binned GOF tests
    // If ignoreEmptyBins is true, then any empty bins are ignored
    // in the calculation, otherwise an exception is raised if there
    // are empty bins
    Int_t GetNDOF(RooDataHist* data, RooAbsPdf* pdf,
                  Bool_t ignoreEmptyBins=kTRUE);

    // Get the p-value of the value of the test statistic chi2
    // w.r.t. the chi^2 distribution with nDOF degrees of freedom
    Double_t GetPValFromChi2Stat(Double_t chi2, Int_t nDOF);

    // Get the significance (in units of sigma) of the value of the
    // test statistic chi2 w.r.t. the chi^2 distribution with nDOF
    // degrees of freedom
    Double_t GetSignifFromChi2Stat(Double_t chi2, Int_t nDOF);

    // Get the significance (in units of sigma) for the given p-value/
    // significance level
    Double_t GetSignifFromPVal(Double_t pVal);

    // Get the p-value based on the number of toy datasets with the same
    // or more extreme value of the chi^2 test statistic as compared to
    // the "true" distribution (given by the specified value for the chi^2
    // test statistic and the number of degrees of freedom
    Double_t GetPValFromChi2MCToyStudy(
        RooAbsPdf& model, RooDataHist& data, Int_t nToys,
        RooPhysFitter::PlotChi2TestStat statType,
        Bool_t extended = kFALSE, const char* rangeName = 0,
        const char* addCoefRangeName = 0, Int_t nCPU = 1,
        Bool_t interleave = kFALSE, Bool_t verbose = kTRUE,
        Bool_t splitCutRange = kTRUE,
        RooAbsData::ErrorType etype = RooDataHist::SumW2);
    Double_t GetPValFromChi2MCToyStudy(
        RooAbsPdf& model, RooDataHist& data, Int_t nToys,
        RooPhysFitter::PlotChi2TestStat statType,
        const RooCmdArg& arg1, const RooCmdArg& arg2 = RooCmdArg::none(),
        const RooCmdArg& arg3 = RooCmdArg::none(),
        const RooCmdArg& arg4 = RooCmdArg::none(),
        const RooCmdArg& arg5 = RooCmdArg::none(),
        const RooCmdArg& arg6 = RooCmdArg::none(),
        const RooCmdArg& arg7 = RooCmdArg::none(),
        const RooCmdArg& arg8 = RooCmdArg::none(),
        const RooCmdArg& arg9 = RooCmdArg::none());

    /// data members

    // the workspace containing the PDFs, datasets and variables of interest
    RooWorkspace *m_rws;

    // name of the RooDataSet
    const char* m_dataSetName;
    // name of the model PDF
    const char* m_modelName;

    // name of the named set containing the sWeight variables (default "SWeight Variables")
    const char* m_sWeightVarSetName;

    // name of the named set containing the parameters to plot (default "Plot Paramaeters")
    const char* m_plotParamsSetName;


    // test statistic to plot (fit result plots only)
    RooPhysFitter::PlotChi2TestStat m_plotTestStat;

    // flag indicating whether we should use MC sampling study to determine
    // GOF p-value
    Bool_t m_chi2MCStudyFlag;

    // number of toy datasets to produce for MC sampling
    Int_t m_nChi2Toys;

    // number of (global) plot bins
    Int_t m_globalPlotBins;

    // number of (global) bins for calculating chi^2
    // and binned test statistics
    Int_t m_globalChi2Bins;

    // map of variable name to plot bins
    std::map<std::string, Int_t> m_plotBinMap;

    // map of variable name to chi^2 bins
    std::map<std::string, Int_t> m_chi2BinMap;

    // dimensions of parameter box (fit result plots only)
    Float_t m_paramBoxX1;
    Float_t m_paramBoxX2;
    Float_t m_paramBoxY1;
    Float_t m_paramBoxY2;

    // text size of parameter box (fit result plots only)
    Float_t m_paramBoxTextSize;

    // text alignment of parameter box (fit result plots only)
    Int_t m_paramBoxTextAlign;

    // name of TPaveText parameter box (fit result plots only)
    const char* m_paramBoxName;

    // line color used to plot the model PDF
    Color_t m_modelLineColor;
    // line style used to plot the model PDF
    Style_t m_modelLineStyle;
    // line width used to plot the model PDF
    Width_t m_modelLineWidth;

    // line color used to plot the dataset
    Color_t m_dataSetLineColor;
    // line style used to plot the dataset
    Style_t m_dataSetLineStyle;
    // line width used to plot the dataset
    Width_t m_dataSetLineWidth;

    // marker color used to plot the dataset
    Color_t m_dataSetMarkerColor;
    // marker style used to plot the dataset
    Style_t m_dataSetMarkerStyle;
    // marker width used to plot the dataset
    Width_t m_dataSetMarkerSize;

    // fill color used to plot the dataset
    Color_t m_dataSetFillColor;
    // fill style used to plot the dataset
    Style_t m_dataSetFillStyle;

    // TGraph option used to plot RooDataSet
    const char* m_dataSetDrawOption;

    // list of PDF components to plot
    std::vector<std::string> m_pdfComponents;

    // map of PDF component to line color
    std::map<std::string, Color_t> m_pdfLineColorMap;
    // map of PDF component to line style
    std::map<std::string, Style_t> m_pdfLineStyleMap;
    // map of PDF component to line width
    std::map<std::string, Style_t> m_pdfLineWidthMap;

private:
  /// methods
  TString* format(RooAbsReal* var, const RooFitResult* rfit,
                  Int_t sigDigits=1, const char* options="NEPLU") const;
  
  /// data members
  // the output file to write the RooWorkspace to
  TFile *m_file;

  // flag set if we own (and are therefore responsible for deleting) the current
  // RooWorkspace
  Bool_t m_hasOwnership;
};
}
#endif // ROOPHYSFITTER_ROOPHYSFITTER_H
