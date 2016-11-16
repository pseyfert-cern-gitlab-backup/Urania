#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

//ROOT
#include "TChain.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TH2D.h"
#include "TFile.h"

// RooFit

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
#include "V0hhFitter/ToyStudy.h"
#include "V0hhFitter/string_tools.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

// SQLite
#include <sqlite3.h> 

//Constraints
#include "KShh/Constraints/useConstraints.cpp"

void studyCompatibility(std::vector<std::pair<double,double> > factors)
{
  unsigned int n = factors.size();
  double A(0); //Sum of the squared errors;
  double B(0); //Sum of xj/(sJ*sJ)
  double C(0); //Sum of (xj*xj)/(sJ*sJ)
  double D(0); //Sum of the inverse of squared errors.
  for (std::vector<std::pair<double,double> >::iterator it = factors.begin() ; it != factors.end() ; it++)
    {
      A += it->second*it->second;
      B += it->first/(it->second*it->second);
      C += it->first*it->first/(it->second*it->second);
      D += 1./(it->second*it->second);
    }
  double mean = (1./D)*B;
  
  double min_chiSq(0);
  //Calculating the minimun of the chi square
  for (std::vector<std::pair<double,double> >::iterator it = factors.begin() ; it != factors.end() ; it++)
    min_chiSq += (mean-it->first)*(mean-it->first)/(it->second*it->second);
  //Calculating the error.
  //  double err = (1./D)*sqrt(B*B - D*(C-min_chiSq-1));  
  //  std::cout << err << " " << sqrt(A)/n << std::endl;
  double err = sqrt(A)/n;
  std::pair<double,double> k = std::make_pair(mean,err);
  double chiSq(0);
  for (std::vector<std::pair<double,double> >::iterator it = factors.begin() ; it != factors.end() ; it++)
    chiSq += (it->first-k.first)*(it->first-k.first)/(it->second*it->second+k.second*k.second);
  std::cout << "The average factor is " << k.first << " +/- " << k.second << ", and the chi2/ndof is " << chiSq <<"/"<<n << " (S=" << sqrt(chiSq) <<")" <<std::endl;  
}

int main()
{
  //Firstly count the categories and else...
  std::string fileName("constraints-DataFit-Vanilla");
  std::vector<std::string> modes;
  modes.push_back("pipi");
  modes.push_back("Kpi");
  modes.push_back("KK");
  std::vector<std::string> categories;
  categories.push_back("Charmless-Bd");
  categories.push_back("Charmless-Bs");
  categories.push_back("Charmed-Bd");
  categories.push_back("Charmed-Bs");
  categories.push_back("Charmonia-Bd");
  categories.push_back("Charmonia-Bs");
  categories.push_back("MissGamNR-Bd");
  categories.push_back("MissGamNR-Bs");
  categories.push_back("MissGamRes-Bd");
  categories.push_back("MissGamRes-Bs");
  
  std::vector<std::pair<std::string,std::string> > allowed;
  for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
    for (std::vector<std::string>::iterator itCat = categories.begin() ; itCat != categories.end() ; ++itCat)
      if (KShhConstraints::readKey(fileName,*itCat,*itModes))
	{
	  if (*itModes != "Kpi")
	    allowed.push_back(std::make_pair(*itCat,*itModes));
	  else 
	    allowed.push_back(std::make_pair(*itCat,"piK"));
	}
  unsigned int n = 2*allowed.size();
  std::cout << n << std::endl;
  
  TH1F* h_2011 = new TH1F("h_2011","2011",n,0,n);
  TH1F* h_2012a = new TH1F("h_2012a","2012a",n,0,n);
  TH1F* h_2012b = new TH1F("h_2012b","2012b",n,0,n);
  h_2011 ->SetMarkerColor(1);
  h_2011 ->SetLineColor(1);
  h_2012a->SetMarkerColor(2);
  h_2012a->SetLineColor(2);
  h_2012b->SetMarkerColor(4);
  h_2012b->SetLineColor(4);
  std::map<std::string,TH1F*> histos;
  histos["2011"] = h_2011;
  histos["2012a"] = h_2012a;
  histos["2012b"] = h_2012b;
  // Create the gaussian constraints (import from DB) 
  TString dir         = getenv("V0HHFITTERROOT");
  std::string V0hhDir = dir.Data();
  std::string dbTable_pr = V0hhDir+"/KShh/dB/partiallyRecoYielTable.db";
  sqlite3 *db_pr;
  int rc_pr = sqlite3_open(dbTable_pr.c_str(), &db_pr);
  if (rc_pr) {
    std::fprintf(stderr, "Can't open partially reco database: %s\n", sqlite3_errmsg(db_pr));
    exit(0);
  } else {
    fprintf(stderr, "Opened partially reconstructed bkg database successfully\n");
  }
  unsigned int i = 1;
  std::vector<std::string> KScat;
  KScat.push_back("DD");
  KScat.push_back("LL");
  std::vector<std::string> years;
  years.push_back("2011");
  years.push_back("2012a");
  years.push_back("2012b");
  for (std::vector<std::pair<std::string,std::string> >::iterator it = allowed.begin() ; it != allowed.end() ; ++it)
    for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)    
      {
	for (std::vector<std::string>::iterator itYear = years.begin() ; itYear != years.end() ; ++itYear)
	  {
	    const char *sqlRatio_pr;
	    std::string frac_bkg_str(""), frac_bkg_err_str("");
	    Double_t Fraction_bkg_val(0.), Fraction_err_bkg_val(0.);
	    sqlite3_stmt* stmt_pr   = NULL;
	    int retval_pr;
	    TString dbLinkPR  = "SELECTION LIKE 'LOOSE' AND PARTRECO LIKE '"+it->first+"' AND TREENAME LIKE '"+(it->second)+"' AND KSTYPE LIKE '"+(*itKS)+"' AND YEAR LIKE '"+(*itYear)+"'";
	    
	    // Retrive the estimation of the fraction information 
	    TString info_pr = "SELECT * from BKGYIELD WHERE "+dbLinkPR;
	    sqlRatio_pr     = info_pr.Data();
	    retval_pr       = sqlite3_prepare_v2(db_pr, sqlRatio_pr, -1, &stmt_pr, 0);
	    if (retval_pr){
	      printf("Selecting data from DB Failed (err_code=%d)\n", retval_pr);
	      std::cout << dbLinkPR << std::endl;
	      return 0;
	    }
	    while(1) {
	      retval_pr = sqlite3_step(stmt_pr);
	      if (retval_pr == SQLITE_ROW) {
		// Fraction mean value for each bkg 
		//		const unsigned char* frac_bkgLink    = sqlite3_column_text(stmt_pr, 14);
		const unsigned char* frac_bkgLink    = sqlite3_column_text(stmt_pr, 14);
		std::stringstream frac_bkg_tmp_str;
		frac_bkg_tmp_str << frac_bkgLink;
		frac_bkg_str = (frac_bkg_tmp_str).str();
		Fraction_bkg_val = atof((frac_bkg_str).c_str()); 
		// Fraction mean error value for each bkg 
		//		const unsigned char* frac_bkgErrLink = sqlite3_column_text(stmt_pr, 15);
		const unsigned char* frac_bkgErrLink = sqlite3_column_text(stmt_pr, 15);
		std::stringstream frac_bkg_err_tmp_str;
		frac_bkg_err_tmp_str << frac_bkgErrLink;
		frac_bkg_err_str = (frac_bkg_err_tmp_str).str();
		Fraction_err_bkg_val = atof((frac_bkg_err_str).c_str()); 
		break;
	      } 
	      else if(retval_pr == SQLITE_DONE) { 
		std::cout << "WARNING: REQUEST NOT FOUND:" << std::endl << dbLinkPR << std::endl;
		break;
	      }
	    }
	    if (*itYear == "2011")
	      {
		h_2011->SetBinContent(i,Fraction_bkg_val);
		h_2011->SetBinError(i,Fraction_err_bkg_val);
		h_2011->GetXaxis()->SetBinLabel(i,(it->first+","+it->second+","+*itKS).c_str());
	      }
	    if (*itYear == "2012a")
	      {
		h_2012a->SetBinContent(i,Fraction_bkg_val);
		h_2012a->SetBinError(i,Fraction_err_bkg_val);
	      }
	    if (*itYear == "2012b")
	      {
		h_2012b->SetBinContent(i,Fraction_bkg_val);
		h_2012b->SetBinError(i,Fraction_err_bkg_val);
	      }
	    Fraction_bkg_val = 0;
	    Fraction_err_bkg_val = 0;	
	  }
	++i;
      }
  TCanvas *C = new TCanvas("C","C",1800,1000);
  gStyle->SetOptStat(0);
  gPad->SetLogy();
  h_2011->SetTitle("");
  h_2011->Draw("E");
  h_2012a->Draw("E""same");
  h_2012b->Draw("E""same");
  C->SaveAs("Constraints-PartReco.png");
  
  //Finding FACTORS!
  //DD-LL factor.
  std::vector<std::pair<double,double> > fac_DDLL;
  for (std::map<std::string,TH1F*>::iterator it = histos.begin() ; it != histos.end() ; ++it) //Iterates on years.
    { 
      std::vector<std::pair<double,double> > fac_DDLL_Year;
      for (unsigned int i = 1 ; i <= allowed.size() ; i++)
	{        
	  double value = it->second->GetBinContent(2*i)/it->second->GetBinContent(2*i-1);
	  double error = value * sqrt((it->second->GetBinError(2*i-1))*(it->second->GetBinError(2*i-1))/(it->second->GetBinContent(2*i-1)*it->second->GetBinContent(2*i-1)) +
				      (it->second->GetBinError(2*i  ))*(it->second->GetBinError(2*i  ))/(it->second->GetBinContent(2*i  )*it->second->GetBinContent(2*i  )));
	  std::pair<double,double> factor = std::make_pair(value,error);
	  std::cout << it->first << ": "<< allowed[i-1].first << "," << allowed[i-1].second << " : (LL/DD) = "
		    << factor.first
		    << " +/- "
		    << factor.second
		    << std::endl;  
	  fac_DDLL_Year.push_back(factor);
	  fac_DDLL.push_back(factor);
	}
      studyCompatibility(fac_DDLL_Year);
      std::cout << std::endl;
    }
  studyCompatibility(fac_DDLL);
  
  //Inter-Year factors.
  std::cout << "Factors between years: " << std::endl;  
  std::vector<std::pair<double,double> > fac_Years;
  for (std::map<std::string,TH1F*>::iterator it1 = histos.begin() ; it1 != histos.end() ; ++it1)
    for (std::map<std::string,TH1F*>::iterator it2 = it1; it2 != histos.end() ; ++it2)
      if (it2->first != it1->first)
	{
	  std::vector<std::pair<double,double> > fac_Year;
	  for (unsigned int i = 1 ; i <= n ; i++)
	    {
	      std::string tempPR = allowed[((i+1)/2)-1].first+","+allowed[((i+1)/2)-1].second;
	      std::string tempMode = (i%2 == 0)? "LL":"DD";
	      fac_Year.push_back(std::make_pair(it1->second->GetBinContent(i)/it2->second->GetBinContent(i),
						(it1->second->GetBinContent(i)/it2->second->GetBinContent(i))*
						sqrt((it1->second->GetBinError(i))*(it1->second->GetBinError(i))/(it1->second->GetBinContent(i)*it1->second->GetBinContent(i)) +
						     (it2->second->GetBinError(i))*(it2->second->GetBinError(i))/(it2->second->GetBinContent(i)*it2->second->GetBinContent(i))
						     )));
	      if (it1->first == "2011")
		fac_Years.push_back(std::make_pair(it1->second->GetBinContent(i)/it2->second->GetBinContent(i),
						   (it1->second->GetBinContent(i)/it2->second->GetBinContent(i))*
						   sqrt((it1->second->GetBinError(i))*(it1->second->GetBinError(i))/(it1->second->GetBinContent(i)*it1->second->GetBinContent(i)) +
							(it2->second->GetBinError(i))*(it2->second->GetBinError(i))/(it2->second->GetBinContent(i)*it2->second->GetBinContent(i))
							)));
	      std::cout << tempPR+","+tempMode << ": (" << it1->first << "/" << it2->first << ") = " 
			<< it1->second->GetBinContent(i)/it2->second->GetBinContent(i)
			<< " +/- "
			<< (it1->second->GetBinContent(i)/it2->second->GetBinContent(i))*
		sqrt((it1->second->GetBinError(i))*(it1->second->GetBinError(i))/(it1->second->GetBinContent(i)*it1->second->GetBinContent(i)) +
		     (it2->second->GetBinError(i))*(it2->second->GetBinError(i))/(it2->second->GetBinContent(i)*it2->second->GetBinContent(i))
		     )
			<< std::endl;  
	    }
	  studyCompatibility(fac_Year);
	}
  studyCompatibility(fac_Years);
  return 0;
}

