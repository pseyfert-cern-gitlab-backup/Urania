{
  gSystem->Load("libMinuit.so");
  gSystem->Load("libRooFit.so");
  gSystem->Load("libRooFitCore.so");
  gSystem->Load("libRooStats.so");
  ROOT::Cintex::Cintex cintex;
  ROOT::Cintex::Cintex::Enable();
  gSystem->Load("libRooPhysFitterLib.so");
  gSystem->Load("libRooPhysFitterDict.so");
}
