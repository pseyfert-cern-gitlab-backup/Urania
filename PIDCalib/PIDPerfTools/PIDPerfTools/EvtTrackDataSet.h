// $Id: $
#ifndef PIDPERFTOOLS_EVTTRACKDATASET_H 
#define PIDPERFTOOLS_EVTTRACKDATASET_H 1

// Include files
#include <Rtypes.h>
#include "TrackDataSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include <map>
#include <list>
#include <string>

/** @class EvtTrackDataSet EvtTrackDataSet.h PIDPerfTools/EvtTrackDataSet.h
 *  
 *
 *  @author Andrew Powell (LHCb)04
 *  @date   2010-12-25
 */

class EvtTrackDataSet : public TrackDataSet
{
public: 
  /// Standard constructor
  EvtTrackDataSet( );
  
  EvtTrackDataSet( const std::string& TrackName,
                   const std::string& Charge,
                   RooDataSet* Data,
                   const RooArgSet& vars,
                   const std::string& P_Name,
                   const std::string& PT_Name,
                   const std::string& ETA_Name,
                   const std::string& nTrack_Var,
                   const std::string& nSPDHits_Var,
                   const std::string& DLLK_Name,
                   const std::string& DLLp_Name,
                   const std::string& Cuts = "",
                   const std::string& WgtVarName = ""
                   );

  EvtTrackDataSet( const std::string& TrackName,
                   const std::string& Charge,
                   EvtTrackDataSet* Data,
                   const RooArgSet& vars,
                   const std::string& Cuts = "",
                   const std::string& WgtVarName = ""
                   );
  
  EvtTrackDataSet( const std::string& name, 
                   const std::string& title, 
                   TTree* ntuple, 
                   const RooArgSet& vars,
                   const std::string& P_Name,
                   const std::string& PT_Name,
                   const std::string& ETA_Name,
                   const std::string& nTrack_Var,
                   const std::string& nSPDHits_Var,
                   const std::string& DLLK_Name,
                   const std::string& DLLp_Name,
                   const std::string& cuts = "", 
                   const std::string& wgtVarName = ""
                   );

  EvtTrackDataSet( const std::string& Name,
                   const std::string& Charge,
                   EvtTrackDataSet* Numerator,
                   EvtTrackDataSet* Denominator,
                   const std::string& WgtVar,
                   const std::string& Cuts_Num = "",
                   const std::string& Cuts_Denom = "",
                   const std::string& WgtVar_Num = "", 
                   const std::string& WgtVar_Denom = ""
                   );  
  
  virtual ~EvtTrackDataSet( ); ///< Destructor

  //========================================================
  // Get track charge
  //const TString GetCharge() const;
  //========================================================

  //========================================================
  // Append a EvtTrackDataSet
  void append(EvtTrackDataSet& data);
  //========================================================
  
  //========================================================
  // Operator Overload (Assignment)
  //EvtTrackDataSet& operator=(const EvtTrackDataSet&);
  //========================================================

  //========================================================
  // Get track parameter names 
  const std::string Get_ParamName_nTrack() const;
  const std::string Get_ParamName_nSPDHits() const;
  //========================================================  

  //========================================================
  // Get track parameter  
  const RooRealVar* Get_Param_nTrack() const;
  const RooRealVar* Get_Param_nSPDHits() const;
  //========================================================

  //========================================================
  // An additional reduce method that takes a vector of
  // RooBinnings and returns all those events within the 
  // global acceptance of the Binning schema
  virtual RooAbsData* SetInBinSchema(std::vector<RooBinning*>& BinSchema);
  //========================================================

protected:

  //========================================================
  //Protected constructor for internal use only
  EvtTrackDataSet( const std::string& Name, 
                   const std::string& Title, 
                   EvtTrackDataSet* Ntuple, 
                   const RooArgSet& vars, 
                   const RooFormulaVar* cutVar, 
                   const std::string& cutRange, 
                   int nStart, 
                   int nStop, 
                   Bool_t copyCache, 
                   const std::string& wgtVarName = "");
  
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
  
private:

public:

  ClassDef(EvtTrackDataSet,1);
    
};
#endif // PIDPERFTOOLS_EVTTRACKDATASET_H
