#include <iostream>
#include "TTree.h"
#include "TCut.h"
#include "TPad.h"
#include "TH1D.h"
void Trigger(TTree* T, TTree* Tpi, TTree* TK, TString var, TCut req, TCut NNCut, TH1D* trigger, double prec=1000.){
  
  TCut KSig(TString("sweightLb*(sweightLb>-5)*(wCategory==-1)*(")+TString(req.GetTitle())+TString(")")) ;
  TCut Ktrue(req && NNCut && "Category==-1 && BKGCAT==1") ;
  TCut Pitrue(req && NNCut && "Category==1 && BKGCAT==0");
  TCut KtrueW( TString("(")+TString(Ktrue.GetTitle())+TString(")*(MCWeight)"));
  TCut PitrueW(TString("(")+TString(Pitrue.GetTitle())+TString(")*(MCWeight)"));
  // std::cout << KSig.GetTitle() << std::endl ;

  T->Draw(var+" >> trigger",KSig) ;
  double mT = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double mTE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;
  TK->Draw(var+" >> trigger",Ktrue) ;
  double mTK = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double mTKE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;
  TK->Draw(var+" >> trigger",KtrueW) ;
  double mTKW = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double mTKWE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;
  Tpi->Draw(var+" >> trigger",Pitrue) ;
  double mTpi = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double mTpiE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;
  Tpi->Draw(var+" >> trigger",PitrueW) ;
  double mTpiW = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double mTpiWE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;

  TString variable = var.ReplaceAll("Decision","").ReplaceAll("_"," & ").ReplaceAll("BHlt","Hlt").ReplaceAll("PsiHlt","Hlt").ReplaceAll("BL0","L0");
  cout << " \\tt " << variable 
	    << " & " << mTpi << " \\pm " << mTpiE 
	    << " & " << mTpiW << " \\pm " << mTpiWE 
	    << " & " << mTK << " \\pm " << mTKE 
	    << " & " << mTKW << " \\pm " << mTKWE 
	    << " & " << mT << " \\pm " << mTE 
	    << " \\\\ " << endl ;

}
void AllTrigger(TTree* T, TTree* Tpi, TTree* TK, TCut NNCut, TCut L0, TCut Hlt1, TCut Hlt2){
  TH1D trigger("trigger","trigger",2,-0.5,1.5);
  Trigger(T,Tpi,TK,"BL0DiMuonDecision_TOS","(BL0ElectronDecision_TIS==1)",netCut,&trigger);
  Trigger(T,Tpi,TK,"BL0MuonDecision_TOS","(BL0ElectronDecision_TIS==1)",netCut,&trigger);
  Trigger(T,Tpi,TK,"BL0DiMuonDecision_TIS","(BL0ElectronDecision_TIS==1)",netCut,&trigger);
  Trigger(T,Tpi,TK,"BL0MuonDecision_TIS","(BL0ElectronDecision_TIS==1)",netCut,&trigger);
  Trigger(T,Tpi,TK,"BL0HadronDecision_TIS","(BL0ElectronDecision_TIS==1)",netCut,&trigger);
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,L0.GetTitle(),"(BL0ElectronDecision_TIS==1)",netCut,&trigger);
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,"PsiHlt1TrackMuonDecision_TOS",L0 && "BHlt1Global_TIS==1",netCut,&trigger);
  Trigger(T,Tpi,TK,"PsiHlt1DiMuonHighMassDecision_TOS",L0 && "BHlt1Global_TIS==1",netCut,&trigger);
  Trigger(T,Tpi,TK,"BHlt1TrackAllL0Decision_TOS",L0 && "BHlt1Global_TIS==1",netCut,&trigger);
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,Hlt1.GetTitle(),L0 && "BHlt1Global_TIS==1",netCut,&trigger);
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,"BHlt2DiMuonDetachedJPsiDecision_TOS",Hlt1 && "BHlt2Global_TIS==1",netCut,&trigger);
  Trigger(T,Tpi,TK,"BHlt2DiMuonJPsiDecision_TOS",Hlt1 && "BHlt2Global_TIS==1",netCut,&trigger);
  Trigger(T,Tpi,TK,"BHlt2DiMuonJPsiHighPTDecision_TOS",Hlt1 && "BHlt2Global_TIS==1",netCut,&trigger);
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,Hlt2.GetTitle(),Hlt1 && "BHlt2Global_TIS==1",netCut,&trigger);
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,Hlt2.GetTitle(), "BHlt2Global_TIS==1 && BHlt1Global_TIS==1 && BL0ElectronDecision_TIS==1",netCut,&trigger);
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  
  cout << "\n\n" << endl ;
  Trigger(T,Tpi,TK,L0.GetTitle(), "(BL0ElectronDecision_TIS==1)",netCut,&trigger,100000.);
  Trigger(T,Tpi,TK,Hlt1.GetTitle(),L0 && "BHlt1Global_TIS==1",netCut,&trigger,100000.);
  Trigger(T,Tpi,TK,Hlt2.GetTitle(),Hlt1 && "BHlt2Global_TIS==1",netCut,&trigger,100000.);
 
}

