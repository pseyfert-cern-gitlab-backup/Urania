#include "plots.h"

//ClassImp(plots)

plots::plots():
  m_plotfile(0),
  m_stacked(0)
{
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1); 
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  
  
}

plots::plots(const std::string& plotfile):
  m_plotfile(0),
  m_stacked(0)
{
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1); 
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  m_plotfile = new TFile(plotfile.c_str(),"RECREATE");
  
}

plots::~plots()
{
  m_plotfile->Write();
  m_plotfile->Close();
  
}

bool plots::plot(const std::vector<double> & X,const std::vector<double> & Y,const std::string& name, const std::string& xname, const std::string& yname, const std::string& directory)
{
  cd(directory);
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  
  Double_t* Xc = new Double_t [X.size()];
  copy( X.begin(), X.end(), Xc);
  Double_t* Yc = new Double_t [Y.size()];
  copy( Y.begin(), Y.end(), Yc);

  TGraph* plotgraph = new TGraph(X.size(),Xc,Yc);
  if(!plotgraph) return false;
  
  plotgraph->SetLineWidth(2);
  plotgraph->Draw("AL1");
  plotgraph->SetTitle(name.c_str());
  string gname=yname+".v."+xname+"_"+name;
  plotgraph->SetName(gname.c_str());
  plotgraph->GetXaxis()->SetTitle(xname.c_str());
  plotgraph->GetYaxis()->SetTitle(yname.c_str());
  plotCanvas->Draw();
  plotgraph->Write();
  plotCanvas->Write();
  
  return true;
  
}

bool plots::plot(const std::vector<double> & X,const std::vector<double> & Y,const std::vector<double> & Xerr,const std::vector<double> & Yerr,const std::string& name, const std::string& xname, const std::string& yname, const std::string& directory)
{
  cd(directory);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  //TDirectory *plotDir = m_plotfile->mkdir(directory.c_str());
  //plotDir->cd();
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  
  Double_t* Xc = new Double_t [X.size()];
  copy( X.begin(), X.end(), Xc);
  Double_t* Yc = new Double_t [Y.size()];
  copy( Y.begin(), Y.end(), Yc);

  Double_t* XcErr = new Double_t [Xerr.size()];
  copy( Xerr.begin(), Xerr.end(), XcErr);
  Double_t* YcErr = new Double_t [Yerr.size()];
  copy( Yerr.begin(), Yerr.end(), YcErr);

  TGraphErrors* plotgraph=NULL;
  if(Xerr.size()>0 && Yerr.size()>0) plotgraph = new TGraphErrors(X.size(),Xc,Yc,XcErr,YcErr);
  else if(Xerr.size()>0) plotgraph = new TGraphErrors(X.size(),Xc,Yc,XcErr,NULL);
  else if(Yerr.size()>0) plotgraph = new TGraphErrors(X.size(),Xc,Yc,NULL,YcErr);
  
  if(!plotgraph) return false;
  plotgraph->SetLineWidth(2);
  plotgraph->Draw("AL1");
  plotgraph->SetTitle(name.c_str());
  plotgraph->GetXaxis()->SetTitle(xname.c_str());
  plotgraph->GetYaxis()->SetTitle(yname.c_str());
  string gname=yname+".v."+xname+"_"+name;
  plotgraph->SetName(gname.c_str());
  plotCanvas->Draw();
  plotgraph->Write();
  plotCanvas->Write();
  
  //for(unsigned int k=0; k<X.size(); k++) std::cout << "Plotted X " << Xc[k] << "+/-" << XcErr[k] << " Y " << Yc[k] << "+/-" << YcErr[k] << " \'size\' " << X.size() << std::endl;
  
  
  return true;
  
}

bool plots::plot(const unsigned int & arrow, const std::vector<double> & X,const std::vector<double> & Y,const std::string& name, const std::string& xname, const std::string& yname, const std::string& directory)
{
  
  cd(directory);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  
  Double_t* Xc = new Double_t [X.size()];
  copy( X.begin(), X.end(), Xc);
  Double_t* Yc = new Double_t [Y.size()];
  copy( Y.begin(), Y.end(), Yc);

  TGraph* plotgraph = new TGraph(X.size(),Xc,Yc);
  
  if(!plotgraph) return false;
  plotgraph->SetLineWidth(2);
  plotgraph->Draw("AL1");
  plotgraph->SetTitle(name.c_str());
  plotgraph->GetXaxis()->SetTitle(xname.c_str());
  plotgraph->GetYaxis()->SetTitle(yname.c_str());
  string gname=yname+".v."+xname+"_"+name;
  plotgraph->SetName(gname.c_str());
  
  if(arrow< X.size() && arrow < Y.size())
  {
    TArrow* Thisarrow = new TArrow(X[arrow],0,X[arrow],Y[arrow],0.01,"<-");
    if(!Thisarrow) return false;
    Thisarrow->SetLineWidth(2) ;
    Thisarrow->SetLineColor(kBlue);
    Thisarrow->Draw();
  }
  
  
  plotCanvas->Draw();
  plotgraph->Write();
  plotCanvas->Write();

  return true;
  
}

bool plots::plot(const unsigned int & arrow,const std::vector<double> & X,const std::vector<double> & Y,const std::vector<double> & Xerr,const std::vector<double> & Yerr,const std::string& name, const std::string& xname, const std::string& yname, const std::string& directory)
{
  
  cd(directory);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  //TDirectory *plotDir = m_plotfile->mkdir(directory.c_str());
  //plotDir->cd();
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  
  Double_t* Xc = new Double_t [X.size()];
  copy( X.begin(), X.end(), Xc);
  Double_t* Yc = new Double_t [Y.size()];
  copy( Y.begin(), Y.end(), Yc);

  Double_t* XcErr = new Double_t [Xerr.size()];
  copy( Xerr.begin(), Xerr.end(), XcErr);
  Double_t* YcErr = new Double_t [Yerr.size()];
  copy( Yerr.begin(), Yerr.end(), YcErr);

  TGraphErrors* plotgraph=NULL;
  if(Xerr.size()>0 && Yerr.size()>0) plotgraph = new TGraphErrors(X.size(),Xc,Yc,XcErr,YcErr);
  else if(Xerr.size()>0) plotgraph = new TGraphErrors(X.size(),Xc,Yc,XcErr,NULL);
  else if(Yerr.size()>0) plotgraph = new TGraphErrors(X.size(),Xc,Yc,NULL,YcErr);
  
  if(!plotgraph) return false;
  plotgraph->SetLineWidth(2);
  plotgraph->Draw("AL1");
  plotgraph->SetTitle(name.c_str());
  plotgraph->GetXaxis()->SetTitle(xname.c_str());
  plotgraph->GetYaxis()->SetTitle(yname.c_str());
  string gname=yname+".v."+xname+"_"+name;
  plotgraph->SetName(gname.c_str());
  
  if(arrow< X.size() && arrow < Y.size())
  {
    TArrow* Thisarrow = new TArrow(X[arrow],0,X[arrow],Y[arrow],0.01,"<-");
    if(!Thisarrow) return false;
    Thisarrow->SetLineWidth(2) ;
    Thisarrow->SetLineColor(kBlue);
    Thisarrow->Draw();
  }
  
  plotCanvas->Draw();
  plotgraph->Write();
  plotCanvas->Write();
  
  //for(unsigned int k=0; k<X.size(); k++) std::cout << "Plotted X " << Xc[k] << "+/-" << XcErr[k] << " Y " << Yc[k] << "+/-" << YcErr[k] << " \'size\' " << X.size() << std::endl;
  
  
  return true;
  
}
bool plots::cd(const std::string& directory)
{
  m_plotfile->cd();
  TDirectory *aDir=gDirectory;
  
  //parse / characters
  std::string::size_type index=string::npos;
  std::string subdir=directory;
  //std::cout << " cd parsing  " << subdir << std::endl;
  index=subdir.find_first_of('/');
  for(int k=0; k<10 && index != string::npos; k++)
  {
    //std::cout << "  " << subdir.substr(0,index).c_str() << std::endl;
    aDir->cd(subdir.substr(0,index).c_str());
    aDir=gDirectory;
    subdir.erase(0,index+1);
    index=subdir.find_first_of('/');
  }
  
  aDir->cd(subdir.c_str());
  return aDir->cd(subdir.c_str());
}

bool plots::mkdir(const std::string& directory)
{
  m_plotfile->cd();
  TDirectory *aDir=gDirectory;
  //parse / characters
  std::string::size_type index=string::npos;
  std::string subdir=directory;
  //std::cout << " mkdir parsing  " << subdir << std::endl;
  index=subdir.find_first_of('/');
  for(int k=0; k<10 && index != string::npos; k++)
  {
    //std::cout << "  " << subdir.substr(0,index).c_str() << std::endl;
      
    aDir->cd(subdir.substr(0,index).c_str());
    aDir=gDirectory;
    subdir.erase(0,index+1);
    index=subdir.find_first_of('/');
  }
  
  aDir->mkdir(subdir.c_str());
  aDir->cd(subdir.c_str());
  return aDir->cd(subdir.c_str());
}

bool plots::plot(std::vector<TH1F*> histos, const std::string& name, const std::string& directory)
{
  cd(directory);
  
  std::stringstream ss (stringstream::in | stringstream::out);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  
  TLegend* leg = new TLegend(0.75,0.82,0.9,0.92);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  
  THStack* hs=new THStack(name.c_str(),name.c_str());
  
  
  for(unsigned int k=histos.size(); k>0; k--)
  {
    ss << k-1 << std::endl;
    std::string kn="";
    ss>>kn;
    //std::cout << k-1;
      
    if(!histos[k-1]) std::cout << "ERROR: no histogram to plot?" << std::endl;
    else
    {
	  
      //histos[k]->SetDirectory(gDirectory);
      histos[k-1]->SetTitle(name.c_str());
      histos[k-1]->SetLineColor(k);
      if(k==histos.size()) 
	    {
	      histos[k-1]->Draw();
	      histos[k-1]->GetYaxis()->SetTitleOffset(1.55);
	      histos[k-1]->GetXaxis()->SetTitleOffset(1.25);
	      histos[k-1]->GetXaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetXaxis()->SetTitleSize(0.04);
	      histos[k-1]->GetYaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetYaxis()->SetTitleSize(0.04);
	      //histos[k]->SetLineColor(k+1);
	      //histos[k-1]->Draw();
	      //hs->Add(histos[k-1]);//->Draw();
	    }
      hs->Add(histos[k-1]);//->Draw();
      //else histos[k-1]->Draw("same");
      leg->AddEntry(histos[k-1],kn.c_str(),"l");
    }
      
  }
  if(m_stacked) hs->Draw();
  else hs->Draw("nostack");
  plotCanvas->Draw();
  plotCanvas->Write();
  
  return true;
  
}
bool plots::plot(std::vector<TH1F*> histos, const std::vector<TString> leg_entries, const std::string& name, const std::string& directory)
{
  cd(directory);
  if(leg_entries.size()!=histos.size()) return plot(histos, name, directory);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  
  THStack* hs=new THStack(name.c_str(),name.c_str());
  
  TLegend* leg = new TLegend(0.75,0.82,0.9,0.92);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
      
  for(unsigned int k=histos.size(); k>0; k--)
  {
    //std::cout << k-1;
      
    if(!histos[k-1]) std::cout << "ERROR: no histogram to plot?" << std::endl;
    else
    {
	  
      //histos[k]->SetDirectory(gDirectory);
      histos[k-1]->SetTitle(name.c_str());
      histos[k-1]->SetLineColor(k);
      if(k==histos.size()) 
	    {
	      histos[k-1]->Draw();
	      histos[k-1]->GetYaxis()->SetTitleOffset(1.55);
	      histos[k-1]->GetXaxis()->SetTitleOffset(1.25);
	      histos[k-1]->GetXaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetXaxis()->SetTitleSize(0.04);
	      histos[k-1]->GetYaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetYaxis()->SetTitleSize(0.04);
	      //histos[k]->SetLineColor(k+1);
	      //histos[k-1]->Draw();
	    }
      hs->Add(histos[k-1]);//->Draw();
      //else histos[k-1]->Draw("same");
      leg->AddEntry(histos[k-1],leg_entries[k-1],"l");
    }
      
  }
  
  if(m_stacked) hs->Draw();
  else hs->Draw("nostack");
  leg->Draw("same");
  plotCanvas->Draw();
  plotCanvas->Write();
  
  return true;
  
}
bool plots::plot(std::vector<TH1F*> histos, const std::string& name, const double min, const double max, const bool log, const std::string& directory)
{
  cd(directory);
  if(max <= min) return plot(histos, name, directory);
  std::stringstream ss (stringstream::in | stringstream::out);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  plotCanvas->SetLogy(log);
  
  THStack* hs=new THStack(name.c_str(),name.c_str());
  
  TLegend* leg = new TLegend(0.75,0.82,0.9,0.92);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
      
  for(unsigned int k=histos.size(); k>0; k--)
  {
    ss << k-1 << std::endl;
    std::string kn="";
    ss>>kn;
    //std::cout << k-1;
      
    if(!histos[k-1]) std::cout << "ERROR: no histogram to plot?" << std::endl;
    else if(histos[k-1]->Integral()<1e-15) std::cout << "ERROR: no entries to plot?" << std::endl;
    else if(histos[k-1]->GetEntries()<0.01) std::cout << "ERROR: no entries to plot?" << std::endl;
    else
    {
	  
      //histos[k]->SetDirectory(gDirectory);
      histos[k-1]->SetTitle(name.c_str());
      histos[k-1]->SetLineColor(k);
      if(k==histos.size()) 
	    {
	      histos[k-1]->Draw();
	      histos[k-1]->GetYaxis()->SetTitleOffset(1.55);
	      histos[k-1]->GetXaxis()->SetTitleOffset(1.25);
	      histos[k-1]->GetXaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetXaxis()->SetTitleSize(0.04);
	      histos[k-1]->GetYaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetYaxis()->SetTitleSize(0.04);
	      histos[k-1]->GetYaxis()->SetRangeUser(min,max);
	      //if(log) 
	      //histos[k]->SetLineColor(k+1);
	      //histos[k-1]->Draw();
	    }
      hs->Add(histos[k-1]);//->Draw();
      //else histos[k-1]->Draw("same");
      leg->AddEntry(histos[k-1],kn.c_str(),"l");
    }
      
  }
  if(m_stacked) hs->Draw();
  else hs->Draw("nostack");
  leg->Draw("same");
  plotCanvas->Draw();
  plotCanvas->Write();
  
  return true;
  
}

bool plots::plot(std::vector<TH1F*> histos, const std::vector<TString> leg_entries, const std::string& name, const double min, const double max, const bool log, const std::string& directory)
{
  cd(directory);
  if(leg_entries.size()!=histos.size()) return plot(histos, name, min, max, log, directory);
  if(max <= min) return plot(histos, leg_entries, name, directory);
  
  //supress annoying warning :S
  TCanvas *old = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name.c_str());
  if (old && old->IsOnHeap()) {
    //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
   }
  TCanvas* plotCanvas = new TCanvas(name.c_str());
  plotCanvas->SetLogy(log);
  
  THStack* hs=new THStack(name.c_str(),name.c_str());
  
  TLegend* leg = new TLegend(0.75,0.82,0.9,0.92);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
      
  for(unsigned int k=histos.size(); k>0; k--)
  {
      
    if(!histos[k-1]) std::cout << "ERROR: no histogram to plot?" << std::endl;
    else if(histos[k-1]->Integral()<1e-15) std::cout << "ERROR: no integral to plot?: " << name << histos[k-1]->Integral() << std::endl;
    else if(histos[k-1]->GetEntries()<0.01) std::cout << "ERROR: no entries to plot?" << name << std::endl;
    else
    {
	  
      //histos[k]->SetDirectory(gDirectory);
      histos[k-1]->SetTitle(name.c_str());
      histos[k-1]->SetLineColor(k);
      if(k==histos.size()) 
	    {
	      histos[k-1]->Draw();
	      histos[k-1]->GetYaxis()->SetTitleOffset(1.55);
	      histos[k-1]->GetXaxis()->SetTitleOffset(1.25);
	      histos[k-1]->GetXaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetXaxis()->SetTitleSize(0.04);
	      histos[k-1]->GetYaxis()->SetLabelSize(0.035);
	      histos[k-1]->GetYaxis()->SetTitleSize(0.04);
	      histos[k-1]->GetYaxis()->SetRangeUser(min,max);
	      //if(log) 
	      //histos[k]->SetLineColor(k+1);
	      //histos[k-1]->Draw();
	    }
      hs->Add(histos[k-1]);//->Draw()
      //else histos[k-1]->Draw("same");
      leg->AddEntry(histos[k-1],leg_entries[k-1],"l");
    }
      
  }
  if(m_stacked) hs->Draw();
  else hs->Draw("nostack");
  leg->Draw("same");
  plotCanvas->Draw();
  plotCanvas->Write();
  
  return true;
  
}
