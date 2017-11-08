#define NewQ2Variables_cxx
#include "NewQ2Variables.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "TlorentzVector.h"
#include "SemiDec.h"

TLorentzVector Make4V();

void ComputeBMom2Fold(Double_t bMass,
                      TLorentzVector b4V, 
                      TVector3 bDir, 
                      Double_t & pL, 
                      Double_t & pH, 
                      Double_t & det){
      // -----------------------------------------------------------------------------
      // Inputs:
      //    bMass: PDG mass of the Hadron 
      //    b4V: 4-momentum visible of the H, for H-->Cmunu, it is P(C)+P(mu)
      //    bDir: vector of the H direction, from vertex informations: H3-PV3
      // Output: 
      //    pH, pL: High and Low solution of the equation aaa*P^2 + bbb*P + ccc = 0
      //    det: value of bbb^2-4aaa*ccc
      //         if det < 0, solutions are not real, both are set to -bbb/2aaa
      // -----------------------------------------------------------------------------
      TVector3 b3V = b4V.Vect(); // 3-mom of the b-hadron
      Double_t ang=bDir.Angle(b3V);
      
      Double_t aaa = 4*(-pow(b4V.E(),2) + pow(b4V.P()*cos(ang),2));
      Double_t bbb = 4*b4V.P()*cos(ang)*( pow(bMass,2) + b4V.Mag2() );
      Double_t ccc = -4*pow(b4V.E(),2)*pow(b4V.P(),2) + pow(pow(bMass,2)-b4V.Mag2()-2*pow(b4V.P(),2),2);
      det=pow(bbb,2)-4*aaa*ccc;
      pH = -bbb/(2*aaa);
      pL = -bbb/(2*aaa);
      if( det>0 ){
          pL=(-bbb+sqrt(det))/(2*aaa);
          pH=(-bbb-sqrt(det))/(2*aaa);
      }                                    
    return;
}

Double_t hel(TLorentzVector M, 
             TLorentzVector A1, 
             TLorentzVector A2, 
             TLorentzVector B ){
// ------------------------------------------
// Compute the helicity angle of the A meson
// M --> A B
//       A --> A1 A2
// ------------------------------------------      
      B.Boost(-M.BoostVector());
      A1.Boost(-M.BoostVector());
      A2.Boost(-M.BoostVector());

      TLorentzVector A=A1+A2;
      A1.Boost(-A.BoostVector());
      B.Boost(-A.BoostVector());

      TVector3 A1v3=A1.Vect();
      TVector3 Bv3=B.Vect();
      return (A1v3.Dot(Bv3))/(A1v3.Mag()*Bv3.Mag());
}


void NewQ2Variables::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L NewQ2Variables.C
//      Root > NewQ2Variables t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile *newfile=new TFile("small.root","recreate");
   TTree *newtree = fChain->CloneTree(0);

   //add branches -------
   Double_t MassDsG; 
   // DeltaM
   // MassDsMup, MassPimPip, MassDsMuMax, MassDsMuMin;
   //TBranch *bdm=newtree->Branch("DeltaM",&DeltaM,"DeltaM/D"); 
   TBranch *mdg=newtree->Branch("MassDsG",&MassDsG,"MassDsG/D");
   //TBranch *mbmup=newtree->Branch("MassDsMup",&MassDsMup,"MassDsMup/D");
   //TBranch *mbmumax=newtree->Branch("MassDsMuMax",&MassDsMuMax,"MassDsMuMax/D");
   //TBranch *mbmumin=newtree->Branch("MassDsMuMin",&MassDsMuMin,"MassDsMuMin/D");
   //TBranch *mpipi=newtree->Branch("MassPimPip",&MassPimPip,"MassPipPim/D");

   Double_t aDsG;
   //, aDsMup, aDsMum2, aDsMup2;
   TBranch *alcm=newtree->Branch("aDsG",&aDsG,"aDsG/D");
   //TBranch *alcp=newtree->Branch("aDsMup",&aDsMup,"aDsMup/D");
   //TBranch *alcm2=newtree->Branch("aDsMum2",&aDsMum2,"aDsMum2/D");
   //TBranch *alcp2=newtree->Branch("aDsMup2",&aDsMup2,"aDsMup2/D");

   Double_t pBsY, q2Y, mm2Y, thlY, elcmY, wY;
   TBranch *a1 = newtree->Branch("pBsY",&pBsY,"pBsY/D");
   TBranch *a2 = newtree->Branch("q2Y",&q2Y,"q2Y/D");
   TBranch *a3 = newtree->Branch("mm2Y",&mm2Y,"mm2Y/D");
   TBranch *a4 = newtree->Branch("thlY",&thlY,"thlY/D");
   TBranch *a5 = newtree->Branch("elcmY",&elcmY,"elcmY/D");
   TBranch *a6 = newtree->Branch("wY",&wY,"wY/D");

   Double_t pBsP1, q2P1, mm2P1,thlP1, elcmP1, wP1;
   TBranch *b1 = newtree->Branch("pBsP1",&pBsP1,"pBsP1/D");
   TBranch *b2 = newtree->Branch("q2P1",&q2P1,"q2P1/D");
   TBranch *b3 = newtree->Branch("mm2P1",&mm2P1,"mm2P1/D");
   TBranch *b4 = newtree->Branch("thlP1",&thlP1,"thlP1/D");
   TBranch *b5 = newtree->Branch("elcmP1",&elcmP1,"elcmP1/D");
   TBranch *b6 = newtree->Branch("wP1",&wP1,"wP1/D");

   Double_t pBsP2, q2P2, mm2P2,thlP2, elcmP2, wP2;
   TBranch *c1 = newtree->Branch("pBsP2",&pBsP2,"pBsP2/D");
   TBranch *c2 = newtree->Branch("q2P2",&q2P2,"q2P2/D");
   TBranch *c3 = newtree->Branch("mm2P2",&mm2P2,"mm2P2/D");
   TBranch *c4 = newtree->Branch("thlP2",&thlP2,"thlP2/D");
   TBranch *c5 = newtree->Branch("elcmP2",&elcmP2,"elcmP2/D");
   TBranch *c6 = newtree->Branch("wP2",&wP2,"wP2/D");

   Double_t sq;//,aaa,bbb,ccc;  
   Double_t McorrDsss, McorrDs, bSinFlightAng, bFlightLen;

   newtree->Branch("sq",&sq,"sq/D");
//   newtree->Branch("aaa",&aaa,"aaa/D");
//   newtree->Branch("bbb",&bbb,"bbb/D");
//   newtree->Branch("ccc",&ccc,"ccc/D");
   newtree->Branch("McorrDsss",&McorrDsss,"McorrDsss/D");
   newtree->Branch("McorrDs",&McorrDs,"McorrDs/D");
   newtree->Branch("bSinFlightAng",&bSinFlightAng,"bSinFlightAng/D");
   newtree->Branch("bFlightLen",&bFlightLen,"bFlightLen/D");

   // -------------------
   // Constants
   Double_t DsMassPDG(1.96827);
   Double_t BsMassPDG(5366.82);
   Double_t DsstMassPDG(2112.1); 
   Double_t GeV=1000;
   Double_t GeV2= GeV*GeV;
   // -------------------

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if(ientry < 0) break;

      if(ientry%10000<1) cout << ientry << endl; 

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // =====================
      // Some cuts
      // =====================     
      //Float_t Kine = 0;
      //if ( Lambda_c_STAR_PT>2500 && log(Lambda_c_STAR_FD_OWNPV)>2.0 ) Kine = 1;
      //Float_t DsDau = 0;
      //if ( (K_PT+pi_Ds_PT+p_PT)>2100 && Lambda_c_IP_ORIVX < 3) DsDau = 1;

      // =====================

      // =====================
      // Compute Mass-axises
      // =====================

      //DeltaM = Lambda_c_STAR_MM-Lambda_c_MM; // in MeV
      MassDsG = sqrt(((Ds_PE+Ds_0_40_nc_maxPt_PE)*(Ds_PE+Ds_0_40_nc_maxPt_PE)-
                      (Ds_PX+Ds_0_40_nc_maxPt_PX)*(Ds_PX+Ds_0_40_nc_maxPt_PX)-
                      (Ds_PY+Ds_0_40_nc_maxPt_PY)*(Ds_PY+Ds_0_40_nc_maxPt_PY)-
                      (Ds_PZ+Ds_0_40_nc_maxPt_PZ)*(Ds_PZ+Ds_0_40_nc_maxPt_PZ))/1000000)-
                      Ds_MM/1000+DsMassPDG; // GeV
      //MassDsMup = sqrt(((Lambda_c_PE+pi_plus_PE)*(Lambda_c_PE+pi_plus_PE)-
      //                  (Lambda_c_PX+pi_plus_PX)*(Lambda_c_PX+pi_plus_PX)-
      //                  (Lambda_c_PY+pi_plus_PY)*(Lambda_c_PY+pi_plus_PY)-
      //                  (Lambda_c_PZ+pi_plus_PZ)*(Lambda_c_PZ+pi_plus_PZ))/1000000)-
      //                  Lambda_c_MM/1000+DsMassPDG; // GeV
      //MassPimPip = sqrt(((pi_minus_PE+pi_plus_PE)*(pi_minus_PE+pi_plus_PE)-
      //                   (pi_minus_PX+pi_plus_PX)*(pi_minus_PX+pi_plus_PX)-
      //                   (pi_minus_PY+pi_plus_PY)*(pi_minus_PY+pi_plus_PY)-
      //                   (pi_minus_PZ+pi_plus_PZ)*(pi_minus_PZ+pi_plus_PZ))/1000000)-
      //                   Lambda_c_MM/1000+DsMassPDG;
      
      // store max and min DsMu mass 
      //if( MassDsMup > MassDsMum ) {
      //  MassDsMuMax=MassDsMup;
      //  MassDsMuMin=MassDsMum;
      //} else {
      //  MassDsMuMax=MassDsMum;
      //  MassDsMuMin=MassDsMup;
      //}


      // ===================================
      // Reconstructed quantitites
      // ===================================
      TLorentzVector Bs4V(B_s0_PX,B_s0_PY,B_s0_PZ,B_s0_PE); 
      TLorentzVector Mu4V(mu_PX,mu_PY,mu_PZ,mu_PE);
      TLorentzVector Dsst4V(Ds_PX+Ds_0_40_nc_maxPt_PX,Ds_PY+Ds_0_40_nc_maxPt_PY,Ds_PZ+Ds_0_40_nc_maxPt_PZ,Ds_PE+Ds_0_40_nc_maxPt_PE);
      TLorentzVector Ds4V(Ds_PX,Ds_PY,Ds_PZ,Ds_PE);
      //TLorentzVector Pim4V(pi_minus_PX,pi_minus_PY,pi_minus_PZ,pi_minus_PE);
      //TLorentzVector Pip4V(pi_plus_PX,pi_plus_PY,pi_plus_PZ,pi_plus_PE);           
      TLorentzVector DsstMu4V = Dsst4V + Mu4V;
      std::cout << Mu4V.M() << ", " << Dsst4V.M() << std::endl;  
      // ===================================
      // Define elicity angles =============
      // ===================================
      // units mm 
      TVector3 Bs4V3 = Bs4V.Vect();
      TVector3 Bs_dir(B_s0_ENDVERTEX_X - B_s0_OWNPV_X,
                      B_s0_ENDVERTEX_Y - B_s0_OWNPV_Y,
                      B_s0_ENDVERTEX_Z - B_s0_OWNPV_Z);
      Double_t Bs_dir_phi= Bs_dir.Phi();
      Double_t Bs_dir_eta= Bs_dir.Eta();
      Double_t Bs_dir_theta= Bs_dir.Theta();
      Double_t Bs_dir_mag= Bs_dir.Mag();
      Double_t ang=Bs_dir.Angle(Bs4V3);

      bSinFlightAng=sin(Bs_dir_theta);
      bFlightLen=Bs_dir_mag; 
      // ---

      //TLorentzVector DsMum4V=Mu4V+Pim4V;
      //TLorentzVector DsMup4V=Mu4V+Pip4V;
      
      //DsMum4V.Boost(-Dsst4V.BoostVector());
      //aDsMum=cos(DsMum4V.Vect().Angle(Dsst4V.BoostVector()));
      //DsMup4V.Boost(-Dsst4V.BoostVector());
      //aDsMup=cos(DsMup4V.Vect().Angle(Dsst4V.BoostVector()));

      // Altrnative calculation of the cos of Hel angle.
      //aDsMum2 = hel(Muss4V,Mu4V,Pim4V,Pip4V);
      //aDsMup2 = hel(Muss4V,Mu4V,Pip4V,Pim4V);
      
      // ========================================
      // TLorentzVector Bs_mom(B_s0_PX,B_s0_PY,B_s0_PZ,B_s0_PE);
      //TVector3 Bs_vec= Bs4V.Vect();
     
      // =========================================
      // Assuming 1 neutrino: 2-fold ambiguity
      // Bs momentum solutions of the equation
      // aaa*P^2 + bbb*P + ccc = 0
      // =========================================

      Double_t pHigh(0.), pLow(0.),det(0.);
      ComputeBMom2Fold(BsMassPDG,Bs4V,Bs_dir,pLow,pHigh,sq);
      //  cout << pLow << " " << pHigh << endl;
      //------
      TVector3 B3vHigh=(Bs_dir.Unit())*pHigh;
      TVector3 B3vLow=(Bs_dir.Unit())*pLow;
       
      TLorentzVector Bs4vHigh(B3vHigh,sqrt(BsMassPDG*BsMassPDG+B3vHigh.Mag2() ) );
      TLorentzVector Bs4vLow(B3vLow,sqrt(BsMassPDG*BsMassPDG+B3vLow.Mag2() ) );

      pBsP1=pHigh;
      pBsP2=pLow;

      SemiDec slHigh(Bs4vHigh, Dsst4V, Mu4V);
      q2P1=slHigh.GetQ2();
      mm2P1=slHigh.GetMM2();
      thlP1=slHigh.GetThetaL();
      elcmP1=slHigh.GetElCM();
      wP1=slHigh.GetW();

      SemiDec slLow(Bs4vLow, Dsst4V, Mu4V);
      q2P2=slLow.GetQ2();
      mm2P2=slLow.GetMM2();
      thlP2=slLow.GetThetaL();
      elcmP2=slLow.GetElCM();
      wP2=slLow.GetW();      
      
      // ========================================================================
      // Boost Approx. Kinematics
      // ========================================================================
      pBsY = (BsMassPDG/DsstMu4V.M())*(DsstMu4V.Pz())*sqrt(1+pow(tan(Bs_dir_theta),2));
      TVector3 BsFromY3=(Bs_dir.Unit())*pBsY;
      Double_t EBsFromY= sqrt(pow(pBsY,2)+pow(BsMassPDG,2));
      TLorentzVector BsFromY(BsFromY3.X(),BsFromY3.Y(),BsFromY3.Z(),EBsFromY );
      SemiDec slY(BsFromY, Dsst4V, Mu4V);
      q2Y=slY.GetQ2();
      mm2Y=slY.GetMM2();
      thlY=slY.GetThetaL();
      elcmY=slY.GetElCM();
      wY=slY.GetW();

      // ==========================
      // compute corrected mass
      // ==========================
      TVector3 Dsst3V = Dsst4V.Vect();
      Double_t pTcorrss = Dsst3V.Perp(Bs_dir);
      McorrDsst = (sqrt( pow(B_s0_MM,2)+pow(pTcorrss,2) ) + pTcorrss);
      
      TVector3 Mu3V = Mu4V.Vect();
      Double_t pTcorr =  Mu3V.Perp(Bs_dir);
      McorrMu = (sqrt( pow(B_s0_MM,2)+pow(pTcorr,2) ) + pTcorr);

      // ========================================================================
      //if( MuDau > 0 && Kine > 0 ){
      newtree->Fill();
      //}

   } // For jentry
   newtree->Print();
   newfile->Write();
   delete newfile;

}
