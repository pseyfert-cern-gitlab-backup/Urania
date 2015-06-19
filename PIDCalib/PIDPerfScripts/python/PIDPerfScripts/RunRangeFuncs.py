import pickle
import os
import numpy as np
from pprint import pprint
import sys

def GetRunDictionary(StripVer, PartName="K", IsMuonUnBiased=False):

    if PartName not in ("K", "Pi", "P", "Mu"):
        print "**** ERROR: Invalid particle name: %s" %PartName
        sys.exit(1)
        a
    fileSuffix=""
    if not IsMuonUnBiased:
        fileSuffix="h"
    else:
        if PartName=="Mu":
            fileSuffix="mu_and_p_muonUnBiased"
        elif PartName=="P":
            fileSuffix="mu_and_p_muonUnBiased"
        else:
            fileSuffix="h_muonUnBiased"
            
    MUONPreFix = ''
    if IsMuonUnBiased or PartName=="Mu" : MUONPreFix = '/MUON'
    
    #======================================================================
    # Dictionary of Dictionaires for StripVersion -> {UpRuns, DownRuns}
    #======================================================================
    UpRunLims   = pickle.load( open( os.path.expandvars('$CALIBDATASCRIPTSROOT/jobs%s/Stripping%s/ChopTrees/up_runLimits_%s.pkl' %(MUONPreFix,
                                                          StripVer, fileSuffix)),
                                                        'rb' ) )
    DownRunLims = pickle.load( open( os.path.expandvars('$CALIBDATASCRIPTSROOT/jobs%s/Stripping%s/ChopTrees/down_runLimits_%s.pkl' %(MUONPreFix,
                                                         StripVer, fileSuffix)),
                                                        'rb' ) )
    
    Strip2Reco = {'13b'  : 10,
                  '15'   : 11,
                  '17'   : 12,
                  '20'   : 14,
                  '20r1' : 14
                  }

    StripDict = {'StripVer' : StripVer,
                 'RecoVer'  : Strip2Reco[StripVer],
                 'UpRuns'   : UpRunLims.astype(int),  
                 'DownRuns' : DownRunLims.astype(int)        
                 }

    print 'StripVer : ', StripDict['StripVer']
    print 'RecoVer  : ', StripDict['RecoVer']
    print 'UpRuns   : ', StripDict['UpRuns']
    print 'DownRuns : ', StripDict['DownRuns']
    
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
    runFirst = 0
    runLast  = 0
    if MagPolarity=='MagUp':
        ndim = DataDict['UpRuns'].shape[0]
        runFirst = DataDict['UpRuns'][0:ndim,0]
        runLast  = DataDict['UpRuns'][0:ndim,1]
    if MagPolarity=='MagDown':
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
