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
TFile *outFile;

UInt_t loadFiles(std::string filename);
UInt_t loadVars(std::string filename);

UInt_t loadFiles(std::string filename){
	ifstream fileStream;
	std::string lineread;
	TString line;
	UInt_t nlines =0;
	TString word;
	TString inString;
	Double_t inDouble;
	Int_t inInt;
	UInt_t linenum =0;

	fileStream.open(filename.c_str());
	if (!fileStream){
		std::cout << "Error in opening file list" << std::endl;
		return EXIT_FAILURE;
	}
	while(!line.ReadLine(fileStream).eof()){
		TObjArray* Strings = line.Tokenize(" \t");
		TIter iString(Strings);
		TObjString* os=0;
		os=(TObjString*)iString();
		linenum++;
		if(!os->GetString().BeginsWith('#')){
			if(Strings->GetEntries() != 8){
				std::cout << filename.c_str() << ": line " << linenum << ": isn't a valid input line." << std::endl;

				std::cout << "expected 8 parameters, found " << Strings->GetEntries() << ". Ensure you haven't got extra spaces/tabs and try again." << std::endl;
				exit(EXIT_FAILURE);
			}

			try{
				inString = lexical_cast <string> (os->GetString());
				Files.push_back(TFile::Open(inString));
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid filename" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();
			try{
				inString = lexical_cast <string> (os->GetString());
				TuplePaths.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid ntuple name" << std::endl;
				exit(EXIT_FAILURE);
			}
			Trees.push_back((TTree*)Files.back()->Get(TuplePaths.back()));

			os=(TObjString*)iString();
			try{
				inString = lexical_cast <string> (os->GetString());
				preprocCuts.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid cut string" << std::endl;
				exit(EXIT_FAILURE);
			}

			os=(TObjString*)iString();

			try{
				inString = lexical_cast <string> (os->GetString());
				LegendNames.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid legend name" << std::endl;
				exit(EXIT_FAILURE);
			}
			Trees.back()->Draw(">>elist_"+LegendNames.back(), preprocCuts.back(),"entrylist");
			elists.push_back((TEntryList*)gDirectory->Get("elist_"+LegendNames.back()));
			elists.back()->SetReapplyCut(kTRUE);
			Trees.back()->SetEntryList(elists.back());

			os=(TObjString*)iString();

			try{
				inInt = lexical_cast <int> (os->GetString());
				Colors.push_back(inInt);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid color int" << std::endl;
				exit(EXIT_FAILURE);
			}

			os=(TObjString*)iString();

			try{
				inInt = lexical_cast <int> (os->GetString());
				FillStyles.push_back(inInt);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid fillstyle int" << std::endl;
				exit(EXIT_FAILURE);
			}


			os=(TObjString*)iString();
			if(os->GetString()=="N"){
				Double_t norm = 1.0/(Double_t)elists.back()->GetN();
				cout << "Normalising " << LegendNames.back() << " to unit area. Normalisation factor:" << norm << endl;
				Weights.push_back(norm);

			}else{
				try{
					inDouble = lexical_cast <double> (os->GetString());
					Weights.push_back(inDouble);
				}catch(bad_lexical_cast &e){
					std::cout << filename.c_str() << ": line " << linenum << ": not a valid weighting double" << std::endl;
					exit(EXIT_FAILURE);
				}

			}

			os=(TObjString*)iString();
			try{
				inInt = lexical_cast <int> (os->GetString());
				lw.push_back(inInt);
			}catch(bad_lexical_cast &e){
				std::cout << filename.c_str() << ": line " << linenum << ": not a valid linewidth int" << std::endl;
				exit(EXIT_FAILURE);
			}


			nlines++;

		}
	}

	return nlines;
}


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

Double_t getSeparation( TH1* S, TH1* B ) //FROM TMVA
{
	Double_t separation = 0;
	Int_t    nstep  = S->GetNbinsX();
	Double_t intBin = (S->GetXaxis()->GetXmax() - S->GetXaxis()->GetXmin())/nstep;
	Double_t nS     = S->GetSumOfWeights()*intBin;
	Double_t nB     = B->GetSumOfWeights()*intBin;
	if (nS > 0 && nB > 0) {
		for (Int_t bin=0; bin<nstep; bin++) {
			Double_t s = S->GetBinContent( bin )/Double_t(nS);
			Double_t b = B->GetBinContent( bin )/Double_t(nB);
			if (s + b > 0) separation += 0.5*(s - b)*(s - b)/(s + b);
		}
		separation *= intBin;
	}
	else {
		cout << "<GetSeparation> histograms with zero entries: " << nS << " : " << nB << " cannot compute separation" << endl;
		separation = 0;
	}

	return separation;
}

array2d kstest(UInt_t Varnum){

	array1th1f histos;
	array2d ksresults;
	histos.resize(Trees.size());
	ksresults.resize(Trees.size());
	for(UInt_t i=0; i< Trees.size(); i++){
		ksresults[i].resize(Trees.size());
		histos[i] = new TH1F(LegendNames[i],LegendNames[i],VarBins[Varnum],VarLower[Varnum],VarUpper[Varnum]);
		Trees[i]->Draw(Vars[Varnum]+">>"+LegendNames[i]);
		histos[i]->Sumw2();
		histos[i]->Scale(Weights[i]);
	}

	for(UInt_t k=0; k< Trees.size(); k++){
		ksresults[k][k] = 1.0;
		for(UInt_t l =0; l < k; l++){

			ksresults[k][l] = histos[k]->Chi2Test(histos[l],"WW");
			//ksresults[k][l] = histos[k]->KolmogorovTest(histos[l],"UO");
			//ksresults[k][l] = getSeparation(histos[k],histos[l]);
			ksresults[l][k] = ksresults[k][l];
		}

	}

	for(UInt_t k=0; k< Trees.size(); k++){
		histos[k]->Delete();
	}
	return ksresults;

}

void printkstest(array2d ksresults, TString varname){
	cout << "\\begin{table}" << endl;
	TString tab = "\\begin{tabular}{l|";
	for(UInt_t i=0; i< Trees.size(); i++){
		tab.Append("c");
	}
	tab.Append("}");
	cout << tab << endl;
	cout << varname;
	for(UInt_t i=0; i< Trees.size(); i++){
		cout << "	&	" << LegendNames[i];
	}
	cout << "	\\\\" << endl;
	cout << "\\hline" << endl;

	for(UInt_t i=0; i< Trees.size(); i++){
		cout << LegendNames[i];
		for(UInt_t j=0; j< Trees.size(); j++){
			cout << "	&	" << prettyPrint(ksresults[i][j]);
		}
		cout << "	\\\\" << endl;
	}
	cout << "\\end{tabular}" << endl;
	cout << "\\end{table}" << endl;

}



int main(int argc, char *argv[]){
	if(argc != 3){
		cout << "kstest:       Generates KStest matrices from stacker inputs" << endl;
		cout << "author:        Conor Fitzpatrick 2010" << endl;
		cout << "Syntax:        stackergen <files.txt> <vars.txt>"<< endl;
		return EXIT_FAILURE;

	}

	std::string filelistName = argv[1];
	std::string varlistName = argv[2];

	loadFiles(filelistName);
	loadVars(varlistName);

	for(UInt_t i =0; i< Vars.size(); i++){
		cout << "" << endl;
		printkstest(kstest(i), Vars[i]);
	}

}
