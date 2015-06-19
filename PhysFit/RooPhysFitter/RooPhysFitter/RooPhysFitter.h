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
class RooHist;
//class RooCmdArg;

/** @class RooPhysfitter RooPhysFitter.h RooPhysFitter/RooPhysFitter.h
 
    Class to perform handle the fitting of unbinned data with one or more
    physical parameters (e.g. reconstructed mass of a particle) to a model PDF,
    constructing sWeights, creating reduced datasets and plotting fit results.
    Note that the model PDF must be of type RooAddPdf (or inherit from it),
    since several methods (include the construction of the sPlot and the 
    plotting methods) require a RooArgList of coefficients and PDFs.

    @author Philip Hunt
    @date   2011-05-11
 */

namespace RooPhysFit
{
class RooPhysFitter : public TNamed
{
public:
  ClassDef(RooPhysFitter,1);

  /// Typedef for the boost character-separated tokenizer template
  typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

  /// Standard constructor.
  RooPhysFitter( );

  /** Overloaded constructor.
      @param name name of the (TNamed) object.
      @param title title of the (TNamed) object.
  */
  RooPhysFitter( const char* name, const char* title );
  
  /** Create a new RooWorkspace object.
      @param name Name of the RooWorkspace.
      @param title Title of the RooWorkspace.
  */
  void CreateWS( const char* name, const char* title="");

  /** Add a prexisting RooWorkspace object.
      @param ws A pointer to the RooWorkspace object.
      @param takeOwnership A flag indicating whether the RooPhysFitter
      object should (true) take ownership of the RooWorkspace or
      (false) if the user should be responsible for deleting it.
  */
  void SetWS(RooWorkspace* ws, Bool_t takeOwnership=kFALSE);
  
  /** Attach a file for writing out the RooWorkspace.
      @param filename The name of the output TFile.
      @param options The TFile access mode.
  */
  void AttachFile(const char* filename, const char* options);
  
  
  /** Load an existing RooWorkspace from file,
      and optionally attach the file for writing any changes to the
      RooWorkspace.
      @param filename The name of the input TFile.
      @param wsName The name of the RooWorkspace.
      @param attachFile A flag indicating whether the file
      should be attached (opened in UPDATE mode to allow 
      changes to the RooWorkspace.
  */
  void LoadWS( const char* filename, const char* wsName,
               Bool_t attachFile=kFALSE);
  
  /// Save the workspace to the attached file.
  void SaveWS();
  
  /** Save the workspace to the specified file (if a file is already
      attached, it will be detached).
      @param filename The name the output file.
      @param recreateFile A flag indicating whether the file should be
      opened in (true) RECREATE or (false) UPDATE mode.
  */
  void SaveWS(const char* filename, Bool_t recreateFile=kTRUE);
 
  /** Save the workspace to the already open TFile. N.B. Since we don't
      necessarily own the file, we should release ownership of the
      RooWorkspace.
      @param f A pointer to the input TFile.
  */
  void SaveWS(TFile* f);

  /** Create a reduced data set with name "newName" using cut "cut".
      If saveToWS is true, then the new data set is saved to the workspace,
      otherwise a pointer to the new data set is returned.
  */
  RooDataSet* CreateReducedDataSet(const char* newName,
                                   const char* cut,
                                   Bool_t saveToWS=kTRUE);
  
  /** Create a reduced data set with name "newName" using the 
      named range "range".
      If saveToWS is true, then the new data set is saved to the workspace,
      otherwise a pointer to the new data set is returned.
  */
  RooDataSet* CreateReducedDataSetByRange(const char* newName,
                                          const char* range,
                                          Bool_t saveToWS=kTRUE);


  /** Perform a maximum likelihood fit of the specified model 
      PDF to the specified dataset.
      The RooFitResult will be saved to rfres_$(fitName}, where ${fitName}
      is the specified fitName.
      @param fitName The name of the RooFitResult (must be unique).
      @param nCores The number of parallel jobs to use for 
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
  void PerformFit(const char* fitName="fitResults", Int_t nCores=4,
                  Bool_t saveSnapshot=kTRUE, Bool_t printResults=kFALSE,
                  Bool_t useSumW2Errors=kFALSE, Bool_t extendedMode=kTRUE);

  /** Perform a binned fit to the model PDF.
      A binned clone of the data is made, which is then used to fit the PDF.
      The default binning for each variable in the original dataset is used.
      The number of bins for a given variable can be changed using the
      SetBins method.
      By default, a maximum likelihood fit is performed. If useChi2Method is
      set to true, then a chi^2 fit is performed instead.
      For descriptions of the other arguments, see the PerformFit method.
  */
  void PerformBinnedFit(const char* fitName="fitResults", Int_t nCores=4,
                        Bool_t saveSnapshot=kTRUE, Bool_t printResults=kFALSE,
                        Bool_t useSumW2Errors=kFALSE, 
                        Bool_t extendedMode=kTRUE,
                        Bool_t useChi2Method=kFALSE);

  /** Perform an iterative binned fit to the model PDF, for a given
      list of Minuit strategies.
      For descriptions of the other arguments, see the PerformFit and 
      PerformBinndFit methods.
  */
  void PerformIterativeBinnedFit( std::vector<Int_t>& minuitStrategies,
                                  const char* fitName="fitResults",
                                  Int_t nCores=4,
                                  Bool_t saveSnapshot=kTRUE,
                                  Bool_t printResults=kFALSE,
                                  Bool_t useSumW2Errors=kFALSE, 
                                  Bool_t extendedMode=kTRUE,
                                  Bool_t useChi2Method=kFALSE);

  /** Calculate SWeights (Note that newName is only used when the RooDataSet
      is cloned) for the fit results named "fitName".
      To use the current values for the fit parameters (instead of 
      loading a snapshot), specify an empty string for fitName.
      If no newName is specified, then the dataset with weights will be 
      called "{origName}_withWeights", where {origName} is the name of the 
      input dataset.
  */
  void CalculateSWeights(const char* fitName="fitResults", 
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
  void CreateDummySWeights(const char* sVariable,
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
  RooDataSet* CreateWeightedDataSet(const char* newName, 
                                    const char* sVariable,
                                    const char* fitName="",
                                    Bool_t saveToWS=kTRUE);
  
  /** Save a weighted dataset for each sWeight species. 
      By default, the new datasets will be of the 
      form "{origName}_{sVariable}", where
      {origName} is the name of the original RooDataSet, and sVariable
      is the name of the sWeight for a particular species.
      If a "fitName" is given, then this fit snapshot be loaded,
      else the current fit values are used.
      If "prefix" is specified, then {origName} is replace by prefix.
  */
  void SaveWeightedDataSets(const char* fitName="",
                            const char* prefix="");
  

  /** Plots the pulls between the observable with name "name" 
      for the model PDF.
      NB. The variable must be an observable in the model PDF.
      If a "fitName" is given, then this fit snapshot be loaded,
      else the current fit values are used.
      The function returns a RooPlot pointer. Note that the user is 
      responsible for deleting this object.
  */
  RooPlot* PlotFitPulls(const char* name,
                        const char* fitName="");

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
  RooPlot* PlotFitResults(const char* name,
                          const char* fitName="fitResults",
                          const char* range="",
                          const char* rangeTitle="",
                          Bool_t sumW2Errors=kFALSE,
                          Bool_t paramBox=kTRUE);
  
  
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
  RooPlot* PlotVariable(const char* name, const char* cut="",
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
 
      "nCores" is used to specify the number of parallel jobs to used for 
      the MIGRAD minimisation of the NLL.
  
      If "plotProfileLL" is true, then the profile likelihood estimator 
      (the NLL minimised w.r.t. all nuisance parameters) is also determined 
      and plotted. 
  
      The default line colors are blue for the NLL, and red for the "
      profile likelihood.
      
      These values can be overridded by specifying "llColor" and "pllColor".
  */
  RooPlot* PlotLikelihoodScan(const char* name,
                              const char* fitName="fitResults",
                              const char* range="", Int_t nCores=4,
                              Bool_t plotProfileLL=kTRUE,
                              Color_t llColor=kBlue,
                              Color_t pllColor=kRed);
  
  /** Create the named set "Plot Parameters" with contents from the
      colon-separated list "contentList". This is used to indicate 
      which variables should be plotted.
      N.B. If this set does not exist in the workspace, then all parameters 
      in the pdf are plotted.
  */
  void SetPlotParameters(const char* contentList);
  
  
  /** Add the parameter "paramName" to the named set "Plot Parameters".
      This is used to indicate what variables should be plotted.
      If this set does not exist in the workspace, then all parameters 
      in the pdf are plotted.
  */
  void AddPlotParameter(const char* paramName);

  /** Load the snapshot of the fit parameters given by name "fitName".
      Will raise an exception if the snapshot does not exist in the
      workspace.
  */
  void LoadSnapshot(const char* fitName);
  
  /** Save the snapshot of the fit parameters to "fitName".
      Will raise an exception if the snapshot cannot be created in the
      workspace.
  */
  void SaveSnapshot(const char* fitName);

  /** Add the range "range" for the specified variable "name", with limits
      ["min", "max"].
      If the range name already exists, then it is overwritten. 
      If no range is specified, then the  default range is overwritten.
      This method raises an exception if the variable does not exists in the
      workspace.
  */
  void SetRange(const char* name, Float_t min, Float_t max, 
                const char* range="");
  
  /** Add the plot component "name" to the list of PDF components to plot
      N.B. There is no check that the PDF component exists in the 
      RooWorkspace.
      @param name Name of the PDF component to add.
      @param lineCol The line color used when plotting the PDF component.
      @param lineStyle The line style used when plotting the PDF component.
      @param lineWidth The line width used when plotting the PDF component.
  */
  void AddPdfComponent(const char* name, Color_t lineCol=kBlue,
                       Style_t lineStyle=kDashed,
                       Width_t lineWidth=3);
  

  /** Set the line color of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  void SetPdfComponentLineColor(const char* name, Color_t col);
  /** Set the line style of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  void SetPdfComponentLineStyle(const char* name, Style_t style);
  /** Set the line width of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  void SetPdfComponentLineWidth(const char* name, Width_t width);
  /** Set the line color, style and width of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  void SetPdfComponentLineAttributes(const char* name, Color_t col,
                                     Style_t style, Width_t width);
  
  /** Remove the plot component "name" from the list of PDF components to 
      plot.
      N.B. Will raise an exception if it is not in the list of components.
  */
  void RemovePdfComponent(const char* name);
  
  /// Clear the list of PDF components to plot.
  void ClearPdfComponents();
  
  
  /** Set the name of the model PDF (NB. the model must be a RooAddPdf 
      instance, or inherit from it).
  */
  void SetModelName(const char* name);
  
  /// Set the dataset name (NB. the data set must be unbinned).
  void SetDataSetName(const char* name); 
  
  /// Set the name of the named set containing the sWeight variables.
  void SetSWeightSetName(const char* name);
  
  /// Set the name of the named set containing the plot parameters.
  void SetPlotParameterSetName(const char* name);
  
  
  /// Set the line color of the model PDF.
  void SetModelLineColor(Color_t col);

  /// Set the line style of the model PDF.
  void SetModelLineStyle(Style_t style);

  /// Set the line width of the model PDF.
  void SetModelLineWidth(Width_t width);

  /// Set the line attributes of the model PDF.
  void SetModelLineAttributes(Color_t col, Style_t style, Width_t width);

  /// Set the dataset line color.
  void SetDataSetLineColor(Color_t col);

  /// Set the dataset line style.
  void SetDataSetLineStyle(Style_t style);

  /// Set the dataset line width.
  void SetDataSetLineWidth(Width_t width);

  /// Set the dataset line attributes.
  void SetDataSetLineAttributes(Color_t col, Style_t style, Width_t width);  
  
  /// Set the dataset marker color.
  void SetDataSetMarkerColor(Color_t col);

  /// Set the dataset marker style.
  void SetDataSetMarkerStyle(Style_t style);

  /// Set the dataset marker size.
  void SetDataSetMarkerSize(Size_t size);

  /// Set the dataset marker attributes.
  void SetDataSetMarkerAttributes(Color_t col, Style_t style, Size_t size);  

  /// Set the dataset fill color.
  void SetDataSetFillColor(Color_t col);

  /// Set the dataset fill style.
  void SetDataSetFillStyle(Style_t style);

  /// Set the dataset fill attributes.
  void SetDataSetFillAttributes(Color_t col, Style_t style);
  
  
  /// Set the dataset draw options (see TGraphPainter for details).
  void SetDataSetDrawOption(const char* opt);
  
  /// Set the parameter box X1.
  void SetParamBoxX1(Float_t x);
  /// Set the parameter box X2.
  void SetParamBoxX2(Float_t x);
  /// Set the parameter box Y1.
  void SetParamBoxY1(Float_t x);
  /// Set the parameter box Y2.
  void SetParamBoxY2(Float_t x);
  
  /// Set the parameter box text size.
  void SetParamBoxTextSize(Float_t size);

  /// Set the parameter box text alignment (see TAttText for details).
  void SetParamBoxTextAlign(Int_t align);

  /// Set the name of the parameter box.
  void SetParamBoxName(const char* name);
  
  /// Set the parameter box attributes.
  void SetParamBoxAttributes(const char* name, Float_t x1, Float_t y1,
                             Float_t x2, Float_t y2,
                             Float_t textSize=0.03, Int_t textAlign=12);
  
  /// Set the number of global bins to use in subsequent plots.
  void SetPlotBins(Int_t nBins);
  
  /** Set the number of bins to use in subsequent plots for the given variable.
      N.B. This will override the number of global bins.
  */
  void SetPlotBins(const char* name, Int_t nBins);
 
    
  /** Set the default number of bins for a given RooRealVar.
      Optionally, set the number of bins for a given named range.
      If you want to set the number of bins for a given named binning,
      then you should manipulate the RooRealVar object directly 
      using the GetVar method.
      Will raise an exception if the requested variable does not exist in the
      workspace.
  */
  void SetBins(const char* name, Int_t nBins, const char* range=0);
  
  /** Get the specified yield.
      If a range is given, then a new RooRealVar is creating containing 
      the yield, otherwise, a clone of the original yield is returned, 
      unless returnClone is false.
      If fitName is specified, then the fit result snapshot is loaded first.
  */
  RooRealVar* GetYield(const char* name, const char* range="",
                       const char* fitName="", Bool_t returnClone=kTRUE) const;
  
  /// Get the currently attached workspace.
  const RooWorkspace* GetWS() const;
  RooWorkspace* GetWS(); /// mutator version
  
  /// Get a variable from the workspace by name.
  const RooRealVar* GetVar(const char* name) const;
  RooRealVar* GetVar(const char* name); /// mutator version
  
  /// Get a dataset from the workspace by name.
  const RooAbsData* GetDataSet(const char* name) const;
  RooAbsData* GetDataSet(const char* name); /// mutator version
  
  /// Get the RooDataSet with the name given by GetDataSetName().
  const RooDataSet* GetDataSet() const;
  RooDataSet* GetDataSet(); /// mutator version

  /// Get the data set name.
  const char* GetDataSetName() const;
  
  /// Get the PDF with the name given by GetModelName().
  const RooAddPdf* GetModel() const;
  RooAddPdf* GetModel(); /// mutator version

  /// Get the model name.
  const char* GetModelName() const;

  /// Get the sWeight set name.
  const char* GetSWeightSetName() const;

  /// Get the plot parameters named set name.
  const char* GetPlotParamsSetName() const;
  
  /// Get a RooAbsPdf from the workspace by name.
  const RooAbsPdf* GetPdf(const char* name) const;
  RooAbsPdf* GetPdf(const char* name); /// mutator version
  
  /** Get the named set with the given name from the workspace.
      Will raise an exception if the set does not exist in the workspace.
  */
  const RooArgSet* GetNamedSet(const char* name) const;
  
  /** Retrieve the fit result (rfres_${fitName} from the workspace.
      Will raise an exception if the fit result does not exist in the 
      workspace.
  */
  const RooFitResult* GetFitResult(const char* fitName) const;
  RooFitResult* GetFitResult(const char* fitName); /// mutator version
  
  /// Get the line color of the model PDF
  const Color_t& GetModelLineColor() const;
  /// Get the line style of the model PDF
  const Style_t& GetModelLineStyle() const;
  /// Get the line width of the model PDF
  const Width_t& GetModelLineWidth() const;
  
  /** Get the line color of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  const Color_t& GetPdfComponentLineColor(const char* name) const;
  /** Get the line style of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  const Style_t& GetPdfComponentLineStyle(const char* name) const;
  /** Get the line width of the specified PDF component.
      N.B. Will raise an exception if it is not in the list of components.
  */
  const Width_t& GetPdfComponentLineWidth(const char* name) const;

  /// Get the dataset line color.
  const Color_t& GetDataSetLineColor() const;
  /// Get the dataset line style.
  const Style_t& GetDataSetLineStyle() const;
  /// Get the dataset line width.
  const Width_t& GetDataSetLineWidth() const;
  
  /// Get the dataset marker color.
  const Color_t& GetDataSetMarkerColor() const;
  /// Get the dataset marker style.
  const Style_t& GetDataSetMarkerStyle() const;
  /// Get the dataset marker width.
  const Size_t& GetDataSetMarkerSize() const;

  /// Get the dataset fill color.
  const Color_t& GetDataSetFillColor() const;
  /// Get the dataset fill style.
  const Style_t& GetDataSetFillStyle() const;
  
  /// Get the dataset draw options (see TGraphPainter for details).
  const char* GetDataSetDrawOption() const;
  
  /// Get the parameter box X1.
  const Float_t& GetParamBoxX1() const;
  /// Get the parameter box X2.
  const Float_t& GetParamBoxX2() const;
  /// Get the parameter box Y1.
  const Float_t& GetParamBoxY1() const;
  /// Get the parameter box Y2.
  const Float_t& GetParamBoxY2() const;
  
  /// Get the parameter box text size.
  const Float_t& GetParamBoxTextSize() const;

  /// Get the paramter box text alignment.
  const Int_t& GetParamBoxTextAlign() const;

  /// Get the parameter box name.
  const char* GetParamBoxName() const;
  
  /** Get the number of plot bins.
      If a name is specified, returns the number of bins for a given
      variable (raises an exception if the number of bins have not
      been defined for this variable)
  */
  const Int_t& GetPlotBins(const char* name="") const;
  
  virtual ~RooPhysFitter( ); ///< Destructor
  
protected:
  // methods
  
  /** Get the number of plot bins.
      Returns the number of bins for this variable, if defined, else
      returns the global number of bins
  */
  virtual const Int_t& GetPlotBinsInt(const char* name) const;
    
  /** get the name of the data histogram in a RooPlot.
      This function is used to get the pull plot.
      NB. You may need to be override this method in a derived class.
  */
  virtual std::string GetDataHistName() const;
  
  /** get the name of the model PDF curve in a RooPlot of the specified
      fit variable.
      This function is used to get the pull plot.
      NB. You may need to be override this method in a derived class.
  */
  virtual std::string GetModelCurveName(const char* var) const;
  
  // data members

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

private:
  // methods

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
};
}
#endif // ROOPHYSFITTER_ROOPHYSFITTER_H
