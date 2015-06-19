import pickle
import os
import numpy as np
from pprint import pprint
import sys

def GetMomBinVarName():
    return "P"

def GetPtBinVarName():
    return "PT"

def GetEtaBinVarName():
    return "ETA"

def GetNTracksBinVarName():
    return "nTrack"

def GetBinVarNames():
   return (GetMomBinVarName(), GetPtBinVarName(),
           GetEtaBinVarName(), GetNTracksBinVarName())

def GetRICHPIDRealPartTypes():
    return ("K", "Pi", "P")

def GetRICHPIDPartTypes():
    return GetRICHPIDRealPartTypes()

def GetMuonPIDRealPartTypes():
    return ("Mu",)

def GetMuonPIDPartTypes():
    return GetMuonPIDRealPartTypes()+tuple(['{0}_MuonUnBiased'.format(
        p) for p in GetRICHPIDRealPartTypes()])

def GetRealPartTypes():
    return GetRICHPIDRealPartTypes()+GetMuonPIDRealPartTypes()

def GetPartTypes():
    return GetRICHPIDPartTypes()+GetMuonPIDPartTypes()

def GetPklTypes():
    return GetRICHPIDPartTypes()

def CheckRealPartType(PartName):
    ValidPartNames=GetRealPartTypes()
    if PartName not in ValidPartNames:
        msg=("Invalid particle type '{0}'. "
             "Allowed types are {1}").format(
            PartName, str(ValidPartNames))
        raise TypeError(msg)

def CheckPartType(PartName):
    ValidPartNames=GetPartTypes()
    if PartName not in ValidPartNames:
        msg=("Invalid particle type '{0}'. "
             "Allowed types are {1}").format(
            PartName, str(ValidPartNames))
        raise TypeError(msg)

def CheckPklType(PartName):
    ValidPartNames=GetPklTypes()
    if PartName not in ValidPartNames:
        msg=("Invalid particle type for the samples/code version you are using."
             "Allowed types are {0}. If you wish to use other please check twiki page for instructions").format(str(ValidPartNames))
        raise TypeError(msg)

def CheckMagPol(MagPol):
    ValidMagPols=("MagUp", "MagDown")
    if MagPol not in ValidMagPols:
        msg=("Invalid magnet polarity '{0}'. "
        "Allowed polarities are {1}").format(MagPol, str(ValidMagPols))
        raise TypeError(msg)

def CheckStripVer(StripVer):
    ValidStripVers=("13b", "15", "17", "20", "20r1", "20_MCTuneV2",
         "20r1_MCTuneV2")
    if StripVer not in ValidStripVers:
        msg=("Invalid stripping version '{0}'. "
             "Allowed versions are {1}").format(StripVer, str(ValidStripVers))
        raise TypeError(msg)

def CheckBinVarName(VarName):
    ValidBinVarNames=GetBinVarNames()
    if VarName not in ValidBinVarNames:
        msg=("Invalid binning variable '{0}'. "
             "Allowed variables are {1}").format(VarName, str(ValidBinVarNames))
        raise TypeError(msg)
            
def GetRecoVer(StripVer):
    CheckStripVer(StripVer)
    if StripVer=='13b':
        return 10
    elif StripVer=='15':
        return 11
    elif StripVer=='17':
        return 12
    else:
        return 14

def GetFileSuffix(PartName):
    CheckPartType(PartName)
    if PartName in ("K", "Pi", "P"):
        return "h"
    if PartName in ("Mu",  "P_MuonUnBiased"):
        return "mu_and_p_muonUnBiased"
    else:
        return "h_muonUnBiased"

def GetPklFileSuffix(PartName):
    CheckPklType(PartName)
    if PartName in ("K", "Pi",):
        return "dst_k_and_pi"
    if PartName in ("P"):
        return "lam0_p"
            
def GetRunDictionary(StripVer, PartName="K"):#, IsMuonUnBiased=False):

    fileSuffix=GetFileSuffix(PartName)
    pklfileSuffix=GetPklFileSuffix(PartName)
    #MUONPreFix = ''
    ##   if PartName in ("Mu", "K_MuonUnBiased", "Pi_MuonUnBiased", "P_MuonUnBiased"):
    ##         MUONPreFix = '/MUON'
    
 
    #======================================================================
    # Dictionary of Dictionaires for StripVersion -> {UpRuns, DownRuns}
    #======================================================================
    UpRunLims   = pickle.load( open( os.path.expandvars(
        '$CALIBDATASCRIPTSROOT/jobs/Stripping{strp}/ChopTrees/up_runLimits_{suf}.pkl'.format(
        strp=StripVer, suf=pklfileSuffix)), 'rb' ) )
    DownRunLims = pickle.load( open( os.path.expandvars(
        '$CALIBDATASCRIPTSROOT/jobs/Stripping{strp}/ChopTrees/down_runLimits_{suf}.pkl'.format(
        strp=StripVer, suf=pklfileSuffix)), 'rb' ) )    

    StripDict = {'StripVer'   : StripVer,
                 'RecoVer'    : GetRecoVer(StripVer),
                 'UpRuns'     : UpRunLims.astype(int),  
                 'DownRuns'   : DownRunLims.astype(int)        
                 }

    print 'StripVer   : ', StripDict['StripVer']
    print 'RecoVer    : ', StripDict['RecoVer']
    print 'UpRuns     : ', StripDict['UpRuns']
    print 'DownRuns   : ', StripDict['DownRuns']
    
    return StripDict

def __FindFileIndex(run, runFirst, runLast):
    #======================================================================
    # Is run within the limits of a file?
    # - Create arrays of booleans determining if run is:
    #    a) Equal-to-or-greater-than the first run in each
    #       file (IsrunGreaterThanFirst)
    #    b) Equal-to-or-less-than the last run in each
    #       file (IsrunLessThanLast)
    # - Take the logical and and search for a 'True'.
    # - If there is no 'True', then find the first 'True' in
    #   IsrunLessThanLast.
    # - If there is no 'True' in IsrunLessThanLast, then find the
    #   first 'True' in IsrunGreaterThanFirst.
    #   and take this index as the first file to process.
    # - If no match is made, a 'ValueError: min() arg is an empty sequence'
    #   is returned.
    #======================================================================
    IsrunGreaterThanFirst = runFirst<=run
    IsrunLessThanLast     = runLast>=run
    IsrunInHere           = np.logical_and(IsrunGreaterThanFirst,IsrunLessThanLast)

    if np.any(IsrunInHere):
        FileIndex = np.min(np.nonzero(IsrunInHere==True)[0])
    elif np.any(IsrunLessThanLast):
        FileIndex = np.min(np.nonzero(IsrunLessThanLast == True)[0])
    else:
        FileIndex = np.max(np.nonzero(IsrunGreaterThanFirst == True)[0])
    
    return FileIndex



def GetMinMaxFileDictionary(DataDict, MagPolarity, runMin=None, runMax=None):
    #======================================================================
    # Determine file index ranges corresponding to RunMin and RunMax
    #======================================================================
    CheckMagPol(MagPolarity)
    runFirst = 0
    runLast  = 0
    if MagPolarity=='MagUp':
        ndim = DataDict['UpRuns'].shape[0]
        runFirst = DataDict['UpRuns'][0:ndim,0]
        runLast  = DataDict['UpRuns'][0:ndim,1]
    else:
        ndim = DataDict['DownRuns'].shape[0]
        runFirst = DataDict['DownRuns'][0:ndim,0]
        runLast  = DataDict['DownRuns'][0:ndim,1]

    if runMin is None:
        #print 'runMin is None', runMin
        minIndex = 0
    else:
        #print 'runMin is not None', runMin
        minIndex = __FindFileIndex(int(runMin), runFirst, runLast)
    if runMax is None:
        #print 'runMax is None', runMax
        maxIndex = len(runFirst)-1
    else:
        #print 'runMax is not None', runMax
        maxIndex = __FindFileIndex(int(runMax), runFirst, runLast)

    print 'RunMin: {run}, Min file index: {index}'.format(run=runMin, index=minIndex)
    print 'RunMax: {run}, Max file index: {index}'.format(run=runMax, index=maxIndex)

    ret = {'minIndex' : minIndex,
           'maxIndex' : maxIndex}

    return ret
