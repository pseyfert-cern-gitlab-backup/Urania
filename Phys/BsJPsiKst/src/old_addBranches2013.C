///////////////////////////////////////////
/// Usage: root -l -q addBranches2013.C  //
///  Wrote by Juan Jose Saborido Silva   //
///   Updated by Carlos Vazquez Sierra   //
///////////////////////////////////////////

Double_t doca( Double_t x1, Double_t y1, Double_t z1, Double_t xp1, Double_t yp1,
               Double_t x2, Double_t y2, Double_t z2, Double_t xp2, Double_t yp2 ) {

  Double_t difxp = xp2 - xp1 ;
  Double_t difyp = yp2 - yp1 ;

  Double_t equis = x1 - x2 + xp2*z2 - xp1*z1 ;
  Double_t ygrie = y1 - y2 + yp2*z2 - yp1*z1 ;

  Double_t zeta  = ( equis*difxp + ygrie*difyp ) / ( difxp*difxp + difyp*difyp ) ;

  Double_t nx1 = x1 + xp1*(zeta-z1) ;
  Double_t ny1 = y1 + yp1*(zeta-z1) ;
  Double_t nz1 = zeta ;

  Double_t nx2 = x2 + xp2*(zeta-z2) ;
  Double_t ny2 = y2 + yp2*(zeta-z2) ;
  Double_t nz2 = zeta ;

  Double_t dist = TMath::Sqrt( (nx1-nx2)*(nx1-nx2) + (ny1-ny2)*(ny1-ny2) + (nz1-nz2)*(nz1-nz2) ) ;

  return dist ;

}

void addBranches2013() {

   TFile *fold = TFile::Open("inputTuple.root"); // UPDATE !!!
   TTree *Toldd = (TTree*)fold->Get("BdTuple/DecayTree");
   TFile *fjunk = TFile::Open("junkDeleteMe.root","recreate"); // Junk file. Delete after running the script.
   const char *firstCuts = "muplus_MINIPCHI2 > 16 && muminus_MINIPCHI2 > 16 && Kplus_MINIPCHI2 > 2 && piminus_MINIPCHI2 > 2";
   TTree *Told = Toldd->CopyTree(firstCuts); // Very loose cuts to reduce tuple size.
   Long64_t EntriesToCopy  = Told->GetEntries();
   TFile *fnew = TFile::Open("outputTuple.root","recreate");
   TTree *Tnew = Told->CloneTree(EntriesToCopy);

   ///////////////////////////////////////////////////////////

   Double_t max_DOCA   = 0. ;
   Double_t lessIPS    = 0. ;
   Double_t Mjpsik     = 0. ;
   Double_t CPsi       = 0. ;
   Double_t CTheta     = 0. ;
   Double_t B0_LIFE_PS = 0. ;

   TBranch *b_max_DOCA = Tnew->Branch("max_DOCA", &max_DOCA, "max_DOCA/D");
   TBranch *b_lessIPS  = Tnew->Branch("lessIPS" , &lessIPS , "lessIPS/D" );
   TBranch *b_Mjpsik   = Tnew->Branch("Mjpsik"  , &Mjpsik  , "Mjpsik/D"  );
   TBranch *b_CPsi     = Tnew->Branch("CPsi"    , &CPsi    , "CPsi/D"    );
   TBranch *b_CTheta   = Tnew->Branch("CTheta"  , &CTheta  , "CTheta/D"  );
   TBranch *b_B0_LIFE_PS   = Tnew->Branch("B0_LIFE_PS"  , &B0_LIFE_PS  , "B0_LIFE_PS/D"  );

   Double_t muplus_MINIPCHI2;
   Double_t muminus_MINIPCHI2;
   Double_t Kplus_MINIPCHI2;
   Double_t piminus_MINIPCHI2;
   Double_t B0_ThetaVtr;
   Double_t B0_ThetaTr;

   Double_t J_psi_1S_PX ;
   Double_t J_psi_1S_PY ;
   Double_t J_psi_1S_PZ ;
   Double_t J_psi_1S_M  ;

   Double_t Kplus_PX ;
   Double_t Kplus_PY ;
   Double_t Kplus_PZ ;
   Double_t Kplus_M  ;

   Double_t B0_LOKI_DTF_CTAU  ;

   Tnew->SetBranchAddress("muplus_MINIPCHI2"  , &muplus_MINIPCHI2);
   Tnew->SetBranchAddress("muminus_MINIPCHI2" , &muminus_MINIPCHI2);
   Tnew->SetBranchAddress("Kplus_MINIPCHI2"   , &Kplus_MINIPCHI2);
   Tnew->SetBranchAddress("piminus_MINIPCHI2" , &piminus_MINIPCHI2);
   Tnew->SetBranchAddress("B0_ThetaVtr"       , &B0_ThetaVtr);
   Tnew->SetBranchAddress("B0_ThetaTr"        , &B0_ThetaTr);
   Tnew->SetBranchAddress("J_psi_1S_PX"       , &J_psi_1S_PX);
   Tnew->SetBranchAddress("J_psi_1S_PY"       , &J_psi_1S_PY);
   Tnew->SetBranchAddress("J_psi_1S_PZ"       , &J_psi_1S_PZ);
   Tnew->SetBranchAddress("J_psi_1S_M"        , &J_psi_1S_M);
   Tnew->SetBranchAddress("Kplus_PX"          , &Kplus_PX);
   Tnew->SetBranchAddress("Kplus_PY"          , &Kplus_PY);
   Tnew->SetBranchAddress("Kplus_PZ"          , &Kplus_PZ);
   Tnew->SetBranchAddress("Kplus_M"           , &Kplus_M);

   Double_t Kplus_TRACK_FirstMeasurementX ;
   Double_t Kplus_TRACK_FirstMeasurementY ;
   Double_t Kplus_TRACK_FirstMeasurementZ ;
   Double_t Kplus_PX ;
   Double_t Kplus_PY ;
   Double_t Kplus_PZ ;
   Double_t piminus_TRACK_FirstMeasurementX ;
   Double_t piminus_TRACK_FirstMeasurementY ;
   Double_t piminus_TRACK_FirstMeasurementZ ;
   Double_t piminus_PX ;
   Double_t piminus_PY ;
   Double_t piminus_PZ ;
   Double_t muplus_TRACK_FirstMeasurementX ;
   Double_t muplus_TRACK_FirstMeasurementY ;
   Double_t muplus_TRACK_FirstMeasurementZ ;
   Double_t muplus_PX ;
   Double_t muplus_PY ;
   Double_t muplus_PZ ;
   Double_t muminus_TRACK_FirstMeasurementX ;
   Double_t muminus_TRACK_FirstMeasurementY ;
   Double_t muminus_TRACK_FirstMeasurementZ ;
   Double_t muminus_PX ;
   Double_t muminus_PY ;
   Double_t muminus_PZ ;

   Tnew->SetBranchAddress("Kplus_TRACK_FirstMeasurementX"    , &Kplus_TRACK_FirstMeasurementX);
   Tnew->SetBranchAddress("Kplus_TRACK_FirstMeasurementY"    , &Kplus_TRACK_FirstMeasurementY);
   Tnew->SetBranchAddress("Kplus_TRACK_FirstMeasurementZ"    , &Kplus_TRACK_FirstMeasurementZ);
   Tnew->SetBranchAddress("Kplus_PX"                         , &Kplus_PX);
   Tnew->SetBranchAddress("Kplus_PY"                         , &Kplus_PY);
   Tnew->SetBranchAddress("Kplus_PZ"                         , &Kplus_PZ);

   Tnew->SetBranchAddress("piminus_TRACK_FirstMeasurementX"  , &piminus_TRACK_FirstMeasurementX);
   Tnew->SetBranchAddress("piminus_TRACK_FirstMeasurementY"  , &piminus_TRACK_FirstMeasurementY);
   Tnew->SetBranchAddress("piminus_TRACK_FirstMeasurementZ"  , &piminus_TRACK_FirstMeasurementZ);
   Tnew->SetBranchAddress("piminus_PX"                       , &piminus_PX);
   Tnew->SetBranchAddress("piminus_PY"                       , &piminus_PY);
   Tnew->SetBranchAddress("piminus_PZ"                       , &piminus_PZ);

   Tnew->SetBranchAddress("muplus_TRACK_FirstMeasurementX"   , &muplus_TRACK_FirstMeasurementX);
   Tnew->SetBranchAddress("muplus_TRACK_FirstMeasurementY"   , &muplus_TRACK_FirstMeasurementY);
   Tnew->SetBranchAddress("muplus_TRACK_FirstMeasurementZ"   , &muplus_TRACK_FirstMeasurementZ);
   Tnew->SetBranchAddress("muplus_PX"                        , &muplus_PX);
   Tnew->SetBranchAddress("muplus_PY"                        , &muplus_PY);
   Tnew->SetBranchAddress("muplus_PZ"                        , &muplus_PZ);

   Tnew->SetBranchAddress("muminus_TRACK_FirstMeasurementX"  , &muminus_TRACK_FirstMeasurementX);
   Tnew->SetBranchAddress("muminus_TRACK_FirstMeasurementY"  , &muminus_TRACK_FirstMeasurementY);
   Tnew->SetBranchAddress("muminus_TRACK_FirstMeasurementZ"  , &muminus_TRACK_FirstMeasurementZ);
   Tnew->SetBranchAddress("muminus_PX"                       , &muminus_PX);
   Tnew->SetBranchAddress("muminus_PY"                       , &muminus_PY);
   Tnew->SetBranchAddress("muminus_PZ"                       , &muminus_PZ);

   Tnew->SetBranchAddress("B0_LOKI_DTF_CTAU"                       , &B0_LOKI_DTF_CTAU);

   Double_t x1, y1, z1, xp1, yp1 ;
   Double_t x2, y2, z2, xp2, yp2 ;
   Double_t doca1, doca2, doca3, doca4, doca5, doca6 ;

   Long64_t nentries = Tnew->GetEntries();

   for (Long64_t ii = 0; ii<nentries; ii++) {

     Tnew->GetEntry(ii);

     // muplus-muminus DOCA:
     x1    = muplus_TRACK_FirstMeasurementX ;
     y1    = muplus_TRACK_FirstMeasurementY ;
     z1    = muplus_TRACK_FirstMeasurementZ ;
     xp1   = muplus_PX / muplus_PZ ;
     yp1   = muplus_PY / muplus_PZ ;
     x2    = muminus_TRACK_FirstMeasurementX ;
     y2    = muminus_TRACK_FirstMeasurementY ;
     z2    = muminus_TRACK_FirstMeasurementZ ;
     xp2   = muminus_PX / muminus_PZ ;
     yp2   = muminus_PY / muminus_PZ ;
     doca1 = doca( x1, y1, z1, xp1, yp1, x2, y2, z2, xp2, yp2 );

     // muplus-piminus DOCA:
     x2    = piminus_TRACK_FirstMeasurementX ;
     y2    = piminus_TRACK_FirstMeasurementY ;
     z2    = piminus_TRACK_FirstMeasurementZ ;
     xp2   = piminus_PX / piminus_PZ ;
     yp2   = piminus_PY / piminus_PZ ;
     doca2 = doca( x1, y1, z1, xp1, yp1, x2, y2, z2, xp2, yp2 );

     // muplus-Kplus DOCA:
     x2    = Kplus_TRACK_FirstMeasurementX ;
     y2    = Kplus_TRACK_FirstMeasurementY ;
     z2    = Kplus_TRACK_FirstMeasurementZ ;
     xp2   = Kplus_PX / Kplus_PZ ;
     yp2   = Kplus_PY / Kplus_PZ ;
     doca3 = doca( x1, y1, z1, xp1, yp1, x2, y2, z2, xp2, yp2 );

     // muminus-piminus DOCA:
     x1    = muminus_TRACK_FirstMeasurementX ;
     y1    = muminus_TRACK_FirstMeasurementY ;
     z1    = muminus_TRACK_FirstMeasurementZ ;
     xp1   = muminus_PX / muminus_PZ ;
     yp1   = muminus_PY / muminus_PZ ;
     x2    = piminus_TRACK_FirstMeasurementX ;
     y2    = piminus_TRACK_FirstMeasurementY ;
     z2    = piminus_TRACK_FirstMeasurementZ ;
     xp2   = piminus_PX / piminus_PZ ;
     yp2   = piminus_PY / piminus_PZ ;
     doca4 = doca( x1, y1, z1, xp1, yp1, x2, y2, z2, xp2, yp2 );

     // muminus-Kplus DOCA:
     x2    = Kplus_TRACK_FirstMeasurementX ;
     y2    = Kplus_TRACK_FirstMeasurementY ;
     z2    = Kplus_TRACK_FirstMeasurementZ ;
     xp2   = Kplus_PX / Kplus_PZ ;
     yp2   = Kplus_PY / Kplus_PZ ;
     doca5 = doca( x1, y1, z1, xp1, yp1, x2, y2, z2, xp2, yp2 );

     // Kplus-piminus DOCA:
     x1    = Kplus_TRACK_FirstMeasurementX ;
     y1    = Kplus_TRACK_FirstMeasurementY ;
     z1    = Kplus_TRACK_FirstMeasurementZ ;
     xp1   = Kplus_PX / Kplus_PZ ;
     yp1   = Kplus_PY / Kplus_PZ ;
     x2    = piminus_TRACK_FirstMeasurementX ;
     y2    = piminus_TRACK_FirstMeasurementY ;
     z2    = piminus_TRACK_FirstMeasurementZ ;
     xp2   = piminus_PX / piminus_PZ ;
     yp2   = piminus_PY / piminus_PZ ;
     doca6 = doca( x1, y1, z1, xp1, yp1, x2, y2, z2, xp2, yp2 );

     Double_t max1 = TMath::Max( TMath::Max(doca1,doca2), TMath::Max(doca3,doca4) ) ;
     Double_t max2 = TMath::Max( doca5, doca6 ) ;
     max_DOCA = TMath::Max( max1, max2) ;

     lessIPS = TMath::Min( TMath::Min(muplus_MINIPCHI2,muminus_MINIPCHI2),
                           TMath::Min( Kplus_MINIPCHI2,piminus_MINIPCHI2) ) ;
     lessIPS = TMath::Sqrt( lessIPS ) ;

     Double_t pj2  = J_psi_1S_PX*J_psi_1S_PX + J_psi_1S_PY*J_psi_1S_PY + J_psi_1S_PZ*J_psi_1S_PZ ;
     Double_t pk2  = Kplus_PX*Kplus_PX       + Kplus_PY*Kplus_PY       + Kplus_PZ*Kplus_PZ ;
     Double_t pjpk = J_psi_1S_PX*Kplus_PX    + J_psi_1S_PY*Kplus_PY    + J_psi_1S_PZ*Kplus_PZ ;
     Double_t mj2  = J_psi_1S_M*J_psi_1S_M ;
     Double_t mk2  = Kplus_M*Kplus_M ;
     Double_t raiz = TMath::Sqrt( (pj2 + mj2)*( pk2 + mk2) ) ;

     Mjpsik = TMath::Sqrt( mj2 + mk2 + 2.*raiz - 2.*pjpk ) ;

     CPsi   = TMath::Cos(B0_ThetaVtr) ;
     CTheta = TMath::Cos(B0_ThetaTr) ;

     B0_LIFE_PS = 3.3356409519815204*B0_LOKI_DTF_CTAU ;

     b_max_DOCA ->Fill() ;
     b_lessIPS  ->Fill() ;
     b_Mjpsik   ->Fill() ;
     b_CPsi     ->Fill() ;
     b_CTheta   ->Fill() ;
     b_B0_LIFE_PS ->Fill() ;
   }

   Tnew->Write();
   fnew->Write();
   fnew->Close();
   fold->Close();
   delete fnew;
   delete fold;
}
