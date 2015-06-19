import ROOT
from PIDPerfScripts.RunRangeFuncs import *

__all__=('CheckBinScheme', 'AddBinScheme',
         'SetDefaultBinScheme', 'AddUniformBins',
         'AddBinBoundary', 'GetBinScheme')      

_BinSchemes={}
for trackType in GetPartTypes():
    for varName in GetBinVarNames():
        _BinSchemes.setdefault(trackType,{})
        _BinSchemes[trackType][varName]={}

def CheckBinScheme(trackType, varName, schemeName, errorOnMissing=True):
    """Check whether the requested scheme name exists for the sepecified """
    """track type and bin variable.
If 'errorOnMissing' is True, then raises a KeyError exception upon finding """
    """a missing scheme name.
If 'errorOnMissing' is False, then returns False upon finding a missing """
    """scheme name.
Return True if the requested scheme name is found."""
    CheckPartType(trackType)
    CheckBinVarName(varName)
    schemeNames = _BinSchemes[trackType][varName].keys()
    if schemeName not in schemeNames:
        if errorOnMissing:
            msg=("Scheme name '{sname}' not in the list of bin schemes for "
            "variable '{vname}'. Possible schemes are {snames}").format(
                sname=schemeName, vname=varName, snames=str(schemeNames))
            raise KeyError(msg)
        else:
            return False
    return True

def AddBinScheme(trackType, varName, schemeName, xMin, xMax, 
    replaceCurrentScheme=False):
    """Adds a new scheme with the requested scheme name for the specified """
    """track type and bin variable with bin range [xMin, xMax].
If 'replaceCurrentScheme' is False, then a KeyError will be raised """
    """if a scheme with the same name already exists."""
    CheckPartType(trackType)
    CheckBinVarName(varName)
    schemeExists = CheckBinScheme(trackType, varName, schemeName, False)
    if schemeExists and not replaceCurrentScheme:
        msg=("Scheme name '{sname}' already in the list of bin schemes "
        "for track type '{tname}', variable '{vname}'.").format(
            sname=schemeName, tname=trackType, vname=varName)
        raise KeyError(msg)
        
                       
    _BinSchemes[trackType][varName][schemeName]=ROOT.RooBinning(xMin, xMax, 
        varName)

def SetDefaultBinScheme(trackType, varName, schemeName):
    """Set the default binning scheme for the specified track type and """
    """bin variable.
If 'muonUnBiased' is False, the default scheme for RICH calibration is set, """
    """otherwise the default scheme for muon calibration is set.
Raises a KeyError if a scheme with the requested name does not exist."""
    CheckBinScheme(trackType, varName, schemeName)
    _BinSchemes[trackType][varName]['default']=ROOT.RooBinning(
        _BinSchemes[trackType][varName][schemeName], varName)
    
def AddUniformBins(trackType, varName, schemeName, nBins, xMin, xMax):
    """Adds 'nBins' bins, uniform in the range [xMin, xMax] to the binning """
    """scheme of the specified track type and bin variable.
Raises a KeyError if a scheme with the requested name does not exist."""
    CheckBinScheme(trackType, varName, schemeName)
    _BinSchemes[trackType][varName][schemeName].addUniform(nBins, xMin, xMax)

def AddBinBoundary(trackType, varName, schemeName, boundary):
    """Adds a new bin boundary to the binning scheme of the specified """
    """track type and bin variable.
Raises a KeyError if a scheme with the requested name does not exist."""
    CheckBinScheme(trackType, varName, schemeName)
    _BinSchemes[trackType][varName][schemeName].addBoundary(boundary)
    
def GetBinScheme(trackType, varName, schemeName=None):
    """Returns a copy of the requested binning scheme (we don't want the """
    """user to modify the original scheme).
If no scheme name is specified, then the default calibration scheme is """
    """used instead.
Raises a KeyError if a scheme with the requested name does not exist."""
    if schemeName is not None:
        CheckBinScheme(trackType, varName, schemeName)
        return ROOT.RooBinning(_BinSchemes[trackType][varName][schemeName],
            varName)
    else:
        CheckBinScheme(trackType, varName, 'default')
        return ROOT.RooBinning(_BinSchemes[trackType][varName]['default'],
            varName)

###########################################################################
######        Here, we make the default binning schemes              ######
###### The user can add more binning schemes using the above methods ######
###########################################################################

### DLL(K-pi), RICH (default schemes)

for trType in GetRICHPIDPartTypes():
    # momentum
    AddBinScheme(trType, 'P', 'DLLKpi', 3000, 100000)
    AddBinBoundary(trType, 'P', 'DLLKpi', 9300) # R1 Kaon threshold
    AddBinBoundary(trType, 'P', 'DLLKpi', 15600) # R2 Kaon threshold
    AddUniformBins(trType, 'P', 'DLLKpi', 15, 19000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'DLLKpi', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'DLLKpi', 4, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'DLLKpi', 0, 500)
    AddBinBoundary(trType, 'nTrack', 'DLLKpi', 50)
    AddBinBoundary(trType, 'nTrack', 'DLLKpi', 200)
    AddBinBoundary(trType, 'nTrack', 'DLLKpi', 300)

### DLL(K-pi), "MuonUnBiased" (default schemes)

for trType in GetMuonPIDPartTypes():
    # momentum
    AddBinScheme(trType, 'P', 'DLLKpi_MuonUnBiased', 3000, 100000)
    momBoundaries = (6000, 8000, 10000, 12000, 14500, 17500, 21500, 27000,
                     32000, 40000, 60000, 70000)
    for boundary in momBoundaries:
        AddBinBoundary(trType, 'P', 'DLLKpi_MuonUnBiased', boundary) 

    # eta
    AddBinScheme(trType, 'ETA', 'DLLKpi_MuonUnBiased', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'DLLKpi_MuonUnBiased', 4, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'DLLKpi_MuonUnBiased', 0, 500)
    AddBinBoundary(trType, 'nTrack', 'DLLKpi_MuonUnBiased', 50)
    AddBinBoundary(trType, 'nTrack', 'DLLKpi_MuonUnBiased', 200)
    AddBinBoundary(trType, 'nTrack', 'DLLKpi_MuonUnBiased', 300)

### RICH performance plots

for trType in ('K', 'Pi'):
    ## for K/pi ID/misID performance plots
    
    # momentum
    AddBinScheme(trType, 'P', 'PerfPlots_KPi', 2000, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_KPi', 40, 2000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'PerfPlots_KPi', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'PerfPlots_KPi', 35, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'PerfPlots_KPi', 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_KPi', 50, 0, 500)

for trType in ('P', 'Pi'):
    ### for P/pi ID/misID performance plots
    
    # momentum
    AddBinScheme(trType, 'P', 'PerfPlots_PPi', 5000, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_PPi', 38, 5000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'PerfPlots_PPi', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'PerfPlots_PPi', 35, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'PerfPlots_PPi', 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_PPi', 50, 0, 500)

for trType in ('Mu', 'K_MuonUnBiased'):
    ### for Mu/K ID/misID performance plots

    # momentum
    AddBinScheme(trType, 'P', 'PerfPlots_MuK_MuonUnBiased', 2000, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_MuK_MuonUnBiased', 40, 2000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'PerfPlots_MuK_MuonUnBiased', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'PerfPlots_MuK_MuonUnBiased', 35, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'PerfPlots_MuK_MuonUnBiased', 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_MuK_MuonUnBiased', 50, 0, 500)

for trType in ('Mu', 'Pi_MuonUnBiased'):
    ### for Mu/pi ID/misID performance plots

    # momentum
    AddBinScheme(trType, 'P', 'PerfPlots_MuPi_MuonUnBiased', 2000, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_MuPi_MuonUnBiased', 40, 2000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'PerfPlots_MuPi_MuonUnBiased', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'PerfPlots_MuPi_MuonUnBiased', 35, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'PerfPlots_MuPi_MuonUnBiased', 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_MuPi_MuonUnBiased', 50, 0, 500)

for trType in ('Mu', 'P_MuonUnBiased'):
    ### for Mu/pi ID/misID performance plots

    # momentum
    AddBinScheme(trType, 'P', 'PerfPlots_MuP_MuonUnBiased', 2000, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_MuP_MuonUnBiased', 40, 2000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'PerfPlots_MuP_MuonUnBiased', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'PerfPlots_MuP_MuonUnBiased', 35, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'PerfPlots_MuP_MuonUnBiased', 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_MuP_MuonUnBiased', 50, 0, 500)

for trType in ('e', 'Pi'):
    ### for e/pi ID/misID performance plots
    
    # momentum
    AddBinScheme(trType, 'P', 'PerfPlots_ePi', 5000, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_ePi', 38, 5000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'PerfPlots_ePi', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'PerfPlots_ePi', 35, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'PerfPlots_ePi', 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_ePi', 50, 0, 500)

for trType in GetPartTypes():
    AddBinScheme(trType, 'P', 'PerfPlots_%s'%(trType), 0, 100000)
    AddUniformBins(trType, 'P', 'PerfPlots_%s'%(trType), 20, 0, 100000)

    AddBinScheme(trType, 'ETA', 'PerfPlots_%s'%(trType), 1.5, 5.0)
    AddUniformBins(trType, 'ETA', 'PerfPlots_%s'%(trType), 20, 1.5, 5.0)

    AddBinScheme(trType, 'HasBremAdded', 'PerfPlots_%s'%(trType), 0, 2)
    AddUniformBins(trType, 'HasBremAdded', 'PerfPlots_%s'%(trType), 2, 0, 2)

    AddBinScheme(trType, 'CaloRegion', 'PerfPlots_%s'%(trType), 2, 5)
    AddUniformBins(trType, 'CaloRegion', 'PerfPlots_%s'%(trType), 3, 2, 5)

    AddBinScheme(trType, 'nTrack', 'PerfPlots_%s'%(trType), 0, 500)
    AddUniformBins(trType, 'nTrack', 'PerfPlots_%s'%(trType), 20, 0, 500)

    AddBinScheme(trType, 'nSPDHits', 'PerfPlots_%s'%(trType), 0, 500)
    AddUniformBins(trType, 'nSPDHits', 'PerfPlots_%s'%(trType), 20, 0, 500)

### set the default binning schemes
for trType in GetRICHPIDPartTypes():
    SetDefaultBinScheme(trType, 'P', 'DLLKpi')
    SetDefaultBinScheme(trType, 'ETA', 'DLLKpi')
    SetDefaultBinScheme(trType, 'nTrack', 'DLLKpi')

for trType in GetMuonPIDPartTypes():
    SetDefaultBinScheme(trType, 'P', 'DLLKpi_MuonUnBiased')
    SetDefaultBinScheme(trType, 'ETA', 'DLLKpi_MuonUnBiased')
    SetDefaultBinScheme(trType, 'nTrack', 'DLLKpi_MuonUnBiased')
