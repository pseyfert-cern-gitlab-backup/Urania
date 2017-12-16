createCalibTrees(TTree* input) {
  limit_interface* li = new limit_interface();
  for (unsigned int g = 0 ; g < li->the_geobins() ; ++g) {
    TString ref = li->getGeoRefString();
    ref += "&&";
    ref += li->the_geo() + ">" + Form("%f",li->the_geobinning()[g]);
    ref += "&&";
    ref += li->the_geo() + "<" + Form("%f",li->the_geobinning()[1+g]);
    TTree* kopie = input->CopyTree(ref.Data());
    int lo = fabs(100*li->the_geobinning()[g]);
    int hi = fabs(100*li->the_geobinning()[g+1]);
    TString name = "";
    if (li->the_geobinning()[g]<0.) {
      name += "m";
    }
    name += Form("%03d",lo);
    name += "to";
    if (li->the_geobinning()[g+1]<0.) {
      name += "m";
    }
    name += Form("%03d",hi);
    name += ".root";
    TFile* ff = new TFile(name.Data(),"recreate");
    ff->WriteTObject(kopie);
    ff->Close();
  }
}
