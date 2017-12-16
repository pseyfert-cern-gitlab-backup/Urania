/// file calibrateGEO_and_PID
/// @author Paul Seyfert
/// @date   2012-02-01
/// @brief  first attempt to create calibrated 2D signal pdfs for the Tau23Mu analysis

#include "calibrateGEO.C"
#include <vector>
#include "../params/limit_interface.h"
#include "TROOT.h"
#include "TMath.h"
#include "TSystem.h"

limit_interface* li;
/**
 * @param geocal calibrated 1d pdf for the geometric MVA (created with calibrateGEO.C)
 * @param reference
 */
void combine(TH1* geocal, TH1* reference, int sys = -1) {
  gSystem->Load("../params/libLimitROOT.so");
  li = new limit_interface();
  int geobins = geocal->GetNbinsX();
  li->set_central_mass(g_taumass);
  
  
  std::vector<TFile*> PIDcalibs_data;
  std::vector<TH1*> PIDhists_data;
  std::vector<TFile*> PIDcalibs_MC;
  std::vector<TH1*> PIDhists_MC;
  TH1* overallPID;
  TH1* overallPIDMC;
  TH1* overallPIDMCtruth;
  TFile* file = new TFile("../ZooThings/0x7f0/BuDATA-calibrated.root","read");
  file->GetObject("combined_dis",overallPID);
  file = new TFile("../ZooThings/0x7f0/BuMC10-calibrated.root","read");
  file->GetObject("combined_dis",overallPIDMC);
  file->GetObject("combined_ref",overallPIDMCtruth);
  PIDhists_data.clear();
  // read the calibrated 1d pdfs for the PID MVA in each GeoMVA slice
  // the files are to be created in several runs of the ZooLLReader using -g and -G
  for (unsigned int i = 0 ; i < geobins ; ++i) {
    PIDcalibs_data.push_back(new TFile(Form("../ZooThings/0x7f0/BuDATA-%d.root",i),"read"));
    PIDhists_data.push_back(NULL);
    PIDcalibs_data.back()->GetObject("combined_dis",PIDhists_data.back());
    PIDcalibs_MC.push_back(new TFile(Form("../ZooThings/0x7f0/BuMC10-%d.root",i),"read"));
    PIDhists_MC.push_back(NULL);
    PIDcalibs_MC.back()->GetObject("combined_dis",PIDhists_MC.back());
  }
  int pidbins = PIDhists_data.back()->GetNbinsX();
  TH1* bothcal = new TH1F("bothcal","bothcal",geobins*pidbins,0,geobins*pidbins);
  TH2* bothcal2D = new TH2F("bothcal2D","bothcal2D",geobins,0,geobins,pidbins,0,pidbins);
  bothcal2D->GetXaxis()->SetTitle("GeoMVA");
  bothcal2D->GetYaxis()->SetTitle("PIDMVA");

  TH1* bothcalMC = new TH1F("bothcalMC","bothcalMC",geobins*pidbins,0,geobins*pidbins);
  TH2* bothcalMC2D = new TH2F("bothcalMC2D","bothcalMC2D",pidbins,0,pidbins,geobins,0,geobins);
  TH1* uncorrelated = new TH1F("uncorrelated","uncorrelated",geobins*pidbins,0,geobins*pidbins);
  TH1* uncorrelatedMC = new TH1F("uncorrelatedMC","uncorrelatedMC",geobins*pidbins,0,geobins*pidbins);
  TH1* uncorrelatedMCtruth = new TH1F("uncorrelatedMCtruth","uncorrelatedMCtruth",geobins*pidbins,0,geobins*pidbins);
  std::cout << pidbins << " PID bins" << std::endl;
  std::cout << n_geobins << " GeoMVA bins" << std::endl;


  for (int p = 0 ; p < pidbins ; ++p) {
    for (int g = 0 ; g < n_geobins ; ++g) {
      std::cout << "p=" << p << "\tg=" << g;
      int thisbin = g+p*n_geobins;
      bothcal->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * PIDhists_data[g]->GetBinContent(p+1));  
      for (int mm = 0 ; mm < (int)(li->GetNMassbins()+0.1) ; ++mm) {
        float gaussint = 0.5 * (1+ TMath::Erf(1./g_tauwidth/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)));
        float calvalerr;
        gaussint -= 0.5 * (1+ TMath::Erf(1./g_tauwidth/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        std::cout << " integral = " << gaussint << std::endl;
        float calval = gaussint * geocal->GetBinContent(g+1) * PIDhists_data[g]->GetBinContent(p+1);
        if (sys<0) {
          calvalerr = gaussint * geocal->GetBinError(g+1) * PIDhists_data[g]->GetBinContent(p+1);
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calval+3*calvalerr , calval-3*calvalerr );
        } else {
      //PIDhists_data[g]->SetBinContent(1+sys,PIDhists_data[g]->GetBinContent(1+sys)+3*PIDhists_data[g]->GetBinContent(1+sys));
          calvalerr = gaussint * geocal->GetBinContent(g+1) * PIDhists_data[g]->GetBinError(p+1);
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calval+3*calvalerr , calval-3*calvalerr );
        }
        std::cout << " calval   = " << calval << " +/- " << calvalerr << std::endl;
        std::cout << " mass range " << li->GetMasslow(mm) << "\t" << li->GetMasshigh(mm) << std::endl;
      }
      bothcal2D->SetBinContent(bothcal2D->GetBin(g+1,p+1),geocal->GetBinContent(g+1) * PIDhists_data[g]->GetBinContent(p+1));  
      bothcal2D->SetBinError(bothcal2D->GetBin(g+1,p+1),sqrt(geocal->GetBinError(g+1) * geocal->GetBinError(g+1) + PIDhists_data[g]->GetBinContent(p+1) * PIDhists_data[g]->GetBinContent(p+1)));
      bothcalMC->SetBinContent(thisbin+1,reference->GetBinContent(g+1) * PIDhists_MC[g]->GetBinContent(p+1)); 
      bothcalMC2D->SetBinContent(bothcalMC2D->GetBin(p+1,g+1),reference->GetBinContent(g+1) * PIDhists_MC[g]->GetBinContent(p+1));
      //uncorrelated->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * overallPID->GetBinContent(p+1));
      //uncorrelatedMC->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * overallPIDMC->GetBinContent(p+1));
      //uncorrelatedMCtruth->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * overallPIDMCtruth->GetBinContent(p+1));
      std::cout << "\n\t\t" << geocal->GetBinContent(g+1) << " * " << PIDhists_data[g]->GetBinContent(p+1) 
        << " = " <<  geocal->GetBinContent(g+1)  *  PIDhists_data[g]->GetBinContent(1+p) << std::endl;
    }
  }
}


void combine_use_ref(TH1* geocal, TH1* reference) {
  int geobins = geocal->GetNbinsX();
  
  std::vector<TFile*> PIDcalibs_data;
  std::vector<TH1*> PIDhists_data;
  std::vector<TFile*> PIDcalibs_MC;
  std::vector<TH1*> PIDhists_MC;
  TH1* overallPID;
  TH1* overallPIDMC;
  TH1* overallPIDMCtruth;
  TFile* file = new TFile("../ZooThings/0x7f0/BuDATA-calibrated.root","read");
  file->GetObject("combined_ref",overallPID);
  file = new TFile("../ZooThings/0x7f0/BuMC10-calibrated.root","read");
  file->GetObject("combined_ref",overallPIDMC);
  file->GetObject("combined_ref",overallPIDMCtruth);
  PIDhists_data.clear();
  // read the calibrated 1d pdfs for the PID MVA in each GeoMVA slice
  // the files are to be created in several runs of the ZooLLReader using -g and -G
  for (unsigned int i = 0 ; i < geobins ; ++i) {
    PIDcalibs_data.push_back(new TFile(Form("../ZooThings/0x7f0/BuDATA-%d.root",i),"read"));
    PIDhists_data.push_back(NULL);
    PIDcalibs_data.back()->GetObject("combined_ref",PIDhists_data.back());
    PIDcalibs_MC.push_back(new TFile(Form("../ZooThings/0x7f0/BuMC10-%d.root",i),"read"));
    PIDhists_MC.push_back(NULL);
    PIDcalibs_MC.back()->GetObject("combined_ref",PIDhists_MC.back());
  }
  int pidbins = PIDhists_data.back()->GetNbinsX();
  TH2* ref2D = new TH2F("ref2D","ref2D",geobins,0,geobins,pidbins,0,pidbins);
  ref2D->GetXaxis()->SetTitle("GeoMVA");
  ref2D->GetYaxis()->SetTitle("PidMVA");
  TH1* bothcal = new TH1F("bothcal","bothcal",geobins*pidbins,0,geobins*pidbins);
  TH1* bothcalMC = new TH1F("bothcalMC","bothcalMC",geobins*pidbins,0,geobins*pidbins);
  TH2* bothcalMC2D = new TH2F("bothcalMC2D","bothcalMC2D",pidbins,0,pidbins,geobins,0,geobins);
  TH1* uncorrelated = new TH1F("uncorrelated","uncorrelated",geobins*pidbins,0,geobins*pidbins);
  TH1* uncorrelatedMC = new TH1F("uncorrelatedMC","uncorrelatedMC",geobins*pidbins,0,geobins*pidbins);
  TH1* uncorrelatedMCtruth = new TH1F("uncorrelatedMCtruth","uncorrelatedMCtruth",geobins*pidbins,0,geobins*pidbins);
  std::cout << pidbins << " PID bins" << std::endl;
  std::cout << n_geobins << " GeoMVA bins" << std::endl;

  for (int p = 0 ; p < pidbins ; ++p) {
    for (int g = 0 ; g < n_geobins ; ++g) {
      std::cout << "p=" << p << "\tg=" << g;
      int thisbin = g+p*n_geobins;
      bothcal->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * PIDhists_data[g]->GetBinContent(p+1));  
      ref2D->SetBinContent(ref2D->GetBin(g+1,p+1),reference->GetBinContent(g+1) * PIDhists_MC[g]->GetBinContent(p+1));  
      bothcalMC->SetBinContent(thisbin+1,reference->GetBinContent(g+1) * PIDhists_MC[g]->GetBinContent(p+1)); 
      bothcalMC2D->SetBinContent(bothcalMC2D->GetBin(p+1,g+1),reference->GetBinContent(g+1) * PIDhists_MC[g]->GetBinContent(p+1));
      uncorrelated->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * overallPID->GetBinContent(p+1));
      uncorrelatedMC->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * overallPIDMC->GetBinContent(p+1));
      uncorrelatedMCtruth->SetBinContent(thisbin+1,geocal->GetBinContent(g+1) * overallPIDMCtruth->GetBinContent(p+1));
      std::cout << "\n\t\t" << geocal->GetBinContent(g+1) << " * " << PIDhists_data[g]->GetBinContent(p+1) 
        << " = " <<  geocal->GetBinContent(g+1)  *  PIDhists_data[g]->GetBinContent(1+p) << std::endl;
    }
  }
}
