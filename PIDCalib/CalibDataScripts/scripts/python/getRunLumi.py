from diracFuncs import *
import numpy as np        
import pickle

def usage():
    print 'Following:'
    print '> SetupLHCbDirac'
    print '> lhcb-proxy-init'
    print 'Usage: %s <Config Version> <Processing Pass> <lumi range - MAG DOWN (pb^-1)> <lumi range - MAG UP (pb^-1)> <fileSuffix>' %(Script.scriptName)
    print '> python -u getRunLumi.py Collision12 /Reco14/Stripping20 30 30 h'

gLogger.setLevel("INFO")

#======================================================================
# Get command line arguments
# If less than 3 arguments passed, call usage()
#======================================================================
Script.parseCommandLine()
args = Script.getPositionalArgs()
if len(args) < 3: 
    usage()
    DIRAC.exit(2)

configVersion  = args[0]
processingPass = args[1]
lumiBlock_down = float(args[2])
lumiBlock_up   = float(args[3])
fileSuffix     = args[4]
dqFlag         = 'OK'

msg="Config version: %s" %configVersion
print msg
gLogger.info(msg)
msg="Processing pass: %s" %processingPass
print msg
gLogger.info(msg)
msg="Luminosity block (magnet down): %.2f pb-1" %lumiBlock_down
print msg 
gLogger.info(msg)
msg="Luminosity block (magnet up): %.2f pb-1" %lumiBlock_up
print msg 
gLogger.info(msg)
msg="File suffix: %s" %fileSuffix
print msg
gLogger.info(msg)
 
bkDict = {'ConfigName'    : 'LHCb',
          'ConfigVersion' : configVersion,
          'ProcPass'      : processingPass}

res = bkClient.getFileTypes(bkDict);
if not res['OK']:
    print 'ERROR %s' % (res['Message'])
    gLogger.error(res['Message'])
    DIRAC.exit(2)

ftList   = res['Value']['Records']
allTypes = []
for thisTypeArray in ftList:
    thisType = thisTypeArray[0]
    if re.search("\.DST$", thisType):
        allTypes.append(thisType)
    elif re.search("\.MDST$", thisType):
        allTypes.append(thisType)

for fileType in allTypes:
    m = re.search('(\w+)\.DST', fileType)
    if not m:
        m = re.search('(\w+)\.MDST', fileType)
        if not m:
            gLogger.error('Cannot extract file type')
            DIRAC.exit(2)

    #======================================================================
    # Only consider the PID stripping stream
    #======================================================================
    fileTypeName = m.group(1)
    if fileTypeName != 'PID':
        continue

    gLogger.info('Now loading stream %s' %(fileTypeName))

    #======================================================================
    # Obtain a list of LFNs in a given stream
    #======================================================================
    allLFN = GetAllLFN(configVersion, processingPass, fileType, dqFlag)
    if not len(allLFN) > 0:
        continue
    
    #======================================================================
    # Returns a dictionary of dictionaries:
    # magpol : runNumber = lumi
    #======================================================================
    runHash  = GetRunList(allLFN)

    #======================================================================
    # Create separate lists of all Up and Down runs 
    #======================================================================   
    upRuns   = runHash['Up'].keys()
    downRuns = runHash['Down'].keys()

    upRuns.sort()
    downRuns.sort()
    
    #======================================================================
    # Create ordered list of runs
    #======================================================================   
    upRunNumbers   = []
    downRunNumbers = []
    for i in upRuns:
        upRunNumbers.append(int(i))
    for i in downRuns:
        downRunNumbers.append(int(i))
    upRunNumbers.sort()
    downRunNumbers.sort()
    
    #======================================================================
    # Loop over field up runs and append min and max run limits (defined by
    # the user specified integrated lumi) to the list runLimits. Once
    # filled, pass this into a numpy array and modify its shape.
    #======================================================================   
    runLimits = [upRunNumbers[0]]
    sumLumi = 0
    for i, runId in enumerate(upRunNumbers):

        sumLumi += float(runHash['Up'][str(runId)])
        #print 'Up', runId, runHash['Up'][str(runId)], sumLumi

        if sumLumi > (lumiBlock_up * 1000000 ):
            # Append last run number to list
            runLimits.append(upRunNumbers[i-1])
            # Append this run number to list
            runLimits.append(runId)
            # Reset sumLumi to this runs lumi value
            print sumLumi - float(runHash['Up'][str(runId)])
            sumLumi = float(runHash['Up'][str(runId)])
            
    if len(runLimits)%2 != 0:
        runLimits.append(upRunNumbers[len(upRunNumbers)-1])
        
    upRunLimits = np.asarray(runLimits)
    upRunLimits.shape = -1,2
    print 'Up Run Limits'
    print upRunLimits
            
    #======================================================================
    # Again, but now for field down
    #======================================================================
    runLimits = [downRunNumbers[0]]
    sumLumi = 0
    for i, runId in enumerate(downRunNumbers):

        sumLumi += float(runHash['Down'][str(runId)])
        #print 'Down', runId, runHash['Down'][str(runId)], sumLumi

        if sumLumi > (lumiBlock_down * 1000000):
            # Append last run number to list
            runLimits.append(downRunNumbers[i-1])
            # Append this run number to list
            runLimits.append(runId)
            # Reset sumLumi to this runs lumi value
            print sumLumi - float(runHash['Down'][str(runId)])
            sumLumi = float(runHash['Down'][str(runId)])
            
    if len(runLimits)%2 != 0:
        runLimits.append(downRunNumbers[len(downRunNumbers)-1])

    downRunLimits = np.asarray(runLimits)
    downRunLimits.shape = -1,2
    print 'Down Run Limits'
    print downRunLimits

    #======================================================================
    # Pickle the numpy arrays
    #======================================================================
    upFile = open('up_runLimits_%s.pkl' %fileSuffix, 'wb')
    pickle.dump(upRunLimits, upFile)
    upFile.close()

    downFile = open('down_runLimits_%s.pkl' %fileSuffix, 'wb')
    pickle.dump(downRunLimits, downFile)
    downFile.close()
