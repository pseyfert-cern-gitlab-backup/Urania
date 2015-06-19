// $Id: $
// Include files
// std libs
#include <iostream>
#include <cmath>
#include <sstream>
#include <cassert>
#include <algorithm>

// ROOT
#include "TCanvas.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TAxis.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TEventList.h"
#include "TSystem.h"
#include "TTreeFormula.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"

// RooFit
#include "RooWorkspace.h"

#include "RooAbsCollection.h"
#include "RooAbsData.h"
#include "RooDataSet.h"
#include "RooDataHist.h"

#include "RooAbsReal.h"
#include "RooRealVar.h"

#include "RooPlot.h"

#include "RooAbsPdf.h"
#include "RooAddPdf.h"

#include "RooArgSet.h"

#include "RooAbsBinning.h"

#include "RooFormulaVar.h"

#include "RooChi2Var.h"
#include "RooChiSquarePdf.h"

#include "RooStats/SPlot.h"
#include "RooMinuit.h"

#include "RooCmdArg.h"

// local
#include "RooPhysFitter/RooPhysFitter.h"
#include "RooPhysFitter/Exceptions.h"
#include "RooPhysFitter/RooGaussianChi2Var.h"
#include "RooPhysFitter/RooPearsonsChi2Var.h"
#include "RooPhysFitter/RooYatesChi2Var.h"
#include "RooPhysFitter/RooLLRatioVar.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RooPhysFitter
//
// 2011-05-11 : Philip Hunt
//-----------------------------------------------------------------------------

using namespace RooPhysFit;
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RooPhysFitter::RooPhysFitter(  ) : TNamed(), m_rws(0), m_file(0)
{
    m_hasOwnership=kFALSE;

    m_dataSetName="data";
    m_modelName="model";
    m_sWeightVarSetName="Weights";
    m_plotParamsSetName="PlotParams";

    m_plotTestStat=RooPhysFitter::NoTestStat;

    m_chi2MCStudyFlag=kFALSE;
    m_nChi2Toys=10000;

    m_globalPlotBins=100;
    m_globalChi2Bins=100;

    m_paramBoxX1=0.60;
    m_paramBoxY1=0.70;
    m_paramBoxX2=0.95;
    m_paramBoxY2=0.93;

    m_paramBoxTextSize=0.028;
    m_paramBoxTextAlign=12; // left adjusted, vertically centered
    m_paramBoxName="paramBox";

    m_modelLineColor=kBlue;
    m_modelLineStyle=1;
    m_modelLineWidth=3;

    m_dataSetLineColor=kBlack;
    m_dataSetLineStyle=1;
    m_dataSetLineWidth=3;

    m_dataSetMarkerColor=kBlack;
    m_dataSetMarkerStyle=kFullSquare;
    m_dataSetMarkerSize=1;

    m_dataSetFillColor=kBlack;
    m_dataSetFillStyle=3001;

    m_dataSetDrawOption="P";
}

// overloaded constructor
RooPhysFitter::RooPhysFitter( const char* name, const char* title)
        : TNamed(name, title), m_rws(0), m_file(0)
{
    m_hasOwnership=kFALSE;

    m_dataSetName="data";
    m_modelName="model";
    m_sWeightVarSetName="Weights";
    m_plotParamsSetName="PlotParams";

    m_plotTestStat=RooPhysFitter::NoTestStat;

    m_chi2MCStudyFlag=kFALSE;
    m_nChi2Toys=10000;

    m_globalPlotBins=100;
    m_globalChi2Bins=100;

    m_paramBoxX1=0.60;
    m_paramBoxY1=0.70;
    m_paramBoxX2=0.95;
    m_paramBoxY2=0.93;

    m_paramBoxTextSize=0.028;
    m_paramBoxTextAlign=12; // left adjusted, vertically centered
    m_paramBoxName="paramBox";

    m_modelLineColor=kBlue;
    m_modelLineStyle=1;
    m_modelLineWidth=3;

    m_dataSetLineColor=kBlack;
    m_dataSetLineStyle=1;
    m_dataSetLineWidth=3;

    m_dataSetMarkerColor=kBlack;
    m_dataSetMarkerStyle=kFullSquare;
    m_dataSetMarkerSize=1;

    m_dataSetFillColor=kBlack;
    m_dataSetFillStyle=3001;

    m_dataSetDrawOption="P";
}


// create a new RooWorkspace object
void RooPhysFitter::CreateWS( const char* name, const char* title)
{
    if (m_rws&&m_hasOwnership)
    {
        std::cout << "WARNING: Deleting existing RooWorkspace "
        << m_rws->GetName()
        << ". If a file is attached, it will be closed"
        << std::endl;
        delete m_rws;
        if (m_file)
            delete m_file;
    }
    m_rws = new RooWorkspace(name, title);
    m_hasOwnership=kTRUE;
}

// add a prexisting RooWorkspace object
void RooPhysFitter::SetWS(RooWorkspace* ws, Bool_t takeOwnership)
{
    if (m_rws&&m_hasOwnership)
    {
        std::cout << "WARNING: Deleting existing RooWorkspace "
        << m_rws->GetName()
        << ". If a file is attached, it will be closed"
        << std::endl;
        delete m_rws;
        if (m_file)
            delete m_file;
    }
    m_rws = ws;
    m_hasOwnership = takeOwnership;
}

// attach a file for writing out the RooWorkspace
void RooPhysFitter::AttachFile(const char* filename, const char* options)
{
    if (m_file)
    {
        std::cout << "WARNING: Deleting existing TFile " << m_file->GetName()
        << std::endl;
        delete m_file;
    }
    TFile *f=TFile::Open(filename, options);
    if (!f || f->IsZombie())
    {
        throw IOFailure("RooPhysFitter::AttachFile", filename, options);
    }
    m_file=f;
}

// load an existing RooWorkspace from file,
// and optionally attach the file for writing any changes to the
// RooWorkspace
void RooPhysFitter::LoadWS( const char* filename, const char* wsName,
                            Bool_t attachFile)
{
    const char *mode=(!attachFile)?"READ":"UPDATE";
    TFile *f=TFile::Open(filename, mode);
    if (!f || f->IsZombie())
    {
        throw IOFailure("RooPhysFitter::LoadWS", filename, mode);
    }

    RooWorkspace *rws = dynamic_cast<RooWorkspace*>(f->Get(wsName));
    if (!rws)
    {
        throw TDirectoryError("RooPhysFitter::LoadWS", *f, wsName);
    }
    if (m_hasOwnership&&m_rws)
    {
        std::cout << "WARNING: Deleting existing RooWorkspace " << m_rws->GetName()
        << std::endl;
        delete m_rws;
    }
    m_rws=rws;
    m_hasOwnership=kFALSE;
    if (attachFile)
    {
        if (m_file)
        {
            std::cout << "WARNING: Deleting existing TFile " << m_file->GetName()
            << std::endl;
            delete m_file;
        }
        m_file=f;
    }
}

// save the workspace to the attached file
void RooPhysFitter::SaveWS()
{
    if (!m_file)
    {
        throw GeneralException("RooPhysFitter::SaveWS",
                               "No output file specified. Cannot save workspace.");
    }
    m_file->cd();
    m_rws->Write();
}

// save the workspace to the specified file
void RooPhysFitter::SaveWS(const char* filename, Bool_t recreateFile)
{
    const char* mode=(recreateFile)?"RECREATE":"UPDATE";
    AttachFile(filename, mode);
    m_file->cd();
    m_rws->Write();
}

// Save the workspace to the specified file
// Since we don't own the file, we should release ownership
void RooPhysFitter::SaveWS(TFile* f)
{
   if (!f) { 
     throw GeneralException("RooPhysFitter::SaveWS",
                            "No output file specified. Cannot save workspace.");
   }

   f->cd();
   m_rws->Write();

   if (m_hasOwnership) {
     std::cout << "WARNING: Releasing ownership of RooWorkspace to TFile " << f->GetName()
               << std::endl;
   }
   m_hasOwnership=kFALSE;
}

// Create a reduced data set with name "newName" using cut "cut"
// If saveToWS is true, then the new data set is saved to the workspace,
// otherwise a pointer to the new data set is returned
RooDataSet* RooPhysFitter::CreateReducedDataSet(const char* newName,
                                                const char* cut,
                                                Bool_t saveToWS) 
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::CreateReducedDataSet",
                           "No RooWorkspace object is defined");
  }
  if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
  {
    throw GeneralException("RooPhysFitter::CreateReducedDataSet",
                           "No RooDataSet name defined");
  }
  RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds)
  {
    throw WSRetrievalFailure("RooPhysFitter::CreateReducedDataSet",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  RooDataSet* rds_reduced = (RooDataSet*)rds->reduce(cut);
  if (!rds_reduced)
  {
    std::stringstream msg;
    msg << "Failed to create reduced data set with cut " << cut;
    
    throw GeneralException("RooPhysFitter::CreateReducedDataSet",
                           msg.str());
  }
  rds_reduced->SetName(newName);
  if (saveToWS) {
    if (m_rws->import(*rds_reduced)) {
      throw WSImportFailure("RooPhysFitter::CreateReducedDataSet",
                            *m_rws, *rds_reduced);
    }
    return 0;
  }
  return rds_reduced;
}


// Create a reduced data set with name "newName" using range "range"
// If saveToWS is true, then the new data set is saved to the workspace,
// otherwise a pointer to the new data set is returned
// multiple range can be specified using a colon separator
RooDataSet* RooPhysFitter::CreateReducedDataSetByRange(const char* newName,
                                                       const char* range,
                                                       Bool_t saveToWS) 
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::CreateReducedDataSetByRange",
                           "No RooWorkspace object is defined");
  }
  if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
  {
    throw GeneralException("RooPhysFitter::CreateReducedDataSetByRange",
                           "No RooDataSet name defined");
  }
  if (!range||strcmp(range,"")==0)
  {
    throw GeneralException("RooPhysFitter::CreateReducedDataSetByRange",
                           "No range defined");
  }
  
  RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds)
  {
    throw WSRetrievalFailure("RooPhysFitter::CreateReducedDataSetByRange",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  std::string str(range);
  boost::char_separator<char> sep(";");
  Tokenizer tokens(str, sep);
  std::vector<std::string> args;
  args.assign(tokens.begin(),tokens.end());
      
  RooDataSet* rds_reduced = 0;

  std::cout << "RooPhysFitter::CreateReducedDataSetByRange: Got " 
            << args.size() << " ranges: " << range << std::endl;
  
  switch (args.size()) {
  case 0:
    {
      throw GeneralException("RooPhysFitter::CreateReducedDataSetByRange",
                             "Unable to get list of ranges");
      break;
    }
  case 1:
    {
      std::string r1=args.at(0);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()));
      break;
    }
  case 2:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()));
      break;
    }
  case 3:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      std::string r3=args.at(2);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()),
                                             RooFit::CutRange(r3.c_str()));
      break;
    }
  case 4:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      std::string r3=args.at(2);
      std::string r4=args.at(3);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()),
                                             RooFit::CutRange(r3.c_str()),
                                             RooFit::CutRange(r4.c_str()));
      break;
    }
  case 5:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      std::string r3=args.at(2);
      std::string r4=args.at(3); 
      std::string r5=args.at(4);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()),
                                             RooFit::CutRange(r3.c_str()),
                                             RooFit::CutRange(r4.c_str()),
                                             RooFit::CutRange(r5.c_str()));
      break;
    }
  case 6:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      std::string r3=args.at(2);
      std::string r4=args.at(3); 
      std::string r5=args.at(4);
      std::string r6=args.at(5);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()),
                                             RooFit::CutRange(r3.c_str()),
                                             RooFit::CutRange(r4.c_str()),
                                             RooFit::CutRange(r5.c_str()),
                                             RooFit::CutRange(r6.c_str()));
      break;
    }
    case 7:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      std::string r3=args.at(2);
      std::string r4=args.at(3); 
      std::string r5=args.at(4);
      std::string r6=args.at(5);
      std::string r7=args.at(6);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()),
                                             RooFit::CutRange(r3.c_str()),
                                             RooFit::CutRange(r4.c_str()),
                                             RooFit::CutRange(r5.c_str()),
                                             RooFit::CutRange(r6.c_str()),
                                             RooFit::CutRange(r7.c_str()));
      break;
    }
    case 8:
    {
      std::string r1=args.at(0);
      std::string r2=args.at(1);
      std::string r3=args.at(2);
      std::string r4=args.at(3); 
      std::string r5=args.at(4);
      std::string r6=args.at(5);
      std::string r7=args.at(6);
      std::string r8=args.at(7);
      rds_reduced = (RooDataSet*)rds->reduce(RooFit::CutRange(r1.c_str()),
                                             RooFit::CutRange(r2.c_str()),
                                             RooFit::CutRange(r3.c_str()),
                                             RooFit::CutRange(r4.c_str()),
                                             RooFit::CutRange(r5.c_str()),
                                             RooFit::CutRange(r6.c_str()),
                                             RooFit::CutRange(r7.c_str()),
                                             RooFit::CutRange(r8.c_str()));
      break;
    }
  default:
    {
      std::stringstream msg;
      msg << "No more than 8 ranges supported, but " << args.size()
          << " requested";
      throw GeneralException("RooPhysFitter::CreateReducedDataSetByRange",
                             msg.str());
      break;
    }    
  }
  
  if (!rds_reduced)
  {
    std::stringstream msg;
    msg << "Failed to create reduced data set with cut range " << range;
    
    throw GeneralException("RooPhysFitter::CreateReducedDataSetByRange",
                           msg.str());
  }
  rds_reduced->SetName(newName);
  if (saveToWS) {
    if (m_rws->import(*rds_reduced)) {
      throw WSImportFailure("RooPhysFitter::CreateReducedDataSetByRange",
                            *m_rws, *rds_reduced);
    }
    return 0;
  }
  return rds_reduced;
}


// perform the fit of the specified model PDF to the specified data
void RooPhysFitter::PerformFit(const char* fitName, Int_t nCores,
                               Bool_t saveSnapshot, Bool_t printResults,
                               Bool_t useSumW2Errors, Bool_t extendedMode)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::PerformFit",
                               "No RooWorkspace object is defined");
    }
    if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
    {
        throw GeneralException("RooPhysFitter::PerformFit",
                               "No RooDataSet name defined");
    }
    RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::PerformFit",
                                 *m_rws, m_dataSetName, "RooDataSet");
    }
    if (rds->numEntries()==0) {
      throw GeneralException("RooPhysFitter::PerformFit",
                             "Request to perform fit to data set with no entries");
    }
    RooAddPdf* model = dynamic_cast<RooAddPdf*>(m_rws->pdf(m_modelName));
    if (!model)
    {
        throw WSRetrievalFailure("RooPhysFitter::PerformFit",
                                 *m_rws, m_modelName, "RooAddPdf");
    }

    RooFitResult* res = model->fitTo(*rds, RooFit::Extended(extendedMode),
                                     RooFit::NumCPU(nCores),
                                     RooFit::Timer(kTRUE),
                                     RooFit::SumW2Error(useSumW2Errors),
                                     RooFit::Save(kTRUE));
    if (printResults&&res)
    {
        res->Print("v");
    }

    if (saveSnapshot)
    {
        const RooArgSet* fitParams = model->getParameters(*rds);
        assert(fitParams);
        m_rws->saveSnapshot(fitName,*fitParams,kTRUE);
    }
    TString fitResName=TString::Format("rfres_%s", fitName);
    res->SetName(fitResName.Data());
    if (m_rws->import(*res)) {
      throw WSImportFailure("RooPhysFitter::PerformFit",
                            *m_rws, *res);
    }
}

// Perform a binned fit to the model PDF
// A binned clone of the data is made, which is then used to fit the PDF
// The default binning for each variable in the original dataset is used
// The number of bins for a given variable can be changed using the
// SetBins method
// By default, a maximum likelihood fit is performed. If useChi2Method is
// set to true, then a chi^2 fit is performed instead
void RooPhysFitter::PerformBinnedFit(const char* fitName, Int_t nCores,
                                     Bool_t saveSnapshot, Bool_t printResults,
                                     Bool_t useSumW2Errors, 
                                     Bool_t extendedMode,
                                     Bool_t useChi2Method)
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::PerformBinnedFit",
                           "No RooWorkspace object is defined");
  }
  if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
  {
    throw GeneralException("RooPhysFitter::PerformBinnedFit",
                           "No RooDataSet name defined");
  }
  RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds)
  {
    throw WSRetrievalFailure("RooPhysFitter::PerformBinnedFit",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  if (rds->numEntries()==0) {
    throw GeneralException("RooPhysFitter::PerformBinnedFit",
      "Request to perform fit to data set with no entries");
  }

  // get the model PDF
  RooAddPdf* model = (RooAddPdf*)m_rws->pdf(m_modelName);
  if (!model)
  {
    throw WSRetrievalFailure("RooPhysFitter::PerformBinnedFit"
                             ,*m_rws, m_modelName, "RooAddPdf");
  }
  
  // get the list of observables
  const RooArgSet* observables = model->getObservables(*rds);
  assert(observables);

  TString binnedName=TString::Format("%s_binned", rds->GetName());
  TString binnedTitle=TString::Format("%s_binned", rds->GetTitle());

  RooArgSet* obsCpy = (RooArgSet*)observables->Clone();

  RooDataHist* hist = 0;
  try {
    hist = new RooDataHist(binnedName.Data(),
                           binnedTitle.Data(),
                           *obsCpy, *rds);
  }
  catch (std::bad_alloc& e) {
    std::stringstream msg;
    msg << "Got std::bad_alloc when creating new RooDataHist "
        << binnedName;
    throw GeneralException("RooPhysFitter::PerformBinnedFit",
                           msg.str());
  }
  if (!hist) {
    throw GeneralException("RooPhysFitter::PerformBinnedFit",
                           "Failed to make binned copy of input data set");
  }

  RooFitResult* res = 0;
  if (!useChi2Method) {
    res = model->fitTo(*hist, RooFit::Extended(extendedMode),
                       RooFit::NumCPU(nCores),
                       RooFit::Timer(kTRUE),
                       RooFit::SumW2Error(useSumW2Errors),
                       RooFit::Save(kTRUE),
                       RooFit::PrintLevel(1));
  }
  else {
    RooAbsData::ErrorType errType= !useSumW2Errors ? RooAbsData::Poisson : RooAbsData::SumW2;
    res = model->chi2FitTo(*hist, RooFit::Extended(extendedMode),
                           RooFit::NumCPU(nCores),
                           RooFit::DataError(errType),
                           RooFit::Timer(kTRUE),
                           RooFit::Save(kTRUE),
                           RooFit::PrintLevel(1));
  }
  if (printResults&&res)
  {
    res->Print("v");
  }
  
  if (saveSnapshot)
  {
    const RooArgSet* fitParams = model->getParameters(*rds);
    assert(fitParams);
    m_rws->saveSnapshot(fitName,*fitParams,kTRUE);
  }
  TString fitResName=TString::Format("rfres_%s", fitName);
  res->SetName(fitResName.Data());
  if (m_rws->import(*res)) {
    throw WSImportFailure("RooPhysFitter::PerformBinnedFit",
                          *m_rws, *res);
  }
  delete hist;
}

void RooPhysFitter::PerformIterativeBinnedFit(std::vector<Int_t>& minuitStrategies,
                                              const char* fitName, Int_t nCores,
                                              Bool_t saveSnapshot, Bool_t printResults,
                                              Bool_t useSumW2Errors, 
                                              Bool_t extendedMode,
                                              Bool_t useChi2Method)
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::PerformIterativeBinnedFit",
                           "No RooWorkspace object is defined");
  }
  if (!m_dataSetName||strcmp(m_dataSetName,"")==0)
  {
    throw GeneralException("RooPhysFitter::PerformIterativeBinnedFit",
                           "No RooDataSet name defined");
  }
  RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds)
  {
    throw WSRetrievalFailure("RooPhysFitter::PerformIterativeBinnedFit",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  if (rds->numEntries()==0) {
    throw GeneralException("RooPhysFitter::PerformIterativeBinnedFit",
      "Request to perform fit to data set with no entries");
  }

  // get the model PDF
  RooAddPdf* model = (RooAddPdf*)m_rws->pdf(m_modelName);
  if (!model)
  {
    throw WSRetrievalFailure("RooPhysFitter::PerformIterativeBinnedFit"
                             ,*m_rws, m_modelName, "RooAddPdf");
  }

  // get the list of observables
  const RooArgSet* observables = model->getObservables(*rds);
  assert(observables);
  observables->Print();

  TString binnedName=TString::Format("%s_binned", rds->GetName());
  TString binnedTitle=TString::Format("%s_binned", rds->GetTitle());

  RooArgSet* obsCpy = (RooArgSet*)observables->Clone();

  RooDataHist* hist = 0;
  try {
    hist = new RooDataHist(binnedName.Data(),
                           binnedTitle.Data(),
                           *obsCpy, *rds);
  }
  catch (std::bad_alloc& e) {
    std::stringstream msg;
    msg << "Got std::bad_alloc when creating new RooDataHist "
        << binnedName;
    throw GeneralException("RooPhysFitter::PerformIterativeBinnedFit",
                           msg.str());
  }
  if (!hist) {
    throw GeneralException("RooPhysFitter::PerformIterativeBinnedFit",
                           "Failed to make binned copy of input data set");
  }

  if (minuitStrategies.empty())
  {
    throw GeneralException("RooPhysFitter::PerformIterativeBinnedFit",
                           "vector<Int_t> empty");
  }
  
  RooFitResult* res = 0;
  std::vector<Int_t>::iterator itr;
  for(itr=minuitStrategies.begin(); itr<minuitStrategies.end(); itr++)
  {
    if (!useChi2Method) 
    {
      
      res = model->fitTo(*hist, RooFit::Extended(extendedMode),
                         RooFit::NumCPU(nCores),
                         RooFit::Timer(kTRUE),
                         RooFit::SumW2Error(useSumW2Errors),
                         RooFit::Save(kTRUE),
                         RooFit::Strategy(*itr),
                         RooFit::PrintLevel(3));
      
    }
    else 
    {
      RooAbsData::ErrorType errType= !useSumW2Errors ? RooAbsData::Poisson : RooAbsData::SumW2;
      res = model->chi2FitTo(*hist, RooFit::Extended(extendedMode),
                             RooFit::NumCPU(nCores),
                             RooFit::DataError(errType),
                             RooFit::Timer(kTRUE),
                             RooFit::Save(kTRUE),
                             RooFit::Strategy(*itr),
                             RooFit::PrintLevel(3));
      
    }
  }//Loop over MINUIT Strategies
  
  if (printResults&&res)
  {
    res->Print("v");
  }
  
  if (saveSnapshot)
  {
    const RooArgSet* fitParams = model->getParameters(*rds);
    assert(fitParams);
    m_rws->saveSnapshot(fitName,*fitParams,kTRUE);
  }
  TString fitResName=TString::Format("rfres_%s", fitName);
  res->SetName(fitResName.Data());
  if (m_rws->import(*res)) {
    throw WSImportFailure("RooPhysFitter::PerformIterativeBinnedFit",
                          *m_rws, *res);
  }
  delete hist;
}


// Calculate SWeights (Note that newName is only used when the RooDataSet
// is cloned). To use the current values for the fit parameters
// (instead of loading a snapshot), specify an empty string
// If no newName is specified, then the dataset with wrights will be called
// {origName}_withWeights, where {origName} is the name of the input dataset
void RooPhysFitter::CalculateSWeights(const char* fitName,
                                      const char* newName)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::CalculateSWeights",
                               "No RooWorkspace object is defined!");
    }
    RooDataSet* rds = (RooDataSet*)m_rws->data(m_dataSetName);
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::CalculateSWeights"
                                 ,*m_rws, m_dataSetName, "RooDataSet");
    }

    RooAddPdf* model = (RooAddPdf*)m_rws->pdf(m_modelName);
    if (!model)
    {
        throw WSRetrievalFailure("RooPhysFitter::CalculateSWeights"
                                 ,*m_rws, m_modelName, "RooAddPdf");
    }

    // make a copy of the RooAddPdf (otherwise sPlots does not work)
    RooAddPdf* modelClone = (RooAddPdf*)model->cloneTree();
    assert(modelClone);

    const RooArgList yields = modelClone->coefList();

    if (fitName&&strcmp(fitName,"")!=0)
    {
        std::cout << "INFO: Loading snapshot " << fitName << std::endl;
        if (!m_rws->loadSnapshot(fitName))
        {
            throw WSRetrievalFailure("RooPhysFitter::CalculateSWeights",
                                     *m_rws, fitName, "fit snapshot");
        }
    }
    if (strcmp(newName, m_dataSetName)==0)
    {
      std::stringstream msg;
      msg << "Requested RooDataSet name " << newName 
          << " is the same as the current dataset";
      throw GeneralException("RooPhysFitter::CalculateSWeights",
                             msg.str());
    }
    TString weightedName=newName;
    if (!newName||strcmp(newName,"")==0)
    {
        weightedName.Form("%s_withWeights", rds->GetName());
        std::cout << "WARNING: No new RooDataSet name specified for "
        << " RooDataSet with weights. "
        << "Will use the name " << weightedName << std::endl;
    }

    // create sPlot object
    std::cout << "Constructing sWeights..." << std::endl;
    RooStats::SPlot* splot = new RooStats::SPlot("sPlot", "An sPlot",
                             *rds, modelClone,
                             yields, RooArgSet(),
                             kTRUE, kTRUE,
                             weightedName.Data());


    RooDataSet* rds_withWeights=splot->GetSDataSet();
    if (!rds_withWeights)
    {
        throw GeneralException("RooPhysFitter::CalculateSWeights",
                               "No dataset with sWeight variables returned by sPlot object!");
    }

    std::cout << "Checking SWeights:" << std::endl;
    RooRealVar *arg=0;
    TIterator *iter = yields.createIterator();
    assert(iter);
    while ( (arg = (RooRealVar*)iter->Next()) )
    {
        std::cout << "Yield " << arg->GetName()
        << " = " << arg->getVal()
        << " . From sWeights it is "
        << splot->GetYieldFromSWeight(arg->GetName())
        << " . " << std::endl;
    }

    if(m_rws->import(*rds_withWeights))
    {
        throw WSImportFailure("RooPhysFitter::CalculateSWeights",
                              *m_rws, *rds_withWeights);
    }
    m_dataSetName=(m_rws->data(weightedName.Data()))->GetName();

    RooArgList weightList=splot->GetSWeightVars();
    RooArgSet* weights=(RooArgSet*)(&weightList);
    if (!weights)
    {
      std::stringstream msg;
      msg << "Failed to get RooArgSet of sWeight variables";
      throw GeneralException("RooPhysFitter::CalculateSWeights",
                             msg.str());
    }

    if (m_rws->defineSet(m_sWeightVarSetName, *weights))
    {
        throw WSImportFailure("RooPhysFitter::CalculateSWeights",
                              *m_rws, *weights, m_sWeightVarSetName);
    }

    // replace current name with weighted dataset
    delete modelClone;
    modelClone=0;
    delete splot;
    splot=0;
}


// Add dummy sWeights. The yieldName should be the name of the signal
// yield variable for that species. This will be assigned a weight of one.
// All other yields be assigned a weight of zero.
// One reason for using this method would be to assign dummy weights to 
// signal-associated Monte Carlo so that the selection code can be used
// on data and MC.
// if no newName is specified, then the dataset with weights will be called
// {origName}_withWeights, where {origName} is the name of the input dataset
void RooPhysFitter::CreateDummySWeights(const char* sVariable,
                                        Float_t weight,
                                        const char* newName,
                                        Bool_t appendToDataSet)
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::CreateDummySWeights",
                           "No RooWorkspace object is defined!");
  }
  RooDataSet* rds = (RooDataSet*)m_rws->data(m_dataSetName);
  if (!rds)
  {
    throw WSRetrievalFailure("RooPhysFitter::CreateDummySWeights"
                             ,*m_rws, m_dataSetName, "RooDataSet");
  }

  TString weightedName=newName;
  if (!appendToDataSet) {
    if (strcmp(newName, m_dataSetName)==0)
    {
      std::stringstream msg;
      msg << "Requested RooDataSet name " << newName 
          << " is the same as the current dataset";
      throw GeneralException("RooPhysFitter::CalculateSWeights",
                             msg.str());
    }
    if (!newName||strcmp(newName,"")==0)
    {
      weightedName.Form("%s_withWeights", rds->GetName());
      std::cout << "WARNING: No new RooDataSet name specified for "
                << " RooDataSet with weights. "
                << "Will use the name " << weightedName << std::endl;
    }
  }
  
  RooDataSet* rds_withWeights = NULL;
  if (appendToDataSet) rds_withWeights = rds;
  else rds_withWeights=(RooDataSet*)rds->Clone(weightedName.Data());
  
  RooRealVar sWeight(sVariable, "", weight);
  rds_withWeights->addColumn(sWeight);
 
  if (!appendToDataSet) {
    if(m_rws->import(*rds_withWeights))
    {
      throw WSImportFailure("RooPhysFitter::CalculateSWeights",
                            *m_rws, *rds_withWeights);
    }
    m_dataSetName=(m_rws->data(weightedName.Data()))->GetName();
  }
  else {
    if(m_rws->import(sWeight))
    {
      throw WSImportFailure("RooPhysFitter::CalculateSWeights",
                            *m_rws, sWeight);
    }
  }
  
  if (m_rws->extendSet(m_sWeightVarSetName, sVariable))
  {
    throw WSImportFailure("RooPhysFitter::CalculateSWeights",
                          *m_rws, m_sWeightVarSetName, sVariable, kFALSE);
  }
}

// Create a weighted dataset for a given sWeight species (sVariable).
// Note that the sWeight variables are named {yieldName}_sw,
// where {yieldName} is the name of the yield for a given species
// If saveToWS is false, then the dataset is returned (note it should be
// manually deleted), otherwise, a NULL pointer is returned, and the dataset
// is imported into the workspace
RooDataSet* RooPhysFitter::CreateWeightedDataSet(const char* newName,
        const char* sVariable, const char* fitName, 
        //const char* dataSetWithWeightsName,
        Bool_t saveToWS)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::CreateWeightedDataSet",
                               "No RooWorkspace object is defined!");
    }
    /*
    TString weightedName=dataSetWithWeightsName;
    if (!dataSetWithWeightsName||strcmp(dataSetWithWeightsName,"")==0)
    {
        weightedName.Form("%s_withWeights", m_dataSetName);
        std::cout << "WARNING: No new RooDataSet name specified for "
        << " RooDataSet with weights. "
        << "Will use the name " << weightedName << std::endl;
    }
    */
    if (fitName&&strcmp(fitName,"")!=0)
    {
        std::cout << "INFO: Loading snapshot " << fitName << std::endl;
        if (!m_rws->loadSnapshot(fitName))
        {
            throw WSRetrievalFailure("RooPhysFitter::CreateWeightedDataSet",
                                     *m_rws, fitName, "fit snapshot");
        }
    }
    RooDataSet* rds = (RooDataSet*)m_rws->data(m_dataSetName);
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::CreateWeightedDataSet"
                                 ,*m_rws, m_dataSetName, "RooDataSet");
    }
    RooRealVar* sVar=0;
    std::string varname=sVariable;
    sVar = m_rws->var(varname.c_str());
    if (!sVar)
    {
        varname+="_sw";
        sVar = m_rws->var(varname.c_str());
        if (!sVar)
        {
            throw WSRetrievalFailure("RooPhysFitter::CreateWeightedDataSet"
                                     ,*m_rws, sVariable, "RooRealVar");
        }
    }
    RooDataSet* rds_ws = new RooDataSet(newName, rds->GetTitle()
                                        ,rds, *(rds->get()), 0, varname.c_str());
    if (saveToWS)
    {
        if(m_rws->import(*rds_ws))
        {
            delete rds_ws;
            throw WSImportFailure("RooPhysFitter::CreateWeightedDataSet"
                                  ,*m_rws, *rds_ws);
        }
        delete rds_ws;
        rds_ws=0;
    }
    return rds_ws;
}


// Save a weighted dataset for each sWeight species. By default, the new
// datasets will be of the form {origName}_{sVariable}, where {origName}
// is the name of the original RooDataSet, and sVariable is the name of the
//  sWeight for a particular species. If prefix is specified, then {origName}
// is replace by prefix. If saveToWS is false, then the dataset is returned
// (note it should be manually deleted), otherwise, a NULL pointer is returned,
//  and the dataset is imported into the workspace
void RooPhysFitter::SaveWeightedDataSets(const char* fitName, 
//const char* dataSetWithWeightsName,
        const char* prefix)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::SaveWeightedDataSets",
                               "No RooWorkspace object is defined!");
    }
    const RooArgSet* weights = m_rws->set(m_sWeightVarSetName);
    if (!weights)
    {
        throw WSRetrievalFailure("RooPhysFitter::SaveWeightedDataSets",
                                 *m_rws, m_sWeightVarSetName, "RooArgSet");
    }
    /*
    TString weightedName=dataSetWithWeightsName;
    if (!dataSetWithWeightsName||strcmp(dataSetWithWeightsName,"")==0)
    {
        weightedName.Form("%s_withWeights", m_dataSetName);
        std::cout << "WARNING: No new RooDataSet name specified for "
        << " RooDataSet with weights. "
        << "Will use the name " << weightedName << std::endl;
    }
    */
    if (fitName&&strcmp(fitName,"")!=0)
    {
        std::cout << "INFO: Loading snapshot " << fitName << std::endl;
        if (!m_rws->loadSnapshot(fitName))
        {
            throw WSRetrievalFailure("RooPhysFitter::SaveWeightedDataSets",
                                     *m_rws, fitName, "fit snapshot");
        }
    }
    RooDataSet* rds = (RooDataSet*)m_rws->data(m_dataSetName);
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::SaveWeightedDataSets"
                                 ,*m_rws, m_dataSetName, "RooDataSet");
    }
    const char* oldName=rds->GetName();
    TIterator *it = weights->createIterator();
    RooRealVar* v;
    while ( (v=(RooRealVar*)it->Next()) )
    {
      std::string sVariable=v->GetName();
      std::string newName=(!prefix||strcmp(prefix,"")==0)?oldName:prefix;
      newName+="_";
      newName+=sVariable;
      this->CreateWeightedDataSet(newName.c_str(), sVariable.c_str(), fitName, kTRUE);
    }
}


// Plot the observable with name 'name', showing the fit results
// NB. The variable must be an observable in the model PDF
//
// Optionally, a range can be specified. This will be used to extrapolate the
// yields to the given range. The function will raise an exception if the
// range does not exist for the given observable.
//
// By default, the extrapolated yields will be labelled "yieldTitle (range)".
// If rangeTitle is specified, then the label will be "yieldTitle (rangeTitle)"
//
// If sumWErrors is true, then plot sum-of-weights-squared errors (default is
// Poissonian errors). RooFit will force sum-of-weights-squared errors if the
// dataset is weighted.
//
// If printChi2 is true, then the chi^2, and number of degrees of freedom
// of the fit are shown.
//
// If a chi^2 test statistic has been set, then this will be calculated,
// and the p-value and significance will be determined and plotted
//
// If the fit was produced in extended mode, and the chi^2 or a
// chi^2 test statistic have been requested, then extendedMode should
// be set to true.
//
// The function returns a RooPlot pointer. Note that the user is responsible
//for deleting this object.
RooPlot* RooPhysFitter::PlotFitResults(const char* name,
                                       const char* fitName,
                                       const char* range,
                                       const char* rangeTitle,
                                       Bool_t sumW2Errors,
                                       Bool_t printChi2,
                                       Bool_t extendedMode,
                                       Int_t nChi2FitCores)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::PlotFitResults",
                               "No RooWorkspace object is defined!");
    }
    // check that name is specified
    if (!name||strcmp(name,"")==0)
    {
        throw GeneralException("RooPhysFitter::PlotFitResults",
                               "No variable name has been specified!");
    }

    // get the dataset
    RooDataSet* rds = (RooDataSet*)m_rws->data(m_dataSetName);
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotFitResults"
                                 ,*m_rws, m_dataSetName, "RooDataSet");
    }

    // get the model PDF
    RooAddPdf* model = (RooAddPdf*)m_rws->pdf(m_modelName);
    if (!model)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotFitResults"
                                 ,*m_rws, m_modelName, "RooAddPdf");
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables(*rds);
    assert(observables);

    // get the plot variable
    RooRealVar* var = m_rws->var(name);
    if (!var)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotFitResults"
                                 ,*m_rws, name, "RooRealVar");
    }

    // check that the plot variable is in the list of observables
    if (!observables->contains(*var))
    {
        std::stringstream msg;
        msg << "Plot variable " << name << " is not in the list of observables "
        << "for model PDF " << model->GetName();
        throw GeneralException("RooPhysFitter::PlotFitResults", msg.str());
    }
    if (fitName&&strcmp(fitName,"")!=0)
    {
      if (!m_rws->loadSnapshot(fitName))
      {
        throw WSRetrievalFailure("RooPhysFitter::PlotFitResults"
                                 ,*m_rws, fitName, "fit snapshot");
      }
    }

    // get the plot parameters
    const RooArgSet* paramsTmp = m_rws->set(m_plotParamsSetName);
    if (!paramsTmp)
    {
      paramsTmp = m_rws->set(m_plotParamsSetName);
      if (!paramsTmp)
      {
        paramsTmp = model->getParameters(*rds);
        if (!paramsTmp)
        {
          throw WSRetrievalFailure("RooPhysFitter::PlotFitResults"
                                   ,*m_rws, m_plotParamsSetName, "RooArgSet");
        }
      }
    }
    // get the RooFitResult
    const RooFitResult* rfres = this->GetFitResult(fitName);
    
    const RooArgList& yieldList = model->coefList();
    const RooArgList& pdfList = model->pdfList();

    const RooArgSet& yields(yieldList);

    // clone the plot parameter set
    RooArgSet* params = (RooArgSet*)paramsTmp->Clone("params");

    // add yields (ignore duplicate warnings)
    params->add(yields, kTRUE);

    // make the RooPlot
    Int_t nPlotBins=m_plotBinMap.find(name)==m_plotBinMap.end()?m_globalPlotBins:m_plotBinMap[name];

    RooPlot* rp = var->frame(RooFit::Bins(nPlotBins));
    if (!rp)
    {
      std::stringstream msg;
      msg << "Failed to get RooPlot for RooRealVar " << name;
      throw GeneralException("RooPhysFitter::PlotFitResults", msg.str());
    }
    RooAbsData::ErrorType errorType = (!sumW2Errors)?RooAbsData::Poisson
                                      :RooAbsData::SumW2;
    rp->GetYaxis()->SetTitleOffset(1.2);
    if (strcmp(var->GetTitle(),"")==0) {
      rp->GetXaxis()->SetTitle(TString::Format("%s %s", var->GetName(),
                                               rp->GetXaxis()->GetTitle()));
    }
    
    RooLinkedList argList;
    RooCmdArg* arg = 0;
    try {
      arg = new RooCmdArg(RooFit::LineColor(m_dataSetLineColor));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    
    try {
      arg = new RooCmdArg(RooFit::LineStyle(m_dataSetLineStyle));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::LineWidth(m_dataSetLineWidth));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::MarkerColor(m_dataSetMarkerColor));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::MarkerStyle(m_dataSetMarkerStyle));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::MarkerSize(m_dataSetMarkerSize));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::FillColor(m_dataSetFillColor));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::FillStyle(m_dataSetFillStyle));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::DrawOption(m_dataSetDrawOption));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
      arg = new RooCmdArg(RooFit::DataError(errorType));
      argList.Add(arg->Clone());
      delete arg;
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new RooCmdArg");
    }
    rds->plotOn(rp, argList);

    model->plotOn(rp, RooFit::LineColor(m_modelLineColor),
                  RooFit::LineStyle(m_modelLineStyle),
                  RooFit::LineWidth(m_modelLineWidth));


    // show the PDF components
    if (m_pdfComponents.size()>0)
    {
        for (std::vector<std::string>::iterator compName=m_pdfComponents.begin();
                compName!=m_pdfComponents.end(); ++compName)
        {

            assert(m_pdfLineColorMap.find(*compName)!=m_pdfLineColorMap.end());
            assert(m_pdfLineStyleMap.find(*compName)!=m_pdfLineStyleMap.end());
            assert(m_pdfLineWidthMap.find(*compName)!=m_pdfLineWidthMap.end());

            Color_t col = m_pdfLineColorMap[*compName];
            Style_t style = m_pdfLineStyleMap[*compName];
            Width_t width = m_pdfLineWidthMap[*compName];

            model->plotOn(rp, RooFit::Components(compName->c_str()),
                          RooFit::LineColor(col), RooFit::LineStyle(style),
                          RooFit::LineWidth(width));
        }
    }

    TPaveText *pv =0;
    try {
      pv=new TPaveText(m_paramBoxX1, m_paramBoxY1
                       ,m_paramBoxX2, m_paramBoxY2, "BRNDC");
    }
    catch (std::bad_alloc& e) {
      throw GeneralException("RooPhysFitter::PlotFitResults",
                             "Got std::bad_alloc when creating new TPaveText");
    }
    pv->SetName(m_paramBoxName);
    pv->SetFillColor(0);
    pv->SetBorderSize(0);
    pv->SetTextAlign(m_paramBoxTextAlign);
    pv->SetTextSize(m_paramBoxTextSize);
    pv->SetFillStyle(4001);

   
    // add parameter box
    TIterator *pIter = params->createIterator();
    RooAbsReal *pvar;
    while ( (pvar=(RooAbsReal*)pIter->Next()) )
    {
      assert(pvar);
      // swap name and title if title is specified, 
      // else use the original name
      const char* ptitle="";
      if (pvar->GetTitle()!=0&&strcmp(pvar->GetTitle(),"")!=0)
      {
        ptitle=pvar->GetTitle();
      }
      else
      {
        ptitle=pvar->GetName();
      }
      
      RooAbsReal* pvarTmp = (RooAbsReal*)pvar->Clone(ptitle);
      assert(pvarTmp);
      
      TString *formatted=this->format(pvarTmp,rfres,1,"NEPLU");
      //TString *formatted=pvarTmp->format(1, "NEPLU");
      pv->AddText(formatted->Data());
      
      delete formatted;
      formatted=0;
      delete pvarTmp;
      pvarTmp=0;
    }
    if (range&&strcmp(range,"")!=0)
    {
      //        TIterator* it = yields.createIterator();
        RooAbsPdf* pdfComp=0;
        RooRealVar* yield=0;
        RooRealVar *fracInRange=0;
        RooRealVar *yieldInRange=0;
        TString yieldName="";
        //        TString yieldTitle="";

        for (Int_t i=0; i<pdfList.getSize(); ++i) 
        {
          yield=(RooRealVar*)yieldList.at(i);
          pdfComp=(RooAbsPdf*)pdfList.at(i);
          assert(yield);
          assert(pdfComp);
          fracInRange = (RooRealVar*)pdfComp->createIntegral(
                              *observables,
                              RooFit::NormSet(*observables),
                              RooFit::Range(range));
          assert(fracInRange);
          // yieldName.Form("%s_inRange", yield->GetName());
          if (!rangeTitle||strcmp(rangeTitle,"")==0) {
            yieldName.Form("%s (in '%s' range)", yield->GetTitle(),
                           range);
          }
          else {
            yieldName.Form("%s (%s)", yield->GetTitle(),
                           rangeTitle);
          }
          try {
            yieldInRange = new RooRealVar(yieldName.Data(), ""
                                          , 0, rds->numEntries());
          }
          catch (std::bad_alloc& e) {
            std::stringstream msg;
            msg << "Got std::bad_alloc when creating new RooRealVar "
                << yieldName;
            throw GeneralException("RooPhysFitter::PlotFitResults",
                                   msg.str());
          }
          yieldInRange->setVal(fracInRange->getVal()*yield->getVal());
          yieldInRange->setError(fracInRange->getVal()*yield->getError());
          TString *formatted=yieldInRange->format(1, "NEPLU");
          pv->AddText(formatted->Data());
          delete formatted;
          formatted=0;
          delete yieldInRange;
          yieldInRange=0;
          delete fracInRange;
          fracInRange=0;
        }
    }

    if (printChi2||m_plotTestStat!=RooPhysFitter::NoTestStat)
    {

        TString binnedName=TString::Format("%s_binned", rds->GetName());
        TString binnedTitle=TString::Format("%s_binned", rds->GetTitle());

        RooArgSet* obsCpy = (RooArgSet*)observables->Clone();
        TIterator* it = obsCpy->createIterator();
        RooRealVar* var;
        while ( (var=(RooRealVar*)it->Next()) )
        {
          if (m_chi2BinMap.find(var->GetName())==m_chi2BinMap.end())
          {
            var->setBins(m_globalChi2Bins);
          }
          else
          {
            var->setBins(m_chi2BinMap[var->GetName()]);
          }
        }
        
        RooDataHist* data_binned = 0;
        try {
        data_binned = new RooDataHist(binnedName.Data(),
                                      binnedTitle.Data(),
                                      *obsCpy, *rds);
        }
        catch (std::bad_alloc& e) {
          std::stringstream msg;
          msg << "Got std::bad_alloc when creating new RooDataHist "
              << binnedName;
          throw GeneralException("RooPhysFitter::PlotFitResults",
                                 msg.str());
        }
        if (printChi2)
        {
            RooGaussianChi2Var chi2Var("chi2Var", "",
                                       *((RooAbsPdf*)model->cloneTree()),
                                       *data_binned,
                                       RooFit::Extended(extendedMode),
                                       RooFit::SumW2Error(sumW2Errors),
                                       RooFit::NumCPU(nChi2FitCores));
            Double_t chi2 = chi2Var.getVal();

            Int_t nDOF = GetNDOF(data_binned, model, kTRUE);

            TString text = TString::Format("#chi^{2} / d.o.f. = %.3f/%d = %.3f",
                                           chi2, nDOF, chi2/nDOF);
            std::cout << text << std::endl;
            TString text_pval = TString::Format("p-value = %.3f", GetPValFromChi2Stat(chi2, nDOF));
            std::cout << text_pval << std::endl;
            pv->AddText(text.Data());
        }

        if (m_plotTestStat!=RooPhysFitter::NoTestStat)
        {
            // calculate the test statistic
            RooAbsTestStatistic* testStat = 0;
            const char* statName="";
            if (m_plotTestStat==RooPhysFitter::PearsonsChi2)
            {
                statName="PearsonsChi2";
                try {
                  testStat = new RooPearsonsChi2Var(statName, "",
                                                    *((RooAbsPdf*)model->cloneTree()),
                                                    *data_binned,
                                                    RooFit::Extended(extendedMode),
                                                    RooFit::SumW2Error(sumW2Errors),
                                                    RooFit::NumCPU(nChi2FitCores));
                }
                catch (std::bad_alloc& e) {
                  std::stringstream msg;
                  msg << "Got std::bad_alloc when creating new RooPearsonsChi2Var "
                      << statName;
                  throw GeneralException("RooPhysFitter::PlotFitResults",
                                         msg.str());
                }
            }
            else if (m_plotTestStat==RooPhysFitter::YatesChi2)
            {
                statName="YatesChi2";
                try {
                  testStat = new RooYatesChi2Var(statName, "",
                                                 *((RooAbsPdf*)model->cloneTree()),
                                                 *data_binned,
                                                 RooFit::Extended(extendedMode),
                                                 RooFit::SumW2Error(sumW2Errors),
                                                 RooFit::NumCPU(nChi2FitCores));
                }
                catch (std::bad_alloc& e) {
                  std::stringstream msg;
                  msg << "Got std::bad_alloc when creating new RooYatesChi2Var "
                      << statName;
                  throw GeneralException("RooPhysFitter::PlotFitResults",
                                         msg.str());
                }
            }
            else if (m_plotTestStat==RooPhysFitter::LLRatio)
            {
                statName="LLRatio";
                try {
                  testStat = new RooLLRatioVar(statName, "",
                                               *((RooAbsPdf*)model->cloneTree()),
                                               *data_binned,
                                               RooFit::Extended(extendedMode),
                                               RooFit::SumW2Error(sumW2Errors),
                                               RooFit::NumCPU(nChi2FitCores));
                }
                catch (std::bad_alloc& e) {
                  std::stringstream msg;
                  msg << "Got std::bad_alloc when creating new RooLLRatioVar "
                      << statName;
                  throw GeneralException("RooPhysFitter::PlotFitResults",
                                         msg.str());
                }
            }

            Double_t chi2 = testStat->getVal();
            Int_t nDOF = GetNDOF(data_binned, model, kTRUE);
            Double_t pVal=0;
            if (m_chi2MCStudyFlag==kFALSE)
            {
                pVal = GetPValFromChi2Stat(chi2, nDOF);
            }
            else
            {
                pVal = GetPValFromChi2MCToyStudy(*((RooAbsPdf*)model->cloneTree()),
                                                 *data_binned,
                                                 m_nChi2Toys, m_plotTestStat,
                                                 RooFit::Extended(extendedMode),
                                                 RooFit::SumW2Error(sumW2Errors),
                                                 RooFit::NumCPU(nChi2FitCores));
            }

            Double_t signif = GetSignifFromPVal(pVal);

            TString text1 = TString::Format("#Chi^{2} (%s)/d.o.f. = %.3f/%d",
                                            statName, chi2, nDOF);


            TString text2 = "";
            if (m_chi2MCStudyFlag==kFALSE)
            {
                text2 = TString::Format("p-value = %.4f, signif. = %.3f #sigma", pVal, signif);
            }
            else
            {
                text2 = TString::Format("p-value (nToys=%d)= %.4f, signif. = %.3f #sigma",
                                        m_nChi2Toys, pVal, signif);
            }
            pv->AddText(text1.Data());
            pv->AddText(text2.Data());
            delete testStat;
        }
        delete data_binned;
    }
    rp->addObject(pv);

    return rp;
}


// Plot the specified variable with name 'name'
// NB. The variable must exist in the dataset
//
// If a range is specified, then the variable is plotted over this range.
// This function will raise an exception is the range does not exist
//
// If sumWErrors is true, then plot sum-of-weights-squared errors (default is
// Poissonian errors). RooFit will force sum-of-weights-squared errors if
// the dataset is weighted.
//
// If a RooPlot pointer is given as argument, then the variable is plotted
// on the existing RooPlot
//
// If scale is >0, then the plot will be rescaled by the specified amount
//
// If newname is set, then the dataset is renamed in the RooPlot.
// This is useful if several datasets need to be plotted on the same RooPlot
//
// If ymin/ymax is >0, then the minimum/maximum of the plot is set to
// this value, overriding RooPlot's default values
RooPlot* RooPhysFitter::PlotVariable(const char* name, const char* cut,
                                     const char* range,
                                     Bool_t sumW2Errors, RooPlot* frame,
                                     Double_t scale, const char* newname,
                                     Double_t ymin, Double_t ymax)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::PlotVariable",
                               "No RooWorkspace object is defined!");
    }
    // check that name is specified
    if (!name||strcmp(name,"")==0)
    {
        throw GeneralException("RooPhysFitter::PlotVariable",
                               "No variable name has been specified!");
    }

    const RooRealVar* var = m_rws->var(name);
    if (!var)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotVariable"
                                 ,*m_rws, name, "RooRealVar");
    }
    RooDataSet* rds = (RooDataSet*)m_rws->data(m_dataSetName);
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotVariable"
                                 ,*m_rws, m_dataSetName, "RooDataSet");
    }

    Int_t nPlotBins=m_plotBinMap.find(name)==m_plotBinMap.end()?m_globalPlotBins:m_plotBinMap[name];

    // get the RooPlot object
    RooPlot* rp=0;

    if (!frame)
    {
        rp = var->frame(RooFit::Bins(nPlotBins), RooFit::Range(range));
        if (!rp)
        {
          std::stringstream msg;
          msg << "Failed to get RooPlot for RooRealVar " << var->GetName();
          throw GeneralException("RooPhysFitter::PlotVariable", msg.str());
        }
        if (strcmp(var->GetTitle(),"")==0) {
          rp->GetXaxis()->SetTitle(TString::Format("%s %s", var->GetName(),
                                                   rp->GetXaxis()->GetTitle()));
        }
    }

    else
    {
        rp = frame;
    }
    
    RooAbsData::ErrorType errorType = (!sumW2Errors)?RooAbsData::Poisson
                                      :RooAbsData::SumW2;

    if (scale<0)
        scale=0;

    RooLinkedList argList;
    RooCmdArg* arg = 0;

    arg = new RooCmdArg(RooFit::LineColor(m_dataSetLineColor));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::LineStyle(m_dataSetLineStyle));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::LineWidth(m_dataSetLineWidth));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::MarkerColor(m_dataSetMarkerColor));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::MarkerStyle(m_dataSetMarkerStyle));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::MarkerSize(m_dataSetMarkerSize));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::FillColor(m_dataSetFillColor));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::FillStyle(m_dataSetFillStyle));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::DrawOption(m_dataSetDrawOption));
    argList.Add(arg->Clone());
    delete arg;

    arg = new RooCmdArg(RooFit::DataError(errorType));
    argList.Add(arg->Clone());
    delete arg;

    if (scale!=0)
    {
        arg = new RooCmdArg(RooFit::Rescale(scale));
        argList.Add(arg->Clone());
        delete arg;
    }

    if (strcmp(newname,"")!=0)
    {
        arg = new RooCmdArg(RooFit::Name(newname));
        argList.Add(arg->Clone());
        delete arg;
    }
    if (strcmp(cut,"")!=0) {
      arg = new RooCmdArg(RooFit::Cut(cut));
      argList.Add(arg->Clone());
      delete arg;
    }
    
    rp->GetYaxis()->SetTitleOffset(1.2);

    rds->plotOn(rp, argList);

    rp->SetMaximum(rp->GetMaximum());

    if (scale!=0)
    {
        rp->SetMaximum(rp->GetMaximum()*scale);
        rp->SetMinimum(rp->GetMinimum()*scale);
    }

    if (ymax!=0)
        rp->SetMaximum(ymax);
    if (ymin!=0)
        rp->SetMinimum(ymin);

    return rp;
}

RooPlot* RooPhysFitter::PlotLikelihoodScan(const char* name,
        const char* fitName,
        const char* range,
        Int_t nCores,
        Bool_t plotProfileLL,
        Color_t llColor,
        Color_t pllColor)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::PlotLikelihoodScan",
                               "No RooWorkspace object is defined!");
    }
    // check that name is specified
    if (!name||strcmp(name,"")==0)
    {
        throw GeneralException("RooPhysFitter::PlotLikelihoodScan",
                               "No variable name has been specified!");
    }

    const RooRealVar* var = m_rws->var(name);
    if (!var)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotLikelihoodScan",
                                 *m_rws, name, "RooRealVar");
    }

    RooDataSet* rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
    if (!rds)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotLikelihoodScan",
                                 *m_rws, m_dataSetName, "RooDataSet");
    }

    RooAddPdf* model = dynamic_cast<RooAddPdf*>(m_rws->pdf(m_modelName));
    if (!model)
    {
        throw WSRetrievalFailure("RooPhysFitter::PlotLikelihoodScan",
                                 *m_rws, m_modelName, "RooAddPdf");
    }

    // check that the variable is a parameter in the model PDF
    const RooArgSet* params = model->getParameters(*rds);
    assert(params);
    if (!params->contains(*var))
    {
      std::stringstream msg;
      msg << var->GetName() << " not a parameter of the model PDF "
          << model->GetName();
      throw GeneralException("RooPhysFitter::PlotLikelihoodScan",
                             msg.str());
    }
    if (fitName&&strcmp(fitName,"")!=0)
    {
        if (!m_rws->loadSnapshot(fitName))
        {
            throw WSRetrievalFailure("RooPhysFitter::PlotLikelihoodScan"
                                     ,*m_rws, fitName, "fit snapshot");
        }
    }

    // NLL
    RooAbsReal* nll = model->createNLL(*rds, RooFit::NumCPU(nCores));
    // minimise likelikood w.r.t. all parameters before making plots
    RooMinuit(*nll).migrad();
    TString title=TString::Format("(Profile) Log likelihood for %s ", name);

    Int_t nPlotBins=m_plotBinMap.find(name)==m_plotBinMap.end()?m_globalPlotBins:m_plotBinMap[name];

    // get the RooPlot object
    RooPlot* rp = var->frame(RooFit::Bins(nPlotBins), RooFit::Range(range),
                             RooFit::Title(title.Data()),
                             RooFit::LineColor(llColor));
    if (!rp)
    {
        std::stringstream msg;
        msg << "Failed to get RooPlot for RooRealVar " << name;
        throw GeneralException("RooPhysFitter::PlotProfileLikelihood",
                               msg.str());
    }
    if (plotProfileLL)
    {
        RooArgSet vars(*var);
        RooAbsReal* pll=nll->createProfile(vars);
        pll->plotOn(rp, RooFit::LineColor(pllColor));
    }
    return rp;
}

// Create the named set "Plot Parameters" (or name set by the
// SetPlotParameterSetName method) with contents from the colon-separated list
// contentList. This is used to indicate what variables should be plotted.
// If this set does not exist in the workspace, then all parameters in the
// pdf are plotted
void RooPhysFitter::SetPlotParameters(const char* contentList)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::SetPlotParameters",
                               "No RooWorkspace object is defined.");
    }
    if (m_rws->defineSet(m_plotParamsSetName, contentList))
    {
        throw WSImportFailure("RooPhysFitter::SetPlotParameters",
                              *m_rws, m_plotParamsSetName, contentList, kTRUE);
    }
}

// Add the parameter paramName to the named set "Plot Parameters"
// (or name set by the SetPlotParameterSetName method)
// This is used to indicate what variables should be plotted.
// If this set does not exist in the workspace, then all parameters
// in the pdf are plotted
void RooPhysFitter::AddPlotParameter(const char* paramName)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::AddPlotParameter",
                               "No RooWorkspace object is defined!");
    }
    if (m_rws->extendSet(m_plotParamsSetName, paramName))
    {
        throw WSImportFailure("RooPhysFitter::AddPlotParameter",
                              *m_rws, m_plotParamsSetName, paramName, kFALSE);
    }
}

// Load the snapshot of the fit parameters given by name fitName
// Will raise an exception if the fit name does not exist in the
// workspace
void RooPhysFitter::LoadSnapshot(const char* fitName)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::LoadSnapshot",
                               "No RooWorkspace object is defined!");
    }

    if (!fitName||strcmp(fitName,"")==0)
    {
        throw GeneralException("RooPhysFitter::LoadSnapshot",
                               "No fit name given");
    }

    if (!m_rws->loadSnapshot(fitName))
    {
        throw WSRetrievalFailure("RooPhysFitter::LoadSnapshot",
                                 *m_rws, fitName, "fit snapshot");
    }
}

void RooPhysFitter::SetRange(const char* name, Float_t min, Float_t max,
                             const char* range) 
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::SetRange",
                           "No RooWorkspace object is defined!");
  }
  if (!name||strcmp(name,"")==0)
  {
    throw GeneralException("RooPhysFitter::SetRange",
                           "No variable name given");
  }
  RooRealVar* var = m_rws->var(name);
  if (!var) {
    throw WSRetrievalFailure("RooPhysFitter::SetRange", *m_rws,
                             name, "RooRealVar");
  }
  var->setRange(range,min,max);
}

// Add the plot component "name" to the list of PDF components to plot
// NB: there is no check that the PDF component exists in the RooWorkspace
void RooPhysFitter::AddPdfComponent(const char* name, Color_t lineCol,
                                    Style_t lineStyle, Width_t lineWidth)
{
    if (std::find(m_pdfComponents.begin(),
                  m_pdfComponents.end(),name)!=m_pdfComponents.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is already in the list of "
        << "components to plot";
        throw GeneralException("RooPhysFitter::AddPdfComponent", msg.str());
    }
    assert(m_pdfLineColorMap.find(name)==m_pdfLineColorMap.end());
    assert(m_pdfLineStyleMap.find(name)==m_pdfLineStyleMap.end());
    assert(m_pdfLineWidthMap.find(name)==m_pdfLineWidthMap.end());

    m_pdfComponents.push_back(name);
    m_pdfLineColorMap[name]=lineCol;
    m_pdfLineStyleMap[name]=lineStyle;
    m_pdfLineWidthMap[name]=lineWidth;
}

// set the line color, style and width of the specified PDF component
// Will raise an exception if it is not in the list of components
void RooPhysFitter::SetPdfComponentLineColor(const char* name, Color_t col)
{
    if (std::find(m_pdfComponents.begin(),
                  m_pdfComponents.end(),name)==m_pdfComponents.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
        << "components to plot";
        throw GeneralException("RooPhysFitter::SetPdfComponentLineColor",
                               msg.str());
    }
    assert(m_pdfLineColorMap.find(name)!=m_pdfLineColorMap.end());
    m_pdfLineColorMap[name]=col;
}

void RooPhysFitter::SetPdfComponentLineStyle(const char* name, Style_t style)
{
    if (std::find(m_pdfComponents.begin(),
                  m_pdfComponents.end(),name)==m_pdfComponents.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
        << "components to plot";
        throw GeneralException("RooPhysFitter::SetPdfComponentLineStyle",
                               msg.str());
    }
    assert(m_pdfLineStyleMap.find(name)!=m_pdfLineStyleMap.end());
    m_pdfLineStyleMap[name]=style;
}

void RooPhysFitter::SetPdfComponentLineWidth(const char* name, Width_t width)
{
    if (std::find(m_pdfComponents.begin(),
                  m_pdfComponents.end(),name)==m_pdfComponents.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
        << "components to plot";
        throw GeneralException("RooPhysFitter::SetPdfComponentLineWidth",
                               msg.str());
    }
    assert(m_pdfLineWidthMap.find(name)!=m_pdfLineWidthMap.end());
    m_pdfLineWidthMap[name]=width;
}


void RooPhysFitter::SetPdfComponentLineAttributes(const char* name, Color_t col,
        Style_t style, Width_t width)
{
    if (std::find(m_pdfComponents.begin(),
                  m_pdfComponents.end(),name)==m_pdfComponents.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
        << "components to plot";
        throw GeneralException("RooPhysFitter::SetPdfComponentLineAttributes",
                               msg.str());
    }
    assert(m_pdfLineColorMap.find(name)!=m_pdfLineColorMap.end());
    assert(m_pdfLineStyleMap.find(name)!=m_pdfLineStyleMap.end());
    assert(m_pdfLineWidthMap.find(name)!=m_pdfLineWidthMap.end());
    m_pdfLineColorMap[name]=col;
    m_pdfLineStyleMap[name]=style;
    m_pdfLineWidthMap[name]=width;
}

// Remove the plot component "name" from the list of PDF components to plot
// Will raise an exception if it is not in the list of components
void RooPhysFitter::RemovePdfComponent(const char* name)
{
    if (std::find(m_pdfComponents.begin(),
                  m_pdfComponents.end(),name)==m_pdfComponents.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " not in the list of "
        << "components to plot";
        throw GeneralException("RooPhysFitter::SetPdfComponentLineAttributes",
                               msg.str());
    }
    assert(m_pdfLineColorMap.find(name)!=m_pdfLineColorMap.end());
    assert(m_pdfLineStyleMap.find(name)!=m_pdfLineStyleMap.end());
    assert(m_pdfLineWidthMap.find(name)!=m_pdfLineWidthMap.end());
    m_pdfLineColorMap.erase(name);
    m_pdfLineStyleMap.erase(name);
    m_pdfLineWidthMap.erase(name);
    std::vector<std::string>::iterator it = std::find(m_pdfComponents.begin(),
                                            m_pdfComponents.end(),
                                            name);
    m_pdfComponents.erase(it);
}

// Clear the list of PDF components to plot
void RooPhysFitter::ClearPdfComponents()
{
    m_pdfComponents.clear();
    m_pdfLineColorMap.clear();
    m_pdfLineStyleMap.clear();
    m_pdfLineWidthMap.clear();
}

// set name of the model PDF (NB. the model must be a RooAddPdf instance,
// or inherit from it)
void RooPhysFitter::SetModelName(const char* name)
{
    m_modelName=name;
}

// set the dataset name (NB. the data set must be unbinned)
void RooPhysFitter::SetDataSetName(const char* name)
{
    m_dataSetName=name;
}

// Set the binnined test statistic to plot (fit results plot only)
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
void RooPhysFitter::SetChi2TestStat(RooPhysFitter::PlotChi2TestStat stat)
{
    m_plotTestStat=stat;
}

// should we perform an MC random sampling study to determine the
// goodness-of-fit?
void RooPhysFitter::SetChi2MCStudyFlag(Bool_t flag)
{
    m_chi2MCStudyFlag=flag;
}

// set the number of toys to use for the MC sampling study
void RooPhysFitter::SetNumChi2Toys(UInt_t nToys)
{
    m_nChi2Toys=nToys;
}

// set the name of the named set containing the sWeight variables
void RooPhysFitter::SetSWeightSetName(const char* name)
{
    m_sWeightVarSetName=name;
}

// set the name of the named set containing the plot parameters
void RooPhysFitter::SetPlotParameterSetName(const char* name)
{
    m_plotParamsSetName=name;
}

// set the line attributes of the model PDF
void RooPhysFitter::SetModelLineColor(Color_t col)
{
    m_modelLineColor=col;
}

void RooPhysFitter::SetModelLineStyle(Style_t style)
{
    m_modelLineStyle=style;
}

void RooPhysFitter::SetModelLineWidth(Width_t width)
{
    m_modelLineWidth=width;
}

void RooPhysFitter::SetModelLineAttributes(Color_t col, Style_t style,
        Width_t width)
{
    m_modelLineColor=col;
    m_modelLineStyle=style;
    m_modelLineWidth=width;
}

// set the dataset line attributes
void RooPhysFitter::SetDataSetLineColor(Color_t col)
{
    m_dataSetLineColor=col;
}

void RooPhysFitter::SetDataSetLineStyle(Style_t style)
{
    m_dataSetLineStyle=style;
}

void RooPhysFitter::SetDataSetLineWidth(Width_t width)
{
    m_dataSetLineWidth=width;
}

void RooPhysFitter::SetDataSetLineAttributes(Color_t col,
        Style_t style, Width_t width)
{
    m_dataSetLineColor=col;
    m_dataSetLineStyle=style;
    m_dataSetLineWidth=width;
}

// set the dataset marker attributes
void RooPhysFitter::SetDataSetMarkerColor(Color_t col)
{
    m_dataSetMarkerColor=col;
}

void RooPhysFitter::SetDataSetMarkerStyle(Style_t style)
{
    m_dataSetMarkerStyle=style;
}

void RooPhysFitter::SetDataSetMarkerSize(Size_t size)
{
    m_dataSetMarkerSize=size;
}

void RooPhysFitter::SetDataSetMarkerAttributes(Color_t col,
        Style_t style, Size_t size)
{
    m_dataSetMarkerColor=col;
    m_dataSetMarkerStyle=style;
    m_dataSetMarkerSize=size;
}

// set the dataset fill attributes
void RooPhysFitter::SetDataSetFillColor(Color_t col)
{
    m_dataSetFillColor=col;
}

void RooPhysFitter::SetDataSetFillStyle(Style_t style)
{
    m_dataSetFillStyle=style;
}
void RooPhysFitter::SetDataSetFillAttributes(Color_t col,
        Style_t style)
{
    m_dataSetFillColor=col;
    m_dataSetFillStyle=style;
}

// set the dataset draw options (see TGraphPainter for details)
void RooPhysFitter::SetDataSetDrawOption(const char* opt)
{
    m_dataSetDrawOption=opt;
}

// set the parameter box attributes
void RooPhysFitter::SetParamBoxX1(Float_t x)
{
  if (x>1||x<0) {
    std::stringstream msg;
    msg << "New value for parameter box X1 (" 
        << x << ") is out of range";
    throw GeneralException("RooPhysFitter::SetParamBoxX1",
                           msg.str());
  }
  if (x>m_paramBoxX2) {
    std::stringstream msg;
    msg << "New value for parameter box X1 (" 
        << x << ") greater than parameter box X2 ("
        << m_paramBoxX2 << ")";
    throw GeneralException("RooPhysFitter::SetParamBoxX1",
                           msg.str());
  }
  m_paramBoxX1=x;
}

void RooPhysFitter::SetParamBoxX2(Float_t x)
{
  if (x>1||x<0) {
    std::stringstream msg;
    msg << "New value for parameter box X2 (" 
        << x << ") is out of range";
    throw GeneralException("RooPhysFitter::SetParamBoxX2",
                           msg.str());
  }
  if (x<m_paramBoxX1) {
    std::stringstream msg;
    msg << "New value for parameter box X2 (" 
        << x << ") less than parameter box X1 ("
        << m_paramBoxX1 << ")";
    throw GeneralException("RooPhysFitter::SetParamBoxX2",
                           msg.str());
  }
  m_paramBoxX2=x;
}

void RooPhysFitter::SetParamBoxY1(Float_t x)
{
 if (x>1||x<0) {
    std::stringstream msg;
    msg << "New value for parameter box Y1 (" 
        << x << ") is out of range";
    throw GeneralException("RooPhysFitter::SetParamBoxY1",
                           msg.str());
  }
  if (x>m_paramBoxX2) {
    std::stringstream msg;
    msg << "New value for parameter box Y1 (" 
        << x << ") greater than parameter box Y2 ("
        << m_paramBoxY2 << ")";
    throw GeneralException("RooPhysFitter::SetParamBoxY1",
                           msg.str());
  }
  m_paramBoxY1=x;
}

void RooPhysFitter::SetParamBoxY2(Float_t x)
{
  if (x>1||x<0) {
    std::stringstream msg;
    msg << "New value for parameter box Y2 (" 
        << x << ") is out of range";
    throw GeneralException("RooPhysFitter::SetParamBoxY2",
                           msg.str());
  }
  if (x<m_paramBoxY1) {
    std::stringstream msg;
    msg << "New value for parameter box Y2 (" 
        << x << ") less than parameter box Y1 ("
        << m_paramBoxY1 << ")";
    throw GeneralException("RooPhysFitter::SetParamBoxY2",
                           msg.str());
  }
  m_paramBoxY2=x;
}

void RooPhysFitter::SetParamBoxTextSize(Float_t size)
{
    m_paramBoxTextSize=size;
}

void RooPhysFitter::SetParamBoxTextAlign(Int_t align)
{
    m_paramBoxTextAlign=align;
}

void RooPhysFitter::SetParamBoxName(const char* name)
{
    m_paramBoxName=name;
}

void RooPhysFitter::SetParamBoxAttributes(const char* name,
        Float_t x1, Float_t y1,
        Float_t x2, Float_t y2,
        Float_t textSize, Int_t textAlign)
{
    m_paramBoxX1=x1;
    m_paramBoxX2=x2;
    m_paramBoxY1=y1;
    m_paramBoxY2=y2;
    m_paramBoxTextSize=textSize;
    m_paramBoxTextAlign=textAlign;
    m_paramBoxName=name;
}

// Set the number of global bins to use in subsequent plots
void RooPhysFitter::SetPlotBins(Int_t nBins)
{
    m_globalPlotBins=nBins;
}

// Set the number of bins to use in subsequent plots for the given variable
// this will override the number of global bins
void RooPhysFitter::SetPlotBins(const char* name, Int_t nBins)
{
    m_plotBinMap[name]=nBins;
}

// Set the number of global bins to use when calculating the chi2 or
// binned test statistic.
void RooPhysFitter::SetChi2Bins(Int_t nBins)
{
    m_globalChi2Bins=nBins;
}


// Set the number of global bins to use when calculating the chi2 or
// binned test statistic for the given variable.
// This will override the number of global bins
void RooPhysFitter::SetChi2Bins(const char* name, Int_t nBins)
{
    m_chi2BinMap[name]=nBins;
}

// Set the default number of bins for a given RooRealVar
// Optionally, set the number of bins for a given named range
// If you want to set asymmetric bins, then you should manipulate 
// the RooRealVar object directly using the GetVar method
// Will raise an exception if the requested variable does not exist in the
// workspace
void RooPhysFitter::SetBins(const char* name, Int_t nBins, 
                            const char* range) 
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::SetBins",
                           "No RooWorkspace object is defined!");
  }
  RooRealVar* var = m_rws->var(name);
  if (!var) {
    throw WSRetrievalFailure("RooPhysFitter::SetBins",
                             *m_rws, name, "RooRealVar");
  }
  var->setBins(nBins, range);
}

// get the yield in a given range
RooRealVar* RooPhysFitter::GetYield(const char* name, const char* range,
                                    const char* fitName, Bool_t returnClone) const
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::GetYield",
                           "No RooWorkspace object is defined!");
  }
  
  if (fitName&&strcmp(fitName,"")!=0)
  {
    if (!m_rws->loadSnapshot(fitName))
    {
      throw WSRetrievalFailure("RooPhysFitter::GetYield",
                               *m_rws, fitName, "fit snapshot");
    } 
  }
  
  // get the model PDF
  RooAddPdf* model = (RooAddPdf*)m_rws->pdf(m_modelName);
  if (!model)
  {
    throw WSRetrievalFailure("RooPhysFitter::GetYield"
                             ,*m_rws, m_modelName, "RooAddPdf");
  }  
  RooDataSet *rds = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
  if (!rds)
  {
    throw WSRetrievalFailure("RooPhysFitter::GetYield",
                             *m_rws, m_dataSetName, "RooDataSet");
  }
  // get the list of observables
  const RooArgSet* observables = model->getObservables(*rds);
  assert(observables);
  
  const RooArgList& yieldList = model->coefList();
  const RooArgList& pdfList = model->pdfList();
  
  const RooRealVar* yield = (const RooRealVar*)yieldList.find(name);
  if (!yield) {
    std::stringstream msg;
    msg << "Failed to get yield name " << name << " from the list of yields";
    throw GeneralException("RooPhysFitter::GetYield", msg.str());
  }
  if (!range&&strcmp(range,"")==0) {
    if (returnClone) return (RooRealVar*)yield->Clone();
    else return (RooRealVar*)yieldList.find(name);;
  }
  
  const RooAbsPdf* pdf = (const RooAbsPdf*)pdfList.at(yieldList.index(yield));
  if (!pdf) {
    std::stringstream msg;
    msg << "Failed to get PDF component corresponding to yield " << name 
        << " from the list of PDFs";
    throw GeneralException("RooPhysFitter::GetYield", msg.str());
  }
  RooRealVar* fracInRange = (RooRealVar*)pdf->createIntegral(
      *observables, RooFit::NormSet(*observables), RooFit::Range(range));
  assert(fracInRange);
  RooRealVar* yieldInRange = new RooRealVar(TString::Format("%s_%s", name, range).Data(),
                                            yield->GetTitle(),0, rds->numEntries());
  yieldInRange->setVal(fracInRange->getVal()*yield->getVal());
  yieldInRange->setError(fracInRange->getVal()*yield->getError());
  return yieldInRange;
}

// get the currently attached workspace
const RooWorkspace* RooPhysFitter::GetWS() const
{
    return m_rws;
}
RooWorkspace* RooPhysFitter::GetWS()
{ // mutator version
    return m_rws;
}


// get a variable from the workspace by name
const RooRealVar* RooPhysFitter::GetVar(const char* name) const
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetVar",
                               "No RooWorkspace object is defined!");
    }
    const RooRealVar* var = m_rws->var(name);
    if (!var)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetVar",
                                 *m_rws, name, "RooRealVar");
    }
    return var;
}
RooRealVar* RooPhysFitter::GetVar(const char* name)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetVar",
                               "No RooWorkspace object is defined!");
    }
    RooRealVar* var = m_rws->var(name);
    if (!var)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetVar",
                                 *m_rws, name, "RooRealVar");
    }
    return var;
}


// get a dataset from the workspace by name
const RooAbsData* RooPhysFitter::GetDataSet(const char* name) const
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetDataSet",
                               "No RooWorkspace object is defined!");
    }
    const RooAbsData* rws = (const RooAbsData*)m_rws->data(name);
    if (!rws)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetDataSet",
                                 *m_rws, name, "RooAbsData");
    }
    return rws;
}
// get a dataset from the workspace by name
RooAbsData* RooPhysFitter::GetDataSet(const char* name)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetDataSet",
                               "No RooWorkspace object is defined!");
    }
    RooAbsData* rws = m_rws->data(name);
    if (!rws)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetDataSet",
                                 *m_rws, name, "RooAbsData");
    }
    return rws;
}


// get the RooDataSet with the name given by GetDataSetName()
const RooDataSet* RooPhysFitter::GetDataSet() const
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetDataSet",
                               "No RooWorkspace object is defined!");
    }
    const RooDataSet* rws = (const RooDataSet*)(m_rws->data(m_dataSetName));
    if (!rws)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetDataSet",
                                 *m_rws,m_dataSetName , "RooDataSet");
    }
    return rws;
}
RooDataSet* RooPhysFitter::GetDataSet()
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetDataSet",
                               "No RooWorkspace object is defined!");
    }
    RooDataSet* rws = dynamic_cast<RooDataSet*>(m_rws->data(m_dataSetName));
    if (!rws)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetDataSet",
                                 *m_rws, m_dataSetName, "RooDataSet");
    }
    return rws;
}


// get the PDF with the name given by GetModelName()
const RooAddPdf* RooPhysFitter::GetModel() const
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetModel",
                               "No RooWorkspace object is defined!");
    }
    const RooAddPdf* model = dynamic_cast<const RooAddPdf*>(m_rws->pdf(m_modelName));
    if (!model)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetModel",
                                 *m_rws, m_modelName, "RooAddPdf");
    }
    return model;
}
RooAddPdf* RooPhysFitter::GetModel()
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetModel",
                               "No RooWorkspace object is defined!");
    }
    RooAddPdf* model = dynamic_cast<RooAddPdf*>(m_rws->pdf(m_modelName));
    if (!model)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetModel",
                                 *m_rws, m_modelName, "RooAddPdf");
    }
    return model;
}


// get a RooAbsPdf from the workspace by name
const RooAbsPdf* RooPhysFitter::GetPdf(const char* name) const
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetPdf",
                               "No RooWorkspace object is defined!");
    }
    const RooAbsPdf* pdf = m_rws->pdf(name);
    if (!pdf)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetPdf",
                                 *m_rws, name, "RooAbsPdf");
    }
    return pdf;
}
RooAbsPdf* RooPhysFitter::GetPdf(const char* name)
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetPdf",
                               "No RooWorkspace object is defined!");
    }
    RooAbsPdf* pdf = m_rws->pdf(name);
    if (!pdf)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetPdf",
                                 *m_rws, name, "RooAbsPdf");
    }
    return pdf;
}


// Get the named set with the given name from the workspace
// Will raise an exception if the set does not exist in the workspace
const RooArgSet* RooPhysFitter::GetNamedSet(const char* name) const
{
    if (!m_rws)
    {
        throw GeneralException("RooPhysFitter::GetNamedSet",
                               "No RooWorkspace object is defined!");
    }
    const RooArgSet* set = m_rws->set(name);
    if (!set)
    {
        throw WSRetrievalFailure("RooPhysFitter::GetNamedSet",
                                 *m_rws, name, "RooArgSet");
    }
    return set;
}

const RooFitResult* RooPhysFitter::GetFitResult(const char* fitName) const 
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::GetFitResult",
                           "No RooWorkspace object is defined!");
  }
  TString fitResName=TString::Format("rfres_%s", fitName);
  const RooFitResult* rfres = (const RooFitResult*)m_rws->obj(fitResName.Data());
  if (!rfres) {
    throw WSRetrievalFailure("RooPhysFitter::GetFitResult",
                             *m_rws, fitResName.Data(), "RooFitResults");
  }
  return rfres;
}
RooFitResult* RooPhysFitter::GetFitResult(const char* fitName) 
{
  if (!m_rws)
  {
    throw GeneralException("RooPhysFitter::GetFitResult",
                           "No RooWorkspace object is defined!");
  }
  TString fitResName=TString::Format("rfres_%s", fitName);
  RooFitResult* rfres = (RooFitResult*)m_rws->obj(fitResName.Data());
  if (!rfres) {
    throw WSRetrievalFailure("RooPhysFitter::GetFitResult",
                             *m_rws, fitResName.Data(), "RooFitResults");
  }
  return rfres;
}

const char* RooPhysFitter::GetDataSetName() const {return m_dataSetName;}
const char* RooPhysFitter::GetModelName() const {return m_modelName;}
const char* RooPhysFitter::GetSWeightSetName() const {return m_sWeightVarSetName;}
const char* RooPhysFitter::GetPlotParamsSetName() const {return m_plotParamsSetName;}

// get the test statistic to plot (fit result plots only)
RooPhysFitter::PlotChi2TestStat RooPhysFitter::GetChi2TestStat() const
{
    return m_plotTestStat;
}

// should we perform an MC random sampling study to determine the
// goodness-of-fit?
Bool_t RooPhysFitter::GetChi2MCStudyFlag() const
{
    return m_chi2MCStudyFlag;
}

// get the number of toys to use for the MC sampling study
UInt_t RooPhysFitter::GetNumChi2Toys() const
{
    return m_nChi2Toys;
}

// get the line color of the model PDF
Color_t RooPhysFitter::GetModelLineColor() const
{
    return m_modelLineColor;
}
// get the line style of the model PDF
Style_t RooPhysFitter::GetModelLineStyle() const
{
    return m_modelLineStyle;
}
// get the line width of the model PDF
Width_t RooPhysFitter::GetModelLineWidth() const
{
    return m_modelLineWidth;
}

// get the line color, style and width of the specified PDF component
// Will raise an exception if it is not in the list of components
Color_t RooPhysFitter::GetPdfComponentLineColor(const char* name)
{
    if (m_pdfLineColorMap.find(name)==m_pdfLineColorMap.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is not in  the list of components to plot";
        throw GeneralException("RooPhysFitter::GetPdfComponentLineColor", msg.str());
    }
    return m_pdfLineColorMap[name];
}
Style_t RooPhysFitter::GetPdfComponentLineStyle(const char* name)
{
    if (m_pdfLineStyleMap.find(name)==m_pdfLineStyleMap.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is not in the list of components to plot";
        throw GeneralException("RooPhysFitter::GetPdfComponentLineStyle", msg.str());
    }
    return m_pdfLineStyleMap[name];
}
Width_t RooPhysFitter::GetPdfComponentLineWidth(const char* name)
{
    if (m_pdfLineWidthMap.find(name)==m_pdfLineWidthMap.end())
    {
        std::stringstream msg;
        msg << "PDF component " << name << " is not in the list of components to plot";
        throw GeneralException("RooPhysFitter::GetPdfComponentLineWidth", msg.str());
    }
    return m_pdfLineWidthMap[name];
}

// get the dataset line color
Color_t RooPhysFitter::GetDataSetLineColor() const
{
    return m_dataSetLineColor;
}
// get the dataset line style
Style_t RooPhysFitter::GetDataSetLineStyle() const
{
    return m_dataSetLineStyle;
}
// get the dataset line width
Width_t RooPhysFitter::GetDataSetLineWidth() const
{
    return m_dataSetLineWidth;
}

// get the dataset marker color
Color_t RooPhysFitter::GetDataSetMarkerColor() const
{
    return m_dataSetMarkerColor;
}
// get the dataset marker style
Style_t RooPhysFitter::GetDataSetMarkerStyle() const
{
    return m_dataSetMarkerStyle;
}
// get the dataset marker width
Size_t RooPhysFitter::GetDataSetMarkerSize() const
{
    return m_dataSetMarkerSize;
}

// get the dataset fill color
Color_t RooPhysFitter::GetDataSetFillColor() const
{
    return m_dataSetFillColor;
}
// get the dataset fill style
Style_t RooPhysFitter::GetDataSetFillStyle() const
{
    return m_dataSetFillStyle;
}

// get the dataset draw options (see TGraphPainter for details)
const char* RooPhysFitter::GetDataSetDrawOption() const
{
    return m_dataSetDrawOption;
}

// get the parameter box attributes
Float_t RooPhysFitter::GetParamBoxX1() const
{
    return m_paramBoxX1;
}
Float_t RooPhysFitter::GetParamBoxX2() const
{
    return m_paramBoxX2;
}
Float_t RooPhysFitter::GetParamBoxY1() const
{
    return m_paramBoxY1;
}
Float_t RooPhysFitter::GetParamBoxY2() const
{
    return m_paramBoxY2;
}

Float_t RooPhysFitter::GetParamBoxTextSize() const
{
    return m_paramBoxTextSize;
}
Int_t RooPhysFitter::GetParamBoxTextAlign() const
{
    return m_paramBoxTextAlign;
}
const char* RooPhysFitter::GetParamBoxName() const
{
    return m_paramBoxName;
}

// Get the number of plot bins
// If a name is specified, returns the number of bins for a given
// variable (raises an exception if the number of bins have not
// been defined for this variable)
Int_t RooPhysFitter::GetPlotBins(const char* name)
{
    if (!name||strcmp(name,"")==0)
    {
        return m_globalPlotBins;
    }
    if (m_plotBinMap.find(name)==m_plotBinMap.end())
    {
        std::stringstream msg;
        msg << "Variable " << name << " is not in the map of variable name to plot bins";
        throw GeneralException("RooPhysFitter::GetPlotBins", msg.str());
    }
    return m_plotBinMap[name];
}

// Get the number of chi2 bins
// If a name is specified, returns the number of bins for a given
// variable (raises an exception if the number of bins have not
// been defined for this variable)
Int_t RooPhysFitter::GetChi2Bins(const char* name)
{
    if (!name||strcmp(name,"")==0)
    {
        return m_globalChi2Bins;
    }
    if (m_chi2BinMap.find(name)==m_chi2BinMap.end())
    {
        std::stringstream msg;
        msg << "Variable " << name << " is not in the map of variable name to plot bins";
        throw GeneralException("RooPhysFitter::GetChi2Bins", msg.str());
    }
    return m_chi2BinMap[name];
}


// Get the number of degrees of freedom for binned GOF tests
// If ignoreEmptyBins is true, then any empty bins are ignored
// in the calculation, otherwise an exception is raised if there
// are empty bins
Int_t RooPhysFitter::GetNDOF(RooDataHist* data, RooAbsPdf* pdf, Bool_t ignoreEmptyBins)
{
    assert(data);
    assert(pdf);
    Double_t weight;
    Int_t nBins=0;
    Int_t nParams = ((pdf->getParameters(data))->selectByAttrib("Constant",kFALSE))->getSize();
    for (Int_t i=0; i<data->numEntries(); ++i)
    {
        data->get(i);
        weight=data->weight();
        if (weight<0)
        {
            std::stringstream msg;
            msg << "Got negative weight " << weight << " for bin " << i;
            throw GeneralException("RooPhysFitter::GetNDOF", msg.str());
        }
        if (weight==0)
        {
            if (!ignoreEmptyBins)
            {
                std::stringstream msg;
                msg << "Bin " << i << " has zero entries, but no request to ignore empty bins";
                throw GeneralException("RooPhysFitter::GetNDOF", msg.str());
            }
            continue;
        }
        nBins++;
    }
    return nBins-nParams-1;
}


// Get the p-value of the value of the test statistic chi2
// w.r.t. the chi^2 distribution with nDOF degrees of freedom
Double_t RooPhysFitter::GetPValFromChi2Stat(Double_t chi2, Int_t nDOF)
{
    RooRealVar chi2Var("chi2", "", 0.0, chi2);
    RooRealVar nDOFVar("nDOF", "", (Double_t)nDOF);
    RooChiSquarePdf chi2Pdf("chi2Pdf", "", chi2Var, nDOFVar);
    Double_t pVal = 1.0 - chi2Pdf.analyticalIntegral(1);
    return pVal;
}

// Get the significance (in units of sigma) of the value of the
// test statistic chi2 w.r.t. the chi^2 distribution with nDOF
// degrees of freedom
Double_t RooPhysFitter::GetSignifFromChi2Stat(Double_t chi2, Int_t nDOF)
{
    Double_t pVal = this->GetPValFromChi2Stat(chi2, nDOF);
    return this->GetSignifFromPVal(pVal);
}

// Get the significance (in units of sigma) for the given p-value/
// significance level
Double_t RooPhysFitter::GetSignifFromPVal(Double_t pVal)
{
    return std::sqrt(2)*TMath::ErfcInverse(pVal);
}

// Get the p-value based on the number of toy datasets with the same
// or more extreme value of the chi^2 test statistic as compared to
// the "true" distribution (given by the specified value for the chi^2
// test statistic and the number of degrees of freedom
Double_t RooPhysFitter::GetPValFromChi2MCToyStudy(
    RooAbsPdf& model, RooDataHist& data, Int_t nToys,
    PlotChi2TestStat statType, Bool_t extended, const char* rangeName,
    const char* addCoefRangeName, Int_t nCPU, RooFit::MPSplit interleave,
    Bool_t verbose, Bool_t splitCutRange, RooAbsData::ErrorType etype)
{
    if (nToys<=0)
    {
        std::stringstream msg;
        msg << "Got invalid number of toys" << nToys;
        throw GeneralException("RooPhysFitter::GetPValFromChi2MCToyStudy",
                               msg.str());
    }
    if (statType==RooPhysFitter::NoTestStat)
    {
        std::stringstream msg;
        msg << "Request to perform MC random sampling study when no test statistic "
        << " has been specified";
        throw GeneralException("RooPhysFitter::GetPValFromChi2MCToyStudy",
                               msg.str());
    }

    RooAbsOptTestStatistic* testStat=0;
    const char* statName="";
    if (statType==RooPhysFitter::PearsonsChi2)
    {
        statName="PearsonsChi2";
        testStat = new RooPearsonsChi2Var(statName, "", model, data,
                                          extended, rangeName,
                                          addCoefRangeName, nCPU, interleave,
                                          verbose, splitCutRange, etype
                                         );
    }
    else if (statType==RooPhysFitter::YatesChi2)
    {
        statName="YatesChi2";
        testStat = new RooYatesChi2Var(statName, "", model, data,
                                       extended, rangeName,
                                       addCoefRangeName, nCPU, interleave,
                                       verbose, splitCutRange, etype
                                      );
    }
    else if (statType==RooPhysFitter::LLRatio)
    {
        statName="LLRatio";
        testStat = new RooLLRatioVar(statName, "", model, data,
                                     extended, rangeName,
                                     addCoefRangeName, nCPU, interleave,
                                     verbose, splitCutRange, etype
                                    );
    }

    Double_t chi2 = testStat->getVal();

    if (chi2<0)
    {
        std::stringstream msg;
        msg << "Got invalid chi2 " << chi2;
        throw GeneralException("RooPhysFitter::GetPValFromChi2MCToyStudy",
                               msg.str());
    }

    Int_t nToysGteChi2=0; // number of toys with chi^2 >= "true" chi^2
    const RooArgSet* obs = model.getObservables(data);
    assert(obs);

    RooAbsOptTestStatistic* testStat_toy=0;
    RooDataHist* data_toy=0;
    const char* statName_toy="";
    Double_t chi2_toy=0;
    for (Int_t iToy=0; iToy<nToys; ++iToy)
    {
        // generate model dataset
        data_toy = model.generateBinned(*obs);//, data.numEntries());

        // create the test statistis
        if (statType==RooPhysFitter::PearsonsChi2)
        {
            statName_toy="PearsonsChi2";
            testStat_toy = new RooPearsonsChi2Var(statName_toy, "", model,
                                                  *data_toy, extended, rangeName,
                                                  addCoefRangeName, nCPU, interleave,
                                                  verbose, splitCutRange, etype
                                                 );
        }
        else if (statType==RooPhysFitter::YatesChi2)
        {
            statName_toy="YatesChi2";
            testStat_toy = new RooYatesChi2Var(statName_toy, "", model,
                                               *data_toy, extended, rangeName,
                                               addCoefRangeName, nCPU, interleave,
                                               verbose, splitCutRange, etype
                                              );
        }
        else if (statType==RooPhysFitter::LLRatio)
        {
            statName_toy="LLRatio";
            testStat_toy = new RooLLRatioVar(statName_toy, "", model,
                                             *data_toy, extended, rangeName,
                                             addCoefRangeName, nCPU, interleave,
                                             verbose, splitCutRange, etype
                                            );
        }
        chi2_toy = testStat_toy->getVal();
        if (chi2_toy>=chi2)
        {
            nToysGteChi2++;
        }
    }
    return ((Double_t)nToysGteChi2)/nToys;
}

Double_t RooPhysFitter::GetPValFromChi2MCToyStudy(
    RooAbsPdf& model, RooDataHist& data, Int_t nToys,
    PlotChi2TestStat statType, const RooCmdArg& arg1, const RooCmdArg& arg2,
    const RooCmdArg& arg3, const RooCmdArg& arg4, const RooCmdArg& arg5,
    const RooCmdArg& arg6, const RooCmdArg& arg7, const RooCmdArg& arg8,
    const RooCmdArg& arg9)
{
    if (nToys<=0)
    {
        std::stringstream msg;
        msg << "Got invalid number of toys" << nToys;
        throw GeneralException("RooPhysFitter::GetPValFromChi2MCToyStudy",
                               msg.str());
    }
    if (statType==RooPhysFitter::NoTestStat)
    {
        std::stringstream msg;
        msg << "Request to perform MC random sampling study when no test statistic "
        << " has been specified";
        throw GeneralException("RooPhysFitter::GetPValFromChi2MCToyStudy",
                               msg.str());
    }

    RooAbsOptTestStatistic* testStat=0;
    const char* statName="";
    if (statType==RooPhysFitter::PearsonsChi2)
    {
        statName="PearsonsChi2";
        testStat = new RooPearsonsChi2Var(statName, "", model, data,
                                          arg1, arg2, arg3, arg4, arg5, arg6,
                                          arg7, arg8, arg9
                                         );
    }
    else if (statType==RooPhysFitter::YatesChi2)
    {
        statName="YatesChi2";
        testStat = new RooYatesChi2Var(statName, "", model, data,
                                       arg1, arg2, arg3, arg4, arg5, arg6,
                                       arg7, arg8, arg9
                                      );
    }
    else if (statType==RooPhysFitter::LLRatio)
    {
        statName="LLRatio";
        testStat = new RooLLRatioVar(statName, "", model, data,
                                     arg1, arg2, arg3, arg4, arg5, arg6,
                                     arg7, arg8, arg9
                                    );
    }

    Double_t chi2 = testStat->getVal();

    if (chi2<0)
    {
        std::stringstream msg;
        msg << "Got invalid chi2 " << chi2;
        throw GeneralException("RooPhysFitter::GetPValFromChi2MCToyStudy",
                               msg.str());
    }

    Int_t nToysGteChi2=0; // number of toys with chi^2 >= "true" chi^2
    const RooArgSet* obs = model.getObservables(data);
    assert(obs);

    RooAbsOptTestStatistic* testStat_toy=0;
    RooDataHist* data_toy=0;
    const char* statName_toy="";
    Double_t chi2_toy=0;
    for (Int_t iToy=0; iToy<nToys; ++iToy)
    {
        // generate model dataset
        data_toy = model.generateBinned(*obs);//, data.numEntries());

        // create the test statistis
        if (statType==RooPhysFitter::PearsonsChi2)
        {
            statName_toy="PearsonsChi2";
            testStat_toy = new RooPearsonsChi2Var(statName_toy, "", model,
                                                  *data_toy, arg1, arg2, arg3, arg4,
                                                  arg5, arg6, arg7, arg8, arg9
                                                 );
        }
        else if (statType==RooPhysFitter::YatesChi2)
        {
            statName_toy="YatesChi2";
            testStat_toy = new RooYatesChi2Var(statName_toy, "", model,
                                               *data_toy, arg1, arg2, arg3, arg4,
                                               arg5, arg6, arg7, arg8, arg9
                                              );
        }
        else if (statType==RooPhysFitter::LLRatio)
        {
            statName_toy="LLRatio";
            testStat_toy = new RooLLRatioVar(statName_toy, "", model,
                                             *data_toy, arg1, arg2, arg3, arg4,
                                             arg5, arg6, arg7, arg8, arg9
                                            );
        }
        chi2_toy = testStat_toy->getVal();
        if (chi2_toy>=chi2)
        {
            nToysGteChi2++;
        }
    }
    return ((Double_t)nToysGteChi2)/nToys;
}

// create a formatting TString for an abitrary RooAbsArg object
TString* RooPhysFitter::format(RooAbsReal* var, const RooFitResult* rfit,
                               Int_t sigDigits, const char *options) const
{
  // To control what is shown use the following options
  // N = show name
  // H = hide value
  // E = show error
  // U = show unit
  //
  // To control how it is shown use these options
  // L = TLatex mode
  // X = Latex mode
  // Y = Latex table mode ( '=' replaced by '&' )
  // V = Make name \verbatim in Latex mode
  // P = use error to control shown precision
  // F = force fixed precision
  assert(var);
  assert(rfit);

  // if this is a RooRealVar, then just return the standard method
  RooRealVar* rvar = dynamic_cast<RooRealVar*>(var);
  if (rvar) return rvar->format(sigDigits, options);

  // otherwise, we have to calculate things ourself
  //cout << "format = " << options << endl ;

  // parse the options string
  TString opts(options);
  opts.ToLower();
  Bool_t showName= opts.Contains("n");
  Bool_t hideValue= opts.Contains("h");
  Bool_t showError= opts.Contains("e");
  Bool_t showUnit= opts.Contains("u");
  Bool_t tlatexMode= opts.Contains("l");
  Bool_t latexMode= opts.Contains("x");
  Bool_t latexTableMode = opts.Contains("y") ;
  Bool_t latexVerbatimName = opts.Contains("v") ;

  if (latexTableMode) latexMode = kTRUE ;
  Double_t value = var->getVal();
  Double_t error = var->getPropagatedError(*rfit);
  TString unit = var->getUnit();
  
  Bool_t hasError=(error!=0);
  
  Bool_t useErrorForPrecision= (((showError && hasError && !var->isConstant()) || opts.Contains("p")) && !opts.Contains("f")) ;
  // calculate the precision to use
  if(sigDigits < 1) sigDigits= 1;
  Int_t leadingDigitVal = 0;
  if (useErrorForPrecision) {    
    leadingDigitVal = (Int_t)floor(log10(fabs(error+1e-10)));
    if (value==0&&error==0) leadingDigitVal=0 ;
  } else {
    leadingDigitVal = (Int_t)floor(log10(fabs(value+1e-10)));
    if (value==0) leadingDigitVal=0 ;
  }
  Int_t leadingDigitErr= (Int_t)floor(log10(fabs(error)));
  Int_t whereVal= leadingDigitVal - sigDigits + 1;
  Int_t whereErr= leadingDigitErr - sigDigits + 1;
  char fmtVal[16], fmtErr[16];

  if (value<0) whereVal -= 1 ;
  snprintf(fmtVal,16,"%%.%df", whereVal < 0 ? -whereVal : 0);
  snprintf(fmtErr,16,"%%.%df", whereErr < 0 ? -whereErr : 0);
  TString *text= new TString();
  if(latexMode) text->Append("$");
  // begin the string with "<name> = " if requested
  if(showName) {
    if (latexTableMode && latexVerbatimName) {
      text->Append("\\verb+") ;
    }
    text->Append(var->getPlotLabel());
    if (latexVerbatimName) text->Append("+") ;

    if (!latexTableMode) {
      text->Append(" = ");
    } else {
      text->Append(" $ & $ ");
    }
  }

  // Add leading space if value is positive
  if (value>=0) text->Append(" ") ;

  // append our value if requested
  char buffer[256];
  if(!hideValue) {
    // The following lines are copied from
    // RooRealVar::chopAt
    // They don't actually seem to do anything,
    // but I thought I better put them in here in case
    // they're implemented in the future
    //  Double_t scale= pow(10.0,whereVal);
    //     Int_t trunc= (Int_t)floor(value/scale + 0.5);
    //     Double_t ca = (Double_t)trunc*scale;
    
    snprintf(buffer, 256,fmtVal, value);
    text->Append(buffer);
  }

  // append our error if requested and this variable is not constant
  if(hasError && showError) {
    if(tlatexMode) {
      text->Append(" #pm ");
    }
    else if(latexMode) {
      text->Append("\\pm ");
    }
    else {
      text->Append(" +/- ");
    }
    snprintf(buffer, 256,fmtErr, error);
    text->Append(buffer);
  }  

  // append our units if requested
  if(!unit.IsNull() && showUnit) {
    text->Append(' ');
    text->Append(unit);
  }
  if(latexMode) text->Append("$");
  return text;
}

//=============================================================================
// Destructor
//=============================================================================
RooPhysFitter::~RooPhysFitter()
{
    if (m_hasOwnership&&m_rws)
    {
        // If we created the RooWorkspace, then we are in charge of deleting it.
        // If it was loaded from a TFil, then it will be deleted automatically
        // when the file is closed
        delete m_rws;
        m_rws=0;
    }
    delete m_file;
    m_file=0;
}
//=============================================================================
