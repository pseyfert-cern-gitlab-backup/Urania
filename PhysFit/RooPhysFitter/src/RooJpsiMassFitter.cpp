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
#include "RooPhysFitter/RooJpsiMassFitter.h"
#include "RooPhysFitter/Exceptions.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RooJpsiMassFitter
//
// 2014-02-27 : Thomas Bird
//-----------------------------------------------------------------------------

//using namespace RooPhysFit;
// This is a really bad idea, and should be fixed!
using namespace RooPhysFit;

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================



void RooJpsiMassFitter::MakeDMassSigBiCB(RooRealVar& mu, RooRealVar& sig_left,
                                  RooRealVar& sig_right, RooRealVar& alpha_left,
                                  RooRealVar& alpha_right, RooRealVar& n_left,
                                  RooRealVar& n_right, RooRealVar& frac_left)
{
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::MakeDMassSigBiCB",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooJpsiMassFitter::MakeDMassSigBiCB",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  TString neg_mass_formula = "";
  neg_mass_formula.Form("-%s",mass->GetName());

  RooFormulaVar neg_mass("neg_mass","",neg_mass_formula.Data(),*mass);
  RooFormulaVar neg_mu("neg_mu","","-dmass_sig_mu",mu);

  RooCBShape dmass_sig_cb_left("dmass_sig_cb_left", "", *mass, mu, sig_left, alpha_left, n_left);
  RooCBShape dmass_sig_cb_right("dmass_sig_cb_right", "", neg_mass, neg_mu, sig_right, alpha_right, n_right);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_cb_left,dmass_sig_cb_right),
                          RooArgList(frac_left));

  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooJpsiMassFitter::MakeDMassSigBiCB",
                          *m_rws, dMassSigModel);
  }
}

void RooJpsiMassFitter::MakeDMassSigBiCB(Float_t mu_start,
                                      Float_t mu_min,
                                      Float_t mu_max,
                                      Float_t sig_left_start,
                                      Float_t sig_left_min,
                                      Float_t sig_left_max,
                                      Float_t sig_right_start,
                                      Float_t sig_right_min,
                                      Float_t sig_right_max,
                                      Float_t alpha_left_start,
                                      Float_t alpha_left_min,
                                      Float_t alpha_left_max,
                                      Float_t alpha_right_start,
                                      Float_t alpha_right_min,
                                      Float_t alpha_right_max,
                                      Float_t n_left_start,
                                      Float_t n_left_min,
                                      Float_t n_left_max,
                                      Float_t n_right_start,
                                      Float_t n_right_min,
                                      Float_t n_right_max,
                                      Float_t frac_left_start,
                                      Float_t frac_left_min,
                                      Float_t frac_left_max,
                                      const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::MakeDMassSigBiCB",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooJpsiMassFitter::MakeDMassSigBiCB",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  TString mu_title="";
  TString neg_mu_title="";
  TString sig_left_title="";
  TString sig_right_title="";
  TString alpha_left_title="";
  TString alpha_right_title="";
  TString n_left_title="";
  TString n_right_title="";
  TString frac_left_title="";
  TString neg_mass_title="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    mu_title="#mu";
    neg_mu_title="-#mu";
    sig_left_title="#sigma_{left}";
    sig_right_title="#sigma_{right}";
    alpha_left_title="#alpha_{left}";
    alpha_right_title="#alpha_{right}";
    n_left_title="n_{left}";
    n_right_title="n_{right}";
    frac_left_title="f_{left}";
    neg_mass_title="-m";
  }
  else {
    mu_title.Form("%s #mu", m_dMassPartName);
    neg_mu_title.Form("%s -#mu", m_dMassPartName);
    sig_left_title.Form("%s #sigma_{left}", m_dMassPartName);
    sig_right_title.Form("%s #sigma_{right}", m_dMassPartName);
    alpha_left_title.Form("%s #alpha_{left}", m_dMassPartName);
    alpha_right_title.Form("%s #alpha_{right}", m_dMassPartName);
    n_left_title.Form("%s n_{left}", m_dMassPartName);
    n_right_title.Form("%s n_{right}", m_dMassPartName);
    frac_left_title.Form("%s f_{left}", m_dMassPartName);
    neg_mass_title.Form("-m_{%s}", m_dMassPartName);
  }

  RooRealVar mu("dmass_sig_mu", mu_title.Data(), mu_start, mu_min, mu_max, unit);
  RooRealVar sig_left("dmass_sig_sigma_left", sig_left_title.Data(), sig_left_start, sig_left_min, sig_left_max, unit);
  RooRealVar sig_right("dmass_sig_sigma_right", sig_right_title.Data(), sig_right_start, sig_right_min, sig_right_max, unit);
  RooRealVar alpha_left("dmass_sig_alpha_left", alpha_left_title.Data(), alpha_left_start, alpha_left_min, alpha_left_max);
  RooRealVar alpha_right("dmass_sig_alpha_right", alpha_right_title.Data(), alpha_right_start, alpha_right_min, alpha_right_max);
  RooRealVar n_left("dmass_sig_n_left", n_left_title.Data(), n_left_start, n_left_min, n_left_max);
  RooRealVar n_right("dmass_sig_n_right", n_right_title.Data(), n_right_start, n_right_min, n_right_max);
  RooRealVar frac_left("dmass_sig_frac_left", frac_left_title.Data(), frac_left_start, frac_left_min, frac_left_max);

  TString neg_mass_formula = "";
  neg_mass_formula.Form("-%s",mass->GetName());

  RooFormulaVar neg_mass("neg_mass",neg_mass_title.Data(),neg_mass_formula.Data(),*mass);
  RooFormulaVar neg_mu("neg_mu",neg_mu_title.Data(),"-dmass_sig_mu",mu);

  RooCBShape dmass_sig_cb_left("dmass_sig_cb_left", "", *mass, mu, sig_left, alpha_left, n_left);
  RooCBShape dmass_sig_cb_right("dmass_sig_cb_right", "", neg_mass, neg_mu, sig_right, alpha_right, n_right);

  RooAddPdf dMassSigModel(m_dMassSigModelName, "",
                          RooArgList(dmass_sig_cb_left,dmass_sig_cb_right),
                          RooArgList(frac_left));

  if (m_rws->import(dMassSigModel)) {
    throw WSImportFailure("RooJpsiMassFitter::MakeDMassSigBiCB",
                          *m_rws, dMassSigModel);
  }
}

void RooJpsiMassFitter::MakeDMassSigBiCBFixn(RooRealVar& mu, RooRealVar& sig_left,
                                  RooRealVar& sig_right, RooRealVar& alpha_left,
                                  RooRealVar& alpha_right, RooRealVar& frac_left)
{
  TString n_left_title="";
  TString n_right_title="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    n_left_title="n_{left}";
    n_right_title="n_{right}";
  }
  else {
    n_left_title.Form("%s n_{left}", m_dMassPartName);
    n_right_title.Form("%s n_{right}", m_dMassPartName);
  }

  RooRealVar n_left("dmass_sig_n_left", n_left_title.Data(), 1.);
  RooRealVar n_right("dmass_sig_n_right", n_right_title.Data(), 1.);

  MakeDMassSigBiCB( mu, sig_left,
                    sig_right, alpha_left,
                    alpha_right, n_left,
                    n_right, frac_left);

  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::MakeDMassSigBiCB",
                           "No RooWorkspace object is defined.");
  }

  m_rws->var("dmass_sig_n_left")->setConstant(true);
  m_rws->var("dmass_sig_n_right")->setConstant(true);
}

void RooJpsiMassFitter::MakeDMassSigBiCBFixn(Float_t mu_start,
                                          Float_t mu_min,
                                          Float_t mu_max,
                                          Float_t sig_left_start,
                                          Float_t sig_left_min,
                                          Float_t sig_left_max,
                                          Float_t sig_right_start,
                                          Float_t sig_right_min,
                                          Float_t sig_right_max,
                                          Float_t alpha_left_start,
                                          Float_t alpha_left_min,
                                          Float_t alpha_left_max,
                                          Float_t alpha_right_start,
                                          Float_t alpha_right_min,
                                          Float_t alpha_right_max,
                                          Float_t frac_left_start,
                                          Float_t frac_left_min,
                                          Float_t frac_left_max,
                                          const char* unit)
{

  MakeDMassSigBiCB( mu_start, mu_min,mu_max,
                    sig_left_start, sig_left_min, sig_left_max,
                    sig_right_start, sig_right_min, sig_right_max,
                    alpha_left_start, alpha_left_min, alpha_left_max,
                    alpha_right_start, alpha_right_min, alpha_right_max,
                    1., 0.95, 1.05,
                    1., 0.95, 1.05,
                    frac_left_start, frac_left_min, frac_left_max,
                    unit);
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::MakeDMassSigBiCB",
                           "No RooWorkspace object is defined.");
  }

  m_rws->var("dmass_sig_n_left")->setConstant(true);
  m_rws->var("dmass_sig_n_right")->setConstant(true);

}

void RooJpsiMassFitter::MakeBkgJpsi2s(RooRealVar& grad, RooRealVar& mu, 
                                        RooRealVar& frac)
{
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::MakeBkgJpsi2s",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s",
                           *m_rws, m_dMassName, "RooRealVar");
  }

  TString invMassUnit="";
  TString gradTitle="";
  TString fracTitle="";
  TString neg_mu_title="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    gradTitle="#nabla";
    fracTitle="f_{J/#psi(2S)}";
    neg_mu_title="-#mu_{J/#psi(2S)}";
  }
  else {
    gradTitle.Form("%s #nabla", m_dMassPartName);
    fracTitle.Form("%s f_{J/#psi(2S)}", m_dMassPartName);
    neg_mu_title.Form("%s -#mu_{J/#psi(2S)}", m_dMassPartName);
  }
  
  RooRealVar * frac_left = m_rws->var("dmass_sig_frac_left");
  if (!frac_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_frac_left", "RooRealVar");
  RooAbsReal * neg_mass = (RooAbsReal*) m_rws->obj("neg_mass");
  if (!neg_mass) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "neg_mass", "RooFormulaVar");
  RooRealVar * sig_left = m_rws->var("dmass_sig_sigma_left");
  if (!sig_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_sigma_left", "RooRealVar");
  RooRealVar * sig_right = m_rws->var("dmass_sig_sigma_right");
  if (!sig_right) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_sigma_right", "RooRealVar");
  RooRealVar * n_left = m_rws->var("dmass_sig_n_left");
  if (!n_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_n_left", "RooRealVar");
  RooRealVar * n_right = m_rws->var("dmass_sig_n_right");
  if (!n_right) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_n_right", "RooRealVar");
  RooRealVar * alpha_left = m_rws->var("dmass_sig_alpha_left");
  if (!alpha_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_alpha_left", "RooRealVar");
  RooRealVar * alpha_right = m_rws->var("dmass_sig_alpha_right");
  if (!alpha_right) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_alpha_right", "RooRealVar");
  
  RooFormulaVar neg_mu("neg_jpsi2s_mu",neg_mu_title.Data(),"-dmass_jpsi2s_mu",mu);

  RooCBShape cb_left("dmass_jpsi2s_cb_left", "", *mass, mu, *sig_left, *alpha_left, *n_left);
  RooCBShape cb_right("dmass_jpsi2s_cb_right", "",*neg_mass, neg_mu, *sig_right, *alpha_right, *n_right);

  RooAddPdf bkg_jpsi2e("dmass_jpsi2s", "",
                          RooArgList(cb_left,cb_right),
                          RooArgList(*frac_left));

  RooExponential poly("dmass_bkg","",*mass,grad);
  
//   RooChebychev poly("dmass_bkg","",*mass,RooArgList(grad));
  
  RooAddPdf dMassBkgModel(m_dMassBkgModelName, "",
                          RooArgList(bkg_jpsi2e,poly),
                          RooArgList(frac));
  
  
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooJpsiMassFitter::MakeBkgJpsi2s",
                          *m_rws, dMassBkgModel);
  }
}

void RooJpsiMassFitter::MakeBkgJpsi2s(Float_t grad_start, Float_t grad_min,
                                        Float_t grad_max, Float_t mu_start, 
                                        Float_t mu_min, Float_t mu_max,
                                        Float_t frac_start, Float_t frac_min,
                                        Float_t frac_max, const char* unit)
{
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::MakeBkgJpsi2s",
                           "No RooWorkspace object is defined.");
  }
  RooRealVar* mass = m_rws->var(m_dMassName);
  if (!mass) {
    throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s",
                           *m_rws, m_dMassName, "RooRealVar");
  }
  
  TString mu_title="";
  TString neg_mu_title="";

  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    mu_title="#mu_{J/#psi(2S)}";
    neg_mu_title="-#mu_{J/#psi(2S)}";
  }
  else {
    mu_title.Form("%s #mu_{J/#psi(2S)}", m_dMassPartName);
    neg_mu_title.Form("%s -#mu_{J/#psi(2S)}", m_dMassPartName);
  }

  RooRealVar mu("dmass_jpsi2s_mu", mu_title.Data(), mu_start, mu_min, mu_max, unit);

  RooRealVar * frac_left = m_rws->var("dmass_sig_frac_left");
  if (!frac_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_frac_left", "RooRealVar");
  RooAbsReal * neg_mass = (RooAbsReal*) m_rws->obj("neg_mass");
  if (!neg_mass) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "neg_mass", "RooFormulaVar");
  RooRealVar * sig_left = m_rws->var("dmass_sig_sigma_left");
  if (!sig_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_sigma_left", "RooRealVar");
  RooRealVar * sig_right = m_rws->var("dmass_sig_sigma_right");
  if (!sig_right) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_sigma_right", "RooRealVar");
  RooRealVar * n_left = m_rws->var("dmass_sig_n_left");
  if (!n_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_n_left", "RooRealVar");
  RooRealVar * n_right = m_rws->var("dmass_sig_n_right");
  if (!n_right) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_n_right", "RooRealVar");
  RooRealVar * alpha_left = m_rws->var("dmass_sig_alpha_left");
  if (!alpha_left) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_alpha_left", "RooRealVar");
  RooRealVar * alpha_right = m_rws->var("dmass_sig_alpha_right");
  if (!alpha_right) throw WSRetrievalFailure("RooJpsiMassFitter:MakeBkgJpsi2s", *m_rws, "dmass_sig_alpha_right", "RooRealVar");
  
  RooFormulaVar neg_mu("neg_jpsi2s_mu",neg_mu_title.Data(),"-dmass_jpsi2s_mu",mu);

  RooCBShape cb_left("dmass_jpsi2s_cb_left", "", *mass, mu, *sig_left, *alpha_left, *n_left);
  RooCBShape cb_right("dmass_jpsi2s_cb_right", "",*neg_mass, neg_mu, *sig_right, *alpha_right, *n_right);

  RooAddPdf bkg_jpsi2e("dmass_jpsi2s", "",
                          RooArgList(cb_left,cb_right),
                          RooArgList(*frac_left));

  TString invMassUnit="";
  if (unit&&strcmp(unit,"")!=0) {
    invMassUnit.Form("(%s)^{-1}", unit);
  }
  TString gradTitle="";
  TString fracTitle="";
  if (!m_dMassPartName||strcmp(m_dMassPartName,"")==0) {
    gradTitle="#nabla";
    fracTitle="f_{J/#psi(2S)}";
  }
  else {
    gradTitle.Form("%s #nabla", m_dMassPartName);
    fracTitle.Form("%s f_{J/#psi(2S)}", m_dMassPartName);
  }
  
  RooRealVar decay("dmass_bkg_exp_decay", "#Gamma_{bkg}", grad_start, grad_min,
                  grad_max, "");
  RooExponential exp_decay("dmass_bkg","",*mass,decay);

//   RooRealVar grad("dmass_bkg_poly_c1", gradTitle.Data(), grad_start, grad_min,
//                   grad_max, invMassUnit);
//   RooChebychev poly("dmass_bkg","",*mass,RooArgList(grad));
  
  RooRealVar bkg_jpsi2e_frac("dmass_bkg_frac_jpsi2s", fracTitle.Data(), frac_start, frac_min,
                  frac_max, "");
  
  RooAddPdf dMassBkgModel(m_dMassBkgModelName, "",
//                           RooArgList(bkg_jpsi2e,poly),
                          RooArgList(bkg_jpsi2e,exp_decay),
                          RooArgList(bkg_jpsi2e_frac));
  
  if (m_rws->import(dMassBkgModel)) {
    throw WSImportFailure("RooJpsiMassFitter::MakeBkgJpsi2s",
                          *m_rws, dMassBkgModel);
  }
}



void RooJpsiMassFitter::ReplaceWithAbsVar( const char* varName, 
                                           float varMin, 
                                           float varMax )
{
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::ReplaceWithAbsVar",
                           "No RooWorkspace object is defined.");
  }
  
  RooAddPdf* pdf = (RooAddPdf*) m_rws->obj(m_modelName);
  if (!pdf) {
    throw WSRetrievalFailure("RooJpsiMassFitter:ReplaceWithAbsVar",
                           *m_rws, m_modelName, "RooAddPdf");
  }
  
  m_rws->factory(TString::Format("RooFormulaVar::abs_%s('abs(%s)',{%s})",varName,varName,varName).Data());
  
  RooFormulaVar* var = (RooFormulaVar*) m_rws->obj(TString::Format("abs_%s",varName).Data());
  if (!var) {
    throw WSRetrievalFailure("RooJpsiMassFitter:ReplaceWithAbsVar",
                           *m_rws, TString::Format("abs_%s",varName).Data(), "RooFormulaVar");
  }
  
  if (strcmp(varName,"nbkg") == 0) {
    var->SetTitle("N_{bkg.}");
  }
  var->setAttribute(TString::Format("ORIGNAME:%s",varName).Data(), true);
  
  pdf->redirectServers(RooArgList(*var), true ,true);
  
  RooRealVar* var_orig = m_rws->var(varName);
  if (!var_orig) {
    throw WSRetrievalFailure("RooJpsiMassFitter:ReplaceWithAbsVar",
                           *m_rws, varName, "RooRealVar");
  }
  
  var_orig->setMin(varMin);
  var_orig->setMax(varMax);

}



void RooJpsiMassFitter::RemoveAbsVar( const char* varName, 
                                      float varMin, 
                                      float varMax )
{
  if (!m_rws) {
    throw GeneralException("RooJpsiMassFitter::ReplaceWithAbsVar",
                           "No RooWorkspace object is defined.");
  }
  
  RooAddPdf* pdf = (RooAddPdf*) m_rws->obj(m_modelName);
  if (!pdf) {
    throw WSRetrievalFailure("RooJpsiMassFitter:ReplaceWithAbsVar",
                           *m_rws, m_modelName, "RooAddPdf");
  }
  
  RooRealVar* var_orig = m_rws->var(varName);
  if (!var_orig) {
    throw WSRetrievalFailure("RooJpsiMassFitter:ReplaceWithAbsVar",
                           *m_rws, varName, "RooRealVar");
  }
  
  var_orig->setAttribute(TString::Format("ORIGNAME:abs_%s",varName).Data(), true);
  
  pdf->redirectServers(RooArgList(*var_orig), true ,true);
  
  var_orig->setMin(varMin);
  var_orig->setMax(varMax);

}
