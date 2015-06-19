#include <iostream>
#include "TTree.h"
#include "TCut.h"
#include "TPad.h"
#include "TH1D.h"
void Trigger(TTree* T, TTree* Tpi, TTree* TK, TString var, TCut req, TCut otherT, TH1D* trigger, 
             TString label ="", double prec=1000.){
  
  TCut ok("(ErrorCode[0]==-9 || ErrorCode[0]==0)");
  TCut NNCut("netOutput[0]>0.552");
  TString common = TString("(")+TString(ok.GetTitle())+TString(")*(")+TString(req.GetTitle())+TString(")*(")+
    TString(NNCut.GetTitle())+TString(")") ;
  TString commonNoReq = TString("(")+TString(ok.GetTitle())+TString(")*(")+TString(NNCut.GetTitle())+TString(")") ;
                                        //  cout << common << endl ;
  TCut KSig(TString("sweightLb[0]*(sweightLb[0]>-3)*(Category[0]==-1)*(runNumber>110000)*")+common) ;
  TCut Ktrue(common+"*(Category[0]==-1)*(BKGCAT==1)") ;
  TCut Pitrue(common+"*(Category[0]==1)*(BKGCAT==0)");
  TCut KtrueW( TString("(")+TString(Ktrue.GetTitle())+TString(")*(DalitzWeight2[0]*PTWeight[0]*SPDWeight[0])"));
  TCut PitrueW(TString("(")+TString(Pitrue.GetTitle())+TString(")*(DalitzWeight2[0]*PTWeight[0]*SPDWeight[0])"));
  // std::cout << Ktrue.GetTitle() << std::endl ;

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
  T->Draw(var+" >> trigger",KSig) ;
  double mT = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double mTE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;
  T->Draw("("+TString(otherT.GetTitle())+")*("+var+") >> trigger",KSig) ;  // no requirement
  double fT = (100./prec)*int(prec*trigger->GetMean()+0.5) ;
  double fTE = (100./prec)*int(prec*trigger->GetMeanError()+0.5) ;
  if (""==label){
    label = var.ReplaceAll("Decision","").ReplaceAll("B_Hlt","Hlt").
      ReplaceAll("Psi_Hlt","Hlt").ReplaceAll("B_L0","L0").ReplaceAll("_TOS","");
  }
  cout << " \\tt " << label
       << " & " << mTpi << " ! " << mTpiE 
       << " & " << mTpiW << " ! " << mTpiWE
       << " & " << mTK << " ! " << mTKE 
       << " & " << mTKW << " ! " << mTKWE 
       << " & " << mT << " ! " << mTE 
       << " & " << fT << " ! " << fTE 
       << " \\\\ " << endl ;
  
}
//==================================================================================
void AllTrigger(TTree* T, TTree* Tpi, TTree* TK, TCut L0, TCut Hlt1, TCut Hlt2){
  TH1D trigger("trigger","trigger",2,-0.5,1.5);
  Trigger(T,Tpi,TK,"B_L0MuonDecision_TOS","(B_L0Global_TIS==1)","1",&trigger);
  Trigger(T,Tpi,TK,"B_L0DiMuonDecision_TOS","(B_L0Global_TIS==1)",
          "B_L0MuonDecision_TOS==0",&trigger);
  //Trigger(T,Tpi,TK,"B_L0HadronDecision_TIS","(B_L0Global_TIS==1)",
  //        "B_L0MuonDecision_TOS+B_L0DiMuonDecision_TOS==0",&trigger);
  //Trigger(T,Tpi,TK,"B_L0MuonDecision_TIS","(B_L0Global_TIS==1)",
  //        "B_L0MuonDecision_TOS+B_L0DiMuonDecision_TOS+B_L0HadronDecision_TIS==0",&trigger);
  //  Trigger(T,Tpi,TK,"B_L0DiMuonDecision_TIS","(B_L0Global_TIS==1)",
  //        "B_L0MuonDecision_TOS+B_L0DiMuonDecision_TOS==0",&trigger);
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,L0.GetTitle(),"(B_L0Global_TIS==1)","1",&trigger,"L0");
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,"Psi_Hlt1TrackMuonDecision_TOS",L0 && "B_Hlt1Global_TIS==1","1",&trigger);
  Trigger(T,Tpi,TK,"B_Hlt1TrackAllL0Decision_TOS",L0 && "B_Hlt1Global_TIS==1",
          "Psi_Hlt1TrackMuonDecision_TOS==0",&trigger);
  Trigger(T,Tpi,TK,"Psi_Hlt1DiMuonHighMassDecision_TOS",L0 && "B_Hlt1Global_TIS==1",
          "Psi_Hlt1TrackMuonDecision_TOS+B_Hlt1TrackAllL0Decision_TOS==0",&trigger);
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,Hlt1.GetTitle(),L0 && "B_Hlt1Global_TIS==1","1",&trigger,"Hlt1");
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,"B_Hlt2DiMuonDetachedJPsiDecision_TOS",Hlt1 && "B_Hlt2Global_TIS==1","1",&trigger);
  Trigger(T,Tpi,TK,"B_Hlt2DiMuonJPsiHighPTDecision_TOS",Hlt1 && "B_Hlt2Global_TIS==1",
          "B_Hlt2DiMuonDetachedJPsiDecision_TOS==0",&trigger);
  Trigger(T,Tpi,TK,"B_Hlt2DiMuonJPsiDecision_TOS",Hlt1 && "B_Hlt2Global_TIS==1",
          "B_Hlt2DiMuonDetachedJPsiDecision_TOS+B_Hlt2DiMuonJPsiHighPTDecision_TOS==0",&trigger);
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,Hlt2.GetTitle(),Hlt1 && "B_Hlt2Global_TIS==1","1",&trigger,"Hlt2");
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  Trigger(T,Tpi,TK,Hlt2.GetTitle(), "B_Hlt2Global_TIS==1 && B_Hlt1Global_TIS==1 && B_L0Global_TIS==1",
          "1",&trigger,"Trigger");
  cout << "\\hline" << endl ;
  cout << "\\hline" << endl ;
  
  cout << "\n\n" << endl ;
  Trigger(T,Tpi,TK,L0.GetTitle(), "(B_L0Global_TIS==1)","1",&trigger,"L0 & ",100000.);
  Trigger(T,Tpi,TK,Hlt1.GetTitle(),L0 && "B_Hlt1Global_TIS==1","1",&trigger,"Hlt1 & ",100000.);
  Trigger(T,Tpi,TK,Hlt2.GetTitle(),Hlt1 && "B_Hlt2Global_TIS==1","1",&trigger,"Hlt2& ",100000.);
 
}

