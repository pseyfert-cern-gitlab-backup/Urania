#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TROOT.h"

// Settings for the number of signal and background events (only used if !finalVersion). "0" means as many as possible.
TString NumberEventsSgn = "0"; //"240000"; //"120000";
TString NumberEventsBkg = "0"; //"120000"; //"60000";




//usage
//MakeFlatteningFunction("../TMVA_training/149c1818_MC12vsMC12.root",  "TestTree", "BDT", -1., 1.01, false, 300, "149c1818.C", "classID==0")



void MakeFlatteningFunction(
	//Input file and tree to be used ("TrainTree" or "TestTree"):
	TString InputFile = "TMVA_output.root", TString Tree = "TrainTree",
	// Leaf in the tree that represents the classifier, maximum and minimum value:
	TString Classifier = "MLP", double Left = -0.2, double Right = 1.2,
	// Invert order?
	bool Invert = true,
	// No of points in the lookup table created:
	const int noBins = 1000, 
	// Output file name:
	int varset = 0x149cf818,
  TString CutString = "productionweightMC11v3*(cleaningcut&&Hlt1Dec&&Hlt2Dec&&L0Dec&&mass_p0p1>250&&abs(mass_p0p2-1020.4)>20&&abs(mass_p1p2-1020.4)>20&&NeuroBayes_0x145cf818>-50.)")
{
	// Input stuff
	TFile* File = new TFile(InputFile);
	TNtuple* Data = (TNtuple*)File->Get(Tree);
	TH1D* OriginalHisto = new TH1D("OriginalHisto","",noBins,Left,Right);
	
	Data->Project("OriginalHisto",Classifier,CutString);

  TString OutputFile = Form("flatter_0x%x.h",varset);
	
	// Calculate accumulated histogram
	int AccumulatedHisto[noBins];
	int sum = 0;
	for (int i = 0; i<noBins; i++) {
		sum += OriginalHisto->GetBinContent(i);
		AccumulatedHisto[i] = sum;
	} 
	sum += OriginalHisto->GetBinContent(noBins+1);
	
	// Calculate output stuff
	double output[noBins];
	double input[noBins];
	if (Invert) {
		for (int i = 0; i < noBins; i++) {
			output[i] = 1 - (double) AccumulatedHisto[i] / sum;
		}
	} else {
		for (int i = 0; i < noBins; i++) {
			output[i] = (double) AccumulatedHisto[i] / sum;
		}
	}
	for (int i = 0; i < noBins; i++) {
		input[i] = (double) Left + i * (Right - Left) / (noBins-1);
	}
	
	// Save as pseudo script
	std::ofstream FileStream;
	FileStream.open(OutputFile);
	
	FileStream << "// Need to add use RichDet v* Det to requirements file" << std::endl;
	FileStream << std::endl;
	
	FileStream << "// Include" << std::endl;
	FileStream << "#include \"RichDet/Rich1DTabFunc.h\"" << std::endl;
	FileStream << std::endl;
	
	FileStream << "// Create object" << std::endl;
  FileStream << "template<>" << std::endl;
	FileStream << "TabulatedFunction1D* flatter<" << varset << ">() {" << std::endl;

	FileStream << "TabulatedFunction1D* FlattenLookupTable;" << std::endl;
	FileStream << std::endl;
	
	FileStream << "// Initialisation (should do this just once, slow)" << std::endl;
	FileStream << "double input[" << noBins <<"] = {";
	for (int i = 0; i < noBins - 1; i++)
	{
		FileStream << input[i] << ", ";
	}
	FileStream << input[noBins-1] << "};" << std::endl;
	FileStream << "double output[" << noBins <<"] = {";
	for (int i = 0; i < noBins - 1; i++)
	{
		FileStream << output[i] << ", ";
	}
	FileStream << output[noBins-1] << "};" << std::endl;
	FileStream << "FlattenLookupTable = new TabulatedFunction1D(input, output, " << noBins << ", gsl_interp_linear);" << std::endl;
	FileStream << std::endl;
	
	FileStream << "return FlattenLookupTable;}" << std::endl;
	
	FileStream.close();
	
	// delete objects
	delete File;
	//delete Data;
}




