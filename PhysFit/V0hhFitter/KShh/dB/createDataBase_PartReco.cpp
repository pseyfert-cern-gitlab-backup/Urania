#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "TMath.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

std::vector<Double_t> divError(Double_t val1, Double_t err1, Double_t val2, Double_t err2){  
  std::vector<Double_t> div_res;  
  Double_t div(0.), sig1_sq(0.), sig2_sq(0.), sig_div(0.);
  
  div     = val1/val2;
  sig1_sq = (err1/val1)*(err1/val1); 
  sig2_sq = (err2/val2)*(err2/val2); 
  sig_div = div*sqrt(sig1_sq+sig2_sq);
  
  div_res.push_back(div);
  div_res.push_back(sig_div);
  
  return div_res;
}

std::vector<Double_t> multError(Double_t val1, Double_t err1, Double_t val2, Double_t err2){
   std::vector<Double_t> mult_res;

   Double_t mult(0.), sig1_sq(0.), sig2_sq(0.), sig_mult(0.);
   
   mult     = val1*val2;
   sig1_sq  = (err1/val1)*(err1/val1); 
   sig2_sq  = (err2/val2)*(err2/val2); 
   sig_mult = mult*sqrt(sig1_sq+sig2_sq);

   mult_res.push_back(mult);
   mult_res.push_back(sig_mult);

   return mult_res;
}

std::pair<double,double> average(std::vector<std::pair<double, double> > values)
{
  double value(0), errTemp(0);
  unsigned int nVals(0);
  for (std::vector<std::pair<double,double> > ::iterator it = values.begin() ; it != values.end() ; ++it)
    {
      nVals++;
      value += it->first;
      errTemp += it->second*it->second;      
    }
  value /= nVals;
  double err = TMath::Sqrt(errTemp)/nVals;
  return std::make_pair(value,err);
}

void usage( std::ostream& out, const TString& progName )
{
   out<<"Usage:\n";
   out<<progName<<" [ID] [Sel] [Bkg] [treeName] [KS_type] [Year] {BF}\n";
}

int main(int argc, char* argv[])
{
	if ( argc < 6 ) { 
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}   
	
   TString ID       = argv[1];
   TString Sel      = argv[2];
   TString BkgName  = argv[3];
   TString treeName = argv[4];
   TString KS_type  = argv[5];
   TString Year     = argv[6];
   bool BF = false;
   if (argc > 7)
   	   BF = (std::string(argv[7]) == "BF");
   std::cout << "Parameters: " << ID << " " << Sel << " " << BkgName << " " << treeName << " " << KS_type << " " << Year << std::endl;
   if (BF)
	   std::cout << "Seventh argument is 'BF'. Returning the table without part. reco. bkg BFs" << std::endl;
   
   TString Mode = "";
   if (treeName == "pipi") {
	   Mode = "Bd2KSpipi";
   } else if (treeName == "KK"){
	   Mode = "Bd2KSKK";
   } else if ((treeName == "Kpi") || (treeName == "piK")){
	   Mode = "Bs2KSKpi";
   } else {
	   std::cout << "ERROR: Wrong configuration" << std::endl;
     exit(0);
   }

   std::map<TString,TString> canonicalTree;
   canonicalTree["Bd2etapKS02pipigamma"  ] = "pipi";
   canonicalTree["Bd2pipiKS0gamma"       ] = "pipi";
   canonicalTree["Bd2Kst0rho02KS0pi0pipi"] = "pipi";
   canonicalTree["Bu2D0pi2KS0pipi"       ] = "pipi";
   canonicalTree["Bs2KstKst2KS0piKpi0"   ] = "Kpi";
   canonicalTree["Bu2D0K2KS0pipi"        ] = "Kpi";
   canonicalTree["Bd2Kst0phi2KS0pi0KK"   ] = "KK";
   canonicalTree["Bd2etacKS2KKpi0"       ] = "KK";
   
   // Global variables
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   bool isCat = (canonicalTree[BkgName] == "");
   if (isCat)
     std::cout << "WARNING: This is a category: " << BkgName << "." << std::endl;

   //Defining categories
   TString CatName("");
   if (isCat)
     CatName = BkgName(0,BkgName.First("-"));
   std::map<TString,std::vector<TString> > categories;
   categories["Charmless"].push_back("Bd2Kst0phi2KS0pi0KK");
   categories["Charmless"].push_back("Bd2Kst0rho02KS0pi0pipi");
   categories["Charmless"].push_back("Bs2KstKst2KS0piKpi0");
   categories["Charmed"].push_back("Bu2D0pi2KS0pipi");
   categories["Charmed"].push_back("Bu2D0K2KS0pipi");
   categories["Charmonia"].push_back("Bd2etacKS2KKpi0");
   categories["MissGamNR"].push_back("Bd2pipiKS0gamma");
   categories["MissGamRes"].push_back("Bd2pipiKS0gamma");

   ///////////////////////////
   //     Open database     //
   ///////////////////////////
   TString currentDir = getenv("V0HHFITTERROOT");
   std::string dirConversion = (currentDir).Data();
   std::string fileTable = (BF)?dirConversion+"/KShh/dB/partiallyRecoYielTable-BF.db":dirConversion+"/KShh/dB/partiallyRecoYielTable.db";
   rc = sqlite3_open(fileTable.c_str(), &db);
   if (rc) {
	   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	   exit(0);
   } else {
	   fprintf(stdout, "Opened database successfully\n");
   }
   
   ////////////////////////////
   //  Efficiency dictionary //
   ////////////////////////////

   Double_t BR_sig(0.), BR_sig_Err(0.); 

   std::map<TString,std::pair<double,double> > BRs;
   BRs["pipi"] = std::make_pair(3.25 * 1e-5,0.40  * 1e-5);
   BRs["Kpi"]  = std::make_pair(4.85 * 1e-5,0.85  * 1e-5);
   BRs["piK"]  = std::make_pair(4.85 * 1e-5,0.85  * 1e-5);
   BRs["KK"]   = std::make_pair(1.31 * 1e-5,0.07  * 1e-5);
   BRs["Bd2etapKS02pipigamma"]   = std::make_pair(3.3*1e-5,0.2*1e-5);
   BRs["Bd2pipiKS0gamma"]        = std::make_pair(1.95*1e-5,0.22*1e-5);
   BRs["Bd2Kst0rho02KS0pi0pipi"] = std::make_pair(2.55*1e-5,0.23*1e-5);
   BRs["Bu2D0pi2KS0pipi"]        = std::make_pair(30.9*1e-5,1.35*1e-5);
   BRs["Bs2KstKst2KS0piKpi0"]    = std::make_pair(0.53*1e-5,0.08*1e-5);
   BRs["Bu2D0K2KS0pipi"]         = std::make_pair(1.50*1e-5,0.36*1e-5);
   BRs["Bd2etacKS2KKpi0"]        = std::make_pair(1.43*1e-5,0.15*1e-5);
   
   // Generated efficiency Signal
   Double_t Acc_eff(0.);
   std::map<TString,double> Acc_effs;
   Acc_effs["pipi-2011"]  = 0.1970;
   Acc_effs["pipi-2012a"] = 0.2066;
   Acc_effs["pipi-2012b"] = 0.2066;
   Acc_effs["Kpi-2011"]   = 0.2023;
   Acc_effs["Kpi-2012a"]  = 0.2113;
   Acc_effs["Kpi-2012b"]  = 0.2113;
   Acc_effs["piK-2011"]   = 0.2023;
   Acc_effs["piK-2012a"]  = 0.2113;
   Acc_effs["piK-2012b"]  = 0.2113;
   Acc_effs["KK-2011"]    = 0.2075;
   Acc_effs["KK-2012a"]   = 0.2169;
   Acc_effs["KK-2012b"]   = 0.2169;
   Acc_eff = Acc_effs[treeName+"-"+Year];
   
   // Generator efficiency Bkg 
   Double_t Acc_Bkg_eff(0.), Acc_Bkg_err(0.);
   std::map<TString,std::pair<double,double> > Acc_Bkg;
   Acc_Bkg["Bd2etapKS02pipigamma"] = std::make_pair(0.2374,0.002572);
   Acc_Bkg["Bd2pipiKS0gamma"] = std::make_pair(0.2023,0.001100);
   Acc_Bkg["Bd2Kst0rho02KS0pi0pipi"] = std::make_pair(0.1677,0.000641);
   Acc_Bkg["Bu2D0pi2KS0pipi"] = std::make_pair(0.1639,0.000293);
   Acc_Bkg["Bs2KstKst2KS0piKpi0"] = std::make_pair(0.1757,0.000497);
   Acc_Bkg["Bu2D0K2KS0pipi"] = std::make_pair(0.1663,0.000215);
   Acc_Bkg["Bd2Kst0phi2KS0pi0KK"] = std::make_pair(0.1844,0.000765);
   Acc_Bkg["Bd2etacKS2KKpi0"] = std::make_pair(0.18158,0.00063);
   if (!isCat)
     {
       Acc_Bkg_eff = Acc_Bkg[BkgName].first;
       Acc_Bkg_err = Acc_Bkg[BkgName].second;
     }
   else
     {
       std::vector<std::pair<double,double> > acceptancies;
       for (std::vector<TString>::iterator it = categories[CatName].begin() ; it != categories[CatName].end() ; ++it)
	 acceptancies.push_back(Acc_Bkg[*it]);
       Acc_Bkg_eff = average(acceptancies).first;
       Acc_Bkg_err = average(acceptancies).second;
     }
   Double_t Sel_bkg_den(0.); // Extra info
   std::map<TString,double> Sel_bkg_dens;
   Sel_bkg_dens["Bd2etapKS02pipigamma"  ] = 2010745;
   Sel_bkg_dens["Bd2pipiKS0gamma"       ] = 2031499;
   Sel_bkg_dens["Bd2Kst0rho02KS0pi0pipi"] = 2022996;
   Sel_bkg_dens["Bu2D0pi2KS0pipi"       ] = 2033698;
   Sel_bkg_dens["Bs2KstKst2KS0piKpi0"   ] = 2045495;
   Sel_bkg_dens["Bu2D0K2KS0pipi"        ] = 2046609;
   Sel_bkg_dens["Bd2Kst0phi2KS0pi0KK"   ] = 1961995;
   Sel_bkg_dens["Bd2etacKS2KKpi0"       ] = 2049247;
   Sel_bkg_den = Sel_bkg_dens[BkgName];
   Double_t BR_bkg(0.), BR_bkg_Err(0.); 
   Bool_t Frag_flag = kFALSE;
   if (BkgName == "Bu2D0pi2KS0pipi" || BkgName.Contains("Charmed"))
     Frag_flag   = kTRUE;
   
   BR_sig     = BRs[treeName].first;
   BR_sig_Err = BRs[treeName].second;
   
   std::map<TString,std::pair<double,double> > BR_Vals;
   
   BR_Vals["Charmless-Bd-pipi"] = std::make_pair(2.55,0.23 );
   BR_Vals["Charmless-Bd-Kpi" ] = std::make_pair(0.04,0.01);
   BR_Vals["Charmless-Bd-KK"  ] = std::make_pair(2.56,0.21);
   BR_Vals["Charmless-Bs-pipi"] = std::make_pair(0.001,0.01); //WARNING
   BR_Vals["Charmless-Bs-Kpi" ] = std::make_pair(0.53,0.08);
   BR_Vals["Charmless-Bs-KK"  ] = std::make_pair(0.001,0.01);//WARNING

   BR_Vals["Charmed-Bd-pipi"] = std::make_pair(30.90,1.35);
   BR_Vals["Charmed-Bd-Kpi" ] = std::make_pair(2.42,0.42);
   BR_Vals["Charmed-Bd-KK"  ] = std::make_pair(0.32,0.14);
   BR_Vals["Charmed-Bs-pipi"] = std::make_pair(1.6,0.35);
   BR_Vals["Charmed-Bs-Kpi" ] = std::make_pair(1.50,0.36);
   BR_Vals["Charmed-Bs-KK"  ] = std::make_pair(0.26,0.08);
   
   BR_Vals["Charmonia-Bd-pipi"] = std::make_pair(0.91,0.06);
   BR_Vals["Charmonia-Bd-Kpi" ] = std::make_pair(0.002,0.0003);
   BR_Vals["Charmonia-Bd-KK"  ] = std::make_pair(1.43,0.15);
   BR_Vals["Charmonia-Bs-pipi"] = std::make_pair(0.04,0.01);
   BR_Vals["Charmonia-Bs-Kpi" ] = std::make_pair(0.001,0.01); //WARNING
   BR_Vals["Charmonia-Bs-KK"  ] = std::make_pair(0.02,0.01);
   
   BR_Vals["MissGamNR-Bd-pipi"] = std::make_pair(1.95,0.22);
   BR_Vals["MissGamNR-Bd-Kpi" ] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamNR-Bd-KK"  ] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamNR-Bs-pipi"] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamNR-Bs-Kpi" ] = std::make_pair(0.001,0.01);//WARNING
   BR_Vals["MissGamNR-Bs-KK"  ] = std::make_pair(0.001,0.01);

   BR_Vals["MissGamRes-Bd-pipi"] = std::make_pair(3.3,0.2);
   BR_Vals["MissGamRes-Bd-Kpi" ] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamRes-Bd-KK"  ] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamRes-Bs-pipi"] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamRes-Bs-Kpi" ] = std::make_pair(0.001,0.01);
   BR_Vals["MissGamRes-Bs-KK"  ] = std::make_pair(0.001,0.01);
   
   if (isCat)
	   {
		   TString tempTreeName(treeName);
		   if (treeName == "piK")
			   tempTreeName = "Kpi";
		   BR_bkg     = BR_Vals[BkgName+"-"+tempTreeName].first  * 1e-5;
		   BR_bkg_Err = BR_Vals[BkgName+"-"+tempTreeName].second * 1e-5;
	   }
   else
	   {
		   BR_bkg = BRs[BkgName].first;
		   BR_bkg_Err = BRs[BkgName].second;
	   }
   if (BF)
	   {
		   std::cout << "WARNING: The BRs have been set to one!" << std::endl;
		   BR_bkg = 1.;
		   BR_bkg_Err = 0.;
	   }
   // Selection efficiency
   TString baseDir = getenv("V0HHFITTERDATA");
   //   TString baseDir = "root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/";
   
   //*********************************//
   //    Signal selection efficiency  //
   //*********************************//
   Double_t Sel_sig_num(0.), Sel_sig_den(0.), Sel_sig_eff(0.);
   Double_t Err_sig_num(0.), Err_sig_den(0.), Sel_sig_err(0.);
   
   //   TFile *Sig_eff = TFile::Open(baseDir + "/KShhFit/MonteCarlo/"+Year+"/SingleCand/"+Sel+"/"+Mode+"/"+Mode+"-MC-"+Year+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root");
   TFile *Sig_eff = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/SingleCand/"+Sel+"/"+Mode+"/"+Mode+"-MC-"+Year+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root");
   TTree* t_Eff   = 0;
   if (treeName == "piK"){
     t_Eff = dynamic_cast<TTree*>( Sig_eff->Get("B2KShh"+KS_type+"/B2KpiKS"));
   } else {
     t_Eff = dynamic_cast<TTree*>( Sig_eff->Get("B2KShh"+KS_type+"/B2"+treeName+"KS"));
   }
   Sel_sig_num    = t_Eff->GetEntries();
   Err_sig_num    = sqrt(Sel_sig_num); 
   
   // Signal denominator
   TString genYear ="";
   if ((Year == "2012a") || (Year == "2012b")){ genYear = "2012"; }
   else { genYear = "2011"; }
   std::cout << baseDir + "/KShh/MonteCarlo/"+Year+"/Gen/"+Mode+"/"+Mode+"-MC-"+genYear+"-MagAll.root" << std::endl;
   TFile *Sig_eff_den = NULL;
   if (Mode == "Bd2KSpipi" || Mode == "Bs2KSKpi" || Mode == "Bs2KSpiK")
	   Sig_eff_den = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/Gen/"+Mode+"/"+Mode+"-MC-"+genYear+"-MagAll-Reco.root");
   else
	   Sig_eff_den = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/Gen/"+Mode+"/"+Mode+"-MC-"+genYear+"-MagAll.root");
   TTree* t_Eff_den   = dynamic_cast<TTree*>( Sig_eff_den->Get("tupleMCTruth"));
   Sel_sig_den        = t_Eff_den->GetEntries();
   Err_sig_den        = sqrt(Sel_sig_den); 
   std::cout << "0: " << std::endl;
   // Total Selection efficiency 
   Sel_sig_eff = Sel_sig_num/Sel_sig_den;
   // Selection efficiency error
   Double_t sig_1_sq   = (Err_sig_num/Sel_sig_num)*(Err_sig_num/Sel_sig_num);
   Double_t sig_2_sq   = (Err_sig_den/Sel_sig_den)*(Err_sig_den/Sel_sig_den);
   Sel_sig_err         = Sel_sig_eff*(sqrt(sig_1_sq + sig_2_sq));

   // Calcultae Selection efficiency X Generated one 
   Double_t SelNGen_sig_Eff(0.), SelNGen_sig_Err(0.);
   SelNGen_sig_Eff = Sel_sig_eff*Acc_eff;
   TString EffSelNGenInfo = "";
   std::cout << std::fixed << std::showpoint;
   std::setprecision(10);
   EffSelNGenInfo.Form("%e",SelNGen_sig_Eff);
   Double_t rel_Eff_Sel = Sel_sig_err/Sel_sig_eff;
   SelNGen_sig_Err = SelNGen_sig_Eff*rel_Eff_Sel;
   TString ErrSelNGenInfo = "";
   ErrSelNGenInfo.Form("%e",SelNGen_sig_Err);
   
   // Close files
   Sig_eff->Close();
   Sig_eff_den->Close();
                                       
   //*********************************//
   // Background selection efficiency //
   //*********************************//
   Double_t Sel_bkg_num(0.), Sel_bkg_eff(0.);
   Double_t Err_bkg_num(0.), Err_bkg_den(0.), Sel_bkg_err(0.);
   
   TString BkgTreeName(BkgName);
   if (!isCat)
     {
       TFile *Bkg_eff   = TFile::Open(baseDir + "/KShh/MonteCarlo/2011/SingleCand/"+Sel+"/"+BkgTreeName+"/"+BkgTreeName+"-MC-2011-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root");
       TTree* t_bkg_Eff = dynamic_cast<TTree*>( Bkg_eff->Get("B2KShh"+KS_type+"/B2"+canonicalTree[BkgName]+"KS"));
       Sel_bkg_num    = t_bkg_Eff->GetEntries();
       Err_bkg_num    = sqrt(Sel_bkg_num); 
       // Close files
       Bkg_eff->Close();
       // Dividing from the previous retrieved yield
       Err_bkg_den = sqrt(Sel_bkg_den); 
       // Total Selection bkg efficiency 
       Sel_bkg_eff = Sel_bkg_num/Sel_bkg_den;
       
       // Selection efficiency error
       Double_t sig_bkg_1_sq   = (Err_bkg_num/Sel_bkg_num)*(Err_bkg_num/Sel_bkg_num);
       Double_t sig_bkg_2_sq   = (Err_bkg_den/Sel_bkg_den)*(Err_bkg_den/Sel_bkg_den);
       Sel_bkg_err             = Sel_bkg_eff*(sqrt(sig_bkg_1_sq + sig_bkg_2_sq));       
     }
   else
     {
       TFile *Bkg_eff = NULL;
       TTree* t_bkg_Eff = NULL;
       std::vector<std::pair<double,double> > sel_bkg_vals;
       double num(0),den(1);
       for (std::vector<TString>::iterator it = categories[CatName].begin() ; it != categories[CatName].end() ; ++it)
	 {
	   Bkg_eff = TFile::Open(baseDir + "/KShh/MonteCarlo/2011/SingleCand/"+Sel+"/"+(*it)+"/"+(*it)+"-MC-2011-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root");
	   t_bkg_Eff = dynamic_cast<TTree*>( Bkg_eff->Get("B2KShh"+KS_type+"/B2"+canonicalTree[(*it)]+"KS"));
	   num = t_bkg_Eff->GetEntries();
	   den = Sel_bkg_dens[(*it)];  
	   std::cout << *it << " " << num << " " << den << std::endl;
	   sel_bkg_vals.push_back(std::make_pair(divError(num,sqrt(num),den,sqrt(den))[0],
						 divError(num,sqrt(num),den,sqrt(den))[1]));
	 }
       //       Sel_bkg_eff = average(sel_bkg_vals).first;
       //       Sel_bkg_err = average(sel_bkg_vals).second;
       Sel_bkg_eff = sel_bkg_vals[0].first;
       Sel_bkg_err = sel_bkg_vals[0].second;
     }
   std::cout << "1: " << Err_bkg_den << std::endl;
   
   // Calculate Selection efficiency X Generated one 
   Double_t SelNGen_bkg_Eff(0.), SelNGen_bkg_Err(0.);
   SelNGen_bkg_Eff = Sel_bkg_eff*Acc_Bkg_eff;
   std::cout << std::fixed << std::showpoint;
   std::setprecision(10);
   TString EffSelNGenInfo_bkg = "";
   EffSelNGenInfo_bkg.Form("%e",SelNGen_bkg_Eff);
   Double_t rel_Eff_Sel_bkg = Sel_bkg_err/Sel_bkg_eff;
   SelNGen_bkg_Err = SelNGen_bkg_Eff*rel_Eff_Sel_bkg;
   TString ErrSelNGenInfo_bkg = "";
   ErrSelNGenInfo_bkg.Form("%e",SelNGen_bkg_Err);                                       
   
   // ****************************** //
   //   Calculating mean and error   //
   // ****************************** //
   
   // Efficiency ratio
   std::vector<Double_t> ratio_Eff;
   ratio_Eff = divError(SelNGen_bkg_Eff, SelNGen_bkg_Err, SelNGen_sig_Eff, SelNGen_sig_Err);
   std::cout << SelNGen_bkg_Eff << " " << SelNGen_bkg_Err << " " << SelNGen_sig_Eff << " " << SelNGen_sig_Err << std::endl; //LHENRY
   std::cout << "ratio_Eff " << ratio_Eff[0] << " +/- " << ratio_Eff[1] << std::endl; //LHENRY
   // Multiplication of Eff X fragmentation
   std::vector<Double_t> factor_Eff_Frag;
   Double_t ratio_Frag     = 3.90625;
   Double_t ratio_Frag_err = 0.30518; 
   if (Frag_flag){
     factor_Eff_Frag = multError(ratio_Eff[0], ratio_Eff[1], ratio_Frag, ratio_Frag_err); 
   } else {
     factor_Eff_Frag.push_back(ratio_Eff[0]);
     factor_Eff_Frag.push_back(ratio_Eff[1]);
   }

   // ****************************** //
   //          Eff ratios            //
   // ****************************** //
   std::cout << std::fixed << std::showpoint;
   std::setprecision(10);
   TString EffRatioBkgInfo = "";
   EffRatioBkgInfo.Form("%e",factor_Eff_Frag[0]);
   TString ErrRatioBkgInfo = "";
   ErrRatioBkgInfo.Form("%e",factor_Eff_Frag[1]);
   
   
   // BR ratio
   std::vector<Double_t> ratio_BR;
   
   ratio_BR = divError(BR_bkg, BR_bkg_Err, BR_sig, BR_sig_Err);
   std::cout << BR_bkg << " " << BR_bkg_Err << " " << BR_sig << " " << BR_sig_Err << std::endl; //LHENRY
   std::cout << "Ratio_BR: " << ratio_BR[0] << " " << ratio_BR[1] << std::endl; //LHENRY
   std::cout << std::fixed << std::showpoint;
   std::setprecision(10);
   TString BRInfo = "";
   BRInfo.Form("%e",BR_bkg);
   TString BRErrorInfo = "";
   BRErrorInfo.Form("%e",BR_bkg_Err);
   
   // Multiplication of Eff X fragmentation X BR
   std::vector<Double_t> factor_Eff_Frag_BR;
   factor_Eff_Frag_BR = multError(factor_Eff_Frag[0], factor_Eff_Frag[1], ratio_BR[0], ratio_BR[1]); 
   std::cout << factor_Eff_Frag[0] << " " << factor_Eff_Frag[1] << " " << ratio_BR[0] << " " << ratio_BR[1] << std::endl; //LHENRY
   std::cout << "factor_Eff_Frag_BR: " << factor_Eff_Frag_BR[0] << " " << factor_Eff_Frag_BR[1] << std::endl; //LHENRY

   // ****************************** //
   //          Total factor          //
   // ****************************** //
   std::cout << std::fixed << std::showpoint;
   std::setprecision(10);
   TString FactorBkgInfo = "";
   FactorBkgInfo.Form("%e",factor_Eff_Frag_BR[0]);
   TString FactorBkgErrorInfo = "";
   FactorBkgErrorInfo.Form("%e",factor_Eff_Frag_BR[1]);
   
   ////////////////////////////
   //  Create SQL statement  //
   ////////////////////////////
   
   std::cout << "INFO: Inserting (" << ID << ", " << Sel << ", " <<  BkgName << "," << treeName << ", " << KS_type << ", " << Year << ", " 
	     << EffSelNGenInfo << ", " 
	     << ErrSelNGenInfo << ", "
	     << EffSelNGenInfo_bkg << ", " 
	     << ErrSelNGenInfo_bkg << ", "
	     << EffRatioBkgInfo << ","
	     << ErrRatioBkgInfo << ","
	     << BRInfo << ", " 
	     << BRErrorInfo << ", " 
	     << FactorBkgInfo << ", " 
	     << FactorBkgErrorInfo << ")" 
	     << std::endl; 
   TString db_Dict   = "INSERT INTO BKGYIELD (ID,SELECTION,PARTRECO,TREENAME,KSTYPE,YEAR,EFFSIG,ERRSIG,EFFBKG,ERRBKG,EFFRATIO,ERRRATIO,BR,ERRBR,YIELD,ERRYIELD) ";
   TString db_Link   = "VALUES ("+ID+", '"+Sel+"', '"+BkgName+"', '"+treeName+"', '"+KS_type+"', '"+Year+"', "+EffSelNGenInfo+", "+ErrSelNGenInfo+", "+EffSelNGenInfo_bkg+", "+ErrSelNGenInfo_bkg+", "+EffRatioBkgInfo+", "+ErrRatioBkgInfo+", "+BRInfo+", "+BRErrorInfo+", "+FactorBkgInfo+", "+FactorBkgErrorInfo+");";
   TString insertVal = db_Dict + db_Link;
   std::string Value = (insertVal).Data();
   const char* sql = Value.c_str();
   
   ////////////////////////////
   //  Execute SQL statement //
   ////////////////////////////
   
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   int return_code;
   if ( rc != SQLITE_OK ){
     return_code = 1;
     fprintf(stderr, "SQL error: %s\n", zErrMsg);
     sqlite3_free(zErrMsg);     
   } else {
     return_code = 0;
     fprintf(stdout, "Records created successfully\n");
   }
   
   sqlite3_close(db);
   std::cout << return_code << std::endl;
   return return_code;
}
