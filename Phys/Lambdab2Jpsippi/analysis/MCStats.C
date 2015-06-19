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

double SingleStats(TH1D* hh,TTree* T, TCut cut, double& n1, double& r, double& e, TString weight ){
  T->Draw("1 >> hh",TString(cut.GetTitle())+"*"+weight);
  double n2 = hh->GetSumOfWeights();
  r = n2/n1 ;
  e = sqrt(r*(1-r)/n1);
  // cout << n2 << " & " << r << " ! " << e << " & " ;
  cout << int(n2+0.5) << " & " ;
  printEbRule(100*r,100*e);  
  cout << " & " ;
  n1 = n2 ; // return 
  
} ;

void DoubleStats(TH1D* hh,TTree* Pi, TTree* K, TCut cutPi, TCut cutK, double& np, double& nk, TString weight ){
  double rp, ep, rk, ek;
  SingleStats(hh,Pi,cutPi,np,rp,ep,weight);
  SingleStats(hh,K, cutK, nk,rk,ek,weight);
  double f = rk/rp ;
  double e = sqrt((ep/rp)*(ep/rp)+(ek/rk)*(ek/rk))*f ;
  printEbRule(f,e);
  cout << "\\\\" << endl ;
} ;

//======================================================================================
void MCStats(TTree* MCPi, TTree* MCK, TTree* Pi, TTree* K, TString weight){

  cout << "% weight is " << weight << " %%%%%%%%%%%%%%%%%%%%%%%%%% " << endl ; 
  TString weight0 = weight;
  weight0.ReplaceAll("B_TRUETAU","Lambda_b0_TRUETAU");
  
  TCut KReco("(Kminus_Reconstructed==1)*(muminus_Reconstructed==1)*(muplus_Reconstructed==1)*(pplus_Reconstructed==1)");
  TCut PiReco("(piminus_Reconstructed==1)*(muminus_Reconstructed==1)*(muplus_Reconstructed==1)*(pplus_Reconstructed==1)");
  TCut PsiMass("abs("+PsiM+"-3096.916)<80");
  TH1D* hh =  new TH1D("hh","hh",1,0.5,1.5);

  MCPi->Draw("1 >> hh",weight0);
  double nP = hh->GetSumOfWeights();
  MCK->Draw("1 >> hh",weight0);
  double nK = hh->GetSumOfWeights();
  double nP2 = nP/0.1564;  // from generation stats
  double nK2 = nK/0.1637 ;
  if ("1"!=weight){
    nP2 = nP/0.159777;  // from generation stats
    nK2 = nK/0.16916 ;
  }
  cout << "\nMC Tuple & \\multicolumn{2}{|L}{" << int(nP) << "} &  \\multicolumn{2}{|L|}{" << int(nK) << "} & \\\\" << endl ;
  cout << "Reconstructed & " ;
  DoubleStats(hh,MCPi,MCK,PiReco,KReco,nP,nK,weight0);  // MCWeight
  //cout << "Mass windows & " ;
  //DoubleStats(hh,MCPi,MCK,PiReco)*(PsiMass)*("abs("+BMpi+"-5620)<500",KReco)*(PsiMass)*("abs("+BMKasPi+"-5620)<500",nP,nK);
  cout << "Stripped  & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)","(BKGCAT==1)",nP,nK,weight);
  cout << "Stream & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)","(BKGCAT==1)*(Category==-1)",nP,nK,weight);
  cout << "Preselected & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)*(ErrorCode>-10)","(BKGCAT==1)*(Category==-1)*(ErrorCode>-10)",nP,nK,weight);
  cout << "Triggered & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)*(ErrorCode>-9)","(BKGCAT==1)*(Category==-1)*(ErrorCode>-9)",nP,nK,weight);
  //cout << "Passes Vetoes 8 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0)*(Category==1)*(ErrorCode>-8)","BKGCAT==1)*(Category==-1)*(ErrorCode>-8)",nP,nK);
  cout << "Passes \\Lz Veto & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)*(ErrorCode>-7)","(BKGCAT==1)*(Category==-1)*(ErrorCode>-7)",nP,nK,weight);
  cout << "Passes \\Pphi Veto  & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)*(ErrorCode>-6)","(BKGCAT==1)*(Category==-1)*(ErrorCode>-6)",nP,nK,weight);
  //cout << "Passes Vetoes 5 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0)*(Category==1)*(ErrorCode>-5)","BKGCAT==1)*(Category==-1)*(ErrorCode>-5)",nP,nK);
  //cout << "Passes Vetoes 4 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0)*(Category==1)*(ErrorCode>-4)","BKGCAT==1)*(Category==-1)*(ErrorCode>-4)",nP,nK);
  //cout << "Passes Vetoes 0 & "  ;
  //DoubleStats(Pi,K,"BKGCAT==0)*(Category==1)*(ErrorCode==0)","BKGCAT==1)*(Category==-1)*(ErrorCode==0)",nP,nK);
  cout << "Passes NN & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)*(ErrorCode==0)*(netOutput>0.552)",
              "(BKGCAT==1)*(Category==-1)*(ErrorCode==0)*(netOutput>0.552)",nP,nK,weight);
  cout << "\\hline{}Overall & "  ;
  DoubleStats(hh,Pi,K,"(BKGCAT==0)*(Category==1)*(ErrorCode==0)*(netOutput>0.552)",
              "(BKGCAT==1)*(Category==-1)*(ErrorCode==0)*(netOutput>0.552)",nP2,nK2,weight);
}
//======================================================================================
double reweightedAcceptance(TTree* PH, TTree* TH, int nb, TString weight = "DalitzWeight*PTWeight2"){
  
  TH2D* ha = Make2DPlot("ha","m'",nb,0,1,"#theta'",nb,0,1);
  TH2D* hc = Make2DPlot("hc","m'",nb,0,1,"#theta'",nb,0,1);
  TProfile2D* pw = new TProfile2D("pw","",nb,0,1,nb,0,1);
  
  PH->Draw("thetaprime:mprime >> ha");
  TH->Draw("thetaprime:mprime >> hc");

  double na = ha->GetSumOfWeights();
  double nc = hc->GetSumOfWeights();
  double r = nc/na ;
  cout << " Unweighted: " << na << " " << nc << " " << r << endl ;

  TH->Draw(weight+":thetaprime:mprime >> pw");
  ha->Multiply(pw);
  hc->Multiply(pw);
  
  double na2 = ha->GetSumOfWeights();
  double nc2 = hc->GetSumOfWeights();
  double r2 = nc2/na2 ;
  double e = r2/r ;
  cout << " Weighted: " << na2 << " " << nc2 << " " << r2 << " effect: " << e << endl ;

  ha->Divide(hc);
  ha->Draw("COL");
  return e;
  
}
