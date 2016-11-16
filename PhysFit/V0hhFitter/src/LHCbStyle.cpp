#include "V0hhFitter/LHCbStyle.h"
#include "V0hhFitter/Exceptions.h"

using namespace V0hhFit;

// use helvetica-bold-r-normal, precision 2 (rotatable)
const Int_t LHCbStyle::LHCbStyle::m_lhcbFont = 132;  // Old LHCb style: 62;

// line thickness
const Double_t LHCbStyle::LHCbStyle::m_lhcbWidth = 2.00; // Old LHCb style: 3.00;
const Double_t LHCbStyle::LHCbStyle::m_lhcbTSize = 0.056;

LHCbStyle::LHCbStyle() {
  // use plain black on white colors
  gROOT->SetStyle("Plain"); 
  m_lhcbStyle= new TStyle("lhcbStyle","LHCb plots style");
  
  //m_lhcbStyle->SetErrorX(0); //  don't suppress the error bar along X

  m_lhcbStyle->SetFillColor(1);
  m_lhcbStyle->SetFillStyle(1001);   // solid
  m_lhcbStyle->SetFrameFillColor(0);
  m_lhcbStyle->SetFrameBorderMode(0);
  m_lhcbStyle->SetPadBorderMode(0);
  m_lhcbStyle->SetPadColor(0);
  m_lhcbStyle->SetCanvasBorderMode(0);
  m_lhcbStyle->SetCanvasColor(0);
  m_lhcbStyle->SetStatColor(0);
  m_lhcbStyle->SetLegendBorderSize(0);
  m_lhcbStyle->SetLegendFont(132);

  // If you want the usual gradient palette (blue -> red)
  m_lhcbStyle->SetPalette(1);
  // If you want colors that correspond to gray scale in black and white:
  int colors[8] = {0,5,7,3,6,2,4,1};
  m_lhcbStyle->SetPalette(8,colors);

  // set the paper & margin sizes
  m_lhcbStyle->SetPaperSize(20,26);
  m_lhcbStyle->SetPadTopMargin(0.05);
  m_lhcbStyle->SetPadRightMargin(0.05); // increase for colz plots
  m_lhcbStyle->SetPadBottomMargin(0.16);
  m_lhcbStyle->SetPadLeftMargin(0.14);
  
  // use large fonts
  m_lhcbStyle->SetTextFont(m_lhcbFont);
  m_lhcbStyle->SetTextSize(m_lhcbTSize);
  m_lhcbStyle->SetLabelFont(m_lhcbFont,"x");
  m_lhcbStyle->SetLabelFont(m_lhcbFont,"y");
  m_lhcbStyle->SetLabelFont(m_lhcbFont,"z");
  m_lhcbStyle->SetLabelSize(m_lhcbTSize,"x");
  m_lhcbStyle->SetLabelSize(m_lhcbTSize,"y");
  m_lhcbStyle->SetLabelSize(m_lhcbTSize,"z");
  m_lhcbStyle->SetTitleFont(m_lhcbFont);
  m_lhcbStyle->SetTitleFont(m_lhcbFont,"x");
  m_lhcbStyle->SetTitleFont(m_lhcbFont,"y");
  m_lhcbStyle->SetTitleFont(m_lhcbFont,"z");
  m_lhcbStyle->SetTitleSize(1.2*m_lhcbTSize,"x");
  m_lhcbStyle->SetTitleSize(1.2*m_lhcbTSize,"y");
  m_lhcbStyle->SetTitleSize(1.2*m_lhcbTSize,"z");

  // use medium bold lines and thick markers
  m_lhcbStyle->SetLineWidth(m_lhcbWidth);
  m_lhcbStyle->SetFrameLineWidth(m_lhcbWidth);
  m_lhcbStyle->SetHistLineWidth(m_lhcbWidth);
  m_lhcbStyle->SetFuncWidth(m_lhcbWidth);
  m_lhcbStyle->SetGridWidth(m_lhcbWidth);
  m_lhcbStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  m_lhcbStyle->SetMarkerStyle(20);
  m_lhcbStyle->SetMarkerSize(1.0);

  // label offsets
  m_lhcbStyle->SetLabelOffset(0.010,"X");
  m_lhcbStyle->SetLabelOffset(0.010,"Y");

  // by default, do not display histogram decorations:
  m_lhcbStyle->SetOptStat(0);  
  //m_lhcbStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  m_lhcbStyle->SetStatFormat("6.3g"); // specified as c printf options
  m_lhcbStyle->SetOptTitle(0);
  m_lhcbStyle->SetOptFit(0);
  //m_lhcbStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  //titles
  m_lhcbStyle->SetTitleOffset(0.95,"X");
  m_lhcbStyle->SetTitleOffset(0.95,"Y");
  m_lhcbStyle->SetTitleOffset(1.2,"Z");
  m_lhcbStyle->SetTitleFillColor(0);
  m_lhcbStyle->SetTitleStyle(0);
  m_lhcbStyle->SetTitleBorderSize(0);
  m_lhcbStyle->SetTitleFont(m_lhcbFont,"title");
  m_lhcbStyle->SetTitleX(0.0);
  m_lhcbStyle->SetTitleY(1.0); 
  m_lhcbStyle->SetTitleW(1.0);
  m_lhcbStyle->SetTitleH(0.05);
  
  // look of the statistics box:
  m_lhcbStyle->SetStatBorderSize(0);
  m_lhcbStyle->SetStatFont(m_lhcbFont);
  m_lhcbStyle->SetStatFontSize(0.05);
  m_lhcbStyle->SetStatX(0.9);
  m_lhcbStyle->SetStatY(0.9);
  m_lhcbStyle->SetStatW(0.25);
  m_lhcbStyle->SetStatH(0.15);

  // put tick marks on top and RHS of plots
  m_lhcbStyle->SetPadTickX(1);
  m_lhcbStyle->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  m_lhcbStyle->SetNdivisions(505,"x");
  m_lhcbStyle->SetNdivisions(510,"y");
  
  gROOT->SetStyle("lhcbStyle");
  gROOT->ForceStyle();

  std::cout << "-------------------------" << std::endl;  
  std::cout << "Set LHCb Style - Feb 2012" << std::endl;
  std::cout << "-------------------------" << std::endl;  

}

LHCbStyle::~LHCbStyle() {
    delete m_lhcbStyle; m_lhcbStyle=0;
}

TStyle* LHCbStyle::getStyle(const std::string& name) const { 
    m_lhcbStyle->SetName(name.c_str());
    return m_lhcbStyle;
}

TStyle* LHCbStyle::getStyle(const TString& name) const { 
    m_lhcbStyle->SetName(name);
    return m_lhcbStyle;
}

TText* LHCbStyle::lhcbLabel() const { 
    TText* lhcbLabel1 = new TText();
    lhcbLabel1->SetTextFont(m_lhcbFont);
    lhcbLabel1->SetTextColor(1);
    lhcbLabel1->SetTextSize(m_lhcbTSize);
    lhcbLabel1->SetTextAlign(12);
    return lhcbLabel1;
}

TLatex* LHCbStyle::lhcbLatex() const {
    TLatex* lhcbLatex1 = new TLatex();
    lhcbLatex1->SetTextFont(m_lhcbFont);
    lhcbLatex1->SetTextColor(1);
    lhcbLatex1->SetTextSize(m_lhcbTSize);
    lhcbLatex1->SetTextAlign(12);
    return lhcbLatex1;
}

TPaveText* LHCbStyle::lhcbName() const {
    TPaveText *lName = new TPaveText(0.65,0.8,0.9,0.9,"BRNDC");
    lName->SetFillColor(0);
    lName->SetTextAlign(12);
    lName->SetBorderSize(0);
    lName->AddText("LHCb");
    return lName;
}

TPaveText* LHCbStyle::addText( const std::string& optLR,
       const std::string& optText ) const {

    m_lhcbStyle->SetPadTopMargin(0.05);
    const double topmargin = gStyle->GetPadTopMargin();
    
    TPaveText *l = 0;
    
    if( optLR == "R" ) {
        const double rightmargin = gStyle->GetPadRightMargin();
        l = new TPaveText(0.70 - rightmargin,
                0.85 - topmargin,
                0.95 - rightmargin,
                0.95 - topmargin,
                "BRNDC");
    } else if ( optLR == "L" ) {
        const double leftmargin = gStyle->GetPadLeftMargin();
        l = new TPaveText( leftmargin + 0.02,
                0.85 - topmargin,
                leftmargin + 0.20,
                0.95 - topmargin,
                "BRNDC");
    } else {
        throw GeneralException("LHCbStyle::addText",
   "option " + optText + " is not defined."); 
    }

    l->AddText( optText.c_str() );

    l->SetFillColor(0);
    l->SetTextAlign(12);
    l->SetBorderSize(0);
    return l;
}

