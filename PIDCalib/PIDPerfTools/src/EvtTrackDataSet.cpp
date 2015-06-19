// $Id: $
// Include files
#include <algorithm>
#include <iomanip>
// local
#include "PIDPerfTools/EvtTrackDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : EvtTrackDataSet
//
// 2010-12-25 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(EvtTrackDataSet)

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
EvtTrackDataSet::EvtTrackDataSet( )
  : TrackDataSet( )
{

}

EvtTrackDataSet::EvtTrackDataSet( const std::string& TrackName,
                                  const std::string& Charge,
                                  RooDataSet* Data,
                                  const RooArgSet& vars,
                                  const std::string& P_Var,
                                  const std::string& PT_Var,
                                  const std::string& ETA_Var,
                                  const std::string& nTrack_Var,
                                  const std::string& DLLK_Var,
                                  const std::string& DLLp_Var,
                                  const std::string& Cuts,
                                  const std::string& WgtVarName
                                  )
  : TrackDataSet( TrackName,
                  Charge,
                  Data,
                  vars,
                  P_Var,
                  PT_Var,
                  ETA_Var,
                  DLLK_Var,
                  DLLp_Var,
                  Cuts,
                  WgtVarName)
{
  SetTrackVar( nTrack_Var,
               "nTrack");
}

EvtTrackDataSet::EvtTrackDataSet( const std::string& TrackName,
                                  const std::string& Charge,
                                  EvtTrackDataSet* Data,
                                  const RooArgSet& vars,
                                  const std::string& Cuts ,
                                  const std::string& WgtVarName
                                  )
  : TrackDataSet( TrackName,
                  Charge,
                  Data,
                  vars,
                  Cuts,
                  WgtVarName )
{
  SetTrackVar( Data->Get_ParamName_nTrack(),
               "nTrack");
}


EvtTrackDataSet::EvtTrackDataSet( const std::string& TrackName,
                                  const std::string& Charge,
                                  TTree* Ntuple,
                                  const RooArgSet& Vars,
                                  const std::string& P_Var,
                                  const std::string& PT_Var,
                                  const std::string& ETA_Var,
                                  const std::string& nTrack_Var,
                                  const std::string& DLLK_Var,
                                  const std::string& DLLp_Var,
                                  const std::string& Cuts,
                                  const std::string& WgtVarName
                                  )
  : TrackDataSet( TrackName,
                  Charge,
                  Ntuple,
                  Vars,
                  P_Var,
                  PT_Var,
                  ETA_Var,
                  DLLK_Var,
                  DLLp_Var,
                  Cuts,
                  WgtVarName )
{
  SetTrackVar( nTrack_Var,
               "nTrack");
}

EvtTrackDataSet::EvtTrackDataSet( const std::string& Name,
                                  const std::string& Title,
                                  EvtTrackDataSet* Data,
                                  const RooArgSet& vars,
                                  const RooFormulaVar* cutVar,
                                  const std::string& cutRange,
                                  int nStart,
                                  int nStop,
                                  Bool_t copyCache,
                                  const std::string& wgtVarName)
  : TrackDataSet(Name,
                 Title,
                 dynamic_cast<EvtTrackDataSet*>(Data),
                 vars,
                 cutVar,
                 cutRange,
                 nStart,
                 nStop,
                 copyCache,
                 wgtVarName)
{
  SetTrackVar( Data->Get_ParamName_nTrack(),
               "nTrack");
}

EvtTrackDataSet::EvtTrackDataSet( const std::string& Name,
                                  const std::string& Charge,
                                  EvtTrackDataSet* Numerator,
                                  EvtTrackDataSet* Denominator,
                                  const std::string& WgtVar,
                                  const std::string& Cuts_Num,
                                  const std::string& Cuts_Denom,
                                  const std::string& WgtVar_Num,
                                  const std::string& WgtVar_Denom
                                  )
  : TrackDataSet(Name,
                 Charge,
                 Numerator,
                 Denominator,
                 WgtVar,
                 Cuts_Num,
                 Cuts_Denom,
                 WgtVar_Num,
                 WgtVar_Denom
                 )
{
  SetTrackVar( Denominator->Get_ParamName_nTrack(),
               "nTrack");
}

//=============================================================================
// Destructor
//=============================================================================
EvtTrackDataSet::~EvtTrackDataSet() {}

//=============================================================================
// Append method for EvtTrackDataSet
//=============================================================================
void EvtTrackDataSet::append(EvtTrackDataSet& Data)
{
  assert( Data.Get_ParamName_nTrack() == this->Get_ParamName_nTrack() );

  //RooDataSet::append(dynamic_cast<RooDataSet&>(Data));
  TrackDataSet::append(dynamic_cast<TrackDataSet&>(Data));

}

//=============================================================================
// Get nTrack Param Name
//=============================================================================
const std::string EvtTrackDataSet::Get_ParamName_nTrack() const
{
  return Get_ParamName("nTrack");
}

//=============================================================================
// Get nTrack Parameter
//=============================================================================
const RooRealVar* EvtTrackDataSet::Get_Param_nTrack() const
{
  return Get_Param("nTrack");
}

//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* EvtTrackDataSet::SetInBinSchema(std::vector<RooBinning*>& BinSchema)
{
  std::vector<RooBinning*>::iterator itr_Binning;

  std::list<std::pair<std::string, RooBinning*> > BinDefs;

  for(itr_Binning = BinSchema.begin(); itr_Binning != BinSchema.end(); ++itr_Binning)
  {
    BinDefs.push_back( make_pair(this->Get_ParamName((*itr_Binning)->GetName()),
                                 *itr_Binning) );
  }

  DataBinCuts Data_Cuts("Data Cuts",
                        "",
                        BinDefs);

  RooFormulaVar cutVar(Data_Cuts.GetGlobalCuts(),
                       Data_Cuts.GetGlobalCuts(),
                       *get()) ;

  return reduceEng(*get(),
                   &cutVar,
                   "",
                   0,
                   2000000000,
                   kFALSE);

}

//=============================================================================
// Implementation of RooAbsData virtual method that drives the
// RooAbsData::reduce() methods
//=============================================================================
RooAbsData* EvtTrackDataSet::reduceEng(const RooArgSet& varSubset,
                                       const RooFormulaVar* cutVar,
                                       const std::string& cutRange,
                                       Int_t nStart,
                                       Int_t nStop,
                                       Bool_t copyCache)
{
  checkInit() ;

  RooArgSet tmp(varSubset) ;
  if (_wgtVar) {
    tmp.add(*_wgtVar) ;
  }
  EvtTrackDataSet* ret = new EvtTrackDataSet( GetName(),
                                              GetTitle(),
                                              this,
                                              tmp,
                                              cutVar,
                                              cutRange,
                                              nStart,
                                              nStop,
                                              copyCache,
                                              _wgtVar ? _wgtVar->GetName() : "" ) ;

  // WVE - propagate optional weight variable
  //       check behaviour in plotting.
  //   if (_wgtVar) {
  //     ret->setWeightVar(_wgtVar->GetName()) ;
  //   }
  return ret ;
}

//=============================================================================
