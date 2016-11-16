import ROOT
from ROOT import (RooRealVar, RooDataSet, RooArgSet, TFile)
from copy import copy
import os

###
### MuPlusFromJpsi2MuMu;16  DecayTree
### pminusFromL0;5  DecayTree
### PiPlusFromTaggedD;4 DecayTree
### MuMinusFromJpsi2MuMu;3  DecayTree
### KMinusFromTaggedD;2 DecayTree
### pplusFromL0;2 DecayTree
### KPlusFromTaggedD;2  DecayTree
### PiMinusFromTaggedD;2  DecayTree
###


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
        'Charge':           var('Charge',                      "{particle}_trackcharge"     , 'charge'      ),
        'nTracks':          var('nTracks',                     "nTracks"                    , 'nTracks'     ),
        'runNumber':        var('runNumber',                   "runNumber"                  , 'runnumber'   ),
        'DLLK':             var('{particle}_CombDLLK',         "{particle}_Brunel_PIDK"     , 'dll'         ),
        'DLLp':             var('{particle}_CombDLLp',         "{particle}_Brunel_PIDp"     , 'dll'         ),
        'DLLe':             var('{particle}_CombDLLe',         "{particle}_Brunel_PIDe"     , 'dll'         ),
        'DLLmu':            var('{particle}_CombDLLmu',        "{particle}_Brunel_PIDmu"    , 'dll'         ),
##        'DLLpK':            var('My_DLLpK',                                                ,               ),
        'V2ProbNNK':        var('{particle}_V2ProbNNK',        '{particle}_Brunel_V2ProbNNk'       , 'prob'        ),
        'V2ProbNNpi':       var('{particle}_V2ProbNNpi',       '{particle}_Brunel_V2ProbNNpi'      , 'prob'        ),
        'V2ProbNNp':        var('{particle}_V2ProbNNp',        '{particle}_Brunel_V2ProbNNp'       , 'prob'        ),
        'V2ProbNNmu':       var('{particle}_V2ProbNNmu',       '{particle}_Brunel_V2ProbNNmu'      , 'prob'        ),
        'V2ProbNNe':        var('{particle}_V2ProbNNe',        '{particle}_Brunel_V2ProbNNe'       , 'prob'        ),
        'V2ProbNNghost':    var('{particle}_V2ProbNNghost',    '{particle}_Brunel_V2ProbNNghost'   , 'prob'        ),
        'V3ProbNNK':        var('{particle}_V3ProbNNK',        '{particle}_Brunel_V3ProbNNk'       , 'prob'        ),
        'V3ProbNNpi':       var('{particle}_V3ProbNNpi',       '{particle}_Brunel_V3ProbNNpi'      , 'prob'        ),
        'V3ProbNNp':        var('{particle}_V3ProbNNp',        '{particle}_Brunel_V3ProbNNp'       , 'prob'        ),
        'V3ProbNNmu':       var('{particle}_V3ProbNNmu',       '{particle}_Brunel_V3ProbNNmu'      , 'prob'        ),
        'V3ProbNNe':        var('{particle}_V3ProbNNe',        '{particle}_Brunel_V3ProbNNe'       , 'prob'        ),
        'V3ProbNNghost':    var('{particle}_V3ProbNNghost',    '{particle}_Brunel_V3ProbNNghost'   , 'prob'        ),
        'V4ProbNNK':        var('{particle}_V4ProbNNK',        '{particle}_Brunel_V4ProbNNk'       , 'prob'        ),
        'V4ProbNNpi':       var('{particle}_V4ProbNNpi',       '{particle}_Brunel_V4ProbNNpi'      , 'prob'        ),
        'V4ProbNNp':        var('{particle}_V4ProbNNp',        '{particle}_Brunel_V4ProbNNp'       , 'prob'        ),
        'V4ProbNNmu':       var('{particle}_V4ProbNNmu',       '{particle}_Brunel_V4ProbNNmu'      , 'prob'        ),
        'V4ProbNNe':        var('{particle}_V4ProbNNe',        '{particle}_Brunel_V4ProbNNe'       , 'prob'        ),
        'V4ProbNNghost':    var('{particle}_V4ProbNNghost',    '{particle}_Brunel_V4ProbNNghost'   , 'prob'        ),
#        'trackcharge':      var('{particle}_trackcharge',      '{particle}_trackcharge'     , 'charge'      ),
        'P':                var('{particle}_P',                '{particle}_Brunel_P'               , 'p'           ),
        'PT':               var('{particle}_PT',               '{particle}_Brunel_PT'              , 'pt'          ),
        'ETA':              var('{particle}_Eta',              '{particle}_Brunel_ETA'             , 'eta'         ),
        'PHI':              var('{particle}_Phi',              '{particle}_Brunel_PHI'             , 'phi'         ),
        'IsMuon':           var('{particle}_IsMuon',           '{particle}_Brunel_isMuon'          , 'bool'        ),
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
        'Unbias_HLT1':      var('{particle}_Unbias_HLT1',      '{particle}_MuonUnbiased'    , 'bool'        ),
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
#        'trackcharge':      var('{particle}_trackcharge',      '{particle}_trackcharge'     , 'charge'      ),
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
        'sweight':          var('nsig_sw',                     '{particle}_sWeight'         , [-10,10]      ),
    }


datasets = {
  'DSt_Pi' : ["DSt_PiMTuple", "DSt_PiPTuple"],
  'DSt_K'  : ["DSt_KPTuple", "DSt_KMTuple"],
  'Lam0_P' : ["Lam0_PTuple", "Lam0_PbarTuple", "Lam0_HPT_PTuple", "Lam0_HPT_PbarTuple", "Lam0_VHPT_PTuple", "Lam0_VHPT_PbarTuple"],
  'Jpsi_Mu': ["Jpsi_MuPTuple", "Jpsi_MuMTuple"]
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
    print "Cannot configure dataset " + datasetname
    return RooDataSet()

  vars = copy(vars_dataset)
  if datasetname in additionalVariables:
    vars.update ( additionalVariables[datasetname] )

  list = ROOT.TList ()
  for dataset in datasets [ datasetname ]:
    list.Add ( file.Get ( dataset + "/DecayTree" ) )

  tmp = ROOT.TFile.Open ( "/tmp/" + os.getenv('USER') + "/tmpPidCalib.root" , "RECREATE")
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

  return RooDataSet ( datasetname + "ds", 
                      "RooDataset automatically generated from TTree "+datasetname,
                      tree, listOfVars 
                    )

 
    

if __name__ == "__main__":
  print "TESTING"
  ds = getDataSetFromTuple (
    file=TFile.Open("/afs/cern.ch/work/l/landerli/afsgangadir/workspace/landerli/LocalXML/295/0/output/PIDCalib.root"), 
    mother="Lam0",
    part="P")

  ds.Print()

