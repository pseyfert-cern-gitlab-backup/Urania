//#define isMC                                                                                                                                                                                                                               
//#define SSpion // uses SSpion tagger (Bu and Bd) ELSE SSkaon (Bs only) 
//
//	To Compile:
//	
//	g++ -Wall -Wextra -Wsign-compare -Wmissing-noreturn -msse -msse2 -m3dnow -g -ansi -O3 -funroll-all-loops `root-config --cflags --libs --ldflags` -lTreePlayer -Wall -g CreateNtupleB_withFullyCalibratedMistag.C -o CreateNtupleB_withFullyCalibratedMistag
//	./CreateNtupleB_withFullyCalibratedMistag ntuplaA.root B_s0
//	
//	(( to Run in CINT:
//	(( root -q -b "CreateNtupleB.C(\"ntuplaA.root", \"B_s0\")"
//
// =================================================================================================
//	
//     WARNING, M. Dorigo, 23 October 2013:
// 
//     Tagging variables are now:
//     
//     OS combination with cut-based Kaon tagger: tagdecision_os_cb, tagomega_os_cb;
//     OS combination with nnet      Kaon tagger: tagdecision_os_nn, tagomega_os_nn;
//
//     SS combination with cut-based Kaon tagger: tagdecision_ss_cb, tagomega_ss_cb;
//     SS combination with nnet      Kaon tagger: tagdecision_ss_nn, tagomega_ss_nn;
//
//     Mistag are fully calibrated. That allows to use in the tagged time-dependent fit p0 = <eta> and p1=1 for all tagging categories. 
//
//	ROOT Headers
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFormula.h"
#include "TString.h"
#include "TTreeFormula.h"
//	System Headers
#include <iomanip>
#include <iostream>
#include <stdio.h>

using namespace::std;

namespace {
   map<string, string> extensions;
}

template<typename T> 
TString extension()
{
   if (extensions.empty()) {
      extensions.insert(make_pair("f", "/F"));
      extensions.insert(make_pair("d", "/D"));
      extensions.insert(make_pair("i", "/I"));
      extensions.insert(make_pair("j", "/i"));
      extensions.insert(make_pair("y", "/l"));
      extensions.insert(make_pair("b", "/O"));
   }

   map<string, string>::const_iterator it = extensions.find(typeid(T).name());
   if (it != extensions.end()) {
      return TString(it->second.c_str());
   } else {
      cout << "Warning, cannot find extension for type " << typeid(T).name() << endl;
      return "";
   }
}

//#	The name of the 'Ntuple' objects in the ROOT files
#define GLOBAL_NTUPLE_NAME "DecayTree"

//#	Compression level to use for the output_file. (This may easily be changed
//  to be the same as the input for convenience)

int _GLOBAL_COMPRESSION = 9;

//#	Algorithm for Calculating the candidate with the Best PV per Evenet
void best_vtx_chi2_cut( TString input_file, TString input_branch, TString output_file, TString output_branch, TString pre_cuts );

//#	Algorithm for Copying data from "input_branch" in an "input_file" to an "output_branch" in an "output_file"
template<typename T>
void CopyBranch( TString input_file, TString input_branch, TString output_file, TString output_branch);

//#	Algorithm for Creating a new branch "output_branch" in an "output_file", this is created by evaluating the "Relation" for all events in the "input_file"
template<typename T>
void CreateBranch( TString input_file, TString Relation, TString output_file, TString output_branch);

//#	Create an empty ttree in an otherwise empty ROOT file
bool template_NtupleB_File( TString output_file="output.root" );

//#	The main body of code for creating NtupleB
bool CreateNtupleB( TString input_file, TString B_NAME, TString output_file, bool include_cleantail = true );

//#	The function which does the fetching from a ROOT file
template<typename T>
vector<T> Buffer_Branch( TTree* input_tree, TString input_branch, TString cut_string="" );

//#	Window to the code when compiled and run externally to ROOT rather than in CINT
#ifndef __CINT__
int main( int argc, char* argv[] )
{
	//	Give standard Usage information and exit if we have the wrong number of inputs
   cout << "Usage:" << " " << argv[0] << " " << "Input_File.root" 
        << " B_s0 or B0 [output_file.root]" << endl;
	if( argc < 3 ) {
     return(-1);
	}

  vector<string> args;
  vector<string> opts;
  // skip program name argv[0] if present
  argc -= (argc > 0);
  argv += (argc > 0);

  // Loop over arguments
  bool do_args = false;
  for (int i = 0; i < argc; ++i) {
     if (!do_args && !strncmp(argv[i], "--", 2)) {
        opts.push_back(string(argv[i]));
     } else if (!do_args) {
        do_args = true;
     }
     if (do_args) {
        args.push_back(string(argv[i]));
     }
  }
  // Check for our option
  bool include_cleantail = true; 
  for (vector<string>::const_iterator it = opts.begin(), end = opts.end(); it != end; ++it) {
     if (*it == "--no-cleantail") {
        include_cleantail = false;
     }
  }

	//	If we have the right number of inputs, Create NtupleB
  TString output_filename(args[1]);
  output_filename += "Output.root";
  if (args.size() == 3) {
     output_filename = args[2].c_str();
  }
	bool success = CreateNtupleB( args[0].c_str(), args[1].c_str(), output_filename, include_cleantail ); 
  if (success) {
     return 0;
  } else {
     return -1;
  }
}
#endif


//#	Create the output file with an empty Ntuple
bool CreateNtupleB( TString input_file, TString B_NAME, TString output_file, bool include_cleantail)
{
	cout << "\n" << endl;

  TString B_NAME_HLT(B_NAME);

	//#	Some Setup Parameters
	TString input_tree_path=GLOBAL_NTUPLE_NAME;

	//#	Create an empty output file
	bool success = template_NtupleB_File( output_file );
  if (!success) {
     cerr << "Could not open output file " << output_file.Data() << endl;
     return false;
  }

	//#       Create an empty output file with the same compression level as the input NtupleA (can easily change this to compression_level=9 but this may be slower)
	TFile* input_file_obj = new TFile( input_file, "READ" );
  if (!input_file_obj || !input_file_obj->IsOpen()) {
     cerr << "Could not open input file " << input_file.Data() << endl;
     return false;
  }
	_GLOBAL_COMPRESSION = input_file_obj->GetCompressionLevel();
	TTree* input_tree = (TTree*) gDirectory->Get( input_tree_path );
  if (!input_tree) {
     cerr << "Could not get input tree " << input_tree_path.Data() << "." << endl;
     return false;
  }

	//#       Need some mechanism for identifying the 2nd Daughter
	TString DAU2_NAME="";
	if ( input_tree->GetBranch( "phi_1020_ID" )	)	{	DAU2_NAME = "phi_1020" ;	}
	else if( input_tree->GetBranch( "Kst_892_0_ID")	)	{	DAU2_NAME = "Kst_892_0" ;	}
	else if( input_tree->GetBranch( "Kplus_ID"    )	)	{	DAU2_NAME = "Kplus" ;		}
	else if( input_tree->GetBranch( "Kminus_ID"   )	)	{	DAU2_NAME = "Kminus" ;		}

  bool isMC = input_tree->GetBranch( B_NAME + "_TRUETAU" );

  if (input_tree->GetBranch( B_NAME + "_Hlt2DiMuonDetachedJPsiDecision_TOS" )) {
     B_NAME_HLT += "_";
  }

	input_file_obj->Close();

	//#     Same for _ALL_ trees
	CopyBranch<ULong64_t>( input_file, "eventNumber", output_file, "eventNumber");
	CopyBranch<UInt_t>( input_file, "runNumber", output_file, "runNumber");


	//#     First Daughter (always J/psi)
	CopyBranch<Int_t>( input_file, "J_psi_1S_ID", output_file, "piddau1");
	CopyBranch<Double_t>( input_file, "J_psi_1S_MM", output_file, "mdau1");
	CopyBranch<Double_t>( input_file, "J_psi_1S_MMERR", output_file, "sigmadau1");

	//#	Now 2nd Daughter has been identified
	CopyBranch<Int_t>( input_file, TString( DAU2_NAME + "_ID" ), output_file, "piddau2");
	CopyBranch<Double_t>( input_file, TString( DAU2_NAME + "_MM" ), output_file, "mdau2");
	CopyBranch<Double_t>( input_file, TString( DAU2_NAME + "_MMERR" ), output_file, "sigmamdau2");

	//#	Identify the Decay Type

	//#	using logical conditions true = 1, false = 0
	//#       
	//#                      jpsi/phi        jpsi/k+        jpsi/k-          jpsi/k*                jpsi/k*         jpsi/k*bar
	TString pid_calc("(piddau2==333)*40+(piddau2==321)*10+(piddau2==-321)*11 "
                   "+ (piddau2==313)*20+(piddau2==-313)*21+(piddau2==310)*30");

	CreateBranch<Int_t>( output_file, pid_calc, output_file, "decaytype");



  if (isMC) {
     // MC
     CopyBranch<Int_t>( input_file, TString( B_NAME + "_BKGCAT" ), output_file, "bkgcat");
     CopyBranch<Int_t>( input_file, "pythia", output_file, "pythia" );
     CreateBranch<Double_t>( input_file, TString( B_NAME + "_TRUETAU*1000." ), output_file, "truetime");
     CreateBranch<Double_t>( input_file, TString( B_NAME + "_LOKI_DTF_CTAU/0.299792458 - " + B_NAME + "_TRUETAU * 1000." ), output_file, "time_diff");
     CreateBranch<Int_t>( input_file, TString( B_NAME + "_TRUEID" ), output_file, "trueid");
  }

	//#	B Candidate
	CopyBranch<Int_t>( input_file, TString( B_NAME + "_ID" ), output_file, "pid");

	//#	B Properties
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_P" ), output_file, "B_P");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_PT" ), output_file, "B_Pt");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_LOKI_ETA" ), output_file, "B_eta");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_LOKI_PHI" ), output_file, "B_phi");

	//#	B Candidate Mass
        CopyBranch<Double_t>( input_file, TString( B_NAME + "_LOKI_MASS_JpsiConstr"), output_file, "mass_JpsiConstr");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_M"), output_file, "mass");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_MMERR"), output_file, "sigmam");

	//#	B Candidate Time	Want time in ps
	CreateBranch<Double_t>( input_file, TString( B_NAME + "_LOKI_DTF_CTAU/0.299792458" ), output_file, "time");
	CreateBranch<Double_t>( input_file, TString( B_NAME + "_LOKI_DTF_CTAUERR/0.299792458" ), output_file, "sigmat");





	//#	Transverse Angles
	CreateBranch<Double_t>( input_file, TString( "cos("+B_NAME + "_ThetaTr)" ), output_file, "trcostheta");
	CreateBranch<Double_t>( input_file, TString( "cos("+B_NAME + "_ThetaVtr)" ), output_file, "trcospsi");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_PhiTr" ), output_file, "trphi");


	//#	Helicity Angles
	CreateBranch<Double_t>( input_file, TString( "cos("+B_NAME + "_ThetaK)" ), output_file, "helcosthetaK");
	CreateBranch<Double_t>( input_file, TString( "cos("+B_NAME + "_ThetaL)" ), output_file, "helcosthetaL");
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_Phi" ), output_file, "helphi");

	//#	Tagging Info
	CopyBranch<Int_t>( input_file, TString( B_NAME + "_TAGDECISION_OS_wCBK_calib" ), output_file, "tagdecision_os_cb" );
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_TAGOMEGA_OS_wCBK_calib" ),    output_file, "tagomega_os_cb");
	CopyBranch<Int_t>( input_file, TString( B_NAME + "_TAGDECISION_OS_wNNK_calib" ), output_file, "tagdecision_os_nn" );
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_TAGOMEGA_OS_wNNK_calib" ),    output_file, "tagomega_os_nn");
#ifdef SSpion
	CopyBranch<Int_t>( input_file, TString( B_NAME + "_SS_Pion_DEC_new" ),  output_file, "tagdecision_ss" );
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_SS_Pion_PROB_new" ), output_file, "tagomega_ss");
#else
	CopyBranch<Int_t>( input_file, TString( B_NAME + "_SS_nnetKaon_DEC_calib" ),  output_file, "tagdecision_ss_nn" );
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_SS_nnetKaon_PROB_calib" ), output_file, "tagomega_ss_nn");
	CopyBranch<Int_t>( input_file, TString( B_NAME + "_SS_Kaon_DEC_calib" ),  output_file, "tagdecision_ss_cb" );
	CopyBranch<Double_t>( input_file, TString( B_NAME + "_SS_Kaon_PROB_calib" ), output_file, "tagomega_ss_cb");
#endif

	//#     Clone Information
	CopyBranch<Int_t>( input_file, "klClone", output_file, "klClone" );
	CopyBranch<Int_t>( input_file, "type1Clone", output_file, "type1Clone" );
	CopyBranch<Int_t>( input_file, "type2Clone", output_file, "type2Clone" );
	CopyBranch<Int_t>( input_file, "polarity", output_file, "polarity" );


	//#	Parameters are boolean so can be used in simple logic decision

	//TString unbiased_cut( B_NAME_HLT+"Hlt1DiMuonHighMassDecision_Dec" && "+B_NAME_HLT+"Hlt2DiMuonDetachedJPsiDecision_TOS" );
	//TString biased_cut( "("+B_NAME_HLT+"Hlt1TrackMuonDecision_TOS" || "+B_NAME_HLT+"Hlt1TrackAllL0Decision_TOS") && "+B_NAME_HLT+"Hlt2DiMuonDetachedJPsiDecision_TOS" );

	//TString trigger_cut( "("+B_NAME+"Hlt2DiMuonDetachedJPsiDecision_TOS == 1) && ( ("+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_TOS == 1) || ("+B_NAME_HLT+"Hlt1TrackMuonDecision_TOS == 1))" );

	TString trigger_cut_unbiased          ( "("+B_NAME_HLT+"Hlt2DiMuonDetachedJPsiDecision_TOS == 1) && ("+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_Dec == 1 )" );
	TString trigger_cut_unbiased_prescaled( "("+B_NAME_HLT+"Hlt2DiMuonJPsiDecision_TOS == 1)         && ("+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_Dec == 1 )" );
	TString trigger_cut_exclusive_biased  ( "("+B_NAME_HLT+"Hlt2DiMuonDetachedJPsiDecision_TOS == 1) && ("+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_Dec == 0 ) && ("+B_NAME_HLT+"Hlt1TrackMuonDecision_TOS==1 || "+B_NAME_HLT+"Hlt1TrackAllL0Decision_TOS==1)" );

	CreateBranch<Int_t>( input_file, trigger_cut_unbiased		, output_file, "triggerDecisionUnbiased" );
	CreateBranch<Int_t>( input_file, trigger_cut_unbiased_prescaled, output_file, "triggerDecisionUnbiasedPrescaled" );
	CreateBranch<Int_t>( input_file, trigger_cut_exclusive_biased  , output_file, "triggerDecisionBiasedExcl" );

  TString trigger_cut_hlt1_unbiased( "("+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_TOS == 1 )" );
  TString trigger_cut_hlt1_unbiased_dec( "("+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_Dec == 1 )" );
  TString trigger_cut_hlt1_biased( "("+B_NAME_HLT+"Hlt1TrackMuonDecision_TOS == 1 || "+B_NAME_HLT+"Hlt1TrackAllL0Decision_TOS == 1)" );
  TString trigger_cut_hlt1_excl_biased( "("+B_NAME_HLT+"Hlt1TrackMuonDecision_TOS == 1 |"
                                        "| "+B_NAME_HLT+"Hlt1TrackAllL0Decision_TOS == 1)"
                                        " && "+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_TOS == 0" );
  TString trigger_cut_hlt1_excl_biased_dec( "("+B_NAME_HLT+"Hlt1TrackMuonDecision_TOS == 1 |"
                                            "| "+B_NAME_HLT+"Hlt1TrackAllL0Decision_TOS == 1)"
                                            " && "+B_NAME_HLT+"Hlt1DiMuonHighMassDecision_Dec == 0" );
  TString trigger_cut_hlt2_unbiased( "("+B_NAME_HLT+"Hlt2DiMuonJPsiDecision_TOS == 1)");
  TString trigger_cut_hlt2_biased( "("+B_NAME_HLT+"Hlt2DiMuonDetachedJPsiDecision_TOS == 1)" );

  CreateBranch<Int_t>( input_file, trigger_cut_hlt1_unbiased, output_file, "hlt1_unbiased" );
  CreateBranch<Int_t>( input_file, trigger_cut_hlt1_unbiased_dec, output_file, "hlt1_unbiased_dec" );
  CreateBranch<Int_t>( input_file, trigger_cut_hlt1_biased, output_file, "hlt1_biased" );
  CreateBranch<Int_t>( input_file, trigger_cut_hlt1_excl_biased, output_file, "hlt1_excl_biased" );
  CreateBranch<Int_t>( input_file, trigger_cut_hlt1_excl_biased_dec, output_file, "hlt1_excl_biased_dec" );
  CreateBranch<Int_t>( input_file, trigger_cut_hlt2_unbiased, output_file, "hlt2_unbiased" );
  CreateBranch<Int_t>( input_file, trigger_cut_hlt2_biased, output_file, "hlt2_biased" );

	CopyBranch<Double_t>( input_file, "Kplus_PIDK"   , output_file, "Kplus_pidK" );
	CopyBranch<Double_t>( input_file, "Kplus_PIDp"  , output_file, "Kplus_pidp" );
	CopyBranch<Double_t>( input_file, "Kminus_PIDK"   , output_file, "Kminus_pidK" );
	CopyBranch<Double_t>( input_file, "Kminus_PIDp"  , output_file, "Kminus_pidp" );
	CopyBranch<Double_t>( input_file, "muplus_TRACK_CHI2NDOF"   , output_file, "muplus_track_chi2ndof" );
	CopyBranch<Double_t>( input_file, "muminus_TRACK_CHI2NDOF"  , output_file, "muminus_track_chi2ndof" );
	CopyBranch<Double_t>( input_file, "Kplus_TRACK_CHI2NDOF"    , output_file, "Kplus_track_chi2ndof" );
	CopyBranch<Double_t>( input_file, "Kminus_TRACK_CHI2NDOF"   , output_file, "Kminus_track_chi2ndof" );
	CopyBranch<Double_t>( input_file, "muplus_TRACK_GhostProb"  , output_file, "muplus_track_ghostprob" );
	CopyBranch<Double_t>( input_file, "muminus_TRACK_GhostProb" , output_file, "muminus_track_ghostprob" );
	CopyBranch<Double_t>( input_file, "Kplus_TRACK_GhostProb"   , output_file, "Kplus_track_ghostprob" );
	CopyBranch<Double_t>( input_file, "Kminus_TRACK_GhostProb"  , output_file, "Kminus_track_ghostprob" );

	CopyBranch<Double_t>( input_file, "muplus_ProbNNghost"  , output_file, "muplus_ProbNNghost" );
	CopyBranch<Double_t>( input_file, "muminus_ProbNNghost" , output_file, "muminus_ProbNNghost" );
	CopyBranch<Double_t>( input_file, "Kplus_ProbNNghost"   , output_file, "Kplus_ProbNNghost" );
	CopyBranch<Double_t>( input_file, "Kminus_ProbNNghost"  , output_file, "Kminus_ProbNNghost" );

	CopyBranch<Double_t>( input_file, TString( B_NAME+"_ENDVERTEX_CHI2" ), output_file, TString( B_NAME+"_endvertex_chi2" ));
	CopyBranch<Int_t>( input_file, TString( B_NAME+"_ENDVERTEX_NDOF" ), output_file, TString( B_NAME+"_endvertex_ndof" ) );
	CopyBranch<Double_t>( input_file, TString( B_NAME+"_ENDVERTEX_X" ), output_file, TString( B_NAME+"_ENDVERTEX_X" ));
	CopyBranch<Double_t>( input_file, TString( B_NAME+"_ENDVERTEX_Y" ), output_file, TString( B_NAME+"_ENDVERTEX_Y" ));
	CopyBranch<Double_t>( input_file, TString( B_NAME+"_ENDVERTEX_Z" ), output_file, TString( B_NAME+"_ENDVERTEX_Z" ));
	CopyBranch<Double_t>( input_file, TString( B_NAME+"_OWNPV_Z" ), output_file, TString( B_NAME+"_OWNPV_Z" ));
	CopyBranch<Double_t>( input_file, TString( DAU2_NAME+"_ENDVERTEX_CHI2" ), output_file, TString( DAU2_NAME+"_endvertex_chi2" ));
	CopyBranch<Double_t>( input_file, TString( DAU2_NAME+"_ENDVERTEX_NDOF" ), output_file, TString( DAU2_NAME+"_endvertex_ndof" ) );
	CopyBranch<Double_t>( input_file, TString( DAU2_NAME+"_PT" ), output_file, TString( DAU2_NAME+"_pt" ));

	
	CopyBranch<Double_t>( input_file, "muminus_P" , output_file, "muminus_P" );
	CopyBranch<Double_t>( input_file, "muminus_PX" , output_file, "muminus_PX" );
	CopyBranch<Double_t>( input_file, "muminus_PY" , output_file, "muminus_PY" );
	CopyBranch<Double_t>( input_file, "muminus_PZ" , output_file, "muminus_PZ" );
	CopyBranch<Double_t>( input_file, "muminus_LOKI_ETA" , output_file, "muminus_LOKI_ETA" );
	CopyBranch<Double_t>( input_file, "muplus_P" , output_file, "muplus_P" );
	CopyBranch<Double_t>( input_file, "muplus_PX" , output_file, "muplus_PX" );
	CopyBranch<Double_t>( input_file, "muplus_PY" , output_file, "muplus_PY" );
	CopyBranch<Double_t>( input_file, "muplus_PZ" , output_file, "muplus_PZ" );
	CopyBranch<Double_t>( input_file, "muplus_LOKI_ETA" , output_file, "muplus_LOKI_ETA" );
	CopyBranch<Double_t>( input_file, "Kminus_PX" , output_file, "Kminus_PX" );
	CopyBranch<Double_t>( input_file, "Kminus_PY" , output_file, "Kminus_PY" );
	CopyBranch<Double_t>( input_file, "Kminus_PZ" , output_file, "Kminus_PZ" );
	CopyBranch<Double_t>( input_file, "Kminus_LOKI_ETA" , output_file, "Kminus_LOKI_ETA" );
	CopyBranch<Double_t>( input_file, "Kplus_PX" , output_file, "Kplus_PX" );
	CopyBranch<Double_t>( input_file, "Kplus_PY" , output_file, "Kplus_PY" );
	CopyBranch<Double_t>( input_file, "Kplus_PZ" , output_file, "Kplus_PZ" );
	CopyBranch<Double_t>( input_file, "Kplus_LOKI_ETA" , output_file, "Kplus_LOKI_ETA" );
	CopyBranch<Double_t>( input_file, "nPV" , output_file, "nPV" );
	CopyBranch<Double_t>( input_file, "nVeloTracks" , output_file, "nVeloTracks" );
	CopyBranch<Double_t>( input_file, "nTracks" , output_file, "nTracks" );


	//#	'Apply' Cuts



	//#	Quality Cut
	TString sel_quality_cut( "( ("+B_NAME+"_LOKI_DTF_CHI2NDOF > 0) && ("+B_NAME+"_LOKI_DTF_VCHI2NDOF > 0) )" );

	CreateBranch<Int_t>( input_file, sel_quality_cut, output_file, "sel_qualitycut" );




	//#	CleanTail Cut
	TString sel_cleantail_cut("("+B_NAME+"_MINIPCHI2NEXTBEST > 50 || "+B_NAME+"_MINIPCHI2NEXTBEST < 0 )");

	CreateBranch<Int_t>( input_file, sel_cleantail_cut, output_file, "sel_cleantail" );




	//#	Mass Cuts on the Daughters


	//#	Mass cut varies with each second daughter but is the same for daughter1
	TString sel_dau1mass_cut( "abs(J_psi_1S_MM - 3096.916) < 75" );
	TString sel_dau2mass_cut="";
	if( DAU2_NAME == "phi_1020")		sel_dau2mass_cut.Append("abs(phi_1020_MM-1019.46)<12");
	else if( DAU2_NAME == "Kst_892_0")	sel_dau2mass_cut.Append("abs(Kst_892_0_MM-892)<70");
	else if( DAU2_NAME == "Kplus")		sel_dau2mass_cut.Append("Bplus_LOKI_MASS_JpsiConstr>5100 && Bplus_LOKI_MASS_JpsiConstr<5450");
	else if( DAU2_NAME == "Kminus")		sel_dau2mass_cut.Append("Bplus_LOKI_MASS_JpsiConstr>5100 && Bplus_LOKI_MASS_JpsiConstr<5450");


	//	Create column with Mass Cut on Daughter 1
	CreateBranch<Int_t>( input_file, sel_dau1mass_cut, output_file, "sel_daughter1" );

	//	For 1fb of Data (Moriond2012) we are NOT applying the phi cut in the main fitting selection 'sel'

	//	Create column with Mass Cut on Daughter 2
	//CreateBranch<Int_t>( input_file, sel_dau2mass_cut, output_file, "sel_daughter2" );


	//#	Clone Cuts
	CreateBranch<Int_t>( input_file, "klClone==0", output_file, "sel_clonecut" );


	//#	Best Vertex

	//	Cuts Applied before the best primary vertex before the event is selected
	TString PreSel_Best_Vertex;
  if (include_cleantail) {
     PreSel_Best_Vertex = "sel_daughter1 && sel_qualitycut && sel_clonecut && sel_cleantail";
  } else {
     PreSel_Best_Vertex = "sel_daughter1 && sel_qualitycut && sel_clonecut";
  }
     
	//#	Copy the discriminator to NtupleB to allow people to 
	CopyBranch<Double_t>( input_file, TString( B_NAME+"_LOKI_DTF_VCHI2NDOF" ), output_file, TString( B_NAME+"_LOKI_DTF_VCHI2NDOF" ));

	//#	Create the best PV
	best_vtx_chi2_cut( input_file, TString( B_NAME+"_LOKI_DTF_VCHI2NDOF" ), output_file, "sel_onecand", PreSel_Best_Vertex );


	//#	Full Selection Applied
	TString full_sel( PreSel_Best_Vertex );
	full_sel.Append("&& sel_onecand" );

	//#	Write out the 'final' decision
	CreateBranch<Int_t>( output_file, full_sel, output_file, "sel" );

  return true;
}

//#	'Setup' the Output File
//#
bool template_NtupleB_File( TString output_file )
{
	//#	Create the NTupleA file which will contain the NtupleB Data
	TFile* output_root_file = new TFile( output_file, "RECREATE" );
  if (!output_root_file || !output_root_file->IsOpen()) {
     cerr << "Could not open output file " << output_file.Data() << endl;
     return false;
  }
	output_root_file->SetCompressionLevel( _GLOBAL_COMPRESSION );
	TTree* output_TTree = new TTree( GLOBAL_NTUPLE_NAME, GLOBAL_NTUPLE_NAME );
	//#	Want only EVER 1 copy of the TTree
	output_TTree->Write("",TObject::kOverwrite);
	output_root_file->Close();
  return true;
}

//#	Calculate which candidate per event has the best Chi2 based on the variable "input_branch"
void best_vtx_chi2_cut( TString input_file, TString input_branch, TString output_file, TString output_branch, TString pre_cuts )
{
	cout << "Finding Events with Best Vertex from:  " << input_branch 
       << "   Only considering events which have passed the cut:   " << pre_cuts << endl << endl;

	//#       Read the input Ntuple as ReadOnly
	TFile* input_root_file = new TFile( input_file, "READ" );
	TTree* input_tree = (TTree*) gDirectory->Get( GLOBAL_NTUPLE_NAME );

	// TBranch* input_branch_object = (TBranch*) input_tree->GetBranch( input_branch );

	//#       Read the output Ntuple for Modification;
	TFile* output_root_file = new TFile( output_file, "UPDATE" );
	output_root_file->SetCompressionLevel( _GLOBAL_COMPRESSION );
	TTree* output_tree = (TTree*) gDirectory->Get( GLOBAL_NTUPLE_NAME );

	TString chi2_param = input_branch;

	Long64_t total_entries = input_tree->GetEntries();

	//	We want to evaluate these objects i.e. read this information as we loop through the file
	TTreeFormula* previous_cut_object = new TTreeFormula( "previous_cut_value", pre_cuts, output_tree );
	TTreeFormula* run_number_object = new TTreeFormula( "run_number_value", "runNumber", input_tree );
	TTreeFormula* event_number_object = new TTreeFormula( "event_number_value", "eventNumber", input_tree );
	TTreeFormula* best_chi2_param_object = new TTreeFormula( "chi2_param_value", chi2_param, input_tree );


	Bool_t* best_entry_decision = NULL;
	best_entry_decision = new Bool_t[total_entries];

	//#	Default decision is that we don't have the best PV for this event
	for( Long64_t i=0; i< total_entries; ++i )
	{	best_entry_decision[i] = false;	}

	Long64_t i=0;

	//#	Loop over all events in the file
	//#	This has to be a while loop rather than a for loop in order to modify the index object i within the algorithm
	while( i< total_entries )
	{

		//#	Get the new event and run number
		input_tree->GetEntry( i, 0 );									//#	Needed for Run/Event number and chi2 value
		output_tree->GetEntry( i, 0 );									//#	Needed for Result of previous cuts

		//#	Only consider events which have been selected by other cuts
		if( Int_t( previous_cut_object->EvalInstance() ) == 1 )
		{

			//#	Store the run and event number of the entries in this file
			Double_t run_number_global = run_number_object->EvalInstance( i );			//#	First Run Number
			Double_t event_number_global = event_number_object->EvalInstance( i );			//#	First Event Number

			Double_t min_value_found = best_chi2_param_object->EvalInstance(i);			//#	Best chi2 for this run

			Long64_t best_entry =  i;									//#	Best entry number (i.e. entry num of best chi2)

			//#	Loop forward over all other events in the file
			for( Long64_t j = i + 1; j < total_entries; ++j )
			{
				//#	Check if event has already passes the previous cuts
				input_tree->GetEntry( j, 0 );							//#	Run/Event Num & chi2
				output_tree->GetEntry( j, 0 );							//#	Previous cuts

				//#	Again, only consider events passing the previous sets of cuts
				if( Long64_t( previous_cut_object->EvalInstance(j) ) == 1 )
				{

					//#	Get the event and run number of the next event

					Double_t run_number_local = run_number_object->EvalInstance(j);		//#	Run Num for next entry
					Double_t event_number_local = event_number_object->EvalInstance(j);	//#	Event Num for next entry

					//#	Get the new chi2
					Double_t new_param_value = best_chi2_param_object->EvalInstance(j);	//#	chi2 for next entry

					//#	if we have moved to a new run/event exit the local loop and continue the global loop through the file

					if( ! ( (run_number_local==run_number_global) && (event_number_local==event_number_global) ) )
					{	i = j-1;	//#	NB -1 here is correct as we globally increment outside this loop
						break;
					}

					//#	test the new value of the chi2 parameter and determeine if it's a better fit or not
					if( new_param_value < min_value_found )
					{
						min_value_found = new_param_value;
						best_entry = j;
					}
				}
			}

			//#	After making a decison set the best vertex result to true
			best_entry_decision[ best_entry ] = true;

		}

		//#	Move to next entry if this one didn't pass the cuts
		++i;
	}

	//	Integer object used for casting the boolean decision to ints
	Int_t cast_to_int=0;

	//#	Create output Branch
	TBranch* output_branch_obj = output_tree->Branch( output_branch, &cast_to_int, TString( output_branch + "/I") ); 

	//#	Needed for something internal in ROOT
	output_tree->SetEntries( total_entries );

	//#	Store the result of the bestchi2 in this column
	for( Long64_t i=0; i< total_entries; ++i )
	{
		//#	Just to be explicit about what we expect to be written out
		if( best_entry_decision[i] )
		{
			cast_to_int = 1;
		} else {
			cast_to_int = 0;
		}
		output_branch_obj->Fill();
	}

	//#	Write the output and close the file
	output_tree->Write("",TObject::kOverwrite);
	output_root_file->Close();
	input_root_file->Close();
}

//#	Copy the 'input_branch' from the 'input_file' into the 'output_branch' in the 'output_file'
//#
//#	This will check for incompatabilities, warn, and attempt to recast data objects where required
//#
template<typename T>
void CopyBranch(TString input_file, TString input_branch, TString output_file, TString output_branch)
{
	//#       Some Setup Parameters
	TString input_tree_path = GLOBAL_NTUPLE_NAME;

	//#	Read the input Ntuple as ReadOnly
	TFile* input_root_file = new TFile( input_file, "READ" );
	TTree* input_tree = (TTree*) gDirectory->Get( input_tree_path );

  if (!input_tree->GetBranch(input_branch.Data())) {
     return;
  }

	vector<T> input_branch_data = Buffer_Branch<T>( input_tree, input_branch );
  if (input_branch_data.empty()) {
     return;
  }

	//#	Read the output Ntuple for Modification
	TFile* output_root_file = new TFile( output_file, "UPDATE" );
	output_root_file->SetCompressionLevel( _GLOBAL_COMPRESSION );
	TTree* output_tree = (TTree*) gDirectory->Get( GLOBAL_NTUPLE_NAME );


	//#	Need to give extensions to Titles to know what type the branch is
	T output_object;
  TString output_ext = extension<T>();
  
	//#	Create the output Branch
	TBranch* output_branch_obj = output_tree->Branch( output_branch, &output_object,  TString( output_branch + output_ext ) );

	//#	Not 100% sure why this is required, but there are serious problems when it isn't present
	output_tree->SetEntries( input_branch_data.size() );

	//#	Let the user know what operation is being performed so it doesn't look like the process has stalled
	cout << "Copying Data to: " << setw(34) << output_branch << "\t\tfrom:" << setw(80) << input_branch << endl;

	//#	Actually copy the data

	//#	If the data isn't in the format we expect then we need to re-cast the object between primatives
	for(Long64_t i=0; i< (Long64_t)input_branch_data.size(); ++i)
	{
     output_object = input_branch_data[i];
     output_branch_obj->Fill();
	}
  
	//#	Write the Data out
	output_tree->Write("",TObject::kOverwrite);

	//#	Close the ROOT files
	output_root_file->Close();
	input_root_file->Close();
}


//#	Create a new Branch 'output_branch'
//#	
//#	This will evaluate a given 'Relation' which is assumed to be in a cutstring style format
//#	The input objects for the formula _must_ all be in the input_file and it creates a new 'output_branch' of 'output_type' in the output_file
//#
template<typename T>
void CreateBranch( TString input_file, TString Relation, TString output_file, TString output_branch)
{
	//#       Some Setup Parameters
	TString input_tree_path=GLOBAL_NTUPLE_NAME;

	//#       Read the input Ntuple as ReadOnly
	TFile* input_root_file = new TFile( input_file, "READ" );
	TTree* input_tree = (TTree*) gDirectory->Get( input_tree_path );

	//#       Read the output Ntuple for Modification
	TFile* output_root_file = new TFile( output_file, "UPDATE" );
	output_root_file->SetCompressionLevel( _GLOBAL_COMPRESSION );
	TTree* output_tree = (TTree*) gDirectory->Get( GLOBAL_NTUPLE_NAME );

	T output_object;
  TString output_ext = extension<T>();

	vector<T> output_data = Buffer_Branch<T>( input_tree, Relation );

	//#       Create the output Branch
	TBranch* output_branch_obj = output_tree->Branch( output_branch, &output_object, TString( output_branch+output_ext ) );


	//#	Again not sure why I should have to SetEntries but it doesn't work without it
	output_tree->SetEntries( output_data.size() );

	//print '\nCreating New Branch:%*s\tby Evaluating:\t%*s\n' % ( 36, output_branch, 70, str(Relation) ) 
	cout << "Creating New Branch: " << setw(30) << output_branch << "\t\tfrom: " 
       << setw(80) << Relation << endl;

	//#	Evaluate the forumla for each row and store the result in the new TBranch
	for( Long64_t i = 0; i < Long64_t(output_data.size()); ++i)
	{
     //#	Evaluate and convert the result
     output_object = output_data[i];
     output_branch_obj->Fill();
	}

	//#	Save the output
	output_tree->Write("",TObject::kOverwrite);

	//#	Close the Files
	output_root_file->Close();
	input_root_file->Close();
}

template <typename T>
vector<T> Buffer_Branch( TTree* input_tree, TString input_branch, TString cut_string )
{
   vector<T> output_branch_data;
   
   //      By default ROOT limits this to 1M entries, this has been written explicitly for some cases when this is insufficient
   input_tree->SetEstimate( input_tree->GetEntries() );
   
   //      Use TSelector to accesst the data of interest
   input_tree->Draw( input_branch, cut_string, "goff" );
   
   Double_t* temp_pointer = input_tree->GetV1();
   
   for(Long64_t entry_i = 0; entry_i < input_tree->GetSelectedRows(); ++entry_i) {
      output_branch_data.push_back( T(temp_pointer[entry_i]) );
   }
   return output_branch_data;
}

