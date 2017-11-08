void CreateControlledCocktail() {

  /*
input/RootOutp_MCAll_MCstuTemDBdDstDs.root
input/RootOutp_MCAll_MCstuTemDBsDsDs.root
input/RootOutp_MCAll_MCstuTemDBuD0Ds.root
input/RootOutp_MCAll_MCstuTemDLbLcDs.root
input/RootOutp_MCAll_MCstuTemDSameSide.root
input/RootOutp_MCAll_MCstuTemDSideBands.root
input/RootOutp_MCAll_MCstuTemDSignal_Bs0D1pMu.root
input/RootOutp_MCAll_MCstuTemDSignal_Bs0Ds0staMu.root
input/RootOutp_MCAll_MCstuTemDSignal_Bs0Ds1Mu.root
input/RootOutp_MCAll_MCstuTemDSignal_Bs0DsMu.root
input/RootOutp_MCAll_MCstuTemDSignal_Bs0DstaMu.root
input/RootOutp_MCAll_TauMCstuTemDSignal_Bs0Ds0staTau.root
input/RootOutp_MCAll_TauMCstuTemDSignal_Bs0Ds1pTau.root
input/RootOutp_MCAll_TauMCstuTemDSignal_Bs0Ds1Tau.root
input/RootOutp_MCAll_TauMCstuTemDSignal_Bs0DstaTau.root
input/RootOutp_MCAll_TauMCstuTemDSignal_Bs0DsTau.root
  */

  TFile * f_dsmu =  new TFile("input/RootOutp_MCAll_MCstuTemDSignal_Bs0DsMu.root");
  RooWorkspace *w = (RooWorkspace*) f_dsmu->Get("w");
  w->Print();

  return;

}

