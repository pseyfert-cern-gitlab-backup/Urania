#include<vector>
#include<TH2F.h>
#include<TFile.h>
#include<../../params/limit_interface.h>

TH2F* strip(TH2F* longhist) {
  limit_interface* li = new limit_interface();
  TH2F* output = new TH2F("etapdf_data","signal pdf 2012",li->the_geobins(),0,li->the_geobins(),li->the_pidbins(),0,li->the_pidbins());
  int mmax = li->GetNMassbins();
  for (unsigned g = 0 ; g < li->the_geobins() ; ++g) {
    for (unsigned p = 0 ; p < li->the_pidbins() ; ++p) {
      int glob = li->GetGlobalMVAbin(g,p);
      float binconts = 0.;
      for (unsigned m = 0 ; m < mmax ; ++m) {
        binconts += longhist->GetBinContent(longhist->GetBin(1+glob,1+m));
      }
      output->SetBinContent(output->GetBin(1+g,1+p),binconts);
    }
  }
  output->Scale(1./output->GetSum());
  output->GetXaxis()->SetTitle("M_{3body} bin");
  output->GetYaxis()->SetTitle("ProbNNmu bin");
  return output;
}

TH2F* constrain(TH2F* longhist) {
  TH2F* out = strip(longhist);
  for (unsigned x = 1 ; x <= out->GetNbinsX() ; ++x) {
    for (unsigned y = 1 ; y <= out->GetNbinsY() ; ++y) {
      if (out->GetBinContent(out->GetBin(x,y)) < 0.) {
          out->SetBinContent(out->GetBin(x,y),0.);
      }
    }
  }
  out->Scale(1./out->GetSum());
  return out;
}

TH1D* bloop() {
  TFile* ff = new TFile("../params/ProbNNmu/v4_with450Veto_sigPDF.root","read");
  TH1D* c;
  TH2F* buffer;
  ff->GetObject("central",buffer);
  c= (TH1D*)constrain(buffer)->ProjectionY();
  TH2F* sys[12];
  TH1D* sys1[12];
  int u;
  for ( u = 0; u <= 11 ; ++u) {
    TFile* ff = new TFile(Form("../params/ProbNNmu/v4_with450Veto_systematics_sig%d.root",u),"read");
    ff->GetObject("plus",sys[u]);
    sys[u]=constrain(sys[u]);
    sys1[u]=sys[u]->ProjectionY(Form("sysfor%d",u));
  }
  for (int b = 1 ; b <= c->GetNbinsX() ; ++b) {
    c->SetBinError(b,0.);
  }
  for (int b = 1 ; b <= c->GetNbinsX() ; ++b) {
    for ( u = 0 ; u <= 11 ; ++u) {
      float diff = (sys1[u]->GetBinContent(b)-c->GetBinContent(b));
      std::cout << "central = " << c->GetBinContent(b) << "\tplus = " << sys1[u]->GetBinContent(b) << "\t\tdiff = " << diff << std::endl;
      c->SetBinError(b,sqrt((sys1[u]->GetBinContent(b)-c->GetBinContent(b))*(sys1[u]->GetBinContent(b)-c->GetBinContent(b))/9.+c->GetBinError(b)*c->GetBinError(b)));
    }
  }
  return c;
}

void update() {
  limit_interface* li = new limit_interface();
  TFile* upd = new TFile("data.root","update");
  TH2F* central ;
  upd->GetObject("etapdf_data",central);
  std::vector<TH2F*> hists;
  for (int i = 0 ; i < 9 ; ++i) {
    TFile* here_f = new TFile(Form("data%d.root",i),"read");
    TH2F* here_h;
    here_f->GetObject("etapdf_data",here_h);
    hists.push_back(here_h);
  }
  for (unsigned g = 0 ; g < li->the_geobins() ; ++g) {
    for (unsigned p = 0 ; p < li->the_pidbins() ; ++p) {
      float devhere = 0;
      int binnum = central->GetBin(g+1,p+1);
      for (unsigned h = 0 ; h < hists.size() ; ++h) {
        float dev = central->GetBinContent(binnum) - hists[h]->GetBinContent(binnum);
        dev = dev/3.;
        devhere+= dev*dev;
      }
      devhere = sqrt(devhere);
      central->SetBinError(binnum,devhere);
    }
  }
  upd->WriteTObject(central);
  upd->Close();
}
