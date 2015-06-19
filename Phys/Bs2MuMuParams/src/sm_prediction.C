//-----------------------------------------------------------------------------
// sm_prediction 
// A program to recompute the sm prediction for Bsmumu BR
// author : Francesco Dettori - francesco.dettori@cern.ch
// date: March 2014
//-----------------------------------------------------------------------------


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "SomeUtils/Measurement.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TH3.h"
#include "TH1.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TCut.h"
#include "TFormula.h"
#include "TString.h"
#include "TGraphErrors.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"
#include "TTime.h"
#include "TTimeStamp.h"
#include "TObjectTable.h"
#include "TAxis.h"
#include "TLatex.h"
#include "TString.h"
#include "TColor.h"


using namespace std;

//============================================================
// Bobeth estimate of the Wilson coefficient
// 
Measurement  Bo112CA(Measurement alpha_s_Mz, Measurement  M_t)
{
  Measurement Rt = M_t/173.1;
  Measurement Ralpha = alpha_s_Mz/0.1184;
  Measurement CA = 0.4690 *Rt.power(1.53)*Ralpha.power(-0.09);
  // Adding additional uncertainties on CA: 
  // 0.3%  from O(alphaem) corrections from mu_b in [m_b/2, 2m_b]
  Measurement rel_1(1,0.003);
  // 2 x 0.2% from O(alpha_s^3, alphaem^2, alphasalphaem) matchint corr. from mu_0 in [m_t/2, 2m_t]
  Measurement rel_2(1,0.004);
  // 0.3% from top-mass conversion from on-shell to MS scheme
  Measurement rel_3(1,0.003);
  // 0.5% further (power correctinos O(m_b^2/M_W^2) etc) 
  Measurement rel_4(1,0.005);
  CA = CA*rel_1*rel_2*rel_3*rel_4;
  return CA;
  
}

//============================================================
// Bobeth calculation of the BR(Bs->mumu)
Measurement Bo112BR(Measurement VtbVts, Measurement GF, Measurement M_W,
                    Measurement alphas_Mz, Measurement M_t, 
                    Measurement m_mu, Measurement M_Bs, Measurement f_Bs,
                    Measurement GammasH_inv, Measurement hslash){
  cout << endl;
  cout << "Bo112BR Calculation of Bo112BR a la Bobeth" << endl;
  
  
  Measurement N = VtbVts * GF.power(2) *M_W.power(2)/pow(TMath::Pi(),2) ;
  cout << "N = " << N << endl;
  Measurement CA = Bo112CA(alphas_Mz, M_t);
  cout << "CA = " << CA << endl;
  
  //  Measurement a(5.0,0.5);
  //  cout << " Test power a= " << a << "    a^2 = " << a.power(2) << "    a^1.5 = " << a.power(1.5) << endl;

  Measurement betasquare = (1 - 4*m_mu.power(2)/M_Bs.power(2));
  Measurement beta = betasquare.power(0.5);
  cout << "Betasquare is " << betasquare << " Beta is " << beta  << endl;
  cout << " N^2  " << N.power(2) << endl
       << " fBs^2 " <<  f_Bs.power(2) << endl
       << " CA^2 " <<  CA.power(2) << endl;
  // Remove the normalisation and put all the error inside C10

  Measurement BR = N.power(2) * M_Bs * f_Bs.power(2) * GammasH_inv * 4 * m_mu.power(2) * beta 
    * CA.power(2) / (8 *TMath::Pi() *hslash);

  // Measurement BR = N.power(2) * M_Bs * f_Bs.power(2) * GammasH_inv * 4 * m_mu.power(2) * beta 
  //   * (0.4690*0.4690) / (8 *TMath::Pi() *hslash);
  
  cout << " BR = " << BR << "   tex version "<< BR.tex() <<  "\t\t relative error: "<< BR.rel_error() << endl;

  return BR;
  
}

//============================================================
// Reverse formula of the BR, to estimate Vcb 
Measurement FDVcb(Measurement VtbVts_over_Vcb, Measurement GF, Measurement M_W,
                  Measurement alphas_Mz, Measurement M_t, 
                  Measurement m_mu, Measurement M_Bs, Measurement f_Bs,
                  Measurement GammasH_inv, Measurement hslash, 
                  Measurement BR_exp){
  cout << endl;
  cout << "Calculation of Vcb from inverse formula  " << endl;
  
  // Get unnormalized theoretical BR from direct formula 
  // But passing VtbVts_over_Vcb 
  Measurement un_BR = Bo112BR(VtbVts_over_Vcb,  GF,  M_W,
                              alphas_Mz,  M_t, 
                              m_mu,  M_Bs,  f_Bs,
                              GammasH_inv,  hslash);
  
  Measurement Vcb_square = BR_exp/un_BR;
  cout << " Vcb_square = " << Vcb_square << endl;
  
  
  return Vcb_square.power(0.5);
  
}




//============================================================
// Bobeth calculation of the BR(Bd->mumu)
Measurement Bo112BRd(Measurement VtbVtd, Measurement GF, Measurement M_W,
                    Measurement alphas_Mz, Measurement M_t, 
                    Measurement m_mu, Measurement M_Bd, Measurement f_Bd,
                    Measurement tauBd, Measurement hslash){
  cout << endl;
  cout << "Bo112BR Calculation of Bo112BR a la Bobeth (Bd)" << endl;
  
  
  Measurement N = VtbVtd * GF.power(2) *M_W.power(2)/pow(TMath::Pi(),2) ;
  cout << "N = " << N << endl;
  Measurement CA = Bo112CA(alphas_Mz, M_t);
  cout << "CA = " << CA << endl;
  
  //  Measurement a(5.0,0.5);
  //  cout << " Test power a= " << a << "    a^2 = " << a.power(2) << "    a^1.5 = " << a.power(1.5) << endl;

  Measurement betasquare = (1 - 4*m_mu.power(2)/M_Bd.power(2));
  Measurement beta = betasquare.power(0.5);
  cout << "Betasquare is " << betasquare << " Beta is " << beta  << endl;
  cout << " N^2  " << N.power(2) << endl
       << " fBd^2 " <<  f_Bd.power(2) << endl
       << " CA^2 " <<  CA.power(2) << endl;
  
  Measurement BR = N.power(2) * M_Bd * f_Bd.power(2) * tauBd * 4 * m_mu.power(2) * beta 
    * CA.power(2) / (8 *TMath::Pi() *hslash);

  cout << " BR = " << BR << "   tex version "<< BR.tex() << endl;
  
  return BR;
  
}

//============================================================
// Calculation of the ratio of branching fractions Bs/Bd
Measurement RB(Measurement VtbVtd, Measurement VtbVts, 
               Measurement f_Bs_over_f_Bd, 
               Measurement m_mu,
               Measurement M_Bd, Measurement M_Bs, 
               Measurement tauBd,   Measurement GammasH_inv)
{
  Measurement RM = M_Bd / M_Bs ;
  //cout << "Mass ratio " << RM << endl;
  //RM.set_error(0.);
  
  
  Measurement RV = VtbVtd / VtbVts;
  //  cout << "Ratio of V matrix " << RV << endl;
  //RV.set_error(0.);
  
  Measurement Rt = tauBd / GammasH_inv;
  //  cout << "Ratio of lifetimes  " << Rt << endl;
  //Rt.set_error(0.);
  
  
  Measurement Rbeta_square  = (1 - 4*m_mu.power(2)/M_Bd.power(2)) / (1 - 4*m_mu.power(2)/M_Bs.power(2));
  Measurement Rbeta = Rbeta_square.power(0.5);
  //Rbeta.set_error(0.);
  
  //cout << "Rbeta  = " << Rbeta << endl;
  //  f_Bs_over_f_Bd.set_error(0);
  
  Measurement R = RM * RV.power(2) * Rt * Rbeta / f_Bs_over_f_Bd.power(2);
  
  return R;
  
}



//============================================================
// Inami-Lim function 
Measurement YZero(Measurement x){
  // All this would require a separate error propagation as they are all correlated
  // we are not a that level yet... 
  Measurement a = (4-x)/(1-x);
  Measurement b = 3*x/((1-x)*(1-x));
  return (x/8)*(a + b*x.ln());
}

//============================================================
// Buras calculation of the BR
Measurement BurBR(Measurement VtbVts, Measurement GF, Measurement M_W,
                  Measurement sin2thetaw, Measurement tau_Bs, 
                  Measurement m_mu, Measurement M_Bs, Measurement f_Bs,
                  Measurement C10, Measurement hslash){
  // Calculation a la buras (1) 
  // Here there is actually a double counting of the error of sin2theta, as it is inside C10,
  // but it's small 

  cout << "BurBR   Calculation a la Buras (1): normalisation with MW " << endl;
  
  Measurement N = GF.power(4)*M_W.power(4)* sin2thetaw.power(2)/(8 *pow(TMath::Pi(),5));
  Measurement   betasquare = 1 - 4*m_mu.power(2)/M_Bs.power(2);
  Measurement BR =  N * tau_Bs *  VtbVts.power(2) * f_Bs.power(2) * M_Bs * m_mu.power(2)
    * betasquare.power(0.5) *C10.power(2)/hslash ; 
  
  return BR;
}

//============================================================
// Buras calculation with different normalisation
Measurement BurBR2(Measurement VtbVts, Measurement GF, Measurement M_W,
                   Measurement alphaem_Mz,   Measurement tau_Bs, 
                   Measurement m_mu, Measurement M_Bs, Measurement f_Bs,
                   Measurement C10, Measurement hslash){
  // Calculation a la buras 
  cout <<  "BurBR Calculation a la Buras (2): normalisation with alpha " << endl;
  
  Measurement Nalt = GF.power(2)*alphaem_Mz.power(2)/(16*pow(TMath::Pi(),3));
  Measurement   betasquare = 1 - 4*m_mu.power(2)/M_Bs.power(2);
  Measurement BR_2 =  Nalt * tau_Bs *  VtbVts.power(2) * f_Bs.power(2) * M_Bs * m_mu.power(2)
    * betasquare.power(0.5) *C10.power(2)/hslash ; 

  return BR_2;
}
void welcome() {
    cout << "============================================================"<< endl;
  cout << "   Standard Model parametric re-calculations   " << endl
       << "   of the B-> mu mu branching fractions    " << endl;
  
}

void help(){
  welcome() ;
  cout << endl 
       <<  "   -d \t    Switches on the debug and additional output    " << endl
       <<  "   -h  \t    Shows this help  " << endl;
  
  
  
}


//============================================================
// MAIN
//============================================================
int main(int argc, char **argv){

  bool debug = false;
  for(Int_t i=1; i<argc; i++){
    TString opt(argv[i]);
    cout << " Parsing option: " << opt << endl;
    if(opt.Contains("-h")){
      help();
      return 0;
    }else if(opt == "-d"){
      Info("...","Debug mode on " );
      debug  = true;
    }else{
      Error("Option parsing...","unknown option %s",opt.Data());
      help();
      return -1;
    }

  }
  
  welcome();
  

  TApplication theApp("App", &argc, argv);
  
  Measurement hslash(6.58211899E-13, 0.00000016E-13);// [GeV ps] PDG
  if( debug ) cout << " Conversion constant hslash " <<  hslash << endl;

  // Experimental value (from naive combination conf note) 
  Measurement BRBs_exp(2.9e-9, 0.7e-9);
  
  
  Measurement m_mu(0.1056583715,0.0000000035); // Mass of the muon [GeV]  

  // Tevatron LHC combination of the mass of top: 
  Measurement M_t(173.34, 0.76); //arXiv 1403.4427
  
  // Inputs to Bobeth PRL 112, 101801 (Bo112)
  Measurement Bo112_GF(1.166379E-5,0.);              // [ GeV^-2 ]
  Measurement Bo112_alphas_Mz(0.1184,0.0007);    
  Measurement Bo112_alphaem_Mz_inv(127.944,0.014);
  Measurement Bo112_alphaem_Mz = 1/Bo112_alphaem_Mz_inv;
  Measurement Bo112_Deltaalpha(0.02772,0.00010);
  Measurement Bo112_M_Z(91.1876, 0.0021) ;           // [ GeV ] 
  Measurement Bo112_M_W(80.358, 0.008) ;             // [ GeV ] 
  Measurement Bo112_M_t(173.1,0.9);                  // [ GeV ] 
  Measurement Bo112_M_H(125.9, 0.4);                 // [ GeV ]  
  Measurement Bo112_M_Bs(5.36677,0.00024);           // [ GeV ] 
  Measurement Bo112_M_Bd(5.27958,0.00017);           // [ GeV ] 
  Measurement Bo112_f_Bs(0.2277, 0.0045);            // [ GeV ] 
  Measurement Bo112_f_Bd(0.1905, 0.0042);            // [ GeV ] 
  Measurement f_Bs_over_f_Bd(1.202, 0.022);          // Adimensional 
  if( debug ) cout << endl << " Cross check fBs/fBd  = " << f_Bs_over_f_Bd 
       << "   from single values =    " << Bo112_f_Bs / Bo112_f_Bd << endl;
  
  Measurement Bo112_GammasH_inv(1.615,0.021);        // [ ps ] 
  Measurement Bo112_tauBd(1.519,0.007);              // [ ps ] 
  Measurement Bo112_Vcb(0.0424,0.0009);               // Inclusive (experiment+theory) 
  Measurement Bo112_Vcb_incl(0.04242,0.00086);       // Same as above but with more digits (experiment+theory)...  
  Measurement Bo112_Vcb_excl(0.03955,0.00072,0.00050,2); //  Exclusive (experiment+theory+lattice) 
  Measurement Vcbdiff = Bo112_Vcb_incl-Bo112_Vcb_excl;
  if( debug ) cout << endl <<  " Difference between Vcb values " << Bo112_Vcb_incl << " - " <<  Bo112_Vcb_excl 
       << " = " <<  Vcbdiff <<  "  sigma=" << Vcbdiff.value()/Vcbdiff.error() << endl;
  
  
  Measurement Bo112_VtbVts_over_Vcb(0.980,0.001);
  Measurement Bo112_VtbVtd(0.0088,0.0003);
  Measurement Bo112_VtbVts = Bo112_VtbVts_over_Vcb*Bo112_Vcb;
  if( debug ) cout << "This measurement of VtbVts is " << Bo112_VtbVts << endl;
  Measurement Bo112_VtbVts_incl = Bo112_VtbVts_over_Vcb*Bo112_Vcb_incl;
  Measurement Bo112_VtbVts_excl = Bo112_VtbVts_over_Vcb*Bo112_Vcb_excl;
  
  Measurement Vcb_pdg(0.0409,0.0015); // PDG with update 2013 (online) 
  Measurement Bo112_VtbVts_pdg = Bo112_VtbVts_over_Vcb*Vcb_pdg;
  
  Measurement Vtd_over_Vts_pdg(0.211, 0.00608); // PDG online 
  


  // Inputs to Buras EPJC 2012 
  Measurement Bur_GF(1.16638E-5,0.);              // [ GeV^-2 ]
  Measurement Bur_alphas_Mz(0.1184,0.0007);    
  Measurement Bur_alphaem_Mz_inv(127.937,0.021);
  Measurement Bur_alphaem_Mz = 1/Bur_alphaem_Mz_inv;
  //  Measurement Bur_Deltaalpha(0.02772,0.00010);
  Measurement Bur_M_Z(91.1876, 0.0021) ;           // [ GeV ] 
  Measurement Bur_M_W(80.385, 0.015) ;             // [ GeV ] 
  Measurement Bur_M_t(173.2,0.9);                  // [ GeV ] 
  Measurement Bur_M_H(125., 0.);                 // [ GeV ]  
  Measurement Bur_M_Bs(5.36677,0.00024);           // [ GeV ] 
  Measurement Bur_M_Bd(5.27958,0.00017);           // [ GeV ] 
  Measurement Bur_f_Bs(0.227, 0.008);            // [ GeV ] 
  Measurement Bur_f_Bd(0.1905, 0.0042);            // [ GeV ] 
  Measurement Bur_f_Bs_over_f_Bd(1.195,0.);        //
  Measurement Bur_tau_Bs(1.466,0.031);              // [ ps ]
  Measurement Bur_GammasH_inv(1.615,0.021);        // [ ps ] 
  Measurement Bur_tauBd(1.519,0.007);              // [ ps ] 
  Measurement Bur_ys(0.087,0.014);  
  
  
  //Measurement Bur_VtbVtd(0.0088,0.0003);
  Measurement Bur_VtbVtd(0.0087,0.0002);
  Measurement Bur_VtbVts(0.0405,0.0008);
  Measurement Bur_sin2thetaw(0.23116, 0.00003);
  
  Measurement Bur_eta_Y(1.0113,0.);
  Measurement Bur_m_t_correction = Bur_M_t.power(3.07)/pow(173.2,3.07);
  Measurement Bur_m_t(163.2,0.);

  if( debug ) cout << " Correction for m_t renorm error is " << Bur_m_t_correction << endl;
  
  Measurement Bur_x_tW =  Bur_m_t.power(2)/Bur_M_W.power(2);
  if( debug ) cout << " Used x_tw is " << Bur_x_tW << endl;
  
  Measurement Bur_Y = Bur_eta_Y*YZero(Bur_x_tW);
  Measurement Bur_C10 = Bur_Y/Bur_sin2thetaw;
  if( debug ) cout << " Yzero is " << YZero(Bur_x_tW) << "   C10 = " <<  Bur_C10 << endl;
  
  
  if( debug ) cout << endl <<" Crosscheck sin2theta2 = " <<  Bur_sin2thetaw
       << " or indirectly  " << TMath::Pi() * Bur_alphaem_Mz/(sqrt(2)*Bur_GF *Bur_M_W.power(2))
       << " ratio " <<  Bur_sin2thetaw/ (TMath::Pi() * Bur_alphaem_Mz/(sqrt(2)*Bur_GF *Bur_M_W.power(2))) 
       << endl;
  

  // Modified inputs for Buras effective lifetime paper 
  Measurement Fle_f_Bs(0.225, 0.003);            // [ GeV ] 
  Measurement Fle_f_Bd(0.186, 0.004);            // [ GeV ] 
  Measurement Fle_f_Bs_f_Bd(1.205,0.007);        
  Measurement Fle_tau_Bs(1.503,0.010);     // [ ps ]
  
  // Crosscheck of the time correction factors 
  Measurement hfag_DeGammas_Gammas(0.123,0.017);  
  Measurement hfag_ys = hfag_DeGammas_Gammas/2.;
  Measurement hfag_tau_Bs(1.516, 0.011);
  Measurement calc_GammasH_inv = hfag_tau_Bs/(1-hfag_ys);
  

  // ========  UTFIT  =============
  ////  http://www.utfit.org/UTfit/ResultsSummer2014PostMoriondSM
  cout << " UTFIT " << endl;
  Measurement utfit2014_Vtb(0.999121, 0.000021);
  Measurement utfit2014_Vtd_r(0.00879, 0.00017); // Absolute real part
  Measurement utfit2014_Vts_r(0.04095, 0.00055); // Absolute real part 
  Measurement utfit2014_VtbVtd = utfit2014_Vtb * utfit2014_Vtd_r;
  Measurement utfit2014_VtbVts = utfit2014_Vtb * utfit2014_Vts_r;
  Measurement utfit2014_Vtd_over_Vts =  utfit2014_Vtd_r/utfit2014_Vts_r;
  cout << " VtbVtd = " <<  utfit2014_VtbVtd.tex() << endl;
  cout << " VtbVts = " <<  utfit2014_VtbVts.tex() << endl;
  cout << " Vtd/Vts = " <<  utfit2014_Vtd_over_Vts.tex() << endl;
  
  // ========  CKMFitter  =============
  //// http://ckmfitter.in2p3.fr/www/results/plots_moriond14/num/ckmEval_results.html
  cout << " CKM fitter " << endl;
  Measurement ckmfitter2014_Vtb(0.999138, 0.000052, 0.000030,   1);
  Measurement ckmfitter2014_Vtd_r(0.00855, 0.00018, 0.00030,   1);
  Measurement ckmfitter2014_Vts_r(0.04062, 0.00070, 0.00125,   1);
  Measurement ckmfitter2014_VtbVtd = ckmfitter2014_Vtb * ckmfitter2014_Vtd_r;
  Measurement ckmfitter2014_VtbVts = ckmfitter2014_Vtb * ckmfitter2014_Vts_r;
  Measurement ckmfitter2014_Vtd_over_Vts =  ckmfitter2014_Vtd_r/ckmfitter2014_Vts_r;
  cout << " VtbVtd = " <<  ckmfitter2014_VtbVtd.tex() << endl;
  cout << " VtbVts = " <<  ckmfitter2014_VtbVts.tex() << endl;
  cout << " Vtd/Vts = " <<  ckmfitter2014_Vtd_over_Vts.tex() << endl;

  // ========  PDG  =============
  ///http://pdg.lbl.gov/2013/reviews/rpp2013-rev-ckm-matrix.pdf
  cout << " PDG " << endl;
  Measurement pdg2013_Vtb(0.999146, 0.000021, 0.000046,   1);
  Measurement pdg2013_Vtd_r(0.00867, 0.00029, 0.00031,   1);
  Measurement pdg2013_Vts_r(0.0404, 0.0011, 0.0005,   1);
  Measurement pdg2013_VtbVtd = pdg2013_Vtb * pdg2013_Vtd_r;
  Measurement pdg2013_VtbVts = pdg2013_Vtb * pdg2013_Vts_r;
  Measurement pdg2013_Vtd_over_Vts =  pdg2013_Vtd_r/pdg2013_Vts_r;
  cout << " VtbVtd = " <<  pdg2013_VtbVtd.tex() << endl;
  cout << " VtbVts = " <<  pdg2013_VtbVts.tex() << endl;
  cout << " Vtd/Vts = " <<  pdg2013_Vtd_over_Vts.tex() << endl;
  
  


  if( debug ) 
  {
    cout << "Time factor taubs/(1-ys) " <<  calc_GammasH_inv  << endl;
    cout << "Time factor 1/Gamams_H " <<  Bo112_GammasH_inv << endl;
  }
  


  cout << endl 
       << "============================================================"<< endl;
  cout << "           Bd-> mu mu " << endl;
  cout << "============================================================"<< endl;
  
  if( debug ) {
     
    // Baseline calculation from Buras paper 
    Measurement Bur_BR = BurBR(Bur_VtbVts, Bur_GF, Bur_M_W,
                               Bur_sin2thetaw, Bur_tau_Bs, 
                               m_mu, Bur_M_Bs, Bur_f_Bs,
                               Bur_C10, hslash);
    // Buras paper with different normalisation 
    Measurement Bur_BR2 = BurBR2(Bur_VtbVts, Bur_GF, Bur_M_W,
                                 Bur_alphaem_Mz,   Bur_tau_Bs, 
                                 m_mu, Bur_M_Bs, Bur_f_Bs,
                                 Bur_C10, hslash);
    // Buras-Fleischer paper inputs 
    Measurement Fle_BR = BurBR(Bur_VtbVts, Bur_GF, Bur_M_W,
                               Bur_sin2thetaw, Fle_tau_Bs, 
                               m_mu, Bur_M_Bs, Fle_f_Bs,
                               Bur_C10, hslash);
    // Buras-Fleischer paper inputs and different normalisation 
    Measurement Fle_BR2 = BurBR2(Bur_VtbVts, Bur_GF, Bur_M_W,
                                 Bur_alphaem_Mz,   Fle_tau_Bs, 
                                 m_mu, Bur_M_Bs, Fle_f_Bs,
                                 Bur_C10, hslash);
    
    
    cout << " Buras BR with first  normalisation " << Bur_BR 
         << "    with M_t error "<<  Bur_BR*Bur_m_t_correction<< endl;
    cout << " Buras BR with second normalisation " << Bur_BR2 
         << "    with M_t error "<<  Bur_BR2*Bur_m_t_correction<< endl;
    cout << " Buras-Fleischer BR with first normalisation " 
         << Fle_BR << "    with M_t error "<<  Fle_BR*Bur_m_t_correction<< endl;
    cout << " Buras-Fleischer BR with second normalisation " 
         << Fle_BR2 << "    with M_t error "<<  Fle_BR2*Bur_m_t_correction<< endl;
    
    Measurement Fle_BR2T = Fle_BR2 / (1 - Bur_ys);
    cout << " Buras-Fleischer BR with second normalisation corrected for time "  << Fle_BR2T << endl;
    
  }
  
  
  // Branching ratio Bobeth (time integrated) [Baseline]
  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation " << endl;
  Measurement Bo112_BRT = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                            Bo112_alphas_Mz,  Bo112_M_t, 
                            m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                            Bo112_GammasH_inv,  hslash);

  if( debug ) cout << "Error contribution of Vcb only: " << Bo112_BRT.value() * 2 * Bo112_Vcb.error()/ Bo112_Vcb.value() << endl;
  if( debug ) cout << "Error contribution of fBs only: " << Bo112_BRT.value() * 2 * Bo112_f_Bs.error()/Bo112_f_Bs.value() << endl;
  Measurement  Bo112_BRT_vcberror( Bo112_BRT.value(),  Bo112_BRT.value() * 2 * Bo112_Vcb.error()/ Bo112_Vcb.value() );
  if( debug ) 
  {
    
    cout << "============================================================"<< endl;
    cout << "      Bobeth calculation with more digits on Vcb" << endl;
    Measurement Bo112_BRT_incl = Bo112BR( Bo112_VtbVts_incl,  Bo112_GF,  Bo112_M_W,
                                          Bo112_alphas_Mz,  Bo112_M_t, 
                                          m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                          Bo112_GammasH_inv,  hslash);
    cout << "============================================================"<< endl;
    cout << "      Bobeth calculation with Vcb from PDG (average)" << endl;
    Measurement Bo112_BRT_pdg = Bo112BR( Bo112_VtbVts_pdg,  Bo112_GF,  Bo112_M_W,
                                         Bo112_alphas_Mz,  Bo112_M_t, 
                                         m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                         Bo112_GammasH_inv,  hslash);
    cout << "============================================================"<< endl;
    cout << "      Bobeth calculation with VtbVts from PDG (UTFit CKMfitter)" << endl;
    Measurement Bo112_BRT_VtbVts = Bo112BR( Bur_VtbVts,  Bo112_GF,  Bo112_M_W,
                                            Bo112_alphas_Mz,  Bo112_M_t, 
                                            m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                            Bo112_GammasH_inv,  hslash);
  }
  
  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation with new top mass" << endl;
  // bobeth with new top mass
  Measurement Bo112_BRT_top = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                                       Bo112_alphas_Mz,  M_t, 
                                       m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                       Bo112_GammasH_inv,  hslash);
  if( debug ) 
  {
    
    cout << endl <<"              Vcb incl with more digits                  " << endl;
    Measurement Bo112_BRT_top_incl = Bo112BR( Bo112_VtbVts_incl,  Bo112_GF,  Bo112_M_W,
                                              Bo112_alphas_Mz,  M_t, 
                                              m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                              Bo112_GammasH_inv,  hslash);
    cout << endl<<"              Vcb PDG                      " << endl;
    Measurement Bo112_BRT_top_pdg = Bo112BR( Bo112_VtbVts_pdg,  Bo112_GF,  Bo112_M_W,
                                             Bo112_alphas_Mz,  M_t, 
                                             m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                             Bo112_GammasH_inv,  hslash);
    
    cout << endl<<"              VtbVts from CKMfitter and UTFit                " << endl;
    Measurement Bo112_BRT_top_VtbVts = Bo112BR( Bur_VtbVts,  Bo112_GF,  Bo112_M_W,
                                                Bo112_alphas_Mz,  M_t, 
                                                m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                                Bo112_GammasH_inv,  hslash);
  }

  if( debug ) 
  {
    cout << "============================================================"<< endl;
    cout << "      Bobeth calculation with Nf=2 fBs (FLAG) " << endl;
    // Bobeth calculation with fBs taken from Nf=2 lattice average 
    Measurement FLAG_f_Bs_N2(0.235,0.006);
    Measurement Bo112_BRT_N2 = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                                        Bo112_alphas_Mz,  Bo112_M_t, 
                                        m_mu,  Bo112_M_Bs,  FLAG_f_Bs_N2,
                                        Bo112_GammasH_inv,  hslash);
    cout << "Error contribution of fBs only: " << Bo112_BRT_N2.value() * 2 * FLAG_f_Bs_N2.error()/ FLAG_f_Bs_N2.value() << endl;
    cout << "============================================================"<< endl;
    cout << "      Bobeth calculation with exclusive Vcb                 " << endl;
    Measurement Bo112_BRT_excl = Bo112BR( Bo112_VtbVts_excl,  Bo112_GF,  Bo112_M_W,
                                          Bo112_alphas_Mz,  Bo112_M_t, 
                                          m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                          Bo112_GammasH_inv,  hslash);
    cout << "    ...result total error " <<  Bo112_BRT_excl.total_error() << endl;
    cout << "Error contribution of Vcb only: " 
         << Bo112_BRT_excl.value() * 2 * Bo112_Vcb_excl.error()/ Bo112_Vcb_excl.value() << endl;
    cout << endl <<  "            ... and updated top mass                   " << endl;
    Measurement  Bo112_BRT_excl_vcberror( Bo112_BRT_excl.value(),  
                                          Bo112_BRT_excl.value() * 2 * Bo112_Vcb_excl.error()/ Bo112_Vcb_excl.value() );
    Measurement Bo112_BRT_vcb_diff =  Bo112_BRT_vcberror - Bo112_BRT_excl_vcberror;
    cout << "BR difference between inclusive and exclusive " << Bo112_BRT_vcb_diff << "     sigma = "
         <<Bo112_BRT_vcb_diff.value()/Bo112_BRT_vcb_diff.error()<< endl;
    
    Measurement Bo112_BRT_top_excl = Bo112BR( Bo112_VtbVts_excl,  Bo112_GF,  Bo112_M_W,
                                              Bo112_alphas_Mz,  M_t, 
                                              m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                              Bo112_GammasH_inv,  hslash);
    cout << "    ...result total error " <<  Bo112_BRT_top_excl.total_error() << endl;
    cout << "============================================================"<< endl;
    cout << "      Bobeth calculation with calculated 1/Gammas_H" << endl;
    Measurement Bo112_BRT_calcG = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                                           Bo112_alphas_Mz,  Bo112_M_t, 
                                           m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                           calc_GammasH_inv,  hslash);
  }
  if( debug ) 
  {
    
    cout << "============================================================" << endl;
    cout << "   Reverse calculation of Vcb from experimental BR          " << endl;
    // Measurement FDVcb(Measurement VtbVts_over_Vcb, Measurement GF, Measurement M_W,
    //                   Measurement alphas_Mz, Measurement M_t, 
    //                   Measurement m_mu, Measurement M_Bs, Measurement f_Bs,
    //                   Measurement GammasH_inv, Measurement hslash, 
    //                   Measurement BR_exp){
    
    Measurement FDVcb_r = FDVcb( Bo112_VtbVts_over_Vcb,  Bo112_GF,  Bo112_M_W,
                                 Bo112_alphas_Mz,  M_t, 
                                 m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                 Bo112_GammasH_inv,  hslash, 
                                 BRBs_exp);
    Measurement BRBs_noerr(BRBs_exp.value(),0.);
    
    Measurement FDVcb_noerr = FDVcb( Bo112_VtbVts_over_Vcb,  Bo112_GF,  Bo112_M_W,
                                     Bo112_alphas_Mz,  M_t, 
                                     m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                     Bo112_GammasH_inv,  hslash, 
                                     BRBs_noerr);
    
    cout << "Vcb = " << FDVcb_r << endl;
    cout << "  If the BR Bsmumu have zero error : " << endl;
    
    cout << "Vcb = " << FDVcb_noerr << endl;
    cout << endl;
    
  }
  if( debug ) 
  {
    cout << "============================================================"<< endl;
    cout << "     Buras calculation with Bobeth parameters     " << endl;
    // Branching ratio calculated with Buras-Fleischer method 
    // but some of the Bo112 parameters 
    Measurement FleBo_BR =  BurBR2(Bo112_VtbVts, Bur_GF, Bur_M_W,
                                   Bur_alphaem_Mz,   Fle_tau_Bs, 
                                   m_mu, Bur_M_Bs, Bo112_f_Bs,
                                   Bur_C10, hslash);
    cout << " FleBo_BR " << FleBo_BR << "    (integrated: " << FleBo_BR/(1-Bur_ys) << endl;
    
    // Bobeth branching ratio with some of the Buras-Fleischer parameters
    Measurement BoBu_BRT = Bo112BR( Bur_VtbVts,  Bo112_GF,  Bo112_M_W,
                                    Bo112_alphas_Mz,  Bo112_M_t, 
                                    m_mu,  Bo112_M_Bs,  Fle_f_Bs,
                                    Bo112_GammasH_inv,  hslash);
    
    cout << " BoBu (integrated) " << BoBu_BRT << endl;
    
  }
  
  cout << endl 
       << "============================================================"<< endl;
  cout << "           Bd-> mu mu " << endl;
  cout << "============================================================"<< endl;
  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation " << endl;

  Measurement Bo112_BRdT = Bo112BRd( Bo112_VtbVtd,  Bo112_GF,  Bo112_M_W,
                                     Bo112_alphas_Mz,  Bo112_M_t, 
                                     m_mu,  Bo112_M_Bd,  Bo112_f_Bd,
                                     Bo112_tauBd,  hslash);
  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation with new top mass" << endl;
  Measurement Bo112_BRdT_M_t = Bo112BRd( Bo112_VtbVtd,  Bo112_GF,  Bo112_M_W,
                                     Bo112_alphas_Mz,  M_t, 
                                     m_mu,  Bo112_M_Bd,  Bo112_f_Bd,
                                     Bo112_tauBd,  hslash);


  cout << endl 
       << "============================================================"<< endl;
  cout << "        Ratio of branching fractions  " << endl;
  cout << "============================================================"<< endl;
  if(debug)
  {
    
    Measurement R = RB( Bo112_VtbVtd,  Bo112_VtbVts, 
                        f_Bs_over_f_Bd, 
                        m_mu,
                        Bo112_M_Bd,  Bo112_M_Bs, 
                        Bo112_tauBd,    Bo112_GammasH_inv);
    
    cout << " Ratio Bd/Bs  =  " << R.tex() <<  "  Relative error = " << R.rel_error() << endl
         << " 1/R          =  " << R.inverse().tex() << endl;
    
    cout << endl << "Calculation from Vtd/Vts : " << endl;
    
    Measurement R_precise = RB( Vtd_over_Vts_pdg, Measurement(1,0.), 
                                f_Bs_over_f_Bd, 
                                m_mu,
                                Bo112_M_Bd,  Bo112_M_Bs, 
                                Bo112_tauBd,    Bo112_GammasH_inv);
    
    cout << " Ratio Bd/Bs  =  " << R_precise.tex() <<  "  Relative error = " << R_precise.rel_error()<< endl;
    
    Measurement Rcheck = Measurement(1.06e-10, 0.09e-10) / Measurement(3.65e-9,0.23e-9);
  
    cout << endl << "Crosscheck from Bobeth paper ratio of single values "  
         << Rcheck << "    Rel error "  << Rcheck.rel_error() << endl << endl;
  }
  
  
  
    
  if(debug)
  {
    
    Measurement R_diego =  RB(Bur_VtbVtd, Bur_VtbVts,
                              Bur_f_Bs_over_f_Bd, 
                              m_mu,
                              Bur_M_Bd,  Bur_M_Bs, 
                              Bur_tauBd, 
                              Bur_tau_Bs);
    
    
    cout  << "Ratio with Diego's parameters " << R_diego.tex() << "   Relative error " << R_diego.rel_error() << endl
          << " 1/R = " << 1/R_diego << endl;
    
    Measurement R_diego_3 =   RB( Bur_VtbVtd/Bur_VtbVts, Measurement(1,0.), 
                                  f_Bs_over_f_Bd, 
                                  m_mu,
                                  Bo112_M_Bd,  Bo112_M_Bs, 
                                  Bo112_tauBd,  hfag_tau_Bs);//  Bo112_GammasH_inv);
    
    cout  << "Ratio with Diego's parameters " << R_diego_3.tex() << "   Relative error " << R_diego_3.rel_error() << endl
          << " 1/R = " << 1/R_diego_3 << endl;
    

  }
  
  
  Measurement R_to_use =  RB(pdg2013_Vtd_over_Vts, Measurement(1,0.),
                             f_Bs_over_f_Bd, 
                            m_mu,
                            Bo112_M_Bd,  Bo112_M_Bs, 
                            Bo112_tauBd,    Bo112_GammasH_inv);
  cout  << "Ratio Bd/Bs " << R_to_use.tex() << "   Relative error " << R_to_use.rel_error() << endl
        << " 1/R = " << 1/R_to_use << endl;
  
  
  cout << "============================================================"<< endl;  
  
  


  cout << "... this is the end"<< endl;







  //  theApp.Run();
  return 0;

}

