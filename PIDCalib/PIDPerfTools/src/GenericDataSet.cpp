// $Id: $
// Include files
#include <algorithm>
#include <iomanip>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/foreach.hpp>

// local
#include "PIDPerfTools/GenericDataSet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : GenericDataSet
//
// 2010-12-25 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//ClassImp(GenericDataSet)

using std::cout;
using std::endl;

namespace PIDCalib 
{
  struct length 
  {
    bool operator() ( const std::string& a, const std::string& b )
    {
      return a.size() < b.size();   
    } 
  };

  struct strToDouble
  {
    double operator() ( const std::string& s )
    {
      return boost::lexical_cast<double>(s);
    }
  };
}

//=============================================================================
// Overloaded operators
//=============================================================================
void* GenericDataSet::operator new (size_t bytes)
{
  return RooDataSet::operator new(bytes);
}

void* GenericDataSet::operator new (size_t bytes, void *p)
{
  return TObject::operator new(bytes, p);
}

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
GenericDataSet::GenericDataSet( )
  : RooDataSet( )
{

}

GenericDataSet::GenericDataSet( const std::string& TrackName,
                            RooDataSet* Data,
                            const RooArgSet& vars,
                            const std::vector< std::pair< std::string,std::string > >& VarAliases,
                            const std::string& Cuts,
                            const std::string& WgtVarName
                            ) 
  : RooDataSet( TrackName.c_str(),
                Data->GetTitle(),
                Data,
                vars,
                NULL,
                WgtVarName.empty() ? NULL : WgtVarName.c_str() ),
    m_Aliases( VarAliases )
    
{
  SetTrackVars( VarAliases );
  
  if (not Cuts.empty()) {
//     RooDataSet* dset = this->reduce(FormatCutList(Cuts).c_str());
    
    _dstore = new RooTreeDataStore(fName.Data(),fTitle.Data(),_vars,*_dstore,FormatCutList(Cuts).c_str(),WgtVarName.c_str()) ;

    appendToDir(this,kTRUE) ;
    
    if (WgtVarName.c_str()) {
      // Use the supplied weight column
      initialize(WgtVarName.c_str()) ;    
    } else {
      if (_wgtVar && vars.find(_wgtVar->GetName())) {
        // Use the weight column of the source data set
        initialize(_wgtVar->GetName()) ;
      } else {
        initialize(0) ;
      }
    }
  }
  
}



GenericDataSet::GenericDataSet( const std::string& TrackName,
                            GenericDataSet* Data,
                            const RooArgSet& vars,
                            const std::string& Cuts ,
                            const std::string& WgtVarName
                            )
  : RooDataSet( TrackName.c_str(),
                Data->GetTitle(),
                Data,
                vars,
                NULL,
                WgtVarName.empty() ? NULL : WgtVarName.c_str() ),
    m_Aliases( *Data->Get_Aliases() )
{
  SetTrackVars( *(Data->Get_Aliases()) );
  
  if (not Cuts.empty()) {
//     RooDataSet* dset = this->reduce(FormatCutList(Cuts).c_str());
    
    _dstore = new RooTreeDataStore(fName.Data(),fTitle.Data(),_vars,*_dstore,FormatCutList(Cuts).c_str(),WgtVarName.c_str()) ;

    appendToDir(this,kTRUE) ;
    
    if (WgtVarName.c_str()) {
      // Use the supplied weight column
      initialize(WgtVarName.c_str()) ;    
    } else {
      if (_wgtVar && vars.find(_wgtVar->GetName())) {
        // Use the weight column of the source data set
        initialize(_wgtVar->GetName()) ;
      } else {
        initialize(0) ;
      }
    }
  }
  
}

GenericDataSet::GenericDataSet( const std::string& Name, 
                            const std::string& Title, 
                            GenericDataSet* Data, 
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
    m_Aliases( *Data->Get_Aliases() )
{
  SetTrackVars( *(Data->Get_Aliases()) );
}

//=============================================================================
// Destructor
//=============================================================================
GenericDataSet::~GenericDataSet() {}

//=============================================================================
// Get track charge
//=============================================================================
const std::vector< std::pair< std::string, std::string > >* GenericDataSet::Get_Aliases() const
{
  return &m_Aliases;  
}

//=============================================================================
// Define track variable
//=============================================================================
void GenericDataSet::SetTrackVars( const std::vector< std::pair< std::string,std::string > >& VarAliases )
{
  std::pair<std::string,std::string> alias;
  BOOST_FOREACH(alias, VarAliases) {
    SetTrackVar(alias.second, alias.first);
  }
}

//=============================================================================
// Define track variable
//=============================================================================
void GenericDataSet::SetTrackVar( const std::string& InputName,
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
    cout<<"WARNING: "<<InputName<<" is not in DataSet"<<endl;
//     RooErrorHandler::softAbort();
  }

}

//=============================================================================
// Define track variable DLLpK and add to the DataSet
//=============================================================================
void GenericDataSet::SetTrackVar_DLLpK( const std::string& InputName_DLLp,
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
// Append method for GenericDataSet
//=============================================================================
void GenericDataSet::append(GenericDataSet& Data)
{
  const std::vector< std::pair< std::string, std::string > >* Data_Aliases = Data.Get_Aliases();
  
  assert(m_Aliases.size() == Data_Aliases->size());
  
  std::pair<std::string,std::string> Data_Pair, Local_Pair;
  BOOST_FOREACH(Data_Pair, *Data_Aliases) {
    bool Var_Found = false;
    BOOST_FOREACH(Local_Pair, m_Aliases) {
      if (Data_Pair.first == Local_Pair.first) {
        Var_Found = true;
        assert(Data_Pair.second == Local_Pair.second);
      }
    }
    assert(Var_Found);
    _unused(Var_Found);
  }

  RooDataSet::append(dynamic_cast<RooDataSet&>(Data));   
}

//=============================================================================
// Get Param Name
//=============================================================================
const std::string GenericDataSet::Get_ParamName(const std::string& Internal_Name) const 
{
  std::map<std::string, RooRealVar*>::const_iterator iter;

  iter = m_ParamMap.find(std::string(Internal_Name));

  if(iter==m_ParamMap.end())
  {
    cout << "**ERROR** In GenericDataSet::Get_ParamName:    " 
         << "internal parameter name '" << Internal_Name 
         << "' not known." << endl;
    RooErrorHandler::softAbort();
  }
  
  return iter->second->GetName();
}


//=============================================================================
// Get Parameter
//=============================================================================
const RooRealVar* GenericDataSet::Get_Param(const std::string& Internal_Name) const 
{
  std::map<std::string, RooRealVar*>::const_iterator iter;

  iter = m_ParamMap.find(std::string(Internal_Name));

  if(iter==m_ParamMap.end())
  {
    cout<<"**ERROR** In GenericDataSet::Get_Param:    internal parameter name '"
        <<Internal_Name<<"' not known."<<endl;
    RooErrorHandler::softAbort();
  }
  
  return iter->second;
} 


//=============================================================================
// An additional reduce method that takes a vector of  RooBinnings and returns 
// all those events within the global acceptance of the Binning schema
//=============================================================================
RooAbsData* GenericDataSet::SetInBinSchema(const std::vector<RooBinning*>& BinSchema)
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
RooAbsData* GenericDataSet::reduceEng(const RooArgSet& varSubset, 
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
  
  GenericDataSet* ret =  new GenericDataSet(std::string(GetName()), 
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



//=============================================================================
// Split composite cut string into individual cuts. Here we assumme the 
// individual cuts are separated by the Boolean logic operator '&&'.
//=============================================================================
void GenericDataSet::SplitCut( const std::string& Cut,
                                  std::vector< std::string >& SplitVec)
{
  boost::split( SplitVec, Cut, boost::is_any_of("&&") ); 
  
  // Above split command erroneously fills SplitVec with empty strings, in 
  // addition to the wanted sub strings. To correct for this, it is therefore 
  // necessary to remove these entries.

  SplitVec.erase( std::remove_if( SplitVec.begin(), SplitVec.end(), 
                                  boost::bind( &std::string::empty, _1 ) ), 
                  SplitVec.end() );
}

//=============================================================================
// Translate a cut on (P, PT, ETA, DLLK, DLLp, DLLKp) into a cut on the defined
// corresponding GenericDataSet variable
//=============================================================================
const std::string GenericDataSet::TranslateCut( const std::string& Cut )
{
  std::string s(Cut), sre, ret;
  boost::regex re;
  boost::cmatch matches;

  //sre = "\\s*(\\w+)\\s*([>=<!]{1,2})\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*";
  //sre = "\\s*(\\D+)\\s*([>=<!]{1,2})\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*";
  sre = "\\s*(.+)\\s*([>=<!]{1,2})\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*";

  try
  {
    // Assignment and construction initialize the FSM used
    // for regexp parsing
    re = sre;
  }

  catch (boost::regex_error& e)
  {
    std::cout << sre << " is not a valid regular expression: \""
         << e.what() << "\"" << std::endl;
  }

  if (boost::regex_match(s.c_str(), matches, re))
  {
    //std::cout<<"Found a match"<<std::endl;
    // matches[0] contains the original string.  matches[n]
    // contains a sub_match object for each matching
    // subexpression
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      // sub_match::first and sub_match::second are iterators that
      // refer to the first and one past the last chars of the
      // matching subexpression
      std::string match(matches[i].first, matches[i].second);

      //std::cout << "\tmatches[" << i << "] = " << match << std::endl;
    }
    
    //If all matches found, format the cut string
    if (matches.size()==4)
    {
      std::string A, B, C;
      A.assign(matches[1].first, matches[1].second);
      B.assign(matches[2].first, matches[2].second);
      C.assign(matches[3].first, matches[3].second);
      
      // Create a vector<string> storing the keys of m_ParamMap 
      std::pair<std::string, RooRealVar*> me;
      std::vector<std::string> vec_keys;      
      BOOST_FOREACH(me, this->m_ParamMap) 
      {  
//         if(me.first!="P"){
          vec_keys.push_back(me.first);  
//         }
      }
      // Sort strings with shortest -> longest
      sort( vec_keys.begin(), vec_keys.end(), PIDCalib::length() );

      // Declare string to store updated cut-variable string
      std::string newCut = A;

      std::vector<std::string>::iterator iter;
      for(iter=vec_keys.begin(); iter!=vec_keys.end(); ++iter)
      {
        //std::cout<<*iter<<'\t'<<"Current:" <<A;

        // Regular expression to find PID variable surrounded either side by non-word character
        std::string _regex = "\\b"+(*iter)+"\\b";
        boost::regex re2(_regex.c_str());
        
        std::string temp = boost::regex_replace(newCut, 
                                             re2,
                                             (this->m_ParamMap[*iter])->GetName()
                                             );
        newCut = temp;
        //std::cout<<'\t'<<"New: "<<A<<'\t'<<temp<<'\t'<<newCut<<std::endl; 
      }
      
      ret = newCut;
      ret += B;
      ret += C;

      //std::cout<<Cut<<" -->> "<<ret<<std::endl;

      return ret;
    }
    else
    {
      std::cout <<"Only "<<matches.size()<<" matches made in "<< s <<std::endl;
      return NULL;
    }

  }
  else
  {
    std::cout<<"The regexp \"" << re << "\" does not match \"" << s << "\"" <<std::endl;
    return NULL;
  }
}

//=============================================================================
// Format a given cut string, possibly composed of multiple cuts separated by 
// the Boolean '&&' operator, into a string to be passed to RooDataSet::reduce()
//=============================================================================
const std::string GenericDataSet::FormatCutList(const std::string& Cut)
{
  std::vector< std::string > CutSeries;

  // If there exist at least one instance of "&&" in the string, then pass it
  // to the SplitCut function for splitting into individual cuts, else simply 
  // pass cut into CutSeries vector
  if(boost::algorithm::find_first(Cut, "&&"))
  {
    SplitCut( Cut, CutSeries );    
  }
  else
  {
    CutSeries.push_back(Cut);
  }
  
  std::string TotCut = "";
  std::vector< std::string >::iterator cut_itr;
  for(cut_itr=CutSeries.begin(); cut_itr!=CutSeries.end(); ++cut_itr)
  {
    if(!TotCut.empty())
      TotCut += " && ";
    TotCut += TranslateCut(*cut_itr);
  }
  return TotCut;
}



