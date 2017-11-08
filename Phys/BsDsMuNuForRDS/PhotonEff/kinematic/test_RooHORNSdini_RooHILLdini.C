{

  ////////////////////////////////////
  cout<<"-----------------------"<<endl;
  cout<<"- Test of RooFLATdini -"<<endl;
  cout<<"-----------------------"<<endl<<endl;
  ////////////////////////////////////
  gROOT->ProcessLine(".x /home/gandini/PDFs/ThesisStyle.C");
  gSystem->Load("P_DstarKinematic_C.so");
  gSystem->Load("P_VectorPlot_C.so");
  gSystem->Load("/home/gandini/PDFs/RooFLATdini_cc.so");
  gSystem->Load("/home/gandini/PDFs/RooHORNSdini_cc.so");
  gSystem->Load("/home/gandini/PDFs/RooHILLdini_cc.so");

  #include "/home/gandini/PDFs/Convert.h"
  using namespace std;
  using namespace RooFit;


  ////////////////////////////////////////////////////
  #include "values.txt"
  ////////////////////////////////////////////////////
  RooRealVar   m("m","m",  4800,5500);
  RooRealVar   mL("mL","mL",  4600);
  RooRealVar   mR("mR","mR",  5400);
  RooRealVar   sigma("sigma","resolution",RESOLUTION,5,50);
  RooRealVar   sigma2("sigma2","resolution",RESOLUTION);
  RooRealVar   fsig("fsig","fsig",0.33333333,0,1);
  ////////////////////////////////////////////////////


  RooHILLdini   pdf_RooHILLdini_Bu_Dstar0Pi( "pdf_RooHILLdini_Bu_Dstar0Pi" ,"pdf_RooHILLdini"  ,m,a_Bu_Dstar0Pi_D0gamma  ,b_Bu_Dstar0Pi_D0gamma  ,sigma) ;
  RooHORNSdini  pdf_RooHORNSdini_Bu_Dstar0Pi("pdf_RooHORNSdini_Bu_Dstar0Pi","pdf_RooHORNSdini" ,m,a_Bu_Dstar0Pi_D0pi0    ,b_Bu_Dstar0Pi_D0pi0    ,sigma) ;
  RooAddPdf     pdf_Bu_Dstar0Pi("pdf_Bu_Dstar0Pi","pdf_Bu_Dstar0Pi",RooArgList(pdf_RooHILLdini_Bu_Dstar0Pi,pdf_RooHORNSdini_Bu_Dstar0Pi),fsig) ;

  RooHILLdini   pdf_RooHILLdini_Bu_Dstar0K( "pdf_RooHILLdini_Bu_Dstar0K" ,"pdf_RooHILLdini"  ,m,a_Bu_Dstar0K_D0gamma  ,b_Bu_Dstar0K_D0gamma  ,sigma) ;
  RooHORNSdini  pdf_RooHORNSdini_Bu_Dstar0K("pdf_RooHORNSdini_Bu_Dstar0K","pdf_RooHORNSdini" ,m,a_Bu_Dstar0K_D0pi0    ,b_Bu_Dstar0K_D0pi0    ,sigma) ;
  RooAddPdf     pdf_Bu_Dstar0K("pdf_Bu_Dstar0K","pdf_Bu_Dstar0K",RooArgList(pdf_RooHILLdini_Bu_Dstar0K,pdf_RooHORNSdini_Bu_Dstar0K),fsig) ;

  RooHORNSdini  pdf_Bd_DstarpPi("pdf_RooHORNSdini_Bd_DstarpPi","pdf_RooHORNSdini" ,m, a_Bd_DstarpPi_D0pi ,b_Bd_DstarpPi_D0pi    ,sigma) ;
  RooHORNSdini  pdf_Bd_DstarpK("pdf_RooHORNSdini_Bd_DstarpK","pdf_RooHORNSdini"   ,m, a_Bd_DstarpK_D0pi ,b_Bd_DstarpK_D0pi    ,sigma) ;


  /*
  RooRealVar   f1("f1","f1",(1-0.08)/2);
  RooRealVar   f2("f2","f2",(1-0.08)/2);
  RooRealVar   f3("f3","f3", 0.08/2);
  RooAddPdf sum("sum","sum",RooArgList(pdf_Bu_Dstar0Pi,pdf_Bu_Dstar0K,pdf_Bd_DstarpPi,pdf_Bd_DstarpK),RooArgList(f1,f2,f3));
  RooPlot* mframe = m.frame() ;
  sum.plotOn(mframe) ;
  mframe->Draw();
  */


  /*
  RooDataSet* data = pdf.generate(m,50000) ;
  pdf.fitTo(*data) ;
  RooPlot* mframe = m.frame() ;
  data->plotOn(mframe) ;
  pdf.plotOn(mframe) ;
  mframe->Draw();
  */


  RooPlot* mframe = m.frame();
  pdf_Bu_Dstar0Pi->plotOn(mframe,LineWidth(1),LineColor(kBlue) ) ;
  pdf_Bu_Dstar0K->plotOn(mframe, LineWidth(1),LineColor(kRed)  ) ;
  pdf_Bd_DstarpPi->plotOn(mframe , LineWidth(1),LineColor(kBlue)  ) ;
  pdf_Bd_DstarpK->plotOn(mframe,   LineWidth(1),LineColor(kRed)   ) ;
  mframe->Draw();


}
