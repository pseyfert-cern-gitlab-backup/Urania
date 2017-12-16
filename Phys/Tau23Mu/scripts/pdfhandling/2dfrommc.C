TH2F* mchist(TTree* baum) {
  limit_interface* li = new limit_interface();
  TString baseline("(");
  baseline += li->getGeoRefString();
  baseline += ")";
  TH2F* ret = new TH2F("etapdf_mc","etapdf_mc",li->the_geobins(),0,li->the_geobins(),li->the_pidbins(),0,li->the_pidbins());
  ret->Sumw2();
  for (unsigned p = 0 ; p < li->the_pidbins() ; ++p) {
    for (unsigned g = 0 ; g < li->the_geobins() ; ++g) {
      TString thisone = baseline + Form("*(%s>=%f&&%s<%f&&%s>=%f&&%s<%f)",li->the_geo().Data(),li->the_geobinning()[g],li->the_geo().Data(),li->the_geobinning()[g+1],li->the_pid().Data(),li->the_pidbinning()[p],li->the_pid().Data(),li->the_pidbinning()[1+p]);
      int glob = li->GetGlobalMVAbin(g,p);
      std::cout << thisone << std::endl;
      ret->SetBinContent(ret->GetBin(1+g,1+p),baum->Draw("mass",thisone));
    }
  }
  ret->Scale(1./ret->GetSum());
  ret->GetXaxis()->SetTitle("GeoMVA bin");
  ret->GetYaxis()->SetTitle("ProbNNmu bin");
  return ret;

  

}
