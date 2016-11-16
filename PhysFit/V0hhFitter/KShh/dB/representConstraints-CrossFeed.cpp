#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

//ROOT
#include "TChain.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
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

int main(int argc, char* argv[])
{
  unsigned int nCol(13);
  std::string name("");
  bool divSig(false);
  boost::program_options::options_description decisions("Option Arguments");
  decisions.add_options()
    ("help,h" , "produce help message")
    ("name,n"    , boost::program_options::value<std::string>(&name),"")
    ("nCol,c"    , boost::program_options::value<unsigned int>(&nCol),"nCol: 7 for EffSel, 9 for EffSelNGen, 11 for PID, 13 for TOTAL")
    ("divSig,d"    , boost::program_options::value<bool>(&divSig),"")
    ;
  
  boost::program_options::variables_map vm;
  boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
  boost::program_options::notify( vm );

  if (nCol == 13 && !vm.count("divSig"))
    {
      std::cout << "INFO: Default divSig behaviour for TOTAL argument is true. Setting it to true then." << std::endl;
      divSig = true;
    }
  
  //Firstly count the categories and else...
  std::string fileName("constraints-DataFit-Vanilla");
  
  std::vector<std::pair<std::string,std::string> > crossFeeds;
  crossFeeds.push_back(std::make_pair("pipi","Bs2KSKpi"));
  crossFeeds.push_back(std::make_pair("KK","Bs2KSKpi"));
  crossFeeds.push_back(std::make_pair("Kpi","Bd2KSKK"));
  crossFeeds.push_back(std::make_pair("Kpi","Bd2KSpipi"));
  
  unsigned int n = 2*crossFeeds.size();
  std::cout << n << std::endl;
  std::map<std::string,TH1F*> histos;
  unsigned int iHisto = 1;
  for (std::vector<std::pair<std::string,std::string> >::iterator it = crossFeeds.begin() ; it != crossFeeds.end() ; ++it)
    {
      histos[it->second+"_as_"+it->first] = new TH1F(("h_"+it->second+"_as_"+it->first).c_str(),(it->second+" as "+it->first).c_str(),6,0,6);
      histos[it->second+"_as_"+it->first]->SetMarkerColor(iHisto);
      histos[it->second+"_as_"+it->first]->SetLineColor(iHisto);
      ++iHisto;
    }
  
  // Create the gaussian constraints (import from DB) 
  TString dir         = getenv("V0HHFITTERROOT");
  std::string V0hhDir = dir.Data();
  std::string dbTable_pr = V0hhDir+"/KShh/dB/efficiencyTable.db";
  sqlite3 *db_pr;
  int rc_pr = sqlite3_open(dbTable_pr.c_str(), &db_pr);
  if (rc_pr) {
    std::fprintf(stderr, "Can't open efficiencies database: %s\n", sqlite3_errmsg(db_pr));
    exit(0);
  } else {
    fprintf(stderr, "Opened efficiency database successfully\n");
  }
  unsigned int i = 1;
  std::vector<std::string> KScat;
  KScat.push_back("DD");
  KScat.push_back("LL");
  std::vector<std::string> years;
  years.push_back("2011");
  years.push_back("2012a");
  years.push_back("2012b");
  std::pair<int,int> cols = std::make_pair(nCol,nCol+1);
  double minVal(100),maxVal(0),maxErr(0);
  std::string selType("Loose");
  selType = "DP1";
  for (std::vector<std::string>::iterator itYear = years.begin() ; itYear != years.end() ; ++itYear)
    for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)    
      {
	for (std::vector<std::pair<std::string,std::string> >::iterator it = crossFeeds.begin() ; it != crossFeeds.end() ; ++it)
	  {
	    //Retrieving signal
	    sqlite3_stmt* stmt_sig   = NULL;
	    Double_t Eff_Sel_sig(0.), Err_Sel_sig(0.);
	    const char *sqlSig;
	    TString dbLinkSig   = "";
	    int retval;
	    std::string sig_eff_str(""), sig_err_str("");

	    if (((it->first) == "Kpi") || ((it->first) == "piK"))
	      dbLinkSig = "SELECTION LIKE '"+selType+"' AND MODE LIKE 'Bs2KS"+(it->first)+"' AND KSTYPE LIKE '"+(*itKS)+"' AND YEAR LIKE '"+(*itYear)+"' AND TREENAME LIKE '"+(it->first)+"'";
	    else
	      dbLinkSig = "SELECTION LIKE '"+selType+"' AND MODE LIKE 'Bd2KS"+(it->first)+"' AND KSTYPE LIKE '"+(*itKS)+"' AND YEAR LIKE '"+(*itYear)+"' AND TREENAME LIKE '"+(it->first)+"'";
	    TString aux = "SELECT * from EFFICIENCY WHERE "+dbLinkSig;
	    sqlSig = aux.Data();
	    retval = sqlite3_prepare_v2(db_pr, sqlSig, -1, &stmt_sig, 0);
	    if (retval){
	      printf("Selecting data from DB Failed (err_code=%d)\n", retval);
	      return 0;
	    }
	    while(1) {
	      retval = sqlite3_step(stmt_sig);
	      if (retval == SQLITE_ROW) {
		// Selection and Generation efficiency
		const unsigned char* sig_effLink = sqlite3_column_text(stmt_sig, 9);
		std::stringstream sig_eff_tmp_str;
		sig_eff_tmp_str << sig_effLink;
		sig_eff_str = (sig_eff_tmp_str).str();
		Eff_Sel_sig = atof((sig_eff_str).c_str()); 
		// Selection and Generation efficiency error
		const unsigned char* sig_errLink = sqlite3_column_text(stmt_sig, 10);
		std::stringstream sig_err_tmp_str;
		sig_err_tmp_str << sig_errLink;
		sig_err_str = (sig_err_tmp_str).str();
		Err_Sel_sig = atof((sig_err_str).c_str()); 
		break;
	      } else if(retval == SQLITE_DONE) { 
		break;
	      }
	    }
	    const char *sqlRatio_pr;
	    std::string frac_bkg_str(""), frac_bkg_err_str("");
	    Double_t Fraction_bkg_val(0.), Fraction_err_bkg_val(0.);
	    sqlite3_stmt* stmt_pr   = NULL;
	    int retval_pr;
	    TString dbLinkPR  = "SELECTION LIKE 'LOOSE' AND MODE LIKE '"+it->second+"' AND TREENAME LIKE '"+(it->first)+"' AND KSTYPE LIKE '"+(*itKS)+"' AND YEAR LIKE '"+(*itYear)+"'";
	    
	    // Retrive the estimation of the fraction information 
	    TString info_pr = "SELECT * from EFFICIENCY WHERE "+dbLinkPR;
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
		const unsigned char* frac_bkgLink    = sqlite3_column_text(stmt_pr, cols.first);
		std::stringstream frac_bkg_tmp_str;
		frac_bkg_tmp_str << frac_bkgLink;
		frac_bkg_str = (frac_bkg_tmp_str).str();
		Fraction_bkg_val = atof((frac_bkg_str).c_str()); 
		// Fraction mean error value for each bkg 
		//		const unsigned char* frac_bkgErrLink = sqlite3_column_text(stmt_pr, 15);
		const unsigned char* frac_bkgErrLink = sqlite3_column_text(stmt_pr, cols.second);
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
	    if (divSig)
	      {
		double tempVal = Fraction_bkg_val/Eff_Sel_sig;
		double tempRelFrac = Fraction_err_bkg_val/Fraction_bkg_val;
		double tempRelSig  = Err_Sel_sig/Eff_Sel_sig;
		double tempErr  = tempVal*sqrt(tempRelFrac*tempRelFrac + tempRelSig*tempRelSig);
		std::cout << "INFO: Dividing the frac by the signal eff. (" << Fraction_bkg_val << " +/- " << Fraction_err_bkg_val << ") -> " << tempVal << " +/- " << tempErr << std::endl;
		Fraction_bkg_val = tempVal;
		Fraction_err_bkg_val = tempErr;
	      }
	    histos[it->second+"_as_"+it->first]->SetBinContent(i,Fraction_bkg_val);
	    histos[it->second+"_as_"+it->first]->SetBinError(i,Fraction_err_bkg_val);
	    histos[it->second+"_as_"+it->first]->GetXaxis()->SetBinLabel(i,(*itYear+","+*itKS).c_str());
	    if (Fraction_bkg_val> maxVal)
	      maxVal = Fraction_bkg_val;
	    if (Fraction_bkg_val < minVal)
	      minVal = Fraction_bkg_val;
	    if (Fraction_err_bkg_val > maxErr)
	      maxErr = Fraction_err_bkg_val;
	    Fraction_bkg_val = 0;
	    Fraction_err_bkg_val = 0;	
	  }
	++i;
      }
  TCanvas *C = new TCanvas("C","C",1800,1000);
  gStyle->SetOptStat(0);
  gPad->SetLogy();
  bool first(true);
  unsigned int compteur(1);
  for (std::map<std::string,TH1F*>::iterator it = histos.begin() ; it != histos.end() ; ++it)
    it->second->GetYaxis()->SetRangeUser(minVal-maxErr,maxVal+maxErr);
  for (std::map<std::string,TH1F*>::iterator it = histos.begin() ; it != histos.end() ; ++it)
    {
      if (i==1)	
	it->second->Draw("E");
      else
	it->second->Draw("E""same");      
      std::cout << compteur << " " << it->second->GetLineColor() << std::endl;
      compteur++;
      
    }
  //Create a TLegend
  TLegend* legend = new TLegend(0.80,0.80,1.,1.);
  for (std::map<std::string,TH1F*>::iterator it = histos.begin() ; it != histos.end() ; ++it)
    legend->AddEntry(it->second);
  legend->Draw();
  if (name == "")
    C->SaveAs("CrossFeeds-Constraints.png");
  else
    C->SaveAs(("CrossFeeds-Constraints-"+name+".png").c_str());
  //Finding FACTORS!
  //DD-LL factor.
  std::vector<std::pair<double,double> > fac_DDLL;
  for (std::map<std::string,TH1F*>::iterator it = histos.begin() ; it != histos.end() ; ++it)
    {   
      std::vector<std::pair<double,double> > fac_DDLL_CF;  
      for (unsigned int i = 1 ; i <= 6 ;i+=2)
	{	
	  std::pair<double,double> factor = std::make_pair(it->second->GetBinContent(i+1)/it->second->GetBinContent(i),
							   (it->second->GetBinContent(i+1)/it->second->GetBinContent(i))*
							   sqrt((it->second->GetBinError(i)  )*(it->second->GetBinError(i)  )/(it->second->GetBinContent(i  )*it->second->GetBinContent(i)  ) 
								+(it->second->GetBinError(i+1))*(it->second->GetBinError(i+1))/(it->second->GetBinContent(i+1)*it->second->GetBinContent(i+1))));
	  std::cout << it->first << ": (LL/DD) = "
		    << factor.first
		    << " +/- "
		    << factor.second
		    << std::endl;  
	  fac_DDLL.push_back(factor);
	  fac_DDLL_CF.push_back(factor);
	}
      studyCompatibility(fac_DDLL_CF);
      std::cout << std::endl;
    }
  studyCompatibility(fac_DDLL);
  //Years factors 
  std::cout << "Years factors: "<< std::endl;
  std::vector<std::pair<double,double> > fac_2012a;
  std::vector<std::pair<double,double> > fac_2012b;
  std::vector<std::pair<double,double> > fac_2012;
  for (std::map<std::string,TH1F*>::iterator it = histos.begin() ; it != histos.end() ; ++it)
    {
      std::vector<std::pair<double,double> > fac_2012a_CF;
      std::vector<std::pair<double,double> > fac_2012b_CF;
      for (unsigned int i = 1 ; i <= 2 ;i++)
	{
	  std::string KSmode = (i==1)?"DD":"LL";
	  std::pair<double,double> factor_2012a =
	    std::make_pair(it->second->GetBinContent(i)/it->second->GetBinContent(i+2),
			   (it->second->GetBinContent(i)/it->second->GetBinContent(i+2))*
			   sqrt((it->second->GetBinError(i)  )*(it->second->GetBinError(i)  )/(it->second->GetBinContent(i  )*it->second->GetBinContent(i)  ) +
				(it->second->GetBinError(i+2))*(it->second->GetBinError(i+2))/(it->second->GetBinContent(i+2)*it->second->GetBinContent(i+2))
				)
			   );
	  std::pair<double,double> factor_2012b =
	    std::make_pair(it->second->GetBinContent(i)/it->second->GetBinContent(i+4),
			   (it->second->GetBinContent(i)/it->second->GetBinContent(i+4))*
			   sqrt((it->second->GetBinError(i)  )*(it->second->GetBinError(i)  )/(it->second->GetBinContent(i  )*it->second->GetBinContent(i)  ) +
				(it->second->GetBinError(i+4))*(it->second->GetBinError(i+4))/(it->second->GetBinContent(i+4)*it->second->GetBinContent(i+4))
				)
			   );
	  
	std::cout << it->first << "(" << KSmode <<"): (2011/2012a) = "
		  << factor_2012a.first
		  << " +/- "
		  << factor_2012a.second
		  << std::endl;  
	std::cout << it->first << "(" << KSmode <<"): (2011/2012b) = "
		  << factor_2012b.first
		  << " +/- "
		  << factor_2012b.second
		  << std::endl;  
	fac_2012a.push_back(factor_2012a);
	fac_2012b.push_back(factor_2012b);
	fac_2012 .push_back(factor_2012a);
	fac_2012 .push_back(factor_2012b);
	fac_2012a_CF.push_back(factor_2012a);
	fac_2012b_CF.push_back(factor_2012b);
	}
      studyCompatibility(fac_2012a_CF);
      studyCompatibility(fac_2012b_CF);
      std::cout << std::endl;
    }
  std::cout << "2011/2012a factors:" << std::endl;
  studyCompatibility(fac_2012a);
  std::cout << "2011/2012b factors:" << std::endl;
  studyCompatibility(fac_2012b);
  std::cout << "2011/2012 factors:" << std::endl;
  studyCompatibility(fac_2012);
  //Inter-CF factors.
  std::cout << "Factors between crossfeeds: " << std::endl;
  for (std::map<std::string,TH1F*>::iterator it1 = histos.begin() ; it1 != histos.end() ; ++it1)
    for (std::map<std::string,TH1F*>::iterator it2 = it1; it2 != histos.end() ; ++it2)
      if (it2->first != it1->first)
	{
	  std::vector<std::pair<double,double> > fac_CF;
	  for (unsigned int i = 1 ; i <= 6 ; i++)
	    {
	      std::string tempYear = (i==1 || i==2)? "2011":((i==3 ||i==4 )? "2012a":"2012b");
	      std::string tempMode = (i%2)? "LL":"DD";
	      fac_CF.push_back(std::make_pair(it1->second->GetBinContent(i)/it2->second->GetBinContent(i),
					      (it1->second->GetBinContent(i)/it2->second->GetBinContent(i))*
					      sqrt((it1->second->GetBinError(i))*(it1->second->GetBinError(i))/(it1->second->GetBinContent(i)*it1->second->GetBinContent(i)) +
						   (it2->second->GetBinError(i))*(it2->second->GetBinError(i))/(it2->second->GetBinContent(i)*it2->second->GetBinContent(i))
						   )));
	      std::cout << tempYear+","+tempMode << ": (" << it1->first << "/" << it2->first << ") = " 
			<< it1->second->GetBinContent(i)/it2->second->GetBinContent(i)
			<< " +/- "
			<< (it1->second->GetBinContent(i)/it2->second->GetBinContent(i))*
		sqrt((it1->second->GetBinError(i))*(it1->second->GetBinError(i))/(it1->second->GetBinContent(i)*it1->second->GetBinContent(i)) +
		     (it2->second->GetBinError(i))*(it2->second->GetBinError(i))/(it2->second->GetBinContent(i)*it2->second->GetBinContent(i))
		     )
			<< std::endl;  
	    }
	  studyCompatibility(fac_CF);
	}
  return 0;
}

