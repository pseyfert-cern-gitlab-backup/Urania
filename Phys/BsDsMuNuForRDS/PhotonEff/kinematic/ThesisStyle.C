#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TText.h"
#include "TLatex.h"

#include <iomanip>
#include <iostream>
using namespace std;



void ThesisStyle()
{
  cout<<"--------------------"<<endl;
  cout<<"PAOLO STYLE LOADED!"<<endl;
  cout<<"~/root/rootlogon.C"<<endl;
  cout<<"--------------------"<<endl<<endl;

  /////////////////////////////////////////////////////////////////
  // Simply include the line
  // gROOT->ProcessLine(".x /home/gandini/PDFs/ThesisStyle.C");
  // at the beginning of your root macro.
  /////////////////////////////////////////////////////////////////


  gROOT->Reset();

  TStyle *ThesisStyle= new TStyle("ThesisStyle","Paolo Thesis style");

  
  // Turn off some borders ///////
  ThesisStyle->SetCanvasBorderMode(0);
  ThesisStyle->SetFrameBorderMode(0);
  ThesisStyle->SetPadBorderMode(0);
  ThesisStyle->SetDrawBorder(0);
  ThesisStyle->SetCanvasBorderSize(0);
  ThesisStyle->SetFrameBorderSize(0);
  ThesisStyle->SetPadBorderSize(1);
  //ThesisStyle->SetBorderSize(2);
  ThesisStyle->SetTitleBorderSize(0);
  ////////////////////////////////

  
  ////////////////////////////////
  ThesisStyle->SetAxisColor(1, "xyz");
  ThesisStyle->SetCanvasColor(0);
  ThesisStyle->SetFrameFillColor(0);
  ThesisStyle->SetFrameLineColor(1);
  ThesisStyle->SetHistFillColor(0);
  ThesisStyle->SetHistLineColor(1);
  ThesisStyle->SetPadColor(kWhite);
  ThesisStyle->SetStatColor(0);
  ThesisStyle->SetStatTextColor(1);
  ThesisStyle->SetTitleColor(1);
  ThesisStyle->SetTitleTextColor(1);
  ThesisStyle->SetLabelColor(1,"xyz");
  ThesisStyle->SetFuncColor(2);
  ////////////////////////////////


  
  // Set the size of the default canvas //
  // 600x500 looks almost square
  ThesisStyle->SetCanvasDefH(500);
  ThesisStyle->SetCanvasDefW(600);
  ThesisStyle->SetCanvasDefX(10);
  ThesisStyle->SetCanvasDefY(10);
  ////////////////////////////////////////


  //////////////////////////////////////////////////////////
  int style_label_font=132;
  int style_label_font_bold=22;
  ThesisStyle->SetLabelFont(style_label_font,"xyz");
  ThesisStyle->SetLabelSize(0.05,"xyz");
  ThesisStyle->SetLabelOffset(0.013,"xz");
  ThesisStyle->SetLabelOffset(0.010,"y");
  ThesisStyle->SetStatFont(style_label_font);
  
  ThesisStyle->SetTitleFont(style_label_font_bold,"xyz"); // axis titles
  ThesisStyle->SetTitleFont(style_label_font_bold,"h");   // histogram title
  ThesisStyle->SetTitleSize(0.063,"xyz"); // axis titles
  ThesisStyle->SetTitleSize(0.063,"h"); // histogram title
  ThesisStyle->SetTitleOffset(1.1,"x");
  ThesisStyle->SetTitleOffset(1.4,"y");//1.1
  
  //ThesisStyle->SetStripDecimals(kFALSE); // if we have 1.5 do not set 1.0 -> 1
  ThesisStyle->SetTitleX(0.12); // spot where histogram title goes
  ThesisStyle->SetTitleW(0.78); // width computed so that title is centered
  //TGaxis::SetMaxDigits(2); // restrict the number of digits in labels
  //////////////////////////////////////////////////////////

  
  // Set Line Widths
  ThesisStyle->SetFrameLineWidth(1);
  ThesisStyle->SetFuncWidth(1);
  ThesisStyle->SetHistLineWidth(1);
  ThesisStyle->SetLineWidth(1);
  ////////////////////////////


  // Set all fill styles to be empty and line styles to be solid
  ThesisStyle->SetFrameFillStyle(0);
  ThesisStyle->SetHistFillStyle(1001);
  ThesisStyle->SetFrameLineStyle(0);
  ThesisStyle->SetHistLineStyle(0);
  ThesisStyle->SetTitleStyle(0);
  ThesisStyle->SetFuncStyle(1);

  // Set margins -- I like to shift the plot a little up and to the
  // right to make more room for axis labels
  ThesisStyle->SetPadTopMargin(0.02); //0.08
  ThesisStyle->SetPadBottomMargin(0.14);//12
  ThesisStyle->SetPadLeftMargin(0.18); //0.14
  ThesisStyle->SetPadRightMargin(0.06);


  

  // Set Data/Stat/... and other options
  ThesisStyle->SetOptDate(0);
  ThesisStyle->SetDateX(0.01);
  ThesisStyle->SetDateY(0.01);
  ThesisStyle->SetOptFile(0);
  ThesisStyle->SetOptFit(111);
  ThesisStyle->SetOptLogx(0);
  ThesisStyle->SetOptLogy(0);
  ThesisStyle->SetOptLogz(0);
  ThesisStyle->SetOptStat(1110);// no histogram title
 ThesisStyle->SetStatFormat("6.4f");
 ThesisStyle->SetFitFormat("6.4f");
 ThesisStyle->SetStatStyle(0); // hollow
 //ThesisStyle->SetStatStyle(1001); // filled
 ThesisStyle->SetStatBorderSize(0);
 ThesisStyle->SetStatW(0.25);
 ThesisStyle->SetStatH(0.125);
 //ThesisStyle->SetStatX(0.90);
 //ThesisStyle->SetStatY(0.90);
 ThesisStyle->SetStatX(1.0-ThesisStyle->GetPadRightMargin()-0.02);
 ThesisStyle->SetStatY(1.0-ThesisStyle->GetPadTopMargin()-0.02);
 ThesisStyle->SetOptTitle(1);
 // Set tick marks and turn off grids
 ThesisStyle->SetNdivisions(1005,"xyz");
 ThesisStyle->SetNdivisions(510,"xyz");
 ThesisStyle->SetPadTickX(1);
 ThesisStyle->SetPadTickY(1);
 ThesisStyle->SetTickLength(0.02,"xyz");
 ThesisStyle->SetPadGridX(0);
 ThesisStyle->SetPadGridY(0);


 // no supressed zeroes!
 ThesisStyle->SetHistMinimumZero(kTRUE);


 // Set paper size for life in the US
 //ThesisStyle->SetPaperSize(TStyle::kUSLetter);
 // or europe
 ThesisStyle->SetPaperSize(TStyle::kA4);

 // use a pretty palette for color plots
 ThesisStyle->SetPalette(1,0);

 //ThesisStyle->SetLabelColor(1,"xyz");
 // Force this style on all histograms



 int text_font=132;
 int text_font_bold=22;

 TText *PaoloLabel = new TText();
 PaoloLabel->SetTextFont(text_font_bold);
 PaoloLabel->SetTextColor(1);
 PaoloLabel->SetTextSize(0.045);
 PaoloLabel->SetTextAlign(12);

 TLatex *PaoloLatex = new TLatex();
 PaoloLatex->SetTextFont(text_font_bold);
 PaoloLatex->SetTextColor(1);
 PaoloLatex->SetTextSize(0.045);
 PaoloLatex->SetTextAlign(12);

 gStyle->SetOptStat("");
 ThesisStyle->SetOptStat("");
 gROOT->SetStyle("ThesisStyle");
 gROOT->ForceStyle();

}

