#include "vector"

gSystem->Load("../params/libLimitROOT.so");

float g_taumass = 1779.1; // 0.1
float g_tauwidth1= 7.7;   // 0.1
float g_tauwidth2= 12.;   // 0.8


float g_corr0 = 1.f;
float g_corr1 = .957f;
float g_corr2 = .936f;
float g_corr3 = .926f;
float g_corr4 = .911f;
float g_corr5 = .894f;

void pidcorrection(int par) {
  if (par == 20) {
  g_corr0 = 1.00 * 1.f;
  g_corr1 = 1.02 * .957f;
  g_corr2 = 1.02 * .936f;
  g_corr3 = 1.02 * .926f;
  g_corr4 = 1.02 * .911f;
  g_corr5 = 1.02 * .894f;
  }
  if (par == 21) {
  g_corr0 = 1.00 * 1.f;
  g_corr1 = 0.98 * .957f;
  g_corr2 = 0.98 * .936f;
  g_corr3 = 0.98 * .926f;
  g_corr4 = 0.98 * .911f;
  g_corr5 = 0.98 * .894f;
  }
}

void setmasses(int par, float sigmas) {

  g_taumass = 1779.0; // 0.1
  if (1==par) {
    g_taumass = 1779.0 + sigmas* 0.1;
  }
  g_tauwidth1= 7.6;   // 0.1
  if (2==par) {
    g_tauwidth1= 7.6 + sigmas* 0.1;
  }
  g_tauwidth2= 11.5;   // 0.5
  if (3==par) {
    g_tauwidth2= 11.5 + sigmas * 0.5;
  }


}

/*
 *
 root -l 
 gSystem->Load("../params/libLimitROOT.so");
 .L newcal2012.C
 limit_interface* li = newcal(true)
 TH1* calib = li->GetFilledHistogram()
 calib->SetName("central")
 TFile* ff = new TFile("base_2012_calibV3_up_1down.root","recreate")
 ff->WriteTObject(calib)
 ff->Close()
 li = newcal(false)
 calib = li->GetFilledHistogram()
 calib->SetName("central")
 ff = new TFile("base_2012_calibV3_down_1down.root","recreate")
 ff->WriteTObject(calib)
 ff->Close()
 .q
 */

//TString preweight = "NgammaVLLRR_RAD*(";

TString preweight(int prechoice = 0) {
 /// TODO: weights from 2011 table
 if (0==prechoice) return  TString("(");

 //if (1==prechoice) return  TString("(2.-((production==1)*1.0419)+((production!=1)*0.8808))*(");
 //if (2==prechoice) return  TString("(2.-((production==2)*2.0000)+((production!=2)*0.9957))*(");
 //if (3==prechoice) return  TString("(2.-((production==4)*1.1728)+((production==8)*1.1728)+((production!=8)*(production!=4)*0.9666))*(");
 //if (4==prechoice) return  TString("(2.-((production==5)*1.2234)+((production!=5)*0.9768))*(");

 if (5==prechoice) return  TString("(((production==1)*(1.0419))+((production!=1)*(0.8808)))*(");
 if (6==prechoice) return  TString("(((production==2)*(2.0000))+((production!=2)*(0.9957)))*(");
 if (7==prechoice) return  TString("(((production==4)*(1.1728))+((production==8)*(1.1728))+((production!=8)*(production!=4)*(0.9666)))*(");
 if (8==prechoice) return  TString("(((production==5)*(1.2234))+((production!=5)*(0.9768)))*(");

 if (1==prechoice) return  TString("(2.-(((production==1)*(1.0419))+((production!=1)*(0.8808))))*(");
 if (2==prechoice) return  TString("(2.-(((production==2)*(2.0000))+((production!=2)*(0.9957))))*(");
 if (3==prechoice) return  TString("(2.-(((production==4)*(1.1728))+((production==8)*(1.1728))+((production!=8)*(production!=4)*(0.9666))))*(");
 if (4==prechoice) return  TString("(2.-(((production==5)*(1.2234))+((production!=5)*(0.9768))))*(");


 //if (5==prechoice) return  TString("(((production==1)*(1.0419+0.0419))+((production!=1)*(0.8808-(1.-0.8808))))*(");
 //if (6==prechoice) return  TString("(((production==2)*(2.0000+1.0000))+((production!=2)*(0.9957-(1.-0.9957))))*(");
 //if (7==prechoice) return  TString("(((production==4)*(1.1728+0.1728))+((production==8)*(1.1728+0.1728))+((production!=8)*(production!=4)*(0.9666-(1.-0.9666))))*(");
 //if (8==prechoice) return  TString("(((production==5)*(1.2234+0.2234))+((production!=5)*(0.9768-(1.-0.9768))))*(");

 //if (1==prechoice) return  TString("(2.-(((production==1)*(1.0419+0.0419))+((production!=1)*(0.8808-(1.-0.8808)))))*(");
 //if (2==prechoice) return  TString("(2.-(((production==2)*(2.0000+1.0000))+((production!=2)*(0.9957-(1.-0.9957)))))*(");
 //if (3==prechoice) return  TString("(2.-(((production==4)*(1.1728+0.1728))+((production==8)*(1.1728+0.1728))+((production!=8)*(production!=4)*(0.9666-(1.-0.9666)))))*(");
 //if (4==prechoice) return  TString("(2.-(((production==5)*(1.2234+0.2234))+((production!=5)*(0.9768-(1.-0.9768)))))*(");


 if ( 9==prechoice) return TString("NgammaVLLLL*(");
 if (10==prechoice) return TString("NgammaVLLRR*(");
 if (11==prechoice) return TString("NgammaRAD*(");
 if (12==prechoice) return TString("NgammaVLLLL_RAD*(");
 if (13==prechoice) return TString("NgammaVLLRR_RAD*(");


  return  TString("(");

}

limit_interface* newcal(bool up = true, int prechoice = 0) {
  if (14==prechoice) {
    setmasses(1,-3.);
  }
  if (15==prechoice) {
    setmasses(2,-3.);
  }
  if (16==prechoice) {
    setmasses(3,-3.);
  }
  if (17==prechoice) {
    setmasses(1,3.);
  }
  if (18==prechoice) {
    setmasses(2,3.);
  }
  if (19==prechoice) {
    setmasses(3,3.);
  }
  if (20==prechoice || 21==prechoice) {
    pidcorrection(prechoice);
  }
  limit_interface* li = new limit_interface();
  std::vector<TTree*> trees;
  std::vector<float> pid_part;
  std::vector<float> pid_parte;
  std::vector<float> pid_partee;
  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      trees.push_back(NULL);
      pid_part.push_back(0.f);
      pid_parte.push_back(0.f);
      pid_partee.push_back(0.f);
    }
  }

  for (int p = 0 ; p < li->the_pidbins() ; ++p) {
    for (int g = 0 ; g < li->the_geobins() ; ++g) {
      //if (0==p) continue;
      int glob = li->GetGlobalMVAbin(g,p);
      TFile* ff ;
      if (0==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Up.0.4.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Down.0.4.2012.root","read");
        }
      }
      if (1==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Up.0.4.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Down.0.4.2012.root","read");
        }
      }
      if (2==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Up.0.54.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Down.0.54.2012.root","read");
        }
      }
      if (3==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Up.0.61.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Down.0.61.2012.root","read");
        }
      }
      if (4==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Up.0.71.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Down.0.71.2012.root","read");
        }
      }
      if (5==p) {
        if (up) {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Up.0.8.2012.root","read");
        } else {
          ff = new TFile("~/physiwork/pseyfert/zoontuple/Urania_v2r1/PIDCalib/PIDPerfScripts/scripts/python/MultiTrack/tau.Down.0.8.2012.root","read");
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
      float numee;

      if (0!=p) {

        trees[glob]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)");
        den = buffer->GetSum();
        trees[glob]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        num = buffer->GetSum();

        trees[glob]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*(Event_PIDCalibEff+Event_PIDCalibErr)");
        nume = buffer->GetSum();
        trees[glob]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*(Event_PIDCalibEff-Event_PIDCalibErr)");
        numee = buffer->GetSum();

      } else {
        den = 1.f;
        num = 1.f;
        nume = 1.f;
        numee = 1.f;
      }
      float corr = 1.f;
      if (0==p) { corr = g_corr0; }
      if (1==p) { corr = g_corr1; }
      if (2==p) { corr = g_corr2; }
      if (3==p) { corr = g_corr3; }
      if (4==p) { corr = g_corr4; }
      if (5==p) { corr = g_corr5; }
      float corr3 = corr*corr*corr;
      pid_part[glob] = num/den * corr3;
      pid_parte[glob] = nume/den * corr3;
      pid_partee[glob] = numee/den * corr3;

      if (p < li->the_pidbins() -1) {
        int glob2 = li->GetGlobalMVAbin(g,p+1);
        std::cout << "p = " << p << "\tp2 = " << p+1 << "\tg = " << g << "\tglob = " << glob << "\tglob2 = " << glob2 << "\t(" << "size = " << trees.size() << "\n";

        trees[glob2]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)");
        float den2 = buffer->GetSum();
        trees[glob2]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*Event_PIDCalibEff");
        float num2 = buffer->GetSum();

        trees[glob2]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*(Event_PIDCalibEff+Event_PIDCalibErr)");
        float nume2 = buffer->GetSum();
        trees[glob2]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")*(Event_PIDCalibEff!=0)*(Event_PIDCalibEff-Event_PIDCalibErr)");
        float numee2 = buffer->GetSum();
      float corrprime = 1.f;
      if (0==p+1) { corrprime = g_corr0; }
      if (1==p+1) { corrprime = g_corr1; }
      if (2==p+1) { corrprime = g_corr2; }
      if (3==p+1) { corrprime = g_corr3; }
      if (4==p+1) { corrprime = g_corr4; }
      if (5==p+1) { corrprime = g_corr5; }
      if (6==p+1) { std::cout << "ERROR" << std::endl;corrprime = .921f; }
      float corr3prime = corrprime*corrprime*corrprime;

        pid_part[glob] = num/den * corr3 - num2/den2 * corr3prime;
        if (0==p) {
         std::cout << pid_part[glob] << num << " / " << den << " - " << num2 << " / " << den2 << "\n";
        }
        pid_parte[glob] = nume/den * corr3 - nume2/den2 * corr3prime;
        pid_partee[glob] = nume/den * corr3 - numee2/den2 * corr3prime;


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

        trees[glob]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+"&&"+Form("MN_BLEND_FLAT>%f&&MN_BLEND_FLAT<%f",li->GetGeolow(g),li->GetGeohigh(g))+")");
        float num = buffer->GetSum();
        trees[glob]->Draw("mass>>buffer",preweight(prechoice)+li->CutString2012()+")");
        float den = buffer->GetSum();
        float calval = gaussint * num/den * pid_part[glob];
        float calvale = gaussint * num/den * pid_parte[glob];
        float calvalee = gaussint * num/den * pid_partee[glob];
        li->SetPrivate(g,p,0.5*li->GetMasslow(mm)+0.5*li->GetMasshigh(mm) , calval, calvale , calvalee );
      }
    }
  }


  return li;

}



void newcal(int c) {
  TH1* calib;
  TH1* calibp;
  TH1* calibm;
  TFile* ff;
  limit_interface* li;
    li = newcal(true,c);
    calib = li->GetFilledHistogram();
    calibp = li->GetFilledHistogram_PLUS();
    calibm = li->GetFilledHistogram_MINUS();
    calib->SetName("central");
    calibp->SetName("plus");
    calibm->SetName("minus");
    if (c!=0) {
      ff = new TFile(Form("base_2012_calibV4_up_sys%d.root",c),"recreate");
    } else {
      ff = new TFile(Form("base_2012_calibV4_up.root"),"recreate");
    }
    ff->WriteTObject(calib);
    ff->WriteTObject(calibp);
    ff->WriteTObject(calibm);
    ff->Close()           ;
    li = newcal(false,c);
    calib = li->GetFilledHistogram();
    calibp = li->GetFilledHistogram_PLUS();
    calibm = li->GetFilledHistogram_MINUS();
    calib->SetName("central");
    calibp->SetName("plus");
    calibm->SetName("minus");
    if (c!=0) {
      ff = new TFile(Form("base_2012_calibV4_down_sys%d.root",c),"recreate");
    } else {
      ff = new TFile(Form("base_2012_calibV4_down.root"),"recreate");
    }
    ff->WriteTObject(calib);
    ff->WriteTObject(calibp);
    ff->WriteTObject(calibm);
    ff->Close()           ;
}


