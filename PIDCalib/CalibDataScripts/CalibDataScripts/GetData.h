// $Id: $
#ifndef CALIBDATASCRIPTS_GETDATA_H 
#define CALIBDATASCRIPTS_GETDATA_H 1

// Include files
#include "TChain.h"

#include <string>
#include <vector>

/*
 * @author Andrew Powell (LHCb)04
 *  @date   2011-06-17
 */

TChain* GetData(const std::vector<std::string>& files,
                const char* SubDir_TreeName);

TChain* GetData(const std::vector<std::string>& files,
                const char* SubDir_TreeName, TString cutstring);

#endif // CALIBDATASCRIPTS_GETDATA_H


