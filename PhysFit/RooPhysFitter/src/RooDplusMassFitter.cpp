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
#include "RooCBShape.h"
#include "RooVoigtian.h"
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

// local
#include "RooPhysFitter/RooDplusMassFitter.h"
#include "RooPhysFitter/Exceptions.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RooDplusMassFitter
//
// 2011-09-19 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

using namespace RooPhysFit;
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

RooDplusMassFitter::RooDplusMassFitter() 
  : RooPhysFitter(), m_dplusMassName("mass"),
    m_dplusMassDplusPartName("D^{+}") /* D+ label */,
    m_dplusMassDsPartName("D_{s}^{+}") /* D_s+ label */,
    m_dplusMassBkgPartName("") /* bkg label */,
    m_dplusMassDplusModelName("dplusModel"), m_dplusMassDsModelName("dsModel"),
    m_dplusMassBkgModelName("bkgModel"), m_dplusMassDplusYieldName("ndplus"),
    m_dplusMassDsYieldName("nds"), m_dplusMassBkgYieldName("nbkg"),
    m_spectSetName("Spectators"), m_catSetName("Categories"),
    m_printEntries(kFALSE), m_printFreq(100), m_varNameToBranchName(),
    m_catNameToBranchName(), m_varNameToFunction(), m_varNameToFormula()
{
}

RooDplusMassFitter::RooDplusMassFitter( const char* name, const char* title ) 
  : RooPhysFitter(name, title), m_dplusMassName("mass"),
    m_dplusMassDplusPartName("D^{+}") /* D+ label */,
    m_dplusMassDsPartName("D_{s}^{+}") /* D_s+ label */,
    m_dplusMassBkgPartName("") /* bkg label */,
    m_dplusMassDplusModelName("dplusModel"), m_dplusMassDsModelName("dsModel"),
    m_dplusMassBkgModelName("bkgModel"), m_dplusMassDplusYieldName("ndplus"),
    m_dplusMassDsYieldName("nds"), m_dplusMassBkgYieldName("nbkg"),
    m_spectSetName("Spectators"), m_catSetName("Categories"),
    m_printEntries(kFALSE), m_printFreq(100), m_varNameToBranchName(),
    m_catNameToBranchName(), m_varNameToFunction(), m_varNameToFormula()
{
}

const char* RooDplusMassFitter::GetPartName(RooDplusMassFitter::PartType pType) const
{
  if (pType==RooDplusMassFitter::UndefinedPart) return "Undefined particle";
  else if (pType==RooDplusMassFitter::Dplus) return "Dplus";
  else if (pType==RooDplusMassFitter::Ds) return "Ds";
  else return "Unknown particle";
}

Bool_t RooDplusMassFitter::ValidPartName(RooDplusMassFitter::PartType pType) const
{
  if (pType==RooDplusMassFitter::Dplus) return kTRUE;
  else if (pType==RooDplusMassFitter::Ds) return kTRUE;
  else return kFALSE;
}

void RooDplusMassFitter::MakeDplusMassVar(Float_t xmin, Float_t xmax, 
                                          const char* unit, const char* title) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassVar",
                           "No RooWorkspace object is defined.");
  }
  if (!m_dplusMassName||strcmp(m_dplusMassName,"")==0) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassVar",
                           "No D+ mass variable name specified.");
  }
  RooRealVar mass(m_dplusMassName,(!title)?"":title,xmin,xmax,
                  (!unit)?"MeV/c^{2}":unit);
  if (m_rws->import(mass)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassVar",
      *m_rws, mass);
  }
}

// Add a "spectator" variable (not used as a fit variable)
// Optionally, it can added to a named set in the workspace by 
// specifying "setName". If the branch name in the TTree, brName,
// is not specified, it is assumed that it has the same name as 
// the RooRealVar
void RooDplusMassFitter::AddSpectator(const char* name, Double_t xmin, 
                                      Double_t xmax,
                                      const char* brName, const char* unit,
                                      const char* title, const char* setName)
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::AddSpectator",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
                 (!unit)?"":unit);
  if (m_rws->import(var)) {
    throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, var);
  }
  if (brName&&strcmp(brName,"")!=0) {
    m_varNameToBranchName[name]=brName;
  }
  if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
    throw GeneralException("RooDplusMassFitter::AddSpectator",
                           "No spectator set name specified.");
  }
  if (m_rws->extendSet(m_spectSetName, name)) {
      throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            m_spectSetName, name);
  }
  if (setName&&strcmp(setName,"")!=0) {
    if (m_rws->extendSet(setName, name)) {
      throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            setName, name);
    }
  }
}

void RooDplusMassFitter::AddSpectator(const char *name, Double_t xmin,
                                      Double_t xmax, 
                                      RooDplusMassFitter::DoubleFun fun,
                                      const char *brName, const char *unit,
                                      const char *title, const char* setName) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::AddSpectator",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
                 (!unit)?"":unit);
  if (m_rws->import(var)) {
    throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, var);
  }
  if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
    throw GeneralException("RooDplusMassFitter::AddSpectator",
                           "No spectator set name specified.");
  }
  if (m_rws->extendSet(m_spectSetName, name)) {
      throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            m_spectSetName, name);
  }
  if (brName&&strcmp(brName,"")!=0) {
    m_varNameToBranchName[name]=brName;
  }
  m_varNameToFunction[name]=fun;
  if (setName&&strcmp(setName,"")!=0) {
    if (m_rws->extendSet(setName, name)) {
      throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            setName, name);
    }
  }
}

void RooDplusMassFitter::AddSpectator(const char *name, Double_t xmin,
                                      Double_t xmax, 
                                      TFormula& fun,
                                      const char *brName, const char *unit,
                                      const char *title, const char* setName) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::AddSpectator",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar var(name,((!title)||(strcmp(title,"")==0))?"":title,xmin,xmax,
                 (!unit)?"":unit);
  if (m_rws->import(var)) {
    throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, var);
  }
  if (!m_spectSetName||strcmp(m_spectSetName,"")==0) {
    throw GeneralException("RooDplusMassFitter::AddSpectator",
                           "No spectator set name specified.");
  }
  if (fun.GetNdim()!=1) {
    std::stringstream msg;
    msg << "Expected one dimension for TFormula " << fun.GetName()
        << ", got " << fun.GetNdim();
    throw GeneralException("RooDplusMassFitter::AddSpectator",msg.str());
  }
   if (fun.GetNpar()!=0) {
    std::stringstream msg;
    msg << "Expected zero parameters for TFormula " << fun.GetName()
        << ", got " << fun.GetNpar();
    throw GeneralException("RooDplusMassFitter::AddSpectator",msg.str());
  }
  if (m_rws->extendSet(m_spectSetName, name)) {
      throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            m_spectSetName, name);
  }
  if (brName&&strcmp(brName,"")!=0) {
    m_varNameToBranchName[name]=brName;
  }
  m_varNameToFormula[name]=fun;
  if (setName&&strcmp(setName,"")!=0) {
    if (m_rws->extendSet(setName, name)) {
      throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            setName, name);
    }
  }
}

void RooDplusMassFitter::AddCategory(const char* name,
                                     std::vector<std::string> types,
                                     std::vector<Int_t> indices,
                                     const char* brName,
                                     const char* title) {
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::AddCategory",
                           "No RooWorkspace object is defined.");
  }
  if (types.size()==0) {
    throw GeneralException("RooDplusMassFitter::AddCategory",
                           "No category types have been specified.");
  }
  
  if (indices.size()!=types.size()) {
    std::stringstream msg;
    msg << "Number of category types " << types.size()
        << " does not match number of indices " << indices.size();
    throw GeneralException("RooDplusMassFitter::AddCategory", msg.str());
  }
  
  RooCategory cat(name, ((!title)||(strcmp(title,"")==0))?"":title);
  for (UInt_t i=0; i<types.size(); ++i) {
    std::string type = types[i];
    Int_t index = indices[i];
    if (cat.defineType(type.c_str(), index)) {
      std::stringstream msg;
      msg << "Failed to add category type " << type << " to RooCategory "
          << name;
      throw GeneralException("RooDplusMassFitter::AddCategory", msg.str());
    }
  }
  if (m_rws->import(cat)) {
    throw WSImportFailure("RooDplusMassFitter::AddCategory", *m_rws, cat);
  }
  if (!m_catSetName||strcmp(m_catSetName,"")==0) {
    throw GeneralException("RooDplusMassFitter::AddCategory",
                           "No category set name specified.");
                           }
  if (m_rws->extendSet(m_catSetName, name)) {
  throw WSImportFailure("RooDplusMassFitter::AddSpectator", *m_rws, 
                            m_catSetName, name);
  }
  if (brName&&strcmp(brName,"")!=0) {
    m_catNameToBranchName[name]=brName;
  }
}

void RooDplusMassFitter::AddCategory(const char* name,
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

void RooDplusMassFitter::MakeDplusMassSigGauss(RooDplusMassFitter::PartType pType,
                                               RooRealVar& mu, RooRealVar& sig) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigGauss",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigGauss",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigGauss",
                             *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooGaussian sigModel(this->GetDplusMassSigModelName(pType), "",
                       *mass, mu, sig);
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigGauss",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassSigGauss(RooDplusMassFitter::PartType pType,
                                               Float_t mu_start,
                                               Float_t mu_min,
                                               Float_t mu_max,
                                               Float_t sig_start,
                                               Float_t sig_min,
                                               Float_t sig_max,
                                               const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigGauss",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigGauss",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigGauss",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  const char* dplusMassPartName=this->GetDplusMassSigPartName(pType);
  
  if (!dplusMassPartName||strcmp(dplusMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
  }
  else {
    muTitle.Form("%s #mu", dplusMassPartName);
    sigTitle.Form("%s #sigma", dplusMassPartName);
  }

  const char* partLabel = this->GetDplusMassSigPartLabel(pType);
  TString muName=TString::Format("dplusmass_%s_mu", partLabel);
  TString sigName=TString::Format("dplusmass_%s_sigma", partLabel);;
  
  RooRealVar mu(muName.Data(), muTitle.Data(), mu_start, 
                mu_min, mu_max, unit);
  RooRealVar sig(sigName.Data(), sigTitle.Data(), sig_start, sig_min, 
                 sig_max, unit);
  RooGaussian sigModel(this->GetDplusMassSigModelName(pType), "",
                       *mass, mu, sig);
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigGauss",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassSigBiGauss(RooDplusMassFitter::PartType pType,
                                                 RooRealVar& mu, 
                                                 RooRealVar& sig0,
                                                 RooRealVar& sig1oSig0,
                                                 RooRealVar& coreFrac,
                                                 const char* sig1Name,
                                                 const char* sig1Title) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }

  const char* partLabel = this->GetDplusMassSigPartLabel(pType);
  TString g0Name=TString::Format("dplusmass_%s_gauss0", partLabel);
  TString g1Name=TString::Format("dplusmass_%s_gauss1", partLabel);

  RooGaussian mass_sig_g0(g0Name.Data(), "", *mass, mu, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(sig0.getUnit());
  
  RooGaussian mass_sig_g1(g1Name.Data(), "", *mass, mu, sig1);
  RooAddPdf sigModel(this->GetDplusMassSigModelName(pType), "",
                     RooArgList(mass_sig_g0,mass_sig_g1),
                     RooArgList(coreFrac));
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassSigBiGauss(RooDplusMassFitter::PartType pType,
                                                 Float_t mu_start, 
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
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  
  TString muTitle="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString coreFracTitle="";
  const char* dplusMassPartName=this->GetDplusMassSigPartName(pType);
  if (!dplusMassPartName||strcmp(dplusMassPartName,"")==0) {
    muTitle="#mu";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
    sig1Title="#sigma_{tail}";
    coreFracTitle="f_{core}";
  }
  else {
    muTitle.Form("%s #mu", dplusMassPartName);
    sig0Title.Form("%s #sigma_{core}", dplusMassPartName);
    sig1Title.Form("%s #sigma_{tail}", dplusMassPartName);
    sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", dplusMassPartName);
    coreFracTitle.Form("%s f_{core}", dplusMassPartName);
  }
   
  const char* partLabel = this->GetDplusMassSigPartLabel(pType);

  TString muName=TString::Format("dplusmass_%s_mu", partLabel);
  TString sig0Name=TString::Format("dplusmass_%s_sigma0", partLabel);
  TString sig1Name=TString::Format("dplusmass_%s_sigma1", partLabel);
  TString s1oS0Name=TString::Format("dplusmass_%s_s1oS0", partLabel);
  TString g0Name=TString::Format("dplusmass_%s_gauss0", partLabel);
  TString g1Name=TString::Format("dplusmass_%s_gauss1", partLabel);
  TString coreFracName=TString::Format("dplusmass_%s_coreFrac", partLabel);

  RooRealVar mu(muName.Data(), muTitle.Data(), mu_start,
                mu_min, mu_max, unit);
  RooRealVar sig0(sig0Name.Data(), sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian mass_sig_g0(g0Name.Data(), "", *mass, mu, sig0);

  RooRealVar sig1oSig0(s1oS0Name.Data(), sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
  
  RooFormulaVar sig1(sig1Name.Data(), sig1Title.Data(), "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);
  
  RooGaussian mass_sig_g1(g1Name.Data(), "", *mass, mu, sig1);

  RooRealVar coreFrac(coreFracName.Data(), coreFracTitle.Data(),
                      coreFrac_start,0.0,1);
  
  RooAddPdf sigModel(this->GetDplusMassSigModelName(pType), "", 
                     RooArgList(mass_sig_g0,mass_sig_g1),
                     RooArgList(coreFrac));
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassSigBiGauss(RooDplusMassFitter::PartType pType,
                                                 RooRealVar& mu0, 
                                                 RooRealVar& mu1,
                                                 RooRealVar& sig0,
                                                 RooRealVar& sig1oSig0,
                                                 RooRealVar& coreFrac,
                                                 const char* sig1Name,
                                                 const char* sig1Title) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }

  const char* partLabel = this->GetDplusMassSigPartLabel(pType);

  TString g0Name=TString::Format("dplusmass_%s_gauss0", partLabel);
  TString g1Name=TString::Format("dplusmass_%s_gauss1", partLabel);

  RooGaussian mass_sig_g0(g0Name.Data(), "", *mass, mu0, sig0);
  RooFormulaVar sig1(sig1Name, sig1Title, "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(sig0.getUnit());
  
  RooGaussian mass_sig_g1(g0Name.Data(), "", *mass, mu1, sig1);
  
  RooAddPdf sigModel(this->GetDplusMassSigModelName(pType), "",
                     RooArgList(mass_sig_g0,mass_sig_g1),
                     RooArgList(coreFrac));
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassSigBiGauss(RooDplusMassFitter::PartType pType,
                                                 Float_t mu0_start,
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
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                             *m_rws, m_dplusMassName, "RooRealVar");
  }
  //   if (coreFrac_start<0.5) {
  //     throw GeneralException("RooDplusMassFitter::MakeDplusMassSigBiGauss",
  //                            "Core fraction cannot be less than 50%");
  //   }
  TString mu0Title="";
  TString mu1Title="";
  TString sig0Title="";
  TString sig1oSig0Title="";
  TString sig1Title="";
  TString coreFracTitle="";
  const char* dplusMassPartName=this->GetDplusMassSigPartName(pType);
  if (!dplusMassPartName||strcmp(dplusMassPartName,"")==0) {
    mu0Title="#mu_{core}";
    mu1Title="#mu_{tail}";
    sig0Title="#sigma_{core}";
    sig1oSig0Title="#sigma_{tail}/#sigma_{core}";
    sig1Title="#sigma_{tail}";
    coreFracTitle="f_{core}";
  }
  else {
    mu0Title.Form("%s #mu_{core}", dplusMassPartName);
    mu1Title.Form("%s #mu_{tail}", dplusMassPartName);
    sig0Title.Form("%s #sigma_{core}", dplusMassPartName);
    sig1Title.Form("%s #sigma_{tail}", dplusMassPartName);
    sig1oSig0Title.Form("%s #sigma_{tail}/#sigma_{core}", dplusMassPartName);
    coreFracTitle.Form("%s f_{core}", dplusMassPartName);
  }

  const char* partLabel = this->GetDplusMassSigPartLabel(pType);

  TString mu0Name=TString::Format("dplusmass_%s_mu0", partLabel);
  TString sig0Name=TString::Format("dplusmass_%s_sigma0", partLabel);
  TString g0Name=TString::Format("dplusmass_%s_gauss0", partLabel);

  TString mu1Name=TString::Format("dplusmass_%s_mu1", partLabel);
  TString sig1Name=TString::Format("dplusmass_%s_sigma1", partLabel);
  TString g1Name=TString::Format("dplusmass_%s_gauss1", partLabel);

  TString s1oS0Name=TString::Format("dplusmass_%s_s1oS0", partLabel);
  TString coreFracName=TString::Format("dplusmass_%s_coreFrac", partLabel);

  RooRealVar mu0(mu0Name.Data(), mu0Title.Data(),
                 mu0_start, mu0_min, mu0_max, unit);
  RooRealVar sig0(sig0Name.Data(), sig0Title.Data(),
                  sig0_start, sig0_min, sig0_max, unit);
  RooGaussian mass_sig_g0(g0Name.Data(), "", *mass, mu0, sig0);

  RooRealVar sig1oSig0(s1oS0Name.Data(), sig1oSig0Title.Data(),
                       sig1oSig0_start, sig1oSig0_min, sig1oSig0_max);
  RooRealVar mu1(mu1Name.Data(), mu1Title.Data(),
                 mu1_start, mu1_min, mu1_max, unit);  
  RooFormulaVar sig1(sig1Name.Data(), sig1Title.Data(), "@0*@1", 
                     RooArgList(sig1oSig0,sig0));
  sig1.setUnit(unit);
  
  RooGaussian mass_sig_g1(g1Name.Data(), "", *mass, mu1, sig1);

  RooRealVar coreFrac(coreFracName.Data(), coreFracTitle.Data(),
                      coreFrac_start,0.0,1);
  
  RooAddPdf sigModel(this->GetDplusMassSigModelName(pType), "", 
                     RooArgList(mass_sig_g0,mass_sig_g1),
                     RooArgList(coreFrac));
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigBiGauss",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassSigCruijff(RooDplusMassFitter::PartType pType,
                                                 RooRealVar& mu, 
                                                 RooRealVar& sigL,
                                                 RooRealVar& sigR,
                                                 RooRealVar& alphaL,
                                                 RooRealVar& alphaR) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooCruijff sigModel(this->GetDplusMassSigModelName(pType), "",
                      *mass, mu, sigL, sigR, alphaL, alphaR);
  
  //  if (m_rws->importClassCode(RooCruijff::Class(),kTRUE)) {
  //     throw WSImportCodeFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
  //                                    *m_rws, "RooCruijff");
  //   }
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                          *m_rws, sigModel);
  }
  //m_rws->importClassCode();
}


void RooDplusMassFitter::MakeDplusMassSigCruijff(RooDplusMassFitter::PartType pType,
                                                 Float_t mu_start, 
                                                 Float_t mu_min,
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
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                             *m_rws, m_dplusMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigLTitle="";
  TString alphaLTitle="";
  TString sigRTitle="";
  TString alphaRTitle="";
  const char* dplusMassPartName=this->GetDplusMassSigPartName(pType);
  if (!dplusMassPartName||strcmp(dplusMassPartName,"")==0) {
    muTitle="#mu";
    sigLTitle="#sigma_{L}";
    alphaLTitle="#alpha_{L}";
    sigRTitle="#sigma_{R}";
    alphaRTitle="#alpha_{R}";
  }
  else {
    muTitle.Form("%s #mu", dplusMassPartName);
    sigLTitle.Form("%s #sigma_{L}", dplusMassPartName);
    alphaLTitle.Form("%s #alpha_{L}", dplusMassPartName);
    sigRTitle.Form("%s #sigma_{R}", dplusMassPartName);
    alphaRTitle.Form("%s #alpha_{R}", dplusMassPartName);
  }

  const char* partLabel = this->GetDplusMassSigPartLabel(pType);

  TString muName=TString::Format("dplusmass_%s_mu", partLabel);
  TString sigLName=TString::Format("dplusmass_%s_sigmaL", partLabel);
  TString sigRName=TString::Format("dplusmass_%s_sigmaR", partLabel);
  TString alphaLName=TString::Format("dplusmass_%s_alphaL", partLabel);
  TString alphaRName=TString::Format("dplusmass_%s_alphaR", partLabel);

  RooRealVar mu(muName.Data(), muTitle.Data(), mu_start, 
                mu_min, mu_max, unit);
  RooRealVar sigL(sigLName.Data(), sigLTitle.Data(), 
                  sigL_start, sigL_min, sigL_max, unit);
  RooRealVar alphaL(alphaLName.Data(), alphaLTitle.Data(), 
                    alphaL_start, alphaL_min, alphaL_max);
  RooRealVar sigR(sigRName.Data(), sigRTitle.Data(), 
                  sigR_start, sigR_min, sigR_max, unit);
  RooRealVar alphaR(alphaRName.Data(), alphaRTitle.Data(), 
                    alphaR_start, alphaR_min, alphaR_max);

  RooCruijff sigModel(this->GetDplusMassSigModelName(pType), "", 
                      *mass, mu, sigL, sigR, alphaL, alphaR);
  //   if (m_rws->importClassCode(RooCruijff::Class(),kTRUE)) {
  //     throw WSImportCodeFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
  //                                    *m_rws, "RooCruijff");
  //   }
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                          *m_rws, sigModel);
  }
  //m_rws->importClassCode();
}

void RooDplusMassFitter::MakeDplusMassSigCruijff(RooDplusMassFitter::PartType pType,
                                                 RooRealVar& mu,
                                                 RooRealVar& sig,
                                                 RooRealVar& alphaL,
                                                 RooRealVar& alphaR) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooCruijffSimple sigModel(this->GetDplusMassSigModelName(pType), "",
                            *mass, mu, sig, alphaL, alphaR);
  //  if (m_rws->importClassCode(RooCruijffSimple::Class(),kTRUE)) {
  //     throw WSImportCodeFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
  //                                    *m_rws, "RooCruijffSimple");
  //   }
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                          *m_rws, sigModel);
  }
  //m_rws->importClassCode();
}

void RooDplusMassFitter::MakeDplusMassSigCruijff(RooDplusMassFitter::PartType pType,
                                                 Float_t mu_start, 
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
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCruijff",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                             *m_rws, m_dplusMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString alphaLTitle="";
  TString alphaRTitle="";
  const char* dplusMassPartName=this->GetDplusMassSigPartName(pType);
  if (!dplusMassPartName||strcmp(dplusMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    alphaLTitle="#alpha_{L}";
    alphaRTitle="#alpha_{R}";
  }
  else {
    muTitle.Form("%s #mu", dplusMassPartName);
    sigTitle.Form("%s #sigma", dplusMassPartName);
    alphaLTitle.Form("%s #alpha_{L}", dplusMassPartName);
    alphaRTitle.Form("%s #alpha_{R}", dplusMassPartName);
  }

  const char* partLabel = this->GetDplusMassSigPartLabel(pType);

  TString muName=TString::Format("dplusmass_%s_mu", partLabel);
  TString sigName=TString::Format("dplusmass_%s_sigma", partLabel);
  TString alphaLName=TString::Format("dplusmass_%s_alphaL", partLabel);
  TString alphaRName=TString::Format("dplusmass_%s_alphaR", partLabel);

  RooRealVar mu(muName.Data(), muTitle.Data(), mu_start,
                mu_min, mu_max, unit);
  RooRealVar sig(sigName.Data(), sigTitle.Data(), sig_start, sig_min, 
                 sig_max, unit);
  RooRealVar alphaL(alphaLName.Data(), alphaLTitle.Data(), alphaL_start,
                    alphaL_min, alphaL_max);
  RooRealVar alphaR(alphaRName.Data(), alphaRTitle.Data(), alphaR_start,
                    alphaR_min, alphaR_max);

  RooCruijffSimple sigModel(this->GetDplusMassSigModelName(pType), "",
                            *mass, mu, sig, alphaL, alphaR);
  //   if (m_rws->importClassCode(RooCruijffSimple::Class(),kTRUE)) {
  //     throw WSImportCodeFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
  //                                    *m_rws, "RooCruijffSimple");
  //   }
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigCruijff",
                          *m_rws, sigModel);
  }
  //m_rws->importClassCode();
}

void RooDplusMassFitter::MakeDplusMassSigCB(RooDplusMassFitter::PartType pType,
                                            RooRealVar& mu, RooRealVar& sig,
                                            RooRealVar& alpha, RooRealVar& n) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCB",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCB",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigCB",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooCBShape sigModel(this->GetDplusMassSigModelName(pType), "", 
                      *mass, mu, sig, alpha, n);
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigCB",
                          *m_rws, sigModel);
  }
}


void RooDplusMassFitter::MakeDplusMassSigCB(RooDplusMassFitter::PartType pType,
                                            Float_t mu_start, Float_t mu_min,
                                            Float_t mu_max, Float_t sig_start,
                                            Float_t sig_min, Float_t sig_max,
                                            Float_t alpha_start, 
                                            Float_t alpha_min,
                                            Float_t alpha_max, Float_t n_start,
                                            Float_t n_min, Float_t n_max,
                                            const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCB",
                           "No RooWorkspace object is defined.");
  }
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::MakeDplusMassSigCB",
                           msg.str());
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassSigCB",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  TString muTitle="";
  TString sigTitle="";
  TString alphaTitle="";
  TString nTitle="";
  const char* dplusMassPartName=this->GetDplusMassSigPartName(pType);
  if (!dplusMassPartName||strcmp(dplusMassPartName,"")==0) {
    muTitle="#mu";
    sigTitle="#sigma";
    alphaTitle="#alpha";
    nTitle="n";
  }
  else {
    muTitle.Form("%s #mu", dplusMassPartName);
    sigTitle.Form("%s #sigma", dplusMassPartName);
    alphaTitle.Form("%s #alpha", dplusMassPartName);
    nTitle.Form("%s n", dplusMassPartName);
  }
  
  const char* partLabel = this->GetDplusMassSigPartLabel(pType);

  TString muName=TString::Format("dplusmass_%s_mu", partLabel);
  TString sigName=TString::Format("dplusmass_%s_sigma", partLabel);
  TString alphaName=TString::Format("dplusmass_%s_alpha", partLabel);
  TString nName=TString::Format("dplusmass_%s_n", partLabel);

  RooRealVar mu(muName.Data(), muTitle.Data(), mu_start,
                mu_min, mu_max, unit);
  RooRealVar sig(sigName.Data(), sigTitle.Data(), sig_start, sig_min, 
                 sig_max, unit);
  RooRealVar alpha(alphaName.Data(), alphaTitle.Data(), alpha_start,
                   alpha_min, alpha_max);
  RooRealVar n(nName.Data(), nTitle.Data(), n_start, n_min, n_max);

  RooCBShape sigModel(this->GetDplusMassSigModelName(pType), "", 
                      *mass, mu, sig, alpha, n);
  if (m_rws->import(sigModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassSigCB",
                          *m_rws, sigModel);
  }
}

void RooDplusMassFitter::MakeDplusMassBkgFlat(RooRealVar& grad) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassBkgFlat",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter:MakeDplusMassBkgFlat",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooChebychev bkgModel(m_dplusMassBkgModelName,"",
                        *mass,RooArgList(grad));
  if (m_rws->import(bkgModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassBkgFlat",
                          *m_rws, bkgModel);
  }
}

void RooDplusMassFitter::MakeDplusMassBkgFlat(Float_t grad_start, 
                                              Float_t grad_min,
                                              Float_t grad_max,
                                              const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassBkgFlat",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter:MakeDplusMassBkgFlat",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }
  TString gradTitle="";
  if (!m_dplusMassBkgPartName||strcmp(m_dplusMassBkgPartName,"")==0) {
    gradTitle="#nabla";
  }
  else {
    gradTitle.Form("%s #nabla", m_dplusMassBkgPartName);
  }  

  RooRealVar grad("dplusmass_bkg_poly_c1", gradTitle.Data(), 
                  grad_start, grad_min, grad_max, invMassUnit);
  RooChebychev bkgModel(m_dplusMassBkgModelName,"",*mass,RooArgList(grad));
  if (m_rws->import(bkgModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassBkgFlat",
                          *m_rws, bkgModel);
  }
}

void RooDplusMassFitter::MakeDplusMassBkgQuadratic(RooRealVar& c1,
                                                   RooRealVar& c2) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassBkgQuadratic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter:MakeDplusMassBkgQuadratic",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooChebychev bkgModel(m_dplusMassBkgModelName, "",
                        *mass, RooArgList(c1,c2));
  if (m_rws->import(bkgModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassBkgQuadratic",
                          *m_rws, bkgModel);
  }
}

void RooDplusMassFitter::MakeDplusMassBkgQuadratic(Float_t c1_start,
                                                   Float_t c1_min,
                                                   Float_t c1_max, 
                                                   Float_t c2_start,
                                                   Float_t c2_min, 
                                                   Float_t c2_max,
                                                   const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassBkgQuadratic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter:MakeDplusMassBkgQuadratic",
                             *m_rws, m_dplusMassName, "RooRealVar");
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
  if (!m_dplusMassBkgPartName||strcmp(m_dplusMassBkgPartName,"")==0) {
    c1Title="c_{1}";
    c2Title="c_{2}";
  }
  else {
    c1Title.Form("%s c_{1}", m_dplusMassBkgPartName);
    c2Title.Form("%s c_{2}", m_dplusMassBkgPartName);
  }
  
  RooRealVar c1("dplusmass_bkg_poly_c1", c1Title.Data(), c1_start, c1_min,
                c1_max, invMassUnit.Data());
  RooRealVar c2("dplusmass_bkg_poly_c2", c2Title.Data(), c2_start, c2_min,
                c2_max, invMass2Unit.Data());
  RooChebychev bkgModel(m_dplusMassBkgModelName,"",*mass,RooArgList(c1,c2));
  if (m_rws->import(bkgModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassBkgQuadratic",
                          *m_rws, bkgModel);
  }
}

void RooDplusMassFitter::MakeDplusMassBkgCubic(RooRealVar& c1,
                                               RooRealVar& c2,
                                               RooRealVar& c3) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassBkgCubic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter:MakeDplusMassBkgCubic",
                           *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooChebychev bkgModel(m_dplusMassBkgModelName,"",
                        *mass,RooArgList(c1,c2,c3));
  if (m_rws->import(bkgModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassBkgCubic",
                          *m_rws, bkgModel);
  }
}

void RooDplusMassFitter::MakeDplusMassBkgCubic(Float_t c1_start,
                                               Float_t c1_min,
                                               Float_t c1_max, 
                                               Float_t c2_start,
                                               Float_t c2_min, 
                                               Float_t c2_max,
                                               Float_t c3_start, 
                                               Float_t c3_min,
                                               Float_t c3_max, 
                                               const char* unit) 
{
  if (!m_rws) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassBkgCubic",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter:MakeDplusMassBkgCubic",
                             *m_rws, m_dplusMassName, "RooRealVar");
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
  if (!m_dplusMassBkgPartName||strcmp(m_dplusMassBkgPartName,"")==0) {
    c1Title="c_{1}";
    c2Title="c_{2}";
    c3Title="c_{3}";
  }
  else {
    c1Title.Form("%s c_{1}", m_dplusMassBkgPartName);
    c2Title.Form("%s c_{2}", m_dplusMassBkgPartName);
    c3Title.Form("%s c_{3}", m_dplusMassBkgPartName);
  }
  
  RooRealVar c1("dplusmass_bkg_poly_c1", c1Title.Data(), c1_start, c1_min,
                c1_max, invMassUnit.Data());
  RooRealVar c2("dplusmass_bkg_poly_c2", c2Title.Data(), c2_start, c2_min,
                c2_max, invMass2Unit.Data());
  RooRealVar c3("dplusmass_bkg_poly_c3", c3Title.Data(), c3_start, c3_min,
                c3_max, invMass2Unit.Data());
  RooChebychev bkgModel(m_dplusMassBkgModelName,"",
                        *mass,RooArgList(c1,c2,c3));
  if (m_rws->import(bkgModel)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassBkgCubic",
                          *m_rws, bkgModel);
  }
}

// make 1D D+ model - specify expected fraction of each background type
// NB. No check that sum(frac)==1
void RooDplusMassFitter::MakeDplusMassModel(Float_t frac_dplus, 
                                            Float_t frac_ds,
                                            Float_t frac_bkg)

{
  if (frac_dplus<0&&frac_ds<0&&frac_bkg<0) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassModel",
       "Fit fractions are less than zero. At least one fraction must be >0");
    
  }
  if (frac_dplus>1) {
    std::stringstream msg;
    msg << "D+ fit fraction is greater than unity (" << frac_dplus << ")";
    throw GeneralException("RooDplusMassFitter::MakeDplusMassModel", 
                           msg.str());
  }
  if (frac_ds>1) {
    std::stringstream msg;
    msg << "D+ fit fraction is greater than unity (" << frac_ds << ")";
    throw GeneralException("RooDplusMassFitter::MakeDplusMassModel", 
                           msg.str());
  }
  if (frac_bkg>1) {
    std::stringstream msg;
    msg << "Combinatoric background fit fraction is greater than unity ("
        << frac_bkg << ")";
    throw GeneralException("RooDplusMassFitter::MakeDplusMassModel", msg.str());
  }
  if (!m_rws)
  {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassModel",
                           "No RooWorkspace object is defined!");
  }
  RooDataSet* rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassModel",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassModel",
                             *m_rws, m_dplusMassName, "RooRealVar");
  }
  RooAbsPdf* dplusModel=m_rws->pdf(m_dplusMassDplusModelName);
  if (!dplusModel&&frac_dplus>=0) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassModel",
                             *m_rws,m_dplusMassDplusModelName,"RooAbsPdf");
  }
  RooAbsPdf* dsModel=m_rws->pdf(m_dplusMassDsModelName);
  if (!dplusModel&&frac_ds>=0) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassModel",
                             *m_rws,m_dplusMassDsModelName,"RooAbsPdf");
  }
  RooAbsPdf* bkgModel=m_rws->pdf(m_dplusMassBkgModelName);
  if (!bkgModel&&frac_bkg>=0) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassModel",
                             *m_rws,m_dplusMassBkgModelName,"RooAbsPdf");
  }
  Int_t nentries = rds->numEntries();
  if (nentries<=0) {
    std::stringstream msg;
    msg << "Got invalid number of entries " << nentries
        << " from RooDataSet " << m_dataSetName;
    throw GeneralException("RooDplusMassFitter::MakeDplusMassModel",
                           msg.str());
  }
  Int_t ndplus_est = static_cast<Int_t>(frac_dplus*nentries);
  Int_t nds_est = static_cast<Int_t>(frac_ds*nentries);
  Int_t nbkg_est = static_cast<Int_t>(frac_bkg*nentries);
  
  RooRealVar ndplus(m_dplusMassDplusYieldName,
                    "N_{D+ sig.}", ndplus_est, 0, nentries);
  RooRealVar nds(m_dplusMassDsYieldName,
                 "N_{Ds sig.}", nds_est, 0, nentries);
  RooRealVar nbkg(m_dplusMassBkgYieldName, "N_{bkg.}", nbkg_est, 0, nentries);
  RooArgList yieldList;//(nsig, nbkg);
  RooArgList pdfList;//(*sigModel, *bkgModel);

  if (frac_dplus>=0) {
    pdfList.add(*dplusModel);
    yieldList.add(ndplus);
  }
  if (frac_ds>=0) {
    pdfList.add(*dsModel);
    yieldList.add(nds);
  }
  if (frac_bkg>=0) {
    pdfList.add(*bkgModel);
    yieldList.add(nbkg);
  }
  assert(pdfList.getSize()!=0);
  assert(yieldList.getSize()!=0);

  RooAddPdf model(m_modelName, "", pdfList, yieldList);
  
  if (m_rws->import(model)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassModel",
                          *m_rws, model);
  }
}

void RooDplusMassFitter::MakeDplusMassDataSet(TTree* tt, 
                                              const char* dplusMassVarname,
                                              const char* name,
                                              const char* title,
                                              const char* cuts) 
{
  if (!m_rws)
  {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                           "No RooWorkspace object is defined.");
  }
  if (!tt) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
           "Expected pointer to TTree as argument, got NULL pointer.");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooDplusMassFitter::MakeDplusMassDataSet",
                             *m_rws, m_dplusMassName, "RooRealVar");
  }
  if (!dplusMassVarname||strcmp(dplusMassVarname,"")==0) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                           "No D mass branch name specified.");
  }
  if (!name||strcmp(name,"")==0) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                           "No RooDataSet name specified.");
  }
  Long64_t nTotal = tt->GetEntries();
  if (nTotal==0) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
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
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                             msg.str());
    }
    tt->SetEntryList(elist);
  }
  
  // TTree* ttReduced = tt->CopyTree(cuts);
  Long64_t nentries = !elist?tt->GetEntries():elist->GetN();
  if (nentries==0) {
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                           "No entries in TTree after cuts.");
  }
  
  Float_t M_f=0;
  Double_t M=0;
  // if this is a TChain, then we need to use the daughter's method
  tt->SetBranchStatus("*", 1);

  TChain* ch=0;
  ch=dynamic_cast<TChain*>(tt);
  std::string masstype=ch?GetBranchType(ch, dplusMassVarname):GetBranchType(tt, dplusMassVarname);
  if (!ch) {
    if (masstype.compare("Float_t")==0) { 
      tt->SetBranchAddress(dplusMassVarname, &M_f);
    }
    else if (masstype.compare("Double_t")==0) {
      tt->SetBranchAddress(dplusMassVarname, &M);
    }
    else {
      std::stringstream msg;
      msg << "Got unexpected type " << masstype << " for variable " 
          << dplusMassVarname;
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", msg.str());
    }
  }
  else {
    if (masstype.compare("Float_t")==0) { 
      ch->SetBranchAddress(dplusMassVarname, &M_f);
    }
    else if (masstype.compare("Double_t")==0) {
      ch->SetBranchAddress(dplusMassVarname, &M);
    }
    else {
      std::stringstream msg;
      msg << "Got unexpected type " << masstype << " for variable " 
          << dplusMassVarname;
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", msg.str());
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
        throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", 
                               msg.str());
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
        throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                               msg.str());
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
        throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", msg.str());
      }
      std::string branchName=this->GetCatBranchName(catName);
      std::string type=GetBranchType(tt, branchName);
      if ( !(type.compare("Int_t")==0 || type.compare("Bool_t")==0 || type.compare("UInt_t")==0) ) {
        std::stringstream msg;
        msg << "Requested branch name " << branchName << " is of type "
            << type << ", but categories can only be of type Int_t, UInt_t or Bool_t";
        throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", msg.str());
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
  
  std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Initial entries = "
            << nTotal << std::endl;
  if (cuts&&strlen(cuts)>0) {
    std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Entries passing selection cut (" 
              << cuts << ") = " << nentries << std::endl;
  }

  for (entry=0; entry<nentries; ++entry)
  {
    entryNumber=tt->GetEntryNumber(entry);
    if (entryNumber<0) {
      std::stringstream msg;
      msg << "Got invalid entry number " << entryNumber;
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", 
                             msg.str());
    }
    if (ch) {
      localEntry = ch->LoadTree(entryNumber);
      if (localEntry<0) {
        std::stringstream msg;
        msg << "Got invalid entry number in current tree " << localEntry;
        throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                               msg.str());
      }
    }
    
    Int_t nb;
    nb=tt->GetEntry(entryNumber);
    if (nb<=0) {
      std::stringstream msg;
      msg << "Got invalid number of bytes " << nb 
          << " for entry " << entry;
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", 
                             msg.str());
    }
  
    if (masstype.compare("Float_t")==0) M=static_cast<Double_t>(M_f);

    Bool_t printEntry=m_printEntries&&(entry%m_printFreq==0);
    if (printEntry) {
      std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Entry " << entry
                << ", entry number " << entryNumber 
                << ", entry in current tree " << localEntry
                << std::endl;
      std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: D mass = " << M
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
            throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                                   msg.str());
          }
          if (!args.find(vname.c_str())) {
            std::stringstream msg;
            msg << "Unable to find variable name " << vname << " in RooArgSet";
            throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                                   msg.str());
          }
          if (printEntry) {
            std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Variable "
                      << vname << ", value = " << v << std::endl;
          }
          RooRealVar *var=dynamic_cast<RooRealVar*>(&args[vname.c_str()]);
          if (!var) {
            std::stringstream msg;
            msg << "Unable to cast RooAbsArg " << vname << " to a RooRealVar";
            throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
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
                std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Variable "
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
                std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Variable "
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
                std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Variable "
                          << vname<< ", value = " << v << " is not in range ("
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
          void *val=(it->second);
          assert(val!=NULL);
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
            throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                                   msg.str());
          }
          
          RooCategory *cat=dynamic_cast<RooCategory*>(&args[vname.c_str()]);
          if (!cat) {
            std::stringstream msg;
            msg << "Unable to cast RooAbsArg " << vname << " to a RooCategory";
            throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                                   msg.str());
          }
          if (!cat->isValidIndex(v)) {
            passed=kFALSE;
            if (printEntry) {
              std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Category " << vname
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
    throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet",
                           "No entries selected!");
  }

  std::cout << "RooDplusMassFitter::MakeDplusMassDataSet: Selected entries = " 
            << rds->numEntries() << std::endl;

  if (m_rws->import(*rds)) {
    throw WSImportFailure("RooDplusMassFitter::MakeDplusMassDataSet", *m_rws, *rds);
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
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", 
                             msg.str());
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
      throw GeneralException("RooDplusMassFitter::MakeDplusMassDataSet", msg.str());
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
void RooDplusMassFitter::PerformDplusMassBinnedFit(Int_t nBins,
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
    throw GeneralException("RooDplusMassFitter::PerformDplusMassBinnedFit",
                           "No RooWorkspace object is defined");
  }
  RooRealVar* mass = m_rws->var(m_dplusMassName);
  if (!mass)
  {
    throw WSRetrievalFailure("RooDplusMassFitter::PerformDplusMassBinnedFit"
                             ,*m_rws, m_dplusMassName, "RooRealVar");
  }
  Int_t oldBins = mass->getBins();
  mass->setBins(nBins);
  this->PerformBinnedFit(fitName,nCores,saveSnapshot,printResults,
                         useSumW2Errors,extendedMode, useChi2Method);
  mass->setBins(oldBins);
}

void RooDplusMassFitter::SetDplusMassSigPartName(RooDplusMassFitter::PartType pType,
                                              const char* name)
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigPartName",
                           msg.str());
  }
  if (pType==RooDplusMassFitter::Dplus) m_dplusMassDplusPartName=name;
  else  m_dplusMassDsPartName=name;
}

void RooDplusMassFitter::SetDplusMassBkgPartName(const char* name)
{
  m_dplusMassBkgPartName=name;
}


void RooDplusMassFitter::SetDplusMassName(const char* name) {
  m_dplusMassName=name;
}

void RooDplusMassFitter::SetDplusMassSigModelName(RooDplusMassFitter::PartType pType,
                                                  const char* name)
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigModelName",
                           msg.str());
  }
  if (pType==RooDplusMassFitter::Dplus) m_dplusMassDplusModelName=name;
  else m_dplusMassDsModelName=name;
}

void RooDplusMassFitter::SetDplusMassBkgModelName(const char* name) 
{
  m_dplusMassBkgModelName=name;
}

void RooDplusMassFitter::SetDplusMassSigYieldName(RooDplusMassFitter::PartType pType,
                                                  const char* name)
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigYieldName",
                           msg.str());
  }
  if (pType==RooDplusMassFitter::Dplus) m_dplusMassDplusYieldName=name;
  else m_dplusMassDsYieldName=name;
}
void RooDplusMassFitter::SetDplusMassBkgYieldName(const char* name) 
{
  m_dplusMassBkgYieldName=name;
}

void RooDplusMassFitter::SetSpectatorSetName(const char* name) 
{
  m_spectSetName=name;
}

void RooDplusMassFitter::SetCategorySetName(const char* name)
{
  m_catSetName=name;
}

void RooDplusMassFitter::SetPrintEntriesFlag(Bool_t flag) {m_printEntries=flag;}

void RooDplusMassFitter::SetPrintFreq(Int_t freq) {m_printFreq=freq;}

const char* RooDplusMassFitter::GetDplusMassSigPartName(RooDplusMassFitter::PartType pType) const
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigPartName",
                           msg.str());
  }  
  if (pType==RooDplusMassFitter::Dplus) return m_dplusMassDplusPartName;
  else return m_dplusMassDsPartName;
}

const char* RooDplusMassFitter::GetDplusMassBkgPartName() const
{
  return m_dplusMassBkgPartName;
}

const char* RooDplusMassFitter::GetDplusMassName() const
{
  return m_dplusMassName;
}

const char* RooDplusMassFitter::GetDplusMassSigModelName(RooDplusMassFitter::PartType pType) const
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigModelName",
                           msg.str());
  }   
  if (pType==RooDplusMassFitter::Dplus) return m_dplusMassDplusModelName;
  else return m_dplusMassDsModelName;
}

const char* RooDplusMassFitter::GetDplusMassBkgModelName() const
{
  return m_dplusMassBkgModelName;
}

const char* RooDplusMassFitter::GetDplusMassSigYieldName(RooDplusMassFitter::PartType pType) const
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigYieldName",
                           msg.str());
  }
  if (pType==RooDplusMassFitter::Dplus) return m_dplusMassDplusYieldName;
  else return m_dplusMassDsYieldName;
}

const char* RooDplusMassFitter::GetDplusMassBkgYieldName() const
{
  return m_dplusMassBkgYieldName;
}

const char* RooDplusMassFitter::GetSpectatorSetName() const
{
  return m_spectSetName;
}

const char* RooDplusMassFitter::GetCategorySetName() const
{
  return m_catSetName;
}

const char* RooDplusMassFitter::GetDplusMassSigPartLabel(RooDplusMassFitter::PartType pType) const 
{
  if (!this->ValidPartName(pType)) {
    std::stringstream msg;
    msg << "Invalid particle type " << this->GetPartName(pType);
    throw GeneralException("RooDplusMassFitter::SetDplusMassSigYieldName",
                           msg.str());
  }
  if (pType==RooDplusMassFitter::Dplus) return "dplus";
  else return "ds";
}
const Bool_t& RooDplusMassFitter::GetPrintEntriesFlag() const {return m_printEntries;}

const Int_t& RooDplusMassFitter::GetPrintFreq() const {return m_printFreq;}


std::string RooDplusMassFitter::GetVarBranchName(const std::string& name) const
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

std::string RooDplusMassFitter::GetCatBranchName(const std::string& name) const
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


std::string RooDplusMassFitter::GetBranchType(TTree* tt, 
    const std::string& brName) const
{
  assert(tt);
  TChain* ch=dynamic_cast<TChain*>(tt);
  TBranch* br = ch==NULL?tt->GetBranch(brName.c_str()):ch->GetBranch(
    brName.c_str());
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
RooDplusMassFitter::~RooDplusMassFitter() {}
//=============================================================================
