#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sqlite3.h> 

//ROOT
#include "TString.h"

#include <boost/program_options.hpp>

static int callback(void *data, int argc, char **argv, char **azColName){
  int i;
  fprintf(stderr, "%s: ", (const char*)data);
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char* argv[])
{
  std::string year(""),bdt(""),KS(""),mode(""),tree("");
  boost::program_options::options_description decisions("Option Arguments");
  decisions.add_options()    
    ("help,h" , "produce help message")
    ("year,y", boost::program_options::value<std::string>(&year), "specify which year is to be taken into account (2011, 2012a, 2012b).")
    ("bdt,b", boost::program_options::value<std::string>(&bdt), "specify which bdt is to be taken into account (Loose, Tight, DP1, DP2).")
    ("KS,k", boost::program_options::value<std::string>(&KS), "specify which KS type is to be taken into account (DD,LL).")
    ("mode,m", boost::program_options::value<std::string>(&mode), "specify which mode is to be taken into account (Bd2etapKS02pipigamma Bd2pipiKS0gamma Bd2Kst0rho02KS0pi0pipi Bu2D0pi2KS0pipi Bs2KstKst2KS0piKpi0 Bu2D0K2KS0pipi Bd2Kst0phi2KS0pi0KK Bd2etacKS2KKpi0).")
    ("tree,t", boost::program_options::value<std::string>(&tree), "specify which tree is to be taken into account.")
    ;  
  boost::program_options::variables_map vm;
  boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
  boost::program_options::notify( vm );
  std::vector<std::string> messages; 
  if( vm.count("help") ) {
    std::cout << decisions << std::endl;
    std::exit(0);
  }
 if (vm.count("year"))
    messages.push_back("YEAR LIKE '"+year+"'");
  if (vm.count("bdt"))
    messages.push_back("SELECTION LIKE '"+bdt+"'");
  if (vm.count("KS"))
    messages.push_back("KSTYPE LIKE '"+KS+"'");
  if (vm.count("mode"))
    messages.push_back("PARTRECO LIKE '"+mode+"'");
  if (vm.count("tree"))
    messages.push_back("TREENAME LIKE '"+tree+"'");


  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  //  const char *sql;
  std::string sql;
  const char* data = "Callback function called";
  
  /* Open database */
  TString currentDir = getenv("V0HHFITTERROOT");
  std::string dirConversion = (currentDir).Data();
  std::string fileTable = dirConversion+"/KShh/dB/partiallyRecoYielTable-BF.db"; 
  rc = sqlite3_open(fileTable.c_str(), &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    exit(0);
  }
  else
    fprintf(stderr, "Opened database successfully\n");
  
  /* Create SQL statement */
  sql = std::string("SELECT * from BKGYIELD");
  if (messages.size() != 0)
    sql += std::string(" WHERE");
  bool first(true);
  for (std::vector<std::string>::iterator it = messages.begin() ; it != messages.end() ; ++it)
    {
      if (first)
	{
	  sql += std::string(" ");
	  sql += *it;
	  first = false;       
	}
      else
	{
	  sql += std::string(" AND ");
	  sql += *it;
	}
    }
  std::cout << sql << std::endl;
  
  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
  if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }else{
    fprintf(stdout, "Operation done successfully\n");
  }
  sqlite3_close(db);
  return 0;
}
