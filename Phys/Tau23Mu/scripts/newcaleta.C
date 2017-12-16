#include "vector"
float g_taumass = 1779.0;
float g_tauwidth2= 11.5;
float g_tauwidth1= 7.6;

/*
 *
 root -l 
 gSystem->Load("../params/libLimitROOT.so");
 .L newcal2011.C
 limit_interface* li = newcal(true)
 TH1* calib = li->GetFilledHistogram()
 calib->SetName("central")
 TFile* ff = new TFile("base_2011_newcalib_up_1down.root","recreate")
 ff->WriteTObject(calib)
 ff->Close()
 li = newcal(false)
 calib = li->GetFilledHistogram()
 calib->SetName("central")
 ff = new TFile("base_2011_newcalib_down_1down.root","recreate")
 ff->WriteTObject(calib)
 ff->Close()
 .q
 */

//TString preweight = "NgammaVLLRR_RAD*(";

TString preweight = "(";
//TString preweight = "(2.-((production==1)*1.0419)+((production!=1)*0.8808))*(";
//TString preweight = "(2.-((production==2)*2.0000)+((production!=2)*0.9957))*(";
//TString preweight = "(2.-((production==4)*1.1728)+((production==8)*1.1728)+((production!=8)*(production!=4)*0.9666))*(";
//TString preweight = "(2.-((production==5)*1.2234)+((production!=5)*0.9768))*(";

limit_interface* newcal(bool up = true) {
  limit_interface* li = new limit_interface();
  std::vector<TTree*> trees;
  std::vector<float> pid_part;
  std::vector<float> pid_parte;
  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      trees.push_back(NULL);
      pid_part.push_back(0.f);
      pid_parte.push_back(0.f);
    }
  }

  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      //if (0==p) continue;
      int glob = li->GetGlobalMVAbin(g,p);
      TFile* ff ;
      if (0==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Up.0.4.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Down.0.4.2012.root","read");
        }
      }
      if (1==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Up.0.4.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Down.0.4.2012.root","read");
        }
      }
      if (2==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Up.0.54.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Down.0.54.2012.root","read");
        }
      }
      if (3==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Up.0.61.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Down.0.61.2012.root","read");
        }
      }
      if (4==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Up.0.71.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Down.0.71.2012.root","read");
        }
      }
      if (5==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Up.0.8.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/ds2etamunu.Down.0.8.2012.root","read");
        }
      }
      ff->GetObject("Tau23Mu",trees[glob]);
    }
  }
  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      int glob = li->GetGlobalMVAbin(g,p);
      std::cout << "p = " << p << "\tp2 = " << p+1 << "\tg = " << g << "\tglob = " << glob << "\t(" << "size = " << trees.size() << "\t" << trees[glob] << "\n";
    }
  }

  TH1F* buffer = new TH1F("buffer","buffer",1,0.,5000.);
  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      int glob = li->GetGlobalMVAbin(g,p);

      float den ;
      float num;
      float nume;

      if (0!=p) {

        trees[glob]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)");
        den = buffer->GetSum();
        trees[glob]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        num = buffer->GetSum();

        trees[glob]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*(Event_PIDCalibEff+Event_PIDCalibErr)");
        nume = buffer->GetSum();

      } else {
        den = 1.f;
        num = 1.f;
        nume = 1.f;
      }
      pid_part[glob] = num/den;
      pid_parte[glob] = nume/den;

      if (p < li->the_pidbins() -1) {
        int glob2 = li->GetGlobalMVAbin(g,p+1);
        std::cout << "p = " << p << "\tp2 = " << p+1 << "\tg = " << g << "\tglob = " << glob << "\tglob2 = " << glob2 << "\t(" << "size = " << trees.size() << "\n";

        trees[glob2]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)");
        float den2 = buffer->GetSum();
        trees[glob2]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        float num2 = buffer->GetSum();

        trees[glob2]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*(Event_PIDCalibEff+Event_PIDCalibErr)");
        float nume2 = buffer->GetSum();

        pid_part[glob] = num/den - num2/den2;
        if (0==p) {
         std::cout << pid_part[glob] << num << " / " << den << " - " << num2 << " / " << den2 << "\n";
        }
        pid_parte[glob] = nume/den - nume2/den2;


      }
    }
  }


  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      std::cout << "p=" << p << "\tg=" << g;
      int glob = li->GetGlobalMVAbin(g,p);

      for (int mm = 0 ; mm < (int)(li->GetNMassbins()+0.1) ; ++mm) {
        float gaussint1 = 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth1/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint2 = 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasshigh(mm) - g_taumass)))- 0.5 * (1+ TMath::Erf(1./g_tauwidth2/sqrt(2) * (li->GetMasslow(mm) - g_taumass)));
        float gaussint =    .7*gaussint1    + .3*gaussint2;

        trees[glob]->Draw("mass>>buffer",preweight+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")");
        float num = buffer->GetSum();
        trees[glob]->Draw("mass>>buffer",preweight+li->CutString2012()+")");
        float den = buffer->GetSum();
        float calval = gaussint * num/den * pid_part[glob];
        li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calval , calval );
      }
    }
  }


  return li;

}





