#ifndef V0HHFITTER_FITTERPULLS_H
#define V0HHFITTER_FITTERPULLS_H 1

/***************************
 * FitterPulls                *
 *                         *
 * © 2004 Thomas Latham    *
 *    and Nicole Chevalier *
 ***************************/

// STL include
#include <vector>
#include <numeric>

// ROOT 
#include "TFile.h"
#include "TString.h"

// RooFit
#include "RooArgList.h"
#include "RooFitResult.h"
#include "RooArgSet.h"

namespace V0hhFit {
  
  class FitterPulls {
  public:
    FitterPulls(); 
    FitterPulls(const RooArgList& floatList); 
    FitterPulls(std::vector<std::string> files, std::string dataFitName="dataFit", bool syst = false); 
    virtual ~FitterPulls();
	
    virtual void dataFitResult(const RooFitResult* fitres);
	virtual void createVectors(const RooArgList& floatList); 
	virtual void createVectors_Syst(const RooArgList& floatList); 
	virtual void createVectors_SystII(std::vector<std::string> names);
	
	/** fillVectors - fills toy information. This method will take the 
	 * initial parameters of the RooFitResults were the nominal values.
	 @param fitres RooFitResult of the fit to toy data. 
	*/
	virtual void fillVectors(const RooFitResult* fitres);
    
	/** fillVectors - fills toy information. This method will takes two 
	 * input arguments, one for the nominal fit result and thus truth, the second the initial parameters of the RooFitResults were the nominal values.
	 @param fitres RooFitResult of the fit to toy data. 
	 @param fitres RooFitResult of the fit to toy data. 
	*/
	virtual void fillVectors(const RooArgSet* genParams,
							 const RooArgSet* toyParams,
							 const RooFitResult* toyFitRes);
	
	virtual void fillVectors_Syst(const RooFitResult* fitres_official, 
								  const RooFitResult* fitres_toyMC); 
	
	virtual void fillVectors_SystII(std::vector<std::string> files);
	
	virtual void fillVectors_SystII(const RooFitResult* fitres_official, 
									const RooFitResult* fitres_toyMC); 
	
	virtual void setBins( Int_t bins ) { m_nBins = bins; }
	virtual void writeVectors(TString filename) const;
	
	virtual void plotErrorVsResiduals(TString dir, TString filename) const;
	virtual void plotPulls(TString filename, Int_t nCores = 2, 
						   Double_t plotLimit = 5.0, Double_t fitLimit = 5.0 ) const;
	virtual void plotPulls_DP(TString filename, Int_t nCores = 2, 
						   Double_t plotLimit = 5.0, Double_t fitLimit = 5.0 ) const;
	virtual void plotConstant(TString dir, TString filename, Int_t nCores = 2) const;
	virtual void plotEdms(TString filename) const;
	virtual void plotNlls(TString filename) const;
	virtual void plotResiduals( TString dir, std::string filename, Int_t nCores = 2 ) const;
	virtual void plotResiduals( TString filename, Int_t nCores = 2 ) const;
	virtual void plotValues( TString dir, TString filename, Int_t nCores = 2 ) const;
	virtual void plotValues( TString filename, Int_t nCores = 2 ) const;
	virtual void plotToyResiduals( TString filename, Int_t nCores = 2 ) const;
	virtual void plotToyValues( TString filename, Int_t nCores = 2 ) const;
	virtual void plotSystI( TString filename, std::string paramName, Int_t nCores = 4 ) const;
	virtual void plotSystI_DP( TString filename, std::string paramName, Int_t nCores = 4 ) const;
	virtual void plotSystII( TString filename, Int_t nCores = 2 ) const;
	
	virtual Double_t average_edm() const { return std::accumulate(m_edm.begin(), m_edm.end(), 0.0)/ static_cast<Double_t>( m_edm.size() ); }
	virtual Double_t last_edm() const { return m_edm.back(); }
	virtual Int_t last_status() const { return m_status.back(); }
	virtual Int_t last_covQual() const { return m_covQual.back(); }
	
  protected:
	
  private:
	Int_t m_nBins; // number of bins for plotting
	Int_t m_nVars; // number of float variables
	const RooFitResult* m_dataRes;
	Double_t m_dataNll;
	
	std::vector<TString> m_paramName;
	std::vector<TString> m_constName; //Constant parameters which are varied over (Syst I study)
	std::vector<const RooFitResult*> m_results;			
	std::vector<std::vector<Double_t> > m_constants; //Constant parameters which are varied over (Syst I study)
	std::vector<std::vector<Double_t> > m_pulls;
	std::vector<std::vector<Double_t> > m_errors;
	std::vector<std::vector<Double_t> > m_errorLo;
	std::vector<std::vector<Double_t> > m_errorHi;
	std::vector<std::vector<Double_t> > m_values;
	std::vector<std::vector<Double_t> > m_residuals;
	std::vector<std::vector<Double_t> > m_toyValues;     // Values used for generation (ie. post gaussian randomization & poissonization)
	std::vector<std::vector<Double_t> > m_toyResiduals;  // Difference between m_values & genResiduals.
	std::vector<std::vector<Double_t> > m_SystI;
	//			std::vector<std::vector<Double_t> > m_varPars; // Keeps track of the variation of parameters used in Syst I. studies to ensure it's done correctly.
	std::vector<std::vector<Double_t> > m_SystII;
	std::vector<Double_t> m_nlls;
	std::vector<Double_t> m_edm;
	std::vector<Int_t>    m_status;
	std::vector<Int_t>    m_covQual;
	
	ClassDef(FitterPulls,1); // Pulls Class	
  };
  
  inline void FitterPulls::dataFitResult(const RooFitResult* fitres) {
	  m_dataRes = fitres;
	  m_dataNll = fitres->minNll();
	  
  }
  
}

#endif // V0HHFITTER_FITTERPULLS_H
