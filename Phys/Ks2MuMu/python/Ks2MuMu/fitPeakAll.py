import os
os.system('rm KsMuMuPeakPars.py')
import ROOT
f = ROOT.TFile('OutputPlots.root', 'RECREATE' )
f.Close()
for cat in ['TOS1_', 'TOS2_', 'TIS_']:
    for i in xrange(10):
        os.system('python fitPeak.py ' + cat + ' ' + str(i))
