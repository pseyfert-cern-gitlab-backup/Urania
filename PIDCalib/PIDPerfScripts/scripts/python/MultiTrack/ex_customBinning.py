"""This file is an example of a user-defined binning scheme file, which """ \
"""can be passed as an argument to the multi-track calibration scripts.
The methods for constructing binning schema are defined in """ \
"""$PIDPERFSCRIPTSROOT/python/PIDPerfScripts/binning.py."""

from PIDPerfScripts.binning import *
from PIDPerfScripts.RunRangeFuncs import GetRICHPIDPartTypes
from PIDPerfScripts.RunRangeFuncs import GetMuonPIDPartTypes

### DLL(K-pi), RICH (alternative schemes)

for trType in GetRICHPIDPartTypes():
    # momentum
    AddBinScheme(trType, 'P', 'DLLKpi_alt', 2000, 100000)
    AddBinBoundary(trType, 'P', 'DLLKpi_alt', 9300) # R1 Kaon threshold
    AddBinBoundary(trType, 'P', 'DLLKpi_alt', 15600) # R2 Kaon threshold
    AddUniformBins(trType, 'P', 'DLLKpi_alt', 15, 19000, 100000)

    # eta
    AddBinScheme(trType, 'ETA', 'DLLKpi_alt', 1.5, 5)
    AddUniformBins(trType, 'ETA', 'DLLKpi_alt', 2, 1.5, 5)

    # nTrack
    AddBinScheme(trType, 'nTrack', 'DLLKpi_alt', 0, 500)
    AddUniformBins(trType, 'nTrack', 'DLLKpi_alt', 2, 0, 500)

### DLL(K-pi), RICH (P and PT binning schemes)
for trType in GetRICHPIDPartTypes():
    # momentum
    AddBinScheme(trType, 'P', 'DLLKpi_PPT', 2000, 100000)
    AddBinBoundary(trType, 'P', 'DLLKpi_PPT', 9300) # R1 Kaon threshold
    AddBinBoundary(trType, 'P', 'DLLKpi_PPT', 15600) # R2 Kaon threshold
    AddUniformBins(trType, 'P', 'DLLKpi_PPT', 15, 19000, 100000)

    # pt 
    AddBinScheme(trType, 'PT', 'DLLKpi_PPT', 250, 5000)
    AddUniformBins(trType, 'PT', 'DLLKpi_PPT', 10, 250, 5000)
 
