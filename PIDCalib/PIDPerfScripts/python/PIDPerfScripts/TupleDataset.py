import ROOT
from ROOT import (RooRealVar, RooDataSet, RooArgSet, TFile)
from copy import copy
import os
import time

class var:
  def __init__ (self, dsname, tuplename, range ):
    if isinstance ( range, str ):
      if   range == "prob"     : range = [-1e400, 1e400 ]#range = [0,1]
      elif range == "dll"      : range = [-1e400, 1e400 ]#range = [-1150, 200]
      elif range == "pt"       : range = [-1e400, 1e400 ]#range = [0,200e3]
      elif range == "p"        : range = [-1e400, 1e400 ]#range = [0,500e3]
      elif range == "nTracks"  : range = [-1e400, 1e400 ]#range = [0, 2000]
      elif range == "runnumber": range = [-1e400, 1e400 ]#range = [111761, 999999]
      elif range == "bool"     : range = [-1e400, 1e400 ]#range = [-1, 2]
      elif range == "charge"   : range = [-1e400, 1e400 ]#range = [-2, 2]
      elif range == "nShared"  : range = [-1e400, 1e400 ]#range = [-2, 500]
      elif range == "nSpd"     : range = [-1e400, 1e400 ]#range = [0, 1000]
      elif range == "nRhit"    : range = [-1e400, 1e400 ]#range = [0, 10000]
      elif range == "nPVs"     : range = [-1e400, 1e400 ]#range = [0, 20]
      elif range == "phi"      : range = [-1e400, 1e400 ]#range = [-3.14159, 3.14159 ]
      elif range == "eta"      : range = [-1e400, 1e400 ]#range = [1, 6]

    self.tuplename = tuplename
    self.dsname    = dsname
    self.range     = range

  def getRooRealVar(self, partName):
    name = self.dsname.format ( particle = partName )
    return RooRealVar (name, name, self.range[0], self.range[1])

  def getBranchName(self, partName):
    return self.tuplename.format ( particle = partName )
    
  
vars_dataset = {
        'probe_Charge':           var('Charge',                      "{particle}_Charge"     , 'charge'      ),
        'nTracks':          var('nTracks',                     "nTracks"                    , 'nTracks'     ),
        'runNumber':        var('runNumber',                   "runNumber"                  , 'runnumber'   ),
        'nPVs':        var('nPVs',                   "nPVs"                  , 'nPVs'   ),
        'probe_PIDK':             var('{particle}_CombDLLK',         "{particle}_Brunel_PIDK"     , 'dll'         ),
        'probe_PIDp':             var('{particle}_CombDLLp',         "{particle}_Brunel_PIDp"     , 'dll'         ),
        'probe_PIDe':             var('{particle}_CombDLLe',         "{particle}_Brunel_PIDe"     , 'dll'         ),
        'probe_PIDmu':            var('{particle}_CombDLLmu',        "{particle}_Brunel_PIDmu"    , 'dll'         ),
        'probe_V2ProbNNK':        var('{particle}_V2ProbNNK',        '{particle}_MC12TuneV2_ProbNNk'       , 'prob'        ),
        'probe_V2ProbNNpi':       var('{particle}_V2ProbNNpi',       '{particle}_MC12TuneV2_ProbNNpi'      , 'prob'        ),
        'probe_V2ProbNNp':        var('{particle}_V2ProbNNp',        '{particle}_MC12TuneV2_ProbNNp'       , 'prob'        ),
        'probe_V2ProbNNmu':       var('{particle}_V2ProbNNmu',       '{particle}_MC12TuneV2_ProbNNmu'      , 'prob'        ),
        'probe_V2ProbNNe':        var('{particle}_V2ProbNNe',        '{particle}_MC12TuneV2_ProbNNe'       , 'prob'        ),
        'probe_V2ProbNNghost':    var('{particle}_V2ProbNNghost',    '{particle}_MC12TuneV2_ProbNNghost'   , 'prob'        ),
        'probe_V3ProbNNK':        var('{particle}_V3ProbNNK',        '{particle}_MC12TuneV3_ProbNNk'       , 'prob'        ),
        'probe_V3ProbNNpi':       var('{particle}_V3ProbNNpi',       '{particle}_MC12TuneV3_ProbNNpi'      , 'prob'        ),
        'probe_V3ProbNNp':        var('{particle}_V3ProbNNp',        '{particle}_MC12TuneV3_ProbNNp'       , 'prob'        ),
        'probe_V3ProbNNmu':       var('{particle}_V3ProbNNmu',       '{particle}_MC12TuneV3_ProbNNmu'      , 'prob'        ),
        'probe_V3ProbNNe':        var('{particle}_V3ProbNNe',        '{particle}_MC12TuneV3_ProbNNe'       , 'prob'        ),
        'probe_V3ProbNNghost':    var('{particle}_V3ProbNNghost',    '{particle}_MC12TuneV3_ProbNNghost'   , 'prob'        ),
        'probe_V4ProbNNK':        var('{particle}_V4ProbNNK',        '{particle}_MC12TuneV4_ProbNNk'       , 'prob'        ),
        'probe_V4ProbNNpi':       var('{particle}_V4ProbNNpi',       '{particle}_MC12TuneV4_ProbNNpi'      , 'prob'        ),
        'probe_V4ProbNNp':        var('{particle}_V4ProbNNp',        '{particle}_MC12TuneV4_ProbNNp'       , 'prob'        ),
        'probe_V4ProbNNmu':       var('{particle}_V4ProbNNmu',       '{particle}_MC12TuneV4_ProbNNmu'      , 'prob'        ),
        'probe_V4ProbNNe':        var('{particle}_V4ProbNNe',        '{particle}_MC12TuneV4_ProbNNe'       , 'prob'        ),
        'probe_V4ProbNNghost':    var('{particle}_V4ProbNNghost',    '{particle}_MC12TuneV4_ProbNNghost'   , 'prob'        ),
        'probe_V1ProbNNK':        var('{particle}_V1ProbNNK',        '{particle}_MC15TuneV1_ProbNNk'       , 'prob'        ),
        'probe_V1ProbNNpi':       var('{particle}_V1ProbNNpi',       '{particle}_MC15TuneV1_ProbNNpi'      , 'prob'        ),
        'probe_V1ProbNNp':        var('{particle}_V1ProbNNp',        '{particle}_MC15TuneV1_ProbNNp'       , 'prob'        ),
        'probe_V1ProbNNmu':       var('{particle}_V1ProbNNmu',       '{particle}_MC15TuneV1_ProbNNmu'      , 'prob'        ),
        'probe_V1ProbNNe':        var('{particle}_V1ProbNNe',        '{particle}_MC15TuneV1_ProbNNe'       , 'prob'        ),
        'probe_V1ProbNNghost':    var('{particle}_V1ProbNNghost',    '{particle}_MC15TuneV1_ProbNNghost'   , 'prob'        ),
#        'trackcharge':      var('{particle}_trackcharge',      '{particle}_trackcharge'     , 'charge'      ),
        'P':                var('{particle}_P',                '{particle}_Brunel_P'               , 'p'           ),
        'PT':               var('{particle}_PT',               '{particle}_Brunel_PT'              , 'pt'          ),
        'ETA':              var('{particle}_Eta',              '{particle}_Brunel_ETA'             , 'eta'         ),
        'PHI':              var('{particle}_Phi',              '{particle}_Brunel_PHI'             , 'phi'         ),
        'IsMuon':           var('{particle}_IsMuon',           '{particle}_Brunel_isMuon'          , 'bool'        ),
        'IsMuonTight':           var('{particle}_IsMuonTight',           '{particle}_Brunel_isMuonTight'          , 'bool'        ),
        'InMuonAcc':        var('{particle}_InMuonAcc',        '{particle}_Brunel_InMuonAcc'       , 'bool'        ),
        'IsMuonLoose':      var('{particle}_IsMuonLoose',      '{particle}_Brunel_isMuonLoose'     , 'bool'        ),
        'nShared':          var('{particle}_nShared',          '{particle}_Brunel_NShared'         , 'nShared'     ),
        'RICHThreshold_pi': var('{particle}_RICHThreshold_pi', '{particle}_Brunel_RICHThresholdPi' , 'bool'        ),
        'RICHThreshold_p':  var('{particle}_RICHThreshold_p',  '{particle}_Brunel_RICHThresholdPr' , 'bool'        ),
        'RICHThreshold_e':  var('{particle}_RICHThreshold_e',  '{particle}_Brunel_RICHThresholdEl' , 'bool'        ),
        'RICHThreshold_K':  var('{particle}_RICHThreshold_K',  '{particle}_Brunel_RICHThresholdKa' , 'bool'        ),
        'RICHThreshold_mu': var('{particle}_RICHThreshold_mu', '{particle}_Brunel_RICHThresholdMu' , 'bool'        ),
        'RICHAerogelUsed':  var('{particle}_RICHAerogelUsed',  '{particle}_Brunel_RICHAerogelUsed' , 'bool'        ),
        'RICH1GasUsed':     var('{particle}_RICH1GasUsed',     '{particle}_Brunel_RICH1GasUsed'    , 'bool'        ),
        'RICH2GasUsed':     var('{particle}_RICH2GasUsed',     '{particle}_Brunel_RICH2GasUsed'    , 'bool'        ),
        'HasRich':          var('{particle}_hasRich',          '{particle}_Brunel_hasRich'         , 'bool'        ),
        'HasCalo':          var('{particle}_hasCalo',          '{particle}_Brunel_hasCalo'         , 'bool'        ),
        #'HasBremAdded':     var('{particle}_HasBremAdded',                                 ,               ),
#        'CaloRegion':       var('{particle}_CaloRegion',                                   ,               ),
        'nSPDHits':         var('nSPDHits',                    'nSPDhits'                   , 'nSpd'        ),
        'Unbias_HLT1':      var('{particle}_Unbias_HLT1',      '{particle}_Brunel_MuonUnbiased'    , 'bool'        ),
        'Unbias_HLT12':     var('{particle}_Unbias_HLT12',     '{particle}_MuonUnbiased'    , 'bool'        ),
#        'ProbeTIS':         var('{particle}_Probe_TIS',        '{particle}_Probe_TIS       ,               ),
#        'TagTOS':           var('{particle}_Tag_TOS',                                      ,               ),
        'tDLLK':             var('{particle}_Tesla_CombDLLK',   "{particle}_PIDK"            , 'dll'         ),
        'tDLLp':             var('{particle}_Tesla_CombDLLp',   "{particle}_PIDp"            , 'dll'         ),
        'tDLLe':             var('{particle}_Tesla_CombDLLe',   "{particle}_PIDe"            , 'dll'         ),
        'tDLLmu':            var('{particle}_Tesla_CombDLLmu',  "{particle}_PIDmu"           , 'dll'         ),
##        'DLLpK':            var('My_DLLpK',                                                ,               ),
        'tV2ProbNNK':        var('{particle}_Tesla_V2ProbNNK',        '{particle}_V2ProbNNk'       , 'prob'        ),
        'tV2ProbNNpi':       var('{particle}_Tesla_V2ProbNNpi',       '{particle}_V2ProbNNpi'      , 'prob'        ),
        'tV2ProbNNp':        var('{particle}_Tesla_V2ProbNNp',        '{particle}_V2ProbNNp'       , 'prob'        ),
        'tV2ProbNNmu':       var('{particle}_Tesla_V2ProbNNmu',       '{particle}_V2ProbNNmu'      , 'prob'        ),
        'tV2ProbNNe':        var('{particle}_Tesla_V2ProbNNe',        '{particle}_V2ProbNNe'       , 'prob'        ),
        'tV2ProbNNghost':    var('{particle}_Tesla_V2ProbNNghost',    '{particle}_V2ProbNNghost'   , 'prob'        ),
        'tV3ProbNNK':        var('{particle}_Tesla_V3ProbNNK',        '{particle}_V3ProbNNk'       , 'prob'        ),
        'tV3ProbNNpi':       var('{particle}_Tesla_V3ProbNNpi',       '{particle}_V3ProbNNpi'      , 'prob'        ),
        'tV3ProbNNp':        var('{particle}_Tesla_V3ProbNNp',        '{particle}_V3ProbNNp'       , 'prob'        ),
        'tV3ProbNNmu':       var('{particle}_Tesla_V3ProbNNmu',       '{particle}_V3ProbNNmu'      , 'prob'        ),
        'tV3ProbNNe':        var('{particle}_Tesla_V3ProbNNe',        '{particle}_V3ProbNNe'       , 'prob'        ),
        'tV3ProbNNghost':    var('{particle}_Tesla_V3ProbNNghost',    '{particle}_V3ProbNNghost'   , 'prob'        ),
        'trackcharge':      var('{particle}_trackcharge',      '{particle}_trackcharge'     , 'charge'      ),
        'tP':                var('{particle}_Tesla_P',                '{particle}_P'               , 'p'           ),
        'tPT':               var('{particle}_Tesla_PT',               '{particle}_PT'              , 'pt'          ),
        'tETA':              var('{particle}_Tesla_Eta',              '{particle}_ETA'             , 'eta'         ),
        'tPHI':              var('{particle}_Tesla_Phi',              '{particle}_PHI'             , 'phi'         ),
        'tIsMuon':           var('{particle}_Tesla_IsMuon',           '{particle}_isMuon'          , 'bool'        ),
        'tInMuonAcc':        var('{particle}_Tesla_InMuonAcc',        '{particle}_InMuonAcc'       , 'bool'        ),
        'tIsMuonLoose':      var('{particle}_Tesla_IsMuonLoose',      '{particle}_isMuonLoose'     , 'bool'        ),
        'tnShared':          var('{particle}_Tesla_nShared',          '{particle}_NShared'         , 'nShared'     ),
        'tRICHThreshold_pi': var('{particle}_Tesla_RICHThreshold_pi', '{particle}_RICHThresholdPi' , 'bool'        ),
        'tRICHThreshold_p':  var('{particle}_Tesla_RICHThreshold_p',  '{particle}_RICHThresholdPr' , 'bool'        ),
        'tRICHThreshold_e':  var('{particle}_Tesla_RICHThreshold_e',  '{particle}_RICHThresholdEl' , 'bool'        ),
        'tRICHThreshold_K':  var('{particle}_Tesla_RICHThreshold_K',  '{particle}_RICHThresholdKa' , 'bool'        ),
        'tRICHThreshold_mu': var('{particle}_Tesla_RICHThreshold_mu', '{particle}_RICHThresholdMu' , 'bool'        ),
        'tRICHAerogelUsed':  var('{particle}_Tesla_RICHAerogelUsed',  '{particle}_RICHAerogelUsed' , 'bool'        ),
        'tRICH1GasUsed':     var('{particle}_Tesla_RICH1GasUsed',     '{particle}_RICH1GasUsed'    , 'bool'        ),
        'tRICH2GasUsed':     var('{particle}_Tesla_RICH2GasUsed',     '{particle}_RICH2GasUsed'    , 'bool'        ),
        'tHasRich':          var('{particle}_Tesla_hasRich',          '{particle}_hasRich'         , 'bool'        ),
        'tHasCalo':          var('{particle}_Tesla_hasCalo',          '{particle}_hasCalo'         , 'bool'        ),
        'nRich1Hits':          var('nRich1Hits',          'nRich1Hits'         , 'nRhit'        ),
        'nRich2Hits':          var('nRich2Hits',          'nRich2Hits'         , 'nRhit'        ),
        'sweight':          var('nsig_sw',                     '{particle}_sWeight'         , [-10,10]      ),
    }


datasets = {
  'DSt_Pi' : ["DSt_PiMTuple", "DSt_PiPTuple"],
  'DSt_K'  : ["DSt_KPTuple", "DSt_KMTuple"],
  'Lam0_P' : ["Lam0_PTuple", "Lam0_PbarTuple", "Lam0_HPT_PTuple", "Lam0_HPT_PbarTuple", "Lam0_VHPT_PTuple", "Lam0_VHPT_PbarTuple"],
  'Jpsi_Mu': ["Jpsi_MuPTuple", "Jpsi_MuMTuple"],
  'P_LcfB' : ["LbLcMu_PTuple", "LbLcMu_PbarTuple"],
  'Sigmac0_P': ["Sigmac0_PbarTuple","Sigmac0_PTuple"],
  'DsPhi_K': ["DsPhi_KP_notagTuple","DsPhi_KM_notagTuple","DsPhi_KPTuple","DsPhi_KMTuple"],
  'Sigmacpp_P': ["Sigmacpp_PbarTuple","Sigmacpp_PTuple"],
  'DSt3Pi_Pi' : ["DSt3Pi_PiMTuple", "DSt3Pi_PiPTuple"],
  'DSt3Pi_K'  : ["DSt3Pi_KPTuple", "DSt3Pi_KMTuple"],
  'Phi_K': ["Phi_KMTuple","Phi_KPTuple"],
  'Phi_Mu': ["Phi_MuMTuple","Phi_MuPTuple"],
  'B_Jpsi_Mu': ["B_Jpsi_MuPTuple","B_Jpsi_MuMTuple"],
  'Jpsi_P': ["Jpsi_PTuple","Jpsi_PbarTuple"],
  'KS_Pi':  ["KS_PiPTuple","KS_PiMTuple"],
  #'Jpsi_e': ["Jpsi_EPTuple","Jpsi_EMTuple"],
  'B_Jpsi_P': ["B_Jpsi_PTuple","B_Jpsi_PbarTuple"],
  'B_Jpsi_e': ["B_Jpsi_EPTuple","B_Jpsi_EMTuple"]
}

additionalVariables = {
  'DSt_Pi' :  { 
    'HasCalo': var('{particle}_hasCalo',  '{particle}_hasCalo', 'bool'),
  }
}

def getDataSetFromTuple ( file, mother, part ):
  roovars = {}
  listOfVars = RooArgSet()

  datasetname = mother + "_" + part

  if datasetname not in datasets:
    print "Cannot configure dataset " + datasetname + ", not in Turbo stream"
    return RooDataSet()

  vars = copy(vars_dataset)
  if datasetname in additionalVariables:
    vars.update ( additionalVariables[datasetname] )

  list = ROOT.TList ()
  for dataset in datasets [ datasetname ]:
    list.Add ( file.Get ( dataset + "/DecayTree" ) )
    print "Try to get tree: "+dataset

  tmp = ROOT.TFile.Open (  "/tmp/"+os.getenv('USER') + "/tmpPidCalib_"+datasetname+"{0}.root".format(time.time()) , "RECREATE")
  print tmp.GetName()
  tree = ROOT.TTree.MergeTrees ( list )  
  if not tree:
    raise Exception ( "No data for dataset: " + datasetname )

  for varid in vars:
    myvar = vars [ varid  ]
    varRoo  = myvar.getRooRealVar ( part )
    varname = myvar.getBranchName ( "probe" )

    b = tree.GetBranch ( varname )
    if not b:
      print "Cannot load branch " + varname + " from TTree: " + datasetname 
      continue

    b.SetName ( varRoo.GetName() )
    roovars [ varRoo.GetName() ] = varRoo
    listOfVars.add ( varRoo )
 
  print "before RooDataSet: ({0},{1})".format(time.time(),time.clock())

  os.remove(tmp.GetName())

  return RooDataSet ( datasetname + "ds", 
                      "RooDataset automatically generated from TTree "+datasetname,
                      tree, listOfVars 
                    )

 
    

if __name__ == "__main__":
  print "TESTING"
  ds = getDataSetFromTuple (
    file=TFile.Open("tmp/"+os.getenv('USER')+"/PIDCalib.root"),
    mother="Lam0",
    part="P")

  ds.Print()

