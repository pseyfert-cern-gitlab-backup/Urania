from ROOT import *
import time
import os
import math
# --------------------------------------------
inputPath = "dataTuple.root" # Update.
outputPath = "dataTuplewCosines.root" # Update.
treeName = "DecayTree" # Update.
# --------------------------------------------
print '\nStarting...'
print '\nCopying tuple...'
timeZero = time.time()
os.system('cp '+inputPath+' '+outputPath)
timeCopy = time.time()-timeZero
print 'Done. Elapsed time: '+str(round(timeCopy,4))+' s.'
print '\nIncluding cosines...\n'
timeZero = time.time()
myFile = TFile(outputPath,"UPDATE")
myTree = myFile.Get(treeName)
# --------------------------------------------
gROOT.ProcessLine(\
    "struct MyStruct{\
     Float_t helK_Float;\
     Float_t helL_Float;\
    };")
from ROOT import MyStruct
# --------------------------------------------
helK_Value = MyStruct()
helK_Branch = myTree.Branch('helcosthetaK', AddressOf(helK_Value,'helK_Float'), 'helcosthetaK/F')
helL_Value = MyStruct()
helL_Branch = myTree.Branch('helcosthetaL', AddressOf(helL_Value,'helL_Float'), 'helcosthetaL/F')
# --------------------------------------------
eventCounter = 0
for event in myTree:
  helK_Value.helK_Float = math.cos(float(event.B0_ThetaK))
  helK_Branch.Fill()
  helL_Value.helL_Float = math.cos(float(event.B0_ThetaL))
  helL_Branch.Fill()
  eventCounter += 1
  if not eventCounter%10000:
    print str(eventCounter) + ' events processed...'
# --------------------------------------------
print '\nSaving output file...'
myTree.Write("",TObject.kOverwrite)
myFile.Close()
totalTime = time.time()-timeZero
print 'Done. Elapsed time: ' + str(round(totalTime,4)) + ' s.\n'
# --------------------------------------------
