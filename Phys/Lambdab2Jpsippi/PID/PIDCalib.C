#include "TTree.h"

void PIDCalib(TString what, TTree* piPCD20, TTree* KPCD20, TString piVar = "Pi_PIDCalibEff", 
              TString KVar = "K_PIDCalibEff", TString pol = "(1)"){
  
  if (!(what.Contains("&"))) what = what+" & ";
  double pe, ke ;
  piPCD20->Draw(piVar,"nsig_sw*"+pol) ;
  double pm = int(10000*htemp->GetMean()+0.5)/100.  ; 
  if (piVar.Contains("_PIDCalibEff")){
    piPCD20->Draw(piVar+"Error","nsig_sw*"+pol) ;
    pe = int(10000*htemp->GetMean()+0.5)/100.  ; 
  } else {
    pe = sqrt(htemp->GetMean()*(1-htemp->GetMean())/htemp->GetEntries());
    pe = int(10000*pe+0.5)/100. ;
  }
  KPCD20->Draw(KVar,"nsig_sw*"+pol)  ;
  double km = int(10000*htemp->GetMean()+0.5)/100.  ; 
  if (KVar.Contains("_PIDCalibEff")){
    KPCD20->Draw(KVar+"Error","nsig_sw*"+pol) ;
    ke = int(10000*htemp->GetMean()+0.5)/100. ;
  } else {
    ke = sqrt(htemp->GetMean()*(1-htemp->GetMean())/htemp->GetEntries());
    ke = int(10000*ke+0.5)/100. ;
  }
  double r = km/pm ; 
  double re = r*sqrt((ke/km)*(ke/km)+(pe/pm)*(pe/pm));
  std::cout << what << " & " << pm << "\\pm" << pe << " & " << km << "\\pm" << ke << " & " 
            << int(10000*r+0.5)/10000. << "\\pm" << int(10000*re+0.5)/10000. 
            << "\\\\ %%%%%%%%%%%%%%" << endl ;

}
