// $Id: $
// Include files
#include <algorithm>
#include <iomanip>

// local
#include "PIDPerfTools/TrackDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TrackDataSet
//
// 2010-12-25 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(TrackDataSet)

using std::cout;
using std::endl;

//=============================================================================
// Overloaded operators
//=============================================================================
void* TrackDataSet::operator new (size_t bytes)
{
  return RooDataSet::operator new(bytes);
}

void* TrackDataSet::operator new (size_t bytes, void *p)
{
  return TObject::operator new(bytes, p);
}

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TrackDataSet::TrackDataSet( )
  : RooDataSet( )
{

}

TrackDataSet::TrackDataSet( const std::string& TrackName,
                            const std::string& Charge,
                            RooDataSet* Data,
                            const RooArgSet& vars,
                            const std::string& P_Var,
                            const std::string& PT_Var,
                            const std::string& ETA_Var,
                            const std::string& DLLK_Var,
                            const std::string& DLLp_Var,
                            const std::string& Cuts,
                            const std::string& WgtVarName
                            ) 
  : RooDataSet( TrackName.c_str(),
                Data->GetTitle(),
                Data,
                vars,
                Cuts.empty()       ? NULL : Cuts.c_str(),
                WgtVarName.empty() ? NULL : WgtVarName.c_str() ),
    m_Charge( Charge )
    
{
  SetTrackVar( P_Var,
               "P" );
  SetTrackVar( PT_Var,
               "PT" );
  SetTrackVar( ETA_Var,
               "ETA" );
  SetTrackVar( DLLK_Var,
               "DLLK" );
  SetTrackVar( DLLp_Var,
               "DLLp" );
  SetTrackVar_DLLpK( DLLp_Var,
                     DLLK_Var,
                     "DLLpK" );
}



TrackDataSet::TrackDataSet( const std::string& TrackName,
                            const std::string& Charge,
                            TrackDataSet* Data,
                            const RooArgSet& vars,
                            const std::string& Cuts ,
                            const std::string& WgtVarName
                            )
  : RooDataSet( TrackName.c_str(),
                Data->GetTitle(),
                Data,
                vars,
                Cuts.empty()       ? NULL : Cuts.c_str(),
                WgtVarName.empty() ? NULL : WgtVarName.c_str() ),
    m_Charge( Charge )
{
  SetTrackVar( Data->Get_ParamName_P(),
               "P" );
  SetTrackVar( Data->Get_ParamName_PT(),
               "PT" );
  SetTrackVar( Data->Get_ParamName_ETA(),
               "ETA" );
  SetTrackVar( Data->Get_ParamName_DLLK(),
               "DLLK" );
  SetTrackVar( Data->Get_ParamName_DLLp(),
               "DLLp" ); 
  SetTrackVar( Data->Get_ParamName_DLLpK(),
               "DLLpK" );
}


TrackDataSet::TrackDataSet( const std::string& TrackName, 
                            const std::string& Charge, 
                            TTree* Ntuple, 
                            const RooArgSet& Vars,
                            const std::string& P_Var,
                            const std::string& PT_Var,
                            const std::string& ETA_Var,
                            const std::string& DLLK_Var,
                            const std::string& DLLp_Var,
                            const std::string& Cuts, 
                            const std::string& WgtVarName
                            )
  : RooDataSet( TrackName.c_str(), 
                Charge.c_str(), 
                Ntuple, 
                Vars, 
                Cuts.empty()       ? NULL : Cuts.c_str(), 
                WgtVarName.empty() ? NULL : WgtVarName.c_str() ),
    m_Charge( Charge ) 
{
  SetTrackVar( P_Var,
               "P" );
  SetTrackVar( PT_Var,
               "PT" );
  SetTrackVar( ETA_Var,
               "ETA" );
  SetTrackVar( DLLK_Var,
               "DLLK" );
  SetTrackVar( DLLp_Var,
               "DLLp" );
  SetTrackVar_DLLpK( DLLp_Var,
                     DLLK_Var,
                     "DLLpK" );  
}

TrackDataSet::TrackDataSet( const std::string& Name, 
                            const std::string& Title, 
                            TrackDataSet* Data, 
                            const RooArgSet& vars, 
                            const RooFormulaVar* cutVar, 
                            const std::string& cutRange, 
                            int nStart, 
                            int nStop, 
                            Bool_t copyCache, 
                            const std::string& wgtVarName)
  : RooDataSet(Name.c_str(),
               Title.c_str(),
               dynamic_cast<RooDataSet*>(Data),
               vars,
               cutVar,
               cutRange.c_str(),
               nStart,
               nStop,
               copyCache,
               wgtVarName.empty() ? NULL : wgtVarName.c_str() ),
    m_Charge( Data->m_Charge )
{
  SetTrackVar( Data->Get_ParamName_P(),
               "P");
  SetTrackVar( Data->Get_ParamName_PT(),
               "PT");
  SetTrackVar( Data->Get_ParamName_ETA(),
               "ETA");
  SetTrackVar( Data->Get_ParamName_DLLK(),
               "DLLK");
  SetTrackVar( Data->Get_ParamName_DLLp(),
               "DLLp");
  SetTrackVar(Data->Get_ParamName_DLLpK(),
              "DLLpK" );
}

TrackDataSet::TrackDataSet( const std::string& Name,
                            const std::string& Charge,
                            TrackDataSet* Numerator,
                            TrackDataSet* Denominator,
                            const std::string& WgtVar,
                            const std::string& Cuts_Num,
                            const std::string& Cuts_Denom,
                            const std::string& WgtVar_Num, 
                            const std::string& WgtVar_Denom
                            )
  : RooDataSet(Name.c_str(), 
               Charge.c_str(),
               Denominator,
               *Denominator->get(),
               Cuts_Denom.empty() ? NULL : Cuts_Denom.c_str(),
               0),
    m_Charge( Charge ) 
{ 

  RooRealVar* Weight_Var = NULL;

  TrackDataSet* _NumAll = new TrackDataSet( Numerator->GetName(),
                                            Numerator->GetTitle(),
                                            Numerator,
                                            *Numerator->get(),
                                            0,
                                            WgtVar_Num
                                            );
  
  TrackDataSet* _DenomAll = new TrackDataSet( Denominator->GetName(),
                                              Denominator->GetTitle(),
                                              Denominator,
                                              *Denominator->get(),
                                              0,
                                              WgtVar_Denom
                                              );
  // Normalisation
  Double_t _NumTot   = _NumAll->sumEntries();
  Double_t _DenomTot = _DenomAll->sumEntries();
  
  delete _NumAll;
  delete _DenomAll;

  if ( !WgtVar_Denom.empty() )
  {
    Weight_Var = (RooRealVar*)(Denominator->get())->find(WgtVar_Denom.c_str());
    if(Weight_Var == NULL)
    {
      cout<<"**ERROR** "<<Weight_Var<<" is not in DataSet"<<endl;
      RooErrorHandler::softAbort();
    }
  }

  TrackDataSet* _Num = new TrackDataSet( Numerator->GetName(),
                                         Numerator->GetTitle(),
                                         Numerator,
                                         *Numerator->get(),
                                         Cuts_Num,
                                         WgtVar_Num
                                         );
  
  TrackDataSet* _Denom = new TrackDataSet( Denominator->GetName(),
                                           Denominator->GetTitle(),
                                           Denominator,
                                           *Denominator->get(),
                                           Cuts_Denom,
                                           WgtVar_Denom
                                           );
  
  Double_t ratio =  (_Num->sumEntries()/_Denom->sumEntries())*_DenomTot/_NumTot ;
  delete _Num;
  delete _Denom;

  RooRealVar wValue( "wValue", "", ratio );

  TString Formula = WgtVar_Denom.empty() ? "wValue" : TString(WgtVar_Denom.c_str())+"*wValue";
  
  RooFormulaVar wFunc( WgtVar.c_str(),
                       "event weight",
                       Formula.Data(),
                       RooArgList(*Weight_Var,
                                  wValue) );

  SetTrackVar( Denominator->Get_ParamName_P(),
               "P");
  SetTrackVar( Denominator->Get_ParamName_PT(),
               "PT");
  SetTrackVar( Denominator->Get_ParamName_ETA(),
               "ETA");
  SetTrackVar( Denominator->Get_ParamName_DLLK(),
               "DLLK");
  SetTrackVar( Denominator->Get_ParamName_DLLp(),
               "DLLp");
  SetTrackVar_DLLpK( Denominator->Get_ParamName_DLLp(),
                     Denominator->Get_ParamName_DLLK(),
                     "DLLpK" );

  this->addColumn(wFunc) ;  
}

//=============================================================================
// Destructor
//=============================================================================
TrackDataSet::~TrackDataSet() {}

//=============================================================================
// Get track charge
//=============================================================================
const TString TrackDataSet::GetCharge() const
{
  return TString(m_Charge);  
}

//=============================================================================
// Define track variable
//=============================================================================
void TrackDataSet::SetTrackVar( const std::string& InputName,
                                std::string InternalName )
{
  // Get parameter list and pointer to parameter with name 'InputName'
  const RooArgSet* vars = this->get(); 
  
  if(vars->find(InputName.c_str()))
  {
    m_ParamMap.insert( make_pair(InternalName,
                                 (RooRealVar*)vars->find(InputName.c_str())) );
  }
  else
  {
    cout<<"***ERROR*** "<<InputName<<" is not in DataSet"<<endl;
    RooErrorHandler::softAbort();
  }

}

//=============================================================================
// Define track variable DLLpK and add to the DataSet
//=============================================================================
void TrackDataSet::SetTrackVar_DLLpK( const std::string& InputName_DLLp,
                                      const std::string& InputName_DLLK,
                                      std::string InternalName)
{
  // Get parameter list and pointer to parameter with name 'InputName'
  const RooArgSet* vars = this->get(); 
  
  try
  {  
    if(!vars->find(InputName_DLLp.c_str()) )
    {
      throw InputName_DLLp;
    }
    
    if(!vars->find(InputName_DLLK.c_str()) )
    {
      throw InputName_DLLK;
    }
  }
  catch( std::string& variable)
  {
    cout<<"***ERROR*** "<<variable<<" is not in DataSet"<<endl;
    RooErrorHandler::softAbort();
  }
  
  RooRealVar* DLLp = (RooRealVar*)vars->find(InputName_DLLp.c_str());
  RooRealVar* DLLK = (RooRealVar*)vars->find(InputName_DLLK.c_str());
  
  RooFormulaVar DLLpK("My_DLLpK",
                      "DLL(p - K)", 
                      "@0 - @1",
                      RooArgSet(*DLLp,*DLLK));
  
  if(!vars->find("My_DLLpK"))
  {
    this->addColumn(DLLpK);
  }

  m_ParamMap.insert( make_pair(InternalName,
                               (RooRealVar*)vars->find("My_DLLpK")) );
}

//=============================================================================
// Append method for TrackDataSet
//=============================================================================
void TrackDataSet::append(TrackDataSet& Data)
{
  assert( Data.Get_ParamName_P() == Get_ParamName_P() );
  assert( Data.Get_ParamName_PT() == Get_ParamName_PT() );
  assert( Data.Get_ParamName_ETA() == Get_ParamName_ETA() );
  assert( Data.Get_ParamName_DLLK() == Get_ParamName_DLLK() );
  assert( Data.Get_ParamName_DLLp() == Get_ParamName_DLLp() );
  assert( Data.Get_ParamName_DLLpK() == Get_ParamName_DLLpK() );

  RooDataSet::append(dynamic_cast<RooDataSet&>(Data));   
}

//=============================================================================
// Get Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName(const std::string& Internal_Name) const 
{
  std::map<std::string, RooRealVar*>::const_iterator iter;

  iter = m_ParamMap.find(std::string(Internal_Name));

  if(iter==m_ParamMap.end())
  {
    cout<<"**ERROR** "<<Internal_Name<<" not known."<<endl;
    RooErrorHandler::softAbort();
  }
  
  return iter->second->GetName();
}

//=============================================================================
// Get P Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName_P() const 
{
  return Get_ParamName("P");
}

//=============================================================================
// Get PT Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName_PT() const 
{
  return Get_ParamName("PT");
}

//=============================================================================
// Get ETA Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName_ETA() const 
{
  return Get_ParamName("ETA");
}

//=============================================================================
// Get DLLK Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName_DLLK() const 
{
  return Get_ParamName("DLLK");
}

//=============================================================================
// Get DLLp Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName_DLLp() const 
{
  return Get_ParamName("DLLp");
}

//=============================================================================
// Get DLLpK Param Name
//=============================================================================
const std::string TrackDataSet::Get_ParamName_DLLpK() const 
{
  return Get_ParamName("DLLpK");
}


//=============================================================================
// Get Parameter
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param(const std::string& Internal_Name) const 
{
  std::map<std::string, RooRealVar*>::const_iterator iter;

  iter = m_ParamMap.find(std::string(Internal_Name));

  if(iter==m_ParamMap.end())
  {
    cout<<"**ERROR** "<<Internal_Name<<" not known."<<endl;
    RooErrorHandler::softAbort();
  }
  
  return iter->second;
}

//=============================================================================
// Get P Parameter
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param_P() const 
{
  return Get_Param("P");
}

//=============================================================================
// Get PT Param Name
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param_PT() const 
{
  return Get_Param("PT");
}

//=============================================================================
// Get ETA Param Name
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param_ETA() const 
{
  return Get_Param("ETA");
}

//=============================================================================
// Get DLLK Param Name
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param_DLLK() const 
{
  return Get_Param("DLLK");
}

//=============================================================================
// Get DLLp Param Name
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param_DLLp() const  
{
  return Get_Param("DLLp");
}

//=============================================================================
// Get DLLpK Param Name
//=============================================================================
const RooRealVar* TrackDataSet::Get_Param_DLLpK() const  
{
  return Get_Param("DLLpK");
}
  


//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns 
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* TrackDataSet::SetInBinSchema(const std::vector<RooBinning*>& BinSchema)
{
  std::vector<RooBinning*>::const_iterator itr_Binning;

  std::list<std::pair<std::string, RooBinning*> > BinDefs;

  for ( itr_Binning = BinSchema.begin(); itr_Binning != BinSchema.end(); ++itr_Binning)
  {
    const std::string name = this->Get_ParamName((*itr_Binning)->GetName());
    BinDefs.push_back( make_pair(name,*itr_Binning) );
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
RooAbsData* TrackDataSet::reduceEng(const RooArgSet& varSubset, 
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

  // Really would like to pass cuts applied to the 'know' parameter names:
  // - P, PT, Eta, DLLK, DLLp 
  // Not clear how best to do this?
  
  TrackDataSet* ret =  new TrackDataSet(std::string(GetName()), 
                                        std::string(GetTitle()), 
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
