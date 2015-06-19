#include <RooResolutionModel.h>
#include <P2VV/RooAbsEffResModel.h>

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const char *name, const char *title, RooRealVar& convVar) 
   : RooResolutionModel(name, title, convVar)
{  
}

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const RooAbsEffResModel& other, const char* name) 
  : RooResolutionModel(other, name)
{
}

