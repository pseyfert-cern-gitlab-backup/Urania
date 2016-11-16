#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "TFile.h"
#include "TMath.h"


//A little macro to ackowledge if sWeights and fits on data give the same results.
int compare_sWeights()
{
	std::pair<std::string,std::string> fileNames = std::make_pair(
																  "~/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Fit-WS-Standard-Louis-Tight-Exponential-Standard.root",
																  "~/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Fit-WS-sWeights-Louis-Tight-Exponential-Standard.root"
																  );
	TFile *f;
	f = TFile::Open(fileNames.first.c_str());
	RooFitResult *firstRes = ((RooFitResult*)((RooWorkspace*) f->Get("newDesktop"))->genobj("rfres_fitResults"));
	f->Close();
	f = TFile::Open(fileNames.second.c_str());
	RooFitResult *secondRes = ((RooFitResult*)((RooWorkspace*) f->Get("newDesktop"))->genobj("rfres_fitResults"));
	f->Close();
	std::vector<std::string> meson;
	meson.push_back("Bd");
	meson.push_back("Bs");
	std::vector<std::string> invMass;
	invMass.push_back("pipi");
	invMass.push_back("piK" );
	invMass.push_back("Kpi" );
	invMass.push_back("KK"  );
	std::vector<std::string> year;
	year.push_back("2011");
	year.push_back("2012a");
	year.push_back("2012b");
	std::vector<std::string> KS;
	KS.push_back("DD");
	KS.push_back("LL");
	firstRes->Print();
    for (std::vector<std::string>::iterator itInvMass = invMass.begin() ; itInvMass != invMass.end() ; ++itInvMass)
		for (std::vector<std::string>::iterator itYear = year.begin() ; itYear != year.end() ; ++itYear)
			for (std::vector<std::string>::iterator itMeson = meson.begin() ; itMeson != meson.end() ; ++itMeson)
				for (std::vector<std::string>::iterator itKS = KS.begin() ; itKS != KS.end() ; ++itKS)
					{
						if (*itMeson == "Bs" && *itInvMass == "KK")
							continue;
						std::string varName = (*itMeson)+"2KS"+(*itInvMass)+(*itKS)+"_"+(*itYear)+"_pdf_KS"+(*itInvMass)+(*itKS)+"_"+(*itYear)+"_Yield";
						//						std::cout << varName << std::endl;
						RooRealVar *varFirst  = (RooRealVar*) &(firstRes ->floatParsFinal()[firstRes ->floatParsFinal().index(varName.c_str())]);
						RooRealVar *varSecond = (RooRealVar*) &(secondRes->floatParsFinal()[secondRes->floatParsFinal().index(varName.c_str())]);
						std::pair<double,double> val1 = std::make_pair(varFirst ->getVal(),varFirst ->getError());
						std::pair<double,double> val2 = std::make_pair(varSecond->getVal(),varSecond->getError());
						double sigmas = (val1.first - val2.first)/sqrt(val1.second*val1.second + val2.second*val2.second);
						std::cout << (*itMeson)+"2KS"+(*itInvMass)+(*itKS)+"_"+(*itYear) << ": " << sigmas << std::endl;
					}
	return 0;
}
