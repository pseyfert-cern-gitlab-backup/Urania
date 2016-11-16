#Calculate significance from the -log(L)
from ROOT import *

def getSignificance(llb, ll, ndf = 1, comment = ''):

    # Statistic    t = -2log( L_null / L_hyp )
    #              t = -2 ( log(L_null) - log(L_hyp))
    #              t =  2 ( -log(L_null) - (-log(L_null)))
    #  llb and ll are -log(L) from RooNLLVar::getVal()
    #              t =  2 [ llb - ll]

    deltaNLL = 2*(llb - ll);

    print " ----------------------------------------------- "
    print " o) Calculating the significance for:"
    print " ", comment
    print "   -log(L_null) =",llb
    print "   -log(L_hyp) =",ll
    print "   2*Delta log likelihood: -2log(L_null / L_hyp) = ",deltaNLL

    pvalue = TMath.Prob(deltaNLL,ndf)
    print "   p value is " , pvalue

    sigma = sqrt(2.)*TMath.ErfInverse(1-pvalue);
    print "   This corresponds to: ", sigma , ' sigma'
    print " ----------------------------------------------- "

    return sigma



def sigmas(offset = 1):

    if offset:
        #This is the -log(L) of the fitted model:
        # a) The null model
        nll_null        =  -39498.7731133
        # b) BRs free
        nll_brs         =  -39505.6527706
        getSignificance(nll_null,nll_brs,1,' BRs fit w.r.t. BRs=BRd=0')
        # c) BRs free
        nll_brd         =  -39499.9535895
        getSignificance(nll_null,nll_brd,1,' BRd fit w.r.t. BRs=BRd=0')
        # d) BRs,BRd free
        nll_brs_brd     =  -39507.1901171
        getSignificance(nll_null,nll_brs_brd,2,' BRs,BRd fit w.r.t. BRs=BRd=0')
        print '  RESULTS WITH OFFSET! '

    else:
        #This is the -log(L) of the fitted model:
        # a) The null model
        nll_null        =  -39498.7732527
        # b) BRs free
        nll_brs         =  -39505.6526336
        getSignificance(nll_null,nll_brs,1,' BRs fit w.r.t. BRs=BRd=0')
        # c) BRd free
        nll_brd         =  -39499.9536189
        getSignificance(nll_null,nll_brd,1,' BRd fit w.r.t. BRs=BRd=0')
        # d) BRs,BRd free
        nll_brs_brd     =  -39507.1899438
        getSignificance(nll_null,nll_brs_brd,2,' BRs,BRd fit w.r.t. BRs=BRd=0')

        print '  RESULTS WITHOUT OFFSET! '




