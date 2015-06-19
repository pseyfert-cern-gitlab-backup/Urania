// $Id: $
// Include files
#include <algorithm>
#include <iomanip>
// local
#include "PIDPerfTools/PIDTrackDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : PIDTrackDataSet
//
// 2010-12-25 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(PIDTrackDataSet)

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
PIDTrackDataSet::PIDTrackDataSet( )
  : EvtTrackDataSet( )
{

}

PIDTrackDataSet::PIDTrackDataSet( const std::string& TrackName,
                                  const std::string& Charge,
                                  RooDataSet* Data,
                                  const RooArgSet& vars,
                                  const std::string& P_Var,
                                  const std::string& PT_Var,
                                  const std::string& ETA_Var,
                                  const std::string& nTrack_Var,
                                  const std::string& nSPDHits_Var,
                                  const std::string& DLLK_Var,
                                  const std::string& DLLp_Var,
                                  const std::string& DLLe_Var,
                                  const std::string& DLLmu_Var,
                                  const std::string& IsMuon_Var,
                                  const std::string& IsMuonLoose_Var,
                                  const std::string& nShared_Var,
                                  const std::string& HasBremAdded_Var,
                                  const std::string& CaloRegion_Var,
                                  const std::string& ProbNNK_Var,
                                  const std::string& ProbNNpi_Var,
                                  const std::string& ProbNNp_Var,
                                  const std::string& ProbNNmu_Var,
                                  const std::string& ProbNNe_Var,
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
                     nSPDHits_Var,
                     DLLK_Var,
                     DLLp_Var,
                     "",
                     WgtVarName
                   )
{
  SetTrackVar( ProbNNK_Var,
               "ProbNNK");
  
  SetTrackVar( ProbNNpi_Var,
               "ProbNNpi");

  SetTrackVar( ProbNNp_Var,
               "ProbNNp");

  SetTrackVar( ProbNNmu_Var,
               "ProbNNmu");

  SetTrackVar( ProbNNe_Var,
               "ProbNNe");

  SetTrackVar( DLLe_Var,
               "DLLe");
  
  SetTrackVar( DLLmu_Var,
               "DLLmu");

  SetTrackVar( IsMuon_Var,
               "IsMuon" );

  SetTrackVar( IsMuonLoose_Var,
               "IsMuonLoose" );

  SetTrackVar( nShared_Var,
               "nShared" ); 

  SetTrackVar( HasBremAdded_Var,
               "HasBremAdded" );

  SetTrackVar( CaloRegion_Var,
               "CaloRegion" ); 
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}

PIDTrackDataSet::PIDTrackDataSet( const std::string& TrackName,
                                  const std::string& Charge,
                                  PIDTrackDataSet* Data,
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
  SetTrackVar( Data->Get_ParamName_ProbNNK(),
               "ProbNNK" );

  SetTrackVar( Data->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );

  SetTrackVar( Data->Get_ParamName_ProbNNp(),
               "ProbNNp" );

  SetTrackVar( Data->Get_ParamName_ProbNNmu(),
               "ProbNNmu" );

  SetTrackVar( Data->Get_ParamName_ProbNNe(),
               "ProbNNe" );

  SetTrackVar( Data->Get_ParamName_DLLe(),
               "DLLe");
  
  SetTrackVar( Data->Get_ParamName_DLLmu(),
               "DLLmu");
  
  SetTrackVar( Data->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Data->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Data->Get_ParamName_nShared(),
               "nShared" );

  SetTrackVar( Data->Get_ParamName_HasBremAdded(),
               "HasBremAdded" );

  SetTrackVar( Data->Get_ParamName_CaloRegion(),
               "CaloRegion" ); 
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}


PIDTrackDataSet::PIDTrackDataSet( const std::string& TrackName,
                                  const std::string& Charge,
                                  TTree* Ntuple,
                                  const RooArgSet& Vars,
                                  const std::string& P_Var,
                                  const std::string& PT_Var,
                                  const std::string& ETA_Var,
                                  const std::string& nTrack_Var,
                                  const std::string& nSPDHits_Var,
                                  const std::string& DLLK_Var,
                                  const std::string& DLLp_Var,
                                  const std::string& DLLe_Var,
                                  const std::string& DLLmu_Var,
                                  const std::string& IsMuon_Var,
                                  const std::string& IsMuonLoose_Var,
                                  const std::string& nShared_Var,
                                  const std::string& HasBremAdded_Var,
                                  const std::string& CaloRegion_Var,
                                  const std::string& ProbNNK_Var,
                                  const std::string& ProbNNpi_Var,
                                  const std::string& ProbNNp_Var,
                                  const std::string& ProbNNmu_Var,
                                  const std::string& ProbNNe_Var,
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
                     nSPDHits_Var,
                     DLLK_Var,
                     DLLp_Var,
                     "",
                     WgtVarName
                   )
{
  SetTrackVar( ProbNNK_Var,
               "ProbNNK");
  
  SetTrackVar( ProbNNpi_Var,
               "ProbNNpi");

  SetTrackVar( ProbNNp_Var,
               "ProbNNp");
  
  SetTrackVar( ProbNNmu_Var,
               "ProbNNmu");
  
  SetTrackVar( ProbNNe_Var,
               "ProbNNe");
  
  SetTrackVar( DLLe_Var,
               "DLLe");

  SetTrackVar( DLLmu_Var,
               "DLLmu");

  SetTrackVar( IsMuon_Var,
               "IsMuon" );

  SetTrackVar( IsMuonLoose_Var,
               "IsMuonLoose" );

  SetTrackVar( nShared_Var,
               "nShared" ); 

  SetTrackVar( HasBremAdded_Var,
               "HasBremAdded" ); 

  SetTrackVar( CaloRegion_Var,
               "CaloRegion" ); 
  
  if (not Cuts.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts).c_str())->store();
  }
}

PIDTrackDataSet::PIDTrackDataSet( const std::string& Name,
                                  const std::string& Title,
                                  PIDTrackDataSet* Data,
                                  const RooArgSet& vars,
                                  const RooFormulaVar* cutVar,
                                  const std::string& cutRange,
                                  int nStart,
                                  int nStop,
                                  Bool_t copyCache,
                                  const std::string& wgtVarName
                                )
  : EvtTrackDataSet(Name,
                    Title,
                    dynamic_cast<PIDTrackDataSet*>(Data),
                    vars,
                    cutVar,
                    cutRange,
                    nStart,
                    nStop,
                    copyCache,
                    wgtVarName
                   )
{
  SetTrackVar( Data->Get_ParamName_ProbNNK(),
               "ProbNNK" );
  
  SetTrackVar( Data->Get_ParamName_ProbNNpi(),
               "ProbNNpi" );
  
  SetTrackVar( Data->Get_ParamName_ProbNNp(),
               "ProbNNp" );

  SetTrackVar( Data->Get_ParamName_ProbNNmu(),
               "ProbNNmu" );

  SetTrackVar( Data->Get_ParamName_ProbNNe(),
               "ProbNNe" );

  SetTrackVar( Data->Get_ParamName_DLLe(),
               "DLLe");

  SetTrackVar( Data->Get_ParamName_DLLmu(),
               "DLLmu");
  
  SetTrackVar( Data->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Data->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Data->Get_ParamName_nShared(),
               "nShared" );

  SetTrackVar( Data->Get_ParamName_HasBremAdded(),
               "HasBremAdded" );

  SetTrackVar( Data->Get_ParamName_CaloRegion(),
               "CaloRegion" ); 
}

PIDTrackDataSet::PIDTrackDataSet( const std::string& Name,
                                  const std::string& Charge,
                                  PIDTrackDataSet* Numerator,
                                  PIDTrackDataSet* Denominator,
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
  
  SetTrackVar( Denominator->Get_ParamName_ProbNNmu(),
               "ProbNNmu" );
    
  SetTrackVar( Denominator->Get_ParamName_ProbNNe(),
               "ProbNNe" );
  
  SetTrackVar( Denominator->Get_ParamName_DLLe(),
               "DLLe");
  
  SetTrackVar( Denominator->Get_ParamName_DLLmu(),
               "DLLmu");
  
  SetTrackVar( Denominator->Get_ParamName_IsMuon(),
               "IsMuon" );

  SetTrackVar( Denominator->Get_ParamName_IsMuonLoose(),
               "IsMuonLoose" );

  SetTrackVar( Denominator->Get_ParamName_nShared(),
               "nShared" );

  SetTrackVar( Denominator->Get_ParamName_HasBremAdded(),
               "HasBremAdded" );

  SetTrackVar( Denominator->Get_ParamName_CaloRegion(),
               "CaloRegion" ); 
  
  if (not Cuts_Denom.empty()) {
    _dstore = this->reduce(FormatCutList(Cuts_Denom).c_str())->store();
  }
}

//=============================================================================
// Destructor
//=============================================================================
PIDTrackDataSet::~PIDTrackDataSet() {}

//=============================================================================
// Append method for PIDTrackDataSet
//=============================================================================
void PIDTrackDataSet::append(PIDTrackDataSet& Data)
{
  assert( Data.Get_ParamName_ProbNNK() == this->Get_ParamName_ProbNNK() );
  assert( Data.Get_ParamName_ProbNNpi() == this->Get_ParamName_ProbNNpi() );
  assert( Data.Get_ParamName_ProbNNp() == this->Get_ParamName_ProbNNp() );
  assert( Data.Get_ParamName_ProbNNmu() == this->Get_ParamName_ProbNNmu() );
  assert( Data.Get_ParamName_ProbNNe() == this->Get_ParamName_ProbNNe() );
  assert( Data.Get_ParamName_DLLe() == this->Get_ParamName_DLLe() );
  assert( Data.Get_ParamName_DLLmu() == this->Get_ParamName_DLLmu() );
  assert( Data.Get_ParamName_IsMuon() == this->Get_ParamName_IsMuon() );
  assert( Data.Get_ParamName_IsMuonLoose() == this->Get_ParamName_IsMuonLoose() );
  assert( Data.Get_ParamName_nShared() == this->Get_ParamName_nShared() );
  assert( Data.Get_ParamName_HasBremAdded() == this->Get_ParamName_HasBremAdded() );
  assert( Data.Get_ParamName_CaloRegion() == this->Get_ParamName_CaloRegion() );

  //RooDataSet::append(dynamic_cast<RooDataSet&>(Data));
  EvtTrackDataSet::append(dynamic_cast<EvtTrackDataSet&>(Data));

}

//=============================================================================
// Get ProbNNK Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_ProbNNK() const
{
  return Get_ParamName("ProbNNK");
}


//=============================================================================
// Get ProbNNpi Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_ProbNNpi() const
{
  return Get_ParamName("ProbNNpi");
}

//=============================================================================
// Get ProbNNp Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_ProbNNp() const
{
  return Get_ParamName("ProbNNp");
}

//=============================================================================
// Get ProbNNmu Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_ProbNNmu() const
{
  return Get_ParamName("ProbNNmu");
}

//=============================================================================
// Get ProbNNe Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_ProbNNe() const
{
  return Get_ParamName("ProbNNe");
}

//=============================================================================
// Get DLLe Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_DLLe() const
{
  return Get_ParamName("DLLe");
}

//=============================================================================
// Get DLLmu Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_DLLmu() const
{
  return Get_ParamName("DLLmu");
}

//=============================================================================
// Get IsMuon Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_IsMuon() const
{
  return Get_ParamName("IsMuon");
}

//=============================================================================
// Get IsMuonLoose Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_IsMuonLoose() const
{
  return Get_ParamName("IsMuonLoose");
}

//=============================================================================
// Get nShared Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_nShared() const
{
  return Get_ParamName("nShared");
}

//=============================================================================
// Get HasBremAdded Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_HasBremAdded() const
{
  return Get_ParamName("HasBremAdded");
}

//=============================================================================
// Get CaloRegion Param Name
//=============================================================================
const std::string PIDTrackDataSet::Get_ParamName_CaloRegion() const
{
  return Get_ParamName("CaloRegion");
}


//=============================================================================
// Get ProbNNK Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_ProbNNK() const
{
  return Get_Param("ProbNNK");
}

//=============================================================================
// Get ProbNNpi Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_ProbNNpi() const
{
  return Get_Param("ProbNNpi");
}

//=============================================================================
// Get ProbNNp Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_ProbNNp() const
{
  return Get_Param("ProbNNp");
}

//=============================================================================
// Get ProbNNmu Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_ProbNNmu() const
{
  return Get_Param("ProbNNmu");
}

//=============================================================================
// Get ProbNNe Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_ProbNNe() const
{
  return Get_Param("ProbNNe");
}

//=============================================================================
// Get DLLe Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_DLLe() const
{
  return Get_Param("DLLe");
}

//=============================================================================
// Get DLLmu Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_DLLmu() const
{
  return Get_Param("DLLmu");
}

//=============================================================================
// Get IsMuon Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_IsMuon() const
{
  return Get_Param("IsMuon");
}

//=============================================================================
// Get IsMuonLoose Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_IsMuonLoose() const
{
  return Get_Param("IsMuonLoose");
}

//=============================================================================
// Get nShared Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_nShared() const
{
  return Get_Param("nShared");
}

//=============================================================================
// Get HasBremAdded Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_HasBremAdded() const
{
  return Get_Param("HasBremAdded");
}

//=============================================================================
// Get CaloRegion Parameter
//=============================================================================
const RooRealVar* PIDTrackDataSet::Get_Param_CaloRegion() const
{
  return Get_Param("CaloRegion");
}

//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* PIDTrackDataSet::SetInBinSchema(std::vector<RooBinning*>& BinSchema)
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
RooAbsData* PIDTrackDataSet::reduceEng(const RooArgSet& varSubset,
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
  PIDTrackDataSet* ret = new PIDTrackDataSet( GetName(),
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
