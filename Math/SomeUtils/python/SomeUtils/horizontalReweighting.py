from ROOT import *
from SomeUtils.GLBasic import *

# path in Erasmus
# /cvmfs/lhcb.cern.ch/lib/lhcb/ERASMUS/ERASMUS_v9r0/InstallArea/x86_64-slc5-gcc46-opt/python/SomeUtils


def getTruthMachedEvents(t,v):
    mcL = []
    for ev in t:
        if abs(getattr(ev,'B_s0_TRUEID'))==531:
            mcL.append(getattr(ev,v))
    return mcL

def getAll(t,v):
    mcL = []
    for ev in t: mcL.append(getattr(ev,v))
    return mcL

def MimicWeightedDistribution(t,var,wPref,Nbins=100):
    """ Generates a python list that mimics an sweighted
    histogram. t is the TTree, var the variable name and
    wPref the name of the weighting variable in the NTuple"""
    
    #List of new mimiced distribution
    newDistribution = []

    #Create Binning
    varRange = [t.GetMinimum(var), t.GetMaximum(var)]
    binWidth = float( varRange[1]-varRange[0] )/ float(Nbins)

    # Calculate Bin boundaries
    bounds=[]
    low_bin  = [varRange[0]]
    high_bin = [varRange[0] + binWidth]
    bounds   = [ [varRange[0], varRange[0]+binWidth] ]
    for b in range(Nbins-1):
        low_bin  = bounds[b][0] + binWidth
        high_bin = bounds[b][1] + binWidth
        bounds.append([low_bin,high_bin])

    #Get sum of weights in each bin (not the most elegant way to do that)
    c3 = TCanvas('el','el')
    t.Draw(var + '>>TEMP(' +str(Nbins)+ ',' +str(varRange[0])+ ',' +str(varRange[1])+ ')', wPref)
    from ROOT import gPad
    TEMP = gPad.GetPrimitive('TEMP')
    
    binning={}
    for b in bounds:
        n_i = TEMP.GetBinContent(bounds.index(b)+1)
        binning.update( {'bin'+str(bounds.index(b)+1) : {'bounds':b , 'yield':int(round(n_i))}} )

    from ROOT import TRandom
    rdm = TRandom()
    
    for b in binning.keys():
        for evnt in xrange(binning[b]['yield']):
            newDistribution.append( rdm.Uniform(binning[b]['bounds'][0], binning[b]['bounds'][1]) )

    return newDistribution

def getMachedDistribution(Vref, Vout, Nbins = 500):
        
    Uref = UniFunc(Vref, nbinsmax = Nbins)
    Uout = UniFunc(Vout, nbinsmax = Nbins)    

    l = []
    for entry in Vout:
        Vout_i_reweighted = Uref.inverse(Uout(entry))
        l.append(Vout_i_reweighted)
    return l

def MakeListsOutOfBranches(tree,whichVar):
    print '\nMaking lists of branches to be copied to output tree\n'
    for var in whichVar:
        if var in tree.GetListOfBranches():pass
        else: print 'Ignoring', var, '. Reason: not found in list of branches' 

    outLists = dict( (var,[]) for var in whichVar )
    for entry in tree:
        for v in whichVar:
            outLists[v].append(getattr(entry,v))
    return outLists

def FillBranches(t, varList, newDistr,renameBranches={} ):
    #Make 1-entry arrays to represent the fill variables
    from array import array  
    addDict = {}
    for v in varList: addDict.update( {v:array('f',[0])} )

    #Make Branches and assign the fill variables
    branchDict = {}
    for v in varList:
        if v in renameBranches.keys():
            branchDict.update( {renameBranches[v]:t.Branch(v, addDict[v], renameBranches[v]+'/F')} )
            print 'Renaming Branch',v ,'  to  ', renameBranches[v] 
        else: branchDict.update( {v:t.Branch(v, addDict[v], v+'/F')} )

    #Fill Branches and write tree
    entries = len(newDistr[newDistr.keys()[0]])
    for ind in xrange(entries):
        for v in varList:
            if ind==0:
                if v not in renameBranches.keys():print 'Filling Branch: ', v
                else: print 'Filling Branch: ', renameBranches[v]
            addDict[v][0] = newDistr[v][ind]
        t.Fill()
    t.Write()



def getSumWeights(t,pref):
    sum=0
    for e in t:sum+=getattr(e,pref)
    return sum

def reduceDataSize(distr,reduceTo=.2):
    from ROOT import TRandom
    rdm = TRandom()
    initSize = len(distr[distr.keys()[0]])
    while len(distr[distr.keys()[0]]) >= reduceTo*initSize:
        removeEntry = int(rdm.Uniform(0,len(distr[distr.keys()[0]] ) ))
        for v in distr.keys():
            distr[v].pop( removeEntry )


class HorizontalReweighter:

    def __init__(self, tin, target, varList, win = 0, wout = 0):

        self.InputTree = tin
        self.TargetTree = target
        self.vars = varlist
        self.weights_in = win
        self.weights_target = wout
        if weights_in : InDistr = dict( (v,MimicWeightedDistribution(tin,v,weights_in)) for v in varList )
        else: InDistr = dict( (v,getAll(tin,v)) for v in varList )
        if weights_target: RefDistr = dict( (v,MimicWeightedDistribution(target,v,weights_target)) for v in varList )
        else: RefDistr = dict( (v,getAll(target,v)) for v in varList )
        self.defineTransformations()
    

    def defineTransformations():
        self.Uin = dict(( v, Unifunc(InDistr[v])) for v in self.vars)
        self.Utarget = dict(( v, Unifunc(RefDistr[v])) for v in self.vars)

    def DoEntry(self,t):
        return dict( (v, self.Utarget[v].inverse( self.Uin[v](getattr(t,v)))) for v in self.vars)
    
    def __call__(self,t, outputfilename):
        v0 = t.GetListOfBranches()
        varList = v0 + self.vars
        OutDstr =  MakeListsOutOfBranches(tIn,v0) 
        OutDistr_ = dict( (v,getMachedDistribution(self.RefDistr[v],self.InpDistr[v],Nbins=500)  )for v in self.vars)
        for key in OutDistr_.keys(): OutDistr[key] = OutDistr_[key]
        outFile = TFile(outputfilename,'recreate')
        outTree = TTree('T','Reweight')
        FillBranches(outTree, varList, OutDistr)
        outFile.Close()


        #from array import array  
        #addDict = {}
        #for v in varList: addDict.update( {v:array('f',[0])} )
        
        
