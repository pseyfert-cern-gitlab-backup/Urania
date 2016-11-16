// Include files
#include <string>
#include <vector>
#include <iostream>
#include "TChain.h"

// local
#include "CalibDataScripts/GetData.h"
TChain* GetData(const std::vector<std::string>& files,
                const char* SubDir_TreeName)
{ 
  
  TChain* t = new TChain(SubDir_TreeName);
  
  std::vector<std::string>::const_iterator itr;
  for(itr=files.begin(); itr!=files.end(); ++itr)// Loop over ganga IDs
  { 
    //std::cout<<*itr<<std::endl;
    t->Add(itr->c_str());
  }
  
  std::cout << "Got " << t->GetEntries() << " entries for tuple type \""
            << SubDir_TreeName << "\"" << std::endl;
  return t;
}
