#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

//ROOT
#include "TString.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int  rc;
  const char *sql;
  bool criterion = (argc > 1);
  if (criterion)
	  std::cout << "INFO: Creating the PIDcrit database." << std::endl;
  /* Open database */
  TString currentDir = getenv("V0HHFITTERROOT");
  std::string dirConversion = (currentDir).Data();
  std::string fileTable = dirConversion+"/KShh/dB/efficiencyTable-New.db"; 
  
  rc = sqlite3_open(fileTable.c_str(), &db);
  if (rc){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    exit(0);
  } else{
    fprintf(stdout, "Opened database successfully\n");
  }
  
  /* Create SQL statement */
  sql =  "CREATE TABLE EFFICIENCY("			 \
	  "ID INT PRIMARY KEY     NOT NULL,"	 \
	  "SELECTION      TEXT    NOT NULL,"	 \
	  "MODE           TEXT    NOT NULL,"	 \
	  "KSTYPE         TEXT    NOT NULL,"	 \
	  "YEAR           TEXT    NOT NULL,"	 \
	  "TREENAME       TEXT    NOT NULL,"	 \
	  "EFFSELNGEN     REAL,"				 \
	  "ERRSELNGEN     REAL,"				 \
	  "EFFPID         REAL,"				 \
	  "ERRPID         REAL,"				 \
	  "EFFTOT         REAL,"				 \
	  "ERRTOT         REAL );";
  
  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
  } else {
	  fprintf(stdout, "Table created successfully\n");
  }
  sqlite3_close(db);
  return 0;
}
