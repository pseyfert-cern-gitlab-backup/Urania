#ifndef ROOT_BACKGROUND_H 
#define ROOT_BACKGROUND_H 1

// Include files
#include "RooKeysPdf.h"
#include "RooGaussian.h"
#include "TFile.h"
#include "TString.h"
#include "RooConstVar.h"
#include "TSystemDirectory.h"
#include "Tuples.h"
using namespace RooFit ;
// http://root.cern.ch/root/html/tutorials/roofit/rf604_constraints.C.html
/** @class background background.h root/background.h
 *  
 *  Background shape
 *
 *  @author Patrick Koppenburg
 *  @date   2013-05-16
 */
class background {
public: 
  /// Standard constructor
  background( TString name, int cat, double y, double e, TString nncut, double factor = 1., TString rho=""){
    m_name = name ;
    m_category = cat;
    //std::cout << name << " " << y << " " << e << std::endl ;
    double l = y-3*factor*e;
    if (l<0) l=0;
    m_yield = new RooRealVar(TString(c_Yield+" "+name),"background yield",y,l,y+3*factor*e);
    m_y = y;
    m_e = e;
    //m_yield->Print("v");
    m_constraint = new RooGaussian("fconstraint "+name,"fconstraint "+name ,*m_yield, 
				   RooConst(y),RooConst(factor*e)) ;
    int code = 0; TString fName =  "" ;
    TFile* f = 0 ;
    if (name.Contains(c_PsipKMass)) {
      code = c_psipK_BKGCAT ;
      f = getMCFile( "LambdabMC-LbK-Sim08a-1127-1128-1129-1137-"+rho, nncut, "-SW.root"); 
    } else if (name.Contains(c_PsiKpMass)){ 
      code = c_Kp_BKGCAT ;
      f = getMCFile( "LambdabMC-LbK-Sim08a-1127-1128-1129-1137-"+rho, nncut, "-SW.root"); 
    } else if (name.Contains(c_PsipiKMass)) {
      code = c_piK_BKGCAT ;
      f = getMCFile( "LambdabMC-B2JpsiKpi-Sim08a-1138-1139-"+rho, nncut, "-SW.root");
    } else  if (name.Contains(c_PsiKpiMass)){ 
      code = c_Kpi_BKGCAT ;
      f = getMCFile( "LambdabMC-B2JpsiKpi-Sim08a-1138-1139-"+rho, nncut, "-SW.root");
    } else if (name.Contains(c_PsiKKMass)){
      code = c_KK_BKGCAT ;
      f = getMCFile( "LambdabMC-B2JpsiKK-Sim08a-1134-1135-"+rho, nncut, "-SW.root");
    } else if (name.Contains(c_PsippiMass)){ 
      code = c_ppi_BKGCAT ;
      f = getMCFile( "LambdabMC-Lbpi-Sim08a-1122-1123-1124-1125-"+rho, nncut, "-SW.root");
    }
    TString codeN = "";
    codeN+=code ;
    TString rName =  "RK_"+(CatCodes::SignalCand==cat?c_PsippiName:c_PsipKName)+"_pdf_"+codeN ;
    
    //    f->ls();
    RooKeysPdf* lPdf = (RooKeysPdf*)f->Get(rName); /// will crash if no f
    std::cout << "Background made with " << name <<  " " << cat << " " << f->GetName() << " " 
              << rName << " " << lPdf << std::endl ;
    m_pdf = new RooKeysPdf(*lPdf) ; /// copy
    // m_pdf.Print();
    f->Close();
    
  }
  // get MC file
  TFile* getMCFile(TString pattern, TString nnCut, TString ext="-SW.root", const char *dirname="./")
  {    
    TString fname = pattern+nnCut+ext;
    TFile* f = TFile::Open(fname);
    if (!f){
      std::cout << "WARNING : Cannot find " << fname << ". Looking for similar" << std::endl ;
      TSystemDirectory dir(dirname, dirname);
      TList *files = dir.GetListOfFiles();
      if (files) {
        TSystemFile *file;
        TIter next(files);
        while ((file=(TSystemFile*)next())) {
          fname = file->GetName();
          if (!file->IsDirectory() && fname.EndsWith(ext) && fname.Contains(pattern)) {
	    std::cout << "Opening " << fname << " instead." << std::endl ;
           return  TFile::Open(fname);
          }
        }
      }
    }
    if (!f) std::cout << "ERROR: Did not find replacement for " << fname << std::endl ;
    return f ;
  }
  
  virtual ~background( ){}; ///< Destructor

  /// Accessors
  RooGaussian* constraint(){ return m_constraint ;}
  RooKeysPdf* pdf(){ return m_pdf ;}
  TString name()const{ return m_name ; }
  RooRealVar* yield(){ return m_yield ; }
  double y(){return m_y;};
  double e(){return m_e;};
  

protected:

private:
  TString m_name ;
  int m_category ;
  RooKeysPdf* m_pdf ;
  RooRealVar* m_yield ;
  RooRealVar* m_savedYield ;
  RooGaussian* m_constraint ;
  double m_y;
  double m_e;
  
};
typedef std::vector<background*> backgrounds ;
#endif // ROOT_BACKGROUND_H
