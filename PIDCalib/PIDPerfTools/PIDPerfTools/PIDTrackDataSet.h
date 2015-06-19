// $Id: $
#ifndef PIDPERFTOOLS_PIDTRACKDATASET_H 
#define PIDPERFTOOLS_PIDTRACKDATASET_H 1

// Include files
#include <Rtypes.h>
#include "EvtTrackDataSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include <map>
#include <list>
#include <string>

/** @class PIDTrackDataSet PIDTrackDataSet.h PIDPerfTools/PIDTrackDataSet.h
 *  
 *
 *  @author Andrew Powell (LHCb)04
 *  @date   2011-09-20
 */

class PIDTrackDataSet : public virtual EvtTrackDataSet
{
public: 
  /// Standard constructor
  PIDTrackDataSet( );
  
  PIDTrackDataSet( const std::string& TrackName,
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
                   const std::string& DLLe_Name,
                   const std::string& DLLmu_Name,
                   const std::string& IsMuon_Name,
                   const std::string& IsMuonLoose_Name,
                   const std::string& nShared_Name,
                   const std::string& HasBremAdded_Name,
                   const std::string& CaloRegion_Name,
                   const std::string& ProbNNK_Name,
                   const std::string& ProbNNpi_Name,
                   const std::string& ProbNNp_Name,
                   const std::string& ProbNNmu_Name,
                   const std::string& ProbNNe_Name,
                   const std::string& Cuts = "",
                   const std::string& WgtVarName = ""
                   );

  PIDTrackDataSet( const std::string& TrackName,
                   const std::string& Charge,
                   PIDTrackDataSet* Data,
                   const RooArgSet& vars,
                   const std::string& Cuts = "",
                   const std::string& WgtVarName = ""
                   );
  
  PIDTrackDataSet( const std::string& name, 
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
                   const std::string& DLLe_Name,
                   const std::string& DLLmu_Name,
                   const std::string& IsMuon_Name,
                   const std::string& IsMuonLoose_Name,
                   const std::string& nShared_Name,    
                   const std::string& HasBremAdded_Name,
                   const std::string& CaloRegion_Name,               
                   const std::string& ProbNNK_Name,
                   const std::string& ProbNNpi_Name,
                   const std::string& ProbNNp_Name,
                   const std::string& ProbNNmu_Name,
                   const std::string& ProbNNe_Name,
                   const std::string& cuts = "", 
                   const std::string& wgtVarName = ""
                    );
  
  PIDTrackDataSet( const std::string& Name,
                   const std::string& Charge,
                   PIDTrackDataSet* Numerator,
                   PIDTrackDataSet* Denominator,
                   const std::string& WgtVar,
                   const std::string& Cuts_Num = "",
                   const std::string& Cuts_Denom = "",
                   const std::string& WgtVar_Num = "", 
                   const std::string& WgtVar_Denom = ""
                   );  
  
  virtual ~PIDTrackDataSet( ); ///< Destructor
  
  //========================================================
  // Get track charge
  //const TString GetCharge() const;
  //========================================================

  //========================================================
  // Append a PIDTrackDataSet
  void append(PIDTrackDataSet& data);
  //========================================================
  
  //========================================================
  // Operator Overload (Assignment)
  //PIDTrackDataSet& operator=(const PIDTrackDataSet&);
  //========================================================

  //========================================================
  // Get track parameter names 
  //========================================================  
  const std::string Get_ParamName_ProbNNK() const;
  const std::string Get_ParamName_ProbNNpi() const;
  const std::string Get_ParamName_ProbNNp() const;
  const std::string Get_ParamName_ProbNNmu() const;
  const std::string Get_ParamName_ProbNNe() const;
  const std::string Get_ParamName_DLLe() const;
  const std::string Get_ParamName_DLLmu() const;
  const std::string Get_ParamName_IsMuon() const;
  const std::string Get_ParamName_IsMuonLoose() const;
  const std::string Get_ParamName_nShared() const;
  const std::string Get_ParamName_HasBremAdded() const;
  const std::string Get_ParamName_CaloRegion() const;

  //========================================================
  // Get track parameter  
  //========================================================
  const RooRealVar* Get_Param_ProbNNK() const;
  const RooRealVar* Get_Param_ProbNNpi() const;
  const RooRealVar* Get_Param_ProbNNp() const;
  const RooRealVar* Get_Param_ProbNNmu() const;
  const RooRealVar* Get_Param_ProbNNe() const;
  const RooRealVar* Get_Param_DLLe() const;
  const RooRealVar* Get_Param_DLLmu() const;
  const RooRealVar* Get_Param_IsMuon() const;
  const RooRealVar* Get_Param_IsMuonLoose() const;
  const RooRealVar* Get_Param_nShared() const;
  const RooRealVar* Get_Param_HasBremAdded() const;
  const RooRealVar* Get_Param_CaloRegion() const;

  //========================================================
  // An additional reduce method that takes a vector of
  // RooBinnings and returns all those events within the 
  // global acceptance of the Binning schema
  virtual RooAbsData* SetInBinSchema(std::vector<RooBinning*>& BinSchema);
  //========================================================

protected:

  //========================================================
  //Protected constructor for internal use only
  PIDTrackDataSet( const std::string& Name, 
                   const std::string& Title, 
                   PIDTrackDataSet* Ntuple, 
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
  
  ClassDef(PIDTrackDataSet,1);

};
#endif // PIDPERFTOOLS_PIDTRACKDATASET_H
