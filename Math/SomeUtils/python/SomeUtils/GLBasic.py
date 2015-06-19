#! /usr/bin/python

#-------------------------------------------------------------------
#
#  This module performs a Multi Variate Analysis that transforms the initial
# variables into a set of new variables which distributions are gaussian and
# they are uncorrelated, in 1st order.
#
#  requires: scipy (scientific python)
#
#  version: v2r0
#  authors: J.A Hernando (CERN,USC), D. Martinez (USC) 
#               Santiago de Compostela, December 5 2007
#-------------------------------------------------------------------
import sys
#sys.path.append('
#import scipy.special
from math import sqrt
import numpy, os
import cPickle

if not "matrixmultiply" in dir(numpy):
    numpy.matrixmultiply = numpy.dot

f = file(os.environ["SOMEUTILSROOT"] + "/operators/toGauss_2008","r")
sq2 = sqrt(2)
toGauss_0 = cPickle.load(f)

# number of minimum entries per uniform bin
NMIN = 10
# number of maximun bins for the uniform operator
NBINSMAX = 500

import scipy.special
erfi = scipy.special.erfinv  ### SEEMS TO BE TOO SLOW

def toGauss(x):
    if x>0.99 or x < 0.01: return sq2*erfi(2*x-1)
    else: return toGauss_0(x)

def mean(var):
    total = 0
    for x in var: total += x
    return total/(1.*len(var))

def mod2(var):
    total = 0
    for x in var: total += x*x
    return total/(1.*nsize)

def chi2_old(inputmatrix):
    """ compute the chi2 of a list of list of variables
    """
    nvars = len(inputmatrix)
    nsize = len(inputmatrix[0])
    chi = []
    for i in range(nsize):
	ch = 0.
	for j in range(nvars):
	    ch = ch + inputmatrix[j][i]*inputmatrix[j][i] # No restas aqui el valor medio ?
	chi.append(ch)
    return chi
def chi2(entry):
    out = 0.
    for x in entry: out += x*x
    return out
    

def LinearCorrelationMatrix(vars):
    """ compute the correlation matrix
    C[i][j] = E[(xi-E[xi])*(xj-E[xj])]
    @vars: list of list of variables
    """
    print "computing Linear Correlation matrix..."
    nvars = len(vars)
    nsize  = len(vars[0])
    vmean = map(mean,vars)
    def cov(i,j):
	cij = 0
	for k in range(nsize):
	    cij += (vars[i][k]-vmean[i])*(vars[j][k]-vmean[j])
	return cij/(1.*nsize)  ## dividir al final? 
    cc = nvars*[nvars*[0.]]
    CC = numpy.mat(cc)
    for i in range(nvars):
        for j in range(i,nvars): CC[i,j] = cov(i,j)
    for i in range(nvars):
        for j in range(0,i):
            CC[i,j]=CC[j,i]
    eL,eV = numpy.linalg.eig(CC)
    R = numpy.mat(eV)
    Ri = numpy.linalg.pinv(R)
    print " C ",CC
    print " R ",R
    print " Eigenvalues ",eL
    # print " RiCR",Ri*(CC*R)
    return CC,Ri,eL

        
class UniFunc:
    """ Uniform Function: A function that transform a variable into a flat distribution
    """

    def __init__(self,var,nbinsmax = NBINSMAX):
	""" Construct a Uniform Function
	A Uniforn function is a function which transformed values 
	have a flat distribution between [0.,1.]
        @var : a list with the initial values
        @nbinsmax: the maximum number of points in the numerical transformation
	"""        
	xlist = map(float,var)
        xlist.sort()
	n = len(xlist)
	nbins0 = int((1.*n)/NMIN)
	self.size = min(nbins0,nbinsmax)
	self.xaxis = self.size*[0.]
	self.yaxis = self.size*[0.]
        
        supmin = .5/len(var)
        cte = (1.-2*supmin)/(self.size-1)
	for i in range(self.size):
	    self.yaxis[i]=supmin + i*cte  # Pq no usas append ?
	    jevt = int(i*n*cte)  # Pq no i*(n-1)*cte y te ahorras el min() ?
	    jevt = min(jevt,n-1)
	    self.xaxis[i]=xlist[jevt]

    def value(self,x,xlist,ylist):
        """ returns the y value associated to x between the point in the xlist and y list
        """
	def bin(x,xlist):
	    """ returns the bin index in which boundaries the value of x lies in the xlist
	    """
	    x = float(x)
	    if (x<=xlist[0]): return 0,0
	    if (x>=xlist[-1]): return self.size-1,self.size-1 
	    for i in range(self.size):
		if x < xlist[i]:
		    return max(0,i-1),min(self.size-1,i)
	#print x
	x = float(x)
	#print x
	ww = bin(x,xlist)
	#print ww
	if not "__len__" in dir(ww):
		print "Crazy, " ,x, xlist[0], xlist[-1]

	i,j = ww
	x0 = xlist[i]
	y0 = ylist[i] 
	dx = xlist[j]-x0
	dy = ylist[j]-y0
	dydx = 0.
	if (i != j): dydx = dy/dx # ???????
	y = y0+dydx*(x-x0)
	return y

    def __call__(self,x):
	""" returns the transformed value of x 
	"""
	return self.value(x,self.xaxis,self.yaxis)

    def inverse(self,y):
	""" returns the inverse transformation value. 
	From a unifrom distribution to the original one
	"""
	return self.value(y,self.yaxis,self.xaxis)
   
class UnCorrGaussOperator:
    """ UnCorrGaussOperator is an operator that operates in n variables 
    and which transformed variables have a gaussian distribution, uncorrelated in 1st order.
    """
    def __init__(self,xmultivars,
                 saveFinalVariables = True,
                 saveIntermediateVariables = False):
        """ construct the operator to transtorm the variables into a list
        of gaussian distributed variables, uncorrelated in fist order
        @xmultivars : a list of list of quantities,
        i.e. consider a sample of 3dimensional ppoints, xmultivars = [x,y,z], where
        x,y and z are lists of the same dimensions with the x,yz valures
	@saveFinalVariables: final gaussian variables will be saved in the object
	@saveIntermediateVariables: intermediate variables will be sabed in the object
        """
        x0 = xmultivars
        if isinstance(xmultivars,dict): x0 = xmultivars.values()
        # create a unifun function of Gaussian to Uniform -> Gaussian transformations
	#gaussianNumbers = []
        n0 = len(xmultivars[0])
	#for i in range(10000): gaussianNumbers.append(gauss(0.,1.)) ####OJO

	def _UFS(mvars):
            """ create a list of uniform functions """
	    _ufs = []
	    for var in mvars: _ufs.append( UniFunc(var))
	    return _ufs
        # construct the uniform functions from the initial variables x0
	self.U1FS = _UFS(x0)
        
        # transform the initial variables into gaussian ones
        rows = len(x0[0])
        columns = len(x0)
        x1 = []
        for i in range(columns):
            
            x1.append(map(toGauss,map(self.U1FS[i],x0[i])))
            
                              
        x0 = None #!!
        
        # decorrelate the gaussian distribution in 1st order
        # compute the density matrix and its eigenvalues
	self.C,self.R,self.eL = LinearCorrelationMatrix(x1)
        
        # project the variables into the new axis
	x2 = self.rotate(self.R,x1)
        #if (saveIntermediateVariables):
         #   self.interVarsGauss = x1
          #  self.interVarsUncorrelated = x2
            
        x1 = None #!!
        
        # construct the uniform functions of the projected variables
	self.U2FS = _UFS(x2)
        # transform the projected variables into final ones
        
    def gaussianize(self,inputvars,UFS):
        """ apply a list of uniform fuction to a list of variables
        """
	x = []
	
	for i in range(len(inputvars)):
            x.append(UFS[i](inputvars[i]))
	return map(toGauss,x)  ## x' = erf-1(2*F(x)-1)
	
	
    def rotate(self,R,xmultivars):
        """ Apply the rotation matrix to a list of list of variables
        """
	n = len(xmultivars)
	nn = len(xmultivars[0])
	ymultivars = []
	for i in range(n): ymultivars.append([])
	for i in range(nn):
	    x0 = n*[0.]  ##### It's an entry !!!!!!!, n is the number of variables !!
	    for j in range(n): x0[j] = xmultivars[j][i]
	    x0 = numpy.array(x0)
	    #print x0
	    #print R
	    #u0 = numpy.array(numpy.matrixmultiply(R,x0))
	    u0 = numpy.array(numpy.matrixmultiply(R,x0)) #!!!!!!!!!!!!!!!!!!!!!!!!!?/
	    #print u0
	    for j in range(n):
                # TODO: change from lxplus to Mac 
		ymultivars[j].append(u0[0][j])
		#print ymultivars[j][-1]
	return ymultivars

    def __call__(self,inputvars):
        """ Apply the operator to an entry
        """
	x0 = inputvars
        #if isinstance(inputvars,dict): x0 = inputvars.values()
	x1 = self.gaussianize(x0,self.U1FS)
	
	x2 = numpy.array(numpy.matrixmultiply(self.R,numpy.array(x1)))
        
	return self.gaussianize(x2[0],self.U2FS)

class GaussDiscriminantOperator:
    """ GaussDiscriminatOperator provides a discriminating variable between signal and noise
    The discrimination uses the UnCorrGaussOperator to transform 
    the signal and noise distributions into a gaussian ones. 
    For each event the probability (related to the chi2) of been a signal and noise, 
    in the transformed gaussian space, it is computed as the discriminat variable
    """
    def __init__(self,signal,noise):
        """ contruction of the Gauss Discriminat Operator
        @t0: a list of list of variables for the signal sample
        @t1: a list of list of variables for the background sample
        """
        # creates the UniOperator for signal and background
        print " Constructing Signal Decorrelator"
	self.signalOper = UnCorrGaussOperator(signal)
        print " Constructing Background Decorrelator"
	self.noiseOper  = UnCorrGaussOperator(noise)

        # compute the delta chi2 of the signal sample
        print "Computing Delta Chi2"
        ### signal is a list of columns !!!!!!!
        columns = range(len(signal))
        entries = range(len(signal[0]))
        #i = 0
        entry = len(signal)*[0.]
        deltaList = len(signal[0])*[0.]
        for i in entries:
            for j in columns:
                entry[j] = signal[j][i]
            deltaList[i] = self.deltaChi2(entry)["delta"]
         #   i += 1
        # create a uniform function the delta chi2 distribution of the signal
	self.usb = UniFunc(deltaList) 

    def deltaChi2(self,entry):
        """ computes the discrimant variable in a given entry
        @sample: a list of list of variables (or a dictionary of list)
        returns a dictionary of list, with the transformation of the sample into 
	the signal space, the background space, and the discriminat variable. 
        """
	h0 = self.signalOper(entry)
	h1 = self.noiseOper(entry)
	ch0 = chi2(h0)
	ch1 = chi2(h1)
	#dch = numpy.array(ch1)-numpy.array(ch0) # A chi2 per entry
        n = len(h0)
        outvars = {}
        for i in range(n):
            outvars["s"+str(i)] = h0[i]
            outvars["n"+str(i)] = h1[i]
        outvars["delta"] = ch1 - ch0
        outvars["chi2s"] = ch0
        outvars["chi2b"] = ch1
        return outvars
    
    def __call__(self,entry):
        """ computes the uniform discrimant variable in a sample
        @sample: a list of list of variables that correspond at this sample
        returns the list of uniform decorrelated variables accoring to the
        signal, to the background, and the last list correspond to the discriminat
        variable
        """
	outvars = self.deltaChi2(entry)
	outvars["sb"] = self.usb(outvars["delta"])
	return  outvars
    
