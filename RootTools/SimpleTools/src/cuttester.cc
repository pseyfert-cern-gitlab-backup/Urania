/* cuttester: Part of the simpletools package
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
#include <fstream>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TMath.h>
#include <TTree.h>
#include <TStopwatch.h>
#include <vector>
#include <TH1F.h>

using namespace std;

char pretty[10]; 
UInt_t ncuts=0;
vector<TString> cuts;
const TString And = "&&";
TString allCuts = "";
TString weightVar = "";
TTree* inTree;
TH1F* tmphist;

Double_t getWeightedEntries(TString cut){
	tmphist = new TH1F("temp","temp",3,-10.0,10.0);
	if(cut != ""){
		inTree->Draw(cut+">>temp","("+cut+")*("+weightVar+")");
	}else{
		inTree->Draw(weightVar+">>temp",weightVar);
	}
	Double_t tmptot = tmphist->Integral();
	tmphist->Delete();
	return tmptot;
}

TString prettyPrint(Double_t num){
	TString prettyString;
	sprintf (pretty, "%4.3f",num);
	prettyString = pretty;
	return prettyString;
}

TString createCut(UInt_t exclude){ //creates a cut string of all optimal cuts except the one to optimise
	TString outString ="";
	for(UInt_t i =0; i<ncuts; i++){
		if(i!=exclude){
			outString.Append(cuts[i]);
			outString.Append(And);
		}
	}
	outString = outString.Strip(TString::kTrailing,*And);
	return outString;
}


int main(int argc, char *argv[]) {
	if(argc != 4 && argc !=5){
		cout << "cuttester:   	tests a set of cuts, giving inclusive and exclusive efficiencies"<< endl;
		cout << "author:        Conor Fitzpatrick, 2008"<< endl;
		cout << "Syntax: " << argv[0] << " <input.root> <path/to/ntuple> <cutlist.txt> [weight var]"<< endl;
		cout << "cutlist.txt is a list of cuts without spaces, eg: B_s_Mass<500"<< endl;
		return EXIT_FAILURE;
	}
	Bool_t usingWeights = false;
	if(argc == 5){
		usingWeights = true;
		weightVar = argv[4];
	}

	TFile *in(0);
	TString inname = argv[1];   
	TString tpath = argv[2];   
	std::string cutListName = argv[3];

	in = TFile::Open( inname );
	TString slash = "/";
	inTree = (TTree*)in->Get(tpath);
	tpath.Resize(tpath.First(slash)); 
	UInt_t total = inTree->GetEntries();
	Double_t totalw = (Double_t)total;
	if(usingWeights){
		totalw = getWeightedEntries("");
	}


	cout << "--------CUTTESTER - Conor Fitzpatrick, 2008 ----------" << endl;
	cout << "testing cuts in:	" << cutListName << endl;
	cout <<	"to ntuple:		" << tpath 	<< endl;
	cout <<	"in file:		" << inname 	<< endl;
	cout << "total entries:		" << total	<< endl;
	if(usingWeights){
		cout << "using weight var:	" << weightVar	<< endl;
		cout << "tot. weighted entries:	" << totalw	<< endl;
	}
	cout << "-------------------------------------------------------" << endl;


	ifstream fileStream;
	TString cut;
	std::string lineread;
	fileStream.open(cutListName.c_str());
	if (!fileStream){
		std::cout << "Error in opening cut file" << std::endl;
		return EXIT_FAILURE;
	}

	cout << "cut no. 	cut" << endl;
	cout << "-------------------------------------------------------" << endl;
	while(!cut.ReadLine(fileStream).eof()){
		if(cut.BeginsWith("#")){}else{	cuts.push_back(cut);

			allCuts.Append(cut);
			allCuts.Append(And);
			cout <<  ncuts << "	" << cut << endl;
			ncuts++;
		}
	}
	allCuts = allCuts.Strip(TString::kTrailing,*And);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

	vector<Double_t> exclacc(ncuts);
	vector<Double_t> excleff(ncuts);
	vector<Double_t> dexcleff(ncuts);
	vector<Double_t> dincleff(ncuts);
	vector<Double_t> incleff(ncuts);
	vector<Double_t> inclacc(ncuts);
	vector<Double_t> toteff(ncuts);
	vector<Double_t> dtoteff(ncuts);
	vector<Double_t> totacc(ncuts);
	TString totstring ="";
	TStopwatch sw;
	sw.Start();
	Double_t totpassing; 

	if(usingWeights){
	totpassing = getWeightedEntries(allCuts);
	}else{
	totpassing = (Double_t)inTree->GetEntries(allCuts);
	}
	cout << "cut no.		excl. eff.			incl. eff.			total eff.			cands. passing" << endl;


	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for(UInt_t i=0; i<ncuts; i++){
		//calculate exclusive efficiency
		if(usingWeights){
		exclacc[i] = getWeightedEntries(cuts[i]);
		}else{
		exclacc[i] = (Double_t)inTree->GetEntries(cuts[i]);
		}
		excleff[i] = ((Double_t)exclacc[i])/totalw;
		dexcleff[i] = sqrt(excleff[i]*(1.0-excleff[i])/totalw)*100;
		excleff[i] = excleff[i]*100;

		//calculate total efficicency
		totstring.Append(cuts[i]);
		if(usingWeights){
		totacc[i] = getWeightedEntries(totstring);
		}else{
		totacc[i] = (Double_t)inTree->GetEntries(totstring);
		}
		toteff[i] = ((Double_t)totacc[i])/totalw;
		dtoteff[i]= sqrt(toteff[i]*(1.0-toteff[i])/totalw)*100;
		toteff[i]=toteff[i]*100;
		totstring.Append("&&");

		//calculate inclusive efficiency
		if(usingWeights){
		inclacc[i] = getWeightedEntries(createCut(i));
		}else{
		inclacc[i] = (Double_t)inTree->GetEntries(createCut(i));
		}
		//cout << "This cut: " << cuts[i] << " All other cuts: " << createCut(i) << endl;
		//cout << "evts. after all other cuts: " << inclacc[i] << endl;
		//cout << "evts. after all cuts: " << totpassing << endl;
		incleff[i] = totpassing/inclacc[i];
		dincleff[i] = sqrt(incleff[i]*(1.0-incleff[i])/(inclacc[i]))*100;
		incleff[i]=incleff[i]*100;

		cout << i << "	&	$" << prettyPrint(excleff[i]) << "\\pm" << prettyPrint(dexcleff[i]) << "\\%$	&	$" << prettyPrint(incleff[i])<<"\\pm"<<prettyPrint(dincleff[i])<<"\\%$	&	$" <<prettyPrint(toteff[i]) << "\\pm" << prettyPrint(dtoteff[i]) << "\\%$	&       $" << totacc[i] << "$	\\\\" << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	sw.Stop();
	sw.Print();
	cout<< "done." << endl;

}
