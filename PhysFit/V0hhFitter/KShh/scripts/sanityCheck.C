#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "TFile.h"
#include "TMath.h"

std::pair<double,double> div(std::pair<double,double> lhs,std::pair<double,double> rhs)
{
	double ratio = lhs.first/rhs.first;
	double relLhs = lhs.second/lhs.first;
	double relRhs = rhs.second/rhs.first;
	double error = ratio * sqrt(relLhs*relLhs + relRhs*relRhs);
	return std::make_pair(ratio,error);
}

void sanityCheck()
{
	std::vector<std::string> KS;
	KS.push_back("DD");
	KS.push_back("LL");
	std::vector<std::string> invMass;
	invMass.push_back("pipi");
	invMass.push_back("piK" );
	invMass.push_back("Kpi" );
	//BECAUSE BLIND	//	invMass.push_back("KK"  );
	std::vector<std::string> year;
	year.push_back("2011");
	year.push_back("2012a");
	year.push_back("2012b");
	
	TFile* f = TFile::Open("~/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Fit-WS-Standard-Louis-Loose-Exponential-Standard.root","READ");
	RooWorkspace *w = (RooWorkspace*) f->Get("newDesktop");
	RooFitResult* fitRes = (RooFitResult*) w->genobj("rfres_fitResults");
	fitRes->Print();
	for (std::vector<std::string>::iterator itInvMass = invMass.begin() ; itInvMass != invMass.end() ; ++itInvMass)
		{	
			std::vector<std::pair<double,double> > ratios;
			double sumWeights(0);
			double sum(0);
			double sumSqErrors(0);
			std::cout << "Invariant mass : " << *itInvMass << std::endl;
			unsigned int n(0);
			for (std::vector<std::string>::iterator itYear = year.begin() ; itYear != year.end() ; ++itYear)
				for (std::vector<std::string>::iterator itKS = KS.begin() ; itKS != KS.end() ; ++itKS)
					{
						std::string BdName = "Bd2KS"+(*itInvMass)+(*itKS)+"_"+(*itYear)+"_pdf_KS"+(*itInvMass)+(*itKS)+"_"+(*itYear)+"_Yield";
						std::string BsName = "Bs2KS"+(*itInvMass)+(*itKS)+"_"+(*itYear)+"_pdf_KS"+(*itInvMass)+(*itKS)+"_"+(*itYear)+"_Yield";
						RooArgList finPars = fitRes->floatParsFinal();
						double valBd = ((RooRealVar*) &finPars[finPars.index(BdName.c_str())])->getVal();
						double errBd = ((RooRealVar*) &finPars[finPars.index(BdName.c_str())])->getError();
						double valBs = ((RooRealVar*) &finPars[finPars.index(BsName.c_str())])->getVal();
						double errBs = ((RooRealVar*) &finPars[finPars.index(BsName.c_str())])->getError();
						std::pair<double,double> ZeeRatio = div(std::make_pair(valBd,errBd),std::make_pair(valBs,errBs));
						ratios.push_back(ZeeRatio);
						sumWeights += 1./(ZeeRatio.second*ZeeRatio.second);
						sum += ZeeRatio.first/(ZeeRatio.second*ZeeRatio.second);
						sumSqErrors += ZeeRatio.second*ZeeRatio.second;
						n++;
						std::cout << *itYear << "," << *itKS << ": " << ZeeRatio.first << " +/- " << ZeeRatio.second << std::endl;
					}
			//Now calculate everything.
			double mean = (1./sumWeights)*sum;
			double error = sqrt(1./sumWeights);
			double chiSq(0);
			for (std::vector<std::pair<double,double> >::iterator it = ratios.begin() ; it != ratios.end() ; ++it)
				chiSq += (mean-it->first)*(mean-it->first)/(it->second*it->second);
			std::cout << "Mean is " << mean << " +/- " << error 
					  << " and chi square is " << chiSq << "/" << n << " corresponding to a probability of " << TMath::Prob(chiSq,n) << std::endl;			
		}
}
