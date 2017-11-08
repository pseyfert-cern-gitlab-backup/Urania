################################################################################
## Module to automate data retrieval, so that scripts can run natively on both
## lxplus and the LNF cluster. Contains some dictionaries to hold data values
## and functions to automatically retrieve them.
################################################################################
import os, sys, errno
from ROOT import TFile, TTree, TChain
import BsDsMuNuForRDS.Configuration as Configuration

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
    'lxplus' : '/eos/lhcb/user/r/rvazquez/RDS/WithVetoes/'
    ,'lnf'   : ''
    }

# Directory for the Dalitz variables processed from Ricci's
# master files.
dalitzDirDict = {
    'lxplus' : '/afs/cern.ch/work/r/rvazquez/RDS/'
    ,'lnf'   : ''
    }

# Temporary post Ds veto locations, for local processing
# and immediately before being copied to the final dir
# on eos.
temporaryDirDict = {
    'lxplus' : '/afs/cern.ch/work/r/rvazquez/RDS/WithDsVetoes/'
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

    'MC_Signal'   : { 'tNames'       : [ 'B2DsMuNuTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_Sim09b_DsMuNu_Up.root' ]
                       ,'MagDown'    : [ 'TupleRDS_Sim09b_DsMuNu_Down.root' ]
                       ,'MagUpOut'   : 'TupleRDS_Sim09b_DsMuNu_Up.root'
                       ,'MagDownOut' : 'TupleRDS_Sim09b_DsMuNu_Down.root'
                       }

    ,'MC_Tau'      : { 'tNames'      : [ 'B2DsMuNuTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_Sim09b_DsTauNu_Up.root' ]
                       ,'MagDown'    : [ 'TupleRDS_Sim09b_DsTauNu_Down.root']
                       ,'MagUpOut'   : 'TupleRDS_Sim09b_DsTauNu_Up.root'
                       ,'MagDownOut' : 'TupleRDS_Sim09b_DsTauNu_Down.root'
                     }

    ,'MC_InclDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_InclDsUp_allNeutrals_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_InclDsDown_allNeutrals_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_InclDsUp_allNeutrals_iso.root' 
                       ,'MagDownOut' :  'TupleRDS_InclDsDown_allNeutrals_iso.root'
                       }

    ,'MC_LbLcDs'   : { 'tNames'      : [ 'B2DsMuNuTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_Sim09b_LbLcDs_Up.root' ]
                       ,'MagDown'    : [ 'TupleRDS_Sim09b_LbLcDs_Down.root' ]
                       ,'MagUpOut'   :  'TupleRDS_Sim09b_LbLcDs_Up.root'
                       ,'MagDownOut' :  'TupleRDS_Sim09b_LbLcDs_Down.root'
                       }

    ,'MC_BdDstDs'  : { 'tNames'      : [ 'B2DsMuNuTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_Sim09b_BdDstDs_Up.root' ]
                       ,'MagDown'    : [ 'TupleRDS_Sim09b_BdDstDs_Down.root' ]
                       ,'MagUpOut'   :  'TupleRDS_Sim09b_BdDstDs_Up.root'
                       ,'MagDownOut' :  'TupleRDS_Sim09b_BdDstDs_Down.root'
                       }

    ,'MC_BsDsDs'   : { 'tNames'      : [ 'B2DsMuNuTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_Sim09b_BsDsDs_Up.root' ]
                       ,'MagDown'    : [ 'TupleRDS_Sim09b_BsDsDs_Down.root' ]
                       ,'MagUpOut'   :  'TupleRDS_Sim09b_BsDsDs_Up.root'
                       ,'MagDownOut' :  'TupleRDS_Sim09b_BsDsDs_Down.root'
                       }

    ,'MC_BuD0Ds'   : { 'tNames'      : [ 'B2DsMuNuTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_Sim09b_BuD0Ds_Up.root' ]
                       ,'MagDown'    : [ 'TupleRDS_Sim09b_BuD0Ds_Down.root' ]
                       ,'MagUpOut'   :  'TupleRDS_Sim09b_BuD0Ds_Up.root'
                       ,'MagDownOut' :  'TupleRDS_Sim09b_BuD0Ds_Down.root'
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

# The EOS protocol to use.
EOSProtocol = 'root://eoslhcb.cern.ch//'

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


def checkTempDirExists(path='/tmp/RDs/'):
    '''
    Function to check the requested path, the temp afs dir by default,
    exists. If it does we ignore this and carry on with the execution.
    '''
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise

######################################################
# Getting directories.
######################################################
def getEOSPreSelectionDirectory(dataTag='MC09_Mu'):
    '''
    Returns the directory on EOS containing the ntuples
    before any selection is applied.
    Assumes the default shared repository, but this
    can be overwritten by the entry "inputDir" in
    the configurationDict.
    '''
    if 'inputDir' in Configuration.configurationDict[dataTag].keys():
        return Configuration.configurationDict[dataTag]['inputDir']
    else:
        return preSelectionDirectoryEOS

def getEOSDalitzDirectory():
    '''
    Returns the directory on EOS where the Dalitz tuples
    are stored.
    '''
    return dalitzDirectoryEOS
    
def getEOSPostSelectionDirectory():
    '''
    Returns the directory on EOS containing the data
    after full selection, with the extra info added.
    '''
    return postSelectionDirectoryEOS

def getLocalDalitzDirectory():
    '''
    Returns the directory on the local filesystem where
    the Dalitz tuples are created and stored.
    Checks the tmp dir exists and if not makes it on the fly.
    '''
    checkTempDirExists()
    hostKey = getHostKey()
    return localDalitzDirectoryDict[hostKey]

def getLocalPostSelectionDirectory():
    '''
    Returns the directory on the local filesystem where
    the postSelection ntuples are temporarily stored.
    Checks the tmp dir exists and if not makes it on the fly.
    '''
    checkTempDirExists()
    hostKey = getHostKey()
    return localPostSelectionDirectoryDict[hostKey]

######################################################
# Building filenames automatically.
######################################################
def getOutputFileName(dataTag, verbose=True):
    '''
    Function to get the output name for the filtered
    ntuples. ONLY GETS THE END FILE NAME! Not the dir!
    Needs combined with other functions to return the full name.
    '''
    outName = Configuration.configurationDict[dataTag]['outputFile']
    if verbose:
        print '-- DataRetrieval.getOutputFileName: function returns:'
        print '--', outName
    return outName

def getDalitzFileName(dataTag, verbose=True):
    '''
    Get the  Dalitz filename.
    Again, just the filename itself and not the path.
    '''
    dalitzName = 'DalitzTuple_%s.root' %dataTag
    if verbose:
        print '-- DataRetrieval.getDalitzFileName: function returns:'
        print '--', dalitzName
    return dalitzName

def getLocalDalitzFileName(dataTag, verbose=True):
    '''
    Get the full local filesystem filename for the
    Dalitz ntuple.
    '''
    baseName = getLocalDalitzDirectory()
    endName  = getDalitzFileName(dataTag, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose:
        print '-- DataRetrieval.getLocalDalitzFileName: function returns:'
        print '--', fullName
    return fullName

def getLocalPostSelectionFileName(dataTag, verbose=True):
    '''
    Get the full local filesystem filename for the
    postselection ntuple.
    '''
    baseName = getLocalPostSelectionDirectory()
    endName  = getOutputFileName(dataTag, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose:
        print '-- DataRetrieval.getLocalPostSelectionFileName: function returns:'
        print '--', fullName
    return fullName

def getEOSDalitzFileName(dataTag, verbose=True):
    '''
    Get the full EOS filename for the
    Dalitz ntuple.
    This does not include the EOS protocol.
    '''
    baseName = getEOSDalitzDirectory()
    endName  = getDalitzFileName(dataTag, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose:
        print '-- DataRetrieval.getEOSDalitzFileName: function returns:'
        print '--', fullName
    return fullName

def getEOSPostSelectionFileName(dataTag, verbose=True):
    '''
    Get the full EOS filename for the
    postselection ntuple.
    This does not include the EOS protocol.
    '''
    baseName = getEOSPostSelectionDirectory()
    endName  = getOutputFileName(dataTag, verbose)
    fullName = '%s%s' %(baseName, endName)
    if verbose:
        print '-- DataRetrieval.getEOSPostSelectionFileName: function returns:'
        print '--', fullName
    return fullName

######################################################
# Now the functions to return TChain objects.
######################################################
def getListOfFiles(dataTag, verbose=True):
    '''
    Get the full list of file names to add to the TChain.
    These will be formatted with the protocol and the correct
    full pathname.
    '''
    # First get the list of file names within the home directory.
    inList = Configuration.configurationDict[dataTag]['inputFiles']
    
    # Now get the data directory and the protocol.
    dataDir = getEOSPreSelectionDirectory(dataTag)
    
    # Now populate a list of full names to be passed to the ROOT classes.
    outList = []
    if verbose: print '-- DataRetrieval.getListOfFiles adding file to list:'
    for endName in inList:
        toAdd = '%s%s%s' %(EOSProtocol, dataDir, endName)
        if verbose: print '---- ' + toAdd
        outList.append(toAdd)
    return outList

def getChainWithTupleName(dataTag, tupleName="B2DsMuNuTuple/DecayTree", verbose=True):
    '''
    Get a TChain for the relevant datatype.
    '''
    # First get the tuple name and make the chain.
    tName = tupleName
    if verbose:
        print '-- DataRetrieval.getChainWithTupleName making chain with name:'
        print '----', tName
    c = TChain(tName)
    
    # Now get the list of files and add them.
    fList = getListOfFiles(dataTag, verbose)
    for fName in fList:
        c.Add(fName)
    if verbose: print '-- DataRetrieval.getChainWithTupleName retrieved TChain with %i entries.\n' %c.GetEntries()    
    return c

def getEOSDalitzFile(dataTag, verbose=True):
    '''
    Get the EOS Dalitz File from EOS, formatted with the remote root
    eos protocol.
    '''
    fName = getEOSDalitzFileName(dataTag, verbose=True)
    return EOSProtocol + fName
    
def getProcessedChain(dataTag, tName="B2DsMuNuTuple/DecayTree", verbose=True):
    '''
    Get the fully processed ntuples from my mass storage.
    Takes the following required positional command line arguments:
        dataTag  - what kind of data do you want?
    And takes the following optional arguments:
        tName - the specified tuple within the file to get. This defaults
              - to "B2DsMuNuTuple/DecayTree". 
              - The truth matched tuples can be found in MC with "MB2DsMuNuTuple/DecayTree".
              - The various SS and fake lines are:
                  - B2DsMuNuTupleFake/DecayTree
                  - B2DsMuNuSSTuple/DecayTree
                  - B2DsMuNuSSTupleFake/DecayTree
    '''
    # Get the name without protocol then add it.
    nameNoProtocol = getEOSPostSelectionFileName(dataTag, verbose=True)
    # If the default tuple isn't in the configurationDict for that key,
    # use the fake muon as default instead.
    if 'B2DsMuNuTuple/DecayTree' not in Configuration.configurationDict[dataTag]['tNames']:
        tName = 'B2DsMuNuTupleFake/DecayTree'
    if verbose: print tName
    if tName not in Configuration.configurationDict[dataTag]['tNames']:
        sys.exit('DataRetrieval.getProcessedChain ERROR: tuple name not recognised.')

    c = TChain(tName)
    fName = '%s%s' %(EOSProtocol, nameNoProtocol)
    if verbose:
        print '-- DataRetrieval.getProcessedChain: Adding file to chain:'
        print '---- %s' %fName
    c.Add(fName)
    if verbose: print '-- Retrieved TChain with %i entries.\n' %c.GetEntries()
    return c

if __name__ == '__main__':
    pass
