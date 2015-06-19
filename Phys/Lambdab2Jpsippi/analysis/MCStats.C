// Include files 

#include "TTree.h"
#include "TCut.h"
#include <iostream>

using namespace std ;

void printEbRule(double v, double e){  ///< prints v\pm e with correct number of signif digits
  std::cout << ebRule(v,e) << " ! " << ebRule(e) ;
}
double ebRule(double e){ return ebRule(e,e); }  ///< display only the error
double ebRule(double v, double e){   // v is the value, e the error
  if (e<=0.) return v;
  double j = int(log(e/3.5449999)/log(10.)-1); // not exactly EB rule
  double f = pow(10,j);
  double v2 = f*int(v/f+0.5);
  // std::cout << "\n EbRule " << e << " " << e/0.35449999 << " " << j << " " << f << " " << v2 << "\n" << std::endl;
  return v2 ;
}

double SingleStats(TTree* T, TCut cut, double& n1, double& r, double& e ){
  double n2 = T->GetEntries(cut) ;
  r = n2/n1 ;
  e = sqrt(r*(1-r)/n1);
  // cout << n2 << " & " << r << " ! " << e << " & " ;
  cout << n2 << " & " ;
  printEbRule(100*r,100*e);  
  cout << " & " ;
  n1 = n2 ; // return 
  
}

void DoubleStats(TTree* Pi, TTree* K, TCut cutPi, TCut cutK, double& np, double& nk ){
  double rp, ep, rk, ek;
  SingleStats(Pi,cutPi,np,rp,ep);
  SingleStats(K, cutK, nk,rk,ek);
  double f = rk/rp ;
  double e = sqrt((ep/rp)*(ep/rp)+(ek/rk)*(ek/rk))*f ;
  printEbRule(f,e);
  cout << "\\\\" << endl ;
}

void MCStats(TTree* MCPi, TTree* MCK, TTree* Pi, TTree* K){
  
  TCut KReco("Kminus_Reconstructed==1 && muminus_Reconstructed==1 && muplus_Reconstructed==1 && pplus_Reconstructed==1");
  TCut PiReco("piminus_Reconstructed==1 && muminus_Reconstructed==1 && muplus_Reconstructed==1 && pplus_Reconstructed==1");
  TCut PsiMass("abs("+PsiM+"-3096.916)<80");

  double nP = MCPi->GetEntries();
  double nK = MCK->GetEntries();
  double nP2 = nP/0.1564;  // from generation stats
  double nK2 = nK/0.1637 ;
  cout << "\n\\tt MCDecayTreeTuple & " << int(nP) << " & & " << int(nK) << " & & \\\\" << endl ;
  cout << "Reconstructed & " ;
  DoubleStats(MCPi,MCK,PiReco,KReco,nP,nK);
  cout << "Mass windows & " ;
  DoubleStats(MCPi,MCK,PiReco && PsiMass && "abs("+BMpi+"-5620)<500",KReco && PsiMass && "abs("+BMKasPi+"-5620)<500",nP,nK);
  cout << "Stripped  & "  ;
  DoubleStats(Pi,K,"BKGCAT==0","BKGCAT==1",nP,nK);
  cout << "Stream & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1","BKGCAT==1 && Category==-1",nP,nK);
  cout << "Preselected & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-10","BKGCAT==1 && Category==-1 && ErrorCode>-10",nP,nK);
  cout << "Triggered & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-9","BKGCAT==1 && Category==-1 && ErrorCode>-9",nP,nK);
  //cout << "Passes Vetoes 8 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-8","BKGCAT==1 && Category==-1 && ErrorCode>-8",nP,nK);
  cout << "Passes \\Lz Veto & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-7","BKGCAT==1 && Category==-1 && ErrorCode>-7",nP,nK);
  cout << "Passes \\Pphi Veto  & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-6","BKGCAT==1 && Category==-1 && ErrorCode>-6",nP,nK);
  //cout << "Passes Vetoes 5 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-5","BKGCAT==1 && Category==-1 && ErrorCode>-5",nP,nK);
  //cout << "Passes Vetoes 4 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode>-4","BKGCAT==1 && Category==-1 && ErrorCode>-4",nP,nK);
  //cout << "Passes Vetoes 0 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode==0","BKGCAT==1 && Category==-1 && ErrorCode==0",nP,nK);
  cout << "Passes NN & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode==0 && netOutput>0.552",
              "BKGCAT==1 && Category==-1 && ErrorCode==0 && netOutput>0.552",nP,nK);
  cout << "\\hline{}Overall & "  ;
  DoubleStats(Pi,K,"BKGCAT==0 && Category==1 && ErrorCode==0 && netOutput>0.552",
              "BKGCAT==1 && Category==-1 && ErrorCode==0 && netOutput>0.552",nP2,nK2);
}
