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

  #include "/home/gandini/PDFs/Convert.h"
  using namespace std;
  using namespace RooFit;
  cout<<"---------------------"<<endl;



  


  RooRealVar m("m","m",  4500,5500) ;
  RooRealVar a("a","a",  2092.104, 2092.104-50, 2092.104+50) ; a.setConstant();
  RooRealVar b("b","b",  5139.287, 5139.287-50, 5139.287+50) ;
  RooRealVar sigma("sigma","width of gaussian",0,0,30) ;
  RooHORNSdini pdf("pdf","pdf",m,a,b,sigma) ;

  RooDataSet* data = pdf.generate(m,10000) ;
  pdf.fitTo(*data) ;

  RooPlot* mframe = m.frame() ;
  data->plotOn(mframe) ;
  pdf.plotOn(mframe) ;
  mframe->Draw();




}
