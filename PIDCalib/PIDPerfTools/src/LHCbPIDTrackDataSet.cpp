// Include files
#include <algorithm>
#include <iomanip>
// local
#include "PIDPerfTools/LHCbPIDTrackDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : LHCbPIDTrackDataSet
//
// 2013-02-24 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(LHCbPIDTrackDataSet)

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
LHCbPIDTrackDataSet::LHCbPIDTrackDataSet(  )
  : EvtTrackDataSet(),
  RICHTrackDataSet(),
  MUONTrackDataSet()
{
  
}

LHCbPIDTrackDataSet::LHCbPIDTrackDataSet( const std::string& TrackName,
                                          const std::string& Charge,
                                          RooDataSet* Data,
                                          const RooArgSet& vars,
                                          const std::string& P_Var,
                                          const std::string& PT_Var,
                                          const std::string& ETA_Var,
                                          const std::string& nTrack_Var,
                                          const std::string& DLLK_Var,
                                          const std::string& DLLp_Var,
                                          const std::string& DLLe_Var,
                                          const std::string& DLLmu_Var,
                                          const std::string& IsMuon_Var,
                                          const std::string& IsMuonLoose_Var,
                                          const std::string& nShared_Var,
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
                     WgtVarName
                   )
    //    RICHTrackDataSet(),
    //    MUONTrackDataSet()
{
  SetTrackVar( ProbNNK_Name,
               "ProbNNK");
  
  SetTrackVar( ProbNNpi_Name,
               "ProbNNpi");
  
  SetTrackVar( ProbNNp_Name,
               "ProbNNp");
  
  SetTrackVar( DLLmu_Var,
               "DLLmu");

  SetTrackVar( DLLe_Var,
               "DLLe");
  
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

LHCbPIDTrackDataSet::LHCbPIDTrackDataSet( const std::string& TrackName,
                                          const std::string& Charge,
                                          LHCbPIDTrackDataSet* Data,
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
                   ),
    RICHTrackDataSet(),
    MUONTrackDataSet()
{
  SetTrackVar( Data->Get_ParamName_ProbNNK(),
               "ProbNNK" );
  
  SetTrackVar( Data->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );
  
  SetTrackVar( Data->Get_ParamName_ProbNNp(),
               "ProbNNp" );
  
  SetTrackVar( Data->Get_ParamName_DLLmu(),
               "DLLmu");
  
  SetTrackVar( Data->Get_ParamName_DLLe(),
               "DLLe");
  
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

LHCbPIDTrackDataSet::LHCbPIDTrackDataSet( const std::string& Name,
                                          const std::string& Title,
                                          LHCbPIDTrackDataSet* Data,
                                          const RooArgSet& vars,
                                          const RooFormulaVar* cutVar,
                                          const std::string& cutRange,
                                          int nStart,
                                          int nStop,
                                          Bool_t copyCache,
                                          const std::string& wgtVarName)
  : EvtTrackDataSet(Name,
                    Title,
                    dynamic_cast<LHCbPIDTrackDataSet*>(Data),
                    vars,
                    cutVar,
                    cutRange,
                    nStart,
                    nStop,
                    copyCache,
                    wgtVarName),
    RICHTrackDataSet(),
    MUONTrackDataSet()
{
  SetTrackVar( Data->Get_ParamName_ProbNNK(),
               "ProbNNK" );
  
  SetTrackVar( Data->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );
  
  SetTrackVar( Data->Get_ParamName_ProbNNp(),
               "ProbNNp" );

  SetTrackVar( Data->Get_ParamName_DLLmu(),
               "DLLmu");

  SetTrackVar( Data->Get_ParamName_DLLe(),
               "DLLe");
  
  SetTrackVar( Data->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Data->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Data->Get_ParamName_nShared(),
               "nShared" );
}

/*
LHCbPIDTrackDataSet::LHCbPIDTrackDataSet( const std::string& Name,
                                          const std::string& Charge,
                                          LHCbPIDTrackDataSet* Numerator,
                                          LHCbPIDTrackDataSet* Denominator,
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
                    Cuts_Denom,
                    WgtVar_Num,
                    WgtVar_Denom
                    ),
    RICHTrackDataSet(),
    MUONTrackDataSet()
{
  SetTrackVar( Denominator->Get_ParamName_ProbNNK(),
               "ProbNNK" );
  
  SetTrackVar( Denominator->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );
  
  SetTrackVar( Denominator->Get_ParamName_ProbNNp(),
               "ProbNNp" );

  SetTrackVar( Denominator->Get_ParamName_DLLmu(),
               "DLLmu");

  SetTrackVar( Denominator->Get_ParamName_DLLe(),
               "DLLe");
  
  SetTrackVar( Denominator->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Denominator->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Denominator->Get_ParamName_nShared(),
               "nShared" );
}
*/
//=============================================================================
// Destructor
//=============================================================================
LHCbPIDTrackDataSet::~LHCbPIDTrackDataSet() {} 

//=============================================================================
// Append method for LHCbPIDTrackDataSet
//=============================================================================
void LHCbPIDTrackDataSet::append(LHCbPIDTrackDataSet& Data)
{
  RICHTrackDataSet::append(dynamic_cast<RICHTrackDataSet&>(Data));
  MUONTrackDataSet::append(dynamic_cast<MUONTrackDataSet&>(Data));
}

//=============================================================================
// Get DLLe Param Name
//=============================================================================
const std::string LHCbPIDTrackDataSet::Get_ParamName_DLLe() const
{
  return Get_ParamName("DLLe");
}

//=============================================================================
// Get DLLe Parameter
//=============================================================================
const RooRealVar* LHCbPIDTrackDataSet::Get_Param_DLLe() const
{
  return Get_Param("DLLe");
}

//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* LHCbPIDTrackDataSet::SetInBinSchema(std::vector<RooBinning*>& BinSchema)
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
RooAbsData* LHCbPIDTrackDataSet::reduceEng(const RooArgSet& varSubset,
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
  LHCbPIDTrackDataSet* ret = new LHCbPIDTrackDataSet( GetName(),
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
