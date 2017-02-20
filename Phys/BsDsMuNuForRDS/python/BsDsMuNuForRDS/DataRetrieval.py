################################################################################
## Module to automate data retrieval, so that scripts can run natively on both
## lxplus and the LNF cluster. Contains some dictionaries to hold data values
## and functions to automatically retrieve them.
################################################################################
import os, sys
from ROOT import TFile, TTree, TChain
import BsDsMuNuForRDS.Configuration as Configuration

################################################################################
## DATA
################################################################################
# Some EOS locations first.
# This is the directory where the package will read the unprocessed trees.
preSelectionDirectoryEOS  = '/eos/lhcb/wg/semileptonic/Bs2DsX/UnprocessedTrees/'
# And the corresponding location where they'll be stored when processed.
postSelectionDirectoryEOS = '/eos/lhcb/wg/semileptonic/Bs2DsX/ProcessedTrees/'
# Directory for the trees containing the Dalitz variables.
dalitzDirectoryEOS        = '/eos/lhcb/wg/semileptonic/Bs2DsX/DalitzTrees/'

# Now some locations for where ROOT files are created.
# They must be local, so these depend on if we're running on lxplus
# or at the LNF cluster.
# First the temporary location for the Dalitz trees.
localDalitzDirectoryDict = {
    'lxplus' : '/afs/cern.ch/work/s/sogilvy/Bs2DsX/DalitzTrees/'
    ,'lnf'   : ''
    }
# Now the temporary location for the processed trees.
localPostSelectionDirectoryDict = {
    'lxplus' : '/afs/cern.ch/work/s/sogilvy/Bs2DsX/ProcessedTrees/'
    ,'lnf'   : ''
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
    '''
    hostKey = getHostKey()
    return localDalitzDirectoryDict[hostKey]

def getLocalPostSelectionDirectory():
    '''
    Returns the directory on the local filesystem where
    the postSelection ntuples are temporarily stored.
    '''
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
