#include "TFile.h"
#include "TH1F.h"

void CountDsstar(){
 
  chain = new TFile("../src/histosPhotonReco_MC.root");

  TH1F *h1 = (TH1F*) chain->Get("DsMuMassWithFirstG04");
  TH1F *h2 = (TH1F*) chain->Get("DsMuMass04");  

  //norm1 = h1->Integral(70,200);
  //norm2 = h2->Integral(70,200);
  norm1 = h1->Integral(0,40);
  norm2 = h2->Integral(0,40);
  std::cout << "Norm1 = " << norm1 << std::endl;
  std::cout << "Norm2 = " << norm2 << std::endl;

  double ratio = -1*norm1/norm2;
  TH1F *total = (TH1F*)h1->Clone("total"); 
  total->Add(h2,ratio);

  double yield = total->Integral(39,56);
  std::cout << "The yield is = " << yield << std::endl;

  TCanvas *canvas = new TCanvas("c","c",0,0,800,600);
  total->Draw();
  canvas->SaveAs("CountLast_MC_First040.pdf");

  TCanvas *canvas2 = new TCanvas("c2","c2",0,0,800,600);
  h1->Draw();
  h2->Scale(-1*ratio);
  h2->SetLineColor(2);
  h2->Draw("same");
  canvas2->SaveAs("ScaleLast.pdf");
}


