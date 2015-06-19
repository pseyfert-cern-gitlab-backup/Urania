// $Id: $
// Include files
#include <algorithm>
#include <iomanip>
// local
#include "PIDPerfTools/RICHTrackDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RICHTrackDataSet
//
// 2010-12-25 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(RICHTrackDataSet)

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RICHTrackDataSet::RICHTrackDataSet( )
  : EvtTrackDataSet( )
{

}

RICHTrackDataSet::RICHTrackDataSet( const std::string& TrackName,
                                    const std::string& Charge,
                                    RooDataSet* Data,
                                    const RooArgSet& vars,
                                    const std::string& P_Var,
                                    const std::string& PT_Var,
                                    const std::string& ETA_Var,
                                    const std::string& nTrack_Var,
                                    const std::string& DLLK_Var,
                                    const std::string& DLLp_Var,
                                    const std::string& ProbNNK_Name,
                                    const std::string& ProbNNpi_Name,
                                    const std::string& ProbNNp_Name,
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
  SetTrackVar( ProbNNK_Name,
               "ProbNNK");

  SetTrackVar( ProbNNpi_Name,
               "ProbNNpi");

  SetTrackVar( ProbNNp_Name,
               "ProbNNp");
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}

RICHTrackDataSet::RICHTrackDataSet( const std::string& TrackName,
                                    const std::string& Charge,
                                    RICHTrackDataSet* Data,
                                    const RooArgSet& vars,
                                    const std::string& Cuts ,
                                    const std::string& WgtVarName
                                    )
  : EvtTrackDataSet( TrackName,
                     Charge,
                     Data,
                     vars,
                     "",
                     WgtVarName )
{
  SetTrackVar( Data->Get_ParamName_ProbNNK(),
               "ProbNNK" );

  SetTrackVar( Data->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );

  SetTrackVar( Data->Get_ParamName_ProbNNp(),
               "ProbNNp" );
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}


RICHTrackDataSet::RICHTrackDataSet( const std::string& TrackName,
                                    const std::string& Charge,
                                    TTree* Ntuple,
                                    const RooArgSet& Vars,
                                    const std::string& P_Var,
                                    const std::string& PT_Var,
                                    const std::string& ETA_Var,
                                    const std::string& nTrack_Var,
                                    const std::string& DLLK_Var,
                                    const std::string& DLLp_Var,
                                    const std::string& ProbNNK_Name,
                                    const std::string& ProbNNpi_Name,
                                    const std::string& ProbNNp_Name,
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
                     WgtVarName)
{
  SetTrackVar( ProbNNK_Name,
               "ProbNNK");
  
  SetTrackVar( ProbNNpi_Name,
               "ProbNNpi");

  SetTrackVar( ProbNNp_Name,
               "ProbNNp");
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }

}

RICHTrackDataSet::RICHTrackDataSet( const std::string& Name,
                                    const std::string& Title,
                                    RICHTrackDataSet* Data,
                                    const RooArgSet& vars,
                                    const RooFormulaVar* cutVar,
                                    const std::string& cutRange,
                                    int nStart,
                                    int nStop,
                                    Bool_t copyCache,
                                    const std::string& wgtVarName)
  : EvtTrackDataSet(Name,
                    Title,
                    dynamic_cast<RICHTrackDataSet*>(Data),
                    vars,
                    cutVar,
                    cutRange,
                    nStart,
                    nStop,
                    copyCache,
                    wgtVarName) 
{
  SetTrackVar( Data->Get_ParamName_ProbNNK(),
               "ProbNNK" );

  SetTrackVar( Data->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );

  SetTrackVar( Data->Get_ParamName_ProbNNp(),
               "ProbNNp" );
}

RICHTrackDataSet::RICHTrackDataSet( const std::string& Name,
                                    const std::string& Charge,
                                    RICHTrackDataSet* Numerator,
                                    RICHTrackDataSet* Denominator,
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
  SetTrackVar( Denominator->Get_ParamName_ProbNNK(),
               "ProbNNK" );
  
  SetTrackVar( Denominator->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );
  
  SetTrackVar( Denominator->Get_ParamName_ProbNNp(),
               "ProbNNp" );
  
  if (not Cuts_Denom.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts_Denom).c_str())->store();
  }
}

//=============================================================================
// Destructor
//=============================================================================
RICHTrackDataSet::~RICHTrackDataSet() {}

//=============================================================================
// Append method for RICHTrackDataSet
//=============================================================================
void RICHTrackDataSet::append(RICHTrackDataSet& Data)
{
  assert( Data.Get_ParamName_ProbNNK() == this->Get_ParamName_ProbNNK() );
  assert( Data.Get_ParamName_ProbNNpi() == this->Get_ParamName_ProbNNpi() );
  assert( Data.Get_ParamName_ProbNNp() == this->Get_ParamName_ProbNNp() );

  //RooDataSet::append(dynamic_cast<RooDataSet&>(Data));
  EvtTrackDataSet::append(dynamic_cast<EvtTrackDataSet&>(Data));

}

//=============================================================================
// Get ProbNNK Param Name
//=============================================================================
const std::string RICHTrackDataSet::Get_ParamName_ProbNNK() const
{
  return Get_ParamName("ProbNNK");
}


//=============================================================================
// Get ProbNNpi Param Name
//=============================================================================
const std::string RICHTrackDataSet::Get_ParamName_ProbNNpi() const
{
  return Get_ParamName("ProbNNpi");
}

//=============================================================================
// Get ProbNNp Param Name
//=============================================================================
const std::string RICHTrackDataSet::Get_ParamName_ProbNNp() const
{
  return Get_ParamName("ProbNNp");
}

//=============================================================================
// Get ProbNNK Parameter
//=============================================================================
const RooRealVar* RICHTrackDataSet::Get_Param_ProbNNK() const
{
  return Get_Param("ProbNNK");
}

//=============================================================================
// Get ProbNNpi Parameter
//=============================================================================
const RooRealVar* RICHTrackDataSet::Get_Param_ProbNNpi() const
{
  return Get_Param("ProbNNpi");
}

//=============================================================================
// Get ProbNNp Parameter
//=============================================================================
const RooRealVar* RICHTrackDataSet::Get_Param_ProbNNp() const
{
  return Get_Param("ProbNNp");
}

//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* RICHTrackDataSet::SetInBinSchema(std::vector<RooBinning*>& BinSchema)
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
RooAbsData* RICHTrackDataSet::reduceEng(const RooArgSet& varSubset,
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
  RICHTrackDataSet* ret = new RICHTrackDataSet( GetName(),
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
