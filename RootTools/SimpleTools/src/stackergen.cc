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
#include <stdlib.h>
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
#include<TObjArray.h>

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

char cmpLower[10];
char cmpUpper[10];

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
array1tel elists;
array1s Units;
array1b Axis;
array1i lw;
array1b zerorms;
array1s sweightvar;

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
			try{
                                inDouble = lexical_cast <double> (os->GetString());
                                TString scaler = "";
                                scaler += inDouble;
                                sweightvar.push_back(scaler);

                        }catch(bad_lexical_cast &e){
                                try{
                                        inString = lexical_cast <string> (os->GetString());
                                        if(inString == "N"){
                                                Double_t norm = 1.0/(Double_t)elists.back()->GetN();
                                                TString scaler = "";
                                                scaler += norm;
                                                cout << "#Normalising " << LegendNames.back() << " to unit area. Normalisation factor:" << norm << endl;
                                                sweightvar.push_back(scaler);
                                        }else{
                                                sweightvar.push_back(inString);
                                                cout << "#sWeightVar loaded for" << LegendNames.back() << ": "<< inString << endl;
                                        }
                                }catch(bad_lexical_cast &e){
                                        std::cout << filename.c_str() << ": line " << linenum << ": not a valid weighting" << std::endl;
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


UInt_t getAllVars(){
	TObjArray *members = Trees[0]->GetListOfLeaves();
	VarLower.resize(members->GetEntries());
	VarUpper.resize(members->GetEntries());
	zerorms.resize(members->GetEntries());
	Vars.resize(members->GetEntries());
	for(int i = 0; i < members->GetEntries(); i++){
		Vars[i] = (members->At(i)->GetName());
		VarLower[i] = FLT_MAX;
		VarUpper[i] = -FLT_MAX;
		zerorms[i] = true;
	}
	return members->GetEntries();
}

void minmax(){
	for(UInt_t i=0; i< Trees.size(); i++){
		for(UInt_t j=0; j<Vars.size(); j++){
			Trees[i]->Draw(Vars[j]+">>tmp",sweightvar[i]);
			TH1F *tmp = (TH1F*)gDirectory->Get("tmp");
			Double_t tmpmax = tmp->GetXaxis()->GetXmax();
			Double_t tmpmin = tmp->GetXaxis()->GetXmin();
			if(tmpmax>VarUpper[j]){VarUpper[j]=tmpmax;}
			if(tmpmin<VarLower[j]){VarLower[j]=tmpmin;}
			if(tmp->GetRMS()!=0){zerorms[j]= false;}
			tmp->Delete();
		}
	}
}

int main(int argc, char *argv[]){
	if(argc != 3){
		cout << "stackergen:       Generates varlist for stacker" << endl;
		cout << "author:        Conor Fitzpatrick 2008" << endl;
		cout << "Syntax:        stackergen <files.txt> <bins>"<< endl;
		cout << "files.txt syntax: <TFile path> <path/to/ntuple> <preproc cut> <legend title> <histo color int> <FillStyle int> <weight (N for unit normalisation)> <linewidth int>" << endl;
		return EXIT_FAILURE;

	}

	std::string filelistName = argv[1];
	UInt_t bins = atoi(argv[2]);

	loadFiles(filelistName);
	getAllVars();
	TCanvas *c = new TCanvas("null","null",0,0);
	minmax();
	delete c;
	for(UInt_t i=0; i<Vars.size(); i++){
		if(zerorms[i]){
		cout << "#" << Vars[i] << "	"<< VarLower[i] << "	" << VarUpper[i] << "	" << bins << "	" << "\"\"" << "	" <<"lin" << "	" << "All datasets have zero RMS" << endl;
		}else{
			sprintf(cmpUpper,"%g",VarUpper[i]);
			sprintf(cmpLower,"%g",VarLower[i]);
			if((strcmp(cmpLower,cmpUpper)!=0)){
				cout << Vars[i] << "	"<< cmpLower << "	" << cmpUpper << "	" << bins << "	" << "\"\"" << "	" <<"lin" << endl;
			}else{
				cout << "#" << Vars[i] << "     "<< cmpLower << "    " << cmpUpper << "   " << bins << "  " << "\"\"" << "        " <<"lin" << "  " << "Datasets have no range" << endl;

			}
		}
	}
}
