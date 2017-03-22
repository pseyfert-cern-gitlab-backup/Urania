#include "TROOT.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooMultiVarGaussian.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TMatrixDSym.h"

#include "../Espresso/RooGLMFunction.hh"
using namespace Espresso;

#include <fstream>
#include <iostream>

using namespace std;
using namespace RooFit;

void printSomeVals(RooGLMFunction& calib, RooRealVar& eta)
{
  cout << "===> Some values" << endl;
  eta.setVal(0.1);
  cout << "eta=0.1 => omega = "<< calib.getVal()<<endl;
  eta.setVal(0.2);
  cout << "eta=0.2 => omega = "<< calib.getVal()<<endl;
  eta.setVal(0.3);
  cout << "eta=0.3 => omega = "<< calib.getVal()<<endl;
  eta.setVal(0.4);
  cout << "eta=0.4 => omega = "<< calib.getVal()<<endl;
  eta.setVal(0.45);
  cout << "eta=0.45 => omega = "<< calib.getVal()<<endl;
}

void testRooGLMFunction()
{
  //Print "initial" conditions
  RooRealVar eta("eta","#eta",0.0,0.5);

  string calName = "OS_Combination_Calibration";
  string calFileName = "OS_Combination_Calibration.xml";
  auto glm = Espresso::createRooGLMCalibration("OS","OS",eta,calName,calFileName);
  RooArgList& coeffs = std::get<0>(glm);
  RooArgList& deltacoeffs = std::get<1>(glm);
  RooMultiVarGaussian& constraint = std::get<2>(glm);
  RooGLMFunction& os_b = std::get<3>(glm);
  RooGLMFunction& os_bbar = std::get<4>(glm);

  cout << "===> B Calibration function" << endl;
  os_b.Print("v");

  cout << "===> B-bar Calibration function" << endl;
  os_bbar.Print("v");

  cout << "===> Gaussian constraint" << endl;
  constraint.Print("v");
  
  TMatrixDSym covariance = constraint.covarianceMatrix();
  cout << "===> Covariance matrix" << endl;
  covariance.Print("v");

  cout << "===> Before modifying coefficients" << endl;
  cout << "Flavour = +1:" << endl;
  printSomeVals(os_b, eta);
  cout << "Flavour = -1:" << endl;
  printSomeVals(os_bbar, eta);
  
  //Play with coeffcients
  for (std::size_t i = 0; i < coeffs.getSize(); ++i)
  {
    ((RooRealVar*)coeffs.at(i))->setVal(0.0);
    ((RooRealVar*)coeffs.at(i))->setConstant(kTRUE);
    ((RooRealVar*)deltacoeffs.at(i))->setVal(0.0);
    ((RooRealVar*)deltacoeffs.at(i))->setConstant(kTRUE);
  }

  cout << "===> After modifying coefficients" << endl;
  cout << "Flavour = +1:" << endl;
  printSomeVals(os_b, eta);
  cout << "Flavour = -1:" << endl;
  printSomeVals(os_bbar, eta);
  
}


int main()
{
  testRooGLMFunction();
}
