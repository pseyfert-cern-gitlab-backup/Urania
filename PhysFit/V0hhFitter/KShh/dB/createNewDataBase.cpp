/*#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

//ROOT
#include "TCut.h"
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

void usage( std::ostream& out, const TString& progName )
{
  out<<"Usage:\n";
  out<<progName<<" [ID] [Type = Signal or CrossFeed] [Sel] [Mode] [KS_type] [Year] [optional treeName]\n";
}

int main(int argc, char* argv[])
{
	// Input configuration
	if ( argc < 6 ) {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}   	
	TString ID       = argv[1];
	TString Type     = argv[2];
	TString Sel      = argv[3];
	TString Mode     = argv[4];
	TString KS_type  = argv[5];
	TString Year     = argv[6];
	std::string treeName = "";
	if ( Type == "CrossFeed" ) { 
		if ( argc > 7 ) { 
			treeName = argv[7];
		}  
		else {
			usage( std::cerr, argv[0] );
			return EXIT_FAILURE;
		}   
	} else {
		if ((Mode == "Bd2KSpipi") || (Mode == "Bs2KSPipi")){
			treeName = "pipi";
		} else if ((Mode == "Bd2KSKpi") || (Mode == "Bs2KSKpi")){
			treeName = "Kpi";
		} else if ((Mode == "Bd2KSKpi") || (Mode == "Bs2KSKpi")){
			treeName = "piK";
		} else {
			treeName = "KK";
		}
	}
	// Global variables
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	//char *sql;
	
	///////////////////////////
	//     Open database     //
	///////////////////////////
	TString currentDir = getenv("V0HHFITTERROOT");
	std::string dirConversion = (currentDir).Data();
	std::string fileTable = dirConversion+"/KShh/dB/efficiencyTable-New.db"; 
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
	//	TString cutStr = "";
	// Generated efficiency
	Double_t Acc_eff(0.);
	if (Mode == "Bd2KSpipi")
		if (Year == "2011") Acc_eff = 0.1970;
		else Acc_eff = 0.2066;
	else if (Mode == "Bs2KSpipi")
		if (Year == "2011") Acc_eff = 0.1967;
		else  Acc_eff = 0.2066;
	else if ((Mode == "Bd2KSKpi") || (Mode == "Bd2KSpiK"))
		if (Year == "2011") Acc_eff = 0.2017;
		else Acc_eff = 0.2111;
	else if ((Mode == "Bs2KSKpi") || (Mode == "Bs2KSpiK"))
		if (Year == "2011") Acc_eff = 0.2023;
		else Acc_eff = 0.2113;
	else if (Mode == "Bd2KSKK")
		if (Year == "2011") Acc_eff = 0.2075;
		else Acc_eff = 0.2169;
	else if (Mode == "Bs2KSKK")
		if (Year == "2011") Acc_eff = 0.2074;
		else  Acc_eff = 0.2163;
	else 
		{
			fprintf(stderr, "ERROR: There is something wrong in the efficiency configuration");
			exit(0);
		}
	TString EffGenInfo = "";
	EffGenInfo.Form("%e",Acc_eff);
	
	// PID efficiency
	TString baseDir = getenv("V0HHFITTERDATA");
	
   // Calculate Selection efficiency
   // Uses: BR MC samples & Gen samples.
   // Ratio: N(selection)(Mode)/N(gen(Mode)
   Double_t Sel_num(0.), Sel_den(0.), Sel_eff(0.);
   Double_t Err_Sel_num(0.), Err_Sel_den(0.), Sel_err(0.);
   TFile *Sig_eff = 0;
   if (Mode == "Bd2KSpiK"){
	   Sig_eff = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/BDT/"+Sel+"/Bd2KSKpi/Bd2KSKpi-MC-"+Year+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT.root");
   } else if (Mode == "Bs2KSpiK"){
	   Sig_eff = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/BDT/"+Sel+"/Bs2KSKpi/Bs2KSKpi-MC-"+Year+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT.root");
   } else {
	   Sig_eff = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/BDT/"+Sel+"/Bd2KSKpi/Bd2KSKpi-MC-"+Year+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT.root");
   }
   TTree* t_Eff   = dynamic_cast<TTree*>( Sig_eff->Get("B2KShh"+KS_type+"/B2"+treeName+"KS"));
   Sel_num     = t_Eff->GetEntries();
   Err_Sel_num = sqrt(Sel_num); 
   
   TString genYear ="";
   if ((Year == "2012a") || (Year == "2012b")){ genYear = "2012"; }
   else { genYear = "2011"; }
   TFile *Sig_eff_den = 0;
   if (Mode == "Bd2KSpiK"){
      Sig_eff_den = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/Gen/Bd2KSKpi/Bd2KSKpi-MC-"+genYear+"-MagAll.root");
   } else if (Mode == "Bs2KSpiK"){
      Sig_eff_den = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/Gen/Bs2KSKpi/Bs2KSKpi-MC-"+genYear+"-MagAll.root");
   } else {
      Sig_eff_den = TFile::Open(baseDir + "/KShh/MonteCarlo/"+Year+"/Gen/"+Mode+"/"+Mode+"-MC-"+genYear+"-MagAll.root");
   }
   TTree* t_Eff_den   = dynamic_cast<TTree*>( Sig_eff_den->Get("tupleMCTruth"));
   Sel_den     = t_Eff_den->GetEntries();
   Err_Sel_den = sqrt(Sel_den); 
   
   // Total Selection efficiency 
   Sel_eff = Sel_num/Sel_den;
   std::cout << std::fixed << std::showpoint;
   std::setprecision(10);
   TString EffSelInfo = "";
   EffSelInfo.Form("%e",Sel_eff);
   
   // Selection efficiency error
   Double_t sig_1_sq   = (Err_Sel_num/Sel_num)*(Err_Sel_num/Sel_num);
   Double_t sig_2_sq   = (Err_Sel_den/Sel_den)*(Err_Sel_den/Sel_den);
   Sel_err             = Sel_eff*(sqrt(sig_1_sq + sig_2_sq));
   TString ErrSelInfo = "";
   ErrSelInfo.Form("%e",Sel_err);

   // Calculate Selection efficiency X Generated one 
   Double_t SelNGen_Eff(0.), SelNGen_Err(0.);
   SelNGen_Eff = Sel_eff*Acc_eff;
   TString EffSelNGenInfo = "";
   EffSelNGenInfo.Form("%e",SelNGen_Eff);
   Double_t rel_Eff_Sel = Sel_err/Sel_eff;
   SelNGen_Err = SelNGen_Eff*rel_Eff_Sel;
   TString ErrSelNGenInfo = "";
   ErrSelNGenInfo.Form("%e",SelNGen_Err);

   // Close files
   Sig_eff->Close();
   Sig_eff_den->Close();
                                       
   // Total efficiency
   Double_t tot_eff(0.);
   tot_eff = PID_eff*Sel_eff*Acc_eff;
   if (criterion && (Sel == "Loose" || Sel == "Tight"))
	   tot_eff *= criterionEff.first;
   TString EffTotInfo = "";
   EffTotInfo.Form("%e",tot_eff);
   
   // Total efficiency error
   Double_t tot_eff_err(0.), Error_Sel_PID(0.), rel_err(0.);
   Double_t Sel_PID_eff = Sel_eff*PID_eff;
   if (criterion && (Sel == "Loose" || Sel == "Tight"))
	   Sel_PID_eff *= criterionEff.first;
   Double_t tot_sig_1_sq = (Sel_err/Sel_eff)*(Sel_err/Sel_eff);
   Double_t tot_sig_2_sq = (PID_eff_err/PID_eff)*(PID_eff_err/PID_eff);
   Double_t tot_sig_3_sq = 0;
   if (criterion && (Sel == "Loose" || Sel == "Tight"))
	   if (criterionEff.first != 0.)
		   tot_sig_3_sq = (criterionEff.second/criterionEff.first)*(criterionEff.second/criterionEff.first);
	   else
		   tot_sig_3_sq = 0.;
   Error_Sel_PID = Sel_PID_eff*(sqrt(tot_sig_1_sq + tot_sig_2_sq + tot_sig_3_sq));
   rel_err       = (sqrt(tot_sig_1_sq + tot_sig_2_sq + tot_sig_3_sq));//(Error_Sel_PID)/(Sel_PID_eff); 
   tot_eff_err   = tot_eff*rel_err; 
   TString ErrTotInfo = "";
   ErrTotInfo.Form("%e",tot_eff_err);

   ////////////////////////////
   //  Create SQL statement  //
   ////////////////////////////
   if (!criterion) 
	   std::cout << "INFO: Inserting (" << ID << ", " << Sel << ", " <<  Mode << ", " << KS_type << ", " << Year << ", " << treeName << ", " 
				 << EffGenInfo << ", " 
				 << EffSelInfo << ", " << ErrSelInfo << ", "
				 << EffSelNGenInfo << ", " << ErrSelNGenInfo << ", " 
				 << EffPIDInfo << ", " << ErrPIDInfo << ", " 
				 << EffTotInfo << ", " << ErrTotInfo << ")" 
				 << std::endl; 
   else
	   	   std::cout << "INFO: Inserting (" << ID << ", " << Sel << ", " <<  Mode << ", " << KS_type << ", " << Year << ", " << treeName << ", " 
					 << EffGenInfo << ", " 
					 << EffSelInfo << ", " << ErrSelInfo << ", "
					 << EffSelNGenInfo << ", " << ErrSelNGenInfo << ", " 
					 << EffPIDInfo << ", " << ErrPIDInfo << ", " 
					 << EffCritInfo    << ", " << ErrCritInfo << ", " 
					 << EffTotInfo << ", " << ErrTotInfo << ")" 
					 << std::endl; 

   
   TString db_Dict   = (criterion)?
	   "INSERT INTO EFFICIENCY (ID,SELECTION,MODE,KSTYPE,YEAR,TREENAME,EFFGEN,EFFSEL,ERRSEL,EFFSELNGEN,ERRSELNGEN,EFFPID,ERRPID,EFFCRIT,ERRCRIT,EFFTOT,ERRTOT) ":
	   "INSERT INTO EFFICIENCY (ID,SELECTION,MODE,KSTYPE,YEAR,TREENAME,EFFGEN,EFFSEL,ERRSEL,EFFSELNGEN,ERRSELNGEN,EFFPID,ERRPID,EFFTOT,ERRTOT) ";
   TString db_Link   = (criterion)?
	   "VALUES ("+ID+", '"+Sel+"', '"+Mode+"', '"+KS_type+"', '"+Year+"', '"+treeName+"',"+EffGenInfo+","+EffSelInfo+","+ErrSelInfo+", "+EffSelNGenInfo+", "+ErrSelNGenInfo+", "+EffPIDInfo+", "+ErrPIDInfo+", "+EffCritInfo+", "+ErrCritInfo+", "+EffTotInfo+", "+ErrTotInfo+");":
	   "VALUES ("+ID+", '"+Sel+"', '"+Mode+"', '"+KS_type+"', '"+Year+"', '"+treeName+"',"+EffGenInfo+","+EffSelInfo+","+ErrSelInfo+", "+EffSelNGenInfo+", "+ErrSelNGenInfo+", "+EffPIDInfo+", "+ErrPIDInfo+", "+EffTotInfo+", "+ErrTotInfo+");";
   TString insertVal = db_Dict + db_Link;
   std::string Value = (insertVal).Data();
   const char* sql = Value.c_str();
   
   ////////////////////////////
   //  Execute SQL statement //
   ////////////////////////////
   
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if ( rc != SQLITE_OK ){
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
   } else {
	   fprintf(stdout, "Records created successfully\n");
   }
   
   sqlite3_close(db);
   
   return 0;
}
*/

#include <iostream>

int main()
{
	std::cout << "Hello world!" << std::endl;
}
