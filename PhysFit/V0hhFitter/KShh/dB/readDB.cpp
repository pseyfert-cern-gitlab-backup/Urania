#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sqlite3.h> 

//ROOT
#include "TString.h"

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
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  const char *sql;
  const char* data = "Callback function called";
  
  /* Open database */
   TString currentDir = getenv("V0HHFITTERROOT");
   std::string dirConversion = (currentDir).Data();
   std::string fileTable = (argc > 1)? dirConversion+"/KShh/dB/efficiencyTable-PIDcrit.db":dirConversion+"/KShh/dB/efficiencyTable.db";
   rc = sqlite3_open(fileTable.c_str(), &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
     fprintf(stderr, "Opened database successfully\n");
   }
   
   /* Create SQL statement */
   //   sql = "SELECT * from EFFICIENCY";
   sql = "SELECT * from EFFICIENCY WHERE SELECTION LIKE 'Loose'";
   //   sql = "SELECT * from EFFICIENCY WHERE SELECTION LIKE 'Loose' AND MODE LIKE 'Bd2KSKK' AND KSTYPE LIKE 'DD' AND YEAR LIKE '2011' AND TREENAME LIKE 'Kpi'";
   //   sql = "SELECT * from EFFICIENCY WHERE SELECTION LIKE 'Loose' AND MODE LIKE 'Bd2KSKK' AND KSTYPE LIKE 'DD' AND YEAR LIKE '2011' AND TREENAME LIKE 'Kpi'";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", zErrMsg);
     sqlite3_free(zErrMsg);
   }else{
     fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
