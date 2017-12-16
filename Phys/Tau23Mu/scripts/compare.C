
TString selection = "triggered*(abs(particleid)==truetau)";
//TString selectionblue = "triggered*(abs(particleid)==truetau)";
//TString selectionred = "triggered*(abs(particleid)==truetau)";
TString selectionred = "L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&mass_p0p1>250&&(mass_p0p1)>250";//&&abs(particleid)==truetau && abs(mass_p1p2-1020) <15";
TString selectionblue = "(L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&(mass_p0p1)>250)";//&&abs(particleid)==truetau)";
//TString selectionblue = "(L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&mass_p0p1>250)*(abs(mass-1980)<30 - (abs(mass-1980)>150 && abs(mass-1980)<180))*(p1_PIDmupi>8&&p2_PIDmupi>8&&p1_PIDmuk>15&&p2_PIDmuk>15 && abs(mass_p1p2-1020)<15)";


compare(TTree* red, TTree* blue) {
  red->SetLineColor(2);
  int rot = red->Draw("mass",selectionblue);
  int blau = blue->Draw("mass",selectionblue);
  TString norm = Form("%d./%d.",rot,blau);
  std::cout << norm << std::endl;
  float rot2 = red->Draw("mass",selectionblue);
  float blau2 = blue->Draw("mass","("+selectionblue+")*"+norm);
  std::cout << rot2 << "\t" << blau2 << std::endl;
  std::cout << ("("+selectionblue+")*"+norm) << std::endl;
  for (int i = 0 ; i < blue->GetListOfBranches()->GetSize() ; ++i) {
    
    TCanvas* c = new TCanvas();
    c->cd();
    printf("%s",blue->GetListOfBranches()->At(i)->GetName());
    red->Draw(blue->GetListOfBranches()->At(i)->GetName(),selectionblue);
    blue->Draw(blue->GetListOfBranches()->At(i)->GetName(),"("+selectionblue+")*"+norm,"same");
    c->Print(Form("/tmp/buff/%02d.eps",i));
    delete c;
  }

}

std::vector<std::string> vars() {
  std::vector<std::string> ret;
  ret.push_back("DOCAone");
  ret.push_back("DOCAtwo");
  ret.push_back("DOCAthree");
  ret.push_back("iso");
  ret.push_back("CDF3");


  ret.push_back("TMath::Exp(-1000*LifeTime)");
  ret.push_back("IPSig");
  ret.push_back("VertexChi2");
  ret.push_back("acos(dira)");
  ret.push_back("pt");
  ret.push_back("min(p0_IPSig,min(p1_IPSig,p2_IPSig))");

  ret.push_back("ptorderedp0_pt");
  ret.push_back("ptorderedp1_pt");
  ret.push_back("ptorderedp2_pt");

  return ret;
}

comparetwothings(TTree* red, TTree* blue) {
  int rot = red->Draw("mass",selectionred);
  int blau = blue->Draw("mass",selectionblue);
  TString norm = Form("%d./%d.",rot,blau);
  std::cout << norm << std::endl;
  //float rot2 = red->Draw("mass",selection);
  //float blau2 = blue->Draw("mass","("+selection+")*"+norm);
  //std::cout << rot2 << "\t" << blau2 << std::endl;
  //std::cout << ("("+selection+")*"+norm) << std::endl;
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  for (int i = 0 ; i < blue->GetListOfBranches()->GetSize() ; ++i) {
    red->SetLineColor(2);
    TString br = "GeoMVA";    
    TCanvas* c = new TCanvas();
    c->cd();
    printf("%s\n",blue->GetListOfBranches()->At(i)->GetName());
    red->Draw(blue->GetListOfBranches()->At(i)->GetName(),selectionred);
//    htemp->SetTitle(blue->GetListOfBranches()->At(i)->GetName());
    //red->Draw(br,selectionred);
    blue->SetLineColor(4);
    blue->Draw(blue->GetListOfBranches()->At(i)->GetName(),"("+selectionblue+")*"+norm,"same");
//    if (i==21) break;
    //blue->Draw(br,"("+selectionblue+")*"+norm,"same");
    c->Print(Form("/tmp/%02d.eps",i));
    delete c;
  }

}

comparetwothingsret(TTree* red, TTree* blue) {
  int rot = red->Draw("mass",selectionred);
  int blau = blue->Draw("mass",selectionblue);
  TString norm = Form("%d./%d.",rot,blau);
  std::cout << norm << std::endl;
  //float rot2 = red->Draw("mass",selection);
  //float blau2 = blue->Draw("mass","("+selection+")*"+norm);
  //std::cout << rot2 << "\t" << blau2 << std::endl;
  //std::cout << ("("+selection+")*"+norm) << std::endl;
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  std::vector<std::string> ret = vars();
  for (int i = 0 ; i < ret.size() ; ++i) {
    red->SetLineColor(2);
    TString br = "GeoMVA";    
    TCanvas* c = new TCanvas();
    c->cd();
    printf("%s\n",ret[i].c_str());
    red->Draw(ret[i].c_str(),selectionred);
//    htemp->SetTitle(blue->GetListOfBranches()->At(i)->GetName());
    //red->Draw(br,selectionred);
    blue->SetLineColor(4);
    blue->Draw(ret[i].c_str(),"("+selectionblue+")*"+norm,"same");
//    if (i==21) break;
    //blue->Draw(br,"("+selectionblue+")*"+norm,"same");
    TFile* ff = new TFile(Form("/tmp/%02d.root",i),"recreate");
    ff->WriteTObject(c);
    c->Print(Form("/tmp/%02d.eps",i));
    ff->Close();
    delete c;
  }

  TH1F* tauhist = new TH1F("taudaughterpt","taudaughterpt",150,0,15000);
  TH1F* dshist = new TH1F("dsdaughterpt","dsdaughterpt",150,0,15000);

  for (int i = 0 ; i < 3 ; ++i) {
    TH1F* thistau = (TH1F*)tauhist->Clone(Form("tau%d",i));
    TH1F* thisds = (TH1F*)dshist->Clone(Form("ds%d",i));
    blue->Draw(Form("ptorderedp%d_pt>>tau%d",i,i),"("+selectionblue+")*"+norm);
    red->Draw( Form("ptorderedp%d_pt>>ds%d",i,i),"("+selectionred+")");
    tauhist->Add(thistau);
    dshist->Add(thisds);
  }
  tauhist->Scale(1./tauhist->GetSum());
  dshist->Scale(1./dshist->GetSum());
  tauhist->SetLineColor(kBlue);
  dshist->SetLineColor(kRed);
  TCanvas* c = new TCanvas();
  tauhist->Draw();
  dshist->Draw("same");
  TFile* ff = new TFile("/tmp/summed.root","recreate");
  ff->WriteTObject(c);
  c->Print("/tmp/summ.eps");
  ff->Close();
}
