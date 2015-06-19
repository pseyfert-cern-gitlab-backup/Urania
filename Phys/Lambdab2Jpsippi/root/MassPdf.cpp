// ####################################################################################################
// Phys/Lambdab2Jpsippi Package
// PDF description
// Authors: Patrick Koppenburg 
// ####################################################################################################
#include "MassPdf.h"
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
#include "TPad.h"

using namespace RooFit ;
// ####################################################################################################

// ####################################################################################################
// *** Constructor ***
// Mass only
MassPdf::MassPdf(TString name, RooRealVar* mass, int nevents, TString opt, TString sigType, TString bkgType){
  m_debug = false ;
  
  // grep "* m_" MassPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print " "$1"=0;"}'
  m_mass = mass;
  m_nLambdab=0;
  m_nonPeaking=0;
  m_mean =0;
  m_frac=0;
  m_alpha=0;
  m_n=0;
  m_alpha2=0;
  m_n2=0;
  m_width = 0;
  m_width2 = 0 ;
  m_Lambdab=0;
  m_Lambdab_I=0;
  m_Lambdab_II=0;
  m_bkg1=0;
  m_bkg2=0;
  m_comBKG=0;
  m_massPdf=0;
  m_name = name ;

  m_nLambdab = new RooRealVar(m_name+" nLambdab", "number of Lambdab",0.0, 1.0*nevents);
  m_nonPeaking = new RooRealVar(m_name+" nNonPeaking", "number of BKG",0.0, 1.0*nevents);

  m_mean = new RooRealVar(m_name+" mean","mean mass", 5620,5600,5650);
  m_width = new RooRealVar(m_name+" width","width", 5., 2., 10.);
  m_extended = true ; // (m_nevents>0);
  
  // Individual Components
  if(sigType=="CB" || sigType=="DoubleCB" || sigType=="GaussCB"){
    std::cout << " SETUP: Signal Model m_Lambdab_I" << std::endl;
    if ("free"==opt){
      m_alpha = new RooRealVar(m_name+" alpha","alpha",1.48, 0.,10.);         
      m_n = new RooRealVar(m_name+" n","n",2.98,0.,20.);                         
    } else {
      m_alpha = new RooRealVar(m_name+" alpha","alpha",1.48);             
      m_n = new RooRealVar(m_name+" n","n",2.98);                         
    }
    m_Lambdab_I = new RooCBShape(m_name+"CBshapeLambdab","Lambdab Crystal Ball",*m_mass,*m_mean,*m_width,*m_alpha,*m_n);
  }
  if(sigType=="DoubleCB"){
    std::cout << " SETUP: Signal Model m_Lambdab_II" << std::endl;
    if ("free"==opt){
      m_alpha2 = new RooRealVar(m_name+" alpha2","alpha2",-1.32, -10.,0.);         
      m_n2 = new RooRealVar(m_name+" n2","n2",18.3,0.,20.);                         
    } else {
      m_alpha2 = new RooRealVar(m_name+" alpha2","alpha2",-1.32);         
      m_n2 = new RooRealVar(m_name+" n2","n2",18.3);                      
    }
    m_Lambdab_II = new RooCBShape(m_name+" CBshapeLambdab_refl",
                                  "Lambdab Refl Crystal Ball",*m_mass,*m_mean,*m_width,*m_alpha2,*m_n2);
  }
  if(sigType=="Gauss" || sigType=="DoubleGauss"){
    std::cout << " SETUP: Signal Model m_Lambdab_I" << std::endl;
    m_Lambdab_I = new RooGaussian(m_name+" LambdabGauss_core", 
                                  "Lambdab core gaussian" , *m_mass, *m_mean, *m_width);
  }
  if(sigType=="GaussCB" || sigType=="DoubleGauss"){
    std::cout << " SETUP: Signal Model m_Lambdab_II" << std::endl;
    m_width2 = new RooRealVar(m_name+" width2","width2",10 , 5, 3);
    m_Lambdab_II = new RooGaussian(m_name+" LambdabGauss_wide", 
                                   "Lambdab wide gaussian" , *m_mass, *m_mean, *m_width2);
  }

  // Final Model
  if(sigType=="CB"){
    std::cout << " SETUP: Signal Model = Single Crystal Ball" << std::endl;
    m_Lambdab = (RooAbsPdf *)m_Lambdab_I;
  }
  if(sigType=="Gauss"){
    std::cout << " SETUP: Signal Model = Single Gauss" << std::endl;
    m_Lambdab = (RooAbsPdf *)m_Lambdab_I;
  }
  if(sigType=="DoubleCB") std::cout << " SETUP: Signal Model = Double Crystal Ball" << std::endl;
  if(sigType=="GaussCB") std::cout << " SETUP: Signal Model = Gauss + Crystal Ball" << std::endl;
  if(sigType=="DoubleGauss") std::cout << " SETUP: Signal Model = Double Gauss" << std::endl;
  if(sigType=="DoubleCB" || sigType=="GaussCB" || sigType=="DoubleGauss"){
    m_frac = new RooRealVar(m_name+" frac", "Fraction of narrow component", 0.67521, 0.0, 1.0);
    m_Lambdab = new RooAddPdf(m_name+" Lambda PDF","Lambda PDF",RooArgList(*m_Lambdab_I,*m_Lambdab_II),RooArgList(*m_frac));
  }


  if(bkgType=="Exp"){
    std::cout << " SETUP: Background Model = Exponential" << std::endl;
    m_bkg1 = new RooRealVar(m_name+" expo","expo", -0.004,-0.1,0.);
    m_comBKG = new RooExponential(m_name+" comBKG" , "combinatorial BKG", *m_mass, *m_bkg1);
  }
  else if(bkgType=="Poly2"){
    std::cout << " SETUP: Background Model = Second Order Chebychev Polynomial" << std::endl;
    m_bkg1 = new RooRealVar(m_name+" pol1","Chebychev Par 1", -0.17993 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_bkg2 = new RooRealVar(m_name+" pol2","Chebychev Par 2", -0.00823 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_comBKG = new RooChebychev(m_name+" comBKG","combinatorial BKG", *m_mass, RooArgList(*m_bkg1, *m_bkg2));
  }
  else if(bkgType=="Poly1"){
    std::cout << " SETUP: Background Model = Second Order Chebychev Polynomial" << std::endl;
    m_bkg1 = new RooRealVar(m_name+" pol1","Chebychev Par 1", -0.17993 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_comBKG = new RooChebychev(m_name+" comBKG","combinatorial BKG", *m_mass, RooArgList(*m_bkg1));
  }
  else if(bkgType=="Uni"){
    std::cout << " SETUP: Background Model = Uniform" << std::endl;
    m_comBKG = new RooUniform(m_name+" comBKG","combinatorial BKG", *m_mass);
  }
  else std::cout << "ERROR: No background model specified." << std::endl;
  //  m_massPdf = new RooAddPdf(m_name+" massPdf", "Mass PDF for Sig + Bkg" , massPdfList(), fracPdfList());
  
  m_massPdf = new RooAddPdf(m_name+" massPdf", "Mass PDF for Sig + Bkg" , massPdfList(), fracPdfList());
  std::cout << " SETUP: Model Done \n" << std::endl;
 
}
//##################################################################################################
// *** Plot PDF ***
RooPlot* MassPdf::plotOn(TCanvas* canvas, RooDataSet* data, bool doSumW2, Int_t logy, bool param, bool pull){
  std::cout << "@@ Start Plotting PDF " << m_name << " " << m_mass->GetName() << std::endl;
  
  // *** Frame ***
  RooPlot* massFrame = m_mass->frame(Bins((m_mass->getMax() - m_mass->getMin())/5));
  
  // Titles
  massFrame->SetTitle("");
  massFrame->SetYTitle("Events/(5 MeV/c^{2})");
  if ( m_name.Contains("PsipK")) massFrame->SetXTitle("m_{J/#psipK} [MeV/c^{2}]");
  else massFrame->SetXTitle("m_{J/#psip#pi} [MeV/c^{2}]");
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  
  // PDF components
  if (!m_massPdf) {
    std::cout <<"Can't plot null" << std::endl;
    return massFrame;
  }
  m_massPdf->plotOn(massFrame, Components(*m_Lambdab), Range(m_mass->getMin(),m_mass->getMax()),
		    FillColor(15), FillStyle(1001), DrawOption("F"));
  m_massPdf->plotOn(massFrame, Components(*m_comBKG), Range(m_mass->getMin(),m_mass->getMax()),
		    LineStyle(kDashed), LineColor(kBlack) );  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,MarkerStyle(8),MarkerSize(0.8));
  m_massPdf->plotOn(massFrame, Range(m_mass->getMin(),m_mass->getMax()), LineColor(1) );
  
  std::cout << "@@ Finished Plotting PDF" << std::endl;  
  
  if ( m_name.Contains("PsipK") && 1==logy ) {
    massFrame->SetMinimum(5.); /// @todo : be smarter here
    massFrame->SetMaximum(1.5*massFrame->GetMaximum()); 
  }
  else if ( m_name.Contains("Psippi") && 1==logy ) massFrame->SetMinimum(0.8); /// @todo : be smarter here
  // Add Parameters and pull
  if(param){
    if (m_debug) std::cout << "param" << std::endl ;
    m_massPdf->paramOn(massFrame,Layout(0.5,0.92,0.92));
    massFrame->getAttText()->SetTextSize(0.03);
  }
  if(pull){
    if (m_debug) std::cout << "pull " << massFrame << std::endl ;
    std::cout << "@@ Adding Pull" << std::endl; 
    AddPull(canvas,massFrame,logy); 
  } else{
    if (m_debug) std::cout << "no pull" << std::endl ;
    canvas->SetLeftMargin(0.2);
    canvas->SetBottomMargin(0.15);
    canvas->cd(1);
    gPad->SetLogy(logy);
    massFrame->Draw("");
  } ;
  std::cout << "@@ Done plot" << std::endl; 
  return massFrame ;
}
//##################################################################################################
// *** Plot PDF ***
MassPdf::~MassPdf() {
  // grep "* m_" MassPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print "  if("$1") delete"$1";"}'
  if( m_mass ) delete m_mass ;
  if( m_nLambdab) delete m_nLambdab;
  if( m_nonPeaking) delete m_nonPeaking;
  if( m_mean ) delete m_mean ;
  if( m_frac) delete m_frac;
  if( m_alpha) delete m_alpha;
  if( m_n) delete m_n;
  if( m_alpha2) delete m_alpha2;
  if( m_n2) delete m_n2;
  if( m_Lambdab_I) delete m_Lambdab_I;
  if( m_Lambdab_II) delete m_Lambdab_II;
  if( m_Lambdab) delete m_Lambdab;
  if( m_bkg1) delete m_bkg1;
  if( m_bkg2) delete m_bkg2;
  if( m_comBKG) delete m_comBKG;
  if( m_massPdf) delete m_massPdf;

}

// ####################################################################################################
// *** Main ***
void MassPdf::AddPull(TCanvas* pullCanvas, RooPlot* frame, Int_t logy){
  if (m_debug) std::cout << "AddPull" << std::endl ;
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
  
  // General Settings
  pullframe->SetMinimum(-5);
  pullframe->SetMaximum(5);
  pullframe->GetYaxis()->SetNdivisions(503,kTRUE);	
  pullframe->SetTitleSize(0,"y");// No title here	
  // pullframe->SetLabelSize(0.,"y");// and no labels
  
  // *** Place the first frame ***
  // To keep the correct scale of the labels, use the Margins instead of Pad coordinates
  TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
  xPad->SetLeftMargin(0.2);
  xPad->SetBottomMargin(ratio);	
  // Draw Pad	
  xPad->Draw();
  xPad->cd();
  xPad->SetLogy(logy);
  // Suppress X-axis decoration
  frame->SetLabelSize(0,"x");
  frame->SetTitleSize(0,"x");
  // Fill Pad	
  frame->Draw("");
  
  
  // *** Place the second frame ***
  // go back to the Bottom layer
  pullCanvas->cd();
  // To keep the correct scale of the labels, use the Margins instead of Pad coordinates
  TPad* pullPad = new TPad("pullPad", "Pad for Pull Plot", 0., 0., 1., 1);
	pullPad->SetLogy(0);
  pullPad->SetLeftMargin(0.2);
  pullPad->SetBottomMargin(0.15);	
  pullPad->SetTopMargin(1-ratio+0.01);
  // Make the pad transparent
  pullPad->SetFillColor(0);
  pullPad->SetFillStyle(0);
  // Draw Pad	
  pullPad->Draw();
  pullPad->cd();
  // Fill Pad - Draw Y axis on the right side such that it doesn't overlap
  pullframe->Draw("");
  if (m_debug) std::cout << "Done Pull" << std::endl ;
  
}
// ####################################################################################################
void MassPdf::setConstant(TString which){
  // std::cout << "* Setting parameters to constant" << std::endl;
  if( which=="All" || which=="Signal"){
    if(m_mean) m_mean->setConstant(true);
    if(m_width) m_width->setConstant(true);
    if(m_alpha) m_alpha->setConstant(true);
    if(m_n) m_n->setConstant(true);
    if(m_frac) m_frac->setConstant(true);
    if (m_width2) m_width2->setConstant(true);
    if(m_alpha2) m_alpha2->setConstant(true);
    if(m_n2) m_n2->setConstant(true);
  }
  if( which=="All" || which=="Bkg"){
    if(m_bkg1) m_bkg1->setConstant(true);
    if(m_bkg2) m_bkg2->setConstant(true);
  }
  // std::cout << "* Done" << std::endl;
}
// ####################################################################################################
void MassPdf::setConstant(const MassPdf* pdf,TString which){
  std::cout << "* Copying values from " << pdf->m_name << std::endl ;
  if( which=="All" || which=="Signal"){
    std::cout << "* 1 " << pdf->m_mean << " " << m_mean << std::endl ;
    if (pdf->m_mean && m_mean) m_mean->setVal(pdf->m_mean->getVal());
    if (pdf->m_width && m_width) m_width->setVal(pdf->m_width->getVal());
    if (pdf->m_alpha && m_alpha) m_alpha->setVal(pdf->m_alpha->getVal());
    if (pdf->m_n && m_n) m_n->setVal(pdf->m_n->getVal());
    if (pdf->m_frac && m_frac) m_frac->setVal(pdf->m_frac->getVal());
    if (pdf->m_width2 && m_width2) m_width2->setVal(pdf->m_width2->getVal());
    if (pdf->m_alpha2 && m_alpha2) m_alpha2->setVal(pdf->m_alpha2->getVal());
    if (pdf->m_n2 && m_n2) m_n2->setVal(pdf->m_n2->getVal());
  }
  if( which=="All" || which=="Bkg"){
    if (pdf->m_bkg1 && m_bkg1) m_bkg1->setVal(pdf->m_bkg1->getVal());
    if (pdf->m_bkg2 && m_bkg2) m_bkg2->setVal(pdf->m_bkg2->getVal());
  }
  setConstant(which);
}
// ####################################################################################################
void MassPdf::Print(double& signal, double& error, bool print){
  signal = m_nLambdab->getVal();
  error = m_nLambdab->getError();
  if (print){
    std::cout << "##########################################################" << std::endl;
    std::cout << "######### " << m_name << " & = & " << signal << " \\pm " << error 
              << "\\quad (" << fabs(100*error/signal+0.5) << "\\%) #########" << std::endl ;
    std::cout << "##########################################################" << std::endl;
  }
  
}

//#####################################################################################################
RooFitResult* MassPdf::fit(RooDataSet* data, bool doSumW2, TString range){
  if (!data) return 0 ;
  if (""==range){
    if(doSumW2) return m_massPdf->fitTo(*data, PrintLevel(-1), 
                                        Warnings(false), Verbose(false), Save(), SumW2Error(kTRUE));
    else return m_massPdf->fitTo(*data, PrintLevel(-1),
                                 Warnings(false), Verbose(false), Save());
  } else {
    if(doSumW2) return m_massPdf->fitTo(*data, Range(range), PrintLevel(-1), 
                                        Warnings(false), Verbose(false), Save(), SumW2Error(kTRUE));
    else return m_massPdf->fitTo(*data, PrintLevel(-1), 
                                 Warnings(false), Verbose(false), Range(range), Save());
  }
}
