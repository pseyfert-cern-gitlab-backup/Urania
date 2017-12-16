#include<iostream>

/**
* @brief get histograms for systematics w/o properly calculating them
*
* @param b the DOF which gets generated
* @param in the scenario (and thereby filename root
*/
void simple(int b, TString in) {

  limit_interface* li = new limit_interface();
  if (b>=li->the_pidbins()+li->the_geobins()) return ;
  TFile* out = new TFile(Form("%s_systematics_sig%d.root",in.Data(),b),"recreate");
  TFile* inf = new TFile(Form("%s.root",in.Data()),"read");
  TH2F* cent;
  inf->GetObject("central",cent);

  TH2F* plus = cent->Clone("plus");
  TH2F* minus = cent->Clone("minus");

  if (b>=li->the_geobins()) {
    /// this is a pidbin, loop over geo
    std::cout << "pid" << std::endl;
    b -= li->the_geobins();
    for (int j = 0 ; j < li->the_geobins() ; ++j) {
      int kk = li->GetGlobalMVAbin(j,b);
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        plus->SetBinContent(plus->GetBin(1+kk,1+m),1.195*plus->GetBinContent(plus->GetBin(1+kk,1+m)));
        minus->SetBinContent(minus->GetBin(1+kk,1+m),0.985*minus->GetBinContent(minus->GetBin(1+kk,1+m)));
      }
    }
  } else {
    std::cout << "geo" << std::endl;
    for (int j = 0 ; j < li->the_pidbins() ; ++j) {
      int kk = li->GetGlobalMVAbin(b,j);
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        plus->SetBinContent(plus->GetBin(1+kk,1+m),1.195*plus->GetBinContent(plus->GetBin(1+kk,1+m)));
        minus->SetBinContent(minus->GetBin(1+kk,1+m),0.985*minus->GetBinContent(minus->GetBin(1+kk,1+m)));
      }
    }
  }

  out->WriteTObject(plus);
  out->WriteTObject(minus);

  out->Close();
}


/**
* @brief generate histograms for systematics from the latest combineGEO_and_PID_forpaper.C file (check README)
*
* @param ins filename root
*/
void sim(TString ins = "CONF") {

  limit_interface* li = new limit_interface();
  TFile* ing = new TFile(Form("%s_geo.root",ins.Data()),"read");
  TH1* central_g;
  TH1* up_g;
  TH1* down_g;
  ing->GetObject("central",central_g);
  ing->GetObject("central_plus",up_g);
  ing->GetObject("central_minus",down_g);

  int counter = 0;

  for (unsigned g = 0 ; g < li->the_geobins() ; ++g) {
    TH2F* c_up = (TH2F*)central_g->Clone("plus");
    TH2F* c_down = (TH2F*)central_g->Clone("minus");
    for (unsigned p = 0 ; p < li->the_pidbins() ; ++p) {
      int kk = li->GetGlobalMVAbin(g,p);
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        c_up->SetBinContent(c_up->GetBin(1+kk,1+m),up_g->GetBinContent(c_up->GetBin(1+kk,1+m)));
        c_down->SetBinContent(c_down->GetBin(1+kk,1+m),down_g->GetBinContent(c_down->GetBin(1+kk,1+m)));
      }
    }
    TFile* out = new TFile(Form("%s_systematics_sig%d.root",ins.Data(),counter++),"recreate");
    out->WriteTObject(c_up);
    out->WriteTObject(c_down);
    out->Close();
  }
  for (unsigned p = 0 ; p < li->the_pidbins() ; ++p) {
    TFile* inp = new TFile(Form("%s_pid%d.root",ins.Data(),p),"read");
    TH2F* central_p;
    TH2F* up_p;
    TH2F* down_p;
    inp->GetObject("central",central_p);
    inp->GetObject("central_plus",up_p);
    inp->GetObject("central_minus",down_p);


    TH2F* c_up = (TH2F*)up_p->Clone("plus");
    TH2F* c_down = (TH2F*)down_p->Clone("minus");

    TFile* out = new TFile(Form("%s_systematics_sig%d.root",ins.Data(),counter++),"recreate");
    out->WriteTObject(c_up);
    out->WriteTObject(c_down);
    out->Close();
  }

  for (unsigned masscounter = 1 ; masscounter < 4 ; ++masscounter) {
    TFile* inp = new TFile(Form("%s_mass%d.root",ins.Data(),masscounter),"read");
    TH2F* central_p;
    TH2F* up_p;
    TH2F* down_p;
    inp->GetObject("central",central_p);
    inp->GetObject("plus",up_p);
    inp->GetObject("minus",down_p);


    TH2F* c_up = (TH2F*)up_p->Clone("plus");
    TH2F* c_down = (TH2F*)down_p->Clone("minus");
    c_up->Scale(1./c_up->GetSum());
    c_down->Scale(1./c_down->GetSum());
    c_up->Scale(up_p->GetSum()/central_p->GetSum());
    c_down->Scale(down_p->GetSum()/central_p->GetSum());

    TFile* out = new TFile(Form("%s_systematics_sig%d.root",ins.Data(),counter++),"recreate");
    out->WriteTObject(c_up);
    out->WriteTObject(c_down);
    out->Close();
  }

}

int goesto(int comesfrom) {
  if (1==comesfrom) return -2;
  if (2==comesfrom) return -2;
  if (3==comesfrom) return -2;
  if (4==comesfrom) return -2;
  if (5==comesfrom) return -2;
  if (6==comesfrom) return -2;
  if (7==comesfrom) return 1;
  if (8==comesfrom) return 2;
  if (9==comesfrom) return 3;
  if (10==comesfrom) return 4;
  if (11==comesfrom) return -2;
  if (12==comesfrom) return 5;
  if (13==comesfrom) return 6;
  if (14==comesfrom) return 7;
  if (15==comesfrom) return 8;
  if (16==comesfrom) return -2;
  if (17==comesfrom) return 9;
  if (18==comesfrom) return 10;
  if (19==comesfrom) return 11;
  if (20==comesfrom) return 12;
  if (21==comesfrom) return -2;
  if (22==comesfrom) return 13;
  if (23==comesfrom) return 14;
  if (24==comesfrom) return 15;
  if (25==comesfrom) return 16;
  if (26==comesfrom) return -5;
  if (27==comesfrom) return -5;
  if (28==comesfrom) return -5;
  if (29==comesfrom) return -5;
}

int goesto_v3(int comesfrom) {
  if (1==comesfrom) return -2;
  if (2==comesfrom) return -2;
  if (3==comesfrom) return -2;
  if (4==comesfrom) return -2;
  if (5==comesfrom) return -2;
  if (6==comesfrom) return -2;

  if (7==comesfrom) return -2;
  if (8==comesfrom) return   1;
  if (9==comesfrom) return   2;
  if (10==comesfrom) return  3;
  if (11==comesfrom) return  4;
  if (12==comesfrom) return  5;

  if (13==comesfrom) return -2;
  if (14==comesfrom) return  6;
  if (15==comesfrom) return  7;
  if (16==comesfrom) return  8;
  if (17==comesfrom) return  9;
  if (18==comesfrom) return 10;

  if (19==comesfrom) return -2;
  if (20==comesfrom) return 11;
  if (21==comesfrom) return 12;
  if (22==comesfrom) return 13;
  if (23==comesfrom) return 14;
  if (24==comesfrom) return 15;

  if (25==comesfrom) return -2;
  if (26==comesfrom) return 16;
  if (27==comesfrom) return 17;
  if (28==comesfrom) return 18;
  if (29==comesfrom) return 19;
  if (30==comesfrom) return 20;

  if (31==comesfrom) return -2;
  if (32==comesfrom) return 21;
  if (33==comesfrom) return 22;
  if (34==comesfrom) return 23;
  if (35==comesfrom) return 24;
  if (36==comesfrom) return 25;



}

int goesto_v2(int comesfrom) {
  
  if (1==comesfrom)  return -2;
  if (2==comesfrom)  return -2;
  if (3==comesfrom)  return -2;
  if (4==comesfrom)  return -2;
  if (5==comesfrom)  return -2;
  if (6==comesfrom)  return -2;
  if (7==comesfrom)  return -2;

  if (8==comesfrom)  return -2;
  if (9==comesfrom)  return 1;
  if (10==comesfrom) return 2;
  if (11==comesfrom) return 3;
  if (12==comesfrom) return 4;
  if (13==comesfrom) return 5;
  if (14==comesfrom) return 6;

  if (15==comesfrom) return -2;
  if (16==comesfrom) return 7;
  if (17==comesfrom) return 8;
  if (18==comesfrom) return 9;
  if (19==comesfrom) return 10;
  if (20==comesfrom) return 11;
  if (21==comesfrom) return 12;

  if (22==comesfrom) return -2;
  if (23==comesfrom) return 13;
  if (24==comesfrom) return 14;
  if (25==comesfrom) return 15;
  if (26==comesfrom) return 16;
  if (27==comesfrom) return 17;
  if (28==comesfrom) return 18;

  if (29==comesfrom) return -2;
  if (30==comesfrom) return 19;
  if (31==comesfrom) return 20;
  if (32==comesfrom) return 21;
  if (33==comesfrom) return 22;
  if (34==comesfrom) return 23;
  if (35==comesfrom) return 24;

  if (36==comesfrom) return -2;
  if (37==comesfrom) return 25;
  if (38==comesfrom) return 26;
  if (39==comesfrom) return 27;
  if (40==comesfrom) return 28;
  if (41==comesfrom) return 29;
  if (42==comesfrom) return 30;
  return -5;
}

/**
* @brief convert signal histograms to trashed background histograms
*
* @param source
*/
void convert(TString source = TString("CONF_MC11")) {
  limit_interface* li = new limit_interface();
  TString ins = "";
  TFile* ing = new TFile(Form("%s_sigPDF.root",source.Data()),"read");
  TH2F* central_g;
  ing->GetObject("central",central_g);
  central_g->Scale(1./central_g->GetSum());

  int binsaftertrashing = 25;

  TH2F* cout = new TH2F("cent","central",binsaftertrashing,0,binsaftertrashing,central_g->GetNbinsY(),central_g->GetYaxis()->GetBinLowEdge(1),central_g->GetYaxis()->GetBinLowEdge(1+central_g->GetNbinsY()));
  for (int b = 1 ; b <= central_g->GetNbinsX() ; ++b) {
    for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
      if (goesto_v3(b)<0) continue;
      int bbout = cout->GetBin(goesto_v3(b),1+m);
      int bbin = central_g->GetBin(b,1+m);
      cout->SetBinContent(bbout,central_g->GetBinContent(bbin));
    }
  }

  TFile* out = new TFile(Form("%s_trash_sigPDF.root",source.Data()),"recreate");
  cout->SetName("central");
  out->WriteTObject(cout);
  out->Close();

  for (int counter = 0 ; counter<=11 ; ++counter) {
//    if (0==counter||5==counter) continue;
    TH2F* p;
    TH2F* mi;
    ing = new TFile(Form("%s_systematics_sig%d.root",source.Data(),counter),"read");
    ing->GetObject("plus",p);
    ing->GetObject("minus",mi);
    mi->Scale(1./mi->GetSum());
    p->Scale(1./p->GetSum());
    TH2F* pout = new TH2F("pl","plus",binsaftertrashing,0,binsaftertrashing,p->GetNbinsY(),p->GetYaxis()->GetBinLowEdge(1),p->GetYaxis()->GetBinLowEdge(1+p->GetNbinsY()));
    TH2F* mout = new TH2F("mi","minus",binsaftertrashing,0,binsaftertrashing,mi->GetNbinsY(),mi->GetYaxis()->GetBinLowEdge(1),mi->GetYaxis()->GetBinLowEdge(1+mi->GetNbinsY()));
    for (int b = 1 ; b <= p->GetNbinsX() ; ++b) {
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        if (goesto_v3(b)<0) continue;
        int bbout = cout->GetBin(goesto_v3(b),1+m);
        int bbin = p->GetBin(b,1+m);
        pout->SetBinContent(bbout,p->GetBinContent(bbin));
        mout->SetBinContent(bbout,mi->GetBinContent(bbin));
      }
    }
    out = new TFile(Form("%s_trash_systematics_sig%d.root",source.Data(),counter),"recreate");
    pout->SetName("plus");
    out->WriteTObject(pout);
    mout->SetName("minus");
    out->WriteTObject(mout);
    out->Close();
  }

  for (int counter = 12 ; counter <= 14 ; ++counter) {
    TH2F* p;
    TH2F* mi;
    ing = new TFile(Form("%s_systematics_sig%d.root",source.Data(),counter),"read");
    ing->GetObject("plus",p);
    ing->GetObject("minus",mi);
    mi->Scale(1./mi->GetSum());
    p->Scale(1./p->GetSum());
    TH2F* pout = new TH2F("pl","plus",binsaftertrashing,0,binsaftertrashing,p->GetNbinsY(),p->GetYaxis()->GetBinLowEdge(1),p->GetYaxis()->GetBinLowEdge(1+p->GetNbinsY()));
    TH2F* mout = new TH2F("mi","minus",binsaftertrashing,0,binsaftertrashing,mi->GetNbinsY(),mi->GetYaxis()->GetBinLowEdge(1),mi->GetYaxis()->GetBinLowEdge(1+mi->GetNbinsY()));
    for (int b = 1 ; b <= p->GetNbinsX() ; ++b) {
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        if (goesto_v3(b)<0) continue;
        int bbout = cout->GetBin(goesto_v3(b),1+m);
        int bbin = p->GetBin(b,1+m);
        pout->SetBinContent(bbout,p->GetBinContent(bbin));
        mout->SetBinContent(bbout,mi->GetBinContent(bbin));
      }
    }
    out = new TFile(Form("%s_trash_systematics_sig%d.root",source.Data(),counter),"recreate");
    pout->SetName("plus");
    pout->Scale(1./pout->GetSum());
    pout->Scale(p->GetSum());
    out->WriteTObject(pout);
    mout->SetName("minus");
    mout->Scale(1./mout->GetSum());
    mout->Scale(mi->GetSum());
    out->WriteTObject(mout);
    out->Close();
  }


}



/**
* @brief convert background histograms to trashed background histograms
*
* @param source
*/
void convertbackground(TString source = TString("CONF_MC11")) {
  limit_interface* li = new limit_interface();
  TString ins = "";
  TFile* ing = new TFile(Form("%s.root",source.Data()),"read");
  TH2D* central_g;
  TH2D* p;
  TH2D* mi;
  ing->GetObject("expected",central_g);
  ing->GetObject("expected_plus",p);
  ing->GetObject("expected_minus",mi);

  TH2F* cout = new TH2F("cent","central",25,0,25,central_g->GetNbinsY(),central_g->GetYaxis()->GetBinLowEdge(1),central_g->GetYaxis()->GetBinLowEdge(1+central_g->GetNbinsY()));
  TH2F* pout = new TH2F("plus","plus",25,0,25,central_g->GetNbinsY(),central_g->GetYaxis()->GetBinLowEdge(1),central_g->GetYaxis()->GetBinLowEdge(1+central_g->GetNbinsY()));
  TH2F* mout = new TH2F("minu","minus",25,0,25,central_g->GetNbinsY(),central_g->GetYaxis()->GetBinLowEdge(1),central_g->GetYaxis()->GetBinLowEdge(1+central_g->GetNbinsY()));
  for (int b = 1 ; b <= central_g->GetNbinsX() ; ++b) {
    for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
      if (goesto_v3(b)<0) continue;
      int bbout = cout->GetBin(goesto_v3(b),1+m);
      int bbin = central_g->GetBin(b,1+m);
      cout->SetBinContent(bbout,central_g->GetBinContent(bbin));
      pout->SetBinContent(bbout,p->GetBinContent(bbin));
      mout->SetBinContent(bbout,mi->GetBinContent(bbin));
    }
  }

  TFile* out = new TFile(Form("%s_trash.root",source.Data()),"recreate");
  cout->SetName("expected");
  mout->SetName("expected_minus");
  pout->SetName("expected_plus");
  out->WriteTObject(cout);
  out->WriteTObject(pout);
  out->WriteTObject(mout);
  out->Close();

  for (int counter = 1 ; counter<=36 ; ++counter) {
//    if (0==counter||5==counter) continue;
    //TH2D* p;
    //TH2D* mi;
    ing = new TFile(Form("%s_sys%d.root",source.Data(),counter),"read");
    ing->GetObject("expected_plus",p);
    ing->GetObject("expected_minus",mi);
    TH2F* pout = new TH2F("pl","plus",25,0,25,p->GetNbinsY(),p->GetYaxis()->GetBinLowEdge(1),p->GetYaxis()->GetBinLowEdge(1+p->GetNbinsY()));
    TH2F* mout = new TH2F("mi","minus",25,0,25,mi->GetNbinsY(),mi->GetYaxis()->GetBinLowEdge(1),mi->GetYaxis()->GetBinLowEdge(1+mi->GetNbinsY()));
    for (int b = 1 ; b <= p->GetNbinsX() ; ++b) {
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        if (goesto_v3(b)<0) continue;
        int bbout = cout->GetBin(goesto_v3(b),1+m);
        int bbin = p->GetBin(b,1+m);
        pout->SetBinContent(bbout,p->GetBinContent(bbin));
        mout->SetBinContent(bbout,mi->GetBinContent(bbin));
      }
    }
    out = new TFile(Form("%s_trash_sys%d.root",source.Data(),counter),"recreate");
    pout->SetName("expected_plus");
    out->WriteTObject(pout);
    mout->SetName("expected_minus");
    out->WriteTObject(mout);
    out->Close();
  }
}


void pmumusys(TString ins = "CONF") {

  limit_interface* li = new limit_interface();
  TFile* ing = new TFile(Form("%s_sigPDF.root",ins.Data()),"read");
  TH1* central_g;
  TH1* up_g;
  TH1* down_g;
  ing->GetObject("central",central_g);
  ing->GetObject("central_plus",up_g);
  ing->GetObject("central_minus",down_g);

  int counter = 0;

  for (unsigned g = 0 ; g < li->the_geobins() ; ++g) {
    TH2* c_up = (TH2*)central_g->Clone("plus");
    TH2* c_down = (TH2*)central_g->Clone("minus");
    for (unsigned p = 0 ; p < li->the_pidbins() ; ++p) {
      int kk = li->GetGlobalMVAbin(g,p);
      for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
        c_up->SetBinContent(c_up->GetBin(1+kk,1+m),up_g->GetBinContent(c_up->GetBin(1+kk,1+m)));
        c_down->SetBinContent(c_down->GetBin(1+kk,1+m),down_g->GetBinContent(c_down->GetBin(1+kk,1+m)));
      }
    }
    TFile* out = new TFile(Form("%s_systematics_sig%d.root",ins.Data(),counter++),"recreate");
    out->WriteTObject(c_up);
    out->WriteTObject(c_down);
    out->Close();
  }
}

void pmumumasssys(TString ins = "tau2pmumuOS") {
  TFile* im = new TFile(Form("%s_mean.root",ins.Data()),"update");
  TFile* is1 = new TFile(Form("%s_sigma1.root",ins.Data()),"update");
  TFile* is2 = new TFile(Form("%s_sigma2.root",ins.Data()),"update");

  TH2F* c;
  TH2F* p;
  TH2F* m;
  im->GetObject("central",c);
  im->GetObject("plus",p);
  im->GetObject("minus",m);

  p->Scale(1./c->GetSum());
  m->Scale(1./c->GetSum());
  c->Scale(1./c->GetSum());
  im->WriteTObject(p);
  im->WriteTObject(c);
  im->WriteTObject(m);
  im->Close();

  is1->GetObject("central",c);
  is1->GetObject("plus",p);
  is1->GetObject("minus",m);

  p->Scale(1./c->GetSum());
  m->Scale(1./c->GetSum());
  c->Scale(1./c->GetSum());
  is1->WriteTObject(p);
  is1->WriteTObject(c);
  is1->WriteTObject(m);
  is1->Close();

  is2->GetObject("central",c);
  is2->GetObject("plus",p);
  is2->GetObject("minus",m);

  p->Scale(1./c->GetSum());
  m->Scale(1./c->GetSum());
  c->Scale(1./c->GetSum());
  is2->WriteTObject(p);
  is2->WriteTObject(c);
  is2->WriteTObject(m);
  is2->Close();

}

void convertpmumumasssys(TString ins = "tau2pmumuOS") {
  TFile* im = new TFile(Form("%s_mean.root",ins.Data()),"read");
  TFile* is1 = new TFile(Form("%s_sigma1.root",ins.Data()),"read");
  TFile* is2 = new TFile(Form("%s_sigma2.root",ins.Data()),"read");

  TH2F* central;
  TH2F* p;
  TH2F* min;
  im->GetObject("central",central);
  im->GetObject("plus",p);
  im->GetObject("minus",min);


  TH2F* pcout = new TH2F("pl","pl",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  TH2F* mcout = new TH2F("mi","mi",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  for (unsigned int b = 2 ; b <= central->GetNbinsX() ; ++b) {
    for (int m = 1 ; m <= central->GetNbinsY() ; ++m) {
      int bbin = central->GetBin(b,m);
      int bbout = pcout->GetBin(b-1,m);
      pcout->SetBinContent(bbout,p->GetBinContent(bbin));
      mcout->SetBinContent(bbout,min->GetBinContent(bbin));
    }
  }
  pcout->Scale(p->GetSum()/pcout->GetSum());
  mcout->Scale(min->GetSum()/mcout->GetSum());
  TFile* out = new TFile(Form("%s_trash_mean.root",ins.Data()),"recreate");
  pcout->SetName("plus");
  mcout->SetName("minus");
  out->WriteTObject(mcout);
  out->WriteTObject(pcout);
  out->Close();




  is1->GetObject("central",central);
  is1->GetObject("plus",p);
  is1->GetObject("minus",min);

  pcout = new TH2F("pl","pl",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  mcout = new TH2F("mi","mi",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  for (unsigned int b = 2 ; b <= central->GetNbinsX() ; ++b) {
    for (int m = 1 ; m <= central->GetNbinsY() ; ++m) {
      int bbin = central->GetBin(b,m);
      int bbout = pcout->GetBin(b-1,m);
      pcout->SetBinContent(bbout,p->GetBinContent(bbin));
      mcout->SetBinContent(bbout,min->GetBinContent(bbin));
    }
  }
  pcout->Scale(p->GetSum()/pcout->GetSum());
  mcout->Scale(min->GetSum()/mcout->GetSum());
  out = new TFile(Form("%s_trash_sigma1.root",ins.Data()),"recreate");
  pcout->SetName("plus");
  mcout->SetName("minus");
  out->WriteTObject(mcout);
  out->WriteTObject(pcout);
  out->Close();


  is2->GetObject("central",central);
  is2->GetObject("plus",p);
  is2->GetObject("minus",min);

  pcout = new TH2F("pl","pl",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  mcout = new TH2F("mi","mi",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  for (unsigned int b = 2 ; b <= central->GetNbinsX() ; ++b) {
    for (int m = 1 ; m <= central->GetNbinsY() ; ++m) {
      int bbin = central->GetBin(b,m);
      int bbout = pcout->GetBin(b-1,m);
      pcout->SetBinContent(bbout,p->GetBinContent(bbin));
      mcout->SetBinContent(bbout,min->GetBinContent(bbin));
    }
  }
  pcout->Scale(p->GetSum()/pcout->GetSum());
  mcout->Scale(min->GetSum()/mcout->GetSum());
  out = new TFile(Form("%s_trash_sigma2.root",ins.Data()),"recreate");
  pcout->SetName("plus");
  mcout->SetName("minus");
  out->WriteTObject(mcout);
  out->WriteTObject(pcout);
  out->Close();



}

void convertpmumu(TString ins = "tau2pmumuOS") {
  TFile* ing = new TFile(Form("%s_sigPDF.root",ins.Data()),"read");
  TH2F* central;
  ing->GetObject("central",central);
  central->Scale(1./central->GetSum());

  TH2F* ccout = new TH2F("cent","central",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  for (unsigned int b = 2 ; b <= central->GetNbinsX() ; ++b) {
    for (int m = 1 ; m <= central->GetNbinsY() ; ++m) {
      int bbin = central->GetBin(b,m);
      int bbout = ccout->GetBin(b-1,m);
      ccout->SetBinContent(bbout,central->GetBinContent(bbin));
    }
  }
  TFile* out = new TFile(Form("%s_trash_sigPDF.root",ins.Data()),"recreate");
  ccout->SetName("central");
  out->WriteTObject(ccout);
  out->Close();

  for (int counter = 0 ; counter <= 4 ; ++counter) {
    TH2F* p;
    TH2F* mi;
    ing = new TFile(Form("%s_systematics_sig%d.root",ins.Data(),counter),"read");
    ing->GetObject("plus",p);
    ing->GetObject("minus",mi);
    mi->Scale(1./mi->GetSum());
    p->Scale(1./p->GetSum());
    TH2F* mout = new TH2F("mi","minus",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
    TH2F* pout = new TH2F("pl","plus",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));

    for (unsigned int b = 2 ; b <= central->GetNbinsX() ; ++b) {
      for (int m = 1 ; m <= central->GetNbinsY() ; ++m) {
        int bbin = central->GetBin(b,m);  
        int bbout = ccout->GetBin(b-1,m);  
        pout->SetBinContent(bbout,p->GetBinContent(bbin));
        mout->SetBinContent(bbout,mi->GetBinContent(bbin));
        std::cout << Form("%f",(mi->GetBinContent(bbin))) <<std::endl;
      }                                   
    }                                     

    out = new TFile(Form("%s_trash_systematics_sig%d.root",ins.Data(),counter),"recreate");
    pout->SetName("plus");
    out->WriteTObject(pout);
    mout->SetName("minus");
    out->WriteTObject(mout);
    out->Close();

  }
}


void convertobserved(TString source = TString("CONF_MC11")) {
  limit_interface* li = new limit_interface();
  TString ins = "";
  TFile* ing = new TFile(Form("%s_observed.root",source.Data()),"read");
  TH2F* central_g;
  ing->GetObject("observed",central_g);

  TH2F* cout = new TH2F("cent","central",25,0,25,central_g->GetNbinsY(),central_g->GetYaxis()->GetBinLowEdge(1),central_g->GetYaxis()->GetBinLowEdge(1+central_g->GetNbinsY()));
  for (int b = 1 ; b <= central_g->GetNbinsX() ; ++b) {
    for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
      if (goesto_v3(b)<0) continue;
      int bbout = cout->GetBin(goesto_v3(b),1+m);
      int bbin = central_g->GetBin(b,1+m);
      cout->SetBinContent(bbout,central_g->GetBinContent(bbin));
    }
  }

  TFile* out = new TFile(Form("%s_trash_observed.root",source.Data()),"recreate");
  cout->SetName("observed");
  out->WriteTObject(cout);
  out->Close();

}
void convertobservedpmumu(TString source = TString("tau2pmumuOS")) {
  limit_interface* li = new limit_interface();
  TString ins = "";
  TFile* ing = new TFile(Form("%s_observed.root",source.Data()),"read");
  TH2F* central_g;
  ing->GetObject("observed",central_g);

  TH2F* ccout = new TH2F("cent","central",4,0,4,central_g->GetNbinsY(),central_g->GetYaxis()->GetBinLowEdge(1),central_g->GetYaxis()->GetBinLowEdge(1+central_g->GetNbinsY()));
  for (int b = 1 ; b <= central_g->GetNbinsX() ; ++b) {
    for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
      int bbin = central_g->GetBin(b,m+1);  
      int bbout = ccout->GetBin(b-1,m+1);  
      ccout->SetBinContent(bbout,central_g->GetBinContent(bbin));
    }
  }

  TFile* out = new TFile(Form("%s_trash_observed.root",source.Data()),"recreate");
  ccout->SetName("observed");
  out->WriteTObject(ccout);
  out->Close();

}





void convertpmumumasssigma2(TString ins = "tau2pmumuOS") {
  TFile* is2 = new TFile(Form("%s_sigma2.root",ins.Data()),"read");

  TH2F* central;
  TH2F* p;
  TH2F* min;


  is2->GetObject("central",central);
  is2->GetObject("plus",p);
  is2->GetObject("minus",min);

  TH2F* pcout = new TH2F("pl","pl",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  TH2F* mcout = new TH2F("mi","mi",central->GetNbinsX()-1,0,central->GetNbinsX()-1,central->GetNbinsY(),central->GetYaxis()->GetBinLowEdge(1),central->GetYaxis()->GetBinLowEdge(1+central->GetNbinsY()));
  for (unsigned int b = 2 ; b <= central->GetNbinsX() ; ++b) {
    for (int m = 1 ; m <= central->GetNbinsY() ; ++m) {
      int bbin = central->GetBin(b,m);
      int bbout = pcout->GetBin(b-1,m);
      pcout->SetBinContent(bbout,p->GetBinContent(bbin));
      mcout->SetBinContent(bbout,min->GetBinContent(bbin));
    }
  }
  pcout->Scale(p->GetSum()/pcout->GetSum());
  mcout->Scale(min->GetSum()/mcout->GetSum());
  TFile* out = new TFile(Form("%s_trash_sigma2.root",ins.Data()),"recreate");
  pcout->SetName("plus");
  mcout->SetName("minus");
  out->WriteTObject(mcout);
  out->WriteTObject(pcout);
  out->Close();



}
