from sklearn.externals import joblib
import root_numpy
import numpy
import pandas
from scikit_BDT_vars import BDTVARS
import ROOT as rt
import matplotlib.pyplot as plt
from PlotTools import MakeAdaptiveBinnedHist
from scikit_BDT_utils import *

for cat in ('TosTos1Tos', 'TosTos2Tos'):
    saveset = joblib.load('saveOutput_' + cat + '.pkl')
    target, dec = saveset[1:3]
    makeROC( target, dec )
    print '--- Showing category < %s >' %cat
    plt.show()
