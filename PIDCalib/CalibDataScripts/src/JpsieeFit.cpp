// $Id: $
// Include files
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "TFile.h"
#include "TAxis.h"
#include "TString.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH2.h"
#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooPlot.h"

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "RooPhysFitter/RooJpsiMassFitter.h"

// Include files (local)
#include "CalibDataScripts/SetSpectatorVars.h"
#include "CalibDataScripts/JpsieeFit.h"
#include "CalibDataScripts/GetData.h"
#include "CalibDataScripts/LHCbStyle.h"
#include "CalibDataScripts/CheckFitResults.h"

// Namespaces
namespace bass=boost::assign;
using std::cout;
using std::cerr;
using std::endl;

// typedefs
typedef std::map<TString,TString> ssMap;
typedef std::vector<TString> sVect;

void JpsieeFit(TChain* ch,
      const char* charge,
      int bremAdded,
      const char* pName,
      const char* otherPName,
      const char* wsName,
      const char* fName,
      const char* dsName,
      const char* jpsiName,
      std::vector<fptr>& fun_vec,
      const char* index,
      Bool_t isVerbose,
      Bool_t exitOnBadFit,
      float &bkgSlope
    )
{

  //==================================================//
  // Declare and configure fitter
  //==================================================//
  RooPhysFit::RooJpsiMassFitter* massFitter
    = new RooPhysFit::RooJpsiMassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(jpsiName);
  massFitter->SetDMassSigModelName("sigModel");
  massFitter->SetDMassBkgModelName("bkgModel");
  massFitter->MakeDMassVar(
                           2400.,
                           3600.,
                           "MeV/c^{2}",
                           "m_{ee}");

  if (isVerbose) massFitter->SetPrintEntriesFlag(kTRUE);

  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout<<"Adding Spectator Vars"<<std::endl;
    (*itr)(*massFitter, "e", pName);
  }

  //==================================================//
  // Select tracks with specific charge (e- = +ve ID)
  //==================================================//
  TString chrg="";
  if(strcmp(charge, "Positive")==0)
    chrg = "1";
  else if(strcmp(charge,"Negative")==0)
    chrg = "-1";
  else {
    std::cerr << "J/psi " << charge << " " << pName
              << "fit: Unexpected charge type " << charge
              << std::endl;
    exit(EXIT_FAILURE);
  }

  TString chargeCut = TString::Format("-1*(%s_ID/abs(%s_ID))=="+chrg,
    pName, pName);
  TString probeCut = TString::Format("%s_Probe==1", pName);
  TString tisCut = TString::Format("%s_ElectronTisTagged==1", pName);
  TString tagCut = TString::Format("%s_Tag==1", otherPName);
  TString bremCut = TString::Format("%s_HasBremAdded==%i", pName, bremAdded);
  TString Cuts = TString::Format("(%s) && (%s) && (%s) && (%s) && (%s)",
    chargeCut.Data(), probeCut.Data(), tisCut.Data(),
    tagCut.Data(), bremCut.Data());

  massFitter->MakeDMassDataSet(ch,
                               "Jpsi_M",
                               dsName,
                               "",
                               Cuts.Data());

  //==================================================//
  // Configure Jpsi Line Shape, single CB if there 
  // were no bremsstrahlung photons added and double 
  // if photons were added
  //==================================================//
  if (bremAdded == 0) {
//     massFitter->MakeDMassSigBiGauss(3056, 3025, 3075,
//                                 11.0, 9.0, 13.0,
//                                 2.0, 1.2, 2.8, 
//                                 0.75);
    massFitter->MakeDMassSigCB(
      3056, 3025, 3075,
      45., 1., 250.,
      0.7, 0., 5.,
      5.0, 5.0, 5.0
    );
    massFitter->GetVar("dmass_sig_n")->setConstant(true);
  } else if (bremAdded == 1) {
    massFitter->MakeDMassSigBiCB(
      3056, 3025, 3075,
      45., 1., 250.,
      100., 1., 250.,
//       0.7, 0., 5.,
      0.6, 0.6, 0.6,
      1.6, 0., 5.,
      5.0, 5.0, 5.0,
      1.0, 1.0, 1.0,
      0.75, 0.0, 1.0
    );
//     massFitter->MakeDMassSigBiGauss(3056, 3025, 3075,
//                                 11.0, 9.0, 13.0,
//                                 2.0, 1.2, 2.8, 
//                                 0.75);
    massFitter->GetVar("dmass_sig_alpha_left")->setConstant(true);
    massFitter->GetVar("dmass_sig_n_left")->setConstant(true);
    massFitter->GetVar("dmass_sig_n_right")->setConstant(true);
  }

  //==================================================//
  // Configure D0 Background Shape and make the sum 
  // of signal and background
  //==================================================//
//   massFitter->MakeDMassBkgJpsiee(
// //                                   -.9, -1.5, 1.,
//                                   -2e-3, -.2, .2,
//                                   3630., 3500., 3700.,
//                                   0.3, 0.0, 1.0 ,
//                                   "");

//   massFitter->MakeDMassBkgExp(-2e-3, -.2, .1);
//   massFitter->MakeDMassModel(0.90, 0.10);
  
  if (bremAdded == 0 or bkgSlope == -999.) {
    massFitter->MakeDMassBkgFlat(-.9, -1.5, 0.);
    massFitter->MakeDMassModel(0.90, 0.10);
  } else {
    massFitter->MakeDMassBkgFlat(bkgSlope, bkgSlope, bkgSlope);
    massFitter->GetVar("dmass_bkg_poly_c1")->setConstant(true);
    
    massFitter->MakeDMassModel(0.95, 0.05);
    
    float varMax = massFitter->GetVar("nbkg")->getMax();
    massFitter->ReplaceWithAbsVar("nbkg", -varMax, varMax);
    massFitter->GetVar("nbkg")->setVal(-5.);
  }

  //==================================================//
  // Save inital parameters of the fit
  //==================================================//
  massFitter->SaveSnapshot("initModel");
  

  //==================================================//
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  std::vector<Int_t> FitStrategies = bass::list_of(0)(2);
  int nbins = 100;
  massFitter->PerformDMassIterativeBinnedFit(nbins,
                                             FitStrategies,
                                             "fitResults",
                                             1, // use single thread for batch processing
                                             kTRUE, /* save snapshot */
                                             kTRUE,  /* print results */
                                             kFALSE, /* use sum-of-weights errors */
                                             kTRUE, /* use extended mode */
                                             kFALSE /* perform chi^2 fit */
                                             );
  
  
  //==================================================//
  // Save fitted slope value for use in brems fit
  //==================================================//
  if (bremAdded == 0) {
    bkgSlope = massFitter->GetVar("dmass_bkg_poly_c1")->getVal();
  } 
  
  //==================================================//
  // Remove the RooFormulaVar for the SWeighting
  //==================================================//
  if (bremAdded == 1) {
    float varMax = massFitter->GetVar("nbkg")->getMax();
    float nbkg_abs_val = abs(massFitter->GetVar("nbkg")->getVal());
    massFitter->GetVar("nbkg")->setVal(nbkg_abs_val);
    massFitter->RemoveAbsVar("nbkg", 0., varMax);
  }

  //==================================================//
  // Calculate sWeights
  //==================================================//
  massFitter->CalculateSWeights("fitResults",
                                TString::Format("%s_wSWeights",dsName).Data());
  massFitter->SaveWS();
  
  //==================================================//
  // Return the RooFormulaVar for plotting
  //==================================================//
  if (bremAdded == 1) {
    float varMax = massFitter->GetVar("nbkg")->getMax();
    massFitter->ReplaceWithAbsVar("nbkg", -varMax, varMax);
  }

  //==================================================//
  // Configure plot attributes
  //==================================================//
  std::cout << "Setting plot attributes" << std::endl;
  if (bremAdded == 0) {
    massFitter->AddPdfComponent("sigModel",      kRed,      kDashed, 3);
  } else if (bremAdded == 1) {
    massFitter->AddPdfComponent("dmass_sig_cb_left",      kRed,      kDashed, 3);
    massFitter->AddPdfComponent("dmass_sig_cb_right",     kGreen,    kDashed, 3);
  }
  massFitter->AddPdfComponent("bkgModel",  kOrange+2, 7,       3);

  TString plotParams("");
  if (bremAdded == 0) {
    plotParams = "dmass_sig_mu,dmass_sig_sigma,dmass_sig_alpha,dmass_bkg_poly_c1";
  } else if (bremAdded == 1) {
    plotParams = "dmass_sig_mu,dmass_sig_sigma_left,dmass_sig_sigma_right,dmass_sig_alpha_left,dmass_sig_alpha_right,dmass_sig_frac_left";
  }

  massFitter->SetPlotParameters(plotParams.Data());
  massFitter->SetParamBoxAttributes("paramBox",0.68,0.55,0.95,0.93,0.022,12);

  massFitter->SetPlotBins(100);
  massFitter->SetPlotBins(jpsiName, nbins);


  //==================================================//
  // Make plots
  //==================================================//
  massFitter->SetRange(jpsiName, 2900.,3150., "sigRange");
  TString rangeTitle="sigRegion";
  LHCbStyle();

  TString bremFileSuffix("");
  if ( bremAdded == 0 ) {
    bremFileSuffix = "NoBrem";
  } else if ( bremAdded == 1 ) {
    bremFileSuffix = "Brem";
  }
  
  TFile * tf = TFile::Open("JPsiee_Plots.root","UPDATE");

  //==================================================//
  // Plot correlation matrix
  //==================================================//

  TH2* correlationHist = massFitter->GetFitResult("fitResults")->correlationHist();

  TCanvas* cnv_corr = new TCanvas("cnv_corr", "", 900, 900);
  cnv_corr->cd();
  cnv_corr->SetMargin(0.4,0.15,0.4,0.05);
  correlationHist->GetXaxis()->LabelsOption("v");
  
  correlationHist->Draw("colz");
  
  cnv_corr->SaveAs(TString::Format("Corr_%s_%s_%s_%s.pdf",pName,
                             charge,bremFileSuffix.Data(),index).Data());
  
  correlationHist->Write(TString::Format("Corr_%s_%s_%s_%s",pName,
                             charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot Initial fit state
  //==================================================//
  RooPlot* rp_mass_init = massFitter->PlotFitResults(jpsiName,
                                                "initModel",
                                                "sigRange",
                                                rangeTitle.Data(),
                                                kFALSE /* use SumW2 errors */,
                                                kFALSE /* plot parambox */
                                                );

  // get the pull plot
  RooPlot* rp_mass_init_pull = massFitter->PlotFitPulls(jpsiName,
                                                   "initModel");

  rp_mass_init_pull->GetXaxis()->SetRangeUser(-5.,5.);
  rp_mass_init_pull->SetTitle(";;");
  rp_mass_init_pull->SetLabelSize(0.12, "X");
  rp_mass_init_pull->SetLabelSize(0.12, "Y");

  TCanvas* c0 = new TCanvas("cnv_mass_init", "", 900, 900);
  TPad* c0_upper = new TPad("cnv_mass_init_upper", "", 0.005, 0.25, 0.995, 0.995);
  TPad* c0_lower = new TPad("cnv_mass_init_lower", "", 0.005, 0.05, 0.995, 0.245);
  c0_upper->Draw();
  c0_lower->Draw();

  // plot the mass
  c0_upper->cd();
  rp_mass_init->Draw();

  // plot the pulls
  c0_lower->cd();
  rp_mass_init_pull->Draw();
  c0->SaveAs(TString::Format("FitInit_%s_%s_%s_%s.pdf",pName,
                             charge,bremFileSuffix.Data(),index).Data());
  
  rp_mass_init->Write(TString::Format("FitInit_%s_%s_%s_%s",pName,
                             charge,bremFileSuffix.Data(),index).Data());
  rp_mass_init_pull->Write(TString::Format("FitInit_%s_%s_%s_%s_Pull",pName,
                             charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot final fit
  //==================================================//
  RooPlot* rp_mass = massFitter->PlotFitResults(jpsiName,
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data(),
                                                kFALSE /* use SumW2 errors */
                                                );

  // get the pull plot
  RooPlot* rp_mass_pull = massFitter->PlotFitPulls(jpsiName,
                                                   "fitResults");

  rp_mass_pull->GetXaxis()->SetRangeUser(-5.,5.);
  rp_mass_pull->SetTitle(";;");
  rp_mass_pull->SetLabelSize(0.12, "X");
  rp_mass_pull->SetLabelSize(0.12, "Y");

  TCanvas* c1 = new TCanvas("cnv_mass", "", 900, 900);
  TPad* c1_upper = new TPad("cnv_mass_upper", "", 0.005, 0.25, 0.995, 0.995);
  TPad* c1_lower = new TPad("cnv_mass_lower", "", 0.005, 0.05, 0.995, 0.245);
  c1_upper->Draw();
  c1_lower->Draw();

  // plot the mass
  c1_upper->cd();
  rp_mass->Draw();

  // plot the pulls
  c1_lower->cd();
  rp_mass_pull->Draw();
  rp_mass_pull->GetXaxis()->SetRangeUser(-5.,5.);
  rp_mass_pull->Draw();
  c1->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.pdf",pName,
                             charge,bremFileSuffix.Data(),index).Data());
  
  rp_mass->Write(TString::Format("FitRes_%s_%s_%s_%s",pName,
                             charge,bremFileSuffix.Data(),index).Data());
  rp_mass_pull->Write(TString::Format("FitRes_%s_%s_%s_%s_Pull",pName,
                             charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot weighted DLL(e-pi) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  TString varName="e_CombDLLe";
  massFitter->SetRange(varName.Data(), -30., 30., "hasRichRange");
  RooPlot* rp_pide = massFitter->PlotVariable(varName.Data(),
                                               "", "hasRichRange", kTRUE);
  TCanvas* c2 = new TCanvas("cnv_pide", "", 1024, 768);
  rp_pide->Draw();
  c2->SaveAs(TString::Format("DLLe_%s_%s_%s_%s.pdf",pName,charge,bremFileSuffix.Data(),index).Data());
  
  rp_pide->Write(TString::Format("DLLe_%s_%s_%s_%s",
                                    pName,charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot weighted ProbNN(pi) distribution
  //==================================================//
  varName="e_ProbNNpi";
  massFitter->SetRange(varName.Data(), 0, 1, "isPionRange");
  RooPlot* rp_probnnpi = massFitter->PlotVariable(varName.Data(),
                                                 "", "isPionRange", kTRUE);
  TCanvas* c3 = new TCanvas("cnv_probnnpi", "", 1024, 768);
  rp_probnnpi->Draw();
  c3->SaveAs(TString::Format("ProbNNpi_%s_%s_%s_%s.pdf",
                             pName,charge,bremFileSuffix.Data(),index).Data());
  
  rp_probnnpi->Write(TString::Format("ProbNNpi_%s_%s_%s_%s",
                             pName,charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot weighted ProbNN(e) distribution
  //==================================================//
  varName="e_ProbNNe";
  massFitter->SetRange(varName.Data(), 0, 1, "isElectronRange");
  RooPlot* rp_probnne = massFitter->PlotVariable(varName.Data(),
                                                 "", "isElectronRange", kTRUE);
  TCanvas* c4 = new TCanvas("cnv_probnne", "", 1024, 768);
  rp_probnne->Draw();
  c4->SaveAs(TString::Format("ProbNNe_%s_%s_%s_%s.pdf",
                             pName,charge,bremFileSuffix.Data(),index).Data());
  
  rp_probnne->Write(TString::Format("ProbNNe_%s_%s_%s_%s",
                             pName,charge,bremFileSuffix.Data(),index).Data());

  
  
  massFitter->SetDataSetName("data");
  //==================================================//
  // Plot unweighted DLL(e-pi) distribution
  //==================================================//
  varName="e_CombDLLe";
  RooPlot* rp_pide_nosw = massFitter->PlotVariable(varName.Data(),
                                               "", "hasRichRange", kTRUE);
  c2->cd();
  rp_pide_nosw->Draw();
  c2->SaveAs(TString::Format("DLLe_noSW_%s_%s_%s_%s.pdf",pName,charge,bremFileSuffix.Data(),index).Data());
  
  rp_pide_nosw->Write(TString::Format("DLLe_noSW_%s_%s_%s_%s",
                                    pName,charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot unweighted ProbNN(pi) distribution
  //==================================================//
  varName="e_ProbNNpi";
  RooPlot* rp_probnnpi_nosw = massFitter->PlotVariable(varName.Data(),
                                                 "", "isPionRange", kTRUE);
  c3->cd();
  rp_probnnpi_nosw->Draw();
  c3->SaveAs(TString::Format("ProbNNpi_noSW_%s_%s_%s_%s.pdf",
                             pName,charge,bremFileSuffix.Data(),index).Data());
  
  rp_probnnpi_nosw->Write(TString::Format("ProbNNpi_noSW_%s_%s_%s_%s",
                             pName,charge,bremFileSuffix.Data(),index).Data());

  //==================================================//
  // Plot unweighted ProbNN(e) distribution
  //==================================================//
  varName="e_ProbNNe";
  RooPlot* rp_probnne_nosw = massFitter->PlotVariable(varName.Data(),
                                                 "", "isElectronRange", kTRUE);
  c4->cd();
  rp_probnne_nosw->Draw();
  c4->SaveAs(TString::Format("ProbNNe_noSW_%s_%s_%s_%s.pdf",
                             pName,charge,bremFileSuffix.Data(),index).Data());
  
  rp_probnne_nosw->Write(TString::Format("ProbNNe_noSW_%s_%s_%s_%s",
                             pName,charge,bremFileSuffix.Data(),index).Data());

  
  massFitter->SetDataSetName("data_sigw");

  //==================================================//
  // Check fit convergence
  //==================================================//
  int status=-1;
  if ( !(checkFitStatus(*massFitter, "fitResults", status)) )
  {
    std::string minuit2Message="";
    std::string minosMessage="";
    std::string hesseMessage="";
    getFitStatusMessages(status, minuit2Message, minosMessage, hesseMessage);
    cerr << "J/psi ee " << charge << " " << pName << (bremAdded == 0 ? " No Brem" : " Brem")
         << " fit failed to converge: "
         << endl;
    if (minuit2Message!="OK.") cerr << minuit2Message << endl;
    if (minosMessage!="OK.") cerr << minosMessage << endl;
    if (hesseMessage!="OK.") cerr << hesseMessage << endl;
    if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  int covQual=-1;
  if ( !(checkCovQual(*massFitter, "fitResults", covQual)) )
  {
    cerr << "J/psi ee " << charge << " " << pName << (bremAdded == 0 ? " No Brem" : " Brem")
         << " fit has invalid covariance matrix: "
         << getCovQualMessage(covQual) << endl;
    if (exitOnBadFit) exit(EXIT_FAILURE);
  }

  // print warning if EDM is > 1e-2
  double edm = -9999.;
  if ( !(checkEDM(*massFitter, "fitResults", edm, 1e-2)) )
  {
    cerr << "WARNING: " << "J/psi ee " << charge << " "
         << pName << (bremAdded == 0 ? " No Brem" : " Brem") << " fit has EDM > 1e-2 ("
         << std::setprecision(3) << edm << ")" << endl;
    if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  cout << "Fit is acceptable" << endl ;
  

  //==================================================//
  // Clean up
  //==================================================//
  tf->Close();
  
  delete tf;
  tf = NULL;
  
  delete cnv_corr;
  cnv_corr=NULL;
  delete c0;
  c0=NULL;
  delete c1;
  c1=NULL;
  delete c2;
  c2=NULL;
  delete c3;
  c3=NULL;
  delete c4;
  c4=NULL;
  delete massFitter;
  massFitter=NULL;
}

void usage(const char* fname, ostream& os = cout) {
    os << "Usage: " << fname
       << "<magPol> <stripVersion> <dataType> "
       << "<index> <outputDir> <verbose?> <exitOnBadFit?> "
       << "<inputFile0> (<inputFile1> ...)" << endl << endl;
    os << "Example: " << fname << " \"Down\" "
       << "\"20\" \"2012\" \"0\" \"/output/dir\" "
       << "\"1\" \"1\" \"/input/dir/0/infile.root\"" << endl;
}

int main(int argc, char *argv[])
{
  // first = name given to fit function,
  // second = charge indicator in output filename
  // The first part of the pair should really be an enum instead
  ssMap charges = bass::map_list_of("Positive", "Plus")("Negative", "Minus");
  // map of charge to electron name
  ssMap electronNames = bass::map_list_of("Positive", "e0")("Negative", "e1");
  // map of charge to other electron name
  ssMap otherElectronNames = bass::map_list_of("Positive", "e1")("Negative", "e0");

  const char* wsName="JpsieeCalib";
  const char* dsName="data";
  const char* massName="mass";
  const char* tupleName="CalibPID";

  //---------------------------------------------------//
  // argv parameters:
  // 1: Field Orientation (Up or Down)
  // 2: Stripping version
  // 3: Datatype (e.g. '2011' or '2012')
  // 4: Subset index
  // 5: Output directory
  // 6: print entries (1 = print entries, 0 = don't print)
  // 7: Exit on bad fit flag (1 = exit if fit, covariance or EDM quality is bad,
  //    0 = print error message on bad fit, but don't exit)
  // 8: File(s) to run over
  //---------------------------------------------------//
  if ( !(argc>8) )
  {
    cerr << "Invalid number of arguments passed: " << argc-1 << endl;
    usage(argv[0], cerr);
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//

  const char* magPol=argv[1];
  const char* stripVersion=argv[2];
  const char* DataType=argv[3];
  const char* index=argv[4];
  const char* outDir=argv[5];
  const char* c_printEntries=argv[6];
  const char* c_exitOnBadFit=argv[7];
  Bool_t printEntries = boost::lexical_cast<Bool_t>(c_printEntries);
  Bool_t exitOnBadFit = boost::lexical_cast<Bool_t>(c_exitOnBadFit);

  //---------------------------------------------------//
  // Pass input files into vector
  //---------------------------------------------------//
  std::vector<std::string> inputFiles;
  for (unsigned int i = 8; i < (unsigned int)argc; ++i)
  {
     std::string fname = argv[i];
     inputFiles.push_back(fname);
  }

  //---------------------------------------------------//
  // Specfiy list of variables to be included in dataset
  //---------------------------------------------------//
  std::vector<fptr> fun_vec;
  if (strcmp(DataType,"2012")==0) fun_vec.push_back(SetSpecVars_EvtVars2012);
  else if (strcmp(DataType,"2011")==0) fun_vec.push_back(SetSpecVars_EvtVars2011);
  else {
    cerr << "Invalid DataType " << DataType << endl;
    return EXIT_FAILURE;
  }
  fun_vec.push_back(SetSpecVars_StdDLLs2011);
  fun_vec.push_back(SetSpecVars_ANNVars);
  fun_vec.push_back(SetSpecVars_KinematicVars);
  fun_vec.push_back(SetSpecVars_MuonVars);
  fun_vec.push_back(SetSpecVars_RICHVars);
  fun_vec.push_back(SetSpecVars_ElectronVars);

  TString fname;
  TString tupleFullName;

  //---------------------------------------------------//
  // Fit -ve, +ve tracks
  //---------------------------------------------------//
  BOOST_FOREACH(const ssMap::value_type& charge, charges) {
    tupleFullName.Form("JpsieeKFromBTuple/%s",
                       tupleName);
    const TString& electronName = electronNames[charge.first];
    const TString& otherElectronName = otherElectronNames[charge.first];

    float bkgSlope(-999.);

    for (int ibrem = 0 ; ibrem < 2; ++ibrem) {

      //---------------------------------------------------//
      // Get data
      //---------------------------------------------------//
      // It'd be better if GetData took a enum that specified the calibration sample
      // and worked out the correct tuple name
      TChain* t = GetData(inputFiles, tupleFullName.Data());

      fname.Form("%s/Jpsi_e%s_Mag%s_Strip%s_%s_%s.root",
                outDir, (charge.second).Data(),
                magPol, stripVersion, (ibrem == 0 ? "NoBrem" : "Brem"),
                index);
      std::cout << "Making J/psi ee fit for "
                << "particle (charge) = "
                << electronName.Data() << " (" << charge.second
                << ") with " << (ibrem == 0 ? "no " : "") << "brems" << std::endl;

      if (t==NULL)
      {
        cerr << "TChain pointer is NULL" << endl;
        return EXIT_FAILURE;
      }

      if (t->GetEntries()==0)
      {
        cerr << "TChain contains no entries" << endl;
        return EXIT_FAILURE;
      }

      try {
          JpsieeFit(t, (charge.first).Data(), ibrem,
                  electronName.Data(), otherElectronName.Data(),
                  wsName, fname.Data(), dsName, massName,
                  fun_vec, index, printEntries, exitOnBadFit,
                  bkgSlope
          );
      }
      catch (std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
      }

    }
    // we should really delete the TChain, but doing so seems to cause
    // occasional segmentation faults
    //delete t;
    //t=NULL;
  }
  return EXIT_SUCCESS;
}
