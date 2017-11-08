#define addRegressionData_cxx
#include "addRegressionData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TMVA/Reader.h"

void addRegressionData::Loop(){
   if (fChain == 0) return;

   Float_t pReg,q2Reg;
   TString method = "MLP";

   TBranch *pRegBranch = fChain->Branch("pReg",&pReg,"pReg/F");
   TBranch *q2RegBranch = fChain->Branch("q2Reg",&q2Reg,"q2Reg/F");
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
   
   Float_t var1, var2;
   Float_t diff1, diff2;
   reader->AddVariable("InvSinF",&var1);
   reader->AddVariable("bFLenF",&var2);

   TString weights = "TMVARegression_MLP.weights.xml";
   reader->BookMVA( method, weights );

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      var1 = 1./bSinFlightAng;
      var2 = bFlightLen;
      pReg = (reader->EvaluateRegression(method))[0];
      pRegBranch->Fill();
      diff1 = abs(pReg-pBsP1);
      diff2 = abs(pReg-pBsP2); 
      if (diff1 <= diff2){
        q2Reg = q2P1;
      }else{
        q2Reg = q2P2;
      }
      q2RegBranch->Fill();
   }
   fChain->Write("",TObject::kOverwrite);
}
