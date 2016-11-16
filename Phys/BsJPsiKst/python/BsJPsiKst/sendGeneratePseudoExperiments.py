import os
import sys

# ------ Input args ----------
iexpMin       = int(sys.argv[1]) # int to tag the mKpi bin
iexpMax       = int(sys.argv[2]) # int to tag the mKpi bin
OutPutTag     = str(sys.argv[3]) # string to tag the name of the OutPutFile
_USE_GRID_    = int(sys.argv[4]) # int to tag the use of GRID
doPeakingBkgs = int(sys.argv[5]) # int to enable peaking bkgs generation
simultaneous  = int(sys.argv[6]) # int to enable simultaneous parameters in generation
nonZeroACPs   = int(sys.argv[7]) # int to flag if we generate the ACPs with non zero values
if nonZeroACPs:
    ACPset    = str(sys.argv[8]) # string to tag the set of ACPs

Command = "python generatePseudoExperiments.py"
if simultaneous:
    Command = "python generatePseudoExperiments_Simultaneous.py"


for i in range(iexpMin,iexpMax):
    if nonZeroACPs:
        print "%s %s %s %s %s %s %s"%(Command, i, OutPutTag, _USE_GRID_, doPeakingBkgs, nonZeroACPs, ACPset)
        os.system("%s %s %s %s %s %s %s"%(Command, i, OutPutTag, _USE_GRID_, doPeakingBkgs, nonZeroACPs, ACPset))
    else:
        print "%s %s %s %s %s %s"%(Command, i, OutPutTag, _USE_GRID_, doPeakingBkgs, nonZeroACPs)
        os.system("%s %s %s %s %s %s"%(Command, i, OutPutTag, _USE_GRID_, doPeakingBkgs, nonZeroACPs))
        
