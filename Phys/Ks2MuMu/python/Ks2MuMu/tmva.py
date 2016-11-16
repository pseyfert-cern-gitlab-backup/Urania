#!/usr/bin/env python
# @(#)root/tmva $Id: TMVAClassification.py,v 1.59.2.1 2008/12/02 08:51:43 andreas.hoecker Exp $
# ------------------------------------------------------------------------------ #
# Project      : TMVA - a Root-integrated toolkit for multivariate data analysis #
# Package      : TMVA                                                            #
# Python script: TMVAClassification.py                                           #
#                                                                                #
# This python script provides examples for the training and testing of all the   #
# TMVA classifiers through PyROOT. Note that the use PyROOT requires that you    #
# have a python version > 2.2 installed on your computer.                        #
#                                                                                #
# The Application works similarly, please see:                                   #
#    TMVA/macros/TMVAClassificationApplication.C                                 #
# For regression, see:                                                           #
#    TMVA/macros/TMVARegression.C                                                #
#    TMVA/macros/TMVARegressionpplication.C                                      #
# and translate to python as done here.                                          #
#                                                                                #
# As input data is used a toy-MC sample consisting of four Gaussian-distributed  #
# and linearly correlated input variables.                                       #
#                                                                                #
# The methods to be used can be switched on and off via the prompt command, for  #
# example:                                                                       #
#                                                                                #
#    python TMVAClassification.py --methods Fisher,Likelihood                    #
#                                                                                #
# The output file "TMVA.root" can be analysed with the use of dedicated          #
# macros (simply say: root -l <../macros/macro.C>), which can be conveniently    #
# invoked through a GUI that will appear at the end of the run of this macro.    #
#                                                                                #
# for help type "python TMVAClassification.py --help"                            #
# ------------------------------------------------------------------------------ #

# --------------------------------------------
# Standard python import
import sys, os    # exit
sys.path.append(os.environ["BS2MUMUROOT"] +"/python/Bs2MuMu/")
import time   # time accounting
import getopt # command line parser
from smartpyROOT import *
from triggerclass import *
from SomeUtils.NewKarlen import *
from SomeUtils.someFunctions import *
# --------------------------------------------



variables = ["Bips", "lessIPSmu", "Vchi2", "Bdissig"]

outfname    = "TMVA_C12_r.root"



#methods     = "Cuts,CutsD,CutsPCA,CutsGA,CutsSA,Likelihood,LikelihoodD,LikelihoodPCA,LikelihoodKDE,LikelihoodMIX,PDERS,PDERSD,PDERSPCA,PDERSkNN,PDEFoam,KNN,HMatrix,Fisher,FisherG,BoostedFisher,LD,FDA_GA,FDA_SA,FDA_MC,FDA_MT,FDA_GAMT,FDA_MCMT,MLP,MLPBFGS,CFMlpANN,TMlpANN,SVM,BDT,BDTD,BDTG,BDTB,RuleFit"

#methods     = "PDERS,PDERSD,PDERSPCA,PDERSkNN,PDEFoam,KNN,FisherG,BoostedFisher,FDA_GA,FDA_SA,FDA_MC,FDA_MT,FDA_GAMT,FDA_MCMT,MLP,MLPBFGS,CFMlpANN,TMlpANN,SVM,BDT,BDTD,BDTG,BDTB,RuleFit"
verbose     = False
methods = {} ## Dictionary of TMVA methods, grouping  those that have some common origin (for example, all BDT's together, all NN's ....)
mlist = []  ## HEre I'dd appendl latter all methods I want to test
#cuts = ["Cuts","CutsD","CutsPCA","CutsGA","CutsSA"]
#likelihoods = ["Likelihood","LikelihoodD","LikelihoodPCA","LikelihoodKDE","LikelihoodMIX"]
methods["PDERS"] = ["PDERS","PDERSD","PDERSPCA","PDERSkNN"]
#methods["PDEFoam"] = ["PDEFoam"]
methods["KNN"] = ["KNN"]
methods["Fisher"] = ["FisherG"]
methods["Boost"] = ["BoostedFisher"]
methods["FDA"] = ["FDA_GA","FDA_SA","FDA_MC","FDA_MT","FDA_GAMT","FDA_MCMT"]
methods["MLP"] =["MLP","MLPBFGS"]
methods["CFMlpANN"] = ["CFMlpANN"]
methods["TMlpANN"] = ["TMlpANN"]
methods["BDT"] = ["BDT","BDTD","BDTG","BDTB"]
methods["RuleFit"] = ["RuleFit"]
methods["SVM"] = ["SVM"]

for x in methods.values(): mlist += x
mlist = methods["BDT"]   ### Here I redefine mlist to use only BDT's. To make a fast check


print "=== TMVAClassification: use method(s)..."
for m in mlist:
    if m.strip() != '':
        print "=== - <%s>" % m.strip()

    # Import ROOT classes
from ROOT import gSystem, gROOT, gApplication, TFile, TTree, TCut, TH1F
    
   
    # Logon not automatically loaded through PyROOT (logon loads TMVA library) load also GUI
gROOT.SetMacroPath( "../macros/" )
gROOT.Macro       ( "../macros/TMVAlogon.C" )    
gROOT.LoadMacro   ( "../macros/TMVAGui.C" )
    
    # Import TMVA classes from ROOT
from ROOT import TMVA

    # Output file
outputFile = TFile( outfname, 'RECREATE' )
    
    # Create instance of TMVA factory (see TMVA/macros/TMVAClassification.C for more factory options)
    # All TMVA output can be suppressed by removing the "!" (not) in 
    # front of the "Silent" argument in the option string
factory = TMVA.Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D" )

    # Set verbosity
factory.SetVerbose( verbose )
    
    # If you wish to modify default settings 
    # (please check "src/Config.h" to see all available global options)
    #    gConfig().GetVariablePlotting()).fTimesRMS = 8.0
    #    gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory"


    # Define the input variables that shall be used for the classifier training
    # note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
    # [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

for var in variables: factory.AddVariable( var,var, "units", 'F' )
    
    # You can add so-called "Spectator variables", which are not used in the MVA training, 
    # but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the 
    # input variables, the response values of all trained MVAs, and the spectator variables
factory.AddSpectator( "Bmass",  "Spectator 1", "units")#, 'F' )
factory.AddSpectator( "evt",  "Spectator 2", "units")#, 'F' )

   

    # Get the signal and background trees for training
signal_train, f1      = getTuple("/afs/cern.ch/user/d/diegoms/vol5/bstrainS")#,thing = "Ks2pipi")#/Bs2MuMu")
signal_test, f2      = getTuple("/afs/cern.ch/user/d/diegoms/vol5/bstestS")#,thing = "Ks2pipi")#/Bs2MuMu")
bkg_train, f3      = getTuple("/afs/cern.ch/user/d/diegoms/vol5/bstrainB")#,thing = "Ks2mumu")#/Bs2MuMu")
bkg_test, f4     = getTuple("/afs/cern.ch/user/d/diegoms/vol5/bstestB")#,thing = "Ks2mumu")#/Bs2MuMu")
#BREAK

## signal_train, f1      = getTuple("~/vol5/bstrainS")#,thing = "Bs2MuMu")#/Bs2MuMu")
## signal_test, f2      = getTuple("~/vol5/bstestS")#,thing = "Bs2MuMu")#/Bs2MuMu")
## bkg_train, f3      = getTuple("~/vol5/bstrainB")#,thing = "Bs2MuMu")
## bkg_test, f4      = getTuple("~/vol5/bstestB")#,thing = "Bs2MuMu")
signalWeight     = 1.0
bkgWeight = 1.0

    # To give different trees for training and testing, do as follows:
factory.AddSignalTree( signal_train, signalWeight, "Training" )
factory.AddSignalTree( signal_test,    signalWeight,  "Test" )
factory.AddBackgroundTree( bkg_train, bkgWeight, "Training" )
factory.AddBackgroundTree( bkg_test,    bkgWeight,  "Test" )


    
    # Use the following code instead of the above two or four lines to add signal and background 
    # training and test events "by hand"
    # NOTE that in this case one should not give expressions (such as "var1+var2") in the input 
    #      variable definition, but simply compute the expression before adding the event
    #
    #    # --- begin ----------------------------------------------------------
    #    
    # ... *** please lookup code in TMVA/macros/TMVAClassification.C ***
    #    
    #    # --- end ------------------------------------------------------------
    #
    # ====== end of register trees ==============================================    
            
    # This would set individual event weights (the variables defined in the 
    # expression need to exist in the original TTree)
    #    for signal    : factory.SetSignalWeightExpression("weight1*weight2")
    #    for background: factory.SetBackgroundWeightExpression("weight1*weight2")

    # Apply additional cuts on the signal and background sample. 
    # example for cut: mycut = TCut( "abs(var1)<0.5 && abs(var2-0.5)<1" )
mycutSig = TCut( "" ) 
mycutBkg = TCut( "" ) 
    
    # Here, the relevant variables are copied over in new, slim trees that are
    # used for TMVA training and testing
    # "SplitMode=Random" means that the input events are randomly shuffled before
    # splitting them into training and test samples
factory.PrepareTrainingAndTestTree( mycutSig, mycutBkg,"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" )

    # ... and alternative call to use a different number of signal and background training/test event is:
    # factory.PrepareTrainingAndTestTree( mycut, "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" )

    # --------------------------------------------------------------------------------------------------

    # ---- Book MVA methods
    #
    # please lookup the various method configuration options in the corresponding cxx files, eg:
    # src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
    # it is possible to preset ranges in the option string in which the cut optimisation should be done:
    # "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

    # Cut optimisation
if "Cuts" in mlist:factory.BookMethod( TMVA.Types.kCuts, "Cuts", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" )

if "CutsD" in mlist:factory.BookMethod( TMVA.Types.kCuts, "CutsD","!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" )

if "CutsPCA" in mlist: factory.BookMethod( TMVA.Types.kCuts, "CutsPCA","!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" )
    
if "CutsGA" in mlist: factory.BookMethod( TMVA.Types.kCuts, "CutsGA", "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" )
   
if "CutsSA" in mlist: factory.BookMethod( TMVA.Types.kCuts, "CutsSA","!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" )
   
    # Likelihood
if "Likelihood" in mlist: factory.BookMethod( TMVA.Types.kLikelihood, "Likelihood", "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" )

    # test the decorrelated likelihood
if "LikelihoodD" in mlist: factory.BookMethod( TMVA.Types.kLikelihood, "LikelihoodD", "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" )

if "LikelihoodPCA" in mlist:factory.BookMethod( TMVA.Types.kLikelihood, "LikelihoodPCA","!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" )
 
    # test the new kernel density estimator
if "LikelihoodKDE" in mlist: factory.BookMethod( TMVA.Types.kLikelihood, "LikelihoodKDE", "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" )

    # test the mixed splines and kernel density estimator (depending on which variable)
if "LikelihoodMIX" in mlist: factory.BookMethod( TMVA.Types.kLikelihood, "LikelihoodMIX", "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" )

    # test the multi-dimensional probability density estimator
    # here are the options strings for the MinMax and RMS methods, respectively:
    #      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );   
    #      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );   
if "PDERS" in mlist: factory.BookMethod( TMVA.Types.kPDERS, "PDERS", "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" )

if "PDERSkNN" in mlist:factory.BookMethod( TMVA.Types.kPDERS, "PDERSkNN", "!H:!V:VolumeRangeMode=kNN:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" )

if "PDERSD" in mlist:factory.BookMethod( TMVA.Types.kPDERS, "PDERSD", "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" )

if "PDERSPCA" in mlist: factory.BookMethod( TMVA.Types.kPDERS, "PDERSPCA", "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" )

    # Multi-dimensional likelihood estimator using self-adapting phase-space binning
if "PDEFoam" in mlist: factory.BookMethod( TMVA.Types.kPDEFoam, "PDEFoam", "H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0333:nActiveCells=500:nSampl=2000:nBin=5:CutNmin=T:Nmin=100:Kernel=None:Compress=T" )

    # K-Nearest Neighbour classifier (KNN)
if "KNN" in mlist: factory.BookMethod( TMVA.Types.kKNN, "KNN", "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" )
    # H-Matrix (chi2-squared) method
if "HMatrix" in mlist: factory.BookMethod( TMVA.Types.kHMatrix, "HMatrix", "!H:!V" ); 
            
    # Fisher discriminant   
if "Fisher" in mlist: factory.BookMethod( TMVA.Types.kFisher, "Fisher", "H:!V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=60:NsmoothMVAPdf=10" )

    # Fisher with Gauss-transformed input variables
if "FisherG" in mlist: factory.BookMethod( TMVA.Types.kFisher, "FisherG", "H:!V:VarTransform=Gauss" )
            
    # Composite classifier: ensemble (tree) of boosted Fisher classifiers
if "BoostedFisher" in mlist: factory.BookMethod( TMVA.Types.kFisher, "BoostedFisher", "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2")

    # Linear discriminant (same as Fisher)
if "LD" in mlist: factory.BookMethod( TMVA.Types.kLD, "LD", "H:!V:VarTransform=None" )
            
	 # Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
if "FDA_MC" in mlist:factory.BookMethod( TMVA.Types.kFDA, "FDA_MC", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" )
   
if "FDA_GA" in mlist: factory.BookMethod( TMVA.Types.kFDA, "FDA_GA","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" )

if "FDA_SA" in mlist: factory.BookMethod( TMVA.Types.kFDA, "FDA_SA", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" )

if "FDA_MT" in mlist:factory.BookMethod( TMVA.Types.kFDA, "FDA_MT", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" )

if "FDA_GAMT" in mlist:factory.BookMethod( TMVA.Types.kFDA, "FDA_GAMT","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" )
        
if "FDA_MCMT" in mlist: factory.BookMethod( TMVA.Types.kFDA, "FDA_MCMT", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" )

    # TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
if "MLP" in mlist: factory.BookMethod( TMVA.Types.kMLP, "MLP",  "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5" )

if "MLPBFGS" in mlist: factory.BookMethod( TMVA.Types.kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS" )

    # CF(Clermont-Ferrand)ANN
if "CFMlpANN" in mlist: factory.BookMethod( TMVA.Types.kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  );  # n_cycles:#nodes:#nodes:...  
  
    # Tmlp(Root)ANN
if "TMlpANN" in mlist: factory.BookMethod( TMVA.Types.kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  )
  
    # Support Vector Machine
if "SVM" in mlist: factory.BookMethod( TMVA.Types.kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" )
            
    # Boosted Decision Trees
if "BDTG" in mlist: factory.BookMethod( TMVA.Types.kBDT, "BDTG", "!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.30:UseBaggedGrad:GradBaggingFraction=0.6:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=50:NNodesMax=5" )

if "BDT" in mlist: factory.BookMethod( TMVA.Types.kBDT, "BDT", "!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" )
   
if "BDTB" in mlist: factory.BookMethod( TMVA.Types.kBDT, "BDTB",  "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" )

if "BDTD" in mlist: factory.BookMethod( TMVA.Types.kBDT, "BDTD", "!H:!V:NTrees=250:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" )
   
    # RuleFit -- TMVA implementation of Friedman's method
if "RuleFit" in mlist: factory.BookMethod( TMVA.Types.kRuleFit, "RuleFit", "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" )

    # --------------------------------------------------------------------------------------------------
            
    # ---- Now you can tell the factory to train, test, and evaluate the MVAs. 

    # Train MVAs
factory.TrainAllMethods()
    
    # Test MVAs
factory.TestAllMethods()
    
    # Evaluate MVAs
factory.EvaluateAllMethods()    
    
    # Save the output.
variablesx = variables
#for x in Y8:
 #   if x not in variablesx: variablesx.append(x)
#for x in C12:
 #   if x not in variablesx: variablesx.append(x)

### GL construction
s = channelData(fromRootToListDic(signal_train, labels = ["evt","Bmass"] + variablesx))
b = channelData(fromRootToListDic(bkg_train, labels = ["evt","Bmass"] + variablesx))
## s.addVariable("isoSum",["mu1iso5","mu2iso5"], suma)
## s.addVariable("minpt", ["mu1pt","mu2pt"], min)
## b.addVariable("isoSum",["mu1iso5","mu2iso5"], suma)
## b.addVariable("minpt", ["mu1pt","mu2pt"], min)

s2 = channelData(fromRootToListDic(signal_test, labels = ["evt","Bmass"] + variablesx))
b2 = channelData(fromRootToListDic(bkg_test, labels = ["evt","Bmass"] + variablesx))
#BREAK
## s2.addVariable("isoSum",["mu1iso5","mu2iso5"], suma)
## s2.addVariable("minpt", ["mu1pt","mu2pt"], min)
## b2.addVariable("isoSum",["mu1iso5","mu2iso5"], suma)
## b2.addVariable("minpt", ["mu1pt","mu2pt"], min)


Ns = len(s2)
Nb = len(b2)


GL = NewKarlen(s,b ,variables )

#GLK = NewKarlen(s,b , ["mu1iso5","mu2iso5","DOCA", "Blife_ps","Bip","lessIPSmu", "Bpt"] )
#GLKb =GLK # NewKarlen(s,b , ["mu1iso5","mu2iso5","DOCA", "Blife_ps","Bip","lessIPSmu", "Bpt","Vchi2", "buggy_angle"] )
#GLi = NewKarlen(s,b ,variables0 )

#GL2 = IsoGL_noC(s,b,variables0,isos)
#multiGL = IsoGL(s,b,variables0,isos)

GL(b,"GLmva")
GL(s, "GLmva")
#GLK(s,"GLK")
#GLK(b,"GLK")
#GLKb(s,"GLKb")
#GLKb(b,"GLKb")

GL(b2,"GLmva")
GL(s2, "GLmva")
#GLK(s2,"GLK")
#GLK(b2,"GLK")
#GLKb(s2,"GLKb")
#GLKb(b2,"GLKb")

#GLi(b2,"GLmvai")
#GLi(s2, "GLmvai")

#multiGL(s2, "multiGL")
#multiGL(b2, "multiGL")
#GL2(s2, "multiGL2")
#GL2(b2, "multiGL2")


ggl = TH1F("GL","GL",100,0.,1.)
#gglisocut = TH1F("GLic","GLic",100,0.,1.)
#hgl = TH1F("HGL","HGL",100,0.,1.)
#hgl2 = TH1F("HGL2","HGL2",100,0.,1.)

for i in range(50):
    x = 0.02*i
    cut = Cut("GLmvasb.>"+str(x))
    #cut2 = Cut("GLKsb.>"+str(x))
    #cut3 = Cut("GLKbsb.>"+str(x))
    
    dumis = cut(s2)
    dumib = cut(b2)
    dumis.desagrupate()
    dumib.desagrupate()
    ggl.Fill(len(dumis)*1./Ns, 1.-len(dumib)*1./Nb)
    
    #dumis = cut2(s2)
    #dumib = cut2(b2)
    #dumis.desagrupate()
    #dumib.desagrupate()
    #hgl.Fill(len(dumis)*1./Ns, 1.-len(dumib)*1./Nb)
   
    #dumis = cut3(s2)
    #dumib = cut3(b2)
    #dumis.desagrupate()
    #dumib.desagrupate()
    #hgl2.Fill(len(dumis)*1./Ns, 1.-len(dumib)*1./Nb)
    
ggl.SetName("GL")
ggl.Write()
#gglisocut.Write()
#hgl.Write()
#hgl2.Write()
outputFile.Close()
colors = {}
from ROOT import *
colors["PDERS"] = kYellow
colors["PDEFoam"] = kYellow
colors["KNN"] = kBlack
colors["Fisher"] = kGreen
colors["Boost"] = kGreen 
colors["FDA"] = kCyan
colors["MLP"] = kBlue
colors["CFMlpANN"] = kBlue


colors["TMlpANN"] = kBlue
colors["BDT"] = kOrange
colors["RuleFit"] = kPink
colors["SVM"] = kViolet

    # open the GUI for the result macros    
#gROOT.ProcessLine( "TMVAGui(\"%s\")" % outfname )
    
    # keep the ROOT thread running
#gApplication.Run()

f = TFile(outfname)

gl = f.Get("GL")
#glz = f.Get("GLic")
#hgl = f.Get("HGL")
#hgl2 = f.Get("HGL2")

for i in range(gl.GetNbinsX()):
    gl.SetBinError(i+1,0)
    ## glz.SetBinError(i+1,0)
    #hgl.SetBinError(i+1,0)
    #hgl2.SetBinError(i+1,0)
    
gl.Draw()
#hgl.SetLineColor(kBlue)
#hgl.Draw("same")
#hgl2.SetLineColor(kGreen)
#hgl2.Draw("same")

d = {}
for k in methods.keys():
    for method in methods[k]:
        if method not in mlist: continue
        d[method] = f.Get("Method_"+k).Get(method).Get("MVA_"+method + "_rejBvsS")
        d[method].SetLineColor(colors["BDT"])
        d[method].Draw("same")




# ----------------------------------------------------------

#hgl = TH1F("HGL","HGL",100,0.,1.)
#glold = TH1F("GLold","GLold",100,0.,1.)

## GLold = NewKarlen(s,b ,["DOCA","lessIPSmu","Bip","Blife_ps","mu1iso5","mu2iso5"])
## s2.desagrupate()
## b2.desagrupate()
## GLold(s2,"GLold")
## GLold(b2,"GLold")

## for i in range(50):
##     x = 0.02*i
##     cut = Cut("GLoldsb.>"+str(x))
    
##     dumis = cut(s2)
##     dumib = cut(b2)
##     dumis.desagrupate()
##     dumib.desagrupate()
##     glold.Fill(len(dumis)*1./Ns, 1.-len(dumib)*1./Nb)

## s1b = channelData( "~/scratch0/NTuples/bs_sm_train",name2 = "Bs2MuMu",labels = ["evt"] + variables)
## s2b = channelData( "~/scratch0/NTuples/bs_sm_test",name2 = "Bs2MuMu",labels = ["evt"] + variables)

## GLsm = NewKarlen(s1b, b,variables)
## GL(s2b,"GLmva")
## GLsm(s2b,"GLsm")
## GLsm(b2,"GLsm")


## gl0= TH1F("GL0","GL0",100,0.,1.)
## gl1= TH1F("GL1","GL1",100,0.,1.)

## b2.desagrupate()
## Nb = len(b2)
## Ns = len(s2b)
## for i in range(50):
##     x = 0.02*i
##     cut = Cut("GLmvasb.>"+str(x))
    
##     dumis = cut(s2b)
##     dumib = cut(b2)
##     dumis.desagrupate()
##     dumib.desagrupate()
##     print len(dumib)
##     gl0.Fill(len(dumis)*1./Ns, 1.-len(dumib)*1./Nb)
##     cut = Cut("GLsmsb.>"+str(x))
    
##     dumis = cut(s2b)
##     dumib = cut(b2)
##     print len(dumib)
##     dumis.desagrupate()
##     dumib.desagrupate()
##     gl1.Fill(len(dumis)*1./Ns, 1.-len(dumib)*1./Nb)

#outputFile.Close()
colorsB = {}
#from ROOT import *
colorsB["BDTD"] = kGreen
colorsB["BDT"] = kRed
colorsB["BDTG"] = kBlue


def comparefiles(f1name,f2name):
    f1 = TFile(f1name)
    f2 = TFile(f2name)
    d, d2 = {}, {}
    c = TCanvas()
    k = "BDT"
    i = 1
    for method in methods[k]:
            if method not in mlist: continue
            d[method] = f1.Get("Method_"+k).Get(method).Get("MVA_"+method + "_rejBvsS")
            d[method].SetLineColor(colorsB[method])
            if i :
                d[method].Draw()
                i = 0
            else: d[method].Draw("same")
            d2[method] = f2.Get("Method_"+k).Get(method).Get("MVA_"+method + "_rejBvsS")
            d2[method].SetLineColor(colorsB[method])
            d2[method].SetLineStyle(kDashed)
            d2[method].Draw("same")
    return d, d2, c
            
        
