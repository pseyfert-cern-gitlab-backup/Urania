// $Id: $
#ifndef CALIBDATASCRIPTS_SETSPECTATORVARS_H 
#define CALIBDATASCRIPTS_SETSPECTATORVARS_H 1

// Include files
namespace RooPhysFit{
  class RooDMassFitter;
}

/*  @author Andrew Powell (LHCb)04
 *  @date   2011-06-10
 */

void SetSpecVars_EvtVars2012(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple);


void SetSpecVars_EvtVars2011(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple);

void SetSpecVars_MCEvtVars2011(RooPhysFit::RooDMassFitter& Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple);

void SetSpecVars_StdDLLs2011(RooPhysFit::RooDMassFitter& Mfit,
                             const char* parPrefix_DataSet,
                             const char* parPrefix_nTuple);

void SetSpecVars_EvtVars(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple);

void SetSpecVars_MCEvtVars(RooPhysFit::RooDMassFitter& Mfit,
                           const char* parPrefix_DataSet,
                           const char* parPrefix_nTuple);

void SetSpecVars_StdDLLs(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple);

void SetSpecVars_ANNVars(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple);

void SetSpecVars_KinematicVars(RooPhysFit::RooDMassFitter& Mfit,
                               const char* parPrefix_DataSet,
                               const char* parPrefix_nTuple);

void SetSpecVars_HamishVars(RooPhysFit::RooDMassFitter& Mfit,
                            const char* parPrefix_DataSet,
                            const char* parPrefix_nTuple);

void SetSpecVars_RadRadius(RooPhysFit::RooDMassFitter& Mfit,
                           const char* parPrefix_DataSet,
                           const char* parPrefix_nTuple);

void SetSpecVars_RICHVars(RooPhysFit::RooDMassFitter& Mfit,
                          const char* parPrefix_DataSet,
                          const char* parPrefix_nTuple);

void SetSpecVars_RICHCategories(RooPhysFit::RooDMassFitter& Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple);

void SetSpecVars_MUONCategories(RooPhysFit::RooDMassFitter& Mfit,
                                const char* parPrefix_DataSet,
                                const char* parPrefix_nTuple);

void SetSpecVars_MuonVars(RooPhysFit::RooDMassFitter& Mfit,
                          const char* parPrefix_DataSet,
                          const char* parPrefix_nTuple);

void SetSpecVars_ElectronVars(RooPhysFit::RooDMassFitter& Mfit,
                         const char* parPrefix_DataSet,
                         const char* parPrefix_nTuple);

#endif // CALIBDATASCRIPTS_SETSPECTATORVARS_H
