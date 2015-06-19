// $Id: $
#ifndef ROOPHYSFITTER_ROODPLUSMASSFITTER_H 
#define ROOPHYSFITTER_ROODPLUSMASSFITTER_H 1

// Include files
#include "RooPhysFitter/RooPhysFitter.h"

#include <map>
#include <string>
#include "TFormula.h"

// forward declarations
class TTree;

/** @class RooDplusMassFitter RooDplusMassFitter.h RooPhysFitter/RooDplusMassFitter.h
 *  
 *
 *  @author Philip Hunt (LHCB)
 *  @date   2011-09-19
 */
/* Class to extend the functionality of RooPhysFitter to provide helper 
functions to create a model and unbinned data set for a single 
descriminating variable with two signal peaks. 
In principle, the variable can be any physical parameter, but the model
production functions are designed for a mass variable with two Gaussian-like 
signals, and a simple polynomial background, e.g. D+ and Ds+ masses
*/
namespace RooPhysFit
{
  class RooDplusMassFitter : public RooPhysFit::RooPhysFitter {
  public: 
    ClassDef(RooDplusMassFitter,1);
    
    typedef Double_t(*DoubleFun)(Double_t a);

    enum PartType {UndefinedPart=-1, Dplus=0, Ds=1};
    
    /// Standard constructor
    RooDplusMassFitter( ); 
    RooDplusMassFitter( const char* name, const char* title ); 

    // get the particle name
    const char* GetPartName(RooDplusMassFitter::PartType pType) const;
    Bool_t ValidPartName(RooDplusMassFitter::PartType pType) const;
    
    // create the D+/Ds mass variable
    void MakeDplusMassVar(Float_t xmin, Float_t xmax,
                          const char* unit="MeV/c^{2}",
                          const char* title="");
    
    // Add a "spectator" variable (not used as a fit variable)
    // Optionally, it can added to a named set in the workspace by 
    // specifying "setName". If the branch name in the TTree, brName,
    // is not specified, it is assumed that it has the same name as 
    // the RooRealVar
    void AddSpectator(const char* name, Double_t xmin, Double_t xmax,
                      const char* brName="", const char* unit="",
                      const char* title="", const char* setName="");
    
    // Add a "spectator" variable (not used as a fit variable)
    // Similar to the above AddSpectator method, except that a pointer
    // to a function is used as an argument. The function will take 
    // the branch value (converted to a double) ,and return another double
    // For example, this function can be used to store the natural 
    // logarithm using std::log
    void AddSpectator(const char* name, Double_t xmin, Double_t xmax,
                      RooDplusMassFitter::DoubleFun fun,
                      const char* brName="",
                      const char* unit="", const char* title="",
                      const char* setName="");

    // Add a "spectator" variable (not used as a fit variable)
    // similar to the above AddSpectator method, except that a generic 
    // TFormula is used as an argument. The method will raise an exception 
    // if the number of dimensions is not unity. In addition, the method 
    // does not accept any parameters
    void AddSpectator(const char* name, Double_t xmin, Double_t xmax,
                      TFormula& fun, const char* brName="",
                      const char* unit="", const char* title="",
                      const char* setName="");

    // Add a RooCategory, with the types corresponding to a branch in the 
    // input TTree. If the branch name in the TTree, brName, is not specified,
    // it is assumed that it has the same name as the RooCategory
    // The vector "types" corresponds to the category types. The vector 
    // "indicies" should contain the indices to use for the given type in 
    // sequence. Note that the function will raise an exception if the number
    // of indices is not the same as the number of types
    void AddCategory(const char* name, std::vector<std::string> types,
                     std::vector<Int_t> indices, const char* brName="",
                     const char* title="");

    /***** create D+ signal model *****/
    // single Gaussian
    void MakeDplusMassSigGauss( RooDplusMassFitter::PartType pType,
                                RooRealVar& mu, RooRealVar& sig);
    void MakeDplusMassSigGauss( RooDplusMassFitter::PartType pType,
                                Float_t mu_start, Float_t mu_min,
                                Float_t mu_max,
                                Float_t sig_start, Float_t sig_min,
                                Float_t sig_max,
                                const char* unit="MeV/c^{2}");

    // double Gaussian with single mean
    void MakeDplusMassSigBiGauss( RooDplusMassFitter::PartType pType,
                                  RooRealVar& mu, RooRealVar& sig0, 
                                  RooRealVar& sig1oSig0, RooRealVar& coreFrac,
                                  const char* sig1Name, const char* sig1Title);
    
    void MakeDplusMassSigBiGauss( RooDplusMassFitter::PartType pType,
                                  Float_t mu_start, Float_t mu_min,
                                  Float_t mu_max,
                                  Float_t sig0_start, Float_t sig0_min, 
                                  Float_t sig0_max,
                                  Float_t sig1oSig0_start,
                                  Float_t sig1oSig0_min,
                                  Float_t sig1oSig0_max, 
                                  Float_t coreFrac_start,
                                  const char* unit="MeV/c^{2}");

    // double Gaussian with separate means
    void MakeDplusMassSigBiGauss( RooDplusMassFitter::PartType pType,
                                  RooRealVar& mu0, RooRealVar& mu1,
                                  RooRealVar& sig0, RooRealVar& sig1oSig0,
                                  RooRealVar& coreFrac,
                                  const char* sig1Name, const char* sig1Title);
    
    
    void MakeDplusMassSigBiGauss( RooDplusMassFitter::PartType pType,
                                  Float_t mu0_start, Float_t mu0_min,
                                  Float_t mu0_max,
                                  Float_t mu1_start, Float_t mu1_min,
                                  Float_t mu1_max,
                                  Float_t sig0_start, Float_t sig0_min,
                                  Float_t sig0_max,
                                  Float_t sig1oSig0_start,
                                  Float_t sig1oSig0_min,
                                  Float_t sig1oSig0_max, 
                                  Float_t coreFrac_start,
                                  const char* unit="MeV/c^{2}");

    // single Cruijff PDF
    void MakeDplusMassSigCruijff( RooDplusMassFitter::PartType pType,
                                  RooRealVar& mu, RooRealVar& sigL, 
                                  RooRealVar& sigR, RooRealVar& alphaL,
                                  RooRealVar& alphaR );
    void MakeDplusMassSigCruijff( RooDplusMassFitter::PartType pType,
                                  Float_t mu_start, Float_t mu_min,
                                  Float_t mu_max,
                                  Float_t sigL_start, Float_t sigL_min, 
                                  Float_t sigL_max, Float_t sigR_start,
                                  Float_t sigR_min, Float_t sigR_max,
                                  Float_t alphaL_start, Float_t alphaL_min,
                                  Float_t alphaL_max, Float_t alphaR_start,
                                  Float_t alphaR_min, Float_t alphaR_max,
                                  const char* unit="MeV/c^{2}");
    
    // single Cruijff PDF with common sigma
    void MakeDplusMassSigCruijff( RooDplusMassFitter::PartType pType,
                                  RooRealVar& mu, RooRealVar& sig,
                                  RooRealVar& alphaL, RooRealVar& alphaR );
    void MakeDplusMassSigCruijff( RooDplusMassFitter::PartType pType,
                                  Float_t mu_start, Float_t mu_min,
                                  Float_t mu_max,
                                  Float_t sig_start, Float_t sig_min, 
                                  Float_t sig_max,
                                  Float_t alphaL_start, Float_t alphaL_min,
                                  Float_t alphaL_max, Float_t alphaR_start,
                                  Float_t alphaR_min, Float_t alphaR_max,
                                  const char* unit="MeV/c^{2}");
    
    // single Crystal Ball PDF
    void MakeDplusMassSigCB( RooDplusMassFitter::PartType pType,
                             RooRealVar& mu, RooRealVar& sig,
                             RooRealVar& alpha, RooRealVar& n);
    void MakeDplusMassSigCB( RooDplusMassFitter::PartType pType,
                             Float_t mu_start, Float_t mu_min, Float_t mu_max,
                             Float_t sig_start, Float_t sig_min,
                             Float_t sig_max,
                             Float_t alpha_start, Float_t alpha_min,
                             Float_t alpha_max, Float_t n_start, Float_t n_min,
                             Float_t n_max, const char* unit="MeV/c^{2}");

    /***** create D+ background model *****/
    // D+ flat background (unit is the "mass" unit)
    void MakeDplusMassBkgFlat(RooRealVar& grad);
    void MakeDplusMassBkgFlat(Float_t grad_start, Float_t grad_min,
                              Float_t grad_max,
                              const char* unit="MeV/c^{2}");
    
    // D+ quadratic background
    void MakeDplusMassBkgQuadratic(RooRealVar& c1, RooRealVar& c2);
    void MakeDplusMassBkgQuadratic(Float_t c1_start, Float_t c1_min,
                                   Float_t c1_max,
                                   Float_t c2_start, Float_t c2_min, 
                                   Float_t c2_max,
                                   const char* unit="MeV/c^{2}");
    // D+ cubic background
    void MakeDplusMassBkgCubic(RooRealVar& c1, RooRealVar& c2, RooRealVar& c3);
    void MakeDplusMassBkgCubic(Float_t c1_start, Float_t c1_min,
                               Float_t c1_max,
                               Float_t c2_start, Float_t c2_min,
                               Float_t c2_max,
                               Float_t c3_start, Float_t c3_min,
                               Float_t c3_max,
                               const char* unit="MeV/c^{2}");

    // make 1D D0 model - specify expected fraction of each background type
    // NB. No check that sum(frac)==1
    // If a starting value for a model fraction is less than zero, then this
    // model type will be ignored. This is useful to produce partial models
    // e.g. a background-only model
    // The method will raise an exception if all fractions are less than zero
    void MakeDplusMassModel(Float_t frac_dplus, Float_t frac_ds,
                            Float_t frac_bkg);
    
    // Create a dataset with name "name" from a TTree tt.
    // The branch name in the TTree for the D+/Ds mass is specified by
    // "dplusMassVarname"
    // If the data set name is specified, then the value set by the
    // SetDataSetName method will be overwritten with the new name,
    // otherwise the name set by the SetDataSetName
    // method will be used as the data set name
    void MakeDplusMassDataSet(TTree* tt, const char* dplusMassVarname, 
                              const char* name="", const char* title="", 
                              const char* cuts="");
    
    // Perform a binned fit to the model PDF
    // A binned clone of the data is made, which is then used to fit the PDF
    // The default binning for each variable in the original dataset is used,
    // except for the mass variable, which uses the specified number of bins
    // The number of bins for a given variable can be changed using the
    // SetBins method
    // By default, a maximum likelihood fit is performed. If useChi2Method is
    // set to true, then a chi^2 fit is performed instead
    void PerformDplusMassBinnedFit(Int_t nBins,
                                   const char* fitName="fitResults", 
                                   Int_t nCores=4,
                                   Bool_t saveSnapshot=kTRUE, 
                                   Bool_t printResults=kFALSE,
                                   Bool_t useSumW2Errors=kFALSE, 
                                   Bool_t extendedMode=kTRUE,
                                   Bool_t useChi2Method=kFALSE);

    void SetDplusMassSigPartName(RooDplusMassFitter::PartType pType,
                                 const char* name);
    void SetDplusMassBkgPartName(const char* name);
   
    void SetDplusMassName(const char* name);

    void SetDplusMassSigModelName(RooDplusMassFitter::PartType pType,
                                  const char* name);
    void SetDplusMassBkgModelName(const char* name);

    void SetDplusMassSigYieldName(RooDplusMassFitter::PartType pType,
                                  const char* name);
    void SetDplusMassBkgYieldName(const char* name);

    void SetSpectatorSetName(const char* name);
    void SetCategorySetName(const char* name);

    void SetPrintEntriesFlag(Bool_t flag);
    void SetPrintFreq(Int_t freq);

    const char* GetDplusMassSigPartName(RooDplusMassFitter::PartType pType) const;
    const char* GetDplusMassBkgPartName() const;

    const char* GetDplusMassName() const;

    const char* GetDplusMassSigModelName(RooDplusMassFitter::PartType pType) const;
    const char* GetDplusMassBkgModelName() const;

    const char* GetDplusMassSigYieldName(RooDplusMassFitter::PartType pType) const;
    const char* GetDplusMassBkgYieldName() const;

    const char* GetSpectatorSetName() const;
    const char* GetCategorySetName() const;
    
    const Bool_t& GetPrintEntriesFlag() const;
    const Int_t& GetPrintFreq() const;
    
    const char* GetDplusMassSigPartLabel(RooDplusMassFitter::PartType pType) const;

    virtual ~RooDplusMassFitter( ); ///< Destructor

  protected:

    // methods
    std::string GetBranchType(TTree* tt, std::string brName);
    
    // data members
    const char* m_dplusMassName;
    const char* m_dplusMassDplusPartName;
    const char* m_dplusMassDsPartName;
    const char* m_dplusMassBkgPartName;
    const char* m_dplusMassDplusModelName;
    const char* m_dplusMassDsModelName;
    const char* m_dplusMassBkgModelName;
    const char* m_dplusMassDplusYieldName;
    const char* m_dplusMassDsYieldName;
    const char* m_dplusMassBkgYieldName;
    const char* m_spectSetName;
    const char* m_catSetName;
    Bool_t m_printEntries;
    Int_t m_printFreq;
  
    // map of the RooRealVar name of the spectator to the leaf name in the TTree
    std::map< std::string, std::string > m_varNameToBranchName;
    
    // map of the RooCategory name of the category to the leaf name in the TTree
    std::map< std::string, std::string > m_catNameToBranchName;
    
    // map of the RooRealVar name of the spectator to the function to be 
    // applied to the leaf value  
    std::map< std::string, RooDplusMassFitter::DoubleFun > m_varNameToFunction;
    // map of the RooRealVar name of the spectator to the TFormula to be 
    // applied to the leaf value  
    std::map< std::string, TFormula > m_varNameToFormula;
  private:
  };
}

#endif // ROOPHYSFITTER_ROODPLUSMASSFITTER_H
