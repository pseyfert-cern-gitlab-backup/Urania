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
      TString fname = TString("/home/pseyfert/physiwork/zoontuple/Erasmus_v8r1/PIDCalib/PIDPerfScripts/x86_64-slc5-gcc43-opt/geo_ds2etamunu/") + lookup(g,p);
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
        baums[glob]->Draw("mass>>buffer",TString("(")+li->getGeoRefString()+")*(Event_PIDCalibEff!=0)");
        den = buffer->GetSum();
        baums[glob]->Draw("mass>>buffer",TString("(")+li->getGeoRefString()+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        num = buffer->GetSum();
        if (sys==p) {
          baums[glob]->Draw("mass>>buffer",TString("(")+li->getGeoRefString()+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff+Event_PIDCalibEffError");
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
        baums[glob_2]->Draw("mass>>buffer2",TString("(")+li->getGeoRefString()+")*(Event_PIDCalibEff!=0)");
        float den2 = buffer2->GetSum();
        baums[glob_2]->Draw("mass>>buffer2",TString("(")+li->getGeoRefString()+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        float num2 = buffer2->GetSum();
        float nume2 = num2;
        if (sys==p+1) {
          baums[glob_2]->Draw("mass>>buffer2",TString("(")+li->getGeoRefString()+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff+Event_PIDCalibEffError");
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



  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      std::cout << "p=" << p << "\tg=" << g;
      int thisbin = g+p*n_geobins;
      int glob = li->GetGlobalMVAbin(g,p);
      for (int mm = 0 ; mm < (int)(li->GetNMassbins()+0.1) ; ++mm) {
        float gaussint = 0.5 * (1+ TMath::Erf(1./g_tauwidth/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)));
        float calvalerr;
        gaussint -= 0.5 * (1+ TMath::Erf(1./g_tauwidth/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        std::cout << " integral = " << gaussint << std::endl;
        float calval = gaussint * geocal->GetBinContent(g+1) * pid_part[glob];
        if (sys<0) {
          calvalerr = gaussint * geocal->GetBinError(g+1) * pid_part[glob];
          if (calvalerr<calval*0.05) {
            calvalerr = calval*0.05;
          }
          li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calval+3*calvalerr , calval-3*calvalerr );
        } else {
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



