// $Id: $
// Include files
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <iomanip>

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
#include "CalibDataScripts/JpsiFit.h"
#include "CalibDataScripts/GetData.h"
#include "CalibDataScripts/LHCbStyle.h"
#include "CalibDataScripts/CheckFitResults.h"

// Namespaces
namespace bass=boost::assign;
using namespace std;

// typedefs
typedef std::map<TString,TString> ssMap;
typedef std::vector<TString> sVect;

void JpsiFit(TChain* ch, 
             const char* charge,
             const char* pName,
             const char* otherPName,
             const char* wsName,
             const char* fName,
             const char* dsName,
             const char* jpsiName,
             std::vector<fptr>& fun_vec,
             const char* index,
             Bool_t isVerbose,
             Bool_t exitOnBadFit)
{
  
  //==================================================//
  // Constants
  //==================================================//
  Float_t jpsiMassPDG=3096;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooPhysFit::RooDMassFitter* massFitter
    = new RooPhysFit::RooDMassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(jpsiName);
  massFitter->SetDMassSigModelName("sigModel");
  massFitter->SetDMassBkgModelName("bkgModel");
  massFitter->MakeDMassVar(jpsiMassPDG-110,
                           jpsiMassPDG+110,
                           "MeV/c^{2}",
                           "m_{#mu#mu}");

  if (isVerbose) massFitter->SetPrintEntriesFlag(kTRUE);

  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;


  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {

    std::cout<<"Adding Spectator Vars"<<std::endl;
    (*itr)(*massFitter, "Mu", pName);



}
  //  SetSpecVars_MuonTisTosTagged(*massFitter,"Mu",pName,otherPName);
  //==================================================//
  // Select tracks with specific charge (mu- = +ve ID)
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

  // TString chargeCut = TString::Format("mup_TRACK_GHOSTPROB<0.5 && mum_TRACK_GHOSTPROB<0.5 && -1*(%s_ID/abs(%s_ID))=="+chrg,
  //    pName, pName);

 TString chargeCut = TString::Format("-1*(%s_ID/abs(%s_ID))=="+chrg, pName, pName);
  TString probeCut = TString::Format("%s_MuonProbe==1", pName);
  TString muonUnBiasedCut = TString::Format("%s_MuonUnbiased==1", pName);
  TString tagCut = TString::Format("%s_MuonTag==1", otherPName);
  TString Cuts = TString::Format("(%s) && (%s) && (%s) && (%s)",
    chargeCut.Data(), probeCut.Data(), muonUnBiasedCut.Data(),
    tagCut.Data());

  massFitter->MakeDMassDataSet(ch, 
                               "Jpsi_M", 
                               dsName, 
                               "", 
                               Cuts.Data());
  
  //==================================================//
  // Configure Jpsi Line Shape
  //==================================================//
                                     
  //massFitter->MakeDMassSigBiGauss(jpsiMassPDG, jpsiMassPDG-5, jpsiMassPDG+5,
  //                                11.0, 9.0, 13.0,
  //                                2.0, 1.2, 2.8, 
  //                                0.75);
                                  
  massFitter->MakeDMassSigCB(jpsiMassPDG, jpsiMassPDG-10, jpsiMassPDG+10, 
                                    12.0, 9.0, 30.0,
                                    13, 13, 13, 
                                    1.0, 1.0, 1.0);
  
  //==================================================//
  // Configure D0 Background Shape
  //==================================================//
  massFitter->MakeDMassBkgExp(-0.1, -0.9, 0.9);

  //==================================================//
  // Make composite model with following estimate of 
  // yield breakdown
  //==================================================//
  massFitter->MakeDMassModel(0.25, 0.75);
  
  //==================================================// 
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  std::vector<Int_t> FitStrategies = bass::list_of(0)(1);
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
  // massFitter->PerformDMassBinnedFit(nbins,
                                    // "fitResults", 
                                    // 1, // use single thread for batch processing
                                    // kTRUE, /* save snapshot */
                                    // kTRUE,  /* print results */
                                    // kFALSE, /* use sum-of-weights errors */
                                    // kTRUE, /* use extended mode */
                                    // kFALSE /* perform chi^2 fit */
                                    // );

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
    cerr << "J/psi " << charge << " " << pName
         << " fit failed to converge: "
         << endl;
    if (minuit2Message!="OK.") cerr << minuit2Message << endl;
    if (minosMessage!="OK.") cerr << minosMessage << endl;
    if (hesseMessage!="OK.") cerr << hesseMessage << endl;
    //    if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  int covQual=-1;
  if ( !(checkCovQual(*massFitter, "fitResults", covQual)) ) 
  {
    cerr << "J/psi " << charge << " " << pName 
         << " fit has invalid covariance matrix: " 
         << getCovQualMessage(covQual) << endl;
    //if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  
  // print warning if EDM is > 1e-2
  double edm = -9999.;
  if ( !(checkEDM(*massFitter, "fitResults", edm)) ) 
  {
    cerr << "WARNING: " << "J/psi " << charge << " "
         << pName << " fit has EDM > 1e-2 ("
         << std::setprecision(3) << edm << ")" << endl;
    // if (exitOnBadFit) exit(EXIT_FAILURE);
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

  // TString plotParams="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
  TString plotParams="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alpha,dmass_sig_n";
//  plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
  //plotParams+=",dmass_bkg_poly_c1";

  massFitter->SetPlotParameters(plotParams.Data());
  massFitter->SetParamBoxAttributes("paramBox",0.68,0.55,0.95,0.93,0.022,12);

  massFitter->SetPlotBins(100);
  massFitter->SetPlotBins(jpsiName, nbins);

  
  //==================================================// 
  // Make plots
  //==================================================//
  massFitter->SetRange(jpsiName, jpsiMassPDG-55,jpsiMassPDG+55, "sigRange");
  TString rangeTitle="sigRegion";
  LHCbStyle();
  
  //==================================================// 
  // Plot D0 Mass Fit
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
  c1->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.eps",jpsiName,pName,
                             charge,index).Data());

  //==================================================// 
  // Plot weighted DLL(mu-pi) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  //TString varName="Mu_Tesla_CombDLLmu";
TString varName="Mu_CombDLLmu";
  massFitter->SetRange(varName.Data(), -30., 30., "hasRichRange");
  RooPlot* rp_pidmu = massFitter->PlotVariable(varName.Data(),
                                               "", "hasRichRange", kTRUE);
  TCanvas* c2 = new TCanvas("cnv_pidmu", "", 1024, 768);
  rp_pidmu->Draw();
  c2->SaveAs(TString::Format("DLLmu_%s_%s_%s.eps",pName,charge,index).Data());

  //==================================================// 
  // Plot weighted ProbNN(pi) distribution
  //==================================================//
  RooPlot* rp_probnnpi = massFitter->PlotVariable("Mu_V2ProbNNpi",
                                                 "", "", kTRUE);
  TCanvas* c3 = new TCanvas("cnv_probnnpi", "", 1024, 768);
  rp_probnnpi->Draw();
  c3->SaveAs(TString::Format("ProbNNpi_%s_%s_%s.eps",
                             pName,charge,index).Data());
  
  //==================================================// 
  // Plot weighted ProbNN(mu) distribution
  //==================================================//
  varName="Mu_V2ProbNNmu";
  massFitter->SetRange(varName.Data(), 0, 1, "isMuonRange");
  RooPlot* rp_probnnmu = massFitter->PlotVariable("Mu_V2ProbNNmu",
                                                 "", "isMuonRange", kTRUE);
  TCanvas* c4 = new TCanvas("cnv_probnnmu", "", 1024, 768);
  rp_probnnmu->Draw();
  c4->SaveAs(TString::Format("ProbNNmu_%s_%s_%s.eps",
                             pName,charge,index).Data());
  
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
  delete rp_mass;
  rp_mass=NULL;
  delete rp_pidmu;
  rp_pidmu=NULL;
  delete rp_probnnpi;
  rp_probnnpi=NULL;
  delete rp_probnnmu;
  rp_probnnmu=NULL;
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
  // map of charge to muon name
  ssMap muonNames = bass::map_list_of("Positive", "mup")("Negative", "mum");
  // map of charge to other muon name
  ssMap otherMuonNames = bass::map_list_of("Positive", "mum")("Negative", "mup");

  const char* wsName="JpsiCalib";
  const char* dsName="data";
  const char* massName="mass";
  const char* tupleName="DecayTree";

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

 fun_vec.push_back(SetSpecVars_EvtVars);
  fun_vec.push_back(SetSpecVars_StdDLLs2011);
  fun_vec.push_back(SetSpecVars_ANNVars2012);
  fun_vec.push_back(SetSpecVars_KinematicVars);
  fun_vec.push_back(SetSpecVars_MuonVars);
  fun_vec.push_back(SetSpecVars_RICHVars);
   fun_vec.push_back(SetSpecVars_MuonTisTosTagged);

  TString fname;
  TString tupleFullName;
  
  //---------------------------------------------------//
  // Fit -ve, +ve tracks 
  //---------------------------------------------------//
  BOOST_FOREACH(const ssMap::value_type& charge, charges) {
    tupleFullName.Form("JpsiFromBNoPIDNoMipTuple/%s", 
                       tupleName);
    const TString& muonName = muonNames[charge.first];
    const TString& otherMuonName = otherMuonNames[charge.first];

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
    
    fname.Form("%s/Jpsi_Mu%s_Mag%s_Strip%s_%s.root",
	       outDir, (charge.second).Data(),
	       magPol, stripVersion, index);
    std::cout << "Making J/psi fit for "
                << "particle (charge) = " 
                << muonName.Data() << " (" << charge.second
                << ")" << std::endl;
    try {
        JpsiFit(t, (charge.first).Data(), 
                muonName.Data(), otherMuonName.Data(),
                wsName, fname.Data(), dsName, massName,
                fun_vec, index, printEntries, exitOnBadFit);
    }
    catch (std::exception &e) {
       std::cerr << "Caught exception: " << e.what() << std::endl;
       return EXIT_FAILURE;
    }
    // we should really delete the TChain, but doing so seems to cause
    // occasional segmentation faults
    //delete t;
    //t=NULL;
  }
  return EXIT_SUCCESS;
}
