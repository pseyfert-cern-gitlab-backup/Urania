#include <stdio.h>
#include <vector>

#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TNtuple.h"

#include "Meerkat/AbsPhaseSpace.hh"
#include "Meerkat/AbsDensity.hh"

#include "Meerkat/Logger.hh"

AbsDensity::AbsDensity(const char* pdfName) {
  m_maxTries = 100000;
  m_majorant = 0. ;
  strncpy(m_name, pdfName, 255);
  m_name[255] = 0;  
}

AbsDensity::~AbsDensity() {

}

void AbsDensity::slice(std::vector<Double_t> &x, UInt_t num, TH1F* hist) {

  std::vector<Double_t> point = x; 

  UInt_t bins = hist->GetNbinsX(); 

  Logger::print(0, "%20.20s INFO: filling 1D slice in variable %d, hist \"%s\" (%d bins)\n", 
         m_name, num, hist->GetName(), bins ); 

  UInt_t i;
  Logger::setTimer();
  for (i=1; i<=bins; i++) {
    if (Logger::timer(1)) Logger::print(0, "%20.20s INFO: filling bin %d\n", m_name, i);
    Double_t xi = hist->GetBinCenter(i); 
    point[num] = xi; 
    Double_t d = 0;
    if (phaseSpace()->withinLimits(point)) 
      d = density(point); 
    if (d<0) d = 0;
    hist->SetBinContent(i, d); 
  }
}

void AbsDensity::slice(std::vector<Double_t> &x, UInt_t numx, UInt_t numy, TH2F* hist, Bool_t inPhaseSpace) {

  std::vector<Double_t> point = x; 

  UInt_t xbins = hist->GetNbinsX(); 
  UInt_t ybins = hist->GetNbinsY(); 

  Logger::print(0, "%20.20s INFO: filling 2D slice in variables %d and %d, hist \"%s\" (%dx%d bins)\n", 
         m_name, numx, numy, hist->GetName(), xbins, ybins ); 

  UInt_t ix, iy;
  Logger::setTimer(); 
  for (ix=1; ix<=xbins; ix++) {
    if (Logger::timer(1)) Logger::print(0, "%20.20s INFO: filling row %d\n", m_name, ix);
    for (iy=1; iy<=ybins; iy++) {
      Double_t xi = hist->GetXaxis()->GetBinCenter(ix); 
      Double_t yi = hist->GetYaxis()->GetBinCenter(iy); 
      point[numx] = xi; 
      point[numy] = yi; 
      Double_t d = 0;
      if (!inPhaseSpace || phaseSpace()->withinLimits(point)) 
        d = density(point); 
      if (d<0) d = 0;
      hist->SetBinContent(ix, iy, d);
    }
  }
}

void AbsDensity::project(TH1F* hist) {
  if (phaseSpace()->dimensionality() != 1) {
    Logger::print(2, "%20.20s ERROR: Projection of %dD density to 1D histogram is not supported\n", m_name, 
           phaseSpace()->dimensionality());
    abort();
  }
  std::vector<Double_t> x(1); 
  x[0] = 0;
  slice(x, 0, hist); 
}

void AbsDensity::project(TH2F* hist, Bool_t inPhaseSpace) {
  if (phaseSpace()->dimensionality() != 2) {
    Logger::print(0, "%20.20s ERROR: Projection of %dD density to 2D histogram is not supported\n", m_name, 
           phaseSpace()->dimensionality());
    abort();
  }
  std::vector<Double_t> x(2); 
  x[0] = 0;
  x[1] = 0;
  slice(x, 0, 1, hist, inPhaseSpace); 
}

Double_t AbsDensity::generate(std::vector<Double_t> &x) {

  Bool_t success = 0;
  Double_t d = 0;
  
  UInt_t dimensionality = phaseSpace()->dimensionality(); 
  UInt_t t; 

  Bool_t estimateMajorant = (m_majorant <= 0); 
  if (estimateMajorant) {
    Logger::print(0, "%20.20s INFO: Generating toy MC distribution\n", m_name);
    Logger::print(0, "%20.20s INFO: Majorant will be estimated with %d tries\n", m_name, m_maxTries);
  }

  for (t = 0; t < m_maxTries; t++) {

    // Generate random point
    UInt_t var;
    for (var = 0; var < dimensionality; var++) {
      Double_t lowerLimit = phaseSpace()->lowerLimit(var);
      Double_t upperLimit = phaseSpace()->upperLimit(var);
      x[var] = lowerLimit + m_rnd.Rndm()*(upperLimit-lowerLimit);
    }

    Bool_t inPhsp = phaseSpace()->withinLimits(x); 
    if (inPhsp) {
      Double_t y = m_majorant*m_rnd.Rndm();
      d = density(x); 
      if (d > m_majorant) {
        if (!estimateMajorant)
          Logger::print(0, "%20.20s WARNING: Updating majorant: %f -> %f\n", m_name, m_majorant, 1.1*d);
        m_majorant = 1.1*d; 
      } 
      if (d > y) {
        success = 1; 
        if (!estimateMajorant) break;
      }
    }
  }
  if (!success) {
    Logger::print(1, "%20.20s WARNING: failed to generate a point within phase space after %d tries\n", m_name, m_maxTries); 
    return 0;
  }
  
  if (estimateMajorant) {
    Logger::print(0, "%20.20s INFO: Estimated majorant = %f\n", m_name, m_majorant);
  }
  
  return d; 
}

void AbsDensity::generate(TNtuple* tree, UInt_t numEvents) {

  Float_t array[11]; 
  UInt_t dimensionality = phaseSpace()->dimensionality(); 
  
  if (dimensionality > 10) {
    Logger::print(2, "%20.20s ERROR: Generation is not supported for more than 10 dimensions\n", m_name);
    abort();
  }

  std::vector<Double_t> x(dimensionality); 
  UInt_t i; 
  Logger::setTimer(); 
  for (i=0; i<numEvents; i++) { 
    Double_t eff = generate(x); 

    UInt_t n; 
    for (n=0; n<dimensionality; n++) array[n] = x[n]; 
    array[dimensionality] = eff; 
    
    tree->Fill(array); 
    
    if (i % 100 == 0 && Logger::timer(2)) Logger::print(0, "%20.20s INFO: Ntuple event %d/%d (%f%%)\n", 
                                         m_name, i, numEvents, 100.*(Double_t)i/(Double_t)numEvents);
  } 
  tree->Write(); 

}

double AbsDensity::transform(TH1F* hist1, TH1F* hist2, double x) {

  int i; 
  int nbins = hist1->GetNbinsX(); 
  if (hist2->GetNbinsX() != nbins) {
    Logger::print(2, "%20.20s ERROR: In transform - numbers of bins in two histograms do not match\n", m_name);
    abort(); 
  }

  TAxis* xaxis = hist1->GetXaxis(); 
  
  double xmin = xaxis->GetXmin(); 
  double xmax = xaxis->GetXmax(); 

  if (x <= xmin) return xmin; 
  if (x >= xmax) return xmax; 

  double sum1 = 0;
  double sum2 = 0;
  double partsum1 = 0.;
  double xb = xmin; 
  int xbin = 1; 
  for (i=1; i<=nbins; i++) {
    xb = xaxis->GetBinUpEdge(i); 
    double h1 = hist1->GetBinContent(i); 
    double h2 = hist2->GetBinContent(i); 
    sum1 += h1; 
    sum2 += h2; 
    if (xb < x) { 
      partsum1 += h1; 
      xbin = i+1; 
    }
  }

  if (sum1 == 0 || sum2 == 0) return x;  // No correction is the histogram is empty

  double frac0 = partsum1/sum1; 

//  int xbin = xaxis->FindBin(x);
//  double frac0 = intarr1[xbin-1]; 
  double dfrac = (x-xaxis->GetBinLowEdge(xbin))/xaxis->GetBinWidth(xbin)*hist1->GetBinContent(xbin)/sum1; 

//  int ibin2 = TMath::BinarySearch(nbins,intarr2,frac);

//  int xbin = xaxis->FindBin(x);

//  double frac = (hist1->Integral(1, xbin-1) + hist1->GetBinContent(xbin)*(x-xaxis->GetBinLowEdge(xbin)/xaxis->GetBinWidth(xbin)))/integ1; 

//  double frac0 = hist1->Integral(1, xbin-1)/integ1; 
//  double dfrac = hist1->GetBinContent(xbin)*(x-xaxis->GetBinLowEdge(xbin)/xaxis->GetBinWidth(xbin))/integ1;

  double frac = frac0 + dfrac; 

  double partsum2 = 0;
  for (i=1; i<=nbins; i++) {
    double h2 = hist2->GetBinContent(i); 
    if ( (partsum2 + h2)/sum2 > frac) break;
    partsum2 += h2; 
  }
  
//  double x2 = xaxis->GetBinLowEdge(i) + xaxis->GetBinWidth(i)*(frac - sum/integ2)/hist2->GetBinContent(i);
  double x20 = xaxis->GetBinLowEdge(i);
  if (hist2->GetBinContent(i) == 0) return x; 
  double dx2 = xaxis->GetBinWidth(i)*(frac*sum2 - partsum2)/hist2->GetBinContent(i);

  double x2 = x20 + dx2; 

  if ( !(x2<0) && !(x2>=0.) ) // If nan
    Logger::print(0, "x=%f, int1=%f, int2=%f, xbin=%d, xbin2=%d, dx/w=%f, h1=%f, frac0=%f, dfrac=%f, frac=%f, sum=%f, x20=%f, dx2=%f, x2=%f\n", 
    x, sum1, sum2, xbin, i, (x-xaxis->GetBinLowEdge(xbin))/xaxis->GetBinWidth(xbin), hist1->GetBinContent(xbin), frac0, dfrac, frac, partsum2, x20, dx2, x2);

  return x2; 

}
