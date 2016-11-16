import os
os.system('rm KsMuMuResults.py')
import ROOT
f = ROOT.TFile('OutputPlots.root', 'RECREATE' )
f.Close()
for cat in ['TOS1_', 'TOS2_', 'TIS_']:
    for i in xrange(10):
        os.system('python Fit_KsMuMu.py ' + cat + ' ' + str(i))
