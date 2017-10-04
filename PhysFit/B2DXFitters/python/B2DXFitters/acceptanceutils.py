"""
@file acceptanceutils.py

@author Manuel Schiller <Manuel.Schiller@cern.ch>
@date 2015-06-11

@brief utilities to build acceptance functions
"""
import ROOT
from B2DXFitters.WS import WS as WS 

def buildSplineAcceptance(
        ws,     # workspace into which to import
        time,   # time variable
        pfx,    # prefix to be used in names
        knots,  # knots
        coeffs, # acceptance coefficients
        floatParams = False, # float acceptance parameters
        extrapolate = True, # do linear extrapolation for the last knot. The next to last coefficient is fixed to one
        toFix = [], # knot positions to be fixed
        debug = False # debug printout
        ): 
    """
    build a spline acceptance function

    ws          -- workspace into which to import acceptance functions
    time        -- time observable
    pfx         -- prefix (mode name) from which to build object names
    knots       -- list of knot positions
    coeffs      -- spline coefficients
    floatParams -- if True, spline acceptance parameters will be floated
    extrapolate -- if True, do linear extrapolation for the last knot. The next to last coefficient is fixed to one
    toFix       -- knot positions to be fixed 
    debug       -- if True, print some debugging output

    returns a pair of acceptance functions, first the unnormalised one for
    fitting, then the normalised one for generation

    The minimum and maximum of the range of the time variable implicitly
    defines the position of the first and last knot. The other knot positions
    are passed in knots. Conversely, the coeffs parameter records the height
    of the sline at all but the last two knot positions. The next to last knot
    coefficient is fixed to 1.0, thus fixing the overall scale of the
    acceptance function. The spline coefficient for the last knot is fixed by
    extrapolating linearly from the two knots before; this prevents
    statistical fluctuations at the low stats high lifetime end of the
    spectrum to curve the spline.
    """
    # build acceptance function
    from copy import deepcopy
    myknots = deepcopy(knots)
    mycoeffs = deepcopy(coeffs)
    if debug:
        print 'DEBUG: knots and coefficients lists:'
        print myknots
        print mycoeffs
    from ROOT import (RooBinning, RooArgList, RooPolyVar, RooCubicSplineFun,
            RooConstVar, RooProduct, RooRealVar)
    if ( ((len(myknots) != len(mycoeffs)) and extrapolate) or 0 >= min(len(myknots), len(mycoeffs))):
        raise ValueError('ERROR: Spline knot position list and/or coefficient'
                'list mismatch. Same lenght is required for linear extrapolation')
    if ( ((len(myknots)+1 != len(mycoeffs)) and not extrapolate) or 0 >= min(len(myknots), len(mycoeffs))):
        raise ValueError('ERROR: Spline knot position list and/or coefficient'
                         'list mismatch. Number of coefficients = number of knots+1 is required without linear extrapolation')
    one = WS(ws, RooConstVar('one', '1', 1.0))
    # create the knot binning
    knotbinning = WS(ws, RooBinning(time.getMin(), time.getMax(),
        '%s_knotbinning' % pfx))
    for v in myknots:
        knotbinning.addBoundary(v)
    if debug:
        print 'DEBUG: Spline knots: %s' % str([
            knotbinning.array()[i] for i in xrange(0, knotbinning.numBoundaries())
            ])
    knotbinning.removeBoundary(time.getMin())
    knotbinning.removeBoundary(time.getMax())
    knotbinning.removeBoundary(time.getMin())
    knotbinning.removeBoundary(time.getMax())
    oldbinning, lo, hi = time.getBinning(), time.getMin(), time.getMax()
    time.setBinning(knotbinning, '%s_knotbinning' % pfx)
    time.setBinning(oldbinning)
    time.setRange(lo, hi)
    del oldbinning
    del knotbinning
    del lo
    del hi
    # create the knot coefficients
    coefflist = RooArgList()
    i = 0
    for v in mycoeffs:
        if floatParams and i not in toFix:
            coefflist.add(WS(ws, RooRealVar('%s_SplineAccCoeff%u' % (pfx, i),
                                            'v_{%u}' % (i+1), v, 0., 3.)))
        else:
            coefflist.add(WS(ws, RooConstVar('%s_SplineAccCoeff%u' % (pfx, i),
                                             'v_{%u}' % (i+1), v)))
        i = i + 1
    if extrapolate:
        coefflist.add(one)
    i = i + 1
    del mycoeffs
    myknots.append(time.getMax())
    myknots.reverse()
    fudge = (myknots[0] - myknots[1]) / (myknots[2] - myknots[1])
    if debug:
        print 'DEBUG: slope for last coefficients %f' % (fudge)
    lastmycoeffs = RooArgList(
            WS(ws, RooConstVar('%s_SplineAccCoeff%u_coeff0' % (pfx, i),
                '%s_SplineAccCoeff%u_coeff0' % (pfx, i), 1. - fudge)),
            WS(ws, RooConstVar('%s_SplineAccCoeff%u_coeff1' % (pfx, i),
                '%s_SplineAccCoeff%u_coeff1' % (pfx, i), fudge)))
    polyCoeff = RooPolyVar(
                '%s_SplineAccCoeff%u' % (pfx, i), 'v_{%u}' % (i+1),
                        coefflist.at(coefflist.getSize() - 2), lastmycoeffs)

    if extrapolate:
        coefflist.add(WS(ws, polyCoeff))
    else:
        if floatParams:
            coefflist.add(WS(ws, RooRealVar('%s_SplineAccCoeff%u' % (pfx, i),
                                            'v_{%u}' % (i+1), polyCoeff.getVal(), 0., 3.)))
        else:
            coefflist.add(WS(ws, RooConstVar('%s_SplineAccCoeff%u' % (pfx, i),
                                             'v_{%u}' % (i+1), polyCoeff.getVal() )))
        
    del i
    del myknots
    if debug:
        print 'DEBUG: Spline Coeffs: %s' % str([
            coefflist.at(i).getVal() for i in xrange(0, coefflist.getSize())
            ])
    # create the spline itself
    tacc = WS(ws, RooCubicSplineFun('%s_SplineAcceptance' % pfx,
        '%s_SplineAcceptance' % pfx, time, '%s_knotbinning' % pfx,
        coefflist))
    del lastmycoeffs
    if not floatParams:
        # make sure the acceptance is <= 1 for generation
        m = max([coefflist.at(j).getVal() for j in
            xrange(0, coefflist.getSize())])
        c = WS(ws, RooConstVar('%s_SplineAccNormCoeff' % pfx,
            '%s_SplineAccNormCoeff' % pfx, 0.99 / m))
        tacc_norm = WS(ws, RooProduct('%s_SplineAcceptanceNormalised' % pfx,
            '%s_SplineAcceptanceNormalised' % pfx, RooArgList(tacc, c)))
        del c
        del m
    else:
        tacc_norm = None # not supported when floating
    del coefflist
    return tacc, tacc_norm

