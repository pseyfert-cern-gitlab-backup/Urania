"""This file is an example of a user-defined binning scheme file, which """ \
"""can be passed as an argument to the multi-track calibration scripts.
The methods for constructing binning schema are defined in """ \
"""$PIDPERFSCRIPTSROOT/python/PIDPerfScripts/binning.py."""

from PIDPerfScripts.binning import *
from PIDPerfScripts.RunRangeFuncs import GetRICHPIDPartTypes
from PIDPerfScripts.RunRangeFuncs import GetMuonPIDPartTypes

### DLL(K-pi), RICH (alternative schemes)

for trType in ["e","Mu"]:
    # momentum
    AddBinScheme(trType, 'P', 'emu', 3800, 150000)
    AddBinBoundary(trType, 'P', 'emu', 120000)
    AddBinBoundary(trType, 'P', 'emu', 100000)
    AddUniformBins(trType, 'P', 'emu', 10, 3800, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'emu', 1.5, 5)
    AddBinBoundary(trType, 'ETA', 'emu', 2.2)
    AddBinBoundary(trType, 'ETA', 'emu', 4)
    AddUniformBins(trType, 'ETA', 'emu', 2, 2.2, 4)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'emu', 0, 500)
    AddBinBoundary(trType, 'nTrack', 'emu', 300)
    AddUniformBins(trType, 'nTrack', 'emu', 4, 0, 300)

for trType in ["Pi"]:
    # momentum
    AddBinScheme(trType, 'P', 'emu', 1000, 20000)
    AddBinBoundary(trType, 'P', 'emu', 15000)
    AddUniformBins(trType, 'P', 'emu', 10, 1000, 15000)

    # eta
    AddBinScheme(trType, 'ETA', 'emu', 1.5, 5)
    AddBinBoundary(trType, 'ETA', 'emu', 2.2)
    AddBinBoundary(trType, 'ETA', 'emu', 4)
    AddUniformBins(trType, 'ETA', 'emu', 2, 2.2, 4)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'emu', 0, 500)
    AddBinBoundary(trType, 'nTrack', 'emu', 300)
    AddUniformBins(trType, 'nTrack', 'emu', 4, 0, 300)
 
