#include "TTree.h"

void PIDCalib(TString what, TTree* piPCD20, TTree* KPCD20, TString piVar = "Pi_PIDCalibEff", TString KVar = "K_PIDCalibEff"){
  
  double pe, ke ;
  piPCD20->Draw(piVar,"nsig_sw") ;
  double pm = int(10000*htemp->GetMean()+0.5)/100.  ; 
  if (piVar.Contains("_PIDCalibEff")){
    piPCD20->Draw(piVar+"Error","nsig_sw") ;
    pe = int(10000*htemp->GetMean()+0.5)/100.  ; 
  } else pe = int(10000*htemp->GetMeanError()+0.5)/100. ;

  KPCD20->Draw(KVar,"nsig_sw")  ;
  double km = int(10000*htemp->GetMean()+0.5)/100.  ; 
  if (KVar.Contains("_PIDCalibEff")){
    KPCD20->Draw(KVar+"Error","nsig_sw") ;
    ke = int(10000*htemp->GetMean()+0.5)/100. ;
  } else ke = int(10000*htemp->GetMeanError()+0.5)/100. ;
  r = km/pm ; 
  re = r*sqrt((ke/km)*(ke/km)+(pe/pm)*(pe/pm));
  std::cout << what << " & " << pm << "\\pm" << pe << " & " << km << "\\pm" << ke << " & " 
	    << int(10000*r+0.5)/10000. << "\\pm" << int(10000*re+0.5)/10000. << "\\\\ %%%%%%%%%%%%%%" << endl ;

}
