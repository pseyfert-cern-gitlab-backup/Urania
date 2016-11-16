#include <vector>
#include "root_libs.h"
#include "TObjString.h"

void GangaMacro(char* arg1 = "", char* arg2 = "", char* arg3 = "",
		char* arg4 = "", char* arg5 = "", char* arg6 = "",
		char* arg7 = "", char* arg8 = "", char* arg9 = "",
		char* arg10 = "", char* arg11 = "", char* arg12 = "",
		char* arg13 = "") {
  
  gSystem->Load("confinte_cpp.so");

  gSystem->Load("testFC_macro_C.so");
  
  //set up main, eg command line opts
  vector<TObjString*> myObj;
  //-var 1 -bin 5 -P 2 -points 2 -f RootWorksp_FD_outp.root 
  myObj.push_back(new TObjString(arg1));
  myObj.push_back(new TObjString(arg2));
  myObj.push_back(new TObjString(arg3));
  myObj.push_back(new TObjString(arg4));
  myObj.push_back(new TObjString(arg5));
  myObj.push_back(new TObjString(arg6));
  myObj.push_back(new TObjString(arg7));
  myObj.push_back(new TObjString(arg8));
  myObj.push_back(new TObjString(arg9));
  myObj.push_back(new TObjString(arg10));
  myObj.push_back(new TObjString(arg11));
  myObj.push_back(new TObjString(arg12));
  myObj.push_back(new TObjString(arg13));


  //convert the TList args into a main compatible list
  const Int_t argc = myObj.size();

  //memory is dynamically allocated
  char** argv = new char*[argc];

  Int_t count = 0;
  for(int iob =0; iob<myObj.size(); iob++) {
    const char* str = myObj.at(iob)->String();
    argv[count] = new char[strlen(str)];
    strcpy(argv[count],str);
    count++;
  }

  //Executes code
  testFC_macro(argc, argv);

  //clean up
  for(int i = 0; i < argc; i++){
    delete argv[i];
  }
  delete argv;

  return;

}
