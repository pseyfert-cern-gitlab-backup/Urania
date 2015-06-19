#ifndef PIDPERFTOOLS_LHCBPIDTRACKDATASET_H 
#define PIDPERFTOOLS_LHCBPIDTRACKDATASET_H 1

// Include files
#include <Rtypes.h>
#include "RICHTrackDataSet.h"
#include "MUONTrackDataSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include <map>
#include <list>
#include <string>

/** @class LHCbPIDTrackDataSet LHCbPIDTrackDataSet.h PIDPerfTools/LHCbPIDTrackDataSet.h
 *  
 *
 *  @author Andrew Powell (LHCb)04
 *  @date   2013-02-24
 */
class LHCbPIDTrackDataSet : public RICHTrackDataSet, public MUONTrackDataSet
{
public: 
  /// Standard constructor
  LHCbPIDTrackDataSet( ); 
  
  LHCbPIDTrackDataSet( const std::string& TrackName,
                       const std::string& Charge,
                       RooDataSet* Data,
                       const RooArgSet& vars,
                       const std::string& P_Name,
                       const std::string& PT_Name,
                       const std::string& ETA_Name,
                       const std::string& nTrack_Var,
                       const std::string& DLLK_Name,
                       const std::string& DLLp_Name,
                       const std::string& DLLe_Name,
                       const std::string& DLLmu_Name,
                       const std::string& IsMuon_Name,
                       const std::string& IsMuonLoose_Name,
                       const std::string& nShared_Name,
                       const std::string& ProbNNK_Name,
                       const std::string& ProbNNpi_Name,
                       const std::string& ProbNNp_Name,
                       const std::string& Cuts = "",
                       const std::string& WgtVarName = ""
                       );
  
  LHCbPIDTrackDataSet( const std::string& TrackName,
                       const std::string& Charge,
                       LHCbPIDTrackDataSet* Data,
                       const RooArgSet& vars,
                       const std::string& Cuts = "",
                       const std::string& WgtVarName = ""
                       );
  /*
  LHCbPIDTrackDataSet( const std::string& Name,
                       const std::string& Charge,
                       LHCbPIDTrackDataSet* Numerator,
                       LHCbPIDTrackDataSet* Denominator,
                       const std::string& WgtVar,
                       const std::string& Cuts_Num = "",
                       const std::string& Cuts_Denom = "",
                       const std::string& WgtVar_Num = "", 
                       const std::string& WgtVar_Denom = ""
                       );  
  */  
  virtual ~LHCbPIDTrackDataSet( ); ///< Destructor

  //========================================================
  // Append a LHCbPIDTrackDataSet
  void append(LHCbPIDTrackDataSet& data);
  //========================================================
  
  //========================================================
  // Operator Overload (Assignment)
  //LHCbPIDTrackDataSet& operator=(const LHCbPIDTrackDataSet&);
  //========================================================

  //========================================================
  // Get track parameter names 
  const std::string Get_ParamName_DLLe() const;
  //========================================================

  //========================================================
  // Get track parameter  
  const RooRealVar* Get_Param_DLLe() const;
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
  LHCbPIDTrackDataSet( const std::string& Name, 
                       const std::string& Title, 
                       LHCbPIDTrackDataSet* Ntuple, 
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

  ClassDef(LHCbPIDTrackDataSet,2);

};
#endif // PIDPERFTOOLS_LHCBPIDTRACKDATASET_H
