from diracFuncs import *

#======================================================================
# Script to determine the lumiosity for a given set of run intervals
# associated with a specific TCK
#======================================================================

def usage():
    print 'Usage: %s <Config Version> <Processing Pass>' %(Script.scriptName)
    print 'python -u getTCKLumi.py Collision11 /Reco12/Stripping17'

gLogger.setLevel("INFO")

#======================================================================
# Define dictionary of dictionaries. For each trigger set declare the:
# a) TCK
# b) Run range
# c) integrated lumi (zero initially)
#======================================================================
Set2Runs = { 'A' : {'TCK'  : '0x5D0033',
                    'Runs' : [[89333, 89350]],
                    'lumi' : 0
                    },
             'D' : {'TCK'  : '0x6D0032', 
                    'Runs' : [[91631, 91658], [91733, 92316]],
                    'lumi' : 0
                     },
             'E' : {'TCK'  : '0x700034',
                    'Runs' : [[91729, 91732]],
                    'lumi' : 0
                     },
             'F' : {'TCK'  : '0x6D0032', 
                    'Runs' : [[92317, 92735], [92826, 92905]],
                    'lumi' : 0
                     },
             'G' : {'TCK'  : '0x710035', 
                    'Runs' : [[92821, 92825]],
                    'lumi' : 0
                     },
             'H' : {'TCK'  : '0x730035', 
                    'Runs' : [[92906, 93700], [93721, 94012]],
                    'lumi' : 0
                     },
             'I' : {'TCK'  : '0x740036', 
                    'Runs' : [[93701, 93720]],
                    'lumi' : 0
                     },
             'J' : {'TCK'  : '0x710035', 
                    'Runs' : [[94169, 94386]],
                    'lumi' : 0
                     },
             'K' : {'TCK'  : '0x760037', 
                    'Runs' : [[95929, 101011]],
                    'lumi' : 0
                     },
             'L' : {'TCK'  : '0x790037', 
                    'Runs' : [[101012, 101067]],
                    'lumi' : 0
                     },
             'M' : {'TCK'  : '0x790037', 
                    'Runs' : [[101092, 101121]],
                    'lumi' : 0
                     },
             'N' : {'TCK'  : '0x790037', 
                    'Runs' : [[101122, 101678], [101683, 101761]],
                    'lumi' : 0
                    },
             'O' : {'TCK'  : '0x790038', 
                    'Runs' : [[101680, 101682], [101762, 104486]],
                    'lumi' : 0
                    }
             }
print Set2Runs

#======================================================================
# Get command line arguments
# If less than 2 arguments passed, call usage()
#======================================================================
Script.parseCommandLine()
args = Script.getPositionalArgs()
if len(args) < 2: 
    usage()
    DIRAC.exit(2)

configVersion  = args[0]
processingPass = args[1]
dqFlag         = 'OK'

bkDict = {'ConfigName'    : 'LHCb',
          'ConfigVersion' : configVersion,
          'ProcPass'      : processingPass}

res = bkClient.getFileTypes(bkDict);
if not res['OK']:
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
    # Merge Up and Down run lists
    #======================================================================   
    upRuns   = runHash['Up']
    downRuns = runHash['Down']
    bothRuns = upRuns.copy()
    bothRuns.update(downRuns)
    print bothRuns
    
    #======================================================================
    # For given list of run ranges, determine the integrated luminosity 
    #======================================================================   
    for Set, dict in Set2Runs.items():
        for i in dict['Runs']:
            print i, i[0], i[1]
            for run in range(i[0], i[1]):
                if bothRuns.has_key(str(run)):
                    lumi = float(bothRuns[str(run)])
                    print 'Lumi', lumi
                    dict['lumi'] += lumi
print Set2Runs
