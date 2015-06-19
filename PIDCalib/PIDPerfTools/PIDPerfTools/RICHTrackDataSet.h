// $Id: $
#ifndef PIDPERFTOOLS_RICHTRACKDATASET_H 
#define PIDPERFTOOLS_RICHTRACKDATASET_H 1

// Include files
#include <Rtypes.h>
#include "EvtTrackDataSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include <map>
#include <list>
#include <string>

/** @class RICHTrackDataSet RICHTrackDataSet.h PIDPerfTools/RICHTrackDataSet.h
 *  
 *
 *  @author Andrew Powell (LHCb)04
 *  @date   2011-09-20
 */

class RICHTrackDataSet : public virtual EvtTrackDataSet
{
public: 
  /// Standard constructor
  RICHTrackDataSet( );
  
  RICHTrackDataSet( const std::string& TrackName,
                    const std::string& Charge,
                    RooDataSet* Data,
                    const RooArgSet& vars,
                    const std::string& P_Name,
                    const std::string& PT_Name,
                    const std::string& ETA_Name,
                    const std::string& nTrack_Var,
                    const std::string& DLLK_Name,
                    const std::string& DLLp_Name,
                    const std::string& ProbNNK_Name,
                    const std::string& ProbNNpi_Name,
                    const std::string& ProbNNp_Name,
                    const std::string& Cuts = "",
                    const std::string& WgtVarName = ""
                   );

  RICHTrackDataSet( const std::string& TrackName,
                    const std::string& Charge,
                    RICHTrackDataSet* Data,
                    const RooArgSet& vars,
                    const std::string& Cuts = "",
                    const std::string& WgtVarName = ""
                    );
  
  RICHTrackDataSet( const std::string& name, 
                    const std::string& title, 
                    TTree* ntuple, 
                    const RooArgSet& vars,
                    const std::string& P_Name,
                    const std::string& PT_Name,
                    const std::string& ETA_Name,
                    const std::string& nTrack_Var,
                    const std::string& DLLK_Name,
                    const std::string& DLLp_Name,
                    const std::string& ProbNNK_Name,
                    const std::string& ProbNNpi_Name,
                    const std::string& ProbNNp_Name,
                    const std::string& cuts = "", 
                    const std::string& wgtVarName = ""
                    );
  
  RICHTrackDataSet( const std::string& Name,
                    const std::string& Charge,
                    RICHTrackDataSet* Numerator,
                    RICHTrackDataSet* Denominator,
                    const std::string& WgtVar,
                    const std::string& Cuts_Num = "",
                    const std::string& Cuts_Denom = "",
                    const std::string& WgtVar_Num = "", 
                    const std::string& WgtVar_Denom = ""
                    );  
  
  virtual ~RICHTrackDataSet( ); ///< Destructor

  //========================================================
  // Get track charge
  //const TString GetCharge() const;
  //========================================================

  //========================================================
  // Append a RICHTrackDataSet
  void append(RICHTrackDataSet& data);
  //========================================================
  
  //========================================================
  // Operator Overload (Assignment)
  //RICHTrackDataSet& operator=(const RICHTrackDataSet&);
  //========================================================

  //========================================================
  // Get track parameter names 
  const std::string Get_ParamName_ProbNNK() const;
  const std::string Get_ParamName_ProbNNpi() const;
  const std::string Get_ParamName_ProbNNp() const;
  //========================================================  

  //========================================================
  // Get track parameter  
  const RooRealVar* Get_Param_ProbNNK() const;
  const RooRealVar* Get_Param_ProbNNpi() const;
  const RooRealVar* Get_Param_ProbNNp() const;
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
  RICHTrackDataSet( const std::string& Name, 
                   const std::string& Title, 
                   RICHTrackDataSet* Ntuple, 
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
  
  ClassDef(RICHTrackDataSet,1);

};
#endif // PIDPERFTOOLS_RICHTRACKDATASET_H
