import ROOT
import sys
import warnings
import time
from PIDPerfScripts.Definitions import *
from PIDPerfScripts.Exceptions import *
from PIDPerfScripts.RunDictFuncs import *
from PIDPerfScripts.TupleDataset import *
from  PIDPerfScripts import OverrideCalibDataStore
from DIRAC.Resources.Storage.StorageElement     import StorageElement

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
    if None not in (runMin, runMax):
        if TrackCuts!='':
            TrackCuts+=' && '
        TrackCuts+='runNumber>='+runMin+' && runNumber<='+runMax
    if verbose:
        print 'Track Cuts: ', TrackCuts
    
    if verbose:
       print "Attemptng to get URLS: ({0},{1}) ".format(time.time(),time.clock())  
    files = GetFiles(StripVer,MagPolarity,PartName,runMin,runMax,maxFiles,verbose)  
 
    if verbose:
       print "Obtain URLS: ({0},{1}) ".format(time.time(),time.clock())
    DataSets = []

    for file in files:
        DataSet = GetDataSet(StripVer, MagPolarity,PartName,TrackCuts,file, verbose,
                             allowMissingDataSets, minEntries, triggerList)
        if DataSet is not None:
            DataSets.append(DataSet)
    return DataSets

def GetDataSet(StripVer, MagPolarity,PartName,TrackCuts,file, verbose=False,
               allowMissingDataSets=False, minEntries=0, triggerList=[]):

    RecoVer = GetRecoVer(StripVer)
 
    if verbose:
      print "Attempting to open file {0} for reading: ({1},{2})".format(file,time.time(),time.clock())
         
 
    f = ROOT.TFile.Open(file)

    if not f:
        if allowMissingDataSets:
            warnings.warn("File %s does not exist. Skipping this subsample" %file)
            return None
        else:
            raise IOError("Failed to open file %s for reading" %file)

    DataSetNameDict = GetDataSetNameDictionary(PartName)
    wsname=DataSetNameDict['WorkspaceName']
    if verbose:
      print "Attempting to get workspace {0}".format(wsname)
    ws = f.Get(wsname)

    ## Lucio Anderlini -- May 26, 2015
    ## The following code tries to load the dataset directly from the nTuple
    ## in case the RooWorkspace is not available.
    CheckPartType(PartName)
    PartType = GetRealPartType(PartName)        
    DataSetNameDict = GetDataSetNameDictionary(PartName)
   
    if verbose: print "Attempting to create dataset: ({0},{1})".format(time.time(),time.clock())
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
      print "Retrieved data: ({0},{1})".format(time.time(),time.clock())

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

def GetFiles(StripVer,MagPolarity,PartName,runMin=None,runMax=None,maxFiles = -1,verbose=False):
    CheckStripVer(StripVer)
    files = OverrideCalibDataStore.GetDictFiles(runMin,runMax,maxFiles,verbose)
    if len(files) > 0: 
       print "Using files from:" + os.getenv('OVERRIDECALIBDATASTORE')
       return files

    if CheckIsTurbo(StripVer):        
        from LHCbDIRAC.Interfaces.API.DiracLHCb import DiracLHCb
        time.sleep(5)
        dirac = DiracLHCb()

        CheckMagPol(MagPolarity) 
     
        query = GetTurboPath(StripVer,MagPolarity)
        print query
        lfns = dirac.bkQueryPath ( query )
        if 'Value' not in lfns.keys(): print "Value not in lfns.keys()"
        if 'LFNs' not in lfns['Value'].keys(): "LFNs not in lfns['Value'].keys()"
        if maxFiles > 0: lfns = lfns['Value']['LFNs'].keys()[:int(maxFiles)]
        else: lfns = lfns['Value']['LFNs'].keys()
 
        replicas = dirac.getAllReplicas ( lfns ) ['Value']['Successful']
        replica_failed = dirac.getAllReplicas ( lfns ) ['Value']['Failed']
 
        if len(replica_failed) == 0: print "obtain replicas for all files successfully"        

        for lfn_fail in replica_failed:
            print lfn_failed

        replicaDict = {}

        for lfn in replicas:
            for site in replicas[lfn].keys():
                pfn = replicas[lfn][site]
                if site not in replicaDict: replicaDict[site] = []

                replicaDict[site] += [ lfn ]
                break  ## max 1 replica per lfn to avoid double counting

        for site in replicaDict:
             urls = dirac.getAccessURL ( replicaDict[site], site )
             urls = StorageElement ( site ).getURL( replicaDict[site], "root" )#("root", "xroot")) 
             urls = urls['Value']['Successful'].values()
             if len(urls) and "root:" not in urls[0]:
                  urls = StorageElement ( site ).getURL( replicaDict[site] )#("root", "xroot")) 
                  urls = urls['Value']['Successful'].values()
             files += urls
             print files[-1]     
        return files
    else:
        #======================================================================
        # Create dictionary holding:
        # - Reconstruction version    ['RecoVer']
        # - np.array of:
        #        - MagUp run limits   ['UpRuns']
        #        - MagDown run limits ['DownRuns']
        #======================================================================
        CheckPartType(PartName)
        DataDict = GetRunDictionary(StripVer, PartName , verbose )

        #======================================================================
        # Determine min and max file indicies
        #======================================================================
        CheckMagPol(MagPolarity)
        IndexDict = GetMinMaxFileDictionary(DataDict, MagPolarity,
                                            runMin, runMax, maxFiles , verbose )

        from os import getenv
        
        RecoVer = GetRecoVer(StripVer)

        stv = StripVer
        if StripVer == '21_MCTuneV4':
           stv = '21'
        if StripVer == '21r1_MCTuneV4':
           stv = '21r1'
        if StripVer == '23_MCTuneV1':
           stv = '23'


        DataSetNameDict = GetDataSetNameDictionary(PartName)

        fname_protocol = ""
        fname_query = ""
        fname_extra = ""

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

        PartType = GetRealPartType(PartName)
        for i in xrange(IndexDict['minIndex'], IndexDict['maxIndex']+1):
            fname = ("{prtcol}//{extra}//{topdir}/Reco{reco}_DATA/{pol}/"
                     "{mother}_{part}_{pol}_Strip{strp}_{idx}.root").format(
                prtcol=fname_protocol, extra=fname_extra,topdir=fname_head, reco=RecoVer,
                pol=MagPolarity, mother=DataSetNameDict['MotherName'],
                part=PartType, strp=stv, idx=i)
            files += [fname];
            print files[-1]  
        return files
