################################################################################
## Module to automate data retrieval, so that scripts can run natively on both
## lxplus and the LNF cluster. Contains some dictionaries to hold data values
## and functions to automatically retrieve them.
################################################################################
import os, sys
from ROOT import TFile, TTree, TChain

################################################################################
## DATA
################################################################################
# Master file directory locations.
masterDirDict = {
    'lxplus' : '/eos/lhcb/user/r/rvazquez/RDS/'
    ,'lnf'   : '/data/Shared/TupleProd_Dec15/'
    }

# Home directory for the processed ntuples on eos.
finalDirDict = {
    'lxplus' : '/eos/lhcb/user/s/sogilvy/RDs/WithVetoes/'
    ,'lnf'   : ''
    }

# Directory for the Dalitz variables processed from Ricci's
# master files.
dalitzDirDict = {
    'lxplus' : '/afs/cern.ch/work/s/sogilvy/RDs/'
    ,'lnf'   : ''
    }

# Temporary post Ds veto locations, for local processing
# and immediately before being copied to the final dir
# on eos.
temporaryDirDict = {
    'lxplus' : '/afs/cern.ch/work/s/sogilvy/RDs/WithVetoes/'
    ,'lnf'   : ''
    }

# Data protocol. Use eos for lxplus.
protocolDict = {
    'lxplus' : 'root://eoslhcb.cern.ch//'
    ,'lnf'   : ''
    }

# A dict containing lists of all files to be added for each type of data and polarity.
# Also contains the tuple names for each file type to be cycled over.
dataDict = {

    'MC_Signal'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_MCSignalUp_allNeutrals_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_MCSignalDown_allNeutrals_iso.root']
                       ,'MagUpOut'   : 'TupleRDS_MCSignalUp_allNeutrals_iso.root'
                       ,'MagDownOut' : 'TupleRDS_MCSignalDown_allNeutrals_iso.root'
                       }
    
    ,'MC_InclDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_InclDsUp_allNeutrals_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_InclDsDown_allNeutrals_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_InclDsUp_allNeutrals_iso.root' 
                       ,'MagDownOut' :  'TupleRDS_InclDsDown_allNeutrals_iso.root'
                       }

    ,'MC_LbLcDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_LbLcDs_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_LbLcDs_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_LbLcDs_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_LbLcDs_Down_iso.root'
                       }

    ,'MC_BdDstDs'  : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_BdDstDs_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_BdDstDs_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_BdDstDs_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_BdDstDs_Down_iso.root'
                       }

    ,'MC_BsDsDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_BsDsDs_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_BsDsDs_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_BsDsDs_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_BsDsDs_Down_iso.root'
                       }

    ,'MC_BuD0Ds'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_BuD0Ds_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_BuD0Ds_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_BuD0Ds_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_BuD0Ds_Down_iso.root'
                       }
    
    ,'Data'        : { 'tNames'      : ['B2DsMuNuTuple/DecayTree'
                                        ,'B2DsMuNuTupleFake/DecayTree'
                                        ,'B2DsMuNuSSTuple/DecayTree'
                                        ,'B2DsMuNuSSTupleFake/DecayTree']
                       ,'MagUp'      : ['TupleRDS_DataUp_1_allNeutrals_iso.root'
                                        ,'TupleRDS_DataUp_2_allNeutrals_iso.root']
                       ,'MagDown'    : ['TupleRDS_DataDown_1_allNeutrals_iso.root'
                                        ,'TupleRDS_DataDown_2_allNeutrals_iso.root']
                       ,'MagUpOut'   : 'TupleRDS_DataUp_allNeutrals_iso.root'
                       ,'MagDownOut' : 'TupleRDS_DataDown_allNeutrals_iso.root'
                       }
    
    }


################################################################################
## FUNCS - these act on the data objects to retrieve and make files.
################################################################################
# First functions to return info about the current system and protocol to use.
def getHostKey():
    '''
    Function to determine the host name, and use it to
    find the host key for the dictionaries.
    '''
    hostName = os.environ['HOSTNAME']
    if 'lxplus' in hostName:
        return 'lxplus'
    elif 'lhcb' in hostName:
        return 'lnf'
    else:
        sys.exit('DataRetrieval ERROR: host name not recognised.')

def getProtocol():
    '''
    Returns the appropriate protocol to open the TFile.
    '''
    hostKey = getHostKey()
    return protocolDict[hostKey]

######################################################
# Getting directories.
######################################################
def getMasterDirectory():
    '''
    Returns the appropriate directory containing the data
    from the master directory (Ricci ntuples from DaVinci).
    '''
    hostKey = getHostKey()
    return masterDirDict[hostKey]

def getDalitzDirectory():
    '''
    Returns the directory where the Dalitz tuples
    are stored.
    '''
    hostKey = getHostKey()
    return dalitzDirDict[hostKey]
    
def getFinalDirectory():
    '''
    Returns the appropriate directory containing the data
    after full selection and after all branches are added.
    '''
    hostKey = getHostKey()
    return finalDirDict[hostKey]

def getTemporaryDirectory():
    '''
    Returns the appropriate directory containing the data
    after full selection on my local space, which should
    immediately be copied to eos and then deleted.
    '''
    hostKey = getHostKey()
    return temporaryDirDict[hostKey]

######################################################
# Building filenames automatically.
######################################################
def getOutputFileName(dataTag, polarity, verbose=True):
    '''
    Function to get the output name for the filtered
    ntuples. ONLY GETS THE END FILE NAME! Not the dir!
    Needs combined with other functions to return the full name.
    '''
    outName = dataDict[dataTag]['%s%s' %(polarity, 'Out')]
    if verbose:
        print '-- DataRetrieval.getOutputFileName: function returns:'
        print '--', outName
    return outName

def getDalitzFileName(dataTag, polarity, verbose=True):
    '''
    Get the full Dalitz filename.
    '''
    baseName = getDalitzDirectory()
    endName  = getOutputFileName(dataTag, polarity, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose: print '-- dalitzName says:', fullName
    return fullName

def getTemporaryFileName(dataTag, polarity, verbose=True):
    '''
    Get the full temporary filename.
    '''
    baseName = getTemporaryDirectory()
    endName  = getOutputFileName(dataTag, polarity, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose: print '-- tempName says:', fullName
    return fullName

def getFinalFileName(dataTag, polarity, verbose=True):
    '''
    Get the full master filename.
    '''
    baseName = getFinalDirectory()
    endName  = getOutputFileName(dataTag, polarity, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose: print '-- finalName says:', fullName
    return fullName

######################################################
# Now the functions to return TChain objects.
######################################################
def getListOfFiles(dataTag, polarity, verbose=False):
    '''
    Get the full list of file names to add to the TChain.
    These will be formatted with the protocol and the correct
    full pathname.
    '''
    # First get the list of file names within the home directory.
    inList = dataDict[dataTag][polarity]
    
    # Now get the data directory and the protocol.
    dataDir = getMasterDirectory()
    protocol = getProtocol()
    
    # Now populate a list of full names to be passed to the ROOT classes.
    outList = []
    for endName in inList:
        toAdd = '%s%s%s' %(protocol, dataDir, endName)
        if verbose: print '-- DataRetrieval: Adding file to list:'+'\n--- ' + toAdd
        outList.append(toAdd)
    return outList

def getChainWithTupleName(dataTag, polarity, tupleName="B2DsMuNuTuple/DecayTree", verbose=True):
    '''
    Get a chain for the relevant datatype.
    '''
    # First get the tuple name and make the chain.
    tName = tupleName
    if verbose:
        #print '*'*50
        print '-- DataRetrieval: making chain with name:', tName
    c = TChain(tName)
    
    # Now get the list of files and add them.
    fList = getListOfFiles(dataTag, polarity, verbose)
    for fName in fList:
        c.Add(fName)
    if verbose: print '-- DataRetrieval: Retrieved TChain with %i entries.\n' %c.GetEntries()    
    return c

def getProcessedChain(dataTag, polarity, tName="B2DsMuNuTuple/DecayTree", verbose=True):
    '''
    Get the fully processed ntuples from my mass storage.
    Takes the following required positional command line arguments:
        dataTag  - what kind of data do you want?
                 - valid keys: "data", "MC_Signal", "MC_InclDs",
                               "MC_LbLcDs", MC_BdDstDs", MC_BsDsDs", MC_BuD0Ds"
                 - where data is real data.
        polarity - one of either MagUp or MagDown.
    And takes the following optional arguments:
        tName - the specified tuple within the file to get. This defaults
              - to "B2DsMuNuTuple/DecayTree". 
              - The truth matched tuples can be found in MC with "MB2DsMuNuTuple/DecayTree".
              - The various SS and fake lines are:
                  - B2DsMuNuTupleFake/DecayTree
                  - B2DsMuNuSSTuple/DecayTree
                  - B2DsMuNuSSTupleFake/DecayTree
        verbose - taken as a fourth argument can be true or false. Defaults to true to actually
                - show you what you are getting.
    '''
    theDir = finalDirDict[getHostKey()]
    if verbose: print tName
    if tName not in dataDict[dataTag]['tNames']:
        sys.exit('DataRetrieval ERROR: tuple name not recognised.')

    c = TChain(tName)
    fName ='%s%s%s' %(getProtocol(),
                      finalDirDict[getHostKey()],
                      getOutputFileName(dataTag, polarity))
    if verbose:
        print '-- DataRetrieval: Adding file to chain:'
        print '--- %s' %fName
    c.Add(fName)
    if verbose: print 'Retrieved TChain with %i entries.\n' %c.GetEntries()
    return c

if __name__ == '__main__':
    getListOfFiles('Data', 'MagDown')
    getChainWithTupleName('Data', 'MagDown')
    getTemporaryFileName('Data', 'MagDown')
    getFinalFileName('MC_Signal', 'MagDown')
