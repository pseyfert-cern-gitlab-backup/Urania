//////////////////////////////////////////////////
// ********** Loading useful classes ********** //
//////////////////////////////////////////////////

#include "ToyModel.h"

/////////////////////////////////////////
// ********** Main-function ********** //
/////////////////////////////////////////
int Simulation(int tracktype, int set_seed, double theLumi=0, TString setup = "Default"){

  // ********** Creating new DecayModel ********** //
  ///////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "//////////////////////////////////////////////////" << std::endl;
  std::cout << "// ********** Creating new Toy Model ********** //" << std::endl;
  std::cout << "//////////////////////////////////////////////////" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  ToyModel* myTool = new ToyModel();

  myTool->DefiningConstantsAndVariables(tracktype, theLumi);
  myTool->BuildPdf();
  myTool->GenerateData(set_seed);

  // *** for plotting ***
  //myTool->Plotting("SepBsOnly");

  // *** for fitting ***
  myTool->FittingParameters(setup);
  //myTool->Plotting("Fit");  
  myTool->Saving();

  delete myTool;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "///////////////////////////////////////////" << std::endl;
  std::cout << "// ********** Toy is finished ********** //" << std::endl;
  std::cout << "///////////////////////////////////////////" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  return 0;
};
