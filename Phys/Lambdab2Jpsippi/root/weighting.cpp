// $Id: $
// Include files 
#include "Tuples.h"
#include "MassPdf.h"
#include "RooDataSet.h"
#include "TTree.h"
#include "TFile.h"
#include "TCut.h"
#include "RooStats/SPlot.h"
#include "NetTree.h"
#include "MultipleCandidates.h"
#include "TGraphErrors.h"

static const TString c_PsippiName = "PsippiFit" ;
static const TString c_PsipKName = "PsipKFit" ;
static const double c_alpha = 30. ;

using namespace std;
//-----------------------------------------------------------------------------
// Implementation file for class : weighting
//
// 2012-10-03 : Patrick Koppenburg
//-----------------------------------------------------------------------------
class weighting {
public :
  weighting(const TString fullname1, const TString fullname2, const TString opt);
  ~weighting() {}
  int weight();
private :
  double getNNCut(const double alpha);
  RooDataSet* getDataSet(RooRealVar* mass, int cat = -100, 
                         double nnCut = -100, bool killMuCa = true);
  RooDataSet* reduceDataSet(RooDataSet* rd, int category, double nnCut);
  int fit(TString, RooDataSet* data, MassPdf* pdf);
  int writeTree(double nnCut);
  RooStats::SPlot* sWeight(TString name,RooRealVar* mass, const int catCode,double nnCut);
  int extractSWeight(TString name,RooDataSet* Data, RooStats::SPlot* sData, 
                              Long64_t& jentry, double& sweightLb, double& sweightBkg);
  void dataPlot(TString name, RooRealVar* mass, RooDataSet* data){  
    m_outfile->cd();
    RooPlot* massFrame = mass->frame();
    data->plotOn(massFrame);
    massFrame->Write(mass->GetName()+name);
  };
  void printBFs(double nnCut);
  inline double round(double a, double f){
    return f*int(a/f+0.5);
  } 
  
  NetTree* m_tuple ;
  NetTree* m_tuple2 ;
  TFile* m_outfile ;
  RooRealVar* m_allMass ;
  RooRealVar* m_PsippiMass ;
  RooRealVar* m_PsipKMass ;
  //  RooDataSet* m_allData ;
  RooStats::SPlot* m_sData ;
  RooStats::SPlot* m_sData_PsipK ;
  bool m_debug ;
  double m_defaultNNCut ;
  MultipleCandidates* m_eventMap;
  double m_Lbpi_s ;
  double m_Lbpi_e ;
  double m_LbK_s ;
  double m_LbK_e ;
  double m_LbpiB_s ;
  double m_LbpiB_e ;
  double m_LbKB_s ;
  double m_LbKB_e ;
  double m_LbpiAB_s ;
  double m_LbpiAB_e ;
  double m_LbKAB_s ;
  double m_LbKAB_e ;
  TCut m_sigCut ;
  TCut m_bkgCut ;
  bool m_free ;
  bool m_notree ;
  bool m_stop ;
  bool m_mc ;
  bool m_allmc ;
  
};

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
weighting::weighting( const TString fullname1, const TString fullname2, const TString opt ) {

  m_debug = true ; /// keep this line
  m_debug = ("debug"==opt) ;
  m_stop = false ;
  m_allmc = "allmc"==opt ;
  m_free = ("free"==opt || m_allmc);
  m_notree = ("notree"==opt || m_free );
  m_mc = fullname1.Contains("Lb2Jpsi") ;

  TFile* f1 = TFile::Open(fullname1);
  m_tuple = new NetTree(fullname1);

  TString NNCut = "0." ;
  m_bkgCut = TCut("Category==1");
  m_sigCut = TCut("Category==1");
  if ( fullname2==fullname1) {
    cout << "Will be using data only to optimize NN" << endl ;
    m_tuple2 = m_tuple ;
    m_sigCut = TCut("Category==-1 && ErrorCode==0"); // use J/psipK
    NNCut = "opt";
  } else if (fullname2.Contains(".root")){
    m_tuple2 = new NetTree(fullname2);    
    cout << "Neural net cut to be applied will be determined from MC" << endl ;
    NNCut = "opt";
  } else {
    m_tuple2 = 0; 
    if (""!=fullname2) NNCut = fullname2 ;
    m_defaultNNCut = NNCut.Atof() ;
  }
  
  unsigned int lastslash = fullname1.Last('/');
  TString plotfilename = fullname1(lastslash+1,fullname1.Length()-lastslash-1);
  plotfilename = plotfilename.ReplaceAll("-NN.root","-"+NNCut+"-SW.root") ;
  std::cout << plotfilename << std::endl ;
  m_outfile = new TFile( plotfilename, "RECREATE" );
  m_outfile->cd();

  m_allMass = new RooRealVar(c_PsippiMass,"all Mass",-1.,10001.);
  double mn = (m_mc?5400.:c_ppi_minFit); // wider mass window for MC
  double mx = c_ppi_maxFit;
  m_PsippiMass = new RooRealVar(c_PsippiMass,"J/#psip#pi Mass",mn,mx);
  m_PsipKMass = new RooRealVar(c_PsipKMass,"J/#psipK Mass",mn,mx); /// same fit range
  m_sData = 0;
  m_sData_PsipK = 0;
  m_eventMap = 0;
  if ("free" != opt && "notree" != opt && "" != opt && "debug" != opt && "allmc" != opt)  m_stop = true ;
  
}
//=============================================================================
// Punzi-ing
//=============================================================================
double weighting::getNNCut(const double alpha){
  char mcut[100] = "";  
  sprintf(mcut,"PsippiMass>%.3f && PsippiMass<%.3f", c_ppi_maxFit, c_ppi_maxMass);
  TCut sidebandCut = TCut(mcut);
  if ( m_tuple2==m_tuple){
    sprintf(mcut,"PsipKMass>%.3f && PsipKMass<%.3f", c_NormMin, c_NormMax);
  } else {
    sprintf(mcut,"PsippiMass>%.3f && PsippiMass<%.3f", c_NormMin, c_NormMax);
  }
  TCut peakCut = TCut(mcut);
  cout << "Mass cuts for signal are " << m_sigCut.GetTitle() << " & " << peakCut.GetTitle()<< endl ;
  cout << "Mass cuts for background are " << m_bkgCut.GetTitle() << " & " << sidebandCut.GetTitle() << endl ;
  double cMin = -1 ;
  double cMax =  1 ;
  if (m_debug) std::cout << "DEBUG getNNCut:: " << std::endl ;
  double nn = m_defaultNNCut ;  // default
  if ( 0==m_tuple2 ) return nn ;
  const unsigned int nb = 1000 ;
  TH1D s("s","signal NN",nb,cMin,cMax);
  m_tuple2->fChain->Draw("netOutput >> s",m_sigCut && peakCut);
  TH1D b("b","background NN",nb,cMin,cMax);
  m_tuple->fChain->Draw("netOutput >> b",m_bkgCut && sidebandCut) ; // 300 MeV
  TH1D sb("sb","Signal/sqrt(S+B)",nb,cMin,cMax);

  TGraph* grPareto = new TGraph();
  TGraph* grBest   = new TGraph();
  TGraphErrors* grFoM   = new TGraphErrors();
  TGraphErrors* grBFoM  = new TGraphErrors();

  // factor 1.5 takes the slope into account
  const double factor = 2*(c_NormMax-c_NormMin)/(c_ppi_maxMass-c_ppi_maxFit) ; // ratio of mass ranges
  double background = b.Integral();
  double signal = s.Integral();
  cout << "Factor is " << factor << " " << signal << " " << background << endl ;
  double sumS = signal ;
  double sumB = background ;
  unsigned int mb = 0 ;
  double bestFoM = 0 ;
  for ( unsigned int i = 1 ; i!=nb+1 ; i++){
    sumS -= s.GetBinContent(i);
    sumB -= b.GetBinContent(i);
    if (sumS<=0 || sumB<=0) break ;
    double se = (sumS/signal);
    double sd = (alpha+sqrt(factor*sumB));
    double FoM = se/sd ;
    double FoMe1 = sqrt(se*(1-se)/signal);
    double FoMe2 = 0.5*sqrt(sumB*factor)/sqrt(sumB);
    double FoMe = sqrt((FoMe1/se)*(FoMe1/se)+(FoMe2/sd)*(FoMe2/sd))*FoM;
    if (m_debug ) cout << se << " +/- " << FoMe1 << " and " << sd << " +/- " 
		       << FoMe2 << " (" << sumB << " " << factor << ")" << endl ;
    double csumS = 1200*se  ; // estimated yield
    if ( FoM-FoMe>bestFoM ){  // only take if it's at least one sigma away
      bestFoM = FoM ;
      mb = i ;
    }
    if (m_debug || 
	(mb==i && i>0.8*nb ) || 
	i==1) std::cout << i << " (" << s.GetBinCenter(i) 
			<< ") Signal " << sumS << " eff " <<  se 
			<< " Bkg " << factor*sumB << " eff " <<  (sumB/background) 
			<< " S/B: " << sumS/(factor*sumB) 
			<< " S/sqrt(S+B) " << csumS/sqrt(csumS+factor*sumB) 
			<< " FoM: " << FoM << " +/- " << FoMe << std::endl ;
    grPareto->SetPoint(i-1,se,(sumB/background));
    grFoM->SetPoint(i-1,s.GetBinCenter(i),FoM);
    if (m_debug) cout << s.GetBinWidth(i) << " " << FoMe << endl ;
    grFoM->SetPointError(i-1,s.GetBinWidth(i),FoMe);
    sb.SetBinContent(i-1, csumS/sqrt(csumS+factor*sumB) );
  }
  nn = cMin+(cMax-cMin)*float(mb+cMin)/nb ;
  if (m_debug || true ) std::cout << "Alpha " << alpha 
                                  << " NN cut: " << nn << " (bin " << mb << ")" << std::endl ;
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
 

  return nn; 
  
}
//=============================================================================
// Make DataSet
//=============================================================================
RooDataSet* weighting::getDataSet(RooRealVar* mass, int catCut, 
				  double netCut, bool killMuCa){
  TString name = TString(mass->GetName())+TString("Set");
  if (m_debug) cout << "DEBUG :: getting all data for " << name << endl ;

  RooRealVar* category = new RooRealVar(c_Category,c_Category,-10.,2.);
  RooRealVar* netOutput = new RooRealVar(c_NetOutput,c_NetOutput,-10.,2.);
  RooRealVar* baryon = new RooRealVar(c_Baryon,c_Baryon,-10.,10.);
  //  RooRealVar* entry = new RooRealVar("entry","entry",0,10000000.);
  RooDataSet* rd = 0 ;
  // replace by a loop
  if ( m_allMass == mass) {
    rd = new RooDataSet(name,name,RooArgList(*mass,*netOutput,*baryon,*category,*m_PsipKMass)); // add PsipK Mass
  } else {
    rd = new RooDataSet(name,name,RooArgList(*mass,*netOutput,*baryon,*category));
  }
  const Long64_t nentries = m_tuple->fChain->GetEntries();
  /// @todo MultipleCandidates here
  double frac = printFrac(nentries/10.);
  unsigned int nPairs = 0 ;
  unsigned int nBadNN = 0 ;
  unsigned int nBadCat = 0 ;
  unsigned int nBadMuCa = 0 ;
  unsigned int nOutOfRange = 0 ;
  unsigned int nBadPV = 0 ;
  unsigned int nBadTruth = 0 ;
  cout << "### Getting " << mass->GetName() << " data with catCut " << catCut << " netCut " << netCut << endl ; 
  for ( Long64_t i = 0 ; i<nentries ; i++){
    m_tuple->fChain->GetEntry(i);
    if( m_debug || 0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" 
							  << 100*i/nentries << "%)" << std::endl;
    std::list<unsigned int> passPVs ;
    if (m_mc && !m_allmc && 
	!((m_tuple->BKGCAT==0 && catCut==CatCodes::SignalCand) ||
	  (m_tuple->BKGCAT==c_psipK_BKGCAT && catCut==CatCodes::pKCand))) {
      nBadTruth++;
      continue;
    } 
    unsigned int npvs = (m_allmc?1:m_tuple->PVs);
    for ( unsigned int pv = 0 ; pv<npvs ; pv++){
      nPairs++ ;
      double m = 0 ;
      if (c_PsippiMass==mass->GetName()) m = m_tuple->PsippiMass[pv] ;
      else if (c_PsipKMass==mass->GetName()) m = m_tuple->PsipKMass[pv];
      else {
        cout << "Unknown " << mass->GetName() << endl ;
        return 0 ;
      }
      if (netCut>ErrorCodes::Splitter){ 
        if (m_tuple->netOutput[pv]<netCut) {
          nBadNN++ ;
          continue; 
        }
        Candidate mca = m_eventMap->randomCandidate(m_tuple->RunNumber, m_tuple->EventNumber);
	if (m_debug) std::cout << "DEBUG " << m_tuple->RunNumber << " " << m_tuple->EventNumber << " " << pv 
			       << " MCA: " << mca.first << " " << mca.second << endl ;
        if (-1!=mca.first && ( mca.first!=i || mca.second!=pv) ) {
          if (m_debug) cout << "Candidate " << i << " kept candidate is " 
			    << mca.first << " " << mca.second << endl ;
          if (mca.first!=i) nBadMuCa++ ;
          if (mca.second!=pv) nBadPV++ ;
          continue; 
        }
        if (m_tuple->Category[pv]!=catCut && !m_allmc) {
          nBadCat++ ;
          continue; 
        }
        if (m<mass->getMin() || m>mass->getMax()){
          nOutOfRange ;
          continue ;
        }
      }
      if (c_PsippiMass==mass->GetName()) m = m_tuple->PsippiMass[pv] ;
      else if (c_PsipKMass==mass->GetName()) m = m_tuple->PsipKMass[pv];    
      mass->setVal(m);
      if ( m_allMass == mass) { // additional variable
	m_PsipKMass->setVal(m_tuple->PsipKMass[pv]);
      }
      netOutput->setVal(m_tuple->netOutput[pv]);
      category->setVal(m_tuple->Category[pv]);
      baryon->setVal(m_tuple->Baryon);
      if (m_debug) std::cout << "Adding " << i << " " << m_tuple->Category[pv] << " " 
                             << m_tuple->EventNumber << std::endl ;
      if ( m_allMass == mass) rd->add(RooArgSet(*mass,*netOutput,*baryon,*category,*m_PsipKMass));
      else rd->add(RooArgSet(*mass,*netOutput,*baryon,*category));
    }
  } // candidates
  
  std::cout << "######################### Results #########################" << std::endl ;
  std::cout                  << "  Number of candidates                    : " << nentries << std::endl;
  if (nBadTruth)   std::cout << "  Number of bad Truth                     : " << nBadTruth << std::endl ;
  std::cout                  << "  Number of pairs                         : " << nPairs << std::endl;
  if (nBadNN)      std::cout << "    Number of pairs failing cuts          : " << nBadNN << std::endl;
  if (nBadMuCa)    std::cout << "    Number of killed Multiple pairs       : " << nBadMuCa << std::endl ;
  if (nBadPV)      std::cout << "    Number of Multiple PV pairs           : " << nBadPV << std::endl;
  if (nBadCat)     std::cout << "    Number of bad category pairs          : " << nBadCat << std::endl;
  if (nOutOfRange) std::cout << "    Number of bad masses                  : " << nOutOfRange << std::endl ;
  std::cout                  << "    Number of Good pairs                  : " << rd->sumEntries() << std::endl;
  std::cout << "###########################################################" << std::endl ;

  if (netCut<ErrorCodes::Splitter) dataPlot("AllData",mass,rd);
  if (m_debug) std::cout << "DEBUG :: getDatset returns " << name << " with " 
			 << rd->sumEntries() << " entries" << std::endl ;
  return rd ;

} 
//=============================================================================
// Write Tree
//=============================================================================
int weighting::writeTree(double nnCut){

  if (m_debug) std::cout << "INFO :: writeTree" << std::endl ;
  Double_t wPsippiMass[100], wPsipKMass[100], sweightLb[100], sweightBkg[100], wNetOutput[100], wMass[100], wQ[100] ;
  Int_t wCategory[100], wErrorCode[100], wBaryon ;
    
  TTree* outtree = new TTree("WeightTree","Weight Tree");
  unsigned int wPV_s  = 0 ;  // do not use the same name as in [wPV] 
  // see http://root.cern.ch/root/roottalk/roottalk03/2873.html
  outtree->Branch("wPV",           &wPV_s,       "wPV/I");
  outtree->Branch("wMass",         &wMass,       "wMass[wPV]/D");
  outtree->Branch("wQ",            &wQ,          "wQ[wPV]/D");
  outtree->Branch("w"+c_PsippiMass,&wPsippiMass, "w"+c_PsippiMass+"[wPV]/D");
  outtree->Branch("w"+c_PsipKMass, &wPsipKMass,  "w"+c_PsipKMass+"[wPV]/D");
  outtree->Branch("sweightLb",     &sweightLb,   "sweightLb[wPV]/D");
  outtree->Branch("sweightBkg",    &sweightBkg,  "sweightBkg[wPV]/D");
  outtree->Branch("w"+c_Category,  &wCategory,   "w"+c_Category+"[wPV]/I");
  outtree->Branch("w"+c_NetOutput, &wNetOutput,  "w"+c_NetOutput+"[wPV]/D");
  outtree->Branch("w"+c_Baryon,    &wBaryon,     "w"+c_Baryon+"/I");
  outtree->Branch("w"+c_ErrorCode, &wErrorCode,  "w"+c_ErrorCode+"[wPV]/I");
  outtree->SetDirectory(m_outfile);
  
  RooDataSet* PsippiData = m_sData->GetSDataSet() ;
  RooDataSet* PsipKData = m_sData_PsipK->GetSDataSet() ;
  const Long64_t nentries = m_tuple->fChain->GetEntries();
  RooArgSet *allVar = (RooArgSet *) PsippiData->get();
  RooArgSet*  sWeightPsippiVar = (RooArgSet *) PsippiData->get();
  RooArgSet * sWeightPsipKVar = (RooArgSet *) PsipKData->get();
  //  RooRealVar* sWeightPsipK_mass = (RooRealVar *)sWeightPsipKVar->find(c_PsipKMass);
  
  Long64_t Psippi_entry = 0 ;
  Long64_t PsipK_entry = 0 ;
  int ok = 0;
  double frac = printFrac(nentries/10.);

  int nPPi = m_sData->GetSDataSet()->sumEntries() ;
  int nPK = m_sData_PsipK->GetSDataSet()->sumEntries() ;
  
  for(Long64_t i=0; i<nentries; i++){
    m_tuple->fChain->GetEntry(i);
    if( m_debug || 0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" 
							  << 100*i/nentries << "%)" << std::endl;
    wPV_s = m_tuple->PVs ;
    wBaryon = m_tuple->Baryon ;
    for ( unsigned int pv = 0 ; pv<m_tuple->PVs ; pv++){    
      wPsippiMass[pv] = m_tuple->PsippiMass[pv];
      wPsipKMass[pv]  = m_tuple->PsipKMass[pv];
      wCategory[pv] = m_tuple->Category[pv];
      wNetOutput[pv] = m_tuple->netOutput[pv];
      wErrorCode[pv] = m_tuple->ErrorCode[pv];
      if ( CatCodes::SignalCand == wCategory[pv] ) {
        wMass[pv] = wPsippiMass[pv] ;
        wQ[pv]    = wPsippiMass[pv]-m_psi-m_p-m_pi ;
      } else if ( CatCodes::pKCand == wCategory[pv] ) {
        wMass[pv] = wPsipKMass[pv] ;
        wQ[pv]    = wPsipKMass[pv]-m_psi-m_p-m_K ;
      } else {
        wMass[pv] = ErrorCodes::FailsCuts ;
        wQ[pv] = ErrorCodes::FailsCuts ; 
      }
      if (m_debug) std::cout << "DEBUG:: " << i << " M:" << wPsippiMass[pv] << " " << wCategory[pv]
                             << " " << wNetOutput[pv] << " " << wPsipKMass[pv] << std::endl ;
      if ( wNetOutput[pv]>nnCut ){        
        Candidate mca = m_eventMap->randomCandidate(m_tuple->RunNumber, m_tuple->EventNumber);
        if ( mca.first>=0 && m_debug) std::cout << "DEBUG:: Multiple Candidate. " 
						 << i << " Kept is " << mca.first << " " << mca.second << std::endl ;
        if (-1<mca.first && (mca.first!=i || mca.second!=pv) ){
          if (m_debug ) std::cout << "DEBUG:: killed Multiple Candidate. Kept is " << mca.first 
				  << " " << mca.second << std::endl ;
          sweightLb[pv] = ErrorCodes::KilledMuCa;
          sweightBkg[pv] =  ErrorCodes::KilledMuCa ;
          wErrorCode[pv] = ErrorCodes::KilledMuCa ; // new error code
        } else if (CatCodes::SignalCand == wCategory[pv]  &&
            wPsippiMass[pv]>=c_ppi_minFit && wPsippiMass[pv]<=c_ppi_maxFit){
          ok = extractSWeight(c_PsippiName,PsippiData,m_sData,Psippi_entry,sweightLb[pv],sweightBkg[pv]);
          RooRealVar* mass = (RooRealVar *)PsippiData->get()->find(c_PsippiMass);
          if (fabs(mass->getVal()-wPsippiMass[pv])>0.01){
            std::cout << "ERROR:: ppi candidate " << i << " and " << Psippi_entry  << " / " << nPK
                      << " M:" << mass->getVal() << " but should have " << wPsippiMass[pv] << std::endl ;
            return -11 ;
          }
          if (m_debug) std::cout << "DEBUG:: ppi candidate " << i << " and " 
                                 << Psippi_entry << " / " << nPPi
                                 << " M:" << wPsippiMass[pv] << " W = " << sweightLb[pv] << std::endl ;
        } else if (CatCodes::pKCand == wCategory[pv] && 
                   wPsipKMass[pv]>=c_ppi_minFit && wPsipKMass[pv]<=c_ppi_maxFit){   // fit range is the same
          ok = extractSWeight(c_PsipKName,PsipKData,m_sData_PsipK,PsipK_entry,sweightLb[pv],sweightBkg[pv]);      
          RooRealVar* mass = (RooRealVar *)PsipKData->get()->find(c_PsipKMass);
          if (fabs(mass->getVal()-wPsipKMass[pv])>0.01){
            std::cout << "ERROR:: pK  candidate " << i << " and " << PsipK_entry  << " / " << nPK
                      << " M:" << mass->getVal() << " but should have " << wPsipKMass[pv] << std::endl ;
            return -11 ;
          }
          if (m_debug) std::cout << "DEBUG:: pK  candidate " << i << " and " << PsipK_entry  << " / " << nPK
                                 << " M:" << wPsipKMass[pv] << " W = " << sweightLb[pv] << std::endl ;

        } else {
          sweightLb[pv] = ErrorCodes::FailsCuts ;
          sweightBkg[pv] =  ErrorCodes::FailsCuts ;
        }
      }
      else {
        sweightLb[pv] = ErrorCodes::FailsCuts ;
        sweightBkg[pv] =  ErrorCodes::FailsCuts ; 
      }
      if (0!=ok) {
        std::cout << "ERROR " << ok << std::endl ;
        return ok;
      }
    } // pv
    outtree->Fill() ;	
  }
  std::cout << "Reached sWeight entries " << Psippi_entry << " of " << nPPi << std::endl ;
  outtree->Write();
  std::cout << "Done" << std::endl ;
  
  return ok ;
}
//=============================================================================
// extractSWeight(){
//=============================================================================
int weighting::extractSWeight(TString name,RooDataSet* Data, RooStats::SPlot* sData, 
                              Long64_t& jentry, double& sweightLb, double& sweightBkg){
  
  if (jentry>=Data->sumEntries()){
    std::cout << "ERROR : " << jentry << " larger than " << Data->sumEntries() << std::endl ;
    return -8 ;
  }
  Data->get(jentry);
  if (sData->GetSWeightVars().getSize() == 0 ){
    cout << "Error. Sweight has no variables " << endl ;
    return -7 ;
  }
  
  sweightLb = sData->GetSWeight(jentry,name+" nLambdab");
  sweightBkg = sData->GetSWeight(jentry,name+" nNonPeaking");
  if (m_debug){
    RooArgList ra = sData->GetSWeightVars();
    cout << "DEBUG :: " << ra.getSize() << " vars are " ;
    for ( unsigned int i=0 ; i<ra.getSize() ; i++) if (ra.at(i)) cout << ra.at(i)->GetName() << " ";
    cout << endl ;
  }
  if (m_debug) std::cout << "DEBUG:: sweight is " << sweightLb << std::endl ;
  if ( fabs(sweightLb+1<0.0000001) ) {
    RooArgList ra = sData->GetSWeightVars();
    cout << "Error. Sweight is " << sweightLb << ". " << ra.getSize() << " vars are " ;
    for ( unsigned int i=0 ; i<10 ; i++) {
      if (ra.at(i)) cout << ra.at(i)->GetName() << " ";
    }
    cout << " - done " << endl ;
    //    return -1 ;
  }
  jentry++;
  //  cout << "entry now " << jentry << endl ;
  return 0;
}
  
//=============================================================================
// Fit
//=============================================================================
int weighting::fit(TString name, RooDataSet* data, MassPdf* pdf){
  
  Int_t logy = (m_mc || (c_PsippiMass==pdf->mass()->GetName()?0:1));
  dataPlot("Data4Fit",pdf->mass(),data);
  std::cout << "#################### FIT " << name << " #######################" << std::endl ;
  RooFitResult* r = pdf->fit(data,true);
  r->Print();
  TCanvas* getBestPlot1 = new TCanvas(name,"Canvas for MassPlot",600,600);
  RooPlot* r1 = pdf->plotOn(getBestPlot1,data,kFALSE,logy,false,false); // Plot without Pull
  r1->Write(name);
  getBestPlot1->Write("TC_"+name);
  TCanvas* getBestPlot2 = new TCanvas(name+"B","Canvas for MassPlot",600,600);
  RooPlot* r2 = pdf->plotOn(getBestPlot2,data,kFALSE,logy,true,false); // Plot without Pull but param
  r2->Write(name+"B");
  getBestPlot2->Write("TC_"+name+"B");
  TCanvas* getBestPlot3 = new TCanvas(name+"C","Canvas for MassPlot",600,600);
  RooPlot* r3 = pdf->plotOn(getBestPlot3,data,kFALSE,logy,false,true); // Plot with pull
  r3->Write(name+"C");
  getBestPlot3->Write("TC_"+name+"C");
  pdf->Print();
  if (m_debug) std::cout << "#################### FIT " << name << " done #######################" << std::endl ;
  return 0 ;
}
//=============================================================================
// Fit
//=============================================================================
RooStats::SPlot* weighting::sWeight(TString name,RooRealVar* mass, const int catCode,double nnCut){
  if (m_debug) std::cout << "DEBUG :: sWeight " << name << std::endl ;
  RooDataSet* Data = getDataSet(mass,catCode,nnCut,true);
  if (m_debug || Data->sumEntries()==0) std::cout << "DEBUG :: " << name << " " << mass->GetName() << " " 
			 << Data->sumEntries() << std::endl ;
  if (Data->sumEntries()==0) return 0 ;
  dataPlot("SelData",mass,Data);
  MassPdf* mFit = new MassPdf(name,mass,Data->sumEntries(),(m_free?"free":""));
  if (m_mc && !m_allmc) {
    mFit->nNonPeaking()->setVal(0.);
    mFit->nNonPeaking()->setConstant(true);
  }
  m_outfile->cd();
  int ok = fit(name, Data, mFit);  
  if (0!=ok) return 0;
  if (m_debug) std::cout << "DEBUG :: Doing sWeight " << name 
                         << " " << mFit->fracPdfList().at(0)->GetName() 
                         << " " << mFit->fracPdfList().at(1)->GetName() << std::endl ;
  RooStats::SPlot* sp = (m_notree?0:new RooStats::SPlot(name+"sData",name+"sData", *Data, mFit->pdf(), mFit->fracPdfList()));
  if (!m_free){
    // CPV
    RooDataSet* DataA = (RooDataSet *)Data->reduce(c_Baryon+"<0"); // Antibaryon
    RooDataSet* DataB = (RooDataSet *)Data->reduce(c_Baryon+">0"); // Baryon
    cout << "Antibaryon entries " << DataA->sumEntries() << " and baryon entries " << DataB->sumEntries() << " from " << Data->sumEntries() << endl ;
    if ( 0==DataA->sumEntries() || 0==DataB->sumEntries() ) return 0 ;
    MassPdf* mFitA = new MassPdf(name+"A",mass,DataA->sumEntries(),"");
    mFitA->setConstant(mFit,"Signal");
    MassPdf* mFitB = new MassPdf(name+"B",mass,DataB->sumEntries(),"");  
    mFitB->setConstant(mFit,"Signal");
    ok = fit(name+"AB", DataA, mFitA);
    if (0!=ok) return 0;
    ok = fit(name+"B", DataB, mFitB);
    if (0!=ok) return 0;
    if (c_PsipKName==name){
      mFit->Print(m_LbK_s,m_LbK_e,false); 
      mFitB->Print(m_LbKB_s,m_LbKB_e,false); 
      mFitA->Print(m_LbKAB_s,m_LbKAB_e,false); 
    } else if (c_PsippiName==name){
      mFit->Print(m_Lbpi_s,m_Lbpi_e,false); 
      mFitB->Print(m_LbpiB_s,m_LbpiB_e,false); 
      mFitA->Print(m_LbpiAB_s,m_LbpiAB_e,false); 
    }  
    delete DataA ;
    delete DataB ;
  }
  return sp ;
}

//=============================================================================
// BFs
//=============================================================================
void weighting::printBFs(double nnCut){
  cout << "\n\n%%% Yields with NN cut = " << nnCut << endl ;
  cout << "The fit on the full sample yields:" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
  cout << "N(\\LbK) & = & " << round(m_LbK_s,1.) << " \\pm " << round(m_LbK_e,1.)
       << "\\quad (" << round(100*m_LbK_e/m_LbK_s,0.01) << "\\%) \\\\ % grepme2" << endl ;
  cout << "N(\\Lbpi) & = & " << round(m_Lbpi_s,1.) << " \\pm " << round(m_Lbpi_e,1.) 
       << "\\quad (" << round(100*m_Lbpi_e/m_Lbpi_s,0.1) << "\\%) \\\\ % grepme1" << endl ;
  double r = m_Lbpi_s/m_LbK_s ;
  double e = r*sqrt((m_LbK_e/m_LbK_s)*(m_LbK_e/m_LbK_s)+(m_Lbpi_e/m_Lbpi_s)*(m_Lbpi_e/m_Lbpi_s)) ;
  cout << "\\frac{N(\\Lbpi)}{N(\\LbK)} & = & " << round(r,0.0001) << " \\pm " << round(e,0.0001) 
       << "\\quad (" << round(100*e/r,0.1) << "\\%)" << endl ;
  cout << "\\end{eqnarray*}" << endl ;

  cout << "\n%%% Baryons " << endl ;
  cout << "Only for baryons:" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
  cout << "N(\\LbKm) & = & " << round(m_LbKB_s,1.) << " \\pm " << round(m_LbKB_e,1.) 
       << "\\quad (" << round(100*m_LbKB_e/m_LbKB_s,0.01) << "\\%) \\\\" << endl ;
  cout << "N(\\Lbpim) & = & " << round(m_LbpiB_s,1.) << " \\pm " << round(m_LbpiB_e,1.) 
       << "\\quad (" << round(100*m_LbpiB_e/m_LbpiB_s,0.1)
       << "\\%) \\\\" << endl;
  r = m_LbpiB_s/m_LbKB_s ;
  e = r*sqrt((m_LbKB_e/m_LbKB_s)*(m_LbKB_e/m_LbKB_s)+(m_LbpiB_e/m_LbpiB_s)*(m_LbpiB_e/m_LbpiB_s)) ;
  cout << "\\frac{N(\\Lbpim)}{N(\\LbKm)} & = & " << round(r,0.0001) << " \\pm " << round(e,0.0001) 
       << "\\quad (" << round(100*e/(r),0.1) << "\\%)" << endl ;
  cout << "\\end{eqnarray*}" << endl ;
  
  cout << "\n%%% AntiBaryons " << endl ;
  cout << "Only for antibaryons:" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
  cout << "N(\\LbbKp) & = & " << round(m_LbKAB_s,1.) << " \\pm " << round(m_LbKAB_e,1.) 
       << "\\quad (" << round(100*m_LbKAB_e/m_LbKAB_s,0.01) 
       << "\\%) \\\\" << endl ;
  cout << "N(\\Lbbpip) & = & " << round(m_LbpiAB_s,1.) << " \\pm " << round(m_LbpiAB_e,1.) 
       << "\\quad (" << round(100*m_LbpiAB_e/m_LbpiAB_s,0.1)
       << "\\%) \\\\" << endl;
  r = m_LbpiAB_s/m_LbKAB_s ;
  e = sqrt((m_LbKAB_e/m_LbKAB_s)*(m_LbKAB_e/m_LbKAB_s)+(m_LbpiAB_e/m_LbpiAB_s)*(m_LbpiAB_e/m_LbpiAB_s))*r ;
  cout << "\\frac{N(\\Lbbpip)}{N(\\LbbKp)} & = & " << round(r,0.0001) << " \\pm " << round(e,0.0001) 
       << "\\quad (" << round(100*e/(r),0.1) << "\\%)" << endl ;
  cout << "\\end{eqnarray*}" << endl ;
  
  cout << "\n%%% DeltaACP " << endl ;
  cout << "Resulting in the following raw asymmetries:" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
  double aK  = (m_LbKB_s-m_LbKAB_s)/m_LbK_s ;
  double aKe = sqrt((1-aK)*(1+aK)/m_LbK_s); 
  cout << "A_{CP}(\\LbK) & = & (" << round(100*aK,0.1) << " \\pm " << round(100*aKe,0.1) 
       << ")\\%\\quad (" << round(aK/aKe,0.1) << "\\sigma) \\\\" << endl ;  
  double api  = (m_LbpiB_s-m_LbpiAB_s)/m_Lbpi_s ;
  double apie = sqrt((1-api)*(1+api)/m_Lbpi_s); 
  cout << "A_{CP}(\\Lbpi) & = & (" << round(100*api,0.1) << " \\pm " << round(100*apie,0.1) 
       << ")\\%\\quad (" << round(api/apie,0.1) << "\\sigma) \\\\" << endl ; 
  e = sqrt(aKe*aKe+apie*apie);
  cout << "\\Delta A_{CP} & = & (" << round(100*(aK-api),0.1) << " \\pm " << round(100*e,0.1) 
       << ")\\%\\quad (" << round((aK-api)/e,0.1) << "\\sigma)" << endl ;
  cout << "\\end{eqnarray*}" << endl ;

}
//=============================================================================
// Weighting
//=============================================================================
int weighting::weight(){

  if (m_stop) return -5 ;
  //  m_allData = getDataSet(m_allMass);
  double nnCut = getNNCut(c_alpha);
  cout << "Neural net cut to be applied will be " << nnCut << endl ;  
  /*
   * @todo: Make the Kpi fit first, freeze the tails (now fixed)
   * Write sWeighting of Kpi. Check TisTos for signal and background.
   * There may be some more preselection cuts to apply.
   */
  m_eventMap = createEventMap(m_tuple, nnCut) ;
  /*
   * Kpi hypothesis
   */
  // *** sWeight Magic ***
  m_sData_PsipK = sWeight(c_PsipKName,m_PsipKMass,CatCodes::pKCand,nnCut);
  /*
   * Psippi hypothesis
   */
  // *** sWeight Magic ***
  m_sData = sWeight(c_PsippiName,m_PsippiMass,CatCodes::SignalCand,nnCut);

  int ok = 0;
  if ( !m_notree ){
    if (!m_sData_PsipK || !m_sData) return -6;
    ok = writeTree(nnCut);
    if (0!=ok) return ok;
  }
  
  printBFs(nnCut);

  m_outfile->Close();
  return ok;
  
}
//=============================================================================
// *** Main ***
int main(int argc, char** argv) {

  if(argc<3){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./weighting.exe  Lambdab-R12S17b-721-NN.root " 
              << " [  Lambdab-R12S17b-721-NN.root  | 0.8 ] [ notree ]" 
              << "  | tee test-weighting" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname1 = TString(argv[1]);
  TString fullname2 = TString(argv[2]);
  TString opt = (argc>3)?TString(argv[3]):"";

  make_canvas();
  weighting w(fullname1,fullname2,opt);

  return w.weight();
}
