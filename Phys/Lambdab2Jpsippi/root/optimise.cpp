// $Id: $
// Include files 
#include "Tuples.h"
#include "MassPdf.h"
#include "TTree.h"
#include "TFile.h"
#include "TCut.h"
#include "NetTree.h"
#include "TGraphErrors.h"

static const double c_alpha = 5. ;
static const double c_empiric = 2. ; // empiric slope factor when extrapolating

using namespace std;
//-----------------------------------------------------------------------------
// Implementation file for class : optimise
//
// 2012-10-03 : Patrick Koppenburg
//-----------------------------------------------------------------------------
class optimise {
public :
  optimise(const TString fullname1, const TString fullname2, const TString opt);
  ~optimise() {}
  int getOptimum();
private :
  double getNNCut(const double alpha);

  NetTree* m_ExpTuple ; // use
  TFile* m_outfile ;// use
  bool m_debug ;  /// use
  TCut m_sigCut ; // use
  TCut m_bkgCut ; //use
  bool m_first ;  ///< This is a first round on J/psipK
  double m_minMass ;// use
  double m_maxMass ;// use
  bool m_usePunzi ;
  
};

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
optimise::optimise( const TString fullname1, const TString fullname2, 
		    const TString opt ) {

  m_debug = true ; /// keep this line
  m_debug = ("debug"==opt) ;
  m_minMass = c_minFit ;
  m_maxMass = c_maxFit ;

  m_bkgCut = TCut("Category[0]==1 && ErrorCode[0]==0"); 
  m_sigCut = TCut("Category[0]==-1 && ErrorCode[0]==0");
  m_first = false ;
  cout << "Will be using data to optimize NN" << endl ;    
  m_usePunzi = false ;
  // now get files

  TFile* f1 = TFile::Open(fullname1);
  m_ExpTuple = new NetTree(fullname1,fullname2);
  
  unsigned int lastslash = fullname1.Last('/');
  TString plotfilename = fullname1(lastslash+1,fullname1.Length()-lastslash-1);
  TString plotfilename2 = fullname2(lastslash+1,fullname2.Length()-lastslash-1);
  
  plotfilename = plotfilename.ReplaceAll("-NN.root","-Opt.root") ;
  if (plotfilename2.Contains("S20-") && plotfilename.Contains("S20r1-")){
    plotfilename.ReplaceAll("S20r1-","S20X-");
  } else if (plotfilename2.Contains("S20r1-") && plotfilename.Contains("S20-")){
    plotfilename.ReplaceAll("S20-","S20X-");
  }
  std::cout << "Ouptut file is ``" << plotfilename << "''" << std::endl ;
  m_outfile = new TFile( plotfilename, "RECREATE" );
  m_outfile->cd();

  std::cout << "####### Optimise settings : " 
	    << " opt : ``" << opt << "''" << std::endl ;
}
//=============================================================================
// Punzi-ing
//=============================================================================
double optimise::getNNCut(const double alpha){
  if (m_debug) std::cout << "DEBUG getNNCut:: " << std::endl ;
  double nn = -5 ;  // default

  char mcut[100] = "";  
  sprintf(mcut,"PsippiMass[0]>%.3f && PsippiMass[0]<%.3f", m_maxMass, c_maxMass);
  TCut sidebandCut = TCut(mcut);
  //  if ( m_ExpTuple2==m_ExpTuple){
  sprintf(mcut,"PsipKMass[0]>%.3f && PsipKMass[0]<%.3f && 0==EventNumber%%%i", c_NormMin, c_NormMax, c_trainFrac);
  //  } else {
  //    sprintf(mcut,"PsippiMass>%.3f && PsippiMass<%.3f", c_NormMin, c_NormMax);
  //  }
  TCut peakCut = TCut(mcut);
  cout << "Mass cuts for signal are " << m_sigCut.GetTitle() << " & " << peakCut.GetTitle()<< endl ;
  cout << "Mass cuts for background are " << m_bkgCut.GetTitle() << " & " << sidebandCut.GetTitle() << endl ;
  double cMin = -1 ;
  double cMax =  1 ;
  const unsigned int nb = 1000 ;
  TH1D s("s","signal NN",nb,cMin,cMax);
  m_ExpTuple->fChain->Draw("netOutput[0] >> s",m_sigCut && peakCut);
  TH1D b("b","background NN",nb,cMin,cMax);
  m_ExpTuple->fChain->Draw("netOutput[0] >> b",m_bkgCut && sidebandCut) ; // 300 MeV
  TH1D sb("sb","Signal/sqrt(S+B)",nb,cMin,cMax);

  cout << "Entries in plots are " << s.GetEntries() << " at peak and " 
       << b.GetEntries() << " background " << endl ; 

  TGraph* grPareto = new TGraph();
  TGraph* grBest   = new TGraph();
  TGraphErrors* grFoM   = new TGraphErrors();
  TGraphErrors* grBFoM  = new TGraphErrors();
  TGraphErrors* grSB   = new TGraphErrors();
  TGraphErrors* grBSB  = new TGraphErrors();

  // factor 2 takes the slope into account
  const double factor = c_empiric*(c_NormMax-c_NormMin)/(c_maxMass-m_maxMass) ; // ratio of mass ranges
  const double background = b.Integral();
  const double signal = c_trainFrac*s.Integral(); // mutiply by trainFrac
  cout << "Factor is " << factor << ", signal: " << signal << ", background " << background << endl ;
  double sumS = signal ;  
  double sumB = background ;
  unsigned int mb = 0 ;
  double bestFoM = 0 ;
  double BFfactor = 0.09 ; // estimate
  for ( unsigned int i = 1 ; i!=nb+1 ; i++){
    sumS -= c_trainFrac*s.GetBinContent(i); // mutiply by trainFrac
    sumB -= b.GetBinContent(i);
    if (sumS<=0 || sumB<=0) break ;
    double se = (sumS/signal);
    double sd = (alpha/2+sqrt(factor*sumB));
    double FoM = se/sd ;
    double FoMe1 = sqrt(se*(1-se)/signal);
    double FoMe2 = 0.5*sqrt(sumB*factor)/sqrt(sumB);
    double FoMe = sqrt((FoMe1/se)*(FoMe1/se)+(FoMe2/sd)*(FoMe2/sd))*FoM;
    if (m_debug ) cout << se << " +/- " << FoMe1 << " and " << sd << " +/- " 
                       << FoMe2 << " (" << sumB << " " << factor << ")" << endl ;
    // sqrt s+B
    double ss =  BFfactor*sumS ;
    double sqrtSB = sqrt(ss+sumB) ;
    double SosSB = ss/sqrtSB ;
    double SosSBe_S = sqrt(ss)*(sqrtSB-0.5*ss/sqrtSB)/(ss+sumB);
    double SosSBe_B = sqrt(sumB)*(-0.5*ss/sqrtSB)/(ss+sumB);
    double SosSBe = sqrt(SosSBe_S*SosSBe_S+SosSBe_B*SosSBe_B);
    
    if (m_usePunzi){
      if ( FoM-FoMe>bestFoM ){  // only take if it's at least one sigma away
	bestFoM = FoM ;
	mb = i ;
      }
    } else {     
      if ( SosSB-SosSBe >bestFoM ){  // only take if it's at least one sigma away
	bestFoM = SosSB ;
	mb = i ;
      }
     
    }
    if (m_debug || 
        (mb==i ) || // && i>0.8*nb
        i==1) std::cout << i << " (" << s.GetBinCenter(i) 
                        << ") Signal " << sumS << " eff " <<  se 
                        << " Bkg " << factor*sumB << " eff " <<  (sumB/background) 
                        << " S/B: " << BFfactor*sumS/(factor*sumB) 
                        << " S/sqrt(S+B) " <<  SosSB 
                        << " +/- " << SosSBe
                        << " - Punzi FoM: " << FoM << " +/- " << FoMe << std::endl ;
    grPareto->SetPoint(i-1,se,(sumB/background));
    grFoM->SetPoint(i-1,s.GetBinCenter(i),FoM);
    if (m_debug) cout << s.GetBinWidth(i) << " " << FoMe << endl ;
    grFoM->SetPointError(i-1,s.GetBinWidth(i),FoMe);
    grSB->SetPoint(i-1,s.GetBinCenter(i),SosSB);
    grSB->SetPointError(i-1,s.GetBinWidth(i),SosSBe);
    sb.SetBinContent(i-1, SosSB );
    sb.SetBinError(i-1, SosSBe );
  }
  nn = cMin+(cMax-cMin)*float(mb+cMin)/nb ;
  
  if (m_usePunzi) std::cout << "Punzi with alpha : " << alpha ;
  else std::cout << "S/sqrt(S+B) method " ;
  std::cout << " NN cut: " << nn << " (bin " << mb << ")" << std::endl ;
  m_outfile->cd();
  s.Write("signal NN "+TString(m_bkgCut.GetTitle())) ;
  b.Write("background NN "+TString(m_bkgCut.GetTitle())) ;
  sb.Write("s to s and B "+TString(m_bkgCut.GetTitle())) ;
  grPareto->Write("Pareto "+TString(m_bkgCut.GetTitle())) ;
  grFoM->Write("FoM2 "+TString(m_bkgCut.GetTitle())) ;
  grBest->SetPoint(0,grPareto->GetX()[mb],grPareto->GetY()[mb]);
  grBest->Write("Best "+TString(m_bkgCut.GetTitle())) ;
  grBFoM->SetPoint(0,grFoM->GetX()[mb],grFoM->GetY()[mb]);
  grBFoM->SetPointError(0,grFoM->GetEX()[mb],grFoM->GetEY()[mb]);
  grBFoM->Write("Best FoM "+TString(m_bkgCut.GetTitle())) ;
  grBSB->SetPoint(0,grSB->GetX()[mb],grSB->GetY()[mb]);
  grBSB->SetPointError(0,grSB->GetEX()[mb],grSB->GetEY()[mb]);
  grSB->Write("SB "+TString(m_bkgCut.GetTitle())) ;
  grBSB->Write("Best SB "+TString(m_bkgCut.GetTitle())) ;
 
  return nn; 
  
}
//=============================================================================
// Optimise
//=============================================================================
int optimise::getOptimum(){

  int ok = 0 ;
  //  m_allData = getDataSet(m_allMass);
  double nnCut = getNNCut(c_alpha);
  cout << "Neural net cut to be applied will be " << nnCut << endl ;  
  std::cout << "Optimise Done. Returning " << ok << std::endl;
  return ok;
  
}
//=============================================================================
// *** Main ***
int main(int argc, char** argv) {

  if(argc<3){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./optimise.exe Lambdab-S20r1-980-NN.root Lambdab-S20-982-NN.root  " 
              << " [ | debug | allmc ] " 
              << " | tee test-optimise" << std::endl;  
    return -9;
  }

  TString a1 = TString(argv[1]);
  TString a2 = (argc>2)?TString(argv[2]):"";
  TString a3 = (argc>3)?TString(argv[3]):"";

  // *** Decode Arguments ***
  TString fullname1 = a1 ;
  TString fullname2 = "" ;
  TString what = "";
  TString opt = "";
  if (a2.Contains(".root")){
    fullname2 = a2 ;
    opt  = a3 ;
  } else {
    opt  = a2 ;
  }

  std::cout << "Configured optimise with file1: ``" << fullname1 
	    << " file2: ``" << fullname2 << "'', opt ``" << opt << "''" << std::endl ;

  make_canvas();
  optimise o(fullname1,fullname2,opt);

  return o.getOptimum();
}
