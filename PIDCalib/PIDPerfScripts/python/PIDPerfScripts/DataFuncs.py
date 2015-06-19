import ROOT
from PIDPerfScripts.RunRangeFuncs import *
from GaudiPython import gbl
import sys
import exceptions
import warnings

class GetEnvError(exceptions.Exception):
    pass

class TFileError(exceptions.Exception):
    pass

class RooWorkspaceError(exceptions.Exception):
    pass

class RooDataSetError(exceptions.Exception):
    pass

def GetRealPartType(PartName):
    CheckPartType(PartName)
    if PartName == 'K' or PartName == 'K_MuonUnBiased':
        return 'K'
    elif PartName == 'Pi' or PartName == 'Pi_MuonUnBiased':
        return 'Pi'
    elif PartName == 'P' or PartName == 'P_MuonUnBiased':
        return 'P'
    else:
        return 'Mu'

# N.B. The following method will need to be changed once the
# Lambda_c proton samples are included
def GetMotherName(PartName):
    #PartType = GetRealPartType(PartName)
    if PartName == 'K' or PartName == 'Pi':
        return 'DSt'
    elif PartName == 'P':
        return 'Lam0'
    if PartName == 'K_MuonUnBiased' or PartName == 'Pi_MuonUnBiased':
        return 'DSt_MuonUnBiased'
    elif PartName == 'P_MuonUnBiased':
        return 'Lam0'
    else:
        return 'Jpsi'

# N.B. The following method will need to be changed once the
# Lambda_c proton samples are included
def GetWorkspaceName(PartName):
    PartType = GetRealPartType(PartName)
    if PartType == 'K' or PartType == 'Pi':
        return 'RSDStCalib'
    elif PartType == 'P':
        return 'Lam0Calib'
    else:
        return 'JpsiCalib'

def IsMuonUnBiased(PartName):
    CheckPartType(PartName)
    if PartName in ("Mu", "K_MuonUnBiased", "Pi_MuonUnBiased", "P_MuonUnBiased"):
        return True
    else:
        return False
    
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
                verbose=False, allowMissingDataSets=False, minEntries=1000):
    
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
    DataDict = GetRunDictionary(StripVer, PartName)

    #======================================================================
    # Determine min and max file indicies 
    #======================================================================
    IndexDict = GetMinMaxFileDictionary(DataDict, MagPolarity,
                                        runMin, runMax)

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
                             allowMissingDataSets, minEntries)
        if DataSet is not None:
            DataSets.append(DataSet)
    return DataSets

def GetDataSet(StripVer, MagPolarity, PartName, TrackCuts, index, verbose=False,
               allowMissingDataSets=False, minEntries=1000):

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
    DataDict = GetRunDictionary(StripVer, PartName)

    #======================================================================
    # Determine Mother and Workspace names
    #======================================================================
    DataSetNameDict = GetDataSetNameDictionary(PartName)

    PartType = GetRealPartType(PartName)

    fname_protocol = ""
    fname_query = ""
    
    CalibDataProtocol=os.getenv("CALIBDATAURLPROTOCOL")
    CalibDataQuery=os.getenv("CALIBDATAURLQUERY")   

    # set the URL protocol (if applicable)
    if CalibDataProtocol is not None and CalibDataProtocol!="":
        fname_protocol = "{0}://".format(CalibDataProtocol)

    # set the URL query (if applicable)
    if CalibDataQuery is not None and CalibDataQuery!="":
        fname_query = "?{0}".format(CalibDataQuery)

    vname_head = "CALIBDATASTORE" if not IsMuonUnBiased(PartName) else "MUONCALIBDATASTORE"
    fname_head = os.getenv(vname_head)
    if fname_head is None:
        raise GetEnvError("Cannot retrieve dataset, environmental variable %s has not been set." %vname_head)
    
    fname = "{prtcol}{topdir}/Reco{reco}_DATA/{pol}/{mother}_{part}_{pol}_Strip{strp}_{idx}.root{qry}".format(
        prtcol=fname_protocol, topdir=fname_head, reco=DataDict['RecoVer'],
        pol=MagPolarity, mother=DataSetNameDict['MotherName'],
        part=PartType, strp=StripVer, idx=index, qry=fname_query)
    
    f = ROOT.TFile.Open(fname)
    if not f:
        if allowMissingDataSets:
            warnings.warn("File %s does not exist. Skipping this subsample" %fname)
            return None
        else:
            raise IOError("Failed to open file %s for reading" %fname)

    wsname=DataSetNameDict['WorkspaceName']
    ws = f.Get(wsname)
    if not ws:
        raise TFileError("Failed to retrieve workspace {wsname} from file {fname}".format(
            wsname=DataSetNameDict['WorkspaceName'], fname=fname))
    Data = ws.data('data')
    if not Data:
        raise RooWorkspaceError("RooDataSet not found in workspace %s" %wsname)
        
    #======================================================================
    # Declare Instance of RICHTrackDataSet for Calibration tracks
    #======================================================================
        
    DataSet = gbl.PIDTrackDataSet('Calib_Data'
                                  , ''
                                  , Data
                                  , Data.get()
                                  , PartType+'_P'
                                  , PartType+'_PT'
                                  , PartType+'_Eta'
                                  , 'nTracks'
                                  , PartType+'_CombDLLK'
                                  , PartType+'_CombDLLp'
                                  , PartType+'_CombDLLe'
                                  , PartType+'_CombDLLmu'
                                  , PartType+'_IsMuon'
                                  , PartType+'_IsMuonLoose'
                                  , PartType+'_nShared'
                                  , PartType+'_ProbNNK'
                                  , PartType+'_ProbNNpi'
                                  , PartType+'_ProbNNp'
                                  , PartType+'_ProbNNmu'
                                  , PartType+'_ProbNNe'
                                  , TrackCuts
                                  , 'nsig_sw'
                                  )
    ws.Delete()
    f.Close()
    if verbose:
        print DataSet, type(DataSet)
        
    #======================================================================
    # Sanity test: do we have a dataset, and is it empty?
    #======================================================================
    if DataSet is None:
        raise RooDataSetError("Failed to create PIDTrackDataSet from RooDataSet")
        
    if DataSet.sumEntries()==0:
        raise RooDataSetError("PIDTrackDataSet contains no entries")

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
        warnings.warn( 'Insufficient events in PIDTrackDataSet ({nEvt}). Requested at least {minEvts} entries. Skipping this sumsample'.format(
            nEvt=DataSet.sumEntries(), minEvts=minEntries) )
        return None
                  
    return DataSet

def GetPerfPlotList( PerfFunc,
                     StripVer,
                     MagPolarity,
                     PartName,
                     DLLCutList,
                     TrackCuts,
                     BinningScheme=None,
                     runMin=None,
                     runMax=None,
                     verbose=True,
                     allowMissingDataSets=False):
  
    #======================================================================
    # Declare default list of PID plots
    #======================================================================
    Plots = []
 
    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
    for DataSet in GetDataSets(StripVer, MagPolarity, PartName, TrackCuts,
                               runMin, runMax, verbose, allowMissingDataSets):
        
        #======================================================================
        # Run Specific implementation of PerfCalculator
        #======================================================================
        Plots = PerfFunc(PartName, DataSet, DLLCutList, BinningScheme, Plots,
                         verbose)

        #======================================================================
        # Delete DataSet
        #======================================================================
        DataSet.Delete()

    #======================================================================
    # Return list of plots
    #======================================================================
    return Plots


def GetPerfResultList(PerfFunc,
                      StripVer,
                      MagPolarity,
                      PartName,
                      DLLCutList,
                      TrackCuts,
                      runMin=None,
                      runMax=None,
                      verbose=True,
                      allowMissingDataSets=False):


    #======================================================================
    # Declare default list of PID results
    #======================================================================
    PIDResults = []

    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
    for DataSet in GetDataSets(StripVer, MagPolarity, PartName, TrackCuts,
                               runMin, runMax, verbose, allowMissingDataSets):
        
        #======================================================================
        # Run Specific implementation of PerfCalculator
        #======================================================================
        PerfFunc(DataSet, DLLCutList, PIDResults, verbose)
        if verbose:
            print PIDResults
        
        #======================================================================
        # Delete DataSet
        #======================================================================
        DataSet.Delete()

    #======================================================================
    # Return list PIDResults
    #======================================================================
    return PIDResults
