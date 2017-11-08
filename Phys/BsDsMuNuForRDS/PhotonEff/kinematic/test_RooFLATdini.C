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
  #include "/home/gandini/PDFs/Convert.h"
  using namespace std;
  using namespace RooFit;
  cout<<"---------------------"<<endl;


  
  cout<<"Min  = 5113.460"<<endl;
  cout<<"Max  = 5012.799"<<endl;
  cout<<"Diff = "<<5113.460-5012.799<<endl;
  


  RooRealVar m("m","m",  4500,5500) ;
  RooRealVar a("a","a",  5012.799, 5012.799-50, 5012.799+50) ;
  RooRealVar b("b","b",  5113.460, 5113.460-50, 5113.460+50) ;
  RooRealVar sigma("sigma","width of gaussian",11,5,30) ;
  RooFLATdini pdf("pdf","pdf",m,a,b,sigma) ;

  RooDataSet* data = pdf.generate(m,10000) ;
  pdf.fitTo(*data) ;

  RooPlot* mframe = m.frame() ;
  data->plotOn(mframe) ;
  pdf.plotOn(mframe) ;
  mframe->Draw();




}
