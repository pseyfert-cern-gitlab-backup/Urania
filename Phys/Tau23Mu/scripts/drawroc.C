#include "calibrateGEO.C"
const int rocpoints = 50;
float interestingvalues[rocpoints];
GeoMVACut oldcuts[rocpoints];
GeoMVACut newcuts[rocpoints];

float oldeffs[rocpoints+4];
float neweffs[rocpoints+4];
TH1* oldroc;
TH1* newroc;
TTree* taumcold;
TTree* taumcnew;
TTree* dsmcold;
TTree* dsmcnew;
TTree* dsdataold;
TTree* dsdatanew;
TTree* BkgTree1;
TTree* BkgTree2;
TH1* oldcorrection;
TH1* newcorrection;
//void loadfiles() {
//  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
//  ff->GetObject("rds_data",dsmcold);
//  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2e2.root","read");
//  ff->GetObject("rds_data",dsmcnew);
//  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e2.root","read");
//  ff->GetObject("rds_data",dsdataold);
//  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2e2.root","read");
//  ff->GetObject("rds_data",dsdatanew);
//  TChain* buffer = new TChain("Tau23Mu");
//  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e2_flatV2.root"); 
//  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e2_flatV2.root"); 
//  taumcold = (TTree*) buffer;
//  TChain* buffer = new TChain("Tau23Mu");
//  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3.2e2_flatV3.root"); 
//  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3.2e2_flatV3.root"); 
//  taumcnew = (TTree*) buffer;
//  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3e2_1024_maybe.root","read");
//  ff->GetObject("Tau23Mu",BkgTree1);
//  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3.2e2_1024pb_flatV3.root","read");
//  ff->GetObject("Tau23Mu",BkgTree2);
//
//}

void loadfiles_D() {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2oe2.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2oe2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e2_flatV2.root"); 
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e2_flatV2.root"); 
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2oe2_flatV3.root"); 
  buffer->Add("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2oe2_flatV3.root"); 
  taumcnew = (TTree*) buffer;
  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile("~/tmpbuffer/stp17_mud_BDTv3.2De2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);

}

void loadfiles_BOTH() {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2BOTHe2.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2BOTHe2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e2_flatV2.root"); 
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e2_flatV2.root"); 
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2BOTHe2_flatV3.root"); 
  buffer->Add("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2BOTHe2_flatV3.root"); 
  taumcnew = (TTree*) buffer;
  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile("~/tmpbuffer/stp17_mud_BDTv3.2BOTHe2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);

}

void loadfiles_DATA() {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2DATAe2.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2DATAe2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e2_flatV2.root"); 
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e2_flatV2.root"); 
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2DATAe2_flatV3.root"); 
  buffer->Add("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2DATAe2_flatV3.root"); 
  taumcnew = (TTree*) buffer;
  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile("~/tmpbuffer/stp17_mud_BDTv3.2DATAe2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);

}
loadfilesswap(TString part) {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e2_flatV2.root"); 
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e2_flatV2.root"); 
  taumcnew = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  //buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mud_BDTv3.2")+part+"e2_flatV3.root"); 
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2")+part+"e2_flatV3.root"); 
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2")+part+"e2_flatV3.root"); 
  taumcold = (TTree*) buffer;
  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);
  ff = new TFile(TString("~/tmpbuffer/stp17_mud_BDTv3.2")+part+"e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);


}
loadfiles(TString part) {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2STDe2_flatV3.root"); 
  buffer->Add("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2STDe2_flatV3.root"); 
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2")+part+"e2_flatV3.root"); 
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2")+part+"e2_flatV3.root"); 
  taumcnew = (TTree*) buffer;
  ff = new TFile("~/tmpbuffer/stp17_mud_BDTv3.2STDe2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile(TString("~/tmpbuffer/stp17_mud_BDTv3.2")+part+"e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);
}
smearedload() {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/smeared_v3e2.root"),"read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2STDe2_flatV3.root"); 
  buffer->Add("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2STDe2_flatV3.root"); 
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2")+part+"e2_flatV3.root"); 
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2")+part+"e2_flatV3.root"); 
  taumcnew = (TTree*) buffer;
  ff = new TFile("~/tmpbuffer/stp17_mud_BDTv3.2STDe2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile(TString("~/tmpbuffer/stp17_mud_BDTv3.2")+part+"e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);


}

loadfiles(TString part, TString part2) {
  TFile* ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3.2")+part2+"e2.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2")+part+"e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile(TString("~/phd/dropbox/rd/2011-11-20/myTau/run/stp17_v3.2")+part2+"e2.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mud_BDTv3.2")+part+"e2_flatV3.root"); 
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  //buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mud_BDTv3.2")+part+"e2_flatV3.root"); 
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_md_BDTv3.2")+part2+"e2_flatV3.root"); 
  buffer->Add(TString("~/tmpbuffer/mctru_tau23mu_mu_BDTv3.2")+part2+"e2_flatV3.root"); 
  taumcnew = (TTree*) buffer;
  ff = new TFile(TString("~/tmpbuffer/stp17_mud_BDTv3.2")+part+"e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile(TString("~/tmpbuffer/stp17_mud_BDTv3.2")+part2+"e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);


}
loadOLD() {
  TFile* ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e2.root","read");
  ff->GetObject("rds_data",dsmcold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/mc_v3e1.root","read");
  ff->GetObject("rds_data",dsmcnew);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e2.root","read");
  ff->GetObject("rds_data",dsdataold);
  ff = new TFile("~/phd/dropbox/rd/2011-11-20/myTau/run/s17_v3e1.root","read");
  ff->GetObject("rds_data",dsdatanew);
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e2_flatV2.root");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e2_flatV2.root");
  taumcold = (TTree*) buffer;
  TChain* buffer = new TChain("Tau23Mu");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_mu_BDTv3e1_flatV2.root");
  buffer->Add("~/phd/dropbox/rd/newtuples/mctru_tau23mu_md_BDTv3e1_flatV2.root");
  taumcnew = (TTree*) buffer;
  ff = new TFile("~/phd/dropbox/rd/newtuples/stp17_mud_BDTv3e2_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree1);
  ff = new TFile("~/tmpbuffer/stp17_mud_BDTv3e1_1024pb_flatV3.root","read");
  ff->GetObject("Tau23Mu",BkgTree2);
}


void init(float pidcut1=-1.,float pidcut2=-10,bool calibrate = true, bool quick = false) {
  float startrange= 0.990;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    interestingvalues[i] = startrange + i*(1.-startrange)/rocpoints;
  }
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i << "\trej = " << interestingvalues[i]<< std::endl;
  }
  int workingon = rocpoints-1;
  TString cuts = "Hlt1Dec&&Hlt2Dec&&L0Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250";

  if (pidcut2<-2)
    pidcut2=pidcut1;

  int denomb1 = BkgTree1->Draw("mass",cuts+"&&(mass>2100||mass<1500)");
  if (!quick){
    for (float f = 1. ; f > -1. ; f-=0.005) {
      int numb = BkgTree1->Draw("mass",cuts+Form( "&&GeoMVA>%f&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))>%f&&(mass>2100||mass<1500)",f,pidcut1));
      //std::cout << "cutvalue " << f << "\tbackground
      float rej = 1.-((float)numb)/((float)denomb1);
      if (rej<interestingvalues[workingon]) {
        oldcuts[rocpoints-1-workingon].m_rej = rej;
        oldcuts[rocpoints-1-workingon].m_cut = f;
        workingon--;
      }
      if (workingon<0) break;
    }
    workingon = rocpoints-1;
  }
  int denomb2 = BkgTree2->Draw("mass",cuts+"&&(mass>2100||mass<1500)");
  std::cout << "denomb2 = " << denomb2 << std::endl;
  for (float f = 1. ; f > -1. ; f-=0.005) {
    int numb2 = BkgTree2->Draw("mass",cuts+Form( "&&GeoMVA>%f&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))>%f&&(mass>2100||mass<1500)",f,pidcut2));
    float rej = 1.-((float)numb2)/((float)denomb2);
    std::cout << "f = " << f << "\tref = " << rej << "\tnumerator = " << numb2 << std::endl;
    if (rej<interestingvalues[workingon]) {
      std::cout << "I TOOK f = " << f << "\tref = " << rej << "\tnumerator = " << numb2 << std::endl;
      std::cout << "I TOOK in bin " << rocpoints-1-workingon << std::endl;
      newcuts[rocpoints-1-workingon].m_rej = rej;
      newcuts[rocpoints-1-workingon].m_cut = f;
      workingon--;
    }
    if (workingon<0) break;
  }

  std::cout << "OLD" << std::endl;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i 
      << "\t\t\trej = " << oldcuts[i].m_rej << "\tcut = " << oldcuts[i].m_cut << std::endl;
  }
  std::cout << "NEW" << std::endl;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i 
      << "\t\t\trej = " << newcuts[i].m_rej << "\tcut = " << newcuts[i].m_cut << std::endl;
  }
  ////DEBUG
  ///return;

  oldcorrection = correctionFactors(dsmcold,taumcold);
  newcorrection = correctionFactors(dsmcnew,taumcnew);
  if (!calibrate) {
    for (unsigned int bb = 0 ; bb <= oldcorrection->GetNbinsX() +1 ; ++bb) { 
      oldcorrection->SetBinContent(bb,1.);
      newcorrection->SetBinContent(bb,1.);
    }
  }
  // force n_geobins to be effectively 2
  geobinning[0]=-1;
  geobinning[1]=.12345; // to be set later
  geobinning[2]=1;
  for (unsigned int i = 3 ; i <= n_geobins ; ++i) {
    geobinning[i]=2.;
  }

  for (unsigned i = 0 ; i < rocpoints ; ++i) {
    std::cout << "processing ROC point " << i << std::endl;
    if(!quick) {
      geobinning[1] = oldcuts[i].m_cut;
      for (unsigned int j = 0 ; j <= n_geobins ; ++j) {
        std::cout << "geobinning["<<j<<"]\t"<<geobinning[j]<<std::endl;
      }
      TH1* calibration = geocalibration(dsdataold,oldcorrection);
      oldcuts[i].m_sigeff = calibration->GetBinContent(2);
    }
    geobinning[1] = newcuts[i].m_cut;
    for (unsigned int j = 0 ; j <= n_geobins ; ++j) {
      std::cout << "geobinning["<<j<<"]\t"<<geobinning[j]<<std::endl;
    }
    calibration = geocalibration(dsdatanew,newcorrection);
    newcuts[i].m_sigeff = calibration->GetBinContent(2);
  }


  std::cout << "OLD" << std::endl;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i 
      << "\t\t\trej = " << oldcuts[i].m_rej << "\tcut = " << oldcuts[i].m_cut << "\teff = " << oldcuts[i].m_sigeff<< std::endl;
  }
  std::cout << "NEW" << std::endl;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i 
      << "\t\t\trej = " << newcuts[i].m_rej << "\tcut = " << newcuts[i].m_cut << "\teff = " << newcuts[i].m_sigeff<< std::endl;
  }
  std::cout << "sanitise by sorting" << std::endl;

  for (int r = 0 ; r < rocpoints-1 ; ++r) {
    if (fabs(oldcuts[r].m_sigeff-oldcuts[r+1].m_sigeff)<0.0001 && oldcuts[r].m_sigeff>oldcuts[r+1].m_sigeff) {
      oldcuts[r+1].m_sigeff = oldcuts[r].m_sigeff + 0.00001;
    }
    if (oldcuts[r].m_sigeff>oldcuts[r+1].m_sigeff) {
      GeoMVACut buffer = oldcuts[r];
      oldcuts[r] = oldcuts[r+1];
      oldcuts[r+1]=buffer;
      r = -1;
    } else if (fabs(oldcuts[r].m_sigeff-oldcuts[r+1].m_sigeff)<0.000001) {
      oldcuts[r+1].m_sigeff += 0.00001;
    }
  }
  for (int r = 0 ; r < rocpoints-1 ; ++r) {
    if (fabs(newcuts[r].m_sigeff-newcuts[r+1].m_sigeff)<0.0001 && newcuts[r].m_sigeff>newcuts[r+1].m_sigeff) {
      newcuts[r+1].m_sigeff = newcuts[r].m_sigeff + 0.00001;
    }
    if (newcuts[r].m_sigeff>newcuts[r+1].m_sigeff) {
      GeoMVACut buffer = newcuts[r];
      newcuts[r] = newcuts[r+1];
      newcuts[r+1]=buffer;
      r = -1;
    } else if (fabs(newcuts[r].m_sigeff-newcuts[r+1].m_sigeff)<0.000001) {
      newcuts[r+1].m_sigeff += 0.00001;
    }
  }


  std::cout << "sanitised by sorting" << std::endl;

  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    oldeffs[i+2] = oldcuts[i].m_sigeff;
    neweffs[i+2] = newcuts[i].m_sigeff;
  }
  oldeffs[1]=oldeffs[2]-0.0001;
  oldeffs[0]=oldeffs[1]-0.0001;
  oldeffs[rocpoints+2]=oldeffs[rocpoints+1]+0.0001;
  oldeffs[rocpoints+3]=oldeffs[rocpoints+2]+0.0001;
  neweffs[1]=neweffs[2]-0.0001;
  neweffs[0]=neweffs[1]-0.0001;
  neweffs[rocpoints+2]=neweffs[rocpoints+1]+0.0001;
  neweffs[rocpoints+3]=neweffs[rocpoints+2]+0.0001;

  std::cout << "OLD" << std::endl;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i 
      << "\t\t\trej = " << oldcuts[i].m_rej << "\tcut = " << oldcuts[i].m_cut << "\teff = " << oldcuts[i].m_sigeff<< std::endl;
  }
  std::cout << "NEW" << std::endl;
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    std::cout << "i = " << i 
      << "\t\t\trej = " << newcuts[i].m_rej << "\tcut = " << newcuts[i].m_cut << "\teff = " << newcuts[i].m_sigeff<< std::endl;
  }
  for (unsigned int i = 0 ; i < rocpoints+4 ; ++i) {
    std::cout << "oldeffs["<<i<<"] = " << oldeffs[i] << std::endl;
  }

  for (unsigned int i = 0 ; i < rocpoints+4 ; ++i) {
    std::cout << "neweffs["<<i<<"] = " << neweffs[i] << std::endl;
  }

  oldroc = new TH1F("oldroc","oldroc",rocpoints+2,oldeffs);
  newroc = new TH1F("newroc","newroc",rocpoints+2,neweffs);
  for (unsigned int i = 0 ; i < rocpoints ; ++i) {
    oldroc->SetBinContent(i+2,oldcuts[i].m_rej);
    newroc->SetBinContent(i+2,newcuts[i].m_rej);
  }
  TCanvas* c = new TCanvas();
  if (calibrate) {
    oldroc->GetXaxis()->SetTitle("calibrated #tau efficiency");
  } else {
    oldroc->GetXaxis()->SetTitle("#D_{s} efficiency");
  }
  oldroc->SetLineColor(kRed);
  oldroc->Draw("L");
  newroc->SetLineColor(kBlue);
  newroc->Draw("L same");
  c->BuildLegend();
}

void getRoc() {
  TCanvas* c = new TCanvas();
  oldroc->SetLineColor(kRed);
  oldroc->Draw("L");
  newroc->SetLineColor(kBlue);
  newroc->Draw("L same");
  c->BuildLegend();
}
