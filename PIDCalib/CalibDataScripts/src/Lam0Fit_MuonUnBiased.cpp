// $Id: $
// Include files
#include <map>
#include <vector>
#include <cstdlib>

#include "TString.h"
#include "TChain.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooPlot.h"

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "RooPhysFitter/RooDMassFitter.h"

// Include files (local)
#include "CalibDataScripts/SetSpectatorVars.h"
#include "CalibDataScripts/Lam0Fit_MuonUnBiased.h"
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

void Lam0Fit_MuonUnBiased(TChain* ch, 
                          const char* charge,
                          const char* MomRange,
                          const char* pName,
                          const char* wsName,
                          const char* fName,
                          const char* dsName,
                          const char* lam0Name,
                          std::vector<fptr>& fun_vec,
                          const char* index,
                          Bool_t isVerbose,
                          Bool_t exitOnBadFit)
{
  
  //==================================================//
  // Constants
  //==================================================//
  Float_t lam0MassPDG=1115.683;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooPhysFit::RooDMassFitter* massFitter 
    = new RooPhysFit::RooDMassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(lam0Name);
  massFitter->SetDMassSigModelName("sigModel");
  massFitter->SetDMassBkgModelName("bkgModel");
  massFitter->MakeDMassVar(lam0MassPDG-15,
                           lam0MassPDG+15,
                           "MeV/c^{2}",
                           "m_{p#pi}");

  if (isVerbose) massFitter->SetPrintEntriesFlag(kTRUE);

  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout << "Adding Spectator Vars" << std::endl;
    (*itr)(*massFitter, pName, pName);
  }
  
  //==================================================//
  // Select tracks with specific charge
  //==================================================//
  TString chrg="";
  if(strcmp(charge, "Positive")==0)
    chrg = "1.0";
  else if(strcmp(charge,"Negative")==0)
    chrg = "-1.0";
  else {
    std::cerr << "Lambda0 " << charge << " MuonUnBiased " << pName 
              << "fit: Unexpected charge type " << charge
              << std::endl;
    exit(EXIT_FAILURE);
  }

  TString Cuts;
  Cuts.Form("(%s_MuonTisTagged==1)&&(%s_ID/abs(%s_ID) == "+chrg+")",
    pName, pName, pName);  

  //==================================================//
  // Apply max momentum cut on events in LoP line
  //==================================================//
  if (strcmp(MomRange, "LoP")==0)
    Cuts.Append(" && P_P <= 40000.0");
  else if (strcmp(MomRange, "HiP")==0)
    Cuts.Append(" && P_P > 40000.0");
  else {
    std::cerr << "Lambda0 " << charge << " MuonUnBiased " << pName 
              << "fit: Unexpected momentum type "
              << MomRange << std::endl;
    exit(EXIT_FAILURE);
  }

  massFitter->MakeDMassDataSet(ch, 
                               "Lam0_M", 
                               dsName, 
                               "", 
                               Cuts.Data());
  
 //==================================================//
  // Configure Lambda Line Shape
  //==================================================//
  /*
  massFitter->MakeDMassSigBiGauss(lam0MassPDG, lam0MassPDG-5, lam0MassPDG+5,
                                   0.7,0.1,1.5,
                                   2.4,1.0,4.0, 
                                   0.5);
  */
  massFitter->MakeDMassSigTriGauss(lam0MassPDG, lam0MassPDG-5, lam0MassPDG+5,
                                   1.0,0.5,1.5,
                                   2.0,1.5,2.5, 
                                   7.0,5.0,9.0, 
                                   0.55,
                                   0.35);
  
  //==================================================//
  // Configure Lambda Background Shape
  //==================================================//
  //massFitter->MakeDMassBkgQuadratic(-0.2, -1, 1,
  //                                  -0.2, -1, 1);
  massFitter->MakeDMassBkgFlat(-0.1, -0.5, 0.3);

  //==================================================//
  // Make composite model with following estimate of 
  // yield breakdown
  //==================================================//
  massFitter->MakeDMassModel(0.4, 0.6);
  
  //==================================================// 
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  std::vector<Int_t> FitStrategies = bass::list_of(0)(2);
  int nbins = 500;
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
  // Check fit convergence
  //==================================================//
  int status=-1;
  if ( !(checkFitStatus(*massFitter, "fitResults", status)) ) 
  {
    std::string minuit2Message="";
    std::string minosMessage="";
    std::string hesseMessage="";
    getFitStatusMessages(status, minuit2Message, minosMessage, hesseMessage);
    cerr << "Lambda0 " << charge << " MuonUnBiased " << pName
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
    cerr << "Lambda0 " << charge << " MuonUnBiased " << pName 
         << " fit has invalid covariance matrix: " 
         << getCovQualMessage(covQual) << endl;
    if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  
  // print warning if EDM is > 1e-2
  double edm = -9999.;
  if ( !(checkEDM(*massFitter, "fitResults", edm)) ) 
  {
    cerr << "WARNING: " << "Lambda0 " << charge << " MuonUnBiased "
         << pName << " fit has EDM > 1e-2 ("
         << std::setprecision(3) << edm << ")" << endl;
    if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  
  //==================================================// 
  // Calculate sWeights
  //==================================================//
  massFitter->CalculateSWeights("fitResults", 
                                TString::Format("%s_wSWeights",dsName).Data());
  massFitter->SaveWS();
  
  //==================================================// 
  // Configure plot attributes
  //==================================================//
  std::cout << "Setting plot attributes" << std::endl;
  massFitter->AddPdfComponent("sigModel",  kRed,      kDashed, 3);
  massFitter->AddPdfComponent("bkgModel",  kOrange+2, 7,       3);

  TString plotParams
    = "dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1,dmass_sig_sigma2";
  // plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
  massFitter->SetPlotParameters(plotParams.Data());
  massFitter->SetParamBoxAttributes("paramBox",0.62,0.5,0.95,0.93,0.022,12);

  massFitter->SetPlotBins(100);
  massFitter->SetPlotBins(lam0Name, nbins);
  
  //==================================================// 
  // Make plots
  //==================================================//
  massFitter->SetRange(lam0Name,lam0MassPDG-4.0,lam0MassPDG+4.0, "sigRange");
  TString rangeTitle="sigRegion";
  LHCbStyle();
  
  //==================================================// 
  // Plot D0 Mass Fit
  //==================================================//
  RooPlot* rp_mass = massFitter->PlotFitResults(lam0Name, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data(),
                                                kFALSE /* use SumW2 errors */
                                                );

  // get the pull plot
  RooPlot* rp_mass_pull = massFitter->PlotFitPulls(lam0Name,
                                                   "fitResults");
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
  
  c1->SaveAs(TString::Format("FitRes_MuonUnBiased%s_%s_%s_%s_%s.eps", 
                             lam0Name,pName,
                             charge, MomRange, index).Data());

  //==================================================// 
  // Plot weighted DLL(p-pi) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  TString varName;
  varName.Form("%s_CombDLLp",pName);
  massFitter->SetRange(varName.Data(), -150., 150., "hasRichRange");
  RooPlot* rp_pidp = massFitter->PlotVariable(varName.Data(),
                                              "", "hasRichRange", kTRUE);
  TCanvas* c2 = new TCanvas("cnv_pidp", "", 1024, 768);
  rp_pidp->Draw();
  c2->SaveAs(TString::Format("DLLp_MuonUnBiased%s_%s_%s_%s.eps",pName,charge,
                             MomRange,index).Data());

  //==================================================// 
  // Plot weighted DLL(mu-pi) distribution
  //==================================================//
  varName.Form("%s_CombDLLmu",pName);
  massFitter->SetRange(varName.Data(), -150., 150., "hasRichRange");
  RooPlot* rp_pidmu = massFitter->PlotVariable(varName.Data(),
                                              "", "hasRichRange", kTRUE);
  TCanvas* c3 = new TCanvas("cnv_pidmu", "", 1024, 768);
  rp_pidmu->Draw();
  c3->SaveAs(TString::Format("DLLmu_MuonUnBiased%s_%s_%s_%s.eps",pName,charge,
                             MomRange,index).Data());

  //==================================================// 
  // Plot weighted ProbNN(p) distribution
  //==================================================//
  RooPlot* rp_probnnp = massFitter->PlotVariable(TString::Format("%s_ProbNNp",
                                                                 pName).Data(),
                                                 "", "", kTRUE);
  TCanvas* c4 = new TCanvas("cnv_probnnp", "", 1024, 768);
  rp_probnnp->Draw();
  c4->SaveAs(TString::Format("ProbNNp_MuonUnBiased%s_%s_%s_%s.eps",pName,charge,
                             MomRange, index).Data());
  
  //==================================================// 
  // Plot weighted ProbNN(pi) distribution
  //==================================================//
  RooPlot* rp_probnnpi = massFitter->PlotVariable(TString::Format("%s_ProbNNpi",
                                                                 pName).Data(),
                                                 "", "", kTRUE);
  TCanvas* c5 = new TCanvas("cnv_probnnpi", "", 1024, 768);
  rp_probnnpi->Draw();
  c5->SaveAs(TString::Format("ProbNNpi_MuonUnBiased%s_%s_%s_%s.eps",
                             pName,charge,
                             MomRange, index).Data());
  
  //==================================================// 
  // Plot weighted ProbNN(mu) distribution
  //==================================================//
  varName.Form("%s_ProbNNmu", pName);
  massFitter->SetRange(varName.Data(), 0, 1, "isMuonRange");
  RooPlot* rp_probnnmu = massFitter->PlotVariable(varName.Data(),
                                                  "", "isMuonRange", kTRUE);
  TCanvas* c6 = new TCanvas("cnv_probnnmu", "", 1024, 768);
  rp_probnnmu->Draw();
  c6->SaveAs(TString::Format("ProbNNmu_MuonUnBiased%s_%s_%s_%s.eps",
                             pName,charge,
                             MomRange, index).Data());
  
  //==================================================// 
  // Clean up
  //==================================================//
  delete c1;
  c1=NULL;
  delete c2;
  c2=NULL;
  delete c3;
  c3=NULL;
  delete c4;
  c4=NULL;
  delete c5;
  c5=NULL;
  delete c6;
  c6=NULL;
  delete rp_mass;
  rp_mass=NULL;
  delete rp_pidp;
  rp_pidp=NULL;
  delete rp_pidmu;
  rp_pidmu=NULL;
  delete rp_probnnp;
  rp_probnnp=NULL;
  delete rp_probnnpi;
  rp_probnnpi=NULL;
  delete rp_probnnmu;
  rp_probnnmu=NULL;
  delete massFitter;
  massFitter=NULL;
}

void usage(const char* fname, ostream& os = cout) {
    os << "Usage: " << fname << " <partName> "
       << "<magPol> <stripVersion> <dataType> "
       << "<index> <outputDir> <verbose?> <exitOnBadFit?> "
       << "<inputFile0> (<inputFile1> ...)" << endl << endl;
    os << "Example: " << fname << " \"P\" \"Down\" "
       << "\"20\" \"2012\" \"0\" \"/output/dir\" "
       << "\"1\" \"1\" \"/input/dir/0/infile.root\"" << endl;
}

int main(int argc, char *argv[])
{
  // first = name given to fit function,
  // second = charge indicator in output filename
  // The first part of the pair should really be an enum instead
  ssMap charges = bass::map_list_of("Negative", "Minus")("Positive", "Plus");
  sVect momRanges = bass::list_of("LoP")("HiP");

  const char* wsName="Lam0Calib";
  const char* dsName="data";
  const char* massName="mass";
  const char* tupleName="CalibPID";

  //---------------------------------------------------//
  // argv parameters:
  // 1: Particle Name in nTulpe
  // 2: Field Orientation (Up or Down)
  // 3: Stripping version
  // 4: Datatype (e.g. '2011' or '2012')
  // 5: Subset index
  // 6: Output directory
  // 7: print entries (1 = print entries, 0 = don't print)
  // 8: Exit on bad fit flag (1 = exit if fit, covariance or EDM quality is bad,
  //    0 = print error message on bad fit, but don't exit)
  // 9: File(s) to run over
  //---------------------------------------------------//
  if ( !(argc>9) )
  {
    cerr << "Invalid number of arguments passed: " << argc-1 << endl;
    usage(argv[0], cerr);
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  const char* pName=argv[1];
  const char* magPol=argv[2];
  const char* stripVersion=argv[3];
  const char* DataType=argv[4];
  const char* index=argv[5];
  const char* outDir=argv[6];
  const char* c_printEntries=argv[7];
  const char* c_exitOnBadFit=argv[8];
  Bool_t printEntries = boost::lexical_cast<Bool_t>(c_printEntries);
  Bool_t exitOnBadFit = boost::lexical_cast<Bool_t>(c_exitOnBadFit);

  //---------------------------------------------------//
  // Pass input files into vector 
  //---------------------------------------------------//
  std::vector<std::string> inputFiles;
  for (unsigned int i = 9; i < (unsigned int)argc; ++i) 
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

  TString fname;
  TString tupleFullName;
  
  //---------------------------------------------------//
  // Fit -ve, +ve, Low P, High P tracks 
  //---------------------------------------------------//
  BOOST_FOREACH(const TString& momRange, momRanges) {
    tupleFullName.Form("Lam02PPi_%sTuple/%s", 
                       momRange.Data(), tupleName);
    BOOST_FOREACH(const ssMap::value_type& charge, charges) {
      //---------------------------------------------------//
      // Get data
      //---------------------------------------------------//
      // It'd be better if GetData took a enum that specified the calibration sample
      // and worked out the correct tuple name
      TChain* t = GetData(inputFiles, tupleFullName.Data());
 
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

      fname.Form("%s/Lam0_MuonUnBiased_%s%s_%s_Mag%s_Strip%s_%s.root",
                 outDir, pName, (charge.second).Data(), momRange.Data(),
                 magPol, stripVersion, index);
      std::cout << "Making " << momRange << " MuonUnBiased Lam0 fit for "
                << "particle (charge) = " 
                << pName << " (" << charge.second
                << ")" << std::endl;
      try {      
          Lam0Fit_MuonUnBiased(t, (charge.first).Data(), momRange.Data(),
                               pName, wsName, fname.Data(), dsName,
                               massName, fun_vec, index, printEntries, exitOnBadFit);
      }
      catch (std::exception &e) {
         std::cerr << "Caught exception: " << e.what() << std::endl;
         return EXIT_FAILURE;
    }
     
      // we should really delete the TChain, but doing so seems to cause
      // occasional segmentation fault
      delete t;
      t=NULL;
    } // loop over charges
  } // loop over lo/hiP
  return EXIT_SUCCESS;
}
