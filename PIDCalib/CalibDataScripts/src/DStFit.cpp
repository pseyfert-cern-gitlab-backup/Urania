
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
#include "RooPhysFitter/RooDstarD0MassFitter.h"

// Include files (local)
#include "CalibDataScripts/SetSpectatorVars.h"
#include "CalibDataScripts/DStFit.h"
#include "CalibDataScripts/GetData.h"
#include "CalibDataScripts/LHCbStyle.h"
#include "CalibDataScripts/CheckFitResults.h"

// Namespaces
namespace bass=boost::assign;
using namespace std;

// typedefs
typedef std::map<TString,TString> ssMap;

void DStFit(TChain* ch,
            const char* charge,
            const char* pName,
            const char* wsName,
            const char* fName,
            const char* dsName,
            const char* d0Name,
            const char* delmName,
            std::vector<fptr>& fun_vec,
            const char* index,
            Bool_t verbose,
            Bool_t exitOnBadFit) 
{  
  //==================================================//
  // Constants
  //==================================================//
  const Float_t d0MassPDG=1864.83;
  const Float_t delmPDG=145.421;
  const Float_t piPDG=139.57018;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooPhysFit::RooDstarD0MassFitter* massFitter 
    = new RooPhysFit::RooDstarD0MassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(d0Name);
  massFitter->SetDelmName(delmName);
  massFitter->MakeDMassVar(1823,
                           1920,
                           "MeV/c^{2}",
                           "m_{K#pi}");

  massFitter->MakeDelmVar( 141,//delmPDG-6.0,
                          delmPDG+7.0,
                          "MeV/c^{2}",
                          "m_{K#pi#pi_{s}}-m_{K#pi}");
  if (verbose) {
    massFitter->SetPrintEntriesFlag(kTRUE);
  }

  //==================================================//
  // If pName is sPi, set DataSet name to Pi
  //==================================================//
  const char* DSpName = NULL;
  if(strcmp(pName,"Pi")==0 || strcmp(pName,"K")==0)
    DSpName = pName;
  else if(strcmp(pName,"sPi")==0)
    DSpName = "Pi";
  else
  {
    std::cerr << "D* " << charge << " " << pName 
              << "fit: Unexpected particle name "
              << pName << std::endl;
    exit(EXIT_FAILURE);
  }
    
  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout << "Adding Spectator Vars" << std::endl;
    (*itr)(*massFitter, DSpName, pName);
  }
  
  //==================================================//
  // Select tracks with specific charge  (h+ = +ve ID)
  //==================================================//
  TString chrg="";
  if(strcmp(charge, "Positive")==0)
    chrg = "1";
  else if(strcmp(charge,"Negative")==0)
    chrg = "-1";
  else{
    std::cerr << "D* " << charge << " " << pName 
              << "fit: Unexpected charge type " << charge
              << std::endl;
    exit(EXIT_FAILURE);
  }

  massFitter->MakeDelmDataSet(ch, 
                              "D0_M", 
                              "DSt_M", 
                              dsName, 
                              "", 
                              TString::Format("%s_ID/abs(%s_ID) == "+chrg, pName,       pName).Data(),
                              kFALSE);


  //==================================================//
  // Configure D0 Line Shape
  //==================================================//
  massFitter->MakeDMassSigBiGauss(d0MassPDG, d0MassPDG-5, d0MassPDG+5,
                                  8.0, 7.0, 9.0,
                                  2.0, 1.5, 2.5, 
                                  0.8);
  
  //==================================================//
  // Configure D0 Background Shape
  //==================================================//
  massFitter->MakeDMassBkgFlat(-0.4, -5., -0.05);
  massFitter->MakeDMassBkgExpForMult(-0.0, -20.0, 20.0);
  //  massFitter->MakeDMassBkgQuadratic(-0.3, -0.8, -0.1,
  //                                 -0.3, -0.8, -0.1);
                                    
  //==================================================//
  // Configure DeltaM Line Shape
  //==================================================//
  massFitter->MakeDelmSigBiGauss(delmPDG, delmPDG-1.0, delmPDG+1.0, 
                                 0.55, 0.45, 0.65,
                                 2.0, 1.5, 2.5,
                                 0.55); 
  


  //==================================================//
  // Configure DeltaM Background Shape
  //==================================================//
  /*   
massFitter->MakeDelmBkgDstD0BG(piPDG, piPDG+10, piPDG+10,//dm0 (threshold)
                                 15.8, 1.0, 17.0,          //c   (exponent)
                                 2.9,   1.0,  5.0,         //a   (power)
                                 -7.4, -15.0, -6.0);       //b   (linear)
  */

  massFitter->MakeDelmBkgThreshold( 4.0,-10.0,10.0);
 massFitter->MakeDelmBkgThresholdForWS( 4.0,-10.0,10.0);
 /*
massFitter->MakeDelmBkgDstD0BGForWS(piPDG, piPDG+10, piPDG+10,//dm0 (threshold)
                                 15.8, 1.0, 17.0,          //c   (exponent)
                                 2.9,   1.0,  5.0,         //a   (power)
                                 -7.4, -15.0, -6.0);       //b   (linear)
 */
  //Fix b and c parameters for better fit
  /* massFitter->MakeDelmBkgDstD0BG(piPDG,piPDG-1, piPDG+1,//dm0 (threshold)
                                 5.0,                   //c   (exponent)
                                 2.3,   1.8,  2.,      //a   (power)
                                 -8);                   //b   (linear)
  */

  // Use two-body phase space PDF (expanded to 2nd order) by Mat Charles et al.
  //massFitter->MakeDelmBkgTwoBodyPhsp(0.1, -10., 0., // 1st order coefficient
  //                                   0.1, -10., 0. // 2nd order coefficient
   //                                  );
                                           
  //==================================================//
  // Make composite model with following estimate of 
  // yield breakdown
  //==================================================//
  massFitter->MakeDelmModel(0.65, /* frac(signal) */
                            0.150, /* frac(comb) */
                            0.19, /* frac(wrong pi_s) */
                            0.01); /* frac(bkg-like D0, signal-like delta(m) */
  
  //==================================================// 
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  std::vector<Int_t> FitStrategies = bass::list_of(0)(2);
  int nbins_d0 = 150;
  int nbins_delm = 150;
  massFitter->PerformDelmIterativeBinnedFit(nbins_d0,
                                            nbins_delm,
                                            FitStrategies,
                                            "fitResults", 
                                            1, // use single thread for batch processing
                                            kTRUE, /* save snapshot */
                                            kTRUE, /* print results */
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
    cerr << "D* " << charge << " " << pName
         << " fit failed to converge: "
         << endl;
    if (minuit2Message!="OK.") cerr << minuit2Message << endl;
    if (minosMessage!="OK.") cerr << minosMessage << endl;
    if (hesseMessage!="OK.") cerr << hesseMessage << endl;

    //if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  int covQual=-1;
  if ( !(checkCovQual(*massFitter, "fitResults", covQual)) ) 
  {
    cerr << "D* " << charge << " " << pName 
         << " fit has invalid covariance matrix: " 
         << getCovQualMessage(covQual) << endl;
    //if (exitOnBadFit) exit(EXIT_FAILURE);
  }
  
  // print warning if EDM is > 1e-2
  double edm = -9999.;
  if ( !(checkEDM(*massFitter, "fitResults", edm)) ) 
  {
    cerr << "D* " << charge << " " << pName
         << " fit has EDM > 1e-2 ("
         << std::setprecision(3) << edm << ")" << endl;
    //if (exitOnBadFit) exit(EXIT_FAILURE);
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
  massFitter->AddPdfComponent("sig2DModel",     kRed,      kDashed, 3);
  massFitter->AddPdfComponent("combBkg2DModel", kGreen+3,  kDotted, 3);
  massFitter->AddPdfComponent("piBkg2DModel",   kMagenta,  kDashed, 3);
 massFitter->AddPdfComponent("d0Bkg2DModel",   kCyan,  kDashed, 3);

  TString plotParams_d0="";
  TString plotParams_delm="";
  plotParams_d0="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
  plotParams_delm="delm_sig_mu,delm_sig_sigma0,delm_sig_sigma1";
  massFitter->SetParamBoxAttributes("paramBox",0.62,0.5,0.95,0.93,0.022,12);

  massFitter->SetPlotBins(100); 
  massFitter->SetPlotBins(d0Name, nbins_d0);
  massFitter->SetPlotBins(delmName, nbins_delm);
  
  //==================================================// 
  // Make plots
  //==================================================//
  // RooRealVar* mass=massFitter->GetVar(d0Name);
  massFitter->SetRange(d0Name,d0MassPDG-30,d0MassPDG+30,"sigRange");
  // RooRealVar* delm=massFitter->GetVar("delm");
  massFitter->SetRange(delmName,delmPDG-2.3,delmPDG+2.3,"sigRange");
  TString rangeTitle="sigRegion";
  LHCbStyle();
  
  //==================================================// 
  // Plot D0 Mass Fit
  //==================================================//
  massFitter->SetPlotParameters(plotParams_d0.Data());
  
  RooPlot* rp_mass = massFitter->PlotFitResults(d0Name, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data(),
                                                kFALSE /* use SumW2 errors */
                                                );

  // get the pull plot
  RooPlot* rp_mass_pull = massFitter->PlotFitPulls(d0Name,
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
  
  c1->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.eps", d0Name,pName,
                             charge, index).Data());
  
  //==================================================// 
  // Plot DeltaM Fit
  //==================================================//
  massFitter->SetPlotParameters(plotParams_delm.Data());
  RooPlot* rp_delm = massFitter->PlotFitResults(delmName, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data(),
                                                kFALSE /* use SumW2 errors */
                                                );

  // get the pull plot
  RooPlot* rp_delm_pull = massFitter->PlotFitPulls(delmName,
                                                   "fitResults");
  rp_delm_pull->SetTitle(";;");
  rp_delm_pull->SetLabelSize(0.12, "X");
  rp_delm_pull->SetLabelSize(0.12, "Y");
  
  TCanvas* c2 = new TCanvas("cnv_delm", "", 900, 900);
  TPad* c2_upper = new TPad("cnv_delm_upper", "", 0.005, 0.25, 0.995, 0.995);
  TPad* c2_lower = new TPad("cnv_delm_lower", "", 0.005, 0.05, 0.995, 0.245);
  c2_upper->Draw();
  c2_lower->Draw();
    
  // plot the mass
  c2_upper->cd();
  rp_delm->Draw();

  // plot the pulls
  c2_lower->cd();
  rp_delm_pull->Draw();

  c2->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.eps",delmName,pName,
                             charge,index).Data());

  //==================================================// 
  // Plot weighted DLL(K-pi) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  TString varName;
  varName.Form("%s_CombDLLK",DSpName);
  massFitter->SetRange(varName.Data(), -150., 150., "hasRichRange");
  
  RooPlot* rp_pidk = massFitter->PlotVariable(varName.Data(),
                                               "", "hasRichRange", kTRUE);
  TCanvas* c3 = new TCanvas("cnv_pidk",
                            "", 1024, 768);
  rp_pidk->Draw();
  c3->SaveAs(TString::Format("DLLK_%s_%s_%s.eps",pName,charge,index).Data());
  
  //==================================================// 
  // Plot weighted ProbNN(K) distribution
  //==================================================//
  RooPlot* rp_probnnk = massFitter->PlotVariable(TString::Format("%s_V2ProbNNK",
                                                                 DSpName).Data(),
                                                 "", "", kTRUE);
  TCanvas* c4 = new TCanvas("cnv_probnnk", "", 1024, 768);
  rp_probnnk->Draw();
  c4->SaveAs(TString::Format("ProbNNk_%s_%s_%s.eps",pName,charge,index).Data());
  
  //==================================================// 
  // Plot weighted ProbNN(pi) distribution
  //==================================================//
  RooPlot* rp_probnnpi = massFitter->PlotVariable(TString::Format("%s_V2ProbNNpi",
                                                                  DSpName).Data(),
                                                  "", "", kTRUE);
  TCanvas* c5 = new TCanvas("cnv_probnnpi", "", 1024, 768);
  rp_probnnpi->Draw();
  c5->SaveAs(TString::Format("ProbNNpi_%s_%s_%s.eps",pName,charge,
                             index).Data());
  
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
  delete rp_mass;
  rp_mass=NULL;
  delete rp_delm;
  rp_delm=NULL;
  delete rp_pidk;
  rp_pidk=NULL;
  delete rp_probnnk;
  rp_probnnk=NULL;
  delete rp_probnnpi;
  rp_probnnpi=NULL;
  delete massFitter;
  massFitter=NULL;
}

void usage(const char* fname, ostream& os = cout) {
    os << "Usage: " << fname << " <partName> "
       << "<magPol> <stripVersion> <dataType> "
       << "<index> <outputDir> <verbose?> <exitOnBadFit?> "
       << "<inputFile0> (<inputFile1> ...)" << endl << endl;
    os << "Example: " << fname << " \"K\" \"Down\" "
       << "\"20\" \"2012\" \"0\" \"/output/dir\" "
       << "\"1\" \"1\" \"/input/dir/0/infile.root\"" << endl;
}

int main(int argc, char *argv[])
{
  ssMap charges = bass::map_list_of("Negative", "Minus")("Positive", "Plus");
  const char* wsName="RSDStCalib";
  const char* dsName="data";
  const char* d0MassName="mass";
  const char* deltaMassName="delm";
  const char* tupleName="CalibPID";

  //---------------------------------------------------//
  // argv parameters:
  // 1: Particle Name in nTulpe
  // 2: Field Orientation (Up or Down)
  // 3: Stripping version
  // 4: Datatype (e.g. '2011' or '2012')
  // 5: Subset index
  // 6: Output directory
  // 7: Print entries flag (1=print entries, 0=don't print entries)
  // 8: Exit on bad fit flag (1 = exit if fit, covariance or EDM quality is bad,
  //    0 = print error message on bad fit, but don't exit)
  // 9: File(s) to run over
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
  fun_vec.push_back(SetSpecVars_KPiMuonUNB);
  //---------------------------------------------------//
  // Fit -ve and +ve tracks 
  //---------------------------------------------------//
  TString fname;
  TString tupleFullName=TString::Format("DSt2D0Pi_D02RSKPiTuple/%s", tupleName);
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

    fname.Form("%s/DSt_%s%s_Mag%s_Strip%s_%s.root",
               outDir, pName, (charge.second).Data(), magPol, stripVersion, index);
    std::cout << "Making D* fit for particle (charge) = " << pName << " (" << charge.second
              << ")" << std::endl;
    try {
      DStFit(t, (charge.first).Data(), pName, wsName, fname.Data(), dsName, 
        	   d0MassName, deltaMassName, fun_vec, index, printEntries, exitOnBadFit);
    }
    catch (std::exception &e) {
       std::cerr << "Caught exception: " << e.what() << std::endl;
       return EXIT_FAILURE;
    }
    // we should really delete the TChain, but doing so seems to cause
    // occasional segmentation fault
    //delete t;
    //t=NULL;
  } 
  
  return EXIT_SUCCESS;
}

