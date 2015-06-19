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
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooVoigtian.h"
#include "RooPhysFitter/RooCruijff.h"
#include "RooPhysFitter/RooCruijffSimple.h"
#include "RooPhysFitter/RooPhiBg.h"

// ROOT
#include "TChain.h"
#include "TTree.h"
#include "TTreeFormula.h"
#include "TString.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TEntryList.h"

// local
#include "RooPhysFitter/RooDMassFitter.h"
#include "RooPhysFitter/Exceptions.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RooDMassFitter
//
// 2011-05-16 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

//using namespace RooPhysFit;
// This is a really bad idea, and should be fixed!
using namespace RooPhysFit;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

RooDMassFitter::RooDMassFitter(  )
  : RooPhysFitter(), m_dMassPartName(""), m_dMassName("mass"),
    m_dMassSigModelName("sigModel"), m_dMassBkgModelName("bkgModel"),
    m_dMassSigYieldName("nsig"), m_dMassBkgYieldName("nbkg"),
    m_spectSetName("Spectators"), m_catSetName("Categories"),
    m_printEntries(kFALSE), m_printFreq(100),
    m_varNameToBranchName(), m_catNameToBranchName(),
    m_varNameToFunction(), m_varNameToFormula()
{
}

RooDMassFitter::RooDMassFitter( const char* name, const char* title )
  : RooPhysFitter(name, title), m_dMassPartName(""), m_dMassName("mass"),
    m_dMassSigModelName("sigModel"), m_dMassBkgModelName("bkgModel"),
    m_dMassSigYieldName("nsig"), m_dMassBkgYieldName("nbkg"),
    m_spectSetName("Spectators"), m_catSetName("Categories"),
    m_printEntries(kFALSE), m_printFreq(100),
    m_varNameToBranchName(), m_catNameToBranchName(),
    m_varNameToFunction(), m_varNameToFormula()
{
}

void RooDMassFitter::MakeDMassVar(Float_t xmin, Float_t xmax,
                                  const char* unit, const char* title)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassVar",
                           "No RooWorkspace object is defined.");
  }
  if (!m_dMassName||strcmp(m_dMassName,"")==0) {
    throw GeneralException("RooDMassFitter::MakeDMassVar",
                           "No D mass variable name specified.");
  }
  RooRealVar mass(m_dMassName,(!title)?"":title,xmin,xmax,
                  (!unit)?"MeV/c^{2}":unit);
  if (m_rws->import(mass)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassVar", *m_rws, mass);
  }
}



void RooDMassFitter::AddSpectator(const char *name, Double_t xmin,
                                  Double_t xmax, const char *brName,
                                  const char *unit, const char *title,
                                  const char* setName)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::AddSpectator",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
                 (!unit)?"":unit);
  if (m_rws->import(var)) {
    throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws, var);
  }
  std::string s_brName = (brName==NULL) ? "" : brName;

  if (s_brName!="") {
    m_varNameToBranchName[name]=s_brName;
  }
  if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
    throw GeneralException("RooDMassFitter::AddSpectator",
                           "No spectator set name specified.");
  }
  if (m_rws->extendSet(m_spectSetName, name)) {
      throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            m_spectSetName, name);
  }
  if (setName&&strcmp(setName,"")!=0) {
    if (m_rws->extendSet(setName, name)) {
      throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            setName, name);
    }
  }
}

void RooDMassFitter::AddSpectator(const char *name, Double_t xmin,
                                  Double_t xmax,
                                  RooDMassFitter::DoubleFun fun,
                                  const char *brName, const char *unit,
                                  const char *title, const char* setName)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::AddSpectator",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
                 (!unit)?"":unit);
  if (m_rws->import(var)) {
    throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws, var);
  }
  if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
    throw GeneralException("RooDMassFitter::AddSpectator",
                           "No spectator set name specified.");
  }
  if (m_rws->extendSet(m_spectSetName, name)) {
      throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            m_spectSetName, name);
  }
  std::string s_brName = (brName==NULL) ? "" : brName;
  if (s_brName!="") {
    m_varNameToBranchName[name]=s_brName;
  }
  m_varNameToFunction[name]=fun;
  if (setName&&strcmp(setName,"")!=0) {
    if (m_rws->extendSet(setName, name)) {
      throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            setName, name);
    }
  }
}

void RooDMassFitter::AddSpectator(const char *name, Double_t xmin,
                                  Double_t xmax,
                                  TFormula& fun,
                                  const char *brName, const char *unit,
                                  const char *title, const char* setName)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::AddSpectator",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
                 (!unit)?"":unit);
  if (m_rws->import(var)) {
    throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws, var);
  }
  if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
    throw GeneralException("RooDMassFitter::AddSpectator",
                           "No spectator set name specified.");
  }
  if (fun.GetNdim()!=1) {
    std::stringstream msg;
    msg << "Expected one dimension for TFormula " << fun.GetName()
        << ", got " << fun.GetNdim();
    throw GeneralException("RooDMassFitter::AddSpectator",msg.str());
  }
   if (fun.GetNpar()!=0) {
    std::stringstream msg;
    msg << "Expected zero parameters for TFormula " << fun.GetName()
        << ", got " << fun.GetNpar();
    throw GeneralException("RooDMassFitter::AddSpectator",msg.str());
  }
  if (m_rws->extendSet(m_spectSetName, name)) {
      throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            m_spectSetName, name);
  }
  std::string s_brName = (brName==NULL) ? "" : brName;
  if (s_brName!="") {
    m_varNameToBranchName[name]=s_brName;
  }
  m_varNameToFormula[name]=fun;
  if (setName&&strcmp(setName,"")!=0) {
    if (m_rws->extendSet(setName, name)) {
      throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            setName, name);
    }
  }
}


void RooDMassFitter::AddCategory(const char* name,
                                  std::vector<std::string> types,
                                  std::vector<Int_t> indices,
                                  const char* brName,
                                  const char* title)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::AddCategory",
                           "No RooWorkspace object is defined.");
  }
  if (types.size()==0) {
    throw GeneralException("RooDMassFitter::AddCategory",
                           "No category types have been specified.");
  }

  if (indices.size()!=types.size()) {
    std::stringstream msg;
    msg << "Number of category types " << types.size()
        << " does not match number of indices " << indices.size();
    throw GeneralException("RooDMassFitter::AddCategory", msg.str());
  }

  RooCategory cat(name, ((!title)||(strcmp(title,"")==0))?"":title);
  for (UInt_t i=0; i<types.size(); ++i) {
    std::string type = types[i];
    Int_t index = indices[i];
    if (cat.defineType(type.c_str(), index)) {
      std::stringstream msg;
      msg << "Failed to add category type " << type << " to RooCategory "
          << name;
      throw GeneralException("RooDMassFitter::AddCategory", msg.str());
    }
  }
  if (m_rws->import(cat)) {
    throw WSImportFailure("RooDMassFitter::AddCategory", *m_rws, cat);
  }
  if (!m_catSetName||strcmp(m_catSetName,"")==0) {
    throw GeneralException("RooDMassFitter::AddCategory",
                           "No category set name specified.");
  }
  if (m_rws->extendSet(m_catSetName, name)) {
    throw WSImportFailure("RooDMassFitter::AddSpectator", *m_rws,
                            m_catSetName, name);
  }
  std::string s_brName = (brName==NULL) ? "" : brName;
  if (s_brName!="") {
    m_catNameToBranchName[name]=s_brName;
  }
}

void RooDMassFitter::AddCategory(const char* name,
                                 TString* types,
                                 Int_t* indices, UInt_t ntypes,
                                 const char* brName,
                                 const char* title)
{
    std::vector<std::string> v_types;
    std::vector<Int_t> v_indices;
    for (UInt_t i=0; i<ntypes; ++i) {
      v_types.push_back((types[i]).Data());
      v_indices.push_back(indices[i]);
    }
    this->AddCategory(name, v_types, v_indices, brName, title);
}

void RooDMassFitter::MakeDMassSigGauss(RooRealVar& mu, RooRealVar& sig)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooGaussian dMassSigModel(m_dMassSigModelName, "", *mass, mu, sig);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigGauss(Float_t mu_start, Float_t mu_min,
                                       Float_t mu_max, Float_t sig_start,
                                       Float_t sig_min, Float_t sig_max,
                                       const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sigTitle.Form("%s #sigma", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("dmass_sig_sigma", sigTitle.Data(), sig_start, sig_min,
                 sig_max, unit);
  RooGaussian dMassSigModel(m_dMassSigModelName, "", *mass, mu, sig);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigBiGauss(RooRealVar& mu, RooRealVar& sig0,
                                         RooRealVar& sig1oSig0,
                                         RooRealVar& coreFrac,
                                         const char* sig1Name,
                                         const char* sig1Title)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigBiGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }

  RooGaussian dmass_sig_g0("dmass_sig_gauss0", "", *mass, mu, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1",
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(sig0.getUnit());

  RooGaussian dmass_sig_g1("dmass_sig_gauss1", "", *mass, mu, sig1);
  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_g0,dmass_sig_g1),
                          RooArgList(coreFrac));
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigBiGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigBiGauss(Float_t mu_start, Float_t mu_min,
                                         Float_t mu_max, Float_t sig0_start,
                                         Float_t sig0_min, Float_t sig0_max,
                                         Float_t sig1oSig0_start,
                                         Float_t sig1oSig0_min,
                                         Float_t sig1oSig0_max,
                                         Float_t coreFrac_start,
                                         const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigBiGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }

  TString muTitle="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString coreFracTitle="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
    sig1Title="#sigma_{tail}";
    coreFracTitle="f_{core}";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sig0Title.Form("%s #sigma_{core}", m_dMassPartName);
    sig1Title.Form("%s #sigma_{tail}", m_dMassPartName);
    sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_dMassPartName);
    coreFracTitle.Form("%s f_{core}", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start,
                mu_min, mu_max, unit);
  RooRealVar sig0("dmass_sig_sigma0", sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian dmass_sig_g0("dmass_sig_gauss0", "", *mass, mu, sig0);

  RooRealVar sig1oSig0("dmass_sig_s1oS0", sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);

  RooFormulaVar sig1("dmass_sig_sigma1", sig1Title.Data(), "@0*@1",
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);

  RooGaussian dmass_sig_g1("dmass_sig_gauss1", "", *mass, mu, sig1);

  RooRealVar coreFrac("dmass_sig_coreFrac", coreFracTitle.Data(),
                      coreFrac_start,0.0,1);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_g0,dmass_sig_g1),
                          RooArgList(coreFrac));
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigBiGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigBiGauss(RooRealVar& mu0, RooRealVar& mu1,
                                         RooRealVar& sig0,
                                         RooRealVar& sig1oSig0,
                                         RooRealVar& coreFrac,
                                         const char* sig1Name,
                                         const char* sig1Title)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigBiGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooGaussian dmass_sig_g0("dmass_sig_gauss0", "", *mass, mu0, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1",
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(sig0.getUnit());

  RooGaussian dmass_sig_g1("dmass_sig_gauss1", "", *mass, mu1, sig1);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_g0,dmass_sig_g1),
                          RooArgList(coreFrac));
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigBiGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigBiGauss(Float_t mu0_start, Float_t mu0_min,
                                         Float_t mu0_max,
                                         Float_t mu1_start, Float_t mu1_min,
                                         Float_t mu1_max,Float_t sig0_start,
                                         Float_t sig0_min, Float_t sig0_max,
                                         Float_t sig1oSig0_start,
                                         Float_t sig1oSig0_min,
                                         Float_t sig1oSig0_max,
                                         Float_t coreFrac_start,
                                         const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigBiGauss",
                             *m_rws, m_dMassName, "RooRealVar");
  }
//   if (coreFrac_start<0.5) {
//     throw GeneralException("RooDMassFitter::MakeDMassSigBiGauss",
//                            "Core fraction cannot be less than 50%");
//   }
  TString mu0Title="";
  TString mu1Title="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString coreFracTitle="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    mu0Title="#mu_{core}";
    mu1Title="#mu_{tail}";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
    sig1Title="#sigma_{tail}";
    coreFracTitle="f_{core}";
  }
  else {
    mu0Title.Form("%s #mu_{core}", m_dMassPartName);
    mu1Title.Form("%s #mu_{tail}", m_dMassPartName);
    sig0Title.Form("%s #sigma_{core}", m_dMassPartName);
    sig1Title.Form("%s #sigma_{tail}", m_dMassPartName);
    sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", m_dMassPartName);
    coreFracTitle.Form("%s f_{core}", m_dMassPartName);
  }

  RooRealVar mu0("dmass_sig_mu0", mu0Title.Data(),
                 mu0_start, mu0_min, mu0_max, unit);
  RooRealVar sig0("dmass_sig_sigma0", sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian dmass_sig_g0("dmass_sig_gauss0", "", *mass, mu0, sig0);

  RooRealVar sig1oSig0("dmass_sig_s1oS0", sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
  RooRealVar mu1("dmass_sig_mu1", mu1Title.Data(),
                 mu1_start, mu1_min, mu1_max, unit);
  RooFormulaVar sig1("dmass_sig_sigma1", sig1Title.Data(), "@0*@1",
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);

  RooGaussian dmass_sig_g1("dmass_sig_gauss1", "", *mass, mu1, sig1);

  RooRealVar coreFrac("dmass_sig_coreFrac", coreFracTitle.Data(),
                      coreFrac_start,0.0,1);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                       RooArgList(dmass_sig_g0,dmass_sig_g1),
                       RooArgList(coreFrac));
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigBiGauss",
                          *m_rws, dMassSigModel);
  }
}


void RooDMassFitter::MakeDMassSigTriGauss(RooRealVar& mu,
                                          RooRealVar& sig0,
                                          RooRealVar& sig1oSig0,
                                          RooRealVar& sig2oSig0,
                                          RooRealVar& coreFrac0,
                                          RooRealVar& coreFrac1,
                                          const char* sig1Name,
                                          const char* sig1Title)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigTriGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigTriGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooGaussian dmass_sig_g0("dmass_sig_gauss0", "", *mass, mu, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1",
                     RooArgList(sig1oSig0,sig0));
  RooFormulaVar sig2(sig1Name, sig1Title, "@0*@1",
                     RooArgList(sig2oSig0,sig0));
  sig1.setUnit(sig0.getUnit());

  RooGaussian dmass_sig_g1("dmass_sig_gauss1", "", *mass, mu, sig1);
  RooGaussian dmass_sig_g2("dmass_sig_gauss2", "", *mass, mu, sig2);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_g0,dmass_sig_g1,dmass_sig_g2),
                          RooArgList(coreFrac0,coreFrac1));
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigTriGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigTriGauss(Float_t mu_start, Float_t mu_min,
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
                                          const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigTriGauss",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigTriGauss",
                           *m_rws, m_dMassName, "RooRealVar");
  }

  TString muTitle="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString sig2Title="";
  TString sig2oSig0Title="";
  TString coreFrac0Title="";
  TString coreFrac1Title="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail-1}/#sigma_{core}";
    sig2oSig0Title="#sigma_{tail-2}/#sigma_{core}";
    sig1Title="#sigma_{tail-1}";
    sig2Title="#sigma_{tail-2}";
    coreFrac0Title="f_{core}";
    coreFrac1Title="f_{wide}";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sig0Title.Form("%s #sigma_{core}", m_dMassPartName);
    sig1Title.Form("%s #sigma_{tail-1}", m_dMassPartName);
    sig2Title.Form("%s #sigma_{tail-2}", m_dMassPartName);
    sig1oSig0Title.Form("%s #sigma_{tail-1}/#sigma_{core}", m_dMassPartName);
    sig2oSig0Title.Form("%s #sigma_{tail-2}/#sigma_{core}", m_dMassPartName);
    coreFrac0Title.Form("%s f_{core}", m_dMassPartName);
    coreFrac1Title.Form("%s f_{wide}", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start,
                mu_min, mu_max, unit);
  RooRealVar sig0("dmass_sig_sigma0", sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian dmass_sig_g0("dmass_sig_gauss0", "", *mass, mu, sig0);

  RooRealVar sig1oSig0("dmass_sig_s1oS0", sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
  RooRealVar sig2oSig0("dmass_sig_s2oS0", sig2oSig0Title.Data(),
                       sig2oSig0_start, sig2oSig0_min, sig2oSig0_max);

  RooFormulaVar sig1("dmass_sig_sigma1", sig1Title.Data(), "@0*@1",
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);
  RooFormulaVar sig2("dmass_sig_sigma2", sig2Title.Data(), "@0*@1",
                     RooArgList(sig2oSig0,sig0));
  sig2.setUnit(unit);

  RooGaussian dmass_sig_g1("dmass_sig_gauss1", "", *mass, mu, sig1);
  RooGaussian dmass_sig_g2("dmass_sig_gauss2", "", *mass, mu, sig2);

  RooRealVar coreFrac0("dmass_sig_coreFrac0", coreFrac0Title.Data(),
                      coreFrac0_start,0.0,1);
  RooRealVar coreFrac1("dmass_sig_coreFrac1", coreFrac1Title.Data(),
                      coreFrac1_start,0.0,1);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_g0,dmass_sig_g1,dmass_sig_g2),
                          RooArgList(coreFrac0,coreFrac1));
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigTriGauss",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigCruijff(RooRealVar& mu, RooRealVar& sigL,
                                         RooRealVar& sigR, RooRealVar& alphaL,
                                         RooRealVar& alphaR)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigCruijff",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooCruijff dMassSigModel(m_dMassSigModelName, "", *mass, mu, sigL, sigR, alphaL,
                           alphaR);

 //  if (m_rws->importClassCode(RooCruijff::Class(),kTRUE)) {
//     throw WSImportCodeFailure("RooDMassFitter::MakeDMassSigCruijff",
//                                    *m_rws, "RooCruijff");
//   }
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigCruijff",
                          *m_rws, dMassSigModel);
  }
  //m_rws->importClassCode();
}


void RooDMassFitter::MakeDMassSigCruijff(Float_t mu_start, Float_t mu_min,
                                         Float_t mu_max, Float_t sigL_start,
                                         Float_t sigL_min, Float_t sigL_max,
                                         Float_t sigR_start, Float_t sigR_min,
                                         Float_t sigR_max, Float_t alphaL_start,
                                         Float_t alphaL_min, Float_t alphaL_max,
                                         Float_t alphaR_start, Float_t alphaR_min,
                                         Float_t alphaR_max, const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigCruijff",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigLTitle="";
  TString alphaLTitle="";
  TString sigRTitle="";
  TString alphaRTitle="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sigLTitle="#sigma_{L}";
    alphaLTitle="#alpha_{L}";
    sigRTitle="#sigma_{R}";
    alphaRTitle="#alpha_{R}";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sigLTitle.Form("%s #sigma_{L}", m_dMassPartName);
    alphaLTitle.Form("%s #alpha_{L}", m_dMassPartName);
    sigRTitle.Form("%s #sigma_{R}", m_dMassPartName);
    alphaRTitle.Form("%s #alpha_{R}", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sigL("dmass_sig_sigmaL", sigLTitle.Data(), sigL_start, sigL_min,
                 sigL_max, unit);
  RooRealVar alphaL("dmass_sig_alphaL", alphaLTitle.Data(), alphaL_start,
                   alphaL_min, alphaL_max);
  RooRealVar sigR("dmass_sig_sigmaR", sigRTitle.Data(), sigR_start, sigR_min,
                 sigR_max, unit);
  RooRealVar alphaR("dmass_sig_alphaR", alphaRTitle.Data(), alphaR_start,
                   alphaR_min, alphaR_max);

  RooCruijff dMassSigModel(m_dMassSigModelName, "", *mass, mu, sigL, sigR, alphaL, alphaR);
//   if (m_rws->importClassCode(RooCruijff::Class(),kTRUE)) {
//     throw WSImportCodeFailure("RooDMassFitter::MakeDMassSigCruijff",
//                                    *m_rws, "RooCruijff");
//   }
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigCruijff",
                          *m_rws, dMassSigModel);
  }
  //m_rws->importClassCode();
}

void RooDMassFitter::MakeDMassSigCruijff(RooRealVar& mu, RooRealVar& sig,
                                         RooRealVar& alphaL, RooRealVar& alphaR)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigCruijff",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooCruijffSimple dMassSigModel(m_dMassSigModelName, "", *mass, mu, sig, alphaL, alphaR);
 //  if (m_rws->importClassCode(RooCruijffSimple::Class(),kTRUE)) {
//     throw WSImportCodeFailure("RooDMassFitter::MakeDMassSigCruijff",
//                                    *m_rws, "RooCruijffSimple");
//   }
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigCruijff",
                          *m_rws, dMassSigModel);
  }
  //m_rws->importClassCode();
}

void RooDMassFitter::MakeDMassSigCruijff(Float_t mu_start, Float_t mu_min,
                                         Float_t mu_max, Float_t sig_start,
                                         Float_t sig_min, Float_t sig_max,
                                         Float_t alphaL_start, Float_t alphaL_min,
                                         Float_t alphaL_max,
                                         Float_t alphaR_start, Float_t alphaR_min,
                                         Float_t alphaR_max, const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigCruijff",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString alphaLTitle="";
  TString alphaRTitle="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    alphaLTitle="#alpha_{L}";
    alphaRTitle="#alpha_{R}";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sigTitle.Form("%s #sigma", m_dMassPartName);
    alphaLTitle.Form("%s #alpha_{L}", m_dMassPartName);
    alphaRTitle.Form("%s #alpha_{R}", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("dmass_sig_sigma", sigTitle.Data(), sig_start, sig_min,
                 sig_max, unit);
  RooRealVar alphaL("dmass_sig_alphaL", alphaLTitle.Data(), alphaL_start,
                   alphaL_min, alphaL_max);
  RooRealVar alphaR("dmass_sig_alphaR", alphaRTitle.Data(), alphaR_start,
                   alphaR_min, alphaR_max);

  RooCruijffSimple dMassSigModel(m_dMassSigModelName, "", *mass, mu, sig, alphaL, alphaR);
//   if (m_rws->importClassCode(RooCruijffSimple::Class(),kTRUE)) {
//     throw WSImportCodeFailure("RooDMassFitter::MakeDMassSigCruijff",
//                                    *m_rws, "RooCruijffSimple");
//   }
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigCruijff",
                          *m_rws, dMassSigModel);
  }
  //m_rws->importClassCode();
}


void RooDMassFitter::MakeDMassSigCB(RooRealVar& mu, RooRealVar& sig,
                                    RooRealVar& alpha, RooRealVar& n)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigCB",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigCB",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooCBShape dMassSigModel(m_dMassSigModelName, "", *mass, mu, sig, alpha, n);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigCB",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigCB(Float_t mu_start, Float_t mu_min,
                                    Float_t mu_max, Float_t sig_start,
                                    Float_t sig_min, Float_t sig_max,
                                    Float_t alpha_start, Float_t alpha_min,
                                    Float_t alpha_max, Float_t n_start,
                                    Float_t n_min, Float_t n_max,
                                    const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigCB",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigCB",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString alphaTitle="";
  TString nTitle="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    alphaTitle="#alpha";
    nTitle="n";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sigTitle.Form("%s #sigma", m_dMassPartName);
    alphaTitle.Form("%s #alpha", m_dMassPartName);
    nTitle.Form("%s n", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("dmass_sig_sigma", sigTitle.Data(), sig_start, sig_min,
                 sig_max, unit);
  RooRealVar alpha("dmass_sig_alpha", alphaTitle.Data(), alpha_start,
                   alpha_min, alpha_max);
  RooRealVar n("dmass_sig_n", nTitle.Data(), n_start, n_min, n_max);

  RooCBShape dMassSigModel(m_dMassSigModelName, "", *mass, mu, sig, alpha, n);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigCB",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigVoigtian(RooRealVar& mu, RooRealVar& sig,
                                          RooRealVar& gamma, Bool_t doFast)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigVoigtian",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigVoigtian",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  RooVoigtian dMassSigModel(m_dMassSigModelName, "", *mass, mu, gamma, sig, doFast);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigVoigtian",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigVoigtian(Float_t mu_start, Float_t mu_min, Float_t mu_max,
                                          Float_t sig_start, Float_t sig_min, Float_t sig_max,
                                          Float_t gamma_start, Float_t gamma_min,
                                          Float_t gamma_max, const char* unit, Bool_t doFast)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigVoigtian",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigVoigtian",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString gammaTitle="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    gammaTitle="#Gamma";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sigTitle.Form("%s #sigma", m_dMassPartName);
    gammaTitle.Form("%s #Gamma", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("dmass_sig_sigma", sigTitle.Data(), sig_start, sig_min,
                 sig_max, unit);
  RooRealVar gamma("dmass_sig_gamma", gammaTitle.Data(), gamma_start, gamma_min,
                   gamma_max, unit);
  RooVoigtian dMassSigModel(m_dMassSigModelName, "", *mass, mu, gamma, sig, doFast);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigVoigtian",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassSigVoigtian(Float_t mu_start, Float_t mu_min, Float_t mu_max,
                                          Float_t sig_start, Float_t sig_min, Float_t sig_max,
                                          Float_t gamma, const char* unit, Bool_t doFast)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassSigVoigtian",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassSigVoigtian",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString gammaTitle="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    gammaTitle="#Gamma";
  }
  else {
    muTitle.Form("%s #mu", m_dMassPartName);
    sigTitle.Form("%s #sigma", m_dMassPartName);
    gammaTitle.Form("%s #Gamma", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", muTitle.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig("dmass_sig_sigma", sigTitle.Data(), sig_start, sig_min,
                 sig_max, unit);
  RooRealVar gammaVar("dmass_sig_gamma", gammaTitle.Data(), gamma, unit);
  RooVoigtian dMassSigModel(m_dMassSigModelName, "", *mass, mu, gammaVar, sig, doFast);
  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassSigVoigtian",
                          *m_rws, dMassSigModel);
  }
}

void RooDMassFitter::MakeDMassBkgFlat(RooRealVar& grad)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgFlat",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgFlat",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooChebychev dMassBkgModel(m_dMassBkgModelName,"",*mass,RooArgList(grad));
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgFlat",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgFlat(Float_t grad_start, Float_t grad_min,
                                        Float_t grad_max,const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgFlat",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgFlat",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }
  TString gradTitle="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    gradTitle="#nabla";
  }
  else {
    gradTitle.Form("%s #nabla", m_dMassPartName);
  }

  RooRealVar grad("dmass_bkg_poly_c1", gradTitle.Data(), grad_start, grad_min,
                  grad_max, invMassUnit);
  RooChebychev dMassBkgModel(m_dMassBkgModelName,"",*mass,RooArgList(grad));
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgFlat",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgExp(RooRealVar& decay)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgExp",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgExp",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooExponential dMassBkgModel(m_dMassBkgModelName,"",*mass,decay);
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgExp",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgExp(Float_t decay_start, Float_t decay_min,
                                        Float_t decay_max,const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgExp",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgExp",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }
  TString decayTitle="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    decayTitle="#gamma";
  }
  else {
    decayTitle.Form("%s #gamma", m_dMassPartName);
  }

  RooRealVar decay("dmass_bkg_exp_decay", decayTitle.Data(), decay_start, decay_min,
                  decay_max, invMassUnit);
  RooExponential dMassBkgModel(m_dMassBkgModelName,"",*mass,decay);
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgExp",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgQuadratic(RooRealVar& c1,
                                           RooRealVar& c2)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgQuadratic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgQuadratic",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooChebychev dMassBkgModel(m_dMassBkgModelName,"",*mass,RooArgList(c1,c2));
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgQuadratic",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgQuadratic(Float_t c1_start,Float_t c1_min,
                                           Float_t c1_max, Float_t c2_start,
                                           Float_t c2_min, Float_t c2_max,
                                           const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgQuadratic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgQuadratic",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }
  TString invMass2Unit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMass2Unit.Form("(%s)^{-2}", unit);
  }
  TString c1Title="";
  TString c2Title="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    c1Title="c_{1}";
    c2Title="c_{2}";
  }
  else {
    c1Title.Form("%s c_{1}", m_dMassPartName);
    c2Title.Form("%s c_{2}", m_dMassPartName);
  }

  RooRealVar c1("dmass_bkg_poly_c1", c1Title.Data(), c1_start, c1_min,
                c1_max, invMassUnit.Data());
  RooRealVar c2("dmass_bkg_poly_c2", c2Title.Data(), c2_start, c2_min,
                c2_max, invMass2Unit.Data());
  RooChebychev dMassBkgModel(m_dMassBkgModelName,"",*mass,RooArgList(c1,c2));
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgQuadratic",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgCubic(RooRealVar& c1,
                                       RooRealVar& c2,
                                       RooRealVar& c3)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgCubic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgCubic",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooChebychev dMassBkgModel(m_dMassBkgModelName,"",*mass,RooArgList(c1,c2,c3));
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgCubic",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakeDMassBkgCubic(Float_t c1_start,Float_t c1_min,
                                       Float_t c1_max, Float_t c2_start,
                                       Float_t c2_min, Float_t c2_max,
                                       Float_t c3_start, Float_t c3_min,
                                       Float_t c3_max, const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakeDMassBkgCubic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakeDMassBkgCubic",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }
  TString invMass2Unit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMass2Unit.Form("(%s)^{-2}", unit);
  }
  TString invMass3Unit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMass3Unit.Form("(%s)^{-3}", unit);
  }
  TString c1Title="";
  TString c2Title="";
  TString c3Title="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    c1Title="c_{1}";
    c2Title="c_{2}";
    c3Title="c_{3}";
  }
  else {
    c1Title.Form("%s c_{1}", m_dMassPartName);
    c2Title.Form("%s c_{2}", m_dMassPartName);
    c3Title.Form("%s c_{3}", m_dMassPartName);
  }

  RooRealVar c1("dmass_bkg_poly_c1", c1Title.Data(), c1_start, c1_min,
                c1_max, invMassUnit.Data());
  RooRealVar c2("dmass_bkg_poly_c2", c2Title.Data(), c2_start, c2_min,
                c2_max, invMass2Unit.Data());
  RooRealVar c3("dmass_bkg_poly_c3", c3Title.Data(), c3_start, c3_min,
                c3_max, invMass2Unit.Data());
  RooChebychev dMassBkgModel(m_dMassBkgModelName,"",*mass,RooArgList(c1,c2,c3));
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassBkgCubic",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakePhiBkg(RooRealVar& c1, RooRealVar& c2)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakePhiBkg",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakePhiBkg",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  RooPhiBg dMassBkgModel(m_dMassBkgModelName,"",*mass,c1,c2);

  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakePhiBkg",
                          *m_rws, dMassBkgModel);
  }
}

void RooDMassFitter::MakePhiBkg(Float_t c1_start, Float_t c1_min,
                                Float_t c1_max,
                                Float_t c2_start, Float_t c2_min,
                                Float_t c2_max, const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDMassFitter::MakePhiBkg",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter:MakePhiBkg",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }

  TString c1Title="";
  TString c2Title="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    c1Title="c_{1}";
    c2Title="c_{2}";
  }
  else {
    c1Title.Form("%s c_{1}", m_dMassPartName);
    c2Title.Form("%s c_{2}", m_dMassPartName);
  }

  RooRealVar c1("dmass_bkg_c1", c1Title.Data(), c1_start, c1_min,
                c1_max, invMassUnit.Data());
  RooRealVar c2("dmass_bkg_c2", c2Title.Data(), c2_start, c2_min,
                c2_max, unit);

  RooPhiBg dMassBkgModel(m_dMassBkgModelName,"",*mass,c1,c2);

  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooDMassFitter::MakePhiBkg",
                          *m_rws, dMassBkgModel);
  }
}

// make 1D D0 model - specify expected fraction of each background type
// NB. No check that sum(frac)==1
void RooDMassFitter::MakeDMassModel(Float_t frac_sig, Float_t frac_bkg)
{
  if (frac_sig<0&&frac_bkg<0) {
    throw GeneralException("RooDMassFitter::MakeDMassModel",
       "Fit fractions are less than zero. At least one fraction must be >0");
  }
  if (frac_sig>1) {
    std::stringstream msg;
    msg << "Signal fit fraction is greater than unity (" << frac_sig << ")";
    throw GeneralException("RooDMassFitter::MakeDMassModel", msg.str());
  }
  if (frac_bkg>1) {
    std::stringstream msg;
    msg << "Combinatoric background fit fraction is greater than unity ("
        << frac_bkg << ")";
    throw GeneralException("RooDMassFitter::MakeDMassModel", msg.str());
  }
  if (!m_rws)
  {
    throw GeneralException("RooDMassFitter::MakeDMassModel",
                           "No RooWorkspace object is defined!");
  }
  RooDataSet* rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassModel",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassModel",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  RooAbsPdf* sigModel=m_rws->pdf(m_dMassSigModelName);
  if (!sigModel&&frac_sig>=0) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassModel",
                             *m_rws,m_dMassSigModelName,"RooAbsPdf");
  }
  RooAbsPdf* bkgModel=m_rws->pdf(m_dMassBkgModelName);
  if (!bkgModel&&frac_bkg>=0) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassModel",
                             *m_rws,m_dMassBkgModelName,"RooAbsPdf");
  }
  Int_t nentries = rds->numEntries();
  if (nentries<=0) {
    std::stringstream msg;
    msg << "Got invalid number of entries " << nentries
        << " from RooDataSet " << m_dataSetName;
    throw GeneralException("RooDMassFitter::MakeDMassModel",msg.str());
  }
  Int_t nsig_est = static_cast<Int_t>(frac_sig*nentries);
  Int_t nbkg_est = static_cast<Int_t>(frac_bkg*nentries);

  RooRealVar nsig(m_dMassSigYieldName, "N_{sig.}", nsig_est, 0, nentries);
  RooRealVar nbkg(m_dMassBkgYieldName, "N_{bkg.}", nbkg_est, 0, nentries);
  
  
  RooArgList yieldList;//(nsig, nbkg);
  RooArgList pdfList;//(*sigModel, *bkgModel);

  if (frac_sig>=0) {
    pdfList.add(*sigModel);
    yieldList.add(nsig);
  }
  if (frac_bkg>=0) {
    pdfList.add(*bkgModel);
    yieldList.add(nbkg);
  }
  assert(pdfList.getSize()!=0);
  assert(yieldList.getSize()!=0);

  RooAddPdf model(m_modelName, "", pdfList, yieldList);

  if (m_rws->import(model)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassModel",
                          *m_rws, model);
  }
}

void RooDMassFitter::MakeDMassDataSet(TTree* tt, const char* dMassVarname,
                                      const char* name, const char* title,
                                      const char* cuts)
{
  if (!m_rws)
  {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                           "No RooWorkspace object is defined.");
  }
  if (!tt) {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
           "Expected pointer to TTree as argument, got NULL pointer.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDMassFitter::MakeDMassDataSet",
                             *m_rws, m_dMassName, "RooRealVar");
  }
  if (!dMassVarname||strcmp(dMassVarname,"")==0) {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                           "No D mass branch name specified.");
  }
  if (!name||strcmp(name,"")==0) {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                           "No RooDataSet name specified.");
  }
  Long64_t nTotal = tt->GetEntries();
  if (nTotal==0) {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                           "No entries in input TTree.");
  }
  TEntryList* elist=0;
  tt->SetBranchStatus("*",1);
  if (cuts&&strcmp(cuts,"")!=0) {
    tt->Draw(">>elist",cuts, "entryList");
    elist = (TEntryList*)gDirectory->Get("elist");
    if (!elist) {
      std::stringstream msg;
      msg << "Failed to retrieve TEntryList for cuts " << cuts;
      throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                             msg.str());
    }
    tt->SetEntryList(elist);
  }

  // TTree* ttReduced = tt->CopyTree(cuts);
  Long64_t nentries = !elist?tt->GetEntries():elist->GetN();
  if (nentries==0) {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                           "No entries in TTree after cuts.");
  }

  Float_t M_f=0;
  Double_t M=0;
  // if this is a TChain, then we need to use the daughter's method
  tt->SetBranchStatus("*", 1);

  TChain* ch=0;
  ch=dynamic_cast<TChain*>(tt);
  std::string masstype=ch?GetBranchType(ch, dMassVarname):GetBranchType(tt, dMassVarname);
  if (!ch) {
    if (masstype.compare("Float_t")==0) {
      tt->SetBranchAddress(dMassVarname, &M_f);
    }
    else if (masstype.compare("Double_t")==0) {
      tt->SetBranchAddress(dMassVarname, &M);
    }
    else {
      std::stringstream msg;
      msg << "Got unexpected type " << masstype << " for variable "
          << dMassVarname;
      throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
    }
  }
  else {
    if (masstype.compare("Float_t")==0) {
      ch->SetBranchAddress(dMassVarname, &M_f);
    }
    else if (masstype.compare("Double_t")==0) {
      ch->SetBranchAddress(dMassVarname, &M);
    }
    else {
      std::stringstream msg;
      msg << "Got unexpected type " << masstype << " for variable "
          << dMassVarname;
      throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
    }
  }

  RooArgSet observables(*mass);
  RooArgSet args(*mass);

  std::map<std::string, void*> varMap;
  std::map<std::string, void*> catMap;

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
        throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
      }
      std::string branchName=this->GetVarBranchName(varName);
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
        throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
      }
      if (!ch) {
        tt->SetBranchAddress(branchName.c_str(), varMap[varName]);
      }
      else {
        ch->SetBranchAddress(branchName.c_str(), varMap[varName]);
      }
    }
  }
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
        throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
      }
      std::string branchName=this->GetCatBranchName(catName);
      std::string type=GetBranchType(tt, branchName);
      if ( !(type.compare("Int_t")==0 || type.compare("Bool_t")==0 || type.compare("UInt_t")==0) ) {
        std::stringstream msg;
        msg << "Requested branch name " << branchName << " is of type "
            << type << ", but categories can only be of type Int_t, UInt_t or Bool_t";
        throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
      }
      if (type.compare("Int_t")==0) {
        catMap[catName] = new Int_t();
      }
      else if (type.compare("UInt_t")==0) {
        catMap[catName] = new UInt_t();
      }
      else {
        catMap[catName] = new Bool_t();
      }
      if (!ch) {
        tt->SetBranchAddress(branchName.c_str(), catMap[catName]);
      }
      else {
        ch->SetBranchAddress(branchName.c_str(), catMap[catName]);
      }
    }
  }

  RooDataSet *rds = new RooDataSet(name, title?title:"", args);
  Long64_t entry=0;
  Long64_t localEntry=0;
  Long64_t entryNumber=0;

  std::cout << "RooDMassFitter::MakeDMassDataSet: Initial entries = "
            << nTotal << std::endl;
  if (cuts&&strlen(cuts)>0) {
    std::cout << "RooDMassFitter::MakeDMassDataSet: Entries passing selection cut ("
              << cuts << ") = " << nentries << std::endl;
  }

  for (entry=0; entry<nentries; ++entry)
  {
    entryNumber=tt->GetEntryNumber(entry);
    if (entryNumber<0) {
      std::stringstream msg;
      msg << "Got invalid entry number " << entryNumber;
      throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
    }
    if (ch) {
      localEntry = ch->LoadTree(entryNumber);
      if (localEntry<0) {
        std::stringstream msg;
        msg << "Got invalid entry number in current tree " << localEntry;
        throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
      }
    }

    Int_t nb;
    nb=tt->GetEntry(entryNumber);
    if (nb<=0) {
      std::stringstream msg;
      msg << "Got invalid number of bytes " << nb
          << " for entry " << entry;
      throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
    }

    if (masstype.compare("Float_t")==0) M=static_cast<Double_t>(M_f);

    Bool_t printEntry=m_printEntries&&(entry%m_printFreq==0);
    if (printEntry) {
      std::cout << "RooDMassFitter::MakeDMassDataSet: Entry " << entry
                << ", entry number " << entryNumber
                << ", entry in current tree " << localEntry
                << std::endl;
      std::cout << "RooDMassFitter::MakeDMassDataSet: D mass = " << M
                << std::endl;
    }
    if ( (mass->inRange(M,0)) ) {
      mass->setVal(M);
      Bool_t passed=kTRUE;
      if (varMap.size()!=0) {
        for (std::map<std::string, void*>::iterator it=varMap.begin();
             it!=varMap.end(); ++it)
        {
          std::string vname=(it->first);
          void *val=(it->second);
          assert (val!=NULL);
          std::string branchName=this->GetVarBranchName(vname);
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
            throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                                   msg.str());
          }
          if (!args.find(vname.c_str())) {
            std::stringstream msg;
            msg << "Unable to find variable name " << vname << " in RooArgSet";
            throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                                   msg.str());
          }
          if (printEntry) {
            std::cout << "RooDMassFitter::MakeDMassDataSet: Variable "
                      << vname << ", value = " << v << std::endl;
          }

          RooRealVar *var=dynamic_cast<RooRealVar*>(&args[vname.c_str()]);
          if (!var) {
            std::stringstream msg;
            msg << "Unable to cast RooAbsArg " << vname << " to a RooRealVar";
            throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                                   msg.str());
          }
          std::map< std::string, DoubleFun >::const_iterator it_func;
          it_func=m_varNameToFunction.find(vname);
          std::map< std::string, TFormula >::const_iterator it_form;
          it_form=m_varNameToFormula.find(vname);
          if (it_func!=m_varNameToFunction.end()) {
            const DoubleFun& fun = it_func->second;
            assert(fun);
            v = fun(v);
            if (!var->inRange(v,0)) {
              passed=kFALSE;
              if (printEntry) {
                std::cout << "RooDMassFitter::MakeDMassDataSet: Variable "
                          << vname << ", value = " << v
                          << " is not in range ("
                          << var->getMin()
                          << ", " << var->getMax() << ")" << std::endl;
              }

              break;
            }
            var->setVal(v);
          }
          else if (it_form!=m_varNameToFormula.end()) {
            const TFormula& fun = it_form->second;
            v = fun.Eval(v);
            if (!var->inRange(v,0)) {
              passed=kFALSE;
              if (printEntry) {
                std::cout << "RooDMassFitter::MakeDMassDataSet: Variable "
                          << vname
                          << ", value = " << v << " is not in range ("
                          << var->getMin()
                          << ", " << var->getMax() << ")" << std::endl;
              }

              break;
            }
            var->setVal(v);
          }
          else {
            if (!var->inRange(v,0))
            {
              passed=kFALSE;
              if (printEntry) {
                std::cout << "RooDMassFitter::MakeDMassDataSet: Variable "
                          << vname
                          << ", value = " << v << " is not in range ("
                          << var->getMin()
                          << ", " << var->getMax() << ")" << std::endl;
              }

              break;
            }
            var->setVal(v);
          }
        }
      }
      if (catMap.size()>0) {
        for (std::map<std::string, void*>::iterator it=catMap.begin();
             it!=catMap.end(); ++it)
        {
          std::string vname=(it->first);
          void* val=(it->second);
          assert (val!=NULL);
          std::string branchName=this->GetCatBranchName(vname);
          std::string type=GetBranchType(tt, branchName);
          Int_t v;
          if (type.compare("Int_t")==0) {
            Int_t* ptr=static_cast<Int_t*>(val);
            assert(ptr);
            v=(Int_t)(*ptr);
          }
          else if (type.compare("Bool_t")==0) {
            Bool_t* ptr=static_cast<Bool_t*>(val);
            assert(ptr);
            v=(Int_t)(*ptr);
          }
          else if (type.compare("UInt_t")==0) {
            UInt_t* ptr=static_cast<UInt_t*>(val);
            assert(ptr);
            v=(Int_t)(*ptr);
          }
          else {
            std::stringstream msg;
            msg << "Requested branch name " << branchName << " is of type "
                << type << ", but categories can only be of type Int_t, UInt_t or Bool_t";
            throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                                    msg.str());
          }
          if (printEntry) {
            std::cout << "RooDMassFitter::MakeDMassDataSet: Category "
                      << vname << ", value = " << v << std::endl;
          }

          RooCategory *cat=dynamic_cast<RooCategory*>(&args[vname.c_str()]);
          if (!cat) {
            std::stringstream msg;
            msg << "Unable to cast RooAbsArg " << vname << " to a RooCategory";
            throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                                   msg.str());
          }
          if (!cat->isValidIndex(v)) {
            passed=kFALSE;
            if (printEntry) {
              std::cout << "RooDMassFitter::MakeDMassDataSet: Category " << vname
                        << ", value = " << v << " is not a valid index" << std::endl;
            }
            break;
          }
          cat->setIndex(v);
        }
      }
      if (!passed) continue;
      rds->add(args);
    }
  } // loop over entries
  if (rds->numEntries()==0) {
    throw GeneralException("RooDMassFitter::MakeDMassDataSet",
                           "No entries selected!");
  }

  std::cout << "RooDMassFitter::MakeDMassDataSet: Selected entries = "
            << rds->numEntries() << std::endl;

  if (m_rws->import(*rds)) {
    throw WSImportFailure("RooDMassFitter::MakeDMassDataSet", *m_rws, *rds);
  }
  for (std::map<std::string, void*>::iterator i=varMap.begin();
       i!=varMap.end(); ++i) {
    std::string vname = i->first;
    void* val = i->second;
    if (val==NULL) continue;
    std::string branchName=this->GetVarBranchName(vname);
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
      throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
    }
  }
  varMap.clear();
  for (std::map<std::string, void*>::iterator i=catMap.begin();
       i!=catMap.end(); ++i) {
    std::string vname = i->first;
    void* val = i->second;
    if (val==NULL) continue;
    std::string branchName=this->GetCatBranchName(vname);
    std::string type=GetBranchType(tt, branchName);
    if (type.compare("Int_t")==0) {
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
      throw GeneralException("RooDMassFitter::MakeDMassDataSet", msg.str());
    }
  }
  catMap.clear();
  m_dataSetName = name;
}

// Perform a binned fit to the model PDF
// A binned clone of the data is made, which is then used to fit the PDF
// The default binning for each variable in the original dataset is used,
// except for the mass variable, which uses the specified number of bins
// The number of bins for a given variable can be changed using the
// SetBins method
// By default, a maximum likelihood fit is performed. If useChi2Method is
// set to true, then a chi^2 fit is performed instead
void RooDMassFitter::PerformDMassBinnedFit(Int_t nBins,
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
    throw GeneralException("RooDMassFitter::PerformDMassBinnedFit",
                           "No RooWorkspace object is defined");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass)
  {
    throw WSRetrievalFailure("RooDMassFitter::PerformDMassBinnedFit"
                             ,*m_rws, m_dMassName, "RooRealVar");
  }
  Int_t oldBins = mass->getBins();
  mass->setBins(nBins);
  this->PerformBinnedFit(fitName,nCores,saveSnapshot,printResults,
                         useSumW2Errors,extendedMode, useChi2Method);
  mass->setBins(oldBins);
}

void RooDMassFitter::PerformDMassIterativeBinnedFit(Int_t nBins,
                                                    std::vector<Int_t>& minuitStrategies,
                                                    const char* fitName,
                                                    Int_t nCores,
                                                    Bool_t saveSnapshot,
                                                    Bool_t printResults,
                                                    Bool_t useSumW2Errors,
                                                    Bool_t extendedMode,
                                                    Bool_t useChi2Method)
{
  std::cout<<"In RooDMassFitter::PerformDMassIterativeBinnedFit"<<std::endl;
  if (!m_rws)
  {
    throw GeneralException("RooDMassFitter::PerformDMassIterativeBinnedFit",
                           "No RooWorkspace object is defined");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass)
  {
    throw WSRetrievalFailure("RooDMassFitter::PerformDMassIterativeBinnedFit"
                             ,*m_rws, m_dMassName, "RooRealVar");
  }
  Int_t oldBins = mass->getBins();
  mass->setBins(nBins);
  this->PerformIterativeBinnedFit( minuitStrategies,fitName,nCores,saveSnapshot,printResults,
                                  useSumW2Errors,extendedMode, useChi2Method);
  mass->setBins(oldBins);
}

void RooDMassFitter::SetDMassPartName(const char* name) {m_dMassPartName=name;}
void RooDMassFitter::SetDMassName(const char* name) {m_dMassName=name;}


void RooDMassFitter::SetDMassSigModelName(const char* name) {m_dMassSigModelName=name;}
void RooDMassFitter::SetDMassBkgModelName(const char* name) {m_dMassBkgModelName=name;}

void RooDMassFitter::SetDMassSigYieldName(const char* name) {m_dMassSigYieldName=name;}
void RooDMassFitter::SetDMassBkgYieldName(const char* name) {m_dMassBkgYieldName=name;}


void RooDMassFitter::SetSpectatorSetName(const char* name) {m_spectSetName=name;}
void RooDMassFitter::SetCategorySetName(const char* name) {m_catSetName=name;}

void RooDMassFitter::SetPrintEntriesFlag(Bool_t flag) {m_printEntries=flag;}

void RooDMassFitter::SetPrintFreq(Int_t freq) {m_printFreq=freq;}

const char* RooDMassFitter::GetDMassPartName() const {return m_dMassPartName;}
const char* RooDMassFitter::GetDMassName() const {return m_dMassName;}

const char* RooDMassFitter::GetDMassSigModelName() const {return m_dMassSigModelName;}
const char* RooDMassFitter::GetDMassBkgModelName() const {return m_dMassBkgModelName;}

const char* RooDMassFitter::GetDMassSigYieldName() const {return m_dMassSigYieldName;}
const char* RooDMassFitter::GetDMassBkgYieldName() const {return m_dMassBkgYieldName;}

const char* RooDMassFitter::GetSpectatorSetName() const {return m_spectSetName;}
const char* RooDMassFitter::GetCategorySetName() const {return m_catSetName;}

const Bool_t& RooDMassFitter::GetPrintEntriesFlag() const {return m_printEntries;}

const Int_t& RooDMassFitter::GetPrintFreq() const {return m_printFreq;}

std::string RooDMassFitter::GetVarBranchName(const std::string& name) const
{
  std::string brName="";
  std::map<std::string,std::string>::const_iterator it;
  it=m_varNameToBranchName.find(name);
  if (it==m_varNameToBranchName.end()) {
    brName = name;
  }
  else {
    brName = it->second;
  }
  return brName;
}

std::string RooDMassFitter::GetCatBranchName(const std::string& name) const
{
  std::string brName="";
  std::map<std::string,std::string>::const_iterator it;
  it=m_catNameToBranchName.find(name);
  if (it==m_catNameToBranchName.end()) {
    brName = name;
  }
  else {
    brName = it->second;
  }
  return brName;
}

std::string RooDMassFitter::GetBranchType(TTree* tt, const std::string& brName) const
{
  assert(tt);
  TChain* ch=dynamic_cast<TChain*>(tt);
  TBranch* br = ch==NULL?tt->GetBranch(brName.c_str()):ch->GetBranch(brName.c_str());
  if (!br) {
    std::stringstream msg;
    msg << "Unable to retrieve branch with name " << brName << " from TTree "
        << tt->GetName();
    throw GeneralException("RooDMassFitter::GetBranchType", msg.str());
  }
  return std::string( ((TLeaf*)br->GetListOfLeaves()->At(0))->GetTypeName());
}

//=============================================================================
// Destructor
//=============================================================================
RooDMassFitter::~RooDMassFitter() {}
//=============================================================================
