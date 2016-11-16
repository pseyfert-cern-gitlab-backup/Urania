#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TText.h"
#include "TLatex.h"

#include <iomanip>
#include <iostream>
using namespace std;

TPaveText *zName = new TPaveText(0.65,0.8,0.9,0.9,"BRNDC");
TText *zLabel = new TText();
TLatex *zLatex = new TLatex();

void zstyle()
{

//gROOT->Reset();

TStyle *zStyle= new TStyle("zStyle","Z official plots style");

// use helvetica-bold-r-normal, precision 2 (rotatable)
Int_t zFont = 42;
// line thickness
Int_t zWidth = 1;

// use plain black on white colors
zStyle->SetFrameBorderMode(0);
zStyle->SetCanvasBorderMode(0);
zStyle->SetPadBorderMode(0);
zStyle->SetPadColor(0);
zStyle->SetCanvasColor(0);
zStyle->SetStatColor(0);
zStyle->SetPalette(1);
zStyle->SetTitleColor(1);
//zStyle->SetFillColor(0);

// set the paper & margin sizes
zStyle->SetPaperSize(20,26);
zStyle->SetPadTopMargin(0.05);
zStyle->SetPadRightMargin(0.05); // increase for colz plots!!
zStyle->SetPadBottomMargin(0.16);
zStyle->SetPadLeftMargin(0.14);

// use large fonts
zStyle->SetTextFont(zFont);
zStyle->SetTextSize(0.08);
zStyle->SetLabelFont(zFont,"x");
zStyle->SetLabelFont(zFont,"y");
zStyle->SetLabelFont(zFont,"z");
zStyle->SetLabelSize(0.05,"x");
zStyle->SetLabelSize(0.05,"y");
zStyle->SetLabelSize(0.05,"z");
zStyle->SetTitleFont(zFont,"x");
zStyle->SetTitleFont(zFont,"y");
zStyle->SetTitleFont(zFont,"z");
zStyle->SetTitleSize(0.05,"x");
zStyle->SetTitleSize(0.05,"y");
zStyle->SetTitleSize(0.05,"z");

// use bold lines and markers
zStyle->SetLineWidth(zWidth);
zStyle->SetFrameLineWidth(zWidth);
zStyle->SetHistLineWidth(zWidth);
zStyle->SetFuncWidth(zWidth);
zStyle->SetGridWidth(zWidth);
zStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
zStyle->SetMarkerStyle(1);
zStyle->SetMarkerSize(1);

// label offsets
zStyle->SetLabelOffset(0.015);

// by default, do not display histogram decorations:
zStyle->SetOptStat(0);  
//zStyle->SetOptStat(1110);  // show only nent, mean, rms
zStyle->SetOptTitle(0);
zStyle->SetOptFit(0);
//zStyle->SetOptFit(1011); // show probability, parameters and errors

// look of the statistics box:
zStyle->SetStatBorderSize(1);
zStyle->SetStatFont(zFont);
zStyle->SetStatFontSize(0.05);
zStyle->SetStatX(0.9);
zStyle->SetStatY(0.9);
zStyle->SetStatW(0.25);
zStyle->SetStatH(0.15);

// put tick marks on top and RHS of plots
zStyle->SetPadTickX(1);
zStyle->SetPadTickY(1);

// histogram divisions: only 5 in x to avoid label overlaps
zStyle->SetNdivisions(505,"x");
zStyle->SetNdivisions(510,"y");

gROOT->SetStyle("zStyle");
gROOT->ForceStyle();

//TPaveText *zName = new TPaveText(0.65,0.8,0.9,0.9,"BRNDC");
zName->SetFillColor(0);
zName->SetTextAlign(12);
zName->SetBorderSize(1);
zName->AddText("Z");

//TText *zLabel = new TText();
zLabel->SetTextFont(zFont);
zLabel->SetTextColor(1);
zLabel->SetTextSize(0.04);
zLabel->SetTextAlign(12);

//TLatex *zLatex = new TLatex();
zLatex->SetTextFont(zFont);
zLatex->SetTextColor(1);
zLatex->SetTextSize(0.04);
zLatex->SetTextAlign(12);

}


