/* stackergen: Part of the simpletools package
 * (c) Conor Fitzpatrick, 2008
 *
 * If you find this program useful in whole or in part 
 * please cite this paper: 
 *
 * Feel free to send bugreports, feature requests, patches etc to:
 * conor.fitzpatrick@cern.ch
 *
 */

#include <iostream>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TMath.h>
#include <TTree.h>
#include <TStopwatch.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <fstream>
#include "stdio.h"
#include "string"
#include "TStyle.h"
#include "Riostream.h"
#include "TAxis.h"
#include <TRandom3.h>
#include <cctype>
#include <cmath>
#include <vector>
#include <TArrow.h>
#include <TH1F.h>
#include <TH1.h>
#include <TEntryList.h>
#include <TLegend.h>
#include<THStack.h>
#include<TColor.h>
#include<Rtypes.h>
#include<TPaveStats.h>
#include<TVirtualHistPainter.h>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

typedef vector<Bool_t> array1b;
typedef vector<TString> array1s;
typedef vector<TFile*> array1tf;
typedef vector<TTree*> array1tt;
typedef vector<Double_t> array1d;

typedef vector<UInt_t> array1i;
typedef vector<TColor> array1tc;
typedef vector<TEntryList*> array1tel;
typedef vector< vector< TH1F* > > array2th1f;
typedef vector< vector< Double_t > > array2d;
typedef vector< TH1F* > array1th1f;
typedef vector<Double_t*> array1ard;


array1s preprocCuts;
array1s TuplePaths;
array1s LegendNames;
array1s FileNames;
array1i Colors;
array1i FillStyles;
array1s Vars;
array1tf Files;
array1tt Trees;
array1d VarLower;
array1d VarUpper;
array1i VarBins;
array1d Weights;
array1tel elists;
array1s Units;
array1b Axis;
array1i lw;
char pretty[10];
TFile *inFile;
TNtuple *inTuple;
UInt_t evts;
UInt_t loadVars(std::string filename);

UInt_t loadVars(std::string filename){
	ifstream fileStream;
	std::string lineread;
	TString line;
	UInt_t nlines =0;
	TString inString;
	Double_t inDouble;
	Int_t inInt;
	UInt_t linenum =0;
	TString word;
	fileStream.open(filename.c_str());
	if (!fileStream){
		std::cout << "Error in opening var list" << std::endl;
		return EXIT_FAILURE;
	}
	while(!line.ReadLine(fileStream).eof()){

		TObjArray* Strings = line.Tokenize(" \t");
		TIter iString(Strings);
		TObjString* os=0;
		os=(TObjString*)iString();
		linenum++;
		if(!os->GetString().BeginsWith('#')){
			if(Strings->GetEntries() != 6){
				std::cout << filename.c_str() << ": line " << linenum << ": isn't a valid input line. Check the format and try again" << std::endl;
				std::cout << "expected 6 parameters, found " << Strings->GetEntries() << ". Ensure you haven't got extra spaces/tabs and try again." << std::endl;
				exit(EXIT_FAILURE);
			}

			try{
				inString = lexical_cast <string> (os->GetString());
				Vars.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid variable" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();

			try{
				inDouble = lexical_cast <double> (os->GetString());
				VarLower.push_back(inDouble);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid lower double" << std::endl;
				exit(EXIT_FAILURE);
			}


			os=(TObjString*)iString();
			try{
				inDouble = lexical_cast <double> (os->GetString());
				VarUpper.push_back(inDouble);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid upper double" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();
			try{
				inInt = lexical_cast <int> (os->GetString());
				VarBins.push_back(inInt);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid bins int" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();

			try{
				inString = lexical_cast <string> (os->GetString());
				Units.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid units string" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();
			if(os->GetString() == "log"){Axis.push_back(true);}else{
				if(os->GetString() == "lin"){Axis.push_back(false);}else{
					std::cout << filename.c_str() << ": line " << linenum << ": need to specify \"log\" or \"lin\"" << std::endl;
					exit(EXIT_FAILURE);
				}


			}

			nlines++;
		}
	}
	return nlines;
}

TString prettyPrint(Double_t num){
	TString prettyString;
	sprintf (pretty, "%4.3f",num);
	prettyString = pretty;
	return prettyString;
}

array2d getCorrs(){
	array2d corresults;
	corresults.resize(Vars.size());
	for(UInt_t i=0; i< Vars.size(); i++){
		corresults[i].resize(Vars.size());
	}

	for(UInt_t k=0; k< Vars.size(); k++){
		corresults[k][k] = 1.0;
		for(UInt_t l =0; l < k; l++){
			inTuple->Draw(Vars[k]+":"+Vars[l]);
			TGraph *gr = new TGraph(inTuple->GetSelectedRows(),inTuple->GetV2(), inTuple->GetV1());
			//gr->Draw("ap");
			corresults[k][l] = gr->GetCorrelationFactor();
			corresults[l][k] = corresults[k][l];
			cout << Vars[k] << "	" << Vars[l] << "	"<< prettyPrint(corresults[k][l]) << endl;
			gr->Delete();
		}

	}

	return corresults;

}

void printCorrs(array2d corresults){
	cout << "\\begin{table}" << endl;
	TString tab = "\\begin{tabular}{l|";
	for(UInt_t i=0; i< Vars.size(); i++){
		tab.Append("c");
	}
	tab.Append("}");
	cout << tab << endl;
	for(UInt_t i=0; i< Vars.size(); i++){
		cout << "	&	" << i+1;
	}
	cout << "	\\\\" << endl;
	cout << "\\hline" << endl;

	for(UInt_t i=0; i< Vars.size(); i++){
		cout << i+1 << ":	" << Vars[i];
		for(UInt_t j=0; j< Vars.size(); j++){
			cout << "	&	" << prettyPrint(corresults[i][j]);
		}
		cout << "	\\\\" << endl;
	}
	cout << "\\end{tabular}" << endl;
	cout << "\\end{table}" << endl;

}



int main(int argc, char *argv[]){
	if(argc != 5){
		cout << "kstest:       Generates correlation matrices from stacker inputs" << endl;
		cout << "author:        Conor Fitzpatrick 2010" << endl;
		cout << "Syntax:        corrs <file.root> <tuplepath> <cut> <vars.txt>"<< endl;
		return EXIT_FAILURE;

	}

	TString fileName = argv[1];
	TString tuplePath = argv[2];
	TString cut = argv[3];
	std::string varlistName = argv[4];

	loadVars(varlistName);
	inFile = TFile::Open(fileName);
	inTuple = (TNtuple*)inFile->Get(tuplePath);
	inTuple->Draw(">>elist",cut,"entrylist");
	TEntryList *elist = (TEntryList*)gDirectory->Get("elist");
	elist->SetReapplyCut(kTRUE);
	inTuple->SetEntryList(elist);
	inTuple->SetEstimate(elist->GetEntriesToProcess());
	printCorrs(getCorrs());
}
