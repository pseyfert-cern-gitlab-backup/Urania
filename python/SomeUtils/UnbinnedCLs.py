from ROOT import *
from bisect import *
#from scipy import random as rnd
from Urania import *
recoverTree()
NCPU = 1
Toys = 100

class LimitCalculator:
    def __init__(self, signalVar, bkgVar, fitvars,model, N_bkg_exp, binned = False): ## eg: signalvar: BR, fitVars: mas & BDT
        """ 'signalVar' is the RooRealVar corresponding to the signal strength.
        It can either be the signal yield, the BR, xsection*BR, etc...
        If different from the signal yield, then the relation between both is
        given by the normalization factor (aka SES), which can be specified
        via the SetNormalizationFactor(float bla) method.
        'bkgVar' is the RooRealVar of the backround yield.

        'fitVars' is the RooArgSet of the fitting space axes
        (typically the invariant mass, or the invariant mass and a MVA category)

        'model' is the RooFit model

        'N_bkg_exp' is the number of expected  backround events.

        'binned' specifies wether the data -and therefore the pseudo-experiments
        is binned or unbinned.
        """
        self.signalVar = signalVar
        self.bkgVar = bkgVar
        self.fitvars = fitvars
        self.ResetDLLlists()
        self.model = model
        self.alpha = 1
        self.N_bkg_exp = N_bkg_exp 
        self.hesse = kFALSE
        self.minos = kFALSE
        self.Constraints = RooArgSet()
        self.constraints_list= []
        self.constraints_mpvs = []
        self.strategy = 1
        self.binned = binned
        self.fit_float_np = 1
        self.fit_float_b = 1
        self.fit_float_s = 1
        
        if binned: self.gen = self.model.generateBinned
        else: self.gen = self.model.generate 
        self.ns_vals = TH1F(signalVar.GetName()+ "_H", signalVar.GetName() + "_H", int(signalVar.getMax()-signalVar.getMin()), signalVar.getMin(), signalVar.getMax())
    def ResetDLLlists(self):
        """Empties all the values of the test-statistic storaged so far
        """
        self.testDLLs = []
        self.nullDLLs = []
    def SetNormalizationFactor(self, alpha):
        """Sets signal normalization factor (aka SES)
        """
        self.alpha = alpha
   
    def doExperimentClassic(self, signalStrength):
        """ Generates a null and a test experiment, and calculates Tevatron/LEP's test-statistic for both
        """
        nullExperiment = self.makeNullExperiment()
        testExperiment = self.makeTestExperiment(signalStrength)

        self.testDLLs.append(self.calcDLLClassic(testExperiment, signalStrength))
        self.nullDLLs.append(self.calcDLLClassic(nullExperiment, signalStrength))
        del nullExperiment
        del testExperiment
        
    def calcDLLClassic(self, dataSet, signalStrength):
        """Calculates LEP/Tevatron's test-statistic for the specified dataSet and value for signalStrength
        'dataSet' is expected to be a RooDataSet
        """
        NLLVar = self.model.createNLL(dataSet)
        self.resetBkgYield(setConstant=1)
        self.setConstraintsToMPV(setConstant = 1)
        self.signalVar.setVal(0)
        #self.signalVar.setConstant(kTRUE)
       
        nullNLL = NLLVar.getVal()
        self.signalVar.setVal(signalStrength)
        testNLL = NLLVar.getVal()
        DLL = testNLL - nullNLL
        del NLLVar
        return -DLL
    def SetConstraints(self, constraints):
        """ Tells the Limit calculator which are the priors of the nuisance
        parameters. They will be used in the generation of the pseudoexperiments
        and optionally in the test-statistic
        """
        self.Constraints = constraints
        self.constraints_arglist = RooArgList(constraints)
        for i in range(self.constraints_arglist.getSize()):
            const = self.constraints_arglist[i]
            self.constraints_list.append(const)
            self.constraints_mpvs.append(self.PriorMPV(const))
    def randomizeConstraints(self):
        """ sets the the nuisance parameters to randomly generated
        values, according to their prior densities
        """
        for constraint in self.constraints_list:
            RooArgList(constraint.getVariables())[0].setConstant(kFALSE)
            constraint.generateEvent(1)
           
    def makeTestExperiment(self, signalStrength):
        """ Generates a pseudo-experiment for a given signal strength.
        The signal strength is typically the number of signal events,
        but can differ if a normalization factor was set.
        """
        self.signalVar.setVal(signalStrength)
        self.randomizeConstraints()
        return self.gen(self.fitvars,RooFit.Extended())

    def makeNullExperiment(self):
        """ Generates a background-only pseudo-experiment
        """
        return self.makeTestExperiment(0)
    
    def plotNullExperiment(self):
        """ Generates a background-only pseudo-experiment
        and plots it
        """ 
        nullExperiment = self.makeNullExperiment()
        fr = RooArgList(self.fitvars)[0].frame()
        self.model.fitTo(nullExperiment, RooFit.ExternalConstraints(self.Constraints), RooFit.Strategy(self.strategy),
                         RooFit.Hesse(self.hesse),RooFit.Minos(self.minos), RooFit.NumCPU(NCPU))
        nullExperiment.plotOn(fr)
        self.model.plotOn(fr)
        fr.Draw()
        return fr, nullExperiment
    
    def plotTestExperiment(self, signalStrength):
        """ Generates a pseudo-experiment for a given signal strength.
        The signal strength is typically the number of signal events,
        but can differ if a normalization factor was set, and then plots it.
        """
        testExperiment = self.makeTestExperiment(signalStrength)
        fr = RooArgList(self.fitvars)[0].frame()
        self.model.fitTo(testExperiment, RooFit.ExternalConstraints(self.Constraints) , RooFit.Strategy(self.strategy),
                         RooFit.Hesse(self.hesse),RooFit.Minos(self.minos),RooFit.NumCPU(NCPU) )
        testExperiment.plotOn(fr)
        self.model.plotOn(fr)
        fr.Draw()
        return fr, testExperiment
        
    def doExperiment(self, signalStrength):
        """ Generates a null and a test experiment, and calculates
        the custom/default fit-based test-statistic for both
        """
        nullExperiment = self.makeNullExperiment()
        testExperiment = self.makeTestExperiment(signalStrength)

        self.nullDLLs.append(self.calcDLL(nullExperiment, signalStrength))
        self.testDLLs.append(self.calcDLL(testExperiment, signalStrength))
        self.ns_vals.Fill(self.signalVar.getVal())
        del nullExperiment
        del testExperiment
        
    def calcDLL(self, dataSet, signalStrength):
        """Calculates the default fit-based test-statistic for the
        specified dataSet and value for signalStrength
        'dataSet' is expected to be a RooDataSet
        """
        NLLVar = self.model.createNLL(dataSet)
       
        self.setConstraintsToMPV(setConstant = not self.fit_float_np)
        self.resetBkgYield(setConstant = not self.fit_float_b)
        self.signalVar.setVal(0)
        self.signalVar.setConstant(kTRUE)
        self.model.fitTo(dataSet, RooFit.ExternalConstraints(self.Constraints), RooFit.Strategy(self.strategy),
                         RooFit.Hesse(self.hesse),RooFit.Minos(self.minos), RooFit.NumCPU(NCPU)) 
        nullNLL = NLLVar.getVal()
        self.setConstraintsToMPV(setConstant = not self.fit_float_np)
        self.resetBkgYield(setConstant = not self.fit_float_b)
        self.signalVar.setVal(signalStrength)
        self.signalVar.setConstant(not self.fit_float_s)
        self.model.fitTo(dataSet, RooFit.ExternalConstraints(self.Constraints), RooFit.Strategy(self.strategy),
                         RooFit.Hesse(self.hesse),RooFit.Minos(self.minos), RooFit.NumCPU(NCPU))
        testNLL = NLLVar.getVal()
        DLL = testNLL - nullNLL
        del NLLVar
        return -DLL
    def runToys(self,NToys, signalStrength):
        """ Runs (NToys) signal and background pseudo-experiments,
        and storages the values of their fit-based test-statistic
        """
        self.ResetDLLlists()
        for i in range(NToys): self.doExperiment(signalStrength)
        
    def runToysClassic(self,NToys,signalStrength):
        """ Runs (NToys) signal and background pseudo-experiments,
        and storages the values of their Tevatron/LEP test-statistic
        """
        self.ResetDLLlists()
        for i in range(NToys): self.doExperimentClassic(signalStrength)
                
    def ConfidenceLevels(self, data, signalStrength, NToys = Toys):
        """ Runs (NToys) signal and background pseudo-experiments,
        storages the values of their fit-based test-statistic, and returns
        the CLs, CLb and CLsb of the given signalStrength.
        'data' is expected to be a RooDataSet
        """
        self.runToys(NToys,signalStrength)
        observedDLL = self.calcDLL(data, signalStrength)
        self.testDLLs.sort()
        self.nullDLLs.sort()

        clb  = float(bisect(self.nullDLLs,observedDLL)) / len(self.nullDLLs)
        clsb = float(bisect(self.testDLLs,observedDLL)) / len(self.testDLLs)
        cls  = clsb/clb

        return cls, clb, clsb

    def ConfidenceLevelsClassic(self, data,signalStrength, NToys = Toys):
        """ Runs (NToys) signal and background pseudo-experiments,
        storages the values of their Tevatron/LEP test-statistic, and returns
        the CLs, CLb and CLsb of the given signalStrength
        'data' is expected to be a RooDataSet
        """
        self.runToysClassic(NToys,signalStrength)
        observedDLL = self.calcDLLClassic(data,signalStrength)
        self.testDLLs.sort()
        self.nullDLLs.sort()

        clb  = float(bisect(self.nullDLLs,observedDLL)) / len(self.nullDLLs)
        clsb = float(bisect(self.testDLLs,observedDLL)) / len(self.testDLLs)
        cls  = clsb/clb
        return cls, clb, clsb

    def resetBkgYield(self, setConstant = 0):
        """ Resets the background expectation to its most probable value (mpv).
        'setConstant' specifies whether to make it constant or not after
        it has been set to the mpv.
        """
        self.bkgVar.setVal(self.N_bkg_exp)
        self.bkgVar.setConstant(setConstant)
        
    def setConstraintsToMPV(self, setConstant=0):
        """ Sets all the nusiance parameters to their most probable
        values (mpv's) according to the given priors.
        setConstant' specifies whether to make them
        constant or not after they have been set to the mpv's.
        """
        for i in range(len(self.constraints_list)):
            constraint = self.constraints_list[i]
            myvar = RooArgList(constraint.getVariables())[0]
            myvar.setVal(self.constraints_mpvs[i])
            myvar.setConstant(setConstant)
            
    def PriorMPV(self, constraint):
        """ returns the most probable value of a nuisance
        parameter according 'constraint' prior density.  
        """
        myvar = RooArgList(constraint.getVariables())[0]
        myvar_0 = myvar.getVal()
        l = []
        ssize = (myvar.getMax() - myvar.getMin()) *1./ 1000
        for i in range(1001):
            x= myvar.getMin() + i*ssize
            myvar.setVal(x)
            l.append([constraint.getVal(), x])
        l.sort()
        myvar.setVal(myvar_0)
        return l[-1][1]
