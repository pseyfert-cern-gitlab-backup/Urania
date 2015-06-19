//	To Run in CINT:
//	
//	root -q -b "CreateNtupleB.C(\"/tmp/rcurrie/Pass2-Bs-Up.root\", \"B_s0\")"
//	
//	To Compile:
//	
//	g++ -Wall -Wextra -Wsign-compare -Wmissing-noreturn -msse -msse2 -m3dnow -g -ansi -O3 -funroll-all-loops `root-config --cflags --libs --ldflags` -lTreePlayer -Wall -g CreateNtupleB.C -o CreateNtupleB
//	./CreateNtupleB /tmp/rcurrie/Pass2-Bs-Up.root B_s0
//	
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

//#	The name of the 'Ntuple' objects in the ROOT files
#define GLOBAL_NTUPLE_NAME "DecayTree"

//#	Compression level to use for the output_file. (This may easily be changed to be the same as the input for convenience)
int _GLOBAL_COMPRESSION = 0;

//#	Algorithm for Calculating the candidate with the Best PV per Evenet
void best_vtx_chi2_cut( TString input_file, TString input_branch, TString output_file, TString output_branch, TString pre_cuts );

//#	Algorithm for Copying data from "input_branch" in an "input_file" to an "output_branch" in an "output_file"
void CopyBranch( TString input_file, TString input_branch, TString output_file, TString output_branch, TString output_type );

//#	Algorithm for Creating a new branch "output_branch" in an "output_file", this is created by evaluating the "Relation" for all events in the "input_file"
void CreateBranch( TString input_file, TString Relation, TString output_file, TString output_branch, TString output_type );

//#	Create an empty ttree in an otherwise empty ROOT file
void template_NtupleB_File( TString output_file="output.root" );

//#	The main body of code for creating NtupleB
void CreateNtupleB( TString input_file, TString B_NAME = "B_s0" );

//#	Window to the code when compiled and run externally to ROOT rather than in CINT
#ifndef __CINT__
int main( int argc, char* argv[] )
{
	//	Give standard Usage information and exit if we have the wrong number of inputs
	cout << "\n\nUsage:\n" << "\t\t" << argv[0] << "\t\t" << "Input_File.root" << "\t\t" << "B_s0 or B0" << endl;
	if( argc != 3 ) {	return(-1);	}

	//	If we have the right number of inputs, Create NtupleB
	CreateNtupleB( argv[1], argv[2] ); 
	return 0;
}
#endif


//#	Create the output file with an empty Ntuple
void CreateNtupleB( TString input_file, TString B_NAME )
{
	cout << "\n" << endl;

	//#	Output FileName
	TString output_file( B_NAME ); output_file.Append("_Output.root");

	//#	Some Setup Parameters
	TString input_tree_path=GLOBAL_NTUPLE_NAME;

	//#	Create an empty output file
	template_NtupleB_File( output_file );


	//#		Most Data is stored in FLOAT or INT format, RooFit doesn't handle Bool_t columns (I blame RooFit) so store all Boolean decisions as INTs
	//#
	TString INT="Int_t";
	TString FLOAT="Float_t";
	TString BOOL="Bool_t";




	//#       Create an empty output file with the same compression level as the input NtupleA (can easily change this to compression_level=9 but this may be slower)
	TFile* input_file_obj = new TFile( input_file, "READ" );
	_GLOBAL_COMPRESSION = input_file_obj->GetCompressionLevel();
	TTree* input_tree = (TTree*) gDirectory->Get( input_tree_path );

	//#       Need some mechanism for identifying the 2nd Daughter
	TString DAU2_NAME="";
	if ( input_tree->GetBranch( "phi_1020_ID" )	)	{	DAU2_NAME = "phi_1020" ;	}
	else if( input_tree->GetBranch( "Kst_892_0_ID")	)	{	DAU2_NAME = "Kst_892_0" ;	}
	else if( input_tree->GetBranch( "Kplus_ID"    )	)	{	DAU2_NAME = "Kplus" ;		}
	else if( input_tree->GetBranch( "Kminus_ID"   )	)	{	DAU2_NAME = "Kminus" ;		}

	input_file_obj->Close();





	//#     Same for _ALL_ trees
	CopyBranch( input_file, "eventNumber", output_file, "eventNumber", INT );
	CopyBranch( input_file, "runNumber", output_file, "runNumber", INT );



	//#     First Daughter (always J/psi)
	CopyBranch( input_file, "J_psi_1S_ID", output_file, "piddau1", INT );
	CopyBranch( input_file, "J_psi_1S_MM", output_file, "mdau1", FLOAT );
	CopyBranch( input_file, "J_psi_1S_MMERR", output_file, "sigmadau1", FLOAT );

	//#	Now 2nd Daughter has been identified
	CopyBranch( input_file, TString( DAU2_NAME + "_ID" ), output_file, "piddau2", INT );
	CopyBranch( input_file, TString( DAU2_NAME + "_MM" ), output_file, "mdau2", FLOAT );
	CopyBranch( input_file, TString( DAU2_NAME + "_MMERR" ), output_file, "sigmamdau2", FLOAT );



	//#	Identify the Decay Type

	//#	using logical conditions true = 1, false = 0
	//#       
	//#                      jpsi/phi        jpsi/k+        jpsi/k-          jpsi/k*                jpsi/k*         jpsi/k*bar
	TString pid_calc("(piddau2==333)*40+(piddau2==321)*10+(piddau2==-321)*11+(piddau2==313)*20+(piddau2==-313)*21+(piddau2==310)*30");

	CreateBranch( output_file, pid_calc, output_file, "decaytype", INT );




	//#	B Candidate
	CopyBranch( input_file, TString( B_NAME + "_ID" ), output_file, "pid", INT );

	//#	B Properties
	CopyBranch( input_file, TString( B_NAME + "_P" ), output_file, "B_P", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_PT" ), output_file, "B_Pt", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_LOKI_ETA" ), output_file, "B_eta", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_LOKI_PHI" ), output_file, "B_phi", FLOAT );

	//#	B Candidate Mass
	CopyBranch( input_file, TString( B_NAME + "_LOKI_MASS_JpsiConstr"), output_file, "mass", FLOAT );
	CreateBranch( input_file, "0", output_file, "sigmam", FLOAT );

	//#	B Candidate Time	Want time in ps
	CreateBranch( input_file, TString( B_NAME + "_LOKI_DTF_CTAU/0.299792458" ), output_file, "time", FLOAT );
	CreateBranch( input_file, TString( B_NAME + "_LOKI_DTF_CTAUERR/0.299792458" ), output_file, "sigmat", FLOAT );





	//#	Transverse Angles
	CreateBranch( input_file, TString( "cos("+B_NAME + "_ThetaTr)" ), output_file, "trcostheta", FLOAT );
	CreateBranch( input_file, TString( "cos("+B_NAME + "_ThetaVtr)" ), output_file, "trcospsi", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_PhiTr" ), output_file, "trphi", FLOAT );


	//#	Helicity Angles
	CreateBranch( input_file, TString( "cos("+B_NAME + "_ThetaK)" ), output_file, "helcosthetaK", FLOAT );
	CreateBranch( input_file, TString( "cos("+B_NAME + "_ThetaL)" ), output_file, "helcosthetaL", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_Phi" ), output_file, "helphi", FLOAT );





	//#	Tagging Info
	CopyBranch( input_file, TString( B_NAME + "_TAGDECISION" ), output_file, "tagdecision", INT );
	CopyBranch( input_file, TString( B_NAME + "_TAGCAT" ), output_file, "tagcat", INT );
	CopyBranch( input_file, TString( B_NAME + "_TAGOMEGA" ), output_file, "tagomega", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_TAGDECISION_OS" ), output_file, "tagdecision_os", INT );
	CopyBranch( input_file, TString( B_NAME + "_TAGCAT_OS" ), output_file, "tagcat_os", INT );
	CopyBranch( input_file, TString( B_NAME + "_TAGOMEGA_OS" ), output_file, "tagomega_os", FLOAT );
	CopyBranch( input_file, TString( B_NAME + "_SS_Kaon_DEC" ), output_file, "tagdecision_ss", INT );
	CopyBranch( input_file, TString( B_NAME + "_SS_Kaon_PROB" ), output_file, "tagomega_ss", FLOAT );



	//#     Clone Information
	CopyBranch( input_file, "klClone", output_file, "klClone", INT );
	CopyBranch( input_file, "type1Clone", output_file, "type1Clone", INT );
	CopyBranch( input_file, "type2Clone", output_file, "type2Clone", INT );
	CopyBranch( input_file, "polarity", output_file, "polarity", INT );





	//#	Tagging Info


	//#	Parameters are boolean so can be used in simple logic decision

	TString unbiased_cut( B_NAME+"Hlt1DiMuonHighMassDecision_TOS && "+B_NAME+"Hlt2DiMuonJPsiDecision_TOS" );
	TString biased_cut( "("+B_NAME+"Hlt1TrackMuonDecision_TOS || "+B_NAME+"Hlt1TrackAllL0Decision_TOS) && "+B_NAME+"Hlt2DiMuonJPsiDecision_TOS");


	//#	Create the Tagging Branches
	CreateBranch( input_file, "triggeredByUnbiasedHlt1AndHlt2", output_file, "triggeredByUnbiasedHlt1AndHlt2", INT );
	CreateBranch( input_file, "triggeredByBiasedHlt1AndHlt2", output_file, "triggeredByBiasedHlt1AndHlt2", INT );





	//#	'Apply' Cuts



	//#	Quality Cut
	TString sel_quality_cut( "( ("+B_NAME+"_LOKI_DTF_CHI2NDOF > 0) && ("+B_NAME+"_LOKI_DTF_VCHI2NDOF > 0) )" );

	CreateBranch( input_file, sel_quality_cut, output_file, "sel_qualitycut", INT );




	//#	CleanTail Cut
	TString sel_cleantail_cut("("+B_NAME+"_MINIPCHI2NEXTBEST > 50 || "+B_NAME+"_MINIPCHI2NEXTBEST < 0 )");

	CreateBranch( input_file, sel_cleantail_cut, output_file, "sel_cleantail", INT );




	//#	Mass Cuts on the Daughters


	//#	Mass cut varies with each second daughter but is the same for daughter1
	TString sel_dau1mass_cut( "abs(J_psi_1S_MM - 3090) < 60" );
	TString sel_dau2mass_cut="";
	if( DAU2_NAME == "phi_1020")		sel_dau2mass_cut.Append("abs(phi_1020_MM-1019.46)<12");
	else if( DAU2_NAME == "Kst_892_0")	sel_dau2mass_cut.Append("abs(Kst_892_0_MM-892)<70");
	else if( DAU2_NAME == "Kplus")		sel_dau2mass_cut.Append("Bplus_LOKI_MASS_JpsiConstr>5100 && Bplus_LOKI_MASS_JpsiConstr<5450");
	else if( DAU2_NAME == "Kminus")		sel_dau2mass_cut.Append("Betss_LOKI_MASS_JpsiConstr>5100 && Bplus_LOKI_MASS_JpsiConstr<5450");


	//	Create column with Mass Cut on Daughter 1
        CreateBranch( input_file, sel_dau1mass_cut, output_file, "sel_daughter1", INT );

	//	Create column with Mass Cut on Daughter 2
	CreateBranch( input_file, sel_dau2mass_cut, output_file, "sel_daughter2", INT );


	//#	Clone Cuts
	CreateBranch( input_file, "klClone==0", output_file, "sel_clonecut", INT );


	//#	Best Vertex


	//	Cuts Applied before the best primary vertex before the event is selected
	TString PreSel_Best_Vertex("sel_daughter1 && sel_daughter2 && sel_cleantail && sel_qualitycut && sel_clonecut");

	//#	Copy the discriminator to NtupleB to allow people to 
	CopyBranch( input_file, TString( B_NAME+"_LOKI_DTF_VCHI2NDOF" ), output_file, TString( B_NAME+"_LOKI_DTF_VCHI2NDOF" ), FLOAT );

	//#	Create the best PV
	best_vtx_chi2_cut( input_file, TString( B_NAME+"_LOKI_DTF_VCHI2NDOF" ), output_file, "sel_onecand", PreSel_Best_Vertex );





	//#	Full Selection Applied
	TString full_sel( PreSel_Best_Vertex );
	full_sel.Append("&& sel_onecand" );

	//#	Write out the 'final' decision
	CreateBranch( output_file, full_sel, output_file, "sel", INT );

}

//#	'Setup' the Output File
//#
void template_NtupleB_File( TString output_file )
{
	//#	Create the NTupleA file which will contain the NtupleB Data
	TFile* output_root_file = new TFile( output_file, "RECREATE" );
	output_root_file->SetCompressionLevel( _GLOBAL_COMPRESSION );
	TTree* output_TTree = new TTree( GLOBAL_NTUPLE_NAME, GLOBAL_NTUPLE_NAME );
	//#	Want only EVER 1 copy of the TTree
	output_TTree->Write("",TObject::kOverwrite);
	output_root_file->Close();
}

//#	Calculate which candidate per event has the best Chi2 based on the variable "input_branch"
void best_vtx_chi2_cut( TString input_file, TString input_branch, TString output_file, TString output_branch, TString pre_cuts )
{
	cout << "\nFinding Events with Best Vertex from:  " << input_branch << "   Only considering events which have passed the cut:   " << pre_cuts << endl << endl;

	//#       Read the input Ntuple as ReadOnly
	TFile* input_root_file = new TFile( input_file, "READ" );
	TTree* input_tree = (TTree*) gDirectory->Get( GLOBAL_NTUPLE_NAME );
	input_tree->AddBranchToCache( input_branch );

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

			Int_t best_entry =  i;									//#	Best entry number (i.e. entry num of best chi2)

			//#	Loop forward over all other events in the file
			for( Int_t j=i+1; j< total_entries; ++j )
			{
				//#	Check if event has already passes the previous cuts
				input_tree->GetEntry( j, 0 );							//#	Run/Event Num & chi2
				output_tree->GetEntry( j, 0 );							//#	Previous cuts

				//#	Again, only consider events passing the previous sets of cuts
				if( Int_t( previous_cut_object->EvalInstance(j) ) == 1 )
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
void CopyBranch( TString input_file, TString input_branch, TString output_file, TString output_branch, TString output_type )
{
	//#       Some Setup Parameters
	TString input_tree_path=GLOBAL_NTUPLE_NAME;

	//#	Read the input Ntuple as ReadOnly
	TFile* input_root_file = new TFile( input_file, "READ" );
	TTree* input_tree = (TTree*) gDirectory->Get( input_tree_path );


	//#	Read the output Ntuple for Modification
	TFile* output_root_file = new TFile( output_file, "UPDATE" );
	output_root_file->SetCompressionLevel( _GLOBAL_COMPRESSION );
	TTree* output_tree = (TTree*) gDirectory->Get( GLOBAL_NTUPLE_NAME );


	//#	Get the input Leaf
	TBranch* input_branch_object = (TBranch*) input_tree->GetBranch( input_branch );
	TLeaf* input_branch_leaf = (TLeaf*) input_branch_object->GetListOfLeaves()->First();

	TString input_type = input_branch_leaf->GetTypeName();

	//#	Determine if the output datatype matches the input datatype or not
	bool recast = false;

	if( !(input_type == output_type) )
	{
		cout << "Warning!, input type for branch " << input_branch << " is not of type " << output_type << " attempting to recast" << endl;
		recast = true;
	}

	//#	Need to give extensions to Titles to know what type the branch is
	TString output_ext="";
	Int_t myInt=0;	Float_t myFloat=0;	Bool_t myBool=false;	Double_t myDouble=0;

	void* input_object_pointer = NULL;
	void* output_object_pointer = NULL;

	if( output_type == "Int_t"  )
	{
		output_ext = "/I";
		output_object_pointer = &myInt;
	}
	else if( output_type == "Float_t")
	{
		output_ext = "/F";
		output_object_pointer = &myFloat;
	}
	else if( output_type == "Bool_t" )
	{
		output_ext = "/O";
		output_object_pointer = &myBool;
	}

	if( input_type == "Int_t")		{	input_object_pointer = &myInt;		}
	else if( input_type == "Float_t")	{	input_object_pointer = &myFloat;	}
	else if( input_type == "Bool_t")	{	input_object_pointer = &myBool;		}
	else if( input_type == "Double_t")	{	input_object_pointer = &myDouble;	}

	//#       Set the Address of the Branch of the input_tree
	input_tree->SetBranchAddress( input_branch, input_object_pointer );

	//#	Create the output Branch
	TBranch* output_branch_obj = output_tree->Branch( output_branch, output_object_pointer,  TString( output_branch + output_ext ) );


	//#	Not 100% sure why this is required, but there are serious problems when it isn't present
	Long64_t entries = input_tree->GetEntriesFast();
	output_tree->SetEntries( entries );


	//#	Let the user know what operation is being performed so it doesn't look like the process has stalled
	cout << "\nCopying Data to: " << setw(34) << output_branch << "\t\tfrom:" << setw(80) << input_branch << endl;

	//#	Actually copy the data

	//#	If the data isn't in the format we expect then we need to re-cast the object between primatives
	if( recast )
	{
		for( Long64_t i=0; i< entries; ++i )
		{
			input_tree->LoadTree( i );
			input_branch_object->GetEntry( i );

			if( input_type == "Double_t" )
			{
				if( output_type == "Float_t")	{	myFloat = Float_t(myDouble);	}
				if( output_type == "Int_t")	{	myInt = Int_t(myDouble);	}
				if( output_type == "Bool_t")	{	myBool = Bool_t(myDouble);	}
			}

			if( input_type == "Float_t" )
			{
				if( output_type == "Int_t")	{	myInt = Int_t(myFloat);		}
				if( output_type == "Bool_t")	{	myBool = Int_t(myFloat);	}
			}

			if( input_type == "Int_t" )
			{
				if( output_type == "Float_t")	{	myFloat = Float_t(myInt);	}
				if( output_type == "Bool_t")	{	myBool = Bool_t(myInt);		}
			}

			if( input_type == "Bool_t" )
			{
				if( output_type == "Float_t")	{	myFloat = Float_t(myBool);	}
				if( output_type == "Int_t")	{	myInt = Int_t(myBool);		}
			}

			//#	Put this entry into the 
			output_branch_obj->Fill();
		}
	}
	//#	if the data is in the correct format we can just copy the result
	else
	{
		for(Long64_t i=0; i< entries; ++i)
		{
			input_tree->GetEntry( i );
			output_branch_obj->Fill();
		}
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
void CreateBranch( TString input_file, TString Relation, TString output_file, TString output_branch, TString output_type )
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

	void* output_object_pointer = NULL;

	//#	Need to give extensions to Titles to know what type the branch is
	TString output_ext="";
	Int_t myInt=0;	Float_t myFloat=0;	Bool_t myBool=false;	Double_t myDouble=0;

	//#       Need to give extensions to Titles to know what type the branch is
	if( output_type == "Int_t"  )
	{
		output_ext = "/I";
		output_object_pointer = &myInt;
	}
	else if( output_type == "Float_t")
	{
		output_ext = "/F";
		output_object_pointer = &myFloat;
	}
	else if( output_type == "Bool_t" )
	{
		output_ext = "/O";
		output_object_pointer = &myBool;
	}
	else if( output_type == "Double_t" )
	{
		output_ext = "/D";
		output_object_pointer = &myDouble;
	}

	//#	Create a TTreeForumla instance
	//#	This object is the object which evaulates cutstrings for TTrees
	TTreeFormula* ttree_formula_obj = new TTreeFormula( "newfomula", Relation, input_tree );

	//#       Create the output Branch
	TBranch* output_branch_obj = output_tree->Branch( output_branch, output_object_pointer, TString( output_branch+output_ext ) );


	//#	Again not sure why I should have to SetEntries but it doesn't work without it
	Long64_t entries = input_tree->GetEntriesFast();
	output_tree->SetEntries( entries );

	//print '\nCreating New Branch:%*s\tby Evaluating:\t%*s\n' % ( 36, output_branch, 70, str(Relation) ) 
	cout << "\nCreating New Branch: " << setw(30) << output_branch << "\t\tfrom: " << setw(80) << Relation << endl;

	//#	Evaluate the forumla for each row and store the result in the new TBranch
	for( Long64_t i=0; i< entries; ++i)
	{
		input_tree->GetEntry( i );

		//#	Evaluate and convert the result
		if ( output_type == "Float_t" )		{	myFloat = Float_t( ttree_formula_obj->EvalInstance(i) );	}
		else if ( output_type == "Int_t" )	{	myInt = Int_t( ttree_formula_obj->EvalInstance(i) );		}
		else if ( output_type == "Bool_t" )	{	myBool = Bool_t( ttree_formula_obj->EvalInstance(i) );		}
		else if ( output_type == "Double_t" )	{	myDouble = Double_t( ttree_formula_obj->EvalInstance(i) );	}

		output_branch_obj->Fill();
	}

	//#	Save the output
	output_tree->Write("",TObject::kOverwrite);

	//#	Close the Files
	output_root_file->Close();
	input_root_file->Close();
}

