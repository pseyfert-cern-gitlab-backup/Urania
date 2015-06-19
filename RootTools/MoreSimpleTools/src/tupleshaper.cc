/* 
 * Tuple Shaper.
 * Resample an input ntuple to look like the shape from another ntuple.
 *
 */

#include <stdlib.h>
#include <iostream>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCint.h>
#include <TMath.h>
#include <TH1F.h>
#include <TH1.h>
#include <TTree.h>
#include <TRandom3.h>
#include <TStopwatch.h>
#include <TFormula.h>
#include <TTreeFormula.h>
#include <TTreeFormulaManager.h>
using std::cout;
using std::endl;
using std::flush;

int main(int argc, char *argv[]) {
	if(argc != 9 ){
		cout << "tuplesampler:  resamples from input to match the shape of target"<< endl;
		cout << "Syntax: " << argv[0] << " <target.root> <input.root> <path/to/ntuple> <formula> <nbins> <min> <max> <output1.root>"<< endl;
		return EXIT_FAILURE;
	}

	TFile *in;
	TFile *target;
	TString tname = argv[1];   
	TString inname = argv[2];   
	TString tpath = argv[3];    
	TString formula = argv[4];   
	Double_t nbins = atof(argv[5]);
	Double_t min = atof(argv[6]);
	Double_t max = atof(argv[7]);
	TFile *sout1(0);
	TString soutname1 = argv[8];
	TStopwatch sw;
	cout << "opening: " << tname << ", " << inname << endl;

	in = TFile::Open( inname );
	target = TFile::Open( tname );
	TString slash = "/";
  
	cout << "getting tree " << tpath << endl;
	TTree* inTree = (TTree*)in->Get(tpath);
  
	TTree* targetTree = (TTree*)target->Get(tpath);
  
	tpath.Resize(tpath.First(slash)); 
	
  UInt_t total =  inTree->GetEntries();
  
	sout1 = new TFile(soutname1,"RECREATE");
	sout1->mkdir(tpath);
	sout1->cd(tpath);	
	TTree *soutTree1 = inTree->CloneTree(0);
  
	cout << "--------TUPLESAMPLER ----------" << endl;
	cout << "target distribution from:" << tpath     << endl;
	cout << "sampling from:           " << inname     << endl;
	cout << "in file:                 " << tname      << endl;
	cout << "with formula:            " << formula     << endl;
  cout << "using binning:           " << nbins << ',' << min << ',' << max   << endl;
	cout << "to file:                 " << soutname1   << endl;
	cout << "---------------------------------------------------------" << endl;
  
  //first step, fill the histograms and normalize to get the ratios
  //get the maxima/minima
  TString drawthis=formula;
  //drawthis.Append(">>htemp");
  //targetTree->Draw(drawthis);
  //TH1F* htemp = (TH1F*)gDirectory->Get("htemp");
  //double min=htemp->GetBinLowEdge(1);
  //double max=htemp->GetBinLowEdge(htemp->GetNbinsX()+1);
  
  TH1F* targetH = new TH1F("target",formula,nbins,min,max);
  TH1F* inputH = new TH1F("input",formula,nbins,min,max);
  TH1F* outputH=new TH1F("output",formula,nbins,min,max);
  
  drawthis=formula;
  drawthis.Append(">>target");
  
  targetTree->Draw(drawthis);
  
  
  drawthis=formula;
  drawthis.Append(">>input");
  
  inTree->Draw(drawthis);
  
  TH1F* ratioH=(TH1F*)inputH->Clone("ratio");
  
  ratioH->Divide(targetH);
  
  //double minrat=ratioH->GetMinimum();
  int minbin=ratioH->GetMinimumBin();
  //cout << "min ratio " << minrat << " in "<< minbin << " at " << ratioH->GetBinLowEdge(minbin) << endl;
  
  double scale=inputH->GetBinContent(minbin)/targetH->GetBinContent(minbin);
  //cout << " scale " << scale << endl;
  //cout << " integral target " << scale*targetH->Integral() << endl;
  //cout << " integral source " << inputH->Integral() << endl;
  
  
  //targetH->Scale(scale);
  
  //now target is normalized so that it fits within source.
  
	//inTree->Print();
	int k = 0;
	int pc = 0;
  Float_t val =0.0;
  Int_t bin =0;
  TTreeFormula *aformula = new TTreeFormula("formula",formula,inTree);
	sw.Start();
	for(UInt_t i = 0; i<total; i++){
		inTree->GetEntry(i);
    val = aformula->EvalInstance(0);
    if(val>=min && val<=max)
    {
      bin=targetH->FindBin(val);
      //check if there are already enough from this sample
      //cout << bin << " " << val << " " << " " << outputH->GetBinContent(bin) << " " << targetH->GetBinContent(bin)*scale <<endl;
      
      if(outputH->GetBinContent(bin) < (targetH->GetBinContent(bin)*scale))
      {
        //fill the histogram and the tree
        outputH->Fill(val);
        soutTree1->Fill();
      }
      //otherwise just skip
    }
    
    pc = ((100*i)/total);
		if(pc == k+10){
			k = pc;
			cout << pc << "\% complete\r" << flush;
		}
	}
	cout << "100" << "\% complete\r" << endl;
	UInt_t out1 =  soutTree1->GetEntries();
  
	sout1->Write();
	sw.Stop();

	cout << "--------------------------------------------------------" << endl;
	cout << "Input contained   " << total << " events" << endl;
	cout << "Output contains " << out1 << " events" << endl;
	Double_t outRat = Double_t(out1)/Double_t(total);
	Double_t doutRat = sqrt(outRat*(1.0-outRat)/Double_t(total));
	cout << "Sampled ratio: " << outRat<<"+\\-"<< doutRat << endl;

	cout << "--------------------------------------------------------" << endl;
	sw.Print();
	cout << "done." << endl;

}
