// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Add Pull Plots to Frame
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TPad.h"

using namespace RooFit ;

// ####################################################################################################
// *** Main ***
void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy, double *chi2Val){

  // *** Canvas ***
	pullCanvas->cd(1);
	Float_t ratio = 0.30; // Percentage of the plot for Pull distributions
	
	// *** Pull Plot ***
  RooPlot* pullframe = (RooPlot *)frame->emptyClone("pullframe");
	
	// Titles
  pullframe->SetTitle("");
  pullframe->SetYTitle("Pull");
  pullframe->SetXTitle(frame->GetXaxis()->GetTitle());
	
	// Fill - And specify plot option: Bar-chart
	pullframe->addObject((TObject*)frame->pullHist(),"B");
	// Extract the histogram in orde to apply plot options
	TGraph* pullgraph = (TGraph*) pullframe->getObject(0);
	//pullgraph->SetLineWidth(2);
	pullgraph->SetFillColor(12);
	pullgraph->SetFillStyle(1001);
  
  // *** Quality of Fit ***
  int numGraph = pullgraph->GetN();
  double xval = 0;
  double yval = 0;
  double yerr = 0;
  double chi2 = 0;
  for(Int_t i=0; i<numGraph; i++){
    pullgraph->GetPoint(i,xval,yval);
    yerr = pullgraph->GetErrorY(i);

    chi2 += pow(yval,2)/pow(yerr,2);
  }
  chi2Val[0] = chi2;
  chi2Val[1] = numGraph;
  std::cout << "\n PULL: Goodness of Fit estimate -> chi2 = " << chi2 << "/" << numGraph << " bins \n" << std::endl;
  std::cout << std::endl;
	
	// General Settings
  pullframe->SetMinimum(-5);
	pullframe->SetMaximum(5);
	pullframe->GetYaxis()->SetNdivisions(503,true);	
  pullframe->SetTitleSize(0,"y");// No title here	
	pullframe->SetLabelSize(0.03,"y");
	
	// *** Place the first frame ***
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
	xPad->SetLeftMargin(0.15);
	xPad->SetBottomMargin(ratio);	
	// Draw Pad	
	xPad->Draw();
	xPad->cd();
	xPad->SetLogy(logy);
	// Suppress X-axis decoration
	frame->SetLabelSize(0,"x");
	frame->SetTitleSize(0,"x");
  frame->SetLabelOffset(0.015,"y");
	// Fill Pad	
	frame->Draw("");
		
	
	// *** Place the second frame ***
	// go back to the Bottom layer
	pullCanvas->cd();
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* pullPad = new TPad("pullPad", "Pad for Pull Plot", 0., 0., 1., 1);
	pullPad->SetLeftMargin(0.15);
	pullPad->SetBottomMargin(0.17);	
	pullPad->SetTopMargin(1-ratio+0.01);
	// Make the pad transparent
	pullPad->SetFillColor(0);
	pullPad->SetFillStyle(0);
	// Draw Pad	
	pullPad->Draw();
	pullPad->cd();
	// Fill Pad - Draw Y axis on the right side such that it doesn't overlap
	pullframe->Draw("");

}

// ####################################################################################################
// *** Main ***
void AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy){

  double chi2Val[] = {-999,-999};
  AddPull(pullCanvas, frame, logy, chi2Val);
}

// ####################################################################################################