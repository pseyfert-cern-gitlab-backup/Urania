// @(#)root/tmva $Id: TMVAClassification.C 38895 2011-04-18 11:59:54Z evt $
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TMath.h"

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVAGui.C"
#include "TMVA/MethodBase.h"

#include "flat2013.h"


#include "flatter.h"

//#include "flatter_0x141cf818.h"
//#include "flatter_0x145cf818.h"
//#include "flatter_0x149cf818.h"

#include "flatter_0x145cf818.h"
#include "flatter_0x141cf018.h"
#include "flatter_0x145cf018.h"
#include "flatter_0x149cf018.h"
#include "flatter_0x141cf818.h"
#include "flatter_0x149cf818.h"
#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

#endif



TTree* TMVACC( TString myMethodList = "" , int varset = 0xFFFFFF, TTree* intree = NULL, TTree* outtree = NULL)
{
  if (NULL==intree) return outtree;
  Long64_t nentries = intree->GetEntriesFast();
  if (0==nentries) return outtree;
  flat2013 ntup = flat2013(intree);
  TMVA::Tools::Instance();

  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;

  TMVA::Reader *reader = new TMVA::Reader( "!Silent:!Color" );

  if (varset & 1 << 0)
    reader->AddVariable("FlightDistance",&ntup.FlightDistance);
  if (varset & 1 << 1)
    std::cerr << "NONONONONO 1\n";

  float trans_ct;
  if (varset & 1 << 20)
    reader->AddVariable("TMath::Exp(-1000*LifeTime)",&trans_ct);

  if (varset & 1 << 2)
    reader->AddVariable("IP",&ntup.IP);

  if (varset & 1 << 3)
    reader->AddVariable("IPSig",&ntup.IPSig);
  if (varset & 1 << 4)
    reader->AddVariable("VertexChi2",&ntup.VertexChi2);
  float trans_dira;
  if (varset & 1 << 18)
    reader->AddVariable("acos(dira)",&trans_dira);

  if (varset & 1 << 19)
    reader->AddVariable("pt",&ntup.pt);


  //daughter kinematic
  if (varset & 1 << 5)
    reader->AddVariable("p0_IP",&ntup.p0_IP);
  if (varset & 1 << 6)
    reader->AddVariable("p1_IP",&ntup.p1_IP);
  if (varset & 1 << 7)
    reader->AddVariable("p2_IP",&ntup.p2_IP);

  if (varset & 1 << 8)
    reader->AddVariable("p0_IPSig",&ntup.p0_IPSig);

  if (varset & 1 << 9)
    reader->AddVariable("p1_IPSig",&ntup.p1_IPSig);

  if (varset & 1 << 10)
    reader->AddVariable("p2_IPSig",&ntup.p2_IPSig);

  if (varset & 1 << 11)
    reader->AddVariable("Laura_SumBDT",&ntup.Laura_SumBDT);
    
  float min_ipsig;
  if (varset & 1 << 12)
    reader->AddVariable("min(p0_IPSig,min(p1_IPSig,p2_IPSig))",&min_ipsig);
  //std::cerr << "NONONONONO 12" << std::endl;

  if (varset & 1 << 13)
    reader->AddVariable("DOCAone",&ntup.DOCAone);

  if (varset & 1 << 14)
    reader->AddVariable("DOCAtwo",&ntup.DOCAtwo);

  if (varset & 1 << 15)
    reader->AddVariable("DOCAthree",&ntup.DOCAthree);

  if (varset & 1 << 16)
    std::cerr << "NONONONONO 16" << std::endl;


  //isolations
  if (varset & 1 << 21)
    reader->AddVariable("isolationa",&ntup.isolationa);
  if (varset & 1 << 21)
    reader->AddVariable("isolationb",&ntup.isolationb);

  if (varset & 1 << 21)
    reader->AddVariable("isolationc",&ntup.isolationc);

  if (varset & 1 << 22)
    reader->AddVariable("isolationd",&ntup.isolationd);

  if (varset & 1 << 22)
    reader->AddVariable("isolatione",&ntup.isolatione);

  if (varset & 1 << 22)
    reader->AddVariable("isolationf",&ntup.isolationf);

  if (varset & 1 << 23)
    reader->AddVariable("iso",&ntup.iso);

  if (varset & 1 << 24)
    reader->AddVariable("CDF1",&ntup.CDF1);

  if (varset & 1 << 25)
    reader->AddVariable("CDF2",&ntup.CDF2);

  if (varset & 1 << 26)
    reader->AddVariable("CDF3",&ntup.CDF3);


  if (varset & 1 << 27) {
    reader->AddVariable("p0_track_Chi2Dof",&ntup.p0_track_Chi2Dof);
    reader->AddVariable("p1_track_Chi2Dof",&ntup.p1_track_Chi2Dof);
    reader->AddVariable("p2_track_Chi2Dof",&ntup.p2_track_Chi2Dof);

  }
  if (varset & 1 << 28) {
    reader->AddVariable("p0_track_MatchChi2",&ntup.p0_track_MatchChi2);
    reader->AddVariable("p1_track_MatchChi2",&ntup.p1_track_MatchChi2);
    reader->AddVariable("p2_track_MatchChi2",&ntup.p2_track_MatchChi2);

  }

  if (varset & 1 << 30) {
    reader->AddVariable("polarisationangle",&ntup.polarisationangle);
  }
  if (varset & 1 << 31) {
    reader->AddVariable("mass_p0p2",&ntup.mass_p0p2);
    reader->AddVariable("mass_p1p2",&ntup.mass_p1p2);
  }


  //reader->AddSpectator("truetau",&ntup.truetau);
  //reader->AddSpectator("NeuroBayes_0x109cf818",&ntup.NeuroBayes_0x109cf818);
  //reader->AddSpectator("NeuroBayes_0x119cf818",&ntup.NeuroBayes_0x119cf818);
  //reader->AddSpectator("NeuroBayes_0x129cf818",&ntup.NeuroBayes_0x129cf818);
  //reader->AddSpectator("NeuroBayes_0x141cf818",&ntup.NeuroBayes_0x141cf818);
  //reader->AddSpectator("NeuroBayes_0x143cf818",&ntup.NeuroBayes_0x143cf818);
  //reader->AddSpectator("NeuroBayes_0x145cf818",&ntup.NeuroBayes_0x145cf818);
  //reader->AddSpectator("NeuroBayes_0x149c1818",&ntup.NeuroBayes_0x149c1818);
  //reader->AddSpectator("NeuroBayes_0x149ce018",&ntup.NeuroBayes_0x149ce018);
  //reader->AddSpectator("NeuroBayes_0x149ce718",&ntup.NeuroBayes_0x149ce718);
  //reader->AddSpectator("NeuroBayes_0x149cf818",&ntup.NeuroBayes_0x149cf818);
  //reader->AddSpectator("NeuroBayes_0x149d1818",&ntup.NeuroBayes_0x149d1818);
  //reader->AddSpectator("NeuroBayes_0x1c9cf818",&ntup.NeuroBayes_0x1c9cf818);

  //reader->BookMVA( TString("BDT method"), TString(Form("weights/Geo_v4_%x_BT.weights.xml",varset)));
  reader->BookMVA( TString("BDT method"), TString(Form("weights/GeoMVA2013_v3_b_%x_BDT.weights.xml",varset)));
  reader->BookMVA( TString("BDTold method"), TString(Form("weights/GeoMVA2013_v3_b_%x_BDTold.weights.xml",varset)));
  reader->BookMVA(TString("MLP method"),TString(Form("weights/GeoMVA2013_v3_b_%x_MLP.weights.xml",varset)));
  reader->BookMVA(TString("MLPCJ method"),TString(Form("weights/GeoMVA2013_v3_b_%x_MLPCJ.weights.xml",varset)));
  //reader->BookMVA(TString("MLPBFGS method"),TString(Form("weights/GeoMVA2013_v3_%x_MLPBFGS.weights.xml",varset)));
  //reader->BookMVA(TString("MLPMSE method"),TString(Form("weights/GeoMVA2013_v3_%x_MLPMSE.weights.xml",varset)));
  //reader->BookMVA(TString("MLPMSEBFGW method"),TString(Form("weights/GeoMVA2013_v3_%x_MLPMSEBFGW.weights.xml",varset)));
  //reader->BookMVA(TString("MLPBNN method"),TString(Form("weights/GeoMVA2013_v3_%x_MLPBNN.weights.xml",varset)));




  float response;
  float responseold;
  float mlp_response;
  float mlpcj_response;
  float mlpbfgs_response;
  float mlpmse_response;
  float mlpmsebfgw_response;
  float mlpbnn_response;
  float flat_response;
  //outtree = intree->CloneTree(0);
  TBranch* b_nb   = outtree->Branch(Form("TMVA_v3_b_0x%x",varset),&response,Form("TMVA_v3_b_0x%x/F",varset));
  TBranch* b_nbold   = outtree->Branch(Form("oldTMVA_v3_b_0x%x",varset),&responseold,Form("oldTMVA_v3_b_0x%x/F",varset));
  TBranch* b_nb3  = outtree->Branch(Form("MLP_v3_b_0x%x",varset),&mlp_response,Form("MLP_v3_b_0x%x/F",varset));
  TBranch* b_nb4  = outtree->Branch(Form("MLPCJ_v3_b_0x%x",varset),&mlpcj_response,Form("MLPCJ_v3_b_0x%x/F",varset));
  //TBranch* b_nb5  = outtree->Branch(Form("MLPBFGS_v3_0x%x",varset),&mlpbfgs_response,Form("MLPBFGS_v3_0x%x/F",varset));
  //TBranch* b_nb6  = outtree->Branch(Form("MLPMSE_v3_0x%x",varset),&mlpmse_response,Form("MLPMSE_v3_0x%x/F",varset));
  //TBranch* b_nb7  = outtree->Branch(Form("MLPMSEBFGW_v3_0x%x",varset),&mlpmsebfgw_response,Form("MLPMSEBFGW_v3_0x%x/F",varset));
  //TBranch* b_nb8  = outtree->Branch(Form("MLPBNN_v3_0x%x",varset),&mlpbnn_response,Form("MLPBNN_v3_0x%x/F",varset));
  ////TBranch* b_nb2  = outtree->Branch(Form("flat_TMVA_v3_0x%x",varset),&flat_response,Form("flat_TMVA_v3_0x%x/F",varset));

  std::cout << "now file " << intree->GetCurrentFile()->GetName() << std::endl;

  TabulatedFunction1D* lookuptable;


  if (0x109cf818==varset) lookuptable=flatter<0x109cf818>();
  if (0x119cf818==varset) lookuptable=flatter<0x119cf818>();
  if (0x129cf818==varset) lookuptable=flatter<0x129cf818>();
  if (0x141cf818==varset) lookuptable=flatter<0x141cf818>();
  if (0x143cf818==varset) lookuptable=flatter<0x143cf818>();
  if (0x145cf818==varset) lookuptable=flatter<0x145cf818>();
  if (0x149c1818==varset) lookuptable=flatter<0x149c1818>();
  if (0x149ce018==varset) lookuptable=flatter<0x149ce018>();
  if (0x149ce718==varset) lookuptable=flatter<0x149ce718>();
  if (0x149cf818==varset) lookuptable=flatter<0x149cf818>();
  if (0x149d1818==varset) lookuptable=flatter<0x149d1818>();
  if (0x1c9cf818==varset) lookuptable=flatter<0x1c9cf818>();
  if (0x549cf818==varset) lookuptable=flatter<0x549cf818>();
  if (0x145cf818==varset) lookuptable=flatter<0x145cf818>();
  if (0x141cf018==varset) lookuptable=flatter<0x141cf018>();
  if (0x145cf018==varset) lookuptable=flatter<0x145cf018>();
  if (0x149cf018==varset) lookuptable=flatter<0x149cf018>();
  if (0x141cf818==varset) lookuptable=flatter<0x141cf818>();
  if (0x149cf818==varset) lookuptable=flatter<0x149cf818>();

  std::cout << "initialised flattener" << std::endl;


  for (Long64_t jentry = 0 ; jentry< nentries;jentry++) {
  //  std::cout << "get entry" << std::endl;
    intree->GetEntry(jentry);
    if (0==ntup.cleaningcut) continue;
    //std::cout << "compute entry" << std::endl;
    
    trans_dira = acos(ntup.dira);
    trans_ct = TMath::Exp(-1000*ntup.LifeTime);
    min_ipsig = std::min(ntup.p0_IPSig,std::min(ntup.p1_IPSig,ntup.p2_IPSig));

   // std::cout << "computed entry" << std::endl;



    response = reader->EvaluateMVA( "BDT method" );
    responseold = reader->EvaluateMVA( "BDTold method" );
    //mlp_response = reader->EvaluateMVA( "MLP method" );
    mlp_response = reader->EvaluateMVA("MLP method");
    mlpcj_response = reader->EvaluateMVA("MLPCJ method");
    //mlpbfgs_response = reader->EvaluateMVA("MLPBFGS method");
    //mlpmse_response = reader->EvaluateMVA("MLPMSE method");
    //mlpmsebfgw_response = reader->EvaluateMVA("MLPMSEBFGW method");
    //mlpbnn_response = reader->EvaluateMVA("MLPBNN method");
    //std::cout << "evaluated entry" << std::endl;
    flat_response = lookuptable->value(response);
    if (flat_response <0.) flat_response = 0.;
    if (flat_response >1.) flat_response = 1.;
    //std::cout << "flattened entry" << std::endl;
    outtree->Fill();
//    b_nb->Fill();
//    b_nb2->Fill();



//    std::cout << "filled entry" << std::endl;
  }
  std::cout << "loop finished" << std::endl;

  delete reader;
  delete lookuptable;
  return outtree;

}

int ip, flight,taukin,docas,dira,Tiso,Ciso;
int trchi;
int matchchi;
int varset = 0;
int conditions = 0;
int withpolangle = 0;
int dalitz = 0;
int make_varset(int vars = 0) {
  varset = 0 ;
  varset |= 0x8;
  varset |= 0x10;
  if (0 == ip)
    varset |= 0x700;
  if (1 == ip) 
    varset |= 0x1800;
  if (0 == flight)
    varset |= 0x3;
  if (1 == flight)
    varset |= 0x100000;
  if (2 == flight)
    varset |= 0x100003;
  if (1 == taukin) 
    varset |= 0x080000;
  if (1 == docas)
    varset |= 0xE000;
  if (2 == docas)
    varset |= 0x10000;
  if (1 == dira)
    varset |= 0x40000;
  if (1 == Tiso)
    varset |= 1 << 21;
  if (2 == Tiso)
    varset |= 1 << 22;
  if (3 == Tiso)
    varset |= 1 << 23;
  if (1 == Ciso)
    varset |= 1 << 24;
  if (2 == Ciso)
    varset |= 1 << 25;
  if (3 == Ciso)
    varset |= 1 << 26;
  if (1 == trchi)
    varset |= 1 << 27;
  if (1 == matchchi)
    varset |= 1 << 28;
  if (2 == matchchi)
    varset |= 1 << 29;
  if (1 == withpolangle)
    varset |= 1 << 30;
  if (1 == dalitz)
    varset |= 1 << 31;

  if (0!=vars)
    varset=vars;

//  TString fnames[17];
//  int jjj = 0;
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mcbkg_2011trigger_MC10inclB_DOWN_TRUTHATTEMPT_sm0_flat.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mcbkg_2011trigger_MC10inclB_UP_TRUTHATTEMPT_sm0_flat.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mcbkg_2011trigger_MC10inclC_DOWN_TRUTHATTEMPT_sm0_flat.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mcbkg_2011trigger_MC10inclC_UP_TRUTHATTEMPT_sm0_flat.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC10ds2phipi_DOWN_TRUTHATTEMPT_sm0_flat_509997evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC10ds2phipi_UP_TRUTHATTEMPT_sm0_flat_509995evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC10tau23mu_DOWN_TRUTHATTEMPT_sm0_flat_78499evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC10tau23mu_UP_TRUTHATTEMPT_sm0_flat_83099evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC11ds2phipi_DOWN_TRUTHATTEMPT_sm0_flat_509996evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC11ds2phipi_UP_TRUTHATTEMPT_sm0_flat_601998evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC11tau23mu_DOWN_TRUTHATTEMPT_sm0_flat_593995evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_MC11tau23mu_UP_TRUTHATTEMPT_sm0_flat_510499evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mcselected_MC10tau23mu_md_TCKEMU_flat_78499evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mcselected_MC10tau23mu_mu_TCKEMU_flat_83099evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_tau2pmumuOS_DOWN_TRUTHATTEMPT_sm0_flat_127800evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_tau2pmumuOS_UP_TRUTHATTEMPT_sm0_flat_140500evts.root";
//  fnames[jjj++] = "/auto/data/pseyfert/NB_MC/mc_tau2pmumuSS_DOWN_TRUTHATTEMPT_sm0_flat_125600evts.root";

  TString fnames[17];
  int jjj = 0;
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclBP6_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclBP6_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclBP8_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclBP8_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclCP6_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclCP6_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclCP8_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclCP8_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_BD_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_B_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_BDs_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_BDs_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_BD_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_B_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_pD_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_pDs_DOWN_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_pDs_UP_TCKEMU_sm0/flat.root";
  fnames[jjj++] = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu_P6_pD_UP_TCKEMU_sm0/flat.root";

  for (int i = 0 ; i < 18 ; ++i) {
    TTree* tree;
    TFile* ff = new TFile(fnames[i].Data(),"read");
    std::map<std::string,int> done;
    for (int treeid = 0 ; treeid < ff->GetListOfKeys()->GetEntries() ; ++treeid) {
      done[ff->GetListOfKeys()->At(treeid)->GetName()] = 0;
    }
    ff->Close();
    delete ff;
    for (std::map<std::string,int>::iterator  it  = done.begin() ; it != done.end() ; ++it) {
      if (1==it->second) continue;
      TFile* ff = new TFile(fnames[i].Data(),"update");
      ff->GetObject((((std::string)it->first).c_str()),tree);
      TMVACC("",varset,tree);
      ff->WriteTObject(tree);
      done[it->first] = 1;
      ff->Close();
      delete ff;
    }
  }

  return varset;
}

void initvar() {

  ip = 1;
  flight = 1;
  taukin = 1;
  docas = 1;
  dira = 1;
  Tiso = 3;
  Ciso = 3;
  trchi = 0;
  matchchi = 1;
  withpolangle = 0;
}

int TMVA_write_Geo() {
  varset = 0;
  conditions = 0;
  if (false) {
    for ( ip = 0 ; ip < 3 ; ++ip) { // 3
      for ( flight = 0 ; flight < 4 ; ++flight) { //4
        for ( taukin = 0 ; taukin < 2 ; ++taukin) { //2
          for ( docas = 0 ; docas < 2 ; ++docas) { //2
            for ( dira = 0 ; dira <2 ; ++dira) { //2
              for ( Tiso = 0 ; Tiso < 2 ; ++Tiso) {
                for ( Ciso = 0 ; Ciso < 2 ; ++Ciso) {
                  varset = 0 ;
                  varset |= 0x8;
                  varset |= 0x10;
                  if (0 == ip)
                    varset |= 0x700;
                  if (1 == ip) 
                    varset |= 0x1800;
                  if (0 == flight)
                    varset |= 0x3;
                  if (1 == flight)
                    varset |= 0x100000;
                  if (2 == flight)
                    varset |= 0x100003;
                  if (1 == taukin) 
                    varset |= 0x080000;
                  if (1 == docas)
                    varset |= 0xE000;
                  if (1 == dira)
                    varset |= 0x40000;
                  if (1 == Tiso)
                    varset |= 1 << 21;
                  if (2 == Tiso)
                    varset |= 1 << 22;
                  if (3 == Tiso)
                    varset |= 1 << 23;
                  if (1 == Ciso)
                    varset |= 1 << 24;
                  if (2 == Ciso)
                    varset |= 1 << 25;
                  if (3 == Ciso)
                    varset |= 1 << 26;
                  ++conditions;
                  TMVACC("",varset);
                }
              }
            }
          }
        }
      } 
    }
  }
  /// force no iso
  varset = ((0x145cf818) | (1 << 22) | (1 << 23)) ^ ((1 << 22) | (1 << 23));
  int basevars = varset;
  make_varset(varset);
  /// force all iso
  varset = basevars | (1 << 22);
  make_varset(varset);
  /// force summ iso
  varset = basevars | (1 << 23);
  make_varset(varset);
  /// lauras iso
  varset = basevars | (1 << 11);
  make_varset(varset);
  /// lauras iso and old iso
  varset = basevars | (1 << 11);
  varset |=  (1 << 23);
  make_varset(varset);


  if (false) {
    //initvar();
    //printf("%x",make_varset());

    initvar();
    //dalitz = 1;
    withpolangle = 1;
    printf("%x",make_varset());
 

  //  initvar();
  //  docas = 2;
  //  make_varset();

  //  initvar();
  //  matchchi = 2;
  //  make_varset();
    
  }
  if (true) {

    initvar();
    trchi = 1;
    make_varset();
 
    initvar();
    matchchi = 1;
    make_varset();

    initvar();
    trchi = 1;
    matchchi = 1;
    make_varset();

    initvar();
    Ciso = 0;
    make_varset();
 
    initvar();
    Ciso = 1;
    make_varset();
 
    initvar();
    Ciso = 2;
    make_varset();
          
    initvar();
    Tiso = 0;
    make_varset();
    
    initvar();
    Tiso = 1;
    make_varset();
    
    initvar();
    Tiso = 2;
    make_varset();
   
    initvar();
    docas = 0;
    make_varset();
    
    initvar();
    docas = 2;
    make_varset();
      
    initvar();
    ip = 0;
    make_varset();
       
    initvar();
    ip = 2;
    make_varset();
     
  }
  return 0;
}

int main(int argc, char** argv) {
  std:: cout << " ============ WELCOME ===========" << std::endl;
  if (2>argc) {
    std::cout << "USAGE TMVA_write_Geo <varset=0x149cf818> <infilename> <outfilename>" << std::endl;
    return 1;
  }
  char* buffer;
  int varset = strtol(argv[1],&buffer,0);
  std::cout << buffer << std::endl;

  printf("varset = 0x%x \t\t%s\n", varset,argv[1]);
  for (int i = 2 ; i < argc ; ++i) {
    printf("file %d: %s\n", i, argv[i]);
  }
  //for (int i = 2 ; i < argc ; ++i) {
  {
    int i = 2;
    TTree* intree;
    TTree* outtree;
    TFile* ff = new TFile(argv[i],"read");
    std::map<std::string,int> done;
    for (int treeid = 0 ; treeid < ff->GetListOfKeys()->GetEntries() ; ++treeid) {
      done[ff->GetListOfKeys()->At(treeid)->GetName()] = 0;
    }
    ff->Close();
    delete ff;
    for (std::map<std::string,int>::iterator  it  = done.begin() ; it != done.end() ; ++it) {
      if (1==it->second) continue;
      printf("now initiating tree %s in file %s for setting 0x%x\n", it->first.c_str(), argv[i], varset);
      TFile* ff_in = new TFile(argv[i],"read");
      ff_in->GetObject((((std::string)it->first).c_str()),intree);
      TFile* ff_out = new TFile(argv[i+1],"update");
      outtree = intree->CloneTree(0);
      printf("now doing tree %s in file %s for setting 0x%x\n", it->first.c_str(), argv[i], varset);
      outtree = TMVACC("",varset,intree,outtree);
      printf("now done tree %s in file %s for setting 0x%x\n", it->first.c_str(), argv[i], varset);
      std::cout << "tree to be written is " << outtree << std::endl;
      ff_out->WriteTObject(outtree);
      printf("now written outtree\n");
      done[it->first] = 1;
      ff_in->Close();
      printf("closed first file\n");
      ff_out->Close();
      printf("closed second file\n");
      delete ff_in;
      printf("deleted first file\n");
      delete ff_out;
      printf("deleted second file\n");
    }
  }

  std:: cout << " ============ GOOD BYE ==========" << std::endl;
  return 0;
}
