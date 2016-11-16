import DIRAC

from DIRAC                      import S_OK, S_ERROR, gLogger
from DIRAC.Core.Base            import Script
from DIRAC.Core.Utilities.List  import sortList
from LHCbDIRAC.BookkeepingSystem.Client.BookkeepingClient import BookkeepingClient

import os
import re
import time
from time import gmtime, strftime

import urllib, json
from copy import copy

bkClient = BookkeepingClient()

################################################################################
#                                                                              #
# GetAllLFN:                                                                   #
#                                                                              #
# Get the list of LFN in a given stream.                                       #
#                                                                              #
################################################################################
def GetAllLFN(configVersion, processingPass, fileType, dqFlag):
    bkDict = {'ConfigName'     : 'LHCb',
              'ConfigVersion'  : configVersion,
              'ProcessingPass' : processingPass,
              'FileType'       : fileType,
              'EventType'      : 90000000,
              'DataQualityFlag': dqFlag}
    res = bkClient.getVisibleFilesWithMetadata(bkDict)
    if not res['OK']:
        gLogger.error(res['Message'])
        DIRAC.exit(2)

    gLogger.info('Found LFN list.')
    allLFN = res['Value']['LFNs'].keys()
    return allLFN

################################################################################
#                                                                              #
# GetRunList:                                                                  #
#                                                                              #
# Get the list of all runs in the stream and match to them the LFN.            #
#                                                                              #
################################################################################
def GetRunList(allLFN):
    splitBy = 100
    nStep   = int(len(allLFN)/splitBy) + 1
    
    runHash = {'Up' : {},
               'Down' : {}}
    for i in range(0, nStep):
        first = i     * splitBy
        last  = (i+1) * splitBy
        
        rangeLFN = allLFN[first:last]

        res = bkClient.getFileMetadata(rangeLFN)
        #res = bkClient.getFileMetaDataForUsers(allLFN)
        if not res['OK']:
            gLogger.error(res['Message'])
            DIRAC.exit(2)
        gLogger.info('Found LFN metadata step %d.' %(i))

        lfnData = res['Value']['Successful']
     
        for lfn, metadata in lfnData.items():
            if not metadata.has_key('RunNumber'):
                msg="Metadata for LFN %s has no key named 'Run Number'" %lfn
                print "ERROR: %s" %msg
                gLogger.error(msg)
                DIRAC.exit(2)
            if not metadata.has_key('Luminosity'):
                msg="Metadata for LFN %s has no key named 'Luminosity'" %lfn
                print "ERROR: %s" %msg
                gLogger.error(msg)
                DIRAC.exit(2)
	    runNumber  = str(metadata['RunNumber'])
            luminosity = metadata['Luminosity']

            if runHash['Up'].has_key(runNumber):
                runHash['Up'][runNumber] += luminosity
            elif runHash['Down'].has_key(runNumber):
                runHash['Down'][runNumber] += luminosity
            else:
                res = bkClient.getRunInformations(int(runNumber))
                if not res['OK']:
                    gLogger.error(res['Message'])
                    DIRAC.exit(2)
                dtd = res['Value']['DataTakingDescription']
                if re.search('Excl', dtd):
                    continue
                elif re.search('Up', dtd):
                    runHash['Up'][runNumber] = luminosity
                elif re.search('Down', dtd):
                    runHash['Down'][runNumber] = luminosity
                else:
                    continue

    return runHash

