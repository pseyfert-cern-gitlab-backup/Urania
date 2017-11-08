void DumpYields() {

  TFile *DsMu = new TFile("DsMu.root","READ");
  int nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  int ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 

  cout<<" DsMu :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  TFile *DsTau = new TFile("DsTau.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" DsTau :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  cout<<" *********************** "<<endl;
  TFile *DstMu = new TFile("DstMu.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" DstMu :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  TFile *DstTau = new TFile("DstTau.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" DstTau :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  cout<<" *********************** "<<endl;
  TFile *Ds0StMu = new TFile("Ds0StMu.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" Ds0StMu :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  TFile *Ds0StTau = new TFile("Ds0StTau.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" Ds0StTau :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  cout<<" *********************** "<<endl;
  TFile *Ds1Mu = new TFile("Ds1Mu.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" Ds1Mu :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  /*
  TFile *Ds1Tau = new TFile("Ds1Tau.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" Ds1Tau :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;
  */
  cout<<" *********************** "<<endl;
  TFile *Ds1pMu = new TFile("Ds1pMu.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" Ds1pMu :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  TFile *Ds1pTau = new TFile("Ds1pTau.root","READ");
  nin = ((TH1D*)gDirectory->Get("histoMass"))->GetEntries(); 
  ninfit = ((TH1D*)gDirectory->Get("histoMassFit"))->GetEntries(); 
  cout<<" Ds1pTau :: "<<ninfit<<" "<<nin<<" rat:: "<<(double)ninfit/nin<<endl;

  return;
}
