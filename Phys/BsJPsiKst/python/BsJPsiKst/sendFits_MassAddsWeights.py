import os
import sys

# ------ Input args ----------
tupleSource   = str(sys.argv[1]) # string to tag the source of ntuples: 'Toys' or 'Data' 
_USE_GRID_    = int(sys.argv[2]) # bool to tag if we are on the grid or not (files location)
include_Lb    = str(sys.argv[3]) # str to tag Lb bkg is included: 'Lb' or 'noLb'
inPutTag      = str(sys.argv[4]) # string to tag the name of the InPutFile
outPutTag     = str(sys.argv[5]) # string to tag the name of the OutPutFile
iexpMin       = int(sys.argv[6]) # int to tag the nbr of the experiment
iexpMax       = int(sys.argv[7]) # int to tag the nbr of the experiment
simultaneous  = int(sys.argv[8]) # int to enable simultaneous parameters in fit
fractions     = int(sys.argv[9]) # int to enable yield fractions parameters in fit

Command = "python fitMassAddsWeights_OneExp.py"
if simultaneous:
    Command = "python fitMassAddsWeights_OneExpSimultaneous.py"
if fractions:
    Command = "python fitMassAddsWeights_OneExpFractions.py"

for i in range(iexpMin,iexpMax):
    print "%s %s %s %s %s %s %s"%(Command, tupleSource, _USE_GRID_, include_Lb, inPutTag, outPutTag, i)
    os.system("%s %s %s %s %s %s %s"%(Command, tupleSource, _USE_GRID_, include_Lb, inPutTag, outPutTag, i))

