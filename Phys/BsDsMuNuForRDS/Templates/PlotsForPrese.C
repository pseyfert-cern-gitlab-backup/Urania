void PlotsForPrese() {


  TFile *f = new TFile("/data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root","READ");

  TTree* myT = ((TTree*)gDirectory->Get("B2DsMuNuTuple/DecayTree"));

  myT->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_ProbNNmu>0.3 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myprobH = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myprobH");
  myprobH->SetLineColor(2);
  myT->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_ProbNNmu<=0.3 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myprobL = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myprobL");
  myprobL->SetLineColor(4);


  TFile *f2 = new TFile("/data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root","READ");

  TTree* myT2 = ((TTree*)gDirectory->Get("B2DsMuNuTuple/DecayTree"));

  myT2->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && Bs_0_M>3000 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myBmH = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myBmH");
  myBmH->SetLineColor(2);
  myT2->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && Bs_0_M<=3000 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myBmL = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myBmL");
  myBmL->SetLineColor(4);

  /*
    Isoplots
  */
  myT2->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_iso_MinBDT_Long>-0.5 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myIsoH = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myIsoH");
  myIsoH->SetLineColor(2);
  myT2->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_iso_MinBDT_Long<=-0.5 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myIsoL = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myIsoL");
  myIsoL->SetLineColor(4);


  myT2->Draw("mu_iso_MinBDT_Long:Bs_0_MCORR>>htemp(50,3000,8000,33,-1.1,1.1)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_PT>1000 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH2D* myIso2D = (TH2D*)((TH2D*)gDirectory->Get("htemp"))->Clone("myIso2D");


  /*
    pT plots
  */
  myT2->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_PT>1000 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myPTH = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myPTH");
  myPTH->SetLineColor(2);
  myT2->Draw("Bs_0_MCORR>>htemp(100,3000,8000)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_PT<=1000 && ( ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 531 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 433 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) || ( (( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)) && (( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )) && (( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 ) ) && (( TMath::Abs(Bs_0_TRUEID) == 531 )) ) )");
  TH1D* myPTL = (TH1D*)((TH1D*)gDirectory->Get("htemp"))->Clone("myPTL");
  myPTL->SetLineColor(4);

  /*
    bkg
  */
  TFile *f3 = new TFile("/data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BsDsDs_iso.root","READ");

  TTree* myT3 = ((TTree*)gDirectory->Get("B2DsMuNuTuple/DecayTree"));
  myT3->Draw("mu_iso_MinBDT_Long:Bs_0_MCORR>>htemp(50,3000,8000,33,-1.1,1.1)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_PT>1000 ");
  TH2D* DsDs_myIso2D = (TH2D*)((TH2D*)gDirectory->Get("htemp"))->Clone("DsDs_myIso2D");


  /*
    bkg
  */
  TFile *f4 = new TFile("/data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu_iso.root","READ");

  TTree* myT4 = ((TTree*)gDirectory->Get("B2DsMuNuSSTuple/DecayTree"));
  myT4->Draw("mu_iso_MinBDT_Long:Bs_0_MCORR>>htemp(50,3000,8000,33,-1.1,1.1)","Bs_0_MCORR>3000 && Bs_0_MCORR<8000 && mu_PT>1000 ");
  TH2D* SS_myIso2D = (TH2D*)((TH2D*)gDirectory->Get("htemp"))->Clone("SS_myIso2D");
 



  TCanvas *c1 = new TCanvas("c1","",900,900);
  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  myprobH->Scale(1./myprobH->GetSumOfWeights());
  myprobL->Scale(1./myprobL->GetSumOfWeights());
  myprobH->SetTitle("");
  myprobH->GetYaxis()->SetTitle("Entries / 50 [MeV]");
  myprobH->GetXaxis()->SetTitle("M(B) corr [MeV]");
  myprobH->GetYaxis()->SetTitleOffset(2);
  myprobH->GetXaxis()->SetTitleOffset(1.2);
  myprobH->Draw();
  myprobL->Draw("same");

  TLegend* l1 = new TLegend(0.6,0.6,0.82,0.80);
  l1->AddEntry(myprobH,"probNN(#mu)>0.3","l");
  l1->AddEntry(myprobL,"probNN(#mu)<=0.3","l");
  l1->Draw();

  c1->Print("Bmass_vs_prob.pdf");

  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  myBmH->Scale(1./myBmH->GetSumOfWeights());
  myBmL->Scale(1./myBmL->GetSumOfWeights());
  myBmH->SetTitle("");
  myBmH->GetYaxis()->SetTitle("Entries / 50 [MeV]");
  myBmH->GetXaxis()->SetTitle("M(B) corr [MeV]");
  myBmH->GetYaxis()->SetTitleOffset(2);
  myBmH->GetXaxis()->SetTitleOffset(1.2);
  myBmH->Draw();
  myBmL->Draw("same");
  TLegend* l2 = new TLegend(0.55,0.65,0.77,0.80);
  l2->AddEntry(myBmH,"M(B)>3000","l");
  l2->AddEntry(myBmL,"M(B)<=3000","l");
  l2->Draw();

  c1->Print("Bmass_vs_Bm.pdf");

  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  myIsoH->Scale(1./myIsoH->GetSumOfWeights());
  myIsoL->Scale(1./myIsoL->GetSumOfWeights());
  myIsoH->SetTitle("");
  myIsoH->GetYaxis()->SetTitle("Entries / 50 [MeV]");
  myIsoH->GetXaxis()->SetTitle("M(B) corr [MeV]");
  myIsoH->GetYaxis()->SetTitleOffset(2);
  myIsoH->GetXaxis()->SetTitleOffset(1.2);
  myIsoH->Draw();
  myIsoL->Draw("same");
  TLegend* l3 = new TLegend(0.55,0.65,0.77,0.80);
  l3->AddEntry(myIsoH,"Iso>-0.5","l");
  l3->AddEntry(myIsoL,"Iso<=0.5","l");
  l3->Draw();

  c1->Print("Bmass_vs_Iso.pdf");

  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  myPTH->Scale(1./myPTH->GetSumOfWeights());
  myPTL->Scale(1./myPTL->GetSumOfWeights());
  myPTH->SetTitle("");
  myPTH->GetYaxis()->SetTitle("Entries / 50 [MeV]");
  myPTH->GetXaxis()->SetTitle("M(B) corr [MeV]");
  myPTH->GetYaxis()->SetTitleOffset(2);
  myPTH->GetXaxis()->SetTitleOffset(1.2);
  myPTH->Draw();
  myPTL->Draw("same");
  TLegend* l4 = new TLegend(0.55,0.65,0.77,0.80);
  l4->AddEntry(myPTH,"pT>1000","l");
  l4->AddEntry(myPTL,"pT<=1000","l");
  l4->Draw();

  c1->Print("Bmass_vs_PT.pdf");

  c1->cd();
  gPad->SetRightMargin(0.13);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  myIso2D->Draw("colz");
  myIso2D->SetTitle("");
  myIso2D->GetYaxis()->SetTitle("Iso");
  myIso2D->GetXaxis()->SetTitle("M(B) corr [MeV]");
  c1->Print("BmassIso_2D.pdf");

  c1->cd();
  gPad->SetRightMargin(0.13);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  DsDs_myIso2D->SetTitle("");
  DsDs_myIso2D->GetYaxis()->SetTitle("Iso");
  DsDs_myIso2D->GetXaxis()->SetTitle("M(B) corr [MeV]");
  DsDs_myIso2D->Draw("colz");

  c1->Print("DsDs_BmassIso_2D.pdf");

  c1->cd();
  gPad->SetRightMargin(0.13);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  SS_myIso2D->SetTitle("");
  SS_myIso2D->GetYaxis()->SetTitle("Iso");
  SS_myIso2D->GetXaxis()->SetTitle("M(B) corr [MeV]");
  SS_myIso2D->Draw("colz");

  c1->Print("SS_BmassIso_2D.pdf");

  return;

}
