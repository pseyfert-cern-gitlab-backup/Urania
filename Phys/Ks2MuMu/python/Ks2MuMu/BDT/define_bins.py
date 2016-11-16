from sklearn.externals import joblib
import sys, os
import root_numpy
import numpy
import pandas
from scikit_BDT_vars import BDTVARS
import ROOT as rt
import matplotlib.pyplot as plt
from PlotTools import MakeAdaptiveBinnedHist

# ---------------------------------------
# Background rejection and number of bins
BKGREJ = 99./100
NBINS  = 10
# ---------------------------------------
# Enable showing the plots
SHOW = False
# ------------------------------------------
# Output file
OFILE = rt.TFile('bdtBins.root', 'RECREATE')
# ------------------------------------------

assert BKGREJ < 1., 'ERROR: Background rejection must be smaller than 1'

TRIGDICT = {'TosTos1Tos': 'TOS1_', 'TosTos2Tos': 'TOS2_'}

sys.path.append('../')
from fiducial import *

rt.gROOT.SetBatch(not SHOW)
for cat in ('TosTos1Tos', 'TosTos2Tos'):
    saveset = joblib.load('saveOutput_' + cat + '.pkl')
    decbkg  = saveset[4]
    newlst  = sorted(decbkg)
    while len(newlst)*1./len(decbkg) > 1. - BKGREJ:
        newlst.pop(0)
    ct = newlst[0]
    print '--- Loose cut for category:', cat, '=>', ct
    n = len(decbkg)
    plt.hist(decbkg,
             weights  = n*[1./n],
             bins     = 100,
             range    = (0,1),
             histtype = 'stepfilled',
             alpha    = 0.5)
    plt.plot([ct, ct], [0, 1], 'r-')
    ax = plt.subplot(1, 1, 1)
    ax.set_yscale('log', nonposy = 'clip')
    if SHOW:
        plt.show()

    ipath = 'root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/'
    ifile = rt.TFile(ipath + 'Ksmumu_StrippedMC2012_mcMatch_MVA.root')
    ofile = rt.TFile('dummy.root', 'RECREATE')
    print '--- Copying input tree...'
    otree = ifile.Get('DecayTree').CopyTree(SEL[TRIGDICT[cat]])
    otree.AutoSave()
    ofile.Close()
    print '--- Extracting BDT values'
    bdt   = root_numpy.root2array('dummy.root', 'DecayTree', branches = ['BDT' + cat])
    bdt   = numpy.array([b[0] for b in bdt])
    bdtct = bdt[bdt>ct]
    os.system('rm dummy.root')

    OFILE.cd()
    minocc = len(bdtct)/NBINS
    print '--- Minimum occupancy:', minocc
    hct = MakeAdaptiveBinnedHist('SigEff_' + cat, minocc, bdtct.tolist(),
                                 title = 'Signal efficiency for ' + cat)
    hct.Sumw2()
    for b in bdtct:
        hct.Fill( b )
    hct.Scale(1./hct.GetSumOfWeights())
    hct.Draw('E1')
    hct.Write()
    binedges = [hct.GetBinLowEdge( i ) for i in xrange(1, hct.GetNbinsX() + 1)] + [1.]
    print '--- Bin edges (ending by 1) for category < %s >: %s' %(cat, binedges)

    print '--- Signal efficiency for category < %s >: %f' %(cat, len(bdtct)*1./len(bdt))

ofile.Close()
