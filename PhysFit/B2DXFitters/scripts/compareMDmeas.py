#!/usr/bin/env python
# --------------------------------------------------------------------------- 
# @file prolog.py
#
# @brief Compare two or more sets of parameters (e.g. fit results).
#        After a minimisation of the chi2, it returns the discrepancy
#        between the measurements in number of sigmas.
#        The approach is the same followed by the HFLAV group:
#        https://arxiv.org/pdf/1612.07233.pdf (chapter 2)
#
# @author Vincenzo Battista
# @date 2017-08-27
#
# --------------------------------------------------------------------------- 
# This file is used as both a shell script and as a Python script.
""":"
# This part is run by the shell. It does some setup which is convenient to save
# work in common use cases.

# make sure the environment is set up properly
if test -n "$CMTCONFIG" \
         -a -f $B2DXFITTERSROOT/$CMTCONFIG/libB2DXFittersDict.so \
     -a -f $B2DXFITTERSROOT/$CMTCONFIG/libB2DXFittersLib.so; then
    # all ok, software environment set up correctly, so don't need to do 
    # anything
    true
else
    if test -n "$CMTCONFIG"; then
    # clean up incomplete LHCb software environment so we can run
    # standalone
        echo Cleaning up incomplete LHCb software environment.
        PYTHONPATH=`echo $PYTHONPATH | tr ':' '\n' | \
            egrep -v "^($User_release_area|$MYSITEROOT/lhcb)" | \
            tr '\n' ':' | sed -e 's/:$//'`
        export PYTHONPATH
        LD_LIBRARY_PATH=`echo $LD_LIBRARY_PATH | tr ':' '\n' | \
            egrep -v "^($User_release_area|$MYSITEROOT/lhcb)" | \
            tr '\n' ':' | sed -e 's/:$//'`
        export LD_LIBRARY_PATH
        exec env -u CMTCONFIG -u B2DXFITTERSROOT "$0" "$@"
    fi
    # automatic set up in standalone build mode
    if test -z "$B2DXFITTERSROOT"; then
        cwd="$(pwd)"
        # try to find from where script is executed, use current directory as
        # fallback
        tmp="$(dirname $0)"
        tmp=${tmp:-"$cwd"}
        # convert to absolute path
        tmp=`readlink -f "$tmp"`
        # move up until standalone/setup.sh found, or root reached
        while test \( \! -d "$tmp"/standalone \) -a -n "$tmp" -a "$tmp"\!="/"; do
            tmp=`dirname "$tmp"`
        done
        if test -d "$tmp"/standalone; then
            cd "$tmp"/standalone
            . ./setup.sh
        else
            echo `basename $0`: Unable to locate standalone/setup.sh
            exit 1
        fi
        cd "$cwd"
        unset tmp
        unset cwd
    fi
fi

# figure out which custom allocators are available
# prefer jemalloc over tcmalloc
for i in libjemalloc libtcmalloc; do
    for j in `echo "$LD_LIBRARY_PATH" | tr ':' ' '` \
        /usr/local/lib /usr/lib /lib; do
        for k in `find "$j" -name "$i"'*.so.?' | sort -r`; do
            if test \! -e "$k"; then
            continue
        fi
        echo adding $k to LD_PRELOAD
        if test -z "$LD_PRELOAD"; then
            export LD_PRELOAD="$k"
            break 3
        else
            export LD_PRELOAD="$LD_PRELOAD":"$k"
            break 3
        fi
    done
    done
done

# set batch scheduling (if schedtool is available)
schedtool="`which schedtool 2>/dev/zero`"
if test -n "$schedtool" -a -x "$schedtool"; then
    echo "enabling batch scheduling for this job (schedtool -B)"
    schedtool="$schedtool -B -e"
else
    schedtool=""
fi

# set ulimit to protect against bugs which crash the machine: 3G vmem max,
# no more then 8M stack
ulimit -v $((3072 * 1024))
ulimit -s $((   8 * 1024))

# trampoline into python
exec $schedtool /usr/bin/time -v env python -O "$0" - "$@"
"""
__doc__ = """ real docstring """
#"
# -----------------------------------------------------------------------------
# Load necessary libraries
# -----------------------------------------------------------------------------

import B2DXFitters
import ROOT
from ROOT import TROOT, TSystem, TVector, TMatrix, TMinuit, TDecompChol, TMath, TMatrixDSym

from optparse import OptionParser
from math import pi, log, sqrt
from os.path import exists
import os, sys, gc
import copy

import numpy as np

import array
from array import array

# -----------------------------------------------------------------------------
def TakeXMLCalibration(xml):

    import Espresso
    from ROOT import RooRealVar, RooArgSet
    
    eta = RooRealVar("eta", "eta", 0.0, 0.5)
    glm = ROOT.Espresso.GLMBuilder(xml.rsplit('.')[-2].rsplit('/')[-1],
                                   xml.rsplit('.')[-2].rsplit('/')[-1],
                                   eta,
                                   xml.rsplit('.')[-2].rsplit('/')[-1],
                                   xml)

    cov = glm.covariance_matrix().covarianceMatrix()

    n = glm.coefficients().getSize()
    if n != glm.delta_coefficients().getSize():
        raise ValueError("TakeXMLCalibration(...) => ERROR: number of coefficients != number of delta coefficients in %s. Something wrong with the file..." % xml)
    meas = TVector(2*n)

    coeffset = RooArgSet(glm.coefficients())
    citer = coeffset.createIterator()
    c = citer.Next()
    
    dcoeffset = RooArgSet(glm.delta_coefficients())
    dciter = dcoeffset.createIterator()
    dc = dciter.Next()

    i=0
    while c:
        meas[i] = c.getVal()
        c = citer.Next()
        i += 1
    i=n
    while dc:
        meas[i] = dc.getVal()
        dc = dciter.Next()
        i += 1

    return meas, cov

# -----------------------------------------------------------------------------
def InvertMatrix(matrix):

    chol = TDecompChol(matrix)
    inv = chol.Invert()
    if not inv:
        raise ValueError("InvertMatrix(...) => ERROR: matrix not inverted")
    return inv

# -----------------------------------------------------------------------------
def chi2( par, npar, measurements, covMatrices ):
    """
    chi2 square function to combine measurements:

    chi2(x) = Sum_i (X_i - x)^T V_i^-1 (X_i - x)

    where the sum id done over all inputs, X_i is the i-th array
    of measurements and V_i^-1 is the inverse of the i-th covariance matrix.

    The minimized chi2(x) gives the average x of the measurements
    This value, divided by the n.d.o.f, gives an estimate of the compatibility
    between the input measurements
    """
    
    #Initialise x
    x = TVector(int(npar[0]))
    for p in range(0, npar[0]):
        x[p] = par[p]

    #Compute chi^2
    chi2 = 0

    for i in range(0, measurements.__len__()):
        """
        Because of a bug in PyROOT, we cannot
        make operations between TMatrix/TVector like:

        diff = measurements[i] - x
        prod = diff * covMatrices[i]
        chi2 += prod * diff

        This triggers the following error:

        Error in <TClingCallFunc::make_wrapper>: Cannot make wrapper for a function templateinstantiation with no body!

        Hopefully that will be fixed at some point:
        https://sft.its.cern.ch/jira/browse/ROOT-7717
        """
        #Compute difference X_i - x
        diff = []
        for el in range(0, npar[0]):
            diff.append(measurements[i][el] - x[el])

        #Compute product (X_i - x)^T V_i^-1
        prod = []
        for col in range(0, npar[0]):
            val = 0.0
            for row in range(0, npar[0]):
                val += diff[row] * covMatrices[i][col][row]
            prod.append( val )

        #Compute product (X_i - x)^T V_i^-1 (X_i - x)
        for el in range(0, npar[0]):
            chi2 += prod[el] * diff[el]

    return chi2
    
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
def compareMDmeas(configName, debug):
    
    # Get the configuration file
    myconfigfilegrabber = __import__(configName, fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()

    from B2DXFitters.MDFitSettingTranslator import Translator
    mdt = Translator(myconfigfile, "MDSettings", False)
    MDSettings = mdt.getConfig()

    print "=========================================================="
    print "COMPAREMDMEAS IS RUNNING WITH THE FOLLOWING CONFIGURATION OPTIONS"
    for option in myconfigfile:
        if option == "constParams":
            for param in myconfigfile[option]:
                print param, "is constant in the fit"
        else:
            print option, " = ", myconfigfile[option]
    print "=========================================================="

    print ""
    print 60*"#"
    print "Taking input measurements/covariance matrices"
    print 60*"#"
    print ""

    measurements = []
    covMatrices = []
    covMatricesInv = []
    titles = []

    for input in myconfigfile["Inputs"].iterkeys():

        print "Taking " + input + " input..."
        titles.append(input)

        if "XML" in myconfigfile["Inputs"][input].keys():
            #Take measurements and covariance matrix from XML file produced by EspressoPerformanceMonitor
            print "...from XML file"
            meas, cov = TakeXMLCalibration(myconfigfile["Inputs"][input]["XML"])
            measurements.append( meas )
            covMatrices.append( cov )
            covMatricesInv.append( InvertMatrix(cov) )

        elif "Values" and "Errors" and "Correlation" in myconfigfile["Inputs"][input].keys():
            #Build everything from the config file directly
            print "...building from config file"
            from B2DXFitters.utils import BuildCovMatFromCorrMat

            n = myconfigfile["Inputs"][input]["Values"].__len__()

            meas = TVector(n)
            for i in range(0, n):
                meas[i] = myconfigfile["Inputs"][input]["Values"][i]

            measurements.append( meas )

            if myconfigfile["Inputs"][input]["Errors"] != None and myconfigfile["Inputs"][input]["Correlation"] != None:
                cov = BuildCovMatFromCorrMat(n,
                                             myconfigfile["Inputs"][input]["Errors"],
                                             myconfigfile["Inputs"][input]["Correlation"],
                                             False) #do not apply any regularisation by hand, for the moment...
                covMatrices.append( cov )
                covMatricesInv.append( InvertMatrix(cov) )
            else:
                #Assume to have "exact" (true) values to compare with
                cov = TMatrixDSym(n)
                for row in range(0,n):
                    for col in range(0,n):
                        cov[row][col] = 0.0
                covMatricesInv.append( cov )
                covMatrices.append( cov )

        else:
            raise ValueError("compareMDmeas(...) => ERROR: Need to specify either 'XML' key or 'Values', 'Errors', 'Correlation' keys in the config file dictionary")

    if debug:
        print "Summary of input measurements:"
        for meas in measurements:
            meas.Print("v")
        print "Summary of covariance matrices:"
        for cov in covMatrices:
            cov.Print("v")
        print "Summary of inverted covariance matrices:"
        for cov in covMatricesInv:
            cov.Print("v")

    nparams = measurements[0].GetNoElements()
    nmeas = measurements.__len__()

    print ""
    print 60*"#"
    print "Build Chi2 function"
    print 60*"#"
    print ""

    def fcn( npar, gin, f, par, flag ):
        """
        Objective function as required by MINUIT
        We pray the Python gods that this works outside the C/C++/Fortran world as well...
        """        
        f[0] = chi2(par, npar, measurements, covMatricesInv)

    #---Instantiate MINUIT
    mn = TMinuit( nparams )
    mn.SetFCN( fcn )

    #---Initialisation
    #We take the simple, arithmetic average as starting point
    startList = [0.0]*nparams
    for p in range(0, nparams):
        for m in range(0,nmeas):
            startList[p] += measurements[m][p]
        startList[p] /= nmeas
    start = array('d', startList)

    #Step size: 1/1000 of the magnitude of the starting parameter
    stepList = []
    for s in startList:
        if s != 0:
            stepList.append( np.sign(s) * s / 1000.0 )
        else:
            stepList.append( 0.0001)
    step = array('d', stepList)

    #Boundaries:
    minList = []
    maxList = []
    for s in startList:
        if s<0:
            minList.append( s*10.0 )
            maxList.append( s/10.0 )
        elif s>0:
            minList.append( s/10.0 )
            maxList.append( s*10.0 )
        else:
            minList.append( -10.0 )
            maxList.append( 10.0 )

    min = array('d', minList)
    max = array('d', maxList)
            
    ierflg = array('i', [0])
    if "Parameters" in myconfigfile.keys():
        for p in range(0, nparams):
            mn.mnparm(p, myconfigfile["Parameters"][p], start[p], step[p], min[p], max[p], ierflg)
    else:
        for p in range(0, nparams):
            mn.mnparm(p, "par"+str(p), start[p], step[p], min[p], max[p], ierflg)

    #---MINUIT settings
    arglist = array( 'd', 10*[0.] )
    
    #chi2 error
    arglist[0] = 1
    mn.mnexcm( "SET ERR", arglist, 1, ierflg )

    #strategy: improve minimum
    arglist[0] = 2
    mn.mnexcm("SET STR", arglist, 1, ierflg)

    #---Run MIGRAD with max 1000 iterations
    arglist[0] = 1000
    mn.mnexcm( "MIGRAD", arglist, 1, ierflg )

    chi2min = array('d', [0.0])
    edm = array('d', [0.0])
    errdef = array('d', [0.0])
    nvpar = array('i', [0])
    nparx = array('i', [0])
    icstat = array('i', [0])
    mn.mnstat( chi2min, edm, errdef, nvpar, nparx, icstat )

    print ""
    print 60*"#"

    print "Minimised chi2 value:"
    print chi2min[0]

    ndof = measurements.__len__()*mn.GetNumFreePars() - mn.GetNumFreePars()

    print "Number of degrees of freedom:"
    print ndof

    #p-value: integral of chi2 from observed chi2 to infinity
    #the smaller the p-value, the higher the discrepancy
    pvalue = TMath.Prob(chi2min[0], ndof)
    print "p-value:"
    print pvalue

    #Z-score: from the error function Z=Phi^-1(1-pvalue)
    #it gives the discrepancy in sigma
    Zscore = TMath.ErfInverse(1-pvalue)
    print "Z-score (sigma):"
    print Zscore

    print 60*"#"
    print ""

    if nmeas == 2:

        #Return the 1D discrepancy parameter-by-parameter as well,
        #defined as sigma = (par1-par2) / sqrt(sigma1^2 + sigma2^2)
        #The following assumptions are thus made:
        #1) Correlations between parameters are neglected
        #2) The two measurements are assumed to be fully uncorrelated

        import uncertainties
        from uncertainties import ufloat

        #Print discrepancies
        sigmas = []
        meas1 = []
        meas2 = []
        for p in range(0, nparams):
            meas1.append( ufloat( measurements[0][p], sqrt( covMatrices[0][p][p] ) ) )
            meas2.append( ufloat( measurements[1][p], sqrt( covMatrices[1][p][p] ) ) )
            sigmas.append( (meas1[p].n - meas2[p].n) / sqrt( meas1[p].s*meas1[p].s + meas2[p].s*meas2[p].s ) )

        print ""
        print 60*"#"
        print "1D discrepancies (sigma) between parameters:"
        print "Parameter   &   "+titles[0]+"   &   "+titles[1]+"   &   Discrepancy ($\sigma$) "+r"\\"
        print "\hline"
        for p in range(nparams):

            #Parameter name
            line = "$"+myconfigfile["Parameters"][p]+"$   &   "

            #Measurements
            latexval=r'{0:.2u}'.format(meas1[p]).replace("+/-","\pm")
            line+="$"+latexval+"$   &   "

            latexval=r'{0:.2u}'.format(meas2[p]).replace("+/-","\pm")
            line+="$"+latexval+"$   &   "

            #Sigma
            latexval=r'{0:.2f}'.format(sigmas[p])
            line+="$"+latexval+"$ "

            #Print
            print line+r"\\"
            
        print "\hline"
        print 60*"#"
        print ""
    
# -----------------------------------------------------------------------------
_usage = '%prog [options]'

parser = OptionParser(_usage)

parser.add_option('--configName',
                  dest = 'configName',
                  default = 'MyConfigFile',
                  help = 'configuration file name')

parser.add_option('-d', '--debug',
                  dest    = 'debug',
                  default = False,
                  action  = 'store_true',
                  help    = 'print debug information while processing'
                  )

# -----------------------------------------------------------------------------

if __name__ == '__main__':
        (options, args) = parser.parse_args()

        config = options.configName
        last = config.rfind("/")
        directory = config[:last + 1]
        configName = config[last + 1:]
        p = configName.rfind(".")
        configName = configName[:p]

        sys.path.append(directory)

        compareMDmeas(configName, options.debug)
        
