#include "TFile.h"
#include "TMath.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include <iostream>
#include <map>
#include <vector>
int AnalyzeResults()
{
	TFile *f = TFile::Open("/afs/cern.ch/user/l/lohenry/Fitter/KShh/WS/Data-WS-Loose-sWeights.root","READ");
	RooWorkspace* newDesktop = (RooWorkspace*) f->Get("newDesktop");
	std::map<std::string,std::pair<double,double> > yields;
	std::vector<std::string> invMass;
	invMass.push_back("pipi");
	invMass.push_back("piK");
	invMass.push_back("Kpi");
	invMass.push_back("KK");
	std::vector<std::string> years;
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	std::vector<std::string> KScat;
	KScat.push_back("DD");
	KScat.push_back("LL");
	if (newDesktop == NULL)
		{
			std::cout << "No desktop!" << std::endl;
			return 1;
		}
	for (std::vector<std::string>::iterator itMass = invMass.begin() ; itMass != invMass.end() ; ++itMass)
		for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)
				{
					std::string name = "2KS"+(*itMass)+(*itKS)+"_"+(*itYears)+"_pdf_KS"+(*itMass)+(*itKS)+"_"+(*itYears)+"_Yield";
					if (newDesktop->var(("Bd"+name).c_str()) == NULL)
						{
							std::cout << "No var named " << "Bd"+name << std::endl;
							return 1;
						}
					yields["Bd2KS"+(*itMass)+(*itKS)+"_"+(*itYears)] = std::make_pair(newDesktop->var(("Bd"+name).c_str())->getVal(),newDesktop->var(("Bd"+name).c_str())->getError());
					yields["Bs2KS"+(*itMass)+(*itKS)+"_"+(*itYears)] = std::make_pair(newDesktop->var(("Bs"+name).c_str())->getVal(),newDesktop->var(("Bs"+name).c_str())->getError());
					if (itMass->find("KK") == std::string::npos)
						{
							double ratio = yields["Bs2KS"+(*itMass)+(*itKS)+"_"+(*itYears)].first/yields["Bd2KS"+(*itMass)+(*itKS)+"_"+(*itYears)].first;
							double error = ratio*TMath::Sqrt((1./(yields["Bs2KS"+(*itMass)+(*itKS)+"_"+(*itYears)].second*yields["Bs2KS"+(*itMass)+(*itKS)+"_"+(*itYears)].second))+
															 (1./(yields["Bd2KS"+(*itMass)+(*itKS)+"_"+(*itYears)].second*yields["Bd2KS"+(*itMass)+(*itKS)+"_"+(*itYears)].second)));
							std::cout << "Ratio of Bs/Bd in "+(*itMass)+" spectrum for " << (*itYears) << "," << (*itKS) << " is " << ratio << " +/- " << error << "." << std::endl;
						}
				}
	return 0;
};
