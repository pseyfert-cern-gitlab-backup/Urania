// Include files 

// local
#include "DrawUtils.h"

#include "root_libs.h"
#include "TCanvas.h"
#include "TGaxis.h"

#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsRealLValue.h"


//-----------------------------------------------------------------------------
//
// 2013-04-22 : Francesco Dettori
//-----------------------------------------------------------------------------
RooPlot *DrawUtils::PlotResiduals(const RooPlot *frame)
{
  RooPlot *frameRes = frame->getPlotVar()->frame();
  RooHist *resHist = (RooHist*)frame->pullHist();
//   for (int i = 0; i < resHist->GetN(); i++)
//     resHist->SetPointError(i,0.,0.,0.,0.);
  resHist->SetFillColor(kBlue-9);
  frameRes->addObject(resHist,"E3") ; 
  frameRes->SetMinimum(-5.) ; 
  frameRes->SetMaximum(+5.) ; 
  frameRes->SetTitle("");
  frameRes->GetXaxis()->SetTitle(frame->GetXaxis()->GetTitle());
  
  frameRes->GetYaxis()->SetNdivisions(110);
  frameRes->GetYaxis()->SetLabelSize(0.);
  frameRes->GetYaxis()->SetTitle("Pull");

  frameRes->GetYaxis()->CenterTitle();
  frameRes->GetYaxis()->SetTitleSize(0.17);
  frameRes->GetYaxis()->SetTitleOffset(0.38);
  frameRes->GetXaxis()->SetNdivisions( frame->GetXaxis()->GetNdivisions() );
  //  frameRes->Draw();
  TGaxis *xup = new TGaxis(-0.05,5.,0.05,5.,-0.05,0.05,510,"-");
  xup->SetLabelSize(0.); 
  xup->SetNdivisions( frame->GetXaxis()->GetNdivisions() );
  //  xup->Draw();
  TGaxis *yright = new TGaxis(0.05,-5.,0.05,5.,-5.,5.,510,"+L");
  yright->SetLabelSize(0.);
  yright->SetNdivisions(110);
  //  yright->Draw();
  TLine *lResup = new TLine(frameRes->getPlotVar()->getMin(),3.,
			    frameRes->getPlotVar()->getMax(),3.);
  lResup->SetLineColor(kRed);
  //  lResup->Draw();
  TLine *lResdw = new TLine(frameRes->getPlotVar()->getMin(),-3.,
			    frameRes->getPlotVar()->getMax(),-3.);
  lResdw->SetLineColor(kRed);
  //  lResdw->Draw();
  //  frameRes->addObject(xup) ; 
  //  frameRes->addObject(yright) ; 
  frameRes->addObject(lResup) ; 
  frameRes->addObject(lResdw) ; 

  TLatex lat;
  lat.SetTextSize(0.16);
  lat.SetTextAlign(32);
  double xLabel = frameRes->getPlotVar()->getMin() - 
    0.01*(frameRes->getPlotVar()->getMax()-frameRes->getPlotVar()->getMin());
  TLatex *labdw = new TLatex(xLabel,-3.,"-3");
  labdw->SetTextSize(0.16);
  labdw->SetTextAlign(32);
  TLatex *labmid = new TLatex(xLabel, 0.," 0");
  labmid->SetTextSize(0.16);
  labmid->SetTextAlign(32);
  TLatex *labup = new TLatex(xLabel, 3.,"+3");
  labup->SetTextSize(0.16);
  labup->SetTextAlign(32);
  frameRes->addObject(labdw);
  frameRes->addObject(labmid);
  frameRes->addObject(labup);
  
  return frameRes; 
}


TCanvas * DrawUtils::PlotFitAndResiduals(RooPlot * frame, 
                                         const char *name, const char *title,const char* tag,
                                         int xSize , int ySize, bool log) 
{
  TLatex lat;
  lat.SetTextSize(0.06);
  lat.SetTextAlign(13);
  double xLat = frame->GetXaxis()->GetXmin() + 0.05*( frame->GetXaxis()->GetXmax()- frame->GetXaxis()->GetXmin() );
  double yLat = 0.98*frame->GetMaximum();
  
  TCanvas *c = new TCanvas(name,title,xSize,ySize);
  c->Divide(2);
  c->GetPad(1)->SetPad(0.0,0.2,1.0,1.0);
  c->GetPad(2)->SetPad(0.0,0.0,1.0,0.2);
  c->GetPad(1)->SetLeftMargin(0.15);
  c->GetPad(2)->SetLeftMargin(0.15);
  c->GetPad(1)->SetBottomMargin(0.1);
  c->GetPad(2)->SetTopMargin(0.1);
  c->cd(1);
  frame->SetMinimum(0.5);
  
  frame->Draw();
  if(log) gPad->SetLogy();
  
  lat.DrawLatex(xLat,yLat,tag);
  c->cd(2);
  RooPlot *frameRes = PlotResiduals(frame);
  frameRes->Draw();
  
  return c;
}
