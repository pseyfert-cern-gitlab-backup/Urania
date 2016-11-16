from ROOT import *
import time

####################################
nameFile = "xx.root" ## Modify me
nameTree = "DecayTree" ## Modify me
####################################

timeZero = time.time()

myFile = TFile(nameFile,'UPDATE')
myTree = myFile.Get(nameTree)

gROOT.ProcessLine(\
    "struct MyStruct{\
     Float_t lifepsFloat;\
    };")
from ROOT import MyStruct

lifepsValue = MyStruct()
lifepsBranch = myTree.Branch('B0_LIFE_PS', AddressOf(lifepsValue,'lifepsFloat'), 'B0_LIFE_PS/F')

conversion_factor = 3.3356409519815204

eventCounter = 0
for event in myTree:
  lifepsValue.lifepsFloat = conversion_factor*float(event.B0_LOKI_DTF_CTAU)
  lifepsBranch.Fill()
  eventCounter += 1
  if not eventCounter%10000:
    print str(eventCounter) + ' events processed...'

print '\nSaving output file...'
myTree.Write("",TObject.kOverwrite)
myFile.Close()

totalTime = time.time()-timeZero
print 'Elapsed time: ' + str(round(totalTime,4)) + ' s.'
print 'Done.\n'

