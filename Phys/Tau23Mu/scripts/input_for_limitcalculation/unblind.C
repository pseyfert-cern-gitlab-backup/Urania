/**
* @file unblind.C
* @brief make histogram with the unblinded number of observed events. code to be run  in CINT
* @author Paul Seyfert
* @date 2012-09-20
*/


/**
* @brief get histograms for the unblinded = observed result
*
* @param additional additional cuts, like eta veto
*/
void unblind2012(TString additional("(min(mass_p0p2,mass_p1p2)>450")) {
 TChain* Tau23Mu = new TChain("Tau23Mu");
 Tau23Mu->Add("/auto/data/pseyfert/Krakow/unblinded/2021UP");
 Tau23Mu->Add("/auto/data/pseyfert/Krakow/unblinded/2021DOWN");


 gSystem->Load("../../params2012/libLimitROOT.so");

 limit_interface* li = new limit_interface();
 li->setGeoRefString(li->getGeoRefString()+"&&"+additional.Data());


 //loop over GeoMVA bins
 for (int g = 0 ; g < li->GetNGeobins() ; ++g) {
   
   // loop over PID bins
   for (int p = 0 ; p < li->GetNPIDbins() ; ++p) {
   
     // get bin boarders
     float lowG = li->GetGeolow(g);
     float highG = li->GetGeohigh(g);
     float lowP = li->GetPIDlow(p);
     float highP = li->GetPIDhigh(p);
     
     for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
       float lowm = li->GetMasslow(m);
       float highm = li->GetMasshigh(m);
       // here your fits determine these three:
       int evts = Tau23Mu->Draw("mass",li->CutString2012()+Form("&&%s>%f&&%s<%f&&%s>%f&&%s<%f&&mass>%f&&mass<%f",li->the_geo().Data(),lowG,li->the_geo().Data(),highG,li->the_pid().Data(),lowP,li->the_pid().Data(),highP,lowm,highm));
       float expectedBKG = (float)(int)evts;
     
       li->SetPrivate(g,p,(lowm+highm)*.5,expectedBKG,expectedBKG,expectedBKG);
     } // end mass loop
     
   } // end pid loop
 } // end geo loop
 
 TFile* f = new TFile("/tmp/unblindedinterface2012.root","recreate");
 f->WriteTObject(li->GetFilledHistogram("observed"));
 f->WriteTObject(li->GetFilledHistogram_PLUS("observed2"));
 f->WriteTObject(li->GetFilledHistogram_MINUS("observed3"));
 f->Close();
}

void unblind2011(TString additional("(min(mass_p0p2,mass_p1p2)>450")) {
 TChain* Tau23Mu = new TChain("Tau23Mu");
 Tau23Mu->Add("/auto/data/pseyfert/Krakow/unblinded/2011UP");
 Tau23Mu->Add("/auto/data/pseyfert/Krakow/unblinded/2011DOWN");


 gSystem->Load("../../params2011/libLimitROOT.so");

 limit_interface* li = new limit_interface();
 li->setGeoRefString(li->getGeoRefString()+"&&"+additional.Data());


 //loop over GeoMVA bins
 for (int g = 0 ; g < li->GetNGeobins() ; ++g) {
   
   // loop over PID bins
   for (int p = 0 ; p < li->GetNPIDbins() ; ++p) {
   
     // get bin boarders
     float lowG = li->GetGeolow(g);
     float highG = li->GetGeohigh(g);
     float lowP = li->GetPIDlow(p);
     float highP = li->GetPIDhigh(p);
     
     for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
       float lowm = li->GetMasslow(m);
       float highm = li->GetMasshigh(m);
       // here your fits determine these three:
       int evts = Tau23Mu->Draw("mass",li->CutString2011()+Form("&&%s>%f&&%s<%f&&%s>%f&&%s<%f&&mass>%f&&mass<%f",li->the_geo().Data(),lowG,li->the_geo().Data(),highG,li->the_pid().Data(),lowP,li->the_pid().Data(),highP,lowm,highm));
       float expectedBKG = (float)(int)evts;
     
       li->SetPrivate(g,p,(lowm+highm)*.5,expectedBKG,expectedBKG,expectedBKG);
     } // end mass loop
     
   } // end pid loop
 } // end geo loop
 
 TFile* f = new TFile("/tmp/unblindedinterface2011.root","recreate");
 f->WriteTObject(li->GetFilledHistogram("observed"));
 f->WriteTObject(li->GetFilledHistogram_PLUS("observed2"));
 f->WriteTObject(li->GetFilledHistogram_MINUS("observed3"));
 f->Close();
}

void unblindpmumu(TString mode("OS")) {
 TChain* Tau = new TChain(Form("tau2pmumu%s/tau2pmumu%s",mode.Data(),mode.Data()));
 Tau->Add(Form("/afs/cern.ch/work/j/jrharris/public/Tau2PMuMu/stp17unblinded_Tau2PMuMu%s_full.root",mode.Data()));


 gSystem->Load("./libLimitROOT.so");

 limit_interface* li = new limit_interface();


 //loop over GeoMVA bins
 for (int g = 0 ; g < li->GetNGeobins() ; ++g) {

   // get bin boarders
   float lowG = li->GetGeolow(g);
   float highG = li->GetGeohigh(g);

   for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
     int p = 0;
     float lowm = li->GetMasslow(m);
     float highm = li->GetMasshigh(m);
     // here your fits determine these three:
     int evts = Tau->Draw("mass",Form("GeoMVA>%f&&GeoMVA<%f&&mass>%f&&mass<%f",lowG,highG,lowm,highm));
     float expectedBKG = (float)(int)evts;

     li->SetPrivate(g,p,(lowm+highm)*.5,expectedBKG,expectedBKG,expectedBKG);
   } // end mass loop

 } // end geo loop
 
 TFile* f = new TFile("/tmp/unblindedinterface.root","recreate");
 f->WriteTObject(li->GetFilledHistogram("observed"));
 f->WriteTObject(li->GetFilledHistogram_PLUS("observed2"));
 f->WriteTObject(li->GetFilledHistogram_MINUS("observed3"));
 f->Close();
}
