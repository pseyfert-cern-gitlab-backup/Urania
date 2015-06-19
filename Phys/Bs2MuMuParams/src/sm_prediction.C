//-----------------------------------------------------------------------------
// sm_prediction 
// A program to recompute the sm prediction for Bsmumu BR
// author : Francesco Dettori
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
// Bobeth calculation of the BR
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
  
  cout << " BR = " << BR << "   tex version "<< BR.tex() << endl;



  return BR;
  
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


//============================================================
// MAIN
//============================================================
int main(int argc, char **argv){
  TApplication theApp("App", &argc, argv);

  cout << " Start " << endl;
  
  
  Measurement hslash(6.58211899E-13, 0.00000016E-13);// [GeV ps] PDG
  cout << " Conversion constant hslash " <<  hslash << endl;

  
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
  Measurement Bo112_GammasH_inv(1.615,0.021);        // [ ps ] 
  Measurement Bo112_tauBd(1.519,0.007);              // [ ps ] 
  Measurement Bo112_Vcb(0.0424,0.0009);               // Inclusive (experiment+theory) 
  Measurement Bo112_Vcb_incl(0.04242,0.00086);       // Same as above but with more digits (experiment+theory)...  
  Measurement Bo112_Vcb_excl(0.03955,0.00072,0.00050,2); //  Exclusive (experiment+theory+lattice) 
  Measurement Vcbdiff = Bo112_Vcb_incl-Bo112_Vcb_excl;
  cout << " Difference between Vcb values " << Bo112_Vcb_incl << " - " <<  Bo112_Vcb_excl 
       << " = " <<  Vcbdiff <<  "  sigma=" << Vcbdiff.value()/Vcbdiff.error() << endl;
  
  Measurement Bo112_VtbVts_over_Vcb(0.980,0.001);
  Measurement Bo112_VtbVtd(0.0088,0.0003);
  Measurement Bo112_VtbVts = Bo112_VtbVts_over_Vcb*Bo112_Vcb;
  cout << "This measurement of VtbVts is " << Bo112_VtbVts << endl;
  Measurement Bo112_VtbVts_incl = Bo112_VtbVts_over_Vcb*Bo112_Vcb_incl;
  Measurement Bo112_VtbVts_excl = Bo112_VtbVts_over_Vcb*Bo112_Vcb_excl;
  
  


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
  Measurement Bur_tau_Bs(1.466,0.031);              // [ ps ]
  Measurement Bur_GammasH_inv(1.615,0.021);        // [ ps ] 
  Measurement Bur_tauBd(1.519,0.007);              // [ ps ] 
  Measurement Bur_ys(0.087,0.014);  
  
  
  Measurement Bur_VtbVtd(0.0088,0.0003);
  Measurement Bur_VtbVts(0.0405,0.0008);
  Measurement Bur_sin2thetaw(0.23116, 0.00003);
  
  Measurement Bur_eta_Y(1.0113,0.);
  Measurement Bur_m_t_correction = Bur_M_t.power(3.07)/pow(173.2,3.07);
  Measurement Bur_m_t(163.2,0.);

  cout << " Correction for m_t renorm error is " << Bur_m_t_correction << endl;
  
  Measurement Bur_x_tW =  Bur_m_t.power(2)/Bur_M_W.power(2);
  cout << " Used x_tw is " << Bur_x_tW << endl;
  
  Measurement Bur_Y = Bur_eta_Y*YZero(Bur_x_tW);
  Measurement Bur_C10 = Bur_Y/Bur_sin2thetaw;
  cout << " Yzero is " << YZero(Bur_x_tW) << "   C10 = " <<  Bur_C10 << endl;
  
  
  cout << " Crosscheck sin2theta2 = " <<  Bur_sin2thetaw
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
  cout << "Time factor taubs/(1-ys) " <<  calc_GammasH_inv  << endl;
  cout << "Time factor 1/Gamams_H " <<  Bo112_GammasH_inv << endl;
  


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
  
  
  
  // Branching ratio Bobeth (time integrated) [Baseline]
  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation " << endl;
  Measurement Bo112_BRT = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                            Bo112_alphas_Mz,  Bo112_M_t, 
                            m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                            Bo112_GammasH_inv,  hslash);

  cout << "Error contribution of Vcb only: " << Bo112_BRT.value() * 2 * Bo112_Vcb.error()/ Bo112_Vcb.value() << endl;
  cout << "Error contribution of fBs only: " << Bo112_BRT.value() * 2 * Bo112_f_Bs.error()/Bo112_f_Bs.value() << endl;

  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation with more digits on Vcb" << endl;
  Measurement Bo112_BRT_incl = Bo112BR( Bo112_VtbVts_incl,  Bo112_GF,  Bo112_M_W,
                                        Bo112_alphas_Mz,  Bo112_M_t, 
                                        m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                        Bo112_GammasH_inv,  hslash);

  cout << "============================================================"<< endl;
  cout << "      Bobeth calculation with new top mass" << endl;
  // bobeth with new top mass
  Measurement Bo112_BRT_top = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                                       Bo112_alphas_Mz,  M_t, 
                                       m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                       Bo112_GammasH_inv,  hslash);

  Measurement Bo112_BRT_top_incl = Bo112BR( Bo112_VtbVts_incl,  Bo112_GF,  Bo112_M_W,
                                       Bo112_alphas_Mz,  M_t, 
                                       m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                       Bo112_GammasH_inv,  hslash);
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
  
 cout << "============================================================"<< endl;
 cout << "      Bobeth calculation with calculated 1/Gammas_H" << endl;
 Measurement Bo112_BRT_calcG = Bo112BR( Bo112_VtbVts,  Bo112_GF,  Bo112_M_W,
                                        Bo112_alphas_Mz,  Bo112_M_t, 
                                        m_mu,  Bo112_M_Bs,  Bo112_f_Bs,
                                        calc_GammasH_inv,  hslash);


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
  

  cout << "... this is the end"<< endl;
  //  theApp.Run();
  return 0;

}

