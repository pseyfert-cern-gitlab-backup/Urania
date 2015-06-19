// $Id: $
#ifndef PIDPERFTOOLS_MUONTRACKDATASET_H 
#define PIDPERFTOOLS_MUONTRACKDATASET_H 1

// Include files
#include <Rtypes.h>
#include "EvtTrackDataSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include <map>
#include <list>
#include <string>

/** @class MUONTrackDataSet MUONTrackDataSet.h PIDPerfTools/MUONTrackDataSet.h
 *  
 *
 *  @author Andrew Powell (LHCb)04
 *  @date   2011-09-22
 */

class MUONTrackDataSet : public virtual EvtTrackDataSet
{
public: 
  /// Standard constructor
  MUONTrackDataSet( );
  
  MUONTrackDataSet( const std::string& TrackName,
                    const std::string& Charge,
                    RooDataSet* Data,
                    const RooArgSet& vars,
                    const std::string& P_Name,
                    const std::string& PT_Name,
                    const std::string& ETA_Name,
                    const std::string& nTrack_Var,
                    const std::string& DLLK_Name,
                    const std::string& DLLp_Name,
                    const std::string& DLLmu_Name,
                    const std::string& IsMuon_Name,
                    const std::string& IsMuonLoose_Name,
                    const std::string& nShared_Name,
                    const std::string& Cuts = "",
                    const std::string& WgtVarName = ""
                   );

  MUONTrackDataSet( const std::string& TrackName,
                    const std::string& Charge,
                    MUONTrackDataSet* Data,
                    const RooArgSet& vars,
                    const std::string& Cuts = "",
                    const std::string& WgtVarName = ""
                    );
  
  MUONTrackDataSet( const std::string& name, 
                    const std::string& title, 
                    TTree* ntuple, 
                    const RooArgSet& vars,
                    const std::string& P_Name,
                    const std::string& PT_Name,
                    const std::string& ETA_Name,
                    const std::string& nTrack_Var,
                    const std::string& DLLK_Name,
                    const std::string& DLLp_Name,
                    const std::string& DLLmu_Name,
                    const std::string& IsMuon_Name,
                    const std::string& IsMuonLoose_Name,
                    const std::string& nShared_Name,
                    const std::string& cuts = "", 
                    const std::string& wgtVarName = ""
                    );
  
  MUONTrackDataSet( const std::string& Name,
                    const std::string& Charge,
                    MUONTrackDataSet* Numerator,
                    MUONTrackDataSet* Denominator,
                    const std::string& WgtVar,
                    const std::string& Cuts_Num = "",
                    const std::string& Cuts_Denom = "",
                    const std::string& WgtVar_Num = "", 
                    const std::string& WgtVar_Denom = ""
                    );  
  
  virtual ~MUONTrackDataSet( ); ///< Destructor

  //========================================================
  // Append a MUONTrackDataSet
  void append(MUONTrackDataSet& data);
  //========================================================
  
  //========================================================
  // Operator Overload (Assignment)
  //MUONTrackDataSet& operator=(const MUONTrackDataSet&);
  //========================================================

  //========================================================
  // Get track parameter names 
  const std::string Get_ParamName_DLLmu() const;
  const std::string Get_ParamName_IsMuon() const;
  const std::string Get_ParamName_IsMuonLoose() const;
  const std::string Get_ParamName_nShared() const;
  //========================================================  

  //========================================================
  // Get track parameter  
  const RooRealVar* Get_Param_DLLmu() const;
  const RooRealVar* Get_Param_IsMuon() const;
  const RooRealVar* Get_Param_IsMuonLoose() const;
  const RooRealVar* Get_Param_nShared() const;
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
  MUONTrackDataSet( const std::string& Name, 
                   const std::string& Title, 
                   MUONTrackDataSet* Ntuple, 
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

  ClassDef(MUONTrackDataSet,1);

};
#endif // PIDPERFTOOLS_MUONTRACKDATASET_H
