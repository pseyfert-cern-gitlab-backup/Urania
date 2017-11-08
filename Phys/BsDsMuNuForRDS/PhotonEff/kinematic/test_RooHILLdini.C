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
  cout<<"---------------------"<<endl;


  
  cout<<"Min  = 5226.723"<<endl;
  cout<<"Max  = 4905.583"<<endl;
  cout<<"Diff = "<<5226.723-4905.583<<endl;
  

  RooRealVar m("m","m",  4500,5500) ;
  RooRealVar a("a","a",  4905.583, 4905.583-50, 4905.583+50) ;
  RooRealVar b("b","b",  5226.723, 5226.723-50, 5226.723+50) ;
  RooRealVar sigma("sigma","width of gaussian",9,5,90) ;
  RooHILLdini pdf("pdf","pdf",m,a,b,sigma) ;


  a.setConstant();
  b.setConstant();


  RooDataSet* data = pdf.generate(m,50000) ;
  pdf.fitTo(*data) ;

  RooPlot* mframe = m.frame() ;
  data->plotOn(mframe) ;
  pdf.plotOn(mframe) ;
  mframe->Draw();




}
