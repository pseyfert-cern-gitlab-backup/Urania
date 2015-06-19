/* stacker: Part of the simpletools package
 * v 1.0b
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
TFile *outFile;
UInt_t loadFiles(std::string filename);
UInt_t loadVars(std::string filename);
array1b usingSweights;
array1s sweightvar;

int main(int argc, char *argv[]){
	if(argc !=9 && argc !=8){

		cout << "stacker: 	Quick and easy histogram tool" << endl;
		cout <<	"author: 	Conor Fitzpatrick 2008" << endl;	
		cout << "syntax: 	stacker <files.txt> <vars.txt> <rows> <cols> <width> <height> <outputdir> [stackargs]" << endl;	
		cout << "files.txt syntax: <TFile path> <path/to/ntuple> <preproc cut> <legend title> <histo color int> <FillStyle int> <weight (N for unit normalisation)> <linewidth int>" << endl;
		cout << "vars.txt syntax: <var name> <lower bound> <upper bound> <bins> <x-axis title/units> <y-axis log/lin>" << endl;
		return EXIT_FAILURE;

	}

	std::string filelistName = argv[1];
	std::string varlistName = argv[2];
	UInt_t PlotRows = atoi(argv[3]);
	UInt_t PlotCols = atoi(argv[4]);
	UInt_t CanvWidth = atoi(argv[5]);
	UInt_t CanvHeight = atoi(argv[6]);
	TString outputDir = argv[7];
	gSystem->mkdir( outputDir );
	outFile = new TFile(outputDir+"/plots.root","RECREATE");
	TString * stackargs;
	if(argc==9){       
		stackargs = new TString(argv[8]);
	}else{
		stackargs = new TString("");
	}

	UInt_t nFiles = loadFiles(filelistName);
	UInt_t nVars = loadVars(varlistName);
	UInt_t ppp = PlotRows * PlotCols;

	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetStatX(999.);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetMarkerStyle(20);
	gStyle->SetMarkerSize(1.2);
	gStyle->SetHistLineWidth(2);
	gStyle->SetLineStyleString(2,"[12 12]");
	UInt_t nVarsDone = 0;
	UInt_t page = 0;

	while(nVarsDone<nVars){
		cout << "page = " << page <<endl;
		outFile->cd();
		char *canvName = new char[256];
		sprintf(canvName,outputDir+"_plots_page_%i",page);
		TCanvas *c = new TCanvas(canvName,canvName, CanvWidth,CanvHeight);
		c->SetFillColor(0);
		c->Divide(PlotCols,PlotRows);
		c->Update();

		for(UInt_t v = 0; v<ppp; v++){
			if(nVarsDone<nVars){
				c->cd(v+1);
				gPad->SetFillColor(0);
				TPaveStats *stats[nFiles];
				THStack *hs = new THStack(Vars[nVarsDone],Vars[nVarsDone]);
				TLegend *legend = new TLegend(0.15,0.80,0.25,0.65);
				cout << "pad = " << v << "	Variable = " <<  Vars[nVarsDone] << endl;	
				for(UInt_t f=0; f<nFiles; f++){	
					TString name = Vars[nVarsDone]+"_"+LegendNames[f];
					TH1F *Histo = new TH1F("temp",name,VarBins[nVarsDone],VarLower[nVarsDone],VarUpper[nVarsDone]);

					//Trees[f]->Draw(Vars[nVarsDone]+">>"+"temp","("+Vars[nVarsDone]+")*("+sweightvar[f]+")");
					Trees[f]->Draw(Vars[nVarsDone]+">>"+"temp",sweightvar[f]);
					Histo->SetTitle(LegendNames[f]);
					Histo->SetName(name);
					Histo->SetStats(true);
					c->Update();
					Histo->SetLineColor(Colors[f]);
					Histo->SetFillColor(Colors[f]);
					Histo->SetFillStyle(FillStyles[f]);
					Histo->SetLineWidth(lw[f]);
					stats[f]=new TPaveStats();
					stats[f] = (TPaveStats*)Histo->GetListOfFunctions()->FindObject("stats");
					stats[f]->SetTextColor(Colors[f]);
					hs->Add(Histo);
					legend->AddEntry(Histo,LegendNames[f],"f");
				}
				if(Axis[nVarsDone]){
					gPad->SetLogy();
				}

				hs->Draw(*stackargs);
				c->Update();
				hs->GetXaxis()->SetTitle(Units[nVarsDone]);
				hs->GetYaxis()->SetTitle("Candidates");
				hs->Draw(*stackargs);

				Double_t x1 = 0.825;
				Double_t x2 = 0.975;
				Double_t y1 = 0.825;
				Double_t y2 = 0.975;
				for(UInt_t g=0; g<nFiles; g++){
					stats[g]->SetX1NDC(x1); stats[g]->SetX2NDC(x2);
					stats[g]->SetY1NDC(y1);  stats[g]->SetY2NDC(y2);
					y1 = y1 - 0.165;
					y2 = y2 - 0.165;
					stats[g]->Draw();
				}

				nVarsDone++;

			/*	if(v==0){
					legend->SetShadowColor(0);
					legend->SetLineColor(0);
					legend->SetTextSize(0.05);
					legend->SetFillColor(0);
					legend->Draw();
				}
			*/
			}
			c->Update();
		}
		page++;
		c->Write();

		//gStyle->SetPaperSize(52,40);
		c->Print(outputDir+"/"+canvName+".png");
		c->Print(outputDir+"/"+canvName+".eps");
		c->Print(outputDir+"/"+canvName+".pdf");
		c->Print(outputDir+"/"+canvName+".svg");
		delete c;

	}
	outFile->Write();
	outFile->Close();
}

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
	//char* delimiters = " 	";

	fileStream.open(filename.c_str());
	if (!fileStream){
		std::cout << "Error in opening file list" << std::endl;
		return EXIT_FAILURE;
	}
	while(!line.ReadLine(fileStream).eof()){

		//TObjArray* Strings = line.Tokenize(delimiters);
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
				cout << "Normalising " << LegendNames.back() << " to unit area. Normalisation factor:" << norm << endl;
				sweightvar.push_back(scaler);
			}else{
				sweightvar.push_back(inString);
				cout << "sWeightVar loaded for" << LegendNames.back() << ": "<< inString << endl;
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
	//char* delimiters = " 	";

	fileStream.open(filename.c_str());
	if (!fileStream){
		std::cout << "Error in opening var list" << std::endl;
		return EXIT_FAILURE;
	}
	while(!line.ReadLine(fileStream).eof()){

		//TObjArray* Strings = line.Tokenize(delimiters);
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
