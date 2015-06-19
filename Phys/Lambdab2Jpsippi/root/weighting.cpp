// $Id: $
// Include files 
#include "Tuples.h"
#include "Lambdab.h"
#include "MassPdf.h"
#include "RooDataSet.h"
#include "TTree.h"
#include "TFile.h"
#include "TCut.h"
#include "RooStats/SPlot.h"
#include "NetTree.h"
#include "MultipleCandidates.h"
#include "TGraphErrors.h"
#include "RooKeysPdf.h"
#include "background.h"

static const TString c_unblind = "unblind";
static const TString c_Fittable = "Fittable";

using namespace std;

//-----------------------------------------------------------------------------
// Implementation file for class : weighting
//
// 2012-10-03 : Patrick Koppenburg
//-----------------------------------------------------------------------------
class weighting {
public :
  weighting(const TString fullname1, const TString fullname2, const TString what, const TString opt);
  ~weighting() {}
  int weight();
private :
  double getNNCut();
  RooDataSet* getDataSet(RooRealVar* mass, int cat = -100, 
                         double nnCut = -100, bool killMuCa = true);
  //  RooDataSet* reduceDataSet(RooDataSet* rd, int category, double nnCut);
  int fit(TString, RooDataSet* data, MassPdf* pdf);
  int RKFit(TString name, RooRealVar* mass, RooDataSet* data);
  void plotRK(backgrounds& bs, RooRealVar* mass, TString name);
  background* reflectionFit(TString name, RooRealVar* mass, RooDataSet* data);
  backgrounds getBackgrounds(TString name, RooRealVar* mass, RooDataSet* Data);
  int writeTree(double nnCut);
  int writeTrainTree();
  MassPdf* doAllFits(TString name,RooRealVar* mass, RooDataSet* Data, const int catCode, 
		  double nnCut, bool blinded);
  MassPdf* doFits(TString name,RooRealVar* mass, RooDataSet* Data, const int catCode, 
		  double nnCut, bool blinded, TString baryon);
  int extractSWeight(TString name,RooDataSet* Data, RooStats::SPlot* sData, 
                     Long64_t& jentry, double& sweightLb, double& sweightNon,
                     double& sweightKpi, double& sweightpiK, double& sweightKK,
                     double& sweightKp, double& sweightLref);
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
  
  NetTree* m_ExpTuple ;
  //  NetTree* m_ExpTuple2 ;
  Lambdab* m_LambdabTuple ;     /// Init tuple for weighting
  TFile* m_outfile ;
  RooRealVar* m_allMass ;
  RooRealVar* m_PsippiMass ;
  RooRealVar* m_PsipKMass ;
  RooRealVar* m_PsiKpMass ;  /// Reflection
  RooRealVar* m_PsiKKMass ;  /// Reflection
  RooRealVar* m_PsiKpiMass ; /// Reflection
  RooRealVar* m_PsipiKMass ; /// Reflection
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
  bool m_signalmc ;
  bool m_signalmc_pi ;
  bool m_allmc ; ///< do training on MC
  bool m_all ;
  bool m_first ;  ///< This is a first round on J/psipK
  double m_minMass ;
  double m_maxMass ;
  TString m_what ;
  double m_unblind ; ///< I decide to unblind the peaks
  std::vector<TString> m_bkgCats ; ///< background categories to consider
  TString m_NNCut ;
  bool m_withXib  ;
  
};

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
weighting::weighting( const TString fullname1, const TString fullname2, 
		      const TString what, const TString opt ) {

  m_debug = true ; /// keep this line
  m_debug = ("debug"==opt) ;
  m_mc = fullname1.Contains("Sim08") ;
  m_signalmc = fullname1.Contains("Lb") ;
  m_signalmc_pi = fullname1.Contains("Lbpi") ;
  m_stop = false ;
  m_allmc = "allmc"==opt ;
  m_what = what ;
  m_all = (c_All==m_what) ;
  m_free = ("free"==opt || m_signalmc || m_allmc);
  m_withXib = ("withXib"==opt);
  m_notree = ("notree"==opt || m_mc || m_withXib );
  m_unblind = ((c_unblind==opt) || m_mc) ;
  //  m_ExpTuple2 = 0 ;
  m_minMass = (m_mc?c_minMCFit:c_minFit) ;
  m_maxMass = (m_mc?c_maxMCFit:c_maxFit) ;
  if (m_withXib) m_maxMass = c_maxFitXib ;
 

  m_NNCut = "0." ;
  m_bkgCut = TCut("Category==1 && ErrorCode==0");
  m_sigCut = TCut("Category==-1 && ErrorCode==0");
  m_first = false ;
  if ( c_Opt==m_what ) {
    cout << "Will be using data to optimize NN" << endl ;    
    m_sigCut = TCut("Category==-1 && ErrorCode==0"); // use J/psipK
    m_NNCut = c_Opt ;
    m_defaultNNCut = -5 ;
  } else if (m_all) {
    m_NNCut = c_All; 
    m_defaultNNCut = -10 ;
    m_first = true ;
    m_minMass = c_minpKFit ;
    m_maxMass = c_maxpKFit ;
    cout << "######## This is an initial weighting on J/psipK in " << m_minMass 
	 << " " << m_maxMass << endl ;
  } else {
    m_NNCut = m_what ;     
    m_defaultNNCut = m_NNCut.Atof() ;
    cout << "######## Using cut " << m_defaultNNCut << endl ;
  }
  
  // now get files

  TFile* f1 = TFile::Open(fullname1);
  if ( m_first ){
    m_LambdabTuple = new Lambdab(fullname1,"","","");
    //    if (what==fullname1) m_ExpTuple2 = m_ExpTuple ;
    m_ExpTuple = 0 ;
  } else {
    m_ExpTuple = new NetTree(fullname1,fullname2);
    m_LambdabTuple = 0 ;
  }
  // this is hard coded :-(
  m_bkgCats.push_back("0");
  m_bkgCats.push_back("1");
  m_bkgCats.push_back("31");
  m_bkgCats.push_back("32");
  m_bkgCats.push_back("33");
  m_bkgCats.push_back("34");

  unsigned int lastslash = fullname1.Last('/');
  TString plotfilename = fullname1(lastslash+1,fullname1.Length()-lastslash-1);
  TString plotfilename2 = fullname2(lastslash+1,fullname2.Length()-lastslash-1);
  
  if (plotfilename.Contains("NN")){
    plotfilename = plotfilename.ReplaceAll("-NN.root","-"+(""==opt?"":opt+"-")+m_NNCut+"-SW.root") ;
    if (plotfilename2.Contains("S20-") && plotfilename.Contains("S20r1-")){
      plotfilename.ReplaceAll("S20r1-","S20X-");
    } else if (plotfilename2.Contains("S20r1-") && plotfilename.Contains("S20-")){
      plotfilename.ReplaceAll("S20-","S20X-");
    }
  } else {
    plotfilename = plotfilename.ReplaceAll(".root","-"+m_NNCut+"-SW.root") ;
  }
  std::cout << "Ouptut file is ``" << plotfilename << "''" << std::endl ;
  m_outfile = new TFile( plotfilename, "RECREATE" );
  m_outfile->cd();

  m_allMass = new RooRealVar(c_PsippiMass,"all Mass",-1.,10001.);
  double mn = m_minMass; 
  double mx = m_maxMass;
  m_PsippiMass = new RooRealVar(c_PsippiMass,"J/#psip#pi Mass",mn,mx);
  m_PsippiMass->setRange("Low", mn, c_ppi_minBlind);
  m_PsippiMass->setRange("High", c_ppi_maxBlind, mx);
  m_PsipKMass = new RooRealVar(c_PsipKMass,"J/#psipK Mass",mn,mx); /// same fit range
  m_PsiKpMass = new RooRealVar(c_PsiKpMass,"J/#psiKp Mass",    0,15720); 
  m_PsiKpiMass = new RooRealVar(c_PsiKpiMass,"J/#psiK#pi Mass",0,15380); 
  m_PsipiKMass = new RooRealVar(c_PsipiKMass,"J/#psi#piK Mass",0,15380); 
  m_PsiKKMass = new RooRealVar(c_PsiKKMass,"J/#psiKK Mass",    0,15720); 
  m_PsippiMass->setRange(c_Fittable, 5580,5700); // narrowed, extended
  m_PsiKpMass->setRange(c_Fittable, 5520,5720);
  m_PsiKpiMass->setRange(c_Fittable, 5180,5350); // narrowed
  m_PsipiKMass->setRange(c_Fittable, 5180,5380);
  m_PsipKMass->setRange(c_Fittable, 5560,5720);  // narrowed
  m_PsiKKMass->setRange(c_Fittable, 5330,5470); // narrowed

  m_sData = 0;
  m_sData_PsipK = 0;
  m_eventMap = 0;
  if ("free" != opt && "notree" != opt && "" != opt && "debug" != opt && "allmc" != opt && "withXib"!=opt)  m_stop = true ;
  
  std::cout << "####### Weighting settings : " 
	    << (m_signalmc?"Signal ":"") 
	    << (m_mc?"MC ":"Data")
	    << (m_allmc?"AllMC ":"") 
	    << (m_free?"Free ":"Constrained ")
	    << (m_unblind?"Unblind ":"Blind ")
	    << (m_notree?"No Tree ":"Write Tree ")
	    << (m_withXib?"With Xib ":"Without Xib ")
	    << " what : ``" << what << "''"
	    << " opt : ``" << opt << "''" 
	    << " Mass range : " << m_minMass << ":" << m_maxMass << std::endl ;
}
//=============================================================================
// Punzi-ing
//=============================================================================
double weighting::getNNCut(){
  if (m_debug) std::cout << "DEBUG getNNCut:: " << std::endl ;
  double nn = m_defaultNNCut ;  // default
  return nn ;
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
  RooRealVar* BKGCAT = new RooRealVar(c_BKGCAT,c_BKGCAT,-10,100.);
  RooRealVar* DalitzWeight = new RooRealVar(c_DalitzWeight,c_DalitzWeight,0.,20.);
  RooRealVar* PTWeight = new RooRealVar(c_PTWeight+"2",c_PTWeight+"2",0.,20.);
  //  RooRealVar* entry = new RooRealVar("entry","entry",0,10000000.);
  RooDataSet* rd = 0 ;
  // replace by a loop
  RooArgList variables(*mass,*netOutput,*baryon,*category,*m_PsipKMass);
  if ( m_mc ) {
    variables.add(*BKGCAT);
    variables.add(*DalitzWeight);
    variables.add(*PTWeight);
  }
  if (m_ExpTuple) {
    variables.add(*m_PsippiMass);
    variables.add(*m_PsipKMass);
    variables.add(*m_PsiKpMass);
    variables.add(*m_PsiKpiMass);
    variables.add(*m_PsipiKMass);
    variables.add(*m_PsiKKMass); 
  }
  if (!m_mc) rd = new RooDataSet(name,name,variables); 
  // weight by Dalitz weight (usually 1)
  else rd = new RooDataSet(name,name,variables,TString(c_DalitzWeight+"*"+c_PTWeight+"2"));  
  rd->Print();
  const Long64_t nentries = (m_debug?100000:(m_ExpTuple?m_ExpTuple->fChain->GetEntries():m_LambdabTuple->GetEntries(m_debug)));
  /// @todo MultipleCandidates here
  double frac = printFrac(nentries/10.);
  unsigned int nPairs = 0 ;
  unsigned int nBadNN = 0 ;
  unsigned int nBadCat = 0 ;
  unsigned int nBadMuCa = 0 ;
  unsigned int nOutOfRange = 0 ;
  unsigned int nBadPV = 0 ;
  unsigned int nBadTruth = 0 ;
  unsigned int nGood = 0 ;
  unsigned int nBlinded = 0 ;
  unsigned int nErrorCode = 0 ;
  unsigned int nTeaching = 0 ;
  cout << "### Getting " << mass->GetName() << " data with catCut " 
       << catCut << " netCut " << netCut << endl ; 
  //  m_LambdabTuple->fChain->Scan("B_M","","",10);
  for ( Long64_t i = 0 ; i<nentries ; i++){
    m_ExpTuple?m_ExpTuple->fChain->GetEntry(i):m_LambdabTuple->fChain->GetEntry(i);
    if( m_debug || 0==i%((int)(frac*nentries))) 
      std::cout << " |-> " << i << " / " << nentries << " (" 
                << 100*i/nentries << "%) - " << (m_LambdabTuple?m_LambdabTuple->B_M:m_ExpTuple->PsippiMass[0]) << " " 
                << (m_LambdabTuple?m_LambdabTuple->eventNumber:m_ExpTuple->EventNumber) << "/" 
                << (m_LambdabTuple?m_LambdabTuple->runNumber:m_ExpTuple->RunNumber) << " Good " 
                << nGood << " (" << (nGood>0?int(10000.*nGood/i+0.5)/100.:0) 
                << "%)" << endl ;
    std::list<unsigned int> passPVs ;
    if (m_ExpTuple && m_mc && !m_allmc){  // bad MC
      int b = m_ExpTuple->BKGCAT;
      if (!(c_ppi_BKGCAT==b || c_psipK_BKGCAT==b || c_piK_BKGCAT==b || c_Kpi_BKGCAT==b || c_KK_BKGCAT==b || c_Kp_BKGCAT==b)) {
        nBadTruth++;
        continue;
      }
    } 
    if (m_ExpTuple && m_debug) std::cout << "Pass MC" << std::endl ;
    
    if (m_LambdabTuple && !m_LambdabTuple->pid(m_debug)){
      if (m_debug) std::cout << "fails PID" << std::endl ;
      continue ;
    }
    if (m_LambdabTuple && !m_LambdabTuple->trigger()){
      if (m_debug) std::cout << "fails trigger" << std::endl ;
      continue ;
    }

    unsigned int npvs = (m_ExpTuple?(m_allmc?1:m_ExpTuple->PVs):(m_all?1:(m_LambdabTuple->nPVs)));
    if (m_debug) std::cout << "PVs: " << npvs << std::endl ;
    for ( unsigned int pv = 0 ; pv<npvs ; pv++){
      if (m_debug) std::cout << "#### PV " << pv << std::endl ;
      nPairs++ ;
      if (m_LambdabTuple && !m_LambdabTuple->preselection(pv,m_debug)){
        if (m_debug) std::cout << "fails preselection" << std::endl ;
        continue ;
      }
      if (m_ExpTuple && m_ExpTuple->ErrorCode[pv]<0){
        nErrorCode++ ;
        continue ;
      }
      if (m_LambdabTuple && !m_LambdabTuple->PassesMassVetoesForTeaching(pv)){
        if ( m_debug ) std::cout << "Fails vetoes" << std::endl ;
        continue ; 
      } // fails cuts
      int cat = (m_ExpTuple?m_ExpTuple->Category[pv]:m_LambdabTuple->getCategory());
      if (cat!=catCut && !m_allmc) {
        if (m_debug) cout << "Wrong category " << cat << endl ;
        nBadCat++ ;
        continue; 
      }
      /*
      if (!m_unblind && m_ExpTuple && m_ExpTuple->blinded(pv)){
        if (m_debug) std::cout << "Blinded" << std::endl ;
        nBlinded++;
        continue ;       
      }
      */
      double m = 0 ;
      Candidate mca ;
      if (c_PsippiMass==mass->GetName()) m = m_ExpTuple?m_ExpTuple->PsippiMass[pv]:m_LambdabTuple->B_FullFit_M[pv] ;
      else if (c_PsipKMass==mass->GetName()) m = m_ExpTuple?m_ExpTuple->PsipKMass[pv]:m_LambdabTuple->B_SubpK_M[pv];
      else {
        cout << "Unknown " << mass->GetName() << endl ;
        return 0 ;
      }
      if (m_debug) std::cout << "Cat " << cat << " mass " << m 
                             << " netCut " << netCut << " " <<  ErrorCodes::Splitter << std::endl ; 
      if (netCut>ErrorCodes::Splitter){ // do test netcut 
        if (m_debug) std::cout << "Testing netcut versus " << m_ExpTuple->netOutput[pv] << std::endl ;
        if (m_ExpTuple->netOutput[pv]<netCut) {
          nBadNN++ ;
          continue; 
        }
        mca = m_eventMap->randomCandidate(m_ExpTuple->RunNumber, m_ExpTuple->EventNumber);        
      } else if (m_LambdabTuple) {
        mca = m_eventMap->randomCandidate(m_LambdabTuple->runNumber, m_LambdabTuple->eventNumber);        
      }
      
      if (m_debug) std::cout << "DEBUG " << (m_ExpTuple?m_ExpTuple->RunNumber:m_LambdabTuple->runNumber) 
                             << " " << (m_ExpTuple?m_ExpTuple->EventNumber:m_LambdabTuple->eventNumber) << " " << pv 
                             << " MCA: " << mca.first << " " << mca.second << endl ;
      if (-1!=mca.first && ( mca.first!=i || mca.second!=pv) ) {
        if (m_debug) cout << "Candidate " << i << " kept candidate is " 
                          << mca.first << " " << mca.second << endl ;
        if (mca.first!=i) nBadMuCa++ ;
        if (mca.second!=pv) nBadPV++ ;
        continue; 
      }
      //      std::cout << m << " " << mass << std::endl;
      // std::cout << mass->getMin() << std::endl;
      if (m<mass->getMin() || m>mass->getMax()){
        if (m_debug) cout << "Mass out of range " << m << endl ;
        nOutOfRange++ ;
        continue ;
      }
      if (m_debug) std::cout << "Passed selections " << std::endl ;
      category->setVal(cat);
      if (m_ExpTuple && m_ExpTuple->trainingSample() && CatCodes::pKCand==catCut){
        if (m_debug) std::cout << "Used in teaching" << std::endl ;
        nTeaching++;
        continue ;
      }
      if (m_ExpTuple){
	
        if (c_PsippiMass==mass->GetName()) m = m_ExpTuple->PsippiMass[pv] ;
        else if (c_PsipKMass==mass->GetName()) m = m_ExpTuple->PsipKMass[pv];    
        if (m_debug) std::cout << mass->GetName() << " " 
                               << m << std::endl ;
        mass->setVal(m);
        netOutput->setVal(m_ExpTuple->netOutput[pv]);
        baryon->setVal(m_ExpTuple->Baryon);
        m_PsipKMass->setVal(m_ExpTuple->PsipKMass[pv]); // Lb
        m_PsiKpMass->setVal(m_ExpTuple->PsiKpMass[pv]); // Lb
        m_PsippiMass->setVal(m_ExpTuple->PsippiMass[pv]); //Lb
        m_PsiKpiMass->setVal(m_ExpTuple->PsiKpiMass[pv]); // Bd
        m_PsipiKMass->setVal(m_ExpTuple->PsipiKMass[pv]); // Bd
        m_PsiKKMass->setVal(m_ExpTuple->PsiKKMass[pv]); //Bs
        if (m_mc) BKGCAT->setVal(m_ExpTuple->BKGCAT);
        if (m_debug) std::cout << "Adding " << i << " " << cat << " " 
                               << m_ExpTuple->EventNumber << " " << (m_mc?m_ExpTuple->BKGCAT:-1) << std::endl ;
        nGood++;
      } else {
        if (c_PsippiMass==mass->GetName()) m = m_LambdabTuple->B_FullFit_M[pv] ;
        else if (c_PsipKMass==mass->GetName()) m = m_LambdabTuple->B_SubpK_M[pv];    
        if (m_debug) std::cout << mass->GetName() << " = " 
                               << m << std::endl ;
        mass->setVal(m);
        m_PsipKMass->setVal(m_LambdabTuple->B_SubpK_M[pv]); // Lb
        netOutput->setVal(netCut);
        baryon->setVal((m_LambdabTuple->pplus_ID>0)?1:-1);
        if (m_debug) std::cout << "Adding " << i << " " << cat << " " 
                               << m_LambdabTuple->eventNumber << "/" 
                               << m_LambdabTuple->runNumber << " " << mass->getVal() << std::endl ;
        nGood++;
      }
      rd->add(variables);
      if (m_debug) rd->Print("v");
    }
  } // candidates
  
  std::cout << "######################### Results #########################" << std::endl ;
  std::cout                  << "  Number of candidates                    : " << nentries << std::endl;
  if (nBadTruth)   std::cout << "  Number of bad Truth                     : " << nBadTruth << std::endl ;
  std::cout                  << "  Number of pairs                         : " << nPairs << std::endl;
  if (nErrorCode)  std::cout << "    Number of error code pairs            : " << nErrorCode << std::endl;
  if (nBadCat)     std::cout << "    Number of bad category pairs          : " << nBadCat << std::endl;
  if (nBlinded)    std::cout << "    Number of pairs blinded               : " << nBlinded << std::endl;
  if (nBadNN)      std::cout << "    Number of pairs failing cuts          : " << nBadNN << std::endl;
  if (nBadMuCa)    std::cout << "    Number of killed Multiple pairs       : " << nBadMuCa << std::endl ;
  if (nBadPV)      std::cout << "    Number of Multiple PV pairs           : " << nBadPV << std::endl;
  if (nOutOfRange) std::cout << "    Number of bad masses                  : " << nOutOfRange << std::endl ;
  if (nTeaching)   std::cout << "    Number of Teaching pairs              : " << nTeaching << std::endl ;
  std::cout                  << "    Number of Good pairs                  : " << int(rd->sumEntries()) << std::endl;
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
  Double_t wPsippiMass[100], wPsipKMass[100], sweightLb[100], sweightBkg[100];
  Double_t wNetOutput[100], wMass[100], wQ[100] ;
  Double_t sweightKpi[100], sweightpiK[100], sweightKK[100],sweightKp[100], sweightLref[100], sweightNon[100];
  Int_t wCategory[100], wErrorCode[100], wBaryon, wMultiplicity ;
  
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
  outtree->Branch("sweightKpi",    &sweightKpi,  "sweightKpi[wPV]/D");
  outtree->Branch("sweightpiK",    &sweightpiK,  "sweightpiK[wPV]/D");
  outtree->Branch("sweightKK",     &sweightKK,   "sweightKK[wPV]/D");
  outtree->Branch("sweightKp",     &sweightKp,   "sweightKp[wPV]/D");
  outtree->Branch("sweightLref",   &sweightLref, "sweightLref[wPV]/D");
  outtree->Branch("sweightNon",    &sweightNon,  "sweightNon[wPV]/D");
  outtree->Branch("w"+c_Category,  &wCategory,   "w"+c_Category+"[wPV]/I");
  outtree->Branch("w"+c_NetOutput, &wNetOutput,  "w"+c_NetOutput+"[wPV]/D");
  outtree->Branch("w"+c_Baryon,    &wBaryon,     "w"+c_Baryon+"/I");
  outtree->Branch("w"+c_ErrorCode, &wErrorCode,  "w"+c_ErrorCode+"[wPV]/I");
  outtree->Branch("wMultiplicity", &wMultiplicity,"wMultiplicity/I");
  outtree->SetDirectory(m_outfile);
  
  RooDataSet* PsippiData = (m_unblind?m_sData->GetSDataSet():0) ;
  RooDataSet* PsipKData = m_sData_PsipK->GetSDataSet() ;
  const Long64_t nentries = m_ExpTuple->fChain->GetEntries();
  //  RooArgSet *allVar = (m_unblind?(RooArgSet *) PsippiData->get():0);
  //  RooArgSet*  sWeightPsippiVar = (m_unblind?(RooArgSet *) PsippiData->get():0);
  RooArgSet * sWeightPsipKVar = (RooArgSet *) PsipKData->get();
  RooRealVar* sWeightPsipK_mass = (RooRealVar *)sWeightPsipKVar->find(c_PsipKMass);
  
  Long64_t Psippi_entry = 0 ;
  Long64_t PsipK_entry = 0 ;
  int ok = 0;
  double frac = printFrac(nentries/10.);

  int nPPi = (m_unblind?m_sData->GetSDataSet()->sumEntries():0) ;
  int nPK = m_sData_PsipK->GetSDataSet()->sumEntries() ;
  
  for(Long64_t i=0; i<nentries; i++){
    m_ExpTuple->fChain->GetEntry(i);
    m_debug = (257550108==m_ExpTuple->EventNumber);
    if( m_debug || 0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries << " (" 
                                                          << 100*i/nentries << "%)" << std::endl;
    wPV_s = m_ExpTuple->PVs ;
    wBaryon = m_ExpTuple->Baryon ;
    wMultiplicity = m_eventMap->candidatesInEvent(m_ExpTuple->RunNumber, m_ExpTuple->EventNumber);
    for ( unsigned int pv = 0 ; pv<m_ExpTuple->PVs ; pv++){   
      sweightKpi[pv] = -20; sweightpiK[pv] = -20; sweightKK[pv] = -20;
      sweightKp[pv] = -20; sweightLref[pv] = -20, sweightNon[pv] = -20;
      wPsippiMass[pv] = m_ExpTuple->PsippiMass[pv];
      wPsipKMass[pv]  = m_ExpTuple->PsipKMass[pv];
      wCategory[pv] = m_ExpTuple->Category[pv];
      wNetOutput[pv] = m_ExpTuple->netOutput[pv];
      wErrorCode[pv] = m_ExpTuple->ErrorCode[pv];
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
      if ( wNetOutput[pv]>nnCut && wErrorCode[pv]==0 ){        
        Candidate mca = m_eventMap->randomCandidate(m_ExpTuple->RunNumber, m_ExpTuple->EventNumber);
        if ( mca.first>=0 && m_debug) std::cout << "DEBUG:: Multiple Candidate. " 
                                                << i << " Kept is " << mca.first << " " << mca.second << std::endl ;
        if (-1<mca.first && (mca.first!=i || mca.second!=pv) ){
          if (m_debug ) std::cout << "DEBUG:: killed Multiple Candidate. Kept is " << mca.first 
                                  << " " << mca.second << std::endl ;
          sweightLb[pv] = ErrorCodes::KilledMuCa;
          sweightBkg[pv] =  ErrorCodes::KilledMuCa ;
          wErrorCode[pv] = ErrorCodes::KilledMuCa ; // new error code
        } else if (m_ExpTuple->trainingSample() && CatCodes::pKCand== wCategory[pv]){
          if (m_debug) std::cout << "Used in teaching" << std::endl ;
          sweightLb[pv] = ErrorCodes::Teaching;
          sweightBkg[pv] =  ErrorCodes::Teaching ;
          wErrorCode[pv] = ErrorCodes::Teaching ; // new error code
        } else if (CatCodes::SignalCand == wCategory[pv]  &&
                   wPsippiMass[pv]>=m_minMass && wPsippiMass[pv]<=m_maxMass){
          if (m_unblind){
            ok = extractSWeight(c_PsippiName,PsippiData,m_sData,Psippi_entry,
                                sweightLb[pv],sweightNon[pv],
                                sweightKpi[pv], sweightpiK[pv], sweightKK[pv],
                                sweightKp[pv], sweightLref[pv]);
            sweightBkg[pv] = sweightNon[pv]+sweightKpi[pv]+sweightpiK[pv]+sweightKK[pv]+sweightKp[pv]+sweightLref[pv];
            RooRealVar* mass = (RooRealVar *)PsippiData->get()->find(c_PsippiMass);
            if (fabs(mass->getVal()-wPsippiMass[pv])>0.01){
              std::cout << "ERROR:: ppi candidate " << i << " and " << Psippi_entry  << " / " << nPK
                        << " M:" << mass->getVal() << " but should have " << wPsippiMass[pv] << std::endl ;
              return -11 ;
            }
            if (m_debug) std::cout << "DEBUG:: ppi candidate " << i << " and " 
                                   << Psippi_entry << " / " << nPPi
                                   << " M:" << wPsippiMass[pv] << " W = " << sweightLb[pv] << std::endl ;
          } else {
           sweightLb[pv] = ErrorCodes::Blind ;
           sweightBkg[pv] =  ErrorCodes::Blind ;
          }
        } else if (CatCodes::pKCand == wCategory[pv] && 
                   wPsipKMass[pv]>=m_minMass && wPsipKMass[pv]<=m_maxMass){   // fit range is the same
          ok = extractSWeight(c_PsipKName,PsipKData,m_sData_PsipK,PsipK_entry,
                              sweightLb[pv],sweightNon[pv],
                              sweightKpi[pv], sweightpiK[pv], sweightKK[pv],
                              sweightKp[pv], sweightLref[pv]);      
          sweightBkg[pv] = sweightNon[pv]+sweightKpi[pv]+sweightpiK[pv]+sweightKK[pv]+sweightKp[pv]+sweightLref[pv];
          RooRealVar* mass = (RooRealVar *)PsipKData->get()->find(c_PsipKMass);
          if (m_debug) std::cout << "DEBUG: " << sWeightPsipK_mass->getVal() << " and " 
                                 << m_ExpTuple->PsipKMass[pv] << std::endl ;
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
  std::cout << "Reached sWeight entries " << PsipK_entry << " of " << nPK << std::endl ;
  outtree->Write();
  std::cout << "Done" << std::endl ;
  
  return ok ;
}
//=============================================================================
// Write Simple Tree For Training
//=============================================================================
int weighting::writeTrainTree(){

  if (m_debug) std::cout << "INFO :: writeTrainTree" << std::endl ;
  Double_t wMass[100], sweightLb[100], sweightBkg[100] ;
  Int_t wCategory[100];
    
  TTree* outtree = new TTree("TrainTree","Train Tree");
  unsigned int wPV_s  = 0 ;  // do not use the same name as in [wPV] 
  // see http://root.cern.ch/root/roottalk/roottalk03/2873.html
  outtree->Branch("tPV",           &wPV_s,       "tPV/I");
  outtree->Branch("tMass",         &wMass,       "tMass[tPV]/D");
  outtree->Branch("tweightLb",     &sweightLb,   "sweightLb[tPV]/D"); 
  outtree->Branch("tweightBkg",    &sweightBkg,  "sweightBkg[tPV]/D");
  outtree->Branch("t"+c_Category,  &wCategory,   "t"+c_Category+"[tPV]/I");
  outtree->SetDirectory(m_outfile);
  
  if (!m_sData_PsipK) return -1 ;
  RooDataSet* PsipKData = m_sData_PsipK->GetSDataSet() ;
  const Long64_t nentries = (m_debug?10000:m_LambdabTuple->GetEntries(m_debug));
  //  RooArgSet *allVar = (RooArgSet *) PsipKData->get();
  RooArgSet * sWeightPsipKVar = (RooArgSet *) PsipKData->get();
  
  Long64_t PsipK_entry = 0 ;
  int ok = 0;
  double frac = printFrac(nentries/10.);

  int nPK = PsipKData->sumEntries() ;
  
  for(Long64_t i=0; i<nentries; i++){
    m_LambdabTuple->fChain->GetEntry(i);
    if( m_debug || 0==i%((int)(frac*nentries))) 
      std::cout << " |-> " << i << " / " << nentries << " (" 
                << 100*i/nentries << "%) E/R = " << m_LambdabTuple->eventNumber << "/" 
                << m_LambdabTuple->runNumber << std::endl;
    wPV_s = m_LambdabTuple->nPVs ;
    bool pid = m_LambdabTuple->pid();
    bool trigger = m_LambdabTuple->trigger();
    for ( unsigned int pv = 0 ; pv<wPV_s ; pv++){    
      wCategory[pv] = m_LambdabTuple->getCategory();
      wMass[pv] = m_LambdabTuple->B_SubpK_M[pv];
      if (m_debug) std::cout << "DEBUG:: " << i << " M:" << wMass[pv] << " " << wCategory[pv]
                             << " " << " "  << std::endl ;
      if (!pid || !m_LambdabTuple->preselection(pv,m_debug)){
        sweightLb[pv] = ErrorCodes::FailsCuts ;
        sweightBkg[pv] = ErrorCodes::FailsCuts ;
        continue ;
      }
      if (!trigger){	
        sweightLb[pv] = ErrorCodes::FailsTrigger ;
        sweightBkg[pv] = ErrorCodes::FailsTrigger ;
        continue ;
      }
      if (!m_LambdabTuple->PassesMassVetoesForTeaching(pv)){
        sweightLb[pv] = ErrorCodes::Reflection ;
        sweightBkg[pv] = ErrorCodes::Reflection ;
        continue ;
      }
      if (!(pv==0 &&    // only pv 0
            CatCodes::pKCand==wCategory[pv] && 
            wMass[pv]>=m_minMass && wMass[pv]<=m_maxMass )){
        sweightLb[pv] = ErrorCodes::FailsCategory ;
        sweightBkg[pv] = ErrorCodes::FailsCategory ;
        continue ;	
      }
      Candidate mca = m_eventMap->randomCandidate(m_LambdabTuple->runNumber, m_LambdabTuple->eventNumber);
      if (-1<mca.first && (mca.first!=i || mca.second!=pv) ){
        if (m_debug ) std::cout << "DEBUG:: killed Multiple Candidate. Kept is " << mca.first 
                                << " " << mca.second << std::endl ;
        sweightLb[pv] = ErrorCodes::KilledMuCa;
        sweightBkg[pv] =  ErrorCodes::KilledMuCa ;
        continue ;
      }     
      if (nPK<PsipK_entry){
        std::cout << "ERROR : reach beyond last candidate of pK " << nPK << std::endl ;
        return -1 ;
      }
      double d; // dummy
      ok = extractSWeight(c_PsipKName,PsipKData,m_sData_PsipK,PsipK_entry,sweightLb[pv],sweightBkg[pv],d,d,d,d,d);      
      if (0!=ok) return ok;
      RooRealVar* mass = (RooRealVar *)PsipKData->get()->find(c_PsipKMass);
      if (fabs(mass->getVal()-wMass[pv])>0.01){
        std::cout << "ERROR:: pK  candidate " << i  <<  " " << PsipK_entry << " / " << nPK
                  << " M:" << mass->getVal() << " but should have " << wMass[pv] << std::endl ;
        return -11 ;
      } 
      if (m_debug) std::cout << "DEBUG:: pK  candidate " << i << " and " << PsipK_entry  << " / " << nPK
                             << " M:" << wMass[pv] << " W = " << sweightLb[pv] << std::endl ;
    } // pv
    outtree->Fill() ;	
  }
  outtree->Write();
  std::cout << "Done" << std::endl ;
  
  return ok ;
}
//=============================================================================
// extractSWeight(){
//=============================================================================
int weighting::extractSWeight(TString name,RooDataSet* Data, RooStats::SPlot* sData, 
                              Long64_t& jentry, double& sweightLb, double& sweightNon,
                              double& sweightKpi, double& sweightpiK, double& sweightKK,
                              double& sweightKp, double& sweightLref){
  
  if (jentry>=Data->sumEntries()){
    std::cout << "ERROR : " << jentry << " larger than " << Data->sumEntries() << std::endl ;
    return -8 ;
  }
  Data->get(jentry);
  unsigned int n = sData->GetSWeightVars().getSize() ;
  if ( 0 == n ){
    cout << "Error. Sweight has no variables " << endl ;
    return -7 ;
  }
  
  //cout << "Looking for ``" << c_Yield+" "+c_Lambdab << "''" << endl ;
  sweightLb  = sData->GetSWeight(jentry,c_Yield+" "+c_Lambdab);
  //cout << "Looking for ``" << c_Yield+" "+c_NonPeaking << "''" << endl ;
  sweightNon = sData->GetSWeight(jentry,c_Yield+" "+c_NonPeaking);
  if (n>2){  
    //cout << "Looking for ``" << c_Yield+" "+c_PsiKpiMass << "''" << endl ;
    sweightKpi = sData->GetSWeight(jentry,c_Yield+" "+c_PsiKpiMass);
    //cout << "Looking for ``" << c_Yield+" "+c_PsipiKMass << "''" << endl ;
    sweightpiK = sData->GetSWeight(jentry,c_Yield+" "+c_PsipiKMass);
    //cout << "Looking for ``" << c_Yield+" "+c_PsiKKMass << "''" << endl ;
    sweightKK  = sData->GetSWeight(jentry,c_Yield+" "+c_PsiKKMass);
    //cout << "Looking for ``" << c_Yield+" "+c_PsiKpMass << "''" << endl ;
    sweightKp  = sData->GetSWeight(jentry,c_Yield+" "+c_PsiKpMass);
    //cout << "Looking for ``" << c_Yield+" "+c_PsippiMass << "''" << endl ;
    if (name.Contains("Psippi")) sweightLref  =  sData->GetSWeight(jentry,c_Yield+" "+c_PsipKMass);
    if (name.Contains("PsipK")) sweightLref  =  sData->GetSWeight(jentry,c_Yield+" "+c_PsippiMass);
    if (m_debug) std::cout << "Weights are Lb " << sweightLb << ", Non " << sweightNon 
			   << ", Kpi " << sweightKpi
			   << ", piK " << sweightpiK 
			   << ", KK " << sweightKK 
			   << ", Kp " << sweightKp 
			   << ", Lref " << sweightLref 
			   << std::endl ;
  } else if (m_debug){
    std::cout << "Weights are " << sweightLb << " and " << sweightNon << std::endl ;
  }
  
  if (m_debug){
    RooArgList ra = sData->GetSWeightVars();
    cout << "DEBUG :: " << ra.getSize() << " vars are " ;
    for ( unsigned int i=0 ; i<ra.getSize() ; i++) if (ra.at(i)) cout << ra.at(i)->GetName() << " ";
    cout << endl ;
  }
  if (m_debug) std::cout << "DEBUG:: sweight is " << sweightLb << std::endl ;
  /*
  if ( fabs(sweightLb+1<0.0000001) ) {
    RooArgList ra = sData->GetSWeightVars();
    cout << "Error. Sweight is " << sweightLb << ". " << ra.getSize() << " vars are " ;
    for ( unsigned int i=0 ; i<10 ; i++) {
      if (ra.at(i)) cout << ra.at(i)->GetName() << " ";
    }
    cout << " - done " << endl ;
    //    return -1 ;
  }
  */
  jentry++;
  //  cout << "entry now " << jentry << endl ;
  return 0;
}
  
//=============================================================================
// reflection fit on data
//=============================================================================
background* weighting::reflectionFit(TString name, RooRealVar* mass, RooDataSet* data){
  if (m_mc) return 0 ; // no need on MC
  if (!mass || !data) return 0 ;
  if (data->sumEntries()<=0) return 0 ;
  RooDataSet* data2 = 0 ;
  //char ll[100];
  //sprintf(ll,mass->GetName(),">",mass->getMin()); /// else there's a huge spike at minimum
  data2 = (RooDataSet *)data; // ->reduce(TString(ll)
  double n = data2->sumEntries() ;
  double factor = 1;
  if ( c_PsippiName==name ){ // ppi fit has a lot of Kpi
    if (c_PsipiKMass==mass->GetName()) {
      data2 = (RooDataSet *)data->reduce("(abs("+c_PsiKpiMass+"-5279.5)>15)"); // veto Kpi
      factor = 1/c_vetoFactor;
    }
  } else { // pK has a lot to piK
    if (c_PsiKpiMass==mass->GetName()) {
      data2 = (RooDataSet *)data->reduce("(abs("+c_PsipiKMass+"-5279.5)>15)"); // veto piK
      factor = 1/c_vetoFactor;
    }
  }
  std::cout << "Doing reflection fit of " << name << " for " << mass->GetName() << " with " 
	    << n << " entries of " << data->sumEntries() << " " << std::endl ;
  RooRealVar fG("Peak events","Peak events",0.5*n,0.,n);
  RooRealVar fbkg("Bkg events","Bkg events",0.5*n,0.,n);
  double m = m_Lb;
  if (c_PsiKpiMass==mass->GetName() || c_PsipiKMass==mass->GetName()) m=m_Bd;
  else if (c_PsiKKMass==mass->GetName()) m=m_Bs;
  RooRealVar peak("peak","peak",m,m-1.,m+1.); // fixed within 1 mev
  RooRealVar sigma("sigma","core sigma",6.,4.,10);
  RooRealVar peak2("peak2","peak2",m,0,10000.); 
  RooRealVar sigma2("sigma2","sigma2",1000,50.,10000.);
  //RooRealVar slope("slope","slope",0.2,-10.,10.);
  //RooRealVar slope2("slope2","slope2",0.1,-10.,10.);
  //  RooChebychev Bkg("Cheb","RooChebychev",*mass,RooArgList(slope)); // , slope2
  RooGaussian G("G","Gaussian",*mass,peak,sigma);
  RooGaussian Bkg("Bkg","Background",*mass,peak2,sigma2);
  RooAddPdf pdf("pdf","pdf for"+name,RooArgList(G,Bkg),RooArgList(fG,fbkg)); // ));
  RooFitResult* r = pdf.fitTo(*data2,Save(),PrintLevel(-1),Warnings(false), Verbose(false),Range(c_Fittable));
  RooPlot* plotM = mass->frame(Range(c_Fittable),Bins(50));
  data2->plotOn(plotM);
  pdf.plotOn(plotM,LineColor(kMagenta),Range(c_Fittable));
  pdf.plotOn(plotM,LineColor(kRed),LineStyle(kDashed),Range(c_Fittable),Components(G));
  pdf.plotOn(plotM,LineColor(kGreen),LineStyle(kDashed),Range(c_Fittable),Components(Bkg));
  //  pdf.paramOn(plotM,Layout(0.5,0.92,0.92));
  m_outfile->cd();
  plotM->Write("Fit_"+name+"_"+mass->GetName());
  std::cout << (name.Contains(c_PsippiName)?"\\pion":"\\kaon")  << " & " 
            << (m_Lb==m?"\\Lb":(m_Bs==m?"\\Bs":"\\Bd")) << "\\to " 
            << TString(mass->GetTitle()).ReplaceAll("#pi","{\\pi}").ReplaceAll("#psi","{\\psi}").ReplaceAll("Mass","") << " & " 
            << int(fG.getVal()+0.5) << " ! " << int(fG.getError()+0.5) 
            << " & " << 0.1*int(10*fG.getVal()/fG.getError()+0.5) 
            << "\\sigma \\\\"
            << ((name.EndsWith("B_blind")||(name.EndsWith("B")))?"% grepme4 ":"% grepme3 ")  
            << std::endl ;
  r->Print();
  pdf.Print();
  return new background(mass->GetName(),
                        (name.Contains(c_PsippiName)?CatCodes::SignalCand:CatCodes::pKCand),
                        factor*fG.getVal(), factor*fG.getError(), m_NNCut);                               
}
//=============================================================================
// Get background vector
//=============================================================================
backgrounds weighting::getBackgrounds(TString name, RooRealVar* mass, RooDataSet* Data){
  backgrounds bkgVec;
  if (m_ExpTuple){
    std::cout << "\\hline % grepme3" << std::endl ;
    background* b;
    if (name.Contains(c_PsippiName)) b = reflectionFit(name,m_PsipKMass,Data); // pK just for ppi
    else b = reflectionFit(name,m_PsippiMass,Data); // ppi just for pK
    if (b) bkgVec.push_back(b);
    b = reflectionFit(name,m_PsipiKMass,Data); // 
    if (b) bkgVec.push_back(b);
    b = reflectionFit(name,m_PsiKpiMass,Data); // 
    if (b) bkgVec.push_back(b);
    b = reflectionFit(name,m_PsiKKMass,Data); // 
    if (b) bkgVec.push_back(b);
    b = reflectionFit(name,m_PsiKpMass,Data); // 
    if (b) bkgVec.push_back(b);
    m_outfile->cd();
    plotRK(bkgVec,mass,name);
  }
  return bkgVec;
}
//=============================================================================
// plot rookeys
//=============================================================================
void weighting::plotRK(backgrounds& bs, RooRealVar* mass, TString name){
  RooArgList pdfs;
  RooArgList norms;
  for (backgrounds::iterator b = bs.begin(); b!=bs.end() ; ++b){
    if (m_debug) (*b)->pdf()->Print("v");
    if (m_debug) (*b)->yield()->Print("v");
    pdfs.add(*((*b)->pdf()));
    norms.add(*((*b)->yield()));
  }
  RooAddPdf pdf("rk pdf "+TString(mass->GetName()),"rk pdf for"+TString(mass->GetName()),pdfs,norms);
  RooPlot* plotM = mass->frame();
  pdf.plotOn(plotM,LineColor(kMagenta));
  int c = 2;
  for (backgrounds::iterator b = bs.begin(); b!=bs.end() ; ++b){
    pdf.plotOn(plotM,LineColor(c),LineStyle(kDashed),Components(*((*b)->pdf())));
    c++ ;
    if (5==c) c++; // not yellow
    if (6==c) c++; // not magenta
  }
  plotM->Write("RK_"+name+"_"+TString(mass->GetName()));
}

//=============================================================================
// RooKeysPdf Fit for MC
//=============================================================================
int weighting::RKFit(TString name, RooRealVar* mass, RooDataSet* data){
  //
  // @todo weight by Dalitz
  //
  if (!m_mc) return 0 ; // no need on data
  //  if (m_signalmc && !m_signalmc_pi && c_PsipKName==name) return 0 ; // no need to fit peak itself
  if (!mass || !data) return -77;
  if (data->sumEntries()<=0) return 0 ;
  std::cout << "Trying RooKeysPdf for " << name << " with " << data->sumEntries() << " entries " << std::endl ;

  for ( std::vector<TString>::const_iterator b = m_bkgCats.begin() ; b!=m_bkgCats.end() ; ++b){
    if ("1"==*b && c_PsipKName==name) continue ; // no need to fit peak itself
    if ("0"==*b && c_PsippiName==name) continue ; // no need to fit peak itself
    RooDataSet* data2 = (RooDataSet *)data->reduce(*b+"==BKGCAT");  
    if (data2->sumEntries()==0) continue;
    std::cout << "Doing RooKeysPdf for background " << *b+"==BKGCAT"
	      << " with " << data2->sumEntries() << " entries in range " 
	      << mass->getMin() << ":" << mass->getMax() << std::endl ;
    RooKeysPdf rk("RK"+name+*b,"RK"+name+*b,*mass,*data2,RooKeysPdf::NoMirror,1.5); 
    RooPlot* plotM = mass->frame(Bins(50));
    if (name.Contains("c_PsipKName")) plotM->SetXTitle("m_{J/#psipK} [MeV/c^{2}]");
    else if (name.Contains("c_PsippiName")) plotM->SetXTitle("m_{J/#psip#pi} [MeV/c^{2}]");
    plotM->SetTitle("");
    data2->plotOn(plotM);
    rk.plotOn(plotM,LineColor(kMagenta));
    plotM->Write("RK_"+name+"_plot_"+*b);
    rk.Write("RK_"+name+"_pdf_"+*b);
  }
  std::cout << "Done RooKeysPdf" << std::endl ;
  return 0;
}
//=============================================================================
// Fit
//=============================================================================
int weighting::fit(TString name, RooDataSet* data, MassPdf* pdf){
  
  Int_t logy = 0 ;
  if (c_PsipKMass==pdf->mass()->GetName()) logy = 1 ;
  if (m_allmc || m_signalmc) logy = 1 ;
  if (m_all) logy = 0 ;
  if (m_debug) data->get(0)->Print("v");
  RooDataSet* data2 = data ;
  if (!m_allmc){
    if (m_signalmc) {
      if (m_signalmc_pi) {
        data2 = (RooDataSet *)data->reduce("BKGCAT==0") ;
        //	std::cout << "BKGCAT==0" << std::endl ;
      } else {
        data2 = (RooDataSet *)data->reduce("BKGCAT==1") ;
        //	std::cout << "BKGCAT==1" << std::endl ;
      }
    }
  }
  if (data2->sumEntries()==0){
    std::cout << "No entries left after reduction" << std::endl ;
    return 0 ;
  }
  std::cout << "Fitting " << name << " on " << data2->sumEntries() << " entries " << std::endl ;
  std::cout << "Plots will be made in " << (1==logy?"logy":"liny") << " for " << pdf->mass()->GetName() << std::endl ;
  dataPlot(name+"Data4Fit",pdf->mass(),data2);
  std::cout << "#################### FIT " << name << " #######################" << std::endl ;
  RooFitResult* r = pdf->fit(data2,false);
  r->Print();
  TCanvas* getBestPlot1 = new TCanvas(name,"Canvas for MassPlot",600,600);
  RooPlot* r1 = pdf->plotOn(getBestPlot1,data2,kFALSE,logy,false,false); // Plot without Pull
  r1->Write(name);
  getBestPlot1->Write("TC_"+name);
  TCanvas* getBestPlot2 = new TCanvas(name+"B","Canvas for MassPlot",600,600);
  RooPlot* r2 = pdf->plotOn(getBestPlot2,data2,kFALSE,logy,true,false); // Plot without Pull but param
  r2->Write(name+"B");
  getBestPlot2->Write("TC_"+name+"B");
  TCanvas* getBestPlot3 = new TCanvas(name+"C","Canvas for MassPlot",600,600);
  RooPlot* r3 = pdf->plotOn(getBestPlot3,data2,kFALSE,logy,false,true); // Plot with pull
  r3->Write(name+"C");
  getBestPlot3->Write("TC_"+name+"C");
  pdf->Print();
  if (m_debug) std::cout << "#################### FIT " << name << " done #######################" << std::endl ;
  return 0 ;
}
//=============================================================================
// Fit
//=============================================================================
MassPdf* weighting::doAllFits(TString name,RooRealVar* mass, RooDataSet* Data, 
                           const int catCode,double nnCut,bool blinded){
  MassPdf* mFit = doFits(name,mass,Data,catCode, nnCut,blinded,"");
  MassPdf* mFitB = doFits(name,mass,Data,catCode, nnCut,blinded,"B"); // baryons only
  MassPdf* mFitAB = doFits(name,mass,Data,catCode, nnCut,blinded,"AB"); // anti-baryons only
  return mFit ;
}
//=============================================================================
// Fit
//=============================================================================
MassPdf* weighting::doFits(TString name1,RooRealVar* mass, RooDataSet* Data, 
                           const int catCode,double nnCut,bool blinded,TString baryon){
  if (""!=baryon && m_free) return 0 ; /// no need to do baryons
  int ok = 0;
  name1 = name1+baryon ;
  TString name = (blinded?name1+"_blind":name1);
  RooDataSet* DataF = Data ;
  if ("B"==baryon) DataF = (RooDataSet *)Data->reduce(c_Baryon+">0"); // baryon
  else if ("AB"==baryon) DataF = (RooDataSet *)Data->reduce(c_Baryon+"<0"); // Antibaryon

  if (m_debug) std::cout << "DEBUG :: sWeight " << name << std::endl ;
  if (m_debug || DataF->sumEntries()==0) std::cout << "DEBUG :: " << name << " " << mass->GetName() << " " 
						   << DataF->sumEntries() << std::endl ;
  if (DataF->sumEntries()==0) return 0 ;
  backgrounds bkgVec = getBackgrounds(name,mass,DataF) ;
  dataPlot("SelData"+baryon,mass,DataF);
  MassPdf* mFit = new MassPdf(name,mass,DataF->sumEntries(),bkgVec,(m_free?"free":""),(blinded?"Low,High":""),
                              "DoubleCB",(m_ExpTuple?"Exp":"Poly2"),m_withXib);
  if (blinded) {
    mFit->nLambdab()->setVal(0.);
    mFit->nLambdab()->setConstant();
    mFit->setConstant("Signal");
  }
  if (m_mc && !m_allmc) {
    mFit->nNonPeaking()->setVal(0.);
    mFit->nNonPeaking()->setConstant(true);
  }
  ok = fit(name, DataF, mFit); 
  if (0!=ok) return 0;
  if (c_PsipKName==name1) mFit->Print(m_LbK_s,m_LbK_e,c_trainFrac);  // this defines m_LbK_s,m_LbK_e using trainfrac
  else if (c_PsipKName+"B"==name1) mFit->Print(m_LbKB_s,m_LbKB_e,c_trainFrac);  
  else if (c_PsipKName+"AB"==name1) mFit->Print(m_LbKAB_s,m_LbKAB_e,c_trainFrac);  
  else if (c_PsippiName==name1) mFit->Print(m_Lbpi_s,m_Lbpi_e,1.);  
  else if (c_PsippiName+"B"==name1) mFit->Print(m_LbpiB_s,m_LbpiB_e,1.);  
  else if (c_PsippiName+"AB"==name1) mFit->Print(m_LbpiAB_s,m_LbpiAB_e,1.);  
  else {
    std::cout << "ERROR in Fit Results " << name << " " << baryon << endl ;
    return 0 ;
  }

  return mFit ;
}

//=============================================================================
// BFs
//=============================================================================
void weighting::printBFs(double nnCut){
  cout << "\n\n%%% Yields with NN cut = " << nnCut << endl ;
  cout << "The fit on the full sample yields:\n" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
  cout << "N(\\LbK) & = & " << round(m_LbK_s,1.) << " \\pm " << round(m_LbK_e,1.)
       << "\\quad (" << round(100*m_LbK_e/m_LbK_s,0.01) << "\\%) \\\\ % grepme2" << endl ;
  if (m_unblind){
    cout << "N(\\Lbpi) & = & " << round(m_Lbpi_s,1.) << " \\pm " << round(m_Lbpi_e,1.) 
	 << "\\quad (" << round(100*m_Lbpi_e/m_Lbpi_s,0.1) << "\\%) \\\\ % grepme1" << endl ;
    double r = m_Lbpi_s/m_LbK_s ;
    double e = r*sqrt((m_LbK_e/m_LbK_s)*(m_LbK_e/m_LbK_s)+(m_Lbpi_e/m_Lbpi_s)*(m_Lbpi_e/m_Lbpi_s)) ;
    cout << "\\frac{N(\\Lbpi)}{N(\\LbK)} & = & " << round(r,0.0001) << " \\pm " << round(e,0.0001) 
	 << "\\quad (" << round(100*e/r,0.1) << "\\%)" << endl ;
  }
  cout << "\\end{eqnarray*}" << endl ;

  cout << "\n%%% Baryons " << endl ;
  cout << "Only for baryons:\n" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
    cout << "N(\\LbKm) & = & " << round(m_LbKB_s,1.) << " \\pm " << round(m_LbKB_e,1.) 
	 << "\\quad (" << round(100*m_LbKB_e/m_LbKB_s,0.01) << "\\%) \\\\" << endl ;
  if (m_unblind){
    cout << "N(\\Lbpim) & = & " << round(m_LbpiB_s,1.) << " \\pm " << round(m_LbpiB_e,1.) 
	 << "\\quad (" << round(100*m_LbpiB_e/m_LbpiB_s,0.1)
	 << "\\%) \\\\" << endl;
    double r = m_LbpiB_s/m_LbKB_s ;
    double e = r*sqrt((m_LbKB_e/m_LbKB_s)*(m_LbKB_e/m_LbKB_s)+(m_LbpiB_e/m_LbpiB_s)*(m_LbpiB_e/m_LbpiB_s)) ;
    cout << "\\frac{N(\\Lbpim)}{N(\\LbKm)} & = & " << round(r,0.0001) << " \\pm " << round(e,0.0001) 
	 << "\\quad (" << round(100*e/(r),0.1) << "\\%)" << endl ;
  }
  cout << "\\end{eqnarray*}" << endl ;
  
  cout << "\n%%% Anti-Baryons " << endl ;
  cout << "Only for anti-baryons:\n" << endl ;
  cout << "\\begin{eqnarray*}" << endl ;
  cout << "N(\\LbbKp) & = & " << round(m_LbKAB_s,1.) << " \\pm " << round(m_LbKAB_e,1.) 
       << "\\quad (" << round(100*m_LbKAB_e/m_LbKAB_s,0.01) 
       << "\\%) \\\\" << endl ;
  if (m_unblind){
    cout << "N(\\Lbbpip) & = & " << round(m_LbpiAB_s,1.) << " \\pm " << round(m_LbpiAB_e,1.) 
	 << "\\quad (" << round(100*m_LbpiAB_e/m_LbpiAB_s,0.1)
	 << "\\%) \\\\" << endl;
    double r = m_LbpiAB_s/m_LbKAB_s ;
    double e = sqrt((m_LbKAB_e/m_LbKAB_s)*(m_LbKAB_e/m_LbKAB_s)+(m_LbpiAB_e/m_LbpiAB_s)*(m_LbpiAB_e/m_LbpiAB_s))*r ;
    cout << "\\frac{N(\\Lbbpip)}{N(\\LbbKp)} & = & " << round(r,0.0001) << " \\pm " << round(e,0.0001) 
	 << "\\quad (" << round(100*e/(r),0.1) << "\\%)" << endl ;
  }
  cout << "\\end{eqnarray*}" << endl ;
  
  if (m_unblind){
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
    double e = sqrt(aKe*aKe+apie*apie);
    cout << "\\Delta A_{CP} & = & (" << round(100*(aK-api),0.1) << " \\pm " << round(100*e,0.1) 
	 << ")\\%\\quad (" << round((aK-api)/e,0.1) << "\\sigma)" << endl ;
    cout << "\\end{eqnarray*}" << endl ;
  }
}
//=============================================================================
// Weighting
//=============================================================================
int weighting::weight(){

  if (m_stop) {
    std::cout << "Stopping now" << endl ;
    return -5 ;
  }
  int ok = 0 ;
  //  m_allData = getDataSet(m_allMass);
  double nnCut = getNNCut();
  cout << "Neural net cut to be applied will be " << nnCut << endl ;  
  /*
   * @todo: Make the Kpi fit first, freeze the tails (now fixed)
   * Write sWeighting of Kpi. Check TisTos for signal and background.
   * There may be some more preselection cuts to apply.
   */
  if (!m_first) m_eventMap = createEventMap(m_ExpTuple, nnCut,m_debug) ;
  else m_eventMap = createEventMap(m_LambdabTuple,true,m_debug) ;
  /*
   * Kpi hypothesis
   */
  // *** sWeight Magic ***
  MassPdf* pdf_pK = 0 ;
  RooDataSet* Data = getDataSet(m_PsipKMass,CatCodes::pKCand,nnCut,true);
  if (!m_mc || (m_signalmc && !m_signalmc_pi)){
    pdf_pK = doAllFits(c_PsipKName,m_PsipKMass,Data,CatCodes::pKCand,nnCut,false);
    if (!pdf_pK ){
      if (!m_mc) {
        m_outfile->Close();
        return -5 ;
      }
    } 
  }
  ok = RKFit(c_PsipKName,m_PsipKMass,Data);
  if (0!=ok) return ok ;
  /*
   * Psippi hypothesis
   */
  // *** sWeight Magic ***
  MassPdf* pdf_ppi = 0 ;
  if ( m_ExpTuple ){
    RooDataSet* Data2 = getDataSet(m_PsippiMass,CatCodes::SignalCand,nnCut,true);
    if (!m_mc || m_signalmc_pi){
      pdf_ppi = doAllFits(c_PsippiName,m_PsippiMass,Data2,CatCodes::SignalCand,nnCut,!m_unblind);
      if (!pdf_ppi && !m_mc ) return -5 ;
    }
    ok = RKFit(c_PsippiName,m_PsippiMass,Data2);
    if (0!=ok) return ok ;  
  }

  if ( !m_notree && m_ExpTuple && !m_mc){
    if (pdf_pK) m_sData_PsipK = new RooStats::SPlot(c_PsipKName+"sData",c_PsipKName+"sData", *Data, 
						    pdf_pK->pdf(), pdf_pK->fracPdfList());
    if (pdf_ppi && m_unblind) m_sData = new RooStats::SPlot(c_PsippiName+"sData",c_PsippiName+"sData", *Data, 
							    pdf_ppi->pdf(), pdf_ppi->fracPdfList());
    ok = writeTree(nnCut);
    if (0!=ok) return ok;
  } else if (m_LambdabTuple){
    if (pdf_pK) m_sData_PsipK = new RooStats::SPlot(c_PsipKName+"sData",c_PsipKName+"sData", *Data, 
						    pdf_pK->pdf(), pdf_pK->fracPdfList());
    ok = writeTrainTree();
  }
  
  if (m_ExpTuple && !m_mc) printBFs(nnCut);

  m_outfile->Close();
  std::cout << "Weighting Done. Returning " << ok << std::endl;
  return ok;
  
}
//=============================================================================
// *** Main ***
int main(int argc, char** argv) {

  if(argc<3){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./weighting.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-S20r1-980.root " 
              << " [ " << c_All << " ] [ | notree | debug ]" 
              << " | tee test-weighting-all" << std::endl;  
    std::cout << "or" << std::endl;  
    std::cout << "./weighting.exe Lambdab-S20r1-980-NN.root Lambdab-S20-982-NN.root  " 
              << " [ 0.8 | " << c_Opt << " ] [ | notree | debug | allmc | free | withXib | " << c_unblind << " ]" 
              << " | tee test-weighting" << std::endl;  
    return -9;
  }

  TString a1 = TString(argv[1]);
  TString a2 = (argc>2)?TString(argv[2]):"";
  TString a3 = (argc>3)?TString(argv[3]):"";
  TString a4 = (argc>4)?TString(argv[4]):"";

  // *** Decode Arguments ***
  TString fullname1 = a1 ;
  TString fullname2 = "" ;
  TString what = "";
  TString opt = "";
  if (a2.Contains(".root")){
    fullname2 = a2 ;
    what = a3 ;
    opt  = a4 ;
  } else {
    what = a2 ;
    opt  = a3 ;
  }

  std::cout << "Configured weighting with file1: ``" << fullname1 
	    << " file2: ``" << fullname2 << "'', what ``" 
            << what << "'', opt ``" << opt << "''" << std::endl ;

  make_canvas();
  weighting w(fullname1,fullname2,what,opt);

  return w.weight();
}
