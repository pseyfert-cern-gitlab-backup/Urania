#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "TError.h"
#include "Riostream.h"

#include "TemplateTools.h"

using namespace std;
using namespace RooFit;

int main(int argc, char **argv) {

  string flag = "outp";
  string infi = "Strip20_20r1_data_dimuon_all_newDLL.root";
  string confF = "config/config_file.txt";
  bool applyRange = kFALSE;
  string range = "bli_l,bli_u";
  int debug(0), parm, parbin;
  bool matchMC = kFALSE;
  bool doMC = kFALSE;
  bool doNewMC = kFALSE;
  bool doTau = kFALSE;
  bool doTrueDs = kFALSE;
  bool doSB = kFALSE;
  bool doSS = kFALSE;
  bool doFake = kFALSE;
  bool doRooKeys = kFALSE;
  bool doFF = kFALSE;
  gErrorIgnoreLevel = kFatal;

  for (int i = 0; i < argc; i++){
    cout<<" "<<argc<<" "<<argv[i]<<endl;
    if(strcmp(argv[i],"-in") == 0)    { infi = string(argv[++i]);    }                 // Decide among different MC input
    if(strcmp(argv[i],"-flag") == 0)  { flag = string(argv[++i]);    }                 // Flagging output eps files
    if(strcmp(argv[i],"-deb") == 0)   { debug = atoi(argv[++i]);  }                    // Enable debug
    if(strcmp(argv[i],"-mc") == 0)    { doMC = kTRUE;  }                    // MC events
    if(strcmp(argv[i],"-newmc") == 0)    { doNewMC = kTRUE;  }                    // MC events
    if(strcmp(argv[i],"-fake") == 0)  { doFake = kTRUE;  }                    // MC events
    if(strcmp(argv[i],"-side") == 0)  { doSB = kTRUE;  }                    // Sidebands
    if(strcmp(argv[i],"-tau") == 0)   { doTau = kTRUE;  }                    // Enable debug
    if(strcmp(argv[i],"-ss") == 0)    { doSS = kTRUE;  }                    // Enable debug
    if(strcmp(argv[i],"-trueds") == 0)   { doTrueDs = kTRUE;  }                    // True Ds
    if(strcmp(argv[i],"-rook") == 0)   { doRooKeys = kTRUE;  }                    // create rookeys pdfs
    if(strcmp(argv[i],"-ff") == 0)   { doFF = kTRUE; parbin = atoi(argv[++i]); }     // do the templates only for mass in bins of q2 
    if(strcmp(argv[i],"-conf") == 0) { confF = string(argv[++i]);  }                    // configuration file
    if(strcmp(argv[i],"-mat") == 0)   { matchMC = kTRUE; parm = atoi(argv[++i]);  }                    // Enable debug
    if(strcmp(argv[i],"-range") == 0) { 
           // Flagging output eps files
      applyRange = kTRUE;
      range = string(argv[++i]);  
    }                        
  }
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;

  TemplateTools *d = new TemplateTools(infi,flag,debug);

  d->configure(range,applyRange,confF);

  if(doSB) d->doSideBands();

  if(doSS) d->doSameSign();

  if(doTrueDs) d->doTrueDs();

  if(doFake) d->doFake();

  if(doFF) d->doFF(parbin);

  if(doRooKeys) d->doRooKeys();

  if(doNewMC) d->doNewMC();
  
  if(doMC) {
    d->doMC();
    if(matchMC) d->doMCmatch(parm);
    if(doTau) d->doTau();
  }
  cout<<"Setting output "<<endl;
  d->SetupOutput();

  d->doTemplate();

  return 0;
}

