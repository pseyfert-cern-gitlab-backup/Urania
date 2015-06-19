// $Id: $
// Include files
#include <algorithm>
#include <iomanip>
// local
#include "PIDPerfTools/MUONTrackDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : MUONTrackDataSet
//
// 2011-09-22 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(MUONTrackDataSet)

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
MUONTrackDataSet::MUONTrackDataSet( )
  : EvtTrackDataSet( )
{

}

MUONTrackDataSet::MUONTrackDataSet( const std::string& TrackName,
                                    const std::string& Charge,
                                    RooDataSet* Data,
                                    const RooArgSet& vars,
                                    const std::string& P_Var,
                                    const std::string& PT_Var,
                                    const std::string& ETA_Var,
                                    const std::string& nTrack_Var,
                                    const std::string& DLLK_Var,
                                    const std::string& DLLp_Var,
                                    const std::string& DLLmu_Var,
                                    const std::string& IsMuon_Var,
                                    const std::string& IsMuonLoose_Var,
                                    const std::string& nShared_Var,
                                    const std::string& Cuts,
                                    const std::string& WgtVarName
                                    )
  : EvtTrackDataSet( TrackName,
                     Charge,
                     Data,
                     vars,
                     P_Var,
                     PT_Var,
                     ETA_Var,
                     nTrack_Var,
                     DLLK_Var,
                     DLLp_Var,
                     "",
                     WgtVarName)
{
  SetTrackVar( DLLmu_Var,
               "DLLmu");

  SetTrackVar( IsMuon_Var,
               "IsMuon" );

  SetTrackVar( IsMuonLoose_Var,
               "IsMuonLoose" );

  SetTrackVar( nShared_Var,
               "nShared" );
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}

MUONTrackDataSet::MUONTrackDataSet( const std::string& TrackName,
                                    const std::string& Charge,
                                    MUONTrackDataSet* Data,
                                    const RooArgSet& vars,
                                    const std::string& Cuts ,
                                    const std::string& WgtVarName
                                    )
  : EvtTrackDataSet( TrackName,
                     Charge,
                     Data,
                     vars,
                     "",
                     WgtVarName
                   )
{
  SetTrackVar( Data->Get_ParamName_DLLmu(),
               "DLLmu");

  SetTrackVar( Data->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Data->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Data->Get_ParamName_nShared(),
               "nShared" );
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}


MUONTrackDataSet::MUONTrackDataSet( const std::string& TrackName,
                                    const std::string& Charge,
                                    TTree* Ntuple,
                                    const RooArgSet& Vars,
                                    const std::string& P_Var,
                                    const std::string& PT_Var,
                                    const std::string& ETA_Var,
                                    const std::string& nTrack_Var,
                                    const std::string& DLLK_Var,
                                    const std::string& DLLp_Var,
                                    const std::string& DLLmu_Var,
                                    const std::string& IsMuon_Var,
                                    const std::string& IsMuonLoose_Var,
                                    const std::string& nShared_Var,
                                    const std::string& Cuts,
                                    const std::string& WgtVarName
                                    )
  : EvtTrackDataSet( TrackName,
                     Charge,
                     Ntuple,
                     Vars,
                     P_Var,
                     PT_Var,
                     ETA_Var,
                     nTrack_Var,
                     DLLK_Var,
                     DLLp_Var,
                     "",
                     WgtVarName
                   )
{
  SetTrackVar( DLLmu_Var,
               "DLLmu");

  SetTrackVar( IsMuon_Var,
               "IsMuon" );

  SetTrackVar( IsMuonLoose_Var,
               "IsMuonLoose" );

  SetTrackVar( nShared_Var,
               "nShared" );
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }

}

MUONTrackDataSet::MUONTrackDataSet( const std::string& Name,
                                    const std::string& Title,
                                    MUONTrackDataSet* Data,
                                    const RooArgSet& vars,
                                    const RooFormulaVar* cutVar,
                                    const std::string& cutRange,
                                    int nStart,
                                    int nStop,
                                    Bool_t copyCache,
                                    const std::string& wgtVarName)
  : EvtTrackDataSet(Name,
                    Title,
                    dynamic_cast<MUONTrackDataSet*>(Data),
                    vars,
                    cutVar,
                    cutRange,
                    nStart,
                    nStop,
                    copyCache,
                    wgtVarName)
{
  SetTrackVar( Data->Get_ParamName_DLLmu(),
               "DLLmu");

  SetTrackVar( Data->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Data->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Data->Get_ParamName_nShared(),
               "nShared" );
}

MUONTrackDataSet::MUONTrackDataSet( const std::string& Name,
                                    const std::string& Charge,
                                    MUONTrackDataSet* Numerator,
                                    MUONTrackDataSet* Denominator,
                                    const std::string& WgtVar,
                                    const std::string& Cuts_Num,
                                    const std::string& Cuts_Denom,
                                    const std::string& WgtVar_Num,
                                    const std::string& WgtVar_Denom
                                    )
  : EvtTrackDataSet(Name,
                    Charge,
                    Numerator,
                    Denominator,
                    WgtVar,
                    Cuts_Num,
                    "",
                    WgtVar_Num,
                    WgtVar_Denom
                    )
{
  SetTrackVar( Denominator->Get_ParamName_DLLmu(),
               "DLLmu");
  
  SetTrackVar( Denominator->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Denominator->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Denominator->Get_ParamName_nShared(),
               "nShared" );
  
  if (not Cuts_Denom.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts_Denom).c_str())->store();
  }
}

//=============================================================================
// Destructor
//=============================================================================
MUONTrackDataSet::~MUONTrackDataSet() {}

//=============================================================================
// Append method for MUONTrackDataSet
//=============================================================================
void MUONTrackDataSet::append(MUONTrackDataSet& Data)
{
  assert( Data.Get_ParamName_IsMuon()      == this->Get_ParamName_IsMuon() );
  assert( Data.Get_ParamName_IsMuonLoose() == this->Get_ParamName_IsMuonLoose() );
  assert( Data.Get_ParamName_nShared()     == this->Get_ParamName_nShared() );
  
  //RooDataSet::append(dynamic_cast<RooDataSet&>(Data));
  EvtTrackDataSet::append(dynamic_cast<EvtTrackDataSet&>(Data));

}

//=============================================================================
// Get DLLmu Param Name
//=============================================================================
const std::string MUONTrackDataSet::Get_ParamName_DLLmu() const
{
  return Get_ParamName("DLLmu");
}

//=============================================================================
// Get IsMuon Param Name
//=============================================================================
const std::string MUONTrackDataSet::Get_ParamName_IsMuon() const
{
  return Get_ParamName("IsMuon");
}

//=============================================================================
// Get IsMuonLoose Param Name
//=============================================================================
const std::string MUONTrackDataSet::Get_ParamName_IsMuonLoose() const
{
  return Get_ParamName("IsMuonLoose");
}


//=============================================================================
// Get nShared Param Name
//=============================================================================
const std::string MUONTrackDataSet::Get_ParamName_nShared() const
{
  return Get_ParamName("nShared");
}

//=============================================================================
// Get DLLmu Parameter
//=============================================================================
const RooRealVar* MUONTrackDataSet::Get_Param_DLLmu() const
{
  return Get_Param("DLLmu");
}

//=============================================================================
// Get IsMuon Parameter
//=============================================================================
const RooRealVar* MUONTrackDataSet::Get_Param_IsMuon() const
{
  return Get_Param("IsMuon");
}

//=============================================================================
// Get IsMuonLoose Parameter
//=============================================================================
const RooRealVar* MUONTrackDataSet::Get_Param_IsMuonLoose() const
{
  return Get_Param("IsMuonLoose");
}

//=============================================================================
// Get nShared Parameter
//=============================================================================
const RooRealVar* MUONTrackDataSet::Get_Param_nShared() const
{
  return Get_Param("nShared");
}

//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* MUONTrackDataSet::SetInBinSchema(std::vector<RooBinning*>& BinSchema)
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
RooAbsData* MUONTrackDataSet::reduceEng(const RooArgSet& varSubset,
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
  MUONTrackDataSet* ret = new MUONTrackDataSet( GetName(),
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
