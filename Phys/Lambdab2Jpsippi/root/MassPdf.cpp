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
void MassPdf::make(TString name, RooRealVar* mass, int nevents,backgrounds bkgs, 
                   TString opt, TString range, TString sigType, TString bkgType,
		   bool withXib){
  m_debug = false ;
  if (nevents<=0) std::cout << "Error : No events for " << name << std::endl ;
  
  // grep "* m_" MassPdf.h | awk -F"\*" '{print $2}' | awk -F";" '{print " "$1"=0;"}'
  m_mass = mass;
  if (""==range) {
    m_range = c_range ;
    m_mass->setRange(c_range, m_mass->getMin(),m_mass->getMax()); // trivial range
  } else m_range = range ;   // defined range
  
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
  m_backgrounds = bkgs ;

  m_nLambdab = new RooRealVar(c_Yield+" "+c_Lambdab, "number of Lambdab",0.0, 1.0*nevents);
  m_nonPeaking = new RooRealVar(c_Yield+" "+c_NonPeaking, "number of BKG",0.0, ("None"==bkgType)?0.:1.0*nevents);

  m_mean = new RooRealVar("mean","mean mass", 5620,5600,5650);
  m_width = new RooRealVar("width","width", 5., 2., 10.);
  m_extended = true ; // (m_nevents>0);
  m_lastFit = 0 ;

  m_nXib = (withXib?new RooRealVar(c_Yield+" Xib", "number of Xib",0.0, 0.01*nevents):0);
  m_meanXib = (withXib?new RooRealVar("mean Xib","mean mass Xib", 5788,5773,5803):0); // +/- 3*5 MeV
  
  // Individual Components
  if(sigType=="CB" || sigType=="DoubleCB" || sigType=="GaussCB"){
    std::cout << " SETUP: Signal Model m_Lambdab_I" << std::endl;
    if ("free"==opt){
      m_alpha = new RooRealVar("alpha","alpha",1.68, 0.,10.);         
      m_n = new RooRealVar("n","n",3.18,0.,20.);                         
    } else {
      m_alpha = new RooRealVar("alpha","alpha",1.68);             
      m_n = new RooRealVar("n","n",3.18);                         
    }
    m_Lambdab_I = new RooCBShape(m_name+"CBshapeLambdab","Lambdab Crystal Ball",*m_mass,*m_mean,*m_width,*m_alpha,*m_n);
    m_Xib_I = (withXib?new RooCBShape(m_name+"CBshapeXib","Xib Crystal Ball",*m_mass,*m_meanXib,*m_width,*m_alpha,*m_n):0);
  }
  if(sigType=="DoubleCB"){
    std::cout << " SETUP: Signal Model m_Lambdab_II" << std::endl;
    if ("free"==opt){
      m_alpha2 = new RooRealVar("alpha2","alpha2",-1.68, -10.,0.);         
      m_n2 = new RooRealVar("n2","n2",3.44,0.,20.);                         
    } else {
      m_alpha2 = new RooRealVar("alpha2","alpha2",-1.68);         
      m_n2 = new RooRealVar("n2","n2",3.44);                      
    }
    m_Lambdab_II = new RooCBShape("CBshapeLambdab_refl",
                                  "Lambdab Refl Crystal Ball",*m_mass,*m_mean,*m_width,*m_alpha2,*m_n2);
    m_Xib_II = (withXib?new RooCBShape("CBshapeXib_refl",
				       "Xib Refl Crystal Ball",*m_mass,*m_meanXib,*m_width,*m_alpha2,*m_n2):0);
  }
  if(sigType=="Gauss" || sigType=="DoubleGauss"){
    std::cout << " SETUP: Signal Model m_Lambdab_I" << std::endl;
    m_Lambdab_I = new RooGaussian("LambdabGauss_core", 
                                  "Lambdab core gaussian" , *m_mass, *m_mean, *m_width);
  }
  if(sigType=="GaussCB" || sigType=="DoubleGauss"){
    std::cout << " SETUP: Signal Model m_Lambdab_II" << std::endl;
    m_width2 = new RooRealVar("width2","width2",10 , 5, 3);
    m_Lambdab_II = new RooGaussian("LambdabGauss_wide", 
                                   "Lambdab wide gaussian" , *m_mass, *m_mean, *m_width2);
    m_Xib_II = (withXib?new RooGaussian("XibGauss_wide", 
					"Xib wide gaussian" , *m_mass, *m_meanXib, *m_width2):0);
  }

  // Final Model
  if(sigType=="CB"){
    std::cout << " SETUP: Signal Model = Single Crystal Ball" << std::endl;
    m_Lambdab = (RooAbsPdf *)m_Lambdab_I;
    m_Xib = (withXib?(RooAbsPdf *)m_Xib_I:0) ;
  }
  if(sigType=="Gauss"){
    std::cout << " SETUP: Signal Model = Single Gauss" << std::endl;
    m_Lambdab = (RooAbsPdf *)m_Lambdab_I;
    m_Xib = (withXib?(RooAbsPdf *)m_Xib_I:0) ;
  }
  if(sigType=="DoubleCB") std::cout << " SETUP: Signal Model = Double Crystal Ball" << std::endl;
  if(sigType=="GaussCB") std::cout << " SETUP: Signal Model = Gauss + Crystal Ball" << std::endl;
  if(sigType=="DoubleGauss") std::cout << " SETUP: Signal Model = Double Gauss" << std::endl;
  if(sigType=="DoubleCB" || sigType=="GaussCB" || sigType=="DoubleGauss"){
    m_frac = new RooRealVar("frac", "Fraction of narrow component", 0.491, 0.0, 1.0);
    m_Lambdab = new RooAddPdf("Lambdab PDF","Lambdab PDF",RooArgList(*m_Lambdab_I,*m_Lambdab_II),RooArgList(*m_frac));
    m_Xib = (withXib?new RooAddPdf("Xib PDF","Xib PDF",RooArgList(*m_Xib_I,*m_Xib_II),RooArgList(*m_frac)):0);
  }

  if(bkgType=="Exp"){
    std::cout << " SETUP: Background Model = Exponential" << std::endl;
    m_bkg1 = new RooRealVar("expo","expo", -0.004,-0.1,0.);
    m_comBKG = new RooExponential("comBKG" , "combinatorial BKG", *m_mass, *m_bkg1);
  }
  else if(bkgType=="Poly2"){
    std::cout << " SETUP: Background Model = Second Order Chebychev Polynomial" << std::endl;
    m_bkg1 = new RooRealVar("pol1","Chebychev Par 1", 0 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_bkg2 = new RooRealVar("pol2","Chebychev Par 2", 0 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_comBKG = new RooChebychev("comBKG","combinatorial BKG", *m_mass, RooArgList(*m_bkg1, *m_bkg2));
  }
  else if(bkgType=="Poly1"){
    std::cout << " SETUP: Background Model = Second Order Chebychev Polynomial" << std::endl;
    m_bkg1 = new RooRealVar("pol1","Chebychev Par 1", 0 , -1., 1.); // DO NOT ALLLOW FOR TOO LARGE SLOPES
    m_comBKG = new RooChebychev("comBKG","combinatorial BKG", *m_mass, RooArgList(*m_bkg1));
  }
  else if(bkgType=="Uni" || bkgType=="None"){
    std::cout << " SETUP: Background Model = Uniform" << std::endl;
    m_comBKG = new RooUniform("comBKG","combinatorial BKG", *m_mass);
  }
  else std::cout << "ERROR: No background model specified." << std::endl;
  //  m_massPdf = new RooAddPdf("massPdf", "Mass PDF for Sig + Bkg" , massPdfList(), fracPdfList());
  
  m_massPdf = new RooAddPdf("massPdf", "Mass PDF for Sig + Bkg" , massPdfList(), fracPdfList());
  std::cout << " SETUP: Model Done \n" << std::endl;
 
}
//##################################################################################################
// *** Plot PDF ***
RooPlot* MassPdf::plotOn(TCanvas* canvas, RooDataSet* data, bool doSumW2, Int_t logy, bool param, bool pull){
  std::cout << "@@ Start Plotting PDF " << m_name << " " << m_mass->GetName() << std::endl;
  if (!m_lastFit) {
    std::cout << "Error: Nothing fitted yet!"<< std::endl;
    return 0 ;
  }// http://www.slac.stanford.edu/grp/eg/minos/ROOTSYS/cvs/roofit/doc/v524/
  
  // *** Frame ***
  double bw =  (m_name.Contains("PsipK")?5.:10.) ;
  RooPlot* massFrame = m_mass->frame(Bins((m_mass->getMax() - m_mass->getMin())/bw));
  
  // Titles
  massFrame->SetTitle("");
  massFrame->SetYTitle("Events/(5 MeV/c^{2})");
  if ( m_name.Contains("PsipK")) massFrame->SetXTitle("m_{J/#psipK} [MeV/c^{2}]");
  else massFrame->SetXTitle("m_{J/#psip#pi} [MeV/c^{2}]");
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else if (c_range==m_range) data->plotOn(massFrame) ; // ,MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,CutRange(m_range)) ; // ,MarkerStyle(8),MarkerSize(0.8));
  
  // PDF components
  if (!m_massPdf) {
    std::cout <<"Can't plot null" << std::endl;
    return massFrame;
  }
  //  const RooCmdArg range = (m_range?Range(m_range):Range(m_mass->getMin(),m_mass->getMax()));
  //  std::cout << m_range << std::endl ;
  // range.Print() ;
  double n = data->sumEntries();
  if (c_range!=m_range) n = data->sumEntries("1",m_range); // weight 1 in range
  m_massPdf->plotOn(massFrame, Components(*m_Lambdab), Range(m_range),
                    Normalization(n,RooAbsReal::NumEvent),
                    FillColor(15), FillStyle(1001), DrawOption("F")); // VisualizeERange(m_range)or(*m_lastFit));
  if (m_Xib) m_massPdf->plotOn(massFrame, Components(*m_Xib), Range(m_range),
                               Normalization(n,RooAbsReal::NumEvent),
                               FillColor(16), FillStyle(1001), DrawOption("F"));
  m_massPdf->plotOn(massFrame, Components(*m_comBKG), Range(m_range),
                    Normalization(n,RooAbsReal::NumEvent),
                    LineStyle(kDashed), LineColor(kBlack)); // ,VisualizeError(*m_lastFit) ); 
  int c = 2 ;
  if (!m_backgrounds.empty()){
    for (backgrounds::iterator b = m_backgrounds.begin(); b!=m_backgrounds.end() ; ++b){
      (*b)->pdf()->Print() ;
      m_massPdf->plotOn(massFrame, Components(*((*b)->pdf())), Range(m_range),
                        Normalization(n,RooAbsReal::NumEvent),
                        LineStyle(kDotted), LineColor(c)); 
      std::cout << m_name << " : plotted " << (*b)->name() << " with colour " << c << std::endl ;
      // 2 red, 3 green, 4 blue, 6 magenta, 7 cyan, 8 dark green
      c++ ;
      if (5==c) c++; // not yellow
    }
  }
  
  // Data
  if(doSumW2) data->plotOn(massFrame, DataError(RooAbsData::SumW2),MarkerStyle(8),MarkerSize(0.8));
  else if (c_range==m_range) data->plotOn(massFrame) ; // ,MarkerStyle(8),MarkerSize(0.8));
  else data->plotOn(massFrame,CutRange(m_range)) ; // ,MarkerStyle(8),MarkerSize(0.8));
  if (c_range==m_range) m_massPdf->plotOn(massFrame, LineColor(1),  Range(m_mass->getMin(),m_mass->getMax()) );
  else m_massPdf->plotOn(massFrame, LineColor(1),  Range(m_range), Normalization(n,RooAbsReal::NumEvent) );
  
  std::cout << "@@ Finished Plotting PDF" << std::endl;  

  if (1==logy ) {
    if (0==nNonPeaking()->getVal()) massFrame->SetMinimum(0.5); /// @todo : be smarter here
    else if (m_name.Contains("PsipK")) massFrame->SetMinimum(0.8);
    else if (m_name.Contains("Psippi")) massFrame->SetMinimum(0.5);
    massFrame->SetMaximum(1.5*massFrame->GetMaximum()); 
  }
  
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
  pullframe->GetYaxis()->SetTitleOffset(1.55);
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
void MassPdf::Print(double& signal, double& error, double factor, TString print){
  Print(m_nLambdab,signal,error,factor,print);
}
// ####################################################################################################
void MassPdf::Print(RooRealVar* var){
  if (!var) return ;
  double signal = var->getVal();
  double error = var->getError();
  std::cout << var->GetName() << " & " ;
  printEbRule(signal,error);
  std::cout << " \\\\" << std::endl ;
  
}
// ####################################################################################################
void MassPdf::Print(RooRealVar* var, double& signal, double& error, double factor, TString print){
  signal = factor*var->getVal();
  error = factor*var->getError();
  if ("E"==print){
    std::cout << "##########################################################" << std::endl;
    std::cout << "######### " << m_name << " & = & " ;
    printEbRule(signal,error);
    std::cout << "\\quad (" << fabs(100*error/signal+0.5) << "\\%) #########" << std::endl ;
    std::cout << "##########################################################" << std::endl;
  } else if ("T"==print){
    Print(var->GetName(),signal,error);
    std::cout << "\\\\" << std::endl ; 
  }
}
// ####################################################################################################
void MassPdf::Print(TString name, double signal, double error){
  std::cout << name << " & " ;
  printEbRule(signal,error);
  //  std::cout << "\\\\" << std::endl ; 
}
// ####################################################################################################
void MassPdf::Print(){
  std::cout << m_name << " %%%%%%%%%%%% Results " << std::endl ;
  Print(m_nLambdab);
  Print(m_nonPeaking);
  Print(m_mean);
  Print(m_width);
  Print(m_width2);
  Print(m_frac);
  Print(m_n);
  Print(m_alpha);
  Print(m_n2);
  Print(m_alpha2);
  Print(m_bkg1);
  for (backgrounds::iterator b = m_backgrounds.begin(); b!=m_backgrounds.end() ; ++b){
    double e = (*b)->yield()->getError();
    double v = (*b)->yield()->getVal();
    Print("Yield "+(*b)->name().ReplaceAll("Mass",""),v,e);
    std::cout << " & " ; 
    printEbRule((*b)->y(),(*b)->e());
    std::cout << "\\\\" << std::endl ; 
  }
}

//#####################################################################################################
RooFitResult* MassPdf::fit(RooDataSet* data, bool doSumW2){
  if (!data) return 0 ;
  std::cout << m_massPdf << std::endl ;
  if (c_range==m_range){
    if(doSumW2) m_lastFit = m_massPdf->fitTo(*data, ExternalConstraints(externalConstraintsList()),
                                             PrintLevel(-1), Warnings(false), Verbose(false), 
                                             Save(), SumW2Error(kTRUE));
    else m_lastFit = m_massPdf->fitTo(*data, ExternalConstraints(externalConstraintsList()),
                                      PrintLevel(-1), Warnings(false), Verbose(false), Save());
  } else {
    if(doSumW2) m_lastFit = m_massPdf->fitTo(*data, Range(m_range),
                                             ExternalConstraints(externalConstraintsList()),
                                             PrintLevel(-1), Warnings(false), Verbose(false), Save(), 
                                             SumW2Error(kTRUE));
    else m_lastFit = m_massPdf->fitTo(*data, Range(m_range), 
                                      ExternalConstraints(externalConstraintsList()),
                                      PrintLevel(-1), 
                                      Warnings(false), Verbose(false),Save());
  }
  return m_lastFit ;
}
//#####################################################################################################
// out of class
double ebRule(double v, double e){   // v is the value, e the error
  if (e<=0.) return v;
  double j = int(log(e/3.5449999)/log(10.)-1); // not exactly EB rule
  double f = pow(10,j);
  double v2 = f*int(v/f+0.5);
  // std::cout << "\n EbRule " << e << " " << e/0.35449999 << " " << j << " " << f << " " << v2 << "\n" << std::endl;
  return v2 ;
}
//#####################################################################################################
double ebRule(double e){ return ebRule(e,e); }  ///< display only the error
//#####################################################################################################
void printEbRule(double v, double e, TString sep){  ///< prints v\pm e with correct number of signif digits
  if (e>0) std::cout << ebRule(v,e) << sep << ebRule(e) ;
  else std::cout << v ;
}
