
void newcal2011W(int c) {
  gROOT->ProcessLine("gSystem->Load(\"../params/libLimitROOT.so\")");
  gROOT->ProcessLine(".L newcal2011.C");
  newcal2011(c);
}

