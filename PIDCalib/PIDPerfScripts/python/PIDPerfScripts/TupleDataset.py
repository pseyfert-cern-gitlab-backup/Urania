import ROOT
from ROOT import (RooRealVar, RooDataSet, RooArgSet, TFile)
from copy import copy
import os
import time
import tempfile

class var:
  def __init__ (self, dsname, tuplename, range ):
    if isinstance ( range, str ):
      #Just set the range of all variables to be the same
      if   range == "var"     : range = [-1e400, 1e400 ]

    self.tuplename = tuplename
    self.dsname    = dsname
    self.range     = range

  def getRooRealVar(self, partName):
    name = self.dsname.format ( particle = partName )
    return RooRealVar (name, name, self.range[0], self.range[1])

  def getBranchName(self, partName):
    return self.tuplename.format ( particle = partName )


# vars_dataset contains all of the variables accessible within PIDCalib, each corresponding to a branch in the WGP nTuples
# Each entry in the list is of the form    'BinSchemeName':   var('RooDataSetName', 'WGPTupleName', 'Range')

# 'BinSchemeName' : the variable name used when creating a binning scheme within Binning.py
# 'RooDataSetName' : name of the variable within the internal PIDCalib RooDataSets (and the old Run I calibration sample files)
# 'WGPTupleName' : name of the variable branch in the WGP nTuples
# 'Range' : variable ranges, as specified above. Of the form [min,max]
# {particle} = "probe" in WGP nTuples
    
vars_dataset = {
  'MC12TuneV2_ProbNNe':             var('{particle}_V2ProbNNe',        '{particle}_MC12TuneV2_ProbNNe',        'var'),
  'Brunel_MC12TuneV2_ProbNNe':                   var('{particle}_Brunel_MC12TuneV2_ProbNNe',        '{particle}_Brunel_MC12TuneV2_ProbNNe',        'var'),        
  'MC12TuneV2_ProbNNmu':            var('{particle}_V2ProbNNmu',        '{particle}_MC12TuneV2_ProbNNmu',        'var'),        
  'Brunel_MC12TuneV2_ProbNNmu':                  var('{particle}_Brunel_MC12TuneV2_ProbNNmu',        '{particle}_Brunel_MC12TuneV2_ProbNNmu',        'var'),        
  'MC12TuneV2_ProbNNpi':            var('{particle}_V2ProbNNpi',        '{particle}_MC12TuneV2_ProbNNpi',        'var'),
  'Brunel_MC12TuneV2_ProbNNpi':                  var('{particle}_Brunel_MC12TuneV2_ProbNNpi',        '{particle}_Brunel_MC12TuneV2_ProbNNpi',        'var'),        
  'MC12TuneV2_ProbNNK':             var('{particle}_V2ProbNNK',        '{particle}_MC12TuneV2_ProbNNk',        'var'), #Uppercase K in PIDCalib, lowercase in WGP nTuple 
  'Brunel_MC12TuneV2_ProbNNK':                   var('{particle}_Brunel_MC12TuneV2_ProbNNk',        '{particle}_Brunel_MC12TuneV2_ProbNNk',        'var'),        
  'MC12TuneV2_ProbNNp':             var('{particle}_V2ProbNNp',        '{particle}_MC12TuneV2_ProbNNp',        'var'),
  'Brunel_MC12TuneV2_ProbNNp':                   var('{particle}_Brunel_MC12TuneV2_ProbNNp',        '{particle}_Brunel_MC12TuneV2_ProbNNp',        'var'),        
  'MC12TuneV2_ProbNNghost':         var('{particle}_V2ProbNNghost',        '{particle}_MC12TuneV2_ProbNNghost',        'var'),
  'Brunel_MC12TuneV2_ProbNNghost':               var('{particle}_Brunel_MC12TuneV2_ProbNNghost',        '{particle}_Brunel_MC12TuneV2_ProbNNghost',        'var'),        
  'MC12TuneV3_ProbNNe':             var('{particle}_V3ProbNNe',        '{particle}_MC12TuneV3_ProbNNe',        'var'),
  'Brunel_MC12TuneV3_ProbNNe':                   var('{particle}_Brunel_MC12TuneV3_ProbNNe',        '{particle}_Brunel_MC12TuneV3_ProbNNe',        'var'),        
  'MC12TuneV3_ProbNNmu':            var('{particle}_V3ProbNNmu',        '{particle}_MC12TuneV3_ProbNNmu',        'var'),
  'Brunel_MC12TuneV3_ProbNNmu':                  var('{particle}_Brunel_MC12TuneV3_ProbNNmu',        '{particle}_Brunel_MC12TuneV3_ProbNNmu',        'var'),        
  'MC12TuneV3_ProbNNpi':            var('{particle}_V3ProbNNpi',        '{particle}_MC12TuneV3_ProbNNpi',        'var'),
  'Brunel_MC12TuneV3_ProbNNpi':                  var('{particle}_Brunel_MC12TuneV3_ProbNNpi',        '{particle}_Brunel_MC12TuneV3_ProbNNpi',        'var'),
  'MC12TuneV3_ProbNNK':             var('{particle}_V3ProbNNK',        '{particle}_MC12TuneV3_ProbNNk',        'var'), #Uppercase K in PIDCalib, lowercase in WGP nTuple 
  'Brunel_MC12TuneV3_ProbNNK':                   var('{particle}_Brunel_MC12TuneV3_ProbNNk',        '{particle}_Brunel_MC12TuneV3_ProbNNk',        'var'),
  'MC12TuneV3_ProbNNp':             var('{particle}_V3ProbNNp',        '{particle}_MC12TuneV3_ProbNNp',        'var'),
  'Brunel_MC12TuneV3_ProbNNp':                   var('{particle}_Brunel_MC12TuneV3_ProbNNp',        '{particle}_Brunel_MC12TuneV3_ProbNNp',        'var'),
  'MC12TuneV3_ProbNNghost':         var('{particle}_V3ProbNNghost',        '{particle}_MC12TuneV3_ProbNNghost',        'var'),        
  'Brunel_MC12TuneV3_ProbNNghost':               var('{particle}_Brunel_MC12TuneV3_ProbNNghost',        '{particle}_Brunel_MC12TuneV3_ProbNNghost',        'var'),        
  'MC12TuneV4_ProbNNe':             var('{particle}_MC12TuneV4_ProbNNe',        '{particle}_MC12TuneV4_ProbNNe',        'var'),
  'Brunel_MC12TuneV4_ProbNNe':                   var('{particle}_Brunel_MC12TuneV4_ProbNNe',        '{particle}_Brunel_MC12TuneV4_ProbNNe',        'var'),        
  'MC12TuneV4_ProbNNmu':            var('{particle}_MC12TuneV4_ProbNNmu',        '{particle}_MC12TuneV4_ProbNNmu',        'var'),
  'Brunel_MC12TuneV4_ProbNNmu':                  var('{particle}_Brunel_MC12TuneV4_ProbNNmu',        '{particle}_Brunel_MC12TuneV4_ProbNNmu',        'var'),
  'MC12TuneV4_ProbNNpi':            var('{particle}_MC12TuneV4_ProbNNpi',        '{particle}_MC12TuneV4_ProbNNpi',        'var'),
  'Brunel_MC12TuneV4_ProbNNpi':                  var('{particle}_Brunel_MC12TuneV4_ProbNNpi',        '{particle}_Brunel_MC12TuneV4_ProbNNpi',        'var'),
  'MC12TuneV4_ProbNNK':             var('{particle}_MC12TuneV4_ProbNNk',        '{particle}_MC12TuneV4_ProbNNk',        'var'), #Uppercase K in PIDCalib, lowercase in WGP nTuple 
  'Brunel_MC12TuneV4_ProbNNK':                   var('{particle}_Brunel_MC12TuneV4_ProbNNk',        '{particle}_Brunel_MC12TuneV4_ProbNNk',        'var'),        
  'MC12TuneV4_ProbNNp':             var('{particle}_MC12TuneV4_ProbNNp',        '{particle}_MC12TuneV4_ProbNNp',        'var'),
  'Brunel_MC12TuneV4_ProbNNp':                   var('{particle}_Brunel_MC12TuneV4_ProbNNp',        '{particle}_Brunel_MC12TuneV4_ProbNNp',        'var'),        
  'MC12TuneV4_ProbNNghost':         var('{particle}_MC12TuneV4_ProbNNghost',        '{particle}_MC12TuneV4_ProbNNghost',        'var'),
  'Brunel_MC12TuneV4_ProbNNghost':               var('{particle}_Brunel_MC12TuneV4_ProbNNghost',        '{particle}_Brunel_MC12TuneV4_ProbNNghost',        'var'),
  'MC15TuneV1_ProbNNe':             var('{particle}_MC15TuneV1_ProbNNe',        '{particle}_MC15TuneV1_ProbNNe',        'var'),
  'Brunel_MC15TuneV1_ProbNNe':                   var('{particle}_Brunel_MC15TuneV1_ProbNNe',        '{particle}_Brunel_MC15TuneV1_ProbNNe',        'var'),        
  'MC15TuneV1_ProbNNmu':            var('{particle}_MC15TuneV1_ProbNNmu',        '{particle}_MC15TuneV1_ProbNNmu',        'var'),
  'Brunel_MC15TuneV1_ProbNNmu':                  var('{particle}_Brunel_MC15TuneV1_ProbNNmu',        '{particle}_Brunel_MC15TuneV1_ProbNNmu',        'var'),
  'MC15TuneV1_ProbNNpi':            var('{particle}_MC15TuneV1_ProbNNpi',        '{particle}_MC15TuneV1_ProbNNpi',        'var'),
  'Brunel_MC15TuneV1_ProbNNpi':                  var('{particle}_Brunel_MC15TuneV1_ProbNNpi',        '{particle}_Brunel_MC15TuneV1_ProbNNpi',        'var'),
  'MC15TuneV1_ProbNNK':             var('{particle}_MC15TuneV1_ProbNNk',        '{particle}_MC15TuneV1_ProbNNk',        'var'), #Uppercase K in PIDCalib, lowercase in WGP nTuple 
  'Brunel_MC15TuneV1_ProbNNK':                   var('{particle}_Brunel_MC15TuneV1_ProbNNk',        '{particle}_Brunel_MC15TuneV1_ProbNNk',        'var'),        
  'MC15TuneV1_ProbNNp':             var('{particle}_MC15TuneV1_ProbNNp',        '{particle}_MC15TuneV1_ProbNNp',        'var'),
  'Brunel_MC15TuneV1_ProbNNp':                   var('{particle}_Brunel_MC15TuneV1_ProbNNp',        '{particle}_Brunel_MC15TuneV1_ProbNNp',        'var'),        
  'MC15TuneV1_ProbNNghost':         var('{particle}_MC15TuneV1_ProbNNghost',        '{particle}_MC15TuneV1_ProbNNghost',        'var'),        
  'Brunel_MC15TuneV1_ProbNNghost':               var('{particle}_Brunel_MC15TuneV1_ProbNNghost',        '{particle}_Brunel_MC15TuneV1_ProbNNghost',        'var'),            
  'PP_CaloPrsE':                    var('{particle}_PP_CaloPrsE',        '{particle}_PP_CaloPrsE',        'var'),
  'Brunel_PP_CaloPrsE':                          var('{particle}_Brunel_PP_CaloPrsE',        '{particle}_Brunel_PP_CaloPrsE',        'var'),        
  'PP_CaloEcalE':                   var('{particle}_PP_CaloEcalE',        '{particle}_PP_CaloEcalE',        'var'),
  'Brunel_PP_CaloEcalE':                         var('{particle}_Brunel_PP_CaloEcalE',        '{particle}_Brunel_PP_CaloEcalE',        'var'),        
  'PP_CaloHcalE':                   var('{particle}_PP_CaloHcalE',        '{particle}_PP_CaloHcalE',        'var'),
  'Brunel_PP_CaloHcalE':                         var('{particle}_Brunel_PP_CaloHcalE',        '{particle}_Brunel_PP_CaloHcalE',        'var'),
  'PP_CaloEcalChi2':                var('{particle}_PP_CaloEcalChi2',        '{particle}_PP_CaloEcalChi2',        'var'),
  'Brunel_PP_CaloEcalChi2':                      var('{particle}_Brunel_PP_CaloEcalChi2',        '{particle}_Brunel_PP_CaloEcalChi2',        'var'),        
  'PP_CaloEoverP':                  var('{particle}_PP_CaloEoverP',        '{particle}_PP_CaloEoverP',        'var'),
  'Brunel_PP_CaloEoverP':                        var('{particle}_Brunel_PP_CaloEoverP',        '{particle}_Brunel_PP_CaloEoverP',        'var'),        
  'PP_EcalPIDe':                    var('{particle}_PP_EcalPIDe',        '{particle}_PP_EcalPIDe',        'var'),
  'Brunel_PP_EcalPIDe':                          var('{particle}_Brunel_PP_EcalPIDe',        '{particle}_Brunel_PP_EcalPIDe',        'var'),        
  'PP_PrsPIDe':                     var('{particle}_PP_PrsPIDe',        '{particle}_PP_PrsPIDe',        'var'),
  'Brunel_PP_PrsPIDe':                           var('{particle}_Brunel_PP_PrsPIDe',        '{particle}_Brunel_PP_PrsPIDe',        'var'),        
  'PP_HcalPIDe':                    var('{particle}_PP_HcalPIDe',        '{particle}_PP_HcalPIDe',        'var'),
  'Brunel_PP_HcalPIDe':                          var('{particle}_Brunel_PP_HcalPIDe',        '{particle}_Brunel_PP_HcalPIDe',        'var'),
  'PP_VeloCharge':                  var('{particle}_PP_VeloCharge',        '{particle}_PP_VeloCharge',        'var'),
  'Brunel_PP_VeloCharge':                        var('{particle}_Brunel_PP_VeloCharge',        '{particle}_Brunel_PP_VeloCharge',        'var'),
  'Charge':                         var('{particle}_Charge',        '{particle}_Charge',        'var'),
  'Brunel_Charge':                               var('{particle}_Brunel_Charge',        '{particle}_Brunel_Charge',        'var'),        
  'ETA':                            var('{particle}_Eta',        '{particle}_ETA',        'var'),             
  'Brunel_ETA':                                  var('{particle}_Brunel_ETA',        '{particle}_Brunel_ETA',        'var'),        
  'ElectronUnbiased':               var('{particle}_ElectronUnbiased',        '{particle}_ElectronUnbiased',        'var'),
  'Brunel_ElectronUnbiased':                     var('{particle}_Brunel_ElectronUnbiased',        '{particle}_Brunel_ElectronUnbiased',        'var'),
  'MINIPCHI2':                      var('{particle}_MINIPCHI2',        '{particle}_MINIPCHI2',        'var'),        
  'Brunel_MINIPCHI2':                            var('{particle}_Brunel_MINIPCHI2',        '{particle}_Brunel_MINIPCHI2',        'var'),        
  'MuonBgLL':                       var('{particle}_MuonBgLL',        '{particle}_MuonBgLL',        'var'),        
  'Brunel_MuonBgLL':                             var('{particle}_Brunel_MuonBgLL',        '{particle}_Brunel_MuonBgLL',        'var'),        
  'MuonMuLL':                       var('{particle}_MuonMuLL',        '{particle}_MuonMuLL',        'var'),        
  'Brunel_MuonMuLL':                             var('{particle}_Brunel_MuonMuLL',        '{particle}_Brunel_MuonMuLL',        'var'),              
  'MuonUnbiased':                   var('{particle}_MuonUnbiased',        '{particle}_MuonUnbiased',        'var'),        
  'Brunel_MuonUnbiased':                         var('{particle}_Brunel_MuonUnbiased',        '{particle}_Brunel_MuonUnbiased',        'var'),        
  'Unbias_HLT1':                   var('{particle}_Unbias_HLT1',        '{particle}_Unbias_HLT1',        'var'),        
  'P':                              var('{particle}_P',        '{particle}_P',        'var'),          
  'Brunel_P':                                    var('{particle}_Brunel_P',        '{particle}_Brunel_P',        'var'),         
  'PHI':                            var('{particle}_Phi',        '{particle}_PHI',        'var'),             
  'Brunel_PHI':                                  var('{particle}_Brunel_PHI',        '{particle}_Brunel_PHI',        'var'),         # PIDCalib called DLLx, WGP nTuple called PIDx 
  'DLLK':                           var('{particle}_CombDLLK',        '{particle}_PIDK',        'var'),         
  'Brunel_DLLK':                                 var('{particle}_Brunel_PIDK',        '{particle}_Brunel_PIDK',        'var'),        
  'DLLd':                           var('{particle}_PIDd',        '{particle}_PIDd',        'var'),         
  'Brunel_DLLd':                                 var('{particle}_Brunel_PIDd',        '{particle}_Brunel_PIDd',        'var'),        
  'DLLe':                           var('{particle}_CombDLLe',        '{particle}_PIDe',        'var'),         
  'Brunel_DLLe':                                 var('{particle}_Brunel_PIDe',        '{particle}_Brunel_PIDe',        'var'),        
  'DLLmu':                          var('{particle}_CombDLLmu',        '{particle}_PIDmu',        'var'),         
  'Brunel_DLLmu':                                var('{particle}_Brunel_PIDmu',        '{particle}_Brunel_PIDmu',        'var'),        
  'DLLp':                           var('{particle}_CombDLLp',        '{particle}_PIDp',        'var'),          
  'Brunel_DLLp':                                 var('{particle}_Brunel_PIDp',        '{particle}_Brunel_PIDp',        'var'),        
  'PT':                             var('{particle}_PT',        '{particle}_PT',        'var'),        
  'Brunel_PT':                                   var('{particle}_Brunel_PT',        '{particle}_Brunel_PT',        'var'),        
  'RichDLLbt':                      var('{particle}_RichDLLbt',        '{particle}_RichDLLbt',        'var'),        
  'Brunel_RichDLLbt':                            var('{particle}_Brunel_RichDLLbt',        '{particle}_Brunel_RichDLLbt',        'var'),
  'RichDLLd':                       var('{particle}_RichDLLd',        '{particle}_RichDLLd',        'var'),         
  'Brunel_RichDLLd':                             var('{particle}_Brunel_RichDLLd',        '{particle}_Brunel_RichDLLd',        'var'),        
  'RichDLLe':                       var('{particle}_RichDLLe',        '{particle}_RichDLLe',        'var'),        
  'Brunel_RichDLLe':            		  var('{particle}_Brunel_RichDLLe',        '{particle}_Brunel_RichDLLe',        'var'),        
  'RichDLLk':            		  var('{particle}_RichDLLk',        '{particle}_RichDLLk',        'var'),         
  'Brunel_RichDLLk':            		  var('{particle}_Brunel_RichDLLk',        '{particle}_Brunel_RichDLLk',        'var'),        
  'RichDLLmu':            	  var('{particle}_RichDLLmu',        '{particle}_RichDLLmu',        'var'),        
  'Brunel_RichDLLmu':            		  var('{particle}_Brunel_RichDLLmu',        '{particle}_Brunel_RichDLLmu',        'var'),        
  'RichDLLp':            		  var('{particle}_RichDLLp',        '{particle}_RichDLLp',        'var'),         
  'Brunel_RichDLLp':            		  var('{particle}_Brunel_RichDLLp',        '{particle}_Brunel_RichDLLp',        'var'),        
  'RichDLLpi':            	  var('{particle}_RichDLLpi',        '{particle}_RichDLLpi',        'var'),        
  'Brunel_RichDLLpi':            		  var('{particle}_Brunel_RichDLLpi',        '{particle}_Brunel_RichDLLpi',        'var'),        
  'TRACK_GHOSTPROB':            	  var('{particle}_TRACK_GHOSTPROB',        '{particle}_TRACK_GHOSTPROB',        'var'),
  'Brunel_TRACK_GHOSTPROB':            	  var('{particle}_Brunel_TRACK_GHOSTPROB',        '{particle}_Brunel_TRACK_GHOSTPROB',        'var'),        
  'TRCHI2NDOF':            	  var('{particle}_TRCHI2NDOF',        '{particle}_TRCHI2NDOF',        'var'),        
  'Brunel_TRCHI2NDOF':            		  var('{particle}_Brunel_TRCHI2NDOF',        '{particle}_Brunel_TRCHI2NDOF',        'var'),        
  'trackcharge':            	  var('{particle}_trackcharge',        '{particle}_trackcharge',        'var'),
  'Brunel_trackcharge':            		  var('{particle}_Brunel_trackcharge',        '{particle}_Brunel_trackcharge',        'var'),        
  'ID':            		  var('{particle}_ID',        '{particle}_ID',        'var'),          
  'Brunel_ID':            			  var('{particle}_Brunel_ID',        '{particle}_Brunel_ID',        'var'),        
  'hasMuon':            		  var('{particle}_hasMuon',        '{particle}_hasMuon',        'var'),        
  'Brunel_hasMuon':            		  var('{particle}_Brunel_hasMuon',        '{particle}_Brunel_hasMuon',        'var'),        
  'IsMuon':            		  var('{particle}_IsMuon',        '{particle}_isMuon',        'var'),        
  'Brunel_IsMuon':            			  var('{particle}_Brunel_isMuon',        '{particle}_Brunel_isMuon',        'var'),     #IsMuon in PIDCalib, isMuon in WGP nTuples  
  'IsMuonLoose':            	  var('{particle}_IsMuonLoose',        '{particle}_isMuonLoose',        'var'),
  'Brunel_IsMuonLoose':            		  var('{particle}_Brunel_isMuonLoose',        '{particle}_Brunel_isMuonLoose',        'var'),   #IsMuonLoose in PIDCalib, isMuonLoose in WGP nTuples     
  'IsMuonTight':            	  var('{particle}_isMuonTight',        '{particle}_isMuonTight',        'var'),        
  'Brunel_IsMuonTight':            		  var('{particle}_Brunel_isMuonTight',        '{particle}_Brunel_isMuonTight',        'var'),
  'nShared':            		  var('{particle}_nShared',        '{particle}_NShared',        'var'),    # PID Calib is nShared, WGP nTuple is NShared      
  'Brunel_nShared':            		  var('{particle}_Brunel_NShared',        '{particle}_Brunel_NShared',        'var'),        
  'InMuonAcc':            	  var('{particle}_InMuonAcc',        '{particle}_InMuonAcc',        'var'),
  'Brunel_InMuonAcc':            		  var('{particle}_Brunel_InMuonAcc',        '{particle}_Brunel_InMuonAcc',        'var'),
  'TRACK_MatchCHI2':            	  var('{particle}_TRACK_MatchCHI2',        '{particle}_TRACK_MatchCHI2',        'var'),
  'Brunel_TRACK_MatchCHI2':            	  var('{particle}_Brunel_TRACK_MatchCHI2',        '{particle}_Brunel_TRACK_MatchCHI2',        'var'),        
  'HasRich':            		  var('{particle}_hasRich',        '{particle}_hasRich',        'var'),    # HasRich in PIDCalib, hasRich in WGP nTuples    
  'Brunel_HasRich':            		  var('{particle}_Brunel_hasRich',        '{particle}_Brunel_hasRich',        'var'),        
  'HasCalo':           		  var('{particle}_hasCalo',        '{particle}_hasCalo',        'var'),    # HasCalo in PIDCalib, hasCalo in WGP nTuples      
  'Brunel_HasCalo':            		  var('{particle}_Brunel_hasCalo',        '{particle}_Brunel_hasCalo',        'var'),        
  'RICHThreshold_pi':            	  var('{particle}_RICHThreshold_pi',        '{particle}_RICHThresholdPi',        'var'),
  'Brunel_RICHThreshold_pi':            	  var('{particle}_Brunel_RICHThresholdPi',        '{particle}_Brunel_RICHThresholdPi',        'var'),      #PIDCalib name is _K, _pi e.t.c, WGP nTuple is Ka,Pi,Pr  
  'RICHThreshold_K':            	  var('{particle}_RICHThreshold_K',        '{particle}_RICHThresholdKa',        'var'),        
  'Brunel_RICHThreshold_K':            	  var('{particle}_Brunel_RICHThresholdKa',        '{particle}_Brunel_RICHThresholdKa',        'var'),        
  'RICHThreshold_p':            	  var('{particle}_RICHThreshold_p',        '{particle}_RICHThresholdPr',        'var'),        
  'Brunel_RICHThreshold_p':            	  var('{particle}_Brunel_RICHThresholdPr',        '{particle}_Brunel_RICHThresholdPr',        'var'),        
  'RICHThreshold_e':            	  var('{particle}_RICHThreshold_e',        '{particle}_RICHThresholdEl',        'var'),        
  'Brunel_RICHThreshold_e':            	  var('{particle}_Brunel_RICHThresholdEl',        '{particle}_Brunel_RICHThresholdEl',        'var'),        
  'RICHThreshold_mu':            	  var('{particle}_RICHThreshold_mu',        '{particle}_RICHThresholdMu',        'var'),        
  'Brunel_RICHThreshold_mu':            	  var('{particle}_Brunel_RICHThresholdMu',        '{particle}_Brunel_RICHThresholdMu',        'var'),        
  'RICHAerogelUsed':            	  var('{particle}_RICHAerogelUsed',        '{particle}_RICHAerogelUsed',        'var'),        
  'Brunel_RICHAerogelUsed':            	  var('{particle}_Brunel_RICHAerogelUsed',        '{particle}_Brunel_RICHAerogelUsed',        'var'),        
  'RICH1GasUsed':            	  var('{particle}_RICH1GasUsed',        '{particle}_RICH1GasUsed',        'var'),        
  'Brunel_RICH1GasUsed':            		  var('{particle}_Brunel_RICH1GasUsed',        '{particle}_Brunel_RICH1GasUsed',        'var'),        
  'RICH2GasUsed':            	  var('{particle}_RICH2GasUsed',        '{particle}_RICH2GasUsed',        'var'),
  'Brunel_RICH2GasUsed':            		  var('{particle}_Brunel_RICH2GasUsed',        '{particle}_Brunel_RICH2GasUsed',        'var'),        
  'Brunel_NMatchingCand':            		  var('NMatchingCand_{particle}_Brunel',        'NMatchingCand_{particle}_Brunel',        'var'),
  'Brunel_Overlap_loaded':            		  var('Overlap_loaded_{particle}_Brunel',        'Overlap_loaded_{particle}_Brunel',        'var'),        
  'Brunel_Overlap_original':            	  var('Overlap_original_{particle}_Brunel',        'Overlap_original_{particle}_Brunel',        'var'),        
  'nCandidate':            		  var('nCandidate',        'nCandidate',        'var'),            
  'totCandidates':            		  var('totCandidates',        'totCandidates',        'var'),
  'EventInSequence':            	  var('EventInSequence',        'EventInSequence',        'var'),
  'TCK':            			  var('TCK',        'TCK',        'var'),                    
  'eventNumber':           		  var('eventNumber',        'eventNumber',        'var'),         
  'eventNumber1':            		  var('eventNumber1',        'eventNumber1',        'var'),           
  'eventNumber2':           		  var('eventNumber2',        'eventNumber2',        'var'),          
  'runNumber':            		  var('runNumber',        'runNumber',        'var'),            
  'nMuonTracks':            		  var('nMuonTracks',        'nMuonTracks',        'var'),           
  'nPVs':            			  var('nPVs',        'nPVs',        'var'),               
  'nRich1Hits':            		  var('nRich1Hits',        'nRich1Hits',        'var'),             
  'nRich2Hits':            		  var('nRich2Hits',        'nRich2Hits',        'var'),             
  'nSPDHits':            		  var('nSPDhits',        'nSPDhits',        'var'),  #### PIDCalib is nSPDHits, WGP nTuple is nSPDhits          
  'nTracks':            		  var('nTracks',        'nTracks',        'var'),         
  'nVeloClusters':                var('nVeloClusters',    'nVeloClusters',    'var'),
  'nVeloClusters_Brunel':         var('nVeloClusters_Brunel',    'nVeloClusters_Brunel',    'var'),
  'sweight':            		  var('nsig_sw', '{particle}_sWeight',        'var')
  }


datasets = {
  'DSt_Pi' : ["DSt_PiMTuple", "DSt_PiPTuple"],
  'DSt_K'  : ["DSt_KPTuple", "DSt_KMTuple"],
  'Lam0_P' : ["Lam0_PTuple", "Lam0_PbarTuple", "Lam0_HPT_PTuple", "Lam0_HPT_PbarTuple", "Lam0_VHPT_PTuple", "Lam0_VHPT_PbarTuple"],
  'Jpsi_Mu': ["Jpsi_MuPTuple", "Jpsi_MuMTuple"],
  'LcfB_P' : ["LbLcMu_PTuple", "LbLcMu_PbarTuple"],
  'Sigmac0_P': ["Sigmac0_PbarTuple","Sigmac0_PTuple"],
  'DsPhi_K': ["DsPhi_KPTuple","DsPhi_KMTuple"],
  'Sigmacpp_P': ["Sigmacpp_PbarTuple","Sigmacpp_PTuple"],
  'DSt3Pi_Pi' : ["DSt3Pi_PiMTuple", "DSt3Pi_PiPTuple"],
  'DSt3Pi_K'  : ["DSt3Pi_KPTuple", "DSt3Pi_KMTuple"],
  'Phi_K': ["Phi_KMTuple","Phi_KPTuple"],
  'Phi_Mu': ["Phi_MuMTuple","Phi_MuPTuple"],
  'B_Jpsi_Mu': ["B_Jpsi_MuPTuple","B_Jpsi_MuMTuple"],
  'Jpsi_P': ["Jpsi_PTuple","Jpsi_PbarTuple"],
  'KS_Pi':  ["KS_PiPTuple","KS_PiMTuple"],
  'Jpsi_e': ["Jpsi_EPTuple","Jpsi_EMTuple"],
  'B_Jpsi_P': ["B_Jpsi_PTuple","B_Jpsi_PbarTuple"],
  'B_Jpsi_e': ["B_Jpsi_EPTuple","B_Jpsi_EMTuple"]
}

#Add the Brem variables to everything apart from Lam0_P sample, and add certain muon variables only to the Jpsi_Mu
additionalVariables = {
  'DSt_K' :  {
  	'HasBremAdded':                   var('{particle}_HasBremAdded',        '{particle}_HasBremAdded',        'var'),
  	'Brunel_HasBremAdded':                         var('{particle}_Brunel_HasBremAdded',        '{particle}_Brunel_HasBremAdded',        'var'),        
  	'BremMultiplicity':               var('{particle}_BremMultiplicity',        '{particle}_BremMultiplicity',        'var'),        
  	'Brunel_BremMultiplicity':                     var('{particle}_Brunel_BremMultiplicity',        '{particle}_Brunel_BremMultiplicity',        'var'),        
  	'BremPE':                         var('{particle}_BremPE',        '{particle}_BremPE',        'var'),           
  	'Brunel_BremPE':                               var('{particle}_Brunel_BremPE',        '{particle}_Brunel_BremPE',        'var'),        
  	'BremPX':                         var('{particle}_BremPX',        '{particle}_BremPX',        'var'),         
  	'Brunel_BremPX':                               var('{particle}_Brunel_BremPX',        '{particle}_Brunel_BremPX',        'var'),        
  	'BremPY':                         var('{particle}_BremPY',        '{particle}_BremPY',        'var'),           
  	'Brunel_BremPY':                               var('{particle}_Brunel_BremPY',        '{particle}_Brunel_BremPY',        'var'),        
  	'BremPZ':                         var('{particle}_BremPZ',        '{particle}_BremPZ',        'var'),         
  	'Brunel_BremPZ':                               var('{particle}_Brunel_BremPZ',        '{particle}_Brunel_BremPZ',        'var'),        
  	'BremOriginX':                    var('{particle}_BremOriginX',        '{particle}_BremOriginX',        'var'),
  	'Brunel_BremOriginX':                          var('{particle}_Brunel_BremOriginX',        '{particle}_Brunel_BremOriginX',        'var'),        
  	'BremOriginY':                    var('{particle}_BremOriginY',        '{particle}_BremOriginY',        'var'),
  	'Brunel_BremOriginY':                          var('{particle}_Brunel_BremOriginY',        '{particle}_Brunel_BremOriginY',        'var'),        
  	'BremOriginZ':                    var('{particle}_BremOriginZ',        '{particle}_BremOriginZ',        'var'),
  	'Brunel_BremOriginZ':                          var('{particle}_Brunel_BremOriginZ',        '{particle}_Brunel_BremOriginZ',        'var'),      
  },
  'DSt_Pi' :  {
  	'HasBremAdded':                   var('{particle}_HasBremAdded',        '{particle}_HasBremAdded',        'var'),
  	'Brunel_HasBremAdded':                         var('{particle}_Brunel_HasBremAdded',        '{particle}_Brunel_HasBremAdded',        'var'),        
  	'BremMultiplicity':               var('{particle}_BremMultiplicity',        '{particle}_BremMultiplicity',        'var'),        
  	'Brunel_BremMultiplicity':                     var('{particle}_Brunel_BremMultiplicity',        '{particle}_Brunel_BremMultiplicity',        'var'),        
  	'BremPE':                         var('{particle}_BremPE',        '{particle}_BremPE',        'var'),           
  	'Brunel_BremPE':                               var('{particle}_Brunel_BremPE',        '{particle}_Brunel_BremPE',        'var'),        
  	'BremPX':                         var('{particle}_BremPX',        '{particle}_BremPX',        'var'),         
  	'Brunel_BremPX':                               var('{particle}_Brunel_BremPX',        '{particle}_Brunel_BremPX',        'var'),        
  	'BremPY':                         var('{particle}_BremPY',        '{particle}_BremPY',        'var'),           
  	'Brunel_BremPY':                               var('{particle}_Brunel_BremPY',        '{particle}_Brunel_BremPY',        'var'),        
  	'BremPZ':                         var('{particle}_BremPZ',        '{particle}_BremPZ',        'var'),         
  	'Brunel_BremPZ':                               var('{particle}_Brunel_BremPZ',        '{particle}_Brunel_BremPZ',        'var'),        
  	'BremOriginX':                    var('{particle}_BremOriginX',        '{particle}_BremOriginX',        'var'),
  	'Brunel_BremOriginX':                          var('{particle}_Brunel_BremOriginX',        '{particle}_Brunel_BremOriginX',        'var'),        
  	'BremOriginY':                    var('{particle}_BremOriginY',        '{particle}_BremOriginY',        'var'),
  	'Brunel_BremOriginY':                          var('{particle}_Brunel_BremOriginY',        '{particle}_Brunel_BremOriginY',        'var'),        
  	'BremOriginZ':                    var('{particle}_BremOriginZ',        '{particle}_BremOriginZ',        'var'),
  	'Brunel_BremOriginZ':                          var('{particle}_Brunel_BremOriginZ',        '{particle}_Brunel_BremOriginZ',        'var'),      
  },
  'Jpsi_Mu' :  {
  	'HasBremAdded':                   var('{particle}_HasBremAdded',        '{particle}_HasBremAdded',        'var'),
  	'Brunel_HasBremAdded':                         var('{particle}_Brunel_HasBremAdded',        '{particle}_Brunel_HasBremAdded',        'var'),        
  	'BremMultiplicity':               var('{particle}_BremMultiplicity',        '{particle}_BremMultiplicity',        'var'),        
  	'Brunel_BremMultiplicity':                     var('{particle}_Brunel_BremMultiplicity',        '{particle}_Brunel_BremMultiplicity',        'var'),        
  	'BremPE':                         var('{particle}_BremPE',        '{particle}_BremPE',        'var'),           
  	'Brunel_BremPE':                               var('{particle}_Brunel_BremPE',        '{particle}_Brunel_BremPE',        'var'),        
  	'BremPX':                         var('{particle}_BremPX',        '{particle}_BremPX',        'var'),         
  	'Brunel_BremPX':                               var('{particle}_Brunel_BremPX',        '{particle}_Brunel_BremPX',        'var'),        
  	'BremPY':                         var('{particle}_BremPY',        '{particle}_BremPY',        'var'),           
  	'Brunel_BremPY':                               var('{particle}_Brunel_BremPY',        '{particle}_Brunel_BremPY',        'var'),        
  	'BremPZ':                         var('{particle}_BremPZ',        '{particle}_BremPZ',        'var'),         
  	'Brunel_BremPZ':                               var('{particle}_Brunel_BremPZ',        '{particle}_Brunel_BremPZ',        'var'),        
  	'BremOriginX':                    var('{particle}_BremOriginX',        '{particle}_BremOriginX',        'var'),
  	'Brunel_BremOriginX':                          var('{particle}_Brunel_BremOriginX',        '{particle}_Brunel_BremOriginX',        'var'),        
  	'BremOriginY':                    var('{particle}_BremOriginY',        '{particle}_BremOriginY',        'var'),
  	'Brunel_BremOriginY':                          var('{particle}_Brunel_BremOriginY',        '{particle}_Brunel_BremOriginY',        'var'),        
  	'BremOriginZ':                    var('{particle}_BremOriginZ',        '{particle}_BremOriginZ',        'var'),
  	'Brunel_BremOriginZ':                          var('{particle}_Brunel_BremOriginZ',        '{particle}_Brunel_BremOriginZ',        'var'),  
  	'MuonProbe':                      var('{particle}_MuonProbe',        '{particle}_MuonProbe',        'var'),        
  	'Brunel_MuonProbe':                            var('{particle}_Brunel_MuonProbe',        '{particle}_Brunel_MuonProbe',        'var'),        
  	'MuonTOS':                        var('{particle}_MuonTOS',        '{particle}_MuonTOS',        'var'),        
  	'Brunel_MuonTOS':                              var('{particle}_Brunel_MuonTOS',        '{particle}_Brunel_MuonTOS',        'var'),        
  	'MuonTag':                        var('{particle}_MuonTag',        '{particle}_MuonTag',        'var'),          
  	'Brunel_MuonTag':                              var('{particle}_Brunel_MuonTag',        '{particle}_Brunel_MuonTag',        'var'),  
  }
}

def getDataSetFromTuple ( file, mother, part, trackcuts, pidcuts, xvar, yvar, zvar):

  
  datasetname = mother + "_" + part

  if datasetname not in datasets:
    print "Cannot configure dataset " + datasetname + ", not in Turbo stream"
    return RooDataSet()

  vars = copy(vars_dataset)
  if datasetname in additionalVariables:
    vars.update ( additionalVariables[datasetname] )
    
  tempdir = tempfile.mkdtemp()
  print "Creating temporary directory: "+tempdir
  tmp = ROOT.TFile.Open(tempdir+"/tmpPidCalib_"+datasetname+".root","RECREATE")
  #tmp = ROOT.TFile.Open (  "/tmp/"+os.getenv('USER') + "/tmpPidCalib_"+datasetname+"{0}.root".format(time.time()) , "RECREATE")
  


  data_total = ROOT.RooDataSet()
  print "Converting WGP nTuple to RooDataSet: ({0},{1})".format(time.time(),time.clock())
  
  i = 0
  for dataset in datasets [ datasetname ]:
  
    roovars = {}
    listOfVars = RooArgSet()
  	
    tree = ROOT.TChain()
    tree.Add(file+"/"+dataset+"/DecayTree")
    
    #Check if the tree has any entries in it
    if tree.GetEntries() == 0:
    	return None
    	#raise Exception ( "No data for dataset: " + datasetname )
    	
    #if not tree:
    #  raise Exception ( "No data for dataset: " + datasetname )
  	
    tree.SetBranchStatus("*",0)
  	
    for varid in vars:
      myvar = vars [ varid  ]
      varRoo  = myvar.getRooRealVar ( part )
      varname = myvar.getBranchName ( "probe" )
      if varid != "Unbias_HLT1":
        b = tree.GetBranch ( varname )
      keep = False
      if varid == xvar:
        print "Variable " + varid + " is X binning variable. Adding to RooDataSet."
        keep = True
      elif varid == yvar:
        print "Variable " + varid + " is Y binning variable. Adding to RooDataSet."
        keep = True
      elif varid == zvar:
        print "Variable " + varid + " is Z binning variable. Adding to RooDataSet."
        keep = True
      elif varid == "sweight":
        print "Variable " + varid + " is sWeight. Adding to RooDataSet."
        keep = True
      elif varid in trackcuts:
        print "Variable " + varid + " is in track cuts. Adding to RooDataSet."
        keep = True
      elif varid in pidcuts:
        print "Variable " + varid + " is in PID cuts. Adding to RooDataSet."
        keep = True
      if keep == True:
        b.SetStatus(1)
        b.SetName ( varRoo.GetName() )
        roovars [ varRoo.GetName() ] = varRoo
        listOfVars.add ( varRoo )
      if not b:
        print "Cannot load branch " + varname + " from TTree: " + datasetname
        continue
          
    data = RooDataSet("data","data",tree.CloneTree(),listOfVars)
    
    if i==0:
    	print "Initialising RooDataSet with data from tuple " + dataset 
    	data_total = data
    else:
    	print "Appending additional data from tuple " + dataset
    	data_total.append(data)
    i+=1

  os.remove(tmp.GetName())
  os.rmdir
  data_total.SetName(datasetname+"ds")
  data_total.SetTitle("RooDataset automatically generated from TTree "+datasetname)

  return data_total
 
  
if __name__ == "__main__":
  print "TESTING"
  ds = getDataSetFromTuple (
    file=TFile.Open("tmp/"+os.getenv('USER')+"/PIDCalib.root"),
    mother="Lam0",
    part="P")

  ds.Print()
