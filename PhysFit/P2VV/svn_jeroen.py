python = [
   "compatibility.py",
   "Dilution.py",
   "P2VVGeneralUtils.py",
   "P2VVImports.py",
   "RooFitDecorators.py",
   "RooFitWrappers.py",
   "ROOTDecorators.py",
   "ToyMCUtils.py"]

P2VVLoad = [
     "__init__.py", 
     "LHCbStyle.py",
     "MultiCatGen.py",
     "P2VVLibrary.py",
     "RooFitOutput.py"
     ]
examples = [
   "amplitudeMoments.py",
   "Bs2JpsiKKFit.py",
   "computeAngEffMoments.py",
   "plotAngEfficiency.py",
   "plotSWavePhases.py",
   "timeAnglesSignal.py"
   ]

include = [
   "Functions.h",
   "MultiHistEntry.h",
   "ProgressDisplay.h",
   "RooAbsEffResModel.h",
   "RooAvEffConstraint.h",
   "RooBinnedPdf.h",
   "RooBoxPdf.h",
   "RooBTagDecay.h",
   "RooCalibratedDilution.h",
   "RooComplementCoef.h",
   "RooCorrectedSWeight.h",
   "RooCruijff.h",
   "RooDataSetToTree.h",
   "RooEffConvGenContext.h",
   "RooEfficiencyBin.h",
   "RooEffResModel.h",
   "RooExplicitNormPdf.h",
   "RooMultiCatGenerator.h",
   "RooMultiEffResModel.h",
   "RooP2VVAngleBasis.h",
   "RooRealCategory.h",
   "RooRealMoments.h",
   "RooRelBreitWigner.h",
   "RooTagDecisionWrapper.h",
   "RooThresholdPdf.h",
   "RooTransAngle.h",
   "RooTrivialTagDecay.h"
   ]

src = [
   "Functions.cxx",
   "ProgressDisplay.cxx",
   "RooAbsEffResModel.cxx",
   "RooAvEffConstraint.cxx",
   "RooBinnedPdf.cxx",
   "RooBoxPdf.cxx",
   "RooBTagDecay.cxx",
   "RooCalibratedDilution.cxx",
   "RooComplementCoef.cxx",
   "RooCorrectedSWeight.cxx",
   "RooCruijff.cxx",
   "RooDataSetToTree.cxx",
   "RooEffConvGenContext.cxx",
   "RooEfficiencyBin.cxx",
   "RooEffResModel.cxx",
   "RooExplicitNormPdf.cxx",
   "RooMultiCatGenerator.cxx",
   "RooMultiEffResModel.cxx",
   "RooP2VVAngleBasis.cxx",
   "RooRealCategory.cxx",
   "RooRealMoments.cxx",
   "RooRelBreitWigner.cxx",
   "RooTagDecisionWrapper.cxx",
   "RooThresholdPdf.cxx",
   "RooTransAngle.cxx",
   "RooTrivialTagDecay.cxx"
]

from os import system as shell

for thing in python:
    shell("svn add python/"+thing)
    
for thing in P2VVLoad:
    shell("svn add python/P2VVLoad/"+thing)

for thing in src:
    shell("svn add src/"+thing)

for thing in include:
    shell("svn add include/"+thing)
    
for thing in examples:
    shell("svn add examples/"+thing)
    
    
