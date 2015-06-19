from ROOT import *
import sys
import os
import time

#####################################
# Author: Carlos Vazquez            #
# carlos.vazquez@cern.ch            #
#####################################

##### Input file and name of the tree:
inputPath = "/scratch02/carlos_vazquez/FinalTuples/MagUpAndDown4000GeVReco14s20r0p1dv33r4_2062pb_StrippingBetaSBs2JpsiKstarWideLine_2012_DOCA_withcuts.root"
inputTree = "DecayTree"
##### Output file:
outputPath = "./MagUpAndDown4000GeVReco14s20r0p1dv33r4_2062pb_StrippingBetaSBs2JpsiKstarWideLine_2012_BDTG_Loose.root"
##### Method name, GL weights filename and variables list:
nameMethod = "BDTG"
variablesList = ["max_DOCA","B0_LOKI_DTF_CTAU","lessIPS","B0_PT","B0_IP_OWNPV","B0_ENDVERTEX_CHI2"]
##### Weight class file path:
inputClass = "./BDTG_Loose_2012.C"
#####################################

timeZero = time.time()

print '\n* Input file: ' + inputPath + ':' + inputTree
variableString = variablesList[0]
if len(variablesList)>1:
  for ii in range(len(variablesList)-1):
    variableString += ', ' + variablesList[ii+1]
print '* Variables: ' + variableString
print '* Methods: ' + nameMethod
print '* Output file: ' + outputPath + ':' + inputTree

try:
  dummyFile = open(inputClass,"r")
  dummyFile.close()
except:
  sys.exit("\nERROR: "+inputClass+" does not exist.\n")

print '\nLoading and copying input file...\n'
os.system("cp " + inputPath + " " + outputPath)
myFile = TFile(outputPath,"UPDATE")
myTree = myFile.Get(inputTree)

print 'Loading TMVAoperators...\n'
os.system("cp $SOMEUTILSROOT/src/vdouble.C .")
sys.path.append(os.environ["BS2MUMUROOT"] +"/python/Bs2MuMu/") # This path is not defined in Erasmus anymore. Needs Urania.
from TMVAoperators import *
print '\nLoading TMVAoperator class...\n'
myMethod = TMVAoperator(inputClass,nameMethod,variablesList)

gROOT.ProcessLine(\
    "struct MyStruct{\
     Float_t methodFloat;\
    };")
from ROOT import MyStruct

methodValue = MyStruct()
methodBranch = myTree.Branch(nameMethod, AddressOf(methodValue,'methodFloat'), nameMethod+'/F')

print '\nExtracting MVA values...\n'

eventCounter = 0
for event in myTree:
  ## methodValue:
  methodValue.methodFloat = myMethod.GetMvaValue(event)
  methodBranch.Fill()
  eventCounter += 1
  if not eventCounter%10000:
    print str(eventCounter) + ' events processed...'

print '\nSaving output file...'
myTree.Write("",TObject.kOverwrite)
myFile.Close()

totalTime = time.time()-timeZero
print 'Elapsed time: ' + str(round(totalTime,4)) + ' s.'
os.system("rm vdouble*")
print 'Done.\n'
