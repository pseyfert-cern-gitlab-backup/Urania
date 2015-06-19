// $Id: $
// Include files 
// C++ libraries
#include <sstream>
#include <iostream>

// RooFit
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooPhysFitter/RooGranet.h"
#include "RooDstD0BG.h"
#include "RooPhysFitter/RooCruijff.h"
#include "RooPhysFitter/RooCruijffSimple.h"

// ROOT 
#include "TChain.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TString.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TEntryList.h"
//#include "TEventList.h"

// local
#include "RooPhysFitter/RooDstarD0MassFitter.h"
#include "RooPhysFitter/Exceptions.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RooDstarD0MassFitter
//
// 2011-05-19 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

using namespace RooPhysFit;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RooDstarD0MassFitter::RooDstarD0MassFitter(  ) : RooDMassFitter() {
  m_dMassPartName="D^{0}";
  m_delmPartName="#Delta_{m}";
  m_delmName="delm";

  m_dMassSigModelName="d0MassSigModel";
  m_dMassBkgModelName="d0MassBkgModel";

  m_delmSigModelName="delmSigModel";
  m_delmBkgModelName="delmBkgModel";

  m_2dMassSigModelName="sig2DModel";
  m_2dMassCombBkgModelName="combBkg2DModel";
  m_2dMassPiBkgModelName="piBkg2DModel";
  m_2dMassD0BkgModelName="d0Bkg2DModel";
  m_2dMassCombinedBkgModelName="bkg2DModel";
  
  m_2dMassSigYieldName="nsig";
  m_2dMassCombBkgYieldName="nbkg_comb";
  m_2dMassPiBkgYieldName="nbkg_randPi";
  m_2dMassD0BkgYieldName="nbkg_fakeD0";
  m_2dMassCombinedBkgYieldName="nbkg";
}

RooDstarD0MassFitter::RooDstarD0MassFitter(const char* name, const char* title)
  : RooDMassFitter(name, title) 
{
  m_dMassPartName="D^{0}";
  m_delmPartName="#Delta_{m}";
  m_delmName="delm";

  m_dMassSigModelName="d0MassSigModel";
  m_dMassBkgModelName="d0MassBkgModel";

  m_delmSigModelName="delmSigModel";
  m_delmBkgModelName="delmBkgModel";

  m_2dMassSigModelName="sig2DModel";
  m_2dMassCombBkgModelName="combBkg2DModel";
  m_2dMassPiBkgModelName="piBkg2DModel";
  m_2dMassD0BkgModelName="d0Bkg2DModel";
  m_2dMassCombinedBkgModelName="bkg2DModel";
  
  m_2dMassSigYieldName="nsig";
  m_2dMassCombBkgYieldName="nbkg_comb";
  m_2dMassPiBkgYieldName="nbkg_randPi";
  m_2dMassD0BkgYieldName="nbkg_fakeD0";
  m_2dMassCombinedBkgYieldName="nbkg";
}

void RooDstarD0MassFitter::MakeDelmVar(Float_t xmin, Float_t xmax,
                                       const char* unit, const char* title)
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmVar",
                           "No RooWorkspace object is defined.");
  }
  if (!m_delmName||strcmp(m_delmName,"")==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmVar",
                           "No Delta mass variable name specified.");
  }
  RooRealVar delm(m_delmName,(!title)?"":title,xmin,xmax,
                  (!unit)?"MeV/c^{2}":unit);
  if (m_rws->import(delm)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmVar", *m_rws, delm);
  }
}

void RooDstarD0MassFitter::MakeDelmSigGauss(RooRealVar& mu, RooRealVar& sig) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigGauss",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooGaussian delmSigModel(m_delmSigModelName, "", *delm, mu, sig);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigGauss",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigGauss(Float_t mu_start, Float_t mu_min,
                                            Float_t mu_max, Float_t sig_start,
                                            Float_t sig_min, Float_t sig_max,
                                            const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigGauss",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
  }
  else {
    muTitle.Form("%s #mu", m_delmPartName);
    sigTitle.Form("%s #sigma", m_delmPartName);
  }
  
  RooRealVar mu("delm_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("delm_sig_sigma", sigTitle.Data(), sig_start, sig_min, 
                 sig_max, unit);
  RooGaussian delmSigModel(m_delmSigModelName, "", *delm, mu, sig);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigGauss",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigBiGauss(RooRealVar& mu,
                                              RooRealVar& sig0,
                                              RooRealVar& sig1oSig0,
                                              RooRealVar& coreFrac,
                                              const char* sig1Name,
                                              const char* sig1Title) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           *m_rws, m_delmName, "RooRealVar");
  }

  RooGaussian delm_sig_g0("delm_sig_gauss0", "", *delm, mu, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(sig0.getUnit());

  RooGaussian delm_sig_g1("delm_sig_gauss1", "", *delm, mu, sig1);
  RooAddPdf delmSigModel(m_delmSigModelName, "",
                          RooArgList(delm_sig_g0,delm_sig_g1),
                          RooArgList(coreFrac));
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigBiGauss(Float_t mu_start,
                                               Float_t mu_min,
                                               Float_t mu_max,
                                               Float_t sig0_start,
                                               Float_t sig0_min,
                                               Float_t sig0_max,
                                               Float_t sig1oSig0_start,
                                               Float_t sig1oSig0_min,
                                               Float_t sig1oSig0_max,
                                               Float_t coreFrac_start,
                                               const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           *m_rws, m_delmName, "RooRealVar");
  }
  
  TString muTitle="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString coreFracTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    muTitle="#mu";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
    sig1Title="#sigma_{tail}";
    coreFracTitle="f_{core}";
  }
  else {
    muTitle.Form("%s #mu", m_delmPartName);
    sig0Title.Form("%s #sigma_{core}", m_delmPartName);
    sig1Title.Form("%s #sigma_{tail}", m_delmPartName);
    sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_delmPartName);
    coreFracTitle.Form("%s f_{core}", m_delmPartName);
  }
   
  RooRealVar mu("delm_sig_mu", muTitle.Data(), mu_start,
                mu_min, mu_max, unit);
  RooRealVar sig0("delm_sig_sigma0", sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian delm_sig_g0("delm_sig_gauss0", "", *delm, mu, sig0);

  RooRealVar sig1oSig0("delm_sig_s1oS0", sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
  
  RooFormulaVar sig1("delm_sig_sigma1", sig1Title.Data(), "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);
 
  RooGaussian delm_sig_g1("delm_sig_gauss1", "", *delm, mu, sig1);

  RooRealVar coreFrac("delm_sig_coreFrac", coreFracTitle.Data(),
                      coreFrac_start,0.0,1);
  
  RooAddPdf delmSigModel(m_delmSigModelName, "", 
                          RooArgList(delm_sig_g0,delm_sig_g1),
                          RooArgList(coreFrac));
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                          *m_rws, delmSigModel);
  }
}


void RooDstarD0MassFitter::MakeDelmSigBiGauss(RooRealVar& mu0,
                                              RooRealVar& mu1,
                                              RooRealVar& sig0,
                                              RooRealVar& sig1oSig0,
                                              RooRealVar& coreFrac,
                                              const char* sig1Name,
                                              const char* sig1Title) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooGaussian delm_sig_g0("delm_sig_gauss0", "", *delm, mu0, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(sig0.getUnit());

  RooGaussian delm_sig_g1("delm_sig_gauss1", "", *delm, mu1, sig1);
  
  RooAddPdf delmSigModel(m_delmSigModelName, "",
                          RooArgList(delm_sig_g0,delm_sig_g1),
                          RooArgList(coreFrac));
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigBiGauss(Float_t mu0_start,
                                              Float_t mu0_min,
                                              Float_t mu0_max, 
                                              Float_t mu1_start,
                                              Float_t mu1_min,
                                              Float_t mu1_max,
                                              Float_t sig0_start,
                                              Float_t sig0_min,
                                              Float_t sig0_max,
                                              Float_t sig1oSig0_start,
                                              Float_t sig1oSig0_min,
                                              Float_t sig1oSig0_max,
                                              Float_t coreFrac_start,
                                              const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                           *m_rws, m_delmName, "RooRealVar");
  }
  
  TString mu0Title="";
  TString mu1Title="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString coreFracTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    mu0Title="#mu_{core}";
    mu1Title="#mu_{tail}";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
    sig1Title="#sigma_{tail}";
    coreFracTitle="f_{core}";
  }
  else {
    mu0Title.Form("%s #mu_{core}", m_delmPartName);
    mu1Title.Form("%s #mu_{tail}", m_delmPartName);
    sig0Title.Form("%s #sigma_{core}", m_delmPartName);
    sig1Title.Form("%s #sigma_{tail}", m_delmPartName);
    sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_delmPartName);
    coreFracTitle.Form("%s f_{core}", m_delmPartName);
  }

  RooRealVar mu0("delm_sig_mu0", mu0Title.Data(),
                 mu0_start, mu0_min, mu0_max, unit);
  RooRealVar sig0("delm_sig_sigma0", sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian delm_sig_g0("delm_sig_gauss0", "", *delm, mu0, sig0);

  RooRealVar sig1oSig0("delm_sig_s1oS0", sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
  RooRealVar mu1("delm_sig_mu1", mu1Title.Data(),
                 mu1_start, mu1_min, mu1_max, unit);  
  RooFormulaVar sig1("delm_sig_sigma1", sig1Title.Data(), "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);

  RooGaussian delm_sig_g1("delm_sig_gauss1", "", *delm, mu1, sig1);

  RooRealVar coreFrac("delm_sig_coreFrac", coreFracTitle.Data(),
                      coreFrac_start,0.0,1);
  
  RooAddPdf delmSigModel(m_delmSigModelName, "", 
                         RooArgList(delm_sig_g0,delm_sig_g1),
                         RooArgList(coreFrac));
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigBiGauss",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigCruijff(RooRealVar& mu,
                                              RooRealVar& sigL,
                                              RooRealVar& sigR,
                                              RooRealVar& alphaL,
                                              RooRealVar& alphaR) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_delmName);
  if (!mass) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooCruijff delmSigModel(m_delmSigModelName, "", *mass, mu, sigL,
                           sigR, alphaL, alphaR);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigCruijff(Float_t mu_start, Float_t mu_min,
                                              Float_t mu_max, 
                                              Float_t sigL_start,
                                              Float_t sigL_min,
                                              Float_t sigL_max,
                                              Float_t sigR_start,
                                              Float_t sigR_min,
                                              Float_t sigR_max,
                                              Float_t alphaL_start,
                                              Float_t alphaL_min,
                                              Float_t alphaL_max,
                                              Float_t alphaR_start, 
                                              Float_t alphaR_min,
                                              Float_t alphaR_max,
                                              const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString muTitle="";
  TString sigLTitle="";
  TString alphaLTitle="";
  TString sigRTitle="";
  TString alphaRTitle="";

  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    muTitle="#mu";
    sigLTitle="#sigma_{L}";
    alphaLTitle="#alpha_{L}";
    sigRTitle="#sigma_{R}";
    alphaRTitle="#alpha_{R}";
  }
  else {
    muTitle.Form("%s #mu", m_delmPartName);
    sigLTitle.Form("%s #sigma_{L}", m_delmPartName);
    alphaLTitle.Form("%s #alpha_{L}", m_delmPartName);
    sigRTitle.Form("%s #sigma_{R}", m_delmPartName);
    alphaRTitle.Form("%s #alpha_{R}", m_delmPartName);
  }
  
  RooRealVar mu("delm_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sigL("delm_sig_sigmaL", sigLTitle.Data(), sigL_start, sigL_min, 
                 sigL_max, unit);
  RooRealVar alphaL("delm_sig_alphaL", alphaLTitle.Data(), alphaL_start,
                   alphaL_min, alphaL_max);
  RooRealVar sigR("delm_sig_sigmaR", sigRTitle.Data(), sigR_start, sigR_min, 
                 sigR_max, unit);
  RooRealVar alphaR("delm_sig_alphaR", alphaRTitle.Data(), alphaR_start,
                   alphaR_min, alphaR_max);

  RooCruijff delmSigModel(m_delmSigModelName, "", *delm, mu, sigL, sigR, alphaL, alphaR);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigCruijff(RooRealVar& mu, RooRealVar& sig,
                                              RooRealVar& alphaL,
                                              RooRealVar& alphaR) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooCruijffSimple delmSigModel(m_delmSigModelName, "", *delm, mu, sig,
                                alphaL, alphaR);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigCruijff(Float_t mu_start, 
                                               Float_t mu_min,
                                               Float_t mu_max,
                                               Float_t sig_start,
                                               Float_t sig_min,
                                               Float_t sig_max,
                                               Float_t alphaL_start,
                                               Float_t alphaL_min,
                                               Float_t alphaL_max,
                                               Float_t alphaR_start,
                                               Float_t alphaR_min,
                                               Float_t alphaR_max,
                                               const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString alphaLTitle="";
  TString alphaRTitle="";

  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    alphaLTitle="#alpha_{L}";
    alphaRTitle="#alpha_{R}";
  }
  else {
    muTitle.Form("%s #mu", m_delmPartName);
    sigTitle.Form("%s #sigma", m_delmPartName);
    alphaLTitle.Form("%s #alpha_{L}", m_delmPartName);
    alphaRTitle.Form("%s #alpha_{R}", m_delmPartName);
  }
  
  RooRealVar mu("delm_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("delm_sig_sigma", sigTitle.Data(), sig_start, sig_min, 
                 sig_max, unit);
  RooRealVar alphaL("delm_sig_alphaL", alphaLTitle.Data(), alphaL_start,
                   alphaL_min, alphaL_max);
  RooRealVar alphaR("delm_sig_alphaR", alphaRTitle.Data(), alphaR_start,
                   alphaR_min, alphaR_max);

  RooCruijffSimple delmSigModel(m_delmSigModelName, "", *delm, mu, sig,
                                 alphaL, alphaR);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigCruijff",
                          *m_rws, delmSigModel);
  }
}

void RooDstarD0MassFitter::MakeDelmSigCB(RooRealVar& mu, RooRealVar& sig,
                                          RooRealVar& alpha, RooRealVar& n) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigCB",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigCB",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooCBShape delmSigModel(m_delmSigModelName, "", *delm, mu, sig, alpha, n);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigCB",
                          *m_rws, delmSigModel);
  }
}


void RooDstarD0MassFitter::MakeDelmSigCB(Float_t mu_start, Float_t mu_min,
                                          Float_t mu_max, Float_t sig_start,
                                          Float_t sig_min, Float_t sig_max,
                                          Float_t alpha_start,
                                          Float_t alpha_min,
                                          Float_t alpha_max, Float_t n_start,
                                          Float_t n_min, Float_t n_max,
                                          const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmSigCB",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmSigCB",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString alphaTitle="";
  TString nTitle="";

  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    alphaTitle="#alpha";
    nTitle="n";
  }
  else {
    muTitle.Form("%s #mu", m_delmPartName);
    sigTitle.Form("%s #sigma", m_delmPartName);
    alphaTitle.Form("%s #alpha", m_delmPartName);
    nTitle.Form("%s n", m_delmPartName);
  }
  
  RooRealVar mu("delm_sig_mu", muTitle.Data(), mu_start, mu_min,
                mu_max, unit);
  RooRealVar sig("delm_sig_sigma", sigTitle.Data(), sig_start, sig_min, 
                 sig_max, unit);
  RooRealVar alpha("delm_sig_alpha", alphaTitle.Data(), alpha_start,
                   alpha_min, alpha_max);
  RooRealVar n("delm_sig_n", nTitle.Data(), n_start, n_min, n_max);

  RooCBShape delmSigModel(m_delmSigModelName, "", *delm, mu, sig, alpha, n);
  if (m_rws->import(delmSigModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmSigCB",
                          *m_rws, delmSigModel);
  }
}

/***** create Delta mass background model *****/
// RooDstD0BG background
void RooDstarD0MassFitter::MakeDelmBkgDstD0BG(RooRealVar& dm0, // threshold
                                              RooRealVar& c, RooRealVar& a,
                                              RooRealVar& b) 
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooDstD0BG delmBkgModel(m_delmBkgModelName, "", *delm, dm0, c, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                          *m_rws, delmBkgModel);
  }
}

void RooDstarD0MassFitter::MakeDelmBkgDstD0BG(Float_t dm0_start,
                                              Float_t dm0_min, 
                                              Float_t dm0_max, Float_t c_start,
                                              Float_t c_min, Float_t c_max,
                                              Float_t a_start, Float_t a_min,
                                              Float_t a_max, Float_t b_start,
                                              Float_t b_min, Float_t b_max,
                                              const char* unit)
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString dm0Title="";
  TString cTitle="";
  TString aTitle="";
  TString bTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    dm0Title="(#Delta m)_{0}";
    cTitle="c";
    aTitle="a";
    bTitle="b";
  }
  else {
    dm0Title.Form("%s (#Delta m)_{0}", m_delmPartName);
    cTitle.Form("%s c", m_delmPartName);
    aTitle.Form("%s a", m_delmPartName);
    bTitle.Form("%s b", m_delmPartName);
  }
  RooRealVar dm0("delm_bkg_dm0", dm0Title.Data(), dm0_start, dm0_min, dm0_max,
                 unit);
  RooRealVar c("delm_bkg_c", cTitle.Data(), c_start, c_min, c_max);
  RooRealVar a("delm_bkg_a", aTitle.Data(), a_start, a_min, a_max);
  RooRealVar b("delm_bkg_b", bTitle.Data(), b_start, b_min, b_max);
  
  RooDstD0BG delmBkgModel(m_delmBkgModelName, "", *delm, dm0, c, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                          *m_rws, delmBkgModel);
  }
}

void RooDstarD0MassFitter::MakeDelmBkgDstD0BG(Float_t dm0_start,
                                              Float_t dm0_min, 
                                              Float_t dm0_max, Float_t c_start,
                                              Float_t a_start, Float_t a_min,Float_t a_max,
                                              Float_t b_start,
                                              const char* unit)
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString dm0Title="";
  TString cTitle="";
  TString aTitle="";
  TString bTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    dm0Title="(#Delta m)_{0}";
    cTitle="c";
    aTitle="a";
    bTitle="b";
  }
  else {
    dm0Title.Form("%s (#Delta m)_{0}", m_delmPartName);
    cTitle.Form("%s c", m_delmPartName);
    aTitle.Form("%s a", m_delmPartName);
    bTitle.Form("%s b", m_delmPartName);
  }
  RooRealVar dm0("delm_bkg_dm0", dm0Title.Data(), dm0_start, dm0_min, dm0_max,
                 unit);
  RooRealVar c("delm_bkg_c", cTitle.Data(), c_start);
  RooRealVar a("delm_bkg_a", aTitle.Data(), a_start, a_min, a_max);
  RooRealVar b("delm_bkg_b", bTitle.Data(), b_start);
  
  RooDstD0BG delmBkgModel(m_delmBkgModelName, "", *delm, dm0, c, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                          *m_rws, delmBkgModel);
  }
}





void RooDstarD0MassFitter::MakeDelmBkgDstD0BG(Float_t dm0, Float_t c_start,
                                              Float_t c_min, Float_t c_max,
                                              Float_t a_start, Float_t a_min,
                                              Float_t a_max, Float_t b_start,
                                              Float_t b_min, Float_t b_max,
                                              const char* unit)
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString dm0Title="";
  TString cTitle="";
  TString aTitle="";
  TString bTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    dm0Title="(#Delta m)_{0}";
    cTitle="c";
    aTitle="a";
    bTitle="b";
  }
  else {
    dm0Title.Form("%s (#Delta m)_{0}", m_delmPartName);
    cTitle.Form("%s c", m_delmPartName);
    aTitle.Form("%s a", m_delmPartName);
    bTitle.Form("%s b", m_delmPartName);
  }
  RooRealVar dm0Var("delm_bkg_dm0", dm0Title.Data(), dm0, unit);
  RooRealVar c("delm_bkg_c", cTitle.Data(), c_start, c_min, c_max);
  RooRealVar a("delm_bkg_a", aTitle.Data(), a_start, a_min, a_max);
  RooRealVar b("delm_bkg_b", bTitle.Data(), b_start, b_min, b_max);
  
  RooDstD0BG delmBkgModel(m_delmBkgModelName, "", *delm, dm0Var, c, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgDstD0BG",
                          *m_rws, delmBkgModel);
  }
}


// RooGranet background
void RooDstarD0MassFitter::MakeDelmBkgGranet(RooRealVar& dm0, // threshold 
                                             RooRealVar& a, // exponent
                                             RooRealVar& b // power
                                             ) 
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgGranet",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgGranet",
                           *m_rws, m_delmName, "RooRealVar");
  }
  RooGranet delmBkgModel(m_delmBkgModelName, "", *delm, dm0, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgGranet",
                          *m_rws, delmBkgModel);
  }
}

void RooDstarD0MassFitter::MakeDelmBkgGranet(Float_t dm0_start, 
                                             Float_t dm0_min, Float_t dm0_max,
                                             Float_t a_start, Float_t a_min,
                                             Float_t a_max, Float_t b_start,
                                             Float_t b_min, Float_t b_max,
                                             const char* unit) 
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgGranet",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgGranet",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString dm0Title="";
  TString aTitle="";
  TString bTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    dm0Title="(#Delta m)_{0}";
    aTitle="a";
    bTitle="b";
  }
  else {
    dm0Title.Form("%s (#Delta m)_{0}", m_delmPartName);
    aTitle.Form("%s a", m_delmPartName);
    bTitle.Form("%s b", m_delmPartName);
  }
  RooRealVar dm0("delm_bkg_dm0", dm0Title.Data(), dm0_start, dm0_min,
                 dm0_max, unit);
  RooRealVar a("delm_bkg_a", aTitle.Data(), a_start, a_min, a_max);
  RooRealVar b("delm_bkg_b", bTitle.Data(), b_start, b_min, b_max);

  RooGranet delmBkgModel(m_delmBkgModelName, "", *delm, dm0, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgGranet",
                          *m_rws, delmBkgModel);
  }
}

void RooDstarD0MassFitter::MakeDelmBkgGranet(Float_t dm0, Float_t a_start,
                                             Float_t a_min, Float_t a_max,
                                             Float_t b_start, Float_t b_min,
                                             Float_t b_max, const char* unit) 
{
   if (!m_rws) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmBkgGranet",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmBkgGranet",
                           *m_rws, m_delmName, "RooRealVar");
  }
  TString dm0Title="";
  TString aTitle="";
  TString bTitle="";
  if (!m_delmPartName||strcmp(m_delmPartName,"")==0) {
    dm0Title="(#Delta m)_{0}";
    aTitle="a";
    bTitle="b";
  }
  else {
    dm0Title.Form("%s (#Delta m)_{0}", m_delmPartName);
    aTitle.Form("%s a", m_delmPartName);
    bTitle.Form("%s b", m_delmPartName);
  }
  RooRealVar dm0Var("delm_bkg_dm0", dm0Title.Data(), dm0, unit);
  RooRealVar a("delm_bkg_a", aTitle.Data(), a_start, a_min, a_max);
  RooRealVar b("delm_bkg_b", bTitle.Data(), b_start, b_min, b_max);

  RooGranet delmBkgModel(m_delmBkgModelName, "", *delm, dm0Var, a, b);
  if (m_rws->import(delmBkgModel)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmBkgGranet",
                          *m_rws, delmBkgModel);
  }
}


// make 2D D0/delta mass model - specify expected fraction of each 
// background type. NB. No check that sum(frac)==1
// If a starting value for a model fraction is less than zero, then this
// model type will be ignored. This is useful to produce partial models
// e.g. a background-only model
// The method will raise an exception if all fractions are less than zero
void RooDstarD0MassFitter::MakeDelmModel(Float_t frac_sig,
                                         Float_t frac_combBkg,
                                         Float_t frac_piBkg,
                                         Float_t frac_d0Bkg) 
{
  if (frac_sig<0&&frac_combBkg<0&&frac_piBkg&&frac_d0Bkg<0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel", 
                           "Fit fractions are less than zero. At least one fraction must be >0");
  }
  
  if (frac_sig>1) {
    std::stringstream msg;
    msg << "Signal fit fraction is greater than unity (" << frac_sig << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel", msg.str());
  }
  if (frac_combBkg>1) {
    std::stringstream msg;
    msg << "Combinatoric background fit fraction is greater than unity ("
        << frac_combBkg << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel", msg.str());
  }
  if (frac_piBkg>1) {
    std::stringstream msg;
    msg << "Random slow pion background fit fraction is greater than unity ("
        << frac_piBkg << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel", msg.str());
  }
  if (frac_d0Bkg>1) {
    std::stringstream msg;
    msg << "Fake D0 background fit fraction is greater than unity ("
        << frac_d0Bkg << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel", msg.str());
  }

  if (!m_rws)
  {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel",
                           "No RooWorkspace object is defined!");
  }
  RooDataSet* rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws, m_delmName, "RooRealVar");
  }
  RooAbsPdf* d0MassSigModel=m_rws->pdf(m_dMassSigModelName);
  if (!d0MassSigModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws,m_dMassSigModelName,"RooAbsPdf");
  }
  RooAbsPdf* d0MassBkgModel=m_rws->pdf(m_dMassBkgModelName);
  if (!d0MassBkgModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws,m_dMassBkgModelName,"RooAbsPdf");
  }
  RooAbsPdf* delmSigModel=m_rws->pdf(m_delmSigModelName);
  if (!delmSigModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws,m_delmSigModelName,"RooAbsPdf");
  }
  RooAbsPdf* delmBkgModel=m_rws->pdf(m_delmBkgModelName);
  if (!delmBkgModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmModel",
                             *m_rws,m_delmBkgModelName,"RooAbsPdf");
  }
  
  /*** create the 2D PDF ***/

  // signal
  RooProdPdf sigModel(m_2dMassSigModelName,"",
                      RooArgSet(*d0MassSigModel, *delmSigModel));
  
  // combinatoric background (bkg in D0 mass, bkg in delta mass)
  RooProdPdf combModel(m_2dMassCombBkgModelName,"",
                       RooArgSet(*d0MassBkgModel, *delmBkgModel));
  
  // random slow pion bkg (signal in D0 mass, bkg in delta mass)
  RooProdPdf piModel(m_2dMassPiBkgModelName, "",
                     RooArgSet(*d0MassSigModel, *delmBkgModel));
  
  // fake D0 bkg (bkg in D0 mass, signal in delta mass)
  RooProdPdf d0Model(m_2dMassD0BkgModelName, "",
                     RooArgSet(*d0MassBkgModel, *delmSigModel));
  
  Int_t nentries = rds->numEntries();
  if (nentries<=0) {
    std::stringstream msg;
    msg << "Got invalid number of entries " << nentries
        << " from RooDataSet " << m_dataSetName;
    throw GeneralException("RooDstarD0MassFitter::MakeDelmModel",msg.str());
  }
  Int_t nsig_est = static_cast<Int_t>(frac_sig*nentries);
  Int_t ncombBkg_est = static_cast<Int_t>(frac_combBkg*nentries);
  Int_t npiBkg_est = static_cast<Int_t>(frac_piBkg*nentries);
  Int_t nd0Bkg_est = static_cast<Int_t>(frac_d0Bkg*nentries);

  RooRealVar nsig(m_2dMassSigYieldName, "N_{sig.}", nsig_est, 0, nentries);
  RooRealVar ncomb(m_2dMassCombBkgYieldName, "N_{bkg. (comb.)}",
                   ncombBkg_est, 0, nentries);
  RooRealVar npi(m_2dMassPiBkgYieldName, "N_{bkg. (random #pi_{s})}",
                 npiBkg_est, 0, nentries);
  RooRealVar nD0(m_2dMassD0BkgYieldName, "N_{bkg. (fake D^{0})}",
                 nd0Bkg_est, 0, nentries);
  
  RooArgList yieldList;//(nsig, ncomb);
  RooArgList pdfList;//(sigModel, combModel);

  if (frac_sig>=0) {
    pdfList.add(sigModel);
    yieldList.add(nsig);
  }
  if (frac_combBkg>=0) {
    pdfList.add(combModel);
    yieldList.add(ncomb);
  }
  if (frac_piBkg>=0) {
    pdfList.add(piModel);
    yieldList.add(npi);
  }
  if (frac_d0Bkg>=0) {
    pdfList.add(d0Model);
    yieldList.add(nD0);
  }
  assert(pdfList.getSize()!=0);
  assert(yieldList.getSize()!=0);

  RooAddPdf model(m_modelName, "#Delta_{m} - D^{0} 2D combined model PDF",
                  pdfList, yieldList);
  
  if (m_rws->import(model)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmModel",
                          *m_rws, model);
  }
}


// make 2D D0/delta mass model  with all background types combined
// - specify expected fraction of each 
// background type. NB. No check that sum(frac)==1
// If a starting value for a model fraction is less than zero, then this
// model type will be ignored. This is useful to produce partial models
// e.g. a background-only model
// The method will raise an exception if all fractions are less than zero
void RooDstarD0MassFitter::MakeDelmCombinedBkgModel(Float_t frac_sig,
                                                    Float_t frac_combBkg,
                                                    Float_t frac_piBkg,
                                                    Float_t frac_d0Bkg) 
{
  if (frac_sig<0&&frac_combBkg<0&&frac_piBkg&&frac_d0Bkg<0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", 
                           "Fit fractions are less than zero. At least one fraction must be >0");
  }
  if (frac_combBkg<0&&frac_piBkg&&frac_d0Bkg<0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", 
                           "Background fit fractions are less than zero. At least one background fraction must be >0");
  }
  if (frac_sig>1) {
    std::stringstream msg;
    msg << "Signal fit fraction is greater than unity (" << frac_sig << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", msg.str());
  }
  if (frac_combBkg>1) {
    std::stringstream msg;
    msg << "Combinatoric background fit fraction is greater than unity ("
        << frac_combBkg << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", msg.str());
  }
  if (frac_piBkg>1) {
    std::stringstream msg;
    msg << "Random slow pion background fit fraction is greater than unity ("
        << frac_piBkg << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", msg.str());
  }
  if (frac_d0Bkg>1) {
    std::stringstream msg;
    msg << "Fake D0 background fit fraction is greater than unity ("
        << frac_d0Bkg << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", msg.str());
  }
  Float_t frac_bkgTotal=0;
  if (frac_combBkg>0) frac_bkgTotal+=frac_combBkg;
  if (frac_piBkg>0) frac_bkgTotal+=frac_piBkg;
  if (frac_d0Bkg>0) frac_bkgTotal+=frac_d0Bkg;

  if (frac_bkgTotal>1) {
    std::stringstream msg;
    msg << "Combined background fraction is greater than unity ("
        << frac_bkgTotal << ")";
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel", msg.str());
  }
  
  if (!m_rws)
  {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                           "No RooWorkspace object is defined!");
  }
  
  RooDataSet* rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws, m_delmName, "RooRealVar");
  }
  RooAbsPdf* d0MassSigModel=m_rws->pdf(m_dMassSigModelName);
  if (!d0MassSigModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws,m_dMassSigModelName,"RooAbsPdf");
  }
  RooAbsPdf* d0MassBkgModel=m_rws->pdf(m_dMassBkgModelName);
  if (!d0MassBkgModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws,m_dMassBkgModelName,"RooAbsPdf");
  }
  RooAbsPdf* delmSigModel=m_rws->pdf(m_delmSigModelName);
  if (!delmSigModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws,m_delmSigModelName,"RooAbsPdf");
  }
  RooAbsPdf* delmBkgModel=m_rws->pdf(m_delmBkgModelName);
  if (!delmBkgModel) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                             *m_rws,m_delmBkgModelName,"RooAbsPdf");
  }
  
  /*** create the 2D PDF ***/

  // signal
  RooProdPdf sigModel(m_2dMassSigModelName,"",
                      RooArgSet(*d0MassSigModel, *delmSigModel));
  
  // combinatoric background (bkg in D0 mass, bkg in delta mass)
  RooProdPdf combModel(m_2dMassCombBkgModelName,"",
                       RooArgSet(*d0MassBkgModel, *delmBkgModel));
  
  // random slow pion bkg (signal in D0 mass, bkg in delta mass)
  RooProdPdf piModel(m_2dMassPiBkgModelName, "",
                     RooArgSet(*d0MassSigModel, *delmBkgModel));
  
  // fake D0 bkg (bkg in D0 mass, signal in delta mass)
  RooProdPdf d0Model(m_2dMassD0BkgModelName, "",
                     RooArgSet(*d0MassBkgModel, *delmSigModel));
  
  Int_t nentries = rds->numEntries();
  if (nentries<=0) {
    std::stringstream msg;
    msg << "Got invalid number of entries " << nentries
        << " from RooDataSet " << m_dataSetName;
    throw GeneralException("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",msg.str());
  }
  Int_t nsig_est = static_cast<Int_t>(frac_sig*nentries);
  Int_t ncombBkg_est = static_cast<Int_t>(frac_combBkg*nentries);
  Int_t npiBkg_est = static_cast<Int_t>(frac_piBkg*nentries);
  Int_t nd0Bkg_est = static_cast<Int_t>(frac_d0Bkg*nentries);
  Int_t nbkgTotal_est = static_cast<Int_t>(frac_bkgTotal*nentries);

  RooRealVar nsig("nsig", "N_{sig.}", nsig_est, 0, nentries);
  RooRealVar ncomb("nbkg_comb", "N_{bkg. (comb.)}", ncombBkg_est, 0, nentries);
  RooRealVar npi("nbkg_randomPion", "N_{bkg. (random #pi_{s})}",
                 npiBkg_est, 0, nentries);
  RooRealVar nD0("nbkg_fakeD0", "N_{bkg. (fake D^{0})}",
                 nd0Bkg_est, 0, nentries);
  RooRealVar nbkgTotal("nbkg_total", "N_{bkg. (total)}", nbkgTotal_est, 0, nentries);

  RooArgList bkgYieldList;
  RooArgList bkgPdfList;
  
  RooArgList yieldList;//(nsig, ncomb);
  RooArgList pdfList;//(sigModel, combModel);

  if (frac_sig>=0) {
    pdfList.add(sigModel);
    yieldList.add(nsig);
  }
  if (frac_bkgTotal>=0) {
    if (frac_combBkg>=0) {
      bkgPdfList.add(combModel);
      bkgYieldList.add(ncomb);
    }
    if (frac_piBkg>=0) {
      bkgPdfList.add(piModel);
      bkgYieldList.add(npi);
    }
    if (frac_d0Bkg>=0) {
      bkgPdfList.add(d0Model);
      bkgYieldList.add(nD0);
    }
  }
  assert(bkgPdfList.getSize()!=0);
  assert(bkgYieldList.getSize()!=0);

  RooAddPdf bkgCombinedModel(m_2dMassCombinedBkgModelName, "", bkgPdfList, bkgYieldList);
  
  pdfList.add(bkgCombinedModel);
  yieldList.add(nbkgTotal);
  
  assert(pdfList.getSize()!=0);
  assert(yieldList.getSize()!=0);

  RooAddPdf model(m_modelName, "#Delta_{m} - D^{0} 2D combined model PDF",
                  pdfList, yieldList);
  
  if (m_rws->import(model)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmCombinedBkgModel",
                          *m_rws, model);
  }
}



void RooDstarD0MassFitter::MakeDelmDataSet(TTree* tt,
                                           const char* d0MassVarname, 
                                           const char* dstarMassVarname,
                                           const char* name, const char* title,
                                           const char* cuts,
                                           Bool_t useDelmVarFromTree) 
{
  if (!m_rws)
  {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No RooWorkspace object is defined.");
  }
  if (!tt) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
           "Expected pointer to TTree as argument, got NULL pointer.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmDataSet",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm) {
    throw WSRetrievalFailure("RooDstarD0MassFitter::MakeDelmDataSet",
                             *m_rws, m_delmName, "RooRealVar");
  }
  if (!d0MassVarname||strcmp(d0MassVarname,"")==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No D0 mass branch name specified.");
  }
  if (!dstarMassVarname||strcmp(dstarMassVarname,"")==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No D* mass branch name specified.");
  }
  if (!name||strcmp(name,"")==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No RooDataSet name specified.");
  }
  Long64_t nTotal = tt->GetEntries();
  if (nTotal==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No entries in input TTree.");
  }
  //TEntryList* elist=0;
  TEntryList* elist=0;
  tt->SetBranchStatus("*",1);
  if (cuts&&strcmp(cuts,"")!=0) {
    tt->Draw(">>elist",cuts,"entryList");
    elist = (TEntryList*)gDirectory->Get("elist");
    if (!elist) {
      std::stringstream msg;
      msg << "Failed to retrieve TEntryList for cuts " << cuts;
      throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                             msg.str());
    }
    tt->SetEntryList(elist);
  }
  Long64_t nentries = !elist?tt->GetEntries():elist->GetN();
  if (nentries==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No entries in TTree after cuts.");
  }

  Float_t D0M_f, DstarM_f;
  Double_t D0M, DstarM;
  // if this is a TChain, then we need to use the daughter's method
  tt->SetBranchStatus("*", 1);

  TChain* ch=0;
  ch=dynamic_cast<TChain*>(tt);
  std::string masstype=ch?GetBranchType(ch, d0MassVarname):GetBranchType(tt, d0MassVarname);
  if (!ch) {
    if (masstype.compare("Float_t")==0) { 
      tt->SetBranchAddress(d0MassVarname, &D0M_f);
      tt->SetBranchAddress(dstarMassVarname, &DstarM_f);
    }
    else if (masstype.compare("Double_t")==0) {
      tt->SetBranchAddress(d0MassVarname, &D0M);
      tt->SetBranchAddress(dstarMassVarname, &DstarM);
    }
    else {
      std::stringstream msg;
      msg << "Got unexpected type " << masstype << " for variable " 
          << d0MassVarname;
      throw GeneralException("RooDstarD0MassFitter::MakeDMassDataSet", msg.str());
    }
  }
  else {
    if (masstype.compare("Float_t")==0) { 
      ch->SetBranchAddress(d0MassVarname, &D0M_f);
      ch->SetBranchAddress(dstarMassVarname, &DstarM_f);
    }
    else if (masstype.compare("Double_t")==0) {
      ch->SetBranchAddress(d0MassVarname, &D0M);
      ch->SetBranchAddress(dstarMassVarname, &DstarM);
    }
    else {
      std::stringstream msg;
      msg << "Got unexpected type " << masstype << " for variable " 
          << d0MassVarname;
      throw GeneralException("RooDstarD0MassFitter::MakeDMassDataSet", msg.str());
    }
  }

  RooArgSet observables(*mass, *delm);
  RooArgSet args(*mass, *delm);
  
  std::map<std::string, void*> varMap;
  std::map<std::string, Int_t*> catMap;
  
  const RooArgSet* extraArgs = m_rws->set(m_spectSetName);
  const RooArgSet* categories = m_rws->set(m_catSetName);

  if (extraArgs) {
    TIterator *it = extraArgs->createIterator();
    std::string varName;
    RooRealVar* v;
    while ( (v=(RooRealVar*)it->Next()) )
    {
      varName=v->GetName();
      if (!args.add(*v)) {
        std::stringstream msg;
        msg << "Request to add RooRealVar " << varName 
            << " to dataset, which has already been included";
        throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
      }
      std::string branchName=varName;
      if (m_varNameToBranchName.find(varName)!=m_varNameToBranchName.end()) {
        branchName=m_varNameToBranchName[varName];
      }
      std::string type=GetBranchType(tt, branchName);
      if (type.compare("Float_t")==0) {
        varMap[varName] = new Float_t();
      }
      else if (type.compare("Double_t")==0) {
        varMap[varName] = new Double_t();
      }
      else if (type.compare("Int_t")==0) {
        varMap[varName] = new Int_t();
      }
      else if (type.compare("UInt_t")==0) {
        varMap[varName] = new UInt_t();
      }
      else if (type.compare("Bool_t")==0) {
        varMap[varName] = new Bool_t();
      }
      else {
        std::stringstream msg;
        msg << "Got unexpected type " << type << " for variable " << varName;
        throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
      }
      if (!ch) {
        tt->SetBranchAddress(branchName.c_str(), varMap[varName]);
      }
      else {
        ch->SetBranchAddress(branchName.c_str(), varMap[varName]);
      }
    }
  } // extra args

  if (categories) {
    TIterator *it = categories->createIterator();
    std::string catName;
    RooCategory* cat;
    while ( (cat=(RooCategory*)it->Next()) )
    {
      catName=cat->GetName();
      if (!args.add(*cat)) {
        std::stringstream msg;
        msg << "Request to add RooCategory " << catName 
            << " to dataset, which has already been included";
        throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
      }
      std::string branchName=catName;
      if (m_catNameToBranchName.find(catName)!=m_catNameToBranchName.end()) {
        branchName=m_catNameToBranchName[catName];
      }
      std::string type=GetBranchType(tt, branchName);
      if ( !(type.compare("Int_t")==0 || type.compare("Bool_t")==0) ) {
        std::stringstream msg;
        msg << "Requested branch name " << branchName << " is of type "
            << type << ", but categories can only be of type Int_t or Bool_t";
        throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
      }
      catMap[catName] = new Int_t();
      if (!ch) {
        tt->SetBranchAddress(branchName.c_str(), catMap[catName]);
      }
      else {
        ch->SetBranchAddress(branchName.c_str(), catMap[catName]);
      }      
    }
  } // categories
  
  RooDataSet *rds = new RooDataSet(name, title?title:"", args);
  Long64_t entry=0;
  Long64_t localEntry=0;
  Long64_t entryNumber=0;
  

  for (entry=0; entry<nentries; ++entry)
  {
    entryNumber=tt->GetEntryNumber(entry);
    if (entryNumber<0) {
       std::stringstream msg;
       msg << "Got invalid entry number " << entryNumber;
       throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
     }
    if (ch) {
      localEntry = tt->LoadTree(entryNumber);
      if (localEntry<0) {
        std::stringstream msg;
        msg << "Got invalid entry number in current tree " << localEntry;
        throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
      }
    }
    
    Int_t nb=0;
    nb=tt->GetEntry(entryNumber);
    if (nb<=0) {
      std::stringstream msg;
      msg << "Got invalid number of bytes " << nb 
          << " for entry " << entry << ", entry number " << entryNumber;
      throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
    }
    
    if (masstype.compare("Float_t")==0) {
      D0M=static_cast<Double_t>(D0M_f);
      DstarM=static_cast<Double_t>(DstarM_f);
    }

    Double_t Delm = (!useDelmVarFromTree) ? DstarM-D0M : DstarM;
    
    if ( (mass->inRange(D0M,0)) && (delm->inRange(Delm,0)) ) {
      mass->setVal(D0M);
      delm->setVal(Delm);
      
      Bool_t passed=kTRUE;
      if (varMap.size()!=0) {
        for (std::map<std::string, void*>::iterator it=varMap.begin();
             it!=varMap.end(); ++it)
        {
          std::string vname=(it->first);
          void *val=(it->second);
          assert (val!=NULL);
          std::string branchName=vname;
          if (m_varNameToBranchName.find(vname)!=m_varNameToBranchName.end()) {
            branchName=m_varNameToBranchName[vname];
          }
          Double_t v;
          std::string type=GetBranchType(tt, branchName);
          if (type.compare("Float_t")==0) {
            Float_t* ptr=static_cast<Float_t*>(val);
            assert(ptr);
            v=(Double_t)(*ptr);
          }
          else if (type.compare("Double_t")==0) {
            Double_t* ptr = static_cast<Double_t*>(val);
            assert(ptr);
            v=(Double_t)(*ptr);
          }
          else if (type.compare("Int_t")==0) {
            Int_t* ptr = static_cast<Int_t*>(val);
            assert(ptr);
            v=(Double_t)(*ptr);
          }
          else if (type.compare("UInt_t")==0) {
            UInt_t* ptr = static_cast<UInt_t*>(val);
            assert(ptr);
            v=(Double_t)(*ptr);
          }
          else if (type.compare("Bool_t")==0) {
            Bool_t* ptr = static_cast<Bool_t*>(val);
            assert(ptr);
            v=(Double_t)(*ptr);
          }
          else {
            std::stringstream msg;
            msg << "Got unexpected type " << type << " for variable " 
                << vname;
            throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                                   msg.str());
          }
          if (!args.find(vname.c_str())) {
            std::stringstream msg;
            msg << "Unable to find variable name " << vname << " in RooArgSet";
            throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                                   msg.str());
          }
          RooRealVar *var=dynamic_cast<RooRealVar*>(&args[vname.c_str()]);
          if (!var) {
            std::stringstream msg;
            msg << "Unable to cast RooAbsArg " << vname << " to a RooRealVar";
            throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                                   msg.str());
          }
          if (m_varNameToFunction.find(vname)!=m_varNameToFunction.end()) { 
            DoubleFun fun = m_varNameToFunction[vname];
            assert(fun);
            v = fun(v);
            if (!var->inRange(v,0)) {
              passed=kFALSE;
              break;
            }
            var->setVal(v);
          }
          else if (m_varNameToFormula.find(vname)!=m_varNameToFormula.end()) {
            TFormula& fun = m_varNameToFormula[vname];
            v = fun.Eval(v);
            if (!var->inRange(v,0)) {
              passed=kFALSE;
              break;
            }
            var->setVal(v);
          }
          else {
            if (!var->inRange(v,0))
            {
              passed=kFALSE;
              break;
            }
            var->setVal(v);
          }
        }
      }
      if (catMap.size()>0) {
        for (std::map<std::string, Int_t*>::iterator it=catMap.begin();
             it!=catMap.end(); ++it)
        {
          std::string vname=(it->first);
          Int_t *val=(it->second);
          assert(val!=NULL);
          std::string branchName=vname;
          if (m_catNameToBranchName.find(vname)!=m_catNameToBranchName.end()) {
            branchName=m_catNameToBranchName[vname];
          }
          std::string type=GetBranchType(tt, branchName);
          if ( !(type.compare("Int_t")==0 || type.compare("Bool_t")==0) ) {
            std::stringstream msg;
            msg << "Requested branch name " << branchName << " is of type "
                << type << ", but categories can only be of type Int_t or Bool_t";
            throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                                   msg.str());
          }
          RooCategory *cat=dynamic_cast<RooCategory*>(&args[vname.c_str()]);
          if (!cat) {
            std::stringstream msg;
            msg << "Unable to cast RooAbsArg " << vname << " to a RooCategory";
            throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                                   msg.str());
          }
          if (!cat->isValidIndex(*val)) {
            passed=kFALSE;
            break;
          }
          cat->setIndex(*val);
        }
      }
      if (!passed) continue;
      rds->add(args);
    }
  } // loop over entries

  if (rds->numEntries()==0) {
    throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet",
                           "No entries selected!");
  }
  std::cout << "RooDstarD0MassFitter::MakeDelmDataSet: Initial entries = "
            << nTotal << std::endl;
  if (cuts&&strlen(cuts)>0) {
    std::cout << "RooDstarD0MassFitter::MakeDelmDataSet: Entries passing selection cut (" 
              << cuts << ") = " << nentries << std::endl;
  }
  std::cout << "RooDstarD0MassFitter::MakeDelmDataSet: Selected entries = " 
            << rds->numEntries() << std::endl;

  if (m_rws->import(*rds)) {
    throw WSImportFailure("RooDstarD0MassFitter::MakeDelmDataSet", *m_rws, *rds);
  }

  
  for (std::map<std::string, void*>::iterator i=varMap.begin();
       i!=varMap.end(); ++i) {
    std::string vname = i->first;
    void* val = i->second;
    if (val==NULL) continue;
    std::string branchName=vname;
    if (m_varNameToBranchName.find(vname)!=m_varNameToBranchName.end()) {
      branchName=m_varNameToBranchName[vname];
    }
    std::string type=GetBranchType(tt, branchName);
    if (type.compare("Float_t")==0) {
      delete static_cast<Float_t*>(val);
    }
    else if (type.compare("Double_t")==0) {
      delete static_cast<Double_t*>(val);
    }
    else if (type.compare("Int_t")==0) {
      delete static_cast<Int_t*>(val);
    }
    else if (type.compare("UInt_t")==0) {
      delete static_cast<UInt_t*>(val);
    }
    else if (type.compare("Bool_t")==0) {
      delete static_cast<Bool_t*>(val);
    }
    else {
      std::stringstream msg;
      msg << "Got invalid data type " << type; 
      throw GeneralException("RooDstarD0MassFitter::MakeDelmDataSet", msg.str());
    }
  }
  varMap.clear();
  for (std::map<std::string, Int_t*>::iterator i=catMap.begin();
       i!=catMap.end(); ++i) {
    std::string vname = i->first;
    Int_t* val = i->second;
    if (val==NULL) continue;
    delete val;
  }
  catMap.clear();
  m_dataSetName = name;
}

// Perform a binned fit to the model PDF
// A binned clone of the data is made, which is then used to fit the PDF
// The default binning for each variable in the original dataset is used,
// except for the D0 mass and delta mass variables, which uses the 
// specified number of bins
// The number of bins for a given variable can be changed using the
// SetBins method
// By default, a maximum likelihood fit is performed. If useChi2Method is
// set to true, then a chi^2 fit is performed instead
void RooDstarD0MassFitter::PerformDelmBinnedFit(Int_t nD0MassBins, 
                                                Int_t nDelmBins,
                                                const char* fitName, 
                                                Int_t nCores,
                                                Bool_t saveSnapshot, 
                                                Bool_t printResults,
                                                Bool_t useSumW2Errors, 
                                                Bool_t extendedMode,
                                                Bool_t useChi2Method)
{
  if (!m_rws)
  {
    throw GeneralException("RooDstarD0MassFitter::PerformDelmBinnedFit",
                           "No RooWorkspace object is defined");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass)
  {
    throw WSRetrievalFailure("RooDstarDMassFitter::PerformDelmBinnedFit"
                             ,*m_rws, m_dMassName, "RooRealVar");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm)
  {
    throw WSRetrievalFailure("RooDstarDMassFitter::PerformDelmBinnedFit"
                             ,*m_rws, m_delmName, "RooRealVar");
  }
  Int_t oldD0MassBins = mass->getBins();
  mass->setBins(nD0MassBins);
  Int_t oldDelmBins = delm->getBins();
  delm->setBins(nDelmBins);
  this->PerformBinnedFit(fitName,nCores,saveSnapshot,printResults,
                         useSumW2Errors,extendedMode, useChi2Method);
  mass->setBins(oldD0MassBins);
  delm->setBins(oldDelmBins);
}

void RooDstarD0MassFitter::PerformDelmIterativeBinnedFit(Int_t nD0MassBins, 
                                                         Int_t nDelmBins,
                                                         std::vector<Int_t>& minuitStrategies,
                                                         const char* fitName, 
                                                         Int_t nCores,
                                                         Bool_t saveSnapshot, 
                                                         Bool_t printResults,
                                                         Bool_t useSumW2Errors, 
                                                         Bool_t extendedMode,
                                                         Bool_t useChi2Method)
{
  if (!m_rws)
  {
    throw GeneralException("RooDstarD0MassFitter::PerformDelmBinnedFit",
                           "No RooWorkspace object is defined");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass)
  {
    throw WSRetrievalFailure("RooDstarDMassFitter::PerformDelmBinnedFit"
                             ,*m_rws, m_dMassName, "RooRealVar");
  }
  RooRealVar* delm = m_rws->var(m_delmName);
  if (!delm)
  {
    throw WSRetrievalFailure("RooDstarDMassFitter::PerformDelmBinnedFit"
                             ,*m_rws, m_delmName, "RooRealVar");
  }
  Int_t oldD0MassBins = mass->getBins();
  mass->setBins(nD0MassBins);
  Int_t oldDelmBins = delm->getBins();
  delm->setBins(nDelmBins);
  this->PerformIterativeBinnedFit(minuitStrategies, fitName,nCores,saveSnapshot,printResults,
                                  useSumW2Errors,extendedMode, useChi2Method);
  mass->setBins(oldD0MassBins);
  delm->setBins(oldDelmBins);
}
  

void RooDstarD0MassFitter::SetDelmPartName(const char* name) {m_delmPartName=name;}
void RooDstarD0MassFitter::SetDelmName(const char* name) {m_delmName=name;}

void RooDstarD0MassFitter::SetDelmSigModelName(const char* name) {m_delmSigModelName=name;}
void RooDstarD0MassFitter::SetDelmBkgModelName(const char* name) {m_delmBkgModelName=name;}

void RooDstarD0MassFitter::Set2DMassSigModelName(const char* name) {m_2dMassSigModelName=name;}
void RooDstarD0MassFitter::Set2DMassCombBkgModelName(const char* name) {m_2dMassCombBkgModelName=name;}
void RooDstarD0MassFitter::Set2DMassRandPiBkgModelName(const char* name) {m_2dMassPiBkgModelName=name;}
void RooDstarD0MassFitter::Set2DMassFakeD0BkgModelName(const char* name) {m_2dMassD0BkgModelName=name;}

void RooDstarD0MassFitter::Set2DMassCombinedBkgModelName(const char *name) {m_2dMassCombinedBkgModelName=name;}
 
void RooDstarD0MassFitter::Set2DMassSigYieldName(const char* name) {m_2dMassSigYieldName=name;}
void RooDstarD0MassFitter::Set2DMassCombBkgYieldName(const char* name) {m_2dMassCombBkgYieldName=name;}
void RooDstarD0MassFitter::Set2DMassRandPiBkgYieldName(const char* name) {m_2dMassPiBkgYieldName=name;}
void RooDstarD0MassFitter::Set2DMassFakeD0BkgYieldName(const char* name) {m_2dMassD0BkgYieldName=name;}

void RooDstarD0MassFitter::Set2DMassCombinedBkgYieldName(const char *name) {m_2dMassCombinedBkgYieldName=name;}

const char* RooDstarD0MassFitter::GetDelmPartName() {return m_delmPartName;}
const char* RooDstarD0MassFitter::GetDelmName() {return m_delmName;}

const char* RooDstarD0MassFitter::GetDelmSigModelName() {return m_delmSigModelName;}
const char* RooDstarD0MassFitter::GetDelmBkgModelName() {return m_delmBkgModelName;}

const char* RooDstarD0MassFitter::Get2DMassSigModelName() {return m_2dMassSigModelName;}
const char* RooDstarD0MassFitter::Get2DMassCombBkgModelName() {return m_2dMassCombBkgModelName;}
const char* RooDstarD0MassFitter::Get2DMassRandPiBkgModelName() {return m_2dMassPiBkgModelName;}
const char* RooDstarD0MassFitter::Get2DMassFakeD0BkgModelName() {return m_2dMassD0BkgModelName;}
const char* RooDstarD0MassFitter::Get2DMassCombinedBkgModelName() {return m_2dMassCombinedBkgModelName;}
 
const char* RooDstarD0MassFitter::Get2DMassSigYieldName() {return m_2dMassSigYieldName;}
const char* RooDstarD0MassFitter::Get2DMassCombBkgYieldName() {return m_2dMassCombBkgYieldName;}
const char* RooDstarD0MassFitter::Get2DMassRandPiBkgYieldName() {return m_2dMassPiBkgYieldName;}
const char* RooDstarD0MassFitter::Get2DMassFakeD0BkgYieldName() {return m_2dMassD0BkgYieldName;}
const char* RooDstarD0MassFitter::Get2DMassCombinedBkgYieldName() {return m_2dMassCombinedBkgYieldName;}

//=============================================================================
// Destructor
//=============================================================================
RooDstarD0MassFitter::~RooDstarD0MassFitter() {}
//=============================================================================
