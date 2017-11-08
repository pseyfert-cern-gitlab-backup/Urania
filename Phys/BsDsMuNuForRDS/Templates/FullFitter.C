#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "TError.h"
#include "Riostream.h"

#include "FitTools.h"

using namespace std;
using namespace RooFit;

int main(int argc, char **argv) {

  string flag = "outp";
  string infi = "Strip20_20r1_data_dimuon_all_newDLL.root";
  bool applyRange = kFALSE;
  string range = "bli_l,bli_u";
  int debug(0); 
  string confF = "config/config_file.txt";
  string confFl = "";
  bool doMCmat = kFALSE;
  bool doTwoD = kFALSE;
  bool SameSign = kFALSE; 
  bool SignalOnly = kFALSE;
  bool AddConstraint = kFALSE;
  gErrorIgnoreLevel = kFatal;
  
  for (int i = 0; i < argc; i++){
    cout<<" "<<argc<<" "<<argv[i]<<endl;
    if(strcmp(argv[i],"-in") == 0)    { infi = string(argv[++i]);    }                 // Decide among different MC input
    if(strcmp(argv[i],"-flag") == 0)  { flag = string(argv[++i]);    }                 // Flagging output eps files
    if(strcmp(argv[i],"-deb") == 0)   { debug = atoi(argv[++i]);  }                    // Enable debug
    if(strcmp(argv[i],"-cfg") == 0)   { confF = string(argv[++i]);  }                  // Config file
    if(strcmp(argv[i],"-twd") == 0)    { doTwoD = kTRUE;  }                           // Do TwoD
    if(strcmp(argv[i],"-mcmat") == 0)    { doMCmat = kTRUE;  }                           // Do TwoD
    if(strcmp(argv[i],"-ss") == 0)    { SameSign = kTRUE;  }                           // Use bkg from SS
    if(strcmp(argv[i],"-aco") == 0)    { AddConstraint = kTRUE;  }                           // AddConstraint
    if(strcmp(argv[i],"-sigO") == 0)  { SignalOnly = kTRUE;  }                         // Signal Only
    if(strcmp(argv[i],"-conf") == 0)  { confFl = string(argv[++i]);  }                 // PDF flag
    if(strcmp(argv[i],"-range") == 0) { 
           // Flagging output eps files
      applyRange = kTRUE;
      range = string(argv[++i]);  
    }                        
  }
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;

  FitTools *d = new FitTools(infi,flag,debug,SignalOnly,AddConstraint);

  if(SameSign) d->doSameSign();

  if(doTwoD) d->doTwoD();

  if(doMCmat) d->doMCmat();

  d->configure(range,applyRange,confF);

  d->loadPDFs(confFl);

  d->doFit();

  return 0;
}

