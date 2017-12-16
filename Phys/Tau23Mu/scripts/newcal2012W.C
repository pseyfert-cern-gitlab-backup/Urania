
void newcal2012W(int c) {
  gROOT->ProcessLine("gSystem->Load(\"../params/libLimitROOT.so\")");
  gROOT->ProcessLine(".L newcal.C");
  newcal(c);
}

