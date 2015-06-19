// $Id: $
#ifndef ROOPHYSFITTER_ROODMASSFITTER_H
#define ROOPHYSFITTER_ROODMASSFITTER_H 1

// Include files
#include "RooPhysFitter/RooPhysFitter.h"

#include <map>
#include <string>
#include "TFormula.h"

// forward declarations
class TTree;

/** @class RooDMassFitter RooDMassFitter.h RooPhysFitter/RooDMassFitter.h

    Class to extend the functionality of RooPhysFitter to provide helper
    functions to create a model and unbinned data set for a single
    descriminating variable.
    In principle, the variable can be any physical parameter, but the
    model production functions are designed for a mass variable with a
    Gaussian-like signal, and a simple polynomial background, e.g. D^0 mass.

    @author Philip Hunt (LHCB)
    @date   2011-05-16
*/

namespace RooPhysFit
{
  class RooDMassFitter : public RooPhysFit::RooPhysFitter {
  public:
    ClassDef(RooDMassFitter,1);

    typedef Double_t(*DoubleFun)(Double_t a);

    /// Standard constructor
    RooDMassFitter( );
    /// Overloaded constructor
    RooDMassFitter( const char* name, const char* title);

    /// Create the D0 mass variable.
    void MakeDMassVar(Float_t xmin, Float_t xmax,
                      const char* unit="MeV/c^{2}",
                      const char* title="");

    /** Add a "spectator" variable (not used as a fit variable).
        Optionally, it can added to a named set in the workspace
        by specifying "setName".
        If the branch name in the TTree, brName, is not specified,
        it is assumed that it has the same name as the RooRealVar.
    */
    void AddSpectator(const char* name, Double_t xmin, Double_t xmax,
                      const char* brName="", const char* unit="",
                      const char* title="", const char* setName="");

    /** Add a "spectator" variable (not used as a fit variable).
        Similar to the above AddSpectator method, except that a pointer
        to a function is used as an argument. The function will take
        the branch value (converted to a double) ,and return another double.
        For example, this function can be used to store the natural
        logarithm using std::log.
    */
    void AddSpectator(const char* name, Double_t xmin, Double_t xmax,
                      RooDMassFitter::DoubleFun fun,
                      const char* brName="",
                      const char* unit="", const char* title="",
                      const char* setName="");

    /** Add a "spectator" variable (not used as a fit variable).
        Similar to the above AddSpectator method, except that a
        generic TFormula is used as an argument. The method will raise an
        exception if the number of dimensions is nit unity. In addition,
        the method does not accept any parameters.
    */
    void AddSpectator(const char* name, Double_t xmin, Double_t xmax,
                      TFormula& fun, const char* brName="",
                      const char* unit="", const char* title="",
                      const char* setName="");

    /** Add a RooCategory, with the types corresponding to a branch in the
        input TTree.
        If the branch name in the TTree, brName, is not specified, it is
        assumed that it has the same name as the RooCategory.
        The vector "types" corresponds to the category types. The vector
        "indicies" should contain the indices to use for the given type
        in sequence. Note that the function will raise an exception if
        the number of indices is not the same as the number of types.
    */
    void AddCategory(const char* name, std::vector<std::string> types,
                     std::vector<Int_t> indices, const char* brName="",
                     const char* title="");

     /** Add a RooCategory, with the types corresponding to a branch in the
        input TTree.
        Similar the the other AddCategory method, but takes C-style
        arrays of types and indices instead of vectors. This means that
        this method can be used in CINT.
        The additional argument, 'ntypes' is the number of types
        in the category (i.e. the length of the indices and types arrays).
        */
    void AddCategory(const char* name, TString* types,
                     Int_t* indices, UInt_t ntypes, const char* brName="",
                     const char* title="");
    /// Single Gaussian D0 signal model
    void MakeDMassSigGauss( RooRealVar& mu, RooRealVar& sig);
    /// Single Gaussian D0 signal model
    void MakeDMassSigGauss( Float_t mu_start, Float_t mu_min, Float_t mu_max,
                            Float_t sig_start, Float_t sig_min, Float_t sig_max,
                            const char* unit="MeV/c^{2}");

    /// Double Gaussian D0 signal model with single mean
    void MakeDMassSigBiGauss( RooRealVar& mu, RooRealVar& sig0,
                              RooRealVar& sig1oSig0,
                              RooRealVar& coreFrac,
                              const char* sig1Name, const char* sig1Title);
    /// Double Gaussian D0 signal model with single mean
    void MakeDMassSigBiGauss( Float_t mu_start, Float_t mu_min,
                              Float_t mu_max,
                              Float_t sig0_start, Float_t sig0_min,
                              Float_t sig0_max,
                              Float_t sig1oSig0_start, Float_t sig1oSig0_min,
                              Float_t sig1oSig0_max, Float_t coreFrac_start,
                              const char* unit="MeV/c^{2}");

    /// Double Gaussian D0 signal model with separate means
    void MakeDMassSigBiGauss( RooRealVar& mu0, RooRealVar& mu1,
                              RooRealVar& sig0, RooRealVar& sig1oSig0,
                              RooRealVar& coreFrac,
                              const char* sig1Name, const char* sig1Title);
    /// Double Gaussian D0 signal model with separate means
    void MakeDMassSigBiGauss( Float_t mu0_start, Float_t mu0_min,
                              Float_t mu0_max,
                              Float_t mu1_start, Float_t mu1_min,
                              Float_t mu1_max,
                              Float_t sig0_start, Float_t sig0_min,
                              Float_t sig0_max,
                              Float_t sig1oSig0_start, Float_t sig1oSig0_min,
                              Float_t sig1oSig0_max, Float_t coreFrac_start,
                              const char* unit="MeV/c^{2}");

    /// Triple Gaussian D0 signal model with single mean
    void MakeDMassSigTriGauss( RooRealVar& mu, RooRealVar& sig0,
                               RooRealVar& sig1oSig0,
                               RooRealVar& sig2oSig0,
                               RooRealVar& coreFrac0, RooRealVar& coreFrac1,
                               const char* sig1Name, const char* sig1Title);
    /// Triple Gaussian D0 signal model with single mean
    void MakeDMassSigTriGauss( Float_t mu_start, Float_t mu_min,
                               Float_t mu_max,
                               Float_t sig0_start, Float_t sig0_min,
                               Float_t sig0_max,
                               Float_t sig1oSig0_start, Float_t sig1oSig0_min,
                               Float_t sig1oSig0_max,
                               Float_t sig2oSig0_start, Float_t sig2oSig0_min,
                               Float_t sig2oSig0_max,
                               Float_t coreFrac0_start,
                               Float_t coreFrac1_start,
                               const char* unit="MeV/c^{2}");

    /// Single D0 signal model Cruijff PDF
    void MakeDMassSigCruijff( RooRealVar& mu, RooRealVar& sigL,
                              RooRealVar& sigR, RooRealVar& alphaL,
                              RooRealVar& alphaR );
    /// Single D0 signal model Cruijff PDF
    void MakeDMassSigCruijff( Float_t mu_start, Float_t mu_min,
                              Float_t mu_max,
                              Float_t sigL_start, Float_t sigL_min,
                              Float_t sigL_max, Float_t sigR_start,
                              Float_t sigR_min, Float_t sigR_max,
                              Float_t alphaL_start, Float_t alphaL_min,
                              Float_t alphaL_max, Float_t alphaR_start,
                              Float_t alphaR_min, Float_t alphaR_max,
                              const char* unit="MeV/c^{2}");

    /// Single D0 signal model Cruijff PDF with common sigma
    void MakeDMassSigCruijff( RooRealVar& mu, RooRealVar& sig,
                              RooRealVar& alphaL, RooRealVar& alphaR );
    /// Single D0 signal model Cruijff PDF with common sigma
    void MakeDMassSigCruijff( Float_t mu_start, Float_t mu_min, Float_t mu_max,
                              Float_t sig_start, Float_t sig_min,
                              Float_t sig_max,
                              Float_t alphaL_start, Float_t alphaL_min,
                              Float_t alphaL_max, Float_t alphaR_start,
                              Float_t alphaR_min, Float_t alphaR_max,
                              const char* unit="MeV/c^{2}");


    /// Single D0 model Crystal Ball PDF
    void MakeDMassSigCB( RooRealVar& mu, RooRealVar& sig, RooRealVar& alpha,
                         RooRealVar& n);
    /// Single D0 model Crystal Ball PDF
    void MakeDMassSigCB( Float_t mu_start, Float_t mu_min, Float_t mu_max,
                         Float_t sig_start, Float_t sig_min, Float_t sig_max,
                         Float_t alpha_start, Float_t alpha_min,
                         Float_t alpha_max, Float_t n_start, Float_t n_min,
                         Float_t n_max, const char* unit="MeV/c^{2}");

    /** Voigtian distribution (Gaussian(x)Lorentzian(Breit-Wigner)
        distribution).
        Commonly used in particle physics to represent a mass distribution
        with a non-negligible width (e.g. a phi).
        If doFast is false, then the errors are calculated using the
        standard CERNLIB algorithm is used.
        If doFast is true, then a complex error look-up table is used.
    */
    void MakeDMassSigVoigtian(RooRealVar& mu, RooRealVar& sig,
                              RooRealVar& gamma, Bool_t doFast=kFALSE);
    /** Voigtian distribution (Gaussian(x)Lorentzian(Breit-Wigner)
        distribution).
        Commonly used in particle physics to represent a mass distribution
        with a non-negligible width (e.g. a phi).
        If doFast is false, then the errors are calculated using the
        standard CERNLIB algorithm is used.
        If doFast is true, then a complex error look-up table is used.
    */
    void MakeDMassSigVoigtian(Float_t mu_start, Float_t mu_min,
                              Float_t mu_max,
                              Float_t sig_start, Float_t sig_min,
                              Float_t sig_max,
                              Float_t gamma_start, Float_t gamma_min,
                              Float_t gamma_max, const char* unit="MeV/c^{2}",
                              Bool_t doFast=kFALSE);
    /// RooVoigtian with a fixed gamma (full width at half maximum).
    void MakeDMassSigVoigtian(Float_t mu_start, Float_t mu_min,
                              Float_t mu_max,
                              Float_t sig_start, Float_t sig_min,
                              Float_t sig_max,
                              Float_t gamma, const char* unit="MeV/c^{2}",
                              Bool_t doFast=kFALSE);

    /// D0 exponential background model (unit is the "mass" unit)
    void MakeDMassBkgExp(RooRealVar& decay);
    /// D0 exponential background model (unit is the "mass" unit)
    void MakeDMassBkgExp(Float_t decay_start, Float_t decay_min,
                          Float_t decay_max,
                          const char* unit="MeV/c^{2}");

    /// D0 flat background model (unit is the "mass" unit)
    void MakeDMassBkgFlat(RooRealVar& grad);
    /// D0 flat background model (unit is the "mass" unit)
    void MakeDMassBkgFlat(Float_t grad_start, Float_t grad_min,
                          Float_t grad_max,
                          const char* unit="MeV/c^{2}");

    /// D0 quadratic background model
    void MakeDMassBkgQuadratic(RooRealVar& c1, RooRealVar& c2);
    /// D0 quadratic background model
    void MakeDMassBkgQuadratic(Float_t c1_start, Float_t c1_min,
                               Float_t c1_max,
                               Float_t c2_start, Float_t c2_min,
                               Float_t c2_max,
                               const char* unit="MeV/c^{2}");

    /// D0 cubic background model
    void MakeDMassBkgCubic(RooRealVar& c1, RooRealVar& c2, RooRealVar& c3);
    /// D0 quadratic background model
    void MakeDMassBkgCubic(Float_t c1_start, Float_t c1_min, Float_t c1_max,
                           Float_t c2_start, Float_t c2_min, Float_t c2_max,
                           Float_t c3_start, Float_t c3_min, Float_t c3_max,
                           const char* unit="MeV/c^{2}");

    /// Phi->KK background model
    void MakePhiBkg(RooRealVar& c1, RooRealVar& c2);
    /// Phi->KK background model
    void MakePhiBkg(Float_t c1_start, Float_t c1_min, Float_t c1_max,
                    Float_t c2_start, Float_t c2_min, Float_t c2_max,
                    const char* unit="MeV/c^{2}");

    /** Make one-dimensional (D0) model - specify expected fraction of each
        background type.
        NB. No check that sum(frac)==1.
        If a starting value for a model fraction is less than zero, then this
        model type will be ignored. This is useful to produce partial models
        e.g. a background-only model.
        The method will raise an exception if all fractions are less than zero.
    */
    void MakeDMassModel(Float_t frac_sig, Float_t frac_bkg);

    /** Create a dataset with name "name" from a TTree tt.
        The branch name in the TTree for the D0 mass is specified by
        "d0MassVarname".
        If the data set name is specified, then the value set by the
        SetDataSetName method will be overwritten with the new name,
        otherwise the name set by the SetDataSetName method will be used
        as the data set name.
    */
    void MakeDMassDataSet(TTree* tt, const char* dMassVarname,
                          const char* name="",
                          const char* title="", const char* cuts="");

    /** Perform a binned fit to the model PDF.
        See RooPhysFitter::PerformBinnedFit for a description of the
        arguments.
    */
    void PerformDMassBinnedFit(Int_t nBins,
                               const char* fitName="fitResults",
                               Int_t nCores=4,
                               Bool_t saveSnapshot=kTRUE,
                               Bool_t printResults=kFALSE,
                               Bool_t useSumW2Errors=kFALSE,
                               Bool_t extendedMode=kTRUE,
                               Bool_t useChi2Method=kFALSE);

    /** Perform an iterative binned fit to the model PDF.
        See RooPhysFitter::PerformIterativeBinnedFit for a description of the
        arguments.
    */
    void PerformDMassIterativeBinnedFit(Int_t nBins,
                                        std::vector<Int_t>& minuitStrategies,
                                        const char* fitName="fitResults",
                                        Int_t nCores=4,
                                        Bool_t saveSnapshot=kTRUE,
                                        Bool_t printResults=kFALSE,
                                        Bool_t useSumW2Errors=kFALSE,
                                        Bool_t extendedMode=kTRUE,
                                        Bool_t useChi2Method=kFALSE);

    /// Set the name of the D particle (used to label fit components)
    void SetDMassPartName(const char* name);
    /// Set the name of the D mass variable (in the RooDataSet)
    void SetDMassName(const char* name);
    /// Set the signal model name
    void SetDMassSigModelName(const char* name);
    /// Set the background model name
    void SetDMassBkgModelName(const char* name);
    /// Set the signal yield name (e.g. "nsig")
    void SetDMassSigYieldName(const char* name);
    /// Set the background yield name (e.g. "nbkg")
    void SetDMassBkgYieldName(const char* name);
    /// Set the name of the spectator named set
    void SetSpectatorSetName(const char* name);
    /// Set the name of the named set for RooCategories
    void SetCategorySetName(const char* name);
    /// Set the 'PrintEntries' flag
    void SetPrintEntriesFlag(Bool_t flag);
    /// Set the print frequency (used when constructing the dataset)
    void SetPrintFreq(Int_t freq);

    /// Get the name of the D particle
    const char* GetDMassPartName() const;
    /// Get the D mass variable name
    const char* GetDMassName() const;
    /// Get the signal model name
    const char* GetDMassSigModelName() const;
    /// Get the background model name
    const char* GetDMassBkgModelName() const;
    /// Get the signal yield name
    const char* GetDMassSigYieldName() const;
    /// Get the background yield name
    const char* GetDMassBkgYieldName() const;
    /// Get the name of the "Spectator" named set
    const char* GetSpectatorSetName() const;
    /// Get the name of the "Category" named set
    const char* GetCategorySetName() const;
    /// Get the "PrintEntries" flag
    const Bool_t& GetPrintEntriesFlag() const;
    /// Get the print frequency
    const Int_t& GetPrintFreq() const;

    virtual ~RooDMassFitter( ); ///< Destructor

  protected:
    // methods

    /** Get the branch name for a given variable name,
        returning the variable name if not found.
    */
    virtual std::string GetVarBranchName(const std::string& name) const;

    /** Get the branch name for a given category name,
        returning the category name if not found.
    */
    virtual std::string GetCatBranchName(const std::string& name) const;

    /// Get the branch type
    std::string GetBranchType(TTree* tt, const std::string& brName) const;

    // data members
    const char* m_dMassPartName;
    const char* m_dMassName;
    const char* m_dMassSigModelName;
    const char* m_dMassBkgModelName;
    const char* m_dMassSigYieldName;
    const char* m_dMassBkgYieldName;
    const char* m_spectSetName;
    const char* m_catSetName;
    Bool_t m_printEntries;
    Int_t m_printFreq;

    /** Map of the RooRealVar name of the spectator to the leaf name
        in the TTree
    */
    std::map< std::string, std::string > m_varNameToBranchName;

    /** Map of the RooCategory name of the category to the leaf name
        in the TTree
    */
    std::map< std::string, std::string > m_catNameToBranchName;

    /** Map of the RooRealVar name of the spectator to the function to
        be applied to the leaf value.
    */
    std::map< std::string, RooDMassFitter::DoubleFun > m_varNameToFunction;
    /** Map of the RooRealVar name of the spectator to the TFormula to
        be applied to the leaf value.
    */
    std::map< std::string, TFormula > m_varNameToFormula;
  private:
  };
}
#endif // ROOPHYSFITTER_ROODMASSFITTER_H
