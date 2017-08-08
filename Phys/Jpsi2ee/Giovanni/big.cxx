{ //comment this line if void line is uncommented, and uncomment includes

/*
//using namespace TMath;
#include "RooPlot.h"
#include "RooHist.h"
#include "RooHistPdf.h"
#include "RooNDKeysPdf.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooExponential.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TVirtualPad.h"
#include "TPaveLabel.h"
#include "TStyle.h"
*/


using namespace RooFit;

//void big(){

	std::vector<TString> branches;
	branches.push_back("Psi_L0Global_TIS");
	branches.push_back("Psi_L0Global_TOS");
	branches.push_back("Psi_Hlt1Global_TIS");
	branches.push_back("Psi_Hlt1Global_TOS");
	branches.push_back("Psi_L0HadronDecision_TIS");
	branches.push_back("Psi_L0HadronDecision_TOS");
	branches.push_back("Psi_L0MuonDecision_TIS");
	branches.push_back("Psi_L0MuonDecision_TOS");
	branches.push_back("Psi_L0DiMuonDecision_TIS");
	branches.push_back("Psi_L0DiMuonDecision_TOS");
	branches.push_back("Psi_L0ElectronDecision_TIS");
	branches.push_back("Psi_L0ElectronDecision_TOS");
	branches.push_back("Psi_L0PhotonDecision_TIS");
	branches.push_back("Psi_L0PhotonDecision_TOS");
	branches.push_back("Psi_Hlt1TrackMVADecision_TIS");
	branches.push_back("Psi_Hlt1TrackMVADecision_TOS");
	branches.push_back("Psi_Hlt1TwoTrackMVADecision_TIS");
	branches.push_back("Psi_Hlt1TwoTrackMVADecision_TOS");
	branches.push_back("Psi_Hlt1SingleElectronNoIPDecision_TIS");
	branches.push_back("Psi_Hlt1SingleElectronNoIPDecision_TOS");

	RooRealVar Psi_M("Psi_M","Psi_M",2000,3600);
	RooRealVar Psi_PT("Psi_PT","Psi_PT",0,RooNumber::infinity());

	TFile *meas = TFile::Open("Acut.root");
	RooDataSet* data2 = (RooDataSet*)meas->Get("ds");
	data2=(RooDataSet*)data2->reduce("Psi_M<3600&&Psi_M>2000");
	RooDataSet* ptbin;

	RooRealVar mg1("mg1", "mean gauss 1",3100,2500,3500);
	RooRealVar sg1("sg1", "sigma gauss 1",1000,100,2000);
	RooGaussian gauss1("gauss1","gauss PDF 1",Psi_M,mg1,sg1);
	RooRealVar mg2("mg2", "mean gauss 2",3100,2500,3500);
	RooRealVar sg2("sg2", "sigma gauss 2",180,60,300);
	RooGaussian gauss2("gauss2","gauss PDF 2",Psi_M,mg2,sg2);
	RooRealVar mcb("mcb","mean cb",2000,4000);
	RooRealVar scb("scb","sigma cb",0,100);
	RooRealVar alpha("alpha","alpha",0.1,3);
	RooRealVar n("n","n",0.5,2);
	RooCBShape cb("cb","cbshape PDF",Psi_M,mcb,scb,alpha,n);
	RooRealVar c1("c1","proportionality coefficient 1",0.5,0,1);
	RooRealVar c2("c2","proportionality coefficient 2",0.1,0,0.2);
	RooAddPdf three("three","2xGaussian and CBShape",RooArgSet(gauss1,gauss2,cb),RooArgSet(c1,c2));

	alpha.setVal(0.43);
	alpha.setConstant();
	c1.setVal(0.153);
	c1.setConstant();
	c2.setVal(0.196);
	c2.setConstant();
	mcb.setVal(3063.8);
	mcb.setConstant();
	mg1.setVal(3043);
	mg1.setConstant();
	mg2.setVal(3069);
	mg2.setConstant();
	n.setVal(1.93);
	n.setConstant();
	scb.setVal(37.4);
	scb.setConstant();

	RooRealVar t("t","exponential PDF parameter",-0.00035,-1.,-0.);
	RooExponential expon("expon","exponential PDF",Psi_M,t);
	RooRealVar* c3;
	RooRealVar* c4;
	RooAddPdf* five;
	RooFitResult* rf2;
	RooStats::SPlot* m_sData;
	int sign_sum,back_sum;
	RooPlot* pic; //= Psi_M.frame();

	TFile* tree = TFile::Open("/eos/lhcb/user/p/pkoppenb/Jpsi2ee/Jpsi2017-1533.root");
	TTree* T = (TTree*)tree->Get("Hlt2DiElectronJPsiEETurbo_Tuple/DecayTree");

//	TFile* tree = TFile::Open("cutted.root");
//	TTree* T = (TTree*)tree->Get("DecayTree");

	TFile* outfile;// = new TFile("newbranches.root","recreate");
	TTree* outtree;// = new TTree("Friend","Friend");
	Double_t sWeight_sign, sWeight_back;
	TBranch* sBranch_sign;// = outtree->Branch("sWeight_sign",&sWeight_sign);
	TBranch* sBranch_back;// = outtree->Branch("sWeight_back",&sWeight_back);

	Double_t bm,ps,ep,em;
	T->SetBranchAddress("Psi_M",&bm);
	T->SetBranchAddress("Psi_PT",&ps);
	T->SetBranchAddress("eminus_PT",&em);
	T->SetBranchAddress("eplus_PT",&ep);
	int numEntries= T->GetEntries("");

	TH1D* sign;//=new TH1D("sign","sign",2,-0.5,1.5);
        TH1D* back;//=new TH1D("back","back",2,-0.5,1.5);
	Double_t s,b;
        TH1D* sf;//=new TH1D("sf","sign",100,-3,6);
        TH1D* bf;//=new TH1D("bf","back",100,-3,6);
	TH1D* sn;
	TH1D* bn;

        Double_t smax,bmax,smin,bmin;

	cout << "OK" << endl;

	int numgev = 12;
	for (int k=10; k<numgev; k++){
		cout << "bin number: " << k+1 << endl;

		ptbin=(RooDataSet*)data2->reduce("Psi_PT>(2000+"+TString::Format("%i",k)+"*1000) && Psi_PT<(2000+"+TString::Format("%i",k+1)+"*1000)");
		ptbin=(RooDataSet*)data2->reduce("Psi_PT>15000");
		c3= new RooRealVar("c3","prop. coeff. 3",0.1*ptbin->sumEntries(),0,ptbin->sumEntries());
		c4= new RooRealVar("c4","prop. coeff. 4",0.9*ptbin->sumEntries(),0,ptbin->sumEntries());
		five= new RooAddPdf("five","MC based fit on data with exponential and or chebyshev background",RooArgSet(three,expon),RooArgSet(*c3,*c4));
		rf2 = five->fitTo(*ptbin,Save());
		m_sData = new RooStats::SPlot("sData","sData",*ptbin,five,RooArgSet(*c3,*c4));
		sign_sum = m_sData->GetYieldFromSWeight("c3");
		back_sum = m_sData->GetYieldFromSWeight("c4");
		pic = Psi_M.frame();
		ptbin->plotOn(pic);
		five->plotOn(pic);
		pic->Draw();
		gPad->SaveAs("img/Psi_PT"+TString::Format("%i",k+1)+".png");
		pic->Clear();

		outfile = new TFile("tempbranches.root","recreate");
		outtree = new TTree("Friend","Friend");
		sBranch_sign = outtree->Branch("sWeight_sign",&sWeight_sign);
		sBranch_back = outtree->Branch("sWeight_back",&sWeight_back);
		T->AddFriend(outtree);

		int j=0;
		for(int i=0; i < numEntries; i++){
			T->GetEntry(i);
			Double_t d=(Double_t)i/numEntries;
			if (bm<3600 && bm>2000 && abs((em-ep)/(em+ep))<0.7 && ps>(2000+k*1000) && ps<(2000+(k+1)*1000)){
				sWeight_sign = ptbin->get(j)->getRealValue("c3_sw");
				sWeight_back = ptbin->get(j)->getRealValue("c4_sw");
				if (j%5000==0){
                        	        cout << d << endl;
                 	                cout << bm << endl;
					cout << ps << endl;
                               		cout << abs((em-ep)/(em+ep)) << endl;
                                	cout << sWeight_sign << endl;
                                	cout << sWeight_back << endl;
                                	cout << "" << endl;
                        	}
				j++;
			}
			else{
				sWeight_sign = 0;
				sWeight_back = 0;
			}
			outtree->Fill();
		}
		outtree->GetListOfBranches()->Print();

//		TFile* outf = new TFile("prov.root","recreate");
//		outtree = (TTree*)outf->Get("Friend");

		
		
		for(TString branch : branches){
			sign=new TH1D("sign","sign",2,-0.5,1.5);
			T->Draw(branch+">>sign","(1/"+TString::Format("%i",sign_sum)+")*sWeight_sign");
			s = sign->GetMean();
			sign->Delete();
			cout << branch << " sign_meanval: " << s << endl;
			back=new TH1D("back","back",2,-0.5,1.5);	
			T->Draw(branch+">>back","(1/"+TString::Format("%i",back_sum)+")*sWeight_back");
			b = back->GetMean();
			cout << branch << " back_meanval: " << b << endl;
			back->Delete();
		}
		
		TCanvas canvas;
		sf=new TH1D("sf","sign",100,-3,6);
		T->Draw("log(Psi_FDCHI2_OWNPV)/log(10.) >> sf","(1/"+TString::Format("%i",sign_sum)+")*sWeight_sign*(Psi_PT>(2000+"+TString::Format("%i",k)+"*1000) && Psi_PT<(2000+"+TString::Format("%i",k+1)+"*1000))");
		smax=sf->GetMaximum();
		smin=sf->GetMinimum();
		bf=new TH1D("bf","back",100,-3,6);
		T->Draw("log(Psi_FDCHI2_OWNPV)/log(10.) >> bf","(1/"+TString::Format("%i",back_sum)+")*sWeight_back*(Psi_PT>(2000+"+TString::Format("%i",k)+"*1000) && Psi_PT<(2000+"+TString::Format("%i",k+1)+"*1000))");
		bmax=bf->GetMaximum();
		bmin=bf->GetMinimum();
		sf->SetMaximum(1.05*max(smax,bmax));
		sf->SetMinimum(1.05*min(smin,bmin));
		sf->Draw();
		bf->SetLineColor(2);
		bf->Draw("same");
		canvas.SaveAs("img/Psi_FDCHI2_OWNPV"+TString::Format("%i",k+1)+".png");
		sf->Delete();
		bf->Delete();

		TCanvas canvass;
                sn=new TH1D("sn","sign",100,-3,6);
                T->Draw("(Psi_ENDVERTEX_Z-Psi_OWNPV_Z)*Psi_M/Psi_PZ >> sn","(1/"+TString::Format("%i",sign_sum)+")*sWeight_sign*(Psi_PT>(2000+"+TString::Format("%i",k)+"*1000) && Psi_PT<(2000+"+TString::Format("%i",k+1)+"*1000))");
                smax=sn->GetMaximum();
                smin=sn->GetMinimum();
                bn=new TH1D("bn","back",100,-3,6);
                T->Draw("(Psi_ENDVERTEX_Z-Psi_OWNPV_Z)*Psi_M/Psi_PZ >> bn","(1/"+TString::Format("%i",back_sum)+")*sWeight_back*(Psi_PT>(2000+"+TString::Format("%i",k)+"*1000) && Psi_PT<(2000+"+TString::Format("%i",k+1)+"*1000))");
                bmax=bn->GetMaximum();
                bmin=bn->GetMinimum();
                sn->SetMaximum(1.05*max(smax,bmax));
                sn->SetMinimum(1.05*min(smin,bmin));
                sn->Draw();
                bn->SetLineColor(2);
                bn->Draw("same");
                canvass.SaveAs("img/Psi_COMP"+TString::Format("%i",k+1)+".png");
                sn->Delete();
                bn->Delete();


		T->RemoveFriend(outtree);


	}


}

