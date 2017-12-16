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

TString lookup(int g, int p) {
  TString ret = "geo_";
  limit_interface* li = new limit_interface();
  
  if (li->the_geobinning()[g]<0.) {
    ret += "m";
  }
  ret += Form("%03d",(int)(fabs(100.*li->the_geobinning()[g])));
  ret += "to";
  if (li->the_geobinning()[g+1]<0.) {
    ret += "m";
  }
  ret += Form("%03d",(int)(fabs(100.*li->the_geobinning()[g+1])));

  ret += "_PID_";

  ret += Form("%03d",(int)(fabs(100.01*li->the_pidbinning()[p])));
  ret += ".root";
  

  delete li;
  return ret;


  if (0 == g && 1 == p) return "geo_m100to005_PID_027.root";
  if (1 == g && 1 == p) return "geo_005to035_PID_027.root";
  if (2 == g && 1 == p) return "geo_035to055_PID_027.root";
  if (3 == g && 1 == p) return "geo_055to075_PID_027.root";
  if (4 == g && 1 == p) return "geo_075to100_PID_027.root";

  if (0 == g && 2 == p) return "geo_m100to005_PID_057.root";
  if (1 == g && 2 == p) return "geo_005to035_PID_057.root";
  if (2 == g && 2 == p) return "geo_035to055_PID_057.root";
  if (3 == g && 2 == p) return "geo_055to075_PID_057.root";
  if (4 == g && 2 == p) return "geo_075to100_PID_057.root";

  if (0 == g && 3 == p) return "geo_m100to005_PID_075.root";
  if (1 == g && 3 == p) return "geo_005to035_PID_075.root";
  if (2 == g && 3 == p) return "geo_035to055_PID_075.root";
  if (3 == g && 3 == p) return "geo_055to075_PID_075.root";
  if (4 == g && 3 == p) return "geo_075to100_PID_075.root";

  if (0 == g && 4 == p) return "geo_m100to005_PID_081.root";
  if (1 == g && 4 == p) return "geo_005to035_PID_081.root";
  if (2 == g && 4 == p) return "geo_035to055_PID_081.root";
  if (3 == g && 4 == p) return "geo_055to075_PID_081.root";
  if (4 == g && 4 == p) return "geo_075to100_PID_081.root";

  return "doesnt_work";

}


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
  
  std::vector<TTree*> baums;
  std::vector<float> pid_part;
  std::vector<float> pid_parte;
  
  for(int p = 0 ; p < li->the_pidbins() ; ++p) {
    for(int g = 0 ; g < li->the_geobins() ; ++g) {
      li->GetGlobalMVAbin(g,p);
      //TTree* b = NULL;
      baums.push_back(NULL);
      pid_part.push_back(0.f);
      pid_parte.push_back(0.f);
    }
  }
  std::cout << "fuck" << std::endl;

  for(int p = 0 ; p < li->the_pidbins() ; ++p) {
    for(int g = 0 ; g < li->the_geobins() ; ++g) {
      if (0==p) continue;
      int glob = li->GetGlobalMVAbin(g,p);
      TString fname = TString("/home/pseyfert/physiwork/zoontuple/Erasmus_v8r1/PIDCalib/PIDPerfScripts/x86_64-slc5-gcc43-opt/") + lookup(g,p);
      TFile* ff = new TFile(fname,"read");
      ff->GetObject("Tau23Mu",baums[glob]);
    }
  }
  std::cout << "fuckfuck" << std::endl;

  for(int p = 0 ; p < li->the_pidbins() ; ++p) {
    std::cout << "    fuckfuck" << std::endl;
    for(int g = 0 ; g < li->the_geobins() ; ++g) {
      int glob = li->GetGlobalMVAbin(g,p);
      if (NULL == baums[glob]) { std::cout <<"ahahaah" << std::endl;}
      TH1F* buffer = new TH1F("buffer","buffer",1,0.,5000.);
      float den ; 
      float num;
      float nume;
      if (0!=p) {
        baums[glob]->Draw("mass>>buffer",TString("(")+li->getGeoRefString()+")*productionweightMC11v3*(Event_PIDCalibEff!=0)");
        den = buffer->GetSum();
        baums[glob]->Draw("mass>>buffer",TString("(")+li->getGeoRefString()+")*productionweightMC11v3*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        num = buffer->GetSum();
        if (sys==p) {
          baums[glob]->Draw("mass>>buffer",TString("(")+li->getGeoRefString()+")*productionweightMC11v3*(Event_PIDCalibEff!=0)*Event_PIDCalibEff+Event_PIDCalibEffError");
          nume = buffer->GetSum();
        } else {
          nume = num;
        }
      } else {
        den = 1.f;
        num = 1.f;
        nume = 1.f;
      }

      pid_part[glob] = num/den;
      pid_parte[glob] = nume/den;
      if (p < li->the_pidbins() - 1) {
        int glob_2 = li->GetGlobalMVAbin(g,p+1);
        if (NULL == baums[glob_2]) { std::cout <<"ahahaah" << std::endl;}
        TH1F* buffer2 = new TH1F("buffer2","buffer2",1,0.,5000.);
        baums[glob_2]->Draw("mass>>buffer2",TString("(")+li->getGeoRefString()+")*productionweightMC11v3*(Event_PIDCalibEff!=0)");
        float den2 = buffer2->GetSum();
        baums[glob_2]->Draw("mass>>buffer2",TString("(")+li->getGeoRefString()+")*productionweightMC11v3*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        float num2 = buffer2->GetSum();
        float nume2 = num2;
        if (sys==p+1) {
          baums[glob_2]->Draw("mass>>buffer2",TString("(")+li->getGeoRefString()+")*productionweightMC11v3*(Event_PIDCalibEff!=0)*Event_PIDCalibEff+Event_PIDCalibEffError");
          nume2 = buffer2->GetSum();
        } 
        pid_part[glob] = num/den - num2/den2;
        pid_parte[glob] = nume/den - nume2/den2;

        if (0==g) std::cout << "g = " << g << "\t\tp = " << p << "\t\teps = " << num/den << "-" << num2/den2 << "=" << num/den - num2/den2 << std::endl;
        if (0==g) std::cout << "g = " << g << "\t\tp = " << p << "\t\tEPS = " << nume/den << "-" << nume2/den2 << "=" << nume/den - nume2/den2 << std::endl;
        delete buffer2;
      }
   //   if (1==g) std::cout << "g = " << g << "\t\tp = " << p << "\t\teps = " << pid_part[glob] << std::endl;
   //   if (2==g) std::cout << "g = " << g << "\t\tp = " << p << "\t\teps = " << pid_part[glob] << std::endl;
   //   if (3==g) std::cout << "g = " << g << "\t\tp = " << p << "\t\teps = " << pid_part[glob] << std::endl;
   //   if (4==g) std::cout << "g = " << g << "\t\tp = " << p << "\t\teps = " << pid_part[glob] << std::endl;
      delete buffer;
    }
  }


  float taumasserr = 0.04;
  float tauwidth1err = 0.1;
  float tauwidth2err = 1.;

  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      std::cout << "p=" << p << "\tg=" << g;
      int thisbin = g+p*n_geobins;
      int glob = li->GetGlobalMVAbin(g,p);
      for (int mm = 0 ; mm < (int)(li->GetNMassbins()+0.1) ; ++mm) {
        float gaussint1 = 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint1Mm = 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasshigh(mm) - g_taumass-3.*taumasserr)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasslow(mm) - g_taumass-3.*taumasserr)));
        float gaussint1Ms1 = 0.5 * (1+ TMath::Erf(1./(g_tauwidth1-3.*tauwidth1err)/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./(g_tauwidth1+3.*tauwidth1err)/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint1Ms2 = 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint1Pm = 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasshigh(mm) - g_taumass+3.*taumasserr)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasslow(mm) - g_taumass+3.*taumasserr)));
        float gaussint1Ps1 = 0.5 * (1+ TMath::Erf(1./(g_tauwidth1+3.*tauwidth1err)/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./(g_tauwidth1+3.*tauwidth1err)/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint1Ps2 = 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float calvalerr;
        float gaussint2 = 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint2Mm = 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasshigh(mm) - g_taumass-3.*taumasserr)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasslow(mm) - g_taumass-3.*taumasserr)));
        float gaussint2Ms1 = 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint2Ms2 = 0.5 * (1+ TMath::Erf(1./(g_tauwidth2-3.*tauwidth2err)/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./(g_tauwidth2-3.*tauwidth2err)/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint2Pm = 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasshigh(mm) - g_taumass+3.*taumasserr)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasslow(mm) - g_taumass+3.*taumasserr)));
        float gaussint2Ps1 = 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint2Ps2 = 0.5 * (1+ TMath::Erf(1./(g_tauwidth2+3.*tauwidth2err)/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./(g_tauwidth2+3.*tauwidth2err)/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint =    .7*gaussint1    + .3*gaussint2;
        float gaussintMm =  .7*gaussint1Mm  + .3*gaussint2Mm;
        float gaussintMs1 = .7*gaussint1Ms1 + .3*gaussint2Ms1;
        float gaussintMs2 = .7*gaussint1Ms2 + .3*gaussint2Ms2;
        float gaussintPm =  .7*gaussint1Pm  + .3*gaussint2Pm;
        float gaussintPs1 = .7*gaussint1Ps1 + .3*gaussint2Ps1;
        float gaussintPs2 = .7*gaussint1Ps2 + .3*gaussint2Ps2;
        std::cout << " integral = " << gaussint << std::endl;
        float calval = gaussint * geocal->GetBinContent(g+1) * pid_part[glob];

        if (-4==sys) {
          float calvalM = gaussintMm * geocal->GetBinContent(g+1) * pid_part[glob];
          float calvalP = gaussintPm * geocal->GetBinContent(g+1) * pid_part[glob];
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calvalP , calvalM );
        }
        if (-3==sys) {
          float calvalM = gaussintMs1 * geocal->GetBinContent(g+1) * pid_part[glob];
          float calvalP = gaussintPs1 * geocal->GetBinContent(g+1) * pid_part[glob];
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calvalP , calvalM );
        }
        if (-2==sys) {
          float calvalM = gaussintMs2 * geocal->GetBinContent(g+1) * pid_part[glob];
          float calvalP = gaussintPs2 * geocal->GetBinContent(g+1) * pid_part[glob];
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calvalP , calvalM );
        }
        if (-1==sys) {
          calvalerr = gaussint * geocal->GetBinError(g+1) * pid_part[glob];
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calval+3*calvalerr , calval-3*calvalerr );
        }
        if (0<=sys) {
      //PIDhists_data[g]->SetBinContent(1+sys,PIDhists_data[g]->GetBinContent(1+sys)+3*PIDhists_data[g]->GetBinContent(1+sys));
      //FIXME
          calvalerr = gaussint * geocal->GetBinContent(g+1) * pid_parte[glob] - gaussint * geocal->GetBinContent(g+1) * pid_part[glob];
//          if (calvalerr<calval*0.05) {
//            calvalerr = calval*0.05;
//          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calval+3*calvalerr , calval-3*calvalerr );
        }
        std::cout << " calval   = " << calval << " +/- " << calvalerr << std::endl;
        std::cout << " mass range " << li->GetMasslow(mm) << "\t" << li->GetMasshigh(mm) << std::endl;
      }
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
