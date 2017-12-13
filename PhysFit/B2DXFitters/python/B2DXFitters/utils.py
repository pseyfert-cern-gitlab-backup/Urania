"""
@file utils.py

@author Manuel Schiller <Manuel.Schiller@cern.ch>
@date 2015-05-24

@brief various little utilities
"""

def setConstantIfSoConfigured(config, obj, recache = None):
    """
    sets the desired parameters constant

    arguments:
    config --  a configuration which contains an entry 'constParams'; this
               entry contains a list of strings or regular expressions which
               should be set constant
    obj --     object on which the matching terms should be set constant; this
               is typically the top level pdf; setConstantIfSoConfigured
               recurses through the tree of RooFit objects rooted at obj, and
               finds the relevant nodes to set constant
    recache -- optional argument normally not given, default value is the
               None; if you call setConstantIfSoConfigured many times with the
               same config dictionary, you can supply your own empty dictionary
               here on the first call which will be used to store the compiled
               forms of the regular expressions used, so you can avoid their
               recompilation during subsequent calls
    
    Example: to set all asymmetries (those containing "Asym" in the RooFit
    object name) and the D parameter ('Bs2DsK_D') constant, you would use:
    @code
    configDict = { 'constParams': [ '.*Asym.*', 'Bs2DsK_D' ] }
    setConstantIfSoConfigured(configDict, mypdf)
    @endcode
    """
    from ROOT import RooAbsArg, RooRealVar, RooConstVar, RooArgSet
    if None == recache:
        recache = {}
        import re
        for rexp in config['constParams']:
            recache[rexp] = re.compile(rexp)
    if obj.InheritsFrom(RooRealVar.Class()):
        if obj.isConstant(): pass
        # set desired RooRealVar-derived objects to const
        for rexp in recache:
            if recache[rexp].match(obj.GetName()):
                obj.setConstant(True)
                break
    elif obj.InheritsFrom(RooConstVar.Class()):
        # ignore RooConstVar instances - these are constant anyway
        pass
    elif obj.InheritsFrom(RooAbsArg.Class()):
        # for everything else, descend hierarchy of RooFit objects to find
        # RooRealVars which might need to be set to constant
        v = RooArgSet()
        obj.treeNodeServerList(v)
        v.remove(obj)
        it = v.fwdIterator()
        while True:
            o = it.next()
            if None == o: break
            setConstantIfSoConfigured(config, o, recache)
    else:
        # ignore everything else
        pass

def randomiseParameters(config, obj, seed, debug, dict = {}):
    """
    re-assign values to parameters taking them
    from a uniform distribution having boundaries equal to
    the parameters boundaries.
    It returns a dictionary containing of the form:
    @code
    {parameter name : value before randomisation}
    @endcode
    This is useful for pulls distributions on toys if the generation
    value is the initial value in the fit (one doesn't want to loose it...)
    This dictionary can then be given as input to the
    FitResultGrabberUtils.CreatePullTree function.
    
    Typical use-case: randomize initial guess on floating
    parameter in a fit to check stability on toys.

    config -- configuration file having the following structure:
    @code
    config['randomiseParams'] = {'parName' : {'min': min, 'max': max}}
    @endcode
    where min and max are the boundaries of the uniform distribution
    used for the generation.
    Regular expressions for parName are allowed.
    obj -- the parent structure (e.g. a RooAbsPdf)
    seed -- the seed used for the random generation
    debug -- if true, print out some information
    dict -- the returned dictionary with parameter name and initial value
    """

    from ROOT import RooAbsArg, RooRealVar, RooConstVar, RooArgSet, TRandom3

    if obj.InheritsFrom(RooRealVar.Class()):
        if obj.isConstant():
            pass
        r = TRandom3()
        r.SetSeed(seed)
        for var in config['randomiseParams'].iterkeys():
            if var == obj.GetName() and var not in dict.keys():
                dict[obj.GetName()] = {}
                dict[obj.GetName()] = obj.getVal()
                val = r.Uniform(config['randomiseParams'][var]['min'], config['randomiseParams'][var]['max'])
                if debug:
                    print "B2DXFitters.utils.randomiseParameters(..) => Parameter "+obj.GetName()
                    print "...Initial guess "+str(obj.getVal())
                    print "...New guess "+str(val)
                    obj.setVal( val )
                break
    elif obj.InheritsFrom(RooConstVar.Class()):
        # ignore RooConstVar instances - these are constant anyway
        pass
    elif obj.InheritsFrom(RooAbsArg.Class()):
        # for everything else, descend hierarchy of RooFit objects to find
        # RooRealVars which might need to be set to constant
        v = RooArgSet()
        obj.treeNodeServerList(v)
        v.remove(obj)
        it = v.fwdIterator()
        while True:
            o = it.next()
            if None == o:
                break
            else:
                # randomise desired RooRealVar-derived objects
                randomiseParameters(config, o, seed, debug, dict)
    else:
        # ignore everything else
        pass


def printPDFTermsOnDataSet(dataset, terms = []):
    """
    print the values of various terms in a pdf for each entry in a data set

    dataset --  data set for which to print terms
    terms --    python list of RooFit objects whose values should be printed
                for each entry in the data set

    This routine is mostly useful to debug cases where something in the PDF
    calculation goes wrong (inside user C++ code, or because of invalid
    entries in the data sample).
    """
    import ROOT
    print 72 * '#'
    print 'DEBUG: DUMPING TERMS FOR EACH ENTRY IN DATASET'
    print 72 * '#'
    vlist = [ v.clone(v.GetName()) for v in terms ]
    for v in vlist:
        ROOT.SetOwnership(v, True)
        v.attachDataSet(dataset)
    tmpvlist = {}
    for v in vlist: tmpvlist[v.GetName()] = v
    vlist = tmpvlist
    del tmpvlist
    notchanged = False
    while not notchanged:
        notchanged = True
        for k in dict(vlist):
            vs = vlist[k].getVariables()
            ROOT.SetOwnership(vs, True)
            it = vs.fwdIterator()
            while True:
                obj = it.next()
                if None == obj: break
                if obj.GetName() in vlist: continue
                notchanged = False
                vlist[obj.GetName()] = obj
            vs = vlist[k].getComponents()
            ROOT.SetOwnership(vs, True)
            it = vs.fwdIterator()
            while True:
                obj = it.next()
                if None == obj: break
                if obj.GetName() in vlist: continue
                notchanged = False
                vlist[obj.GetName()] = obj
        if not notchanged: break
    obs = dataset.get()
    obsdict = { }
    it = obs.fwdIterator()
    while True:
        obj = it.next()
        if None == obj: break
        obsdict[obj.GetName()] = obj
    for i in range(0, dataset.numEntries()):
        dataset.get(i)
        if dataset.isWeighted():
            s = 'DEBUG: WEIGHT %g OBSERVABLES:' % dataset.weight()
        else:
            s = 'DEBUG: OBSERVABLES:'

        for k in obsdict:
            s = ('%s %s = %g' % (s, k, obsdict[k].getVal()) if
                    obsdict[k].InheritsFrom('RooAbsReal') else
                    '%s %s = %d' % (s, k, obsdict[k].getIndex()))
        print s
        vals = {}
        for k in vlist:
            vals[k] = (vlist[k].getValV(obs) if
                    vlist[k].InheritsFrom('RooAbsReal') else vlist[k].getIndex())
        for k in sorted(vals.keys()):
            if k in obsdict: continue
            print 'DEBUG:    ===> %s = %g' % (k, vals[k])
    print 72 * '#'
    return None

def updateConfigDict(configDict, updateDict, allowOnlyKnownKeys = True):
    """
    updates a configuration dictionary with contents of a second dictionary

    configDict          -- config dictionary to update
    updateDict          -- dictionary with updates
    allowOnlyKnownKeys  -- if True, new keys in updateDict must already exist
                           in configDict for the update to succeed; this is a
                           primitive form of protection against typos in config
                           files
                           if False, any update is allowed (to allow quick and
                           dirty hacks that don't mention every possible key in
                           the initial dictionary

    returns the updated dictionary
    """
    for k in updateDict.keys():
        if allowOnlyKnownKeys and k not in configDict:
            raise KeyError(('Configuration dictionary: unknown '
                'key %s, aborting.') % k)
    configDict.update(updateDict)
    return configDict

def configDictFromString(s, where = 'unknown location'):
    """
    parses a string of python code, extracting a dictionary from it

    s       -- string to interpret as python
    where   -- origin of string (file, name of environment variable, ...)
               for error reporting

    returns dictionary
    """
    d = eval(compile(s, where, 'eval'))
    if dict != type(d):
        raise TypeError(('configuration from %s does not evaluate '
            'to dictionary') % where)
    return d

def configDictFromFile(name):
    """
    read a python dictionary from a config file

    name -- file name

    returns config dictionary
    """
    lines = file(name, 'r').readlines()
    return configDictFromString(''.join(lines), name)

def PytoTreeLeaves(type):
        """
        convert python datatype to TTree ROOT datatype
        """

        typecode = None
        if type == 'h':
            typecode = 'S'
        elif type == 'i':
            typecode = 'I'
        elif type == 'f':
            typecode = 'F'
        elif type == 'd':
            typecode = 'D'
        else:
            print "utils.PytoTreeLeaves(...) ==> ERROR: Python typecode " + type + " is not handled"
            exit(-1)
            
        return typecode


def TreeLeavesToPy(type):
        """
        convert TTree ROOT datatype to python datatype
        """
        
        typecode = None
        if type == 'S':
            typecode = 'h'
        elif type == 'I':
            typecode = 'i'
        elif type == 'F':
            typecode = 'f'
        elif type == 'D':
            typecode = 'd'
        else:
            print "utils.TreeLeavesToPy(...) ==> ERROR: TTree type " + type + " is not handled"
            exit(0)
            
        return typecode

def SymmetrizeTriangularMatrix(matrix):
    """
    Create a symmetric matrix out of a triangular matrix.
    It is assumed that the upper-right part of the matrix is given as input.
    If a full n X n matrix is given, the lower-left triangle is overwritten to force symmetry
    """

    import copy
    
    print "utils.SymmetrizeTriangularMatrix(...) ==> Start creating symmetric matrix"

    newmatrix = copy.deepcopy( matrix )
    
    n = len(matrix)
    if n != len(matrix[0]):
        raise ValueError("utils.SymmetrizeTriangularMatrix(...) ==> Numbers of columns and rows mismatch")

    for irow in xrange(1, n): #row 0 is already filled
        for icol in xrange(irow-1, -1, -1):
            newmatrix[irow] = [ newmatrix[icol][irow] ] + newmatrix[irow]

    print "utils.SymmetrizeTriangularMatrix(...) ==> New symmetric matrix"
    print newmatrix
    
    return newmatrix

def BuildCovMatFromCorrMat(n, errors, correlation, regularise = True):
    """
    Build multivariate gaussian starting from errors and correlation matrix.
    If regularize=True, a correction is applied if the matrix is nearly singular.
    Returns a TMatrix ROOT object
    """

    from math import sqrt
    from WS import WS as WS
    from ROOT import ( RooConstVar, RooArgList, RooArgSet, TMatrixDSym,
                       RooMultiVarGaussian, TDecompChol )

    cov = TMatrixDSym(n)
    if len(errors) != n:
        raise ValueError('utils.BuildCovMatFromCorrMat(...) ==> Error list length does not match that of parameter name list')
    for i in xrange(0, n):
        if errors[i] < 0.:
            raise ValueError('utils.BuildCovMatFromCorrMat(...) ==> Errors must be positive')
        cov[i][i] = errors[i] * errors[i]
    correl = SymmetrizeTriangularMatrix(correlation)
    for i in xrange(0, n):
        if abs(correl[i][i] - 1.) > 1e-15:
            raise ValueError('utils.BuildCovMatFromCorrMat(...) ==> Correlation matrix has invalid element on diagonal')
        for j in xrange(0, i):
            # symmetrise by force
            el = 0.5 * (correl[i][j] + correl[j][i])
            # check if we're too far off
            if ((abs(el) < 1e-15 and abs(correl[i][j]-correl[j][i]) > 1e-15) or
                (abs(el) >= 1e-15 and abs(correl[i][j]-correl[j][i]) / el > 1e-15)):
                raise ValueError('utils.BuildCovMatFromCorrMat(...) ==> Correlation matrix not even approximately symmetric')
            if abs(el) > 1.:
                raise ValueError('utils.BuildCovMatFromCorrMat(...) ==> Off-diagonal elements too large to form valid correlation')
            # convert to covariance
            el = el * sqrt(cov[i][i] * cov[j][j])
            cov[i][j] = el
            cov[j][i] = el # ROOT's insanity requires this
    # verify we can invert covariance matrix with Cholesky decomposition
    # (this will catch negative and zero Eigenvalues)
    isposdef = False
    while not isposdef:
        decomp = TDecompChol(cov)
        isposdef = decomp.Decompose()
        if not isposdef:
            print 'utils.BuildCovMatFromCorrMat(...) ==> ERROR: Covariance matrix not positive definite!'
        from ROOT import TVectorD
        vv = TVectorD()
        cov.EigenVectors(vv)
        v = [ vv[i] for i in xrange(0, n) ]
        if regularise:
            if min(v) < 1e-16 or isposdef:
                if min(v) <= 0.:
                    print 'utils.BuildCovMatFromCorrMat(...) ==> WARNING: Attempting to fix non-positive-definiteness...'
                else:
                    print 'utils.BuildCovMatFromCorrMat(...) ==> WARNING: Covariance matrix very close to singular, trying to regularise...'
                print 'utils.BuildCovMatFromCorrMat(...) ==> DEBUG: Covariance matrix before fix:'
                cov.Print()
                print 'utils.BuildCovMatFromCorrMat(...) ==> DEBUG: Eigenvalue spectrum:'
                vv.Print()
                eps = 1.1 * abs(min(v))
                if eps < 1e-9: eps = 1e-9
                print 'utils.BuildCovMatFromCorrMat(...) ==> DEBUG: adding %e to diagonal' % eps
                #for i in xrange(0, n):
                #    cov[i][i] = cov[i][i] + eps
                print 'utils.BuildCovMatFromCorrMat(...) ==> DEBUG: Covariance matrix after fix:'
                cov.Print()
    return cov


def BuildMultivarGaussFromCorrMat(ws, name, paramnamelist, errors, correlation, regularise = True):
    """
    Build multivariate gaussian starting from errors and correlation matrix.
    If regularize=True, a correction is applied if the matrix is nearly singular.
    Returns both Gaussian and RooArgSet with parameters
    """

    print "utils.BuildMultivarGaussFromCorrMat(...) ==> Start building multivariate gaussian"
    
    from math import sqrt
    from WS import WS as WS
    from ROOT import ( RooConstVar, RooArgList, RooArgSet, TMatrixDSym,
                       RooMultiVarGaussian, TDecompChol )
    params = RooArgList()
    mus = RooArgList()
    for arg in paramnamelist:
        print arg
        param = ws.obj(arg)
        if param == None:
            ws.Print("v")
            raise ValueError('utils.BuildMultivarGaussFromCorrMat(...) ==> Parameter %s does not exist in workspace. Please check its content above' % arg)
        params.add(param)
        mus.add(WS(ws, RooConstVar('%s_mean' % arg, '%s_mean' % arg,
                                   param.getVal())))
    n = len(paramnamelist)
    cov = BuildCovMatFromCorrMat(n, errors, correlation, regularise)
    # all set up, construct final multivariate Gaussian
    mvg = WS(ws, RooMultiVarGaussian(name, name, params, mus, cov))
    # make sure we float all parameters given
    i = 0
    for arg in paramnamelist:
        param = ws.obj(arg)
        param.setConstant(False)
        param.setError(sqrt(cov[i][i]))
        i = i + 1
    # cast RooArgList into RooArgSet
    parset = RooArgSet()
    for p in range(0, params.getSize()):
        parset.add( params[p] )
    # all done
    return mvg, parset


def EqualiseCategories(ws, data, configfile, name, debug = True):
    """
    Set the number of events for each category to the same number
    (by default, the less populated category).
    The config file needs to contains a dictionary 'equalCat' with
    a structure like the one in the following example:

    @code
    configdict['equalCat'] = { 'B2f'        :  'BacCharge==1 && TagDecTrue==1',
                               'Bbar2f'     :  'BacCharge==1 && TagDecTrue==-1',
                               'B2fbar'     :  'BacCharge==-1 && TagDecTrue==1',
                               'Bbar2fbar'  :  'BacCharge==-1 && TagDecTrue==-1'
                               }
    @endcode
    """

    import ROOT
    from ROOT import (TTree, RooDataSet, RooFit)
    import B2DXFitters
    from B2DXFitters.WS import WS as WS
    import math

    if debug:
        print "utils.EqualiseCategories(...)=> Equalising categories with different number of entries in input sample"

    yields = {}
    min = float("inf")
    for cat in configfile['equalCat'].iterkeys():
        yields[cat] = {}
        yields[cat]["Entries"] = {}
        yields[cat]["Entries"] = data.tree().GetEntries( configfile['equalCat'][cat] )
        yields[cat]["Cut"] = configfile['equalCat'][cat].replace("_idx","")
        if debug:
            print "utils.EqualiseCategories(...)=> Category "+str(cat)+": "+str(yields[cat])
        if yields[cat]["Entries"] < min:
            min = yields[cat]["Entries"]
            mincat = cat

    if debug:
        print "utils.EqualiseCategories(...)=> Smallest categories: "+mincat+", entries "+str(min)

    dataList = []
    for cat in configfile['equalCat'].iterkeys():
        if cat == mincat:
            dataList.append( data.reduce(RooFit.Cut(yields[cat]["Cut"]),
                                         RooFit.Name(name+"_"+cat) ) )
        else:
            dataTemp = data.reduce(RooFit.Cut(yields[cat]["Cut"]),
                                   RooFit.Name(name+"_"+cat+"_temp") )
            dataList.append( dataTemp.reduce(RooFit.Name(name+"_"+cat),
                                             RooFit.EventRange(0,min)) )

    for d in range(1, dataList.__len__()):
        dataList[0].append( dataList[d] )

    OutputData = dataList[0]
    OutputData.SetName( name )

    if debug:
        print "utils.EqualiseCategories(...)=> Output dataset:"
        OutputData.Print("v")

    return WS(ws, OutputData)

def ModifyAsymmetry(ws, data, configfile, name, tolerance = 1e-09, debug = True):
    """
    Tune asymmetries between pairs of categories in input data.
    The config file needs to contains a dictionary 'modifyAsymm' with
    a structure like the one in the following example:

    @code
    configdict['modifyAsymm'] = { 'CabibboFavoured' : { 'Category1'   : 'TagDecTrue_idx==1 && BacCharge_idx==1',
                                                        'Category2'   : 'TagDecTrue_idx==-1 && BacCharge_idx==-1',
                                                        'Target'      : 0.0},
    'CabibboSuppressed' : { 'Category1'    : 'TagDecTrue_idx==1 && BacCharge_idx==-1',
                            'Category2'    : 'TagDecTrue_idx==-1 && BacCharge_idx==1',
                            'Target'       : 0.0}
    }
    @endcode

    The asymmetry is defined as asymm=(ncat1-ncat2)/(ncat1+ncat2)
    Take care of signs when defining the target asymmetries!!!

    The tolerance is the maximum allowed discrepancies between target and obtained
    asymmetries. The function iterates until the required tolerance is reached.
    The tolerance might be violated because of rounding effects when converting
    integer number of events into float asymmetries, but this case should
    be rare.

    WARNING: all the Categories across all the dictionary should be mutually
    exclusive. The functions aborts if overlapping events are found.

    If you want to compute your asymmetry, the following package may help:
    @code
    git clone ssh://git@gitlab.cern.ch:7999/vibattis/BDecayRates.git
    @endcode
    """

    import ROOT
    from ROOT import (TTree, RooDataSet, RooFit)
    import B2DXFitters
    from B2DXFitters.WS import WS as WS
    import math

    if debug:
        print "utils.ModifyAsymmetry(...)=> Modifying asymmetries in input sample"

    overlap=""
    count = 0
    for asymm in configfile["modifyAsymm"].iterkeys():
        for cut in configfile["modifyAsymm"][asymm].iterkeys():
            if "Category" in cut:
                if count == 0:
                    overlap = overlap + "("+configfile["modifyAsymm"][asymm][cut]+")"
                else:
                    overlap = overlap + " && " + "("+configfile["modifyAsymm"][asymm][cut]+")"
                count = count + 1
                
    if data.tree().GetEntries(overlap) > 0:
        print "utils.ModifyAsymmetry(...)=> ERROR: categories have shared events. Please check your 'modifyAsymm' dictionary"
        if debug:
            print "utils.ModifyAsymmetry(...)=> The current 'overlap' selection is :"+overlap 
        exit(-1)

    InputDataList = {}
    OutputDataList = []
    
    for asymm in configfile["modifyAsymm"].iterkeys():

        InputDataList[asymm] = {}
        InputDataList[asymm] = [data]
        done = False
        iter = 0

        while not done:
            
            if debug:
                print "utils.ModifyAsymmetry(...)=> Modifying "+asymm+", iteration "+str(iter)+", data "+str(InputDataList[asymm][-1].GetName())
            
            cat1 = configfile["modifyAsymm"][asymm]["Category1"]
            cat2 = configfile["modifyAsymm"][asymm]["Category2"]
            
            ccat1 = cat1.replace("_idx","")
            ccat2 = cat2.replace("_idx","")
            
            nCat1 = InputDataList[asymm][-1].tree().GetEntries(cat1)
            nCat2 = InputDataList[asymm][-1].tree().GetEntries(cat2)
            thisAsymm = (float(nCat1) - float(nCat2)) / (float(nCat1) + float(nCat2))
            targetAsymm = configfile["modifyAsymm"][asymm]["Target"]

            if debug:
                print "utils.ModifyAsymmetry(...)=> Category 1: "+ccat1+", entries: "+str(nCat1)
                print "utils.ModifyAsymmetry(...)=> Category 2: "+ccat2+", entries: "+str(nCat2)
                print "utils.ModifyAsymmetry(...)=> Current asymmetry: "+str(thisAsymm)
                print "utils.ModifyAsymmetry(...)=> Target asymmetry: "+str(targetAsymm)

            if thisAsymm > targetAsymm:
                #Reduce nCat1
                targetData = InputDataList[asymm][-1].reduce(RooFit.Cut(ccat2),
                                                             RooFit.Name("target_"+asymm+str(iter)))
                reducedData_temp = InputDataList[asymm][-1].reduce(RooFit.Cut(ccat1),
                                                                   RooFit.Name("target_"+asymm+"_temp"+str(iter)))
                reducedData = reducedData_temp.reduce(RooFit.Name("target_"+asymm+str(iter)),
                                                      RooFit.EventRange(0, int(float(nCat2)*(1.0+targetAsymm)/(1.0-targetAsymm)) ) )
                newAsymm = (float(reducedData.numEntries())-float(targetData.numEntries()))/(float(reducedData.numEntries())+float(targetData.numEntries()))
                if debug:
                    print "utils.ModifyAsymmetry(...)=> New Category 1 entries: "+str(reducedData.numEntries())
                    print "utils.ModifyAsymmetry(...)=> New Category 2 entries: "+str(targetData.numEntries())
                    print "utils.ModifyAsymmetry(...)=> New asymmetry: "+str(newAsymm)

            elif thisAsymm < targetAsymm:
                #Reduce nCat2
                targetData = InputDataList[asymm][-1].reduce(RooFit.Cut(ccat1),
                                                             RooFit.Name("target_"+asymm+str(iter)))
                reducedData_temp = InputDataList[asymm][-1].reduce(RooFit.Cut(ccat2),
                                                                   RooFit.Name("target_"+asymm+"_temp"+str(iter)))
                reducedData = reducedData_temp.reduce(RooFit.Name("target_"+asymm+str(iter)),
                                                      RooFit.EventRange(0, int(float(nCat1)*(1.0-targetAsymm)/(1.0+targetAsymm)) ) )
                newAsymm = (float(targetData.numEntries())-float(reducedData.numEntries()))/(float(targetData.numEntries())+float(reducedData.numEntries()))
                if debug:
                    print "utils.ModifyAsymmetry(...)=> New Category 1 entries: "+str(targetData.numEntries())
                    print "utils.ModifyAsymmetry(...)=> New Category 2 entries: "+str(reducedData.numEntries())
                    print "utils.ModifyAsymmetry(...)=> New asymmetry: "+str(newAsymm)

            else:
                if debug:
                    print "utils.ModifyAsymmetry(...)=> Target asymmetry == asymmetry in data for "+asymm+". Nothing to do."
                newAsymm = targetAsymm
                continue

            targetData.append(reducedData)
            targetData.SetName(name+"_"+asymm+"_fixed_"+str(iter))
            InputDataList[asymm].append(targetData)
            
            if math.fabs(newAsymm - configfile["modifyAsymm"][asymm]["Target"]) <= tolerance:
                done = True

            if debug:
                print "utils.ModifyAsymmetry(...)=> Total entries after asymmetry correction(s) at iteration "+str(iter)+": "+str(InputDataList[asymm][-1].numEntries())

            iter = iter + 1

        OutputDataList.append( InputDataList[asymm][-1] )
        OutputDataList[-1].SetName( name+"_"+asymm )

    OutputData = OutputDataList[0]
    for od in range(1,OutputDataList.__len__()):
        OutputData.append( OutputDataList[od] )

    OutputData.SetName(name)

    if debug:
        print "utils.ModifyAsymmetry(...)=> New dataset after asymmetry correction(s):"
        OutputData.Print("v")

    return WS(ws, OutputData)
