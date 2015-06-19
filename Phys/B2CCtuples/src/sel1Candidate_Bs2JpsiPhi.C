// Program to create NTupleA from DecayTreeTuple
// SetupProject DaVinci, compile and run:
// 
// $> SetupProject DaVinci
// $> g++ -Wall -ggdb -O2 `root-config --cflags --libs --ldflags` -lTreePlayer -o sel1Candidate_Bs2JpsiPhi sel1Candidate_Bs2JpsiPhi.C
// $> ./sel1Candidate_Bs2JpsiPhi "BsTuple/DecayTree" output_tupleA.root input_MagUp.root [input_MagDown.root]
//  last argument in [ ] not mandatory
//
//====================================================================================================================================
// !!! WARNING, M. Dorigo, 23 Oct 2013: 
//
// We have defined two OST and two SST versions, with the "_calib" suffix, which means that they are fully calibrated:
//
// OS 1) OS combination with cut-based Kaon tagger: TAGDECISION_OS_wCBK_calib, TAGOMEGA_OS_wCBK_calib
// OS 2) OS combination with nnet      Kaon tagger: TAGDECISION_OS_wNNK_calib, TAGOMEGA_OS_wNNK_calib
//
// SS 1) SS cut-based Kaon tagger: B_s0_SS_nnetKaon_DEC_calib, B_s0_SS_nnetKaon_PROB_calib
// SS 2) SS nnet      Kaon tagger: B_s0_SS_Kaon_DEC_calib, B_s0_SS_Kaon_PROB_calib
//
//    Calibration parameters as of 23 october 2013:
//    (NB.: the OS nnet need a correction in two steps)
//
//    OS cut based:     p0=0.384  p1=1.008   <eta>=0.380     (JpsiK+  2011+2012 (1/3))
//    OS nnet 1st:      p0=0.423  p1=0.875   <eta>=0.403     (JpsiK+  2011+2012 (1/3))
//    OS nnet 2nd:      p0=0.422  p1=0.993   <eta>=0.422     (JpsiK+  2011+2012 (1/3))
//
//    Hp: assume the same time resolution model and values as in Reco12 2011 (motivated by results in other channels)
//    SSK cut based:    p0=0.390  p1=1.715    <eta>=0.343    (Bs2Dspi 2011+2012 )
//    SSK nnet:         p0=0.442  p1=0.975    <eta>=0.437    (Bs2Dspi 2011+2012 )
//
//    This calibrations will allow to use in the tagged time-dependent fit p0 = <eta> and p1=1 for all tagging categories.
//


#include <iostream>
#include <vector>
#include <map>

#include "TMath.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TCut.h"
#include "TList.h"


namespace {
   using std::cout;
   using std::cerr;
   using std::endl;
   using std::make_pair;
   using std::string;
   using std::map;
   using std::pair;
}

TTree* sel1CandidateBs2JpsiPhi(TTree* tree, TTree* outputTree, int pol = 0, int pythia = 0);

int main(int argc, char* argv[]) {
  map<string, pair<int, int> > inputs;
   if (argc < 4) {
      cout << "Usage:" << " " << argv[0] << " " << "path/to/tree" << " " << "output_file.root"
           << " intput_file.root [input_file.root]" << endl;
      return -1;
   }

   for (int i = 3; i < argc; ++i) {
      int pol = 0;
      string input_filename(argv[i]);
      if (input_filename.find("Down") != string::npos) {
         pol = -1;
      } else if (input_filename.find("Up") != string::npos) {
         pol = 1;
      }
      int pythia = 0;
      if (input_filename.find("Pythia6") != string::npos) {
         pythia = 6;
      } else if (input_filename.find("Pythia8") != string::npos) {
         pythia = 8;
      }
      inputs.insert(make_pair(input_filename, make_pair(pol, pythia)));
   }
  
   const char* treeName = argv[1];

   TTree* firstTree = 0;

   // Create the output file
   const char* outputFile = argv[2];
   TFile* f_out = new TFile(outputFile,"RECREATE");
   
   for(map<string, pair<int, int> >::const_iterator it = inputs.begin(), end = inputs.end();
       it != end; ++it) {
      const string& input = it->first;
      cout << "Processing " << input << endl;
      TFile* file = TFile::Open(input.c_str(), "read");
      if(!file || !file->IsOpen()) {
         cerr << "Could not open file " << input << endl;
         return -2;
      }
      TTree* tree = static_cast<TTree*>(file->Get(treeName));
      if (!tree) {
         cerr << "Could not get tree " << treeName << " from file " << input << endl;
         return -3;
      }
      f_out->cd();
      // Select candidates, flag vertex, etc and merge resuting tree into firstTree
      TTree* newTree = sel1CandidateBs2JpsiPhi(tree, firstTree, it->second.first, it->second.second);
      if (!firstTree) firstTree = newTree;
   }
   
   // Write the combined tree to the output file.
   f_out->WriteTObject(firstTree, firstTree->GetName());
   f_out->Close();
   return 0;
}

int type1Clone(float tx1, float tx2, float ty1, float ty2) {
   return ((TMath::Abs(tx1 -tx2) < 0.0004) && (TMath::Abs(ty1 -ty2) < 0.0002));
}

int type2Clone(float tx1, float tx2, float ty1, float ty2, float qDivp1, float qDivp2  ){
   return ((TMath::Abs(tx1 -tx2) < 0.005) && (TMath::Abs(ty1 -ty2) < 0.005) && TMath::Abs(qDivp1 - qDivp2) < 1e-6);
}

int t1Clone(float tx1, float tx2, float tx3, float tx4, float ty1, float ty2,float ty3, float ty4 ){

   if (type1Clone(tx1,tx2, ty1,ty2) == 1) return 1;
   if (type1Clone(tx1,tx3, ty1,ty3) == 1) return 1;   
   if (type1Clone(tx1,tx4, ty1,ty4) == 1) return 1;   
   if (type1Clone(tx2,tx3, ty2,ty3) == 1) return 1;  
   if (type1Clone(tx2,tx4, ty2,ty4) == 1) return 1;  
   if (type1Clone(tx3,tx4, ty3,ty4) == 1) return 1;  
   return 0;
}

int t2Clone(float tx1, float tx2, float tx3, float tx4, float ty1, float ty2,float ty3, float ty4 , float 
            qp1, float qp2, float qp3, float qp4){

   if (type2Clone(tx1,tx2, ty1,ty2, qp1, qp2) == true) return 1;
   if (type2Clone(tx1,tx3, ty1,ty3, qp1, qp3) == true) return 1;   
   if (type2Clone(tx1,tx4, ty1,ty4, qp1, qp4) == true) return 1;   
   if (type2Clone(tx2,tx3, ty2,ty3, qp2, qp3) == true) return 1;  
   if (type2Clone(tx2,tx4, ty2,ty4, qp2, qp4) == true) return 1;  
   if (type2Clone(tx3,tx4, ty3,ty4,qp3, qp4) == true) return 1;  
   return 0;
}

TTree* sel1CandidateBs2JpsiPhi(TTree* inputTree, TTree* outputTree, int pol, int pythia) {
  
   //CPPM
   TCut cutMu = "min(muplus_PIDmu,muminus_PIDmu)>0&&max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF)<4&&min(muplus_PT,muminus_PT)>500";
   //  TCut cutJ = "J_psi_1S_ENDVERTEX_CHI2/J_psi_1S_ENDVERTEX_NDOF<11";
   TCut cutK = "Kplus_PIDK>0&&Kplus_TRACK_CHI2NDOF<4&&Kminus_PIDK>0&&Kminus_TRACK_CHI2NDOF<4";
   // cutPhi = "phi_1020_PT>1000&&phi_1020_ENDVERTEX_CHI2/phi_1020_ENDVERTEX_NDOF<20&&abs(phi_1020_MM-1020)<12";
   TCut cutPhi = "phi_1020_PT>1000&&phi_1020_ENDVERTEX_CHI2/phi_1020_ENDVERTEX_NDOF<20";
   TCut cutB = "B_s0_LOKI_DTF_VCHI2NDOF>0&&B_s0_LOKI_DTF_VCHI2NDOF<5&&B_s0_IPCHI2_OWNPV<25";

   bool isMC = inputTree->GetBranch( "B_s0_TRUETAU" );
   if (isMC) {
      cout << "Running on MC DTT." << endl;
   } else {
      cout << "Running on Data DTT." << endl;
   }
 
   cout << "Apply cut and copy tree." << endl;
   TCut cut0 = "B_s0_M > 5200 && B_s0_M < 5550";
   TTree* newtree = inputTree->CopyTree(cutMu && cutK && cutPhi && cutB && cut0);
   delete inputTree;

   int polarity = pol;
   TBranch* branch_polarity = newtree->Branch("polarity", &polarity, "polarity/I");

   TBranch* branch_pythia = 0;
   if (isMC) {
      int pythia_version = pythia;
      branch_pythia = newtree->Branch("pythia", &pythia_version, "pythia/I");
   }

   int cloneType1 = 0;
   TBranch *branch_type1Clone = newtree->Branch("type1Clone",&cloneType1, "type1Clone/I");

   int cloneType2 = 0;
   TBranch *branch_type2Clone = newtree->Branch("type2Clone",&cloneType2, "type2Clone/I");

   int klClone = 0;
   TBranch *branch_klClone = newtree->Branch("klClone",&klClone, "klClone/I");

   Double_t muplus_TRACK_CloneDist = 0, muminus_TRACK_CloneDist = 0,
      Kplus_TRACK_CloneDist = 0, Kminus_TRACK_CloneDist = 0;

   Double_t px1 = 0, px2 = 0, px3 = 0, px4 = 0,
      py1=  0, py2 = 0, py3 = 0, py4 = 0,
      pz1 = 0, pz2 = 0, pz3 = 0, pz4 = 0,
      p1 = 0, p2 = 0, p3 = 0, p4 = 0; 

   TBranch* b_muplus_TRACK_CloneDist = 0;
   TBranch* b_muminus_TRACK_CloneDist = 0;
   TBranch* b_Kplus_TRACK_CloneDist = 0;
   TBranch* b_Kminus_TRACK_CloneDist = 0;

   newtree->SetBranchAddress("muplus_TRACK_CloneDist", &muplus_TRACK_CloneDist, &b_muplus_TRACK_CloneDist);
   newtree->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
   newtree->SetBranchAddress("Kplus_TRACK_CloneDist", &Kplus_TRACK_CloneDist, &b_Kplus_TRACK_CloneDist);
   newtree->SetBranchAddress("Kminus_TRACK_CloneDist", &Kminus_TRACK_CloneDist, &b_Kminus_TRACK_CloneDist);
  
   newtree->SetBranchAddress("muplus_PX", &px1 );
   newtree->SetBranchAddress("muminus_PX", &px2 );
   newtree->SetBranchAddress("Kplus_PX", &px3 );
   newtree->SetBranchAddress("Kminus_PX", &px4 );
   newtree->SetBranchAddress("muplus_PY", &py1 );
   newtree->SetBranchAddress("muminus_PY", &py2 );
   newtree->SetBranchAddress("Kplus_PY", &py3 );
   newtree->SetBranchAddress("Kminus_PY", &py4 );
   newtree->SetBranchAddress("muplus_PZ", &pz1 );
   newtree->SetBranchAddress("muminus_PZ", &pz2 );
   newtree->SetBranchAddress("Kplus_PZ", &pz3 );
   newtree->SetBranchAddress("Kminus_PZ", &pz4 );
   newtree->SetBranchAddress("muplus_P", &p1 );
   newtree->SetBranchAddress("muminus_P", &p2 );
   newtree->SetBranchAddress("Kplus_P", &p3 );
   newtree->SetBranchAddress("Kminus_P", &p4 );


   Int_t B_s0_OS_Muon_DEC = 0;
   Int_t B_s0_OS_Electron_DEC = 0;
   Int_t B_s0_OS_Kaon_DEC = 0;
   Int_t B_s0_OS_nnetKaon_DEC = 0;
   Int_t B_s0_VtxCharge_DEC = 0;
   Int_t B_s0_TAGDECISION_OS = 0;

   Double_t B_s0_OS_Muon_PROB = 0;
   Double_t B_s0_OS_Electron_PROB = 0;
   Double_t B_s0_OS_Kaon_PROB = 0;
   Double_t B_s0_OS_nnetKaon_PROB = 0;
   Double_t B_s0_VtxCharge_PROB = 0;
   Double_t B_s0_TAGOMEGA_OS = 0;

   Int_t B_s0_SS_Kaon_DEC = 0;
   Int_t B_s0_SS_nnetKaon_DEC = 0;
   Double_t B_s0_SS_Kaon_PROB = 0;
   Double_t B_s0_SS_nnetKaon_PROB = 0;

   newtree->SetBranchAddress("B_s0_OS_Muon_DEC",    &B_s0_OS_Muon_DEC);
   newtree->SetBranchAddress("B_s0_OS_Electron_DEC",    &B_s0_OS_Electron_DEC);
   newtree->SetBranchAddress("B_s0_OS_Kaon_DEC",    &B_s0_OS_Kaon_DEC);
   newtree->SetBranchAddress("B_s0_OS_nnetKaon_DEC",    &B_s0_OS_nnetKaon_DEC);
   newtree->SetBranchAddress("B_s0_VtxCharge_DEC",    &B_s0_VtxCharge_DEC);
   newtree->SetBranchAddress("B_s0_TAGDECISION_OS", &B_s0_TAGDECISION_OS);

   newtree->SetBranchAddress("B_s0_OS_Muon_PROB",    &B_s0_OS_Muon_PROB);
   newtree->SetBranchAddress("B_s0_OS_Electron_PROB",    &B_s0_OS_Electron_PROB);
   newtree->SetBranchAddress("B_s0_OS_Kaon_PROB",    &B_s0_OS_Kaon_PROB);
   newtree->SetBranchAddress("B_s0_OS_nnetKaon_PROB",    &B_s0_OS_nnetKaon_PROB);
   newtree->SetBranchAddress("B_s0_VtxCharge_PROB",    &B_s0_VtxCharge_PROB);
   newtree->SetBranchAddress("B_s0_TAGOMEGA_OS",    &B_s0_TAGOMEGA_OS);

   newtree->SetBranchAddress("B_s0_SS_Kaon_DEC",    &B_s0_SS_Kaon_DEC);
   newtree->SetBranchAddress("B_s0_SS_nnetKaon_DEC",    &B_s0_SS_nnetKaon_DEC);
   newtree->SetBranchAddress("B_s0_SS_Kaon_PROB",   &B_s0_SS_Kaon_PROB);
   newtree->SetBranchAddress("B_s0_SS_nnetKaon_PROB",   &B_s0_SS_nnetKaon_PROB);

   Int_t B_s0_TAGDECISION_OS_wNNK_calib = 0;
   Double_t B_s0_TAGOMEGA_OS_wNNK_calib = 0;

   Int_t B_s0_TAGDECISION_OS_wCBK_calib = 0;
   Double_t B_s0_TAGOMEGA_OS_wCBK_calib = 0;

   Int_t B_s0_SS_Kaon_DEC_calib = 0;
   Int_t B_s0_SS_nnetKaon_DEC_calib = 0;
   Double_t B_s0_SS_Kaon_PROB_calib = 0;
   Double_t B_s0_SS_nnetKaon_PROB_calib = 0;

   TBranch* bB_s0_TAGDECISION_OS_wNNK_calib = newtree->Branch("B_s0_TAGDECISION_OS_wNNK_calib", &B_s0_TAGDECISION_OS_wNNK_calib,"B_s0_TAGDECISION_OS_wNNK_calib/I");  
   TBranch* bB_s0_TAGOMEGA_OS_wNNK_calib    = newtree->Branch("B_s0_TAGOMEGA_OS_wNNK_calib",    &B_s0_TAGOMEGA_OS_wNNK_calib,   "B_s0_TAGOMEGA_OS_wNNK_calib/D");

   TBranch* bB_s0_TAGDECISION_OS_wCBK_calib = newtree->Branch("B_s0_TAGDECISION_OS_wCBK_calib", &B_s0_TAGDECISION_OS_wCBK_calib,"B_s0_TAGDECISION_OS_wCBK_calib/I");  
   TBranch* bB_s0_TAGOMEGA_OS_wCBK_calib    = newtree->Branch("B_s0_TAGOMEGA_OS_wCBK_calib",    &B_s0_TAGOMEGA_OS_wCBK_calib,   "B_s0_TAGOMEGA_OS_wCBK_calib/D");

   TBranch* bB_s0_SS_Kaon_DEC_calib     = newtree->Branch("B_s0_SS_Kaon_DEC_calib",    &B_s0_SS_Kaon_DEC_calib,   "B_s0_SS_Kaon_DEC_calib/I");
   TBranch* bB_s0_SS_nnetKaon_DEC_calib    = newtree->Branch("B_s0_SS_nnetKaon_DEC_calib",    &B_s0_SS_nnetKaon_DEC_calib,   "B_s0_SS_nnetKaon_DEC_calib/I");
 
   TBranch* bB_s0_SS_Kaon_PROB_calib   = newtree->Branch("B_s0_SS_Kaon_PROB_calib",   &B_s0_SS_Kaon_PROB_calib,  "B_s0_SS_Kaon_PROB_calib/D");
   TBranch* bB_s0_SS_nnetKaon_PROB_calib   = newtree->Branch("B_s0_SS_nnetKaon_PROB_calib",   &B_s0_SS_nnetKaon_PROB_calib,  "B_s0_SS_nnetKaon_PROB_calib/D");



   cout << "Fill extra branches in output tree." << endl;

   for (Long64_t i = 0;i < newtree->GetEntries(); i++) {

      newtree->GetEntry(i);

      if ((muminus_TRACK_CloneDist < 0 || muminus_TRACK_CloneDist > 5000)
          && (muplus_TRACK_CloneDist < 0 || muplus_TRACK_CloneDist > 5000)
          && (Kplus_TRACK_CloneDist < 0 || Kplus_TRACK_CloneDist > 5000)
          && (Kminus_TRACK_CloneDist < 0 || Kminus_TRACK_CloneDist > 5000)) {
         klClone = 0;
      } else {
         klClone = 1;
      }

      cloneType1 = t1Clone(px1/pz1,px2/pz2,px3/pz3,px4/pz4, py1/pz1,py2/pz3,py3/pz3,py4/pz4);
      cloneType2 = t2Clone(px1/pz1,px2/pz2,px3/pz3,px4/pz4, py1/pz1,py2/pz2,py3/pz3,py4/pz4,
                           1/p1,-1/p2, 1/p3,-1/p4);

      branch_type1Clone->Fill();
      branch_type2Clone->Fill();
      branch_klClone->Fill();



      //==========================================================================================================
      // COMPUTE OS COMBINATION USING nnetKaon TAGGER
      //==========================================================================================================

      // Get original tagging decision and mistag from the DTT 
      Double_t osw[4];
      Int_t osdec[4];
      osw[0] =  B_s0_OS_Muon_PROB; 
      osw[1] =  B_s0_OS_Electron_PROB; 
      osw[2] =  B_s0_OS_nnetKaon_PROB; 
      osw[3] =  B_s0_VtxCharge_PROB; 

      osdec[0] =  B_s0_OS_Muon_DEC; 
      osdec[1] =  B_s0_OS_Electron_DEC; 
      osdec[2] =  B_s0_OS_nnetKaon_DEC; 
      osdec[3] =  B_s0_VtxCharge_DEC; 

      //Recompute the OS decision and mistag, with B_s0_OS_nnetKaon instead of B_s0_OS_Kaon 
      Double_t tagdecision=0;
      Double_t pnsum_a= 0.50;  //hypothesis of truetag=+1
      Double_t pnsum_b= 0.50;  //hypothesis of truetag=-1
      Double_t pnsum= 0.;  

      Double_t mtag = 0; 
      Double_t pn = 0; 

      // Multiply probabilities of each OS taggers: 
      for( int i = 0; i != 4; ++i ) 
      	{ 
	  mtag = osdec[i];
      	  if(!mtag) continue;

      	  pn   = 1-osw[i]; //probability of 'right'
      	  pnsum_a *= ((1-mtag)/2 + mtag*pn ); // p
      	  pnsum_b *= ((1+mtag)/2 - mtag*pn ); //(1-p)
      	}

      if(pnsum_a > pnsum_b) tagdecision = +1;
      if(pnsum_a < pnsum_b) tagdecision = -1;
      
      // Normalise probability to the only two possible flavours:
      pnsum = std::max(pnsum_a,pnsum_b) /(pnsum_a + pnsum_b);

      Double_t m_ProbMin_OS = 0.5;      
      // WARNING HARD-CODED NUMBERS for tagging calibration
      // Valid on Reco14 2011 and 2012 real data, Stripping>=20.
      // 1st OS nnet Calibration 
      Double_t m_P0_Cal_OS_nnK1 = 0.423;
      Double_t m_P1_Cal_OS_nnK1 = 0.875;
      Double_t m_Eta_Cal_OS_nnK1 = 0.403;
      // Calibration (w=1-pn) w' = p0 + p1(w-eta) - 1st OS nnet calibration
      pnsum = 1 - m_P0_Cal_OS_nnK1 - m_P1_Cal_OS_nnK1 * ( (1-pnsum) - m_Eta_Cal_OS_nnK1 );
      
      // Throw away poorly significant tags
      if(pnsum < m_ProbMin_OS || tagdecision == 0)
      	{
      	  pnsum = 0.50;
      	  tagdecision = 0;
      	}

      // New OS tag decision and mistag with OS_nnetKaon
      B_s0_TAGDECISION_OS_wNNK_calib = tagdecision;
      double B_s0_TAGOMEGA_OS_wNNK_first = 1-pnsum ;
      //==========================================================================================================
      // END OF OS COMBINATION WITH nnetKaon TAGGER
      //==========================================================================================================



      //==========================================================================================================
      //  APPLY NOW ALL CALIBRATIONS
      //==========================================================================================================

      //CALIBRATION OF OS COMBINATION WITH NNETK:
      //Apply the 2nd OS nnet calibration
      if(B_s0_TAGDECISION_OS_wNNK_calib == 0) B_s0_TAGOMEGA_OS_wNNK_first = 0.5; // untagged
      else if(B_s0_TAGOMEGA_OS_wNNK_first <0.001  || B_s0_TAGOMEGA_OS_wNNK_first >= 0.5 ) {
	B_s0_TAGDECISION_OS_wNNK_calib = 0;
	B_s0_TAGOMEGA_OS_wNNK_first = 0.5;
      }
      Double_t m_P0_Cal_OS_nnK2  = 0.422;
      Double_t m_P1_Cal_OS_nnK2  = 0.993;
      Double_t m_Eta_Cal_OS_nnK2 = 0.422;
      B_s0_TAGOMEGA_OS_wNNK_calib = m_P0_Cal_OS_nnK2 + m_P1_Cal_OS_nnK2 * ( B_s0_TAGOMEGA_OS_wNNK_first - m_Eta_Cal_OS_nnK2 );

      if(B_s0_TAGDECISION_OS_wNNK_calib == 0) B_s0_TAGOMEGA_OS_wNNK_calib = 0.5; // untagged
      else if(B_s0_TAGOMEGA_OS_wNNK_calib <0.001  || B_s0_TAGOMEGA_OS_wNNK_calib >= 0.5 ) {
	B_s0_TAGDECISION_OS_wNNK_calib = 0;
	B_s0_TAGOMEGA_OS_wNNK_calib = 0.5;
      }


      //CALIBRATION OF OS COMBINATION WITH CUT-BASED KAON:
      if(B_s0_TAGDECISION_OS == 0) B_s0_TAGOMEGA_OS = 0.5; // untagged
      else if(B_s0_TAGOMEGA_OS <0.001  || B_s0_TAGOMEGA_OS >= 0.5 ) {
	B_s0_TAGDECISION_OS = 0;
	B_s0_TAGOMEGA_OS = 0.5;
      }

      Double_t m_P0_Cal_OS_CBK  = 0.3853;
      Double_t m_P1_Cal_OS_CBK  = 0.982;
      Double_t m_Eta_Cal_OS_CBK = 0.3791;
      B_s0_TAGOMEGA_OS_wCBK_calib = m_P0_Cal_OS_CBK + m_P1_Cal_OS_CBK * ( B_s0_TAGOMEGA_OS - m_Eta_Cal_OS_CBK );
      B_s0_TAGDECISION_OS_wCBK_calib = B_s0_TAGDECISION_OS;

      if(B_s0_TAGDECISION_OS_wCBK_calib == 0) B_s0_TAGOMEGA_OS_wCBK_calib = 0.5; // untagged
      else if(B_s0_TAGOMEGA_OS_wCBK_calib <0.001  || B_s0_TAGOMEGA_OS_wCBK_calib >= 0.5 ) {
	B_s0_TAGDECISION_OS_wCBK_calib = 0;
	B_s0_TAGOMEGA_OS_wCBK_calib = 0.5;
      }


      //CALIBRATION OF SS NNET KAON:
      if(B_s0_SS_nnetKaon_DEC == -1000) { // untagged
	B_s0_SS_nnetKaon_DEC = 0;
	B_s0_SS_nnetKaon_PROB = 0.5;
      } else if(B_s0_SS_nnetKaon_PROB <0.001  || B_s0_SS_nnetKaon_PROB >= 0.5 ) { 
	B_s0_SS_nnetKaon_DEC = 0;
	B_s0_SS_nnetKaon_PROB = 0.5;
      }

      Double_t m_P0_Cal_SS_NNK  = 0.4499;
      Double_t m_P1_Cal_SS_NNK  = 0.9755;
      Double_t m_Eta_Cal_SS_NNK = 0.4449;
      B_s0_SS_nnetKaon_PROB_calib = m_P0_Cal_SS_NNK + m_P1_Cal_SS_NNK * ( B_s0_SS_nnetKaon_PROB - m_Eta_Cal_SS_NNK );
      B_s0_SS_nnetKaon_DEC_calib = B_s0_SS_nnetKaon_DEC;      

      if(B_s0_SS_nnetKaon_DEC_calib == 0) B_s0_SS_nnetKaon_PROB_calib = 0.5; // untagged
      if(B_s0_SS_nnetKaon_PROB_calib <0.001  || B_s0_SS_nnetKaon_PROB_calib >= 0.5 ) { 
	B_s0_SS_nnetKaon_DEC_calib = 0;
	B_s0_SS_nnetKaon_PROB_calib = 0.5;
      }

      //CALIBRATION OF SS CUTBASED KAON:
      if(B_s0_SS_Kaon_DEC == -1000) { // untagged
	B_s0_SS_Kaon_DEC = 0;
	B_s0_SS_Kaon_PROB = 0.5;
      } else if(B_s0_SS_Kaon_PROB <0.001  || B_s0_SS_Kaon_PROB >= 0.5 ) { 
	B_s0_SS_Kaon_DEC = 0;
	B_s0_SS_Kaon_PROB = 0.5;
      }

      Double_t m_P0_Cal_SS_CBK  = 0.390;
      Double_t m_P1_Cal_SS_CBK  = 1.715;
      Double_t m_Eta_Cal_SS_CBK = 0.343;
      B_s0_SS_Kaon_PROB_calib = m_P0_Cal_SS_CBK + m_P1_Cal_SS_CBK * ( B_s0_SS_Kaon_PROB - m_Eta_Cal_SS_CBK );
      B_s0_SS_Kaon_DEC_calib = B_s0_SS_Kaon_DEC;      

      if(B_s0_SS_Kaon_DEC_calib == 0) B_s0_SS_Kaon_PROB_calib = 0.5; // untagged
      if(B_s0_SS_Kaon_PROB_calib <0.001  || B_s0_SS_Kaon_PROB_calib >= 0.5 ) { 
	B_s0_SS_Kaon_DEC_calib = 0;
	B_s0_SS_Kaon_PROB_calib = 0.5;
      }


      //Fill the branches with CALIBRATED TAGGERS      
      bB_s0_TAGDECISION_OS_wNNK_calib->Fill();
      bB_s0_TAGOMEGA_OS_wNNK_calib->Fill();

      bB_s0_TAGDECISION_OS_wCBK_calib->Fill();
      bB_s0_TAGOMEGA_OS_wCBK_calib->Fill();

      bB_s0_SS_nnetKaon_DEC_calib->Fill();
      bB_s0_SS_nnetKaon_PROB_calib->Fill();

      bB_s0_SS_Kaon_DEC_calib->Fill();
      bB_s0_SS_Kaon_PROB_calib->Fill();

      branch_polarity->Fill(); 
      if (isMC) {
         branch_pythia->Fill(); 
      }
   }
 
   if (outputTree) {
      cout << "Merging tree into output." << endl;
      TList trees;
      trees.Add(newtree);
      outputTree->Merge(&trees);
   }
   return newtree;
}
