// $Id: $
#ifndef PIDPERFTOOLS_GENERICDATASET_H 
#define PIDPERFTOOLS_GENERICDATASET_H 1

// Include files
#include <Rtypes.h>
#include "RooDataSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "RooTreeDataStore.h"
#include <map>
#include <list>
#include <string>
#include <vector>
#include <utility>

#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"

#define _unused(x) ((void)x)

/** @class GenericDataSet GenericDataSet.h PIDPerfTools/GenericDataSet.h
 *  
 *
 *  @author Andrew Powell (LHCb)04
 *  @date   2010-12-25
 */

class GenericDataSet : public RooDataSet
{
public:
  
  /// Overloaded operators (Necessary for ROOT versions >= v5.30)
  void* operator new(size_t sz);
  void* operator new(size_t sz, void* vp);

  /// Standard constructor
  GenericDataSet( );
  
  GenericDataSet( const std::string& TrackName,
                RooDataSet* Data,
                const RooArgSet& vars,
                const std::vector< std::pair< std::string, std::string > >& VarAliases,
                const std::string& Cuts = "",
                const std::string& WgtVarName = ""
                );

  GenericDataSet( const std::string& TrackName,
                GenericDataSet* Data,
                const RooArgSet& vars,
                const std::string& Cuts = "",
                const std::string& WgtVarName = ""
                );
  
  virtual ~GenericDataSet( ); ///< Destructor

  //========================================================
  // Get track charge
  const std::vector< std::pair< std::string, std::string > >* Get_Aliases() const;
  //========================================================

  //========================================================
  // Append a GenericDataSet
  void append(GenericDataSet& data);
  //========================================================
  
  //========================================================
  // Operator Overload (Assignment)
  //GenericDataSet& operator=(const GenericDataSet&);
  //========================================================

  //========================================================
  // Get track parameter names 
  virtual const std::string Get_ParamName(const std::string&) const;
  //========================================================  

  //========================================================
  // Get track parameter  
  const RooRealVar* Get_Param(const std::string&) const;
  //========================================================

  //========================================================
  // An additional reduce method that takes a vector of
  // RooBinnings and returns all those events within the 
  // global acceptance of the Binning schema
  virtual RooAbsData* SetInBinSchema(const std::vector<RooBinning*>& BinSchema);
  //========================================================
  
  void SplitCut( const std::string& Cut, std::vector< std::string >& SplitVec );
  const std::string FormatCutList( const std::string& Cut );
  const std::string TranslateCut( const std::string& Cut );

protected:
  
  //========================================================
  //Protected constructor for internal use only
  GenericDataSet( const std::string& Name, 
                const std::string& Title, 
                GenericDataSet* Ntuple, 
                const RooArgSet& vars, 
                const RooFormulaVar* cutVar, 
                const std::string& cutRange, 
                int nStart, 
                int nStop, 
                Bool_t copyCache, 
                const std::string& wgtVarName = "" );

  //========================================================
  // Implementation of RooAbsData virtual method that drives 
  // the RooAbsData::reduce() methods
  RooAbsData* reduceEng(const RooArgSet& varSubset, 
                        const RooFormulaVar* cutVar, 
                        const std::string& cutRange=0,
                        Int_t nStart=0, 
                        Int_t nStop=2000000000, 
                        Bool_t copyCache=kTRUE);
  //========================================================

  //========================================================
  // Define track variable
  void SetTrackVars( const std::vector< std::pair< std::string, std::string > >& VarAliases );
  //========================================================

  //========================================================
  // Define track variable
  void SetTrackVar( const std::string& ,
                    std::string);
  //========================================================

  //========================================================
  // Define track variable DLLpK
  void SetTrackVar_DLLpK( const std::string& ,
                          const std::string& ,
                          std::string);
  //========================================================

  // Declare a friend class
	template <class T> friend class PerfCalculator;

private:
 
  //========================================================
  // STL Map
  // Mapping between DataSet variables and track parameters
  std::map< std::string, RooRealVar* > m_ParamMap;
  //========================================================
 
  //========================================================
  // Track charge propery
  const std::vector< std::pair< std::string, std::string > > m_Aliases;
  //========================================================

public:

  ClassDef(GenericDataSet,1);

};
#endif // PIDPERFTOOLS_GENERICDATASET_H
