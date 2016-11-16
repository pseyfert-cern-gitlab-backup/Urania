import ROOT
import sys
import warnings
from PIDPerfScripts.Definitions import *
from PIDPerfScripts.Exceptions import *
from PIDPerfScripts.RunDictFuncs import *
from PIDPerfScripts.TupleDataset import *
from  PIDPerfScripts import OverrideCalibDataStore

def GetDataSetNameDictionary(PartName):
    #======================================================================
    # Define Mother and Workspace name given Particle name
    #======================================================================
    MotherName = GetMotherName(PartName)
    WSName = GetWorkspaceName(PartName)

    ret = {'MotherName'    : GetMotherName(PartName),
           'WorkspaceName' : GetWorkspaceName(PartName)
           }

    return ret


def GetDataSets(StripVer, MagPolarity, PartName, TrackCuts, runMin=None, runMax=None,
                verbose=False, allowMissingDataSets=False, minEntries=0, maxFiles=-1, triggerList=[]):

    CheckStripVer(StripVer)
    CheckMagPol(MagPolarity)
    CheckPartType(PartName)

    #======================================================================
    # Create dictionary holding:
    # - Reconstruction version    ['RecoVer']
    # - np.array of:
    #        - MagUp run limits   ['UpRuns']
    #        - MagDown run limits ['DownRuns']
    #======================================================================
    DataDict = GetRunDictionary(StripVer, PartName , verbose )

    #======================================================================
    # Determine min and max file indicies
    #======================================================================
    IndexDict = GetMinMaxFileDictionary(DataDict, MagPolarity,
                                        runMin, runMax, maxFiles , verbose )

    #======================================================================
    # Append runNumber limits to TrackCuts
    #======================================================================
    if None not in (runMin, runMax):
        if TrackCuts!='':
            TrackCuts+=' && '
        TrackCuts+='runNumber>='+runMin+' && runNumber<='+runMax
    if verbose:
        print 'Track Cuts: ', TrackCuts


    #======================================================================
    # Get the DataSets
    #======================================================================
    DataSets = []

    for i in xrange(IndexDict['minIndex'], IndexDict['maxIndex']+1):
        DataSet = GetDataSet(StripVer, MagPolarity, PartName, TrackCuts, i, verbose,
                             allowMissingDataSets, minEntries, triggerList)
        if DataSet is not None:
            DataSets.append(DataSet)
    return DataSets

def GetDataSet(StripVer, MagPolarity, PartName, TrackCuts, index, verbose=False,
               allowMissingDataSets=False, minEntries=0, triggerList=[]):

    from os import getenv

    CheckStripVer(StripVer)
    CheckMagPol(MagPolarity)
    CheckPartType(PartName)

    #======================================================================
    # Create dictionary holding:
    # - Reconstruction version    ['RecoVer']
    # - np.array of:
    #        - MagUp run limits   ['UpRuns']
    #        - MagDown run limits ['DownRuns']
    #======================================================================
    #DataDict = GetRunDictionary(StripVer, PartName)
    RecoVer = GetRecoVer(StripVer)# DataDict['RecoVer']

    #======================================================================
    # Determine Mother and Workspace names
    #======================================================================
    DataSetNameDict = GetDataSetNameDictionary(PartName)

    PartType = GetRealPartType(PartName)

    fname_protocol = ""
    fname_query = ""
    fname_extra = ""

    merged_fname = ""
    fname = OverrideCalibDataStore.GetFileName ( index )
    if fname == None or fname == "":
      CalibDataProtocol=os.getenv("CALIBDATAURLPROTOCOL")
      CalibDataExtra=os.getenv("CALIBDATAEXTRA")
      

      # set the URL protocol (if applicable)
      if CalibDataProtocol is not None and CalibDataProtocol!="":
          fname_protocol = "{0}".format(CalibDataProtocol)


      if CalibDataExtra is not None and CalibDataExtra!="":
          fname_extra = "{0}".format(CalibDataExtra)

      vname_head = "CALIBDATASTORE" 
      fname_head = os.getenv(vname_head)
      if fname_head is None:
          raise GetEnvError("Cannot retrieve dataset, environmental variable %s has not been set." %vname_head)

      fname = ("{prtcol}//{extra}//{topdir}/Reco{reco}_DATA/{pol}/"
               "{mother}_{part}_{pol}_Strip{strp}_{idx}.root").format(
          prtcol=fname_protocol, extra=fname_extra,topdir=fname_head, reco=RecoVer,
          pol=MagPolarity, mother=DataSetNameDict['MotherName'],
          part=PartType, strp=StripVer, idx=index)

      merged_fname = ("{prtcol}//{extra}//{topdir}/Reco{reco}_DATA/{pol}/"
               "PIDCalib_{pol}_Strip{strp}_{idx}.root").format(
          prtcol=fname_protocol, extra=fname_extra,topdir=fname_head, reco=RecoVer,
          pol=MagPolarity, mother=DataSetNameDict['MotherName'],
          part=PartType, strp=StripVer, idx=index)


#    fname = ("{prtcol}{topdir}/{pol}/{part}/"
#             "{mother}_{part}_{pol}_Strip{strp}_{idx}.root{qry}").format(
#         prtcol=fname_protocol, topdir=fname_head,
#         pol=MagPolarity, mother=DataSetNameDict['MotherName'],
#         part=PartType, strp=StripVer, idx=index, qry=fname_query)



    if verbose:
      print "Attempting to open file {0} for reading".format(fname)

    f = ROOT.TFile.Open(fname)
    if not f:
      f = ROOT.TFile.Open ( merged_fname )

    if not f:
        if allowMissingDataSets:
            warnings.warn("File %s does not exist. Skipping this subsample" %fname)
            return None
        else:
            raise IOError("Failed to open file %s for reading" %fname)

    wsname=DataSetNameDict['WorkspaceName']
    if verbose:
      print "Attempting to get workspace {0}".format(wsname)
    ws = f.Get(wsname)

    ## Lucio Anderlini -- May 26, 2015
    ## The following code tries to load the dataset directly from the nTuple
    ## in case the RooWorkspace is not available.

    if ws:
      Data = ws.data('data')
    else:
      Data = getDataSetFromTuple ( file      = f
                                  , mother   = DataSetNameDict['MotherName']
                                  , part     = PartType
            )
      print "Automatic conversion from TTree to RooDataSet"
#        raise TFileError("Failed to retrieve workspace {wsname} from file {fname}".format(
#            wsname=DataSetNameDict['WorkspaceName'], fname=fname))

    if not Data:
        raise RooWorkspaceError("RooDataSet not found in workspace %s" %wsname)
    if verbose:
      print "Retrieved data."

    #Data.Print("v")

    #TODO: check for memory leaks here
    if len(triggerList) > 0:
      if verbose:
        print "Loading trigger decisions."
      TriggerDataSet = ws.data("trigger")
      if not TriggerDataSet:
        print "Error loading trigger dataset"
        sys.exit(1)
      #TriggerDataSet.Print()
      TriggerPrefix = PartType + "_"
      LenTriggerPrefix = len(TriggerPrefix)

      reducedTriggerVarSet = ROOT.RooArgSet()
      triggerVarList = ROOT.RooArgList()
      for triggerName in triggerList:
        var = ws.obj(TriggerPrefix+triggerName)
        if not var:
          availbleTriggers = []
          dsVars = TriggerDataSet.get()
          it = dsVars.createIterator()
          while True:
            v = it.Next()
            if not v: break
            availbleTriggers.append(v.GetName()[LenTriggerPrefix:])
          availbleTriggers.sort()
          raise ValueError( "Trigger %s not availble in trigger dataset. Availble triggers are %s"%( triggerName, availbleTriggers.__repr__() ) )
        reducedTriggerVarSet.add(var)
        #triggerVarList.add(var)

      if verbose:
        print "Removing unneeded trigger decisions."
      MiniTriggerDataSet = getattr(TriggerDataSet,"reduce")(reducedTriggerVarSet)
      #MiniTriggerDataSet.Print("v")

      dsVars = MiniTriggerDataSet.get()
      it = dsVars.createIterator()
      formulae = []
      while True:
        v = it.Next()
        if not v: break
        var_name = v.GetName()
        formulaVarList = ROOT.RooArgList()
        formulaVarList.add(v)

        formulae.append( ROOT.RooFormulaVar( var_name+"_Dec", PartType+" "+var_name[LenTriggerPrefix:]+" Decision", "int((int(%s)&1)/1)"%(var_name), formulaVarList) )
        formulae.append( ROOT.RooFormulaVar( var_name+"_TIS", PartType+" "+var_name[LenTriggerPrefix:]+" TIS", "int((int(%s)&2)/2)"%(var_name), formulaVarList) )
        formulae.append( ROOT.RooFormulaVar( var_name+"_TOS", PartType+" "+var_name[LenTriggerPrefix:]+" TOS", "int((int(%s)&4)/4)"%(var_name), formulaVarList) )

      for formula in formulae:
        triggerVarList.add(formula)

      if verbose:
        print "Unpacking trigger decisions."
      MiniTriggerDataSet.addColumns(triggerVarList)
      Data.merge(MiniTriggerDataSet)

    if verbose:
      print "Applying any cuts the dataset."

    #======================================================================
    # Declare Instance of RICHTrackDataSet for Calibration tracks
    #======================================================================
    ROOT.gSystem.Load('libRooStats.so')
    #ROOT.gSystem.Load('libCintex.so')
    #cintex=ROOT.Cintex
    #cintex.Enable()
    ROOT.gSystem.Load('libPIDPerfToolsLib.so')
    ROOT.gSystem.Load('libPIDPerfToolsDict.so')

    DataSet = None
    dsType = None
    if (RecoVer>=14):
        dsType = 'GenericDataSet'

        VariableVector = ROOT.std.vector(ROOT.std.pair("string,string"))()

        for VarName, DataSetVarName in DataSetVariables().iteritems():
          VariableAlias = ROOT.std.pair("string,string")(VarName, DataSetVarName.format(particle=PartType))
          VariableVector.push_back(VariableAlias)

        for triggerName in triggerList:
          LenTriggerPrefix = len(PartType)+1
          for suffix in ["","_Dec","_TIS","_TOS"]:
            VariableAlias = ROOT.std.pair("string,string")(triggerName+suffix, PartType+"_"+triggerName+suffix)
            VariableVector.push_back(VariableAlias)

        DataSet = ROOT.GenericDataSet('Calib_Data'
                                       , Data
                                       , Data.get()
                                       , VariableVector
                                       , TrackCuts
                                       , 'nsig_sw'
                                       )
        #print "DataSet internal store is:", str(DataSet.store())
        #dsType = 'PIDTrackDataSet'
        #DataSet = ROOT.PIDTrackDataSet('Calib_Data'
                                       #, ''
                                       #, Data
                                       #, Data.get()
                                       #, PartType+'_P'
                                       #, PartType+'_PT'
                                       #, PartType+'_Eta'
                                       #, 'nTracks'
                                       #, 'nSPDHits'
                                       #, PartType+'_CombDLLK'
                                       #, PartType+'_CombDLLp'
                                       #, PartType+'_CombDLLe'
                                       #, PartType+'_CombDLLmu'
                                       #, PartType+'_IsMuon'
                                       #, PartType+'_IsMuonLoose'
                                       #, PartType+'_nShared'
                                       #, PartType+'_HasBremAdded'
                                       #, PartType+'_CaloRegion'
                                       #, PartType+'_ProbNNK'
                                       #, PartType+'_ProbNNpi'
                                       #, PartType+'_ProbNNp'
                                       #, PartType+'_ProbNNmu'
                                       #, PartType+'_ProbNNe'
                                       #, TrackCuts
                                       #, 'nsig_sw'
                                       #)

    else:
        print 'use an earlier version of PIDPerfTools'
        #dsType = 'RICHTrackDataSet'
        #DataSet = ROOT.RICHTrackDataSet('Calib_Data'
        #                                , ''
        #                                , Data
        #                                , Data.get()
        #                                , PartType+'_P'
        #                                , PartType+'_PT'
        #                                , PartType+'_Eta'
        #                                , 'nTracks'
        #                                , 'nSPDHits'
        #                                , PartType+'_CombDLLK'
        #                                , PartType+'_CombDLLp'
        #                                , PartType+'_V2ProbNNK'
        #                                , PartType+'_V2ProbNNpi'
        #                                , PartType+'_V2ProbNNp'
        #                                , TrackCuts
        #                                , 'nsig_sw'
        #                                )

    if ws:
      ws.Delete()

    f.Close()
    if verbose:
        print "DataSet is",str(DataSet)+", which uses the internal store:", str(DataSet.store())

    #======================================================================
    # Sanity test: do we have a dataset, and is it empty?
    #======================================================================
    if DataSet is None:
        raise RooDataSetError("Failed to create {0} from RooDataSet".format(
            dsType))

    if DataSet.sumEntries()==0:
        raise RooDataSetError("{0} contains no entries".format(
            dsType))

    if verbose:
        DataSet.Print('v')

    #======================================================================
    # Reduce dataset to only those events within binning limits
    #======================================================================
    #DataSet = None
    #if BinningScheme is not None:
    #    DataSet = AllDataSet.SetInBinSchema(BinningScheme)
    #    AllDataSet.Delete()
    #else:
    #    DataSet = AllDataSet

    #======================================================================
    # Veto ranges with insufficient statistics
    #======================================================================
    if DataSet.sumEntries()<minEntries:
        msg=('Insufficient events in {dsType} ({nEvt}). '
             'Requested at least {minEvts} entries. '
             'Skipping this sumsample').format(
            dsType=dsType, nEvt=DataSet.sumEntries(), minEvts=minEntries)
        warnings.warn( msg )
        return None

    return DataSet
