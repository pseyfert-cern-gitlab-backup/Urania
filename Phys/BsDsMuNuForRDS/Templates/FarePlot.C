void FarePlot() {

  TFile *f = new TFile("/data/Shared/Data_WithDsVetoes_Jul16/DataAN_S24_RDS_FromTauMu_iso.root","READ");

  TString intrname = "B2DsMuNuTuple/DecayTree";

  TH1D *mass_phipi = new TH1D("mass_phipi","",100,3000,8000);    
  TH1D *mass_KstK = new TH1D("mass_KstK","",100,3000,8000);    

  TCanvas *c1 = new TCanvas("c1","",1800,900);

  TTree* tree = ((TTree*)gDirectory->Get(intrname.Data()));
  tree->Draw("Bs_0_MCORR>>mass_phipi","resFlag == 0 && (Ds_MM>1920 && Ds_MM<2010) && ( mu_PIDmu > 0) && (mu_iso_MinBDT_Long>-0.5)  && (Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS == 1)");
  tree->Draw("Bs_0_MCORR>>mass_KstK","resFlag == 1 && (Ds_MM>1920 && Ds_MM<2010) && ( mu_PIDmu > 0) && (mu_iso_MinBDT_Long>-0.5)  && (Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS == 1)");

  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);
  mass_phipi->Draw();
  mass_phipi->SetXTitle("B_s corr mass (MeV/c^2)");
  c1->cd(2);
  mass_KstK->Draw();
  mass_KstK->SetXTitle("B_s corr mass (MeV/c^2)");
  c1->Print("masses_reso.pdf");
  return;
}
