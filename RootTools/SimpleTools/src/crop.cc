/* crop: Part of the simpletools package
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
#include <TCint.h>
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
#include <boost/lexical_cast.hpp>
#include <TH1.h>
//GUI
#include <TApplication.h>
#include <TCanvas.h>
#include <TGClient.h>
#include <TGFrame.h>
#include<TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>


//http://www.akiti.ca/mulmatvec2.html
typedef vector<Double_t> array1d;
typedef vector<vector<Double_t> > array2d;
typedef vector<vector<vector<Double_t> > > array3d;
typedef vector<TString> array1s;
typedef vector<TFile*> array1tf;
typedef vector<TTree*> array1tt;
typedef vector<Bool_t> array1b;
typedef vector<UInt_t> array1ui;
typedef vector<Int_t> array1i;

using std::cout;
using std::endl;
using namespace boost;
const Double_t zero = 1.0e-30;
const char delimiters[] = " \t\n;";
const TString Bstr = "B",Sstr = "S",Cstr = "#", And = "&&";
char pretty[10];
TString tmpstring;
UInt_t seed = 0;
array1tf sinFile, binFile; //input/output files
TFile *outFile;
TFile *tmpFile;
array1s sinname, binname;   	    //input filenames
array1d sweight, bweight;	    //input file weights
array1s stname, btname;   	    //input ntuple names
array1s sincutname, bincutname;   //preprocessing cuts
array1tt bintuple, sintuple;         //input ntuples
array1tt bintuplecut, sintuplecut;   //preprocessed ntuples
array1b scutme, bcutme;              //apply cuts to input files?

array1s cname;		       //The cuts to optimise
array1d lower;	       //lower limit of cut
array1d upper;	       //upper limit
array1d res;		       //resolution of cut
array1d mineff;		       //min eff of cut
array1ui steps;		       //no. steps per cut
array1ui cutorder;	       //no. steps per cut
UInt_t msteps = 0;	       //max. size of steps array

array1d spreinit, dspreinit; //total signal per file
array1d bpreinit, dbpreinit; //  "   backgd  "   "
array1d sinit, dsinit; //total signal evts. per file (after preprocessing)
array1d binit, dbinit; //  "   backgnd "     "    "    "         "
Double_t sabsinit=0, dsabsinit=0;   //  "   signal  "    all   "    "         " 
Double_t babsinit=0, dbabsinit=0;   //  "   backgd  "     "    "    "         "

array1d maxVal;
array1d tmpmaxVal;
array1i maxk, lastmaxk, tmpmaxk, tmplastmaxk;
array2d cutVal, dcutVal;
array1d SoRSBSteps, dSoRSBSteps;
array1d Steps;
array1s StepNames;
array1s sweightvar,bweightvar;
Int_t nsteps;
UInt_t snum=0, bnum=0, ncuts=0;	       //no. signal/background files, number of cuts 
array3d s, ds;                        //no. signal passing cut per file
array3d b, db;                      	// "  backgnd   "     "   "   "
array2d stot, dstot;                	// "  signal    "     "  for all files
array2d btot, dbtot;            	    // "  backgnd   "     "   "   "    "
array2d sw, dsw;	              // "  weighted signal passing all files
array2d bw, dbw;        	      // "     "    backgnd    "     "   " 
array3d seff, brej;                 //accept/reject rates per file
array2d sefftot, brejtot;           //  "      "      "   all  "
array3d dseff, dbrej;   	       //accept/reject rates per file
array2d dsefftot, dbrejtot;         //  "      "      "   all  "
array2d SoRSB, dSoRSB;              //S/sqrt(S+B)
array2d BoS, dBoS;                  //B/S

TH1F *tmptuple; 

array1b usingSweightsS, usingSweightsB;
void initStats();
void autisticStats();
void finalStats();
bool readWeightFile(std::string weightListName);
bool readCutFile(std::string cutListName);
void prepTuples();
void plotData(UInt_t cut, TDirectory *dir);
void writePlot(UInt_t cut, TDirectory *dir);
void guiPlot(UInt_t cut);
void PlotSoRSB(UInt_t cut);
void PlotSoRSBSteps();
void PlotRoC(UInt_t cut);
void PlotSeff(UInt_t cut);
void PlotBrej(UInt_t cut);
void help(char *args[]);
void orderHardestB();
void orderHardestS();
void orderHardestSB();
void orderRandom(TRandom3 *rng);
void onelineHeader();
void onelineStats(UInt_t cut);
TString createCut(UInt_t exclude);
Int_t scanCut(UInt_t cut, TString otherCuts);
void info(char *args[]);
void banner();
TString prettyPrint(Double_t num);
Double_t getEntriesSignal(TString cutString, UInt_t tuplenum);
Double_t getEntriesBackground(TString cutString, UInt_t tuplenum);
TGMainFrame *guiMain;
TRootEmbeddedCanvas *guiCanvas;
TCanvas * guiACanvas;

int main(int argc, char *argv[]) {



	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);

	Bool_t gui=true;
	banner();
	if(argc != 6){	
		if(argc != 7){
			help(argv);     exit(EXIT_FAILURE);
		}else{

			TString b = "-b";
			if(argv[6] == b){ 
				gui = false;
			}else{
				help(argv);     exit(EXIT_FAILURE);
			}

		}
	}
	info(argv);
	TRandom3 rndGen(seed);
	std::string weightListName = argv[1];
	std::string cutListName = argv[2];
	UInt_t maxIters = atoi(argv[3]);
	TString mode = argv[4];
	TString outname = argv[5];
	UInt_t modenum = 2;

	if(mode == "B"){modenum = 1;}
	if(mode == "SB"){modenum = 2;}
	if(mode == "R"){modenum = 3;}
	if(mode == "S"){modenum = 4;}

	TApplication theApp("App", &argc, argv);
	theApp.GetOptions(&argc, argv);
	if(gui){
		guiMain = new TGMainFrame(gClient->GetRoot(),1024,768);
		guiCanvas = new TRootEmbeddedCanvas("guicanvas",guiMain,1024,768);
		guiMain->AddFrame(guiCanvas,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,10,10,10,1));
		guiMain->SetWindowName("CROP");
		guiMain->MapSubwindows();
		guiMain->Resize(guiMain->GetDefaultSize());
		guiMain->MapWindow();
		guiACanvas = guiCanvas->GetCanvas();
		guiACanvas->SetDoubleBuffer(1);
	}else{
		guiACanvas = new TCanvas("CROP","CROP", 1024,768);
	}
	guiACanvas->cd();
	guiACanvas->Divide(2,2);


	cout << "Parsing weightfile..." << endl;
	if(!readWeightFile(weightListName)){
		exit(EXIT_FAILURE);
	}	
	cout << "Parsing cutfile..." << endl;
	readCutFile(cutListName);

	TStopwatch timer;
	timer.Start();
	outFile = new TFile(outname,"RECREATE");
	char *uniquename(tempnam(NULL, NULL));
	tmpstring = uniquename;
	free(uniquename);
	uniquename = NULL;
	//tmpstring = tmpnam(NULL);
	tmpFile = new TFile(tmpstring,"RECREATE");
	cout << "Applying input cuts..." << endl;
	prepTuples();
	initStats();



	cout << "Finding Starting values..." << endl;
	TDirectory *initDir = outFile->mkdir("Initial","Initial");

	for(UInt_t l = 0; l<ncuts; l++){
		lastmaxk[l] = scanCut(l,"");	
		writePlot(l,initDir);
	}
	orderHardestS();
	autisticStats();

	switch (modenum){		
		case 1:	orderHardestB();
		case 2:	orderHardestSB();
		case 3:	orderRandom(&rndGen);
		default: orderHardestS();
	}

	UInt_t thismaxk=0;
	Double_t delta = -9999;
	UInt_t m=0;
	//Bool_t mc = false;
	Bool_t converged = false;
	cout << "Starting Optimisation..." <<endl;
	cout << "" <<	endl;
	onelineHeader();

	nsteps = 0;
	TString StepName;

	while(!converged){
		for(UInt_t n =0; n<ncuts; n++){
			TString inclusivecut =  createCut(cutorder[n]);
			thismaxk = scanCut(cutorder[n],inclusivecut);
			delta += abs(Int_t(thismaxk) - Int_t(lastmaxk[cutorder[n]]));
			onelineStats(cutorder[n]);
			lastmaxk[cutorder[n]] = thismaxk;
			nsteps++;	
			Steps.push_back(nsteps);

			StepName = cname[cutorder[n]];
			char dtoc[20];
			sprintf(dtoc,"%g",cutVal[cutorder[n]][maxk[cutorder[n]]]);
			StepName.Append(dtoc);
			//StepName += cutVal[n][maxk[n]];
			StepNames.push_back(StepName);
			SoRSBSteps.push_back(SoRSB[cutorder[n]][maxk[cutorder[n]]]);
			dSoRSBSteps.push_back(dSoRSB[cutorder[n]][maxk[cutorder[n]]]);
		}
		if(delta==0){converged=true;}else{delta=0;}

		switch (modenum){		
			case 1:	orderHardestB();
			case 2:	orderHardestSB();
			case 3:	orderRandom(&rndGen);
			default: orderHardestS();
		}
		m++;
		if(m == maxIters){
			cout << "WARNING: Failed to converge after" << m << "steps" << endl;
			cout << "Check output plots, and adjust ranges accordingly" << endl;
			break;
		}
	}
	if(m!=maxIters){cout<< "Converged in "<< m << " steps. Optimal cut:" << endl;
		cout << ""<<endl;
		cout<<	createCut(ncuts+1) << endl;
		cout << "" << endl;
		orderHardestS();
		autisticStats();
		finalStats();
	}
	outFile->cd();

	PlotSoRSBSteps();


	TDirectory *finalDir = outFile->mkdir("Optimised","Optimised");
	for(UInt_t l = 0; l<ncuts; l++){
		writePlot(cutorder[l],finalDir);
	}
	for(UInt_t i = 0; i<snum; i++){
		sinFile[i]->Close();
	}	
	for(UInt_t j = 0; j<bnum; j++){
		binFile[j]->Close();
	}
	sintuplecut.clear();
	bintuplecut.clear();
	sinFile.clear();	
	binFile.clear();	
	outFile->Write();
	outFile->Close();
	tmpFile->Close();
	remove(tmpstring);
	timer.Stop();
	timer.Print();
	//theApp.Run();
	exit(0);
}

void initStats(){
	Double_t sweightotal=0.0;
	Double_t bweightotal=0.0;
	cout << "ntuple		"<<"Evts.	"<<"Passing preprocessing cuts	"<<"weight	"<< endl;
	cout << "-------------------------------------------------------------------"<< endl;
	for(UInt_t i =0; i<snum; i++){
		if(!usingSweightsS[i]){
		cout << "signal "<<i<<"	"<<spreinit[i]<<"		"<<sinit[i]<<"			"<<sweight[i]<<endl;
		}else{
		cout << "signal "<<i<<"	"<<spreinit[i]<<"		"<<sinit[i]<<"			"<<"Per event: " << sweightvar[i] <<endl;
		}
		sweightotal +=(sinit[i]*sweight[i]); 
	}
	for(UInt_t j=0; j<bnum; j++){	
		if(!usingSweightsB[j]){

		cout << "background "<<j<<"	"<<bpreinit[j]<<"		"<<binit[j]<<"			"<<bweight[j]<<endl;
	}else{
		cout << "background "<<j<<"	"<<bpreinit[j]<<"		"<<binit[j]<<"			"<<"Per event: "<< bweightvar[j] <<endl;

		}
		bweightotal +=(binit[j]*bweight[j]); 
	}
	sweightotal = sweightotal/sabsinit;
	bweightotal = bweightotal/babsinit;
	cout <<""<<endl;
	cout << "signal (total)			"<<sabsinit<<"			"<<sweightotal<<endl;
	cout << "background (total)		"<<babsinit<<"			"<<bweightotal<<endl;

	cout <<""<<endl;
	cout <<""<<endl;
}



void finalStats(){

	Double_t initial =0;
	Double_t final =0;
	Double_t finaleff=0.0;
	Double_t dfinaleff=0.0;

	cout << "ntuple		"<<"Total		" <<"Selected	" <<"Eff			" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------  " << endl;

	for(UInt_t j=0; j<snum; j++){
		initial = sinit[j];
		final = getEntriesSignal(createCut(ncuts),j);
		finaleff = final / initial;
		dfinaleff = sqrt(finaleff*(1.0-finaleff)/initial);
		cout <<"signal "<<j<< "	"<< initial << "		"<<final << "		"<< finaleff << " +/- " << dfinaleff << endl;

	}
	for(UInt_t k=0; k<bnum; k++){
		initial = binit[k];
		final = getEntriesBackground(createCut(ncuts),k);
		finaleff = final / initial;
		dfinaleff = sqrt(finaleff*(1.0-finaleff)/initial);
		cout <<"background "<<k<< "	"<< initial << "		"<<final << "		"<< finaleff << " +/- " << dfinaleff << endl;
	}
}


void autisticStats(){

	cout << "Cut	"<< "ntuple		"<<"Sig. Eff.		" <<"Bkg. Rej.		" <<"B/S			" <<"max. S/sqrt(S+B)	"<< endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------  " << endl;
	for(UInt_t i =0; i<ncuts; i++){
		cout << i << " " <<cname[cutorder[i]]<<cutVal[cutorder[i]][maxk[cutorder[i]]] << endl;	
		for(UInt_t j=0; j<snum; j++){
			cout << "	" <<"signal "<<j<< "	"<<prettyPrint(seff[cutorder[i]][j][maxk[cutorder[i]]])<<" +/- "<<prettyPrint(dseff[cutorder[i]][j][maxk[cutorder[i]]])<<endl;
		}
		for(UInt_t k=0; k<bnum; k++){
			cout << "	" <<"background "<<k<<"				"<<prettyPrint(brej[cutorder[i]][k][maxk[cutorder[i]]])<<" +/- "<<prettyPrint(dbrej[cutorder[i]][k][maxk[cutorder[i]]])<<endl;
		}
		cout << "	" <<"TOTAL" <<"		"<<prettyPrint(sefftot[cutorder[i]][maxk[cutorder[i]]])<<" +/- "<<prettyPrint(dsefftot[cutorder[i]][maxk[cutorder[i]]])<<"		"<<prettyPrint(brejtot[cutorder[i]][maxk[cutorder[i]]])<<" +/- "<<prettyPrint(dbrejtot[cutorder[i]][maxk[cutorder[i]]])<<"		"<<prettyPrint(BoS[cutorder[i]][maxk[cutorder[i]]])<<" +/- "<<prettyPrint(dBoS[cutorder[i]][maxk[cutorder[i]]])<<"		"<<prettyPrint(SoRSB[cutorder[i]][maxk[cutorder[i]]])<<" +/- "<<prettyPrint(dSoRSB[cutorder[i]][maxk[cutorder[i]]])<<endl;
		cout <<""<<endl;
		cout <<""<<endl;
	}

}


void onelineHeader(){
	cout << "Cut no." <<"	" <<"Cut delta" << "	" <<"S/sqrt(S+B)" << "		" << "incl. Signal Eff." <<"	" << "incl. Bkg. Rej" << "		" << "cut" <<  endl;
	cout <<"------------------------------------------------------------------------------------------------------------------------------- "<<endl;
}
void onelineStats(UInt_t cut){
	cout << cut <<"	" << Int_t(maxk[cut]) - Int_t(lastmaxk[cut]) <<"		"<<  prettyPrint(SoRSB[cut][maxk[cut]]) << " +/- " << prettyPrint(dSoRSB[cut][maxk[cut]]) << "		" << prettyPrint(sefftot[cut][maxk[cut]]) << " +/- " << prettyPrint(dsefftot[cut][maxk[cut]]) <<"		" << prettyPrint(brejtot[cut][maxk[cut]]) <<" +/- "<< prettyPrint(dbrejtot[cut][maxk[cut]]) << "		" << cname[cut] << cutVal[cut][maxk[cut]] <<  endl;
}


bool readWeightFile(std::string weightListName){

	ifstream fileStream2;
	TString line;
	Double_t inDouble;
	TString inString;
	UInt_t linenum =0;
	TString word;

	fileStream2.open(weightListName.c_str());
	if (!fileStream2){
		std::cout << "Error in opening weightfile" << std::endl;
		exit(EXIT_FAILURE);
	}

	bnum = 0;
	snum = 0; 
	linenum = 0;
	while(!line.ReadLine(fileStream2).eof()){
		linenum++;
		TObjArray* Strings = line.Tokenize(delimiters);
		TIter iString(Strings);
		TObjString* os=0;
		os=(TObjString*)iString(); //signal or background
		word = os->GetString();
		if(word == Bstr){
			if(Strings->GetEntries() != 5 && Strings->GetEntries() != 4){
				std::cout << weightListName.c_str() << ": line " << linenum << ": is not a valid weight line" << std::endl;

				std::cout << "expected 4 or 5 parameters, found " << Strings->GetEntries() << ". Ensure you haven't got extra spaces/tabs and try again." << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString(); //Filename
			try{
				inString = lexical_cast <string> (os->GetString());
				binname.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid filename" << std::endl;
				exit(EXIT_FAILURE);
			}

			os=(TObjString*)iString(); //Ntuplename
			try{
				inString = lexical_cast <string> (os->GetString());
				btname.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid ntuplename" << std::endl;
				exit(EXIT_FAILURE);
			}



			os=(TObjString*)iString(); //Weight
			try{
				inDouble = lexical_cast <double> (os->GetString());
				bweight.push_back(inDouble);
				bweightvar.push_back("");
				usingSweightsB.push_back(false);
			}catch(bad_lexical_cast &e){
				try{
					inString = lexical_cast <string> (os->GetString());
					bweight.push_back(1.0);

					bweightvar.push_back(inString);
					usingSweightsB.push_back(true);
				}catch(bad_lexical_cast &e){
					std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid weight (sWeight)" << std::endl;
					exit(EXIT_FAILURE);
				}

			}

			bincutname.resize(bnum+1);
			bcutme.resize(bnum+1);


			if((os=(TObjString*)iString())){
				try{
					inString = lexical_cast <string> (os->GetString());
					bincutname[bnum] = inString;
				}catch(bad_lexical_cast &e){
					std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid cutstring" << std::endl;
					exit(EXIT_FAILURE);
				}

				bcutme[bnum] = true;
			}else{
				bcutme[bnum] = false;
			}
			bnum++;
		}else{
			if(word == Sstr){
				if(Strings->GetEntries() != 5 && Strings->GetEntries() != 4){
					std::cout << weightListName.c_str() << ": line " << linenum << ": is not a valid weight line" << std::endl;
					std::cout << "expected 4 or 5 parameters, found " << Strings->GetEntries() << ". Ensure you haven't got extra spaces/tabs and try again." << std::endl;
					exit(EXIT_FAILURE);

				}
				os=(TObjString*)iString(); //Filename
				try{
					inString = lexical_cast <string> (os->GetString());
					sinname.push_back(inString);
				}catch(bad_lexical_cast &e){
					std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid filename" << std::endl;
					exit(EXIT_FAILURE);
				}

				os=(TObjString*)iString(); //Ntuplename
				try{
					inString = lexical_cast <string> (os->GetString());
					stname.push_back(inString);
				}catch(bad_lexical_cast &e){
					std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid ntuplename" << std::endl;
					exit(EXIT_FAILURE);
				}


				os=(TObjString*)iString(); //Weight
				try{
					inDouble = lexical_cast <double> (os->GetString());
					sweight.push_back(inDouble);
					usingSweightsS.push_back(false);
					sweightvar.push_back("");
				}catch(bad_lexical_cast &e){
					try{
						inString = lexical_cast <string> (os->GetString());
						sweight.push_back(1.0);
						sweightvar.push_back(inString);

						usingSweightsS.push_back(true);
					}catch(bad_lexical_cast &e){
						std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid weight (sWeight)" << std::endl;
						exit(EXIT_FAILURE);
					}

				}



				sincutname.resize(snum+1);
				scutme.resize(snum+1);

				if((os=(TObjString*)iString())){
					try{
						inString = lexical_cast <string> (os->GetString());
						sincutname[bnum] = inString;
					}catch(bad_lexical_cast &e){
						std::cout << weightListName.c_str() << ": line " << linenum << ": not a valid cutstring" << std::endl;
						exit(EXIT_FAILURE);
					}


					scutme[snum] = true;
				}else{
					scutme[snum] = false;
				}
				snum++;
			}else{
				if(word.BeginsWith(Cstr)){
				}else{
					std::cout << weightListName.c_str() << ": line " << linenum << ": is not a valid weight line" << std::endl;
					exit(EXIT_FAILURE);
				}
			}
		}

	}

	fileStream2.close();
	try{
		bintuple.resize(bnum);
		sintuple.resize(snum);
		bintuplecut.resize(bnum);
		sintuplecut.resize(snum);
		sinFile.resize(snum);
		binFile.resize(bnum);
		spreinit.resize(snum);
		dspreinit.resize(snum);
		bpreinit.resize(bnum);
		dbpreinit.resize(bnum);
		sinit.resize(snum);
		dsinit.resize(snum);
		binit.resize(bnum);
		dbinit.resize(bnum);
	}

	catch (bad_alloc& xa) { // Catch block, for exceptions
		cerr << "An exception occurred: " << xa.what() << "\n";
		return 0;
	} // End of catch block

	return true;
}

bool readCutFile(std::string cutListName){
	UInt_t linenum = 0;
	ifstream fileStream4;
	TString word;
	TString line;
	Double_t inDouble;
	TString inString;
	fileStream4.open(cutListName.c_str());
	ncuts = 0;
	if (!fileStream4){
		std::cout << "Error in opening cut file" << std::endl;
		exit(EXIT_FAILURE);
	}
	while(!line.ReadLine(fileStream4).eof()){
		linenum++;
		TObjArray* Strings = line.Tokenize(delimiters);

		TIter iString(Strings);
		TObjString* os=0;
		os=(TObjString*)iString();
		word = os->GetString();
		if(word.BeginsWith(Cstr)){}else{
			if(Strings->GetEntries() != 5){
				std::cout << cutListName.c_str() << ": line " << linenum << ": is not a valid cut line" << std::endl; 
				std::cout << "expected 5 parameters, found " << Strings->GetEntries() << ". Ensure you haven't got extra spaces/tabs and try again." << std::endl;
				exit(EXIT_FAILURE);
			}
			try{
				inString = lexical_cast <string> (word);
				cname.push_back(inString);
			}catch(bad_lexical_cast &e){
				std::cout << cutListName.c_str() << ": line " << linenum << ": not a valid cut" << std::endl;
				exit(EXIT_FAILURE);			
			}

			os=(TObjString*)iString();
			try{
				inDouble = lexical_cast <double> (os->GetString());	
				lower.push_back(inDouble);
			}catch(bad_lexical_cast &e){
				std::cout << cutListName.c_str() << ": line " << linenum << ": not a valid lower bound" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();
			try{
				inDouble = lexical_cast <double> (os->GetString());  
				upper.push_back(inDouble);
			}catch(bad_lexical_cast &e){
				std::cout << cutListName.c_str() << ": line " << linenum << ": not a valid upper bound" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();
			try{
				inDouble = lexical_cast <double> (os->GetString());
				res.push_back(inDouble);
			}catch(bad_lexical_cast &e){
				std::cout << cutListName.c_str() << ": line " << linenum << ": not a valid step resolution" << std::endl;
				exit(EXIT_FAILURE);
			}
			os=(TObjString*)iString();
			try{
				inDouble = lexical_cast <double> (os->GetString());
				mineff.push_back(inDouble);
			}catch(bad_lexical_cast &e){
				std::cout << cutListName.c_str() << ": line " << linenum << ": not a valid mineff" << std::endl;
				exit(EXIT_FAILURE);
			} 
			steps.push_back(UInt_t((upper[ncuts] - lower[ncuts])/res[ncuts]));
			if(steps[ncuts]>msteps){msteps=steps[ncuts];}
			ncuts++;

		}
	}
	fileStream4.close();
	try{
		stot.resize(ncuts); 
		dstot.resize(ncuts);
		btot.resize(ncuts); 
		dbtot.resize(ncuts);
		sw.resize(ncuts);
		dsw.resize(ncuts); 
		bw.resize(ncuts);
		dbw.resize(ncuts); 
		sefftot.resize(ncuts); 
		brejtot.resize(ncuts);
		dsefftot.resize(ncuts);
		dbrejtot.resize(ncuts);
		SoRSB.resize(ncuts);
		dSoRSB.resize(ncuts);
		BoS.resize(ncuts);
		dBoS.resize(ncuts);
		s.resize(ncuts);
		ds.resize(ncuts);
		b.resize(ncuts); 
		db.resize(ncuts);
		seff.resize(ncuts);
		brej.resize(ncuts);
		dseff.resize(ncuts);
		dbrej.resize(ncuts);
		cutVal.resize(ncuts);
		dcutVal.resize(ncuts);
		tmpmaxVal.resize(ncuts);
		tmpmaxk.resize(ncuts);
		maxVal.resize(ncuts);
		maxk.resize(ncuts);

		lastmaxk.resize(ncuts);
		tmplastmaxk.resize(ncuts);
		cutorder.resize(ncuts);
	}

	catch (bad_alloc& xa) { // Catch block, for exceptions
		cerr << "An exception occurred: " << xa.what() << "\n";
		exit(EXIT_FAILURE);
	} // End of catch block
	for(UInt_t p=0; p < ncuts; p++){
		try{
			stot[p].resize(steps[p]);        
			dstot[p].resize(steps[p]);
			btot[p].resize(steps[p]);        
			dbtot[p].resize(steps[p]);
			sw[p].resize(steps[p]);
			dsw[p].resize(steps[p]);        
			bw[p].resize(steps[p]);
			dbw[p].resize(steps[p]);        
			sefftot[p].resize(steps[p]);        
			brejtot[p].resize(steps[p]);
			dsefftot[p].resize(steps[p]);
			dbrejtot[p].resize(steps[p]);
			SoRSB[p].resize(steps[p]);
			dSoRSB[p].resize(steps[p]);
			BoS[p].resize(steps[p]);
			dBoS[p].resize(steps[p]);
			cutVal[p].resize(steps[p]);
			dcutVal[p].resize(steps[p]);
			s[p].resize(snum);
			ds[p].resize(snum);
			dseff[p].resize(snum);
			seff[p].resize(snum);
			b[p].resize(bnum); 
			db[p].resize(bnum);
			brej[p].resize(bnum);
			dbrej[p].resize(bnum);
		}
		catch (bad_alloc& xa) { // Catch block, for exceptions
			cerr << "An exception occurred: " << xa.what() << "\n";
			return 0;
		} // End of catch block
		for(UInt_t q=0; q<snum; q++){
			try{
				s[p][q].resize(steps[p]);
				ds[p][q].resize(steps[p]);
				seff[p][q].resize(steps[p]);
				dseff[p][q].resize(steps[p]);
			}
			catch (bad_alloc& xa) { // Catch block, for exceptions
				cerr << "An exception occurred: " << xa.what() << "\n";
				exit(EXIT_FAILURE);
			} // End of catch block
		}
		for(UInt_t r=0; r<bnum; r++){
			try{
				b[p][r].resize(steps[p]); 
				db[p][r].resize(steps[p]);
				brej[p][r].resize(steps[p]);
				dbrej[p][r].resize(steps[p]);
			}
			catch (bad_alloc& xa) { // Catch block, for exceptions
				cerr << "An exception occurred: " << xa.what() << "\n";
				exit(EXIT_FAILURE);
			} // End of catch block
		}

	}


	return true;
}

void prepTuples(){
	sabsinit=0; 
	dsabsinit=0;
	babsinit=0;
	dbabsinit=0;
	for(UInt_t i = 0; i<snum; i++){
		sinFile[i] = TFile::Open(sinname[i]);
		sintuple[i] = (TTree*)sinFile[i]->Get(stname[i]);
		if(scutme[i]){
			spreinit[i] = sintuple[i]->GetEntries();
			tmpFile->cd();
			sintuplecut[i]= sintuple[i]->CopyTree(sincutname[i]);
			TString newname = "signal_preproc_";
			//char dtoc[20];
			//sprintf(dtoc,"%i",i);
			//newname.Append(dtoc);
			newname += i;
			sintuplecut[i]->SetName(newname);
			sinit[i] = getEntriesSignal("",i);
		}else{
			sinFile[i]->cd();
			sintuplecut[i]= sintuple[i];
			spreinit[i] = sinit[i] = getEntriesSignal("",i);
		}
		dsinit[i] = sqrt((Double_t)sinit[i]);
		sabsinit += sinit[i];
	}
	dsabsinit = sqrt(sabsinit);
	for(UInt_t j = 0; j<bnum; j++){
		binFile[j] = TFile::Open( binname[j] );
		bintuple[j] = (TTree*)binFile[j]->Get(btname[j]);
		if(bcutme[j]){
			bpreinit[j] = bintuple[j]->GetEntries();
			tmpFile->cd();
			bintuplecut[j]= bintuple[j]->CopyTree(bincutname[j]);
			TString newname = "background_preproc_";
			//char dtoc[20];
			//sprintf(dtoc,"%i",j);
			//newname.Append(dtoc);
			newname += j;
			bintuplecut[j]->SetName(newname);
			binit[j] = getEntriesBackground("",j);
		}else{
			binFile[j]->cd();
			bintuplecut[j]= bintuple[j];
			bpreinit[j] = binit[j] = getEntriesBackground("",j);
		}
		dbinit[j] = sqrt((Double_t)binit[j]);
		babsinit += binit[j];
	}
	dbabsinit = sqrt(babsinit);
}

void writePlot(UInt_t cut, TDirectory *dir){
	dir->cd();
	guiPlot(cut);
	guiACanvas->SetName(cname[cut]);
	guiACanvas->Write();
	dir->Write(); //? 
}

void PlotSoRSB(UInt_t cut){

	Double_t* cutValcut = new Double_t [cutVal[cut].size()];
	copy( cutVal[cut].begin(), cutVal[cut].end(), cutValcut);
	Double_t* dcutValcut = new Double_t [dcutVal[cut].size()];
	copy( dcutVal[cut].begin(), dcutVal[cut].end(), dcutValcut);
	Double_t* sorsbcut = new Double_t [SoRSB[cut].size()];
	copy( SoRSB[cut].begin(), SoRSB[cut].end(), sorsbcut);
	Double_t* dsorsbcut = new Double_t [dSoRSB[cut].size()];
	copy( dSoRSB[cut].begin(), dSoRSB[cut].end(), dsorsbcut);
	TGraphErrors * SoRSBGraph = new TGraphErrors(steps[cut],cutValcut,sorsbcut,dcutValcut,dsorsbcut);
	SoRSBGraph->SetLineWidth(2);
	SoRSBGraph->Draw("AL1");
	SoRSBGraph->SetTitle("S/sqrt(S+B) for cut "+cname[cut]);
	SoRSBGraph->GetXaxis()->SetTitle(cname[cut]);
	SoRSBGraph->GetYaxis()->SetTitle("S/sqrt(S+B)");


	TArrow* SoRSBarrow1 = new TArrow(cutVal[cut][maxk[cut]],SoRSBGraph->GetYaxis()->GetXmin(),cutVal[cut][maxk[cut]],SoRSB[cut][maxk[cut]],0.01,"<-");
	SoRSBarrow1->SetLineWidth(2) ;
	SoRSBarrow1->SetLineColor(kBlue);
	SoRSBarrow1->Draw();

	TArrow* SoRSBarrow2 = new TArrow(SoRSBGraph->GetXaxis()->GetXmin(),SoRSB[cut][maxk[cut]],cutVal[cut][maxk[cut]],SoRSB[cut][maxk[cut]],0.01,"<-");
	SoRSBarrow2->SetLineWidth(2) ;
	SoRSBarrow2->SetLineColor(kBlue);
	SoRSBarrow2->Draw();
}
void PlotSoRSBSteps(){
	TCanvas * evoCanvas = new TCanvas("S/sqrt(S+B) evolution", "S/sqrt(S+B) evolution",800,600);
	Double_t* SoRSBStepArr = new Double_t [SoRSBSteps.size()];
	Double_t* dSoRSBStepArr = new Double_t [dSoRSBSteps.size()];
	Double_t* StepArr = new Double_t [Steps.size()];
	copy( SoRSBSteps.begin(), SoRSBSteps.end(), SoRSBStepArr);
	copy( dSoRSBSteps.begin(), dSoRSBSteps.end(), dSoRSBStepArr);
	copy( Steps.begin(), Steps.end(), StepArr);
	TGraphErrors * SoRSBStepsGraph = new TGraphErrors(nsteps,StepArr,SoRSBStepArr,0,dSoRSBStepArr);
	SoRSBStepsGraph->SetLineWidth(2);
	SoRSBStepsGraph->Draw("AL1");
	SoRSBStepsGraph->SetTitle("S/sqrt(S+B) evolution WRT number of reoptimisations");
	SoRSBStepsGraph->GetYaxis()->SetTitle("S/sqrt(S+B)");
	//	SoRSBStepsGraph->GetXaxis()->SetTitle("reoptimisations");
	for(UInt_t i = 1; i< StepNames.size()+1; i++){
		SoRSBStepsGraph->GetXaxis()->SetBinLabel(SoRSBStepsGraph->GetXaxis()->FindBin(i),StepNames[i-1]);
	}
	evoCanvas->Write();
	delete SoRSBStepArr;
	delete dSoRSBStepArr;
	delete StepArr;
	SoRSBStepsGraph->Delete();
}
void PlotRoC(UInt_t cut){
	Double_t* sefftotcut = new Double_t [sefftot[cut].size()];
	copy( sefftot[cut].begin(), sefftot[cut].end(), sefftotcut);
	Double_t* dsefftotcut = new Double_t [dsefftot[cut].size()];
	copy( dsefftot[cut].begin(), dsefftot[cut].end(), dsefftotcut);

	Double_t* brejtotcut = new Double_t [brejtot[cut].size()];
	copy( brejtot[cut].begin(), brejtot[cut].end(), brejtotcut);
	Double_t* dbrejtotcut = new Double_t [dbrejtot[cut].size()];
	copy( dbrejtot[cut].begin(), dbrejtot[cut].end(), dbrejtotcut);


	TGraphErrors * RocGraph = new TGraphErrors(steps[cut],sefftotcut,brejtotcut,dsefftotcut,dbrejtotcut);
	RocGraph->SetLineWidth(2);
	RocGraph->Draw("AL1");
	RocGraph->SetTitle("Background Rejection vs. Signal Efficiency for cut "+cname[cut]);
	RocGraph->GetYaxis()->SetTitle("Background Rejection");
	RocGraph->GetXaxis()->SetTitle("Signal Efficiency");


	TArrow* RoCarrow1 = new TArrow(sefftot[cut][maxk[cut]],RocGraph->GetYaxis()->GetXmin(),sefftot[cut][maxk[cut]],brejtot[cut][maxk[cut]],0.01,"<-");
	RoCarrow1->SetLineWidth(2) ;
	RoCarrow1->SetLineColor(kBlue);
	RoCarrow1->Draw();

	TArrow* RoCarrow2 = new TArrow(RocGraph->GetXaxis()->GetXmin(),brejtot[cut][maxk[cut]],sefftot[cut][maxk[cut]],brejtot[cut][maxk[cut]],0.01,"<-");
	RoCarrow2->SetLineWidth(2) ;
	RoCarrow2->SetLineColor(kBlue);
	RoCarrow2->Draw();
}

void PlotSeff(UInt_t cut){
	Double_t* cutValcut = new Double_t [cutVal[cut].size()];
	copy( cutVal[cut].begin(), cutVal[cut].end(), cutValcut);
	Double_t* dcutValcut = new Double_t [dcutVal[cut].size()];
	copy( dcutVal[cut].begin(), dcutVal[cut].end(), dcutValcut);


	Double_t* sefftotcut = new Double_t [sefftot[cut].size()];
	copy( sefftot[cut].begin(), sefftot[cut].end(), sefftotcut);
	Double_t* dsefftotcut = new Double_t [dsefftot[cut].size()];
	copy( dsefftot[cut].begin(), dsefftot[cut].end(), dsefftotcut);

	TGraphErrors * SeffGraph = new TGraphErrors(steps[cut],cutValcut,sefftotcut,dcutValcut,dsefftotcut);
	SeffGraph->SetLineWidth(2);
	SeffGraph->Draw("AL1");
	SeffGraph->SetTitle("Signal Efficiency for cut "+cname[cut]);
	SeffGraph->GetXaxis()->SetTitle(cname[cut]);
	SeffGraph->GetYaxis()->SetTitle("Signal Efficiency");



	TArrow* Seffarrow1 = new TArrow(cutVal[cut][maxk[cut]],SeffGraph->GetYaxis()->GetXmin(),cutVal[cut][maxk[cut]],sefftot[cut][maxk[cut]],0.01,"<-");
	Seffarrow1->SetLineWidth(2) ;
	Seffarrow1->SetLineColor(kBlue);
	Seffarrow1->Draw();

	TArrow* Seffarrow2 = new TArrow(SeffGraph->GetXaxis()->GetXmin(),sefftot[cut][maxk[cut]],cutVal[cut][maxk[cut]],sefftot[cut][maxk[cut]],0.01,"<-");
	Seffarrow2->SetLineWidth(2) ;
	Seffarrow2->SetLineColor(kBlue);
	Seffarrow2->Draw();
}

void PlotBrej(UInt_t cut){
	Double_t* cutValcut = new Double_t [cutVal[cut].size()];
	copy( cutVal[cut].begin(), cutVal[cut].end(), cutValcut);
	Double_t* dcutValcut = new Double_t [dcutVal[cut].size()];
	copy( dcutVal[cut].begin(), dcutVal[cut].end(), dcutValcut);

	Double_t* brejtotcut = new Double_t [brejtot[cut].size()];
	copy( brejtot[cut].begin(), brejtot[cut].end(), brejtotcut);
	Double_t* dbrejtotcut = new Double_t [dbrejtot[cut].size()];
	copy( dbrejtot[cut].begin(), dbrejtot[cut].end(), dbrejtotcut);

	TGraphErrors * BrejGraph = new TGraphErrors(steps[cut],cutValcut,brejtotcut,dcutValcut,dbrejtotcut);
	BrejGraph->SetLineWidth(2);
	BrejGraph->Draw("AL1");
	BrejGraph->SetTitle("Background rejection rate for cut "+cname[cut]);
	BrejGraph->GetXaxis()->SetTitle(cname[cut]);
	BrejGraph->GetYaxis()->SetTitle("Background rejection");


	TArrow* Brejarrow1 = new TArrow(cutVal[cut][maxk[cut]],BrejGraph->GetYaxis()->GetXmin(),cutVal[cut][maxk[cut]],brejtot[cut][maxk[cut]],0.01,"<-");
	Brejarrow1->SetLineWidth(2) ;
	Brejarrow1->SetLineColor(kBlue);
	Brejarrow1->Draw();

	TArrow* Brejarrow2 = new TArrow(BrejGraph->GetXaxis()->GetXmin(),brejtot[cut][maxk[cut]],cutVal[cut][maxk[cut]],brejtot[cut][maxk[cut]],0.01,"<-");
	Brejarrow2->SetLineWidth(2) ;
	Brejarrow2->SetLineColor(kBlue);
	Brejarrow2->Draw();

}
void guiPlot(UInt_t cut){
	guiACanvas->cd(1);
	PlotSoRSB(cut);
	guiACanvas->Update();
	guiACanvas->cd(2);
	PlotRoC(cut);
	guiACanvas->Update();
	guiACanvas->cd(3);
	PlotSeff(cut);
	guiACanvas->Update();
	guiACanvas->cd(4);
	PlotBrej(cut);
	guiACanvas->Update();
}

Int_t scanCut(UInt_t cut, TString otherCuts){
	TString cutstring;
	Double_t SB, dsw2, dbw2;

	Int_t meffk = -9999;
	Double_t maxeff = 0.0;
	UInt_t nearestk = 0;
	Double_t nearesteff = 9999;
	maxk[cut] = -9999;
	tmpmaxk[cut] = -9999;
	maxVal[cut] =0.0;
	tmpmaxVal[cut] =0.0;
	array1d suncut(snum);
	Double_t abssuncut=0.0;
	array1d	buncut(bnum);
	Double_t absbuncut=0.0;
	for(UInt_t i = 0; i<snum; i++){
		suncut[i] = getEntriesSignal(otherCuts,i);
		abssuncut += suncut[i];
	}
	for(UInt_t j = 0; j<bnum; j++){
		buncut[j] = getEntriesBackground(otherCuts,j);
		absbuncut += buncut[j];
	}

	for(UInt_t k = 0; k<steps[cut]; k++){
		cutstring = "";
		cutVal[cut][k] = (k*res[cut])+lower[cut];
		dcutVal[cut][k] = res[cut]/2.0;
		//char dtoc[20];
		//sprintf(dtoc,"%f",cutVal[cut][k]);
		cutstring.Append(cname[cut]);
		//cutstring.Append(dtoc);
		cutstring += cutVal[cut][k];
		if(otherCuts!= ""){cutstring.Append(And);}
		stot[cut][k] = 0.0;
		sw[cut][k] = 0.0;
		dsw2 = 0.0;
		for(UInt_t i = 0; i<snum; i++){
			if(suncut[i]==0.0){s[cut][i][k]=0.0;}else{
				s[cut][i][k] = getEntriesSignal(cutstring+otherCuts,i);
			}

			if(s[cut][i][k]!=0){
				ds[cut][i][k] = sqrt(s[cut][i][k]);
				seff[cut][i][k] = s[cut][i][k]/suncut[i];
				dseff[cut][i][k] = sqrt(seff[cut][i][k]*(1-seff[cut][i][k])/suncut[i]);
				stot[cut][k] +=s[cut][i][k];
				sw[cut][k]  += s[cut][i][k]*sweight[i];
				dsw2 += sweight[i]*sweight[i]*s[cut][i][k];
			}else{
				ds[cut][i][k] = 0.0;
				seff[cut][i][k] = 0.0;
				dseff[cut][i][k] = 0.0;
			}
		}
		if(stot[cut][k]!=0){
			dstot[cut][k] = sqrt(stot[cut][k]);
			dsw[cut][k] = sqrt(dsw2);
			sefftot[cut][k] = stot[cut][k]/abssuncut;
			dsefftot[cut][k]= sqrt(sefftot[cut][k]*(1-sefftot[cut][k])/abssuncut);
		}else{
			dstot[cut][k] = 0.0;
			dsw[cut][k] = 0.0;
			sefftot[cut][k] = 0.0;
			dsefftot[cut][k] = 0.0;
		}
		btot[cut][k]=0;
		bw[cut][k]=0;
		dbw2 =0;
		for(UInt_t j = 0; j<bnum; j++){
			if(buncut[j] == 0.0){b[cut][j][k] = 0.0;}else{
				b[cut][j][k] = getEntriesBackground(cutstring+otherCuts,j);
			}
			if(b[cut][j][k]!=0.0){
				db[cut][j][k] = sqrt(b[cut][j][k]);
				brej[cut][j][k] = 1.0 - (b[cut][j][k]/buncut[j]);	
				dbrej[cut][j][k] = sqrt(brej[cut][j][k]*(1.0-brej[cut][j][k])/buncut[j]);
				btot[cut][k] +=b[cut][j][k];
				bw[cut][k]  += b[cut][j][k]*bweight[j];
				dbw2 += b[cut][j][k]*bweight[j]*bweight[j];
			}else{
				db[cut][j][k]=0.0;
				brej[cut][j][k]=1.0;
				dbrej[cut][j][k]=0.0;
			}
		}
		if(btot[cut][k]!=0.0){
			dbtot[cut][k] = sqrt(stot[cut][k]);
			dbw[cut][k] = sqrt(dbw2);
			brejtot[cut][k]=1.0 - btot[cut][k]/absbuncut;
			dbrejtot[cut][k]= sqrt(brejtot[cut][k]*(1.0-brejtot[cut][k])/absbuncut);
		}else{
			dbtot[cut][k]=0.0;
			dbw[cut][k]=0.0;
			brejtot[cut][k]=1.0;
			dbrejtot[cut][k]=0.0;
		}
		if(sw[cut][k]!=0){
			BoS[cut][k] = bw[cut][k]/sw[cut][k];
			dBoS[cut][k] = (dbw2*sw[cut][k]*sw[cut][k]+dsw2*bw[cut][k]*bw[cut][k])/(sw[cut][k]*sw[cut][k]*sw[cut][k]*sw[cut][k]);
			SB = sw[cut][k] + bw[cut][k];
			SoRSB[cut][k] = sw[cut][k]/sqrt(SB);
			dSoRSB[cut][k] = 0.5*sqrt((4.0*dsw2*bw[cut][k]*bw[cut][k] + 4.0*dsw2*bw[cut][k]*sw[cut][k]+dsw2*sw[cut][k]*sw[cut][k]+dbw2*sw[cut][k]*sw[cut][k])/(pow(SB,3.0)));

		}else{
			SoRSB[cut][k]=0.0;
			dSoRSB[cut][k]=0.0;
			BoS[cut][k] = bw[cut][k]/zero;
			dBoS[cut][k] = BoS[cut][k]*sqrt((zero/(zero*zero)));
		}

		if(sefftot[cut][k] >= maxeff){
			meffk =  k;
			maxeff = sefftot[cut][k];
			//	cout << "MAXEFF: " << sefftot[cut][k] << endl;
		}

		if(sefftot[cut][k] >= mineff[cut] && sefftot[cut][k] <= nearesteff){
			nearestk =  k;
			nearesteff = sefftot[cut][k];

			//	cout << "nearesteff: " << sefftot[cut][k] << endl;

		}

		if(k>2){

			if(SoRSB[cut][k-1]>=maxVal[cut]){
				if(SoRSB[cut][k-1]>=SoRSB[cut][k-2] && SoRSB[cut][k-1]>SoRSB[cut][k]){
					maxVal[cut] = SoRSB[cut][k-1]; 
					maxk[cut] = k-1;
				}
				if(SoRSB[cut][k-1]>SoRSB[cut][k-2] && SoRSB[cut][k-1]==SoRSB[cut][k]){
					maxVal[cut] = SoRSB[cut][k-1]; 
					maxk[cut] = k-1;
				}
			}
		}else{

			if(SoRSB[cut][k]>=maxVal[cut]){
				maxVal[cut] = SoRSB[cut][k];
				maxk[cut] = k;
			}
		}

	}

	guiPlot(cut);

	if(sefftot[cut][maxk[cut]] > mineff[cut]){
		return maxk[cut];

	}else{
		if(sefftot[cut][nearestk]  > sefftot[cut][maxk[cut]]){
			cout << "WARNING: Max. S/sqrt(S+B) occurs below min. efficiency requirement. Using S/sqrt(S+B) at min. efficiency instead" << endl;
			cout << "Cut : " << cname[cut] << "	max. eff: " << prettyPrint(maxeff) << "	req. min. eff : " << mineff[cut] << "	optimal eff : " << prettyPrint(sefftot[cut][maxk[cut]]) << endl;
			maxk[cut] = nearestk;
			maxVal[cut] = SoRSB[cut][nearestk];
			return maxk[cut];
		}else{
			maxk[cut] = meffk;
			maxVal[cut] = SoRSB[cut][meffk];
			cout << "WARNING: Min. efficiency requirement for cut " << cname[cut] << " unreachable." << endl;
			cout << "Cut : " << cname[cut] << "	max. eff : " << prettyPrint(maxeff) << "	req. min. eff : " << mineff[cut] << "	optimal eff : " << prettyPrint(sefftot[cut][maxk[cut]]) << endl;
			return maxk[cut];
		}
	}


}
void orderHardestB(){ //orders cuts with least efficient in signal first
	array1b used(ncuts,false);
	Double_t h = -0.1;
	UInt_t min = ncuts+1;
	for(UInt_t j=0; j<ncuts; j++){
		h=-0.1;
		for(UInt_t i=0; i<ncuts; i++){
			if(used[i]==false&&brejtot[i][maxk[i]]>h){
				h = brejtot[i][maxk[i]];
				min = i;
			}
		}

		cutorder[j] = min;
		used[min]=true;
	}
}

void orderHardestS(){ //orders cuts with least efficient in signal first
	array1b used(ncuts,false);
	Double_t h = 1.1;
	UInt_t min = ncuts+1;
	for(UInt_t j=0; j<ncuts; j++){
		h=1.1;
		for(UInt_t i=0; i<ncuts; i++){
			if(used[i]==false&&sefftot[i][maxk[i]]<h){
				h = sefftot[i][maxk[i]];
				min = i;
			}
		}

		cutorder[j] = min;
		used[min]=true;
	}
}

void orderRandom(TRandom3 *rng){ //randomises cut order
	UInt_t randcut = UInt_t(rng->Rndm()*ncuts);
	array1b used(ncuts,false);
	for(UInt_t j=0; j<ncuts; j++){
		while(used[randcut]==true){
			randcut = UInt_t(rng->Rndm()*ncuts);
		}
		cutorder[j] = randcut;
		used[randcut]=true;
	}
}

void orderHardestSB(){ //orders cuts based on which leaves the least S+B
	array1b used(ncuts,false);
	Double_t h = 2.1;
	UInt_t min = ncuts+1;
	Double_t splusb;
	for(UInt_t j=0; j<ncuts; j++){
		h =2.1;
		for(UInt_t i=0; i<ncuts; i++){
			splusb = sefftot[i][maxk[i]] + 1 - brejtot[i][maxk[i]];
			if(used[i]==false&&splusb<h){
				h = splusb;
				min = i;
			}
		}
		cutorder[j] = min;
		used[min]=true;
	}
}

TString createCut(UInt_t exclude){ //creates a cut string of all optimal cuts except the one to optimise
	TString outString ="";

	for(UInt_t i =0; i<ncuts; i++){
		if(i!=exclude){
			outString.Append(cname[i]);
			char dtoc[20];
			sprintf(dtoc,"%g",cutVal[i][maxk[i]]);
			outString.Append(dtoc);
			//	outString.Append(prettyPrint(cutVal[i][maxk[i]]));
			outString.Append(And);
		}
	}
	outString = outString.Strip(TString::kTrailing,*And);
	return outString;
}

void banner(){
	cout << "  ________  ____  ___    "<< endl; 
	cout << " / ___/ _ \\/ __ \\/ _ \\   "<< " Cut Recursive OPtimiser" <<endl;
	cout << "/ /__/ , _/ /_/ / ___/   "<< " (c) Conor Fitzpatrick, 2008" <<endl;
	cout << "\\___/_/|_|\\____/_/ v1.2a "<< endl;
	cout << ""  << endl;
}

void help(char *args[]){
	cout<<	" Syntax: 		" << args[0] <<" <weightfile.list> <cutfile.list> <max. iterations> <Ordering Method> <output.root> [-b]"<< endl;
	cout<<	" Cutfile Syntax:	<cut> <lower bound> <upper bound> <resolution> <min. efficiency>" << endl;
	cout<<	" Weightfile Syntax:	<B/S> <filename.root> <path/to/ntuple> <weight or per-event variable> [preproc. cut]" << endl;
	cout<< ""  << endl;

	cout<< "batchmode is specified with the optional -b flag" << endl;
	cout<< "Cuts are expressed in the cutfile as VarA< or VarA>"  << endl;
	cout<< "to denote less than and greater than respectively." << endl;
	cout<< "Cuts cannot contain any white space, but can be" << endl;
	cout<< "composed using the various mathematical operators" <<endl;
	cout<< " eg: VarA*VarB+(VarA/VarC^3)>  is a valid cut." <<endl;

	cout<< "" << endl;
	cout<< "To specify that an ntuple is signal in the weightfile,"<<endl; 
	cout<< "the first charachter of the line should be an 'S'" << endl;
	cout<< "Similarly a 'B' denotes background. You may specify" << endl;
	cout<< "as many input files of both signal and background as" <<endl;
	cout<< "you want." << endl;

	cout<< "" << endl;
	cout<< "Preprocessing cuts applied to ntuples can be different," << endl;
	cout<< "But for large files it is faster to apply these prior" <<endl;
	cout<< "to running CROP." <<endl;
	cout<< "" <<endl;
	cout<< "The ordering method defines the order in which cuts are applied during optimisation. The modes are:" << endl;
	cout<< "S:	Cuts are applied in order of ascending signal efficiency" << endl;
	cout<< "B:	Cuts are applied in order of descending background efficiency" << endl;
	cout<< "SB:	Cuts are applied in order of the efficiency sum S+B" << endl;
	cout<< "R:	Cuts are applied randomly" << endl;
	cout<< "" << endl;
	cout << "For help and bug reports, contact: conor.fitzpatrick@cern.ch" << endl;
}


void info(char *args[]){
	cout<<"Initialisation:			" << endl;
	cout<<"	optimising cuts:		" << args[2]	<< endl;
	cout<<"	over max. iterations:		" << args[3] 	<< endl;
	cout<<"	using convergence strategy:	" << args[4] 	<< endl;
	cout<<"	using ntuples in file:		" << args[1]	<< endl;
	cout<<"	output file:			" << args[5]	<< endl;

	cout << ""  << endl;
}

TString prettyPrint(Double_t num){
	TString prettyString;
	sprintf (pretty, "%4.3f",num);
	prettyString = pretty;
	return prettyString;
}


Double_t getEntriesSignal(TString cut, UInt_t tuplenum){
	if(!usingSweightsS[tuplenum]){
		return (sintuplecut[tuplenum]->GetEntries(cut));
	}else{
		guiACanvas->cd(1);
		tmptuple = new TH1F("temp","temp",3,-10.0,10.0);
		if(cut != ""){

			sintuplecut[tuplenum]->Draw(cut+">>temp","("+cut+")*("+sweightvar[tuplenum]+")");
			//sintuplecut[tuplenum]->Draw(cut+">>temp",sweightvar[tuplenum]);
		}else{
			sintuplecut[tuplenum]->Draw(sweightvar[tuplenum]+">>temp",sweightvar[tuplenum]);
		}
		//tmptuple->Draw();
		Double_t tmptot = tmptuple->Integral();
		tmptuple->Delete();
		return tmptot;
	}
}
Double_t getEntriesBackground(TString cut, UInt_t tuplenum){
	if(!usingSweightsB[tuplenum]){
		return (bintuplecut[tuplenum]->GetEntries(cut));
	}else{
		guiACanvas->cd(1);
		tmptuple = new TH1F("temp","temp",3,-10.0,10.0);
		if(cut != ""){

			bintuplecut[tuplenum]->Draw(cut+">>temp","("+cut+")*("+bweightvar[tuplenum]+")");
			//bintuplecut[tuplenum]->Draw(cut+">>temp",bweightvar[tuplenum]);
		}else{
			bintuplecut[tuplenum]->Draw(bweightvar[tuplenum]+">>temp",bweightvar[tuplenum]);
		}
		//tmptuple->Draw();
		Double_t tmptot = tmptuple->Integral();
		tmptuple->Delete();
		return tmptot;
	}
}
